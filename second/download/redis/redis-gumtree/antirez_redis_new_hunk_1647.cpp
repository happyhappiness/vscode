            char *nextra = extra;
            int remaining = sizeof(extra);
            quicklist *ql = val->ptr;
            /* Add number of quicklist nodes */
            int used = snprintf(nextra, remaining, " ql_nodes:%u", ql->len);
            nextra += used;
            remaining -= used;
            /* Add average quicklist fill factor */
            double avg = (double)ql->count/ql->len;
            used = snprintf(nextra, remaining, " ql_avg_node:%.2f", avg);
            nextra += used;
            remaining -= used;
            /* Add quicklist fill level / max ziplist size */
            used = snprintf(nextra, remaining, " ql_ziplist_max:%d", ql->fill);
            nextra += used;
            remaining -= used;
            /* Add isCompressed? */
            int compressed = ql->compress != 0;
            used = snprintf(nextra, remaining, " ql_compressed:%d", compressed);
            nextra += used;
            remaining -= used;
            /* Add total uncompressed size */
            unsigned long sz = 0;
            for (quicklistNode *node = ql->head; node; node = node->next) {
                sz += node->sz;
            }
            used = snprintf(nextra, remaining, " ql_uncompressed_size:%lu", sz);
            nextra += used;
            remaining -= used;
        }

        addReplyStatusFormat(c,
