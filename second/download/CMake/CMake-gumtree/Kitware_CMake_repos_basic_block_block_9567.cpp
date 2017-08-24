h(aclent->a_type) {
			case DEF_USER:
			case USER:
				ae_name = archive_read_disk_uname(&a->archive,
				    ae_id);
				ae_tag = ARCHIVE_ENTRY_ACL_USER;
				break;
			case DEF_GROUP:
			case GROUP:
				ae_name = archive_read_disk_gname(&a->archive,
				    ae_id);
				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
				break;
			case DEF_CLASS_OBJ:
			case CLASS_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_MASK;
				break;
			case DEF_USER_OBJ:
			case USER_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
				break;
			case DEF_GROUP_OBJ:
			case GROUP_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
				break;
			case DEF_OTHER_OBJ:
			case OTHER_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
				break;
			default:
				/* Unknown tag type, skip */
				continue;
			}