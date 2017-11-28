             if (strcasecmp(digest_request->response, Response)) {
                 auth_user->credentials(Auth::Failed);
                 digest_request->flags.invalid_password = true;
                 digest_request->setDenyMessage("Incorrect password");
                 return;
             } else {
-                const char *useragent = request->header.getStr(HDR_USER_AGENT);
+                const char *useragent = request->header.getStr(Http::HdrType::USER_AGENT);
 
                 static Ip::Address last_broken_addr;
                 static int seen_broken_client = 0;
 
                 if (!seen_broken_client) {
                     last_broken_addr.setNoAddr();
