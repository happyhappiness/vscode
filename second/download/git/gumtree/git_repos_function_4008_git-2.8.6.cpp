void init_display_notes(struct display_notes_opt *opt)
{
	char *display_ref_env;
	int load_config_refs = 0;
	display_notes_refs.strdup_strings = 1;

	assert(!display_notes_trees);

	if (!opt || opt->use_default_notes > 0 ||
	    (opt->use_default_notes == -1 && !opt->extra_notes_refs.nr)) {
		string_list_append(&display_notes_refs, default_notes_ref());
		display_ref_env = getenv(GIT_NOTES_DISPLAY_REF_ENVIRONMENT);
		if (display_ref_env) {
			string_list_add_refs_from_colon_sep(&display_notes_refs,
							    display_ref_env);
			load_config_refs = 0;
		} else
			load_config_refs = 1;
	}

	git_config(notes_display_config, &load_config_refs);

	if (opt) {
		struct string_list_item *item;
		for_each_string_list_item(item, &opt->extra_notes_refs)
			string_list_add_refs_by_glob(&display_notes_refs,
						     item->string);
	}

	display_notes_trees = load_notes_trees(&display_notes_refs, 0);
	string_list_clear(&display_notes_refs, 0);
}