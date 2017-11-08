static int sc_for_req_method_by_id(int method_id)
{
    if (method_id < 0 || method_id > M_INVALID)
        return UNKNOWN_METHOD;
    else
        return sc_for_req_method_table[method_id] ?
               sc_for_req_method_table[method_id] : UNKNOWN_METHOD;
}