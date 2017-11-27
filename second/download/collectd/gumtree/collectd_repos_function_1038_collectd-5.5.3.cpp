static void free_cfg_quota (cfg_quota_t *q) /* {{{ */
{
	if (q == NULL)
		return;

	if (q->query != NULL)
		na_elem_free (q->query);

	sfree (q);
}