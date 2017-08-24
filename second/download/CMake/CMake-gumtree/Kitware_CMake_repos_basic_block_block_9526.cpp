{
	int i, p;
	const uint32_t rperm = ACE_READ_DATA;
	const uint32_t wperm = ACE_WRITE_DATA | ACE_APPEND_DATA;
	const uint32_t eperm = ACE_EXECUTE;
	const uint32_t pubset = ACE_READ_ATTRIBUTES | ACE_READ_NAMED_ATTRS |
	    ACE_READ_ACL | ACE_SYNCHRONIZE;
	const uint32_t ownset = pubset | ACE_WRITE_ATTRIBUTES |
	    ACE_WRITE_NAMED_ATTRS | ACE_WRITE_ACL | ACE_WRITE_OWNER;

	ace_t *ace;
	ace_t tace[6];

	if (acl == NULL || trivialp == NULL)
		return (-1);

	*trivialp = 0;

	/* ACL_IS_TRIVIAL flag must be set for both POSIX.1e and NFSv4 ACLs */
	if ((acl->acl_flags & ACL_IS_TRIVIAL) == 0)
		return (0);

	/*
	 * POSIX.1e ACLs marked with ACL_IS_TRIVIAL are compatible with
	 * FreeBSD acl_is_trivial_np(). On Solaris they have 4 entries,
	 * including mask.
	 */
	if (acl->acl_type == ACLENT_T) {
		if (acl->acl_cnt == 4)
			*trivialp = 1;
		return (0);
	}

	if (acl->acl_type != ACE_T || acl->acl_entry_size != sizeof(ace_t))
		return (-1);

	/*
	 * Continue with checking NFSv4 ACLs
	 *
	 * Create list of trivial ace's to be compared
	 */

	/* owner@ allow pre */
	tace[0].a_flags = ACE_OWNER;
	tace[0].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
	tace[0].a_access_mask = 0;

	/* owner@ deny */
	tace[1].a_flags = ACE_OWNER;
	tace[1].a_type = ACE_ACCESS_DENIED_ACE_TYPE;
	tace[1].a_access_mask = 0;

	/* group@ deny */
	tace[2].a_flags = ACE_GROUP | ACE_IDENTIFIER_GROUP;
	tace[2].a_type = ACE_ACCESS_DENIED_ACE_TYPE;
	tace[2].a_access_mask = 0;

	/* owner@ allow */
	tace[3].a_flags = ACE_OWNER;
	tace[3].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
	tace[3].a_access_mask = ownset;

	/* group@ allow */
	tace[4].a_flags = ACE_GROUP | ACE_IDENTIFIER_GROUP;
	tace[4].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
	tace[4].a_access_mask = pubset;

	/* everyone@ allow */
	tace[5].a_flags = ACE_EVERYONE;
	tace[5].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
	tace[5].a_access_mask = pubset;

	/* Permissions for everyone@ */
	if (mode & 0004)
		tace[5].a_access_mask |= rperm;
	if (mode & 0002)
		tace[5].a_access_mask |= wperm;
	if (mode & 0001)
		tace[5].a_access_mask |= eperm;

	/* Permissions for group@ */
	if (mode & 0040)
		tace[4].a_access_mask |= rperm;
	else if (mode & 0004)
		tace[2].a_access_mask |= rperm;
	if (mode & 0020)
		tace[4].a_access_mask |= wperm;
	else if (mode & 0002)
		tace[2].a_access_mask |= wperm;
	if (mode & 0010)
		tace[4].a_access_mask |= eperm;
	else if (mode & 0001)
		tace[2].a_access_mask |= eperm;

	/* Permissions for owner@ */
	if (mode & 0400) {
		tace[3].a_access_mask |= rperm;
		if (!(mode & 0040) && (mode & 0004))
			tace[0].a_access_mask |= rperm;
	} else if ((mode & 0040) || (mode & 0004))
		tace[1].a_access_mask |= rperm;
	if (mode & 0200) {
		tace[3].a_access_mask |= wperm;
		if (!(mode & 0020) && (mode & 0002))
			tace[0].a_access_mask |= wperm;
	} else if ((mode & 0020) || (mode & 0002))
		tace[1].a_access_mask |= wperm;
	if (mode & 0100) {
		tace[3].a_access_mask |= eperm;
		if (!(mode & 0010) && (mode & 0001))
			tace[0].a_access_mask |= eperm;
	} else if ((mode & 0010) || (mode & 0001))
		tace[1].a_access_mask |= eperm;

	/* Check if the acl count matches */
	p = 3;
	for (i = 0; i < 3; i++) {
		if (tace[i].a_access_mask != 0)
			p++;
	}
	if (acl->acl_cnt != p)
		return (0);

	p = 0;
	for (i = 0; i < 6; i++) {
		if (tace[i].a_access_mask != 0) {
			ace = &((ace_t *)acl->acl_aclp)[p];
			/*
			 * Illumos added ACE_DELETE_CHILD to write perms for
			 * directories. We have to check against that, too.
			 */
			if (ace->a_flags != tace[i].a_flags ||
			    ace->a_type != tace[i].a_type ||
			    (ace->a_access_mask != tace[i].a_access_mask &&
			    ((acl->acl_flags & ACL_IS_DIR) == 0 ||
			    (tace[i].a_access_mask & wperm) == 0 ||
			    ace->a_access_mask !=
			    (tace[i].a_access_mask | ACE_DELETE_CHILD))))
				return (0);
			p++;
		}
	}

	*trivialp = 1;
	return (0);
}