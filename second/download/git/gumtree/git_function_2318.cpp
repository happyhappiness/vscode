nt cmd_clone(int argc, const char **argv, const char *prefix)
{
	int is_bundle = 0, is_local;
	struct stat buf;
	const char *repo_name, *repo, *work_tree, *git_dir;
	char *path, *dir;
	int dest_exists;
	const struct ref *refs, *remote_head;
	const struct ref *remote_head_points_at;
	const struct ref *our_head_points_at;
	struct ref *mapped_refs;
	const struct ref *ref;
	struct strbuf key = STRBUF_INIT, value = STRBUF_INIT;
	struct strbuf branch_top = STRBUF_INIT, reflog_msg = STRBUF_INIT;
	struct transport *transport = NULL;
	const char *src_ref_prefix = "refs/heads/";
	struct remote *remote;
	int err = 0, complete_refs_before_fetch = 1;

	struct refspec *refspec;
	const char *fetch_pattern;

	packet_trace_identity("clone");
	argc = parse_options(argc, argv, prefix, builtin_clone_options,
			     builtin_clone_usage, 0);

	if (argc > 2)
		usage_msg_opt(_("Too many arguments."),
			builtin_clone_usage, builtin_clone_options);

	if (argc == 0)
		usage_msg_opt(_("You must specify a repository to clone."),
			builtin_clone_usage, builtin_clone_options);

	if (option_single_branch == -1)
		option_single_branch = option_depth ? 1 : 0;

	if (option_mirror)
		option_bare = 1;

	if (option_bare) {
		if (option_origin)
			die(_("--bare and --origin %s options are incompatible."),
			    option_origin);
		if (real_git_dir)
			die(_("--bare and --separate-git-dir are incompatible."));
		option_no_checkout = 1;
	}

	if (!option_origin)
		option_origin = "origin";

	repo_name = argv[0];

	path = get_repo_path(repo_name, &is_bundle);
	if (path)
		repo = xstrdup(absolute_path(repo_name));
	else if (!strchr(repo_name, ':'))
		die(_("repository '%s' does not exist"), repo_name);
	else
		repo = repo_name;

	/* no need to be strict, transport_set_option() will validate it again */
	if (option_depth && atoi(option_depth) < 1)
		die(_("depth %s is not a positive number"), option_depth);

	if (argc == 2)
		dir = xstrdup(argv[1]);
	else
		dir = guess_dir_name(repo_name, is_bundle, option_bare);
	strip_trailing_slashes(dir);

	dest_exists = !stat(dir, &buf);
	if (dest_exists && !is_empty_dir(dir))
		die(_("destination path '%s' already exists and is not "
			"an empty directory."), dir);

	strbuf_addf(&reflog_msg, "clone: from %s", repo);

	if (option_bare)
		work_tree = NULL;
	else {
		work_tree = getenv("GIT_WORK_TREE");
		if (work_tree && !stat(work_tree, &buf))
			die(_("working tree '%s' already exists."), work_tree);
	}

	if (option_bare || work_tree)
		git_dir = xstrdup(dir);
	else {
		work_tree = dir;
		git_dir = mkpathdup("%s/.git", dir);
	}

	atexit(remove_junk);
	sigchain_push_common(remove_junk_on_signal);

	if (!option_bare) {
		if (safe_create_leading_directories_const(work_tree) < 0)
			die_errno(_("could not create leading directories of '%s'"),
				  work_tree);
		if (!dest_exists && mkdir(work_tree, 0777))
			die_errno(_("could not create work tree dir '%s'"),
				  work_tree);
		junk_work_tree = work_tree;
		set_git_work_tree(work_tree);
	}

	junk_git_dir = git_dir;
	if (safe_create_leading_directories_const(git_dir) < 0)
		die(_("could not create leading directories of '%s'"), git_dir);

	set_git_dir_init(git_dir, real_git_dir, 0);
	if (real_git_dir) {
		git_dir = real_git_dir;
		junk_git_dir = real_git_dir;
	}

	if (0 <= option_verbosity) {
		if (option_bare)
			fprintf(stderr, _("Cloning into bare repository '%s'...\n"), dir);
		else
			fprintf(stderr, _("Cloning into '%s'...\n"), dir);
	}
	init_db(option_template, INIT_DB_QUIET);
	write_config(&option_config);

	git_config(git_default_config, NULL);

	if (option_bare) {
		if (option_mirror)
			src_ref_prefix = "refs/";
		strbuf_addstr(&branch_top, src_ref_prefix);

		git_config_set("core.bare", "true");
	} else {
		strbuf_addf(&branch_top, "refs/remotes/%s/", option_origin);
	}

	strbuf_addf(&value, "+%s*:%s*", src_ref_prefix, branch_top.buf);
	strbuf_addf(&key, "remote.%s.url", option_origin);
	git_config_set(key.buf, repo);
	strbuf_reset(&key);

	if (option_reference.nr)
		setup_reference();
	else if (option_dissociate) {
		warning(_("--dissociate given, but there is no --reference"));
		option_dissociate = 0;
	}

	fetch_pattern = value.buf;
	refspec = parse_fetch_refspec(1, &fetch_pattern);

	strbuf_reset(&value);

	remote = remote_get(option_origin);
	transport = transport_get(remote, remote->url[0]);
	transport_set_verbosity(transport, option_verbosity, option_progress);

	path = get_repo_path(remote->url[0], &is_bundle);
	is_local = option_local != 0 && path && !is_bundle;
	if (is_local) {
		if (option_depth)
			warning(_("--depth is ignored in local clones; use file:// instead."));
		if (!access(mkpath("%s/shallow", path), F_OK)) {
			if (option_local > 0)
				warning(_("source repository is shallow, ignoring --local"));
			is_local = 0;
		}
	}
	if (option_local > 0 && !is_local)
		warning(_("--local is ignored"));
	transport->cloning = 1;

	if (!transport->get_refs_list || (!is_local && !transport->fetch))
		die(_("Don't know how to clone %s"), transport->url);

	transport_set_option(transport, TRANS_OPT_KEEP, "yes");

	if (option_depth)
		transport_set_option(transport, TRANS_OPT_DEPTH,
				     option_depth);
	if (option_single_branch)
		transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, "1");

	if (option_upload_pack)
		transport_set_option(transport, TRANS_OPT_UPLOADPACK,
				     option_upload_pack);

	if (transport->smart_options && !option_depth)
		transport->smart_options->check_self_contained_and_connected = 1;

	refs = transport_get_remote_refs(transport);

	if (refs) {
		mapped_refs = wanted_peer_refs(refs, refspec);
		/*
		 * transport_get_remote_refs() may return refs with null sha-1
		 * in mapped_refs (see struct transport->get_refs_list
		 * comment). In that case we need fetch it early because
		 * remote_head code below relies on it.
		 *
		 * for normal clones, transport_get_remote_refs() should
		 * return reliable ref set, we can delay cloning until after
		 * remote HEAD check.
		 */
		for (ref = refs; ref; ref = ref->next)
			if (is_null_sha1(ref->old_sha1)) {
				complete_refs_before_fetch = 0;
				break;
			}

		if (!is_local && !complete_refs_before_fetch)
			transport_fetch_refs(transport, mapped_refs);

		remote_head = find_ref_by_name(refs, "HEAD");
		remote_head_points_at =
			guess_remote_head(remote_head, mapped_refs, 0);

		if (option_branch) {
			our_head_points_at =
				find_remote_branch(mapped_refs, option_branch);

			if (!our_head_points_at)
				die(_("Remote branch %s not found in upstream %s"),
				    option_branch, option_origin);
		}
		else
			our_head_points_at = remote_head_points_at;
	}
	else {
		if (option_branch)
			die(_("Remote branch %s not found in upstream %s"),
					option_branch, option_origin);

		warning(_("You appear to have cloned an empty repository."));
		mapped_refs = NULL;
		our_head_points_at = NULL;
		remote_head_points_at = NULL;
		remote_head = NULL;
		option_no_checkout = 1;
		if (!option_bare)
			install_branch_config(0, "master", option_origin,
					      "refs/heads/master");
	}

	write_refspec_config(src_ref_prefix, our_head_points_at,
			remote_head_points_at, &branch_top);

	if (is_local)
		clone_local(path, git_dir);
	else if (refs && complete_refs_before_fetch)
		transport_fetch_refs(transport, mapped_refs);

	update_remote_refs(refs, mapped_refs, remote_head_points_at,
			   branch_top.buf, reflog_msg.buf, transport, !is_local);

	update_head(our_head_points_at, remote_head, reflog_msg.buf);

	transport_unlock_pack(transport);
	transport_disconnect(transport);

	if (option_dissociate) {
		close_all_packs();
		dissociate_from_references();
	}

	junk_mode = JUNK_LEAVE_REPO;
	err = checkout();

	strbuf_release(&reflog_msg);
	strbuf_release(&branch_top);
	strbuf_release(&key);
	strbuf_release(&value);
	junk_mode = JUNK_LEAVE_ALL;

	free(refspec);
	return err;
}