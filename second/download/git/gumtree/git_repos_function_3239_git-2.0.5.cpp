static int match_name_with_pattern(const char *key, const char *name,
				   const char *value, char **result)
{
	const char *kstar = strchr(key, '*');
	size_t klen;
	size_t ksuffixlen;
	size_t namelen;
	int ret;
	if (!kstar)
		die("Key '%s' of pattern had no '*'", key);
	klen = kstar - key;
	ksuffixlen = strlen(kstar + 1);
	namelen = strlen(name);
	ret = !strncmp(name, key, klen) && namelen >= klen + ksuffixlen &&
		!memcmp(name + namelen - ksuffixlen, kstar + 1, ksuffixlen);
	if (ret && value) {
		const char *vstar = strchr(value, '*');
		size_t vlen;
		size_t vsuffixlen;
		if (!vstar)
			die("Value '%s' of pattern has no '*'", value);
		vlen = vstar - value;
		vsuffixlen = strlen(vstar + 1);
		*result = xmalloc(vlen + vsuffixlen +
				  strlen(name) -
				  klen - ksuffixlen + 1);
		strncpy(*result, value, vlen);
		strncpy(*result + vlen,
			name + klen, namelen - klen - ksuffixlen);
		strcpy(*result + vlen + namelen - klen - ksuffixlen,
		       vstar + 1);
	}
	return ret;
}