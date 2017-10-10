 
 	if (want_name) {
 		int using_default = 0;
 		if (!name) {
 			if (strict && ident_use_config_only
 			    && !(ident_config_given & IDENT_NAME_GIVEN)) {
-				fputs(env_hint, stderr);
+				fputs(_(env_hint), stderr);
 				die("no name was given and auto-detection is disabled");
 			}
 			name = ident_default_name();
 			using_default = 1;
 			if (strict && default_name_is_bogus) {
-				fputs(env_hint, stderr);
+				fputs(_(env_hint), stderr);
 				die("unable to auto-detect name (got '%s')", name);
 			}
 		}
 		if (!*name) {
 			struct passwd *pw;
 			if (strict) {
 				if (using_default)
-					fputs(env_hint, stderr);
+					fputs(_(env_hint), stderr);
 				die("empty ident name (for <%s>) not allowed", email);
 			}
 			pw = xgetpwuid_self(NULL);
 			name = pw->pw_name;
 		}
 	}
 
 	if (!email) {
 		if (strict && ident_use_config_only
 		    && !(ident_config_given & IDENT_MAIL_GIVEN)) {
-			fputs(env_hint, stderr);
+			fputs(_(env_hint), stderr);
 			die("no email was given and auto-detection is disabled");
 		}
 		email = ident_default_email();
 		if (strict && default_email_is_bogus) {
-			fputs(env_hint, stderr);
+			fputs(_(env_hint), stderr);
 			die("unable to auto-detect email address (got '%s')", email);
 		}
 	}
 
 	strbuf_reset(&ident);
 	if (want_name) {
