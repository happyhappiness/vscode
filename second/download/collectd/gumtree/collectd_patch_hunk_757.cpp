       ERROR(PLUGIN_NAME " plugin: unknown InterfaceFormat: %s", value);
       return -1;
     }
     return 0;
   }
 
+  if (strcasecmp(key, "Instances") == 0) {
+    char *eptr = NULL;
+    double val = strtod(value, &eptr);
+
+    if (*eptr != '\0') {
+      ERROR(PLUGIN_NAME " plugin: Invalid value for Instances = '%s'", value);
+      return 1;
+    }
+    if (val <= 0) {
+      ERROR(PLUGIN_NAME " plugin: Instances <= 0 makes no sense.");
+      return 1;
+    }
+    if (val > NR_INSTANCES_MAX) {
+      ERROR(PLUGIN_NAME " plugin: Instances=%f > NR_INSTANCES_MAX=%i"
+                        " use a lower setting or recompile the plugin.",
+            val, NR_INSTANCES_MAX);
+      return 1;
+    }
+
+    nr_instances = (int)val;
+    DEBUG(PLUGIN_NAME " plugin: configured %i instances", nr_instances);
+    return 0;
+  }
+
+  if (strcasecmp(key, "ExtraStats") == 0) {
+    char *localvalue = strdup(value);
+    if (localvalue != NULL) {
+      char *exstats[EX_STATS_MAX_FIELDS];
+      int numexstats =
+          strsplit(localvalue, exstats, STATIC_ARRAY_SIZE(exstats));
+      extra_stats = parse_ex_stats_flags(exstats, numexstats);
+      sfree(localvalue);
+
+#ifdef HAVE_JOB_STATS
+      if ((extra_stats & ex_stats_job_stats_completed) &&
+          (extra_stats & ex_stats_job_stats_background)) {
+        ERROR(PLUGIN_NAME " plugin: Invalid job stats configuration. Only one "
+                          "type of job statistics can be collected at the same "
+                          "time");
+        return 1;
+      }
+#endif
+    }
+  }
+
   /* Unrecognised option. */
   return -1;
 }
 
-static int lv_read(void) {
-  time_t t;
-
+static int lv_connect(void) {
   if (conn == NULL) {
-    /* `conn_string == NULL' is acceptable. */
-    conn = virConnectOpenReadOnly(conn_string);
+/* `conn_string == NULL' is acceptable */
+#ifdef HAVE_FS_INFO
+    /* virDomainGetFSInfo requires full read-write access connection */
+    if (extra_stats & ex_stats_fs_info)
+      conn = virConnectOpen(conn_string);
+    else
+#endif
+      conn = virConnectOpenReadOnly(conn_string);
     if (conn == NULL) {
       c_complain(LOG_ERR, &conn_complain,
                  PLUGIN_NAME " plugin: Unable to connect: "
-                             "virConnectOpenReadOnly failed.");
+                             "virConnectOpen failed.");
+      return -1;
+    }
+    int status = virNodeGetInfo(conn, &nodeinfo);
+    if (status != 0) {
+      ERROR(PLUGIN_NAME ": virNodeGetInfo failed");
       return -1;
     }
   }
   c_release(LOG_NOTICE, &conn_complain,
             PLUGIN_NAME " plugin: Connection established.");
+  return 0;
+}
+
+static void lv_disconnect(void) {
+  if (conn != NULL)
+    virConnectClose(conn);
+  conn = NULL;
+  WARNING(PLUGIN_NAME " plugin: closed connection to libvirt");
+}
+
+static int lv_domain_block_info(virDomainPtr dom, const char *path,
+                                struct lv_block_info *binfo) {
+#ifdef HAVE_BLOCK_STATS_FLAGS
+  int nparams = 0;
+  if (virDomainBlockStatsFlags(dom, path, NULL, &nparams, 0) < 0 ||
+      nparams <= 0) {
+    VIRT_ERROR(conn, "getting the disk params count");
+    return -1;
+  }
+
+  virTypedParameterPtr params = calloc((size_t)nparams, sizeof(*params));
+  if (params == NULL) {
+    ERROR("virt plugin: alloc(%i) for block=%s parameters failed.", nparams,
+          path);
+    return -1;
+  }
+
+  int rc = -1;
+  if (virDomainBlockStatsFlags(dom, path, params, &nparams, 0) < 0) {
+    VIRT_ERROR(conn, "getting the disk params values");
+  } else {
+    rc = get_block_info(binfo, params, nparams);
+  }
+
+  virTypedParamsClear(params, nparams);
+  sfree(params);
+  return rc;
+#else
+  return virDomainBlockStats(dom, path, &(binfo->bi), sizeof(binfo->bi));
+#endif /* HAVE_BLOCK_STATS_FLAGS */
+}
+
+#ifdef HAVE_PERF_STATS
+static void perf_submit(virDomainStatsRecordPtr stats) {
+  for (int i = 0; i < stats->nparams; ++i) {
+    /* Replace '.' with '_' in event field to match other metrics' naming
+     * convention */
+    char *c = strchr(stats->params[i].field, '.');
+    if (c)
+      *c = '_';
+    submit(stats->dom, "perf", stats->params[i].field,
+           &(value_t){.derive = stats->params[i].value.ul}, 1);
+  }
+}
+
+static int get_perf_events(virDomainPtr domain) {
+  virDomainStatsRecordPtr *stats = NULL;
+  /* virDomainListGetStats requires a NULL terminated list of domains */
+  virDomainPtr domain_array[] = {domain, NULL};
+
+  int status =
+      virDomainListGetStats(domain_array, VIR_DOMAIN_STATS_PERF, &stats, 0);
+  if (status == -1) {
+    ERROR("virt plugin: virDomainListGetStats failed with status %i.", status);
+    return status;
+  }
+
+  for (int i = 0; i < status; ++i)
+    perf_submit(stats[i]);
+
+  virDomainStatsRecordListFree(stats);
+  return 0;
+}
+#endif /* HAVE_PERF_STATS */
+
+static void vcpu_pin_submit(virDomainPtr dom, int max_cpus, int vcpu,
+                            unsigned char *cpu_maps, int cpu_map_len) {
+  for (int cpu = 0; cpu < max_cpus; ++cpu) {
+    char type_instance[DATA_MAX_NAME_LEN];
+    _Bool is_set = VIR_CPU_USABLE(cpu_maps, cpu_map_len, vcpu, cpu) ? 1 : 0;
+
+    snprintf(type_instance, sizeof(type_instance), "vcpu_%d-cpu_%d", vcpu, cpu);
+    submit(dom, "cpu_affinity", type_instance, &(value_t){.gauge = is_set}, 1);
+  }
+}
+
+static int get_vcpu_stats(virDomainPtr domain, unsigned short nr_virt_cpu) {
+  int max_cpus = VIR_NODEINFO_MAXCPUS(nodeinfo);
+  int cpu_map_len = VIR_CPU_MAPLEN(max_cpus);
+
+  virVcpuInfoPtr vinfo = calloc(nr_virt_cpu, sizeof(vinfo[0]));
+  if (vinfo == NULL) {
+    ERROR(PLUGIN_NAME " plugin: malloc failed.");
+    return -1;
+  }
+
+  unsigned char *cpumaps = calloc(nr_virt_cpu, cpu_map_len);
+  if (cpumaps == NULL) {
+    ERROR(PLUGIN_NAME " plugin: malloc failed.");
+    sfree(vinfo);
+    return -1;
+  }
+
+  int status =
+      virDomainGetVcpus(domain, vinfo, nr_virt_cpu, cpumaps, cpu_map_len);
+  if (status < 0) {
+    ERROR(PLUGIN_NAME " plugin: virDomainGetVcpus failed with status %i.",
+          status);
+    sfree(cpumaps);
+    sfree(vinfo);
+    return status;
+  }
+
+  for (int i = 0; i < nr_virt_cpu; ++i) {
+    vcpu_submit(vinfo[i].cpuTime, domain, vinfo[i].number, "virt_vcpu");
+    if (extra_stats & ex_stats_vcpupin)
+      vcpu_pin_submit(domain, max_cpus, i, cpumaps, cpu_map_len);
+  }
+
+  sfree(cpumaps);
+  sfree(vinfo);
+  return 0;
+}
+
+#ifdef HAVE_DOM_REASON
+static int get_domain_state(virDomainPtr domain) {
+  int domain_state = 0;
+  int domain_reason = 0;
+
+  int status = virDomainGetState(domain, &domain_state, &domain_reason, 0);
+  if (status != 0) {
+    ERROR(PLUGIN_NAME " plugin: virDomainGetState failed with status %i.",
+          status);
+    return status;
+  }
+
+  domain_state_submit(domain, domain_state, domain_reason);
+  return status;
+}
+#endif /* HAVE_DOM_REASON */
+
+static int get_memory_stats(virDomainPtr domain) {
+  virDomainMemoryStatPtr minfo =
+      calloc(VIR_DOMAIN_MEMORY_STAT_NR, sizeof(virDomainMemoryStatStruct));
+  if (minfo == NULL) {
+    ERROR("virt plugin: malloc failed.");
+    return -1;
+  }
+
+  int mem_stats =
+      virDomainMemoryStats(domain, minfo, VIR_DOMAIN_MEMORY_STAT_NR, 0);
+  if (mem_stats < 0) {
+    ERROR("virt plugin: virDomainMemoryStats failed with mem_stats %i.",
+          mem_stats);
+    sfree(minfo);
+    return mem_stats;
+  }
+
+  for (int i = 0; i < mem_stats; i++)
+    memory_stats_submit((gauge_t)minfo[i].val * 1024, domain, minfo[i].tag);
+
+  sfree(minfo);
+  return 0;
+}
+
+#ifdef HAVE_DISK_ERR
+static void disk_err_submit(virDomainPtr domain,
+                            virDomainDiskErrorPtr disk_err) {
+  submit(domain, "disk_error", disk_err->disk,
+         &(value_t){.gauge = disk_err->error}, 1);
+}
+
+static int get_disk_err(virDomainPtr domain) {
+  /* Get preferred size of disk errors array */
+  int disk_err_count = virDomainGetDiskErrors(domain, NULL, 0, 0);
+  if (disk_err_count == -1) {
+    ERROR(PLUGIN_NAME
+          " plugin: failed to get preferred size of disk errors array");
+    return -1;
+  }
+
+  DEBUG(PLUGIN_NAME
+        " plugin: preferred size of disk errors array: %d for domain %s",
+        disk_err_count, virDomainGetName(domain));
+  virDomainDiskError disk_err[disk_err_count];
+
+  disk_err_count = virDomainGetDiskErrors(domain, disk_err, disk_err_count, 0);
+  if (disk_err_count == -1) {
+    ERROR(PLUGIN_NAME " plugin: virDomainGetDiskErrors failed with status %d",
+          disk_err_count);
+    return -1;
+  }
+
+  DEBUG(PLUGIN_NAME " plugin: detected %d disk errors in domain %s",
+        disk_err_count, virDomainGetName(domain));
+
+  for (int i = 0; i < disk_err_count; ++i) {
+    disk_err_submit(domain, &disk_err[i]);
+    sfree(disk_err[i].disk);
+  }
+
+  return 0;
+}
+#endif /* HAVE_DISK_ERR */
+
+static int get_block_stats(struct block_device *block_dev) {
+
+  if (!block_dev) {
+    ERROR(PLUGIN_NAME " plugin: get_block_stats NULL pointer");
+    return -1;
+  }
+
+  struct lv_block_info binfo;
+  init_block_info(&binfo);
+
+  if (lv_domain_block_info(block_dev->dom, block_dev->path, &binfo) < 0) {
+    ERROR(PLUGIN_NAME " plugin: lv_domain_block_info failed");
+    return -1;
+  }
+
+  disk_submit(&binfo, block_dev->dom, block_dev->path);
+  return 0;
+}
+
+#ifdef HAVE_FS_INFO
+
+#define NM_ADD_ITEM(_fun, _name, _val)                                         \
+  do {                                                                         \
+    ret = _fun(&notif, _name, _val);                                           \
+    if (ret != 0) {                                                            \
+      ERROR(PLUGIN_NAME " plugin: failed to add notification metadata");       \
+      goto cleanup;                                                            \
+    }                                                                          \
+  } while (0)
+
+#define NM_ADD_STR_ITEMS(_items, _size)                                        \
+  do {                                                                         \
+    for (int _i = 0; _i < _size; ++_i) {                                       \
+      DEBUG(PLUGIN_NAME                                                        \
+            " plugin: Adding notification metadata name=%s value=%s",          \
+            _items[_i].name, _items[_i].value);                                \
+      NM_ADD_ITEM(plugin_notification_meta_add_string, _items[_i].name,        \
+                  _items[_i].value);                                           \
+    }                                                                          \
+  } while (0)
+
+static int fs_info_notify(virDomainPtr domain, virDomainFSInfoPtr fs_info) {
+  notification_t notif;
+  int ret = 0;
+
+  /* Local struct, just for the purpose of this function. */
+  typedef struct nm_str_item_s {
+    const char *name;
+    const char *value;
+  } nm_str_item_t;
+
+  nm_str_item_t fs_dev_alias[fs_info->ndevAlias];
+  nm_str_item_t fs_str_items[] = {
+      {.name = "mountpoint", .value = fs_info->mountpoint},
+      {.name = "name", .value = fs_info->name},
+      {.name = "fstype", .value = fs_info->fstype}};
+
+  for (int i = 0; i < fs_info->ndevAlias; ++i) {
+    fs_dev_alias[i].name = "devAlias";
+    fs_dev_alias[i].value = fs_info->devAlias[i];
+  }
+
+  init_notif(&notif, domain, NOTIF_OKAY, "File system information",
+             "file_system", NULL);
+  NM_ADD_STR_ITEMS(fs_str_items, STATIC_ARRAY_SIZE(fs_str_items));
+  NM_ADD_ITEM(plugin_notification_meta_add_unsigned_int, "ndevAlias",
+              fs_info->ndevAlias);
+  NM_ADD_STR_ITEMS(fs_dev_alias, fs_info->ndevAlias);
+
+  plugin_dispatch_notification(&notif);
+
+cleanup:
+  if (notif.meta)
+    plugin_notification_meta_free(notif.meta);
+  return ret;
+}
+
+#undef RETURN_ON_ERR
+#undef NM_ADD_STR_ITEMS
+
+static int get_fs_info(virDomainPtr domain) {
+  virDomainFSInfoPtr *fs_info = NULL;
+  int ret = 0;
+
+  int mount_points_cnt = virDomainGetFSInfo(domain, &fs_info, 0);
+  if (mount_points_cnt == -1) {
+    ERROR(PLUGIN_NAME " plugin: virDomainGetFSInfo failed: %d",
+          mount_points_cnt);
+    return mount_points_cnt;
+  }
+
+  for (int i = 0; i < mount_points_cnt; ++i) {
+    if (fs_info_notify(domain, fs_info[i]) != 0) {
+      ERROR(PLUGIN_NAME " plugin: failed to send file system notification "
+                        "for mount point %s",
+            fs_info[i]->mountpoint);
+      ret = -1;
+    }
+    virDomainFSInfoFree(fs_info[i]);
+  }
+
+  sfree(fs_info);
+  return ret;
+}
+
+#endif /* HAVE_FS_INFO */
+
+#ifdef HAVE_JOB_STATS
+static void job_stats_submit(virDomainPtr domain, virTypedParameterPtr param) {
+  value_t vl = {0};
+
+  if (param->type == VIR_TYPED_PARAM_INT)
+    vl.derive = param->value.i;
+  else if (param->type == VIR_TYPED_PARAM_UINT)
+    vl.derive = param->value.ui;
+  else if (param->type == VIR_TYPED_PARAM_LLONG)
+    vl.derive = param->value.l;
+  else if (param->type == VIR_TYPED_PARAM_ULLONG)
+    vl.derive = param->value.ul;
+  else if (param->type == VIR_TYPED_PARAM_DOUBLE)
+    vl.derive = param->value.d;
+  else if (param->type == VIR_TYPED_PARAM_BOOLEAN)
+    vl.derive = param->value.b;
+  else if (param->type == VIR_TYPED_PARAM_STRING) {
+    submit_notif(domain, NOTIF_OKAY, param->value.s, "job_stats", param->field);
+    return;
+  } else {
+    ERROR(PLUGIN_NAME " plugin: unrecognized virTypedParameterType");
+    return;
+  }
+
+  submit(domain, "job_stats", param->field, &vl, 1);
+}
+
+static int get_job_stats(virDomainPtr domain) {
+  int ret = 0;
+  int job_type = 0;
+  int nparams = 0;
+  virTypedParameterPtr params = NULL;
+  int flags = (extra_stats & ex_stats_job_stats_completed)
+                  ? VIR_DOMAIN_JOB_STATS_COMPLETED
+                  : 0;
+
+  ret = virDomainGetJobStats(domain, &job_type, &params, &nparams, flags);
+  if (ret != 0) {
+    ERROR(PLUGIN_NAME " plugin: virDomainGetJobStats failed: %d", ret);
+    return ret;
+  }
+
+  DEBUG(PLUGIN_NAME " plugin: job_type=%d nparams=%d", job_type, nparams);
+
+  for (int i = 0; i < nparams; ++i) {
+    DEBUG(PLUGIN_NAME " plugin: param[%d] field=%s type=%d", i, params[i].field,
+          params[i].type);
+    job_stats_submit(domain, &params[i]);
+  }
+
+  virTypedParamsFree(params, nparams);
+  return ret;
+}
+#endif /* HAVE_JOB_STATS */
+
+static int get_domain_metrics(domain_t *domain) {
+  struct lv_info info;
+
+  if (!domain || !domain->ptr) {
+    ERROR(PLUGIN_NAME ": get_domain_metrics: NULL pointer");
+    return -1;
+  }
+
+  init_lv_info(&info);
+  int status = lv_domain_info(domain->ptr, &info);
+  if (status != 0) {
+    ERROR(PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
+          status);
+    return -1;
+  }
+
+  if (extra_stats & ex_stats_domain_state) {
+#ifdef HAVE_DOM_REASON
+    /* At this point we already know domain's state from virDomainGetInfo call,
+     * however it doesn't provide a reason for entering particular state.
+     * We need to get it from virDomainGetState.
+     */
+    GET_STATS(get_domain_state, "domain reason", domain->ptr);
+#else
+    /* virDomainGetState is not available. Submit 0, which corresponds to
+     * unknown reason. */
+    domain_state_submit(domain->ptr, info.di.state, 0);
+#endif
+  }
+
+  /* Gather remaining stats only for running domains */
+  if (info.di.state != VIR_DOMAIN_RUNNING)
+    return 0;
+
+  pcpu_submit(domain->ptr, &info);
+  cpu_submit(domain, info.di.cpuTime);
+
+  memory_submit(domain->ptr, (gauge_t)info.di.memory * 1024);
+
+  GET_STATS(get_vcpu_stats, "vcpu stats", domain->ptr, info.di.nrVirtCpu);
+  GET_STATS(get_memory_stats, "memory stats", domain->ptr);
+
+#ifdef HAVE_PERF_STATS
+  if (extra_stats & ex_stats_perf)
+    GET_STATS(get_perf_events, "performance monitoring events", domain->ptr);
+#endif
+
+#ifdef HAVE_FS_INFO
+  if (extra_stats & ex_stats_fs_info)
+    GET_STATS(get_fs_info, "file system info", domain->ptr);
+#endif
+
+#ifdef HAVE_DISK_ERR
+  if (extra_stats & ex_stats_disk_err)
+    GET_STATS(get_disk_err, "disk errors", domain->ptr);
+#endif
+
+#ifdef HAVE_JOB_STATS
+  if (extra_stats &
+      (ex_stats_job_stats_completed | ex_stats_job_stats_background))
+    GET_STATS(get_job_stats, "job stats", domain->ptr);
+#endif
+
+  /* Update cached virDomainInfo. It has to be done after cpu_submit */
+  memcpy(&domain->info, &info.di, sizeof(domain->info));
+  return 0;
+}
+
+static int get_if_dev_stats(struct interface_device *if_dev) {
+  virDomainInterfaceStatsStruct stats = {0};
+  char *display_name = NULL;
+
+  if (!if_dev) {
+    ERROR(PLUGIN_NAME " plugin: get_if_dev_stats: NULL pointer");
+    return -1;
+  }
+
+  switch (interface_format) {
+  case if_address:
+    display_name = if_dev->address;
+    break;
+  case if_number:
+    display_name = if_dev->number;
+    break;
+  case if_name:
+  default:
+    display_name = if_dev->path;
+  }
+
+  if (virDomainInterfaceStats(if_dev->dom, if_dev->path, &stats,
+                              sizeof(stats)) != 0) {
+    ERROR(PLUGIN_NAME " plugin: virDomainInterfaceStats failed");
+    return -1;
+  }
+
+  if ((stats.rx_bytes != -1) && (stats.tx_bytes != -1))
+    submit_derive2("if_octets", (derive_t)stats.rx_bytes,
+                   (derive_t)stats.tx_bytes, if_dev->dom, display_name);
+
+  if ((stats.rx_packets != -1) && (stats.tx_packets != -1))
+    submit_derive2("if_packets", (derive_t)stats.rx_packets,
+                   (derive_t)stats.tx_packets, if_dev->dom, display_name);
+
+  if ((stats.rx_errs != -1) && (stats.tx_errs != -1))
+    submit_derive2("if_errors", (derive_t)stats.rx_errs,
+                   (derive_t)stats.tx_errs, if_dev->dom, display_name);
+
+  if ((stats.rx_drop != -1) && (stats.tx_drop != -1))
+    submit_derive2("if_dropped", (derive_t)stats.rx_drop,
+                   (derive_t)stats.tx_drop, if_dev->dom, display_name);
+  return 0;
+}
+
+static int lv_read(user_data_t *ud) {
+  time_t t;
+  struct lv_read_instance *inst = NULL;
+  struct lv_read_state *state = NULL;
+
+  if (ud->data == NULL) {
+    ERROR(PLUGIN_NAME " plugin: NULL userdata");
+    return -1;
+  }
+
+  inst = ud->data;
+  state = &inst->read_state;
+
+  if (inst->id == 0) {
+    if (lv_connect() < 0)
+      return -1;
+  }
 
   time(&t);
 
   /* Need to refresh domain or device lists? */
   if ((last_refresh == (time_t)0) ||
       ((interval > 0) && ((last_refresh + interval) <= t))) {
-    if (refresh_lists() != 0) {
-      if (conn != NULL)
-        virConnectClose(conn);
-      conn = NULL;
+    if (refresh_lists(inst) != 0) {
+      if (inst->id == 0)
+        lv_disconnect();
       return -1;
     }
     last_refresh = t;
   }
 
 #if 0
     for (int i = 0; i < nr_domains; ++i)
-        fprintf (stderr, "domain %s\n", virDomainGetName (domains[i]));
+        fprintf (stderr, "domain %s\n", virDomainGetName (state->domains[i].ptr));
     for (int i = 0; i < nr_block_devices; ++i)
         fprintf  (stderr, "block device %d %s:%s\n",
                   i, virDomainGetName (block_devices[i].dom),
                   block_devices[i].path);
     for (int i = 0; i < nr_interface_devices; ++i)
         fprintf (stderr, "interface device %d %s:%s\n",
                  i, virDomainGetName (interface_devices[i].dom),
                  interface_devices[i].path);
 #endif
 
-  /* Get CPU usage, memory, VCPU usage for each domain. */
-  for (int i = 0; i < nr_domains; ++i) {
-    virDomainInfo info;
-    virVcpuInfoPtr vinfo = NULL;
-    virDomainMemoryStatPtr minfo = NULL;
-    int status;
-
-    status = virDomainGetInfo(domains[i], &info);
-    if (status != 0) {
-      ERROR(PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
-            status);
-      continue;
-    }
-
-    if (info.state != VIR_DOMAIN_RUNNING) {
-      /* only gather stats for running domains */
-      continue;
-    }
+  /* Get domains' metrics */
+  for (int i = 0; i < state->nr_domains; ++i) {
+    int status = get_domain_metrics(&state->domains[i]);
+    if (status != 0)
+      ERROR(PLUGIN_NAME " failed to get metrics for domain=%s",
+            virDomainGetName(state->domains[i].ptr));
+  }
 
-    cpu_submit(info.cpuTime, domains[i], "virt_cpu_total");
-    memory_submit((gauge_t)info.memory * 1024, domains[i]);
+  /* Get block device stats for each domain. */
+  for (int i = 0; i < state->nr_block_devices; ++i) {
+    int status = get_block_stats(&state->block_devices[i]);
+    if (status != 0)
+      ERROR(PLUGIN_NAME
+            " failed to get stats for block device (%s) in domain %s",
+            state->block_devices[i].path,
+            virDomainGetName(state->domains[i].ptr));
+  }
 
-    vinfo = malloc(info.nrVirtCpu * sizeof(vinfo[0]));
-    if (vinfo == NULL) {
-      ERROR(PLUGIN_NAME " plugin: malloc failed.");
-      continue;
-    }
+  /* Get interface stats for each domain. */
+  for (int i = 0; i < state->nr_interface_devices; ++i) {
+    int status = get_if_dev_stats(&state->interface_devices[i]);
+    if (status != 0)
+      ERROR(PLUGIN_NAME
+            " failed to get interface stats for device (%s) in domain %s",
+            state->interface_devices[i].path,
+            virDomainGetName(state->interface_devices[i].dom));
+  }
 
-    status = virDomainGetVcpus(domains[i], vinfo, info.nrVirtCpu,
-                               /* cpu map = */ NULL, /* cpu map length = */ 0);
-    if (status < 0) {
-      ERROR(PLUGIN_NAME " plugin: virDomainGetVcpus failed with status %i.",
-            status);
-      sfree(vinfo);
-      continue;
-    }
+  return 0;
+}
 
-    for (int j = 0; j < info.nrVirtCpu; ++j)
-      vcpu_submit(vinfo[j].cpuTime, domains[i], vinfo[j].number, "virt_vcpu");
+static int lv_init_instance(size_t i, plugin_read_cb callback) {
+  struct lv_user_data *lv_ud = &(lv_read_user_data[i]);
+  struct lv_read_instance *inst = &(lv_ud->inst);
 
-    sfree(vinfo);
+  memset(lv_ud, 0, sizeof(*lv_ud));
 
-    minfo =
-        malloc(VIR_DOMAIN_MEMORY_STAT_NR * sizeof(virDomainMemoryStatStruct));
-    if (minfo == NULL) {
-      ERROR("virt plugin: malloc failed.");
-      continue;
-    }
+  snprintf(inst->tag, sizeof(inst->tag), "%s-%zu", PLUGIN_NAME, i);
+  inst->id = i;
 
-    status =
-        virDomainMemoryStats(domains[i], minfo, VIR_DOMAIN_MEMORY_STAT_NR, 0);
+  user_data_t *ud = &(lv_ud->ud);
+  ud->data = inst;
+  ud->free_func = NULL;
 
-    if (status < 0) {
-      ERROR("virt plugin: virDomainMemoryStats failed with status %i.", status);
-      sfree(minfo);
-      continue;
-    }
+  INFO(PLUGIN_NAME " plugin: reader %s initialized", inst->tag);
+  return plugin_register_complex_read(NULL, inst->tag, callback, 0, ud);
+}
 
-    for (int j = 0; j < status; j++) {
-      memory_stats_submit((gauge_t)minfo[j].val * 1024, domains[i],
-                          minfo[j].tag);
-    }
+static void lv_clean_read_state(struct lv_read_state *state) {
+  free_block_devices(state);
+  free_interface_devices(state);
+  free_domains(state);
+}
 
-    sfree(minfo);
-  }
+static void lv_fini_instance(size_t i) {
+  struct lv_read_instance *inst = &(lv_read_user_data[i].inst);
+  struct lv_read_state *state = &(inst->read_state);
 
-  /* Get block device stats for each domain. */
-  for (int i = 0; i < nr_block_devices; ++i) {
-    struct _virDomainBlockStats stats;
+  lv_clean_read_state(state);
+  INFO(PLUGIN_NAME " plugin: reader %s finalized", inst->tag);
+}
 
-    if (virDomainBlockStats(block_devices[i].dom, block_devices[i].path, &stats,
-                            sizeof stats) != 0)
-      continue;
+static int lv_init(void) {
+  if (virInitialize() != 0)
+    return -1;
 
-    char *type_instance = NULL;
-    if (blockdevice_format_basename && blockdevice_format == source)
-      type_instance = strdup(basename(block_devices[i].path));
-    else
-      type_instance = strdup(block_devices[i].path);
+  if (lv_connect() != 0)
+    return -1;
 
-    if ((stats.rd_req != -1) && (stats.wr_req != -1))
-      submit_derive2("disk_ops", (derive_t)stats.rd_req, (derive_t)stats.wr_req,
-                     block_devices[i].dom, type_instance);
-
-    if ((stats.rd_bytes != -1) && (stats.wr_bytes != -1))
-      submit_derive2("disk_octets", (derive_t)stats.rd_bytes,
-                     (derive_t)stats.wr_bytes, block_devices[i].dom,
-                     type_instance);
+  DEBUG(PLUGIN_NAME " plugin: starting %i instances", nr_instances);
 
-    sfree(type_instance);
-  } /* for (nr_block_devices) */
+  for (int i = 0; i < nr_instances; ++i)
+    lv_init_instance(i, lv_read);
 
-  /* Get interface stats for each domain. */
-  for (int i = 0; i < nr_interface_devices; ++i) {
-    struct _virDomainInterfaceStats stats;
-    char *display_name = NULL;
-
-    switch (interface_format) {
-    case if_address:
-      display_name = interface_devices[i].address;
-      break;
-    case if_number:
-      display_name = interface_devices[i].number;
-      break;
-    case if_name:
-    default:
-      display_name = interface_devices[i].path;
-    }
+  return 0;
+}
 
-    if (virDomainInterfaceStats(interface_devices[i].dom,
-                                interface_devices[i].path, &stats,
-                                sizeof stats) != 0)
-      continue;
+/*
+ * returns 0 on success and <0 on error
+ */
+static int lv_domain_get_tag(xmlXPathContextPtr xpath_ctx, const char *dom_name,
+                             char *dom_tag) {
+  char xpath_str[BUFFER_MAX_LEN] = {'\0'};
+  xmlXPathObjectPtr xpath_obj = NULL;
+  xmlNodePtr xml_node = NULL;
+  int ret = -1;
+  int err;
+
+  err = xmlXPathRegisterNs(xpath_ctx,
+                           (const xmlChar *)METADATA_VM_PARTITION_PREFIX,
+                           (const xmlChar *)METADATA_VM_PARTITION_URI);
+  if (err) {
+    ERROR(PLUGIN_NAME " plugin: xmlXpathRegisterNs(%s, %s) failed on domain %s",
+          METADATA_VM_PARTITION_PREFIX, METADATA_VM_PARTITION_URI, dom_name);
+    goto done;
+  }
+
+  snprintf(xpath_str, sizeof(xpath_str), "/domain/metadata/%s:%s/text()",
+           METADATA_VM_PARTITION_PREFIX, METADATA_VM_PARTITION_ELEMENT);
+  xpath_obj = xmlXPathEvalExpression((xmlChar *)xpath_str, xpath_ctx);
+  if (xpath_obj == NULL) {
+    ERROR(PLUGIN_NAME " plugin: xmlXPathEval(%s) failed on domain %s",
+          xpath_str, dom_name);
+    goto done;
+  }
+
+  if (xpath_obj->type != XPATH_NODESET) {
+    ERROR(PLUGIN_NAME " plugin: xmlXPathEval(%s) unexpected return type %d "
+                      "(wanted %d) on domain %s",
+          xpath_str, xpath_obj->type, XPATH_NODESET, dom_name);
+    goto done;
+  }
+
+  /*
+   * from now on there is no real error, it's ok if a domain
+   * doesn't have the metadata partition tag.
+   */
+  ret = 0;
+  if (xpath_obj->nodesetval == NULL || xpath_obj->nodesetval->nodeNr != 1) {
+    DEBUG(PLUGIN_NAME " plugin: xmlXPathEval(%s) return nodeset size=%i "
+                      "expected=1 on domain %s",
+          xpath_str,
+          (xpath_obj->nodesetval == NULL) ? 0 : xpath_obj->nodesetval->nodeNr,
+          dom_name);
+  } else {
+    xml_node = xpath_obj->nodesetval->nodeTab[0];
+    sstrncpy(dom_tag, (const char *)xml_node->content, PARTITION_TAG_MAX_LEN);
+  }
+
+done:
+  /* deregister to clean up */
+  err = xmlXPathRegisterNs(xpath_ctx,
+                           (const xmlChar *)METADATA_VM_PARTITION_PREFIX, NULL);
+  if (err) {
+    /* we can't really recover here */
+    ERROR(PLUGIN_NAME
+          " plugin: deregistration of namespace %s failed for domain %s",
+          METADATA_VM_PARTITION_PREFIX, dom_name);
+  }
+  if (xpath_obj)
+    xmlXPathFreeObject(xpath_obj);
 
-    if ((stats.rx_bytes != -1) && (stats.tx_bytes != -1))
-      submit_derive2("if_octets", (derive_t)stats.rx_bytes,
-                     (derive_t)stats.tx_bytes, interface_devices[i].dom,
-                     display_name);
+  return ret;
+}
 
-    if ((stats.rx_packets != -1) && (stats.tx_packets != -1))
-      submit_derive2("if_packets", (derive_t)stats.rx_packets,
-                     (derive_t)stats.tx_packets, interface_devices[i].dom,
-                     display_name);
+static int is_known_tag(const char *dom_tag) {
+  for (int i = 0; i < nr_instances; ++i)
+    if (!strcmp(dom_tag, lv_read_user_data[i].inst.tag))
+      return 1;
+  return 0;
+}
 
-    if ((stats.rx_errs != -1) && (stats.tx_errs != -1))
-      submit_derive2("if_errors", (derive_t)stats.rx_errs,
-                     (derive_t)stats.tx_errs, interface_devices[i].dom,
-                     display_name);
+static int lv_instance_include_domain(struct lv_read_instance *inst,
+                                      const char *dom_name,
+                                      const char *dom_tag) {
+  if ((dom_tag[0] != '\0') && (strcmp(dom_tag, inst->tag) == 0))
+    return 1;
 
-    if ((stats.rx_drop != -1) && (stats.tx_drop != -1))
-      submit_derive2("if_dropped", (derive_t)stats.rx_drop,
-                     (derive_t)stats.tx_drop, interface_devices[i].dom,
-                     display_name);
-  } /* for (nr_interface_devices) */
+  /* instance#0 will always be there, so it is in charge of extra duties */
+  if (inst->id == 0) {
+    if (dom_tag[0] == '\0' || !is_known_tag(dom_tag)) {
+      DEBUG(PLUGIN_NAME " plugin#%s: refreshing domain %s "
+                        "with unknown tag '%s'",
+            inst->tag, dom_name, dom_tag);
+      return 1;
+    }
+  }
 
   return 0;
 }
 
-static int refresh_lists(void) {
+/*
+  virConnectListAllDomains() appeared in 0.10.2
+  Note that LIBVIR_CHECK_VERSION appeared a year later, so
+  in some systems which actually have virConnectListAllDomains()
+  we can't detect this.
+ */
+#ifdef LIBVIR_CHECK_VERSION
+#if LIBVIR_CHECK_VERSION(0, 10, 2)
+#define HAVE_LIST_ALL_DOMAINS 1
+#endif
+#endif
+
+static int refresh_lists(struct lv_read_instance *inst) {
+  struct lv_read_state *state = &inst->read_state;
   int n;
 
   n = virConnectNumOfDomains(conn);
   if (n < 0) {
     VIRT_ERROR(conn, "reading number of domains");
     return -1;
   }
 
+  lv_clean_read_state(state);
+
   if (n > 0) {
+#ifdef HAVE_LIST_ALL_DOMAINS
+    virDomainPtr *domains;
+    n = virConnectListAllDomains(conn, &domains,
+                                 VIR_CONNECT_LIST_DOMAINS_ACTIVE);
+#else
     int *domids;
 
     /* Get list of domains. */
     domids = malloc(sizeof(*domids) * n);
     if (domids == NULL) {
       ERROR(PLUGIN_NAME " plugin: malloc failed.");
       return -1;
     }
 
     n = virConnectListDomains(conn, domids, n);
+#endif
+
     if (n < 0) {
       VIRT_ERROR(conn, "reading list of domains");
+#ifndef HAVE_LIST_ALL_DOMAINS
       sfree(domids);
+#endif
       return -1;
     }
 
-    free_block_devices();
-    free_interface_devices();
-    free_domains();
-
     /* Fetch each domain and add it to the list, unless ignore. */
     for (int i = 0; i < n; ++i) {
-      virDomainPtr dom = NULL;
       const char *name;
       char *xml = NULL;
       xmlDocPtr xml_doc = NULL;
       xmlXPathContextPtr xpath_ctx = NULL;
       xmlXPathObjectPtr xpath_obj = NULL;
-
+      char tag[PARTITION_TAG_MAX_LEN] = {'\0'};
+      virDomainInfo info;
+      int status;
+
+#ifdef HAVE_LIST_ALL_DOMAINS
+      virDomainPtr dom = domains[i];
+#else
+      virDomainPtr dom = NULL;
       dom = virDomainLookupByID(conn, domids[i]);
       if (dom == NULL) {
         VIRT_ERROR(conn, "virDomainLookupByID");
         /* Could be that the domain went away -- ignore it anyway. */
         continue;
       }
+#endif
 
       name = virDomainGetName(dom);
       if (name == NULL) {
         VIRT_ERROR(conn, "virDomainGetName");
         goto cont;
       }
 
-      if (il_domains && ignorelist_match(il_domains, name) != 0)
-        goto cont;
+      status = virDomainGetInfo(dom, &info);
+      if (status != 0) {
+        ERROR(PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
+              status);
+        continue;
+      }
 
-      if (add_domain(dom) < 0) {
-        ERROR(PLUGIN_NAME " plugin: malloc failed.");
-        goto cont;
+      if (info.state != VIR_DOMAIN_RUNNING) {
+        DEBUG(PLUGIN_NAME " plugin: skipping inactive domain %s", name);
+        continue;
       }
 
+      if (il_domains && ignorelist_match(il_domains, name) != 0)
+        goto cont;
+
       /* Get a list of devices for this domain. */
       xml = virDomainGetXMLDesc(dom, 0);
       if (!xml) {
         VIRT_ERROR(conn, "virDomainGetXMLDesc");
         goto cont;
       }
