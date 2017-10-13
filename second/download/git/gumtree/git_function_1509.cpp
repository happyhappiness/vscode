int cmd_init_db(int argc, const char **argv, const char *prefix)
{
	const char *git_dir;
	const char *real_git_dir = NULL;
	const char *work_tree;
	const char *template_dir = NULL;
	unsigned int flags = 0;
	const struct option init_db_options[] = {
		OPT_STRING(0, "template", &template_dir, N_("template-directory"),
				N_("directory from which templates will be used")),
		OPT_SET_INT(0, "bare", &is_bare_repository_cfg,
				N_("create a bare repository"), 1),
		{ OPTION_CALLBACK, 0, "shared", &init_shared_repository,
			N_("permissions"),
			N_("specify that the git repository is to be shared amongst several users"),
			PARSE_OPT_OPTARG | PARSE_OPT_NONEG, shared_callback, 0},
		OPT_BIT('q', "quiet", &flags, N_("be quiet"), INIT_DB_QUIET),
		OPT_STRING(0, "separate-git-dir", &real_git_dir, N_("gitdir"),
			   N_("separate git dir from working tree")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, init_db_options, init_db_usage, 0);

	if (real_git_dir && !is_absolute_path(real_git_dir))
		real_git_dir = xstrdup(real_path(real_git_dir));

	if (argc == 1) {
		int mkdir_tried = 0;
	retry:
		if (chdir(argv[0]) < 0) {
			if (!mkdir_tried) {
				int saved;
				/*
				 * At this point we haven't read any configuration,
				 * and we know shared_repository should always be 0;
				 * but just in case we play safe.
				 */
				saved = shared_repository;
				shared_repository = 0;
				switch (safe_create_leading_directories_const(argv[0])) {
				case SCLD_OK:
				case SCLD_PERMS:
					break;
				case SCLD_EXISTS:
					errno = EEXIST;
					/* fallthru */
				default:
					die_errno(_("cannot mkdir %s"), argv[0]);
					break;
				}
				shared_repository = saved;
				if (mkdir(argv[0], 0777) < 0)
					die_errno(_("cannot mkdir %s"), argv[0]);
				mkdir_tried = 1;
				goto retry;
			}
			die_errno(_("cannot chdir to %s"), argv[0]);
		}
	} else if (0 < argc) {
		usage(init_db_usage[0]);
	}
	if (is_bare_repository_cfg == 1) {
		static char git_dir[PATH_MAX+1];

		setenv(GIT_DIR_ENVIRONMENT,
			getcwd(git_dir, sizeof(git_dir)), argc > 0);
	}

	if (init_shared_repository != -1)
		shared_repository = init_shared_repository;

	/*
	 * GIT_WORK_TREE makes sense only in conjunction with GIT_DIR
	 * without --bare.  Catch the error early.
	 */
	git_dir = getenv(GIT_DIR_ENVIRONMENT);
	work_tree = getenv(GIT_WORK_TREE_ENVIRONMENT);
	if ((!git_dir || is_bare_repository_cfg == 1) && work_tree)
		die(_("%s (or --work-tree=<directory>) not allowed without "
			  "specifying %s (or --git-dir=<directory>)"),
		    GIT_WORK_TREE_ENVIRONMENT,
		    GIT_DIR_ENVIRONMENT);

	/*
	 * Set up the default .git directory contents
	 */
	if (!git_dir)
		git_dir = DEFAULT_GIT_DIR_ENVIRONMENT;

	if (is_bare_repository_cfg < 0)
		is_bare_repository_cfg = guess_repository_type(git_dir);

	if (!is_bare_repository_cfg) {
		const char *git_dir_parent = strrchr(git_dir, '/');
		if (git_dir_parent) {
			char *rel = xstrndup(git_dir, git_dir_parent - git_dir);
			git_work_tree_cfg = xstrdup(real_path(rel));
			free(rel);
		}
		if (!git_work_tree_cfg) {
			git_work_tree_cfg = xcalloc(PATH_MAX, 1);
			if (!getcwd(git_work_tree_cfg, PATH_MAX))
				die_errno (_("Cannot access current working directory"));
		}
		if (work_tree)
			set_git_work_tree(real_path(work_tree));
		else
			set_git_work_tree(git_work_tree_cfg);
		if (access(get_git_work_tree(), X_OK))
			die_errno (_("Cannot access work tree '%s'"),
				   get_git_work_tree());
	}
	else {
		if (work_tree)
			set_git_work_tree(real_path(work_tree));
	}

	set_git_dir_init(git_dir, real_git_dir, 1);

	return init_db(template_dir, flags);
}