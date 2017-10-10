 			to_fetch[nr_heads++] = ref;
 		}
 		else
 			die("http transport does not support %s", buf->buf);
 
 		strbuf_reset(buf);
-		if (strbuf_getline(buf, stdin, '\n') == EOF)
+		if (strbuf_getline_lf(buf, stdin) == EOF)
 			return;
 		if (!*buf->buf)
 			break;
 	} while (1);
 
 	if (fetch(nr_heads, to_fetch))
