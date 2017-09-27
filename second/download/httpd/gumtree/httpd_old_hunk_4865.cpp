            ap_rputs("\n"
                     "</pre>\n", r);
        }
    }

    if (ap_extended_status && !short_report) {
        if (no_table_report)
            ap_rputs("<hr /><h2>Server Details</h2>\n\n", r);
        else
            ap_rputs("\n\n<table border=\"0\"><tr>"
                     "<th>Srv</th><th>PID</th><th>Acc</th>"
                     "<th>M</th>"
