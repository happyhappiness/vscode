    }

    else {

	alarm_fn = fn;

	alarm_expiry_time = time(NULL) + x;

    }

#else

    if (alarm_fn && x && fn != alarm_fn) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, NULL,

	    "ap_set_callback_and_alarm: possible nested timer!");

    }

    alarm_fn = fn;

#ifndef OPTIMIZE_TIMEOUTS

    old = alarm(x);

#else

    if (child_timeouts) {

	old = alarm(x);

    }

