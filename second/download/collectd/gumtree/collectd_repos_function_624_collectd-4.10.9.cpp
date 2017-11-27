static int fc_read (void)
{
  size_t i;

  for (i = 0; i < directories_num; i++)
    fc_read_dir (directories[i]);

  return (0);
}