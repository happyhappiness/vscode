static int git_default_core_config(const char *var, const char *value)
{
	/* This needs a better name */
	if (!strcmp(var, "core.filemode")) {
		trust_executable_bit = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "core.trustctime")) {
		trust_ctime = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "core.checkstat")) {
		if (!strcasecmp(value, "default"))
			check_stat = 1;
		else if (!strcasecmp(value, "minimal"))
			check_stat = 0;
	}

	if (!strcmp(var, "core.quotepath")) {
		quote_path_fully = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.symlinks")) {
		has_symlinks = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.ignorecase")) {
		ignore_case = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.attributesfile"))
		return git_config_pathname(&git_attributes_file, var, value);

	if (!strcmp(var, "core.bare")) {
		is_bare_repository_cfg = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.ignorestat")) {
		assume_unchanged = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.prefersymlinkrefs")) {
		prefer_symlink_refs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.logallrefupdates")) {
		log_all_ref_updates = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.warnambiguousrefs")) {
		warn_ambiguous_refs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.abbrev")) {
		int abbrev = git_config_int(var, value);
		if (abbrev < minimum_abbrev || abbrev > 40)
			return -1;
		default_abbrev = abbrev;
		return 0;
	}

	if (!strcmp(var, "core.loosecompression")) {
		int level = git_config_int(var, value);
		if (level == -1)
			level = Z_DEFAULT_COMPRESSION;
		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die("bad zlib compression level %d", level);
		zlib_compression_level = level;
		zlib_compression_seen = 1;
		return 0;
	}

	if (!strcmp(var, "core.compression")) {
		int level = git_config_int(var, value);
		if (level == -1)
			level = Z_DEFAULT_COMPRESSION;
		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die("bad zlib compression level %d", level);
		core_compression_level = level;
		core_compression_seen = 1;
		if (!zlib_compression_seen)
			zlib_compression_level = level;
		return 0;
	}

	if (!strcmp(var, "core.packedgitwindowsize")) {
		int pgsz_x2 = getpagesize() * 2;
		packed_git_window_size = git_config_ulong(var, value);

		/* This value must be multiple of (pagesize * 2) */
		packed_git_window_size /= pgsz_x2;
		if (packed_git_window_size < 1)
			packed_git_window_size = 1;
		packed_git_window_size *= pgsz_x2;
		return 0;
	}

	if (!strcmp(var, "core.bigfilethreshold")) {
		big_file_threshold = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.packedgitlimit")) {
		packed_git_limit = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.deltabasecachelimit")) {
		delta_base_cache_limit = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.autocrlf")) {
		if (value && !strcasecmp(value, "input")) {
			if (core_eol == EOL_CRLF)
				return error("core.autocrlf=input conflicts with core.eol=crlf");
			auto_crlf = AUTO_CRLF_INPUT;
			return 0;
		}
		auto_crlf = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.safecrlf")) {
		if (value && !strcasecmp(value, "warn")) {
			safe_crlf = SAFE_CRLF_WARN;
			return 0;
		}
		safe_crlf = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.eol")) {
		if (value && !strcasecmp(value, "lf"))
			core_eol = EOL_LF;
		else if (value && !strcasecmp(value, "crlf"))
			core_eol = EOL_CRLF;
		else if (value && !strcasecmp(value, "native"))
			core_eol = EOL_NATIVE;
		else
			core_eol = EOL_UNSET;
		if (core_eol == EOL_CRLF && auto_crlf == AUTO_CRLF_INPUT)
			return error("core.autocrlf=input conflicts with core.eol=crlf");
		return 0;
	}

	if (!strcmp(var, "core.notesref")) {
		notes_ref_name = xstrdup(value);
		return 0;
	}

	if (!strcmp(var, "core.pager"))
		return git_config_string(&pager_program, var, value);

	if (!strcmp(var, "core.editor"))
		return git_config_string(&editor_program, var, value);

	if (!strcmp(var, "core.commentchar")) {
		if (!value)
			return config_error_nonbool(var);
		else if (!strcasecmp(value, "auto"))
			auto_comment_line_char = 1;
		else if (value[0] && !value[1]) {
			comment_line_char = value[0];
			auto_comment_line_char = 0;
		} else
			return error("core.commentChar should only be one character");
		return 0;
	}

	if (!strcmp(var, "core.askpass"))
		return git_config_string(&askpass_program, var, value);

	if (!strcmp(var, "core.excludesfile"))
		return git_config_pathname(&excludes_file, var, value);

	if (!strcmp(var, "core.whitespace")) {
		if (!value)
			return config_error_nonbool(var);
		whitespace_rule_cfg = parse_whitespace_rule(value);
		return 0;
	}

	if (!strcmp(var, "core.fsyncobjectfiles")) {
		fsync_object_files = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.preloadindex")) {
		core_preload_index = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.createobject")) {
		if (!strcmp(value, "rename"))
			object_creation_mode = OBJECT_CREATION_USES_RENAMES;
		else if (!strcmp(value, "link"))
			object_creation_mode = OBJECT_CREATION_USES_HARDLINKS;
		else
			die("Invalid mode for object creation: %s", value);
		return 0;
	}

	if (!strcmp(var, "core.sparsecheckout")) {
		core_apply_sparse_checkout = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.precomposeunicode")) {
		precomposed_unicode = git_config_bool(var, value);
		return 0;
	}

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}