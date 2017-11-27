void module_register (void)
{
	target_proc_t tproc;

	memset (&tproc, 0, sizeof (tproc));
	tproc.create  = tn_create;
	tproc.destroy = tn_destroy;
	tproc.invoke  = tn_invoke;
	fc_register_target ("notification", tproc);
}