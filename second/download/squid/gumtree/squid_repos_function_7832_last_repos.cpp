int SMB_Figure_Protocol(const char *dialects[], int prot_index)

{
    int i;

    // prot_index may be a value outside the table SMB_Types[]
    // which holds data at offsets 0 to 11
    int ourType = (prot_index < 0 || prot_index > 11);

    if (ourType && dialects == SMB_Prots) { /* The jobs is easy, just index into table */

        return(SMB_Types[prot_index]);
    } else { /* Search through SMB_Prots looking for a match */

        for (i = 0; SMB_Prots[i] != NULL; i++) {

            if (strcmp(dialects[prot_index], SMB_Prots[i]) == 0) { /* A match */

                return(SMB_Types[i]);

            }

        }

        /* If we got here, then we are in trouble, because the protocol was not */
        /* One we understand ...                                                */

        return(SMB_P_Unknown);

    }

}