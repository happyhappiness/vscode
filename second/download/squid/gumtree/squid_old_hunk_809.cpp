
        case AnyP::PROTO_GOPHER:
            gopherStart(this);
            break;

        case AnyP::PROTO_FTP:
            ftpStart(this);
            break;

        case AnyP::PROTO_CACHE_OBJECT:

        case AnyP::PROTO_INTERNAL:

        case AnyP::PROTO_URN:
            fatal_dump("Should never get here");
            break;

        case AnyP::PROTO_WHOIS:
            whoisStart(this);
