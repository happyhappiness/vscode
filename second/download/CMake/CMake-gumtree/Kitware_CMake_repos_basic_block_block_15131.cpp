{
		fe = current_fixup(a, archive_entry_pathname_w(entry));
		archive_acl_copy(&fe->acl, archive_entry_acl(entry));
	}