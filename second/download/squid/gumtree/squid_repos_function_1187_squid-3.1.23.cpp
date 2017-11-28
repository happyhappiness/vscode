static void
memStringStats(std::ostream &stream)
{
    int i;
    int pooled_count = 0;
    size_t pooled_volume = 0;
    /* heading */
    stream << "String Pool\t Impact\t\t\n \t (%strings)\t (%volume)\n";
    /* table body */

    for (i = 0; i < mem_str_pool_count; i++) {
        const MemAllocator *pool = StrPools[i].pool;
        const int plevel = pool->getMeter().inuse.level;
        stream << std::setw(20) << std::left << pool->objectType();
        stream << std::right << "\t " << xpercentInt(plevel, StrCountMeter.level);
        stream << "\t " << xpercentInt(plevel * pool->objectSize(), StrVolumeMeter.level) << "\n";
        pooled_count += plevel;
        pooled_volume += plevel * pool->objectSize();
    }

    /* malloc strings */
    stream << std::setw(20) << std::left << "Other Strings";

    stream << std::right << "\t ";

    stream << xpercentInt(StrCountMeter.level - pooled_count, StrCountMeter.level) << "\t ";

    stream << xpercentInt(StrVolumeMeter.level - pooled_volume, StrVolumeMeter.level) << "\n\n";
}