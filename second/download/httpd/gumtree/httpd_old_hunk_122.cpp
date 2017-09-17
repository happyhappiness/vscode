     */
    if (r->read_body == REQUEST_CHUNKED_PASS)
        bufsiz -= 2;
    if (bufsiz <= 0)
        return -1;              /* Cannot read chunked with a small buffer */

    if (r->remaining == 0) {    /* Start of new chunk */

        chunk_start = getline(buffer, bufsiz, r->connection->client, 0);
        if ((chunk_start <= 0) || (chunk_start >= (bufsiz - 1))
            || !isxdigit(*buffer)) {
            r->connection->keepalive = -1;
