      *
      * The found credentials are returned in aUR and if successfully authenticated
      * may now be cached in one or more of the above locations.
      *
      * \return Some AUTH_ACL_* state
      */
-    static AuthAclState tryToAuthenticateAndSetAuthUser(UserRequest::Pointer *aUR, http_hdr_type, HttpRequest *, ConnStateData *, Ip::Address &);
+    static AuthAclState tryToAuthenticateAndSetAuthUser(UserRequest::Pointer *aUR, http_hdr_type, HttpRequest *, ConnStateData *, Ip::Address &, AccessLogEntry::Pointer &);
 
     /// Add the appropriate [Proxy-]Authenticate header to the given reply
     static void addReplyAuthHeader(HttpReply * rep, UserRequest::Pointer auth_user_request, HttpRequest * request, int accelerated, int internal);
 
-    void start(AUTHCB *handler, void *data);
+    /** Start an asynchronous helper lookup to verify the user credentials
+     *
+     * Uses startHelperLookup() for scheme-specific actions.
+     *
+     * The given callback will be called when the auth module has performed
+     * it's external activities.
+     *
+     * \param handler   Handler to process the callback when its run
+     * \param data  CBDATA for handler
+     */
+    void start(HttpRequest *request, AccessLogEntry::Pointer &al, AUTHCB *handler, void *data);
+
     char const * denyMessage(char const * const default_message = NULL);
 
     /** Possibly overrideable in future */
     void setDenyMessage(char const *);
 
     /** Possibly overrideable in future */
