int
aclMatchHTTPStatus(Splay<acl_httpstatus_data*> **dataptr, const Http::StatusCode status)
{
    acl_httpstatus_data X(status);
    const acl_httpstatus_data * const * result = (*dataptr)->find(&X, aclHTTPStatusCompare);

    debugs(28, 3, "aclMatchHTTPStatus: '" << status << "' " << (result ? "found" : "NOT found"));
    return (result != NULL);
}