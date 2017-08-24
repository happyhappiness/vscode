{
		e = le->canonical;
		if (links != NULL)
			*links = le->links;
		le->canonical = NULL;
	}