int sync() override {
        std::streamsize pending(pptr() - pbase());
        lowAppend(pbase(), pending);
        buf_.flush();
        return 0;
    }