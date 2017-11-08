void show_date_relative(unsigned long time, int tz,
			       const struct timeval *now,
			       struct strbuf *timebuf)
{
	unsigned long diff;
	if (now->tv_sec < time) {
		strbuf_addstr(timebuf, _("in the future"));
		return;
	}
	diff = now->tv_sec - time;
	if (diff < 90) {
		strbuf_addf(timebuf,
			 Q_("%lu second ago", "%lu seconds ago", diff), diff);
		return;
	}
	/* Turn it into minutes */
	diff = (diff + 30) / 60;
	if (diff < 90) {
		strbuf_addf(timebuf,
			 Q_("%lu minute ago", "%lu minutes ago", diff), diff);
		return;
	}
	/* Turn it into hours */
	diff = (diff + 30) / 60;
	if (diff < 36) {
		strbuf_addf(timebuf,
			 Q_("%lu hour ago", "%lu hours ago", diff), diff);
		return;
	}
	/* We deal with number of days from here on */
	diff = (diff + 12) / 24;
	if (diff < 14) {
		strbuf_addf(timebuf,
			 Q_("%lu day ago", "%lu days ago", diff), diff);
		return;
	}
	/* Say weeks for the past 10 weeks or so */
	if (diff < 70) {
		strbuf_addf(timebuf,
			 Q_("%lu week ago", "%lu weeks ago", (diff + 3) / 7),
			 (diff + 3) / 7);
		return;
	}
	/* Say months for the past 12 months or so */
	if (diff < 365) {
		strbuf_addf(timebuf,
			 Q_("%lu month ago", "%lu months ago", (diff + 15) / 30),
			 (diff + 15) / 30);
		return;
	}
	/* Give years and months for 5 years or so */
	if (diff < 1825) {
		unsigned long totalmonths = (diff * 12 * 2 + 365) / (365 * 2);
		unsigned long years = totalmonths / 12;
		unsigned long months = totalmonths % 12;
		if (months) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_addf(&sb, Q_("%lu year", "%lu years", years), years);
			strbuf_addf(timebuf,
				 /* TRANSLATORS: "%s" is "<n> years" */
				 Q_("%s, %lu month ago", "%s, %lu months ago", months),
				 sb.buf, months);
			strbuf_release(&sb);
		} else
			strbuf_addf(timebuf,
				 Q_("%lu year ago", "%lu years ago", years), years);
		return;
	}
	/* Otherwise, just years. Centuries is probably overkill. */
	strbuf_addf(timebuf,
		 Q_("%lu year ago", "%lu years ago", (diff + 183) / 365),
		 (diff + 183) / 365);
}