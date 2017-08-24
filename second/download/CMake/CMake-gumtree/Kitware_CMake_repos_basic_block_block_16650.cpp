{
		ac = attr_counter_new(me, last);
		if (ac == NULL)
			return (-1);
		last->next = ac;
	}