        }
    } // else we got a FEAT error and will only report Squid-supported features

    char buf[256];
    if (!hasEPRT) {
        snprintf(buf, sizeof(buf), "\"%*s\"", prependSpaces + 4, "EPRT");
        featReply->header.putStr(HDR_FTP_PRE, buf);
    }
    if (!hasEPSV) {
        snprintf(buf, sizeof(buf), "\"%*s\"", prependSpaces + 4, "EPSV");
        featReply->header.putStr(HDR_FTP_PRE, buf);
    }

    featReply->header.refreshMask();

    writeForwardedReply(featReply.getRaw());
}

void
Ftp::Server::handlePasvReply(const HttpReply *reply, StoreIOBuffer)
{
    ClientSocketContext::Pointer context = getCurrentContext();
    assert(context != NULL);

    if (context->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Server does not support PASV", reply);
        return;
    }

