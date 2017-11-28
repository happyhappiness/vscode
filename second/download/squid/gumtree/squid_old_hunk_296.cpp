    if (urnState->flags.force_menu) {
        debugs(51, 3, "urnHandleReply: forcing menu");
    } else if (min_u) {
        rep->header.putStr(HDR_LOCATION, min_u->url);
    }

    httpBodySet(&rep->body, mb);
    /* don't clean or delete mb; rep->body owns it now */
    e->replaceHttpReply(rep);
    e->complete();

    for (i = 0; i < urlcnt; i++) {
        safe_free(urls[i].url);
        safe_free(urls[i].host);
    }

    safe_free(urls);
    /* mb was absorbed in httpBodySet call, so we must not clean it */
