 /*
  * Routines used by the file-transfer code.
  *
  * Copyright (C) 1996 Andrew Tridgell
  * Copyright (C) 1996 Paul Mackerras
- * Copyright (C) 2003, 2004, 2005 Wayne Davison
+ * Copyright (C) 2003-2008 Wayne Davison
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
- * the Free Software Foundation; either version 2 of the License, or
+ * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License along
- * with this program; if not, write to the Free Software Foundation, Inc.,
- * 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
+ * with this program; if not, visit the http://fsf.org website.
  */
 
 #include "rsync.h"
+#include "ifuncs.h"
 #include "zlib/zlib.h"
 
 extern int do_compression;
 extern int module_id;
 extern int def_compress_level;
+extern char *skip_compress;
 
 static int compression_level, per_file_default_level;
 
-/* determine the compression level based on a wildcard filename list */
-void set_compression(char *fname)
+struct suffix_tree {
+	struct suffix_tree *sibling;
+	struct suffix_tree *child;
+	char letter, word_end;
+};
+
+static char *match_list;
+static struct suffix_tree *suftree;
+
+static void add_suffix(struct suffix_tree **prior, char ltr, const char *str)
 {
-	static char *match_list;
-	char *s;
+	struct suffix_tree *node, *newnode;
 
-	if (!do_compression)
+	if (ltr == '[') {
+		const char *after = strchr(str, ']');
+		/* Just skip bogus character classes. */
+		if (!after++)
+			return;
+		while ((ltr = *str++) != ']')
+			add_suffix(prior, ltr, after);
 		return;
+	}
 
-	if (!match_list) {
-		char *t, *f = lp_dont_compress(module_id);
-		int len = strlen(f);
-		if (!(match_list = t = new_array(char, len + 2)))
-			out_of_memory("set_compression");
-		while (*f) {
-			if (*f == ' ') {
-				f++;
-				continue;
-			}
-			do {
-				if (isupper(*(unsigned char *)f))
-					*t++ = tolower(*(unsigned char *)f);
-				else
-					*t++ = *f;
-			} while (*++f != ' ' && *f);
-			*t++ = '\0';
-		}
-		/* Optimize a match-string of "*". */
-		if (t - match_list == 2 && match_list[0] == '*') {
-			t = match_list;
-			per_file_default_level = 0;
-		} else
-			per_file_default_level = def_compress_level;
+	for (node = *prior; node; prior = &node->sibling, node = node->sibling) {
+		if (node->letter == ltr) {
+			if (*str)
+				add_suffix(&node->child, *str, str+1);
+			else
+				node->word_end = 1;
+			return;
+		}
+		if (node->letter > ltr)
+			break;
+	}
+	if (!(newnode = new(struct suffix_tree)))
+		out_of_memory("add_suffix");
+	newnode->sibling = node;
+	newnode->child = NULL;
+	newnode->letter = ltr;
+	*prior = newnode;
+	if (*str) {
+		add_suffix(&newnode->child, *str, str+1);
+		newnode->word_end = 0;
+	} else
+		newnode->word_end = 1;
+}
+
+static void add_nocompress_suffixes(const char *str)
+{
+	char *buf, *t;
+	const char *f = str;
+
+	if (!(buf = new_array(char, strlen(f) + 1)))
+		out_of_memory("add_nocompress_suffixes");
+
+	while (*f) {
+		if (*f == '/') {
+			f++;
+			continue;
+		}
+
+		t = buf;
+		do {
+			if (isUpper(f))
+				*t++ = toLower(f);
+			else
+				*t++ = *f;
+		} while (*++f != '/' && *f);
+		*t++ = '\0';
+
+		fprintf(stderr, "adding `%s'\n", buf);
+		add_suffix(&suftree, *buf, buf+1);
+	}
+
+	free(buf);
+}
+
+static void init_set_compression(void)
+{
+	const char *f;
+	char *t, *start;
+
+	if (skip_compress)
+		add_nocompress_suffixes(skip_compress);
+
+	/* A non-daemon transfer skips the default suffix list if the
+	 * user specified --skip-compress. */
+	if (skip_compress && module_id < 0)
+		f = "";
+	else
+		f = lp_dont_compress(module_id);
+
+	if (!(match_list = t = new_array(char, strlen(f) + 2)))
+		out_of_memory("set_compression");
+
+	per_file_default_level = def_compress_level;
+
+	while (*f) {
+		if (*f == ' ') {
+			f++;
+			continue;
+		}
+
+		start = t;
+		do {
+			if (isUpper(f))
+				*t++ = toLower(f);
+			else
+				*t++ = *f;
+		} while (*++f != ' ' && *f);
 		*t++ = '\0';
+
+		if (t - start == 1+1 && *start == '*') {
+			/* Optimize a match-string of "*". */
+			*match_list = '\0';
+			suftree = NULL;
+			per_file_default_level = 0;
+			break;
+		}
+
+		/* Move *.foo items into the stuffix tree. */
+		if (*start == '*' && start[1] == '.' && start[2]
+		 && !strpbrk(start+2, ".?*")) {
+			add_suffix(&suftree, start[2], start+3);
+			t = start;
+		}
 	}
+	*t++ = '\0';
+}
+
+/* determine the compression level based on a wildcard filename list */
+void set_compression(const char *fname)
+{
+	const struct suffix_tree *node;
+	const char *s;
+	char ltr;
+
+	if (!do_compression)
+		return;
+
+	if (!match_list)
+		init_set_compression();
 
 	compression_level = per_file_default_level;
 
-	if (!*match_list)
+	if (!*match_list && !suftree)
 		return;
 
 	if ((s = strrchr(fname, '/')) != NULL)
 		fname = s + 1;
 
 	for (s = match_list; *s; s += strlen(s) + 1) {
 		if (iwildmatch(s, fname)) {
 			compression_level = 0;
-			break;
+			return;
+		}
+	}
+
+	if (!(node = suftree) || !(s = strrchr(fname, '.'))
+	 || s == fname || !(ltr = *++s))
+		return;
+
+	while (1) {
+		while (node->letter != ltr) {
+			if (node->letter > ltr)
+				return;
+			if (!(node = node->sibling))
+				return;
+		}
+		if ((ltr = *++s) == '\0') {
+			if (node->word_end)
+				compression_level = 0;
+			return;
 		}
+		if (!(node = node->child))
+			return;
 	}
 }
 
 /* non-compressing recv token */
 static int32 simple_recv_token(int f, char **data)
 {
