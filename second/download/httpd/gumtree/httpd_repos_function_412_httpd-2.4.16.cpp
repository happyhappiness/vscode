static const char *log_log_id(request_rec *r, char *a)
{
    if (a && !strcmp(a, "c")) {
        return r->connection->log_id ? r->connection->log_id : "-";
    }
    else {
        return r->log_id ? r->log_id : "-";
    }
}