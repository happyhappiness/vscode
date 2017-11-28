        /* find out type of object */
        bufp = asn_parse_header(bufp, &ThisVarLen, &(Var->type));
        if (bufp == NULL)
            PARSE_ERROR;
        ThisVarLen = DataLen;

#if DEBUG_VARS_DECODE
        printf("VARS: Data type %d\n", Var->type);
#endif

        /* Parse the type */

        switch ((short) Var->type) {
