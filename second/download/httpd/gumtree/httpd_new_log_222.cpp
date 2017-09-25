ap_fputstrs(output, bb,
                DEBUG_CR "<D:href>",
                dav_xml_escape_uri(pool, response->href),
                "</D:href>" DEBUG_CR,
                NULL);