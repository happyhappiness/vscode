
    default:
        fatal("Hit unreachable code in clientWriteComplete\n");
    }
}

SQUIDCEXTERN CSR clientGetMoreData;
SQUIDCEXTERN CSS clientReplyStatus;
SQUIDCEXTERN CSD clientReplyDetach;

static ClientSocketContext *
parseHttpRequestAbort(ConnStateData * csd, const char *uri)
{
    ClientHttpRequest *http;
    ClientSocketContext *context;
