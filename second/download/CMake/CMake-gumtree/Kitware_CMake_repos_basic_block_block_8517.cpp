(id != -1 || (tag != ARCHIVE_ENTRY_ACL_USER &&
			    tag != ARCHIVE_ENTRY_ACL_GROUP)) {
				ap->permset = permset;
				return (ap);
			}