#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}

static void process_alternates_response(void *callback_data)
{
	struct alternates_request *alt_req =
		(struct alternates_request *)callback_data;
	struct walker *walker = alt_req->walker;
	struct walker_data *cdata = walker->data;
