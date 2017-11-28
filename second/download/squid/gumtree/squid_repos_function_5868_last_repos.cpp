static int
result_recv(char *buffer, int length)
{
    AUTH_HDR *auth;
    int totallen;
    unsigned char reply_digest[AUTH_VECTOR_LEN];
    unsigned char calc_digest[AUTH_VECTOR_LEN];
    int secretlen;
    /* VALUE_PAIR   *req; */

    auth = (AUTH_HDR *) buffer;
    totallen = ntohs(auth->length);

    if (totallen != length) {
        debug("Received invalid reply length from server (want %d/ got %d)\n", totallen, length);
        return -1;
    }
    if (auth->id != request_id) {
        /* Duplicate response of an earlier query, ignore */
        return -1;
    }
    /* Verify the reply digest */
    memcpy(reply_digest, auth->vector, AUTH_VECTOR_LEN);
    memcpy(auth->vector, vector, AUTH_VECTOR_LEN);
    secretlen = strlen(secretkey);
    memcpy(buffer + length, secretkey, secretlen);
    md5_calc(calc_digest, (unsigned char *) auth, length + secretlen);

    if (memcmp(reply_digest, calc_digest, AUTH_VECTOR_LEN) != 0) {
        debug("WARNING: Received invalid reply digest from server\n");
        return -1;
    }
    if (auth->code != PW_AUTHENTICATION_ACK)
        return 1;

    return 0;
}