static void send_file_entry(struct file_struct *file, int f,
			    unsigned base_flags)
{
	unsigned char flags;
	static time_t last_time;
	static mode_t last_mode;
	static DEV64_T last_rdev;
	static uid_t last_uid;
	static gid_t last_gid;
	static char lastname[MAXPATHLEN];
	char *fname;
	int l1, l2;

	if (f == -1)
		return;

	if (!file) {
		write_byte(f, 0);
		return;
	}

	fname = f_name(file);

	flags = base_flags;

	if (file->mode == last_mode)
		flags |= SAME_MODE;
	if (file->rdev == last_rdev)
		flags |= SAME_RDEV;
	if (file->uid == last_uid)
		flags |= SAME_UID;
	if (file->gid == last_gid)
		flags |= SAME_GID;
	if (file->modtime == last_time)
		flags |= SAME_TIME;

	for (l1 = 0;
	     lastname[l1] && (fname[l1] == lastname[l1]) && (l1 < 255);
	     l1++);
	l2 = strlen(fname) - l1;

	if (l1 > 0)
		flags |= SAME_NAME;
	if (l2 > 255)
		flags |= LONG_NAME;

	/* we must make sure we don't send a zero flags byte or the other
	   end will terminate the flist transfer */
	if (flags == 0 && !S_ISDIR(file->mode))
		flags |= FLAG_DELETE;
	if (flags == 0)
		flags |= LONG_NAME;

	write_byte(f, flags);
	if (flags & SAME_NAME)
		write_byte(f, l1);
	if (flags & LONG_NAME)
		write_int(f, l2);
	else
		write_byte(f, l2);
	write_buf(f, fname + l1, l2);

	write_longint(f, file->length);
	if (!(flags & SAME_TIME))
		write_int(f, (int) file->modtime);
	if (!(flags & SAME_MODE))
		write_int(f, to_wire_mode(file->mode));
	if (preserve_uid && !(flags & SAME_UID)) {
		add_uid(file->uid);
		write_int(f, (int) file->uid);
	}
	if (preserve_gid && !(flags & SAME_GID)) {
		add_gid(file->gid);
		write_int(f, (int) file->gid);
	}
	if (preserve_devices && IS_DEVICE(file->mode)
	    && !(flags & SAME_RDEV))
		write_int(f, (int) file->rdev);

#if SUPPORT_LINKS
	if (preserve_links && S_ISLNK(file->mode)) {
		write_int(f, strlen(file->link));
		write_buf(f, file->link, strlen(file->link));
	}
#endif

#if SUPPORT_HARD_LINKS
	if (preserve_hard_links && S_ISREG(file->mode)) {
		if (remote_version < 26) {
			/* 32-bit dev_t and ino_t */
			write_int(f, (int) file->dev);
			write_int(f, (int) file->inode);
		} else {
			/* 64-bit dev_t and ino_t */
			write_longint(f, file->dev);
			write_longint(f, file->inode);
		}
	}
#endif

	if (always_checksum) {
		if (remote_version < 21) {
			write_buf(f, file->sum, 2);
		} else {
			write_buf(f, file->sum, MD4_SUM_LENGTH);
		}
	}

	last_mode = file->mode;
	last_rdev = file->rdev;
	last_uid = file->uid;
	last_gid = file->gid;
	last_time = file->modtime;

	strlcpy(lastname, fname, MAXPATHLEN);
	lastname[MAXPATHLEN - 1] = 0;
}