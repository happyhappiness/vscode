wordlist *
FtpStateData::ftpParseControlReply(char *buf, size_t len, int *codep, size_t *used)
{
    char *s;
    char *sbuf;
    char *end;
    int usable;
    int complete = 0;
    wordlist *head = NULL;
    wordlist *list;
    wordlist **tail = &head;
    size_t offset;
    size_t linelen;
    int code = -1;
    debugs(9, 3, HERE);
    /*
     * We need a NULL-terminated buffer for scanning, ick
     */
    sbuf = (char *)xmalloc(len + 1);
    xstrncpy(sbuf, buf, len + 1);
    end = sbuf + len - 1;

    while (*end != '\r' && *end != '\n' && end > sbuf)
        end--;

    usable = end - sbuf;

    debugs(9, 3, HERE << "usable = " << usable);

    if (usable == 0) {
        debugs(9, 3, HERE << "didn't find end of line");
        safe_free(sbuf);
        return NULL;
    }

    debugs(9, 3, HERE << len << " bytes to play with");
    end++;
    s = sbuf;
    s += strspn(s, crlf);

    for (; s < end; s += strcspn(s, crlf), s += strspn(s, crlf)) {
        if (complete)
            break;

        debugs(9, 5, HERE << "s = {" << s << "}");

        linelen = strcspn(s, crlf) + 1;

        if (linelen < 2)
            break;

        if (linelen > 3)
            complete = (*s >= '0' && *s <= '9' && *(s + 3) == ' ');

        if (complete)
            code = atoi(s);

        offset = 0;

        if (linelen > 3)
            if (*s >= '0' && *s <= '9' && (*(s + 3) == '-' || *(s + 3) == ' '))
                offset = 4;

        list = new wordlist();

        list->key = (char *)xmalloc(linelen - offset);

        xstrncpy(list->key, s + offset, linelen - offset);

        /* trace the FTP communication chat at level 2 */
        debugs(9, 2, "ftp>> " << code << " " << list->key);

        *tail = list;

        tail = &list->next;
    }

    *used = (size_t) (s - sbuf);
    safe_free(sbuf);

    if (!complete)
        wordlistDestroy(&head);

    if (codep)
        *codep = code;

    return head;
}