		break;
	default:
		die(_("cannot use -a with -d"));
	}

	if (!force) {
		head_rev = lookup_commit_reference(head_oid.hash);
		if (!head_rev)
			die(_("Couldn't look up commit object for HEAD"));
	}
	for (i = 0; i < argc; i++, strbuf_release(&bname)) {
		char *target = NULL;
		int flags = 0;
