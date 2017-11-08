util_compare_subgroup_t *util_ald_sgl_dup(util_ald_cache_t *cache, util_compare_subgroup_t *sgl_in)
{
    int i = 0;
    util_compare_subgroup_t *sgl_out = NULL;

    if (!sgl_in) {
        return NULL;
    }

    sgl_out = (util_compare_subgroup_t *) util_ald_alloc(cache, sizeof(util_compare_subgroup_t));
    if (sgl_out) {
        sgl_out->subgroupDNs = util_ald_alloc(cache, sizeof(char *) * sgl_in->len);
        if (sgl_out->subgroupDNs) {
            for (i = 0; i < sgl_in->len; i++) {
                sgl_out->subgroupDNs[i] = util_ald_strdup(cache, sgl_in->subgroupDNs[i]);
                if (!sgl_out->subgroupDNs[i]) {
                    /* We ran out of SHM, delete the strings we allocated for the SGL */
                    for (i = (i - 1); i >= 0; i--) {
                            util_ald_free(cache, sgl_out->subgroupDNs[i]);
                    }
                    util_ald_free(cache, sgl_out->subgroupDNs);
                    util_ald_free(cache, sgl_out);
                    sgl_out =  NULL;
                    break;
                }
            }
            /* We were able to allocate new strings for all the subgroups */
            if (sgl_out != NULL) {
                sgl_out->len = sgl_in->len;
            }
        }
    }

    return sgl_out;
}