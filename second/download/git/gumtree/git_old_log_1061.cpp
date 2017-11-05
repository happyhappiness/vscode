fprintf(f, ":%" PRIuMAX " %s\n", base + k,
					sha1_to_hex(m->data.marked[k]->idx.sha1));