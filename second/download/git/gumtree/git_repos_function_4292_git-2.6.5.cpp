static inline struct origin *origin_incref(struct origin *o)
{
	if (o)
		o->refcnt++;
	return o;
}