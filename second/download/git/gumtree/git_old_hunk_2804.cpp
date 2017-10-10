	struct tree *tree2;
	if (len != 82 || !isspace(line[40]) || get_sha1_hex(line + 41, sha1))
		return error("Need exactly two trees, separated by a space");
	tree2 = lookup_tree(sha1);
	if (!tree2 || parse_tree(tree2))
		return -1;
	printf("%s %s\n", sha1_to_hex(tree1->object.sha1),
			  sha1_to_hex(tree2->object.sha1));
	diff_tree_sha1(tree1->object.sha1, tree2->object.sha1,
		       "", &log_tree_opt.diffopt);
	log_tree_diff_flush(&log_tree_opt);
	return 0;
}

static int diff_tree_stdin(char *line)
