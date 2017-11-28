int
aclMatchHTTPStatus(SplayNode<acl_httpstatus_data*> **dataptr, const Http::StatusCode status)
{

    acl_httpstatus_data X(status);
    SplayNode<acl_httpstatus_data*> **Top = dataptr;
    *Top = Top[0]->splay(&X, aclHTTPStatusCompare);

    debugs(28, 3, "aclMatchHTTPStatus: '" << status << "' " << (splayLastResult ? "NOT found" : "found"));
    return (0 == splayLastResult);
}