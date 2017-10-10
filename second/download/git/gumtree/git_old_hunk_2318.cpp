			; /* silently ignore */
		} else {
			if (S_ISDIR(st.st_mode)) {
				strbuf_addch(name, '/');
				retval = do_for_each_reflog(name, fn, cb_data);
			} else {
				unsigned char sha1[20];
				if (read_ref_full(name->buf, 0, sha1, NULL))
					retval = error("bad ref for %s", name->buf);
				else
					retval = fn(name->buf, sha1, 0, cb_data);
			}
			if (retval)
				break;
		}
		strbuf_setlen(name, oldlen);
	}
