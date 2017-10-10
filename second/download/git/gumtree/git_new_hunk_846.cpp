		free(a);
	}
	free(e->attrs);
	free(e);
}

static void drop_attr_stack(struct attr_stack **stack)
{
	while (*stack) {
		struct attr_stack *elem = *stack;
		*stack = elem->prev;
		attr_stack_free(elem);
	}
}

/* List of all attr_check structs; access should be surrounded by mutex */
static struct check_vector {
	size_t nr;
	size_t alloc;
	struct attr_check **checks;
#ifndef NO_PTHREADS
	pthread_mutex_t mutex;
#endif
} check_vector;

static inline void vector_lock(void)
{
#ifndef NO_PTHREADS
	pthread_mutex_lock(&check_vector.mutex);
#endif
}

static inline void vector_unlock(void)
{
#ifndef NO_PTHREADS
	pthread_mutex_unlock(&check_vector.mutex);
#endif
}

static void check_vector_add(struct attr_check *c)
{
	vector_lock();

	ALLOC_GROW(check_vector.checks,
		   check_vector.nr + 1,
		   check_vector.alloc);
	check_vector.checks[check_vector.nr++] = c;

	vector_unlock();
}

static void check_vector_remove(struct attr_check *check)
{
	int i;

	vector_lock();

	/* Find entry */
	for (i = 0; i < check_vector.nr; i++)
		if (check_vector.checks[i] == check)
			break;

	if (i >= check_vector.nr)
		die("BUG: no entry found");

	/* shift entries over */
	for (; i < check_vector.nr - 1; i++)
		check_vector.checks[i] = check_vector.checks[i + 1];

	check_vector.nr--;

	vector_unlock();
}

/* Iterate through all attr_check instances and drop their stacks */
static void drop_all_attr_stacks(void)
{
	int i;

	vector_lock();

	for (i = 0; i < check_vector.nr; i++) {
		drop_attr_stack(&check_vector.checks[i]->stack);
	}

	vector_unlock();
}

struct attr_check *attr_check_alloc(void)
{
	struct attr_check *c = xcalloc(1, sizeof(struct attr_check));

	/* save pointer to the check struct */
	check_vector_add(c);

	return c;
}

struct attr_check *attr_check_initl(const char *one, ...)
{
	struct attr_check *check;
	int cnt;
	va_list params;
	const char *param;

	va_start(params, one);
	for (cnt = 1; (param = va_arg(params, const char *)) != NULL; cnt++)
		;
	va_end(params);

	check = attr_check_alloc();
	check->nr = cnt;
	check->alloc = cnt;
	check->items = xcalloc(cnt, sizeof(struct attr_check_item));

	check->items[0].attr = git_attr(one);
	va_start(params, one);
	for (cnt = 1; cnt < check->nr; cnt++) {
		const struct git_attr *attr;
		param = va_arg(params, const char *);
		if (!param)
			die("BUG: counted %d != ended at %d",
			    check->nr, cnt);
		attr = git_attr(param);
		if (!attr)
			die("BUG: %s: not a valid attribute name", param);
		check->items[cnt].attr = attr;
	}
	va_end(params);
	return check;
}

struct attr_check *attr_check_dup(const struct attr_check *check)
{
	struct attr_check *ret;

	if (!check)
		return NULL;

	ret = attr_check_alloc();

	ret->nr = check->nr;
	ret->alloc = check->alloc;
	ALLOC_ARRAY(ret->items, ret->nr);
	COPY_ARRAY(ret->items, check->items, ret->nr);

	return ret;
}

struct attr_check_item *attr_check_append(struct attr_check *check,
					  const struct git_attr *attr)
{
	struct attr_check_item *item;

	ALLOC_GROW(check->items, check->nr + 1, check->alloc);
	item = &check->items[check->nr++];
	item->attr = attr;
	return item;
}

void attr_check_reset(struct attr_check *check)
{
	check->nr = 0;
}

void attr_check_clear(struct attr_check *check)
{
	free(check->items);
	check->items = NULL;
	check->alloc = 0;
	check->nr = 0;

	free(check->all_attrs);
	check->all_attrs = NULL;
	check->all_attrs_nr = 0;

	drop_attr_stack(&check->stack);
}

void attr_check_free(struct attr_check *check)
{
	if (check) {
		/* Remove check from the check vector */
		check_vector_remove(check);

		attr_check_clear(check);
		free(check);
	}
}

static const char *builtin_attr[] = {
	"[attr]binary -diff -merge -text",
	NULL,
};

static void handle_attr_line(struct attr_stack *res,
