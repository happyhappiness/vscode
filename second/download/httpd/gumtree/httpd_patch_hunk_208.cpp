      * Rather than fall out to autoindex or some other mapper, this
      * request must die.
      */
     if (anymatch && !neg->avail_vars->nelts) {
 	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
 		      "Negotiation: discovered file(s) matching request: %s"
-                      " (None could be negotiated).", 
+                      " (None could be negotiated).",
                       r->filename);
         return HTTP_NOT_FOUND;
     }
 
     set_vlist_validator(r, r);
 
