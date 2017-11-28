int
read_objid(input, output, out_len)
char *input;
oid *output;
int *out_len;		/* number of subid's in "output" */
{
    struct snmp_mib_tree *root = Mib;
    oid *op = output;
    int i;

    if (*input == '.')
        input++;
    else {
        root = find_rfc1066_mib(root);
        for (i = 0; i < sizeof(RFC1066_MIB) / sizeof(oid); i++) {
            if ((*out_len)-- > 0)
                *output++ = RFC1066_MIB[i];
            else {
                snmplib_debug(0, "object identifier too long\n");
                return (0);
            }
        }
    }

    if (root == NULL) {
        snmplib_debug(0, "Mib not initialized.\n");
        return 0;
    }
    if ((*out_len = parse_subtree(root, input, output, out_len)) == 0)
        return (0);
    *out_len += output - op;

    return (1);
}