static void sensors_free_features (void)
{
	featurelist_t *thisft;
	featurelist_t *nextft;

	if (first_feature == NULL)
		return;

	sensors_cleanup ();

	for (thisft = first_feature; thisft != NULL; thisft = nextft)
	{
		nextft = thisft->next;
		sfree (thisft);
	}
	first_feature = NULL;
}