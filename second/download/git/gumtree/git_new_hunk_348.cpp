		if (!active_nr && read_cache() < 0)
			die(_("Cannot read index"));

		if (amend)
			parent = "HEAD^1";

		if (get_sha1(parent, sha1)) {
			int i, ita_nr = 0;

			for (i = 0; i < active_nr; i++)
				if (ce_intent_to_add(active_cache[i]))
					ita_nr++;
			commitable = active_nr - ita_nr > 0;
		} else {
			/*
			 * Unless the user did explicitly request a submodule
			 * ignore mode by passing a command line option we do
			 * not ignore any changed submodule SHA-1s when
			 * comparing index and parent, no matter what is
			 * configured. Otherwise we won't commit any
