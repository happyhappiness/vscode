bool
Ftp::Client::parseControlReply(size_t &bytesUsed)
{
    char *s;
    char *sbuf;
    char *end;
    int usable;
    int complete = 0;
    wordlist *head = NULL;
    wordlist *list;
    wordlist **tail = &head;
    size_t linelen;
    debugs(9, 3, status());
    /*
     * We need a NULL-terminated buffer for scanning, ick
     */
    const size_t len = ctrl.offset;
    sbuf = (char *)xmalloc(len + 1);
    xstrncpy(sbuf, ctrl.buf, len + 1);
    end = sbuf + len - 1;

    while (*end != '\r' && *end != '\n' && end > sbuf)
        --end;

    usable = end - sbuf;

    debugs(9, 3, "usable = " << usable);

    if (usable == 0) {
        debugs(9, 3, "didn't find end of line");
        safe_free(sbuf);
        return false;
    }

    debugs(9, 3, len << " bytes to play with");
    ++end;
    s = sbuf;
    s += strspn(s, crlf);

    for (; s < end; s += strcspn(s, crlf), s += strspn(s, crlf)) {
        if (complete)
            break;

        debugs(9, 5, "s = {" << s << "}");

        linelen = strcspn(s, crlf) + 1;

        if (linelen < 2)
            break;

        if (linelen > 3)
            complete = (*s >= '0' && *s <= '9' && *(s + 3) == ' ');

        list = new wordlist();

        list->key = (char *)xmalloc(linelen);

        xstrncpy(list->key, s, linelen);

        /* trace the FTP communication chat at level 2 */
        debugs(9, 2, "ftp>> " << list->key);

        if (complete) {
            // use list->key for last_reply because s contains the new line
            ctrl.last_reply = xstrdup(list->key + 4);
            ctrl.replycode = atoi(list->key);
        }

        *tail = list;

        tail = &list->next;
    }

    bytesUsed = static_cast<size_t>(s - sbuf);
    safe_free(sbuf);

    if (!complete) {
        wordlistDestroy(&head);
        return false;
    }

    ctrl.message = head;
    assert(ctrl.replycode >= 0);
    assert(ctrl.last_reply);
    assert(ctrl.message);
    return true;
}