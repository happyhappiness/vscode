static void
aclDumpHTTPStatusListWalkee(acl_httpstatus_data * const &node, void *state)
{
    static char buf[8];
    node->toStr(buf, sizeof(buf));
    wordlistAdd((wordlist **)state, buf);
}