	if (simple) {
		/* Additional safety */
		if (strcmp(branch->refname, branch->merge[0]->src))
			die_push_simple(branch, remote);
	}

	strbuf_addf(&refspec, "%s:%s", branch->refname, branch->merge[0]->src);
	add_refspec(refspec.buf);
}

static void setup_push_current(struct remote *remote, struct branch *branch)
{
	struct strbuf refspec = STRBUF_INIT;

	if (!branch)
		die(_(message_detached_head_die), remote->name);
	strbuf_addf(&refspec, "%s:%s", branch->refname, branch->refname);
	add_refspec(refspec.buf);
}

static int is_workflow_triangular(struct remote *remote)
{
	struct remote *fetch_remote = remote_get(NULL);
	return (fetch_remote && fetch_remote != remote);
