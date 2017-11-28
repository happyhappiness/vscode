void
HttpHdrCc::packInto(Packable * p) const
{
    // optimization: if the mask is empty do nothing
    if (mask==0)
        return;

    HttpHdrCcType flag;
    int pcount = 0;
    assert(p);

    for (flag = HttpHdrCcType::CC_PUBLIC; flag < HttpHdrCcType::CC_ENUM_END; ++flag) {
        if (isSet(flag) && flag != HttpHdrCcType::CC_OTHER) {

            /* print option name for all options */
            p->appendf((pcount ? ", %s": "%s") , CcAttrs[flag].name);

            /* for all options having values, "=value" after the name */
            switch (flag) {
            case HttpHdrCcType::CC_PUBLIC:
                break;
            case HttpHdrCcType::CC_PRIVATE:
                if (private_.size())
                    p->appendf("=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(private_));
                break;

            case HttpHdrCcType::CC_NO_CACHE:
                if (no_cache.size())
                    p->appendf("=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(no_cache));
                break;
            case HttpHdrCcType::CC_NO_STORE:
                break;
            case HttpHdrCcType::CC_NO_TRANSFORM:
                break;
            case HttpHdrCcType::CC_MUST_REVALIDATE:
                break;
            case HttpHdrCcType::CC_PROXY_REVALIDATE:
                break;
            case HttpHdrCcType::CC_MAX_AGE:
                p->appendf("=%d", max_age);
                break;
            case HttpHdrCcType::CC_S_MAXAGE:
                p->appendf("=%d", s_maxage);
                break;
            case HttpHdrCcType::CC_MAX_STALE:
                /* max-stale's value is optional.
                  If we didn't receive it, don't send it */
                if (max_stale != MAX_STALE_ANY)
                    p->appendf("=%d", max_stale);
                break;
            case HttpHdrCcType::CC_MIN_FRESH:
                p->appendf("=%d", min_fresh);
                break;
            case HttpHdrCcType::CC_ONLY_IF_CACHED:
                break;
            case HttpHdrCcType::CC_STALE_IF_ERROR:
                p->appendf("=%d", stale_if_error);
                break;
            case HttpHdrCcType::CC_IMMUTABLE:
                break;
            case HttpHdrCcType::CC_OTHER:
            case HttpHdrCcType::CC_ENUM_END:
                // done below after the loop
                break;
            }

            ++pcount;
        }
    }

    if (other.size() != 0)
        p->appendf((pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH), SQUIDSTRINGPRINT(other));
}