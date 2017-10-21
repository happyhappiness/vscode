		}
		if (!cnt || rxa->num != num) {
			rprintf(FERROR, "[%s] could not find xattr #%d for %s\n",
				who_am_i(), num, f_name(file, NULL));
			exit_cleanup(RERR_STREAMIO);
		}
		if (!XATTR_ABBREV(*rxa) || rxa->datum[0] != XSTATE_ABBREV) {
			rprintf(FERROR, "[%s] internal abbrev error on %s (%s, len=%ld)!\n",
				who_am_i(), f_name(file, NULL), rxa->name, (long)rxa->datum_len);
			exit_cleanup(RERR_STREAMIO);
		}

		if (am_sender) {
			rxa->datum[0] = XSTATE_TODO;
			continue;
		}

		old_datum = rxa->datum;
		rxa->datum_len = read_varint(f_in);

		if (rxa->name_len + rxa->datum_len < rxa->name_len)
			overflow_exit("recv_xattr_request");
		rxa->datum = new_array(char, rxa->datum_len + rxa->name_len);
		if (!rxa->datum)
			out_of_memory("recv_xattr_request");
		name = rxa->datum + rxa->datum_len;
		memcpy(name, rxa->name, rxa->name_len);
		rxa->name = name;
