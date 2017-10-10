		if (e->flags & UNINTERESTING)
			continue;

		if (dwim_ref(e->name, strlen(e->name), sha1, &full_name) != 1)
			continue;

		commit = get_commit(e, full_name);
		if (!commit) {
			warning("%s: Unexpected object of type %s, skipping.",
				e->name,
				typename(e->item->type));
			continue;
