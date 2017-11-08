void unplug_bulk_checkin(void)
{
	state.plugged = 0;
	if (state.f)
		finish_bulk_checkin(&state);
}