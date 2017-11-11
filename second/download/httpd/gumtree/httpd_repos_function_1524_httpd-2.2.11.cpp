static const char *long_res_header_for_sc(int sc)
{
    const char *rc = NULL;
    sc = sc & 0X00FF;
    if(sc <= SC_RES_HEADERS_NUM && sc > 0) {
        rc = response_trans_headers[sc - 1];
    }

    return rc;
}