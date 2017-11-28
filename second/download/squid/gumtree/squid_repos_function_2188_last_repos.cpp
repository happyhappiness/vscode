const char * getHost() const {
        return (server.conn != NULL && server.conn->getPeer() ? server.conn->getPeer()->host : request->url.host());
    }