void
Acl::InnerNode::lineParse()
{
    // XXX: not precise, may change when looping or parsing multiple lines
    if (!cfgline)
        cfgline = xstrdup(config_input_line);

    // expect a list of ACL names, each possibly preceeded by '!' for negation

    while (const char *t = ConfigParser::strtokFile()) {
        const bool negated = (*t == '!');
        if (negated)
            ++t;

        debugs(28, 3, "looking for ACL " << t);
        ACL *a = ACL::FindByName(t);

        if (a == NULL) {
            debugs(28, DBG_CRITICAL, "ACL not found: " << t);
            self_destruct();
            return;
        }

        // append(negated ? new NotNode(a) : a);
        if (negated)
            add(new NotNode(a));
        else
            add(a);
    }

    return;
}