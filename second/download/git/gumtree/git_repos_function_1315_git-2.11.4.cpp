static void release_active_slot(struct active_request_slot *slot)
{
	closedown_active_slot(slot);
	if (slot->curl) {
		xmulti_remove_handle(slot);
		if (curl_session_count > min_curl_sessions) {
			curl_easy_cleanup(slot->curl);
			slot->curl = NULL;
			curl_session_count--;
		}
	}
#ifdef USE_CURL_MULTI
	fill_active_slots();
#endif
}