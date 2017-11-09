SMB_ACL_T sys_acl_get_file( const char *path_p, SMB_ACL_TYPE_T type)
{
	struct acl *file_acl = (struct acl *)NULL;
	struct acl_entry *acl_entry;
	struct new_acl_entry *new_acl_entry;
	struct ace_id *idp;
	struct acl_entry_link *acl_entry_link;
	struct acl_entry_link *acl_entry_link_head;
	int i;
	int rc = 0;

	/* AIX has no DEFAULT */
	if  ( type == SMB_ACL_TYPE_DEFAULT ) {
#ifdef ENOTSUP
		errno = ENOTSUP;
#else
		errno = ENOSYS;
#endif
		return NULL;
	}

	/* Get the acl using statacl */
 
	DEBUG(10,("Entering sys_acl_get_file\n"));
	DEBUG(10,("path_p is %s\n",path_p));

	file_acl = (struct acl *)SMB_MALLOC(BUFSIZ);
 
	if(file_acl == NULL) {
		errno=ENOMEM;
		DEBUG(0,("Error in AIX sys_acl_get_file: %d\n",errno));
		return(NULL);
	}

	memset(file_acl,0,BUFSIZ);

	rc = statacl((char *)path_p,0,file_acl,BUFSIZ);
	if(rc == -1) {
		DEBUG(0,("statacl returned %d with errno %d\n",rc,errno));
		SAFE_FREE(file_acl);
		return(NULL);
	}

	DEBUG(10,("Got facl and returned it\n"));

	/* Point to the first acl entry in the acl */
	acl_entry =  file_acl->acl_ext;

	/* Begin setting up the head of the linked list *
	 * that will be used for the storing the acl    *
	 * in a way that is useful for the posix_acls.c *
	 * code.                                          */

	acl_entry_link_head = acl_entry_link = sys_acl_init(0);
	if(acl_entry_link_head == NULL)
		return(NULL);

	acl_entry_link->entryp = SMB_MALLOC_P(struct new_acl_entry);
	if(acl_entry_link->entryp == NULL) {
		SAFE_FREE(file_acl);
		errno = ENOMEM;
		DEBUG(0,("Error in AIX sys_acl_get_file is %d\n",errno));
		return(NULL);
	}

	DEBUG(10,("acl_entry is %d\n",acl_entry));
	DEBUG(10,("acl_last(file_acl) id %d\n",acl_last(file_acl)));

	/* Check if the extended acl bit is on.   *
	 * If it isn't, do not show the           *
	 * contents of the acl since AIX intends *
	 * the extended info to remain unused     */

	if(file_acl->acl_mode & S_IXACL){
		/* while we are not pointing to the very end */
		while(acl_entry < acl_last(file_acl)) {
			/* before we malloc anything, make sure this is  */
			/* a valid acl entry and one that we want to map */
			idp = id_nxt(acl_entry->ace_id);
			if((acl_entry->ace_type == ACC_SPECIFY ||
				(acl_entry->ace_type == ACC_PERMIT)) && (idp != id_last(acl_entry))) {
					acl_entry = acl_nxt(acl_entry);
					continue;
			}

			idp = acl_entry->ace_id;

			/* Check if this is the first entry in the linked list. *
			 * The first entry needs to keep prevp pointing to NULL *
			 * and already has entryp allocated.                  */

			if(acl_entry_link_head->count != 0) {
				acl_entry_link->nextp = SMB_MALLOC_P(struct acl_entry_link);

				if(acl_entry_link->nextp == NULL) {
					SAFE_FREE(file_acl);
					errno = ENOMEM;
					DEBUG(0,("Error in AIX sys_acl_get_file is %d\n",errno));
					return(NULL);
				}

				acl_entry_link->nextp->prevp = acl_entry_link;
				acl_entry_link = acl_entry_link->nextp;
				acl_entry_link->entryp = SMB_MALLOC_P(struct new_acl_entry);
				if(acl_entry_link->entryp == NULL) {
					SAFE_FREE(file_acl);
					errno = ENOMEM;
					DEBUG(0,("Error in AIX sys_acl_get_file is %d\n",errno));
					return(NULL);
				}
				acl_entry_link->nextp = NULL;
			}

			acl_entry_link->entryp->ace_len = acl_entry->ace_len;

			/* Don't really need this since all types are going *
			 * to be specified but, it's better than leaving it 0 */

			acl_entry_link->entryp->ace_type = acl_entry->ace_type;
 
			acl_entry_link->entryp->ace_access = acl_entry->ace_access;
 
			memcpy(acl_entry_link->entryp->ace_id,idp,sizeof(struct ace_id));

			/* The access in the acl entries must be left shifted by *
			 * three bites, because they will ultimately be compared *
			 * to S_IRUSR, S_IWUSR, and S_IXUSR.                  */

			switch(acl_entry->ace_type){
			case ACC_PERMIT:
			case ACC_SPECIFY:
				acl_entry_link->entryp->ace_access = acl_entry->ace_access;
				acl_entry_link->entryp->ace_access <<= 6;
				acl_entry_link_head->count++;
				break;
			case ACC_DENY:
				/* Since there is no way to return a DENY acl entry *
				 * change to PERM