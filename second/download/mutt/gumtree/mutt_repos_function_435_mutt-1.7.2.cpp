static int test_new_folder (const char *path)
{
  FILE *f;
  int rc = 0;
  int typ;

  typ = mx_get_magic (path);

  if (typ != MUTT_MBOX && typ != MUTT_MMDF)
    return 0;

  if ((f = fopen (path, "rb")))
  {
    rc = test_last_status_new (f);
    safe_fclose (&f);
  }

  return rc;
}