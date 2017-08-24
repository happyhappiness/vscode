(u.st_mode & (S_IFCHR | S_IFIFO)) {
			st->st_dev = fd;
			st->st_rdev = fd;
		}