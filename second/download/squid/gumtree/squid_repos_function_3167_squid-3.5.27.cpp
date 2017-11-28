int sync() {
        std::streamsize pending(pptr() - pbase());

        if (pending)
            theBuf.append(pbase(), pending);

        return 0;
    }