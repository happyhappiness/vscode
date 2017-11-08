time_t Curl_tvdiff_us(struct curltime newer, struct curltime older)
{
  time_t diff = newer.tv_sec-older.tv_sec;
#if SIZEOF_TIME_T < 8
  /* for 32bit time_t systems */
  if(diff >= (0x7fffffff/1000000))
    return 0x7fffffff;
#else
  /* for 64bit time_t systems */
  if(diff >= (0x7fffffffffffffffLL/1000000))
    return 0x7fffffffffffffffLL;
#endif
  return (newer.tv_sec-older.tv_sec)*1000000+
    (int)(newer.tv_usec-older.tv_usec);
}