void h2_request_destroy(h2_request *req)
{
    if (req->to_h1) {
        h2_to_h1_destroy(req->to_h1);
        req->to_h1 = NULL;
    }
}