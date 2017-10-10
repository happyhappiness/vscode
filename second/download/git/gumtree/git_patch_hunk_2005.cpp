 		if (!askpass)
 			askpass = getenv("SSH_ASKPASS");
 		if (askpass && *askpass)
 			r = do_askpass(askpass, prompt);
 	}
 
-	if (!r)
-		r = git_terminal_prompt(prompt, flags & PROMPT_ECHO);
 	if (!r) {
-		/* prompts already contain ": " at the end */
-		die("could not read %s%s", prompt, strerror(errno));
+		const char *err;
+
+		if (git_env_bool("GIT_TERMINAL_PROMPT", 1)) {
+			r = git_terminal_prompt(prompt, flags & PROMPT_ECHO);
+			err = strerror(errno);
+		} else {
+			err = "terminal prompts disabled";
+		}
+		if (!r) {
+			/* prompts already contain ": " at the end */
+			die("could not read %s%s", prompt, err);
+		}
 	}
 	return r;
 }
 
 char *git_getpass(const char *prompt)
 {
