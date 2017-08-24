(tag == ARCHIVE_ENTRY_ACL_USER
		    || tag == ARCHIVE_ENTRY_ACL_GROUP) {
			append_id_w(wp, id);
			if ((type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) == 0)
				id = -1;
		}