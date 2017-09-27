ap_rputs(apr_psprintf(r->pool, 
                     "<p>\n"
                     "<table border='0'>\n"
                     "<tr>\n"
                     "<td bgcolor='#000000'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Cache Name:</b></font></td>"
                     "<td bgcolor='#ffffff'><font size='-1' face='Arial,Helvetica' color='#000000'><b>%s (%s)</b></font></td>"
                     "</tr>\n"
                     "</table>\n</p>\n",
                 buf,
                 cachetype[0] == 'm'? "Main" : 
                                  (cachetype[0] == 's' ? "Search" : 
                                   (cachetype[0] == 'c' ? "Compares" : "DNCompares"))), r);