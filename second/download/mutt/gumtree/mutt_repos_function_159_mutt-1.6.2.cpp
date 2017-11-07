int safe_fsync_close (FILE **f)
{
  int r = 0;

  if (*f)
  {
    if (fflush (*f) || fsync (fileno (*f)))
    {
      r = -1;
      safe_fclose (f);
    }
    else
      r = safe_fclose (f);
  }

  return r;
}