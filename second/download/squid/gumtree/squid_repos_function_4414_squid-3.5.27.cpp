static long
squid_bio_ctrl(BIO *table, int cmd, long arg1, void *arg2)
{
    debugs(83, 5, table << ' ' << cmd << '(' << arg1 << ", " << arg2 << ')');

    switch (cmd) {
    case BIO_C_SET_FD: {
        assert(arg2);
        const int fd = *static_cast<int*>(arg2);
        Ssl::Bio *bio;
        if (arg1 == Ssl::Bio::BIO_TO_SERVER)
            bio = new Ssl::ServerBio(fd);
        else
            bio = new Ssl::ClientBio(fd);
        assert(!table->ptr);
        table->ptr = bio;
        table->init = 1;
        return 0;
    }

    case BIO_C_GET_FD:
        if (table->init) {
            Ssl::Bio *bio = static_cast<Ssl::Bio*>(table->ptr);
            assert(bio);
            if (arg2)
                *static_cast<int*>(arg2) = bio->fd();
            return bio->fd();
        }
        return -1;

    case BIO_CTRL_DUP:
        // Should implemented if the SSL_dup openSSL API function
        // used anywhere in squid.
        return 0;

    case BIO_CTRL_FLUSH:
        if (table->init) {
            Ssl::Bio *bio = static_cast<Ssl::Bio*>(table->ptr);
            assert(bio);
            bio->flush(table);
            return 1;
        }
        return 0;

    /*  we may also need to implement these:
        case BIO_CTRL_RESET:
        case BIO_C_FILE_SEEK:
        case BIO_C_FILE_TELL:
        case BIO_CTRL_INFO:
        case BIO_CTRL_GET_CLOSE:
        case BIO_CTRL_SET_CLOSE:
        case BIO_CTRL_PENDING:
        case BIO_CTRL_WPENDING:
    */
    default:
        return 0;

    }

    return 0; /* NOTREACHED */
}