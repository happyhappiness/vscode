static inline STRUCT_ENTRY *
iptcb_get_entry(TC_HANDLE_T h, unsigned int offset)
{
	return (STRUCT_ENTRY *)((char *)h->entries->entrytable + offset);
}