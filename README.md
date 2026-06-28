# RegistryTool

A registry manipulation extension for GameMaker, strictly limited to `HKEY_CURRENT_USER` for security reasons.

## Important Note on Paths

Paths should **not** include the `Computer\` or `HKEY_CURRENT_USER\` prefixes. All paths are automatically relative to `HKEY_CURRENT_USER` (mentioned above).

* ❌ **Incorrect:** `Computer\HKEY_CURRENT_USER\Software\MyGame`
* ✅ **Correct:** `Software\MyGame`

## Functions

### Key Management

* **`reg_key_open(path: string)`**
Opens a registry key at the specified path. Returns an internal key handle (`double`), not the native Windows handle.
* **`reg_key_exists(keyId: number)`**
Returns `1` if the key handle is valid and exists, `0` if it does not.
* **`reg_key_free(keyId: number)`**
Frees the key handle and closes it. Returns `1` for success, `0` for failure.

### Data Operations

* **`reg_key_write_string(keyId: number, valueName: string, value: string)`**
Writes a string to the specified value name. Returns `1` for success, `0` for failure.
* **`reg_key_write_double(keyId: number, valueName: string, value: number)`**
Writes a number (double) to the specified value name. Returns `1` for success, `0` for failure.
* **`reg_key_read_string(keyId: number, valueName: string)`**
Reads and returns a string from the specified value name. Returns `""` on failure.
* **`reg_key_read_double(keyId: number, valueName: string)`**
Reads and returns a double from the specified value name. Returns `0` on failure.