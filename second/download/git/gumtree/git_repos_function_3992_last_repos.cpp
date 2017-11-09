static void run_request_queue(void)
{
#ifdef USE_CURL_MULTI
	is_running_queue = 1;
	fill_active_slots();
	add_fill_function(NULL, fill_active_slot);
#endif
	do {
		finish_all_active_slots();
#ifdef USE_CURL_MULTI
		fill_active_slots();
#endif
	} while (request_queue_head && !aborted);

#ifdef USE_CURL_MULTI
	is_running_queue = 0;
#endif
}