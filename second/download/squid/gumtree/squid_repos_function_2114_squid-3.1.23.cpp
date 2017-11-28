void
ServerStateData::serverComplete()
{
    debugs(11,5,HERE << "serverComplete " << this);

    if (!doneWithServer()) {
        closeServer();
        assert(doneWithServer());
    }

    completed = true;

    HttpRequest *r = originalRequest();
    r->hier.total_response_time = r->hier.first_conn_start.tv_sec ?
                                  tvSubMsec(r->hier.first_conn_start, current_time) : -1;

    if (requestBodySource != NULL)
        stopConsumingFrom(requestBodySource);

    if (responseBodyBuffer != NULL)
        return;

    serverComplete2();
}