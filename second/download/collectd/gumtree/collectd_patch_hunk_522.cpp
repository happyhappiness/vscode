 /**
- * collectd - src/utils_cms_putval.c
+ * collectd - src/utils_cmd_putval.c
  * Copyright (C) 2007-2009  Florian octo Forster
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
- * Author:
- *   Florian octo Forster <octo at verplant.org>
+ * Authors:
+ *   Florian octo Forster <octo at collectd.org>
  **/
 
 #include "collectd.h"
 #include "common.h"
 #include "plugin.h"
 
 #include "utils_parse_option.h"
-#include "utils_cmd_putval.h"
 
 #define print_to_socket(fh, ...) \
     do { \
         if (fprintf (fh, __VA_ARGS__) < 0) { \
             char errbuf[1024]; \
             WARNING ("handle_putval: failed to write to socket #%i: %s", \
                     fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
-            sfree (vl.values); \
             return -1; \
         } \
         fflush(fh); \
     } while (0)
 
+static int dispatch_values (const data_set_t *ds, value_list_t *vl,
+	       	FILE *fh, char *buffer)
+{
+	int status;
+
+	status = parse_values (buffer, vl, ds);
+	if (status != 0)
+	{
+		print_to_socket (fh, "-1 Parsing the values string failed.\n");
+		return (-1);
+	}
+
+	plugin_dispatch_values (vl);
+	return (0);
+} /* int dispatch_values */
+
 static int set_option (value_list_t *vl, const char *key, const char *value)
 {
 	if ((vl == NULL) || (key == NULL) || (value == NULL))
 		return (-1);
 
 	if (strcasecmp ("interval", key) == 0)
