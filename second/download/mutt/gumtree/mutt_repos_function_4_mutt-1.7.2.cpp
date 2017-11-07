static long double pow10 (int exp)
{
  long double result = 1;

  while (exp)
  {
    result *= 10;
    exp--;
  }
  
  return result;
}