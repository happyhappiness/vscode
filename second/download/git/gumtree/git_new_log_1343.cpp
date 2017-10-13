fprintf(f, ":%" PRIuMAX " %s\n", base + k,
					oid_to_hex(&m->data.marked[k]->idx.oid));