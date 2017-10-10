 			 * preimage, more "+" lines may come after it.
 			 */
 			return;
 		}
 		diff_words_flush(ecbdata);
 		if (ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN) {
-			emit_line(ecbdata->opt, context, reset, line, len);
-			fputs("~\n", ecbdata->opt->file);
+			emit_line(o, context, reset, line, len);
+			fputs("~\n", o->file);
 		} else {
 			/*
 			 * Skip the prefix character, if any.  With
 			 * diff_suppress_blank_empty, there may be
 			 * none.
 			 */
 			if (line[0] != '\n') {
 			      line++;
 			      len--;
 			}
-			emit_line(ecbdata->opt, context, reset, line, len);
+			emit_line(o, context, reset, line, len);
 		}
 		return;
 	}
 
 	switch (line[0]) {
 	case '+':
