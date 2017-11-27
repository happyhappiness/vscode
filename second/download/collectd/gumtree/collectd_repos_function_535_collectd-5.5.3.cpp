static void temp_list_delete(temperature_list_t ** list)
{
    temperature_list_t * tmp;

    while (*list != NULL)
    {
        tmp = (*list);
        (*list) = (*list)->next;
        free(tmp->sensor_name);
        free(tmp);
        tmp = NULL;
    }
}