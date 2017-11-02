static int sys_crelnm
   (const char * logname,
    const char * value)
{
    int ret_val;
    const char * proc_table = "LNM$PROCESS_TABLE";
    struct dsc$descriptor_s proc_table_dsc;
    struct dsc$descriptor_s logname_dsc;
    struct itmlst_3 item_list[2];

    proc_table_dsc.dsc$a_pointer = (char *) proc_table;
    proc_table_dsc.dsc$w_length = strlen(proc_table);
    proc_table_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
    proc_table_dsc.dsc$b_class = DSC$K_CLASS_S;

    logname_dsc.dsc$a_pointer = (char *) logname;
    logname_dsc.dsc$w_length = strlen(logname);
    logname_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
    logname_dsc.dsc$b_class = DSC$K_CLASS_S;

    item_list[0].buflen = strlen(value);
    item_list[0].itmcode = LNM$_STRING;
    item_list[0].bufadr = (char *)value;
    item_list[0].retlen = NULL;

    item_list[1].buflen = 0;
    item_list[1].itmcode = 0;

    ret_val = SYS$CRELNM(NULL, &proc_table_dsc, &logname_dsc, NULL, item_list);

    return ret_val;
}