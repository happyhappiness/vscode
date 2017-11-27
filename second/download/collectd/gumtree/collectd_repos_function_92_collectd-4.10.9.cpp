static void *
loader_dump_callback (SList *item, void *userdata)
{
  const lt_dlvtable *vtable = (const lt_dlvtable *) item->userdata;
  fprintf (stderr, ", %s", (vtable && vtable->name) ? vtable->name : "(null)");
  return 0;
}