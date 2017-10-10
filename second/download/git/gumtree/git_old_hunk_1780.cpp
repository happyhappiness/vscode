				    path,
				    baselen + sublen + 1,
				    &subskip,
				    flags);
		if (subcnt < 0)
			return subcnt;
		i += subcnt;
		sub->count = subcnt; /* to be used in the next loop */
		*skip_count += subskip;
		sub->used = 1;
	}

