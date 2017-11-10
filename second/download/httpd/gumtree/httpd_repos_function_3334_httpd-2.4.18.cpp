static void clear_session(const digest_header_rec *resp)
{
    if (resp->client) {
        resp->client->ha1[0] = '\0';
    }
}