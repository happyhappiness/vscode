static int get_rsync_acl(const char *fname, rsync_acl *racl,
			 SMB_ACL_TYPE_T type, mode_t mode)
{
	SMB_ACL_T sacl;

#ifdef SUPPORT_XATTRS
	/* --fake-super support: load ACLs from an xattr. */
	if (am_root < 0) {
		char *buf;
		size_t len;
		int cnt;

		if ((buf = get_xattr_acl(fname, type == SMB_ACL_TYPE_ACCESS, &len)) == NULL)
			return 0;
		cnt = (len - 4*4) / (4+4);
		if (len < 4*4 || len != (size_t)cnt*(4+4) + 4*4) {
			free(buf);
			return -1;
		}

		racl->user_obj = IVAL(buf, 0);
		if (racl->user_obj == NO_ENTRY)
			racl->user_obj = (mode >> 6) & 7;
		racl->group_obj = IVAL(buf, 4);
		if (racl->group_obj == NO_ENTRY)
			racl->group_obj = (mode >> 3) & 7;
		racl->mask_obj = IVAL(buf, 8);
		racl->other_obj = IVAL(buf, 12);
		if (racl->other_obj == NO_ENTRY)
			racl->other_obj = mode & 7;

		if (cnt) {
			char *bp = buf + 4*4;
			id_access *ida;
			if (!(ida = racl->names.idas = new_array(id_access, cnt)))
				out_of_memory("get_rsync_acl");
			racl->names.count = cnt;
			for ( ; cnt--; ida++, bp += 4+4) {
				ida->id = IVAL(bp, 0);
				ida->access = IVAL(bp, 4);
			}
		}
		free(buf);
		return 0;
	}
#endif

	if ((sacl = sys_acl_get_file(fname, type)) != 0) {
		BOOL ok = unpack_smb_acl(sacl, racl);

		sys_acl_free_acl(sacl);
		if (!ok) {
			return -1;
		}
	} else if (no_acl_syscall_error(errno)) {
		/* ACLs are not supported, so pretend we have a basic ACL. */
		if (type == SMB_ACL_TYPE_ACCESS)
			rsync_acl_fake_perms(racl, mode);
	} else {
		rsyserr(FERROR_XFER, errno, "get_acl: sys_acl_get_file(%s, %s)",
			fname, str_acl_type(type));
		return -1;
	}

	return 0;
}