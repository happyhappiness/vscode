static void
storeCossRebuildFromSwapLog(void *data)
{
    RebuildState *rb = (RebuildState *)data;
    StoreEntry *e = NULL;
    StoreSwapLogData s;
    size_t ss = sizeof(StoreSwapLogData);
    double x;
    assert(rb != NULL);
    /* load a number of objects per invocation */

    for (int aCount = 0; aCount < rb->speed; ++aCount) {
        if (fread(&s, ss, 1, rb->log) != 1) {
            debugs(47, DBG_IMPORTANT, "Done reading " << rb->sd->path << " swaplog (" << rb->n_read << " entries)");
            fclose(rb->log);
            rb->log = NULL;
            storeCossRebuildComplete(rb);
            return;
        }

        ++ rb->n_read;

        if (s.op <= SWAP_LOG_NOP)
            continue;

        if (s.op >= SWAP_LOG_MAX)
            continue;

        debugs(47, 3, "storeCossRebuildFromSwapLog: " <<
               swap_log_op_str[(int) s.op]  << " " << storeKeyText(s.key)  <<
               " "<< std::setfill('0') << std::hex << std::uppercase <<
               std::setw(8) << s.swap_filen);

        if (s.op == SWAP_LOG_ADD) {
            (void) 0;
        } else if (s.op == SWAP_LOG_DEL) {
            /* Delete unless we already have a newer copy */

            if ((e = rb->sd->get
                     (s.key)) != NULL && s.lastref > e->lastref) {
                /*
                 * Make sure we don't unlink the file, it might be
                 * in use by a subsequent entry.  Also note that
                 * we don't have to subtract from cur_size because
                 * adding to cur_size happens in the cleanup procedure.
                 */
                e->expireNow();
                e->releaseRequest();

                if (e->swap_filen > -1) {
                    e->swap_filen = -1;
                }

                e->release();
                /* Fake an unlink here, this is a bad hack :( */
                storeCossRemove(rb->sd, e);
                -- rb->counts.objcount;
                ++ rb->counts.cancelcount;
            }
            continue;
        } else {
            x = log(static_cast<double>(++rb->counts.bad_log_op)) / log(10.0);

            if (0.0 == x - (double)
                    (int) x)
                debugs(47, DBG_IMPORTANT, "WARNING: " << rb->counts.bad_log_op << " invalid swap log entries found");

            ++ rb->counts.invalid;

            continue;
        }

        if ((++rb->counts.scancount & 0xFFF) == 0) {

            struct stat sb;

            if (0 == fstat(fileno(rb->log), &sb))
                storeRebuildProgress(rb->sd->index,
                                     (int) sb.st_size / ss, rb->n_read);
        }

        if (EBIT_TEST(s.flags, KEY_PRIVATE)) {
            ++ rb->counts.badflags;
            continue;
        }

        e = rb->sd->get
            (s.key);

        if (e) {
            /* key already exists, current entry is newer */
            /* keep old, ignore new */
            ++ rb->counts.dupcount;
            continue;
        }

        ++ rb->counts.objcount;

        e = rb->sd->addDiskRestore(s.key,
                                   s.swap_filen,
                                   s.swap_file_sz,
                                   s.expires,
                                   s.timestamp,
                                   s.lastref,
                                   s.lastmod,
                                   s.refcount,
                                   s.flags,
                                   (int) rb->flags.clean);

        storeDirSwapLog(e, SWAP_LOG_ADD);
    }

    eventAdd("storeCossRebuild", storeCossRebuildFromSwapLog, rb, 0.0, 1);
}