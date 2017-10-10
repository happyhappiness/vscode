 	if (blen <= 0 || (unsigned)(ret = vsnprintf(buf, blen, fmt, va)) >= (unsigned)blen)
 		die("Fatal: buffer too small. Please report a bug.");
 	va_end(va);
 	return ret;
 }
 
-static struct imap_cmd *v_issue_imap_cmd(struct imap_store *ctx,
-					 struct imap_cmd_cb *cb,
-					 const char *fmt, va_list ap)
+static struct imap_cmd *issue_imap_cmd(struct imap_store *ctx,
+				       struct imap_cmd_cb *cb,
+				       const char *fmt, va_list ap)
 {
 	struct imap *imap = ctx->imap;
 	struct imap_cmd *cmd;
 	int n, bufl;
 	char buf[1024];
 
