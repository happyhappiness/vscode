 {
     debugs(16, 5, HERE);
     Ipc::Inquirer::start();
     Must(Comm::IsConnOpen(conn));
     Must(aggrAction != NULL);
 
-#if HAVE_UNIQUE_PTR
     std::unique_ptr<MemBuf> replyBuf;
-#else
-    std::auto_ptr<MemBuf> replyBuf;
-#endif
     if (strands.empty()) {
         LOCAL_ARRAY(char, url, MAX_URL);
         snprintf(url, MAX_URL, "%s", aggrAction->command().params.httpUri.termedBuf());
         HttpRequest *req = HttpRequest::CreateFromUrl(url);
         ErrorState err(ERR_INVALID_URL, Http::scNotFound, req);
-#if HAVE_UNIQUE_PTR
         std::unique_ptr<HttpReply> reply(err.BuildHttpReply());
-#else
-        std::auto_ptr<HttpReply> reply(err.BuildHttpReply());
-#endif
         replyBuf.reset(reply->pack());
     } else {
-#if HAVE_UNIQUE_PTR
         std::unique_ptr<HttpReply> reply(new HttpReply);
-#else
-        std::auto_ptr<HttpReply> reply(new HttpReply);
-#endif
         reply->setHeaders(Http::scOkay, NULL, "text/plain", -1, squid_curtime, squid_curtime);
         reply->header.putStr(HDR_CONNECTION, "close"); // until we chunk response
         replyBuf.reset(reply->pack());
     }
     writer = asyncCall(16, 5, "Mgr::Inquirer::noteWroteHeader",
                        CommCbMemFunT<Inquirer, CommIoCbParams>(this, &Inquirer::noteWroteHeader));
