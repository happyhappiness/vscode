void module_register (void)
{
	match_proc_t mproc;

	memset (&mproc, 0, sizeof (mproc));
	mproc.create  = mr_create;
	mproc.destroy = mr_destroy;
	mproc.match   = mr_match;
	fc_register_match ("regex", mproc);
}