{
		case ARCHIVE_ENTRY_ACL_TYPE_ALLOW:
			strcpy(*p, "allow");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DENY:
			strcpy(*p, "deny");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_AUDIT:
			strcpy(*p, "audit");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ALARM:
			strcpy(*p, "alarm");
			break;
		}