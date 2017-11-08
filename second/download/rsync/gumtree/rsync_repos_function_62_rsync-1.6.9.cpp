static int hlink_compare(struct file_struct *f1,struct file_struct *f2)
{
  if (!S_ISREG(f1->mode) && !S_ISREG(f2->mode)) return 0;
  if (!S_ISREG(f1->mode)) return -1;
  if (!S_ISREG(f2->mode)) return 1;

  if (f1->dev != f2->dev) 
    return (f1->dev - f2->dev);

  if (f1->inode != f2->inode) 
    return (f1->inode - f2->inode);

  return file_compare(f1,f2);
}