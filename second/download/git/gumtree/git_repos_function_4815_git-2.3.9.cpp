static int find_boundary(void)
{
	while (!strbuf_getline(&line, fin, '\n')) {
		if (*content_top && is_multipart_boundary(&line))
			return 1;
	}
	return 0;
}