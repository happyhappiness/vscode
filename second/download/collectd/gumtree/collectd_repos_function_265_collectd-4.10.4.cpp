void ignorelist_free (ignorelist_t *il)
{
	ignorelist_item_t *this;
	ignorelist_item_t *next;

	if (il == NULL)
		return;

	for (this = il->head; this != NULL; this = next)
	{
		next = this->next;
#if HAVE_REGEX_H
		if (this->rmatch != NULL)
		{
			regfree (this->rmatch);
			this->rmatch = NULL;
		}
#endif
		if (this->smatch != NULL)
		{
			sfree (this->smatch);
			this->smatch = NULL;
		}
		sfree (this);
	}

	sfree (il);
	il = NULL;
}