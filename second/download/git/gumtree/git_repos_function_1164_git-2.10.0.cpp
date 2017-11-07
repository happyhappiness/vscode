int finish_http_pack_request(struct http_pack_request *preq)
{
	struct packed_git **lst;
	struct packed_git *p = preq->target;
	char *tmp_idx;
	size_t len;
	struct child_process ip = CHILD_PROCESS_INIT;
	const char *ip_argv[8];

	close_pack_index(p);

	fclose(preq->packfile);
	preq->packfile = NULL;

	lst = preq->lst;
	while (*lst != p)
		lst = &((*lst)->next);
	*lst = (*lst)->next;

	if (!strip_suffix(preq->tmpfile, ".pack.temp", &len))
		die("BUG: pack tmpfile does not end in .pack.temp?");
	tmp_idx = xstrfmt("%.*s.idx.temp", (int)len, preq->tmpfile);

	ip_argv[0] = "index-pack";
	ip_argv[1] = "-o";
	ip_argv[2] = tmp_idx;
	ip_argv[3] = preq->tmpfile;
	ip_argv[4] = NULL;

	ip.argv = ip_argv;
	ip.git_cmd = 1;
	ip.no_stdin = 1;
	ip.no_stdout = 1;

	if (run_command(&ip)) {
		unlink(preq->tmpfile);
		unlink(tmp_idx);
		free(tmp_idx);
		return -1;
	}

	unlink(sha1_pack_index_name(p->sha1));

	if (finalize_object_file(preq->tmpfile, sha1_pack_name(p->sha1))
	 || finalize_object_file(tmp_idx, sha1_pack_index_name(p->sha1))) {
		free(tmp_idx);
		return -1;
	}

	install_packed_git(p);
	free(tmp_idx);
	return 0;
}