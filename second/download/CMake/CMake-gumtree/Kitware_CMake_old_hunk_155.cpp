	case 'S':
		/* We support some keys used by the "star" archiver */
		if (strcmp(key, "SCHILY.acl.access") == 0) {
			if (tar->sconv_acl == NULL) {
				tar->sconv_acl =
				    archive_string_conversion_from_charset(
					&(a->archive), "UTF-8", 1);
				if (tar->sconv_acl == NULL)
					return (ARCHIVE_FATAL);
			}

			r = archive_acl_parse_l(archive_entry_acl(entry),
			    value, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
			    tar->sconv_acl);
			if (r != ARCHIVE_OK) {
				err = r;
				if (err == ARCHIVE_FATAL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory for "
					    "SCHILY.acl.access");
					return (err);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Parse error: SCHILY.acl.access");
			}
		} else if (strcmp(key, "SCHILY.acl.default") == 0) {
			if (tar->sconv_acl == NULL) {
				tar->sconv_acl =
				    archive_string_conversion_from_charset(
					&(a->archive), "UTF-8", 1);
				if (tar->sconv_acl == NULL)
					return (ARCHIVE_FATAL);
			}

			r = archive_acl_parse_l(archive_entry_acl(entry),
			    value, ARCHIVE_ENTRY_ACL_TYPE_DEFAULT,
			    tar->sconv_acl);
			if (r != ARCHIVE_OK) {
				err = r;
				if (err == ARCHIVE_FATAL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory for "
					    "SCHILY.acl.default");
					return (err);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Parse error: SCHILY.acl.default");
			}
		} else if (strcmp(key, "SCHILY.devmajor") == 0) {
			archive_entry_set_rdevmajor(entry,
			    (dev_t)tar_atol10(value, strlen(value)));
