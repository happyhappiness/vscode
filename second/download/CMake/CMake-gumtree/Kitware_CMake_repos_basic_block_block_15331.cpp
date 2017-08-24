{
		mine->fd = _wopen(fullpath, flags, 0666);
		free(fullpath);
	}