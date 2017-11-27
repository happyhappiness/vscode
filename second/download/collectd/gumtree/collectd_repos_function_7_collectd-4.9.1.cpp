struct dirent *
readdir (DIR *entry)
{
  int status;

  if (entry == (DIR *) 0)
    return (struct dirent *) 0;

  if (!entry->firsttime)
    {
      status = FindNextFile (entry->hSearch, &entry->Win32FindData);
      if (status == 0)
        return (struct dirent *) 0;
    }

  entry->firsttime = FALSE;
  if (lt_strlcpy (entry->file_info.d_name, entry->Win32FindData.cFileName,
	sizeof entry->file_info.d_name) >= sizeof entry->file_info.d_name)
    return (struct dirent *) 0;
  entry->file_info.d_namlen = strlen (entry->file_info.d_name);

  return &entry->file_info;
}