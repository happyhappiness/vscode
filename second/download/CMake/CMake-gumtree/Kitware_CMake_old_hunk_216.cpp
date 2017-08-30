#endif

	else

		acl = acl_get_file(accpath, ACL_TYPE_ACCESS);

	if (acl != NULL) {

		translate_acl(a, entry, acl,

		    ARCHIVE_ENTRY_ACL_TYPE_ACCESS);

		acl_free(acl);

	}



	/* Only directories can have default ACLs. */

	if (S_ISDIR(archive_entry_mode(entry))) {

		acl = acl_get_file(accpath, ACL_TYPE_DEFAULT);

		if (acl != NULL) {

			translate_acl(a, entry, acl,

			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);

			acl_free(acl);

		}

	}

	return (ARCHIVE_OK);

}



/*

 * Translate system ACL into libarchive internal structure.

 */



static struct {

        int archive_perm;

        int platform_perm;

} acl_perm_map[] = {

        {ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},

        {ARCHIVE_ENTRY_ACL_WRITE, ACL_WRITE},

        {ARCHIVE_ENTRY_ACL_READ, ACL_READ},

#ifdef ACL_TYPE_NFS4

        {ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},

        {ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},

        {ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},

        {ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},

        {ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},

        {ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},

        {ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_NAMED_ATTRS},

        {ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_NAMED_ATTRS},

        {ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},

        {ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},

        {ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},

        {ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},

        {ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_ACL},

        {ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_ACL},

        {ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_WRITE_OWNER},

        {ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}

#endif

};



#ifdef ACL_TYPE_NFS4

static struct {

        int archive_inherit;

        int platform_inherit;

} acl_inherit_map[] = {

        {ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},

	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT},

	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACL_ENTRY_NO_PROPAGATE_INHERIT},

	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_INHERIT_ONLY}

};

#endif

static int

translate_acl(struct archive_read_disk *a,

    struct archive_entry *entry, acl_t acl, int default_entry_acl_type)

{

	acl_tag_t	 acl_tag;

#ifdef ACL_TYPE_NFS4

	acl_entry_type_t acl_type;

	acl_flagset_t	 acl_flagset;

	int brand, r;

#endif

	acl_entry_t	 acl_entry;

	acl_permset_t	 acl_permset;

	int		 i, entry_acl_type;

	int		 s, ae_id, ae_tag, ae_perm;

	const char	*ae_name;





#ifdef ACL_TYPE_NFS4

	// FreeBSD "brands" ACLs as POSIX.1e or NFSv4

	// Make sure the "brand" on this ACL is consistent

	// with the default_entry_acl_type bits provided.

	acl_get_brand_np(acl, &brand);

	switch (brand) {

	case ACL_BRAND_POSIX:

		switch (default_entry_acl_type) {

		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:

		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:

			break;

		default:

			// XXX set warning message?

			return ARCHIVE_FAILED;

		}

		break;

	case ACL_BRAND_NFS4:

		if (default_entry_acl_type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {

			// XXX set warning message?

			return ARCHIVE_FAILED;

		}

		break;

	default:

		// XXX set warning message?

		return ARCHIVE_FAILED;

		break;

	}

#endif





	s = acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry);

	while (s == 1) {

		ae_id = -1;

		ae_name = NULL;

		ae_perm = 0;



		acl_get_tag_type(acl_entry, &acl_tag);

		switch (acl_tag) {

		case ACL_USER:

			ae_id = (int)*(uid_t *)acl_get_qualifier(acl_entry);

			ae_name = archive_read_disk_uname(&a->archive, ae_id);

			ae_tag = ARCHIVE_ENTRY_ACL_USER;

			break;

		case ACL_GROUP:

			ae_id = (int)*(gid_t *)acl_get_qualifier(acl_entry);

			ae_name = archive_read_disk_gname(&a->archive, ae_id);

			ae_tag = ARCHIVE_ENTRY_ACL_GROUP;

			break;

		case ACL_MASK:

