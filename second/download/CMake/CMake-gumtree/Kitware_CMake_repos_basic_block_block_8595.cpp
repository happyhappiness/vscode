(perm & nfsv4_acl_perm_map[i].perm)
				*(*wp)++ = nfsv4_acl_perm_map[i].wc;
			else if ((flags & ARCHIVE_ENTRY_ACL_STYLE_COMPACT) == 0)
				*(*wp)++ = L'