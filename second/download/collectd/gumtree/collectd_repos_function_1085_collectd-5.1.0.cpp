static int swap_read (void) /* {{{ */
{
        swaptbl_t *s;
	char *s_paths;
        int swap_num;
        int status;
        int i;

        derive_t avail = 0;
        derive_t total = 0;

        swap_num = swapctl (SC_GETNSWP, NULL);
        if (swap_num < 0)
        {
                ERROR ("swap plugin: swapctl (SC_GETNSWP) failed with status %i.",
                                swap_num);
                return (-1);
        }
        else if (swap_num == 0)
                return (0);

	/* Allocate and initialize the swaptbl_t structure */
        s = (swaptbl_t *) smalloc (swap_num * sizeof (swapent_t) + sizeof (struct swaptable));
        if (s == NULL)
        {
                ERROR ("swap plugin: smalloc failed.");
                return (-1);
        }

	/* Memory to store the path names. We only use these paths when the
	 * separate option has been configured, but it's easier to just
	 * allocate enough memory in any case. */
	s_paths = calloc (swap_num, PATH_MAX);
	if (s_paths == NULL)
	{
		ERROR ("swap plugin: malloc failed.");
		sfree (s);
		return (-1);
	}
        for (i = 0; i < swap_num; i++)
		s->swt_ent[i].ste_path = s_paths + (i * PATH_MAX);
        s->swt_n = swap_num;

        status = swapctl (SC_LIST, s);
        if (status < 0)
        {
		char errbuf[1024];
                ERROR ("swap plugin: swapctl (SC_LIST) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		sfree (s_paths);
                sfree (s);
                return (-1);
        }
	else if (swap_num < status)
	{
		/* more elements returned than requested */
		ERROR ("swap plugin: I allocated memory for %i structure%s, "
				"but swapctl(2) claims to have returned %i. "
				"I'm confused and will give up.",
				swap_num, (swap_num == 1) ? "" : "s",
				status);
		sfree (s_paths);
                sfree (s);
                return (-1);
	}
	else if (swap_num > status)
		/* less elements returned than requested */
		swap_num = status;

        for (i = 0; i < swap_num; i++)
        {
		char path[PATH_MAX];
		derive_t this_total;
		derive_t this_avail;

                if ((s->swt_ent[i].ste_flags & ST_INDEL) != 0)
                        continue;

		this_total = ((derive_t) s->swt_ent[i].ste_pages) * pagesize;
		this_avail = ((derive_t) s->swt_ent[i].ste_free)  * pagesize;

		/* Shortcut for the "combined" setting (default) */
		if (!report_by_device)
		{
			avail += this_avail;
			total += this_total;
			continue;
		}

		sstrncpy (path, s->swt_ent[i].ste_path, sizeof (path));
		escape_slashes (path, sizeof (path));

		swap_submit_gauge (path, "used", (gauge_t) (this_total - this_avail));
		swap_submit_gauge (path, "free", (gauge_t) this_avail);
        } /* for (swap_num) */

        if (total < avail)
        {
                ERROR ("swap plugin: Total swap space (%"PRIi64") "
                                "is less than free swap space (%"PRIi64").",
                                total, avail);
		sfree (s_paths);
                sfree (s);
                return (-1);
        }

	/* If the "separate" option was specified (report_by_device == 2), all
	 * values have already been dispatched from within the loop. */
	if (!report_by_device)
	{
		swap_submit_gauge (NULL, "used", (gauge_t) (total - avail));
		swap_submit_gauge (NULL, "free", (gauge_t) avail);
	}

	sfree (s_paths);
        sfree (s);
	return (0);
}