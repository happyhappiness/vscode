 	}
 
 	/* if we see a bogus header don't ignore it. Shout and scream */
 
 	if (!(l = strchr(w, ':'))) {
  	    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-			"malformed header in meta file: %s", r->filename);
+                "malformed header in meta file: %s", r->filename);
 	    return HTTP_INTERNAL_SERVER_ERROR;
 	}
 
 	*l++ = '\0';
 	while (*l && apr_isspace(*l))
 	    ++l;
