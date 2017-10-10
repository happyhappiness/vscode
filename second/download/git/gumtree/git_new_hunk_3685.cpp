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

