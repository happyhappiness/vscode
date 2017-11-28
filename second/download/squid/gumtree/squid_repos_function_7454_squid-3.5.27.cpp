struct snmp_pdu *
snmp_fix_pdu(struct snmp_pdu *pdu, int command) {
    struct variable_list *var, *newvar;
    struct snmp_pdu *newpdu;
    int i;
    int copied = 0;

#if DEBUG_PDU
    snmplib_debug(8, "PDU %x:  Fixing.  Err index is %d\n",
                  (unsigned int) pdu, (unsigned int) pdu->errindex);
#endif

    if (pdu->command != SNMP_PDU_RESPONSE ||
            pdu->errstat == SNMP_ERR_NOERROR ||
            pdu->errindex <= 0) {
        snmp_set_api_error(SNMPERR_UNABLE_TO_FIX);
        return (NULL);
    }
    /* clone the pdu */
    newpdu = snmp_pdu_clone(pdu);
    if (newpdu == NULL)
        return (NULL);

    newpdu->variables = 0;
    newpdu->command = command;
    newpdu->reqid = SNMP_DEFAULT_REQID;
    newpdu->errstat = SNMP_DEFAULT_ERRSTAT;
    newpdu->errindex = SNMP_DEFAULT_ERRINDEX;

    /* Loop through the variables, removing whatever isn't necessary */

    var = pdu->variables;
    i = 1;

    /* skip first variable if necessary */
    if (pdu->errindex == i) {
        var = var->next_variable;
        i++;
    }
    if (var != NULL) {

        /* VAR is the first uncopied variable */

        /* Clone this variable */
        newpdu->variables = snmp_var_clone(var);
        if (newpdu->variables == NULL) {
            snmp_pdu_free(newpdu);
            return (NULL);
        }
        copied++;

        newvar = newpdu->variables;

        /* VAR has been copied to NEWVAR. */
        while (var->next_variable) {

            /* Skip the item that was bad */
            if (++i == pdu->errindex) {
                var = var->next_variable;
                continue;
            }
            /* Copy this var */
            newvar->next_variable = snmp_var_clone(var->next_variable);
            if (newvar->next_variable == NULL) {
                snmp_pdu_free(newpdu);
                return (NULL);
            }
            /* Move to the next one */
            newvar = newvar->next_variable;
            var = var->next_variable;
            copied++;
        }
        newvar->next_variable = NULL;
    }
    /* If we didn't copy anything, free the new pdu. */
    if (i < pdu->errindex || copied == 0) {
        snmp_free_pdu(newpdu);
        snmp_set_api_error(SNMPERR_UNABLE_TO_FIX);
        return (NULL);
    }
#if DEBUG_PDU
    snmplib_debug(8, "PDU %x:  Fixed PDU is %x\n",
                  (unsigned int) pdu, (unsigned int) newpdu);
#endif
    return (newpdu);
}