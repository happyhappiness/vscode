{
		next = head->next;
		free(head->value);
		free(head);
	}