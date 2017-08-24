(fullpath != NULL) {
		mine->fd = _wopen(fullpath, flags, 0666);
		free(fullpath);
	} else
		mine->fd = _wopen(wcs, flags, 0666)