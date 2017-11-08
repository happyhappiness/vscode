static int same_trailer(struct trailer_item *a, struct trailer_item *b)
{
	return same_token(a, b) && same_value(a, b);
}