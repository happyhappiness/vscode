void operator()(StoreMeta const &x) {
        switch (x.getType()) {

        case STORE_META_KEY:
            assert(x.length == SQUID_MD5_DIGEST_LENGTH);
            xmemcpy(index, x.value, SQUID_MD5_DIGEST_LENGTH);
            break;

        case STORE_META_STD:
            struct old_metahdr {
                time_t timestamp;
                time_t lastref;
                time_t expires;
                time_t lastmod;
                size_t swap_file_sz;
                uint16_t refcount;
                uint16_t flags;
            } *tmp;
            tmp = (struct old_metahdr *)x.value;
            assert(x.length == STORE_HDR_METASIZE_OLD);
            what->timestamp = tmp->timestamp;
            what->lastref = tmp->lastref;
            what->expires = tmp->expires;
            what->lastmod = tmp->lastmod;
            what->swap_file_sz = tmp->swap_file_sz;
            what->refcount = tmp->refcount;
            what->flags = tmp->flags;
            break;

        case STORE_META_STD_LFS:
            assert(x.length == STORE_HDR_METASIZE);
            xmemcpy(&what->timestamp, x.value, STORE_HDR_METASIZE);
            break;

        default:
            break;
        }
    }