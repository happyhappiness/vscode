			else if (len == 1)
				early = 1; /* "name~" is "name~1"! */
		}
	}
	if (len) {
		struct strbuf truname = STRBUF_INIT;
		strbuf_addf(&truname, "refs/heads/%s", remote);
		strbuf_setlen(&truname, truname.len - len);
		if (ref_exists(truname.buf)) {
			strbuf_addf(msg,
				    "%s\t\tbranch '%s'%s of .\n",
				    sha1_to_hex(remote_head->object.sha1),
				    truname.buf + 11,
				    (early ? " (early part)" : ""));
			strbuf_release(&truname);
			goto cleanup;
		}
		strbuf_release(&truname);
	}

	if (remote_head->util) {
		struct merge_remote_desc *desc;
		desc = merge_remote_util(remote_head);
		if (desc && desc->obj && desc->obj->type == OBJ_TAG) {
