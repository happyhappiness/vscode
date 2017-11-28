
    debugs(9, 7, HERE << " line ={" << line << "}");

    if (strlen(line) > 1024) {
        html = new MemBuf();
        html->init();
        html->appendf("<tr><td colspan=\"5\">%s</td></tr>\n", line);
        return html;
    }

    if (flags.dir_slash && dirpath && typecode != 'D')
        snprintf(prefix, 2048, "%s/", rfc1738_escape_part(dirpath));
    else
