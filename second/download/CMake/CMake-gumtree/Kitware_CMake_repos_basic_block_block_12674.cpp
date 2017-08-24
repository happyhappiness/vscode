{
	if (best_bid < 1 && __archive_read_ahead(a, 1, NULL) != NULL)
		return (1);
	return (-1);
}