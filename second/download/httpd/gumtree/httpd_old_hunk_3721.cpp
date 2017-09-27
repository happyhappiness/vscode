                          "ajp_marshal_into_msgb: "
                          "Error appending the method '%s' as request attribute",
                          r->method);
            return AJP_EOVERFLOW;
        }
    }
    /* Forward the remote port information, which was forgotten
     * from the builtin data of the AJP 13 protocol.
     * Since the servlet spec allows to retrieve it via getRemotePort(),
     * we provide the port to the Tomcat connector as a request
     * attribute. Modern Tomcat versions know how to retrieve
     * the remote port from this attribute.
