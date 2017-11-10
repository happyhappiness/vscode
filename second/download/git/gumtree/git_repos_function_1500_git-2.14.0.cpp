void release_http_pack_request(struct http_pack_request *preq)
{
	if (preq->packfile != NULL) {
		fclose(preq->packfile);
		preq->packfile = NULL;
	}
	preq->slot = NULL;
	free(preq->url);
	free(preq);
}