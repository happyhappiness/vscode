static int sc_for_req_method_by_id(request_rec *r)
{
    int method_id = r->method_number;
    if (method_id < 0 || method_id > M_INVALID) {
        return UNKNOWN_METHOD;
    }
    else if (r->header_only) {
        return SC_M_HEAD;
    }
    else {
        return sc_for_req_method_table[method_id] ?
               sc_for_req_method_table[method_id] : UNKNOWN_METHOD;
    }
}