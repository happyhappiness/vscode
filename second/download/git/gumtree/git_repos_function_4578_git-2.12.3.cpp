static inline int next_word(struct rlw_iterator *it)
{
	if (it->pointer >= it->size)
		return 0;

	it->rlw.word = &it->buffer[it->pointer];
	it->pointer += rlw_get_literal_words(it->rlw.word) + 1;

	it->rlw.literal_words = rlw_get_literal_words(it->rlw.word);
	it->rlw.running_len = rlw_get_running_len(it->rlw.word);
	it->rlw.running_bit = rlw_get_run_bit(it->rlw.word);
	it->rlw.literal_word_offset = 0;

	return 1;
}