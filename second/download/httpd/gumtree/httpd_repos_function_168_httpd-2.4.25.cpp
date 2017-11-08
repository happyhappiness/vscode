static int ImportLogTransaction(request_rec *r)
{
    if (pfn)
        return pfn(r->the_request);
    return DECLINED;
}