(memcmp(s, "allow", 5) == 0)
					type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
				else if (memcmp(s, "audit", 5) == 0)
					type = ARCHIVE_ENTRY_ACL_TYPE_AUDIT;
				else if (memcmp(s, "alarm", 5) == 0)
					type = ARCHIVE_ENTRY_ACL_TYPE_ALARM