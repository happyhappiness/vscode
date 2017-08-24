{
			ace = &((ace_t *)acl->acl_aclp)[e];
			ace->a_who = -1;
			ace->a_access_mask = 0;
			ace->a_flags = 0;
		}