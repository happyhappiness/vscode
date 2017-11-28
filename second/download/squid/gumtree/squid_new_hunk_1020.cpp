#define SQUID_CLIENTSIDE_H

#include "base/RunnersRegistry.h"
#include "clientStreamForward.h"
#include "comm.h"
#include "helper/forward.h"
#include "http/forward.h"
#include "HttpControlMsg.h"
#include "ipc/FdNotes.h"
#include "sbuf/SBuf.h"
#include "servers/Server.h"
#if USE_AUTH
#include "auth/UserRequest.h"
#endif
#if USE_OPENSSL
#include "security/Handshake.h"
#include "ssl/support.h"
#endif

class ClientHttpRequest;
class HttpHdrRangeSpec;

#if USE_OPENSSL
namespace Ssl
{
class ServerBump;
}
#endif
