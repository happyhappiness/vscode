{
#if defined(__LSB_VERSION__)
        /* getattrs() would be handy, but it is not part of LSB 4.0 */
        attr_t fwinAttrs;
        short  fwinPair;
        wattr_get(fwin, &fwinAttrs, &fwinPair, 0);
        wattr_set(win, fwinAttrs, fwinPair, 0);
#else
        wattrset(win,getattrs(fwin));
#endif
        }