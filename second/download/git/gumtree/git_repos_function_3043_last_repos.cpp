static int same_value(struct trailer_item *a, struct arg_item *b)
{
	return !strcasecmp(a->value, b->value);
}