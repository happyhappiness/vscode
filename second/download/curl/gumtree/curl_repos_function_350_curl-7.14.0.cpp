double curlx_tvdiff_secs(struct timeval newer, struct timeval older)
{
  return (double)(newer.tv_sec-older.tv_sec)+
    (double)(newer.tv_usec-older.tv_usec)/1000000.0;
}