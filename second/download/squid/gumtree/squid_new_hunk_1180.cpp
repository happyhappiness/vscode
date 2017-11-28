        }
    } // else we got a FEAT error and will only report Squid-supported features

    char buf[256];
    if (!hasEPRT) {
        snprintf(buf, sizeof(buf), "\"%*s\"", prependSpaces + 4, "EPRT");
        featReply->header.putStr(Http::HdrType::FTP_PRE, buf);
    }
    if (!hasEPSV) {
        snprintf(buf, sizeof(buf), "\"%*s\"", prependSpaces + 4, "EPSV");
        featReply->header.putStr(Http::HdrType::FTP_PRE, buf);
    }

    featReply->header.refreshMask();

    writeForwardedReply(featReply.getRaw());
}

void
Ftp::Server::handlePasvReply(const HttpReply *reply, StoreIOBuffer)
{
    const Http::StreamPointer context(pipeline.front());
    assert(context != nullptr);

    if (context->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Server does not support PASV", reply);
        return;
    }

