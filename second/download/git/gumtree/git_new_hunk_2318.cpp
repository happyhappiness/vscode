			; /* silently ignore */
		} else {
			if (S_ISDIR(st.st_mode)) {
				strbuf_addch(name, '/');
				retval = do_for_each_reflog(name, fn, cb_data);
			} else {
				struct object_id oid;

				if (read_ref_full(name->buf, 0, oid.hash, NULL))
					retval = error("bad ref for %s", name->buf);
				else
					retval = fn(name->buf, &oid, 0, cb_data);
			}
			if (retval)
				break;
		}
		strbuf_setlen(name, oldlen);
	}
