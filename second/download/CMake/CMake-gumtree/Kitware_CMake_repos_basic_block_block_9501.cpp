(pwd == NULL) {
			*ae_id = ugid;
			*ae_name = NULL;
		} else {
			*ae_id = pwd->pw_uid;
			*ae_name = archive_read_disk_uname(a, *ae_id);
		}