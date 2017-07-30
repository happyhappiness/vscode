; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/share.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Curl_share = type { i32, i32, void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)*, i8*, %struct.curl_hash, %struct.CookieInfo*, %struct.curl_ssl_session*, i64, i64 }
%struct.Curl_easy = type { %struct.Curl_easy*, %struct.Curl_easy*, %struct.connectdata*, i32, i32, %struct.Curl_message, [5 x i32], i32, %struct.Names, %struct.Curl_multi*, %struct.Curl_multi*, %struct.Curl_share*, %struct.SingleRequest, %struct.UserDefined, %struct.DynamicStatic, %struct.CookieInfo*, %struct.Progress, %struct.UrlState, %struct.WildcardData, %struct.PureInfo, %struct.curl_tlssessioninfo, i32 }
%struct.connectdata = type { %struct.Curl_easy*, %struct.Curl_chunker, i32 (i8*, i32)*, i8*, i8, i64, %struct.Curl_dns_entry*, %struct.Curl_addrinfo*, [2 x %struct.Curl_addrinfo*], [46 x i8], i32, i32, %struct.hostname, i8*, %struct.hostname, %struct.proxy_info, %struct.proxy_info, i64, i32, i32, i16, [46 x i8], i64, [46 x i8], i64, i8*, i8*, i8*, i8*, i32, i32, %struct.timeval, %struct.timeval, [2 x i32], [2 x i32], [2 x i8], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data], %struct.ssl_primary_config, %struct.ssl_primary_config, i8, %struct.ConnectBits, %struct.timeval, i32, i64, %struct.Curl_handler*, %struct.Curl_handler*, i64, i32, i32, %struct.dynamically_allocated_data, i8, i8, %struct.curl_llist, %struct.curl_llist, i8*, i64, i64, i32 (i8*, i64, i32)*, i8*, [256 x i8], i8*, i32, i32, %union.anon, i32, i32, i8*, i16, i32, [2 x i32], %struct.connectbundle*, i32 }
%struct.Curl_chunker = type { [17 x i8], i32, i32, i64, i64 }
%struct.Curl_dns_entry = type { %struct.Curl_addrinfo*, i64, i64 }
%struct.Curl_addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.Curl_addrinfo* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.hostname = type { i8*, i8*, i8*, i8* }
%struct.proxy_info = type { %struct.hostname, i64, i32, i8*, i8* }
%struct.ssl_connect_data = type { i8, i32, i32 }
%struct.ssl_primary_config = type { i64, i64, i8, i8, i8, i8*, i8*, i8*, i8*, i8*, i8*, i8 }
%struct.ConnectBits = type { i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8 }
%struct.timeval = type { i64, i64 }
%struct.Curl_handler = type { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }
%struct.dynamically_allocated_data = type { i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8* }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%union.anon = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, i32 (%struct.connectdata*)*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }
%struct.Curl_message = type { %struct.CURLMsg }
%struct.CURLMsg = type { i32, %struct.Curl_easy*, %union.anon.0 }
%union.anon.0 = type { i8* }
%struct.Names = type { %struct.curl_hash*, i32 }
%struct.Curl_multi = type { i64, %struct.Curl_easy*, %struct.Curl_easy*, i32, i32, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_easy*, i32, i32, i8*, i8*)*, i8*, i32 (%struct.Curl_easy*, %struct.Curl_easy*, i64, %struct.curl_pushheaders*, i8*)*, i8*, %struct.curl_hash, %struct.Curl_tree*, %struct.curl_hash, i64, i8, %struct.conncache, %struct.Curl_easy*, i64, i64, i64, i64, i64, i64, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_multi*, i64, i8*)*, i8*, %struct.timeval }
%struct.curl_pushheaders = type opaque
%struct.Curl_tree = type { %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.timeval, i8* }
%struct.conncache = type { %struct.curl_hash, i64, i64, %struct.timeval }
%struct.SingleRequest = type { i64, i64*, i64, i64*, i64, i64, i64, i64, %struct.timeval, %struct.timeval, i8, i32, i32, i8*, i64, i8*, i8*, i8*, i8*, i8, i64, i32, %struct.timeval, i32, i32, i32, i64, i64, i8*, i8*, i32, i32, i8, i8, i8, i8*, i8*, i64, i8*, i8, i8, i8, i8, i8* }
%struct.UserDefined = type { %struct._IO_FILE*, i8*, i8*, i64, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i64, i32, i8, i8*, i32 (i8*, i64, i32)*, i64, i16, i32, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i32, i32, i32 (i8*, double, double, double, double)*, i32 (i8*, i64, i64, i64, i64)*, i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)*, i32 (%struct.Curl_easy*, i32, i8*)*, i32 (i8*, i32, i32)*, i8*, i32 (i8*, i32, %struct.curl_sockaddr*)*, i8*, i32 (i8*, i32)*, i8*, i8*, i32 (i8*, i64)*, i32 (i8*, i64)*, i32 (i8*, i64)*, i8*, i8*, i64, i64, i64, i64, i64, i8, i64, i64, i64, i64, i64, i64, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_httppost*, i8, i8, i8, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, i32, i64, i32, i64, %struct.ssl_config_data, %struct.ssl_config_data, %struct.ssl_general_config, i32, i64, i64, i8*, %struct.curl_slist*, i64, i64, i32, i32, i32 (%struct.Curl_easy*, %struct.curl_khkey*, %struct.curl_khkey*, i32, i8*)*, i8*, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i32, i8, i8, i8, i8, i8, i8, i8, i32, i32, i32, i8, i8, i8, i8, i8, i8, i64, i8, i8, i64, i64, i8, [56 x i8*], i32, i64, i64, %struct.curl_slist*, i8, i32, i64, i8, i64 (i8*, i8*, i32)*, i64 (i8*)*, i32 (i8*, i8*, i8*)*, i8*, i64, i8, i64, i64, i8, i64, i8, i8, i8, i8, i64, i8, %struct.Curl_easy*, i8, i32, %struct.Curl_http2_dep*, i8 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.curl_sockaddr = type { i32, i32, i32, i32, %struct.sockaddr }
%struct.curl_httppost = type { %struct.curl_httppost*, i8*, i64, i8*, i64, i8*, i64, i8*, %struct.curl_slist*, %struct.curl_httppost*, i64, i8*, i8*, i64 }
%struct.ssl_config_data = type { %struct.ssl_primary_config, i8, i8, i64, i8*, i8*, i32 (%struct.Curl_easy*, i8*, i8*)*, i8*, i8, i8, i8*, i8*, i8*, i8*, i8* }
%struct.ssl_general_config = type { i64 }
%struct.curl_khkey = type { i8*, i64, i32 }
%struct.curl_slist = type { i8*, %struct.curl_slist* }
%struct.Curl_http2_dep = type { %struct.Curl_http2_dep*, %struct.Curl_easy* }
%struct.DynamicStatic = type { i8*, i8, i8*, i8, %struct.curl_slist*, %struct.curl_slist* }
%struct.Progress = type { i64, i64, i64, i64, i64, i64, i8, i32, i32, double, i64, i64, double, double, double, double, double, double, %struct.timeval, %struct.timeval, %struct.timeval, %struct.timeval, %struct.timeval, i64, %struct.timeval, i64, [6 x i64], [6 x %struct.timeval], i32 }
%struct.UrlState = type { %struct.conncache*, i8, %struct.timeval, %struct.connectdata*, i8*, i64, i8*, [16385 x i8], i64, i8, i8*, i32, %struct.curl_ssl_session*, i64, i32, [3 x %struct.tempbuf], i8*, i8, i32, void (i32)*, i8, %struct.digestdata, %struct.digestdata, %struct.auth, %struct.auth, i8, i8*, %struct.timeval, %struct.Curl_tree, %struct.curl_llist, i8*, i8, i32, i8, i8, i8, i64, i8*, i8*, i8, i8, i8, i8*, i64, i64, i64, i64, i64, i64, i8, i64 (i8*, i64, i64, i8*)*, i8*, %struct.Curl_easy*, i8, i32 }
%struct.tempbuf = type { i8*, i64, i32 }
%struct.digestdata = type { i8*, i8*, i8*, i32, i8, i8*, i8*, i8*, i32 }
%struct.auth = type { i64, i64, i64, i8, i8, i8 }
%struct.WildcardData = type { i32, i8*, i8*, %struct.curl_llist, i8*, void (i8*)*, i8* }
%struct.PureInfo = type { i32, i32, i32, i64, i8, i64, i64, i64, i64, i64, i8*, i8*, [46 x i8], i64, [46 x i8], i64, i8*, i32, %struct.curl_certinfo }
%struct.curl_certinfo = type { i32, %struct.curl_slist** }
%struct.curl_tlssessioninfo = type { i32, i8* }
%struct.curl_hash = type { %struct.curl_llist*, i64 (i8*, i64, i64)*, i64 (i8*, i64, i8*, i64)*, void (i8*)*, i32, i64 }
%struct.CookieInfo = type { %struct.Cookie*, i8*, i8, i64, i8 }
%struct.Cookie = type { %struct.Cookie*, i8*, i8*, i8*, i8*, i8*, i64, i8*, i8, i8*, i8*, i8, i8, i8 }
%struct.curl_ssl_session = type { i8*, i8*, i8*, i8*, i64, i64, i32, i32, %struct.ssl_primary_config }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@Curl_ccalloc = external global i8* (i64, i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define %struct.Curl_share* @curl_share_init() #0 !dbg !1736 {
entry:
  %retval = alloca %struct.Curl_share*, align 8
  %share = alloca %struct.Curl_share*, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_share** %share, metadata !1759, metadata !1760), !dbg !1761
  %0 = load i8* (i64, i64)*, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !1762
  %call = call i8* %0(i64 1, i64 112), !dbg !1762
  %1 = bitcast i8* %call to %struct.Curl_share*, !dbg !1762
  store %struct.Curl_share* %1, %struct.Curl_share** %share, align 8, !dbg !1761
  %2 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1763
  %tobool = icmp ne %struct.Curl_share* %2, null, !dbg !1763
  br i1 %tobool, label %if.then, label %if.end4, !dbg !1765

if.then:                                          ; preds = %entry
  %3 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1766
  %specifier = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %3, i32 0, i32 0, !dbg !1768
  %4 = load i32, i32* %specifier, align 8, !dbg !1769
  %or = or i32 %4, 2, !dbg !1769
  store i32 %or, i32* %specifier, align 8, !dbg !1769
  %5 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1770
  %hostcache = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %5, i32 0, i32 5, !dbg !1772
  %call1 = call i32 @Curl_mk_dnscache(%struct.curl_hash* %hostcache), !dbg !1773
  %tobool2 = icmp ne i32 %call1, 0, !dbg !1773
  br i1 %tobool2, label %if.then3, label %if.end, !dbg !1774

if.then3:                                         ; preds = %if.then
  %6 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1775
  %7 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1775
  %8 = bitcast %struct.Curl_share* %7 to i8*, !dbg !1775
  call void %6(i8* %8), !dbg !1775
  store %struct.Curl_share* null, %struct.Curl_share** %retval, align 8, !dbg !1777
  br label %return, !dbg !1777

if.end:                                           ; preds = %if.then
  br label %if.end4, !dbg !1778

if.end4:                                          ; preds = %if.end, %entry
  %9 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1779
  store %struct.Curl_share* %9, %struct.Curl_share** %retval, align 8, !dbg !1780
  br label %return, !dbg !1780

return:                                           ; preds = %if.end4, %if.then3
  %10 = load %struct.Curl_share*, %struct.Curl_share** %retval, align 8, !dbg !1781
  ret %struct.Curl_share* %10, !dbg !1781
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @Curl_mk_dnscache(%struct.curl_hash*) #2

; Function Attrs: nounwind uwtable
define i32 @curl_share_setopt(%struct.Curl_share* %share, i32 %option, ...) #0 !dbg !1742 {
entry:
  %retval = alloca i32, align 4
  %share.addr = alloca %struct.Curl_share*, align 8
  %option.addr = alloca i32, align 4
  %param = alloca [1 x %struct.__va_list_tag], align 16
  %type = alloca i32, align 4
  %lockfunc = alloca void (%struct.Curl_easy*, i32, i32, i8*)*, align 8
  %unlockfunc = alloca void (%struct.Curl_easy*, i32, i8*)*, align 8
  %ptr = alloca i8*, align 8
  %res = alloca i32, align 4
  store %struct.Curl_share* %share, %struct.Curl_share** %share.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_share** %share.addr, metadata !1782, metadata !1760), !dbg !1783
  store i32 %option, i32* %option.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option.addr, metadata !1784, metadata !1760), !dbg !1785
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %param, metadata !1786, metadata !1760), !dbg !1798
  call void @llvm.dbg.declare(metadata i32* %type, metadata !1799, metadata !1760), !dbg !1800
  call void @llvm.dbg.declare(metadata void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc, metadata !1801, metadata !1760), !dbg !1802
  call void @llvm.dbg.declare(metadata void (%struct.Curl_easy*, i32, i8*)** %unlockfunc, metadata !1803, metadata !1760), !dbg !1804
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !1805, metadata !1760), !dbg !1806
  call void @llvm.dbg.declare(metadata i32* %res, metadata !1807, metadata !1760), !dbg !1808
  store i32 0, i32* %res, align 4, !dbg !1808
  %0 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1809
  %dirty = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %0, i32 0, i32 1, !dbg !1811
  %1 = load volatile i32, i32* %dirty, align 4, !dbg !1811
  %tobool = icmp ne i32 %1, 0, !dbg !1809
  br i1 %tobool, label %if.then, label %if.end, !dbg !1812

if.then:                                          ; preds = %entry
  store i32 2, i32* %retval, align 4, !dbg !1813
  br label %return, !dbg !1813

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1814
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1814
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1814
  %2 = load i32, i32* %option.addr, align 4, !dbg !1815
  switch i32 %2, label %sw.default83 [
    i32 1, label %sw.bb
    i32 2, label %sw.bb15
    i32 3, label %sw.bb42
    i32 4, label %sw.bb56
    i32 5, label %sw.bb70
  ], !dbg !1816

sw.bb:                                            ; preds = %if.end
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1817
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 0, !dbg !1817
  %gp_offset = load i32, i32* %gp_offset_p, align 16, !dbg !1817
  %fits_in_gp = icmp ule i32 %gp_offset, 40, !dbg !1817
  br i1 %fits_in_gp, label %vaarg.in_reg, label %vaarg.in_mem, !dbg !1817

vaarg.in_reg:                                     ; preds = %sw.bb
  %3 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 3, !dbg !1819
  %reg_save_area = load i8*, i8** %3, align 16, !dbg !1819
  %4 = getelementptr i8, i8* %reg_save_area, i32 %gp_offset, !dbg !1819
  %5 = bitcast i8* %4 to i32*, !dbg !1819
  %6 = add i32 %gp_offset, 8, !dbg !1819
  store i32 %6, i32* %gp_offset_p, align 16, !dbg !1819
  br label %vaarg.end, !dbg !1819

vaarg.in_mem:                                     ; preds = %sw.bb
  %overflow_arg_area_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 2, !dbg !1821
  %overflow_arg_area = load i8*, i8** %overflow_arg_area_p, align 8, !dbg !1821
  %7 = bitcast i8* %overflow_arg_area to i32*, !dbg !1821
  %overflow_arg_area.next = getelementptr i8, i8* %overflow_arg_area, i32 8, !dbg !1821
  store i8* %overflow_arg_area.next, i8** %overflow_arg_area_p, align 8, !dbg !1821
  br label %vaarg.end, !dbg !1821

vaarg.end:                                        ; preds = %vaarg.in_mem, %vaarg.in_reg
  %vaarg.addr = phi i32* [ %5, %vaarg.in_reg ], [ %7, %vaarg.in_mem ], !dbg !1823
  %8 = load i32, i32* %vaarg.addr, align 4, !dbg !1823
  store i32 %8, i32* %type, align 4, !dbg !1825
  %9 = load i32, i32* %type, align 4, !dbg !1826
  %shl = shl i32 1, %9, !dbg !1827
  %10 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1828
  %specifier = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %10, i32 0, i32 0, !dbg !1829
  %11 = load i32, i32* %specifier, align 8, !dbg !1830
  %or = or i32 %11, %shl, !dbg !1830
  store i32 %or, i32* %specifier, align 8, !dbg !1830
  %12 = load i32, i32* %type, align 4, !dbg !1831
  switch i32 %12, label %sw.default [
    i32 3, label %sw.bb3
    i32 2, label %sw.bb4
    i32 4, label %sw.bb13
    i32 5, label %sw.bb14
  ], !dbg !1832

sw.bb3:                                           ; preds = %vaarg.end
  br label %sw.epilog, !dbg !1833

sw.bb4:                                           ; preds = %vaarg.end
  %13 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1835
  %cookies = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %13, i32 0, i32 6, !dbg !1837
  %14 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies, align 8, !dbg !1837
  %tobool5 = icmp ne %struct.CookieInfo* %14, null, !dbg !1835
  br i1 %tobool5, label %if.end12, label %if.then6, !dbg !1838

if.then6:                                         ; preds = %sw.bb4
  %call = call %struct.CookieInfo* @Curl_cookie_init(%struct.Curl_easy* null, i8* null, %struct.CookieInfo* null, i1 zeroext true), !dbg !1839
  %15 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1841
  %cookies7 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %15, i32 0, i32 6, !dbg !1842
  store %struct.CookieInfo* %call, %struct.CookieInfo** %cookies7, align 8, !dbg !1843
  %16 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1844
  %cookies8 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %16, i32 0, i32 6, !dbg !1846
  %17 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies8, align 8, !dbg !1846
  %tobool9 = icmp ne %struct.CookieInfo* %17, null, !dbg !1844
  br i1 %tobool9, label %if.end11, label %if.then10, !dbg !1847

if.then10:                                        ; preds = %if.then6
  store i32 4, i32* %res, align 4, !dbg !1848
  br label %if.end11, !dbg !1849

if.end11:                                         ; preds = %if.then10, %if.then6
  br label %if.end12, !dbg !1850

if.end12:                                         ; preds = %if.end11, %sw.bb4
  br label %sw.epilog, !dbg !1851

sw.bb13:                                          ; preds = %vaarg.end
  store i32 5, i32* %res, align 4, !dbg !1852
  br label %sw.epilog, !dbg !1853

sw.bb14:                                          ; preds = %vaarg.end
  br label %sw.epilog, !dbg !1854

sw.default:                                       ; preds = %vaarg.end
  store i32 1, i32* %res, align 4, !dbg !1855
  br label %sw.epilog, !dbg !1856

sw.epilog:                                        ; preds = %sw.default, %sw.bb14, %sw.bb13, %if.end12, %sw.bb3
  br label %sw.epilog84, !dbg !1857

sw.bb15:                                          ; preds = %if.end
  %arraydecay16 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1858
  %gp_offset_p17 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay16, i32 0, i32 0, !dbg !1858
  %gp_offset18 = load i32, i32* %gp_offset_p17, align 16, !dbg !1858
  %fits_in_gp19 = icmp ule i32 %gp_offset18, 40, !dbg !1858
  br i1 %fits_in_gp19, label %vaarg.in_reg20, label %vaarg.in_mem22, !dbg !1858

vaarg.in_reg20:                                   ; preds = %sw.bb15
  %18 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay16, i32 0, i32 3, !dbg !1859
  %reg_save_area21 = load i8*, i8** %18, align 16, !dbg !1859
  %19 = getelementptr i8, i8* %reg_save_area21, i32 %gp_offset18, !dbg !1859
  %20 = bitcast i8* %19 to i32*, !dbg !1859
  %21 = add i32 %gp_offset18, 8, !dbg !1859
  store i32 %21, i32* %gp_offset_p17, align 16, !dbg !1859
  br label %vaarg.end26, !dbg !1859

vaarg.in_mem22:                                   ; preds = %sw.bb15
  %overflow_arg_area_p23 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay16, i32 0, i32 2, !dbg !1860
  %overflow_arg_area24 = load i8*, i8** %overflow_arg_area_p23, align 8, !dbg !1860
  %22 = bitcast i8* %overflow_arg_area24 to i32*, !dbg !1860
  %overflow_arg_area.next25 = getelementptr i8, i8* %overflow_arg_area24, i32 8, !dbg !1860
  store i8* %overflow_arg_area.next25, i8** %overflow_arg_area_p23, align 8, !dbg !1860
  br label %vaarg.end26, !dbg !1860

vaarg.end26:                                      ; preds = %vaarg.in_mem22, %vaarg.in_reg20
  %vaarg.addr27 = phi i32* [ %20, %vaarg.in_reg20 ], [ %22, %vaarg.in_mem22 ], !dbg !1861
  %23 = load i32, i32* %vaarg.addr27, align 4, !dbg !1861
  store i32 %23, i32* %type, align 4, !dbg !1862
  %24 = load i32, i32* %type, align 4, !dbg !1863
  %shl28 = shl i32 1, %24, !dbg !1864
  %neg = xor i32 %shl28, -1, !dbg !1865
  %25 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1866
  %specifier29 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %25, i32 0, i32 0, !dbg !1867
  %26 = load i32, i32* %specifier29, align 8, !dbg !1868
  %and = and i32 %26, %neg, !dbg !1868
  store i32 %and, i32* %specifier29, align 8, !dbg !1868
  %27 = load i32, i32* %type, align 4, !dbg !1869
  switch i32 %27, label %sw.default40 [
    i32 3, label %sw.bb30
    i32 2, label %sw.bb31
    i32 4, label %sw.bb38
    i32 5, label %sw.bb39
  ], !dbg !1870

sw.bb30:                                          ; preds = %vaarg.end26
  br label %sw.epilog41, !dbg !1871

sw.bb31:                                          ; preds = %vaarg.end26
  %28 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1873
  %cookies32 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %28, i32 0, i32 6, !dbg !1875
  %29 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies32, align 8, !dbg !1875
  %tobool33 = icmp ne %struct.CookieInfo* %29, null, !dbg !1873
  br i1 %tobool33, label %if.then34, label %if.end37, !dbg !1876

if.then34:                                        ; preds = %sw.bb31
  %30 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1877
  %cookies35 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %30, i32 0, i32 6, !dbg !1879
  %31 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies35, align 8, !dbg !1879
  call void @Curl_cookie_cleanup(%struct.CookieInfo* %31), !dbg !1880
  %32 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1881
  %cookies36 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %32, i32 0, i32 6, !dbg !1882
  store %struct.CookieInfo* null, %struct.CookieInfo** %cookies36, align 8, !dbg !1883
  br label %if.end37, !dbg !1884

if.end37:                                         ; preds = %if.then34, %sw.bb31
  br label %sw.epilog41, !dbg !1885

sw.bb38:                                          ; preds = %vaarg.end26
  store i32 5, i32* %res, align 4, !dbg !1886
  br label %sw.epilog41, !dbg !1887

sw.bb39:                                          ; preds = %vaarg.end26
  br label %sw.epilog41, !dbg !1888

sw.default40:                                     ; preds = %vaarg.end26
  store i32 1, i32* %res, align 4, !dbg !1889
  br label %sw.epilog41, !dbg !1890

sw.epilog41:                                      ; preds = %sw.default40, %sw.bb39, %sw.bb38, %if.end37, %sw.bb30
  br label %sw.epilog84, !dbg !1891

sw.bb42:                                          ; preds = %if.end
  %arraydecay43 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1892
  %gp_offset_p44 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay43, i32 0, i32 0, !dbg !1892
  %gp_offset45 = load i32, i32* %gp_offset_p44, align 16, !dbg !1892
  %fits_in_gp46 = icmp ule i32 %gp_offset45, 40, !dbg !1892
  br i1 %fits_in_gp46, label %vaarg.in_reg47, label %vaarg.in_mem49, !dbg !1892

vaarg.in_reg47:                                   ; preds = %sw.bb42
  %33 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay43, i32 0, i32 3, !dbg !1893
  %reg_save_area48 = load i8*, i8** %33, align 16, !dbg !1893
  %34 = getelementptr i8, i8* %reg_save_area48, i32 %gp_offset45, !dbg !1893
  %35 = bitcast i8* %34 to void (%struct.Curl_easy*, i32, i32, i8*)**, !dbg !1893
  %36 = add i32 %gp_offset45, 8, !dbg !1893
  store i32 %36, i32* %gp_offset_p44, align 16, !dbg !1893
  br label %vaarg.end53, !dbg !1893

vaarg.in_mem49:                                   ; preds = %sw.bb42
  %overflow_arg_area_p50 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay43, i32 0, i32 2, !dbg !1894
  %overflow_arg_area51 = load i8*, i8** %overflow_arg_area_p50, align 8, !dbg !1894
  %37 = bitcast i8* %overflow_arg_area51 to void (%struct.Curl_easy*, i32, i32, i8*)**, !dbg !1894
  %overflow_arg_area.next52 = getelementptr i8, i8* %overflow_arg_area51, i32 8, !dbg !1894
  store i8* %overflow_arg_area.next52, i8** %overflow_arg_area_p50, align 8, !dbg !1894
  br label %vaarg.end53, !dbg !1894

vaarg.end53:                                      ; preds = %vaarg.in_mem49, %vaarg.in_reg47
  %vaarg.addr54 = phi void (%struct.Curl_easy*, i32, i32, i8*)** [ %35, %vaarg.in_reg47 ], [ %37, %vaarg.in_mem49 ], !dbg !1895
  %38 = load void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i32, i8*)** %vaarg.addr54, align 8, !dbg !1895
  store void (%struct.Curl_easy*, i32, i32, i8*)* %38, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc, align 8, !dbg !1896
  %39 = load void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc, align 8, !dbg !1897
  %40 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1898
  %lockfunc55 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %40, i32 0, i32 2, !dbg !1899
  store void (%struct.Curl_easy*, i32, i32, i8*)* %39, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc55, align 8, !dbg !1900
  br label %sw.epilog84, !dbg !1901

sw.bb56:                                          ; preds = %if.end
  %arraydecay57 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1902
  %gp_offset_p58 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay57, i32 0, i32 0, !dbg !1902
  %gp_offset59 = load i32, i32* %gp_offset_p58, align 16, !dbg !1902
  %fits_in_gp60 = icmp ule i32 %gp_offset59, 40, !dbg !1902
  br i1 %fits_in_gp60, label %vaarg.in_reg61, label %vaarg.in_mem63, !dbg !1902

vaarg.in_reg61:                                   ; preds = %sw.bb56
  %41 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay57, i32 0, i32 3, !dbg !1903
  %reg_save_area62 = load i8*, i8** %41, align 16, !dbg !1903
  %42 = getelementptr i8, i8* %reg_save_area62, i32 %gp_offset59, !dbg !1903
  %43 = bitcast i8* %42 to void (%struct.Curl_easy*, i32, i8*)**, !dbg !1903
  %44 = add i32 %gp_offset59, 8, !dbg !1903
  store i32 %44, i32* %gp_offset_p58, align 16, !dbg !1903
  br label %vaarg.end67, !dbg !1903

vaarg.in_mem63:                                   ; preds = %sw.bb56
  %overflow_arg_area_p64 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay57, i32 0, i32 2, !dbg !1904
  %overflow_arg_area65 = load i8*, i8** %overflow_arg_area_p64, align 8, !dbg !1904
  %45 = bitcast i8* %overflow_arg_area65 to void (%struct.Curl_easy*, i32, i8*)**, !dbg !1904
  %overflow_arg_area.next66 = getelementptr i8, i8* %overflow_arg_area65, i32 8, !dbg !1904
  store i8* %overflow_arg_area.next66, i8** %overflow_arg_area_p64, align 8, !dbg !1904
  br label %vaarg.end67, !dbg !1904

vaarg.end67:                                      ; preds = %vaarg.in_mem63, %vaarg.in_reg61
  %vaarg.addr68 = phi void (%struct.Curl_easy*, i32, i8*)** [ %43, %vaarg.in_reg61 ], [ %45, %vaarg.in_mem63 ], !dbg !1905
  %46 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %vaarg.addr68, align 8, !dbg !1905
  store void (%struct.Curl_easy*, i32, i8*)* %46, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc, align 8, !dbg !1906
  %47 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc, align 8, !dbg !1907
  %48 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1908
  %unlockfunc69 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %48, i32 0, i32 3, !dbg !1909
  store void (%struct.Curl_easy*, i32, i8*)* %47, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc69, align 8, !dbg !1910
  br label %sw.epilog84, !dbg !1911

sw.bb70:                                          ; preds = %if.end
  %arraydecay71 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1912
  %gp_offset_p72 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay71, i32 0, i32 0, !dbg !1912
  %gp_offset73 = load i32, i32* %gp_offset_p72, align 16, !dbg !1912
  %fits_in_gp74 = icmp ule i32 %gp_offset73, 40, !dbg !1912
  br i1 %fits_in_gp74, label %vaarg.in_reg75, label %vaarg.in_mem77, !dbg !1912

vaarg.in_reg75:                                   ; preds = %sw.bb70
  %49 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay71, i32 0, i32 3, !dbg !1913
  %reg_save_area76 = load i8*, i8** %49, align 16, !dbg !1913
  %50 = getelementptr i8, i8* %reg_save_area76, i32 %gp_offset73, !dbg !1913
  %51 = bitcast i8* %50 to i8**, !dbg !1913
  %52 = add i32 %gp_offset73, 8, !dbg !1913
  store i32 %52, i32* %gp_offset_p72, align 16, !dbg !1913
  br label %vaarg.end81, !dbg !1913

vaarg.in_mem77:                                   ; preds = %sw.bb70
  %overflow_arg_area_p78 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay71, i32 0, i32 2, !dbg !1914
  %overflow_arg_area79 = load i8*, i8** %overflow_arg_area_p78, align 8, !dbg !1914
  %53 = bitcast i8* %overflow_arg_area79 to i8**, !dbg !1914
  %overflow_arg_area.next80 = getelementptr i8, i8* %overflow_arg_area79, i32 8, !dbg !1914
  store i8* %overflow_arg_area.next80, i8** %overflow_arg_area_p78, align 8, !dbg !1914
  br label %vaarg.end81, !dbg !1914

vaarg.end81:                                      ; preds = %vaarg.in_mem77, %vaarg.in_reg75
  %vaarg.addr82 = phi i8** [ %51, %vaarg.in_reg75 ], [ %53, %vaarg.in_mem77 ], !dbg !1915
  %54 = load i8*, i8** %vaarg.addr82, align 8, !dbg !1915
  store i8* %54, i8** %ptr, align 8, !dbg !1916
  %55 = load i8*, i8** %ptr, align 8, !dbg !1917
  %56 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1918
  %clientdata = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %56, i32 0, i32 4, !dbg !1919
  store i8* %55, i8** %clientdata, align 8, !dbg !1920
  br label %sw.epilog84, !dbg !1921

sw.default83:                                     ; preds = %if.end
  store i32 1, i32* %res, align 4, !dbg !1922
  br label %sw.epilog84, !dbg !1923

sw.epilog84:                                      ; preds = %sw.default83, %vaarg.end81, %vaarg.end67, %vaarg.end53, %sw.epilog41, %sw.epilog
  %arraydecay85 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %param, i32 0, i32 0, !dbg !1924
  %arraydecay8586 = bitcast %struct.__va_list_tag* %arraydecay85 to i8*, !dbg !1924
  call void @llvm.va_end(i8* %arraydecay8586), !dbg !1924
  %57 = load i32, i32* %res, align 4, !dbg !1925
  store i32 %57, i32* %retval, align 4, !dbg !1926
  br label %return, !dbg !1926

return:                                           ; preds = %sw.epilog84, %if.then
  %58 = load i32, i32* %retval, align 4, !dbg !1927
  ret i32 %58, !dbg !1927
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #3

declare %struct.CookieInfo* @Curl_cookie_init(%struct.Curl_easy*, i8*, %struct.CookieInfo*, i1 zeroext) #2

declare void @Curl_cookie_cleanup(%struct.CookieInfo*) #2

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #3

; Function Attrs: nounwind uwtable
define i32 @curl_share_cleanup(%struct.Curl_share* %share) #0 !dbg !1747 {
entry:
  %retval = alloca i32, align 4
  %share.addr = alloca %struct.Curl_share*, align 8
  store %struct.Curl_share* %share, %struct.Curl_share** %share.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_share** %share.addr, metadata !1928, metadata !1760), !dbg !1929
  %0 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1930
  %cmp = icmp eq %struct.Curl_share* %0, null, !dbg !1932
  br i1 %cmp, label %if.then, label %if.end, !dbg !1933

if.then:                                          ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !1934
  br label %return, !dbg !1934

if.end:                                           ; preds = %entry
  %1 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1935
  %lockfunc = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %1, i32 0, i32 2, !dbg !1937
  %2 = load void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc, align 8, !dbg !1937
  %tobool = icmp ne void (%struct.Curl_easy*, i32, i32, i8*)* %2, null, !dbg !1935
  br i1 %tobool, label %if.then1, label %if.end3, !dbg !1938

if.then1:                                         ; preds = %if.end
  %3 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1939
  %lockfunc2 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %3, i32 0, i32 2, !dbg !1940
  %4 = load void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc2, align 8, !dbg !1940
  %5 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1941
  %clientdata = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %5, i32 0, i32 4, !dbg !1942
  %6 = load i8*, i8** %clientdata, align 8, !dbg !1942
  call void %4(%struct.Curl_easy* null, i32 1, i32 2, i8* %6), !dbg !1939
  br label %if.end3, !dbg !1939

if.end3:                                          ; preds = %if.then1, %if.end
  %7 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1943
  %dirty = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %7, i32 0, i32 1, !dbg !1945
  %8 = load volatile i32, i32* %dirty, align 4, !dbg !1945
  %tobool4 = icmp ne i32 %8, 0, !dbg !1943
  br i1 %tobool4, label %if.then5, label %if.end11, !dbg !1946

if.then5:                                         ; preds = %if.end3
  %9 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1947
  %unlockfunc = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %9, i32 0, i32 3, !dbg !1950
  %10 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc, align 8, !dbg !1950
  %tobool6 = icmp ne void (%struct.Curl_easy*, i32, i8*)* %10, null, !dbg !1947
  br i1 %tobool6, label %if.then7, label %if.end10, !dbg !1951

if.then7:                                         ; preds = %if.then5
  %11 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1952
  %unlockfunc8 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %11, i32 0, i32 3, !dbg !1953
  %12 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc8, align 8, !dbg !1953
  %13 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1954
  %clientdata9 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %13, i32 0, i32 4, !dbg !1955
  %14 = load i8*, i8** %clientdata9, align 8, !dbg !1955
  call void %12(%struct.Curl_easy* null, i32 1, i8* %14), !dbg !1952
  br label %if.end10, !dbg !1952

if.end10:                                         ; preds = %if.then7, %if.then5
  store i32 2, i32* %retval, align 4, !dbg !1956
  br label %return, !dbg !1956

if.end11:                                         ; preds = %if.end3
  %15 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1957
  %hostcache = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %15, i32 0, i32 5, !dbg !1958
  call void @Curl_hash_destroy(%struct.curl_hash* %hostcache), !dbg !1959
  %16 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1960
  %cookies = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %16, i32 0, i32 6, !dbg !1961
  %17 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies, align 8, !dbg !1961
  call void @Curl_cookie_cleanup(%struct.CookieInfo* %17), !dbg !1962
  %18 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1963
  %unlockfunc12 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %18, i32 0, i32 3, !dbg !1965
  %19 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc12, align 8, !dbg !1965
  %tobool13 = icmp ne void (%struct.Curl_easy*, i32, i8*)* %19, null, !dbg !1963
  br i1 %tobool13, label %if.then14, label %if.end17, !dbg !1966

if.then14:                                        ; preds = %if.end11
  %20 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1967
  %unlockfunc15 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %20, i32 0, i32 3, !dbg !1968
  %21 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc15, align 8, !dbg !1968
  %22 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1969
  %clientdata16 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %22, i32 0, i32 4, !dbg !1970
  %23 = load i8*, i8** %clientdata16, align 8, !dbg !1970
  call void %21(%struct.Curl_easy* null, i32 1, i8* %23), !dbg !1967
  br label %if.end17, !dbg !1967

if.end17:                                         ; preds = %if.then14, %if.end11
  %24 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1971
  %25 = load %struct.Curl_share*, %struct.Curl_share** %share.addr, align 8, !dbg !1971
  %26 = bitcast %struct.Curl_share* %25 to i8*, !dbg !1971
  call void %24(i8* %26), !dbg !1971
  store i32 0, i32* %retval, align 4, !dbg !1972
  br label %return, !dbg !1972

return:                                           ; preds = %if.end17, %if.end10, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !1973
  ret i32 %27, !dbg !1973
}

declare void @Curl_hash_destroy(%struct.curl_hash*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_share_lock(%struct.Curl_easy* %data, i32 %type, i32 %accesstype) #0 !dbg !1750 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %type.addr = alloca i32, align 4
  %accesstype.addr = alloca i32, align 4
  %share = alloca %struct.Curl_share*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1974, metadata !1760), !dbg !1975
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1976, metadata !1760), !dbg !1977
  store i32 %accesstype, i32* %accesstype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %accesstype.addr, metadata !1978, metadata !1760), !dbg !1979
  call void @llvm.dbg.declare(metadata %struct.Curl_share** %share, metadata !1980, metadata !1760), !dbg !1981
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1982
  %share1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 11, !dbg !1983
  %1 = load %struct.Curl_share*, %struct.Curl_share** %share1, align 8, !dbg !1983
  store %struct.Curl_share* %1, %struct.Curl_share** %share, align 8, !dbg !1981
  %2 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1984
  %cmp = icmp eq %struct.Curl_share* %2, null, !dbg !1986
  br i1 %cmp, label %if.then, label %if.end, !dbg !1987

if.then:                                          ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !1988
  br label %return, !dbg !1988

if.end:                                           ; preds = %entry
  %3 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1989
  %specifier = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %3, i32 0, i32 0, !dbg !1991
  %4 = load i32, i32* %specifier, align 8, !dbg !1991
  %5 = load i32, i32* %type.addr, align 4, !dbg !1992
  %shl = shl i32 1, %5, !dbg !1993
  %and = and i32 %4, %shl, !dbg !1994
  %tobool = icmp ne i32 %and, 0, !dbg !1994
  br i1 %tobool, label %if.then2, label %if.end7, !dbg !1995

if.then2:                                         ; preds = %if.end
  %6 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1996
  %lockfunc = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %6, i32 0, i32 2, !dbg !1999
  %7 = load void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc, align 8, !dbg !1999
  %tobool3 = icmp ne void (%struct.Curl_easy*, i32, i32, i8*)* %7, null, !dbg !1996
  br i1 %tobool3, label %if.then4, label %if.end6, !dbg !2000

if.then4:                                         ; preds = %if.then2
  %8 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2001
  %lockfunc5 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %8, i32 0, i32 2, !dbg !2002
  %9 = load void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i32, i8*)** %lockfunc5, align 8, !dbg !2002
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2003
  %11 = load i32, i32* %type.addr, align 4, !dbg !2004
  %12 = load i32, i32* %accesstype.addr, align 4, !dbg !2005
  %13 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2006
  %clientdata = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %13, i32 0, i32 4, !dbg !2007
  %14 = load i8*, i8** %clientdata, align 8, !dbg !2007
  call void %9(%struct.Curl_easy* %10, i32 %11, i32 %12, i8* %14), !dbg !2001
  br label %if.end6, !dbg !2001

if.end6:                                          ; preds = %if.then4, %if.then2
  br label %if.end7, !dbg !2008

if.end7:                                          ; preds = %if.end6, %if.end
  store i32 0, i32* %retval, align 4, !dbg !2009
  br label %return, !dbg !2009

return:                                           ; preds = %if.end7, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !2010
  ret i32 %15, !dbg !2010
}

; Function Attrs: nounwind uwtable
define i32 @Curl_share_unlock(%struct.Curl_easy* %data, i32 %type) #0 !dbg !1753 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %type.addr = alloca i32, align 4
  %share = alloca %struct.Curl_share*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2011, metadata !1760), !dbg !2012
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !2013, metadata !1760), !dbg !2014
  call void @llvm.dbg.declare(metadata %struct.Curl_share** %share, metadata !2015, metadata !1760), !dbg !2016
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2017
  %share1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 11, !dbg !2018
  %1 = load %struct.Curl_share*, %struct.Curl_share** %share1, align 8, !dbg !2018
  store %struct.Curl_share* %1, %struct.Curl_share** %share, align 8, !dbg !2016
  %2 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2019
  %cmp = icmp eq %struct.Curl_share* %2, null, !dbg !2021
  br i1 %cmp, label %if.then, label %if.end, !dbg !2022

if.then:                                          ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !2023
  br label %return, !dbg !2023

if.end:                                           ; preds = %entry
  %3 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2024
  %specifier = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %3, i32 0, i32 0, !dbg !2026
  %4 = load i32, i32* %specifier, align 8, !dbg !2026
  %5 = load i32, i32* %type.addr, align 4, !dbg !2027
  %shl = shl i32 1, %5, !dbg !2028
  %and = and i32 %4, %shl, !dbg !2029
  %tobool = icmp ne i32 %and, 0, !dbg !2029
  br i1 %tobool, label %if.then2, label %if.end7, !dbg !2030

if.then2:                                         ; preds = %if.end
  %6 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2031
  %unlockfunc = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %6, i32 0, i32 3, !dbg !2034
  %7 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc, align 8, !dbg !2034
  %tobool3 = icmp ne void (%struct.Curl_easy*, i32, i8*)* %7, null, !dbg !2031
  br i1 %tobool3, label %if.then4, label %if.end6, !dbg !2035

if.then4:                                         ; preds = %if.then2
  %8 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2036
  %unlockfunc5 = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %8, i32 0, i32 3, !dbg !2037
  %9 = load void (%struct.Curl_easy*, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)** %unlockfunc5, align 8, !dbg !2037
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2038
  %11 = load i32, i32* %type.addr, align 4, !dbg !2039
  %12 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2040
  %clientdata = getelementptr inbounds %struct.Curl_share, %struct.Curl_share* %12, i32 0, i32 4, !dbg !2041
  %13 = load i8*, i8** %clientdata, align 8, !dbg !2041
  call void %9(%struct.Curl_easy* %10, i32 %11, i8* %13), !dbg !2036
  br label %if.end6, !dbg !2036

if.end6:                                          ; preds = %if.then4, %if.then2
  br label %if.end7, !dbg !2042

if.end7:                                          ; preds = %if.end6, %if.end
  store i32 0, i32* %retval, align 4, !dbg !2043
  br label %return, !dbg !2043

return:                                           ; preds = %if.end7, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !2044
  ret i32 %14, !dbg !2044
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1756, !1757}
!llvm.ident = !{!1758}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1734, subprograms: !1735)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/share.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !14, !24, !120, !126, !134, !173, !192, !212, !227, !244, !252, !266, !299, !368, !567, !584, !591, !730, !746, !758, !855, !865, !913, !931, !937, !963, !978, !987, !995, !1024, !1225, !1277, !466, !476, !1716, !1725}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 31, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http_chunks.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13}
!6 = !DIEnumerator(name: "CHUNK_HEX", value: 0)
!7 = !DIEnumerator(name: "CHUNK_LF", value: 1)
!8 = !DIEnumerator(name: "CHUNK_DATA", value: 2)
!9 = !DIEnumerator(name: "CHUNK_POSTLF", value: 3)
!10 = !DIEnumerator(name: "CHUNK_STOP", value: 4)
!11 = !DIEnumerator(name: "CHUNK_TRAILER", value: 5)
!12 = !DIEnumerator(name: "CHUNK_TRAILER_CR", value: 6)
!13 = !DIEnumerator(name: "CHUNK_TRAILER_POSTCR", value: 7)
!14 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 644, size: 32, align: 32, elements: !16)
!15 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!16 = !{!17, !18, !19, !20, !21, !22, !23}
!17 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!18 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!19 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!20 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!21 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!22 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!23 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 434, size: 32, align: 32, elements: !25)
!25 = !{!26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119}
!26 = !DIEnumerator(name: "CURLE_OK", value: 0)
!27 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!28 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!29 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!30 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!31 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!32 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!33 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!34 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!35 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!36 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!37 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!38 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!39 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!40 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!41 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!42 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!43 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!44 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!45 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!46 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!47 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!48 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!49 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!50 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!51 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!52 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!53 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!54 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!55 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!56 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!57 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!58 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!59 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!60 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!61 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!62 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!63 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!64 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!65 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!66 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!67 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!68 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!69 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!70 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!71 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!72 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!73 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!74 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!75 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!76 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!77 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!78 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!79 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!80 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!81 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!82 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!83 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!84 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!85 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!86 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!87 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!88 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!89 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!90 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!91 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!92 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!93 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!94 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!95 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!96 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!97 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!98 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!99 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!100 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!101 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!102 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!103 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!104 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!105 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!106 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!107 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!108 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!109 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!110 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!111 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!112 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!113 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!114 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!115 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!116 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!117 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!118 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!119 = !DIEnumerator(name: "CURL_LAST", value: 93)
!120 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 267, size: 32, align: 32, elements: !122)
!121 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/urldata.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!122 = !{!123, !124, !125}
!123 = !DIEnumerator(name: "ssl_connection_none", value: 0)
!124 = !DIEnumerator(name: "ssl_connection_negotiating", value: 1)
!125 = !DIEnumerator(name: "ssl_connection_complete", value: 2)
!126 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 258, size: 32, align: 32, elements: !127)
!127 = !{!128, !129, !130, !131, !132, !133}
!128 = !DIEnumerator(name: "ssl_connect_1", value: 0)
!129 = !DIEnumerator(name: "ssl_connect_2", value: 1)
!130 = !DIEnumerator(name: "ssl_connect_2_reading", value: 2)
!131 = !DIEnumerator(name: "ssl_connect_2_writing", value: 3)
!132 = !DIEnumerator(name: "ssl_connect_3", value: 4)
!133 = !DIEnumerator(name: "ssl_connect_done", value: 5)
!134 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !135, line: 42, size: 32, align: 32, elements: !136)
!135 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ftp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!136 = !{!137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172}
!137 = !DIEnumerator(name: "FTP_STOP", value: 0)
!138 = !DIEnumerator(name: "FTP_WAIT220", value: 1)
!139 = !DIEnumerator(name: "FTP_AUTH", value: 2)
!140 = !DIEnumerator(name: "FTP_USER", value: 3)
!141 = !DIEnumerator(name: "FTP_PASS", value: 4)
!142 = !DIEnumerator(name: "FTP_ACCT", value: 5)
!143 = !DIEnumerator(name: "FTP_PBSZ", value: 6)
!144 = !DIEnumerator(name: "FTP_PROT", value: 7)
!145 = !DIEnumerator(name: "FTP_CCC", value: 8)
!146 = !DIEnumerator(name: "FTP_PWD", value: 9)
!147 = !DIEnumerator(name: "FTP_SYST", value: 10)
!148 = !DIEnumerator(name: "FTP_NAMEFMT", value: 11)
!149 = !DIEnumerator(name: "FTP_QUOTE", value: 12)
!150 = !DIEnumerator(name: "FTP_RETR_PREQUOTE", value: 13)
!151 = !DIEnumerator(name: "FTP_STOR_PREQUOTE", value: 14)
!152 = !DIEnumerator(name: "FTP_POSTQUOTE", value: 15)
!153 = !DIEnumerator(name: "FTP_CWD", value: 16)
!154 = !DIEnumerator(name: "FTP_MKD", value: 17)
!155 = !DIEnumerator(name: "FTP_MDTM", value: 18)
!156 = !DIEnumerator(name: "FTP_TYPE", value: 19)
!157 = !DIEnumerator(name: "FTP_LIST_TYPE", value: 20)
!158 = !DIEnumerator(name: "FTP_RETR_TYPE", value: 21)
!159 = !DIEnumerator(name: "FTP_STOR_TYPE", value: 22)
!160 = !DIEnumerator(name: "FTP_SIZE", value: 23)
!161 = !DIEnumerator(name: "FTP_RETR_SIZE", value: 24)
!162 = !DIEnumerator(name: "FTP_STOR_SIZE", value: 25)
!163 = !DIEnumerator(name: "FTP_REST", value: 26)
!164 = !DIEnumerator(name: "FTP_RETR_REST", value: 27)
!165 = !DIEnumerator(name: "FTP_PORT", value: 28)
!166 = !DIEnumerator(name: "FTP_PRET", value: 29)
!167 = !DIEnumerator(name: "FTP_PASV", value: 30)
!168 = !DIEnumerator(name: "FTP_LIST", value: 31)
!169 = !DIEnumerator(name: "FTP_RETR", value: 32)
!170 = !DIEnumerator(name: "FTP_STOR", value: 33)
!171 = !DIEnumerator(name: "FTP_QUIT", value: 34)
!172 = !DIEnumerator(name: "FTP_LAST", value: 35)
!173 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !174, line: 31, size: 32, align: 32, elements: !175)
!174 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/imap.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!175 = !{!176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191}
!176 = !DIEnumerator(name: "IMAP_STOP", value: 0)
!177 = !DIEnumerator(name: "IMAP_SERVERGREET", value: 1)
!178 = !DIEnumerator(name: "IMAP_CAPABILITY", value: 2)
!179 = !DIEnumerator(name: "IMAP_STARTTLS", value: 3)
!180 = !DIEnumerator(name: "IMAP_UPGRADETLS", value: 4)
!181 = !DIEnumerator(name: "IMAP_AUTHENTICATE", value: 5)
!182 = !DIEnumerator(name: "IMAP_LOGIN", value: 6)
!183 = !DIEnumerator(name: "IMAP_LIST", value: 7)
!184 = !DIEnumerator(name: "IMAP_SELECT", value: 8)
!185 = !DIEnumerator(name: "IMAP_FETCH", value: 9)
!186 = !DIEnumerator(name: "IMAP_FETCH_FINAL", value: 10)
!187 = !DIEnumerator(name: "IMAP_APPEND", value: 11)
!188 = !DIEnumerator(name: "IMAP_APPEND_FINAL", value: 12)
!189 = !DIEnumerator(name: "IMAP_SEARCH", value: 13)
!190 = !DIEnumerator(name: "IMAP_LOGOUT", value: 14)
!191 = !DIEnumerator(name: "IMAP_LAST", value: 15)
!192 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !193, line: 58, size: 32, align: 32, elements: !194)
!193 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_sasl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!194 = !{!195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211}
!195 = !DIEnumerator(name: "SASL_STOP", value: 0)
!196 = !DIEnumerator(name: "SASL_PLAIN", value: 1)
!197 = !DIEnumerator(name: "SASL_LOGIN", value: 2)
!198 = !DIEnumerator(name: "SASL_LOGIN_PASSWD", value: 3)
!199 = !DIEnumerator(name: "SASL_EXTERNAL", value: 4)
!200 = !DIEnumerator(name: "SASL_CRAMMD5", value: 5)
!201 = !DIEnumerator(name: "SASL_DIGESTMD5", value: 6)
!202 = !DIEnumerator(name: "SASL_DIGESTMD5_RESP", value: 7)
!203 = !DIEnumerator(name: "SASL_NTLM", value: 8)
!204 = !DIEnumerator(name: "SASL_NTLM_TYPE2MSG", value: 9)
!205 = !DIEnumerator(name: "SASL_GSSAPI", value: 10)
!206 = !DIEnumerator(name: "SASL_GSSAPI_TOKEN", value: 11)
!207 = !DIEnumerator(name: "SASL_GSSAPI_NO_DATA", value: 12)
!208 = !DIEnumerator(name: "SASL_OAUTH2", value: 13)
!209 = !DIEnumerator(name: "SASL_OAUTH2_RESP", value: 14)
!210 = !DIEnumerator(name: "SASL_CANCEL", value: 15)
!211 = !DIEnumerator(name: "SASL_FINAL", value: 16)
!212 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !213, line: 31, size: 32, align: 32, elements: !214)
!213 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pop3.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!214 = !{!215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226}
!215 = !DIEnumerator(name: "POP3_STOP", value: 0)
!216 = !DIEnumerator(name: "POP3_SERVERGREET", value: 1)
!217 = !DIEnumerator(name: "POP3_CAPA", value: 2)
!218 = !DIEnumerator(name: "POP3_STARTTLS", value: 3)
!219 = !DIEnumerator(name: "POP3_UPGRADETLS", value: 4)
!220 = !DIEnumerator(name: "POP3_AUTH", value: 5)
!221 = !DIEnumerator(name: "POP3_APOP", value: 6)
!222 = !DIEnumerator(name: "POP3_USER", value: 7)
!223 = !DIEnumerator(name: "POP3_PASS", value: 8)
!224 = !DIEnumerator(name: "POP3_COMMAND", value: 9)
!225 = !DIEnumerator(name: "POP3_QUIT", value: 10)
!226 = !DIEnumerator(name: "POP3_LAST", value: 11)
!227 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !228, line: 31, size: 32, align: 32, elements: !229)
!228 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smtp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!229 = !{!230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243}
!230 = !DIEnumerator(name: "SMTP_STOP", value: 0)
!231 = !DIEnumerator(name: "SMTP_SERVERGREET", value: 1)
!232 = !DIEnumerator(name: "SMTP_EHLO", value: 2)
!233 = !DIEnumerator(name: "SMTP_HELO", value: 3)
!234 = !DIEnumerator(name: "SMTP_STARTTLS", value: 4)
!235 = !DIEnumerator(name: "SMTP_UPGRADETLS", value: 5)
!236 = !DIEnumerator(name: "SMTP_AUTH", value: 6)
!237 = !DIEnumerator(name: "SMTP_COMMAND", value: 7)
!238 = !DIEnumerator(name: "SMTP_MAIL", value: 8)
!239 = !DIEnumerator(name: "SMTP_RCPT", value: 9)
!240 = !DIEnumerator(name: "SMTP_DATA", value: 10)
!241 = !DIEnumerator(name: "SMTP_POSTDATA", value: 11)
!242 = !DIEnumerator(name: "SMTP_QUIT", value: 12)
!243 = !DIEnumerator(name: "SMTP_LAST", value: 13)
!244 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "smb_conn_state", file: !245, line: 25, size: 32, align: 32, elements: !246)
!245 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!246 = !{!247, !248, !249, !250, !251}
!247 = !DIEnumerator(name: "SMB_NOT_CONNECTED", value: 0)
!248 = !DIEnumerator(name: "SMB_CONNECTING", value: 1)
!249 = !DIEnumerator(name: "SMB_NEGOTIATE", value: 2)
!250 = !DIEnumerator(name: "SMB_SETUP", value: 3)
!251 = !DIEnumerator(name: "SMB_CONNECTED", value: 4)
!252 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !253, file: !121, line: 1133, size: 32, align: 32, elements: !1712)
!253 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectdata", file: !121, line: 895, size: 13440, align: 64, elements: !254)
!254 = !{!255, !1293, !1305, !1306, !1307, !1308, !1309, !1335, !1336, !1340, !1341, !1342, !1343, !1350, !1351, !1352, !1360, !1361, !1362, !1363, !1364, !1365, !1366, !1367, !1368, !1369, !1370, !1371, !1372, !1373, !1374, !1375, !1376, !1377, !1379, !1380, !1382, !1389, !1395, !1404, !1405, !1406, !1407, !1408, !1444, !1445, !1446, !1447, !1501, !1502, !1503, !1504, !1505, !1518, !1519, !1520, !1521, !1522, !1523, !1524, !1525, !1526, !1527, !1531, !1532, !1533, !1534, !1697, !1698, !1699, !1700, !1701, !1702, !1704, !1711}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !253, file: !121, line: 899, baseType: !256, size: 64, align: 64)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_easy", file: !121, line: 1801, size: 160192, align: 64, elements: !258)
!258 = !{!259, !260, !261, !263, !288, !290, !313, !319, !320, !374, !450, !451, !551, !621, !1081, !1090, !1091, !1127, !1219, !1242, !1272, !1292}
!259 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !257, file: !121, line: 1803, baseType: !256, size: 64, align: 64)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !257, file: !121, line: 1804, baseType: !256, size: 64, align: 64, offset: 64)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "easy_conn", scope: !257, file: !121, line: 1806, baseType: !262, size: 64, align: 64, offset: 128)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !253, size: 64, align: 64)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "mstate", scope: !257, file: !121, line: 1808, baseType: !264, size: 32, align: 32, offset: 192)
!264 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMstate", file: !265, line: 59, baseType: !266)
!265 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/multihandle.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!266 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !265, line: 35, size: 32, align: 32, elements: !267)
!267 = !{!268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287}
!268 = !DIEnumerator(name: "CURLM_STATE_INIT", value: 0)
!269 = !DIEnumerator(name: "CURLM_STATE_CONNECT_PEND", value: 1)
!270 = !DIEnumerator(name: "CURLM_STATE_CONNECT", value: 2)
!271 = !DIEnumerator(name: "CURLM_STATE_WAITRESOLVE", value: 3)
!272 = !DIEnumerator(name: "CURLM_STATE_WAITCONNECT", value: 4)
!273 = !DIEnumerator(name: "CURLM_STATE_WAITPROXYCONNECT", value: 5)
!274 = !DIEnumerator(name: "CURLM_STATE_SENDPROTOCONNECT", value: 6)
!275 = !DIEnumerator(name: "CURLM_STATE_PROTOCONNECT", value: 7)
!276 = !DIEnumerator(name: "CURLM_STATE_WAITDO", value: 8)
!277 = !DIEnumerator(name: "CURLM_STATE_DO", value: 9)
!278 = !DIEnumerator(name: "CURLM_STATE_DOING", value: 10)
!279 = !DIEnumerator(name: "CURLM_STATE_DO_MORE", value: 11)
!280 = !DIEnumerator(name: "CURLM_STATE_DO_DONE", value: 12)
!281 = !DIEnumerator(name: "CURLM_STATE_WAITPERFORM", value: 13)
!282 = !DIEnumerator(name: "CURLM_STATE_PERFORM", value: 14)
!283 = !DIEnumerator(name: "CURLM_STATE_TOOFAST", value: 15)
!284 = !DIEnumerator(name: "CURLM_STATE_DONE", value: 16)
!285 = !DIEnumerator(name: "CURLM_STATE_COMPLETED", value: 17)
!286 = !DIEnumerator(name: "CURLM_STATE_MSGSENT", value: 18)
!287 = !DIEnumerator(name: "CURLM_STATE_LAST", value: 19)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !257, file: !121, line: 1809, baseType: !289, size: 32, align: 32, offset: 224)
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !15, line: 561, baseType: !24)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !257, file: !121, line: 1811, baseType: !291, size: 192, align: 64, offset: 256)
!291 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_message", file: !265, line: 27, size: 192, align: 64, elements: !292)
!292 = !{!293}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "extmsg", scope: !291, file: !265, line: 29, baseType: !294, size: 192, align: 64)
!294 = !DICompositeType(tag: DW_TAG_structure_type, name: "CURLMsg", file: !295, line: 93, size: 192, align: 64, elements: !296)
!295 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/multi.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!296 = !{!297, !304, !307}
!297 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !294, file: !295, line: 94, baseType: !298, size: 32, align: 32)
!298 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMSG", file: !295, line: 91, baseType: !299)
!299 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !295, line: 86, size: 32, align: 32, elements: !300)
!300 = !{!301, !302, !303}
!301 = !DIEnumerator(name: "CURLMSG_NONE", value: 0)
!302 = !DIEnumerator(name: "CURLMSG_DONE", value: 1)
!303 = !DIEnumerator(name: "CURLMSG_LAST", value: 2)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "easy_handle", scope: !294, file: !295, line: 95, baseType: !305, size: 64, align: 64, offset: 64)
!305 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !15, line: 100, baseType: !257)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !294, file: !295, line: 99, baseType: !308, size: 64, align: 64, offset: 128)
!308 = !DICompositeType(tag: DW_TAG_union_type, scope: !294, file: !295, line: 96, size: 64, align: 64, elements: !309)
!309 = !{!310, !312}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "whatever", scope: !308, file: !295, line: 97, baseType: !311, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !308, file: !295, line: 98, baseType: !289, size: 32, align: 32)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "sockets", scope: !257, file: !121, line: 1817, baseType: !314, size: 160, align: 32, offset: 448)
!314 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 160, align: 32, elements: !317)
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !15, line: 131, baseType: !316)
!316 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!317 = !{!318}
!318 = !DISubrange(count: 5)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "numsocks", scope: !257, file: !121, line: 1818, baseType: !316, size: 32, align: 32, offset: 608)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "dns", scope: !257, file: !121, line: 1820, baseType: !321, size: 128, align: 64, offset: 640)
!321 = !DICompositeType(tag: DW_TAG_structure_type, name: "Names", file: !121, line: 1781, size: 128, align: 64, elements: !322)
!322 = !{!323, !367}
!323 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !321, file: !121, line: 1782, baseType: !324, size: 64, align: 64)
!324 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !325, size: 64, align: 64)
!325 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash", file: !326, line: 46, size: 384, align: 64, elements: !327)
!326 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!327 = !{!328, !350, !355, !360, !365, !366}
!328 = !DIDerivedType(tag: DW_TAG_member, name: "table", scope: !325, file: !326, line: 47, baseType: !329, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !330, size: 64, align: 64)
!330 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !331, line: 37, size: 256, align: 64, elements: !332)
!331 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!332 = !{!333, !340, !341, !346}
!333 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !330, file: !331, line: 38, baseType: !334, size: 64, align: 64)
!334 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !335, size: 64, align: 64)
!335 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !331, line: 30, size: 192, align: 64, elements: !336)
!336 = !{!337, !338, !339}
!337 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !335, file: !331, line: 31, baseType: !311, size: 64, align: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !335, file: !331, line: 33, baseType: !334, size: 64, align: 64, offset: 64)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !335, file: !331, line: 34, baseType: !334, size: 64, align: 64, offset: 128)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !330, file: !331, line: 39, baseType: !334, size: 64, align: 64, offset: 64)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !330, file: !331, line: 41, baseType: !342, size: 64, align: 64, offset: 128)
!342 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !331, line: 28, baseType: !343)
!343 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !344, size: 64, align: 64)
!344 = !DISubroutineType(types: !345)
!345 = !{null, !311, !311}
!346 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !330, file: !331, line: 43, baseType: !347, size: 64, align: 64, offset: 192)
!347 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !348, line: 62, baseType: !349)
!348 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!349 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "hash_func", scope: !325, file: !326, line: 50, baseType: !351, size: 64, align: 64, offset: 64)
!351 = !DIDerivedType(tag: DW_TAG_typedef, name: "hash_function", file: !326, line: 32, baseType: !352)
!352 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !353, size: 64, align: 64)
!353 = !DISubroutineType(types: !354)
!354 = !{!347, !311, !347, !347}
!355 = !DIDerivedType(tag: DW_TAG_member, name: "comp_func", scope: !325, file: !326, line: 53, baseType: !356, size: 64, align: 64, offset: 128)
!356 = !DIDerivedType(tag: DW_TAG_typedef, name: "comp_function", file: !326, line: 39, baseType: !357)
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !358, size: 64, align: 64)
!358 = !DISubroutineType(types: !359)
!359 = !{!347, !311, !347, !311, !347}
!360 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !325, file: !326, line: 54, baseType: !361, size: 64, align: 64, offset: 192)
!361 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_hash_dtor", file: !326, line: 44, baseType: !362)
!362 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !363, size: 64, align: 64)
!363 = !DISubroutineType(types: !364)
!364 = !{null, !311}
!365 = !DIDerivedType(tag: DW_TAG_member, name: "slots", scope: !325, file: !326, line: 55, baseType: !316, size: 32, align: 32, offset: 256)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !325, file: !326, line: 56, baseType: !347, size: 64, align: 64, offset: 320)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "hostcachetype", scope: !321, file: !121, line: 1788, baseType: !368, size: 32, align: 32, offset: 64)
!368 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !321, file: !121, line: 1783, size: 32, align: 32, elements: !369)
!369 = !{!370, !371, !372, !373}
!370 = !DIEnumerator(name: "HCACHE_NONE", value: 0)
!371 = !DIEnumerator(name: "HCACHE_GLOBAL", value: 1)
!372 = !DIEnumerator(name: "HCACHE_MULTI", value: 2)
!373 = !DIEnumerator(name: "HCACHE_SHARED", value: 3)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "multi", scope: !257, file: !121, line: 1821, baseType: !375, size: 64, align: 64, offset: 768)
!375 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !376, size: 64, align: 64)
!376 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_multi", file: !265, line: 70, size: 3840, align: 64, elements: !377)
!377 = !{!378, !380, !381, !382, !383, !384, !385, !386, !391, !392, !399, !400, !401, !420, !421, !422, !424, !432, !433, !434, !435, !436, !437, !438, !439, !440, !441, !448, !449}
!378 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !376, file: !265, line: 73, baseType: !379, size: 64, align: 64)
!379 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "easyp", scope: !376, file: !265, line: 76, baseType: !256, size: 64, align: 64, offset: 64)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "easylp", scope: !376, file: !265, line: 77, baseType: !256, size: 64, align: 64, offset: 128)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "num_easy", scope: !376, file: !265, line: 79, baseType: !316, size: 32, align: 32, offset: 192)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "num_alive", scope: !376, file: !265, line: 80, baseType: !316, size: 32, align: 32, offset: 224)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "msglist", scope: !376, file: !265, line: 83, baseType: !330, size: 256, align: 64, offset: 256)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !376, file: !265, line: 85, baseType: !330, size: 256, align: 64, offset: 512)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "socket_cb", scope: !376, file: !265, line: 89, baseType: !387, size: 64, align: 64, offset: 768)
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_callback", file: !295, line: 268, baseType: !388)
!388 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !389, size: 64, align: 64)
!389 = !DISubroutineType(types: !390)
!390 = !{!316, !305, !315, !316, !311, !311}
!391 = !DIDerivedType(tag: DW_TAG_member, name: "socket_userp", scope: !376, file: !265, line: 90, baseType: !311, size: 64, align: 64, offset: 832)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "push_cb", scope: !376, file: !265, line: 93, baseType: !393, size: 64, align: 64, offset: 896)
!393 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_push_callback", file: !295, line: 429, baseType: !394)
!394 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !395, size: 64, align: 64)
!395 = !DISubroutineType(types: !396)
!396 = !{!316, !305, !305, !347, !397, !311}
!397 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !398, size: 64, align: 64)
!398 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_pushheaders", file: !295, line: 422, flags: DIFlagFwdDecl)
!399 = !DIDerivedType(tag: DW_TAG_member, name: "push_userp", scope: !376, file: !265, line: 94, baseType: !311, size: 64, align: 64, offset: 960)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !376, file: !265, line: 97, baseType: !325, size: 384, align: 64, offset: 1024)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "timetree", scope: !376, file: !265, line: 101, baseType: !402, size: 64, align: 64, offset: 1408)
!402 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !403, size: 64, align: 64)
!403 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_tree", file: !404, line: 26, size: 448, align: 64, elements: !405)
!404 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!405 = !{!406, !407, !408, !409, !410, !419}
!406 = !DIDerivedType(tag: DW_TAG_member, name: "smaller", scope: !403, file: !404, line: 27, baseType: !402, size: 64, align: 64)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "larger", scope: !403, file: !404, line: 28, baseType: !402, size: 64, align: 64, offset: 64)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "samen", scope: !403, file: !404, line: 29, baseType: !402, size: 64, align: 64, offset: 128)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "samep", scope: !403, file: !404, line: 30, baseType: !402, size: 64, align: 64, offset: 192)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !403, file: !404, line: 31, baseType: !411, size: 128, align: 64, offset: 256)
!411 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !412, line: 30, size: 128, align: 64, elements: !413)
!412 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!413 = !{!414, !417}
!414 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !411, file: !412, line: 32, baseType: !415, size: 64, align: 64)
!415 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !416, line: 139, baseType: !379)
!416 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!417 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !411, file: !412, line: 33, baseType: !418, size: 64, align: 64, offset: 64)
!418 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !416, line: 141, baseType: !379)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "payload", scope: !403, file: !404, line: 32, baseType: !311, size: 64, align: 64, offset: 384)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "sockhash", scope: !376, file: !265, line: 106, baseType: !325, size: 384, align: 64, offset: 1472)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining", scope: !376, file: !265, line: 109, baseType: !379, size: 64, align: 64, offset: 1856)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "recheckstate", scope: !376, file: !265, line: 111, baseType: !423, size: 8, align: 8, offset: 1920)
!423 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !376, file: !265, line: 114, baseType: !425, size: 640, align: 64, offset: 1984)
!425 = !DICompositeType(tag: DW_TAG_structure_type, name: "conncache", file: !426, line: 26, size: 640, align: 64, elements: !427)
!426 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/conncache.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!427 = !{!428, !429, !430, !431}
!428 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !425, file: !426, line: 27, baseType: !325, size: 384, align: 64)
!429 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !425, file: !426, line: 28, baseType: !347, size: 64, align: 64, offset: 384)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "next_connection_id", scope: !425, file: !426, line: 29, baseType: !379, size: 64, align: 64, offset: 448)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "last_cleanup", scope: !425, file: !426, line: 30, baseType: !411, size: 128, align: 64, offset: 512)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "closure_handle", scope: !376, file: !265, line: 118, baseType: !256, size: 64, align: 64, offset: 2624)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !376, file: !265, line: 120, baseType: !379, size: 64, align: 64, offset: 2688)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "max_host_connections", scope: !376, file: !265, line: 123, baseType: !379, size: 64, align: 64, offset: 2752)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "max_total_connections", scope: !376, file: !265, line: 126, baseType: !379, size: 64, align: 64, offset: 2816)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "max_pipeline_length", scope: !376, file: !265, line: 129, baseType: !379, size: 64, align: 64, offset: 2880)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "content_length_penalty_size", scope: !376, file: !265, line: 132, baseType: !379, size: 64, align: 64, offset: 2944)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_length_penalty_size", scope: !376, file: !265, line: 137, baseType: !379, size: 64, align: 64, offset: 3008)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_site_bl", scope: !376, file: !265, line: 141, baseType: !330, size: 256, align: 64, offset: 3072)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_server_bl", scope: !376, file: !265, line: 144, baseType: !330, size: 256, align: 64, offset: 3328)
!441 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !376, file: !265, line: 148, baseType: !442, size: 64, align: 64, offset: 3584)
!442 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_multi_timer_callback", file: !295, line: 285, baseType: !443)
!443 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !444, size: 64, align: 64)
!444 = !DISubroutineType(types: !445)
!445 = !{!316, !446, !379, !311}
!446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !447, size: 64, align: 64)
!447 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLM", file: !295, line: 56, baseType: !376)
!448 = !DIDerivedType(tag: DW_TAG_member, name: "timer_userp", scope: !376, file: !265, line: 149, baseType: !311, size: 64, align: 64, offset: 3648)
!449 = !DIDerivedType(tag: DW_TAG_member, name: "timer_lastcall", scope: !376, file: !265, line: 150, baseType: !411, size: 128, align: 64, offset: 3712)
!450 = !DIDerivedType(tag: DW_TAG_member, name: "multi_easy", scope: !257, file: !121, line: 1824, baseType: !375, size: 64, align: 64, offset: 832)
!451 = !DIDerivedType(tag: DW_TAG_member, name: "share", scope: !257, file: !121, line: 1827, baseType: !452, size: 64, align: 64, offset: 896)
!452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !453, size: 64, align: 64)
!453 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !454, line: 39, size: 896, align: 64, elements: !455)
!454 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/share.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!455 = !{!456, !458, !460, !482, !487, !488, !489, !520, !549, !550}
!456 = !DIDerivedType(tag: DW_TAG_member, name: "specifier", scope: !453, file: !454, line: 40, baseType: !457, size: 32, align: 32)
!457 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!458 = !DIDerivedType(tag: DW_TAG_member, name: "dirty", scope: !453, file: !454, line: 41, baseType: !459, size: 32, align: 32, offset: 32)
!459 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !457)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "lockfunc", scope: !453, file: !454, line: 43, baseType: !461, size: 64, align: 64, offset: 64)
!461 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_function", file: !15, line: 2365, baseType: !462)
!462 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !463, size: 64, align: 64)
!463 = !DISubroutineType(types: !464)
!464 = !{null, !305, !465, !475, !311}
!465 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_data", file: !15, line: 2355, baseType: !466)
!466 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2343, size: 32, align: 32, elements: !467)
!467 = !{!468, !469, !470, !471, !472, !473, !474}
!468 = !DIEnumerator(name: "CURL_LOCK_DATA_NONE", value: 0)
!469 = !DIEnumerator(name: "CURL_LOCK_DATA_SHARE", value: 1)
!470 = !DIEnumerator(name: "CURL_LOCK_DATA_COOKIE", value: 2)
!471 = !DIEnumerator(name: "CURL_LOCK_DATA_DNS", value: 3)
!472 = !DIEnumerator(name: "CURL_LOCK_DATA_SSL_SESSION", value: 4)
!473 = !DIEnumerator(name: "CURL_LOCK_DATA_CONNECT", value: 5)
!474 = !DIEnumerator(name: "CURL_LOCK_DATA_LAST", value: 6)
!475 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_access", file: !15, line: 2363, baseType: !476)
!476 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2358, size: 32, align: 32, elements: !477)
!477 = !{!478, !479, !480, !481}
!478 = !DIEnumerator(name: "CURL_LOCK_ACCESS_NONE", value: 0)
!479 = !DIEnumerator(name: "CURL_LOCK_ACCESS_SHARED", value: 1)
!480 = !DIEnumerator(name: "CURL_LOCK_ACCESS_SINGLE", value: 2)
!481 = !DIEnumerator(name: "CURL_LOCK_ACCESS_LAST", value: 3)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "unlockfunc", scope: !453, file: !454, line: 44, baseType: !483, size: 64, align: 64, offset: 128)
!483 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_unlock_function", file: !15, line: 2369, baseType: !484)
!484 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !485, size: 64, align: 64)
!485 = !DISubroutineType(types: !486)
!486 = !{null, !305, !465, !311}
!487 = !DIDerivedType(tag: DW_TAG_member, name: "clientdata", scope: !453, file: !454, line: 45, baseType: !311, size: 64, align: 64, offset: 192)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !453, file: !454, line: 47, baseType: !325, size: 384, align: 64, offset: 256)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !453, file: !454, line: 49, baseType: !490, size: 64, align: 64, offset: 640)
!490 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !491, size: 64, align: 64)
!491 = !DICompositeType(tag: DW_TAG_structure_type, name: "CookieInfo", file: !492, line: 48, size: 320, align: 64, elements: !493)
!492 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/cookie.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!493 = !{!494, !516, !517, !518, !519}
!494 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !491, file: !492, line: 50, baseType: !495, size: 64, align: 64)
!495 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !496, size: 64, align: 64)
!496 = !DICompositeType(tag: DW_TAG_structure_type, name: "Cookie", file: !492, line: 28, size: 768, align: 64, elements: !497)
!497 = !{!498, !499, !502, !503, !504, !505, !506, !509, !510, !511, !512, !513, !514, !515}
!498 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !496, file: !492, line: 29, baseType: !495, size: 64, align: 64)
!499 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !496, file: !492, line: 30, baseType: !500, size: 64, align: 64, offset: 64)
!500 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !501, size: 64, align: 64)
!501 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!502 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !496, file: !492, line: 31, baseType: !500, size: 64, align: 64, offset: 128)
!503 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !496, file: !492, line: 32, baseType: !500, size: 64, align: 64, offset: 192)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "spath", scope: !496, file: !492, line: 33, baseType: !500, size: 64, align: 64, offset: 256)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !496, file: !492, line: 34, baseType: !500, size: 64, align: 64, offset: 320)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "expires", scope: !496, file: !492, line: 35, baseType: !507, size: 64, align: 64, offset: 384)
!507 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !508, line: 216, baseType: !379)
!508 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!509 = !DIDerivedType(tag: DW_TAG_member, name: "expirestr", scope: !496, file: !492, line: 36, baseType: !500, size: 64, align: 64, offset: 448)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "tailmatch", scope: !496, file: !492, line: 37, baseType: !423, size: 8, align: 8, offset: 512)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !496, file: !492, line: 40, baseType: !500, size: 64, align: 64, offset: 576)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "maxage", scope: !496, file: !492, line: 41, baseType: !500, size: 64, align: 64, offset: 640)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "secure", scope: !496, file: !492, line: 43, baseType: !423, size: 8, align: 8, offset: 704)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "livecookie", scope: !496, file: !492, line: 44, baseType: !423, size: 8, align: 8, offset: 712)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "httponly", scope: !496, file: !492, line: 45, baseType: !423, size: 8, align: 8, offset: 720)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !491, file: !492, line: 52, baseType: !500, size: 64, align: 64, offset: 64)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "running", scope: !491, file: !492, line: 53, baseType: !423, size: 8, align: 8, offset: 128)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "numcookies", scope: !491, file: !492, line: 54, baseType: !379, size: 64, align: 64, offset: 192)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "newsession", scope: !491, file: !492, line: 55, baseType: !423, size: 8, align: 8, offset: 256)
!520 = !DIDerivedType(tag: DW_TAG_member, name: "sslsession", scope: !453, file: !454, line: 52, baseType: !521, size: 64, align: 64, offset: 704)
!521 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !522, size: 64, align: 64)
!522 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_ssl_session", file: !121, line: 397, size: 1088, align: 64, elements: !523)
!523 = !{!524, !525, !526, !529, !530, !531, !532, !533, !534}
!524 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !522, file: !121, line: 398, baseType: !500, size: 64, align: 64)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !522, file: !121, line: 399, baseType: !500, size: 64, align: 64, offset: 64)
!526 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !522, file: !121, line: 400, baseType: !527, size: 64, align: 64, offset: 128)
!527 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !528, size: 64, align: 64)
!528 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !501)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !522, file: !121, line: 401, baseType: !311, size: 64, align: 64, offset: 192)
!530 = !DIDerivedType(tag: DW_TAG_member, name: "idsize", scope: !522, file: !121, line: 402, baseType: !347, size: 64, align: 64, offset: 256)
!531 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !522, file: !121, line: 403, baseType: !379, size: 64, align: 64, offset: 320)
!532 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !522, file: !121, line: 404, baseType: !316, size: 32, align: 32, offset: 384)
!533 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !522, file: !121, line: 405, baseType: !316, size: 32, align: 32, offset: 416)
!534 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !522, file: !121, line: 406, baseType: !535, size: 640, align: 64, offset: 448)
!535 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !121, line: 351, size: 640, align: 64, elements: !536)
!536 = !{!537, !538, !539, !540, !541, !542, !543, !544, !545, !546, !547, !548}
!537 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !535, file: !121, line: 352, baseType: !379, size: 64, align: 64)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !535, file: !121, line: 353, baseType: !379, size: 64, align: 64, offset: 64)
!539 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !535, file: !121, line: 354, baseType: !423, size: 8, align: 8, offset: 128)
!540 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !535, file: !121, line: 355, baseType: !423, size: 8, align: 8, offset: 136)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !535, file: !121, line: 356, baseType: !423, size: 8, align: 8, offset: 144)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !535, file: !121, line: 357, baseType: !500, size: 64, align: 64, offset: 192)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !535, file: !121, line: 358, baseType: !500, size: 64, align: 64, offset: 256)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !535, file: !121, line: 359, baseType: !500, size: 64, align: 64, offset: 320)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !535, file: !121, line: 360, baseType: !500, size: 64, align: 64, offset: 384)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !535, file: !121, line: 361, baseType: !500, size: 64, align: 64, offset: 448)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !535, file: !121, line: 362, baseType: !500, size: 64, align: 64, offset: 512)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !535, file: !121, line: 363, baseType: !423, size: 8, align: 8, offset: 576)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !453, file: !454, line: 53, baseType: !347, size: 64, align: 64, offset: 768)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !453, file: !454, line: 54, baseType: !379, size: 64, align: 64, offset: 832)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "req", scope: !257, file: !121, line: 1828, baseType: !552, size: 2496, align: 64, offset: 960)
!552 = !DICompositeType(tag: DW_TAG_structure_type, name: "SingleRequest", file: !121, line: 658, size: 2496, align: 64, elements: !553)
!553 = !{!554, !555, !557, !558, !559, !560, !561, !562, !563, !564, !565, !566, !572, !573, !574, !575, !576, !577, !578, !579, !580, !581, !582, !583, !590, !597, !598, !601, !602, !603, !604, !605, !606, !607, !608, !609, !610, !611, !615, !616, !617, !618, !619, !620}
!554 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !552, file: !121, line: 659, baseType: !507, size: 64, align: 64)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "bytecountp", scope: !552, file: !121, line: 660, baseType: !556, size: 64, align: 64, offset: 64)
!556 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !507, size: 64, align: 64)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "maxdownload", scope: !552, file: !121, line: 662, baseType: !507, size: 64, align: 64, offset: 128)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecountp", scope: !552, file: !121, line: 664, baseType: !556, size: 64, align: 64, offset: 192)
!559 = !DIDerivedType(tag: DW_TAG_member, name: "bytecount", scope: !552, file: !121, line: 666, baseType: !507, size: 64, align: 64, offset: 256)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !552, file: !121, line: 667, baseType: !507, size: 64, align: 64, offset: 320)
!561 = !DIDerivedType(tag: DW_TAG_member, name: "headerbytecount", scope: !552, file: !121, line: 669, baseType: !379, size: 64, align: 64, offset: 384)
!562 = !DIDerivedType(tag: DW_TAG_member, name: "deductheadercount", scope: !552, file: !121, line: 670, baseType: !379, size: 64, align: 64, offset: 448)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !552, file: !121, line: 676, baseType: !411, size: 128, align: 64, offset: 512)
!564 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !552, file: !121, line: 677, baseType: !411, size: 128, align: 64, offset: 640)
!565 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !552, file: !121, line: 678, baseType: !423, size: 8, align: 8, offset: 768)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "badheader", scope: !552, file: !121, line: 684, baseType: !567, size: 32, align: 32, offset: 800)
!567 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !552, file: !121, line: 679, size: 32, align: 32, elements: !568)
!568 = !{!569, !570, !571}
!569 = !DIEnumerator(name: "HEADER_NORMAL", value: 0)
!570 = !DIEnumerator(name: "HEADER_PARTHEADER", value: 1)
!571 = !DIEnumerator(name: "HEADER_ALLBAD", value: 2)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "headerline", scope: !552, file: !121, line: 686, baseType: !316, size: 32, align: 32, offset: 832)
!573 = !DIDerivedType(tag: DW_TAG_member, name: "hbufp", scope: !552, file: !121, line: 688, baseType: !500, size: 64, align: 64, offset: 896)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "hbuflen", scope: !552, file: !121, line: 689, baseType: !347, size: 64, align: 64, offset: 960)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !552, file: !121, line: 690, baseType: !500, size: 64, align: 64, offset: 1024)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "str_start", scope: !552, file: !121, line: 691, baseType: !500, size: 64, align: 64, offset: 1088)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "end_ptr", scope: !552, file: !121, line: 692, baseType: !500, size: 64, align: 64, offset: 1152)
!578 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !552, file: !121, line: 693, baseType: !500, size: 64, align: 64, offset: 1216)
!579 = !DIDerivedType(tag: DW_TAG_member, name: "content_range", scope: !552, file: !121, line: 694, baseType: !423, size: 8, align: 8, offset: 1280)
!580 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !552, file: !121, line: 695, baseType: !507, size: 64, align: 64, offset: 1344)
!581 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !552, file: !121, line: 697, baseType: !316, size: 32, align: 32, offset: 1408)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "start100", scope: !552, file: !121, line: 699, baseType: !411, size: 128, align: 64, offset: 1472)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "exp100", scope: !552, file: !121, line: 700, baseType: !584, size: 32, align: 32, offset: 1600)
!584 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "expect100", file: !121, line: 636, size: 32, align: 32, elements: !585)
!585 = !{!586, !587, !588, !589}
!586 = !DIEnumerator(name: "EXP100_SEND_DATA", value: 0)
!587 = !DIEnumerator(name: "EXP100_AWAITING_CONTINUE", value: 1)
!588 = !DIEnumerator(name: "EXP100_SENDING_REQUEST", value: 2)
!589 = !DIEnumerator(name: "EXP100_FAILED", value: 3)
!590 = !DIDerivedType(tag: DW_TAG_member, name: "upgr101", scope: !552, file: !121, line: 701, baseType: !591, size: 32, align: 32, offset: 1632)
!591 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "upgrade101", file: !121, line: 644, size: 32, align: 32, elements: !592)
!592 = !{!593, !594, !595, !596}
!593 = !DIEnumerator(name: "UPGR101_INIT", value: 0)
!594 = !DIEnumerator(name: "UPGR101_REQUESTED", value: 1)
!595 = !DIEnumerator(name: "UPGR101_RECEIVED", value: 2)
!596 = !DIEnumerator(name: "UPGR101_WORKING", value: 3)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "auto_decoding", scope: !552, file: !121, line: 703, baseType: !316, size: 32, align: 32, offset: 1664)
!598 = !DIDerivedType(tag: DW_TAG_member, name: "timeofdoc", scope: !552, file: !121, line: 715, baseType: !599, size: 64, align: 64, offset: 1728)
!599 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !600, line: 75, baseType: !415)
!600 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!601 = !DIDerivedType(tag: DW_TAG_member, name: "bodywrites", scope: !552, file: !121, line: 716, baseType: !379, size: 64, align: 64, offset: 1792)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !552, file: !121, line: 718, baseType: !500, size: 64, align: 64, offset: 1856)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuf", scope: !552, file: !121, line: 719, baseType: !500, size: 64, align: 64, offset: 1920)
!604 = !DIDerivedType(tag: DW_TAG_member, name: "maxfd", scope: !552, file: !121, line: 720, baseType: !315, size: 32, align: 32, offset: 1984)
!605 = !DIDerivedType(tag: DW_TAG_member, name: "keepon", scope: !552, file: !121, line: 722, baseType: !316, size: 32, align: 32, offset: 2016)
!606 = !DIDerivedType(tag: DW_TAG_member, name: "upload_done", scope: !552, file: !121, line: 724, baseType: !423, size: 8, align: 8, offset: 2048)
!607 = !DIDerivedType(tag: DW_TAG_member, name: "ignorebody", scope: !552, file: !121, line: 727, baseType: !423, size: 8, align: 8, offset: 2056)
!608 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !552, file: !121, line: 728, baseType: !423, size: 8, align: 8, offset: 2064)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "location", scope: !552, file: !121, line: 731, baseType: !500, size: 64, align: 64, offset: 2112)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "newurl", scope: !552, file: !121, line: 733, baseType: !500, size: 64, align: 64, offset: 2176)
!611 = !DIDerivedType(tag: DW_TAG_member, name: "upload_present", scope: !552, file: !121, line: 738, baseType: !612, size: 64, align: 64, offset: 2240)
!612 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !613, line: 109, baseType: !614)
!613 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!614 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !416, line: 172, baseType: !379)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "upload_fromhere", scope: !552, file: !121, line: 744, baseType: !500, size: 64, align: 64, offset: 2304)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !552, file: !121, line: 746, baseType: !423, size: 8, align: 8, offset: 2368)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "upload_chunky", scope: !552, file: !121, line: 747, baseType: !423, size: 8, align: 8, offset: 2376)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "getheader", scope: !552, file: !121, line: 749, baseType: !423, size: 8, align: 8, offset: 2384)
!619 = !DIDerivedType(tag: DW_TAG_member, name: "forbidchunk", scope: !552, file: !121, line: 751, baseType: !423, size: 8, align: 8, offset: 2392)
!620 = !DIDerivedType(tag: DW_TAG_member, name: "protop", scope: !552, file: !121, line: 755, baseType: !311, size: 64, align: 64, offset: 2432)
!621 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !257, file: !121, line: 1829, baseType: !622, size: 13760, align: 64, offset: 3456)
!622 = !DICompositeType(tag: DW_TAG_structure_type, name: "UserDefined", file: !121, line: 1558, size: 13760, align: 64, elements: !623)
!623 = !{!624, !679, !680, !681, !682, !683, !684, !685, !686, !687, !688, !689, !690, !691, !692, !693, !694, !699, !700, !701, !702, !707, !708, !709, !711, !712, !713, !719, !724, !740, !752, !763, !764, !787, !788, !793, !794, !795, !800, !801, !802, !803, !804, !805, !806, !807, !808, !809, !810, !811, !812, !813, !814, !815, !816, !822, !823, !841, !842, !843, !844, !845, !846, !847, !848, !849, !850, !851, !852, !853, !862, !863, !875, !876, !898, !899, !903, !905, !906, !907, !908, !909, !910, !911, !918, !919, !943, !944, !945, !946, !947, !948, !949, !950, !951, !952, !953, !954, !955, !956, !957, !958, !959, !960, !961, !962, !969, !970, !971, !972, !973, !974, !975, !976, !985, !993, !1001, !1002, !1003, !1004, !1005, !1006, !1007, !1008, !1009, !1010, !1011, !1012, !1013, !1017, !1018, !1019, !1020, !1021, !1022, !1039, !1040, !1041, !1048, !1053, !1058, !1059, !1060, !1061, !1062, !1063, !1064, !1065, !1066, !1067, !1068, !1069, !1070, !1071, !1072, !1073, !1074, !1080}
!624 = !DIDerivedType(tag: DW_TAG_member, name: "err", scope: !622, file: !121, line: 1559, baseType: !625, size: 64, align: 64)
!625 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !626, size: 64, align: 64)
!626 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !627, line: 48, baseType: !628)
!627 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!628 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !629, line: 245, size: 1728, align: 64, elements: !630)
!629 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!630 = !{!631, !632, !633, !634, !635, !636, !637, !638, !639, !640, !641, !642, !643, !651, !652, !653, !654, !656, !658, !660, !664, !667, !669, !670, !671, !672, !673, !674, !675}
!631 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !628, file: !629, line: 246, baseType: !316, size: 32, align: 32)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !628, file: !629, line: 251, baseType: !500, size: 64, align: 64, offset: 64)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !628, file: !629, line: 252, baseType: !500, size: 64, align: 64, offset: 128)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !628, file: !629, line: 253, baseType: !500, size: 64, align: 64, offset: 192)
!635 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !628, file: !629, line: 254, baseType: !500, size: 64, align: 64, offset: 256)
!636 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !628, file: !629, line: 255, baseType: !500, size: 64, align: 64, offset: 320)
!637 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !628, file: !629, line: 256, baseType: !500, size: 64, align: 64, offset: 384)
!638 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !628, file: !629, line: 257, baseType: !500, size: 64, align: 64, offset: 448)
!639 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !628, file: !629, line: 258, baseType: !500, size: 64, align: 64, offset: 512)
!640 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !628, file: !629, line: 260, baseType: !500, size: 64, align: 64, offset: 576)
!641 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !628, file: !629, line: 261, baseType: !500, size: 64, align: 64, offset: 640)
!642 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !628, file: !629, line: 262, baseType: !500, size: 64, align: 64, offset: 704)
!643 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !628, file: !629, line: 264, baseType: !644, size: 64, align: 64, offset: 768)
!644 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !645, size: 64, align: 64)
!645 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !629, line: 160, size: 192, align: 64, elements: !646)
!646 = !{!647, !648, !650}
!647 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !645, file: !629, line: 161, baseType: !644, size: 64, align: 64)
!648 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !645, file: !629, line: 162, baseType: !649, size: 64, align: 64, offset: 64)
!649 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !628, size: 64, align: 64)
!650 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !645, file: !629, line: 166, baseType: !316, size: 32, align: 32, offset: 128)
!651 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !628, file: !629, line: 266, baseType: !649, size: 64, align: 64, offset: 832)
!652 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !628, file: !629, line: 268, baseType: !316, size: 32, align: 32, offset: 896)
!653 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !628, file: !629, line: 272, baseType: !316, size: 32, align: 32, offset: 928)
!654 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !628, file: !629, line: 274, baseType: !655, size: 64, align: 64, offset: 960)
!655 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !416, line: 131, baseType: !379)
!656 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !628, file: !629, line: 278, baseType: !657, size: 16, align: 16, offset: 1024)
!657 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!658 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !628, file: !629, line: 279, baseType: !659, size: 8, align: 8, offset: 1040)
!659 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !628, file: !629, line: 280, baseType: !661, size: 8, align: 8, offset: 1048)
!661 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 8, align: 8, elements: !662)
!662 = !{!663}
!663 = !DISubrange(count: 1)
!664 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !628, file: !629, line: 284, baseType: !665, size: 64, align: 64, offset: 1088)
!665 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !666, size: 64, align: 64)
!666 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !629, line: 154, baseType: null)
!667 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !628, file: !629, line: 293, baseType: !668, size: 64, align: 64, offset: 1152)
!668 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !416, line: 132, baseType: !379)
!669 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !628, file: !629, line: 302, baseType: !311, size: 64, align: 64, offset: 1216)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !628, file: !629, line: 303, baseType: !311, size: 64, align: 64, offset: 1280)
!671 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !628, file: !629, line: 304, baseType: !311, size: 64, align: 64, offset: 1344)
!672 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !628, file: !629, line: 305, baseType: !311, size: 64, align: 64, offset: 1408)
!673 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !628, file: !629, line: 306, baseType: !347, size: 64, align: 64, offset: 1472)
!674 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !628, file: !629, line: 308, baseType: !316, size: 32, align: 32, offset: 1536)
!675 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !628, file: !629, line: 310, baseType: !676, size: 160, align: 8, offset: 1568)
!676 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 160, align: 8, elements: !677)
!677 = !{!678}
!678 = !DISubrange(count: 20)
!679 = !DIDerivedType(tag: DW_TAG_member, name: "debugdata", scope: !622, file: !121, line: 1560, baseType: !311, size: 64, align: 64, offset: 64)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuffer", scope: !622, file: !121, line: 1561, baseType: !500, size: 64, align: 64, offset: 128)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "proxyport", scope: !622, file: !121, line: 1562, baseType: !379, size: 64, align: 64, offset: 192)
!682 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !622, file: !121, line: 1565, baseType: !311, size: 64, align: 64, offset: 256)
!683 = !DIDerivedType(tag: DW_TAG_member, name: "in_set", scope: !622, file: !121, line: 1566, baseType: !311, size: 64, align: 64, offset: 320)
!684 = !DIDerivedType(tag: DW_TAG_member, name: "writeheader", scope: !622, file: !121, line: 1567, baseType: !311, size: 64, align: 64, offset: 384)
!685 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_out", scope: !622, file: !121, line: 1568, baseType: !311, size: 64, align: 64, offset: 448)
!686 = !DIDerivedType(tag: DW_TAG_member, name: "use_port", scope: !622, file: !121, line: 1569, baseType: !379, size: 64, align: 64, offset: 512)
!687 = !DIDerivedType(tag: DW_TAG_member, name: "httpauth", scope: !622, file: !121, line: 1570, baseType: !349, size: 64, align: 64, offset: 576)
!688 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauth", scope: !622, file: !121, line: 1571, baseType: !349, size: 64, align: 64, offset: 640)
!689 = !DIDerivedType(tag: DW_TAG_member, name: "followlocation", scope: !622, file: !121, line: 1572, baseType: !379, size: 64, align: 64, offset: 704)
!690 = !DIDerivedType(tag: DW_TAG_member, name: "maxredirs", scope: !622, file: !121, line: 1573, baseType: !379, size: 64, align: 64, offset: 768)
!691 = !DIDerivedType(tag: DW_TAG_member, name: "keep_post", scope: !622, file: !121, line: 1576, baseType: !316, size: 32, align: 32, offset: 832)
!692 = !DIDerivedType(tag: DW_TAG_member, name: "free_referer", scope: !622, file: !121, line: 1578, baseType: !423, size: 8, align: 8, offset: 864)
!693 = !DIDerivedType(tag: DW_TAG_member, name: "postfields", scope: !622, file: !121, line: 1580, baseType: !311, size: 64, align: 64, offset: 896)
!694 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !622, file: !121, line: 1581, baseType: !695, size: 64, align: 64, offset: 960)
!695 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !15, line: 324, baseType: !696)
!696 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !697, size: 64, align: 64)
!697 = !DISubroutineType(types: !698)
!698 = !{!316, !311, !507, !316}
!699 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !622, file: !121, line: 1582, baseType: !507, size: 64, align: 64, offset: 1024)
!700 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !622, file: !121, line: 1585, baseType: !657, size: 16, align: 16, offset: 1088)
!701 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !622, file: !121, line: 1586, baseType: !316, size: 32, align: 32, offset: 1120)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !622, file: !121, line: 1588, baseType: !703, size: 64, align: 64, offset: 1152)
!703 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !15, line: 223, baseType: !704)
!704 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !705, size: 64, align: 64)
!705 = !DISubroutineType(types: !706)
!706 = !{!347, !500, !347, !347, !311}
!707 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !622, file: !121, line: 1589, baseType: !703, size: 64, align: 64, offset: 1216)
!708 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !622, file: !121, line: 1590, baseType: !703, size: 64, align: 64, offset: 1280)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !622, file: !121, line: 1591, baseType: !710, size: 64, align: 64, offset: 1344)
!710 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !15, line: 335, baseType: !704)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !622, file: !121, line: 1592, baseType: !316, size: 32, align: 32, offset: 1408)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !622, file: !121, line: 1593, baseType: !316, size: 32, align: 32, offset: 1440)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !622, file: !121, line: 1594, baseType: !714, size: 64, align: 64, offset: 1472)
!714 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !15, line: 183, baseType: !715)
!715 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !716, size: 64, align: 64)
!716 = !DISubroutineType(types: !717)
!717 = !{!316, !311, !718, !718, !718, !718}
!718 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !622, file: !121, line: 1595, baseType: !720, size: 64, align: 64, offset: 1536)
!720 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !15, line: 191, baseType: !721)
!721 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !722, size: 64, align: 64)
!722 = !DISubroutineType(types: !723)
!723 = !{!316, !311, !507, !507, !507, !507}
!724 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !622, file: !121, line: 1596, baseType: !725, size: 64, align: 64, offset: 1600)
!725 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !15, line: 420, baseType: !726)
!726 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !727, size: 64, align: 64)
!727 = !DISubroutineType(types: !728)
!728 = !{!316, !305, !729, !500, !347, !311}
!729 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !15, line: 418, baseType: !730)
!730 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 409, size: 32, align: 32, elements: !731)
!731 = !{!732, !733, !734, !735, !736, !737, !738, !739}
!732 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!733 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!734 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!735 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!736 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!737 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!738 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!739 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !622, file: !121, line: 1597, baseType: !741, size: 64, align: 64, offset: 1664)
!741 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !15, line: 388, baseType: !742)
!742 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !743, size: 64, align: 64)
!743 = !DISubroutineType(types: !744)
!744 = !{!745, !305, !316, !311}
!745 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !15, line: 380, baseType: !746)
!746 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 375, size: 32, align: 32, elements: !747)
!747 = !{!748, !749, !750, !751}
!748 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!749 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!750 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!751 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!752 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !622, file: !121, line: 1598, baseType: !753, size: 64, align: 64, offset: 1728)
!753 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !15, line: 353, baseType: !754)
!754 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !755, size: 64, align: 64)
!755 = !DISubroutineType(types: !756)
!756 = !{!316, !311, !315, !757}
!757 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !15, line: 344, baseType: !758)
!758 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 340, size: 32, align: 32, elements: !759)
!759 = !{!760, !761, !762}
!760 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!761 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!762 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !622, file: !121, line: 1599, baseType: !311, size: 64, align: 64, offset: 1792)
!764 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !622, file: !121, line: 1600, baseType: !765, size: 64, align: 64, offset: 1856)
!765 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !15, line: 368, baseType: !766)
!766 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !767, size: 64, align: 64)
!767 = !DISubroutineType(types: !768)
!768 = !{!315, !311, !757, !769}
!769 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !770, size: 64, align: 64)
!770 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !15, line: 357, size: 256, align: 32, elements: !771)
!771 = !{!772, !773, !774, !775, !776}
!772 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !770, file: !15, line: 358, baseType: !316, size: 32, align: 32)
!773 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !770, file: !15, line: 359, baseType: !316, size: 32, align: 32, offset: 32)
!774 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !770, file: !15, line: 360, baseType: !316, size: 32, align: 32, offset: 64)
!775 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !770, file: !15, line: 361, baseType: !457, size: 32, align: 32, offset: 96)
!776 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !770, file: !15, line: 364, baseType: !777, size: 128, align: 16, offset: 128)
!777 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !778, line: 149, size: 128, align: 16, elements: !779)
!778 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!779 = !{!780, !783}
!780 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !777, file: !778, line: 151, baseType: !781, size: 16, align: 16)
!781 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !782, line: 28, baseType: !657)
!782 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!783 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !777, file: !778, line: 152, baseType: !784, size: 112, align: 8, offset: 16)
!784 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 112, align: 8, elements: !785)
!785 = !{!786}
!786 = !DISubrange(count: 14)
!787 = !DIDerivedType(tag: DW_TAG_member, name: "opensocket_client", scope: !622, file: !121, line: 1603, baseType: !311, size: 64, align: 64, offset: 1920)
!788 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !622, file: !121, line: 1604, baseType: !789, size: 64, align: 64, offset: 1984)
!789 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !15, line: 373, baseType: !790)
!790 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !791, size: 64, align: 64)
!791 = !DISubroutineType(types: !792)
!792 = !{!316, !311, !315}
!793 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !622, file: !121, line: 1606, baseType: !311, size: 64, align: 64, offset: 2048)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !622, file: !121, line: 1608, baseType: !311, size: 64, align: 64, offset: 2112)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !622, file: !121, line: 1611, baseType: !796, size: 64, align: 64, offset: 2176)
!796 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !15, line: 637, baseType: !797)
!797 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !798, size: 64, align: 64)
!798 = !DISubroutineType(types: !799)
!799 = !{!289, !500, !347}
!800 = !DIDerivedType(tag: DW_TAG_member, name: "convtonetwork", scope: !622, file: !121, line: 1613, baseType: !796, size: 64, align: 64, offset: 2240)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "convfromutf8", scope: !622, file: !121, line: 1615, baseType: !796, size: 64, align: 64, offset: 2304)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "progress_client", scope: !622, file: !121, line: 1617, baseType: !311, size: 64, align: 64, offset: 2368)
!803 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_client", scope: !622, file: !121, line: 1618, baseType: !311, size: 64, align: 64, offset: 2432)
!804 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !622, file: !121, line: 1619, baseType: !379, size: 64, align: 64, offset: 2496)
!805 = !DIDerivedType(tag: DW_TAG_member, name: "connecttimeout", scope: !622, file: !121, line: 1620, baseType: !379, size: 64, align: 64, offset: 2560)
!806 = !DIDerivedType(tag: DW_TAG_member, name: "accepttimeout", scope: !622, file: !121, line: 1621, baseType: !379, size: 64, align: 64, offset: 2624)
!807 = !DIDerivedType(tag: DW_TAG_member, name: "server_response_timeout", scope: !622, file: !121, line: 1622, baseType: !379, size: 64, align: 64, offset: 2688)
!808 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_blksize", scope: !622, file: !121, line: 1623, baseType: !379, size: 64, align: 64, offset: 2752)
!809 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_no_options", scope: !622, file: !121, line: 1624, baseType: !423, size: 8, align: 8, offset: 2816)
!810 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !622, file: !121, line: 1625, baseType: !507, size: 64, align: 64, offset: 2880)
!811 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_limit", scope: !622, file: !121, line: 1626, baseType: !379, size: 64, align: 64, offset: 2944)
!812 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_time", scope: !622, file: !121, line: 1627, baseType: !379, size: 64, align: 64, offset: 3008)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "max_send_speed", scope: !622, file: !121, line: 1628, baseType: !507, size: 64, align: 64, offset: 3072)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "max_recv_speed", scope: !622, file: !121, line: 1629, baseType: !507, size: 64, align: 64, offset: 3136)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "set_resume_from", scope: !622, file: !121, line: 1631, baseType: !507, size: 64, align: 64, offset: 3200)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "headers", scope: !622, file: !121, line: 1632, baseType: !817, size: 64, align: 64, offset: 3264)
!817 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !818, size: 64, align: 64)
!818 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !15, line: 2176, size: 128, align: 64, elements: !819)
!819 = !{!820, !821}
!820 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !818, file: !15, line: 2177, baseType: !500, size: 64, align: 64)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !818, file: !15, line: 2178, baseType: !817, size: 64, align: 64, offset: 64)
!822 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !622, file: !121, line: 1633, baseType: !817, size: 64, align: 64, offset: 3328)
!823 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !622, file: !121, line: 1634, baseType: !824, size: 64, align: 64, offset: 3392)
!824 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !825, size: 64, align: 64)
!825 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !15, line: 137, size: 896, align: 64, elements: !826)
!826 = !{!827, !828, !829, !830, !831, !832, !833, !834, !835, !836, !837, !838, !839, !840}
!827 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !825, file: !15, line: 138, baseType: !824, size: 64, align: 64)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !825, file: !15, line: 139, baseType: !500, size: 64, align: 64, offset: 64)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !825, file: !15, line: 140, baseType: !379, size: 64, align: 64, offset: 128)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !825, file: !15, line: 141, baseType: !500, size: 64, align: 64, offset: 192)
!831 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !825, file: !15, line: 142, baseType: !379, size: 64, align: 64, offset: 256)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !825, file: !15, line: 144, baseType: !500, size: 64, align: 64, offset: 320)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !825, file: !15, line: 145, baseType: !379, size: 64, align: 64, offset: 384)
!834 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !825, file: !15, line: 146, baseType: !500, size: 64, align: 64, offset: 448)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !825, file: !15, line: 147, baseType: !817, size: 64, align: 64, offset: 512)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !825, file: !15, line: 148, baseType: !824, size: 64, align: 64, offset: 576)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !825, file: !15, line: 151, baseType: !379, size: 64, align: 64, offset: 640)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !825, file: !15, line: 171, baseType: !500, size: 64, align: 64, offset: 704)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !825, file: !15, line: 174, baseType: !311, size: 64, align: 64, offset: 768)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !825, file: !15, line: 176, baseType: !507, size: 64, align: 64, offset: 832)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "sep_headers", scope: !622, file: !121, line: 1635, baseType: !423, size: 8, align: 8, offset: 3456)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "cookiesession", scope: !622, file: !121, line: 1636, baseType: !423, size: 8, align: 8, offset: 3464)
!843 = !DIDerivedType(tag: DW_TAG_member, name: "crlf", scope: !622, file: !121, line: 1637, baseType: !423, size: 8, align: 8, offset: 3472)
!844 = !DIDerivedType(tag: DW_TAG_member, name: "quote", scope: !622, file: !121, line: 1638, baseType: !817, size: 64, align: 64, offset: 3520)
!845 = !DIDerivedType(tag: DW_TAG_member, name: "postquote", scope: !622, file: !121, line: 1639, baseType: !817, size: 64, align: 64, offset: 3584)
!846 = !DIDerivedType(tag: DW_TAG_member, name: "prequote", scope: !622, file: !121, line: 1640, baseType: !817, size: 64, align: 64, offset: 3648)
!847 = !DIDerivedType(tag: DW_TAG_member, name: "source_quote", scope: !622, file: !121, line: 1641, baseType: !817, size: 64, align: 64, offset: 3712)
!848 = !DIDerivedType(tag: DW_TAG_member, name: "source_prequote", scope: !622, file: !121, line: 1642, baseType: !817, size: 64, align: 64, offset: 3776)
!849 = !DIDerivedType(tag: DW_TAG_member, name: "source_postquote", scope: !622, file: !121, line: 1644, baseType: !817, size: 64, align: 64, offset: 3840)
!850 = !DIDerivedType(tag: DW_TAG_member, name: "telnet_options", scope: !622, file: !121, line: 1646, baseType: !817, size: 64, align: 64, offset: 3904)
!851 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !622, file: !121, line: 1647, baseType: !817, size: 64, align: 64, offset: 3968)
!852 = !DIDerivedType(tag: DW_TAG_member, name: "connect_to", scope: !622, file: !121, line: 1649, baseType: !817, size: 64, align: 64, offset: 4032)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "timecondition", scope: !622, file: !121, line: 1651, baseType: !854, size: 32, align: 32, offset: 4096)
!854 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !15, line: 1929, baseType: !855)
!855 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 1921, size: 32, align: 32, elements: !856)
!856 = !{!857, !858, !859, !860, !861}
!857 = !DIEnumerator(name: "CURL_TIMECOND_NONE", value: 0)
!858 = !DIEnumerator(name: "CURL_TIMECOND_IFMODSINCE", value: 1)
!859 = !DIEnumerator(name: "CURL_TIMECOND_IFUNMODSINCE", value: 2)
!860 = !DIEnumerator(name: "CURL_TIMECOND_LASTMOD", value: 3)
!861 = !DIEnumerator(name: "CURL_TIMECOND_LAST", value: 4)
!862 = !DIDerivedType(tag: DW_TAG_member, name: "timevalue", scope: !622, file: !121, line: 1652, baseType: !599, size: 64, align: 64, offset: 4160)
!863 = !DIDerivedType(tag: DW_TAG_member, name: "httpreq", scope: !622, file: !121, line: 1653, baseType: !864, size: 32, align: 32, offset: 4224)
!864 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_HttpReq", file: !121, line: 1249, baseType: !865)
!865 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1240, size: 32, align: 32, elements: !866)
!866 = !{!867, !868, !869, !870, !871, !872, !873, !874}
!867 = !DIEnumerator(name: "HTTPREQ_NONE", value: 0)
!868 = !DIEnumerator(name: "HTTPREQ_GET", value: 1)
!869 = !DIEnumerator(name: "HTTPREQ_POST", value: 2)
!870 = !DIEnumerator(name: "HTTPREQ_POST_FORM", value: 3)
!871 = !DIEnumerator(name: "HTTPREQ_PUT", value: 4)
!872 = !DIEnumerator(name: "HTTPREQ_HEAD", value: 5)
!873 = !DIEnumerator(name: "HTTPREQ_CUSTOM", value: 6)
!874 = !DIEnumerator(name: "HTTPREQ_LAST", value: 7)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !622, file: !121, line: 1654, baseType: !379, size: 64, align: 64, offset: 4288)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !622, file: !121, line: 1656, baseType: !877, size: 1408, align: 64, offset: 4352)
!877 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_config_data", file: !121, line: 366, size: 1408, align: 64, elements: !878)
!878 = !{!879, !880, !881, !882, !883, !884, !885, !890, !891, !892, !893, !894, !895, !896, !897}
!879 = !DIDerivedType(tag: DW_TAG_member, name: "primary", scope: !877, file: !121, line: 367, baseType: !535, size: 640, align: 64)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "enable_beast", scope: !877, file: !121, line: 368, baseType: !423, size: 8, align: 8, offset: 640)
!881 = !DIDerivedType(tag: DW_TAG_member, name: "no_revoke", scope: !877, file: !121, line: 370, baseType: !423, size: 8, align: 8, offset: 648)
!882 = !DIDerivedType(tag: DW_TAG_member, name: "certverifyresult", scope: !877, file: !121, line: 371, baseType: !379, size: 64, align: 64, offset: 704)
!883 = !DIDerivedType(tag: DW_TAG_member, name: "CRLfile", scope: !877, file: !121, line: 372, baseType: !500, size: 64, align: 64, offset: 768)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "issuercert", scope: !877, file: !121, line: 373, baseType: !500, size: 64, align: 64, offset: 832)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctx", scope: !877, file: !121, line: 374, baseType: !886, size: 64, align: 64, offset: 896)
!886 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !15, line: 639, baseType: !887)
!887 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !888, size: 64, align: 64)
!888 = !DISubroutineType(types: !889)
!889 = !{!289, !305, !311, !311}
!890 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctxp", scope: !877, file: !121, line: 375, baseType: !311, size: 64, align: 64, offset: 960)
!891 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !877, file: !121, line: 376, baseType: !423, size: 8, align: 8, offset: 1024)
!892 = !DIDerivedType(tag: DW_TAG_member, name: "falsestart", scope: !877, file: !121, line: 377, baseType: !423, size: 8, align: 8, offset: 1032)
!893 = !DIDerivedType(tag: DW_TAG_member, name: "cert", scope: !877, file: !121, line: 379, baseType: !500, size: 64, align: 64, offset: 1088)
!894 = !DIDerivedType(tag: DW_TAG_member, name: "cert_type", scope: !877, file: !121, line: 380, baseType: !500, size: 64, align: 64, offset: 1152)
!895 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !877, file: !121, line: 381, baseType: !500, size: 64, align: 64, offset: 1216)
!896 = !DIDerivedType(tag: DW_TAG_member, name: "key_type", scope: !877, file: !121, line: 382, baseType: !500, size: 64, align: 64, offset: 1280)
!897 = !DIDerivedType(tag: DW_TAG_member, name: "key_passwd", scope: !877, file: !121, line: 383, baseType: !500, size: 64, align: 64, offset: 1344)
!898 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !622, file: !121, line: 1657, baseType: !877, size: 1408, align: 64, offset: 5760)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "general_ssl", scope: !622, file: !121, line: 1658, baseType: !900, size: 64, align: 64, offset: 7168)
!900 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_general_config", file: !121, line: 392, size: 64, align: 64, elements: !901)
!901 = !{!902}
!902 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !900, file: !121, line: 393, baseType: !347, size: 64, align: 64)
!903 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !622, file: !121, line: 1659, baseType: !904, size: 32, align: 32, offset: 7232)
!904 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !15, line: 657, baseType: !14)
!905 = !DIDerivedType(tag: DW_TAG_member, name: "dns_cache_timeout", scope: !622, file: !121, line: 1660, baseType: !379, size: 64, align: 64, offset: 7296)
!906 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !622, file: !121, line: 1661, baseType: !379, size: 64, align: 64, offset: 7360)
!907 = !DIDerivedType(tag: DW_TAG_member, name: "private_data", scope: !622, file: !121, line: 1662, baseType: !311, size: 64, align: 64, offset: 7424)
!908 = !DIDerivedType(tag: DW_TAG_member, name: "http200aliases", scope: !622, file: !121, line: 1664, baseType: !817, size: 64, align: 64, offset: 7488)
!909 = !DIDerivedType(tag: DW_TAG_member, name: "ipver", scope: !622, file: !121, line: 1666, baseType: !379, size: 64, align: 64, offset: 7552)
!910 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesize", scope: !622, file: !121, line: 1669, baseType: !507, size: 64, align: 64, offset: 7616)
!911 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_filemethod", scope: !622, file: !121, line: 1671, baseType: !912, size: 32, align: 32, offset: 7680)
!912 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpfile", file: !135, line: 98, baseType: !913)
!913 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !135, line: 93, size: 32, align: 32, elements: !914)
!914 = !{!915, !916, !917}
!915 = !DIEnumerator(name: "FTPFILE_MULTICWD", value: 1)
!916 = !DIEnumerator(name: "FTPFILE_NOCWD", value: 2)
!917 = !DIEnumerator(name: "FTPFILE_SINGLECWD", value: 3)
!918 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_create_missing_dirs", scope: !622, file: !121, line: 1673, baseType: !316, size: 32, align: 32, offset: 7712)
!919 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc", scope: !622, file: !121, line: 1677, baseType: !920, size: 64, align: 64, offset: 7744)
!920 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !15, line: 739, baseType: !921)
!921 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !922, size: 64, align: 64)
!922 = !DISubroutineType(types: !923)
!923 = !{!316, !305, !924, !924, !937, !311}
!924 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !925, size: 64, align: 64)
!925 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !926)
!926 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !15, line: 711, size: 192, align: 64, elements: !927)
!927 = !{!928, !929, !930}
!928 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !926, file: !15, line: 712, baseType: !527, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !926, file: !15, line: 714, baseType: !347, size: 64, align: 64, offset: 64)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !926, file: !15, line: 715, baseType: !931, size: 32, align: 32, offset: 128)
!931 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !15, line: 704, size: 32, align: 32, elements: !932)
!932 = !{!933, !934, !935, !936}
!933 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!934 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!935 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!936 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!937 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !15, line: 731, size: 32, align: 32, elements: !938)
!938 = !{!939, !940, !941, !942}
!939 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!940 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!941 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!942 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!943 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc_userp", scope: !622, file: !121, line: 1678, baseType: !311, size: 64, align: 64, offset: 7808)
!944 = !DIDerivedType(tag: DW_TAG_member, name: "printhost", scope: !622, file: !121, line: 1684, baseType: !423, size: 8, align: 8, offset: 7872)
!945 = !DIDerivedType(tag: DW_TAG_member, name: "get_filetime", scope: !622, file: !121, line: 1685, baseType: !423, size: 8, align: 8, offset: 7880)
!946 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_thru_httpproxy", scope: !622, file: !121, line: 1686, baseType: !423, size: 8, align: 8, offset: 7888)
!947 = !DIDerivedType(tag: DW_TAG_member, name: "prefer_ascii", scope: !622, file: !121, line: 1687, baseType: !423, size: 8, align: 8, offset: 7896)
!948 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_append", scope: !622, file: !121, line: 1688, baseType: !423, size: 8, align: 8, offset: 7904)
!949 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_list_only", scope: !622, file: !121, line: 1689, baseType: !423, size: 8, align: 8, offset: 7912)
!950 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_port", scope: !622, file: !121, line: 1690, baseType: !423, size: 8, align: 8, offset: 7920)
!951 = !DIDerivedType(tag: DW_TAG_member, name: "hide_progress", scope: !622, file: !121, line: 1691, baseType: !423, size: 8, align: 8, offset: 7928)
!952 = !DIDerivedType(tag: DW_TAG_member, name: "http_fail_on_error", scope: !622, file: !121, line: 1692, baseType: !423, size: 8, align: 8, offset: 7936)
!953 = !DIDerivedType(tag: DW_TAG_member, name: "http_keep_sending_on_error", scope: !622, file: !121, line: 1693, baseType: !423, size: 8, align: 8, offset: 7944)
!954 = !DIDerivedType(tag: DW_TAG_member, name: "http_follow_location", scope: !622, file: !121, line: 1694, baseType: !423, size: 8, align: 8, offset: 7952)
!955 = !DIDerivedType(tag: DW_TAG_member, name: "http_transfer_encoding", scope: !622, file: !121, line: 1695, baseType: !423, size: 8, align: 8, offset: 7960)
!956 = !DIDerivedType(tag: DW_TAG_member, name: "http_disable_hostname_check_before_authentication", scope: !622, file: !121, line: 1696, baseType: !423, size: 8, align: 8, offset: 7968)
!957 = !DIDerivedType(tag: DW_TAG_member, name: "include_header", scope: !622, file: !121, line: 1697, baseType: !423, size: 8, align: 8, offset: 7976)
!958 = !DIDerivedType(tag: DW_TAG_member, name: "http_set_referer", scope: !622, file: !121, line: 1698, baseType: !423, size: 8, align: 8, offset: 7984)
!959 = !DIDerivedType(tag: DW_TAG_member, name: "http_auto_referer", scope: !622, file: !121, line: 1699, baseType: !423, size: 8, align: 8, offset: 7992)
!960 = !DIDerivedType(tag: DW_TAG_member, name: "opt_no_body", scope: !622, file: !121, line: 1700, baseType: !423, size: 8, align: 8, offset: 8000)
!961 = !DIDerivedType(tag: DW_TAG_member, name: "upload", scope: !622, file: !121, line: 1701, baseType: !423, size: 8, align: 8, offset: 8008)
!962 = !DIDerivedType(tag: DW_TAG_member, name: "use_netrc", scope: !622, file: !121, line: 1703, baseType: !963, size: 32, align: 32, offset: 8032)
!963 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !15, line: 1867, size: 32, align: 32, elements: !964)
!964 = !{!965, !966, !967, !968}
!965 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!966 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!967 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!968 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!969 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !622, file: !121, line: 1704, baseType: !423, size: 8, align: 8, offset: 8064)
!970 = !DIDerivedType(tag: DW_TAG_member, name: "krb", scope: !622, file: !121, line: 1705, baseType: !423, size: 8, align: 8, offset: 8072)
!971 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_forbid", scope: !622, file: !121, line: 1706, baseType: !423, size: 8, align: 8, offset: 8080)
!972 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_fresh", scope: !622, file: !121, line: 1707, baseType: !423, size: 8, align: 8, offset: 8088)
!973 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !622, file: !121, line: 1708, baseType: !423, size: 8, align: 8, offset: 8096)
!974 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !622, file: !121, line: 1709, baseType: !423, size: 8, align: 8, offset: 8104)
!975 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_pret", scope: !622, file: !121, line: 1710, baseType: !423, size: 8, align: 8, offset: 8112)
!976 = !DIDerivedType(tag: DW_TAG_member, name: "use_ssl", scope: !622, file: !121, line: 1712, baseType: !977, size: 32, align: 32, offset: 8128)
!977 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !15, line: 752, baseType: !978)
!978 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 746, size: 32, align: 32, elements: !979)
!979 = !{!980, !981, !982, !983, !984}
!980 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!981 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!982 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!983 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!984 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !622, file: !121, line: 1714, baseType: !986, size: 32, align: 32, offset: 8160)
!986 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !15, line: 795, baseType: !987)
!987 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 790, size: 32, align: 32, elements: !988)
!988 = !{!989, !990, !991, !992}
!989 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!990 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!991 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!992 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!993 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !622, file: !121, line: 1715, baseType: !994, size: 32, align: 32, offset: 8192)
!994 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !15, line: 787, baseType: !995)
!995 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 782, size: 32, align: 32, elements: !996)
!996 = !{!997, !998, !999, !1000}
!997 = !DIEnumerator(name: "CURLFTPSSL_CCC_NONE", value: 0)
!998 = !DIEnumerator(name: "CURLFTPSSL_CCC_PASSIVE", value: 1)
!999 = !DIEnumerator(name: "CURLFTPSSL_CCC_ACTIVE", value: 2)
!1000 = !DIEnumerator(name: "CURLFTPSSL_CCC_LAST", value: 3)
!1001 = !DIDerivedType(tag: DW_TAG_member, name: "no_signal", scope: !622, file: !121, line: 1716, baseType: !423, size: 8, align: 8, offset: 8224)
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "global_dns_cache", scope: !622, file: !121, line: 1717, baseType: !423, size: 8, align: 8, offset: 8232)
!1003 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_nodelay", scope: !622, file: !121, line: 1718, baseType: !423, size: 8, align: 8, offset: 8240)
!1004 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !622, file: !121, line: 1719, baseType: !423, size: 8, align: 8, offset: 8248)
!1005 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_skip_ip", scope: !622, file: !121, line: 1720, baseType: !423, size: 8, align: 8, offset: 8256)
!1006 = !DIDerivedType(tag: DW_TAG_member, name: "connect_only", scope: !622, file: !121, line: 1722, baseType: !423, size: 8, align: 8, offset: 8264)
!1007 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_auth_types", scope: !622, file: !121, line: 1723, baseType: !379, size: 64, align: 64, offset: 8320)
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "http_te_skip", scope: !622, file: !121, line: 1724, baseType: !423, size: 8, align: 8, offset: 8384)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "http_ce_skip", scope: !622, file: !121, line: 1726, baseType: !423, size: 8, align: 8, offset: 8392)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "new_file_perms", scope: !622, file: !121, line: 1728, baseType: !379, size: 64, align: 64, offset: 8448)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "new_directory_perms", scope: !622, file: !121, line: 1729, baseType: !379, size: 64, align: 64, offset: 8512)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_transfer_mode", scope: !622, file: !121, line: 1730, baseType: !423, size: 8, align: 8, offset: 8576)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !622, file: !121, line: 1732, baseType: !1014, size: 3584, align: 64, offset: 8640)
!1014 = !DICompositeType(tag: DW_TAG_array_type, baseType: !500, size: 3584, align: 64, elements: !1015)
!1015 = !{!1016}
!1016 = !DISubrange(count: 56)
!1017 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !622, file: !121, line: 1733, baseType: !457, size: 32, align: 32, offset: 12224)
!1018 = !DIDerivedType(tag: DW_TAG_member, name: "allowed_protocols", scope: !622, file: !121, line: 1734, baseType: !379, size: 64, align: 64, offset: 12288)
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "redir_protocols", scope: !622, file: !121, line: 1735, baseType: !379, size: 64, align: 64, offset: 12352)
!1020 = !DIDerivedType(tag: DW_TAG_member, name: "mail_rcpt", scope: !622, file: !121, line: 1739, baseType: !817, size: 64, align: 64, offset: 12416)
!1021 = !DIDerivedType(tag: DW_TAG_member, name: "sasl_ir", scope: !622, file: !121, line: 1740, baseType: !423, size: 8, align: 8, offset: 12480)
!1022 = !DIDerivedType(tag: DW_TAG_member, name: "rtspreq", scope: !622, file: !121, line: 1742, baseType: !1023, size: 32, align: 32, offset: 12512)
!1023 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_RtspReq", file: !121, line: 1265, baseType: !1024)
!1024 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1251, size: 32, align: 32, elements: !1025)
!1025 = !{!1026, !1027, !1028, !1029, !1030, !1031, !1032, !1033, !1034, !1035, !1036, !1037, !1038}
!1026 = !DIEnumerator(name: "RTSPREQ_NONE", value: 0)
!1027 = !DIEnumerator(name: "RTSPREQ_OPTIONS", value: 1)
!1028 = !DIEnumerator(name: "RTSPREQ_DESCRIBE", value: 2)
!1029 = !DIEnumerator(name: "RTSPREQ_ANNOUNCE", value: 3)
!1030 = !DIEnumerator(name: "RTSPREQ_SETUP", value: 4)
!1031 = !DIEnumerator(name: "RTSPREQ_PLAY", value: 5)
!1032 = !DIEnumerator(name: "RTSPREQ_PAUSE", value: 6)
!1033 = !DIEnumerator(name: "RTSPREQ_TEARDOWN", value: 7)
!1034 = !DIEnumerator(name: "RTSPREQ_GET_PARAMETER", value: 8)
!1035 = !DIEnumerator(name: "RTSPREQ_SET_PARAMETER", value: 9)
!1036 = !DIEnumerator(name: "RTSPREQ_RECORD", value: 10)
!1037 = !DIEnumerator(name: "RTSPREQ_RECEIVE", value: 11)
!1038 = !DIEnumerator(name: "RTSPREQ_LAST", value: 12)
!1039 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !622, file: !121, line: 1743, baseType: !379, size: 64, align: 64, offset: 12544)
!1040 = !DIDerivedType(tag: DW_TAG_member, name: "wildcardmatch", scope: !622, file: !121, line: 1744, baseType: !423, size: 8, align: 8, offset: 12608)
!1041 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_bgn", scope: !622, file: !121, line: 1745, baseType: !1042, size: 64, align: 64, offset: 12672)
!1042 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !15, line: 292, baseType: !1043)
!1043 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1044, size: 64, align: 64)
!1044 = !DISubroutineType(types: !1045)
!1045 = !{!379, !1046, !311, !316}
!1046 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1047, size: 64, align: 64)
!1047 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !622, file: !121, line: 1747, baseType: !1049, size: 64, align: 64, offset: 12736)
!1049 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !15, line: 306, baseType: !1050)
!1050 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1051, size: 64, align: 64)
!1051 = !DISubroutineType(types: !1052)
!1052 = !{!379, !311}
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !622, file: !121, line: 1749, baseType: !1054, size: 64, align: 64, offset: 12800)
!1054 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !15, line: 315, baseType: !1055)
!1055 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1056, size: 64, align: 64)
!1056 = !DISubroutineType(types: !1057)
!1057 = !{!316, !311, !527, !527}
!1058 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch_data", scope: !622, file: !121, line: 1751, baseType: !311, size: 64, align: 64, offset: 12864)
!1059 = !DIDerivedType(tag: DW_TAG_member, name: "gssapi_delegation", scope: !622, file: !121, line: 1753, baseType: !379, size: 64, align: 64, offset: 12928)
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepalive", scope: !622, file: !121, line: 1756, baseType: !423, size: 8, align: 8, offset: 12992)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepidle", scope: !622, file: !121, line: 1757, baseType: !379, size: 64, align: 64, offset: 13056)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepintvl", scope: !622, file: !121, line: 1758, baseType: !379, size: 64, align: 64, offset: 13120)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !622, file: !121, line: 1759, baseType: !423, size: 8, align: 8, offset: 13184)
!1064 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !622, file: !121, line: 1761, baseType: !347, size: 64, align: 64, offset: 13248)
!1065 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_npn", scope: !622, file: !121, line: 1763, baseType: !423, size: 8, align: 8, offset: 13312)
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_alpn", scope: !622, file: !121, line: 1764, baseType: !423, size: 8, align: 8, offset: 13320)
!1067 = !DIDerivedType(tag: DW_TAG_member, name: "path_as_is", scope: !622, file: !121, line: 1765, baseType: !423, size: 8, align: 8, offset: 13328)
!1068 = !DIDerivedType(tag: DW_TAG_member, name: "pipewait", scope: !622, file: !121, line: 1766, baseType: !423, size: 8, align: 8, offset: 13336)
!1069 = !DIDerivedType(tag: DW_TAG_member, name: "expect_100_timeout", scope: !622, file: !121, line: 1768, baseType: !379, size: 64, align: 64, offset: 13376)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "suppress_connect_headers", scope: !622, file: !121, line: 1769, baseType: !423, size: 8, align: 8, offset: 13440)
!1071 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !622, file: !121, line: 1772, baseType: !256, size: 64, align: 64, offset: 13504)
!1072 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !622, file: !121, line: 1773, baseType: !423, size: 8, align: 8, offset: 13568)
!1073 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !622, file: !121, line: 1774, baseType: !316, size: 32, align: 32, offset: 13600)
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "stream_dependents", scope: !622, file: !121, line: 1776, baseType: !1075, size: 64, align: 64, offset: 13632)
!1075 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1076, size: 64, align: 64)
!1076 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_http2_dep", file: !121, line: 1292, size: 128, align: 64, elements: !1077)
!1077 = !{!1078, !1079}
!1078 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1076, file: !121, line: 1293, baseType: !1075, size: 64, align: 64)
!1079 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1076, file: !121, line: 1294, baseType: !256, size: 64, align: 64, offset: 64)
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "abstract_unix_socket", scope: !622, file: !121, line: 1778, baseType: !423, size: 8, align: 8, offset: 13696)
!1081 = !DIDerivedType(tag: DW_TAG_member, name: "change", scope: !257, file: !121, line: 1830, baseType: !1082, size: 384, align: 64, offset: 17216)
!1082 = !DICompositeType(tag: DW_TAG_structure_type, name: "DynamicStatic", file: !121, line: 1444, size: 384, align: 64, elements: !1083)
!1083 = !{!1084, !1085, !1086, !1087, !1088, !1089}
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "url", scope: !1082, file: !121, line: 1445, baseType: !500, size: 64, align: 64)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "url_alloc", scope: !1082, file: !121, line: 1446, baseType: !423, size: 8, align: 8, offset: 64)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "referer", scope: !1082, file: !121, line: 1447, baseType: !500, size: 64, align: 64, offset: 128)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "referer_alloc", scope: !1082, file: !121, line: 1448, baseType: !423, size: 8, align: 8, offset: 192)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "cookielist", scope: !1082, file: !121, line: 1449, baseType: !817, size: 64, align: 64, offset: 256)
!1089 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !1082, file: !121, line: 1451, baseType: !817, size: 64, align: 64, offset: 320)
!1090 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !257, file: !121, line: 1831, baseType: !490, size: 64, align: 64, offset: 17600)
!1091 = !DIDerivedType(tag: DW_TAG_member, name: "progress", scope: !257, file: !121, line: 1835, baseType: !1092, size: 3200, align: 64, offset: 17664)
!1092 = !DICompositeType(tag: DW_TAG_structure_type, name: "Progress", file: !121, line: 1195, size: 3200, align: 64, elements: !1093)
!1093 = !{!1094, !1095, !1096, !1097, !1098, !1099, !1100, !1101, !1102, !1103, !1104, !1105, !1106, !1107, !1108, !1109, !1110, !1111, !1112, !1113, !1114, !1115, !1116, !1117, !1118, !1119, !1120, !1124, !1126}
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "lastshow", scope: !1092, file: !121, line: 1196, baseType: !599, size: 64, align: 64)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "size_dl", scope: !1092, file: !121, line: 1198, baseType: !507, size: 64, align: 64, offset: 64)
!1096 = !DIDerivedType(tag: DW_TAG_member, name: "size_ul", scope: !1092, file: !121, line: 1199, baseType: !507, size: 64, align: 64, offset: 128)
!1097 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !1092, file: !121, line: 1200, baseType: !507, size: 64, align: 64, offset: 192)
!1098 = !DIDerivedType(tag: DW_TAG_member, name: "uploaded", scope: !1092, file: !121, line: 1201, baseType: !507, size: 64, align: 64, offset: 256)
!1099 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1092, file: !121, line: 1203, baseType: !507, size: 64, align: 64, offset: 320)
!1100 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !1092, file: !121, line: 1205, baseType: !423, size: 8, align: 8, offset: 384)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !1092, file: !121, line: 1206, baseType: !316, size: 32, align: 32, offset: 416)
!1102 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1092, file: !121, line: 1207, baseType: !316, size: 32, align: 32, offset: 448)
!1103 = !DIDerivedType(tag: DW_TAG_member, name: "timespent", scope: !1092, file: !121, line: 1209, baseType: !718, size: 64, align: 64, offset: 512)
!1104 = !DIDerivedType(tag: DW_TAG_member, name: "dlspeed", scope: !1092, file: !121, line: 1211, baseType: !507, size: 64, align: 64, offset: 576)
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "ulspeed", scope: !1092, file: !121, line: 1212, baseType: !507, size: 64, align: 64, offset: 640)
!1106 = !DIDerivedType(tag: DW_TAG_member, name: "t_nslookup", scope: !1092, file: !121, line: 1214, baseType: !718, size: 64, align: 64, offset: 704)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "t_connect", scope: !1092, file: !121, line: 1215, baseType: !718, size: 64, align: 64, offset: 768)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "t_appconnect", scope: !1092, file: !121, line: 1216, baseType: !718, size: 64, align: 64, offset: 832)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "t_pretransfer", scope: !1092, file: !121, line: 1217, baseType: !718, size: 64, align: 64, offset: 896)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "t_starttransfer", scope: !1092, file: !121, line: 1218, baseType: !718, size: 64, align: 64, offset: 960)
!1111 = !DIDerivedType(tag: DW_TAG_member, name: "t_redirect", scope: !1092, file: !121, line: 1219, baseType: !718, size: 64, align: 64, offset: 1024)
!1112 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !1092, file: !121, line: 1221, baseType: !411, size: 128, align: 64, offset: 1088)
!1113 = !DIDerivedType(tag: DW_TAG_member, name: "t_startsingle", scope: !1092, file: !121, line: 1222, baseType: !411, size: 128, align: 64, offset: 1216)
!1114 = !DIDerivedType(tag: DW_TAG_member, name: "t_startop", scope: !1092, file: !121, line: 1223, baseType: !411, size: 128, align: 64, offset: 1344)
!1115 = !DIDerivedType(tag: DW_TAG_member, name: "t_acceptdata", scope: !1092, file: !121, line: 1224, baseType: !411, size: 128, align: 64, offset: 1472)
!1116 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_start", scope: !1092, file: !121, line: 1227, baseType: !411, size: 128, align: 64, offset: 1600)
!1117 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_size", scope: !1092, file: !121, line: 1228, baseType: !507, size: 64, align: 64, offset: 1728)
!1118 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_start", scope: !1092, file: !121, line: 1230, baseType: !411, size: 128, align: 64, offset: 1792)
!1119 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_size", scope: !1092, file: !121, line: 1231, baseType: !507, size: 64, align: 64, offset: 1920)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "speeder", scope: !1092, file: !121, line: 1235, baseType: !1121, size: 384, align: 64, offset: 1984)
!1121 = !DICompositeType(tag: DW_TAG_array_type, baseType: !507, size: 384, align: 64, elements: !1122)
!1122 = !{!1123}
!1123 = !DISubrange(count: 6)
!1124 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_time", scope: !1092, file: !121, line: 1236, baseType: !1125, size: 768, align: 64, offset: 2368)
!1125 = !DICompositeType(tag: DW_TAG_array_type, baseType: !411, size: 768, align: 64, elements: !1122)
!1126 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_c", scope: !1092, file: !121, line: 1237, baseType: !316, size: 32, align: 32, offset: 3136)
!1127 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !257, file: !121, line: 1836, baseType: !1128, size: 136640, align: 64, offset: 20864)
!1128 = !DICompositeType(tag: DW_TAG_structure_type, name: "UrlState", file: !121, line: 1310, size: 136640, align: 64, elements: !1129)
!1129 = !{!1130, !1132, !1133, !1134, !1135, !1136, !1137, !1138, !1142, !1143, !1144, !1145, !1146, !1147, !1148, !1149, !1158, !1159, !1160, !1161, !1165, !1166, !1178, !1179, !1188, !1189, !1190, !1191, !1192, !1193, !1194, !1195, !1196, !1197, !1198, !1199, !1200, !1201, !1202, !1203, !1204, !1205, !1206, !1207, !1208, !1209, !1210, !1211, !1212, !1213, !1214, !1215, !1216, !1217, !1218}
!1130 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !1128, file: !121, line: 1313, baseType: !1131, size: 64, align: 64)
!1131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !425, size: 64, align: 64)
!1132 = !DIDerivedType(tag: DW_TAG_member, name: "multi_owned_by_easy", scope: !1128, file: !121, line: 1318, baseType: !423, size: 8, align: 8, offset: 64)
!1133 = !DIDerivedType(tag: DW_TAG_member, name: "keeps_speed", scope: !1128, file: !121, line: 1321, baseType: !411, size: 128, align: 64, offset: 128)
!1134 = !DIDerivedType(tag: DW_TAG_member, name: "lastconnect", scope: !1128, file: !121, line: 1323, baseType: !262, size: 64, align: 64, offset: 256)
!1135 = !DIDerivedType(tag: DW_TAG_member, name: "headerbuff", scope: !1128, file: !121, line: 1325, baseType: !500, size: 64, align: 64, offset: 320)
!1136 = !DIDerivedType(tag: DW_TAG_member, name: "headersize", scope: !1128, file: !121, line: 1326, baseType: !347, size: 64, align: 64, offset: 384)
!1137 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1128, file: !121, line: 1328, baseType: !500, size: 64, align: 64, offset: 448)
!1138 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuffer", scope: !1128, file: !121, line: 1329, baseType: !1139, size: 131080, align: 8, offset: 512)
!1139 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 131080, align: 8, elements: !1140)
!1140 = !{!1141}
!1141 = !DISubrange(count: 16385)
!1142 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1128, file: !121, line: 1330, baseType: !507, size: 64, align: 64, offset: 131648)
!1143 = !DIDerivedType(tag: DW_TAG_member, name: "this_is_a_follow", scope: !1128, file: !121, line: 1332, baseType: !423, size: 8, align: 8, offset: 131712)
!1144 = !DIDerivedType(tag: DW_TAG_member, name: "first_host", scope: !1128, file: !121, line: 1334, baseType: !500, size: 64, align: 64, offset: 131776)
!1145 = !DIDerivedType(tag: DW_TAG_member, name: "first_remote_port", scope: !1128, file: !121, line: 1340, baseType: !316, size: 32, align: 32, offset: 131840)
!1146 = !DIDerivedType(tag: DW_TAG_member, name: "session", scope: !1128, file: !121, line: 1341, baseType: !521, size: 64, align: 64, offset: 131904)
!1147 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !1128, file: !121, line: 1342, baseType: !379, size: 64, align: 64, offset: 131968)
!1148 = !DIDerivedType(tag: DW_TAG_member, name: "tempcount", scope: !1128, file: !121, line: 1343, baseType: !457, size: 32, align: 32, offset: 132032)
!1149 = !DIDerivedType(tag: DW_TAG_member, name: "tempwrite", scope: !1128, file: !121, line: 1344, baseType: !1150, size: 576, align: 64, offset: 132096)
!1150 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1151, size: 576, align: 64, elements: !1156)
!1151 = !DICompositeType(tag: DW_TAG_structure_type, name: "tempbuf", file: !121, line: 1302, size: 192, align: 64, elements: !1152)
!1152 = !{!1153, !1154, !1155}
!1153 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !1151, file: !121, line: 1303, baseType: !500, size: 64, align: 64)
!1154 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !1151, file: !121, line: 1305, baseType: !347, size: 64, align: 64, offset: 64)
!1155 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1151, file: !121, line: 1306, baseType: !316, size: 32, align: 32, offset: 128)
!1156 = !{!1157}
!1157 = !DISubrange(count: 3)
!1158 = !DIDerivedType(tag: DW_TAG_member, name: "scratch", scope: !1128, file: !121, line: 1345, baseType: !500, size: 64, align: 64, offset: 132672)
!1159 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuf", scope: !1128, file: !121, line: 1346, baseType: !423, size: 8, align: 8, offset: 132736)
!1160 = !DIDerivedType(tag: DW_TAG_member, name: "os_errno", scope: !1128, file: !121, line: 1349, baseType: !316, size: 32, align: 32, offset: 132768)
!1161 = !DIDerivedType(tag: DW_TAG_member, name: "prev_signal", scope: !1128, file: !121, line: 1352, baseType: !1162, size: 64, align: 64, offset: 132800)
!1162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1163, size: 64, align: 64)
!1163 = !DISubroutineType(types: !1164)
!1164 = !{null, !316}
!1165 = !DIDerivedType(tag: DW_TAG_member, name: "allow_port", scope: !1128, file: !121, line: 1354, baseType: !423, size: 8, align: 8, offset: 132864)
!1166 = !DIDerivedType(tag: DW_TAG_member, name: "digest", scope: !1128, file: !121, line: 1356, baseType: !1167, size: 512, align: 64, offset: 132928)
!1167 = !DICompositeType(tag: DW_TAG_structure_type, name: "digestdata", file: !121, line: 410, size: 512, align: 64, elements: !1168)
!1168 = !{!1169, !1170, !1171, !1172, !1173, !1174, !1175, !1176, !1177}
!1169 = !DIDerivedType(tag: DW_TAG_member, name: "nonce", scope: !1167, file: !121, line: 416, baseType: !500, size: 64, align: 64)
!1170 = !DIDerivedType(tag: DW_TAG_member, name: "cnonce", scope: !1167, file: !121, line: 417, baseType: !500, size: 64, align: 64, offset: 64)
!1171 = !DIDerivedType(tag: DW_TAG_member, name: "realm", scope: !1167, file: !121, line: 418, baseType: !500, size: 64, align: 64, offset: 128)
!1172 = !DIDerivedType(tag: DW_TAG_member, name: "algo", scope: !1167, file: !121, line: 419, baseType: !316, size: 32, align: 32, offset: 192)
!1173 = !DIDerivedType(tag: DW_TAG_member, name: "stale", scope: !1167, file: !121, line: 420, baseType: !423, size: 8, align: 8, offset: 224)
!1174 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !1167, file: !121, line: 421, baseType: !500, size: 64, align: 64, offset: 256)
!1175 = !DIDerivedType(tag: DW_TAG_member, name: "qop", scope: !1167, file: !121, line: 422, baseType: !500, size: 64, align: 64, offset: 320)
!1176 = !DIDerivedType(tag: DW_TAG_member, name: "algorithm", scope: !1167, file: !121, line: 423, baseType: !500, size: 64, align: 64, offset: 384)
!1177 = !DIDerivedType(tag: DW_TAG_member, name: "nc", scope: !1167, file: !121, line: 424, baseType: !316, size: 32, align: 32, offset: 448)
!1178 = !DIDerivedType(tag: DW_TAG_member, name: "proxydigest", scope: !1128, file: !121, line: 1357, baseType: !1167, size: 512, align: 64, offset: 133440)
!1179 = !DIDerivedType(tag: DW_TAG_member, name: "authhost", scope: !1128, file: !121, line: 1364, baseType: !1180, size: 256, align: 64, offset: 133952)
!1180 = !DICompositeType(tag: DW_TAG_structure_type, name: "auth", file: !121, line: 1278, size: 256, align: 64, elements: !1181)
!1181 = !{!1182, !1183, !1184, !1185, !1186, !1187}
!1182 = !DIDerivedType(tag: DW_TAG_member, name: "want", scope: !1180, file: !121, line: 1279, baseType: !349, size: 64, align: 64)
!1183 = !DIDerivedType(tag: DW_TAG_member, name: "picked", scope: !1180, file: !121, line: 1281, baseType: !349, size: 64, align: 64, offset: 64)
!1184 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !1180, file: !121, line: 1282, baseType: !349, size: 64, align: 64, offset: 128)
!1185 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1180, file: !121, line: 1284, baseType: !423, size: 8, align: 8, offset: 192)
!1186 = !DIDerivedType(tag: DW_TAG_member, name: "multipass", scope: !1180, file: !121, line: 1286, baseType: !423, size: 8, align: 8, offset: 200)
!1187 = !DIDerivedType(tag: DW_TAG_member, name: "iestyle", scope: !1180, file: !121, line: 1288, baseType: !423, size: 8, align: 8, offset: 208)
!1188 = !DIDerivedType(tag: DW_TAG_member, name: "authproxy", scope: !1128, file: !121, line: 1365, baseType: !1180, size: 256, align: 64, offset: 134208)
!1189 = !DIDerivedType(tag: DW_TAG_member, name: "authproblem", scope: !1128, file: !121, line: 1367, baseType: !423, size: 8, align: 8, offset: 134464)
!1190 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !1128, file: !121, line: 1369, baseType: !311, size: 64, align: 64, offset: 134528)
!1191 = !DIDerivedType(tag: DW_TAG_member, name: "expiretime", scope: !1128, file: !121, line: 1375, baseType: !411, size: 128, align: 64, offset: 134592)
!1192 = !DIDerivedType(tag: DW_TAG_member, name: "timenode", scope: !1128, file: !121, line: 1376, baseType: !403, size: 448, align: 64, offset: 134720)
!1193 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutlist", scope: !1128, file: !121, line: 1377, baseType: !330, size: 256, align: 64, offset: 135168)
!1194 = !DIDerivedType(tag: DW_TAG_member, name: "most_recent_ftp_entrypath", scope: !1128, file: !121, line: 1380, baseType: !500, size: 64, align: 64, offset: 135424)
!1195 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_trying_alternative", scope: !1128, file: !121, line: 1383, baseType: !423, size: 8, align: 8, offset: 135488)
!1196 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1128, file: !121, line: 1385, baseType: !316, size: 32, align: 32, offset: 135520)
!1197 = !DIDerivedType(tag: DW_TAG_member, name: "expect100header", scope: !1128, file: !121, line: 1387, baseType: !423, size: 8, align: 8, offset: 135552)
!1198 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_broke", scope: !1128, file: !121, line: 1389, baseType: !423, size: 8, align: 8, offset: 135560)
!1199 = !DIDerivedType(tag: DW_TAG_member, name: "prev_block_had_trailing_cr", scope: !1128, file: !121, line: 1397, baseType: !423, size: 8, align: 8, offset: 135568)
!1200 = !DIDerivedType(tag: DW_TAG_member, name: "crlf_conversions", scope: !1128, file: !121, line: 1399, baseType: !507, size: 64, align: 64, offset: 135616)
!1201 = !DIDerivedType(tag: DW_TAG_member, name: "pathbuffer", scope: !1128, file: !121, line: 1401, baseType: !500, size: 64, align: 64, offset: 135680)
!1202 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1128, file: !121, line: 1402, baseType: !500, size: 64, align: 64, offset: 135744)
!1203 = !DIDerivedType(tag: DW_TAG_member, name: "slash_removed", scope: !1128, file: !121, line: 1404, baseType: !423, size: 8, align: 8, offset: 135808)
!1204 = !DIDerivedType(tag: DW_TAG_member, name: "use_range", scope: !1128, file: !121, line: 1406, baseType: !423, size: 8, align: 8, offset: 135816)
!1205 = !DIDerivedType(tag: DW_TAG_member, name: "rangestringalloc", scope: !1128, file: !121, line: 1407, baseType: !423, size: 8, align: 8, offset: 135824)
!1206 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !1128, file: !121, line: 1409, baseType: !500, size: 64, align: 64, offset: 135872)
!1207 = !DIDerivedType(tag: DW_TAG_member, name: "resume_from", scope: !1128, file: !121, line: 1411, baseType: !507, size: 64, align: 64, offset: 135936)
!1208 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_client_CSeq", scope: !1128, file: !121, line: 1414, baseType: !379, size: 64, align: 64, offset: 136000)
!1209 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_server_CSeq", scope: !1128, file: !121, line: 1415, baseType: !379, size: 64, align: 64, offset: 136064)
!1210 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_CSeq_recv", scope: !1128, file: !121, line: 1416, baseType: !379, size: 64, align: 64, offset: 136128)
!1211 = !DIDerivedType(tag: DW_TAG_member, name: "infilesize", scope: !1128, file: !121, line: 1418, baseType: !507, size: 64, align: 64, offset: 136192)
!1212 = !DIDerivedType(tag: DW_TAG_member, name: "drain", scope: !1128, file: !121, line: 1421, baseType: !347, size: 64, align: 64, offset: 136256)
!1213 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1128, file: !121, line: 1424, baseType: !423, size: 8, align: 8, offset: 136320)
!1214 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1128, file: !121, line: 1428, baseType: !710, size: 64, align: 64, offset: 136384)
!1215 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1128, file: !121, line: 1429, baseType: !311, size: 64, align: 64, offset: 136448)
!1216 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !1128, file: !121, line: 1431, baseType: !256, size: 64, align: 64, offset: 136512)
!1217 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !1128, file: !121, line: 1432, baseType: !423, size: 8, align: 8, offset: 136576)
!1218 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !1128, file: !121, line: 1433, baseType: !316, size: 32, align: 32, offset: 136608)
!1219 = !DIDerivedType(tag: DW_TAG_member, name: "wildcard", scope: !257, file: !121, line: 1838, baseType: !1220, size: 640, align: 64, offset: 157504)
!1220 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !1221, line: 46, size: 640, align: 64, elements: !1222)
!1221 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1222 = !{!1223, !1235, !1236, !1237, !1238, !1239, !1241}
!1223 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1220, file: !1221, line: 47, baseType: !1224, size: 32, align: 32)
!1224 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !1221, line: 41, baseType: !1225)
!1225 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1221, line: 30, size: 32, align: 32, elements: !1226)
!1226 = !{!1227, !1228, !1229, !1230, !1231, !1232, !1233, !1234}
!1227 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!1228 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!1229 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!1230 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!1231 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!1232 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!1233 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!1234 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!1235 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1220, file: !1221, line: 48, baseType: !500, size: 64, align: 64, offset: 64)
!1236 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !1220, file: !1221, line: 49, baseType: !500, size: 64, align: 64, offset: 128)
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !1220, file: !1221, line: 50, baseType: !330, size: 256, align: 64, offset: 192)
!1238 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !1220, file: !1221, line: 51, baseType: !311, size: 64, align: 64, offset: 448)
!1239 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !1220, file: !1221, line: 52, baseType: !1240, size: 64, align: 64, offset: 512)
!1240 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !1221, line: 43, baseType: !362)
!1241 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !1220, file: !1221, line: 53, baseType: !311, size: 64, align: 64, offset: 576)
!1242 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !257, file: !121, line: 1839, baseType: !1243, size: 1856, align: 64, offset: 158144)
!1243 = !DICompositeType(tag: DW_TAG_structure_type, name: "PureInfo", file: !121, line: 1154, size: 1856, align: 64, elements: !1244)
!1244 = !{!1245, !1246, !1247, !1248, !1249, !1250, !1251, !1252, !1253, !1254, !1255, !1256, !1257, !1261, !1262, !1263, !1264, !1265, !1266}
!1245 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !1243, file: !121, line: 1155, baseType: !316, size: 32, align: 32)
!1246 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxycode", scope: !1243, file: !121, line: 1156, baseType: !316, size: 32, align: 32, offset: 32)
!1247 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1243, file: !121, line: 1157, baseType: !316, size: 32, align: 32, offset: 64)
!1248 = !DIDerivedType(tag: DW_TAG_member, name: "filetime", scope: !1243, file: !121, line: 1158, baseType: !379, size: 64, align: 64, offset: 128)
!1249 = !DIDerivedType(tag: DW_TAG_member, name: "timecond", scope: !1243, file: !121, line: 1162, baseType: !423, size: 8, align: 8, offset: 192)
!1250 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !1243, file: !121, line: 1164, baseType: !379, size: 64, align: 64, offset: 256)
!1251 = !DIDerivedType(tag: DW_TAG_member, name: "request_size", scope: !1243, file: !121, line: 1165, baseType: !379, size: 64, align: 64, offset: 320)
!1252 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauthavail", scope: !1243, file: !121, line: 1166, baseType: !349, size: 64, align: 64, offset: 384)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "httpauthavail", scope: !1243, file: !121, line: 1167, baseType: !349, size: 64, align: 64, offset: 448)
!1254 = !DIDerivedType(tag: DW_TAG_member, name: "numconnects", scope: !1243, file: !121, line: 1168, baseType: !379, size: 64, align: 64, offset: 512)
!1255 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !1243, file: !121, line: 1169, baseType: !500, size: 64, align: 64, offset: 576)
!1256 = !DIDerivedType(tag: DW_TAG_member, name: "wouldredirect", scope: !1243, file: !121, line: 1170, baseType: !500, size: 64, align: 64, offset: 640)
!1257 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_ip", scope: !1243, file: !121, line: 1180, baseType: !1258, size: 368, align: 8, offset: 704)
!1258 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 368, align: 8, elements: !1259)
!1259 = !{!1260}
!1260 = !DISubrange(count: 46)
!1261 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_port", scope: !1243, file: !121, line: 1181, baseType: !379, size: 64, align: 64, offset: 1088)
!1262 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_ip", scope: !1243, file: !121, line: 1183, baseType: !1258, size: 368, align: 8, offset: 1152)
!1263 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_port", scope: !1243, file: !121, line: 1184, baseType: !379, size: 64, align: 64, offset: 1536)
!1264 = !DIDerivedType(tag: DW_TAG_member, name: "conn_scheme", scope: !1243, file: !121, line: 1186, baseType: !527, size: 64, align: 64, offset: 1600)
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "conn_protocol", scope: !1243, file: !121, line: 1187, baseType: !457, size: 32, align: 32, offset: 1664)
!1266 = !DIDerivedType(tag: DW_TAG_member, name: "certs", scope: !1243, file: !121, line: 1189, baseType: !1267, size: 128, align: 64, offset: 1728)
!1267 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !15, line: 2214, size: 128, align: 64, elements: !1268)
!1268 = !{!1269, !1270}
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1267, file: !15, line: 2215, baseType: !316, size: 32, align: 32)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1267, file: !15, line: 2216, baseType: !1271, size: 64, align: 64, offset: 64)
!1271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !817, size: 64, align: 64)
!1272 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !257, file: !121, line: 1840, baseType: !1273, size: 128, align: 64, offset: 160000)
!1273 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !15, line: 2245, size: 128, align: 64, elements: !1274)
!1274 = !{!1275, !1291}
!1275 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1273, file: !15, line: 2246, baseType: !1276, size: 32, align: 32)
!1276 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !15, line: 2235, baseType: !1277)
!1277 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2222, size: 32, align: 32, elements: !1278)
!1278 = !{!1279, !1280, !1281, !1282, !1283, !1284, !1285, !1286, !1287, !1288, !1289, !1290}
!1279 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!1280 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!1281 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!1282 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!1283 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!1284 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!1285 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!1286 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!1287 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!1288 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!1289 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!1290 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1273, file: !15, line: 2247, baseType: !311, size: 64, align: 64, offset: 64)
!1292 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !257, file: !121, line: 1847, baseType: !457, size: 32, align: 32, offset: 160128)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !253, file: !121, line: 904, baseType: !1294, size: 384, align: 64, offset: 64)
!1294 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !4, line: 82, size: 384, align: 64, elements: !1295)
!1295 = !{!1296, !1300, !1301, !1303, !1304}
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1294, file: !4, line: 83, baseType: !1297, size: 136, align: 8)
!1297 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 136, align: 8, elements: !1298)
!1298 = !{!1299}
!1299 = !DISubrange(count: 17)
!1300 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1294, file: !4, line: 84, baseType: !316, size: 32, align: 32, offset: 160)
!1301 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1294, file: !4, line: 85, baseType: !1302, size: 32, align: 32, offset: 192)
!1302 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !4, line: 66, baseType: !3)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1294, file: !4, line: 86, baseType: !507, size: 64, align: 64, offset: 256)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1294, file: !4, line: 87, baseType: !347, size: 64, align: 64, offset: 320)
!1305 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !253, file: !121, line: 906, baseType: !789, size: 64, align: 64, offset: 448)
!1306 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !253, file: !121, line: 907, baseType: !311, size: 64, align: 64, offset: 512)
!1307 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !253, file: !121, line: 909, baseType: !423, size: 8, align: 8, offset: 576)
!1308 = !DIDerivedType(tag: DW_TAG_member, name: "connection_id", scope: !253, file: !121, line: 915, baseType: !379, size: 64, align: 64, offset: 640)
!1309 = !DIDerivedType(tag: DW_TAG_member, name: "dns_entry", scope: !253, file: !121, line: 922, baseType: !1310, size: 64, align: 64, offset: 704)
!1310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1311, size: 64, align: 64)
!1311 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_dns_entry", file: !1312, line: 66, size: 192, align: 64, elements: !1313)
!1312 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hostip.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1313 = !{!1314, !1333, !1334}
!1314 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !1311, file: !1312, line: 67, baseType: !1315, size: 64, align: 64)
!1315 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1316, size: 64, align: 64)
!1316 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_addrinfo", file: !1317, line: 61, baseType: !1318)
!1317 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1318 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_addrinfo", file: !1317, line: 51, size: 384, align: 64, elements: !1319)
!1319 = !{!1320, !1321, !1322, !1323, !1324, !1328, !1329, !1331}
!1320 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !1318, file: !1317, line: 52, baseType: !316, size: 32, align: 32)
!1321 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !1318, file: !1317, line: 53, baseType: !316, size: 32, align: 32, offset: 32)
!1322 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !1318, file: !1317, line: 54, baseType: !316, size: 32, align: 32, offset: 64)
!1323 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !1318, file: !1317, line: 55, baseType: !316, size: 32, align: 32, offset: 96)
!1324 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !1318, file: !1317, line: 56, baseType: !1325, size: 32, align: 32, offset: 128)
!1325 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !508, line: 186, baseType: !1326)
!1326 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !778, line: 33, baseType: !1327)
!1327 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !416, line: 189, baseType: !457)
!1328 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !1318, file: !1317, line: 57, baseType: !500, size: 64, align: 64, offset: 192)
!1329 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !1318, file: !1317, line: 58, baseType: !1330, size: 64, align: 64, offset: 256)
!1330 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !777, size: 64, align: 64)
!1331 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !1318, file: !1317, line: 59, baseType: !1332, size: 64, align: 64, offset: 320)
!1332 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1318, size: 64, align: 64)
!1333 = !DIDerivedType(tag: DW_TAG_member, name: "timestamp", scope: !1311, file: !1312, line: 69, baseType: !599, size: 64, align: 64, offset: 64)
!1334 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !1311, file: !1312, line: 71, baseType: !379, size: 64, align: 64, offset: 128)
!1335 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr", scope: !253, file: !121, line: 927, baseType: !1315, size: 64, align: 64, offset: 768)
!1336 = !DIDerivedType(tag: DW_TAG_member, name: "tempaddr", scope: !253, file: !121, line: 928, baseType: !1337, size: 128, align: 64, offset: 832)
!1337 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1315, size: 128, align: 64, elements: !1338)
!1338 = !{!1339}
!1339 = !DISubrange(count: 2)
!1340 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr_str", scope: !253, file: !121, line: 933, baseType: !1258, size: 368, align: 8, offset: 960)
!1341 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !253, file: !121, line: 935, baseType: !457, size: 32, align: 32, offset: 1344)
!1342 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !253, file: !121, line: 937, baseType: !316, size: 32, align: 32, offset: 1376)
!1343 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !253, file: !121, line: 939, baseType: !1344, size: 256, align: 64, offset: 1408)
!1344 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostname", file: !121, line: 581, size: 256, align: 64, elements: !1345)
!1345 = !{!1346, !1347, !1348, !1349}
!1346 = !DIDerivedType(tag: DW_TAG_member, name: "rawalloc", scope: !1344, file: !121, line: 582, baseType: !500, size: 64, align: 64)
!1347 = !DIDerivedType(tag: DW_TAG_member, name: "encalloc", scope: !1344, file: !121, line: 583, baseType: !500, size: 64, align: 64, offset: 64)
!1348 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1344, file: !121, line: 584, baseType: !500, size: 64, align: 64, offset: 128)
!1349 = !DIDerivedType(tag: DW_TAG_member, name: "dispname", scope: !1344, file: !121, line: 585, baseType: !527, size: 64, align: 64, offset: 192)
!1350 = !DIDerivedType(tag: DW_TAG_member, name: "secondaryhostname", scope: !253, file: !121, line: 940, baseType: !500, size: 64, align: 64, offset: 1664)
!1351 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !253, file: !121, line: 941, baseType: !1344, size: 256, align: 64, offset: 1728)
!1352 = !DIDerivedType(tag: DW_TAG_member, name: "socks_proxy", scope: !253, file: !121, line: 944, baseType: !1353, size: 512, align: 64, offset: 1984)
!1353 = !DICompositeType(tag: DW_TAG_structure_type, name: "proxy_info", file: !121, line: 883, size: 512, align: 64, elements: !1354)
!1354 = !{!1355, !1356, !1357, !1358, !1359}
!1355 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1353, file: !121, line: 884, baseType: !1344, size: 256, align: 64)
!1356 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !1353, file: !121, line: 885, baseType: !379, size: 64, align: 64, offset: 256)
!1357 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !1353, file: !121, line: 886, baseType: !904, size: 32, align: 32, offset: 320)
!1358 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1353, file: !121, line: 887, baseType: !500, size: 64, align: 64, offset: 384)
!1359 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !1353, file: !121, line: 888, baseType: !500, size: 64, align: 64, offset: 448)
!1360 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !253, file: !121, line: 945, baseType: !1353, size: 512, align: 64, offset: 2496)
!1361 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !253, file: !121, line: 947, baseType: !379, size: 64, align: 64, offset: 3008)
!1362 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !253, file: !121, line: 948, baseType: !316, size: 32, align: 32, offset: 3072)
!1363 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !253, file: !121, line: 949, baseType: !316, size: 32, align: 32, offset: 3104)
!1364 = !DIDerivedType(tag: DW_TAG_member, name: "secondary_port", scope: !253, file: !121, line: 951, baseType: !657, size: 16, align: 16, offset: 3136)
!1365 = !DIDerivedType(tag: DW_TAG_member, name: "primary_ip", scope: !253, file: !121, line: 961, baseType: !1258, size: 368, align: 8, offset: 3152)
!1366 = !DIDerivedType(tag: DW_TAG_member, name: "primary_port", scope: !253, file: !121, line: 962, baseType: !379, size: 64, align: 64, offset: 3520)
!1367 = !DIDerivedType(tag: DW_TAG_member, name: "local_ip", scope: !253, file: !121, line: 968, baseType: !1258, size: 368, align: 8, offset: 3584)
!1368 = !DIDerivedType(tag: DW_TAG_member, name: "local_port", scope: !253, file: !121, line: 969, baseType: !379, size: 64, align: 64, offset: 3968)
!1369 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !253, file: !121, line: 971, baseType: !500, size: 64, align: 64, offset: 4032)
!1370 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !253, file: !121, line: 972, baseType: !500, size: 64, align: 64, offset: 4096)
!1371 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !253, file: !121, line: 973, baseType: !500, size: 64, align: 64, offset: 4160)
!1372 = !DIDerivedType(tag: DW_TAG_member, name: "oauth_bearer", scope: !253, file: !121, line: 975, baseType: !500, size: 64, align: 64, offset: 4224)
!1373 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !253, file: !121, line: 977, baseType: !316, size: 32, align: 32, offset: 4288)
!1374 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !253, file: !121, line: 978, baseType: !316, size: 32, align: 32, offset: 4320)
!1375 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !253, file: !121, line: 980, baseType: !411, size: 128, align: 64, offset: 4352)
!1376 = !DIDerivedType(tag: DW_TAG_member, name: "created", scope: !253, file: !121, line: 981, baseType: !411, size: 128, align: 64, offset: 4480)
!1377 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !253, file: !121, line: 982, baseType: !1378, size: 64, align: 32, offset: 4608)
!1378 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 64, align: 32, elements: !1338)
!1379 = !DIDerivedType(tag: DW_TAG_member, name: "tempsock", scope: !253, file: !121, line: 984, baseType: !1378, size: 64, align: 32, offset: 4672)
!1380 = !DIDerivedType(tag: DW_TAG_member, name: "sock_accepted", scope: !253, file: !121, line: 985, baseType: !1381, size: 16, align: 8, offset: 4736)
!1381 = !DICompositeType(tag: DW_TAG_array_type, baseType: !423, size: 16, align: 8, elements: !1338)
!1382 = !DIDerivedType(tag: DW_TAG_member, name: "recv", scope: !253, file: !121, line: 987, baseType: !1383, size: 128, align: 64, offset: 4800)
!1383 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1384, size: 128, align: 64, elements: !1338)
!1384 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1385, size: 64, align: 64)
!1385 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_recv", file: !121, line: 863, baseType: !1386)
!1386 = !DISubroutineType(types: !1387)
!1387 = !{!612, !262, !316, !500, !347, !1388}
!1388 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !289, size: 64, align: 64)
!1389 = !DIDerivedType(tag: DW_TAG_member, name: "send", scope: !253, file: !121, line: 988, baseType: !1390, size: 128, align: 64, offset: 4928)
!1390 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1391, size: 128, align: 64, elements: !1338)
!1391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1392, size: 64, align: 64)
!1392 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_send", file: !121, line: 856, baseType: !1393)
!1393 = !DISubroutineType(types: !1394)
!1394 = !{!612, !262, !316, !1046, !347, !1388}
!1395 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !253, file: !121, line: 993, baseType: !1396, size: 192, align: 32, offset: 5056)
!1396 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1397, size: 192, align: 32, elements: !1338)
!1397 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_connect_data", file: !121, line: 274, size: 96, align: 32, elements: !1398)
!1398 = !{!1399, !1400, !1402}
!1399 = !DIDerivedType(tag: DW_TAG_member, name: "use", scope: !1397, file: !121, line: 278, baseType: !423, size: 8, align: 8)
!1400 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1397, file: !121, line: 279, baseType: !1401, size: 32, align: 32, offset: 32)
!1401 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connection_state", file: !121, line: 271, baseType: !120)
!1402 = !DIDerivedType(tag: DW_TAG_member, name: "connecting_state", scope: !1397, file: !121, line: 280, baseType: !1403, size: 32, align: 32, offset: 64)
!1403 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connect_state", file: !121, line: 265, baseType: !126)
!1404 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !253, file: !121, line: 994, baseType: !1396, size: 192, align: 32, offset: 5248)
!1405 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !253, file: !121, line: 995, baseType: !535, size: 640, align: 64, offset: 5440)
!1406 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_config", scope: !253, file: !121, line: 996, baseType: !535, size: 640, align: 64, offset: 6080)
!1407 = !DIDerivedType(tag: DW_TAG_member, name: "tls_upgraded", scope: !253, file: !121, line: 997, baseType: !423, size: 8, align: 8, offset: 6720)
!1408 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !253, file: !121, line: 999, baseType: !1409, size: 280, align: 8, offset: 6728)
!1409 = !DICompositeType(tag: DW_TAG_structure_type, name: "ConnectBits", file: !121, line: 514, size: 280, align: 8, elements: !1410)
!1410 = !{!1411, !1412, !1413, !1414, !1415, !1416, !1417, !1418, !1419, !1420, !1421, !1422, !1423, !1424, !1425, !1426, !1427, !1428, !1429, !1430, !1431, !1432, !1433, !1434, !1435, !1436, !1437, !1438, !1439, !1440, !1441, !1442, !1443}
!1411 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !1409, file: !121, line: 516, baseType: !423, size: 8, align: 8)
!1412 = !DIDerivedType(tag: DW_TAG_member, name: "reuse", scope: !1409, file: !121, line: 517, baseType: !423, size: 8, align: 8, offset: 8)
!1413 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1409, file: !121, line: 518, baseType: !423, size: 8, align: 8, offset: 16)
!1414 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1409, file: !121, line: 520, baseType: !423, size: 8, align: 8, offset: 24)
!1415 = !DIDerivedType(tag: DW_TAG_member, name: "proxy", scope: !1409, file: !121, line: 522, baseType: !423, size: 8, align: 8, offset: 32)
!1416 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxy", scope: !1409, file: !121, line: 523, baseType: !423, size: 8, align: 8, offset: 40)
!1417 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy", scope: !1409, file: !121, line: 524, baseType: !423, size: 8, align: 8, offset: 48)
!1418 = !DIDerivedType(tag: DW_TAG_member, name: "user_passwd", scope: !1409, file: !121, line: 525, baseType: !423, size: 8, align: 8, offset: 56)
!1419 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user_passwd", scope: !1409, file: !121, line: 526, baseType: !423, size: 8, align: 8, offset: 64)
!1420 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6_ip", scope: !1409, file: !121, line: 527, baseType: !423, size: 8, align: 8, offset: 72)
!1421 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6", scope: !1409, file: !121, line: 529, baseType: !423, size: 8, align: 8, offset: 80)
!1422 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1409, file: !121, line: 531, baseType: !423, size: 8, align: 8, offset: 88)
!1423 = !DIDerivedType(tag: DW_TAG_member, name: "tcpconnect", scope: !1409, file: !121, line: 533, baseType: !1381, size: 16, align: 8, offset: 96)
!1424 = !DIDerivedType(tag: DW_TAG_member, name: "protoconnstart", scope: !1409, file: !121, line: 535, baseType: !423, size: 8, align: 8, offset: 112)
!1425 = !DIDerivedType(tag: DW_TAG_member, name: "retry", scope: !1409, file: !121, line: 538, baseType: !423, size: 8, align: 8, offset: 120)
!1426 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_proxy", scope: !1409, file: !121, line: 540, baseType: !423, size: 8, align: 8, offset: 128)
!1427 = !DIDerivedType(tag: DW_TAG_member, name: "authneg", scope: !1409, file: !121, line: 544, baseType: !423, size: 8, align: 8, offset: 136)
!1428 = !DIDerivedType(tag: DW_TAG_member, name: "rewindaftersend", scope: !1409, file: !121, line: 548, baseType: !423, size: 8, align: 8, offset: 144)
!1429 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !1409, file: !121, line: 552, baseType: !423, size: 8, align: 8, offset: 152)
!1430 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !1409, file: !121, line: 556, baseType: !423, size: 8, align: 8, offset: 160)
!1431 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_data_ssl", scope: !1409, file: !121, line: 559, baseType: !423, size: 8, align: 8, offset: 168)
!1432 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !1409, file: !121, line: 560, baseType: !423, size: 8, align: 8, offset: 176)
!1433 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd_in_url", scope: !1409, file: !121, line: 561, baseType: !423, size: 8, align: 8, offset: 184)
!1434 = !DIDerivedType(tag: DW_TAG_member, name: "stream_was_rewound", scope: !1409, file: !121, line: 562, baseType: !423, size: 8, align: 8, offset: 192)
!1435 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_connect_closed", scope: !1409, file: !121, line: 565, baseType: !423, size: 8, align: 8, offset: 200)
!1436 = !DIDerivedType(tag: DW_TAG_member, name: "bound", scope: !1409, file: !121, line: 568, baseType: !423, size: 8, align: 8, offset: 208)
!1437 = !DIDerivedType(tag: DW_TAG_member, name: "type_set", scope: !1409, file: !121, line: 570, baseType: !423, size: 8, align: 8, offset: 216)
!1438 = !DIDerivedType(tag: DW_TAG_member, name: "multiplex", scope: !1409, file: !121, line: 571, baseType: !423, size: 8, align: 8, offset: 224)
!1439 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !1409, file: !121, line: 573, baseType: !423, size: 8, align: 8, offset: 232)
!1440 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_npn", scope: !1409, file: !121, line: 574, baseType: !423, size: 8, align: 8, offset: 240)
!1441 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_alpn", scope: !1409, file: !121, line: 575, baseType: !423, size: 8, align: 8, offset: 248)
!1442 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_connected", scope: !1409, file: !121, line: 576, baseType: !1381, size: 16, align: 8, offset: 256)
!1443 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy_connecting", scope: !1409, file: !121, line: 578, baseType: !423, size: 8, align: 8, offset: 272)
!1444 = !DIDerivedType(tag: DW_TAG_member, name: "connecttime", scope: !253, file: !121, line: 1004, baseType: !411, size: 128, align: 64, offset: 7040)
!1445 = !DIDerivedType(tag: DW_TAG_member, name: "num_addr", scope: !253, file: !121, line: 1006, baseType: !316, size: 32, align: 32, offset: 7168)
!1446 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutms_per_addr", scope: !253, file: !121, line: 1007, baseType: !599, size: 64, align: 64, offset: 7232)
!1447 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !253, file: !121, line: 1010, baseType: !1448, size: 64, align: 64, offset: 7296)
!1448 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1449, size: 64, align: 64)
!1449 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1450)
!1450 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_handler", file: !121, line: 763, size: 1024, align: 64, elements: !1451)
!1451 = !{!1452, !1453, !1457, !1462, !1467, !1473, !1474, !1475, !1476, !1481, !1482, !1483, !1489, !1493, !1498, !1499, !1500}
!1452 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1450, file: !121, line: 764, baseType: !527, size: 64, align: 64)
!1453 = !DIDerivedType(tag: DW_TAG_member, name: "setup_connection", scope: !1450, file: !121, line: 767, baseType: !1454, size: 64, align: 64, offset: 64)
!1454 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1455, size: 64, align: 64)
!1455 = !DISubroutineType(types: !1456)
!1456 = !{!289, !262}
!1457 = !DIDerivedType(tag: DW_TAG_member, name: "do_it", scope: !1450, file: !121, line: 770, baseType: !1458, size: 64, align: 64, offset: 128)
!1458 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1459, size: 64, align: 64)
!1459 = !DISubroutineType(types: !1460)
!1460 = !{!289, !262, !1461}
!1461 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !423, size: 64, align: 64)
!1462 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1450, file: !121, line: 771, baseType: !1463, size: 64, align: 64, offset: 192)
!1463 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_done_func", file: !121, line: 634, baseType: !1464)
!1464 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1465, size: 64, align: 64)
!1465 = !DISubroutineType(types: !1466)
!1466 = !{!289, !262, !289, !423}
!1467 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1450, file: !121, line: 777, baseType: !1468, size: 64, align: 64, offset: 256)
!1468 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_do_more_func", file: !121, line: 633, baseType: !1469)
!1469 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1470, size: 64, align: 64)
!1470 = !DISubroutineType(types: !1471)
!1471 = !{!289, !262, !1472}
!1472 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !316, size: 64, align: 64)
!1473 = !DIDerivedType(tag: DW_TAG_member, name: "connect_it", scope: !1450, file: !121, line: 785, baseType: !1458, size: 64, align: 64, offset: 320)
!1474 = !DIDerivedType(tag: DW_TAG_member, name: "connecting", scope: !1450, file: !121, line: 788, baseType: !1458, size: 64, align: 64, offset: 384)
!1475 = !DIDerivedType(tag: DW_TAG_member, name: "doing", scope: !1450, file: !121, line: 789, baseType: !1458, size: 64, align: 64, offset: 448)
!1476 = !DIDerivedType(tag: DW_TAG_member, name: "proto_getsock", scope: !1450, file: !121, line: 793, baseType: !1477, size: 64, align: 64, offset: 512)
!1477 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1478, size: 64, align: 64)
!1478 = !DISubroutineType(types: !1479)
!1479 = !{!316, !262, !1480, !316}
!1480 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!1481 = !DIDerivedType(tag: DW_TAG_member, name: "doing_getsock", scope: !1450, file: !121, line: 799, baseType: !1477, size: 64, align: 64, offset: 576)
!1482 = !DIDerivedType(tag: DW_TAG_member, name: "domore_getsock", scope: !1450, file: !121, line: 805, baseType: !1477, size: 64, align: 64, offset: 640)
!1483 = !DIDerivedType(tag: DW_TAG_member, name: "perform_getsock", scope: !1450, file: !121, line: 812, baseType: !1484, size: 64, align: 64, offset: 704)
!1484 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1485, size: 64, align: 64)
!1485 = !DISubroutineType(types: !1486)
!1486 = !{!316, !1487, !1480, !316}
!1487 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1488, size: 64, align: 64)
!1488 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !253)
!1489 = !DIDerivedType(tag: DW_TAG_member, name: "disconnect", scope: !1450, file: !121, line: 821, baseType: !1490, size: 64, align: 64, offset: 768)
!1490 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1491, size: 64, align: 64)
!1491 = !DISubroutineType(types: !1492)
!1492 = !{!289, !262, !423}
!1493 = !DIDerivedType(tag: DW_TAG_member, name: "readwrite", scope: !1450, file: !121, line: 825, baseType: !1494, size: 64, align: 64, offset: 832)
!1494 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1495, size: 64, align: 64)
!1495 = !DISubroutineType(types: !1496)
!1496 = !{!289, !256, !262, !1497, !1461}
!1497 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !612, size: 64, align: 64)
!1498 = !DIDerivedType(tag: DW_TAG_member, name: "defport", scope: !1450, file: !121, line: 828, baseType: !379, size: 64, align: 64, offset: 896)
!1499 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1450, file: !121, line: 829, baseType: !457, size: 32, align: 32, offset: 960)
!1500 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1450, file: !121, line: 831, baseType: !457, size: 32, align: 32, offset: 992)
!1501 = !DIDerivedType(tag: DW_TAG_member, name: "given", scope: !253, file: !121, line: 1011, baseType: !1448, size: 64, align: 64, offset: 7360)
!1502 = !DIDerivedType(tag: DW_TAG_member, name: "ip_version", scope: !253, file: !121, line: 1013, baseType: !379, size: 64, align: 64, offset: 7424)
!1503 = !DIDerivedType(tag: DW_TAG_member, name: "sockfd", scope: !253, file: !121, line: 1017, baseType: !315, size: 32, align: 32, offset: 7488)
!1504 = !DIDerivedType(tag: DW_TAG_member, name: "writesockfd", scope: !253, file: !121, line: 1018, baseType: !315, size: 32, align: 32, offset: 7520)
!1505 = !DIDerivedType(tag: DW_TAG_member, name: "allocptr", scope: !253, file: !121, line: 1035, baseType: !1506, size: 640, align: 64, offset: 7552)
!1506 = !DICompositeType(tag: DW_TAG_structure_type, name: "dynamically_allocated_data", file: !121, line: 1024, size: 640, align: 64, elements: !1507)
!1507 = !{!1508, !1509, !1510, !1511, !1512, !1513, !1514, !1515, !1516, !1517}
!1508 = !DIDerivedType(tag: DW_TAG_member, name: "proxyuserpwd", scope: !1506, file: !121, line: 1025, baseType: !500, size: 64, align: 64)
!1509 = !DIDerivedType(tag: DW_TAG_member, name: "uagent", scope: !1506, file: !121, line: 1026, baseType: !500, size: 64, align: 64, offset: 64)
!1510 = !DIDerivedType(tag: DW_TAG_member, name: "accept_encoding", scope: !1506, file: !121, line: 1027, baseType: !500, size: 64, align: 64, offset: 128)
!1511 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd", scope: !1506, file: !121, line: 1028, baseType: !500, size: 64, align: 64, offset: 192)
!1512 = !DIDerivedType(tag: DW_TAG_member, name: "rangeline", scope: !1506, file: !121, line: 1029, baseType: !500, size: 64, align: 64, offset: 256)
!1513 = !DIDerivedType(tag: DW_TAG_member, name: "ref", scope: !1506, file: !121, line: 1030, baseType: !500, size: 64, align: 64, offset: 320)
!1514 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1506, file: !121, line: 1031, baseType: !500, size: 64, align: 64, offset: 384)
!1515 = !DIDerivedType(tag: DW_TAG_member, name: "cookiehost", scope: !1506, file: !121, line: 1032, baseType: !500, size: 64, align: 64, offset: 448)
!1516 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_transport", scope: !1506, file: !121, line: 1033, baseType: !500, size: 64, align: 64, offset: 512)
!1517 = !DIDerivedType(tag: DW_TAG_member, name: "te", scope: !1506, file: !121, line: 1034, baseType: !500, size: 64, align: 64, offset: 576)
!1518 = !DIDerivedType(tag: DW_TAG_member, name: "readchannel_inuse", scope: !253, file: !121, line: 1057, baseType: !423, size: 8, align: 8, offset: 8192)
!1519 = !DIDerivedType(tag: DW_TAG_member, name: "writechannel_inuse", scope: !253, file: !121, line: 1059, baseType: !423, size: 8, align: 8, offset: 8200)
!1520 = !DIDerivedType(tag: DW_TAG_member, name: "send_pipe", scope: !253, file: !121, line: 1061, baseType: !330, size: 256, align: 64, offset: 8256)
!1521 = !DIDerivedType(tag: DW_TAG_member, name: "recv_pipe", scope: !253, file: !121, line: 1063, baseType: !330, size: 256, align: 64, offset: 8512)
!1522 = !DIDerivedType(tag: DW_TAG_member, name: "master_buffer", scope: !253, file: !121, line: 1065, baseType: !500, size: 64, align: 64, offset: 8768)
!1523 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !253, file: !121, line: 1067, baseType: !347, size: 64, align: 64, offset: 8832)
!1524 = !DIDerivedType(tag: DW_TAG_member, name: "buf_len", scope: !253, file: !121, line: 1068, baseType: !347, size: 64, align: 64, offset: 8896)
!1525 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !253, file: !121, line: 1071, baseType: !695, size: 64, align: 64, offset: 8960)
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !253, file: !121, line: 1072, baseType: !311, size: 64, align: 64, offset: 9024)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "syserr_buf", scope: !253, file: !121, line: 1091, baseType: !1528, size: 2048, align: 8, offset: 9088)
!1528 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 2048, align: 8, elements: !1529)
!1529 = !{!1530}
!1530 = !DISubrange(count: 256)
!1531 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !253, file: !121, line: 1099, baseType: !500, size: 64, align: 64, offset: 11136)
!1532 = !DIDerivedType(tag: DW_TAG_member, name: "trlMax", scope: !253, file: !121, line: 1100, baseType: !316, size: 32, align: 32, offset: 11200)
!1533 = !DIDerivedType(tag: DW_TAG_member, name: "trlPos", scope: !253, file: !121, line: 1101, baseType: !316, size: 32, align: 32, offset: 11232)
!1534 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !253, file: !121, line: 1114, baseType: !1535, size: 1792, align: 64, offset: 11264)
!1535 = !DICompositeType(tag: DW_TAG_union_type, scope: !253, file: !121, line: 1103, size: 1792, align: 64, elements: !1536)
!1536 = !{!1537, !1584, !1589, !1594, !1597, !1645, !1659, !1671, !1678, !1696}
!1537 = !DIDerivedType(tag: DW_TAG_member, name: "ftpc", scope: !1535, file: !121, line: 1104, baseType: !1538, size: 1792, align: 64)
!1538 = !DICompositeType(tag: DW_TAG_structure_type, name: "ftp_conn", file: !135, line: 118, size: 1792, align: 64, elements: !1539)
!1539 = !{!1540, !1560, !1561, !1563, !1564, !1565, !1566, !1567, !1568, !1569, !1570, !1571, !1572, !1573, !1574, !1575, !1576, !1578, !1579, !1580, !1581, !1582, !1583}
!1540 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1538, file: !135, line: 119, baseType: !1541, size: 896, align: 64)
!1541 = !DICompositeType(tag: DW_TAG_structure_type, name: "pingpong", file: !1542, line: 48, size: 896, align: 64, elements: !1543)
!1542 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1543 = !{!1544, !1545, !1546, !1547, !1548, !1549, !1550, !1551, !1552, !1553, !1554, !1555, !1556}
!1544 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !1541, file: !1542, line: 49, baseType: !500, size: 64, align: 64)
!1545 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !1541, file: !1542, line: 50, baseType: !347, size: 64, align: 64, offset: 64)
!1546 = !DIDerivedType(tag: DW_TAG_member, name: "nread_resp", scope: !1541, file: !1542, line: 51, baseType: !347, size: 64, align: 64, offset: 128)
!1547 = !DIDerivedType(tag: DW_TAG_member, name: "linestart_resp", scope: !1541, file: !1542, line: 52, baseType: !500, size: 64, align: 64, offset: 192)
!1548 = !DIDerivedType(tag: DW_TAG_member, name: "pending_resp", scope: !1541, file: !1542, line: 54, baseType: !423, size: 8, align: 8, offset: 256)
!1549 = !DIDerivedType(tag: DW_TAG_member, name: "sendthis", scope: !1541, file: !1542, line: 57, baseType: !500, size: 64, align: 64, offset: 320)
!1550 = !DIDerivedType(tag: DW_TAG_member, name: "sendleft", scope: !1541, file: !1542, line: 59, baseType: !347, size: 64, align: 64, offset: 384)
!1551 = !DIDerivedType(tag: DW_TAG_member, name: "sendsize", scope: !1541, file: !1542, line: 60, baseType: !347, size: 64, align: 64, offset: 448)
!1552 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !1541, file: !1542, line: 61, baseType: !411, size: 128, align: 64, offset: 512)
!1553 = !DIDerivedType(tag: DW_TAG_member, name: "response_time", scope: !1541, file: !1542, line: 63, baseType: !379, size: 64, align: 64, offset: 640)
!1554 = !DIDerivedType(tag: DW_TAG_member, name: "conn", scope: !1541, file: !1542, line: 66, baseType: !262, size: 64, align: 64, offset: 704)
!1555 = !DIDerivedType(tag: DW_TAG_member, name: "statemach_act", scope: !1541, file: !1542, line: 72, baseType: !1454, size: 64, align: 64, offset: 768)
!1556 = !DIDerivedType(tag: DW_TAG_member, name: "endofresp", scope: !1541, file: !1542, line: 74, baseType: !1557, size: 64, align: 64, offset: 832)
!1557 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1558, size: 64, align: 64)
!1558 = !DISubroutineType(types: !1559)
!1559 = !{!423, !262, !500, !347, !1472}
!1560 = !DIDerivedType(tag: DW_TAG_member, name: "entrypath", scope: !1538, file: !135, line: 120, baseType: !500, size: 64, align: 64, offset: 896)
!1561 = !DIDerivedType(tag: DW_TAG_member, name: "dirs", scope: !1538, file: !135, line: 121, baseType: !1562, size: 64, align: 64, offset: 960)
!1562 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !500, size: 64, align: 64)
!1563 = !DIDerivedType(tag: DW_TAG_member, name: "dirdepth", scope: !1538, file: !135, line: 122, baseType: !316, size: 32, align: 32, offset: 1024)
!1564 = !DIDerivedType(tag: DW_TAG_member, name: "diralloc", scope: !1538, file: !135, line: 123, baseType: !316, size: 32, align: 32, offset: 1056)
!1565 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !1538, file: !135, line: 124, baseType: !500, size: 64, align: 64, offset: 1088)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "dont_check", scope: !1538, file: !135, line: 125, baseType: !423, size: 8, align: 8, offset: 1152)
!1567 = !DIDerivedType(tag: DW_TAG_member, name: "ctl_valid", scope: !1538, file: !135, line: 128, baseType: !423, size: 8, align: 8, offset: 1160)
!1568 = !DIDerivedType(tag: DW_TAG_member, name: "cwddone", scope: !1538, file: !135, line: 131, baseType: !423, size: 8, align: 8, offset: 1168)
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "cwdfail", scope: !1538, file: !135, line: 133, baseType: !423, size: 8, align: 8, offset: 1176)
!1570 = !DIDerivedType(tag: DW_TAG_member, name: "wait_data_conn", scope: !1538, file: !135, line: 135, baseType: !423, size: 8, align: 8, offset: 1184)
!1571 = !DIDerivedType(tag: DW_TAG_member, name: "prevpath", scope: !1538, file: !135, line: 136, baseType: !500, size: 64, align: 64, offset: 1216)
!1572 = !DIDerivedType(tag: DW_TAG_member, name: "transfertype", scope: !1538, file: !135, line: 137, baseType: !501, size: 8, align: 8, offset: 1280)
!1573 = !DIDerivedType(tag: DW_TAG_member, name: "count1", scope: !1538, file: !135, line: 139, baseType: !316, size: 32, align: 32, offset: 1312)
!1574 = !DIDerivedType(tag: DW_TAG_member, name: "count2", scope: !1538, file: !135, line: 140, baseType: !316, size: 32, align: 32, offset: 1344)
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "count3", scope: !1538, file: !135, line: 141, baseType: !316, size: 32, align: 32, offset: 1376)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1538, file: !135, line: 142, baseType: !1577, size: 32, align: 32, offset: 1408)
!1577 = !DIDerivedType(tag: DW_TAG_typedef, name: "ftpstate", file: !135, line: 80, baseType: !134)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "state_saved", scope: !1538, file: !135, line: 143, baseType: !1577, size: 32, align: 32, offset: 1440)
!1579 = !DIDerivedType(tag: DW_TAG_member, name: "retr_size_saved", scope: !1538, file: !135, line: 145, baseType: !507, size: 64, align: 64, offset: 1472)
!1580 = !DIDerivedType(tag: DW_TAG_member, name: "server_os", scope: !1538, file: !135, line: 146, baseType: !500, size: 64, align: 64, offset: 1536)
!1581 = !DIDerivedType(tag: DW_TAG_member, name: "known_filesize", scope: !1538, file: !135, line: 147, baseType: !507, size: 64, align: 64, offset: 1600)
!1582 = !DIDerivedType(tag: DW_TAG_member, name: "newhost", scope: !1538, file: !135, line: 152, baseType: !500, size: 64, align: 64, offset: 1664)
!1583 = !DIDerivedType(tag: DW_TAG_member, name: "newport", scope: !1538, file: !135, line: 153, baseType: !657, size: 16, align: 16, offset: 1728)
!1584 = !DIDerivedType(tag: DW_TAG_member, name: "httpc", scope: !1535, file: !121, line: 1105, baseType: !1585, size: 32, align: 32)
!1585 = !DICompositeType(tag: DW_TAG_structure_type, name: "http_conn", file: !1586, line: 200, size: 32, align: 32, elements: !1587)
!1586 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1587 = !{!1588}
!1588 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !1585, file: !1586, line: 227, baseType: !316, size: 32, align: 32)
!1589 = !DIDerivedType(tag: DW_TAG_member, name: "sshc", scope: !1535, file: !121, line: 1106, baseType: !1590, size: 64, align: 64)
!1590 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssh_conn", file: !1591, line: 110, size: 64, align: 64, elements: !1592)
!1591 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ssh.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1592 = !{!1593}
!1593 = !DIDerivedType(tag: DW_TAG_member, name: "authlist", scope: !1590, file: !1591, line: 111, baseType: !527, size: 64, align: 64)
!1594 = !DIDerivedType(tag: DW_TAG_member, name: "tftpc", scope: !1535, file: !121, line: 1107, baseType: !1595, size: 64, align: 64)
!1595 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1596, size: 64, align: 64)
!1596 = !DICompositeType(tag: DW_TAG_structure_type, name: "tftp_state_data", file: !121, line: 1107, flags: DIFlagFwdDecl)
!1597 = !DIDerivedType(tag: DW_TAG_member, name: "imapc", scope: !1535, file: !121, line: 1108, baseType: !1598, size: 1472, align: 64)
!1598 = !DICompositeType(tag: DW_TAG_structure_type, name: "imap_conn", file: !174, line: 70, size: 1472, align: 64, elements: !1599)
!1599 = !{!1600, !1601, !1603, !1604, !1636, !1637, !1638, !1640, !1641, !1642, !1643, !1644}
!1600 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1598, file: !174, line: 71, baseType: !1541, size: 896, align: 64)
!1601 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1598, file: !174, line: 72, baseType: !1602, size: 32, align: 32, offset: 896)
!1602 = !DIDerivedType(tag: DW_TAG_typedef, name: "imapstate", file: !174, line: 50, baseType: !173)
!1603 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1598, file: !174, line: 73, baseType: !423, size: 8, align: 8, offset: 928)
!1604 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1598, file: !174, line: 74, baseType: !1605, size: 256, align: 64, offset: 960)
!1605 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASL", file: !193, line: 101, size: 256, align: 64, elements: !1606)
!1606 = !{!1607, !1628, !1630, !1631, !1632, !1633, !1634, !1635}
!1607 = !DIDerivedType(tag: DW_TAG_member, name: "params", scope: !1605, file: !193, line: 102, baseType: !1608, size: 64, align: 64)
!1608 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1609, size: 64, align: 64)
!1609 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1610)
!1610 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASLproto", file: !193, line: 86, size: 384, align: 64, elements: !1611)
!1611 = !{!1612, !1613, !1614, !1615, !1616, !1620, !1624}
!1612 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !1610, file: !193, line: 87, baseType: !527, size: 64, align: 64)
!1613 = !DIDerivedType(tag: DW_TAG_member, name: "contcode", scope: !1610, file: !193, line: 88, baseType: !316, size: 32, align: 32, offset: 64)
!1614 = !DIDerivedType(tag: DW_TAG_member, name: "finalcode", scope: !1610, file: !193, line: 89, baseType: !316, size: 32, align: 32, offset: 96)
!1615 = !DIDerivedType(tag: DW_TAG_member, name: "maxirlen", scope: !1610, file: !193, line: 90, baseType: !347, size: 64, align: 64, offset: 128)
!1616 = !DIDerivedType(tag: DW_TAG_member, name: "sendauth", scope: !1610, file: !193, line: 91, baseType: !1617, size: 64, align: 64, offset: 192)
!1617 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1618, size: 64, align: 64)
!1618 = !DISubroutineType(types: !1619)
!1619 = !{!289, !262, !527, !527}
!1620 = !DIDerivedType(tag: DW_TAG_member, name: "sendcont", scope: !1610, file: !193, line: 94, baseType: !1621, size: 64, align: 64, offset: 256)
!1621 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1622, size: 64, align: 64)
!1622 = !DISubroutineType(types: !1623)
!1623 = !{!289, !262, !527}
!1624 = !DIDerivedType(tag: DW_TAG_member, name: "getmessage", scope: !1610, file: !193, line: 96, baseType: !1625, size: 64, align: 64, offset: 320)
!1625 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1626, size: 64, align: 64)
!1626 = !DISubroutineType(types: !1627)
!1627 = !{null, !500, !1562}
!1628 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1605, file: !193, line: 103, baseType: !1629, size: 32, align: 32, offset: 64)
!1629 = !DIDerivedType(tag: DW_TAG_typedef, name: "saslstate", file: !193, line: 76, baseType: !192)
!1630 = !DIDerivedType(tag: DW_TAG_member, name: "authmechs", scope: !1605, file: !193, line: 104, baseType: !457, size: 32, align: 32, offset: 96)
!1631 = !DIDerivedType(tag: DW_TAG_member, name: "prefmech", scope: !1605, file: !193, line: 105, baseType: !457, size: 32, align: 32, offset: 128)
!1632 = !DIDerivedType(tag: DW_TAG_member, name: "authused", scope: !1605, file: !193, line: 106, baseType: !457, size: 32, align: 32, offset: 160)
!1633 = !DIDerivedType(tag: DW_TAG_member, name: "resetprefs", scope: !1605, file: !193, line: 107, baseType: !423, size: 8, align: 8, offset: 192)
!1634 = !DIDerivedType(tag: DW_TAG_member, name: "mutual_auth", scope: !1605, file: !193, line: 108, baseType: !423, size: 8, align: 8, offset: 200)
!1635 = !DIDerivedType(tag: DW_TAG_member, name: "force_ir", scope: !1605, file: !193, line: 109, baseType: !423, size: 8, align: 8, offset: 208)
!1636 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1598, file: !174, line: 75, baseType: !457, size: 32, align: 32, offset: 1216)
!1637 = !DIDerivedType(tag: DW_TAG_member, name: "cmdid", scope: !1598, file: !174, line: 76, baseType: !316, size: 32, align: 32, offset: 1248)
!1638 = !DIDerivedType(tag: DW_TAG_member, name: "resptag", scope: !1598, file: !174, line: 77, baseType: !1639, size: 40, align: 8, offset: 1280)
!1639 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 40, align: 8, elements: !317)
!1640 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1598, file: !174, line: 78, baseType: !423, size: 8, align: 8, offset: 1320)
!1641 = !DIDerivedType(tag: DW_TAG_member, name: "login_disabled", scope: !1598, file: !174, line: 79, baseType: !423, size: 8, align: 8, offset: 1328)
!1642 = !DIDerivedType(tag: DW_TAG_member, name: "ir_supported", scope: !1598, file: !174, line: 80, baseType: !423, size: 8, align: 8, offset: 1336)
!1643 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox", scope: !1598, file: !174, line: 81, baseType: !500, size: 64, align: 64, offset: 1344)
!1644 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox_uidvalidity", scope: !1598, file: !174, line: 82, baseType: !500, size: 64, align: 64, offset: 1408)
!1645 = !DIDerivedType(tag: DW_TAG_member, name: "pop3c", scope: !1535, file: !121, line: 1109, baseType: !1646, size: 1536, align: 64)
!1646 = !DICompositeType(tag: DW_TAG_structure_type, name: "pop3_conn", file: !213, line: 60, size: 1536, align: 64, elements: !1647)
!1647 = !{!1648, !1649, !1651, !1652, !1653, !1654, !1655, !1656, !1657, !1658}
!1648 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1646, file: !213, line: 61, baseType: !1541, size: 896, align: 64)
!1649 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1646, file: !213, line: 62, baseType: !1650, size: 32, align: 32, offset: 896)
!1650 = !DIDerivedType(tag: DW_TAG_typedef, name: "pop3state", file: !213, line: 46, baseType: !212)
!1651 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1646, file: !213, line: 63, baseType: !423, size: 8, align: 8, offset: 928)
!1652 = !DIDerivedType(tag: DW_TAG_member, name: "eob", scope: !1646, file: !213, line: 64, baseType: !347, size: 64, align: 64, offset: 960)
!1653 = !DIDerivedType(tag: DW_TAG_member, name: "strip", scope: !1646, file: !213, line: 66, baseType: !347, size: 64, align: 64, offset: 1024)
!1654 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1646, file: !213, line: 68, baseType: !1605, size: 256, align: 64, offset: 1088)
!1655 = !DIDerivedType(tag: DW_TAG_member, name: "authtypes", scope: !1646, file: !213, line: 69, baseType: !457, size: 32, align: 32, offset: 1344)
!1656 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1646, file: !213, line: 70, baseType: !457, size: 32, align: 32, offset: 1376)
!1657 = !DIDerivedType(tag: DW_TAG_member, name: "apoptimestamp", scope: !1646, file: !213, line: 71, baseType: !500, size: 64, align: 64, offset: 1408)
!1658 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1646, file: !213, line: 72, baseType: !423, size: 8, align: 8, offset: 1472)
!1659 = !DIDerivedType(tag: DW_TAG_member, name: "smtpc", scope: !1535, file: !121, line: 1110, baseType: !1660, size: 1344, align: 64)
!1660 = !DICompositeType(tag: DW_TAG_structure_type, name: "smtp_conn", file: !228, line: 65, size: 1344, align: 64, elements: !1661)
!1661 = !{!1662, !1663, !1665, !1666, !1667, !1668, !1669, !1670}
!1662 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1660, file: !228, line: 66, baseType: !1541, size: 896, align: 64)
!1663 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1660, file: !228, line: 67, baseType: !1664, size: 32, align: 32, offset: 896)
!1664 = !DIDerivedType(tag: DW_TAG_typedef, name: "smtpstate", file: !228, line: 48, baseType: !227)
!1665 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1660, file: !228, line: 68, baseType: !423, size: 8, align: 8, offset: 928)
!1666 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1660, file: !228, line: 69, baseType: !500, size: 64, align: 64, offset: 960)
!1667 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1660, file: !228, line: 70, baseType: !1605, size: 256, align: 64, offset: 1024)
!1668 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1660, file: !228, line: 71, baseType: !423, size: 8, align: 8, offset: 1280)
!1669 = !DIDerivedType(tag: DW_TAG_member, name: "size_supported", scope: !1660, file: !228, line: 72, baseType: !423, size: 8, align: 8, offset: 1288)
!1670 = !DIDerivedType(tag: DW_TAG_member, name: "auth_supported", scope: !1660, file: !228, line: 74, baseType: !423, size: 8, align: 8, offset: 1296)
!1671 = !DIDerivedType(tag: DW_TAG_member, name: "rtspc", scope: !1535, file: !121, line: 1111, baseType: !1672, size: 192, align: 64)
!1672 = !DICompositeType(tag: DW_TAG_structure_type, name: "rtsp_conn", file: !1673, line: 43, size: 192, align: 64, elements: !1674)
!1673 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/rtsp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1674 = !{!1675, !1676, !1677}
!1675 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_buf", scope: !1672, file: !1673, line: 44, baseType: !500, size: 64, align: 64)
!1676 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_bufsize", scope: !1672, file: !1673, line: 45, baseType: !612, size: 64, align: 64, offset: 64)
!1677 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_channel", scope: !1672, file: !1673, line: 46, baseType: !316, size: 32, align: 32, offset: 128)
!1678 = !DIDerivedType(tag: DW_TAG_member, name: "smbc", scope: !1535, file: !121, line: 1112, baseType: !1679, size: 640, align: 64)
!1679 = !DICompositeType(tag: DW_TAG_structure_type, name: "smb_conn", file: !245, line: 33, size: 640, align: 64, elements: !1680)
!1680 = !{!1681, !1682, !1683, !1684, !1689, !1690, !1691, !1692, !1693, !1694, !1695}
!1681 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1679, file: !245, line: 34, baseType: !244, size: 32, align: 32)
!1682 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1679, file: !245, line: 35, baseType: !500, size: 64, align: 64, offset: 64)
!1683 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1679, file: !245, line: 36, baseType: !500, size: 64, align: 64, offset: 128)
!1684 = !DIDerivedType(tag: DW_TAG_member, name: "challenge", scope: !1679, file: !245, line: 37, baseType: !1685, size: 64, align: 8, offset: 192)
!1685 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1686, size: 64, align: 8, elements: !1687)
!1686 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!1687 = !{!1688}
!1688 = !DISubrange(count: 8)
!1689 = !DIDerivedType(tag: DW_TAG_member, name: "session_key", scope: !1679, file: !245, line: 38, baseType: !457, size: 32, align: 32, offset: 256)
!1690 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1679, file: !245, line: 39, baseType: !657, size: 16, align: 16, offset: 288)
!1691 = !DIDerivedType(tag: DW_TAG_member, name: "recv_buf", scope: !1679, file: !245, line: 40, baseType: !500, size: 64, align: 64, offset: 320)
!1692 = !DIDerivedType(tag: DW_TAG_member, name: "upload_size", scope: !1679, file: !245, line: 41, baseType: !347, size: 64, align: 64, offset: 384)
!1693 = !DIDerivedType(tag: DW_TAG_member, name: "send_size", scope: !1679, file: !245, line: 42, baseType: !347, size: 64, align: 64, offset: 448)
!1694 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1679, file: !245, line: 43, baseType: !347, size: 64, align: 64, offset: 512)
!1695 = !DIDerivedType(tag: DW_TAG_member, name: "got", scope: !1679, file: !245, line: 44, baseType: !347, size: 64, align: 64, offset: 576)
!1696 = !DIDerivedType(tag: DW_TAG_member, name: "generic", scope: !1535, file: !121, line: 1113, baseType: !311, size: 64, align: 64)
!1697 = !DIDerivedType(tag: DW_TAG_member, name: "cselect_bits", scope: !253, file: !121, line: 1116, baseType: !316, size: 32, align: 32, offset: 13056)
!1698 = !DIDerivedType(tag: DW_TAG_member, name: "waitfor", scope: !253, file: !121, line: 1117, baseType: !316, size: 32, align: 32, offset: 13088)
!1699 = !DIDerivedType(tag: DW_TAG_member, name: "localdev", scope: !253, file: !121, line: 1128, baseType: !500, size: 64, align: 64, offset: 13120)
!1700 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !253, file: !121, line: 1129, baseType: !657, size: 16, align: 16, offset: 13184)
!1701 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !253, file: !121, line: 1130, baseType: !316, size: 32, align: 32, offset: 13216)
!1702 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_state", scope: !253, file: !121, line: 1137, baseType: !1703, size: 64, align: 32, offset: 13248)
!1703 = !DICompositeType(tag: DW_TAG_array_type, baseType: !252, size: 64, align: 32, elements: !1338)
!1704 = !DIDerivedType(tag: DW_TAG_member, name: "bundle", scope: !253, file: !121, line: 1138, baseType: !1705, size: 64, align: 64, offset: 13312)
!1705 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1706, size: 64, align: 64)
!1706 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectbundle", file: !426, line: 38, size: 384, align: 64, elements: !1707)
!1707 = !{!1708, !1709, !1710}
!1708 = !DIDerivedType(tag: DW_TAG_member, name: "multiuse", scope: !1706, file: !426, line: 39, baseType: !316, size: 32, align: 32)
!1709 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !1706, file: !426, line: 40, baseType: !347, size: 64, align: 64, offset: 64)
!1710 = !DIDerivedType(tag: DW_TAG_member, name: "conn_list", scope: !1706, file: !426, line: 41, baseType: !330, size: 256, align: 64, offset: 128)
!1711 = !DIDerivedType(tag: DW_TAG_member, name: "negnpn", scope: !253, file: !121, line: 1140, baseType: !316, size: 32, align: 32, offset: 13376)
!1712 = !{!1713, !1714, !1715}
!1713 = !DIEnumerator(name: "TUNNEL_INIT", value: 0)
!1714 = !DIEnumerator(name: "TUNNEL_CONNECT", value: 1)
!1715 = !DIEnumerator(name: "TUNNEL_COMPLETE", value: 2)
!1716 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2374, size: 32, align: 32, elements: !1717)
!1717 = !{!1718, !1719, !1720, !1721, !1722, !1723, !1724}
!1718 = !DIEnumerator(name: "CURLSHE_OK", value: 0)
!1719 = !DIEnumerator(name: "CURLSHE_BAD_OPTION", value: 1)
!1720 = !DIEnumerator(name: "CURLSHE_IN_USE", value: 2)
!1721 = !DIEnumerator(name: "CURLSHE_INVALID", value: 3)
!1722 = !DIEnumerator(name: "CURLSHE_NOMEM", value: 4)
!1723 = !DIEnumerator(name: "CURLSHE_NOT_BUILT_IN", value: 5)
!1724 = !DIEnumerator(name: "CURLSHE_LAST", value: 6)
!1725 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2384, size: 32, align: 32, elements: !1726)
!1726 = !{!1727, !1728, !1729, !1730, !1731, !1732, !1733}
!1727 = !DIEnumerator(name: "CURLSHOPT_NONE", value: 0)
!1728 = !DIEnumerator(name: "CURLSHOPT_SHARE", value: 1)
!1729 = !DIEnumerator(name: "CURLSHOPT_UNSHARE", value: 2)
!1730 = !DIEnumerator(name: "CURLSHOPT_LOCKFUNC", value: 3)
!1731 = !DIEnumerator(name: "CURLSHOPT_UNLOCKFUNC", value: 4)
!1732 = !DIEnumerator(name: "CURLSHOPT_USERDATA", value: 5)
!1733 = !DIEnumerator(name: "CURLSHOPT_LAST", value: 6)
!1734 = !{!311}
!1735 = !{!1736, !1742, !1747, !1750, !1753}
!1736 = distinct !DISubprogram(name: "curl_share_init", scope: !1, file: !1, line: 35, type: !1737, isLocal: false, isDefinition: true, scopeLine: 36, flags: DIFlagPrototyped, isOptimized: false, variables: !1741)
!1737 = !DISubroutineType(types: !1738)
!1738 = !{!1739}
!1739 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1740, size: 64, align: 64)
!1740 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLSH", file: !15, line: 101, baseType: !453)
!1741 = !{}
!1742 = distinct !DISubprogram(name: "curl_share_setopt", scope: !1, file: !1, line: 52, type: !1743, isLocal: false, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !1741)
!1743 = !DISubroutineType(types: !1744)
!1744 = !{!1745, !452, !1746, null}
!1745 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLSHcode", file: !15, line: 2382, baseType: !1716)
!1746 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLSHoption", file: !15, line: 2393, baseType: !1725)
!1747 = distinct !DISubprogram(name: "curl_share_cleanup", scope: !1, file: !1, line: 174, type: !1748, isLocal: false, isDefinition: true, scopeLine: 175, flags: DIFlagPrototyped, isOptimized: false, variables: !1741)
!1748 = !DISubroutineType(types: !1749)
!1749 = !{!1745, !452}
!1750 = distinct !DISubprogram(name: "Curl_share_lock", scope: !1, file: !1, line: 213, type: !1751, isLocal: false, isDefinition: true, scopeLine: 215, flags: DIFlagPrototyped, isOptimized: false, variables: !1741)
!1751 = !DISubroutineType(types: !1752)
!1752 = !{!1745, !256, !465, !475}
!1753 = distinct !DISubprogram(name: "Curl_share_unlock", scope: !1, file: !1, line: 231, type: !1754, isLocal: false, isDefinition: true, scopeLine: 232, flags: DIFlagPrototyped, isOptimized: false, variables: !1741)
!1754 = !DISubroutineType(types: !1755)
!1755 = !{!1745, !256, !465}
!1756 = !{i32 2, !"Dwarf Version", i32 4}
!1757 = !{i32 2, !"Debug Info Version", i32 3}
!1758 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1759 = !DILocalVariable(name: "share", scope: !1736, file: !1, line: 37, type: !452)
!1760 = !DIExpression()
!1761 = !DILocation(line: 37, column: 22, scope: !1736)
!1762 = !DILocation(line: 37, column: 30, scope: !1736)
!1763 = !DILocation(line: 38, column: 6, scope: !1764)
!1764 = distinct !DILexicalBlock(scope: !1736, file: !1, line: 38, column: 6)
!1765 = !DILocation(line: 38, column: 6, scope: !1736)
!1766 = !DILocation(line: 39, column: 5, scope: !1767)
!1767 = distinct !DILexicalBlock(scope: !1764, file: !1, line: 38, column: 13)
!1768 = !DILocation(line: 39, column: 12, scope: !1767)
!1769 = !DILocation(line: 39, column: 22, scope: !1767)
!1770 = !DILocation(line: 41, column: 26, scope: !1771)
!1771 = distinct !DILexicalBlock(scope: !1767, file: !1, line: 41, column: 8)
!1772 = !DILocation(line: 41, column: 33, scope: !1771)
!1773 = !DILocation(line: 41, column: 8, scope: !1771)
!1774 = !DILocation(line: 41, column: 8, scope: !1767)
!1775 = !DILocation(line: 42, column: 7, scope: !1776)
!1776 = distinct !DILexicalBlock(scope: !1771, file: !1, line: 41, column: 45)
!1777 = !DILocation(line: 43, column: 7, scope: !1776)
!1778 = !DILocation(line: 45, column: 3, scope: !1767)
!1779 = !DILocation(line: 47, column: 10, scope: !1736)
!1780 = !DILocation(line: 47, column: 3, scope: !1736)
!1781 = !DILocation(line: 48, column: 1, scope: !1736)
!1782 = !DILocalVariable(name: "share", arg: 1, scope: !1742, file: !1, line: 52, type: !452)
!1783 = !DILocation(line: 52, column: 38, scope: !1742)
!1784 = !DILocalVariable(name: "option", arg: 2, scope: !1742, file: !1, line: 52, type: !1746)
!1785 = !DILocation(line: 52, column: 58, scope: !1742)
!1786 = !DILocalVariable(name: "param", scope: !1742, file: !1, line: 54, type: !1787)
!1787 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !627, line: 79, baseType: !1788)
!1788 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !1789, line: 50, baseType: !1790)
!1789 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1790 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 54, baseType: !1791)
!1791 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1792, size: 192, align: 64, elements: !662)
!1792 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 54, size: 192, align: 64, elements: !1793)
!1793 = !{!1794, !1795, !1796, !1797}
!1794 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !1792, file: !1, line: 54, baseType: !457, size: 32, align: 32)
!1795 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !1792, file: !1, line: 54, baseType: !457, size: 32, align: 32, offset: 32)
!1796 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !1792, file: !1, line: 54, baseType: !311, size: 64, align: 64, offset: 64)
!1797 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !1792, file: !1, line: 54, baseType: !311, size: 64, align: 64, offset: 128)
!1798 = !DILocation(line: 54, column: 11, scope: !1742)
!1799 = !DILocalVariable(name: "type", scope: !1742, file: !1, line: 55, type: !316)
!1800 = !DILocation(line: 55, column: 7, scope: !1742)
!1801 = !DILocalVariable(name: "lockfunc", scope: !1742, file: !1, line: 56, type: !461)
!1802 = !DILocation(line: 56, column: 22, scope: !1742)
!1803 = !DILocalVariable(name: "unlockfunc", scope: !1742, file: !1, line: 57, type: !483)
!1804 = !DILocation(line: 57, column: 24, scope: !1742)
!1805 = !DILocalVariable(name: "ptr", scope: !1742, file: !1, line: 58, type: !311)
!1806 = !DILocation(line: 58, column: 9, scope: !1742)
!1807 = !DILocalVariable(name: "res", scope: !1742, file: !1, line: 59, type: !1745)
!1808 = !DILocation(line: 59, column: 14, scope: !1742)
!1809 = !DILocation(line: 61, column: 6, scope: !1810)
!1810 = distinct !DILexicalBlock(scope: !1742, file: !1, line: 61, column: 6)
!1811 = !DILocation(line: 61, column: 13, scope: !1810)
!1812 = !DILocation(line: 61, column: 6, scope: !1742)
!1813 = !DILocation(line: 64, column: 5, scope: !1810)
!1814 = !DILocation(line: 66, column: 3, scope: !1742)
!1815 = !DILocation(line: 68, column: 10, scope: !1742)
!1816 = !DILocation(line: 68, column: 3, scope: !1742)
!1817 = !DILocation(line: 71, column: 12, scope: !1818)
!1818 = distinct !DILexicalBlock(scope: !1742, file: !1, line: 68, column: 18)
!1819 = !DILocation(line: 71, column: 12, scope: !1820)
!1820 = !DILexicalBlockFile(scope: !1818, file: !1, discriminator: 1)
!1821 = !DILocation(line: 71, column: 12, scope: !1822)
!1822 = !DILexicalBlockFile(scope: !1818, file: !1, discriminator: 2)
!1823 = !DILocation(line: 71, column: 12, scope: !1824)
!1824 = !DILexicalBlockFile(scope: !1818, file: !1, discriminator: 3)
!1825 = !DILocation(line: 71, column: 10, scope: !1824)
!1826 = !DILocation(line: 72, column: 29, scope: !1818)
!1827 = !DILocation(line: 72, column: 27, scope: !1818)
!1828 = !DILocation(line: 72, column: 5, scope: !1818)
!1829 = !DILocation(line: 72, column: 12, scope: !1818)
!1830 = !DILocation(line: 72, column: 22, scope: !1818)
!1831 = !DILocation(line: 73, column: 12, scope: !1818)
!1832 = !DILocation(line: 73, column: 5, scope: !1818)
!1833 = !DILocation(line: 75, column: 7, scope: !1834)
!1834 = distinct !DILexicalBlock(scope: !1818, file: !1, line: 73, column: 18)
!1835 = !DILocation(line: 79, column: 11, scope: !1836)
!1836 = distinct !DILexicalBlock(scope: !1834, file: !1, line: 79, column: 10)
!1837 = !DILocation(line: 79, column: 18, scope: !1836)
!1838 = !DILocation(line: 79, column: 10, scope: !1834)
!1839 = !DILocation(line: 80, column: 26, scope: !1840)
!1840 = distinct !DILexicalBlock(scope: !1836, file: !1, line: 79, column: 27)
!1841 = !DILocation(line: 80, column: 9, scope: !1840)
!1842 = !DILocation(line: 80, column: 16, scope: !1840)
!1843 = !DILocation(line: 80, column: 24, scope: !1840)
!1844 = !DILocation(line: 81, column: 13, scope: !1845)
!1845 = distinct !DILexicalBlock(scope: !1840, file: !1, line: 81, column: 12)
!1846 = !DILocation(line: 81, column: 20, scope: !1845)
!1847 = !DILocation(line: 81, column: 12, scope: !1840)
!1848 = !DILocation(line: 82, column: 15, scope: !1845)
!1849 = !DILocation(line: 82, column: 11, scope: !1845)
!1850 = !DILocation(line: 83, column: 7, scope: !1840)
!1851 = !DILocation(line: 87, column: 7, scope: !1834)
!1852 = !DILocation(line: 100, column: 11, scope: !1834)
!1853 = !DILocation(line: 102, column: 7, scope: !1834)
!1854 = !DILocation(line: 105, column: 7, scope: !1834)
!1855 = !DILocation(line: 108, column: 11, scope: !1834)
!1856 = !DILocation(line: 109, column: 5, scope: !1834)
!1857 = !DILocation(line: 110, column: 5, scope: !1818)
!1858 = !DILocation(line: 114, column: 12, scope: !1818)
!1859 = !DILocation(line: 114, column: 12, scope: !1820)
!1860 = !DILocation(line: 114, column: 12, scope: !1822)
!1861 = !DILocation(line: 114, column: 12, scope: !1824)
!1862 = !DILocation(line: 114, column: 10, scope: !1824)
!1863 = !DILocation(line: 115, column: 30, scope: !1818)
!1864 = !DILocation(line: 115, column: 28, scope: !1818)
!1865 = !DILocation(line: 115, column: 25, scope: !1818)
!1866 = !DILocation(line: 115, column: 5, scope: !1818)
!1867 = !DILocation(line: 115, column: 12, scope: !1818)
!1868 = !DILocation(line: 115, column: 22, scope: !1818)
!1869 = !DILocation(line: 116, column: 12, scope: !1818)
!1870 = !DILocation(line: 116, column: 5, scope: !1818)
!1871 = !DILocation(line: 118, column: 7, scope: !1872)
!1872 = distinct !DILexicalBlock(scope: !1818, file: !1, line: 116, column: 18)
!1873 = !DILocation(line: 122, column: 10, scope: !1874)
!1874 = distinct !DILexicalBlock(scope: !1872, file: !1, line: 122, column: 10)
!1875 = !DILocation(line: 122, column: 17, scope: !1874)
!1876 = !DILocation(line: 122, column: 10, scope: !1872)
!1877 = !DILocation(line: 123, column: 29, scope: !1878)
!1878 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 122, column: 26)
!1879 = !DILocation(line: 123, column: 36, scope: !1878)
!1880 = !DILocation(line: 123, column: 9, scope: !1878)
!1881 = !DILocation(line: 124, column: 9, scope: !1878)
!1882 = !DILocation(line: 124, column: 16, scope: !1878)
!1883 = !DILocation(line: 124, column: 24, scope: !1878)
!1884 = !DILocation(line: 125, column: 7, scope: !1878)
!1885 = !DILocation(line: 129, column: 7, scope: !1872)
!1886 = !DILocation(line: 135, column: 11, scope: !1872)
!1887 = !DILocation(line: 137, column: 7, scope: !1872)
!1888 = !DILocation(line: 140, column: 7, scope: !1872)
!1889 = !DILocation(line: 143, column: 11, scope: !1872)
!1890 = !DILocation(line: 144, column: 7, scope: !1872)
!1891 = !DILocation(line: 146, column: 5, scope: !1818)
!1892 = !DILocation(line: 149, column: 16, scope: !1818)
!1893 = !DILocation(line: 149, column: 16, scope: !1820)
!1894 = !DILocation(line: 149, column: 16, scope: !1822)
!1895 = !DILocation(line: 149, column: 16, scope: !1824)
!1896 = !DILocation(line: 149, column: 14, scope: !1824)
!1897 = !DILocation(line: 150, column: 23, scope: !1818)
!1898 = !DILocation(line: 150, column: 5, scope: !1818)
!1899 = !DILocation(line: 150, column: 12, scope: !1818)
!1900 = !DILocation(line: 150, column: 21, scope: !1818)
!1901 = !DILocation(line: 151, column: 5, scope: !1818)
!1902 = !DILocation(line: 154, column: 18, scope: !1818)
!1903 = !DILocation(line: 154, column: 18, scope: !1820)
!1904 = !DILocation(line: 154, column: 18, scope: !1822)
!1905 = !DILocation(line: 154, column: 18, scope: !1824)
!1906 = !DILocation(line: 154, column: 16, scope: !1824)
!1907 = !DILocation(line: 155, column: 25, scope: !1818)
!1908 = !DILocation(line: 155, column: 5, scope: !1818)
!1909 = !DILocation(line: 155, column: 12, scope: !1818)
!1910 = !DILocation(line: 155, column: 23, scope: !1818)
!1911 = !DILocation(line: 156, column: 5, scope: !1818)
!1912 = !DILocation(line: 159, column: 11, scope: !1818)
!1913 = !DILocation(line: 159, column: 11, scope: !1820)
!1914 = !DILocation(line: 159, column: 11, scope: !1822)
!1915 = !DILocation(line: 159, column: 11, scope: !1824)
!1916 = !DILocation(line: 159, column: 9, scope: !1824)
!1917 = !DILocation(line: 160, column: 25, scope: !1818)
!1918 = !DILocation(line: 160, column: 5, scope: !1818)
!1919 = !DILocation(line: 160, column: 12, scope: !1818)
!1920 = !DILocation(line: 160, column: 23, scope: !1818)
!1921 = !DILocation(line: 161, column: 5, scope: !1818)
!1922 = !DILocation(line: 164, column: 9, scope: !1818)
!1923 = !DILocation(line: 165, column: 5, scope: !1818)
!1924 = !DILocation(line: 168, column: 3, scope: !1742)
!1925 = !DILocation(line: 170, column: 10, scope: !1742)
!1926 = !DILocation(line: 170, column: 3, scope: !1742)
!1927 = !DILocation(line: 171, column: 1, scope: !1742)
!1928 = !DILocalVariable(name: "share", arg: 1, scope: !1747, file: !1, line: 174, type: !452)
!1929 = !DILocation(line: 174, column: 39, scope: !1747)
!1930 = !DILocation(line: 176, column: 6, scope: !1931)
!1931 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 176, column: 6)
!1932 = !DILocation(line: 176, column: 12, scope: !1931)
!1933 = !DILocation(line: 176, column: 6, scope: !1747)
!1934 = !DILocation(line: 177, column: 5, scope: !1931)
!1935 = !DILocation(line: 179, column: 6, scope: !1936)
!1936 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 179, column: 6)
!1937 = !DILocation(line: 179, column: 13, scope: !1936)
!1938 = !DILocation(line: 179, column: 6, scope: !1747)
!1939 = !DILocation(line: 180, column: 5, scope: !1936)
!1940 = !DILocation(line: 180, column: 12, scope: !1936)
!1941 = !DILocation(line: 181, column: 21, scope: !1936)
!1942 = !DILocation(line: 181, column: 28, scope: !1936)
!1943 = !DILocation(line: 183, column: 6, scope: !1944)
!1944 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 183, column: 6)
!1945 = !DILocation(line: 183, column: 13, scope: !1944)
!1946 = !DILocation(line: 183, column: 6, scope: !1747)
!1947 = !DILocation(line: 184, column: 8, scope: !1948)
!1948 = distinct !DILexicalBlock(scope: !1949, file: !1, line: 184, column: 8)
!1949 = distinct !DILexicalBlock(scope: !1944, file: !1, line: 183, column: 20)
!1950 = !DILocation(line: 184, column: 15, scope: !1948)
!1951 = !DILocation(line: 184, column: 8, scope: !1949)
!1952 = !DILocation(line: 185, column: 7, scope: !1948)
!1953 = !DILocation(line: 185, column: 14, scope: !1948)
!1954 = !DILocation(line: 185, column: 53, scope: !1948)
!1955 = !DILocation(line: 185, column: 60, scope: !1948)
!1956 = !DILocation(line: 186, column: 5, scope: !1949)
!1957 = !DILocation(line: 189, column: 22, scope: !1747)
!1958 = !DILocation(line: 189, column: 29, scope: !1747)
!1959 = !DILocation(line: 189, column: 3, scope: !1747)
!1960 = !DILocation(line: 192, column: 23, scope: !1747)
!1961 = !DILocation(line: 192, column: 30, scope: !1747)
!1962 = !DILocation(line: 192, column: 3, scope: !1747)
!1963 = !DILocation(line: 204, column: 6, scope: !1964)
!1964 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 204, column: 6)
!1965 = !DILocation(line: 204, column: 13, scope: !1964)
!1966 = !DILocation(line: 204, column: 6, scope: !1747)
!1967 = !DILocation(line: 205, column: 5, scope: !1964)
!1968 = !DILocation(line: 205, column: 12, scope: !1964)
!1969 = !DILocation(line: 205, column: 51, scope: !1964)
!1970 = !DILocation(line: 205, column: 58, scope: !1964)
!1971 = !DILocation(line: 206, column: 3, scope: !1747)
!1972 = !DILocation(line: 208, column: 3, scope: !1747)
!1973 = !DILocation(line: 209, column: 1, scope: !1747)
!1974 = !DILocalVariable(name: "data", arg: 1, scope: !1750, file: !1, line: 213, type: !256)
!1975 = !DILocation(line: 213, column: 35, scope: !1750)
!1976 = !DILocalVariable(name: "type", arg: 2, scope: !1750, file: !1, line: 213, type: !465)
!1977 = !DILocation(line: 213, column: 56, scope: !1750)
!1978 = !DILocalVariable(name: "accesstype", arg: 3, scope: !1750, file: !1, line: 214, type: !475)
!1979 = !DILocation(line: 214, column: 34, scope: !1750)
!1980 = !DILocalVariable(name: "share", scope: !1750, file: !1, line: 216, type: !452)
!1981 = !DILocation(line: 216, column: 22, scope: !1750)
!1982 = !DILocation(line: 216, column: 30, scope: !1750)
!1983 = !DILocation(line: 216, column: 36, scope: !1750)
!1984 = !DILocation(line: 218, column: 6, scope: !1985)
!1985 = distinct !DILexicalBlock(scope: !1750, file: !1, line: 218, column: 6)
!1986 = !DILocation(line: 218, column: 12, scope: !1985)
!1987 = !DILocation(line: 218, column: 6, scope: !1750)
!1988 = !DILocation(line: 219, column: 5, scope: !1985)
!1989 = !DILocation(line: 221, column: 6, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !1750, file: !1, line: 221, column: 6)
!1991 = !DILocation(line: 221, column: 13, scope: !1990)
!1992 = !DILocation(line: 221, column: 29, scope: !1990)
!1993 = !DILocation(line: 221, column: 27, scope: !1990)
!1994 = !DILocation(line: 221, column: 23, scope: !1990)
!1995 = !DILocation(line: 221, column: 6, scope: !1750)
!1996 = !DILocation(line: 222, column: 8, scope: !1997)
!1997 = distinct !DILexicalBlock(scope: !1998, file: !1, line: 222, column: 8)
!1998 = distinct !DILexicalBlock(scope: !1990, file: !1, line: 221, column: 36)
!1999 = !DILocation(line: 222, column: 15, scope: !1997)
!2000 = !DILocation(line: 222, column: 8, scope: !1998)
!2001 = !DILocation(line: 223, column: 7, scope: !1997)
!2002 = !DILocation(line: 223, column: 14, scope: !1997)
!2003 = !DILocation(line: 223, column: 23, scope: !1997)
!2004 = !DILocation(line: 223, column: 29, scope: !1997)
!2005 = !DILocation(line: 223, column: 35, scope: !1997)
!2006 = !DILocation(line: 223, column: 47, scope: !1997)
!2007 = !DILocation(line: 223, column: 54, scope: !1997)
!2008 = !DILocation(line: 224, column: 3, scope: !1998)
!2009 = !DILocation(line: 227, column: 3, scope: !1750)
!2010 = !DILocation(line: 228, column: 1, scope: !1750)
!2011 = !DILocalVariable(name: "data", arg: 1, scope: !1753, file: !1, line: 231, type: !256)
!2012 = !DILocation(line: 231, column: 37, scope: !1753)
!2013 = !DILocalVariable(name: "type", arg: 2, scope: !1753, file: !1, line: 231, type: !465)
!2014 = !DILocation(line: 231, column: 58, scope: !1753)
!2015 = !DILocalVariable(name: "share", scope: !1753, file: !1, line: 233, type: !452)
!2016 = !DILocation(line: 233, column: 22, scope: !1753)
!2017 = !DILocation(line: 233, column: 30, scope: !1753)
!2018 = !DILocation(line: 233, column: 36, scope: !1753)
!2019 = !DILocation(line: 235, column: 6, scope: !2020)
!2020 = distinct !DILexicalBlock(scope: !1753, file: !1, line: 235, column: 6)
!2021 = !DILocation(line: 235, column: 12, scope: !2020)
!2022 = !DILocation(line: 235, column: 6, scope: !1753)
!2023 = !DILocation(line: 236, column: 5, scope: !2020)
!2024 = !DILocation(line: 238, column: 6, scope: !2025)
!2025 = distinct !DILexicalBlock(scope: !1753, file: !1, line: 238, column: 6)
!2026 = !DILocation(line: 238, column: 13, scope: !2025)
!2027 = !DILocation(line: 238, column: 29, scope: !2025)
!2028 = !DILocation(line: 238, column: 27, scope: !2025)
!2029 = !DILocation(line: 238, column: 23, scope: !2025)
!2030 = !DILocation(line: 238, column: 6, scope: !1753)
!2031 = !DILocation(line: 239, column: 8, scope: !2032)
!2032 = distinct !DILexicalBlock(scope: !2033, file: !1, line: 239, column: 8)
!2033 = distinct !DILexicalBlock(scope: !2025, file: !1, line: 238, column: 36)
!2034 = !DILocation(line: 239, column: 15, scope: !2032)
!2035 = !DILocation(line: 239, column: 8, scope: !2033)
!2036 = !DILocation(line: 240, column: 7, scope: !2032)
!2037 = !DILocation(line: 240, column: 14, scope: !2032)
!2038 = !DILocation(line: 240, column: 26, scope: !2032)
!2039 = !DILocation(line: 240, column: 32, scope: !2032)
!2040 = !DILocation(line: 240, column: 38, scope: !2032)
!2041 = !DILocation(line: 240, column: 45, scope: !2032)
!2042 = !DILocation(line: 241, column: 3, scope: !2033)
!2043 = !DILocation(line: 243, column: 3, scope: !1753)
!2044 = !DILocation(line: 244, column: 1, scope: !1753)
