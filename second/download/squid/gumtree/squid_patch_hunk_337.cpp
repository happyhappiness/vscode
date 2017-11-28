 build_filter(char *filter, int size, const char *templ, const char *user, const char *group)
 {
     int n;
     while (*templ && size > 0) {
         switch (*templ) {
         case '%':
-            templ++;
+            ++templ;
             switch (*templ) {
             case 'u':
             case 'v':
-                templ++;
+                ++templ;
                 n = ldap_escape_value(filter, size, user);
                 size -= n;
                 filter += n;
                 break;
             case 'g':
             case 'a':
-                templ++;
+                ++templ;
                 n = ldap_escape_value(filter, size, group);
                 size -= n;
                 filter += n;
                 break;
             default:
                 fprintf(stderr, "ERROR: Unknown filter template string %%%c\n", *templ);
                 return 1;
                 break;
             }
             break;
         case '\\':
-            templ++;
+            ++templ;
             if (*templ) {
                 *filter = *templ;
                 ++filter;
                 ++templ;
                 --size;
             }
