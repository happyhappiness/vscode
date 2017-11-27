int rate_to_value (value_t *ret_value, gauge_t rate, /* {{{ */
		rate_to_value_state_t *state,
		int ds_type, cdtime_t t)
{
	gauge_t delta_gauge;
	cdtime_t delta_t;

	if (ds_type == DS_TYPE_GAUGE)
	{
		state->last_value.gauge = rate;
		state->last_time = t;

		*ret_value = state->last_value;
		return (0);
	}

	/* Counter and absolute can't handle negative rates. Reset "last time"
	 * to zero, so that the next valid rate will re-initialize the
	 * structure. */
	if ((rate < 0.0)
			&& ((ds_type == DS_TYPE_COUNTER)
				|| (ds_type == DS_TYPE_ABSOLUTE)))
	{
		memset (state, 0, sizeof (*state));
		return (EINVAL);
	}

	/* Another invalid state: The time is not increasing. */
	if (t <= state->last_time)
	{
		memset (state, 0, sizeof (*state));
		return (EINVAL);
	}

	delta_t = t - state->last_time;
	delta_gauge = (rate * CDTIME_T_TO_DOUBLE (delta_t)) + state->residual;

	/* Previous value is invalid. */
	if (state->last_time == 0) /* {{{ */
	{
		if (ds_type == DS_TYPE_DERIVE)
		{
			state->last_value.derive = (derive_t) rate;
			state->residual = rate - ((gauge_t) state->last_value.derive);
		}
		else if (ds_type == DS_TYPE_COUNTER)
		{
			state->last_value.counter = (counter_t) rate;
			state->residual = rate - ((gauge_t) state->last_value.counter);
		}
		else if (ds_type == DS_TYPE_ABSOLUTE)
		{
			state->last_value.absolute = (absolute_t) rate;
			state->residual = rate - ((gauge_t) state->last_value.absolute);
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
		derive_t delta_derive = (derive_t) delta_gauge;

		state->last_value.derive += delta_derive;
		state->residual = delta_gauge - ((gauge_t) delta_derive);
	}
	else if (ds_type == DS_TYPE_COUNTER)
	{
		counter_t delta_counter = (counter_t) delta_gauge;

		state->last_value.counter += delta_counter;
		state->residual = delta_gauge - ((gauge_t) delta_counter);
	}
	else if (ds_type == DS_TYPE_ABSOLUTE)
	{
		absolute_t delta_absolute = (absolute_t) delta_gauge;

		state->last_value.absolute = delta_absolute;
		state->residual = delta_gauge - ((gauge_t) delta_absolute);
	}
	else
	{
		assert (23 == 42);
	}

        state->last_time = t;
	*ret_value = state->last_value;
	return (0);
}