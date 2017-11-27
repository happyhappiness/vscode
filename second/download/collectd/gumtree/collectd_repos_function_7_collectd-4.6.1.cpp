static DIR*
opendir (path)
  const char *path;
{
  char file_specification[LT_FILENAME_MAX];
  DIR *entry;

  assert(path != (char *) NULL);
  /* allow space for: path + '\\' '\\' '*' '.' '*' + '\0' */
  (void) strncpy (file_specification, path, LT_FILENAME_MAX-6);
  file_specification[LT_FILENAME_MAX-6] = LT_EOS_CHAR;
  (void) strcat(file_specification,"\\");
  entry = LT_DLMALLOC (DIR,sizeof(DIR));
  if (entry != (DIR *) 0)
    {
      entry->firsttime = TRUE;
      entry->hSearch = FindFirstFile(file_specification,&entry->Win32FindData);
    }
  if (entry->hSearch == INVALID_HANDLE_VALUE)
    {
      (void) strcat(file_specification,"\\*.*");
      entry->hSearch = FindFirstFile(file_specification,&entry->Win32FindData);
      if (entry->hSearch == INVALID_HANDLE_VALUE)
        {
          LT_DLFREE (entry);
          return (DIR *) 0;
        }
    }
  return(entry);
}