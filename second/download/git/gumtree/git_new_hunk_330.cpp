					   &c->parents->item->object, l))
				die("BUG: not unique item in first-parent chain");
			c = c->parents->item;
		}

		if (oidcmp(&c->object.oid, &sb.final->object.oid))
			die(_("--reverse --first-parent together require range along first-parent chain"));
	}

	if (is_null_oid(&sb.final->object.oid)) {
		o = sb.final->util;
		sb.final_buf = xmemdupz(o->file.ptr, o->file.size);
		sb.final_buf_size = o->file.size;
	}
	else {
		o = get_origin(&sb, sb.final, path);
		if (fill_blob_sha1_and_mode(o))
			die(_("no such path %s in %s"), path, final_commit_name);

		if (DIFF_OPT_TST(&sb.revs->diffopt, ALLOW_TEXTCONV) &&
		    textconv_object(path, o->mode, &o->blob_oid, 1, (char **) &sb.final_buf,
				    &sb.final_buf_size))
			;
		else
			sb.final_buf = read_sha1_file(o->blob_oid.hash, &type,
						      &sb.final_buf_size);

		if (!sb.final_buf)
			die(_("cannot read blob %s for path %s"),
			    oid_to_hex(&o->blob_oid),
			    path);
	}
	num_read_blob++;
	lno = prepare_lines(&sb);

	if (lno && !range_list.nr)
