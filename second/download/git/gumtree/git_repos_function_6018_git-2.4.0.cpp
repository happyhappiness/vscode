static char *find_local_name(const char *remote_name, const char *refs,
			     int *force_p, int *not_for_merge_p)
{
	const char *ref = refs;
	int len = strlen(remote_name);

	while (ref) {
		const char *next;
		int single_force, not_for_merge;

		while (*ref == '\n')
			ref++;
		if (!*ref)
			break;
		next = strchr(ref, '\n');

		single_force = not_for_merge = 0;
		if (*ref == '+') {
			single_force = 1;
			ref++;
		}
		if (*ref == '.') {
			not_for_merge = 1;
			ref++;
			if (*ref == '+') {
				single_force = 1;
				ref++;
			}
		}
		if (!strncmp(remote_name, ref, len) && ref[len] == ':') {
			const char *local_part = ref + len + 1;
			int retlen;

			if (!next)
				retlen = strlen(local_part);
			else
				retlen = next - local_part;
			*force_p = single_force;
			*not_for_merge_p = not_for_merge;
			return xmemdupz(local_part, retlen);
		}
		ref = next;
	}
	return NULL;
}