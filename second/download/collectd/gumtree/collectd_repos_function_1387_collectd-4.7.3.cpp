static inline unsigned int
iptcb_ent_is_hook_entry(STRUCT_ENTRY *e, TC_HANDLE_T h)
{
	unsigned int i;

	for (i = 0; i < NUMHOOKS; i++) {
		if ((h->info.valid_hooks & (1 << i))
		    && iptcb_get_entry(h, h->info.hook_entry[i]) == e)
			return i+1;
	}
	return 0;
}