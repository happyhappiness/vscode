 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#include "squid.h"
#include "CacheManager.h"
#include "Store.h"
#include "comm.h"
#include "pconn.h"
#include "fde.h"

#define PCONN_FDS_SZ	8	/* pconn set size, increase for better memcache hit rate */

static MemAllocator *pconn_fds_pool = NULL;
PconnModule * PconnModule::instance = NULL;
CBDATA_CLASS_INIT(IdleConnList);

/* ========== IdleConnList ============================================ */

IdleConnList::IdleConnList(const char *key, PconnPool *thePool) : parent(thePool)
{
    hash.key = xstrdup(key);
    nfds_alloc = PCONN_FDS_SZ;
    nfds = 0;
    fds = (int *)pconn_fds_pool->alloc();
}

IdleConnList::~IdleConnList()
{

    parent->unlinkList(this);

    if (nfds_alloc == PCONN_FDS_SZ)
        pconn_fds_pool->free(fds);
    else
        xfree(fds);

    xfree(hash.key);
}

int
IdleConnList::findFDIndex (int fd)
{
    int index;

    for (index = nfds - 1; index >= 0; --index) {
        if (fds[index] == fd)
            return index;
    }

    return -1;
}

void
IdleConnList::removeFD(int fd)
{
    int index = findFDIndex(fd);
    if (index < 0) {
        debugs(48, 2, "IdleConnList::removeFD: FD " << fd << " NOT FOUND!");
        return;
    }
    debugs(48, 3, "IdleConnList::removeFD: found FD " << fd << " at index " << index);

    for (; index < nfds - 1; index++)
        fds[index] = fds[index + 1];

    if (--nfds == 0) {
        debugs(48, 3, "IdleConnList::removeFD: deleting " << hashKeyStr(&hash));
        delete this;
    }
}

void
IdleConnList::clearHandlers(int fd)
{
    comm_read_cancel(fd, IdleConnList::read, this);
    commSetTimeout(fd, -1, NULL, NULL);
}

void
IdleConnList::push(int fd)
{
    if (nfds == nfds_alloc) {
        debugs(48, 3, "IdleConnList::push: growing FD array");
        nfds_alloc <<= 1;
        int *old = fds;
        fds = (int *)xmalloc(nfds_alloc * sizeof(int));
        xmemcpy(fds, old, nfds * sizeof(int));

        if (nfds == PCONN_FDS_SZ)
            pconn_fds_pool->free(old);
        else
            xfree(old);
    }

    fds[nfds++] = fd;
    comm_read(fd, fakeReadBuf, sizeof(fakeReadBuf), IdleConnList::read, this);
    commSetTimeout(fd, Config.Timeout.pconn, IdleConnList::timeout, this);
}

/*
 * XXX this routine isn't terribly efficient - if there's a pending
 * read event (which signifies the fd will close in the next IO loop!)
 * we ignore the FD and move onto the next one. This means, as an example,
 * if we have a lot of FDs open to a very popular server and we get a bunch
 * of requests JUST as they timeout (say, it shuts down) we'll be wasting
 * quite a bit of CPU. Just keep it in mind.
 */
int
IdleConnList::findUseableFD()
{
    assert(nfds);

    for (int i=nfds-1; i>=0; i--) {
        if (!comm_has_pending_read_callback(fds[i])) {
            return fds[i];
        }
    }

    return -1;
}

void
IdleConnList::read(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    debugs(48, 3, "IdleConnList::read: " << len << " bytes from FD " << fd);

    if (flag == COMM_ERR_CLOSING) {
        /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */
        return;
    }

    IdleConnList *list = (IdleConnList *) data;
    list->removeFD(fd);	/* might delete list */
    comm_close(fd);
}

void
IdleConnList::timeout(int fd, void *data)
{
    debugs(48, 3, "IdleConnList::timeout: FD " << fd);
    IdleConnList *list = (IdleConnList *) data;
    list->removeFD(fd);	/* might delete list */
    comm_close(fd);
}

/* ========== PconnPool PRIVATE FUNCTIONS ============================================ */

const char *
PconnPool::key(const char *host, unsigned short port, const char *domain, IpAddress &client_address)
{
    LOCAL_ARRAY(char, buf, SQUIDHOSTNAMELEN * 3 + 10);
    char ntoabuf[MAX_IPSTRLEN];

    if (domain && !client_address.IsAnyAddr())
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d-%s/%s", host, (int) port, client_address.NtoA(ntoabuf,MAX_IPSTRLEN), domain);
    else if (domain && client_address.IsAnyAddr())
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d/%s", host, (int) port, domain);
    else if ((!domain) && !client_address.IsAnyAddr())
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d-%s", host, (int) port, client_address.NtoA(ntoabuf,MAX_IPSTRLEN));
    else
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d", host, (int) port);

    debugs(48,6,"PconnPool::key(" << (host?host:"(no host!)") << "," << port << "," << (domain?domain:"(no domain)") << "," << client_address << "is {" << buf << "}" );
    return buf;
}

void
PconnPool::dumpHist(StoreEntry * e)
{
    int i;
    storeAppendPrintf(e,
                      "%s persistent connection counts:\n"
                      "\n"
                      "\treq/\n"
                      "\tconn      count\n"
                      "\t----  ---------\n",
                      descr);

    for (i = 0; i < PCONN_HIST_SZ; i++) {
        if (hist[i] == 0)
            continue;

        storeAppendPrintf(e, "\t%4d  %9d\n", i, hist[i]);
    }
}

void
PconnPool::dumpHash(StoreEntry *e)
{
    int i;
    hash_link *walker = NULL;
    hash_table *hid = table;
    hash_first(hid);

    for (i = 0, walker = hid->next; walker; walker = hash_next(hid)) {
        storeAppendPrintf(e, "\t item %5d: %s\n", i++, (char *)(walker->key));
    }
}

/* ========== PconnPool PUBLIC FUNCTIONS ============================================ */

PconnPool::PconnPool(const char *aDescr) : table(NULL), descr(aDescr)
{
    int i;
    table = hash_create((HASHCMP *) strcmp, 229, hash_string);

    for (i = 0; i < PCONN_HIST_SZ; i++)
        hist[i] = 0;

    PconnModule::GetInstance()->add(this);
}

PconnPool::~PconnPool()
{
    descr = NULL;
    hashFreeMemory(table);
}

void
PconnPool::push(int fd, const char *host, unsigned short port, const char *domain, IpAddress &client_address)
{
    IdleConnList *list;
    const char *aKey;
    LOCAL_ARRAY(char, desc, FD_DESC_SZ);

    if (fdUsageHigh()) {
        debugs(48, 3, "PconnPool::push: Not many unused FDs");
        comm_close(fd);
        return;
    } else if (shutting_down) {
        comm_close(fd);
        debugs(48, 3, "PconnPool::push: Squid is shutting down. Refusing to do anything");
        return;
    }

    aKey = key(host, port, domain, client_address);

    list = (IdleConnList *) hash_lookup(table, aKey);

    if (list == NULL) {
        list = new IdleConnList(aKey, this);
        debugs(48, 3, "PconnPool::push: new IdleConnList for {" << hashKeyStr(&list->hash) << "}" );
        hash_join(table, &list->hash);
    } else {
        debugs(48, 3, "PconnPool::push: found IdleConnList for {" << hashKeyStr(&list->hash) << "}" );
    }

    list->push(fd);

    assert(!comm_has_incomplete_write(fd));
    snprintf(desc, FD_DESC_SZ, "%s idle connection", host);
    fd_note(fd, desc);
    debugs(48, 3, "PconnPool::push: pushed FD " << fd << " for " << aKey);
}

/**
 * Return a pconn fd for host:port if available and retriable.
 * Otherwise, return -1.
 *
 * We close available persistent connection if the caller transaction is not
 * retriable to avoid having a growing number of open connections when many
 * transactions create persistent connections but are not retriable.
 */
int
PconnPool::pop(const char *host, unsigned short port, const char *domain, IpAddress &client_address, bool isRetriable)
{
    const char * aKey = key(host, port, domain, client_address);

    IdleConnList *list = (IdleConnList *)hash_lookup(table, aKey);
    if (list == NULL) {
        debugs(48, 3, "PconnPool::pop: lookup for key {" << aKey << "} failed.");
        return -1;
    } else {
        debugs(48, 3, "PconnPool::pop: found " << hashKeyStr(&list->hash) << (isRetriable?"(to use)":"(to kill)") );
    }

    int fd = list->findUseableFD(); // search from the end. skip pending reads.

    if (fd >= 0) {
        list->clearHandlers(fd);
        list->removeFD(fd);	/* might delete list */

        if (!isRetriable) {
            comm_close(fd);
            return -1;
        }
    }

    return fd;
}

void
PconnPool::unlinkList(IdleConnList *list) const
{
    hash_remove_link(table, &list->hash);
}

void
PconnPool::count(int uses)
{
    if (uses >= PCONN_HIST_SZ)
        uses = PCONN_HIST_SZ - 1;

    hist[uses]++;
}

/* ========== PconnModule ============================================ */

/*
 * This simple class exists only for the cache manager
 */

PconnModule::PconnModule() : pools(NULL), poolCount(0)
{
    pools = (PconnPool **) xcalloc(MAX_NUM_PCONN_POOLS, sizeof(*pools));
    pconn_fds_pool = memPoolCreate("pconn_fds", PCONN_FDS_SZ * sizeof(int));
    debugs(48, 0, "persistent connection module initialized");
    registerWithCacheManager();
}

PconnModule *
PconnModule::GetInstance()
