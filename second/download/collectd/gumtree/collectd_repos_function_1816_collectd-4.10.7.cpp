static inline int
iptcb_get_entry_n(STRUCT_ENTRY *i,
	    unsigned int number,
	    unsigned int *pos,
	    STRUCT_ENTRY **pe)
{
	if (*pos == number) {
		*pe = i;
		return 1;
	}
	(*pos)++;
	return 0;
}