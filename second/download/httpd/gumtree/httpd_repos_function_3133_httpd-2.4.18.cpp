void util_ald_sgl_free(util_ald_cache_t *cache, util_compare_subgroup_t **sgl)
{
    int i = 0;
    if (sgl == NULL || *sgl == NULL) {
        return;
    }

    for (i = 0; i < (*sgl)->len; i++) {
        util_ald_free(cache, (*sgl)->subgroupDNs[i]);
    }
    util_ald_free(cache, *sgl);
}