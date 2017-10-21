static void receive_file_entry(struct file_struct **fptr,
			       unsigned flags, int f)
{
	static time_t last_time;
	static mode_t last_mode;
	static DEV64_T last_rdev;
	static uid_t last_uid;
	static gid_t last_gid;
	static char lastname[MAXPATHLEN];
	char thisname[MAXPATHLEN];
	unsigned int l1 = 0, l2 = 0;
	char *p;
	struct file_struct *file;

	if (flags & SAME_NAME)
		l1 = read_byte(f);

	if (flags & LONG_NAME)
		l2 = read_int(f);
	else
		l2 = read_byte(f);

	file = new(struct file_struct);
	if (!file)
		out_of_memory("receive_file_entry");
	memset((char *) file, 0, sizeof(*file));
	(*fptr) = file;

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
	lastname[MAXPATHLEN - 1] = 0;

	clean_fname(thisname);

	if (sanitize_paths) {
		sanitize_path(thisname, NULL);
	}

	if ((p = strrchr(thisname, '/'))) {
		static char *lastdir;
		*p = 0;
		if (lastdir && strcmp(thisname, lastdir) == 0) {
			file->dirname = lastdir;
		} else {
			file->dirname = strdup(thisname);
			lastdir = file->dirname;
		}
		file->basename = strdup(p + 1);
	} else {
		file->dirname = NULL;
		file->basename = strdup(thisname);
	}

	if (!file->basename)
		out_of_memory("receive_file_entry 1");


	file->flags = flags;
	file->length = read_longint(f);
	file->modtime =
	    (flags & SAME_TIME) ? last_time : (time_t) read_int(f);
	file->mode =
	    (flags & SAME_MODE) ? last_mode : from_wire_mode(read_int(f));
	if (preserve_uid)
		file->uid =
		    (flags & SAME_UID) ? last_uid : (uid_t) read_int(f);
	if (preserve_gid)
		file->gid =
		    (flags & SAME_GID) ? last_gid : (gid_t) read_int(f);
	if (preserve_devices && IS_DEVICE(file->mode))
		file->rdev =
		    (flags & SAME_RDEV) ? last_rdev : (DEV64_T) read_int(f);

	if (preserve_links && S_ISLNK(file->mode)) {
		int l = read_int(f);
		if (l < 0) {
			rprintf(FERROR, "overflow: l=%d\n", l);
			overflow("receive_file_entry");
		}
		file->link = new_array(char, l + 1);
		if (!file->link)
			out_of_memory("receive_file_entry 2");
		read_sbuf(f, file->link, l);
		if (sanitize_paths) {
			sanitize_path(file->link, file->dirname);
		}
	}
#if SUPPORT_HARD_LINKS
	if (preserve_hard_links && S_ISREG(file->mode)) {
		if (protocol_version < 26) {
			file->dev = read_int(f);
			file->inode = read_int(f);
		} else {
			file->dev = read_longint(f);
			file->inode = read_longint(f);
		}
	}
#endif

	if (always_checksum) {
		file->sum = new_array(char, MD4_SUM_LENGTH);
		if (!file->sum)
			out_of_memory("md4 sum");
		if (protocol_version < 21) {
			read_buf(f, file->sum, 2);
		} else {
			read_buf(f, file->sum, MD4_SUM_LENGTH);
		}
	}

	last_mode = file->mode;
	last_rdev = file->rdev;
	last_uid = file->uid;
	last_gid = file->gid;
	last_time = file->modtime;

	if (!preserve_perms) {
		extern int orig_umask;
		/* set an appropriate set of permissions based on original
		   permissions and umask. This emulates what GNU cp does */
		file->mode &= ~orig_umask;
	}
}