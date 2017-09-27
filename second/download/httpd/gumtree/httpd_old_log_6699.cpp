ap_rputs("\n\n<table rules=\"all\" cellpadding=\"1%\">\n"
                     "<tr><th rowspan=\"2\">PID</th>"
                         "<th colspan=\"2\">Connections</th>\n"
                         "<th colspan=\"2\">Threads</th>"
                         "<th colspan=\"4\">Async connections</th></tr>\n"
                     "<tr><th>total</th><th>accepting</th>"
                         "<th>busy</th><th>idle</th><th>writing</th>"
                         "<th>keep-alive</th><th>closing</th></tr>\n", r);