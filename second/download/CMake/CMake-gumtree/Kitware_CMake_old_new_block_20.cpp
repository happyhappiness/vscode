{
			case ACL_ENTRY_TYPE_ALLOW:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
				break;
			case ACL_ENTRY_TYPE_DENY:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
				break;
			case ACL_ENTRY_TYPE_AUDIT:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_AUDIT;
				break;
			case ACL_ENTRY_TYPE_ALARM:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
				break;
			default:
				archive_set_error(&a->archive, errno,
				    "Invalid NFSv4 ACL entry type");
				return (ARCHIVE_WARN);
			}