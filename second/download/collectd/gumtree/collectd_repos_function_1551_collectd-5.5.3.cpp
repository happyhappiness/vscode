static int
node_handler_define_schema(void *arg, const char *val, const char *key)
{
    struct ceph_daemon *d = (struct ceph_daemon *) arg;
    int pc_type;
    pc_type = atoi(val);
    return ceph_daemon_add_ds_entry(d, key, pc_type);
}