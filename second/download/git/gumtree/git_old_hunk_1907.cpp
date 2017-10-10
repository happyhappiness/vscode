#include "cache.h"
#include "refs.h"
#include "object.h"
#include "commit.h"
#include "tag.h"

/* refs */
static FILE *info_ref_fp;

static int add_info_ref(const char *path, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *o = parse_object(sha1);
	if (!o)
		return -1;

	fprintf(info_ref_fp, "%s	%s\n", sha1_to_hex(sha1), path);
	if (o->type == OBJ_TAG) {
		o = deref_tag(o, path, 0);
		if (o)
			fprintf(info_ref_fp, "%s	%s^{}\n",
				sha1_to_hex(o->sha1), path);
	}
	return 0;
}

static int update_info_refs(int force)
{
	char *path0 = git_pathdup("info/refs");
	int len = strlen(path0);
	char *path1 = xmalloc(len + 2);

	strcpy(path1, path0);
	strcpy(path1 + len, "+");

	safe_create_leading_directories(path0);
	info_ref_fp = fopen(path1, "w");
	if (!info_ref_fp)
		return error("unable to update %s", path1);
	for_each_ref(add_info_ref, NULL);
	fclose(info_ref_fp);
	adjust_shared_perm(path1);
	rename(path1, path0);
	free(path0);
	free(path1);
	return 0;
}

/* packs */
static struct pack_info {
	struct packed_git *p;
	int old_num;
