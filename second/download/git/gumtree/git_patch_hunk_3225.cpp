 #include "utf8.h"
 #include "git-compat-util.h"
 #include "version.h"
 
 typedef enum { FIELD_STR, FIELD_ULONG, FIELD_TIME } cmp_type;
 
+struct align {
+	align_type position;
+	unsigned int width;
+};
+
+/*
+ * An atom is a valid field atom listed below, possibly prefixed with
+ * a "*" to denote deref_tag().
+ *
+ * We parse given format string and sort specifiers, and make a list
+ * of properties that we need to extract out of objects.  ref_array_item
+ * structure will hold an array of values extracted that can be
+ * indexed with the "atom number", which is an index into this
+ * array.
+ */
+static struct used_atom {
+	const char *name;
+	cmp_type type;
+	union {
+		char color[COLOR_MAXLEN];
+		struct align align;
+		enum { RR_NORMAL, RR_SHORTEN, RR_TRACK, RR_TRACKSHORT }
+			remote_ref;
+		struct {
+			enum { C_BARE, C_BODY, C_BODY_DEP, C_LINES, C_SIG, C_SUB } option;
+			unsigned int nlines;
+		} contents;
+		enum { O_FULL, O_SHORT } objectname;
+	} u;
+} *used_atom;
+static int used_atom_cnt, need_tagged, need_symref;
+static int need_color_reset_at_eol;
+
+static void color_atom_parser(struct used_atom *atom, const char *color_value)
+{
+	if (!color_value)
+		die(_("expected format: %%(color:<color>)"));
+	if (color_parse(color_value, atom->u.color) < 0)
+		die(_("unrecognized color: %%(color:%s)"), color_value);
+}
+
+static void remote_ref_atom_parser(struct used_atom *atom, const char *arg)
+{
+	if (!arg)
+		atom->u.remote_ref = RR_NORMAL;
+	else if (!strcmp(arg, "short"))
+		atom->u.remote_ref = RR_SHORTEN;
+	else if (!strcmp(arg, "track"))
+		atom->u.remote_ref = RR_TRACK;
+	else if (!strcmp(arg, "trackshort"))
+		atom->u.remote_ref = RR_TRACKSHORT;
+	else
+		die(_("unrecognized format: %%(%s)"), atom->name);
+}
+
+static void body_atom_parser(struct used_atom *atom, const char *arg)
+{
+	if (arg)
+		die(_("%%(body) does not take arguments"));
+	atom->u.contents.option = C_BODY_DEP;
+}
+
+static void subject_atom_parser(struct used_atom *atom, const char *arg)
+{
+	if (arg)
+		die(_("%%(subject) does not take arguments"));
+	atom->u.contents.option = C_SUB;
+}
+
+static void contents_atom_parser(struct used_atom *atom, const char *arg)
+{
+	if (!arg)
+		atom->u.contents.option = C_BARE;
+	else if (!strcmp(arg, "body"))
+		atom->u.contents.option = C_BODY;
+	else if (!strcmp(arg, "signature"))
+		atom->u.contents.option = C_SIG;
+	else if (!strcmp(arg, "subject"))
+		atom->u.contents.option = C_SUB;
+	else if (skip_prefix(arg, "lines=", &arg)) {
+		atom->u.contents.option = C_LINES;
+		if (strtoul_ui(arg, 10, &atom->u.contents.nlines))
+			die(_("positive value expected contents:lines=%s"), arg);
+	} else
+		die(_("unrecognized %%(contents) argument: %s"), arg);
+}
+
+static void objectname_atom_parser(struct used_atom *atom, const char *arg)
+{
+	if (!arg)
+		atom->u.objectname = O_FULL;
+	else if (!strcmp(arg, "short"))
+		atom->u.objectname = O_SHORT;
+	else
+		die(_("unrecognized %%(objectname) argument: %s"), arg);
+}
+
+static align_type parse_align_position(const char *s)
+{
+	if (!strcmp(s, "right"))
+		return ALIGN_RIGHT;
+	else if (!strcmp(s, "middle"))
+		return ALIGN_MIDDLE;
+	else if (!strcmp(s, "left"))
+		return ALIGN_LEFT;
+	return -1;
+}
+
+static void align_atom_parser(struct used_atom *atom, const char *arg)
+{
+	struct align *align = &atom->u.align;
+	struct string_list params = STRING_LIST_INIT_DUP;
+	int i;
+	unsigned int width = ~0U;
+
+	if (!arg)
+		die(_("expected format: %%(align:<width>,<position>)"));
+
+	align->position = ALIGN_LEFT;
+
+	string_list_split(&params, arg, ',', -1);
+	for (i = 0; i < params.nr; i++) {
+		const char *s = params.items[i].string;
+		int position;
+
+		if (skip_prefix(s, "position=", &s)) {
+			position = parse_align_position(s);
+			if (position < 0)
+				die(_("unrecognized position:%s"), s);
+			align->position = position;
+		} else if (skip_prefix(s, "width=", &s)) {
+			if (strtoul_ui(s, 10, &width))
+				die(_("unrecognized width:%s"), s);
+		} else if (!strtoul_ui(s, 10, &width))
+			;
+		else if ((position = parse_align_position(s)) >= 0)
+			align->position = position;
+		else
+			die(_("unrecognized %%(align) argument: %s"), s);
+	}
+
+	if (width == ~0U)
+		die(_("positive width expected with the %%(align) atom"));
+	align->width = width;
+	string_list_clear(&params, 0);
+}
+
 static struct {
 	const char *name;
 	cmp_type cmp_type;
+	void (*parser)(struct used_atom *atom, const char *arg);
 } valid_atom[] = {
 	{ "refname" },
 	{ "objecttype" },
 	{ "objectsize", FIELD_ULONG },
-	{ "objectname" },
+	{ "objectname", FIELD_STR, objectname_atom_parser },
 	{ "tree" },
 	{ "parent" },
 	{ "numparent", FIELD_ULONG },
 	{ "object" },
 	{ "type" },
 	{ "tag" },
