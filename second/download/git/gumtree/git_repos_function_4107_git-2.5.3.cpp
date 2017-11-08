static void setup_push_current(struct remote *remote, struct branch *branch)
{
	if (!branch)
		die(_(message_detached_head_die), remote->name);
	add_refspec(branch->name);
}