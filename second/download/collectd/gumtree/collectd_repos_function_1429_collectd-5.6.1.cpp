static void
uuidcache_init(void)
{
	char line[100];
	char *s;
	int ma, mi, sz;
	static char ptname[100];
	FILE *procpt;
	char uuid[16], *label = NULL;
	char device[110];
	int handleOnFirst;

	if(uuidCache) {
		return;
	}

	procpt = fopen(PROC_PARTITIONS, "r");
	if(procpt == NULL) {
		return;
	}

	for(int firstPass = 1; firstPass >= 0; firstPass--) {
		fseek(procpt, 0, SEEK_SET);
		while(fgets(line, sizeof(line), procpt)) {
			if(sscanf(line, " %d %d %d %[^\n ]",
				&ma, &mi, &sz, ptname) != 4)
			{
				continue;
			}

			/* skip extended partitions (heuristic: size 1) */
			if(sz == 1) {
				continue;
			}

			/* look only at md devices on first pass */
			handleOnFirst = !strncmp(ptname, "md", 2);
			if(firstPass != handleOnFirst) {
				continue;
			}

			/* skip entire disk (minor 0, 64, ... on ide;
			0, 16, ... on sd) */
			/* heuristic: partition name ends in a digit */

			for(s = ptname; *s; s++);

			if(isdigit((int)s[-1])) {
			/*
			* Note: this is a heuristic only - there is no reason
			* why these devices should live in /dev.
			* Perhaps this directory should be specifiable by option.
			* One might for example have /devlabel with links to /dev
			* for the devices that may be accessed in this way.
			* (This is useful, if the cdrom on /dev/hdc must not
			* be accessed.)
			*/
				ssnprintf(device, sizeof(device), "%s/%s",
					DEVLABELDIR, ptname);
				if(!get_label_uuid(device, &label, uuid)) {
					uuidcache_addentry(sstrdup(device),
						label, uuid);
				}
			}
		}
	}
	fclose(procpt);
}