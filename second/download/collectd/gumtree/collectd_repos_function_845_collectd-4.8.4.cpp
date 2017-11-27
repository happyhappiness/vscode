void module_register (void)
{
  match_proc_t mproc;

  memset (&mproc, 0, sizeof (mproc));
  mproc.create  = mv_create;
  mproc.destroy = mv_destroy;
  mproc.match   = mv_match;
  fc_register_match ("value", mproc);
}