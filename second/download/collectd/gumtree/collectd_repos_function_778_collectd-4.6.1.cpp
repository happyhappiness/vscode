void module_register (void)
{
  match_proc_t mproc;

  memset (&mproc, 0, sizeof (mproc));
  mproc.create  = mt_create;
  mproc.destroy = mt_destroy;
  mproc.match   = mt_match;
  fc_register_match ("value", mproc);
}