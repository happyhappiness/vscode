int sys_acl_create_entry( SMB_ACL_T *pacl, SMB_ACL_ENTRY_T *pentry)
{
	struct acl_entry_link *theacl;
	struct acl_entry_link *acl_entryp;
	struct acl_entry_link *temp_entry;
	int counting;

	DEBUG(10,("Entering the sys_acl_create_entry\n"));

	theacl = acl_entryp = *pacl;

	/* Get to the end of the acl before adding entry */

	for(counting=0; counting < theacl->count; counting++){
		DEBUG(10,("The acl_entryp is %d\n",acl_entryp));
		temp_entry = acl_entryp;
		acl_entryp = acl_entryp->nextp;
	}

	if(theacl->count != 0){
		temp_entry->nextp = acl_entryp = SMB_MALLOC_P(struct acl_entry_link);
		if(acl_entryp == NULL) {
			errno = ENOMEM;
			DEBUG(0,("Error in sys_acl_create_entry is %d\n",errno));
			return(-1);
		}

		DEBUG(10,("The acl_entryp is %d\n",acl_entryp));
		acl_entryp->prevp = temp_entry;
		DEBUG(10,("The acl_entryp->prevp is %d\n",acl_entryp->prevp));
	}

	*pentry = acl_entryp->entryp = SMB_MALLOC_P(struct new_acl_entry);
	if(*pentry == NULL) {
		errno = ENOMEM;
		DEBUG(0,("Error in sys_acl_create_entry is %d\n",errno));
		return(-1);
	}

	memset(*pentry,0,sizeof(struct new_acl_entry));
	acl_entryp->entryp->ace_len = sizeof(struct acl_entry);
	acl_entryp->entryp->ace_type = ACC_PERMIT;
	acl_entryp->entryp->ace_id->id_len = sizeof(struct ace_id);
	acl_entryp->nextp = NULL;
	theacl->count++;
	DEBUG(10,("Exiting sys_acl_create_entry\n"));
	return(0);
}