static void send_file_entry(struct file_struct *file, int f)
{
	unsigned short flags;
	static time_t modtime;
	static mode_t mode;
	static int64 dev;
	static dev_t rdev;
	static uint32 rdev_major;
	static uid_t uid;
	static gid_t gid;
	static char lastname[MAXPATHLEN];
	char fname[MAXPATHLEN];
	int l1, l2;

	if (f < 0)
		return;

	if (!file) {
		write_byte(f, 0);
		modtime = 0, mode = 0;
		dev = 0, rdev = makedev(0, 0);
		rdev_major = 0;
		uid = 0, gid = 0;
		*lastname = '\0';
		return;
	}

	io_write_phase = "send_file_entry";

	f_name(file, fname);

	flags = file->flags & XMIT_TOP_DIR;

	if (file->mode == mode)
		flags |= XMIT_SAME_MODE;
	else
		mode = file->mode;
	if ((preserve_devices && IS_DEVICE(mode))
	 || (preserve_specials && IS_SPECIAL(mode))) {
		if (protocol_version < 28) {
			if (file->u.rdev == rdev)
				flags |= XMIT_SAME_RDEV_pre28;
			else
				rdev = file->u.rdev;
		} else {
			rdev = file->u.rdev;
			if ((uint32)major(rdev) == rdev_major)
				flags |= XMIT_SAME_RDEV_MAJOR;
			else
				rdev_major = major(rdev);
			if ((uint32)minor(rdev) <= 0xFFu)
				flags |= XMIT_RDEV_MINOR_IS_SMALL;
		}
	} else if (protocol_version < 28)
		rdev = makedev(0, 0);
	if (file->uid == uid)
		flags |= XMIT_SAME_UID;
	else
		uid = file->uid;
	if (file->gid == gid)
		flags |= XMIT_SAME_GID;
	else
		gid = file->gid;
	if (file->modtime == modtime)
		flags |= XMIT_SAME_TIME;
	else
		modtime = file->modtime;

#ifdef SUPPORT_HARD_LINKS
	if (file->link_u.idev) {
		if (file->F_DEV == dev) {
			if (protocol_version >= 28)
				flags |= XMIT_SAME_DEV;
		} else
			dev = file->F_DEV;
		flags |= XMIT_HAS_IDEV_DATA;
	}
#endif

	for (l1 = 0;
	    lastname[l1] && (fname[l1] == lastname[l1]) && (l1 < 255);
	    l1++) {}
	l2 = strlen(fname+l1);

	if (l1 > 0)
		flags |= XMIT_SAME_NAME;
	if (l2 > 255)
		flags |= XMIT_LONG_NAME;

	/* We must make sure we don't send a zero flag byte or the
	 * other end will terminate the flist transfer.  Note that
	 * the use of XMIT_TOP_DIR on a non-dir has no meaning, so
	 * it's harmless way to add a bit to the first flag byte. */
	if (protocol_version >= 28) {
		if (!flags && !S_ISDIR(mode))
			flags |= XMIT_TOP_DIR;
		if ((flags & 0xFF00) || !flags) {
			flags |= XMIT_EXTENDED_FLAGS;
			write_byte(f, flags);
			write_byte(f, flags >> 8);
		} else
			write_byte(f, flags);
	} else {
		if (!(flags & 0xFF))
			flags |= S_ISDIR(mode) ? XMIT_LONG_NAME : XMIT_TOP_DIR;
		write_byte(f, flags);
	}
	if (flags & XMIT_SAME_NAME)
		write_byte(f, l1);
	if (flags & XMIT_LONG_NAME)
		write_int(f, l2);
	else
		write_byte(f, l2);
	write_buf(f, fname + l1, l2);

	write_longint(f, file->length);
	if (!(flags & XMIT_SAME_TIME))
		write_int(f, modtime);
	if (!(flags & XMIT_SAME_MODE))
		write_int(f, to_wire_mode(mode));
	if (preserve_uid && !(flags & XMIT_SAME_UID)) {
		if (!numeric_ids)
			add_uid(uid);
		write_int(f, uid);
	}
	if (preserve_gid && !(flags & XMIT_SAME_GID)) {
		if (!numeric_ids)
			add_gid(gid);
		write_int(f, gid);
	}
	if ((preserve_devices && IS_DEVICE(mode))
	 || (preserve_specials && IS_SPECIAL(mode))) {
		if (protocol_version < 28) {
			if (!(flags & XMIT_SAME_RDEV_pre28))
				write_int(f, (int)rdev);
		} else {
			if (!(flags & XMIT_SAME_RDEV_MAJOR))
				write_int(f, major(rdev));
			if (flags & XMIT_RDEV_MINOR_IS_SMALL)
				write_byte(f, minor(rdev));
			else
				write_int(f, minor(rdev));
		}
	}

#ifdef SUPPORT_LINKS
	if (preserve_links && S_ISLNK(mode)) {
		int len = strlen(file->u.link);
		write_int(f, len);
		write_buf(f, file->u.link, len);
	}
#endif

#ifdef SUPPORT_HARD_LINKS
	if (flags & XMIT_HAS_IDEV_DATA) {
		if (protocol_version < 26) {
			/* 32-bit dev_t and ino_t */
			write_int(f, dev);
			write_int(f, file->F_INODE);
		} else {
			/* 64-bit dev_t and ino_t */
			if (!(flags & XMIT_SAME_DEV))
				write_longint(f, dev);
			write_longint(f, file->F_INODE);
		}
	}
#endif

	if (always_checksum && (S_ISREG(mode) || protocol_version < 28)) {
		char *sum;
		if (S_ISREG(mode))
			sum = file->u.sum;
		else {
			/* Prior to 28, we sent a useless set of nulls. */
			sum = empty_sum;
		}
		write_buf(f, sum, checksum_len);
	}

	strlcpy(lastname, fname, MAXPATHLEN);

	io_write_phase = "unknown";
}