int sys_acl_set_file( const char *name, SMB_ACL_TYPE_T acltype, SMB_ACL_T theacl)
{
	struct acl_entry_link *acl_entry_link = NULL;
	struct acl *file_acl = NULL;
	struct acl *file_acl_temp = NULL;
	struct acl_entry *acl_entry = NULL;
	struct ace_id *ace_id = NULL;
	uint id_type;
	uint user_id;
	uint acl_length;
	uint rc;

	DEBUG(10,("Entering sys_acl_set_file\n"));
	DEBUG(10,("File name is %s\n",name));
 
	/* AIX has no default ACL */
	if(acltype == SMB_ACL_TYPE_DEFAULT)
		return(0);

	acl_length = BUFSIZ;
	file_acl = (struct acl *)SMB_MALLOC(BUFSIZ);

	if(file_acl == NULL) {
		errno = ENOMEM;
		DEBUG(0,("Error in sys_acl_set_file is %d\n",errno));
		return(-1);
	}

	memset(file_acl,0,BUFSIZ);

	file_acl->acl_len = ACL_SIZ;
	file_acl->acl_mode = S_IXACL;

	for(acl_entry_link=theacl; acl_entry_link != NULL; acl_entry_link = acl_entry_link->nextp) {
		acl_entry_link->entryp->ace_access >>= 6;
		id_type = acl_entry_link->entryp->ace_id->id_type;

		switch(id_type) {
		case SMB_ACL_USER_OBJ:
			file_acl->u_access = acl_entry_link->entryp->ace_access;
			continue;
		case SMB_ACL_GROUP_OBJ:
			file_acl->g_access = acl_entry_link->entryp->ace_access;
			continue;
		case SMB_ACL_OTHER:
			file_acl->o_access = acl_entry_link->entryp->ace_access;
			continue;
		case SMB_ACL_MASK:
			continue;
		}

		if((file_acl->acl_len + sizeof(struct acl_entry)) > acl_length) {
			acl_length += sizeof(struct acl_entry);
			file_acl_temp = (struct acl *)SMB_MALLOC(acl_length);
			if(file_acl_temp == NULL) {
				SAFE_FREE(file_acl);
				errno = ENOMEM;
				DEBUG(0,("Error in sys_acl_set_file is %d\n",errno));
				return(-1);
			}  

			memcpy(file_acl_temp,file_acl,file_acl->acl_len);
			SAFE_FREE(file_acl);
			file_acl = file_acl_temp;
		}

		acl_entry = (struct acl_entry *)((char *)file_acl + file_acl->acl_len);
		file_acl->acl_len += sizeof(struct acl_entry);
		acl_entry->ace_len = acl_entry_link->entryp->ace_len;
		acl_entry->ace_access = acl_entry_link->entryp->ace_access;
 
		/* In order to use this, we'll need to wait until we can get denies */
		/* if(!acl_entry->ace_access && acl_entry->ace_type == ACC_PERMIT)
		acl_entry->ace_type = ACC_SPECIFY; */

		acl_entry->ace_type = ACC_SPECIFY;
 
		ace_id = acl_entry->ace_id;
 
		ace_id->id_type = acl_entry_link->entryp->ace_id->id_type;
		DEBUG(10,("The id type is %d\n",ace_id->id_type));
		ace_id->id_len = acl_entry_link->entryp->ace_id->id_len;
		memcpy(&user_id, acl_entry_link->entryp->ace_id->id_data, sizeof(uid_t));
		memcpy(acl_entry->ace_id->id_data, &user_id, sizeof(uid_t));
	}

	rc = chacl((char*)name,file_acl,file_acl->acl_len);
	DEBUG(10,("errno is %d\n",errno));
	DEBUG(10,("return code is %d\n",rc));
	SAFE_FREE(file_acl);
	DEBUG(10,("Exiting the sys_acl_set_file\n"));
	return(rc);
}