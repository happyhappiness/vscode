static int
file_not_found ()
{
  const char *error = 0;

  LT_DLMUTEX_GETERROR (error);
  if (error == LT_DLSTRERROR (FILE_NOT_FOUND))
    return 1;

  return 0;
}