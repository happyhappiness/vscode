{
			case ACE_ACCESS_ALLOWED_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
				break;
			case ACE_ACCESS_DENIED_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
				break;
			case ACE_SYSTEM_AUDIT_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
				break;
			case ACE_SYSTEM_ALARM_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
				break;
			default:
				/* Unknown entry type, skip */
				continue;
			}