		return dest_path;

	if (cp == dest_path)
		dest_path = "/";

	*cp = '\0';
	if (!push_dir(dest_path)) {
		rsyserr(FERROR, errno, "push_dir#3 %s failed",
			full_fname(dest_path));
		exit_cleanup(RERR_FILESELECT);
	}
	*cp = '/';

	return cp + 1;
}


/* This is only called by the sender. */
static void read_final_goodbye(int f_in, int f_out)
{
	int i;

