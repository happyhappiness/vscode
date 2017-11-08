static void send_if_directory(int f, struct file_list *flist,
			      struct file_struct *file)
{
	char fbuf[MAXPATHLEN];

	if (S_ISDIR(file->mode)
	    && !(file->flags & FLAG_MOUNT_POINT) && f_name_to(file, fbuf)) {
		void *save_filters;
		unsigned int len = strlen(fbuf);
		if (len > 1 && fbuf[len-1] == '/')
			fbuf[--len] = '\0';
		if (len >= MAXPATHLEN - 1) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR, "skipping long-named directory: %s\n",
				full_fname(fbuf));
			return;
		}
		save_filters = push_local_filters(fbuf, len);
		send_directory(f, flist, fbuf, len);
		pop_local_filters(save_filters);
	}
}