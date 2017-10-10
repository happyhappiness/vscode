		dirlen = last_slash - path;
	} else {
		basename_offset = 0;
		dirlen = 0;
	}

	prepare_attr_stack(path, dirlen);
	for (i = 0; i < attr_nr; i++)
		check_all_attr[i].value = ATTR__UNKNOWN;
	if (num && !cannot_trust_maybe_real) {
		rem = 0;
		for (i = 0; i < num; i++) {
			if (!check[i].attr->maybe_real) {
				struct git_attr_check *c;
				c = check_all_attr + check[i].attr->attr_nr;
				c->value = ATTR__UNSET;
				rem++;
			}
		}
		if (rem == num)
			return;
	}

	rem = attr_nr;
	for (stk = attr_stack; 0 < rem && stk; stk = stk->prev)
		rem = fill(path, pathlen, basename_offset, stk, rem);
}

int git_check_attr(const char *path, int num, struct git_attr_check *check)
{
	int i;

	collect_some_attrs(path, num, check);

	for (i = 0; i < num; i++) {
		const char *value = check_all_attr[check[i].attr->attr_nr].value;
		if (value == ATTR__UNKNOWN)
			value = ATTR__UNSET;
		check[i].value = value;
	}

	return 0;
}

int git_all_attrs(const char *path, int *num, struct git_attr_check **check)
{
	int i, count, j;

	collect_some_attrs(path, 0, NULL);

	/* Count the number of attributes that are set. */
	count = 0;
	for (i = 0; i < attr_nr; i++) {
		const char *value = check_all_attr[i].value;
		if (value != ATTR__UNSET && value != ATTR__UNKNOWN)
			++count;
	}
	*num = count;
	ALLOC_ARRAY(*check, count);
	j = 0;
	for (i = 0; i < attr_nr; i++) {
		const char *value = check_all_attr[i].value;
		if (value != ATTR__UNSET && value != ATTR__UNKNOWN) {
			(*check)[j].attr = check_all_attr[i].attr;
			(*check)[j].value = value;
			++j;
		}
	}

	return 0;
}

void git_attr_set_direction(enum git_attr_direction new, struct index_state *istate)
{
	enum git_attr_direction old = direction;

	if (is_bare_repository() && new != GIT_ATTR_INDEX)
		die("BUG: non-INDEX attr direction in a bare repo");

	direction = new;
	if (new != old)
		drop_attr_stack();
	use_index = istate;
}
