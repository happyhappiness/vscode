    *val = atoi(str);
  else
    retcode = 1; /* badness */
  return retcode;
}

/**
 * Parses the given string looking for an offset (which may be
 * a larger-than-integer value).
 *
 * @param val  the offset to populate
 * @param str  the buffer containing the offset
 * @return zero if successful, non-zero if failure.
 */
static int str2offset(curl_off_t *val, const char *str)
{
#if (CURL_SIZEOF_CURL_OFF_T > CURL_SIZEOF_LONG)
  *val = curlx_strtoofft(str, NULL, 0);
  if((*val == CURL_LLONG_MAX || *val == CURL_LLONG_MIN) && (ERRNO == ERANGE))
    return 1;
#else
  *val = strtol(str, NULL, 0);
  if ((*val == LONG_MIN || *val == LONG_MAX) && ERRNO == ERANGE)
    return 1;
#endif
