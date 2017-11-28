
/**
 * Async-opener of a Comm connection.
 */
class ConnOpener : public AsyncJob
{
protected:
    virtual void start();
    virtual void swanSong();

public:
    void noteAbort() { mustStop("externally aborted"); }

    typedef CbcPointer<ConnOpener> Pointer;

