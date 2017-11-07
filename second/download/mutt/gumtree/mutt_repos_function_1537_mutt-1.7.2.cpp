int mh_check_empty (const char *path)
{
  DIR *dp;
  struct dirent *de;
  int r = 1; /* assume empty until we find a message */
  
  if ((dp = opendir (path)) == NULL)
    return -1;
  while ((de = readdir (dp)))
  {
    if (mh_valid_message (de->d_name))
    {
      r = 0;
      break;
    }
  }
  closedir (dp);
  
  return r;
}