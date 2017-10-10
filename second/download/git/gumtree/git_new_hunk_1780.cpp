				    path,
				    baselen + sublen + 1,
				    &subskip,
				    flags);
		if (subcnt < 0)
			return subcnt;
		if (!subcnt)
			die("index cache-tree records empty sub-tree");
		i += subcnt;
		sub->count = subcnt; /* to be used in the next loop */
		*skip_count += subskip;
		sub->used = 1;
	}

