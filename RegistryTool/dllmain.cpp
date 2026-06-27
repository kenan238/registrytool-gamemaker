#include "pch.h"
#include <unordered_map>
#include <string>
#include <vector>

#define GML extern "C" __declspec(dllexport)

std::unordered_map<double, HKEY> registryMap;
double currentId = 1.0;

static double ResultToGML(bool result) {
  return result ? 1.0 : 0.0;
}

static double ResultToGML(LONG result) {
  return (result == ERROR_SUCCESS) ? 1.0 : 0.0;
}

GML double reg_key_open(const char* path) {
  HKEY hKey;
  LONG result = RegCreateKeyExA(HKEY_CURRENT_USER, path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

  if (result == ERROR_SUCCESS) {
    double assignedId = currentId++;
    registryMap[assignedId] = hKey;

    return assignedId;
  }

  return 0.0;
}

GML double reg_key_free(double keyId) {
  auto it = registryMap.find(keyId);

  if (it != registryMap.end()) {
    RegCloseKey(it->second);
    registryMap.erase(it);
    return 1.0;
  }

  return 0.0;
}

static HKEY GetKey(double keyId) {
  auto it = registryMap.find(keyId);

  if (it == registryMap.end()) {
    return NULL;
  }

  return it->second;
}

GML double reg_key_exists(double keyId) {
  HKEY hKey = GetKey(keyId);
  return ResultToGML(hKey != NULL);
}

GML double reg_key_write_string(double keyId, const char* valueName, const char* data) {
  HKEY hKey = GetKey(keyId);
  if (hKey == NULL || data == NULL)
    return 0.0;

  LONG result = RegSetValueExA(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(data), strlen(data) + 1);

  return ResultToGML(result);
}

GML double reg_key_write_double(double keyId, const char* valueName, double data) {
  HKEY hKey = GetKey(keyId);
  if (hKey == NULL)
    return 0.0;

  DWORD dwordValue = static_cast<DWORD>(data);

  LONG result = RegSetValueExA(hKey, valueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&dwordValue), sizeof(dwordValue));

  return ResultToGML(result);
}

GML double reg_key_read_double(double keyId, const char* valueName) {
  HKEY hKey = GetKey(keyId);
  if (hKey == NULL || valueName == NULL)
    return 0.0;

  DWORD dwordValue = 0;
  DWORD bufferSize = sizeof(dwordValue);
  DWORD valueType = 0; // let windows fill the type

  LONG result = RegQueryValueExA(
    hKey,
    valueName,
    NULL,
    &valueType,
    reinterpret_cast<LPBYTE>(&dwordValue),
    &bufferSize
  );

  // verify success
  if (result == ERROR_SUCCESS && (valueType == REG_DWORD || valueType == REG_QWORD)) {
    return static_cast<double>(dwordValue);
  }

  return 0.0;
}

GML const char* reg_key_read_string(double keyId, const char* valueName) {
  static std::string stringResult;
  HKEY hKey = GetKey(keyId);
  
  if (hKey == NULL || valueName == NULL)
    return "";

  DWORD bufferSize = 0;
  DWORD valueType = 0; // let windows fill ze type

  // first call with NULL buffer to get the exact size required by the registry string
  LONG result = RegQueryValueExA(hKey, valueName, NULL, &valueType, NULL, &bufferSize);

  if (result == ERROR_SUCCESS && (valueType == REG_SZ || valueType == REG_EXPAND_SZ)) {
    std::vector<char> buffer(bufferSize);

    result = RegQueryValueExA(
      hKey,
      valueName,
      NULL,
      &valueType,
      reinterpret_cast<LPBYTE>(buffer.data()),
      &bufferSize
    );

    if (result == ERROR_SUCCESS) {
      stringResult.assign(buffer.data(), bufferSize);
      while (!stringResult.empty() && stringResult.back() == '\0')
        stringResult.pop_back();
      return stringResult.c_str();
    }
  }

  return ""; 
}