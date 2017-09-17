<tr><th>Req<td>Milliseconds required to process most recent request\n \
<tr><th>Conn<td>Kilobytes transferred this connection\n \
<tr><th>Child<td>Megabytes transferred this child\n \
<tr><th>Slot<td>Total megabytes transferred this slot\n \
</table>\n", r);
#else
	ap_rputs("</table>\n \
<hr> \
<table>\n \
<tr><th>Srv<td>Server number\n \
<tr><th>PID<td>OS process ID\n \
<tr><th>Acc<td>Number of accesses this connection / this child / this slot\n \
<tr><th>M<td>Mode of operation\n \
