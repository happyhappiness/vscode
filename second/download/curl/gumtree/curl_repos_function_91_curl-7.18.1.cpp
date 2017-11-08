static void remsock(SockInfo *f)
{
  if (!f) { return; }
  if (f->evset) { event_del(&f->ev); }
  free(f);
}