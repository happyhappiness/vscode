int parse_options_concat(struct option *dst, size_t dst_size, struct option *src)
{
	int i, j;

	for (i = 0; i < dst_size; i++)
		if (dst[i].type == OPTION_END)
			break;
	for (j = 0; i < dst_size; i++, j++) {
		dst[i] = src[j];
		if (src[j].type == OPTION_END)
			return 0;
	}
	return -1;
}