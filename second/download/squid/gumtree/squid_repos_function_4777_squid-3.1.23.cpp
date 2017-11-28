int
ACLMaxUserIP::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    int ti;

    if ((ti = AuthenticateAcl(checklist)) != 1)
        return ti;

    ti = match(checklist->auth_user_request, checklist->src_addr);

    AUTHUSERREQUESTUNLOCK(checklist->auth_user_request, "ACLChecklist via ACLMaxUserIP");

    return ti;
}