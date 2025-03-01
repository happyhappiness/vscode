         debugs(9, 9, HERE << ": found user='" << user << "'(" << total_len <<") unescaped.");
     }
 
     debugs(9, 9, HERE << ": OUT: login='" << login << "', escaped=" << escaped << ", user=" << user << ", password=" << password);
 }
 
+/**
+ * Cancel the timeout on the Control socket and establish one
+ * on the data socket
+ */
 void
-FtpStateData::ftpTimeout(const CommTimeoutCbParams &io)
+FtpStateData::switchTimeoutToDataChannel()
 {
-    debugs(9, 4, "ftpTimeout: FD " << io.fd << ": '" << entry->url() << "'" );
+    commUnsetConnTimeout(ctrl.conn);
 
-    if (SENT_PASV == state && io.fd == data.fd) {
-        /* stupid ftp.netscape.com */
-        fwd->dontRetry(false);
-        fwd->ftpPasvFailed(true);
-        debugs(9, DBG_IMPORTANT, "ftpTimeout: timeout in SENT_PASV state" );
+    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
+    AsyncCall::Pointer timeoutCall = JobCallback(9, 5, TimeoutDialer, this, FtpStateData::ftpTimeout);
+    commSetConnTimeout(data.conn, Config.Timeout.read, timeoutCall);
+}
+
+void
+FtpStateData::listenForDataChannel(const Comm::ConnectionPointer &conn, const char *note)
+{
+    assert(!Comm::IsConnOpen(data.conn));
+
+    typedef CommCbMemFunT<FtpStateData, CommAcceptCbParams> AcceptDialer;
+    typedef AsyncCallT<AcceptDialer> AcceptCall;
+    RefCount<AcceptCall> call = static_cast<AcceptCall*>(JobCallback(11, 5, AcceptDialer, this, FtpStateData::ftpAcceptDataConnection));
+    Subscription::Pointer sub = new CallSubscription<AcceptCall>(call);
+
+    /* open the conn if its not already open */
+    if (!Comm::IsConnOpen(conn)) {
+        conn->fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, conn->local, conn->flags, note);
+        if (!Comm::IsConnOpen(conn)) {
+            debugs(5, DBG_CRITICAL, HERE << "comm_open_listener failed:" << conn->local << " error: " << errno);
+            return;
+        }
+        debugs(9, 3, HERE << "Unconnected data socket created on " << conn);
     }
 
-    failed(ERR_READ_TIMEOUT, 0);
-    /* failed() closes ctrl.fd and frees ftpState */
+    assert(Comm::IsConnOpen(conn));
+    AsyncJob::Start(new Comm::TcpAcceptor(conn, note, sub));
+
+    // Ensure we have a copy of the FD opened for listening and a close handler on it.
+    data.opened(conn, dataCloser());
+    switchTimeoutToDataChannel();
 }
 
 void
-FtpStateData::listingStart()
+FtpStateData::ftpTimeout(const CommTimeoutCbParams &io)
 {
-    debugs(9,3, HERE);
-    wordlist *w;
-    char *dirup;
-    int i, j, k;
-    const char *title = title_url.termedBuf();
-    flags.listing_started = true;
-    printfReplyBody("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
-    printfReplyBody("<!-- HTML listing generated by Squid %s -->\n",
-                    version_string);
-    printfReplyBody("<!-- %s -->\n", mkrfc1123(squid_curtime));
-    printfReplyBody("<HTML><HEAD><TITLE>\n");
-    {
-        char *t = xstrdup(title);
-        rfc1738_unescape(t);
-        printfReplyBody("FTP Directory: %s\n", html_quote(t));
-        xfree(t);
-    }
-
-    printfReplyBody("</TITLE>\n");
-    printfReplyBody("<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}--></STYLE>\n");
-
-    if (flags.need_base_href)
-        printfReplyBody("<BASE HREF=\"%s\">\n",
-                        html_quote(base_href.termedBuf()));
-
-    printfReplyBody("</HEAD><BODY>\n");
-
-    if (cwd_message) {
-        printfReplyBody("<PRE>\n");
-
-        for (w = cwd_message; w; w = w->next)
-            printfReplyBody("%s\n", html_quote(w->key));
-
-        printfReplyBody("</PRE>\n");
-
-        printfReplyBody("<HR noshade size=\"1px\">\n");
-
-        wordlistDestroy(&cwd_message);
-    }
-
-    printfReplyBody("<H2>\n");
-    printfReplyBody("FTP Directory: ");
-    /* "ftp://" == 6 characters */
-    assert(title_url.size() >= 6);
-    k = 6 + strcspn(&title[6], "/");
-
-    for (i = 6, j = 0; title[i]; j = i) {
-        printfReplyBody("<A HREF=\"");
-        i += strcspn(&title[i], "/");
-
-        if (i > j) {
-            char *url = xstrdup(title);
-            url[i] = '\0';
-            printfReplyBody("%s", html_quote(url + k));
-            printfReplyBody("/");
-            printfReplyBody("\">");
-            rfc1738_unescape(url + j);
-            printfReplyBody("%s", html_quote(url + j));
-            safe_free(url);
-            printfReplyBody("</A>");
-        }
-
-        printfReplyBody("/");
-
-        if (title[i] == '/')
-            i++;
-
-        if (i == j) {
-            /* Error guard, or "assert" */
-            printfReplyBody("ERROR: Failed to parse URL: %s\n",
-                            html_quote(title));
-            debugs(9, DBG_CRITICAL, "Failed to parse URL: " << title);
-            break;
+    debugs(9, 4, HERE << io.conn << ": '" << entry->url() << "'" );
+
+    if (abortOnBadEntry("entry went bad while waiting for a timeout"))
+        return;
+
+    if (SENT_PASV == state) {
+        /* stupid ftp.netscape.com, of FTP server behind stupid firewall rules */
+        flags.pasv_supported = false;
+        debugs(9, DBG_IMPORTANT, "ftpTimeout: timeout in SENT_PASV state" );
+
+        // cancel the data connection setup.
+        if (data.opener != NULL) {
+            data.opener->cancel("timeout");
+            data.opener = NULL;
         }
+        data.close();
     }
 
-    printfReplyBody("</H2>\n");
-    printfReplyBody("<PRE>\n");
-    dirup = htmlifyListEntry("<internal-dirup>");
-    writeReplyBody(dirup, strlen(dirup));
-    flags.html_header_sent = 1;
+    failed(ERR_READ_TIMEOUT, 0);
+    /* failed() closes ctrl.conn and frees ftpState */
 }
 
+#if DEAD_CODE // obsoleted by ERR_DIR_LISTING
 void
 FtpStateData::listingFinish()
 {
-    debugs(9,3,HERE);
-    entry->buffer();
-    printfReplyBody("</PRE>\n");
+    // TODO: figure out what this means and how to show it ...
 
     if (flags.listformat_unknown && !flags.tried_nlst) {
-        printfReplyBody("<A HREF=\"%s/;type=d\">[As plain directory]</A>\n",
+        printfReplyBody("<a href=\"%s/;type=d\">[As plain directory]</a>\n",
                         flags.dir_slash ? rfc1738_escape_part(old_filepath) : ".");
     } else if (typecode == 'D') {
         const char *path = flags.dir_slash ? filepath : ".";
-        printfReplyBody("<A HREF=\"%s/\">[As extended directory]</A>\n", rfc1738_escape_part(path));
+        printfReplyBody("<a href=\"%s/\">[As extended directory]</a>\n", rfc1738_escape_part(path));
     }
-
-    printfReplyBody("<HR noshade size=\"1px\">\n");
-    printfReplyBody("<ADDRESS>\n");
-    printfReplyBody("Generated %s by %s (%s)\n",
-                    mkrfc1123(squid_curtime),
-                    getMyHostname(),
-                    visible_appname_string);
-    printfReplyBody("</ADDRESS></BODY></HTML>\n");
 }
+#endif /* DEAD_CODE */
 
 /// \ingroup ServerProtocolFTPInternal
 static const char *Month[] = {
     "Jan", "Feb", "Mar", "Apr", "May", "Jun",
     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
 };
