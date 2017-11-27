static int get_reference_temperature(double * result)
{
    temperature_list_t * list = temp_list;

    gauge_t * values = NULL;   /**< rate values */
    size_t    values_num = 0;  /**< number of rate values */
    int i;

    gauge_t values_history[REF_TEMP_AVG_NUM];

    double avg_sum;  /**< Value sum for computing average */
    int    avg_num;  /**< Number of values for computing average */
    double average;  /**< Resulting value average */

    *result = NAN;

    while(list != NULL)
    {
        avg_sum = 0.0;
        avg_num = 0;

        /* First time need to read current rate to learn how many values are
           there (typically for temperature it would be just one).
           We do not expect dynamic changing of number of temperarure values
           in runtime yet (are there any such cases?). */
        if(!list->initialized)
        {
            if(uc_get_rate_by_name(list->sensor_name,
                                   &values,
                                   &values_num))
            {
                DEBUG ("barometer: get_reference_temperature - rate \"%s\" not found yet",
                       list->sensor_name);
                list = list->next;
                continue;
            }

            DEBUG ("barometer: get_reference_temperature - initialize \"%s\", %zu vals",
                   list->sensor_name,
                   values_num);

            list->initialized = 1;
            list->num_values = values_num;

            for(i=0; i<values_num; ++i)
            {
                DEBUG ("barometer: get_reference_temperature - rate %d: %lf **",
                       i,
                       values[i]);
                if(!isnan(values[i]))
                {
                    avg_sum += values[i];
                    ++avg_num;
                }
            }
            free(values);
            values = NULL;
        }

        /* It is OK to get here the first time as well, in the worst case
           the history will full of NANs. */
        if(uc_get_history_by_name(list->sensor_name,
                                  values_history,
                                  REF_TEMP_AVG_NUM,
                                  list->num_values))
        {
            ERROR ("barometer: get_reference_temperature - history \"%s\" lost",
                   list->sensor_name);
            list->initialized = 0;
            list->num_values = 0;
            list = list->next;
            continue;
        }

        for(i=0; i<REF_TEMP_AVG_NUM*list->num_values; ++i)
        {
            DEBUG ("barometer: get_reference_temperature - history %d: %lf",
                   i,
                   values_history[i]);
            if(!isnan(values_history[i]))
            {
                avg_sum += values_history[i];
                ++avg_num;
            }
        }

        if(avg_num == 0)   /* still no history? fallback to current */
        {
            if(uc_get_rate_by_name(list->sensor_name,
                                   &values,
                                   &values_num))
            {
                ERROR ("barometer: get_reference_temperature - rate \"%s\" lost",
                       list->sensor_name);
                list->initialized = 0;
                list->num_values = 0;
                list = list->next;
                continue;
            }

            for(i=0; i<values_num; ++i)
            {
                DEBUG ("barometer: get_reference_temperature - rate last %d: %lf **",
                       i,
                       values[i]);
                if(!isnan(values[i]))
                {
                    avg_sum += values[i];
                    ++avg_num;
                }
            }
            free(values);
            values = NULL;
        }

        if(avg_num == 0)
        {
            ERROR ("barometer: get_reference_temperature - could not read \"%s\"",
                   list->sensor_name);
            list->initialized = 0;
            list->num_values = 0;
        }
        else
        {
            average = avg_sum / (double) avg_num;
            if(isnan(*result))
                *result=average;
            else if(*result>average)
                *result=average;
        }
        list = list->next;
    }  /* while sensor list */

    if(*result == NAN)
    {
        ERROR("barometer: get_reference_temperature - no sensor available (yet?)");
        return -1;
    }
    DEBUG ("barometer: get_reference_temperature - temp is %lf", *result);
    return 0;
}