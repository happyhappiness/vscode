{
	case ARCHIVE_ENTRY_ACL_USER_OBJ:
		name = NULL;
		id = -1;
		if ((type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			strcpy(*p, "owner@");
			break;
		}
		/* FALLTHROUGH */
	case ARCHIVE_ENTRY_ACL_USER:
		strcpy(*p, "user");
		break;
	case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
		name = NULL;
		id = -1;
		if ((type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			strcpy(*p, "group@");
			break;
		}
		/* FALLTHROUGH */
	case ARCHIVE_ENTRY_ACL_GROUP:
		strcpy(*p, "group");
		break;
	case ARCHIVE_ENTRY_ACL_MASK:
		strcpy(*p, "mask");
		name = NULL;
		id = -1;
		break;
	case ARCHIVE_ENTRY_ACL_OTHER:
		strcpy(*p, "other");
		name = NULL;
		id = -1;
		break;
	case ARCHIVE_ENTRY_ACL_EVERYONE:
		strcpy(*p, "everyone@");
		name = NULL;
		id = -1;
		break;
	}