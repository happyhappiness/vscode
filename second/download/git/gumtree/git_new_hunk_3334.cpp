
		strbuf_branchname(&bname, argv[i]);
		free(name);
		name = mkpathdup(fmt, bname.buf);

		if (kinds == FILTER_REFS_BRANCHES) {
			const struct worktree *wt =
				find_shared_symref("HEAD", name);
			if (wt) {
				error(_("Cannot delete branch '%s' "
					"checked out at '%s'"),
				      bname.buf, wt->path);
				ret = 1;
				continue;
			}
		}

		target = resolve_ref_unsafe(name,
