static void
aclDumpDomainListWalkee(char * const & node_data, void *outlist)
{
    /* outlist is really a wordlist ** */
    wordlistAdd((wordlist **)outlist, (char const *)node_data);
}