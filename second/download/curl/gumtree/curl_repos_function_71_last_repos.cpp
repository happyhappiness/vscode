static void remsock(SockInfo *f, GlobalInfo *g)
{
  printf("%s  \n", __PRETTY_FUNCTION__);
  if(f) {
    if(f->evset)
      ev_io_stop(g->loop, &f->ev);
    free(f);
  }
}