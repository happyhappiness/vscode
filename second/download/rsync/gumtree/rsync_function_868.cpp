static int stat_xattr(const char *fname, STRUCT_STAT *fst)
{
	int mode, rdev_major, rdev_minor, uid, gid, len;
	char buf[256];

	if (am_root >= 0 || IS_DEVICE(fst->st_mode) || IS_SPECIAL(fst->st_mode))
		return -1;

	len = sys_lgetxattr(fname, XSTAT_ATTR, buf, sizeof buf - 1);
	if (len >= (int)sizeof buf) {
		len = -1;
		errno = ERANGE;
	}
	if (len < 0) {
		if (errno == ENOTSUP || errno == ENOATTR)
			return -1;
		if (errno == EPERM && S_ISLNK(fst->st_mode)) {
			fst->st_uid = 0;
			fst->st_gid = 0;
			return 0;
		}
		fprintf(stderr, "failed to read xattr %s for %s: %s\n",
			XSTAT_ATTR, fname, strerror(errno));
		return -1;
	}
	buf[len] = '\0';

	if (sscanf(buf, "%o %d,%d %d:%d",
		   &mode, &rdev_major, &rdev_minor, &uid, &gid) != 5) {
		fprintf(stderr, "Corrupt %s xattr attached to %s: \"%s\"\n",
			XSTAT_ATTR, fname, buf);
		exit(1);
	}

#if _S_IFLNK != 0120000
	if ((mode & (_S_IFMT)) == 0120000)
		mode = (mode & ~(_S_IFMT)) | _S_IFLNK;
#endif
	fst->st_mode = mode;

	fst->st_rdev = MAKEDEV(rdev_major, rdev_minor);
	fst->st_uid = uid;
	fst->st_gid = gid;

	return 0;
}