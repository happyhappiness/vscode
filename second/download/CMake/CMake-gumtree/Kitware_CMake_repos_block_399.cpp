{
	struct private_b64encode *state = (struct private_b64encode *)f->data;
	int ret, ret2;

	/* Flush remaining bytes. */
	if (state->hold_len != 0)
		b64_encode(&state->encoded_buff, state->hold, state->hold_len);
	archive_string_sprintf(&state->encoded_buff, "====\n");
	/* Write the last block */
	archive_write_set_bytes_in_last_block(f->archive, 1);
	ret = __archive_write_filter(f->next_filter,
	    state->encoded_buff.s, archive_strlen(&state->encoded_buff));
	ret2 = __archive_write_close_filter(f->next_filter);
	if (ret > ret2)
		ret = ret2;
	return (ret);
}