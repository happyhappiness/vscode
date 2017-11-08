FILE *fopen_for_writing(const char *path)
{
	FILE *ret = fopen(path, "w");

	if (!ret && errno == EPERM) {
		if (!unlink(path))
			ret = fopen(path, "w");
		else
			errno = EPERM;
	}
	return ret;
}