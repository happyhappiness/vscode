static int md_cmp_path (struct maildir *a, struct maildir *b)
{
  return strcmp (a->h->path, b->h->path);
}