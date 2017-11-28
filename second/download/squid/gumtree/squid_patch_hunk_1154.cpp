         ErrorState err(ERR_INVALID_URL, Http::scNotFound, req);
         std::unique_ptr<HttpReply> reply(err.BuildHttpReply());
         replyBuf.reset(reply->pack());
     } else {
         std::unique_ptr<HttpReply> reply(new HttpReply);
         reply->setHeaders(Http::scOkay, NULL, "text/plain", -1, squid_curtime, squid_curtime);
-        reply->header.putStr(HDR_CONNECTION, "close"); // until we chunk response
+        reply->header.putStr(Http::HdrType::CONNECTION, "close"); // until we chunk response
         replyBuf.reset(reply->pack());
     }
     writer = asyncCall(16, 5, "Mgr::Inquirer::noteWroteHeader",
                        CommCbMemFunT<Inquirer, CommIoCbParams>(this, &Inquirer::noteWroteHeader));
     Comm::Write(conn, replyBuf.get(), writer);
 }
