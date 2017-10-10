	}

	if (!pack_name && !from_stdin)
		usage(index_pack_usage);
	if (fix_thin_pack && !from_stdin)
		die(_("--fix-thin cannot be used without --stdin"));
	if (!index_name && pack_name)
		index_name = derive_filename(pack_name, ".idx", &index_name_buf);
	if (keep_msg && !keep_name && pack_name)
		keep_name = derive_filename(pack_name, ".keep", &keep_name_buf);

	if (verify) {
		if (!index_name)
			die(_("--verify with no packfile name given"));
		read_idx_option(&opts, index_name);
		opts.flags |= WRITE_IDX_VERIFY | WRITE_IDX_STRICT;
	}
