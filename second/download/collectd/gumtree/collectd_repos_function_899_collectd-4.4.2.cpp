TC_HANDLE_T
TC_INIT(const char *tablename)
{
	TC_HANDLE_T h;
	STRUCT_GETINFO info;
	unsigned int tmp;
	socklen_t s;

	iptc_fn = TC_INIT;

	if (strlen(tablename) >= TABLE_MAXNAMELEN) {
		errno = EINVAL;
		return NULL;
	}
	
	if (sockfd_use == 0) {
		sockfd = socket(TC_AF, SOCK_RAW, IPPROTO_RAW);
		if (sockfd < 0)
			return NULL;
	}
	sockfd_use++;

	s = sizeof(info);

	strcpy(info.name, tablename);
	if (getsockopt(sockfd, TC_IPPROTO, SO_GET_INFO, &info, &s) < 0) {
		if (--sockfd_use == 0) {
			close(sockfd);
			sockfd = -1;
		}
		return NULL;
	}

	DEBUGP("valid_hooks=0x%08x, num_entries=%u, size=%u\n",
		info.valid_hooks, info.num_entries, info.size);

	if ((h = alloc_handle(info.name, info.size, info.num_entries))
	    == NULL) {
		if (--sockfd_use == 0) {
			close(sockfd);
			sockfd = -1;
		}
		return NULL;
	}

	/* Initialize current state */
	h->info = info;

	h->entries->size = h->info.size;

	tmp = sizeof(STRUCT_GET_ENTRIES) + h->info.size;

	if (getsockopt(sockfd, TC_IPPROTO, SO_GET_ENTRIES, h->entries,
		       &tmp) < 0)
		goto error;

#ifdef IPTC_DEBUG2
	{
		int fd = open("/tmp/libiptc-so_get_entries.blob", 
				O_CREAT|O_WRONLY);
		if (fd >= 0) {
			write(fd, h->entries, tmp);
			close(fd);
		}
	}
#endif

	if (parse_table(h) < 0)
		goto error;

	CHECK(h);
	return h;
error:
	TC_FREE(&h);
	return NULL;
}