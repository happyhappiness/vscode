{
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			acl->mode &= ~0700;
			acl->mode |= (permset & 7) << 6;
			return (0);
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			acl->mode &= ~0070;
			acl->mode |= (permset & 7) << 3;
			return (0);
		case ARCHIVE_ENTRY_ACL_OTHER:
			acl->mode &= ~0007;
			acl->mode |= permset & 7;
			return (0);
		}