; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/getinfo.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

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
%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%union.anon.1 = type { i64* }
%union.anon.2 = type { %struct.curl_certinfo* }

@Curl_cfree = external global void (i8*)*, align 8
@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

; Function Attrs: nounwind uwtable
define i32 @Curl_initinfo(%struct.Curl_easy* %data) #0 !dbg !1803 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %pro = alloca %struct.Progress*, align 8
  %info = alloca %struct.PureInfo*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1832, metadata !1833), !dbg !1834
  call void @llvm.dbg.declare(metadata %struct.Progress** %pro, metadata !1835, metadata !1833), !dbg !1837
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1838
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 16, !dbg !1839
  store %struct.Progress* %progress, %struct.Progress** %pro, align 8, !dbg !1837
  call void @llvm.dbg.declare(metadata %struct.PureInfo** %info, metadata !1840, metadata !1833), !dbg !1842
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1843
  %info1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 19, !dbg !1844
  store %struct.PureInfo* %info1, %struct.PureInfo** %info, align 8, !dbg !1842
  %2 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1845
  %t_nslookup = getelementptr inbounds %struct.Progress, %struct.Progress* %2, i32 0, i32 12, !dbg !1846
  store double 0.000000e+00, double* %t_nslookup, align 8, !dbg !1847
  %3 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1848
  %t_connect = getelementptr inbounds %struct.Progress, %struct.Progress* %3, i32 0, i32 13, !dbg !1849
  store double 0.000000e+00, double* %t_connect, align 8, !dbg !1850
  %4 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1851
  %t_appconnect = getelementptr inbounds %struct.Progress, %struct.Progress* %4, i32 0, i32 14, !dbg !1852
  store double 0.000000e+00, double* %t_appconnect, align 8, !dbg !1853
  %5 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1854
  %t_pretransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %5, i32 0, i32 15, !dbg !1855
  store double 0.000000e+00, double* %t_pretransfer, align 8, !dbg !1856
  %6 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1857
  %t_starttransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %6, i32 0, i32 16, !dbg !1858
  store double 0.000000e+00, double* %t_starttransfer, align 8, !dbg !1859
  %7 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1860
  %timespent = getelementptr inbounds %struct.Progress, %struct.Progress* %7, i32 0, i32 9, !dbg !1861
  store double 0.000000e+00, double* %timespent, align 8, !dbg !1862
  %8 = load %struct.Progress*, %struct.Progress** %pro, align 8, !dbg !1863
  %t_redirect = getelementptr inbounds %struct.Progress, %struct.Progress* %8, i32 0, i32 17, !dbg !1864
  store double 0.000000e+00, double* %t_redirect, align 8, !dbg !1865
  %9 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1866
  %httpcode = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %9, i32 0, i32 0, !dbg !1867
  store i32 0, i32* %httpcode, align 8, !dbg !1868
  %10 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1869
  %httpproxycode = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %10, i32 0, i32 1, !dbg !1870
  store i32 0, i32* %httpproxycode, align 4, !dbg !1871
  %11 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1872
  %httpversion = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %11, i32 0, i32 2, !dbg !1873
  store i32 0, i32* %httpversion, align 8, !dbg !1874
  %12 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1875
  %filetime = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %12, i32 0, i32 3, !dbg !1876
  store i64 -1, i64* %filetime, align 8, !dbg !1877
  %13 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1878
  %timecond = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %13, i32 0, i32 4, !dbg !1879
  store i8 0, i8* %timecond, align 8, !dbg !1880
  %14 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1881
  %header_size = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %14, i32 0, i32 5, !dbg !1882
  store i64 0, i64* %header_size, align 8, !dbg !1883
  %15 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1884
  %request_size = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %15, i32 0, i32 6, !dbg !1885
  store i64 0, i64* %request_size, align 8, !dbg !1886
  %16 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1887
  %proxyauthavail = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %16, i32 0, i32 7, !dbg !1888
  store i64 0, i64* %proxyauthavail, align 8, !dbg !1889
  %17 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1890
  %httpauthavail = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %17, i32 0, i32 8, !dbg !1891
  store i64 0, i64* %httpauthavail, align 8, !dbg !1892
  %18 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1893
  %numconnects = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %18, i32 0, i32 9, !dbg !1894
  store i64 0, i64* %numconnects, align 8, !dbg !1895
  %19 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1896
  %20 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1896
  %contenttype = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %20, i32 0, i32 10, !dbg !1896
  %21 = load i8*, i8** %contenttype, align 8, !dbg !1896
  call void %19(i8* %21), !dbg !1896
  %22 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1897
  %contenttype2 = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %22, i32 0, i32 10, !dbg !1898
  store i8* null, i8** %contenttype2, align 8, !dbg !1899
  %23 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1900
  %24 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1900
  %wouldredirect = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %24, i32 0, i32 11, !dbg !1900
  %25 = load i8*, i8** %wouldredirect, align 8, !dbg !1900
  call void %23(i8* %25), !dbg !1900
  %26 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1901
  %wouldredirect3 = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %26, i32 0, i32 11, !dbg !1902
  store i8* null, i8** %wouldredirect3, align 8, !dbg !1903
  %27 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1904
  %conn_primary_ip = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %27, i32 0, i32 12, !dbg !1905
  %arrayidx = getelementptr inbounds [46 x i8], [46 x i8]* %conn_primary_ip, i64 0, i64 0, !dbg !1904
  store i8 0, i8* %arrayidx, align 8, !dbg !1906
  %28 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1907
  %conn_local_ip = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %28, i32 0, i32 14, !dbg !1908
  %arrayidx4 = getelementptr inbounds [46 x i8], [46 x i8]* %conn_local_ip, i64 0, i64 0, !dbg !1907
  store i8 0, i8* %arrayidx4, align 8, !dbg !1909
  %29 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1910
  %conn_primary_port = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %29, i32 0, i32 13, !dbg !1911
  store i64 0, i64* %conn_primary_port, align 8, !dbg !1912
  %30 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1913
  %conn_local_port = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %30, i32 0, i32 15, !dbg !1914
  store i64 0, i64* %conn_local_port, align 8, !dbg !1915
  %31 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1916
  %conn_scheme = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %31, i32 0, i32 16, !dbg !1917
  store i8* null, i8** %conn_scheme, align 8, !dbg !1918
  %32 = load %struct.PureInfo*, %struct.PureInfo** %info, align 8, !dbg !1919
  %conn_protocol = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %32, i32 0, i32 17, !dbg !1920
  store i32 0, i32* %conn_protocol, align 8, !dbg !1921
  ret i32 0, !dbg !1922
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_getinfo(%struct.Curl_easy* %data, i32 %info, ...) #0 !dbg !1807 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %arg = alloca [1 x %struct.__va_list_tag], align 16
  %param_longp = alloca i64*, align 8
  %param_doublep = alloca double*, align 8
  %param_charp = alloca i8**, align 8
  %param_slistp = alloca %struct.curl_slist**, align 8
  %param_socketp = alloca i32*, align 8
  %type = alloca i32, align 4
  %result = alloca i32, align 4
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1923, metadata !1833), !dbg !1924
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !1925, metadata !1833), !dbg !1926
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %arg, metadata !1927, metadata !1833), !dbg !1939
  call void @llvm.dbg.declare(metadata i64** %param_longp, metadata !1940, metadata !1833), !dbg !1941
  store i64* null, i64** %param_longp, align 8, !dbg !1941
  call void @llvm.dbg.declare(metadata double** %param_doublep, metadata !1942, metadata !1833), !dbg !1943
  store double* null, double** %param_doublep, align 8, !dbg !1943
  call void @llvm.dbg.declare(metadata i8*** %param_charp, metadata !1944, metadata !1833), !dbg !1945
  store i8** null, i8*** %param_charp, align 8, !dbg !1945
  call void @llvm.dbg.declare(metadata %struct.curl_slist*** %param_slistp, metadata !1946, metadata !1833), !dbg !1947
  store %struct.curl_slist** null, %struct.curl_slist*** %param_slistp, align 8, !dbg !1947
  call void @llvm.dbg.declare(metadata i32** %param_socketp, metadata !1948, metadata !1833), !dbg !1949
  store i32* null, i32** %param_socketp, align 8, !dbg !1949
  call void @llvm.dbg.declare(metadata i32* %type, metadata !1950, metadata !1833), !dbg !1951
  call void @llvm.dbg.declare(metadata i32* %result, metadata !1952, metadata !1833), !dbg !1953
  store i32 48, i32* %result, align 4, !dbg !1953
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1954
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !1954
  br i1 %tobool, label %if.end, label %if.then, !dbg !1956

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %result, align 4, !dbg !1957
  store i32 %1, i32* %retval, align 4, !dbg !1958
  br label %return, !dbg !1958

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !1959
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1959
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1959
  %2 = load i32, i32* %info.addr, align 4, !dbg !1960
  %and = and i32 15728640, %2, !dbg !1961
  store i32 %and, i32* %type, align 4, !dbg !1962
  %3 = load i32, i32* %type, align 4, !dbg !1963
  switch i32 %3, label %sw.default [
    i32 1048576, label %sw.bb
    i32 2097152, label %sw.bb6
    i32 3145728, label %sw.bb23
    i32 4194304, label %sw.bb40
    i32 5242880, label %sw.bb57
  ], !dbg !1964

sw.bb:                                            ; preds = %if.end
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !1965
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 0, !dbg !1965
  %gp_offset = load i32, i32* %gp_offset_p, align 16, !dbg !1965
  %fits_in_gp = icmp ule i32 %gp_offset, 40, !dbg !1965
  br i1 %fits_in_gp, label %vaarg.in_reg, label %vaarg.in_mem, !dbg !1965

vaarg.in_reg:                                     ; preds = %sw.bb
  %4 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 3, !dbg !1967
  %reg_save_area = load i8*, i8** %4, align 16, !dbg !1967
  %5 = getelementptr i8, i8* %reg_save_area, i32 %gp_offset, !dbg !1967
  %6 = bitcast i8* %5 to i8***, !dbg !1967
  %7 = add i32 %gp_offset, 8, !dbg !1967
  store i32 %7, i32* %gp_offset_p, align 16, !dbg !1967
  br label %vaarg.end, !dbg !1967

vaarg.in_mem:                                     ; preds = %sw.bb
  %overflow_arg_area_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 2, !dbg !1969
  %overflow_arg_area = load i8*, i8** %overflow_arg_area_p, align 8, !dbg !1969
  %8 = bitcast i8* %overflow_arg_area to i8***, !dbg !1969
  %overflow_arg_area.next = getelementptr i8, i8* %overflow_arg_area, i32 8, !dbg !1969
  store i8* %overflow_arg_area.next, i8** %overflow_arg_area_p, align 8, !dbg !1969
  br label %vaarg.end, !dbg !1969

vaarg.end:                                        ; preds = %vaarg.in_mem, %vaarg.in_reg
  %vaarg.addr = phi i8*** [ %6, %vaarg.in_reg ], [ %8, %vaarg.in_mem ], !dbg !1971
  %9 = load i8**, i8*** %vaarg.addr, align 8, !dbg !1971
  store i8** %9, i8*** %param_charp, align 8, !dbg !1973
  %10 = load i8**, i8*** %param_charp, align 8, !dbg !1974
  %tobool3 = icmp ne i8** %10, null, !dbg !1974
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !1976

if.then4:                                         ; preds = %vaarg.end
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1977
  %12 = load i32, i32* %info.addr, align 4, !dbg !1978
  %13 = load i8**, i8*** %param_charp, align 8, !dbg !1979
  %call = call i32 @getinfo_char(%struct.Curl_easy* %11, i32 %12, i8** %13), !dbg !1980
  store i32 %call, i32* %result, align 4, !dbg !1981
  br label %if.end5, !dbg !1982

if.end5:                                          ; preds = %if.then4, %vaarg.end
  br label %sw.epilog, !dbg !1983

sw.bb6:                                           ; preds = %if.end
  %arraydecay7 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !1984
  %gp_offset_p8 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay7, i32 0, i32 0, !dbg !1984
  %gp_offset9 = load i32, i32* %gp_offset_p8, align 16, !dbg !1984
  %fits_in_gp10 = icmp ule i32 %gp_offset9, 40, !dbg !1984
  br i1 %fits_in_gp10, label %vaarg.in_reg11, label %vaarg.in_mem13, !dbg !1984

vaarg.in_reg11:                                   ; preds = %sw.bb6
  %14 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay7, i32 0, i32 3, !dbg !1985
  %reg_save_area12 = load i8*, i8** %14, align 16, !dbg !1985
  %15 = getelementptr i8, i8* %reg_save_area12, i32 %gp_offset9, !dbg !1985
  %16 = bitcast i8* %15 to i64**, !dbg !1985
  %17 = add i32 %gp_offset9, 8, !dbg !1985
  store i32 %17, i32* %gp_offset_p8, align 16, !dbg !1985
  br label %vaarg.end17, !dbg !1985

vaarg.in_mem13:                                   ; preds = %sw.bb6
  %overflow_arg_area_p14 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay7, i32 0, i32 2, !dbg !1986
  %overflow_arg_area15 = load i8*, i8** %overflow_arg_area_p14, align 8, !dbg !1986
  %18 = bitcast i8* %overflow_arg_area15 to i64**, !dbg !1986
  %overflow_arg_area.next16 = getelementptr i8, i8* %overflow_arg_area15, i32 8, !dbg !1986
  store i8* %overflow_arg_area.next16, i8** %overflow_arg_area_p14, align 8, !dbg !1986
  br label %vaarg.end17, !dbg !1986

vaarg.end17:                                      ; preds = %vaarg.in_mem13, %vaarg.in_reg11
  %vaarg.addr18 = phi i64** [ %16, %vaarg.in_reg11 ], [ %18, %vaarg.in_mem13 ], !dbg !1987
  %19 = load i64*, i64** %vaarg.addr18, align 8, !dbg !1987
  store i64* %19, i64** %param_longp, align 8, !dbg !1988
  %20 = load i64*, i64** %param_longp, align 8, !dbg !1989
  %tobool19 = icmp ne i64* %20, null, !dbg !1989
  br i1 %tobool19, label %if.then20, label %if.end22, !dbg !1991

if.then20:                                        ; preds = %vaarg.end17
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1992
  %22 = load i32, i32* %info.addr, align 4, !dbg !1993
  %23 = load i64*, i64** %param_longp, align 8, !dbg !1994
  %call21 = call i32 @getinfo_long(%struct.Curl_easy* %21, i32 %22, i64* %23), !dbg !1995
  store i32 %call21, i32* %result, align 4, !dbg !1996
  br label %if.end22, !dbg !1997

if.end22:                                         ; preds = %if.then20, %vaarg.end17
  br label %sw.epilog, !dbg !1998

sw.bb23:                                          ; preds = %if.end
  %arraydecay24 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !1999
  %gp_offset_p25 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay24, i32 0, i32 0, !dbg !1999
  %gp_offset26 = load i32, i32* %gp_offset_p25, align 16, !dbg !1999
  %fits_in_gp27 = icmp ule i32 %gp_offset26, 40, !dbg !1999
  br i1 %fits_in_gp27, label %vaarg.in_reg28, label %vaarg.in_mem30, !dbg !1999

vaarg.in_reg28:                                   ; preds = %sw.bb23
  %24 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay24, i32 0, i32 3, !dbg !2000
  %reg_save_area29 = load i8*, i8** %24, align 16, !dbg !2000
  %25 = getelementptr i8, i8* %reg_save_area29, i32 %gp_offset26, !dbg !2000
  %26 = bitcast i8* %25 to double**, !dbg !2000
  %27 = add i32 %gp_offset26, 8, !dbg !2000
  store i32 %27, i32* %gp_offset_p25, align 16, !dbg !2000
  br label %vaarg.end34, !dbg !2000

vaarg.in_mem30:                                   ; preds = %sw.bb23
  %overflow_arg_area_p31 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay24, i32 0, i32 2, !dbg !2001
  %overflow_arg_area32 = load i8*, i8** %overflow_arg_area_p31, align 8, !dbg !2001
  %28 = bitcast i8* %overflow_arg_area32 to double**, !dbg !2001
  %overflow_arg_area.next33 = getelementptr i8, i8* %overflow_arg_area32, i32 8, !dbg !2001
  store i8* %overflow_arg_area.next33, i8** %overflow_arg_area_p31, align 8, !dbg !2001
  br label %vaarg.end34, !dbg !2001

vaarg.end34:                                      ; preds = %vaarg.in_mem30, %vaarg.in_reg28
  %vaarg.addr35 = phi double** [ %26, %vaarg.in_reg28 ], [ %28, %vaarg.in_mem30 ], !dbg !2002
  %29 = load double*, double** %vaarg.addr35, align 8, !dbg !2002
  store double* %29, double** %param_doublep, align 8, !dbg !2003
  %30 = load double*, double** %param_doublep, align 8, !dbg !2004
  %tobool36 = icmp ne double* %30, null, !dbg !2004
  br i1 %tobool36, label %if.then37, label %if.end39, !dbg !2006

if.then37:                                        ; preds = %vaarg.end34
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2007
  %32 = load i32, i32* %info.addr, align 4, !dbg !2008
  %33 = load double*, double** %param_doublep, align 8, !dbg !2009
  %call38 = call i32 @getinfo_double(%struct.Curl_easy* %31, i32 %32, double* %33), !dbg !2010
  store i32 %call38, i32* %result, align 4, !dbg !2011
  br label %if.end39, !dbg !2012

if.end39:                                         ; preds = %if.then37, %vaarg.end34
  br label %sw.epilog, !dbg !2013

sw.bb40:                                          ; preds = %if.end
  %arraydecay41 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2014
  %gp_offset_p42 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay41, i32 0, i32 0, !dbg !2014
  %gp_offset43 = load i32, i32* %gp_offset_p42, align 16, !dbg !2014
  %fits_in_gp44 = icmp ule i32 %gp_offset43, 40, !dbg !2014
  br i1 %fits_in_gp44, label %vaarg.in_reg45, label %vaarg.in_mem47, !dbg !2014

vaarg.in_reg45:                                   ; preds = %sw.bb40
  %34 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay41, i32 0, i32 3, !dbg !2015
  %reg_save_area46 = load i8*, i8** %34, align 16, !dbg !2015
  %35 = getelementptr i8, i8* %reg_save_area46, i32 %gp_offset43, !dbg !2015
  %36 = bitcast i8* %35 to %struct.curl_slist***, !dbg !2015
  %37 = add i32 %gp_offset43, 8, !dbg !2015
  store i32 %37, i32* %gp_offset_p42, align 16, !dbg !2015
  br label %vaarg.end51, !dbg !2015

vaarg.in_mem47:                                   ; preds = %sw.bb40
  %overflow_arg_area_p48 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay41, i32 0, i32 2, !dbg !2016
  %overflow_arg_area49 = load i8*, i8** %overflow_arg_area_p48, align 8, !dbg !2016
  %38 = bitcast i8* %overflow_arg_area49 to %struct.curl_slist***, !dbg !2016
  %overflow_arg_area.next50 = getelementptr i8, i8* %overflow_arg_area49, i32 8, !dbg !2016
  store i8* %overflow_arg_area.next50, i8** %overflow_arg_area_p48, align 8, !dbg !2016
  br label %vaarg.end51, !dbg !2016

vaarg.end51:                                      ; preds = %vaarg.in_mem47, %vaarg.in_reg45
  %vaarg.addr52 = phi %struct.curl_slist*** [ %36, %vaarg.in_reg45 ], [ %38, %vaarg.in_mem47 ], !dbg !2017
  %39 = load %struct.curl_slist**, %struct.curl_slist*** %vaarg.addr52, align 8, !dbg !2017
  store %struct.curl_slist** %39, %struct.curl_slist*** %param_slistp, align 8, !dbg !2018
  %40 = load %struct.curl_slist**, %struct.curl_slist*** %param_slistp, align 8, !dbg !2019
  %tobool53 = icmp ne %struct.curl_slist** %40, null, !dbg !2019
  br i1 %tobool53, label %if.then54, label %if.end56, !dbg !2021

if.then54:                                        ; preds = %vaarg.end51
  %41 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2022
  %42 = load i32, i32* %info.addr, align 4, !dbg !2023
  %43 = load %struct.curl_slist**, %struct.curl_slist*** %param_slistp, align 8, !dbg !2024
  %call55 = call i32 @getinfo_slist(%struct.Curl_easy* %41, i32 %42, %struct.curl_slist** %43), !dbg !2025
  store i32 %call55, i32* %result, align 4, !dbg !2026
  br label %if.end56, !dbg !2027

if.end56:                                         ; preds = %if.then54, %vaarg.end51
  br label %sw.epilog, !dbg !2028

sw.bb57:                                          ; preds = %if.end
  %arraydecay58 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2029
  %gp_offset_p59 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay58, i32 0, i32 0, !dbg !2029
  %gp_offset60 = load i32, i32* %gp_offset_p59, align 16, !dbg !2029
  %fits_in_gp61 = icmp ule i32 %gp_offset60, 40, !dbg !2029
  br i1 %fits_in_gp61, label %vaarg.in_reg62, label %vaarg.in_mem64, !dbg !2029

vaarg.in_reg62:                                   ; preds = %sw.bb57
  %44 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay58, i32 0, i32 3, !dbg !2030
  %reg_save_area63 = load i8*, i8** %44, align 16, !dbg !2030
  %45 = getelementptr i8, i8* %reg_save_area63, i32 %gp_offset60, !dbg !2030
  %46 = bitcast i8* %45 to i32**, !dbg !2030
  %47 = add i32 %gp_offset60, 8, !dbg !2030
  store i32 %47, i32* %gp_offset_p59, align 16, !dbg !2030
  br label %vaarg.end68, !dbg !2030

vaarg.in_mem64:                                   ; preds = %sw.bb57
  %overflow_arg_area_p65 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay58, i32 0, i32 2, !dbg !2031
  %overflow_arg_area66 = load i8*, i8** %overflow_arg_area_p65, align 8, !dbg !2031
  %48 = bitcast i8* %overflow_arg_area66 to i32**, !dbg !2031
  %overflow_arg_area.next67 = getelementptr i8, i8* %overflow_arg_area66, i32 8, !dbg !2031
  store i8* %overflow_arg_area.next67, i8** %overflow_arg_area_p65, align 8, !dbg !2031
  br label %vaarg.end68, !dbg !2031

vaarg.end68:                                      ; preds = %vaarg.in_mem64, %vaarg.in_reg62
  %vaarg.addr69 = phi i32** [ %46, %vaarg.in_reg62 ], [ %48, %vaarg.in_mem64 ], !dbg !2032
  %49 = load i32*, i32** %vaarg.addr69, align 8, !dbg !2032
  store i32* %49, i32** %param_socketp, align 8, !dbg !2033
  %50 = load i32*, i32** %param_socketp, align 8, !dbg !2034
  %tobool70 = icmp ne i32* %50, null, !dbg !2034
  br i1 %tobool70, label %if.then71, label %if.end73, !dbg !2036

if.then71:                                        ; preds = %vaarg.end68
  %51 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2037
  %52 = load i32, i32* %info.addr, align 4, !dbg !2038
  %53 = load i32*, i32** %param_socketp, align 8, !dbg !2039
  %call72 = call i32 @getinfo_socket(%struct.Curl_easy* %51, i32 %52, i32* %53), !dbg !2040
  store i32 %call72, i32* %result, align 4, !dbg !2041
  br label %if.end73, !dbg !2042

if.end73:                                         ; preds = %if.then71, %vaarg.end68
  br label %sw.epilog, !dbg !2043

sw.default:                                       ; preds = %if.end
  br label %sw.epilog, !dbg !2044

sw.epilog:                                        ; preds = %sw.default, %if.end73, %if.end56, %if.end39, %if.end22, %if.end5
  %arraydecay74 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2045
  %arraydecay7475 = bitcast %struct.__va_list_tag* %arraydecay74 to i8*, !dbg !2045
  call void @llvm.va_end(i8* %arraydecay7475), !dbg !2045
  %54 = load i32, i32* %result, align 4, !dbg !2046
  store i32 %54, i32* %retval, align 4, !dbg !2047
  br label %return, !dbg !2047

return:                                           ; preds = %sw.epilog, %if.then
  %55 = load i32, i32* %retval, align 4, !dbg !2048
  ret i32 %55, !dbg !2048
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @getinfo_char(%struct.Curl_easy* %data, i32 %info, i8** %param_charp) #0 !dbg !1811 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %param_charp.addr = alloca i8**, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2049, metadata !1833), !dbg !2050
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !2051, metadata !1833), !dbg !2052
  store i8** %param_charp, i8*** %param_charp.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %param_charp.addr, metadata !2053, metadata !1833), !dbg !2054
  %0 = load i32, i32* %info.addr, align 4, !dbg !2055
  switch i32 %0, label %sw.default [
    i32 1048577, label %sw.bb
    i32 1048594, label %sw.bb3
    i32 1048597, label %sw.bb5
    i32 1048606, label %sw.bb6
    i32 1048607, label %sw.bb7
    i32 1048608, label %sw.bb9
    i32 1048617, label %sw.bb11
    i32 1048612, label %sw.bb14
    i32 1048625, label %sw.bb16
  ], !dbg !2056

sw.bb:                                            ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2057
  %change = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 14, !dbg !2059
  %url = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change, i32 0, i32 0, !dbg !2060
  %2 = load i8*, i8** %url, align 8, !dbg !2060
  %tobool = icmp ne i8* %2, null, !dbg !2057
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !2057

cond.true:                                        ; preds = %sw.bb
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2061
  %change1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 14, !dbg !2063
  %url2 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change1, i32 0, i32 0, !dbg !2064
  %4 = load i8*, i8** %url2, align 8, !dbg !2064
  br label %cond.end, !dbg !2065

cond.false:                                       ; preds = %sw.bb
  br label %cond.end, !dbg !2066

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %4, %cond.true ], [ getelementptr inbounds ([1 x i8], [1 x i8]* @.str, i32 0, i32 0), %cond.false ], !dbg !2068
  %5 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2070
  store i8* %cond, i8** %5, align 8, !dbg !2071
  br label %sw.epilog, !dbg !2072

sw.bb3:                                           ; preds = %entry
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2073
  %info4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 19, !dbg !2074
  %contenttype = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info4, i32 0, i32 10, !dbg !2075
  %7 = load i8*, i8** %contenttype, align 8, !dbg !2075
  %8 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2076
  store i8* %7, i8** %8, align 8, !dbg !2077
  br label %sw.epilog, !dbg !2078

sw.bb5:                                           ; preds = %entry
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2079
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 13, !dbg !2080
  %private_data = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 79, !dbg !2081
  %10 = load i8*, i8** %private_data, align 8, !dbg !2081
  %11 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2082
  store i8* %10, i8** %11, align 8, !dbg !2083
  br label %sw.epilog, !dbg !2084

sw.bb6:                                           ; preds = %entry
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2085
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 17, !dbg !2086
  %most_recent_ftp_entrypath = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 30, !dbg !2087
  %13 = load i8*, i8** %most_recent_ftp_entrypath, align 8, !dbg !2087
  %14 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2088
  store i8* %13, i8** %14, align 8, !dbg !2089
  br label %sw.epilog, !dbg !2090

sw.bb7:                                           ; preds = %entry
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2091
  %info8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 19, !dbg !2092
  %wouldredirect = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info8, i32 0, i32 11, !dbg !2093
  %16 = load i8*, i8** %wouldredirect, align 8, !dbg !2093
  %17 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2094
  store i8* %16, i8** %17, align 8, !dbg !2095
  br label %sw.epilog, !dbg !2096

sw.bb9:                                           ; preds = %entry
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2097
  %info10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 19, !dbg !2098
  %conn_primary_ip = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info10, i32 0, i32 12, !dbg !2099
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %conn_primary_ip, i32 0, i32 0, !dbg !2097
  %19 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2100
  store i8* %arraydecay, i8** %19, align 8, !dbg !2101
  br label %sw.epilog, !dbg !2102

sw.bb11:                                          ; preds = %entry
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2103
  %info12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 19, !dbg !2104
  %conn_local_ip = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info12, i32 0, i32 14, !dbg !2105
  %arraydecay13 = getelementptr inbounds [46 x i8], [46 x i8]* %conn_local_ip, i32 0, i32 0, !dbg !2103
  %21 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2106
  store i8* %arraydecay13, i8** %21, align 8, !dbg !2107
  br label %sw.epilog, !dbg !2108

sw.bb14:                                          ; preds = %entry
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2109
  %set15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 13, !dbg !2110
  %str = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set15, i32 0, i32 128, !dbg !2111
  %arrayidx = getelementptr inbounds [56 x i8*], [56 x i8*]* %str, i64 0, i64 47, !dbg !2109
  %23 = load i8*, i8** %arrayidx, align 8, !dbg !2109
  %24 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2112
  store i8* %23, i8** %24, align 8, !dbg !2113
  br label %sw.epilog, !dbg !2114

sw.bb16:                                          ; preds = %entry
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2115
  %info17 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 19, !dbg !2116
  %conn_scheme = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info17, i32 0, i32 16, !dbg !2117
  %26 = load i8*, i8** %conn_scheme, align 8, !dbg !2117
  %27 = load i8**, i8*** %param_charp.addr, align 8, !dbg !2118
  store i8* %26, i8** %27, align 8, !dbg !2119
  br label %sw.epilog, !dbg !2120

sw.default:                                       ; preds = %entry
  store i32 48, i32* %retval, align 4, !dbg !2121
  br label %return, !dbg !2121

sw.epilog:                                        ; preds = %sw.bb16, %sw.bb14, %sw.bb11, %sw.bb9, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb3, %cond.end
  store i32 0, i32* %retval, align 4, !dbg !2122
  br label %return, !dbg !2122

return:                                           ; preds = %sw.epilog, %sw.default
  %28 = load i32, i32* %retval, align 4, !dbg !2123
  ret i32 %28, !dbg !2123
}

; Function Attrs: nounwind uwtable
define internal i32 @getinfo_long(%struct.Curl_easy* %data, i32 %info, i64* %param_longp) #0 !dbg !1815 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %param_longp.addr = alloca i64*, align 8
  %sockfd = alloca i32, align 4
  %lptr = alloca %union.anon.1, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2124, metadata !1833), !dbg !2125
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !2126, metadata !1833), !dbg !2127
  store i64* %param_longp, i64** %param_longp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %param_longp.addr, metadata !2128, metadata !1833), !dbg !2129
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !2130, metadata !1833), !dbg !2131
  call void @llvm.dbg.declare(metadata %union.anon.1* %lptr, metadata !2132, metadata !1833), !dbg !2138
  %0 = load i32, i32* %info.addr, align 4, !dbg !2139
  switch i32 %0, label %sw.default51 [
    i32 2097154, label %sw.bb
    i32 2097174, label %sw.bb2
    i32 2097166, label %sw.bb5
    i32 2097163, label %sw.bb7
    i32 2097164, label %sw.bb9
    i32 2097165, label %sw.bb11
    i32 2097199, label %sw.bb12
    i32 2097172, label %sw.bb15
    i32 2097175, label %sw.bb17
    i32 2097176, label %sw.bb19
    i32 2097177, label %sw.bb23
    i32 2097178, label %sw.bb25
    i32 2097181, label %sw.bb27
    i32 2097192, label %sw.bb30
    i32 2097194, label %sw.bb32
    i32 2097187, label %sw.bb34
    i32 2097189, label %sw.bb37
    i32 2097190, label %sw.bb39
    i32 2097191, label %sw.bb41
    i32 2097198, label %sw.bb43
    i32 2097200, label %sw.bb48
  ], !dbg !2140

sw.bb:                                            ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2141
  %info1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 19, !dbg !2143
  %httpcode = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info1, i32 0, i32 0, !dbg !2144
  %2 = load i32, i32* %httpcode, align 8, !dbg !2144
  %conv = sext i32 %2 to i64, !dbg !2141
  %3 = load i64*, i64** %param_longp.addr, align 8, !dbg !2145
  store i64 %conv, i64* %3, align 8, !dbg !2146
  br label %sw.epilog52, !dbg !2147

sw.bb2:                                           ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2148
  %info3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 19, !dbg !2149
  %httpproxycode = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info3, i32 0, i32 1, !dbg !2150
  %5 = load i32, i32* %httpproxycode, align 4, !dbg !2150
  %conv4 = sext i32 %5 to i64, !dbg !2148
  %6 = load i64*, i64** %param_longp.addr, align 8, !dbg !2151
  store i64 %conv4, i64* %6, align 8, !dbg !2152
  br label %sw.epilog52, !dbg !2153

sw.bb5:                                           ; preds = %entry
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2154
  %info6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 19, !dbg !2155
  %filetime = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info6, i32 0, i32 3, !dbg !2156
  %8 = load i64, i64* %filetime, align 8, !dbg !2156
  %9 = load i64*, i64** %param_longp.addr, align 8, !dbg !2157
  store i64 %8, i64* %9, align 8, !dbg !2158
  br label %sw.epilog52, !dbg !2159

sw.bb7:                                           ; preds = %entry
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2160
  %info8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 19, !dbg !2161
  %header_size = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info8, i32 0, i32 5, !dbg !2162
  %11 = load i64, i64* %header_size, align 8, !dbg !2162
  %12 = load i64*, i64** %param_longp.addr, align 8, !dbg !2163
  store i64 %11, i64* %12, align 8, !dbg !2164
  br label %sw.epilog52, !dbg !2165

sw.bb9:                                           ; preds = %entry
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2166
  %info10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 19, !dbg !2167
  %request_size = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info10, i32 0, i32 6, !dbg !2168
  %14 = load i64, i64* %request_size, align 8, !dbg !2168
  %15 = load i64*, i64** %param_longp.addr, align 8, !dbg !2169
  store i64 %14, i64* %15, align 8, !dbg !2170
  br label %sw.epilog52, !dbg !2171

sw.bb11:                                          ; preds = %entry
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2172
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 13, !dbg !2173
  %ssl = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 73, !dbg !2174
  %certverifyresult = getelementptr inbounds %struct.ssl_config_data, %struct.ssl_config_data* %ssl, i32 0, i32 3, !dbg !2175
  %17 = load i64, i64* %certverifyresult, align 8, !dbg !2175
  %18 = load i64*, i64** %param_longp.addr, align 8, !dbg !2176
  store i64 %17, i64* %18, align 8, !dbg !2177
  br label %sw.epilog52, !dbg !2178

sw.bb12:                                          ; preds = %entry
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2179
  %set13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 13, !dbg !2180
  %proxy_ssl = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set13, i32 0, i32 74, !dbg !2181
  %certverifyresult14 = getelementptr inbounds %struct.ssl_config_data, %struct.ssl_config_data* %proxy_ssl, i32 0, i32 3, !dbg !2182
  %20 = load i64, i64* %certverifyresult14, align 8, !dbg !2182
  %21 = load i64*, i64** %param_longp.addr, align 8, !dbg !2183
  store i64 %20, i64* %21, align 8, !dbg !2184
  br label %sw.epilog52, !dbg !2185

sw.bb15:                                          ; preds = %entry
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2186
  %set16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 13, !dbg !2187
  %followlocation = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set16, i32 0, i32 11, !dbg !2188
  %23 = load i64, i64* %followlocation, align 8, !dbg !2188
  %24 = load i64*, i64** %param_longp.addr, align 8, !dbg !2189
  store i64 %23, i64* %24, align 8, !dbg !2190
  br label %sw.epilog52, !dbg !2191

sw.bb17:                                          ; preds = %entry
  %25 = load i64*, i64** %param_longp.addr, align 8, !dbg !2192
  %to_long = bitcast %union.anon.1* %lptr to i64**, !dbg !2193
  store i64* %25, i64** %to_long, align 8, !dbg !2194
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2195
  %info18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 19, !dbg !2196
  %httpauthavail = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info18, i32 0, i32 8, !dbg !2197
  %27 = load i64, i64* %httpauthavail, align 8, !dbg !2197
  %to_ulong = bitcast %union.anon.1* %lptr to i64**, !dbg !2198
  %28 = load i64*, i64** %to_ulong, align 8, !dbg !2198
  store i64 %27, i64* %28, align 8, !dbg !2199
  br label %sw.epilog52, !dbg !2200

sw.bb19:                                          ; preds = %entry
  %29 = load i64*, i64** %param_longp.addr, align 8, !dbg !2201
  %to_long20 = bitcast %union.anon.1* %lptr to i64**, !dbg !2202
  store i64* %29, i64** %to_long20, align 8, !dbg !2203
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2204
  %info21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %30, i32 0, i32 19, !dbg !2205
  %proxyauthavail = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info21, i32 0, i32 7, !dbg !2206
  %31 = load i64, i64* %proxyauthavail, align 8, !dbg !2206
  %to_ulong22 = bitcast %union.anon.1* %lptr to i64**, !dbg !2207
  %32 = load i64*, i64** %to_ulong22, align 8, !dbg !2207
  store i64 %31, i64* %32, align 8, !dbg !2208
  br label %sw.epilog52, !dbg !2209

sw.bb23:                                          ; preds = %entry
  %33 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2210
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %33, i32 0, i32 17, !dbg !2211
  %os_errno = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 18, !dbg !2212
  %34 = load i32, i32* %os_errno, align 4, !dbg !2212
  %conv24 = sext i32 %34 to i64, !dbg !2210
  %35 = load i64*, i64** %param_longp.addr, align 8, !dbg !2213
  store i64 %conv24, i64* %35, align 8, !dbg !2214
  br label %sw.epilog52, !dbg !2215

sw.bb25:                                          ; preds = %entry
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2216
  %info26 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 19, !dbg !2217
  %numconnects = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info26, i32 0, i32 9, !dbg !2218
  %37 = load i64, i64* %numconnects, align 8, !dbg !2218
  %38 = load i64*, i64** %param_longp.addr, align 8, !dbg !2219
  store i64 %37, i64* %38, align 8, !dbg !2220
  br label %sw.epilog52, !dbg !2221

sw.bb27:                                          ; preds = %entry
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2222
  %call = call i32 @Curl_getconnectinfo(%struct.Curl_easy* %39, %struct.connectdata** null), !dbg !2223
  store i32 %call, i32* %sockfd, align 4, !dbg !2224
  %40 = load i32, i32* %sockfd, align 4, !dbg !2225
  %cmp = icmp ne i32 %40, -1, !dbg !2227
  br i1 %cmp, label %if.then, label %if.else, !dbg !2228

if.then:                                          ; preds = %sw.bb27
  %41 = load i32, i32* %sockfd, align 4, !dbg !2229
  %conv29 = sext i32 %41 to i64, !dbg !2230
  %42 = load i64*, i64** %param_longp.addr, align 8, !dbg !2231
  store i64 %conv29, i64* %42, align 8, !dbg !2232
  br label %if.end, !dbg !2233

if.else:                                          ; preds = %sw.bb27
  %43 = load i64*, i64** %param_longp.addr, align 8, !dbg !2234
  store i64 -1, i64* %43, align 8, !dbg !2235
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %sw.epilog52, !dbg !2236

sw.bb30:                                          ; preds = %entry
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2237
  %info31 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %44, i32 0, i32 19, !dbg !2238
  %conn_primary_port = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info31, i32 0, i32 13, !dbg !2239
  %45 = load i64, i64* %conn_primary_port, align 8, !dbg !2239
  %46 = load i64*, i64** %param_longp.addr, align 8, !dbg !2240
  store i64 %45, i64* %46, align 8, !dbg !2241
  br label %sw.epilog52, !dbg !2242

sw.bb32:                                          ; preds = %entry
  %47 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2243
  %info33 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %47, i32 0, i32 19, !dbg !2244
  %conn_local_port = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info33, i32 0, i32 15, !dbg !2245
  %48 = load i64, i64* %conn_local_port, align 8, !dbg !2245
  %49 = load i64*, i64** %param_longp.addr, align 8, !dbg !2246
  store i64 %48, i64* %49, align 8, !dbg !2247
  br label %sw.epilog52, !dbg !2248

sw.bb34:                                          ; preds = %entry
  %50 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2249
  %info35 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %50, i32 0, i32 19, !dbg !2250
  %timecond = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info35, i32 0, i32 4, !dbg !2251
  %51 = load i8, i8* %timecond, align 8, !dbg !2251
  %tobool = trunc i8 %51 to i1, !dbg !2251
  %cond = select i1 %tobool, i64 1, i64 0, !dbg !2249
  %52 = load i64*, i64** %param_longp.addr, align 8, !dbg !2252
  store i64 %cond, i64* %52, align 8, !dbg !2253
  br label %sw.epilog52, !dbg !2254

sw.bb37:                                          ; preds = %entry
  %53 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2255
  %state38 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %53, i32 0, i32 17, !dbg !2256
  %rtsp_next_client_CSeq = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state38, i32 0, i32 44, !dbg !2257
  %54 = load i64, i64* %rtsp_next_client_CSeq, align 8, !dbg !2257
  %55 = load i64*, i64** %param_longp.addr, align 8, !dbg !2258
  store i64 %54, i64* %55, align 8, !dbg !2259
  br label %sw.epilog52, !dbg !2260

sw.bb39:                                          ; preds = %entry
  %56 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2261
  %state40 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %56, i32 0, i32 17, !dbg !2262
  %rtsp_next_server_CSeq = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state40, i32 0, i32 45, !dbg !2263
  %57 = load i64, i64* %rtsp_next_server_CSeq, align 8, !dbg !2263
  %58 = load i64*, i64** %param_longp.addr, align 8, !dbg !2264
  store i64 %57, i64* %58, align 8, !dbg !2265
  br label %sw.epilog52, !dbg !2266

sw.bb41:                                          ; preds = %entry
  %59 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2267
  %state42 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %59, i32 0, i32 17, !dbg !2268
  %rtsp_CSeq_recv = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state42, i32 0, i32 46, !dbg !2269
  %60 = load i64, i64* %rtsp_CSeq_recv, align 8, !dbg !2269
  %61 = load i64*, i64** %param_longp.addr, align 8, !dbg !2270
  store i64 %60, i64* %61, align 8, !dbg !2271
  br label %sw.epilog52, !dbg !2272

sw.bb43:                                          ; preds = %entry
  %62 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2273
  %info44 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %62, i32 0, i32 19, !dbg !2274
  %httpversion = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info44, i32 0, i32 2, !dbg !2275
  %63 = load i32, i32* %httpversion, align 8, !dbg !2275
  switch i32 %63, label %sw.default [
    i32 10, label %sw.bb45
    i32 11, label %sw.bb46
    i32 20, label %sw.bb47
  ], !dbg !2276

sw.bb45:                                          ; preds = %sw.bb43
  %64 = load i64*, i64** %param_longp.addr, align 8, !dbg !2277
  store i64 1, i64* %64, align 8, !dbg !2279
  br label %sw.epilog, !dbg !2280

sw.bb46:                                          ; preds = %sw.bb43
  %65 = load i64*, i64** %param_longp.addr, align 8, !dbg !2281
  store i64 2, i64* %65, align 8, !dbg !2282
  br label %sw.epilog, !dbg !2283

sw.bb47:                                          ; preds = %sw.bb43
  %66 = load i64*, i64** %param_longp.addr, align 8, !dbg !2284
  store i64 3, i64* %66, align 8, !dbg !2285
  br label %sw.epilog, !dbg !2286

sw.default:                                       ; preds = %sw.bb43
  %67 = load i64*, i64** %param_longp.addr, align 8, !dbg !2287
  store i64 0, i64* %67, align 8, !dbg !2288
  br label %sw.epilog, !dbg !2289

sw.epilog:                                        ; preds = %sw.default, %sw.bb47, %sw.bb46, %sw.bb45
  br label %sw.epilog52, !dbg !2290

sw.bb48:                                          ; preds = %entry
  %68 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2291
  %info49 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %68, i32 0, i32 19, !dbg !2292
  %conn_protocol = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info49, i32 0, i32 17, !dbg !2293
  %69 = load i32, i32* %conn_protocol, align 8, !dbg !2293
  %conv50 = zext i32 %69 to i64, !dbg !2291
  %70 = load i64*, i64** %param_longp.addr, align 8, !dbg !2294
  store i64 %conv50, i64* %70, align 8, !dbg !2295
  br label %sw.epilog52, !dbg !2296

sw.default51:                                     ; preds = %entry
  store i32 48, i32* %retval, align 4, !dbg !2297
  br label %return, !dbg !2297

sw.epilog52:                                      ; preds = %sw.bb48, %sw.epilog, %sw.bb41, %sw.bb39, %sw.bb37, %sw.bb34, %sw.bb32, %sw.bb30, %if.end, %sw.bb25, %sw.bb23, %sw.bb19, %sw.bb17, %sw.bb15, %sw.bb12, %sw.bb11, %sw.bb9, %sw.bb7, %sw.bb5, %sw.bb2, %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !2298
  br label %return, !dbg !2298

return:                                           ; preds = %sw.epilog52, %sw.default51
  %71 = load i32, i32* %retval, align 4, !dbg !2299
  ret i32 %71, !dbg !2299
}

; Function Attrs: nounwind uwtable
define internal i32 @getinfo_double(%struct.Curl_easy* %data, i32 %info, double* %param_doublep) #0 !dbg !1819 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %param_doublep.addr = alloca double*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2300, metadata !1833), !dbg !2301
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !2302, metadata !1833), !dbg !2303
  store double* %param_doublep, double** %param_doublep.addr, align 8
  call void @llvm.dbg.declare(metadata double** %param_doublep.addr, metadata !2304, metadata !1833), !dbg !2305
  %0 = load i32, i32* %info.addr, align 4, !dbg !2306
  switch i32 %0, label %sw.default [
    i32 3145731, label %sw.bb
    i32 3145732, label %sw.bb1
    i32 3145733, label %sw.bb3
    i32 3145761, label %sw.bb5
    i32 3145734, label %sw.bb7
    i32 3145745, label %sw.bb9
    i32 3145735, label %sw.bb11
    i32 3145736, label %sw.bb13
    i32 3145737, label %sw.bb16
    i32 3145738, label %sw.bb19
    i32 3145743, label %sw.bb22
    i32 3145744, label %sw.bb26
    i32 3145747, label %sw.bb37
  ], !dbg !2307

sw.bb:                                            ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2308
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 16, !dbg !2310
  %timespent = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 9, !dbg !2311
  %2 = load double, double* %timespent, align 8, !dbg !2311
  %3 = load double*, double** %param_doublep.addr, align 8, !dbg !2312
  store double %2, double* %3, align 8, !dbg !2313
  br label %sw.epilog, !dbg !2314

sw.bb1:                                           ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2315
  %progress2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 16, !dbg !2316
  %t_nslookup = getelementptr inbounds %struct.Progress, %struct.Progress* %progress2, i32 0, i32 12, !dbg !2317
  %5 = load double, double* %t_nslookup, align 8, !dbg !2317
  %6 = load double*, double** %param_doublep.addr, align 8, !dbg !2318
  store double %5, double* %6, align 8, !dbg !2319
  br label %sw.epilog, !dbg !2320

sw.bb3:                                           ; preds = %entry
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2321
  %progress4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 16, !dbg !2322
  %t_connect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress4, i32 0, i32 13, !dbg !2323
  %8 = load double, double* %t_connect, align 8, !dbg !2323
  %9 = load double*, double** %param_doublep.addr, align 8, !dbg !2324
  store double %8, double* %9, align 8, !dbg !2325
  br label %sw.epilog, !dbg !2326

sw.bb5:                                           ; preds = %entry
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2327
  %progress6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 16, !dbg !2328
  %t_appconnect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress6, i32 0, i32 14, !dbg !2329
  %11 = load double, double* %t_appconnect, align 8, !dbg !2329
  %12 = load double*, double** %param_doublep.addr, align 8, !dbg !2330
  store double %11, double* %12, align 8, !dbg !2331
  br label %sw.epilog, !dbg !2332

sw.bb7:                                           ; preds = %entry
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2333
  %progress8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 16, !dbg !2334
  %t_pretransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %progress8, i32 0, i32 15, !dbg !2335
  %14 = load double, double* %t_pretransfer, align 8, !dbg !2335
  %15 = load double*, double** %param_doublep.addr, align 8, !dbg !2336
  store double %14, double* %15, align 8, !dbg !2337
  br label %sw.epilog, !dbg !2338

sw.bb9:                                           ; preds = %entry
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2339
  %progress10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 16, !dbg !2340
  %t_starttransfer = getelementptr inbounds %struct.Progress, %struct.Progress* %progress10, i32 0, i32 16, !dbg !2341
  %17 = load double, double* %t_starttransfer, align 8, !dbg !2341
  %18 = load double*, double** %param_doublep.addr, align 8, !dbg !2342
  store double %17, double* %18, align 8, !dbg !2343
  br label %sw.epilog, !dbg !2344

sw.bb11:                                          ; preds = %entry
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2345
  %progress12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 16, !dbg !2346
  %uploaded = getelementptr inbounds %struct.Progress, %struct.Progress* %progress12, i32 0, i32 4, !dbg !2347
  %20 = load i64, i64* %uploaded, align 8, !dbg !2347
  %conv = sitofp i64 %20 to double, !dbg !2348
  %21 = load double*, double** %param_doublep.addr, align 8, !dbg !2349
  store double %conv, double* %21, align 8, !dbg !2350
  br label %sw.epilog, !dbg !2351

sw.bb13:                                          ; preds = %entry
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2352
  %progress14 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 16, !dbg !2353
  %downloaded = getelementptr inbounds %struct.Progress, %struct.Progress* %progress14, i32 0, i32 3, !dbg !2354
  %23 = load i64, i64* %downloaded, align 8, !dbg !2354
  %conv15 = sitofp i64 %23 to double, !dbg !2355
  %24 = load double*, double** %param_doublep.addr, align 8, !dbg !2356
  store double %conv15, double* %24, align 8, !dbg !2357
  br label %sw.epilog, !dbg !2358

sw.bb16:                                          ; preds = %entry
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2359
  %progress17 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 16, !dbg !2360
  %dlspeed = getelementptr inbounds %struct.Progress, %struct.Progress* %progress17, i32 0, i32 10, !dbg !2361
  %26 = load i64, i64* %dlspeed, align 8, !dbg !2361
  %conv18 = sitofp i64 %26 to double, !dbg !2362
  %27 = load double*, double** %param_doublep.addr, align 8, !dbg !2363
  store double %conv18, double* %27, align 8, !dbg !2364
  br label %sw.epilog, !dbg !2365

sw.bb19:                                          ; preds = %entry
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2366
  %progress20 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 16, !dbg !2367
  %ulspeed = getelementptr inbounds %struct.Progress, %struct.Progress* %progress20, i32 0, i32 11, !dbg !2368
  %29 = load i64, i64* %ulspeed, align 8, !dbg !2368
  %conv21 = sitofp i64 %29 to double, !dbg !2369
  %30 = load double*, double** %param_doublep.addr, align 8, !dbg !2370
  store double %conv21, double* %30, align 8, !dbg !2371
  br label %sw.epilog, !dbg !2372

sw.bb22:                                          ; preds = %entry
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2373
  %progress23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %31, i32 0, i32 16, !dbg !2374
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress23, i32 0, i32 8, !dbg !2375
  %32 = load i32, i32* %flags, align 8, !dbg !2375
  %and = and i32 %32, 64, !dbg !2376
  %tobool = icmp ne i32 %and, 0, !dbg !2376
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !2377

cond.true:                                        ; preds = %sw.bb22
  %33 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2378
  %progress24 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %33, i32 0, i32 16, !dbg !2379
  %size_dl = getelementptr inbounds %struct.Progress, %struct.Progress* %progress24, i32 0, i32 1, !dbg !2380
  %34 = load i64, i64* %size_dl, align 8, !dbg !2380
  %conv25 = sitofp i64 %34 to double, !dbg !2381
  br label %cond.end, !dbg !2382

cond.false:                                       ; preds = %sw.bb22
  br label %cond.end, !dbg !2384

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi double [ %conv25, %cond.true ], [ -1.000000e+00, %cond.false ], !dbg !2386
  %35 = load double*, double** %param_doublep.addr, align 8, !dbg !2388
  store double %cond, double* %35, align 8, !dbg !2389
  br label %sw.epilog, !dbg !2390

sw.bb26:                                          ; preds = %entry
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2391
  %progress27 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 16, !dbg !2392
  %flags28 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress27, i32 0, i32 8, !dbg !2393
  %37 = load i32, i32* %flags28, align 8, !dbg !2393
  %and29 = and i32 %37, 32, !dbg !2394
  %tobool30 = icmp ne i32 %and29, 0, !dbg !2394
  br i1 %tobool30, label %cond.true31, label %cond.false34, !dbg !2395

cond.true31:                                      ; preds = %sw.bb26
  %38 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2396
  %progress32 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %38, i32 0, i32 16, !dbg !2397
  %size_ul = getelementptr inbounds %struct.Progress, %struct.Progress* %progress32, i32 0, i32 2, !dbg !2398
  %39 = load i64, i64* %size_ul, align 8, !dbg !2398
  %conv33 = sitofp i64 %39 to double, !dbg !2399
  br label %cond.end35, !dbg !2400

cond.false34:                                     ; preds = %sw.bb26
  br label %cond.end35, !dbg !2401

cond.end35:                                       ; preds = %cond.false34, %cond.true31
  %cond36 = phi double [ %conv33, %cond.true31 ], [ -1.000000e+00, %cond.false34 ], !dbg !2402
  %40 = load double*, double** %param_doublep.addr, align 8, !dbg !2403
  store double %cond36, double* %40, align 8, !dbg !2404
  br label %sw.epilog, !dbg !2405

sw.bb37:                                          ; preds = %entry
  %41 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2406
  %progress38 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %41, i32 0, i32 16, !dbg !2407
  %t_redirect = getelementptr inbounds %struct.Progress, %struct.Progress* %progress38, i32 0, i32 17, !dbg !2408
  %42 = load double, double* %t_redirect, align 8, !dbg !2408
  %43 = load double*, double** %param_doublep.addr, align 8, !dbg !2409
  store double %42, double* %43, align 8, !dbg !2410
  br label %sw.epilog, !dbg !2411

sw.default:                                       ; preds = %entry
  store i32 48, i32* %retval, align 4, !dbg !2412
  br label %return, !dbg !2412

sw.epilog:                                        ; preds = %sw.bb37, %cond.end35, %cond.end, %sw.bb19, %sw.bb16, %sw.bb13, %sw.bb11, %sw.bb9, %sw.bb7, %sw.bb5, %sw.bb3, %sw.bb1, %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !2413
  br label %return, !dbg !2413

return:                                           ; preds = %sw.epilog, %sw.default
  %44 = load i32, i32* %retval, align 4, !dbg !2414
  ret i32 %44, !dbg !2414
}

; Function Attrs: nounwind uwtable
define internal i32 @getinfo_slist(%struct.Curl_easy* %data, i32 %info, %struct.curl_slist** %param_slistp) #0 !dbg !1823 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %param_slistp.addr = alloca %struct.curl_slist**, align 8
  %ptr = alloca %union.anon.2, align 8
  %tsip = alloca %struct.curl_tlssessioninfo**, align 8
  %tsi = alloca %struct.curl_tlssessioninfo*, align 8
  %conn = alloca %struct.connectdata*, align 8
  %i = alloca i32, align 4
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2415, metadata !1833), !dbg !2416
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !2417, metadata !1833), !dbg !2418
  store %struct.curl_slist** %param_slistp, %struct.curl_slist*** %param_slistp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_slist*** %param_slistp.addr, metadata !2419, metadata !1833), !dbg !2420
  call void @llvm.dbg.declare(metadata %union.anon.2* %ptr, metadata !2421, metadata !1833), !dbg !2427
  %0 = load i32, i32* %info.addr, align 4, !dbg !2428
  switch i32 %0, label %sw.default [
    i32 4194331, label %sw.bb
    i32 4194332, label %sw.bb1
    i32 4194338, label %sw.bb2
    i32 4194347, label %sw.bb4
    i32 4194349, label %sw.bb4
  ], !dbg !2429

sw.bb:                                            ; preds = %entry
  %1 = load %struct.curl_slist**, %struct.curl_slist*** %param_slistp.addr, align 8, !dbg !2430
  store %struct.curl_slist* null, %struct.curl_slist** %1, align 8, !dbg !2432
  br label %sw.epilog, !dbg !2433

sw.bb1:                                           ; preds = %entry
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2434
  %call = call %struct.curl_slist* @Curl_cookie_list(%struct.Curl_easy* %2), !dbg !2435
  %3 = load %struct.curl_slist**, %struct.curl_slist*** %param_slistp.addr, align 8, !dbg !2436
  store %struct.curl_slist* %call, %struct.curl_slist** %3, align 8, !dbg !2437
  br label %sw.epilog, !dbg !2438

sw.bb2:                                           ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2439
  %info3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 19, !dbg !2440
  %certs = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info3, i32 0, i32 18, !dbg !2441
  %to_certinfo = bitcast %union.anon.2* %ptr to %struct.curl_certinfo**, !dbg !2442
  store %struct.curl_certinfo* %certs, %struct.curl_certinfo** %to_certinfo, align 8, !dbg !2443
  %to_slist = bitcast %union.anon.2* %ptr to %struct.curl_slist**, !dbg !2444
  %5 = load %struct.curl_slist*, %struct.curl_slist** %to_slist, align 8, !dbg !2444
  %6 = load %struct.curl_slist**, %struct.curl_slist*** %param_slistp.addr, align 8, !dbg !2445
  store %struct.curl_slist* %5, %struct.curl_slist** %6, align 8, !dbg !2446
  br label %sw.epilog, !dbg !2447

sw.bb4:                                           ; preds = %entry, %entry
  call void @llvm.dbg.declare(metadata %struct.curl_tlssessioninfo*** %tsip, metadata !2448, metadata !1833), !dbg !2450
  %7 = load %struct.curl_slist**, %struct.curl_slist*** %param_slistp.addr, align 8, !dbg !2451
  %8 = bitcast %struct.curl_slist** %7 to %struct.curl_tlssessioninfo**, !dbg !2452
  store %struct.curl_tlssessioninfo** %8, %struct.curl_tlssessioninfo*** %tsip, align 8, !dbg !2450
  call void @llvm.dbg.declare(metadata %struct.curl_tlssessioninfo** %tsi, metadata !2453, metadata !1833), !dbg !2454
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2455
  %tsi5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 20, !dbg !2456
  store %struct.curl_tlssessioninfo* %tsi5, %struct.curl_tlssessioninfo** %tsi, align 8, !dbg !2454
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn, metadata !2457, metadata !1833), !dbg !2458
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2459
  %easy_conn = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 2, !dbg !2460
  %11 = load %struct.connectdata*, %struct.connectdata** %easy_conn, align 8, !dbg !2460
  store %struct.connectdata* %11, %struct.connectdata** %conn, align 8, !dbg !2458
  %12 = load %struct.curl_tlssessioninfo*, %struct.curl_tlssessioninfo** %tsi, align 8, !dbg !2461
  %13 = load %struct.curl_tlssessioninfo**, %struct.curl_tlssessioninfo*** %tsip, align 8, !dbg !2462
  store %struct.curl_tlssessioninfo* %12, %struct.curl_tlssessioninfo** %13, align 8, !dbg !2463
  %call6 = call i32 @Curl_ssl_backend(), !dbg !2464
  %14 = load %struct.curl_tlssessioninfo*, %struct.curl_tlssessioninfo** %tsi, align 8, !dbg !2465
  %backend = getelementptr inbounds %struct.curl_tlssessioninfo, %struct.curl_tlssessioninfo* %14, i32 0, i32 0, !dbg !2466
  store i32 %call6, i32* %backend, align 8, !dbg !2467
  %15 = load %struct.curl_tlssessioninfo*, %struct.curl_tlssessioninfo** %tsi, align 8, !dbg !2468
  %internals = getelementptr inbounds %struct.curl_tlssessioninfo, %struct.curl_tlssessioninfo* %15, i32 0, i32 1, !dbg !2469
  store i8* null, i8** %internals, align 8, !dbg !2470
  %16 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2471
  %tobool = icmp ne %struct.connectdata* %16, null, !dbg !2471
  br i1 %tobool, label %land.lhs.true, label %if.end12, !dbg !2473

land.lhs.true:                                    ; preds = %sw.bb4
  %17 = load %struct.curl_tlssessioninfo*, %struct.curl_tlssessioninfo** %tsi, align 8, !dbg !2474
  %backend7 = getelementptr inbounds %struct.curl_tlssessioninfo, %struct.curl_tlssessioninfo* %17, i32 0, i32 0, !dbg !2476
  %18 = load i32, i32* %backend7, align 8, !dbg !2476
  %cmp = icmp ne i32 %18, 0, !dbg !2477
  br i1 %cmp, label %if.then, label %if.end12, !dbg !2478

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2479, metadata !1833), !dbg !2481
  store i32 0, i32* %i, align 4, !dbg !2482
  br label %for.cond, !dbg !2484

for.cond:                                         ; preds = %for.inc, %if.then
  %19 = load i32, i32* %i, align 4, !dbg !2485
  %conv = zext i32 %19 to i64, !dbg !2485
  %cmp8 = icmp ult i64 %conv, 2, !dbg !2488
  br i1 %cmp8, label %for.body, label %for.end, !dbg !2489

for.body:                                         ; preds = %for.cond
  %20 = load i32, i32* %i, align 4, !dbg !2490
  %idxprom = zext i32 %20 to i64, !dbg !2493
  %21 = load %struct.connectdata*, %struct.connectdata** %conn, align 8, !dbg !2493
  %ssl = getelementptr inbounds %struct.connectdata, %struct.connectdata* %21, i32 0, i32 38, !dbg !2494
  %arrayidx = getelementptr inbounds [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data]* %ssl, i64 0, i64 %idxprom, !dbg !2493
  %use = getelementptr inbounds %struct.ssl_connect_data, %struct.ssl_connect_data* %arrayidx, i32 0, i32 0, !dbg !2495
  %22 = load i8, i8* %use, align 4, !dbg !2495
  %tobool10 = trunc i8 %22 to i1, !dbg !2495
  br i1 %tobool10, label %if.then11, label %if.end, !dbg !2496

if.then11:                                        ; preds = %for.body
  br label %for.end, !dbg !2497

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !2499

for.inc:                                          ; preds = %if.end
  %23 = load i32, i32* %i, align 4, !dbg !2500
  %inc = add i32 %23, 1, !dbg !2500
  store i32 %inc, i32* %i, align 4, !dbg !2500
  br label %for.cond, !dbg !2502

for.end:                                          ; preds = %if.then11, %for.cond
  br label %if.end12, !dbg !2503

if.end12:                                         ; preds = %for.end, %land.lhs.true, %sw.bb4
  br label %sw.epilog, !dbg !2504

sw.default:                                       ; preds = %entry
  store i32 48, i32* %retval, align 4, !dbg !2505
  br label %return, !dbg !2505

sw.epilog:                                        ; preds = %if.end12, %sw.bb2, %sw.bb1, %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !2506
  br label %return, !dbg !2506

return:                                           ; preds = %sw.epilog, %sw.default
  %24 = load i32, i32* %retval, align 4, !dbg !2507
  ret i32 %24, !dbg !2507
}

; Function Attrs: nounwind uwtable
define internal i32 @getinfo_socket(%struct.Curl_easy* %data, i32 %info, i32* %param_socketp) #0 !dbg !1826 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %param_socketp.addr = alloca i32*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2508, metadata !1833), !dbg !2509
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !2510, metadata !1833), !dbg !2511
  store i32* %param_socketp, i32** %param_socketp.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %param_socketp.addr, metadata !2512, metadata !1833), !dbg !2513
  %0 = load i32, i32* %info.addr, align 4, !dbg !2514
  switch i32 %0, label %sw.default [
    i32 5242924, label %sw.bb
  ], !dbg !2515

sw.bb:                                            ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2516
  %call = call i32 @Curl_getconnectinfo(%struct.Curl_easy* %1, %struct.connectdata** null), !dbg !2518
  %2 = load i32*, i32** %param_socketp.addr, align 8, !dbg !2519
  store i32 %call, i32* %2, align 4, !dbg !2520
  br label %sw.epilog, !dbg !2521

sw.default:                                       ; preds = %entry
  store i32 48, i32* %retval, align 4, !dbg !2522
  br label %return, !dbg !2522

sw.epilog:                                        ; preds = %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !2523
  br label %return, !dbg !2523

return:                                           ; preds = %sw.epilog, %sw.default
  %3 = load i32, i32* %retval, align 4, !dbg !2524
  ret i32 %3, !dbg !2524
}

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

declare i32 @Curl_getconnectinfo(%struct.Curl_easy*, %struct.connectdata**) #3

declare %struct.curl_slist* @Curl_cookie_list(%struct.Curl_easy*) #3

declare i32 @Curl_ssl_backend() #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1829, !1830}
!llvm.ident = !{!1831}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1799, subprograms: !1802)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/getinfo.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !100, !111, !120, !126, !134, !173, !192, !212, !227, !244, !252, !266, !299, !368, !472, !491, !498, !637, !653, !665, !763, !773, !835, !855, !861, !887, !902, !911, !919, !948, !1187, !1239, !1678, !1731, !1790}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 434, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99}
!6 = !DIEnumerator(name: "CURLE_OK", value: 0)
!7 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!8 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!9 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!10 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!11 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!12 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!13 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!14 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!15 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!16 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!17 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!18 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!19 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!20 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!21 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!22 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!23 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!24 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!25 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!26 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!27 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!28 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!29 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!30 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!31 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!32 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!33 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!34 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!35 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!36 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!37 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!38 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!39 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!40 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!41 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!42 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!43 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!44 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!45 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!46 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!47 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!48 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!49 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!50 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!51 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!52 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!53 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!54 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!55 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!56 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!57 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!58 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!59 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!60 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!61 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!62 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!63 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!64 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!65 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!66 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!67 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!68 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!69 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!70 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!71 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!72 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!73 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!74 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!75 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!76 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!77 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!78 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!79 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!80 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!81 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!82 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!83 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!84 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!85 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!86 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!87 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!88 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!89 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!90 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!91 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!92 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!93 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!94 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!95 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!96 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!97 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!98 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!99 = !DIEnumerator(name: "CURL_LAST", value: 93)
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !101, line: 31, size: 32, align: 32, elements: !102)
!101 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http_chunks.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!102 = !{!103, !104, !105, !106, !107, !108, !109, !110}
!103 = !DIEnumerator(name: "CHUNK_HEX", value: 0)
!104 = !DIEnumerator(name: "CHUNK_LF", value: 1)
!105 = !DIEnumerator(name: "CHUNK_DATA", value: 2)
!106 = !DIEnumerator(name: "CHUNK_POSTLF", value: 3)
!107 = !DIEnumerator(name: "CHUNK_STOP", value: 4)
!108 = !DIEnumerator(name: "CHUNK_TRAILER", value: 5)
!109 = !DIEnumerator(name: "CHUNK_TRAILER_CR", value: 6)
!110 = !DIEnumerator(name: "CHUNK_TRAILER_POSTCR", value: 7)
!111 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 644, size: 32, align: 32, elements: !112)
!112 = !{!113, !114, !115, !116, !117, !118, !119}
!113 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!114 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!115 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!116 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!117 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!118 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!119 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
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
!252 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !253, file: !121, line: 1133, size: 32, align: 32, elements: !1674)
!253 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectdata", file: !121, line: 895, size: 13440, align: 64, elements: !254)
!254 = !{!255, !1255, !1267, !1268, !1269, !1270, !1271, !1297, !1298, !1302, !1303, !1304, !1305, !1312, !1313, !1314, !1322, !1323, !1324, !1325, !1326, !1327, !1328, !1329, !1330, !1331, !1332, !1333, !1334, !1335, !1336, !1337, !1338, !1339, !1341, !1342, !1344, !1351, !1357, !1366, !1367, !1368, !1369, !1370, !1406, !1407, !1408, !1409, !1463, !1464, !1465, !1466, !1467, !1480, !1481, !1482, !1483, !1484, !1485, !1486, !1487, !1488, !1489, !1493, !1494, !1495, !1496, !1659, !1660, !1661, !1662, !1663, !1664, !1666, !1673}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !253, file: !121, line: 899, baseType: !256, size: 64, align: 64)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_easy", file: !121, line: 1801, size: 160192, align: 64, elements: !258)
!258 = !{!259, !260, !261, !263, !288, !290, !313, !319, !320, !374, !450, !451, !454, !528, !1005, !1014, !1041, !1077, !1181, !1204, !1234, !1254}
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
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !4, line: 561, baseType: !3)
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
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !4, line: 100, baseType: !257)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !294, file: !295, line: 99, baseType: !308, size: 64, align: 64, offset: 128)
!308 = !DICompositeType(tag: DW_TAG_union_type, scope: !294, file: !295, line: 96, size: 64, align: 64, elements: !309)
!309 = !{!310, !312}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "whatever", scope: !308, file: !295, line: 97, baseType: !311, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !308, file: !295, line: 98, baseType: !289, size: 32, align: 32)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "sockets", scope: !257, file: !121, line: 1817, baseType: !314, size: 160, align: 32, offset: 448)
!314 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 160, align: 32, elements: !317)
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !4, line: 131, baseType: !316)
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
!453 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !4, line: 101, flags: DIFlagFwdDecl)
!454 = !DIDerivedType(tag: DW_TAG_member, name: "req", scope: !257, file: !121, line: 1828, baseType: !455, size: 2496, align: 64, offset: 960)
!455 = !DICompositeType(tag: DW_TAG_structure_type, name: "SingleRequest", file: !121, line: 658, size: 2496, align: 64, elements: !456)
!456 = !{!457, !460, !462, !463, !464, !465, !466, !467, !468, !469, !470, !471, !477, !478, !481, !482, !483, !484, !485, !486, !487, !488, !489, !490, !497, !504, !505, !508, !509, !510, !511, !512, !513, !514, !515, !516, !517, !518, !522, !523, !524, !525, !526, !527}
!457 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !455, file: !121, line: 659, baseType: !458, size: 64, align: 64)
!458 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !459, line: 216, baseType: !379)
!459 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!460 = !DIDerivedType(tag: DW_TAG_member, name: "bytecountp", scope: !455, file: !121, line: 660, baseType: !461, size: 64, align: 64, offset: 64)
!461 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !458, size: 64, align: 64)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "maxdownload", scope: !455, file: !121, line: 662, baseType: !458, size: 64, align: 64, offset: 128)
!463 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecountp", scope: !455, file: !121, line: 664, baseType: !461, size: 64, align: 64, offset: 192)
!464 = !DIDerivedType(tag: DW_TAG_member, name: "bytecount", scope: !455, file: !121, line: 666, baseType: !458, size: 64, align: 64, offset: 256)
!465 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !455, file: !121, line: 667, baseType: !458, size: 64, align: 64, offset: 320)
!466 = !DIDerivedType(tag: DW_TAG_member, name: "headerbytecount", scope: !455, file: !121, line: 669, baseType: !379, size: 64, align: 64, offset: 384)
!467 = !DIDerivedType(tag: DW_TAG_member, name: "deductheadercount", scope: !455, file: !121, line: 670, baseType: !379, size: 64, align: 64, offset: 448)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !455, file: !121, line: 676, baseType: !411, size: 128, align: 64, offset: 512)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !455, file: !121, line: 677, baseType: !411, size: 128, align: 64, offset: 640)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !455, file: !121, line: 678, baseType: !423, size: 8, align: 8, offset: 768)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "badheader", scope: !455, file: !121, line: 684, baseType: !472, size: 32, align: 32, offset: 800)
!472 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !455, file: !121, line: 679, size: 32, align: 32, elements: !473)
!473 = !{!474, !475, !476}
!474 = !DIEnumerator(name: "HEADER_NORMAL", value: 0)
!475 = !DIEnumerator(name: "HEADER_PARTHEADER", value: 1)
!476 = !DIEnumerator(name: "HEADER_ALLBAD", value: 2)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "headerline", scope: !455, file: !121, line: 686, baseType: !316, size: 32, align: 32, offset: 832)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "hbufp", scope: !455, file: !121, line: 688, baseType: !479, size: 64, align: 64, offset: 896)
!479 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !480, size: 64, align: 64)
!480 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "hbuflen", scope: !455, file: !121, line: 689, baseType: !347, size: 64, align: 64, offset: 960)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !455, file: !121, line: 690, baseType: !479, size: 64, align: 64, offset: 1024)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "str_start", scope: !455, file: !121, line: 691, baseType: !479, size: 64, align: 64, offset: 1088)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "end_ptr", scope: !455, file: !121, line: 692, baseType: !479, size: 64, align: 64, offset: 1152)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !455, file: !121, line: 693, baseType: !479, size: 64, align: 64, offset: 1216)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "content_range", scope: !455, file: !121, line: 694, baseType: !423, size: 8, align: 8, offset: 1280)
!487 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !455, file: !121, line: 695, baseType: !458, size: 64, align: 64, offset: 1344)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !455, file: !121, line: 697, baseType: !316, size: 32, align: 32, offset: 1408)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "start100", scope: !455, file: !121, line: 699, baseType: !411, size: 128, align: 64, offset: 1472)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "exp100", scope: !455, file: !121, line: 700, baseType: !491, size: 32, align: 32, offset: 1600)
!491 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "expect100", file: !121, line: 636, size: 32, align: 32, elements: !492)
!492 = !{!493, !494, !495, !496}
!493 = !DIEnumerator(name: "EXP100_SEND_DATA", value: 0)
!494 = !DIEnumerator(name: "EXP100_AWAITING_CONTINUE", value: 1)
!495 = !DIEnumerator(name: "EXP100_SENDING_REQUEST", value: 2)
!496 = !DIEnumerator(name: "EXP100_FAILED", value: 3)
!497 = !DIDerivedType(tag: DW_TAG_member, name: "upgr101", scope: !455, file: !121, line: 701, baseType: !498, size: 32, align: 32, offset: 1632)
!498 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "upgrade101", file: !121, line: 644, size: 32, align: 32, elements: !499)
!499 = !{!500, !501, !502, !503}
!500 = !DIEnumerator(name: "UPGR101_INIT", value: 0)
!501 = !DIEnumerator(name: "UPGR101_REQUESTED", value: 1)
!502 = !DIEnumerator(name: "UPGR101_RECEIVED", value: 2)
!503 = !DIEnumerator(name: "UPGR101_WORKING", value: 3)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "auto_decoding", scope: !455, file: !121, line: 703, baseType: !316, size: 32, align: 32, offset: 1664)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "timeofdoc", scope: !455, file: !121, line: 715, baseType: !506, size: 64, align: 64, offset: 1728)
!506 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !507, line: 75, baseType: !415)
!507 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!508 = !DIDerivedType(tag: DW_TAG_member, name: "bodywrites", scope: !455, file: !121, line: 716, baseType: !379, size: 64, align: 64, offset: 1792)
!509 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !455, file: !121, line: 718, baseType: !479, size: 64, align: 64, offset: 1856)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuf", scope: !455, file: !121, line: 719, baseType: !479, size: 64, align: 64, offset: 1920)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "maxfd", scope: !455, file: !121, line: 720, baseType: !315, size: 32, align: 32, offset: 1984)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "keepon", scope: !455, file: !121, line: 722, baseType: !316, size: 32, align: 32, offset: 2016)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "upload_done", scope: !455, file: !121, line: 724, baseType: !423, size: 8, align: 8, offset: 2048)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "ignorebody", scope: !455, file: !121, line: 727, baseType: !423, size: 8, align: 8, offset: 2056)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !455, file: !121, line: 728, baseType: !423, size: 8, align: 8, offset: 2064)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "location", scope: !455, file: !121, line: 731, baseType: !479, size: 64, align: 64, offset: 2112)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "newurl", scope: !455, file: !121, line: 733, baseType: !479, size: 64, align: 64, offset: 2176)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "upload_present", scope: !455, file: !121, line: 738, baseType: !519, size: 64, align: 64, offset: 2240)
!519 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !520, line: 109, baseType: !521)
!520 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!521 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !416, line: 172, baseType: !379)
!522 = !DIDerivedType(tag: DW_TAG_member, name: "upload_fromhere", scope: !455, file: !121, line: 744, baseType: !479, size: 64, align: 64, offset: 2304)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !455, file: !121, line: 746, baseType: !423, size: 8, align: 8, offset: 2368)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "upload_chunky", scope: !455, file: !121, line: 747, baseType: !423, size: 8, align: 8, offset: 2376)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "getheader", scope: !455, file: !121, line: 749, baseType: !423, size: 8, align: 8, offset: 2384)
!526 = !DIDerivedType(tag: DW_TAG_member, name: "forbidchunk", scope: !455, file: !121, line: 751, baseType: !423, size: 8, align: 8, offset: 2392)
!527 = !DIDerivedType(tag: DW_TAG_member, name: "protop", scope: !455, file: !121, line: 755, baseType: !311, size: 64, align: 64, offset: 2432)
!528 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !257, file: !121, line: 1829, baseType: !529, size: 13760, align: 64, offset: 3456)
!529 = !DICompositeType(tag: DW_TAG_structure_type, name: "UserDefined", file: !121, line: 1558, size: 13760, align: 64, elements: !530)
!530 = !{!531, !586, !587, !588, !589, !590, !591, !592, !593, !594, !595, !596, !597, !598, !599, !600, !601, !606, !607, !608, !609, !614, !615, !616, !618, !619, !620, !626, !631, !647, !659, !670, !671, !695, !696, !701, !702, !703, !708, !709, !710, !711, !712, !713, !714, !715, !716, !717, !718, !719, !720, !721, !722, !723, !724, !730, !731, !749, !750, !751, !752, !753, !754, !755, !756, !757, !758, !759, !760, !761, !770, !771, !783, !784, !820, !821, !825, !827, !828, !829, !830, !831, !832, !833, !840, !841, !867, !868, !869, !870, !871, !872, !873, !874, !875, !876, !877, !878, !879, !880, !881, !882, !883, !884, !885, !886, !893, !894, !895, !896, !897, !898, !899, !900, !909, !917, !925, !926, !927, !928, !929, !930, !931, !932, !933, !934, !935, !936, !937, !941, !942, !943, !944, !945, !946, !963, !964, !965, !972, !977, !982, !983, !984, !985, !986, !987, !988, !989, !990, !991, !992, !993, !994, !995, !996, !997, !998, !1004}
!531 = !DIDerivedType(tag: DW_TAG_member, name: "err", scope: !529, file: !121, line: 1559, baseType: !532, size: 64, align: 64)
!532 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !533, size: 64, align: 64)
!533 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !534, line: 48, baseType: !535)
!534 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!535 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !536, line: 245, size: 1728, align: 64, elements: !537)
!536 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!537 = !{!538, !539, !540, !541, !542, !543, !544, !545, !546, !547, !548, !549, !550, !558, !559, !560, !561, !563, !565, !567, !571, !574, !576, !577, !578, !579, !580, !581, !582}
!538 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !535, file: !536, line: 246, baseType: !316, size: 32, align: 32)
!539 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !535, file: !536, line: 251, baseType: !479, size: 64, align: 64, offset: 64)
!540 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !535, file: !536, line: 252, baseType: !479, size: 64, align: 64, offset: 128)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !535, file: !536, line: 253, baseType: !479, size: 64, align: 64, offset: 192)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !535, file: !536, line: 254, baseType: !479, size: 64, align: 64, offset: 256)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !535, file: !536, line: 255, baseType: !479, size: 64, align: 64, offset: 320)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !535, file: !536, line: 256, baseType: !479, size: 64, align: 64, offset: 384)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !535, file: !536, line: 257, baseType: !479, size: 64, align: 64, offset: 448)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !535, file: !536, line: 258, baseType: !479, size: 64, align: 64, offset: 512)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !535, file: !536, line: 260, baseType: !479, size: 64, align: 64, offset: 576)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !535, file: !536, line: 261, baseType: !479, size: 64, align: 64, offset: 640)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !535, file: !536, line: 262, baseType: !479, size: 64, align: 64, offset: 704)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !535, file: !536, line: 264, baseType: !551, size: 64, align: 64, offset: 768)
!551 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !552, size: 64, align: 64)
!552 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !536, line: 160, size: 192, align: 64, elements: !553)
!553 = !{!554, !555, !557}
!554 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !552, file: !536, line: 161, baseType: !551, size: 64, align: 64)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !552, file: !536, line: 162, baseType: !556, size: 64, align: 64, offset: 64)
!556 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !535, size: 64, align: 64)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !552, file: !536, line: 166, baseType: !316, size: 32, align: 32, offset: 128)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !535, file: !536, line: 266, baseType: !556, size: 64, align: 64, offset: 832)
!559 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !535, file: !536, line: 268, baseType: !316, size: 32, align: 32, offset: 896)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !535, file: !536, line: 272, baseType: !316, size: 32, align: 32, offset: 928)
!561 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !535, file: !536, line: 274, baseType: !562, size: 64, align: 64, offset: 960)
!562 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !416, line: 131, baseType: !379)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !535, file: !536, line: 278, baseType: !564, size: 16, align: 16, offset: 1024)
!564 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!565 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !535, file: !536, line: 279, baseType: !566, size: 8, align: 8, offset: 1040)
!566 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !535, file: !536, line: 280, baseType: !568, size: 8, align: 8, offset: 1048)
!568 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 8, align: 8, elements: !569)
!569 = !{!570}
!570 = !DISubrange(count: 1)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !535, file: !536, line: 284, baseType: !572, size: 64, align: 64, offset: 1088)
!572 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !573, size: 64, align: 64)
!573 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !536, line: 154, baseType: null)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !535, file: !536, line: 293, baseType: !575, size: 64, align: 64, offset: 1152)
!575 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !416, line: 132, baseType: !379)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !535, file: !536, line: 302, baseType: !311, size: 64, align: 64, offset: 1216)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !535, file: !536, line: 303, baseType: !311, size: 64, align: 64, offset: 1280)
!578 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !535, file: !536, line: 304, baseType: !311, size: 64, align: 64, offset: 1344)
!579 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !535, file: !536, line: 305, baseType: !311, size: 64, align: 64, offset: 1408)
!580 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !535, file: !536, line: 306, baseType: !347, size: 64, align: 64, offset: 1472)
!581 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !535, file: !536, line: 308, baseType: !316, size: 32, align: 32, offset: 1536)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !535, file: !536, line: 310, baseType: !583, size: 160, align: 8, offset: 1568)
!583 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 160, align: 8, elements: !584)
!584 = !{!585}
!585 = !DISubrange(count: 20)
!586 = !DIDerivedType(tag: DW_TAG_member, name: "debugdata", scope: !529, file: !121, line: 1560, baseType: !311, size: 64, align: 64, offset: 64)
!587 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuffer", scope: !529, file: !121, line: 1561, baseType: !479, size: 64, align: 64, offset: 128)
!588 = !DIDerivedType(tag: DW_TAG_member, name: "proxyport", scope: !529, file: !121, line: 1562, baseType: !379, size: 64, align: 64, offset: 192)
!589 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !529, file: !121, line: 1565, baseType: !311, size: 64, align: 64, offset: 256)
!590 = !DIDerivedType(tag: DW_TAG_member, name: "in_set", scope: !529, file: !121, line: 1566, baseType: !311, size: 64, align: 64, offset: 320)
!591 = !DIDerivedType(tag: DW_TAG_member, name: "writeheader", scope: !529, file: !121, line: 1567, baseType: !311, size: 64, align: 64, offset: 384)
!592 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_out", scope: !529, file: !121, line: 1568, baseType: !311, size: 64, align: 64, offset: 448)
!593 = !DIDerivedType(tag: DW_TAG_member, name: "use_port", scope: !529, file: !121, line: 1569, baseType: !379, size: 64, align: 64, offset: 512)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "httpauth", scope: !529, file: !121, line: 1570, baseType: !349, size: 64, align: 64, offset: 576)
!595 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauth", scope: !529, file: !121, line: 1571, baseType: !349, size: 64, align: 64, offset: 640)
!596 = !DIDerivedType(tag: DW_TAG_member, name: "followlocation", scope: !529, file: !121, line: 1572, baseType: !379, size: 64, align: 64, offset: 704)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "maxredirs", scope: !529, file: !121, line: 1573, baseType: !379, size: 64, align: 64, offset: 768)
!598 = !DIDerivedType(tag: DW_TAG_member, name: "keep_post", scope: !529, file: !121, line: 1576, baseType: !316, size: 32, align: 32, offset: 832)
!599 = !DIDerivedType(tag: DW_TAG_member, name: "free_referer", scope: !529, file: !121, line: 1578, baseType: !423, size: 8, align: 8, offset: 864)
!600 = !DIDerivedType(tag: DW_TAG_member, name: "postfields", scope: !529, file: !121, line: 1580, baseType: !311, size: 64, align: 64, offset: 896)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !529, file: !121, line: 1581, baseType: !602, size: 64, align: 64, offset: 960)
!602 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !4, line: 324, baseType: !603)
!603 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !604, size: 64, align: 64)
!604 = !DISubroutineType(types: !605)
!605 = !{!316, !311, !458, !316}
!606 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !529, file: !121, line: 1582, baseType: !458, size: 64, align: 64, offset: 1024)
!607 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !529, file: !121, line: 1585, baseType: !564, size: 16, align: 16, offset: 1088)
!608 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !529, file: !121, line: 1586, baseType: !316, size: 32, align: 32, offset: 1120)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !529, file: !121, line: 1588, baseType: !610, size: 64, align: 64, offset: 1152)
!610 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !4, line: 223, baseType: !611)
!611 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !612, size: 64, align: 64)
!612 = !DISubroutineType(types: !613)
!613 = !{!347, !479, !347, !347, !311}
!614 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !529, file: !121, line: 1589, baseType: !610, size: 64, align: 64, offset: 1216)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !529, file: !121, line: 1590, baseType: !610, size: 64, align: 64, offset: 1280)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !529, file: !121, line: 1591, baseType: !617, size: 64, align: 64, offset: 1344)
!617 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !4, line: 335, baseType: !611)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !529, file: !121, line: 1592, baseType: !316, size: 32, align: 32, offset: 1408)
!619 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !529, file: !121, line: 1593, baseType: !316, size: 32, align: 32, offset: 1440)
!620 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !529, file: !121, line: 1594, baseType: !621, size: 64, align: 64, offset: 1472)
!621 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !4, line: 183, baseType: !622)
!622 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !623, size: 64, align: 64)
!623 = !DISubroutineType(types: !624)
!624 = !{!316, !311, !625, !625, !625, !625}
!625 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !529, file: !121, line: 1595, baseType: !627, size: 64, align: 64, offset: 1536)
!627 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !4, line: 191, baseType: !628)
!628 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !629, size: 64, align: 64)
!629 = !DISubroutineType(types: !630)
!630 = !{!316, !311, !458, !458, !458, !458}
!631 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !529, file: !121, line: 1596, baseType: !632, size: 64, align: 64, offset: 1600)
!632 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !4, line: 420, baseType: !633)
!633 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !634, size: 64, align: 64)
!634 = !DISubroutineType(types: !635)
!635 = !{!316, !305, !636, !479, !347, !311}
!636 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !4, line: 418, baseType: !637)
!637 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 409, size: 32, align: 32, elements: !638)
!638 = !{!639, !640, !641, !642, !643, !644, !645, !646}
!639 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!640 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!641 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!642 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!643 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!644 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!645 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!646 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !529, file: !121, line: 1597, baseType: !648, size: 64, align: 64, offset: 1664)
!648 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !4, line: 388, baseType: !649)
!649 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !650, size: 64, align: 64)
!650 = !DISubroutineType(types: !651)
!651 = !{!652, !305, !316, !311}
!652 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !4, line: 380, baseType: !653)
!653 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 375, size: 32, align: 32, elements: !654)
!654 = !{!655, !656, !657, !658}
!655 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!656 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!657 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!658 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !529, file: !121, line: 1598, baseType: !660, size: 64, align: 64, offset: 1728)
!660 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !4, line: 353, baseType: !661)
!661 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !662, size: 64, align: 64)
!662 = !DISubroutineType(types: !663)
!663 = !{!316, !311, !315, !664}
!664 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !4, line: 344, baseType: !665)
!665 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 340, size: 32, align: 32, elements: !666)
!666 = !{!667, !668, !669}
!667 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!668 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!669 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !529, file: !121, line: 1599, baseType: !311, size: 64, align: 64, offset: 1792)
!671 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !529, file: !121, line: 1600, baseType: !672, size: 64, align: 64, offset: 1856)
!672 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !4, line: 368, baseType: !673)
!673 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !674, size: 64, align: 64)
!674 = !DISubroutineType(types: !675)
!675 = !{!315, !311, !664, !676}
!676 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !677, size: 64, align: 64)
!677 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !4, line: 357, size: 256, align: 32, elements: !678)
!678 = !{!679, !680, !681, !682, !684}
!679 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !677, file: !4, line: 358, baseType: !316, size: 32, align: 32)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !677, file: !4, line: 359, baseType: !316, size: 32, align: 32, offset: 32)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !677, file: !4, line: 360, baseType: !316, size: 32, align: 32, offset: 64)
!682 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !677, file: !4, line: 361, baseType: !683, size: 32, align: 32, offset: 96)
!683 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!684 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !677, file: !4, line: 364, baseType: !685, size: 128, align: 16, offset: 128)
!685 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !686, line: 149, size: 128, align: 16, elements: !687)
!686 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!687 = !{!688, !691}
!688 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !685, file: !686, line: 151, baseType: !689, size: 16, align: 16)
!689 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !690, line: 28, baseType: !564)
!690 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!691 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !685, file: !686, line: 152, baseType: !692, size: 112, align: 8, offset: 16)
!692 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 112, align: 8, elements: !693)
!693 = !{!694}
!694 = !DISubrange(count: 14)
!695 = !DIDerivedType(tag: DW_TAG_member, name: "opensocket_client", scope: !529, file: !121, line: 1603, baseType: !311, size: 64, align: 64, offset: 1920)
!696 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !529, file: !121, line: 1604, baseType: !697, size: 64, align: 64, offset: 1984)
!697 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !4, line: 373, baseType: !698)
!698 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !699, size: 64, align: 64)
!699 = !DISubroutineType(types: !700)
!700 = !{!316, !311, !315}
!701 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !529, file: !121, line: 1606, baseType: !311, size: 64, align: 64, offset: 2048)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !529, file: !121, line: 1608, baseType: !311, size: 64, align: 64, offset: 2112)
!703 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !529, file: !121, line: 1611, baseType: !704, size: 64, align: 64, offset: 2176)
!704 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !4, line: 637, baseType: !705)
!705 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !706, size: 64, align: 64)
!706 = !DISubroutineType(types: !707)
!707 = !{!289, !479, !347}
!708 = !DIDerivedType(tag: DW_TAG_member, name: "convtonetwork", scope: !529, file: !121, line: 1613, baseType: !704, size: 64, align: 64, offset: 2240)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "convfromutf8", scope: !529, file: !121, line: 1615, baseType: !704, size: 64, align: 64, offset: 2304)
!710 = !DIDerivedType(tag: DW_TAG_member, name: "progress_client", scope: !529, file: !121, line: 1617, baseType: !311, size: 64, align: 64, offset: 2368)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_client", scope: !529, file: !121, line: 1618, baseType: !311, size: 64, align: 64, offset: 2432)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !529, file: !121, line: 1619, baseType: !379, size: 64, align: 64, offset: 2496)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "connecttimeout", scope: !529, file: !121, line: 1620, baseType: !379, size: 64, align: 64, offset: 2560)
!714 = !DIDerivedType(tag: DW_TAG_member, name: "accepttimeout", scope: !529, file: !121, line: 1621, baseType: !379, size: 64, align: 64, offset: 2624)
!715 = !DIDerivedType(tag: DW_TAG_member, name: "server_response_timeout", scope: !529, file: !121, line: 1622, baseType: !379, size: 64, align: 64, offset: 2688)
!716 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_blksize", scope: !529, file: !121, line: 1623, baseType: !379, size: 64, align: 64, offset: 2752)
!717 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_no_options", scope: !529, file: !121, line: 1624, baseType: !423, size: 8, align: 8, offset: 2816)
!718 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !529, file: !121, line: 1625, baseType: !458, size: 64, align: 64, offset: 2880)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_limit", scope: !529, file: !121, line: 1626, baseType: !379, size: 64, align: 64, offset: 2944)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_time", scope: !529, file: !121, line: 1627, baseType: !379, size: 64, align: 64, offset: 3008)
!721 = !DIDerivedType(tag: DW_TAG_member, name: "max_send_speed", scope: !529, file: !121, line: 1628, baseType: !458, size: 64, align: 64, offset: 3072)
!722 = !DIDerivedType(tag: DW_TAG_member, name: "max_recv_speed", scope: !529, file: !121, line: 1629, baseType: !458, size: 64, align: 64, offset: 3136)
!723 = !DIDerivedType(tag: DW_TAG_member, name: "set_resume_from", scope: !529, file: !121, line: 1631, baseType: !458, size: 64, align: 64, offset: 3200)
!724 = !DIDerivedType(tag: DW_TAG_member, name: "headers", scope: !529, file: !121, line: 1632, baseType: !725, size: 64, align: 64, offset: 3264)
!725 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !726, size: 64, align: 64)
!726 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !4, line: 2176, size: 128, align: 64, elements: !727)
!727 = !{!728, !729}
!728 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !726, file: !4, line: 2177, baseType: !479, size: 64, align: 64)
!729 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !726, file: !4, line: 2178, baseType: !725, size: 64, align: 64, offset: 64)
!730 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !529, file: !121, line: 1633, baseType: !725, size: 64, align: 64, offset: 3328)
!731 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !529, file: !121, line: 1634, baseType: !732, size: 64, align: 64, offset: 3392)
!732 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !733, size: 64, align: 64)
!733 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !4, line: 137, size: 896, align: 64, elements: !734)
!734 = !{!735, !736, !737, !738, !739, !740, !741, !742, !743, !744, !745, !746, !747, !748}
!735 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !733, file: !4, line: 138, baseType: !732, size: 64, align: 64)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !733, file: !4, line: 139, baseType: !479, size: 64, align: 64, offset: 64)
!737 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !733, file: !4, line: 140, baseType: !379, size: 64, align: 64, offset: 128)
!738 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !733, file: !4, line: 141, baseType: !479, size: 64, align: 64, offset: 192)
!739 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !733, file: !4, line: 142, baseType: !379, size: 64, align: 64, offset: 256)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !733, file: !4, line: 144, baseType: !479, size: 64, align: 64, offset: 320)
!741 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !733, file: !4, line: 145, baseType: !379, size: 64, align: 64, offset: 384)
!742 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !733, file: !4, line: 146, baseType: !479, size: 64, align: 64, offset: 448)
!743 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !733, file: !4, line: 147, baseType: !725, size: 64, align: 64, offset: 512)
!744 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !733, file: !4, line: 148, baseType: !732, size: 64, align: 64, offset: 576)
!745 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !733, file: !4, line: 151, baseType: !379, size: 64, align: 64, offset: 640)
!746 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !733, file: !4, line: 171, baseType: !479, size: 64, align: 64, offset: 704)
!747 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !733, file: !4, line: 174, baseType: !311, size: 64, align: 64, offset: 768)
!748 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !733, file: !4, line: 176, baseType: !458, size: 64, align: 64, offset: 832)
!749 = !DIDerivedType(tag: DW_TAG_member, name: "sep_headers", scope: !529, file: !121, line: 1635, baseType: !423, size: 8, align: 8, offset: 3456)
!750 = !DIDerivedType(tag: DW_TAG_member, name: "cookiesession", scope: !529, file: !121, line: 1636, baseType: !423, size: 8, align: 8, offset: 3464)
!751 = !DIDerivedType(tag: DW_TAG_member, name: "crlf", scope: !529, file: !121, line: 1637, baseType: !423, size: 8, align: 8, offset: 3472)
!752 = !DIDerivedType(tag: DW_TAG_member, name: "quote", scope: !529, file: !121, line: 1638, baseType: !725, size: 64, align: 64, offset: 3520)
!753 = !DIDerivedType(tag: DW_TAG_member, name: "postquote", scope: !529, file: !121, line: 1639, baseType: !725, size: 64, align: 64, offset: 3584)
!754 = !DIDerivedType(tag: DW_TAG_member, name: "prequote", scope: !529, file: !121, line: 1640, baseType: !725, size: 64, align: 64, offset: 3648)
!755 = !DIDerivedType(tag: DW_TAG_member, name: "source_quote", scope: !529, file: !121, line: 1641, baseType: !725, size: 64, align: 64, offset: 3712)
!756 = !DIDerivedType(tag: DW_TAG_member, name: "source_prequote", scope: !529, file: !121, line: 1642, baseType: !725, size: 64, align: 64, offset: 3776)
!757 = !DIDerivedType(tag: DW_TAG_member, name: "source_postquote", scope: !529, file: !121, line: 1644, baseType: !725, size: 64, align: 64, offset: 3840)
!758 = !DIDerivedType(tag: DW_TAG_member, name: "telnet_options", scope: !529, file: !121, line: 1646, baseType: !725, size: 64, align: 64, offset: 3904)
!759 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !529, file: !121, line: 1647, baseType: !725, size: 64, align: 64, offset: 3968)
!760 = !DIDerivedType(tag: DW_TAG_member, name: "connect_to", scope: !529, file: !121, line: 1649, baseType: !725, size: 64, align: 64, offset: 4032)
!761 = !DIDerivedType(tag: DW_TAG_member, name: "timecondition", scope: !529, file: !121, line: 1651, baseType: !762, size: 32, align: 32, offset: 4096)
!762 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !4, line: 1929, baseType: !763)
!763 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1921, size: 32, align: 32, elements: !764)
!764 = !{!765, !766, !767, !768, !769}
!765 = !DIEnumerator(name: "CURL_TIMECOND_NONE", value: 0)
!766 = !DIEnumerator(name: "CURL_TIMECOND_IFMODSINCE", value: 1)
!767 = !DIEnumerator(name: "CURL_TIMECOND_IFUNMODSINCE", value: 2)
!768 = !DIEnumerator(name: "CURL_TIMECOND_LASTMOD", value: 3)
!769 = !DIEnumerator(name: "CURL_TIMECOND_LAST", value: 4)
!770 = !DIDerivedType(tag: DW_TAG_member, name: "timevalue", scope: !529, file: !121, line: 1652, baseType: !506, size: 64, align: 64, offset: 4160)
!771 = !DIDerivedType(tag: DW_TAG_member, name: "httpreq", scope: !529, file: !121, line: 1653, baseType: !772, size: 32, align: 32, offset: 4224)
!772 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_HttpReq", file: !121, line: 1249, baseType: !773)
!773 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1240, size: 32, align: 32, elements: !774)
!774 = !{!775, !776, !777, !778, !779, !780, !781, !782}
!775 = !DIEnumerator(name: "HTTPREQ_NONE", value: 0)
!776 = !DIEnumerator(name: "HTTPREQ_GET", value: 1)
!777 = !DIEnumerator(name: "HTTPREQ_POST", value: 2)
!778 = !DIEnumerator(name: "HTTPREQ_POST_FORM", value: 3)
!779 = !DIEnumerator(name: "HTTPREQ_PUT", value: 4)
!780 = !DIEnumerator(name: "HTTPREQ_HEAD", value: 5)
!781 = !DIEnumerator(name: "HTTPREQ_CUSTOM", value: 6)
!782 = !DIEnumerator(name: "HTTPREQ_LAST", value: 7)
!783 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !529, file: !121, line: 1654, baseType: !379, size: 64, align: 64, offset: 4288)
!784 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !529, file: !121, line: 1656, baseType: !785, size: 1408, align: 64, offset: 4352)
!785 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_config_data", file: !121, line: 366, size: 1408, align: 64, elements: !786)
!786 = !{!787, !802, !803, !804, !805, !806, !807, !812, !813, !814, !815, !816, !817, !818, !819}
!787 = !DIDerivedType(tag: DW_TAG_member, name: "primary", scope: !785, file: !121, line: 367, baseType: !788, size: 640, align: 64)
!788 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !121, line: 351, size: 640, align: 64, elements: !789)
!789 = !{!790, !791, !792, !793, !794, !795, !796, !797, !798, !799, !800, !801}
!790 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !788, file: !121, line: 352, baseType: !379, size: 64, align: 64)
!791 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !788, file: !121, line: 353, baseType: !379, size: 64, align: 64, offset: 64)
!792 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !788, file: !121, line: 354, baseType: !423, size: 8, align: 8, offset: 128)
!793 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !788, file: !121, line: 355, baseType: !423, size: 8, align: 8, offset: 136)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !788, file: !121, line: 356, baseType: !423, size: 8, align: 8, offset: 144)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !788, file: !121, line: 357, baseType: !479, size: 64, align: 64, offset: 192)
!796 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !788, file: !121, line: 358, baseType: !479, size: 64, align: 64, offset: 256)
!797 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !788, file: !121, line: 359, baseType: !479, size: 64, align: 64, offset: 320)
!798 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !788, file: !121, line: 360, baseType: !479, size: 64, align: 64, offset: 384)
!799 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !788, file: !121, line: 361, baseType: !479, size: 64, align: 64, offset: 448)
!800 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !788, file: !121, line: 362, baseType: !479, size: 64, align: 64, offset: 512)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !788, file: !121, line: 363, baseType: !423, size: 8, align: 8, offset: 576)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "enable_beast", scope: !785, file: !121, line: 368, baseType: !423, size: 8, align: 8, offset: 640)
!803 = !DIDerivedType(tag: DW_TAG_member, name: "no_revoke", scope: !785, file: !121, line: 370, baseType: !423, size: 8, align: 8, offset: 648)
!804 = !DIDerivedType(tag: DW_TAG_member, name: "certverifyresult", scope: !785, file: !121, line: 371, baseType: !379, size: 64, align: 64, offset: 704)
!805 = !DIDerivedType(tag: DW_TAG_member, name: "CRLfile", scope: !785, file: !121, line: 372, baseType: !479, size: 64, align: 64, offset: 768)
!806 = !DIDerivedType(tag: DW_TAG_member, name: "issuercert", scope: !785, file: !121, line: 373, baseType: !479, size: 64, align: 64, offset: 832)
!807 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctx", scope: !785, file: !121, line: 374, baseType: !808, size: 64, align: 64, offset: 896)
!808 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !4, line: 639, baseType: !809)
!809 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !810, size: 64, align: 64)
!810 = !DISubroutineType(types: !811)
!811 = !{!289, !305, !311, !311}
!812 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctxp", scope: !785, file: !121, line: 375, baseType: !311, size: 64, align: 64, offset: 960)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !785, file: !121, line: 376, baseType: !423, size: 8, align: 8, offset: 1024)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "falsestart", scope: !785, file: !121, line: 377, baseType: !423, size: 8, align: 8, offset: 1032)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "cert", scope: !785, file: !121, line: 379, baseType: !479, size: 64, align: 64, offset: 1088)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "cert_type", scope: !785, file: !121, line: 380, baseType: !479, size: 64, align: 64, offset: 1152)
!817 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !785, file: !121, line: 381, baseType: !479, size: 64, align: 64, offset: 1216)
!818 = !DIDerivedType(tag: DW_TAG_member, name: "key_type", scope: !785, file: !121, line: 382, baseType: !479, size: 64, align: 64, offset: 1280)
!819 = !DIDerivedType(tag: DW_TAG_member, name: "key_passwd", scope: !785, file: !121, line: 383, baseType: !479, size: 64, align: 64, offset: 1344)
!820 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !529, file: !121, line: 1657, baseType: !785, size: 1408, align: 64, offset: 5760)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "general_ssl", scope: !529, file: !121, line: 1658, baseType: !822, size: 64, align: 64, offset: 7168)
!822 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_general_config", file: !121, line: 392, size: 64, align: 64, elements: !823)
!823 = !{!824}
!824 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !822, file: !121, line: 393, baseType: !347, size: 64, align: 64)
!825 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !529, file: !121, line: 1659, baseType: !826, size: 32, align: 32, offset: 7232)
!826 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !4, line: 657, baseType: !111)
!827 = !DIDerivedType(tag: DW_TAG_member, name: "dns_cache_timeout", scope: !529, file: !121, line: 1660, baseType: !379, size: 64, align: 64, offset: 7296)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !529, file: !121, line: 1661, baseType: !379, size: 64, align: 64, offset: 7360)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "private_data", scope: !529, file: !121, line: 1662, baseType: !311, size: 64, align: 64, offset: 7424)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "http200aliases", scope: !529, file: !121, line: 1664, baseType: !725, size: 64, align: 64, offset: 7488)
!831 = !DIDerivedType(tag: DW_TAG_member, name: "ipver", scope: !529, file: !121, line: 1666, baseType: !379, size: 64, align: 64, offset: 7552)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesize", scope: !529, file: !121, line: 1669, baseType: !458, size: 64, align: 64, offset: 7616)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_filemethod", scope: !529, file: !121, line: 1671, baseType: !834, size: 32, align: 32, offset: 7680)
!834 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpfile", file: !135, line: 98, baseType: !835)
!835 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !135, line: 93, size: 32, align: 32, elements: !836)
!836 = !{!837, !838, !839}
!837 = !DIEnumerator(name: "FTPFILE_MULTICWD", value: 1)
!838 = !DIEnumerator(name: "FTPFILE_NOCWD", value: 2)
!839 = !DIEnumerator(name: "FTPFILE_SINGLECWD", value: 3)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_create_missing_dirs", scope: !529, file: !121, line: 1673, baseType: !316, size: 32, align: 32, offset: 7712)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc", scope: !529, file: !121, line: 1677, baseType: !842, size: 64, align: 64, offset: 7744)
!842 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !4, line: 739, baseType: !843)
!843 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !844, size: 64, align: 64)
!844 = !DISubroutineType(types: !845)
!845 = !{!316, !305, !846, !846, !861, !311}
!846 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !847, size: 64, align: 64)
!847 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !848)
!848 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !4, line: 711, size: 192, align: 64, elements: !849)
!849 = !{!850, !853, !854}
!850 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !848, file: !4, line: 712, baseType: !851, size: 64, align: 64)
!851 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !852, size: 64, align: 64)
!852 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !480)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !848, file: !4, line: 714, baseType: !347, size: 64, align: 64, offset: 64)
!854 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !848, file: !4, line: 715, baseType: !855, size: 32, align: 32, offset: 128)
!855 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !4, line: 704, size: 32, align: 32, elements: !856)
!856 = !{!857, !858, !859, !860}
!857 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!858 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!859 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!860 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!861 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !4, line: 731, size: 32, align: 32, elements: !862)
!862 = !{!863, !864, !865, !866}
!863 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!864 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!865 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!866 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!867 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc_userp", scope: !529, file: !121, line: 1678, baseType: !311, size: 64, align: 64, offset: 7808)
!868 = !DIDerivedType(tag: DW_TAG_member, name: "printhost", scope: !529, file: !121, line: 1684, baseType: !423, size: 8, align: 8, offset: 7872)
!869 = !DIDerivedType(tag: DW_TAG_member, name: "get_filetime", scope: !529, file: !121, line: 1685, baseType: !423, size: 8, align: 8, offset: 7880)
!870 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_thru_httpproxy", scope: !529, file: !121, line: 1686, baseType: !423, size: 8, align: 8, offset: 7888)
!871 = !DIDerivedType(tag: DW_TAG_member, name: "prefer_ascii", scope: !529, file: !121, line: 1687, baseType: !423, size: 8, align: 8, offset: 7896)
!872 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_append", scope: !529, file: !121, line: 1688, baseType: !423, size: 8, align: 8, offset: 7904)
!873 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_list_only", scope: !529, file: !121, line: 1689, baseType: !423, size: 8, align: 8, offset: 7912)
!874 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_port", scope: !529, file: !121, line: 1690, baseType: !423, size: 8, align: 8, offset: 7920)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "hide_progress", scope: !529, file: !121, line: 1691, baseType: !423, size: 8, align: 8, offset: 7928)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "http_fail_on_error", scope: !529, file: !121, line: 1692, baseType: !423, size: 8, align: 8, offset: 7936)
!877 = !DIDerivedType(tag: DW_TAG_member, name: "http_keep_sending_on_error", scope: !529, file: !121, line: 1693, baseType: !423, size: 8, align: 8, offset: 7944)
!878 = !DIDerivedType(tag: DW_TAG_member, name: "http_follow_location", scope: !529, file: !121, line: 1694, baseType: !423, size: 8, align: 8, offset: 7952)
!879 = !DIDerivedType(tag: DW_TAG_member, name: "http_transfer_encoding", scope: !529, file: !121, line: 1695, baseType: !423, size: 8, align: 8, offset: 7960)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "http_disable_hostname_check_before_authentication", scope: !529, file: !121, line: 1696, baseType: !423, size: 8, align: 8, offset: 7968)
!881 = !DIDerivedType(tag: DW_TAG_member, name: "include_header", scope: !529, file: !121, line: 1697, baseType: !423, size: 8, align: 8, offset: 7976)
!882 = !DIDerivedType(tag: DW_TAG_member, name: "http_set_referer", scope: !529, file: !121, line: 1698, baseType: !423, size: 8, align: 8, offset: 7984)
!883 = !DIDerivedType(tag: DW_TAG_member, name: "http_auto_referer", scope: !529, file: !121, line: 1699, baseType: !423, size: 8, align: 8, offset: 7992)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "opt_no_body", scope: !529, file: !121, line: 1700, baseType: !423, size: 8, align: 8, offset: 8000)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "upload", scope: !529, file: !121, line: 1701, baseType: !423, size: 8, align: 8, offset: 8008)
!886 = !DIDerivedType(tag: DW_TAG_member, name: "use_netrc", scope: !529, file: !121, line: 1703, baseType: !887, size: 32, align: 32, offset: 8032)
!887 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !4, line: 1867, size: 32, align: 32, elements: !888)
!888 = !{!889, !890, !891, !892}
!889 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!890 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!891 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!892 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!893 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !529, file: !121, line: 1704, baseType: !423, size: 8, align: 8, offset: 8064)
!894 = !DIDerivedType(tag: DW_TAG_member, name: "krb", scope: !529, file: !121, line: 1705, baseType: !423, size: 8, align: 8, offset: 8072)
!895 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_forbid", scope: !529, file: !121, line: 1706, baseType: !423, size: 8, align: 8, offset: 8080)
!896 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_fresh", scope: !529, file: !121, line: 1707, baseType: !423, size: 8, align: 8, offset: 8088)
!897 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !529, file: !121, line: 1708, baseType: !423, size: 8, align: 8, offset: 8096)
!898 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !529, file: !121, line: 1709, baseType: !423, size: 8, align: 8, offset: 8104)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_pret", scope: !529, file: !121, line: 1710, baseType: !423, size: 8, align: 8, offset: 8112)
!900 = !DIDerivedType(tag: DW_TAG_member, name: "use_ssl", scope: !529, file: !121, line: 1712, baseType: !901, size: 32, align: 32, offset: 8128)
!901 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !4, line: 752, baseType: !902)
!902 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 746, size: 32, align: 32, elements: !903)
!903 = !{!904, !905, !906, !907, !908}
!904 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!905 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!906 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!907 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!908 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!909 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !529, file: !121, line: 1714, baseType: !910, size: 32, align: 32, offset: 8160)
!910 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !4, line: 795, baseType: !911)
!911 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 790, size: 32, align: 32, elements: !912)
!912 = !{!913, !914, !915, !916}
!913 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!914 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!915 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!916 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!917 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !529, file: !121, line: 1715, baseType: !918, size: 32, align: 32, offset: 8192)
!918 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !4, line: 787, baseType: !919)
!919 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 782, size: 32, align: 32, elements: !920)
!920 = !{!921, !922, !923, !924}
!921 = !DIEnumerator(name: "CURLFTPSSL_CCC_NONE", value: 0)
!922 = !DIEnumerator(name: "CURLFTPSSL_CCC_PASSIVE", value: 1)
!923 = !DIEnumerator(name: "CURLFTPSSL_CCC_ACTIVE", value: 2)
!924 = !DIEnumerator(name: "CURLFTPSSL_CCC_LAST", value: 3)
!925 = !DIDerivedType(tag: DW_TAG_member, name: "no_signal", scope: !529, file: !121, line: 1716, baseType: !423, size: 8, align: 8, offset: 8224)
!926 = !DIDerivedType(tag: DW_TAG_member, name: "global_dns_cache", scope: !529, file: !121, line: 1717, baseType: !423, size: 8, align: 8, offset: 8232)
!927 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_nodelay", scope: !529, file: !121, line: 1718, baseType: !423, size: 8, align: 8, offset: 8240)
!928 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !529, file: !121, line: 1719, baseType: !423, size: 8, align: 8, offset: 8248)
!929 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_skip_ip", scope: !529, file: !121, line: 1720, baseType: !423, size: 8, align: 8, offset: 8256)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "connect_only", scope: !529, file: !121, line: 1722, baseType: !423, size: 8, align: 8, offset: 8264)
!931 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_auth_types", scope: !529, file: !121, line: 1723, baseType: !379, size: 64, align: 64, offset: 8320)
!932 = !DIDerivedType(tag: DW_TAG_member, name: "http_te_skip", scope: !529, file: !121, line: 1724, baseType: !423, size: 8, align: 8, offset: 8384)
!933 = !DIDerivedType(tag: DW_TAG_member, name: "http_ce_skip", scope: !529, file: !121, line: 1726, baseType: !423, size: 8, align: 8, offset: 8392)
!934 = !DIDerivedType(tag: DW_TAG_member, name: "new_file_perms", scope: !529, file: !121, line: 1728, baseType: !379, size: 64, align: 64, offset: 8448)
!935 = !DIDerivedType(tag: DW_TAG_member, name: "new_directory_perms", scope: !529, file: !121, line: 1729, baseType: !379, size: 64, align: 64, offset: 8512)
!936 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_transfer_mode", scope: !529, file: !121, line: 1730, baseType: !423, size: 8, align: 8, offset: 8576)
!937 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !529, file: !121, line: 1732, baseType: !938, size: 3584, align: 64, offset: 8640)
!938 = !DICompositeType(tag: DW_TAG_array_type, baseType: !479, size: 3584, align: 64, elements: !939)
!939 = !{!940}
!940 = !DISubrange(count: 56)
!941 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !529, file: !121, line: 1733, baseType: !683, size: 32, align: 32, offset: 12224)
!942 = !DIDerivedType(tag: DW_TAG_member, name: "allowed_protocols", scope: !529, file: !121, line: 1734, baseType: !379, size: 64, align: 64, offset: 12288)
!943 = !DIDerivedType(tag: DW_TAG_member, name: "redir_protocols", scope: !529, file: !121, line: 1735, baseType: !379, size: 64, align: 64, offset: 12352)
!944 = !DIDerivedType(tag: DW_TAG_member, name: "mail_rcpt", scope: !529, file: !121, line: 1739, baseType: !725, size: 64, align: 64, offset: 12416)
!945 = !DIDerivedType(tag: DW_TAG_member, name: "sasl_ir", scope: !529, file: !121, line: 1740, baseType: !423, size: 8, align: 8, offset: 12480)
!946 = !DIDerivedType(tag: DW_TAG_member, name: "rtspreq", scope: !529, file: !121, line: 1742, baseType: !947, size: 32, align: 32, offset: 12512)
!947 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_RtspReq", file: !121, line: 1265, baseType: !948)
!948 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1251, size: 32, align: 32, elements: !949)
!949 = !{!950, !951, !952, !953, !954, !955, !956, !957, !958, !959, !960, !961, !962}
!950 = !DIEnumerator(name: "RTSPREQ_NONE", value: 0)
!951 = !DIEnumerator(name: "RTSPREQ_OPTIONS", value: 1)
!952 = !DIEnumerator(name: "RTSPREQ_DESCRIBE", value: 2)
!953 = !DIEnumerator(name: "RTSPREQ_ANNOUNCE", value: 3)
!954 = !DIEnumerator(name: "RTSPREQ_SETUP", value: 4)
!955 = !DIEnumerator(name: "RTSPREQ_PLAY", value: 5)
!956 = !DIEnumerator(name: "RTSPREQ_PAUSE", value: 6)
!957 = !DIEnumerator(name: "RTSPREQ_TEARDOWN", value: 7)
!958 = !DIEnumerator(name: "RTSPREQ_GET_PARAMETER", value: 8)
!959 = !DIEnumerator(name: "RTSPREQ_SET_PARAMETER", value: 9)
!960 = !DIEnumerator(name: "RTSPREQ_RECORD", value: 10)
!961 = !DIEnumerator(name: "RTSPREQ_RECEIVE", value: 11)
!962 = !DIEnumerator(name: "RTSPREQ_LAST", value: 12)
!963 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !529, file: !121, line: 1743, baseType: !379, size: 64, align: 64, offset: 12544)
!964 = !DIDerivedType(tag: DW_TAG_member, name: "wildcardmatch", scope: !529, file: !121, line: 1744, baseType: !423, size: 8, align: 8, offset: 12608)
!965 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_bgn", scope: !529, file: !121, line: 1745, baseType: !966, size: 64, align: 64, offset: 12672)
!966 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !4, line: 292, baseType: !967)
!967 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !968, size: 64, align: 64)
!968 = !DISubroutineType(types: !969)
!969 = !{!379, !970, !311, !316}
!970 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !971, size: 64, align: 64)
!971 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!972 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !529, file: !121, line: 1747, baseType: !973, size: 64, align: 64, offset: 12736)
!973 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !4, line: 306, baseType: !974)
!974 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !975, size: 64, align: 64)
!975 = !DISubroutineType(types: !976)
!976 = !{!379, !311}
!977 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !529, file: !121, line: 1749, baseType: !978, size: 64, align: 64, offset: 12800)
!978 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !4, line: 315, baseType: !979)
!979 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !980, size: 64, align: 64)
!980 = !DISubroutineType(types: !981)
!981 = !{!316, !311, !851, !851}
!982 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch_data", scope: !529, file: !121, line: 1751, baseType: !311, size: 64, align: 64, offset: 12864)
!983 = !DIDerivedType(tag: DW_TAG_member, name: "gssapi_delegation", scope: !529, file: !121, line: 1753, baseType: !379, size: 64, align: 64, offset: 12928)
!984 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepalive", scope: !529, file: !121, line: 1756, baseType: !423, size: 8, align: 8, offset: 12992)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepidle", scope: !529, file: !121, line: 1757, baseType: !379, size: 64, align: 64, offset: 13056)
!986 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepintvl", scope: !529, file: !121, line: 1758, baseType: !379, size: 64, align: 64, offset: 13120)
!987 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !529, file: !121, line: 1759, baseType: !423, size: 8, align: 8, offset: 13184)
!988 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !529, file: !121, line: 1761, baseType: !347, size: 64, align: 64, offset: 13248)
!989 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_npn", scope: !529, file: !121, line: 1763, baseType: !423, size: 8, align: 8, offset: 13312)
!990 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_alpn", scope: !529, file: !121, line: 1764, baseType: !423, size: 8, align: 8, offset: 13320)
!991 = !DIDerivedType(tag: DW_TAG_member, name: "path_as_is", scope: !529, file: !121, line: 1765, baseType: !423, size: 8, align: 8, offset: 13328)
!992 = !DIDerivedType(tag: DW_TAG_member, name: "pipewait", scope: !529, file: !121, line: 1766, baseType: !423, size: 8, align: 8, offset: 13336)
!993 = !DIDerivedType(tag: DW_TAG_member, name: "expect_100_timeout", scope: !529, file: !121, line: 1768, baseType: !379, size: 64, align: 64, offset: 13376)
!994 = !DIDerivedType(tag: DW_TAG_member, name: "suppress_connect_headers", scope: !529, file: !121, line: 1769, baseType: !423, size: 8, align: 8, offset: 13440)
!995 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !529, file: !121, line: 1772, baseType: !256, size: 64, align: 64, offset: 13504)
!996 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !529, file: !121, line: 1773, baseType: !423, size: 8, align: 8, offset: 13568)
!997 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !529, file: !121, line: 1774, baseType: !316, size: 32, align: 32, offset: 13600)
!998 = !DIDerivedType(tag: DW_TAG_member, name: "stream_dependents", scope: !529, file: !121, line: 1776, baseType: !999, size: 64, align: 64, offset: 13632)
!999 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1000, size: 64, align: 64)
!1000 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_http2_dep", file: !121, line: 1292, size: 128, align: 64, elements: !1001)
!1001 = !{!1002, !1003}
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1000, file: !121, line: 1293, baseType: !999, size: 64, align: 64)
!1003 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1000, file: !121, line: 1294, baseType: !256, size: 64, align: 64, offset: 64)
!1004 = !DIDerivedType(tag: DW_TAG_member, name: "abstract_unix_socket", scope: !529, file: !121, line: 1778, baseType: !423, size: 8, align: 8, offset: 13696)
!1005 = !DIDerivedType(tag: DW_TAG_member, name: "change", scope: !257, file: !121, line: 1830, baseType: !1006, size: 384, align: 64, offset: 17216)
!1006 = !DICompositeType(tag: DW_TAG_structure_type, name: "DynamicStatic", file: !121, line: 1444, size: 384, align: 64, elements: !1007)
!1007 = !{!1008, !1009, !1010, !1011, !1012, !1013}
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "url", scope: !1006, file: !121, line: 1445, baseType: !479, size: 64, align: 64)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "url_alloc", scope: !1006, file: !121, line: 1446, baseType: !423, size: 8, align: 8, offset: 64)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "referer", scope: !1006, file: !121, line: 1447, baseType: !479, size: 64, align: 64, offset: 128)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "referer_alloc", scope: !1006, file: !121, line: 1448, baseType: !423, size: 8, align: 8, offset: 192)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "cookielist", scope: !1006, file: !121, line: 1449, baseType: !725, size: 64, align: 64, offset: 256)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !1006, file: !121, line: 1451, baseType: !725, size: 64, align: 64, offset: 320)
!1014 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !257, file: !121, line: 1831, baseType: !1015, size: 64, align: 64, offset: 17600)
!1015 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1016, size: 64, align: 64)
!1016 = !DICompositeType(tag: DW_TAG_structure_type, name: "CookieInfo", file: !1017, line: 48, size: 320, align: 64, elements: !1018)
!1017 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/cookie.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1018 = !{!1019, !1037, !1038, !1039, !1040}
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !1016, file: !1017, line: 50, baseType: !1020, size: 64, align: 64)
!1020 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1021, size: 64, align: 64)
!1021 = !DICompositeType(tag: DW_TAG_structure_type, name: "Cookie", file: !1017, line: 28, size: 768, align: 64, elements: !1022)
!1022 = !{!1023, !1024, !1025, !1026, !1027, !1028, !1029, !1030, !1031, !1032, !1033, !1034, !1035, !1036}
!1023 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1021, file: !1017, line: 29, baseType: !1020, size: 64, align: 64)
!1024 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1021, file: !1017, line: 30, baseType: !479, size: 64, align: 64, offset: 64)
!1025 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !1021, file: !1017, line: 31, baseType: !479, size: 64, align: 64, offset: 128)
!1026 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1021, file: !1017, line: 32, baseType: !479, size: 64, align: 64, offset: 192)
!1027 = !DIDerivedType(tag: DW_TAG_member, name: "spath", scope: !1021, file: !1017, line: 33, baseType: !479, size: 64, align: 64, offset: 256)
!1028 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1021, file: !1017, line: 34, baseType: !479, size: 64, align: 64, offset: 320)
!1029 = !DIDerivedType(tag: DW_TAG_member, name: "expires", scope: !1021, file: !1017, line: 35, baseType: !458, size: 64, align: 64, offset: 384)
!1030 = !DIDerivedType(tag: DW_TAG_member, name: "expirestr", scope: !1021, file: !1017, line: 36, baseType: !479, size: 64, align: 64, offset: 448)
!1031 = !DIDerivedType(tag: DW_TAG_member, name: "tailmatch", scope: !1021, file: !1017, line: 37, baseType: !423, size: 8, align: 8, offset: 512)
!1032 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !1021, file: !1017, line: 40, baseType: !479, size: 64, align: 64, offset: 576)
!1033 = !DIDerivedType(tag: DW_TAG_member, name: "maxage", scope: !1021, file: !1017, line: 41, baseType: !479, size: 64, align: 64, offset: 640)
!1034 = !DIDerivedType(tag: DW_TAG_member, name: "secure", scope: !1021, file: !1017, line: 43, baseType: !423, size: 8, align: 8, offset: 704)
!1035 = !DIDerivedType(tag: DW_TAG_member, name: "livecookie", scope: !1021, file: !1017, line: 44, baseType: !423, size: 8, align: 8, offset: 712)
!1036 = !DIDerivedType(tag: DW_TAG_member, name: "httponly", scope: !1021, file: !1017, line: 45, baseType: !423, size: 8, align: 8, offset: 720)
!1037 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !1016, file: !1017, line: 52, baseType: !479, size: 64, align: 64, offset: 64)
!1038 = !DIDerivedType(tag: DW_TAG_member, name: "running", scope: !1016, file: !1017, line: 53, baseType: !423, size: 8, align: 8, offset: 128)
!1039 = !DIDerivedType(tag: DW_TAG_member, name: "numcookies", scope: !1016, file: !1017, line: 54, baseType: !379, size: 64, align: 64, offset: 192)
!1040 = !DIDerivedType(tag: DW_TAG_member, name: "newsession", scope: !1016, file: !1017, line: 55, baseType: !423, size: 8, align: 8, offset: 256)
!1041 = !DIDerivedType(tag: DW_TAG_member, name: "progress", scope: !257, file: !121, line: 1835, baseType: !1042, size: 3200, align: 64, offset: 17664)
!1042 = !DICompositeType(tag: DW_TAG_structure_type, name: "Progress", file: !121, line: 1195, size: 3200, align: 64, elements: !1043)
!1043 = !{!1044, !1045, !1046, !1047, !1048, !1049, !1050, !1051, !1052, !1053, !1054, !1055, !1056, !1057, !1058, !1059, !1060, !1061, !1062, !1063, !1064, !1065, !1066, !1067, !1068, !1069, !1070, !1074, !1076}
!1044 = !DIDerivedType(tag: DW_TAG_member, name: "lastshow", scope: !1042, file: !121, line: 1196, baseType: !506, size: 64, align: 64)
!1045 = !DIDerivedType(tag: DW_TAG_member, name: "size_dl", scope: !1042, file: !121, line: 1198, baseType: !458, size: 64, align: 64, offset: 64)
!1046 = !DIDerivedType(tag: DW_TAG_member, name: "size_ul", scope: !1042, file: !121, line: 1199, baseType: !458, size: 64, align: 64, offset: 128)
!1047 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !1042, file: !121, line: 1200, baseType: !458, size: 64, align: 64, offset: 192)
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "uploaded", scope: !1042, file: !121, line: 1201, baseType: !458, size: 64, align: 64, offset: 256)
!1049 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1042, file: !121, line: 1203, baseType: !458, size: 64, align: 64, offset: 320)
!1050 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !1042, file: !121, line: 1205, baseType: !423, size: 8, align: 8, offset: 384)
!1051 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !1042, file: !121, line: 1206, baseType: !316, size: 32, align: 32, offset: 416)
!1052 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1042, file: !121, line: 1207, baseType: !316, size: 32, align: 32, offset: 448)
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "timespent", scope: !1042, file: !121, line: 1209, baseType: !625, size: 64, align: 64, offset: 512)
!1054 = !DIDerivedType(tag: DW_TAG_member, name: "dlspeed", scope: !1042, file: !121, line: 1211, baseType: !458, size: 64, align: 64, offset: 576)
!1055 = !DIDerivedType(tag: DW_TAG_member, name: "ulspeed", scope: !1042, file: !121, line: 1212, baseType: !458, size: 64, align: 64, offset: 640)
!1056 = !DIDerivedType(tag: DW_TAG_member, name: "t_nslookup", scope: !1042, file: !121, line: 1214, baseType: !625, size: 64, align: 64, offset: 704)
!1057 = !DIDerivedType(tag: DW_TAG_member, name: "t_connect", scope: !1042, file: !121, line: 1215, baseType: !625, size: 64, align: 64, offset: 768)
!1058 = !DIDerivedType(tag: DW_TAG_member, name: "t_appconnect", scope: !1042, file: !121, line: 1216, baseType: !625, size: 64, align: 64, offset: 832)
!1059 = !DIDerivedType(tag: DW_TAG_member, name: "t_pretransfer", scope: !1042, file: !121, line: 1217, baseType: !625, size: 64, align: 64, offset: 896)
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "t_starttransfer", scope: !1042, file: !121, line: 1218, baseType: !625, size: 64, align: 64, offset: 960)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "t_redirect", scope: !1042, file: !121, line: 1219, baseType: !625, size: 64, align: 64, offset: 1024)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !1042, file: !121, line: 1221, baseType: !411, size: 128, align: 64, offset: 1088)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "t_startsingle", scope: !1042, file: !121, line: 1222, baseType: !411, size: 128, align: 64, offset: 1216)
!1064 = !DIDerivedType(tag: DW_TAG_member, name: "t_startop", scope: !1042, file: !121, line: 1223, baseType: !411, size: 128, align: 64, offset: 1344)
!1065 = !DIDerivedType(tag: DW_TAG_member, name: "t_acceptdata", scope: !1042, file: !121, line: 1224, baseType: !411, size: 128, align: 64, offset: 1472)
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_start", scope: !1042, file: !121, line: 1227, baseType: !411, size: 128, align: 64, offset: 1600)
!1067 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_size", scope: !1042, file: !121, line: 1228, baseType: !458, size: 64, align: 64, offset: 1728)
!1068 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_start", scope: !1042, file: !121, line: 1230, baseType: !411, size: 128, align: 64, offset: 1792)
!1069 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_size", scope: !1042, file: !121, line: 1231, baseType: !458, size: 64, align: 64, offset: 1920)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "speeder", scope: !1042, file: !121, line: 1235, baseType: !1071, size: 384, align: 64, offset: 1984)
!1071 = !DICompositeType(tag: DW_TAG_array_type, baseType: !458, size: 384, align: 64, elements: !1072)
!1072 = !{!1073}
!1073 = !DISubrange(count: 6)
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_time", scope: !1042, file: !121, line: 1236, baseType: !1075, size: 768, align: 64, offset: 2368)
!1075 = !DICompositeType(tag: DW_TAG_array_type, baseType: !411, size: 768, align: 64, elements: !1072)
!1076 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_c", scope: !1042, file: !121, line: 1237, baseType: !316, size: 32, align: 32, offset: 3136)
!1077 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !257, file: !121, line: 1836, baseType: !1078, size: 136640, align: 64, offset: 20864)
!1078 = !DICompositeType(tag: DW_TAG_structure_type, name: "UrlState", file: !121, line: 1310, size: 136640, align: 64, elements: !1079)
!1079 = !{!1080, !1082, !1083, !1084, !1085, !1086, !1087, !1088, !1092, !1093, !1094, !1095, !1096, !1109, !1110, !1111, !1120, !1121, !1122, !1123, !1127, !1128, !1140, !1141, !1150, !1151, !1152, !1153, !1154, !1155, !1156, !1157, !1158, !1159, !1160, !1161, !1162, !1163, !1164, !1165, !1166, !1167, !1168, !1169, !1170, !1171, !1172, !1173, !1174, !1175, !1176, !1177, !1178, !1179, !1180}
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !1078, file: !121, line: 1313, baseType: !1081, size: 64, align: 64)
!1081 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !425, size: 64, align: 64)
!1082 = !DIDerivedType(tag: DW_TAG_member, name: "multi_owned_by_easy", scope: !1078, file: !121, line: 1318, baseType: !423, size: 8, align: 8, offset: 64)
!1083 = !DIDerivedType(tag: DW_TAG_member, name: "keeps_speed", scope: !1078, file: !121, line: 1321, baseType: !411, size: 128, align: 64, offset: 128)
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "lastconnect", scope: !1078, file: !121, line: 1323, baseType: !262, size: 64, align: 64, offset: 256)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "headerbuff", scope: !1078, file: !121, line: 1325, baseType: !479, size: 64, align: 64, offset: 320)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "headersize", scope: !1078, file: !121, line: 1326, baseType: !347, size: 64, align: 64, offset: 384)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1078, file: !121, line: 1328, baseType: !479, size: 64, align: 64, offset: 448)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuffer", scope: !1078, file: !121, line: 1329, baseType: !1089, size: 131080, align: 8, offset: 512)
!1089 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 131080, align: 8, elements: !1090)
!1090 = !{!1091}
!1091 = !DISubrange(count: 16385)
!1092 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1078, file: !121, line: 1330, baseType: !458, size: 64, align: 64, offset: 131648)
!1093 = !DIDerivedType(tag: DW_TAG_member, name: "this_is_a_follow", scope: !1078, file: !121, line: 1332, baseType: !423, size: 8, align: 8, offset: 131712)
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "first_host", scope: !1078, file: !121, line: 1334, baseType: !479, size: 64, align: 64, offset: 131776)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "first_remote_port", scope: !1078, file: !121, line: 1340, baseType: !316, size: 32, align: 32, offset: 131840)
!1096 = !DIDerivedType(tag: DW_TAG_member, name: "session", scope: !1078, file: !121, line: 1341, baseType: !1097, size: 64, align: 64, offset: 131904)
!1097 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1098, size: 64, align: 64)
!1098 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_ssl_session", file: !121, line: 397, size: 1088, align: 64, elements: !1099)
!1099 = !{!1100, !1101, !1102, !1103, !1104, !1105, !1106, !1107, !1108}
!1100 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1098, file: !121, line: 398, baseType: !479, size: 64, align: 64)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1098, file: !121, line: 399, baseType: !479, size: 64, align: 64, offset: 64)
!1102 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1098, file: !121, line: 400, baseType: !851, size: 64, align: 64, offset: 128)
!1103 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !1098, file: !121, line: 401, baseType: !311, size: 64, align: 64, offset: 192)
!1104 = !DIDerivedType(tag: DW_TAG_member, name: "idsize", scope: !1098, file: !121, line: 402, baseType: !347, size: 64, align: 64, offset: 256)
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !1098, file: !121, line: 403, baseType: !379, size: 64, align: 64, offset: 320)
!1106 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !1098, file: !121, line: 404, baseType: !316, size: 32, align: 32, offset: 384)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1098, file: !121, line: 405, baseType: !316, size: 32, align: 32, offset: 416)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !1098, file: !121, line: 406, baseType: !788, size: 640, align: 64, offset: 448)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !1078, file: !121, line: 1342, baseType: !379, size: 64, align: 64, offset: 131968)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "tempcount", scope: !1078, file: !121, line: 1343, baseType: !683, size: 32, align: 32, offset: 132032)
!1111 = !DIDerivedType(tag: DW_TAG_member, name: "tempwrite", scope: !1078, file: !121, line: 1344, baseType: !1112, size: 576, align: 64, offset: 132096)
!1112 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1113, size: 576, align: 64, elements: !1118)
!1113 = !DICompositeType(tag: DW_TAG_structure_type, name: "tempbuf", file: !121, line: 1302, size: 192, align: 64, elements: !1114)
!1114 = !{!1115, !1116, !1117}
!1115 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !1113, file: !121, line: 1303, baseType: !479, size: 64, align: 64)
!1116 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !1113, file: !121, line: 1305, baseType: !347, size: 64, align: 64, offset: 64)
!1117 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1113, file: !121, line: 1306, baseType: !316, size: 32, align: 32, offset: 128)
!1118 = !{!1119}
!1119 = !DISubrange(count: 3)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "scratch", scope: !1078, file: !121, line: 1345, baseType: !479, size: 64, align: 64, offset: 132672)
!1121 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuf", scope: !1078, file: !121, line: 1346, baseType: !423, size: 8, align: 8, offset: 132736)
!1122 = !DIDerivedType(tag: DW_TAG_member, name: "os_errno", scope: !1078, file: !121, line: 1349, baseType: !316, size: 32, align: 32, offset: 132768)
!1123 = !DIDerivedType(tag: DW_TAG_member, name: "prev_signal", scope: !1078, file: !121, line: 1352, baseType: !1124, size: 64, align: 64, offset: 132800)
!1124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1125, size: 64, align: 64)
!1125 = !DISubroutineType(types: !1126)
!1126 = !{null, !316}
!1127 = !DIDerivedType(tag: DW_TAG_member, name: "allow_port", scope: !1078, file: !121, line: 1354, baseType: !423, size: 8, align: 8, offset: 132864)
!1128 = !DIDerivedType(tag: DW_TAG_member, name: "digest", scope: !1078, file: !121, line: 1356, baseType: !1129, size: 512, align: 64, offset: 132928)
!1129 = !DICompositeType(tag: DW_TAG_structure_type, name: "digestdata", file: !121, line: 410, size: 512, align: 64, elements: !1130)
!1130 = !{!1131, !1132, !1133, !1134, !1135, !1136, !1137, !1138, !1139}
!1131 = !DIDerivedType(tag: DW_TAG_member, name: "nonce", scope: !1129, file: !121, line: 416, baseType: !479, size: 64, align: 64)
!1132 = !DIDerivedType(tag: DW_TAG_member, name: "cnonce", scope: !1129, file: !121, line: 417, baseType: !479, size: 64, align: 64, offset: 64)
!1133 = !DIDerivedType(tag: DW_TAG_member, name: "realm", scope: !1129, file: !121, line: 418, baseType: !479, size: 64, align: 64, offset: 128)
!1134 = !DIDerivedType(tag: DW_TAG_member, name: "algo", scope: !1129, file: !121, line: 419, baseType: !316, size: 32, align: 32, offset: 192)
!1135 = !DIDerivedType(tag: DW_TAG_member, name: "stale", scope: !1129, file: !121, line: 420, baseType: !423, size: 8, align: 8, offset: 224)
!1136 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !1129, file: !121, line: 421, baseType: !479, size: 64, align: 64, offset: 256)
!1137 = !DIDerivedType(tag: DW_TAG_member, name: "qop", scope: !1129, file: !121, line: 422, baseType: !479, size: 64, align: 64, offset: 320)
!1138 = !DIDerivedType(tag: DW_TAG_member, name: "algorithm", scope: !1129, file: !121, line: 423, baseType: !479, size: 64, align: 64, offset: 384)
!1139 = !DIDerivedType(tag: DW_TAG_member, name: "nc", scope: !1129, file: !121, line: 424, baseType: !316, size: 32, align: 32, offset: 448)
!1140 = !DIDerivedType(tag: DW_TAG_member, name: "proxydigest", scope: !1078, file: !121, line: 1357, baseType: !1129, size: 512, align: 64, offset: 133440)
!1141 = !DIDerivedType(tag: DW_TAG_member, name: "authhost", scope: !1078, file: !121, line: 1364, baseType: !1142, size: 256, align: 64, offset: 133952)
!1142 = !DICompositeType(tag: DW_TAG_structure_type, name: "auth", file: !121, line: 1278, size: 256, align: 64, elements: !1143)
!1143 = !{!1144, !1145, !1146, !1147, !1148, !1149}
!1144 = !DIDerivedType(tag: DW_TAG_member, name: "want", scope: !1142, file: !121, line: 1279, baseType: !349, size: 64, align: 64)
!1145 = !DIDerivedType(tag: DW_TAG_member, name: "picked", scope: !1142, file: !121, line: 1281, baseType: !349, size: 64, align: 64, offset: 64)
!1146 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !1142, file: !121, line: 1282, baseType: !349, size: 64, align: 64, offset: 128)
!1147 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1142, file: !121, line: 1284, baseType: !423, size: 8, align: 8, offset: 192)
!1148 = !DIDerivedType(tag: DW_TAG_member, name: "multipass", scope: !1142, file: !121, line: 1286, baseType: !423, size: 8, align: 8, offset: 200)
!1149 = !DIDerivedType(tag: DW_TAG_member, name: "iestyle", scope: !1142, file: !121, line: 1288, baseType: !423, size: 8, align: 8, offset: 208)
!1150 = !DIDerivedType(tag: DW_TAG_member, name: "authproxy", scope: !1078, file: !121, line: 1365, baseType: !1142, size: 256, align: 64, offset: 134208)
!1151 = !DIDerivedType(tag: DW_TAG_member, name: "authproblem", scope: !1078, file: !121, line: 1367, baseType: !423, size: 8, align: 8, offset: 134464)
!1152 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !1078, file: !121, line: 1369, baseType: !311, size: 64, align: 64, offset: 134528)
!1153 = !DIDerivedType(tag: DW_TAG_member, name: "expiretime", scope: !1078, file: !121, line: 1375, baseType: !411, size: 128, align: 64, offset: 134592)
!1154 = !DIDerivedType(tag: DW_TAG_member, name: "timenode", scope: !1078, file: !121, line: 1376, baseType: !403, size: 448, align: 64, offset: 134720)
!1155 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutlist", scope: !1078, file: !121, line: 1377, baseType: !330, size: 256, align: 64, offset: 135168)
!1156 = !DIDerivedType(tag: DW_TAG_member, name: "most_recent_ftp_entrypath", scope: !1078, file: !121, line: 1380, baseType: !479, size: 64, align: 64, offset: 135424)
!1157 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_trying_alternative", scope: !1078, file: !121, line: 1383, baseType: !423, size: 8, align: 8, offset: 135488)
!1158 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1078, file: !121, line: 1385, baseType: !316, size: 32, align: 32, offset: 135520)
!1159 = !DIDerivedType(tag: DW_TAG_member, name: "expect100header", scope: !1078, file: !121, line: 1387, baseType: !423, size: 8, align: 8, offset: 135552)
!1160 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_broke", scope: !1078, file: !121, line: 1389, baseType: !423, size: 8, align: 8, offset: 135560)
!1161 = !DIDerivedType(tag: DW_TAG_member, name: "prev_block_had_trailing_cr", scope: !1078, file: !121, line: 1397, baseType: !423, size: 8, align: 8, offset: 135568)
!1162 = !DIDerivedType(tag: DW_TAG_member, name: "crlf_conversions", scope: !1078, file: !121, line: 1399, baseType: !458, size: 64, align: 64, offset: 135616)
!1163 = !DIDerivedType(tag: DW_TAG_member, name: "pathbuffer", scope: !1078, file: !121, line: 1401, baseType: !479, size: 64, align: 64, offset: 135680)
!1164 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1078, file: !121, line: 1402, baseType: !479, size: 64, align: 64, offset: 135744)
!1165 = !DIDerivedType(tag: DW_TAG_member, name: "slash_removed", scope: !1078, file: !121, line: 1404, baseType: !423, size: 8, align: 8, offset: 135808)
!1166 = !DIDerivedType(tag: DW_TAG_member, name: "use_range", scope: !1078, file: !121, line: 1406, baseType: !423, size: 8, align: 8, offset: 135816)
!1167 = !DIDerivedType(tag: DW_TAG_member, name: "rangestringalloc", scope: !1078, file: !121, line: 1407, baseType: !423, size: 8, align: 8, offset: 135824)
!1168 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !1078, file: !121, line: 1409, baseType: !479, size: 64, align: 64, offset: 135872)
!1169 = !DIDerivedType(tag: DW_TAG_member, name: "resume_from", scope: !1078, file: !121, line: 1411, baseType: !458, size: 64, align: 64, offset: 135936)
!1170 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_client_CSeq", scope: !1078, file: !121, line: 1414, baseType: !379, size: 64, align: 64, offset: 136000)
!1171 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_server_CSeq", scope: !1078, file: !121, line: 1415, baseType: !379, size: 64, align: 64, offset: 136064)
!1172 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_CSeq_recv", scope: !1078, file: !121, line: 1416, baseType: !379, size: 64, align: 64, offset: 136128)
!1173 = !DIDerivedType(tag: DW_TAG_member, name: "infilesize", scope: !1078, file: !121, line: 1418, baseType: !458, size: 64, align: 64, offset: 136192)
!1174 = !DIDerivedType(tag: DW_TAG_member, name: "drain", scope: !1078, file: !121, line: 1421, baseType: !347, size: 64, align: 64, offset: 136256)
!1175 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1078, file: !121, line: 1424, baseType: !423, size: 8, align: 8, offset: 136320)
!1176 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1078, file: !121, line: 1428, baseType: !617, size: 64, align: 64, offset: 136384)
!1177 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1078, file: !121, line: 1429, baseType: !311, size: 64, align: 64, offset: 136448)
!1178 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !1078, file: !121, line: 1431, baseType: !256, size: 64, align: 64, offset: 136512)
!1179 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !1078, file: !121, line: 1432, baseType: !423, size: 8, align: 8, offset: 136576)
!1180 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !1078, file: !121, line: 1433, baseType: !316, size: 32, align: 32, offset: 136608)
!1181 = !DIDerivedType(tag: DW_TAG_member, name: "wildcard", scope: !257, file: !121, line: 1838, baseType: !1182, size: 640, align: 64, offset: 157504)
!1182 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !1183, line: 46, size: 640, align: 64, elements: !1184)
!1183 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1184 = !{!1185, !1197, !1198, !1199, !1200, !1201, !1203}
!1185 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1182, file: !1183, line: 47, baseType: !1186, size: 32, align: 32)
!1186 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !1183, line: 41, baseType: !1187)
!1187 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1183, line: 30, size: 32, align: 32, elements: !1188)
!1188 = !{!1189, !1190, !1191, !1192, !1193, !1194, !1195, !1196}
!1189 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!1190 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!1191 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!1192 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!1193 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!1194 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!1195 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!1196 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!1197 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1182, file: !1183, line: 48, baseType: !479, size: 64, align: 64, offset: 64)
!1198 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !1182, file: !1183, line: 49, baseType: !479, size: 64, align: 64, offset: 128)
!1199 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !1182, file: !1183, line: 50, baseType: !330, size: 256, align: 64, offset: 192)
!1200 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !1182, file: !1183, line: 51, baseType: !311, size: 64, align: 64, offset: 448)
!1201 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !1182, file: !1183, line: 52, baseType: !1202, size: 64, align: 64, offset: 512)
!1202 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !1183, line: 43, baseType: !362)
!1203 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !1182, file: !1183, line: 53, baseType: !311, size: 64, align: 64, offset: 576)
!1204 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !257, file: !121, line: 1839, baseType: !1205, size: 1856, align: 64, offset: 158144)
!1205 = !DICompositeType(tag: DW_TAG_structure_type, name: "PureInfo", file: !121, line: 1154, size: 1856, align: 64, elements: !1206)
!1206 = !{!1207, !1208, !1209, !1210, !1211, !1212, !1213, !1214, !1215, !1216, !1217, !1218, !1219, !1223, !1224, !1225, !1226, !1227, !1228}
!1207 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !1205, file: !121, line: 1155, baseType: !316, size: 32, align: 32)
!1208 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxycode", scope: !1205, file: !121, line: 1156, baseType: !316, size: 32, align: 32, offset: 32)
!1209 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1205, file: !121, line: 1157, baseType: !316, size: 32, align: 32, offset: 64)
!1210 = !DIDerivedType(tag: DW_TAG_member, name: "filetime", scope: !1205, file: !121, line: 1158, baseType: !379, size: 64, align: 64, offset: 128)
!1211 = !DIDerivedType(tag: DW_TAG_member, name: "timecond", scope: !1205, file: !121, line: 1162, baseType: !423, size: 8, align: 8, offset: 192)
!1212 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !1205, file: !121, line: 1164, baseType: !379, size: 64, align: 64, offset: 256)
!1213 = !DIDerivedType(tag: DW_TAG_member, name: "request_size", scope: !1205, file: !121, line: 1165, baseType: !379, size: 64, align: 64, offset: 320)
!1214 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauthavail", scope: !1205, file: !121, line: 1166, baseType: !349, size: 64, align: 64, offset: 384)
!1215 = !DIDerivedType(tag: DW_TAG_member, name: "httpauthavail", scope: !1205, file: !121, line: 1167, baseType: !349, size: 64, align: 64, offset: 448)
!1216 = !DIDerivedType(tag: DW_TAG_member, name: "numconnects", scope: !1205, file: !121, line: 1168, baseType: !379, size: 64, align: 64, offset: 512)
!1217 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !1205, file: !121, line: 1169, baseType: !479, size: 64, align: 64, offset: 576)
!1218 = !DIDerivedType(tag: DW_TAG_member, name: "wouldredirect", scope: !1205, file: !121, line: 1170, baseType: !479, size: 64, align: 64, offset: 640)
!1219 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_ip", scope: !1205, file: !121, line: 1180, baseType: !1220, size: 368, align: 8, offset: 704)
!1220 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 368, align: 8, elements: !1221)
!1221 = !{!1222}
!1222 = !DISubrange(count: 46)
!1223 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_port", scope: !1205, file: !121, line: 1181, baseType: !379, size: 64, align: 64, offset: 1088)
!1224 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_ip", scope: !1205, file: !121, line: 1183, baseType: !1220, size: 368, align: 8, offset: 1152)
!1225 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_port", scope: !1205, file: !121, line: 1184, baseType: !379, size: 64, align: 64, offset: 1536)
!1226 = !DIDerivedType(tag: DW_TAG_member, name: "conn_scheme", scope: !1205, file: !121, line: 1186, baseType: !851, size: 64, align: 64, offset: 1600)
!1227 = !DIDerivedType(tag: DW_TAG_member, name: "conn_protocol", scope: !1205, file: !121, line: 1187, baseType: !683, size: 32, align: 32, offset: 1664)
!1228 = !DIDerivedType(tag: DW_TAG_member, name: "certs", scope: !1205, file: !121, line: 1189, baseType: !1229, size: 128, align: 64, offset: 1728)
!1229 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !4, line: 2214, size: 128, align: 64, elements: !1230)
!1230 = !{!1231, !1232}
!1231 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1229, file: !4, line: 2215, baseType: !316, size: 32, align: 32)
!1232 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1229, file: !4, line: 2216, baseType: !1233, size: 64, align: 64, offset: 64)
!1233 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !725, size: 64, align: 64)
!1234 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !257, file: !121, line: 1840, baseType: !1235, size: 128, align: 64, offset: 160000)
!1235 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !4, line: 2245, size: 128, align: 64, elements: !1236)
!1236 = !{!1237, !1253}
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1235, file: !4, line: 2246, baseType: !1238, size: 32, align: 32)
!1238 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !4, line: 2235, baseType: !1239)
!1239 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2222, size: 32, align: 32, elements: !1240)
!1240 = !{!1241, !1242, !1243, !1244, !1245, !1246, !1247, !1248, !1249, !1250, !1251, !1252}
!1241 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!1242 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!1243 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!1244 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!1245 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!1246 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!1247 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!1248 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!1249 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!1250 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!1251 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!1252 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1235, file: !4, line: 2247, baseType: !311, size: 64, align: 64, offset: 64)
!1254 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !257, file: !121, line: 1847, baseType: !683, size: 32, align: 32, offset: 160128)
!1255 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !253, file: !121, line: 904, baseType: !1256, size: 384, align: 64, offset: 64)
!1256 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !101, line: 82, size: 384, align: 64, elements: !1257)
!1257 = !{!1258, !1262, !1263, !1265, !1266}
!1258 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1256, file: !101, line: 83, baseType: !1259, size: 136, align: 8)
!1259 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 136, align: 8, elements: !1260)
!1260 = !{!1261}
!1261 = !DISubrange(count: 17)
!1262 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1256, file: !101, line: 84, baseType: !316, size: 32, align: 32, offset: 160)
!1263 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1256, file: !101, line: 85, baseType: !1264, size: 32, align: 32, offset: 192)
!1264 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !101, line: 66, baseType: !100)
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1256, file: !101, line: 86, baseType: !458, size: 64, align: 64, offset: 256)
!1266 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1256, file: !101, line: 87, baseType: !347, size: 64, align: 64, offset: 320)
!1267 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !253, file: !121, line: 906, baseType: !697, size: 64, align: 64, offset: 448)
!1268 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !253, file: !121, line: 907, baseType: !311, size: 64, align: 64, offset: 512)
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !253, file: !121, line: 909, baseType: !423, size: 8, align: 8, offset: 576)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "connection_id", scope: !253, file: !121, line: 915, baseType: !379, size: 64, align: 64, offset: 640)
!1271 = !DIDerivedType(tag: DW_TAG_member, name: "dns_entry", scope: !253, file: !121, line: 922, baseType: !1272, size: 64, align: 64, offset: 704)
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
!1282 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !1280, file: !1279, line: 52, baseType: !316, size: 32, align: 32)
!1283 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !1280, file: !1279, line: 53, baseType: !316, size: 32, align: 32, offset: 32)
!1284 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !1280, file: !1279, line: 54, baseType: !316, size: 32, align: 32, offset: 64)
!1285 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !1280, file: !1279, line: 55, baseType: !316, size: 32, align: 32, offset: 96)
!1286 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !1280, file: !1279, line: 56, baseType: !1287, size: 32, align: 32, offset: 128)
!1287 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !459, line: 186, baseType: !1288)
!1288 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !686, line: 33, baseType: !1289)
!1289 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !416, line: 189, baseType: !683)
!1290 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !1280, file: !1279, line: 57, baseType: !479, size: 64, align: 64, offset: 192)
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !1280, file: !1279, line: 58, baseType: !1292, size: 64, align: 64, offset: 256)
!1292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !685, size: 64, align: 64)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !1280, file: !1279, line: 59, baseType: !1294, size: 64, align: 64, offset: 320)
!1294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1280, size: 64, align: 64)
!1295 = !DIDerivedType(tag: DW_TAG_member, name: "timestamp", scope: !1273, file: !1274, line: 69, baseType: !506, size: 64, align: 64, offset: 64)
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !1273, file: !1274, line: 71, baseType: !379, size: 64, align: 64, offset: 128)
!1297 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr", scope: !253, file: !121, line: 927, baseType: !1277, size: 64, align: 64, offset: 768)
!1298 = !DIDerivedType(tag: DW_TAG_member, name: "tempaddr", scope: !253, file: !121, line: 928, baseType: !1299, size: 128, align: 64, offset: 832)
!1299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1277, size: 128, align: 64, elements: !1300)
!1300 = !{!1301}
!1301 = !DISubrange(count: 2)
!1302 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr_str", scope: !253, file: !121, line: 933, baseType: !1220, size: 368, align: 8, offset: 960)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !253, file: !121, line: 935, baseType: !683, size: 32, align: 32, offset: 1344)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !253, file: !121, line: 937, baseType: !316, size: 32, align: 32, offset: 1376)
!1305 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !253, file: !121, line: 939, baseType: !1306, size: 256, align: 64, offset: 1408)
!1306 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostname", file: !121, line: 581, size: 256, align: 64, elements: !1307)
!1307 = !{!1308, !1309, !1310, !1311}
!1308 = !DIDerivedType(tag: DW_TAG_member, name: "rawalloc", scope: !1306, file: !121, line: 582, baseType: !479, size: 64, align: 64)
!1309 = !DIDerivedType(tag: DW_TAG_member, name: "encalloc", scope: !1306, file: !121, line: 583, baseType: !479, size: 64, align: 64, offset: 64)
!1310 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1306, file: !121, line: 584, baseType: !479, size: 64, align: 64, offset: 128)
!1311 = !DIDerivedType(tag: DW_TAG_member, name: "dispname", scope: !1306, file: !121, line: 585, baseType: !851, size: 64, align: 64, offset: 192)
!1312 = !DIDerivedType(tag: DW_TAG_member, name: "secondaryhostname", scope: !253, file: !121, line: 940, baseType: !479, size: 64, align: 64, offset: 1664)
!1313 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !253, file: !121, line: 941, baseType: !1306, size: 256, align: 64, offset: 1728)
!1314 = !DIDerivedType(tag: DW_TAG_member, name: "socks_proxy", scope: !253, file: !121, line: 944, baseType: !1315, size: 512, align: 64, offset: 1984)
!1315 = !DICompositeType(tag: DW_TAG_structure_type, name: "proxy_info", file: !121, line: 883, size: 512, align: 64, elements: !1316)
!1316 = !{!1317, !1318, !1319, !1320, !1321}
!1317 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1315, file: !121, line: 884, baseType: !1306, size: 256, align: 64)
!1318 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !1315, file: !121, line: 885, baseType: !379, size: 64, align: 64, offset: 256)
!1319 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !1315, file: !121, line: 886, baseType: !826, size: 32, align: 32, offset: 320)
!1320 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1315, file: !121, line: 887, baseType: !479, size: 64, align: 64, offset: 384)
!1321 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !1315, file: !121, line: 888, baseType: !479, size: 64, align: 64, offset: 448)
!1322 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !253, file: !121, line: 945, baseType: !1315, size: 512, align: 64, offset: 2496)
!1323 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !253, file: !121, line: 947, baseType: !379, size: 64, align: 64, offset: 3008)
!1324 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !253, file: !121, line: 948, baseType: !316, size: 32, align: 32, offset: 3072)
!1325 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !253, file: !121, line: 949, baseType: !316, size: 32, align: 32, offset: 3104)
!1326 = !DIDerivedType(tag: DW_TAG_member, name: "secondary_port", scope: !253, file: !121, line: 951, baseType: !564, size: 16, align: 16, offset: 3136)
!1327 = !DIDerivedType(tag: DW_TAG_member, name: "primary_ip", scope: !253, file: !121, line: 961, baseType: !1220, size: 368, align: 8, offset: 3152)
!1328 = !DIDerivedType(tag: DW_TAG_member, name: "primary_port", scope: !253, file: !121, line: 962, baseType: !379, size: 64, align: 64, offset: 3520)
!1329 = !DIDerivedType(tag: DW_TAG_member, name: "local_ip", scope: !253, file: !121, line: 968, baseType: !1220, size: 368, align: 8, offset: 3584)
!1330 = !DIDerivedType(tag: DW_TAG_member, name: "local_port", scope: !253, file: !121, line: 969, baseType: !379, size: 64, align: 64, offset: 3968)
!1331 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !253, file: !121, line: 971, baseType: !479, size: 64, align: 64, offset: 4032)
!1332 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !253, file: !121, line: 972, baseType: !479, size: 64, align: 64, offset: 4096)
!1333 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !253, file: !121, line: 973, baseType: !479, size: 64, align: 64, offset: 4160)
!1334 = !DIDerivedType(tag: DW_TAG_member, name: "oauth_bearer", scope: !253, file: !121, line: 975, baseType: !479, size: 64, align: 64, offset: 4224)
!1335 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !253, file: !121, line: 977, baseType: !316, size: 32, align: 32, offset: 4288)
!1336 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !253, file: !121, line: 978, baseType: !316, size: 32, align: 32, offset: 4320)
!1337 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !253, file: !121, line: 980, baseType: !411, size: 128, align: 64, offset: 4352)
!1338 = !DIDerivedType(tag: DW_TAG_member, name: "created", scope: !253, file: !121, line: 981, baseType: !411, size: 128, align: 64, offset: 4480)
!1339 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !253, file: !121, line: 982, baseType: !1340, size: 64, align: 32, offset: 4608)
!1340 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 64, align: 32, elements: !1300)
!1341 = !DIDerivedType(tag: DW_TAG_member, name: "tempsock", scope: !253, file: !121, line: 984, baseType: !1340, size: 64, align: 32, offset: 4672)
!1342 = !DIDerivedType(tag: DW_TAG_member, name: "sock_accepted", scope: !253, file: !121, line: 985, baseType: !1343, size: 16, align: 8, offset: 4736)
!1343 = !DICompositeType(tag: DW_TAG_array_type, baseType: !423, size: 16, align: 8, elements: !1300)
!1344 = !DIDerivedType(tag: DW_TAG_member, name: "recv", scope: !253, file: !121, line: 987, baseType: !1345, size: 128, align: 64, offset: 4800)
!1345 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1346, size: 128, align: 64, elements: !1300)
!1346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1347, size: 64, align: 64)
!1347 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_recv", file: !121, line: 863, baseType: !1348)
!1348 = !DISubroutineType(types: !1349)
!1349 = !{!519, !262, !316, !479, !347, !1350}
!1350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !289, size: 64, align: 64)
!1351 = !DIDerivedType(tag: DW_TAG_member, name: "send", scope: !253, file: !121, line: 988, baseType: !1352, size: 128, align: 64, offset: 4928)
!1352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1353, size: 128, align: 64, elements: !1300)
!1353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1354, size: 64, align: 64)
!1354 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_send", file: !121, line: 856, baseType: !1355)
!1355 = !DISubroutineType(types: !1356)
!1356 = !{!519, !262, !316, !970, !347, !1350}
!1357 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !253, file: !121, line: 993, baseType: !1358, size: 192, align: 32, offset: 5056)
!1358 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1359, size: 192, align: 32, elements: !1300)
!1359 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_connect_data", file: !121, line: 274, size: 96, align: 32, elements: !1360)
!1360 = !{!1361, !1362, !1364}
!1361 = !DIDerivedType(tag: DW_TAG_member, name: "use", scope: !1359, file: !121, line: 278, baseType: !423, size: 8, align: 8)
!1362 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1359, file: !121, line: 279, baseType: !1363, size: 32, align: 32, offset: 32)
!1363 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connection_state", file: !121, line: 271, baseType: !120)
!1364 = !DIDerivedType(tag: DW_TAG_member, name: "connecting_state", scope: !1359, file: !121, line: 280, baseType: !1365, size: 32, align: 32, offset: 64)
!1365 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connect_state", file: !121, line: 265, baseType: !126)
!1366 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !253, file: !121, line: 994, baseType: !1358, size: 192, align: 32, offset: 5248)
!1367 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !253, file: !121, line: 995, baseType: !788, size: 640, align: 64, offset: 5440)
!1368 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_config", scope: !253, file: !121, line: 996, baseType: !788, size: 640, align: 64, offset: 6080)
!1369 = !DIDerivedType(tag: DW_TAG_member, name: "tls_upgraded", scope: !253, file: !121, line: 997, baseType: !423, size: 8, align: 8, offset: 6720)
!1370 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !253, file: !121, line: 999, baseType: !1371, size: 280, align: 8, offset: 6728)
!1371 = !DICompositeType(tag: DW_TAG_structure_type, name: "ConnectBits", file: !121, line: 514, size: 280, align: 8, elements: !1372)
!1372 = !{!1373, !1374, !1375, !1376, !1377, !1378, !1379, !1380, !1381, !1382, !1383, !1384, !1385, !1386, !1387, !1388, !1389, !1390, !1391, !1392, !1393, !1394, !1395, !1396, !1397, !1398, !1399, !1400, !1401, !1402, !1403, !1404, !1405}
!1373 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !1371, file: !121, line: 516, baseType: !423, size: 8, align: 8)
!1374 = !DIDerivedType(tag: DW_TAG_member, name: "reuse", scope: !1371, file: !121, line: 517, baseType: !423, size: 8, align: 8, offset: 8)
!1375 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1371, file: !121, line: 518, baseType: !423, size: 8, align: 8, offset: 16)
!1376 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1371, file: !121, line: 520, baseType: !423, size: 8, align: 8, offset: 24)
!1377 = !DIDerivedType(tag: DW_TAG_member, name: "proxy", scope: !1371, file: !121, line: 522, baseType: !423, size: 8, align: 8, offset: 32)
!1378 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxy", scope: !1371, file: !121, line: 523, baseType: !423, size: 8, align: 8, offset: 40)
!1379 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy", scope: !1371, file: !121, line: 524, baseType: !423, size: 8, align: 8, offset: 48)
!1380 = !DIDerivedType(tag: DW_TAG_member, name: "user_passwd", scope: !1371, file: !121, line: 525, baseType: !423, size: 8, align: 8, offset: 56)
!1381 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user_passwd", scope: !1371, file: !121, line: 526, baseType: !423, size: 8, align: 8, offset: 64)
!1382 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6_ip", scope: !1371, file: !121, line: 527, baseType: !423, size: 8, align: 8, offset: 72)
!1383 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6", scope: !1371, file: !121, line: 529, baseType: !423, size: 8, align: 8, offset: 80)
!1384 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1371, file: !121, line: 531, baseType: !423, size: 8, align: 8, offset: 88)
!1385 = !DIDerivedType(tag: DW_TAG_member, name: "tcpconnect", scope: !1371, file: !121, line: 533, baseType: !1343, size: 16, align: 8, offset: 96)
!1386 = !DIDerivedType(tag: DW_TAG_member, name: "protoconnstart", scope: !1371, file: !121, line: 535, baseType: !423, size: 8, align: 8, offset: 112)
!1387 = !DIDerivedType(tag: DW_TAG_member, name: "retry", scope: !1371, file: !121, line: 538, baseType: !423, size: 8, align: 8, offset: 120)
!1388 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_proxy", scope: !1371, file: !121, line: 540, baseType: !423, size: 8, align: 8, offset: 128)
!1389 = !DIDerivedType(tag: DW_TAG_member, name: "authneg", scope: !1371, file: !121, line: 544, baseType: !423, size: 8, align: 8, offset: 136)
!1390 = !DIDerivedType(tag: DW_TAG_member, name: "rewindaftersend", scope: !1371, file: !121, line: 548, baseType: !423, size: 8, align: 8, offset: 144)
!1391 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !1371, file: !121, line: 552, baseType: !423, size: 8, align: 8, offset: 152)
!1392 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !1371, file: !121, line: 556, baseType: !423, size: 8, align: 8, offset: 160)
!1393 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_data_ssl", scope: !1371, file: !121, line: 559, baseType: !423, size: 8, align: 8, offset: 168)
!1394 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !1371, file: !121, line: 560, baseType: !423, size: 8, align: 8, offset: 176)
!1395 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd_in_url", scope: !1371, file: !121, line: 561, baseType: !423, size: 8, align: 8, offset: 184)
!1396 = !DIDerivedType(tag: DW_TAG_member, name: "stream_was_rewound", scope: !1371, file: !121, line: 562, baseType: !423, size: 8, align: 8, offset: 192)
!1397 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_connect_closed", scope: !1371, file: !121, line: 565, baseType: !423, size: 8, align: 8, offset: 200)
!1398 = !DIDerivedType(tag: DW_TAG_member, name: "bound", scope: !1371, file: !121, line: 568, baseType: !423, size: 8, align: 8, offset: 208)
!1399 = !DIDerivedType(tag: DW_TAG_member, name: "type_set", scope: !1371, file: !121, line: 570, baseType: !423, size: 8, align: 8, offset: 216)
!1400 = !DIDerivedType(tag: DW_TAG_member, name: "multiplex", scope: !1371, file: !121, line: 571, baseType: !423, size: 8, align: 8, offset: 224)
!1401 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !1371, file: !121, line: 573, baseType: !423, size: 8, align: 8, offset: 232)
!1402 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_npn", scope: !1371, file: !121, line: 574, baseType: !423, size: 8, align: 8, offset: 240)
!1403 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_alpn", scope: !1371, file: !121, line: 575, baseType: !423, size: 8, align: 8, offset: 248)
!1404 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_connected", scope: !1371, file: !121, line: 576, baseType: !1343, size: 16, align: 8, offset: 256)
!1405 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy_connecting", scope: !1371, file: !121, line: 578, baseType: !423, size: 8, align: 8, offset: 272)
!1406 = !DIDerivedType(tag: DW_TAG_member, name: "connecttime", scope: !253, file: !121, line: 1004, baseType: !411, size: 128, align: 64, offset: 7040)
!1407 = !DIDerivedType(tag: DW_TAG_member, name: "num_addr", scope: !253, file: !121, line: 1006, baseType: !316, size: 32, align: 32, offset: 7168)
!1408 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutms_per_addr", scope: !253, file: !121, line: 1007, baseType: !506, size: 64, align: 64, offset: 7232)
!1409 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !253, file: !121, line: 1010, baseType: !1410, size: 64, align: 64, offset: 7296)
!1410 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1411, size: 64, align: 64)
!1411 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1412)
!1412 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_handler", file: !121, line: 763, size: 1024, align: 64, elements: !1413)
!1413 = !{!1414, !1415, !1419, !1424, !1429, !1435, !1436, !1437, !1438, !1443, !1444, !1445, !1451, !1455, !1460, !1461, !1462}
!1414 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1412, file: !121, line: 764, baseType: !851, size: 64, align: 64)
!1415 = !DIDerivedType(tag: DW_TAG_member, name: "setup_connection", scope: !1412, file: !121, line: 767, baseType: !1416, size: 64, align: 64, offset: 64)
!1416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1417, size: 64, align: 64)
!1417 = !DISubroutineType(types: !1418)
!1418 = !{!289, !262}
!1419 = !DIDerivedType(tag: DW_TAG_member, name: "do_it", scope: !1412, file: !121, line: 770, baseType: !1420, size: 64, align: 64, offset: 128)
!1420 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1421, size: 64, align: 64)
!1421 = !DISubroutineType(types: !1422)
!1422 = !{!289, !262, !1423}
!1423 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !423, size: 64, align: 64)
!1424 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1412, file: !121, line: 771, baseType: !1425, size: 64, align: 64, offset: 192)
!1425 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_done_func", file: !121, line: 634, baseType: !1426)
!1426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1427, size: 64, align: 64)
!1427 = !DISubroutineType(types: !1428)
!1428 = !{!289, !262, !289, !423}
!1429 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1412, file: !121, line: 777, baseType: !1430, size: 64, align: 64, offset: 256)
!1430 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_do_more_func", file: !121, line: 633, baseType: !1431)
!1431 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1432, size: 64, align: 64)
!1432 = !DISubroutineType(types: !1433)
!1433 = !{!289, !262, !1434}
!1434 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !316, size: 64, align: 64)
!1435 = !DIDerivedType(tag: DW_TAG_member, name: "connect_it", scope: !1412, file: !121, line: 785, baseType: !1420, size: 64, align: 64, offset: 320)
!1436 = !DIDerivedType(tag: DW_TAG_member, name: "connecting", scope: !1412, file: !121, line: 788, baseType: !1420, size: 64, align: 64, offset: 384)
!1437 = !DIDerivedType(tag: DW_TAG_member, name: "doing", scope: !1412, file: !121, line: 789, baseType: !1420, size: 64, align: 64, offset: 448)
!1438 = !DIDerivedType(tag: DW_TAG_member, name: "proto_getsock", scope: !1412, file: !121, line: 793, baseType: !1439, size: 64, align: 64, offset: 512)
!1439 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1440, size: 64, align: 64)
!1440 = !DISubroutineType(types: !1441)
!1441 = !{!316, !262, !1442, !316}
!1442 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!1443 = !DIDerivedType(tag: DW_TAG_member, name: "doing_getsock", scope: !1412, file: !121, line: 799, baseType: !1439, size: 64, align: 64, offset: 576)
!1444 = !DIDerivedType(tag: DW_TAG_member, name: "domore_getsock", scope: !1412, file: !121, line: 805, baseType: !1439, size: 64, align: 64, offset: 640)
!1445 = !DIDerivedType(tag: DW_TAG_member, name: "perform_getsock", scope: !1412, file: !121, line: 812, baseType: !1446, size: 64, align: 64, offset: 704)
!1446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1447, size: 64, align: 64)
!1447 = !DISubroutineType(types: !1448)
!1448 = !{!316, !1449, !1442, !316}
!1449 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1450, size: 64, align: 64)
!1450 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !253)
!1451 = !DIDerivedType(tag: DW_TAG_member, name: "disconnect", scope: !1412, file: !121, line: 821, baseType: !1452, size: 64, align: 64, offset: 768)
!1452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1453, size: 64, align: 64)
!1453 = !DISubroutineType(types: !1454)
!1454 = !{!289, !262, !423}
!1455 = !DIDerivedType(tag: DW_TAG_member, name: "readwrite", scope: !1412, file: !121, line: 825, baseType: !1456, size: 64, align: 64, offset: 832)
!1456 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1457, size: 64, align: 64)
!1457 = !DISubroutineType(types: !1458)
!1458 = !{!289, !256, !262, !1459, !1423}
!1459 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !519, size: 64, align: 64)
!1460 = !DIDerivedType(tag: DW_TAG_member, name: "defport", scope: !1412, file: !121, line: 828, baseType: !379, size: 64, align: 64, offset: 896)
!1461 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1412, file: !121, line: 829, baseType: !683, size: 32, align: 32, offset: 960)
!1462 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1412, file: !121, line: 831, baseType: !683, size: 32, align: 32, offset: 992)
!1463 = !DIDerivedType(tag: DW_TAG_member, name: "given", scope: !253, file: !121, line: 1011, baseType: !1410, size: 64, align: 64, offset: 7360)
!1464 = !DIDerivedType(tag: DW_TAG_member, name: "ip_version", scope: !253, file: !121, line: 1013, baseType: !379, size: 64, align: 64, offset: 7424)
!1465 = !DIDerivedType(tag: DW_TAG_member, name: "sockfd", scope: !253, file: !121, line: 1017, baseType: !315, size: 32, align: 32, offset: 7488)
!1466 = !DIDerivedType(tag: DW_TAG_member, name: "writesockfd", scope: !253, file: !121, line: 1018, baseType: !315, size: 32, align: 32, offset: 7520)
!1467 = !DIDerivedType(tag: DW_TAG_member, name: "allocptr", scope: !253, file: !121, line: 1035, baseType: !1468, size: 640, align: 64, offset: 7552)
!1468 = !DICompositeType(tag: DW_TAG_structure_type, name: "dynamically_allocated_data", file: !121, line: 1024, size: 640, align: 64, elements: !1469)
!1469 = !{!1470, !1471, !1472, !1473, !1474, !1475, !1476, !1477, !1478, !1479}
!1470 = !DIDerivedType(tag: DW_TAG_member, name: "proxyuserpwd", scope: !1468, file: !121, line: 1025, baseType: !479, size: 64, align: 64)
!1471 = !DIDerivedType(tag: DW_TAG_member, name: "uagent", scope: !1468, file: !121, line: 1026, baseType: !479, size: 64, align: 64, offset: 64)
!1472 = !DIDerivedType(tag: DW_TAG_member, name: "accept_encoding", scope: !1468, file: !121, line: 1027, baseType: !479, size: 64, align: 64, offset: 128)
!1473 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd", scope: !1468, file: !121, line: 1028, baseType: !479, size: 64, align: 64, offset: 192)
!1474 = !DIDerivedType(tag: DW_TAG_member, name: "rangeline", scope: !1468, file: !121, line: 1029, baseType: !479, size: 64, align: 64, offset: 256)
!1475 = !DIDerivedType(tag: DW_TAG_member, name: "ref", scope: !1468, file: !121, line: 1030, baseType: !479, size: 64, align: 64, offset: 320)
!1476 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1468, file: !121, line: 1031, baseType: !479, size: 64, align: 64, offset: 384)
!1477 = !DIDerivedType(tag: DW_TAG_member, name: "cookiehost", scope: !1468, file: !121, line: 1032, baseType: !479, size: 64, align: 64, offset: 448)
!1478 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_transport", scope: !1468, file: !121, line: 1033, baseType: !479, size: 64, align: 64, offset: 512)
!1479 = !DIDerivedType(tag: DW_TAG_member, name: "te", scope: !1468, file: !121, line: 1034, baseType: !479, size: 64, align: 64, offset: 576)
!1480 = !DIDerivedType(tag: DW_TAG_member, name: "readchannel_inuse", scope: !253, file: !121, line: 1057, baseType: !423, size: 8, align: 8, offset: 8192)
!1481 = !DIDerivedType(tag: DW_TAG_member, name: "writechannel_inuse", scope: !253, file: !121, line: 1059, baseType: !423, size: 8, align: 8, offset: 8200)
!1482 = !DIDerivedType(tag: DW_TAG_member, name: "send_pipe", scope: !253, file: !121, line: 1061, baseType: !330, size: 256, align: 64, offset: 8256)
!1483 = !DIDerivedType(tag: DW_TAG_member, name: "recv_pipe", scope: !253, file: !121, line: 1063, baseType: !330, size: 256, align: 64, offset: 8512)
!1484 = !DIDerivedType(tag: DW_TAG_member, name: "master_buffer", scope: !253, file: !121, line: 1065, baseType: !479, size: 64, align: 64, offset: 8768)
!1485 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !253, file: !121, line: 1067, baseType: !347, size: 64, align: 64, offset: 8832)
!1486 = !DIDerivedType(tag: DW_TAG_member, name: "buf_len", scope: !253, file: !121, line: 1068, baseType: !347, size: 64, align: 64, offset: 8896)
!1487 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !253, file: !121, line: 1071, baseType: !602, size: 64, align: 64, offset: 8960)
!1488 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !253, file: !121, line: 1072, baseType: !311, size: 64, align: 64, offset: 9024)
!1489 = !DIDerivedType(tag: DW_TAG_member, name: "syserr_buf", scope: !253, file: !121, line: 1091, baseType: !1490, size: 2048, align: 8, offset: 9088)
!1490 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 2048, align: 8, elements: !1491)
!1491 = !{!1492}
!1492 = !DISubrange(count: 256)
!1493 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !253, file: !121, line: 1099, baseType: !479, size: 64, align: 64, offset: 11136)
!1494 = !DIDerivedType(tag: DW_TAG_member, name: "trlMax", scope: !253, file: !121, line: 1100, baseType: !316, size: 32, align: 32, offset: 11200)
!1495 = !DIDerivedType(tag: DW_TAG_member, name: "trlPos", scope: !253, file: !121, line: 1101, baseType: !316, size: 32, align: 32, offset: 11232)
!1496 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !253, file: !121, line: 1114, baseType: !1497, size: 1792, align: 64, offset: 11264)
!1497 = !DICompositeType(tag: DW_TAG_union_type, scope: !253, file: !121, line: 1103, size: 1792, align: 64, elements: !1498)
!1498 = !{!1499, !1546, !1551, !1556, !1559, !1607, !1621, !1633, !1640, !1658}
!1499 = !DIDerivedType(tag: DW_TAG_member, name: "ftpc", scope: !1497, file: !121, line: 1104, baseType: !1500, size: 1792, align: 64)
!1500 = !DICompositeType(tag: DW_TAG_structure_type, name: "ftp_conn", file: !135, line: 118, size: 1792, align: 64, elements: !1501)
!1501 = !{!1502, !1522, !1523, !1525, !1526, !1527, !1528, !1529, !1530, !1531, !1532, !1533, !1534, !1535, !1536, !1537, !1538, !1540, !1541, !1542, !1543, !1544, !1545}
!1502 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1500, file: !135, line: 119, baseType: !1503, size: 896, align: 64)
!1503 = !DICompositeType(tag: DW_TAG_structure_type, name: "pingpong", file: !1504, line: 48, size: 896, align: 64, elements: !1505)
!1504 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1505 = !{!1506, !1507, !1508, !1509, !1510, !1511, !1512, !1513, !1514, !1515, !1516, !1517, !1518}
!1506 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !1503, file: !1504, line: 49, baseType: !479, size: 64, align: 64)
!1507 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !1503, file: !1504, line: 50, baseType: !347, size: 64, align: 64, offset: 64)
!1508 = !DIDerivedType(tag: DW_TAG_member, name: "nread_resp", scope: !1503, file: !1504, line: 51, baseType: !347, size: 64, align: 64, offset: 128)
!1509 = !DIDerivedType(tag: DW_TAG_member, name: "linestart_resp", scope: !1503, file: !1504, line: 52, baseType: !479, size: 64, align: 64, offset: 192)
!1510 = !DIDerivedType(tag: DW_TAG_member, name: "pending_resp", scope: !1503, file: !1504, line: 54, baseType: !423, size: 8, align: 8, offset: 256)
!1511 = !DIDerivedType(tag: DW_TAG_member, name: "sendthis", scope: !1503, file: !1504, line: 57, baseType: !479, size: 64, align: 64, offset: 320)
!1512 = !DIDerivedType(tag: DW_TAG_member, name: "sendleft", scope: !1503, file: !1504, line: 59, baseType: !347, size: 64, align: 64, offset: 384)
!1513 = !DIDerivedType(tag: DW_TAG_member, name: "sendsize", scope: !1503, file: !1504, line: 60, baseType: !347, size: 64, align: 64, offset: 448)
!1514 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !1503, file: !1504, line: 61, baseType: !411, size: 128, align: 64, offset: 512)
!1515 = !DIDerivedType(tag: DW_TAG_member, name: "response_time", scope: !1503, file: !1504, line: 63, baseType: !379, size: 64, align: 64, offset: 640)
!1516 = !DIDerivedType(tag: DW_TAG_member, name: "conn", scope: !1503, file: !1504, line: 66, baseType: !262, size: 64, align: 64, offset: 704)
!1517 = !DIDerivedType(tag: DW_TAG_member, name: "statemach_act", scope: !1503, file: !1504, line: 72, baseType: !1416, size: 64, align: 64, offset: 768)
!1518 = !DIDerivedType(tag: DW_TAG_member, name: "endofresp", scope: !1503, file: !1504, line: 74, baseType: !1519, size: 64, align: 64, offset: 832)
!1519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1520, size: 64, align: 64)
!1520 = !DISubroutineType(types: !1521)
!1521 = !{!423, !262, !479, !347, !1434}
!1522 = !DIDerivedType(tag: DW_TAG_member, name: "entrypath", scope: !1500, file: !135, line: 120, baseType: !479, size: 64, align: 64, offset: 896)
!1523 = !DIDerivedType(tag: DW_TAG_member, name: "dirs", scope: !1500, file: !135, line: 121, baseType: !1524, size: 64, align: 64, offset: 960)
!1524 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !479, size: 64, align: 64)
!1525 = !DIDerivedType(tag: DW_TAG_member, name: "dirdepth", scope: !1500, file: !135, line: 122, baseType: !316, size: 32, align: 32, offset: 1024)
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "diralloc", scope: !1500, file: !135, line: 123, baseType: !316, size: 32, align: 32, offset: 1056)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !1500, file: !135, line: 124, baseType: !479, size: 64, align: 64, offset: 1088)
!1528 = !DIDerivedType(tag: DW_TAG_member, name: "dont_check", scope: !1500, file: !135, line: 125, baseType: !423, size: 8, align: 8, offset: 1152)
!1529 = !DIDerivedType(tag: DW_TAG_member, name: "ctl_valid", scope: !1500, file: !135, line: 128, baseType: !423, size: 8, align: 8, offset: 1160)
!1530 = !DIDerivedType(tag: DW_TAG_member, name: "cwddone", scope: !1500, file: !135, line: 131, baseType: !423, size: 8, align: 8, offset: 1168)
!1531 = !DIDerivedType(tag: DW_TAG_member, name: "cwdfail", scope: !1500, file: !135, line: 133, baseType: !423, size: 8, align: 8, offset: 1176)
!1532 = !DIDerivedType(tag: DW_TAG_member, name: "wait_data_conn", scope: !1500, file: !135, line: 135, baseType: !423, size: 8, align: 8, offset: 1184)
!1533 = !DIDerivedType(tag: DW_TAG_member, name: "prevpath", scope: !1500, file: !135, line: 136, baseType: !479, size: 64, align: 64, offset: 1216)
!1534 = !DIDerivedType(tag: DW_TAG_member, name: "transfertype", scope: !1500, file: !135, line: 137, baseType: !480, size: 8, align: 8, offset: 1280)
!1535 = !DIDerivedType(tag: DW_TAG_member, name: "count1", scope: !1500, file: !135, line: 139, baseType: !316, size: 32, align: 32, offset: 1312)
!1536 = !DIDerivedType(tag: DW_TAG_member, name: "count2", scope: !1500, file: !135, line: 140, baseType: !316, size: 32, align: 32, offset: 1344)
!1537 = !DIDerivedType(tag: DW_TAG_member, name: "count3", scope: !1500, file: !135, line: 141, baseType: !316, size: 32, align: 32, offset: 1376)
!1538 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1500, file: !135, line: 142, baseType: !1539, size: 32, align: 32, offset: 1408)
!1539 = !DIDerivedType(tag: DW_TAG_typedef, name: "ftpstate", file: !135, line: 80, baseType: !134)
!1540 = !DIDerivedType(tag: DW_TAG_member, name: "state_saved", scope: !1500, file: !135, line: 143, baseType: !1539, size: 32, align: 32, offset: 1440)
!1541 = !DIDerivedType(tag: DW_TAG_member, name: "retr_size_saved", scope: !1500, file: !135, line: 145, baseType: !458, size: 64, align: 64, offset: 1472)
!1542 = !DIDerivedType(tag: DW_TAG_member, name: "server_os", scope: !1500, file: !135, line: 146, baseType: !479, size: 64, align: 64, offset: 1536)
!1543 = !DIDerivedType(tag: DW_TAG_member, name: "known_filesize", scope: !1500, file: !135, line: 147, baseType: !458, size: 64, align: 64, offset: 1600)
!1544 = !DIDerivedType(tag: DW_TAG_member, name: "newhost", scope: !1500, file: !135, line: 152, baseType: !479, size: 64, align: 64, offset: 1664)
!1545 = !DIDerivedType(tag: DW_TAG_member, name: "newport", scope: !1500, file: !135, line: 153, baseType: !564, size: 16, align: 16, offset: 1728)
!1546 = !DIDerivedType(tag: DW_TAG_member, name: "httpc", scope: !1497, file: !121, line: 1105, baseType: !1547, size: 32, align: 32)
!1547 = !DICompositeType(tag: DW_TAG_structure_type, name: "http_conn", file: !1548, line: 200, size: 32, align: 32, elements: !1549)
!1548 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1549 = !{!1550}
!1550 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !1547, file: !1548, line: 227, baseType: !316, size: 32, align: 32)
!1551 = !DIDerivedType(tag: DW_TAG_member, name: "sshc", scope: !1497, file: !121, line: 1106, baseType: !1552, size: 64, align: 64)
!1552 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssh_conn", file: !1553, line: 110, size: 64, align: 64, elements: !1554)
!1553 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ssh.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1554 = !{!1555}
!1555 = !DIDerivedType(tag: DW_TAG_member, name: "authlist", scope: !1552, file: !1553, line: 111, baseType: !851, size: 64, align: 64)
!1556 = !DIDerivedType(tag: DW_TAG_member, name: "tftpc", scope: !1497, file: !121, line: 1107, baseType: !1557, size: 64, align: 64)
!1557 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1558, size: 64, align: 64)
!1558 = !DICompositeType(tag: DW_TAG_structure_type, name: "tftp_state_data", file: !121, line: 1107, flags: DIFlagFwdDecl)
!1559 = !DIDerivedType(tag: DW_TAG_member, name: "imapc", scope: !1497, file: !121, line: 1108, baseType: !1560, size: 1472, align: 64)
!1560 = !DICompositeType(tag: DW_TAG_structure_type, name: "imap_conn", file: !174, line: 70, size: 1472, align: 64, elements: !1561)
!1561 = !{!1562, !1563, !1565, !1566, !1598, !1599, !1600, !1602, !1603, !1604, !1605, !1606}
!1562 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1560, file: !174, line: 71, baseType: !1503, size: 896, align: 64)
!1563 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1560, file: !174, line: 72, baseType: !1564, size: 32, align: 32, offset: 896)
!1564 = !DIDerivedType(tag: DW_TAG_typedef, name: "imapstate", file: !174, line: 50, baseType: !173)
!1565 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1560, file: !174, line: 73, baseType: !423, size: 8, align: 8, offset: 928)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1560, file: !174, line: 74, baseType: !1567, size: 256, align: 64, offset: 960)
!1567 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASL", file: !193, line: 101, size: 256, align: 64, elements: !1568)
!1568 = !{!1569, !1590, !1592, !1593, !1594, !1595, !1596, !1597}
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "params", scope: !1567, file: !193, line: 102, baseType: !1570, size: 64, align: 64)
!1570 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1571, size: 64, align: 64)
!1571 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1572)
!1572 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASLproto", file: !193, line: 86, size: 384, align: 64, elements: !1573)
!1573 = !{!1574, !1575, !1576, !1577, !1578, !1582, !1586}
!1574 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !1572, file: !193, line: 87, baseType: !851, size: 64, align: 64)
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "contcode", scope: !1572, file: !193, line: 88, baseType: !316, size: 32, align: 32, offset: 64)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "finalcode", scope: !1572, file: !193, line: 89, baseType: !316, size: 32, align: 32, offset: 96)
!1577 = !DIDerivedType(tag: DW_TAG_member, name: "maxirlen", scope: !1572, file: !193, line: 90, baseType: !347, size: 64, align: 64, offset: 128)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "sendauth", scope: !1572, file: !193, line: 91, baseType: !1579, size: 64, align: 64, offset: 192)
!1579 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1580, size: 64, align: 64)
!1580 = !DISubroutineType(types: !1581)
!1581 = !{!289, !262, !851, !851}
!1582 = !DIDerivedType(tag: DW_TAG_member, name: "sendcont", scope: !1572, file: !193, line: 94, baseType: !1583, size: 64, align: 64, offset: 256)
!1583 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1584, size: 64, align: 64)
!1584 = !DISubroutineType(types: !1585)
!1585 = !{!289, !262, !851}
!1586 = !DIDerivedType(tag: DW_TAG_member, name: "getmessage", scope: !1572, file: !193, line: 96, baseType: !1587, size: 64, align: 64, offset: 320)
!1587 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1588, size: 64, align: 64)
!1588 = !DISubroutineType(types: !1589)
!1589 = !{null, !479, !1524}
!1590 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1567, file: !193, line: 103, baseType: !1591, size: 32, align: 32, offset: 64)
!1591 = !DIDerivedType(tag: DW_TAG_typedef, name: "saslstate", file: !193, line: 76, baseType: !192)
!1592 = !DIDerivedType(tag: DW_TAG_member, name: "authmechs", scope: !1567, file: !193, line: 104, baseType: !683, size: 32, align: 32, offset: 96)
!1593 = !DIDerivedType(tag: DW_TAG_member, name: "prefmech", scope: !1567, file: !193, line: 105, baseType: !683, size: 32, align: 32, offset: 128)
!1594 = !DIDerivedType(tag: DW_TAG_member, name: "authused", scope: !1567, file: !193, line: 106, baseType: !683, size: 32, align: 32, offset: 160)
!1595 = !DIDerivedType(tag: DW_TAG_member, name: "resetprefs", scope: !1567, file: !193, line: 107, baseType: !423, size: 8, align: 8, offset: 192)
!1596 = !DIDerivedType(tag: DW_TAG_member, name: "mutual_auth", scope: !1567, file: !193, line: 108, baseType: !423, size: 8, align: 8, offset: 200)
!1597 = !DIDerivedType(tag: DW_TAG_member, name: "force_ir", scope: !1567, file: !193, line: 109, baseType: !423, size: 8, align: 8, offset: 208)
!1598 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1560, file: !174, line: 75, baseType: !683, size: 32, align: 32, offset: 1216)
!1599 = !DIDerivedType(tag: DW_TAG_member, name: "cmdid", scope: !1560, file: !174, line: 76, baseType: !316, size: 32, align: 32, offset: 1248)
!1600 = !DIDerivedType(tag: DW_TAG_member, name: "resptag", scope: !1560, file: !174, line: 77, baseType: !1601, size: 40, align: 8, offset: 1280)
!1601 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 40, align: 8, elements: !317)
!1602 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1560, file: !174, line: 78, baseType: !423, size: 8, align: 8, offset: 1320)
!1603 = !DIDerivedType(tag: DW_TAG_member, name: "login_disabled", scope: !1560, file: !174, line: 79, baseType: !423, size: 8, align: 8, offset: 1328)
!1604 = !DIDerivedType(tag: DW_TAG_member, name: "ir_supported", scope: !1560, file: !174, line: 80, baseType: !423, size: 8, align: 8, offset: 1336)
!1605 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox", scope: !1560, file: !174, line: 81, baseType: !479, size: 64, align: 64, offset: 1344)
!1606 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox_uidvalidity", scope: !1560, file: !174, line: 82, baseType: !479, size: 64, align: 64, offset: 1408)
!1607 = !DIDerivedType(tag: DW_TAG_member, name: "pop3c", scope: !1497, file: !121, line: 1109, baseType: !1608, size: 1536, align: 64)
!1608 = !DICompositeType(tag: DW_TAG_structure_type, name: "pop3_conn", file: !213, line: 60, size: 1536, align: 64, elements: !1609)
!1609 = !{!1610, !1611, !1613, !1614, !1615, !1616, !1617, !1618, !1619, !1620}
!1610 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1608, file: !213, line: 61, baseType: !1503, size: 896, align: 64)
!1611 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1608, file: !213, line: 62, baseType: !1612, size: 32, align: 32, offset: 896)
!1612 = !DIDerivedType(tag: DW_TAG_typedef, name: "pop3state", file: !213, line: 46, baseType: !212)
!1613 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1608, file: !213, line: 63, baseType: !423, size: 8, align: 8, offset: 928)
!1614 = !DIDerivedType(tag: DW_TAG_member, name: "eob", scope: !1608, file: !213, line: 64, baseType: !347, size: 64, align: 64, offset: 960)
!1615 = !DIDerivedType(tag: DW_TAG_member, name: "strip", scope: !1608, file: !213, line: 66, baseType: !347, size: 64, align: 64, offset: 1024)
!1616 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1608, file: !213, line: 68, baseType: !1567, size: 256, align: 64, offset: 1088)
!1617 = !DIDerivedType(tag: DW_TAG_member, name: "authtypes", scope: !1608, file: !213, line: 69, baseType: !683, size: 32, align: 32, offset: 1344)
!1618 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1608, file: !213, line: 70, baseType: !683, size: 32, align: 32, offset: 1376)
!1619 = !DIDerivedType(tag: DW_TAG_member, name: "apoptimestamp", scope: !1608, file: !213, line: 71, baseType: !479, size: 64, align: 64, offset: 1408)
!1620 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1608, file: !213, line: 72, baseType: !423, size: 8, align: 8, offset: 1472)
!1621 = !DIDerivedType(tag: DW_TAG_member, name: "smtpc", scope: !1497, file: !121, line: 1110, baseType: !1622, size: 1344, align: 64)
!1622 = !DICompositeType(tag: DW_TAG_structure_type, name: "smtp_conn", file: !228, line: 65, size: 1344, align: 64, elements: !1623)
!1623 = !{!1624, !1625, !1627, !1628, !1629, !1630, !1631, !1632}
!1624 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1622, file: !228, line: 66, baseType: !1503, size: 896, align: 64)
!1625 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1622, file: !228, line: 67, baseType: !1626, size: 32, align: 32, offset: 896)
!1626 = !DIDerivedType(tag: DW_TAG_typedef, name: "smtpstate", file: !228, line: 48, baseType: !227)
!1627 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1622, file: !228, line: 68, baseType: !423, size: 8, align: 8, offset: 928)
!1628 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1622, file: !228, line: 69, baseType: !479, size: 64, align: 64, offset: 960)
!1629 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1622, file: !228, line: 70, baseType: !1567, size: 256, align: 64, offset: 1024)
!1630 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1622, file: !228, line: 71, baseType: !423, size: 8, align: 8, offset: 1280)
!1631 = !DIDerivedType(tag: DW_TAG_member, name: "size_supported", scope: !1622, file: !228, line: 72, baseType: !423, size: 8, align: 8, offset: 1288)
!1632 = !DIDerivedType(tag: DW_TAG_member, name: "auth_supported", scope: !1622, file: !228, line: 74, baseType: !423, size: 8, align: 8, offset: 1296)
!1633 = !DIDerivedType(tag: DW_TAG_member, name: "rtspc", scope: !1497, file: !121, line: 1111, baseType: !1634, size: 192, align: 64)
!1634 = !DICompositeType(tag: DW_TAG_structure_type, name: "rtsp_conn", file: !1635, line: 43, size: 192, align: 64, elements: !1636)
!1635 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/rtsp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1636 = !{!1637, !1638, !1639}
!1637 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_buf", scope: !1634, file: !1635, line: 44, baseType: !479, size: 64, align: 64)
!1638 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_bufsize", scope: !1634, file: !1635, line: 45, baseType: !519, size: 64, align: 64, offset: 64)
!1639 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_channel", scope: !1634, file: !1635, line: 46, baseType: !316, size: 32, align: 32, offset: 128)
!1640 = !DIDerivedType(tag: DW_TAG_member, name: "smbc", scope: !1497, file: !121, line: 1112, baseType: !1641, size: 640, align: 64)
!1641 = !DICompositeType(tag: DW_TAG_structure_type, name: "smb_conn", file: !245, line: 33, size: 640, align: 64, elements: !1642)
!1642 = !{!1643, !1644, !1645, !1646, !1651, !1652, !1653, !1654, !1655, !1656, !1657}
!1643 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1641, file: !245, line: 34, baseType: !244, size: 32, align: 32)
!1644 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1641, file: !245, line: 35, baseType: !479, size: 64, align: 64, offset: 64)
!1645 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1641, file: !245, line: 36, baseType: !479, size: 64, align: 64, offset: 128)
!1646 = !DIDerivedType(tag: DW_TAG_member, name: "challenge", scope: !1641, file: !245, line: 37, baseType: !1647, size: 64, align: 8, offset: 192)
!1647 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1648, size: 64, align: 8, elements: !1649)
!1648 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!1649 = !{!1650}
!1650 = !DISubrange(count: 8)
!1651 = !DIDerivedType(tag: DW_TAG_member, name: "session_key", scope: !1641, file: !245, line: 38, baseType: !683, size: 32, align: 32, offset: 256)
!1652 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1641, file: !245, line: 39, baseType: !564, size: 16, align: 16, offset: 288)
!1653 = !DIDerivedType(tag: DW_TAG_member, name: "recv_buf", scope: !1641, file: !245, line: 40, baseType: !479, size: 64, align: 64, offset: 320)
!1654 = !DIDerivedType(tag: DW_TAG_member, name: "upload_size", scope: !1641, file: !245, line: 41, baseType: !347, size: 64, align: 64, offset: 384)
!1655 = !DIDerivedType(tag: DW_TAG_member, name: "send_size", scope: !1641, file: !245, line: 42, baseType: !347, size: 64, align: 64, offset: 448)
!1656 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1641, file: !245, line: 43, baseType: !347, size: 64, align: 64, offset: 512)
!1657 = !DIDerivedType(tag: DW_TAG_member, name: "got", scope: !1641, file: !245, line: 44, baseType: !347, size: 64, align: 64, offset: 576)
!1658 = !DIDerivedType(tag: DW_TAG_member, name: "generic", scope: !1497, file: !121, line: 1113, baseType: !311, size: 64, align: 64)
!1659 = !DIDerivedType(tag: DW_TAG_member, name: "cselect_bits", scope: !253, file: !121, line: 1116, baseType: !316, size: 32, align: 32, offset: 13056)
!1660 = !DIDerivedType(tag: DW_TAG_member, name: "waitfor", scope: !253, file: !121, line: 1117, baseType: !316, size: 32, align: 32, offset: 13088)
!1661 = !DIDerivedType(tag: DW_TAG_member, name: "localdev", scope: !253, file: !121, line: 1128, baseType: !479, size: 64, align: 64, offset: 13120)
!1662 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !253, file: !121, line: 1129, baseType: !564, size: 16, align: 16, offset: 13184)
!1663 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !253, file: !121, line: 1130, baseType: !316, size: 32, align: 32, offset: 13216)
!1664 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_state", scope: !253, file: !121, line: 1137, baseType: !1665, size: 64, align: 32, offset: 13248)
!1665 = !DICompositeType(tag: DW_TAG_array_type, baseType: !252, size: 64, align: 32, elements: !1300)
!1666 = !DIDerivedType(tag: DW_TAG_member, name: "bundle", scope: !253, file: !121, line: 1138, baseType: !1667, size: 64, align: 64, offset: 13312)
!1667 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1668, size: 64, align: 64)
!1668 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectbundle", file: !426, line: 38, size: 384, align: 64, elements: !1669)
!1669 = !{!1670, !1671, !1672}
!1670 = !DIDerivedType(tag: DW_TAG_member, name: "multiuse", scope: !1668, file: !426, line: 39, baseType: !316, size: 32, align: 32)
!1671 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !1668, file: !426, line: 40, baseType: !347, size: 64, align: 64, offset: 64)
!1672 = !DIDerivedType(tag: DW_TAG_member, name: "conn_list", scope: !1668, file: !426, line: 41, baseType: !330, size: 256, align: 64, offset: 128)
!1673 = !DIDerivedType(tag: DW_TAG_member, name: "negnpn", scope: !253, file: !121, line: 1140, baseType: !316, size: 32, align: 32, offset: 13376)
!1674 = !{!1675, !1676, !1677}
!1675 = !DIEnumerator(name: "TUNNEL_INIT", value: 0)
!1676 = !DIEnumerator(name: "TUNNEL_CONNECT", value: 1)
!1677 = !DIEnumerator(name: "TUNNEL_COMPLETE", value: 2)
!1678 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2258, size: 32, align: 32, elements: !1679)
!1679 = !{!1680, !1681, !1682, !1683, !1684, !1685, !1686, !1687, !1688, !1689, !1690, !1691, !1692, !1693, !1694, !1695, !1696, !1697, !1698, !1699, !1700, !1701, !1702, !1703, !1704, !1705, !1706, !1707, !1708, !1709, !1710, !1711, !1712, !1713, !1714, !1715, !1716, !1717, !1718, !1719, !1720, !1721, !1722, !1723, !1724, !1725, !1726, !1727, !1728, !1729, !1730}
!1680 = !DIEnumerator(name: "CURLINFO_NONE", value: 0)
!1681 = !DIEnumerator(name: "CURLINFO_EFFECTIVE_URL", value: 1048577)
!1682 = !DIEnumerator(name: "CURLINFO_RESPONSE_CODE", value: 2097154)
!1683 = !DIEnumerator(name: "CURLINFO_TOTAL_TIME", value: 3145731)
!1684 = !DIEnumerator(name: "CURLINFO_NAMELOOKUP_TIME", value: 3145732)
!1685 = !DIEnumerator(name: "CURLINFO_CONNECT_TIME", value: 3145733)
!1686 = !DIEnumerator(name: "CURLINFO_PRETRANSFER_TIME", value: 3145734)
!1687 = !DIEnumerator(name: "CURLINFO_SIZE_UPLOAD", value: 3145735)
!1688 = !DIEnumerator(name: "CURLINFO_SIZE_DOWNLOAD", value: 3145736)
!1689 = !DIEnumerator(name: "CURLINFO_SPEED_DOWNLOAD", value: 3145737)
!1690 = !DIEnumerator(name: "CURLINFO_SPEED_UPLOAD", value: 3145738)
!1691 = !DIEnumerator(name: "CURLINFO_HEADER_SIZE", value: 2097163)
!1692 = !DIEnumerator(name: "CURLINFO_REQUEST_SIZE", value: 2097164)
!1693 = !DIEnumerator(name: "CURLINFO_SSL_VERIFYRESULT", value: 2097165)
!1694 = !DIEnumerator(name: "CURLINFO_FILETIME", value: 2097166)
!1695 = !DIEnumerator(name: "CURLINFO_CONTENT_LENGTH_DOWNLOAD", value: 3145743)
!1696 = !DIEnumerator(name: "CURLINFO_CONTENT_LENGTH_UPLOAD", value: 3145744)
!1697 = !DIEnumerator(name: "CURLINFO_STARTTRANSFER_TIME", value: 3145745)
!1698 = !DIEnumerator(name: "CURLINFO_CONTENT_TYPE", value: 1048594)
!1699 = !DIEnumerator(name: "CURLINFO_REDIRECT_TIME", value: 3145747)
!1700 = !DIEnumerator(name: "CURLINFO_REDIRECT_COUNT", value: 2097172)
!1701 = !DIEnumerator(name: "CURLINFO_PRIVATE", value: 1048597)
!1702 = !DIEnumerator(name: "CURLINFO_HTTP_CONNECTCODE", value: 2097174)
!1703 = !DIEnumerator(name: "CURLINFO_HTTPAUTH_AVAIL", value: 2097175)
!1704 = !DIEnumerator(name: "CURLINFO_PROXYAUTH_AVAIL", value: 2097176)
!1705 = !DIEnumerator(name: "CURLINFO_OS_ERRNO", value: 2097177)
!1706 = !DIEnumerator(name: "CURLINFO_NUM_CONNECTS", value: 2097178)
!1707 = !DIEnumerator(name: "CURLINFO_SSL_ENGINES", value: 4194331)
!1708 = !DIEnumerator(name: "CURLINFO_COOKIELIST", value: 4194332)
!1709 = !DIEnumerator(name: "CURLINFO_LASTSOCKET", value: 2097181)
!1710 = !DIEnumerator(name: "CURLINFO_FTP_ENTRY_PATH", value: 1048606)
!1711 = !DIEnumerator(name: "CURLINFO_REDIRECT_URL", value: 1048607)
!1712 = !DIEnumerator(name: "CURLINFO_PRIMARY_IP", value: 1048608)
!1713 = !DIEnumerator(name: "CURLINFO_APPCONNECT_TIME", value: 3145761)
!1714 = !DIEnumerator(name: "CURLINFO_CERTINFO", value: 4194338)
!1715 = !DIEnumerator(name: "CURLINFO_CONDITION_UNMET", value: 2097187)
!1716 = !DIEnumerator(name: "CURLINFO_RTSP_SESSION_ID", value: 1048612)
!1717 = !DIEnumerator(name: "CURLINFO_RTSP_CLIENT_CSEQ", value: 2097189)
!1718 = !DIEnumerator(name: "CURLINFO_RTSP_SERVER_CSEQ", value: 2097190)
!1719 = !DIEnumerator(name: "CURLINFO_RTSP_CSEQ_RECV", value: 2097191)
!1720 = !DIEnumerator(name: "CURLINFO_PRIMARY_PORT", value: 2097192)
!1721 = !DIEnumerator(name: "CURLINFO_LOCAL_IP", value: 1048617)
!1722 = !DIEnumerator(name: "CURLINFO_LOCAL_PORT", value: 2097194)
!1723 = !DIEnumerator(name: "CURLINFO_TLS_SESSION", value: 4194347)
!1724 = !DIEnumerator(name: "CURLINFO_ACTIVESOCKET", value: 5242924)
!1725 = !DIEnumerator(name: "CURLINFO_TLS_SSL_PTR", value: 4194349)
!1726 = !DIEnumerator(name: "CURLINFO_HTTP_VERSION", value: 2097198)
!1727 = !DIEnumerator(name: "CURLINFO_PROXY_SSL_VERIFYRESULT", value: 2097199)
!1728 = !DIEnumerator(name: "CURLINFO_PROTOCOL", value: 2097200)
!1729 = !DIEnumerator(name: "CURLINFO_SCHEME", value: 1048625)
!1730 = !DIEnumerator(name: "CURLINFO_LASTONE", value: 49)
!1731 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "dupstring", file: !121, line: 1466, size: 32, align: 32, elements: !1732)
!1732 = !{!1733, !1734, !1735, !1736, !1737, !1738, !1739, !1740, !1741, !1742, !1743, !1744, !1745, !1746, !1747, !1748, !1749, !1750, !1751, !1752, !1753, !1754, !1755, !1756, !1757, !1758, !1759, !1760, !1761, !1762, !1763, !1764, !1765, !1766, !1767, !1768, !1769, !1770, !1771, !1772, !1773, !1774, !1775, !1776, !1777, !1778, !1779, !1780, !1781, !1782, !1783, !1784, !1785, !1786, !1787, !1788, !1789}
!1733 = !DIEnumerator(name: "STRING_CERT_ORIG", value: 0)
!1734 = !DIEnumerator(name: "STRING_CERT_PROXY", value: 1)
!1735 = !DIEnumerator(name: "STRING_CERT_TYPE_ORIG", value: 2)
!1736 = !DIEnumerator(name: "STRING_CERT_TYPE_PROXY", value: 3)
!1737 = !DIEnumerator(name: "STRING_COOKIE", value: 4)
!1738 = !DIEnumerator(name: "STRING_COOKIEJAR", value: 5)
!1739 = !DIEnumerator(name: "STRING_CUSTOMREQUEST", value: 6)
!1740 = !DIEnumerator(name: "STRING_DEFAULT_PROTOCOL", value: 7)
!1741 = !DIEnumerator(name: "STRING_DEVICE", value: 8)
!1742 = !DIEnumerator(name: "STRING_ENCODING", value: 9)
!1743 = !DIEnumerator(name: "STRING_FTP_ACCOUNT", value: 10)
!1744 = !DIEnumerator(name: "STRING_FTP_ALTERNATIVE_TO_USER", value: 11)
!1745 = !DIEnumerator(name: "STRING_FTPPORT", value: 12)
!1746 = !DIEnumerator(name: "STRING_KEY_ORIG", value: 13)
!1747 = !DIEnumerator(name: "STRING_KEY_PROXY", value: 14)
!1748 = !DIEnumerator(name: "STRING_KEY_PASSWD_ORIG", value: 15)
!1749 = !DIEnumerator(name: "STRING_KEY_PASSWD_PROXY", value: 16)
!1750 = !DIEnumerator(name: "STRING_KEY_TYPE_ORIG", value: 17)
!1751 = !DIEnumerator(name: "STRING_KEY_TYPE_PROXY", value: 18)
!1752 = !DIEnumerator(name: "STRING_KRB_LEVEL", value: 19)
!1753 = !DIEnumerator(name: "STRING_NETRC_FILE", value: 20)
!1754 = !DIEnumerator(name: "STRING_PROXY", value: 21)
!1755 = !DIEnumerator(name: "STRING_PRE_PROXY", value: 22)
!1756 = !DIEnumerator(name: "STRING_SET_RANGE", value: 23)
!1757 = !DIEnumerator(name: "STRING_SET_REFERER", value: 24)
!1758 = !DIEnumerator(name: "STRING_SET_URL", value: 25)
!1759 = !DIEnumerator(name: "STRING_SSL_CAPATH_ORIG", value: 26)
!1760 = !DIEnumerator(name: "STRING_SSL_CAPATH_PROXY", value: 27)
!1761 = !DIEnumerator(name: "STRING_SSL_CAFILE_ORIG", value: 28)
!1762 = !DIEnumerator(name: "STRING_SSL_CAFILE_PROXY", value: 29)
!1763 = !DIEnumerator(name: "STRING_SSL_PINNEDPUBLICKEY_ORIG", value: 30)
!1764 = !DIEnumerator(name: "STRING_SSL_PINNEDPUBLICKEY_PROXY", value: 31)
!1765 = !DIEnumerator(name: "STRING_SSL_CIPHER_LIST_ORIG", value: 32)
!1766 = !DIEnumerator(name: "STRING_SSL_CIPHER_LIST_PROXY", value: 33)
!1767 = !DIEnumerator(name: "STRING_SSL_EGDSOCKET", value: 34)
!1768 = !DIEnumerator(name: "STRING_SSL_RANDOM_FILE", value: 35)
!1769 = !DIEnumerator(name: "STRING_USERAGENT", value: 36)
!1770 = !DIEnumerator(name: "STRING_SSL_CRLFILE_ORIG", value: 37)
!1771 = !DIEnumerator(name: "STRING_SSL_CRLFILE_PROXY", value: 38)
!1772 = !DIEnumerator(name: "STRING_SSL_ISSUERCERT_ORIG", value: 39)
!1773 = !DIEnumerator(name: "STRING_SSL_ISSUERCERT_PROXY", value: 40)
!1774 = !DIEnumerator(name: "STRING_USERNAME", value: 41)
!1775 = !DIEnumerator(name: "STRING_PASSWORD", value: 42)
!1776 = !DIEnumerator(name: "STRING_OPTIONS", value: 43)
!1777 = !DIEnumerator(name: "STRING_PROXYUSERNAME", value: 44)
!1778 = !DIEnumerator(name: "STRING_PROXYPASSWORD", value: 45)
!1779 = !DIEnumerator(name: "STRING_NOPROXY", value: 46)
!1780 = !DIEnumerator(name: "STRING_RTSP_SESSION_ID", value: 47)
!1781 = !DIEnumerator(name: "STRING_RTSP_STREAM_URI", value: 48)
!1782 = !DIEnumerator(name: "STRING_RTSP_TRANSPORT", value: 49)
!1783 = !DIEnumerator(name: "STRING_SERVICE_NAME", value: 50)
!1784 = !DIEnumerator(name: "STRING_MAIL_FROM", value: 51)
!1785 = !DIEnumerator(name: "STRING_MAIL_AUTH", value: 52)
!1786 = !DIEnumerator(name: "STRING_BEARER", value: 53)
!1787 = !DIEnumerator(name: "STRING_LASTZEROTERMINATED", value: 54)
!1788 = !DIEnumerator(name: "STRING_COPYPOSTFIELDS", value: 55)
!1789 = !DIEnumerator(name: "STRING_LAST", value: 56)
!1790 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1828, size: 32, align: 32, elements: !1791)
!1791 = !{!1792, !1793, !1794, !1795, !1796, !1797, !1798}
!1792 = !DIEnumerator(name: "CURL_HTTP_VERSION_NONE", value: 0)
!1793 = !DIEnumerator(name: "CURL_HTTP_VERSION_1_0", value: 1)
!1794 = !DIEnumerator(name: "CURL_HTTP_VERSION_1_1", value: 2)
!1795 = !DIEnumerator(name: "CURL_HTTP_VERSION_2_0", value: 3)
!1796 = !DIEnumerator(name: "CURL_HTTP_VERSION_2TLS", value: 4)
!1797 = !DIEnumerator(name: "CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE", value: 5)
!1798 = !DIEnumerator(name: "CURL_HTTP_VERSION_LAST", value: 6)
!1799 = !{!316, !479, !379, !625, !1800, !311}
!1800 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1801, size: 64, align: 64)
!1801 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1235, size: 64, align: 64)
!1802 = !{!1803, !1807, !1811, !1815, !1819, !1823, !1826}
!1803 = distinct !DISubprogram(name: "Curl_initinfo", scope: !1, file: !1, line: 45, type: !1804, isLocal: false, isDefinition: true, scopeLine: 46, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1804 = !DISubroutineType(types: !1805)
!1805 = !{!289, !256}
!1806 = !{}
!1807 = distinct !DISubprogram(name: "Curl_getinfo", scope: !1, file: !1, line: 392, type: !1808, isLocal: false, isDefinition: true, scopeLine: 393, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1808 = !DISubroutineType(types: !1809)
!1809 = !{!289, !256, !1810, null}
!1810 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLINFO", file: !4, line: 2312, baseType: !1678)
!1811 = distinct !DISubprogram(name: "getinfo_char", scope: !1, file: !1, line: 91, type: !1812, isLocal: true, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1812 = !DISubroutineType(types: !1813)
!1813 = !{!289, !256, !1810, !1814}
!1814 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !851, size: 64, align: 64)
!1815 = distinct !DISubprogram(name: "getinfo_long", scope: !1, file: !1, line: 140, type: !1816, isLocal: true, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1816 = !DISubroutineType(types: !1817)
!1817 = !{!289, !256, !1810, !1818}
!1818 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !379, size: 64, align: 64)
!1819 = distinct !DISubprogram(name: "getinfo_double", scope: !1, file: !1, line: 249, type: !1820, isLocal: true, isDefinition: true, scopeLine: 251, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1820 = !DISubroutineType(types: !1821)
!1821 = !{!289, !256, !1810, !1822}
!1822 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !625, size: 64, align: 64)
!1823 = distinct !DISubprogram(name: "getinfo_slist", scope: !1, file: !1, line: 302, type: !1824, isLocal: true, isDefinition: true, scopeLine: 304, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1824 = !DISubroutineType(types: !1825)
!1825 = !{!289, !256, !1810, !1233}
!1826 = distinct !DISubprogram(name: "getinfo_socket", scope: !1, file: !1, line: 378, type: !1827, isLocal: true, isDefinition: true, scopeLine: 380, flags: DIFlagPrototyped, isOptimized: false, variables: !1806)
!1827 = !DISubroutineType(types: !1828)
!1828 = !{!289, !256, !1810, !1442}
!1829 = !{i32 2, !"Dwarf Version", i32 4}
!1830 = !{i32 2, !"Debug Info Version", i32 3}
!1831 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1832 = !DILocalVariable(name: "data", arg: 1, scope: !1803, file: !1, line: 45, type: !256)
!1833 = !DIExpression()
!1834 = !DILocation(line: 45, column: 42, scope: !1803)
!1835 = !DILocalVariable(name: "pro", scope: !1803, file: !1, line: 47, type: !1836)
!1836 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1042, size: 64, align: 64)
!1837 = !DILocation(line: 47, column: 20, scope: !1803)
!1838 = !DILocation(line: 47, column: 27, scope: !1803)
!1839 = !DILocation(line: 47, column: 33, scope: !1803)
!1840 = !DILocalVariable(name: "info", scope: !1803, file: !1, line: 48, type: !1841)
!1841 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1205, size: 64, align: 64)
!1842 = !DILocation(line: 48, column: 20, scope: !1803)
!1843 = !DILocation(line: 48, column: 28, scope: !1803)
!1844 = !DILocation(line: 48, column: 34, scope: !1803)
!1845 = !DILocation(line: 50, column: 3, scope: !1803)
!1846 = !DILocation(line: 50, column: 8, scope: !1803)
!1847 = !DILocation(line: 50, column: 19, scope: !1803)
!1848 = !DILocation(line: 51, column: 3, scope: !1803)
!1849 = !DILocation(line: 51, column: 8, scope: !1803)
!1850 = !DILocation(line: 51, column: 18, scope: !1803)
!1851 = !DILocation(line: 52, column: 3, scope: !1803)
!1852 = !DILocation(line: 52, column: 8, scope: !1803)
!1853 = !DILocation(line: 52, column: 21, scope: !1803)
!1854 = !DILocation(line: 53, column: 3, scope: !1803)
!1855 = !DILocation(line: 53, column: 8, scope: !1803)
!1856 = !DILocation(line: 53, column: 22, scope: !1803)
!1857 = !DILocation(line: 54, column: 3, scope: !1803)
!1858 = !DILocation(line: 54, column: 8, scope: !1803)
!1859 = !DILocation(line: 54, column: 24, scope: !1803)
!1860 = !DILocation(line: 55, column: 3, scope: !1803)
!1861 = !DILocation(line: 55, column: 8, scope: !1803)
!1862 = !DILocation(line: 55, column: 18, scope: !1803)
!1863 = !DILocation(line: 56, column: 3, scope: !1803)
!1864 = !DILocation(line: 56, column: 8, scope: !1803)
!1865 = !DILocation(line: 56, column: 19, scope: !1803)
!1866 = !DILocation(line: 58, column: 3, scope: !1803)
!1867 = !DILocation(line: 58, column: 9, scope: !1803)
!1868 = !DILocation(line: 58, column: 18, scope: !1803)
!1869 = !DILocation(line: 59, column: 3, scope: !1803)
!1870 = !DILocation(line: 59, column: 9, scope: !1803)
!1871 = !DILocation(line: 59, column: 23, scope: !1803)
!1872 = !DILocation(line: 60, column: 3, scope: !1803)
!1873 = !DILocation(line: 60, column: 9, scope: !1803)
!1874 = !DILocation(line: 60, column: 21, scope: !1803)
!1875 = !DILocation(line: 61, column: 3, scope: !1803)
!1876 = !DILocation(line: 61, column: 9, scope: !1803)
!1877 = !DILocation(line: 61, column: 18, scope: !1803)
!1878 = !DILocation(line: 62, column: 3, scope: !1803)
!1879 = !DILocation(line: 62, column: 9, scope: !1803)
!1880 = !DILocation(line: 62, column: 18, scope: !1803)
!1881 = !DILocation(line: 64, column: 3, scope: !1803)
!1882 = !DILocation(line: 64, column: 9, scope: !1803)
!1883 = !DILocation(line: 64, column: 21, scope: !1803)
!1884 = !DILocation(line: 65, column: 3, scope: !1803)
!1885 = !DILocation(line: 65, column: 9, scope: !1803)
!1886 = !DILocation(line: 65, column: 22, scope: !1803)
!1887 = !DILocation(line: 66, column: 3, scope: !1803)
!1888 = !DILocation(line: 66, column: 9, scope: !1803)
!1889 = !DILocation(line: 66, column: 24, scope: !1803)
!1890 = !DILocation(line: 67, column: 3, scope: !1803)
!1891 = !DILocation(line: 67, column: 9, scope: !1803)
!1892 = !DILocation(line: 67, column: 23, scope: !1803)
!1893 = !DILocation(line: 68, column: 3, scope: !1803)
!1894 = !DILocation(line: 68, column: 9, scope: !1803)
!1895 = !DILocation(line: 68, column: 21, scope: !1803)
!1896 = !DILocation(line: 70, column: 3, scope: !1803)
!1897 = !DILocation(line: 71, column: 3, scope: !1803)
!1898 = !DILocation(line: 71, column: 9, scope: !1803)
!1899 = !DILocation(line: 71, column: 21, scope: !1803)
!1900 = !DILocation(line: 73, column: 3, scope: !1803)
!1901 = !DILocation(line: 74, column: 3, scope: !1803)
!1902 = !DILocation(line: 74, column: 9, scope: !1803)
!1903 = !DILocation(line: 74, column: 23, scope: !1803)
!1904 = !DILocation(line: 76, column: 3, scope: !1803)
!1905 = !DILocation(line: 76, column: 9, scope: !1803)
!1906 = !DILocation(line: 76, column: 28, scope: !1803)
!1907 = !DILocation(line: 77, column: 3, scope: !1803)
!1908 = !DILocation(line: 77, column: 9, scope: !1803)
!1909 = !DILocation(line: 77, column: 26, scope: !1803)
!1910 = !DILocation(line: 78, column: 3, scope: !1803)
!1911 = !DILocation(line: 78, column: 9, scope: !1803)
!1912 = !DILocation(line: 78, column: 27, scope: !1803)
!1913 = !DILocation(line: 79, column: 3, scope: !1803)
!1914 = !DILocation(line: 79, column: 9, scope: !1803)
!1915 = !DILocation(line: 79, column: 25, scope: !1803)
!1916 = !DILocation(line: 81, column: 3, scope: !1803)
!1917 = !DILocation(line: 81, column: 9, scope: !1803)
!1918 = !DILocation(line: 81, column: 21, scope: !1803)
!1919 = !DILocation(line: 82, column: 3, scope: !1803)
!1920 = !DILocation(line: 82, column: 9, scope: !1803)
!1921 = !DILocation(line: 82, column: 23, scope: !1803)
!1922 = !DILocation(line: 88, column: 3, scope: !1803)
!1923 = !DILocalVariable(name: "data", arg: 1, scope: !1807, file: !1, line: 392, type: !256)
!1924 = !DILocation(line: 392, column: 41, scope: !1807)
!1925 = !DILocalVariable(name: "info", arg: 2, scope: !1807, file: !1, line: 392, type: !1810)
!1926 = !DILocation(line: 392, column: 56, scope: !1807)
!1927 = !DILocalVariable(name: "arg", scope: !1807, file: !1, line: 394, type: !1928)
!1928 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !534, line: 79, baseType: !1929)
!1929 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !1930, line: 50, baseType: !1931)
!1930 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1931 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 394, baseType: !1932)
!1932 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1933, size: 192, align: 64, elements: !569)
!1933 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 394, size: 192, align: 64, elements: !1934)
!1934 = !{!1935, !1936, !1937, !1938}
!1935 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !1933, file: !1, line: 394, baseType: !683, size: 32, align: 32)
!1936 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !1933, file: !1, line: 394, baseType: !683, size: 32, align: 32, offset: 32)
!1937 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !1933, file: !1, line: 394, baseType: !311, size: 64, align: 64, offset: 64)
!1938 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !1933, file: !1, line: 394, baseType: !311, size: 64, align: 64, offset: 128)
!1939 = !DILocation(line: 394, column: 11, scope: !1807)
!1940 = !DILocalVariable(name: "param_longp", scope: !1807, file: !1, line: 395, type: !1818)
!1941 = !DILocation(line: 395, column: 9, scope: !1807)
!1942 = !DILocalVariable(name: "param_doublep", scope: !1807, file: !1, line: 396, type: !1822)
!1943 = !DILocation(line: 396, column: 11, scope: !1807)
!1944 = !DILocalVariable(name: "param_charp", scope: !1807, file: !1, line: 397, type: !1814)
!1945 = !DILocation(line: 397, column: 16, scope: !1807)
!1946 = !DILocalVariable(name: "param_slistp", scope: !1807, file: !1, line: 398, type: !1233)
!1947 = !DILocation(line: 398, column: 23, scope: !1807)
!1948 = !DILocalVariable(name: "param_socketp", scope: !1807, file: !1, line: 399, type: !1442)
!1949 = !DILocation(line: 399, column: 18, scope: !1807)
!1950 = !DILocalVariable(name: "type", scope: !1807, file: !1, line: 400, type: !316)
!1951 = !DILocation(line: 400, column: 7, scope: !1807)
!1952 = !DILocalVariable(name: "result", scope: !1807, file: !1, line: 401, type: !289)
!1953 = !DILocation(line: 401, column: 12, scope: !1807)
!1954 = !DILocation(line: 403, column: 7, scope: !1955)
!1955 = distinct !DILexicalBlock(scope: !1807, file: !1, line: 403, column: 6)
!1956 = !DILocation(line: 403, column: 6, scope: !1807)
!1957 = !DILocation(line: 404, column: 12, scope: !1955)
!1958 = !DILocation(line: 404, column: 5, scope: !1955)
!1959 = !DILocation(line: 406, column: 3, scope: !1807)
!1960 = !DILocation(line: 408, column: 35, scope: !1807)
!1961 = !DILocation(line: 408, column: 28, scope: !1807)
!1962 = !DILocation(line: 408, column: 8, scope: !1807)
!1963 = !DILocation(line: 409, column: 10, scope: !1807)
!1964 = !DILocation(line: 409, column: 3, scope: !1807)
!1965 = !DILocation(line: 411, column: 19, scope: !1966)
!1966 = distinct !DILexicalBlock(scope: !1807, file: !1, line: 409, column: 16)
!1967 = !DILocation(line: 411, column: 19, scope: !1968)
!1968 = !DILexicalBlockFile(scope: !1966, file: !1, discriminator: 1)
!1969 = !DILocation(line: 411, column: 19, scope: !1970)
!1970 = !DILexicalBlockFile(scope: !1966, file: !1, discriminator: 2)
!1971 = !DILocation(line: 411, column: 19, scope: !1972)
!1972 = !DILexicalBlockFile(scope: !1966, file: !1, discriminator: 3)
!1973 = !DILocation(line: 411, column: 17, scope: !1972)
!1974 = !DILocation(line: 412, column: 8, scope: !1975)
!1975 = distinct !DILexicalBlock(scope: !1966, file: !1, line: 412, column: 8)
!1976 = !DILocation(line: 412, column: 8, scope: !1966)
!1977 = !DILocation(line: 413, column: 29, scope: !1975)
!1978 = !DILocation(line: 413, column: 35, scope: !1975)
!1979 = !DILocation(line: 413, column: 41, scope: !1975)
!1980 = !DILocation(line: 413, column: 16, scope: !1975)
!1981 = !DILocation(line: 413, column: 14, scope: !1975)
!1982 = !DILocation(line: 413, column: 7, scope: !1975)
!1983 = !DILocation(line: 414, column: 5, scope: !1966)
!1984 = !DILocation(line: 416, column: 19, scope: !1966)
!1985 = !DILocation(line: 416, column: 19, scope: !1968)
!1986 = !DILocation(line: 416, column: 19, scope: !1970)
!1987 = !DILocation(line: 416, column: 19, scope: !1972)
!1988 = !DILocation(line: 416, column: 17, scope: !1972)
!1989 = !DILocation(line: 417, column: 8, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !1966, file: !1, line: 417, column: 8)
!1991 = !DILocation(line: 417, column: 8, scope: !1966)
!1992 = !DILocation(line: 418, column: 29, scope: !1990)
!1993 = !DILocation(line: 418, column: 35, scope: !1990)
!1994 = !DILocation(line: 418, column: 41, scope: !1990)
!1995 = !DILocation(line: 418, column: 16, scope: !1990)
!1996 = !DILocation(line: 418, column: 14, scope: !1990)
!1997 = !DILocation(line: 418, column: 7, scope: !1990)
!1998 = !DILocation(line: 419, column: 5, scope: !1966)
!1999 = !DILocation(line: 421, column: 21, scope: !1966)
!2000 = !DILocation(line: 421, column: 21, scope: !1968)
!2001 = !DILocation(line: 421, column: 21, scope: !1970)
!2002 = !DILocation(line: 421, column: 21, scope: !1972)
!2003 = !DILocation(line: 421, column: 19, scope: !1972)
!2004 = !DILocation(line: 422, column: 8, scope: !2005)
!2005 = distinct !DILexicalBlock(scope: !1966, file: !1, line: 422, column: 8)
!2006 = !DILocation(line: 422, column: 8, scope: !1966)
!2007 = !DILocation(line: 423, column: 31, scope: !2005)
!2008 = !DILocation(line: 423, column: 37, scope: !2005)
!2009 = !DILocation(line: 423, column: 43, scope: !2005)
!2010 = !DILocation(line: 423, column: 16, scope: !2005)
!2011 = !DILocation(line: 423, column: 14, scope: !2005)
!2012 = !DILocation(line: 423, column: 7, scope: !2005)
!2013 = !DILocation(line: 424, column: 5, scope: !1966)
!2014 = !DILocation(line: 426, column: 20, scope: !1966)
!2015 = !DILocation(line: 426, column: 20, scope: !1968)
!2016 = !DILocation(line: 426, column: 20, scope: !1970)
!2017 = !DILocation(line: 426, column: 20, scope: !1972)
!2018 = !DILocation(line: 426, column: 18, scope: !1972)
!2019 = !DILocation(line: 427, column: 8, scope: !2020)
!2020 = distinct !DILexicalBlock(scope: !1966, file: !1, line: 427, column: 8)
!2021 = !DILocation(line: 427, column: 8, scope: !1966)
!2022 = !DILocation(line: 428, column: 30, scope: !2020)
!2023 = !DILocation(line: 428, column: 36, scope: !2020)
!2024 = !DILocation(line: 428, column: 42, scope: !2020)
!2025 = !DILocation(line: 428, column: 16, scope: !2020)
!2026 = !DILocation(line: 428, column: 14, scope: !2020)
!2027 = !DILocation(line: 428, column: 7, scope: !2020)
!2028 = !DILocation(line: 429, column: 5, scope: !1966)
!2029 = !DILocation(line: 431, column: 21, scope: !1966)
!2030 = !DILocation(line: 431, column: 21, scope: !1968)
!2031 = !DILocation(line: 431, column: 21, scope: !1970)
!2032 = !DILocation(line: 431, column: 21, scope: !1972)
!2033 = !DILocation(line: 431, column: 19, scope: !1972)
!2034 = !DILocation(line: 432, column: 8, scope: !2035)
!2035 = distinct !DILexicalBlock(scope: !1966, file: !1, line: 432, column: 8)
!2036 = !DILocation(line: 432, column: 8, scope: !1966)
!2037 = !DILocation(line: 433, column: 31, scope: !2035)
!2038 = !DILocation(line: 433, column: 37, scope: !2035)
!2039 = !DILocation(line: 433, column: 43, scope: !2035)
!2040 = !DILocation(line: 433, column: 16, scope: !2035)
!2041 = !DILocation(line: 433, column: 14, scope: !2035)
!2042 = !DILocation(line: 433, column: 7, scope: !2035)
!2043 = !DILocation(line: 434, column: 5, scope: !1966)
!2044 = !DILocation(line: 436, column: 5, scope: !1966)
!2045 = !DILocation(line: 439, column: 3, scope: !1807)
!2046 = !DILocation(line: 441, column: 10, scope: !1807)
!2047 = !DILocation(line: 441, column: 3, scope: !1807)
!2048 = !DILocation(line: 442, column: 1, scope: !1807)
!2049 = !DILocalVariable(name: "data", arg: 1, scope: !1811, file: !1, line: 91, type: !256)
!2050 = !DILocation(line: 91, column: 48, scope: !1811)
!2051 = !DILocalVariable(name: "info", arg: 2, scope: !1811, file: !1, line: 91, type: !1810)
!2052 = !DILocation(line: 91, column: 63, scope: !1811)
!2053 = !DILocalVariable(name: "param_charp", arg: 3, scope: !1811, file: !1, line: 92, type: !1814)
!2054 = !DILocation(line: 92, column: 43, scope: !1811)
!2055 = !DILocation(line: 94, column: 10, scope: !1811)
!2056 = !DILocation(line: 94, column: 3, scope: !1811)
!2057 = !DILocation(line: 96, column: 20, scope: !2058)
!2058 = distinct !DILexicalBlock(scope: !1811, file: !1, line: 94, column: 16)
!2059 = !DILocation(line: 96, column: 26, scope: !2058)
!2060 = !DILocation(line: 96, column: 33, scope: !2058)
!2061 = !DILocation(line: 96, column: 37, scope: !2062)
!2062 = !DILexicalBlockFile(scope: !2058, file: !1, discriminator: 1)
!2063 = !DILocation(line: 96, column: 43, scope: !2062)
!2064 = !DILocation(line: 96, column: 50, scope: !2062)
!2065 = !DILocation(line: 96, column: 20, scope: !2062)
!2066 = !DILocation(line: 96, column: 20, scope: !2067)
!2067 = !DILexicalBlockFile(scope: !2058, file: !1, discriminator: 2)
!2068 = !DILocation(line: 96, column: 20, scope: !2069)
!2069 = !DILexicalBlockFile(scope: !2058, file: !1, discriminator: 3)
!2070 = !DILocation(line: 96, column: 6, scope: !2069)
!2071 = !DILocation(line: 96, column: 18, scope: !2069)
!2072 = !DILocation(line: 97, column: 5, scope: !2058)
!2073 = !DILocation(line: 99, column: 20, scope: !2058)
!2074 = !DILocation(line: 99, column: 26, scope: !2058)
!2075 = !DILocation(line: 99, column: 31, scope: !2058)
!2076 = !DILocation(line: 99, column: 6, scope: !2058)
!2077 = !DILocation(line: 99, column: 18, scope: !2058)
!2078 = !DILocation(line: 100, column: 5, scope: !2058)
!2079 = !DILocation(line: 102, column: 29, scope: !2058)
!2080 = !DILocation(line: 102, column: 35, scope: !2058)
!2081 = !DILocation(line: 102, column: 39, scope: !2058)
!2082 = !DILocation(line: 102, column: 6, scope: !2058)
!2083 = !DILocation(line: 102, column: 18, scope: !2058)
!2084 = !DILocation(line: 103, column: 5, scope: !2058)
!2085 = !DILocation(line: 110, column: 20, scope: !2058)
!2086 = !DILocation(line: 110, column: 26, scope: !2058)
!2087 = !DILocation(line: 110, column: 32, scope: !2058)
!2088 = !DILocation(line: 110, column: 6, scope: !2058)
!2089 = !DILocation(line: 110, column: 18, scope: !2058)
!2090 = !DILocation(line: 111, column: 5, scope: !2058)
!2091 = !DILocation(line: 115, column: 20, scope: !2058)
!2092 = !DILocation(line: 115, column: 26, scope: !2058)
!2093 = !DILocation(line: 115, column: 31, scope: !2058)
!2094 = !DILocation(line: 115, column: 6, scope: !2058)
!2095 = !DILocation(line: 115, column: 18, scope: !2058)
!2096 = !DILocation(line: 116, column: 5, scope: !2058)
!2097 = !DILocation(line: 119, column: 20, scope: !2058)
!2098 = !DILocation(line: 119, column: 26, scope: !2058)
!2099 = !DILocation(line: 119, column: 31, scope: !2058)
!2100 = !DILocation(line: 119, column: 6, scope: !2058)
!2101 = !DILocation(line: 119, column: 18, scope: !2058)
!2102 = !DILocation(line: 120, column: 5, scope: !2058)
!2103 = !DILocation(line: 124, column: 20, scope: !2058)
!2104 = !DILocation(line: 124, column: 26, scope: !2058)
!2105 = !DILocation(line: 124, column: 31, scope: !2058)
!2106 = !DILocation(line: 124, column: 6, scope: !2058)
!2107 = !DILocation(line: 124, column: 18, scope: !2058)
!2108 = !DILocation(line: 125, column: 5, scope: !2058)
!2109 = !DILocation(line: 127, column: 20, scope: !2058)
!2110 = !DILocation(line: 127, column: 26, scope: !2058)
!2111 = !DILocation(line: 127, column: 30, scope: !2058)
!2112 = !DILocation(line: 127, column: 6, scope: !2058)
!2113 = !DILocation(line: 127, column: 18, scope: !2058)
!2114 = !DILocation(line: 128, column: 5, scope: !2058)
!2115 = !DILocation(line: 130, column: 20, scope: !2058)
!2116 = !DILocation(line: 130, column: 26, scope: !2058)
!2117 = !DILocation(line: 130, column: 31, scope: !2058)
!2118 = !DILocation(line: 130, column: 6, scope: !2058)
!2119 = !DILocation(line: 130, column: 18, scope: !2058)
!2120 = !DILocation(line: 131, column: 5, scope: !2058)
!2121 = !DILocation(line: 134, column: 5, scope: !2058)
!2122 = !DILocation(line: 137, column: 3, scope: !1811)
!2123 = !DILocation(line: 138, column: 1, scope: !1811)
!2124 = !DILocalVariable(name: "data", arg: 1, scope: !1815, file: !1, line: 140, type: !256)
!2125 = !DILocation(line: 140, column: 48, scope: !1815)
!2126 = !DILocalVariable(name: "info", arg: 2, scope: !1815, file: !1, line: 140, type: !1810)
!2127 = !DILocation(line: 140, column: 63, scope: !1815)
!2128 = !DILocalVariable(name: "param_longp", arg: 3, scope: !1815, file: !1, line: 141, type: !1818)
!2129 = !DILocation(line: 141, column: 36, scope: !1815)
!2130 = !DILocalVariable(name: "sockfd", scope: !1815, file: !1, line: 143, type: !315)
!2131 = !DILocation(line: 143, column: 17, scope: !1815)
!2132 = !DILocalVariable(name: "lptr", scope: !1815, file: !1, line: 148, type: !2133)
!2133 = !DICompositeType(tag: DW_TAG_union_type, scope: !1815, file: !1, line: 145, size: 64, align: 64, elements: !2134)
!2134 = !{!2135, !2137}
!2135 = !DIDerivedType(tag: DW_TAG_member, name: "to_ulong", scope: !2133, file: !1, line: 146, baseType: !2136, size: 64, align: 64)
!2136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !349, size: 64, align: 64)
!2137 = !DIDerivedType(tag: DW_TAG_member, name: "to_long", scope: !2133, file: !1, line: 147, baseType: !1818, size: 64, align: 64)
!2138 = !DILocation(line: 148, column: 5, scope: !1815)
!2139 = !DILocation(line: 150, column: 10, scope: !1815)
!2140 = !DILocation(line: 150, column: 3, scope: !1815)
!2141 = !DILocation(line: 152, column: 20, scope: !2142)
!2142 = distinct !DILexicalBlock(scope: !1815, file: !1, line: 150, column: 16)
!2143 = !DILocation(line: 152, column: 26, scope: !2142)
!2144 = !DILocation(line: 152, column: 31, scope: !2142)
!2145 = !DILocation(line: 152, column: 6, scope: !2142)
!2146 = !DILocation(line: 152, column: 18, scope: !2142)
!2147 = !DILocation(line: 153, column: 5, scope: !2142)
!2148 = !DILocation(line: 155, column: 20, scope: !2142)
!2149 = !DILocation(line: 155, column: 26, scope: !2142)
!2150 = !DILocation(line: 155, column: 31, scope: !2142)
!2151 = !DILocation(line: 155, column: 6, scope: !2142)
!2152 = !DILocation(line: 155, column: 18, scope: !2142)
!2153 = !DILocation(line: 156, column: 5, scope: !2142)
!2154 = !DILocation(line: 158, column: 20, scope: !2142)
!2155 = !DILocation(line: 158, column: 26, scope: !2142)
!2156 = !DILocation(line: 158, column: 31, scope: !2142)
!2157 = !DILocation(line: 158, column: 6, scope: !2142)
!2158 = !DILocation(line: 158, column: 18, scope: !2142)
!2159 = !DILocation(line: 159, column: 5, scope: !2142)
!2160 = !DILocation(line: 161, column: 20, scope: !2142)
!2161 = !DILocation(line: 161, column: 26, scope: !2142)
!2162 = !DILocation(line: 161, column: 31, scope: !2142)
!2163 = !DILocation(line: 161, column: 6, scope: !2142)
!2164 = !DILocation(line: 161, column: 18, scope: !2142)
!2165 = !DILocation(line: 162, column: 5, scope: !2142)
!2166 = !DILocation(line: 164, column: 20, scope: !2142)
!2167 = !DILocation(line: 164, column: 26, scope: !2142)
!2168 = !DILocation(line: 164, column: 31, scope: !2142)
!2169 = !DILocation(line: 164, column: 6, scope: !2142)
!2170 = !DILocation(line: 164, column: 18, scope: !2142)
!2171 = !DILocation(line: 165, column: 5, scope: !2142)
!2172 = !DILocation(line: 167, column: 20, scope: !2142)
!2173 = !DILocation(line: 167, column: 26, scope: !2142)
!2174 = !DILocation(line: 167, column: 30, scope: !2142)
!2175 = !DILocation(line: 167, column: 34, scope: !2142)
!2176 = !DILocation(line: 167, column: 6, scope: !2142)
!2177 = !DILocation(line: 167, column: 18, scope: !2142)
!2178 = !DILocation(line: 168, column: 5, scope: !2142)
!2179 = !DILocation(line: 170, column: 20, scope: !2142)
!2180 = !DILocation(line: 170, column: 26, scope: !2142)
!2181 = !DILocation(line: 170, column: 30, scope: !2142)
!2182 = !DILocation(line: 170, column: 40, scope: !2142)
!2183 = !DILocation(line: 170, column: 6, scope: !2142)
!2184 = !DILocation(line: 170, column: 18, scope: !2142)
!2185 = !DILocation(line: 171, column: 5, scope: !2142)
!2186 = !DILocation(line: 173, column: 20, scope: !2142)
!2187 = !DILocation(line: 173, column: 26, scope: !2142)
!2188 = !DILocation(line: 173, column: 30, scope: !2142)
!2189 = !DILocation(line: 173, column: 6, scope: !2142)
!2190 = !DILocation(line: 173, column: 18, scope: !2142)
!2191 = !DILocation(line: 174, column: 5, scope: !2142)
!2192 = !DILocation(line: 176, column: 20, scope: !2142)
!2193 = !DILocation(line: 176, column: 10, scope: !2142)
!2194 = !DILocation(line: 176, column: 18, scope: !2142)
!2195 = !DILocation(line: 177, column: 22, scope: !2142)
!2196 = !DILocation(line: 177, column: 28, scope: !2142)
!2197 = !DILocation(line: 177, column: 33, scope: !2142)
!2198 = !DILocation(line: 177, column: 11, scope: !2142)
!2199 = !DILocation(line: 177, column: 20, scope: !2142)
!2200 = !DILocation(line: 178, column: 5, scope: !2142)
!2201 = !DILocation(line: 180, column: 20, scope: !2142)
!2202 = !DILocation(line: 180, column: 10, scope: !2142)
!2203 = !DILocation(line: 180, column: 18, scope: !2142)
!2204 = !DILocation(line: 181, column: 22, scope: !2142)
!2205 = !DILocation(line: 181, column: 28, scope: !2142)
!2206 = !DILocation(line: 181, column: 33, scope: !2142)
!2207 = !DILocation(line: 181, column: 11, scope: !2142)
!2208 = !DILocation(line: 181, column: 20, scope: !2142)
!2209 = !DILocation(line: 182, column: 5, scope: !2142)
!2210 = !DILocation(line: 184, column: 20, scope: !2142)
!2211 = !DILocation(line: 184, column: 26, scope: !2142)
!2212 = !DILocation(line: 184, column: 32, scope: !2142)
!2213 = !DILocation(line: 184, column: 6, scope: !2142)
!2214 = !DILocation(line: 184, column: 18, scope: !2142)
!2215 = !DILocation(line: 185, column: 5, scope: !2142)
!2216 = !DILocation(line: 187, column: 20, scope: !2142)
!2217 = !DILocation(line: 187, column: 26, scope: !2142)
!2218 = !DILocation(line: 187, column: 31, scope: !2142)
!2219 = !DILocation(line: 187, column: 6, scope: !2142)
!2220 = !DILocation(line: 187, column: 18, scope: !2142)
!2221 = !DILocation(line: 188, column: 5, scope: !2142)
!2222 = !DILocation(line: 190, column: 34, scope: !2142)
!2223 = !DILocation(line: 190, column: 14, scope: !2142)
!2224 = !DILocation(line: 190, column: 12, scope: !2142)
!2225 = !DILocation(line: 194, column: 8, scope: !2226)
!2226 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 194, column: 8)
!2227 = !DILocation(line: 194, column: 15, scope: !2226)
!2228 = !DILocation(line: 194, column: 8, scope: !2142)
!2229 = !DILocation(line: 195, column: 28, scope: !2226)
!2230 = !DILocation(line: 195, column: 22, scope: !2226)
!2231 = !DILocation(line: 195, column: 8, scope: !2226)
!2232 = !DILocation(line: 195, column: 20, scope: !2226)
!2233 = !DILocation(line: 195, column: 7, scope: !2226)
!2234 = !DILocation(line: 199, column: 8, scope: !2226)
!2235 = !DILocation(line: 199, column: 20, scope: !2226)
!2236 = !DILocation(line: 200, column: 5, scope: !2142)
!2237 = !DILocation(line: 203, column: 20, scope: !2142)
!2238 = !DILocation(line: 203, column: 26, scope: !2142)
!2239 = !DILocation(line: 203, column: 31, scope: !2142)
!2240 = !DILocation(line: 203, column: 6, scope: !2142)
!2241 = !DILocation(line: 203, column: 18, scope: !2142)
!2242 = !DILocation(line: 204, column: 5, scope: !2142)
!2243 = !DILocation(line: 207, column: 20, scope: !2142)
!2244 = !DILocation(line: 207, column: 26, scope: !2142)
!2245 = !DILocation(line: 207, column: 31, scope: !2142)
!2246 = !DILocation(line: 207, column: 6, scope: !2142)
!2247 = !DILocation(line: 207, column: 18, scope: !2142)
!2248 = !DILocation(line: 208, column: 5, scope: !2142)
!2249 = !DILocation(line: 211, column: 20, scope: !2142)
!2250 = !DILocation(line: 211, column: 26, scope: !2142)
!2251 = !DILocation(line: 211, column: 31, scope: !2142)
!2252 = !DILocation(line: 211, column: 6, scope: !2142)
!2253 = !DILocation(line: 211, column: 18, scope: !2142)
!2254 = !DILocation(line: 212, column: 5, scope: !2142)
!2255 = !DILocation(line: 214, column: 20, scope: !2142)
!2256 = !DILocation(line: 214, column: 26, scope: !2142)
!2257 = !DILocation(line: 214, column: 32, scope: !2142)
!2258 = !DILocation(line: 214, column: 6, scope: !2142)
!2259 = !DILocation(line: 214, column: 18, scope: !2142)
!2260 = !DILocation(line: 215, column: 5, scope: !2142)
!2261 = !DILocation(line: 217, column: 20, scope: !2142)
!2262 = !DILocation(line: 217, column: 26, scope: !2142)
!2263 = !DILocation(line: 217, column: 32, scope: !2142)
!2264 = !DILocation(line: 217, column: 6, scope: !2142)
!2265 = !DILocation(line: 217, column: 18, scope: !2142)
!2266 = !DILocation(line: 218, column: 5, scope: !2142)
!2267 = !DILocation(line: 220, column: 20, scope: !2142)
!2268 = !DILocation(line: 220, column: 26, scope: !2142)
!2269 = !DILocation(line: 220, column: 32, scope: !2142)
!2270 = !DILocation(line: 220, column: 6, scope: !2142)
!2271 = !DILocation(line: 220, column: 18, scope: !2142)
!2272 = !DILocation(line: 221, column: 5, scope: !2142)
!2273 = !DILocation(line: 223, column: 12, scope: !2142)
!2274 = !DILocation(line: 223, column: 18, scope: !2142)
!2275 = !DILocation(line: 223, column: 23, scope: !2142)
!2276 = !DILocation(line: 223, column: 5, scope: !2142)
!2277 = !DILocation(line: 225, column: 8, scope: !2278)
!2278 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 223, column: 36)
!2279 = !DILocation(line: 225, column: 20, scope: !2278)
!2280 = !DILocation(line: 226, column: 7, scope: !2278)
!2281 = !DILocation(line: 228, column: 8, scope: !2278)
!2282 = !DILocation(line: 228, column: 20, scope: !2278)
!2283 = !DILocation(line: 229, column: 7, scope: !2278)
!2284 = !DILocation(line: 231, column: 8, scope: !2278)
!2285 = !DILocation(line: 231, column: 20, scope: !2278)
!2286 = !DILocation(line: 232, column: 7, scope: !2278)
!2287 = !DILocation(line: 234, column: 8, scope: !2278)
!2288 = !DILocation(line: 234, column: 20, scope: !2278)
!2289 = !DILocation(line: 235, column: 7, scope: !2278)
!2290 = !DILocation(line: 237, column: 5, scope: !2142)
!2291 = !DILocation(line: 239, column: 20, scope: !2142)
!2292 = !DILocation(line: 239, column: 26, scope: !2142)
!2293 = !DILocation(line: 239, column: 31, scope: !2142)
!2294 = !DILocation(line: 239, column: 6, scope: !2142)
!2295 = !DILocation(line: 239, column: 18, scope: !2142)
!2296 = !DILocation(line: 240, column: 5, scope: !2142)
!2297 = !DILocation(line: 243, column: 5, scope: !2142)
!2298 = !DILocation(line: 246, column: 3, scope: !1815)
!2299 = !DILocation(line: 247, column: 1, scope: !1815)
!2300 = !DILocalVariable(name: "data", arg: 1, scope: !1819, file: !1, line: 249, type: !256)
!2301 = !DILocation(line: 249, column: 50, scope: !1819)
!2302 = !DILocalVariable(name: "info", arg: 2, scope: !1819, file: !1, line: 249, type: !1810)
!2303 = !DILocation(line: 249, column: 65, scope: !1819)
!2304 = !DILocalVariable(name: "param_doublep", arg: 3, scope: !1819, file: !1, line: 250, type: !1822)
!2305 = !DILocation(line: 250, column: 40, scope: !1819)
!2306 = !DILocation(line: 252, column: 10, scope: !1819)
!2307 = !DILocation(line: 252, column: 3, scope: !1819)
!2308 = !DILocation(line: 254, column: 22, scope: !2309)
!2309 = distinct !DILexicalBlock(scope: !1819, file: !1, line: 252, column: 16)
!2310 = !DILocation(line: 254, column: 28, scope: !2309)
!2311 = !DILocation(line: 254, column: 37, scope: !2309)
!2312 = !DILocation(line: 254, column: 6, scope: !2309)
!2313 = !DILocation(line: 254, column: 20, scope: !2309)
!2314 = !DILocation(line: 255, column: 5, scope: !2309)
!2315 = !DILocation(line: 257, column: 22, scope: !2309)
!2316 = !DILocation(line: 257, column: 28, scope: !2309)
!2317 = !DILocation(line: 257, column: 37, scope: !2309)
!2318 = !DILocation(line: 257, column: 6, scope: !2309)
!2319 = !DILocation(line: 257, column: 20, scope: !2309)
!2320 = !DILocation(line: 258, column: 5, scope: !2309)
!2321 = !DILocation(line: 260, column: 22, scope: !2309)
!2322 = !DILocation(line: 260, column: 28, scope: !2309)
!2323 = !DILocation(line: 260, column: 37, scope: !2309)
!2324 = !DILocation(line: 260, column: 6, scope: !2309)
!2325 = !DILocation(line: 260, column: 20, scope: !2309)
!2326 = !DILocation(line: 261, column: 5, scope: !2309)
!2327 = !DILocation(line: 263, column: 22, scope: !2309)
!2328 = !DILocation(line: 263, column: 28, scope: !2309)
!2329 = !DILocation(line: 263, column: 37, scope: !2309)
!2330 = !DILocation(line: 263, column: 6, scope: !2309)
!2331 = !DILocation(line: 263, column: 20, scope: !2309)
!2332 = !DILocation(line: 264, column: 5, scope: !2309)
!2333 = !DILocation(line: 266, column: 23, scope: !2309)
!2334 = !DILocation(line: 266, column: 29, scope: !2309)
!2335 = !DILocation(line: 266, column: 38, scope: !2309)
!2336 = !DILocation(line: 266, column: 6, scope: !2309)
!2337 = !DILocation(line: 266, column: 20, scope: !2309)
!2338 = !DILocation(line: 267, column: 5, scope: !2309)
!2339 = !DILocation(line: 269, column: 22, scope: !2309)
!2340 = !DILocation(line: 269, column: 28, scope: !2309)
!2341 = !DILocation(line: 269, column: 37, scope: !2309)
!2342 = !DILocation(line: 269, column: 6, scope: !2309)
!2343 = !DILocation(line: 269, column: 20, scope: !2309)
!2344 = !DILocation(line: 270, column: 5, scope: !2309)
!2345 = !DILocation(line: 272, column: 31, scope: !2309)
!2346 = !DILocation(line: 272, column: 37, scope: !2309)
!2347 = !DILocation(line: 272, column: 46, scope: !2309)
!2348 = !DILocation(line: 272, column: 23, scope: !2309)
!2349 = !DILocation(line: 272, column: 6, scope: !2309)
!2350 = !DILocation(line: 272, column: 20, scope: !2309)
!2351 = !DILocation(line: 273, column: 5, scope: !2309)
!2352 = !DILocation(line: 275, column: 30, scope: !2309)
!2353 = !DILocation(line: 275, column: 36, scope: !2309)
!2354 = !DILocation(line: 275, column: 45, scope: !2309)
!2355 = !DILocation(line: 275, column: 22, scope: !2309)
!2356 = !DILocation(line: 275, column: 6, scope: !2309)
!2357 = !DILocation(line: 275, column: 20, scope: !2309)
!2358 = !DILocation(line: 276, column: 5, scope: !2309)
!2359 = !DILocation(line: 278, column: 31, scope: !2309)
!2360 = !DILocation(line: 278, column: 37, scope: !2309)
!2361 = !DILocation(line: 278, column: 46, scope: !2309)
!2362 = !DILocation(line: 278, column: 23, scope: !2309)
!2363 = !DILocation(line: 278, column: 6, scope: !2309)
!2364 = !DILocation(line: 278, column: 20, scope: !2309)
!2365 = !DILocation(line: 279, column: 5, scope: !2309)
!2366 = !DILocation(line: 281, column: 30, scope: !2309)
!2367 = !DILocation(line: 281, column: 36, scope: !2309)
!2368 = !DILocation(line: 281, column: 45, scope: !2309)
!2369 = !DILocation(line: 281, column: 22, scope: !2309)
!2370 = !DILocation(line: 281, column: 6, scope: !2309)
!2371 = !DILocation(line: 281, column: 20, scope: !2309)
!2372 = !DILocation(line: 282, column: 5, scope: !2309)
!2373 = !DILocation(line: 284, column: 23, scope: !2309)
!2374 = !DILocation(line: 284, column: 29, scope: !2309)
!2375 = !DILocation(line: 284, column: 38, scope: !2309)
!2376 = !DILocation(line: 284, column: 44, scope: !2309)
!2377 = !DILocation(line: 284, column: 22, scope: !2309)
!2378 = !DILocation(line: 285, column: 15, scope: !2309)
!2379 = !DILocation(line: 285, column: 21, scope: !2309)
!2380 = !DILocation(line: 285, column: 30, scope: !2309)
!2381 = !DILocation(line: 285, column: 7, scope: !2309)
!2382 = !DILocation(line: 284, column: 22, scope: !2383)
!2383 = !DILexicalBlockFile(scope: !2309, file: !1, discriminator: 1)
!2384 = !DILocation(line: 284, column: 22, scope: !2385)
!2385 = !DILexicalBlockFile(scope: !2309, file: !1, discriminator: 2)
!2386 = !DILocation(line: 284, column: 22, scope: !2387)
!2387 = !DILexicalBlockFile(scope: !2309, file: !1, discriminator: 3)
!2388 = !DILocation(line: 284, column: 6, scope: !2387)
!2389 = !DILocation(line: 284, column: 20, scope: !2387)
!2390 = !DILocation(line: 286, column: 5, scope: !2309)
!2391 = !DILocation(line: 288, column: 23, scope: !2309)
!2392 = !DILocation(line: 288, column: 29, scope: !2309)
!2393 = !DILocation(line: 288, column: 38, scope: !2309)
!2394 = !DILocation(line: 288, column: 44, scope: !2309)
!2395 = !DILocation(line: 288, column: 22, scope: !2309)
!2396 = !DILocation(line: 289, column: 15, scope: !2309)
!2397 = !DILocation(line: 289, column: 21, scope: !2309)
!2398 = !DILocation(line: 289, column: 30, scope: !2309)
!2399 = !DILocation(line: 289, column: 7, scope: !2309)
!2400 = !DILocation(line: 288, column: 22, scope: !2383)
!2401 = !DILocation(line: 288, column: 22, scope: !2385)
!2402 = !DILocation(line: 288, column: 22, scope: !2387)
!2403 = !DILocation(line: 288, column: 6, scope: !2387)
!2404 = !DILocation(line: 288, column: 20, scope: !2387)
!2405 = !DILocation(line: 290, column: 5, scope: !2309)
!2406 = !DILocation(line: 292, column: 23, scope: !2309)
!2407 = !DILocation(line: 292, column: 29, scope: !2309)
!2408 = !DILocation(line: 292, column: 38, scope: !2309)
!2409 = !DILocation(line: 292, column: 6, scope: !2309)
!2410 = !DILocation(line: 292, column: 20, scope: !2309)
!2411 = !DILocation(line: 293, column: 5, scope: !2309)
!2412 = !DILocation(line: 296, column: 5, scope: !2309)
!2413 = !DILocation(line: 299, column: 3, scope: !1819)
!2414 = !DILocation(line: 300, column: 1, scope: !1819)
!2415 = !DILocalVariable(name: "data", arg: 1, scope: !1823, file: !1, line: 302, type: !256)
!2416 = !DILocation(line: 302, column: 49, scope: !1823)
!2417 = !DILocalVariable(name: "info", arg: 2, scope: !1823, file: !1, line: 302, type: !1810)
!2418 = !DILocation(line: 302, column: 64, scope: !1823)
!2419 = !DILocalVariable(name: "param_slistp", arg: 3, scope: !1823, file: !1, line: 303, type: !1233)
!2420 = !DILocation(line: 303, column: 51, scope: !1823)
!2421 = !DILocalVariable(name: "ptr", scope: !1823, file: !1, line: 308, type: !2422)
!2422 = !DICompositeType(tag: DW_TAG_union_type, scope: !1823, file: !1, line: 305, size: 64, align: 64, elements: !2423)
!2423 = !{!2424, !2426}
!2424 = !DIDerivedType(tag: DW_TAG_member, name: "to_certinfo", scope: !2422, file: !1, line: 306, baseType: !2425, size: 64, align: 64)
!2425 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1229, size: 64, align: 64)
!2426 = !DIDerivedType(tag: DW_TAG_member, name: "to_slist", scope: !2422, file: !1, line: 307, baseType: !725, size: 64, align: 64)
!2427 = !DILocation(line: 308, column: 5, scope: !1823)
!2428 = !DILocation(line: 310, column: 10, scope: !1823)
!2429 = !DILocation(line: 310, column: 3, scope: !1823)
!2430 = !DILocation(line: 312, column: 6, scope: !2431)
!2431 = distinct !DILexicalBlock(scope: !1823, file: !1, line: 310, column: 16)
!2432 = !DILocation(line: 312, column: 19, scope: !2431)
!2433 = !DILocation(line: 313, column: 5, scope: !2431)
!2434 = !DILocation(line: 315, column: 38, scope: !2431)
!2435 = !DILocation(line: 315, column: 21, scope: !2431)
!2436 = !DILocation(line: 315, column: 6, scope: !2431)
!2437 = !DILocation(line: 315, column: 19, scope: !2431)
!2438 = !DILocation(line: 316, column: 5, scope: !2431)
!2439 = !DILocation(line: 320, column: 24, scope: !2431)
!2440 = !DILocation(line: 320, column: 30, scope: !2431)
!2441 = !DILocation(line: 320, column: 35, scope: !2431)
!2442 = !DILocation(line: 320, column: 9, scope: !2431)
!2443 = !DILocation(line: 320, column: 21, scope: !2431)
!2444 = !DILocation(line: 321, column: 25, scope: !2431)
!2445 = !DILocation(line: 321, column: 6, scope: !2431)
!2446 = !DILocation(line: 321, column: 19, scope: !2431)
!2447 = !DILocation(line: 322, column: 5, scope: !2431)
!2448 = !DILocalVariable(name: "tsip", scope: !2449, file: !1, line: 326, type: !1800)
!2449 = distinct !DILexicalBlock(scope: !2431, file: !1, line: 325, column: 5)
!2450 = !DILocation(line: 326, column: 36, scope: !2449)
!2451 = !DILocation(line: 327, column: 43, scope: !2449)
!2452 = !DILocation(line: 326, column: 43, scope: !2449)
!2453 = !DILocalVariable(name: "tsi", scope: !2449, file: !1, line: 328, type: !1801)
!2454 = !DILocation(line: 328, column: 35, scope: !2449)
!2455 = !DILocation(line: 328, column: 42, scope: !2449)
!2456 = !DILocation(line: 328, column: 48, scope: !2449)
!2457 = !DILocalVariable(name: "conn", scope: !2449, file: !1, line: 329, type: !262)
!2458 = !DILocation(line: 329, column: 27, scope: !2449)
!2459 = !DILocation(line: 329, column: 34, scope: !2449)
!2460 = !DILocation(line: 329, column: 40, scope: !2449)
!2461 = !DILocation(line: 331, column: 15, scope: !2449)
!2462 = !DILocation(line: 331, column: 8, scope: !2449)
!2463 = !DILocation(line: 331, column: 13, scope: !2449)
!2464 = !DILocation(line: 332, column: 22, scope: !2449)
!2465 = !DILocation(line: 332, column: 7, scope: !2449)
!2466 = !DILocation(line: 332, column: 12, scope: !2449)
!2467 = !DILocation(line: 332, column: 20, scope: !2449)
!2468 = !DILocation(line: 333, column: 7, scope: !2449)
!2469 = !DILocation(line: 333, column: 12, scope: !2449)
!2470 = !DILocation(line: 333, column: 22, scope: !2449)
!2471 = !DILocation(line: 335, column: 10, scope: !2472)
!2472 = distinct !DILexicalBlock(scope: !2449, file: !1, line: 335, column: 10)
!2473 = !DILocation(line: 335, column: 15, scope: !2472)
!2474 = !DILocation(line: 335, column: 18, scope: !2475)
!2475 = !DILexicalBlockFile(scope: !2472, file: !1, discriminator: 1)
!2476 = !DILocation(line: 335, column: 23, scope: !2475)
!2477 = !DILocation(line: 335, column: 31, scope: !2475)
!2478 = !DILocation(line: 335, column: 10, scope: !2475)
!2479 = !DILocalVariable(name: "i", scope: !2480, file: !1, line: 336, type: !683)
!2480 = distinct !DILexicalBlock(scope: !2472, file: !1, line: 335, column: 55)
!2481 = !DILocation(line: 336, column: 22, scope: !2480)
!2482 = !DILocation(line: 337, column: 15, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !2480, file: !1, line: 337, column: 9)
!2484 = !DILocation(line: 337, column: 13, scope: !2483)
!2485 = !DILocation(line: 337, column: 20, scope: !2486)
!2486 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 1)
!2487 = distinct !DILexicalBlock(scope: !2483, file: !1, line: 337, column: 9)
!2488 = !DILocation(line: 337, column: 22, scope: !2486)
!2489 = !DILocation(line: 337, column: 9, scope: !2486)
!2490 = !DILocation(line: 338, column: 24, scope: !2491)
!2491 = distinct !DILexicalBlock(scope: !2492, file: !1, line: 338, column: 14)
!2492 = distinct !DILexicalBlock(scope: !2487, file: !1, line: 337, column: 73)
!2493 = !DILocation(line: 338, column: 14, scope: !2491)
!2494 = !DILocation(line: 338, column: 20, scope: !2491)
!2495 = !DILocation(line: 338, column: 27, scope: !2491)
!2496 = !DILocation(line: 338, column: 14, scope: !2492)
!2497 = !DILocation(line: 365, column: 13, scope: !2498)
!2498 = distinct !DILexicalBlock(scope: !2491, file: !1, line: 338, column: 32)
!2499 = !DILocation(line: 367, column: 9, scope: !2492)
!2500 = !DILocation(line: 337, column: 68, scope: !2501)
!2501 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 2)
!2502 = !DILocation(line: 337, column: 9, scope: !2501)
!2503 = !DILocation(line: 368, column: 7, scope: !2480)
!2504 = !DILocation(line: 370, column: 5, scope: !2431)
!2505 = !DILocation(line: 372, column: 5, scope: !2431)
!2506 = !DILocation(line: 375, column: 3, scope: !1823)
!2507 = !DILocation(line: 376, column: 1, scope: !1823)
!2508 = !DILocalVariable(name: "data", arg: 1, scope: !1826, file: !1, line: 378, type: !256)
!2509 = !DILocation(line: 378, column: 50, scope: !1826)
!2510 = !DILocalVariable(name: "info", arg: 2, scope: !1826, file: !1, line: 378, type: !1810)
!2511 = !DILocation(line: 378, column: 65, scope: !1826)
!2512 = !DILocalVariable(name: "param_socketp", arg: 3, scope: !1826, file: !1, line: 379, type: !1442)
!2513 = !DILocation(line: 379, column: 47, scope: !1826)
!2514 = !DILocation(line: 381, column: 10, scope: !1826)
!2515 = !DILocation(line: 381, column: 3, scope: !1826)
!2516 = !DILocation(line: 383, column: 42, scope: !2517)
!2517 = distinct !DILexicalBlock(scope: !1826, file: !1, line: 381, column: 16)
!2518 = !DILocation(line: 383, column: 22, scope: !2517)
!2519 = !DILocation(line: 383, column: 6, scope: !2517)
!2520 = !DILocation(line: 383, column: 20, scope: !2517)
!2521 = !DILocation(line: 384, column: 5, scope: !2517)
!2522 = !DILocation(line: 386, column: 5, scope: !2517)
!2523 = !DILocation(line: 389, column: 3, scope: !1826)
!2524 = !DILocation(line: 390, column: 1, scope: !1826)
