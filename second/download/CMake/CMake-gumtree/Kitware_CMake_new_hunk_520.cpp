#ifndef ARCHIVE_H_INCLUDED

#define	ARCHIVE_H_INCLUDED



/*

 * The version number is expressed as a single integer that makes it

 * easy to compare versions at build time: for version a.b.c, the

 * version number is printf("%d%03d%03d",a,b,c).  For example, if you

 * know your application requires version 2.12.108 or later, you can

 * assert that ARCHIVE_VERSION_NUMBER >= 2012108.

 */

/* Note: Compiler will complain if this does not match archive_entry.h! */

#define	ARCHIVE_VERSION_NUMBER 3002000



#include <sys/stat.h>

#include <stddef.h>  /* for wchar_t */

#include <stdio.h> /* For FILE * */

#include <time.h> /* For time_t */



/*

 * Note: archive.h is for use outside of libarchive; the configuration

