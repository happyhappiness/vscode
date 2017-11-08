void sig_int(void)
{
  if (cleanup_fname)
    unlink(cleanup_fname);
  exit(1);
}