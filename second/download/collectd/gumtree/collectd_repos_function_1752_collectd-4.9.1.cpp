static inline int
print_match(const STRUCT_ENTRY_MATCH *m)
{
	printf("Match name: `%s'\n", m->u.user.name);
	return 0;
}