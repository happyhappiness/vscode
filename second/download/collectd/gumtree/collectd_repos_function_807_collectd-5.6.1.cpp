static void type_list_free (type_list_t *t)
{
	type_t *this;

	this = t->head;
	while (this != NULL)
	{
		type_t *next = this->next;

		sfree (this->name);
		sfree (this);

		this = next;
	}

	t->head = NULL;
	t->tail = NULL;
}