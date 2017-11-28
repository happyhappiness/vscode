 #if USE_OPENSSL
 namespace Ssl
 {
 class ServerBump;
 }
 #endif
+
 /**
- * Manages a connection to a client.
+ * Legacy Server code managing a connection to a client.
+ *
+ * NP: presents AsyncJob API but does not operate autonomously as a Job.
+ *     So Must() is not safe to use.
+ *
+ * Multiple requests (up to pipeline_prefetch) can be pipelined.
+ * This object is responsible for managing which one is currently being
+ * fulfilled and what happens to the queue if the current one causes the client
+ * connection to be closed early.
+ *
+ * Act as a manager for the client connection and passes data in buffer to a
+ * Parser relevant to the state (message headers vs body) that is being
+ * processed.
  *
- * Multiple requests (up to pipeline_prefetch) can be pipelined. This object is responsible for managing
- * which one is currently being fulfilled and what happens to the queue if the current one
- * causes the client connection to be closed early.
+ * Performs HTTP message processing to kick off the actual HTTP request
+ * handling objects (Http::Stream, ClientHttpRequest, HttpRequest).
  *
- * Act as a manager for the connection and passes data in buffer to the current parser.
- * the parser has ambiguous scope at present due to being made from global functions
- * I believe this object uses the parser to identify boundaries and kick off the
- * actual HTTP request handling objects (ClientSocketContext, ClientHttpRequest, HttpRequest)
+ * Performs SSL-Bump processing for switching between HTTP and HTTPS protocols.
  *
- * If the above can be confirmed accurate we can call this object PipelineManager or similar
+ * To terminate a ConnStateData close() the client Comm::Connection it is
+ * managing, or for graceful half-close use the stopReceiving() or
+ * stopSending() methods.
  */
-class ConnStateData : public BodyProducer, public HttpControlMsgSink, public RegisteredRunner
+class ConnStateData : public Server, public HttpControlMsgSink, private IndependentRunner
 {
 
 public:
     explicit ConnStateData(const MasterXaction::Pointer &xact);
     virtual ~ConnStateData();
 
-    void readSomeData();
-    bool areAllContextsForThisConnection() const;
-    void freeAllContexts();
-    void notifyAllContexts(const int xerrno); ///< tell everybody about the err
+    /* ::Server API */
+    virtual void receivedFirstByte();
+    virtual bool handleReadData();
+    virtual void afterClientRead();
+    virtual void afterClientWrite(size_t);
+
+    /* HttpControlMsgSink API */
+    virtual void sendControlMsg(HttpControlMsg);
+    virtual void doneWithControlMsg();
+
     /// Traffic parsing
     bool clientParseRequests();
     void readNextRequest();
 
-    // In v3.5, usually called via ClientSocketContext::keepaliveNextRequest().
     /// try to make progress on a transaction or read more I/O
     void kick();
 
-    ClientSocketContext::Pointer getCurrentContext() const;
-    void addContextToQueue(ClientSocketContext * context);
-    int getConcurrentRequestCount() const;
     bool isOpen() const;
 
-    // HttpControlMsgSink API
-    virtual void sendControlMsg(HttpControlMsg msg);
-
-    // Client TCP connection details from comm layer.
-    Comm::ConnectionPointer clientConnection;
-
-    class In {
-    public:
-        In();
-        ~In();
-        void maybeMakeSpaceAvailable();
-
-        ChunkedCodingParser *bodyParser; ///< parses chunked request body
-        SBuf buf;
-    } in;
+    Http1::TeChunkedParser *bodyParser; ///< parses HTTP/1.1 chunked request body
 
     /** number of body bytes we need to comm_read for the "current" request
      *
      * \retval 0         We do not need to read any [more] body bytes
      * \retval negative  May need more but do not know how many; could be zero!
      * \retval positive  Need to read exactly that many more body bytes
