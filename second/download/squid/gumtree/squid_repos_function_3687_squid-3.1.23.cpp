void
QosConfig::parseConfigLine()
{
    // %i honors 0 and 0x prefixes, which are important for things like umask
    /* parse options ... */
    char *token;
    while ( (token = strtok(NULL, w_space)) ) {

        if (strncmp(token, "local-hit=",10) == 0) {
            sscanf(&token[10], "%i", &tos_local_hit);
        } else if (strncmp(token, "sibling-hit=",12) == 0) {
            sscanf(&token[12], "%i", &tos_sibling_hit);
        } else if (strncmp(token, "parent-hit=",11) == 0) {
            sscanf(&token[11], "%i", &tos_parent_hit);
        } else if (strcmp(token, "disable-preserve-miss") == 0) {
            preserve_miss_tos = 0;
            preserve_miss_tos_mask = 0;
        } else if (preserve_miss_tos && strncmp(token, "miss-mask=",10) == 0) {
            sscanf(&token[10], "%i", &preserve_miss_tos_mask);
        }
    }
}