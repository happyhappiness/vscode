static int mod_info_module_cmds(request_rec * r, const command_rec * cmds,
                                ap_directive_t * node, int from, int level)
{
    int shown = from;
    ap_directive_t *dir;
    if (level == 0)
        ap_set_module_config(r->request_config, &info_module, NULL);
    for (dir = node; dir; dir = dir->next) {
        if (dir->first_child != NULL) {
            if (level < mod_info_module_cmds(r, cmds, dir->first_child,
                                             shown, level + 1)) {
                shown = level;
                mod_info_show_close(r, dir, level);
            }
        }
        else if (mod_info_has_cmd(cmds, dir)) {
            if (shown < level) {
                mod_info_show_parents(r, dir->parent, shown, level - 1);
                shown = level;
            }
            mod_info_show_cmd(r, dir, level);
        }
    }
    return shown;
}