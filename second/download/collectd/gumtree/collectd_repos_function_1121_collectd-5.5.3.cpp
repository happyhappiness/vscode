void module_register (void)
{
	target_proc_t tproc;

	memset (&tproc, 0, sizeof (tproc));
	tproc.create  = v5_create;
	tproc.destroy = v5_destroy;
	tproc.invoke  = v5_invoke;
	fc_register_target ("v5upgrade", tproc);
}