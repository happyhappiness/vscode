static bool rand_enough(int nread)
{
  /* this is a very silly decision to make */
  return (nread > 500) ? TRUE : FALSE;
}