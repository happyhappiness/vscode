					m->data.sets[k]);
		}
	} else {
		for (k = 0; k < 1024; k++) {
			if (m->data.marked[k])
				fprintf(f, ":%" PRIuMAX " %s\n", base + k,
					oid_to_hex(&m->data.marked[k]->idx.oid));
		}
	}
}

static void dump_marks(void)
{
