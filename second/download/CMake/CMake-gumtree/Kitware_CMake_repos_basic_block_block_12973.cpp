{
		/* Collect the next group of (up to) four characters. */
		int v = 0;
		int group_size = 0;
		while (group_size < 4 && len > 0) {
			/* '=' or '_' padding indicates final group. */
			if (*src == '=' || *src == '_') {
				len = 0;
				break;
			}
			/* Skip illegal characters (including line breaks) */
			if (*src > 127 || *src < 32
			    || decode_table[*src] == 0xff) {
				len--;
				src++;
				continue;
			}
			v <<= 6;
			v |= decode_table[*src++];
			len --;
			group_size++;
		}
		/* Align a short group properly. */
		v <<= 6 * (4 - group_size);
		/* Unpack the group we just collected. */
		switch (group_size) {
		case 4: d[2] = v & 0xff;
			/* FALLTHROUGH */
		case 3: d[1] = (v >> 8) & 0xff;
			/* FALLTHROUGH */
		case 2: d[0] = (v >> 16) & 0xff;
			break;
		case 1: /* this is invalid! */
			break;
		}
		d += group_size * 3 / 4;
	}