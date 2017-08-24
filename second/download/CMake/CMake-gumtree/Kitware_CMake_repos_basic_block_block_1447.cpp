{
  HANDLE fout;
  wchar_t* wname;
  DWORD error;
  if (!name) {
    return ERROR_INVALID_PARAMETER;
  }

  /* Close the existing handle.  */
  kwsysProcessCleanupHandle(phandle);

  /* Create a handle to write a file for the pipe.  */
  wname = kwsysEncoding_DupToWide(name);
  fout =
    CreateFileW(wname, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
  error = GetLastError();
  free(wname);
  if (fout == INVALID_HANDLE_VALUE) {
    return error;
  }

  /* Assign the replacement handle.  */
  *phandle = fout;
  return ERROR_SUCCESS;
}