static ignorelist_t *il_domains = NULL;
/* List of block devices, if specified. */
static ignorelist_t *il_block_devices = NULL;
/* List of network interface devices, if specified. */
static ignorelist_t *il_interface_devices = NULL;

static int ignore_device_match(ignorelist_t *, const char *domname,
                               const char *devpath);

/* Actual list of domains found on last refresh. */
static virDomainPtr *domains = NULL;
static int nr_domains = 0;

static void free_domains(void);
static int add_domain(virDomainPtr dom);

/* Actual list of block devices found on last refresh. */
struct block_device {
  virDomainPtr dom; /* domain */
  char *path;       /* name of block device */
};

static struct block_device *block_devices = NULL;
static int nr_block_devices = 0;

static void free_block_devices(void);
static int add_block_device(virDomainPtr dom, const char *path);

/* Actual list of network interfaces found on last refresh. */
struct interface_device {
  virDomainPtr dom; /* domain */
  char *path;       /* name of interface device */
  char *address;    /* mac address of interface device */
  char *number;     /* interface device number */
};

static struct interface_device *interface_devices = NULL;
static int nr_interface_devices = 0;

static void free_interface_devices(void);
static int add_interface_device(virDomainPtr dom, const char *path,
                                const char *address, unsigned int number);

/* HostnameFormat. */
#define HF_MAX_FIELDS 3

enum hf_field { hf_none = 0, hf_hostname, hf_name, hf_uuid };

static enum hf_field hostname_format[HF_MAX_FIELDS] = {hf_name};

/* PluginInstanceFormat */
#define PLGINST_MAX_FIELDS 2

enum plginst_field { plginst_none = 0, plginst_name, plginst_uuid };

static enum plginst_field plugin_instance_format[PLGINST_MAX_FIELDS] = {
    plginst_none};

/* InterfaceFormat. */
enum if_field { if_address, if_name, if_number };

static enum if_field interface_format = if_name;

/* Time that we last refreshed. */
static time_t last_refresh = (time_t)0;

static int refresh_lists(void);

/* ERROR(...) macro for virterrors. */
#define VIRT_ERROR(conn, s)                                                    \
  do {                                                                         \
    virErrorPtr err;                                                           \
    err = (conn) ? virConnGetLastError((conn)) : virGetLastError();            \
    if (err)                                                                   \
      ERROR("%s: %s", (s), err->message);                                      \
  } while (0)

static void init_value_list(value_list_t *vl, virDomainPtr dom) {
  int n;
  const char *name;
  char uuid[VIR_UUID_STRING_BUFLEN];

  sstrncpy(vl->plugin, PLUGIN_NAME, sizeof(vl->plugin));

  vl->host[0] = '\0';

  /* Construct the hostname field according to HostnameFormat. */
  for (int i = 0; i < HF_MAX_FIELDS; ++i) {
    if (hostname_format[i] == hf_none)
      continue;

    n = DATA_MAX_NAME_LEN - strlen(vl->host) - 2;

    if (i > 0 && n >= 1) {
      strncat(vl->host, ":", 1);
      n--;
    }

    switch (hostname_format[i]) {
    case hf_none:
      break;
    case hf_hostname:
      strncat(vl->host, hostname_g, n);
      break;
    case hf_name:
      name = virDomainGetName(dom);
      if (name)
        strncat(vl->host, name, n);
      break;
    case hf_uuid:
      if (virDomainGetUUIDString(dom, uuid) == 0)
        strncat(vl->host, uuid, n);
      break;
    }
  }

  vl->host[sizeof(vl->host) - 1] = '\0';

  /* Construct the plugin instance field according to PluginInstanceFormat. */
  for (int i = 0; i < PLGINST_MAX_FIELDS; ++i) {
    if (plugin_instance_format[i] == plginst_none)
      continue;

    n = sizeof(vl->plugin_instance) - strlen(vl->plugin_instance) - 2;

    if (i > 0 && n >= 1) {
      strncat(vl->plugin_instance, ":", 1);
      n--;
    }

    switch (plugin_instance_format[i]) {
    case plginst_none:
      break;
    case plginst_name:
      name = virDomainGetName(dom);
      if (name)
        strncat(vl->plugin_instance, name, n);
      break;
    case plginst_uuid:
      if (virDomainGetUUIDString(dom, uuid) == 0)
        strncat(vl->plugin_instance, uuid, n);
      break;
    }
  }

  vl->plugin_instance[sizeof(vl->plugin_instance) - 1] = '\0';

} /* void init_value_list */

static void memory_submit(gauge_t memory, virDomainPtr dom) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  init_value_list(&vl, dom);

  values[0].gauge = memory;

  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.type, "memory", sizeof(vl.type));
  sstrncpy(vl.type_instance, "total", sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}

static void memory_stats_submit(gauge_t memory, virDomainPtr dom,
                                int tag_index) {
  static const char *tags[] = {"swap_in",        "swap_out", "major_fault",
                               "minor_fault",    "unused",   "available",
                               "actual_balloon", "rss"};

  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  init_value_list(&vl, dom);

  values[0].gauge = memory;

  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.type, "memory", sizeof(vl.type));
  sstrncpy(vl.type_instance, tags[tag_index], sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}

static void cpu_submit(unsigned long long cpu_time, virDomainPtr dom,
                       const char *type) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  init_value_list(&vl, dom);

  values[0].derive = cpu_time;

  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.type, type, sizeof(vl.type));

  plugin_dispatch_values(&vl);
}

static void vcpu_submit(derive_t cpu_time, virDomainPtr dom, int vcpu_nr,
                        const char *type) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  init_value_list(&vl, dom);

  values[0].derive = cpu_time;
  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.type, type, sizeof(vl.type));
  ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%d", vcpu_nr);

  plugin_dispatch_values(&vl);
}

static void submit_derive2(const char *type, derive_t v0, derive_t v1,
                           virDomainPtr dom, const char *devname) {
  value_t values[2];
  value_list_t vl = VALUE_LIST_INIT;

  init_value_list(&vl, dom);

  values[0].derive = v0;
  values[1].derive = v1;
  vl.values = values;
  vl.values_len = 2;

  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, devname, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
} /* void submit_derive2 */

static int lv_init(void) {
  if (virInitialize() != 0)
    return -1;
  else
    return 0;
}

static int lv_config(const char *key, const char *value) {
  if (virInitialize() != 0)
    return 1;

  if (il_domains == NULL)
    il_domains = ignorelist_create(1);
  if (il_block_devices == NULL)
    il_block_devices = ignorelist_create(1);
  if (il_interface_devices == NULL)
    il_interface_devices = ignorelist_create(1);

  if (strcasecmp(key, "Connection") == 0) {
    char *tmp = strdup(value);
    if (tmp == NULL) {
      ERROR(PLUGIN_NAME " plugin: Connection strdup failed.");
      return 1;
    }
    sfree(conn_string);
    conn_string = tmp;
    return 0;
  }

  if (strcasecmp(key, "RefreshInterval") == 0) {
    char *eptr = NULL;
    interval = strtol(value, &eptr, 10);
    if (eptr == NULL || *eptr != '\0')
      return 1;
    return 0;
  }

  if (strcasecmp(key, "Domain") == 0) {
    if (ignorelist_add(il_domains, value))
      return 1;
    return 0;
  }
  if (strcasecmp(key, "BlockDevice") == 0) {
    if (ignorelist_add(il_block_devices, value))
      return 1;
    return 0;
  }
  if (strcasecmp(key, "InterfaceDevice") == 0) {
    if (ignorelist_add(il_interface_devices, value))
      return 1;
    return 0;
  }

  if (strcasecmp(key, "IgnoreSelected") == 0) {
    if (IS_TRUE(value)) {
      ignorelist_set_invert(il_domains, 0);
      ignorelist_set_invert(il_block_devices, 0);
      ignorelist_set_invert(il_interface_devices, 0);
    } else {
      ignorelist_set_invert(il_domains, 1);
      ignorelist_set_invert(il_block_devices, 1);
      ignorelist_set_invert(il_interface_devices, 1);
    }
    return 0;
  }

  if (strcasecmp(key, "HostnameFormat") == 0) {
    char *value_copy;
    char *fields[HF_MAX_FIELDS];
    int n;

    value_copy = strdup(value);
    if (value_copy == NULL) {
      ERROR(PLUGIN_NAME " plugin: strdup failed.");
      return -1;
    }

    n = strsplit(value_copy, fields, HF_MAX_FIELDS);
    if (n < 1) {
      sfree(value_copy);
      ERROR(PLUGIN_NAME " plugin: HostnameFormat: no fields");
      return -1;
    }

    for (int i = 0; i < n; ++i) {
      if (strcasecmp(fields[i], "hostname") == 0)
        hostname_format[i] = hf_hostname;
      else if (strcasecmp(fields[i], "name") == 0)
        hostname_format[i] = hf_name;
      else if (strcasecmp(fields[i], "uuid") == 0)
        hostname_format[i] = hf_uuid;
      else {
        ERROR(PLUGIN_NAME " plugin: unknown HostnameFormat field: %s",
              fields[i]);
        sfree(value_copy);
        return -1;
      }
    }
    sfree(value_copy);

    for (int i = n; i < HF_MAX_FIELDS; ++i)
      hostname_format[i] = hf_none;

    return 0;
  }

  if (strcasecmp(key, "PluginInstanceFormat") == 0) {
    char *value_copy;
    char *fields[PLGINST_MAX_FIELDS];
    int n;

    value_copy = strdup(value);
    if (value_copy == NULL) {
      ERROR(PLUGIN_NAME " plugin: strdup failed.");
      return -1;
    }

    n = strsplit(value_copy, fields, PLGINST_MAX_FIELDS);
    if (n < 1) {
      sfree(value_copy);
      ERROR(PLUGIN_NAME " plugin: PluginInstanceFormat: no fields");
      return -1;
    }

    for (int i = 0; i < n; ++i) {
      if (strcasecmp(fields[i], "none") == 0) {
        plugin_instance_format[i] = plginst_none;
        break;
      } else if (strcasecmp(fields[i], "name") == 0)
        plugin_instance_format[i] = plginst_name;
      else if (strcasecmp(fields[i], "uuid") == 0)
        plugin_instance_format[i] = plginst_uuid;
      else {
        ERROR(PLUGIN_NAME " plugin: unknown PluginInstanceFormat field: %s",
              fields[i]);
        sfree(value_copy);
        return -1;
      }
    }
    sfree(value_copy);

    for (int i = n; i < PLGINST_MAX_FIELDS; ++i)
      plugin_instance_format[i] = plginst_none;

    return 0;
  }

  if (strcasecmp(key, "InterfaceFormat") == 0) {
    if (strcasecmp(value, "name") == 0)
      interface_format = if_name;
    else if (strcasecmp(value, "address") == 0)
      interface_format = if_address;
    else if (strcasecmp(value, "number") == 0)
      interface_format = if_number;
    else {
      ERROR(PLUGIN_NAME " plugin: unknown InterfaceFormat: %s", value);
      return -1;
    }
    return 0;
  }

  /* Unrecognised option. */
  return -1;
}

static int lv_read(void) {
  time_t t;

  if (conn == NULL) {
    /* `conn_string == NULL' is acceptable. */
    conn = virConnectOpenReadOnly(conn_string);
    if (conn == NULL) {
      c_complain(LOG_ERR, &conn_complain,
                 PLUGIN_NAME " plugin: Unable to connect: "
                             "virConnectOpenReadOnly failed.");
      return -1;
    }
  }
  c_release(LOG_NOTICE, &conn_complain,
            PLUGIN_NAME " plugin: Connection established.");

  time(&t);

  /* Need to refresh domain or device lists? */
  if ((last_refresh == (time_t)0) ||
      ((interval > 0) && ((last_refresh + interval) <= t))) {
    if (refresh_lists() != 0) {
      if (conn != NULL)
        virConnectClose(conn);
      conn = NULL;
      return -1;
    }
    last_refresh = t;
  }

#if 0
    for (int i = 0; i < nr_domains; ++i)
        fprintf (stderr, "domain %s\n", virDomainGetName (domains[i]));
    for (int i = 0; i < nr_block_devices; ++i)
        fprintf  (stderr, "block device %d %s:%s\n",
