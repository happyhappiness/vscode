 /**
  * collectd - src/utils_cmd_flush.c
- * Copyright (C) 2008  Sebastian Harl
- * Copyright (C) 2008  Florian Forster
+ * Copyright (C) 2008       Sebastian Harl
+ * Copyright (C) 2008       Florian Forster
  *
- * This program is free software; you can redistribute it and/or modify it
- * under the terms of the GNU General Public License as published by the
- * Free Software Foundation; only version 2 of the License is applicable.
+ * Permission is hereby granted, free of charge, to any person obtaining a
+ * copy of this software and associated documentation files (the "Software"),
+ * to deal in the Software without restriction, including without limitation
+ * the rights to use, copy, modify, merge, publish, distribute, sublicense,
+ * and/or sell copies of the Software, and to permit persons to whom the
+ * Software is furnished to do so, subject to the following conditions:
  *
- * This program is distributed in the hope that it will be useful, but
- * WITHOUT ANY WARRANTY; without even the implied warranty of
- * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
- * General Public License for more details.
+ * The above copyright notice and this permission notice shall be included in
+ * all copies or substantial portions of the Software.
  *
- * You should have received a copy of the GNU General Public License along
- * with this program; if not, write to the Free Software Foundation, Inc.,
- * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
+ * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
+ * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
+ * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
+ * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
+ * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
+ * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
+ * DEALINGS IN THE SOFTWARE.
  *
  * Authors:
  *   Sebastian "tokkee" Harl <sh at tokkee.org>
- *   Florian "octo" Forster <octo at verplant.org>
+ *   Florian "octo" Forster <octo at collectd.org>
  **/
 
 #include "collectd.h"
 #include "common.h"
 #include "plugin.h"
 #include "utils_parse_option.h"
-#include "utils_cmd_flush.h"
 
-int handle_flush (FILE *fh, char *buffer)
-{
-	int success = 0;
-	int error   = 0;
-
-	double timeout = 0.0;
-	char **plugins = NULL;
-	size_t plugins_num = 0;
-	char **identifiers = NULL;
-	size_t identifiers_num = 0;
-
-	size_t i;
-
-#define PRINT_TO_SOCK(fh, ...) \
+#define print_to_socket(fh, ...) \
 	do { \
 		if (fprintf (fh, __VA_ARGS__) < 0) { \
 			char errbuf[1024]; \
 			WARNING ("handle_flush: failed to write to socket #%i: %s", \
 					fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
-			strarray_free (plugins, plugins_num); \
-			strarray_free (identifiers, identifiers_num); \
 			return -1; \
 		} \
 		fflush(fh); \
 	} while (0)
 
+static int add_to_array (char ***array, int *array_num, char *value)
+{
+	char **temp;
+
+	temp = (char **) realloc (*array, sizeof (char *) * (*array_num + 1));
+	if (temp == NULL)
+		return (-1);
+
+	*array = temp;
+	(*array)[*array_num] = value;
+	(*array_num)++;
+
+	return (0);
+} /* int add_to_array */
+
+int handle_flush (FILE *fh, char *buffer)
+{
+	int success = 0;
+	int error   = 0;
+
+	double timeout = 0.0;
+	char **plugins = NULL;
+	int plugins_num = 0;
+	char **identifiers = NULL;
+	int identifiers_num = 0;
+
+	int i;
+
 	if ((fh == NULL) || (buffer == NULL))
 		return (-1);
 
 	DEBUG ("utils_cmd_flush: handle_flush (fh = %p, buffer = %s);",
 			(void *) fh, buffer);
 
 	if (strncasecmp ("FLUSH", buffer, strlen ("FLUSH")) != 0)
 	{
-		PRINT_TO_SOCK (fh, "-1 Cannot parse command.\n");
+		print_to_socket (fh, "-1 Cannot parse command.\n");
 		return (-1);
 	}
 	buffer += strlen ("FLUSH");
 
 	while (*buffer != 0)
 	{
