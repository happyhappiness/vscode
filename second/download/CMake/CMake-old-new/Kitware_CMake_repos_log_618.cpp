archive_set_error(&a->archive, errno,
	    "Can't set user=%jd/group=%jd for %ls",
	    (intmax_t)a->uid, (intmax_t)a->gid, a->name);