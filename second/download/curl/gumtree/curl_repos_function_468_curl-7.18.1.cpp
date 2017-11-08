static bool rand_enough(void)
{
  return (bool)(0 != RAND_status());
}