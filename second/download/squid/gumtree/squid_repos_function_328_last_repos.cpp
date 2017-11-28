static void *
loader_callback (SList *item, void *userdata)
{
  const lt_dlvtable *vtable = (const lt_dlvtable *) item->userdata;
  const char *	    name    = (const char *) userdata;

  assert (vtable);

  return STREQ (vtable->name, name) ? (void *) item : NULL;
}