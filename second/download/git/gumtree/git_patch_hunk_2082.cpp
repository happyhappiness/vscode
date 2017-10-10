 			/* prompts already contain ": " at the end */
 			die("could not read %s%s", prompt, err);
 		}
 	}
 	return r;
 }
-
-char *git_getpass(const char *prompt)
-{
-	return git_prompt(prompt, PROMPT_ASKPASS);
-}
