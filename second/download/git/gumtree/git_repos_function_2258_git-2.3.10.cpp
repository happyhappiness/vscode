static void update_first(struct trailer_item **first)
{
	if (*first)
		while ((*first)->previous != NULL)
			*first = (*first)->previous;
}