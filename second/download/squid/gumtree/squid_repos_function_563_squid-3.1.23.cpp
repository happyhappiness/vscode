DIR *
opendir (const char *path)
{
  char file_spec[LT_FILENAME_MAX];
  DIR *entry;

  assert (path != (char *) 0);
  if (lt_strlcpy (file_spec, path, sizeof file_spec) >= sizeof file_spec
      || lt_strlcat (file_spec, "\\", sizeof file_spec) >= sizeof file_spec)
    return (DIR *) 0;
  entry = (DIR *) malloc (sizeof(DIR));
  if (entry != (DIR *) 0)
    {
      entry->firsttime = TRUE;
      entry->hSearch = FindFirstFile (file_spec, &entry->Win32FindData);

      if (entry->hSearch == INVALID_HANDLE_VALUE)
	{
	  if (lt_strlcat (file_spec, "\\*.*", sizeof file_spec) < sizeof file_spec)
	    {
	      entry->hSearch = FindFirstFile (file_spec, &entry->Win32FindData);
	    }

	  if (entry->hSearch == INVALID_HANDLE_VALUE)
	    {
	      entry = (free (entry), (DIR *) 0);
	    }
	}
    }

  return entry;
}