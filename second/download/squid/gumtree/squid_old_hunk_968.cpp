 */

// See AsyncJobs.dox for details.

/// \ingroup AsyncJobAPI
/// Base class for all asynchronous jobs
class AsyncJob
{
public:
    typedef CbcPointer<AsyncJob> Pointer;

public:
    AsyncJob(const char *aTypeName);
    virtual ~AsyncJob();

    virtual void *toCbdata() = 0;

    /// starts a freshly created job (i.e., makes the job asynchronous)
    static Pointer Start(AsyncJob *job);

protected:
    // XXX: temporary method to replace "delete this" in jobs-in-transition.
    // Will be replaced with calls to mustStop() when transition is complete.
