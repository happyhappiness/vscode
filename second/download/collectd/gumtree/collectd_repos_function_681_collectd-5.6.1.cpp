static void ps_update_counter (_Bool init, derive_t *group_counter,
				derive_t *curr_counter, unsigned long *curr_value,
				derive_t new_counter, unsigned long new_value)
{
	if (init)
	{
		*curr_value = new_value;
		*curr_counter += new_value;
		*group_counter += new_value;
		return;
	}

	if (new_counter < *curr_counter)
		*curr_value = new_counter + (ULONG_MAX - *curr_counter);
	else
		*curr_value = new_counter - *curr_counter;

	*curr_counter = new_counter;
	*group_counter += *curr_value;
}