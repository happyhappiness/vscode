{
			struct sparse_block *sb = pax->sparse_list->next;
			free(pax->sparse_list);
			pax->sparse_list = sb;
		}