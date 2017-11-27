void module_register (void)
{
	target_proc_t tproc = { 0 };

	tproc.create  = tr_create;
	tproc.destroy = tr_destroy;
	tproc.invoke  = tr_invoke;
	fc_register_target ("replace", tproc);
}