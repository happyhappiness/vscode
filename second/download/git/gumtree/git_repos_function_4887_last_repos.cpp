void rlwit_discard_first_words(struct rlw_iterator *it, size_t x)
{
	while (x > 0) {
		size_t discard;

		if (it->rlw.running_len > x) {
			it->rlw.running_len -= x;
			return;
		}

		x -= it->rlw.running_len;
		it->rlw.running_len = 0;

		discard = (x > it->rlw.literal_words) ? it->rlw.literal_words : x;

		it->literal_word_start += discard;
		it->rlw.literal_words -= discard;
		x -= discard;

		if (x > 0 || rlwit_word_size(it) == 0) {
			if (!next_word(it))
				break;

			it->literal_word_start =
				rlwit_literal_words(it) + it->rlw.literal_word_offset;
		}
	}
}