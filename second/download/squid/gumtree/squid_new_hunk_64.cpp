
/* The functions in this file handle authentication.
 * They DO NOT perform access control or auditing.
 * See acl.c for access control and client_side.c for auditing */


#include "squid-old.h"
#include "auth/basic/auth_basic.h"
#include "auth/basic/Scheme.h"
#include "auth/basic/User.h"
#include "auth/basic/UserRequest.h"
#include "auth/Gadgets.h"
#include "auth/State.h"
#include "charset.h"
#include "mgr/Registration.h"
#include "Store.h"
#include "HttpReply.h"
#include "rfc1738.h"
#include "uudecode.h"
#include "wordlist.h"
#include "SquidTime.h"

/* Basic Scheme */
static AUTHSSTATS authenticateBasicStats;

helper *basicauthenticators = NULL;

static int authbasic_initialised = 0;


/*
 *
 * Public Functions
 *
 */

/* internal functions */

bool
Auth::Basic::Config::active() const
{
    return authbasic_initialised == 1;
}

bool
Auth::Basic::Config::configured() const
{
    if ((authenticateProgram != NULL) && (authenticateChildren.n_max != 0) &&
            (basicAuthRealm != NULL)) {
        debugs(29, 9, HERE << "returning configured");
        return true;
    }

    debugs(29, 9, HERE << "returning unconfigured");
    return false;
}

const char *
Auth::Basic::Config::type() const
{
    return Auth::Basic::Scheme::GetInstance()->type();
}

void
Auth::Basic::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (authenticateProgram) {
        debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'Basic realm=\"" << basicAuthRealm << "\"'");
        httpHeaderPutStrf(&rep->header, hdrType, "Basic realm=\"%s\"", basicAuthRealm);
    }
}

void
Auth::Basic::Config::rotateHelpers()
{
    /* schedule closure of existing helpers */
    if (basicauthenticators) {
        helperShutdown(basicauthenticators);
    }

    /* NP: dynamic helper restart will ensure they start up again as needed. */
}

/** shutdown the auth helpers and free any allocated configuration details */
void
Auth::Basic::Config::done()
{
    authbasic_initialised = 0;

    if (basicauthenticators) {
        helperShutdown(basicauthenticators);
    }

    delete basicauthenticators;
    basicauthenticators = NULL;

    if (authenticateProgram)
        wordlistDestroy(&authenticateProgram);

    if (basicAuthRealm)
        safe_free(basicAuthRealm);
}

void
Auth::Basic::Config::dump(StoreEntry * entry, const char *name, Auth::Config * scheme)
{
    wordlist *list = authenticateProgram;
    storeAppendPrintf(entry, "%s %s", name, "basic");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n");

    storeAppendPrintf(entry, "%s basic realm %s\n", name, basicAuthRealm);
    storeAppendPrintf(entry, "%s basic children %d startup=%d idle=%d concurrency=%d\n", name, authenticateChildren.n_max, authenticateChildren.n_startup, authenticateChildren.n_idle, authenticateChildren.concurrency);
    storeAppendPrintf(entry, "%s basic credentialsttl %d seconds\n", name, (int) credentialsTTL);
    storeAppendPrintf(entry, "%s basic casesensitive %s\n", name, casesensitive ? "on" : "off");
}

Auth::Basic::Config::Config() :
        credentialsTTL( 2*60*60 ),
        casesensitive(0),
        utf8(0)
{
    basicAuthRealm = xstrdup("Squid proxy-caching web server");
}

Auth::Basic::Config::~Config()
{
    safe_free(basicAuthRealm);
}

void
Auth::Basic::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("auth_param basic program", authenticateProgram->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        authenticateChildren.parseConfig();
    } else if (strcasecmp(param_str, "realm") == 0) {
        parse_eol(&basicAuthRealm);
    } else if (strcasecmp(param_str, "credentialsttl") == 0) {
        parse_time_t(&credentialsTTL);
    } else if (strcasecmp(param_str, "casesensitive") == 0) {
        parse_onoff(&casesensitive);
