	filesystem_dev = st.st_dev;
}


static int to_wire_mode(mode_t mode)
{
	if (S_ISLNK(mode) && (_S_IFLNK != 0120000)) {
		return (mode & ~(_S_IFMT)) | 0120000;
	}
	return (int) mode;
}

static mode_t from_wire_mode(int mode)
{
	if ((mode & (_S_IFMT)) == 0120000 && (_S_IFLNK != 0120000)) {
		return (mode & ~(_S_IFMT)) | _S_IFLNK;
	}
	return (mode_t) mode;
}


static void send_directory(int f, struct file_list *flist, char *dir);

static char *flist_dir;


/**
 * Make sure @p flist is big enough to hold at least @p flist->count
 * entries.
 **/
static void flist_expand(struct file_list *flist)
{
	if (flist->count >= flist->malloced) {
		void *new_ptr;

		if (flist->malloced < 1000)
			flist->malloced += 1000;
		else
			flist->malloced *= 2;

		if (flist->files) {
			new_ptr = realloc_array(flist->files,
						struct file_struct *,
						flist->malloced);
		} else {
			new_ptr = new_array(struct file_struct *,
					    flist->malloced);
		}

		if (verbose >= 2) {
			rprintf(FINFO, "expand file_list to %.0f bytes, did%s move\n",
				(double)sizeof(flist->files[0])
				* flist->malloced,
				(new_ptr == flist->files) ? " not" : "");
		}

		flist->files = (struct file_struct **) new_ptr;

		if (!flist->files)
			out_of_memory("flist_expand");
	}
}


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

	io_write_phase = "send_file_entry";

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
	     l1++) {}
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
		if (protocol_version < 26) {
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
		if (protocol_version < 21) {
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

	io_write_phase = "unknown";
}



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


/* determine if a file in a different filesstem should be skipped
   when one_file_system is set. We bascally only want to include
   the mount points - but they can be hard to find! */
static int skip_filesystem(char *fname, STRUCT_STAT * st)
{
	STRUCT_STAT st2;
	char *p = strrchr(fname, '/');

	/* skip all but directories */
	if (!S_ISDIR(st->st_mode))
		return 1;

	/* if its not a subdirectory then allow */
	if (!p)
		return 0;

	*p = 0;
	if (link_stat(fname, &st2)) {
		*p = '/';
		return 0;
	}
	*p = '/';

	return (st2.st_dev != filesystem_dev);
}

#define STRDUP(ap, p)	(ap ? string_area_strdup(ap, p) : strdup(p))
/* IRIX cc cares that the operands to the ternary have the same type. */
#define MALLOC(ap, i)	(ap ? (void*) string_area_malloc(ap, i) : malloc(i))

/**
 * Create a file_struct for a named file by reading its stat()
 * information and performing extensive checks against global
 * options.
 *
 * @return the new file, or NULL if there was an error or this file
