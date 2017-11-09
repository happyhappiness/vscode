static inline size_t rlwit_word_size(struct rlw_iterator *it)
{
	return it->rlw.running_len + it->rlw.literal_words;
}