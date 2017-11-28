inline
const char *errorDetailName(int errDetailId)
{
    if (errDetailId < ERR_DETAIL_START)
        return "SYSERR";

    if (errDetailId < ERR_DETAIL_MAX)
        return err_detail_type_str[errDetailId-ERR_DETAIL_START+2];

    if (errDetailId >=ERR_DETAIL_EXCEPTION_START)
        return "EXCEPTION";

    return "UNKNOWN";
}