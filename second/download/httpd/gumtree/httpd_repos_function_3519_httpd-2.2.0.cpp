static char *
readdirectory(directory_type *dir)
{
for (;;)
  {
  struct dirent *dent = readdir(dir);
  if (dent == NULL) return NULL;
  if (strcmp(dent->d_name, ".") != 0 && strcmp(dent->d_name, "..") != 0)
    return dent->d_name;
  }
return NULL;   /* Keep compiler happy; never executed */
}