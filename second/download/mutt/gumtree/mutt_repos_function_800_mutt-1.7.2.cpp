static int browser_compare_date (const void *a, const void *b)
{
  struct folder_file *pa = (struct folder_file *) a;
  struct folder_file *pb = (struct folder_file *) b;

  int r = pa->mtime - pb->mtime;

  return ((BrowserSort & SORT_REVERSE) ? -r : r);
}