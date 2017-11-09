static void am_rerere_clear(void)
{
	struct string_list merge_rr = STRING_LIST_INIT_DUP;
	rerere_clear(&merge_rr);
	string_list_clear(&merge_rr, 1);
}