static int cna_handle_volume_usage_data (const host_config_t *host, /* {{{ */
		cfg_volume_usage_t *cfg_volume, na_elem_t *data)
{
	na_elem_t *elem_volume;
	na_elem_t *elem_volumes;
	na_elem_iter_t iter_volume;

	elem_volumes = na_elem_child (data, "volumes");
	if (elem_volumes == NULL)
	{
		ERROR ("netapp plugin: cna_handle_volume_usage_data: "
				"na_elem_child (\"volumes\") failed "
				"for host %s.", host->name);
		return (-1);
	}

	iter_volume = na_child_iterator (elem_volumes);
	for (elem_volume = na_iterator_next (&iter_volume);
			elem_volume != NULL;
			elem_volume = na_iterator_next (&iter_volume))
	{
		const char *volume_name, *state;

		data_volume_usage_t *v;
		uint64_t value;

		na_elem_t *sis;
		const char *sis_state;
		uint64_t sis_saved_reported;

		volume_name = na_child_get_string (elem_volume, "name");
		if (volume_name == NULL)
			continue;

		state = na_child_get_string (elem_volume, "state");
		if ((state == NULL) || (strcmp(state, "online") != 0))
			continue;

		/* get_volume_usage may return NULL if the volume is to be ignored. */
		v = get_volume_usage (cfg_volume, volume_name);
		if (v == NULL)
			continue;

		if ((v->flags & CFG_VOLUME_USAGE_SNAP) != 0)
			cna_handle_volume_snap_usage(host, v);
		
		if ((v->flags & CFG_VOLUME_USAGE_DF) == 0)
			continue;

		/* 2^4 exa-bytes? This will take a while ;) */
		value = na_child_get_uint64(elem_volume, "size-available", UINT64_MAX);
		if (value != UINT64_MAX) {
			v->norm_free = value;
			v->flags |= HAVE_VOLUME_USAGE_NORM_FREE;
		}

		value = na_child_get_uint64(elem_volume, "size-used", UINT64_MAX);
		if (value != UINT64_MAX) {
			v->norm_used = value;
			v->flags |= HAVE_VOLUME_USAGE_NORM_USED;
		}

		value = na_child_get_uint64(elem_volume, "snapshot-blocks-reserved", UINT64_MAX);
		if (value != UINT64_MAX) {
			/* 1 block == 1024 bytes  as per API docs */
			v->snap_reserved = 1024 * value;
			v->flags |= HAVE_VOLUME_USAGE_SNAP_RSVD;
		}

		sis = na_elem_child(elem_volume, "sis");
		if (sis == NULL)
			continue;

		if (na_elem_child(sis, "sis-info"))
			sis = na_elem_child(sis, "sis-info");
		
		sis_state = na_child_get_string(sis, "state");
		if (sis_state == NULL)
			continue;

		/* If SIS is not enabled, there's nothing left to do for this volume. */
		if (strcmp ("enabled", sis_state) != 0)
			continue;

		sis_saved_reported = na_child_get_uint64(sis, "size-saved", UINT64_MAX);
		if (sis_saved_reported == UINT64_MAX)
			continue;

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
				continue;

			sis_saved_percent = na_child_get_uint64(sis, "percentage-saved", UINT64_MAX);
			if (sis_saved_percent > 100)
				continue;

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
	} /* for (elem_volume) */

	return (cna_submit_volume_usage_data (host->name, cfg_volume, host->interval));
}