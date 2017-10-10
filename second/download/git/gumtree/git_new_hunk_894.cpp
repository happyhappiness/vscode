	i = 0;
	while (!strbuf_getline_nul(&info, fp)) {
		int lmode, rmode;
		struct object_id loid, roid;
		char status;
		const char *src_path, *dst_path;

		if (starts_with(info.buf, "::"))
			die(N_("combined diff formats('-c' and '--cc') are "
			       "not supported in\n"
			       "directory diff mode('-d' and '--dir-diff')."));

		if (parse_index_info(info.buf, &lmode, &rmode, &loid, &roid,
				     &status))
			break;
		if (strbuf_getline_nul(&lpath, fp))
			break;
		src_path = lpath.buf;

		i++;
		if (status != 'C' && status != 'R') {
			dst_path = src_path;
		} else {
			if (strbuf_getline_nul(&rpath, fp))
				break;
			dst_path = rpath.buf;
		}

		if (S_ISGITLINK(lmode) || S_ISGITLINK(rmode)) {
			strbuf_reset(&buf);
			strbuf_addf(&buf, "Subproject commit %s",
				    oid_to_hex(&loid));
