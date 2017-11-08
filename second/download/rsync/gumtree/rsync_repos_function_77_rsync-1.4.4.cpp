static int flist_compare(struct file_struct *f1,struct file_struct *f2)
{
  if (!f1->name && !f2->name) return 0;
  if (!f1->name) return -1;
  if (!f2->name) return 1;
  return strcmp(f1->name,f2->name);
}