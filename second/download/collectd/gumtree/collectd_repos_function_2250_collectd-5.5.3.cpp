int value_to_rate (value_t *ret_rate, derive_t value, /* {{{ */
		value_to_rate_state_t *state,
		int ds_type, cdtime_t t)
{
	double interval;

	/* Another invalid state: The time is not increasing. */
	if (t <= state->last_time)
	{
		memset (state, 0, sizeof (*state));
		return (EINVAL);
	}

	interval = CDTIME_T_TO_DOUBLE(t - state->last_time);

	/* Previous value is invalid. */
	if (state->last_time == 0) /* {{{ */
	{
		if (ds_type == DS_TYPE_DERIVE)
		{
			state->last_value.derive = value;
		}
		else if (ds_type == DS_TYPE_COUNTER)
		{
			state->last_value.counter = (counter_t) value;
		}
		else if (ds_type == DS_TYPE_ABSOLUTE)
		{
			state->last_value.absolute = (absolute_t) value;
		}
		else
		{
			assert (23 == 42);
		}

		state->last_time = t;
		return (EAGAIN);
	} /* }}} */

	if (ds_type == DS_TYPE_DERIVE)
	{
		ret_rate->gauge = (value - state->last_value.derive) / interval;
		state->last_value.derive = value;
	}
	else if (ds_type == DS_TYPE_COUNTER)
	{
		ret_rate->gauge = (((counter_t)value) - state->last_value.counter) / interval;
		state->last_value.counter = (counter_t) value;
	}
	else if (ds_type == DS_TYPE_ABSOLUTE)
	{
		ret_rate->gauge = (((absolute_t)value) - state->last_value.absolute) / interval;
		state->last_value.absolute = (absolute_t) value;
	}
	else
	{
		assert (23 == 42);
	}

        state->last_time = t;
	return (0);
}