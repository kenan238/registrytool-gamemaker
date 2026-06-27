\# RegistryTool



A registry manipulation extension for GameMaker, strictly limited to `HKEY\_CURRENT\_USER` for security reasons.



\## Functions



\### Key Management



\* \*\*`reg\_key\_open(path: string)`\*\*

Opens a registry key at the specified path. Returns an internal key handle (`double`), not the native Windows handle.

\* \*\*`reg\_key\_exists(keyId: number)`\*\*

Returns `1` if the key handle is valid and exists, `0` if it does not.

\* \*\*`reg\_key\_free(keyId: number)`\*\*

Frees the key handle and closes it. Returns `1` for success, `0` for failure.



\### Data Operations



\* \*\*`reg\_key\_write\_string(keyId: number, valueName: string, value: string)`\*\*

Writes a string to the specified value name. Returns `1` for success, `0` for failure.

\* \*\*`reg\_key\_write\_double(keyId: number, valueName: string, value: number)`\*\*

Writes a number (double) to the specified value name. Returns `1` for success, `0` for failure.

\* \*\*`reg\_key\_read\_string(keyId: number, valueName: string)`\*\*

Reads and returns a string from the specified value name. Returns `""` on failure.

\* \*\*`reg\_key\_read\_double(keyId: number, valueName: string)`\*\*

Reads and returns a double from the specified value name. Returns `0` on failure.

