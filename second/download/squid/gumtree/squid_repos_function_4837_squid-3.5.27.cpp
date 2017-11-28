int
ACLHTTPStatus::match(ACLChecklist *checklist)
{
    return aclMatchHTTPStatus(&data, Filled(checklist)->reply->sline.status());
}