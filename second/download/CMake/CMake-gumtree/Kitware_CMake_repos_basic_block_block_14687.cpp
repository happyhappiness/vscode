{
#if HAVE_SUN_ACL
		/* Solaris writes POSIX.1e access and default ACLs together */
		ret = set_acl(a, fd, name, abstract_acl, ACLENT_T,
		    ARCHIVE_ENTRY_ACL_TYPE_POSIX1E, "posix1e");
#else	/* HAVE_POSIX_ACL */
		if ((archive_acl_types(abstract_acl)
		    & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0) {
			ret = set_acl(a, fd, name, abstract_acl,
			    ACL_TYPE_ACCESS, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
			    "access");
			if (ret != ARCHIVE_OK)
				return (ret);
		}
		if ((archive_acl_types(abstract_acl)
		    & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
			ret = set_acl(a, fd, name, abstract_acl,
			    ACL_TYPE_DEFAULT, ARCHIVE_ENTRY_ACL_TYPE_DEFAULT,
			    "default");
#endif	/* !HAVE_SUN_ACL */
		/* Simultaneous POSIX.1e and NFSv4 is not supported */
		return (ret);
	}