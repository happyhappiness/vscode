static struct reflog_expire_cfg *find_cfg_ent(const char *pattern, size_t len)
{
	struct reflog_expire_cfg *ent;

	if (!reflog_expire_cfg_tail)
		reflog_expire_cfg_tail = &reflog_expire_cfg;

	for (ent = reflog_expire_cfg; ent; ent = ent->next)
		if (ent->len == len &&
		    !memcmp(ent->pattern, pattern, len))
			return ent;

	ent = xcalloc(1, (sizeof(*ent) + len));
	memcpy(ent->pattern, pattern, len);
	ent->len = len;
	*reflog_expire_cfg_tail = ent;
	reflog_expire_cfg_tail = &(ent->next);
	return ent;
}