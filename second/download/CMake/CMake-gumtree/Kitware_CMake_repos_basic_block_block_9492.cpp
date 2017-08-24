{
			acl_free(acl);
			acl = NULL;
			/*
			 * Simultaneous NFSv4 and POSIX.1e ACLs for the same
			 * entry are not allowed, so we should return here
			 */
			return (ARCHIVE_OK);
		}