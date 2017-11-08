int sys_acl_valid( SMB_ACL_T theacl )
{
	int user_obj = 0;
	int group_obj = 0;
	int other_obj = 0;
	struct acl_entry_link *acl_entry;

	for(acl_entry=theacl; acl_entry != NULL; acl_entry = acl_entry->nextp) {
		user_obj += (acl_entry->entryp->ace_id->id_type == SMB_ACL_USER_OBJ);
		group_obj += (acl_entry->entryp->ace_id->id_type == SMB_ACL_GROUP_OBJ);
		other_obj += (acl_entry->entryp->ace_id->id_type == SMB_ACL_OTHER);
	}

	DEBUG(10,("user_obj=%d, group_obj=%d, other_obj=%d\n",user_obj,group_obj,other_obj));
 
	if(user_obj != 1 || group_obj != 1 || other_obj != 1)
		return(-1); 

	return(0);
}