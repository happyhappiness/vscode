size_t SyncTime_CURL_WriteHeader(void *ptr, size_t size, size_t nmemb,
                                 void *stream)
{
  int   i, RetVal;
  char  TmpStr1[26], TmpStr2[26];

  if (ShowAllHeader == 1)
    fprintf(stderr, "%s", (char *)(ptr));

  if (strncmp((char *)(ptr), "Date:", 5) == 0) {
    if (ShowAllHeader == 0)
      fprintf(stderr, "HTTP Server. %s", (char *)(ptr));

    if (AutoSyncTime == 1) {
      *TmpStr1 = 0;
      *TmpStr2 = 0;
      if (strlen((char *)(ptr)) > 50) /* Can prevent buffer overflow to
                                         TmpStr1 & 2? */
        AutoSyncTime = 0;
      else {
        RetVal = sscanf ((char *)(ptr), "Date: %s %hu %s %hu %hu:%hu:%hu",
                         TmpStr1, &SYSTime.wDay, TmpStr2, &SYSTime.wYear,
                         &SYSTime.wHour, &SYSTime.wMinute, &SYSTime.wSecond);

        if (RetVal == 7) {

          SYSTime.wMilliseconds = 500;    /* adjust to midpoint, 0.5 sec */
          for (i=0; i<12; i++) {
            if (strcmp(MthStr[i], TmpStr2) == 0) {
              SYSTime.wMonth = i+1;
              break;
            }
          }
          AutoSyncTime = 3;       /* Computer clock will be adjusted */
        }
        else {
          AutoSyncTime = 0;       /* Error in sscanf() fields conversion */
        }
      }
    }
  }

  if (strncmp((char *)(ptr), "X-Cache: HIT", 12) == 0) {
    fprintf(stderr, "ERROR: HTTP Server data is cached."
            " Server Date is no longer valid.\n");
    AutoSyncTime = 0;
  }
  return(nmemb*size);
}