virtual HttpReply *_lock() {
        return static_cast<HttpReply*>(HttpMsg::_lock());
    }