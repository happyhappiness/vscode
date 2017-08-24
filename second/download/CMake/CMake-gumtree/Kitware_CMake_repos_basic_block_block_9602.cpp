(*fd >= 0)
		list_size = flistxattr(*fd, list, list_size);
	else if (!a->follow_symlinks)
		list_size = llistxattr(path, list, list_size);
	else
		list_size = listxattr(path, list, list_size)