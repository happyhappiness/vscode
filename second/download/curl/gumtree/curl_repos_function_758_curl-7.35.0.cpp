CURLcode main_init(void)
{
#if defined(__DJGPP__) || defined(__GO32__)
  /* stop stat() wasting time */
  _djstat_flags |= _STAT_INODE | _STAT_EXEC_MAGIC | _STAT_DIRSIZE;
#endif

  return curl_global_init(CURL_GLOBAL_DEFAULT);
}