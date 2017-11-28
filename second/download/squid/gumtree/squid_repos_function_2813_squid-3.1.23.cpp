virtual HttpRequest *_lock() {
        return static_cast<HttpRequest*>(HttpMsg::_lock());
    }