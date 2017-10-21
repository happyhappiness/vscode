	flist->files = new_ptr;

	if (!flist->files)
		out_of_memory("flist_expand");
}

static void send_file_entry(struct file_struct *file, int f)
{
	unsigned short flags;
	static time_t modtime;
	static mode_t mode;
	static int64 dev;
	static dev_t rdev;
