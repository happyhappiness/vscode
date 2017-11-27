void
lt_dlloader_dump (void)
{
  fprintf (stderr, "loaders: ");
  if (!loaders)
    {
      fprintf (stderr, "(empty)");
    }
  else
    {
      const lt_dlvtable *head = (const lt_dlvtable *) loaders->userdata;
      fprintf (stderr, "%s", (head && head->name) ? head->name : "(null)");
      if (slist_tail (loaders))
	slist_foreach (slist_tail (loaders), loader_dump_callback, NULL);
    }
  fprintf (stderr, "\n");
}