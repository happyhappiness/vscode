int sys_acl_free_acl(SMB_ACL_T posix_acl)
{
	struct acl_entry_link *acl_entry_link;

	for(acl_entry_link = posix_acl->nextp; acl_entry_link->nextp != NULL; acl_entry_link = acl_entry_link->nextp) {
		SAFE_FREE(acl_entry_link->prevp->entryp);
		SAFE_FREE(acl_entry_link->prevp);
	}

	SAFE_FREE(acl_entry_link->prevp->entryp);
	SAFE_FREE(acl_entry_link->prevp);
	SAFE_FREE(acl_entry_link->entryp);
	SAFE_FREE(acl_entry_link);
 
	return(0);
}