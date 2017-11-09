static long double abs_val (long double value)
{
  long double result = value;

  if (value < 0)
    result = -value;

  return result;
}