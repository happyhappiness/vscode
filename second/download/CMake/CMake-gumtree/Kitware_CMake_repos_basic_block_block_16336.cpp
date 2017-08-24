{
		if (!np->dir && np->rr_child == NULL) {
			p = np->identifier + np->ext_off + np->ext_len;
			if (np->ext_len == 0 && allow_period) {
				*p++ = '.';
				np->ext_len = 1;
			}
			if (np->ext_len == 1 && !allow_period) {
				*--p = '\0';
				np->ext_len = 0;
			}
			np->id_len = np->ext_off + np->ext_len;
			if (allow_vernum) {
				*p++ = ';';
				*p++ = '1';
				np->id_len += 2;
			}
			*p = '\0';
		} else
			np->id_len = np->ext_off + np->ext_len;
		np->mb_len = np->id_len;
	}