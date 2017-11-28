 */

struct variable_list *
snmp_var_new(oid * Name, int Len) {
    struct variable_list *New;

#if DEBUG_VARS
    printf("VARS: Creating.\n");
#endif

    New = xmalloc(sizeof(*New));
    /* XXX xmalloc never returns NULL */
    if (New == NULL) {
