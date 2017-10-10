	 * looks like an object ID will do since it will be immediately
	 * replaced by the symbolic-ref or update-ref invocation in the new
	 * worktree.
	 */
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/HEAD", sb_repo.buf);
	write_file(sb.buf, "%s", sha1_to_hex(null_sha1));
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/commondir", sb_repo.buf);
	write_file(sb.buf, "../..");

	fprintf_ln(stderr, _("Preparing %s (identifier %s)"), path, name);

	argv_array_pushf(&child_env, "%s=%s", GIT_DIR_ENVIRONMENT, sb_git.buf);
	argv_array_pushf(&child_env, "%s=%s", GIT_WORK_TREE_ENVIRONMENT, path);
	cp.git_cmd = 1;

	if (commit)
		argv_array_pushl(&cp.args, "update-ref", "HEAD",
				 oid_to_hex(&commit->object.oid), NULL);
	else
