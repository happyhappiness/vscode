			add_pax_attr(&(pax->pax_header), "SCHILY.fflags", p);

		/* I use star-compatible ACL attributes. */
		if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA |
			    ARCHIVE_ENTRY_ACL_STYLE_COMPACT);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}
		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS |
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}
		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}

		/* We use GNU-tar-compatible sparse attributes. */