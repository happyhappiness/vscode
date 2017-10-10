 * can be NULL, signifying the empty list.
 */
const char *find_descendant_ref(const char *dirname,
				const struct string_list *extras,
				const struct string_list *skip);

int rename_ref_available(const char *oldname, const char *newname);

/* We allow "recursive" symbolic refs. Only within reason, though */
#define SYMREF_MAXDEPTH 5

/* Include broken references in a do_for_each_ref*() iteration: */
#define DO_FOR_EACH_INCLUDE_BROKEN 0x01
