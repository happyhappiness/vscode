{
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