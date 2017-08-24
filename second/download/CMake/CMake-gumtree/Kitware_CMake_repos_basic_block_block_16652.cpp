{
			ac->prev = pac;
			ac->next = pac->next;
			pac->next = ac;
			if (ac->next != NULL)
				ac->next->prev = ac;
		}