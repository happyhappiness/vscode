static int
check_null_access_log(CustomLog *customlog_definitions)
{
    return customlog_definitions == NULL;
}