#if USE_OPENSSL
namespace Ssl
{
class ServerBump;
}
#endif
/**
 * Manages a connection to a client.
 *
 * Multiple requests (up to pipeline_prefetch) can be pipelined. This object is responsible for managing
 * which one is currently being fulfilled and what happens to the queue if the current one
 * causes the client connection to be closed early.
 *
 * Act as a manager for the connection and passes data in buffer to the current parser.
 * the parser has ambiguous scope at present due to being made from global functions
 * I believe this object uses the parser to identify boundaries and kick off the
 * actual HTTP request handling objects (ClientSocketContext, ClientHttpRequest, HttpRequest)
 *
 * If the above can be confirmed accurate we can call this object PipelineManager or similar
 */
class ConnStateData : public BodyProducer, public HttpControlMsgSink, public RegisteredRunner
{

public:
    explicit ConnStateData(const MasterXaction::Pointer &xact);
    virtual ~ConnStateData();

    void readSomeData();
    bool areAllContextsForThisConnection() const;
    void freeAllContexts();
    void notifyAllContexts(const int xerrno); ///< tell everybody about the err
    /// Traffic parsing
    bool clientParseRequests();
    void readNextRequest();

    // In v3.5, usually called via ClientSocketContext::keepaliveNextRequest().
    /// try to make progress on a transaction or read more I/O
    void kick();

    ClientSocketContext::Pointer getCurrentContext() const;
    void addContextToQueue(ClientSocketContext * context);
    int getConcurrentRequestCount() const;
    bool isOpen() const;

    // HttpControlMsgSink API
    virtual void sendControlMsg(HttpControlMsg msg);

    // Client TCP connection details from comm layer.
    Comm::ConnectionPointer clientConnection;

    class In {
    public:
        In();
        ~In();
        void maybeMakeSpaceAvailable();

        ChunkedCodingParser *bodyParser; ///< parses chunked request body
        SBuf buf;
    } in;

    /** number of body bytes we need to comm_read for the "current" request
     *
     * \retval 0         We do not need to read any [more] body bytes
     * \retval negative  May need more but do not know how many; could be zero!
     * \retval positive  Need to read exactly that many more body bytes
