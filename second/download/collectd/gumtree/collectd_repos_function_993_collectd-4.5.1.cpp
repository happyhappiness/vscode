void
TC_FREE(TC_HANDLE_T *h)
{
	struct chain_head *c, *tmp;

	iptc_fn = TC_FREE;
	if (--sockfd_use == 0) {
		close(sockfd);
		sockfd = -1;
	}

	list_for_each_entry_safe(c, tmp, &(*h)->chains, list) {
		struct rule_head *r, *rtmp;

		list_for_each_entry_safe(r, rtmp, &c->rules, list) {
			free(r);
		}

		free(c);
	}

	free((*h)->entries);
	free(*h);

	*h = NULL;
}