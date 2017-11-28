/*
 * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

/* DEBUG: section --    External DISKD process implementation. */

#include "squid.h"
#include "DiskIO/DiskDaemon/diomsg.h"
#include "hash.h"

#include <cerrno>
#include <iostream>
#if HAVE_SYS_IPC_H
#include <sys/ipc.h>
#endif
#if HAVE_SYS_MSG_H
#include <sys/msg.h>
#endif
#if HAVE_SYS_SHM_H
#include <sys/shm.h>
#endif

void
xassert(const char *msg, const char *file, int line)
{
    fprintf(stderr,"assertion failed: %s:%d: \"%s\"\n", file, line, msg);

