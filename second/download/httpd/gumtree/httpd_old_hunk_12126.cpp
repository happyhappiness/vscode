<tr><th>Req<td>Milliseconds required to process most recent request\n \
<tr><th>Conn<td>Kilobytes transferred this connection\n \
<tr><th>Child<td>Megabytes transferred this child\n \
<tr><th>Slot<td>Total megabytes transferred this slot\n \
</table>\n", r);
#endif
    }

#else /* !defined(STATUS) */

    ap_rputs("<hr>To obtain a full report with current status information and", r);
    ap_rputs(" DNS and LOGGING status codes \n", r);
    ap_rputs("you need to recompile Apache after adding the line <pre>", r);
    ap_rputs("Rule STATUS=yes</pre>into the file <code>Configuration</code>\n", r);

#endif /* STATUS */

    if (!short_report) {
	ap_rputs(ap_psignature("<HR>\n",r), r);
	ap_rputs("</BODY></HTML>\n", r);
    }

