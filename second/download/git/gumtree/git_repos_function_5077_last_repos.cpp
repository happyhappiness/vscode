static void setup_push_current(struct remote *remote, struct branch *branch)
{
	struct strbuf refspec = STRBUF_INIT;

	if (!branch)
		die(_(message_detached_head_die), remote->name);
	strbuf_addf(&refspec, "%s:%s", branch->refname, branch->refname);
	add_refspec(refspec.buf);
}