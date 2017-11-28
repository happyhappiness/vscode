static char *
makeExternalAclKey(ACLFilledChecklist * ch, external_acl_data * acl_data)
{
    static MemBuf mb;
    mb.reset();

    // check for special case tokens in the format
    for (Format::Token *t = acl_data->def->format.format; t ; t = t->next) {

        if (t->type == Format::LFT_EXT_ACL_NAME) {
            // setup for %ACL
            safe_free(ch->al->lastAclName);
            ch->al->lastAclName = xstrdup(acl_data->name);
        }

        if (t->type == Format::LFT_EXT_ACL_DATA) {
            // setup string for %DATA
            SBuf sb;
            for (auto arg = acl_data->arguments; arg; arg = arg->next) {
                if (sb.length())
                    sb.append(" ", 1);

                if (acl_data->def->quote == Format::LOG_QUOTE_URL) {
                    const char *quoted = rfc1738_escape(arg->key);
                    sb.append(quoted, strlen(quoted));
                } else {
                    static MemBuf mb2;
                    mb2.init();
                    strwordquote(&mb2, arg->key);
                    sb.append(mb2.buf, mb2.size);
                    mb2.clean();
                }
            }

            ch->al->lastAclData = sb;
        }

#if USE_IDENT
        if (t->type == Format::LFT_USER_IDENT) {
            if (!*ch->rfc931) {
                // if we fail to go async, we still return NULL and the caller
                // will detect the failure in ACLExternal::match().
                (void)ch->goAsync(IdentLookup::Instance());
                return NULL;
            }
        }
#endif
    }

    // assemble the full helper lookup string
    acl_data->def->format.assemble(mb, ch->al, 0);

    return mb.buf;
}