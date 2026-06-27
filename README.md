# RegistryTool
A registry manipulation extension for GameMaker, limited to `HKEY_CURRENT_USER` for security reasons.

# Functions
`reg_key_open(path: string)`: returns the key's handle as a `double`, not the actual Windows handle.
`reg_key_free(keyId: number)`: frees the key handle and closes it (returns 1 for success, 0 for failure).
`reg_key_exists(keyId: number)`: returns 1 if exists, 0 if it doesn't.
`reg_key_write_string(keyId: number, valueName: string, value: string)`: writes a string to that value at that key (returns 1 for success, 0 for failure).
`reg_key_write_double(keyId: number, valueName: string, value: number)`: writes a number (double) to that value at that key (returns 1 for success, 0 for failure).
`reg_key_read_string(keyId: number, valueName: string)`: reads a string from that value at that key and returns it (returns 1 for success, 0 for failure).
`reg_key_read_double(keyId: number, valueName: string)`: reads a double from that value at that key and returns it (returns 1 for success, 0 for failure).