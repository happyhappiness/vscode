SMB_ACL_T sys_acl_init(int count)
{
	SMB_ACL_T	a;

	if (count < 0) {
		errno = EINVAL;
		return NULL;
	}

	if ((a = (SMB_ACL_T)SMB_MALLOC(sizeof a[0] + sizeof (struct acl))) == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	a->next = -1;
	a->freeaclp = False;
	a->aclp = (struct acl *)((char *)a + sizeof a[0]);
	a->aclp->acl_cnt = 0;

	return a;
}