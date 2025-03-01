	if (delete_ref(ref, sha1, 0))
		return 1;
	printf("Deleted replace ref '%s'\n", name);
	return 0;
}

static int replace_object(const char *object_ref, const char *replace_ref,
			  int force)
{
	unsigned char object[20], prev[20], repl[20];
	enum object_type obj_type, repl_type;
	char ref[PATH_MAX];
	struct ref_lock *lock;

	if (get_sha1(object_ref, object))
		die("Failed to resolve '%s' as a valid ref.", object_ref);
	if (get_sha1(replace_ref, repl))
		die("Failed to resolve '%s' as a valid ref.", replace_ref);

	if (snprintf(ref, sizeof(ref),
		     "refs/replace/%s",
		     sha1_to_hex(object)) > sizeof(ref) - 1)
		die("replace ref name too long: %.*s...", 50, ref);
	if (check_refname_format(ref, 0))
		die("'%s' is not a valid ref name.", ref);

	obj_type = sha1_object_info(object, NULL);
	repl_type = sha1_object_info(repl, NULL);
	if (!force && obj_type != repl_type)
		die("Objects must be of the same type.\n"
		    "'%s' points to a replaced object of type '%s'\n"
		    "while '%s' points to a replacement object of type '%s'.",
		    object_ref, typename(obj_type),
		    replace_ref, typename(repl_type));

	if (read_ref(ref, prev))
		hashclr(prev);
	else if (!force)
		die("replace ref '%s' already exists", ref);

	lock = lock_any_ref_for_update(ref, prev, 0, NULL);
	if (!lock)
		die("%s: cannot lock the ref", ref);
	if (write_ref_sha1(lock, repl, NULL) < 0)
		die("%s: cannot update the ref", ref);

	return 0;
}

int cmd_replace(int argc, const char **argv, const char *prefix)
{
	int list = 0, delete = 0, force = 0;
	const char *format = NULL;
	struct option options[] = {
		OPT_BOOL('l', "list", &list, N_("list replace refs")),
		OPT_BOOL('d', "delete", &delete, N_("delete replace refs")),
		OPT_BOOL('f', "force", &force, N_("replace the ref if it exists")),
		OPT_STRING(0, "format", &format, N_("format"), N_("use this format")),
		OPT_END()
	};

	check_replace_refs = 0;

	argc = parse_options(argc, argv, prefix, options, git_replace_usage, 0);

	if (list && delete)
		usage_msg_opt("-l and -d cannot be used together",
			      git_replace_usage, options);

	if (format && delete)
		usage_msg_opt("--format and -d cannot be used together",
			      git_replace_usage, options);

	if (force && (list || delete))
		usage_msg_opt("-f cannot be used with -d or -l",
			      git_replace_usage, options);

	/* Delete refs */
	if (delete) {
		if (argc < 1)
			usage_msg_opt("-d needs at least one argument",
				      git_replace_usage, options);
		return for_each_replace_name(argv, delete_replace_ref);
	}

	/* Replace object */
	if (!list && argc) {
		if (argc != 2)
			usage_msg_opt("bad number of arguments",
				      git_replace_usage, options);
		if (format)
			usage_msg_opt("--format cannot be used when not listing",
				      git_replace_usage, options);
		return replace_object(argv[0], argv[1], force);
	}

	/* List refs, even if "list" is not set */
	if (argc > 1)
		usage_msg_opt("only one pattern can be given with -l",
			      git_replace_usage, options);
	if (force)
		usage_msg_opt("-f needs some arguments",
			      git_replace_usage, options);

	return list_replace_refs(argv[0], format);
}
