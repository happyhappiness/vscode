static int has_remote(const char *refname, const struct object_id *oid,
		      int flags, void *cb_data)
{
	return 1;
}

static int submodule_needs_pushing(const char *path, const unsigned char sha1[20])
{
	if (add_submodule_odb(path) || !lookup_commit_reference(sha1))
		return 0;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		const char *argv[] = {"rev-list", NULL, "--not", "--remotes", "-n", "1" , NULL};
		struct strbuf buf = STRBUF_INIT;
		int needs_pushing = 0;

		argv[1] = sha1_to_hex(sha1);
		cp.argv = argv;
		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.out = -1;
		cp.dir = path;
		if (start_command(&cp))
			die("Could not run 'git rev-list %s --not --remotes -n 1' command in submodule %s",
				sha1_to_hex(sha1), path);
		if (strbuf_read(&buf, cp.out, 41))
			needs_pushing = 1;
		finish_command(&cp);
		close(cp.out);
		strbuf_release(&buf);
		return needs_pushing;
	}

	return 0;
}

static void collect_submodules_from_diff(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	int i;
	struct string_list *needs_pushing = data;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (!S_ISGITLINK(p->two->mode))
			continue;
		if (submodule_needs_pushing(p->two->path, p->two->oid.hash))
			string_list_insert(needs_pushing, p->two->path);
	}
}

static void find_unpushed_submodule_commits(struct commit *commit,
		struct string_list *needs_pushing)
{
