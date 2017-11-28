int sync() {
        std::streamsize pending(pptr() - pbase());

        if (pending)
            theEntry->append(pbase(), pending);

        theEntry->flush();

        return 0;
    }