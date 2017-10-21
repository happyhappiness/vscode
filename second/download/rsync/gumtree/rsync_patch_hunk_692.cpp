 #include "rsync.h"
 
 int dry_run, read_only, list_only, verbose;
 int preserve_perms = 0;
 
 
-int main(int argc, char **argv)
+int
+main(int argc, char **argv)
 {
 	if (argc != 3) {
 		fprintf(stderr, "usage: t_unsafe LINKDEST SRCDIR\n");
 		return 1;
 	}
 
