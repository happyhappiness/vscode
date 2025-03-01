 * idle connections across the collection.
 */
class PconnPool
{

public:
    PconnPool(const char *aDescription, const CbcPointer<PeerPoolMgr> &aMgr);
    ~PconnPool();

    void moduleInit();
    void push(const Comm::ConnectionPointer &serverConn, const char *domain);

    /**
     * Returns either a pointer to a popped connection to dest or nil.
     * Closes the connection before returning its pointer unless keepOpen.
     *
     * A caller with a non-retriable transaction should set keepOpen to false
     * and call pop() anyway, even though the caller does not want a pconn.
     * This forces us to close an available persistent connection, avoiding
     * creating a growing number of open connections when many transactions
     * create (and push) persistent connections but are not retriable and,
     * hence, do not need to pop a connection.
     */
    Comm::ConnectionPointer pop(const Comm::ConnectionPointer &dest, const char *domain, bool keepOpen);
    void count(int uses);
    void dumpHist(StoreEntry *e) const;
    void dumpHash(StoreEntry *e) const;
    void unlinkList(IdleConnList *list);
    void noteUses(int uses);
    /// closes any n connections, regardless of their destination
    void closeN(int n);
    int count() const { return theCount; }
    void noteConnectionAdded() { ++theCount; }
    void noteConnectionRemoved() { assert(theCount > 0); --theCount; }

    // sends an async message to the pool manager, if any
    void notifyManager(const char *reason);

private:

    static const char *key(const Comm::ConnectionPointer &destLink, const char *domain);

    int hist[PCONN_HIST_SZ];
    hash_table *table;
    const char *descr;
    CbcPointer<PeerPoolMgr> mgr; ///< optional pool manager (for notifications)
    int theCount; ///< the number of pooled connections
};

class StoreEntry;
class PconnPool;

