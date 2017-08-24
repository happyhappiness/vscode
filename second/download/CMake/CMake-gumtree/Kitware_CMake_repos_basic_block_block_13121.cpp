{
		struct hdlink *next = hdlink->next;

		free(hdlink);
		hdlink = next;
	}