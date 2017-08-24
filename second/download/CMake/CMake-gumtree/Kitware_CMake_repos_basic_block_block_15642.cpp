{
		size_t newsize = cpio->ino_list_size < 512
		    ? 512 : cpio->ino_list_size * 2;
		void *newlist = realloc(cpio->ino_list,
		    sizeof(cpio->ino_list[0]) * newsize);
		if (newlist == NULL)
			return (-1);

		cpio->ino_list_size = newsize;
		cpio->ino_list = newlist;
	}