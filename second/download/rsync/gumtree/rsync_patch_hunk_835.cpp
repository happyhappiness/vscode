 			rprintf(FERROR, "%s\n", line);
 			/* This is always fatal; the server will now
 			 * close the socket. */
 			return -1;
 		}
 
-		rprintf(FINFO, "%s\n", line);
+		/* This might be a MOTD line or a module listing, but there is
+		 * no way to differentiate it.  The manpage mentions this. */
+		if (output_motd)
+			rprintf(FINFO, "%s\n", line);
 	}
 	kluge_around_eof = 0;
 
 	for (i = 0; i < sargc; i++) {
 		io_printf(f_out, "%s\n", sargs[i]);
 	}
