static void close_file_descriptors(void)
{
  for(num_open.rlim_cur = 0;
      num_open.rlim_cur < num_open.rlim_max;
      num_open.rlim_cur++)
    if(fd[num_open.rlim_cur] > 0)
      close(fd[num_open.rlim_cur]);
  free(fd);
  fd = NULL;
}