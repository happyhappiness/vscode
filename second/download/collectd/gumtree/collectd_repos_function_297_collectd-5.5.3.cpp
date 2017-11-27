static int kafka_config(oconfig_item_t *ci) /* {{{ */
{
	int                          i;
	oconfig_item_t              *child;
    rd_kafka_conf_t             *conf;
    rd_kafka_conf_res_t          ret;
    char                         errbuf[1024];

    if ((conf = rd_kafka_conf_new()) == NULL) {
        WARNING("cannot allocate kafka configuration.");
        return -1;
    }
	for (i = 0; i < ci->children_num; i++)  {
		child = &ci->children[i];

		if (strcasecmp("Topic", child->key) == 0) {
			kafka_config_topic (conf, child);
		} else if (strcasecmp(child->key, "Property") == 0) {
			char *key = NULL;
			char *val = NULL;

			if (child->values_num != 2) {
				WARNING("kafka properties need both a key and a value.");
                goto errout;
			}
			if (child->values[0].type != OCONFIG_TYPE_STRING ||
			    child->values[1].type != OCONFIG_TYPE_STRING) {
				WARNING("kafka properties needs string arguments.");
                goto errout;
			}
			if ((key = strdup(child->values[0].value.string)) == NULL) {
				WARNING("cannot allocate memory for attribute key.");
                goto errout;
			}
			if ((val = strdup(child->values[1].value.string)) == NULL) {
				WARNING("cannot allocate memory for attribute value.");
                goto errout;
			}
            ret = rd_kafka_conf_set(conf, key, val, errbuf, sizeof(errbuf));
            if (ret != RD_KAFKA_CONF_OK) {
                WARNING("cannot set kafka property %s to %s: %s",
                        key, val, errbuf);
                goto errout;
            }
			sfree(key);
			sfree(val);
		} else {
			WARNING ("write_kafka plugin: Ignoring unknown "
				 "configuration option \"%s\" at top level.",
				 child->key);
		}
	}
    if (conf != NULL)
        rd_kafka_conf_destroy(conf);
    return (0);
 errout:
    if (conf != NULL)
        rd_kafka_conf_destroy(conf);
    return -1;
}