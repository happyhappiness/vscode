/* 
   Copyright (C) Andrew Tridgell 1996
   Copyright (C) Paul Mackerras 1996
   Copyright (C) 2002 by Martin Pool <mbp@samba.org>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "rsync.h"

extern int dry_run;
extern int verbose;

#if SUPPORT_HARD_LINKS
static int hlink_compare(struct file_struct *f1, struct file_struct *f2)
{
	if (!S_ISREG(f1->mode) && !S_ISREG(f2->mode))
		return 0;
	if (!S_ISREG(f1->mode))
		return -1;
	if (!S_ISREG(f2->mode))
		return 1;

	if (f1->dev != f2->dev)
		return (int) (f1->dev > f2->dev ? 1 : -1);

	if (f1->inode != f2->inode)
		return (int) (f1->inode > f2->inode ? 1 : -1);

	return file_compare(&f1, &f2);
}


static struct file_struct *hlink_list;
static int hlink_count;
#endif

void init_hard_links(struct file_list *flist)
{
#if SUPPORT_HARD_LINKS
	int i;
