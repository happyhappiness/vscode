static void closedown_active_slot(struct active_request_slot *slot)
{
	active_requests--;
	slot->in_use = 0;
}