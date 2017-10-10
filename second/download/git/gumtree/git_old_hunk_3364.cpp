	dst_name = resolve_ref_unsafe(buf.buf, 0, sha1, &flag);
	strbuf_release(&buf);

	if (!(flag & REF_ISSYMREF))
		return;

	dst_name = strip_namespace(dst_name);
	if (!dst_name) {
		rp_error("refusing update to broken symref '%s'", cmd->ref_name);
		cmd->skip_update = 1;
		cmd->error_string = "broken symref";
		return;
	}

	if ((item = string_list_lookup(list, dst_name)) == NULL)
		return;

	cmd->skip_update = 1;

