 */

/* The functions in this file handle authentication.
 * They DO NOT perform access control or auditing.
 * See acl.c for access control and client_side.c for auditing */

#include "squid-old.h"
#include "auth/Config.h"
#include "auth/Scheme.h"
#include "auth/UserRequest.h"
#include "auth/User.h"
#include "comm/Connection.h"
#include "HttpReply.h"
#include "HttpRequest.h"

/* Generic Functions */

char const *
Auth::UserRequest::username() const
{
    if (user() != NULL)
        return user()->username();
    else
        return NULL;
}

/**** PUBLIC FUNCTIONS (ALL GENERIC!)  ****/

/* send the initial data to an authenticator module */
void
Auth::UserRequest::start(AUTHCB * handler, void *data)
{
    assert(handler);
    assert(data);
    debugs(29, 9, HERE << "auth_user_request '" << this << "'");
    module_start(handler, data);
}

bool
Auth::UserRequest::valid() const
{
    debugs(29, 9, HERE << "Validating Auth::UserRequest '" << this << "'.");

    if (user() == NULL) {
        debugs(29, 4, HERE << "No associated Auth::User data");
        return false;
    }

    if (user()->auth_type == Auth::AUTH_UNKNOWN) {
        debugs(29, 4, HERE << "Auth::User '" << user() << "' uses unknown scheme.");
        return false;
    }

    if (user()->auth_type == Auth::AUTH_BROKEN) {
        debugs(29, 4, HERE << "Auth::User '" << user() << "' is broken for it's scheme.");
        return false;
    }

    /* any other sanity checks that we need in the future */

    /* finally return ok */
    debugs(29, 5, HERE << "Validated. Auth::UserRequest '" << this << "'.");
    return true;
}

void *
Auth::UserRequest::operator new (size_t byteCount)
{
    fatal("Auth::UserRequest not directly allocatable\n");
    return (void *)1;
}

void
Auth::UserRequest::operator delete (void *address)
{
    fatal("Auth::UserRequest child failed to override operator delete\n");
}

Auth::UserRequest::UserRequest():
        _auth_user(NULL),
        message(NULL),
        lastReply(AUTH_ACL_CANNOT_AUTHENTICATE)
{
    debugs(29, 5, HERE << "initialised request " << this);
}

Auth::UserRequest::~UserRequest()
{
    assert(RefCountCount()==0);
    debugs(29, 5, HERE << "freeing request " << this);

    if (user() != NULL) {
        /* release our references to the user credentials */
        user(NULL);
    }

    safe_free(message);
}

void
Auth::UserRequest::setDenyMessage(char const *aString)
{
    safe_free(message);
    message = xstrdup(aString);
}

char const *
Auth::UserRequest::getDenyMessage()
{
    return message;
}

char const *
Auth::UserRequest::denyMessage(char const * const default_message)
{
    if (this == NULL || getDenyMessage() == NULL) {
        return default_message;
    }

    return getDenyMessage();
}

static void
authenticateAuthUserRequestSetIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address &ipaddr)
{
    Auth::User::Pointer auth_user = auth_user_request->user();

    if (!auth_user)
        return;

    auth_user->addIp(ipaddr);
}

void
authenticateAuthUserRequestRemoveIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address const &ipaddr)
{
    Auth::User::Pointer auth_user = auth_user_request->user();

    if (!auth_user)
        return;

    auth_user->removeIp(ipaddr);
}

void
authenticateAuthUserRequestClearIp(Auth::UserRequest::Pointer auth_user_request)
{
    if (auth_user_request != NULL)
        auth_user_request->user()->clearIp();
}

int
authenticateAuthUserRequestIPCount(Auth::UserRequest::Pointer auth_user_request)
{
    assert(auth_user_request != NULL);
    assert(auth_user_request->user() != NULL);
    return auth_user_request->user()->ipcount;
}


/*
 * authenticateUserAuthenticated: is this auth_user structure logged in ?
 */
int
authenticateUserAuthenticated(Auth::UserRequest::Pointer auth_user_request)
{
    if (auth_user_request == NULL || !auth_user_request->valid())
        return 0;

    return auth_user_request->authenticated();
}

Auth::Direction
Auth::UserRequest::direction()
{
    if (user() == NULL)
        return Auth::CRED_ERROR; // No credentials. Should this be a CHALLENGE instead?

    if (authenticateUserAuthenticated(this))
        return Auth::CRED_VALID;

    return module_direction();
}

void
Auth::UserRequest::addAuthenticationInfoHeader(HttpReply * rep, int accelerated)
{}

void
Auth::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accelerated)
{}

void
Auth::UserRequest::onConnectionClose(ConnStateData *)
{}

const char *
Auth::UserRequest::connLastHeader()
{
    fatal("Auth::UserRequest::connLastHeader should always be overridden by conn based auth schemes");
    return NULL;
}

/*
 * authenticateAuthenticateUser: call the module specific code to
 * log this user request in.
 * Cache hits may change the auth_user pointer in the structure if needed.
 * This is basically a handle approach.
 */
static void
authenticateAuthenticateUser(Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, ConnStateData * conn, http_hdr_type type)
{
    assert(auth_user_request.getRaw() != NULL);

    auth_user_request->authenticate(request, conn, type);
}

static Auth::UserRequest::Pointer
authTryGetUser(Auth::UserRequest::Pointer auth_user_request, ConnStateData * conn, HttpRequest * request)
{
    if (auth_user_request != NULL)
        return auth_user_request;
    else if (request != NULL && request->auth_user_request != NULL)
        return request->auth_user_request;
    else if (conn != NULL)
        return conn->auth_user_request;
    else
        return NULL;
}
