void ewah_and(
	struct ewah_bitmap *ewah_i,
	struct ewah_bitmap *ewah_j,
	struct ewah_bitmap *out)
{
	struct rlw_iterator rlw_i;
	struct rlw_iterator rlw_j;
	size_t literals;

	rlwit_init(&rlw_i, ewah_i);
	rlwit_init(&rlw_j, ewah_j);

	while (rlwit_word_size(&rlw_i) > 0 && rlwit_word_size(&rlw_j) > 0) {
		while (rlw_i.rlw.running_len > 0 || rlw_j.rlw.running_len > 0) {
			struct rlw_iterator *prey, *predator;

			if (rlw_i.rlw.running_len < rlw_j.rlw.running_len) {
				prey = &rlw_i;
				predator = &rlw_j;
			} else {
				prey = &rlw_j;
				predator = &rlw_i;
			}

			if (predator->rlw.running_bit == 0) {
				ewah_add_empty_words(out, 0,
					predator->rlw.running_len);
				rlwit_discard_first_words(prey,
					predator->rlw.running_len);
				rlwit_discard_first_words(predator,
					predator->rlw.running_len);
			} else {
				size_t index = rlwit_discharge(prey, out,
					predator->rlw.running_len, 0);
				ewah_add_empty_words(out, 0,
					predator->rlw.running_len - index);
				rlwit_discard_first_words(predator,
					predator->rlw.running_len);
			}
		}

		literals = min_size(
			rlw_i.rlw.literal_words,
			rlw_j.rlw.literal_words);

		if (literals) {
			size_t k;

			for (k = 0; k < literals; ++k) {
				ewah_add(out,
					rlw_i.buffer[rlw_i.literal_word_start + k] &
					rlw_j.buffer[rlw_j.literal_word_start + k]
				);
			}

			rlwit_discard_first_words(&rlw_i, literals);
			rlwit_discard_first_words(&rlw_j, literals);
		}
	}

	if (rlwit_word_size(&rlw_i) > 0)
		rlwit_discharge_empty(&rlw_i, out);
	else
		rlwit_discharge_empty(&rlw_j, out);

	out->bit_size = max_size(ewah_i->bit_size, ewah_j->bit_size);
}