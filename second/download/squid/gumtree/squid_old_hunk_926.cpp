
void
ACLHierCodeData::parse()
{
    char *t = NULL;

    while ((t = strtokFile())) {
        for (hier_code iter = HIER_NONE; iter <= HIER_MAX; ++iter) {
            if (iter == HIER_MAX) {
                fatalf("ERROR: No such hier_code '%s'",t);
                return;
            }
            if (strcmp(hier_code_str[iter],t) == 0) {
