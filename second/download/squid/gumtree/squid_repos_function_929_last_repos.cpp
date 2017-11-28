void clear() {
        scheme_=AnyP::PROTO_NONE;
        hostIsNumeric_ = false;
        *host_ = 0;
        hostAddr_.setEmpty();
        port_ = 0;
        touch();
    }