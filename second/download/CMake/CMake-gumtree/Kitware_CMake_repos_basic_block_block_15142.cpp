(archive_entry_filetype(a->entry) == AE_IFDIR)
			a->deferred |= TODO_ACLS;
		else
			a->todo |= TODO_ACLS