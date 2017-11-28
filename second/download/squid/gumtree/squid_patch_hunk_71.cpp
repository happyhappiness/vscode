  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
  *
  */
 
-#ifndef SQUID_AUTHUSERREQUEST_H
-#define SQUID_AUTHUSERREQUEST_H
+#ifndef SQUID_AUTH_USERREQUEST_H
+#define SQUID_AUTH_USERREQUEST_H
 
-#include "client_side.h"
+#if USE_AUTH
 
-class AuthUser;
+#include "auth/AuthAclState.h"
+#include "auth/Scheme.h"
+#include "auth/User.h"
+#include "dlink.h"
+#include "ip/Address.h"
+#include "typedefs.h"
+#include "HttpHeader.h"
 
 class ConnStateData;
+class HttpReply;
+class HttpRequest;
 
-class AuthScheme;
+/**
+ * Maximum length (buffer size) for token strings.
+ */
+// AYJ: must match re-definition in helpers/negotiate_auth/kerberos/negotiate_kerb_auth.cc
+#define MAX_AUTHTOKEN_LEN   32768
 
-struct AuthUserIP {
+/// \ingroup AuthAPI
+class AuthUserIP
+{
+public:
     dlink_node node;
     /* IP addr this user authenticated from */
 
-    IpAddress ipaddr;
+    Ip::Address ipaddr;
     time_t ip_expiretime;
 };
 
+// TODO: make auth schedule AsyncCalls?
+typedef void AUTHCB(void*);
+
+namespace Auth
+{
+
+// NP: numeric values specified for old code backward compatibility.
+//  remove after transition is complete
+enum Direction {
+    CRED_CHALLENGE = 1, ///< Client needs to be challenged. secure token.
+    CRED_VALID = 0,     ///< Credentials are valid and a up to date. The OK/Failed state is accurate.
+    CRED_LOOKUP = -1,   ///< Credentials need to be validated with the backend helper
+    CRED_ERROR = -2     ///< ERROR in the auth module. Cannot determine the state of this request.
+};
+
 /**
- \ingroup AuthAPI
  * This is a short lived structure is the visible aspect of the authentication framework.
+ *
+ * It and its children hold the state data while processing authentication for a client request.
+ * The AuthenticationStateData object is merely a CBDATA wrapper for one of these.
  */
-class AuthUserRequest
+class UserRequest : public RefCountable
 {
+public:
+    typedef RefCount<Auth::UserRequest> Pointer;
+
+    UserRequest();
+    virtual ~UserRequest();
+    void *operator new(size_t byteCount);
+    void operator delete(void *address);
 
 public:
     /**
      * This is the object passed around by client_side and acl functions
      * it has request specific data, and links to user specific data
      * the user
      */
-    AuthUser *_auth_user;
+    User::Pointer _auth_user;
 
     /**
      *  Used by squid to determine what the next step in performing authentication for a given scheme is.
      *
-     \retval -2	ERROR in the auth module. Cannot determine request direction.
-     \retval -1	The auth module needs to send data to an external helper.
-     *		Squid will prepare for a callback on the request and call the AUTHSSTART function.
-     \retval  0	The auth module has all the information it needs to perform the authentication and provide a succeed/fail result.
-     \retval  1	The auth module needs to send a new challenge to the request originator.
-     *		Squid will return the appropriate status code (401 or 407) and call the registered FixError function to allow the auth module to insert it's challenge.
+     * \retval CRED_ERROR	ERROR in the auth module. Cannot determine request direction.
+     * \retval CRED_LOOKUP	The auth module needs to send data to an external helper.
+     *				Squid will prepare for a callback on the request and call the AUTHSSTART function.
+     * \retval CRED_VALID	The auth module has all the information it needs to perform the authentication
+     *				and provide a succeed/fail result.
+     * \retval CRED_CHALLENGE	The auth module needs to send a new challenge to the request originator.
+     *				Squid will return the appropriate status code (401 or 407) and call the registered
+     *				FixError function to allow the auth module to insert it's challenge.
      */
-    int direction();
+    Direction direction();
 
     /**
      * Used by squid to determine whether the auth scheme has successfully authenticated the user request.
      *
      \retval true	User has successfully been authenticated.
      \retval false	Timeouts on cached credentials have occurred or for any reason the credentials are not valid.
      */
     virtual int authenticated() const = 0;
+
+    /**
+     * Check a auth_user pointer for validity.
+     * Does not check passwords, just data sensability. Broken or Unknown auth_types are not valid for use...
+     *
+     * \retval false    User credentials are missing.
+     * \retval false    User credentials use an unknown scheme type.
+     * \retval false    User credentials are broken for their scheme.
+     *
+     * \retval true	User credentials exist and may be able to authenticate.
+     */
+    bool valid() const;
+
     virtual void authenticate(HttpRequest * request, ConnStateData * conn, http_hdr_type type) = 0;
-    /* template method */
-    virtual int module_direction() = 0;
-    virtual void addHeader(HttpReply * rep, int accel);
-    virtual void addTrailer(HttpReply * rep, int accel);
+
+    /* template method - what needs to be done next? advertise schemes, challenge, handle error, nothing? */
+    virtual Direction module_direction() = 0;
+
+    /* add the [Proxy-]Authentication-Info header */
+    virtual void addAuthenticationInfoHeader(HttpReply * rep, int accel);
+
+    /* add the [Proxy-]Authentication-Info trailer */
+    virtual void addAuthenticationInfoTrailer(HttpReply * rep, int accel);
+
     virtual void onConnectionClose(ConnStateData *);
 
     /**
      * Called when squid is ready to put the request on hold and wait for a callback from the auth module
      * when the auth module has performed it's external activities.
      *
-     \param handler	Handler to process the callback when its run
-     \param data	CBDATA for handler
+     * \param handler	Handler to process the callback when its run
+     * \param data	CBDATA for handler
      */
-    virtual void module_start(RH *handler, void *data) = 0;
+    virtual void module_start(AUTHCB *handler, void *data) = 0;
 
-    virtual AuthUser *user() {return _auth_user;}
+    // User credentials object this UserRequest is managing
+    virtual User::Pointer user() {return _auth_user;}
+    virtual const User::Pointer user() const {return _auth_user;}
+    virtual void user(User::Pointer aUser) {_auth_user=aUser;}
 
-    virtual const AuthUser *user() const {return _auth_user;}
-
-    virtual void user(AuthUser *aUser) {_auth_user=aUser;}
-
-    static auth_acl_t tryToAuthenticateAndSetAuthUser(AuthUserRequest **, http_hdr_type, HttpRequest *, ConnStateData *, IpAddress &);
-    static void addReplyAuthHeader(HttpReply * rep, AuthUserRequest * auth_user_request, HttpRequest * request, int accelerated, int internal);
+    /**
+     * Locate user credentials in one of several locations. Begin authentication if needed.
+     *
+     * Credentials may be found in one of the following locations (listed by order of preference):
+     * - the source passed as parameter aUR
+     * - cached in the HttpRequest parameter from a previous authentication of this request
+     * - cached in the ConnStateData paremeter from a previous authentication of this connection
+     *   (only applies to some situations. ie NTLM, Negotiate, Kerberos auth schemes,
+     *    or decrypted SSL requests from inside an authenticated CONNECT tunnel)
+     * - cached in the user credentials cache from a previous authentication of the same credentials
+     *   (only applies to cacheable authentication methods, ie Basic auth)
+     * - new credentials created from HTTP headers in this request
+     *
+     * The found credentials are returned in aUR and if successfully authenticated
+     * may now be cached in one or more of the above locations.
+     *
+     * \return Some AUTH_ACL_* state
+     */
+    static AuthAclState tryToAuthenticateAndSetAuthUser(UserRequest::Pointer *aUR, http_hdr_type, HttpRequest *, ConnStateData *, Ip::Address &);
 
-    AuthUserRequest();
+    /// Add the appropriate [Proxy-]Authenticate header to the given reply
+    static void addReplyAuthHeader(HttpReply * rep, UserRequest::Pointer auth_user_request, HttpRequest * request, int accelerated, int internal);
 
-    virtual ~AuthUserRequest();
-    void *operator new(size_t byteCount);
-    void operator delete(void *address);
-
-    void start( RH * handler, void *data);
+    void start(AUTHCB *handler, void *data);
     char const * denyMessage(char const * const default_message = NULL);
 
     /** Possibly overrideable in future */
     void setDenyMessage(char const *);
 
     /** Possibly overrideable in future */
     char const * getDenyMessage();
 
-    size_t refCount() const;
-    void _lock();            /**< \note please use AUTHUSERREQUESTLOCK()   */
-    void _unlock();          /**< \note please use AUTHUSERREQUESTUNLOCK() */
-
     /**
      * Squid does not make assumptions about where the username is stored.
      * This function must return a pointer to a NULL terminated string to be used in logging the request.
      * The string should NOT be allocated each time this function is called.
      *
      \retval NULL	No username/usercode is known.
      \retval *		Null-terminated username string.
      */
     char const *username() const;
 
-    AuthScheme *scheme() const;
+    Scheme::Pointer scheme() const;
 
     virtual const char * connLastHeader();
 
 private:
 
-    static auth_acl_t authenticate(AuthUserRequest ** auth_user_request, http_hdr_type headertype, HttpRequest * request, ConnStateData * conn, IpAddress &src_addr);
+    static AuthAclState authenticate(UserRequest::Pointer * auth_user_request, http_hdr_type headertype, HttpRequest * request, ConnStateData * conn, Ip::Address &src_addr);
 
     /** return a message on the 407 error pages */
     char *message;
 
-    /** how many 'processes' are working on this data */
-    size_t references;
-
     /**
      * We only attempt authentication once per http request. This
      * is to allow multiple auth acl references from different _access areas
      * when using connection based authentication
      */
-    auth_acl_t lastReply;
+    AuthAclState lastReply;
 };
 
-/* AuthUserRequest */
+} // namespace Auth
 
-/**
- \ingroup AuthAPI
- \deprecated Use AuthUserRequest::refCount() instead.
- */
-extern size_t authenticateRequestRefCount (AuthUserRequest *);
+/* AuthUserRequest */
 
 /// \ingroup AuthAPI
-extern void authenticateFixHeader(HttpReply *, AuthUserRequest *, HttpRequest *, int, int);
+extern void authenticateFixHeader(HttpReply *, Auth::UserRequest::Pointer, HttpRequest *, int, int);
 /// \ingroup AuthAPI
-extern void authenticateAddTrailer(HttpReply *, AuthUserRequest *, HttpRequest *, int);
+extern void authenticateAddTrailer(HttpReply *, Auth::UserRequest::Pointer, HttpRequest *, int);
 
 /// \ingroup AuthAPI
-extern void authenticateAuthUserRequestRemoveIp(AuthUserRequest *, IpAddress const &);
-/// \ingroup AuthAPI
-extern void authenticateAuthUserRequestClearIp(AuthUserRequest *);
+extern void authenticateAuthUserRequestRemoveIp(Auth::UserRequest::Pointer, Ip::Address const &);
 /// \ingroup AuthAPI
-extern int authenticateAuthUserRequestIPCount(AuthUserRequest *);
+extern void authenticateAuthUserRequestClearIp(Auth::UserRequest::Pointer);
 /// \ingroup AuthAPI
-/// \deprecated Use AuthUserRequest::direction() instead.
-extern int authenticateDirection(AuthUserRequest *);
+extern int authenticateAuthUserRequestIPCount(Auth::UserRequest::Pointer);
 
 /// \ingroup AuthAPI
-/// See AuthUserRequest::authenticated()
-extern int authenticateUserAuthenticated(AuthUserRequest *);
-/// \ingroup AuthAPI
-extern int authenticateValidateUser(AuthUserRequest *);
-
-/// \todo Drop dead code? or make a debugging option.
-#if 0
-#define AUTHUSERREQUESTUNLOCK(a,b) if(a){(a)->_unlock();debugs(0,0,HERE << "auth_user_request " << a << " was unlocked for " << b); (a)=NULL;}
-#define AUTHUSERREQUESTLOCK(a,b) { (a)->_lock(); debugs(0,0,HERE << "auth_user_request " << a << " was locked for " << b); }
-#endif
-#define AUTHUSERREQUESTUNLOCK(a,b) if(a){(a)->_unlock();(a)=NULL;}
-#define AUTHUSERREQUESTLOCK(a,b) (a)->_lock()
-
+/// See Auth::UserRequest::authenticated()
+extern int authenticateUserAuthenticated(Auth::UserRequest::Pointer);
 
+#endif /* USE_AUTH */
 #endif /* SQUID_AUTHUSERREQUEST_H */
