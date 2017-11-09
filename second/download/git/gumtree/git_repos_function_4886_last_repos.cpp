void rlwit_init(struct rlw_iterator *it, struct ewah_bitmap *from_ewah)
{
	it->buffer = from_ewah->buffer;
	it->size = from_ewah->buffer_size;
	it->pointer = 0;

	next_word(it);

	it->literal_word_start = rlwit_literal_words(it) +
		it->rlw.literal_word_offset;
}