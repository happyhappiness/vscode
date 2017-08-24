f(vto[i].flags & FLAGS_UNSIGNED)
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned int)