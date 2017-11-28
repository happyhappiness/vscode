{
    cfg->parsePoolAccess(LegacyParser);
}

#endif

#if USE_DELAY_POOLS
#include "ClientDelayConfig.h"
/* do nothing - free_client_delay_pool_count is the magic free function.
 * this is why client_delay_pool_count isn't just marked TYPE: u_short
 */

#define free_client_delay_pool_access(X)
#define free_client_delay_pool_rates(X)
#define dump_client_delay_pool_access(X, Y, Z)
#define dump_client_delay_pool_rates(X, Y, Z)

static void
free_client_delay_pool_count(ClientDelayConfig * cfg)
{
    cfg->freePoolCount();
}

static void
dump_client_delay_pool_count(StoreEntry * entry, const char *name, ClientDelayConfig &cfg)
{
    cfg.dumpPoolCount (entry, name);
}

static void
parse_client_delay_pool_count(ClientDelayConfig * cfg)
{
    cfg->parsePoolCount();
}

static void
parse_client_delay_pool_rates(ClientDelayConfig * cfg)
{
    cfg->parsePoolRates();
}

static void
parse_client_delay_pool_access(ClientDelayConfig * cfg)
{
    cfg->parsePoolAccess(LegacyParser);
}
#endif

#if USE_HTTP_VIOLATIONS
static void
dump_http_header_access(StoreEntry * entry, const char *name, const HeaderManglers *manglers)
{
    if (manglers)
        manglers->dumpAccess(entry, name);
}

static void
parse_http_header_access(HeaderManglers **pm)
{
    char *t = NULL;

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, 0, "parse_http_header_access: missing header name.");
        return;
    }

    if (!*pm)
        *pm = new HeaderManglers;
    HeaderManglers *manglers = *pm;
    header_mangler *mangler = manglers->track(t);
    assert(mangler);
    parse_acl_access(&mangler->access_list);
}

static void
free_HeaderManglers(HeaderManglers **pm)
{
    // we delete the entire http_header_* mangler configuration at once
    if (const HeaderManglers *manglers = *pm) {
        delete manglers;
        *pm = NULL;
    }
}

static void
dump_http_header_replace(StoreEntry * entry, const char *name, const HeaderManglers *manglers)
{
    if (manglers)
        manglers->dumpReplacement(entry, name);
}

static void
parse_http_header_replace(HeaderManglers **pm)
{
    char *t = NULL;

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, 0, "parse_http_header_replace: missing header name.");
        return;
    }

    const char *value = t + strlen(t) + 1;

    if (!*pm)
        *pm = new HeaderManglers;
    HeaderManglers *manglers = *pm;
    manglers->setReplacement(t, value);
}

#endif

static void
dump_cachedir(StoreEntry * entry, const char *name, SquidConfig::_cacheSwap swap)
{
    SwapDir *s;
    int i;
    assert (entry);

    for (i = 0; i < swap.n_configured; ++i) {
        s = dynamic_cast<SwapDir *>(swap.swapDirs[i].getRaw());
        if (!s) continue;
        storeAppendPrintf(entry, "%s %s %s", name, s->type(), s->path);
        s->dump(*entry);
        storeAppendPrintf(entry, "\n");
    }
