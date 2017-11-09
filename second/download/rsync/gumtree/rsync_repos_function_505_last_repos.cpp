static mode_t change_sacl_perms(SMB_ACL_T sacl, rsync_acl *racl, mode_t old_mode, mode_t mode)
{
	SMB_ACL_ENTRY_T entry;
	const char *errfun;
	int rc;

	if (S_ISDIR(mode)) {
		/* If the sticky bit is going on, it's not safe to allow all
		 * the new ACL to go into effect before it gets set. */
#ifdef SMB_ACL_LOSES_SPECIAL_MODE_BITS
		if (mode & S_ISVTX)
			mode &= ~0077;
#else
		if (mode & S_ISVTX && !(old_mode & S_ISVTX))
			mode &= ~0077;
	} else {
		/* If setuid or setgid is going off, it's not safe to allow all
		 * the new ACL to go into effect before they get cleared. */
		if ((old_mode & S_ISUID && !(mode & S_ISUID))
		 || (old_mode & S_ISGID && !(mode & S_ISGID)))
			mode &= ~0077;
#endif
	}

	errfun = "sys_acl_get_entry";
	for (rc = sys_acl_get_entry(sacl, SMB_ACL_FIRST_ENTRY, &entry);
	     rc == 1;
	     rc = sys_acl_get_entry(sacl, SMB_ACL_NEXT_ENTRY, &entry)) {
		SMB_ACL_TAG_T tag_type;
		if ((rc = sys_acl_get_tag_type(entry, &tag_type)) != 0) {
			errfun = "sys_acl_get_tag_type";
			break;
		}
		switch (tag_type) {
		case SMB_ACL_USER_OBJ:
			COE2( store_access_in_entry,((mode >> 6) & 7, entry) );
			break;
		case SMB_ACL_GROUP_OBJ:
			/* group is only empty when identical to group perms. */
			if (racl->group_obj != NO_ENTRY)
				break;
			COE2( store_access_in_entry,((mode >> 3) & 7, entry) );
			break;
		case SMB_ACL_MASK:
#ifndef HAVE_SOLARIS_ACLS
#ifndef ACLS_NEED_MASK
			/* mask is only empty when we don't need it. */
			if (racl->mask_obj == NO_ENTRY)
				break;
#endif
			COE2( store_access_in_entry,((mode >> 3) & 7, entry) );
#endif
			break;
		case SMB_ACL_OTHER:
			COE2( store_access_in_entry,(mode & 7, entry) );
			break;
		}
	}
	if (rc) {
	  error_exit:
		if (errfun) {
			rsyserr(FERROR_XFER, errno, "change_sacl_perms: %s()",
				errfun);
		}
		return (mode_t)-1;
	}

#ifdef SMB_ACL_LOSES_SPECIAL_MODE_BITS
	/* Ensure that chmod() will be called to restore any lost setid bits. */
	if (old_mode & (S_ISUID | S_ISGID | S_ISVTX)
	 && BITS_EQUAL(old_mode, mode, CHMOD_BITS))
		old_mode &= ~(S_ISUID | S_ISGID | S_ISVTX);
#endif

	/* Return the mode of the file on disk, as we will set them. */
	return (old_mode & ~ACCESSPERMS) | (mode & ACCESSPERMS);
}