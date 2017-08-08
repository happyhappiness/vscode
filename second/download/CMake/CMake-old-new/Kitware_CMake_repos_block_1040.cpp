{
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