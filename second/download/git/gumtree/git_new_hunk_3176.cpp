
	ret = start_command(&cmd);
	if (ret)
		return ret;

	out = xfdopen(cmd.out, "r");
	while (strbuf_getline_lf(&line, out) != EOF) {
		if (line.len != 40)
			die("repack: Expecting 40 character sha1 lines only from pack-objects.");
		string_list_append(&names, line.buf);
	}
	fclose(out);
	ret = finish_command(&cmd);
