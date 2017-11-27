static void vg_read(vg_t vg, char const *vg_name)
{
    struct dm_list *lvs;
    struct lvm_lv_list *lvl;
    char const *name;
    char const *attrs;
    uint64_t size;

    lvm_submit (vg_name, "free", lvm_vg_get_free_size(vg));

    lvs = lvm_vg_list_lvs(vg);
    if (!lvs) {
        /* no VGs are defined, which is not an error per se */
        return;
    }

    dm_list_iterate_items(lvl, lvs) {
        name = lvm_lv_get_name(lvl->lv);
        attrs = get_lv_property_string(lvl->lv, "lv_attr");
        size = lvm_lv_get_size(lvl->lv);
        if (name == NULL || attrs == NULL || size == NO_VALUE)
            continue;

        /* Condition on volume type.  We want the reported sizes in the
           volume group to sum to the size of the volume group, so we ignore
           virtual volumes.  */
        switch (attrs[0]) {
            case 's':
            case 'S':
                /* Snapshot.  Also report used/free space. */
                report_lv_utilization(lvl->lv, vg_name, name, size,
                        "data_percent");
                break;
            case 't':
                /* Thin pool virtual volume.  We report the underlying data
                   and metadata volumes, not this one.  Report used/free
                   space, then ignore. */
                report_thin_pool_utilization(lvl->lv, vg_name, size);
                continue;
            case 'v':
                /* Virtual volume.  Ignore. */
                continue;
            case 'V':
                /* Thin volume or thin snapshot.  Ignore. */
                continue;
        }
        lvm_submit(vg_name, name, size);
    }
}