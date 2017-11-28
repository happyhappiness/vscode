static void
neighborCountIgnored(CachePeer * p)
{
    if (p == NULL)
        return;

    ++ p->stats.ignored_replies;

    ++NLateReplies;
}