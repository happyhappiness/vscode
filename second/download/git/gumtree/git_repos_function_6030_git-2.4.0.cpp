static void convert_tree(void *buffer, unsigned long size, unsigned char *result_sha1)
{
	void *orig_buffer = buffer;
	unsigned long orig_size = size;

	while (size) {
		size_t len = 1+strlen(buffer);

		convert_binary_sha1((char *) buffer + len);

		len += 20;
		if (len > size)
			die("corrupt tree object");
		size -= len;
		buffer = (char *) buffer + len;
	}

	write_subdirectory(orig_buffer, orig_size, "", 0, result_sha1);
}