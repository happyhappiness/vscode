static int disk_read(void) {
#if HAVE_IOKIT_IOKITLIB_H
  io_registry_entry_t disk;
  io_registry_entry_t disk_child;
  io_iterator_t disk_list;
  CFMutableDictionaryRef props_dict, child_dict;
  CFDictionaryRef stats_dict;
  CFStringRef tmp_cf_string_ref;
  kern_return_t status;

  signed long long read_ops, read_byt, read_tme;
  signed long long write_ops, write_byt, write_tme;

  int disk_major, disk_minor;
  char disk_name[DATA_MAX_NAME_LEN];
  char child_disk_name_bsd[DATA_MAX_NAME_LEN],
      props_disk_name_bsd[DATA_MAX_NAME_LEN];

  /* Get the list of all disk objects. */
  if (IOServiceGetMatchingServices(
          io_master_port, IOServiceMatching(kIOBlockStorageDriverClass),
          &disk_list) != kIOReturnSuccess) {
    ERROR("disk plugin: IOServiceGetMatchingServices failed.");
    return (-1);
  }

  while ((disk = IOIteratorNext(disk_list)) != 0) {
    props_dict = NULL;
    stats_dict = NULL;
    child_dict = NULL;

    /* get child of disk entry and corresponding property dictionary */
    if ((status = IORegistryEntryGetChildEntry(
             disk, kIOServicePlane, &disk_child)) != kIOReturnSuccess) {
      /* This fails for example for DVD/CD drives, which we want to ignore
       * anyway */
      DEBUG("IORegistryEntryGetChildEntry (disk) failed: 0x%08x", status);
      IOObjectRelease(disk);
      continue;
    }
    if (IORegistryEntryCreateCFProperties(
            disk_child, (CFMutableDictionaryRef *)&child_dict,
            kCFAllocatorDefault, kNilOptions) != kIOReturnSuccess ||
        child_dict == NULL) {
      ERROR("disk plugin: IORegistryEntryCreateCFProperties (disk_child) "
            "failed.");
      IOObjectRelease(disk_child);
      IOObjectRelease(disk);
      continue;
    }

    /* extract name and major/minor numbers */
    memset(child_disk_name_bsd, 0, sizeof(child_disk_name_bsd));
    tmp_cf_string_ref =
        (CFStringRef)CFDictionaryGetValue(child_dict, CFSTR(kIOBSDNameKey));
    if (tmp_cf_string_ref) {
      assert(CFGetTypeID(tmp_cf_string_ref) == CFStringGetTypeID());
      CFStringGetCString(tmp_cf_string_ref, child_disk_name_bsd,
                         sizeof(child_disk_name_bsd), kCFStringEncodingUTF8);
    }
    disk_major = (int)dict_get_value(child_dict, kIOBSDMajorKey);
    disk_minor = (int)dict_get_value(child_dict, kIOBSDMinorKey);
    DEBUG("disk plugin: child_disk_name_bsd=\"%s\" major=%d minor=%d",
          child_disk_name_bsd, disk_major, disk_minor);
    CFRelease(child_dict);
    IOObjectRelease(disk_child);

    /* get property dictionary of the disk entry itself */
    if (IORegistryEntryCreateCFProperties(
            disk, (CFMutableDictionaryRef *)&props_dict, kCFAllocatorDefault,
            kNilOptions) != kIOReturnSuccess ||
        props_dict == NULL) {
      ERROR("disk-plugin: IORegistryEntryCreateCFProperties failed.");
      IOObjectRelease(disk);
      continue;
    }

    /* extract name and stats dictionary */
    memset(props_disk_name_bsd, 0, sizeof(props_disk_name_bsd));
    tmp_cf_string_ref =
        (CFStringRef)CFDictionaryGetValue(props_dict, CFSTR(kIOBSDNameKey));
    if (tmp_cf_string_ref) {
      assert(CFGetTypeID(tmp_cf_string_ref) == CFStringGetTypeID());
      CFStringGetCString(tmp_cf_string_ref, props_disk_name_bsd,
                         sizeof(props_disk_name_bsd), kCFStringEncodingUTF8);
    }
    stats_dict = (CFDictionaryRef)CFDictionaryGetValue(
        props_dict, CFSTR(kIOBlockStorageDriverStatisticsKey));
    if (stats_dict == NULL) {
      ERROR("disk plugin: CFDictionaryGetValue (%s) failed.",
            kIOBlockStorageDriverStatisticsKey);
      CFRelease(props_dict);
      IOObjectRelease(disk);
      continue;
    }
    DEBUG("disk plugin: props_disk_name_bsd=\"%s\"", props_disk_name_bsd);

    /* choose name */
    if (use_bsd_name) {
      if (child_disk_name_bsd[0] != 0)
        sstrncpy(disk_name, child_disk_name_bsd, sizeof(disk_name));
      else if (props_disk_name_bsd[0] != 0)
        sstrncpy(disk_name, props_disk_name_bsd, sizeof(disk_name));
      else {
        ERROR("disk plugin: can't find bsd disk name.");
        ssnprintf(disk_name, sizeof(disk_name), "%i-%i", disk_major,
                  disk_minor);
      }
    } else
      ssnprintf(disk_name, sizeof(disk_name), "%i-%i", disk_major, disk_minor);

    DEBUG("disk plugin: disk_name = \"%s\"", disk_name);

    /* check the name against ignore list */
    if (ignorelist_match(ignorelist, disk_name) != 0) {
      CFRelease(props_dict);
      IOObjectRelease(disk);
      continue;
    }

    /* extract the stats */
    read_ops =
        dict_get_value(stats_dict, kIOBlockStorageDriverStatisticsReadsKey);
    read_byt =
        dict_get_value(stats_dict, kIOBlockStorageDriverStatisticsBytesReadKey);
    read_tme = dict_get_value(stats_dict,
                              kIOBlockStorageDriverStatisticsTotalReadTimeKey);
    write_ops =
        dict_get_value(stats_dict, kIOBlockStorageDriverStatisticsWritesKey);
    write_byt = dict_get_value(stats_dict,
                               kIOBlockStorageDriverStatisticsBytesWrittenKey);
    write_tme = dict_get_value(
        stats_dict, kIOBlockStorageDriverStatisticsTotalWriteTimeKey);
    CFRelease(props_dict);
    IOObjectRelease(disk);

    /* and submit */
    if ((read_byt != -1LL) || (write_byt != -1LL))
      disk_submit(disk_name, "disk_octets", read_byt, write_byt);
    if ((read_ops != -1LL) || (write_ops != -1LL))
      disk_submit(disk_name, "disk_ops", read_ops, write_ops);
    if ((read_tme != -1LL) || (write_tme != -1LL))
      disk_submit(disk_name, "disk_time", read_tme / 1000, write_tme / 1000);
  }
  IOObjectRelease(disk_list);
/* #endif HAVE_IOKIT_IOKITLIB_H */

#elif KERNEL_FREEBSD
  int retry, dirty;

  void *snap = NULL;
  struct devstat *snap_iter;

  struct gident *geom_id;

  const char *disk_name;
  long double read_time, write_time, busy_time, total_duration;

  for (retry = 0, dirty = 1; retry < 5 && dirty == 1; retry++) {
    if (snap != NULL)
      geom_stats_snapshot_free(snap);

    /* Get a fresh copy of stats snapshot */
    snap = geom_stats_snapshot_get();
    if (snap == NULL) {
      ERROR("disk plugin: geom_stats_snapshot_get() failed.");
      return (-1);
    }

    /* Check if we have dirty read from this snapshot */
    dirty = 0;
    geom_stats_snapshot_reset(snap);
    while ((snap_iter = geom_stats_snapshot_next(snap)) != NULL) {
      if (snap_iter->id == NULL)
        continue;
      geom_id = geom_lookupid(&geom_tree, snap_iter->id);

      /* New device? refresh GEOM tree */
      if (geom_id == NULL) {
        geom_deletetree(&geom_tree);
        if (geom_gettree(&geom_tree) != 0) {
          ERROR("disk plugin: geom_gettree() failed");
          geom_stats_snapshot_free(snap);
          return (-1);
        }
        geom_id = geom_lookupid(&geom_tree, snap_iter->id);
      }
      /*
       * This should be rare: the device come right before we take the
       * snapshot and went away right after it.  We will handle this
       * case later, so don't mark dirty but silently ignore it.
       */
      if (geom_id == NULL)
        continue;

      /* Only collect PROVIDER data */
      if (geom_id->lg_what != ISPROVIDER)
        continue;

      /* Only collect data when rank is 1 (physical devices) */
      if (((struct gprovider *)(geom_id->lg_ptr))->lg_geom->lg_rank != 1)
        continue;

      /* Check if this is a dirty read quit for another try */
      if (snap_iter->sequence0 != snap_iter->sequence1) {
        dirty = 1;
        break;
      }
    }
  }

  /* Reset iterator */
  geom_stats_snapshot_reset(snap);
  for (;;) {
    snap_iter = geom_stats_snapshot_next(snap);
    if (snap_iter == NULL)
      break;

    if (snap_iter->id == NULL)
      continue;
    geom_id = geom_lookupid(&geom_tree, snap_iter->id);
    if (geom_id == NULL)
      continue;
    if (geom_id->lg_what != ISPROVIDER)
      continue;
    if (((struct gprovider *)(geom_id->lg_ptr))->lg_geom->lg_rank != 1)
      continue;
    /* Skip dirty reads, if present */
    if (dirty && (snap_iter->sequence0 != snap_iter->sequence1))
      continue;

    disk_name = ((struct gprovider *)geom_id->lg_ptr)->lg_name;

    if (ignorelist_match(ignorelist, disk_name) != 0)
      continue;

    if ((snap_iter->bytes[DEVSTAT_READ] != 0) ||
        (snap_iter->bytes[DEVSTAT_WRITE] != 0)) {
      disk_submit(disk_name, "disk_octets",
                  (derive_t)snap_iter->bytes[DEVSTAT_READ],
                  (derive_t)snap_iter->bytes[DEVSTAT_WRITE]);
    }

    if ((snap_iter->operations[DEVSTAT_READ] != 0) ||
        (snap_iter->operations[DEVSTAT_WRITE] != 0)) {
      disk_submit(disk_name, "disk_ops",
                  (derive_t)snap_iter->operations[DEVSTAT_READ],
                  (derive_t)snap_iter->operations[DEVSTAT_WRITE]);
    }

    read_time = devstat_compute_etime(&snap_iter->duration[DEVSTAT_READ], NULL);
    write_time =
        devstat_compute_etime(&snap_iter->duration[DEVSTAT_WRITE], NULL);
    if ((read_time != 0) || (write_time != 0)) {
      disk_submit(disk_name, "disk_time", (derive_t)(read_time * 1000),
                  (derive_t)(write_time * 1000));
    }
    if (devstat_compute_statistics(snap_iter, NULL, 1.0, DSM_TOTAL_BUSY_TIME,
                                   &busy_time, DSM_TOTAL_DURATION,
                                   &total_duration, DSM_NONE) != 0) {
      WARNING("%s", devstat_errbuf);
    } else {
      submit_io_time(disk_name, busy_time, total_duration);
    }
  }
  geom_stats_snapshot_free(snap);

#elif KERNEL_LINUX
  FILE *fh;
  char buffer[1024];

  char *fields[32];
  int numfields;
  int fieldshift = 0;

  int minor = 0;

  derive_t read_sectors = 0;
  derive_t write_sectors = 0;

  derive_t read_ops = 0;
  derive_t read_merged = 0;
  derive_t read_time = 0;
  derive_t write_ops = 0;
  derive_t write_merged = 0;
  derive_t write_time = 0;
  gauge_t in_progress = NAN;
  derive_t io_time = 0;
  derive_t weighted_time = 0;
  int is_disk = 0;

  diskstats_t *ds, *pre_ds;

  if ((fh = fopen("/proc/diskstats", "r")) == NULL) {
    fh = fopen("/proc/partitions", "r");
    if (fh == NULL) {
      ERROR("disk plugin: fopen (/proc/{diskstats,partitions}) failed.");
      return (-1);
    }

    /* Kernel is 2.4.* */
    fieldshift = 1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *disk_name;
    char *output_name;

    numfields = strsplit(buffer, fields, 32);

    if ((numfields != (14 + fieldshift)) && (numfields != 7))
      continue;

    minor = atoll(fields[1]);

    disk_name = fields[2 + fieldshift];

    for (ds = disklist, pre_ds = disklist; ds != NULL;
         pre_ds = ds, ds = ds->next)
      if (strcmp(disk_name, ds->name) == 0)
        break;

    if (ds == NULL) {
      if ((ds = (diskstats_t *)calloc(1, sizeof(diskstats_t))) == NULL)
        continue;

      if ((ds->name = strdup(disk_name)) == NULL) {
        free(ds);
        continue;
      }

      if (pre_ds == NULL)
        disklist = ds;
      else
        pre_ds->next = ds;
    }

    is_disk = 0;
    if (numfields == 7) {
      /* Kernel 2.6, Partition */
      read_ops = atoll(fields[3]);
      read_sectors = atoll(fields[4]);
      write_ops = atoll(fields[5]);
      write_sectors = atoll(fields[6]);
    } else if (numfields == (14 + fieldshift)) {
      read_ops = atoll(fields[3 + fieldshift]);
      write_ops = atoll(fields[7 + fieldshift]);

      read_sectors = atoll(fields[5 + fieldshift]);
      write_sectors = atoll(fields[9 + fieldshift]);

      if ((fieldshift == 0) || (minor == 0)) {
        is_disk = 1;
        read_merged = atoll(fields[4 + fieldshift]);
        read_time = atoll(fields[6 + fieldshift]);
        write_merged = atoll(fields[8 + fieldshift]);
        write_time = atoll(fields[10 + fieldshift]);

        in_progress = atof(fields[11 + fieldshift]);

        io_time = atof(fields[12 + fieldshift]);
        weighted_time = atof(fields[13 + fieldshift]);
      }
    } else {
      DEBUG("numfields = %i; => unknown file format.", numfields);
      continue;
    }

    {
      derive_t diff_read_sectors;
      derive_t diff_write_sectors;

      /* If the counter wraps around, it's only 32 bits.. */
      if (read_sectors < ds->read_sectors)
        diff_read_sectors = 1 + read_sectors + (UINT_MAX - ds->read_sectors);
      else
        diff_read_sectors = read_sectors - ds->read_sectors;
      if (write_sectors < ds->write_sectors)
        diff_write_sectors = 1 + write_sectors + (UINT_MAX - ds->write_sectors);
      else
        diff_write_sectors = write_sectors - ds->write_sectors;

      ds->read_bytes += 512 * diff_read_sectors;
      ds->write_bytes += 512 * diff_write_sectors;
      ds->read_sectors = read_sectors;
      ds->write_sectors = write_sectors;
    }

    /* Calculate the average time an io-op needs to complete */
    if (is_disk) {
      derive_t diff_read_ops;
      derive_t diff_write_ops;
      derive_t diff_read_time;
      derive_t diff_write_time;

      if (read_ops < ds->read_ops)
        diff_read_ops = 1 + read_ops + (UINT_MAX - ds->read_ops);
      else
        diff_read_ops = read_ops - ds->read_ops;
      DEBUG("disk plugin: disk_name = %s; read_ops = %" PRIi64 "; "
            "ds->read_ops = %" PRIi64 "; diff_read_ops = %" PRIi64 ";",
            disk_name, read_ops, ds->read_ops, diff_read_ops);

      if (write_ops < ds->write_ops)
        diff_write_ops = 1 + write_ops + (UINT_MAX - ds->write_ops);
      else
        diff_write_ops = write_ops - ds->write_ops;

      if (read_time < ds->read_time)
        diff_read_time = 1 + read_time + (UINT_MAX - ds->read_time);
      else
        diff_read_time = read_time - ds->read_time;

      if (write_time < ds->write_time)
        diff_write_time = 1 + write_time + (UINT_MAX - ds->write_time);
      else
        diff_write_time = write_time - ds->write_time;

      if (diff_read_ops != 0)
        ds->avg_read_time += disk_calc_time_incr(diff_read_time, diff_read_ops);
      if (diff_write_ops != 0)
        ds->avg_write_time +=
            disk_calc_time_incr(diff_write_time, diff_write_ops);

      ds->read_ops = read_ops;
      ds->read_time = read_time;
      ds->write_ops = write_ops;
      ds->write_time = write_time;

      if (read_merged || write_merged)
        ds->has_merged = 1;

      if (in_progress)
        ds->has_in_progress = 1;

      if (io_time)
        ds->has_io_time = 1;

    } /* if (is_disk) */

    /* Don't write to the RRDs if we've just started.. */
    ds->poll_count++;
    if (ds->poll_count <= 2) {
      DEBUG("disk plugin: (ds->poll_count = %i) <= "
            "(min_poll_count = 2); => Not writing.",
            ds->poll_count);
      continue;
    }

    if ((read_ops == 0) && (write_ops == 0)) {
      DEBUG("disk plugin: ((read_ops == 0) && "
            "(write_ops == 0)); => Not writing.");
      continue;
    }

    output_name = disk_name;

#if HAVE_LIBUDEV
    char *alt_name = NULL;
    if (conf_udev_name_attr != NULL) {
      alt_name =
          disk_udev_attr_name(handle_udev, disk_name, conf_udev_name_attr);
      if (alt_name != NULL)
        output_name = alt_name;
    }
#endif

    if (ignorelist_match(ignorelist, output_name) != 0) {
#if HAVE_LIBUDEV
      /* release udev-based alternate name, if allocated */
      sfree(alt_name);
#endif
      continue;
    }

    if ((ds->read_bytes != 0) || (ds->write_bytes != 0))
      disk_submit(output_name, "disk_octets", ds->read_bytes, ds->write_bytes);

    if ((ds->read_ops != 0) || (ds->write_ops != 0))
      disk_submit(output_name, "disk_ops", read_ops, write_ops);

    if ((ds->avg_read_time != 0) || (ds->avg_write_time != 0))
      disk_submit(output_name, "disk_time", ds->avg_read_time,
                  ds->avg_write_time);

    if (is_disk) {
      if (ds->has_merged)
        disk_submit(output_name, "disk_merged", read_merged, write_merged);
      if (ds->has_in_progress)
        submit_in_progress(output_name, in_progress);
      if (ds->has_io_time)
        submit_io_time(output_name, io_time, weighted_time);
    } /* if (is_disk) */

#if HAVE_LIBUDEV
    /* release udev-based alternate name, if allocated */
    sfree(alt_name);
#endif
  } /* while (fgets (buffer, sizeof (buffer), fh) != NULL) */

  fclose(fh);
/* #endif defined(KERNEL_LINUX) */

#elif HAVE_LIBKSTAT
#if HAVE_KSTAT_IO_T_WRITES && HAVE_KSTAT_IO_T_NWRITES && HAVE_KSTAT_IO_T_WTIME
#define KIO_ROCTETS reads
#define KIO_WOCTETS writes
#define KIO_ROPS nreads
#define KIO_WOPS nwrites
#define KIO_RTIME rtime
#define KIO_WTIME wtime
#elif HAVE_KSTAT_IO_T_NWRITTEN && HAVE_KSTAT_IO_T_WRITES &&                    \
    HAVE_KSTAT_IO_T_WTIME
#define KIO_ROCTETS nread
#define KIO_WOCTETS nwritten
#define KIO_ROPS reads
#define KIO_WOPS writes
#define KIO_RTIME rtime
#define KIO_WTIME wtime
#else
#error "kstat_io_t does not have the required members"
#endif
  static kstat_io_t kio;

  if (kc == NULL)
    return (-1);

  for (int i = 0; i < numdisk; i++) {
    if (kstat_read(kc, ksp[i], &kio) == -1)
      continue;

    if (strncmp(ksp[i]->ks_class, "disk", 4) == 0) {
      if (ignorelist_match(ignorelist, ksp[i]->ks_name) != 0)
        continue;

      disk_submit(ksp[i]->ks_name, "disk_octets", kio.KIO_ROCTETS,
                  kio.KIO_WOCTETS);
      disk_submit(ksp[i]->ks_name, "disk_ops", kio.KIO_ROPS, kio.KIO_WOPS);
      /* FIXME: Convert this to microseconds if necessary */
      disk_submit(ksp[i]->ks_name, "disk_time", kio.KIO_RTIME, kio.KIO_WTIME);
    } else if (strncmp(ksp[i]->ks_class, "partition", 9) == 0) {
      if (ignorelist_match(ignorelist, ksp[i]->ks_name) != 0)
        continue;

      disk_submit(ksp[i]->ks_name, "disk_octets", kio.KIO_ROCTETS,
                  kio.KIO_WOCTETS);
      disk_submit(ksp[i]->ks_name, "disk_ops", kio.KIO_ROPS, kio.KIO_WOPS);
    }
  }
/* #endif defined(HAVE_LIBKSTAT) */

#elif defined(HAVE_LIBSTATGRAB)
  sg_disk_io_stats *ds;
#if HAVE_LIBSTATGRAB_0_90
  size_t disks;
#else
  int disks;
#endif
  char name[DATA_MAX_NAME_LEN];

  if ((ds = sg_get_disk_io_stats(&disks)) == NULL)
    return (0);

  for (int counter = 0; counter < disks; counter++) {
    strncpy(name, ds->disk_name, sizeof(name));
    name[sizeof(name) - 1] =
        '\0'; /* strncpy doesn't terminate longer strings */

    if (ignorelist_match(ignorelist, name) != 0) {
      ds++;
      continue;
    }

    disk_submit(name, "disk_octets", ds->read_bytes, ds->write_bytes);
    ds++;
  }
/* #endif defined(HAVE_LIBSTATGRAB) */

#elif defined(HAVE_PERFSTAT)
  derive_t read_sectors;
  derive_t write_sectors;
  derive_t read_time;
  derive_t write_time;
  derive_t read_ops;
  derive_t write_ops;
  perfstat_id_t firstpath;
  int rnumdisk;

  if ((numdisk = perfstat_disk(NULL, NULL, sizeof(perfstat_disk_t), 0)) < 0) {
    char errbuf[1024];
    WARNING("disk plugin: perfstat_disk: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  if (numdisk != pnumdisk || stat_disk == NULL) {
    if (stat_disk != NULL)
      free(stat_disk);
    stat_disk = (perfstat_disk_t *)calloc(numdisk, sizeof(perfstat_disk_t));
  }
  pnumdisk = numdisk;

  firstpath.name[0] = '\0';
  if ((rnumdisk = perfstat_disk(&firstpath, stat_disk, sizeof(perfstat_disk_t),
                                numdisk)) < 0) {
    char errbuf[1024];
    WARNING("disk plugin: perfstat_disk : %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  for (int i = 0; i < rnumdisk; i++) {
    if (ignorelist_match(ignorelist, stat_disk[i].name) != 0)
      continue;

    read_sectors = stat_disk[i].rblks * stat_disk[i].bsize;
    write_sectors = stat_disk[i].wblks * stat_disk[i].bsize;
    disk_submit(stat_disk[i].name, "disk_octets", read_sectors, write_sectors);

    read_ops = stat_disk[i].xrate;
    write_ops = stat_disk[i].xfers - stat_disk[i].xrate;
    disk_submit(stat_disk[i].name, "disk_ops", read_ops, write_ops);

    read_time = stat_disk[i].rserv;
    read_time *= ((double)(_system_configuration.Xint) /
                  (double)(_system_configuration.Xfrac)) /
                 1000000.0;
    write_time = stat_disk[i].wserv;
    write_time *= ((double)(_system_configuration.Xint) /
                   (double)(_system_configuration.Xfrac)) /
                  1000000.0;
    disk_submit(stat_disk[i].name, "disk_time", read_time, write_time);
  }
#endif /* defined(HAVE_PERFSTAT) */

  return (0);
}