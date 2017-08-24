{
		next = attr->next;
		free(attr->name);
		free(attr->value);
		free(attr);
		attr = next;
	}