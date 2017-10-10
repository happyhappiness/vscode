 #include "tree-walk.h"
 #include "commit.h"
 #include "tag.h"
 #include "fsck.h"
 #include "refs.h"
 #include "utf8.h"
+#include "sha1-array.h"
 
-static int fsck_walk_tree(struct tree *tree, fsck_walk_func walk, void *data)
+#define FSCK_FATAL -1
+#define FSCK_INFO -2
+
+#define FOREACH_MSG_ID(FUNC) \
+	/* fatal errors */ \
+	FUNC(NUL_IN_HEADER, FATAL) \
+	FUNC(UNTERMINATED_HEADER, FATAL) \
+	/* errors */ \
+	FUNC(BAD_DATE, ERROR) \
+	FUNC(BAD_DATE_OVERFLOW, ERROR) \
+	FUNC(BAD_EMAIL, ERROR) \
+	FUNC(BAD_NAME, ERROR) \
+	FUNC(BAD_OBJECT_SHA1, ERROR) \
+	FUNC(BAD_PARENT_SHA1, ERROR) \
+	FUNC(BAD_TAG_OBJECT, ERROR) \
+	FUNC(BAD_TIMEZONE, ERROR) \
+	FUNC(BAD_TREE, ERROR) \
+	FUNC(BAD_TREE_SHA1, ERROR) \
+	FUNC(BAD_TYPE, ERROR) \
+	FUNC(DUPLICATE_ENTRIES, ERROR) \
+	FUNC(MISSING_AUTHOR, ERROR) \
+	FUNC(MISSING_COMMITTER, ERROR) \
+	FUNC(MISSING_EMAIL, ERROR) \
+	FUNC(MISSING_GRAFT, ERROR) \
+	FUNC(MISSING_NAME_BEFORE_EMAIL, ERROR) \
+	FUNC(MISSING_OBJECT, ERROR) \
+	FUNC(MISSING_PARENT, ERROR) \
+	FUNC(MISSING_SPACE_BEFORE_DATE, ERROR) \
+	FUNC(MISSING_SPACE_BEFORE_EMAIL, ERROR) \
+	FUNC(MISSING_TAG, ERROR) \
+	FUNC(MISSING_TAG_ENTRY, ERROR) \
+	FUNC(MISSING_TAG_OBJECT, ERROR) \
+	FUNC(MISSING_TREE, ERROR) \
+	FUNC(MISSING_TYPE, ERROR) \
+	FUNC(MISSING_TYPE_ENTRY, ERROR) \
+	FUNC(MULTIPLE_AUTHORS, ERROR) \
+	FUNC(TAG_OBJECT_NOT_TAG, ERROR) \
+	FUNC(TREE_NOT_SORTED, ERROR) \
+	FUNC(UNKNOWN_TYPE, ERROR) \
+	FUNC(ZERO_PADDED_DATE, ERROR) \
+	/* warnings */ \
+	FUNC(BAD_FILEMODE, WARN) \
+	FUNC(EMPTY_NAME, WARN) \
+	FUNC(FULL_PATHNAME, WARN) \
+	FUNC(HAS_DOT, WARN) \
+	FUNC(HAS_DOTDOT, WARN) \
+	FUNC(HAS_DOTGIT, WARN) \
+	FUNC(NULL_SHA1, WARN) \
+	FUNC(ZERO_PADDED_FILEMODE, WARN) \
+	/* infos (reported as warnings, but ignored by default) */ \
+	FUNC(BAD_TAG_NAME, INFO) \
+	FUNC(MISSING_TAGGER_ENTRY, INFO)
+
+#define MSG_ID(id, msg_type) FSCK_MSG_##id,
+enum fsck_msg_id {
+	FOREACH_MSG_ID(MSG_ID)
+	FSCK_MSG_MAX
+};
+#undef MSG_ID
+
+#define STR(x) #x
+#define MSG_ID(id, msg_type) { STR(id), NULL, FSCK_##msg_type },
+static struct {
+	const char *id_string;
+	const char *downcased;
+	int msg_type;
+} msg_id_info[FSCK_MSG_MAX + 1] = {
+	FOREACH_MSG_ID(MSG_ID)
+	{ NULL, NULL, -1 }
+};
+#undef MSG_ID
+
+static int parse_msg_id(const char *text)
+{
+	int i;
+
+	if (!msg_id_info[0].downcased) {
+		/* convert id_string to lower case, without underscores. */
+		for (i = 0; i < FSCK_MSG_MAX; i++) {
+			const char *p = msg_id_info[i].id_string;
+			int len = strlen(p);
+			char *q = xmalloc(len);
+
+			msg_id_info[i].downcased = q;
+			while (*p)
+				if (*p == '_')
+					p++;
+				else
+					*(q)++ = tolower(*(p)++);
+			*q = '\0';
+		}
+	}
+
+	for (i = 0; i < FSCK_MSG_MAX; i++)
+		if (!strcmp(text, msg_id_info[i].downcased))
+			return i;
+
+	return -1;
+}
+
+static int fsck_msg_type(enum fsck_msg_id msg_id,
+	struct fsck_options *options)
+{
+	int msg_type;
+
+	assert(msg_id >= 0 && msg_id < FSCK_MSG_MAX);
+
+	if (options->msg_type)
+		msg_type = options->msg_type[msg_id];
+	else {
+		msg_type = msg_id_info[msg_id].msg_type;
+		if (options->strict && msg_type == FSCK_WARN)
+			msg_type = FSCK_ERROR;
+	}
+
+	return msg_type;
+}
+
+static void init_skiplist(struct fsck_options *options, const char *path)
+{
+	static struct sha1_array skiplist = SHA1_ARRAY_INIT;
+	int sorted, fd;
+	char buffer[41];
+	unsigned char sha1[20];
+
+	if (options->skiplist)
+		sorted = options->skiplist->sorted;
+	else {
+		sorted = 1;
+		options->skiplist = &skiplist;
+	}
+
+	fd = open(path, O_RDONLY);
+	if (fd < 0)
+		die("Could not open skip list: %s", path);
+	for (;;) {
+		int result = read_in_full(fd, buffer, sizeof(buffer));
+		if (result < 0)
+			die_errno("Could not read '%s'", path);
+		if (!result)
+			break;
+		if (get_sha1_hex(buffer, sha1) || buffer[40] != '\n')
+			die("Invalid SHA-1: %s", buffer);
+		sha1_array_append(&skiplist, sha1);
+		if (sorted && skiplist.nr > 1 &&
+				hashcmp(skiplist.sha1[skiplist.nr - 2],
+					sha1) > 0)
+			sorted = 0;
+	}
+	close(fd);
+
+	if (sorted)
+		skiplist.sorted = 1;
+}
+
+static int parse_msg_type(const char *str)
+{
+	if (!strcmp(str, "error"))
+		return FSCK_ERROR;
+	else if (!strcmp(str, "warn"))
+		return FSCK_WARN;
+	else if (!strcmp(str, "ignore"))
+		return FSCK_IGNORE;
+	else
+		die("Unknown fsck message type: '%s'", str);
+}
+
+int is_valid_msg_type(const char *msg_id, const char *msg_type)
+{
+	if (parse_msg_id(msg_id) < 0)
+		return 0;
+	parse_msg_type(msg_type);
+	return 1;
+}
+
+void fsck_set_msg_type(struct fsck_options *options,
+		const char *msg_id, const char *msg_type)
+{
+	int id = parse_msg_id(msg_id), type;
+
+	if (id < 0)
+		die("Unhandled message id: %s", msg_id);
+	type = parse_msg_type(msg_type);
+
+	if (type != FSCK_ERROR && msg_id_info[id].msg_type == FSCK_FATAL)
+		die("Cannot demote %s to %s", msg_id, msg_type);
+
+	if (!options->msg_type) {
+		int i;
+		int *msg_type = xmalloc(sizeof(int) * FSCK_MSG_MAX);
+		for (i = 0; i < FSCK_MSG_MAX; i++)
+			msg_type[i] = fsck_msg_type(i, options);
+		options->msg_type = msg_type;
+	}
+
+	options->msg_type[id] = type;
+}
+
+void fsck_set_msg_types(struct fsck_options *options, const char *values)
+{
+	char *buf = xstrdup(values), *to_free = buf;
+	int done = 0;
+
+	while (!done) {
+		int len = strcspn(buf, " ,|"), equal;
+
+		done = !buf[len];
+		if (!len) {
+			buf++;
+			continue;
+		}
+		buf[len] = '\0';
+
+		for (equal = 0;
+		     equal < len && buf[equal] != '=' && buf[equal] != ':';
+		     equal++)
+			buf[equal] = tolower(buf[equal]);
+		buf[equal] = '\0';
+
+		if (!strcmp(buf, "skiplist")) {
+			if (equal == len)
+				die("skiplist requires a path");
+			init_skiplist(options, buf + equal + 1);
+			buf += len + 1;
+			continue;
+		}
+
+		if (equal == len)
+			die("Missing '=': '%s'", buf);
+
+		fsck_set_msg_type(options, buf, buf + equal + 1);
+		buf += len + 1;
+	}
+	free(to_free);
+}
+
+static void append_msg_id(struct strbuf *sb, const char *msg_id)
+{
+	for (;;) {
+		char c = *(msg_id)++;
+
+		if (!c)
+			break;
+		if (c != '_')
+			strbuf_addch(sb, tolower(c));
+		else {
+			assert(*msg_id);
+			strbuf_addch(sb, *(msg_id)++);
+		}
+	}
+
+	strbuf_addstr(sb, ": ");
+}
+
+__attribute__((format (printf, 4, 5)))
+static int report(struct fsck_options *options, struct object *object,
+	enum fsck_msg_id id, const char *fmt, ...)
+{
+	va_list ap;
+	struct strbuf sb = STRBUF_INIT;
+	int msg_type = fsck_msg_type(id, options), result;
+
+	if (msg_type == FSCK_IGNORE)
+		return 0;
+
+	if (options->skiplist && object &&
+			sha1_array_lookup(options->skiplist, object->sha1) >= 0)
+		return 0;
+
+	if (msg_type == FSCK_FATAL)
+		msg_type = FSCK_ERROR;
+	else if (msg_type == FSCK_INFO)
+		msg_type = FSCK_WARN;
+
+	append_msg_id(&sb, msg_id_info[id].id_string);
+
+	va_start(ap, fmt);
+	strbuf_vaddf(&sb, fmt, ap);
+	result = options->error_func(object, msg_type, sb.buf);
+	strbuf_release(&sb);
+	va_end(ap);
+
+	return result;
+}
+
+static int fsck_walk_tree(struct tree *tree, void *data, struct fsck_options *options)
 {
 	struct tree_desc desc;
 	struct name_entry entry;
 	int res = 0;
 
 	if (parse_tree(tree))
