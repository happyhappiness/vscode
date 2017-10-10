			}
			if (!read_oneliner(&buf, rebase_path_orig_head(), 0) ||
					get_sha1_hex(buf.buf, orig)) {
				res = error(_("could not read orig-head"));
				goto cleanup_head_ref;
			}
			strbuf_reset(&buf);
			if (!read_oneliner(&buf, rebase_path_onto(), 0)) {
				res = error(_("could not read 'onto'"));
				goto cleanup_head_ref;
			}
			msg = reflog_message(opts, "finish", "%s onto %s",
				head_ref.buf, buf.buf);
