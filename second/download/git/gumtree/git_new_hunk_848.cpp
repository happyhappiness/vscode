		dirlen = last_slash - path;
	} else {
		basename_offset = 0;
		dirlen = 0;
	}

	prepare_attr_stack(path, dirlen, &check->stack);
	all_attrs_init(&g_attr_hashmap, check);
	determine_macros(check->all_attrs, check->stack);

	if (check->nr) {
		rem = 0;
		for (i = 0; i < check->nr; i++) {
			int n = check->items[i].attr->attr_nr;
			struct all_attrs_item *item = &check->all_attrs[n];
			if (item->macro) {
				item->value = ATTR__UNSET;
				rem++;
			}
		}
		if (rem == check->nr)
			return;
	}

	rem = check->all_attrs_nr;
	fill(path, pathlen, basename_offset, check->stack, check->all_attrs, rem);
}

int git_check_attr(const char *path, struct attr_check *check)
{
	int i;

	collect_some_attrs(path, check);

	for (i = 0; i < check->nr; i++) {
		size_t n = check->items[i].attr->attr_nr;
		const char *value = check->all_attrs[n].value;
		if (value == ATTR__UNKNOWN)
			value = ATTR__UNSET;
		check->items[i].value = value;
	}

	return 0;
}

void git_all_attrs(const char *path, struct attr_check *check)
{
	int i;

	attr_check_reset(check);
	collect_some_attrs(path, check);

	for (i = 0; i < check->all_attrs_nr; i++) {
		const char *name = check->all_attrs[i].attr->name;
		const char *value = check->all_attrs[i].value;
		struct attr_check_item *item;
		if (value == ATTR__UNSET || value == ATTR__UNKNOWN)
			continue;
		item = attr_check_append(check, git_attr(name));
		item->value = value;
	}
}

void attr_start(void)
{
#ifndef NO_PTHREADS
	pthread_mutex_init(&g_attr_hashmap.mutex, NULL);
	pthread_mutex_init(&check_vector.mutex, NULL);
#endif
}
