            ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
            ap_rvputs(r, "</table>\n<input type=hidden name='b' id='b' ", NULL);
            ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
                      "'>\n", NULL);
            ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
                      bsel->s->nonce, "'>\n", NULL);
            ap_rvputs(r, "</form>\n", NULL);
            ap_rputs("<hr />\n", r);
        }
        ap_rputs(ap_psignature("",r), r);
        ap_rputs("</body></html>\n", r);
        ap_rflush(r);
    }
