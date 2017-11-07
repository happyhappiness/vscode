int test_new_folder (const char *path)
{
  FILE *f;
  int rc = 0;
  int typ;

  typ = mx_get_magic (path);

  if (typ != M_MBOX && typ != M_MMDF && typ != M_KENDRA)
    return 0;

  if ((f = fopen (path, "rb")))
  {
    rc = test_last_status_new (f);
    fclose (f);
  }

  return rc;
}