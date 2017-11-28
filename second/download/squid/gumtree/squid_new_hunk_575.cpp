
    assert(0 == i);
    s->flush();
    memFree(buf, MEM_4K_BUF);
#else

    reply->setHeaders(Http::scBadRequest, "Bad Request", NULL, -1, squid_curtime, -2);
    s->replaceHttpReply(reply);
    storeAppendPrintf(s, "NETDB support not compiled into this Squid cache.\n");
#endif

    s->complete();
}
