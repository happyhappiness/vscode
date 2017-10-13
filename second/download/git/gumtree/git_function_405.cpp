int cmd_format_patch(int argc, const char **argv, const char *prefix)
{
	struct commit *commit;
	struct commit **list = NULL;
	struct rev_info rev;
	struct setup_revision_opt s_r_opt;
	int nr = 0, total, i;
	int use_stdout = 0;
	int start_number = -1;
	int just_numbers = 0;
	int ignore_if_in_upstream = 0;
	int cover_letter = -1;
	int boundary_count = 0;
	int no_binary_diff = 0;
	int zero_commit = 0;
	struct commit *origin = NULL;
	const char *in_reply_to = NULL;
	struct patch_ids ids;
	struct strbuf buf = STRBUF_INIT;
	int use_patch_format = 0;
	int quiet = 0;
	int reroll_count = -1;
	char *branch_name = NULL;
	char *base_commit = NULL;
	struct base_tree_info bases;

	const struct option builtin_format_patch_options[] = {
		{ OPTION_CALLBACK, 'n', "numbered", &numbered, NULL,
			    N_("use [PATCH n/m] even with a single patch"),
			    PARSE_OPT_NOARG, numbered_callback },
		{ OPTION_CALLBACK, 'N', "no-numbered", &numbered, NULL,
			    N_("use [PATCH] even with multiple patches"),
			    PARSE_OPT_NOARG, no_numbered_callback },
		OPT_BOOL('s', "signoff", &do_signoff, N_("add Signed-off-by:")),
		OPT_BOOL(0, "stdout", &use_stdout,
			    N_("print patches to standard out")),
		OPT_BOOL(0, "cover-letter", &cover_letter,
			    N_("generate a cover letter")),
		OPT_BOOL(0, "numbered-files", &just_numbers,
			    N_("use simple number sequence for output file names")),
		OPT_STRING(0, "suffix", &fmt_patch_suffix, N_("sfx"),
			    N_("use <sfx> instead of '.patch'")),
		OPT_INTEGER(0, "start-number", &start_number,
			    N_("start numbering patches at <n> instead of 1")),
		OPT_INTEGER('v', "reroll-count", &reroll_count,
			    N_("mark the series as Nth re-roll")),
		{ OPTION_CALLBACK, 0, "subject-prefix", &rev, N_("prefix"),
			    N_("Use [<prefix>] instead of [PATCH]"),
			    PARSE_OPT_NONEG, subject_prefix_callback },
		{ OPTION_CALLBACK, 'o', "output-directory", &output_directory,
			    N_("dir"), N_("store resulting files in <dir>"),
			    PARSE_OPT_NONEG, output_directory_callback },
		{ OPTION_CALLBACK, 'k', "keep-subject", &rev, NULL,
			    N_("don't strip/add [PATCH]"),
			    PARSE_OPT_NOARG | PARSE_OPT_NONEG, keep_callback },
		OPT_BOOL(0, "no-binary", &no_binary_diff,
			 N_("don't output binary diffs")),
		OPT_BOOL(0, "zero-commit", &zero_commit,
			 N_("output all-zero hash in From header")),
		OPT_BOOL(0, "ignore-if-in-upstream", &ignore_if_in_upstream,
			 N_("don't include a patch matching a commit upstream")),
		{ OPTION_SET_INT, 'p', "no-stat", &use_patch_format, NULL,
		  N_("show patch format instead of default (patch + stat)"),
		  PARSE_OPT_NONEG | PARSE_OPT_NOARG, NULL, 1},
		OPT_GROUP(N_("Messaging")),
		{ OPTION_CALLBACK, 0, "add-header", NULL, N_("header"),
			    N_("add email header"), 0, header_callback },
		{ OPTION_CALLBACK, 0, "to", NULL, N_("email"), N_("add To: header"),
			    0, to_callback },
		{ OPTION_CALLBACK, 0, "cc", NULL, N_("email"), N_("add Cc: header"),
			    0, cc_callback },
		{ OPTION_CALLBACK, 0, "from", &from, N_("ident"),
			    N_("set From address to <ident> (or committer ident if absent)"),
			    PARSE_OPT_OPTARG, from_callback },
		OPT_STRING(0, "in-reply-to", &in_reply_to, N_("message-id"),
			    N_("make first mail a reply to <message-id>")),
		{ OPTION_CALLBACK, 0, "attach", &rev, N_("boundary"),
			    N_("attach the patch"), PARSE_OPT_OPTARG,
			    attach_callback },
		{ OPTION_CALLBACK, 0, "inline", &rev, N_("boundary"),
			    N_("inline the patch"),
			    PARSE_OPT_OPTARG | PARSE_OPT_NONEG,
			    inline_callback },
		{ OPTION_CALLBACK, 0, "thread", &thread, N_("style"),
			    N_("enable message threading, styles: shallow, deep"),
			    PARSE_OPT_OPTARG, thread_callback },
		OPT_STRING(0, "signature", &signature, N_("signature"),
			    N_("add a signature")),
		OPT_STRING(0, "base", &base_commit, N_("base-commit"),
			   N_("add prerequisite tree info to the patch series")),
		OPT_FILENAME(0, "signature-file", &signature_file,
				N_("add a signature from a file")),
		OPT__QUIET(&quiet, N_("don't print the patch filenames")),
		OPT_END()
	};

	extra_hdr.strdup_strings = 1;
	extra_to.strdup_strings = 1;
	extra_cc.strdup_strings = 1;
	init_log_defaults();
	git_config(git_format_config, NULL);
	init_revisions(&rev, prefix);
	rev.commit_format = CMIT_FMT_EMAIL;
	rev.expand_tabs_in_log_default = 0;
	rev.verbose_header = 1;
	rev.diff = 1;
	rev.max_parents = 1;
	DIFF_OPT_SET(&rev.diffopt, RECURSIVE);
	rev.subject_prefix = fmt_patch_subject_prefix;
	memset(&s_r_opt, 0, sizeof(s_r_opt));
	s_r_opt.def = "HEAD";
	s_r_opt.revarg_opt = REVARG_COMMITTISH;

	if (default_attach) {
		rev.mime_boundary = default_attach;
		rev.no_inline = 1;
	}

	/*
	 * Parse the arguments before setup_revisions(), or something
	 * like "git format-patch -o a123 HEAD^.." may fail; a123 is
	 * possibly a valid SHA1.
	 */
	argc = parse_options(argc, argv, prefix, builtin_format_patch_options,
			     builtin_format_patch_usage,
			     PARSE_OPT_KEEP_ARGV0 | PARSE_OPT_KEEP_UNKNOWN |
			     PARSE_OPT_KEEP_DASHDASH);

	if (0 < reroll_count) {
		struct strbuf sprefix = STRBUF_INIT;
		strbuf_addf(&sprefix, "%s v%d",
			    rev.subject_prefix, reroll_count);
		rev.reroll_count = reroll_count;
		rev.subject_prefix = strbuf_detach(&sprefix, NULL);
	}

	for (i = 0; i < extra_hdr.nr; i++) {
		strbuf_addstr(&buf, extra_hdr.items[i].string);
		strbuf_addch(&buf, '\n');
	}

	if (extra_to.nr)
		strbuf_addstr(&buf, "To: ");
	for (i = 0; i < extra_to.nr; i++) {
		if (i)
			strbuf_addstr(&buf, "    ");
		strbuf_addstr(&buf, extra_to.items[i].string);
		if (i + 1 < extra_to.nr)
			strbuf_addch(&buf, ',');
		strbuf_addch(&buf, '\n');
	}

	if (extra_cc.nr)
		strbuf_addstr(&buf, "Cc: ");
	for (i = 0; i < extra_cc.nr; i++) {
		if (i)
			strbuf_addstr(&buf, "    ");
		strbuf_addstr(&buf, extra_cc.items[i].string);
		if (i + 1 < extra_cc.nr)
			strbuf_addch(&buf, ',');
		strbuf_addch(&buf, '\n');
	}

	rev.extra_headers = strbuf_detach(&buf, NULL);

	if (from) {
		if (split_ident_line(&rev.from_ident, from, strlen(from)))
			die(_("invalid ident line: %s"), from);
	}

	if (start_number < 0)
		start_number = 1;

	/*
	 * If numbered is set solely due to format.numbered in config,
	 * and it would conflict with --keep-subject (-k) from the
	 * command line, reset "numbered".
	 */
	if (numbered && keep_subject && !numbered_cmdline_opt)
		numbered = 0;

	if (numbered && keep_subject)
		die (_("-n and -k are mutually exclusive."));
	if (keep_subject && subject_prefix)
		die (_("--subject-prefix and -k are mutually exclusive."));
	rev.preserve_subject = keep_subject;

	argc = setup_revisions(argc, argv, &rev, &s_r_opt);
	if (argc > 1)
		die (_("unrecognized argument: %s"), argv[1]);

	if (rev.diffopt.output_format & DIFF_FORMAT_NAME)
		die(_("--name-only does not make sense"));
	if (rev.diffopt.output_format & DIFF_FORMAT_NAME_STATUS)
		die(_("--name-status does not make sense"));
	if (rev.diffopt.output_format & DIFF_FORMAT_CHECKDIFF)
		die(_("--check does not make sense"));

	if (!use_patch_format &&
		(!rev.diffopt.output_format ||
		 rev.diffopt.output_format == DIFF_FORMAT_PATCH))
		rev.diffopt.output_format = DIFF_FORMAT_DIFFSTAT | DIFF_FORMAT_SUMMARY;

	/* Always generate a patch */
	rev.diffopt.output_format |= DIFF_FORMAT_PATCH;

	rev.zero_commit = zero_commit;

	if (!DIFF_OPT_TST(&rev.diffopt, TEXT) && !no_binary_diff)
		DIFF_OPT_SET(&rev.diffopt, BINARY);

	if (rev.show_notes)
		init_display_notes(&rev.notes_opt);

	if (!output_directory && !use_stdout)
		output_directory = config_output_directory;

	if (!use_stdout)
		output_directory = set_outdir(prefix, output_directory);
	else
		setup_pager();

	if (output_directory) {
		if (rev.diffopt.use_color != GIT_COLOR_ALWAYS)
			rev.diffopt.use_color = GIT_COLOR_NEVER;
		if (use_stdout)
			die(_("standard output, or directory, which one?"));
		if (mkdir(output_directory, 0777) < 0 && errno != EEXIST)
			die_errno(_("Could not create directory '%s'"),
				  output_directory);
	}

	if (rev.pending.nr == 1) {
		int check_head = 0;

		if (rev.max_count < 0 && !rev.show_root_diff) {
			/*
			 * This is traditional behaviour of "git format-patch
			 * origin" that prepares what the origin side still
			 * does not have.
			 */
			rev.pending.objects[0].item->flags |= UNINTERESTING;
			add_head_to_pending(&rev);
			check_head = 1;
		}
		/*
		 * Otherwise, it is "format-patch -22 HEAD", and/or
		 * "format-patch --root HEAD".  The user wants
		 * get_revision() to do the usual traversal.
		 */

		if (!strcmp(rev.pending.objects[0].name, "HEAD"))
			check_head = 1;

		if (check_head) {
			unsigned char sha1[20];
			const char *ref, *v;
			ref = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
						 sha1, NULL);
			if (ref && skip_prefix(ref, "refs/heads/", &v))
				branch_name = xstrdup(v);
			else
				branch_name = xstrdup(""); /* no branch */
		}
	}

	/*
	 * We cannot move this anywhere earlier because we do want to
	 * know if --root was given explicitly from the command line.
	 */
	rev.show_root_diff = 1;

	if (ignore_if_in_upstream) {
		/* Don't say anything if head and upstream are the same. */
		if (rev.pending.nr == 2) {
			struct object_array_entry *o = rev.pending.objects;
			if (oidcmp(&o[0].item->oid, &o[1].item->oid) == 0)
				return 0;
		}
		get_patch_ids(&rev, &ids);
	}

	if (prepare_revision_walk(&rev))
		die(_("revision walk setup failed"));
	rev.boundary = 1;
	while ((commit = get_revision(&rev)) != NULL) {
		if (commit->object.flags & BOUNDARY) {
			boundary_count++;
			origin = (boundary_count == 1) ? commit : NULL;
			continue;
		}

		if (ignore_if_in_upstream && has_commit_patch_id(commit, &ids))
			continue;

		nr++;
		REALLOC_ARRAY(list, nr);
		list[nr - 1] = commit;
	}
	if (nr == 0)
		/* nothing to do */
		return 0;
	total = nr;
	if (!keep_subject && auto_number && total > 1)
		numbered = 1;
	if (numbered)
		rev.total = total + start_number - 1;
	if (cover_letter == -1) {
		if (config_cover_letter == COVER_AUTO)
			cover_letter = (total > 1);
		else
			cover_letter = (config_cover_letter == COVER_ON);
	}

	if (!signature) {
		; /* --no-signature inhibits all signatures */
	} else if (signature && signature != git_version_string) {
		; /* non-default signature already set */
	} else if (signature_file) {
		struct strbuf buf = STRBUF_INIT;

		if (strbuf_read_file(&buf, signature_file, 128) < 0)
			die_errno(_("unable to read signature file '%s'"), signature_file);
		signature = strbuf_detach(&buf, NULL);
	}

	memset(&bases, 0, sizeof(bases));
	if (base_commit || base_auto) {
		struct commit *base = get_base_commit(base_commit, list, nr);
		reset_revision_walk();
		prepare_bases(&bases, base, list, nr);
	}

	if (in_reply_to || thread || cover_letter)
		rev.ref_message_ids = xcalloc(1, sizeof(struct string_list));
	if (in_reply_to) {
		const char *msgid = clean_message_id(in_reply_to);
		string_list_append(rev.ref_message_ids, msgid);
	}
	rev.numbered_files = just_numbers;
	rev.patch_suffix = fmt_patch_suffix;
	if (cover_letter) {
		if (thread)
			gen_message_id(&rev, "cover");
		make_cover_letter(&rev, use_stdout,
				  origin, nr, list, branch_name, quiet);
		print_bases(&bases, rev.diffopt.file);
		print_signature(rev.diffopt.file);
		total++;
		start_number--;
	}
	rev.add_signoff = do_signoff;
	while (0 <= --nr) {
		int shown;
		commit = list[nr];
		rev.nr = total - nr + (start_number - 1);
		/* Make the second and subsequent mails replies to the first */
		if (thread) {
			/* Have we already had a message ID? */
			if (rev.message_id) {
				/*
				 * For deep threading: make every mail
				 * a reply to the previous one, no
				 * matter what other options are set.
				 *
				 * For shallow threading:
				 *
				 * Without --cover-letter and
				 * --in-reply-to, make every mail a
				 * reply to the one before.
				 *
				 * With --in-reply-to but no
				 * --cover-letter, make every mail a
				 * reply to the <reply-to>.
				 *
				 * With --cover-letter, make every
				 * mail but the cover letter a reply
				 * to the cover letter.  The cover
				 * letter is a reply to the
				 * --in-reply-to, if specified.
				 */
				if (thread == THREAD_SHALLOW
				    && rev.ref_message_ids->nr > 0
				    && (!cover_letter || rev.nr > 1))
					free(rev.message_id);
				else
					string_list_append(rev.ref_message_ids,
							   rev.message_id);
			}
			gen_message_id(&rev, oid_to_hex(&commit->object.oid));
		}

		if (!use_stdout &&
		    open_next_file(rev.numbered_files ? NULL : commit, NULL, &rev, quiet))
			die(_("Failed to create output files"));
		shown = log_tree_commit(&rev, commit);
		free_commit_buffer(commit);

		/* We put one extra blank line between formatted
		 * patches and this flag is used by log-tree code
		 * to see if it needs to emit a LF before showing
		 * the log; when using one file per patch, we do
		 * not want the extra blank line.
		 */
		if (!use_stdout)
			rev.shown_one = 0;
		if (shown) {
			print_bases(&bases, rev.diffopt.file);
			if (rev.mime_boundary)
				fprintf(rev.diffopt.file, "\n--%s%s--\n\n\n",
				       mime_boundary_leader,
				       rev.mime_boundary);
			else
				print_signature(rev.diffopt.file);
		}
		if (!use_stdout)
			fclose(rev.diffopt.file);
	}
	free(list);
	free(branch_name);
	string_list_clear(&extra_to, 0);
	string_list_clear(&extra_cc, 0);
	string_list_clear(&extra_hdr, 0);
	if (ignore_if_in_upstream)
		free_patch_ids(&ids);
	return 0;
}