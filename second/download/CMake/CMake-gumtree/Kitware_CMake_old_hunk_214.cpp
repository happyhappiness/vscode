}
#endif


#ifdef HAVE_POSIX_ACL
static int translate_acl(struct archive_read_disk *a,
    struct archive_entry *entry, acl_t acl, int archive_entry_acl_type);

static int
setup_acls(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	const char	*accpath;
	acl_t		 acl;
#if HAVE_ACL_IS_TRIVIAL_NP
	int		r;
#endif

	accpath = archive_entry_sourcepath(entry);
	if (accpath == NULL)
		accpath = archive_entry_pathname(entry);

	archive_entry_acl_clear(entry);

#ifdef ACL_TYPE_NFS4
	/* Try NFS4 ACL first. */
	if (*fd >= 0)
		acl = acl_get_fd(*fd);
#if HAVE_ACL_GET_LINK_NP
	else if (!a->follow_symlinks)
		acl = acl_get_link_np(accpath, ACL_TYPE_NFS4);
#else
	else if ((!a->follow_symlinks)
	    && (archive_entry_filetype(entry) == AE_IFLNK))
