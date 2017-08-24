@@ -1939,9 +1939,6 @@ unknowntag_start(struct archive_read *a, struct xar *xar, const char *name)
 {
 	struct unknown_tag *tag;
 
-#if DEBUG
-	fprintf(stderr, "unknowntag_start:%s\n", name);
-#endif
 	tag = malloc(sizeof(*tag));
 	if (tag == NULL) {
 		archive_set_error(&a->archive, ENOMEM, "Out of memory");
@@ -1951,6 +1948,9 @@ unknowntag_start(struct archive_read *a, struct xar *xar, const char *name)
 	archive_string_init(&(tag->name));
 	archive_strcpy(&(tag->name), name);
 	if (xar->unknowntags == NULL) {
+#if DEBUG
+		fprintf(stderr, "UNKNOWNTAG_START:%s\n", name);
+#endif
 		xar->xmlsts_unknown = xar->xmlsts;
 		xar->xmlsts = UNKNOWN;
 	}
@@ -1963,18 +1963,19 @@ unknowntag_end(struct xar *xar, const char *name)
 {
 	struct unknown_tag *tag;
 
-#if DEBUG
-	fprintf(stderr, "unknowntag_end:%s\n", name);
-#endif
 	tag = xar->unknowntags;
 	if (tag == NULL || name == NULL)
 		return;
 	if (strcmp(tag->name.s, name) == 0) {
 		xar->unknowntags = tag->next;
 		archive_string_free(&(tag->name));
 		free(tag);
-		if (xar->unknowntags == NULL)
+		if (xar->unknowntags == NULL) {
+#if DEBUG
+			fprintf(stderr, "UNKNOWNTAG_END:%s\n", name);
+#endif
 			xar->xmlsts = xar->xmlsts_unknown;
+		}
 	}
 }
 
@@ -2168,7 +2169,7 @@ xml_start(struct archive_read *a, const char *name, struct xmlattr_list *list)
 	case FILE_ACL:
 		if (strcmp(name, "appleextended") == 0)
 			xar->xmlsts = FILE_ACL_APPLEEXTENDED;
-		if (strcmp(name, "default") == 0)
+		else if (strcmp(name, "default") == 0)
 			xar->xmlsts = FILE_ACL_DEFAULT;
 		else if (strcmp(name, "access") == 0)
 			xar->xmlsts = FILE_ACL_ACCESS;
@@ -2690,9 +2691,9 @@ xml_data(void *userData, const char *s, int len)
 #if DEBUG
 	{
 		char buff[1024];
-		if (len > sizeof(buff)-1)
-			len = sizeof(buff)-1;
-		memcpy(buff, s, len);
+		if (len > (int)(sizeof(buff)-1))
+			len = (int)(sizeof(buff)-1);
+		strncpy(buff, s, len);
 		buff[len] = 0;
 		fprintf(stderr, "\tlen=%d:\"%s\"\n", len, buff);
 	}