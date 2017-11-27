void module_register (void)
{
	match_proc_t mproc = { 0 };

	mproc.create  = mr_create;
	mproc.destroy = mr_destroy;
	mproc.match   = mr_match;
	fc_register_match ("regex", mproc);
}