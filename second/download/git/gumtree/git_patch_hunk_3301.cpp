 			pw = xgetpwuid_self(NULL);
 			name = pw->pw_name;
 		}
 	}
 
 	if (!email) {
+		if (strict && ident_use_config_only
+		    && !(ident_config_given & IDENT_MAIL_GIVEN)) {
+			fputs(env_hint, stderr);
+			die("no email was given and auto-detection is disabled");
+		}
 		email = ident_default_email();
 		if (strict && default_email_is_bogus) {
 			fputs(env_hint, stderr);
 			die("unable to auto-detect email address (got '%s')", email);
 		}
-		if (strict && ident_use_config_only
-		    && !(ident_config_given & IDENT_MAIL_GIVEN))
-			die("user.useConfigOnly set but no mail given");
 	}
 
 	strbuf_reset(&ident);
 	if (want_name) {
 		strbuf_addstr_without_crud(&ident, name);
 		strbuf_addstr(&ident, " <");
