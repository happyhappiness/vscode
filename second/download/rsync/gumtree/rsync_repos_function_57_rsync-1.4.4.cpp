void exit_cleanup(int code)
{
  if (cleanup_fname)
    unlink(cleanup_fname);
  exit(code);
}