static int acl_sort(SMB_ACL_T acl_d)
{
	int fixmask = (acl_d->count <= 4);

	if (hpux_acl_sort(acl_d->count, fixmask, acl_d->acl) != 0) {
		errno = EINVAL;
		return -1;
	}
	return 0;
}