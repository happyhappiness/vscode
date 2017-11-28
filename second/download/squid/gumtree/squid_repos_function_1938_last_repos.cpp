static void
idnsVCClosed(const CommCloseCbParams &params)
{
    nsvc * vc = (nsvc *)params.data;
    delete vc;
}