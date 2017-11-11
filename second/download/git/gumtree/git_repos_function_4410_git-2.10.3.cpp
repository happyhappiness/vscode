static int do_push(const char *repo, int flags,
		   const struct string_list *push_options)
{
	int i, errs;
	struct remote *remote = pushremote_get(repo);
	const char **url;
	int url_nr;

	if (!remote) {
		if (repo)
			die(_("bad repository '%s'"), repo);
		die(_("No configured push destination.\n"
		    "Either specify the URL from the command-line or configure a remote repository using\n"
		    "\n"
		    "    git remote add <name> <url>\n"
		    "\n"
		    "and then push using the remote name\n"
		    "\n"
		    "    git push <name>\n"));
	}

	if (remote->mirror)
		flags |= (TRANSPORT_PUSH_MIRROR|TRANSPORT_PUSH_FORCE);

	if (push_options->nr)
		flags |= TRANSPORT_PUSH_OPTIONS;

	if ((flags & TRANSPORT_PUSH_ALL) && refspec) {
		if (!strcmp(*refspec, "refs/tags/*"))
			return error(_("--all and --tags are incompatible"));
		return error(_("--all can't be combined with refspecs"));
	}

	if ((flags & TRANSPORT_PUSH_MIRROR) && refspec) {
		if (!strcmp(*refspec, "refs/tags/*"))
			return error(_("--mirror and --tags are incompatible"));
		return error(_("--mirror can't be combined with refspecs"));
	}

	if ((flags & (TRANSPORT_PUSH_ALL|TRANSPORT_PUSH_MIRROR)) ==
				(TRANSPORT_PUSH_ALL|TRANSPORT_PUSH_MIRROR)) {
		return error(_("--all and --mirror are incompatible"));
	}

	if (!refspec && !(flags & TRANSPORT_PUSH_ALL)) {
		if (remote->push_refspec_nr) {
			refspec = remote->push_refspec;
			refspec_nr = remote->push_refspec_nr;
		} else if (!(flags & TRANSPORT_PUSH_MIRROR))
			setup_default_push_refspecs(remote);
	}
	errs = 0;
	url_nr = push_url_of_remote(remote, &url);
	if (url_nr) {
		for (i = 0; i < url_nr; i++) {
			struct transport *transport =
				transport_get(remote, url[i]);
			if (flags & TRANSPORT_PUSH_OPTIONS)
				transport->push_options = push_options;
			if (push_with_options(transport, flags))
				errs++;
		}
	} else {
		struct transport *transport =
			transport_get(remote, NULL);
		if (flags & TRANSPORT_PUSH_OPTIONS)
			transport->push_options = push_options;
		if (push_with_options(transport, flags))
			errs++;
	}
	return !!errs;
}