		struct ref_entry *entry = dir->entries[i];
		if (entry->flag & REF_DIR)
			prime_ref_dir(get_ref_dir(entry));
	}
}

struct nonmatching_ref_data {
	const struct string_list *skip;
	const char *conflicting_refname;
};

static int nonmatching_ref_fn(struct ref_entry *entry, void *vdata)
