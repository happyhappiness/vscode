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
