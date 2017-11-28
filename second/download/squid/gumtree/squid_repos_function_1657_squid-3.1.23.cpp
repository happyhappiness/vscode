void mayUseConnection(bool aBool) {
        mayUseConnection_ = aBool;
        debug (33,3)("ClientSocketContext::mayUseConnection: This %p marked %d\n",
                     this, aBool);
    }