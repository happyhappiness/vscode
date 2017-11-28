
/**
 * Async-opener of a Comm connection.
 */
class ConnOpener : public AsyncJob
{
    CBDATA_CLASS(ConnOpener);

public:
    void noteAbort() { mustStop("externally aborted"); }

    typedef CbcPointer<ConnOpener> Pointer;

