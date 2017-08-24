(ac != NULL) {
		tac = ac->next;
		free(ac);
		ac = tac;
	}