}

#endif



#if HAVE_DARWIN_ACL

static int translate_guid(struct archive *, acl_entry_t,

    int *, int *, const char **);



static void add_trivial_nfs4_acl(struct archive_entry *);

#endif



#if HAVE_SUN_ACL

static int

sun_acl_is_trivial(acl_t *, mode_t, int *trivialp);

#endif



#if HAVE_POSIX_ACL || HAVE_NFS4_ACL

static int translate_acl(struct archive_read_disk *a,

    struct archive_entry *entry,

#if HAVE_SUN_ACL

    acl_t *acl,

#else

    acl_t acl,

#endif

    int archive_entry_acl_type);



static int

setup_acls(struct archive_read_disk *a,

    struct archive_entry *entry, int *fd)

{

	const char	*accpath;

#if HAVE_SUN_ACL

	acl_t		*acl;

#else

	acl_t		acl;

#endif

	int		r;



	accpath = NULL;



#if HAVE_SUN_ACL || HAVE_DARWIN_ACL || HAVE_ACL_GET_FD_NP

	if (*fd < 0)

#else

	/* For default ACLs on Linux we need reachable accpath */

	if (*fd < 0 || S_ISDIR(archive_entry_mode(entry)))

#endif

	{

		accpath = archive_entry_sourcepath(entry);

		if (accpath == NULL || (a->tree != NULL &&

		    a->tree_enter_working_dir(a->tree) != 0))

			accpath = archive_entry_pathname(entry);

		if (accpath == NULL) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "Couldn't determine file path to read ACLs");

			return (ARCHIVE_WARN);

		}

		if (a->tree != NULL &&

#if !HAVE_SUN_ACL && !HAVE_DARWIN_ACL && !HAVE_ACL_GET_FD_NP

		    *fd < 0 &&

#endif

		    (a->follow_symlinks ||

		    archive_entry_filetype(entry) != AE_IFLNK)) {

			*fd = a->open_on_current_dir(a->tree,

			    accpath, O_RDONLY | O_NONBLOCK);

		}

	}



	archive_entry_acl_clear(entry);



	acl = NULL;



#if HAVE_NFS4_ACL

	/* Try NFSv4 ACL first. */

	if (*fd >= 0)

#if HAVE_SUN_ACL

		/* Solaris reads both POSIX.1e and NFSv4 ACL here */

		facl_get(*fd, 0, &acl);

#elif HAVE_ACL_GET_FD_NP

		acl = acl_get_fd_np(*fd, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);

#else

		acl = acl_get_fd(*fd);

#endif

#if HAVE_ACL_GET_LINK_NP

	else if (!a->follow_symlinks)

		acl = acl_get_link_np(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);

#else

	else if ((!a->follow_symlinks)

	    && (archive_entry_filetype(entry) == AE_IFLNK))

