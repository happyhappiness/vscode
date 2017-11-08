int transport_summary_width(const struct ref *refs)
{
	int maxw = -1;

	for (; refs; refs = refs->next) {
		maxw = measure_abbrev(&refs->old_oid, maxw);
		maxw = measure_abbrev(&refs->new_oid, maxw);
	}
	if (maxw < 0)
		maxw = FALLBACK_DEFAULT_ABBREV;
	return (2 * maxw + 3);
}