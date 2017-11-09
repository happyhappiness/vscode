static int mutt_mkwrapdir (const char *path, char *newfile, size_t nflen, 
		    char *newdir, size_t ndlen)
{
  const char *basename;
  char parent[_POSIX_PATH_MAX];
  char *p;

  strfcpy (parent, NONULL (path), sizeof (parent));
  
  if ((p = strrchr (parent, '/')))
  {
    *p = '\0';
    basename = p + 1;
  }
  else
  {
    strfcpy (parent, ".", sizeof (parent));
    basename = path;
  }

  snprintf (newdir, ndlen, "%s/%s", parent, ".muttXXXXXX");
  if (mkdtemp(newdir) == NULL)
  {
      dprint(1, (debugfile, "mutt_mkwrapdir: mkdtemp() failed\n"));
      return -1;
  }
  
  if (snprintf (newfile, nflen, "%s/%s", newdir, NONULL(basename)) >= nflen)
  {
      rmdir(newdir);
      dprint(1, (debugfile, "mutt_mkwrapdir: string was truncated\n"));
      return -1;
  }
  return 0;  
}