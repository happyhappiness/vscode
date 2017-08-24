{
		if (!tree_current_file_information(t, &t->lst, 1))
			return NULL;
		t->flags |= hasLstat;
	}