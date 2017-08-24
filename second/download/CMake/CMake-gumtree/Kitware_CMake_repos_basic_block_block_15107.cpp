(fullname != NULL)
		r = SetFileAttributesW(fullname, attr);
	else
		r = SetFileAttributesW(path, attr)