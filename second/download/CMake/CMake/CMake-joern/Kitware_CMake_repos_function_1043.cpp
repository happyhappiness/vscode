static int
set_acl(struct archive *a, int fd, const char *name,
    struct archive_acl *abstract_acl,
    acl_type_t acl_type, int ae_requested_type, const char *tname)
{
#if HAVE_SUN_ACL
	aclent_t	 *aclent;
	ace_t		 *ace;
	int		 e, r;
	acl_t		 *acl;
#else
	acl_t		 acl;
	acl_entry_t	 acl_entry;
	acl_permset_t	 acl_permset;
#if HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL
	acl_flagset_t	 acl_flagset;
#endif
#endif	/* HAVE_SUN_ACL */
#if HAVE_ACL_TYPE_NFS4
	int		r;
#endif
	int		 ret;
	int		 ae_type, ae_permset, ae_tag, ae_id;
#if HAVE_DARWIN_ACL
	uuid_t		ae_uuid;
#endif
	uid_t		 ae_uid;
	gid_t		 ae_gid;
	const char	*ae_name;
	int		 entries;
	int		 i;

	ret = ARCHIVE_OK;
	entries = archive_acl_reset(abstract_acl, ae_requested_type);
	if (entries == 0)
		return (ARCHIVE_OK);

#if HAVE_SUN_ACL
	acl = NULL;
	acl = malloc(sizeof(acl_t));
	if (acl == NULL) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
			"Invalid ACL type");
		return (ARCHIVE_FAILED);
	}
	if (acl_type == ACE_T)
		acl->acl_entry_size = sizeof(ace_t);
	else if (acl_type == ACLENT_T)
		acl->acl_entry_size = sizeof(aclent_t);
	else {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
			"Invalid ACL type");
		acl_free(acl);
		return (ARCHIVE_FAILED);
	}
	acl->acl_type = acl_type;
	acl->acl_cnt = entries;

	acl->acl_aclp = malloc(entries * acl->acl_entry_size);
	if (acl->acl_aclp == NULL) {
		archive_set_error(a, errno,
		    "Can't allocate memory for acl buffer");
		acl_free(acl);
		return (ARCHIVE_FAILED);
	}
#else	/* !HAVE_SUN_ACL */
	acl = acl_init(entries);
	if (acl == (acl_t)NULL) {
		archive_set_error(a, errno,
		    "Failed to initialize ACL working storage");
		return (ARCHIVE_FAILED);
	}
#endif	/* !HAVE_SUN_ACL */
#if HAVE_SUN_ACL
	e = 0;
#endif
	while (archive_acl_next(a, abstract_acl, ae_requested_type, &ae_type,
		   &ae_permset, &ae_tag, &ae_id, &ae_name) == ARCHIVE_OK) {
#if HAVE_SUN_ACL
		ace = NULL;
		aclent = NULL;
		if (acl->acl_type == ACE_T)  {
			ace = &((ace_t *)acl->acl_aclp)[e];
			ace->a_who = -1;
			ace->a_access_mask = 0;
			ace->a_flags = 0;
		} else {
			aclent = &((aclent_t *)acl->acl_aclp)[e];
			aclent->a_id = -1;
			aclent->a_type = 0;
			aclent->a_perm = 0;
		}
#else	/* !HAVE_SUN_ACL  */
#if HAVE_DARWIN_ACL
		/*
		 * Mac OS doesn't support NFSv4 ACLs for
		 * owner@, group@ and everyone@.
		 * We skip any of these ACLs found.
		 */
		if (ae_tag == ARCHIVE_ENTRY_ACL_USER_OBJ ||
		    ae_tag == ARCHIVE_ENTRY_ACL_GROUP_OBJ ||
		    ae_tag == ARCHIVE_ENTRY_ACL_EVERYONE)
			continue;
#endif
		if (acl_create_entry(&acl, &acl_entry) != 0) {
			archive_set_error(a, errno,
			    "Failed to create a new ACL entry");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}
#endif	/* !HAVE_SUN_ACL */
#if HAVE_DARWIN_ACL
		switch (ae_type) {
		case ARCHIVE_ENTRY_ACL_TYPE_ALLOW:
			acl_set_tag_type(acl_entry, ACL_EXTENDED_ALLOW);
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DENY:
			acl_set_tag_type(acl_entry, ACL_EXTENDED_DENY);
			break;
		default:
			/* We don't support any other types on MacOS */
			continue;
		}
#endif
		switch (ae_tag) {
#if HAVE_SUN_ACL
		case ARCHIVE_ENTRY_ACL_USER:
			ae_uid = archive_write_disk_uid(a, ae_name, ae_id);
			if (acl->acl_type == ACE_T)
				ace->a_who = ae_uid;
			else {
				aclent->a_id = ae_uid;
				aclent->a_type |= USER;
			}
			break;
		case ARCHIVE_ENTRY_ACL_GROUP:
			ae_gid = archive_write_disk_gid(a, ae_name, ae_id);
			if (acl->acl_type == ACE_T) {
				ace->a_who = ae_gid;
				ace->a_flags |= ACE_IDENTIFIER_GROUP;
			} else {
				aclent->a_id = ae_gid;
				aclent->a_type |= GROUP;
			}
			break;
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			if (acl->acl_type == ACE_T)
				ace->a_flags |= ACE_OWNER;
			else
				aclent->a_type |= USER_OBJ;
			break;
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			if (acl->acl_type == ACE_T) {
				ace->a_flags |= ACE_GROUP;
				ace->a_flags |= ACE_IDENTIFIER_GROUP;
			} else
				aclent->a_type |= GROUP_OBJ;
			break;
		case ARCHIVE_ENTRY_ACL_MASK:
			aclent->a_type |= CLASS_OBJ;
			break;
		case ARCHIVE_ENTRY_ACL_OTHER:
			aclent->a_type |= OTHER_OBJ;
			break;
		case ARCHIVE_ENTRY_ACL_EVERYONE:
			ace->a_flags |= ACE_EVERYONE;
			break;
#else	/* !HAVE_SUN_ACL */
		case ARCHIVE_ENTRY_ACL_USER:
			ae_uid = archive_write_disk_uid(a, ae_name, ae_id);
#if !HAVE_DARWIN_ACL	/* FreeBSD, Linux */
			acl_set_tag_type(acl_entry, ACL_USER);
			acl_set_qualifier(acl_entry, &ae_uid);
#else	/* MacOS */
			if (mbr_identifier_to_uuid(ID_TYPE_UID, &ae_uid,
			    sizeof(uid_t), ae_uuid) != 0)
				continue;
			if (acl_set_qualifier(acl_entry, &ae_uuid) != 0)
				continue;
#endif	/* HAVE_DARWIN_ACL */
			break;
		case ARCHIVE_ENTRY_ACL_GROUP:
			ae_gid = archive_write_disk_gid(a, ae_name, ae_id);
#if !HAVE_DARWIN_ACL	/* FreeBSD, Linux */
			acl_set_tag_type(acl_entry, ACL_GROUP);
			acl_set_qualifier(acl_entry, &ae_gid);
#else	/* MacOS */
			if (mbr_identifier_to_uuid(ID_TYPE_GID, &ae_gid,
			    sizeof(gid_t), ae_uuid) != 0)
				continue;
			if (acl_set_qualifier(acl_entry, &ae_uuid) != 0)
				continue;
#endif	/* HAVE_DARWIN_ACL */
			break;
#if !HAVE_DARWIN_ACL	/* FreeBSD, Linux */
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			acl_set_tag_type(acl_entry, ACL_USER_OBJ);
			break;
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			acl_set_tag_type(acl_entry, ACL_GROUP_OBJ);
			break;
		case ARCHIVE_ENTRY_ACL_MASK:
			acl_set_tag_type(acl_entry, ACL_MASK);
			break;
		case ARCHIVE_ENTRY_ACL_OTHER:
			acl_set_tag_type(acl_entry, ACL_OTHER);
			break;
#if HAVE_ACL_TYPE_NFS4	/* FreeBSD only */
		case ARCHIVE_ENTRY_ACL_EVERYONE:
			acl_set_tag_type(acl_entry, ACL_EVERYONE);
			break;
#endif
#endif	/* !HAVE_DARWIN_ACL */
#endif	/* !HAVE_SUN_ACL */
		default:
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Unknown ACL tag");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}

#if HAVE_ACL_TYPE_NFS4 || HAVE_SUN_ACL
		r = 0;
		switch (ae_type) {
#if HAVE_SUN_ACL
		case ARCHIVE_ENTRY_ACL_TYPE_ALLOW:
			if (ace != NULL)
				ace->a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
			else
				r = -1;
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DENY:
			if (ace != NULL)
				ace->a_type = ACE_ACCESS_DENIED_ACE_TYPE;
			else
				r = -1;
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_AUDIT:
			if (ace != NULL)
				ace->a_type = ACE_SYSTEM_AUDIT_ACE_TYPE;
			else
				r = -1;
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ALARM:
			if (ace != NULL)
				ace->a_type = ACE_SYSTEM_ALARM_ACE_TYPE;
			else
				r = -1;
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
			if (aclent == NULL)
				r = -1;
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
			if (aclent != NULL)
				aclent->a_type |= ACL_DEFAULT;
			else
				r = -1;
			break;
#else	/* !HAVE_SUN_ACL */
		case ARCHIVE_ENTRY_ACL_TYPE_ALLOW:
			r = acl_set_entry_type_np(acl_entry, ACL_ENTRY_TYPE_ALLOW);
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DENY:
			r = acl_set_entry_type_np(acl_entry, ACL_ENTRY_TYPE_DENY);
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_AUDIT:
			r = acl_set_entry_type_np(acl_entry, ACL_ENTRY_TYPE_AUDIT);
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ALARM:
			r = acl_set_entry_type_np(acl_entry, ACL_ENTRY_TYPE_ALARM);
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
			// These don't translate directly into the system ACL.
			break;
#endif	/* !HAVE_SUN_ACL */
		default:
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Unknown ACL entry type");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}

		if (r != 0) {
#if HAVE_SUN_ACL
			errno = EINVAL;
#endif
			archive_set_error(a, errno,
			    "Failed to set ACL entry type");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}
#endif	/* HAVE_ACL_TYPE_NFS4 || HAVE_SUN_ACL */

#if HAVE_SUN_ACL
		if (acl->acl_type == ACLENT_T) {
			if (ae_permset & ARCHIVE_ENTRY_ACL_EXECUTE)
				aclent->a_perm |= 1;
			if (ae_permset & ARCHIVE_ENTRY_ACL_WRITE)
				aclent->a_perm |= 2;
			if (ae_permset & ARCHIVE_ENTRY_ACL_READ)
				aclent->a_perm |= 4;
		} else
#else
		if (acl_get_permset(acl_entry, &acl_permset) != 0) {
			archive_set_error(a, errno,
			    "Failed to get ACL permission set");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}
		if (acl_clear_perms(acl_permset) != 0) {
			archive_set_error(a, errno,
			    "Failed to clear ACL permissions");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}
#endif	/* !HAVE_SUN_ACL */
		for (i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
			if (ae_permset & acl_perm_map[i].archive_perm) {
#if HAVE_SUN_ACL
				ace->a_access_mask |=
				    acl_perm_map[i].platform_perm;
#else
				if (acl_add_perm(acl_permset,
				    acl_perm_map[i].platform_perm) != 0) {
					archive_set_error(a, errno,
					    "Failed to add ACL permission");
					ret = ARCHIVE_FAILED;
					goto exit_free;
				}
#endif
			}
		}

#if HAVE_NFS4_ACL
#if HAVE_SUN_ACL
		if (acl_type == ACE_T)
#elif HAVE_DARWIN_ACL
		if (acl_type == ACL_TYPE_EXTENDED)
#else	/* FreeBSD */
		if (acl_type == ACL_TYPE_NFS4)
#endif
		{
#if HAVE_POSIX_ACL || HAVE_DARWIN_ACL
			/*
			 * acl_get_flagset_np() fails with non-NFSv4 ACLs
			 */
			if (acl_get_flagset_np(acl_entry, &acl_flagset) != 0) {
				archive_set_error(a, errno,
				    "Failed to get flagset from an NFSv4 ACL entry");
				ret = ARCHIVE_FAILED;
				goto exit_free;
			}
			if (acl_clear_flags_np(acl_flagset) != 0) {
				archive_set_error(a, errno,
				    "Failed to clear flags from an NFSv4 ACL flagset");
				ret = ARCHIVE_FAILED;
				goto exit_free;
			}
#endif /* HAVE_POSIX_ACL || HAVE_DARWIN_ACL */
			for (i = 0; i < (int)(sizeof(acl_inherit_map) /sizeof(acl_inherit_map[0])); ++i) {
				if (ae_permset & acl_inherit_map[i].archive_inherit) {
#if HAVE_SUN_ACL
					ace->a_flags |=
					    acl_inherit_map[i].platform_inherit;
#else	/* !HAVE_SUN_ACL */
					if (acl_add_flag_np(acl_flagset,
							acl_inherit_map[i].platform_inherit) != 0) {
						archive_set_error(a, errno,
						    "Failed to add flag to NFSv4 ACL flagset");
						ret = ARCHIVE_FAILED;
						goto exit_free;
					}
#endif	/* HAVE_SUN_ACL */
				}
			}
		}
#endif	/* HAVE_NFS4_ACL */
#if HAVE_SUN_ACL
	e++;
#endif
	}

#if HAVE_ACL_SET_FD_NP || HAVE_ACL_SET_FD || HAVE_SUN_ACL
	/* Try restoring the ACL through 'fd' if we can. */
#if HAVE_SUN_ACL || HAVE_ACL_SET_FD_NP
	if (fd >= 0)
#else	/* !HAVE_SUN_ACL && !HAVE_ACL_SET_FD_NP */
	if (fd >= 0 && acl_type == ACL_TYPE_ACCESS)
#endif
	{
#if HAVE_SUN_ACL
		if (facl_set(fd, acl) == 0)
#elif HAVE_ACL_SET_FD_NP
		if (acl_set_fd_np(fd, acl, acl_type) == 0)
#else	/* !HAVE_SUN_ACL && !HAVE_ACL_SET_FD_NP */
		if (acl_set_fd(fd, acl) == 0)
#endif
			ret = ARCHIVE_OK;
		else {
			if (errno == EOPNOTSUPP) {
				/* Filesystem doesn't support ACLs */
				ret = ARCHIVE_OK;
			} else {
				archive_set_error(a, errno,
				    "Failed to set %s acl on fd", tname);
			}
		}
	} else
#endif	/* HAVE_ACL_SET_FD_NP || HAVE_ACL_SET_FD || HAVE_SUN_ACL */
#if HAVE_SUN_ACL
	if (acl_set(name, acl) != 0)
#elif HAVE_ACL_SET_LINK_NP
	if (acl_set_link_np(name, acl_type, acl) != 0)
#else
	/* TODO: Skip this if 'name' is a symlink. */
	if (acl_set_file(name, acl_type, acl) != 0)
#endif
	{
		if (errno == EOPNOTSUPP) {
			/* Filesystem doesn't support ACLs */
			ret = ARCHIVE_OK;
		} else {
			archive_set_error(a, errno, "Failed to set %s acl",
			    tname);
			ret = ARCHIVE_WARN;
		}
	}
exit_free:
	acl_free(acl);
	return (ret);
}