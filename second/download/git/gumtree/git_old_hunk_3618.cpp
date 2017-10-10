				      bname.buf, wt->path);
				ret = 1;
				continue;
			}
		}

		target = resolve_ref_unsafe(name,
					    RESOLVE_REF_READING
					    | RESOLVE_REF_NO_RECURSE
					    | RESOLVE_REF_ALLOW_BAD_NAME,
					    sha1, &flags);
		if (!target) {
			error(remote_branch
			      ? _("remote-tracking branch '%s' not found.")
			      : _("branch '%s' not found."), bname.buf);
			ret = 1;
			continue;
		}

		if (!(flags & (REF_ISSYMREF|REF_ISBROKEN)) &&
		    check_branch_commit(bname.buf, name, sha1, head_rev, kinds,
					force)) {
			ret = 1;
			continue;
		}

		if (delete_ref(name, is_null_sha1(sha1) ? NULL : sha1,
			       REF_NODEREF)) {
			error(remote_branch
			      ? _("Error deleting remote-tracking branch '%s'")
			      : _("Error deleting branch '%s'"),
			      bname.buf);
			ret = 1;
			continue;
		}
		if (!quiet) {
			printf(remote_branch
			       ? _("Deleted remote-tracking branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISBROKEN) ? "broken"
			       : (flags & REF_ISSYMREF) ? target
			       : find_unique_abbrev(sha1, DEFAULT_ABBREV));
		}
		delete_branch_config(bname.buf);
	}

	free(name);

	return(ret);
}
