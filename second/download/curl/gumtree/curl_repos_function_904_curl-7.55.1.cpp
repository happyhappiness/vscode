static int multiply(unsigned long *amount, long with)
{
  unsigned long sum = *amount * with;
  if(!with) {
    *amount = 0;
    return 0;
  }
  if(sum/with != *amount)
    return 1; /* didn't fit, bail out */
  *amount = sum;
  return 0;
}