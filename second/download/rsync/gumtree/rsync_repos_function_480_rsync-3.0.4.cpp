static void send_file_entry(int f, const char *fname, struct file_struct *file,
#ifdef SUPPORT_LINKS
			    const char *symlink_name, int symlink_len,
#endif
			    int ndx, int first_ndx)
{
	static time_t modtime;
	static mode_t mode;
#ifdef SUPPORT_HARD_LINKS
	static int64 dev;
#endif
	static dev_t rdev;
	static uint32 rdev_major;
	static uid_t uid;
	static gid_t gid;
	static const char *user_name, *group_name;
	static char lastname[MAXPATHLEN];
	int first_hlink_ndx = -1;
	int l1, l2;
	int xflags;

	/* Initialize starting value of xflags. */
	if (protocol_version >= 30 && S_ISDIR(file->mode)) {
		dir_count++;
		if (file->flags & FLAG_CONTENT_DIR)
			xflags = file->flags & FLAG_TOP_DIR;
		else if (file->flags & FLAG_IMPLIED_DIR)
			xflags = XMIT_TOP_DIR | XMIT_NO_CONTENT_DIR;
		else
			xflags = XMIT_NO_CONTENT_DIR;
	} else
		xflags = file->flags & FLAG_TOP_DIR; /* FLAG_TOP_DIR == XMIT_TOP_DIR */

	if (file->mode == mode)
		xflags |= XMIT_SAME_MODE;
	else
		mode = file->mode;

	if ((preserve_devices && IS_DEVICE(mode))
	 || (preserve_specials && IS_SPECIAL(mode))) {
		if (protocol_version < 28) {
			if (tmp_rdev == rdev)
				xflags |= XMIT_SAME_RDEV_pre28;
			else
				rdev = tmp_rdev;
		} else {
			rdev = tmp_rdev;
			if ((uint32)major(rdev) == rdev_major)
				xflags |= XMIT_SAME_RDEV_MAJOR;
			else
				rdev_major = major(rdev);
			if (protocol_version < 30 && (uint32)minor(rdev) <= 0xFFu)
				xflags |= XMIT_RDEV_MINOR_8_pre30;
		}
	} else if (protocol_version < 28)
		rdev = MAKEDEV(0, 0);
	if (!preserve_uid || ((uid_t)F_OWNER(file) == uid && *lastname))
		xflags |= XMIT_SAME_UID;
	else {
		uid = F_OWNER(file);
		if (!numeric_ids) {
			user_name = add_uid(uid);
			if (inc_recurse && user_name)
				xflags |= XMIT_USER_NAME_FOLLOWS;
		}
	}
	if (!preserve_gid || ((gid_t)F_GROUP(file) == gid && *lastname))
		xflags |= XMIT_SAME_GID;
	else {
		gid = F_GROUP(file);
		if (!numeric_ids) {
			group_name = add_gid(gid);
			if (inc_recurse && group_name)
				xflags |= XMIT_GROUP_NAME_FOLLOWS;
		}
	}
	if (file->modtime == modtime)
		xflags |= XMIT_SAME_TIME;
	else
		modtime = file->modtime;

#ifdef SUPPORT_HARD_LINKS
	if (tmp_dev != 0) {
		if (protocol_version >= 30) {
			struct ht_int64_node *np = idev_find(tmp_dev, tmp_ino);
			first_hlink_ndx = (int32)(long)np->data - 1;
			if (first_hlink_ndx < 0) {
				np->data = (void*)(long)(first_ndx + ndx + 1);
				xflags |= XMIT_HLINK_FIRST;
			}
		} else {
			if (tmp_dev == dev) {
				if (protocol_version >= 28)
					xflags |= XMIT_SAME_DEV_pre30;
			} else
				dev = tmp_dev;
		}
		xflags |= XMIT_HLINKED;
	}
#endif

	for (l1 = 0;
	    lastname[l1] && (fname[l1] == lastname[l1]) && (l1 < 255);
	    l1++) {}
	l2 = strlen(fname+l1);

	if (l1 > 0)
		xflags |= XMIT_SAME_NAME;
	if (l2 > 255)
		xflags |= XMIT_LONG_NAME;

	/* We must make sure we don't send a zero flag byte or the
	 * other end will terminate the flist transfer.  Note that
	 * the use of XMIT_TOP_DIR on a non-dir has no meaning, so
	 * it's harmless way to add a bit to the first flag byte. */
	if (protocol_version >= 28) {
		if (!xflags && !S_ISDIR(mode))
			xflags |= XMIT_TOP_DIR;
		if ((xflags & 0xFF00) || !xflags) {
			xflags |= XMIT_EXTENDED_FLAGS;
			write_shortint(f, xflags);
		} else
			write_byte(f, xflags);
	} else {
		if (!(xflags & 0xFF))
			xflags |= S_ISDIR(mode) ? XMIT_LONG_NAME : XMIT_TOP_DIR;
		write_byte(f, xflags);
	}
	if (xflags & XMIT_SAME_NAME)
		write_byte(f, l1);
	if (xflags & XMIT_LONG_NAME)
		write_varint30(f, l2);
	else
		write_byte(f, l2);
	write_buf(f, fname + l1, l2);

	if (first_hlink_ndx >= 0) {
		write_varint(f, first_hlink_ndx);
		if (first_hlink_ndx >= first_ndx)
			goto the_end;
	}

	write_varlong30(f, F_LENGTH(file), 3);
	if (!(xflags & XMIT_SAME_TIME)) {
		if (protocol_version >= 30)
			write_varlong(f, modtime, 4);
		else
			write_int(f, modtime);
	}
	if (!(xflags & XMIT_SAME_MODE))
		write_int(f, to_wire_mode(mode));
	if (preserve_uid && !(xflags & XMIT_SAME_UID)) {
		if (protocol_version < 30)
			write_int(f, uid);
		else {
			write_varint(f, uid);
			if (xflags & XMIT_USER_NAME_FOLLOWS) {
				int len = strlen(user_name);
				write_byte(f, len);
				write_buf(f, user_name, len);
			}
		}
	}
	if (preserve_gid && !(xflags & XMIT_SAME_GID)) {
		if (protocol_version < 30)
			write_int(f, gid);
		else {
			write_varint(f, gid);
			if (xflags & XMIT_GROUP_NAME_FOLLOWS) {
				int len = strlen(group_name);
				write_byte(f, len);
				write_buf(f, group_name, len);
			}
		}
	}
	if ((preserve_devices && IS_DEVICE(mode))
	 || (preserve_specials && IS_SPECIAL(mode))) {
		if (protocol_version < 28) {
			if (!(xflags & XMIT_SAME_RDEV_pre28))
				write_int(f, (int)rdev);
		} else {
			if (!(xflags & XMIT_SAME_RDEV_MAJOR))
				write_varint30(f, major(rdev));
			if (protocol_version >= 30)
				write_varint(f, minor(rdev));
			else if (xflags & XMIT_RDEV_MINOR_8_pre30)
				write_byte(f, minor(rdev));
			else
				write_int(f, minor(rdev));
		}
	}

#ifdef SUPPORT_LINKS
	if (symlink_len) {
		write_varint30(f, symlink_len);
		write_buf(f, symlink_name, symlink_len);
	}
#endif

#ifdef SUPPORT_HARD_LINKS
	if (tmp_dev != 0 && protocol_version < 30) {
		if (protocol_version < 26) {
			/* 32-bit dev_t and ino_t */
			write_int(f, (int32)dev);
			write_int(f, (int32)tmp_ino);
		} else {
			/* 64-bit dev_t and ino_t */
			if (!(xflags & XMIT_SAME_DEV_pre30))
				write_longint(f, dev);
			write_longint(f, tmp_ino);
		}
	}
#endif

	if (always_checksum && (S_ISREG(mode) || protocol_version < 28)) {
		const char *sum;
		if (S_ISREG(mode))
			sum = tmp_sum;
		else {
			/* Prior to 28, we sent a useless set of nulls. */
			sum = empty_sum;
		}
		write_buf(f, sum, checksum_len);
	}

  the_end:
	strlcpy(lastname, fname, MAXPATHLEN);

	if (S_ISREG(mode) || S_ISLNK(mode))
		stats.total_size += F_LENGTH(file);
}