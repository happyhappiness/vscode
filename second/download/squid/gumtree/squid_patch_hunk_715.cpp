             /* Ugly workaround for certain very broken browsers using the
              * wrong method to calculate the request-digest on POST request.
              * This should be deleted once Digest authentication becomes more
              * widespread and such broken browsers no longer are commonly
              * used.
              */
+            sTmp = HttpRequestMethod(Http::METHOD_GET).image();
             DigestCalcResponse(SESSIONKEY, authenticateDigestNonceNonceb64(digest_request->nonce),
                                digest_request->nc, digest_request->cnonce, digest_request->qop,
-                               RequestMethodStr(Http::METHOD_GET), digest_request->uri, HA2, Response);
+                               sTmp.c_str(), digest_request->uri, HA2, Response);
 
             if (strcasecmp(digest_request->response, Response)) {
                 auth_user->credentials(Auth::Failed);
                 digest_request->flags.invalid_password = true;
                 digest_request->setDenyMessage("Incorrect password");
                 return;
