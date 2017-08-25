{
  DWORD lastmsg = GetLastError();
  LPVOID msg;
  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,
    lastmsg,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &msg,
    0,
    NULL
  );
  printf("%d - %s: %s (%d)\n",line,str,msg, lastmsg);
  LocalFree(msg);
  ::SetLastError(ERROR_SUCCESS);
}