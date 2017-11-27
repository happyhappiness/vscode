void module_register (void)
{
  match_proc_t mproc;

  memset (&mproc, 0, sizeof (mproc));
  mproc.create  = mh_create;
  mproc.destroy = mh_destroy;
  mproc.match   = mh_match;
  fc_register_match ("hashed", mproc);
}