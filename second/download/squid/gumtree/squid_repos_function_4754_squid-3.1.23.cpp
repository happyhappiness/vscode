int
ACLIdent::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    if (checklist->rfc931[0]) {
        return data->match(checklist->rfc931);
    } else if (checklist->conn() != NULL && checklist->conn()->rfc931[0]) {
        return data->match(checklist->conn()->rfc931);
    } else {
        debugs(28, 3, HERE << "switching to ident lookup state");
        checklist->changeState(IdentLookup::Instance());
        return 0;
    }
}