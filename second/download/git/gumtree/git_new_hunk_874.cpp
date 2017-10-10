		if (option_bare)
			fprintf(stderr, _("Cloning into bare repository '%s'...\n"), dir);
		else
			fprintf(stderr, _("Cloning into '%s'...\n"), dir);
	}

	if (option_recurse_submodules.nr > 0) {
		struct string_list_item *item;
		struct strbuf sb = STRBUF_INIT;

		/* remove duplicates */
		string_list_sort(&option_recurse_submodules);
		string_list_remove_duplicates(&option_recurse_submodules, 0);

		/*
		 * NEEDSWORK: In a multi-working-tree world, this needs to be
		 * set in the per-worktree config.
		 */
		for_each_string_list_item(item, &option_recurse_submodules) {
			strbuf_addf(&sb, "submodule.active=%s",
				    item->string);
			string_list_append(&option_config,
					   strbuf_detach(&sb, NULL));
		}

		if (option_required_reference.nr &&
		    option_optional_reference.nr)
			die(_("clone --recursive is not compatible with "
			      "both --reference and --reference-if-able"));
		else if (option_required_reference.nr) {
			string_list_append(&option_config,
