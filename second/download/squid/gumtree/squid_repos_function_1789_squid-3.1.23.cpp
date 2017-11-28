static void
neighborCountIgnored(peer * p)
{
    if (p == NULL)
        return;

    p->stats.ignored_replies++;

    NLateReplies++;
}