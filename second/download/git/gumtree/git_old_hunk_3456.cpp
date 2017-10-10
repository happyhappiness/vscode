		ret = index_mem(sha1, "", size, type, path, flags);
	} else if (size <= SMALL_FILE_SIZE) {
		char *buf = xmalloc(size);
		if (size == read_in_full(fd, buf, size))
			ret = index_mem(sha1, buf, size, type, path, flags);
		else
			ret = error("short read %s", strerror(errno));
		free(buf);
	} else {
		void *buf = xmmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
		ret = index_mem(sha1, buf, size, type, path, flags);
		munmap(buf, size);
	}
