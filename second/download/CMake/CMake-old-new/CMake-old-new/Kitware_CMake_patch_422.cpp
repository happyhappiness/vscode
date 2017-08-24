@@ -414,7 +414,7 @@ xar_options(struct archive_write *a, const char *key, const char *value)
 		else {
 			archive_set_error(&(a->archive),
 			    ARCHIVE_ERRNO_MISC,
-			    "Unkonwn checksum name: `%s'",
+			    "Unknown checksum name: `%s'",
 			    value);
 			return (ARCHIVE_FAILED);
 		}
@@ -448,7 +448,7 @@ xar_options(struct archive_write *a, const char *key, const char *value)
 		else {
 			archive_set_error(&(a->archive),
 			    ARCHIVE_ERRNO_MISC,
-			    "Unkonwn compression name: `%s'",
+			    "Unknown compression name: `%s'",
 			    value);
 			return (ARCHIVE_FAILED);
 		}
@@ -485,7 +485,7 @@ xar_options(struct archive_write *a, const char *key, const char *value)
 		else {
 			archive_set_error(&(a->archive),
 			    ARCHIVE_ERRNO_MISC,
-			    "Unkonwn checksum name: `%s'",
+			    "Unknown checksum name: `%s'",
 			    value);
 			return (ARCHIVE_FAILED);
 		}