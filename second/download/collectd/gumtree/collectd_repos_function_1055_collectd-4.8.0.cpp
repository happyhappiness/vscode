void module_register (void)
{
  match_proc_t mproc;

  memset (&mproc, 0, sizeof (mproc));
  mproc.create  = mec_create;
  mproc.destroy = mec_destroy;
  mproc.match   = mec_match;
  fc_register_match ("empty_counter", mproc);
}