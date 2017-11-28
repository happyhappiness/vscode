SBufList
ACLExternal::dump() const
{
    external_acl_data const *acl = data;
    SBufList rv;
    rv.push_back(SBuf(acl->def->name));

    for (wordlist *arg = acl->arguments; arg; arg = arg->next) {
        SBuf s;
        s.Printf(" %s", arg->key);
        rv.push_back(s);
    }

    return rv;
}