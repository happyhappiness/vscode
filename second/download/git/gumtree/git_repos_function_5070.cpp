int cmd_show(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	struct object_array_entry *objects;
	struct setup_revision_opt opt;
	struct pathspec match_all;
	int i, count, ret = 0;

	init_grep_defaults();
	git_config(git_log_config, NULL);

	memset(&match_all, 0, sizeof(match_all));
	init_revisions(&rev, prefix);
	rev.diff = 1;
	rev.always_show_header = 1;
	rev.no_walk = REVISION_WALK_NO_WALK_SORTED;
	rev.diffopt.stat_width = -1; 	/* Scale to real terminal size */

	memset(&opt, 0, sizeof(opt));
	opt.def = "HEAD";
	opt.tweak = show_setup_revisions_tweak;
	cmd_log_init(argc, argv, prefix, &rev, &opt);

	if (!rev.no_walk)
		return cmd_log_walk(&rev);

	count = rev.pending.nr;
	objects = rev.pending.objects;
	for (i = 0; i < count && !ret; i++) {
		struct object *o = objects[i].item;
		const char *name = objects[i].name;
		switch (o->type) {
		case OBJ_BLOB:
			ret = show_blob_object(o->sha1, &rev, name);
			break;
		case OBJ_TAG: {
			struct tag *t = (struct tag *)o;

			if (rev.shown_one)
				putchar('\n');
			printf("%stag %s%s\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					t->tag,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			ret = show_tag_object(o->sha1, &rev);
			rev.shown_one = 1;
			if (ret)
				break;
			o = parse_object(t->tagged->sha1);
			if (!o)
				ret = error(_("Could not read object %s"),
					    sha1_to_hex(t->tagged->sha1));
			objects[i].item = o;
			i--;
			break;
		}
		case OBJ_TREE:
			if (rev.shown_one)
				putchar('\n');
			printf("%stree %s%s\n\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					name,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			read_tree_recursive((struct tree *)o, "", 0, 0, &match_all,
					show_tree_object, NULL);
			rev.shown_one = 1;
			break;
		case OBJ_COMMIT:
			rev.pending.nr = rev.pending.alloc = 0;
			rev.pending.objects = NULL;
			add_object_array(o, name, &rev.pending);
			ret = cmd_log_walk(&rev);
			break;
		default:
			ret = error(_("Unknown type: %d"), o->type);
		}
	}
	free(objects);
	return ret;
}