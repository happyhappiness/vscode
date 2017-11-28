void
snmp_free_pdu(struct snmp_pdu *pdu)
{
    struct variable_list *vp, *ovp;

    vp = pdu->variables;
    while (vp) {
        ovp = vp;
        vp = vp->next_variable;
        snmp_var_free(ovp);
    }

    if (pdu->enterprise)
        xfree((char *) pdu->enterprise);
    xfree((char *) pdu);
}