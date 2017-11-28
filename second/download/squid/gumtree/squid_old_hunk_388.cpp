
protected:
    static IOCB WroteControlMsg;
    void wroteControlMsg(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag, int xerrno);

private:
    CBDATA_CLASS(ClientSocketContext);
    void prepareReply(HttpReply * rep);
    void packChunk(const StoreIOBuffer &bodyData, MemBuf &mb);
    void packRange(StoreIOBuffer const &, MemBuf * mb);
    void deRegisterWithConn();
    void doClose();
    void initiateClose(const char *reason);

    AsyncCall::Pointer cbControlMsgSent; ///< notifies HttpControlMsg Source

    bool mayUseConnection_; /* This request may use the connection. Don't read anymore requests for now */
    bool connRegistered_;
};


class ConnectionDetail;

/**
 * Manages a connection to a client.
 *
 * Multiple requests (up to 2) can be pipelined. This object is responsible for managing
 * which one is currently being fulfilled and what happens to the queue if the current one
 * causes the client connection to be closed early.
