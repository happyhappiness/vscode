unsigned char read_batch_flags(void)
{
	int flags;

	if (read_batch_flist_file((char *) &flags, 4)) {
		return 1;
	} else {
		return 0;
	}
}