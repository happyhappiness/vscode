static int hnd2num(CURL *hnd)
{
  int i;
  for(i = 0; i< num_transfers; i++) {
    if(curl_hnd[i] == hnd)
      return i;
  }
  return 0; /* weird, but just a fail-safe */
}