{
		case ARCHIVE_ENTRY_ACL_TYPE_ALLOW:
			wcscpy(*wp, L"allow");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_DENY:
			wcscpy(*wp, L"deny");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_AUDIT:
			wcscpy(*wp, L"audit");
			break;
		case ARCHIVE_ENTRY_ACL_TYPE_ALARM:
			wcscpy(*wp, L"alarm");
			break;
		default:
			break;
		}