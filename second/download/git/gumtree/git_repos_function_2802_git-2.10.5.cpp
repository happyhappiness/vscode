static int ranges_overlap(struct range *a, struct range *b)
{
	return !(a->end <= b->start || b->end <= a->start);
}