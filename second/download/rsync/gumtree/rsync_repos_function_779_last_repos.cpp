int sys_acl_set_file(const char *name, SMB_ACL_TYPE_T type, SMB_ACL_T acl_d)
{
	struct stat	s;
	struct acl	*acl_p;
	int		acl_count;
	struct acl	*acl_buf	= NULL;
	int		ret;

	if (type != SMB_ACL_TYPE_ACCESS && type != SMB_ACL_TYPE_DEFAULT) {
		errno = EINVAL;
		return -1;
	}

	if (acl_sort(acl_d) != 0) {
		return -1;
	}

	acl_p		= &acl_d->acl[0];
	acl_count	= acl_d->count;

	/*
	 * if it's a directory there is extra work to do
	 * since the acl() system call will replace both
	 * the access ACLs and the default ACLs (if any)
	 */
	if (stat(name, &s) != 0) {
		return -1;
	}
	if (S_ISDIR(s.st_mode)) {
		SMB_ACL_T	acc_acl;
		SMB_ACL_T	def_acl;
		SMB_ACL_T	tmp_acl;
		int		i;

		if (type == SMB_ACL_TYPE_ACCESS) {
			acc_acl = acl_d;
			def_acl = tmp_acl = sys_acl_get_file(name, SMB_ACL_TYPE_DEFAULT);

		} else {
			def_acl = acl_d;
			acc_acl = tmp_acl = sys_acl_get_file(name, SMB_ACL_TYPE_ACCESS);
		}

		if (tmp_acl == NULL) {
			return -1;
		}

		/*
		 * allocate a temporary buffer for the complete ACL
		 */
		acl_count = acc_acl->count + def_acl->count;
		acl_p = acl_buf = SMB_MALLOC_ARRAY(struct acl, acl_count);

		if (acl_buf == NULL) {
			sys_acl_free_acl(tmp_acl);
			errno = ENOMEM;
			return -1;
		}

		/*
		 * copy the access control and default entries into the buffer
		 */
		memcpy(&acl_buf[0], &acc_acl->acl[0],
			acc_acl->count * sizeof(acl_buf[0]));

		memcpy(&acl_buf[acc_acl->count], &def_acl->acl[0],
			def_acl->count * sizeof(acl_buf[0]));

		/*
		 * set the ACL_DEFAULT flag on the default entries
		 */
		for (i = acc_acl->count; i < acl_count; i++) {
			acl_buf[i].a_type |= ACL_DEFAULT;
		}

		sys_acl_free_acl(tmp_acl);

	} else if (type != SMB_ACL_TYPE_ACCESS) {
		errno = EINVAL;
		return -1;
	}

	ret = acl(name, SETACL, acl_count, acl_p);

	SAFE_FREE(acl_buf);

	return ret;
}