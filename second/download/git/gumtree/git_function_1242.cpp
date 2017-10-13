int cmd_commit(int argc, const char **argv, const char *prefix)
{
	static struct wt_status s;
	static struct option builtin_commit_options[] = {
		OPT__QUIET(&quiet, N_("suppress summary after successful commit")),
		OPT__VERBOSE(&verbose, N_("show diff in commit message template")),

		OPT_GROUP(N_("Commit message options")),
		OPT_FILENAME('F', "file", &logfile, N_("read message from file")),
		OPT_STRING(0, "author", &force_author, N_("author"), N_("override author for commit")),
		OPT_STRING(0, "date", &force_date, N_("date"), N_("override date for commit")),
		OPT_CALLBACK('m', "message", &message, N_("message"), N_("commit message"), opt_parse_m),
		OPT_STRING('c', "reedit-message", &edit_message, N_("commit"), N_("reuse and edit message from specified commit")),
		OPT_STRING('C', "reuse-message", &use_message, N_("commit"), N_("reuse message from specified commit")),
		OPT_STRING(0, "fixup", &fixup_message, N_("commit"), N_("use autosquash formatted message to fixup specified commit")),
		OPT_STRING(0, "squash", &squash_message, N_("commit"), N_("use autosquash formatted message to squash specified commit")),
		OPT_BOOL(0, "reset-author", &renew_authorship, N_("the commit is authored by me now (used with -C/-c/--amend)")),
		OPT_BOOL('s', "signoff", &signoff, N_("add Signed-off-by:")),
		OPT_FILENAME('t', "template", &template_file, N_("use specified template file")),
		OPT_BOOL('e', "edit", &edit_flag, N_("force edit of commit")),
		OPT_STRING(0, "cleanup", &cleanup_arg, N_("default"), N_("how to strip spaces and #comments from message")),
		OPT_BOOL(0, "status", &include_status, N_("include status in commit message template")),
		{ OPTION_STRING, 'S', "gpg-sign", &sign_commit, N_("key-id"),
		  N_("GPG sign commit"), PARSE_OPT_OPTARG, NULL, (intptr_t) "" },
		/* end commit message options */

		OPT_GROUP(N_("Commit contents options")),
		OPT_BOOL('a', "all", &all, N_("commit all changed files")),
		OPT_BOOL('i', "include", &also, N_("add specified files to index for commit")),
		OPT_BOOL(0, "interactive", &interactive, N_("interactively add files")),
		OPT_BOOL('p', "patch", &patch_interactive, N_("interactively add changes")),
		OPT_BOOL('o', "only", &only, N_("commit only specified files")),
		OPT_BOOL('n', "no-verify", &no_verify, N_("bypass pre-commit and commit-msg hooks")),
		OPT_BOOL(0, "dry-run", &dry_run, N_("show what would be committed")),
		OPT_SET_INT(0, "short", &status_format, N_("show status concisely"),
			    STATUS_FORMAT_SHORT),
		OPT_BOOL(0, "branch", &s.show_branch, N_("show branch information")),
		OPT_SET_INT(0, "porcelain", &status_format,
			    N_("machine-readable output"), STATUS_FORMAT_PORCELAIN),
		OPT_SET_INT(0, "long", &status_format,
			    N_("show status in long format (default)"),
			    STATUS_FORMAT_LONG),
		OPT_BOOL('z', "null", &s.null_termination,
			 N_("terminate entries with NUL")),
		OPT_BOOL(0, "amend", &amend, N_("amend previous commit")),
		OPT_BOOL(0, "no-post-rewrite", &no_post_rewrite, N_("bypass post-rewrite hook")),
		{ OPTION_STRING, 'u', "untracked-files", &untracked_files_arg, N_("mode"), N_("show untracked files, optional modes: all, normal, no. (Default: all)"), PARSE_OPT_OPTARG, NULL, (intptr_t)"all" },
		/* end commit contents options */

		OPT_HIDDEN_BOOL(0, "allow-empty", &allow_empty,
				N_("ok to record an empty change")),
		OPT_HIDDEN_BOOL(0, "allow-empty-message", &allow_empty_message,
				N_("ok to record a change with an empty message")),

		OPT_END()
	};

	struct strbuf sb = STRBUF_INIT;
	struct strbuf author_ident = STRBUF_INIT;
	const char *index_file, *reflog_msg;
	char *nl;
	struct object_id oid;
	struct commit_list *parents = NULL;
	struct stat statbuf;
	struct commit *current_head = NULL;
	struct commit_extra_header *extra = NULL;
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_commit_usage, builtin_commit_options);

	status_init_config(&s, git_commit_config);
	status_format = STATUS_FORMAT_NONE; /* Ignore status.short */
	s.colopts = 0;

	if (get_sha1("HEAD", oid.hash))
		current_head = NULL;
	else {
		current_head = lookup_commit_or_die(oid.hash, "HEAD");
		if (parse_commit(current_head))
			die(_("could not parse HEAD commit"));
	}
	verbose = -1; /* unspecified */
	argc = parse_and_validate_options(argc, argv, builtin_commit_options,
					  builtin_commit_usage,
					  prefix, current_head, &s);
	if (verbose == -1)
		verbose = (config_commit_verbose < 0) ? 0 : config_commit_verbose;

	if (dry_run)
		return dry_run_commit(argc, argv, prefix, current_head, &s);
	index_file = prepare_index(argc, argv, prefix, current_head, 0);

	/* Set up everything for writing the commit object.  This includes
	   running hooks, writing the trees, and interacting with the user.  */
	if (!prepare_to_commit(index_file, prefix,
			       current_head, &s, &author_ident)) {
		rollback_index_files();
		return 1;
	}

	/* Determine parents */
	reflog_msg = getenv("GIT_REFLOG_ACTION");
	if (!current_head) {
		if (!reflog_msg)
			reflog_msg = "commit (initial)";
	} else if (amend) {
		if (!reflog_msg)
			reflog_msg = "commit (amend)";
		parents = copy_commit_list(current_head->parents);
	} else if (whence == FROM_MERGE) {
		struct strbuf m = STRBUF_INIT;
		FILE *fp;
		int allow_fast_forward = 1;
		struct commit_list **pptr = &parents;

		if (!reflog_msg)
			reflog_msg = "commit (merge)";
		pptr = commit_list_append(current_head, pptr);
		fp = fopen(git_path_merge_head(), "r");
		if (fp == NULL)
			die_errno(_("could not open '%s' for reading"),
				  git_path_merge_head());
		while (strbuf_getline_lf(&m, fp) != EOF) {
			struct commit *parent;

			parent = get_merge_parent(m.buf);
			if (!parent)
				die(_("Corrupt MERGE_HEAD file (%s)"), m.buf);
			pptr = commit_list_append(parent, pptr);
		}
		fclose(fp);
		strbuf_release(&m);
		if (!stat(git_path_merge_mode(), &statbuf)) {
			if (strbuf_read_file(&sb, git_path_merge_mode(), 0) < 0)
				die_errno(_("could not read MERGE_MODE"));
			if (!strcmp(sb.buf, "no-ff"))
				allow_fast_forward = 0;
		}
		if (allow_fast_forward)
			parents = reduce_heads(parents);
	} else {
		if (!reflog_msg)
			reflog_msg = (whence == FROM_CHERRY_PICK)
					? "commit (cherry-pick)"
					: "commit";
		commit_list_insert(current_head, &parents);
	}

	/* Finally, get the commit message */
	strbuf_reset(&sb);
	if (strbuf_read_file(&sb, git_path_commit_editmsg(), 0) < 0) {
		int saved_errno = errno;
		rollback_index_files();
		die(_("could not read commit message: %s"), strerror(saved_errno));
	}

	if (verbose || /* Truncate the message just before the diff, if any. */
	    cleanup_mode == CLEANUP_SCISSORS)
		strbuf_setlen(&sb, wt_status_locate_end(sb.buf, sb.len));

	if (cleanup_mode != CLEANUP_NONE)
		strbuf_stripspace(&sb, cleanup_mode == CLEANUP_ALL);
	if (template_untouched(&sb) && !allow_empty_message) {
		rollback_index_files();
		fprintf(stderr, _("Aborting commit; you did not edit the message.\n"));
		exit(1);
	}
	if (message_is_empty(&sb) && !allow_empty_message) {
		rollback_index_files();
		fprintf(stderr, _("Aborting commit due to empty commit message.\n"));
		exit(1);
	}

	if (amend) {
		const char *exclude_gpgsig[2] = { "gpgsig", NULL };
		extra = read_commit_extra_headers(current_head, exclude_gpgsig);
	} else {
		struct commit_extra_header **tail = &extra;
		append_merge_tag_headers(parents, &tail);
	}

	if (commit_tree_extended(sb.buf, sb.len, active_cache_tree->sha1,
			 parents, oid.hash, author_ident.buf, sign_commit, extra)) {
		rollback_index_files();
		die(_("failed to write commit object"));
	}
	strbuf_release(&author_ident);
	free_commit_extra_headers(extra);

	nl = strchr(sb.buf, '\n');
	if (nl)
		strbuf_setlen(&sb, nl + 1 - sb.buf);
	else
		strbuf_addch(&sb, '\n');
	strbuf_insert(&sb, 0, reflog_msg, strlen(reflog_msg));
	strbuf_insert(&sb, strlen(reflog_msg), ": ", 2);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, "HEAD", oid.hash,
				   current_head
				   ? current_head->object.oid.hash : null_sha1,
				   0, sb.buf, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		rollback_index_files();
		die("%s", err.buf);
	}
	ref_transaction_free(transaction);

	unlink(git_path_cherry_pick_head());
	unlink(git_path_revert_head());
	unlink(git_path_merge_head());
	unlink(git_path_merge_msg());
	unlink(git_path_merge_mode());
	unlink(git_path_squash_msg());

	if (commit_index_files())
		die (_("Repository has been updated, but unable to write\n"
		     "new_index file. Check that disk is not full and quota is\n"
		     "not exceeded, and then \"git reset HEAD\" to recover."));

	rerere(0);
	run_commit_hook(use_editor, get_index_file(), "post-commit", NULL);
	if (amend && !no_post_rewrite) {
		struct notes_rewrite_cfg *cfg;
		cfg = init_copy_notes_for_rewrite("amend");
		if (cfg) {
			/* we are amending, so current_head is not NULL */
			copy_note_for_rewrite(cfg, current_head->object.oid.hash, oid.hash);
			finish_copy_notes_for_rewrite(cfg, "Notes added by 'git commit --amend'");
		}
		run_rewrite_hook(&current_head->object.oid, &oid);
	}
	if (!quiet)
		print_summary(prefix, &oid, !current_head);

	strbuf_release(&err);
	return 0;
}