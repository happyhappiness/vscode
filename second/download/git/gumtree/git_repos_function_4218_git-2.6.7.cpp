static int get_rebase_fork_point(unsigned char *fork_point, const char *repo,
		const char *refspec)
{
	int ret;
	struct branch *curr_branch;
	const char *remote_branch;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf sb = STRBUF_INIT;

	curr_branch = branch_get("HEAD");
	if (!curr_branch)
		return -1;

	if (refspec)
		remote_branch = get_tracking_branch(repo, refspec);
	else
		remote_branch = get_upstream_branch(repo);

	if (!remote_branch)
		return -1;

	argv_array_pushl(&cp.args, "merge-base", "--fork-point",
			remote_branch, curr_branch->name, NULL);
	cp.no_stdin = 1;
	cp.no_stderr = 1;
	cp.git_cmd = 1;

	ret = capture_command(&cp, &sb, GIT_SHA1_HEXSZ);
	if (ret)
		goto cleanup;

	ret = get_sha1_hex(sb.buf, fork_point);
	if (ret)
		goto cleanup;

cleanup:
	strbuf_release(&sb);
	return ret ? -1 : 0;
}