 
 	/*
 	 * Capture output to output buffer and check the return code from the
 	 * child process.  A '0' indicates a hit, a '1' indicates no hit and
 	 * anything else is an error.
 	 */
-	status = capture_command(&cp, &w->out, 0);
+	status = capture_command(&cp, &child_output, 0);
 	if (status && (status != 1)) {
 		/* flush the buffer */
-		write_or_die(1, w->out.buf, w->out.len);
+		write_or_die(1, child_output.buf, child_output.len);
 		die("process for submodule '%s' failed with exit code: %d",
 		    gs->name, status);
 	}
 
+	opt->output(opt, child_output.buf, child_output.len);
+	strbuf_release(&child_output);
 	/* invert the return code to make a hit equal to 1 */
 	return !status;
 }
 
 /*
  * Prep grep structures for a submodule grep
