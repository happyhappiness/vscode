struct map_struct *map_file(int fd,OFF_T len)
{
	struct map_struct *ret;
	ret = (struct map_struct *)malloc(sizeof(*ret));
	if (!ret) out_of_memory("map_file");

	ret->map = NULL;
	ret->fd = fd;
	ret->size = len;
	ret->p = NULL;
	ret->p_size = 0;
	ret->p_offset = 0;
	ret->p_len = 0;

#ifdef USE_MMAP
	len = MIN(len, MAX_MAP_SIZE);
	ret->map = (char *)do_mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
	if (ret->map == (char *)-1) {
		ret->map = NULL;
	} else {
		ret->p_len = len;
	}
#endif
	return ret;
}