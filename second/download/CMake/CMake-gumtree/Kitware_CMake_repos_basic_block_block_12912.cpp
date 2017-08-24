(tar->sparse_last != NULL)
		tar->sparse_last->next = p;
	else
		tar->sparse_list = p