  * like `id -G` on Linux, but it's too hard to find a portable
  * equivalent.
  **/
 
 #include "rsync.h"
 
-#ifndef NGROUPS
-/* It ought to be defined, but just in case. */
-#  define NGROUPS 32
-#endif
-
 int
 main(UNUSED(int argc), UNUSED(char *argv[]))
 {
 	int n, i;
-	gid_t list[NGROUPS];
+	gid_t *list;
+	gid_t gid = MY_GID();
+	int gid_in_list = 0;
 
-	if ((n = getgroups(NGROUPS, list)) == -1) {
+#ifdef HAVE_GETGROUPS
+	if ((n = getgroups(0, NULL)) < 0) {
 		perror("getgroups");
 		return 1;
 	}
+#else
+	n = 0;
+#endif
+
+	list = (gid_t*)malloc(sizeof (gid_t) * (n + 1));
+	if (!list) {
+		fprintf(stderr, "out of memory!\n");
+		exit(1);
+	}
+
+#ifdef HAVE_GETGROUPS
+	if (n > 0)
+		n = getgroups(n, list);
+#endif
 
-	for (i = 0; i < n; i++) 
-		printf("%u ", list[i]);
+	for (i = 0; i < n; i++)  {
+		printf("%lu ", (unsigned long)list[i]);
+		if (list[i] == gid)
+			gid_in_list = 1;
+	}
+	/* The default gid might not be in the list on some systems. */
+	if (!gid_in_list)
+		printf("%lu", (unsigned long)gid);
 	printf("\n");
 		
 	return 0;
 }
