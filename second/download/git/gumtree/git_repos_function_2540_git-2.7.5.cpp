static int find_patch_start(struct strbuf **lines, int count)
{
	int i;

	/* Get the start of the patch part if any */
	for (i = 0; i < count; i++) {
		if (starts_with(lines[i]->buf, "---"))
			return i;
	}

	return count;
}