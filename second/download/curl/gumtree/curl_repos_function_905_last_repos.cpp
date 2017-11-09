static void setfiletime(long filetime, const char *filename,
                        FILE *error_stream)
{
  if(filetime >= 0) {
/* Windows utime() may attempt to adjust our unix gmt 'filetime' by a daylight
   saving time offset and since it's GMT that is bad behavior. When we have
   access to a 64-bit type we can bypass utime and set the times directly. */
#if defined(WIN32) && (SIZEOF_CURL_OFF_T >= 8)
    HANDLE hfile;

#if (SIZEOF_LONG >= 8)
    /* 910670515199 is the maximum unix filetime that can be used as a
       Windows FILETIME without overflow: 30827-12-31T23:59:59. */
    if(filetime > CURL_OFF_T_C(910670515199)) {
      fprintf(error_stream,
              "Failed to set filetime %ld on outfile: overflow\n",
              filetime);
      return;
    }
#endif /* SIZEOF_LONG >= 8 */

    hfile = CreateFileA(filename, FILE_WRITE_ATTRIBUTES,
                        (FILE_SHARE_READ | FILE_SHARE_WRITE |
                         FILE_SHARE_DELETE),
                        NULL, OPEN_EXISTING, 0, NULL);
    if(hfile != INVALID_HANDLE_VALUE) {
      curl_off_t converted = ((curl_off_t)filetime * 10000000) +
                             CURL_OFF_T_C(116444736000000000);
      FILETIME ft;
      ft.dwLowDateTime = (DWORD)(converted & 0xFFFFFFFF);
      ft.dwHighDateTime = (DWORD)(converted >> 32);
      if(!SetFileTime(hfile, NULL, &ft, &ft)) {
        fprintf(error_stream,
                "Failed to set filetime %ld on outfile: "
                "SetFileTime failed: GetLastError %u\n",
                filetime, GetLastError());
      }
      CloseHandle(hfile);
    }
    else {
      fprintf(error_stream,
              "Failed to set filetime %ld on outfile: "
              "CreateFile failed: GetLastError %u\n",
              filetime, GetLastError());
    }

#elif defined(HAVE_UTIMES)
    struct timeval times[2];
    times[0].tv_sec = times[1].tv_sec = filetime;
    times[0].tv_usec = times[1].tv_usec = 0;
    if(utimes(filename, times)) {
      fprintf(error_stream,
              "Failed to set filetime %ld on outfile: errno %d\n",
              filetime, errno);
    }

#elif defined(HAVE_UTIME)
    struct utimbuf times;
    times.actime = (time_t)filetime;
    times.modtime = (time_t)filetime;
    if(utime(filename, &times)) {
      fprintf(error_stream,
              "Failed to set filetime %ld on outfile: errno %d\n",
              filetime, errno);
    }
#endif
  }
}