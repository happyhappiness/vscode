static inline STRUCT_ENTRY *
iptcb_offset2entry(TC_HANDLE_T h, unsigned int offset)
{
	return (STRUCT_ENTRY *) ((void *)h->entries->entrytable+offset);
}