 				strbuf_reset(&nbuf);
 				if (unquote_c_style(&nbuf, buf.buf, NULL))
 					die("line is badly quoted");
 				strbuf_swap(&buf, &nbuf);
 			}
 			p = prefix_path(prefix, prefix_length, buf.buf);
-			checkout_file(p, prefix_length);
+			checkout_file(p, prefix);
 			if (p < buf.buf || p > buf.buf + buf.len)
 				free((char *)p);
 		}
 		strbuf_release(&nbuf);
 		strbuf_release(&buf);
 	}
