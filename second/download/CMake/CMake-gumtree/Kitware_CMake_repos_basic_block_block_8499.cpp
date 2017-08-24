{
		ap = acl->acl_head->next;
		archive_mstring_clean(&acl->acl_head->name);
		free(acl->acl_head);
		acl->acl_head = ap;
	}