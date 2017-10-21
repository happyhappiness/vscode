	}

	if (!(ret = new(struct filter_struct)))
		out_of_memory("add_rule");
	memset(ret, 0, sizeof ret[0]);

	if (xflags & XFLG_ANCHORED2ABS && *pat == '/'
	    && !(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))) {
		mflags |= MATCHFLG_ABS_PATH;
		ex_len = dirbuf_len - module_dirlen - 1;
	} else
		ex_len = 0;
	if (!(ret->pattern = new_array(char, ex_len + pat_len + 1)))
		out_of_memory("add_rule");
	if (ex_len)
		memcpy(ret->pattern, dirbuf + module_dirlen, ex_len);
