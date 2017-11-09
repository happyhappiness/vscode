int combine_notes_cat_sort_uniq(unsigned char *cur_sha1,
		const unsigned char *new_sha1)
{
	struct string_list sort_uniq_list = STRING_LIST_INIT_DUP;
	struct strbuf buf = STRBUF_INIT;
	int ret = 1;

	/* read both note blob objects into unique_lines */
	if (string_list_add_note_lines(&sort_uniq_list, cur_sha1))
		goto out;
	if (string_list_add_note_lines(&sort_uniq_list, new_sha1))
		goto out;
	string_list_remove_empty_items(&sort_uniq_list, 0);
	string_list_sort(&sort_uniq_list);
	string_list_remove_duplicates(&sort_uniq_list, 0);

	/* create a new blob object from sort_uniq_list */
	if (for_each_string_list(&sort_uniq_list,
				 string_list_join_lines_helper, &buf))
		goto out;

	ret = write_sha1_file(buf.buf, buf.len, blob_type, cur_sha1);

out:
	strbuf_release(&buf);
	string_list_clear(&sort_uniq_list, 0);
	return ret;
}