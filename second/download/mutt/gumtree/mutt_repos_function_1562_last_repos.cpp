static int md_cmp_inode (struct maildir *a, struct maildir *b)
{
  return a->inode - b->inode;
}