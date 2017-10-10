 */
#include "cache.h"
#include "builtin.h"
#include "parse-options.h"
#include "userdiff.h"
#include "streaming.h"

static int cat_one_file(int opt, const char *exp_type, const char *obj_name)
{
	unsigned char sha1[20];
	enum object_type type;
	char *buf;
	unsigned long size;
	struct object_context obj_context;

	if (get_sha1_with_context(obj_name, 0, sha1, &obj_context))
		die("Not a valid object name %s", obj_name);

	buf = NULL;
	switch (opt) {
	case 't':
		type = sha1_object_info(sha1, NULL);
		if (type > 0) {
			printf("%s\n", typename(type));
			return 0;
		}
		break;

	case 's':
		type = sha1_object_info(sha1, &size);
		if (type > 0) {
			printf("%lu\n", size);
			return 0;
		}
		break;

	case 'e':
		return !has_sha1_file(sha1);

	case 'c':
		if (!obj_context.path[0])
