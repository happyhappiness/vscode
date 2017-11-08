char *apply_refspecs(struct refspec *refspecs, int nr_refspec,
		     const char *name)
{
	struct refspec query;

	memset(&query, 0, sizeof(struct refspec));
	query.src = (char *)name;

	if (query_refspecs(refspecs, nr_refspec, &query))
		return NULL;

	return query.dst;
}