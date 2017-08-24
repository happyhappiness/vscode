(idtype == ID_TYPE_UID) {
		*ae_tag = ARCHIVE_ENTRY_ACL_USER;
		pwd = getpwuuid(q);
		if (pwd == NULL) {
			*ae_id = ugid;
			*ae_name = NULL;
		} else {
			*ae_id = pwd->pw_uid;
			*ae_name = archive_read_disk_uname(a, *ae_id);
		}
	} else if (idtype == ID_TYPE_GID) {
		*ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
		grp = getgruuid(q);
		if (grp == NULL) {
			*ae_id = ugid;
			*ae_name = NULL;
		} else {
			*ae_id = grp->gr_gid;
			*ae_name = archive_read_disk_gname(a, *ae_id);
		}
	} else
		r = 1