"<tr><th>SS</th><td>Seconds since beginning of most recent request</td></tr>\n \
<tr><th>Req</th><td>Milliseconds required to process most recent request</td></tr>\n \
<tr><th>Conn</th><td>Kilobytes transferred this connection</td></tr>\n \
<tr><th>Child</th><td>Megabytes transferred this child</td></tr>\n \
<tr><th>Slot</th><td>Total megabytes transferred this slot</td></tr>\n \
</table>\n", r);
        }
    } /* if (ap_extended_status && !short_report) */
    else {

        if (!short_report) {
            ap_rputs("<hr />To obtain a full report with current status "
