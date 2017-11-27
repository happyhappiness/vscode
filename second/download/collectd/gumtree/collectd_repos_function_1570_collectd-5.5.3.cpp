void module_register(void)
{
    plugin_register_complex_config("ceph", ceph_config);
    plugin_register_init("ceph", ceph_init);
    plugin_register_read("ceph", ceph_read);
    plugin_register_shutdown("ceph", ceph_shutdown);
}