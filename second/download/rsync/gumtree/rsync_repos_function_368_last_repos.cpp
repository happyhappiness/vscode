int robust_rename(const char *from, const char *to, const char *partialptr,
		  int mode)
{
	int tries = 4;

	while (tries--) {
		if (do_rename(from, to) == 0)
			return 0;

		switch (errno) {
#ifdef ETXTBSY
		case ETXTBSY:
			if (robust_unlink(to) != 0) {
				errno = ETXTBSY;
				return -1;
			}
			errno = ETXTBSY;
			break;
#endif
		case EXDEV:
			if (partialptr) {
				if (!handle_partial_dir(partialptr,PDIR_CREATE))
					return -2;
				to = partialptr;
			}
			if (copy_file(from, to, -1, mode) != 0)
				return -2;
			do_unlink(from);
			return 1;
		default:
			return -1;
		}
	}
	return -1;
}