static void xmulti_remove_handle(struct active_request_slot *slot)
{
#ifdef USE_CURL_MULTI
	curl_multi_remove_handle(curlm, slot->curl);
#endif
}