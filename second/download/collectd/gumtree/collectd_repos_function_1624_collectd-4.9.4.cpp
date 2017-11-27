static int ts_invoke_counter (const data_set_t *ds, value_list_t *vl, /* {{{ */
		ts_data_t *data, int dsrc_index)
{
	uint64_t curr_counter;
	int status;
	int failure;

	/* Required meta data */
	uint64_t prev_counter;
	char key_prev_counter[128];
	uint64_t int_counter;
	char key_int_counter[128];
	double int_fraction;
	char key_int_fraction[128];

	curr_counter = (uint64_t) vl->values[dsrc_index].counter;

	ssnprintf (key_prev_counter, sizeof (key_prev_counter),
			"target_scale[%p,%i]:prev_counter",
			(void *) data, dsrc_index);
	ssnprintf (key_int_counter, sizeof (key_int_counter),
			"target_scale[%p,%i]:int_counter",
			(void *) data, dsrc_index);
	ssnprintf (key_int_fraction, sizeof (key_int_fraction),
			"target_scale[%p,%i]:int_fraction",
			(void *) data, dsrc_index);

	prev_counter = curr_counter;
	int_counter = 0;
	int_fraction = 0.0;

	/* Query the meta data */
	failure = 0;

	status = uc_meta_data_get_unsigned_int (vl, key_prev_counter,
			&prev_counter);
	if (status != 0)
		failure++;

	status = uc_meta_data_get_unsigned_int (vl, key_int_counter, &int_counter);
	if (status != 0)
		failure++;

	status = uc_meta_data_get_double (vl, key_int_fraction, &int_fraction);
	if (status != 0)
		failure++;

	if (failure == 0)
	{
		uint64_t difference;
		double rate;

		/* Calcualte the rate */
		if (prev_counter > curr_counter) /* => counter overflow */
		{
			if (prev_counter <= 4294967295UL) /* 32 bit overflow */
				difference = (4294967295UL - prev_counter) + curr_counter;
			else /* 64 bit overflow */
				difference = (18446744073709551615ULL - prev_counter) + curr_counter;
		}
		else /* no overflow */
		{
			difference = curr_counter - prev_counter;
		}
		rate = ((double) difference) / ((double) vl->interval);

		/* Modify the rate. */
		if (!isnan (data->factor))
			rate *= data->factor;
		if (!isnan (data->offset))
			rate += data->offset;

		/* Calculate the internal counter. */
		int_fraction += (rate * ((double) vl->interval));
		difference = (uint64_t) int_fraction;
		int_fraction -= ((double) difference);
		int_counter  += difference;

		assert (int_fraction >= 0.0);
		assert (int_fraction <  1.0);

		DEBUG ("Target `scale': ts_invoke_counter: %"PRIu64" -> %g -> %"PRIu64
				"(+%g)",
				curr_counter, rate, int_counter, int_fraction);
	}
	else /* (failure != 0) */
	{
		int_counter = 0;
		int_fraction = 0.0;
	}

	vl->values[dsrc_index].counter = (counter_t) int_counter;

	/* Update to the new counter value */
	uc_meta_data_add_unsigned_int (vl, key_prev_counter, curr_counter);
	uc_meta_data_add_unsigned_int (vl, key_int_counter, int_counter);
	uc_meta_data_add_double (vl, key_int_fraction, int_fraction);


	return (0);
}