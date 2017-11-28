int
ACLAtStepStrategy::match (ACLData<Ssl::BumpStep> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    Ssl::ServerBump *bump = NULL;
    if (checklist->conn() != NULL && (bump = checklist->conn()->serverBump()))
        return data->match(bump->step);
    else
        return data->match(Ssl::bumpStep1);
    return 0;
}