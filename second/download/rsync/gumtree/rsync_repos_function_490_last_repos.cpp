static BOOL pack_smb_acl(SMB_ACL_T *smb_acl, const rsync_acl *racl)
{
#ifdef ACLS_NEED_MASK
	uchar mask_bits;
#endif
	size_t count;
	id_access *ida;
	const char *errfun = NULL;
	SMB_ACL_ENTRY_T entry;

	if (!(*smb_acl = sys_acl_init(calc_sacl_entries(racl)))) {
		rsyserr(FERROR_XFER, errno, "pack_smb_acl: sys_acl_init()");
		return False;
	}

#ifndef HAVE_OSX_ACLS
	COE( sys_acl_create_entry,(smb_acl, &entry) );
	COE( sys_acl_set_info,(entry, SMB_ACL_USER_OBJ, racl->user_obj & ~NO_ENTRY, 0) );
#endif

	for (ida = racl->names.idas, count = racl->names.count; count; ida++, count--) {
#ifdef SMB_ACL_NEED_SORT
		if (!(ida->access & NAME_IS_USER))
			break;
#endif
		COE( sys_acl_create_entry,(smb_acl, &entry) );
		COE( sys_acl_set_info,
		    (entry,
		     ida->access & NAME_IS_USER ? SMB_ACL_USER : SMB_ACL_GROUP,
		     ida->access & ~NAME_IS_USER, ida->id) );
	}

#ifndef HAVE_OSX_ACLS
	COE( sys_acl_create_entry,(smb_acl, &entry) );
	COE( sys_acl_set_info,(entry, SMB_ACL_GROUP_OBJ, racl->group_obj & ~NO_ENTRY, 0) );

#ifdef SMB_ACL_NEED_SORT
	for ( ; count; ida++, count--) {
		COE( sys_acl_create_entry,(smb_acl, &entry) );
		COE( sys_acl_set_info,(entry, SMB_ACL_GROUP, ida->access, ida->id) );
	}
#endif

#ifdef ACLS_NEED_MASK
	mask_bits = racl->mask_obj == NO_ENTRY ? racl->group_obj & ~NO_ENTRY : racl->mask_obj;
	COE( sys_acl_create_entry,(smb_acl, &entry) );
	COE( sys_acl_set_info,(entry, SMB_ACL_MASK, mask_bits, 0) );
#else
	if (racl->mask_obj != NO_ENTRY) {
		COE( sys_acl_create_entry,(smb_acl, &entry) );
		COE( sys_acl_set_info,(entry, SMB_ACL_MASK, racl->mask_obj, 0) );
	}
#endif

	COE( sys_acl_create_entry,(smb_acl, &entry) );
	COE( sys_acl_set_info,(entry, SMB_ACL_OTHER, racl->other_obj & ~NO_ENTRY, 0) );
#endif

#ifdef DEBUG
	if (sys_acl_valid(*smb_acl) < 0)
		rprintf(FERROR_XFER, "pack_smb_acl: warning: system says the ACL I packed is invalid\n");
#endif

	return True;

  error_exit:
	if (errfun) {
		rsyserr(FERROR_XFER, errno, "pack_smb_acl %s()", errfun);
	}
	sys_acl_free_acl(*smb_acl);
	return False;
}