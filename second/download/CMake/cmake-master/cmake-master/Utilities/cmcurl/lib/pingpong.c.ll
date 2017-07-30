; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, i32 (%struct.connectdata*)*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.timeval = type { i64, i64 }
%struct.connectdata = type { %struct.Curl_easy*, %struct.Curl_chunker, i32 (i8*, i32)*, i8*, i8, i64, %struct.Curl_dns_entry*, %struct.Curl_addrinfo*, [2 x %struct.Curl_addrinfo*], [46 x i8], i32, i32, %struct.hostname, i8*, %struct.hostname, %struct.proxy_info, %struct.proxy_info, i64, i32, i32, i16, [46 x i8], i64, [46 x i8], i64, i8*, i8*, i8*, i8*, i32, i32, %struct.timeval, %struct.timeval, [2 x i32], [2 x i32], [2 x i8], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data], %struct.ssl_primary_config, %struct.ssl_primary_config, i8, %struct.ConnectBits, %struct.timeval, i32, i64, %struct.Curl_handler*, %struct.Curl_handler*, i64, i32, i32, %struct.dynamically_allocated_data, i8, i8, %struct.curl_llist, %struct.curl_llist, i8*, i64, i64, i32 (i8*, i64, i32)*, i8*, [256 x i8], i8*, i32, i32, %union.anon.0, i32, i32, i8*, i16, i32, [2 x i32], %struct.connectbundle*, i32 }
%struct.Curl_easy = type { %struct.Curl_easy*, %struct.Curl_easy*, %struct.connectdata*, i32, i32, %struct.Curl_message, [5 x i32], i32, %struct.Names, %struct.Curl_multi*, %struct.Curl_multi*, %struct.Curl_share*, %struct.SingleRequest, %struct.UserDefined, %struct.DynamicStatic, %struct.CookieInfo*, %struct.Progress, %struct.UrlState, %struct.WildcardData, %struct.PureInfo, %struct.curl_tlssessioninfo, i32 }
%struct.Curl_message = type { %struct.CURLMsg }
%struct.CURLMsg = type { i32, %struct.Curl_easy*, %union.anon }
%union.anon = type { i8* }
%struct.Names = type { %struct.curl_hash*, i32 }
%struct.curl_hash = type { %struct.curl_llist*, i64 (i8*, i64, i64)*, i64 (i8*, i64, i8*, i64)*, void (i8*)*, i32, i64 }
%struct.Curl_multi = type { i64, %struct.Curl_easy*, %struct.Curl_easy*, i32, i32, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_easy*, i32, i32, i8*, i8*)*, i8*, i32 (%struct.Curl_easy*, %struct.Curl_easy*, i64, %struct.curl_pushheaders*, i8*)*, i8*, %struct.curl_hash, %struct.Curl_tree*, %struct.curl_hash, i64, i8, %struct.conncache, %struct.Curl_easy*, i64, i64, i64, i64, i64, i64, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_multi*, i64, i8*)*, i8*, %struct.timeval }
%struct.curl_pushheaders = type opaque
%struct.Curl_tree = type { %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.timeval, i8* }
%struct.conncache = type { %struct.curl_hash, i64, i64, %struct.timeval }
%struct.Curl_share = type opaque
%struct.SingleRequest = type { i64, i64*, i64, i64*, i64, i64, i64, i64, %struct.timeval, %struct.timeval, i8, i32, i32, i8*, i64, i8*, i8*, i8*, i8*, i8, i64, i32, %struct.timeval, i32, i32, i32, i64, i64, i8*, i8*, i32, i32, i8, i8, i8, i8*, i8*, i64, i8*, i8, i8, i8, i8, i8* }
%struct.UserDefined = type { %struct._IO_FILE*, i8*, i8*, i64, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i64, i32, i8, i8*, i32 (i8*, i64, i32)*, i64, i16, i32, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i32, i32, i32 (i8*, double, double, double, double)*, i32 (i8*, i64, i64, i64, i64)*, i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)*, i32 (%struct.Curl_easy*, i32, i8*)*, i32 (i8*, i32, i32)*, i8*, i32 (i8*, i32, %struct.curl_sockaddr*)*, i8*, i32 (i8*, i32)*, i8*, i8*, i32 (i8*, i64)*, i32 (i8*, i64)*, i32 (i8*, i64)*, i8*, i8*, i64, i64, i64, i64, i64, i8, i64, i64, i64, i64, i64, i64, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_httppost*, i8, i8, i8, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, i32, i64, i32, i64, %struct.ssl_config_data, %struct.ssl_config_data, %struct.ssl_general_config, i32, i64, i64, i8*, %struct.curl_slist*, i64, i64, i32, i32, i32 (%struct.Curl_easy*, %struct.curl_khkey*, %struct.curl_khkey*, i32, i8*)*, i8*, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i32, i8, i8, i8, i8, i8, i8, i8, i32, i32, i32, i8, i8, i8, i8, i8, i8, i64, i8, i8, i64, i64, i8, [56 x i8*], i32, i64, i64, %struct.curl_slist*, i8, i32, i64, i8, i64 (i8*, i8*, i32)*, i64 (i8*)*, i32 (i8*, i8*, i8*)*, i8*, i64, i8, i64, i64, i8, i64, i8, i8, i8, i8, i64, i8, %struct.Curl_easy*, i8, i32, %struct.Curl_http2_dep*, i8 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.curl_sockaddr = type { i32, i32, i32, i32, %struct.sockaddr }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.curl_httppost = type { %struct.curl_httppost*, i8*, i64, i8*, i64, i8*, i64, i8*, %struct.curl_slist*, %struct.curl_httppost*, i64, i8*, i8*, i64 }
%struct.ssl_config_data = type { %struct.ssl_primary_config, i8, i8, i64, i8*, i8*, i32 (%struct.Curl_easy*, i8*, i8*)*, i8*, i8, i8, i8*, i8*, i8*, i8*, i8* }
%struct.ssl_general_config = type { i64 }
%struct.curl_khkey = type { i8*, i64, i32 }
%struct.curl_slist = type { i8*, %struct.curl_slist* }
%struct.Curl_http2_dep = type { %struct.Curl_http2_dep*, %struct.Curl_easy* }
%struct.DynamicStatic = type { i8*, i8, i8*, i8, %struct.curl_slist*, %struct.curl_slist* }
%struct.CookieInfo = type { %struct.Cookie*, i8*, i8, i64, i8 }
%struct.Cookie = type { %struct.Cookie*, i8*, i8*, i8*, i8*, i8*, i64, i8*, i8, i8*, i8*, i8, i8, i8 }
%struct.Progress = type { i64, i64, i64, i64, i64, i64, i8, i32, i32, double, i64, i64, double, double, double, double, double, double, %struct.timeval, %struct.timeval, %struct.timeval, %struct.timeval, %struct.timeval, i64, %struct.timeval, i64, [6 x i64], [6 x %struct.timeval], i32 }
%struct.UrlState = type { %struct.conncache*, i8, %struct.timeval, %struct.connectdata*, i8*, i64, i8*, [16385 x i8], i64, i8, i8*, i32, %struct.curl_ssl_session*, i64, i32, [3 x %struct.tempbuf], i8*, i8, i32, void (i32)*, i8, %struct.digestdata, %struct.digestdata, %struct.auth, %struct.auth, i8, i8*, %struct.timeval, %struct.Curl_tree, %struct.curl_llist, i8*, i8, i32, i8, i8, i8, i64, i8*, i8*, i8, i8, i8, i8*, i64, i64, i64, i64, i64, i64, i8, i64 (i8*, i64, i64, i8*)*, i8*, %struct.Curl_easy*, i8, i32 }
%struct.curl_ssl_session = type { i8*, i8*, i8*, i8*, i64, i64, i32, i32, %struct.ssl_primary_config }
%struct.tempbuf = type { i8*, i64, i32 }
%struct.digestdata = type { i8*, i8*, i8*, i32, i8, i8*, i8*, i8*, i32 }
%struct.auth = type { i64, i64, i64, i8, i8, i8 }
%struct.WildcardData = type { i32, i8*, i8*, %struct.curl_llist, i8*, void (i8*)*, i8* }
%struct.PureInfo = type { i32, i32, i32, i64, i8, i64, i64, i64, i64, i64, i8*, i8*, [46 x i8], i64, [46 x i8], i64, i8*, i32, %struct.curl_certinfo }
%struct.curl_certinfo = type { i32, %struct.curl_slist** }
%struct.curl_tlssessioninfo = type { i32, i8* }
%struct.Curl_chunker = type { [17 x i8], i32, i32, i64, i64 }
%struct.Curl_dns_entry = type { %struct.Curl_addrinfo*, i64, i64 }
%struct.Curl_addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.Curl_addrinfo* }
%struct.hostname = type { i8*, i8*, i8*, i8* }
%struct.proxy_info = type { %struct.hostname, i64, i32, i8*, i8* }
%struct.ssl_connect_data = type { i8, i32, i32 }
%struct.ssl_primary_config = type { i64, i64, i8, i8, i8, i8*, i8*, i8*, i8*, i8*, i8*, i8 }
%struct.ConnectBits = type { i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8 }
%struct.Curl_handler = type { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }
%struct.dynamically_allocated_data = type { i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8* }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%union.anon.0 = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [24 x i8] c"server response timeout\00", align 1
@.str.1 = private unnamed_addr constant [18 x i8] c"select/poll error\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"%s\0D\0A\00", align 1
@Curl_cfree = external global void (i8*)*, align 8
@.str.3 = private unnamed_addr constant [24 x i8] c"response reading failed\00", align 1
@.str.4 = private unnamed_addr constant [70 x i8] c"Excessive server response line length received, %zd bytes. Stripping\0A\00", align 1
@Curl_cmalloc = external global i8* (i64)*, align 8

; Function Attrs: nounwind uwtable
define i64 @Curl_pp_state_timeout(%struct.pingpong* %pp) #0 !dbg !1680 {
entry:
  %pp.addr = alloca %struct.pingpong*, align 8
  %conn = alloca %struct.connectdata*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %timeout_ms = alloca i64, align 8
  %timeout2_ms = alloca i64, align 8
  %response_time = alloca i64, align 8
  %agg.tmp = alloca %struct.timeval, align 8
  %agg.tmp11 = alloca %struct.timeval, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !1721, metadata !1722), !dbg !1723
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !1724, metadata !1722), !dbg !1725
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1726
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !1727
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !1727
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !1725
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1728, metadata !1722), !dbg !1729
  %2 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1730
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 0, !dbg !1731
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !1731
  store %struct.Curl_easy* %3, %struct.Curl_easy** %data, align 8, !dbg !1729
  call void @llvm.dbg.declare(metadata i64* %timeout_ms, metadata !1732, metadata !1722), !dbg !1733
  call void @llvm.dbg.declare(metadata i64* %timeout2_ms, metadata !1734, metadata !1722), !dbg !1735
  call void @llvm.dbg.declare(metadata i64* %response_time, metadata !1736, metadata !1722), !dbg !1737
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1738
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 13, !dbg !1739
  %server_response_timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 45, !dbg !1740
  %5 = load i64, i64* %server_response_timeout, align 8, !dbg !1740
  %tobool = icmp ne i64 %5, 0, !dbg !1741
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !1741

cond.true:                                        ; preds = %entry
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1742
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 13, !dbg !1743
  %server_response_timeout4 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 45, !dbg !1744
  %7 = load i64, i64* %server_response_timeout4, align 8, !dbg !1744
  br label %cond.end, !dbg !1745

cond.false:                                       ; preds = %entry
  %8 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1747
  %response_time5 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %8, i32 0, i32 9, !dbg !1748
  %9 = load i64, i64* %response_time5, align 8, !dbg !1748
  br label %cond.end, !dbg !1749

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %7, %cond.true ], [ %9, %cond.false ], !dbg !1751
  store i64 %cond, i64* %response_time, align 8, !dbg !1753
  %10 = load i64, i64* %response_time, align 8, !dbg !1754
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !1755
  %11 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !1755
  %12 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %11, i32 0, i32 0, !dbg !1755
  %13 = extractvalue { i64, i64 } %call, 0, !dbg !1755
  store i64 %13, i64* %12, align 8, !dbg !1755
  %14 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %11, i32 0, i32 1, !dbg !1755
  %15 = extractvalue { i64, i64 } %call, 1, !dbg !1755
  store i64 %15, i64* %14, align 8, !dbg !1755
  %16 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1755
  %response = getelementptr inbounds %struct.pingpong, %struct.pingpong* %16, i32 0, i32 8, !dbg !1755
  %17 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !1755
  %18 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %17, i32 0, i32 0, !dbg !1755
  %19 = load i64, i64* %18, align 8, !dbg !1755
  %20 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %17, i32 0, i32 1, !dbg !1755
  %21 = load i64, i64* %20, align 8, !dbg !1755
  %22 = bitcast %struct.timeval* %response to { i64, i64 }*, !dbg !1755
  %23 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %22, i32 0, i32 0, !dbg !1755
  %24 = load i64, i64* %23, align 8, !dbg !1755
  %25 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %22, i32 0, i32 1, !dbg !1755
  %26 = load i64, i64* %25, align 8, !dbg !1755
  %call6 = call i64 @curlx_tvdiff(i64 %19, i64 %21, i64 %24, i64 %26), !dbg !1756
  %sub = sub nsw i64 %10, %call6, !dbg !1757
  store i64 %sub, i64* %timeout_ms, align 8, !dbg !1758
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1759
  %set7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %27, i32 0, i32 13, !dbg !1761
  %timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set7, i32 0, i32 42, !dbg !1762
  %28 = load i64, i64* %timeout, align 8, !dbg !1762
  %tobool8 = icmp ne i64 %28, 0, !dbg !1759
  br i1 %tobool8, label %if.then, label %if.end, !dbg !1763

if.then:                                          ; preds = %cond.end
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1764
  %set9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 13, !dbg !1766
  %timeout10 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set9, i32 0, i32 42, !dbg !1767
  %30 = load i64, i64* %timeout10, align 8, !dbg !1767
  %call12 = call { i64, i64 } @curlx_tvnow(), !dbg !1768
  %31 = bitcast %struct.timeval* %agg.tmp11 to { i64, i64 }*, !dbg !1768
  %32 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 0, !dbg !1768
  %33 = extractvalue { i64, i64 } %call12, 0, !dbg !1768
  store i64 %33, i64* %32, align 8, !dbg !1768
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 1, !dbg !1768
  %35 = extractvalue { i64, i64 } %call12, 1, !dbg !1768
  store i64 %35, i64* %34, align 8, !dbg !1768
  %36 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1768
  %now = getelementptr inbounds %struct.connectdata, %struct.connectdata* %36, i32 0, i32 31, !dbg !1768
  %37 = bitcast %struct.timeval* %agg.tmp11 to { i64, i64 }*, !dbg !1768
  %38 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %37, i32 0, i32 0, !dbg !1768
  %39 = load i64, i64* %38, align 8, !dbg !1768
  %40 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %37, i32 0, i32 1, !dbg !1768
  %41 = load i64, i64* %40, align 8, !dbg !1768
  %42 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !1768
  %43 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %42, i32 0, i32 0, !dbg !1768
  %44 = load i64, i64* %43, align 8, !dbg !1768
  %45 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %42, i32 0, i32 1, !dbg !1768
  %46 = load i64, i64* %45, align 8, !dbg !1768
  %call13 = call i64 @curlx_tvdiff(i64 %39, i64 %41, i64 %44, i64 %46), !dbg !1769
  %sub14 = sub nsw i64 %30, %call13, !dbg !1771
  store i64 %sub14, i64* %timeout2_ms, align 8, !dbg !1772
  %47 = load i64, i64* %timeout_ms, align 8, !dbg !1773
  %48 = load i64, i64* %timeout2_ms, align 8, !dbg !1773
  %cmp = icmp slt i64 %47, %48, !dbg !1773
  br i1 %cmp, label %cond.true15, label %cond.false16, !dbg !1773

cond.true15:                                      ; preds = %if.then
  %49 = load i64, i64* %timeout_ms, align 8, !dbg !1774
  br label %cond.end17, !dbg !1774

cond.false16:                                     ; preds = %if.then
  %50 = load i64, i64* %timeout2_ms, align 8, !dbg !1775
  br label %cond.end17, !dbg !1775

cond.end17:                                       ; preds = %cond.false16, %cond.true15
  %cond18 = phi i64 [ %49, %cond.true15 ], [ %50, %cond.false16 ], !dbg !1777
  store i64 %cond18, i64* %timeout_ms, align 8, !dbg !1779
  br label %if.end, !dbg !1780

if.end:                                           ; preds = %cond.end17, %cond.end
  %51 = load i64, i64* %timeout_ms, align 8, !dbg !1781
  ret i64 %51, !dbg !1782
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #2

declare { i64, i64 } @curlx_tvnow() #2

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_statemach(%struct.pingpong* %pp, i1 zeroext %block) #0 !dbg !1685 {
entry:
  %retval = alloca i32, align 4
  %pp.addr = alloca %struct.pingpong*, align 8
  %block.addr = alloca i8, align 1
  %conn = alloca %struct.connectdata*, align 8
  %sock = alloca i32, align 4
  %rc = alloca i32, align 4
  %interval_ms = alloca i64, align 8
  %timeout_ms = alloca i64, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %result = alloca i32, align 4
  %agg.tmp = alloca %struct.timeval, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !1783, metadata !1722), !dbg !1784
  %frombool = zext i1 %block to i8
  store i8 %frombool, i8* %block.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %block.addr, metadata !1785, metadata !1722), !dbg !1786
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !1787, metadata !1722), !dbg !1788
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1789
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !1790
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !1790
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !1788
  call void @llvm.dbg.declare(metadata i32* %sock, metadata !1791, metadata !1722), !dbg !1792
  %2 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1793
  %sock2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 33, !dbg !1794
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock2, i64 0, i64 0, !dbg !1793
  %3 = load i32, i32* %arrayidx, align 8, !dbg !1793
  store i32 %3, i32* %sock, align 4, !dbg !1792
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !1795, metadata !1722), !dbg !1796
  call void @llvm.dbg.declare(metadata i64* %interval_ms, metadata !1797, metadata !1722), !dbg !1798
  call void @llvm.dbg.declare(metadata i64* %timeout_ms, metadata !1799, metadata !1722), !dbg !1800
  %4 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1801
  %call = call i64 @Curl_pp_state_timeout(%struct.pingpong* %4), !dbg !1802
  store i64 %call, i64* %timeout_ms, align 8, !dbg !1800
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1803, metadata !1722), !dbg !1804
  %5 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1805
  %data3 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 0, !dbg !1806
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data3, align 8, !dbg !1806
  store %struct.Curl_easy* %6, %struct.Curl_easy** %data, align 8, !dbg !1804
  call void @llvm.dbg.declare(metadata i32* %result, metadata !1807, metadata !1722), !dbg !1808
  store i32 0, i32* %result, align 4, !dbg !1808
  %7 = load i64, i64* %timeout_ms, align 8, !dbg !1809
  %cmp = icmp sle i64 %7, 0, !dbg !1811
  br i1 %cmp, label %if.then, label %if.end, !dbg !1812

if.then:                                          ; preds = %entry
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1813
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %8, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str, i32 0, i32 0)), !dbg !1815
  store i32 28, i32* %retval, align 4, !dbg !1816
  br label %return, !dbg !1816

if.end:                                           ; preds = %entry
  %9 = load i8, i8* %block.addr, align 1, !dbg !1817
  %tobool = trunc i8 %9 to i1, !dbg !1817
  br i1 %tobool, label %if.then4, label %if.else, !dbg !1819

if.then4:                                         ; preds = %if.end
  store i64 1000, i64* %interval_ms, align 8, !dbg !1820
  %10 = load i64, i64* %timeout_ms, align 8, !dbg !1822
  %11 = load i64, i64* %interval_ms, align 8, !dbg !1824
  %cmp5 = icmp slt i64 %10, %11, !dbg !1825
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1826

if.then6:                                         ; preds = %if.then4
  %12 = load i64, i64* %timeout_ms, align 8, !dbg !1827
  store i64 %12, i64* %interval_ms, align 8, !dbg !1828
  br label %if.end7, !dbg !1829

if.end7:                                          ; preds = %if.then6, %if.then4
  br label %if.end8, !dbg !1830

if.else:                                          ; preds = %if.end
  store i64 0, i64* %interval_ms, align 8, !dbg !1831
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.end7
  %13 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1832
  %call9 = call zeroext i1 @Curl_pp_moredata(%struct.pingpong* %13), !dbg !1835
  br i1 %call9, label %if.then10, label %if.else11, !dbg !1836

if.then10:                                        ; preds = %if.end8
  store i32 1, i32* %rc, align 4, !dbg !1837
  br label %if.end25, !dbg !1838

if.else11:                                        ; preds = %if.end8
  %14 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1839
  %sendleft = getelementptr inbounds %struct.pingpong, %struct.pingpong* %14, i32 0, i32 6, !dbg !1841
  %15 = load i64, i64* %sendleft, align 8, !dbg !1841
  %tobool12 = icmp ne i64 %15, 0, !dbg !1839
  br i1 %tobool12, label %if.else14, label %land.lhs.true, !dbg !1842

land.lhs.true:                                    ; preds = %if.else11
  br i1 false, label %if.then13, label %if.else14, !dbg !1843

if.then13:                                        ; preds = %land.lhs.true
  store i32 1, i32* %rc, align 4, !dbg !1845
  br label %if.end24, !dbg !1846

if.else14:                                        ; preds = %land.lhs.true, %if.else11
  %16 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1847
  %sendleft15 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %16, i32 0, i32 6, !dbg !1848
  %17 = load i64, i64* %sendleft15, align 8, !dbg !1848
  %tobool16 = icmp ne i64 %17, 0, !dbg !1847
  br i1 %tobool16, label %cond.true, label %cond.false, !dbg !1847

cond.true:                                        ; preds = %if.else14
  br label %cond.end, !dbg !1849

cond.false:                                       ; preds = %if.else14
  %18 = load i32, i32* %sock, align 4, !dbg !1851
  br label %cond.end, !dbg !1853

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ -1, %cond.true ], [ %18, %cond.false ], !dbg !1854
  %19 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1856
  %sendleft17 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %19, i32 0, i32 6, !dbg !1857
  %20 = load i64, i64* %sendleft17, align 8, !dbg !1857
  %tobool18 = icmp ne i64 %20, 0, !dbg !1856
  br i1 %tobool18, label %cond.true19, label %cond.false20, !dbg !1856

cond.true19:                                      ; preds = %cond.end
  %21 = load i32, i32* %sock, align 4, !dbg !1858
  br label %cond.end21, !dbg !1859

cond.false20:                                     ; preds = %cond.end
  br label %cond.end21, !dbg !1860

cond.end21:                                       ; preds = %cond.false20, %cond.true19
  %cond22 = phi i32 [ %21, %cond.true19 ], [ -1, %cond.false20 ], !dbg !1861
  %22 = load i64, i64* %interval_ms, align 8, !dbg !1862
  %call23 = call i32 @Curl_socket_check(i32 %cond, i32 -1, i32 %cond22, i64 %22), !dbg !1863
  store i32 %call23, i32* %rc, align 4, !dbg !1865
  br label %if.end24

if.end24:                                         ; preds = %cond.end21, %if.then13
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %if.then10
  %23 = load i8, i8* %block.addr, align 1, !dbg !1866
  %tobool26 = trunc i8 %23 to i1, !dbg !1866
  br i1 %tobool26, label %if.then27, label %if.end38, !dbg !1868

if.then27:                                        ; preds = %if.end25
  %24 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1869
  %call28 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %24), !dbg !1872
  %tobool29 = icmp ne i32 %call28, 0, !dbg !1872
  br i1 %tobool29, label %if.then30, label %if.else31, !dbg !1873

if.then30:                                        ; preds = %if.then27
  store i32 42, i32* %result, align 4, !dbg !1874
  br label %if.end34, !dbg !1875

if.else31:                                        ; preds = %if.then27
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1876
  %call32 = call { i64, i64 } @curlx_tvnow(), !dbg !1877
  %26 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !1877
  %27 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %26, i32 0, i32 0, !dbg !1877
  %28 = extractvalue { i64, i64 } %call32, 0, !dbg !1877
  store i64 %28, i64* %27, align 8, !dbg !1877
  %29 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %26, i32 0, i32 1, !dbg !1877
  %30 = extractvalue { i64, i64 } %call32, 1, !dbg !1877
  store i64 %30, i64* %29, align 8, !dbg !1877
  %31 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !1878
  %32 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 0, !dbg !1878
  %33 = load i64, i64* %32, align 8, !dbg !1878
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 1, !dbg !1878
  %35 = load i64, i64* %34, align 8, !dbg !1878
  %call33 = call i32 @Curl_speedcheck(%struct.Curl_easy* %25, i64 %33, i64 %35), !dbg !1879
  store i32 %call33, i32* %result, align 4, !dbg !1881
  br label %if.end34

if.end34:                                         ; preds = %if.else31, %if.then30
  %36 = load i32, i32* %result, align 4, !dbg !1882
  %tobool35 = icmp ne i32 %36, 0, !dbg !1882
  br i1 %tobool35, label %if.then36, label %if.end37, !dbg !1884

if.then36:                                        ; preds = %if.end34
  %37 = load i32, i32* %result, align 4, !dbg !1885
  store i32 %37, i32* %retval, align 4, !dbg !1886
  br label %return, !dbg !1886

if.end37:                                         ; preds = %if.end34
  br label %if.end38, !dbg !1887

if.end38:                                         ; preds = %if.end37, %if.end25
  %38 = load i32, i32* %rc, align 4, !dbg !1888
  %cmp39 = icmp eq i32 %38, -1, !dbg !1890
  br i1 %cmp39, label %if.then40, label %if.else41, !dbg !1891

if.then40:                                        ; preds = %if.end38
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1892
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %39, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.1, i32 0, i32 0)), !dbg !1894
  store i32 27, i32* %result, align 4, !dbg !1895
  br label %if.end46, !dbg !1896

if.else41:                                        ; preds = %if.end38
  %40 = load i32, i32* %rc, align 4, !dbg !1897
  %tobool42 = icmp ne i32 %40, 0, !dbg !1897
  br i1 %tobool42, label %if.then43, label %if.end45, !dbg !1899

if.then43:                                        ; preds = %if.else41
  %41 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1900
  %statemach_act = getelementptr inbounds %struct.pingpong, %struct.pingpong* %41, i32 0, i32 11, !dbg !1901
  %42 = load i32 (%struct.connectdata*)*, i32 (%struct.connectdata*)** %statemach_act, align 8, !dbg !1901
  %43 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1902
  %call44 = call i32 %42(%struct.connectdata* %43), !dbg !1900
  store i32 %call44, i32* %result, align 4, !dbg !1903
  br label %if.end45, !dbg !1904

if.end45:                                         ; preds = %if.then43, %if.else41
  br label %if.end46

if.end46:                                         ; preds = %if.end45, %if.then40
  %44 = load i32, i32* %result, align 4, !dbg !1905
  store i32 %44, i32* %retval, align 4, !dbg !1906
  br label %return, !dbg !1906

return:                                           ; preds = %if.end46, %if.then36, %if.then
  %45 = load i32, i32* %retval, align 4, !dbg !1907
  ret i32 %45, !dbg !1907
}

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_pp_moredata(%struct.pingpong* %pp) #0 !dbg !1715 {
entry:
  %pp.addr = alloca %struct.pingpong*, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !1908, metadata !1722), !dbg !1909
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1910
  %sendleft = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 6, !dbg !1911
  %1 = load i64, i64* %sendleft, align 8, !dbg !1911
  %tobool = icmp ne i64 %1, 0, !dbg !1910
  br i1 %tobool, label %land.end, label %land.lhs.true, !dbg !1912

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1913
  %cache = getelementptr inbounds %struct.pingpong, %struct.pingpong* %2, i32 0, i32 0, !dbg !1915
  %3 = load i8*, i8** %cache, align 8, !dbg !1915
  %tobool1 = icmp ne i8* %3, null, !dbg !1913
  br i1 %tobool1, label %land.rhs, label %land.end, !dbg !1916

land.rhs:                                         ; preds = %land.lhs.true
  %4 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1917
  %nread_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %4, i32 0, i32 2, !dbg !1919
  %5 = load i64, i64* %nread_resp, align 8, !dbg !1919
  %6 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1920
  %cache_size = getelementptr inbounds %struct.pingpong, %struct.pingpong* %6, i32 0, i32 1, !dbg !1921
  %7 = load i64, i64* %cache_size, align 8, !dbg !1921
  %cmp = icmp ult i64 %5, %7, !dbg !1922
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %entry
  %8 = phi i1 [ false, %land.lhs.true ], [ false, %entry ], [ %cmp, %land.rhs ]
  %cond = select i1 %8, i32 1, i32 0, !dbg !1923
  %tobool2 = icmp ne i32 %cond, 0, !dbg !1923
  ret i1 %tobool2, !dbg !1925
}

declare i32 @Curl_socket_check(i32, i32, i32, i64) #2

declare i32 @Curl_pgrsUpdate(%struct.connectdata*) #2

declare i32 @Curl_speedcheck(%struct.Curl_easy*, i64, i64) #2

; Function Attrs: nounwind uwtable
define void @Curl_pp_init(%struct.pingpong* %pp) #0 !dbg !1688 {
entry:
  %pp.addr = alloca %struct.pingpong*, align 8
  %conn = alloca %struct.connectdata*, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !1926, metadata !1722), !dbg !1927
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !1928, metadata !1722), !dbg !1929
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1930
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !1931
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !1931
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !1929
  %2 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1932
  %nread_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %2, i32 0, i32 2, !dbg !1933
  store i64 0, i64* %nread_resp, align 8, !dbg !1934
  %3 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1935
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 0, !dbg !1936
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1936
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 17, !dbg !1937
  %buffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 6, !dbg !1938
  %5 = load i8*, i8** %buffer, align 8, !dbg !1938
  %6 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1939
  %linestart_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %6, i32 0, i32 3, !dbg !1940
  store i8* %5, i8** %linestart_resp, align 8, !dbg !1941
  %7 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1942
  %pending_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %7, i32 0, i32 4, !dbg !1943
  store i8 1, i8* %pending_resp, align 8, !dbg !1944
  %8 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1945
  %response = getelementptr inbounds %struct.pingpong, %struct.pingpong* %8, i32 0, i32 8, !dbg !1946
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !1947
  %9 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !1947
  %10 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %9, i32 0, i32 0, !dbg !1947
  %11 = extractvalue { i64, i64 } %call, 0, !dbg !1947
  store i64 %11, i64* %10, align 8, !dbg !1947
  %12 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %9, i32 0, i32 1, !dbg !1947
  %13 = extractvalue { i64, i64 } %call, 1, !dbg !1947
  store i64 %13, i64* %12, align 8, !dbg !1947
  %14 = bitcast %struct.timeval* %response to i8*, !dbg !1947
  %15 = bitcast %struct.timeval* %coerce to i8*, !dbg !1947
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* %15, i64 16, i32 8, i1 false), !dbg !1948
  ret void, !dbg !1950
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_vsendf(%struct.pingpong* %pp, i8* %fmt, %struct.__va_list_tag* %args) #0 !dbg !1691 {
entry:
  %retval = alloca i32, align 4
  %pp.addr = alloca %struct.pingpong*, align 8
  %fmt.addr = alloca i8*, align 8
  %args.addr = alloca %struct.__va_list_tag*, align 8
  %bytes_written = alloca i64, align 8
  %write_len = alloca i64, align 8
  %fmt_crlf = alloca i8*, align 8
  %s = alloca i8*, align 8
  %result = alloca i32, align 4
  %conn = alloca %struct.connectdata*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !1951, metadata !1722), !dbg !1952
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !1953, metadata !1722), !dbg !1954
  store %struct.__va_list_tag* %args, %struct.__va_list_tag** %args.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %args.addr, metadata !1955, metadata !1722), !dbg !1956
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !1957, metadata !1722), !dbg !1958
  call void @llvm.dbg.declare(metadata i64* %write_len, metadata !1959, metadata !1722), !dbg !1960
  call void @llvm.dbg.declare(metadata i8** %fmt_crlf, metadata !1961, metadata !1722), !dbg !1962
  call void @llvm.dbg.declare(metadata i8** %s, metadata !1963, metadata !1722), !dbg !1964
  call void @llvm.dbg.declare(metadata i32* %result, metadata !1965, metadata !1722), !dbg !1966
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !1967, metadata !1722), !dbg !1968
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !1969
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !1970
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !1970
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !1968
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1971, metadata !1722), !dbg !1972
  %2 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !1973
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 0, !dbg !1974
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !1974
  store %struct.Curl_easy* %3, %struct.Curl_easy** %data, align 8, !dbg !1972
  br label %do.body, !dbg !1975

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !1976

do.end:                                           ; preds = %do.body
  br label %do.body3, !dbg !1979

do.body3:                                         ; preds = %do.end
  br label %do.end4, !dbg !1980

do.end4:                                          ; preds = %do.body3
  br label %do.body5, !dbg !1983

do.body5:                                         ; preds = %do.end4
  br label %do.end6, !dbg !1984

do.end6:                                          ; preds = %do.body5
  %4 = load i8*, i8** %fmt.addr, align 8, !dbg !1987
  %call = call i8* (i8*, ...) @curl_maprintf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* %4), !dbg !1988
  store i8* %call, i8** %fmt_crlf, align 8, !dbg !1989
  %5 = load i8*, i8** %fmt_crlf, align 8, !dbg !1990
  %tobool = icmp ne i8* %5, null, !dbg !1990
  br i1 %tobool, label %if.end, label %if.then, !dbg !1992

if.then:                                          ; preds = %do.end6
  store i32 27, i32* %retval, align 4, !dbg !1993
  br label %return, !dbg !1993

if.end:                                           ; preds = %do.end6
  %6 = load i8*, i8** %fmt_crlf, align 8, !dbg !1994
  %7 = load %struct.__va_list_tag*, %struct.__va_list_tag** %args.addr, align 8, !dbg !1995
  %call7 = call i8* @curl_mvaprintf(i8* %6, %struct.__va_list_tag* %7), !dbg !1996
  store i8* %call7, i8** %s, align 8, !dbg !1997
  %8 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1998
  %9 = load i8*, i8** %fmt_crlf, align 8, !dbg !1998
  call void %8(i8* %9), !dbg !1998
  %10 = load i8*, i8** %s, align 8, !dbg !1999
  %tobool8 = icmp ne i8* %10, null, !dbg !1999
  br i1 %tobool8, label %if.end10, label %if.then9, !dbg !2001

if.then9:                                         ; preds = %if.end
  store i32 27, i32* %retval, align 4, !dbg !2002
  br label %return, !dbg !2002

if.end10:                                         ; preds = %if.end
  store i64 0, i64* %bytes_written, align 8, !dbg !2003
  %11 = load i8*, i8** %s, align 8, !dbg !2004
  %call11 = call i64 @strlen(i8* %11) #6, !dbg !2005
  store i64 %call11, i64* %write_len, align 8, !dbg !2006
  %12 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2007
  call void @Curl_pp_init(%struct.pingpong* %12), !dbg !2008
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2009
  store i32 0, i32* %result, align 4, !dbg !2010
  %14 = load i32, i32* %result, align 4, !dbg !2011
  %tobool12 = icmp ne i32 %14, 0, !dbg !2011
  br i1 %tobool12, label %if.then13, label %if.end14, !dbg !2013

if.then13:                                        ; preds = %if.end10
  %15 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2014
  %16 = load i8*, i8** %s, align 8, !dbg !2014
  call void %15(i8* %16), !dbg !2014
  %17 = load i32, i32* %result, align 4, !dbg !2016
  store i32 %17, i32* %retval, align 4, !dbg !2017
  br label %return, !dbg !2017

if.end14:                                         ; preds = %if.end10
  %18 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2018
  %19 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2019
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %19, i32 0, i32 33, !dbg !2020
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 0, !dbg !2019
  %20 = load i32, i32* %arrayidx, align 8, !dbg !2019
  %21 = load i8*, i8** %s, align 8, !dbg !2021
  %22 = load i64, i64* %write_len, align 8, !dbg !2022
  %call15 = call i32 @Curl_write(%struct.connectdata* %18, i32 %20, i8* %21, i64 %22, i64* %bytes_written), !dbg !2023
  store i32 %call15, i32* %result, align 4, !dbg !2024
  %23 = load i32, i32* %result, align 4, !dbg !2025
  %tobool16 = icmp ne i32 %23, 0, !dbg !2025
  br i1 %tobool16, label %if.then17, label %if.end18, !dbg !2027

if.then17:                                        ; preds = %if.end14
  %24 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2028
  %25 = load i8*, i8** %s, align 8, !dbg !2028
  call void %24(i8* %25), !dbg !2028
  %26 = load i32, i32* %result, align 4, !dbg !2030
  store i32 %26, i32* %retval, align 4, !dbg !2031
  br label %return, !dbg !2031

if.end18:                                         ; preds = %if.end14
  %27 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2032
  %data19 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %27, i32 0, i32 0, !dbg !2034
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data19, align 8, !dbg !2034
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 13, !dbg !2035
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 106, !dbg !2036
  %29 = load i8, i8* %verbose, align 8, !dbg !2036
  %tobool20 = trunc i8 %29 to i1, !dbg !2036
  br i1 %tobool20, label %if.then21, label %if.end24, !dbg !2037

if.then21:                                        ; preds = %if.end18
  %30 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2038
  %data22 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %30, i32 0, i32 0, !dbg !2039
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data22, align 8, !dbg !2039
  %32 = load i8*, i8** %s, align 8, !dbg !2040
  %33 = load i64, i64* %bytes_written, align 8, !dbg !2041
  %34 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2042
  %call23 = call i32 @Curl_debug(%struct.Curl_easy* %31, i32 2, i8* %32, i64 %33, %struct.connectdata* %34), !dbg !2043
  br label %if.end24, !dbg !2043

if.end24:                                         ; preds = %if.then21, %if.end18
  %35 = load i64, i64* %bytes_written, align 8, !dbg !2044
  %36 = load i64, i64* %write_len, align 8, !dbg !2046
  %cmp = icmp ne i64 %35, %36, !dbg !2047
  br i1 %cmp, label %if.then25, label %if.else, !dbg !2048

if.then25:                                        ; preds = %if.end24
  %37 = load i8*, i8** %s, align 8, !dbg !2049
  %38 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2051
  %sendthis = getelementptr inbounds %struct.pingpong, %struct.pingpong* %38, i32 0, i32 5, !dbg !2052
  store i8* %37, i8** %sendthis, align 8, !dbg !2053
  %39 = load i64, i64* %write_len, align 8, !dbg !2054
  %40 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2055
  %sendsize = getelementptr inbounds %struct.pingpong, %struct.pingpong* %40, i32 0, i32 7, !dbg !2056
  store i64 %39, i64* %sendsize, align 8, !dbg !2057
  %41 = load i64, i64* %write_len, align 8, !dbg !2058
  %42 = load i64, i64* %bytes_written, align 8, !dbg !2059
  %sub = sub i64 %41, %42, !dbg !2060
  %43 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2061
  %sendleft = getelementptr inbounds %struct.pingpong, %struct.pingpong* %43, i32 0, i32 6, !dbg !2062
  store i64 %sub, i64* %sendleft, align 8, !dbg !2063
  br label %if.end30, !dbg !2064

if.else:                                          ; preds = %if.end24
  %44 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2065
  %45 = load i8*, i8** %s, align 8, !dbg !2065
  call void %44(i8* %45), !dbg !2065
  %46 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2067
  %sendthis26 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %46, i32 0, i32 5, !dbg !2068
  store i8* null, i8** %sendthis26, align 8, !dbg !2069
  %47 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2070
  %sendsize27 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %47, i32 0, i32 7, !dbg !2071
  store i64 0, i64* %sendsize27, align 8, !dbg !2072
  %48 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2073
  %sendleft28 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %48, i32 0, i32 6, !dbg !2074
  store i64 0, i64* %sendleft28, align 8, !dbg !2075
  %49 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2076
  %response = getelementptr inbounds %struct.pingpong, %struct.pingpong* %49, i32 0, i32 8, !dbg !2077
  %call29 = call { i64, i64 } @curlx_tvnow(), !dbg !2078
  %50 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2078
  %51 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %50, i32 0, i32 0, !dbg !2078
  %52 = extractvalue { i64, i64 } %call29, 0, !dbg !2078
  store i64 %52, i64* %51, align 8, !dbg !2078
  %53 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %50, i32 0, i32 1, !dbg !2078
  %54 = extractvalue { i64, i64 } %call29, 1, !dbg !2078
  store i64 %54, i64* %53, align 8, !dbg !2078
  %55 = bitcast %struct.timeval* %response to i8*, !dbg !2078
  %56 = bitcast %struct.timeval* %coerce to i8*, !dbg !2078
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %55, i8* %56, i64 16, i32 8, i1 false), !dbg !2079
  br label %if.end30

if.end30:                                         ; preds = %if.else, %if.then25
  store i32 0, i32* %retval, align 4, !dbg !2081
  br label %return, !dbg !2081

return:                                           ; preds = %if.end30, %if.then17, %if.then13, %if.then9, %if.then
  %57 = load i32, i32* %retval, align 4, !dbg !2082
  ret i32 %57, !dbg !2082
}

declare i8* @curl_maprintf(i8*, ...) #2

declare i8* @curl_mvaprintf(i8*, %struct.__va_list_tag*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @Curl_write(%struct.connectdata*, i32, i8*, i64, i64*) #2

declare i32 @Curl_debug(%struct.Curl_easy*, i32, i8*, i64, %struct.connectdata*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_sendf(%struct.pingpong* %pp, i8* %fmt, ...) #0 !dbg !1701 {
entry:
  %pp.addr = alloca %struct.pingpong*, align 8
  %fmt.addr = alloca i8*, align 8
  %result = alloca i32, align 4
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !2083, metadata !1722), !dbg !2084
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !2085, metadata !1722), !dbg !2086
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2087, metadata !1722), !dbg !2088
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap, metadata !2089, metadata !1722), !dbg !2095
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !2096
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !2096
  call void @llvm.va_start(i8* %arraydecay1), !dbg !2096
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2097
  %1 = load i8*, i8** %fmt.addr, align 8, !dbg !2098
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !2099
  %call = call i32 @Curl_pp_vsendf(%struct.pingpong* %0, i8* %1, %struct.__va_list_tag* %arraydecay2), !dbg !2100
  store i32 %call, i32* %result, align 4, !dbg !2101
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !2102
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !2102
  call void @llvm.va_end(i8* %arraydecay34), !dbg !2102
  %2 = load i32, i32* %result, align 4, !dbg !2103
  ret i32 %2, !dbg !2104
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #5

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #5

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_readresp(i32 %sockfd, %struct.pingpong* %pp, i32* %code, i64* %size) #0 !dbg !1704 {
entry:
  %retval = alloca i32, align 4
  %sockfd.addr = alloca i32, align 4
  %pp.addr = alloca %struct.pingpong*, align 8
  %code.addr = alloca i32*, align 8
  %size.addr = alloca i64*, align 8
  %perline = alloca i64, align 8
  %keepon = alloca i8, align 1
  %gotbytes = alloca i64, align 8
  %ptr = alloca i8*, align 8
  %conn = alloca %struct.connectdata*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %buf = alloca i8*, align 8
  %result = alloca i32, align 4
  %i = alloca i64, align 8
  %clipamount = alloca i64, align 8
  %restart = alloca i8, align 1
  %n = alloca i64, align 8
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2105, metadata !1722), !dbg !2106
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !2107, metadata !1722), !dbg !2108
  store i32* %code, i32** %code.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %code.addr, metadata !2109, metadata !1722), !dbg !2110
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !2111, metadata !1722), !dbg !2112
  call void @llvm.dbg.declare(metadata i64* %perline, metadata !2113, metadata !1722), !dbg !2114
  call void @llvm.dbg.declare(metadata i8* %keepon, metadata !2115, metadata !1722), !dbg !2116
  store i8 1, i8* %keepon, align 1, !dbg !2116
  call void @llvm.dbg.declare(metadata i64* %gotbytes, metadata !2117, metadata !1722), !dbg !2118
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !2119, metadata !1722), !dbg !2120
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !2121, metadata !1722), !dbg !2122
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2123
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !2124
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !2124
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !2122
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2125, metadata !1722), !dbg !2126
  %2 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2127
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 0, !dbg !2128
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !2128
  store %struct.Curl_easy* %3, %struct.Curl_easy** %data, align 8, !dbg !2126
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !2129, metadata !1722), !dbg !2131
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2132
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 17, !dbg !2133
  %buffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 6, !dbg !2134
  %5 = load i8*, i8** %buffer, align 8, !dbg !2134
  store i8* %5, i8** %buf, align 8, !dbg !2131
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2135, metadata !1722), !dbg !2136
  store i32 0, i32* %result, align 4, !dbg !2136
  %6 = load i32*, i32** %code.addr, align 8, !dbg !2137
  store i32 0, i32* %6, align 4, !dbg !2138
  %7 = load i64*, i64** %size.addr, align 8, !dbg !2139
  store i64 0, i64* %7, align 8, !dbg !2140
  %8 = load i8*, i8** %buf, align 8, !dbg !2141
  %9 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2142
  %nread_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %9, i32 0, i32 2, !dbg !2143
  %10 = load i64, i64* %nread_resp, align 8, !dbg !2143
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 %10, !dbg !2144
  store i8* %add.ptr, i8** %ptr, align 8, !dbg !2145
  %11 = load i8*, i8** %ptr, align 8, !dbg !2146
  %12 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2147
  %linestart_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %12, i32 0, i32 3, !dbg !2148
  %13 = load i8*, i8** %linestart_resp, align 8, !dbg !2148
  %sub.ptr.lhs.cast = ptrtoint i8* %11 to i64, !dbg !2149
  %sub.ptr.rhs.cast = ptrtoint i8* %13 to i64, !dbg !2149
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2149
  store i64 %sub.ptr.sub, i64* %perline, align 8, !dbg !2150
  br label %while.cond, !dbg !2151

while.cond:                                       ; preds = %if.end118, %entry
  %14 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2152
  %nread_resp3 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %14, i32 0, i32 2, !dbg !2154
  %15 = load i64, i64* %nread_resp3, align 8, !dbg !2154
  %cmp = icmp ult i64 %15, 16384, !dbg !2155
  br i1 %cmp, label %land.rhs, label %land.end6, !dbg !2156

land.rhs:                                         ; preds = %while.cond
  %16 = load i8, i8* %keepon, align 1, !dbg !2157
  %tobool = trunc i8 %16 to i1, !dbg !2157
  br i1 %tobool, label %land.rhs4, label %land.end, !dbg !2159

land.rhs4:                                        ; preds = %land.rhs
  %17 = load i32, i32* %result, align 4, !dbg !2160
  %tobool5 = icmp ne i32 %17, 0, !dbg !2162
  %lnot = xor i1 %tobool5, true, !dbg !2162
  br label %land.end

land.end:                                         ; preds = %land.rhs4, %land.rhs
  %18 = phi i1 [ false, %land.rhs ], [ %lnot, %land.rhs4 ]
  br label %land.end6

land.end6:                                        ; preds = %land.end, %while.cond
  %19 = phi i1 [ false, %while.cond ], [ %18, %land.end ]
  br i1 %19, label %while.body, label %while.end, !dbg !2163

while.body:                                       ; preds = %land.end6
  %20 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2165
  %cache = getelementptr inbounds %struct.pingpong, %struct.pingpong* %20, i32 0, i32 0, !dbg !2168
  %21 = load i8*, i8** %cache, align 8, !dbg !2168
  %tobool7 = icmp ne i8* %21, null, !dbg !2165
  br i1 %tobool7, label %if.then, label %if.else, !dbg !2169

if.then:                                          ; preds = %while.body
  br label %do.body, !dbg !2170

do.body:                                          ; preds = %if.then
  br label %do.end, !dbg !2172

do.end:                                           ; preds = %do.body
  %22 = load i8*, i8** %ptr, align 8, !dbg !2175
  %23 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2176
  %cache8 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %23, i32 0, i32 0, !dbg !2177
  %24 = load i8*, i8** %cache8, align 8, !dbg !2177
  %25 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2178
  %cache_size = getelementptr inbounds %struct.pingpong, %struct.pingpong* %25, i32 0, i32 1, !dbg !2179
  %26 = load i64, i64* %cache_size, align 8, !dbg !2179
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %22, i8* %24, i64 %26, i32 1, i1 false), !dbg !2180
  %27 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2181
  %cache_size9 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %27, i32 0, i32 1, !dbg !2182
  %28 = load i64, i64* %cache_size9, align 8, !dbg !2182
  store i64 %28, i64* %gotbytes, align 8, !dbg !2183
  %29 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2184
  %30 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2184
  %cache10 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %30, i32 0, i32 0, !dbg !2184
  %31 = load i8*, i8** %cache10, align 8, !dbg !2184
  call void %29(i8* %31), !dbg !2184
  %32 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2185
  %cache11 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %32, i32 0, i32 0, !dbg !2186
  store i8* null, i8** %cache11, align 8, !dbg !2187
  %33 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2188
  %cache_size12 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %33, i32 0, i32 1, !dbg !2189
  store i64 0, i64* %cache_size12, align 8, !dbg !2190
  br label %if.end25, !dbg !2191

if.else:                                          ; preds = %while.body
  br label %do.body13, !dbg !2192

do.body13:                                        ; preds = %if.else
  br label %do.end14, !dbg !2194

do.end14:                                         ; preds = %do.body13
  %34 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2197
  %35 = load i32, i32* %sockfd.addr, align 4, !dbg !2198
  %36 = load i8*, i8** %ptr, align 8, !dbg !2199
  %37 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2200
  %nread_resp15 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %37, i32 0, i32 2, !dbg !2201
  %38 = load i64, i64* %nread_resp15, align 8, !dbg !2201
  %sub = sub i64 16384, %38, !dbg !2202
  %call = call i32 @Curl_read(%struct.connectdata* %34, i32 %35, i8* %36, i64 %sub, i64* %gotbytes), !dbg !2203
  store i32 %call, i32* %result, align 4, !dbg !2204
  %39 = load i32, i32* %result, align 4, !dbg !2205
  %cmp16 = icmp eq i32 %39, 81, !dbg !2207
  br i1 %cmp16, label %if.then17, label %if.end, !dbg !2208

if.then17:                                        ; preds = %do.end14
  store i32 0, i32* %retval, align 4, !dbg !2209
  br label %return, !dbg !2209

if.end:                                           ; preds = %do.end14
  %40 = load i32, i32* %result, align 4, !dbg !2210
  %tobool18 = icmp ne i32 %40, 0, !dbg !2210
  br i1 %tobool18, label %if.end21, label %land.lhs.true, !dbg !2212

land.lhs.true:                                    ; preds = %if.end
  %41 = load i64, i64* %gotbytes, align 8, !dbg !2213
  %cmp19 = icmp sgt i64 %41, 0, !dbg !2215
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !2216

if.then20:                                        ; preds = %land.lhs.true
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2217
  store i32 0, i32* %result, align 4, !dbg !2218
  br label %if.end21, !dbg !2219

if.end21:                                         ; preds = %if.then20, %land.lhs.true, %if.end
  %43 = load i32, i32* %result, align 4, !dbg !2220
  %tobool22 = icmp ne i32 %43, 0, !dbg !2220
  br i1 %tobool22, label %if.then23, label %if.end24, !dbg !2222

if.then23:                                        ; preds = %if.end21
  store i8 0, i8* %keepon, align 1, !dbg !2223
  br label %if.end24, !dbg !2224

if.end24:                                         ; preds = %if.then23, %if.end21
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %do.end
  %44 = load i8, i8* %keepon, align 1, !dbg !2225
  %tobool26 = trunc i8 %44 to i1, !dbg !2225
  br i1 %tobool26, label %if.else28, label %if.then27, !dbg !2227

if.then27:                                        ; preds = %if.end25
  br label %if.end118, !dbg !2228

if.else28:                                        ; preds = %if.end25
  %45 = load i64, i64* %gotbytes, align 8, !dbg !2230
  %cmp29 = icmp sle i64 %45, 0, !dbg !2232
  br i1 %cmp29, label %if.then30, label %if.else31, !dbg !2233

if.then30:                                        ; preds = %if.else28
  store i8 0, i8* %keepon, align 1, !dbg !2234
  store i32 56, i32* %result, align 4, !dbg !2236
  %46 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2237
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %46, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !2238
  br label %if.end117, !dbg !2239

if.else31:                                        ; preds = %if.else28
  call void @llvm.dbg.declare(metadata i64* %i, metadata !2240, metadata !1722), !dbg !2242
  call void @llvm.dbg.declare(metadata i64* %clipamount, metadata !2243, metadata !1722), !dbg !2244
  store i64 0, i64* %clipamount, align 8, !dbg !2244
  call void @llvm.dbg.declare(metadata i8* %restart, metadata !2245, metadata !1722), !dbg !2246
  store i8 0, i8* %restart, align 1, !dbg !2246
  %47 = load i64, i64* %gotbytes, align 8, !dbg !2247
  %48 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2248
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %48, i32 0, i32 12, !dbg !2249
  %headerbytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 6, !dbg !2250
  %49 = load i64, i64* %headerbytecount, align 8, !dbg !2251
  %add = add nsw i64 %49, %47, !dbg !2251
  store i64 %add, i64* %headerbytecount, align 8, !dbg !2251
  %50 = load i64, i64* %gotbytes, align 8, !dbg !2252
  %51 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2253
  %nread_resp32 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %51, i32 0, i32 2, !dbg !2254
  %52 = load i64, i64* %nread_resp32, align 8, !dbg !2255
  %add33 = add i64 %52, %50, !dbg !2255
  store i64 %add33, i64* %nread_resp32, align 8, !dbg !2255
  store i64 0, i64* %i, align 8, !dbg !2256
  br label %for.cond, !dbg !2258

for.cond:                                         ; preds = %for.inc, %if.else31
  %53 = load i64, i64* %i, align 8, !dbg !2259
  %54 = load i64, i64* %gotbytes, align 8, !dbg !2262
  %cmp34 = icmp slt i64 %53, %54, !dbg !2263
  br i1 %cmp34, label %for.body, label %for.end, !dbg !2264

for.body:                                         ; preds = %for.cond
  %55 = load i64, i64* %perline, align 8, !dbg !2265
  %inc = add nsw i64 %55, 1, !dbg !2265
  store i64 %inc, i64* %perline, align 8, !dbg !2265
  %56 = load i8*, i8** %ptr, align 8, !dbg !2267
  %57 = load i8, i8* %56, align 1, !dbg !2269
  %conv = sext i8 %57 to i32, !dbg !2269
  %cmp35 = icmp eq i32 %conv, 10, !dbg !2270
  br i1 %cmp35, label %if.then37, label %if.end64, !dbg !2271

if.then37:                                        ; preds = %for.body
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2272
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %58, i32 0, i32 13, !dbg !2275
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 106, !dbg !2276
  %59 = load i8, i8* %verbose, align 8, !dbg !2276
  %tobool38 = trunc i8 %59 to i1, !dbg !2276
  br i1 %tobool38, label %if.then39, label %if.end42, !dbg !2277

if.then39:                                        ; preds = %if.then37
  %60 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2278
  %61 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2279
  %linestart_resp40 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %61, i32 0, i32 3, !dbg !2280
  %62 = load i8*, i8** %linestart_resp40, align 8, !dbg !2280
  %63 = load i64, i64* %perline, align 8, !dbg !2281
  %64 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2282
  %call41 = call i32 @Curl_debug(%struct.Curl_easy* %60, i32 1, i8* %62, i64 %63, %struct.connectdata* %64), !dbg !2283
  br label %if.end42, !dbg !2283

if.end42:                                         ; preds = %if.then39, %if.then37
  %65 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2284
  %66 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2285
  %linestart_resp43 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %66, i32 0, i32 3, !dbg !2286
  %67 = load i8*, i8** %linestart_resp43, align 8, !dbg !2286
  %68 = load i64, i64* %perline, align 8, !dbg !2287
  %call44 = call i32 @Curl_client_write(%struct.connectdata* %65, i32 2, i8* %67, i64 %68), !dbg !2288
  store i32 %call44, i32* %result, align 4, !dbg !2289
  %69 = load i32, i32* %result, align 4, !dbg !2290
  %tobool45 = icmp ne i32 %69, 0, !dbg !2290
  br i1 %tobool45, label %if.then46, label %if.end47, !dbg !2292

if.then46:                                        ; preds = %if.end42
  %70 = load i32, i32* %result, align 4, !dbg !2293
  store i32 %70, i32* %retval, align 4, !dbg !2294
  br label %return, !dbg !2294

if.end47:                                         ; preds = %if.end42
  %71 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2295
  %endofresp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %71, i32 0, i32 12, !dbg !2297
  %72 = load i1 (%struct.connectdata*, i8*, i64, i32*)*, i1 (%struct.connectdata*, i8*, i64, i32*)** %endofresp, align 8, !dbg !2297
  %73 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2298
  %74 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2299
  %linestart_resp48 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %74, i32 0, i32 3, !dbg !2300
  %75 = load i8*, i8** %linestart_resp48, align 8, !dbg !2300
  %76 = load i64, i64* %perline, align 8, !dbg !2301
  %77 = load i32*, i32** %code.addr, align 8, !dbg !2302
  %call49 = call zeroext i1 %72(%struct.connectdata* %73, i8* %75, i64 %76, i32* %77), !dbg !2295
  br i1 %call49, label %if.then50, label %if.end61, !dbg !2303

if.then50:                                        ; preds = %if.end47
  call void @llvm.dbg.declare(metadata i64* %n, metadata !2304, metadata !1722), !dbg !2306
  %78 = load i8*, i8** %ptr, align 8, !dbg !2307
  %79 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2308
  %linestart_resp51 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %79, i32 0, i32 3, !dbg !2309
  %80 = load i8*, i8** %linestart_resp51, align 8, !dbg !2309
  %sub.ptr.lhs.cast52 = ptrtoint i8* %78 to i64, !dbg !2310
  %sub.ptr.rhs.cast53 = ptrtoint i8* %80 to i64, !dbg !2310
  %sub.ptr.sub54 = sub i64 %sub.ptr.lhs.cast52, %sub.ptr.rhs.cast53, !dbg !2310
  store i64 %sub.ptr.sub54, i64* %n, align 8, !dbg !2306
  %81 = load i8*, i8** %buf, align 8, !dbg !2311
  %82 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2312
  %linestart_resp55 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %82, i32 0, i32 3, !dbg !2313
  %83 = load i8*, i8** %linestart_resp55, align 8, !dbg !2313
  %84 = load i64, i64* %n, align 8, !dbg !2314
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %81, i8* %83, i64 %84, i32 1, i1 false), !dbg !2315
  %85 = load i64, i64* %n, align 8, !dbg !2316
  %86 = load i8*, i8** %buf, align 8, !dbg !2317
  %arrayidx = getelementptr inbounds i8, i8* %86, i64 %85, !dbg !2317
  store i8 0, i8* %arrayidx, align 1, !dbg !2318
  store i8 0, i8* %keepon, align 1, !dbg !2319
  %87 = load i8*, i8** %ptr, align 8, !dbg !2320
  %add.ptr56 = getelementptr inbounds i8, i8* %87, i64 1, !dbg !2321
  %88 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2322
  %linestart_resp57 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %88, i32 0, i32 3, !dbg !2323
  store i8* %add.ptr56, i8** %linestart_resp57, align 8, !dbg !2324
  %89 = load i64, i64* %i, align 8, !dbg !2325
  %inc58 = add nsw i64 %89, 1, !dbg !2325
  store i64 %inc58, i64* %i, align 8, !dbg !2325
  %90 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2326
  %nread_resp59 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %90, i32 0, i32 2, !dbg !2327
  %91 = load i64, i64* %nread_resp59, align 8, !dbg !2327
  %92 = load i64*, i64** %size.addr, align 8, !dbg !2328
  store i64 %91, i64* %92, align 8, !dbg !2329
  %93 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2330
  %nread_resp60 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %93, i32 0, i32 2, !dbg !2331
  store i64 0, i64* %nread_resp60, align 8, !dbg !2332
  br label %for.end, !dbg !2333

if.end61:                                         ; preds = %if.end47
  store i64 0, i64* %perline, align 8, !dbg !2334
  %94 = load i8*, i8** %ptr, align 8, !dbg !2335
  %add.ptr62 = getelementptr inbounds i8, i8* %94, i64 1, !dbg !2336
  %95 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2337
  %linestart_resp63 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %95, i32 0, i32 3, !dbg !2338
  store i8* %add.ptr62, i8** %linestart_resp63, align 8, !dbg !2339
  br label %if.end64, !dbg !2340

if.end64:                                         ; preds = %if.end61, %for.body
  br label %for.inc, !dbg !2341

for.inc:                                          ; preds = %if.end64
  %96 = load i8*, i8** %ptr, align 8, !dbg !2342
  %incdec.ptr = getelementptr inbounds i8, i8* %96, i32 1, !dbg !2342
  store i8* %incdec.ptr, i8** %ptr, align 8, !dbg !2342
  %97 = load i64, i64* %i, align 8, !dbg !2344
  %inc65 = add nsw i64 %97, 1, !dbg !2344
  store i64 %inc65, i64* %i, align 8, !dbg !2344
  br label %for.cond, !dbg !2345

for.end:                                          ; preds = %if.then50, %for.cond
  %98 = load i8, i8* %keepon, align 1, !dbg !2346
  %tobool66 = trunc i8 %98 to i1, !dbg !2346
  br i1 %tobool66, label %if.else74, label %land.lhs.true67, !dbg !2348

land.lhs.true67:                                  ; preds = %for.end
  %99 = load i64, i64* %i, align 8, !dbg !2349
  %100 = load i64, i64* %gotbytes, align 8, !dbg !2351
  %cmp68 = icmp ne i64 %99, %100, !dbg !2352
  br i1 %cmp68, label %if.then70, label %if.else74, !dbg !2353

if.then70:                                        ; preds = %land.lhs.true67
  %101 = load i64, i64* %gotbytes, align 8, !dbg !2354
  %102 = load i64, i64* %i, align 8, !dbg !2356
  %sub71 = sub nsw i64 %101, %102, !dbg !2357
  store i64 %sub71, i64* %clipamount, align 8, !dbg !2358
  store i8 1, i8* %restart, align 1, !dbg !2359
  br label %do.body72, !dbg !2360

do.body72:                                        ; preds = %if.then70
  br label %do.end73, !dbg !2361

do.end73:                                         ; preds = %do.body72
  br label %if.end96, !dbg !2364

if.else74:                                        ; preds = %land.lhs.true67, %for.end
  %103 = load i8, i8* %keepon, align 1, !dbg !2365
  %tobool75 = trunc i8 %103 to i1, !dbg !2365
  br i1 %tobool75, label %if.then76, label %if.else90, !dbg !2367

if.then76:                                        ; preds = %if.else74
  %104 = load i64, i64* %perline, align 8, !dbg !2368
  %105 = load i64, i64* %gotbytes, align 8, !dbg !2371
  %cmp77 = icmp eq i64 %104, %105, !dbg !2372
  br i1 %cmp77, label %land.lhs.true79, label %if.else83, !dbg !2373

land.lhs.true79:                                  ; preds = %if.then76
  %106 = load i64, i64* %gotbytes, align 8, !dbg !2374
  %cmp80 = icmp sgt i64 %106, 8192, !dbg !2376
  br i1 %cmp80, label %if.then82, label %if.else83, !dbg !2377

if.then82:                                        ; preds = %land.lhs.true79
  %107 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2378
  %108 = load i64, i64* %gotbytes, align 8, !dbg !2380
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %107, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.4, i32 0, i32 0), i64 %108), !dbg !2381
  store i8 1, i8* %restart, align 1, !dbg !2382
  store i64 40, i64* %clipamount, align 8, !dbg !2383
  br label %if.end89, !dbg !2384

if.else83:                                        ; preds = %land.lhs.true79, %if.then76
  %109 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2385
  %nread_resp84 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %109, i32 0, i32 2, !dbg !2387
  %110 = load i64, i64* %nread_resp84, align 8, !dbg !2387
  %cmp85 = icmp ugt i64 %110, 8192, !dbg !2388
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !2389

if.then87:                                        ; preds = %if.else83
  %111 = load i64, i64* %perline, align 8, !dbg !2390
  store i64 %111, i64* %clipamount, align 8, !dbg !2392
  store i8 1, i8* %restart, align 1, !dbg !2393
  br label %if.end88, !dbg !2394

if.end88:                                         ; preds = %if.then87, %if.else83
  br label %if.end89

if.end89:                                         ; preds = %if.end88, %if.then82
  br label %if.end95, !dbg !2395

if.else90:                                        ; preds = %if.else74
  %112 = load i64, i64* %i, align 8, !dbg !2396
  %113 = load i64, i64* %gotbytes, align 8, !dbg !2398
  %cmp91 = icmp eq i64 %112, %113, !dbg !2399
  br i1 %cmp91, label %if.then93, label %if.end94, !dbg !2400

if.then93:                                        ; preds = %if.else90
  store i8 1, i8* %restart, align 1, !dbg !2401
  br label %if.end94, !dbg !2402

if.end94:                                         ; preds = %if.then93, %if.else90
  br label %if.end95

if.end95:                                         ; preds = %if.end94, %if.end89
  br label %if.end96

if.end96:                                         ; preds = %if.end95, %do.end73
  %114 = load i64, i64* %clipamount, align 8, !dbg !2403
  %tobool97 = icmp ne i64 %114, 0, !dbg !2403
  br i1 %tobool97, label %if.then98, label %if.end111, !dbg !2405

if.then98:                                        ; preds = %if.end96
  %115 = load i64, i64* %clipamount, align 8, !dbg !2406
  %116 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2408
  %cache_size99 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %116, i32 0, i32 1, !dbg !2409
  store i64 %115, i64* %cache_size99, align 8, !dbg !2410
  %117 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !2411
  %118 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2411
  %cache_size100 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %118, i32 0, i32 1, !dbg !2411
  %119 = load i64, i64* %cache_size100, align 8, !dbg !2411
  %call101 = call i8* %117(i64 %119), !dbg !2411
  %120 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2412
  %cache102 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %120, i32 0, i32 0, !dbg !2413
  store i8* %call101, i8** %cache102, align 8, !dbg !2414
  %121 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2415
  %cache103 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %121, i32 0, i32 0, !dbg !2417
  %122 = load i8*, i8** %cache103, align 8, !dbg !2417
  %tobool104 = icmp ne i8* %122, null, !dbg !2415
  br i1 %tobool104, label %if.then105, label %if.else109, !dbg !2418

if.then105:                                       ; preds = %if.then98
  %123 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2419
  %cache106 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %123, i32 0, i32 0, !dbg !2420
  %124 = load i8*, i8** %cache106, align 8, !dbg !2420
  %125 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2421
  %linestart_resp107 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %125, i32 0, i32 3, !dbg !2422
  %126 = load i8*, i8** %linestart_resp107, align 8, !dbg !2422
  %127 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2423
  %cache_size108 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %127, i32 0, i32 1, !dbg !2424
  %128 = load i64, i64* %cache_size108, align 8, !dbg !2424
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %124, i8* %126, i64 %128, i32 1, i1 false), !dbg !2425
  br label %if.end110, !dbg !2425

if.else109:                                       ; preds = %if.then98
  store i32 27, i32* %retval, align 4, !dbg !2426
  br label %return, !dbg !2426

if.end110:                                        ; preds = %if.then105
  br label %if.end111, !dbg !2427

if.end111:                                        ; preds = %if.end110, %if.end96
  %129 = load i8, i8* %restart, align 1, !dbg !2428
  %tobool112 = trunc i8 %129 to i1, !dbg !2428
  br i1 %tobool112, label %if.then113, label %if.end116, !dbg !2430

if.then113:                                       ; preds = %if.end111
  %130 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2431
  %nread_resp114 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %130, i32 0, i32 2, !dbg !2433
  store i64 0, i64* %nread_resp114, align 8, !dbg !2434
  %131 = load i8*, i8** %buf, align 8, !dbg !2435
  %132 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2436
  %linestart_resp115 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %132, i32 0, i32 3, !dbg !2437
  store i8* %131, i8** %linestart_resp115, align 8, !dbg !2438
  store i8* %131, i8** %ptr, align 8, !dbg !2439
  store i64 0, i64* %perline, align 8, !dbg !2440
  br label %if.end116, !dbg !2441

if.end116:                                        ; preds = %if.then113, %if.end111
  br label %if.end117

if.end117:                                        ; preds = %if.end116, %if.then30
  br label %if.end118

if.end118:                                        ; preds = %if.end117, %if.then27
  br label %while.cond, !dbg !2442

while.end:                                        ; preds = %land.end6
  %133 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2444
  %pending_resp = getelementptr inbounds %struct.pingpong, %struct.pingpong* %133, i32 0, i32 4, !dbg !2445
  store i8 0, i8* %pending_resp, align 8, !dbg !2446
  %134 = load i32, i32* %result, align 4, !dbg !2447
  store i32 %134, i32* %retval, align 4, !dbg !2448
  br label %return, !dbg !2448

return:                                           ; preds = %while.end, %if.else109, %if.then46, %if.then17
  %135 = load i32, i32* %retval, align 4, !dbg !2449
  ret i32 %135, !dbg !2449
}

declare i32 @Curl_read(%struct.connectdata*, i32, i8*, i64, i64*) #2

declare i32 @Curl_client_write(%struct.connectdata*, i32, i8*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare void @Curl_infof(%struct.Curl_easy*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_getsock(%struct.pingpong* %pp, i32* %socks, i32 %numsocks) #0 !dbg !1708 {
entry:
  %retval = alloca i32, align 4
  %pp.addr = alloca %struct.pingpong*, align 8
  %socks.addr = alloca i32*, align 8
  %numsocks.addr = alloca i32, align 4
  %conn = alloca %struct.connectdata*, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !2450, metadata !1722), !dbg !2451
  store i32* %socks, i32** %socks.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %socks.addr, metadata !2452, metadata !1722), !dbg !2453
  store i32 %numsocks, i32* %numsocks.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %numsocks.addr, metadata !2454, metadata !1722), !dbg !2455
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !2456, metadata !1722), !dbg !2457
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2458
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !2459
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !2459
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !2457
  %2 = load i32, i32* %numsocks.addr, align 4, !dbg !2460
  %tobool = icmp ne i32 %2, 0, !dbg !2460
  br i1 %tobool, label %if.end, label %if.then, !dbg !2462

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2463
  br label %return, !dbg !2463

if.end:                                           ; preds = %entry
  %3 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2464
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 33, !dbg !2465
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 0, !dbg !2464
  %4 = load i32, i32* %arrayidx, align 8, !dbg !2464
  %5 = load i32*, i32** %socks.addr, align 8, !dbg !2466
  %arrayidx2 = getelementptr inbounds i32, i32* %5, i64 0, !dbg !2466
  store i32 %4, i32* %arrayidx2, align 4, !dbg !2467
  %6 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2468
  %sendleft = getelementptr inbounds %struct.pingpong, %struct.pingpong* %6, i32 0, i32 6, !dbg !2470
  %7 = load i64, i64* %sendleft, align 8, !dbg !2470
  %tobool3 = icmp ne i64 %7, 0, !dbg !2468
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !2471

if.then4:                                         ; preds = %if.end
  store i32 65536, i32* %retval, align 4, !dbg !2472
  br label %return, !dbg !2472

if.end5:                                          ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !2474
  br label %return, !dbg !2474

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2475
  ret i32 %8, !dbg !2475
}

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_flushsend(%struct.pingpong* %pp) #0 !dbg !1711 {
entry:
  %retval = alloca i32, align 4
  %pp.addr = alloca %struct.pingpong*, align 8
  %conn = alloca %struct.connectdata*, align 8
  %written = alloca i64, align 8
  %sock = alloca i32, align 4
  %result = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !2476, metadata !1722), !dbg !2477
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !2478, metadata !1722), !dbg !2479
  %0 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2480
  %conn1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %0, i32 0, i32 10, !dbg !2481
  %1 = load %struct.connectdata*, %struct.connectdata** %conn1, align 8, !dbg !2481
  store %struct.connectdata* %1, %struct.connectdata** %conn, align 8, !dbg !2479
  call void @llvm.dbg.declare(metadata i64* %written, metadata !2482, metadata !1722), !dbg !2483
  call void @llvm.dbg.declare(metadata i32* %sock, metadata !2484, metadata !1722), !dbg !2485
  %2 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2486
  %sock2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 33, !dbg !2487
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock2, i64 0, i64 0, !dbg !2486
  %3 = load i32, i32* %arrayidx, align 8, !dbg !2486
  store i32 %3, i32* %sock, align 4, !dbg !2485
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2488, metadata !1722), !dbg !2489
  %4 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2490
  %5 = load i32, i32* %sock, align 4, !dbg !2491
  %6 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2492
  %sendthis = getelementptr inbounds %struct.pingpong, %struct.pingpong* %6, i32 0, i32 5, !dbg !2493
  %7 = load i8*, i8** %sendthis, align 8, !dbg !2493
  %8 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2494
  %sendsize = getelementptr inbounds %struct.pingpong, %struct.pingpong* %8, i32 0, i32 7, !dbg !2495
  %9 = load i64, i64* %sendsize, align 8, !dbg !2495
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %9, !dbg !2496
  %10 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2497
  %sendleft = getelementptr inbounds %struct.pingpong, %struct.pingpong* %10, i32 0, i32 6, !dbg !2498
  %11 = load i64, i64* %sendleft, align 8, !dbg !2498
  %idx.neg = sub i64 0, %11, !dbg !2499
  %add.ptr3 = getelementptr inbounds i8, i8* %add.ptr, i64 %idx.neg, !dbg !2499
  %12 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2500
  %sendleft4 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %12, i32 0, i32 6, !dbg !2501
  %13 = load i64, i64* %sendleft4, align 8, !dbg !2501
  %call = call i32 @Curl_write(%struct.connectdata* %4, i32 %5, i8* %add.ptr3, i64 %13, i64* %written), !dbg !2502
  store i32 %call, i32* %result, align 4, !dbg !2489
  %14 = load i32, i32* %result, align 4, !dbg !2503
  %tobool = icmp ne i32 %14, 0, !dbg !2503
  br i1 %tobool, label %if.then, label %if.end, !dbg !2505

if.then:                                          ; preds = %entry
  %15 = load i32, i32* %result, align 4, !dbg !2506
  store i32 %15, i32* %retval, align 4, !dbg !2507
  br label %return, !dbg !2507

if.end:                                           ; preds = %entry
  %16 = load i64, i64* %written, align 8, !dbg !2508
  %17 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2510
  %sendleft5 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %17, i32 0, i32 6, !dbg !2511
  %18 = load i64, i64* %sendleft5, align 8, !dbg !2511
  %cmp = icmp ne i64 %16, %18, !dbg !2512
  br i1 %cmp, label %if.then6, label %if.else, !dbg !2513

if.then6:                                         ; preds = %if.end
  %19 = load i64, i64* %written, align 8, !dbg !2514
  %20 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2516
  %sendleft7 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %20, i32 0, i32 6, !dbg !2517
  %21 = load i64, i64* %sendleft7, align 8, !dbg !2518
  %sub = sub i64 %21, %19, !dbg !2518
  store i64 %sub, i64* %sendleft7, align 8, !dbg !2518
  br label %if.end13, !dbg !2519

if.else:                                          ; preds = %if.end
  %22 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2520
  %23 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2520
  %sendthis8 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %23, i32 0, i32 5, !dbg !2520
  %24 = load i8*, i8** %sendthis8, align 8, !dbg !2520
  call void %22(i8* %24), !dbg !2520
  %25 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2522
  %sendthis9 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %25, i32 0, i32 5, !dbg !2523
  store i8* null, i8** %sendthis9, align 8, !dbg !2524
  %26 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2525
  %sendsize10 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %26, i32 0, i32 7, !dbg !2526
  store i64 0, i64* %sendsize10, align 8, !dbg !2527
  %27 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2528
  %sendleft11 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %27, i32 0, i32 6, !dbg !2529
  store i64 0, i64* %sendleft11, align 8, !dbg !2530
  %28 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2531
  %response = getelementptr inbounds %struct.pingpong, %struct.pingpong* %28, i32 0, i32 8, !dbg !2532
  %call12 = call { i64, i64 } @curlx_tvnow(), !dbg !2533
  %29 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2533
  %30 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %29, i32 0, i32 0, !dbg !2533
  %31 = extractvalue { i64, i64 } %call12, 0, !dbg !2533
  store i64 %31, i64* %30, align 8, !dbg !2533
  %32 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %29, i32 0, i32 1, !dbg !2533
  %33 = extractvalue { i64, i64 } %call12, 1, !dbg !2533
  store i64 %33, i64* %32, align 8, !dbg !2533
  %34 = bitcast %struct.timeval* %response to i8*, !dbg !2533
  %35 = bitcast %struct.timeval* %coerce to i8*, !dbg !2533
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %34, i8* %35, i64 16, i32 8, i1 false), !dbg !2534
  br label %if.end13

if.end13:                                         ; preds = %if.else, %if.then6
  store i32 0, i32* %retval, align 4, !dbg !2536
  br label %return, !dbg !2536

return:                                           ; preds = %if.end13, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !2537
  ret i32 %36, !dbg !2537
}

; Function Attrs: nounwind uwtable
define i32 @Curl_pp_disconnect(%struct.pingpong* %pp) #0 !dbg !1714 {
entry:
  %pp.addr = alloca %struct.pingpong*, align 8
  store %struct.pingpong* %pp, %struct.pingpong** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pingpong** %pp.addr, metadata !2538, metadata !1722), !dbg !2539
  %0 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2540
  %1 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2540
  %cache = getelementptr inbounds %struct.pingpong, %struct.pingpong* %1, i32 0, i32 0, !dbg !2540
  %2 = load i8*, i8** %cache, align 8, !dbg !2540
  call void %0(i8* %2), !dbg !2540
  %3 = load %struct.pingpong*, %struct.pingpong** %pp.addr, align 8, !dbg !2541
  %cache1 = getelementptr inbounds %struct.pingpong, %struct.pingpong* %3, i32 0, i32 0, !dbg !2542
  store i8* null, i8** %cache1, align 8, !dbg !2543
  ret i32 0, !dbg !2544
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1718, !1719}
!llvm.ident = !{!1720}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1678, subprograms: !1679)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !26, !123, !129, !185, !227, !234, !269, !279, !285, !290, !297, !307, !316, !322, !328, !334, !340, !347, !353, !359, !374, !385, !399, !410, !415, !423, !461, !480, !500, !515, !532, !540}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 35, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/multihandle.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25}
!6 = !DIEnumerator(name: "CURLM_STATE_INIT", value: 0)
!7 = !DIEnumerator(name: "CURLM_STATE_CONNECT_PEND", value: 1)
!8 = !DIEnumerator(name: "CURLM_STATE_CONNECT", value: 2)
!9 = !DIEnumerator(name: "CURLM_STATE_WAITRESOLVE", value: 3)
!10 = !DIEnumerator(name: "CURLM_STATE_WAITCONNECT", value: 4)
!11 = !DIEnumerator(name: "CURLM_STATE_WAITPROXYCONNECT", value: 5)
!12 = !DIEnumerator(name: "CURLM_STATE_SENDPROTOCONNECT", value: 6)
!13 = !DIEnumerator(name: "CURLM_STATE_PROTOCONNECT", value: 7)
!14 = !DIEnumerator(name: "CURLM_STATE_WAITDO", value: 8)
!15 = !DIEnumerator(name: "CURLM_STATE_DO", value: 9)
!16 = !DIEnumerator(name: "CURLM_STATE_DOING", value: 10)
!17 = !DIEnumerator(name: "CURLM_STATE_DO_MORE", value: 11)
!18 = !DIEnumerator(name: "CURLM_STATE_DO_DONE", value: 12)
!19 = !DIEnumerator(name: "CURLM_STATE_WAITPERFORM", value: 13)
!20 = !DIEnumerator(name: "CURLM_STATE_PERFORM", value: 14)
!21 = !DIEnumerator(name: "CURLM_STATE_TOOFAST", value: 15)
!22 = !DIEnumerator(name: "CURLM_STATE_DONE", value: 16)
!23 = !DIEnumerator(name: "CURLM_STATE_COMPLETED", value: 17)
!24 = !DIEnumerator(name: "CURLM_STATE_MSGSENT", value: 18)
!25 = !DIEnumerator(name: "CURLM_STATE_LAST", value: 19)
!26 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 434, size: 32, align: 32, elements: !28)
!27 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!28 = !{!29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122}
!29 = !DIEnumerator(name: "CURLE_OK", value: 0)
!30 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!31 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!32 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!33 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!34 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!35 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!36 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!37 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!38 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!39 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!40 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!41 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!42 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!43 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!44 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!45 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!46 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!47 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!48 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!49 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!50 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!51 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!52 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!53 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!54 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!55 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!56 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!57 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!58 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!59 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!60 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!61 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!62 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!63 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!64 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!65 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!66 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!67 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!68 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!69 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!70 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!71 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!72 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!73 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!74 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!75 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!76 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!77 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!78 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!79 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!80 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!81 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!82 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!83 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!84 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!85 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!86 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!87 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!88 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!89 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!90 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!91 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!92 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!93 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!94 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!95 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!96 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!97 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!98 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!99 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!100 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!101 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!102 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!103 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!104 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!105 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!106 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!107 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!108 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!109 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!110 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!111 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!112 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!113 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!114 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!115 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!116 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!117 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!118 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!119 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!120 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!121 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!122 = !DIEnumerator(name: "CURL_LAST", value: 93)
!123 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !124, line: 86, size: 32, align: 32, elements: !125)
!124 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/multi.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!125 = !{!126, !127, !128}
!126 = !DIEnumerator(name: "CURLMSG_NONE", value: 0)
!127 = !DIEnumerator(name: "CURLMSG_DONE", value: 1)
!128 = !DIEnumerator(name: "CURLMSG_LAST", value: 2)
!129 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !131, file: !130, line: 1783, size: 32, align: 32, elements: !180)
!130 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/urldata.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!131 = !DICompositeType(tag: DW_TAG_structure_type, name: "Names", file: !130, line: 1781, size: 128, align: 64, elements: !132)
!132 = !{!133, !179}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !131, file: !130, line: 1782, baseType: !134, size: 64, align: 64)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !135, size: 64, align: 64)
!135 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash", file: !136, line: 46, size: 384, align: 64, elements: !137)
!136 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!137 = !{!138, !161, !166, !171, !176, !178}
!138 = !DIDerivedType(tag: DW_TAG_member, name: "table", scope: !135, file: !136, line: 47, baseType: !139, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !141, line: 37, size: 256, align: 64, elements: !142)
!141 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!142 = !{!143, !151, !152, !157}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !140, file: !141, line: 38, baseType: !144, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !141, line: 30, size: 192, align: 64, elements: !146)
!146 = !{!147, !149, !150}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !145, file: !141, line: 31, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !145, file: !141, line: 33, baseType: !144, size: 64, align: 64, offset: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !145, file: !141, line: 34, baseType: !144, size: 64, align: 64, offset: 128)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !140, file: !141, line: 39, baseType: !144, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !140, file: !141, line: 41, baseType: !153, size: 64, align: 64, offset: 128)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !141, line: 28, baseType: !154)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!155 = !DISubroutineType(types: !156)
!156 = !{null, !148, !148}
!157 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !140, file: !141, line: 43, baseType: !158, size: 64, align: 64, offset: 192)
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !159, line: 62, baseType: !160)
!159 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!160 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "hash_func", scope: !135, file: !136, line: 50, baseType: !162, size: 64, align: 64, offset: 64)
!162 = !DIDerivedType(tag: DW_TAG_typedef, name: "hash_function", file: !136, line: 32, baseType: !163)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DISubroutineType(types: !165)
!165 = !{!158, !148, !158, !158}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "comp_func", scope: !135, file: !136, line: 53, baseType: !167, size: 64, align: 64, offset: 128)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "comp_function", file: !136, line: 39, baseType: !168)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DISubroutineType(types: !170)
!170 = !{!158, !148, !158, !148, !158}
!171 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !135, file: !136, line: 54, baseType: !172, size: 64, align: 64, offset: 192)
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_hash_dtor", file: !136, line: 44, baseType: !173)
!173 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !174, size: 64, align: 64)
!174 = !DISubroutineType(types: !175)
!175 = !{null, !148}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "slots", scope: !135, file: !136, line: 55, baseType: !177, size: 32, align: 32, offset: 256)
!177 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !135, file: !136, line: 56, baseType: !158, size: 64, align: 64, offset: 320)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "hostcachetype", scope: !131, file: !130, line: 1788, baseType: !129, size: 32, align: 32, offset: 64)
!180 = !{!181, !182, !183, !184}
!181 = !DIEnumerator(name: "HCACHE_NONE", value: 0)
!182 = !DIEnumerator(name: "HCACHE_GLOBAL", value: 1)
!183 = !DIEnumerator(name: "HCACHE_MULTI", value: 2)
!184 = !DIEnumerator(name: "HCACHE_SHARED", value: 3)
!185 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !186, file: !130, line: 679, size: 32, align: 32, elements: !265)
!186 = !DICompositeType(tag: DW_TAG_structure_type, name: "SingleRequest", file: !130, line: 658, size: 2496, align: 64, elements: !187)
!187 = !{!188, !192, !194, !195, !196, !197, !198, !199, !200, !209, !210, !212, !213, !214, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !233, !240, !241, !244, !245, !246, !247, !249, !250, !251, !252, !253, !254, !255, !259, !260, !261, !262, !263, !264}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !186, file: !130, line: 659, baseType: !189, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !190, line: 216, baseType: !191)
!190 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!191 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "bytecountp", scope: !186, file: !130, line: 660, baseType: !193, size: 64, align: 64, offset: 64)
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "maxdownload", scope: !186, file: !130, line: 662, baseType: !189, size: 64, align: 64, offset: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecountp", scope: !186, file: !130, line: 664, baseType: !193, size: 64, align: 64, offset: 192)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "bytecount", scope: !186, file: !130, line: 666, baseType: !189, size: 64, align: 64, offset: 256)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !186, file: !130, line: 667, baseType: !189, size: 64, align: 64, offset: 320)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "headerbytecount", scope: !186, file: !130, line: 669, baseType: !191, size: 64, align: 64, offset: 384)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "deductheadercount", scope: !186, file: !130, line: 670, baseType: !191, size: 64, align: 64, offset: 448)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !186, file: !130, line: 676, baseType: !201, size: 128, align: 64, offset: 512)
!201 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !202, line: 30, size: 128, align: 64, elements: !203)
!202 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!203 = !{!204, !207}
!204 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !201, file: !202, line: 32, baseType: !205, size: 64, align: 64)
!205 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !206, line: 139, baseType: !191)
!206 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!207 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !201, file: !202, line: 33, baseType: !208, size: 64, align: 64, offset: 64)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !206, line: 141, baseType: !191)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !186, file: !130, line: 677, baseType: !201, size: 128, align: 64, offset: 640)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !186, file: !130, line: 678, baseType: !211, size: 8, align: 8, offset: 768)
!211 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "badheader", scope: !186, file: !130, line: 684, baseType: !185, size: 32, align: 32, offset: 800)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "headerline", scope: !186, file: !130, line: 686, baseType: !177, size: 32, align: 32, offset: 832)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "hbufp", scope: !186, file: !130, line: 688, baseType: !215, size: 64, align: 64, offset: 896)
!215 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !216, size: 64, align: 64)
!216 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "hbuflen", scope: !186, file: !130, line: 689, baseType: !158, size: 64, align: 64, offset: 960)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !186, file: !130, line: 690, baseType: !215, size: 64, align: 64, offset: 1024)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "str_start", scope: !186, file: !130, line: 691, baseType: !215, size: 64, align: 64, offset: 1088)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "end_ptr", scope: !186, file: !130, line: 692, baseType: !215, size: 64, align: 64, offset: 1152)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !186, file: !130, line: 693, baseType: !215, size: 64, align: 64, offset: 1216)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "content_range", scope: !186, file: !130, line: 694, baseType: !211, size: 8, align: 8, offset: 1280)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !186, file: !130, line: 695, baseType: !189, size: 64, align: 64, offset: 1344)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !186, file: !130, line: 697, baseType: !177, size: 32, align: 32, offset: 1408)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "start100", scope: !186, file: !130, line: 699, baseType: !201, size: 128, align: 64, offset: 1472)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "exp100", scope: !186, file: !130, line: 700, baseType: !227, size: 32, align: 32, offset: 1600)
!227 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "expect100", file: !130, line: 636, size: 32, align: 32, elements: !228)
!228 = !{!229, !230, !231, !232}
!229 = !DIEnumerator(name: "EXP100_SEND_DATA", value: 0)
!230 = !DIEnumerator(name: "EXP100_AWAITING_CONTINUE", value: 1)
!231 = !DIEnumerator(name: "EXP100_SENDING_REQUEST", value: 2)
!232 = !DIEnumerator(name: "EXP100_FAILED", value: 3)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "upgr101", scope: !186, file: !130, line: 701, baseType: !234, size: 32, align: 32, offset: 1632)
!234 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "upgrade101", file: !130, line: 644, size: 32, align: 32, elements: !235)
!235 = !{!236, !237, !238, !239}
!236 = !DIEnumerator(name: "UPGR101_INIT", value: 0)
!237 = !DIEnumerator(name: "UPGR101_REQUESTED", value: 1)
!238 = !DIEnumerator(name: "UPGR101_RECEIVED", value: 2)
!239 = !DIEnumerator(name: "UPGR101_WORKING", value: 3)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "auto_decoding", scope: !186, file: !130, line: 703, baseType: !177, size: 32, align: 32, offset: 1664)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "timeofdoc", scope: !186, file: !130, line: 715, baseType: !242, size: 64, align: 64, offset: 1728)
!242 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !243, line: 75, baseType: !205)
!243 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!244 = !DIDerivedType(tag: DW_TAG_member, name: "bodywrites", scope: !186, file: !130, line: 716, baseType: !191, size: 64, align: 64, offset: 1792)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !186, file: !130, line: 718, baseType: !215, size: 64, align: 64, offset: 1856)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuf", scope: !186, file: !130, line: 719, baseType: !215, size: 64, align: 64, offset: 1920)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "maxfd", scope: !186, file: !130, line: 720, baseType: !248, size: 32, align: 32, offset: 1984)
!248 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !27, line: 131, baseType: !177)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "keepon", scope: !186, file: !130, line: 722, baseType: !177, size: 32, align: 32, offset: 2016)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "upload_done", scope: !186, file: !130, line: 724, baseType: !211, size: 8, align: 8, offset: 2048)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "ignorebody", scope: !186, file: !130, line: 727, baseType: !211, size: 8, align: 8, offset: 2056)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !186, file: !130, line: 728, baseType: !211, size: 8, align: 8, offset: 2064)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "location", scope: !186, file: !130, line: 731, baseType: !215, size: 64, align: 64, offset: 2112)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "newurl", scope: !186, file: !130, line: 733, baseType: !215, size: 64, align: 64, offset: 2176)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "upload_present", scope: !186, file: !130, line: 738, baseType: !256, size: 64, align: 64, offset: 2240)
!256 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !257, line: 109, baseType: !258)
!257 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!258 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !206, line: 172, baseType: !191)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "upload_fromhere", scope: !186, file: !130, line: 744, baseType: !215, size: 64, align: 64, offset: 2304)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !186, file: !130, line: 746, baseType: !211, size: 8, align: 8, offset: 2368)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "upload_chunky", scope: !186, file: !130, line: 747, baseType: !211, size: 8, align: 8, offset: 2376)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "getheader", scope: !186, file: !130, line: 749, baseType: !211, size: 8, align: 8, offset: 2384)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "forbidchunk", scope: !186, file: !130, line: 751, baseType: !211, size: 8, align: 8, offset: 2392)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "protop", scope: !186, file: !130, line: 755, baseType: !148, size: 64, align: 64, offset: 2432)
!265 = !{!266, !267, !268}
!266 = !DIEnumerator(name: "HEADER_NORMAL", value: 0)
!267 = !DIEnumerator(name: "HEADER_PARTHEADER", value: 1)
!268 = !DIEnumerator(name: "HEADER_ALLBAD", value: 2)
!269 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 409, size: 32, align: 32, elements: !270)
!270 = !{!271, !272, !273, !274, !275, !276, !277, !278}
!271 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!272 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!273 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!274 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!275 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!276 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!277 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!278 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!279 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 375, size: 32, align: 32, elements: !280)
!280 = !{!281, !282, !283, !284}
!281 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!282 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!283 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!284 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!285 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 340, size: 32, align: 32, elements: !286)
!286 = !{!287, !288, !289}
!287 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!288 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!289 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!290 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 1921, size: 32, align: 32, elements: !291)
!291 = !{!292, !293, !294, !295, !296}
!292 = !DIEnumerator(name: "CURL_TIMECOND_NONE", value: 0)
!293 = !DIEnumerator(name: "CURL_TIMECOND_IFMODSINCE", value: 1)
!294 = !DIEnumerator(name: "CURL_TIMECOND_IFUNMODSINCE", value: 2)
!295 = !DIEnumerator(name: "CURL_TIMECOND_LASTMOD", value: 3)
!296 = !DIEnumerator(name: "CURL_TIMECOND_LAST", value: 4)
!297 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 1240, size: 32, align: 32, elements: !298)
!298 = !{!299, !300, !301, !302, !303, !304, !305, !306}
!299 = !DIEnumerator(name: "HTTPREQ_NONE", value: 0)
!300 = !DIEnumerator(name: "HTTPREQ_GET", value: 1)
!301 = !DIEnumerator(name: "HTTPREQ_POST", value: 2)
!302 = !DIEnumerator(name: "HTTPREQ_POST_FORM", value: 3)
!303 = !DIEnumerator(name: "HTTPREQ_PUT", value: 4)
!304 = !DIEnumerator(name: "HTTPREQ_HEAD", value: 5)
!305 = !DIEnumerator(name: "HTTPREQ_CUSTOM", value: 6)
!306 = !DIEnumerator(name: "HTTPREQ_LAST", value: 7)
!307 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 644, size: 32, align: 32, elements: !308)
!308 = !{!309, !310, !311, !312, !313, !314, !315}
!309 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!310 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!311 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!312 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!313 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!314 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!315 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
!316 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !317, line: 93, size: 32, align: 32, elements: !318)
!317 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ftp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!318 = !{!319, !320, !321}
!319 = !DIEnumerator(name: "FTPFILE_MULTICWD", value: 1)
!320 = !DIEnumerator(name: "FTPFILE_NOCWD", value: 2)
!321 = !DIEnumerator(name: "FTPFILE_SINGLECWD", value: 3)
!322 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !27, line: 704, size: 32, align: 32, elements: !323)
!323 = !{!324, !325, !326, !327}
!324 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!325 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!326 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!327 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!328 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !27, line: 731, size: 32, align: 32, elements: !329)
!329 = !{!330, !331, !332, !333}
!330 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!331 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!332 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!333 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!334 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !27, line: 1867, size: 32, align: 32, elements: !335)
!335 = !{!336, !337, !338, !339}
!336 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!337 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!338 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!339 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!340 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 746, size: 32, align: 32, elements: !341)
!341 = !{!342, !343, !344, !345, !346}
!342 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!343 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!344 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!345 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!346 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!347 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 790, size: 32, align: 32, elements: !348)
!348 = !{!349, !350, !351, !352}
!349 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!350 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!351 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!352 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!353 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 782, size: 32, align: 32, elements: !354)
!354 = !{!355, !356, !357, !358}
!355 = !DIEnumerator(name: "CURLFTPSSL_CCC_NONE", value: 0)
!356 = !DIEnumerator(name: "CURLFTPSSL_CCC_PASSIVE", value: 1)
!357 = !DIEnumerator(name: "CURLFTPSSL_CCC_ACTIVE", value: 2)
!358 = !DIEnumerator(name: "CURLFTPSSL_CCC_LAST", value: 3)
!359 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 1251, size: 32, align: 32, elements: !360)
!360 = !{!361, !362, !363, !364, !365, !366, !367, !368, !369, !370, !371, !372, !373}
!361 = !DIEnumerator(name: "RTSPREQ_NONE", value: 0)
!362 = !DIEnumerator(name: "RTSPREQ_OPTIONS", value: 1)
!363 = !DIEnumerator(name: "RTSPREQ_DESCRIBE", value: 2)
!364 = !DIEnumerator(name: "RTSPREQ_ANNOUNCE", value: 3)
!365 = !DIEnumerator(name: "RTSPREQ_SETUP", value: 4)
!366 = !DIEnumerator(name: "RTSPREQ_PLAY", value: 5)
!367 = !DIEnumerator(name: "RTSPREQ_PAUSE", value: 6)
!368 = !DIEnumerator(name: "RTSPREQ_TEARDOWN", value: 7)
!369 = !DIEnumerator(name: "RTSPREQ_GET_PARAMETER", value: 8)
!370 = !DIEnumerator(name: "RTSPREQ_SET_PARAMETER", value: 9)
!371 = !DIEnumerator(name: "RTSPREQ_RECORD", value: 10)
!372 = !DIEnumerator(name: "RTSPREQ_RECEIVE", value: 11)
!373 = !DIEnumerator(name: "RTSPREQ_LAST", value: 12)
!374 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !375, line: 30, size: 32, align: 32, elements: !376)
!375 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!376 = !{!377, !378, !379, !380, !381, !382, !383, !384}
!377 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!378 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!379 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!380 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!381 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!382 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!383 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!384 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!385 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 2222, size: 32, align: 32, elements: !386)
!386 = !{!387, !388, !389, !390, !391, !392, !393, !394, !395, !396, !397, !398}
!387 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!388 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!389 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!390 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!391 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!392 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!393 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!394 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!395 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!396 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!397 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!398 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!399 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !400, line: 31, size: 32, align: 32, elements: !401)
!400 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http_chunks.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!401 = !{!402, !403, !404, !405, !406, !407, !408, !409}
!402 = !DIEnumerator(name: "CHUNK_HEX", value: 0)
!403 = !DIEnumerator(name: "CHUNK_LF", value: 1)
!404 = !DIEnumerator(name: "CHUNK_DATA", value: 2)
!405 = !DIEnumerator(name: "CHUNK_POSTLF", value: 3)
!406 = !DIEnumerator(name: "CHUNK_STOP", value: 4)
!407 = !DIEnumerator(name: "CHUNK_TRAILER", value: 5)
!408 = !DIEnumerator(name: "CHUNK_TRAILER_CR", value: 6)
!409 = !DIEnumerator(name: "CHUNK_TRAILER_POSTCR", value: 7)
!410 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 267, size: 32, align: 32, elements: !411)
!411 = !{!412, !413, !414}
!412 = !DIEnumerator(name: "ssl_connection_none", value: 0)
!413 = !DIEnumerator(name: "ssl_connection_negotiating", value: 1)
!414 = !DIEnumerator(name: "ssl_connection_complete", value: 2)
!415 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 258, size: 32, align: 32, elements: !416)
!416 = !{!417, !418, !419, !420, !421, !422}
!417 = !DIEnumerator(name: "ssl_connect_1", value: 0)
!418 = !DIEnumerator(name: "ssl_connect_2", value: 1)
!419 = !DIEnumerator(name: "ssl_connect_2_reading", value: 2)
!420 = !DIEnumerator(name: "ssl_connect_2_writing", value: 3)
!421 = !DIEnumerator(name: "ssl_connect_3", value: 4)
!422 = !DIEnumerator(name: "ssl_connect_done", value: 5)
!423 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !317, line: 42, size: 32, align: 32, elements: !424)
!424 = !{!425, !426, !427, !428, !429, !430, !431, !432, !433, !434, !435, !436, !437, !438, !439, !440, !441, !442, !443, !444, !445, !446, !447, !448, !449, !450, !451, !452, !453, !454, !455, !456, !457, !458, !459, !460}
!425 = !DIEnumerator(name: "FTP_STOP", value: 0)
!426 = !DIEnumerator(name: "FTP_WAIT220", value: 1)
!427 = !DIEnumerator(name: "FTP_AUTH", value: 2)
!428 = !DIEnumerator(name: "FTP_USER", value: 3)
!429 = !DIEnumerator(name: "FTP_PASS", value: 4)
!430 = !DIEnumerator(name: "FTP_ACCT", value: 5)
!431 = !DIEnumerator(name: "FTP_PBSZ", value: 6)
!432 = !DIEnumerator(name: "FTP_PROT", value: 7)
!433 = !DIEnumerator(name: "FTP_CCC", value: 8)
!434 = !DIEnumerator(name: "FTP_PWD", value: 9)
!435 = !DIEnumerator(name: "FTP_SYST", value: 10)
!436 = !DIEnumerator(name: "FTP_NAMEFMT", value: 11)
!437 = !DIEnumerator(name: "FTP_QUOTE", value: 12)
!438 = !DIEnumerator(name: "FTP_RETR_PREQUOTE", value: 13)
!439 = !DIEnumerator(name: "FTP_STOR_PREQUOTE", value: 14)
!440 = !DIEnumerator(name: "FTP_POSTQUOTE", value: 15)
!441 = !DIEnumerator(name: "FTP_CWD", value: 16)
!442 = !DIEnumerator(name: "FTP_MKD", value: 17)
!443 = !DIEnumerator(name: "FTP_MDTM", value: 18)
!444 = !DIEnumerator(name: "FTP_TYPE", value: 19)
!445 = !DIEnumerator(name: "FTP_LIST_TYPE", value: 20)
!446 = !DIEnumerator(name: "FTP_RETR_TYPE", value: 21)
!447 = !DIEnumerator(name: "FTP_STOR_TYPE", value: 22)
!448 = !DIEnumerator(name: "FTP_SIZE", value: 23)
!449 = !DIEnumerator(name: "FTP_RETR_SIZE", value: 24)
!450 = !DIEnumerator(name: "FTP_STOR_SIZE", value: 25)
!451 = !DIEnumerator(name: "FTP_REST", value: 26)
!452 = !DIEnumerator(name: "FTP_RETR_REST", value: 27)
!453 = !DIEnumerator(name: "FTP_PORT", value: 28)
!454 = !DIEnumerator(name: "FTP_PRET", value: 29)
!455 = !DIEnumerator(name: "FTP_PASV", value: 30)
!456 = !DIEnumerator(name: "FTP_LIST", value: 31)
!457 = !DIEnumerator(name: "FTP_RETR", value: 32)
!458 = !DIEnumerator(name: "FTP_STOR", value: 33)
!459 = !DIEnumerator(name: "FTP_QUIT", value: 34)
!460 = !DIEnumerator(name: "FTP_LAST", value: 35)
!461 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !462, line: 31, size: 32, align: 32, elements: !463)
!462 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/imap.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!463 = !{!464, !465, !466, !467, !468, !469, !470, !471, !472, !473, !474, !475, !476, !477, !478, !479}
!464 = !DIEnumerator(name: "IMAP_STOP", value: 0)
!465 = !DIEnumerator(name: "IMAP_SERVERGREET", value: 1)
!466 = !DIEnumerator(name: "IMAP_CAPABILITY", value: 2)
!467 = !DIEnumerator(name: "IMAP_STARTTLS", value: 3)
!468 = !DIEnumerator(name: "IMAP_UPGRADETLS", value: 4)
!469 = !DIEnumerator(name: "IMAP_AUTHENTICATE", value: 5)
!470 = !DIEnumerator(name: "IMAP_LOGIN", value: 6)
!471 = !DIEnumerator(name: "IMAP_LIST", value: 7)
!472 = !DIEnumerator(name: "IMAP_SELECT", value: 8)
!473 = !DIEnumerator(name: "IMAP_FETCH", value: 9)
!474 = !DIEnumerator(name: "IMAP_FETCH_FINAL", value: 10)
!475 = !DIEnumerator(name: "IMAP_APPEND", value: 11)
!476 = !DIEnumerator(name: "IMAP_APPEND_FINAL", value: 12)
!477 = !DIEnumerator(name: "IMAP_SEARCH", value: 13)
!478 = !DIEnumerator(name: "IMAP_LOGOUT", value: 14)
!479 = !DIEnumerator(name: "IMAP_LAST", value: 15)
!480 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !481, line: 58, size: 32, align: 32, elements: !482)
!481 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_sasl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!482 = !{!483, !484, !485, !486, !487, !488, !489, !490, !491, !492, !493, !494, !495, !496, !497, !498, !499}
!483 = !DIEnumerator(name: "SASL_STOP", value: 0)
!484 = !DIEnumerator(name: "SASL_PLAIN", value: 1)
!485 = !DIEnumerator(name: "SASL_LOGIN", value: 2)
!486 = !DIEnumerator(name: "SASL_LOGIN_PASSWD", value: 3)
!487 = !DIEnumerator(name: "SASL_EXTERNAL", value: 4)
!488 = !DIEnumerator(name: "SASL_CRAMMD5", value: 5)
!489 = !DIEnumerator(name: "SASL_DIGESTMD5", value: 6)
!490 = !DIEnumerator(name: "SASL_DIGESTMD5_RESP", value: 7)
!491 = !DIEnumerator(name: "SASL_NTLM", value: 8)
!492 = !DIEnumerator(name: "SASL_NTLM_TYPE2MSG", value: 9)
!493 = !DIEnumerator(name: "SASL_GSSAPI", value: 10)
!494 = !DIEnumerator(name: "SASL_GSSAPI_TOKEN", value: 11)
!495 = !DIEnumerator(name: "SASL_GSSAPI_NO_DATA", value: 12)
!496 = !DIEnumerator(name: "SASL_OAUTH2", value: 13)
!497 = !DIEnumerator(name: "SASL_OAUTH2_RESP", value: 14)
!498 = !DIEnumerator(name: "SASL_CANCEL", value: 15)
!499 = !DIEnumerator(name: "SASL_FINAL", value: 16)
!500 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !501, line: 31, size: 32, align: 32, elements: !502)
!501 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pop3.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!502 = !{!503, !504, !505, !506, !507, !508, !509, !510, !511, !512, !513, !514}
!503 = !DIEnumerator(name: "POP3_STOP", value: 0)
!504 = !DIEnumerator(name: "POP3_SERVERGREET", value: 1)
!505 = !DIEnumerator(name: "POP3_CAPA", value: 2)
!506 = !DIEnumerator(name: "POP3_STARTTLS", value: 3)
!507 = !DIEnumerator(name: "POP3_UPGRADETLS", value: 4)
!508 = !DIEnumerator(name: "POP3_AUTH", value: 5)
!509 = !DIEnumerator(name: "POP3_APOP", value: 6)
!510 = !DIEnumerator(name: "POP3_USER", value: 7)
!511 = !DIEnumerator(name: "POP3_PASS", value: 8)
!512 = !DIEnumerator(name: "POP3_COMMAND", value: 9)
!513 = !DIEnumerator(name: "POP3_QUIT", value: 10)
!514 = !DIEnumerator(name: "POP3_LAST", value: 11)
!515 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !516, line: 31, size: 32, align: 32, elements: !517)
!516 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smtp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!517 = !{!518, !519, !520, !521, !522, !523, !524, !525, !526, !527, !528, !529, !530, !531}
!518 = !DIEnumerator(name: "SMTP_STOP", value: 0)
!519 = !DIEnumerator(name: "SMTP_SERVERGREET", value: 1)
!520 = !DIEnumerator(name: "SMTP_EHLO", value: 2)
!521 = !DIEnumerator(name: "SMTP_HELO", value: 3)
!522 = !DIEnumerator(name: "SMTP_STARTTLS", value: 4)
!523 = !DIEnumerator(name: "SMTP_UPGRADETLS", value: 5)
!524 = !DIEnumerator(name: "SMTP_AUTH", value: 6)
!525 = !DIEnumerator(name: "SMTP_COMMAND", value: 7)
!526 = !DIEnumerator(name: "SMTP_MAIL", value: 8)
!527 = !DIEnumerator(name: "SMTP_RCPT", value: 9)
!528 = !DIEnumerator(name: "SMTP_DATA", value: 10)
!529 = !DIEnumerator(name: "SMTP_POSTDATA", value: 11)
!530 = !DIEnumerator(name: "SMTP_QUIT", value: 12)
!531 = !DIEnumerator(name: "SMTP_LAST", value: 13)
!532 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "smb_conn_state", file: !533, line: 25, size: 32, align: 32, elements: !534)
!533 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!534 = !{!535, !536, !537, !538, !539}
!535 = !DIEnumerator(name: "SMB_NOT_CONNECTED", value: 0)
!536 = !DIEnumerator(name: "SMB_CONNECTING", value: 1)
!537 = !DIEnumerator(name: "SMB_NEGOTIATE", value: 2)
!538 = !DIEnumerator(name: "SMB_SETUP", value: 3)
!539 = !DIEnumerator(name: "SMB_CONNECTED", value: 4)
!540 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !541, file: !130, line: 1133, size: 32, align: 32, elements: !1674)
!541 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectdata", file: !130, line: 895, size: 13440, align: 64, elements: !542)
!542 = !{!543, !1255, !1267, !1268, !1269, !1270, !1271, !1297, !1298, !1302, !1303, !1304, !1305, !1312, !1313, !1314, !1322, !1323, !1324, !1325, !1326, !1327, !1328, !1329, !1330, !1331, !1332, !1333, !1334, !1335, !1336, !1337, !1338, !1339, !1341, !1342, !1344, !1351, !1357, !1366, !1367, !1368, !1369, !1370, !1406, !1407, !1408, !1409, !1463, !1464, !1465, !1466, !1467, !1480, !1481, !1482, !1483, !1484, !1485, !1486, !1487, !1488, !1489, !1493, !1494, !1495, !1496, !1659, !1660, !1661, !1662, !1663, !1664, !1666, !1673}
!543 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !541, file: !130, line: 899, baseType: !544, size: 64, align: 64)
!544 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !545, size: 64, align: 64)
!545 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_easy", file: !130, line: 1801, size: 160192, align: 64, elements: !546)
!546 = !{!547, !548, !549, !551, !553, !555, !571, !575, !576, !577, !643, !644, !647, !648, !1030, !1039, !1066, !1102, !1206, !1218, !1248, !1254}
!547 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !545, file: !130, line: 1803, baseType: !544, size: 64, align: 64)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !545, file: !130, line: 1804, baseType: !544, size: 64, align: 64, offset: 64)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "easy_conn", scope: !545, file: !130, line: 1806, baseType: !550, size: 64, align: 64, offset: 128)
!550 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !541, size: 64, align: 64)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "mstate", scope: !545, file: !130, line: 1808, baseType: !552, size: 32, align: 32, offset: 192)
!552 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMstate", file: !4, line: 59, baseType: !3)
!553 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !545, file: !130, line: 1809, baseType: !554, size: 32, align: 32, offset: 224)
!554 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !27, line: 561, baseType: !26)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !545, file: !130, line: 1811, baseType: !556, size: 192, align: 64, offset: 256)
!556 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_message", file: !4, line: 27, size: 192, align: 64, elements: !557)
!557 = !{!558}
!558 = !DIDerivedType(tag: DW_TAG_member, name: "extmsg", scope: !556, file: !4, line: 29, baseType: !559, size: 192, align: 64)
!559 = !DICompositeType(tag: DW_TAG_structure_type, name: "CURLMsg", file: !124, line: 93, size: 192, align: 64, elements: !560)
!560 = !{!561, !563, !566}
!561 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !559, file: !124, line: 94, baseType: !562, size: 32, align: 32)
!562 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMSG", file: !124, line: 91, baseType: !123)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "easy_handle", scope: !559, file: !124, line: 95, baseType: !564, size: 64, align: 64, offset: 64)
!564 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !565, size: 64, align: 64)
!565 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !27, line: 100, baseType: !545)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !559, file: !124, line: 99, baseType: !567, size: 64, align: 64, offset: 128)
!567 = !DICompositeType(tag: DW_TAG_union_type, scope: !559, file: !124, line: 96, size: 64, align: 64, elements: !568)
!568 = !{!569, !570}
!569 = !DIDerivedType(tag: DW_TAG_member, name: "whatever", scope: !567, file: !124, line: 97, baseType: !148, size: 64, align: 64)
!570 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !567, file: !124, line: 98, baseType: !554, size: 32, align: 32)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "sockets", scope: !545, file: !130, line: 1817, baseType: !572, size: 160, align: 32, offset: 448)
!572 = !DICompositeType(tag: DW_TAG_array_type, baseType: !248, size: 160, align: 32, elements: !573)
!573 = !{!574}
!574 = !DISubrange(count: 5)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "numsocks", scope: !545, file: !130, line: 1818, baseType: !177, size: 32, align: 32, offset: 608)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "dns", scope: !545, file: !130, line: 1820, baseType: !131, size: 128, align: 64, offset: 640)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "multi", scope: !545, file: !130, line: 1821, baseType: !578, size: 64, align: 64, offset: 768)
!578 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !579, size: 64, align: 64)
!579 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_multi", file: !4, line: 70, size: 3840, align: 64, elements: !580)
!580 = !{!581, !582, !583, !584, !585, !586, !587, !588, !593, !594, !601, !602, !603, !614, !615, !616, !617, !625, !626, !627, !628, !629, !630, !631, !632, !633, !634, !641, !642}
!581 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !579, file: !4, line: 73, baseType: !191, size: 64, align: 64)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "easyp", scope: !579, file: !4, line: 76, baseType: !544, size: 64, align: 64, offset: 64)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "easylp", scope: !579, file: !4, line: 77, baseType: !544, size: 64, align: 64, offset: 128)
!584 = !DIDerivedType(tag: DW_TAG_member, name: "num_easy", scope: !579, file: !4, line: 79, baseType: !177, size: 32, align: 32, offset: 192)
!585 = !DIDerivedType(tag: DW_TAG_member, name: "num_alive", scope: !579, file: !4, line: 80, baseType: !177, size: 32, align: 32, offset: 224)
!586 = !DIDerivedType(tag: DW_TAG_member, name: "msglist", scope: !579, file: !4, line: 83, baseType: !140, size: 256, align: 64, offset: 256)
!587 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !579, file: !4, line: 85, baseType: !140, size: 256, align: 64, offset: 512)
!588 = !DIDerivedType(tag: DW_TAG_member, name: "socket_cb", scope: !579, file: !4, line: 89, baseType: !589, size: 64, align: 64, offset: 768)
!589 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_callback", file: !124, line: 268, baseType: !590)
!590 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !591, size: 64, align: 64)
!591 = !DISubroutineType(types: !592)
!592 = !{!177, !564, !248, !177, !148, !148}
!593 = !DIDerivedType(tag: DW_TAG_member, name: "socket_userp", scope: !579, file: !4, line: 90, baseType: !148, size: 64, align: 64, offset: 832)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "push_cb", scope: !579, file: !4, line: 93, baseType: !595, size: 64, align: 64, offset: 896)
!595 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_push_callback", file: !124, line: 429, baseType: !596)
!596 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !597, size: 64, align: 64)
!597 = !DISubroutineType(types: !598)
!598 = !{!177, !564, !564, !158, !599, !148}
!599 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !600, size: 64, align: 64)
!600 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_pushheaders", file: !124, line: 422, flags: DIFlagFwdDecl)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "push_userp", scope: !579, file: !4, line: 94, baseType: !148, size: 64, align: 64, offset: 960)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !579, file: !4, line: 97, baseType: !135, size: 384, align: 64, offset: 1024)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "timetree", scope: !579, file: !4, line: 101, baseType: !604, size: 64, align: 64, offset: 1408)
!604 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !605, size: 64, align: 64)
!605 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_tree", file: !606, line: 26, size: 448, align: 64, elements: !607)
!606 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!607 = !{!608, !609, !610, !611, !612, !613}
!608 = !DIDerivedType(tag: DW_TAG_member, name: "smaller", scope: !605, file: !606, line: 27, baseType: !604, size: 64, align: 64)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "larger", scope: !605, file: !606, line: 28, baseType: !604, size: 64, align: 64, offset: 64)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "samen", scope: !605, file: !606, line: 29, baseType: !604, size: 64, align: 64, offset: 128)
!611 = !DIDerivedType(tag: DW_TAG_member, name: "samep", scope: !605, file: !606, line: 30, baseType: !604, size: 64, align: 64, offset: 192)
!612 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !605, file: !606, line: 31, baseType: !201, size: 128, align: 64, offset: 256)
!613 = !DIDerivedType(tag: DW_TAG_member, name: "payload", scope: !605, file: !606, line: 32, baseType: !148, size: 64, align: 64, offset: 384)
!614 = !DIDerivedType(tag: DW_TAG_member, name: "sockhash", scope: !579, file: !4, line: 106, baseType: !135, size: 384, align: 64, offset: 1472)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining", scope: !579, file: !4, line: 109, baseType: !191, size: 64, align: 64, offset: 1856)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "recheckstate", scope: !579, file: !4, line: 111, baseType: !211, size: 8, align: 8, offset: 1920)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !579, file: !4, line: 114, baseType: !618, size: 640, align: 64, offset: 1984)
!618 = !DICompositeType(tag: DW_TAG_structure_type, name: "conncache", file: !619, line: 26, size: 640, align: 64, elements: !620)
!619 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/conncache.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!620 = !{!621, !622, !623, !624}
!621 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !618, file: !619, line: 27, baseType: !135, size: 384, align: 64)
!622 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !618, file: !619, line: 28, baseType: !158, size: 64, align: 64, offset: 384)
!623 = !DIDerivedType(tag: DW_TAG_member, name: "next_connection_id", scope: !618, file: !619, line: 29, baseType: !191, size: 64, align: 64, offset: 448)
!624 = !DIDerivedType(tag: DW_TAG_member, name: "last_cleanup", scope: !618, file: !619, line: 30, baseType: !201, size: 128, align: 64, offset: 512)
!625 = !DIDerivedType(tag: DW_TAG_member, name: "closure_handle", scope: !579, file: !4, line: 118, baseType: !544, size: 64, align: 64, offset: 2624)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !579, file: !4, line: 120, baseType: !191, size: 64, align: 64, offset: 2688)
!627 = !DIDerivedType(tag: DW_TAG_member, name: "max_host_connections", scope: !579, file: !4, line: 123, baseType: !191, size: 64, align: 64, offset: 2752)
!628 = !DIDerivedType(tag: DW_TAG_member, name: "max_total_connections", scope: !579, file: !4, line: 126, baseType: !191, size: 64, align: 64, offset: 2816)
!629 = !DIDerivedType(tag: DW_TAG_member, name: "max_pipeline_length", scope: !579, file: !4, line: 129, baseType: !191, size: 64, align: 64, offset: 2880)
!630 = !DIDerivedType(tag: DW_TAG_member, name: "content_length_penalty_size", scope: !579, file: !4, line: 132, baseType: !191, size: 64, align: 64, offset: 2944)
!631 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_length_penalty_size", scope: !579, file: !4, line: 137, baseType: !191, size: 64, align: 64, offset: 3008)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_site_bl", scope: !579, file: !4, line: 141, baseType: !140, size: 256, align: 64, offset: 3072)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_server_bl", scope: !579, file: !4, line: 144, baseType: !140, size: 256, align: 64, offset: 3328)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !579, file: !4, line: 148, baseType: !635, size: 64, align: 64, offset: 3584)
!635 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_multi_timer_callback", file: !124, line: 285, baseType: !636)
!636 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !637, size: 64, align: 64)
!637 = !DISubroutineType(types: !638)
!638 = !{!177, !639, !191, !148}
!639 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !640, size: 64, align: 64)
!640 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLM", file: !124, line: 56, baseType: !579)
!641 = !DIDerivedType(tag: DW_TAG_member, name: "timer_userp", scope: !579, file: !4, line: 149, baseType: !148, size: 64, align: 64, offset: 3648)
!642 = !DIDerivedType(tag: DW_TAG_member, name: "timer_lastcall", scope: !579, file: !4, line: 150, baseType: !201, size: 128, align: 64, offset: 3712)
!643 = !DIDerivedType(tag: DW_TAG_member, name: "multi_easy", scope: !545, file: !130, line: 1824, baseType: !578, size: 64, align: 64, offset: 832)
!644 = !DIDerivedType(tag: DW_TAG_member, name: "share", scope: !545, file: !130, line: 1827, baseType: !645, size: 64, align: 64, offset: 896)
!645 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !646, size: 64, align: 64)
!646 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !27, line: 101, flags: DIFlagFwdDecl)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "req", scope: !545, file: !130, line: 1828, baseType: !186, size: 2496, align: 64, offset: 960)
!648 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !545, file: !130, line: 1829, baseType: !649, size: 13760, align: 64, offset: 3456)
!649 = !DICompositeType(tag: DW_TAG_structure_type, name: "UserDefined", file: !130, line: 1558, size: 13760, align: 64, elements: !650)
!650 = !{!651, !706, !707, !708, !709, !710, !711, !712, !713, !714, !715, !716, !717, !718, !719, !720, !721, !726, !727, !728, !729, !734, !735, !736, !738, !739, !740, !746, !751, !757, !763, !769, !770, !794, !795, !800, !801, !802, !807, !808, !809, !810, !811, !812, !813, !814, !815, !816, !817, !818, !819, !820, !821, !822, !823, !829, !830, !848, !849, !850, !851, !852, !853, !854, !855, !856, !857, !858, !859, !860, !862, !863, !865, !866, !902, !903, !907, !909, !910, !911, !912, !913, !914, !915, !917, !918, !932, !933, !934, !935, !936, !937, !938, !939, !940, !941, !942, !943, !944, !945, !946, !947, !948, !949, !950, !951, !952, !953, !954, !955, !956, !957, !958, !959, !961, !963, !965, !966, !967, !968, !969, !970, !971, !972, !973, !974, !975, !976, !977, !981, !982, !983, !984, !985, !986, !988, !989, !990, !997, !1002, !1007, !1008, !1009, !1010, !1011, !1012, !1013, !1014, !1015, !1016, !1017, !1018, !1019, !1020, !1021, !1022, !1023, !1029}
!651 = !DIDerivedType(tag: DW_TAG_member, name: "err", scope: !649, file: !130, line: 1559, baseType: !652, size: 64, align: 64)
!652 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !653, size: 64, align: 64)
!653 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !654, line: 48, baseType: !655)
!654 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!655 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !656, line: 245, size: 1728, align: 64, elements: !657)
!656 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!657 = !{!658, !659, !660, !661, !662, !663, !664, !665, !666, !667, !668, !669, !670, !678, !679, !680, !681, !683, !685, !687, !691, !694, !696, !697, !698, !699, !700, !701, !702}
!658 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !655, file: !656, line: 246, baseType: !177, size: 32, align: 32)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !655, file: !656, line: 251, baseType: !215, size: 64, align: 64, offset: 64)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !655, file: !656, line: 252, baseType: !215, size: 64, align: 64, offset: 128)
!661 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !655, file: !656, line: 253, baseType: !215, size: 64, align: 64, offset: 192)
!662 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !655, file: !656, line: 254, baseType: !215, size: 64, align: 64, offset: 256)
!663 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !655, file: !656, line: 255, baseType: !215, size: 64, align: 64, offset: 320)
!664 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !655, file: !656, line: 256, baseType: !215, size: 64, align: 64, offset: 384)
!665 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !655, file: !656, line: 257, baseType: !215, size: 64, align: 64, offset: 448)
!666 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !655, file: !656, line: 258, baseType: !215, size: 64, align: 64, offset: 512)
!667 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !655, file: !656, line: 260, baseType: !215, size: 64, align: 64, offset: 576)
!668 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !655, file: !656, line: 261, baseType: !215, size: 64, align: 64, offset: 640)
!669 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !655, file: !656, line: 262, baseType: !215, size: 64, align: 64, offset: 704)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !655, file: !656, line: 264, baseType: !671, size: 64, align: 64, offset: 768)
!671 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !672, size: 64, align: 64)
!672 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !656, line: 160, size: 192, align: 64, elements: !673)
!673 = !{!674, !675, !677}
!674 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !672, file: !656, line: 161, baseType: !671, size: 64, align: 64)
!675 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !672, file: !656, line: 162, baseType: !676, size: 64, align: 64, offset: 64)
!676 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !655, size: 64, align: 64)
!677 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !672, file: !656, line: 166, baseType: !177, size: 32, align: 32, offset: 128)
!678 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !655, file: !656, line: 266, baseType: !676, size: 64, align: 64, offset: 832)
!679 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !655, file: !656, line: 268, baseType: !177, size: 32, align: 32, offset: 896)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !655, file: !656, line: 272, baseType: !177, size: 32, align: 32, offset: 928)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !655, file: !656, line: 274, baseType: !682, size: 64, align: 64, offset: 960)
!682 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !206, line: 131, baseType: !191)
!683 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !655, file: !656, line: 278, baseType: !684, size: 16, align: 16, offset: 1024)
!684 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!685 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !655, file: !656, line: 279, baseType: !686, size: 8, align: 8, offset: 1040)
!686 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!687 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !655, file: !656, line: 280, baseType: !688, size: 8, align: 8, offset: 1048)
!688 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 8, align: 8, elements: !689)
!689 = !{!690}
!690 = !DISubrange(count: 1)
!691 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !655, file: !656, line: 284, baseType: !692, size: 64, align: 64, offset: 1088)
!692 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !693, size: 64, align: 64)
!693 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !656, line: 154, baseType: null)
!694 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !655, file: !656, line: 293, baseType: !695, size: 64, align: 64, offset: 1152)
!695 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !206, line: 132, baseType: !191)
!696 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !655, file: !656, line: 302, baseType: !148, size: 64, align: 64, offset: 1216)
!697 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !655, file: !656, line: 303, baseType: !148, size: 64, align: 64, offset: 1280)
!698 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !655, file: !656, line: 304, baseType: !148, size: 64, align: 64, offset: 1344)
!699 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !655, file: !656, line: 305, baseType: !148, size: 64, align: 64, offset: 1408)
!700 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !655, file: !656, line: 306, baseType: !158, size: 64, align: 64, offset: 1472)
!701 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !655, file: !656, line: 308, baseType: !177, size: 32, align: 32, offset: 1536)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !655, file: !656, line: 310, baseType: !703, size: 160, align: 8, offset: 1568)
!703 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 160, align: 8, elements: !704)
!704 = !{!705}
!705 = !DISubrange(count: 20)
!706 = !DIDerivedType(tag: DW_TAG_member, name: "debugdata", scope: !649, file: !130, line: 1560, baseType: !148, size: 64, align: 64, offset: 64)
!707 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuffer", scope: !649, file: !130, line: 1561, baseType: !215, size: 64, align: 64, offset: 128)
!708 = !DIDerivedType(tag: DW_TAG_member, name: "proxyport", scope: !649, file: !130, line: 1562, baseType: !191, size: 64, align: 64, offset: 192)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !649, file: !130, line: 1565, baseType: !148, size: 64, align: 64, offset: 256)
!710 = !DIDerivedType(tag: DW_TAG_member, name: "in_set", scope: !649, file: !130, line: 1566, baseType: !148, size: 64, align: 64, offset: 320)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "writeheader", scope: !649, file: !130, line: 1567, baseType: !148, size: 64, align: 64, offset: 384)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_out", scope: !649, file: !130, line: 1568, baseType: !148, size: 64, align: 64, offset: 448)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "use_port", scope: !649, file: !130, line: 1569, baseType: !191, size: 64, align: 64, offset: 512)
!714 = !DIDerivedType(tag: DW_TAG_member, name: "httpauth", scope: !649, file: !130, line: 1570, baseType: !160, size: 64, align: 64, offset: 576)
!715 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauth", scope: !649, file: !130, line: 1571, baseType: !160, size: 64, align: 64, offset: 640)
!716 = !DIDerivedType(tag: DW_TAG_member, name: "followlocation", scope: !649, file: !130, line: 1572, baseType: !191, size: 64, align: 64, offset: 704)
!717 = !DIDerivedType(tag: DW_TAG_member, name: "maxredirs", scope: !649, file: !130, line: 1573, baseType: !191, size: 64, align: 64, offset: 768)
!718 = !DIDerivedType(tag: DW_TAG_member, name: "keep_post", scope: !649, file: !130, line: 1576, baseType: !177, size: 32, align: 32, offset: 832)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "free_referer", scope: !649, file: !130, line: 1578, baseType: !211, size: 8, align: 8, offset: 864)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "postfields", scope: !649, file: !130, line: 1580, baseType: !148, size: 64, align: 64, offset: 896)
!721 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !649, file: !130, line: 1581, baseType: !722, size: 64, align: 64, offset: 960)
!722 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !27, line: 324, baseType: !723)
!723 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !724, size: 64, align: 64)
!724 = !DISubroutineType(types: !725)
!725 = !{!177, !148, !189, !177}
!726 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !649, file: !130, line: 1582, baseType: !189, size: 64, align: 64, offset: 1024)
!727 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !649, file: !130, line: 1585, baseType: !684, size: 16, align: 16, offset: 1088)
!728 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !649, file: !130, line: 1586, baseType: !177, size: 32, align: 32, offset: 1120)
!729 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !649, file: !130, line: 1588, baseType: !730, size: 64, align: 64, offset: 1152)
!730 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !27, line: 223, baseType: !731)
!731 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !732, size: 64, align: 64)
!732 = !DISubroutineType(types: !733)
!733 = !{!158, !215, !158, !158, !148}
!734 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !649, file: !130, line: 1589, baseType: !730, size: 64, align: 64, offset: 1216)
!735 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !649, file: !130, line: 1590, baseType: !730, size: 64, align: 64, offset: 1280)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !649, file: !130, line: 1591, baseType: !737, size: 64, align: 64, offset: 1344)
!737 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !27, line: 335, baseType: !731)
!738 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !649, file: !130, line: 1592, baseType: !177, size: 32, align: 32, offset: 1408)
!739 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !649, file: !130, line: 1593, baseType: !177, size: 32, align: 32, offset: 1440)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !649, file: !130, line: 1594, baseType: !741, size: 64, align: 64, offset: 1472)
!741 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !27, line: 183, baseType: !742)
!742 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !743, size: 64, align: 64)
!743 = !DISubroutineType(types: !744)
!744 = !{!177, !148, !745, !745, !745, !745}
!745 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!746 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !649, file: !130, line: 1595, baseType: !747, size: 64, align: 64, offset: 1536)
!747 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !27, line: 191, baseType: !748)
!748 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !749, size: 64, align: 64)
!749 = !DISubroutineType(types: !750)
!750 = !{!177, !148, !189, !189, !189, !189}
!751 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !649, file: !130, line: 1596, baseType: !752, size: 64, align: 64, offset: 1600)
!752 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !27, line: 420, baseType: !753)
!753 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !754, size: 64, align: 64)
!754 = !DISubroutineType(types: !755)
!755 = !{!177, !564, !756, !215, !158, !148}
!756 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !27, line: 418, baseType: !269)
!757 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !649, file: !130, line: 1597, baseType: !758, size: 64, align: 64, offset: 1664)
!758 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !27, line: 388, baseType: !759)
!759 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !760, size: 64, align: 64)
!760 = !DISubroutineType(types: !761)
!761 = !{!762, !564, !177, !148}
!762 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !27, line: 380, baseType: !279)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !649, file: !130, line: 1598, baseType: !764, size: 64, align: 64, offset: 1728)
!764 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !27, line: 353, baseType: !765)
!765 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !766, size: 64, align: 64)
!766 = !DISubroutineType(types: !767)
!767 = !{!177, !148, !248, !768}
!768 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !27, line: 344, baseType: !285)
!769 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !649, file: !130, line: 1599, baseType: !148, size: 64, align: 64, offset: 1792)
!770 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !649, file: !130, line: 1600, baseType: !771, size: 64, align: 64, offset: 1856)
!771 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !27, line: 368, baseType: !772)
!772 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !773, size: 64, align: 64)
!773 = !DISubroutineType(types: !774)
!774 = !{!248, !148, !768, !775}
!775 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !776, size: 64, align: 64)
!776 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !27, line: 357, size: 256, align: 32, elements: !777)
!777 = !{!778, !779, !780, !781, !783}
!778 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !776, file: !27, line: 358, baseType: !177, size: 32, align: 32)
!779 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !776, file: !27, line: 359, baseType: !177, size: 32, align: 32, offset: 32)
!780 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !776, file: !27, line: 360, baseType: !177, size: 32, align: 32, offset: 64)
!781 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !776, file: !27, line: 361, baseType: !782, size: 32, align: 32, offset: 96)
!782 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!783 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !776, file: !27, line: 364, baseType: !784, size: 128, align: 16, offset: 128)
!784 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !785, line: 149, size: 128, align: 16, elements: !786)
!785 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!786 = !{!787, !790}
!787 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !784, file: !785, line: 151, baseType: !788, size: 16, align: 16)
!788 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !789, line: 28, baseType: !684)
!789 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!790 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !784, file: !785, line: 152, baseType: !791, size: 112, align: 8, offset: 16)
!791 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 112, align: 8, elements: !792)
!792 = !{!793}
!793 = !DISubrange(count: 14)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "opensocket_client", scope: !649, file: !130, line: 1603, baseType: !148, size: 64, align: 64, offset: 1920)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !649, file: !130, line: 1604, baseType: !796, size: 64, align: 64, offset: 1984)
!796 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !27, line: 373, baseType: !797)
!797 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !798, size: 64, align: 64)
!798 = !DISubroutineType(types: !799)
!799 = !{!177, !148, !248}
!800 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !649, file: !130, line: 1606, baseType: !148, size: 64, align: 64, offset: 2048)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !649, file: !130, line: 1608, baseType: !148, size: 64, align: 64, offset: 2112)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !649, file: !130, line: 1611, baseType: !803, size: 64, align: 64, offset: 2176)
!803 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !27, line: 637, baseType: !804)
!804 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !805, size: 64, align: 64)
!805 = !DISubroutineType(types: !806)
!806 = !{!554, !215, !158}
!807 = !DIDerivedType(tag: DW_TAG_member, name: "convtonetwork", scope: !649, file: !130, line: 1613, baseType: !803, size: 64, align: 64, offset: 2240)
!808 = !DIDerivedType(tag: DW_TAG_member, name: "convfromutf8", scope: !649, file: !130, line: 1615, baseType: !803, size: 64, align: 64, offset: 2304)
!809 = !DIDerivedType(tag: DW_TAG_member, name: "progress_client", scope: !649, file: !130, line: 1617, baseType: !148, size: 64, align: 64, offset: 2368)
!810 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_client", scope: !649, file: !130, line: 1618, baseType: !148, size: 64, align: 64, offset: 2432)
!811 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !649, file: !130, line: 1619, baseType: !191, size: 64, align: 64, offset: 2496)
!812 = !DIDerivedType(tag: DW_TAG_member, name: "connecttimeout", scope: !649, file: !130, line: 1620, baseType: !191, size: 64, align: 64, offset: 2560)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "accepttimeout", scope: !649, file: !130, line: 1621, baseType: !191, size: 64, align: 64, offset: 2624)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "server_response_timeout", scope: !649, file: !130, line: 1622, baseType: !191, size: 64, align: 64, offset: 2688)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_blksize", scope: !649, file: !130, line: 1623, baseType: !191, size: 64, align: 64, offset: 2752)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_no_options", scope: !649, file: !130, line: 1624, baseType: !211, size: 8, align: 8, offset: 2816)
!817 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !649, file: !130, line: 1625, baseType: !189, size: 64, align: 64, offset: 2880)
!818 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_limit", scope: !649, file: !130, line: 1626, baseType: !191, size: 64, align: 64, offset: 2944)
!819 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_time", scope: !649, file: !130, line: 1627, baseType: !191, size: 64, align: 64, offset: 3008)
!820 = !DIDerivedType(tag: DW_TAG_member, name: "max_send_speed", scope: !649, file: !130, line: 1628, baseType: !189, size: 64, align: 64, offset: 3072)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "max_recv_speed", scope: !649, file: !130, line: 1629, baseType: !189, size: 64, align: 64, offset: 3136)
!822 = !DIDerivedType(tag: DW_TAG_member, name: "set_resume_from", scope: !649, file: !130, line: 1631, baseType: !189, size: 64, align: 64, offset: 3200)
!823 = !DIDerivedType(tag: DW_TAG_member, name: "headers", scope: !649, file: !130, line: 1632, baseType: !824, size: 64, align: 64, offset: 3264)
!824 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !825, size: 64, align: 64)
!825 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !27, line: 2176, size: 128, align: 64, elements: !826)
!826 = !{!827, !828}
!827 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !825, file: !27, line: 2177, baseType: !215, size: 64, align: 64)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !825, file: !27, line: 2178, baseType: !824, size: 64, align: 64, offset: 64)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !649, file: !130, line: 1633, baseType: !824, size: 64, align: 64, offset: 3328)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !649, file: !130, line: 1634, baseType: !831, size: 64, align: 64, offset: 3392)
!831 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !832, size: 64, align: 64)
!832 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !27, line: 137, size: 896, align: 64, elements: !833)
!833 = !{!834, !835, !836, !837, !838, !839, !840, !841, !842, !843, !844, !845, !846, !847}
!834 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !832, file: !27, line: 138, baseType: !831, size: 64, align: 64)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !832, file: !27, line: 139, baseType: !215, size: 64, align: 64, offset: 64)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !832, file: !27, line: 140, baseType: !191, size: 64, align: 64, offset: 128)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !832, file: !27, line: 141, baseType: !215, size: 64, align: 64, offset: 192)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !832, file: !27, line: 142, baseType: !191, size: 64, align: 64, offset: 256)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !832, file: !27, line: 144, baseType: !215, size: 64, align: 64, offset: 320)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !832, file: !27, line: 145, baseType: !191, size: 64, align: 64, offset: 384)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !832, file: !27, line: 146, baseType: !215, size: 64, align: 64, offset: 448)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !832, file: !27, line: 147, baseType: !824, size: 64, align: 64, offset: 512)
!843 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !832, file: !27, line: 148, baseType: !831, size: 64, align: 64, offset: 576)
!844 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !832, file: !27, line: 151, baseType: !191, size: 64, align: 64, offset: 640)
!845 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !832, file: !27, line: 171, baseType: !215, size: 64, align: 64, offset: 704)
!846 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !832, file: !27, line: 174, baseType: !148, size: 64, align: 64, offset: 768)
!847 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !832, file: !27, line: 176, baseType: !189, size: 64, align: 64, offset: 832)
!848 = !DIDerivedType(tag: DW_TAG_member, name: "sep_headers", scope: !649, file: !130, line: 1635, baseType: !211, size: 8, align: 8, offset: 3456)
!849 = !DIDerivedType(tag: DW_TAG_member, name: "cookiesession", scope: !649, file: !130, line: 1636, baseType: !211, size: 8, align: 8, offset: 3464)
!850 = !DIDerivedType(tag: DW_TAG_member, name: "crlf", scope: !649, file: !130, line: 1637, baseType: !211, size: 8, align: 8, offset: 3472)
!851 = !DIDerivedType(tag: DW_TAG_member, name: "quote", scope: !649, file: !130, line: 1638, baseType: !824, size: 64, align: 64, offset: 3520)
!852 = !DIDerivedType(tag: DW_TAG_member, name: "postquote", scope: !649, file: !130, line: 1639, baseType: !824, size: 64, align: 64, offset: 3584)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "prequote", scope: !649, file: !130, line: 1640, baseType: !824, size: 64, align: 64, offset: 3648)
!854 = !DIDerivedType(tag: DW_TAG_member, name: "source_quote", scope: !649, file: !130, line: 1641, baseType: !824, size: 64, align: 64, offset: 3712)
!855 = !DIDerivedType(tag: DW_TAG_member, name: "source_prequote", scope: !649, file: !130, line: 1642, baseType: !824, size: 64, align: 64, offset: 3776)
!856 = !DIDerivedType(tag: DW_TAG_member, name: "source_postquote", scope: !649, file: !130, line: 1644, baseType: !824, size: 64, align: 64, offset: 3840)
!857 = !DIDerivedType(tag: DW_TAG_member, name: "telnet_options", scope: !649, file: !130, line: 1646, baseType: !824, size: 64, align: 64, offset: 3904)
!858 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !649, file: !130, line: 1647, baseType: !824, size: 64, align: 64, offset: 3968)
!859 = !DIDerivedType(tag: DW_TAG_member, name: "connect_to", scope: !649, file: !130, line: 1649, baseType: !824, size: 64, align: 64, offset: 4032)
!860 = !DIDerivedType(tag: DW_TAG_member, name: "timecondition", scope: !649, file: !130, line: 1651, baseType: !861, size: 32, align: 32, offset: 4096)
!861 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !27, line: 1929, baseType: !290)
!862 = !DIDerivedType(tag: DW_TAG_member, name: "timevalue", scope: !649, file: !130, line: 1652, baseType: !242, size: 64, align: 64, offset: 4160)
!863 = !DIDerivedType(tag: DW_TAG_member, name: "httpreq", scope: !649, file: !130, line: 1653, baseType: !864, size: 32, align: 32, offset: 4224)
!864 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_HttpReq", file: !130, line: 1249, baseType: !297)
!865 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !649, file: !130, line: 1654, baseType: !191, size: 64, align: 64, offset: 4288)
!866 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !649, file: !130, line: 1656, baseType: !867, size: 1408, align: 64, offset: 4352)
!867 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_config_data", file: !130, line: 366, size: 1408, align: 64, elements: !868)
!868 = !{!869, !884, !885, !886, !887, !888, !889, !894, !895, !896, !897, !898, !899, !900, !901}
!869 = !DIDerivedType(tag: DW_TAG_member, name: "primary", scope: !867, file: !130, line: 367, baseType: !870, size: 640, align: 64)
!870 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !130, line: 351, size: 640, align: 64, elements: !871)
!871 = !{!872, !873, !874, !875, !876, !877, !878, !879, !880, !881, !882, !883}
!872 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !870, file: !130, line: 352, baseType: !191, size: 64, align: 64)
!873 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !870, file: !130, line: 353, baseType: !191, size: 64, align: 64, offset: 64)
!874 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !870, file: !130, line: 354, baseType: !211, size: 8, align: 8, offset: 128)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !870, file: !130, line: 355, baseType: !211, size: 8, align: 8, offset: 136)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !870, file: !130, line: 356, baseType: !211, size: 8, align: 8, offset: 144)
!877 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !870, file: !130, line: 357, baseType: !215, size: 64, align: 64, offset: 192)
!878 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !870, file: !130, line: 358, baseType: !215, size: 64, align: 64, offset: 256)
!879 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !870, file: !130, line: 359, baseType: !215, size: 64, align: 64, offset: 320)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !870, file: !130, line: 360, baseType: !215, size: 64, align: 64, offset: 384)
!881 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !870, file: !130, line: 361, baseType: !215, size: 64, align: 64, offset: 448)
!882 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !870, file: !130, line: 362, baseType: !215, size: 64, align: 64, offset: 512)
!883 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !870, file: !130, line: 363, baseType: !211, size: 8, align: 8, offset: 576)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "enable_beast", scope: !867, file: !130, line: 368, baseType: !211, size: 8, align: 8, offset: 640)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "no_revoke", scope: !867, file: !130, line: 370, baseType: !211, size: 8, align: 8, offset: 648)
!886 = !DIDerivedType(tag: DW_TAG_member, name: "certverifyresult", scope: !867, file: !130, line: 371, baseType: !191, size: 64, align: 64, offset: 704)
!887 = !DIDerivedType(tag: DW_TAG_member, name: "CRLfile", scope: !867, file: !130, line: 372, baseType: !215, size: 64, align: 64, offset: 768)
!888 = !DIDerivedType(tag: DW_TAG_member, name: "issuercert", scope: !867, file: !130, line: 373, baseType: !215, size: 64, align: 64, offset: 832)
!889 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctx", scope: !867, file: !130, line: 374, baseType: !890, size: 64, align: 64, offset: 896)
!890 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !27, line: 639, baseType: !891)
!891 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !892, size: 64, align: 64)
!892 = !DISubroutineType(types: !893)
!893 = !{!554, !564, !148, !148}
!894 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctxp", scope: !867, file: !130, line: 375, baseType: !148, size: 64, align: 64, offset: 960)
!895 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !867, file: !130, line: 376, baseType: !211, size: 8, align: 8, offset: 1024)
!896 = !DIDerivedType(tag: DW_TAG_member, name: "falsestart", scope: !867, file: !130, line: 377, baseType: !211, size: 8, align: 8, offset: 1032)
!897 = !DIDerivedType(tag: DW_TAG_member, name: "cert", scope: !867, file: !130, line: 379, baseType: !215, size: 64, align: 64, offset: 1088)
!898 = !DIDerivedType(tag: DW_TAG_member, name: "cert_type", scope: !867, file: !130, line: 380, baseType: !215, size: 64, align: 64, offset: 1152)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !867, file: !130, line: 381, baseType: !215, size: 64, align: 64, offset: 1216)
!900 = !DIDerivedType(tag: DW_TAG_member, name: "key_type", scope: !867, file: !130, line: 382, baseType: !215, size: 64, align: 64, offset: 1280)
!901 = !DIDerivedType(tag: DW_TAG_member, name: "key_passwd", scope: !867, file: !130, line: 383, baseType: !215, size: 64, align: 64, offset: 1344)
!902 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !649, file: !130, line: 1657, baseType: !867, size: 1408, align: 64, offset: 5760)
!903 = !DIDerivedType(tag: DW_TAG_member, name: "general_ssl", scope: !649, file: !130, line: 1658, baseType: !904, size: 64, align: 64, offset: 7168)
!904 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_general_config", file: !130, line: 392, size: 64, align: 64, elements: !905)
!905 = !{!906}
!906 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !904, file: !130, line: 393, baseType: !158, size: 64, align: 64)
!907 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !649, file: !130, line: 1659, baseType: !908, size: 32, align: 32, offset: 7232)
!908 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !27, line: 657, baseType: !307)
!909 = !DIDerivedType(tag: DW_TAG_member, name: "dns_cache_timeout", scope: !649, file: !130, line: 1660, baseType: !191, size: 64, align: 64, offset: 7296)
!910 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !649, file: !130, line: 1661, baseType: !191, size: 64, align: 64, offset: 7360)
!911 = !DIDerivedType(tag: DW_TAG_member, name: "private_data", scope: !649, file: !130, line: 1662, baseType: !148, size: 64, align: 64, offset: 7424)
!912 = !DIDerivedType(tag: DW_TAG_member, name: "http200aliases", scope: !649, file: !130, line: 1664, baseType: !824, size: 64, align: 64, offset: 7488)
!913 = !DIDerivedType(tag: DW_TAG_member, name: "ipver", scope: !649, file: !130, line: 1666, baseType: !191, size: 64, align: 64, offset: 7552)
!914 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesize", scope: !649, file: !130, line: 1669, baseType: !189, size: 64, align: 64, offset: 7616)
!915 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_filemethod", scope: !649, file: !130, line: 1671, baseType: !916, size: 32, align: 32, offset: 7680)
!916 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpfile", file: !317, line: 98, baseType: !316)
!917 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_create_missing_dirs", scope: !649, file: !130, line: 1673, baseType: !177, size: 32, align: 32, offset: 7712)
!918 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc", scope: !649, file: !130, line: 1677, baseType: !919, size: 64, align: 64, offset: 7744)
!919 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !27, line: 739, baseType: !920)
!920 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !921, size: 64, align: 64)
!921 = !DISubroutineType(types: !922)
!922 = !{!177, !564, !923, !923, !328, !148}
!923 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !924, size: 64, align: 64)
!924 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !925)
!925 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !27, line: 711, size: 192, align: 64, elements: !926)
!926 = !{!927, !930, !931}
!927 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !925, file: !27, line: 712, baseType: !928, size: 64, align: 64)
!928 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !929, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !216)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !925, file: !27, line: 714, baseType: !158, size: 64, align: 64, offset: 64)
!931 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !925, file: !27, line: 715, baseType: !322, size: 32, align: 32, offset: 128)
!932 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc_userp", scope: !649, file: !130, line: 1678, baseType: !148, size: 64, align: 64, offset: 7808)
!933 = !DIDerivedType(tag: DW_TAG_member, name: "printhost", scope: !649, file: !130, line: 1684, baseType: !211, size: 8, align: 8, offset: 7872)
!934 = !DIDerivedType(tag: DW_TAG_member, name: "get_filetime", scope: !649, file: !130, line: 1685, baseType: !211, size: 8, align: 8, offset: 7880)
!935 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_thru_httpproxy", scope: !649, file: !130, line: 1686, baseType: !211, size: 8, align: 8, offset: 7888)
!936 = !DIDerivedType(tag: DW_TAG_member, name: "prefer_ascii", scope: !649, file: !130, line: 1687, baseType: !211, size: 8, align: 8, offset: 7896)
!937 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_append", scope: !649, file: !130, line: 1688, baseType: !211, size: 8, align: 8, offset: 7904)
!938 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_list_only", scope: !649, file: !130, line: 1689, baseType: !211, size: 8, align: 8, offset: 7912)
!939 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_port", scope: !649, file: !130, line: 1690, baseType: !211, size: 8, align: 8, offset: 7920)
!940 = !DIDerivedType(tag: DW_TAG_member, name: "hide_progress", scope: !649, file: !130, line: 1691, baseType: !211, size: 8, align: 8, offset: 7928)
!941 = !DIDerivedType(tag: DW_TAG_member, name: "http_fail_on_error", scope: !649, file: !130, line: 1692, baseType: !211, size: 8, align: 8, offset: 7936)
!942 = !DIDerivedType(tag: DW_TAG_member, name: "http_keep_sending_on_error", scope: !649, file: !130, line: 1693, baseType: !211, size: 8, align: 8, offset: 7944)
!943 = !DIDerivedType(tag: DW_TAG_member, name: "http_follow_location", scope: !649, file: !130, line: 1694, baseType: !211, size: 8, align: 8, offset: 7952)
!944 = !DIDerivedType(tag: DW_TAG_member, name: "http_transfer_encoding", scope: !649, file: !130, line: 1695, baseType: !211, size: 8, align: 8, offset: 7960)
!945 = !DIDerivedType(tag: DW_TAG_member, name: "http_disable_hostname_check_before_authentication", scope: !649, file: !130, line: 1696, baseType: !211, size: 8, align: 8, offset: 7968)
!946 = !DIDerivedType(tag: DW_TAG_member, name: "include_header", scope: !649, file: !130, line: 1697, baseType: !211, size: 8, align: 8, offset: 7976)
!947 = !DIDerivedType(tag: DW_TAG_member, name: "http_set_referer", scope: !649, file: !130, line: 1698, baseType: !211, size: 8, align: 8, offset: 7984)
!948 = !DIDerivedType(tag: DW_TAG_member, name: "http_auto_referer", scope: !649, file: !130, line: 1699, baseType: !211, size: 8, align: 8, offset: 7992)
!949 = !DIDerivedType(tag: DW_TAG_member, name: "opt_no_body", scope: !649, file: !130, line: 1700, baseType: !211, size: 8, align: 8, offset: 8000)
!950 = !DIDerivedType(tag: DW_TAG_member, name: "upload", scope: !649, file: !130, line: 1701, baseType: !211, size: 8, align: 8, offset: 8008)
!951 = !DIDerivedType(tag: DW_TAG_member, name: "use_netrc", scope: !649, file: !130, line: 1703, baseType: !334, size: 32, align: 32, offset: 8032)
!952 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !649, file: !130, line: 1704, baseType: !211, size: 8, align: 8, offset: 8064)
!953 = !DIDerivedType(tag: DW_TAG_member, name: "krb", scope: !649, file: !130, line: 1705, baseType: !211, size: 8, align: 8, offset: 8072)
!954 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_forbid", scope: !649, file: !130, line: 1706, baseType: !211, size: 8, align: 8, offset: 8080)
!955 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_fresh", scope: !649, file: !130, line: 1707, baseType: !211, size: 8, align: 8, offset: 8088)
!956 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !649, file: !130, line: 1708, baseType: !211, size: 8, align: 8, offset: 8096)
!957 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !649, file: !130, line: 1709, baseType: !211, size: 8, align: 8, offset: 8104)
!958 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_pret", scope: !649, file: !130, line: 1710, baseType: !211, size: 8, align: 8, offset: 8112)
!959 = !DIDerivedType(tag: DW_TAG_member, name: "use_ssl", scope: !649, file: !130, line: 1712, baseType: !960, size: 32, align: 32, offset: 8128)
!960 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !27, line: 752, baseType: !340)
!961 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !649, file: !130, line: 1714, baseType: !962, size: 32, align: 32, offset: 8160)
!962 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !27, line: 795, baseType: !347)
!963 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !649, file: !130, line: 1715, baseType: !964, size: 32, align: 32, offset: 8192)
!964 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !27, line: 787, baseType: !353)
!965 = !DIDerivedType(tag: DW_TAG_member, name: "no_signal", scope: !649, file: !130, line: 1716, baseType: !211, size: 8, align: 8, offset: 8224)
!966 = !DIDerivedType(tag: DW_TAG_member, name: "global_dns_cache", scope: !649, file: !130, line: 1717, baseType: !211, size: 8, align: 8, offset: 8232)
!967 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_nodelay", scope: !649, file: !130, line: 1718, baseType: !211, size: 8, align: 8, offset: 8240)
!968 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !649, file: !130, line: 1719, baseType: !211, size: 8, align: 8, offset: 8248)
!969 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_skip_ip", scope: !649, file: !130, line: 1720, baseType: !211, size: 8, align: 8, offset: 8256)
!970 = !DIDerivedType(tag: DW_TAG_member, name: "connect_only", scope: !649, file: !130, line: 1722, baseType: !211, size: 8, align: 8, offset: 8264)
!971 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_auth_types", scope: !649, file: !130, line: 1723, baseType: !191, size: 64, align: 64, offset: 8320)
!972 = !DIDerivedType(tag: DW_TAG_member, name: "http_te_skip", scope: !649, file: !130, line: 1724, baseType: !211, size: 8, align: 8, offset: 8384)
!973 = !DIDerivedType(tag: DW_TAG_member, name: "http_ce_skip", scope: !649, file: !130, line: 1726, baseType: !211, size: 8, align: 8, offset: 8392)
!974 = !DIDerivedType(tag: DW_TAG_member, name: "new_file_perms", scope: !649, file: !130, line: 1728, baseType: !191, size: 64, align: 64, offset: 8448)
!975 = !DIDerivedType(tag: DW_TAG_member, name: "new_directory_perms", scope: !649, file: !130, line: 1729, baseType: !191, size: 64, align: 64, offset: 8512)
!976 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_transfer_mode", scope: !649, file: !130, line: 1730, baseType: !211, size: 8, align: 8, offset: 8576)
!977 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !649, file: !130, line: 1732, baseType: !978, size: 3584, align: 64, offset: 8640)
!978 = !DICompositeType(tag: DW_TAG_array_type, baseType: !215, size: 3584, align: 64, elements: !979)
!979 = !{!980}
!980 = !DISubrange(count: 56)
!981 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !649, file: !130, line: 1733, baseType: !782, size: 32, align: 32, offset: 12224)
!982 = !DIDerivedType(tag: DW_TAG_member, name: "allowed_protocols", scope: !649, file: !130, line: 1734, baseType: !191, size: 64, align: 64, offset: 12288)
!983 = !DIDerivedType(tag: DW_TAG_member, name: "redir_protocols", scope: !649, file: !130, line: 1735, baseType: !191, size: 64, align: 64, offset: 12352)
!984 = !DIDerivedType(tag: DW_TAG_member, name: "mail_rcpt", scope: !649, file: !130, line: 1739, baseType: !824, size: 64, align: 64, offset: 12416)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "sasl_ir", scope: !649, file: !130, line: 1740, baseType: !211, size: 8, align: 8, offset: 12480)
!986 = !DIDerivedType(tag: DW_TAG_member, name: "rtspreq", scope: !649, file: !130, line: 1742, baseType: !987, size: 32, align: 32, offset: 12512)
!987 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_RtspReq", file: !130, line: 1265, baseType: !359)
!988 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !649, file: !130, line: 1743, baseType: !191, size: 64, align: 64, offset: 12544)
!989 = !DIDerivedType(tag: DW_TAG_member, name: "wildcardmatch", scope: !649, file: !130, line: 1744, baseType: !211, size: 8, align: 8, offset: 12608)
!990 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_bgn", scope: !649, file: !130, line: 1745, baseType: !991, size: 64, align: 64, offset: 12672)
!991 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !27, line: 292, baseType: !992)
!992 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !993, size: 64, align: 64)
!993 = !DISubroutineType(types: !994)
!994 = !{!191, !995, !148, !177}
!995 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !996, size: 64, align: 64)
!996 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!997 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !649, file: !130, line: 1747, baseType: !998, size: 64, align: 64, offset: 12736)
!998 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !27, line: 306, baseType: !999)
!999 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1000, size: 64, align: 64)
!1000 = !DISubroutineType(types: !1001)
!1001 = !{!191, !148}
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !649, file: !130, line: 1749, baseType: !1003, size: 64, align: 64, offset: 12800)
!1003 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !27, line: 315, baseType: !1004)
!1004 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1005, size: 64, align: 64)
!1005 = !DISubroutineType(types: !1006)
!1006 = !{!177, !148, !928, !928}
!1007 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch_data", scope: !649, file: !130, line: 1751, baseType: !148, size: 64, align: 64, offset: 12864)
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "gssapi_delegation", scope: !649, file: !130, line: 1753, baseType: !191, size: 64, align: 64, offset: 12928)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepalive", scope: !649, file: !130, line: 1756, baseType: !211, size: 8, align: 8, offset: 12992)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepidle", scope: !649, file: !130, line: 1757, baseType: !191, size: 64, align: 64, offset: 13056)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepintvl", scope: !649, file: !130, line: 1758, baseType: !191, size: 64, align: 64, offset: 13120)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !649, file: !130, line: 1759, baseType: !211, size: 8, align: 8, offset: 13184)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !649, file: !130, line: 1761, baseType: !158, size: 64, align: 64, offset: 13248)
!1014 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_npn", scope: !649, file: !130, line: 1763, baseType: !211, size: 8, align: 8, offset: 13312)
!1015 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_alpn", scope: !649, file: !130, line: 1764, baseType: !211, size: 8, align: 8, offset: 13320)
!1016 = !DIDerivedType(tag: DW_TAG_member, name: "path_as_is", scope: !649, file: !130, line: 1765, baseType: !211, size: 8, align: 8, offset: 13328)
!1017 = !DIDerivedType(tag: DW_TAG_member, name: "pipewait", scope: !649, file: !130, line: 1766, baseType: !211, size: 8, align: 8, offset: 13336)
!1018 = !DIDerivedType(tag: DW_TAG_member, name: "expect_100_timeout", scope: !649, file: !130, line: 1768, baseType: !191, size: 64, align: 64, offset: 13376)
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "suppress_connect_headers", scope: !649, file: !130, line: 1769, baseType: !211, size: 8, align: 8, offset: 13440)
!1020 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !649, file: !130, line: 1772, baseType: !544, size: 64, align: 64, offset: 13504)
!1021 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !649, file: !130, line: 1773, baseType: !211, size: 8, align: 8, offset: 13568)
!1022 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !649, file: !130, line: 1774, baseType: !177, size: 32, align: 32, offset: 13600)
!1023 = !DIDerivedType(tag: DW_TAG_member, name: "stream_dependents", scope: !649, file: !130, line: 1776, baseType: !1024, size: 64, align: 64, offset: 13632)
!1024 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1025, size: 64, align: 64)
!1025 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_http2_dep", file: !130, line: 1292, size: 128, align: 64, elements: !1026)
!1026 = !{!1027, !1028}
!1027 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1025, file: !130, line: 1293, baseType: !1024, size: 64, align: 64)
!1028 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1025, file: !130, line: 1294, baseType: !544, size: 64, align: 64, offset: 64)
!1029 = !DIDerivedType(tag: DW_TAG_member, name: "abstract_unix_socket", scope: !649, file: !130, line: 1778, baseType: !211, size: 8, align: 8, offset: 13696)
!1030 = !DIDerivedType(tag: DW_TAG_member, name: "change", scope: !545, file: !130, line: 1830, baseType: !1031, size: 384, align: 64, offset: 17216)
!1031 = !DICompositeType(tag: DW_TAG_structure_type, name: "DynamicStatic", file: !130, line: 1444, size: 384, align: 64, elements: !1032)
!1032 = !{!1033, !1034, !1035, !1036, !1037, !1038}
!1033 = !DIDerivedType(tag: DW_TAG_member, name: "url", scope: !1031, file: !130, line: 1445, baseType: !215, size: 64, align: 64)
!1034 = !DIDerivedType(tag: DW_TAG_member, name: "url_alloc", scope: !1031, file: !130, line: 1446, baseType: !211, size: 8, align: 8, offset: 64)
!1035 = !DIDerivedType(tag: DW_TAG_member, name: "referer", scope: !1031, file: !130, line: 1447, baseType: !215, size: 64, align: 64, offset: 128)
!1036 = !DIDerivedType(tag: DW_TAG_member, name: "referer_alloc", scope: !1031, file: !130, line: 1448, baseType: !211, size: 8, align: 8, offset: 192)
!1037 = !DIDerivedType(tag: DW_TAG_member, name: "cookielist", scope: !1031, file: !130, line: 1449, baseType: !824, size: 64, align: 64, offset: 256)
!1038 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !1031, file: !130, line: 1451, baseType: !824, size: 64, align: 64, offset: 320)
!1039 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !545, file: !130, line: 1831, baseType: !1040, size: 64, align: 64, offset: 17600)
!1040 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1041, size: 64, align: 64)
!1041 = !DICompositeType(tag: DW_TAG_structure_type, name: "CookieInfo", file: !1042, line: 48, size: 320, align: 64, elements: !1043)
!1042 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/cookie.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1043 = !{!1044, !1062, !1063, !1064, !1065}
!1044 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !1041, file: !1042, line: 50, baseType: !1045, size: 64, align: 64)
!1045 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1046, size: 64, align: 64)
!1046 = !DICompositeType(tag: DW_TAG_structure_type, name: "Cookie", file: !1042, line: 28, size: 768, align: 64, elements: !1047)
!1047 = !{!1048, !1049, !1050, !1051, !1052, !1053, !1054, !1055, !1056, !1057, !1058, !1059, !1060, !1061}
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1046, file: !1042, line: 29, baseType: !1045, size: 64, align: 64)
!1049 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1046, file: !1042, line: 30, baseType: !215, size: 64, align: 64, offset: 64)
!1050 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !1046, file: !1042, line: 31, baseType: !215, size: 64, align: 64, offset: 128)
!1051 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1046, file: !1042, line: 32, baseType: !215, size: 64, align: 64, offset: 192)
!1052 = !DIDerivedType(tag: DW_TAG_member, name: "spath", scope: !1046, file: !1042, line: 33, baseType: !215, size: 64, align: 64, offset: 256)
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1046, file: !1042, line: 34, baseType: !215, size: 64, align: 64, offset: 320)
!1054 = !DIDerivedType(tag: DW_TAG_member, name: "expires", scope: !1046, file: !1042, line: 35, baseType: !189, size: 64, align: 64, offset: 384)
!1055 = !DIDerivedType(tag: DW_TAG_member, name: "expirestr", scope: !1046, file: !1042, line: 36, baseType: !215, size: 64, align: 64, offset: 448)
!1056 = !DIDerivedType(tag: DW_TAG_member, name: "tailmatch", scope: !1046, file: !1042, line: 37, baseType: !211, size: 8, align: 8, offset: 512)
!1057 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !1046, file: !1042, line: 40, baseType: !215, size: 64, align: 64, offset: 576)
!1058 = !DIDerivedType(tag: DW_TAG_member, name: "maxage", scope: !1046, file: !1042, line: 41, baseType: !215, size: 64, align: 64, offset: 640)
!1059 = !DIDerivedType(tag: DW_TAG_member, name: "secure", scope: !1046, file: !1042, line: 43, baseType: !211, size: 8, align: 8, offset: 704)
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "livecookie", scope: !1046, file: !1042, line: 44, baseType: !211, size: 8, align: 8, offset: 712)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "httponly", scope: !1046, file: !1042, line: 45, baseType: !211, size: 8, align: 8, offset: 720)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !1041, file: !1042, line: 52, baseType: !215, size: 64, align: 64, offset: 64)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "running", scope: !1041, file: !1042, line: 53, baseType: !211, size: 8, align: 8, offset: 128)
!1064 = !DIDerivedType(tag: DW_TAG_member, name: "numcookies", scope: !1041, file: !1042, line: 54, baseType: !191, size: 64, align: 64, offset: 192)
!1065 = !DIDerivedType(tag: DW_TAG_member, name: "newsession", scope: !1041, file: !1042, line: 55, baseType: !211, size: 8, align: 8, offset: 256)
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "progress", scope: !545, file: !130, line: 1835, baseType: !1067, size: 3200, align: 64, offset: 17664)
!1067 = !DICompositeType(tag: DW_TAG_structure_type, name: "Progress", file: !130, line: 1195, size: 3200, align: 64, elements: !1068)
!1068 = !{!1069, !1070, !1071, !1072, !1073, !1074, !1075, !1076, !1077, !1078, !1079, !1080, !1081, !1082, !1083, !1084, !1085, !1086, !1087, !1088, !1089, !1090, !1091, !1092, !1093, !1094, !1095, !1099, !1101}
!1069 = !DIDerivedType(tag: DW_TAG_member, name: "lastshow", scope: !1067, file: !130, line: 1196, baseType: !242, size: 64, align: 64)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "size_dl", scope: !1067, file: !130, line: 1198, baseType: !189, size: 64, align: 64, offset: 64)
!1071 = !DIDerivedType(tag: DW_TAG_member, name: "size_ul", scope: !1067, file: !130, line: 1199, baseType: !189, size: 64, align: 64, offset: 128)
!1072 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !1067, file: !130, line: 1200, baseType: !189, size: 64, align: 64, offset: 192)
!1073 = !DIDerivedType(tag: DW_TAG_member, name: "uploaded", scope: !1067, file: !130, line: 1201, baseType: !189, size: 64, align: 64, offset: 256)
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1067, file: !130, line: 1203, baseType: !189, size: 64, align: 64, offset: 320)
!1075 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !1067, file: !130, line: 1205, baseType: !211, size: 8, align: 8, offset: 384)
!1076 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !1067, file: !130, line: 1206, baseType: !177, size: 32, align: 32, offset: 416)
!1077 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1067, file: !130, line: 1207, baseType: !177, size: 32, align: 32, offset: 448)
!1078 = !DIDerivedType(tag: DW_TAG_member, name: "timespent", scope: !1067, file: !130, line: 1209, baseType: !745, size: 64, align: 64, offset: 512)
!1079 = !DIDerivedType(tag: DW_TAG_member, name: "dlspeed", scope: !1067, file: !130, line: 1211, baseType: !189, size: 64, align: 64, offset: 576)
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "ulspeed", scope: !1067, file: !130, line: 1212, baseType: !189, size: 64, align: 64, offset: 640)
!1081 = !DIDerivedType(tag: DW_TAG_member, name: "t_nslookup", scope: !1067, file: !130, line: 1214, baseType: !745, size: 64, align: 64, offset: 704)
!1082 = !DIDerivedType(tag: DW_TAG_member, name: "t_connect", scope: !1067, file: !130, line: 1215, baseType: !745, size: 64, align: 64, offset: 768)
!1083 = !DIDerivedType(tag: DW_TAG_member, name: "t_appconnect", scope: !1067, file: !130, line: 1216, baseType: !745, size: 64, align: 64, offset: 832)
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "t_pretransfer", scope: !1067, file: !130, line: 1217, baseType: !745, size: 64, align: 64, offset: 896)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "t_starttransfer", scope: !1067, file: !130, line: 1218, baseType: !745, size: 64, align: 64, offset: 960)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "t_redirect", scope: !1067, file: !130, line: 1219, baseType: !745, size: 64, align: 64, offset: 1024)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !1067, file: !130, line: 1221, baseType: !201, size: 128, align: 64, offset: 1088)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "t_startsingle", scope: !1067, file: !130, line: 1222, baseType: !201, size: 128, align: 64, offset: 1216)
!1089 = !DIDerivedType(tag: DW_TAG_member, name: "t_startop", scope: !1067, file: !130, line: 1223, baseType: !201, size: 128, align: 64, offset: 1344)
!1090 = !DIDerivedType(tag: DW_TAG_member, name: "t_acceptdata", scope: !1067, file: !130, line: 1224, baseType: !201, size: 128, align: 64, offset: 1472)
!1091 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_start", scope: !1067, file: !130, line: 1227, baseType: !201, size: 128, align: 64, offset: 1600)
!1092 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_size", scope: !1067, file: !130, line: 1228, baseType: !189, size: 64, align: 64, offset: 1728)
!1093 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_start", scope: !1067, file: !130, line: 1230, baseType: !201, size: 128, align: 64, offset: 1792)
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_size", scope: !1067, file: !130, line: 1231, baseType: !189, size: 64, align: 64, offset: 1920)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "speeder", scope: !1067, file: !130, line: 1235, baseType: !1096, size: 384, align: 64, offset: 1984)
!1096 = !DICompositeType(tag: DW_TAG_array_type, baseType: !189, size: 384, align: 64, elements: !1097)
!1097 = !{!1098}
!1098 = !DISubrange(count: 6)
!1099 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_time", scope: !1067, file: !130, line: 1236, baseType: !1100, size: 768, align: 64, offset: 2368)
!1100 = !DICompositeType(tag: DW_TAG_array_type, baseType: !201, size: 768, align: 64, elements: !1097)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_c", scope: !1067, file: !130, line: 1237, baseType: !177, size: 32, align: 32, offset: 3136)
!1102 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !545, file: !130, line: 1836, baseType: !1103, size: 136640, align: 64, offset: 20864)
!1103 = !DICompositeType(tag: DW_TAG_structure_type, name: "UrlState", file: !130, line: 1310, size: 136640, align: 64, elements: !1104)
!1104 = !{!1105, !1107, !1108, !1109, !1110, !1111, !1112, !1113, !1117, !1118, !1119, !1120, !1121, !1134, !1135, !1136, !1145, !1146, !1147, !1148, !1152, !1153, !1165, !1166, !1175, !1176, !1177, !1178, !1179, !1180, !1181, !1182, !1183, !1184, !1185, !1186, !1187, !1188, !1189, !1190, !1191, !1192, !1193, !1194, !1195, !1196, !1197, !1198, !1199, !1200, !1201, !1202, !1203, !1204, !1205}
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !1103, file: !130, line: 1313, baseType: !1106, size: 64, align: 64)
!1106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !618, size: 64, align: 64)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "multi_owned_by_easy", scope: !1103, file: !130, line: 1318, baseType: !211, size: 8, align: 8, offset: 64)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "keeps_speed", scope: !1103, file: !130, line: 1321, baseType: !201, size: 128, align: 64, offset: 128)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "lastconnect", scope: !1103, file: !130, line: 1323, baseType: !550, size: 64, align: 64, offset: 256)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "headerbuff", scope: !1103, file: !130, line: 1325, baseType: !215, size: 64, align: 64, offset: 320)
!1111 = !DIDerivedType(tag: DW_TAG_member, name: "headersize", scope: !1103, file: !130, line: 1326, baseType: !158, size: 64, align: 64, offset: 384)
!1112 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1103, file: !130, line: 1328, baseType: !215, size: 64, align: 64, offset: 448)
!1113 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuffer", scope: !1103, file: !130, line: 1329, baseType: !1114, size: 131080, align: 8, offset: 512)
!1114 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 131080, align: 8, elements: !1115)
!1115 = !{!1116}
!1116 = !DISubrange(count: 16385)
!1117 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1103, file: !130, line: 1330, baseType: !189, size: 64, align: 64, offset: 131648)
!1118 = !DIDerivedType(tag: DW_TAG_member, name: "this_is_a_follow", scope: !1103, file: !130, line: 1332, baseType: !211, size: 8, align: 8, offset: 131712)
!1119 = !DIDerivedType(tag: DW_TAG_member, name: "first_host", scope: !1103, file: !130, line: 1334, baseType: !215, size: 64, align: 64, offset: 131776)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "first_remote_port", scope: !1103, file: !130, line: 1340, baseType: !177, size: 32, align: 32, offset: 131840)
!1121 = !DIDerivedType(tag: DW_TAG_member, name: "session", scope: !1103, file: !130, line: 1341, baseType: !1122, size: 64, align: 64, offset: 131904)
!1122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1123, size: 64, align: 64)
!1123 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_ssl_session", file: !130, line: 397, size: 1088, align: 64, elements: !1124)
!1124 = !{!1125, !1126, !1127, !1128, !1129, !1130, !1131, !1132, !1133}
!1125 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1123, file: !130, line: 398, baseType: !215, size: 64, align: 64)
!1126 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1123, file: !130, line: 399, baseType: !215, size: 64, align: 64, offset: 64)
!1127 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1123, file: !130, line: 400, baseType: !928, size: 64, align: 64, offset: 128)
!1128 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !1123, file: !130, line: 401, baseType: !148, size: 64, align: 64, offset: 192)
!1129 = !DIDerivedType(tag: DW_TAG_member, name: "idsize", scope: !1123, file: !130, line: 402, baseType: !158, size: 64, align: 64, offset: 256)
!1130 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !1123, file: !130, line: 403, baseType: !191, size: 64, align: 64, offset: 320)
!1131 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !1123, file: !130, line: 404, baseType: !177, size: 32, align: 32, offset: 384)
!1132 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1123, file: !130, line: 405, baseType: !177, size: 32, align: 32, offset: 416)
!1133 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !1123, file: !130, line: 406, baseType: !870, size: 640, align: 64, offset: 448)
!1134 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !1103, file: !130, line: 1342, baseType: !191, size: 64, align: 64, offset: 131968)
!1135 = !DIDerivedType(tag: DW_TAG_member, name: "tempcount", scope: !1103, file: !130, line: 1343, baseType: !782, size: 32, align: 32, offset: 132032)
!1136 = !DIDerivedType(tag: DW_TAG_member, name: "tempwrite", scope: !1103, file: !130, line: 1344, baseType: !1137, size: 576, align: 64, offset: 132096)
!1137 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1138, size: 576, align: 64, elements: !1143)
!1138 = !DICompositeType(tag: DW_TAG_structure_type, name: "tempbuf", file: !130, line: 1302, size: 192, align: 64, elements: !1139)
!1139 = !{!1140, !1141, !1142}
!1140 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !1138, file: !130, line: 1303, baseType: !215, size: 64, align: 64)
!1141 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !1138, file: !130, line: 1305, baseType: !158, size: 64, align: 64, offset: 64)
!1142 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1138, file: !130, line: 1306, baseType: !177, size: 32, align: 32, offset: 128)
!1143 = !{!1144}
!1144 = !DISubrange(count: 3)
!1145 = !DIDerivedType(tag: DW_TAG_member, name: "scratch", scope: !1103, file: !130, line: 1345, baseType: !215, size: 64, align: 64, offset: 132672)
!1146 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuf", scope: !1103, file: !130, line: 1346, baseType: !211, size: 8, align: 8, offset: 132736)
!1147 = !DIDerivedType(tag: DW_TAG_member, name: "os_errno", scope: !1103, file: !130, line: 1349, baseType: !177, size: 32, align: 32, offset: 132768)
!1148 = !DIDerivedType(tag: DW_TAG_member, name: "prev_signal", scope: !1103, file: !130, line: 1352, baseType: !1149, size: 64, align: 64, offset: 132800)
!1149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1150, size: 64, align: 64)
!1150 = !DISubroutineType(types: !1151)
!1151 = !{null, !177}
!1152 = !DIDerivedType(tag: DW_TAG_member, name: "allow_port", scope: !1103, file: !130, line: 1354, baseType: !211, size: 8, align: 8, offset: 132864)
!1153 = !DIDerivedType(tag: DW_TAG_member, name: "digest", scope: !1103, file: !130, line: 1356, baseType: !1154, size: 512, align: 64, offset: 132928)
!1154 = !DICompositeType(tag: DW_TAG_structure_type, name: "digestdata", file: !130, line: 410, size: 512, align: 64, elements: !1155)
!1155 = !{!1156, !1157, !1158, !1159, !1160, !1161, !1162, !1163, !1164}
!1156 = !DIDerivedType(tag: DW_TAG_member, name: "nonce", scope: !1154, file: !130, line: 416, baseType: !215, size: 64, align: 64)
!1157 = !DIDerivedType(tag: DW_TAG_member, name: "cnonce", scope: !1154, file: !130, line: 417, baseType: !215, size: 64, align: 64, offset: 64)
!1158 = !DIDerivedType(tag: DW_TAG_member, name: "realm", scope: !1154, file: !130, line: 418, baseType: !215, size: 64, align: 64, offset: 128)
!1159 = !DIDerivedType(tag: DW_TAG_member, name: "algo", scope: !1154, file: !130, line: 419, baseType: !177, size: 32, align: 32, offset: 192)
!1160 = !DIDerivedType(tag: DW_TAG_member, name: "stale", scope: !1154, file: !130, line: 420, baseType: !211, size: 8, align: 8, offset: 224)
!1161 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !1154, file: !130, line: 421, baseType: !215, size: 64, align: 64, offset: 256)
!1162 = !DIDerivedType(tag: DW_TAG_member, name: "qop", scope: !1154, file: !130, line: 422, baseType: !215, size: 64, align: 64, offset: 320)
!1163 = !DIDerivedType(tag: DW_TAG_member, name: "algorithm", scope: !1154, file: !130, line: 423, baseType: !215, size: 64, align: 64, offset: 384)
!1164 = !DIDerivedType(tag: DW_TAG_member, name: "nc", scope: !1154, file: !130, line: 424, baseType: !177, size: 32, align: 32, offset: 448)
!1165 = !DIDerivedType(tag: DW_TAG_member, name: "proxydigest", scope: !1103, file: !130, line: 1357, baseType: !1154, size: 512, align: 64, offset: 133440)
!1166 = !DIDerivedType(tag: DW_TAG_member, name: "authhost", scope: !1103, file: !130, line: 1364, baseType: !1167, size: 256, align: 64, offset: 133952)
!1167 = !DICompositeType(tag: DW_TAG_structure_type, name: "auth", file: !130, line: 1278, size: 256, align: 64, elements: !1168)
!1168 = !{!1169, !1170, !1171, !1172, !1173, !1174}
!1169 = !DIDerivedType(tag: DW_TAG_member, name: "want", scope: !1167, file: !130, line: 1279, baseType: !160, size: 64, align: 64)
!1170 = !DIDerivedType(tag: DW_TAG_member, name: "picked", scope: !1167, file: !130, line: 1281, baseType: !160, size: 64, align: 64, offset: 64)
!1171 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !1167, file: !130, line: 1282, baseType: !160, size: 64, align: 64, offset: 128)
!1172 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1167, file: !130, line: 1284, baseType: !211, size: 8, align: 8, offset: 192)
!1173 = !DIDerivedType(tag: DW_TAG_member, name: "multipass", scope: !1167, file: !130, line: 1286, baseType: !211, size: 8, align: 8, offset: 200)
!1174 = !DIDerivedType(tag: DW_TAG_member, name: "iestyle", scope: !1167, file: !130, line: 1288, baseType: !211, size: 8, align: 8, offset: 208)
!1175 = !DIDerivedType(tag: DW_TAG_member, name: "authproxy", scope: !1103, file: !130, line: 1365, baseType: !1167, size: 256, align: 64, offset: 134208)
!1176 = !DIDerivedType(tag: DW_TAG_member, name: "authproblem", scope: !1103, file: !130, line: 1367, baseType: !211, size: 8, align: 8, offset: 134464)
!1177 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !1103, file: !130, line: 1369, baseType: !148, size: 64, align: 64, offset: 134528)
!1178 = !DIDerivedType(tag: DW_TAG_member, name: "expiretime", scope: !1103, file: !130, line: 1375, baseType: !201, size: 128, align: 64, offset: 134592)
!1179 = !DIDerivedType(tag: DW_TAG_member, name: "timenode", scope: !1103, file: !130, line: 1376, baseType: !605, size: 448, align: 64, offset: 134720)
!1180 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutlist", scope: !1103, file: !130, line: 1377, baseType: !140, size: 256, align: 64, offset: 135168)
!1181 = !DIDerivedType(tag: DW_TAG_member, name: "most_recent_ftp_entrypath", scope: !1103, file: !130, line: 1380, baseType: !215, size: 64, align: 64, offset: 135424)
!1182 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_trying_alternative", scope: !1103, file: !130, line: 1383, baseType: !211, size: 8, align: 8, offset: 135488)
!1183 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1103, file: !130, line: 1385, baseType: !177, size: 32, align: 32, offset: 135520)
!1184 = !DIDerivedType(tag: DW_TAG_member, name: "expect100header", scope: !1103, file: !130, line: 1387, baseType: !211, size: 8, align: 8, offset: 135552)
!1185 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_broke", scope: !1103, file: !130, line: 1389, baseType: !211, size: 8, align: 8, offset: 135560)
!1186 = !DIDerivedType(tag: DW_TAG_member, name: "prev_block_had_trailing_cr", scope: !1103, file: !130, line: 1397, baseType: !211, size: 8, align: 8, offset: 135568)
!1187 = !DIDerivedType(tag: DW_TAG_member, name: "crlf_conversions", scope: !1103, file: !130, line: 1399, baseType: !189, size: 64, align: 64, offset: 135616)
!1188 = !DIDerivedType(tag: DW_TAG_member, name: "pathbuffer", scope: !1103, file: !130, line: 1401, baseType: !215, size: 64, align: 64, offset: 135680)
!1189 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1103, file: !130, line: 1402, baseType: !215, size: 64, align: 64, offset: 135744)
!1190 = !DIDerivedType(tag: DW_TAG_member, name: "slash_removed", scope: !1103, file: !130, line: 1404, baseType: !211, size: 8, align: 8, offset: 135808)
!1191 = !DIDerivedType(tag: DW_TAG_member, name: "use_range", scope: !1103, file: !130, line: 1406, baseType: !211, size: 8, align: 8, offset: 135816)
!1192 = !DIDerivedType(tag: DW_TAG_member, name: "rangestringalloc", scope: !1103, file: !130, line: 1407, baseType: !211, size: 8, align: 8, offset: 135824)
!1193 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !1103, file: !130, line: 1409, baseType: !215, size: 64, align: 64, offset: 135872)
!1194 = !DIDerivedType(tag: DW_TAG_member, name: "resume_from", scope: !1103, file: !130, line: 1411, baseType: !189, size: 64, align: 64, offset: 135936)
!1195 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_client_CSeq", scope: !1103, file: !130, line: 1414, baseType: !191, size: 64, align: 64, offset: 136000)
!1196 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_server_CSeq", scope: !1103, file: !130, line: 1415, baseType: !191, size: 64, align: 64, offset: 136064)
!1197 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_CSeq_recv", scope: !1103, file: !130, line: 1416, baseType: !191, size: 64, align: 64, offset: 136128)
!1198 = !DIDerivedType(tag: DW_TAG_member, name: "infilesize", scope: !1103, file: !130, line: 1418, baseType: !189, size: 64, align: 64, offset: 136192)
!1199 = !DIDerivedType(tag: DW_TAG_member, name: "drain", scope: !1103, file: !130, line: 1421, baseType: !158, size: 64, align: 64, offset: 136256)
!1200 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1103, file: !130, line: 1424, baseType: !211, size: 8, align: 8, offset: 136320)
!1201 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1103, file: !130, line: 1428, baseType: !737, size: 64, align: 64, offset: 136384)
!1202 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1103, file: !130, line: 1429, baseType: !148, size: 64, align: 64, offset: 136448)
!1203 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !1103, file: !130, line: 1431, baseType: !544, size: 64, align: 64, offset: 136512)
!1204 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !1103, file: !130, line: 1432, baseType: !211, size: 8, align: 8, offset: 136576)
!1205 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !1103, file: !130, line: 1433, baseType: !177, size: 32, align: 32, offset: 136608)
!1206 = !DIDerivedType(tag: DW_TAG_member, name: "wildcard", scope: !545, file: !130, line: 1838, baseType: !1207, size: 640, align: 64, offset: 157504)
!1207 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !375, line: 46, size: 640, align: 64, elements: !1208)
!1208 = !{!1209, !1211, !1212, !1213, !1214, !1215, !1217}
!1209 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1207, file: !375, line: 47, baseType: !1210, size: 32, align: 32)
!1210 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !375, line: 41, baseType: !374)
!1211 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1207, file: !375, line: 48, baseType: !215, size: 64, align: 64, offset: 64)
!1212 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !1207, file: !375, line: 49, baseType: !215, size: 64, align: 64, offset: 128)
!1213 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !1207, file: !375, line: 50, baseType: !140, size: 256, align: 64, offset: 192)
!1214 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !1207, file: !375, line: 51, baseType: !148, size: 64, align: 64, offset: 448)
!1215 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !1207, file: !375, line: 52, baseType: !1216, size: 64, align: 64, offset: 512)
!1216 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !375, line: 43, baseType: !173)
!1217 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !1207, file: !375, line: 53, baseType: !148, size: 64, align: 64, offset: 576)
!1218 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !545, file: !130, line: 1839, baseType: !1219, size: 1856, align: 64, offset: 158144)
!1219 = !DICompositeType(tag: DW_TAG_structure_type, name: "PureInfo", file: !130, line: 1154, size: 1856, align: 64, elements: !1220)
!1220 = !{!1221, !1222, !1223, !1224, !1225, !1226, !1227, !1228, !1229, !1230, !1231, !1232, !1233, !1237, !1238, !1239, !1240, !1241, !1242}
!1221 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !1219, file: !130, line: 1155, baseType: !177, size: 32, align: 32)
!1222 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxycode", scope: !1219, file: !130, line: 1156, baseType: !177, size: 32, align: 32, offset: 32)
!1223 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1219, file: !130, line: 1157, baseType: !177, size: 32, align: 32, offset: 64)
!1224 = !DIDerivedType(tag: DW_TAG_member, name: "filetime", scope: !1219, file: !130, line: 1158, baseType: !191, size: 64, align: 64, offset: 128)
!1225 = !DIDerivedType(tag: DW_TAG_member, name: "timecond", scope: !1219, file: !130, line: 1162, baseType: !211, size: 8, align: 8, offset: 192)
!1226 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !1219, file: !130, line: 1164, baseType: !191, size: 64, align: 64, offset: 256)
!1227 = !DIDerivedType(tag: DW_TAG_member, name: "request_size", scope: !1219, file: !130, line: 1165, baseType: !191, size: 64, align: 64, offset: 320)
!1228 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauthavail", scope: !1219, file: !130, line: 1166, baseType: !160, size: 64, align: 64, offset: 384)
!1229 = !DIDerivedType(tag: DW_TAG_member, name: "httpauthavail", scope: !1219, file: !130, line: 1167, baseType: !160, size: 64, align: 64, offset: 448)
!1230 = !DIDerivedType(tag: DW_TAG_member, name: "numconnects", scope: !1219, file: !130, line: 1168, baseType: !191, size: 64, align: 64, offset: 512)
!1231 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !1219, file: !130, line: 1169, baseType: !215, size: 64, align: 64, offset: 576)
!1232 = !DIDerivedType(tag: DW_TAG_member, name: "wouldredirect", scope: !1219, file: !130, line: 1170, baseType: !215, size: 64, align: 64, offset: 640)
!1233 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_ip", scope: !1219, file: !130, line: 1180, baseType: !1234, size: 368, align: 8, offset: 704)
!1234 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 368, align: 8, elements: !1235)
!1235 = !{!1236}
!1236 = !DISubrange(count: 46)
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_port", scope: !1219, file: !130, line: 1181, baseType: !191, size: 64, align: 64, offset: 1088)
!1238 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_ip", scope: !1219, file: !130, line: 1183, baseType: !1234, size: 368, align: 8, offset: 1152)
!1239 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_port", scope: !1219, file: !130, line: 1184, baseType: !191, size: 64, align: 64, offset: 1536)
!1240 = !DIDerivedType(tag: DW_TAG_member, name: "conn_scheme", scope: !1219, file: !130, line: 1186, baseType: !928, size: 64, align: 64, offset: 1600)
!1241 = !DIDerivedType(tag: DW_TAG_member, name: "conn_protocol", scope: !1219, file: !130, line: 1187, baseType: !782, size: 32, align: 32, offset: 1664)
!1242 = !DIDerivedType(tag: DW_TAG_member, name: "certs", scope: !1219, file: !130, line: 1189, baseType: !1243, size: 128, align: 64, offset: 1728)
!1243 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !27, line: 2214, size: 128, align: 64, elements: !1244)
!1244 = !{!1245, !1246}
!1245 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1243, file: !27, line: 2215, baseType: !177, size: 32, align: 32)
!1246 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1243, file: !27, line: 2216, baseType: !1247, size: 64, align: 64, offset: 64)
!1247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !824, size: 64, align: 64)
!1248 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !545, file: !130, line: 1840, baseType: !1249, size: 128, align: 64, offset: 160000)
!1249 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !27, line: 2245, size: 128, align: 64, elements: !1250)
!1250 = !{!1251, !1253}
!1251 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1249, file: !27, line: 2246, baseType: !1252, size: 32, align: 32)
!1252 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !27, line: 2235, baseType: !385)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1249, file: !27, line: 2247, baseType: !148, size: 64, align: 64, offset: 64)
!1254 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !545, file: !130, line: 1847, baseType: !782, size: 32, align: 32, offset: 160128)
!1255 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !541, file: !130, line: 904, baseType: !1256, size: 384, align: 64, offset: 64)
!1256 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !400, line: 82, size: 384, align: 64, elements: !1257)
!1257 = !{!1258, !1262, !1263, !1265, !1266}
!1258 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1256, file: !400, line: 83, baseType: !1259, size: 136, align: 8)
!1259 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 136, align: 8, elements: !1260)
!1260 = !{!1261}
!1261 = !DISubrange(count: 17)
!1262 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1256, file: !400, line: 84, baseType: !177, size: 32, align: 32, offset: 160)
!1263 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1256, file: !400, line: 85, baseType: !1264, size: 32, align: 32, offset: 192)
!1264 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !400, line: 66, baseType: !399)
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1256, file: !400, line: 86, baseType: !189, size: 64, align: 64, offset: 256)
!1266 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1256, file: !400, line: 87, baseType: !158, size: 64, align: 64, offset: 320)
!1267 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !541, file: !130, line: 906, baseType: !796, size: 64, align: 64, offset: 448)
!1268 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !541, file: !130, line: 907, baseType: !148, size: 64, align: 64, offset: 512)
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !541, file: !130, line: 909, baseType: !211, size: 8, align: 8, offset: 576)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "connection_id", scope: !541, file: !130, line: 915, baseType: !191, size: 64, align: 64, offset: 640)
!1271 = !DIDerivedType(tag: DW_TAG_member, name: "dns_entry", scope: !541, file: !130, line: 922, baseType: !1272, size: 64, align: 64, offset: 704)
!1272 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1273, size: 64, align: 64)
!1273 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_dns_entry", file: !1274, line: 66, size: 192, align: 64, elements: !1275)
!1274 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hostip.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1275 = !{!1276, !1295, !1296}
!1276 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !1273, file: !1274, line: 67, baseType: !1277, size: 64, align: 64)
!1277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1278, size: 64, align: 64)
!1278 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_addrinfo", file: !1279, line: 61, baseType: !1280)
!1279 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1280 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_addrinfo", file: !1279, line: 51, size: 384, align: 64, elements: !1281)
!1281 = !{!1282, !1283, !1284, !1285, !1286, !1290, !1291, !1293}
!1282 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !1280, file: !1279, line: 52, baseType: !177, size: 32, align: 32)
!1283 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !1280, file: !1279, line: 53, baseType: !177, size: 32, align: 32, offset: 32)
!1284 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !1280, file: !1279, line: 54, baseType: !177, size: 32, align: 32, offset: 64)
!1285 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !1280, file: !1279, line: 55, baseType: !177, size: 32, align: 32, offset: 96)
!1286 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !1280, file: !1279, line: 56, baseType: !1287, size: 32, align: 32, offset: 128)
!1287 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !190, line: 186, baseType: !1288)
!1288 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !785, line: 33, baseType: !1289)
!1289 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !206, line: 189, baseType: !782)
!1290 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !1280, file: !1279, line: 57, baseType: !215, size: 64, align: 64, offset: 192)
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !1280, file: !1279, line: 58, baseType: !1292, size: 64, align: 64, offset: 256)
!1292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !784, size: 64, align: 64)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !1280, file: !1279, line: 59, baseType: !1294, size: 64, align: 64, offset: 320)
!1294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1280, size: 64, align: 64)
!1295 = !DIDerivedType(tag: DW_TAG_member, name: "timestamp", scope: !1273, file: !1274, line: 69, baseType: !242, size: 64, align: 64, offset: 64)
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !1273, file: !1274, line: 71, baseType: !191, size: 64, align: 64, offset: 128)
!1297 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr", scope: !541, file: !130, line: 927, baseType: !1277, size: 64, align: 64, offset: 768)
!1298 = !DIDerivedType(tag: DW_TAG_member, name: "tempaddr", scope: !541, file: !130, line: 928, baseType: !1299, size: 128, align: 64, offset: 832)
!1299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1277, size: 128, align: 64, elements: !1300)
!1300 = !{!1301}
!1301 = !DISubrange(count: 2)
!1302 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr_str", scope: !541, file: !130, line: 933, baseType: !1234, size: 368, align: 8, offset: 960)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !541, file: !130, line: 935, baseType: !782, size: 32, align: 32, offset: 1344)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !541, file: !130, line: 937, baseType: !177, size: 32, align: 32, offset: 1376)
!1305 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !541, file: !130, line: 939, baseType: !1306, size: 256, align: 64, offset: 1408)
!1306 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostname", file: !130, line: 581, size: 256, align: 64, elements: !1307)
!1307 = !{!1308, !1309, !1310, !1311}
!1308 = !DIDerivedType(tag: DW_TAG_member, name: "rawalloc", scope: !1306, file: !130, line: 582, baseType: !215, size: 64, align: 64)
!1309 = !DIDerivedType(tag: DW_TAG_member, name: "encalloc", scope: !1306, file: !130, line: 583, baseType: !215, size: 64, align: 64, offset: 64)
!1310 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1306, file: !130, line: 584, baseType: !215, size: 64, align: 64, offset: 128)
!1311 = !DIDerivedType(tag: DW_TAG_member, name: "dispname", scope: !1306, file: !130, line: 585, baseType: !928, size: 64, align: 64, offset: 192)
!1312 = !DIDerivedType(tag: DW_TAG_member, name: "secondaryhostname", scope: !541, file: !130, line: 940, baseType: !215, size: 64, align: 64, offset: 1664)
!1313 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !541, file: !130, line: 941, baseType: !1306, size: 256, align: 64, offset: 1728)
!1314 = !DIDerivedType(tag: DW_TAG_member, name: "socks_proxy", scope: !541, file: !130, line: 944, baseType: !1315, size: 512, align: 64, offset: 1984)
!1315 = !DICompositeType(tag: DW_TAG_structure_type, name: "proxy_info", file: !130, line: 883, size: 512, align: 64, elements: !1316)
!1316 = !{!1317, !1318, !1319, !1320, !1321}
!1317 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1315, file: !130, line: 884, baseType: !1306, size: 256, align: 64)
!1318 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !1315, file: !130, line: 885, baseType: !191, size: 64, align: 64, offset: 256)
!1319 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !1315, file: !130, line: 886, baseType: !908, size: 32, align: 32, offset: 320)
!1320 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1315, file: !130, line: 887, baseType: !215, size: 64, align: 64, offset: 384)
!1321 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !1315, file: !130, line: 888, baseType: !215, size: 64, align: 64, offset: 448)
!1322 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !541, file: !130, line: 945, baseType: !1315, size: 512, align: 64, offset: 2496)
!1323 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !541, file: !130, line: 947, baseType: !191, size: 64, align: 64, offset: 3008)
!1324 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !541, file: !130, line: 948, baseType: !177, size: 32, align: 32, offset: 3072)
!1325 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !541, file: !130, line: 949, baseType: !177, size: 32, align: 32, offset: 3104)
!1326 = !DIDerivedType(tag: DW_TAG_member, name: "secondary_port", scope: !541, file: !130, line: 951, baseType: !684, size: 16, align: 16, offset: 3136)
!1327 = !DIDerivedType(tag: DW_TAG_member, name: "primary_ip", scope: !541, file: !130, line: 961, baseType: !1234, size: 368, align: 8, offset: 3152)
!1328 = !DIDerivedType(tag: DW_TAG_member, name: "primary_port", scope: !541, file: !130, line: 962, baseType: !191, size: 64, align: 64, offset: 3520)
!1329 = !DIDerivedType(tag: DW_TAG_member, name: "local_ip", scope: !541, file: !130, line: 968, baseType: !1234, size: 368, align: 8, offset: 3584)
!1330 = !DIDerivedType(tag: DW_TAG_member, name: "local_port", scope: !541, file: !130, line: 969, baseType: !191, size: 64, align: 64, offset: 3968)
!1331 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !541, file: !130, line: 971, baseType: !215, size: 64, align: 64, offset: 4032)
!1332 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !541, file: !130, line: 972, baseType: !215, size: 64, align: 64, offset: 4096)
!1333 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !541, file: !130, line: 973, baseType: !215, size: 64, align: 64, offset: 4160)
!1334 = !DIDerivedType(tag: DW_TAG_member, name: "oauth_bearer", scope: !541, file: !130, line: 975, baseType: !215, size: 64, align: 64, offset: 4224)
!1335 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !541, file: !130, line: 977, baseType: !177, size: 32, align: 32, offset: 4288)
!1336 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !541, file: !130, line: 978, baseType: !177, size: 32, align: 32, offset: 4320)
!1337 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !541, file: !130, line: 980, baseType: !201, size: 128, align: 64, offset: 4352)
!1338 = !DIDerivedType(tag: DW_TAG_member, name: "created", scope: !541, file: !130, line: 981, baseType: !201, size: 128, align: 64, offset: 4480)
!1339 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !541, file: !130, line: 982, baseType: !1340, size: 64, align: 32, offset: 4608)
!1340 = !DICompositeType(tag: DW_TAG_array_type, baseType: !248, size: 64, align: 32, elements: !1300)
!1341 = !DIDerivedType(tag: DW_TAG_member, name: "tempsock", scope: !541, file: !130, line: 984, baseType: !1340, size: 64, align: 32, offset: 4672)
!1342 = !DIDerivedType(tag: DW_TAG_member, name: "sock_accepted", scope: !541, file: !130, line: 985, baseType: !1343, size: 16, align: 8, offset: 4736)
!1343 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 16, align: 8, elements: !1300)
!1344 = !DIDerivedType(tag: DW_TAG_member, name: "recv", scope: !541, file: !130, line: 987, baseType: !1345, size: 128, align: 64, offset: 4800)
!1345 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1346, size: 128, align: 64, elements: !1300)
!1346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1347, size: 64, align: 64)
!1347 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_recv", file: !130, line: 863, baseType: !1348)
!1348 = !DISubroutineType(types: !1349)
!1349 = !{!256, !550, !177, !215, !158, !1350}
!1350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !554, size: 64, align: 64)
!1351 = !DIDerivedType(tag: DW_TAG_member, name: "send", scope: !541, file: !130, line: 988, baseType: !1352, size: 128, align: 64, offset: 4928)
!1352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1353, size: 128, align: 64, elements: !1300)
!1353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1354, size: 64, align: 64)
!1354 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_send", file: !130, line: 856, baseType: !1355)
!1355 = !DISubroutineType(types: !1356)
!1356 = !{!256, !550, !177, !995, !158, !1350}
!1357 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !541, file: !130, line: 993, baseType: !1358, size: 192, align: 32, offset: 5056)
!1358 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1359, size: 192, align: 32, elements: !1300)
!1359 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_connect_data", file: !130, line: 274, size: 96, align: 32, elements: !1360)
!1360 = !{!1361, !1362, !1364}
!1361 = !DIDerivedType(tag: DW_TAG_member, name: "use", scope: !1359, file: !130, line: 278, baseType: !211, size: 8, align: 8)
!1362 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1359, file: !130, line: 279, baseType: !1363, size: 32, align: 32, offset: 32)
!1363 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connection_state", file: !130, line: 271, baseType: !410)
!1364 = !DIDerivedType(tag: DW_TAG_member, name: "connecting_state", scope: !1359, file: !130, line: 280, baseType: !1365, size: 32, align: 32, offset: 64)
!1365 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connect_state", file: !130, line: 265, baseType: !415)
!1366 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !541, file: !130, line: 994, baseType: !1358, size: 192, align: 32, offset: 5248)
!1367 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !541, file: !130, line: 995, baseType: !870, size: 640, align: 64, offset: 5440)
!1368 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_config", scope: !541, file: !130, line: 996, baseType: !870, size: 640, align: 64, offset: 6080)
!1369 = !DIDerivedType(tag: DW_TAG_member, name: "tls_upgraded", scope: !541, file: !130, line: 997, baseType: !211, size: 8, align: 8, offset: 6720)
!1370 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !541, file: !130, line: 999, baseType: !1371, size: 280, align: 8, offset: 6728)
!1371 = !DICompositeType(tag: DW_TAG_structure_type, name: "ConnectBits", file: !130, line: 514, size: 280, align: 8, elements: !1372)
!1372 = !{!1373, !1374, !1375, !1376, !1377, !1378, !1379, !1380, !1381, !1382, !1383, !1384, !1385, !1386, !1387, !1388, !1389, !1390, !1391, !1392, !1393, !1394, !1395, !1396, !1397, !1398, !1399, !1400, !1401, !1402, !1403, !1404, !1405}
!1373 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !1371, file: !130, line: 516, baseType: !211, size: 8, align: 8)
!1374 = !DIDerivedType(tag: DW_TAG_member, name: "reuse", scope: !1371, file: !130, line: 517, baseType: !211, size: 8, align: 8, offset: 8)
!1375 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1371, file: !130, line: 518, baseType: !211, size: 8, align: 8, offset: 16)
!1376 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1371, file: !130, line: 520, baseType: !211, size: 8, align: 8, offset: 24)
!1377 = !DIDerivedType(tag: DW_TAG_member, name: "proxy", scope: !1371, file: !130, line: 522, baseType: !211, size: 8, align: 8, offset: 32)
!1378 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxy", scope: !1371, file: !130, line: 523, baseType: !211, size: 8, align: 8, offset: 40)
!1379 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy", scope: !1371, file: !130, line: 524, baseType: !211, size: 8, align: 8, offset: 48)
!1380 = !DIDerivedType(tag: DW_TAG_member, name: "user_passwd", scope: !1371, file: !130, line: 525, baseType: !211, size: 8, align: 8, offset: 56)
!1381 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user_passwd", scope: !1371, file: !130, line: 526, baseType: !211, size: 8, align: 8, offset: 64)
!1382 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6_ip", scope: !1371, file: !130, line: 527, baseType: !211, size: 8, align: 8, offset: 72)
!1383 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6", scope: !1371, file: !130, line: 529, baseType: !211, size: 8, align: 8, offset: 80)
!1384 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1371, file: !130, line: 531, baseType: !211, size: 8, align: 8, offset: 88)
!1385 = !DIDerivedType(tag: DW_TAG_member, name: "tcpconnect", scope: !1371, file: !130, line: 533, baseType: !1343, size: 16, align: 8, offset: 96)
!1386 = !DIDerivedType(tag: DW_TAG_member, name: "protoconnstart", scope: !1371, file: !130, line: 535, baseType: !211, size: 8, align: 8, offset: 112)
!1387 = !DIDerivedType(tag: DW_TAG_member, name: "retry", scope: !1371, file: !130, line: 538, baseType: !211, size: 8, align: 8, offset: 120)
!1388 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_proxy", scope: !1371, file: !130, line: 540, baseType: !211, size: 8, align: 8, offset: 128)
!1389 = !DIDerivedType(tag: DW_TAG_member, name: "authneg", scope: !1371, file: !130, line: 544, baseType: !211, size: 8, align: 8, offset: 136)
!1390 = !DIDerivedType(tag: DW_TAG_member, name: "rewindaftersend", scope: !1371, file: !130, line: 548, baseType: !211, size: 8, align: 8, offset: 144)
!1391 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !1371, file: !130, line: 552, baseType: !211, size: 8, align: 8, offset: 152)
!1392 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !1371, file: !130, line: 556, baseType: !211, size: 8, align: 8, offset: 160)
!1393 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_data_ssl", scope: !1371, file: !130, line: 559, baseType: !211, size: 8, align: 8, offset: 168)
!1394 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !1371, file: !130, line: 560, baseType: !211, size: 8, align: 8, offset: 176)
!1395 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd_in_url", scope: !1371, file: !130, line: 561, baseType: !211, size: 8, align: 8, offset: 184)
!1396 = !DIDerivedType(tag: DW_TAG_member, name: "stream_was_rewound", scope: !1371, file: !130, line: 562, baseType: !211, size: 8, align: 8, offset: 192)
!1397 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_connect_closed", scope: !1371, file: !130, line: 565, baseType: !211, size: 8, align: 8, offset: 200)
!1398 = !DIDerivedType(tag: DW_TAG_member, name: "bound", scope: !1371, file: !130, line: 568, baseType: !211, size: 8, align: 8, offset: 208)
!1399 = !DIDerivedType(tag: DW_TAG_member, name: "type_set", scope: !1371, file: !130, line: 570, baseType: !211, size: 8, align: 8, offset: 216)
!1400 = !DIDerivedType(tag: DW_TAG_member, name: "multiplex", scope: !1371, file: !130, line: 571, baseType: !211, size: 8, align: 8, offset: 224)
!1401 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !1371, file: !130, line: 573, baseType: !211, size: 8, align: 8, offset: 232)
!1402 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_npn", scope: !1371, file: !130, line: 574, baseType: !211, size: 8, align: 8, offset: 240)
!1403 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_alpn", scope: !1371, file: !130, line: 575, baseType: !211, size: 8, align: 8, offset: 248)
!1404 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_connected", scope: !1371, file: !130, line: 576, baseType: !1343, size: 16, align: 8, offset: 256)
!1405 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy_connecting", scope: !1371, file: !130, line: 578, baseType: !211, size: 8, align: 8, offset: 272)
!1406 = !DIDerivedType(tag: DW_TAG_member, name: "connecttime", scope: !541, file: !130, line: 1004, baseType: !201, size: 128, align: 64, offset: 7040)
!1407 = !DIDerivedType(tag: DW_TAG_member, name: "num_addr", scope: !541, file: !130, line: 1006, baseType: !177, size: 32, align: 32, offset: 7168)
!1408 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutms_per_addr", scope: !541, file: !130, line: 1007, baseType: !242, size: 64, align: 64, offset: 7232)
!1409 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !541, file: !130, line: 1010, baseType: !1410, size: 64, align: 64, offset: 7296)
!1410 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1411, size: 64, align: 64)
!1411 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1412)
!1412 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_handler", file: !130, line: 763, size: 1024, align: 64, elements: !1413)
!1413 = !{!1414, !1415, !1419, !1424, !1429, !1435, !1436, !1437, !1438, !1443, !1444, !1445, !1451, !1455, !1460, !1461, !1462}
!1414 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1412, file: !130, line: 764, baseType: !928, size: 64, align: 64)
!1415 = !DIDerivedType(tag: DW_TAG_member, name: "setup_connection", scope: !1412, file: !130, line: 767, baseType: !1416, size: 64, align: 64, offset: 64)
!1416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1417, size: 64, align: 64)
!1417 = !DISubroutineType(types: !1418)
!1418 = !{!554, !550}
!1419 = !DIDerivedType(tag: DW_TAG_member, name: "do_it", scope: !1412, file: !130, line: 770, baseType: !1420, size: 64, align: 64, offset: 128)
!1420 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1421, size: 64, align: 64)
!1421 = !DISubroutineType(types: !1422)
!1422 = !{!554, !550, !1423}
!1423 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!1424 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1412, file: !130, line: 771, baseType: !1425, size: 64, align: 64, offset: 192)
!1425 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_done_func", file: !130, line: 634, baseType: !1426)
!1426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1427, size: 64, align: 64)
!1427 = !DISubroutineType(types: !1428)
!1428 = !{!554, !550, !554, !211}
!1429 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1412, file: !130, line: 777, baseType: !1430, size: 64, align: 64, offset: 256)
!1430 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_do_more_func", file: !130, line: 633, baseType: !1431)
!1431 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1432, size: 64, align: 64)
!1432 = !DISubroutineType(types: !1433)
!1433 = !{!554, !550, !1434}
!1434 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!1435 = !DIDerivedType(tag: DW_TAG_member, name: "connect_it", scope: !1412, file: !130, line: 785, baseType: !1420, size: 64, align: 64, offset: 320)
!1436 = !DIDerivedType(tag: DW_TAG_member, name: "connecting", scope: !1412, file: !130, line: 788, baseType: !1420, size: 64, align: 64, offset: 384)
!1437 = !DIDerivedType(tag: DW_TAG_member, name: "doing", scope: !1412, file: !130, line: 789, baseType: !1420, size: 64, align: 64, offset: 448)
!1438 = !DIDerivedType(tag: DW_TAG_member, name: "proto_getsock", scope: !1412, file: !130, line: 793, baseType: !1439, size: 64, align: 64, offset: 512)
!1439 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1440, size: 64, align: 64)
!1440 = !DISubroutineType(types: !1441)
!1441 = !{!177, !550, !1442, !177}
!1442 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!1443 = !DIDerivedType(tag: DW_TAG_member, name: "doing_getsock", scope: !1412, file: !130, line: 799, baseType: !1439, size: 64, align: 64, offset: 576)
!1444 = !DIDerivedType(tag: DW_TAG_member, name: "domore_getsock", scope: !1412, file: !130, line: 805, baseType: !1439, size: 64, align: 64, offset: 640)
!1445 = !DIDerivedType(tag: DW_TAG_member, name: "perform_getsock", scope: !1412, file: !130, line: 812, baseType: !1446, size: 64, align: 64, offset: 704)
!1446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1447, size: 64, align: 64)
!1447 = !DISubroutineType(types: !1448)
!1448 = !{!177, !1449, !1442, !177}
!1449 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1450, size: 64, align: 64)
!1450 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !541)
!1451 = !DIDerivedType(tag: DW_TAG_member, name: "disconnect", scope: !1412, file: !130, line: 821, baseType: !1452, size: 64, align: 64, offset: 768)
!1452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1453, size: 64, align: 64)
!1453 = !DISubroutineType(types: !1454)
!1454 = !{!554, !550, !211}
!1455 = !DIDerivedType(tag: DW_TAG_member, name: "readwrite", scope: !1412, file: !130, line: 825, baseType: !1456, size: 64, align: 64, offset: 832)
!1456 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1457, size: 64, align: 64)
!1457 = !DISubroutineType(types: !1458)
!1458 = !{!554, !544, !550, !1459, !1423}
!1459 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!1460 = !DIDerivedType(tag: DW_TAG_member, name: "defport", scope: !1412, file: !130, line: 828, baseType: !191, size: 64, align: 64, offset: 896)
!1461 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1412, file: !130, line: 829, baseType: !782, size: 32, align: 32, offset: 960)
!1462 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1412, file: !130, line: 831, baseType: !782, size: 32, align: 32, offset: 992)
!1463 = !DIDerivedType(tag: DW_TAG_member, name: "given", scope: !541, file: !130, line: 1011, baseType: !1410, size: 64, align: 64, offset: 7360)
!1464 = !DIDerivedType(tag: DW_TAG_member, name: "ip_version", scope: !541, file: !130, line: 1013, baseType: !191, size: 64, align: 64, offset: 7424)
!1465 = !DIDerivedType(tag: DW_TAG_member, name: "sockfd", scope: !541, file: !130, line: 1017, baseType: !248, size: 32, align: 32, offset: 7488)
!1466 = !DIDerivedType(tag: DW_TAG_member, name: "writesockfd", scope: !541, file: !130, line: 1018, baseType: !248, size: 32, align: 32, offset: 7520)
!1467 = !DIDerivedType(tag: DW_TAG_member, name: "allocptr", scope: !541, file: !130, line: 1035, baseType: !1468, size: 640, align: 64, offset: 7552)
!1468 = !DICompositeType(tag: DW_TAG_structure_type, name: "dynamically_allocated_data", file: !130, line: 1024, size: 640, align: 64, elements: !1469)
!1469 = !{!1470, !1471, !1472, !1473, !1474, !1475, !1476, !1477, !1478, !1479}
!1470 = !DIDerivedType(tag: DW_TAG_member, name: "proxyuserpwd", scope: !1468, file: !130, line: 1025, baseType: !215, size: 64, align: 64)
!1471 = !DIDerivedType(tag: DW_TAG_member, name: "uagent", scope: !1468, file: !130, line: 1026, baseType: !215, size: 64, align: 64, offset: 64)
!1472 = !DIDerivedType(tag: DW_TAG_member, name: "accept_encoding", scope: !1468, file: !130, line: 1027, baseType: !215, size: 64, align: 64, offset: 128)
!1473 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd", scope: !1468, file: !130, line: 1028, baseType: !215, size: 64, align: 64, offset: 192)
!1474 = !DIDerivedType(tag: DW_TAG_member, name: "rangeline", scope: !1468, file: !130, line: 1029, baseType: !215, size: 64, align: 64, offset: 256)
!1475 = !DIDerivedType(tag: DW_TAG_member, name: "ref", scope: !1468, file: !130, line: 1030, baseType: !215, size: 64, align: 64, offset: 320)
!1476 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1468, file: !130, line: 1031, baseType: !215, size: 64, align: 64, offset: 384)
!1477 = !DIDerivedType(tag: DW_TAG_member, name: "cookiehost", scope: !1468, file: !130, line: 1032, baseType: !215, size: 64, align: 64, offset: 448)
!1478 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_transport", scope: !1468, file: !130, line: 1033, baseType: !215, size: 64, align: 64, offset: 512)
!1479 = !DIDerivedType(tag: DW_TAG_member, name: "te", scope: !1468, file: !130, line: 1034, baseType: !215, size: 64, align: 64, offset: 576)
!1480 = !DIDerivedType(tag: DW_TAG_member, name: "readchannel_inuse", scope: !541, file: !130, line: 1057, baseType: !211, size: 8, align: 8, offset: 8192)
!1481 = !DIDerivedType(tag: DW_TAG_member, name: "writechannel_inuse", scope: !541, file: !130, line: 1059, baseType: !211, size: 8, align: 8, offset: 8200)
!1482 = !DIDerivedType(tag: DW_TAG_member, name: "send_pipe", scope: !541, file: !130, line: 1061, baseType: !140, size: 256, align: 64, offset: 8256)
!1483 = !DIDerivedType(tag: DW_TAG_member, name: "recv_pipe", scope: !541, file: !130, line: 1063, baseType: !140, size: 256, align: 64, offset: 8512)
!1484 = !DIDerivedType(tag: DW_TAG_member, name: "master_buffer", scope: !541, file: !130, line: 1065, baseType: !215, size: 64, align: 64, offset: 8768)
!1485 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !541, file: !130, line: 1067, baseType: !158, size: 64, align: 64, offset: 8832)
!1486 = !DIDerivedType(tag: DW_TAG_member, name: "buf_len", scope: !541, file: !130, line: 1068, baseType: !158, size: 64, align: 64, offset: 8896)
!1487 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !541, file: !130, line: 1071, baseType: !722, size: 64, align: 64, offset: 8960)
!1488 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !541, file: !130, line: 1072, baseType: !148, size: 64, align: 64, offset: 9024)
!1489 = !DIDerivedType(tag: DW_TAG_member, name: "syserr_buf", scope: !541, file: !130, line: 1091, baseType: !1490, size: 2048, align: 8, offset: 9088)
!1490 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 2048, align: 8, elements: !1491)
!1491 = !{!1492}
!1492 = !DISubrange(count: 256)
!1493 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !541, file: !130, line: 1099, baseType: !215, size: 64, align: 64, offset: 11136)
!1494 = !DIDerivedType(tag: DW_TAG_member, name: "trlMax", scope: !541, file: !130, line: 1100, baseType: !177, size: 32, align: 32, offset: 11200)
!1495 = !DIDerivedType(tag: DW_TAG_member, name: "trlPos", scope: !541, file: !130, line: 1101, baseType: !177, size: 32, align: 32, offset: 11232)
!1496 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !541, file: !130, line: 1114, baseType: !1497, size: 1792, align: 64, offset: 11264)
!1497 = !DICompositeType(tag: DW_TAG_union_type, scope: !541, file: !130, line: 1103, size: 1792, align: 64, elements: !1498)
!1498 = !{!1499, !1546, !1551, !1556, !1559, !1607, !1621, !1633, !1640, !1658}
!1499 = !DIDerivedType(tag: DW_TAG_member, name: "ftpc", scope: !1497, file: !130, line: 1104, baseType: !1500, size: 1792, align: 64)
!1500 = !DICompositeType(tag: DW_TAG_structure_type, name: "ftp_conn", file: !317, line: 118, size: 1792, align: 64, elements: !1501)
!1501 = !{!1502, !1522, !1523, !1525, !1526, !1527, !1528, !1529, !1530, !1531, !1532, !1533, !1534, !1535, !1536, !1537, !1538, !1540, !1541, !1542, !1543, !1544, !1545}
!1502 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1500, file: !317, line: 119, baseType: !1503, size: 896, align: 64)
!1503 = !DICompositeType(tag: DW_TAG_structure_type, name: "pingpong", file: !1504, line: 48, size: 896, align: 64, elements: !1505)
!1504 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1505 = !{!1506, !1507, !1508, !1509, !1510, !1511, !1512, !1513, !1514, !1515, !1516, !1517, !1518}
!1506 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !1503, file: !1504, line: 49, baseType: !215, size: 64, align: 64)
!1507 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !1503, file: !1504, line: 50, baseType: !158, size: 64, align: 64, offset: 64)
!1508 = !DIDerivedType(tag: DW_TAG_member, name: "nread_resp", scope: !1503, file: !1504, line: 51, baseType: !158, size: 64, align: 64, offset: 128)
!1509 = !DIDerivedType(tag: DW_TAG_member, name: "linestart_resp", scope: !1503, file: !1504, line: 52, baseType: !215, size: 64, align: 64, offset: 192)
!1510 = !DIDerivedType(tag: DW_TAG_member, name: "pending_resp", scope: !1503, file: !1504, line: 54, baseType: !211, size: 8, align: 8, offset: 256)
!1511 = !DIDerivedType(tag: DW_TAG_member, name: "sendthis", scope: !1503, file: !1504, line: 57, baseType: !215, size: 64, align: 64, offset: 320)
!1512 = !DIDerivedType(tag: DW_TAG_member, name: "sendleft", scope: !1503, file: !1504, line: 59, baseType: !158, size: 64, align: 64, offset: 384)
!1513 = !DIDerivedType(tag: DW_TAG_member, name: "sendsize", scope: !1503, file: !1504, line: 60, baseType: !158, size: 64, align: 64, offset: 448)
!1514 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !1503, file: !1504, line: 61, baseType: !201, size: 128, align: 64, offset: 512)
!1515 = !DIDerivedType(tag: DW_TAG_member, name: "response_time", scope: !1503, file: !1504, line: 63, baseType: !191, size: 64, align: 64, offset: 640)
!1516 = !DIDerivedType(tag: DW_TAG_member, name: "conn", scope: !1503, file: !1504, line: 66, baseType: !550, size: 64, align: 64, offset: 704)
!1517 = !DIDerivedType(tag: DW_TAG_member, name: "statemach_act", scope: !1503, file: !1504, line: 72, baseType: !1416, size: 64, align: 64, offset: 768)
!1518 = !DIDerivedType(tag: DW_TAG_member, name: "endofresp", scope: !1503, file: !1504, line: 74, baseType: !1519, size: 64, align: 64, offset: 832)
!1519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1520, size: 64, align: 64)
!1520 = !DISubroutineType(types: !1521)
!1521 = !{!211, !550, !215, !158, !1434}
!1522 = !DIDerivedType(tag: DW_TAG_member, name: "entrypath", scope: !1500, file: !317, line: 120, baseType: !215, size: 64, align: 64, offset: 896)
!1523 = !DIDerivedType(tag: DW_TAG_member, name: "dirs", scope: !1500, file: !317, line: 121, baseType: !1524, size: 64, align: 64, offset: 960)
!1524 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !215, size: 64, align: 64)
!1525 = !DIDerivedType(tag: DW_TAG_member, name: "dirdepth", scope: !1500, file: !317, line: 122, baseType: !177, size: 32, align: 32, offset: 1024)
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "diralloc", scope: !1500, file: !317, line: 123, baseType: !177, size: 32, align: 32, offset: 1056)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !1500, file: !317, line: 124, baseType: !215, size: 64, align: 64, offset: 1088)
!1528 = !DIDerivedType(tag: DW_TAG_member, name: "dont_check", scope: !1500, file: !317, line: 125, baseType: !211, size: 8, align: 8, offset: 1152)
!1529 = !DIDerivedType(tag: DW_TAG_member, name: "ctl_valid", scope: !1500, file: !317, line: 128, baseType: !211, size: 8, align: 8, offset: 1160)
!1530 = !DIDerivedType(tag: DW_TAG_member, name: "cwddone", scope: !1500, file: !317, line: 131, baseType: !211, size: 8, align: 8, offset: 1168)
!1531 = !DIDerivedType(tag: DW_TAG_member, name: "cwdfail", scope: !1500, file: !317, line: 133, baseType: !211, size: 8, align: 8, offset: 1176)
!1532 = !DIDerivedType(tag: DW_TAG_member, name: "wait_data_conn", scope: !1500, file: !317, line: 135, baseType: !211, size: 8, align: 8, offset: 1184)
!1533 = !DIDerivedType(tag: DW_TAG_member, name: "prevpath", scope: !1500, file: !317, line: 136, baseType: !215, size: 64, align: 64, offset: 1216)
!1534 = !DIDerivedType(tag: DW_TAG_member, name: "transfertype", scope: !1500, file: !317, line: 137, baseType: !216, size: 8, align: 8, offset: 1280)
!1535 = !DIDerivedType(tag: DW_TAG_member, name: "count1", scope: !1500, file: !317, line: 139, baseType: !177, size: 32, align: 32, offset: 1312)
!1536 = !DIDerivedType(tag: DW_TAG_member, name: "count2", scope: !1500, file: !317, line: 140, baseType: !177, size: 32, align: 32, offset: 1344)
!1537 = !DIDerivedType(tag: DW_TAG_member, name: "count3", scope: !1500, file: !317, line: 141, baseType: !177, size: 32, align: 32, offset: 1376)
!1538 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1500, file: !317, line: 142, baseType: !1539, size: 32, align: 32, offset: 1408)
!1539 = !DIDerivedType(tag: DW_TAG_typedef, name: "ftpstate", file: !317, line: 80, baseType: !423)
!1540 = !DIDerivedType(tag: DW_TAG_member, name: "state_saved", scope: !1500, file: !317, line: 143, baseType: !1539, size: 32, align: 32, offset: 1440)
!1541 = !DIDerivedType(tag: DW_TAG_member, name: "retr_size_saved", scope: !1500, file: !317, line: 145, baseType: !189, size: 64, align: 64, offset: 1472)
!1542 = !DIDerivedType(tag: DW_TAG_member, name: "server_os", scope: !1500, file: !317, line: 146, baseType: !215, size: 64, align: 64, offset: 1536)
!1543 = !DIDerivedType(tag: DW_TAG_member, name: "known_filesize", scope: !1500, file: !317, line: 147, baseType: !189, size: 64, align: 64, offset: 1600)
!1544 = !DIDerivedType(tag: DW_TAG_member, name: "newhost", scope: !1500, file: !317, line: 152, baseType: !215, size: 64, align: 64, offset: 1664)
!1545 = !DIDerivedType(tag: DW_TAG_member, name: "newport", scope: !1500, file: !317, line: 153, baseType: !684, size: 16, align: 16, offset: 1728)
!1546 = !DIDerivedType(tag: DW_TAG_member, name: "httpc", scope: !1497, file: !130, line: 1105, baseType: !1547, size: 32, align: 32)
!1547 = !DICompositeType(tag: DW_TAG_structure_type, name: "http_conn", file: !1548, line: 200, size: 32, align: 32, elements: !1549)
!1548 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1549 = !{!1550}
!1550 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !1547, file: !1548, line: 227, baseType: !177, size: 32, align: 32)
!1551 = !DIDerivedType(tag: DW_TAG_member, name: "sshc", scope: !1497, file: !130, line: 1106, baseType: !1552, size: 64, align: 64)
!1552 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssh_conn", file: !1553, line: 110, size: 64, align: 64, elements: !1554)
!1553 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ssh.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1554 = !{!1555}
!1555 = !DIDerivedType(tag: DW_TAG_member, name: "authlist", scope: !1552, file: !1553, line: 111, baseType: !928, size: 64, align: 64)
!1556 = !DIDerivedType(tag: DW_TAG_member, name: "tftpc", scope: !1497, file: !130, line: 1107, baseType: !1557, size: 64, align: 64)
!1557 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1558, size: 64, align: 64)
!1558 = !DICompositeType(tag: DW_TAG_structure_type, name: "tftp_state_data", file: !130, line: 1107, flags: DIFlagFwdDecl)
!1559 = !DIDerivedType(tag: DW_TAG_member, name: "imapc", scope: !1497, file: !130, line: 1108, baseType: !1560, size: 1472, align: 64)
!1560 = !DICompositeType(tag: DW_TAG_structure_type, name: "imap_conn", file: !462, line: 70, size: 1472, align: 64, elements: !1561)
!1561 = !{!1562, !1563, !1565, !1566, !1598, !1599, !1600, !1602, !1603, !1604, !1605, !1606}
!1562 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1560, file: !462, line: 71, baseType: !1503, size: 896, align: 64)
!1563 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1560, file: !462, line: 72, baseType: !1564, size: 32, align: 32, offset: 896)
!1564 = !DIDerivedType(tag: DW_TAG_typedef, name: "imapstate", file: !462, line: 50, baseType: !461)
!1565 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1560, file: !462, line: 73, baseType: !211, size: 8, align: 8, offset: 928)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1560, file: !462, line: 74, baseType: !1567, size: 256, align: 64, offset: 960)
!1567 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASL", file: !481, line: 101, size: 256, align: 64, elements: !1568)
!1568 = !{!1569, !1590, !1592, !1593, !1594, !1595, !1596, !1597}
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "params", scope: !1567, file: !481, line: 102, baseType: !1570, size: 64, align: 64)
!1570 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1571, size: 64, align: 64)
!1571 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1572)
!1572 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASLproto", file: !481, line: 86, size: 384, align: 64, elements: !1573)
!1573 = !{!1574, !1575, !1576, !1577, !1578, !1582, !1586}
!1574 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !1572, file: !481, line: 87, baseType: !928, size: 64, align: 64)
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "contcode", scope: !1572, file: !481, line: 88, baseType: !177, size: 32, align: 32, offset: 64)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "finalcode", scope: !1572, file: !481, line: 89, baseType: !177, size: 32, align: 32, offset: 96)
!1577 = !DIDerivedType(tag: DW_TAG_member, name: "maxirlen", scope: !1572, file: !481, line: 90, baseType: !158, size: 64, align: 64, offset: 128)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "sendauth", scope: !1572, file: !481, line: 91, baseType: !1579, size: 64, align: 64, offset: 192)
!1579 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1580, size: 64, align: 64)
!1580 = !DISubroutineType(types: !1581)
!1581 = !{!554, !550, !928, !928}
!1582 = !DIDerivedType(tag: DW_TAG_member, name: "sendcont", scope: !1572, file: !481, line: 94, baseType: !1583, size: 64, align: 64, offset: 256)
!1583 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1584, size: 64, align: 64)
!1584 = !DISubroutineType(types: !1585)
!1585 = !{!554, !550, !928}
!1586 = !DIDerivedType(tag: DW_TAG_member, name: "getmessage", scope: !1572, file: !481, line: 96, baseType: !1587, size: 64, align: 64, offset: 320)
!1587 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1588, size: 64, align: 64)
!1588 = !DISubroutineType(types: !1589)
!1589 = !{null, !215, !1524}
!1590 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1567, file: !481, line: 103, baseType: !1591, size: 32, align: 32, offset: 64)
!1591 = !DIDerivedType(tag: DW_TAG_typedef, name: "saslstate", file: !481, line: 76, baseType: !480)
!1592 = !DIDerivedType(tag: DW_TAG_member, name: "authmechs", scope: !1567, file: !481, line: 104, baseType: !782, size: 32, align: 32, offset: 96)
!1593 = !DIDerivedType(tag: DW_TAG_member, name: "prefmech", scope: !1567, file: !481, line: 105, baseType: !782, size: 32, align: 32, offset: 128)
!1594 = !DIDerivedType(tag: DW_TAG_member, name: "authused", scope: !1567, file: !481, line: 106, baseType: !782, size: 32, align: 32, offset: 160)
!1595 = !DIDerivedType(tag: DW_TAG_member, name: "resetprefs", scope: !1567, file: !481, line: 107, baseType: !211, size: 8, align: 8, offset: 192)
!1596 = !DIDerivedType(tag: DW_TAG_member, name: "mutual_auth", scope: !1567, file: !481, line: 108, baseType: !211, size: 8, align: 8, offset: 200)
!1597 = !DIDerivedType(tag: DW_TAG_member, name: "force_ir", scope: !1567, file: !481, line: 109, baseType: !211, size: 8, align: 8, offset: 208)
!1598 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1560, file: !462, line: 75, baseType: !782, size: 32, align: 32, offset: 1216)
!1599 = !DIDerivedType(tag: DW_TAG_member, name: "cmdid", scope: !1560, file: !462, line: 76, baseType: !177, size: 32, align: 32, offset: 1248)
!1600 = !DIDerivedType(tag: DW_TAG_member, name: "resptag", scope: !1560, file: !462, line: 77, baseType: !1601, size: 40, align: 8, offset: 1280)
!1601 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 40, align: 8, elements: !573)
!1602 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1560, file: !462, line: 78, baseType: !211, size: 8, align: 8, offset: 1320)
!1603 = !DIDerivedType(tag: DW_TAG_member, name: "login_disabled", scope: !1560, file: !462, line: 79, baseType: !211, size: 8, align: 8, offset: 1328)
!1604 = !DIDerivedType(tag: DW_TAG_member, name: "ir_supported", scope: !1560, file: !462, line: 80, baseType: !211, size: 8, align: 8, offset: 1336)
!1605 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox", scope: !1560, file: !462, line: 81, baseType: !215, size: 64, align: 64, offset: 1344)
!1606 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox_uidvalidity", scope: !1560, file: !462, line: 82, baseType: !215, size: 64, align: 64, offset: 1408)
!1607 = !DIDerivedType(tag: DW_TAG_member, name: "pop3c", scope: !1497, file: !130, line: 1109, baseType: !1608, size: 1536, align: 64)
!1608 = !DICompositeType(tag: DW_TAG_structure_type, name: "pop3_conn", file: !501, line: 60, size: 1536, align: 64, elements: !1609)
!1609 = !{!1610, !1611, !1613, !1614, !1615, !1616, !1617, !1618, !1619, !1620}
!1610 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1608, file: !501, line: 61, baseType: !1503, size: 896, align: 64)
!1611 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1608, file: !501, line: 62, baseType: !1612, size: 32, align: 32, offset: 896)
!1612 = !DIDerivedType(tag: DW_TAG_typedef, name: "pop3state", file: !501, line: 46, baseType: !500)
!1613 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1608, file: !501, line: 63, baseType: !211, size: 8, align: 8, offset: 928)
!1614 = !DIDerivedType(tag: DW_TAG_member, name: "eob", scope: !1608, file: !501, line: 64, baseType: !158, size: 64, align: 64, offset: 960)
!1615 = !DIDerivedType(tag: DW_TAG_member, name: "strip", scope: !1608, file: !501, line: 66, baseType: !158, size: 64, align: 64, offset: 1024)
!1616 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1608, file: !501, line: 68, baseType: !1567, size: 256, align: 64, offset: 1088)
!1617 = !DIDerivedType(tag: DW_TAG_member, name: "authtypes", scope: !1608, file: !501, line: 69, baseType: !782, size: 32, align: 32, offset: 1344)
!1618 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1608, file: !501, line: 70, baseType: !782, size: 32, align: 32, offset: 1376)
!1619 = !DIDerivedType(tag: DW_TAG_member, name: "apoptimestamp", scope: !1608, file: !501, line: 71, baseType: !215, size: 64, align: 64, offset: 1408)
!1620 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1608, file: !501, line: 72, baseType: !211, size: 8, align: 8, offset: 1472)
!1621 = !DIDerivedType(tag: DW_TAG_member, name: "smtpc", scope: !1497, file: !130, line: 1110, baseType: !1622, size: 1344, align: 64)
!1622 = !DICompositeType(tag: DW_TAG_structure_type, name: "smtp_conn", file: !516, line: 65, size: 1344, align: 64, elements: !1623)
!1623 = !{!1624, !1625, !1627, !1628, !1629, !1630, !1631, !1632}
!1624 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1622, file: !516, line: 66, baseType: !1503, size: 896, align: 64)
!1625 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1622, file: !516, line: 67, baseType: !1626, size: 32, align: 32, offset: 896)
!1626 = !DIDerivedType(tag: DW_TAG_typedef, name: "smtpstate", file: !516, line: 48, baseType: !515)
!1627 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1622, file: !516, line: 68, baseType: !211, size: 8, align: 8, offset: 928)
!1628 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1622, file: !516, line: 69, baseType: !215, size: 64, align: 64, offset: 960)
!1629 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1622, file: !516, line: 70, baseType: !1567, size: 256, align: 64, offset: 1024)
!1630 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1622, file: !516, line: 71, baseType: !211, size: 8, align: 8, offset: 1280)
!1631 = !DIDerivedType(tag: DW_TAG_member, name: "size_supported", scope: !1622, file: !516, line: 72, baseType: !211, size: 8, align: 8, offset: 1288)
!1632 = !DIDerivedType(tag: DW_TAG_member, name: "auth_supported", scope: !1622, file: !516, line: 74, baseType: !211, size: 8, align: 8, offset: 1296)
!1633 = !DIDerivedType(tag: DW_TAG_member, name: "rtspc", scope: !1497, file: !130, line: 1111, baseType: !1634, size: 192, align: 64)
!1634 = !DICompositeType(tag: DW_TAG_structure_type, name: "rtsp_conn", file: !1635, line: 43, size: 192, align: 64, elements: !1636)
!1635 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/rtsp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1636 = !{!1637, !1638, !1639}
!1637 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_buf", scope: !1634, file: !1635, line: 44, baseType: !215, size: 64, align: 64)
!1638 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_bufsize", scope: !1634, file: !1635, line: 45, baseType: !256, size: 64, align: 64, offset: 64)
!1639 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_channel", scope: !1634, file: !1635, line: 46, baseType: !177, size: 32, align: 32, offset: 128)
!1640 = !DIDerivedType(tag: DW_TAG_member, name: "smbc", scope: !1497, file: !130, line: 1112, baseType: !1641, size: 640, align: 64)
!1641 = !DICompositeType(tag: DW_TAG_structure_type, name: "smb_conn", file: !533, line: 33, size: 640, align: 64, elements: !1642)
!1642 = !{!1643, !1644, !1645, !1646, !1651, !1652, !1653, !1654, !1655, !1656, !1657}
!1643 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1641, file: !533, line: 34, baseType: !532, size: 32, align: 32)
!1644 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1641, file: !533, line: 35, baseType: !215, size: 64, align: 64, offset: 64)
!1645 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1641, file: !533, line: 36, baseType: !215, size: 64, align: 64, offset: 128)
!1646 = !DIDerivedType(tag: DW_TAG_member, name: "challenge", scope: !1641, file: !533, line: 37, baseType: !1647, size: 64, align: 8, offset: 192)
!1647 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1648, size: 64, align: 8, elements: !1649)
!1648 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!1649 = !{!1650}
!1650 = !DISubrange(count: 8)
!1651 = !DIDerivedType(tag: DW_TAG_member, name: "session_key", scope: !1641, file: !533, line: 38, baseType: !782, size: 32, align: 32, offset: 256)
!1652 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1641, file: !533, line: 39, baseType: !684, size: 16, align: 16, offset: 288)
!1653 = !DIDerivedType(tag: DW_TAG_member, name: "recv_buf", scope: !1641, file: !533, line: 40, baseType: !215, size: 64, align: 64, offset: 320)
!1654 = !DIDerivedType(tag: DW_TAG_member, name: "upload_size", scope: !1641, file: !533, line: 41, baseType: !158, size: 64, align: 64, offset: 384)
!1655 = !DIDerivedType(tag: DW_TAG_member, name: "send_size", scope: !1641, file: !533, line: 42, baseType: !158, size: 64, align: 64, offset: 448)
!1656 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1641, file: !533, line: 43, baseType: !158, size: 64, align: 64, offset: 512)
!1657 = !DIDerivedType(tag: DW_TAG_member, name: "got", scope: !1641, file: !533, line: 44, baseType: !158, size: 64, align: 64, offset: 576)
!1658 = !DIDerivedType(tag: DW_TAG_member, name: "generic", scope: !1497, file: !130, line: 1113, baseType: !148, size: 64, align: 64)
!1659 = !DIDerivedType(tag: DW_TAG_member, name: "cselect_bits", scope: !541, file: !130, line: 1116, baseType: !177, size: 32, align: 32, offset: 13056)
!1660 = !DIDerivedType(tag: DW_TAG_member, name: "waitfor", scope: !541, file: !130, line: 1117, baseType: !177, size: 32, align: 32, offset: 13088)
!1661 = !DIDerivedType(tag: DW_TAG_member, name: "localdev", scope: !541, file: !130, line: 1128, baseType: !215, size: 64, align: 64, offset: 13120)
!1662 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !541, file: !130, line: 1129, baseType: !684, size: 16, align: 16, offset: 13184)
!1663 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !541, file: !130, line: 1130, baseType: !177, size: 32, align: 32, offset: 13216)
!1664 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_state", scope: !541, file: !130, line: 1137, baseType: !1665, size: 64, align: 32, offset: 13248)
!1665 = !DICompositeType(tag: DW_TAG_array_type, baseType: !540, size: 64, align: 32, elements: !1300)
!1666 = !DIDerivedType(tag: DW_TAG_member, name: "bundle", scope: !541, file: !130, line: 1138, baseType: !1667, size: 64, align: 64, offset: 13312)
!1667 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1668, size: 64, align: 64)
!1668 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectbundle", file: !619, line: 38, size: 384, align: 64, elements: !1669)
!1669 = !{!1670, !1671, !1672}
!1670 = !DIDerivedType(tag: DW_TAG_member, name: "multiuse", scope: !1668, file: !619, line: 39, baseType: !177, size: 32, align: 32)
!1671 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !1668, file: !619, line: 40, baseType: !158, size: 64, align: 64, offset: 64)
!1672 = !DIDerivedType(tag: DW_TAG_member, name: "conn_list", scope: !1668, file: !619, line: 41, baseType: !140, size: 256, align: 64, offset: 128)
!1673 = !DIDerivedType(tag: DW_TAG_member, name: "negnpn", scope: !541, file: !130, line: 1140, baseType: !177, size: 32, align: 32, offset: 13376)
!1674 = !{!1675, !1676, !1677}
!1675 = !DIEnumerator(name: "TUNNEL_INIT", value: 0)
!1676 = !DIEnumerator(name: "TUNNEL_CONNECT", value: 1)
!1677 = !DIEnumerator(name: "TUNNEL_COMPLETE", value: 2)
!1678 = !{!158, !256, !191}
!1679 = !{!1680, !1685, !1688, !1691, !1701, !1704, !1708, !1711, !1714, !1715}
!1680 = distinct !DISubprogram(name: "Curl_pp_state_timeout", scope: !1, file: !1, line: 47, type: !1681, isLocal: false, isDefinition: true, scopeLine: 48, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1681 = !DISubroutineType(types: !1682)
!1682 = !{!242, !1683}
!1683 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1503, size: 64, align: 64)
!1684 = !{}
!1685 = distinct !DISubprogram(name: "Curl_pp_statemach", scope: !1, file: !1, line: 81, type: !1686, isLocal: false, isDefinition: true, scopeLine: 82, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1686 = !DISubroutineType(types: !1687)
!1687 = !{!554, !1683, !211}
!1688 = distinct !DISubprogram(name: "Curl_pp_init", scope: !1, file: !1, line: 140, type: !1689, isLocal: false, isDefinition: true, scopeLine: 141, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1689 = !DISubroutineType(types: !1690)
!1690 = !{null, !1683}
!1691 = distinct !DISubprogram(name: "Curl_pp_vsendf", scope: !1, file: !1, line: 161, type: !1692, isLocal: false, isDefinition: true, scopeLine: 164, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1692 = !DISubroutineType(types: !1693)
!1693 = !{!554, !1683, !928, !1694}
!1694 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1695, size: 64, align: 64)
!1695 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 147, size: 192, align: 64, elements: !1696)
!1696 = !{!1697, !1698, !1699, !1700}
!1697 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !1695, file: !1, line: 147, baseType: !782, size: 32, align: 32)
!1698 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !1695, file: !1, line: 147, baseType: !782, size: 32, align: 32, offset: 32)
!1699 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !1695, file: !1, line: 147, baseType: !148, size: 64, align: 64, offset: 64)
!1700 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !1695, file: !1, line: 147, baseType: !148, size: 64, align: 64, offset: 128)
!1701 = distinct !DISubprogram(name: "Curl_pp_sendf", scope: !1, file: !1, line: 248, type: !1702, isLocal: false, isDefinition: true, scopeLine: 250, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1702 = !DISubroutineType(types: !1703)
!1703 = !{!554, !1683, !928, null}
!1704 = distinct !DISubprogram(name: "Curl_pp_readresp", scope: !1, file: !1, line: 267, type: !1705, isLocal: false, isDefinition: true, scopeLine: 271, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1705 = !DISubroutineType(types: !1706)
!1706 = !{!554, !248, !1683, !1434, !1707}
!1707 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!1708 = distinct !DISubprogram(name: "Curl_pp_getsock", scope: !1, file: !1, line: 453, type: !1709, isLocal: false, isDefinition: true, scopeLine: 456, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1709 = !DISubroutineType(types: !1710)
!1710 = !{!177, !1683, !1442, !177}
!1711 = distinct !DISubprogram(name: "Curl_pp_flushsend", scope: !1, file: !1, line: 473, type: !1712, isLocal: false, isDefinition: true, scopeLine: 474, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1712 = !DISubroutineType(types: !1713)
!1713 = !{!554, !1683}
!1714 = distinct !DISubprogram(name: "Curl_pp_disconnect", scope: !1, file: !1, line: 497, type: !1712, isLocal: false, isDefinition: true, scopeLine: 498, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1715 = distinct !DISubprogram(name: "Curl_pp_moredata", scope: !1, file: !1, line: 504, type: !1716, isLocal: false, isDefinition: true, scopeLine: 505, flags: DIFlagPrototyped, isOptimized: false, variables: !1684)
!1716 = !DISubroutineType(types: !1717)
!1717 = !{!211, !1683}
!1718 = !{i32 2, !"Dwarf Version", i32 4}
!1719 = !{i32 2, !"Debug Info Version", i32 3}
!1720 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1721 = !DILocalVariable(name: "pp", arg: 1, scope: !1680, file: !1, line: 47, type: !1683)
!1722 = !DIExpression()
!1723 = !DILocation(line: 47, column: 47, scope: !1680)
!1724 = !DILocalVariable(name: "conn", scope: !1680, file: !1, line: 49, type: !550)
!1725 = !DILocation(line: 49, column: 23, scope: !1680)
!1726 = !DILocation(line: 49, column: 30, scope: !1680)
!1727 = !DILocation(line: 49, column: 34, scope: !1680)
!1728 = !DILocalVariable(name: "data", scope: !1680, file: !1, line: 50, type: !544)
!1729 = !DILocation(line: 50, column: 21, scope: !1680)
!1730 = !DILocation(line: 50, column: 26, scope: !1680)
!1731 = !DILocation(line: 50, column: 32, scope: !1680)
!1732 = !DILocalVariable(name: "timeout_ms", scope: !1680, file: !1, line: 51, type: !242)
!1733 = !DILocation(line: 51, column: 10, scope: !1680)
!1734 = !DILocalVariable(name: "timeout2_ms", scope: !1680, file: !1, line: 52, type: !242)
!1735 = !DILocation(line: 52, column: 10, scope: !1680)
!1736 = !DILocalVariable(name: "response_time", scope: !1680, file: !1, line: 53, type: !191)
!1737 = !DILocation(line: 53, column: 8, scope: !1680)
!1738 = !DILocation(line: 53, column: 24, scope: !1680)
!1739 = !DILocation(line: 53, column: 30, scope: !1680)
!1740 = !DILocation(line: 53, column: 34, scope: !1680)
!1741 = !DILocation(line: 53, column: 23, scope: !1680)
!1742 = !DILocation(line: 54, column: 5, scope: !1680)
!1743 = !DILocation(line: 54, column: 11, scope: !1680)
!1744 = !DILocation(line: 54, column: 15, scope: !1680)
!1745 = !DILocation(line: 53, column: 23, scope: !1746)
!1746 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 1)
!1747 = !DILocation(line: 54, column: 40, scope: !1746)
!1748 = !DILocation(line: 54, column: 44, scope: !1746)
!1749 = !DILocation(line: 53, column: 23, scope: !1750)
!1750 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 2)
!1751 = !DILocation(line: 53, column: 23, scope: !1752)
!1752 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 3)
!1753 = !DILocation(line: 53, column: 8, scope: !1752)
!1754 = !DILocation(line: 63, column: 16, scope: !1680)
!1755 = !DILocation(line: 64, column: 5, scope: !1680)
!1756 = !DILocation(line: 64, column: 5, scope: !1746)
!1757 = !DILocation(line: 63, column: 30, scope: !1680)
!1758 = !DILocation(line: 63, column: 14, scope: !1680)
!1759 = !DILocation(line: 66, column: 6, scope: !1760)
!1760 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 66, column: 6)
!1761 = !DILocation(line: 66, column: 12, scope: !1760)
!1762 = !DILocation(line: 66, column: 16, scope: !1760)
!1763 = !DILocation(line: 66, column: 6, scope: !1680)
!1764 = !DILocation(line: 68, column: 19, scope: !1765)
!1765 = distinct !DILexicalBlock(scope: !1760, file: !1, line: 66, column: 25)
!1766 = !DILocation(line: 68, column: 25, scope: !1765)
!1767 = !DILocation(line: 68, column: 29, scope: !1765)
!1768 = !DILocation(line: 69, column: 7, scope: !1765)
!1769 = !DILocation(line: 69, column: 7, scope: !1770)
!1770 = !DILexicalBlockFile(scope: !1765, file: !1, discriminator: 1)
!1771 = !DILocation(line: 68, column: 37, scope: !1765)
!1772 = !DILocation(line: 68, column: 17, scope: !1765)
!1773 = !DILocation(line: 72, column: 18, scope: !1765)
!1774 = !DILocation(line: 72, column: 18, scope: !1770)
!1775 = !DILocation(line: 72, column: 18, scope: !1776)
!1776 = !DILexicalBlockFile(scope: !1765, file: !1, discriminator: 2)
!1777 = !DILocation(line: 72, column: 18, scope: !1778)
!1778 = !DILexicalBlockFile(scope: !1765, file: !1, discriminator: 3)
!1779 = !DILocation(line: 72, column: 16, scope: !1778)
!1780 = !DILocation(line: 73, column: 3, scope: !1765)
!1781 = !DILocation(line: 75, column: 10, scope: !1680)
!1782 = !DILocation(line: 75, column: 3, scope: !1680)
!1783 = !DILocalVariable(name: "pp", arg: 1, scope: !1685, file: !1, line: 81, type: !1683)
!1784 = !DILocation(line: 81, column: 45, scope: !1685)
!1785 = !DILocalVariable(name: "block", arg: 2, scope: !1685, file: !1, line: 81, type: !211)
!1786 = !DILocation(line: 81, column: 54, scope: !1685)
!1787 = !DILocalVariable(name: "conn", scope: !1685, file: !1, line: 83, type: !550)
!1788 = !DILocation(line: 83, column: 23, scope: !1685)
!1789 = !DILocation(line: 83, column: 30, scope: !1685)
!1790 = !DILocation(line: 83, column: 34, scope: !1685)
!1791 = !DILocalVariable(name: "sock", scope: !1685, file: !1, line: 84, type: !248)
!1792 = !DILocation(line: 84, column: 17, scope: !1685)
!1793 = !DILocation(line: 84, column: 24, scope: !1685)
!1794 = !DILocation(line: 84, column: 30, scope: !1685)
!1795 = !DILocalVariable(name: "rc", scope: !1685, file: !1, line: 85, type: !177)
!1796 = !DILocation(line: 85, column: 7, scope: !1685)
!1797 = !DILocalVariable(name: "interval_ms", scope: !1685, file: !1, line: 86, type: !242)
!1798 = !DILocation(line: 86, column: 10, scope: !1685)
!1799 = !DILocalVariable(name: "timeout_ms", scope: !1685, file: !1, line: 87, type: !242)
!1800 = !DILocation(line: 87, column: 10, scope: !1685)
!1801 = !DILocation(line: 87, column: 45, scope: !1685)
!1802 = !DILocation(line: 87, column: 23, scope: !1685)
!1803 = !DILocalVariable(name: "data", scope: !1685, file: !1, line: 88, type: !544)
!1804 = !DILocation(line: 88, column: 21, scope: !1685)
!1805 = !DILocation(line: 88, column: 26, scope: !1685)
!1806 = !DILocation(line: 88, column: 32, scope: !1685)
!1807 = !DILocalVariable(name: "result", scope: !1685, file: !1, line: 89, type: !554)
!1808 = !DILocation(line: 89, column: 12, scope: !1685)
!1809 = !DILocation(line: 91, column: 6, scope: !1810)
!1810 = distinct !DILexicalBlock(scope: !1685, file: !1, line: 91, column: 6)
!1811 = !DILocation(line: 91, column: 17, scope: !1810)
!1812 = !DILocation(line: 91, column: 6, scope: !1685)
!1813 = !DILocation(line: 92, column: 11, scope: !1814)
!1814 = distinct !DILexicalBlock(scope: !1810, file: !1, line: 91, column: 22)
!1815 = !DILocation(line: 92, column: 5, scope: !1814)
!1816 = !DILocation(line: 93, column: 5, scope: !1814)
!1817 = !DILocation(line: 96, column: 6, scope: !1818)
!1818 = distinct !DILexicalBlock(scope: !1685, file: !1, line: 96, column: 6)
!1819 = !DILocation(line: 96, column: 6, scope: !1685)
!1820 = !DILocation(line: 97, column: 17, scope: !1821)
!1821 = distinct !DILexicalBlock(scope: !1818, file: !1, line: 96, column: 13)
!1822 = !DILocation(line: 98, column: 8, scope: !1823)
!1823 = distinct !DILexicalBlock(scope: !1821, file: !1, line: 98, column: 8)
!1824 = !DILocation(line: 98, column: 21, scope: !1823)
!1825 = !DILocation(line: 98, column: 19, scope: !1823)
!1826 = !DILocation(line: 98, column: 8, scope: !1821)
!1827 = !DILocation(line: 99, column: 21, scope: !1823)
!1828 = !DILocation(line: 99, column: 19, scope: !1823)
!1829 = !DILocation(line: 99, column: 7, scope: !1823)
!1830 = !DILocation(line: 100, column: 3, scope: !1821)
!1831 = !DILocation(line: 102, column: 17, scope: !1818)
!1832 = !DILocation(line: 106, column: 28, scope: !1833)
!1833 = distinct !DILexicalBlock(scope: !1834, file: !1, line: 106, column: 11)
!1834 = distinct !DILexicalBlock(scope: !1685, file: !1, line: 104, column: 6)
!1835 = !DILocation(line: 106, column: 11, scope: !1833)
!1836 = !DILocation(line: 106, column: 11, scope: !1834)
!1837 = !DILocation(line: 108, column: 8, scope: !1833)
!1838 = !DILocation(line: 108, column: 5, scope: !1833)
!1839 = !DILocation(line: 109, column: 12, scope: !1840)
!1840 = distinct !DILexicalBlock(scope: !1833, file: !1, line: 109, column: 11)
!1841 = !DILocation(line: 109, column: 16, scope: !1840)
!1842 = !DILocation(line: 109, column: 25, scope: !1840)
!1843 = !DILocation(line: 109, column: 11, scope: !1844)
!1844 = !DILexicalBlockFile(scope: !1833, file: !1, discriminator: 1)
!1845 = !DILocation(line: 111, column: 8, scope: !1840)
!1846 = !DILocation(line: 111, column: 5, scope: !1840)
!1847 = !DILocation(line: 113, column: 28, scope: !1840)
!1848 = !DILocation(line: 113, column: 32, scope: !1840)
!1849 = !DILocation(line: 113, column: 28, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !1840, file: !1, discriminator: 1)
!1851 = !DILocation(line: 113, column: 57, scope: !1852)
!1852 = !DILexicalBlockFile(scope: !1840, file: !1, discriminator: 2)
!1853 = !DILocation(line: 113, column: 28, scope: !1852)
!1854 = !DILocation(line: 113, column: 28, scope: !1855)
!1855 = !DILexicalBlockFile(scope: !1840, file: !1, discriminator: 3)
!1856 = !DILocation(line: 115, column: 28, scope: !1840)
!1857 = !DILocation(line: 115, column: 32, scope: !1840)
!1858 = !DILocation(line: 115, column: 41, scope: !1850)
!1859 = !DILocation(line: 115, column: 28, scope: !1850)
!1860 = !DILocation(line: 115, column: 28, scope: !1852)
!1861 = !DILocation(line: 115, column: 28, scope: !1855)
!1862 = !DILocation(line: 116, column: 28, scope: !1840)
!1863 = !DILocation(line: 113, column: 10, scope: !1864)
!1864 = !DILexicalBlockFile(scope: !1840, file: !1, discriminator: 4)
!1865 = !DILocation(line: 113, column: 8, scope: !1864)
!1866 = !DILocation(line: 118, column: 6, scope: !1867)
!1867 = distinct !DILexicalBlock(scope: !1685, file: !1, line: 118, column: 6)
!1868 = !DILocation(line: 118, column: 6, scope: !1685)
!1869 = !DILocation(line: 120, column: 24, scope: !1870)
!1870 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 120, column: 8)
!1871 = distinct !DILexicalBlock(scope: !1867, file: !1, line: 118, column: 13)
!1872 = !DILocation(line: 120, column: 8, scope: !1870)
!1873 = !DILocation(line: 120, column: 8, scope: !1871)
!1874 = !DILocation(line: 121, column: 14, scope: !1870)
!1875 = !DILocation(line: 121, column: 7, scope: !1870)
!1876 = !DILocation(line: 123, column: 32, scope: !1870)
!1877 = !DILocation(line: 123, column: 38, scope: !1870)
!1878 = !DILocation(line: 123, column: 16, scope: !1870)
!1879 = !DILocation(line: 123, column: 16, scope: !1880)
!1880 = !DILexicalBlockFile(scope: !1870, file: !1, discriminator: 1)
!1881 = !DILocation(line: 123, column: 14, scope: !1870)
!1882 = !DILocation(line: 125, column: 8, scope: !1883)
!1883 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 125, column: 8)
!1884 = !DILocation(line: 125, column: 8, scope: !1871)
!1885 = !DILocation(line: 126, column: 14, scope: !1883)
!1886 = !DILocation(line: 126, column: 7, scope: !1883)
!1887 = !DILocation(line: 127, column: 3, scope: !1871)
!1888 = !DILocation(line: 129, column: 6, scope: !1889)
!1889 = distinct !DILexicalBlock(scope: !1685, file: !1, line: 129, column: 6)
!1890 = !DILocation(line: 129, column: 9, scope: !1889)
!1891 = !DILocation(line: 129, column: 6, scope: !1685)
!1892 = !DILocation(line: 130, column: 11, scope: !1893)
!1893 = distinct !DILexicalBlock(scope: !1889, file: !1, line: 129, column: 16)
!1894 = !DILocation(line: 130, column: 5, scope: !1893)
!1895 = !DILocation(line: 131, column: 12, scope: !1893)
!1896 = !DILocation(line: 132, column: 3, scope: !1893)
!1897 = !DILocation(line: 133, column: 11, scope: !1898)
!1898 = distinct !DILexicalBlock(scope: !1889, file: !1, line: 133, column: 11)
!1899 = !DILocation(line: 133, column: 11, scope: !1889)
!1900 = !DILocation(line: 134, column: 14, scope: !1898)
!1901 = !DILocation(line: 134, column: 18, scope: !1898)
!1902 = !DILocation(line: 134, column: 32, scope: !1898)
!1903 = !DILocation(line: 134, column: 12, scope: !1898)
!1904 = !DILocation(line: 134, column: 5, scope: !1898)
!1905 = !DILocation(line: 136, column: 10, scope: !1685)
!1906 = !DILocation(line: 136, column: 3, scope: !1685)
!1907 = !DILocation(line: 137, column: 1, scope: !1685)
!1908 = !DILocalVariable(name: "pp", arg: 1, scope: !1715, file: !1, line: 504, type: !1683)
!1909 = !DILocation(line: 504, column: 40, scope: !1715)
!1910 = !DILocation(line: 506, column: 12, scope: !1715)
!1911 = !DILocation(line: 506, column: 16, scope: !1715)
!1912 = !DILocation(line: 506, column: 25, scope: !1715)
!1913 = !DILocation(line: 506, column: 28, scope: !1914)
!1914 = !DILexicalBlockFile(scope: !1715, file: !1, discriminator: 1)
!1915 = !DILocation(line: 506, column: 32, scope: !1914)
!1916 = !DILocation(line: 506, column: 38, scope: !1914)
!1917 = !DILocation(line: 506, column: 41, scope: !1918)
!1918 = !DILexicalBlockFile(scope: !1715, file: !1, discriminator: 2)
!1919 = !DILocation(line: 506, column: 45, scope: !1918)
!1920 = !DILocation(line: 506, column: 58, scope: !1918)
!1921 = !DILocation(line: 506, column: 62, scope: !1918)
!1922 = !DILocation(line: 506, column: 56, scope: !1918)
!1923 = !DILocation(line: 506, column: 10, scope: !1924)
!1924 = !DILexicalBlockFile(scope: !1715, file: !1, discriminator: 3)
!1925 = !DILocation(line: 506, column: 3, scope: !1924)
!1926 = !DILocalVariable(name: "pp", arg: 1, scope: !1688, file: !1, line: 140, type: !1683)
!1927 = !DILocation(line: 140, column: 36, scope: !1688)
!1928 = !DILocalVariable(name: "conn", scope: !1688, file: !1, line: 142, type: !550)
!1929 = !DILocation(line: 142, column: 23, scope: !1688)
!1930 = !DILocation(line: 142, column: 30, scope: !1688)
!1931 = !DILocation(line: 142, column: 34, scope: !1688)
!1932 = !DILocation(line: 143, column: 3, scope: !1688)
!1933 = !DILocation(line: 143, column: 7, scope: !1688)
!1934 = !DILocation(line: 143, column: 18, scope: !1688)
!1935 = !DILocation(line: 144, column: 24, scope: !1688)
!1936 = !DILocation(line: 144, column: 30, scope: !1688)
!1937 = !DILocation(line: 144, column: 36, scope: !1688)
!1938 = !DILocation(line: 144, column: 42, scope: !1688)
!1939 = !DILocation(line: 144, column: 3, scope: !1688)
!1940 = !DILocation(line: 144, column: 7, scope: !1688)
!1941 = !DILocation(line: 144, column: 22, scope: !1688)
!1942 = !DILocation(line: 145, column: 3, scope: !1688)
!1943 = !DILocation(line: 145, column: 7, scope: !1688)
!1944 = !DILocation(line: 145, column: 20, scope: !1688)
!1945 = !DILocation(line: 146, column: 3, scope: !1688)
!1946 = !DILocation(line: 146, column: 7, scope: !1688)
!1947 = !DILocation(line: 146, column: 18, scope: !1688)
!1948 = !DILocation(line: 146, column: 18, scope: !1949)
!1949 = !DILexicalBlockFile(scope: !1688, file: !1, discriminator: 1)
!1950 = !DILocation(line: 147, column: 1, scope: !1688)
!1951 = !DILocalVariable(name: "pp", arg: 1, scope: !1691, file: !1, line: 161, type: !1683)
!1952 = !DILocation(line: 161, column: 42, scope: !1691)
!1953 = !DILocalVariable(name: "fmt", arg: 2, scope: !1691, file: !1, line: 162, type: !928)
!1954 = !DILocation(line: 162, column: 37, scope: !1691)
!1955 = !DILocalVariable(name: "args", arg: 3, scope: !1691, file: !1, line: 163, type: !1694)
!1956 = !DILocation(line: 163, column: 33, scope: !1691)
!1957 = !DILocalVariable(name: "bytes_written", scope: !1691, file: !1, line: 165, type: !256)
!1958 = !DILocation(line: 165, column: 11, scope: !1691)
!1959 = !DILocalVariable(name: "write_len", scope: !1691, file: !1, line: 166, type: !158)
!1960 = !DILocation(line: 166, column: 10, scope: !1691)
!1961 = !DILocalVariable(name: "fmt_crlf", scope: !1691, file: !1, line: 167, type: !215)
!1962 = !DILocation(line: 167, column: 9, scope: !1691)
!1963 = !DILocalVariable(name: "s", scope: !1691, file: !1, line: 168, type: !215)
!1964 = !DILocation(line: 168, column: 9, scope: !1691)
!1965 = !DILocalVariable(name: "result", scope: !1691, file: !1, line: 169, type: !554)
!1966 = !DILocation(line: 169, column: 12, scope: !1691)
!1967 = !DILocalVariable(name: "conn", scope: !1691, file: !1, line: 170, type: !550)
!1968 = !DILocation(line: 170, column: 23, scope: !1691)
!1969 = !DILocation(line: 170, column: 30, scope: !1691)
!1970 = !DILocation(line: 170, column: 34, scope: !1691)
!1971 = !DILocalVariable(name: "data", scope: !1691, file: !1, line: 171, type: !544)
!1972 = !DILocation(line: 171, column: 21, scope: !1691)
!1973 = !DILocation(line: 171, column: 28, scope: !1691)
!1974 = !DILocation(line: 171, column: 34, scope: !1691)
!1975 = !DILocation(line: 177, column: 3, scope: !1691)
!1976 = !DILocation(line: 177, column: 3, scope: !1977)
!1977 = !DILexicalBlockFile(scope: !1978, file: !1, discriminator: 1)
!1978 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 177, column: 3)
!1979 = !DILocation(line: 178, column: 3, scope: !1691)
!1980 = !DILocation(line: 178, column: 3, scope: !1981)
!1981 = !DILexicalBlockFile(scope: !1982, file: !1, discriminator: 1)
!1982 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 178, column: 3)
!1983 = !DILocation(line: 179, column: 3, scope: !1691)
!1984 = !DILocation(line: 179, column: 3, scope: !1985)
!1985 = !DILexicalBlockFile(scope: !1986, file: !1, discriminator: 1)
!1986 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 179, column: 3)
!1987 = !DILocation(line: 181, column: 32, scope: !1691)
!1988 = !DILocation(line: 181, column: 14, scope: !1691)
!1989 = !DILocation(line: 181, column: 12, scope: !1691)
!1990 = !DILocation(line: 182, column: 7, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 182, column: 6)
!1992 = !DILocation(line: 182, column: 6, scope: !1691)
!1993 = !DILocation(line: 183, column: 5, scope: !1991)
!1994 = !DILocation(line: 185, column: 16, scope: !1691)
!1995 = !DILocation(line: 185, column: 26, scope: !1691)
!1996 = !DILocation(line: 185, column: 7, scope: !1691)
!1997 = !DILocation(line: 185, column: 5, scope: !1691)
!1998 = !DILocation(line: 186, column: 3, scope: !1691)
!1999 = !DILocation(line: 187, column: 7, scope: !2000)
!2000 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 187, column: 6)
!2001 = !DILocation(line: 187, column: 6, scope: !1691)
!2002 = !DILocation(line: 188, column: 5, scope: !2000)
!2003 = !DILocation(line: 190, column: 17, scope: !1691)
!2004 = !DILocation(line: 191, column: 22, scope: !1691)
!2005 = !DILocation(line: 191, column: 15, scope: !1691)
!2006 = !DILocation(line: 191, column: 13, scope: !1691)
!2007 = !DILocation(line: 193, column: 16, scope: !1691)
!2008 = !DILocation(line: 193, column: 3, scope: !1691)
!2009 = !DILocation(line: 195, column: 12, scope: !1691)
!2010 = !DILocation(line: 195, column: 10, scope: !1691)
!2011 = !DILocation(line: 197, column: 6, scope: !2012)
!2012 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 197, column: 6)
!2013 = !DILocation(line: 197, column: 6, scope: !1691)
!2014 = !DILocation(line: 198, column: 5, scope: !2015)
!2015 = distinct !DILexicalBlock(scope: !2012, file: !1, line: 197, column: 14)
!2016 = !DILocation(line: 199, column: 12, scope: !2015)
!2017 = !DILocation(line: 199, column: 5, scope: !2015)
!2018 = !DILocation(line: 205, column: 23, scope: !1691)
!2019 = !DILocation(line: 205, column: 29, scope: !1691)
!2020 = !DILocation(line: 205, column: 35, scope: !1691)
!2021 = !DILocation(line: 205, column: 54, scope: !1691)
!2022 = !DILocation(line: 205, column: 57, scope: !1691)
!2023 = !DILocation(line: 205, column: 12, scope: !1691)
!2024 = !DILocation(line: 205, column: 10, scope: !1691)
!2025 = !DILocation(line: 212, column: 6, scope: !2026)
!2026 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 212, column: 6)
!2027 = !DILocation(line: 212, column: 6, scope: !1691)
!2028 = !DILocation(line: 213, column: 5, scope: !2029)
!2029 = distinct !DILexicalBlock(scope: !2026, file: !1, line: 212, column: 14)
!2030 = !DILocation(line: 214, column: 12, scope: !2029)
!2031 = !DILocation(line: 214, column: 5, scope: !2029)
!2032 = !DILocation(line: 217, column: 6, scope: !2033)
!2033 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 217, column: 6)
!2034 = !DILocation(line: 217, column: 12, scope: !2033)
!2035 = !DILocation(line: 217, column: 18, scope: !2033)
!2036 = !DILocation(line: 217, column: 22, scope: !2033)
!2037 = !DILocation(line: 217, column: 6, scope: !1691)
!2038 = !DILocation(line: 218, column: 16, scope: !2033)
!2039 = !DILocation(line: 218, column: 22, scope: !2033)
!2040 = !DILocation(line: 219, column: 16, scope: !2033)
!2041 = !DILocation(line: 219, column: 27, scope: !2033)
!2042 = !DILocation(line: 219, column: 42, scope: !2033)
!2043 = !DILocation(line: 218, column: 5, scope: !2033)
!2044 = !DILocation(line: 221, column: 6, scope: !2045)
!2045 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 221, column: 6)
!2046 = !DILocation(line: 221, column: 32, scope: !2045)
!2047 = !DILocation(line: 221, column: 20, scope: !2045)
!2048 = !DILocation(line: 221, column: 6, scope: !1691)
!2049 = !DILocation(line: 223, column: 20, scope: !2050)
!2050 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 221, column: 43)
!2051 = !DILocation(line: 223, column: 5, scope: !2050)
!2052 = !DILocation(line: 223, column: 9, scope: !2050)
!2053 = !DILocation(line: 223, column: 18, scope: !2050)
!2054 = !DILocation(line: 224, column: 20, scope: !2050)
!2055 = !DILocation(line: 224, column: 5, scope: !2050)
!2056 = !DILocation(line: 224, column: 9, scope: !2050)
!2057 = !DILocation(line: 224, column: 18, scope: !2050)
!2058 = !DILocation(line: 225, column: 20, scope: !2050)
!2059 = !DILocation(line: 225, column: 32, scope: !2050)
!2060 = !DILocation(line: 225, column: 30, scope: !2050)
!2061 = !DILocation(line: 225, column: 5, scope: !2050)
!2062 = !DILocation(line: 225, column: 9, scope: !2050)
!2063 = !DILocation(line: 225, column: 18, scope: !2050)
!2064 = !DILocation(line: 226, column: 3, scope: !2050)
!2065 = !DILocation(line: 228, column: 5, scope: !2066)
!2066 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 227, column: 8)
!2067 = !DILocation(line: 229, column: 5, scope: !2066)
!2068 = !DILocation(line: 229, column: 9, scope: !2066)
!2069 = !DILocation(line: 229, column: 18, scope: !2066)
!2070 = !DILocation(line: 230, column: 20, scope: !2066)
!2071 = !DILocation(line: 230, column: 24, scope: !2066)
!2072 = !DILocation(line: 230, column: 33, scope: !2066)
!2073 = !DILocation(line: 230, column: 5, scope: !2066)
!2074 = !DILocation(line: 230, column: 9, scope: !2066)
!2075 = !DILocation(line: 230, column: 18, scope: !2066)
!2076 = !DILocation(line: 231, column: 5, scope: !2066)
!2077 = !DILocation(line: 231, column: 9, scope: !2066)
!2078 = !DILocation(line: 231, column: 20, scope: !2066)
!2079 = !DILocation(line: 231, column: 20, scope: !2080)
!2080 = !DILexicalBlockFile(scope: !2066, file: !1, discriminator: 1)
!2081 = !DILocation(line: 234, column: 3, scope: !1691)
!2082 = !DILocation(line: 235, column: 1, scope: !1691)
!2083 = !DILocalVariable(name: "pp", arg: 1, scope: !1701, file: !1, line: 248, type: !1683)
!2084 = !DILocation(line: 248, column: 41, scope: !1701)
!2085 = !DILocalVariable(name: "fmt", arg: 2, scope: !1701, file: !1, line: 249, type: !928)
!2086 = !DILocation(line: 249, column: 36, scope: !1701)
!2087 = !DILocalVariable(name: "result", scope: !1701, file: !1, line: 251, type: !554)
!2088 = !DILocation(line: 251, column: 12, scope: !1701)
!2089 = !DILocalVariable(name: "ap", scope: !1701, file: !1, line: 252, type: !2090)
!2090 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !654, line: 79, baseType: !2091)
!2091 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !2092, line: 50, baseType: !2093)
!2092 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2093 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 252, baseType: !2094)
!2094 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1695, size: 192, align: 64, elements: !689)
!2095 = !DILocation(line: 252, column: 11, scope: !1701)
!2096 = !DILocation(line: 253, column: 3, scope: !1701)
!2097 = !DILocation(line: 255, column: 27, scope: !1701)
!2098 = !DILocation(line: 255, column: 31, scope: !1701)
!2099 = !DILocation(line: 255, column: 36, scope: !1701)
!2100 = !DILocation(line: 255, column: 12, scope: !1701)
!2101 = !DILocation(line: 255, column: 10, scope: !1701)
!2102 = !DILocation(line: 257, column: 3, scope: !1701)
!2103 = !DILocation(line: 259, column: 10, scope: !1701)
!2104 = !DILocation(line: 259, column: 3, scope: !1701)
!2105 = !DILocalVariable(name: "sockfd", arg: 1, scope: !1704, file: !1, line: 267, type: !248)
!2106 = !DILocation(line: 267, column: 41, scope: !1704)
!2107 = !DILocalVariable(name: "pp", arg: 2, scope: !1704, file: !1, line: 268, type: !1683)
!2108 = !DILocation(line: 268, column: 44, scope: !1704)
!2109 = !DILocalVariable(name: "code", arg: 3, scope: !1704, file: !1, line: 269, type: !1434)
!2110 = !DILocation(line: 269, column: 32, scope: !1704)
!2111 = !DILocalVariable(name: "size", arg: 4, scope: !1704, file: !1, line: 270, type: !1707)
!2112 = !DILocation(line: 270, column: 35, scope: !1704)
!2113 = !DILocalVariable(name: "perline", scope: !1704, file: !1, line: 272, type: !256)
!2114 = !DILocation(line: 272, column: 11, scope: !1704)
!2115 = !DILocalVariable(name: "keepon", scope: !1704, file: !1, line: 273, type: !211)
!2116 = !DILocation(line: 273, column: 8, scope: !1704)
!2117 = !DILocalVariable(name: "gotbytes", scope: !1704, file: !1, line: 274, type: !256)
!2118 = !DILocation(line: 274, column: 11, scope: !1704)
!2119 = !DILocalVariable(name: "ptr", scope: !1704, file: !1, line: 275, type: !215)
!2120 = !DILocation(line: 275, column: 9, scope: !1704)
!2121 = !DILocalVariable(name: "conn", scope: !1704, file: !1, line: 276, type: !550)
!2122 = !DILocation(line: 276, column: 23, scope: !1704)
!2123 = !DILocation(line: 276, column: 30, scope: !1704)
!2124 = !DILocation(line: 276, column: 34, scope: !1704)
!2125 = !DILocalVariable(name: "data", scope: !1704, file: !1, line: 277, type: !544)
!2126 = !DILocation(line: 277, column: 21, scope: !1704)
!2127 = !DILocation(line: 277, column: 28, scope: !1704)
!2128 = !DILocation(line: 277, column: 34, scope: !1704)
!2129 = !DILocalVariable(name: "buf", scope: !1704, file: !1, line: 278, type: !2130)
!2130 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !215)
!2131 = !DILocation(line: 278, column: 16, scope: !1704)
!2132 = !DILocation(line: 278, column: 22, scope: !1704)
!2133 = !DILocation(line: 278, column: 28, scope: !1704)
!2134 = !DILocation(line: 278, column: 34, scope: !1704)
!2135 = !DILocalVariable(name: "result", scope: !1704, file: !1, line: 279, type: !554)
!2136 = !DILocation(line: 279, column: 12, scope: !1704)
!2137 = !DILocation(line: 281, column: 4, scope: !1704)
!2138 = !DILocation(line: 281, column: 9, scope: !1704)
!2139 = !DILocation(line: 282, column: 4, scope: !1704)
!2140 = !DILocation(line: 282, column: 9, scope: !1704)
!2141 = !DILocation(line: 284, column: 7, scope: !1704)
!2142 = !DILocation(line: 284, column: 13, scope: !1704)
!2143 = !DILocation(line: 284, column: 17, scope: !1704)
!2144 = !DILocation(line: 284, column: 11, scope: !1704)
!2145 = !DILocation(line: 284, column: 6, scope: !1704)
!2146 = !DILocation(line: 287, column: 23, scope: !1704)
!2147 = !DILocation(line: 287, column: 27, scope: !1704)
!2148 = !DILocation(line: 287, column: 31, scope: !1704)
!2149 = !DILocation(line: 287, column: 26, scope: !1704)
!2150 = !DILocation(line: 287, column: 11, scope: !1704)
!2151 = !DILocation(line: 289, column: 3, scope: !1704)
!2152 = !DILocation(line: 289, column: 10, scope: !2153)
!2153 = !DILexicalBlockFile(scope: !1704, file: !1, discriminator: 1)
!2154 = !DILocation(line: 289, column: 14, scope: !2153)
!2155 = !DILocation(line: 289, column: 24, scope: !2153)
!2156 = !DILocation(line: 289, column: 34, scope: !2153)
!2157 = !DILocation(line: 289, column: 38, scope: !2158)
!2158 = !DILexicalBlockFile(scope: !1704, file: !1, discriminator: 2)
!2159 = !DILocation(line: 289, column: 45, scope: !2158)
!2160 = !DILocation(line: 289, column: 49, scope: !2161)
!2161 = !DILexicalBlockFile(scope: !1704, file: !1, discriminator: 3)
!2162 = !DILocation(line: 289, column: 48, scope: !2161)
!2163 = !DILocation(line: 289, column: 3, scope: !2164)
!2164 = !DILexicalBlockFile(scope: !1704, file: !1, discriminator: 4)
!2165 = !DILocation(line: 291, column: 8, scope: !2166)
!2166 = distinct !DILexicalBlock(scope: !2167, file: !1, line: 291, column: 8)
!2167 = distinct !DILexicalBlock(scope: !1704, file: !1, line: 289, column: 58)
!2168 = !DILocation(line: 291, column: 12, scope: !2166)
!2169 = !DILocation(line: 291, column: 8, scope: !2167)
!2170 = !DILocation(line: 299, column: 7, scope: !2171)
!2171 = distinct !DILexicalBlock(scope: !2166, file: !1, line: 291, column: 19)
!2172 = !DILocation(line: 299, column: 7, scope: !2173)
!2173 = !DILexicalBlockFile(scope: !2174, file: !1, discriminator: 1)
!2174 = distinct !DILexicalBlock(scope: !2171, file: !1, line: 299, column: 7)
!2175 = !DILocation(line: 300, column: 14, scope: !2171)
!2176 = !DILocation(line: 300, column: 19, scope: !2171)
!2177 = !DILocation(line: 300, column: 23, scope: !2171)
!2178 = !DILocation(line: 300, column: 30, scope: !2171)
!2179 = !DILocation(line: 300, column: 34, scope: !2171)
!2180 = !DILocation(line: 300, column: 7, scope: !2171)
!2181 = !DILocation(line: 301, column: 27, scope: !2171)
!2182 = !DILocation(line: 301, column: 31, scope: !2171)
!2183 = !DILocation(line: 301, column: 16, scope: !2171)
!2184 = !DILocation(line: 302, column: 7, scope: !2171)
!2185 = !DILocation(line: 303, column: 7, scope: !2171)
!2186 = !DILocation(line: 303, column: 11, scope: !2171)
!2187 = !DILocation(line: 303, column: 17, scope: !2171)
!2188 = !DILocation(line: 304, column: 7, scope: !2171)
!2189 = !DILocation(line: 304, column: 11, scope: !2171)
!2190 = !DILocation(line: 304, column: 22, scope: !2171)
!2191 = !DILocation(line: 305, column: 5, scope: !2171)
!2192 = !DILocation(line: 311, column: 7, scope: !2193)
!2193 = distinct !DILexicalBlock(scope: !2166, file: !1, line: 306, column: 10)
!2194 = !DILocation(line: 311, column: 7, scope: !2195)
!2195 = !DILexicalBlockFile(scope: !2196, file: !1, discriminator: 1)
!2196 = distinct !DILexicalBlock(scope: !2193, file: !1, line: 311, column: 7)
!2197 = !DILocation(line: 312, column: 26, scope: !2193)
!2198 = !DILocation(line: 312, column: 32, scope: !2193)
!2199 = !DILocation(line: 312, column: 40, scope: !2193)
!2200 = !DILocation(line: 312, column: 53, scope: !2193)
!2201 = !DILocation(line: 312, column: 57, scope: !2193)
!2202 = !DILocation(line: 312, column: 52, scope: !2193)
!2203 = !DILocation(line: 312, column: 16, scope: !2193)
!2204 = !DILocation(line: 312, column: 14, scope: !2193)
!2205 = !DILocation(line: 318, column: 10, scope: !2206)
!2206 = distinct !DILexicalBlock(scope: !2193, file: !1, line: 318, column: 10)
!2207 = !DILocation(line: 318, column: 17, scope: !2206)
!2208 = !DILocation(line: 318, column: 10, scope: !2193)
!2209 = !DILocation(line: 319, column: 9, scope: !2206)
!2210 = !DILocation(line: 321, column: 11, scope: !2211)
!2211 = distinct !DILexicalBlock(scope: !2193, file: !1, line: 321, column: 10)
!2212 = !DILocation(line: 321, column: 18, scope: !2211)
!2213 = !DILocation(line: 321, column: 22, scope: !2214)
!2214 = !DILexicalBlockFile(scope: !2211, file: !1, discriminator: 1)
!2215 = !DILocation(line: 321, column: 31, scope: !2214)
!2216 = !DILocation(line: 321, column: 10, scope: !2214)
!2217 = !DILocation(line: 323, column: 18, scope: !2211)
!2218 = !DILocation(line: 323, column: 16, scope: !2211)
!2219 = !DILocation(line: 323, column: 9, scope: !2211)
!2220 = !DILocation(line: 326, column: 10, scope: !2221)
!2221 = distinct !DILexicalBlock(scope: !2193, file: !1, line: 326, column: 10)
!2222 = !DILocation(line: 326, column: 10, scope: !2193)
!2223 = !DILocation(line: 328, column: 16, scope: !2221)
!2224 = !DILocation(line: 328, column: 9, scope: !2221)
!2225 = !DILocation(line: 331, column: 9, scope: !2226)
!2226 = distinct !DILexicalBlock(scope: !2167, file: !1, line: 331, column: 8)
!2227 = !DILocation(line: 331, column: 8, scope: !2167)
!2228 = !DILocation(line: 331, column: 8, scope: !2229)
!2229 = !DILexicalBlockFile(scope: !2167, file: !1, discriminator: 1)
!2230 = !DILocation(line: 333, column: 13, scope: !2231)
!2231 = distinct !DILexicalBlock(scope: !2226, file: !1, line: 333, column: 13)
!2232 = !DILocation(line: 333, column: 22, scope: !2231)
!2233 = !DILocation(line: 333, column: 13, scope: !2226)
!2234 = !DILocation(line: 334, column: 14, scope: !2235)
!2235 = distinct !DILexicalBlock(scope: !2231, file: !1, line: 333, column: 28)
!2236 = !DILocation(line: 335, column: 14, scope: !2235)
!2237 = !DILocation(line: 336, column: 13, scope: !2235)
!2238 = !DILocation(line: 336, column: 7, scope: !2235)
!2239 = !DILocation(line: 337, column: 5, scope: !2235)
!2240 = !DILocalVariable(name: "i", scope: !2241, file: !1, line: 342, type: !256)
!2241 = distinct !DILexicalBlock(scope: !2231, file: !1, line: 338, column: 10)
!2242 = !DILocation(line: 342, column: 15, scope: !2241)
!2243 = !DILocalVariable(name: "clipamount", scope: !2241, file: !1, line: 343, type: !256)
!2244 = !DILocation(line: 343, column: 15, scope: !2241)
!2245 = !DILocalVariable(name: "restart", scope: !2241, file: !1, line: 344, type: !211)
!2246 = !DILocation(line: 344, column: 12, scope: !2241)
!2247 = !DILocation(line: 346, column: 42, scope: !2241)
!2248 = !DILocation(line: 346, column: 7, scope: !2241)
!2249 = !DILocation(line: 346, column: 13, scope: !2241)
!2250 = !DILocation(line: 346, column: 17, scope: !2241)
!2251 = !DILocation(line: 346, column: 33, scope: !2241)
!2252 = !DILocation(line: 348, column: 25, scope: !2241)
!2253 = !DILocation(line: 348, column: 7, scope: !2241)
!2254 = !DILocation(line: 348, column: 11, scope: !2241)
!2255 = !DILocation(line: 348, column: 22, scope: !2241)
!2256 = !DILocation(line: 349, column: 13, scope: !2257)
!2257 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 349, column: 7)
!2258 = !DILocation(line: 349, column: 11, scope: !2257)
!2259 = !DILocation(line: 349, column: 18, scope: !2260)
!2260 = !DILexicalBlockFile(scope: !2261, file: !1, discriminator: 1)
!2261 = distinct !DILexicalBlock(scope: !2257, file: !1, line: 349, column: 7)
!2262 = !DILocation(line: 349, column: 22, scope: !2260)
!2263 = !DILocation(line: 349, column: 20, scope: !2260)
!2264 = !DILocation(line: 349, column: 7, scope: !2260)
!2265 = !DILocation(line: 350, column: 16, scope: !2266)
!2266 = distinct !DILexicalBlock(scope: !2261, file: !1, line: 349, column: 44)
!2267 = !DILocation(line: 351, column: 13, scope: !2268)
!2268 = distinct !DILexicalBlock(scope: !2266, file: !1, line: 351, column: 12)
!2269 = !DILocation(line: 351, column: 12, scope: !2268)
!2270 = !DILocation(line: 351, column: 16, scope: !2268)
!2271 = !DILocation(line: 351, column: 12, scope: !2266)
!2272 = !DILocation(line: 359, column: 16, scope: !2273)
!2273 = distinct !DILexicalBlock(scope: !2274, file: !1, line: 359, column: 16)
!2274 = distinct !DILexicalBlock(scope: !2268, file: !1, line: 351, column: 24)
!2275 = !DILocation(line: 359, column: 22, scope: !2273)
!2276 = !DILocation(line: 359, column: 26, scope: !2273)
!2277 = !DILocation(line: 359, column: 16, scope: !2274)
!2278 = !DILocation(line: 360, column: 26, scope: !2273)
!2279 = !DILocation(line: 361, column: 26, scope: !2273)
!2280 = !DILocation(line: 361, column: 30, scope: !2273)
!2281 = !DILocation(line: 361, column: 54, scope: !2273)
!2282 = !DILocation(line: 361, column: 63, scope: !2273)
!2283 = !DILocation(line: 360, column: 15, scope: !2273)
!2284 = !DILocation(line: 368, column: 38, scope: !2274)
!2285 = !DILocation(line: 369, column: 38, scope: !2274)
!2286 = !DILocation(line: 369, column: 42, scope: !2274)
!2287 = !DILocation(line: 369, column: 58, scope: !2274)
!2288 = !DILocation(line: 368, column: 20, scope: !2274)
!2289 = !DILocation(line: 368, column: 18, scope: !2274)
!2290 = !DILocation(line: 370, column: 14, scope: !2291)
!2291 = distinct !DILexicalBlock(scope: !2274, file: !1, line: 370, column: 14)
!2292 = !DILocation(line: 370, column: 14, scope: !2274)
!2293 = !DILocation(line: 371, column: 20, scope: !2291)
!2294 = !DILocation(line: 371, column: 13, scope: !2291)
!2295 = !DILocation(line: 373, column: 14, scope: !2296)
!2296 = distinct !DILexicalBlock(scope: !2274, file: !1, line: 373, column: 14)
!2297 = !DILocation(line: 373, column: 18, scope: !2296)
!2298 = !DILocation(line: 373, column: 28, scope: !2296)
!2299 = !DILocation(line: 373, column: 34, scope: !2296)
!2300 = !DILocation(line: 373, column: 38, scope: !2296)
!2301 = !DILocation(line: 373, column: 54, scope: !2296)
!2302 = !DILocation(line: 373, column: 63, scope: !2296)
!2303 = !DILocation(line: 373, column: 14, scope: !2274)
!2304 = !DILocalVariable(name: "n", scope: !2305, file: !1, line: 376, type: !158)
!2305 = distinct !DILexicalBlock(scope: !2296, file: !1, line: 373, column: 70)
!2306 = !DILocation(line: 376, column: 20, scope: !2305)
!2307 = !DILocation(line: 376, column: 24, scope: !2305)
!2308 = !DILocation(line: 376, column: 30, scope: !2305)
!2309 = !DILocation(line: 376, column: 34, scope: !2305)
!2310 = !DILocation(line: 376, column: 28, scope: !2305)
!2311 = !DILocation(line: 377, column: 21, scope: !2305)
!2312 = !DILocation(line: 377, column: 26, scope: !2305)
!2313 = !DILocation(line: 377, column: 30, scope: !2305)
!2314 = !DILocation(line: 377, column: 46, scope: !2305)
!2315 = !DILocation(line: 377, column: 13, scope: !2305)
!2316 = !DILocation(line: 378, column: 17, scope: !2305)
!2317 = !DILocation(line: 378, column: 13, scope: !2305)
!2318 = !DILocation(line: 378, column: 19, scope: !2305)
!2319 = !DILocation(line: 379, column: 19, scope: !2305)
!2320 = !DILocation(line: 380, column: 34, scope: !2305)
!2321 = !DILocation(line: 380, column: 37, scope: !2305)
!2322 = !DILocation(line: 380, column: 13, scope: !2305)
!2323 = !DILocation(line: 380, column: 17, scope: !2305)
!2324 = !DILocation(line: 380, column: 32, scope: !2305)
!2325 = !DILocation(line: 381, column: 14, scope: !2305)
!2326 = !DILocation(line: 383, column: 21, scope: !2305)
!2327 = !DILocation(line: 383, column: 25, scope: !2305)
!2328 = !DILocation(line: 383, column: 14, scope: !2305)
!2329 = !DILocation(line: 383, column: 19, scope: !2305)
!2330 = !DILocation(line: 384, column: 13, scope: !2305)
!2331 = !DILocation(line: 384, column: 17, scope: !2305)
!2332 = !DILocation(line: 384, column: 28, scope: !2305)
!2333 = !DILocation(line: 385, column: 13, scope: !2305)
!2334 = !DILocation(line: 387, column: 18, scope: !2274)
!2335 = !DILocation(line: 388, column: 32, scope: !2274)
!2336 = !DILocation(line: 388, column: 35, scope: !2274)
!2337 = !DILocation(line: 388, column: 11, scope: !2274)
!2338 = !DILocation(line: 388, column: 15, scope: !2274)
!2339 = !DILocation(line: 388, column: 30, scope: !2274)
!2340 = !DILocation(line: 389, column: 9, scope: !2274)
!2341 = !DILocation(line: 390, column: 7, scope: !2266)
!2342 = !DILocation(line: 349, column: 35, scope: !2343)
!2343 = !DILexicalBlockFile(scope: !2261, file: !1, discriminator: 2)
!2344 = !DILocation(line: 349, column: 40, scope: !2343)
!2345 = !DILocation(line: 349, column: 7, scope: !2343)
!2346 = !DILocation(line: 392, column: 11, scope: !2347)
!2347 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 392, column: 10)
!2348 = !DILocation(line: 392, column: 18, scope: !2347)
!2349 = !DILocation(line: 392, column: 22, scope: !2350)
!2350 = !DILexicalBlockFile(scope: !2347, file: !1, discriminator: 1)
!2351 = !DILocation(line: 392, column: 27, scope: !2350)
!2352 = !DILocation(line: 392, column: 24, scope: !2350)
!2353 = !DILocation(line: 392, column: 10, scope: !2350)
!2354 = !DILocation(line: 397, column: 22, scope: !2355)
!2355 = distinct !DILexicalBlock(scope: !2347, file: !1, line: 392, column: 38)
!2356 = !DILocation(line: 397, column: 33, scope: !2355)
!2357 = !DILocation(line: 397, column: 31, scope: !2355)
!2358 = !DILocation(line: 397, column: 20, scope: !2355)
!2359 = !DILocation(line: 398, column: 17, scope: !2355)
!2360 = !DILocation(line: 399, column: 9, scope: !2355)
!2361 = !DILocation(line: 399, column: 9, scope: !2362)
!2362 = !DILexicalBlockFile(scope: !2363, file: !1, discriminator: 1)
!2363 = distinct !DILexicalBlock(scope: !2355, file: !1, line: 399, column: 9)
!2364 = !DILocation(line: 402, column: 7, scope: !2355)
!2365 = !DILocation(line: 403, column: 15, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !2347, file: !1, line: 403, column: 15)
!2367 = !DILocation(line: 403, column: 15, scope: !2347)
!2368 = !DILocation(line: 405, column: 13, scope: !2369)
!2369 = distinct !DILexicalBlock(scope: !2370, file: !1, line: 405, column: 12)
!2370 = distinct !DILexicalBlock(scope: !2366, file: !1, line: 403, column: 23)
!2371 = !DILocation(line: 405, column: 24, scope: !2369)
!2372 = !DILocation(line: 405, column: 21, scope: !2369)
!2373 = !DILocation(line: 405, column: 34, scope: !2369)
!2374 = !DILocation(line: 405, column: 38, scope: !2375)
!2375 = !DILexicalBlockFile(scope: !2369, file: !1, discriminator: 1)
!2376 = !DILocation(line: 405, column: 47, scope: !2375)
!2377 = !DILocation(line: 405, column: 12, scope: !2375)
!2378 = !DILocation(line: 409, column: 17, scope: !2379)
!2379 = distinct !DILexicalBlock(scope: !2369, file: !1, line: 405, column: 61)
!2380 = !DILocation(line: 410, column: 43, scope: !2379)
!2381 = !DILocation(line: 409, column: 11, scope: !2379)
!2382 = !DILocation(line: 411, column: 19, scope: !2379)
!2383 = !DILocation(line: 415, column: 22, scope: !2379)
!2384 = !DILocation(line: 416, column: 9, scope: !2379)
!2385 = !DILocation(line: 417, column: 17, scope: !2386)
!2386 = distinct !DILexicalBlock(scope: !2369, file: !1, line: 417, column: 17)
!2387 = !DILocation(line: 417, column: 21, scope: !2386)
!2388 = !DILocation(line: 417, column: 32, scope: !2386)
!2389 = !DILocation(line: 417, column: 17, scope: !2369)
!2390 = !DILocation(line: 421, column: 24, scope: !2391)
!2391 = distinct !DILexicalBlock(scope: !2386, file: !1, line: 417, column: 45)
!2392 = !DILocation(line: 421, column: 22, scope: !2391)
!2393 = !DILocation(line: 422, column: 19, scope: !2391)
!2394 = !DILocation(line: 423, column: 9, scope: !2391)
!2395 = !DILocation(line: 424, column: 7, scope: !2370)
!2396 = !DILocation(line: 425, column: 15, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !2366, file: !1, line: 425, column: 15)
!2398 = !DILocation(line: 425, column: 20, scope: !2397)
!2399 = !DILocation(line: 425, column: 17, scope: !2397)
!2400 = !DILocation(line: 425, column: 15, scope: !2366)
!2401 = !DILocation(line: 426, column: 17, scope: !2397)
!2402 = !DILocation(line: 426, column: 9, scope: !2397)
!2403 = !DILocation(line: 428, column: 10, scope: !2404)
!2404 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 428, column: 10)
!2405 = !DILocation(line: 428, column: 10, scope: !2241)
!2406 = !DILocation(line: 429, column: 26, scope: !2407)
!2407 = distinct !DILexicalBlock(scope: !2404, file: !1, line: 428, column: 22)
!2408 = !DILocation(line: 429, column: 9, scope: !2407)
!2409 = !DILocation(line: 429, column: 13, scope: !2407)
!2410 = !DILocation(line: 429, column: 24, scope: !2407)
!2411 = !DILocation(line: 430, column: 21, scope: !2407)
!2412 = !DILocation(line: 430, column: 9, scope: !2407)
!2413 = !DILocation(line: 430, column: 13, scope: !2407)
!2414 = !DILocation(line: 430, column: 19, scope: !2407)
!2415 = !DILocation(line: 431, column: 12, scope: !2416)
!2416 = distinct !DILexicalBlock(scope: !2407, file: !1, line: 431, column: 12)
!2417 = !DILocation(line: 431, column: 16, scope: !2416)
!2418 = !DILocation(line: 431, column: 12, scope: !2407)
!2419 = !DILocation(line: 432, column: 18, scope: !2416)
!2420 = !DILocation(line: 432, column: 22, scope: !2416)
!2421 = !DILocation(line: 432, column: 29, scope: !2416)
!2422 = !DILocation(line: 432, column: 33, scope: !2416)
!2423 = !DILocation(line: 432, column: 49, scope: !2416)
!2424 = !DILocation(line: 432, column: 53, scope: !2416)
!2425 = !DILocation(line: 432, column: 11, scope: !2416)
!2426 = !DILocation(line: 434, column: 11, scope: !2416)
!2427 = !DILocation(line: 435, column: 7, scope: !2407)
!2428 = !DILocation(line: 436, column: 10, scope: !2429)
!2429 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 436, column: 10)
!2430 = !DILocation(line: 436, column: 10, scope: !2241)
!2431 = !DILocation(line: 439, column: 9, scope: !2432)
!2432 = distinct !DILexicalBlock(scope: !2429, file: !1, line: 436, column: 19)
!2433 = !DILocation(line: 439, column: 13, scope: !2432)
!2434 = !DILocation(line: 439, column: 24, scope: !2432)
!2435 = !DILocation(line: 440, column: 36, scope: !2432)
!2436 = !DILocation(line: 440, column: 15, scope: !2432)
!2437 = !DILocation(line: 440, column: 19, scope: !2432)
!2438 = !DILocation(line: 440, column: 34, scope: !2432)
!2439 = !DILocation(line: 440, column: 13, scope: !2432)
!2440 = !DILocation(line: 441, column: 17, scope: !2432)
!2441 = !DILocation(line: 442, column: 7, scope: !2432)
!2442 = !DILocation(line: 289, column: 3, scope: !2443)
!2443 = !DILexicalBlockFile(scope: !1704, file: !1, discriminator: 5)
!2444 = !DILocation(line: 448, column: 3, scope: !1704)
!2445 = !DILocation(line: 448, column: 7, scope: !1704)
!2446 = !DILocation(line: 448, column: 20, scope: !1704)
!2447 = !DILocation(line: 450, column: 10, scope: !1704)
!2448 = !DILocation(line: 450, column: 3, scope: !1704)
!2449 = !DILocation(line: 451, column: 1, scope: !1704)
!2450 = !DILocalVariable(name: "pp", arg: 1, scope: !1708, file: !1, line: 453, type: !1683)
!2451 = !DILocation(line: 453, column: 38, scope: !1708)
!2452 = !DILocalVariable(name: "socks", arg: 2, scope: !1708, file: !1, line: 454, type: !1442)
!2453 = !DILocation(line: 454, column: 36, scope: !1708)
!2454 = !DILocalVariable(name: "numsocks", arg: 3, scope: !1708, file: !1, line: 455, type: !177)
!2455 = !DILocation(line: 455, column: 25, scope: !1708)
!2456 = !DILocalVariable(name: "conn", scope: !1708, file: !1, line: 457, type: !550)
!2457 = !DILocation(line: 457, column: 23, scope: !1708)
!2458 = !DILocation(line: 457, column: 30, scope: !1708)
!2459 = !DILocation(line: 457, column: 34, scope: !1708)
!2460 = !DILocation(line: 459, column: 7, scope: !2461)
!2461 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 459, column: 6)
!2462 = !DILocation(line: 459, column: 6, scope: !1708)
!2463 = !DILocation(line: 460, column: 5, scope: !2461)
!2464 = !DILocation(line: 462, column: 14, scope: !1708)
!2465 = !DILocation(line: 462, column: 20, scope: !1708)
!2466 = !DILocation(line: 462, column: 3, scope: !1708)
!2467 = !DILocation(line: 462, column: 12, scope: !1708)
!2468 = !DILocation(line: 464, column: 6, scope: !2469)
!2469 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 464, column: 6)
!2470 = !DILocation(line: 464, column: 10, scope: !2469)
!2471 = !DILocation(line: 464, column: 6, scope: !1708)
!2472 = !DILocation(line: 466, column: 5, scope: !2473)
!2473 = distinct !DILexicalBlock(scope: !2469, file: !1, line: 464, column: 20)
!2474 = !DILocation(line: 470, column: 3, scope: !1708)
!2475 = !DILocation(line: 471, column: 1, scope: !1708)
!2476 = !DILocalVariable(name: "pp", arg: 1, scope: !1711, file: !1, line: 473, type: !1683)
!2477 = !DILocation(line: 473, column: 45, scope: !1711)
!2478 = !DILocalVariable(name: "conn", scope: !1711, file: !1, line: 476, type: !550)
!2479 = !DILocation(line: 476, column: 23, scope: !1711)
!2480 = !DILocation(line: 476, column: 30, scope: !1711)
!2481 = !DILocation(line: 476, column: 34, scope: !1711)
!2482 = !DILocalVariable(name: "written", scope: !1711, file: !1, line: 477, type: !256)
!2483 = !DILocation(line: 477, column: 11, scope: !1711)
!2484 = !DILocalVariable(name: "sock", scope: !1711, file: !1, line: 478, type: !248)
!2485 = !DILocation(line: 478, column: 17, scope: !1711)
!2486 = !DILocation(line: 478, column: 24, scope: !1711)
!2487 = !DILocation(line: 478, column: 30, scope: !1711)
!2488 = !DILocalVariable(name: "result", scope: !1711, file: !1, line: 479, type: !554)
!2489 = !DILocation(line: 479, column: 12, scope: !1711)
!2490 = !DILocation(line: 479, column: 32, scope: !1711)
!2491 = !DILocation(line: 479, column: 38, scope: !1711)
!2492 = !DILocation(line: 479, column: 44, scope: !1711)
!2493 = !DILocation(line: 479, column: 48, scope: !1711)
!2494 = !DILocation(line: 479, column: 59, scope: !1711)
!2495 = !DILocation(line: 479, column: 63, scope: !1711)
!2496 = !DILocation(line: 479, column: 57, scope: !1711)
!2497 = !DILocation(line: 480, column: 32, scope: !1711)
!2498 = !DILocation(line: 480, column: 36, scope: !1711)
!2499 = !DILocation(line: 479, column: 72, scope: !1711)
!2500 = !DILocation(line: 480, column: 46, scope: !1711)
!2501 = !DILocation(line: 480, column: 50, scope: !1711)
!2502 = !DILocation(line: 479, column: 21, scope: !1711)
!2503 = !DILocation(line: 481, column: 6, scope: !2504)
!2504 = distinct !DILexicalBlock(scope: !1711, file: !1, line: 481, column: 6)
!2505 = !DILocation(line: 481, column: 6, scope: !1711)
!2506 = !DILocation(line: 482, column: 12, scope: !2504)
!2507 = !DILocation(line: 482, column: 5, scope: !2504)
!2508 = !DILocation(line: 484, column: 6, scope: !2509)
!2509 = distinct !DILexicalBlock(scope: !1711, file: !1, line: 484, column: 6)
!2510 = !DILocation(line: 484, column: 26, scope: !2509)
!2511 = !DILocation(line: 484, column: 30, scope: !2509)
!2512 = !DILocation(line: 484, column: 14, scope: !2509)
!2513 = !DILocation(line: 484, column: 6, scope: !1711)
!2514 = !DILocation(line: 486, column: 21, scope: !2515)
!2515 = distinct !DILexicalBlock(scope: !2509, file: !1, line: 484, column: 40)
!2516 = !DILocation(line: 486, column: 5, scope: !2515)
!2517 = !DILocation(line: 486, column: 9, scope: !2515)
!2518 = !DILocation(line: 486, column: 18, scope: !2515)
!2519 = !DILocation(line: 487, column: 3, scope: !2515)
!2520 = !DILocation(line: 489, column: 5, scope: !2521)
!2521 = distinct !DILexicalBlock(scope: !2509, file: !1, line: 488, column: 8)
!2522 = !DILocation(line: 490, column: 5, scope: !2521)
!2523 = !DILocation(line: 490, column: 9, scope: !2521)
!2524 = !DILocation(line: 490, column: 17, scope: !2521)
!2525 = !DILocation(line: 491, column: 20, scope: !2521)
!2526 = !DILocation(line: 491, column: 24, scope: !2521)
!2527 = !DILocation(line: 491, column: 33, scope: !2521)
!2528 = !DILocation(line: 491, column: 5, scope: !2521)
!2529 = !DILocation(line: 491, column: 9, scope: !2521)
!2530 = !DILocation(line: 491, column: 18, scope: !2521)
!2531 = !DILocation(line: 492, column: 5, scope: !2521)
!2532 = !DILocation(line: 492, column: 9, scope: !2521)
!2533 = !DILocation(line: 492, column: 20, scope: !2521)
!2534 = !DILocation(line: 492, column: 20, scope: !2535)
!2535 = !DILexicalBlockFile(scope: !2521, file: !1, discriminator: 1)
!2536 = !DILocation(line: 494, column: 3, scope: !1711)
!2537 = !DILocation(line: 495, column: 1, scope: !1711)
!2538 = !DILocalVariable(name: "pp", arg: 1, scope: !1714, file: !1, line: 497, type: !1683)
!2539 = !DILocation(line: 497, column: 46, scope: !1714)
!2540 = !DILocation(line: 499, column: 3, scope: !1714)
!2541 = !DILocation(line: 500, column: 3, scope: !1714)
!2542 = !DILocation(line: 500, column: 7, scope: !1714)
!2543 = !DILocation(line: 500, column: 13, scope: !1714)
!2544 = !DILocation(line: 501, column: 3, scope: !1714)
