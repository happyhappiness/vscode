int cmd_main(int argc, const char **argv)
{
	struct transfer_request *request;
	struct transfer_request *next_request;
	int nr_refspec = 0;
	const char **refspec = NULL;
	struct remote_lock *ref_lock = NULL;
	struct remote_lock *info_ref_lock = NULL;
	struct rev_info revs;
	int delete_branch = 0;
	int force_delete = 0;
	int objects_to_send;
	int rc = 0;
	int i;
	int new_refs;
	struct ref *ref, *local_refs;

	repo = xcalloc(1, sizeof(*repo));

	argv++;
	for (i = 1; i < argc; i++, argv++) {
		const char *arg = *argv;

		if (*arg == '-') {
			if (!strcmp(arg, "--all")) {
				push_all = MATCH_REFS_ALL;
				continue;
			}
			if (!strcmp(arg, "--force")) {
				force_all = 1;
				continue;
			}
			if (!strcmp(arg, "--dry-run")) {
				dry_run = 1;
				continue;
			}
			if (!strcmp(arg, "--helper-status")) {
				helper_status = 1;
				continue;
			}
			if (!strcmp(arg, "--verbose")) {
				push_verbosely = 1;
				http_is_verbose = 1;
				continue;
			}
			if (!strcmp(arg, "-d")) {
				delete_branch = 1;
				continue;
			}
			if (!strcmp(arg, "-D")) {
				delete_branch = 1;
				force_delete = 1;
				continue;
			}
			if (!strcmp(arg, "-h"))
				usage(http_push_usage);
		}
		if (!repo->url) {
			char *path = strstr(arg, "//");
			str_end_url_with_slash(arg, &repo->url);
			repo->path_len = strlen(repo->url);
			if (path) {
				repo->path = strchr(path+2, '/');
				if (repo->path)
					repo->path_len = strlen(repo->path);
			}
			continue;
		}
		refspec = argv;
		nr_refspec = argc - i;
		break;
	}

#ifndef USE_CURL_MULTI
	die("git-push is not available for http/https repository when not compiled with USE_CURL_MULTI");
#endif

	if (!repo->url)
		usage(http_push_usage);

	if (delete_branch && nr_refspec != 1)
		die("You must specify only one branch name when deleting a remote branch");

	setup_git_directory();

	memset(remote_dir_exists, -1, 256);

	http_init(NULL, repo->url, 1);

#ifdef USE_CURL_MULTI
	is_running_queue = 0;
#endif

	/* Verify DAV compliance/lock support */
	if (!locking_available()) {
		rc = 1;
		goto cleanup;
	}

	sigchain_push_common(remove_locks_on_signal);

	/* Check whether the remote has server info files */
	repo->can_update_info_refs = 0;
	repo->has_info_refs = remote_exists("info/refs");
	repo->has_info_packs = remote_exists("objects/info/packs");
	if (repo->has_info_refs) {
		info_ref_lock = lock_remote("info/refs", LOCK_TIME);
		if (info_ref_lock)
			repo->can_update_info_refs = 1;
		else {
			error("cannot lock existing info/refs");
			rc = 1;
			goto cleanup;
		}
	}
	if (repo->has_info_packs)
		fetch_indices();

	/* Get a list of all local and remote heads to validate refspecs */
	local_refs = get_local_heads();
	fprintf(stderr, "Fetching remote heads...\n");
	get_dav_remote_heads();
	run_request_queue();

	/* Remove a remote branch if -d or -D was specified */
	if (delete_branch) {
		if (delete_remote_branch(refspec[0], force_delete) == -1) {
			fprintf(stderr, "Unable to delete remote branch %s\n",
				refspec[0]);
			if (helper_status)
				printf("error %s cannot remove\n", refspec[0]);
		}
		goto cleanup;
	}

	/* match them up */
	if (match_push_refs(local_refs, &remote_refs,
			    nr_refspec, (const char **) refspec, push_all)) {
		rc = -1;
		goto cleanup;
	}
	if (!remote_refs) {
		fprintf(stderr, "No refs in common and none specified; doing nothing.\n");
		if (helper_status)
			printf("error null no match\n");
		rc = 0;
		goto cleanup;
	}

	new_refs = 0;
	for (ref = remote_refs; ref; ref = ref->next) {
		struct argv_array commit_argv = ARGV_ARRAY_INIT;

		if (!ref->peer_ref)
			continue;

		if (is_null_oid(&ref->peer_ref->new_oid)) {
			if (delete_remote_branch(ref->name, 1) == -1) {
				error("Could not remove %s", ref->name);
				if (helper_status)
					printf("error %s cannot remove\n", ref->name);
				rc = -4;
			}
			else if (helper_status)
				printf("ok %s\n", ref->name);
			new_refs++;
			continue;
		}

		if (!oidcmp(&ref->old_oid, &ref->peer_ref->new_oid)) {
			if (push_verbosely)
				fprintf(stderr, "'%s': up-to-date\n", ref->name);
			if (helper_status)
				printf("ok %s up to date\n", r