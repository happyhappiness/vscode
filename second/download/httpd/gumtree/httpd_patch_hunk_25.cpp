 
 PROXY_DECLARE(int) ap_proxyerror(request_rec *r, int statuscode, const char *message)
 {
     apr_table_setn(r->notes, "error-notes",
 	apr_pstrcat(r->pool, 
 		"The proxy server could not handle the request "
-		"<EM><A HREF=\"", ap_escape_uri(r->pool, r->uri),
+		"<em><a href=\"", ap_escape_uri(r->pool, r->uri),
 		"\">", ap_escape_html(r->pool, r->method),
 		"&nbsp;", 
-		ap_escape_html(r->pool, r->uri), "</A></EM>.<P>\n"
-		"Reason: <STRONG>",
+		ap_escape_html(r->pool, r->uri), "</a></em>.<p>\n"
+		"Reason: <strong>",
 		ap_escape_html(r->pool, message), 
-		"</STRONG>", NULL));
+		"</strong></p>", NULL));
 
     /* Allow "error-notes" string to be printed by ap_send_error_response() */
     apr_table_setn(r->notes, "verbose-error-to", apr_pstrdup(r->pool, "*"));
 
     r->status_line = apr_psprintf(r->pool, "%3.3u Proxy Error", statuscode);
     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
