			return (ARCHIVE_FATAL);

	}

	archive_strncpy(&(tar->localname), acl, p - acl);

	err = archive_acl_from_text_l(archive_entry_acl(entry),

	    tar->localname.s, acl_type, tar->sconv_acl);

	if (err != ARCHIVE_OK) {

		if (errno == ENOMEM) {

			archive_set_error(&a->archive, ENOMEM,

