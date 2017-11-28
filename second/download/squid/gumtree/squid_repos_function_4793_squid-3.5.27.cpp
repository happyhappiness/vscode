SBufList
Acl::Tree::treeDump(const char *prefix, const ActionToString &convert) const
{
    SBufList text;
    Actions::const_iterator action = actions.begin();
    typedef Nodes::const_iterator NCI;
    for (NCI node = nodes.begin(); node != nodes.end(); ++node) {

        text.push_back(SBuf(prefix));

        if (action != actions.end()) {
            const char *act = convert ? convert[action->kind] :
                              (*action == ACCESS_ALLOWED ? "allow" : "deny");
            text.push_back(act?SBuf(act):SBuf("???"));
            ++action;
        }

        // temp is needed until c++11 move constructor
        SBufList temp = (*node)->dump();
        text.splice(text.end(), temp);
        text.push_back(SBuf("\n"));
    }
    return text;
}