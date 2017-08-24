{
		er_next = er->next;
		free(er);
		er = er_next;
	}