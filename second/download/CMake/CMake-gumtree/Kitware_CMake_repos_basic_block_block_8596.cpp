(i = 0; i < nfsv4_acl_flag_map_size; i++) {
			if (perm & nfsv4_acl_flag_map[i].perm)
				*(*wp)++ = nfsv4_acl_flag_map[i].wc;
			else if ((flags & ARCHIVE_ENTRY_ACL_STYLE_COMPACT) == 0)
				*(*wp)++ = L'-';
		}