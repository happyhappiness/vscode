static size_t add_empty_words(struct ewah_bitmap *self, int v, size_t number)
{
	size_t added = 0;
	eword_t runlen, can_add;

	if (rlw_get_run_bit(self->rlw) != v && rlw_size(self->rlw) == 0) {
		rlw_set_run_bit(self->rlw, v);
	} else if (rlw_get_literal_words(self->rlw) != 0 ||
			rlw_get_run_bit(self->rlw) != v) {
		buffer_push_rlw(self, 0);
		if (v) rlw_set_run_bit(self->rlw, v);
		added++;
	}

	runlen = rlw_get_running_len(self->rlw);
	can_add = min_size(number, RLW_LARGEST_RUNNING_COUNT - runlen);

	rlw_set_running_len(self->rlw, runlen + can_add);
	number -= can_add;

	while (number >= RLW_LARGEST_RUNNING_COUNT) {
		buffer_push_rlw(self, 0);
		added++;
		if (v) rlw_set_run_bit(self->rlw, v);
		rlw_set_running_len(self->rlw, RLW_LARGEST_RUNNING_COUNT);
		number -= RLW_LARGEST_RUNNING_COUNT;
	}

	if (number > 0) {
		buffer_push_rlw(self, 0);
		added++;

		if (v) rlw_set_run_bit(self->rlw, v);
		rlw_set_running_len(self->rlw, number);
	}

	return added;
}