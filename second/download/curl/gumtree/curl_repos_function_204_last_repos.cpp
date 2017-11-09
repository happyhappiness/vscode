static void remsock(SockInfo *f)
{
  if(f) {
    if(f->evset)
      event_free(f->ev);
    free(f);
  }
}