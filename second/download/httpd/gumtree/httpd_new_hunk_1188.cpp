     */

    if (r->read_body == REQUEST_CHUNKED_PASS)

        bufsiz -= 2;

    if (bufsiz <= 0)

        return -1;              /* Cannot read chunked with a small buffer */



    /* Check to see if we have already read too much request data.

     * For efficiency reasons, we only check this at the top of each

     * caller read pass, since the limit exists just to stop infinite

     * length requests and nobody cares if it goes over by one buffer.

     */

    max_body = ap_get_limit_req_body(r);

    if (max_body && (r->read_length > max_body)) {

        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

            "Chunked request body is larger than the configured limit of %lu",

            max_body);

        r->connection->keepalive = -1;

        return -1;

    }



    if (r->remaining == 0) {    /* Start of new chunk */



        chunk_start = getline(buffer, bufsiz, r->connection->client, 0);

        if ((chunk_start <= 0) || (chunk_start >= (bufsiz - 1))

            || !isxdigit(*buffer)) {

            r->connection->keepalive = -1;

