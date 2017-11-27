void cf_unregister_complex (const char *type)
{
	cf_complex_callback_t *this, *prev;

	for (prev = NULL, this = complex_callback_head;
			this != NULL;
			prev = this, this = this->next)
		if (strcasecmp (this->type, type) == 0)
		{
			if (prev == NULL)
				complex_callback_head = this->next;
			else
				prev->next = this->next;

			sfree (this->type);
			sfree (this);
			break;
		}
}