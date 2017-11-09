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
		save_filters = push_local_filters(fbuf, len);
		send_directory(f, flist, fbuf, len, flags);
		pop_local_filters(save_filters);
		fbuf[ol] = '\0';
		if (is_dot_dir)
			fbuf[ol-1] = '.';
	}
}