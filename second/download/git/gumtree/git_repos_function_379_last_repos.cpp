static int ce_flush(git_SHA_CTX *context, int fd, unsigned char *sha1)
{
	unsigned int left = write_buffer_len;

	if (left) {
		write_buffer_len = 0;
		git_SHA1_Update(context, write_buffer, left);
	}

	/* Flush first if not enough space for SHA1 signature */
	if (left + 20 > WRITE_BUFFER_SIZE) {
		if (write_in_full(fd, write_buffer, left) != left)
			return -1;
		left = 0;
	}

	/* Append the SHA1 signature at the end */
	git_SHA1_Final(write_buffer + left, context);
	hashcpy(sha1, write_buffer + left);
	left += 20;
	return (write_in_full(fd, write_buffer, left) != left) ? -1 : 0;
}