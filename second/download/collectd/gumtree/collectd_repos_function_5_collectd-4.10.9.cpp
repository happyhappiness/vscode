void
closedir (DIR *entry)
{
  assert (entry != (DIR *) NULL);
  FindClose (entry->hSearch);
  free ((void *) entry);
}