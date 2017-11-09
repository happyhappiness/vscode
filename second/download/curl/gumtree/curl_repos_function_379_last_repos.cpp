static int sys_trnlnm
   (const char * logname,
    char * value,
    int value_len)
{
    const $DESCRIPTOR(table_dsc, "LNM$FILE_DEV");
    const unsigned long attr = LNM$M_CASE_BLIND;
    struct dsc$descriptor_s name_dsc;
    int status;
    unsigned short result;
    struct itmlst_3 itlst[2];

    itlst[0].buflen = value_len;
    itlst[0].itmcode = LNM$_STRING;
    itlst[0].bufadr = value;
    itlst[0].retlen = &result;

    itlst[1].buflen = 0;
    itlst[1].itmcode = 0;

    name_dsc.dsc$w_length = strlen(logname);
    name_dsc.dsc$a_pointer = (char *)logname;
    name_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
    name_dsc.dsc$b_class = DSC$K_CLASS_S;

    status = SYS$TRNLNM(&attr, &table_dsc, &name_dsc, 0, itlst);

    if ($VMS_STATUS_SUCCESS(status)) {

         /* Null terminate and return the string */
        /*--------------------------------------*/
        value[result] = '\0';
    }

    return status;
}