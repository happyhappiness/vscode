 
 	if (reflog) {
 		unsigned char sha1[20];
 		char nth_desc[256];
 		char *ref;
 		int base = 0;
+		unsigned int flags = 0;
 
 		if (ac == 0) {
 			static const char *fake_av[2];
 
-			fake_av[0] = resolve_refdup("HEAD", sha1, 1, NULL);
+			fake_av[0] = resolve_refdup("HEAD",
+						    RESOLVE_REF_READING,
+						    sha1, NULL);
 			fake_av[1] = NULL;
 			av = fake_av;
 			ac = 1;
 		}
 		if (ac != 1)
 			die("--reflog option needs one branch name");
