{
		const unsigned char *p;

		while (pax->sparse_list != NULL &&
		    pax->sparse_list->remaining == 0) {
			struct sparse_block *sb = pax->sparse_list->next;
			free(pax->sparse_list);
			pax->sparse_list = sb;
		}

		if (pax->sparse_list == NULL)
			return (total);

		p = ((const unsigned char *)buff) + total;
		ws = s - total;
		if (ws > pax->sparse_list->remaining)
			ws = (size_t)pax->sparse_list->remaining;

		if (pax->sparse_list->is_hole) {
			/* Current block is hole thus we do not write
			 * the body. */
			pax->sparse_list->remaining -= ws;
			total += ws;
			continue;
		}

		ret = __archive_write_output(a, p, ws);
		pax->sparse_list->remaining -= ws;
		total += ws;
		if (ret != ARCHIVE_OK)
			return (ret);
	}