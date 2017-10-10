{
	while (*src)
		*dst++ = *src++;
	return dst;
}

/*
 * Parse the object referred by ref, and grab needed value.
 */
static void populate_value(struct ref_array_item *ref)
{
	void *buf;
