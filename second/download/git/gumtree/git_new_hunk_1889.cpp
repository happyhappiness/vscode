	klen = kstar - key;
	ksuffixlen = strlen(kstar + 1);
	namelen = strlen(name);
	ret = !strncmp(name, key, klen) && namelen >= klen + ksuffixlen &&
		!memcmp(name + namelen - ksuffixlen, kstar + 1, ksuffixlen);
	if (ret && value) {
		struct strbuf sb = STRBUF_INIT;
		const char *vstar = strchr(value, '*');
		if (!vstar)
			die("Value '%s' of pattern has no '*'", value);
		strbuf_add(&sb, value, vstar - value);
		strbuf_add(&sb, name + klen, namelen - klen - ksuffixlen);
		strbuf_addstr(&sb, vstar + 1);
		*result = strbuf_detach(&sb, NULL);
	}
	return ret;
}

static void query_refspecs_multiple(struct refspec *refs, int ref_count, struct refspec *query, struct string_list *results)
{
