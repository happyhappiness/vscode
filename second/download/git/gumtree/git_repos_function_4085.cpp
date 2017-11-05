void rlwit_discharge_empty(struct rlw_iterator *it, struct ewah_bitmap *out)
{
	while (rlwit_word_size(it) > 0) {
		ewah_add_empty_words(out, 0, rlwit_word_size(it));
		rlwit_discard_first_words(it, rlwit_word_size(it));
	}
}