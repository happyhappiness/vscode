{
#ifdef FSCTL_DELETE_REPARSE_POINT
  // Adjust privileges so that we can succefully open junction points as
  // read/write.
  HANDLE token;
  TOKEN_PRIVILEGES privs;
  OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token);
  LookupPrivilegeValue(NULL, SE_RESTORE_NAME, &privs.Privileges[0].Luid);
  privs.PrivilegeCount = 1;
  privs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  AdjustTokenPrivileges(token, FALSE, &privs, sizeof(TOKEN_PRIVILEGES), NULL,
                        NULL);
  CloseHandle(token);

  HANDLE dir = CreateFileW(
    source.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
    FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
  if (dir == INVALID_HANDLE_VALUE) {
    return false;
  }

  // Set up the structure so that we can delete the junction.
  std::vector<BYTE> buffer(REPARSE_GUID_DATA_BUFFER_HEADER_SIZE, 0);
  REPARSE_GUID_DATA_BUFFER* reparse_buffer =
    (REPARSE_GUID_DATA_BUFFER*)&buffer[0];
  DWORD sentinel;

  reparse_buffer->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;

  BOOL success = DeviceIoControl(
    dir, FSCTL_DELETE_REPARSE_POINT, reparse_buffer,
    REPARSE_GUID_DATA_BUFFER_HEADER_SIZE, NULL, 0, &sentinel, NULL);

  CloseHandle(dir);

  return !!success;
#else
  return false;
#endif
}