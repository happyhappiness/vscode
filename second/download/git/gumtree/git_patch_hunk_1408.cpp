 		die("BUG: cannot create anonymous strftime date_mode struct");
 	mode.type = type;
 	mode.local = 0;
 	return &mode;
 }
 
-const char *show_date(unsigned long time, int tz, const struct date_mode *mode)
+const char *show_date(timestamp_t time, int tz, const struct date_mode *mode)
 {
 	struct tm *tm;
 	static struct strbuf timebuf = STRBUF_INIT;
 
 	if (mode->type == DATE_UNIX) {
 		strbuf_reset(&timebuf);
-		strbuf_addf(&timebuf, "%lu", time);
+		strbuf_addf(&timebuf, "%"PRItime, time);
 		return timebuf.buf;
 	}
 
 	if (mode->local)
 		tz = local_tzoffset(time);
 
 	if (mode->type == DATE_RAW) {
 		strbuf_reset(&timebuf);
-		strbuf_addf(&timebuf, "%lu %+05d", time, tz);
+		strbuf_addf(&timebuf, "%"PRItime" %+05d", time, tz);
 		return timebuf.buf;
 	}
 
 	if (mode->type == DATE_RELATIVE) {
 		struct timeval now;
 
 		strbuf_reset(&timebuf);
 		gettimeofday(&now, NULL);
 		show_date_relative(time, tz, &now, &timebuf);
 		return timebuf.buf;
 	}
 
-	tm = time_to_tm(time, tz);
+	if (mode->local)
+		tm = time_to_tm_local(time);
+	else
+		tm = time_to_tm(time, tz);
 	if (!tm) {
 		tm = time_to_tm(0, 0);
 		tz = 0;
 	}
 
 	strbuf_reset(&timebuf);
