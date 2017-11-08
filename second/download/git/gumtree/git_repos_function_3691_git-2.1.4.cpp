size_t rlwit_discharge(
	struct rlw_iterator *it, struct ewah_bitmap *out, size_t max, int negate)
{
	size_t index = 0;

	while (index < max && rlwit_word_size(it) > 0) {
		size_t pd, pl = it->rlw.running_len;

		if (index + pl > max)
			pl = max - index;

		ewah_add_empty_words(out, it->rlw.running_bit ^ negate, pl);
		index += pl;

		pd = it->rlw.literal_words;
		if (pd + index > max)
			pd = max - index;

		ewah_add_dirty_words(out,
			it->buffer + it->literal_word_start, pd, negate);

		rlwit_discard_first_words(it, pd + pl);
		index += pd;
	}

	return index;
}