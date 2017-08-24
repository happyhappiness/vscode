{
	char *p;
	const char *attr;
	int acl_types;

	acl_types = archive_entry_acl_types(entry);

	if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0)
		attr = "SCHILY.acl.ace";
	else if ((flags & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0)
		attr = "SCHILY.acl.access";
	else if ((flags & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
		attr = "SCHILY.acl.default";
	else
		return (ARCHIVE_FATAL);

	p = archive_entry_acl_to_text_l(entry, NULL, flags, pax->sconv_utf8);
	if (p == NULL) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM, "%s %s",
			    "Can't allocate memory for ", attr);
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT, "%s %s %s",
		    "Can't translate ", attr, " to UTF-8");
		return(ARCHIVE_WARN);
	} else if (*p != '\0') {
		add_pax_attr(&(pax->pax_header),
		    attr, p);
		free(p);
	}
	return(ARCHIVE_OK);
}