(i = 0; i < 6; i++) {
		if (tace[i].a_access_mask != 0) {
			ace = &((ace_t *)acl->acl_aclp)[p];
			/*
			 * Illumos added ACE_DELETE_CHILD to write perms for
			 * directories. We have to check against that, too.
			 */
			if (ace->a_flags != tace[i].a_flags ||
			    ace->a_type != tace[i].a_type ||
			    (ace->a_access_mask != tace[i].a_access_mask &&
			    ((acl->acl_flags & ACL_IS_DIR) == 0 ||
			    (tace[i].a_access_mask & wperm) == 0 ||
			    ace->a_access_mask !=
			    (tace[i].a_access_mask | ACE_DELETE_CHILD))))
				return (0);
			p++;
		}
	}