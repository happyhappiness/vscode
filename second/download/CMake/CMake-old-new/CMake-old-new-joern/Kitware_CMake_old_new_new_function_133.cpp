static int
pax_attribute_acl(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const char *value, int type)
{
	int r;
	const char* errstr;

	switch (type) {
	case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
		errstr = "SCHILY.acl.access";
		break;
	case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
		errstr = "SCHILY.acl.default";
		break;
	case ARCHIVE_ENTRY_ACL_TYPE_NFS4:
		errstr = "SCHILY.acl.ace";
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Unknown ACL type: %d", type);
		return(ARCHIVE_FATAL);
	}

	if (tar->sconv_acl == NULL) {
		tar->sconv_acl =
		    archive_string_conversion_from_charset(
			&(a->archive), "UTF-8", 1);
		if (tar->sconv_acl == NULL)
			return (ARCHIVE_FATAL);
	}

	r = archive_acl_from_text_l(archive_entry_acl(entry), value, type,
	    tar->sconv_acl);
	if (r != ARCHIVE_OK) {
		if (r == ARCHIVE_FATAL) {
			archive_set_error(&a->archive, ENOMEM,
			    "%s %s", "Can't allocate memory for ",
			    errstr);
			return (r);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC, "%s %s", "Parse error: ", errstr);
	}
	return (r);
}