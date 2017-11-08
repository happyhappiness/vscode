static int elapsed(struct timeval *before,
                   struct timeval *after)
{
  ssize_t result;

  result = (after->tv_sec - before->tv_sec) * 1000000 +
    after->tv_usec - before->tv_usec;
  if (result < 0)
    result = 0;

  return curlx_sztosi(result);
}