time_t curlx_tvdiff(struct curltime newer, struct curltime older)
{
#if SIZEOF_TIME_T < 8
  /* for 32bit time_t systems, add a precaution to avoid overflow for really
     big time differences */
  time_t diff = newer.tv_sec-older.tv_sec;
  if(diff >= (0x7fffffff/1000))
    return 0x7fffffff;
#endif
  return (newer.tv_sec-older.tv_sec)*1000+
    (int)(newer.tv_usec-older.tv_usec)/1000;
}