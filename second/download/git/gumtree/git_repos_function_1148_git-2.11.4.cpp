static uint32_t hash_line(const char *cp, size_t len)
{
	size_t i;
	uint32_t h;
	for (i = 0, h = 0; i < len; i++) {
		if (!isspace(cp[i])) {
			h = h * 3 + (cp[i] & 0xff);
		}
	}
	return h;
}