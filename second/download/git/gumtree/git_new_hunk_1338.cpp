		OPT_EXPIRY_DATE(0, "expire", &expire,
				N_("expire objects older than <time>")),
		OPT_END()
	};
	char *s;

	expire = TIME_MAX;
	save_commit_buffer = 0;
	check_replace_refs = 0;
	ref_paranoia = 1;
	init_revisions(&revs, prefix);

	argc = parse_options(argc, argv, prefix, options, prune_usage, 0);

	if (repository_format_precious_objects)
		die(_("cannot prune in a precious-objects repo"));

	while (argc--) {
		struct object_id oid;
		const char *name = *argv++;

		if (!get_oid(name, &oid)) {
			struct object *object = parse_object_or_die(&oid,
								    name);
			add_pending_object(&revs, object, "");
		}
		else
			die("unrecognized argument: %s", name);
	}

