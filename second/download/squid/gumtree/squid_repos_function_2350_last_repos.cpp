int
check_null_wccp2_service(void *)
{
    return !wccp2_service_list_head;
}