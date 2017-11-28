bool
ACLUserData::match(char const *user)
{
    SplayNode<char *> *Top = names;

    debugs(28, 7, "aclMatchUser: user is " << user << ", case_insensitive is " << flags.case_insensitive);
    debugs(28, 8, "Top is " << Top << ", Top->data is " << ((char *) (Top != NULL ? (Top)->data : "Unavailable")));

    if (user == NULL || strcmp(user, "-") == 0)
        return 0;

    if (flags.required) {
        debugs(28, 7, "aclMatchUser: user REQUIRED and auth-info present.");
        return 1;
    }

    if (flags.case_insensitive)
        Top = Top->splay((char *)user, splaystrcasecmp);
    else
        Top = Top->splay((char *)user, splaystrcmp);

    /* Top=splay_splay(user,Top,(splayNode::SPLAYCMP *)dumping_strcmp); */
    debugs(28, 7, "aclMatchUser: returning " << !splayLastResult << ",Top is " <<
           Top << ", Top->data is " << ((char *) (Top ? Top->data : "Unavailable")));

    names = Top;

    return !splayLastResult;
}