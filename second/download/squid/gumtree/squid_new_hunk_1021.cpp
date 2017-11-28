#if USE_OPENSSL
namespace Ssl
{
class ServerBump;
}
#endif

/**
 * Legacy Server code managing a connection to a client.
 *
 * NP: presents AsyncJob API but does not operate autonomously as a Job.
 *     So Must() is not safe to use.
 *
 * Multiple requests (up to pipeline_prefetch) can be pipelined.
 * This object is responsible for managing which one is currently being
 * fulfilled and what happens to the queue if the current one causes the client
 * connection to be closed early.
 *
 * Act as a manager for the client connection and passes data in buffer to a
 * Parser relevant to the state (message headers vs body) that is being
 * processed.
 *
 * Performs HTTP message processing to kick off the actual HTTP request
 * handling objects (Http::Stream, ClientHttpRequest, HttpRequest).
 *
 * Performs SSL-Bump processing for switching between HTTP and HTTPS protocols.
 *
 * To terminate a ConnStateData close() the client Comm::Connection it is
 * managing, or for graceful half-close use the stopReceiving() or
 * stopSending() methods.
 */
class ConnStateData : public Server, public HttpControlMsgSink, private IndependentRunner
{

public:
    explicit ConnStateData(const MasterXaction::Pointer &xact);
    virtual ~ConnStateData();

    /* ::Server API */
    virtual void receivedFirstByte();
    virtual bool handleReadData();
    virtual void afterClientRead();
    virtual void afterClientWrite(size_t);

    /* HttpControlMsgSink API */
    virtual void sendControlMsg(HttpControlMsg);
    virtual void doneWithControlMsg();

    /// Traffic parsing
    bool clientParseRequests();
    void readNextRequest();

    /// try to make progress on a transaction or read more I/O
    void kick();

    bool isOpen() const;

    Http1::TeChunkedParser *bodyParser; ///< parses HTTP/1.1 chunked request body

    /** number of body bytes we need to comm_read for the "current" request
     *
     * \retval 0         We do not need to read any [more] body bytes
     * \retval negative  May need more but do not know how many; could be zero!
     * \retval positive  Need to read exactly that many more body bytes
