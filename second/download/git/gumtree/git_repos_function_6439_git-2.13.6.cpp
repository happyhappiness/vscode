int svndiff0_apply(struct line_buffer *delta, off_t delta_len,
			struct sliding_view *preimage, FILE *postimage)
{
	assert(delta && preimage && postimage && delta_len >= 0);

	if (read_magic(delta, &delta_len))
		return -1;
	while (delta_len) {	/* For each window: */
		off_t pre_off = -1;
		size_t pre_len;

		if (read_offset(delta, &pre_off, &delta_len) ||
		    read_length(delta, &pre_len, &delta_len) ||
		    move_window(preimage, pre_off, pre_len) ||
		    apply_one_window(delta, &delta_len, preimage, postimage))
			return -1;
	}
	return 0;
}