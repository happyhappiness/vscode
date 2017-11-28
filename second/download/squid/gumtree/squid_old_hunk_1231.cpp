
        case Log::Format::CLF_NONE:
            storeAppendPrintf(entry, "logformat=none");
            break;

        case Log::Format::CLF_SQUID:
            storeAppendPrintf(entry, "%s logformat=squid", log->filename);
            break;

        case Log::Format::CLF_COMBINED:
            storeAppendPrintf(entry, "%s logformat=combined", log->filename);
            break;

