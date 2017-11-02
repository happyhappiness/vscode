static struct tftphdr *w_init(void)
{
  return rw_init(0); /* write-behind */
}