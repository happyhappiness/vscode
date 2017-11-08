static void add_log_id(const conn_rec *c, const request_rec *r)
{
    const char **id;
    /* need to cast const away */
    if (r) {
        id = &((request_rec *)r)->log_id;
    }
    else {
        id = &((conn_rec *)c)->log_id;
    }

    ap_run_generate_log_id(c, r, id);
}