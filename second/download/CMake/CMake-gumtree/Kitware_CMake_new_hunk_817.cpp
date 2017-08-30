	if ((keys & F_UID) != 0)

		archive_string_sprintf(str, " uid=%jd", (intmax_t)me->uid);



	if ((keys & F_INO) != 0)

		archive_string_sprintf(str, " inode=%jd", (intmax_t)me->ino);

	if ((keys & F_RESDEV) != 0) {

		archive_string_sprintf(str,

		    " resdevice=native,%ju,%ju",

		    (uintmax_t)me->devmajor,

		    (uintmax_t)me->devminor);

	}



	switch (me->filetype) {

	case AE_IFLNK:

		if ((keys & F_TYPE) != 0)

