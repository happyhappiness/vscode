 	if (fixup_message)
 		f++;
 	if (logfile)
 		f++;
 	if (f > 1)
 		die(_("Only one of -c/-C/-F/--fixup can be used."));
-	if (message.len && f > 0)
+	if (have_option_m && f > 0)
 		die((_("Option -m cannot be combined with -c/-C/-F/--fixup.")));
-	if (f || message.len)
+	if (f || have_option_m)
 		template_file = NULL;
 	if (edit_message)
 		use_message = edit_message;
 	if (amend && !use_message && !fixup_message)
 		use_message = "HEAD";
 	if (!use_message && whence != FROM_CHERRY_PICK && renew_authorship)
