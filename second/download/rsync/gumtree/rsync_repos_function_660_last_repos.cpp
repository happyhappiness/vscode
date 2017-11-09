uLong ZEXPORT zlibCompileFlags()
{
    uLong flags;

    flags = 0;
    switch ((int)(sizeof(uInt))) {
    case 2:     break;				/* CONSTANT CONDITION */
    case 4:     flags += 1;     break;		/* CONSTANT CONDITION */
    case 8:     flags += 2;     break;		/* CONSTANT CONDITION */
    default:    flags += 3;
    }
    switch ((int)(sizeof(uLong))) {
    case 2:     break;				/* CONSTANT CONDITION */
    case 4:     flags += 1 << 2;        break;	/* CONSTANT CONDITION */
    case 8:     flags += 2 << 2;        break;	/* CONSTANT CONDITION */
    default:    flags += 3 << 2;
    }
    switch ((int)(sizeof(voidpf))) {
    case 2:     break;				/* CONSTANT CONDITION */
    case 4:     flags += 1 << 4;        break;	/* CONSTANT CONDITION */
    case 8:     flags += 2 << 4;        break;	/* CONSTANT CONDITION */
    default:    flags += 3 << 4;
    }
    switch ((int)(sizeof(z_off_t))) {
    case 2:     break;				/* CONSTANT CONDITION */
    case 4:     flags += 1 << 6;        break;	/* CONSTANT CONDITION */
    case 8:     flags += 2 << 6;        break;	/* CONSTANT CONDITION */
    default:    flags += 3 << 6;
    }
#ifdef DEBUG
    flags += 1 << 8;
#endif
#if defined(ASMV) || defined(ASMINF)
    flags += 1 << 9;
#endif
#ifdef ZLIB_WINAPI
    flags += 1 << 10;
#endif
#ifdef BUILDFIXED
    flags += 1 << 12;
#endif
#ifdef DYNAMIC_CRC_TABLE
    flags += 1 << 13;
#endif
#ifdef NO_GZCOMPRESS
    flags += 1L << 16;
#endif
#ifdef NO_GZIP
    flags += 1L << 17;
#endif
#ifdef PKZIP_BUG_WORKAROUND
    flags += 1L << 20;
#endif
#ifdef FASTEST
    flags += 1L << 21;
#endif
#if defined(STDC) || defined(Z_HAVE_STDARG_H)
#  ifdef NO_vsnprintf
    flags += 1L << 25;
#    ifdef HAS_vsprintf_void
    flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_vsnprintf_void
    flags += 1L << 26;
#    endif
#  endif
#else
    flags += 1L << 24;
#  ifdef NO_snprintf
    flags += 1L << 25;
#    ifdef HAS_sprintf_void
    flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_snprintf_void
    flags += 1L << 26;
#    endif
#  endif
#endif
    return flags;
}