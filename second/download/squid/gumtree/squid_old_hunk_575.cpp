
    assert(0 == i);
    s->flush();
    memFree(buf, MEM_4K_BUF);
#else

    reply->setHeaders(HTTP_BAD_REQUEST, "Bad Request", NULL, -1, squid_curtime, -2);
    s->replaceHttpReply(reply);
    storeAppendPrintf(s, "NETDB support not compiled into this Squid cache.\n");
#endif

    s->complete();
}
