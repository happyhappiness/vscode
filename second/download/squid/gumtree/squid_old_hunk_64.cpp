
/* The functions in this file handle authentication.
 * They DO NOT perform access control or auditing.
 * See acl.c for access control and client_side.c for auditing */


#include "squid.h"
#include "auth_basic.h"
#include "auth/Gadgets.h"
#include "CacheManager.h"
#include "Store.h"
#include "HttpReply.h"
#include "basicScheme.h"
#include "rfc1738.h"
#include "wordlist.h"
#include "SquidTime.h"

static void
authenticateStateFree(AuthenticateStateData * r)
{
    cbdataFree(r);
}

/* Basic Scheme */

static HLPCB authenticateBasicHandleReply;
static AUTHSSTATS authenticateBasicStats;

static helper *basicauthenticators = NULL;

static AuthBasicConfig basicConfig;

static int authbasic_initialised = 0;


/*
 *
 * Public Functions
 *
 */

/* internal functions */

/* TODO: move to basicScheme.cc - after all per request and user functions are moved out */
void
basicScheme::done()
{
    /* TODO: this should be a Config call. */

    if (basicauthenticators)
        helperShutdown(basicauthenticators);

    authbasic_initialised = 0;

    if (!shutting_down)
        return;

    if (basicauthenticators)
        helperFree(basicauthenticators);

    basicauthenticators = NULL;

    /* XXX Reinstate auth shutdown for dynamic schemes? */
    debugs(29, DBG_CRITICAL, HERE << "Basic authentication Shutdown.");
}

bool
AuthBasicConfig::active() const
{
    return authbasic_initialised == 1;
}

bool
AuthBasicConfig::configured() const
{
    if ((authenticate != NULL) && (authenticateChildren != 0) &&
            (basicAuthRealm != NULL)) {
        debugs(29, 9, HERE << "returning configured");
        return true;
    }

    debugs(29, 9, HERE << "returning unconfigured");
    return false;
}

const char *
AuthBasicConfig::type() const
{
    return basicScheme::GetInstance().type();
}

AuthBasicUserRequest::AuthBasicUserRequest()
{}

AuthBasicUserRequest::~AuthBasicUserRequest()
{}


bool
BasicUser::authenticated() const
{
    if ((flags.credentials_ok == 1) && (credentials_checkedtime + basicConfig.credentialsTTL > squid_curtime))
        return true;

    debugs(29, 4, "User not authenticated or credentials need rechecking.");

    return false;
}

int
AuthBasicUserRequest::authenticated() const
{
    BasicUser const *basic_auth = dynamic_cast<BasicUser const *>(user());

    if (basic_auth && basic_auth->authenticated())
        return 1;

    return 0;
}

/* log a basic user in
 */
void
AuthBasicUserRequest::authenticate(HttpRequest * request, ConnStateData * conn, http_hdr_type type)
{
    assert(user() != NULL);

    basic_data *basic_auth = dynamic_cast<BasicUser *>(user());

    /* if the password is not ok, do an identity */

    if (!basic_auth || basic_auth->flags.credentials_ok != 1)
        return;

    /* are we about to recheck the credentials externally? */
    if ((basic_auth->credentials_checkedtime + basicConfig.credentialsTTL) <= squid_curtime) {
        debugs(29, 4, "authBasicAuthenticate: credentials expired - rechecking");
        return;
    }

    /* we have been through the external helper, and the credentials haven't expired */
    debugs(29, 9, "authenticateBasicAuthenticateuser: user '" << basic_auth->username() << "' authenticated");

    /* Decode now takes care of finding the AuthUser struct in the cache */
    /* after external auth occurs anyway */
    basic_auth->expiretime = current_time.tv_sec;

    return;
}

int
AuthBasicUserRequest::module_direction()
{
    /* null auth_user is checked for by authenticateDirection */
    basic_data *basic_auth = dynamic_cast<BasicUser *>(user());
    assert (basic_auth);

    switch (basic_auth->flags.credentials_ok) {

    case 0:			/* not checked */
        return -1;

    case 1:			/* checked & ok */

        if (basic_auth->credentials_checkedtime + basicConfig.credentialsTTL <= squid_curtime)
            return -1;

        return 0;

    case 2:			/* paused while waiting for a username:password check on another request */
        return -1;

    case 3:			/* authentication process failed. */
        return 0;
    }

    return -2;
}

void
AuthBasicConfig::fixHeader(AuthUserRequest *auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (authenticate) {
        debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'Basic realm=\"" << basicAuthRealm << "\"'");
        httpHeaderPutStrf(&rep->header, hdrType, "Basic realm=\"%s\"", basicAuthRealm);
    }
}

/* free any allocated configuration details */
void
AuthBasicConfig::done()
{
    if (authenticate)
        wordlistDestroy(&authenticate);

    if (basicAuthRealm)
        safe_free(basicAuthRealm);
}

BasicUser::~BasicUser()
{
    safe_free(passwd);
    safe_free(cleartext);
}

static void
authenticateBasicHandleReply(void *data, char *reply)
{
    AuthenticateStateData *r = static_cast<AuthenticateStateData *>(data);
    BasicAuthQueueNode *tmpnode;
    char *t = NULL;
    void *cbdata;
    debugs(29, 9, HERE << "{" << (reply ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' ')))
            *t++ = '\0';

        if (*reply == '\0')
            reply = NULL;
    }

    assert(r->auth_user_request != NULL);
    assert(r->auth_user_request->user()->auth_type == AUTH_BASIC);
    basic_data *basic_auth = dynamic_cast<basic_data *>(r->auth_user_request->user());

    assert(basic_auth != NULL);

    if (reply && (strncasecmp(reply, "OK", 2) == 0))
        basic_auth->flags.credentials_ok = 1;
    else {
        basic_auth->flags.credentials_ok = 3;

        if (t && *t)
            r->auth_user_request->setDenyMessage(t);
    }

    basic_auth->credentials_checkedtime = squid_curtime;

    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata, NULL);

    cbdataReferenceDone(r->data);

    while (basic_auth->auth_queue) {
        tmpnode = basic_auth->auth_queue->next;

        if (cbdataReferenceValidDone(basic_auth->auth_queue->data, &cbdata))
            basic_auth->auth_queue->handler(cbdata, NULL);

        xfree(basic_auth->auth_queue);

        basic_auth->auth_queue = tmpnode;
    }

    authenticateStateFree(r);
}

void
AuthBasicConfig::dump(StoreEntry * entry, const char *name, AuthConfig * scheme)
{
    wordlist *list = authenticate;
    storeAppendPrintf(entry, "%s %s", name, "basic");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n");

    storeAppendPrintf(entry, "%s basic realm %s\n", name, basicAuthRealm);
    storeAppendPrintf(entry, "%s basic children %d\n", name, authenticateChildren);
    storeAppendPrintf(entry, "%s basic concurrency %d\n", name, authenticateConcurrency);
    storeAppendPrintf(entry, "%s basic credentialsttl %d seconds\n", name, (int) credentialsTTL);
    storeAppendPrintf(entry, "%s basic casesensitive %s\n", name, casesensitive ? "on" : "off");
}

AuthBasicConfig::AuthBasicConfig()
{
    /* TODO: move into initialisation list */
    authenticateChildren = 5;
    credentialsTTL = 2 * 60 * 60;	/* two hours */
    basicAuthRealm = xstrdup("Squid proxy-caching web server");
}

AuthBasicConfig::~AuthBasicConfig()
{
    safe_free(basicAuthRealm);
}

void
AuthBasicConfig::parse(AuthConfig * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticate)
            wordlistDestroy(&authenticate);

        parse_wordlist(&authenticate);

        requirePathnameExists("auth_param basic program", authenticate->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        parse_int(&authenticateChildren);
    } else if (strcasecmp(param_str, "concurrency") == 0) {
        parse_int(&authenticateConcurrency);
    } else if (strcasecmp(param_str, "realm") == 0) {
        parse_eol(&basicAuthRealm);
    } else if (strcasecmp(param_str, "credentialsttl") == 0) {
        parse_time_t(&credentialsTTL);
    } else if (strcasecmp(param_str, "casesensitive") == 0) {
        parse_onoff(&casesensitive);
