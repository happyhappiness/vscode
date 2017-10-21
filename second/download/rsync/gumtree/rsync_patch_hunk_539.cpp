 
 
 void auth_client(int fd, char *user, char *challenge)
 {
 	char *pass;
 	char pass2[30];
+	extern char *password_file;
 
 	if (!user || !*user) return;
 
-	if (!(pass=getenv("RSYNC_PASSWORD"))) {
+	if (!(pass=getpassf(password_file)) && !(pass=getenv("RSYNC_PASSWORD"))) {
 		pass = getpass("Password: ");
 	}
 
 	if (!pass || !*pass) {
 		pass = "";
 	}
 
 	generate_hash(pass, challenge, pass2);
-	
 	io_printf(fd, "%s %s\n", user, pass2);
 }
 
+
