  */
 
 /* The functions in this file handle authentication.
  * They DO NOT perform access control or auditing.
  * See acl.c for access control and client_side.c for auditing */
 
-#include "squid.h"
-#include "auth/UserRequest.h"
-#include "auth/User.h"
-/*#include "auth/Gadgets.h"
-#include "acl/Acl.h"
-#include "client_side.h"
-*/
+#include "squid-old.h"
 #include "auth/Config.h"
 #include "auth/Scheme.h"
+#include "auth/UserRequest.h"
+#include "auth/User.h"
+#include "comm/Connection.h"
 #include "HttpReply.h"
 #include "HttpRequest.h"
 
 /* Generic Functions */
 
-size_t
-AuthUserRequest::refCount () const
-{
-    return references;
-}
-
 char const *
-AuthUserRequest::username() const
+Auth::UserRequest::username() const
 {
-    if (user())
+    if (user() != NULL)
         return user()->username();
     else
         return NULL;
 }
 
-size_t
-authenticateRequestRefCount (AuthUserRequest *aRequest)
-{
-    return aRequest->refCount();
-}
-
 /**** PUBLIC FUNCTIONS (ALL GENERIC!)  ****/
 
 /* send the initial data to an authenticator module */
 void
-AuthUserRequest::start(RH * handler, void *data)
+Auth::UserRequest::start(AUTHCB * handler, void *data)
 {
     assert(handler);
-    debugs(29, 9, "authenticateStart: auth_user_request '" << this << "'");
+    assert(data);
+    debugs(29, 9, HERE << "auth_user_request '" << this << "'");
     module_start(handler, data);
 }
 
-/*
- * Check a auth_user pointer for validity. Does not check passwords, just data
- * sensability. Broken or Unknown auth_types are not valid for use...
- */
-
-int
-authenticateValidateUser(AuthUserRequest * auth_user_request)
+bool
+Auth::UserRequest::valid() const
 {
-    debugs(29, 9, "authenticateValidateUser: Validating Auth_user request '" << auth_user_request << "'.");
+    debugs(29, 9, HERE << "Validating Auth::UserRequest '" << this << "'.");
 
-    if (auth_user_request == NULL) {
-        debugs(29, 4, "authenticateValidateUser: Auth_user_request was NULL!");
-        return 0;
-    }
-
-    if (auth_user_request->user() == NULL) {
-        debugs(29, 4, "authenticateValidateUser: No associated auth_user structure");
-        return 0;
+    if (user() == NULL) {
+        debugs(29, 4, HERE << "No associated Auth::User data");
+        return false;
     }
 
-    if (auth_user_request->user()->auth_type == AUTH_UNKNOWN) {
-        debugs(29, 4, "authenticateValidateUser: Auth_user '" << auth_user_request->user() << "' uses unknown scheme.");
-        return 0;
+    if (user()->auth_type == Auth::AUTH_UNKNOWN) {
+        debugs(29, 4, HERE << "Auth::User '" << user() << "' uses unknown scheme.");
+        return false;
     }
 
-    if (auth_user_request->user()->auth_type == AUTH_BROKEN) {
-        debugs(29, 4, "authenticateValidateUser: Auth_user '" << auth_user_request->user() << "' is broken for it's scheme.");
-        return 0;
+    if (user()->auth_type == Auth::AUTH_BROKEN) {
+        debugs(29, 4, HERE << "Auth::User '" << user() << "' is broken for it's scheme.");
+        return false;
     }
 
     /* any other sanity checks that we need in the future */
 
-    /* Thus should a module call to something like authValidate */
-
     /* finally return ok */
-    debugs(29, 5, "authenticateValidateUser: Validated Auth_user request '" << auth_user_request << "'.");
-
-    return 1;
-
+    debugs(29, 5, HERE << "Validated. Auth::UserRequest '" << this << "'.");
+    return true;
 }
 
 void *
-AuthUserRequest::operator new (size_t byteCount)
+Auth::UserRequest::operator new (size_t byteCount)
 {
-    fatal ("AuthUserRequest not directly allocatable\n");
+    fatal("Auth::UserRequest not directly allocatable\n");
     return (void *)1;
 }
 
 void
-AuthUserRequest::operator delete (void *address)
+Auth::UserRequest::operator delete (void *address)
 {
-    fatal ("AuthUserRequest child failed to override operator delete\n");
+    fatal("Auth::UserRequest child failed to override operator delete\n");
 }
 
-AuthUserRequest::AuthUserRequest():_auth_user(NULL), message(NULL),
-        references (0), lastReply (AUTH_ACL_CANNOT_AUTHENTICATE)
+Auth::UserRequest::UserRequest():
+        _auth_user(NULL),
+        message(NULL),
+        lastReply(AUTH_ACL_CANNOT_AUTHENTICATE)
 {
-    debugs(29, 5, "AuthUserRequest::AuthUserRequest: initialised request " <<
-           this);
+    debugs(29, 5, HERE << "initialised request " << this);
 }
 
-AuthUserRequest::~AuthUserRequest()
+Auth::UserRequest::~UserRequest()
 {
-    dlink_node *link;
-    debugs(29, 5, "AuthUserRequest::~AuthUserRequest: freeing request " <<
-           this);
-    assert(references == 0);
-
-    if (user()) {
-        /* unlink from the auth_user struct */
-        link = user()->requests.head;
-
-        while (link && (link->data != this))
-            link = link->next;
-
-        assert(link != NULL);
-
-        dlinkDelete(link, &user()->requests);
-
-        dlinkNodeDelete(link);
-
-        /* unlock the request structure's lock */
-        user()->unlock();
+    assert(RefCountCount()==0);
+    debugs(29, 5, HERE << "freeing request " << this);
 
+    if (user() != NULL) {
+        /* release our references to the user credentials */
         user(NULL);
     }
 
-    safe_free (message);
+    safe_free(message);
 }
 
 void
-AuthUserRequest::setDenyMessage (char const *aString)
+Auth::UserRequest::setDenyMessage(char const *aString)
 {
-    safe_free (message);
-    message = xstrdup (aString);
+    safe_free(message);
+    message = xstrdup(aString);
 }
 
 char const *
-AuthUserRequest::getDenyMessage ()
+Auth::UserRequest::getDenyMessage()
 {
     return message;
 }
 
 char const *
-AuthUserRequest::denyMessage(char const * const default_message)
+Auth::UserRequest::denyMessage(char const * const default_message)
 {
     if (this == NULL || getDenyMessage() == NULL) {
         return default_message;
     }
 
     return getDenyMessage();
 }
 
 static void
-authenticateAuthUserRequestSetIp(AuthUserRequest * auth_user_request, IpAddress &ipaddr)
+authenticateAuthUserRequestSetIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address &ipaddr)
 {
-    AuthUser *auth_user = auth_user_request->user();
+    Auth::User::Pointer auth_user = auth_user_request->user();
 
     if (!auth_user)
         return;
 
     auth_user->addIp(ipaddr);
 }
 
 void
-authenticateAuthUserRequestRemoveIp(AuthUserRequest * auth_user_request, IpAddress const &ipaddr)
+authenticateAuthUserRequestRemoveIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address const &ipaddr)
 {
-    AuthUser *auth_user = auth_user_request->user();
+    Auth::User::Pointer auth_user = auth_user_request->user();
 
     if (!auth_user)
         return;
 
     auth_user->removeIp(ipaddr);
 }
 
 void
-authenticateAuthUserRequestClearIp(AuthUserRequest * auth_user_request)
+authenticateAuthUserRequestClearIp(Auth::UserRequest::Pointer auth_user_request)
 {
-    if (auth_user_request)
+    if (auth_user_request != NULL)
         auth_user_request->user()->clearIp();
 }
 
 int
-authenticateAuthUserRequestIPCount(AuthUserRequest * auth_user_request)
+authenticateAuthUserRequestIPCount(Auth::UserRequest::Pointer auth_user_request)
 {
-    assert(auth_user_request);
-    assert(auth_user_request->user());
+    assert(auth_user_request != NULL);
+    assert(auth_user_request->user() != NULL);
     return auth_user_request->user()->ipcount;
 }
 
 
 /*
  * authenticateUserAuthenticated: is this auth_user structure logged in ?
  */
 int
-authenticateUserAuthenticated(AuthUserRequest * auth_user_request)
+authenticateUserAuthenticated(Auth::UserRequest::Pointer auth_user_request)
 {
-    if (!authenticateValidateUser(auth_user_request))
+    if (auth_user_request == NULL || !auth_user_request->valid())
         return 0;
 
     return auth_user_request->authenticated();
 }
 
-int
-AuthUserRequest::direction()
+Auth::Direction
+Auth::UserRequest::direction()
 {
+    if (user() == NULL)
+        return Auth::CRED_ERROR; // No credentials. Should this be a CHALLENGE instead?
+
     if (authenticateUserAuthenticated(this))
-        return 0;
+        return Auth::CRED_VALID;
 
     return module_direction();
-
-    return -2;
 }
 
 void
-AuthUserRequest::addHeader(HttpReply * rep, int accelerated)
+Auth::UserRequest::addAuthenticationInfoHeader(HttpReply * rep, int accelerated)
 {}
 
 void
-AuthUserRequest::addTrailer(HttpReply * rep, int accelerated)
+Auth::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accelerated)
 {}
 
 void
-AuthUserRequest::onConnectionClose(ConnStateData *)
+Auth::UserRequest::onConnectionClose(ConnStateData *)
 {}
 
 const char *
-AuthUserRequest::connLastHeader()
+Auth::UserRequest::connLastHeader()
 {
-    fatal("AuthUserRequest::connLastHeader should always be overridden by conn based auth schemes");
+    fatal("Auth::UserRequest::connLastHeader should always be overridden by conn based auth schemes");
     return NULL;
 }
 
 /*
  * authenticateAuthenticateUser: call the module specific code to
  * log this user request in.
  * Cache hits may change the auth_user pointer in the structure if needed.
  * This is basically a handle approach.
  */
 static void
-authenticateAuthenticateUser(AuthUserRequest * auth_user_request, HttpRequest * request, ConnStateData * conn, http_hdr_type type)
+authenticateAuthenticateUser(Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, ConnStateData * conn, http_hdr_type type)
 {
-    assert(auth_user_request != NULL);
+    assert(auth_user_request.getRaw() != NULL);
 
     auth_user_request->authenticate(request, conn, type);
 }
 
-static AuthUserRequest *
-authTryGetUser (AuthUserRequest **auth_user_request, ConnStateData * conn, HttpRequest * request)
+static Auth::UserRequest::Pointer
+authTryGetUser(Auth::UserRequest::Pointer auth_user_request, ConnStateData * conn, HttpRequest * request)
 {
-    if (*auth_user_request)
-        return *auth_user_request;
-    else if (request != NULL && request->auth_user_request)
+    if (auth_user_request != NULL)
+        return auth_user_request;
+    else if (request != NULL && request->auth_user_request != NULL)
         return request->auth_user_request;
     else if (conn != NULL)
         return conn->auth_user_request;
     else
         return NULL;
 }
