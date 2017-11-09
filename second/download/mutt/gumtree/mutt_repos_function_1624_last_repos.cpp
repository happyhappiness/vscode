static int
get_size (const char *path)
{
  if (!path)
    return 0;

  struct stat sb;
  if (stat (path, &sb) != 0)
    return 0;

  return sb.st_size;
}