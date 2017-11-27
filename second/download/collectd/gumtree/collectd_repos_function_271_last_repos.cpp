static c_avl_tree_t *zone_scandir(DIR *procdir) {
  pid_t pid;
  dirent_t *direntp;
  psinfo_t psinfo;
  c_avl_tree_t *tree;
  zone_stats_t *stats;

  if (!(tree = c_avl_create(zone_compare))) {
    WARNING("zone plugin: Failed to create tree");
    return NULL;
  }

  rewinddir(procdir);
  while ((direntp = readdir(procdir))) {
    char const *pidstr = direntp->d_name;
    if (pidstr[0] == '.') /* skip "." and ".."  */
      continue;

    pid = atoi(pidstr);
    if (pid == 0 || pid == 2 || pid == 3)
      continue; /* skip sched, pageout and fsflush */

    if (zone_read_procfile(pidstr, "psinfo", &psinfo, sizeof(psinfo_t)) != 0)
      continue;

    stats = zone_find_stats(tree, psinfo.pr_zoneid);
    if (stats) {
      stats->pctcpu += psinfo.pr_pctcpu;
      stats->pctmem += psinfo.pr_pctmem;
    }
  }
  return tree;
}