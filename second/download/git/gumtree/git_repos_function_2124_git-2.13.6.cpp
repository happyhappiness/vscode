int unpack_sha1_header(git_zstream *stream,
		       unsigned char *map, unsigned long mapsize,
		       void *buffer, unsigned long bufsiz)
{
	int status = unpack_sha1_short_header(stream, map, mapsize,
					      buffer, bufsiz);

	if (status < Z_OK)
		return status;

	/* Make sure we have the terminating NUL */
	if (!memchr(buffer, '\0', stream->next_out - (unsigned char *)buffer))
		return -1;
	return 0;
}