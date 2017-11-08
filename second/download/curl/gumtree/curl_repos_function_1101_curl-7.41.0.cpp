void curl_memlimit(long limit)
{
  if(!memlimit) {
    memlimit = TRUE;
    memsize = limit;
  }
}