	return strcmp(xa1->name, xa2->name);
}

static ssize_t get_xattr_names(const char *fname)
{
	ssize_t list_len;
	int64 arg;

	if (!namebuf) {
		namebuf_len = 1024;
		namebuf = new_array(char, namebuf_len);
		if (!namebuf)
			out_of_memory("get_xattr_names");
