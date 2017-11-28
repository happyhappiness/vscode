
    default:
        fatalf("fd_open(): unknown FD type - FD#: %i, type: %u, desc %s\n", fd, type, desc);
    }

#else
    F->read_method = &default_read_method;

    F->write_method = &default_write_method;

#endif

    fdUpdateBiggest(fd, 1);

    if (desc)
        xstrncpy(F->desc, desc, FD_DESC_SZ);

    Number_FD++;
}

void
fd_note(int fd, const char *s)
{
    fde *F = &fd_table[fd];
