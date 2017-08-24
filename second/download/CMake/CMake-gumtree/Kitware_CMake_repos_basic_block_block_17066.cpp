(pax->sparse_list) {
			struct sparse_block *sb;
			if (!pax->sparse_list->is_hole)
				remaining += pax->sparse_list->remaining;
			sb = pax->sparse_list->next;
			free(pax->sparse_list);
			pax->sparse_list = sb;
		}