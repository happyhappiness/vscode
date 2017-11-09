void show_date_relative(timestamp_t time, int tz,
			       const struct timeval *now,
			       struct strbuf *timebuf)
{
	timestamp_t diff;
	if (now->tv_sec < time) {
		strbuf_addstr(timebuf, _("in the future"));
		return;
	}
	diff = now->tv_sec - time;
	if (diff < 90) {
		strbuf_addf(timebuf,
			 Q_("%"PRItime" second ago", "%"PRItime" seconds ago", diff), diff);
		return;
	}
	/* Turn it into minutes */
	diff = (diff + 30) / 60;
	if (diff < 90) {
		strbuf_addf(timebuf,
			 Q_("%"PRItime" minute ago", "%"PRItime" minutes ago", diff), diff);
		return;
	}
	/* Turn it into hours */
	diff = (diff + 30) / 60;
	if (diff < 36) {
		strbuf_addf(timebuf,
			 Q_("%"PRItime" hour ago", "%"PRItime" hours ago", diff), diff);
		return;
	}
	/* We deal with number of days from here on */
	diff = (diff + 12) / 24;
	if (diff < 14) {
		strbuf_addf(timebuf,
			 Q_("%"PRItime" day ago", "%"PRItime" days ago", diff), diff);
		return;
	}
	/* Say weeks for the past 10 weeks or so */
	if (diff < 70) {
		strbuf_addf(timebuf,
			 Q_("%"PRItime" week ago", "%"PRItime" weeks ago", (diff + 3) / 7),
			 (diff + 3) / 7);
		return;
	}
	/* Say months for the past 12 months or so */
	if (diff < 365) {
		strbuf_addf(timebuf,
			 Q_("%"PRItime" month ago", "%"PRItime" months ago", (diff + 15) / 30),
			 (diff + 15) / 30);
		return;
	}
	/* Give years and months for 5 years or so */
	if (diff < 1825) {
		timestamp_t totalmonths = (diff * 12 * 2 + 365) / (365 * 2);
		timestamp_t years = totalmonths / 12;
		timestamp_t months = totalmonths % 12;
		if (months) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_addf(&sb, Q_("%"PRItime" year", "%"PRItime" years", years), years);
			strbuf_addf(timebuf,
				 /* TRANSLATORS: "%s" is "<n> years" */
				 Q_("%s, %"PRItime" month ago", "%s, %"PRItime" months ago", months),
				 sb.buf, months);
			strbuf_release(&sb);
		} else
			strbuf_addf(timebuf,
				 Q_("%"PRItime" year ago", "%"PRItime" years ago", years), years);
		return;
	}
	/* Otherwise, just years. Centuries is probably overkill. */
	strbuf_addf(timebuf,
		 Q_("%"PRItime" year ago", "%"PRItime" years ago", (diff + 183) / 365),
		 (diff + 183) / 365);
}