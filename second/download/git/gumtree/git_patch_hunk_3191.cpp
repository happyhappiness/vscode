 		return NULL;
 	}
 
 	fputs(prompt, output_fh);
 	fflush(output_fh);
 
-	r = strbuf_getline(&buf, input_fh, '\n');
+	r = strbuf_getline_lf(&buf, input_fh);
 	if (!echo) {
 		putc('\n', output_fh);
 		fflush(output_fh);
 	}
 
 	restore_term();
