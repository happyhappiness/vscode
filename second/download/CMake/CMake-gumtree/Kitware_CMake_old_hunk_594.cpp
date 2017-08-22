	if ((keys & F_UID) != 0)
		archive_string_sprintf(str, " uid=%jd", (intmax_t)me->uid);

	switch (me->filetype) {
	case AE_IFLNK:
		if ((keys & F_TYPE) != 0)
