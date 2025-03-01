do {
		struct extr_rec *extr;

		r = _write_directory_descriptors(a, vdd, np, depth);
		if (r < 0)
			return (r);
		if (vdd->vdd_type != VDD_JOLIET) {
			/*
			 * This extract record is used by SUSP,RRIP.
			 * Not for joliet.
			 */
			for (extr = np->extr_rec_list.first;
			    extr != NULL;
			    extr = extr->next) {
				unsigned char *wb;

				wb = wb_buffptr(a);
				memcpy(wb, extr->buf, extr->offset);
				memset(wb + extr->offset, 0,
				    LOGICAL_BLOCK_SIZE - extr->offset);
				r = wb_consume(a, LOGICAL_BLOCK_SIZE);
				if (r < 0)
					return (r);
			}
		}

		if (np->subdirs.first != NULL && depth + 1 < vdd->max_depth) {
			/* Enter to sub directories. */
			np = np->subdirs.first;
			depth++;
			continue;
		}
		while (np != np->parent) {
			if (np->drnext == NULL) {
				/* Return to the parent directory. */
				np = np->parent;
				depth--;
			} else {
				np = np->drnext;
				break;
			}
		}
	} while (np != np->parent);