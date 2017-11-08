int cmd_diff(int argc, const char **argv, const char *prefix)
{
	int i;
	struct rev_info rev;
	struct object_array ent = OBJECT_ARRAY_INIT;
	int blobs = 0, paths = 0;
	struct object_array_entry *blob[2];
	int nongit = 0, no_index = 0;
	int result = 0;

	/*
	 * We could get N tree-ish in the rev.pending_objects list.
	 * Also there could be M blobs there, and P pathspecs.
	 *
	 * N=0, M=0:
	 *	cache vs files (diff-files)
	 * N=0, M=2:
	 *      compare two random blobs.  P must be zero.
	 * N=0, M=1, P=1:
	 *	compare a blob with a working tree file.
	 *
	 * N=1, M=0:
	 *      tree vs cache (diff-index --cached)
	 *
	 * N=2, M=0:
	 *      tree vs tree (diff-tree)
	 *
	 * N=0, M=0, P=2:
	 *      compare two filesystem entities (aka --no-index).
	 *
	 * Other cases are errors.
	 */

	/* Were we asked to do --no-index explicitly? */
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--")) {
			i++;
			break;
		}
		if (!strcmp(argv[i], "--no-index"))
			no_index = DIFF_NO_INDEX_EXPLICIT;
		if (argv[i][0] != '-')
			break;
	}

	prefix = setup_git_directory_gently(&nongit);

	if (!no_index) {
		/*
		 * Treat git diff with at least one path outside of the
		 * repo the same as if the command would have been executed
		 * outside of a git repository.  In this case it behaves
		 * the same way as "git diff --no-index <a> <b>", which acts
		 * as a colourful "diff" replacement.
		 */
		if (nongit || ((argc == i + 2) &&
			       (!path_inside_repo(prefix, argv[i]) ||
				!path_inside_repo(prefix, argv[i + 1]))))
			no_index = DIFF_NO_INDEX_IMPLICIT;
	}

	if (!no_index)
		gitmodules_config();
	init_diff_ui_defaults();
	git_config(git_diff_ui_config, NULL);
	precompose_argv(argc, argv);

	init_revisions(&rev, prefix);

	if (no_index && argc != i + 2) {
		if (no_index == DIFF_NO_INDEX_IMPLICIT) {
			/*
			 * There was no --no-index and there were not two
			 * paths. It is possible that the user intended
			 * to do an inside-repository operation.
			 */
			fprintf(stderr, "Not a git repository\n");
			fprintf(stderr,
				"To compare two paths outside a working tree:\n");
		}
		/* Give the usage message for non-repository usage and exit. */
		usagef("git diff %s <path> <path>",
		       no_index == DIFF_NO_INDEX_EXPLICIT ?
		       "--no-index" : "[--no-index]");

	}
	if (no_index)
		/* If this is a no-index diff, just run it and exit there. */
		diff_no_index(&rev, argc, argv);

	/* Otherwise, we are doing the usual "git" diff */
	rev.diffopt.skip_stat_unmatch = !!diff_auto_refresh_index;

	/* Scale to real terminal size and respect statGraphWidth config */
	rev.diffopt.stat_width = -1;
	rev.diffopt.stat_graph_width = -1;

	/* Default to let external and textconv be used */
	DIFF_OPT_SET(&rev.diffopt, ALLOW_EXTERNAL);
	DIFF_OPT_SET(&rev.diffopt, ALLOW_TEXTCONV);

	if (nongit)
		die(_("Not a git repository"));
	argc = setup_revisions(argc, argv, &rev, NULL);
	if (!rev.diffopt.output_format) {
		rev.diffopt.output_format = DIFF_FORMAT_PATCH;
		diff_setup_done(&rev.diffopt);
	}

	DIFF_OPT_SET(&rev.diffopt, RECURSIVE);

	setup_diff_pager(&rev.diffopt);

	/*
	 * Do we have --cached and not have a pending object, then
	 * default to HEAD by hand.  Eek.
	 */
	if (!rev.pending.nr) {
		int i;
		for (i = 1; i < argc; i++) {
			const char *arg = argv[i];
			if (!strcmp(arg, "--"))
				break;
			else if (!strcmp(arg, "--cached") ||
				 !strcmp(arg, "--staged")) {
				add_head_to_pending(&rev);
				if (!rev.pending.nr) {
					struct tree *tree;
					tree = lookup_tree(EMPTY_TREE_SHA1_BIN);
					add_pending_object(&rev, &tree->object, "HEAD");
				}
				break;
			}
		}
	}

	for (i = 0; i < rev.pending.nr; i++) {
		struct object_array_entry *entry = &rev.pending.objects[i];
		struct object *obj = entry->item;
		const char *name = entry->name;
		int flags = (obj->flags & UNINTERESTING);
		if (!obj->parsed)
			obj = parse_object(obj->oid.hash);
		obj = deref_tag(obj, NULL, 0);
		if (!obj)
			die(_("invalid object '%s' given."), name);
		if (obj->type == OBJ_COMMIT)
			obj = &((struct commit *)obj)->tree->object;

		if (obj->type == OBJ_TREE) {
			obj->flags |= flags;
			add_object_array(obj, name, &ent);
		} else if (obj->type == OBJ_BLOB) {
			if (2 <= blobs)
				die(_("more than two blobs given: '%s'"), name);
			blob[blobs] = entry;
			blobs++;

		} else {
			die(_("unhandled object '%s' given."), name);
		}
	}
	if (rev.prune_data.nr)
		paths += rev.prune_data.nr;

	/*
	 * Now, do the arguments look reasonable?
	 */
	if (!ent.nr) {
		switch (blobs) {
		case 0:
			result = builtin_diff_files(&rev, argc, argv);
			break;
		case 1:
			if (paths != 1)
				usage(builtin_diff_usage);
			result = builtin_diff_b_f(&rev, argc, argv, blob);
			break;
		case 2:
			if (paths)
				usage(builtin_diff_usage);
			result = builtin_diff_blobs(&rev, argc, argv, blob);
			break;
		default:
			usage(builtin_diff_usage);
		}
	}
	else if (blobs)
		usage(builtin_diff_usage);
	else if (ent.nr == 1)
		result = builtin_diff_index(&rev, argc, argv);
	else if (ent.nr == 2)
		result = builtin_diff_tree(&rev, argc, argv,
					   &ent.objects[0], &ent.objects[1]);
	else if (ent.objects[0].item->flags & UNINTERESTING) {
		/*
		 * diff A...B where there is at least one merge base
		 * between A and B.  We have ent.objects[0] ==
		 * merge-base, ent.objects[ents-2] == A, and
		 * ent.objects[ents-1] == B.  Show diff between the
		 * base and B.  Note that we pick one merge base at
		 * random if there are more than one.
		 */
		result = builtin_diff_tree(&rev, argc, argv,
					   &ent.objects[0],
					   &ent.objects[ent.nr-1]);
	} else
		result = builtin_diff_combined(&rev, argc, argv,
					       ent.objects, ent.nr);
	result = diff_result_code(&rev.diffopt, result);
	if (1 < rev.diffopt.skip_stat_unmatch)
		refresh_index_quietly();
	return result;
}