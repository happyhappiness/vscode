static int lvm_read(void)
{
    lvm_t lvm;
    struct dm_list *vg_names;
    struct lvm_str_list *name_list;

    lvm = lvm_init(NULL);
    if (!lvm) {
        ERROR("lvm plugin: lvm_init failed.");
        return (-1);
    }

    vg_names = lvm_list_vg_names(lvm);
    if (!vg_names) {
        ERROR("lvm plugin lvm_list_vg_name failed %s", lvm_errmsg(lvm));
        lvm_quit(lvm);
        return (-1);
    }

    dm_list_iterate_items(name_list, vg_names) {
        vg_t vg;

        vg = lvm_vg_open(lvm, name_list->str, "r", 0);
        if (!vg) {
            ERROR ("lvm plugin: lvm_vg_open (%s) failed: %s",
                    name_list->str, lvm_errmsg(lvm));
            continue;
        }

        vg_read(vg, name_list->str);
        lvm_vg_close(vg);
    }

    lvm_quit(lvm);
    return (0);
}