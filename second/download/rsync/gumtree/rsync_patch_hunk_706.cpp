 	filesystem_dev = st.st_dev;
 }
 
 
 static int to_wire_mode(mode_t mode)
 {
-	if (S_ISLNK(mode) && (_S_IFLNK != 0120000)) {
+#if SUPPORT_LINKS
+	if (S_ISLNK(mode) && (_S_IFLNK != 0120000))
 		return (mode & ~(_S_IFMT)) | 0120000;
-	}
+#endif
 	return (int) mode;
 }
 
 static mode_t from_wire_mode(int mode)
 {
-	if ((mode & (_S_IFMT)) == 0120000 && (_S_IFLNK != 0120000)) {
+	if ((mode & (_S_IFMT)) == 0120000 && (_S_IFLNK != 0120000))
 		return (mode & ~(_S_IFMT)) | _S_IFLNK;
-	}
 	return (mode_t) mode;
 }
 
 
 static void send_directory(int f, struct file_list *flist, char *dir);
 
 static char *flist_dir;
+static int flist_dir_len;
 
 
 /**
  * Make sure @p flist is big enough to hold at least @p flist->count
  * entries.
  **/
-static void flist_expand(struct file_list *flist)
+void flist_expand(struct file_list *flist)
 {
-	if (flist->count >= flist->malloced) {
-		void *new_ptr;
+	void *new_ptr;
 
-		if (flist->malloced < 1000)
-			flist->malloced += 1000;
-		else
-			flist->malloced *= 2;
-
-		if (flist->files) {
-			new_ptr = realloc_array(flist->files,
-						struct file_struct *,
-						flist->malloced);
-		} else {
-			new_ptr = new_array(struct file_struct *,
-					    flist->malloced);
-		}
+	if (flist->count < flist->malloced)
+		return;
 
-		if (verbose >= 2) {
-			rprintf(FINFO, "expand file_list to %.0f bytes, did%s move\n",
-				(double)sizeof(flist->files[0])
-				* flist->malloced,
-				(new_ptr == flist->files) ? " not" : "");
-		}
+	if (flist->malloced < FLIST_START)
+		flist->malloced = FLIST_START;
+	else if (flist->malloced >= FLIST_LINEAR)
+		flist->malloced += FLIST_LINEAR;
+	else
+		flist->malloced *= 2;
 
-		flist->files = (struct file_struct **) new_ptr;
+	/*
+	 * In case count jumped or we are starting the list
+	 * with a known size just set it.
+	 */
+	if (flist->malloced < flist->count)
+		flist->malloced = flist->count;
+
+	if (flist->files) {
+		new_ptr = realloc_array(flist->files,
+		    struct file_struct *, flist->malloced);
+	} else {
+		new_ptr = new_array(struct file_struct *, flist->malloced);
+	}
 
-		if (!flist->files)
-			out_of_memory("flist_expand");
+	if (verbose >= 2) {
+		rprintf(FINFO, "[%s] expand file_list to %.0f bytes, did%s move\n",
+		    who_am_i(),
+		    (double) sizeof flist->files[0] * flist->malloced,
+		    (new_ptr == flist->files) ? " not" : "");
 	}
-}
 
+	flist->files = (struct file_struct **) new_ptr;
+
+	if (!flist->files)
+		out_of_memory("flist_expand");
+}
 
-static void send_file_entry(struct file_struct *file, int f,
-			    unsigned base_flags)
+void send_file_entry(struct file_struct *file, int f, unsigned short base_flags)
 {
-	unsigned char flags;
-	static time_t last_time;
-	static mode_t last_mode;
-	static DEV64_T last_rdev;
-	static uid_t last_uid;
-	static gid_t last_gid;
+	unsigned short flags;
+	static time_t modtime;
+	static mode_t mode;
+	static uint64 dev;
+	static dev_t rdev;
+	static uint32 rdev_major;
+	static uid_t uid;
+	static gid_t gid;
 	static char lastname[MAXPATHLEN];
-	char *fname;
+	char *fname, fbuf[MAXPATHLEN];
 	int l1, l2;
 
 	if (f == -1)
 		return;
 
 	if (!file) {
 		write_byte(f, 0);
+		modtime = 0, mode = 0;
+		dev = 0, rdev = makedev(0, 0);
+		rdev_major = 0;
+		uid = 0, gid = 0;
+		*lastname = '\0';
 		return;
 	}
 
 	io_write_phase = "send_file_entry";
 
-	fname = f_name(file);
+	fname = f_name_to(file, fbuf);
 
 	flags = base_flags;
 
-	if (file->mode == last_mode)
-		flags |= SAME_MODE;
-	if (file->rdev == last_rdev)
-		flags |= SAME_RDEV;
-	if (file->uid == last_uid)
-		flags |= SAME_UID;
-	if (file->gid == last_gid)
-		flags |= SAME_GID;
-	if (file->modtime == last_time)
-		flags |= SAME_TIME;
+	if (file->mode == mode)
+		flags |= XMIT_SAME_MODE;
+	else
+		mode = file->mode;
+	if (preserve_devices) {
+		if (protocol_version < 28) {
+			if (IS_DEVICE(mode)) {
+				if (file->u.rdev == rdev)
+					flags |= XMIT_SAME_RDEV_pre28;
+				else
+					rdev = file->u.rdev;
+			} else
+				rdev = makedev(0, 0);
+		} else if (IS_DEVICE(mode)) {
+			rdev = file->u.rdev;
+			if ((uint32)major(rdev) == rdev_major)
+				flags |= XMIT_SAME_RDEV_MAJOR;
+			else
+				rdev_major = major(rdev);
+			if ((uint32)minor(rdev) <= 0xFFu)
+				flags |= XMIT_RDEV_MINOR_IS_SMALL;
+		}
+	}
+	if (file->uid == uid)
+		flags |= XMIT_SAME_UID;
+	else
+		uid = file->uid;
+	if (file->gid == gid)
+		flags |= XMIT_SAME_GID;
+	else
+		gid = file->gid;
+	if (file->modtime == modtime)
+		flags |= XMIT_SAME_TIME;
+	else
+		modtime = file->modtime;
+
+#if SUPPORT_HARD_LINKS
+	if (file->link_u.idev) {
+		if (file->F_DEV == dev) {
+			if (protocol_version >= 28)
+				flags |= XMIT_SAME_DEV;
+		} else
+			dev = file->F_DEV;
+		flags |= XMIT_HAS_IDEV_DATA;
+	}
+#endif
 
 	for (l1 = 0;
-	     lastname[l1] && (fname[l1] == lastname[l1]) && (l1 < 255);
-	     l1++) {}
-	l2 = strlen(fname) - l1;
+	    lastname[l1] && (fname[l1] == lastname[l1]) && (l1 < 255);
+	    l1++) {}
+	l2 = strlen(fname+l1);
 
 	if (l1 > 0)
-		flags |= SAME_NAME;
+		flags |= XMIT_SAME_NAME;
 	if (l2 > 255)
-		flags |= LONG_NAME;
-
-	/* we must make sure we don't send a zero flags byte or the other
-	   end will terminate the flist transfer */
-	if (flags == 0 && !S_ISDIR(file->mode))
-		flags |= FLAG_DELETE;
-	if (flags == 0)
-		flags |= LONG_NAME;
+		flags |= XMIT_LONG_NAME;
 
-	write_byte(f, flags);
-	if (flags & SAME_NAME)
+	/* We must make sure we don't send a zero flag byte or the
+	 * other end will terminate the flist transfer.  Note that
+	 * the use of XMIT_TOP_DIR on a non-dir has no meaning, so
+	 * it's harmless way to add a bit to the first flag byte. */
+	if (protocol_version >= 28) {
+		if (!flags && !S_ISDIR(mode))
+			flags |= XMIT_TOP_DIR;
+		if ((flags & 0xFF00) || !flags) {
+			flags |= XMIT_EXTENDED_FLAGS;
+			write_byte(f, flags);
+			write_byte(f, flags >> 8);
+		} else
+			write_byte(f, flags);
+	} else {
+		if (!(flags & 0xFF) && !S_ISDIR(mode))
+			flags |= XMIT_TOP_DIR;
+		if (!(flags & 0xFF))
+			flags |= XMIT_LONG_NAME;
+		write_byte(f, flags);
+	}
+	if (flags & XMIT_SAME_NAME)
 		write_byte(f, l1);
-	if (flags & LONG_NAME)
+	if (flags & XMIT_LONG_NAME)
 		write_int(f, l2);
 	else
 		write_byte(f, l2);
 	write_buf(f, fname + l1, l2);
 
 	write_longint(f, file->length);
-	if (!(flags & SAME_TIME))
-		write_int(f, (int) file->modtime);
-	if (!(flags & SAME_MODE))
-		write_int(f, to_wire_mode(file->mode));
-	if (preserve_uid && !(flags & SAME_UID)) {
-		add_uid(file->uid);
-		write_int(f, (int) file->uid);
-	}
-	if (preserve_gid && !(flags & SAME_GID)) {
-		add_gid(file->gid);
-		write_int(f, (int) file->gid);
-	}
-	if (preserve_devices && IS_DEVICE(file->mode)
-	    && !(flags & SAME_RDEV))
-		write_int(f, (int) file->rdev);
+	if (!(flags & XMIT_SAME_TIME))
+		write_int(f, modtime);
+	if (!(flags & XMIT_SAME_MODE))
+		write_int(f, to_wire_mode(mode));
+	if (preserve_uid && !(flags & XMIT_SAME_UID)) {
+		if (!numeric_ids)
+			add_uid(uid);
+		write_int(f, uid);
+	}
+	if (preserve_gid && !(flags & XMIT_SAME_GID)) {
+		if (!numeric_ids)
+			add_gid(gid);
+		write_int(f, gid);
+	}
+	if (preserve_devices && IS_DEVICE(mode)) {
+		if (protocol_version < 28) {
+			if (!(flags & XMIT_SAME_RDEV_pre28))
+				write_int(f, (int)rdev);
+		} else {
+			if (!(flags & XMIT_SAME_RDEV_MAJOR))
+				write_int(f, major(rdev));
+			if (flags & XMIT_RDEV_MINOR_IS_SMALL)
+				write_byte(f, minor(rdev));
+			else
+				write_int(f, minor(rdev));
+		}
+	}
 
 #if SUPPORT_LINKS
-	if (preserve_links && S_ISLNK(file->mode)) {
-		write_int(f, strlen(file->link));
-		write_buf(f, file->link, strlen(file->link));
+	if (preserve_links && S_ISLNK(mode)) {
+		int len = strlen(file->u.link);
+		write_int(f, len);
+		write_buf(f, file->u.link, len);
 	}
 #endif
 
 #if SUPPORT_HARD_LINKS
-	if (preserve_hard_links && S_ISREG(file->mode)) {
+	if (flags & XMIT_HAS_IDEV_DATA) {
 		if (protocol_version < 26) {
 			/* 32-bit dev_t and ino_t */
-			write_int(f, (int) file->dev);
-			write_int(f, (int) file->inode);
+			write_int(f, dev);
+			write_int(f, file->F_INODE);
 		} else {
 			/* 64-bit dev_t and ino_t */
-			write_longint(f, file->dev);
-			write_longint(f, file->inode);
+			if (!(flags & XMIT_SAME_DEV))
+				write_longint(f, dev);
+			write_longint(f, file->F_INODE);
 		}
 	}
 #endif
 
 	if (always_checksum) {
-		if (protocol_version < 21) {
-			write_buf(f, file->sum, 2);
-		} else {
-			write_buf(f, file->sum, MD4_SUM_LENGTH);
+		char *sum;
+		if (S_ISREG(mode))
+			sum = file->u.sum;
+		else if (protocol_version < 28) {
+			/* Prior to 28, we sent a useless set of nulls. */
+			sum = empty_sum;
+		} else
+			sum = NULL;
+		if (sum) {
+			write_buf(f, sum,
+			    protocol_version < 21 ? 2 : MD4_SUM_LENGTH);
 		}
 	}
 
-	last_mode = file->mode;
-	last_rdev = file->rdev;
-	last_uid = file->uid;
-	last_gid = file->gid;
-	last_time = file->modtime;
-
 	strlcpy(lastname, fname, MAXPATHLEN);
-	lastname[MAXPATHLEN - 1] = 0;
 
 	io_write_phase = "unknown";
 }
 
 
 
-static void receive_file_entry(struct file_struct **fptr,
-			       unsigned flags, int f)
+void receive_file_entry(struct file_struct **fptr, unsigned short flags,
+    struct file_list *flist, int f)
 {
-	static time_t last_time;
-	static mode_t last_mode;
-	static DEV64_T last_rdev;
-	static uid_t last_uid;
-	static gid_t last_gid;
-	static char lastname[MAXPATHLEN];
+	static time_t modtime;
+	static mode_t mode;
+	static uint64 dev;
+	static dev_t rdev;
+	static uint32 rdev_major;
+	static uid_t uid;
+	static gid_t gid;
+	static char lastname[MAXPATHLEN], *lastdir;
+	static int lastdir_len = -1;
 	char thisname[MAXPATHLEN];
 	unsigned int l1 = 0, l2 = 0;
-	char *p;
+	int alloc_len, basename_len, dirname_len, linkname_len, sum_len;
+	OFF_T file_length;
+	char *basename, *dirname, *bp;
 	struct file_struct *file;
 
-	if (flags & SAME_NAME)
+	if (!fptr) {
+		modtime = 0, mode = 0;
+		dev = 0, rdev = makedev(0, 0);
+		rdev_major = 0;
+		uid = 0, gid = 0;
+		*lastname = '\0';
+		return;
+	}
+
+	if (flags & XMIT_SAME_NAME)
 		l1 = read_byte(f);
 
-	if (flags & LONG_NAME)
+	if (flags & XMIT_LONG_NAME)
 		l2 = read_int(f);
 	else
 		l2 = read_byte(f);
 
-	file = new(struct file_struct);
-	if (!file)
-		out_of_memory("receive_file_entry");
-	memset((char *) file, 0, sizeof(*file));
-	(*fptr) = file;
-
 	if (l2 >= MAXPATHLEN - l1) {
 		rprintf(FERROR,
 			"overflow: flags=0x%x l1=%d l2=%d lastname=%s\n",
 			flags, l1, l2, lastname);
 		overflow("receive_file_entry");
 	}
 
 	strlcpy(thisname, lastname, l1 + 1);
 	read_sbuf(f, &thisname[l1], l2);
 	thisname[l1 + l2] = 0;
 
 	strlcpy(lastname, thisname, MAXPATHLEN);
-	lastname[MAXPATHLEN - 1] = 0;
 
 	clean_fname(thisname);
 
-	if (sanitize_paths) {
+	if (sanitize_paths)
 		sanitize_path(thisname, NULL);
+
+	if ((basename = strrchr(thisname, '/')) != NULL) {
+		dirname_len = ++basename - thisname; /* counts future '\0' */
+		if (lastdir_len == dirname_len - 1
+		    && strncmp(thisname, lastdir, lastdir_len) == 0) {
+			dirname = lastdir;
+			dirname_len = 0; /* indicates no copy is needed */
+		} else
+			dirname = thisname;
+	} else {
+		basename = thisname;
+		dirname = NULL;
+		dirname_len = 0;
+	}
+	basename_len = strlen(basename) + 1; /* count the '\0' */
+
+	file_length = read_longint(f);
+	if (!(flags & XMIT_SAME_TIME))
+		modtime = (time_t)read_int(f);
+	if (!(flags & XMIT_SAME_MODE))
+		mode = from_wire_mode(read_int(f));
+
+	if (preserve_uid && !(flags & XMIT_SAME_UID))
+		uid = (uid_t)read_int(f);
+	if (preserve_gid && !(flags & XMIT_SAME_GID))
+		gid = (gid_t)read_int(f);
+
+	if (preserve_devices) {
+		if (protocol_version < 28) {
+			if (IS_DEVICE(mode)) {
+				if (!(flags & XMIT_SAME_RDEV_pre28))
+					rdev = (dev_t)read_int(f);
+			} else
+				rdev = makedev(0, 0);
+		} else if (IS_DEVICE(mode)) {
+			uint32 rdev_minor;
+			if (!(flags & XMIT_SAME_RDEV_MAJOR))
+				rdev_major = read_int(f);
+			if (flags & XMIT_RDEV_MINOR_IS_SMALL)
+				rdev_minor = read_byte(f);
+			else
+				rdev_minor = read_int(f);
+			rdev = makedev(rdev_major, rdev_minor);
+		}
 	}
 
-	if ((p = strrchr(thisname, '/'))) {
-		static char *lastdir;
-		*p = 0;
-		if (lastdir && strcmp(thisname, lastdir) == 0) {
-			file->dirname = lastdir;
-		} else {
-			file->dirname = strdup(thisname);
-			lastdir = file->dirname;
+#if SUPPORT_LINKS
+	if (preserve_links && S_ISLNK(mode)) {
+		linkname_len = read_int(f) + 1; /* count the '\0' */
+		if (linkname_len <= 0 || linkname_len > MAXPATHLEN) {
+			rprintf(FERROR, "overflow: linkname_len=%d\n",
+				linkname_len - 1);
+			overflow("receive_file_entry");
 		}
-		file->basename = strdup(p + 1);
-	} else {
-		file->dirname = NULL;
-		file->basename = strdup(thisname);
 	}
+	else
+#endif
+		linkname_len = 0;
 
-	if (!file->basename)
-		out_of_memory("receive_file_entry 1");
+	sum_len = always_checksum && S_ISREG(mode) ? MD4_SUM_LENGTH : 0;
 
+	alloc_len = file_struct_len + dirname_len + basename_len
+		  + linkname_len + sum_len;
+	bp = pool_alloc(flist->file_pool, alloc_len, "receive_file_entry");
+
+	file = *fptr = (struct file_struct *)bp;
+	memset(bp, 0, file_struct_len);
+	bp += file_struct_len;
+
+	file->flags = flags & XMIT_TOP_DIR ? FLAG_TOP_DIR : 0;
+	file->modtime = modtime;
+	file->length = file_length;
+	file->mode = mode;
+	file->uid = uid;
+	file->gid = gid;
+
+	if (dirname_len) {
+		file->dirname = lastdir = bp;
+		lastdir_len = dirname_len - 1;
+		memcpy(bp, dirname, dirname_len - 1);
+		bp += dirname_len;
+		bp[-1] = '\0';
+	} else if (dirname)
+		file->dirname = dirname;
+
+	file->basename = bp;
+	memcpy(bp, basename, basename_len);
+	bp += basename_len;
 
-	file->flags = flags;
-	file->length = read_longint(f);
-	file->modtime =
-	    (flags & SAME_TIME) ? last_time : (time_t) read_int(f);
-	file->mode =
-	    (flags & SAME_MODE) ? last_mode : from_wire_mode(read_int(f));
-	if (preserve_uid)
-		file->uid =
-		    (flags & SAME_UID) ? last_uid : (uid_t) read_int(f);
-	if (preserve_gid)
-		file->gid =
-		    (flags & SAME_GID) ? last_gid : (gid_t) read_int(f);
-	if (preserve_devices && IS_DEVICE(file->mode))
-		file->rdev =
-		    (flags & SAME_RDEV) ? last_rdev : (DEV64_T) read_int(f);
-
-	if (preserve_links && S_ISLNK(file->mode)) {
-		int l = read_int(f);
-		if (l < 0) {
-			rprintf(FERROR, "overflow: l=%d\n", l);
-			overflow("receive_file_entry");
-		}
-		file->link = new_array(char, l + 1);
-		if (!file->link)
-			out_of_memory("receive_file_entry 2");
-		read_sbuf(f, file->link, l);
-		if (sanitize_paths) {
-			sanitize_path(file->link, file->dirname);
-		}
+	if (preserve_devices && IS_DEVICE(mode))
+		file->u.rdev = rdev;
+
+#if SUPPORT_LINKS
+	if (linkname_len) {
+		file->u.link = bp;
+		read_sbuf(f, bp, linkname_len - 1);
+		if (sanitize_paths)
+			sanitize_path(bp, lastdir);
+		bp += linkname_len;
 	}
+#endif
+
 #if SUPPORT_HARD_LINKS
-	if (preserve_hard_links && S_ISREG(file->mode)) {
+	if (preserve_hard_links && protocol_version < 28 && S_ISREG(mode))
+		flags |= XMIT_HAS_IDEV_DATA;
+	if (flags & XMIT_HAS_IDEV_DATA) {
+		uint64 inode;
 		if (protocol_version < 26) {
-			file->dev = read_int(f);
-			file->inode = read_int(f);
+			dev = read_int(f);
+			inode = read_int(f);
 		} else {
-			file->dev = read_longint(f);
-			file->inode = read_longint(f);
+			if (!(flags & XMIT_SAME_DEV))
+				dev = read_longint(f);
+			inode = read_longint(f);
+		}
+		if (flist->hlink_pool) {
+			file->link_u.idev = pool_talloc(flist->hlink_pool,
+			    struct idev, 1, "inode_table");
+			file->F_INODE = inode;
+			file->F_DEV = dev;
 		}
 	}
 #endif
 
 	if (always_checksum) {
-		file->sum = new_array(char, MD4_SUM_LENGTH);
-		if (!file->sum)
-			out_of_memory("md4 sum");
-		if (protocol_version < 21) {
-			read_buf(f, file->sum, 2);
-		} else {
-			read_buf(f, file->sum, MD4_SUM_LENGTH);
+		char *sum;
+		if (sum_len) {
+			file->u.sum = sum = bp;
+			/*bp += sum_len;*/
+		} else if (protocol_version < 28) {
+			/* Prior to 28, we get a useless set of nulls. */
+			sum = empty_sum;
+		} else
+			sum = NULL;
+		if (sum) {
+			read_buf(f, sum,
+			    protocol_version < 21 ? 2 : MD4_SUM_LENGTH);
 		}
 	}
 
-	last_mode = file->mode;
-	last_rdev = file->rdev;
-	last_uid = file->uid;
-	last_gid = file->gid;
-	last_time = file->modtime;
-
 	if (!preserve_perms) {
 		extern int orig_umask;
 		/* set an appropriate set of permissions based on original
-		   permissions and umask. This emulates what GNU cp does */
+		 * permissions and umask. This emulates what GNU cp does */
 		file->mode &= ~orig_umask;
 	}
 }
 
 
-/* determine if a file in a different filesstem should be skipped
-   when one_file_system is set. We bascally only want to include
-   the mount points - but they can be hard to find! */
-static int skip_filesystem(char *fname, STRUCT_STAT * st)
-{
-	STRUCT_STAT st2;
-	char *p = strrchr(fname, '/');
-
-	/* skip all but directories */
-	if (!S_ISDIR(st->st_mode))
-		return 1;
-
-	/* if its not a subdirectory then allow */
-	if (!p)
-		return 0;
-
-	*p = 0;
-	if (link_stat(fname, &st2)) {
-		*p = '/';
-		return 0;
-	}
-	*p = '/';
-
-	return (st2.st_dev != filesystem_dev);
-}
-
-#define STRDUP(ap, p)	(ap ? string_area_strdup(ap, p) : strdup(p))
-/* IRIX cc cares that the operands to the ternary have the same type. */
-#define MALLOC(ap, i)	(ap ? (void*) string_area_malloc(ap, i) : malloc(i))
-
 /**
  * Create a file_struct for a named file by reading its stat()
  * information and performing extensive checks against global
  * options.
  *
  * @return the new file, or NULL if there was an error or this file
