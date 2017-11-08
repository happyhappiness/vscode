static inline struct blame_origin *blame_origin_incref(struct blame_origin *o)
{
	if (o)
		o->refcnt++;
	return o;
}