static bool
clientParseRequest(ConnStateData * conn, bool &do_next_read)
{
    HttpRequestMethod method;
    ClientSocketContext *context;
    bool parsed_req = false;
    HttpVersion http_ver;
    HttpParser hp;

    debugs(33, 5, "clientParseRequest: FD " << conn->fd << ": attempting to parse");

    while (conn->in.notYetUsed > 0 && conn->bodySizeLeft() == 0) {
        connStripBufferWhitespace (conn);

        /* Don't try to parse if the buffer is empty */

        if (conn->in.notYetUsed == 0)
            break;

        /* Limit the number of concurrent requests to 2 */

        if (!connOkToAddRequest(conn)) {
            break;
        }

        /* Should not be needed anymore */
        /* Terminate the string */
        conn->in.buf[conn->in.notYetUsed] = '\0';

        /* Begin the parsing */
        HttpParserInit(&hp, conn->in.buf, conn->in.notYetUsed);

        /* Process request */
        PROF_start(parseHttpRequest);

        context = parseHttpRequest(conn, &hp, &method, &http_ver);

        PROF_stop(parseHttpRequest);

        /* partial or incomplete request */
        if (!context) {

            if (!connKeepReadingIncompleteRequest(conn))
                connCancelIncompleteRequests(conn);

            break;
        }

        /* status -1 or 1 */
        if (context) {
            debugs(33, 5, "clientParseRequest: FD " << conn->fd << ": parsed a request");
            commSetTimeout(conn->fd, Config.Timeout.lifetime, clientLifetimeTimeout,
                           context->http);

            clientProcessRequest(conn, &hp, context, method, http_ver);

            parsed_req = true;

            if (context->mayUseConnection()) {
                debugs(33, 3, "clientParseRequest: Not reading, as this request may need the connection");
                do_next_read = 0;
                break;
            }

            if (!conn->flags.readMoreRequests) {
                conn->flags.readMoreRequests = true;
                break;
            }

            continue;		/* while offset > 0 && conn->bodySizeLeft() == 0 */
        }
    }				/* while offset > 0 && conn->bodySizeLeft() == 0 */

    /* XXX where to 'finish' the parsing pass? */

    return parsed_req;
}