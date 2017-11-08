int robust_rename(char *from, char *to, int mode)
{
	int tries = 4;

	while (tries--) {
		if (do_rename(from, to) == 0)
			return 0;

		switch (errno) {
#ifdef ETXTBSY
		case ETXTBSY:
			if (robust_unlink(to) != 0)
				return -1;
			break;
#endif
		case EXDEV:
			if (copy_file(from, to, mode) != 0)
				return -2;
			do_unlink(from);
			return 1;
		default:
			return -1;
		}
	}
	return -1;
}