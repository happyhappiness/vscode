static void remsock(SockInfo *f)
{
  if (!f) { return; }
  if (f->ev) { g_source_remove(f->ev); }
  g_free(f);
}