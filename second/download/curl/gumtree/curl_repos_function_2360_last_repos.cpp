static bool rand_enough(void)
{
  return (0 != RAND_status()) ? TRUE : FALSE;
}