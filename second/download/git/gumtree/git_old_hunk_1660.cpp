int fast_export_ls(const char *path, uint32_t *mode, struct strbuf *dataref)
{
	ls_from_active_commit(path);
	return parse_ls_response(get_response_line(), mode, dataref);
}

void fast_export_blob_delta(uint32_t mode,
				uint32_t old_mode, const char *old_data,
				off_t len, struct line_buffer *input)
{
	long postimage_len;

	assert(len >= 0);
	postimage_len = apply_delta(len, input, old_data, old_mode);
	if (mode == REPO_MODE_LNK) {
		buffer_skip_bytes(&postimage, strlen("link "));
		postimage_len -= strlen("link ");
	}
	printf("data %ld\n", postimage_len);
	buffer_copy_bytes(&postimage, postimage_len);
	fputc('\n', stdout);
