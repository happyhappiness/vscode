static int ceph_config(oconfig_item_t *ci)
{
    int ret, i;

    for(i = 0; i < ci->children_num; ++i)
    {
        oconfig_item_t *child = ci->children + i;
        if(strcasecmp("Daemon", child->key) == 0)
        {
            ret = cc_add_daemon_config(child);
            if(ret == ENOMEM)
            {
                ERROR("ceph plugin: Couldn't allocate memory");
                return ret;
            }
            else if(ret)
            {
                //process other daemons and ignore this one
                continue;
            }
        }
        else if(strcasecmp("LongRunAvgLatency", child->key) == 0)
        {
            ret = cc_handle_bool(child, &long_run_latency_avg);
            if(ret)
            {
                return ret;
            }
        }
        else if(strcasecmp("ConvertSpecialMetricTypes", child->key) == 0)
        {
            ret = cc_handle_bool(child, &convert_special_metrics);
            if(ret)
            {
                return ret;
            }
        }
        else
        {
            WARNING("ceph plugin: ignoring unknown option %s", child->key);
        }
    }
    return 0;
}