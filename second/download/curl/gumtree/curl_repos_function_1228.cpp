static char *formboundary(struct SessionHandle *data)
{
  /* 24 dashes and 16 hexadecimal digits makes 64 bit (18446744073709551615)
     combinations */
  return aprintf("------------------------%08x%08x",
                 Curl_rand(data), Curl_rand(data));
}