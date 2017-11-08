static struct file_struct *recv_file_entry(int f, struct file_list *flist, int xflags)
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
	int64 file_length;
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
			rprintf(FERROR_UTF8,
			    "[%s] cannot convert filename: %s (%s)\n",
			    who_am_i(), lastname, strerror(errno));
			outbuf.len = 0;
		}
		thisname[outbuf.len] = '\0';
	}
#endif

	if (*thisname)
		clean_fname(thisname, 0);

	if (sanitize_paths)
		sanitize_path(thisname, thisname, "", 0, SP_DEFAULT);

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
			if (preserve_devices && IS_DEVICE(mode)) {
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
		if (IS_DEVICE(mode))
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
#ifdef ICONV_OPTION
		/* We don't know how much extra room we need to convert
		 * the as-yet-unread symlink data, so let's hope that a
		 * double-size buffer is plenty. */
		if (sender_symlink_iconv)
			linkname_len *= 2;
#endif
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
	/* Directories need an extra int32 for the default ACL. */
	if (preserve_acls && S_ISDIR(mode))
		extra_len += EXTRA_LEN;
#endif

	if (always_checksum && S_ISREG(mode))
		extra_len += SUM_EXTRA_CNT * EXTRA_LEN;

#if SIZEOF_INT64 >= 8
	if (file_length > 0xFFFFFFFFu && S_ISREG(mode))
		extra_len += EXTRA_LEN;
#endif
	if (file_length < 0) {
		rprintf(FERROR, "Offset underflow: file-length is negative\n");
		exit_cleanup(RERR_UNSUPPORTED);
	}

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

#ifdef SUPPORT_HARD_LINKS
	if (xflags & XMIT_HLINKED)
		file->flags |= FLAG_HLINKED;
#endif
	file->modtime = (time_t)modtime;
	file->len32 = (uint32)file_length;
#if SIZEOF_INT64 >= 8
	if (file_length > 0xFFFFFFFFu && S_ISREG(mode)) {
#if SIZEOF_CAPITAL_OFF_T < 8
		rprintf(FERROR, "Offset overflow: attempted 64-bit file-length\n");
		exit_cleanup(RERR_UNSUPPORTED);
#else
		file->flags |= FLAG_LENGTH64;
		OPT_EXTRA(file, 0)->unum = (uint32)(file_length >> 32);
#endif
	}
#endif
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

	if (preserve_devices && IS_DEVICE(mode)) {
		uint32 *devp = F_RDEV_P(file);
		DEV_MAJOR(devp) = major(rdev);
		DEV_MINOR(devp) = minor(rdev);
	}

#ifdef SUPPORT_LINKS
	if (linkname_len) {
		bp += basename_len;
		if (first_hlink_ndx >= flist->ndx_start) {
			struct file_struct *first = flist->files[first_hlink_ndx - flist->ndx_start];
			memcpy(bp, F_SYMLINK(first), linkname_len);
		} else {
			if (munge_symlinks) {
				strlcpy(bp, SYMLINK_PREFIX, linkname_len);
				bp += SYMLINK_PREFIX_LEN;
				linkname_len -= SYMLINK_PREFIX_LEN;
			}
#ifdef ICONV_OPTION
			if (sender_symlink_iconv) {
				xbuf outbuf, inbuf;

				alloc_len = linkname_len;
				linkname_len /= 2;

				/* Read the symlink data into the end of our double-sized
				 * buffer and then convert it into the right spot. */
				INIT_XBUF(inbuf, bp + alloc_len - linkname_len,
					  linkname_len - 1, (size_t)-1);
				read_sbuf(f, inbuf.buf, inbuf.len);
				INIT_XBUF(outbuf, bp, 0, alloc_len);

				if (iconvbufs(ic_recv, &inbuf, &outbuf, 0) < 0) {
					io_error |= IOERR_GENERAL;
					rprintf(FERROR_XFER,
					    "[%s] cannot convert symlink data for: %s (%s)\n",
					    who_am_i(), full_fname(thisname), strerror(errno));
					bp = (char*)file->basename;
					*bp++ = '\0';
					outbuf.len = 0;
				}
				bp[outbuf.len] = '\0';
			} else
#endif
				read_sbuf(f, bp, linkname_len - 1);
			if (sanitize_paths && !munge_symlinks && *bp)
				sanitize_path(bp, bp, "", lastdir_depth, SP_DEFAULT);
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
		receive_acl(f, file);
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs)
		receive_xattr(f, file);
#endif

	if (S_ISREG(mode) || S_ISLNK(mode))
		stats.total_size += file_length;

	return file;
}