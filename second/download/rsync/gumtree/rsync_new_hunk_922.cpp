				out_of_memory("rsync_xal_get");
			*ptr = XSTATE_ABBREV;
			sum_end(ptr + 1);
		} else
			name_offset = datum_len;

		rxa = EXPAND_ITEM_LIST(xalp, rsync_xa, RSYNC_XAL_INITIAL);
		rxa->name = ptr + name_offset;
		memcpy(rxa->name, name, name_len);
		rxa->datum = ptr;
		rxa->name_len = name_len;
		rxa->datum_len = datum_len;
