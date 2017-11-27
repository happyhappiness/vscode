static int temp_list_add(temperature_list_t * list, const char * sensor)
{
    temperature_list_t *new_temp;

    new_temp = malloc(sizeof (*new_temp));
    if(new_temp == NULL)
        return -1;

    new_temp->sensor_name = strdup(sensor);
    new_temp->initialized = 0;
    new_temp->num_values = 0;
    if(new_temp->sensor_name == NULL)
    {
        free(new_temp);
        return -1;
    }

    new_temp->next = temp_list;
    temp_list = new_temp;
    return 0;
}