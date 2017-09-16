<tr><th>Req<td>Milliseconds required to process most recent request\n \

<tr><th>Conn<td>Kilobytes transferred this connection\n \

<tr><th>Child<td>Megabytes transferred this child\n \

<tr><th>Slot<td>Total megabytes transferred this slot\n \

</table>\n", r);

#endif

	}



    } else {



    ap_rputs("<hr>To obtain a full report with current status information ", r);

    ap_rputs("you need to use the <code>ExtendedStatus On</code> directive. \n", r);



    }



    if (!short_report) {

	ap_rputs(ap_psignature("<HR>\n",r), r);

	ap_rputs("</BODY></HTML>\n", r);

    }



