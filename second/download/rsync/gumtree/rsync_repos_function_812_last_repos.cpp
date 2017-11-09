int sys_acl_free_acl(SMB_ACL_T acl_d) 
{
	if (acl_d->freeaclp) {
		acl_free(acl_d->aclp);
	}
	acl_free(acl_d);
	return 0;
}