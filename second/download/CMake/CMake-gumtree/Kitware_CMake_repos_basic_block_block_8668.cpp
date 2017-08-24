{
			case 4:
				if (memcmp(s, "user", 4) == 0)
					tag = ARCHIVE_ENTRY_ACL_USER;
				break;
			case 5:
				if (memcmp(s, "group", 5) == 0)
					tag = ARCHIVE_ENTRY_ACL_GROUP;
				break;
			case 6:
				if (memcmp(s, "owner@", 6) == 0)
					tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
				else if (memcmp(s, "group@", 6) == 0)
					tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
				break;
			case 9:
				if (memcmp(s, "everyone@", 9) == 0)
					tag = ARCHIVE_ENTRY_ACL_EVERYONE;
				break;
			default:
				break;
			}