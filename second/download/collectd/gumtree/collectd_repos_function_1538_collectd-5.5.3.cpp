static void ceph_daemon_print(const struct ceph_daemon *d)
{
    DEBUG("ceph plugin: name=%s, asok_path=%s", d->name, d->asok_path);
}