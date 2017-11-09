SMB_ACL_T sys_acl_get_file(const char *path_p, SMB_ACL_TYPE_T type)
{
	SMB_ACL_T	acl_d;
	int		count;		/* # of ACL entries allocated	*/
	int		naccess;	/* # of access ACL entries	*/
	int		ndefault;	/* # of default ACL entries	*/

	if(hpux_acl_call_presence() == False) {
		/* Looks like we don't have the acl() system call on HPUX. 
		 * May be the system doesn't have the latest version of JFS.
		 */
		return NULL; 
	}

	if (type != SMB_ACL_TYPE_ACCESS && type != SMB_ACL_TYPE_DEFAULT) {
		errno = EINVAL;
		return NULL;
	}

	count = INITIAL_ACL_SIZE;
	if ((acl_d = sys_acl_init(count)) == NULL) {
		return NULL;
	}

	/*
	 * If there isn't enough space for the ACL entries we use
	 * ACL_CNT to determine the actual number of ACL entries
	 * reallocate and try again. This is in a loop because it
	 * is possible that someone else could modify the ACL and
	 * increase the number of entries between the call to
	 * ACL_CNT and the call to ACL_GET.
	 */
	while ((count = acl(path_p, ACL_GET, count, &acl_d->acl[0])) < 0 && errno == ENOSPC) {

		sys_acl_free_acl(acl_d);

		if ((count = acl(path_p, ACL_CNT, NACLENTRIES, NULL)) < 0) {
			return NULL;
		}

		if ((acl_d = sys_acl_init(count)) == NULL) {
			return NULL;
		}
	}

	if (count < 0) {
		sys_acl_free_acl(acl_d);
		return NULL;
	}

	/*
	 * calculate the number of access and default ACL entries
	 *
	 * Note: we assume that the acl() system call returned a
	 * well formed ACL which is sorted so that all of the
	 * access ACL entries preceed any default ACL entries
	 */
	for (naccess = 0; naccess < count; naccess++) {
		if (acl_d->acl[naccess].a_type & ACL_DEFAULT)
			break;
	}
	ndefault = count - naccess;
	
	/*
	 * if the caller wants the default ACL we have to copy
	 * the entries down to the start of the acl[] buffer
	 * and mask out the ACL_DEFAULT flag from the type field
	 */
	if (type == SMB_ACL_TYPE_DEFAULT) {
		int	i, j;

		for (i = 0, j = naccess; i < ndefault; i++, j++) {
			acl_d->acl[i] = acl_d->acl[j];
			acl_d->acl[i].a_type &= ~ACL_DEFAULT;
		}

		acl_d->count = ndefault;
	} else {
		acl_d->count = naccess;
	}

	return acl_d;
}