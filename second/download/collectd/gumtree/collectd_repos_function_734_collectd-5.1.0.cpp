static int ethstat_read(void)
{
  size_t i;

  for (i = 0; i < interfaces_num; i++)
    ethstat_read_interface (interfaces[i]);

  return 0;
}