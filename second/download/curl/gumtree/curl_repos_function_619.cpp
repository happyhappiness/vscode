static struct tftphdr *r_init(void)
{
  return rw_init(1); /* read-ahead */
}