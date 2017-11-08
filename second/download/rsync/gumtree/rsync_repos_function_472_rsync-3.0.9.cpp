static uint32 recv_acl_access(int f, uchar *name_follows_ptr)
{
	uint32 access = read_varint(f);

	if (name_follows_ptr) {
		int flags = access & 3;
		access >>= 2;
		if (am_root >= 0 && access & ~SMB_ACL_VALID_NAME_BITS)
			goto value_error;
		if (flags & XFLAG_NAME_FOLLOWS)
			*name_follows_ptr = 1;
		else
			*name_follows_ptr = 0;
		if (flags & XFLAG_NAME_IS_USER)
			access |= NAME_IS_USER;
	} else if (am_root >= 0 && access & ~SMB_ACL_VALID_OBJ_BITS) {
	  value_error:
		rprintf(FERROR_XFER, "recv_acl_access: value out of range: %x\n",
			access);
		exit_cleanup(RERR_STREAMIO);
	}

	return access;
}