	struct commit commit;
	struct tag tag;
};

DEFINE_ALLOCATOR(blob, struct blob)
DEFINE_ALLOCATOR(tree, struct tree)
DEFINE_ALLOCATOR(commit, struct commit)
DEFINE_ALLOCATOR(tag, struct tag)
DEFINE_ALLOCATOR(object, union any_object)

static void report(const char *name, unsigned int count, size_t size)
{
	fprintf(stderr, "%10s: %8u (%"PRIuMAX" kB)\n",
			name, count, (uintmax_t) size);
}

#define REPORT(name)	\
    report(#name, name##_allocs, name##_allocs * sizeof(struct name) >> 10)

void alloc_report(void)
{
	REPORT(blob);
	REPORT(tree);
	REPORT(commit);
	REPORT(tag);
}
