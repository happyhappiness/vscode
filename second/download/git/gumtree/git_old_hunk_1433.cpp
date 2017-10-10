					m->data.sets[k]);
		}
	} else {
		for (k = 0; k < 1024; k++) {
			if (m->data.marked[k])
				fprintf(f, ":%" PRIuMAX " %s\n", base + k,
					sha1_to_hex(m->data.marked[k]->idx.sha1));
		}
	}
}

static void dump_marks(void)
{
