uLong ZEXPORT deflateBound(strm, sourceLen)
    z_streamp strm;
    uLong sourceLen;
{
    deflate_state *s;
    uLong destLen;

    /* conservative upper bound */
    destLen = sourceLen +
              ((sourceLen + 7) >> 3) + ((sourceLen + 63) >> 6) + 11;

    /* if can't get parameters, return conservative bound */
    if (strm == Z_NULL || strm->state == Z_NULL)
        return destLen;

    /* if not default parameters, return conservative bound */
    s = strm->state;
    if (s->w_bits != 15 || s->hash_bits != 8 + 7)
        return destLen;

    /* default settings: return tight bound for that case */
    return compressBound(sourceLen);
}