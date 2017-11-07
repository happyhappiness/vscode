static void read_alternate_refs(const char *path,
				alternate_ref_fn *cb,
				void *data)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	struct strbuf line = STRBUF_INIT;
	FILE *fh;

	cmd.git_cmd = 1;
	argv_array_pushf(&cmd.args, "--git-dir=%s", path);
	argv_array_push(&cmd.args, "for-each-ref");
	argv_array_push(&cmd.args, "--format=%(objectname) %(refname)");
	cmd.env = local_repo_env;
	cmd.out = -1;

	if (start_command(&cmd))
		return;

	fh = xfdopen(cmd.out, "r");
	while (strbuf_getline_lf(&line, fh) != EOF) {
		struct object_id oid;

		if (get_oid_hex(line.buf, &oid) ||
		    line.buf[GIT_SHA1_HEXSZ] != ' ') {
			warning("invalid line while parsing alternate refs: %s",
				line.buf);
			break;
		}

		cb(line.buf + GIT_SHA1_HEXSZ + 1, &oid, data);
	}

	fclose(fh);
	finish_command(&cmd);
}