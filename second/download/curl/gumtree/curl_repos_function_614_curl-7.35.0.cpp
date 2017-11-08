char *test2file(long testno)
{
  static char filename[256];
  snprintf(filename, sizeof(filename), TEST_DATA_PATH, path, testno);
  return filename;
}