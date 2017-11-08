int robust_rename(char *from, char *to)
{
#ifndef ETXTBSY
	return do_rename(from, to);
#else
	int rc = do_rename(from, to);
	if ((rc == 0) || (errno != ETXTBSY))
		return rc;
	if (robust_unlink(to) != 0)
		return -1;
	return do_rename(from, to);
#endif
}