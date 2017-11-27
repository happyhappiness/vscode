static int fc_read(void) {
  for (size_t i = 0; i < directories_num; i++)
    fc_read_dir(directories[i]);

  return (0);
}