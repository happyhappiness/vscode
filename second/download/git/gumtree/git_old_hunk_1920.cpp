			free(tmp);
			if (errors) {
				free(real_ref);
				return -1;
			}
		}
		if (read_ref_at(real_ref, at_time, nth, sha1, NULL,
				&co_time, &co_tz, &co_cnt)) {
			if (!len) {
				if (starts_with(real_ref, "refs/heads/")) {
					str = real_ref + 11;
					len = strlen(real_ref + 11);
				} else {
					/* detached HEAD */
					str = "HEAD";
					len = 4;
				}
			}
			if (at_time)
				warning("Log for '%.*s' only goes "
					"back to %s.", len, str,
					show_date(co_time, co_tz, DATE_RFC2822));
			else {
				die("Log for '%.*s' only has %d entries.",
				    len, str, co_cnt);
			}
		}
	}

