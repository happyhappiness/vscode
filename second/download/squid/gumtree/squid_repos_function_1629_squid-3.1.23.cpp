void
helperStatefulFree(statefulhelper * hlp)
{
    if (!hlp)
        return;

    /* note, don't free hlp->name, it probably points to static memory */
    if (hlp->queue.head)
        debugs(84, 0, "WARNING: freeing " << hlp->id_name << " helper with " <<
               hlp->stats.queue_size << " requests queued");

    cbdataFree(hlp);
}