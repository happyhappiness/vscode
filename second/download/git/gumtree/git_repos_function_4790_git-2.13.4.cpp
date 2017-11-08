static size_t add_empty_word(struct ewah_bitmap *self, int v)
{
	int no_literal = (rlw_get_literal_words(self->rlw) == 0);
	eword_t run_len = rlw_get_running_len(self->rlw);

	if (no_literal && run_len == 0) {
		rlw_set_run_bit(self->rlw, v);
		assert(rlw_get_run_bit(self->rlw) == v);
	}

	if (no_literal && rlw_get_run_bit(self->rlw) == v &&
		run_len < RLW_LARGEST_RUNNING_COUNT) {
		rlw_set_running_len(self->rlw, run_len + 1);
		assert(rlw_get_running_len(self->rlw) == run_len + 1);
		return 0;
	} else {
		buffer_push_rlw(self, 0);

		assert(rlw_get_running_len(self->rlw) == 0);
		assert(rlw_get_run_bit(self->rlw) == 0);
		assert(rlw_get_literal_words(self->rlw) == 0);

		rlw_set_run_bit(self->rlw, v);
		assert(rlw_get_run_bit(self->rlw) == v);

		rlw_set_running_len(self->rlw, 1);
		assert(rlw_get_running_len(self->rlw) == 1);
		assert(rlw_get_literal_words(self->rlw) == 0);
		return 1;
	}
}