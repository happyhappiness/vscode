wordlist *
ACLExternal::dump() const
{
    external_acl_data const *acl = data;
    wordlist *result = NULL;
    wordlist *arg;
    MemBuf mb;
    mb.init();
    mb.Printf("%s", acl->def->name);

    for (arg = acl->arguments; arg; arg = arg->next) {
        mb.Printf(" %s", arg->key);
    }

    wordlistAdd(&result, mb.buf);
    mb.clean();
    return result;
}