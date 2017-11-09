SMB_ACL_T sys_acl_init(int count)
{
	SMB_ACL_T	a;

	if (count < 0) {
		errno = EINVAL;
		return NULL;
	}

	/*
	 * note that since the definition of the structure pointed
	 * to by the SMB_ACL_T includes the first element of the
	 * acl[] array, this actually allocates an ACL with room
	 * for (count+1) entries
	 */
	if ((a = (SMB_ACL_T)SMB_MALLOC(sizeof a[0] + count * sizeof (struct acl))) == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	a->size = count + 1;
	a->count = 0;
	a->next = -1;

	return a;
}