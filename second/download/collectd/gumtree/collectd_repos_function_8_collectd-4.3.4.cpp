static struct dirent *readdir(entry)
  DIR *entry;
{
  int
    status;

  if (entry == (DIR *) 0)
    return((struct dirent *) 0);
  if (!entry->firsttime)
    {
      status = FindNextFile(entry->hSearch,&entry->Win32FindData);
      if (status == 0)
        return((struct dirent *) 0);
    }
  entry->firsttime = FALSE;
  (void) strncpy(entry->file_info.d_name,entry->Win32FindData.cFileName,
    LT_FILENAME_MAX-1);
  entry->file_info.d_name[LT_FILENAME_MAX - 1] = LT_EOS_CHAR;
  entry->file_info.d_namlen = strlen(entry->file_info.d_name);
  return(&entry->file_info);
}