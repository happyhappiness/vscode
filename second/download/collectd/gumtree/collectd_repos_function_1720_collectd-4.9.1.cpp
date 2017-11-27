static unsigned int
iptcb_entry2index(const TC_HANDLE_T h, const STRUCT_ENTRY *seek)
{
	unsigned int pos = 0;

	if (ENTRY_ITERATE(h->entries->entrytable, h->entries->size,
			  iptcb_get_number, seek, &pos) == 0) {
		fprintf(stderr, "ERROR: offset %u not an entry!\n",
			(unsigned int)((char *)seek - (char *)h->entries->entrytable));
		abort();
	}
	return pos;
}