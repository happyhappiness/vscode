static void
aclDumpUserListWalkee(char * const & node_data, void *outlist)
{
    /* outlist is really a wordlist ** */
    wordlistAdd((wordlist **)outlist, (char const *)node_data);
}