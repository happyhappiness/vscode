#include "squid-old.h"
#include "HttpRequest.h"
#include "HttpReply.h"
#include "client_side.h"
#if USE_AUTH
#include "auth/UserRequest.h"
#include "auth/AclProxyAuth.h"
#endif
#include "acl/FilledChecklist.h"
#include "comm/Connection.h"
#include "comm/forward.h"

CBDATA_CLASS_INIT(ACLFilledChecklist);

void
ACLFilledChecklist::checkCallback(allow_t answer)
{
    debugs(28, 5, HERE << this << " answer=" << answer);

#if USE_AUTH
    /* During reconfigure, we can end up not finishing call
     * sequences into the auth code */

    if (auth_user_request != NULL) {
        /* the filled_checklist lock */
        auth_user_request = NULL;
        // It might have been connection based
        // In the case of sslBump we need to preserve authentication info
        // XXX: need to re-evaluate this. ACL tests should not be playing with
        // XXX: wider scoped TCP connection state, even if the helper lookup is stuck.
        if (conn() && !conn()->switchedToHttps()) {
            conn()->auth_user_request = NULL;
        }
    }
#endif

    ACLChecklist::checkCallback(answer); // may delete us
}


void *
