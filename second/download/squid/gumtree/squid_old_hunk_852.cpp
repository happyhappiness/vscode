 * idle connections across the collection.
 */
class PconnPool
{

public:
    PconnPool(const char *);
    ~PconnPool();

    void moduleInit();
    void push(const Comm::ConnectionPointer &serverConn, const char *domain);

    /**
     * Updates destLink to point at an existing open connection if available and retriable.
     * Otherwise, return false.
     *
     * We close available persistent connection if the caller transaction is not
     * retriable to avoid having a growing number of open connections when many
     * transactions create persistent connections but are not retriable.
     */
    Comm::ConnectionPointer pop(const Comm::ConnectionPointer &destLink, const char *domain, bool retriable);
    void count(int uses);
    void dumpHist(StoreEntry *e) const;
    void dumpHash(StoreEntry *e) const;
    void unlinkList(IdleConnList *list);
    void noteUses(int uses);
    void closeN(int n, const Comm::ConnectionPointer &destLink, const char *domain);
    int count() const { return theCount; }
    void noteConnectionAdded() { ++theCount; }
    void noteConnectionRemoved() { assert(theCount > 0); --theCount; }

private:

    static const char *key(const Comm::ConnectionPointer &destLink, const char *domain);

    int hist[PCONN_HIST_SZ];
    hash_table *table;
    const char *descr;
    int theCount; ///< the number of pooled connections
};

class StoreEntry;
class PconnPool;

