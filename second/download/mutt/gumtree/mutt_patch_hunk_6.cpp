     {
       if (fp == NULL && mutt_strcmp(tempfile, a->filename))
       {
 	/* send case: the file is already there */
 	if (safe_symlink (a->filename, tempfile) == -1)
 	{
-	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), 1) == M_YES)
+	  if (mutt_yesorno (_("Can't match nametemplate, continue?"), M_YES) == M_YES)
 	    strfcpy (tempfile, a->filename, sizeof (tempfile));
 	  else
 	    goto return_error;
 	}
 	else
 	  unlink_tempfile = 1;
