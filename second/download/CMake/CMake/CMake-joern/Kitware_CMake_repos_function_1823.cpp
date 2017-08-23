static void kwsys_shared_forward_strerror(char* message)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  /* Implementation for Windows.  */
  DWORD original = GetLastError();
  DWORD length =
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   0, original, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   message, KWSYS_SHARED_FORWARD_MAXPATH, 0);
  if (length < 1 || length > KWSYS_SHARED_FORWARD_MAXPATH) {
    /* FormatMessage failed.  Use a default message.  */
    _snprintf(message, KWSYS_SHARED_FORWARD_MAXPATH,
              "Error 0x%X (FormatMessage failed with error 0x%X)", original,
              GetLastError());
  }
#else
  /* Implementation for UNIX.  */
  strcpy(message, strerror(errno));
#endif
}