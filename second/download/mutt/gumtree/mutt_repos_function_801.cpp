static int browser_compare_size (const void *a, const void *b)
{
  struct folder_file *pa = (struct folder_file *) a;
  struct folder_file *pb = (struct folder_file *) b;

  int r = pa->size - pb->size;

  return ((BrowserSort & SORT_REVERSE) ? -r : r);
}