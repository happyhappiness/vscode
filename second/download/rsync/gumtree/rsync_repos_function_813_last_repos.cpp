int sys_acl_get_entry( SMB_ACL_T theacl, int entry_id, SMB_ACL_ENTRY_T *entry_p)
{
	struct acl_entry_link *link;
	struct new_acl_entry *entry;
	int keep_going;

	if (entry_id == SMB_ACL_FIRST_ENTRY)
		theacl->count = 0;
	else if (entry_id != SMB_ACL_NEXT_ENTRY) {
		errno = EINVAL;
		return -1;
	}

	DEBUG(10,("This is the count: %d\n",theacl->count));

	/* Check if count was previously set to -1. *
	 * If it was, that means we reached the end *
	 * of the acl last time.                    */
	if(theacl->count == -1)
		return(0);

	link = theacl;
	/* To get to the next acl, traverse linked list until index *
	 * of acl matches the count we are keeping.  This count is  *
	 * incremented each time we return an acl entry.            */

	for(keep_going = 0; keep_going < theacl->count; keep_going++)
		link = link->nextp;

	entry = *entry_p =  link->entryp;

	DEBUG(10,("*entry_p is %d\n",entry_p));
	DEBUG(10,("*entry_p->ace_access is %d\n",entry->ace_access));

	/* Increment count */
	theacl->count++;
	if(link->nextp == NULL)
		theacl->count = -1;

	return(1);
}