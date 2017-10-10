 		branch = opts.new_branch;
 	}
 
 	return add_worktree(path, branch, &opts);
 }
 
+static void show_worktree_porcelain(struct worktree *wt)
+{
+	printf("worktree %s\n", wt->path);
+	if (wt->is_bare)
+		printf("bare\n");
+	else {
+		printf("HEAD %s\n", sha1_to_hex(wt->head_sha1));
+		if (wt->is_detached)
+			printf("detached\n");
+		else
+			printf("branch %s\n", wt->head_ref);
+	}
+	printf("\n");
+}
+
+static void show_worktree(struct worktree *wt, int path_maxlen, int abbrev_len)
+{
+	struct strbuf sb = STRBUF_INIT;
+	int cur_path_len = strlen(wt->path);
+	int path_adj = cur_path_len - utf8_strwidth(wt->path);
+
+	strbuf_addf(&sb, "%-*s ", 1 + path_maxlen + path_adj, wt->path);
+	if (wt->is_bare)
+		strbuf_addstr(&sb, "(bare)");
+	else {
+		strbuf_addf(&sb, "%-*s ", abbrev_len,
+				find_unique_abbrev(wt->head_sha1, DEFAULT_ABBREV));
+		if (!wt->is_detached)
+			strbuf_addf(&sb, "[%s]", shorten_unambiguous_ref(wt->head_ref, 0));
+		else
+			strbuf_addstr(&sb, "(detached HEAD)");
+	}
+	printf("%s\n", sb.buf);
+
+	strbuf_release(&sb);
+}
+
+static void measure_widths(struct worktree **wt, int *abbrev, int *maxlen)
+{
+	int i;
+
+	for (i = 0; wt[i]; i++) {
+		int sha1_len;
+		int path_len = strlen(wt[i]->path);
+
+		if (path_len > *maxlen)
+			*maxlen = path_len;
+		sha1_len = strlen(find_unique_abbrev(wt[i]->head_sha1, *abbrev));
+		if (sha1_len > *abbrev)
+			*abbrev = sha1_len;
+	}
+}
+
+static int list(int ac, const char **av, const char *prefix)
+{
+	int porcelain = 0;
+
+	struct option options[] = {
+		OPT_BOOL(0, "porcelain", &porcelain, N_("machine-readable output")),
+		OPT_END()
+	};
+
+	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
+	if (ac)
+		usage_with_options(worktree_usage, options);
+	else {
+		struct worktree **worktrees = get_worktrees();
+		int path_maxlen = 0, abbrev = DEFAULT_ABBREV, i;
+
+		if (!porcelain)
+			measure_widths(worktrees, &abbrev, &path_maxlen);
+
+		for (i = 0; worktrees[i]; i++) {
+			if (porcelain)
+				show_worktree_porcelain(worktrees[i]);
+			else
+				show_worktree(worktrees[i], path_maxlen, abbrev);
+		}
+		free_worktrees(worktrees);
+	}
+	return 0;
+}
+
 int cmd_worktree(int ac, const char **av, const char *prefix)
 {
 	struct option options[] = {
 		OPT_END()
 	};
 
 	if (ac < 2)
 		usage_with_options(worktree_usage, options);
 	if (!strcmp(av[1], "add"))
 		return add(ac - 1, av + 1, prefix);
 	if (!strcmp(av[1], "prune"))
 		return prune(ac - 1, av + 1, prefix);
+	if (!strcmp(av[1], "list"))
+		return list(ac - 1, av + 1, prefix);
 	usage_with_options(worktree_usage, options);
 }
