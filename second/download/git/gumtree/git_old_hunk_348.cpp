		if (!active_nr && read_cache() < 0)
			die(_("Cannot read index"));

		if (amend)
			parent = "HEAD^1";

		if (get_sha1(parent, sha1))
			commitable = !!active_nr;
		else {
			/*
			 * Unless the user did explicitly request a submodule
			 * ignore mode by passing a command line option we do
			 * not ignore any changed submodule SHA-1s when
			 * comparing index and parent, no matter what is
			 * configured. Otherwise we won't commit any
