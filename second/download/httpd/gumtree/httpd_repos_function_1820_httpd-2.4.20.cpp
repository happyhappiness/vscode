static void module_request_hook_participate(request_rec * r, module * modp)
{
    int i, comma = 0;

    ap_rputs("<dt><strong>Request Phase Participation:</strong>\n", r);

    for (i = 0; request_hooks[i].name; i++) {
        module_participate(r, modp, &request_hooks[i], &comma);
    }

    if (!comma) {
        ap_rputs("<tt> <em>none</em></tt>", r);
    }
    ap_rputs("</dt>\n", r);
}