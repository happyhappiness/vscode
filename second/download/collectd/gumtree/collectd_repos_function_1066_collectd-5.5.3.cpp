static void cna_handle_volume_sis_data (const host_config_t *host, /* {{{ */
		data_volume_usage_t *v, na_elem_t *sis)
{
	const char *sis_state;
	uint64_t sis_saved_reported;

	if (na_elem_child(sis, "sis-info"))
		sis = na_elem_child(sis, "sis-info");

	sis_state = na_child_get_string(sis, "state");
	if (sis_state == NULL)
		return;

	/* If SIS is not enabled, there's nothing left to do for this volume. */
	if (strcmp ("enabled", sis_state) != 0)
		return;

	sis_saved_reported = na_child_get_uint64(sis, "size-saved", UINT64_MAX);
	if (sis_saved_reported == UINT64_MAX)
		return;

	/* size-saved is actually a 32 bit number, so ... time for some guesswork. */
	if ((sis_saved_reported >> 32) != 0) {
		/* In case they ever fix this bug. */
		v->sis_saved = sis_saved_reported;
		v->flags |= HAVE_VOLUME_USAGE_SIS_SAVED;
	} else { /* really hacky work-around code. {{{ */
		uint64_t sis_saved_percent;
		uint64_t sis_saved_guess;
		uint64_t overflow_guess;
		uint64_t guess1, guess2, guess3;

		/* Check if we have v->norm_used. Without it, we cannot calculate
		 * sis_saved_guess. */
		if ((v->flags & HAVE_VOLUME_USAGE_NORM_USED) == 0)
			return;

		sis_saved_percent = na_child_get_uint64(sis, "percentage-saved", UINT64_MAX);
		if (sis_saved_percent > 100)
			return;

		/* The "size-saved" value is a 32bit unsigned integer. This is a bug and
		 * will hopefully be fixed in later versions. To work around the bug, try
		 * to figure out how often the 32bit integer wrapped around by using the
		 * "percentage-saved" value. Because the percentage is in the range
		 * [0-100], this should work as long as the saved space does not exceed
		 * 400 GBytes. */
		/* percentage-saved = size-saved / (size-saved + size-used) */
		if (sis_saved_percent < 100)
			sis_saved_guess = v->norm_used * sis_saved_percent / (100 - sis_saved_percent);
		else
			sis_saved_guess = v->norm_used;

		overflow_guess = sis_saved_guess >> 32;
		guess1 = overflow_guess ? ((overflow_guess - 1) << 32) + sis_saved_reported : sis_saved_reported;
		guess2 = (overflow_guess << 32) + sis_saved_reported;
		guess3 = ((overflow_guess + 1) << 32) + sis_saved_reported;

		if (sis_saved_guess < guess2) {
			if ((sis_saved_guess - guess1) < (guess2 - sis_saved_guess))
				v->sis_saved = guess1;
			else
				v->sis_saved = guess2;
		} else {
			if ((sis_saved_guess - guess2) < (guess3 - sis_saved_guess))
				v->sis_saved = guess2;
			else
				v->sis_saved = guess3;
		}
		v->flags |= HAVE_VOLUME_USAGE_SIS_SAVED;
	} /* }}} end of 32-bit workaround */
}