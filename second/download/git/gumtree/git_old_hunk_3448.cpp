		 * If CHERRY_PICK_HEAD or REVERT_HEAD indicates
		 * a single-cherry-pick in progress, abort that.
		 */
		return rollback_single_pick();
	}
	if (!f)
		return error(_("cannot open %s: %s"), git_path_head_file(),
						strerror(errno));
	if (strbuf_getline_lf(&buf, f)) {
		error(_("cannot read %s: %s"), git_path_head_file(),
		      ferror(f) ?  strerror(errno) : _("unexpected end of file"));
		fclose(f);
		goto fail;
	}
