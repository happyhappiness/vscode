static int hpux_acl_sort(int acl_count, int calclass, struct acl *aclp)
{
#if !defined(HAVE_HPUX_ACLSORT)
	/*
	 * The aclsort() system call is availabe on the latest HPUX General
	 * Patch Bundles. So for HPUX, we developed our version of acl_sort 
	 * function. Because, we don't want to update to a new 
	 * HPUX GR bundle just for aclsort() call.
	 */

	struct hpux_acl_types acl_obj_count;
	int n_class_obj_perm = 0;
	int i, j;
 
	if(!acl_count) {
		DEBUG(10,("Zero acl count passed. Returning Success\n"));
		return 0;
	}

	if(aclp == NULL) {
		DEBUG(0,("Null ACL pointer in hpux_acl_sort. Returning Failure. \n"));
		return -1;
	}

	/* Count different types of ACLs in the ACLs array */

	hpux_count_obj(acl_count, aclp, &acl_obj_count);

	/* There should be only one entry each of type USER_OBJ, GROUP_OBJ, 
	 * CLASS_OBJ and OTHER_OBJ 
	 */

	if( (acl_obj_count.n_user_obj  != 1) || 
		(acl_obj_count.n_group_obj != 1) || 
		(acl_obj_count.n_class_obj != 1) ||
		(acl_obj_count.n_other_obj != 1) 
	) {
		DEBUG(0,("hpux_acl_sort: More than one entry or no entries for \
USER OBJ or GROUP_OBJ or OTHER_OBJ or CLASS_OBJ\n"));
		return -1;
	}

	/* If any of the default objects are present, there should be only
	 * one of them each.
	 */

	if( (acl_obj_count.n_def_user_obj  > 1) || (acl_obj_count.n_def_group_obj > 1) || 
			(acl_obj_count.n_def_other_obj > 1) || (acl_obj_count.n_def_class_obj > 1) ) {
		DEBUG(0,("hpux_acl_sort: More than one entry for DEF_CLASS_OBJ \
or DEF_USER_OBJ or DEF_GROUP_OBJ or DEF_OTHER_OBJ\n"));
		return -1;
	}

	/* We now have proper number of OBJ and DEF_OBJ entries. Now sort the acl 
	 * structures.  
	 *
	 * Sorting crieteria - First sort by ACL type. If there are multiple entries of
	 * same ACL type, sort by ACL id.
	 *
	 * I am using the trival kind of sorting method here because, performance isn't 
	 * really effected by the ACLs feature. More over there aren't going to be more
	 * than 17 entries on HPUX. 
	 */

	for(i=0; i<acl_count;i++) {
		for (j=i+1; j<acl_count; j++) {
			if( aclp[i].a_type > aclp[j].a_type ) {
				/* ACL entries out of order, swap them */

				hpux_swap_acl_entries((aclp+i), (aclp+j));

			} else if ( aclp[i].a_type == aclp[j].a_type ) {

				/* ACL entries of same type, sort by id */

				if(aclp[i].a_id > aclp[j].a_id) {
					hpux_swap_acl_entries((aclp+i), (aclp+j));
				} else if (aclp[i].a_id == aclp[j].a_id) {
					/* We have a duplicate entry. */
					if(hpux_prohibited_duplicate_type(aclp[i].a_type)) {
						DEBUG(0, ("hpux_acl_sort: Duplicate entry: Type(hex): %x Id: %d\n",
							aclp[i].a_type, aclp[i].a_id));
						return -1;
					}
				}

			}
		}
	}

	/* set the class obj permissions to the computed one. */
	if(calclass) {
		int n_class_obj_index = -1;

		for(i=0;i<acl_count;i++) {
			n_class_obj_perm |= hpux_get_needed_class_perm((aclp+i));

			if(aclp[i].a_type == CLASS_OBJ)
				n_class_obj_index = i;
		}
		aclp[n_class_obj_index].a_perm = n_class_obj_perm;
	}

	return 0;
#else
	return aclsort(acl_count, calclass, aclp);
#endif
}