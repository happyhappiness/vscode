void
Ipc::Mem::Segment::checkSupport(const char *const context)
{
    if (!Enabled()) {
        debugs(54, 5, HERE << context <<
               ": True shared memory segments are not supported. "
               "Cannot fake shared segments in SMP config.");
        fatalf("Ipc::Mem::Segment: Cannot fake shared segments in SMP config (%s)\n",
               context);
    }
}