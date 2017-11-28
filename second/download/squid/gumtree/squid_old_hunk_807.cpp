#include "ip/QosConfig.h"
#include "ip/tools.h"
#include "MemObject.h"
#include "mgr/Registration.h"
#include "neighbors.h"
#include "pconn.h"
#include "PeerSelectState.h"
#include "SquidConfig.h"
#include "SquidTime.h"
#include "Store.h"
#include "StoreClient.h"
#include "urn.h"
#include "whois.h"
#if USE_SSL
#include "ssl/cert_validate_message.h"
#include "ssl/Config.h"
#include "ssl/helper.h"
#include "ssl/support.h"
#include "ssl/ErrorDetail.h"
#include "ssl/ServerBump.h"
#endif
#if HAVE_ERRNO_H
#include <errno.h>
#endif

static PSC fwdPeerSelectionCompleteWrapper;
static CLCB fwdServerClosedWrapper;
#if USE_SSL
static PF fwdNegotiateSSLWrapper;
#endif
static CNCB fwdConnectDoneWrapper;

static OBJH fwdStats;

#define MAX_FWD_STATS_IDX 9
static int FwdReplyCodes[MAX_FWD_STATS_IDX + 1][Http::scInvalidHeader + 1];

static PconnPool *fwdPconnPool = new PconnPool("server-side");
CBDATA_CLASS_INIT(FwdState);

void
FwdState::abort(void* d)
{
    FwdState* fwd = (FwdState*)d;
    Pointer tmp = fwd; // Grab a temporary pointer to keep the object alive during our scope.

    if (Comm::IsConnOpen(fwd->serverConnection())) {
        comm_remove_close_handler(fwd->serverConnection()->fd, fwdServerClosedWrapper, fwd);
        debugs(17, 3, HERE << "store entry aborted; closing " <<
               fwd->serverConnection());
        fwd->serverConnection()->close();
    } else {
        debugs(17, 7, HERE << "store entry aborted; no connection to close");
    }
    fwd->serverDestinations.clean();
    fwd->self = NULL;
}

/**** PUBLIC INTERFACE ********************************************************/

FwdState::FwdState(const Comm::ConnectionPointer &client, StoreEntry * e, HttpRequest * r, const AccessLogEntryPointer &alp):
        al(alp)
{
    debugs(17, 2, HERE << "Forwarding client request " << client << ", url=" << e->url() );
    entry = e;
    clientConn = client;
    request = r;
    HTTPMSGLOCK(request);
    pconnRace = raceImpossible;
    start_t = squid_curtime;
    serverDestinations.reserve(Config.forward_max_tries);
    e->lock();
    EBIT_SET(e->flags, ENTRY_FWD_HDR_WAIT);
}

// Called once, right after object creation, when it is safe to set self
void FwdState::start(Pointer aSelf)
{
