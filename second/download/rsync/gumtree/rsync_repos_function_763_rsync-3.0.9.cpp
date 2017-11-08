SMB_ACL_T sys_acl_init( int count)
{
	struct acl_entry_link *theacl = NULL;
 
	if (count < 0) {
		errno = EINVAL;
		return NULL;
	}

	DEBUG(10,("Entering sys_acl_init\n"));

	theacl = SMB_MALLOC_P(struct acl_entry_link);
	if(theacl == NULL) {
		errno = ENOMEM;
		DEBUG(0,("Error in sys_acl_init is %d\n",errno));
		return(NULL);
	}

	theacl->count = 0;
	theacl->nextp = NULL;
	theacl->prevp = NULL;
	theacl->entryp = NULL;
	DEBUG(10,("Exiting sys_acl_init\n"));
	return(theacl);
}