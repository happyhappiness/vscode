 #define SQUID_CLIENTSIDE_H
 
 #include "base/RunnersRegistry.h"
 #include "clientStreamForward.h"
 #include "comm.h"
 #include "helper/forward.h"
+#include "http/forward.h"
 #include "HttpControlMsg.h"
-#include "HttpParser.h"
 #include "ipc/FdNotes.h"
-#include "SBuf.h"
+#include "sbuf/SBuf.h"
+#include "servers/Server.h"
 #if USE_AUTH
 #include "auth/UserRequest.h"
 #endif
 #if USE_OPENSSL
+#include "security/Handshake.h"
 #include "ssl/support.h"
 #endif
 
-#include <iosfwd>
-
-class ConnStateData;
 class ClientHttpRequest;
-class clientStreamNode;
-class ChunkedCodingParser;
-namespace AnyP
-{
-class PortCfg;
-} // namespace Anyp
-
-/**
- * Badly named.
- * This is in fact the processing context for a single HTTP request.
- *
- * Managing what has been done, and what happens next to the data buffer
- * holding what we hope is an HTTP request.
- *
- * Parsing is still a mess of global functions done in conjunction with the
- * real socket controller which generated ClientHttpRequest.
- * It also generates one of us and passes us control from there based on
- * the results of the parse.
- *
- * After that all the request interpretation and adaptation is in our scope.
- * Then finally the reply fetcher is created by this and we get the result
- * back. Which we then have to manage writing of it to the ConnStateData.
- *
- * The socket level management is done by a ConnStateData which owns us.
- * The scope of this objects control over a socket consists of the data
- * buffer received from ConnStateData with an initially unknown length.
- * When that length is known it sets the end bounary of our acces to the
- * buffer.
- *
- * The individual processing actions are done by other Jobs which we
- * kick off as needed.
- *
- * XXX: If an async call ends the ClientHttpRequest job, ClientSocketContext
- * (and ConnStateData) may not know about it, leading to segfaults and
- * assertions like areAllContextsForThisConnection(). This is difficult to fix
- * because ClientHttpRequest lacks a good way to communicate its ongoing
- * destruction back to the ClientSocketContext which pretends to "own" *http.
- */
-class ClientSocketContext : public RefCountable
-{
-
-public:
-    typedef RefCount<ClientSocketContext> Pointer;
-    ClientSocketContext(const Comm::ConnectionPointer &aConn, ClientHttpRequest *aReq);
-    ~ClientSocketContext();
-    bool startOfOutput() const;
-    void writeComplete(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, Comm::Flag errflag);
-    void keepaliveNextRequest();
-
-    Comm::ConnectionPointer clientConnection; /// details about the client connection socket.
-    ClientHttpRequest *http;    /* we pretend to own that job */
-    HttpReply *reply;
-    char reqbuf[HTTP_REQBUF_SZ];
-    Pointer next;
-
-    struct {
-
-        unsigned deferred:1; /* This is a pipelined request waiting for the current object to complete */
-
-        unsigned parsed_ok:1; /* Was this parsed correctly? */
-    } flags;
-    bool mayUseConnection() const {return mayUseConnection_;}
-
-    void mayUseConnection(bool aBool) {
-        mayUseConnection_ = aBool;
-        debugs(33,3, HERE << "This " << this << " marked " << aBool);
-    }
-
-    class DeferredParams
-    {
-
-    public:
-        clientStreamNode *node;
-        HttpReply *rep;
-        StoreIOBuffer queuedBuffer;
-    };
-
-    DeferredParams deferredparams;
-    int64_t writtenToSocket;
-    void pullData();
-    int64_t getNextRangeOffset() const;
-    bool canPackMoreRanges() const;
-    clientStream_status_t socketState();
-    void sendBody(HttpReply * rep, StoreIOBuffer bodyData);
-    void sendStartOfMessage(HttpReply * rep, StoreIOBuffer bodyData);
-    size_t lengthToSend(Range<int64_t> const &available);
-    void noteSentBodyBytes(size_t);
-    void buildRangeHeader(HttpReply * rep);
-    clientStreamNode * getTail() const;
-    clientStreamNode * getClientReplyContext() const;
-    ConnStateData *getConn() const;
-    void connIsFinished();
-    void removeFromConnectionList(ConnStateData * conn);
-    void deferRecipientForLater(clientStreamNode * node, HttpReply * rep, StoreIOBuffer receivedData);
-    bool multipartRangeRequest() const;
-    void registerWithConn();
-    void noteIoError(const int xerrno); ///< update state to reflect I/O error
-
-    /// starts writing 1xx control message to the client
-    void writeControlMsg(HttpControlMsg &msg);
-
-    /// true if 1xx to the user is pending
-    bool controlMsgIsPending() {return cbControlMsgSent != NULL;}
-
-protected:
-    static IOCB WroteControlMsg;
-    void wroteControlMsg(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, Comm::Flag errflag, int xerrno);
-    void doneWithControlMsg();
-
-private:
-    void prepareReply(HttpReply * rep);
-    void packChunk(const StoreIOBuffer &bodyData, MemBuf &mb);
-    void packRange(StoreIOBuffer const &, MemBuf * mb);
-    void deRegisterWithConn();
-    void doClose();
-    void initiateClose(const char *reason);
+class HttpHdrRangeSpec;
 
-    AsyncCall::Pointer cbControlMsgSent; ///< notifies HttpControlMsg Source
-
-    bool mayUseConnection_; /* This request may use the connection. Don't read anymore requests for now */
-    bool connRegistered_;
-
-    CBDATA_CLASS2(ClientSocketContext);
-};
-
-class ConnectionDetail;
 #if USE_OPENSSL
 namespace Ssl
 {
 class ServerBump;
 }
 #endif
