(sun_acl_is_trivial(acl, archive_entry_mode(entry),
		    &r) == 0 && r == 1)
#elif HAVE_ACL_IS_TRIVIAL_NP
		if (acl_is_trivial_np(acl, &r) == 0 && r == 1)
#endif
		{
			acl_free(acl);
			acl = NULL;
			/*
			 * Simultaneous NFSv4 and POSIX.1e ACLs for the same
			 * entry are not allowed, so we should return here
			 */
			return (ARCHIVE_OK);
		}