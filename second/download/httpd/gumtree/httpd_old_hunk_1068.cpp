            ap_rputs("<hr />To obtain a full report with current status "
                     "information you need to use the "
                     "<code>ExtendedStatus On</code> directive.\n", r);
        }
    }

    if (!short_report) {
        ap_rputs(ap_psignature("<hr />\n",r), r);
        ap_rputs("</body></html>\n", r);
    }

    return 0;
