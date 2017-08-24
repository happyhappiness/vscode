{
#ifdef FSCTL_GET_REPARSE_POINT
  const DWORD JUNCTION_ATTRS =
    FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_REPARSE_POINT;
  DWORD attrs = GetFileAttributesW(source.c_str());
  if (attrs == INVALID_FILE_ATTRIBUTES) {
    return false;
  }
  if ((attrs & JUNCTION_ATTRS) != JUNCTION_ATTRS) {
    return false;
  }

  // Adjust privileges so that we can succefully open junction points.
  HANDLE token;
  TOKEN_PRIVILEGES privs;
  OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token);
  LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &privs.Privileges[0].Luid);
  privs.PrivilegeCount = 1;
  privs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  AdjustTokenPrivileges(token, FALSE, &privs, sizeof(TOKEN_PRIVILEGES), NULL,
                        NULL);
  CloseHandle(token);

  HANDLE dir = CreateFileW(
    source.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
    FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
  if (dir == INVALID_HANDLE_VALUE) {
    return false;
  }

  // Query whether this is a reparse point or not.
  BYTE buffer[MAXIMUM_REPARSE_DATA_BUFFER_SIZE];
  REPARSE_GUID_DATA_BUFFER* reparse_buffer = (REPARSE_GUID_DATA_BUFFER*)buffer;
  DWORD sentinel;

  BOOL success =
    DeviceIoControl(dir, FSCTL_GET_REPARSE_POINT, NULL, 0, reparse_buffer,
                    MAXIMUM_REPARSE_DATA_BUFFER_SIZE, &sentinel, NULL);

  CloseHandle(dir);

  return (success &&
          (reparse_buffer->ReparseTag == IO_REPARSE_TAG_MOUNT_POINT));
#else
  return false;
#endif
}