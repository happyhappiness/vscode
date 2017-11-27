static int
find_file_callback (filename, data1, data2)
     char *filename;
     lt_ptr data1;
     lt_ptr data2;
{
  char	     **pdir	= (char **) data1;
  FILE	     **pfile	= (FILE **) data2;
  int	     is_done	= 0;

  assert (filename && *filename);
  assert (pdir);
  assert (pfile);

  if ((*pfile = fopen (filename, LT_READTEXT_MODE)))
    {
      char *dirend = strrchr (filename, '/');

      if (dirend > filename)
	*dirend   = LT_EOS_CHAR;

      LT_DLFREE (*pdir);
      *pdir   = lt_estrdup (filename);
      is_done = (*pdir == 0) ? -1 : 1;
    }

  return is_done;
}