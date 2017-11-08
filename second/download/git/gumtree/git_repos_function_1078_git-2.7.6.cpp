void http_cleanup(void)
{
	struct active_request_slot *slot = active_queue_head;

	while (slot != NULL) {
		struct active_request_slot *next = slot->next;
		if (slot->curl != NULL) {
#ifdef USE_CURL_MULTI
			curl_multi_remove_handle(curlm, slot->curl);
#endif
			curl_easy_cleanup(slot->curl);
		}
		free(slot);
		slot = next;
	}
	active_queue_head = NULL;

#ifndef NO_CURL_EASY_DUPHANDLE
	curl_easy_cleanup(curl_default);
#endif

#ifdef USE_CURL_MULTI
	curl_multi_cleanup(curlm);
#endif
	curl_global_cleanup();

	curl_slist_free_all(pragma_header);
	pragma_header = NULL;

	curl_slist_free_all(no_pragma_header);
	no_pragma_header = NULL;

	if (curl_http_proxy) {
		free((void *)curl_http_proxy);
		curl_http_proxy = NULL;
	}

	if (cert_auth.password != NULL) {
		memset(cert_auth.password, 0, strlen(cert_auth.password));
		free(cert_auth.password);
		cert_auth.password = NULL;
	}
	ssl_cert_password_required = 0;

	free(cached_accept_language);
	cached_accept_language = NULL;
}