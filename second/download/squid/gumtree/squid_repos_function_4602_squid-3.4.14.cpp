wordlist*
Acl::Tree::treeDump(const char *prefix, const ActionToString &convert) const
{
    wordlist *text = NULL;
    Actions::const_iterator action = actions.begin();
    typedef Nodes::const_iterator NCI;
    for (NCI node = nodes.begin(); node != nodes.end(); ++node) {

        wordlistAdd(&text, prefix);

        if (action != actions.end()) {
            const char *act = convert ? convert[action->kind] :
                              (*action == ACCESS_ALLOWED ? "allow" : "deny");
            wordlistAdd(&text, act ? act : "???");
            ++action;
        }

        wordlist *rule = (*node)->dump();
        wordlistAddWl(&text, rule);
        wordlistDestroy(&rule);

        wordlistAdd(&text, "\n");
    }
    return text;
}