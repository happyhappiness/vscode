		} else {
			if (mf == MATCHFLG_SENDER_SIDE)
				return;
		}
	}

	if (!(ret = new(struct filter_struct)))
		out_of_memory("add_rule");
	memset(ret, 0, sizeof ret[0]);

	if (!(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))
	 && ((xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH) && *pat == '/')
	  || (xflags & XFLG_ABS_IF_SLASH && strchr(pat, '/') != NULL))) {
		mflags |= MATCHFLG_ABS_PATH;
		if (*pat == '/')
