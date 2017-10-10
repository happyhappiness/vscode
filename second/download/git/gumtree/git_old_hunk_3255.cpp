#include "url.h"
#include "submodule.h"
#include "string-list.h"
#include "sha1-array.h"
#include "sigchain.h"

/* rsync support */

/*
 * We copy packed-refs and refs/ into a temporary file, then read the
 * loose refs recursively (sorting whenever possible), and then inserting
 * those packed refs that are not yet in the list (not validating, but
 * assuming that the file is sorted).
 *
 * Appears refactoring this from refs.c is too cumbersome.
 */

static int str_cmp(const void *a, const void *b)
{
	const char *s1 = a;
	const char *s2 = b;

	return strcmp(s1, s2);
}

/* path->buf + name_offset is expected to point to "refs/" */

static int read_loose_refs(struct strbuf *path, int name_offset,
		struct ref **tail)
{
	DIR *dir = opendir(path->buf);
	struct dirent *de;
	struct {
		char **entries;
		int nr, alloc;
	} list;
	int i, pathlen;

	if (!dir)
		return -1;

	memset (&list, 0, sizeof(list));

	while ((de = readdir(dir))) {
		if (is_dot_or_dotdot(de->d_name))
			continue;
		ALLOC_GROW(list.entries, list.nr + 1, list.alloc);
		list.entries[list.nr++] = xstrdup(de->d_name);
	}
	closedir(dir);

	/* sort the list */

	qsort(list.entries, list.nr, sizeof(char *), str_cmp);

	pathlen = path->len;
	strbuf_addch(path, '/');

	for (i = 0; i < list.nr; i++, strbuf_setlen(path, pathlen + 1)) {
		strbuf_addstr(path, list.entries[i]);
		if (read_loose_refs(path, name_offset, tail)) {
			int fd = open(path->buf, O_RDONLY);
			char buffer[40];
			struct ref *next;

			if (fd < 0)
				continue;
			next = alloc_ref(path->buf + name_offset);
			if (read_in_full(fd, buffer, 40) != 40 ||
					get_oid_hex(buffer, &next->old_oid)) {
				close(fd);
				free(next);
				continue;
			}
			close(fd);
			(*tail)->next = next;
			*tail = next;
		}
	}
	strbuf_setlen(path, pathlen);

	for (i = 0; i < list.nr; i++)
		free(list.entries[i]);
	free(list.entries);

	return 0;
}

/* insert the packed refs for which no loose refs were found */

static void insert_packed_refs(const char *packed_refs, struct ref **list)
{
	FILE *f = fopen(packed_refs, "r");
	static char buffer[PATH_MAX];

	if (!f)
		return;

	for (;;) {
		int cmp = 0; /* assigned before used */
		int len;

		if (!fgets(buffer, sizeof(buffer), f)) {
			fclose(f);
			return;
		}

		if (!isxdigit(buffer[0]))
			continue;
		len = strlen(buffer);
		if (len && buffer[len - 1] == '\n')
			buffer[--len] = '\0';
		if (len < 41)
			continue;
		while ((*list)->next &&
				(cmp = strcmp(buffer + 41,
				      (*list)->next->name)) > 0)
			list = &(*list)->next;
		if (!(*list)->next || cmp < 0) {
			struct ref *next = alloc_ref(buffer + 41);
			buffer[40] = '\0';
			if (get_oid_hex(buffer, &next->old_oid)) {
				warning ("invalid SHA-1: %s", buffer);
				free(next);
				continue;
			}
			next->next = (*list)->next;
			(*list)->next = next;
			list = &(*list)->next;
		}
	}
}

static void set_upstreams(struct transport *transport, struct ref *refs,
	int pretend)
{
	struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		const char *localname;
