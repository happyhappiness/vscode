ssize_t sys_llistxattr(const char *path, char *list, size_t size)
{
	int attrdirfd;
	DIR *dirp;
	struct dirent *dp;
	ssize_t ret = 0;

	if ((attrdirfd = attropen(path, ".", O_RDONLY)) < 0) {
		errno = ENOTSUP;
		return -1;
	}

	if ((dirp = fdopendir(attrdirfd)) == NULL) {
		close(attrdirfd);
		return -1;
	}

	while ((dp = readdir(dirp))) {
		int len = strlen(dp->d_name);

		if (dp->d_name[0] == '.' && (len == 1 || (len == 2 && dp->d_name[1] == '.')))
			continue;
		if (len == 11 && dp->d_name[0] == 'S' && strncmp(dp->d_name, "SUNWattr_r", 10) == 0
		 && (dp->d_name[10] == 'o' || dp->d_name[10] == 'w'))
			continue;

		if ((ret += len+1) > size) {
			if (size == 0)
				continue;
			ret = -1;
			errno = ERANGE;
			break;
		}
		memcpy(list, dp->d_name, len+1);
		list += len+1;
	}

	closedir(dirp);
	close(attrdirfd);

	return ret;
}