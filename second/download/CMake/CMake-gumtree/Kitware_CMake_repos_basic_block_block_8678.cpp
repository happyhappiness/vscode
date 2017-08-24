{
			case 'u':
				if (len == 1 || (len == 4
				    && memcmp(st, "ser", 3) == 0))
					tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
				break;
			case 'g':
				if (len == 1 || (len == 5
				    && memcmp(st, "roup", 4) == 0))
					tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
				break;
			case 'o':
				if (len == 1 || (len == 5
				    && memcmp(st, "ther", 4) == 0))
					tag = ARCHIVE_ENTRY_ACL_OTHER;
				break;
			case 'm':
				if (len == 1 || (len == 4
				    && memcmp(st, "ask", 3) == 0))
					tag = ARCHIVE_ENTRY_ACL_MASK;
				break;
			default:
					break;
			}