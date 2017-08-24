{
		struct sparse_block *sb = pax->sparse_list;
		pax->sparse_list = sb->next;
		free(sb);
	}