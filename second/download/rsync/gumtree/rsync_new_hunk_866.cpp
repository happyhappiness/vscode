	if (filter_list.head
	    && check_filter(&filter_list, fname, is_dir) < 0)
		return 1;
	return 0;
}

static void send_directory(int f, struct file_list *flist,
			   char *fbuf, int len, int flags);

static const char *pathname, *orig_dir;
static int pathname_len;


/* Make sure flist can hold at least flist->used + extra entries. */
static void flist_expand(struct file_list *flist, int extra)
{
	struct file_struct **new_ptr;

	if (flist->used + extra <= flist->malloced)
		return;

	if (flist->malloced < FLIST_START)
		flist->malloced = FLIST_START;
	else if (flist->malloced >= FLIST_LINEAR)
		flist->malloced += FLIST_LINEAR;
	else
		flist->malloced *= 2;

	/* In case count jumped or we are starting the list
	 * with a known size just set it. */
	if (flist->malloced < flist->used + extra)
		flist->malloced = flist->used + extra;

	new_ptr = realloc_array(flist->files, struct file_struct *,
				flist->malloced);

	if (verbose >= 2 && flist->malloced != FLIST_START) {
		rprintf(FCLIENT, "[%s] expand file_list pointer array to %.0f bytes, did%s move\n",
		    who_am_i(),
		    (double)sizeof flist->files[0] * flist->malloced,
		    (new_ptr == flist->files) ? " not" : "");
	}

	flist->files = new_ptr;

	if (!flist->files)
		out_of_memory("flist_expand");
}

static void flist_done_allocating(struct file_list *flist)
{
	void *ptr = pool_boundary(flist->file_pool, 8*1024);
	if (flist->pool_boundary == ptr)
		flist->pool_boundary = NULL; /* list didn't use any pool memory */
	else
		flist->pool_boundary = ptr;
}

int push_pathname(const char *dir, int len)
{
	if (dir == pathname)
		return 1;

	if (!orig_dir)
		orig_dir = strdup(curr_dir);

	if (pathname && !pop_dir(orig_dir)) {
		rsyserr(FERROR, errno, "pop_dir %s failed",
			full_fname(orig_dir));
		exit_cleanup(RERR_FILESELECT);
	}

	if (dir && !push_dir(dir, 0)) {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR, errno, "push_dir %s failed in %s",
			full_fname(dir), curr_dir);
		return 0;
	}

	pathname = dir;
	pathname_len = len >= 0 ? len : dir ? (int)strlen(dir) : 0;

	return 1;
}

static void send_file_entry(int f, struct file_struct *file, int ndx, int first_ndx)
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
	char fname[MAXPATHLEN];
	int first_hlink_ndx = -1;
	int l1, l2;
	int xflags;

#ifdef ICONV_OPTION
	if (ic_send != (iconv_t)-1) {
		xbuf outbuf, inbuf;

		INIT_CONST_XBUF(outbuf, fname);

		if (file->dirname) {
			INIT_XBUF_STRLEN(inbuf, (char*)file->dirname);
			outbuf.size -= 2; /* Reserve room for '/' & 1 more char. */
			if (iconvbufs(ic_send, &inbuf, &outbuf, 0) < 0)
				goto convert_error;
			outbuf.size += 2;
			outbuf.buf[outbuf.len++] = '/';
		}

		INIT_XBUF_STRLEN(inbuf, (char*)file->basename);
		if (iconvbufs(ic_send, &inbuf, &outbuf, 0) < 0) {
		  convert_error:
			io_error |= IOERR_GENERAL;
			rprintf(FINFO,
			    "[%s] cannot convert filename: %s (%s)\n",
			    who_am_i(), f_name(file, fname), strerror(errno));
			return;
		}
		outbuf.buf[outbuf.len] = '\0';
	} else
#endif
		f_name(file, fname);

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
	if (preserve_uid) {
		if ((uid_t)F_OWNER(file) == uid && *lastname)
			xflags |= XMIT_SAME_UID;
		else {
			uid = F_OWNER(file);
			if (!numeric_ids) {
				user_name = add_uid(uid);
				if (inc_recurse && user_name)
					xflags |= XMIT_USER_NAME_FOLLOWS;
			}
		}
	}
	if (preserve_gid) {
		if ((gid_t)F_GROUP(file) == gid && *lastname)
			xflags |= XMIT_SAME_GID;
		else {
			gid = F_GROUP(file);
			if (!numeric_ids) {
				group_name = add_gid(gid);
				if (inc_recurse && group_name)
					xflags |= XMIT_GROUP_NAME_FOLLOWS;
			}
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
			xflags |= XMIT_HLINKED;
		} else {
			if (tmp_dev == dev) {
				if (protocol_version >= 28)
					xflags |= XMIT_SAME_DEV_pre30;
			} else
				dev = tmp_dev;
			xflags |= XMIT_HLINKED;
		}
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
	if (preserve_links && S_ISLNK(mode)) {
		const char *sl = F_SYMLINK(file);
		int len = strlen(sl);
		write_varint30(f, len);
		write_buf(f, sl, len);
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

static struct file_struct *recv_file_entry(struct file_list *flist,
					   int xflags, int f)
{
	static int64 modtime;
	static mode_t mode;
#ifdef SUPPORT_HARD_LINKS
	static int64 dev;
#endif
	static dev_t rdev;
	static uint32 rdev_major;
	static uid_t uid;
	static gid_t gid;
	static uint16 gid_flags;
	static char lastname[MAXPATHLEN], *lastdir;
	static int lastdir_depth, lastdir_len = -1;
	static unsigned int del_hier_name_len = 0;
	static int in_del_hier = 0;
	char thisname[MAXPATHLEN];
	unsigned int l1 = 0, l2 = 0;
	int alloc_len, basename_len, linkname_len;
	int extra_len = file_extra_cnt * EXTRA_LEN;
	int first_hlink_ndx = -1;
	OFF_T file_length;
	const char *basename;
	struct file_struct *file;
	alloc_pool_t *pool;
	char *bp;

	if (xflags & XMIT_SAME_NAME)
		l1 = read_byte(f);

	if (xflags & XMIT_LONG_NAME)
		l2 = read_varint30(f);
	else
		l2 = read_byte(f);

	if (l2 >= MAXPATHLEN - l1) {
		rprintf(FERROR,
			"overflow: xflags=0x%x l1=%d l2=%d lastname=%s [%s]\n",
			xflags, l1, l2, lastname, who_am_i());
		overflow_exit("recv_file_entry");
	}

	strlcpy(thisname, lastname, l1 + 1);
	read_sbuf(f, &thisname[l1], l2);
	thisname[l1 + l2] = 0;

	/* Abuse basename_len for a moment... */
	basename_len = strlcpy(lastname, thisname, MAXPATHLEN);

#ifdef ICONV_OPTION
	if (ic_recv != (iconv_t)-1) {
		xbuf outbuf, inbuf;

		INIT_CONST_XBUF(outbuf, thisname);
		INIT_XBUF(inbuf, lastname, basename_len, -1);

		if (iconvbufs(ic_recv, &inbuf, &outbuf, 0) < 0) {
			io_error |= IOERR_GENERAL;
			rprintf(FINFO,
			    "[%s] cannot convert filename: %s (%s)\n",
			    who_am_i(), lastname, strerror(errno));
			outbuf.len = 0;
		}
		outbuf.buf[outbuf.len] = '\0';
	}
#endif

	clean_fname(thisname, 0);

	if (sanitize_paths)
		sanitize_path(thisname, thisname, "", 0);

	if ((basename = strrchr(thisname, '/')) != NULL) {
		int len = basename++ - thisname;
		if (len != lastdir_len || memcmp(thisname, lastdir, len) != 0) {
			lastdir = new_array(char, len + 1);
			memcpy(lastdir, thisname, len);
			lastdir[len] = '\0';
			lastdir_len = len;
			lastdir_depth = count_dir_elements(lastdir);
		}
	} else
		basename = thisname;
	basename_len = strlen(basename) + 1; /* count the '\0' */

#ifdef SUPPORT_HARD_LINKS
	if (protocol_version >= 30
	 && BITS_SETnUNSET(xflags, XMIT_HLINKED, XMIT_HLINK_FIRST)) {
		first_hlink_ndx = read_varint(f);
		if (first_hlink_ndx < 0 || first_hlink_ndx >= flist->ndx_start + flist->used) {
			rprintf(FERROR,
				"hard-link reference out of range: %d (%d)\n",
				first_hlink_ndx, flist->ndx_start + flist->used);
			exit_cleanup(RERR_PROTOCOL);
		}
		if (first_hlink_ndx >= flist->ndx_start) {
			struct file_struct *first = flist->files[first_hlink_ndx - flist->ndx_start];
			file_length = F_LENGTH(first);
			modtime = first->modtime;
			mode = first->mode;
			if (preserve_uid)
				uid = F_OWNER(first);
			if (preserve_gid)
				gid = F_GROUP(first);
			if ((preserve_devices && IS_DEVICE(mode))
			 || (preserve_specials && IS_SPECIAL(mode))) {
				uint32 *devp = F_RDEV_P(first);
				rdev = MAKEDEV(DEV_MAJOR(devp), DEV_MINOR(devp));
				extra_len += DEV_EXTRA_CNT * EXTRA_LEN;
			}
			if (preserve_links && S_ISLNK(mode))
				linkname_len = strlen(F_SYMLINK(first)) + 1;
			else
				linkname_len = 0;
			goto create_object;
		}
	}
#endif

	file_length = read_varlong30(f, 3);
	if (!(xflags & XMIT_SAME_TIME)) {
		if (protocol_version >= 30) {
			modtime = read_varlong(f, 4);
#if SIZEOF_TIME_T < SIZEOF_INT64
			if (!am_generator && (int64)(time_t)modtime != modtime) {
				rprintf(FERROR_XFER,
				    "Time value of %s truncated on receiver.\n",
				    lastname);
			}
#endif
		} else
			modtime = read_int(f);
	}
	if (!(xflags & XMIT_SAME_MODE))
		mode = from_wire_mode(read_int(f));

	if (chmod_modes && !S_ISLNK(mode))
		mode = tweak_mode(mode, chmod_modes);

	if (preserve_uid && !(xflags & XMIT_SAME_UID)) {
		if (protocol_version < 30)
			uid = (uid_t)read_int(f);
		else {
			uid = (uid_t)read_varint(f);
			if (xflags & XMIT_USER_NAME_FOLLOWS)
				uid = recv_user_name(f, uid);
			else if (inc_recurse && am_root && !numeric_ids)
				uid = match_uid(uid);
		}
	}
	if (preserve_gid && !(xflags & XMIT_SAME_GID)) {
		if (protocol_version < 30)
			gid = (gid_t)read_int(f);
		else {
			gid = (gid_t)read_varint(f);
			gid_flags = 0;
			if (xflags & XMIT_GROUP_NAME_FOLLOWS)
				gid = recv_group_name(f, gid, &gid_flags);
			else if (inc_recurse && (!am_root || !numeric_ids))
				gid = match_gid(gid, &gid_flags);
		}
	}

	if ((preserve_devices && IS_DEVICE(mode))
	 || (preserve_specials && IS_SPECIAL(mode))) {
		if (protocol_version < 28) {
			if (!(xflags & XMIT_SAME_RDEV_pre28))
				rdev = (dev_t)read_int(f);
		} else {
			uint32 rdev_minor;
			if (!(xflags & XMIT_SAME_RDEV_MAJOR))
				rdev_major = read_varint30(f);
			if (protocol_version >= 30)
				rdev_minor = read_varint(f);
			else if (xflags & XMIT_RDEV_MINOR_8_pre30)
				rdev_minor = read_byte(f);
			else
				rdev_minor = read_int(f);
			rdev = MAKEDEV(rdev_major, rdev_minor);
		}
		extra_len += DEV_EXTRA_CNT * EXTRA_LEN;
		file_length = 0;
	} else if (protocol_version < 28)
		rdev = MAKEDEV(0, 0);

#ifdef SUPPORT_LINKS
	if (preserve_links && S_ISLNK(mode)) {
		linkname_len = read_varint30(f) + 1; /* count the '\0' */
		if (linkname_len <= 0 || linkname_len > MAXPATHLEN) {
			rprintf(FERROR, "overflow: linkname_len=%d\n",
				linkname_len - 1);
			overflow_exit("recv_file_entry");
		}
		if (munge_symlinks)
			linkname_len += SYMLINK_PREFIX_LEN;
	}
	else
#endif
		linkname_len = 0;

#ifdef SUPPORT_HARD_LINKS
  create_object:
	if (preserve_hard_links) {
		if (protocol_version < 28 && S_ISREG(mode))
			xflags |= XMIT_HLINKED;
		if (xflags & XMIT_HLINKED)
			extra_len += (inc_recurse+1) * EXTRA_LEN;
	}
#endif

#ifdef SUPPORT_ACLS
	/* We need one or two index int32s when we're preserving ACLs. */
	if (preserve_acls)
		extra_len += (S_ISDIR(mode) ? 2 : 1) * EXTRA_LEN;
#endif

	if (always_checksum && S_ISREG(mode))
		extra_len += SUM_EXTRA_CNT * EXTRA_LEN;

	if (file_length > 0xFFFFFFFFu && S_ISREG(mode))
		extra_len += EXTRA_LEN;

	if (inc_recurse && S_ISDIR(mode)) {
		if (one_file_system) {
			/* Room to save the dir's device for -x */
			extra_len += DEV_EXTRA_CNT * EXTRA_LEN;
		}
		pool = dir_flist->file_pool;
	} else
		pool = flist->file_pool;

#if EXTRA_ROUNDING > 0
	if (extra_len & (EXTRA_ROUNDING * EXTRA_LEN))
		extra_len = (extra_len | (EXTRA_ROUNDING * EXTRA_LEN)) + EXTRA_LEN;
#endif

	alloc_len = FILE_STRUCT_LEN + extra_len + basename_len
		  + linkname_len;
	bp = pool_alloc(pool, alloc_len, "recv_file_entry");

	memset(bp, 0, extra_len + FILE_STRUCT_LEN);
	bp += extra_len;
	file = (struct file_struct *)bp;
	bp += FILE_STRUCT_LEN;

	memcpy(bp, basename, basename_len);
	bp += basename_len + linkname_len; /* skip space for symlink too */

#ifdef SUPPORT_HARD_LINKS
	if (xflags & XMIT_HLINKED)
		file->flags |= FLAG_HLINKED;
#endif
	file->modtime = (time_t)modtime;
	file->len32 = (uint32)file_length;
	if (file_length > 0xFFFFFFFFu && S_ISREG(mode)) {
		file->flags |= FLAG_LENGTH64;
		OPT_EXTRA(file, 0)->unum = (uint32)(file_length >> 32);
	}
	file->mode = mode;
	if (preserve_uid)
		F_OWNER(file) = uid;
	if (preserve_gid) {
		F_GROUP(file) = gid;
		file->flags |= gid_flags;
	}
	if (unsort_ndx)
		F_NDX(file) = flist->used + flist->ndx_start;

	if (basename != thisname) {
		file->dirname = lastdir;
		F_DEPTH(file) = lastdir_depth + 1;
	} else
		F_DEPTH(file) = 1;

	if (S_ISDIR(mode)) {
		if (basename_len == 1+1 && *basename == '.') /* +1 for '\0' */
			F_DEPTH(file)--;
		if (protocol_version >= 30) {
			if (!(xflags & XMIT_NO_CONTENT_DIR)) {
				if (xflags & XMIT_TOP_DIR)
					file->flags |= FLAG_TOP_DIR;
				file->flags |= FLAG_CONTENT_DIR;
			} else if (xflags & XMIT_TOP_DIR)
				file->flags |= FLAG_IMPLIED_DIR;
		} else if (xflags & XMIT_TOP_DIR) {
			in_del_hier = recurse;
			del_hier_name_len = F_DEPTH(file) == 0 ? 0 : l1 + l2;
			if (relative_paths && del_hier_name_len > 2
			    && lastname[del_hier_name_len-1] == '.'
			    && lastname[del_hier_name_len-2] == '/')
				del_hier_name_len -= 2;
			file->flags |= FLAG_TOP_DIR | FLAG_CONTENT_DIR;
		} else if (in_del_hier) {
			if (!relative_paths || !del_hier_name_len
			 || (l1 >= del_hier_name_len
			  && lastname[del_hier_name_len] == '/'))
				file->flags |= FLAG_CONTENT_DIR;
			else
				in_del_hier = 0;
		}
	}

	if ((preserve_devices && IS_DEVICE(mode))
	 || (preserve_specials && IS_SPECIAL(mode))) {
		uint32 *devp = F_RDEV_P(file);
		DEV_MAJOR(devp) = major(rdev);
		DEV_MINOR(devp) = minor(rdev);
	}

#ifdef SUPPORT_LINKS
	if (linkname_len) {
		bp = (char*)file->basename + basename_len;
		if (first_hlink_ndx >= flist->ndx_start) {
			struct file_struct *first = flist->files[first_hlink_ndx - flist->ndx_start];
			memcpy(bp, F_SYMLINK(first), linkname_len);
		} else if (munge_symlinks) {
			strlcpy(bp, SYMLINK_PREFIX, linkname_len);
			bp += SYMLINK_PREFIX_LEN;
			linkname_len -= SYMLINK_PREFIX_LEN;
			read_sbuf(f, bp, linkname_len - 1);
		} else {
			read_sbuf(f, bp, linkname_len - 1);
			if (sanitize_paths)
				sanitize_path(bp, bp, "", lastdir_depth);
		}
	}
#endif

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && xflags & XMIT_HLINKED) {
		if (protocol_version >= 30) {
			if (xflags & XMIT_HLINK_FIRST) {
				F_HL_GNUM(file) = flist->ndx_start + flist->used;
			} else
				F_HL_GNUM(file) = first_hlink_ndx;
		} else {
			static int32 cnt = 0;
			struct ht_int64_node *np;
			int64 ino;
			int32 ndx;
			if (protocol_version < 26) {
				dev = read_int(f);
				ino = read_int(f);
			} else {
				if (!(xflags & XMIT_SAME_DEV_pre30))
					dev = read_longint(f);
				ino = read_longint(f);
			}
			np = idev_find(dev, ino);
			ndx = (int32)(long)np->data - 1;
			if (ndx < 0) {
				ndx = cnt++;
				np->data = (void*)(long)cnt;
			}
			F_HL_GNUM(file) = ndx;
		}
	}
#endif

	if (always_checksum && (S_ISREG(mode) || protocol_version < 28)) {
		if (S_ISREG(mode))
			bp = F_SUM(file);
		else {
			/* Prior to 28, we get a useless set of nulls. */
			bp = tmp_sum;
		}
		if (first_hlink_ndx >= flist->ndx_start) {
			struct file_struct *first = flist->files[first_hlink_ndx - flist->ndx_start];
			memcpy(bp, F_SUM(first), checksum_len);
		} else
			read_buf(f, bp, checksum_len);
	}

#ifdef SUPPORT_ACLS
	if (preserve_acls && !S_ISLNK(mode))
		receive_acl(file, f);
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs)
		receive_xattr(file, f );
#endif

	if (S_ISREG(mode) || S_ISLNK(mode))
		stats.total_size += file_length;

	return file;
}

/* Create a file_struct for a named file by reading its stat() information
 * and performing extensive checks against global options.
 *
 * Returns a pointer to the new file struct, or NULL if there was an error
 * or this file should be excluded. */
struct file_struct *make_file(const char *fname, struct file_list *flist,
			      STRUCT_STAT *stp, int flags, int filter_level)
{
	static char *lastdir;
	static int lastdir_len = -1;
	struct file_struct *file;
	char thisname[MAXPATHLEN];
	char linkname[MAXPATHLEN];
	int alloc_len, basename_len, linkname_len;
	int extra_len = file_extra_cnt * EXTRA_LEN;
	const char *basename;
	alloc_pool_t *pool;
	STRUCT_STAT st;
	char *bp;

	if (strlcpy(thisname, fname, sizeof thisname) >= sizeof thisname) {
		rprintf(FINFO, "skipping overly long name: %s\n", fname);
		return NULL;
	}
	clean_fname(thisname, 0);
	if (sanitize_paths)
		sanitize_path(thisname, thisname, "", 0);

	if (stp && S_ISDIR(stp->st_mode)) {
		st = *stp; /* Needed for "symlink/." with --relative. */
		*linkname = '\0'; /* make IBM code checker happy */
	} else if (readlink_stat(thisname, &st, linkname) != 0) {
		int save_errno = errno;
		/* See if file is excluded before reporting an error. */
		if (filter_level != NO_FILTERS
		 && (is_excluded(thisname, 0, filter_level)
		  || is_excluded(thisname, 1, filter_level))) {
			if (ignore_perishable && save_errno != ENOENT)
				non_perishable_cnt++;
			return NULL;
		}
		if (save_errno == ENOENT) {
#ifdef SUPPORT_LINKS
			/* When our options tell us to follow a symlink that
			 * points nowhere, tell the user about the symlink
			 * instead of giving a "vanished" message.  We only
			 * dereference a symlink if one of the --copy*links
			 * options was specified, so there's no need for the
			 * extra lstat() if one of these options isn't on. */
			if ((copy_links || copy_unsafe_links || copy_dirlinks)
			 && x_lstat(thisname, &st, NULL) == 0
			 && S_ISLNK(st.st_mode)) {
				io_error |= IOERR_GENERAL;
				rprintf(FERROR_XFER, "symlink has no referent: %s\n",
					full_fname(thisname));
			} else
#endif
			{
				enum logcode c = am_daemon && protocol_version < 28
					       ? FERROR : FWARNING;
				io_error |= IOERR_VANISHED;
				rprintf(c, "file has vanished: %s\n",
					full_fname(thisname));
			}
		} else {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR_XFER, save_errno, "readlink %s failed",
				full_fname(thisname));
		}
		return NULL;
	}

	/* backup.c calls us with filter_level set to NO_FILTERS. */
	if (filter_level == NO_FILTERS)
		goto skip_filters;

	if (S_ISDIR(st.st_mode)) {
		if (!xfer_dirs) {
			rprintf(FINFO, "skipping directory %s\n", thisname);
			return NULL;
		}
		/* -x only affects dirs because we need to avoid recursing
		 * into a mount-point directory, not to avoid copying a
		 * symlinked file if -L (or similar) was specified. */
		if (one_file_system && st.st_dev != filesystem_dev
		 && BITS_SETnUNSET(flags, FLAG_CONTENT_DIR, FLAG_TOP_DIR)) {
			if (one_file_system > 1) {
				if (verbose > 1) {
					rprintf(FINFO,
					    "[%s] skipping mount-point dir %s\n",
					    who_am_i(), thisname);
				}
				return NULL;
			}
			flags |= FLAG_MOUNT_DIR;
			flags &= ~FLAG_CONTENT_DIR;
		}
	} else
		flags &= ~FLAG_CONTENT_DIR;

	if (is_excluded(thisname, S_ISDIR(st.st_mode) != 0, filter_level)) {
		if (ignore_perishable)
			non_perishable_cnt++;
		return NULL;
	}

	if (lp_ignore_nonreadable(module_id)) {
#ifdef SUPPORT_LINKS
		if (!S_ISLNK(st.st_mode))
#endif
			if (access(thisname, R_OK) != 0)
				return NULL;
	}

  skip_filters:

	/* Only divert a directory in the main transfer. */
	if (flist) {
		if (flist->prev && S_ISDIR(st.st_mode)
		 && flags & FLAG_DIVERT_DIRS) {
			/* Room for parent/sibling/next-child info. */
			extra_len += DIRNODE_EXTRA_CNT * EXTRA_LEN;
			if (relative_paths)
				extra_len += PTR_EXTRA_CNT * EXTRA_LEN;
			pool = dir_flist->file_pool;
		} else
			pool = flist->file_pool;
	} else
		pool = NULL;

	if (verbose > 2) {
		rprintf(FINFO, "[%s] make_file(%s,*,%d)\n",
			who_am_i(), thisname, filter_level);
	}

	if ((basename = strrchr(thisname, '/')) != NULL) {
		int len = basename++ - thisname;
		if (len != lastdir_len || memcmp(thisname, lastdir, len) != 0) {
			lastdir = new_array(char, len + 1);
			memcpy(lastdir, thisname, len);
			lastdir[len] = '\0';
			lastdir_len = len;
		}
	} else
		basename = thisname;
	basename_len = strlen(basename) + 1; /* count the '\0' */

#ifdef SUPPORT_LINKS
	linkname_len = S_ISLNK(st.st_mode) ? strlen(linkname) + 1 : 0;
#else
	linkname_len = 0;
#endif

	if (st.st_size > 0xFFFFFFFFu && S_ISREG(st.st_mode))
		extra_len += EXTRA_LEN;

#if EXTRA_ROUNDING > 0
	if (extra_len & (EXTRA_ROUNDING * EXTRA_LEN))
		extra_len = (extra_len | (EXTRA_ROUNDING * EXTRA_LEN)) + EXTRA_LEN;
#endif

	alloc_len = FILE_STRUCT_LEN + extra_len + basename_len
		  + linkname_len;
	if (pool)
		bp = pool_alloc(pool, alloc_len, "make_file");
	else {
		if (!(bp = new_array(char, alloc_len)))
			out_of_memory("make_file");
	}

	memset(bp, 0, extra_len + FILE_STRUCT_LEN);
	bp += extra_len;
	file = (struct file_struct *)bp;
	bp += FILE_STRUCT_LEN;

	memcpy(bp, basename, basename_len);
	bp += basename_len + linkname_len; /* skip space for symlink too */

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && flist && flist->prev) {
		if (protocol_version >= 28
		 ? (!S_ISDIR(st.st_mode) && st.st_nlink > 1)
		 : S_ISREG(st.st_mode)) {
			tmp_dev = st.st_dev;
			tmp_ino = st.st_ino;
		} else
			tmp_dev = 0;
	}
#endif

#ifdef HAVE_STRUCT_STAT_ST_RDEV
	if (IS_DEVICE(st.st_mode) || IS_SPECIAL(st.st_mode)) {
		tmp_rdev = st.st_rdev;
		st.st_size = 0;
	}
#endif

	file->flags = flags;
	file->modtime = st.st_mtime;
	file->len32 = (uint32)st.st_size;
	if (st.st_size > 0xFFFFFFFFu && S_ISREG(st.st_mode)) {
		file->flags |= FLAG_LENGTH64;
		OPT_EXTRA(file, 0)->unum = (uint32)(st.st_size >> 32);
	}
	file->mode = st.st_mode;
	if (uid_ndx) /* Check uid_ndx instead of preserve_uid for del support */
		F_OWNER(file) = st.st_uid;
	if (gid_ndx) /* Check gid_ndx instead of preserve_gid for del support */
		F_GROUP(file) = st.st_gid;

	if (basename != thisname)
		file->dirname = lastdir;

#ifdef SUPPORT_LINKS
	if (linkname_len) {
		bp = (char*)file->basename + basename_len;
		memcpy(bp, linkname, linkname_len);
	}
#endif

	if (always_checksum && am_sender && S_ISREG(st.st_mode))
		file_checksum(thisname, tmp_sum, st.st_size);

	F_PATHNAME(file) = pathname;

	/* This code is only used by the receiver when it is building
	 * a list of files for a delete pass. */
	if (keep_dirlinks && linkname_len && flist) {
		STRUCT_STAT st2;
		int save_mode = file->mode;
		file->mode = S_IFDIR; /* Find a directory with our name. */
		if (flist_find(dir_flist, file) >= 0
		 && x_stat(thisname, &st2, NULL) == 0 && S_ISDIR(st2.st_mode)) {
			file->modtime = st2.st_mtime;
			file->len32 = 0;
			file->mode = st2.st_mode;
			if (uid_ndx)
				F_OWNER(file) = st2.st_uid;
			if (gid_ndx)
				F_GROUP(file) = st2.st_gid;
		} else
			file->mode = save_mode;
	}

	if (basename_len == 0+1) {
		if (!pool)
			unmake_file(file);
		return NULL;
	}

	if (unsort_ndx)
		F_NDX(file) = dir_count;

	return file;
}

/* Only called for temporary file_struct entries created by make_file(). */
void unmake_file(struct file_struct *file)
{
	int extra_cnt = file_extra_cnt + LEN64_BUMP(file);
#if EXTRA_ROUNDING > 0
	if (extra_cnt & EXTRA_ROUNDING)
		extra_cnt = (extra_cnt | EXTRA_ROUNDING) + 1;
#endif
	free(REQ_EXTRA(file, extra_cnt));
}

static struct file_struct *send_file_name(int f, struct file_list *flist,
					  char *fname, STRUCT_STAT *stp,
					  int flags, int filter_level)
{
	struct file_struct *file;
#if defined SUPPORT_ACLS || defined SUPPORT_XATTRS
	stat_x sx;
#endif

	file = make_file(fname, flist, stp, flags, filter_level);
	if (!file)
		return NULL;

	if (chmod_modes && !S_ISLNK(file->mode))
		file->mode = tweak_mode(file->mode, chmod_modes);

#ifdef SUPPORT_ACLS
	if (preserve_acls && !S_ISLNK(file->mode) && f >= 0) {
		sx.st.st_mode = file->mode;
		sx.acc_acl = sx.def_acl = NULL;
		if (get_acl(fname, &sx) < 0)
			return NULL;
	}
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs && f >= 0) {
		sx.xattr = NULL;
		if (get_xattr(fname, &sx) < 0)
			return NULL;
	}
#endif

	maybe_emit_filelist_progress(flist->used + flist_count_offset);

	flist_expand(flist, 1);
	flist->files[flist->used++] = file;
	if (f >= 0) {
		send_file_entry(f, file, flist->used - 1, flist->ndx_start);
#ifdef SUPPORT_ACLS
		if (preserve_acls && !S_ISLNK(file->mode)) {
			send_acl(&sx, f);
			free_acl(&sx);
		}
#endif
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs) {
			F_XATTR(file) = send_xattr(&sx, f);
			free_xattr(&sx);
		}
#endif
	}
	return file;
}

static void send_if_directory(int f, struct file_list *flist,
			      struct file_struct *file,
			      char *fbuf, unsigned int ol,
			      int flags)
{
	char is_dot_dir = fbuf[ol-1] == '.' && (ol == 1 || fbuf[ol-2] == '/');

	if (S_ISDIR(file->mode)
	    && !(file->flags & FLAG_MOUNT_DIR) && f_name(file, fbuf)) {
		void *save_filters;
		unsigned int len = strlen(fbuf);
		if (len > 1 && fbuf[len-1] == '/')
			fbuf[--len] = '\0';
		if (len >= MAXPATHLEN - 1) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR_XFER, "skipping long-named directory: %s\n",
				full_fname(fbuf));
			return;
		}
		save_filters = push_local_filters(fbuf, len);
		send_directory(f, flist, fbuf, len, flags);
		pop_local_filters(save_filters);
		fbuf[ol] = '\0';
		if (is_dot_dir)
			fbuf[ol-1] = '.';
	}
}

static int file_compare(const void *file1, const void *file2)
{
	return f_name_cmp(*(struct file_struct **)file1,
			  *(struct file_struct **)file2);
}

/* The guts of a merge-sort algorithm.  This was derived from the glibc
 * version, but I (Wayne) changed the merge code to do less copying and
 * to require only half the amount of temporary memory. */
static void fsort_tmp(struct file_struct **fp, size_t num,
		      struct file_struct **tmp)
{
	struct file_struct **f1, **f2, **t;
	size_t n1, n2;

	n1 = num / 2;
	n2 = num - n1;
	f1 = fp;
	f2 = fp + n1;

	if (n1 > 1)
		fsort_tmp(f1, n1, tmp);
	if (n2 > 1)
		fsort_tmp(f2, n2, tmp);

	while (f_name_cmp(*f1, *f2) <= 0) {
		if (!--n1)
			return;
		f1++;
	}

	t = tmp;
	memcpy(t, f1, n1 * PTR_SIZE);

	*f1++ = *f2++, n2--;

	while (n1 > 0 && n2 > 0) {
		if (f_name_cmp(*t, *f2) <= 0)
			*f1++ = *t++, n1--;
		else
			*f1++ = *f2++, n2--;
	}

	if (n1 > 0)
		memcpy(f1, t, n1 * PTR_SIZE);
}

/* This file-struct sorting routine makes sure that any identical names in
 * the file list stay in the same order as they were in the original list.
 * This is particularly vital in inc_recurse mode where we expect a sort
 * on the flist to match the exact order of a sort on the dir_flist. */
static void fsort(struct file_struct **fp, size_t num)
{
	if (num <= 1)
		return;

	if (use_qsort)
		qsort(fp, num, PTR_SIZE, file_compare);
	else {
		struct file_struct **tmp = new_array(struct file_struct *,
						     (num+1) / 2);
		fsort_tmp(fp, num, tmp);
		free(tmp);
	}
}

/* We take an entire set of sibling dirs from the sorted flist and link them
 * into the tree, setting the appropriate parent/child/sibling pointers. */
static void add_dirs_to_tree(int parent_ndx, struct file_list *from_flist,
			     int dir_cnt)
{
	int i;
	int32 *dp = NULL;
	int32 *parent_dp = parent_ndx < 0 ? NULL
			 : F_DIR_NODE_P(dir_flist->sorted[parent_ndx]);

	flist_expand(dir_flist, dir_cnt);
	dir_flist->sorted = dir_flist->files;

	for (i = 0; dir_cnt; i++) {
		struct file_struct *file = from_flist->sorted[i];

		if (!S_ISDIR(file->mode))
			continue;

		dir_flist->files[dir_flist->used++] = file;
		dir_cnt--;

		if (file->basename[0] == '.' && file->basename[1] == '\0')
			continue;

		if (dp)
			DIR_NEXT_SIBLING(dp) = dir_flist->used - 1;
		else if (parent_dp)
			DIR_FIRST_CHILD(parent_dp) = dir_flist->used - 1;
		else
			send_dir_ndx = dir_flist->used - 1;

		dp = F_DIR_NODE_P(file);
		DIR_PARENT(dp) = parent_ndx;
		DIR_FIRST_CHILD(dp) = -1;
	}
	if (dp)
		DIR_NEXT_SIBLING(dp) = -1;
}

/* This function is normally called by the sender, but the receiving side also
 * calls it from get_dirlist() with f set to -1 so that we just construct the
 * file list in memory without sending it over the wire.  Also, get_dirlist()
 * might call this with f set to -2, which also indicates that local filter
 * rules should be ignored. */
static void send_directory(int f, struct file_list *flist, char *fbuf, int len,
			   int flags)
{
	struct dirent *di;
	unsigned remainder;
	char *p;
	DIR *d;
	int divert_dirs = (flags & FLAG_DIVERT_DIRS) != 0;
	int start = flist->used;
	int filter_level = f == -2 ? SERVER_FILTERS : ALL_FILTERS;

	assert(flist != NULL);

	if (!(d = opendir(fbuf))) {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR_XFER, errno, "opendir %s failed", full_fname(fbuf));
		return;
	}

	p = fbuf + len;
	if (len != 1 || *fbuf != '/')
		*p++ = '/';
