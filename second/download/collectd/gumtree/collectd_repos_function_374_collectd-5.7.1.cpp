static void zone_submit_values(c_avl_tree_t *tree) {
  char zonename[ZONENAME_MAX];
  zoneid_t *zoneid = NULL;
  zone_stats_t *stats = NULL;

  while (c_avl_pick(tree, (void **)&zoneid, (void **)&stats) == 0) {
    if (getzonenamebyid(*zoneid, zonename, sizeof(zonename)) == -1) {
      WARNING("zone plugin: error retrieving zonename");
    } else {
      zone_submit_value(zonename, (gauge_t)FRC2PCT(stats->pctcpu));
    }
    free(stats);
    free(zoneid);
  }
  c_avl_destroy(tree);
}