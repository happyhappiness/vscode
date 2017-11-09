int cmd_rev_parse(int argc, const char **argv, const char *prefix)
{
	int i, as_is = 0, verify = 0, quiet = 0, revs_count = 0, type = 0;
	int did_repo_setup = 0;
	int has_dashdash = 0;
	int output_prefix = 0;
	struct object_id oid;
	unsigned int flags = 0;
	const char *name = NULL;
	struct object_context unused;
	struct strbuf buf = STRBUF_INIT;

	if (argc > 1 && !strcmp("--parseopt", argv[1]))
		return cmd_parseopt(argc - 1, argv + 1, prefix);

	if (argc > 1 && !strcmp("--sq-quote", argv[1]))
		return cmd_sq_quote(argc - 2, argv + 2);

	if (argc > 1 && !strcmp("-h", argv[1]))
		usage(builtin_rev_parse_usage);

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--")) {
			has_dashdash = 1;
			break;
		}
	}

	/* No options; just report on whether we're in a git repo or not. */
	if (argc == 1) {
		setup_git_directory();
		git_config(git_default_config, NULL);
		return 0;
	}

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];

		if (!strcmp(arg, "--local-env-vars")) {
			int i;
			for (i = 0; local_repo_env[i]; i++)
				printf("%s\n", local_repo_env[i]);
			continue;
		}
		if (!strcmp(arg, "--resolve-git-dir")) {
			const char *gitdir = argv[++i];
			if (!gitdir)
				die("--resolve-git-dir requires an argument");
			gitdir = resolve_gitdir(gitdir);
			if (!gitdir)
				die("not a gitdir '%s'", argv[i]);
			puts(gitdir);
			continue;
		}

		/* The rest of the options require a git repository. */
		if (!did_repo_setup) {
			prefix = setup_git_directory();
			git_config(git_default_config, NULL);
			did_repo_setup = 1;
		}

		if (!strcmp(arg, "--git-path")) {
			if (!argv[i + 1])
				die("--git-path requires an argument");
			strbuf_reset(&buf);
			puts(relative_path(git_path("%s", argv[i + 1]),
					   prefix, &buf));
			i++;
			continue;
		}
		if (as_is) {
			if (show_file(arg, output_prefix) && as_is < 2)
				verify_filename(prefix, arg, 0);
			continue;
		}
		if (!strcmp(arg,"-n")) {
			if (++i >= argc)
				die("-n requires an argument");
			if ((filter & DO_FLAGS) && (filter & DO_REVS)) {
				show(arg);
				show(argv[i]);
			}
			continue;
		}
		if (starts_with(arg, "-n")) {
			if ((filter & DO_FLAGS) && (filter & DO_REVS))
				show(arg);
			continue;
		}

		if (*arg == '-') {
			if (!strcmp(arg, "--")) {
				as_is = 2;
				/* Pass on the "--" if we show anything but files.. */
				if (filter & (DO_FLAGS | DO_REVS))
					show_file(arg, 0);
				continue;
			}
			if (!strcmp(arg, "--default")) {
				def = argv[++i];
				if (!def)
					die("--default requires an argument");
				continue;
			}
			if (!strcmp(arg, "--prefix")) {
				prefix = argv[++i];
				if (!prefix)
					die("--prefix requires an argument");
				startup_info->prefix = prefix;
				output_prefix = 1;
				continue;
			}
			if (!strcmp(arg, "--revs-only")) {
				filter &= ~DO_NOREV;
				continue;
			}
			if (!strcmp(arg, "--no-revs")) {
				filter &= ~DO_REVS;
				continue;
			}
			if (!strcmp(arg, "--flags")) {
				filter &= ~DO_NONFLAGS;
				continue;
			}
			if (!strcmp(arg, "--no-flags")) {
				filter &= ~DO_FLAGS;
				continue;
			}
			if (!strcmp(arg, "--verify")) {
				filter &= ~(DO_FLAGS|DO_NOREV);
				verify = 1;
				continue;
			}
			if (!strcmp(arg, "--quiet") || !strcmp(arg, "-q")) {
				quiet = 1;
				flags |= GET_SHA1_QUIETLY;
				continue;
			}
			if (opt_with_value(arg, "--short", &arg)) {
				filter &= ~(DO_FLAGS|DO_NOREV);
				verify = 1;
				abbrev = DEFAULT_ABBREV;
				if (!arg)
					continue;
				abbrev = strtoul(arg, NULL, 10);
				if (abbrev < MINIMUM_ABBREV)
					abbrev = MINIMUM_ABBREV;
				else if (40 <= abbrev)
					abbrev = 40;
				continue;
			}
			if (!strcmp(arg, "--sq")) {
				output_sq = 1;
				continue;
			}
			if (!strcmp(arg, "--not")) {
				show_type ^= REVERSED;
				continue;
			}
			if (!strcmp(arg, "--symbolic")) {
				symbolic = SHOW_SYMBOLIC_ASIS;
				continue;
			}
			if (!strcmp(arg, "--symbolic-full-name")) {
				symbolic = SHOW_SYMBOLIC_FULL;
				continue;
			}
			if (opt_with_value(arg, "--abbrev-ref", &arg)) {
				abbrev_ref = 1;
				abbrev_ref_strict = warn_ambiguous_refs;
				if (arg) {
					if (!strcmp(arg, "strict"))
						abbrev_ref_strict = 1;
					else if (!strcmp(arg, "loose"))
						abbrev_ref_strict = 0;
					else
						die("unknown mode for --abbrev-ref: %s",
						    arg);
				}
				continue;
			}
			if (!strcmp(arg, "--all")) {
				for_each_ref(show_reference, NULL);
				continue;
			}
			if (skip_prefix(arg, "--disambiguate=", &arg)) {
				for_each_abbrev(arg, show_abbrev, NULL);
				continue;
			}
			if (!strcmp(arg, "--bisect")) {
				for_each_ref_in("refs/bisect/bad", show_reference, NULL);
				for_each_ref_in("refs/bisect/good", anti_reference, NULL);
				continue;
			}
			if (opt_with_value(arg, "--branches", &arg)) {
				handle_ref_opt(arg, "refs/heads/");
				continue;
			}
			if (opt_with_value(arg, "--tags", &arg)) {
				handle_ref_opt(arg, "refs/tags/");
				continue;
			}
			if (skip_prefix(arg, "--glob=", &arg)) {
				handle_ref_opt(arg, NULL);
				continue;
			}
			if (opt_with_value(arg, "--remotes", &arg)) {
				handle_ref_opt(arg, "refs/remotes/");
				continue;
			}
			if (skip_prefix(arg, "--exclude=", &arg)) {
				add_ref_exclusion(&ref_excludes, arg);
				continue;
			}
			if (!strcmp(arg, "--show-toplevel")) {
				const char *work_tree = get_git_work_tree();
				if (work_tree)
					puts(work_tree);
				continue;
			}
			if (!strcmp(arg, "--show-superproject-working-tree")) {
				const char *superproject = get_superproject_working_tree();
				if (superproject)
					puts(superproject);
				continue;
			}
			if (!strcmp(arg, "--show-prefix")) {
				if (prefix)
					puts(prefix);
				else
					putchar('\n');
				continue;
			}
			if (!strcmp(arg, "--show-cdup")) {
				const char *pfx = prefix;
				if (!is_inside_work_tree()) {
					const char *work_tree =
						get_git_work_tree();
					if (work_tree)
						printf("%s\n", work_tree);
					continue;
				}
				while (pfx) {
					pfx = strchr(pfx, '/');
					if (pfx) {
						pfx++;
						printf("../");
					}
				}
				putchar('\n');
				continue;
			}
			if (!strcmp(arg, "--git-dir") ||
			    !strcmp(arg, "--absolute-git-dir")) {
				const char *gitdir = getenv(GIT_DIR_ENVIRONMENT);
				char *cwd;
				int len;
				if (arg[2] == 'g') {	/* --git-dir */
					if (gitdir) {
						puts(gitdir);
						continue;
					}
					if (!prefix) {
						puts(".git");
						continue;
					}
				} else {		/* --absolute-git-dir */
					if (!gitdir && !prefix)
						gitdir = ".git";
					if (gitdir) {
						puts(real_path(gitdir));
						continue;
					}
				}
				cwd = xgetcwd();
				len = strlen(cwd);
				printf("%s%s.git\n", cwd, len && cwd[len-1] != '/' ? "/" : "");
				free(cwd);
				continue;
			}
			if (!strcmp(arg, "--git-common-dir")) {
				strbuf_reset(&buf);
				puts(relative_path(get_git_common_dir(),
						   prefix, &buf));
				continue;
			}
			if (!strcmp(arg, "--is-inside-git-dir")) {
				printf("%s\n", is_inside_git_dir() ? "true"
						: "false");
				continue;
			}
			if (!strcmp(arg, "--is-inside-work-tree")) {
				printf("%s\n", is_inside_work_tree() ? "true"
						: "false");
				continue;
			}
			if (!strcmp(arg, "--is-bare-repository")) {
				printf("%s\n", is_bare_repository() ? "true"
						: "false");
				continue;
			}
			if (!strcmp(arg, "--shared-index-path")) {
				if (read_cache() < 0)
					die(_("Could not read the index"));
				if (the_index.split_index) {
					const unsigned char *sha1 = the_index.split_index->base_sha1;
					const char *path = git_path("sharedindex.%s", sha1_to_hex(sha1));
					strbuf_reset(&buf);
					puts(relative_path(path, prefix, &buf));
				}
				continue;
			}
			if (skip_prefix(arg, "--since=", &arg)) {
				show_datestring("--max-age=", arg);
				continue;
			}
			if (skip_prefix(arg, "--after=", &arg)) {
				show_datestring("--max-age=", arg);
				continue;
			}
			if (skip_prefix(arg, "--before=", &arg)) {
				show_datestring("--min-age=", arg);
				continue;
			}
			if (skip_prefix(arg, "--until=", &arg)) {
				show_datestring("--min-age=", arg);
				continue;
			}
			if (show_flag(arg) && verify)
				die_no_single_rev(quiet);
			continue;
		}

		/* Not a flag argument */
		if (try_difference(arg))
			continue;
		if (try_parent_shorthands(arg))
			continue;
		name = arg;
		type = NORMAL;
		if (*arg == '^') {
			name++;
			type = REVERSED;
		}
		if (!get_sha1_with_context(name, flags, oid.hash, &unused)) {
			if (verify)
				revs_count++;
			else
				show_rev(type, &oid, name);
			continue;
		}
		if (verify)
			die_no_single_rev(quiet);
		if (has_dashdash)
			die("bad revision '%s'", arg);
		as_is = 1;
		if (!show_file(arg, output_prefix))
			continue;
		verify_filename(prefix, arg, 1);
	}
	strbuf_release(&buf);
	if (verify) {
		if (revs_count == 1) {
			show_rev(type, &oid, name);
			return 0;
		} else if (revs_count == 0 && show_default())
			return 0;
		die_no_single_rev(quiet);
	} else
		show_default();
	return 0;
}