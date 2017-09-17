    }
    else {
	alarm_fn = fn;
	alarm_expiry_time = time(NULL) + x;
    }
#else
    if (x) {
	alarm_fn = fn;
    }
#ifndef OPTIMIZE_TIMEOUTS
    old = alarm(x);
#else
    if (child_timeouts) {
	old = alarm(x);
    }
