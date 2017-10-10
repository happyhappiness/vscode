	if (triangular)
		die(_("You are pushing to remote '%s', which is not the upstream of\n"
		      "your current branch '%s', without telling me what to push\n"
		      "to update which remote branch."),
		    remote->name, branch->name);

	if (push_default == PUSH_DEFAULT_SIMPLE) {
		/* Additional safety */
		if (strcmp(branch->refname, branch->merge[0]->src))
			die_push_simple(branch, remote);
	}

	strbuf_addf(&refspec, "%s:%s", branch->name, branch->merge[0]->src);
