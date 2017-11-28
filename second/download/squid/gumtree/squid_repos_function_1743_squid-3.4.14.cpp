void mayUseConnection(bool aBool) {
        mayUseConnection_ = aBool;
        debugs(33,3, HERE << "This " << this << " marked " << aBool);
    }