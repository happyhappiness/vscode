void
Mem::PoolReport(const MemPoolStats * mp_st, const MemPoolMeter * AllMeter, std::ostream &stream)
{
    int excess = 0;
    int needed = 0;
    MemPoolMeter *pm = mp_st->meter;
    const char *delim = "\t ";

    stream.setf(std::ios_base::fixed);
    stream << std::setw(20) << std::left << mp_st->label << delim;
    stream << std::setw(4) << std::right << mp_st->obj_size << delim;

    /* Chunks */
    if (mp_st->chunk_capacity) {
        stream << std::setw(4) << toKB(mp_st->obj_size * mp_st->chunk_capacity) << delim;
        stream << std::setw(4) << mp_st->chunk_capacity << delim;

        needed = mp_st->items_inuse / mp_st->chunk_capacity;

        if (mp_st->items_inuse % mp_st->chunk_capacity)
            ++needed;

        excess = mp_st->chunks_inuse - needed;

        stream << std::setw(4) << mp_st->chunks_alloc << delim;
        stream << std::setw(4) << mp_st->chunks_inuse << delim;
        stream << std::setw(4) << mp_st->chunks_free << delim;
        stream << std::setw(4) << mp_st->chunks_partial << delim;
        stream << std::setprecision(3) << xpercent(excess, needed) << delim;
    } else {
        stream << delim;
        stream << delim;
        stream << delim;
        stream << delim;
        stream << delim;
        stream << delim;
        stream << delim;
    }
    /*
     *  Fragmentation calculation:
     *    needed = inuse.currentLevel() / chunk_capacity
     *    excess = used - needed
     *    fragmentation = excess / needed * 100%
     *
     *    Fragm = (alloced - (inuse / obj_ch) ) / alloced
     */
    /* allocated */
    stream << mp_st->items_alloc << delim;
    stream << toKB(mp_st->obj_size * pm->alloc.currentLevel()) << delim;
    stream << toKB(mp_st->obj_size * pm->alloc.peak()) << delim;
    stream << std::setprecision(2) << ((squid_curtime - pm->alloc.peakTime()) / 3600.) << delim;
    stream << std::setprecision(3) << xpercent(mp_st->obj_size * pm->alloc.currentLevel(), AllMeter->alloc.currentLevel()) << delim;
    /* in use */
    stream << mp_st->items_inuse << delim;
    stream << toKB(mp_st->obj_size * pm->inuse.currentLevel()) << delim;
    stream << toKB(mp_st->obj_size * pm->inuse.peak()) << delim;
    stream << std::setprecision(2) << ((squid_curtime - pm->inuse.peakTime()) / 3600.) << delim;
    stream << std::setprecision(3) << xpercent(pm->inuse.currentLevel(), pm->alloc.currentLevel()) << delim;
    /* idle */
    stream << mp_st->items_idle << delim;
    stream << toKB(mp_st->obj_size * pm->idle.currentLevel()) << delim;
    stream << toKB(mp_st->obj_size * pm->idle.peak()) << delim;
    /* saved */
    stream << (int)pm->gb_saved.count << delim;
    stream << std::setprecision(3) << xpercent(pm->gb_saved.count, AllMeter->gb_allocated.count) << delim;
    stream << std::setprecision(3) << xpercent(pm->gb_saved.bytes, AllMeter->gb_allocated.bytes) << delim;
    stream << std::setprecision(3) << xdiv(pm->gb_allocated.count - pm->gb_oallocated.count, xm_deltat) << "\n";
    pm->gb_oallocated.count = pm->gb_allocated.count;
}