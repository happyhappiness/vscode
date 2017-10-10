			else if (len == 1)
				early = 1; /* "name~" is "name~1"! */
		}
	}
	if (len) {
		struct strbuf truname = STRBUF_INIT;
		strbuf_addstr(&truname, "refs/heads/");
		strbuf_addstr(&truname, remote);
		strbuf_setlen(&truname, truname.len - len);
		if (ref_exists(truname.buf)) {
			strbuf_addf(msg,
				    "%s\t\tbranch '%s'%s of .\n",
				    sha1_to_hex(remote_head->object.sha1),
				    truname.buf + 11,
				    (early ? " (early part)" : ""));
			strbuf_release(&truname);
			goto cleanup;
		}
	}

	if (!strcmp(remote, "FETCH_HEAD") &&
			!access(git_path("FETCH_HEAD"), R_OK)) {
		const char *filename;
		FILE *fp;
		struct strbuf line = STRBUF_INIT;
		char *ptr;

		filename = git_path("FETCH_HEAD");
		fp = fopen(filename, "r");
		if (!fp)
			die_errno(_("could not open '%s' for reading"),
				  filename);
		strbuf_getline(&line, fp, '\n');
		fclose(fp);
		ptr = strstr(line.buf, "\tnot-for-merge\t");
		if (ptr)
			strbuf_remove(&line, ptr-line.buf+1, 13);
		strbuf_addbuf(msg, &line);
		strbuf_release(&line);
		goto cleanup;
	}

	if (remote_head->util) {
		struct merge_remote_desc *desc;
		desc = merge_remote_util(remote_head);
		if (desc && desc->obj && desc->obj->type == OBJ_TAG) {
