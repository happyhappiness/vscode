{
		case ARCHIVE_ENTRY_ACL_USER_OBJ:
			if (want_type == ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
				length += 6; /* "owner@" */
				break;
			}
			/* FALLTHROUGH */
		case ARCHIVE_ENTRY_ACL_USER:
		case ARCHIVE_ENTRY_ACL_MASK:
			length += 4; /* "user", "mask" */
			break;
		case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
			if (want_type == ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
				length += 6; /* "group@" */
				break;
			}
			/* FALLTHROUGH */
		case ARCHIVE_ENTRY_ACL_GROUP:
		case ARCHIVE_ENTRY_ACL_OTHER:
			length += 5; /* "group", "other" */
			break;
		case ARCHIVE_ENTRY_ACL_EVERYONE:
			length += 9; /* "everyone@" */
			break;
		}