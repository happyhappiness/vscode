{
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			*permset = (acl->mode >> 6) & 7;
			*type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			*tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
			acl->acl_state = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
			return (ARCHIVE_OK);
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			*permset = (acl->mode >> 3) & 7;
			*type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			*tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
			acl->acl_state = ARCHIVE_ENTRY_ACL_OTHER;
			return (ARCHIVE_OK);
		case ARCHIVE_ENTRY_ACL_OTHER:
			*permset = acl->mode & 7;
			*type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			*tag = ARCHIVE_ENTRY_ACL_OTHER;
			acl->acl_state = -1;
			acl->acl_p = acl->acl_head;
			return (ARCHIVE_OK);
		default:
			break;
		}