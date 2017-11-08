void release_http_pack_request(struct http_pack_request *preq)
{
	if (preq->packfile != NULL) {
		fclose(preq->packfile);
		preq->packfile = NULL;
	}
	if (preq->range_header != NULL) {
		curl_slist_free_all(preq->range_header);
		preq->range_header = NULL;
	}
	preq->slot = NULL;
	free(preq->url);
}