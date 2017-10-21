 
 /**
  * @file trimslash.c
  *
  * Test harness; not linked into release.
  **/
-int main(int argc, char **argv)
+int
+main(int argc, char **argv)
 {
 	int i;
 	
 	if (argc <= 1) {
 		fprintf(stderr, "trimslash: needs at least one argument\n");
 		return 1;
