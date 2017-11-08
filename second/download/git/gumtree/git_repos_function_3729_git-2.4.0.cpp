int combine_notes_overwrite(unsigned char *cur_sha1,
		const unsigned char *new_sha1)
{
	hashcpy(cur_sha1, new_sha1);
	return 0;
}