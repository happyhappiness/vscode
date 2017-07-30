; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/progress.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

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
%struct.timeval = type { i64, i64 }
%struct.Curl_handler = type { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }
%struct.dynamically_allocated_data = type { i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8* }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%union.anon.0 = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, i32 (%struct.connectdata*)*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }

@.str = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.1 = private unnamed_addr constant [17 x i8] c"Callback aborted\00", align 1
@.str.2 = private unnamed_addr constant [45 x i8] c"** Resuming transfer from byte position %ld\0A\00", align 1
@.str.3 = private unnamed_addr constant [162 x i8] c"  %% Total    %% Received %% Xferd  Average Speed   Time    Time     Time  Current\0A                                 Dload  Upload   Total   Spent    Left  Speed\0A\00", align 1
@.str.4 = private unnamed_addr constant [47 x i8] c"\0D%3ld %s  %3ld %s  %3ld %s  %s  %s %s %s %s %s\00", align 1
@.str.5 = private unnamed_addr constant [9 x i8] c"--:--:--\00", align 1
@.str.6 = private unnamed_addr constant [17 x i8] c"%2ld:%02ld:%02ld\00", align 1
@.str.7 = private unnamed_addr constant [13 x i8] c"%3ldd %02ldh\00", align 1
@.str.8 = private unnamed_addr constant [6 x i8] c"%7ldd\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"%5ld\00", align 1
@.str.10 = private unnamed_addr constant [6 x i8] c"%4ldk\00", align 1
@.str.11 = private unnamed_addr constant [11 x i8] c"%2ld.%0ldM\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"%4ldM\00", align 1
@.str.13 = private unnamed_addr constant [11 x i8] c"%2ld.%0ldG\00", align 1
@.str.14 = private unnamed_addr constant [6 x i8] c"%4ldG\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"%4ldT\00", align 1
@.str.16 = private unnamed_addr constant [6 x i8] c"%4ldP\00", align 1

; Function Attrs: nounwind uwtable
define i32 @Curl_pgrsDone(%struct.connectdata* %conn) #0 !dbg !1695 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %rc = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1726, metadata !1727), !dbg !1728
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !1729, metadata !1727), !dbg !1730
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1731, metadata !1727), !dbg !1732
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1733
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !1734
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1734
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !1732
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1735
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 16, !dbg !1736
  %lastshow = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 0, !dbg !1737
  store i64 0, i64* %lastshow, align 8, !dbg !1738
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1739
  %call = call i32 @Curl_pgrsUpdate(%struct.connectdata* %3), !dbg !1740
  store i32 %call, i32* %rc, align 4, !dbg !1741
  %4 = load i32, i32* %rc, align 4, !dbg !1742
  %tobool = icmp ne i32 %4, 0, !dbg !1742
  br i1 %tobool, label %if.then, label %if.end, !dbg !1744

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %rc, align 4, !dbg !1745
  store i32 %5, i32* %retval, align 4, !dbg !1746
  br label %return, !dbg !1746

if.end:                                           ; preds = %entry
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1747
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 16, !dbg !1749
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 8, !dbg !1750
  %7 = load i32, i32* %flags, align 8, !dbg !1750
  %and = and i32 %7, 16, !dbg !1751
  %tobool3 = icmp ne i32 %and, 0, !dbg !1751
  br i1 %tobool3, label %if.end8, label %land.lhs.true, !dbg !1752

land.lhs.true:                                    ; preds = %if.end
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1753
  %progress4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 16, !dbg !1754
  %callback = getelementptr inbounds %struct.Progress, %struct.Progress* %progress4, i32 0, i32 6, !dbg !1755
  %9 = load i8, i8* %callback, align 8, !dbg !1755
  %tobool5 = trunc i8 %9 to i1, !dbg !1755
  br i1 %tobool5, label %if.end8, label %if.then6, !dbg !1756

if.then6:                                         ; preds = %land.lhs.true
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1758
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 13, !dbg !1759
  %err = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 0, !dbg !1760
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** %err, align 8, !dbg !1760
  %call7 = call i32 (%struct._IO_FILE*, i8*, ...) @curl_mfprintf(%struct._IO_FILE* %11, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)), !dbg !1761
  br label %if.end8, !dbg !1761

if.end8:                                          ; preds = %if.then6, %land.lhs.true, %if.end
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1762
  %progress9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 16, !dbg !1763
  %speeder_c = getelementptr inbounds %struct.Progress, %struct.Progress* %progress9, i32 0, i32 28, !dbg !1764
  store i32 0, i32* %speeder_c, align 8, !dbg !1765
  store i32 0, i32* %retval, align 4, !dbg !1766
  br label %return, !dbg !1766

return:                                           ; preds = %if.end8, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !1767
  ret i32 %13, !dbg !1767
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_pgrsUpdate(%struct.connectdata* %conn) #0 !dbg !1716 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %now = alloca %struct.timeval, align 8
  %result = alloca i32, align 4
  %max5 = alloca [6 x [10 x i8]], align 16
  %dlpercen = alloca i64, align 8
  %ulpercen = alloca i64, align 8
  %total_percen = alloca i64, align 8
  %total_transfer = alloca i64, align 8
  %total_expected_transfer = alloca i64, align 8
  %timespent = alloca i64, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %nowindex = alloca i32, align 4
  %checkindex = alloca i32, align 4
  %countindex = alloca i32, align 4
  %time_left = alloca [10 x i8], align 1
  %time_total = alloca [10 x i8], align 1
  %time_spent = alloca [10 x i8], align 1
  %ulestimate = alloca i64, align 8
  %dlestimate = alloca i64, align 8
  %total_estimate = alloca i64, align 8
  %shownow = alloca i8, align 1
  %coerce = alloca %struct.timeval, align 8
  %span_ms = alloca i64, align 8
  %amount = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1768, metadata !1727), !dbg !1769
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !1770, metadata !1727), !dbg !1771
  call void @llvm.dbg.declare(metadata i32* %result, metadata !1772, metadata !1727), !dbg !1773
  call void @llvm.dbg.declare(metadata [6 x [10 x i8]]* %max5, metadata !1774, metadata !1727), !dbg !1778
  call void @llvm.dbg.declare(metadata i64* %dlpercen, metadata !1779, metadata !1727), !dbg !1780
  store i64 0, i64* %dlpercen, align 8, !dbg !1780
  call void @llvm.dbg.declare(metadata i64* %ulpercen, metadata !1781, metadata !1727), !dbg !1782
  store i64 0, i64* %ulpercen, align 8, !dbg !1782
  call void @llvm.dbg.declare(metadata i64* %total_percen, metadata !1783, metadata !1727), !dbg !1784
  store i64 0, i64* %total_percen, align 8, !dbg !1784
  call void @llvm.dbg.declare(metadata i64* %total_transfer, metadata !1785, metadata !1727), !dbg !1786
  call void @llvm.dbg.declare(metadata i64* %total_expected_transfer, metadata !1787, metadata !1727), !dbg !1788
  call void @llvm.dbg.declare(metadata i64* %timespent, metadata !1789, metadata !1727), !dbg !1790
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1791, metadata !1727), !dbg !1792
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1793
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !1794
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1794
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !1792
  call void @llvm.dbg.declare(metadata i32* %nowindex, metadata !1795, metadata !1727), !dbg !1796
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1797
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 16, !dbg !1798
  %speeder_c = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 28, !dbg !1799
  %3 = load i32, i32* %speeder_c, align 8, !dbg !1799
  %rem = srem i32 %3, 6, !dbg !1800
  store i32 %rem, i32* %nowindex, align 4, !dbg !1796
  call void @llvm.dbg.declare(metadata i32* %checkindex, metadata !1801, metadata !1727), !dbg !1802
  call void @llvm.dbg.declare(metadata i32* %countindex, metadata !1803, metadata !1727), !dbg !1804
  call void @llvm.dbg.declare(metadata [10 x i8]* %time_left, metadata !1805, metadata !1727), !dbg !1808
  call void @llvm.dbg.declare(metadata [10 x i8]* %time_total, metadata !1809, metadata !1727), !dbg !1810
  call void @llvm.dbg.declare(metadata [10 x i8]* %time_spent, metadata !1811, metadata !1727), !dbg !1812
  call void @llvm.dbg.declare(metadata i64* %ulestimate, metadata !1813, metadata !1727), !dbg !1814
  store i64 0, i64* %ulestimate, align 8, !dbg !1814
  call void @llvm.dbg.declare(metadata i64* %dlestimate, metadata !1815, metadata !1727), !dbg !1816
  store i64 0, i64* %dlestimate, align 8, !dbg !1816
  call void @llvm.dbg.declare(metadata i64* %total_estimate, metadata !1817, metadata !1727), !dbg !1818
  call void @llvm.dbg.declare(metadata i8* %shownow, metadata !1819, metadata !1727), !dbg !1820
  store i8 0, i8* %shownow, align 1, !dbg !1820
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !1821
  %4 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !1821
  %5 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %4, i32 0, i32 0, !dbg !1821
  %6 = extractvalue { i64, i64 } %call, 0, !dbg !1821
  store i64 %6, i64* %5, align 8, !dbg !1821
  %7 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %4, i32 0, i32 1, !dbg !1821
  %8 = extractvalue { i64, i64 } %call, 1, !dbg !1821
  store i64 %8, i64* %7, align 8, !dbg !1821
  %9 = bitcast %struct.timeval* %now to i8*, !dbg !1821
  %10 = bitcast %struct.timeval* %coerce to i8*, !dbg !1821
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %9, i8* %10, i64 16, i32 8, i1 false), !dbg !1822
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1824
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 16, !dbg !1825
  %start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 18, !dbg !1826
  %12 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !1827
  %13 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %12, i32 0, i32 0, !dbg !1827
  %14 = load i64, i64* %13, align 8, !dbg !1827
  %15 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %12, i32 0, i32 1, !dbg !1827
  %16 = load i64, i64* %15, align 8, !dbg !1827
  %17 = bitcast %struct.timeval* %start to { i64, i64 }*, !dbg !1827
  %18 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %17, i32 0, i32 0, !dbg !1827
  %19 = load i64, i64* %18, align 8, !dbg !1827
  %20 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %17, i32 0, i32 1, !dbg !1827
  %21 = load i64, i64* %20, align 8, !dbg !1827
  %call3 = call double @curlx_tvdiff_secs(i64 %14, i64 %16, i64 %19, i64 %21), !dbg !1827
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1828
  %progress4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 16, !dbg !1829
  %timespent5 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress4, i32 0, i32 9, !dbg !1830
  store double %call3, double* %timespent5, align 8, !dbg !1831
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1832
  %progress6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 16, !dbg !1833
  %timespent7 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress6, i32 0, i32 9, !dbg !1834
  %24 = load double, double* %timespent7, align 8, !dbg !1834
  %conv = fptosi double %24 to i64, !dbg !1835
  store i64 %conv, i64* %timespent, align 8, !dbg !1836
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1837
  %progress8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 16, !dbg !1838
  %downloaded = getelementptr inbounds %struct.Progress, %struct.Progress* %progress8, i32 0, i32 3, !dbg !1839
  %26 = load i64, i64* %downloaded, align 8, !dbg !1839
  %conv9 = sitofp i64 %26 to double, !dbg !1840
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1841
  %progress10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %27, i32 0, i32 16, !dbg !1842
  %timespent11 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress10, i32 0, i32 9, !dbg !1843
  %28 = load double, double* %timespent11, align 8, !dbg !1843
  %cmp = fcmp ogt double %28, 0.000000e+00, !dbg !1844
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1841

cond.true:                                        ; preds = %entry
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1845
  %progress13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 16, !dbg !1846
  %timespent14 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress13, i32 0, i32 9, !dbg !1847
  %30 = load double, double* %timespent14, align 8, !dbg !1847
  br label %cond.end, !dbg !1848

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1849

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi double [ %30, %cond.true ], [ 1.000000e+00, %cond.false ], !dbg !1851
  %div = fdiv double %conv9, %cond, !dbg !1853
  %conv15 = fptosi double %div to i64, !dbg !1854
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1855
  %progress16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %31, i32 0, i32 16, !dbg !1856
  %dlspeed = getelementptr inbounds %struct.Progress, %struct.Progress* %progress16, i32 0, i32 10, !dbg !1857
  store i64 %conv15, i64* %dlspeed, align 8, !dbg !1858
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1859
  %progress17 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 16, !dbg !1860
  %uploaded = getelementptr inbounds %struct.Progress, %struct.Progress* %progress17, i32 0, i32 4, !dbg !1861
  %33 = load i64, i64* %uploaded, align 8, !dbg !1861
  %conv18 = sitofp i64 %33 to double, !dbg !1862
  %34 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1863
  %progress19 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %34, i32 0, i32 16, !dbg !1864
  %timespent20 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress19, i32 0, i32 9, !dbg !1865
  %35 = load double, double* %timespent20, align 8, !dbg !1865
  %cmp21 = fcmp ogt double %35, 0.000000e+00, !dbg !1866
  br i1 %cmp21, label %cond.true23, label %cond.false26, !dbg !1863

cond.true23:                                      ; preds = %cond.end
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1867
  %progress24 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 16, !dbg !1868
  %timespent25 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress24, i32 0, i32 9, !dbg !1869
  %37 = load double, double* %timespent25, align 8, !dbg !1869
  br label %cond.end27, !dbg !1870

cond.false26:                                     ; preds = %cond.end
  br label %cond.end27, !dbg !1871

cond.end27:                                       ; preds = %cond.false26, %cond.true23
  %cond28 = phi double [ %37, %cond.true23 ], [ 1.000000e+00, %cond.false26 ], !dbg !1872
  %div29 = fdiv double %conv18, %cond28, !dbg !1873
  %conv30 = fptosi double %div29 to i64, !dbg !1874
  %38 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1875
  %progress31 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %38, i32 0, i32 16, !dbg !1876
  %ulspeed = getelementptr inbounds %struct.Progress, %struct.Progress* %progress31, i32 0, i32 11, !dbg !1877
  store i64 %conv30, i64* %ulspeed, align 8, !dbg !1878
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1879
  %progress32 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %39, i32 0, i32 16, !dbg !1881
  %lastshow = getelementptr inbounds %struct.Progress, %struct.Progress* %progress32, i32 0, i32 0, !dbg !1882
  %40 = load i64, i64* %lastshow, align 8, !dbg !1882
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %now, i32 0, i32 0, !dbg !1883
  %41 = load i64, i64* %tv_sec, align 8, !dbg !1883
  %cmp33 = icmp ne i64 %40, %41, !dbg !1884
  br i1 %cmp33, label %if.then, label %if.end128, !dbg !1885

if.then:                                          ; preds = %cond.end27
  store i8 1, i8* %shownow, align 1, !dbg !1886
  %tv_sec35 = getelementptr inbounds %struct.timeval, %struct.timeval* %now, i32 0, i32 0, !dbg !1888
  %42 = load i64, i64* %tv_sec35, align 8, !dbg !1888
  %43 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1889
  %progress36 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %43, i32 0, i32 16, !dbg !1890
  %lastshow37 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress36, i32 0, i32 0, !dbg !1891
  store i64 %42, i64* %lastshow37, align 8, !dbg !1892
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1893
  %progress38 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %44, i32 0, i32 16, !dbg !1894
  %downloaded39 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress38, i32 0, i32 3, !dbg !1895
  %45 = load i64, i64* %downloaded39, align 8, !dbg !1895
  %46 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1896
  %progress40 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %46, i32 0, i32 16, !dbg !1897
  %uploaded41 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress40, i32 0, i32 4, !dbg !1898
  %47 = load i64, i64* %uploaded41, align 8, !dbg !1898
  %cmp42 = icmp sgt i64 %45, %47, !dbg !1899
  br i1 %cmp42, label %cond.true44, label %cond.false47, !dbg !1893

cond.true44:                                      ; preds = %if.then
  %48 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1900
  %progress45 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %48, i32 0, i32 16, !dbg !1901
  %downloaded46 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress45, i32 0, i32 3, !dbg !1902
  %49 = load i64, i64* %downloaded46, align 8, !dbg !1902
  br label %cond.end50, !dbg !1903

cond.false47:                                     ; preds = %if.then
  %50 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1905
  %progress48 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %50, i32 0, i32 16, !dbg !1906
  %uploaded49 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress48, i32 0, i32 4, !dbg !1907
  %51 = load i64, i64* %uploaded49, align 8, !dbg !1907
  br label %cond.end50, !dbg !1908

cond.end50:                                       ; preds = %cond.false47, %cond.true44
  %cond51 = phi i64 [ %49, %cond.true44 ], [ %51, %cond.false47 ], !dbg !1910
  %52 = load i32, i32* %nowindex, align 4, !dbg !1912
  %idxprom = sext i32 %52 to i64, !dbg !1913
  %53 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1913
  %progress52 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %53, i32 0, i32 16, !dbg !1914
  %speeder = getelementptr inbounds %struct.Progress, %struct.Progress* %progress52, i32 0, i32 26, !dbg !1915
  %arrayidx = getelementptr inbounds [6 x i64], [6 x i64]* %speeder, i64 0, i64 %idxprom, !dbg !1913
  store i64 %cond51, i64* %arrayidx, align 8, !dbg !1916
  %54 = load i32, i32* %nowindex, align 4, !dbg !1917
  %idxprom53 = sext i32 %54 to i64, !dbg !1918
  %55 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1918
  %progress54 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %55, i32 0, i32 16, !dbg !1919
  %speeder_time = getelementptr inbounds %struct.Progress, %struct.Progress* %progress54, i32 0, i32 27, !dbg !1920
  %arrayidx55 = getelementptr inbounds [6 x %struct.timeval], [6 x %struct.timeval]* %speeder_time, i64 0, i64 %idxprom53, !dbg !1918
  %56 = bitcast %struct.timeval* %arrayidx55 to i8*, !dbg !1921
  %57 = bitcast %struct.timeval* %now to i8*, !dbg !1921
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %56, i8* %57, i64 16, i32 8, i1 false), !dbg !1921
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1922
  %progress56 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %58, i32 0, i32 16, !dbg !1923
  %speeder_c57 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress56, i32 0, i32 28, !dbg !1924
  %59 = load i32, i32* %speeder_c57, align 8, !dbg !1925
  %inc = add nsw i32 %59, 1, !dbg !1925
  store i32 %inc, i32* %speeder_c57, align 8, !dbg !1925
  %60 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1926
  %progress58 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %60, i32 0, i32 16, !dbg !1927
  %speeder_c59 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress58, i32 0, i32 28, !dbg !1928
  %61 = load i32, i32* %speeder_c59, align 8, !dbg !1928
  %cmp60 = icmp sge i32 %61, 6, !dbg !1929
  br i1 %cmp60, label %cond.true62, label %cond.false63, !dbg !1930

cond.true62:                                      ; preds = %cond.end50
  br label %cond.end66, !dbg !1931

cond.false63:                                     ; preds = %cond.end50
  %62 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1932
  %progress64 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %62, i32 0, i32 16, !dbg !1933
  %speeder_c65 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress64, i32 0, i32 28, !dbg !1934
  %63 = load i32, i32* %speeder_c65, align 8, !dbg !1934
  br label %cond.end66, !dbg !1935

cond.end66:                                       ; preds = %cond.false63, %cond.true62
  %cond67 = phi i32 [ 6, %cond.true62 ], [ %63, %cond.false63 ], !dbg !1936
  %sub = sub nsw i32 %cond67, 1, !dbg !1937
  store i32 %sub, i32* %countindex, align 4, !dbg !1938
  %64 = load i32, i32* %countindex, align 4, !dbg !1939
  %tobool = icmp ne i32 %64, 0, !dbg !1939
  br i1 %tobool, label %if.then68, label %if.else110, !dbg !1941

if.then68:                                        ; preds = %cond.end66
  call void @llvm.dbg.declare(metadata i64* %span_ms, metadata !1942, metadata !1727), !dbg !1944
  %65 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1945
  %progress69 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %65, i32 0, i32 16, !dbg !1946
  %speeder_c70 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress69, i32 0, i32 28, !dbg !1947
  %66 = load i32, i32* %speeder_c70, align 8, !dbg !1947
  %cmp71 = icmp sge i32 %66, 6, !dbg !1948
  br i1 %cmp71, label %cond.true73, label %cond.false77, !dbg !1949

cond.true73:                                      ; preds = %if.then68
  %67 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1950
  %progress74 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %67, i32 0, i32 16, !dbg !1951
  %speeder_c75 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress74, i32 0, i32 28, !dbg !1952
  %68 = load i32, i32* %speeder_c75, align 8, !dbg !1952
  %rem76 = srem i32 %68, 6, !dbg !1953
  br label %cond.end78, !dbg !1954

cond.false77:                                     ; preds = %if.then68
  br label %cond.end78, !dbg !1956

cond.end78:                                       ; preds = %cond.false77, %cond.true73
  %cond79 = phi i32 [ %rem76, %cond.true73 ], [ 0, %cond.false77 ], !dbg !1958
  store i32 %cond79, i32* %checkindex, align 4, !dbg !1960
  %69 = load i32, i32* %checkindex, align 4, !dbg !1961
  %idxprom80 = sext i32 %69 to i64, !dbg !1961
  %70 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1961
  %progress81 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %70, i32 0, i32 16, !dbg !1961
  %speeder_time82 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress81, i32 0, i32 27, !dbg !1961
  %arrayidx83 = getelementptr inbounds [6 x %struct.timeval], [6 x %struct.timeval]* %speeder_time82, i64 0, i64 %idxprom80, !dbg !1961
  %71 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !1961
  %72 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %71, i32 0, i32 0, !dbg !1961
  %73 = load i64, i64* %72, align 8, !dbg !1961
  %74 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %71, i32 0, i32 1, !dbg !1961
  %75 = load i64, i64* %74, align 8, !dbg !1961
  %76 = bitcast %struct.timeval* %arrayidx83 to { i64, i64 }*, !dbg !1961
  %77 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %76, i32 0, i32 0, !dbg !1961
  %78 = load i64, i64* %77, align 8, !dbg !1961
  %79 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %76, i32 0, i32 1, !dbg !1961
  %80 = load i64, i64* %79, align 8, !dbg !1961
  %call84 = call i64 @curlx_tvdiff(i64 %73, i64 %75, i64 %78, i64 %80), !dbg !1961
  store i64 %call84, i64* %span_ms, align 8, !dbg !1962
  %81 = load i64, i64* %span_ms, align 8, !dbg !1963
  %cmp85 = icmp eq i64 0, %81, !dbg !1965
  br i1 %cmp85, label %if.then87, label %if.end, !dbg !1966

if.then87:                                        ; preds = %cond.end78
  store i64 1, i64* %span_ms, align 8, !dbg !1967
  br label %if.end, !dbg !1968

if.end:                                           ; preds = %if.then87, %cond.end78
  call void @llvm.dbg.declare(metadata i64* %amount, metadata !1969, metadata !1727), !dbg !1971
  %82 = load i32, i32* %nowindex, align 4, !dbg !1972
  %idxprom88 = sext i32 %82 to i64, !dbg !1973
  %83 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1973
  %progress89 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %83, i32 0, i32 16, !dbg !1974
  %speeder90 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress89, i32 0, i32 26, !dbg !1975
  %arrayidx91 = getelementptr inbounds [6 x i64], [6 x i64]* %speeder90, i64 0, i64 %idxprom88, !dbg !1973
  %84 = load i64, i64* %arrayidx91, align 8, !dbg !1973
  %85 = load i32, i32* %checkindex, align 4, !dbg !1976
  %idxprom92 = sext i32 %85 to i64, !dbg !1977
  %86 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1977
  %progress93 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %86, i32 0, i32 16, !dbg !1978
  %speeder94 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress93, i32 0, i32 26, !dbg !1979
  %arrayidx95 = getelementptr inbounds [6 x i64], [6 x i64]* %speeder94, i64 0, i64 %idxprom92, !dbg !1977
  %87 = load i64, i64* %arrayidx95, align 8, !dbg !1977
  %sub96 = sub nsw i64 %84, %87, !dbg !1980
  store i64 %sub96, i64* %amount, align 8, !dbg !1971
  %88 = load i64, i64* %amount, align 8, !dbg !1981
  %cmp97 = icmp sgt i64 %88, 4294967, !dbg !1983
  br i1 %cmp97, label %if.then99, label %if.else, !dbg !1984

if.then99:                                        ; preds = %if.end
  %89 = load i64, i64* %amount, align 8, !dbg !1985
  %conv100 = sitofp i64 %89 to double, !dbg !1986
  %90 = load i64, i64* %span_ms, align 8, !dbg !1987
  %conv101 = sitofp i64 %90 to double, !dbg !1988
  %div102 = fdiv double %conv101, 1.000000e+03, !dbg !1989
  %div103 = fdiv double %conv100, %div102, !dbg !1990
  %conv104 = fptosi double %div103 to i64, !dbg !1991
  %91 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1992
  %progress105 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %91, i32 0, i32 16, !dbg !1993
  %current_speed = getelementptr inbounds %struct.Progress, %struct.Progress* %progress105, i32 0, i32 5, !dbg !1994
  store i64 %conv104, i64* %current_speed, align 8, !dbg !1995
  br label %if.end109, !dbg !1992

if.else:                                          ; preds = %if.end
  %92 = load i64, i64* %amount, align 8, !dbg !1996
  %mul = mul nsw i64 %92, 1000, !dbg !1997
  %93 = load i64, i64* %span_ms, align 8, !dbg !1998
  %div106 = sdiv i64 %mul, %93, !dbg !1999
  %94 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2000
  %progress107 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %94, i32 0, i32 16, !dbg !2001
  %current_speed108 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress107, i32 0, i32 5, !dbg !2002
  store i64 %div106, i64* %current_speed108, align 8, !dbg !2003
  br label %if.end109

if.end109:                                        ; preds = %if.else, %if.then99
  br label %if.end127, !dbg !2004

if.else110:                                       ; preds = %cond.end66
  %95 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2005
  %progress111 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %95, i32 0, i32 16, !dbg !2006
  %ulspeed112 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress111, i32 0, i32 11, !dbg !2007
  %96 = load i64, i64* %ulspeed112, align 8, !dbg !2007
  %97 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2008
  %progress113 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %97, i32 0, i32 16, !dbg !2009
  %dlspeed114 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress113, i32 0, i32 10, !dbg !2010
  %98 = load i64, i64* %dlspeed114, align 8, !dbg !2010
  %cmp115 = icmp sgt i64 %96, %98, !dbg !2011
  br i1 %cmp115, label %cond.true117, label %cond.false120, !dbg !2012

cond.true117:                                     ; preds = %if.else110
  %99 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2013
  %progress118 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %99, i32 0, i32 16, !dbg !2014
  %ulspeed119 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress118, i32 0, i32 11, !dbg !2015
  %100 = load i64, i64* %ulspeed119, align 8, !dbg !2015
  br label %cond.end123, !dbg !2016

cond.false120:                                    ; preds = %if.else110
  %101 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2018
  %progress121 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %101, i32 0, i32 16, !dbg !2019
  %dlspeed122 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress121, i32 0, i32 10, !dbg !2020
  %102 = load i64, i64* %dlspeed122, align 8, !dbg !2020
  br label %cond.end123, !dbg !2021

cond.end123:                                      ; preds = %cond.false120, %cond.true117
  %cond124 = phi i64 [ %100, %cond.true117 ], [ %102, %cond.false120 ], !dbg !2023
  %103 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2025
  %progress125 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %103, i32 0, i32 16, !dbg !2026
  %current_speed126 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress125, i32 0, i32 5, !dbg !2027
  store i64 %cond124, i64* %current_speed126, align 8, !dbg !2028
  br label %if.end127

if.end127:                                        ; preds = %cond.end123, %if.end109
  br label %if.end128, !dbg !2029

if.end128:                                        ; preds = %if.end127, %cond.end27
  %104 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2030
  %progress129 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %104, i32 0, i32 16, !dbg !2032
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress129, i32 0, i32 8, !dbg !2033
  %105 = load i32, i32* %flags, align 8, !dbg !2033
  %and = and i32 %105, 16, !dbg !2034
  %tobool130 = icmp ne i32 %and, 0, !dbg !2034
  br i1 %tobool130, label %if.end368, label %if.then131, !dbg !2035

if.then131:                                       ; preds = %if.end128
  %106 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2036
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %106, i32 0, i32 13, !dbg !2039
  %fxferinfo = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 27, !dbg !2040
  %107 = load i32 (i8*, i64, i64, i64, i64)*, i32 (i8*, i64, i64, i64, i64)** %fxferinfo, align 8, !dbg !2040
  %tobool132 = icmp ne i32 (i8*, i64, i64, i64, i64)* %107, null, !dbg !2036
  br i1 %tobool132, label %if.then133, label %if.end147, !dbg !2041

if.then133:                                       ; preds = %if.then131
  %108 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2042
  %set134 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %108, i32 0, i32 13, !dbg !2044
  %fxferinfo135 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set134, i32 0, i32 27, !dbg !2045
  %109 = load i32 (i8*, i64, i64, i64, i64)*, i32 (i8*, i64, i64, i64, i64)** %fxferinfo135, align 8, !dbg !2045
  %110 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2046
  %set136 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %110, i32 0, i32 13, !dbg !2047
  %progress_client = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set136, i32 0, i32 40, !dbg !2048
  %111 = load i8*, i8** %progress_client, align 8, !dbg !2048
  %112 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2049
  %progress137 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %112, i32 0, i32 16, !dbg !2050
  %size_dl = getelementptr inbounds %struct.Progress, %struct.Progress* %progress137, i32 0, i32 1, !dbg !2051
  %113 = load i64, i64* %size_dl, align 8, !dbg !2051
  %114 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2052
  %progress138 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %114, i32 0, i32 16, !dbg !2053
  %downloaded139 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress138, i32 0, i32 3, !dbg !2054
  %115 = load i64, i64* %downloaded139, align 8, !dbg !2054
  %116 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2055
  %progress140 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %116, i32 0, i32 16, !dbg !2056
  %size_ul = getelementptr inbounds %struct.Progress, %struct.Progress* %progress140, i32 0, i32 2, !dbg !2057
  %117 = load i64, i64* %size_ul, align 8, !dbg !2057
  %118 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2058
  %progress141 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %118, i32 0, i32 16, !dbg !2059
  %uploaded142 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress141, i32 0, i32 4, !dbg !2060
  %119 = load i64, i64* %uploaded142, align 8, !dbg !2060
  %call143 = call i32 %109(i8* %111, i64 %113, i64 %115, i64 %117, i64 %119), !dbg !2042
  store i32 %call143, i32* %result, align 4, !dbg !2061
  %120 = load i32, i32* %result, align 4, !dbg !2062
  %tobool144 = icmp ne i32 %120, 0, !dbg !2062
  br i1 %tobool144, label %if.then145, label %if.end146, !dbg !2064

if.then145:                                       ; preds = %if.then133
  %121 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2065
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %121, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.1, i32 0, i32 0)), !dbg !2066
  br label %if.end146, !dbg !2066

if.end146:                                        ; preds = %if.then145, %if.then133
  %122 = load i32, i32* %result, align 4, !dbg !2067
  store i32 %122, i32* %retval, align 4, !dbg !2068
  br label %return, !dbg !2068

if.end147:                                        ; preds = %if.then131
  %123 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2069
  %set148 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %123, i32 0, i32 13, !dbg !2071
  %fprogress = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set148, i32 0, i32 26, !dbg !2072
  %124 = load i32 (i8*, double, double, double, double)*, i32 (i8*, double, double, double, double)** %fprogress, align 8, !dbg !2072
  %tobool149 = icmp ne i32 (i8*, double, double, double, double)* %124, null, !dbg !2069
  br i1 %tobool149, label %if.then150, label %if.end171, !dbg !2073

if.then150:                                       ; preds = %if.end147
  %125 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2074
  %set151 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %125, i32 0, i32 13, !dbg !2076
  %fprogress152 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set151, i32 0, i32 26, !dbg !2077
  %126 = load i32 (i8*, double, double, double, double)*, i32 (i8*, double, double, double, double)** %fprogress152, align 8, !dbg !2077
  %127 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2078
  %set153 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %127, i32 0, i32 13, !dbg !2079
  %progress_client154 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set153, i32 0, i32 40, !dbg !2080
  %128 = load i8*, i8** %progress_client154, align 8, !dbg !2080
  %129 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2081
  %progress155 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %129, i32 0, i32 16, !dbg !2082
  %size_dl156 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress155, i32 0, i32 1, !dbg !2083
  %130 = load i64, i64* %size_dl156, align 8, !dbg !2083
  %conv157 = sitofp i64 %130 to double, !dbg !2084
  %131 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2085
  %progress158 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %131, i32 0, i32 16, !dbg !2086
  %downloaded159 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress158, i32 0, i32 3, !dbg !2087
  %132 = load i64, i64* %downloaded159, align 8, !dbg !2087
  %conv160 = sitofp i64 %132 to double, !dbg !2088
  %133 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2089
  %progress161 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %133, i32 0, i32 16, !dbg !2090
  %size_ul162 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress161, i32 0, i32 2, !dbg !2091
  %134 = load i64, i64* %size_ul162, align 8, !dbg !2091
  %conv163 = sitofp i64 %134 to double, !dbg !2092
  %135 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2093
  %progress164 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %135, i32 0, i32 16, !dbg !2094
  %uploaded165 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress164, i32 0, i32 4, !dbg !2095
  %136 = load i64, i64* %uploaded165, align 8, !dbg !2095
  %conv166 = sitofp i64 %136 to double, !dbg !2096
  %call167 = call i32 %126(i8* %128, double %conv157, double %conv160, double %conv163, double %conv166), !dbg !2074
  store i32 %call167, i32* %result, align 4, !dbg !2097
  %137 = load i32, i32* %result, align 4, !dbg !2098
  %tobool168 = icmp ne i32 %137, 0, !dbg !2098
  br i1 %tobool168, label %if.then169, label %if.end170, !dbg !2100

if.then169:                                       ; preds = %if.then150
  %138 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2101
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %138, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.1, i32 0, i32 0)), !dbg !2102
  br label %if.end170, !dbg !2102

if.end170:                                        ; preds = %if.then169, %if.then150
  %139 = load i32, i32* %result, align 4, !dbg !2103
  store i32 %139, i32* %retval, align 4, !dbg !2104
  br label %return, !dbg !2104

if.end171:                                        ; preds = %if.end147
  %140 = load i8, i8* %shownow, align 1, !dbg !2105
  %tobool172 = trunc i8 %140 to i1, !dbg !2105
  br i1 %tobool172, label %if.end174, label %if.then173, !dbg !2107

if.then173:                                       ; preds = %if.end171
  store i32 0, i32* %retval, align 4, !dbg !2108
  br label %return, !dbg !2108

if.end174:                                        ; preds = %if.end171
  %141 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2109
  %progress175 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %141, i32 0, i32 16, !dbg !2111
  %flags176 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress175, i32 0, i32 8, !dbg !2112
  %142 = load i32, i32* %flags176, align 8, !dbg !2112
  %and177 = and i32 %142, 128, !dbg !2113
  %tobool178 = icmp ne i32 %and177, 0, !dbg !2113
  br i1 %tobool178, label %if.end192, label %if.then179, !dbg !2114

if.then179:                                       ; preds = %if.end174
  %143 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2115
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %143, i32 0, i32 17, !dbg !2118
  %resume_from = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 43, !dbg !2119
  %144 = load i64, i64* %resume_from, align 8, !dbg !2119
  %tobool180 = icmp ne i64 %144, 0, !dbg !2115
  br i1 %tobool180, label %if.then181, label %if.end186, !dbg !2120

if.then181:                                       ; preds = %if.then179
  %145 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2121
  %set182 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %145, i32 0, i32 13, !dbg !2123
  %err = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set182, i32 0, i32 0, !dbg !2124
  %146 = load %struct._IO_FILE*, %struct._IO_FILE** %err, align 8, !dbg !2124
  %147 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2125
  %state183 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %147, i32 0, i32 17, !dbg !2126
  %resume_from184 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state183, i32 0, i32 43, !dbg !2127
  %148 = load i64, i64* %resume_from184, align 8, !dbg !2127
  %call185 = call i32 (%struct._IO_FILE*, i8*, ...) @curl_mfprintf(%struct._IO_FILE* %146, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.2, i32 0, i32 0), i64 %148), !dbg !2128
  br label %if.end186, !dbg !2129

if.end186:                                        ; preds = %if.then181, %if.then179
  %149 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2130
  %set187 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %149, i32 0, i32 13, !dbg !2131
  %err188 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set187, i32 0, i32 0, !dbg !2132
  %150 = load %struct._IO_FILE*, %struct._IO_FILE** %err188, align 8, !dbg !2132
  %call189 = call i32 (%struct._IO_FILE*, i8*, ...) @curl_mfprintf(%struct._IO_FILE* %150, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @.str.3, i32 0, i32 0)), !dbg !2133
  %151 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2134
  %progress190 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %151, i32 0, i32 16, !dbg !2135
  %flags191 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress190, i32 0, i32 8, !dbg !2136
  %152 = load i32, i32* %flags191, align 8, !dbg !2137
  %or = or i32 %152, 128, !dbg !2137
  store i32 %or, i32* %flags191, align 8, !dbg !2137
  br label %if.end192, !dbg !2138

if.end192:                                        ; preds = %if.end186, %if.end174
  %153 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2139
  %progress193 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %153, i32 0, i32 16, !dbg !2141
  %flags194 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress193, i32 0, i32 8, !dbg !2142
  %154 = load i32, i32* %flags194, align 8, !dbg !2142
  %and195 = and i32 %154, 32, !dbg !2143
  %tobool196 = icmp ne i32 %and195, 0, !dbg !2143
  br i1 %tobool196, label %land.lhs.true, label %if.end232, !dbg !2144

land.lhs.true:                                    ; preds = %if.end192
  %155 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2145
  %progress197 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %155, i32 0, i32 16, !dbg !2146
  %ulspeed198 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress197, i32 0, i32 11, !dbg !2147
  %156 = load i64, i64* %ulspeed198, align 8, !dbg !2147
  %cmp199 = icmp sgt i64 %156, 0, !dbg !2148
  br i1 %cmp199, label %if.then201, label %if.end232, !dbg !2149

if.then201:                                       ; preds = %land.lhs.true
  %157 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2151
  %progress202 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %157, i32 0, i32 16, !dbg !2153
  %size_ul203 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress202, i32 0, i32 2, !dbg !2154
  %158 = load i64, i64* %size_ul203, align 8, !dbg !2154
  %159 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2155
  %progress204 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %159, i32 0, i32 16, !dbg !2156
  %ulspeed205 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress204, i32 0, i32 11, !dbg !2157
  %160 = load i64, i64* %ulspeed205, align 8, !dbg !2157
  %div206 = sdiv i64 %158, %160, !dbg !2158
  store i64 %div206, i64* %ulestimate, align 8, !dbg !2159
  %161 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2160
  %progress207 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %161, i32 0, i32 16, !dbg !2162
  %size_ul208 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress207, i32 0, i32 2, !dbg !2163
  %162 = load i64, i64* %size_ul208, align 8, !dbg !2163
  %cmp209 = icmp sgt i64 %162, 10000, !dbg !2164
  br i1 %cmp209, label %if.then211, label %if.else218, !dbg !2165

if.then211:                                       ; preds = %if.then201
  %163 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2166
  %progress212 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %163, i32 0, i32 16, !dbg !2167
  %uploaded213 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress212, i32 0, i32 4, !dbg !2168
  %164 = load i64, i64* %uploaded213, align 8, !dbg !2168
  %165 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2169
  %progress214 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %165, i32 0, i32 16, !dbg !2170
  %size_ul215 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress214, i32 0, i32 2, !dbg !2171
  %166 = load i64, i64* %size_ul215, align 8, !dbg !2171
  %div216 = sdiv i64 %166, 100, !dbg !2172
  %div217 = sdiv i64 %164, %div216, !dbg !2173
  store i64 %div217, i64* %ulpercen, align 8, !dbg !2174
  br label %if.end231, !dbg !2175

if.else218:                                       ; preds = %if.then201
  %167 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2176
  %progress219 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %167, i32 0, i32 16, !dbg !2178
  %size_ul220 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress219, i32 0, i32 2, !dbg !2179
  %168 = load i64, i64* %size_ul220, align 8, !dbg !2179
  %cmp221 = icmp sgt i64 %168, 0, !dbg !2180
  br i1 %cmp221, label %if.then223, label %if.end230, !dbg !2181

if.then223:                                       ; preds = %if.else218
  %169 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2182
  %progress224 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %169, i32 0, i32 16, !dbg !2183
  %uploaded225 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress224, i32 0, i32 4, !dbg !2184
  %170 = load i64, i64* %uploaded225, align 8, !dbg !2184
  %mul226 = mul nsw i64 %170, 100, !dbg !2185
  %171 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2186
  %progress227 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %171, i32 0, i32 16, !dbg !2187
  %size_ul228 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress227, i32 0, i32 2, !dbg !2188
  %172 = load i64, i64* %size_ul228, align 8, !dbg !2188
  %div229 = sdiv i64 %mul226, %172, !dbg !2189
  store i64 %div229, i64* %ulpercen, align 8, !dbg !2190
  br label %if.end230, !dbg !2191

if.end230:                                        ; preds = %if.then223, %if.else218
  br label %if.end231

if.end231:                                        ; preds = %if.end230, %if.then211
  br label %if.end232, !dbg !2192

if.end232:                                        ; preds = %if.end231, %land.lhs.true, %if.end192
  %173 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2193
  %progress233 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %173, i32 0, i32 16, !dbg !2195
  %flags234 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress233, i32 0, i32 8, !dbg !2196
  %174 = load i32, i32* %flags234, align 8, !dbg !2196
  %and235 = and i32 %174, 64, !dbg !2197
  %tobool236 = icmp ne i32 %and235, 0, !dbg !2197
  br i1 %tobool236, label %land.lhs.true237, label %if.end273, !dbg !2198

land.lhs.true237:                                 ; preds = %if.end232
  %175 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2199
  %progress238 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %175, i32 0, i32 16, !dbg !2200
  %dlspeed239 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress238, i32 0, i32 10, !dbg !2201
  %176 = load i64, i64* %dlspeed239, align 8, !dbg !2201
  %cmp240 = icmp sgt i64 %176, 0, !dbg !2202
  br i1 %cmp240, label %if.then242, label %if.end273, !dbg !2203

if.then242:                                       ; preds = %land.lhs.true237
  %177 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2204
  %progress243 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %177, i32 0, i32 16, !dbg !2206
  %size_dl244 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress243, i32 0, i32 1, !dbg !2207
  %178 = load i64, i64* %size_dl244, align 8, !dbg !2207
  %179 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2208
  %progress245 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %179, i32 0, i32 16, !dbg !2209
  %dlspeed246 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress245, i32 0, i32 10, !dbg !2210
  %180 = load i64, i64* %dlspeed246, align 8, !dbg !2210
  %div247 = sdiv i64 %178, %180, !dbg !2211
  store i64 %div247, i64* %dlestimate, align 8, !dbg !2212
  %181 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2213
  %progress248 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %181, i32 0, i32 16, !dbg !2215
  %size_dl249 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress248, i32 0, i32 1, !dbg !2216
  %182 = load i64, i64* %size_dl249, align 8, !dbg !2216
  %cmp250 = icmp sgt i64 %182, 10000, !dbg !2217
  br i1 %cmp250, label %if.then252, label %if.else259, !dbg !2218

if.then252:                                       ; preds = %if.then242
  %183 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2219
  %progress253 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %183, i32 0, i32 16, !dbg !2220
  %downloaded254 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress253, i32 0, i32 3, !dbg !2221
  %184 = load i64, i64* %downloaded254, align 8, !dbg !2221
  %185 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2222
  %progress255 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %185, i32 0, i32 16, !dbg !2223
  %size_dl256 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress255, i32 0, i32 1, !dbg !2224
  %186 = load i64, i64* %size_dl256, align 8, !dbg !2224
  %div257 = sdiv i64 %186, 100, !dbg !2225
  %div258 = sdiv i64 %184, %div257, !dbg !2226
  store i64 %div258, i64* %dlpercen, align 8, !dbg !2227
  br label %if.end272, !dbg !2228

if.else259:                                       ; preds = %if.then242
  %187 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2229
  %progress260 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %187, i32 0, i32 16, !dbg !2231
  %size_dl261 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress260, i32 0, i32 1, !dbg !2232
  %188 = load i64, i64* %size_dl261, align 8, !dbg !2232
  %cmp262 = icmp sgt i64 %188, 0, !dbg !2233
  br i1 %cmp262, label %if.then264, label %if.end271, !dbg !2234

if.then264:                                       ; preds = %if.else259
  %189 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2235
  %progress265 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %189, i32 0, i32 16, !dbg !2236
  %downloaded266 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress265, i32 0, i32 3, !dbg !2237
  %190 = load i64, i64* %downloaded266, align 8, !dbg !2237
  %mul267 = mul nsw i64 %190, 100, !dbg !2238
  %191 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2239
  %progress268 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %191, i32 0, i32 16, !dbg !2240
  %size_dl269 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress268, i32 0, i32 1, !dbg !2241
  %192 = load i64, i64* %size_dl269, align 8, !dbg !2241
  %div270 = sdiv i64 %mul267, %192, !dbg !2242
  store i64 %div270, i64* %dlpercen, align 8, !dbg !2243
  br label %if.end271, !dbg !2244

if.end271:                                        ; preds = %if.then264, %if.else259
  br label %if.end272

if.end272:                                        ; preds = %if.end271, %if.then252
  br label %if.end273, !dbg !2245

if.end273:                                        ; preds = %if.end272, %land.lhs.true237, %if.end232
  %193 = load i64, i64* %ulestimate, align 8, !dbg !2246
  %194 = load i64, i64* %dlestimate, align 8, !dbg !2247
  %cmp274 = icmp sgt i64 %193, %194, !dbg !2248
  br i1 %cmp274, label %cond.true276, label %cond.false277, !dbg !2246

cond.true276:                                     ; preds = %if.end273
  %195 = load i64, i64* %ulestimate, align 8, !dbg !2249
  br label %cond.end278, !dbg !2250

cond.false277:                                    ; preds = %if.end273
  %196 = load i64, i64* %dlestimate, align 8, !dbg !2251
  br label %cond.end278, !dbg !2253

cond.end278:                                      ; preds = %cond.false277, %cond.true276
  %cond279 = phi i64 [ %195, %cond.true276 ], [ %196, %cond.false277 ], !dbg !2254
  store i64 %cond279, i64* %total_estimate, align 8, !dbg !2256
  %arraydecay = getelementptr inbounds [10 x i8], [10 x i8]* %time_left, i32 0, i32 0, !dbg !2257
  %197 = load i64, i64* %total_estimate, align 8, !dbg !2258
  %cmp280 = icmp sgt i64 %197, 0, !dbg !2259
  br i1 %cmp280, label %cond.true282, label %cond.false284, !dbg !2258

cond.true282:                                     ; preds = %cond.end278
  %198 = load i64, i64* %total_estimate, align 8, !dbg !2260
  %199 = load i64, i64* %timespent, align 8, !dbg !2261
  %sub283 = sub nsw i64 %198, %199, !dbg !2262
  br label %cond.end285, !dbg !2263

cond.false284:                                    ; preds = %cond.end278
  br label %cond.end285, !dbg !2264

cond.end285:                                      ; preds = %cond.false284, %cond.true282
  %cond286 = phi i64 [ %sub283, %cond.true282 ], [ 0, %cond.false284 ], !dbg !2265
  call void @time2str(i8* %arraydecay, i64 %cond286), !dbg !2266
  %arraydecay287 = getelementptr inbounds [10 x i8], [10 x i8]* %time_total, i32 0, i32 0, !dbg !2267
  %200 = load i64, i64* %total_estimate, align 8, !dbg !2268
  call void @time2str(i8* %arraydecay287, i64 %200), !dbg !2269
  %arraydecay288 = getelementptr inbounds [10 x i8], [10 x i8]* %time_spent, i32 0, i32 0, !dbg !2270
  %201 = load i64, i64* %timespent, align 8, !dbg !2271
  call void @time2str(i8* %arraydecay288, i64 %201), !dbg !2272
  %202 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2273
  %progress289 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %202, i32 0, i32 16, !dbg !2274
  %flags290 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress289, i32 0, i32 8, !dbg !2275
  %203 = load i32, i32* %flags290, align 8, !dbg !2275
  %and291 = and i32 %203, 32, !dbg !2276
  %tobool292 = icmp ne i32 %and291, 0, !dbg !2276
  br i1 %tobool292, label %cond.true293, label %cond.false296, !dbg !2273

cond.true293:                                     ; preds = %cond.end285
  %204 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2277
  %progress294 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %204, i32 0, i32 16, !dbg !2278
  %size_ul295 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress294, i32 0, i32 2, !dbg !2279
  %205 = load i64, i64* %size_ul295, align 8, !dbg !2279
  br label %cond.end299, !dbg !2280

cond.false296:                                    ; preds = %cond.end285
  %206 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2281
  %progress297 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %206, i32 0, i32 16, !dbg !2282
  %uploaded298 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress297, i32 0, i32 4, !dbg !2283
  %207 = load i64, i64* %uploaded298, align 8, !dbg !2283
  br label %cond.end299, !dbg !2284

cond.end299:                                      ; preds = %cond.false296, %cond.true293
  %cond300 = phi i64 [ %205, %cond.true293 ], [ %207, %cond.false296 ], !dbg !2285
  %208 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2286
  %progress301 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %208, i32 0, i32 16, !dbg !2287
  %flags302 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress301, i32 0, i32 8, !dbg !2288
  %209 = load i32, i32* %flags302, align 8, !dbg !2288
  %and303 = and i32 %209, 64, !dbg !2289
  %tobool304 = icmp ne i32 %and303, 0, !dbg !2289
  br i1 %tobool304, label %cond.true305, label %cond.false308, !dbg !2286

cond.true305:                                     ; preds = %cond.end299
  %210 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2290
  %progress306 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %210, i32 0, i32 16, !dbg !2291
  %size_dl307 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress306, i32 0, i32 1, !dbg !2292
  %211 = load i64, i64* %size_dl307, align 8, !dbg !2292
  br label %cond.end311, !dbg !2293

cond.false308:                                    ; preds = %cond.end299
  %212 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2294
  %progress309 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %212, i32 0, i32 16, !dbg !2295
  %downloaded310 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress309, i32 0, i32 3, !dbg !2296
  %213 = load i64, i64* %downloaded310, align 8, !dbg !2296
  br label %cond.end311, !dbg !2297

cond.end311:                                      ; preds = %cond.false308, %cond.true305
  %cond312 = phi i64 [ %211, %cond.true305 ], [ %213, %cond.false308 ], !dbg !2298
  %add = add nsw i64 %cond300, %cond312, !dbg !2299
  store i64 %add, i64* %total_expected_transfer, align 8, !dbg !2300
  %214 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2301
  %progress313 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %214, i32 0, i32 16, !dbg !2302
  %downloaded314 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress313, i32 0, i32 3, !dbg !2303
  %215 = load i64, i64* %downloaded314, align 8, !dbg !2303
  %216 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2304
  %progress315 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %216, i32 0, i32 16, !dbg !2305
  %uploaded316 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress315, i32 0, i32 4, !dbg !2306
  %217 = load i64, i64* %uploaded316, align 8, !dbg !2306
  %add317 = add nsw i64 %215, %217, !dbg !2307
  store i64 %add317, i64* %total_transfer, align 8, !dbg !2308
  %218 = load i64, i64* %total_expected_transfer, align 8, !dbg !2309
  %cmp318 = icmp sgt i64 %218, 10000, !dbg !2311
  br i1 %cmp318, label %if.then320, label %if.else323, !dbg !2312

if.then320:                                       ; preds = %cond.end311
  %219 = load i64, i64* %total_transfer, align 8, !dbg !2313
  %220 = load i64, i64* %total_expected_transfer, align 8, !dbg !2314
  %div321 = sdiv i64 %220, 100, !dbg !2315
  %div322 = sdiv i64 %219, %div321, !dbg !2316
  store i64 %div322, i64* %total_percen, align 8, !dbg !2317
  br label %if.end330, !dbg !2318

if.else323:                                       ; preds = %cond.end311
  %221 = load i64, i64* %total_expected_transfer, align 8, !dbg !2319
  %cmp324 = icmp sgt i64 %221, 0, !dbg !2321
  br i1 %cmp324, label %if.then326, label %if.end329, !dbg !2322

if.then326:                                       ; preds = %if.else323
  %222 = load i64, i64* %total_transfer, align 8, !dbg !2323
  %mul327 = mul nsw i64 %222, 100, !dbg !2324
  %223 = load i64, i64* %total_expected_transfer, align 8, !dbg !2325
  %div328 = sdiv i64 %mul327, %223, !dbg !2326
  store i64 %div328, i64* %total_percen, align 8, !dbg !2327
  br label %if.end329, !dbg !2328

if.end329:                                        ; preds = %if.then326, %if.else323
  br label %if.end330

if.end330:                                        ; preds = %if.end329, %if.then320
  %224 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2329
  %set331 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %224, i32 0, i32 13, !dbg !2330
  %err332 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set331, i32 0, i32 0, !dbg !2331
  %225 = load %struct._IO_FILE*, %struct._IO_FILE** %err332, align 8, !dbg !2331
  %226 = load i64, i64* %total_percen, align 8, !dbg !2332
  %227 = load i64, i64* %total_expected_transfer, align 8, !dbg !2333
  %arrayidx333 = getelementptr inbounds [6 x [10 x i8]], [6 x [10 x i8]]* %max5, i64 0, i64 2, !dbg !2334
  %arraydecay334 = getelementptr inbounds [10 x i8], [10 x i8]* %arrayidx333, i32 0, i32 0, !dbg !2334
  %call335 = call i8* @max5data(i64 %227, i8* %arraydecay334), !dbg !2335
  %228 = load i64, i64* %dlpercen, align 8, !dbg !2336
  %229 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2337
  %progress336 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %229, i32 0, i32 16, !dbg !2338
  %downloaded337 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress336, i32 0, i32 3, !dbg !2339
  %230 = load i64, i64* %downloaded337, align 8, !dbg !2339
  %arrayidx338 = getelementptr inbounds [6 x [10 x i8]], [6 x [10 x i8]]* %max5, i64 0, i64 0, !dbg !2340
  %arraydecay339 = getelementptr inbounds [10 x i8], [10 x i8]* %arrayidx338, i32 0, i32 0, !dbg !2340
  %call340 = call i8* @max5data(i64 %230, i8* %arraydecay339), !dbg !2341
  %231 = load i64, i64* %ulpercen, align 8, !dbg !2342
  %232 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2343
  %progress341 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %232, i32 0, i32 16, !dbg !2344
  %uploaded342 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress341, i32 0, i32 4, !dbg !2345
  %233 = load i64, i64* %uploaded342, align 8, !dbg !2345
  %arrayidx343 = getelementptr inbounds [6 x [10 x i8]], [6 x [10 x i8]]* %max5, i64 0, i64 1, !dbg !2346
  %arraydecay344 = getelementptr inbounds [10 x i8], [10 x i8]* %arrayidx343, i32 0, i32 0, !dbg !2346
  %call345 = call i8* @max5data(i64 %233, i8* %arraydecay344), !dbg !2347
  %234 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2348
  %progress346 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %234, i32 0, i32 16, !dbg !2349
  %dlspeed347 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress346, i32 0, i32 10, !dbg !2350
  %235 = load i64, i64* %dlspeed347, align 8, !dbg !2350
  %arrayidx348 = getelementptr inbounds [6 x [10 x i8]], [6 x [10 x i8]]* %max5, i64 0, i64 3, !dbg !2351
  %arraydecay349 = getelementptr inbounds [10 x i8], [10 x i8]* %arrayidx348, i32 0, i32 0, !dbg !2351
  %call350 = call i8* @max5data(i64 %235, i8* %arraydecay349), !dbg !2352
  %236 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2353
  %progress351 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %236, i32 0, i32 16, !dbg !2354
  %ulspeed352 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress351, i32 0, i32 11, !dbg !2355
  %237 = load i64, i64* %ulspeed352, align 8, !dbg !2355
  %arrayidx353 = getelementptr inbounds [6 x [10 x i8]], [6 x [10 x i8]]* %max5, i64 0, i64 4, !dbg !2356
  %arraydecay354 = getelementptr inbounds [10 x i8], [10 x i8]* %arrayidx353, i32 0, i32 0, !dbg !2356
  %call355 = call i8* @max5data(i64 %237, i8* %arraydecay354), !dbg !2357
  %arraydecay356 = getelementptr inbounds [10 x i8], [10 x i8]* %time_total, i32 0, i32 0, !dbg !2358
  %arraydecay357 = getelementptr inbounds [10 x i8], [10 x i8]* %time_spent, i32 0, i32 0, !dbg !2359
  %arraydecay358 = getelementptr inbounds [10 x i8], [10 x i8]* %time_left, i32 0, i32 0, !dbg !2360
  %238 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2361
  %progress359 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %238, i32 0, i32 16, !dbg !2362
  %current_speed360 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress359, i32 0, i32 5, !dbg !2363
  %239 = load i64, i64* %current_speed360, align 8, !dbg !2363
  %arrayidx361 = getelementptr inbounds [6 x [10 x i8]], [6 x [10 x i8]]* %max5, i64 0, i64 5, !dbg !2364
  %arraydecay362 = getelementptr inbounds [10 x i8], [10 x i8]* %arrayidx361, i32 0, i32 0, !dbg !2364
  %call363 = call i8* @max5data(i64 %239, i8* %arraydecay362), !dbg !2365
  %call364 = call i32 (%struct._IO_FILE*, i8*, ...) @curl_mfprintf(%struct._IO_FILE* %225, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.4, i32 0, i32 0), i64 %226, i8* %call335, i64 %228, i8* %call340, i64 %231, i8* %call345, i8* %call350, i8* %call355, i8* %arraydecay356, i8* %arraydecay357, i8* %arraydecay358, i8* %call363), !dbg !2366
  %240 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2367
  %set365 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %240, i32 0, i32 13, !dbg !2368
  %err366 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set365, i32 0, i32 0, !dbg !2369
  %241 = load %struct._IO_FILE*, %struct._IO_FILE** %err366, align 8, !dbg !2369
  %call367 = call i32 @fflush(%struct._IO_FILE* %241), !dbg !2370
  br label %if.end368, !dbg !2371

if.end368:                                        ; preds = %if.end330, %if.end128
  store i32 0, i32* %retval, align 4, !dbg !2372
  br label %return, !dbg !2372

return:                                           ; preds = %if.end368, %if.then173, %if.end170, %if.end146
  %242 = load i32, i32* %retval, align 4, !dbg !2373
  ret i32 %242, !dbg !2373
}

declare i32 @curl_mfprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define void @Curl_pgrsResetTimesSizes(%struct.Curl_easy* %data) #0 !dbg !1699 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2374, metadata !1727), !dbg !2375
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2376
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 16, !dbg !2377
  %t_nslookup = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 12, !dbg !2378
  store double 0.000000e+00, double* %t_nslookup, align 8, !dbg !2379
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2380
  %progress1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 16, !dbg !2381
  %t_connect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress1, i32 0, i32 13, !dbg !2382
  store double 0.000000e+00, double* %t_connect, align 8, !dbg !2383
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2384
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 16, !dbg !2385
  %t_pretransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 15, !dbg !2386
  store double 0.000000e+00, double* %t_pretransfer, align 8, !dbg !2387
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2388
  %progress3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 16, !dbg !2389
  %t_starttransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %progress3, i32 0, i32 16, !dbg !2390
  store double 0.000000e+00, double* %t_starttransfer, align 8, !dbg !2391
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2392
  call void @Curl_pgrsSetDownloadSize(%struct.Curl_easy* %4, i64 -1), !dbg !2393
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2394
  call void @Curl_pgrsSetUploadSize(%struct.Curl_easy* %5, i64 -1), !dbg !2395
  ret void, !dbg !2396
}

; Function Attrs: nounwind uwtable
define void @Curl_pgrsSetDownloadSize(%struct.Curl_easy* %data, i64 %size) #0 !dbg !1714 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %size.addr = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2397, metadata !1727), !dbg !2398
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2399, metadata !1727), !dbg !2400
  %0 = load i64, i64* %size.addr, align 8, !dbg !2401
  %cmp = icmp sge i64 %0, 0, !dbg !2403
  br i1 %cmp, label %if.then, label %if.else, !dbg !2404

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %size.addr, align 8, !dbg !2405
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2407
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 16, !dbg !2408
  %size_dl = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 1, !dbg !2409
  store i64 %1, i64* %size_dl, align 8, !dbg !2410
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2411
  %progress1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 16, !dbg !2412
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress1, i32 0, i32 8, !dbg !2413
  %4 = load i32, i32* %flags, align 8, !dbg !2414
  %or = or i32 %4, 64, !dbg !2414
  store i32 %or, i32* %flags, align 8, !dbg !2414
  br label %if.end, !dbg !2415

if.else:                                          ; preds = %entry
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2416
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 16, !dbg !2418
  %size_dl3 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 1, !dbg !2419
  store i64 0, i64* %size_dl3, align 8, !dbg !2420
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2421
  %progress4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 16, !dbg !2422
  %flags5 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress4, i32 0, i32 8, !dbg !2423
  %7 = load i32, i32* %flags5, align 8, !dbg !2424
  %and = and i32 %7, -65, !dbg !2424
  store i32 %and, i32* %flags5, align 8, !dbg !2424
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2425
}

; Function Attrs: nounwind uwtable
define void @Curl_pgrsSetUploadSize(%struct.Curl_easy* %data, i64 %size) #0 !dbg !1715 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %size.addr = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2426, metadata !1727), !dbg !2427
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2428, metadata !1727), !dbg !2429
  %0 = load i64, i64* %size.addr, align 8, !dbg !2430
  %cmp = icmp sge i64 %0, 0, !dbg !2432
  br i1 %cmp, label %if.then, label %if.else, !dbg !2433

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %size.addr, align 8, !dbg !2434
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2436
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 16, !dbg !2437
  %size_ul = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 2, !dbg !2438
  store i64 %1, i64* %size_ul, align 8, !dbg !2439
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2440
  %progress1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 16, !dbg !2441
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress1, i32 0, i32 8, !dbg !2442
  %4 = load i32, i32* %flags, align 8, !dbg !2443
  %or = or i32 %4, 32, !dbg !2443
  store i32 %or, i32* %flags, align 8, !dbg !2443
  br label %if.end, !dbg !2444

if.else:                                          ; preds = %entry
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2445
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 16, !dbg !2447
  %size_ul3 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 2, !dbg !2448
  store i64 0, i64* %size_ul3, align 8, !dbg !2449
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2450
  %progress4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 16, !dbg !2451
  %flags5 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress4, i32 0, i32 8, !dbg !2452
  %7 = load i32, i32* %flags5, align 8, !dbg !2453
  %and = and i32 %7, -33, !dbg !2453
  store i32 %and, i32* %flags5, align 8, !dbg !2453
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2454
}

; Function Attrs: nounwind uwtable
define void @Curl_pgrsTime(%struct.Curl_easy* %data, i32 %timer) #0 !dbg !1702 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %timer.addr = alloca i32, align 4
  %now = alloca %struct.timeval, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2455, metadata !1727), !dbg !2456
  store i32 %timer, i32* %timer.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timer.addr, metadata !2457, metadata !1727), !dbg !2458
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !2459, metadata !1727), !dbg !2460
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2461
  %0 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2461
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0, !dbg !2461
  %2 = extractvalue { i64, i64 } %call, 0, !dbg !2461
  store i64 %2, i64* %1, align 8, !dbg !2461
  %3 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1, !dbg !2461
  %4 = extractvalue { i64, i64 } %call, 1, !dbg !2461
  store i64 %4, i64* %3, align 8, !dbg !2461
  %5 = load i32, i32* %timer.addr, align 4, !dbg !2462
  switch i32 %5, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb1
    i32 2, label %sw.bb2
    i32 9, label %sw.bb4
    i32 3, label %sw.bb7
    i32 4, label %sw.bb12
    i32 5, label %sw.bb17
    i32 6, label %sw.bb22
    i32 7, label %sw.bb27
    i32 8, label %sw.bb32
    i32 10, label %sw.bb33
  ], !dbg !2463

sw.default:                                       ; preds = %entry
  br label %sw.bb, !dbg !2464

sw.bb:                                            ; preds = %entry, %sw.default
  br label %sw.epilog, !dbg !2466

sw.bb1:                                           ; preds = %entry
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2468
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 16, !dbg !2469
  %t_startop = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 20, !dbg !2470
  %7 = bitcast %struct.timeval* %t_startop to i8*, !dbg !2471
  %8 = bitcast %struct.timeval* %now to i8*, !dbg !2471
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 16, i32 8, i1 false), !dbg !2471
  br label %sw.epilog, !dbg !2472

sw.bb2:                                           ; preds = %entry
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2473
  %progress3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 16, !dbg !2474
  %t_startsingle = getelementptr inbounds %struct.Progress, %struct.Progress* %progress3, i32 0, i32 19, !dbg !2475
  %10 = bitcast %struct.timeval* %t_startsingle to i8*, !dbg !2476
  %11 = bitcast %struct.timeval* %now to i8*, !dbg !2476
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* %11, i64 16, i32 8, i1 false), !dbg !2476
  br label %sw.epilog, !dbg !2477

sw.bb4:                                           ; preds = %entry
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2478
  %progress5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 16, !dbg !2479
  %t_acceptdata = getelementptr inbounds %struct.Progress, %struct.Progress* %progress5, i32 0, i32 21, !dbg !2480
  %call6 = call { i64, i64 } @curlx_tvnow(), !dbg !2481
  %13 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2481
  %14 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %13, i32 0, i32 0, !dbg !2481
  %15 = extractvalue { i64, i64 } %call6, 0, !dbg !2481
  store i64 %15, i64* %14, align 8, !dbg !2481
  %16 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %13, i32 0, i32 1, !dbg !2481
  %17 = extractvalue { i64, i64 } %call6, 1, !dbg !2481
  store i64 %17, i64* %16, align 8, !dbg !2481
  %18 = bitcast %struct.timeval* %t_acceptdata to i8*, !dbg !2481
  %19 = bitcast %struct.timeval* %coerce to i8*, !dbg !2481
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %18, i8* %19, i64 16, i32 8, i1 false), !dbg !2482
  br label %sw.epilog, !dbg !2484

sw.bb7:                                           ; preds = %entry
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2485
  %progress8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 16, !dbg !2485
  %t_startsingle9 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress8, i32 0, i32 19, !dbg !2485
  %21 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2485
  %22 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %21, i32 0, i32 0, !dbg !2485
  %23 = load i64, i64* %22, align 8, !dbg !2485
  %24 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %21, i32 0, i32 1, !dbg !2485
  %25 = load i64, i64* %24, align 8, !dbg !2485
  %26 = bitcast %struct.timeval* %t_startsingle9 to { i64, i64 }*, !dbg !2485
  %27 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %26, i32 0, i32 0, !dbg !2485
  %28 = load i64, i64* %27, align 8, !dbg !2485
  %29 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %26, i32 0, i32 1, !dbg !2485
  %30 = load i64, i64* %29, align 8, !dbg !2485
  %call10 = call double @curlx_tvdiff_secs(i64 %23, i64 %25, i64 %28, i64 %30), !dbg !2485
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2486
  %progress11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %31, i32 0, i32 16, !dbg !2487
  %t_nslookup = getelementptr inbounds %struct.Progress, %struct.Progress* %progress11, i32 0, i32 12, !dbg !2488
  store double %call10, double* %t_nslookup, align 8, !dbg !2489
  br label %sw.epilog, !dbg !2490

sw.bb12:                                          ; preds = %entry
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2491
  %progress13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 16, !dbg !2491
  %t_startsingle14 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress13, i32 0, i32 19, !dbg !2491
  %33 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2491
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %33, i32 0, i32 0, !dbg !2491
  %35 = load i64, i64* %34, align 8, !dbg !2491
  %36 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %33, i32 0, i32 1, !dbg !2491
  %37 = load i64, i64* %36, align 8, !dbg !2491
  %38 = bitcast %struct.timeval* %t_startsingle14 to { i64, i64 }*, !dbg !2491
  %39 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %38, i32 0, i32 0, !dbg !2491
  %40 = load i64, i64* %39, align 8, !dbg !2491
  %41 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %38, i32 0, i32 1, !dbg !2491
  %42 = load i64, i64* %41, align 8, !dbg !2491
  %call15 = call double @curlx_tvdiff_secs(i64 %35, i64 %37, i64 %40, i64 %42), !dbg !2491
  %43 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2492
  %progress16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %43, i32 0, i32 16, !dbg !2493
  %t_connect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress16, i32 0, i32 13, !dbg !2494
  store double %call15, double* %t_connect, align 8, !dbg !2495
  br label %sw.epilog, !dbg !2496

sw.bb17:                                          ; preds = %entry
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2497
  %progress18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %44, i32 0, i32 16, !dbg !2497
  %t_startsingle19 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress18, i32 0, i32 19, !dbg !2497
  %45 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2497
  %46 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %45, i32 0, i32 0, !dbg !2497
  %47 = load i64, i64* %46, align 8, !dbg !2497
  %48 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %45, i32 0, i32 1, !dbg !2497
  %49 = load i64, i64* %48, align 8, !dbg !2497
  %50 = bitcast %struct.timeval* %t_startsingle19 to { i64, i64 }*, !dbg !2497
  %51 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %50, i32 0, i32 0, !dbg !2497
  %52 = load i64, i64* %51, align 8, !dbg !2497
  %53 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %50, i32 0, i32 1, !dbg !2497
  %54 = load i64, i64* %53, align 8, !dbg !2497
  %call20 = call double @curlx_tvdiff_secs(i64 %47, i64 %49, i64 %52, i64 %54), !dbg !2497
  %55 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2498
  %progress21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %55, i32 0, i32 16, !dbg !2499
  %t_appconnect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress21, i32 0, i32 14, !dbg !2500
  store double %call20, double* %t_appconnect, align 8, !dbg !2501
  br label %sw.epilog, !dbg !2502

sw.bb22:                                          ; preds = %entry
  %56 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2503
  %progress23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %56, i32 0, i32 16, !dbg !2503
  %t_startsingle24 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress23, i32 0, i32 19, !dbg !2503
  %57 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2503
  %58 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %57, i32 0, i32 0, !dbg !2503
  %59 = load i64, i64* %58, align 8, !dbg !2503
  %60 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %57, i32 0, i32 1, !dbg !2503
  %61 = load i64, i64* %60, align 8, !dbg !2503
  %62 = bitcast %struct.timeval* %t_startsingle24 to { i64, i64 }*, !dbg !2503
  %63 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %62, i32 0, i32 0, !dbg !2503
  %64 = load i64, i64* %63, align 8, !dbg !2503
  %65 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %62, i32 0, i32 1, !dbg !2503
  %66 = load i64, i64* %65, align 8, !dbg !2503
  %call25 = call double @curlx_tvdiff_secs(i64 %59, i64 %61, i64 %64, i64 %66), !dbg !2503
  %67 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2504
  %progress26 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %67, i32 0, i32 16, !dbg !2505
  %t_pretransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %progress26, i32 0, i32 15, !dbg !2506
  store double %call25, double* %t_pretransfer, align 8, !dbg !2507
  br label %sw.epilog, !dbg !2508

sw.bb27:                                          ; preds = %entry
  %68 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2509
  %progress28 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %68, i32 0, i32 16, !dbg !2509
  %t_startsingle29 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress28, i32 0, i32 19, !dbg !2509
  %69 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2509
  %70 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %69, i32 0, i32 0, !dbg !2509
  %71 = load i64, i64* %70, align 8, !dbg !2509
  %72 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %69, i32 0, i32 1, !dbg !2509
  %73 = load i64, i64* %72, align 8, !dbg !2509
  %74 = bitcast %struct.timeval* %t_startsingle29 to { i64, i64 }*, !dbg !2509
  %75 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %74, i32 0, i32 0, !dbg !2509
  %76 = load i64, i64* %75, align 8, !dbg !2509
  %77 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %74, i32 0, i32 1, !dbg !2509
  %78 = load i64, i64* %77, align 8, !dbg !2509
  %call30 = call double @curlx_tvdiff_secs(i64 %71, i64 %73, i64 %76, i64 %78), !dbg !2509
  %79 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2510
  %progress31 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %79, i32 0, i32 16, !dbg !2511
  %t_starttransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %progress31, i32 0, i32 16, !dbg !2512
  store double %call30, double* %t_starttransfer, align 8, !dbg !2513
  br label %sw.epilog, !dbg !2514

sw.bb32:                                          ; preds = %entry
  br label %sw.epilog, !dbg !2515

sw.bb33:                                          ; preds = %entry
  %80 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2516
  %progress34 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %80, i32 0, i32 16, !dbg !2516
  %start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress34, i32 0, i32 18, !dbg !2516
  %81 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2516
  %82 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %81, i32 0, i32 0, !dbg !2516
  %83 = load i64, i64* %82, align 8, !dbg !2516
  %84 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %81, i32 0, i32 1, !dbg !2516
  %85 = load i64, i64* %84, align 8, !dbg !2516
  %86 = bitcast %struct.timeval* %start to { i64, i64 }*, !dbg !2516
  %87 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %86, i32 0, i32 0, !dbg !2516
  %88 = load i64, i64* %87, align 8, !dbg !2516
  %89 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %86, i32 0, i32 1, !dbg !2516
  %90 = load i64, i64* %89, align 8, !dbg !2516
  %call35 = call double @curlx_tvdiff_secs(i64 %83, i64 %85, i64 %88, i64 %90), !dbg !2516
  %91 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2517
  %progress36 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %91, i32 0, i32 16, !dbg !2518
  %t_redirect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress36, i32 0, i32 17, !dbg !2519
  store double %call35, double* %t_redirect, align 8, !dbg !2520
  br label %sw.epilog, !dbg !2521

sw.epilog:                                        ; preds = %sw.bb33, %sw.bb32, %sw.bb27, %sw.bb22, %sw.bb17, %sw.bb12, %sw.bb7, %sw.bb4, %sw.bb2, %sw.bb1, %sw.bb
  ret void, !dbg !2522
}

declare { i64, i64 } @curlx_tvnow() #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare double @curlx_tvdiff_secs(i64, i64, i64, i64) #2

; Function Attrs: nounwind uwtable
define void @Curl_pgrsStartNow(%struct.Curl_easy* %data) #0 !dbg !1706 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2523, metadata !1727), !dbg !2524
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2525
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 16, !dbg !2526
  %speeder_c = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 28, !dbg !2527
  store i32 0, i32* %speeder_c, align 8, !dbg !2528
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2529
  %progress1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 16, !dbg !2530
  %start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress1, i32 0, i32 18, !dbg !2531
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2532
  %2 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2532
  %3 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %2, i32 0, i32 0, !dbg !2532
  %4 = extractvalue { i64, i64 } %call, 0, !dbg !2532
  store i64 %4, i64* %3, align 8, !dbg !2532
  %5 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %2, i32 0, i32 1, !dbg !2532
  %6 = extractvalue { i64, i64 } %call, 1, !dbg !2532
  store i64 %6, i64* %5, align 8, !dbg !2532
  %7 = bitcast %struct.timeval* %start to i8*, !dbg !2532
  %8 = bitcast %struct.timeval* %coerce to i8*, !dbg !2532
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 16, i32 8, i1 false), !dbg !2533
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2535
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 16, !dbg !2536
  %ul_limit_start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 22, !dbg !2537
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %ul_limit_start, i32 0, i32 0, !dbg !2538
  store i64 0, i64* %tv_sec, align 8, !dbg !2539
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2540
  %progress3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 16, !dbg !2541
  %ul_limit_start4 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress3, i32 0, i32 22, !dbg !2542
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %ul_limit_start4, i32 0, i32 1, !dbg !2543
  store i64 0, i64* %tv_usec, align 8, !dbg !2544
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2545
  %progress5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 16, !dbg !2546
  %dl_limit_start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress5, i32 0, i32 24, !dbg !2547
  %tv_sec6 = getelementptr inbounds %struct.timeval, %struct.timeval* %dl_limit_start, i32 0, i32 0, !dbg !2548
  store i64 0, i64* %tv_sec6, align 8, !dbg !2549
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2550
  %progress7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 16, !dbg !2551
  %dl_limit_start8 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress7, i32 0, i32 24, !dbg !2552
  %tv_usec9 = getelementptr inbounds %struct.timeval, %struct.timeval* %dl_limit_start8, i32 0, i32 1, !dbg !2553
  store i64 0, i64* %tv_usec9, align 8, !dbg !2554
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2555
  %progress10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 16, !dbg !2556
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress10, i32 0, i32 8, !dbg !2557
  %14 = load i32, i32* %flags, align 8, !dbg !2558
  %and = and i32 %14, 144, !dbg !2558
  store i32 %and, i32* %flags, align 8, !dbg !2558
  ret void, !dbg !2559
}

; Function Attrs: nounwind uwtable
define i64 @Curl_pgrsLimitWaitTime(i64 %cursize, i64 %startsize, i64 %limit, i64 %start.coerce0, i64 %start.coerce1, %struct.timeval* byval align 8 %now) #0 !dbg !1707 {
entry:
  %retval = alloca i64, align 8
  %start = alloca %struct.timeval, align 8
  %cursize.addr = alloca i64, align 8
  %startsize.addr = alloca i64, align 8
  %limit.addr = alloca i64, align 8
  %size = alloca i64, align 8
  %minimum = alloca i64, align 8
  %actual = alloca i64, align 8
  %0 = bitcast %struct.timeval* %start to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %start.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %start.coerce1, i64* %2, align 8
  store i64 %cursize, i64* %cursize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %cursize.addr, metadata !2560, metadata !1727), !dbg !2561
  store i64 %startsize, i64* %startsize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %startsize.addr, metadata !2562, metadata !1727), !dbg !2563
  store i64 %limit, i64* %limit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %limit.addr, metadata !2564, metadata !1727), !dbg !2565
  call void @llvm.dbg.declare(metadata %struct.timeval* %start, metadata !2566, metadata !1727), !dbg !2567
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !2568, metadata !1727), !dbg !2569
  call void @llvm.dbg.declare(metadata i64* %size, metadata !2570, metadata !1727), !dbg !2571
  %3 = load i64, i64* %cursize.addr, align 8, !dbg !2572
  %4 = load i64, i64* %startsize.addr, align 8, !dbg !2573
  %sub = sub nsw i64 %3, %4, !dbg !2574
  store i64 %sub, i64* %size, align 8, !dbg !2571
  call void @llvm.dbg.declare(metadata i64* %minimum, metadata !2575, metadata !1727), !dbg !2576
  call void @llvm.dbg.declare(metadata i64* %actual, metadata !2577, metadata !1727), !dbg !2578
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %start, i32 0, i32 0, !dbg !2579
  %5 = load i64, i64* %tv_sec, align 8, !dbg !2579
  %cmp = icmp eq i64 %5, 0, !dbg !2581
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2582

land.lhs.true:                                    ; preds = %entry
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %start, i32 0, i32 1, !dbg !2583
  %6 = load i64, i64* %tv_usec, align 8, !dbg !2583
  %cmp1 = icmp eq i64 %6, 0, !dbg !2585
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2586

if.then:                                          ; preds = %land.lhs.true
  store i64 0, i64* %retval, align 8, !dbg !2587
  br label %return, !dbg !2587

if.end:                                           ; preds = %land.lhs.true, %entry
  %7 = load i64, i64* %size, align 8, !dbg !2588
  %8 = load i64, i64* %limit.addr, align 8, !dbg !2590
  %cmp2 = icmp slt i64 %7, %8, !dbg !2591
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2592

if.then3:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !2593
  br label %return, !dbg !2593

if.end4:                                          ; preds = %if.end
  %9 = load i64, i64* %size, align 8, !dbg !2594
  %mul = mul nsw i64 1000, %9, !dbg !2595
  %10 = load i64, i64* %limit.addr, align 8, !dbg !2596
  %div = sdiv i64 %mul, %10, !dbg !2597
  store i64 %div, i64* %minimum, align 8, !dbg !2598
  %11 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2599
  %12 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %11, i32 0, i32 0, !dbg !2599
  %13 = load i64, i64* %12, align 8, !dbg !2599
  %14 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %11, i32 0, i32 1, !dbg !2599
  %15 = load i64, i64* %14, align 8, !dbg !2599
  %16 = bitcast %struct.timeval* %start to { i64, i64 }*, !dbg !2599
  %17 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %16, i32 0, i32 0, !dbg !2599
  %18 = load i64, i64* %17, align 8, !dbg !2599
  %19 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %16, i32 0, i32 1, !dbg !2599
  %20 = load i64, i64* %19, align 8, !dbg !2599
  %call = call i64 @curlx_tvdiff(i64 %13, i64 %15, i64 %18, i64 %20), !dbg !2599
  store i64 %call, i64* %actual, align 8, !dbg !2600
  %21 = load i64, i64* %actual, align 8, !dbg !2601
  %22 = load i64, i64* %minimum, align 8, !dbg !2603
  %cmp5 = icmp slt i64 %21, %22, !dbg !2604
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !2605

if.then6:                                         ; preds = %if.end4
  %23 = load i64, i64* %minimum, align 8, !dbg !2606
  %24 = load i64, i64* %actual, align 8, !dbg !2607
  %sub7 = sub nsw i64 %23, %24, !dbg !2608
  store i64 %sub7, i64* %retval, align 8, !dbg !2609
  br label %return, !dbg !2609

if.end8:                                          ; preds = %if.end4
  store i64 0, i64* %retval, align 8, !dbg !2610
  br label %return, !dbg !2610

return:                                           ; preds = %if.end8, %if.then6, %if.then3, %if.then
  %25 = load i64, i64* %retval, align 8, !dbg !2611
  ret i64 %25, !dbg !2611
}

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #2

; Function Attrs: nounwind uwtable
define void @Curl_pgrsSetDownloadCounter(%struct.Curl_easy* %data, i64 %size) #0 !dbg !1710 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %size.addr = alloca i64, align 8
  %now = alloca %struct.timeval, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2612, metadata !1727), !dbg !2613
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2614, metadata !1727), !dbg !2615
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !2616, metadata !1727), !dbg !2617
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2618
  %0 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2618
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0, !dbg !2618
  %2 = extractvalue { i64, i64 } %call, 0, !dbg !2618
  store i64 %2, i64* %1, align 8, !dbg !2618
  %3 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1, !dbg !2618
  %4 = extractvalue { i64, i64 } %call, 1, !dbg !2618
  store i64 %4, i64* %3, align 8, !dbg !2618
  %5 = load i64, i64* %size.addr, align 8, !dbg !2619
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2620
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 16, !dbg !2621
  %downloaded = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 3, !dbg !2622
  store i64 %5, i64* %downloaded, align 8, !dbg !2623
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2624
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 13, !dbg !2626
  %max_recv_speed = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 52, !dbg !2627
  %8 = load i64, i64* %max_recv_speed, align 8, !dbg !2627
  %cmp = icmp sgt i64 %8, 0, !dbg !2628
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2629

land.lhs.true:                                    ; preds = %entry
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2630
  %progress1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 16, !dbg !2631
  %downloaded2 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress1, i32 0, i32 3, !dbg !2632
  %10 = load i64, i64* %downloaded2, align 8, !dbg !2632
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2633
  %progress3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 16, !dbg !2634
  %dl_limit_size = getelementptr inbounds %struct.Progress, %struct.Progress* %progress3, i32 0, i32 25, !dbg !2635
  %12 = load i64, i64* %dl_limit_size, align 8, !dbg !2635
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2636
  %set4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !2637
  %max_recv_speed5 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set4, i32 0, i32 52, !dbg !2638
  %14 = load i64, i64* %max_recv_speed5, align 8, !dbg !2638
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2639
  %progress6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 16, !dbg !2640
  %dl_limit_start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress6, i32 0, i32 24, !dbg !2641
  %16 = bitcast %struct.timeval* %dl_limit_start to { i64, i64 }*, !dbg !2642
  %17 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %16, i32 0, i32 0, !dbg !2642
  %18 = load i64, i64* %17, align 8, !dbg !2642
  %19 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %16, i32 0, i32 1, !dbg !2642
  %20 = load i64, i64* %19, align 8, !dbg !2642
  %call7 = call i64 @Curl_pgrsLimitWaitTime(i64 %10, i64 %12, i64 %14, i64 %18, i64 %20, %struct.timeval* byval align 8 %now), !dbg !2642
  %cmp8 = icmp eq i64 %call7, 0, !dbg !2643
  br i1 %cmp8, label %if.then, label %if.end, !dbg !2644

if.then:                                          ; preds = %land.lhs.true
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2646
  %progress9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 16, !dbg !2648
  %dl_limit_start10 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress9, i32 0, i32 24, !dbg !2649
  %22 = bitcast %struct.timeval* %dl_limit_start10 to i8*, !dbg !2650
  %23 = bitcast %struct.timeval* %now to i8*, !dbg !2650
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %22, i8* %23, i64 16, i32 8, i1 false), !dbg !2650
  %24 = load i64, i64* %size.addr, align 8, !dbg !2651
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2652
  %progress11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 16, !dbg !2653
  %dl_limit_size12 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress11, i32 0, i32 25, !dbg !2654
  store i64 %24, i64* %dl_limit_size12, align 8, !dbg !2655
  br label %if.end, !dbg !2656

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret void, !dbg !2657
}

; Function Attrs: nounwind uwtable
define void @Curl_pgrsSetUploadCounter(%struct.Curl_easy* %data, i64 %size) #0 !dbg !1713 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %size.addr = alloca i64, align 8
  %now = alloca %struct.timeval, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2658, metadata !1727), !dbg !2659
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2660, metadata !1727), !dbg !2661
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !2662, metadata !1727), !dbg !2663
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2664
  %0 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2664
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0, !dbg !2664
  %2 = extractvalue { i64, i64 } %call, 0, !dbg !2664
  store i64 %2, i64* %1, align 8, !dbg !2664
  %3 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1, !dbg !2664
  %4 = extractvalue { i64, i64 } %call, 1, !dbg !2664
  store i64 %4, i64* %3, align 8, !dbg !2664
  %5 = load i64, i64* %size.addr, align 8, !dbg !2665
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2666
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 16, !dbg !2667
  %uploaded = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 4, !dbg !2668
  store i64 %5, i64* %uploaded, align 8, !dbg !2669
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2670
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 13, !dbg !2672
  %max_send_speed = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 51, !dbg !2673
  %8 = load i64, i64* %max_send_speed, align 8, !dbg !2673
  %cmp = icmp sgt i64 %8, 0, !dbg !2674
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2675

land.lhs.true:                                    ; preds = %entry
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2676
  %progress1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 16, !dbg !2677
  %uploaded2 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress1, i32 0, i32 4, !dbg !2678
  %10 = load i64, i64* %uploaded2, align 8, !dbg !2678
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2679
  %progress3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 16, !dbg !2680
  %ul_limit_size = getelementptr inbounds %struct.Progress, %struct.Progress* %progress3, i32 0, i32 23, !dbg !2681
  %12 = load i64, i64* %ul_limit_size, align 8, !dbg !2681
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2682
  %set4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !2683
  %max_send_speed5 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set4, i32 0, i32 51, !dbg !2684
  %14 = load i64, i64* %max_send_speed5, align 8, !dbg !2684
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2685
  %progress6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 16, !dbg !2686
  %ul_limit_start = getelementptr inbounds %struct.Progress, %struct.Progress* %progress6, i32 0, i32 22, !dbg !2687
  %16 = bitcast %struct.timeval* %ul_limit_start to { i64, i64 }*, !dbg !2688
  %17 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %16, i32 0, i32 0, !dbg !2688
  %18 = load i64, i64* %17, align 8, !dbg !2688
  %19 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %16, i32 0, i32 1, !dbg !2688
  %20 = load i64, i64* %19, align 8, !dbg !2688
  %call7 = call i64 @Curl_pgrsLimitWaitTime(i64 %10, i64 %12, i64 %14, i64 %18, i64 %20, %struct.timeval* byval align 8 %now), !dbg !2688
  %cmp8 = icmp eq i64 %call7, 0, !dbg !2689
  br i1 %cmp8, label %if.then, label %if.end, !dbg !2690

if.then:                                          ; preds = %land.lhs.true
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2692
  %progress9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 16, !dbg !2694
  %ul_limit_start10 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress9, i32 0, i32 22, !dbg !2695
  %22 = bitcast %struct.timeval* %ul_limit_start10 to i8*, !dbg !2696
  %23 = bitcast %struct.timeval* %now to i8*, !dbg !2696
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %22, i8* %23, i64 16, i32 8, i1 false), !dbg !2696
  %24 = load i64, i64* %size.addr, align 8, !dbg !2697
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2698
  %progress11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 16, !dbg !2699
  %ul_limit_size12 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress11, i32 0, i32 23, !dbg !2700
  store i64 %24, i64* %ul_limit_size12, align 8, !dbg !2701
  br label %if.end, !dbg !2702

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret void, !dbg !2703
}

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal void @time2str(i8* %r, i64 %seconds) #0 !dbg !1717 {
entry:
  %r.addr = alloca i8*, align 8
  %seconds.addr = alloca i64, align 8
  %d = alloca i64, align 8
  %h = alloca i64, align 8
  %m = alloca i64, align 8
  %s = alloca i64, align 8
  store i8* %r, i8** %r.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %r.addr, metadata !2704, metadata !1727), !dbg !2705
  store i64 %seconds, i64* %seconds.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %seconds.addr, metadata !2706, metadata !1727), !dbg !2707
  call void @llvm.dbg.declare(metadata i64* %d, metadata !2708, metadata !1727), !dbg !2709
  call void @llvm.dbg.declare(metadata i64* %h, metadata !2710, metadata !1727), !dbg !2711
  call void @llvm.dbg.declare(metadata i64* %m, metadata !2712, metadata !1727), !dbg !2713
  call void @llvm.dbg.declare(metadata i64* %s, metadata !2714, metadata !1727), !dbg !2715
  %0 = load i64, i64* %seconds.addr, align 8, !dbg !2716
  %cmp = icmp sle i64 %0, 0, !dbg !2718
  br i1 %cmp, label %if.then, label %if.end, !dbg !2719

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %r.addr, align 8, !dbg !2720
  %call = call i8* @strcpy(i8* %1, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.5, i32 0, i32 0)) #5, !dbg !2722
  br label %if.end19, !dbg !2723

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %seconds.addr, align 8, !dbg !2724
  %div = sdiv i64 %2, 3600, !dbg !2725
  store i64 %div, i64* %h, align 8, !dbg !2726
  %3 = load i64, i64* %h, align 8, !dbg !2727
  %cmp1 = icmp sle i64 %3, 99, !dbg !2729
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !2730

if.then2:                                         ; preds = %if.end
  %4 = load i64, i64* %seconds.addr, align 8, !dbg !2731
  %5 = load i64, i64* %h, align 8, !dbg !2733
  %mul = mul nsw i64 %5, 3600, !dbg !2734
  %sub = sub nsw i64 %4, %mul, !dbg !2735
  %div3 = sdiv i64 %sub, 60, !dbg !2736
  store i64 %div3, i64* %m, align 8, !dbg !2737
  %6 = load i64, i64* %seconds.addr, align 8, !dbg !2738
  %7 = load i64, i64* %h, align 8, !dbg !2739
  %mul4 = mul nsw i64 %7, 3600, !dbg !2740
  %sub5 = sub nsw i64 %6, %mul4, !dbg !2741
  %8 = load i64, i64* %m, align 8, !dbg !2742
  %mul6 = mul nsw i64 %8, 60, !dbg !2743
  %sub7 = sub nsw i64 %sub5, %mul6, !dbg !2744
  store i64 %sub7, i64* %s, align 8, !dbg !2745
  %9 = load i8*, i8** %r.addr, align 8, !dbg !2746
  %10 = load i64, i64* %h, align 8, !dbg !2747
  %11 = load i64, i64* %m, align 8, !dbg !2748
  %12 = load i64, i64* %s, align 8, !dbg !2749
  %call8 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %9, i64 9, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.6, i32 0, i32 0), i64 %10, i64 %11, i64 %12), !dbg !2750
  br label %if.end19, !dbg !2751

if.else:                                          ; preds = %if.end
  %13 = load i64, i64* %seconds.addr, align 8, !dbg !2752
  %div9 = sdiv i64 %13, 86400, !dbg !2754
  store i64 %div9, i64* %d, align 8, !dbg !2755
  %14 = load i64, i64* %seconds.addr, align 8, !dbg !2756
  %15 = load i64, i64* %d, align 8, !dbg !2757
  %mul10 = mul nsw i64 %15, 86400, !dbg !2758
  %sub11 = sub nsw i64 %14, %mul10, !dbg !2759
  %div12 = sdiv i64 %sub11, 3600, !dbg !2760
  store i64 %div12, i64* %h, align 8, !dbg !2761
  %16 = load i64, i64* %d, align 8, !dbg !2762
  %cmp13 = icmp sle i64 %16, 999, !dbg !2764
  br i1 %cmp13, label %if.then14, label %if.else16, !dbg !2765

if.then14:                                        ; preds = %if.else
  %17 = load i8*, i8** %r.addr, align 8, !dbg !2766
  %18 = load i64, i64* %d, align 8, !dbg !2767
  %19 = load i64, i64* %h, align 8, !dbg !2768
  %call15 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %17, i64 9, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.7, i32 0, i32 0), i64 %18, i64 %19), !dbg !2769
  br label %if.end18, !dbg !2769

if.else16:                                        ; preds = %if.else
  %20 = load i8*, i8** %r.addr, align 8, !dbg !2770
  %21 = load i64, i64* %d, align 8, !dbg !2771
  %call17 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %20, i64 9, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.8, i32 0, i32 0), i64 %21), !dbg !2772
  br label %if.end18

if.end18:                                         ; preds = %if.else16, %if.then14
  br label %if.end19

if.end19:                                         ; preds = %if.then, %if.end18, %if.then2
  ret void, !dbg !2773
}

; Function Attrs: nounwind uwtable
define internal i8* @max5data(i64 %bytes, i8* %max5) #0 !dbg !1720 {
entry:
  %bytes.addr = alloca i64, align 8
  %max5.addr = alloca i8*, align 8
  store i64 %bytes, i64* %bytes.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bytes.addr, metadata !2774, metadata !1727), !dbg !2775
  store i8* %max5, i8** %max5.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %max5.addr, metadata !2776, metadata !1727), !dbg !2777
  %0 = load i64, i64* %bytes.addr, align 8, !dbg !2778
  %cmp = icmp slt i64 %0, 100000, !dbg !2780
  br i1 %cmp, label %if.then, label %if.else, !dbg !2781

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %max5.addr, align 8, !dbg !2782
  %2 = load i64, i64* %bytes.addr, align 8, !dbg !2783
  %call = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %1, i64 6, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0), i64 %2), !dbg !2784
  br label %if.end40, !dbg !2784

if.else:                                          ; preds = %entry
  %3 = load i64, i64* %bytes.addr, align 8, !dbg !2785
  %cmp1 = icmp slt i64 %3, 10240000, !dbg !2787
  br i1 %cmp1, label %if.then2, label %if.else4, !dbg !2788

if.then2:                                         ; preds = %if.else
  %4 = load i8*, i8** %max5.addr, align 8, !dbg !2789
  %5 = load i64, i64* %bytes.addr, align 8, !dbg !2790
  %div = sdiv i64 %5, 1024, !dbg !2791
  %call3 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %4, i64 6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0), i64 %div), !dbg !2792
  br label %if.end39, !dbg !2792

if.else4:                                         ; preds = %if.else
  %6 = load i64, i64* %bytes.addr, align 8, !dbg !2793
  %cmp5 = icmp slt i64 %6, 104857600, !dbg !2795
  br i1 %cmp5, label %if.then6, label %if.else10, !dbg !2796

if.then6:                                         ; preds = %if.else4
  %7 = load i8*, i8** %max5.addr, align 8, !dbg !2797
  %8 = load i64, i64* %bytes.addr, align 8, !dbg !2798
  %div7 = sdiv i64 %8, 1048576, !dbg !2799
  %9 = load i64, i64* %bytes.addr, align 8, !dbg !2800
  %rem = srem i64 %9, 1048576, !dbg !2801
  %div8 = sdiv i64 %rem, 104857, !dbg !2802
  %call9 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %7, i64 6, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.11, i32 0, i32 0), i64 %div7, i64 %div8), !dbg !2803
  br label %if.end38, !dbg !2803

if.else10:                                        ; preds = %if.else4
  %10 = load i64, i64* %bytes.addr, align 8, !dbg !2804
  %cmp11 = icmp slt i64 %10, 10485760000, !dbg !2806
  br i1 %cmp11, label %if.then12, label %if.else15, !dbg !2807

if.then12:                                        ; preds = %if.else10
  %11 = load i8*, i8** %max5.addr, align 8, !dbg !2808
  %12 = load i64, i64* %bytes.addr, align 8, !dbg !2809
  %div13 = sdiv i64 %12, 1048576, !dbg !2810
  %call14 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %11, i64 6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0), i64 %div13), !dbg !2811
  br label %if.end37, !dbg !2811

if.else15:                                        ; preds = %if.else10
  %13 = load i64, i64* %bytes.addr, align 8, !dbg !2812
  %cmp16 = icmp slt i64 %13, 107374182400, !dbg !2814
  br i1 %cmp16, label %if.then17, label %if.else22, !dbg !2815

if.then17:                                        ; preds = %if.else15
  %14 = load i8*, i8** %max5.addr, align 8, !dbg !2816
  %15 = load i64, i64* %bytes.addr, align 8, !dbg !2817
  %div18 = sdiv i64 %15, 1073741824, !dbg !2818
  %16 = load i64, i64* %bytes.addr, align 8, !dbg !2819
  %rem19 = srem i64 %16, 1073741824, !dbg !2820
  %div20 = sdiv i64 %rem19, 107374182, !dbg !2821
  %call21 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %14, i64 6, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.13, i32 0, i32 0), i64 %div18, i64 %div20), !dbg !2822
  br label %if.end36, !dbg !2822

if.else22:                                        ; preds = %if.else15
  %17 = load i64, i64* %bytes.addr, align 8, !dbg !2823
  %cmp23 = icmp slt i64 %17, 10737418240000, !dbg !2825
  br i1 %cmp23, label %if.then24, label %if.else27, !dbg !2826

if.then24:                                        ; preds = %if.else22
  %18 = load i8*, i8** %max5.addr, align 8, !dbg !2827
  %19 = load i64, i64* %bytes.addr, align 8, !dbg !2828
  %div25 = sdiv i64 %19, 1073741824, !dbg !2829
  %call26 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %18, i64 6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.14, i32 0, i32 0), i64 %div25), !dbg !2830
  br label %if.end35, !dbg !2830

if.else27:                                        ; preds = %if.else22
  %20 = load i64, i64* %bytes.addr, align 8, !dbg !2831
  %cmp28 = icmp slt i64 %20, 10995116277760000, !dbg !2833
  br i1 %cmp28, label %if.then29, label %if.else32, !dbg !2834

if.then29:                                        ; preds = %if.else27
  %21 = load i8*, i8** %max5.addr, align 8, !dbg !2835
  %22 = load i64, i64* %bytes.addr, align 8, !dbg !2836
  %div30 = sdiv i64 %22, 1099511627776, !dbg !2837
  %call31 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %21, i64 6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i32 0, i32 0), i64 %div30), !dbg !2838
  br label %if.end, !dbg !2838

if.else32:                                        ; preds = %if.else27
  %23 = load i8*, i8** %max5.addr, align 8, !dbg !2839
  %24 = load i64, i64* %bytes.addr, align 8, !dbg !2840
  %div33 = sdiv i64 %24, 1125899906842624, !dbg !2841
  %call34 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %23, i64 6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.16, i32 0, i32 0), i64 %div33), !dbg !2842
  br label %if.end

if.end:                                           ; preds = %if.else32, %if.then29
  br label %if.end35

if.end35:                                         ; preds = %if.end, %if.then24
  br label %if.end36

if.end36:                                         ; preds = %if.end35, %if.then17
  br label %if.end37

if.end37:                                         ; preds = %if.end36, %if.then12
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.then6
  br label %if.end39

if.end39:                                         ; preds = %if.end38, %if.then2
  br label %if.end40

if.end40:                                         ; preds = %if.end39, %if.then
  %25 = load i8*, i8** %max5.addr, align 8, !dbg !2843
  ret i8* %25, !dbg !2844
}

declare i32 @fflush(%struct._IO_FILE*) #2

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #4

declare i32 @curl_msnprintf(i8*, i64, i8*, ...) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1723, !1724}
!llvm.ident = !{!1725}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1693, subprograms: !1694)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/progress.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !26, !123, !129, !185, !227, !234, !269, !279, !285, !290, !297, !307, !316, !322, !328, !334, !340, !347, !353, !359, !374, !385, !399, !410, !415, !423, !461, !480, !500, !515, !532, !540, !1678}
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
!1678 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1679, line: 28, size: 32, align: 32, elements: !1680)
!1679 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/progress.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1680 = !{!1681, !1682, !1683, !1684, !1685, !1686, !1687, !1688, !1689, !1690, !1691, !1692}
!1681 = !DIEnumerator(name: "TIMER_NONE", value: 0)
!1682 = !DIEnumerator(name: "TIMER_STARTOP", value: 1)
!1683 = !DIEnumerator(name: "TIMER_STARTSINGLE", value: 2)
!1684 = !DIEnumerator(name: "TIMER_NAMELOOKUP", value: 3)
!1685 = !DIEnumerator(name: "TIMER_CONNECT", value: 4)
!1686 = !DIEnumerator(name: "TIMER_APPCONNECT", value: 5)
!1687 = !DIEnumerator(name: "TIMER_PRETRANSFER", value: 6)
!1688 = !DIEnumerator(name: "TIMER_STARTTRANSFER", value: 7)
!1689 = !DIEnumerator(name: "TIMER_POSTRANSFER", value: 8)
!1690 = !DIEnumerator(name: "TIMER_STARTACCEPT", value: 9)
!1691 = !DIEnumerator(name: "TIMER_REDIRECT", value: 10)
!1692 = !DIEnumerator(name: "TIMER_LAST", value: 11)
!1693 = !{!242, !191, !189, !745}
!1694 = !{!1695, !1699, !1702, !1706, !1707, !1710, !1713, !1714, !1715, !1716, !1717, !1720}
!1695 = distinct !DISubprogram(name: "Curl_pgrsDone", scope: !1, file: !1, line: 133, type: !1696, isLocal: false, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1696 = !DISubroutineType(types: !1697)
!1697 = !{!177, !550}
!1698 = !{}
!1699 = distinct !DISubprogram(name: "Curl_pgrsResetTimesSizes", scope: !1, file: !1, line: 153, type: !1700, isLocal: false, isDefinition: true, scopeLine: 154, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1700 = !DISubroutineType(types: !1701)
!1701 = !{null, !544}
!1702 = distinct !DISubprogram(name: "Curl_pgrsTime", scope: !1, file: !1, line: 164, type: !1703, isLocal: false, isDefinition: true, scopeLine: 165, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1703 = !DISubroutineType(types: !1704)
!1704 = !{null, !544, !1705}
!1705 = !DIDerivedType(tag: DW_TAG_typedef, name: "timerid", file: !1679, line: 41, baseType: !1678)
!1706 = distinct !DISubprogram(name: "Curl_pgrsStartNow", scope: !1, file: !1, line: 215, type: !1700, isLocal: false, isDefinition: true, scopeLine: 216, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1707 = distinct !DISubprogram(name: "Curl_pgrsLimitWaitTime", scope: !1, file: !1, line: 246, type: !1708, isLocal: false, isDefinition: true, scopeLine: 251, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1708 = !DISubroutineType(types: !1709)
!1709 = !{!191, !189, !189, !189, !201, !201}
!1710 = distinct !DISubprogram(name: "Curl_pgrsSetDownloadCounter", scope: !1, file: !1, line: 274, type: !1711, isLocal: false, isDefinition: true, scopeLine: 275, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1711 = !DISubroutineType(types: !1712)
!1712 = !{null, !544, !189}
!1713 = distinct !DISubprogram(name: "Curl_pgrsSetUploadCounter", scope: !1, file: !1, line: 292, type: !1711, isLocal: false, isDefinition: true, scopeLine: 293, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1714 = distinct !DISubprogram(name: "Curl_pgrsSetDownloadSize", scope: !1, file: !1, line: 310, type: !1711, isLocal: false, isDefinition: true, scopeLine: 311, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1715 = distinct !DISubprogram(name: "Curl_pgrsSetUploadSize", scope: !1, file: !1, line: 322, type: !1711, isLocal: false, isDefinition: true, scopeLine: 323, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1716 = distinct !DISubprogram(name: "Curl_pgrsUpdate", scope: !1, file: !1, line: 338, type: !1696, isLocal: false, isDefinition: true, scopeLine: 339, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1717 = distinct !DISubprogram(name: "time2str", scope: !1, file: !1, line: 32, type: !1718, isLocal: true, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1718 = !DISubroutineType(types: !1719)
!1719 = !{null, !215, !189}
!1720 = distinct !DISubprogram(name: "max5data", scope: !1, file: !1, line: 62, type: !1721, isLocal: true, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !1698)
!1721 = !DISubroutineType(types: !1722)
!1722 = !{!215, !189, !215}
!1723 = !{i32 2, !"Dwarf Version", i32 4}
!1724 = !{i32 2, !"Debug Info Version", i32 3}
!1725 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1726 = !DILocalVariable(name: "conn", arg: 1, scope: !1695, file: !1, line: 133, type: !550)
!1727 = !DIExpression()
!1728 = !DILocation(line: 133, column: 39, scope: !1695)
!1729 = !DILocalVariable(name: "rc", scope: !1695, file: !1, line: 135, type: !177)
!1730 = !DILocation(line: 135, column: 7, scope: !1695)
!1731 = !DILocalVariable(name: "data", scope: !1695, file: !1, line: 136, type: !544)
!1732 = !DILocation(line: 136, column: 21, scope: !1695)
!1733 = !DILocation(line: 136, column: 28, scope: !1695)
!1734 = !DILocation(line: 136, column: 34, scope: !1695)
!1735 = !DILocation(line: 137, column: 3, scope: !1695)
!1736 = !DILocation(line: 137, column: 9, scope: !1695)
!1737 = !DILocation(line: 137, column: 18, scope: !1695)
!1738 = !DILocation(line: 137, column: 26, scope: !1695)
!1739 = !DILocation(line: 138, column: 24, scope: !1695)
!1740 = !DILocation(line: 138, column: 8, scope: !1695)
!1741 = !DILocation(line: 138, column: 6, scope: !1695)
!1742 = !DILocation(line: 139, column: 6, scope: !1743)
!1743 = distinct !DILexicalBlock(scope: !1695, file: !1, line: 139, column: 6)
!1744 = !DILocation(line: 139, column: 6, scope: !1695)
!1745 = !DILocation(line: 140, column: 12, scope: !1743)
!1746 = !DILocation(line: 140, column: 5, scope: !1743)
!1747 = !DILocation(line: 142, column: 8, scope: !1748)
!1748 = distinct !DILexicalBlock(scope: !1695, file: !1, line: 142, column: 6)
!1749 = !DILocation(line: 142, column: 14, scope: !1748)
!1750 = !DILocation(line: 142, column: 23, scope: !1748)
!1751 = !DILocation(line: 142, column: 29, scope: !1748)
!1752 = !DILocation(line: 142, column: 42, scope: !1748)
!1753 = !DILocation(line: 143, column: 7, scope: !1748)
!1754 = !DILocation(line: 143, column: 13, scope: !1748)
!1755 = !DILocation(line: 143, column: 22, scope: !1748)
!1756 = !DILocation(line: 142, column: 6, scope: !1757)
!1757 = !DILexicalBlockFile(scope: !1695, file: !1, discriminator: 1)
!1758 = !DILocation(line: 146, column: 13, scope: !1748)
!1759 = !DILocation(line: 146, column: 19, scope: !1748)
!1760 = !DILocation(line: 146, column: 23, scope: !1748)
!1761 = !DILocation(line: 146, column: 5, scope: !1748)
!1762 = !DILocation(line: 148, column: 3, scope: !1695)
!1763 = !DILocation(line: 148, column: 9, scope: !1695)
!1764 = !DILocation(line: 148, column: 18, scope: !1695)
!1765 = !DILocation(line: 148, column: 28, scope: !1695)
!1766 = !DILocation(line: 149, column: 3, scope: !1695)
!1767 = !DILocation(line: 150, column: 1, scope: !1695)
!1768 = !DILocalVariable(name: "conn", arg: 1, scope: !1716, file: !1, line: 338, type: !550)
!1769 = !DILocation(line: 338, column: 41, scope: !1716)
!1770 = !DILocalVariable(name: "now", scope: !1716, file: !1, line: 340, type: !201)
!1771 = !DILocation(line: 340, column: 18, scope: !1716)
!1772 = !DILocalVariable(name: "result", scope: !1716, file: !1, line: 341, type: !177)
!1773 = !DILocation(line: 341, column: 7, scope: !1716)
!1774 = !DILocalVariable(name: "max5", scope: !1716, file: !1, line: 342, type: !1775)
!1775 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 480, align: 8, elements: !1776)
!1776 = !{!1098, !1777}
!1777 = !DISubrange(count: 10)
!1778 = !DILocation(line: 342, column: 8, scope: !1716)
!1779 = !DILocalVariable(name: "dlpercen", scope: !1716, file: !1, line: 343, type: !189)
!1780 = !DILocation(line: 343, column: 14, scope: !1716)
!1781 = !DILocalVariable(name: "ulpercen", scope: !1716, file: !1, line: 344, type: !189)
!1782 = !DILocation(line: 344, column: 14, scope: !1716)
!1783 = !DILocalVariable(name: "total_percen", scope: !1716, file: !1, line: 345, type: !189)
!1784 = !DILocation(line: 345, column: 14, scope: !1716)
!1785 = !DILocalVariable(name: "total_transfer", scope: !1716, file: !1, line: 346, type: !189)
!1786 = !DILocation(line: 346, column: 14, scope: !1716)
!1787 = !DILocalVariable(name: "total_expected_transfer", scope: !1716, file: !1, line: 347, type: !189)
!1788 = !DILocation(line: 347, column: 14, scope: !1716)
!1789 = !DILocalVariable(name: "timespent", scope: !1716, file: !1, line: 348, type: !189)
!1790 = !DILocation(line: 348, column: 14, scope: !1716)
!1791 = !DILocalVariable(name: "data", scope: !1716, file: !1, line: 349, type: !544)
!1792 = !DILocation(line: 349, column: 21, scope: !1716)
!1793 = !DILocation(line: 349, column: 28, scope: !1716)
!1794 = !DILocation(line: 349, column: 34, scope: !1716)
!1795 = !DILocalVariable(name: "nowindex", scope: !1716, file: !1, line: 350, type: !177)
!1796 = !DILocation(line: 350, column: 7, scope: !1716)
!1797 = !DILocation(line: 350, column: 18, scope: !1716)
!1798 = !DILocation(line: 350, column: 24, scope: !1716)
!1799 = !DILocation(line: 350, column: 33, scope: !1716)
!1800 = !DILocation(line: 350, column: 42, scope: !1716)
!1801 = !DILocalVariable(name: "checkindex", scope: !1716, file: !1, line: 351, type: !177)
!1802 = !DILocation(line: 351, column: 7, scope: !1716)
!1803 = !DILocalVariable(name: "countindex", scope: !1716, file: !1, line: 352, type: !177)
!1804 = !DILocation(line: 352, column: 7, scope: !1716)
!1805 = !DILocalVariable(name: "time_left", scope: !1716, file: !1, line: 353, type: !1806)
!1806 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 80, align: 8, elements: !1807)
!1807 = !{!1777}
!1808 = !DILocation(line: 353, column: 8, scope: !1716)
!1809 = !DILocalVariable(name: "time_total", scope: !1716, file: !1, line: 354, type: !1806)
!1810 = !DILocation(line: 354, column: 8, scope: !1716)
!1811 = !DILocalVariable(name: "time_spent", scope: !1716, file: !1, line: 355, type: !1806)
!1812 = !DILocation(line: 355, column: 8, scope: !1716)
!1813 = !DILocalVariable(name: "ulestimate", scope: !1716, file: !1, line: 356, type: !189)
!1814 = !DILocation(line: 356, column: 14, scope: !1716)
!1815 = !DILocalVariable(name: "dlestimate", scope: !1716, file: !1, line: 357, type: !189)
!1816 = !DILocation(line: 357, column: 14, scope: !1716)
!1817 = !DILocalVariable(name: "total_estimate", scope: !1716, file: !1, line: 358, type: !189)
!1818 = !DILocation(line: 358, column: 14, scope: !1716)
!1819 = !DILocalVariable(name: "shownow", scope: !1716, file: !1, line: 359, type: !211)
!1820 = !DILocation(line: 359, column: 8, scope: !1716)
!1821 = !DILocation(line: 361, column: 9, scope: !1716)
!1822 = !DILocation(line: 361, column: 9, scope: !1823)
!1823 = !DILexicalBlockFile(scope: !1716, file: !1, discriminator: 1)
!1824 = !DILocation(line: 364, column: 53, scope: !1716)
!1825 = !DILocation(line: 364, column: 59, scope: !1716)
!1826 = !DILocation(line: 364, column: 68, scope: !1716)
!1827 = !DILocation(line: 364, column: 30, scope: !1716)
!1828 = !DILocation(line: 364, column: 3, scope: !1716)
!1829 = !DILocation(line: 364, column: 9, scope: !1716)
!1830 = !DILocation(line: 364, column: 18, scope: !1716)
!1831 = !DILocation(line: 364, column: 28, scope: !1716)
!1832 = !DILocation(line: 365, column: 27, scope: !1716)
!1833 = !DILocation(line: 365, column: 33, scope: !1716)
!1834 = !DILocation(line: 365, column: 42, scope: !1716)
!1835 = !DILocation(line: 365, column: 15, scope: !1716)
!1836 = !DILocation(line: 365, column: 13, scope: !1716)
!1837 = !DILocation(line: 369, column: 14, scope: !1716)
!1838 = !DILocation(line: 369, column: 20, scope: !1716)
!1839 = !DILocation(line: 369, column: 29, scope: !1716)
!1840 = !DILocation(line: 369, column: 6, scope: !1716)
!1841 = !DILocation(line: 370, column: 7, scope: !1716)
!1842 = !DILocation(line: 370, column: 13, scope: !1716)
!1843 = !DILocation(line: 370, column: 22, scope: !1716)
!1844 = !DILocation(line: 370, column: 31, scope: !1716)
!1845 = !DILocation(line: 370, column: 34, scope: !1823)
!1846 = !DILocation(line: 370, column: 40, scope: !1823)
!1847 = !DILocation(line: 370, column: 49, scope: !1823)
!1848 = !DILocation(line: 370, column: 7, scope: !1823)
!1849 = !DILocation(line: 370, column: 7, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !1716, file: !1, discriminator: 2)
!1851 = !DILocation(line: 370, column: 7, scope: !1852)
!1852 = !DILexicalBlockFile(scope: !1716, file: !1, discriminator: 3)
!1853 = !DILocation(line: 369, column: 39, scope: !1823)
!1854 = !DILocation(line: 368, column: 28, scope: !1716)
!1855 = !DILocation(line: 368, column: 3, scope: !1716)
!1856 = !DILocation(line: 368, column: 9, scope: !1716)
!1857 = !DILocation(line: 368, column: 18, scope: !1716)
!1858 = !DILocation(line: 368, column: 26, scope: !1716)
!1859 = !DILocation(line: 374, column: 14, scope: !1716)
!1860 = !DILocation(line: 374, column: 20, scope: !1716)
!1861 = !DILocation(line: 374, column: 29, scope: !1716)
!1862 = !DILocation(line: 374, column: 6, scope: !1716)
!1863 = !DILocation(line: 375, column: 7, scope: !1716)
!1864 = !DILocation(line: 375, column: 13, scope: !1716)
!1865 = !DILocation(line: 375, column: 22, scope: !1716)
!1866 = !DILocation(line: 375, column: 31, scope: !1716)
!1867 = !DILocation(line: 375, column: 34, scope: !1823)
!1868 = !DILocation(line: 375, column: 40, scope: !1823)
!1869 = !DILocation(line: 375, column: 49, scope: !1823)
!1870 = !DILocation(line: 375, column: 7, scope: !1823)
!1871 = !DILocation(line: 375, column: 7, scope: !1850)
!1872 = !DILocation(line: 375, column: 7, scope: !1852)
!1873 = !DILocation(line: 374, column: 37, scope: !1823)
!1874 = !DILocation(line: 373, column: 28, scope: !1716)
!1875 = !DILocation(line: 373, column: 3, scope: !1716)
!1876 = !DILocation(line: 373, column: 9, scope: !1716)
!1877 = !DILocation(line: 373, column: 18, scope: !1716)
!1878 = !DILocation(line: 373, column: 26, scope: !1716)
!1879 = !DILocation(line: 378, column: 6, scope: !1880)
!1880 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 378, column: 6)
!1881 = !DILocation(line: 378, column: 12, scope: !1880)
!1882 = !DILocation(line: 378, column: 21, scope: !1880)
!1883 = !DILocation(line: 378, column: 37, scope: !1880)
!1884 = !DILocation(line: 378, column: 30, scope: !1880)
!1885 = !DILocation(line: 378, column: 6, scope: !1716)
!1886 = !DILocation(line: 379, column: 13, scope: !1887)
!1887 = distinct !DILexicalBlock(scope: !1880, file: !1, line: 378, column: 45)
!1888 = !DILocation(line: 381, column: 35, scope: !1887)
!1889 = !DILocation(line: 381, column: 5, scope: !1887)
!1890 = !DILocation(line: 381, column: 11, scope: !1887)
!1891 = !DILocation(line: 381, column: 20, scope: !1887)
!1892 = !DILocation(line: 381, column: 29, scope: !1887)
!1893 = !DILocation(line: 386, column: 7, scope: !1887)
!1894 = !DILocation(line: 386, column: 13, scope: !1887)
!1895 = !DILocation(line: 386, column: 22, scope: !1887)
!1896 = !DILocation(line: 386, column: 33, scope: !1887)
!1897 = !DILocation(line: 386, column: 39, scope: !1887)
!1898 = !DILocation(line: 386, column: 48, scope: !1887)
!1899 = !DILocation(line: 386, column: 32, scope: !1887)
!1900 = !DILocation(line: 387, column: 7, scope: !1887)
!1901 = !DILocation(line: 387, column: 13, scope: !1887)
!1902 = !DILocation(line: 387, column: 22, scope: !1887)
!1903 = !DILocation(line: 386, column: 7, scope: !1904)
!1904 = !DILexicalBlockFile(scope: !1887, file: !1, discriminator: 1)
!1905 = !DILocation(line: 387, column: 33, scope: !1904)
!1906 = !DILocation(line: 387, column: 39, scope: !1904)
!1907 = !DILocation(line: 387, column: 48, scope: !1904)
!1908 = !DILocation(line: 386, column: 7, scope: !1909)
!1909 = !DILexicalBlockFile(scope: !1887, file: !1, discriminator: 2)
!1910 = !DILocation(line: 386, column: 7, scope: !1911)
!1911 = !DILexicalBlockFile(scope: !1887, file: !1, discriminator: 3)
!1912 = !DILocation(line: 385, column: 29, scope: !1887)
!1913 = !DILocation(line: 385, column: 5, scope: !1887)
!1914 = !DILocation(line: 385, column: 11, scope: !1887)
!1915 = !DILocation(line: 385, column: 20, scope: !1887)
!1916 = !DILocation(line: 385, column: 40, scope: !1887)
!1917 = !DILocation(line: 390, column: 35, scope: !1887)
!1918 = !DILocation(line: 390, column: 5, scope: !1887)
!1919 = !DILocation(line: 390, column: 11, scope: !1887)
!1920 = !DILocation(line: 390, column: 20, scope: !1887)
!1921 = !DILocation(line: 390, column: 48, scope: !1887)
!1922 = !DILocation(line: 394, column: 5, scope: !1887)
!1923 = !DILocation(line: 394, column: 11, scope: !1887)
!1924 = !DILocation(line: 394, column: 20, scope: !1887)
!1925 = !DILocation(line: 394, column: 29, scope: !1887)
!1926 = !DILocation(line: 400, column: 20, scope: !1887)
!1927 = !DILocation(line: 400, column: 26, scope: !1887)
!1928 = !DILocation(line: 400, column: 35, scope: !1887)
!1929 = !DILocation(line: 400, column: 44, scope: !1887)
!1930 = !DILocation(line: 400, column: 19, scope: !1887)
!1931 = !DILocation(line: 400, column: 19, scope: !1904)
!1932 = !DILocation(line: 401, column: 29, scope: !1887)
!1933 = !DILocation(line: 401, column: 35, scope: !1887)
!1934 = !DILocation(line: 401, column: 44, scope: !1887)
!1935 = !DILocation(line: 400, column: 19, scope: !1909)
!1936 = !DILocation(line: 400, column: 19, scope: !1911)
!1937 = !DILocation(line: 401, column: 55, scope: !1904)
!1938 = !DILocation(line: 400, column: 16, scope: !1911)
!1939 = !DILocation(line: 404, column: 8, scope: !1940)
!1940 = distinct !DILexicalBlock(scope: !1887, file: !1, line: 404, column: 8)
!1941 = !DILocation(line: 404, column: 8, scope: !1887)
!1942 = !DILocalVariable(name: "span_ms", scope: !1943, file: !1, line: 405, type: !242)
!1943 = distinct !DILexicalBlock(scope: !1940, file: !1, line: 404, column: 20)
!1944 = !DILocation(line: 405, column: 14, scope: !1943)
!1945 = !DILocation(line: 410, column: 21, scope: !1943)
!1946 = !DILocation(line: 410, column: 27, scope: !1943)
!1947 = !DILocation(line: 410, column: 36, scope: !1943)
!1948 = !DILocation(line: 410, column: 45, scope: !1943)
!1949 = !DILocation(line: 410, column: 20, scope: !1943)
!1950 = !DILocation(line: 411, column: 9, scope: !1943)
!1951 = !DILocation(line: 411, column: 15, scope: !1943)
!1952 = !DILocation(line: 411, column: 24, scope: !1943)
!1953 = !DILocation(line: 411, column: 33, scope: !1943)
!1954 = !DILocation(line: 410, column: 20, scope: !1955)
!1955 = !DILexicalBlockFile(scope: !1943, file: !1, discriminator: 1)
!1956 = !DILocation(line: 410, column: 20, scope: !1957)
!1957 = !DILexicalBlockFile(scope: !1943, file: !1, discriminator: 2)
!1958 = !DILocation(line: 410, column: 20, scope: !1959)
!1959 = !DILexicalBlockFile(scope: !1943, file: !1, discriminator: 3)
!1960 = !DILocation(line: 410, column: 18, scope: !1959)
!1961 = !DILocation(line: 414, column: 17, scope: !1943)
!1962 = !DILocation(line: 414, column: 15, scope: !1943)
!1963 = !DILocation(line: 416, column: 15, scope: !1964)
!1964 = distinct !DILexicalBlock(scope: !1943, file: !1, line: 416, column: 10)
!1965 = !DILocation(line: 416, column: 12, scope: !1964)
!1966 = !DILocation(line: 416, column: 10, scope: !1943)
!1967 = !DILocation(line: 417, column: 16, scope: !1964)
!1968 = !DILocation(line: 417, column: 9, scope: !1964)
!1969 = !DILocalVariable(name: "amount", scope: !1970, file: !1, line: 421, type: !189)
!1970 = distinct !DILexicalBlock(scope: !1943, file: !1, line: 420, column: 7)
!1971 = !DILocation(line: 421, column: 20, scope: !1970)
!1972 = !DILocation(line: 421, column: 52, scope: !1970)
!1973 = !DILocation(line: 421, column: 29, scope: !1970)
!1974 = !DILocation(line: 421, column: 35, scope: !1970)
!1975 = !DILocation(line: 421, column: 44, scope: !1970)
!1976 = !DILocation(line: 422, column: 34, scope: !1970)
!1977 = !DILocation(line: 422, column: 11, scope: !1970)
!1978 = !DILocation(line: 422, column: 17, scope: !1970)
!1979 = !DILocation(line: 422, column: 26, scope: !1970)
!1980 = !DILocation(line: 421, column: 61, scope: !1970)
!1981 = !DILocation(line: 424, column: 12, scope: !1982)
!1982 = distinct !DILexicalBlock(scope: !1970, file: !1, line: 424, column: 12)
!1983 = !DILocation(line: 424, column: 19, scope: !1982)
!1984 = !DILocation(line: 424, column: 12, scope: !1970)
!1985 = !DILocation(line: 428, column: 22, scope: !1982)
!1986 = !DILocation(line: 428, column: 14, scope: !1982)
!1987 = !DILocation(line: 428, column: 38, scope: !1982)
!1988 = !DILocation(line: 428, column: 30, scope: !1982)
!1989 = !DILocation(line: 428, column: 45, scope: !1982)
!1990 = !DILocation(line: 428, column: 28, scope: !1982)
!1991 = !DILocation(line: 427, column: 42, scope: !1982)
!1992 = !DILocation(line: 427, column: 11, scope: !1982)
!1993 = !DILocation(line: 427, column: 17, scope: !1982)
!1994 = !DILocation(line: 427, column: 26, scope: !1982)
!1995 = !DILocation(line: 427, column: 40, scope: !1982)
!1996 = !DILocation(line: 432, column: 42, scope: !1982)
!1997 = !DILocation(line: 432, column: 48, scope: !1982)
!1998 = !DILocation(line: 432, column: 68, scope: !1982)
!1999 = !DILocation(line: 432, column: 67, scope: !1982)
!2000 = !DILocation(line: 432, column: 11, scope: !1982)
!2001 = !DILocation(line: 432, column: 17, scope: !1982)
!2002 = !DILocation(line: 432, column: 26, scope: !1982)
!2003 = !DILocation(line: 432, column: 40, scope: !1982)
!2004 = !DILocation(line: 434, column: 5, scope: !1943)
!2005 = !DILocation(line: 438, column: 10, scope: !1940)
!2006 = !DILocation(line: 438, column: 16, scope: !1940)
!2007 = !DILocation(line: 438, column: 25, scope: !1940)
!2008 = !DILocation(line: 438, column: 33, scope: !1940)
!2009 = !DILocation(line: 438, column: 39, scope: !1940)
!2010 = !DILocation(line: 438, column: 48, scope: !1940)
!2011 = !DILocation(line: 438, column: 32, scope: !1940)
!2012 = !DILocation(line: 438, column: 9, scope: !1940)
!2013 = !DILocation(line: 439, column: 9, scope: !1940)
!2014 = !DILocation(line: 439, column: 15, scope: !1940)
!2015 = !DILocation(line: 439, column: 24, scope: !1940)
!2016 = !DILocation(line: 438, column: 9, scope: !2017)
!2017 = !DILexicalBlockFile(scope: !1940, file: !1, discriminator: 1)
!2018 = !DILocation(line: 439, column: 32, scope: !2017)
!2019 = !DILocation(line: 439, column: 38, scope: !2017)
!2020 = !DILocation(line: 439, column: 47, scope: !2017)
!2021 = !DILocation(line: 438, column: 9, scope: !2022)
!2022 = !DILexicalBlockFile(scope: !1940, file: !1, discriminator: 2)
!2023 = !DILocation(line: 438, column: 9, scope: !2024)
!2024 = !DILexicalBlockFile(scope: !1940, file: !1, discriminator: 3)
!2025 = !DILocation(line: 437, column: 7, scope: !1940)
!2026 = !DILocation(line: 437, column: 13, scope: !1940)
!2027 = !DILocation(line: 437, column: 22, scope: !1940)
!2028 = !DILocation(line: 437, column: 36, scope: !1940)
!2029 = !DILocation(line: 441, column: 3, scope: !1887)
!2030 = !DILocation(line: 443, column: 8, scope: !2031)
!2031 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 443, column: 6)
!2032 = !DILocation(line: 443, column: 14, scope: !2031)
!2033 = !DILocation(line: 443, column: 23, scope: !2031)
!2034 = !DILocation(line: 443, column: 29, scope: !2031)
!2035 = !DILocation(line: 443, column: 6, scope: !1716)
!2036 = !DILocation(line: 446, column: 8, scope: !2037)
!2037 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 446, column: 8)
!2038 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 443, column: 43)
!2039 = !DILocation(line: 446, column: 14, scope: !2037)
!2040 = !DILocation(line: 446, column: 18, scope: !2037)
!2041 = !DILocation(line: 446, column: 8, scope: !2038)
!2042 = !DILocation(line: 448, column: 15, scope: !2043)
!2043 = distinct !DILexicalBlock(scope: !2037, file: !1, line: 446, column: 29)
!2044 = !DILocation(line: 448, column: 21, scope: !2043)
!2045 = !DILocation(line: 448, column: 25, scope: !2043)
!2046 = !DILocation(line: 448, column: 35, scope: !2043)
!2047 = !DILocation(line: 448, column: 41, scope: !2043)
!2048 = !DILocation(line: 448, column: 45, scope: !2043)
!2049 = !DILocation(line: 449, column: 35, scope: !2043)
!2050 = !DILocation(line: 449, column: 41, scope: !2043)
!2051 = !DILocation(line: 449, column: 50, scope: !2043)
!2052 = !DILocation(line: 450, column: 35, scope: !2043)
!2053 = !DILocation(line: 450, column: 41, scope: !2043)
!2054 = !DILocation(line: 450, column: 50, scope: !2043)
!2055 = !DILocation(line: 451, column: 35, scope: !2043)
!2056 = !DILocation(line: 451, column: 41, scope: !2043)
!2057 = !DILocation(line: 451, column: 50, scope: !2043)
!2058 = !DILocation(line: 452, column: 35, scope: !2043)
!2059 = !DILocation(line: 452, column: 41, scope: !2043)
!2060 = !DILocation(line: 452, column: 50, scope: !2043)
!2061 = !DILocation(line: 448, column: 13, scope: !2043)
!2062 = !DILocation(line: 453, column: 10, scope: !2063)
!2063 = distinct !DILexicalBlock(scope: !2043, file: !1, line: 453, column: 10)
!2064 = !DILocation(line: 453, column: 10, scope: !2043)
!2065 = !DILocation(line: 454, column: 15, scope: !2063)
!2066 = !DILocation(line: 454, column: 9, scope: !2063)
!2067 = !DILocation(line: 455, column: 14, scope: !2043)
!2068 = !DILocation(line: 455, column: 7, scope: !2043)
!2069 = !DILocation(line: 457, column: 8, scope: !2070)
!2070 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 457, column: 8)
!2071 = !DILocation(line: 457, column: 14, scope: !2070)
!2072 = !DILocation(line: 457, column: 18, scope: !2070)
!2073 = !DILocation(line: 457, column: 8, scope: !2038)
!2074 = !DILocation(line: 459, column: 15, scope: !2075)
!2075 = distinct !DILexicalBlock(scope: !2070, file: !1, line: 457, column: 29)
!2076 = !DILocation(line: 459, column: 21, scope: !2075)
!2077 = !DILocation(line: 459, column: 25, scope: !2075)
!2078 = !DILocation(line: 459, column: 35, scope: !2075)
!2079 = !DILocation(line: 459, column: 41, scope: !2075)
!2080 = !DILocation(line: 459, column: 45, scope: !2075)
!2081 = !DILocation(line: 460, column: 43, scope: !2075)
!2082 = !DILocation(line: 460, column: 49, scope: !2075)
!2083 = !DILocation(line: 460, column: 58, scope: !2075)
!2084 = !DILocation(line: 460, column: 35, scope: !2075)
!2085 = !DILocation(line: 461, column: 43, scope: !2075)
!2086 = !DILocation(line: 461, column: 49, scope: !2075)
!2087 = !DILocation(line: 461, column: 58, scope: !2075)
!2088 = !DILocation(line: 461, column: 35, scope: !2075)
!2089 = !DILocation(line: 462, column: 43, scope: !2075)
!2090 = !DILocation(line: 462, column: 49, scope: !2075)
!2091 = !DILocation(line: 462, column: 58, scope: !2075)
!2092 = !DILocation(line: 462, column: 35, scope: !2075)
!2093 = !DILocation(line: 463, column: 43, scope: !2075)
!2094 = !DILocation(line: 463, column: 49, scope: !2075)
!2095 = !DILocation(line: 463, column: 58, scope: !2075)
!2096 = !DILocation(line: 463, column: 35, scope: !2075)
!2097 = !DILocation(line: 459, column: 13, scope: !2075)
!2098 = !DILocation(line: 464, column: 10, scope: !2099)
!2099 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 464, column: 10)
!2100 = !DILocation(line: 464, column: 10, scope: !2075)
!2101 = !DILocation(line: 465, column: 15, scope: !2099)
!2102 = !DILocation(line: 465, column: 9, scope: !2099)
!2103 = !DILocation(line: 466, column: 14, scope: !2075)
!2104 = !DILocation(line: 466, column: 7, scope: !2075)
!2105 = !DILocation(line: 469, column: 9, scope: !2106)
!2106 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 469, column: 8)
!2107 = !DILocation(line: 469, column: 8, scope: !2038)
!2108 = !DILocation(line: 471, column: 7, scope: !2106)
!2109 = !DILocation(line: 476, column: 10, scope: !2110)
!2110 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 476, column: 8)
!2111 = !DILocation(line: 476, column: 16, scope: !2110)
!2112 = !DILocation(line: 476, column: 25, scope: !2110)
!2113 = !DILocation(line: 476, column: 31, scope: !2110)
!2114 = !DILocation(line: 476, column: 8, scope: !2038)
!2115 = !DILocation(line: 477, column: 10, scope: !2116)
!2116 = distinct !DILexicalBlock(scope: !2117, file: !1, line: 477, column: 10)
!2117 = distinct !DILexicalBlock(scope: !2110, file: !1, line: 476, column: 52)
!2118 = !DILocation(line: 477, column: 16, scope: !2116)
!2119 = !DILocation(line: 477, column: 22, scope: !2116)
!2120 = !DILocation(line: 477, column: 10, scope: !2117)
!2121 = !DILocation(line: 478, column: 17, scope: !2122)
!2122 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 477, column: 35)
!2123 = !DILocation(line: 478, column: 23, scope: !2122)
!2124 = !DILocation(line: 478, column: 27, scope: !2122)
!2125 = !DILocation(line: 480, column: 46, scope: !2122)
!2126 = !DILocation(line: 480, column: 52, scope: !2122)
!2127 = !DILocation(line: 480, column: 58, scope: !2122)
!2128 = !DILocation(line: 478, column: 9, scope: !2122)
!2129 = !DILocation(line: 481, column: 7, scope: !2122)
!2130 = !DILocation(line: 482, column: 15, scope: !2117)
!2131 = !DILocation(line: 482, column: 21, scope: !2117)
!2132 = !DILocation(line: 482, column: 25, scope: !2117)
!2133 = !DILocation(line: 482, column: 7, scope: !2117)
!2134 = !DILocation(line: 487, column: 7, scope: !2117)
!2135 = !DILocation(line: 487, column: 13, scope: !2117)
!2136 = !DILocation(line: 487, column: 22, scope: !2117)
!2137 = !DILocation(line: 487, column: 28, scope: !2117)
!2138 = !DILocation(line: 488, column: 5, scope: !2117)
!2139 = !DILocation(line: 491, column: 9, scope: !2140)
!2140 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 491, column: 8)
!2141 = !DILocation(line: 491, column: 15, scope: !2140)
!2142 = !DILocation(line: 491, column: 24, scope: !2140)
!2143 = !DILocation(line: 491, column: 30, scope: !2140)
!2144 = !DILocation(line: 491, column: 52, scope: !2140)
!2145 = !DILocation(line: 492, column: 9, scope: !2140)
!2146 = !DILocation(line: 492, column: 15, scope: !2140)
!2147 = !DILocation(line: 492, column: 24, scope: !2140)
!2148 = !DILocation(line: 492, column: 32, scope: !2140)
!2149 = !DILocation(line: 491, column: 8, scope: !2150)
!2150 = !DILexicalBlockFile(scope: !2038, file: !1, discriminator: 1)
!2151 = !DILocation(line: 493, column: 20, scope: !2152)
!2152 = distinct !DILexicalBlock(scope: !2140, file: !1, line: 492, column: 52)
!2153 = !DILocation(line: 493, column: 26, scope: !2152)
!2154 = !DILocation(line: 493, column: 35, scope: !2152)
!2155 = !DILocation(line: 493, column: 45, scope: !2152)
!2156 = !DILocation(line: 493, column: 51, scope: !2152)
!2157 = !DILocation(line: 493, column: 60, scope: !2152)
!2158 = !DILocation(line: 493, column: 43, scope: !2152)
!2159 = !DILocation(line: 493, column: 18, scope: !2152)
!2160 = !DILocation(line: 495, column: 10, scope: !2161)
!2161 = distinct !DILexicalBlock(scope: !2152, file: !1, line: 495, column: 10)
!2162 = !DILocation(line: 495, column: 16, scope: !2161)
!2163 = !DILocation(line: 495, column: 25, scope: !2161)
!2164 = !DILocation(line: 495, column: 33, scope: !2161)
!2165 = !DILocation(line: 495, column: 10, scope: !2152)
!2166 = !DILocation(line: 496, column: 20, scope: !2161)
!2167 = !DILocation(line: 496, column: 26, scope: !2161)
!2168 = !DILocation(line: 496, column: 35, scope: !2161)
!2169 = !DILocation(line: 497, column: 12, scope: !2161)
!2170 = !DILocation(line: 497, column: 18, scope: !2161)
!2171 = !DILocation(line: 497, column: 27, scope: !2161)
!2172 = !DILocation(line: 497, column: 34, scope: !2161)
!2173 = !DILocation(line: 496, column: 44, scope: !2161)
!2174 = !DILocation(line: 496, column: 18, scope: !2161)
!2175 = !DILocation(line: 496, column: 9, scope: !2161)
!2176 = !DILocation(line: 498, column: 15, scope: !2177)
!2177 = distinct !DILexicalBlock(scope: !2161, file: !1, line: 498, column: 15)
!2178 = !DILocation(line: 498, column: 21, scope: !2177)
!2179 = !DILocation(line: 498, column: 30, scope: !2177)
!2180 = !DILocation(line: 498, column: 38, scope: !2177)
!2181 = !DILocation(line: 498, column: 15, scope: !2161)
!2182 = !DILocation(line: 499, column: 21, scope: !2177)
!2183 = !DILocation(line: 499, column: 27, scope: !2177)
!2184 = !DILocation(line: 499, column: 36, scope: !2177)
!2185 = !DILocation(line: 499, column: 44, scope: !2177)
!2186 = !DILocation(line: 500, column: 11, scope: !2177)
!2187 = !DILocation(line: 500, column: 17, scope: !2177)
!2188 = !DILocation(line: 500, column: 26, scope: !2177)
!2189 = !DILocation(line: 499, column: 50, scope: !2177)
!2190 = !DILocation(line: 499, column: 18, scope: !2177)
!2191 = !DILocation(line: 499, column: 9, scope: !2177)
!2192 = !DILocation(line: 501, column: 5, scope: !2152)
!2193 = !DILocation(line: 504, column: 9, scope: !2194)
!2194 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 504, column: 8)
!2195 = !DILocation(line: 504, column: 15, scope: !2194)
!2196 = !DILocation(line: 504, column: 24, scope: !2194)
!2197 = !DILocation(line: 504, column: 30, scope: !2194)
!2198 = !DILocation(line: 504, column: 52, scope: !2194)
!2199 = !DILocation(line: 505, column: 9, scope: !2194)
!2200 = !DILocation(line: 505, column: 15, scope: !2194)
!2201 = !DILocation(line: 505, column: 24, scope: !2194)
!2202 = !DILocation(line: 505, column: 32, scope: !2194)
!2203 = !DILocation(line: 504, column: 8, scope: !2150)
!2204 = !DILocation(line: 506, column: 20, scope: !2205)
!2205 = distinct !DILexicalBlock(scope: !2194, file: !1, line: 505, column: 52)
!2206 = !DILocation(line: 506, column: 26, scope: !2205)
!2207 = !DILocation(line: 506, column: 35, scope: !2205)
!2208 = !DILocation(line: 506, column: 45, scope: !2205)
!2209 = !DILocation(line: 506, column: 51, scope: !2205)
!2210 = !DILocation(line: 506, column: 60, scope: !2205)
!2211 = !DILocation(line: 506, column: 43, scope: !2205)
!2212 = !DILocation(line: 506, column: 18, scope: !2205)
!2213 = !DILocation(line: 508, column: 10, scope: !2214)
!2214 = distinct !DILexicalBlock(scope: !2205, file: !1, line: 508, column: 10)
!2215 = !DILocation(line: 508, column: 16, scope: !2214)
!2216 = !DILocation(line: 508, column: 25, scope: !2214)
!2217 = !DILocation(line: 508, column: 33, scope: !2214)
!2218 = !DILocation(line: 508, column: 10, scope: !2205)
!2219 = !DILocation(line: 509, column: 20, scope: !2214)
!2220 = !DILocation(line: 509, column: 26, scope: !2214)
!2221 = !DILocation(line: 509, column: 35, scope: !2214)
!2222 = !DILocation(line: 510, column: 12, scope: !2214)
!2223 = !DILocation(line: 510, column: 18, scope: !2214)
!2224 = !DILocation(line: 510, column: 27, scope: !2214)
!2225 = !DILocation(line: 510, column: 34, scope: !2214)
!2226 = !DILocation(line: 509, column: 46, scope: !2214)
!2227 = !DILocation(line: 509, column: 18, scope: !2214)
!2228 = !DILocation(line: 509, column: 9, scope: !2214)
!2229 = !DILocation(line: 511, column: 15, scope: !2230)
!2230 = distinct !DILexicalBlock(scope: !2214, file: !1, line: 511, column: 15)
!2231 = !DILocation(line: 511, column: 21, scope: !2230)
!2232 = !DILocation(line: 511, column: 30, scope: !2230)
!2233 = !DILocation(line: 511, column: 38, scope: !2230)
!2234 = !DILocation(line: 511, column: 15, scope: !2214)
!2235 = !DILocation(line: 512, column: 21, scope: !2230)
!2236 = !DILocation(line: 512, column: 27, scope: !2230)
!2237 = !DILocation(line: 512, column: 36, scope: !2230)
!2238 = !DILocation(line: 512, column: 46, scope: !2230)
!2239 = !DILocation(line: 513, column: 11, scope: !2230)
!2240 = !DILocation(line: 513, column: 17, scope: !2230)
!2241 = !DILocation(line: 513, column: 26, scope: !2230)
!2242 = !DILocation(line: 512, column: 52, scope: !2230)
!2243 = !DILocation(line: 512, column: 18, scope: !2230)
!2244 = !DILocation(line: 512, column: 9, scope: !2230)
!2245 = !DILocation(line: 514, column: 5, scope: !2205)
!2246 = !DILocation(line: 518, column: 22, scope: !2038)
!2247 = !DILocation(line: 518, column: 33, scope: !2038)
!2248 = !DILocation(line: 518, column: 32, scope: !2038)
!2249 = !DILocation(line: 518, column: 44, scope: !2150)
!2250 = !DILocation(line: 518, column: 22, scope: !2150)
!2251 = !DILocation(line: 518, column: 55, scope: !2252)
!2252 = !DILexicalBlockFile(scope: !2038, file: !1, discriminator: 2)
!2253 = !DILocation(line: 518, column: 22, scope: !2252)
!2254 = !DILocation(line: 518, column: 22, scope: !2255)
!2255 = !DILexicalBlockFile(scope: !2038, file: !1, discriminator: 3)
!2256 = !DILocation(line: 518, column: 20, scope: !2255)
!2257 = !DILocation(line: 521, column: 14, scope: !2038)
!2258 = !DILocation(line: 521, column: 25, scope: !2038)
!2259 = !DILocation(line: 521, column: 40, scope: !2038)
!2260 = !DILocation(line: 521, column: 45, scope: !2150)
!2261 = !DILocation(line: 521, column: 62, scope: !2150)
!2262 = !DILocation(line: 521, column: 60, scope: !2150)
!2263 = !DILocation(line: 521, column: 25, scope: !2150)
!2264 = !DILocation(line: 521, column: 25, scope: !2252)
!2265 = !DILocation(line: 521, column: 25, scope: !2255)
!2266 = !DILocation(line: 521, column: 5, scope: !2255)
!2267 = !DILocation(line: 522, column: 14, scope: !2038)
!2268 = !DILocation(line: 522, column: 26, scope: !2038)
!2269 = !DILocation(line: 522, column: 5, scope: !2038)
!2270 = !DILocation(line: 523, column: 14, scope: !2038)
!2271 = !DILocation(line: 523, column: 26, scope: !2038)
!2272 = !DILocation(line: 523, column: 5, scope: !2038)
!2273 = !DILocation(line: 527, column: 8, scope: !2038)
!2274 = !DILocation(line: 527, column: 14, scope: !2038)
!2275 = !DILocation(line: 527, column: 23, scope: !2038)
!2276 = !DILocation(line: 527, column: 29, scope: !2038)
!2277 = !DILocation(line: 528, column: 8, scope: !2038)
!2278 = !DILocation(line: 528, column: 14, scope: !2038)
!2279 = !DILocation(line: 528, column: 23, scope: !2038)
!2280 = !DILocation(line: 527, column: 8, scope: !2150)
!2281 = !DILocation(line: 528, column: 31, scope: !2150)
!2282 = !DILocation(line: 528, column: 37, scope: !2150)
!2283 = !DILocation(line: 528, column: 46, scope: !2150)
!2284 = !DILocation(line: 527, column: 8, scope: !2252)
!2285 = !DILocation(line: 527, column: 8, scope: !2255)
!2286 = !DILocation(line: 529, column: 8, scope: !2038)
!2287 = !DILocation(line: 529, column: 14, scope: !2038)
!2288 = !DILocation(line: 529, column: 23, scope: !2038)
!2289 = !DILocation(line: 529, column: 29, scope: !2038)
!2290 = !DILocation(line: 530, column: 8, scope: !2038)
!2291 = !DILocation(line: 530, column: 14, scope: !2038)
!2292 = !DILocation(line: 530, column: 23, scope: !2038)
!2293 = !DILocation(line: 529, column: 8, scope: !2150)
!2294 = !DILocation(line: 530, column: 31, scope: !2150)
!2295 = !DILocation(line: 530, column: 37, scope: !2150)
!2296 = !DILocation(line: 530, column: 46, scope: !2150)
!2297 = !DILocation(line: 529, column: 8, scope: !2252)
!2298 = !DILocation(line: 529, column: 8, scope: !2255)
!2299 = !DILocation(line: 528, column: 55, scope: !2252)
!2300 = !DILocation(line: 526, column: 29, scope: !2038)
!2301 = !DILocation(line: 533, column: 22, scope: !2038)
!2302 = !DILocation(line: 533, column: 28, scope: !2038)
!2303 = !DILocation(line: 533, column: 37, scope: !2038)
!2304 = !DILocation(line: 533, column: 50, scope: !2038)
!2305 = !DILocation(line: 533, column: 56, scope: !2038)
!2306 = !DILocation(line: 533, column: 65, scope: !2038)
!2307 = !DILocation(line: 533, column: 48, scope: !2038)
!2308 = !DILocation(line: 533, column: 20, scope: !2038)
!2309 = !DILocation(line: 536, column: 8, scope: !2310)
!2310 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 536, column: 8)
!2311 = !DILocation(line: 536, column: 32, scope: !2310)
!2312 = !DILocation(line: 536, column: 8, scope: !2038)
!2313 = !DILocation(line: 537, column: 22, scope: !2310)
!2314 = !DILocation(line: 538, column: 10, scope: !2310)
!2315 = !DILocation(line: 538, column: 33, scope: !2310)
!2316 = !DILocation(line: 537, column: 37, scope: !2310)
!2317 = !DILocation(line: 537, column: 20, scope: !2310)
!2318 = !DILocation(line: 537, column: 7, scope: !2310)
!2319 = !DILocation(line: 539, column: 13, scope: !2320)
!2320 = distinct !DILexicalBlock(scope: !2310, file: !1, line: 539, column: 13)
!2321 = !DILocation(line: 539, column: 37, scope: !2320)
!2322 = !DILocation(line: 539, column: 13, scope: !2310)
!2323 = !DILocation(line: 540, column: 23, scope: !2320)
!2324 = !DILocation(line: 540, column: 37, scope: !2320)
!2325 = !DILocation(line: 540, column: 45, scope: !2320)
!2326 = !DILocation(line: 540, column: 43, scope: !2320)
!2327 = !DILocation(line: 540, column: 20, scope: !2320)
!2328 = !DILocation(line: 540, column: 7, scope: !2320)
!2329 = !DILocation(line: 542, column: 13, scope: !2038)
!2330 = !DILocation(line: 542, column: 19, scope: !2038)
!2331 = !DILocation(line: 542, column: 23, scope: !2038)
!2332 = !DILocation(line: 547, column: 13, scope: !2038)
!2333 = !DILocation(line: 548, column: 22, scope: !2038)
!2334 = !DILocation(line: 548, column: 47, scope: !2038)
!2335 = !DILocation(line: 548, column: 13, scope: !2038)
!2336 = !DILocation(line: 549, column: 13, scope: !2038)
!2337 = !DILocation(line: 550, column: 22, scope: !2038)
!2338 = !DILocation(line: 550, column: 28, scope: !2038)
!2339 = !DILocation(line: 550, column: 37, scope: !2038)
!2340 = !DILocation(line: 550, column: 49, scope: !2038)
!2341 = !DILocation(line: 550, column: 13, scope: !2038)
!2342 = !DILocation(line: 551, column: 13, scope: !2038)
!2343 = !DILocation(line: 552, column: 22, scope: !2038)
!2344 = !DILocation(line: 552, column: 28, scope: !2038)
!2345 = !DILocation(line: 552, column: 37, scope: !2038)
!2346 = !DILocation(line: 552, column: 47, scope: !2038)
!2347 = !DILocation(line: 552, column: 13, scope: !2038)
!2348 = !DILocation(line: 553, column: 22, scope: !2038)
!2349 = !DILocation(line: 553, column: 28, scope: !2038)
!2350 = !DILocation(line: 553, column: 37, scope: !2038)
!2351 = !DILocation(line: 553, column: 46, scope: !2038)
!2352 = !DILocation(line: 553, column: 13, scope: !2038)
!2353 = !DILocation(line: 554, column: 22, scope: !2038)
!2354 = !DILocation(line: 554, column: 28, scope: !2038)
!2355 = !DILocation(line: 554, column: 37, scope: !2038)
!2356 = !DILocation(line: 554, column: 46, scope: !2038)
!2357 = !DILocation(line: 554, column: 13, scope: !2038)
!2358 = !DILocation(line: 555, column: 13, scope: !2038)
!2359 = !DILocation(line: 556, column: 13, scope: !2038)
!2360 = !DILocation(line: 557, column: 13, scope: !2038)
!2361 = !DILocation(line: 558, column: 22, scope: !2038)
!2362 = !DILocation(line: 558, column: 28, scope: !2038)
!2363 = !DILocation(line: 558, column: 37, scope: !2038)
!2364 = !DILocation(line: 558, column: 52, scope: !2038)
!2365 = !DILocation(line: 558, column: 13, scope: !2038)
!2366 = !DILocation(line: 542, column: 5, scope: !2038)
!2367 = !DILocation(line: 562, column: 12, scope: !2038)
!2368 = !DILocation(line: 562, column: 18, scope: !2038)
!2369 = !DILocation(line: 562, column: 22, scope: !2038)
!2370 = !DILocation(line: 562, column: 5, scope: !2038)
!2371 = !DILocation(line: 564, column: 3, scope: !2038)
!2372 = !DILocation(line: 566, column: 3, scope: !1716)
!2373 = !DILocation(line: 567, column: 1, scope: !1716)
!2374 = !DILocalVariable(name: "data", arg: 1, scope: !1699, file: !1, line: 153, type: !544)
!2375 = !DILocation(line: 153, column: 49, scope: !1699)
!2376 = !DILocation(line: 155, column: 3, scope: !1699)
!2377 = !DILocation(line: 155, column: 9, scope: !1699)
!2378 = !DILocation(line: 155, column: 18, scope: !1699)
!2379 = !DILocation(line: 155, column: 29, scope: !1699)
!2380 = !DILocation(line: 156, column: 3, scope: !1699)
!2381 = !DILocation(line: 156, column: 9, scope: !1699)
!2382 = !DILocation(line: 156, column: 18, scope: !1699)
!2383 = !DILocation(line: 156, column: 28, scope: !1699)
!2384 = !DILocation(line: 157, column: 3, scope: !1699)
!2385 = !DILocation(line: 157, column: 9, scope: !1699)
!2386 = !DILocation(line: 157, column: 18, scope: !1699)
!2387 = !DILocation(line: 157, column: 32, scope: !1699)
!2388 = !DILocation(line: 158, column: 3, scope: !1699)
!2389 = !DILocation(line: 158, column: 9, scope: !1699)
!2390 = !DILocation(line: 158, column: 18, scope: !1699)
!2391 = !DILocation(line: 158, column: 34, scope: !1699)
!2392 = !DILocation(line: 160, column: 28, scope: !1699)
!2393 = !DILocation(line: 160, column: 3, scope: !1699)
!2394 = !DILocation(line: 161, column: 26, scope: !1699)
!2395 = !DILocation(line: 161, column: 3, scope: !1699)
!2396 = !DILocation(line: 162, column: 1, scope: !1699)
!2397 = !DILocalVariable(name: "data", arg: 1, scope: !1714, file: !1, line: 310, type: !544)
!2398 = !DILocation(line: 310, column: 49, scope: !1714)
!2399 = !DILocalVariable(name: "size", arg: 2, scope: !1714, file: !1, line: 310, type: !189)
!2400 = !DILocation(line: 310, column: 66, scope: !1714)
!2401 = !DILocation(line: 312, column: 6, scope: !2402)
!2402 = distinct !DILexicalBlock(scope: !1714, file: !1, line: 312, column: 6)
!2403 = !DILocation(line: 312, column: 11, scope: !2402)
!2404 = !DILocation(line: 312, column: 6, scope: !1714)
!2405 = !DILocation(line: 313, column: 30, scope: !2406)
!2406 = distinct !DILexicalBlock(scope: !2402, file: !1, line: 312, column: 17)
!2407 = !DILocation(line: 313, column: 5, scope: !2406)
!2408 = !DILocation(line: 313, column: 11, scope: !2406)
!2409 = !DILocation(line: 313, column: 20, scope: !2406)
!2410 = !DILocation(line: 313, column: 28, scope: !2406)
!2411 = !DILocation(line: 314, column: 5, scope: !2406)
!2412 = !DILocation(line: 314, column: 11, scope: !2406)
!2413 = !DILocation(line: 314, column: 20, scope: !2406)
!2414 = !DILocation(line: 314, column: 26, scope: !2406)
!2415 = !DILocation(line: 315, column: 3, scope: !2406)
!2416 = !DILocation(line: 317, column: 5, scope: !2417)
!2417 = distinct !DILexicalBlock(scope: !2402, file: !1, line: 316, column: 8)
!2418 = !DILocation(line: 317, column: 11, scope: !2417)
!2419 = !DILocation(line: 317, column: 20, scope: !2417)
!2420 = !DILocation(line: 317, column: 28, scope: !2417)
!2421 = !DILocation(line: 318, column: 5, scope: !2417)
!2422 = !DILocation(line: 318, column: 11, scope: !2417)
!2423 = !DILocation(line: 318, column: 20, scope: !2417)
!2424 = !DILocation(line: 318, column: 26, scope: !2417)
!2425 = !DILocation(line: 320, column: 1, scope: !1714)
!2426 = !DILocalVariable(name: "data", arg: 1, scope: !1715, file: !1, line: 322, type: !544)
!2427 = !DILocation(line: 322, column: 47, scope: !1715)
!2428 = !DILocalVariable(name: "size", arg: 2, scope: !1715, file: !1, line: 322, type: !189)
!2429 = !DILocation(line: 322, column: 64, scope: !1715)
!2430 = !DILocation(line: 324, column: 6, scope: !2431)
!2431 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 324, column: 6)
!2432 = !DILocation(line: 324, column: 11, scope: !2431)
!2433 = !DILocation(line: 324, column: 6, scope: !1715)
!2434 = !DILocation(line: 325, column: 30, scope: !2435)
!2435 = distinct !DILexicalBlock(scope: !2431, file: !1, line: 324, column: 17)
!2436 = !DILocation(line: 325, column: 5, scope: !2435)
!2437 = !DILocation(line: 325, column: 11, scope: !2435)
!2438 = !DILocation(line: 325, column: 20, scope: !2435)
!2439 = !DILocation(line: 325, column: 28, scope: !2435)
!2440 = !DILocation(line: 326, column: 5, scope: !2435)
!2441 = !DILocation(line: 326, column: 11, scope: !2435)
!2442 = !DILocation(line: 326, column: 20, scope: !2435)
!2443 = !DILocation(line: 326, column: 26, scope: !2435)
!2444 = !DILocation(line: 327, column: 3, scope: !2435)
!2445 = !DILocation(line: 329, column: 5, scope: !2446)
!2446 = distinct !DILexicalBlock(scope: !2431, file: !1, line: 328, column: 8)
!2447 = !DILocation(line: 329, column: 11, scope: !2446)
!2448 = !DILocation(line: 329, column: 20, scope: !2446)
!2449 = !DILocation(line: 329, column: 28, scope: !2446)
!2450 = !DILocation(line: 330, column: 5, scope: !2446)
!2451 = !DILocation(line: 330, column: 11, scope: !2446)
!2452 = !DILocation(line: 330, column: 20, scope: !2446)
!2453 = !DILocation(line: 330, column: 26, scope: !2446)
!2454 = !DILocation(line: 332, column: 1, scope: !1715)
!2455 = !DILocalVariable(name: "data", arg: 1, scope: !1702, file: !1, line: 164, type: !544)
!2456 = !DILocation(line: 164, column: 38, scope: !1702)
!2457 = !DILocalVariable(name: "timer", arg: 2, scope: !1702, file: !1, line: 164, type: !1705)
!2458 = !DILocation(line: 164, column: 52, scope: !1702)
!2459 = !DILocalVariable(name: "now", scope: !1702, file: !1, line: 166, type: !201)
!2460 = !DILocation(line: 166, column: 18, scope: !1702)
!2461 = !DILocation(line: 166, column: 24, scope: !1702)
!2462 = !DILocation(line: 168, column: 10, scope: !1702)
!2463 = !DILocation(line: 168, column: 3, scope: !1702)
!2464 = !DILocation(line: 168, column: 17, scope: !2465)
!2465 = !DILexicalBlockFile(scope: !1702, file: !1, discriminator: 1)
!2466 = !DILocation(line: 172, column: 5, scope: !2467)
!2467 = distinct !DILexicalBlock(scope: !1702, file: !1, line: 168, column: 17)
!2468 = !DILocation(line: 175, column: 5, scope: !2467)
!2469 = !DILocation(line: 175, column: 11, scope: !2467)
!2470 = !DILocation(line: 175, column: 20, scope: !2467)
!2471 = !DILocation(line: 175, column: 32, scope: !2467)
!2472 = !DILocation(line: 176, column: 5, scope: !2467)
!2473 = !DILocation(line: 179, column: 5, scope: !2467)
!2474 = !DILocation(line: 179, column: 11, scope: !2467)
!2475 = !DILocation(line: 179, column: 20, scope: !2467)
!2476 = !DILocation(line: 179, column: 36, scope: !2467)
!2477 = !DILocation(line: 180, column: 5, scope: !2467)
!2478 = !DILocation(line: 183, column: 5, scope: !2467)
!2479 = !DILocation(line: 183, column: 11, scope: !2467)
!2480 = !DILocation(line: 183, column: 20, scope: !2467)
!2481 = !DILocation(line: 183, column: 35, scope: !2467)
!2482 = !DILocation(line: 183, column: 35, scope: !2483)
!2483 = !DILexicalBlockFile(scope: !2467, file: !1, discriminator: 1)
!2484 = !DILocation(line: 184, column: 5, scope: !2467)
!2485 = !DILocation(line: 188, column: 7, scope: !2467)
!2486 = !DILocation(line: 187, column: 5, scope: !2467)
!2487 = !DILocation(line: 187, column: 11, scope: !2467)
!2488 = !DILocation(line: 187, column: 20, scope: !2467)
!2489 = !DILocation(line: 187, column: 31, scope: !2467)
!2490 = !DILocation(line: 189, column: 5, scope: !2467)
!2491 = !DILocation(line: 192, column: 7, scope: !2467)
!2492 = !DILocation(line: 191, column: 5, scope: !2467)
!2493 = !DILocation(line: 191, column: 11, scope: !2467)
!2494 = !DILocation(line: 191, column: 20, scope: !2467)
!2495 = !DILocation(line: 191, column: 30, scope: !2467)
!2496 = !DILocation(line: 193, column: 5, scope: !2467)
!2497 = !DILocation(line: 196, column: 7, scope: !2467)
!2498 = !DILocation(line: 195, column: 5, scope: !2467)
!2499 = !DILocation(line: 195, column: 11, scope: !2467)
!2500 = !DILocation(line: 195, column: 20, scope: !2467)
!2501 = !DILocation(line: 195, column: 33, scope: !2467)
!2502 = !DILocation(line: 197, column: 5, scope: !2467)
!2503 = !DILocation(line: 200, column: 7, scope: !2467)
!2504 = !DILocation(line: 199, column: 5, scope: !2467)
!2505 = !DILocation(line: 199, column: 11, scope: !2467)
!2506 = !DILocation(line: 199, column: 20, scope: !2467)
!2507 = !DILocation(line: 199, column: 34, scope: !2467)
!2508 = !DILocation(line: 201, column: 5, scope: !2467)
!2509 = !DILocation(line: 204, column: 7, scope: !2467)
!2510 = !DILocation(line: 203, column: 5, scope: !2467)
!2511 = !DILocation(line: 203, column: 11, scope: !2467)
!2512 = !DILocation(line: 203, column: 20, scope: !2467)
!2513 = !DILocation(line: 203, column: 36, scope: !2467)
!2514 = !DILocation(line: 205, column: 5, scope: !2467)
!2515 = !DILocation(line: 208, column: 5, scope: !2467)
!2516 = !DILocation(line: 210, column: 33, scope: !2467)
!2517 = !DILocation(line: 210, column: 5, scope: !2467)
!2518 = !DILocation(line: 210, column: 11, scope: !2467)
!2519 = !DILocation(line: 210, column: 20, scope: !2467)
!2520 = !DILocation(line: 210, column: 31, scope: !2467)
!2521 = !DILocation(line: 211, column: 5, scope: !2467)
!2522 = !DILocation(line: 213, column: 1, scope: !1702)
!2523 = !DILocalVariable(name: "data", arg: 1, scope: !1706, file: !1, line: 215, type: !544)
!2524 = !DILocation(line: 215, column: 42, scope: !1706)
!2525 = !DILocation(line: 217, column: 3, scope: !1706)
!2526 = !DILocation(line: 217, column: 9, scope: !1706)
!2527 = !DILocation(line: 217, column: 18, scope: !1706)
!2528 = !DILocation(line: 217, column: 28, scope: !1706)
!2529 = !DILocation(line: 218, column: 3, scope: !1706)
!2530 = !DILocation(line: 218, column: 9, scope: !1706)
!2531 = !DILocation(line: 218, column: 18, scope: !1706)
!2532 = !DILocation(line: 218, column: 26, scope: !1706)
!2533 = !DILocation(line: 218, column: 26, scope: !2534)
!2534 = !DILexicalBlockFile(scope: !1706, file: !1, discriminator: 1)
!2535 = !DILocation(line: 219, column: 3, scope: !1706)
!2536 = !DILocation(line: 219, column: 9, scope: !1706)
!2537 = !DILocation(line: 219, column: 18, scope: !1706)
!2538 = !DILocation(line: 219, column: 33, scope: !1706)
!2539 = !DILocation(line: 219, column: 40, scope: !1706)
!2540 = !DILocation(line: 220, column: 3, scope: !1706)
!2541 = !DILocation(line: 220, column: 9, scope: !1706)
!2542 = !DILocation(line: 220, column: 18, scope: !1706)
!2543 = !DILocation(line: 220, column: 33, scope: !1706)
!2544 = !DILocation(line: 220, column: 41, scope: !1706)
!2545 = !DILocation(line: 221, column: 3, scope: !1706)
!2546 = !DILocation(line: 221, column: 9, scope: !1706)
!2547 = !DILocation(line: 221, column: 18, scope: !1706)
!2548 = !DILocation(line: 221, column: 33, scope: !1706)
!2549 = !DILocation(line: 221, column: 40, scope: !1706)
!2550 = !DILocation(line: 222, column: 3, scope: !1706)
!2551 = !DILocation(line: 222, column: 9, scope: !1706)
!2552 = !DILocation(line: 222, column: 18, scope: !1706)
!2553 = !DILocation(line: 222, column: 33, scope: !1706)
!2554 = !DILocation(line: 222, column: 41, scope: !1706)
!2555 = !DILocation(line: 224, column: 3, scope: !1706)
!2556 = !DILocation(line: 224, column: 9, scope: !1706)
!2557 = !DILocation(line: 224, column: 18, scope: !1706)
!2558 = !DILocation(line: 224, column: 24, scope: !1706)
!2559 = !DILocation(line: 225, column: 1, scope: !1706)
!2560 = !DILocalVariable(name: "cursize", arg: 1, scope: !1707, file: !1, line: 246, type: !189)
!2561 = !DILocation(line: 246, column: 40, scope: !1707)
!2562 = !DILocalVariable(name: "startsize", arg: 2, scope: !1707, file: !1, line: 247, type: !189)
!2563 = !DILocation(line: 247, column: 40, scope: !1707)
!2564 = !DILocalVariable(name: "limit", arg: 3, scope: !1707, file: !1, line: 248, type: !189)
!2565 = !DILocation(line: 248, column: 40, scope: !1707)
!2566 = !DILocalVariable(name: "start", arg: 4, scope: !1707, file: !1, line: 249, type: !201)
!2567 = !DILocation(line: 249, column: 44, scope: !1707)
!2568 = !DILocalVariable(name: "now", arg: 5, scope: !1707, file: !1, line: 250, type: !201)
!2569 = !DILocation(line: 250, column: 44, scope: !1707)
!2570 = !DILocalVariable(name: "size", scope: !1707, file: !1, line: 252, type: !189)
!2571 = !DILocation(line: 252, column: 14, scope: !1707)
!2572 = !DILocation(line: 252, column: 21, scope: !1707)
!2573 = !DILocation(line: 252, column: 31, scope: !1707)
!2574 = !DILocation(line: 252, column: 29, scope: !1707)
!2575 = !DILocalVariable(name: "minimum", scope: !1707, file: !1, line: 253, type: !242)
!2576 = !DILocation(line: 253, column: 10, scope: !1707)
!2577 = !DILocalVariable(name: "actual", scope: !1707, file: !1, line: 254, type: !242)
!2578 = !DILocation(line: 254, column: 10, scope: !1707)
!2579 = !DILocation(line: 257, column: 12, scope: !2580)
!2580 = distinct !DILexicalBlock(scope: !1707, file: !1, line: 257, column: 6)
!2581 = !DILocation(line: 257, column: 19, scope: !2580)
!2582 = !DILocation(line: 257, column: 24, scope: !2580)
!2583 = !DILocation(line: 257, column: 33, scope: !2584)
!2584 = !DILexicalBlockFile(scope: !2580, file: !1, discriminator: 1)
!2585 = !DILocation(line: 257, column: 41, scope: !2584)
!2586 = !DILocation(line: 257, column: 6, scope: !2584)
!2587 = !DILocation(line: 258, column: 5, scope: !2580)
!2588 = !DILocation(line: 261, column: 6, scope: !2589)
!2589 = distinct !DILexicalBlock(scope: !1707, file: !1, line: 261, column: 6)
!2590 = !DILocation(line: 261, column: 13, scope: !2589)
!2591 = !DILocation(line: 261, column: 11, scope: !2589)
!2592 = !DILocation(line: 261, column: 6, scope: !1707)
!2593 = !DILocation(line: 262, column: 5, scope: !2589)
!2594 = !DILocation(line: 264, column: 44, scope: !1707)
!2595 = !DILocation(line: 264, column: 42, scope: !1707)
!2596 = !DILocation(line: 264, column: 51, scope: !1707)
!2597 = !DILocation(line: 264, column: 49, scope: !1707)
!2598 = !DILocation(line: 264, column: 11, scope: !1707)
!2599 = !DILocation(line: 265, column: 12, scope: !1707)
!2600 = !DILocation(line: 265, column: 10, scope: !1707)
!2601 = !DILocation(line: 267, column: 6, scope: !2602)
!2602 = distinct !DILexicalBlock(scope: !1707, file: !1, line: 267, column: 6)
!2603 = !DILocation(line: 267, column: 15, scope: !2602)
!2604 = !DILocation(line: 267, column: 13, scope: !2602)
!2605 = !DILocation(line: 267, column: 6, scope: !1707)
!2606 = !DILocation(line: 269, column: 19, scope: !2602)
!2607 = !DILocation(line: 269, column: 29, scope: !2602)
!2608 = !DILocation(line: 269, column: 27, scope: !2602)
!2609 = !DILocation(line: 269, column: 5, scope: !2602)
!2610 = !DILocation(line: 271, column: 3, scope: !1707)
!2611 = !DILocation(line: 272, column: 1, scope: !1707)
!2612 = !DILocalVariable(name: "data", arg: 1, scope: !1710, file: !1, line: 274, type: !544)
!2613 = !DILocation(line: 274, column: 52, scope: !1710)
!2614 = !DILocalVariable(name: "size", arg: 2, scope: !1710, file: !1, line: 274, type: !189)
!2615 = !DILocation(line: 274, column: 69, scope: !1710)
!2616 = !DILocalVariable(name: "now", scope: !1710, file: !1, line: 276, type: !201)
!2617 = !DILocation(line: 276, column: 18, scope: !1710)
!2618 = !DILocation(line: 276, column: 24, scope: !1710)
!2619 = !DILocation(line: 278, column: 31, scope: !1710)
!2620 = !DILocation(line: 278, column: 3, scope: !1710)
!2621 = !DILocation(line: 278, column: 9, scope: !1710)
!2622 = !DILocation(line: 278, column: 18, scope: !1710)
!2623 = !DILocation(line: 278, column: 29, scope: !1710)
!2624 = !DILocation(line: 281, column: 7, scope: !2625)
!2625 = distinct !DILexicalBlock(scope: !1710, file: !1, line: 281, column: 6)
!2626 = !DILocation(line: 281, column: 13, scope: !2625)
!2627 = !DILocation(line: 281, column: 17, scope: !2625)
!2628 = !DILocation(line: 281, column: 32, scope: !2625)
!2629 = !DILocation(line: 281, column: 37, scope: !2625)
!2630 = !DILocation(line: 282, column: 30, scope: !2625)
!2631 = !DILocation(line: 282, column: 36, scope: !2625)
!2632 = !DILocation(line: 282, column: 45, scope: !2625)
!2633 = !DILocation(line: 283, column: 30, scope: !2625)
!2634 = !DILocation(line: 283, column: 36, scope: !2625)
!2635 = !DILocation(line: 283, column: 45, scope: !2625)
!2636 = !DILocation(line: 284, column: 30, scope: !2625)
!2637 = !DILocation(line: 284, column: 36, scope: !2625)
!2638 = !DILocation(line: 284, column: 40, scope: !2625)
!2639 = !DILocation(line: 285, column: 30, scope: !2625)
!2640 = !DILocation(line: 285, column: 36, scope: !2625)
!2641 = !DILocation(line: 285, column: 45, scope: !2625)
!2642 = !DILocation(line: 282, column: 7, scope: !2625)
!2643 = !DILocation(line: 286, column: 35, scope: !2625)
!2644 = !DILocation(line: 281, column: 6, scope: !2645)
!2645 = !DILexicalBlockFile(scope: !1710, file: !1, discriminator: 1)
!2646 = !DILocation(line: 287, column: 5, scope: !2647)
!2647 = distinct !DILexicalBlock(scope: !2625, file: !1, line: 286, column: 42)
!2648 = !DILocation(line: 287, column: 11, scope: !2647)
!2649 = !DILocation(line: 287, column: 20, scope: !2647)
!2650 = !DILocation(line: 287, column: 37, scope: !2647)
!2651 = !DILocation(line: 288, column: 36, scope: !2647)
!2652 = !DILocation(line: 288, column: 5, scope: !2647)
!2653 = !DILocation(line: 288, column: 11, scope: !2647)
!2654 = !DILocation(line: 288, column: 20, scope: !2647)
!2655 = !DILocation(line: 288, column: 34, scope: !2647)
!2656 = !DILocation(line: 289, column: 3, scope: !2647)
!2657 = !DILocation(line: 290, column: 1, scope: !1710)
!2658 = !DILocalVariable(name: "data", arg: 1, scope: !1713, file: !1, line: 292, type: !544)
!2659 = !DILocation(line: 292, column: 50, scope: !1713)
!2660 = !DILocalVariable(name: "size", arg: 2, scope: !1713, file: !1, line: 292, type: !189)
!2661 = !DILocation(line: 292, column: 67, scope: !1713)
!2662 = !DILocalVariable(name: "now", scope: !1713, file: !1, line: 294, type: !201)
!2663 = !DILocation(line: 294, column: 18, scope: !1713)
!2664 = !DILocation(line: 294, column: 24, scope: !1713)
!2665 = !DILocation(line: 296, column: 29, scope: !1713)
!2666 = !DILocation(line: 296, column: 3, scope: !1713)
!2667 = !DILocation(line: 296, column: 9, scope: !1713)
!2668 = !DILocation(line: 296, column: 18, scope: !1713)
!2669 = !DILocation(line: 296, column: 27, scope: !1713)
!2670 = !DILocation(line: 299, column: 7, scope: !2671)
!2671 = distinct !DILexicalBlock(scope: !1713, file: !1, line: 299, column: 6)
!2672 = !DILocation(line: 299, column: 13, scope: !2671)
!2673 = !DILocation(line: 299, column: 17, scope: !2671)
!2674 = !DILocation(line: 299, column: 32, scope: !2671)
!2675 = !DILocation(line: 299, column: 37, scope: !2671)
!2676 = !DILocation(line: 300, column: 30, scope: !2671)
!2677 = !DILocation(line: 300, column: 36, scope: !2671)
!2678 = !DILocation(line: 300, column: 45, scope: !2671)
!2679 = !DILocation(line: 301, column: 30, scope: !2671)
!2680 = !DILocation(line: 301, column: 36, scope: !2671)
!2681 = !DILocation(line: 301, column: 45, scope: !2671)
!2682 = !DILocation(line: 302, column: 30, scope: !2671)
!2683 = !DILocation(line: 302, column: 36, scope: !2671)
!2684 = !DILocation(line: 302, column: 40, scope: !2671)
!2685 = !DILocation(line: 303, column: 30, scope: !2671)
!2686 = !DILocation(line: 303, column: 36, scope: !2671)
!2687 = !DILocation(line: 303, column: 45, scope: !2671)
!2688 = !DILocation(line: 300, column: 7, scope: !2671)
!2689 = !DILocation(line: 304, column: 35, scope: !2671)
!2690 = !DILocation(line: 299, column: 6, scope: !2691)
!2691 = !DILexicalBlockFile(scope: !1713, file: !1, discriminator: 1)
!2692 = !DILocation(line: 305, column: 5, scope: !2693)
!2693 = distinct !DILexicalBlock(scope: !2671, file: !1, line: 304, column: 42)
!2694 = !DILocation(line: 305, column: 11, scope: !2693)
!2695 = !DILocation(line: 305, column: 20, scope: !2693)
!2696 = !DILocation(line: 305, column: 37, scope: !2693)
!2697 = !DILocation(line: 306, column: 36, scope: !2693)
!2698 = !DILocation(line: 306, column: 5, scope: !2693)
!2699 = !DILocation(line: 306, column: 11, scope: !2693)
!2700 = !DILocation(line: 306, column: 20, scope: !2693)
!2701 = !DILocation(line: 306, column: 34, scope: !2693)
!2702 = !DILocation(line: 307, column: 3, scope: !2693)
!2703 = !DILocation(line: 308, column: 1, scope: !1713)
!2704 = !DILocalVariable(name: "r", arg: 1, scope: !1717, file: !1, line: 32, type: !215)
!2705 = !DILocation(line: 32, column: 28, scope: !1717)
!2706 = !DILocalVariable(name: "seconds", arg: 2, scope: !1717, file: !1, line: 32, type: !189)
!2707 = !DILocation(line: 32, column: 42, scope: !1717)
!2708 = !DILocalVariable(name: "d", scope: !1717, file: !1, line: 34, type: !189)
!2709 = !DILocation(line: 34, column: 14, scope: !1717)
!2710 = !DILocalVariable(name: "h", scope: !1717, file: !1, line: 34, type: !189)
!2711 = !DILocation(line: 34, column: 17, scope: !1717)
!2712 = !DILocalVariable(name: "m", scope: !1717, file: !1, line: 34, type: !189)
!2713 = !DILocation(line: 34, column: 20, scope: !1717)
!2714 = !DILocalVariable(name: "s", scope: !1717, file: !1, line: 34, type: !189)
!2715 = !DILocation(line: 34, column: 23, scope: !1717)
!2716 = !DILocation(line: 35, column: 6, scope: !2717)
!2717 = distinct !DILexicalBlock(scope: !1717, file: !1, line: 35, column: 6)
!2718 = !DILocation(line: 35, column: 14, scope: !2717)
!2719 = !DILocation(line: 35, column: 6, scope: !1717)
!2720 = !DILocation(line: 36, column: 12, scope: !2721)
!2721 = distinct !DILexicalBlock(scope: !2717, file: !1, line: 35, column: 20)
!2722 = !DILocation(line: 36, column: 5, scope: !2721)
!2723 = !DILocation(line: 37, column: 5, scope: !2721)
!2724 = !DILocation(line: 39, column: 7, scope: !1717)
!2725 = !DILocation(line: 39, column: 15, scope: !1717)
!2726 = !DILocation(line: 39, column: 5, scope: !1717)
!2727 = !DILocation(line: 40, column: 6, scope: !2728)
!2728 = distinct !DILexicalBlock(scope: !1717, file: !1, line: 40, column: 6)
!2729 = !DILocation(line: 40, column: 8, scope: !2728)
!2730 = !DILocation(line: 40, column: 6, scope: !1717)
!2731 = !DILocation(line: 41, column: 10, scope: !2732)
!2732 = distinct !DILexicalBlock(scope: !2728, file: !1, line: 40, column: 29)
!2733 = !DILocation(line: 41, column: 21, scope: !2732)
!2734 = !DILocation(line: 41, column: 22, scope: !2732)
!2735 = !DILocation(line: 41, column: 18, scope: !2732)
!2736 = !DILocation(line: 41, column: 44, scope: !2732)
!2737 = !DILocation(line: 41, column: 7, scope: !2732)
!2738 = !DILocation(line: 42, column: 10, scope: !2732)
!2739 = !DILocation(line: 42, column: 21, scope: !2732)
!2740 = !DILocation(line: 42, column: 22, scope: !2732)
!2741 = !DILocation(line: 42, column: 18, scope: !2732)
!2742 = !DILocation(line: 42, column: 47, scope: !2732)
!2743 = !DILocation(line: 42, column: 48, scope: !2732)
!2744 = !DILocation(line: 42, column: 44, scope: !2732)
!2745 = !DILocation(line: 42, column: 7, scope: !2732)
!2746 = !DILocation(line: 43, column: 14, scope: !2732)
!2747 = !DILocation(line: 44, column: 45, scope: !2732)
!2748 = !DILocation(line: 44, column: 48, scope: !2732)
!2749 = !DILocation(line: 44, column: 51, scope: !2732)
!2750 = !DILocation(line: 43, column: 5, scope: !2732)
!2751 = !DILocation(line: 45, column: 3, scope: !2732)
!2752 = !DILocation(line: 49, column: 9, scope: !2753)
!2753 = distinct !DILexicalBlock(scope: !2728, file: !1, line: 46, column: 8)
!2754 = !DILocation(line: 49, column: 17, scope: !2753)
!2755 = !DILocation(line: 49, column: 7, scope: !2753)
!2756 = !DILocation(line: 50, column: 10, scope: !2753)
!2757 = !DILocation(line: 50, column: 21, scope: !2753)
!2758 = !DILocation(line: 50, column: 22, scope: !2753)
!2759 = !DILocation(line: 50, column: 18, scope: !2753)
!2760 = !DILocation(line: 50, column: 45, scope: !2753)
!2761 = !DILocation(line: 50, column: 7, scope: !2753)
!2762 = !DILocation(line: 51, column: 8, scope: !2763)
!2763 = distinct !DILexicalBlock(scope: !2753, file: !1, line: 51, column: 8)
!2764 = !DILocation(line: 51, column: 10, scope: !2763)
!2765 = !DILocation(line: 51, column: 8, scope: !2753)
!2766 = !DILocation(line: 52, column: 16, scope: !2763)
!2767 = !DILocation(line: 53, column: 52, scope: !2763)
!2768 = !DILocation(line: 53, column: 55, scope: !2763)
!2769 = !DILocation(line: 52, column: 7, scope: !2763)
!2770 = !DILocation(line: 55, column: 16, scope: !2763)
!2771 = !DILocation(line: 55, column: 55, scope: !2763)
!2772 = !DILocation(line: 55, column: 7, scope: !2763)
!2773 = !DILocation(line: 57, column: 1, scope: !1717)
!2774 = !DILocalVariable(name: "bytes", arg: 1, scope: !1720, file: !1, line: 62, type: !189)
!2775 = !DILocation(line: 62, column: 34, scope: !1720)
!2776 = !DILocalVariable(name: "max5", arg: 2, scope: !1720, file: !1, line: 62, type: !215)
!2777 = !DILocation(line: 62, column: 47, scope: !1720)
!2778 = !DILocation(line: 70, column: 6, scope: !2779)
!2779 = distinct !DILexicalBlock(scope: !1720, file: !1, line: 70, column: 6)
!2780 = !DILocation(line: 70, column: 12, scope: !2779)
!2781 = !DILocation(line: 70, column: 6, scope: !1720)
!2782 = !DILocation(line: 71, column: 14, scope: !2779)
!2783 = !DILocation(line: 71, column: 52, scope: !2779)
!2784 = !DILocation(line: 71, column: 5, scope: !2779)
!2785 = !DILocation(line: 73, column: 11, scope: !2786)
!2786 = distinct !DILexicalBlock(scope: !2779, file: !1, line: 73, column: 11)
!2787 = !DILocation(line: 73, column: 17, scope: !2786)
!2788 = !DILocation(line: 73, column: 11, scope: !2779)
!2789 = !DILocation(line: 74, column: 14, scope: !2786)
!2790 = !DILocation(line: 74, column: 56, scope: !2786)
!2791 = !DILocation(line: 74, column: 61, scope: !2786)
!2792 = !DILocation(line: 74, column: 5, scope: !2786)
!2793 = !DILocation(line: 76, column: 11, scope: !2794)
!2794 = distinct !DILexicalBlock(scope: !2786, file: !1, line: 76, column: 11)
!2795 = !DILocation(line: 76, column: 17, scope: !2794)
!2796 = !DILocation(line: 76, column: 11, scope: !2786)
!2797 = !DILocation(line: 78, column: 14, scope: !2794)
!2798 = !DILocation(line: 79, column: 42, scope: !2794)
!2799 = !DILocation(line: 79, column: 47, scope: !2794)
!2800 = !DILocation(line: 80, column: 15, scope: !2794)
!2801 = !DILocation(line: 80, column: 20, scope: !2794)
!2802 = !DILocation(line: 80, column: 35, scope: !2794)
!2803 = !DILocation(line: 78, column: 5, scope: !2794)
!2804 = !DILocation(line: 84, column: 11, scope: !2805)
!2805 = distinct !DILexicalBlock(scope: !2794, file: !1, line: 84, column: 11)
!2806 = !DILocation(line: 84, column: 17, scope: !2805)
!2807 = !DILocation(line: 84, column: 11, scope: !2794)
!2808 = !DILocation(line: 86, column: 14, scope: !2805)
!2809 = !DILocation(line: 86, column: 56, scope: !2805)
!2810 = !DILocation(line: 86, column: 61, scope: !2805)
!2811 = !DILocation(line: 86, column: 5, scope: !2805)
!2812 = !DILocation(line: 88, column: 11, scope: !2813)
!2813 = distinct !DILexicalBlock(scope: !2805, file: !1, line: 88, column: 11)
!2814 = !DILocation(line: 88, column: 17, scope: !2813)
!2815 = !DILocation(line: 88, column: 11, scope: !2805)
!2816 = !DILocation(line: 90, column: 14, scope: !2813)
!2817 = !DILocation(line: 91, column: 42, scope: !2813)
!2818 = !DILocation(line: 91, column: 47, scope: !2813)
!2819 = !DILocation(line: 92, column: 15, scope: !2813)
!2820 = !DILocation(line: 92, column: 20, scope: !2813)
!2821 = !DILocation(line: 92, column: 35, scope: !2813)
!2822 = !DILocation(line: 90, column: 5, scope: !2813)
!2823 = !DILocation(line: 94, column: 11, scope: !2824)
!2824 = distinct !DILexicalBlock(scope: !2813, file: !1, line: 94, column: 11)
!2825 = !DILocation(line: 94, column: 17, scope: !2824)
!2826 = !DILocation(line: 94, column: 11, scope: !2813)
!2827 = !DILocation(line: 96, column: 14, scope: !2824)
!2828 = !DILocation(line: 96, column: 56, scope: !2824)
!2829 = !DILocation(line: 96, column: 61, scope: !2824)
!2830 = !DILocation(line: 96, column: 5, scope: !2824)
!2831 = !DILocation(line: 98, column: 11, scope: !2832)
!2832 = distinct !DILexicalBlock(scope: !2824, file: !1, line: 98, column: 11)
!2833 = !DILocation(line: 98, column: 17, scope: !2832)
!2834 = !DILocation(line: 98, column: 11, scope: !2824)
!2835 = !DILocation(line: 100, column: 14, scope: !2832)
!2836 = !DILocation(line: 100, column: 56, scope: !2832)
!2837 = !DILocation(line: 100, column: 61, scope: !2832)
!2838 = !DILocation(line: 100, column: 5, scope: !2832)
!2839 = !DILocation(line: 104, column: 14, scope: !2832)
!2840 = !DILocation(line: 104, column: 56, scope: !2832)
!2841 = !DILocation(line: 104, column: 61, scope: !2832)
!2842 = !DILocation(line: 104, column: 5, scope: !2832)
!2843 = !DILocation(line: 116, column: 10, scope: !1720)
!2844 = !DILocation(line: 116, column: 3, scope: !1720)
