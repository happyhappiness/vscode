 again:
 	if (line->len >= (*(mi->content_top))->len + 2 &&
 	    !memcmp(line->buf + (*(mi->content_top))->len, "--", 2)) {
 		/* we hit an end boundary */
 		/* pop the current boundary off the stack */
 		strbuf_release(*(mi->content_top));
-		free(*(mi->content_top));
-		*(mi->content_top) = NULL;
+		FREE_AND_NULL(*(mi->content_top));
 
 		/* technically won't happen as is_multipart_boundary()
 		   will fail first.  But just in case..
 		 */
 		if (--mi->content_top < mi->content) {
 			error("Detected mismatched boundaries, can't recover");
