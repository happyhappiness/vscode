static void
aclDumpArpListWalkee(Eui::Eui48 * const &node, void *state)
{
    static char buf[48];
    node->encode(buf, 48);
    wordlistAdd((wordlist **)state, buf);
}