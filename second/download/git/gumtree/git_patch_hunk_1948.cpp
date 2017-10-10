 			 * of the buffer.
 			 */
 			char *bp;
 
 			bp = find_beginning_of_line(buf, scanp);
 
-			if (*bp != '\n') {
-				strbuf_splice(&sb, 0, 0, buf, endp - buf);
-				if (pos)
-					break; /* need to fill another block */
-				scanp = buf - 1; /* leave loop */
-			} else {
+			if (*bp == '\n') {
 				/*
-				 * (bp + 1) thru endp is the beginning of the
-				 * current line we have in sb
+				 * The newline is the end of the previous line,
+				 * so we know we have complete line starting
+				 * at (bp + 1). Prefix it onto any prior data
+				 * we collected for the line and process it.
 				 */
 				strbuf_splice(&sb, 0, 0, bp + 1, endp - (bp + 1));
 				scanp = bp;
 				endp = bp + 1;
+				ret = show_one_reflog_ent(&sb, fn, cb_data);
+				strbuf_reset(&sb);
+				if (ret)
+					break;
+			} else if (!pos) {
+				/*
+				 * We are at the start of the buffer, and the
+				 * start of the file; there is no previous
+				 * line, and we have everything for this one.
+				 * Process it, and we can end the loop.
+				 */
+				strbuf_splice(&sb, 0, 0, buf, endp - buf);
+				ret = show_one_reflog_ent(&sb, fn, cb_data);
+				strbuf_reset(&sb);
+				break;
 			}
-			ret = show_one_reflog_ent(&sb, fn, cb_data);
-			strbuf_reset(&sb);
-			if (ret)
+
+			if (bp == buf) {
+				/*
+				 * We are at the start of the buffer, and there
+				 * is more file to read backwards. Which means
+				 * we are in the middle of a line. Note that we
+				 * may get here even if *bp was a newline; that
+				 * just means we are at the exact end of the
+				 * previous line, rather than some spot in the
+				 * middle.
+				 *
+				 * Save away what we have to be combined with
+				 * the data from the next read.
+				 */
+				strbuf_splice(&sb, 0, 0, buf, endp - buf);
 				break;
+			}
 		}
 
 	}
 	if (!ret && sb.len)
-		ret = show_one_reflog_ent(&sb, fn, cb_data);
+		die("BUG: reverse reflog parser had leftover data");
 
 	fclose(logfp);
 	strbuf_release(&sb);
 	return ret;
 }
 
