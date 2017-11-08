int robust_rename(char *from, char *to, char *partialptr,
		  int mode)
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
			if (partialptr) {
				if (!handle_partial_dir(partialptr,PDIR_CREATE))
					return -1;
				to = partialptr;
			}
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