Fs::Ufs::UFSSwapLogParser *
Fs::Ufs::UFSSwapLogParser::GetUFSSwapLogParser(FILE *fp)
{
    StoreSwapLogHeader header;

    assert(fp);

    if (fread(&header, sizeof(StoreSwapLogHeader), 1, fp) != 1)
        return NULL;

    if (header.op != SWAP_LOG_VERSION) {
        debugs(47, DBG_IMPORTANT, "Old swap file detected...");
        fseek(fp, 0, SEEK_SET);
        return new UFSSwapLogParser_v1_32bs(fp); // Um. 32-bits except time_t, and can't determine that.
    }

    debugs(47, 2, "Swap file version: " << header.version);

    if (header.version == 1) {
        if (fseek(fp, header.record_size, SEEK_SET) != 0)
            return NULL;

        debugs(47, DBG_IMPORTANT, "Rejecting swap file v1 to avoid cache " <<
               "index corruption. Forcing a full cache index rebuild. " <<
               "See Squid bug #3441.");
        return NULL;

#if UNUSED_CODE
        // baseline
        // 32-bit sfileno
        // native time_t (hopefully 64-bit)
        // 64-bit file size
        if (header.record_size == sizeof(StoreSwapLogData)) {
            debugs(47, DBG_IMPORTANT, "Version 1 of swap file with LFS support detected... ");
            return new UFSSwapLogParser_v1(fp);
        }

        // which means we have a 3-way grid of permutations to import (yuck!)
        // 1) sfileno 32-bit / 64-bit  (64-bit was broken)
        // 2) time_t 32-bit / 64-bit
        // 3) size_t 32-bit / 64-bit  (32-bit was pre-LFS)

        // 32-bit systems...
        // only LFS (size_t) differs from baseline
        if (header.record_size == sizeof(struct UFSSwapLogParser_v1_32bs::StoreSwapLogDataOld)) {
            debugs(47, DBG_IMPORTANT, "Version 1 (32-bit) swap file without LFS support detected... ");
            return new UFSSwapLogParser_v1_32bs(fp);
        }
        // LFS (size_t) and timestamps (time_t) differs from baseline
        if (header.record_size == sizeof(struct UFSSwapLogParser_v1_32bst::StoreSwapLogDataOld)) {
            debugs(47, DBG_IMPORTANT, "Version 1 (32-bit) swap file with short timestamps and without LFS support detected... ");
            return new UFSSwapLogParser_v1_32bst(fp);
        }
        // No downgrade for 64-bit timestamps to 32-bit.

        // 64-bit systems
        // sfileno was 64-bit for a some builds
        if (header.record_size == sizeof(struct UFSSwapLogParser_v1_64bfn::StoreSwapLogDataOld)) {
            debugs(47, DBG_IMPORTANT, "Version 1 (64-bit) swap file with broken sfileno detected... ");
            return new UFSSwapLogParser_v1_64bfn(fp);
        }
        // NP: 64-bit system with 32-bit size_t/time_t are not handled.

        debugs(47, DBG_IMPORTANT, "WARNING: The swap file has wrong format!... ");
        debugs(47, DBG_IMPORTANT, "NOTE: Cannot safely downgrade caches to short (32-bit) timestamps.");
        return NULL;
#endif
    }

    if (header.version >= 2) {
        if (!header.sane()) {
            debugs(47, DBG_IMPORTANT, "ERROR: Corrupted v" << header.version <<
                   " swap file header.");
            return NULL;
        }

        if (fseek(fp, header.record_size, SEEK_SET) != 0)
            return NULL;

        if (header.version == 2)
            return new UFSSwapLogParser_v2(fp);
    }

    // TODO: v3: write to disk in network-order bytes for the larger fields?

    debugs(47, DBG_IMPORTANT, "Unknown swap file version: " << header.version);
    return NULL;
}