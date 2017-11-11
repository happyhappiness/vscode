int
isdirectory(char *filename)
{
DWORD attr = GetFileAttributes(filename);
if (attr == INVALID_FILE_ATTRIBUTES)
  return 0;
return ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0) ? '/' : 0;
}