static inline unsigned long
iptcb_entry2offset(const TC_HANDLE_T h, const STRUCT_ENTRY *e)
{
	return (void *)e - (void *)h->entries->entrytable;
}