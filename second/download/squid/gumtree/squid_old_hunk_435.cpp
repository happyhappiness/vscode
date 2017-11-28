 */

#include "squid.h"
#include "AccessLogEntry.h"
#include "format/Quoting.h"
#include "format/Token.h"
#include "log/File.h"
#include "log/Formats.h"
#include "SquidTime.h"

void
Log::Format::HttpdCommon(const AccessLogEntry::Pointer &al, Logfile * logfile)
{
    const char *user_auth = ::Format::QuoteUrlEncodeUsername(al->cache.authuser);
    const char *user_ident = ::Format::QuoteUrlEncodeUsername(al->cache.rfc931);

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    logfilePrintf(logfile, "%s %s %s [%s] \"%s %s %s/%d.%d\" %d %" PRId64 " %s%s:%s%s",
