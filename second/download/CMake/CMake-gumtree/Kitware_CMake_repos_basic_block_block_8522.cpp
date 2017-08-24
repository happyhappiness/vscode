(acl->acl_text != NULL) {
		free(acl->acl_text);
		acl->acl_text = NULL;
	}