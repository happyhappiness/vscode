static void report_pack_garbage(unsigned seen_bits, const char *path)
{
	if (seen_bits == PACKDIR_FILE_IDX)
		string_list_append(&pack_garbage, path);
}