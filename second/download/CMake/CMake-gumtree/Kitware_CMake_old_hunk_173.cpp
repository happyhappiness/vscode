			return (ARCHIVE_FATAL);

	}

	archive_strncpy(&(tar->localname), acl, p - acl);

	err = archive_acl_parse_l(archive_entry_acl(entry),

	    tar->localname.s, ARCHIVE_ENTRY_ACL_TYPE_ACCESS, tar->sconv_acl);

	if (err != ARCHIVE_OK) {

		if (errno == ENOMEM) {

			archive_set_error(&a->archive, ENOMEM,

