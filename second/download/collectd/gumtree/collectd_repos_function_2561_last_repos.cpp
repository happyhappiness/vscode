static char *sstrerror(int errnum, char *buf, size_t buflen) {
  buf[0] = 0;

#if !HAVE_STRERROR_R
  snprintf(buf, buflen, "Error #%i; strerror_r is not available.", errnum);
/* #endif !HAVE_STRERROR_R */

#elif STRERROR_R_CHAR_P
  {
    char *temp;
    temp = strerror_r(errnum, buf, buflen);
    if (buf[0] == 0) {
      if ((temp != NULL) && (temp != buf) && (temp[0] != 0))
        strncpy(buf, temp, buflen);
      else
        strncpy(buf, "strerror_r did not return "
                     "an error message",
                buflen);
    }
  }
/* #endif STRERROR_R_CHAR_P */

#else
  if (strerror_r(errnum, buf, buflen) != 0) {
    snprintf(buf, buflen, "Error #%i; "
                          "Additionally, strerror_r failed.",
             errnum);
  }
#endif /* STRERROR_R_CHAR_P */

  buf[buflen - 1] = 0;

  return buf;
}