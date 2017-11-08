void cleanup_set(char *fnametmp, char *fname, struct file_struct *file,
		 struct map_struct *buf, int fd1, int fd2)
{
	cleanup_fname = fnametmp;
	cleanup_new_fname = fname;
	cleanup_file = file;
	cleanup_buf = buf;
	cleanup_fd1 = fd1;
	cleanup_fd2 = fd2;
}