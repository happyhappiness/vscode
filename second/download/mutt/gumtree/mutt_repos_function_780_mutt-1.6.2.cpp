static int browser_compare_subject (const void *a, const void *b)
{
  struct folder_file *pa = (struct folder_file *) a;
  struct folder_file *pb = (struct folder_file *) b;

  int r = mutt_strcoll (pa->name, pb->name);

  return ((BrowserSort & SORT_REVERSE) ? -r : r);
}