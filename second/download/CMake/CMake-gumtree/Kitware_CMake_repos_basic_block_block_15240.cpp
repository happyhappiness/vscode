{
		a->pst = NULL; /* Mark stat cache as out-of-date. */
		if (p->fixup & TODO_TIMES) {
			set_times(a, INVALID_HANDLE_VALUE, p->mode, p->name,
			    p->atime, p->atime_nanos,
			    p->birthtime, p->birthtime_nanos,
			    p->mtime, p->mtime_nanos,
			    p->ctime, p->ctime_nanos);
		}
		if (p->fixup & TODO_MODE_BASE)
			la_chmod(p->name, p->mode);
		if (p->fixup & TODO_ACLS)
			set_acls(a, INVALID_HANDLE_VALUE, p->name, &p->acl);
		next = p->next;
		archive_acl_clear(&p->acl);
		free(p->name);
		free(p);
		p = next;
	}