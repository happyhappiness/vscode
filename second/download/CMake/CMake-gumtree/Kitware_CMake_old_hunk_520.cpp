#ifndef ARCHIVE_H_INCLUDED
#define	ARCHIVE_H_INCLUDED

#include <sys/stat.h>
#include <stddef.h>  /* for wchar_t */
#include <stdio.h> /* For FILE * */

/*
 * Note: archive.h is for use outside of libarchive; the configuration
