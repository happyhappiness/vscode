			}

			if (check_refname_format(refname.buf,
						 REFNAME_ALLOW_ONELEVEL)) {
				if (!refname_is_safe(refname.buf))
					die("loose refname is dangerous: %s", refname.buf);
				hashclr(sha1);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			add_entry_to_dir(dir,
					 create_ref_entry(refname.buf, sha1, flag, 0));
		}
		strbuf_setlen(&refname, dirnamelen);
		strbuf_setlen(&path, path_baselen);
	}
	strbuf_release(&refname);
	strbuf_release(&path);
