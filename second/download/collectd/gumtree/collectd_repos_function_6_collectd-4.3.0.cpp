static void
closedir(entry)
  DIR *entry;
{
  assert(entry != (DIR *) NULL);
  FindClose(entry->hSearch);
  lt_dlfree((lt_ptr)entry);
}