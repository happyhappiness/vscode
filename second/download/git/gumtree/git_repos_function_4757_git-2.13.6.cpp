static inline size_t rlwit_literal_words(struct rlw_iterator *it)
{
	return it->pointer - it->rlw.literal_words;
}