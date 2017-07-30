; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.uv__allocator_t = type { i8* (i64)*, i8* (i8*, i64)*, i8* (i64, i64)*, void (i8*)* }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.2, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.1, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.1 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32 }
%union.anon.0 = type { [4 x i8*] }
%struct.anon.2 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.3, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.4, i32, i32 }
%union.anon.3 = type { [4 x i8*] }
%struct.anon.4 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%struct.uv_buf_t = type { i8*, i64 }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.sockaddr_in6 = type { i16, i16, i32, %struct.in6_addr, i32 }
%struct.in6_addr = type { %union.anon }
%union.anon = type { [4 x i32] }
%struct.uv_tcp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.6, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, {}*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.6 = type { [4 x i8*] }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv_udp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.7, %struct.uv_handle_s*, i32, i64, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, %struct.uv__io_s, [2 x i8*], [2 x i8*] }
%union.anon.7 = type { [4 x i8*] }
%struct.uv_udp_send_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_udp_s*, void (%struct.uv_udp_send_s*, i32)*, [2 x i8*], %struct.sockaddr_storage, i32, %struct.uv_buf_t*, i64, void (%struct.uv_udp_send_s*, i32)*, [4 x %struct.uv_buf_t] }
%struct.sockaddr_storage = type { i16, i64, [112 x i8] }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.uv_fs_event_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.8, %struct.uv_handle_s*, i32, i8*, void (%struct.uv_fs_event_s*, i8*, i32, i32)*, [2 x i8*], i32 }
%union.anon.8 = type { [4 x i8*] }
%struct.uv_fs_s = type { i8*, i32, [2 x i8*], [4 x i8*], i32, %struct.uv_loop_s*, {}*, i64, i8*, i8*, %struct.uv_stat_t, i8*, i32, i32, i32, i32, %struct.uv_buf_t*, i64, i32, i32, double, double, %struct.uv__work, [4 x %struct.uv_buf_t] }
%struct.uv_stat_t = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t }
%struct.uv_timespec_t = type { i64, i64 }
%struct.uv__work = type { void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*, %struct.uv_loop_s*, [2 x i8*] }
%struct.dirent = type { i64, i64, i16, i8, [256 x i8] }
%struct.uv_dirent_s = type { i8*, i32 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@uv__allocator = internal global %struct.uv__allocator_t { i8* (i64)* @malloc, i8* (i8*, i64)* @realloc, i8* (i64, i64)* @calloc, void (i8*)* @free }, align 8
@.str = private unnamed_addr constant [6 x i8] c"E2BIG\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"EACCES\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"EADDRINUSE\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"EADDRNOTAVAIL\00", align 1
@.str.4 = private unnamed_addr constant [13 x i8] c"EAFNOSUPPORT\00", align 1
@.str.5 = private unnamed_addr constant [7 x i8] c"EAGAIN\00", align 1
@.str.6 = private unnamed_addr constant [15 x i8] c"EAI_ADDRFAMILY\00", align 1
@.str.7 = private unnamed_addr constant [10 x i8] c"EAI_AGAIN\00", align 1
@.str.8 = private unnamed_addr constant [13 x i8] c"EAI_BADFLAGS\00", align 1
@.str.9 = private unnamed_addr constant [13 x i8] c"EAI_BADHINTS\00", align 1
@.str.10 = private unnamed_addr constant [13 x i8] c"EAI_CANCELED\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c"EAI_FAIL\00", align 1
@.str.12 = private unnamed_addr constant [11 x i8] c"EAI_FAMILY\00", align 1
@.str.13 = private unnamed_addr constant [11 x i8] c"EAI_MEMORY\00", align 1
@.str.14 = private unnamed_addr constant [11 x i8] c"EAI_NODATA\00", align 1
@.str.15 = private unnamed_addr constant [11 x i8] c"EAI_NONAME\00", align 1
@.str.16 = private unnamed_addr constant [13 x i8] c"EAI_OVERFLOW\00", align 1
@.str.17 = private unnamed_addr constant [13 x i8] c"EAI_PROTOCOL\00", align 1
@.str.18 = private unnamed_addr constant [12 x i8] c"EAI_SERVICE\00", align 1
@.str.19 = private unnamed_addr constant [13 x i8] c"EAI_SOCKTYPE\00", align 1
@.str.20 = private unnamed_addr constant [9 x i8] c"EALREADY\00", align 1
@.str.21 = private unnamed_addr constant [6 x i8] c"EBADF\00", align 1
@.str.22 = private unnamed_addr constant [6 x i8] c"EBUSY\00", align 1
@.str.23 = private unnamed_addr constant [10 x i8] c"ECANCELED\00", align 1
@.str.24 = private unnamed_addr constant [9 x i8] c"ECHARSET\00", align 1
@.str.25 = private unnamed_addr constant [13 x i8] c"ECONNABORTED\00", align 1
@.str.26 = private unnamed_addr constant [13 x i8] c"ECONNREFUSED\00", align 1
@.str.27 = private unnamed_addr constant [11 x i8] c"ECONNRESET\00", align 1
@.str.28 = private unnamed_addr constant [13 x i8] c"EDESTADDRREQ\00", align 1
@.str.29 = private unnamed_addr constant [7 x i8] c"EEXIST\00", align 1
@.str.30 = private unnamed_addr constant [7 x i8] c"EFAULT\00", align 1
@.str.31 = private unnamed_addr constant [6 x i8] c"EFBIG\00", align 1
@.str.32 = private unnamed_addr constant [13 x i8] c"EHOSTUNREACH\00", align 1
@.str.33 = private unnamed_addr constant [6 x i8] c"EINTR\00", align 1
@.str.34 = private unnamed_addr constant [7 x i8] c"EINVAL\00", align 1
@.str.35 = private unnamed_addr constant [4 x i8] c"EIO\00", align 1
@.str.36 = private unnamed_addr constant [8 x i8] c"EISCONN\00", align 1
@.str.37 = private unnamed_addr constant [7 x i8] c"EISDIR\00", align 1
@.str.38 = private unnamed_addr constant [6 x i8] c"ELOOP\00", align 1
@.str.39 = private unnamed_addr constant [7 x i8] c"EMFILE\00", align 1
@.str.40 = private unnamed_addr constant [9 x i8] c"EMSGSIZE\00", align 1
@.str.41 = private unnamed_addr constant [13 x i8] c"ENAMETOOLONG\00", align 1
@.str.42 = private unnamed_addr constant [9 x i8] c"ENETDOWN\00", align 1
@.str.43 = private unnamed_addr constant [12 x i8] c"ENETUNREACH\00", align 1
@.str.44 = private unnamed_addr constant [7 x i8] c"ENFILE\00", align 1
@.str.45 = private unnamed_addr constant [8 x i8] c"ENOBUFS\00", align 1
@.str.46 = private unnamed_addr constant [7 x i8] c"ENODEV\00", align 1
@.str.47 = private unnamed_addr constant [7 x i8] c"ENOENT\00", align 1
@.str.48 = private unnamed_addr constant [7 x i8] c"ENOMEM\00", align 1
@.str.49 = private unnamed_addr constant [7 x i8] c"ENONET\00", align 1
@.str.50 = private unnamed_addr constant [12 x i8] c"ENOPROTOOPT\00", align 1
@.str.51 = private unnamed_addr constant [7 x i8] c"ENOSPC\00", align 1
@.str.52 = private unnamed_addr constant [7 x i8] c"ENOSYS\00", align 1
@.str.53 = private unnamed_addr constant [9 x i8] c"ENOTCONN\00", align 1
@.str.54 = private unnamed_addr constant [8 x i8] c"ENOTDIR\00", align 1
@.str.55 = private unnamed_addr constant [10 x i8] c"ENOTEMPTY\00", align 1
@.str.56 = private unnamed_addr constant [9 x i8] c"ENOTSOCK\00", align 1
@.str.57 = private unnamed_addr constant [8 x i8] c"ENOTSUP\00", align 1
@.str.58 = private unnamed_addr constant [6 x i8] c"EPERM\00", align 1
@.str.59 = private unnamed_addr constant [6 x i8] c"EPIPE\00", align 1
@.str.60 = private unnamed_addr constant [7 x i8] c"EPROTO\00", align 1
@.str.61 = private unnamed_addr constant [16 x i8] c"EPROTONOSUPPORT\00", align 1
@.str.62 = private unnamed_addr constant [11 x i8] c"EPROTOTYPE\00", align 1
@.str.63 = private unnamed_addr constant [7 x i8] c"ERANGE\00", align 1
@.str.64 = private unnamed_addr constant [6 x i8] c"EROFS\00", align 1
@.str.65 = private unnamed_addr constant [10 x i8] c"ESHUTDOWN\00", align 1
@.str.66 = private unnamed_addr constant [7 x i8] c"ESPIPE\00", align 1
@.str.67 = private unnamed_addr constant [6 x i8] c"ESRCH\00", align 1
@.str.68 = private unnamed_addr constant [10 x i8] c"ETIMEDOUT\00", align 1
@.str.69 = private unnamed_addr constant [8 x i8] c"ETXTBSY\00", align 1
@.str.70 = private unnamed_addr constant [6 x i8] c"EXDEV\00", align 1
@.str.71 = private unnamed_addr constant [8 x i8] c"UNKNOWN\00", align 1
@.str.72 = private unnamed_addr constant [4 x i8] c"EOF\00", align 1
@.str.73 = private unnamed_addr constant [6 x i8] c"ENXIO\00", align 1
@.str.74 = private unnamed_addr constant [7 x i8] c"EMLINK\00", align 1
@.str.75 = private unnamed_addr constant [10 x i8] c"EHOSTDOWN\00", align 1
@.str.76 = private unnamed_addr constant [23 x i8] c"argument list too long\00", align 1
@.str.77 = private unnamed_addr constant [18 x i8] c"permission denied\00", align 1
@.str.78 = private unnamed_addr constant [23 x i8] c"address already in use\00", align 1
@.str.79 = private unnamed_addr constant [22 x i8] c"address not available\00", align 1
@.str.80 = private unnamed_addr constant [29 x i8] c"address family not supported\00", align 1
@.str.81 = private unnamed_addr constant [33 x i8] c"resource temporarily unavailable\00", align 1
@.str.82 = private unnamed_addr constant [18 x i8] c"temporary failure\00", align 1
@.str.83 = private unnamed_addr constant [19 x i8] c"bad ai_flags value\00", align 1
@.str.84 = private unnamed_addr constant [24 x i8] c"invalid value for hints\00", align 1
@.str.85 = private unnamed_addr constant [17 x i8] c"request canceled\00", align 1
@.str.86 = private unnamed_addr constant [18 x i8] c"permanent failure\00", align 1
@.str.87 = private unnamed_addr constant [24 x i8] c"ai_family not supported\00", align 1
@.str.88 = private unnamed_addr constant [14 x i8] c"out of memory\00", align 1
@.str.89 = private unnamed_addr constant [11 x i8] c"no address\00", align 1
@.str.90 = private unnamed_addr constant [24 x i8] c"unknown node or service\00", align 1
@.str.91 = private unnamed_addr constant [25 x i8] c"argument buffer overflow\00", align 1
@.str.92 = private unnamed_addr constant [29 x i8] c"resolved protocol is unknown\00", align 1
@.str.93 = private unnamed_addr constant [38 x i8] c"service not available for socket type\00", align 1
@.str.94 = private unnamed_addr constant [26 x i8] c"socket type not supported\00", align 1
@.str.95 = private unnamed_addr constant [31 x i8] c"connection already in progress\00", align 1
@.str.96 = private unnamed_addr constant [20 x i8] c"bad file descriptor\00", align 1
@.str.97 = private unnamed_addr constant [24 x i8] c"resource busy or locked\00", align 1
@.str.98 = private unnamed_addr constant [19 x i8] c"operation canceled\00", align 1
@.str.99 = private unnamed_addr constant [26 x i8] c"invalid Unicode character\00", align 1
@.str.100 = private unnamed_addr constant [33 x i8] c"software caused connection abort\00", align 1
@.str.101 = private unnamed_addr constant [19 x i8] c"connection refused\00", align 1
@.str.102 = private unnamed_addr constant [25 x i8] c"connection reset by peer\00", align 1
@.str.103 = private unnamed_addr constant [29 x i8] c"destination address required\00", align 1
@.str.104 = private unnamed_addr constant [20 x i8] c"file already exists\00", align 1
@.str.105 = private unnamed_addr constant [36 x i8] c"bad address in system call argument\00", align 1
@.str.106 = private unnamed_addr constant [15 x i8] c"file too large\00", align 1
@.str.107 = private unnamed_addr constant [20 x i8] c"host is unreachable\00", align 1
@.str.108 = private unnamed_addr constant [24 x i8] c"interrupted system call\00", align 1
@.str.109 = private unnamed_addr constant [17 x i8] c"invalid argument\00", align 1
@.str.110 = private unnamed_addr constant [10 x i8] c"i/o error\00", align 1
@.str.111 = private unnamed_addr constant [28 x i8] c"socket is already connected\00", align 1
@.str.112 = private unnamed_addr constant [33 x i8] c"illegal operation on a directory\00", align 1
@.str.113 = private unnamed_addr constant [36 x i8] c"too many symbolic links encountered\00", align 1
@.str.114 = private unnamed_addr constant [20 x i8] c"too many open files\00", align 1
@.str.115 = private unnamed_addr constant [17 x i8] c"message too long\00", align 1
@.str.116 = private unnamed_addr constant [14 x i8] c"name too long\00", align 1
@.str.117 = private unnamed_addr constant [16 x i8] c"network is down\00", align 1
@.str.118 = private unnamed_addr constant [23 x i8] c"network is unreachable\00", align 1
@.str.119 = private unnamed_addr constant [20 x i8] c"file table overflow\00", align 1
@.str.120 = private unnamed_addr constant [26 x i8] c"no buffer space available\00", align 1
@.str.121 = private unnamed_addr constant [15 x i8] c"no such device\00", align 1
@.str.122 = private unnamed_addr constant [26 x i8] c"no such file or directory\00", align 1
@.str.123 = private unnamed_addr constant [18 x i8] c"not enough memory\00", align 1
@.str.124 = private unnamed_addr constant [30 x i8] c"machine is not on the network\00", align 1
@.str.125 = private unnamed_addr constant [23 x i8] c"protocol not available\00", align 1
@.str.126 = private unnamed_addr constant [24 x i8] c"no space left on device\00", align 1
@.str.127 = private unnamed_addr constant [25 x i8] c"function not implemented\00", align 1
@.str.128 = private unnamed_addr constant [24 x i8] c"socket is not connected\00", align 1
@.str.129 = private unnamed_addr constant [16 x i8] c"not a directory\00", align 1
@.str.130 = private unnamed_addr constant [20 x i8] c"directory not empty\00", align 1
@.str.131 = private unnamed_addr constant [31 x i8] c"socket operation on non-socket\00", align 1
@.str.132 = private unnamed_addr constant [34 x i8] c"operation not supported on socket\00", align 1
@.str.133 = private unnamed_addr constant [24 x i8] c"operation not permitted\00", align 1
@.str.134 = private unnamed_addr constant [12 x i8] c"broken pipe\00", align 1
@.str.135 = private unnamed_addr constant [15 x i8] c"protocol error\00", align 1
@.str.136 = private unnamed_addr constant [23 x i8] c"protocol not supported\00", align 1
@.str.137 = private unnamed_addr constant [31 x i8] c"protocol wrong type for socket\00", align 1
@.str.138 = private unnamed_addr constant [17 x i8] c"result too large\00", align 1
@.str.139 = private unnamed_addr constant [22 x i8] c"read-only file system\00", align 1
@.str.140 = private unnamed_addr constant [46 x i8] c"cannot send after transport endpoint shutdown\00", align 1
@.str.141 = private unnamed_addr constant [13 x i8] c"invalid seek\00", align 1
@.str.142 = private unnamed_addr constant [16 x i8] c"no such process\00", align 1
@.str.143 = private unnamed_addr constant [21 x i8] c"connection timed out\00", align 1
@.str.144 = private unnamed_addr constant [18 x i8] c"text file is busy\00", align 1
@.str.145 = private unnamed_addr constant [32 x i8] c"cross-device link not permitted\00", align 1
@.str.146 = private unnamed_addr constant [14 x i8] c"unknown error\00", align 1
@.str.147 = private unnamed_addr constant [12 x i8] c"end of file\00", align 1
@.str.148 = private unnamed_addr constant [26 x i8] c"no such device or address\00", align 1
@.str.149 = private unnamed_addr constant [15 x i8] c"too many links\00", align 1
@.str.150 = private unnamed_addr constant [13 x i8] c"host is down\00", align 1
@.str.151 = private unnamed_addr constant [6 x i8] c"nbufs\00", align 1
@.str.152 = private unnamed_addr constant [68 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.c\00", align 1
@__PRETTY_FUNCTION__.uv_fs_scandir_next = private unnamed_addr constant [49 x i8] c"int uv_fs_scandir_next(uv_fs_t *, uv_dirent_t *)\00", align 1
@default_loop_ptr = internal global %struct.uv_loop_s* null, align 8
@default_loop_struct = internal global %struct.uv_loop_s zeroinitializer, align 8
@.str.153 = private unnamed_addr constant [9 x i8] c"err == 0\00", align 1
@__PRETTY_FUNCTION__.uv_loop_delete = private unnamed_addr constant [33 x i8] c"void uv_loop_delete(uv_loop_t *)\00", align 1
@.str.154 = private unnamed_addr constant [24 x i8] c"Unknown system error %d\00", align 1
@.str.155 = private unnamed_addr constant [21 x i8] c"Unknown system error\00", align 1
@.str.156 = private unnamed_addr constant [6 x i8] c"async\00", align 1
@.str.157 = private unnamed_addr constant [6 x i8] c"check\00", align 1
@.str.158 = private unnamed_addr constant [9 x i8] c"fs_event\00", align 1
@.str.159 = private unnamed_addr constant [8 x i8] c"fs_poll\00", align 1
@.str.160 = private unnamed_addr constant [7 x i8] c"handle\00", align 1
@.str.161 = private unnamed_addr constant [5 x i8] c"idle\00", align 1
@.str.162 = private unnamed_addr constant [5 x i8] c"pipe\00", align 1
@.str.163 = private unnamed_addr constant [5 x i8] c"poll\00", align 1
@.str.164 = private unnamed_addr constant [8 x i8] c"prepare\00", align 1
@.str.165 = private unnamed_addr constant [8 x i8] c"process\00", align 1
@.str.166 = private unnamed_addr constant [7 x i8] c"stream\00", align 1
@.str.167 = private unnamed_addr constant [4 x i8] c"tcp\00", align 1
@.str.168 = private unnamed_addr constant [6 x i8] c"timer\00", align 1
@.str.169 = private unnamed_addr constant [4 x i8] c"tty\00", align 1
@.str.170 = private unnamed_addr constant [4 x i8] c"udp\00", align 1
@.str.171 = private unnamed_addr constant [7 x i8] c"signal\00", align 1
@.str.172 = private unnamed_addr constant [10 x i8] c"<unknown>\00", align 1
@.str.173 = private unnamed_addr constant [18 x i8] c"[%c%c%c] %-8s %p\0A\00", align 1
@.str.174 = private unnamed_addr constant [3 x i8] c"R-\00", align 1
@.str.175 = private unnamed_addr constant [3 x i8] c"A-\00", align 1
@.str.176 = private unnamed_addr constant [3 x i8] c"I-\00", align 1

; Function Attrs: nounwind uwtable
define i8* @uv__strdup(i8* %s) #0 !dbg !387 {
entry:
  %retval = alloca i8*, align 8
  %s.addr = alloca i8*, align 8
  %len = alloca i64, align 8
  %m = alloca i8*, align 8
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !935, metadata !936), !dbg !937
  call void @llvm.dbg.declare(metadata i64* %len, metadata !938, metadata !936), !dbg !939
  %0 = load i8*, i8** %s.addr, align 8, !dbg !940
  %call = call i64 @strlen(i8* %0) #9, !dbg !941
  %add = add i64 %call, 1, !dbg !942
  store i64 %add, i64* %len, align 8, !dbg !939
  call void @llvm.dbg.declare(metadata i8** %m, metadata !943, metadata !936), !dbg !944
  %1 = load i64, i64* %len, align 8, !dbg !945
  %call1 = call i8* @uv__malloc(i64 %1), !dbg !946
  store i8* %call1, i8** %m, align 8, !dbg !944
  %2 = load i8*, i8** %m, align 8, !dbg !947
  %cmp = icmp eq i8* %2, null, !dbg !949
  br i1 %cmp, label %if.then, label %if.end, !dbg !950

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !951
  br label %return, !dbg !951

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %m, align 8, !dbg !952
  %4 = load i8*, i8** %s.addr, align 8, !dbg !953
  %5 = load i64, i64* %len, align 8, !dbg !954
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 %5, i32 1, i1 false), !dbg !955
  store i8* %3, i8** %retval, align 8, !dbg !956
  br label %return, !dbg !956

return:                                           ; preds = %if.end, %if.then
  %6 = load i8*, i8** %retval, align 8, !dbg !957
  ret i8* %6, !dbg !957
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: nounwind uwtable
define i8* @uv__malloc(i64 %size) #0 !dbg !396 {
entry:
  %size.addr = alloca i64, align 8
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !958, metadata !936), !dbg !959
  %0 = load i8* (i64)*, i8* (i64)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 0), align 8, !dbg !960
  %1 = load i64, i64* %size.addr, align 8, !dbg !961
  %call = call i8* %0(i64 %1), !dbg !962
  ret i8* %call, !dbg !963
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i8* @uv__strndup(i8* %s, i64 %n) #0 !dbg !393 {
entry:
  %retval = alloca i8*, align 8
  %s.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %m = alloca i8*, align 8
  %len = alloca i64, align 8
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !964, metadata !936), !dbg !965
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !966, metadata !936), !dbg !967
  call void @llvm.dbg.declare(metadata i8** %m, metadata !968, metadata !936), !dbg !969
  call void @llvm.dbg.declare(metadata i64* %len, metadata !970, metadata !936), !dbg !971
  %0 = load i8*, i8** %s.addr, align 8, !dbg !972
  %call = call i64 @strlen(i8* %0) #9, !dbg !973
  store i64 %call, i64* %len, align 8, !dbg !971
  %1 = load i64, i64* %n.addr, align 8, !dbg !974
  %2 = load i64, i64* %len, align 8, !dbg !976
  %cmp = icmp ult i64 %1, %2, !dbg !977
  br i1 %cmp, label %if.then, label %if.end, !dbg !978

if.then:                                          ; preds = %entry
  %3 = load i64, i64* %n.addr, align 8, !dbg !979
  store i64 %3, i64* %len, align 8, !dbg !980
  br label %if.end, !dbg !981

if.end:                                           ; preds = %if.then, %entry
  %4 = load i64, i64* %len, align 8, !dbg !982
  %add = add i64 %4, 1, !dbg !983
  %call1 = call i8* @uv__malloc(i64 %add), !dbg !984
  store i8* %call1, i8** %m, align 8, !dbg !985
  %5 = load i8*, i8** %m, align 8, !dbg !986
  %cmp2 = icmp eq i8* %5, null, !dbg !988
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !989

if.then3:                                         ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !990
  br label %return, !dbg !990

if.end4:                                          ; preds = %if.end
  %6 = load i64, i64* %len, align 8, !dbg !991
  %7 = load i8*, i8** %m, align 8, !dbg !992
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 %6, !dbg !992
  store i8 0, i8* %arrayidx, align 1, !dbg !993
  %8 = load i8*, i8** %m, align 8, !dbg !994
  %9 = load i8*, i8** %s.addr, align 8, !dbg !995
  %10 = load i64, i64* %len, align 8, !dbg !996
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* %9, i64 %10, i32 1, i1 false), !dbg !997
  store i8* %8, i8** %retval, align 8, !dbg !998
  br label %return, !dbg !998

return:                                           ; preds = %if.end4, %if.then3
  %11 = load i8*, i8** %retval, align 8, !dbg !999
  ret i8* %11, !dbg !999
}

; Function Attrs: nounwind uwtable
define void @uv__free(i8* %ptr) #0 !dbg !399 {
entry:
  %ptr.addr = alloca i8*, align 8
  %saved_errno = alloca i32, align 4
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1000, metadata !936), !dbg !1001
  call void @llvm.dbg.declare(metadata i32* %saved_errno, metadata !1002, metadata !936), !dbg !1003
  %call = call i32* @__errno_location() #1, !dbg !1004
  %0 = load i32, i32* %call, align 4, !dbg !1004
  store i32 %0, i32* %saved_errno, align 4, !dbg !1005
  %1 = load void (i8*)*, void (i8*)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 3), align 8, !dbg !1006
  %2 = load i8*, i8** %ptr.addr, align 8, !dbg !1007
  call void %1(i8* %2), !dbg !1008
  %3 = load i32, i32* %saved_errno, align 4, !dbg !1009
  %call1 = call i32* @__errno_location() #1, !dbg !1010
  store i32 %3, i32* %call1, align 4, !dbg !1011
  ret void, !dbg !1012
}

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind uwtable
define i8* @uv__calloc(i64 %count, i64 %size) #0 !dbg !402 {
entry:
  %count.addr = alloca i64, align 8
  %size.addr = alloca i64, align 8
  store i64 %count, i64* %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %count.addr, metadata !1013, metadata !936), !dbg !1014
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1015, metadata !936), !dbg !1016
  %0 = load i8* (i64, i64)*, i8* (i64, i64)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 2), align 8, !dbg !1017
  %1 = load i64, i64* %count.addr, align 8, !dbg !1018
  %2 = load i64, i64* %size.addr, align 8, !dbg !1019
  %call = call i8* %0(i64 %1, i64 %2), !dbg !1020
  ret i8* %call, !dbg !1021
}

; Function Attrs: nounwind uwtable
define i8* @uv__realloc(i8* %ptr, i64 %size) #0 !dbg !405 {
entry:
  %ptr.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1022, metadata !936), !dbg !1023
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1024, metadata !936), !dbg !1025
  %0 = load i8* (i8*, i64)*, i8* (i8*, i64)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 1), align 8, !dbg !1026
  %1 = load i8*, i8** %ptr.addr, align 8, !dbg !1027
  %2 = load i64, i64* %size.addr, align 8, !dbg !1028
  %call = call i8* %0(i8* %1, i64 %2), !dbg !1029
  ret i8* %call, !dbg !1030
}

; Function Attrs: nounwind uwtable
define i32 @uv_replace_allocator(i8* (i64)* %malloc_func, i8* (i8*, i64)* %realloc_func, i8* (i64, i64)* %calloc_func, void (i8*)* %free_func) #0 !dbg !408 {
entry:
  %retval = alloca i32, align 4
  %malloc_func.addr = alloca i8* (i64)*, align 8
  %realloc_func.addr = alloca i8* (i8*, i64)*, align 8
  %calloc_func.addr = alloca i8* (i64, i64)*, align 8
  %free_func.addr = alloca void (i8*)*, align 8
  store i8* (i64)* %malloc_func, i8* (i64)** %malloc_func.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i64)** %malloc_func.addr, metadata !1031, metadata !936), !dbg !1032
  store i8* (i8*, i64)* %realloc_func, i8* (i8*, i64)** %realloc_func.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i8*, i64)** %realloc_func.addr, metadata !1033, metadata !936), !dbg !1034
  store i8* (i64, i64)* %calloc_func, i8* (i64, i64)** %calloc_func.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i64, i64)** %calloc_func.addr, metadata !1035, metadata !936), !dbg !1036
  store void (i8*)* %free_func, void (i8*)** %free_func.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %free_func.addr, metadata !1037, metadata !936), !dbg !1038
  %0 = load i8* (i64)*, i8* (i64)** %malloc_func.addr, align 8, !dbg !1039
  %cmp = icmp eq i8* (i64)* %0, null, !dbg !1041
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1042

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8* (i8*, i64)*, i8* (i8*, i64)** %realloc_func.addr, align 8, !dbg !1043
  %cmp1 = icmp eq i8* (i8*, i64)* %1, null, !dbg !1045
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !1046

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i8* (i64, i64)*, i8* (i64, i64)** %calloc_func.addr, align 8, !dbg !1047
  %cmp3 = icmp eq i8* (i64, i64)* %2, null, !dbg !1048
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !1049

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load void (i8*)*, void (i8*)** %free_func.addr, align 8, !dbg !1050
  %cmp5 = icmp eq void (i8*)* %3, null, !dbg !1051
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1052

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1054
  br label %return, !dbg !1054

if.end:                                           ; preds = %lor.lhs.false4
  %4 = load i8* (i64)*, i8* (i64)** %malloc_func.addr, align 8, !dbg !1056
  store i8* (i64)* %4, i8* (i64)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 0), align 8, !dbg !1057
  %5 = load i8* (i8*, i64)*, i8* (i8*, i64)** %realloc_func.addr, align 8, !dbg !1058
  store i8* (i8*, i64)* %5, i8* (i8*, i64)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 1), align 8, !dbg !1059
  %6 = load i8* (i64, i64)*, i8* (i64, i64)** %calloc_func.addr, align 8, !dbg !1060
  store i8* (i64, i64)* %6, i8* (i64, i64)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 2), align 8, !dbg !1061
  %7 = load void (i8*)*, void (i8*)** %free_func.addr, align 8, !dbg !1062
  store void (i8*)* %7, void (i8*)** getelementptr inbounds (%struct.uv__allocator_t, %struct.uv__allocator_t* @uv__allocator, i32 0, i32 3), align 8, !dbg !1063
  store i32 0, i32* %retval, align 4, !dbg !1064
  br label %return, !dbg !1064

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1065
  ret i32 %8, !dbg !1065
}

; Function Attrs: nounwind uwtable
define i64 @uv_handle_size(i32 %type) #0 !dbg !419 {
entry:
  %retval = alloca i64, align 8
  %type.addr = alloca i32, align 4
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1066, metadata !936), !dbg !1067
  %0 = load i32, i32* %type.addr, align 4, !dbg !1068
  switch i32 %0, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb1
    i32 3, label %sw.bb2
    i32 4, label %sw.bb3
    i32 5, label %sw.bb4
    i32 6, label %sw.bb5
    i32 7, label %sw.bb6
    i32 8, label %sw.bb7
    i32 9, label %sw.bb8
    i32 10, label %sw.bb9
    i32 11, label %sw.bb10
    i32 12, label %sw.bb11
    i32 13, label %sw.bb12
    i32 14, label %sw.bb13
    i32 15, label %sw.bb14
    i32 16, label %sw.bb15
  ], !dbg !1069

sw.bb:                                            ; preds = %entry
  store i64 128, i64* %retval, align 8, !dbg !1070
  br label %return, !dbg !1070

sw.bb1:                                           ; preds = %entry
  store i64 120, i64* %retval, align 8, !dbg !1072
  br label %return, !dbg !1072

sw.bb2:                                           ; preds = %entry
  store i64 136, i64* %retval, align 8, !dbg !1074
  br label %return, !dbg !1074

sw.bb3:                                           ; preds = %entry
  store i64 104, i64* %retval, align 8, !dbg !1076
  br label %return, !dbg !1076

sw.bb4:                                           ; preds = %entry
  store i64 96, i64* %retval, align 8, !dbg !1078
  br label %return, !dbg !1078

sw.bb5:                                           ; preds = %entry
  store i64 120, i64* %retval, align 8, !dbg !1080
  br label %return, !dbg !1080

sw.bb6:                                           ; preds = %entry
  store i64 264, i64* %retval, align 8, !dbg !1082
  br label %return, !dbg !1082

sw.bb7:                                           ; preds = %entry
  store i64 160, i64* %retval, align 8, !dbg !1084
  br label %return, !dbg !1084

sw.bb8:                                           ; preds = %entry
  store i64 120, i64* %retval, align 8, !dbg !1086
  br label %return, !dbg !1086

sw.bb9:                                           ; preds = %entry
  store i64 136, i64* %retval, align 8, !dbg !1088
  br label %return, !dbg !1088

sw.bb10:                                          ; preds = %entry
  store i64 248, i64* %retval, align 8, !dbg !1090
  br label %return, !dbg !1090

sw.bb11:                                          ; preds = %entry
  store i64 248, i64* %retval, align 8, !dbg !1092
  br label %return, !dbg !1092

sw.bb12:                                          ; preds = %entry
  store i64 152, i64* %retval, align 8, !dbg !1094
  br label %return, !dbg !1094

sw.bb13:                                          ; preds = %entry
  store i64 312, i64* %retval, align 8, !dbg !1096
  br label %return, !dbg !1096

sw.bb14:                                          ; preds = %entry
  store i64 216, i64* %retval, align 8, !dbg !1098
  br label %return, !dbg !1098

sw.bb15:                                          ; preds = %entry
  store i64 152, i64* %retval, align 8, !dbg !1100
  br label %return, !dbg !1100

sw.default:                                       ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !1102
  br label %return, !dbg !1102

return:                                           ; preds = %sw.default, %sw.bb15, %sw.bb14, %sw.bb13, %sw.bb12, %sw.bb11, %sw.bb10, %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %1 = load i64, i64* %retval, align 8, !dbg !1103
  ret i64 %1, !dbg !1103
}

; Function Attrs: nounwind uwtable
define i64 @uv_req_size(i32 %type) #0 !dbg !422 {
entry:
  %retval = alloca i64, align 8
  %type.addr = alloca i32, align 4
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1104, metadata !936), !dbg !1105
  %0 = load i32, i32* %type.addr, align 4, !dbg !1106
  switch i32 %0, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb1
    i32 3, label %sw.bb2
    i32 4, label %sw.bb3
    i32 5, label %sw.bb4
    i32 6, label %sw.bb5
    i32 7, label %sw.bb6
    i32 8, label %sw.bb7
    i32 9, label %sw.bb8
  ], !dbg !1107

sw.bb:                                            ; preds = %entry
  store i64 64, i64* %retval, align 8, !dbg !1108
  br label %return, !dbg !1108

sw.bb1:                                           ; preds = %entry
  store i64 96, i64* %retval, align 8, !dbg !1110
  br label %return, !dbg !1110

sw.bb2:                                           ; preds = %entry
  store i64 192, i64* %retval, align 8, !dbg !1112
  br label %return, !dbg !1112

sw.bb3:                                           ; preds = %entry
  store i64 80, i64* %retval, align 8, !dbg !1114
  br label %return, !dbg !1114

sw.bb4:                                           ; preds = %entry
  store i64 320, i64* %retval, align 8, !dbg !1116
  br label %return, !dbg !1116

sw.bb5:                                           ; preds = %entry
  store i64 440, i64* %retval, align 8, !dbg !1118
  br label %return, !dbg !1118

sw.bb6:                                           ; preds = %entry
  store i64 128, i64* %retval, align 8, !dbg !1120
  br label %return, !dbg !1120

sw.bb7:                                           ; preds = %entry
  store i64 160, i64* %retval, align 8, !dbg !1122
  br label %return, !dbg !1122

sw.bb8:                                           ; preds = %entry
  store i64 1320, i64* %retval, align 8, !dbg !1124
  br label %return, !dbg !1124

sw.default:                                       ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !1126
  br label %return, !dbg !1126

return:                                           ; preds = %sw.default, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %1 = load i64, i64* %retval, align 8, !dbg !1127
  ret i64 %1, !dbg !1127
}

; Function Attrs: nounwind uwtable
define i64 @uv_loop_size() #0 !dbg !426 {
entry:
  ret i64 848, !dbg !1128
}

; Function Attrs: nounwind uwtable
define { i8*, i64 } @uv_buf_init(i8* %base, i32 %len) #0 !dbg !429 {
entry:
  %retval = alloca %struct.uv_buf_t, align 8
  %base.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %buf = alloca %struct.uv_buf_t, align 8
  store i8* %base, i8** %base.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %base.addr, metadata !1129, metadata !936), !dbg !1130
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !1131, metadata !936), !dbg !1132
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t* %buf, metadata !1133, metadata !936), !dbg !1134
  %0 = load i8*, i8** %base.addr, align 8, !dbg !1135
  %base1 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 0, !dbg !1136
  store i8* %0, i8** %base1, align 8, !dbg !1137
  %1 = load i32, i32* %len.addr, align 4, !dbg !1138
  %conv = zext i32 %1 to i64, !dbg !1138
  %len2 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 1, !dbg !1139
  store i64 %conv, i64* %len2, align 8, !dbg !1140
  %2 = bitcast %struct.uv_buf_t* %retval to i8*, !dbg !1141
  %3 = bitcast %struct.uv_buf_t* %buf to i8*, !dbg !1141
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %2, i8* %3, i64 16, i32 8, i1 false), !dbg !1141
  %4 = bitcast %struct.uv_buf_t* %retval to { i8*, i64 }*, !dbg !1142
  %5 = load { i8*, i64 }, { i8*, i64 }* %4, align 8, !dbg !1142
  ret { i8*, i64 } %5, !dbg !1142
}

; Function Attrs: nounwind uwtable
define i8* @uv_err_name(i32 %err) #0 !dbg !437 {
entry:
  %retval = alloca i8*, align 8
  %err.addr = alloca i32, align 4
  store i32 %err, i32* %err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %err.addr, metadata !1143, metadata !936), !dbg !1144
  %0 = load i32, i32* %err.addr, align 4, !dbg !1145
  switch i32 %0, label %sw.epilog [
    i32 -7, label %sw.bb
    i32 -13, label %sw.bb1
    i32 -98, label %sw.bb2
    i32 -99, label %sw.bb3
    i32 -97, label %sw.bb4
    i32 -11, label %sw.bb5
    i32 -3000, label %sw.bb6
    i32 -3001, label %sw.bb7
    i32 -3002, label %sw.bb8
    i32 -3013, label %sw.bb9
    i32 -3003, label %sw.bb10
    i32 -3004, label %sw.bb11
    i32 -3005, label %sw.bb12
    i32 -3006, label %sw.bb13
    i32 -3007, label %sw.bb14
    i32 -3008, label %sw.bb15
    i32 -3009, label %sw.bb16
    i32 -3014, label %sw.bb17
    i32 -3010, label %sw.bb18
    i32 -3011, label %sw.bb19
    i32 -114, label %sw.bb20
    i32 -9, label %sw.bb21
    i32 -16, label %sw.bb22
    i32 -125, label %sw.bb23
    i32 -4080, label %sw.bb24
    i32 -103, label %sw.bb25
    i32 -111, label %sw.bb26
    i32 -104, label %sw.bb27
    i32 -89, label %sw.bb28
    i32 -17, label %sw.bb29
    i32 -14, label %sw.bb30
    i32 -27, label %sw.bb31
    i32 -113, label %sw.bb32
    i32 -4, label %sw.bb33
    i32 -22, label %sw.bb34
    i32 -5, label %sw.bb35
    i32 -106, label %sw.bb36
    i32 -21, label %sw.bb37
    i32 -40, label %sw.bb38
    i32 -24, label %sw.bb39
    i32 -90, label %sw.bb40
    i32 -36, label %sw.bb41
    i32 -100, label %sw.bb42
    i32 -101, label %sw.bb43
    i32 -23, label %sw.bb44
    i32 -105, label %sw.bb45
    i32 -19, label %sw.bb46
    i32 -2, label %sw.bb47
    i32 -12, label %sw.bb48
    i32 -64, label %sw.bb49
    i32 -92, label %sw.bb50
    i32 -28, label %sw.bb51
    i32 -38, label %sw.bb52
    i32 -107, label %sw.bb53
    i32 -20, label %sw.bb54
    i32 -39, label %sw.bb55
    i32 -88, label %sw.bb56
    i32 -95, label %sw.bb57
    i32 -1, label %sw.bb58
    i32 -32, label %sw.bb59
    i32 -71, label %sw.bb60
    i32 -93, label %sw.bb61
    i32 -91, label %sw.bb62
    i32 -34, label %sw.bb63
    i32 -30, label %sw.bb64
    i32 -108, label %sw.bb65
    i32 -29, label %sw.bb66
    i32 -3, label %sw.bb67
    i32 -110, label %sw.bb68
    i32 -26, label %sw.bb69
    i32 -18, label %sw.bb70
    i32 -4094, label %sw.bb71
    i32 -4095, label %sw.bb72
    i32 -6, label %sw.bb73
    i32 -31, label %sw.bb74
    i32 -112, label %sw.bb75
  ], !dbg !1146

sw.bb:                                            ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i8** %retval, align 8, !dbg !1147
  br label %return, !dbg !1147

sw.bb1:                                           ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i8** %retval, align 8, !dbg !1149
  br label %return, !dbg !1149

sw.bb2:                                           ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i32 0, i32 0), i8** %retval, align 8, !dbg !1151
  br label %return, !dbg !1151

sw.bb3:                                           ; preds = %entry
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i32 0, i32 0), i8** %retval, align 8, !dbg !1153
  br label %return, !dbg !1153

sw.bb4:                                           ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.4, i32 0, i32 0), i8** %retval, align 8, !dbg !1155
  br label %return, !dbg !1155

sw.bb5:                                           ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.5, i32 0, i32 0), i8** %retval, align 8, !dbg !1157
  br label %return, !dbg !1157

sw.bb6:                                           ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.6, i32 0, i32 0), i8** %retval, align 8, !dbg !1159
  br label %return, !dbg !1159

sw.bb7:                                           ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i32 0, i32 0), i8** %retval, align 8, !dbg !1161
  br label %return, !dbg !1161

sw.bb8:                                           ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.8, i32 0, i32 0), i8** %retval, align 8, !dbg !1163
  br label %return, !dbg !1163

sw.bb9:                                           ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.9, i32 0, i32 0), i8** %retval, align 8, !dbg !1165
  br label %return, !dbg !1165

sw.bb10:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.10, i32 0, i32 0), i8** %retval, align 8, !dbg !1167
  br label %return, !dbg !1167

sw.bb11:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i8** %retval, align 8, !dbg !1169
  br label %return, !dbg !1169

sw.bb12:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.12, i32 0, i32 0), i8** %retval, align 8, !dbg !1171
  br label %return, !dbg !1171

sw.bb13:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.13, i32 0, i32 0), i8** %retval, align 8, !dbg !1173
  br label %return, !dbg !1173

sw.bb14:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.14, i32 0, i32 0), i8** %retval, align 8, !dbg !1175
  br label %return, !dbg !1175

sw.bb15:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.15, i32 0, i32 0), i8** %retval, align 8, !dbg !1177
  br label %return, !dbg !1177

sw.bb16:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.16, i32 0, i32 0), i8** %retval, align 8, !dbg !1179
  br label %return, !dbg !1179

sw.bb17:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.17, i32 0, i32 0), i8** %retval, align 8, !dbg !1181
  br label %return, !dbg !1181

sw.bb18:                                          ; preds = %entry
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.18, i32 0, i32 0), i8** %retval, align 8, !dbg !1183
  br label %return, !dbg !1183

sw.bb19:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.19, i32 0, i32 0), i8** %retval, align 8, !dbg !1185
  br label %return, !dbg !1185

sw.bb20:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.20, i32 0, i32 0), i8** %retval, align 8, !dbg !1187
  br label %return, !dbg !1187

sw.bb21:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.21, i32 0, i32 0), i8** %retval, align 8, !dbg !1189
  br label %return, !dbg !1189

sw.bb22:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.22, i32 0, i32 0), i8** %retval, align 8, !dbg !1191
  br label %return, !dbg !1191

sw.bb23:                                          ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.23, i32 0, i32 0), i8** %retval, align 8, !dbg !1193
  br label %return, !dbg !1193

sw.bb24:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.24, i32 0, i32 0), i8** %retval, align 8, !dbg !1195
  br label %return, !dbg !1195

sw.bb25:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.25, i32 0, i32 0), i8** %retval, align 8, !dbg !1197
  br label %return, !dbg !1197

sw.bb26:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.26, i32 0, i32 0), i8** %retval, align 8, !dbg !1199
  br label %return, !dbg !1199

sw.bb27:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.27, i32 0, i32 0), i8** %retval, align 8, !dbg !1201
  br label %return, !dbg !1201

sw.bb28:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.28, i32 0, i32 0), i8** %retval, align 8, !dbg !1203
  br label %return, !dbg !1203

sw.bb29:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.29, i32 0, i32 0), i8** %retval, align 8, !dbg !1205
  br label %return, !dbg !1205

sw.bb30:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.30, i32 0, i32 0), i8** %retval, align 8, !dbg !1207
  br label %return, !dbg !1207

sw.bb31:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.31, i32 0, i32 0), i8** %retval, align 8, !dbg !1209
  br label %return, !dbg !1209

sw.bb32:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.32, i32 0, i32 0), i8** %retval, align 8, !dbg !1211
  br label %return, !dbg !1211

sw.bb33:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.33, i32 0, i32 0), i8** %retval, align 8, !dbg !1213
  br label %return, !dbg !1213

sw.bb34:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.34, i32 0, i32 0), i8** %retval, align 8, !dbg !1215
  br label %return, !dbg !1215

sw.bb35:                                          ; preds = %entry
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.35, i32 0, i32 0), i8** %retval, align 8, !dbg !1217
  br label %return, !dbg !1217

sw.bb36:                                          ; preds = %entry
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.36, i32 0, i32 0), i8** %retval, align 8, !dbg !1219
  br label %return, !dbg !1219

sw.bb37:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.37, i32 0, i32 0), i8** %retval, align 8, !dbg !1221
  br label %return, !dbg !1221

sw.bb38:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.38, i32 0, i32 0), i8** %retval, align 8, !dbg !1223
  br label %return, !dbg !1223

sw.bb39:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.39, i32 0, i32 0), i8** %retval, align 8, !dbg !1225
  br label %return, !dbg !1225

sw.bb40:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.40, i32 0, i32 0), i8** %retval, align 8, !dbg !1227
  br label %return, !dbg !1227

sw.bb41:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.41, i32 0, i32 0), i8** %retval, align 8, !dbg !1229
  br label %return, !dbg !1229

sw.bb42:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.42, i32 0, i32 0), i8** %retval, align 8, !dbg !1231
  br label %return, !dbg !1231

sw.bb43:                                          ; preds = %entry
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.43, i32 0, i32 0), i8** %retval, align 8, !dbg !1233
  br label %return, !dbg !1233

sw.bb44:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.44, i32 0, i32 0), i8** %retval, align 8, !dbg !1235
  br label %return, !dbg !1235

sw.bb45:                                          ; preds = %entry
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.45, i32 0, i32 0), i8** %retval, align 8, !dbg !1237
  br label %return, !dbg !1237

sw.bb46:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.46, i32 0, i32 0), i8** %retval, align 8, !dbg !1239
  br label %return, !dbg !1239

sw.bb47:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.47, i32 0, i32 0), i8** %retval, align 8, !dbg !1241
  br label %return, !dbg !1241

sw.bb48:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.48, i32 0, i32 0), i8** %retval, align 8, !dbg !1243
  br label %return, !dbg !1243

sw.bb49:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.49, i32 0, i32 0), i8** %retval, align 8, !dbg !1245
  br label %return, !dbg !1245

sw.bb50:                                          ; preds = %entry
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.50, i32 0, i32 0), i8** %retval, align 8, !dbg !1247
  br label %return, !dbg !1247

sw.bb51:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.51, i32 0, i32 0), i8** %retval, align 8, !dbg !1249
  br label %return, !dbg !1249

sw.bb52:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.52, i32 0, i32 0), i8** %retval, align 8, !dbg !1251
  br label %return, !dbg !1251

sw.bb53:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.53, i32 0, i32 0), i8** %retval, align 8, !dbg !1253
  br label %return, !dbg !1253

sw.bb54:                                          ; preds = %entry
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.54, i32 0, i32 0), i8** %retval, align 8, !dbg !1255
  br label %return, !dbg !1255

sw.bb55:                                          ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.55, i32 0, i32 0), i8** %retval, align 8, !dbg !1257
  br label %return, !dbg !1257

sw.bb56:                                          ; preds = %entry
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.56, i32 0, i32 0), i8** %retval, align 8, !dbg !1259
  br label %return, !dbg !1259

sw.bb57:                                          ; preds = %entry
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.57, i32 0, i32 0), i8** %retval, align 8, !dbg !1261
  br label %return, !dbg !1261

sw.bb58:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.58, i32 0, i32 0), i8** %retval, align 8, !dbg !1263
  br label %return, !dbg !1263

sw.bb59:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.59, i32 0, i32 0), i8** %retval, align 8, !dbg !1265
  br label %return, !dbg !1265

sw.bb60:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.60, i32 0, i32 0), i8** %retval, align 8, !dbg !1267
  br label %return, !dbg !1267

sw.bb61:                                          ; preds = %entry
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.61, i32 0, i32 0), i8** %retval, align 8, !dbg !1269
  br label %return, !dbg !1269

sw.bb62:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.62, i32 0, i32 0), i8** %retval, align 8, !dbg !1271
  br label %return, !dbg !1271

sw.bb63:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.63, i32 0, i32 0), i8** %retval, align 8, !dbg !1273
  br label %return, !dbg !1273

sw.bb64:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.64, i32 0, i32 0), i8** %retval, align 8, !dbg !1275
  br label %return, !dbg !1275

sw.bb65:                                          ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.65, i32 0, i32 0), i8** %retval, align 8, !dbg !1277
  br label %return, !dbg !1277

sw.bb66:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.66, i32 0, i32 0), i8** %retval, align 8, !dbg !1279
  br label %return, !dbg !1279

sw.bb67:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.67, i32 0, i32 0), i8** %retval, align 8, !dbg !1281
  br label %return, !dbg !1281

sw.bb68:                                          ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.68, i32 0, i32 0), i8** %retval, align 8, !dbg !1283
  br label %return, !dbg !1283

sw.bb69:                                          ; preds = %entry
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.69, i32 0, i32 0), i8** %retval, align 8, !dbg !1285
  br label %return, !dbg !1285

sw.bb70:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.70, i32 0, i32 0), i8** %retval, align 8, !dbg !1287
  br label %return, !dbg !1287

sw.bb71:                                          ; preds = %entry
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.71, i32 0, i32 0), i8** %retval, align 8, !dbg !1289
  br label %return, !dbg !1289

sw.bb72:                                          ; preds = %entry
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.72, i32 0, i32 0), i8** %retval, align 8, !dbg !1291
  br label %return, !dbg !1291

sw.bb73:                                          ; preds = %entry
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.73, i32 0, i32 0), i8** %retval, align 8, !dbg !1293
  br label %return, !dbg !1293

sw.bb74:                                          ; preds = %entry
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.74, i32 0, i32 0), i8** %retval, align 8, !dbg !1295
  br label %return, !dbg !1295

sw.bb75:                                          ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.75, i32 0, i32 0), i8** %retval, align 8, !dbg !1297
  br label %return, !dbg !1297

sw.epilog:                                        ; preds = %entry
  %1 = load i32, i32* %err.addr, align 4, !dbg !1299
  %call = call i8* @uv__unknown_err_code(i32 %1), !dbg !1300
  store i8* %call, i8** %retval, align 8, !dbg !1301
  br label %return, !dbg !1301

return:                                           ; preds = %sw.epilog, %sw.bb75, %sw.bb74, %sw.bb73, %sw.bb72, %sw.bb71, %sw.bb70, %sw.bb69, %sw.bb68, %sw.bb67, %sw.bb66, %sw.bb65, %sw.bb64, %sw.bb63, %sw.bb62, %sw.bb61, %sw.bb60, %sw.bb59, %sw.bb58, %sw.bb57, %sw.bb56, %sw.bb55, %sw.bb54, %sw.bb53, %sw.bb52, %sw.bb51, %sw.bb50, %sw.bb49, %sw.bb48, %sw.bb47, %sw.bb46, %sw.bb45, %sw.bb44, %sw.bb43, %sw.bb42, %sw.bb41, %sw.bb40, %sw.bb39, %sw.bb38, %sw.bb37, %sw.bb36, %sw.bb35, %sw.bb34, %sw.bb33, %sw.bb32, %sw.bb31, %sw.bb30, %sw.bb29, %sw.bb28, %sw.bb27, %sw.bb26, %sw.bb25, %sw.bb24, %sw.bb23, %sw.bb22, %sw.bb21, %sw.bb20, %sw.bb19, %sw.bb18, %sw.bb17, %sw.bb16, %sw.bb15, %sw.bb14, %sw.bb13, %sw.bb12, %sw.bb11, %sw.bb10, %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %2 = load i8*, i8** %retval, align 8, !dbg !1302
  ret i8* %2, !dbg !1302
}

; Function Attrs: nounwind uwtable
define internal i8* @uv__unknown_err_code(i32 %err) #0 !dbg !913 {
entry:
  %err.addr = alloca i32, align 4
  %buf = alloca [32 x i8], align 16
  %copy = alloca i8*, align 8
  store i32 %err, i32* %err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %err.addr, metadata !1303, metadata !936), !dbg !1304
  call void @llvm.dbg.declare(metadata [32 x i8]* %buf, metadata !1305, metadata !936), !dbg !1309
  call void @llvm.dbg.declare(metadata i8** %copy, metadata !1310, metadata !936), !dbg !1311
  %arraydecay = getelementptr inbounds [32 x i8], [32 x i8]* %buf, i32 0, i32 0, !dbg !1312
  %0 = load i32, i32* %err.addr, align 4, !dbg !1313
  %call = call i32 (i8*, i64, i8*, ...) @snprintf(i8* %arraydecay, i64 32, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.154, i32 0, i32 0), i32 %0) #8, !dbg !1314
  %arraydecay1 = getelementptr inbounds [32 x i8], [32 x i8]* %buf, i32 0, i32 0, !dbg !1315
  %call2 = call i8* @uv__strdup(i8* %arraydecay1), !dbg !1316
  store i8* %call2, i8** %copy, align 8, !dbg !1317
  %1 = load i8*, i8** %copy, align 8, !dbg !1318
  %cmp = icmp ne i8* %1, null, !dbg !1319
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1318

cond.true:                                        ; preds = %entry
  %2 = load i8*, i8** %copy, align 8, !dbg !1320
  br label %cond.end, !dbg !1322

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1323

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %2, %cond.true ], [ getelementptr inbounds ([21 x i8], [21 x i8]* @.str.155, i32 0, i32 0), %cond.false ], !dbg !1325
  ret i8* %cond, !dbg !1327
}

; Function Attrs: nounwind uwtable
define i8* @uv_strerror(i32 %err) #0 !dbg !440 {
entry:
  %retval = alloca i8*, align 8
  %err.addr = alloca i32, align 4
  store i32 %err, i32* %err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %err.addr, metadata !1328, metadata !936), !dbg !1329
  %0 = load i32, i32* %err.addr, align 4, !dbg !1330
  switch i32 %0, label %sw.epilog [
    i32 -7, label %sw.bb
    i32 -13, label %sw.bb1
    i32 -98, label %sw.bb2
    i32 -99, label %sw.bb3
    i32 -97, label %sw.bb4
    i32 -11, label %sw.bb5
    i32 -3000, label %sw.bb6
    i32 -3001, label %sw.bb7
    i32 -3002, label %sw.bb8
    i32 -3013, label %sw.bb9
    i32 -3003, label %sw.bb10
    i32 -3004, label %sw.bb11
    i32 -3005, label %sw.bb12
    i32 -3006, label %sw.bb13
    i32 -3007, label %sw.bb14
    i32 -3008, label %sw.bb15
    i32 -3009, label %sw.bb16
    i32 -3014, label %sw.bb17
    i32 -3010, label %sw.bb18
    i32 -3011, label %sw.bb19
    i32 -114, label %sw.bb20
    i32 -9, label %sw.bb21
    i32 -16, label %sw.bb22
    i32 -125, label %sw.bb23
    i32 -4080, label %sw.bb24
    i32 -103, label %sw.bb25
    i32 -111, label %sw.bb26
    i32 -104, label %sw.bb27
    i32 -89, label %sw.bb28
    i32 -17, label %sw.bb29
    i32 -14, label %sw.bb30
    i32 -27, label %sw.bb31
    i32 -113, label %sw.bb32
    i32 -4, label %sw.bb33
    i32 -22, label %sw.bb34
    i32 -5, label %sw.bb35
    i32 -106, label %sw.bb36
    i32 -21, label %sw.bb37
    i32 -40, label %sw.bb38
    i32 -24, label %sw.bb39
    i32 -90, label %sw.bb40
    i32 -36, label %sw.bb41
    i32 -100, label %sw.bb42
    i32 -101, label %sw.bb43
    i32 -23, label %sw.bb44
    i32 -105, label %sw.bb45
    i32 -19, label %sw.bb46
    i32 -2, label %sw.bb47
    i32 -12, label %sw.bb48
    i32 -64, label %sw.bb49
    i32 -92, label %sw.bb50
    i32 -28, label %sw.bb51
    i32 -38, label %sw.bb52
    i32 -107, label %sw.bb53
    i32 -20, label %sw.bb54
    i32 -39, label %sw.bb55
    i32 -88, label %sw.bb56
    i32 -95, label %sw.bb57
    i32 -1, label %sw.bb58
    i32 -32, label %sw.bb59
    i32 -71, label %sw.bb60
    i32 -93, label %sw.bb61
    i32 -91, label %sw.bb62
    i32 -34, label %sw.bb63
    i32 -30, label %sw.bb64
    i32 -108, label %sw.bb65
    i32 -29, label %sw.bb66
    i32 -3, label %sw.bb67
    i32 -110, label %sw.bb68
    i32 -26, label %sw.bb69
    i32 -18, label %sw.bb70
    i32 -4094, label %sw.bb71
    i32 -4095, label %sw.bb72
    i32 -6, label %sw.bb73
    i32 -31, label %sw.bb74
    i32 -112, label %sw.bb75
  ], !dbg !1331

sw.bb:                                            ; preds = %entry
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.76, i32 0, i32 0), i8** %retval, align 8, !dbg !1332
  br label %return, !dbg !1332

sw.bb1:                                           ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.77, i32 0, i32 0), i8** %retval, align 8, !dbg !1334
  br label %return, !dbg !1334

sw.bb2:                                           ; preds = %entry
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.78, i32 0, i32 0), i8** %retval, align 8, !dbg !1336
  br label %return, !dbg !1336

sw.bb3:                                           ; preds = %entry
  store i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.79, i32 0, i32 0), i8** %retval, align 8, !dbg !1338
  br label %return, !dbg !1338

sw.bb4:                                           ; preds = %entry
  store i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.80, i32 0, i32 0), i8** %retval, align 8, !dbg !1340
  br label %return, !dbg !1340

sw.bb5:                                           ; preds = %entry
  store i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.81, i32 0, i32 0), i8** %retval, align 8, !dbg !1342
  br label %return, !dbg !1342

sw.bb6:                                           ; preds = %entry
  store i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.80, i32 0, i32 0), i8** %retval, align 8, !dbg !1344
  br label %return, !dbg !1344

sw.bb7:                                           ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.82, i32 0, i32 0), i8** %retval, align 8, !dbg !1346
  br label %return, !dbg !1346

sw.bb8:                                           ; preds = %entry
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.83, i32 0, i32 0), i8** %retval, align 8, !dbg !1348
  br label %return, !dbg !1348

sw.bb9:                                           ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.84, i32 0, i32 0), i8** %retval, align 8, !dbg !1350
  br label %return, !dbg !1350

sw.bb10:                                          ; preds = %entry
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.85, i32 0, i32 0), i8** %retval, align 8, !dbg !1352
  br label %return, !dbg !1352

sw.bb11:                                          ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.86, i32 0, i32 0), i8** %retval, align 8, !dbg !1354
  br label %return, !dbg !1354

sw.bb12:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.87, i32 0, i32 0), i8** %retval, align 8, !dbg !1356
  br label %return, !dbg !1356

sw.bb13:                                          ; preds = %entry
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.88, i32 0, i32 0), i8** %retval, align 8, !dbg !1358
  br label %return, !dbg !1358

sw.bb14:                                          ; preds = %entry
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.89, i32 0, i32 0), i8** %retval, align 8, !dbg !1360
  br label %return, !dbg !1360

sw.bb15:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.90, i32 0, i32 0), i8** %retval, align 8, !dbg !1362
  br label %return, !dbg !1362

sw.bb16:                                          ; preds = %entry
  store i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.91, i32 0, i32 0), i8** %retval, align 8, !dbg !1364
  br label %return, !dbg !1364

sw.bb17:                                          ; preds = %entry
  store i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.92, i32 0, i32 0), i8** %retval, align 8, !dbg !1366
  br label %return, !dbg !1366

sw.bb18:                                          ; preds = %entry
  store i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.93, i32 0, i32 0), i8** %retval, align 8, !dbg !1368
  br label %return, !dbg !1368

sw.bb19:                                          ; preds = %entry
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.94, i32 0, i32 0), i8** %retval, align 8, !dbg !1370
  br label %return, !dbg !1370

sw.bb20:                                          ; preds = %entry
  store i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.95, i32 0, i32 0), i8** %retval, align 8, !dbg !1372
  br label %return, !dbg !1372

sw.bb21:                                          ; preds = %entry
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.96, i32 0, i32 0), i8** %retval, align 8, !dbg !1374
  br label %return, !dbg !1374

sw.bb22:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.97, i32 0, i32 0), i8** %retval, align 8, !dbg !1376
  br label %return, !dbg !1376

sw.bb23:                                          ; preds = %entry
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.98, i32 0, i32 0), i8** %retval, align 8, !dbg !1378
  br label %return, !dbg !1378

sw.bb24:                                          ; preds = %entry
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.99, i32 0, i32 0), i8** %retval, align 8, !dbg !1380
  br label %return, !dbg !1380

sw.bb25:                                          ; preds = %entry
  store i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.100, i32 0, i32 0), i8** %retval, align 8, !dbg !1382
  br label %return, !dbg !1382

sw.bb26:                                          ; preds = %entry
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.101, i32 0, i32 0), i8** %retval, align 8, !dbg !1384
  br label %return, !dbg !1384

sw.bb27:                                          ; preds = %entry
  store i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.102, i32 0, i32 0), i8** %retval, align 8, !dbg !1386
  br label %return, !dbg !1386

sw.bb28:                                          ; preds = %entry
  store i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.103, i32 0, i32 0), i8** %retval, align 8, !dbg !1388
  br label %return, !dbg !1388

sw.bb29:                                          ; preds = %entry
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.104, i32 0, i32 0), i8** %retval, align 8, !dbg !1390
  br label %return, !dbg !1390

sw.bb30:                                          ; preds = %entry
  store i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.105, i32 0, i32 0), i8** %retval, align 8, !dbg !1392
  br label %return, !dbg !1392

sw.bb31:                                          ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.106, i32 0, i32 0), i8** %retval, align 8, !dbg !1394
  br label %return, !dbg !1394

sw.bb32:                                          ; preds = %entry
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.107, i32 0, i32 0), i8** %retval, align 8, !dbg !1396
  br label %return, !dbg !1396

sw.bb33:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.108, i32 0, i32 0), i8** %retval, align 8, !dbg !1398
  br label %return, !dbg !1398

sw.bb34:                                          ; preds = %entry
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.109, i32 0, i32 0), i8** %retval, align 8, !dbg !1400
  br label %return, !dbg !1400

sw.bb35:                                          ; preds = %entry
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.110, i32 0, i32 0), i8** %retval, align 8, !dbg !1402
  br label %return, !dbg !1402

sw.bb36:                                          ; preds = %entry
  store i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.111, i32 0, i32 0), i8** %retval, align 8, !dbg !1404
  br label %return, !dbg !1404

sw.bb37:                                          ; preds = %entry
  store i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.112, i32 0, i32 0), i8** %retval, align 8, !dbg !1406
  br label %return, !dbg !1406

sw.bb38:                                          ; preds = %entry
  store i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.113, i32 0, i32 0), i8** %retval, align 8, !dbg !1408
  br label %return, !dbg !1408

sw.bb39:                                          ; preds = %entry
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.114, i32 0, i32 0), i8** %retval, align 8, !dbg !1410
  br label %return, !dbg !1410

sw.bb40:                                          ; preds = %entry
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.115, i32 0, i32 0), i8** %retval, align 8, !dbg !1412
  br label %return, !dbg !1412

sw.bb41:                                          ; preds = %entry
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.116, i32 0, i32 0), i8** %retval, align 8, !dbg !1414
  br label %return, !dbg !1414

sw.bb42:                                          ; preds = %entry
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.117, i32 0, i32 0), i8** %retval, align 8, !dbg !1416
  br label %return, !dbg !1416

sw.bb43:                                          ; preds = %entry
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.118, i32 0, i32 0), i8** %retval, align 8, !dbg !1418
  br label %return, !dbg !1418

sw.bb44:                                          ; preds = %entry
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.119, i32 0, i32 0), i8** %retval, align 8, !dbg !1420
  br label %return, !dbg !1420

sw.bb45:                                          ; preds = %entry
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.120, i32 0, i32 0), i8** %retval, align 8, !dbg !1422
  br label %return, !dbg !1422

sw.bb46:                                          ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.121, i32 0, i32 0), i8** %retval, align 8, !dbg !1424
  br label %return, !dbg !1424

sw.bb47:                                          ; preds = %entry
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.122, i32 0, i32 0), i8** %retval, align 8, !dbg !1426
  br label %return, !dbg !1426

sw.bb48:                                          ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.123, i32 0, i32 0), i8** %retval, align 8, !dbg !1428
  br label %return, !dbg !1428

sw.bb49:                                          ; preds = %entry
  store i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.124, i32 0, i32 0), i8** %retval, align 8, !dbg !1430
  br label %return, !dbg !1430

sw.bb50:                                          ; preds = %entry
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.125, i32 0, i32 0), i8** %retval, align 8, !dbg !1432
  br label %return, !dbg !1432

sw.bb51:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.126, i32 0, i32 0), i8** %retval, align 8, !dbg !1434
  br label %return, !dbg !1434

sw.bb52:                                          ; preds = %entry
  store i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.127, i32 0, i32 0), i8** %retval, align 8, !dbg !1436
  br label %return, !dbg !1436

sw.bb53:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.128, i32 0, i32 0), i8** %retval, align 8, !dbg !1438
  br label %return, !dbg !1438

sw.bb54:                                          ; preds = %entry
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.129, i32 0, i32 0), i8** %retval, align 8, !dbg !1440
  br label %return, !dbg !1440

sw.bb55:                                          ; preds = %entry
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.130, i32 0, i32 0), i8** %retval, align 8, !dbg !1442
  br label %return, !dbg !1442

sw.bb56:                                          ; preds = %entry
  store i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.131, i32 0, i32 0), i8** %retval, align 8, !dbg !1444
  br label %return, !dbg !1444

sw.bb57:                                          ; preds = %entry
  store i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.132, i32 0, i32 0), i8** %retval, align 8, !dbg !1446
  br label %return, !dbg !1446

sw.bb58:                                          ; preds = %entry
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.133, i32 0, i32 0), i8** %retval, align 8, !dbg !1448
  br label %return, !dbg !1448

sw.bb59:                                          ; preds = %entry
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.134, i32 0, i32 0), i8** %retval, align 8, !dbg !1450
  br label %return, !dbg !1450

sw.bb60:                                          ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.135, i32 0, i32 0), i8** %retval, align 8, !dbg !1452
  br label %return, !dbg !1452

sw.bb61:                                          ; preds = %entry
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.136, i32 0, i32 0), i8** %retval, align 8, !dbg !1454
  br label %return, !dbg !1454

sw.bb62:                                          ; preds = %entry
  store i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.137, i32 0, i32 0), i8** %retval, align 8, !dbg !1456
  br label %return, !dbg !1456

sw.bb63:                                          ; preds = %entry
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.138, i32 0, i32 0), i8** %retval, align 8, !dbg !1458
  br label %return, !dbg !1458

sw.bb64:                                          ; preds = %entry
  store i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.139, i32 0, i32 0), i8** %retval, align 8, !dbg !1460
  br label %return, !dbg !1460

sw.bb65:                                          ; preds = %entry
  store i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.140, i32 0, i32 0), i8** %retval, align 8, !dbg !1462
  br label %return, !dbg !1462

sw.bb66:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.141, i32 0, i32 0), i8** %retval, align 8, !dbg !1464
  br label %return, !dbg !1464

sw.bb67:                                          ; preds = %entry
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.142, i32 0, i32 0), i8** %retval, align 8, !dbg !1466
  br label %return, !dbg !1466

sw.bb68:                                          ; preds = %entry
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.143, i32 0, i32 0), i8** %retval, align 8, !dbg !1468
  br label %return, !dbg !1468

sw.bb69:                                          ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.144, i32 0, i32 0), i8** %retval, align 8, !dbg !1470
  br label %return, !dbg !1470

sw.bb70:                                          ; preds = %entry
  store i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.145, i32 0, i32 0), i8** %retval, align 8, !dbg !1472
  br label %return, !dbg !1472

sw.bb71:                                          ; preds = %entry
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.146, i32 0, i32 0), i8** %retval, align 8, !dbg !1474
  br label %return, !dbg !1474

sw.bb72:                                          ; preds = %entry
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.147, i32 0, i32 0), i8** %retval, align 8, !dbg !1476
  br label %return, !dbg !1476

sw.bb73:                                          ; preds = %entry
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.148, i32 0, i32 0), i8** %retval, align 8, !dbg !1478
  br label %return, !dbg !1478

sw.bb74:                                          ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.149, i32 0, i32 0), i8** %retval, align 8, !dbg !1480
  br label %return, !dbg !1480

sw.bb75:                                          ; preds = %entry
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.150, i32 0, i32 0), i8** %retval, align 8, !dbg !1482
  br label %return, !dbg !1482

sw.epilog:                                        ; preds = %entry
  %1 = load i32, i32* %err.addr, align 4, !dbg !1484
  %call = call i8* @uv__unknown_err_code(i32 %1), !dbg !1485
  store i8* %call, i8** %retval, align 8, !dbg !1486
  br label %return, !dbg !1486

return:                                           ; preds = %sw.epilog, %sw.bb75, %sw.bb74, %sw.bb73, %sw.bb72, %sw.bb71, %sw.bb70, %sw.bb69, %sw.bb68, %sw.bb67, %sw.bb66, %sw.bb65, %sw.bb64, %sw.bb63, %sw.bb62, %sw.bb61, %sw.bb60, %sw.bb59, %sw.bb58, %sw.bb57, %sw.bb56, %sw.bb55, %sw.bb54, %sw.bb53, %sw.bb52, %sw.bb51, %sw.bb50, %sw.bb49, %sw.bb48, %sw.bb47, %sw.bb46, %sw.bb45, %sw.bb44, %sw.bb43, %sw.bb42, %sw.bb41, %sw.bb40, %sw.bb39, %sw.bb38, %sw.bb37, %sw.bb36, %sw.bb35, %sw.bb34, %sw.bb33, %sw.bb32, %sw.bb31, %sw.bb30, %sw.bb29, %sw.bb28, %sw.bb27, %sw.bb26, %sw.bb25, %sw.bb24, %sw.bb23, %sw.bb22, %sw.bb21, %sw.bb20, %sw.bb19, %sw.bb18, %sw.bb17, %sw.bb16, %sw.bb15, %sw.bb14, %sw.bb13, %sw.bb12, %sw.bb11, %sw.bb10, %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %2 = load i8*, i8** %retval, align 8, !dbg !1487
  ret i8* %2, !dbg !1487
}

; Function Attrs: nounwind uwtable
define i32 @uv_ip4_addr(i8* %ip, i32 %port, %struct.sockaddr_in* %addr) #0 !dbg !441 {
entry:
  %ip.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr_in*, align 8
  store i8* %ip, i8** %ip.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ip.addr, metadata !1488, metadata !936), !dbg !1489
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !1490, metadata !936), !dbg !1491
  store %struct.sockaddr_in* %addr, %struct.sockaddr_in** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %addr.addr, metadata !1492, metadata !936), !dbg !1493
  %0 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr.addr, align 8, !dbg !1494
  %1 = bitcast %struct.sockaddr_in* %0 to i8*, !dbg !1495
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 16, i32 4, i1 false), !dbg !1495
  %2 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr.addr, align 8, !dbg !1496
  %sin_family = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %2, i32 0, i32 0, !dbg !1497
  store i16 2, i16* %sin_family, align 4, !dbg !1498
  %3 = load i32, i32* %port.addr, align 4, !dbg !1499
  %conv = trunc i32 %3 to i16, !dbg !1499
  %call = call zeroext i16 @htons(i16 zeroext %conv) #1, !dbg !1500
  %4 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr.addr, align 8, !dbg !1501
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %4, i32 0, i32 1, !dbg !1502
  store i16 %call, i16* %sin_port, align 2, !dbg !1503
  %5 = load i8*, i8** %ip.addr, align 8, !dbg !1504
  %6 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr.addr, align 8, !dbg !1505
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %6, i32 0, i32 2, !dbg !1506
  %s_addr = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr, i32 0, i32 0, !dbg !1507
  %7 = bitcast i32* %s_addr to i8*, !dbg !1508
  %call1 = call i32 @uv_inet_pton(i32 2, i8* %5, i8* %7), !dbg !1509
  ret i32 %call1, !dbg !1510
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind readnone
declare zeroext i16 @htons(i16 zeroext) #4

declare i32 @uv_inet_pton(i32, i8*, i8*) #5

; Function Attrs: nounwind uwtable
define i32 @uv_ip6_addr(i8* %ip, i32 %port, %struct.sockaddr_in6* %addr) #0 !dbg !466 {
entry:
  %ip.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr_in6*, align 8
  %address_part = alloca [40 x i8], align 16
  %address_part_size = alloca i64, align 8
  %zone_index = alloca i8*, align 8
  store i8* %ip, i8** %ip.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ip.addr, metadata !1511, metadata !936), !dbg !1512
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !1513, metadata !936), !dbg !1514
  store %struct.sockaddr_in6* %addr, %struct.sockaddr_in6** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6** %addr.addr, metadata !1515, metadata !936), !dbg !1516
  call void @llvm.dbg.declare(metadata [40 x i8]* %address_part, metadata !1517, metadata !936), !dbg !1518
  call void @llvm.dbg.declare(metadata i64* %address_part_size, metadata !1519, metadata !936), !dbg !1520
  call void @llvm.dbg.declare(metadata i8** %zone_index, metadata !1521, metadata !936), !dbg !1522
  %0 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr.addr, align 8, !dbg !1523
  %1 = bitcast %struct.sockaddr_in6* %0 to i8*, !dbg !1524
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 28, i32 4, i1 false), !dbg !1524
  %2 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr.addr, align 8, !dbg !1525
  %sin6_family = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %2, i32 0, i32 0, !dbg !1526
  store i16 10, i16* %sin6_family, align 4, !dbg !1527
  %3 = load i32, i32* %port.addr, align 4, !dbg !1528
  %conv = trunc i32 %3 to i16, !dbg !1528
  %call = call zeroext i16 @htons(i16 zeroext %conv) #1, !dbg !1529
  %4 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr.addr, align 8, !dbg !1530
  %sin6_port = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %4, i32 0, i32 1, !dbg !1531
  store i16 %call, i16* %sin6_port, align 2, !dbg !1532
  %5 = load i8*, i8** %ip.addr, align 8, !dbg !1533
  %call1 = call i8* @strchr(i8* %5, i32 37) #9, !dbg !1534
  store i8* %call1, i8** %zone_index, align 8, !dbg !1535
  %6 = load i8*, i8** %zone_index, align 8, !dbg !1536
  %cmp = icmp ne i8* %6, null, !dbg !1538
  br i1 %cmp, label %if.then, label %if.end8, !dbg !1539

if.then:                                          ; preds = %entry
  %7 = load i8*, i8** %zone_index, align 8, !dbg !1540
  %8 = load i8*, i8** %ip.addr, align 8, !dbg !1542
  %sub.ptr.lhs.cast = ptrtoint i8* %7 to i64, !dbg !1543
  %sub.ptr.rhs.cast = ptrtoint i8* %8 to i64, !dbg !1543
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1543
  store i64 %sub.ptr.sub, i64* %address_part_size, align 8, !dbg !1544
  %9 = load i64, i64* %address_part_size, align 8, !dbg !1545
  %cmp3 = icmp uge i64 %9, 40, !dbg !1547
  br i1 %cmp3, label %if.then5, label %if.end, !dbg !1548

if.then5:                                         ; preds = %if.then
  store i64 39, i64* %address_part_size, align 8, !dbg !1549
  br label %if.end, !dbg !1550

if.end:                                           ; preds = %if.then5, %if.then
  %arraydecay = getelementptr inbounds [40 x i8], [40 x i8]* %address_part, i32 0, i32 0, !dbg !1551
  %10 = load i8*, i8** %ip.addr, align 8, !dbg !1552
  %11 = load i64, i64* %address_part_size, align 8, !dbg !1553
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %10, i64 %11, i32 1, i1 false), !dbg !1551
  %12 = load i64, i64* %address_part_size, align 8, !dbg !1554
  %arrayidx = getelementptr inbounds [40 x i8], [40 x i8]* %address_part, i64 0, i64 %12, !dbg !1555
  store i8 0, i8* %arrayidx, align 1, !dbg !1556
  %arraydecay6 = getelementptr inbounds [40 x i8], [40 x i8]* %address_part, i32 0, i32 0, !dbg !1557
  store i8* %arraydecay6, i8** %ip.addr, align 8, !dbg !1558
  %13 = load i8*, i8** %zone_index, align 8, !dbg !1559
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !1559
  store i8* %incdec.ptr, i8** %zone_index, align 8, !dbg !1559
  %14 = load i8*, i8** %zone_index, align 8, !dbg !1560
  %call7 = call i32 @if_nametoindex(i8* %14) #8, !dbg !1561
  %15 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr.addr, align 8, !dbg !1562
  %sin6_scope_id = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %15, i32 0, i32 4, !dbg !1563
  store i32 %call7, i32* %sin6_scope_id, align 4, !dbg !1564
  br label %if.end8, !dbg !1565

if.end8:                                          ; preds = %if.end, %entry
  %16 = load i8*, i8** %ip.addr, align 8, !dbg !1566
  %17 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr.addr, align 8, !dbg !1567
  %sin6_addr = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %17, i32 0, i32 3, !dbg !1568
  %18 = bitcast %struct.in6_addr* %sin6_addr to i8*, !dbg !1569
  %call9 = call i32 @uv_inet_pton(i32 10, i8* %16, i8* %18), !dbg !1570
  ret i32 %call9, !dbg !1571
}

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #2

; Function Attrs: nounwind
declare i32 @if_nametoindex(i8*) #6

; Function Attrs: nounwind uwtable
define i32 @uv_ip4_name(%struct.sockaddr_in* %src, i8* %dst, i64 %size) #0 !dbg !491 {
entry:
  %src.addr = alloca %struct.sockaddr_in*, align 8
  %dst.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store %struct.sockaddr_in* %src, %struct.sockaddr_in** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %src.addr, metadata !1572, metadata !936), !dbg !1573
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !1574, metadata !936), !dbg !1575
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1576, metadata !936), !dbg !1577
  %0 = load %struct.sockaddr_in*, %struct.sockaddr_in** %src.addr, align 8, !dbg !1578
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %0, i32 0, i32 2, !dbg !1579
  %1 = bitcast %struct.in_addr* %sin_addr to i8*, !dbg !1580
  %2 = load i8*, i8** %dst.addr, align 8, !dbg !1581
  %3 = load i64, i64* %size.addr, align 8, !dbg !1582
  %call = call i32 @uv_inet_ntop(i32 2, i8* %1, i8* %2, i64 %3), !dbg !1583
  ret i32 %call, !dbg !1584
}

declare i32 @uv_inet_ntop(i32, i8*, i8*, i64) #5

; Function Attrs: nounwind uwtable
define i32 @uv_ip6_name(%struct.sockaddr_in6* %src, i8* %dst, i64 %size) #0 !dbg !496 {
entry:
  %src.addr = alloca %struct.sockaddr_in6*, align 8
  %dst.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store %struct.sockaddr_in6* %src, %struct.sockaddr_in6** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6** %src.addr, metadata !1585, metadata !936), !dbg !1586
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !1587, metadata !936), !dbg !1588
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1589, metadata !936), !dbg !1590
  %0 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %src.addr, align 8, !dbg !1591
  %sin6_addr = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %0, i32 0, i32 3, !dbg !1592
  %1 = bitcast %struct.in6_addr* %sin6_addr to i8*, !dbg !1593
  %2 = load i8*, i8** %dst.addr, align 8, !dbg !1594
  %3 = load i64, i64* %size.addr, align 8, !dbg !1595
  %call = call i32 @uv_inet_ntop(i32 10, i8* %1, i8* %2, i64 %3), !dbg !1596
  ret i32 %call, !dbg !1597
}

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_bind(%struct.uv_tcp_s* %handle, %struct.sockaddr* %addr, i32 %flags) #0 !dbg !501 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %flags.addr = alloca i32, align 4
  %addrlen = alloca i32, align 4
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !1598, metadata !936), !dbg !1599
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1600, metadata !936), !dbg !1601
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1602, metadata !936), !dbg !1603
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !1604, metadata !936), !dbg !1605
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1606
  %type = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 2, !dbg !1608
  %1 = load i32, i32* %type, align 8, !dbg !1608
  %cmp = icmp ne i32 %1, 12, !dbg !1609
  br i1 %cmp, label %if.then, label %if.end, !dbg !1610

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !1611
  br label %return, !dbg !1611

if.end:                                           ; preds = %entry
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1612
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !1614
  %3 = load i16, i16* %sa_family, align 2, !dbg !1614
  %conv = zext i16 %3 to i32, !dbg !1612
  %cmp1 = icmp eq i32 %conv, 2, !dbg !1615
  br i1 %cmp1, label %if.then3, label %if.else, !dbg !1616

if.then3:                                         ; preds = %if.end
  store i32 16, i32* %addrlen, align 4, !dbg !1617
  br label %if.end11, !dbg !1618

if.else:                                          ; preds = %if.end
  %4 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1619
  %sa_family4 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %4, i32 0, i32 0, !dbg !1621
  %5 = load i16, i16* %sa_family4, align 2, !dbg !1621
  %conv5 = zext i16 %5 to i32, !dbg !1619
  %cmp6 = icmp eq i32 %conv5, 10, !dbg !1622
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !1623

if.then8:                                         ; preds = %if.else
  store i32 28, i32* %addrlen, align 4, !dbg !1624
  br label %if.end10, !dbg !1625

if.else9:                                         ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !1626
  br label %return, !dbg !1626

if.end10:                                         ; preds = %if.then8
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.then3
  %6 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1627
  %7 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1628
  %8 = load i32, i32* %addrlen, align 4, !dbg !1629
  %9 = load i32, i32* %flags.addr, align 4, !dbg !1630
  %call = call i32 @uv__tcp_bind(%struct.uv_tcp_s* %6, %struct.sockaddr* %7, i32 %8, i32 %9), !dbg !1631
  store i32 %call, i32* %retval, align 4, !dbg !1632
  br label %return, !dbg !1632

return:                                           ; preds = %if.end11, %if.else9, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !1633
  ret i32 %10, !dbg !1633
}

declare i32 @uv__tcp_bind(%struct.uv_tcp_s*, %struct.sockaddr*, i32, i32) #5

; Function Attrs: nounwind uwtable
define i32 @uv_udp_bind(%struct.uv_udp_s* %handle, %struct.sockaddr* %addr, i32 %flags) #0 !dbg !618 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %flags.addr = alloca i32, align 4
  %addrlen = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1634, metadata !936), !dbg !1635
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1636, metadata !936), !dbg !1637
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1638, metadata !936), !dbg !1639
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !1640, metadata !936), !dbg !1641
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1642
  %type = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 2, !dbg !1644
  %1 = load i32, i32* %type, align 8, !dbg !1644
  %cmp = icmp ne i32 %1, 15, !dbg !1645
  br i1 %cmp, label %if.then, label %if.end, !dbg !1646

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !1647
  br label %return, !dbg !1647

if.end:                                           ; preds = %entry
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1648
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !1650
  %3 = load i16, i16* %sa_family, align 2, !dbg !1650
  %conv = zext i16 %3 to i32, !dbg !1648
  %cmp1 = icmp eq i32 %conv, 2, !dbg !1651
  br i1 %cmp1, label %if.then3, label %if.else, !dbg !1652

if.then3:                                         ; preds = %if.end
  store i32 16, i32* %addrlen, align 4, !dbg !1653
  br label %if.end11, !dbg !1654

if.else:                                          ; preds = %if.end
  %4 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1655
  %sa_family4 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %4, i32 0, i32 0, !dbg !1657
  %5 = load i16, i16* %sa_family4, align 2, !dbg !1657
  %conv5 = zext i16 %5 to i32, !dbg !1655
  %cmp6 = icmp eq i32 %conv5, 10, !dbg !1658
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !1659

if.then8:                                         ; preds = %if.else
  store i32 28, i32* %addrlen, align 4, !dbg !1660
  br label %if.end10, !dbg !1661

if.else9:                                         ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !1662
  br label %return, !dbg !1662

if.end10:                                         ; preds = %if.then8
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.then3
  %6 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1663
  %7 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1664
  %8 = load i32, i32* %addrlen, align 4, !dbg !1665
  %9 = load i32, i32* %flags.addr, align 4, !dbg !1666
  %call = call i32 @uv__udp_bind(%struct.uv_udp_s* %6, %struct.sockaddr* %7, i32 %8, i32 %9), !dbg !1667
  store i32 %call, i32* %retval, align 4, !dbg !1668
  br label %return, !dbg !1668

return:                                           ; preds = %if.end11, %if.else9, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !1669
  ret i32 %10, !dbg !1669
}

declare i32 @uv__udp_bind(%struct.uv_udp_s*, %struct.sockaddr*, i32, i32) #5

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_connect(%struct.uv_connect_s* %req, %struct.uv_tcp_s* %handle, %struct.sockaddr* %addr, void (%struct.uv_connect_s*, i32)* %cb) #0 !dbg !648 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_connect_s*, align 8
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %cb.addr = alloca void (%struct.uv_connect_s*, i32)*, align 8
  %addrlen = alloca i32, align 4
  store %struct.uv_connect_s* %req, %struct.uv_connect_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_connect_s** %req.addr, metadata !1670, metadata !936), !dbg !1671
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !1672, metadata !936), !dbg !1673
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1674, metadata !936), !dbg !1675
  store void (%struct.uv_connect_s*, i32)* %cb, void (%struct.uv_connect_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_connect_s*, i32)** %cb.addr, metadata !1676, metadata !936), !dbg !1677
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !1678, metadata !936), !dbg !1679
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1680
  %type = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 2, !dbg !1682
  %1 = load i32, i32* %type, align 8, !dbg !1682
  %cmp = icmp ne i32 %1, 12, !dbg !1683
  br i1 %cmp, label %if.then, label %if.end, !dbg !1684

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !1685
  br label %return, !dbg !1685

if.end:                                           ; preds = %entry
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1686
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !1688
  %3 = load i16, i16* %sa_family, align 2, !dbg !1688
  %conv = zext i16 %3 to i32, !dbg !1686
  %cmp1 = icmp eq i32 %conv, 2, !dbg !1689
  br i1 %cmp1, label %if.then3, label %if.else, !dbg !1690

if.then3:                                         ; preds = %if.end
  store i32 16, i32* %addrlen, align 4, !dbg !1691
  br label %if.end11, !dbg !1692

if.else:                                          ; preds = %if.end
  %4 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1693
  %sa_family4 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %4, i32 0, i32 0, !dbg !1695
  %5 = load i16, i16* %sa_family4, align 2, !dbg !1695
  %conv5 = zext i16 %5 to i32, !dbg !1693
  %cmp6 = icmp eq i32 %conv5, 10, !dbg !1696
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !1697

if.then8:                                         ; preds = %if.else
  store i32 28, i32* %addrlen, align 4, !dbg !1698
  br label %if.end10, !dbg !1699

if.else9:                                         ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !1700
  br label %return, !dbg !1700

if.end10:                                         ; preds = %if.then8
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.then3
  %6 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !1701
  %7 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1702
  %8 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1703
  %9 = load i32, i32* %addrlen, align 4, !dbg !1704
  %10 = load void (%struct.uv_connect_s*, i32)*, void (%struct.uv_connect_s*, i32)** %cb.addr, align 8, !dbg !1705
  %call = call i32 @uv__tcp_connect(%struct.uv_connect_s* %6, %struct.uv_tcp_s* %7, %struct.sockaddr* %8, i32 %9, void (%struct.uv_connect_s*, i32)* %10), !dbg !1706
  store i32 %call, i32* %retval, align 4, !dbg !1707
  br label %return, !dbg !1707

return:                                           ; preds = %if.end11, %if.else9, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !1708
  ret i32 %11, !dbg !1708
}

declare i32 @uv__tcp_connect(%struct.uv_connect_s*, %struct.uv_tcp_s*, %struct.sockaddr*, i32, void (%struct.uv_connect_s*, i32)*) #5

; Function Attrs: nounwind uwtable
define i32 @uv_udp_send(%struct.uv_udp_send_s* %req, %struct.uv_udp_s* %handle, %struct.uv_buf_t* %bufs, i32 %nbufs, %struct.sockaddr* %addr, void (%struct.uv_udp_send_s*, i32)* %send_cb) #0 !dbg !651 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_udp_send_s*, align 8
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr*, align 8
  %send_cb.addr = alloca void (%struct.uv_udp_send_s*, i32)*, align 8
  %addrlen = alloca i32, align 4
  store %struct.uv_udp_send_s* %req, %struct.uv_udp_send_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_send_s** %req.addr, metadata !1709, metadata !936), !dbg !1710
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1711, metadata !936), !dbg !1712
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !1713, metadata !936), !dbg !1714
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !1715, metadata !936), !dbg !1716
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1717, metadata !936), !dbg !1718
  store void (%struct.uv_udp_send_s*, i32)* %send_cb, void (%struct.uv_udp_send_s*, i32)** %send_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_udp_send_s*, i32)** %send_cb.addr, metadata !1719, metadata !936), !dbg !1720
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !1721, metadata !936), !dbg !1722
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1723
  %type = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 2, !dbg !1725
  %1 = load i32, i32* %type, align 8, !dbg !1725
  %cmp = icmp ne i32 %1, 15, !dbg !1726
  br i1 %cmp, label %if.then, label %if.end, !dbg !1727

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !1728
  br label %return, !dbg !1728

if.end:                                           ; preds = %entry
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1729
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !1731
  %3 = load i16, i16* %sa_family, align 2, !dbg !1731
  %conv = zext i16 %3 to i32, !dbg !1729
  %cmp1 = icmp eq i32 %conv, 2, !dbg !1732
  br i1 %cmp1, label %if.then3, label %if.else, !dbg !1733

if.then3:                                         ; preds = %if.end
  store i32 16, i32* %addrlen, align 4, !dbg !1734
  br label %if.end11, !dbg !1735

if.else:                                          ; preds = %if.end
  %4 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1736
  %sa_family4 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %4, i32 0, i32 0, !dbg !1738
  %5 = load i16, i16* %sa_family4, align 2, !dbg !1738
  %conv5 = zext i16 %5 to i32, !dbg !1736
  %cmp6 = icmp eq i32 %conv5, 10, !dbg !1739
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !1740

if.then8:                                         ; preds = %if.else
  store i32 28, i32* %addrlen, align 4, !dbg !1741
  br label %if.end10, !dbg !1742

if.else9:                                         ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !1743
  br label %return, !dbg !1743

if.end10:                                         ; preds = %if.then8
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.then3
  %6 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1744
  %7 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1745
  %8 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1746
  %9 = load i32, i32* %nbufs.addr, align 4, !dbg !1747
  %10 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1748
  %11 = load i32, i32* %addrlen, align 4, !dbg !1749
  %12 = load void (%struct.uv_udp_send_s*, i32)*, void (%struct.uv_udp_send_s*, i32)** %send_cb.addr, align 8, !dbg !1750
  %call = call i32 @uv__udp_send(%struct.uv_udp_send_s* %6, %struct.uv_udp_s* %7, %struct.uv_buf_t* %8, i32 %9, %struct.sockaddr* %10, i32 %11, void (%struct.uv_udp_send_s*, i32)* %12), !dbg !1751
  store i32 %call, i32* %retval, align 4, !dbg !1752
  br label %return, !dbg !1752

return:                                           ; preds = %if.end11, %if.else9, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !1753
  ret i32 %13, !dbg !1753
}

declare i32 @uv__udp_send(%struct.uv_udp_send_s*, %struct.uv_udp_s*, %struct.uv_buf_t*, i32, %struct.sockaddr*, i32, void (%struct.uv_udp_send_s*, i32)*) #5

; Function Attrs: nounwind uwtable
define i32 @uv_udp_try_send(%struct.uv_udp_s* %handle, %struct.uv_buf_t* %bufs, i32 %nbufs, %struct.sockaddr* %addr) #0 !dbg !684 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1754, metadata !936), !dbg !1755
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !1756, metadata !936), !dbg !1757
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !1758, metadata !936), !dbg !1759
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1760, metadata !936), !dbg !1761
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !1762, metadata !936), !dbg !1763
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1764
  %type = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 2, !dbg !1766
  %1 = load i32, i32* %type, align 8, !dbg !1766
  %cmp = icmp ne i32 %1, 15, !dbg !1767
  br i1 %cmp, label %if.then, label %if.end, !dbg !1768

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !1769
  br label %return, !dbg !1769

if.end:                                           ; preds = %entry
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1770
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !1772
  %3 = load i16, i16* %sa_family, align 2, !dbg !1772
  %conv = zext i16 %3 to i32, !dbg !1770
  %cmp1 = icmp eq i32 %conv, 2, !dbg !1773
  br i1 %cmp1, label %if.then3, label %if.else, !dbg !1774

if.then3:                                         ; preds = %if.end
  store i32 16, i32* %addrlen, align 4, !dbg !1775
  br label %if.end11, !dbg !1776

if.else:                                          ; preds = %if.end
  %4 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1777
  %sa_family4 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %4, i32 0, i32 0, !dbg !1779
  %5 = load i16, i16* %sa_family4, align 2, !dbg !1779
  %conv5 = zext i16 %5 to i32, !dbg !1777
  %cmp6 = icmp eq i32 %conv5, 10, !dbg !1780
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !1781

if.then8:                                         ; preds = %if.else
  store i32 28, i32* %addrlen, align 4, !dbg !1782
  br label %if.end10, !dbg !1783

if.else9:                                         ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !1784
  br label %return, !dbg !1784

if.end10:                                         ; preds = %if.then8
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.then3
  %6 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1785
  %7 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1786
  %8 = load i32, i32* %nbufs.addr, align 4, !dbg !1787
  %9 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1788
  %10 = load i32, i32* %addrlen, align 4, !dbg !1789
  %call = call i32 @uv__udp_try_send(%struct.uv_udp_s* %6, %struct.uv_buf_t* %7, i32 %8, %struct.sockaddr* %9, i32 %10), !dbg !1790
  store i32 %call, i32* %retval, align 4, !dbg !1791
  br label %return, !dbg !1791

return:                                           ; preds = %if.end11, %if.else9, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !1792
  ret i32 %11, !dbg !1792
}

declare i32 @uv__udp_try_send(%struct.uv_udp_s*, %struct.uv_buf_t*, i32, %struct.sockaddr*, i32) #5

; Function Attrs: nounwind uwtable
define i32 @uv_udp_recv_start(%struct.uv_udp_s* %handle, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %alloc_cb, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %recv_cb) #0 !dbg !687 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %alloc_cb.addr = alloca void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, align 8
  %recv_cb.addr = alloca void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1793, metadata !936), !dbg !1794
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %alloc_cb, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, metadata !1795, metadata !936), !dbg !1796
  store void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %recv_cb, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, metadata !1797, metadata !936), !dbg !1798
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1799
  %type = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 2, !dbg !1801
  %1 = load i32, i32* %type, align 8, !dbg !1801
  %cmp = icmp ne i32 %1, 15, !dbg !1802
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1803

lor.lhs.false:                                    ; preds = %entry
  %2 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8, !dbg !1804
  %cmp1 = icmp eq void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %2, null, !dbg !1806
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !1807

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, align 8, !dbg !1808
  %cmp3 = icmp eq void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %3, null, !dbg !1810
  br i1 %cmp3, label %if.then, label %if.else, !dbg !1811

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1812
  br label %return, !dbg !1812

if.else:                                          ; preds = %lor.lhs.false2
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1813
  %5 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8, !dbg !1814
  %6 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, align 8, !dbg !1815
  %call = call i32 @uv__udp_recv_start(%struct.uv_udp_s* %4, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %5, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %6), !dbg !1816
  store i32 %call, i32* %retval, align 4, !dbg !1817
  br label %return, !dbg !1817

return:                                           ; preds = %if.else, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1818
  ret i32 %7, !dbg !1818
}

declare i32 @uv__udp_recv_start(%struct.uv_udp_s*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*) #5

; Function Attrs: nounwind uwtable
define i32 @uv_udp_recv_stop(%struct.uv_udp_s* %handle) #0 !dbg !690 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1819, metadata !936), !dbg !1820
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1821
  %type = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 2, !dbg !1823
  %1 = load i32, i32* %type, align 8, !dbg !1823
  %cmp = icmp ne i32 %1, 15, !dbg !1824
  br i1 %cmp, label %if.then, label %if.else, !dbg !1825

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !1826
  br label %return, !dbg !1826

if.else:                                          ; preds = %entry
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1827
  %call = call i32 @uv__udp_recv_stop(%struct.uv_udp_s* %2), !dbg !1828
  store i32 %call, i32* %retval, align 4, !dbg !1829
  br label %return, !dbg !1829

return:                                           ; preds = %if.else, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !1830
  ret i32 %3, !dbg !1830
}

declare i32 @uv__udp_recv_stop(%struct.uv_udp_s*) #5

; Function Attrs: nounwind uwtable
define void @uv_walk(%struct.uv_loop_s* %loop, void (%struct.uv_handle_s*, i8*)* %walk_cb, i8* %arg) #0 !dbg !693 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %walk_cb.addr = alloca void (%struct.uv_handle_s*, i8*)*, align 8
  %arg.addr = alloca i8*, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %h = alloca %struct.uv_handle_s*, align 8
  %q5 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1831, metadata !936), !dbg !1832
  store void (%struct.uv_handle_s*, i8*)* %walk_cb, void (%struct.uv_handle_s*, i8*)** %walk_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_handle_s*, i8*)** %walk_cb.addr, metadata !1833, metadata !936), !dbg !1834
  store i8* %arg, i8** %arg.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %arg.addr, metadata !1835, metadata !936), !dbg !1836
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !1837, metadata !936), !dbg !1838
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1839, metadata !936), !dbg !1840
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %h, metadata !1841, metadata !936), !dbg !1842
  br label %do.body, !dbg !1843

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1844
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 2, !dbg !1844
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1844
  %handle_queue1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 2, !dbg !1844
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue1, i64 0, i64 0, !dbg !1844
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1844
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !1844
  %cmp = icmp eq [2 x i8*]* %handle_queue, %3, !dbg !1844
  br i1 %cmp, label %if.then, label %if.else, !dbg !1844

if.then:                                          ; preds = %do.body
  br label %do.body2, !dbg !1848

do.body2:                                         ; preds = %if.then
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1850
  %4 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !1850
  store [2 x i8*]* %queue, [2 x i8*]** %4, align 16, !dbg !1850
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !1850
  %5 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !1850
  store [2 x i8*]* %queue, [2 x i8*]** %5, align 8, !dbg !1850
  br label %do.end, !dbg !1850

do.end:                                           ; preds = %do.body2
  br label %if.end, !dbg !1853

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q5, metadata !1855, metadata !936), !dbg !1857
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1858
  %handle_queue6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 2, !dbg !1858
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 0, !dbg !1858
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1858
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1858
  store [2 x i8*]* %8, [2 x i8*]** %q5, align 8, !dbg !1858
  br label %do.body8, !dbg !1858

do.body8:                                         ; preds = %if.else
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1860
  %handle_queue9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 2, !dbg !1860
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !1860
  %10 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !1860
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !1860
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !1860
  %12 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !1860
  store [2 x i8*]* %11, [2 x i8*]** %12, align 8, !dbg !1860
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !1860
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1860
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1860
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1860
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1860
  store [2 x i8*]* %queue, [2 x i8*]** %15, align 8, !dbg !1860
  %16 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !1860
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1860
  %17 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !1860
  store [2 x i8*]* %16, [2 x i8*]** %17, align 16, !dbg !1860
  %18 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !1860
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 1, !dbg !1860
  %19 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !1860
  %20 = load [2 x i8*]*, [2 x i8*]** %19, align 8, !dbg !1860
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1860
  %handle_queue16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 2, !dbg !1860
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue16, i64 0, i64 1, !dbg !1860
  %22 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !1860
  store [2 x i8*]* %20, [2 x i8*]** %22, align 8, !dbg !1860
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1860
  %handle_queue18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 2, !dbg !1860
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1860
  %handle_queue19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 2, !dbg !1860
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue19, i64 0, i64 1, !dbg !1860
  %25 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !1860
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !1860
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %26, i64 0, i64 0, !dbg !1860
  %27 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !1860
  store [2 x i8*]* %handle_queue18, [2 x i8*]** %27, align 8, !dbg !1860
  %28 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !1860
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %28, i64 0, i64 1, !dbg !1860
  %29 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !1860
  store [2 x i8*]* %queue, [2 x i8*]** %29, align 8, !dbg !1860
  br label %do.end23, !dbg !1860

do.end23:                                         ; preds = %do.body8
  br label %if.end

if.end:                                           ; preds = %do.end23, %do.end
  br label %do.end24, !dbg !1863

do.end24:                                         ; preds = %if.end
  br label %while.cond, !dbg !1865

while.cond:                                       ; preds = %if.end48, %if.then47, %do.end24
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1866
  %30 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !1866
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 16, !dbg !1866
  %cmp26 = icmp eq [2 x i8*]* %queue, %31, !dbg !1866
  %lnot = xor i1 %cmp26, true, !dbg !1868
  br i1 %lnot, label %while.body, label %while.end, !dbg !1869

while.body:                                       ; preds = %while.cond
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1870
  %32 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !1870
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 16, !dbg !1870
  store [2 x i8*]* %33, [2 x i8*]** %q, align 8, !dbg !1872
  %34 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1873
  %35 = bitcast [2 x i8*]* %34 to i8*, !dbg !1873
  %add.ptr = getelementptr inbounds i8, i8* %35, i64 -32, !dbg !1873
  %36 = bitcast i8* %add.ptr to %struct.uv_handle_s*, !dbg !1873
  store %struct.uv_handle_s* %36, %struct.uv_handle_s** %h, align 8, !dbg !1874
  br label %do.body28, !dbg !1875

do.body28:                                        ; preds = %while.body
  %37 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1876
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 0, !dbg !1876
  %38 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !1876
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !1876
  %40 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1876
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 1, !dbg !1876
  %41 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !1876
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 8, !dbg !1876
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 0, !dbg !1876
  %43 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !1876
  store [2 x i8*]* %39, [2 x i8*]** %43, align 8, !dbg !1876
  %44 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1876
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %44, i64 0, i64 1, !dbg !1876
  %45 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !1876
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !1876
  %47 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1876
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !1876
  %48 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !1876
  %49 = load [2 x i8*]*, [2 x i8*]** %48, align 8, !dbg !1876
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %49, i64 0, i64 1, !dbg !1876
  %50 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !1876
  store [2 x i8*]* %46, [2 x i8*]** %50, align 8, !dbg !1876
  br label %do.end35, !dbg !1876

do.end35:                                         ; preds = %do.body28
  br label %do.body36, !dbg !1879

do.body36:                                        ; preds = %do.end35
  %51 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1880
  %handle_queue37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %51, i32 0, i32 2, !dbg !1880
  %52 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1880
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %52, i64 0, i64 0, !dbg !1880
  %53 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1880
  store [2 x i8*]* %handle_queue37, [2 x i8*]** %53, align 8, !dbg !1880
  %54 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1880
  %handle_queue39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %54, i32 0, i32 2, !dbg !1880
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue39, i64 0, i64 1, !dbg !1880
  %55 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !1880
  %56 = load [2 x i8*]*, [2 x i8*]** %55, align 8, !dbg !1880
  %57 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1880
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !1880
  %58 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !1880
  store [2 x i8*]* %56, [2 x i8*]** %58, align 8, !dbg !1880
  %59 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1880
  %60 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1880
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !1880
  %61 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !1880
  %62 = load [2 x i8*]*, [2 x i8*]** %61, align 8, !dbg !1880
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !1880
  %63 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !1880
  store [2 x i8*]* %59, [2 x i8*]** %63, align 8, !dbg !1880
  %64 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1880
  %65 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1880
  %handle_queue44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %65, i32 0, i32 2, !dbg !1880
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue44, i64 0, i64 1, !dbg !1880
  %66 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1880
  store [2 x i8*]* %64, [2 x i8*]** %66, align 8, !dbg !1880
  br label %do.end46, !dbg !1880

do.end46:                                         ; preds = %do.body36
  %67 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1883
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %67, i32 0, i32 7, !dbg !1885
  %68 = load i32, i32* %flags, align 8, !dbg !1885
  %and = and i32 %68, 32768, !dbg !1886
  %tobool = icmp ne i32 %and, 0, !dbg !1886
  br i1 %tobool, label %if.then47, label %if.end48, !dbg !1887

if.then47:                                        ; preds = %do.end46
  br label %while.cond, !dbg !1888

if.end48:                                         ; preds = %do.end46
  %69 = load void (%struct.uv_handle_s*, i8*)*, void (%struct.uv_handle_s*, i8*)** %walk_cb.addr, align 8, !dbg !1890
  %70 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1891
  %71 = load i8*, i8** %arg.addr, align 8, !dbg !1892
  call void %69(%struct.uv_handle_s* %70, i8* %71), !dbg !1890
  br label %while.cond, !dbg !1893

while.end:                                        ; preds = %while.cond
  ret void, !dbg !1895
}

; Function Attrs: nounwind uwtable
define void @uv_print_all_handles(%struct.uv_loop_s* %loop, %struct._IO_FILE* %stream) #0 !dbg !700 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %stream.addr = alloca %struct._IO_FILE*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1896, metadata !936), !dbg !1897
  store %struct._IO_FILE* %stream, %struct._IO_FILE** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %stream.addr, metadata !1898, metadata !936), !dbg !1899
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1900
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !1901
  call void @uv__print_handles(%struct.uv_loop_s* %0, i32 0, %struct._IO_FILE* %1), !dbg !1902
  ret void, !dbg !1903
}

; Function Attrs: nounwind uwtable
define internal void @uv__print_handles(%struct.uv_loop_s* %loop, i32 %only_active, %struct._IO_FILE* %stream) #0 !dbg !914 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %only_active.addr = alloca i32, align 4
  %stream.addr = alloca %struct._IO_FILE*, align 8
  %type = alloca i8*, align 8
  %q = alloca [2 x i8*]*, align 8
  %h = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1904, metadata !936), !dbg !1905
  store i32 %only_active, i32* %only_active.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %only_active.addr, metadata !1906, metadata !936), !dbg !1907
  store %struct._IO_FILE* %stream, %struct._IO_FILE** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %stream.addr, metadata !1908, metadata !936), !dbg !1909
  call void @llvm.dbg.declare(metadata i8** %type, metadata !1910, metadata !936), !dbg !1911
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1912, metadata !936), !dbg !1913
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %h, metadata !1914, metadata !936), !dbg !1915
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1916
  %cmp = icmp eq %struct.uv_loop_s* %0, null, !dbg !1918
  br i1 %cmp, label %if.then, label %if.end, !dbg !1919

if.then:                                          ; preds = %entry
  %call = call %struct.uv_loop_s* @uv_default_loop(), !dbg !1920
  store %struct.uv_loop_s* %call, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1921
  br label %if.end, !dbg !1922

if.end:                                           ; preds = %if.then, %entry
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1923
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 2, !dbg !1923
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue, i64 0, i64 0, !dbg !1923
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1923
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !1923
  store [2 x i8*]* %3, [2 x i8*]** %q, align 8, !dbg !1923
  br label %for.cond, !dbg !1923

for.cond:                                         ; preds = %for.inc, %if.end
  %4 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1925
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1925
  %handle_queue1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 2, !dbg !1925
  %cmp2 = icmp ne [2 x i8*]* %4, %handle_queue1, !dbg !1925
  br i1 %cmp2, label %for.body, label %for.end, !dbg !1925

for.body:                                         ; preds = %for.cond
  %6 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1928
  %7 = bitcast [2 x i8*]* %6 to i8*, !dbg !1928
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 -32, !dbg !1928
  %8 = bitcast i8* %add.ptr to %struct.uv_handle_s*, !dbg !1928
  store %struct.uv_handle_s* %8, %struct.uv_handle_s** %h, align 8, !dbg !1930
  %9 = load i32, i32* %only_active.addr, align 4, !dbg !1931
  %tobool = icmp ne i32 %9, 0, !dbg !1931
  br i1 %tobool, label %land.lhs.true, label %if.end5, !dbg !1933

land.lhs.true:                                    ; preds = %for.body
  %10 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1934
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %10, i32 0, i32 7, !dbg !1934
  %11 = load i32, i32* %flags, align 8, !dbg !1934
  %and = and i32 %11, 16384, !dbg !1934
  %cmp3 = icmp ne i32 %and, 0, !dbg !1934
  br i1 %cmp3, label %if.end5, label %if.then4, !dbg !1936

if.then4:                                         ; preds = %land.lhs.true
  br label %for.inc, !dbg !1937

if.end5:                                          ; preds = %land.lhs.true, %for.body
  %12 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1938
  %type6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %12, i32 0, i32 2, !dbg !1939
  %13 = load i32, i32* %type6, align 8, !dbg !1939
  switch i32 %13, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb7
    i32 3, label %sw.bb8
    i32 4, label %sw.bb9
    i32 5, label %sw.bb10
    i32 6, label %sw.bb11
    i32 7, label %sw.bb12
    i32 8, label %sw.bb13
    i32 9, label %sw.bb14
    i32 10, label %sw.bb15
    i32 11, label %sw.bb16
    i32 12, label %sw.bb17
    i32 13, label %sw.bb18
    i32 14, label %sw.bb19
    i32 15, label %sw.bb20
    i32 16, label %sw.bb21
  ], !dbg !1940

sw.bb:                                            ; preds = %if.end5
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.156, i32 0, i32 0), i8** %type, align 8, !dbg !1941
  br label %sw.epilog, !dbg !1941

sw.bb7:                                           ; preds = %if.end5
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.157, i32 0, i32 0), i8** %type, align 8, !dbg !1943
  br label %sw.epilog, !dbg !1943

sw.bb8:                                           ; preds = %if.end5
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.158, i32 0, i32 0), i8** %type, align 8, !dbg !1945
  br label %sw.epilog, !dbg !1945

sw.bb9:                                           ; preds = %if.end5
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.159, i32 0, i32 0), i8** %type, align 8, !dbg !1947
  br label %sw.epilog, !dbg !1947

sw.bb10:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.160, i32 0, i32 0), i8** %type, align 8, !dbg !1949
  br label %sw.epilog, !dbg !1949

sw.bb11:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.161, i32 0, i32 0), i8** %type, align 8, !dbg !1951
  br label %sw.epilog, !dbg !1951

sw.bb12:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.162, i32 0, i32 0), i8** %type, align 8, !dbg !1953
  br label %sw.epilog, !dbg !1953

sw.bb13:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.163, i32 0, i32 0), i8** %type, align 8, !dbg !1955
  br label %sw.epilog, !dbg !1955

sw.bb14:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.164, i32 0, i32 0), i8** %type, align 8, !dbg !1957
  br label %sw.epilog, !dbg !1957

sw.bb15:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.165, i32 0, i32 0), i8** %type, align 8, !dbg !1959
  br label %sw.epilog, !dbg !1959

sw.bb16:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.166, i32 0, i32 0), i8** %type, align 8, !dbg !1961
  br label %sw.epilog, !dbg !1961

sw.bb17:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.167, i32 0, i32 0), i8** %type, align 8, !dbg !1963
  br label %sw.epilog, !dbg !1963

sw.bb18:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.168, i32 0, i32 0), i8** %type, align 8, !dbg !1965
  br label %sw.epilog, !dbg !1965

sw.bb19:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.169, i32 0, i32 0), i8** %type, align 8, !dbg !1967
  br label %sw.epilog, !dbg !1967

sw.bb20:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.170, i32 0, i32 0), i8** %type, align 8, !dbg !1969
  br label %sw.epilog, !dbg !1969

sw.bb21:                                          ; preds = %if.end5
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.171, i32 0, i32 0), i8** %type, align 8, !dbg !1971
  br label %sw.epilog, !dbg !1971

sw.default:                                       ; preds = %if.end5
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.172, i32 0, i32 0), i8** %type, align 8, !dbg !1973
  br label %sw.epilog, !dbg !1974

sw.epilog:                                        ; preds = %sw.default, %sw.bb21, %sw.bb20, %sw.bb19, %sw.bb18, %sw.bb17, %sw.bb16, %sw.bb15, %sw.bb14, %sw.bb13, %sw.bb12, %sw.bb11, %sw.bb10, %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !1975
  %15 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1976
  %flags22 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 7, !dbg !1977
  %16 = load i32, i32* %flags22, align 8, !dbg !1977
  %and23 = and i32 %16, 8192, !dbg !1978
  %tobool24 = icmp ne i32 %and23, 0, !dbg !1979
  %lnot = xor i1 %tobool24, true, !dbg !1979
  %lnot.ext = zext i1 %lnot to i32, !dbg !1979
  %idxprom = sext i32 %lnot.ext to i64, !dbg !1980
  %arrayidx25 = getelementptr inbounds [3 x i8], [3 x i8]* @.str.174, i64 0, i64 %idxprom, !dbg !1980
  %17 = load i8, i8* %arrayidx25, align 1, !dbg !1980
  %conv = sext i8 %17 to i32, !dbg !1980
  %18 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1981
  %flags26 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 7, !dbg !1982
  %19 = load i32, i32* %flags26, align 8, !dbg !1982
  %and27 = and i32 %19, 16384, !dbg !1983
  %tobool28 = icmp ne i32 %and27, 0, !dbg !1984
  %lnot29 = xor i1 %tobool28, true, !dbg !1984
  %lnot.ext30 = zext i1 %lnot29 to i32, !dbg !1984
  %idxprom31 = sext i32 %lnot.ext30 to i64, !dbg !1985
  %arrayidx32 = getelementptr inbounds [3 x i8], [3 x i8]* @.str.175, i64 0, i64 %idxprom31, !dbg !1985
  %20 = load i8, i8* %arrayidx32, align 1, !dbg !1985
  %conv33 = sext i8 %20 to i32, !dbg !1985
  %21 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1986
  %flags34 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %21, i32 0, i32 7, !dbg !1987
  %22 = load i32, i32* %flags34, align 8, !dbg !1987
  %and35 = and i32 %22, 32768, !dbg !1988
  %tobool36 = icmp ne i32 %and35, 0, !dbg !1989
  %lnot37 = xor i1 %tobool36, true, !dbg !1989
  %lnot.ext38 = zext i1 %lnot37 to i32, !dbg !1989
  %idxprom39 = sext i32 %lnot.ext38 to i64, !dbg !1990
  %arrayidx40 = getelementptr inbounds [3 x i8], [3 x i8]* @.str.176, i64 0, i64 %idxprom39, !dbg !1990
  %23 = load i8, i8* %arrayidx40, align 1, !dbg !1990
  %conv41 = sext i8 %23 to i32, !dbg !1990
  %24 = load i8*, i8** %type, align 8, !dbg !1991
  %25 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !1992
  %26 = bitcast %struct.uv_handle_s* %25 to i8*, !dbg !1993
  %call42 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %14, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.173, i32 0, i32 0), i32 %conv, i32 %conv33, i32 %conv41, i8* %24, i8* %26), !dbg !1994
  br label %for.inc, !dbg !1995

for.inc:                                          ; preds = %sw.epilog, %if.then4
  %27 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1996
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %27, i64 0, i64 0, !dbg !1996
  %28 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !1996
  %29 = load [2 x i8*]*, [2 x i8*]** %28, align 8, !dbg !1996
  store [2 x i8*]* %29, [2 x i8*]** %q, align 8, !dbg !1996
  br label %for.cond, !dbg !1996

for.end:                                          ; preds = %for.cond
  ret void, !dbg !1998
}

; Function Attrs: nounwind uwtable
define void @uv_print_active_handles(%struct.uv_loop_s* %loop, %struct._IO_FILE* %stream) #0 !dbg !755 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %stream.addr = alloca %struct._IO_FILE*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1999, metadata !936), !dbg !2000
  store %struct._IO_FILE* %stream, %struct._IO_FILE** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %stream.addr, metadata !2001, metadata !936), !dbg !2002
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2003
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !2004
  call void @uv__print_handles(%struct.uv_loop_s* %0, i32 1, %struct._IO_FILE* %1), !dbg !2005
  ret void, !dbg !2006
}

; Function Attrs: nounwind uwtable
define void @uv_ref(%struct.uv_handle_s* %handle) #0 !dbg !756 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !2007, metadata !936), !dbg !2008
  br label %do.body, !dbg !2009

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2010
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !2010
  %1 = load i32, i32* %flags, align 8, !dbg !2010
  %and = and i32 %1, 8192, !dbg !2010
  %cmp = icmp ne i32 %and, 0, !dbg !2010
  br i1 %cmp, label %if.then, label %if.end, !dbg !2010

if.then:                                          ; preds = %do.body
  br label %do.end13, !dbg !2014

if.end:                                           ; preds = %do.body
  %2 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2016
  %flags1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 7, !dbg !2016
  %3 = load i32, i32* %flags1, align 8, !dbg !2016
  %or = or i32 %3, 8192, !dbg !2016
  store i32 %or, i32* %flags1, align 8, !dbg !2016
  %4 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2016
  %flags2 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 7, !dbg !2016
  %5 = load i32, i32* %flags2, align 8, !dbg !2016
  %and3 = and i32 %5, 0, !dbg !2016
  %cmp4 = icmp ne i32 %and3, 0, !dbg !2016
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2016

if.then5:                                         ; preds = %if.end
  br label %do.end13, !dbg !2018

if.end6:                                          ; preds = %if.end
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2021
  %flags7 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !2021
  %7 = load i32, i32* %flags7, align 8, !dbg !2021
  %and8 = and i32 %7, 16384, !dbg !2021
  %cmp9 = icmp ne i32 %and8, 0, !dbg !2021
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !2021

if.then10:                                        ; preds = %if.end6
  br label %do.body11, !dbg !2024

do.body11:                                        ; preds = %if.then10
  %8 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2026
  %loop = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %8, i32 0, i32 1, !dbg !2026
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2026
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 1, !dbg !2026
  %10 = load i32, i32* %active_handles, align 8, !dbg !2026
  %inc = add i32 %10, 1, !dbg !2026
  store i32 %inc, i32* %active_handles, align 8, !dbg !2026
  br label %do.end, !dbg !2026

do.end:                                           ; preds = %do.body11
  br label %if.end12, !dbg !2029

if.end12:                                         ; preds = %do.end, %if.end6
  br label %do.end13, !dbg !2031

do.end13:                                         ; preds = %if.end12, %if.then5, %if.then
  ret void, !dbg !2033
}

; Function Attrs: nounwind uwtable
define void @uv_unref(%struct.uv_handle_s* %handle) #0 !dbg !757 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !2034, metadata !936), !dbg !2035
  br label %do.body, !dbg !2036

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2037
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !2037
  %1 = load i32, i32* %flags, align 8, !dbg !2037
  %and = and i32 %1, 8192, !dbg !2037
  %cmp = icmp eq i32 %and, 0, !dbg !2037
  br i1 %cmp, label %if.then, label %if.end, !dbg !2037

if.then:                                          ; preds = %do.body
  br label %do.end14, !dbg !2041

if.end:                                           ; preds = %do.body
  %2 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2043
  %flags1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 7, !dbg !2043
  %3 = load i32, i32* %flags1, align 8, !dbg !2043
  %and2 = and i32 %3, -8193, !dbg !2043
  store i32 %and2, i32* %flags1, align 8, !dbg !2043
  %4 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2043
  %flags3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 7, !dbg !2043
  %5 = load i32, i32* %flags3, align 8, !dbg !2043
  %and4 = and i32 %5, 0, !dbg !2043
  %cmp5 = icmp ne i32 %and4, 0, !dbg !2043
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2043

if.then6:                                         ; preds = %if.end
  br label %do.end14, !dbg !2045

if.end7:                                          ; preds = %if.end
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2048
  %flags8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !2048
  %7 = load i32, i32* %flags8, align 8, !dbg !2048
  %and9 = and i32 %7, 16384, !dbg !2048
  %cmp10 = icmp ne i32 %and9, 0, !dbg !2048
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !2048

if.then11:                                        ; preds = %if.end7
  br label %do.body12, !dbg !2051

do.body12:                                        ; preds = %if.then11
  %8 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2053
  %loop = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %8, i32 0, i32 1, !dbg !2053
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2053
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 1, !dbg !2053
  %10 = load i32, i32* %active_handles, align 8, !dbg !2053
  %dec = add i32 %10, -1, !dbg !2053
  store i32 %dec, i32* %active_handles, align 8, !dbg !2053
  br label %do.end, !dbg !2053

do.end:                                           ; preds = %do.body12
  br label %if.end13, !dbg !2056

if.end13:                                         ; preds = %do.end, %if.end7
  br label %do.end14, !dbg !2058

do.end14:                                         ; preds = %if.end13, %if.then6, %if.then
  ret void, !dbg !2060
}

; Function Attrs: nounwind uwtable
define i32 @uv_has_ref(%struct.uv_handle_s* %handle) #0 !dbg !758 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !2061, metadata !936), !dbg !2062
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2063
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !2063
  %1 = load i32, i32* %flags, align 8, !dbg !2063
  %and = and i32 %1, 8192, !dbg !2063
  %cmp = icmp ne i32 %and, 0, !dbg !2063
  %conv = zext i1 %cmp to i32, !dbg !2063
  ret i32 %conv, !dbg !2064
}

; Function Attrs: nounwind uwtable
define void @uv_stop(%struct.uv_loop_s* %loop) #0 !dbg !763 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2065, metadata !936), !dbg !2066
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2067
  %stop_flag = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 4, !dbg !2068
  store i32 1, i32* %stop_flag, align 8, !dbg !2069
  ret void, !dbg !2070
}

; Function Attrs: nounwind uwtable
define i64 @uv_now(%struct.uv_loop_s* %loop) #0 !dbg !766 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2071, metadata !936), !dbg !2072
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2073
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 27, !dbg !2074
  %1 = load i64, i64* %time, align 8, !dbg !2074
  ret i64 %1, !dbg !2075
}

; Function Attrs: nounwind uwtable
define i64 @uv__count_bufs(%struct.uv_buf_t* %bufs, i32 %nbufs) #0 !dbg !771 {
entry:
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %i = alloca i32, align 4
  %bytes = alloca i64, align 8
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !2076, metadata !936), !dbg !2077
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !2078, metadata !936), !dbg !2079
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2080, metadata !936), !dbg !2081
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !2082, metadata !936), !dbg !2083
  store i64 0, i64* %bytes, align 8, !dbg !2084
  store i32 0, i32* %i, align 4, !dbg !2085
  br label %for.cond, !dbg !2087

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !2088
  %1 = load i32, i32* %nbufs.addr, align 4, !dbg !2091
  %cmp = icmp ult i32 %0, %1, !dbg !2092
  br i1 %cmp, label %for.body, label %for.end, !dbg !2093

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !2094
  %idxprom = zext i32 %2 to i64, !dbg !2095
  %3 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !2095
  %arrayidx = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %3, i64 %idxprom, !dbg !2095
  %len = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx, i32 0, i32 1, !dbg !2096
  %4 = load i64, i64* %len, align 8, !dbg !2096
  %5 = load i64, i64* %bytes, align 8, !dbg !2097
  %add = add i64 %5, %4, !dbg !2097
  store i64 %add, i64* %bytes, align 8, !dbg !2097
  br label %for.inc, !dbg !2098

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %i, align 4, !dbg !2099
  %inc = add i32 %6, 1, !dbg !2099
  store i32 %inc, i32* %i, align 4, !dbg !2099
  br label %for.cond, !dbg !2101

for.end:                                          ; preds = %for.cond
  %7 = load i64, i64* %bytes, align 8, !dbg !2102
  ret i64 %7, !dbg !2103
}

; Function Attrs: nounwind uwtable
define i32 @uv_recv_buffer_size(%struct.uv_handle_s* %handle, i32* %value) #0 !dbg !774 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  %value.addr = alloca i32*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !2104, metadata !936), !dbg !2105
  store i32* %value, i32** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %value.addr, metadata !2106, metadata !936), !dbg !2107
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2108
  %1 = load i32*, i32** %value.addr, align 8, !dbg !2109
  %call = call i32 @uv__socket_sockopt(%struct.uv_handle_s* %0, i32 8, i32* %1), !dbg !2110
  ret i32 %call, !dbg !2111
}

declare i32 @uv__socket_sockopt(%struct.uv_handle_s*, i32, i32*) #5

; Function Attrs: nounwind uwtable
define i32 @uv_send_buffer_size(%struct.uv_handle_s* %handle, i32* %value) #0 !dbg !778 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  %value.addr = alloca i32*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !2112, metadata !936), !dbg !2113
  store i32* %value, i32** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %value.addr, metadata !2114, metadata !936), !dbg !2115
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2116
  %1 = load i32*, i32** %value.addr, align 8, !dbg !2117
  %call = call i32 @uv__socket_sockopt(%struct.uv_handle_s* %0, i32 7, i32* %1), !dbg !2118
  ret i32 %call, !dbg !2119
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_event_getpath(%struct.uv_fs_event_s* %handle, i8* %buffer, i64* %size) #0 !dbg !779 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_fs_event_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %required_len = alloca i64, align 8
  store %struct.uv_fs_event_s* %handle, %struct.uv_fs_event_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %handle.addr, metadata !2120, metadata !936), !dbg !2121
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !2122, metadata !936), !dbg !2123
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !2124, metadata !936), !dbg !2125
  call void @llvm.dbg.declare(metadata i64* %required_len, metadata !2126, metadata !936), !dbg !2127
  %0 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !2128
  %flags = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %0, i32 0, i32 7, !dbg !2128
  %1 = load i32, i32* %flags, align 8, !dbg !2128
  %and = and i32 %1, 16384, !dbg !2128
  %cmp = icmp ne i32 %and, 0, !dbg !2128
  br i1 %cmp, label %if.end, label %if.then, !dbg !2130

if.then:                                          ; preds = %entry
  %2 = load i64*, i64** %size.addr, align 8, !dbg !2131
  store i64 0, i64* %2, align 8, !dbg !2133
  store i32 -22, i32* %retval, align 4, !dbg !2134
  br label %return, !dbg !2134

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !2135
  %path = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %3, i32 0, i32 8, !dbg !2136
  %4 = load i8*, i8** %path, align 8, !dbg !2136
  %call = call i64 @strlen(i8* %4) #9, !dbg !2137
  store i64 %call, i64* %required_len, align 8, !dbg !2138
  %5 = load i64, i64* %required_len, align 8, !dbg !2139
  %6 = load i64*, i64** %size.addr, align 8, !dbg !2141
  %7 = load i64, i64* %6, align 8, !dbg !2142
  %cmp1 = icmp uge i64 %5, %7, !dbg !2143
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2144

if.then2:                                         ; preds = %if.end
  %8 = load i64, i64* %required_len, align 8, !dbg !2145
  %add = add i64 %8, 1, !dbg !2147
  %9 = load i64*, i64** %size.addr, align 8, !dbg !2148
  store i64 %add, i64* %9, align 8, !dbg !2149
  store i32 -105, i32* %retval, align 4, !dbg !2150
  br label %return, !dbg !2150

if.end3:                                          ; preds = %if.end
  %10 = load i8*, i8** %buffer.addr, align 8, !dbg !2151
  %11 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !2152
  %path4 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %11, i32 0, i32 8, !dbg !2153
  %12 = load i8*, i8** %path4, align 8, !dbg !2153
  %13 = load i64, i64* %required_len, align 8, !dbg !2154
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* %12, i64 %13, i32 1, i1 false), !dbg !2155
  %14 = load i64, i64* %required_len, align 8, !dbg !2156
  %15 = load i64*, i64** %size.addr, align 8, !dbg !2157
  store i64 %14, i64* %15, align 8, !dbg !2158
  %16 = load i64, i64* %required_len, align 8, !dbg !2159
  %17 = load i8*, i8** %buffer.addr, align 8, !dbg !2160
  %arrayidx = getelementptr inbounds i8, i8* %17, i64 %16, !dbg !2160
  store i8 0, i8* %arrayidx, align 1, !dbg !2161
  store i32 0, i32* %retval, align 4, !dbg !2162
  br label %return, !dbg !2162

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !2163
  ret i32 %18, !dbg !2163
}

; Function Attrs: nounwind uwtable
define void @uv__fs_scandir_cleanup(%struct.uv_fs_s* %req) #0 !dbg !807 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %dents = alloca %struct.dirent**, align 8
  %nbufs = alloca i32*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2164, metadata !936), !dbg !2165
  call void @llvm.dbg.declare(metadata %struct.dirent*** %dents, metadata !2166, metadata !936), !dbg !2182
  call void @llvm.dbg.declare(metadata i32** %nbufs, metadata !2183, metadata !936), !dbg !2184
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2185
  %call = call i32* @uv__get_nbufs(%struct.uv_fs_s* %0), !dbg !2186
  store i32* %call, i32** %nbufs, align 8, !dbg !2184
  %1 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2187
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %1, i32 0, i32 8, !dbg !2188
  %2 = load i8*, i8** %ptr, align 8, !dbg !2188
  %3 = bitcast i8* %2 to %struct.dirent**, !dbg !2187
  store %struct.dirent** %3, %struct.dirent*** %dents, align 8, !dbg !2189
  %4 = load i32*, i32** %nbufs, align 8, !dbg !2190
  %5 = load i32, i32* %4, align 4, !dbg !2192
  %cmp = icmp ugt i32 %5, 0, !dbg !2193
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2194

land.lhs.true:                                    ; preds = %entry
  %6 = load i32*, i32** %nbufs, align 8, !dbg !2195
  %7 = load i32, i32* %6, align 4, !dbg !2197
  %8 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2198
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %8, i32 0, i32 7, !dbg !2199
  %9 = load i64, i64* %result, align 8, !dbg !2199
  %conv = trunc i64 %9 to i32, !dbg !2200
  %cmp1 = icmp ne i32 %7, %conv, !dbg !2201
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2202

if.then:                                          ; preds = %land.lhs.true
  %10 = load i32*, i32** %nbufs, align 8, !dbg !2203
  %11 = load i32, i32* %10, align 4, !dbg !2204
  %dec = add i32 %11, -1, !dbg !2204
  store i32 %dec, i32* %10, align 4, !dbg !2204
  br label %if.end, !dbg !2205

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  br label %for.cond, !dbg !2206

for.cond:                                         ; preds = %for.inc, %if.end
  %12 = load i32*, i32** %nbufs, align 8, !dbg !2207
  %13 = load i32, i32* %12, align 4, !dbg !2211
  %14 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2212
  %result3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %14, i32 0, i32 7, !dbg !2213
  %15 = load i64, i64* %result3, align 8, !dbg !2213
  %conv4 = trunc i64 %15 to i32, !dbg !2214
  %cmp5 = icmp ult i32 %13, %conv4, !dbg !2215
  br i1 %cmp5, label %for.body, label %for.end, !dbg !2216

for.body:                                         ; preds = %for.cond
  %16 = load i32*, i32** %nbufs, align 8, !dbg !2217
  %17 = load i32, i32* %16, align 4, !dbg !2218
  %idxprom = zext i32 %17 to i64, !dbg !2219
  %18 = load %struct.dirent**, %struct.dirent*** %dents, align 8, !dbg !2219
  %arrayidx = getelementptr inbounds %struct.dirent*, %struct.dirent** %18, i64 %idxprom, !dbg !2219
  %19 = load %struct.dirent*, %struct.dirent** %arrayidx, align 8, !dbg !2219
  %20 = bitcast %struct.dirent* %19 to i8*, !dbg !2219
  call void @free(i8* %20) #8, !dbg !2220
  br label %for.inc, !dbg !2220

for.inc:                                          ; preds = %for.body
  %21 = load i32*, i32** %nbufs, align 8, !dbg !2221
  %22 = load i32, i32* %21, align 4, !dbg !2223
  %inc = add i32 %22, 1, !dbg !2223
  store i32 %inc, i32* %21, align 4, !dbg !2223
  br label %for.cond, !dbg !2224

for.end:                                          ; preds = %for.cond
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %ptr7 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 8, !dbg !2226
  %24 = load i8*, i8** %ptr7, align 8, !dbg !2226
  call void @free(i8* %24) #8, !dbg !2227
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2228
  %ptr8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 8, !dbg !2229
  store i8* null, i8** %ptr8, align 8, !dbg !2230
  ret void, !dbg !2231
}

; Function Attrs: nounwind uwtable
define internal i32* @uv__get_nbufs(%struct.uv_fs_s* %req) #0 !dbg !917 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2232, metadata !936), !dbg !2233
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2234
  %nbufs = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 15, !dbg !2235
  ret i32* %nbufs, !dbg !2236
}

; Function Attrs: nounwind
declare void @free(i8*) #6

; Function Attrs: nounwind uwtable
define i32 @uv_fs_scandir_next(%struct.uv_fs_s* %req, %struct.uv_dirent_s* %ent) #0 !dbg !891 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %ent.addr = alloca %struct.uv_dirent_s*, align 8
  %dents = alloca %struct.dirent**, align 8
  %dent = alloca %struct.dirent*, align 8
  %nbufs = alloca i32*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2237, metadata !936), !dbg !2238
  store %struct.uv_dirent_s* %ent, %struct.uv_dirent_s** %ent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_dirent_s** %ent.addr, metadata !2239, metadata !936), !dbg !2240
  call void @llvm.dbg.declare(metadata %struct.dirent*** %dents, metadata !2241, metadata !936), !dbg !2242
  call void @llvm.dbg.declare(metadata %struct.dirent** %dent, metadata !2243, metadata !936), !dbg !2244
  call void @llvm.dbg.declare(metadata i32** %nbufs, metadata !2245, metadata !936), !dbg !2246
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2247
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 7, !dbg !2249
  %1 = load i64, i64* %result, align 8, !dbg !2249
  %cmp = icmp slt i64 %1, 0, !dbg !2250
  br i1 %cmp, label %if.then, label %if.end, !dbg !2251

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2252
  %result1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 7, !dbg !2253
  %3 = load i64, i64* %result1, align 8, !dbg !2253
  %conv = trunc i64 %3 to i32, !dbg !2252
  store i32 %conv, i32* %retval, align 4, !dbg !2254
  br label %return, !dbg !2254

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2255
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 8, !dbg !2257
  %5 = load i8*, i8** %ptr, align 8, !dbg !2257
  %tobool = icmp ne i8* %5, null, !dbg !2255
  br i1 %tobool, label %if.end3, label %if.then2, !dbg !2258

if.then2:                                         ; preds = %if.end
  store i32 -4095, i32* %retval, align 4, !dbg !2259
  br label %return, !dbg !2259

if.end3:                                          ; preds = %if.end
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2260
  %call = call i32* @uv__get_nbufs(%struct.uv_fs_s* %6), !dbg !2261
  store i32* %call, i32** %nbufs, align 8, !dbg !2262
  %7 = load i32*, i32** %nbufs, align 8, !dbg !2263
  %tobool4 = icmp ne i32* %7, null, !dbg !2263
  br i1 %tobool4, label %cond.true, label %cond.false, !dbg !2263

cond.true:                                        ; preds = %if.end3
  br label %cond.end, !dbg !2264

cond.false:                                       ; preds = %if.end3
  call void @__assert_fail(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.151, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.152, i32 0, i32 0), i32 526, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @__PRETTY_FUNCTION__.uv_fs_scandir_next, i32 0, i32 0)) #10, !dbg !2266
  unreachable, !dbg !2266
                                                  ; No predecessors!
  br label %cond.end, !dbg !2268

cond.end:                                         ; preds = %8, %cond.true
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2270
  %ptr5 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 8, !dbg !2271
  %10 = load i8*, i8** %ptr5, align 8, !dbg !2271
  %11 = bitcast i8* %10 to %struct.dirent**, !dbg !2270
  store %struct.dirent** %11, %struct.dirent*** %dents, align 8, !dbg !2272
  %12 = load i32*, i32** %nbufs, align 8, !dbg !2273
  %13 = load i32, i32* %12, align 4, !dbg !2275
  %cmp6 = icmp ugt i32 %13, 0, !dbg !2276
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !2277

if.then8:                                         ; preds = %cond.end
  %14 = load i32*, i32** %nbufs, align 8, !dbg !2278
  %15 = load i32, i32* %14, align 4, !dbg !2279
  %sub = sub i32 %15, 1, !dbg !2280
  %idxprom = zext i32 %sub to i64, !dbg !2281
  %16 = load %struct.dirent**, %struct.dirent*** %dents, align 8, !dbg !2281
  %arrayidx = getelementptr inbounds %struct.dirent*, %struct.dirent** %16, i64 %idxprom, !dbg !2281
  %17 = load %struct.dirent*, %struct.dirent** %arrayidx, align 8, !dbg !2281
  %18 = bitcast %struct.dirent* %17 to i8*, !dbg !2281
  call void @free(i8* %18) #8, !dbg !2282
  br label %if.end9, !dbg !2282

if.end9:                                          ; preds = %if.then8, %cond.end
  %19 = load i32*, i32** %nbufs, align 8, !dbg !2283
  %20 = load i32, i32* %19, align 4, !dbg !2285
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2286
  %result10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 7, !dbg !2287
  %22 = load i64, i64* %result10, align 8, !dbg !2287
  %conv11 = trunc i64 %22 to i32, !dbg !2288
  %cmp12 = icmp eq i32 %20, %conv11, !dbg !2289
  br i1 %cmp12, label %if.then14, label %if.end16, !dbg !2290

if.then14:                                        ; preds = %if.end9
  %23 = load %struct.dirent**, %struct.dirent*** %dents, align 8, !dbg !2291
  %24 = bitcast %struct.dirent** %23 to i8*, !dbg !2291
  call void @free(i8* %24) #8, !dbg !2293
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2294
  %ptr15 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 8, !dbg !2295
  store i8* null, i8** %ptr15, align 8, !dbg !2296
  store i32 -4095, i32* %retval, align 4, !dbg !2297
  br label %return, !dbg !2297

if.end16:                                         ; preds = %if.end9
  %26 = load i32*, i32** %nbufs, align 8, !dbg !2298
  %27 = load i32, i32* %26, align 4, !dbg !2299
  %inc = add i32 %27, 1, !dbg !2299
  store i32 %inc, i32* %26, align 4, !dbg !2299
  %idxprom17 = zext i32 %27 to i64, !dbg !2300
  %28 = load %struct.dirent**, %struct.dirent*** %dents, align 8, !dbg !2300
  %arrayidx18 = getelementptr inbounds %struct.dirent*, %struct.dirent** %28, i64 %idxprom17, !dbg !2300
  %29 = load %struct.dirent*, %struct.dirent** %arrayidx18, align 8, !dbg !2300
  store %struct.dirent* %29, %struct.dirent** %dent, align 8, !dbg !2301
  %30 = load %struct.dirent*, %struct.dirent** %dent, align 8, !dbg !2302
  %d_name = getelementptr inbounds %struct.dirent, %struct.dirent* %30, i32 0, i32 4, !dbg !2303
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %d_name, i32 0, i32 0, !dbg !2302
  %31 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2304
  %name = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %31, i32 0, i32 0, !dbg !2305
  store i8* %arraydecay, i8** %name, align 8, !dbg !2306
  %32 = load %struct.dirent*, %struct.dirent** %dent, align 8, !dbg !2307
  %d_type = getelementptr inbounds %struct.dirent, %struct.dirent* %32, i32 0, i32 3, !dbg !2308
  %33 = load i8, i8* %d_type, align 2, !dbg !2308
  %conv19 = zext i8 %33 to i32, !dbg !2307
  switch i32 %conv19, label %sw.default [
    i32 4, label %sw.bb
    i32 8, label %sw.bb20
    i32 10, label %sw.bb22
    i32 1, label %sw.bb24
    i32 12, label %sw.bb26
    i32 2, label %sw.bb28
    i32 6, label %sw.bb30
  ], !dbg !2309

sw.bb:                                            ; preds = %if.end16
  %34 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2310
  %type = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %34, i32 0, i32 1, !dbg !2312
  store i32 2, i32* %type, align 8, !dbg !2313
  br label %sw.epilog, !dbg !2314

sw.bb20:                                          ; preds = %if.end16
  %35 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2315
  %type21 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %35, i32 0, i32 1, !dbg !2316
  store i32 1, i32* %type21, align 8, !dbg !2317
  br label %sw.epilog, !dbg !2318

sw.bb22:                                          ; preds = %if.end16
  %36 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2319
  %type23 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %36, i32 0, i32 1, !dbg !2320
  store i32 3, i32* %type23, align 8, !dbg !2321
  br label %sw.epilog, !dbg !2322

sw.bb24:                                          ; preds = %if.end16
  %37 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2323
  %type25 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %37, i32 0, i32 1, !dbg !2324
  store i32 4, i32* %type25, align 8, !dbg !2325
  br label %sw.epilog, !dbg !2326

sw.bb26:                                          ; preds = %if.end16
  %38 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2327
  %type27 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %38, i32 0, i32 1, !dbg !2328
  store i32 5, i32* %type27, align 8, !dbg !2329
  br label %sw.epilog, !dbg !2330

sw.bb28:                                          ; preds = %if.end16
  %39 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2331
  %type29 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %39, i32 0, i32 1, !dbg !2332
  store i32 6, i32* %type29, align 8, !dbg !2333
  br label %sw.epilog, !dbg !2334

sw.bb30:                                          ; preds = %if.end16
  %40 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2335
  %type31 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %40, i32 0, i32 1, !dbg !2336
  store i32 7, i32* %type31, align 8, !dbg !2337
  br label %sw.epilog, !dbg !2338

sw.default:                                       ; preds = %if.end16
  %41 = load %struct.uv_dirent_s*, %struct.uv_dirent_s** %ent.addr, align 8, !dbg !2339
  %type32 = getelementptr inbounds %struct.uv_dirent_s, %struct.uv_dirent_s* %41, i32 0, i32 1, !dbg !2340
  store i32 0, i32* %type32, align 8, !dbg !2341
  br label %sw.epilog, !dbg !2342

sw.epilog:                                        ; preds = %sw.default, %sw.bb30, %sw.bb28, %sw.bb26, %sw.bb24, %sw.bb22, %sw.bb20, %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !2343
  br label %return, !dbg !2343

return:                                           ; preds = %sw.epilog, %if.then14, %if.then2, %if.then
  %42 = load i32, i32* %retval, align 4, !dbg !2344
  ret i32 %42, !dbg !2344
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #7

; Function Attrs: nounwind uwtable
define i32 @uv_loop_configure(%struct.uv_loop_s* %loop, i32 %option, ...) #0 !dbg !901 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %option.addr = alloca i32, align 4
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2345, metadata !936), !dbg !2346
  store i32 %option, i32* %option.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option.addr, metadata !2347, metadata !936), !dbg !2348
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap, metadata !2349, metadata !936), !dbg !2361
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2362, metadata !936), !dbg !2363
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !2364
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !2364
  call void @llvm.va_start(i8* %arraydecay1), !dbg !2364
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2365
  %1 = load i32, i32* %option.addr, align 4, !dbg !2366
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !2367
  %call = call i32 @uv__loop_configure(%struct.uv_loop_s* %0, i32 %1, %struct.__va_list_tag* %arraydecay2), !dbg !2368
  store i32 %call, i32* %err, align 4, !dbg !2369
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !2370
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !2370
  call void @llvm.va_end(i8* %arraydecay34), !dbg !2370
  %2 = load i32, i32* %err, align 4, !dbg !2371
  ret i32 %2, !dbg !2372
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #8

declare i32 @uv__loop_configure(%struct.uv_loop_s*, i32, %struct.__va_list_tag*) #5

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #8

; Function Attrs: nounwind uwtable
define %struct.uv_loop_s* @uv_default_loop() #0 !dbg !905 {
entry:
  %retval = alloca %struct.uv_loop_s*, align 8
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2373
  %cmp = icmp ne %struct.uv_loop_s* %0, null, !dbg !2375
  br i1 %cmp, label %if.then, label %if.end, !dbg !2376

if.then:                                          ; preds = %entry
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2377
  store %struct.uv_loop_s* %1, %struct.uv_loop_s** %retval, align 8, !dbg !2378
  br label %return, !dbg !2378

if.end:                                           ; preds = %entry
  %call = call i32 @uv_loop_init(%struct.uv_loop_s* @default_loop_struct), !dbg !2379
  %tobool = icmp ne i32 %call, 0, !dbg !2379
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !2381

if.then1:                                         ; preds = %if.end
  store %struct.uv_loop_s* null, %struct.uv_loop_s** %retval, align 8, !dbg !2382
  br label %return, !dbg !2382

if.end2:                                          ; preds = %if.end
  store %struct.uv_loop_s* @default_loop_struct, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2383
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2384
  store %struct.uv_loop_s* %2, %struct.uv_loop_s** %retval, align 8, !dbg !2385
  br label %return, !dbg !2385

return:                                           ; preds = %if.end2, %if.then1, %if.then
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %retval, align 8, !dbg !2386
  ret %struct.uv_loop_s* %3, !dbg !2386
}

declare i32 @uv_loop_init(%struct.uv_loop_s*) #5

; Function Attrs: nounwind uwtable
define %struct.uv_loop_s* @uv_loop_new() #0 !dbg !908 {
entry:
  %retval = alloca %struct.uv_loop_s*, align 8
  %loop = alloca %struct.uv_loop_s*, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop, metadata !2387, metadata !936), !dbg !2388
  %call = call i8* @uv__malloc(i64 848), !dbg !2389
  %0 = bitcast i8* %call to %struct.uv_loop_s*, !dbg !2389
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop, align 8, !dbg !2390
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2391
  %cmp = icmp eq %struct.uv_loop_s* %1, null, !dbg !2393
  br i1 %cmp, label %if.then, label %if.end, !dbg !2394

if.then:                                          ; preds = %entry
  store %struct.uv_loop_s* null, %struct.uv_loop_s** %retval, align 8, !dbg !2395
  br label %return, !dbg !2395

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2396
  %call1 = call i32 @uv_loop_init(%struct.uv_loop_s* %2), !dbg !2398
  %tobool = icmp ne i32 %call1, 0, !dbg !2398
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !2399

if.then2:                                         ; preds = %if.end
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2400
  %4 = bitcast %struct.uv_loop_s* %3 to i8*, !dbg !2400
  call void @uv__free(i8* %4), !dbg !2402
  store %struct.uv_loop_s* null, %struct.uv_loop_s** %retval, align 8, !dbg !2403
  br label %return, !dbg !2403

if.end3:                                          ; preds = %if.end
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2404
  store %struct.uv_loop_s* %5, %struct.uv_loop_s** %retval, align 8, !dbg !2405
  br label %return, !dbg !2405

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %retval, align 8, !dbg !2406
  ret %struct.uv_loop_s* %6, !dbg !2406
}

; Function Attrs: nounwind uwtable
define i32 @uv_loop_close(%struct.uv_loop_s* %loop) #0 !dbg !909 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  %h = alloca %struct.uv_handle_s*, align 8
  %saved_data = alloca i8*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2407, metadata !936), !dbg !2408
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !2409, metadata !936), !dbg !2410
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %h, metadata !2411, metadata !936), !dbg !2412
  call void @llvm.dbg.declare(metadata i8** %saved_data, metadata !2413, metadata !936), !dbg !2414
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2415
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 3, !dbg !2415
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2415
  %active_reqs1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 3, !dbg !2415
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs1, i64 0, i64 0, !dbg !2415
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2415
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !2415
  %cmp = icmp eq [2 x i8*]* %active_reqs, %3, !dbg !2415
  br i1 %cmp, label %if.end, label %if.then, !dbg !2417

if.then:                                          ; preds = %entry
  store i32 -16, i32* %retval, align 4, !dbg !2418
  br label %return, !dbg !2418

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2419
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 2, !dbg !2419
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue, i64 0, i64 0, !dbg !2419
  %5 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !2419
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !2419
  store [2 x i8*]* %6, [2 x i8*]** %q, align 8, !dbg !2419
  br label %for.cond, !dbg !2419

for.cond:                                         ; preds = %for.inc, %if.end
  %7 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !2421
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2421
  %handle_queue3 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 2, !dbg !2421
  %cmp4 = icmp ne [2 x i8*]* %7, %handle_queue3, !dbg !2421
  br i1 %cmp4, label %for.body, label %for.end, !dbg !2421

for.body:                                         ; preds = %for.cond
  %9 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !2424
  %10 = bitcast [2 x i8*]* %9 to i8*, !dbg !2424
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 -32, !dbg !2424
  %11 = bitcast i8* %add.ptr to %struct.uv_handle_s*, !dbg !2424
  store %struct.uv_handle_s* %11, %struct.uv_handle_s** %h, align 8, !dbg !2426
  %12 = load %struct.uv_handle_s*, %struct.uv_handle_s** %h, align 8, !dbg !2427
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %12, i32 0, i32 7, !dbg !2429
  %13 = load i32, i32* %flags, align 8, !dbg !2429
  %and = and i32 %13, 32768, !dbg !2430
  %tobool = icmp ne i32 %and, 0, !dbg !2430
  br i1 %tobool, label %if.end6, label %if.then5, !dbg !2431

if.then5:                                         ; preds = %for.body
  store i32 -16, i32* %retval, align 4, !dbg !2432
  br label %return, !dbg !2432

if.end6:                                          ; preds = %for.body
  br label %for.inc, !dbg !2433

for.inc:                                          ; preds = %if.end6
  %14 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !2434
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2434
  %15 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2434
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !2434
  store [2 x i8*]* %16, [2 x i8*]** %q, align 8, !dbg !2434
  br label %for.cond, !dbg !2434

for.end:                                          ; preds = %for.cond
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2436
  call void @uv__loop_close(%struct.uv_loop_s* %17), !dbg !2437
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2438
  %data = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 0, !dbg !2439
  %19 = load i8*, i8** %data, align 8, !dbg !2439
  store i8* %19, i8** %saved_data, align 8, !dbg !2440
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2441
  %21 = bitcast %struct.uv_loop_s* %20 to i8*, !dbg !2442
  call void @llvm.memset.p0i8.i64(i8* %21, i8 -1, i64 848, i32 8, i1 false), !dbg !2442
  %22 = load i8*, i8** %saved_data, align 8, !dbg !2443
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2444
  %data8 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 0, !dbg !2445
  store i8* %22, i8** %data8, align 8, !dbg !2446
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2447
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2449
  %cmp9 = icmp eq %struct.uv_loop_s* %24, %25, !dbg !2450
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !2451

if.then10:                                        ; preds = %for.end
  store %struct.uv_loop_s* null, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2452
  br label %if.end11, !dbg !2453

if.end11:                                         ; preds = %if.then10, %for.end
  store i32 0, i32* %retval, align 4, !dbg !2454
  br label %return, !dbg !2454

return:                                           ; preds = %if.end11, %if.then5, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !2455
  ret i32 %26, !dbg !2455
}

declare void @uv__loop_close(%struct.uv_loop_s*) #5

; Function Attrs: nounwind uwtable
define void @uv_loop_delete(%struct.uv_loop_s* %loop) #0 !dbg !912 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %default_loop = alloca %struct.uv_loop_s*, align 8
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2456, metadata !936), !dbg !2457
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %default_loop, metadata !2458, metadata !936), !dbg !2459
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2460, metadata !936), !dbg !2461
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** @default_loop_ptr, align 8, !dbg !2462
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %default_loop, align 8, !dbg !2463
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2464
  %call = call i32 @uv_loop_close(%struct.uv_loop_s* %1), !dbg !2465
  store i32 %call, i32* %err, align 4, !dbg !2466
  %2 = load i32, i32* %err, align 4, !dbg !2467
  %3 = load i32, i32* %err, align 4, !dbg !2468
  %cmp = icmp eq i32 %3, 0, !dbg !2468
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2468

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2469

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.153, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.152, i32 0, i32 0), i32 661, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv_loop_delete, i32 0, i32 0)) #10, !dbg !2471
  unreachable, !dbg !2471
                                                  ; No predecessors!
  br label %cond.end, !dbg !2473

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2475
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %default_loop, align 8, !dbg !2477
  %cmp1 = icmp ne %struct.uv_loop_s* %5, %6, !dbg !2478
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2479

if.then:                                          ; preds = %cond.end
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2480
  %8 = bitcast %struct.uv_loop_s* %7 to i8*, !dbg !2480
  call void @uv__free(i8* %8), !dbg !2481
  br label %if.end, !dbg !2481

if.end:                                           ; preds = %if.then, %cond.end
  ret void, !dbg !2482
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #6

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #6

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #6

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i64, i8*, ...) #6

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }
attributes #10 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!932, !933}
!llvm.ident = !{!934}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !170, subprograms: !386, globals: !921)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !83, !104, !117, !125, !157, !167}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82}
!6 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!7 = !DIEnumerator(name: "UV_EACCES", value: -13)
!8 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!9 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!10 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!11 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!12 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!13 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!14 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!15 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!16 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!17 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!18 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!19 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!20 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!21 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!22 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!23 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!24 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!25 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!26 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!27 = !DIEnumerator(name: "UV_EBADF", value: -9)
!28 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!29 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!30 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!31 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!32 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!33 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!34 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!35 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!36 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!37 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!38 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!39 = !DIEnumerator(name: "UV_EINTR", value: -4)
!40 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!41 = !DIEnumerator(name: "UV_EIO", value: -5)
!42 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!43 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!44 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!45 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!46 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!47 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!48 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!49 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!50 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!51 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!52 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!53 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!54 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!55 = !DIEnumerator(name: "UV_ENONET", value: -64)
!56 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!57 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!58 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!59 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!60 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!61 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!62 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!63 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!64 = !DIEnumerator(name: "UV_EPERM", value: -1)
!65 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!66 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!67 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!68 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!69 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!70 = !DIEnumerator(name: "UV_EROFS", value: -30)
!71 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!72 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!73 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!74 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!75 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!76 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!77 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!78 = !DIEnumerator(name: "UV_EOF", value: -4095)
!79 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!80 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!81 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!82 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!83 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 184, size: 32, align: 32, elements: !84)
!84 = !{!85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103}
!85 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!86 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!87 = !DIEnumerator(name: "UV_CHECK", value: 2)
!88 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!89 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!90 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!91 = !DIEnumerator(name: "UV_IDLE", value: 6)
!92 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!93 = !DIEnumerator(name: "UV_POLL", value: 8)
!94 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!95 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!96 = !DIEnumerator(name: "UV_STREAM", value: 11)
!97 = !DIEnumerator(name: "UV_TCP", value: 12)
!98 = !DIEnumerator(name: "UV_TIMER", value: 13)
!99 = !DIEnumerator(name: "UV_TTY", value: 14)
!100 = !DIEnumerator(name: "UV_UDP", value: 15)
!101 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!102 = !DIEnumerator(name: "UV_FILE", value: 17)
!103 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!104 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 193, size: 32, align: 32, elements: !105)
!105 = !{!106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116}
!106 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!107 = !DIEnumerator(name: "UV_REQ", value: 1)
!108 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!109 = !DIEnumerator(name: "UV_WRITE", value: 3)
!110 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!111 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!112 = !DIEnumerator(name: "UV_FS", value: 6)
!113 = !DIEnumerator(name: "UV_WORK", value: 7)
!114 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!115 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!116 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!117 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !118, line: 57, size: 32, align: 32, elements: !119)
!118 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!119 = !{!120, !121, !122, !123, !124}
!120 = !DIEnumerator(name: "UV__SIGNAL_ONE_SHOT", value: 524288)
!121 = !DIEnumerator(name: "UV__HANDLE_INTERNAL", value: 32768)
!122 = !DIEnumerator(name: "UV__HANDLE_ACTIVE", value: 16384)
!123 = !DIEnumerator(name: "UV__HANDLE_REF", value: 8192)
!124 = !DIEnumerator(name: "UV__HANDLE_CLOSING", value: 0)
!125 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1086, size: 32, align: 32, elements: !126)
!126 = !{!127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156}
!127 = !DIEnumerator(name: "UV_FS_UNKNOWN", value: -1)
!128 = !DIEnumerator(name: "UV_FS_CUSTOM", value: 0)
!129 = !DIEnumerator(name: "UV_FS_OPEN", value: 1)
!130 = !DIEnumerator(name: "UV_FS_CLOSE", value: 2)
!131 = !DIEnumerator(name: "UV_FS_READ", value: 3)
!132 = !DIEnumerator(name: "UV_FS_WRITE", value: 4)
!133 = !DIEnumerator(name: "UV_FS_SENDFILE", value: 5)
!134 = !DIEnumerator(name: "UV_FS_STAT", value: 6)
!135 = !DIEnumerator(name: "UV_FS_LSTAT", value: 7)
!136 = !DIEnumerator(name: "UV_FS_FSTAT", value: 8)
!137 = !DIEnumerator(name: "UV_FS_FTRUNCATE", value: 9)
!138 = !DIEnumerator(name: "UV_FS_UTIME", value: 10)
!139 = !DIEnumerator(name: "UV_FS_FUTIME", value: 11)
!140 = !DIEnumerator(name: "UV_FS_ACCESS", value: 12)
!141 = !DIEnumerator(name: "UV_FS_CHMOD", value: 13)
!142 = !DIEnumerator(name: "UV_FS_FCHMOD", value: 14)
!143 = !DIEnumerator(name: "UV_FS_FSYNC", value: 15)
!144 = !DIEnumerator(name: "UV_FS_FDATASYNC", value: 16)
!145 = !DIEnumerator(name: "UV_FS_UNLINK", value: 17)
!146 = !DIEnumerator(name: "UV_FS_RMDIR", value: 18)
!147 = !DIEnumerator(name: "UV_FS_MKDIR", value: 19)
!148 = !DIEnumerator(name: "UV_FS_MKDTEMP", value: 20)
!149 = !DIEnumerator(name: "UV_FS_RENAME", value: 21)
!150 = !DIEnumerator(name: "UV_FS_SCANDIR", value: 22)
!151 = !DIEnumerator(name: "UV_FS_LINK", value: 23)
!152 = !DIEnumerator(name: "UV_FS_SYMLINK", value: 24)
!153 = !DIEnumerator(name: "UV_FS_READLINK", value: 25)
!154 = !DIEnumerator(name: "UV_FS_CHOWN", value: 26)
!155 = !DIEnumerator(name: "UV_FS_FCHOWN", value: 27)
!156 = !DIEnumerator(name: "UV_FS_REALPATH", value: 28)
!157 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1020, size: 32, align: 32, elements: !158)
!158 = !{!159, !160, !161, !162, !163, !164, !165, !166}
!159 = !DIEnumerator(name: "UV_DIRENT_UNKNOWN", value: 0)
!160 = !DIEnumerator(name: "UV_DIRENT_FILE", value: 1)
!161 = !DIEnumerator(name: "UV_DIRENT_DIR", value: 2)
!162 = !DIEnumerator(name: "UV_DIRENT_LINK", value: 3)
!163 = !DIEnumerator(name: "UV_DIRENT_FIFO", value: 4)
!164 = !DIEnumerator(name: "UV_DIRENT_SOCKET", value: 5)
!165 = !DIEnumerator(name: "UV_DIRENT_CHAR", value: 6)
!166 = !DIEnumerator(name: "UV_DIRENT_BLOCK", value: 7)
!167 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 239, size: 32, align: 32, elements: !168)
!168 = !{!169}
!169 = !DIEnumerator(name: "UV_LOOP_BLOCK_SIGNAL", value: 0)
!170 = !{!171, !172, !179, !181, !383, !384, !193}
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !174)
!174 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !175, line: 21, baseType: !176)
!175 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!176 = !DICompositeType(tag: DW_TAG_array_type, baseType: !171, size: 128, align: 64, elements: !177)
!177 = !{!178}
!178 = !DISubrange(count: 2)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !174, size: 64, align: 64)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !183)
!183 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !184)
!184 = !{!185, !186, !373, !374, !375, !376, !381, !382}
!185 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !183, file: !4, line: 426, baseType: !171, size: 64, align: 64)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !183, file: !4, line: 426, baseType: !187, size: 64, align: 64, offset: 64)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !189)
!189 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !190)
!190 = !{!191, !192, !194, !195, !196, !197, !199, !201, !202, !203, !222, !223, !224, !225, !256, !288, !312, !313, !314, !315, !316, !317, !318, !322, !323, !324, !329, !332, !333, !335, !336, !369, !370, !371, !372}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !189, file: !4, line: 1475, baseType: !171, size: 64, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !189, file: !4, line: 1477, baseType: !193, size: 32, align: 32, offset: 64)
!193 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !189, file: !4, line: 1478, baseType: !176, size: 128, align: 64, offset: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !189, file: !4, line: 1479, baseType: !176, size: 128, align: 64, offset: 256)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !189, file: !4, line: 1481, baseType: !193, size: 32, align: 32, offset: 384)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !189, file: !4, line: 1482, baseType: !198, size: 64, align: 64, offset: 448)
!198 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !189, file: !4, line: 1482, baseType: !200, size: 32, align: 32, offset: 512)
!200 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 576)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 704)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !189, file: !4, line: 1482, baseType: !204, size: 64, align: 64, offset: 832)
!204 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !205, size: 64, align: 64)
!205 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !206, size: 64, align: 64)
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !207, line: 87, baseType: !208)
!207 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!208 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !207, line: 89, size: 448, align: 64, elements: !209)
!209 = !{!210, !217, !218, !219, !220, !221}
!210 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !208, file: !207, line: 90, baseType: !211, size: 64, align: 64)
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !207, line: 84, baseType: !212)
!212 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !213, size: 64, align: 64)
!213 = !DISubroutineType(types: !214)
!214 = !{null, !215, !216, !193}
!215 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!216 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !208, size: 64, align: 64)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !208, file: !207, line: 91, baseType: !176, size: 128, align: 64, offset: 64)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !208, file: !207, line: 92, baseType: !176, size: 128, align: 64, offset: 192)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !208, file: !207, line: 93, baseType: !193, size: 32, align: 32, offset: 320)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !208, file: !207, line: 94, baseType: !193, size: 32, align: 32, offset: 352)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !208, file: !207, line: 95, baseType: !200, size: 32, align: 32, offset: 384)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !189, file: !4, line: 1482, baseType: !193, size: 32, align: 32, offset: 896)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !189, file: !4, line: 1482, baseType: !193, size: 32, align: 32, offset: 928)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 960)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !189, file: !4, line: 1482, baseType: !226, size: 320, align: 64, offset: 1088)
!226 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !207, line: 129, baseType: !227)
!227 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !228, line: 127, baseType: !229)
!228 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!229 = !DICompositeType(tag: DW_TAG_union_type, file: !228, line: 90, size: 320, align: 64, elements: !230)
!230 = !{!231, !249, !254}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !229, file: !228, line: 124, baseType: !232, size: 320, align: 64)
!232 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !228, line: 92, size: 320, align: 64, elements: !233)
!233 = !{!234, !235, !236, !237, !238, !239, !241, !242}
!234 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !232, file: !228, line: 94, baseType: !200, size: 32, align: 32)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !232, file: !228, line: 95, baseType: !193, size: 32, align: 32, offset: 32)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !232, file: !228, line: 96, baseType: !200, size: 32, align: 32, offset: 64)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !232, file: !228, line: 98, baseType: !193, size: 32, align: 32, offset: 96)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !232, file: !228, line: 102, baseType: !200, size: 32, align: 32, offset: 128)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !232, file: !228, line: 104, baseType: !240, size: 16, align: 16, offset: 160)
!240 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !232, file: !228, line: 105, baseType: !240, size: 16, align: 16, offset: 176)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !232, file: !228, line: 106, baseType: !243, size: 128, align: 64, offset: 192)
!243 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !228, line: 79, baseType: !244)
!244 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !228, line: 75, size: 128, align: 64, elements: !245)
!245 = !{!246, !248}
!246 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !244, file: !228, line: 77, baseType: !247, size: 64, align: 64)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !244, size: 64, align: 64)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !244, file: !228, line: 78, baseType: !247, size: 64, align: 64, offset: 64)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !229, file: !228, line: 125, baseType: !250, size: 320, align: 8)
!250 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 320, align: 8, elements: !252)
!251 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!252 = !{!253}
!253 = !DISubrange(count: 40)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !229, file: !228, line: 126, baseType: !255, size: 64, align: 64)
!255 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !189, file: !4, line: 1482, baseType: !257, size: 1024, align: 64, offset: 1408)
!257 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !258)
!258 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !259)
!259 = !{!260, !261, !262, !264, !269, !270, !278, !279, !280, !286, !287}
!260 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !258, file: !4, line: 768, baseType: !171, size: 64, align: 64)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !258, file: !4, line: 768, baseType: !187, size: 64, align: 64, offset: 64)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !258, file: !4, line: 768, baseType: !263, size: 32, align: 32, offset: 128)
!263 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !83)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !258, file: !4, line: 768, baseType: !265, size: 64, align: 64, offset: 192)
!265 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !266)
!266 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !267, size: 64, align: 64)
!267 = !DISubroutineType(types: !268)
!268 = !{null, !181}
!269 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !258, file: !4, line: 768, baseType: !176, size: 128, align: 64, offset: 256)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !258, file: !4, line: 768, baseType: !271, size: 256, align: 64, offset: 384)
!271 = !DICompositeType(tag: DW_TAG_union_type, scope: !258, file: !4, line: 768, size: 256, align: 64, elements: !272)
!272 = !{!273, !274}
!273 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !271, file: !4, line: 768, baseType: !200, size: 32, align: 32)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !271, file: !4, line: 768, baseType: !275, size: 256, align: 64)
!275 = !DICompositeType(tag: DW_TAG_array_type, baseType: !171, size: 256, align: 64, elements: !276)
!276 = !{!277}
!277 = !DISubrange(count: 4)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !258, file: !4, line: 768, baseType: !181, size: 64, align: 64, offset: 640)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !258, file: !4, line: 768, baseType: !193, size: 32, align: 32, offset: 704)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !258, file: !4, line: 769, baseType: !281, size: 64, align: 64, offset: 768)
!281 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !282)
!282 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !283, size: 64, align: 64)
!283 = !DISubroutineType(types: !284)
!284 = !{null, !285}
!285 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !258, file: !4, line: 769, baseType: !176, size: 128, align: 64, offset: 832)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !258, file: !4, line: 769, baseType: !200, size: 32, align: 32, offset: 960)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !189, file: !4, line: 1482, baseType: !289, size: 448, align: 64, offset: 2432)
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !207, line: 130, baseType: !290)
!290 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !228, line: 213, baseType: !291)
!291 = !DICompositeType(tag: DW_TAG_union_type, file: !228, line: 173, size: 448, align: 64, elements: !292)
!292 = !{!293, !307, !311}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !291, file: !228, line: 192, baseType: !294, size: 448, align: 64)
!294 = !DICompositeType(tag: DW_TAG_structure_type, scope: !291, file: !228, line: 176, size: 448, align: 64, elements: !295)
!295 = !{!296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306}
!296 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !294, file: !228, line: 178, baseType: !200, size: 32, align: 32)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !294, file: !228, line: 179, baseType: !193, size: 32, align: 32, offset: 32)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !294, file: !228, line: 180, baseType: !193, size: 32, align: 32, offset: 64)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !294, file: !228, line: 181, baseType: !193, size: 32, align: 32, offset: 96)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !294, file: !228, line: 182, baseType: !193, size: 32, align: 32, offset: 128)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !294, file: !228, line: 183, baseType: !193, size: 32, align: 32, offset: 160)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !294, file: !228, line: 184, baseType: !200, size: 32, align: 32, offset: 192)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !294, file: !228, line: 185, baseType: !200, size: 32, align: 32, offset: 224)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !294, file: !228, line: 186, baseType: !198, size: 64, align: 64, offset: 256)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !294, file: !228, line: 187, baseType: !198, size: 64, align: 64, offset: 320)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !294, file: !228, line: 190, baseType: !193, size: 32, align: 32, offset: 384)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !291, file: !228, line: 211, baseType: !308, size: 448, align: 8)
!308 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 448, align: 8, elements: !309)
!309 = !{!310}
!310 = !DISubrange(count: 56)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !291, file: !228, line: 212, baseType: !255, size: 64, align: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !189, file: !4, line: 1482, baseType: !181, size: 64, align: 64, offset: 2880)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 2944)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 3072)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 3200)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 3328)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !189, file: !4, line: 1482, baseType: !176, size: 128, align: 64, offset: 3456)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !189, file: !4, line: 1482, baseType: !319, size: 64, align: 64, offset: 3584)
!319 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !320, size: 64, align: 64)
!320 = !DISubroutineType(types: !321)
!321 = !{null}
!322 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !189, file: !4, line: 1482, baseType: !206, size: 448, align: 64, offset: 3648)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !189, file: !4, line: 1482, baseType: !200, size: 32, align: 32, offset: 4096)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !189, file: !4, line: 1482, baseType: !325, size: 128, align: 64, offset: 4160)
!325 = !DICompositeType(tag: DW_TAG_structure_type, scope: !189, file: !4, line: 1482, size: 128, align: 64, elements: !326)
!326 = !{!327, !328}
!327 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !325, file: !4, line: 1482, baseType: !171, size: 64, align: 64)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !325, file: !4, line: 1482, baseType: !193, size: 32, align: 32, offset: 64)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !189, file: !4, line: 1482, baseType: !330, size: 64, align: 64, offset: 4288)
!330 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !331, line: 55, baseType: !198)
!331 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!332 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !189, file: !4, line: 1482, baseType: !330, size: 64, align: 64, offset: 4352)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !189, file: !4, line: 1482, baseType: !334, size: 64, align: 32, offset: 4416)
!334 = !DICompositeType(tag: DW_TAG_array_type, baseType: !200, size: 64, align: 32, elements: !177)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !189, file: !4, line: 1482, baseType: !206, size: 448, align: 64, offset: 4480)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !189, file: !4, line: 1482, baseType: !337, size: 1216, align: 64, offset: 4928)
!337 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !338)
!338 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !339)
!339 = !{!340, !341, !342, !343, !344, !345, !350, !351, !352, !358, !359, !367, !368}
!340 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !338, file: !4, line: 1326, baseType: !171, size: 64, align: 64)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !338, file: !4, line: 1326, baseType: !187, size: 64, align: 64, offset: 64)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !338, file: !4, line: 1326, baseType: !263, size: 32, align: 32, offset: 128)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !338, file: !4, line: 1326, baseType: !265, size: 64, align: 64, offset: 192)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !338, file: !4, line: 1326, baseType: !176, size: 128, align: 64, offset: 256)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !338, file: !4, line: 1326, baseType: !346, size: 256, align: 64, offset: 384)
!346 = !DICompositeType(tag: DW_TAG_union_type, scope: !338, file: !4, line: 1326, size: 256, align: 64, elements: !347)
!347 = !{!348, !349}
!348 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !346, file: !4, line: 1326, baseType: !200, size: 32, align: 32)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !346, file: !4, line: 1326, baseType: !275, size: 256, align: 64)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !338, file: !4, line: 1326, baseType: !181, size: 64, align: 64, offset: 640)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !338, file: !4, line: 1326, baseType: !193, size: 32, align: 32, offset: 704)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !338, file: !4, line: 1327, baseType: !353, size: 64, align: 64, offset: 768)
!353 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !354)
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !355, size: 64, align: 64)
!355 = !DISubroutineType(types: !356)
!356 = !{null, !357, !200}
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !337, size: 64, align: 64)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !338, file: !4, line: 1328, baseType: !200, size: 32, align: 32, offset: 832)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !338, file: !4, line: 1329, baseType: !360, size: 256, align: 64, offset: 896)
!360 = !DICompositeType(tag: DW_TAG_structure_type, scope: !338, file: !4, line: 1329, size: 256, align: 64, elements: !361)
!361 = !{!362, !364, !365, !366}
!362 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !360, file: !4, line: 1329, baseType: !363, size: 64, align: 64)
!363 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !338, size: 64, align: 64)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !360, file: !4, line: 1329, baseType: !363, size: 64, align: 64, offset: 64)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !360, file: !4, line: 1329, baseType: !363, size: 64, align: 64, offset: 128)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !360, file: !4, line: 1329, baseType: !200, size: 32, align: 32, offset: 192)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !338, file: !4, line: 1329, baseType: !193, size: 32, align: 32, offset: 1152)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !338, file: !4, line: 1329, baseType: !193, size: 32, align: 32, offset: 1184)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !189, file: !4, line: 1482, baseType: !200, size: 32, align: 32, offset: 6144)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !189, file: !4, line: 1482, baseType: !206, size: 448, align: 64, offset: 6208)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !189, file: !4, line: 1482, baseType: !171, size: 64, align: 64, offset: 6656)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !189, file: !4, line: 1482, baseType: !200, size: 32, align: 32, offset: 6720)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !183, file: !4, line: 426, baseType: !263, size: 32, align: 32, offset: 128)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !183, file: !4, line: 426, baseType: !265, size: 64, align: 64, offset: 192)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !183, file: !4, line: 426, baseType: !176, size: 128, align: 64, offset: 256)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !183, file: !4, line: 426, baseType: !377, size: 256, align: 64, offset: 384)
!377 = !DICompositeType(tag: DW_TAG_union_type, scope: !183, file: !4, line: 426, size: 256, align: 64, elements: !378)
!378 = !{!379, !380}
!379 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !377, file: !4, line: 426, baseType: !200, size: 32, align: 32)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !377, file: !4, line: 426, baseType: !275, size: 256, align: 64)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !183, file: !4, line: 426, baseType: !181, size: 64, align: 64, offset: 640)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !183, file: !4, line: 426, baseType: !193, size: 32, align: 32, offset: 704)
!383 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !251, size: 64, align: 64)
!384 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !385, line: 62, baseType: !198)
!385 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!386 = !{!387, !393, !396, !399, !402, !405, !408, !419, !422, !426, !429, !437, !440, !441, !466, !491, !496, !501, !618, !648, !651, !684, !687, !690, !693, !700, !755, !756, !757, !758, !763, !766, !771, !774, !778, !779, !807, !891, !901, !905, !908, !909, !912, !913, !914, !917}
!387 = distinct !DISubprogram(name: "uv__strdup", scope: !1, file: !1, line: 54, type: !388, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!388 = !DISubroutineType(types: !389)
!389 = !{!383, !390}
!390 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !391, size: 64, align: 64)
!391 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !251)
!392 = !{}
!393 = distinct !DISubprogram(name: "uv__strndup", scope: !1, file: !1, line: 62, type: !394, isLocal: false, isDefinition: true, scopeLine: 62, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!394 = !DISubroutineType(types: !395)
!395 = !{!383, !390, !384}
!396 = distinct !DISubprogram(name: "uv__malloc", scope: !1, file: !1, line: 74, type: !397, isLocal: false, isDefinition: true, scopeLine: 74, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!397 = !DISubroutineType(types: !398)
!398 = !{!171, !384}
!399 = distinct !DISubprogram(name: "uv__free", scope: !1, file: !1, line: 78, type: !400, isLocal: false, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!400 = !DISubroutineType(types: !401)
!401 = !{null, !171}
!402 = distinct !DISubprogram(name: "uv__calloc", scope: !1, file: !1, line: 89, type: !403, isLocal: false, isDefinition: true, scopeLine: 89, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!403 = !DISubroutineType(types: !404)
!404 = !{!171, !384, !384}
!405 = distinct !DISubprogram(name: "uv__realloc", scope: !1, file: !1, line: 93, type: !406, isLocal: false, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!406 = !DISubroutineType(types: !407)
!407 = !{!171, !171, !384}
!408 = distinct !DISubprogram(name: "uv_replace_allocator", scope: !1, file: !1, line: 97, type: !409, isLocal: false, isDefinition: true, scopeLine: 100, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!409 = !DISubroutineType(types: !410)
!410 = !{!200, !411, !413, !415, !417}
!411 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_malloc_func", file: !4, line: 253, baseType: !412)
!412 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !397, size: 64, align: 64)
!413 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_realloc_func", file: !4, line: 254, baseType: !414)
!414 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !406, size: 64, align: 64)
!415 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_calloc_func", file: !4, line: 255, baseType: !416)
!416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !403, size: 64, align: 64)
!417 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_free_func", file: !4, line: 256, baseType: !418)
!418 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !400, size: 64, align: 64)
!419 = distinct !DISubprogram(name: "uv_handle_size", scope: !1, file: !1, line: 116, type: !420, isLocal: false, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!420 = !DISubroutineType(types: !421)
!421 = !{!384, !263}
!422 = distinct !DISubprogram(name: "uv_req_size", scope: !1, file: !1, line: 124, type: !423, isLocal: false, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!423 = !DISubroutineType(types: !424)
!424 = !{!384, !425}
!425 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !104)
!426 = distinct !DISubprogram(name: "uv_loop_size", scope: !1, file: !1, line: 135, type: !427, isLocal: false, isDefinition: true, scopeLine: 135, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!427 = !DISubroutineType(types: !428)
!428 = !{!384}
!429 = distinct !DISubprogram(name: "uv_buf_init", scope: !1, file: !1, line: 140, type: !430, isLocal: false, isDefinition: true, scopeLine: 140, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!430 = !DISubroutineType(types: !431)
!431 = !{!432, !383, !193}
!432 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !207, line: 119, baseType: !433)
!433 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !207, line: 116, size: 128, align: 64, elements: !434)
!434 = !{!435, !436}
!435 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !433, file: !207, line: 117, baseType: !383, size: 64, align: 64)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !433, file: !207, line: 118, baseType: !384, size: 64, align: 64, offset: 64)
!437 = distinct !DISubprogram(name: "uv_err_name", scope: !1, file: !1, line: 160, type: !438, isLocal: false, isDefinition: true, scopeLine: 160, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!438 = !DISubroutineType(types: !439)
!439 = !{!390, !200}
!440 = distinct !DISubprogram(name: "uv_strerror", scope: !1, file: !1, line: 170, type: !438, isLocal: false, isDefinition: true, scopeLine: 170, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!441 = distinct !DISubprogram(name: "uv_ip4_addr", scope: !1, file: !1, line: 179, type: !442, isLocal: false, isDefinition: true, scopeLine: 179, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!442 = !DISubroutineType(types: !443)
!443 = !{!200, !390, !200, !444}
!444 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !445, size: 64, align: 64)
!445 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !446, line: 237, size: 128, align: 32, elements: !447)
!446 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!447 = !{!448, !452, !455, !461}
!448 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !445, file: !446, line: 239, baseType: !449, size: 16, align: 16)
!449 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !450, line: 28, baseType: !451)
!450 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!451 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!452 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !445, file: !446, line: 240, baseType: !453, size: 16, align: 16, offset: 16)
!453 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !446, line: 117, baseType: !454)
!454 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !331, line: 49, baseType: !451)
!455 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !445, file: !446, line: 241, baseType: !456, size: 32, align: 32, offset: 32)
!456 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !446, line: 31, size: 32, align: 32, elements: !457)
!457 = !{!458}
!458 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !456, file: !446, line: 33, baseType: !459, size: 32, align: 32)
!459 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !446, line: 30, baseType: !460)
!460 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !331, line: 51, baseType: !193)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !445, file: !446, line: 244, baseType: !462, size: 64, align: 8, offset: 64)
!462 = !DICompositeType(tag: DW_TAG_array_type, baseType: !463, size: 64, align: 8, elements: !464)
!463 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!464 = !{!465}
!465 = !DISubrange(count: 8)
!466 = distinct !DISubprogram(name: "uv_ip6_addr", scope: !1, file: !1, line: 187, type: !467, isLocal: false, isDefinition: true, scopeLine: 187, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!467 = !DISubroutineType(types: !468)
!468 = !{!200, !390, !200, !469}
!469 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !470, size: 64, align: 64)
!470 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in6", file: !446, line: 252, size: 224, align: 32, elements: !471)
!471 = !{!472, !473, !474, !475, !490}
!472 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_family", scope: !470, file: !446, line: 254, baseType: !449, size: 16, align: 16)
!473 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_port", scope: !470, file: !446, line: 255, baseType: !453, size: 16, align: 16, offset: 16)
!474 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_flowinfo", scope: !470, file: !446, line: 256, baseType: !460, size: 32, align: 32, offset: 32)
!475 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_addr", scope: !470, file: !446, line: 257, baseType: !476, size: 128, align: 32, offset: 64)
!476 = !DICompositeType(tag: DW_TAG_structure_type, name: "in6_addr", file: !446, line: 209, size: 128, align: 32, elements: !477)
!477 = !{!478}
!478 = !DIDerivedType(tag: DW_TAG_member, name: "__in6_u", scope: !476, file: !446, line: 218, baseType: !479, size: 128, align: 32)
!479 = !DICompositeType(tag: DW_TAG_union_type, scope: !476, file: !446, line: 211, size: 128, align: 32, elements: !480)
!480 = !{!481, !486, !488}
!481 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr8", scope: !479, file: !446, line: 213, baseType: !482, size: 128, align: 8)
!482 = !DICompositeType(tag: DW_TAG_array_type, baseType: !483, size: 128, align: 8, elements: !484)
!483 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !331, line: 48, baseType: !463)
!484 = !{!485}
!485 = !DISubrange(count: 16)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr16", scope: !479, file: !446, line: 215, baseType: !487, size: 128, align: 16)
!487 = !DICompositeType(tag: DW_TAG_array_type, baseType: !454, size: 128, align: 16, elements: !464)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr32", scope: !479, file: !446, line: 216, baseType: !489, size: 128, align: 32)
!489 = !DICompositeType(tag: DW_TAG_array_type, baseType: !460, size: 128, align: 32, elements: !276)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_scope_id", scope: !470, file: !446, line: 258, baseType: !460, size: 32, align: 32, offset: 192)
!491 = distinct !DISubprogram(name: "uv_ip4_name", scope: !1, file: !1, line: 219, type: !492, isLocal: false, isDefinition: true, scopeLine: 219, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!492 = !DISubroutineType(types: !493)
!493 = !{!200, !494, !383, !384}
!494 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !495, size: 64, align: 64)
!495 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !445)
!496 = distinct !DISubprogram(name: "uv_ip6_name", scope: !1, file: !1, line: 224, type: !497, isLocal: false, isDefinition: true, scopeLine: 224, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!497 = !DISubroutineType(types: !498)
!498 = !{!200, !499, !383, !384}
!499 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !500, size: 64, align: 64)
!500 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !470)
!501 = distinct !DISubprogram(name: "uv_tcp_bind", scope: !1, file: !1, line: 229, type: !502, isLocal: false, isDefinition: true, scopeLine: 231, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!502 = !DISubroutineType(types: !503)
!503 = !{!200, !504, !608, !193}
!504 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !505, size: 64, align: 64)
!505 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_tcp_t", file: !4, line: 207, baseType: !506)
!506 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_tcp_s", file: !4, line: 516, size: 1984, align: 64, elements: !507)
!507 = !{!508, !509, !510, !511, !512, !513, !518, !519, !520, !521, !527, !599, !600, !601, !602, !603, !604, !605, !606, !607}
!508 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !506, file: !4, line: 517, baseType: !171, size: 64, align: 64)
!509 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !506, file: !4, line: 517, baseType: !187, size: 64, align: 64, offset: 64)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !506, file: !4, line: 517, baseType: !263, size: 32, align: 32, offset: 128)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !506, file: !4, line: 517, baseType: !265, size: 64, align: 64, offset: 192)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !506, file: !4, line: 517, baseType: !176, size: 128, align: 64, offset: 256)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !506, file: !4, line: 517, baseType: !514, size: 256, align: 64, offset: 384)
!514 = !DICompositeType(tag: DW_TAG_union_type, scope: !506, file: !4, line: 517, size: 256, align: 64, elements: !515)
!515 = !{!516, !517}
!516 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !514, file: !4, line: 517, baseType: !200, size: 32, align: 32)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !514, file: !4, line: 517, baseType: !275, size: 256, align: 64)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !506, file: !4, line: 517, baseType: !181, size: 64, align: 64, offset: 640)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !506, file: !4, line: 517, baseType: !193, size: 32, align: 32, offset: 704)
!520 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !506, file: !4, line: 518, baseType: !384, size: 64, align: 64, offset: 768)
!521 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !506, file: !4, line: 518, baseType: !522, size: 64, align: 64, offset: 832)
!522 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !4, line: 296, baseType: !523)
!523 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !524, size: 64, align: 64)
!524 = !DISubroutineType(types: !525)
!525 = !{null, !181, !384, !526}
!526 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !432, size: 64, align: 64)
!527 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !506, file: !4, line: 518, baseType: !528, size: 64, align: 64, offset: 896)
!528 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !4, line: 299, baseType: !529)
!529 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !530, size: 64, align: 64)
!530 = !DISubroutineType(types: !531)
!531 = !{null, !532, !593, !597}
!532 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !533, size: 64, align: 64)
!533 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !4, line: 206, baseType: !534)
!534 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !4, line: 465, size: 1984, align: 64, elements: !535)
!535 = !{!536, !537, !538, !539, !540, !541, !546, !547, !548, !549, !550, !551, !567, !582, !583, !584, !585, !590, !591, !592}
!536 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !534, file: !4, line: 466, baseType: !171, size: 64, align: 64)
!537 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !534, file: !4, line: 466, baseType: !187, size: 64, align: 64, offset: 64)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !534, file: !4, line: 466, baseType: !263, size: 32, align: 32, offset: 128)
!539 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !534, file: !4, line: 466, baseType: !265, size: 64, align: 64, offset: 192)
!540 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !534, file: !4, line: 466, baseType: !176, size: 128, align: 64, offset: 256)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !534, file: !4, line: 466, baseType: !542, size: 256, align: 64, offset: 384)
!542 = !DICompositeType(tag: DW_TAG_union_type, scope: !534, file: !4, line: 466, size: 256, align: 64, elements: !543)
!543 = !{!544, !545}
!544 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !542, file: !4, line: 466, baseType: !200, size: 32, align: 32)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !542, file: !4, line: 466, baseType: !275, size: 256, align: 64)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !534, file: !4, line: 466, baseType: !181, size: 64, align: 64, offset: 640)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !534, file: !4, line: 466, baseType: !193, size: 32, align: 32, offset: 704)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !534, file: !4, line: 467, baseType: !384, size: 64, align: 64, offset: 768)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !534, file: !4, line: 467, baseType: !522, size: 64, align: 64, offset: 832)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !534, file: !4, line: 467, baseType: !528, size: 64, align: 64, offset: 896)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !534, file: !4, line: 467, baseType: !552, size: 64, align: 64, offset: 960)
!552 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !553, size: 64, align: 64)
!553 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !4, line: 228, baseType: !554)
!554 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !4, line: 551, size: 768, align: 64, elements: !555)
!555 = !{!556, !557, !558, !559, !560, !565, !566}
!556 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !554, file: !4, line: 552, baseType: !171, size: 64, align: 64)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !554, file: !4, line: 552, baseType: !425, size: 32, align: 32, offset: 64)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !554, file: !4, line: 552, baseType: !176, size: 128, align: 64, offset: 128)
!559 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !554, file: !4, line: 552, baseType: !275, size: 256, align: 64, offset: 256)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !554, file: !4, line: 553, baseType: !561, size: 64, align: 64, offset: 512)
!561 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !4, line: 303, baseType: !562)
!562 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !563, size: 64, align: 64)
!563 = !DISubroutineType(types: !564)
!564 = !{null, !552, !200}
!565 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !554, file: !4, line: 554, baseType: !532, size: 64, align: 64, offset: 576)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !554, file: !4, line: 555, baseType: !176, size: 128, align: 64, offset: 640)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !534, file: !4, line: 467, baseType: !568, size: 64, align: 64, offset: 1024)
!568 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !569, size: 64, align: 64)
!569 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !4, line: 226, baseType: !570)
!570 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !4, line: 401, size: 640, align: 64, elements: !571)
!571 = !{!572, !573, !574, !575, !576, !577}
!572 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !570, file: !4, line: 402, baseType: !171, size: 64, align: 64)
!573 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !570, file: !4, line: 402, baseType: !425, size: 32, align: 32, offset: 64)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !570, file: !4, line: 402, baseType: !176, size: 128, align: 64, offset: 128)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !570, file: !4, line: 402, baseType: !275, size: 256, align: 64, offset: 256)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !570, file: !4, line: 403, baseType: !532, size: 64, align: 64, offset: 512)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !570, file: !4, line: 404, baseType: !578, size: 64, align: 64, offset: 576)
!578 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !4, line: 304, baseType: !579)
!579 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !580, size: 64, align: 64)
!580 = !DISubroutineType(types: !581)
!581 = !{null, !568, !200}
!582 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !534, file: !4, line: 467, baseType: !206, size: 448, align: 64, offset: 1088)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !534, file: !4, line: 467, baseType: !176, size: 128, align: 64, offset: 1536)
!584 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !534, file: !4, line: 467, baseType: !176, size: 128, align: 64, offset: 1664)
!585 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !534, file: !4, line: 467, baseType: !586, size: 64, align: 64, offset: 1792)
!586 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !4, line: 305, baseType: !587)
!587 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !588, size: 64, align: 64)
!588 = !DISubroutineType(types: !589)
!589 = !{null, !532, !200}
!590 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !534, file: !4, line: 467, baseType: !200, size: 32, align: 32, offset: 1856)
!591 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !534, file: !4, line: 467, baseType: !200, size: 32, align: 32, offset: 1888)
!592 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !534, file: !4, line: 467, baseType: !171, size: 64, align: 64, offset: 1920)
!593 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !594, line: 102, baseType: !595)
!594 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!595 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !596, line: 172, baseType: !255)
!596 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!597 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !598, size: 64, align: 64)
!598 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !432)
!599 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !506, file: !4, line: 518, baseType: !552, size: 64, align: 64, offset: 960)
!600 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !506, file: !4, line: 518, baseType: !568, size: 64, align: 64, offset: 1024)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !506, file: !4, line: 518, baseType: !206, size: 448, align: 64, offset: 1088)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !506, file: !4, line: 518, baseType: !176, size: 128, align: 64, offset: 1536)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !506, file: !4, line: 518, baseType: !176, size: 128, align: 64, offset: 1664)
!604 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !506, file: !4, line: 518, baseType: !586, size: 64, align: 64, offset: 1792)
!605 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !506, file: !4, line: 518, baseType: !200, size: 32, align: 32, offset: 1856)
!606 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !506, file: !4, line: 518, baseType: !200, size: 32, align: 32, offset: 1888)
!607 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !506, file: !4, line: 518, baseType: !171, size: 64, align: 64, offset: 1920)
!608 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !609, size: 64, align: 64)
!609 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !610)
!610 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !611, line: 149, size: 128, align: 16, elements: !612)
!611 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!612 = !{!613, !614}
!613 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !610, file: !611, line: 151, baseType: !449, size: 16, align: 16)
!614 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !610, file: !611, line: 152, baseType: !615, size: 112, align: 8, offset: 16)
!615 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 112, align: 8, elements: !616)
!616 = !{!617}
!617 = !DISubrange(count: 14)
!618 = distinct !DISubprogram(name: "uv_udp_bind", scope: !1, file: !1, line: 248, type: !619, isLocal: false, isDefinition: true, scopeLine: 250, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!619 = !DISubroutineType(types: !620)
!620 = !{!200, !621, !608, !193}
!621 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !622, size: 64, align: 64)
!622 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_t", file: !4, line: 208, baseType: !623)
!623 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_udp_s", file: !4, line: 590, size: 1728, align: 64, elements: !624)
!624 = !{!625, !626, !627, !628, !629, !630, !635, !636, !637, !638, !639, !640, !645, !646, !647}
!625 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !623, file: !4, line: 591, baseType: !171, size: 64, align: 64)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !623, file: !4, line: 591, baseType: !187, size: 64, align: 64, offset: 64)
!627 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !623, file: !4, line: 591, baseType: !263, size: 32, align: 32, offset: 128)
!628 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !623, file: !4, line: 591, baseType: !265, size: 64, align: 64, offset: 192)
!629 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !623, file: !4, line: 591, baseType: !176, size: 128, align: 64, offset: 256)
!630 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !623, file: !4, line: 591, baseType: !631, size: 256, align: 64, offset: 384)
!631 = !DICompositeType(tag: DW_TAG_union_type, scope: !623, file: !4, line: 591, size: 256, align: 64, elements: !632)
!632 = !{!633, !634}
!633 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !631, file: !4, line: 591, baseType: !200, size: 32, align: 32)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !631, file: !4, line: 591, baseType: !275, size: 256, align: 64)
!635 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !623, file: !4, line: 591, baseType: !181, size: 64, align: 64, offset: 640)
!636 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !623, file: !4, line: 591, baseType: !193, size: 32, align: 32, offset: 704)
!637 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_size", scope: !623, file: !4, line: 597, baseType: !384, size: 64, align: 64, offset: 768)
!638 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_count", scope: !623, file: !4, line: 601, baseType: !384, size: 64, align: 64, offset: 832)
!639 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !623, file: !4, line: 602, baseType: !522, size: 64, align: 64, offset: 896)
!640 = !DIDerivedType(tag: DW_TAG_member, name: "recv_cb", scope: !623, file: !4, line: 602, baseType: !641, size: 64, align: 64, offset: 960)
!641 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_recv_cb", file: !4, line: 583, baseType: !642)
!642 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !643, size: 64, align: 64)
!643 = !DISubroutineType(types: !644)
!644 = !{null, !621, !593, !597, !608, !193}
!645 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !623, file: !4, line: 602, baseType: !206, size: 448, align: 64, offset: 1024)
!646 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !623, file: !4, line: 602, baseType: !176, size: 128, align: 64, offset: 1472)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !623, file: !4, line: 602, baseType: !176, size: 128, align: 64, offset: 1600)
!648 = distinct !DISubprogram(name: "uv_tcp_connect", scope: !1, file: !1, line: 267, type: !649, isLocal: false, isDefinition: true, scopeLine: 270, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!649 = !DISubroutineType(types: !650)
!650 = !{!200, !552, !504, !608, !561}
!651 = distinct !DISubprogram(name: "uv_udp_send", scope: !1, file: !1, line: 287, type: !652, isLocal: false, isDefinition: true, scopeLine: 292, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!652 = !DISubroutineType(types: !653)
!653 = !{!200, !654, !621, !597, !193, !608, !664}
!654 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !655, size: 64, align: 64)
!655 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_send_t", file: !4, line: 229, baseType: !656)
!656 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_udp_send_s", file: !4, line: 606, size: 2560, align: 64, elements: !657)
!657 = !{!658, !659, !660, !661, !662, !663, !668, !669, !678, !679, !680, !681, !682}
!658 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !656, file: !4, line: 607, baseType: !171, size: 64, align: 64)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !656, file: !4, line: 607, baseType: !425, size: 32, align: 32, offset: 64)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !656, file: !4, line: 607, baseType: !176, size: 128, align: 64, offset: 128)
!661 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !656, file: !4, line: 607, baseType: !275, size: 256, align: 64, offset: 256)
!662 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !656, file: !4, line: 608, baseType: !621, size: 64, align: 64, offset: 512)
!663 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !656, file: !4, line: 609, baseType: !664, size: 64, align: 64, offset: 576)
!664 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_send_cb", file: !4, line: 582, baseType: !665)
!665 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !666, size: 64, align: 64)
!666 = !DISubroutineType(types: !667)
!667 = !{null, !654, !200}
!668 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !656, file: !4, line: 610, baseType: !176, size: 128, align: 64, offset: 640)
!669 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !656, file: !4, line: 610, baseType: !670, size: 1024, align: 64, offset: 768)
!670 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !611, line: 162, size: 1024, align: 64, elements: !671)
!671 = !{!672, !673, !674}
!672 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !670, file: !611, line: 164, baseType: !449, size: 16, align: 16)
!673 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !670, file: !611, line: 165, baseType: !198, size: 64, align: 64, offset: 64)
!674 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_padding", scope: !670, file: !611, line: 166, baseType: !675, size: 896, align: 8, offset: 128)
!675 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 896, align: 8, elements: !676)
!676 = !{!677}
!677 = !DISubrange(count: 112)
!678 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !656, file: !4, line: 610, baseType: !193, size: 32, align: 32, offset: 1792)
!679 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !656, file: !4, line: 610, baseType: !526, size: 64, align: 64, offset: 1856)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !656, file: !4, line: 610, baseType: !593, size: 64, align: 64, offset: 1920)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "send_cb", scope: !656, file: !4, line: 610, baseType: !664, size: 64, align: 64, offset: 1984)
!682 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !656, file: !4, line: 610, baseType: !683, size: 512, align: 64, offset: 2048)
!683 = !DICompositeType(tag: DW_TAG_array_type, baseType: !432, size: 512, align: 64, elements: !276)
!684 = distinct !DISubprogram(name: "uv_udp_try_send", scope: !1, file: !1, line: 309, type: !685, isLocal: false, isDefinition: true, scopeLine: 312, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!685 = !DISubroutineType(types: !686)
!686 = !{!200, !621, !597, !193, !608}
!687 = distinct !DISubprogram(name: "uv_udp_recv_start", scope: !1, file: !1, line: 329, type: !688, isLocal: false, isDefinition: true, scopeLine: 331, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!688 = !DISubroutineType(types: !689)
!689 = !{!200, !621, !522, !641}
!690 = distinct !DISubprogram(name: "uv_udp_recv_stop", scope: !1, file: !1, line: 339, type: !691, isLocal: false, isDefinition: true, scopeLine: 339, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!691 = !DISubroutineType(types: !692)
!692 = !{!200, !621}
!693 = distinct !DISubprogram(name: "uv_walk", scope: !1, file: !1, line: 347, type: !694, isLocal: false, isDefinition: true, scopeLine: 347, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!694 = !DISubroutineType(types: !695)
!695 = !{null, !187, !696, !171}
!696 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_walk_cb", file: !4, line: 314, baseType: !697)
!697 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !698, size: 64, align: 64)
!698 = !DISubroutineType(types: !699)
!699 = !{null, !181, !171}
!700 = distinct !DISubprogram(name: "uv_print_all_handles", scope: !1, file: !1, line: 398, type: !701, isLocal: false, isDefinition: true, scopeLine: 398, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!701 = !DISubroutineType(types: !702)
!702 = !{null, !187, !703}
!703 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !704, size: 64, align: 64)
!704 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !594, line: 48, baseType: !705)
!705 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !706, line: 245, size: 1728, align: 64, elements: !707)
!706 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!707 = !{!708, !709, !710, !711, !712, !713, !714, !715, !716, !717, !718, !719, !720, !728, !729, !730, !731, !733, !734, !736, !740, !743, !745, !746, !747, !748, !749, !750, !751}
!708 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !705, file: !706, line: 246, baseType: !200, size: 32, align: 32)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !705, file: !706, line: 251, baseType: !383, size: 64, align: 64, offset: 64)
!710 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !705, file: !706, line: 252, baseType: !383, size: 64, align: 64, offset: 128)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !705, file: !706, line: 253, baseType: !383, size: 64, align: 64, offset: 192)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !705, file: !706, line: 254, baseType: !383, size: 64, align: 64, offset: 256)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !705, file: !706, line: 255, baseType: !383, size: 64, align: 64, offset: 320)
!714 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !705, file: !706, line: 256, baseType: !383, size: 64, align: 64, offset: 384)
!715 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !705, file: !706, line: 257, baseType: !383, size: 64, align: 64, offset: 448)
!716 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !705, file: !706, line: 258, baseType: !383, size: 64, align: 64, offset: 512)
!717 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !705, file: !706, line: 260, baseType: !383, size: 64, align: 64, offset: 576)
!718 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !705, file: !706, line: 261, baseType: !383, size: 64, align: 64, offset: 640)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !705, file: !706, line: 262, baseType: !383, size: 64, align: 64, offset: 704)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !705, file: !706, line: 264, baseType: !721, size: 64, align: 64, offset: 768)
!721 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !722, size: 64, align: 64)
!722 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !706, line: 160, size: 192, align: 64, elements: !723)
!723 = !{!724, !725, !727}
!724 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !722, file: !706, line: 161, baseType: !721, size: 64, align: 64)
!725 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !722, file: !706, line: 162, baseType: !726, size: 64, align: 64, offset: 64)
!726 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !705, size: 64, align: 64)
!727 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !722, file: !706, line: 166, baseType: !200, size: 32, align: 32, offset: 128)
!728 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !705, file: !706, line: 266, baseType: !726, size: 64, align: 64, offset: 832)
!729 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !705, file: !706, line: 268, baseType: !200, size: 32, align: 32, offset: 896)
!730 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !705, file: !706, line: 272, baseType: !200, size: 32, align: 32, offset: 928)
!731 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !705, file: !706, line: 274, baseType: !732, size: 64, align: 64, offset: 960)
!732 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !596, line: 131, baseType: !255)
!733 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !705, file: !706, line: 278, baseType: !451, size: 16, align: 16, offset: 1024)
!734 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !705, file: !706, line: 279, baseType: !735, size: 8, align: 8, offset: 1040)
!735 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !705, file: !706, line: 280, baseType: !737, size: 8, align: 8, offset: 1048)
!737 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 8, align: 8, elements: !738)
!738 = !{!739}
!739 = !DISubrange(count: 1)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !705, file: !706, line: 284, baseType: !741, size: 64, align: 64, offset: 1088)
!741 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !742, size: 64, align: 64)
!742 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !706, line: 154, baseType: null)
!743 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !705, file: !706, line: 293, baseType: !744, size: 64, align: 64, offset: 1152)
!744 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !596, line: 132, baseType: !255)
!745 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !705, file: !706, line: 302, baseType: !171, size: 64, align: 64, offset: 1216)
!746 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !705, file: !706, line: 303, baseType: !171, size: 64, align: 64, offset: 1280)
!747 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !705, file: !706, line: 304, baseType: !171, size: 64, align: 64, offset: 1344)
!748 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !705, file: !706, line: 305, baseType: !171, size: 64, align: 64, offset: 1408)
!749 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !705, file: !706, line: 306, baseType: !384, size: 64, align: 64, offset: 1472)
!750 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !705, file: !706, line: 308, baseType: !200, size: 32, align: 32, offset: 1536)
!751 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !705, file: !706, line: 310, baseType: !752, size: 160, align: 8, offset: 1568)
!752 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 160, align: 8, elements: !753)
!753 = !{!754}
!754 = !DISubrange(count: 20)
!755 = distinct !DISubprogram(name: "uv_print_active_handles", scope: !1, file: !1, line: 403, type: !701, isLocal: false, isDefinition: true, scopeLine: 403, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!756 = distinct !DISubprogram(name: "uv_ref", scope: !1, file: !1, line: 408, type: !267, isLocal: false, isDefinition: true, scopeLine: 408, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!757 = distinct !DISubprogram(name: "uv_unref", scope: !1, file: !1, line: 413, type: !267, isLocal: false, isDefinition: true, scopeLine: 413, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!758 = distinct !DISubprogram(name: "uv_has_ref", scope: !1, file: !1, line: 418, type: !759, isLocal: false, isDefinition: true, scopeLine: 418, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!759 = !DISubroutineType(types: !760)
!760 = !{!200, !761}
!761 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !762, size: 64, align: 64)
!762 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !182)
!763 = distinct !DISubprogram(name: "uv_stop", scope: !1, file: !1, line: 423, type: !764, isLocal: false, isDefinition: true, scopeLine: 423, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!764 = !DISubroutineType(types: !765)
!765 = !{null, !187}
!766 = distinct !DISubprogram(name: "uv_now", scope: !1, file: !1, line: 428, type: !767, isLocal: false, isDefinition: true, scopeLine: 428, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!767 = !DISubroutineType(types: !768)
!768 = !{!330, !769}
!769 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !770, size: 64, align: 64)
!770 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !188)
!771 = distinct !DISubprogram(name: "uv__count_bufs", scope: !1, file: !1, line: 434, type: !772, isLocal: false, isDefinition: true, scopeLine: 434, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!772 = !DISubroutineType(types: !773)
!773 = !{!384, !597, !193}
!774 = distinct !DISubprogram(name: "uv_recv_buffer_size", scope: !1, file: !1, line: 445, type: !775, isLocal: false, isDefinition: true, scopeLine: 445, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!775 = !DISubroutineType(types: !776)
!776 = !{!200, !181, !777}
!777 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!778 = distinct !DISubprogram(name: "uv_send_buffer_size", scope: !1, file: !1, line: 449, type: !775, isLocal: false, isDefinition: true, scopeLine: 449, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!779 = distinct !DISubprogram(name: "uv_fs_event_getpath", scope: !1, file: !1, line: 453, type: !780, isLocal: false, isDefinition: true, scopeLine: 453, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!780 = !DISubroutineType(types: !781)
!781 = !{!200, !782, !383, !806}
!782 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !783, size: 64, align: 64)
!783 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_event_t", file: !4, line: 218, baseType: !784)
!784 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_event_s", file: !4, line: 1297, size: 1088, align: 64, elements: !785)
!785 = !{!786, !787, !788, !789, !790, !791, !796, !797, !798, !799, !804, !805}
!786 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !784, file: !4, line: 1298, baseType: !171, size: 64, align: 64)
!787 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !784, file: !4, line: 1298, baseType: !187, size: 64, align: 64, offset: 64)
!788 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !784, file: !4, line: 1298, baseType: !263, size: 32, align: 32, offset: 128)
!789 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !784, file: !4, line: 1298, baseType: !265, size: 64, align: 64, offset: 192)
!790 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !784, file: !4, line: 1298, baseType: !176, size: 128, align: 64, offset: 256)
!791 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !784, file: !4, line: 1298, baseType: !792, size: 256, align: 64, offset: 384)
!792 = !DICompositeType(tag: DW_TAG_union_type, scope: !784, file: !4, line: 1298, size: 256, align: 64, elements: !793)
!793 = !{!794, !795}
!794 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !792, file: !4, line: 1298, baseType: !200, size: 32, align: 32)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !792, file: !4, line: 1298, baseType: !275, size: 256, align: 64)
!796 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !784, file: !4, line: 1298, baseType: !181, size: 64, align: 64, offset: 640)
!797 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !784, file: !4, line: 1298, baseType: !193, size: 32, align: 32, offset: 704)
!798 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !784, file: !4, line: 1300, baseType: !383, size: 64, align: 64, offset: 768)
!799 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !784, file: !4, line: 1301, baseType: !800, size: 64, align: 64, offset: 832)
!800 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_event_cb", file: !4, line: 352, baseType: !801)
!801 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !802, size: 64, align: 64)
!802 = !DISubroutineType(types: !803)
!803 = !{null, !782, !390, !200, !200}
!804 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !784, file: !4, line: 1301, baseType: !176, size: 128, align: 64, offset: 896)
!805 = !DIDerivedType(tag: DW_TAG_member, name: "wd", scope: !784, file: !4, line: 1301, baseType: !200, size: 32, align: 32, offset: 1024)
!806 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !384, size: 64, align: 64)
!807 = distinct !DISubprogram(name: "uv__fs_scandir_cleanup", scope: !1, file: !1, line: 496, type: !808, isLocal: false, isDefinition: true, scopeLine: 496, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!808 = !DISubroutineType(types: !809)
!809 = !{null, !810}
!810 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !811, size: 64, align: 64)
!811 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_t", file: !4, line: 230, baseType: !812)
!812 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_s", file: !4, line: 1120, size: 3520, align: 64, elements: !813)
!813 = !{!814, !815, !816, !817, !818, !820, !821, !824, !825, !826, !827, !852, !853, !855, !856, !860, !861, !862, !864, !868, !872, !874, !875, !890}
!814 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !812, file: !4, line: 1121, baseType: !171, size: 64, align: 64)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !812, file: !4, line: 1121, baseType: !425, size: 32, align: 32, offset: 64)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !812, file: !4, line: 1121, baseType: !176, size: 128, align: 64, offset: 128)
!817 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !812, file: !4, line: 1121, baseType: !275, size: 256, align: 64, offset: 256)
!818 = !DIDerivedType(tag: DW_TAG_member, name: "fs_type", scope: !812, file: !4, line: 1122, baseType: !819, size: 32, align: 32, offset: 512)
!819 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_type", file: !4, line: 1117, baseType: !125)
!820 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !812, file: !4, line: 1123, baseType: !187, size: 64, align: 64, offset: 576)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !812, file: !4, line: 1124, baseType: !822, size: 64, align: 64, offset: 640)
!822 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_cb", file: !4, line: 315, baseType: !823)
!823 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !808, size: 64, align: 64)
!824 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !812, file: !4, line: 1125, baseType: !593, size: 64, align: 64, offset: 704)
!825 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !812, file: !4, line: 1126, baseType: !171, size: 64, align: 64, offset: 768)
!826 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !812, file: !4, line: 1127, baseType: !390, size: 64, align: 64, offset: 832)
!827 = !DIDerivedType(tag: DW_TAG_member, name: "statbuf", scope: !812, file: !4, line: 1128, baseType: !828, size: 1280, align: 64, offset: 896)
!828 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stat_t", file: !4, line: 349, baseType: !829)
!829 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 332, size: 1280, align: 64, elements: !830)
!830 = !{!831, !832, !833, !834, !835, !836, !837, !838, !839, !840, !841, !842, !843, !849, !850, !851}
!831 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !829, file: !4, line: 333, baseType: !330, size: 64, align: 64)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !829, file: !4, line: 334, baseType: !330, size: 64, align: 64, offset: 64)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !829, file: !4, line: 335, baseType: !330, size: 64, align: 64, offset: 128)
!834 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !829, file: !4, line: 336, baseType: !330, size: 64, align: 64, offset: 192)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !829, file: !4, line: 337, baseType: !330, size: 64, align: 64, offset: 256)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !829, file: !4, line: 338, baseType: !330, size: 64, align: 64, offset: 320)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !829, file: !4, line: 339, baseType: !330, size: 64, align: 64, offset: 384)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !829, file: !4, line: 340, baseType: !330, size: 64, align: 64, offset: 448)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !829, file: !4, line: 341, baseType: !330, size: 64, align: 64, offset: 512)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !829, file: !4, line: 342, baseType: !330, size: 64, align: 64, offset: 576)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "st_flags", scope: !829, file: !4, line: 343, baseType: !330, size: 64, align: 64, offset: 640)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "st_gen", scope: !829, file: !4, line: 344, baseType: !330, size: 64, align: 64, offset: 704)
!843 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !829, file: !4, line: 345, baseType: !844, size: 128, align: 64, offset: 768)
!844 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timespec_t", file: !4, line: 329, baseType: !845)
!845 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 326, size: 128, align: 64, elements: !846)
!846 = !{!847, !848}
!847 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !845, file: !4, line: 327, baseType: !255, size: 64, align: 64)
!848 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !845, file: !4, line: 328, baseType: !255, size: 64, align: 64, offset: 64)
!849 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !829, file: !4, line: 346, baseType: !844, size: 128, align: 64, offset: 896)
!850 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !829, file: !4, line: 347, baseType: !844, size: 128, align: 64, offset: 1024)
!851 = !DIDerivedType(tag: DW_TAG_member, name: "st_birthtim", scope: !829, file: !4, line: 348, baseType: !844, size: 128, align: 64, offset: 1152)
!852 = !DIDerivedType(tag: DW_TAG_member, name: "new_path", scope: !812, file: !4, line: 1129, baseType: !390, size: 64, align: 64, offset: 2176)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !812, file: !4, line: 1129, baseType: !854, size: 32, align: 32, offset: 2240)
!854 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_file", file: !207, line: 121, baseType: !200)
!855 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !812, file: !4, line: 1129, baseType: !200, size: 32, align: 32, offset: 2272)
!856 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !812, file: !4, line: 1129, baseType: !857, size: 32, align: 32, offset: 2304)
!857 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !858, line: 70, baseType: !859)
!858 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!859 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !596, line: 129, baseType: !193)
!860 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !812, file: !4, line: 1129, baseType: !193, size: 32, align: 32, offset: 2336)
!861 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !812, file: !4, line: 1129, baseType: !526, size: 64, align: 64, offset: 2368)
!862 = !DIDerivedType(tag: DW_TAG_member, name: "off", scope: !812, file: !4, line: 1129, baseType: !863, size: 64, align: 64, offset: 2432)
!863 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !594, line: 92, baseType: !744)
!864 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !812, file: !4, line: 1129, baseType: !865, size: 32, align: 32, offset: 2496)
!865 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_uid_t", file: !207, line: 139, baseType: !866)
!866 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !858, line: 80, baseType: !867)
!867 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !596, line: 125, baseType: !193)
!868 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !812, file: !4, line: 1129, baseType: !869, size: 32, align: 32, offset: 2528)
!869 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_gid_t", file: !207, line: 138, baseType: !870)
!870 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !858, line: 65, baseType: !871)
!871 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !596, line: 126, baseType: !193)
!872 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !812, file: !4, line: 1129, baseType: !873, size: 64, align: 64, offset: 2560)
!873 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!874 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !812, file: !4, line: 1129, baseType: !873, size: 64, align: 64, offset: 2624)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !812, file: !4, line: 1129, baseType: !876, size: 320, align: 64, offset: 2688)
!876 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__work", file: !877, line: 30, size: 320, align: 64, elements: !878)
!877 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-threadpool.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!878 = !{!879, !884, !888, !889}
!879 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !876, file: !877, line: 31, baseType: !880, size: 64, align: 64)
!880 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !881, size: 64, align: 64)
!881 = !DISubroutineType(types: !882)
!882 = !{null, !883}
!883 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !876, size: 64, align: 64)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !876, file: !877, line: 32, baseType: !885, size: 64, align: 64, offset: 64)
!885 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !886, size: 64, align: 64)
!886 = !DISubroutineType(types: !887)
!887 = !{null, !883, !200}
!888 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !876, file: !877, line: 33, baseType: !215, size: 64, align: 64, offset: 128)
!889 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !876, file: !877, line: 34, baseType: !176, size: 128, align: 64, offset: 192)
!890 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !812, file: !4, line: 1129, baseType: !683, size: 512, align: 64, offset: 3008)
!891 = distinct !DISubprogram(name: "uv_fs_scandir_next", scope: !1, file: !1, line: 512, type: !892, isLocal: false, isDefinition: true, scopeLine: 512, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!892 = !DISubroutineType(types: !893)
!893 = !{!200, !810, !894}
!894 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !895, size: 64, align: 64)
!895 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_dirent_t", file: !4, line: 236, baseType: !896)
!896 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_dirent_s", file: !4, line: 1031, size: 128, align: 64, elements: !897)
!897 = !{!898, !899}
!898 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !896, file: !4, line: 1032, baseType: !390, size: 64, align: 64)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !896, file: !4, line: 1033, baseType: !900, size: 32, align: 32, offset: 64)
!900 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_dirent_type_t", file: !4, line: 1029, baseType: !157)
!901 = distinct !DISubprogram(name: "uv_loop_configure", scope: !1, file: !1, line: 578, type: !902, isLocal: false, isDefinition: true, scopeLine: 578, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!902 = !DISubroutineType(types: !903)
!903 = !{!200, !187, !904, null}
!904 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_option", file: !4, line: 241, baseType: !167)
!905 = distinct !DISubprogram(name: "uv_default_loop", scope: !1, file: !1, line: 595, type: !906, isLocal: false, isDefinition: true, scopeLine: 595, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!906 = !DISubroutineType(types: !907)
!907 = !{!187}
!908 = distinct !DISubprogram(name: "uv_loop_new", scope: !1, file: !1, line: 607, type: !906, isLocal: false, isDefinition: true, scopeLine: 607, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!909 = distinct !DISubprogram(name: "uv_loop_close", scope: !1, file: !1, line: 623, type: !910, isLocal: false, isDefinition: true, scopeLine: 623, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!910 = !DISubroutineType(types: !911)
!911 = !{!200, !187}
!912 = distinct !DISubprogram(name: "uv_loop_delete", scope: !1, file: !1, line: 653, type: !764, isLocal: false, isDefinition: true, scopeLine: 653, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!913 = distinct !DISubprogram(name: "uv__unknown_err_code", scope: !1, file: !1, line: 148, type: !438, isLocal: true, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!914 = distinct !DISubprogram(name: "uv__print_handles", scope: !1, file: !1, line: 366, type: !915, isLocal: true, isDefinition: true, scopeLine: 366, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!915 = !DISubroutineType(types: !916)
!916 = !{null, !187, !200, !703}
!917 = distinct !DISubprogram(name: "uv__get_nbufs", scope: !1, file: !1, line: 478, type: !918, isLocal: true, isDefinition: true, scopeLine: 478, flags: DIFlagPrototyped, isOptimized: false, variables: !392)
!918 = !DISubroutineType(types: !919)
!919 = !{!920, !810}
!920 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!921 = !{!922, !923, !924}
!922 = !DIGlobalVariable(name: "default_loop_struct", scope: !0, file: !1, line: 591, type: !188, isLocal: true, isDefinition: true, variable: %struct.uv_loop_s* @default_loop_struct)
!923 = !DIGlobalVariable(name: "default_loop_ptr", scope: !0, file: !1, line: 592, type: !187, isLocal: true, isDefinition: true, variable: %struct.uv_loop_s** @default_loop_ptr)
!924 = !DIGlobalVariable(name: "uv__allocator", scope: !0, file: !1, line: 47, type: !925, isLocal: true, isDefinition: true, variable: %struct.uv__allocator_t* @uv__allocator)
!925 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__allocator_t", file: !1, line: 45, baseType: !926)
!926 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 40, size: 256, align: 64, elements: !927)
!927 = !{!928, !929, !930, !931}
!928 = !DIDerivedType(tag: DW_TAG_member, name: "local_malloc", scope: !926, file: !1, line: 41, baseType: !411, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_member, name: "local_realloc", scope: !926, file: !1, line: 42, baseType: !413, size: 64, align: 64, offset: 64)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "local_calloc", scope: !926, file: !1, line: 43, baseType: !415, size: 64, align: 64, offset: 128)
!931 = !DIDerivedType(tag: DW_TAG_member, name: "local_free", scope: !926, file: !1, line: 44, baseType: !417, size: 64, align: 64, offset: 192)
!932 = !{i32 2, !"Dwarf Version", i32 4}
!933 = !{i32 2, !"Debug Info Version", i32 3}
!934 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!935 = !DILocalVariable(name: "s", arg: 1, scope: !387, file: !1, line: 54, type: !390)
!936 = !DIExpression()
!937 = !DILocation(line: 54, column: 30, scope: !387)
!938 = !DILocalVariable(name: "len", scope: !387, file: !1, line: 55, type: !384)
!939 = !DILocation(line: 55, column: 10, scope: !387)
!940 = !DILocation(line: 55, column: 23, scope: !387)
!941 = !DILocation(line: 55, column: 16, scope: !387)
!942 = !DILocation(line: 55, column: 26, scope: !387)
!943 = !DILocalVariable(name: "m", scope: !387, file: !1, line: 56, type: !383)
!944 = !DILocation(line: 56, column: 9, scope: !387)
!945 = !DILocation(line: 56, column: 24, scope: !387)
!946 = !DILocation(line: 56, column: 13, scope: !387)
!947 = !DILocation(line: 57, column: 7, scope: !948)
!948 = distinct !DILexicalBlock(scope: !387, file: !1, line: 57, column: 7)
!949 = !DILocation(line: 57, column: 9, scope: !948)
!950 = !DILocation(line: 57, column: 7, scope: !387)
!951 = !DILocation(line: 58, column: 5, scope: !948)
!952 = !DILocation(line: 59, column: 17, scope: !387)
!953 = !DILocation(line: 59, column: 20, scope: !387)
!954 = !DILocation(line: 59, column: 23, scope: !387)
!955 = !DILocation(line: 59, column: 10, scope: !387)
!956 = !DILocation(line: 59, column: 3, scope: !387)
!957 = !DILocation(line: 60, column: 1, scope: !387)
!958 = !DILocalVariable(name: "size", arg: 1, scope: !396, file: !1, line: 74, type: !384)
!959 = !DILocation(line: 74, column: 25, scope: !396)
!960 = !DILocation(line: 75, column: 24, scope: !396)
!961 = !DILocation(line: 75, column: 37, scope: !396)
!962 = !DILocation(line: 75, column: 10, scope: !396)
!963 = !DILocation(line: 75, column: 3, scope: !396)
!964 = !DILocalVariable(name: "s", arg: 1, scope: !393, file: !1, line: 62, type: !390)
!965 = !DILocation(line: 62, column: 31, scope: !393)
!966 = !DILocalVariable(name: "n", arg: 2, scope: !393, file: !1, line: 62, type: !384)
!967 = !DILocation(line: 62, column: 41, scope: !393)
!968 = !DILocalVariable(name: "m", scope: !393, file: !1, line: 63, type: !383)
!969 = !DILocation(line: 63, column: 9, scope: !393)
!970 = !DILocalVariable(name: "len", scope: !393, file: !1, line: 64, type: !384)
!971 = !DILocation(line: 64, column: 10, scope: !393)
!972 = !DILocation(line: 64, column: 23, scope: !393)
!973 = !DILocation(line: 64, column: 16, scope: !393)
!974 = !DILocation(line: 65, column: 7, scope: !975)
!975 = distinct !DILexicalBlock(scope: !393, file: !1, line: 65, column: 7)
!976 = !DILocation(line: 65, column: 11, scope: !975)
!977 = !DILocation(line: 65, column: 9, scope: !975)
!978 = !DILocation(line: 65, column: 7, scope: !393)
!979 = !DILocation(line: 66, column: 11, scope: !975)
!980 = !DILocation(line: 66, column: 9, scope: !975)
!981 = !DILocation(line: 66, column: 5, scope: !975)
!982 = !DILocation(line: 67, column: 18, scope: !393)
!983 = !DILocation(line: 67, column: 22, scope: !393)
!984 = !DILocation(line: 67, column: 7, scope: !393)
!985 = !DILocation(line: 67, column: 5, scope: !393)
!986 = !DILocation(line: 68, column: 7, scope: !987)
!987 = distinct !DILexicalBlock(scope: !393, file: !1, line: 68, column: 7)
!988 = !DILocation(line: 68, column: 9, scope: !987)
!989 = !DILocation(line: 68, column: 7, scope: !393)
!990 = !DILocation(line: 69, column: 5, scope: !987)
!991 = !DILocation(line: 70, column: 5, scope: !393)
!992 = !DILocation(line: 70, column: 3, scope: !393)
!993 = !DILocation(line: 70, column: 10, scope: !393)
!994 = !DILocation(line: 71, column: 17, scope: !393)
!995 = !DILocation(line: 71, column: 20, scope: !393)
!996 = !DILocation(line: 71, column: 23, scope: !393)
!997 = !DILocation(line: 71, column: 10, scope: !393)
!998 = !DILocation(line: 71, column: 3, scope: !393)
!999 = !DILocation(line: 72, column: 1, scope: !393)
!1000 = !DILocalVariable(name: "ptr", arg: 1, scope: !399, file: !1, line: 78, type: !171)
!1001 = !DILocation(line: 78, column: 21, scope: !399)
!1002 = !DILocalVariable(name: "saved_errno", scope: !399, file: !1, line: 79, type: !200)
!1003 = !DILocation(line: 79, column: 7, scope: !399)
!1004 = !DILocation(line: 84, column: 17, scope: !399)
!1005 = !DILocation(line: 84, column: 15, scope: !399)
!1006 = !DILocation(line: 85, column: 17, scope: !399)
!1007 = !DILocation(line: 85, column: 28, scope: !399)
!1008 = !DILocation(line: 85, column: 3, scope: !399)
!1009 = !DILocation(line: 86, column: 11, scope: !399)
!1010 = !DILocation(line: 86, column: 3, scope: !399)
!1011 = !DILocation(line: 86, column: 9, scope: !399)
!1012 = !DILocation(line: 87, column: 1, scope: !399)
!1013 = !DILocalVariable(name: "count", arg: 1, scope: !402, file: !1, line: 89, type: !384)
!1014 = !DILocation(line: 89, column: 25, scope: !402)
!1015 = !DILocalVariable(name: "size", arg: 2, scope: !402, file: !1, line: 89, type: !384)
!1016 = !DILocation(line: 89, column: 39, scope: !402)
!1017 = !DILocation(line: 90, column: 24, scope: !402)
!1018 = !DILocation(line: 90, column: 37, scope: !402)
!1019 = !DILocation(line: 90, column: 44, scope: !402)
!1020 = !DILocation(line: 90, column: 10, scope: !402)
!1021 = !DILocation(line: 90, column: 3, scope: !402)
!1022 = !DILocalVariable(name: "ptr", arg: 1, scope: !405, file: !1, line: 93, type: !171)
!1023 = !DILocation(line: 93, column: 25, scope: !405)
!1024 = !DILocalVariable(name: "size", arg: 2, scope: !405, file: !1, line: 93, type: !384)
!1025 = !DILocation(line: 93, column: 37, scope: !405)
!1026 = !DILocation(line: 94, column: 24, scope: !405)
!1027 = !DILocation(line: 94, column: 38, scope: !405)
!1028 = !DILocation(line: 94, column: 43, scope: !405)
!1029 = !DILocation(line: 94, column: 10, scope: !405)
!1030 = !DILocation(line: 94, column: 3, scope: !405)
!1031 = !DILocalVariable(name: "malloc_func", arg: 1, scope: !408, file: !1, line: 97, type: !411)
!1032 = !DILocation(line: 97, column: 41, scope: !408)
!1033 = !DILocalVariable(name: "realloc_func", arg: 2, scope: !408, file: !1, line: 98, type: !413)
!1034 = !DILocation(line: 98, column: 42, scope: !408)
!1035 = !DILocalVariable(name: "calloc_func", arg: 3, scope: !408, file: !1, line: 99, type: !415)
!1036 = !DILocation(line: 99, column: 41, scope: !408)
!1037 = !DILocalVariable(name: "free_func", arg: 4, scope: !408, file: !1, line: 100, type: !417)
!1038 = !DILocation(line: 100, column: 39, scope: !408)
!1039 = !DILocation(line: 101, column: 7, scope: !1040)
!1040 = distinct !DILexicalBlock(scope: !408, file: !1, line: 101, column: 7)
!1041 = !DILocation(line: 101, column: 19, scope: !1040)
!1042 = !DILocation(line: 101, column: 27, scope: !1040)
!1043 = !DILocation(line: 101, column: 30, scope: !1044)
!1044 = !DILexicalBlockFile(scope: !1040, file: !1, discriminator: 1)
!1045 = !DILocation(line: 101, column: 43, scope: !1044)
!1046 = !DILocation(line: 101, column: 51, scope: !1044)
!1047 = !DILocation(line: 102, column: 7, scope: !1040)
!1048 = !DILocation(line: 102, column: 19, scope: !1040)
!1049 = !DILocation(line: 102, column: 27, scope: !1040)
!1050 = !DILocation(line: 102, column: 30, scope: !1044)
!1051 = !DILocation(line: 102, column: 40, scope: !1044)
!1052 = !DILocation(line: 101, column: 7, scope: !1053)
!1053 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 2)
!1054 = !DILocation(line: 103, column: 5, scope: !1055)
!1055 = distinct !DILexicalBlock(scope: !1040, file: !1, line: 102, column: 49)
!1056 = !DILocation(line: 106, column: 32, scope: !408)
!1057 = !DILocation(line: 106, column: 30, scope: !408)
!1058 = !DILocation(line: 107, column: 33, scope: !408)
!1059 = !DILocation(line: 107, column: 31, scope: !408)
!1060 = !DILocation(line: 108, column: 32, scope: !408)
!1061 = !DILocation(line: 108, column: 30, scope: !408)
!1062 = !DILocation(line: 109, column: 30, scope: !408)
!1063 = !DILocation(line: 109, column: 28, scope: !408)
!1064 = !DILocation(line: 111, column: 3, scope: !408)
!1065 = !DILocation(line: 112, column: 1, scope: !408)
!1066 = !DILocalVariable(name: "type", arg: 1, scope: !419, file: !1, line: 116, type: !263)
!1067 = !DILocation(line: 116, column: 38, scope: !419)
!1068 = !DILocation(line: 117, column: 11, scope: !419)
!1069 = !DILocation(line: 117, column: 3, scope: !419)
!1070 = !DILocation(line: 118, column: 5, scope: !1071)
!1071 = distinct !DILexicalBlock(scope: !419, file: !1, line: 117, column: 17)
!1072 = !DILocation(line: 118, column: 5, scope: !1073)
!1073 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 1)
!1074 = !DILocation(line: 118, column: 5, scope: !1075)
!1075 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 2)
!1076 = !DILocation(line: 118, column: 5, scope: !1077)
!1077 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 3)
!1078 = !DILocation(line: 118, column: 5, scope: !1079)
!1079 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 4)
!1080 = !DILocation(line: 118, column: 5, scope: !1081)
!1081 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 5)
!1082 = !DILocation(line: 118, column: 5, scope: !1083)
!1083 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 6)
!1084 = !DILocation(line: 118, column: 5, scope: !1085)
!1085 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 7)
!1086 = !DILocation(line: 118, column: 5, scope: !1087)
!1087 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 8)
!1088 = !DILocation(line: 118, column: 5, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 9)
!1090 = !DILocation(line: 118, column: 5, scope: !1091)
!1091 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 10)
!1092 = !DILocation(line: 118, column: 5, scope: !1093)
!1093 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 11)
!1094 = !DILocation(line: 118, column: 5, scope: !1095)
!1095 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 12)
!1096 = !DILocation(line: 118, column: 5, scope: !1097)
!1097 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 13)
!1098 = !DILocation(line: 118, column: 5, scope: !1099)
!1099 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 14)
!1100 = !DILocation(line: 118, column: 5, scope: !1101)
!1101 = !DILexicalBlockFile(scope: !1071, file: !1, discriminator: 15)
!1102 = !DILocation(line: 120, column: 7, scope: !1071)
!1103 = !DILocation(line: 122, column: 1, scope: !419)
!1104 = !DILocalVariable(name: "type", arg: 1, scope: !422, file: !1, line: 124, type: !425)
!1105 = !DILocation(line: 124, column: 32, scope: !422)
!1106 = !DILocation(line: 125, column: 10, scope: !422)
!1107 = !DILocation(line: 125, column: 3, scope: !422)
!1108 = !DILocation(line: 126, column: 5, scope: !1109)
!1109 = distinct !DILexicalBlock(scope: !422, file: !1, line: 125, column: 16)
!1110 = !DILocation(line: 126, column: 5, scope: !1111)
!1111 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 1)
!1112 = !DILocation(line: 126, column: 5, scope: !1113)
!1113 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 2)
!1114 = !DILocation(line: 126, column: 5, scope: !1115)
!1115 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 3)
!1116 = !DILocation(line: 126, column: 5, scope: !1117)
!1117 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 4)
!1118 = !DILocation(line: 126, column: 5, scope: !1119)
!1119 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 5)
!1120 = !DILocation(line: 126, column: 5, scope: !1121)
!1121 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 6)
!1122 = !DILocation(line: 126, column: 5, scope: !1123)
!1123 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 7)
!1124 = !DILocation(line: 126, column: 5, scope: !1125)
!1125 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 8)
!1126 = !DILocation(line: 128, column: 7, scope: !1109)
!1127 = !DILocation(line: 130, column: 1, scope: !422)
!1128 = !DILocation(line: 136, column: 3, scope: !426)
!1129 = !DILocalVariable(name: "base", arg: 1, scope: !429, file: !1, line: 140, type: !383)
!1130 = !DILocation(line: 140, column: 28, scope: !429)
!1131 = !DILocalVariable(name: "len", arg: 2, scope: !429, file: !1, line: 140, type: !193)
!1132 = !DILocation(line: 140, column: 47, scope: !429)
!1133 = !DILocalVariable(name: "buf", scope: !429, file: !1, line: 141, type: !432)
!1134 = !DILocation(line: 141, column: 12, scope: !429)
!1135 = !DILocation(line: 142, column: 14, scope: !429)
!1136 = !DILocation(line: 142, column: 7, scope: !429)
!1137 = !DILocation(line: 142, column: 12, scope: !429)
!1138 = !DILocation(line: 143, column: 13, scope: !429)
!1139 = !DILocation(line: 143, column: 7, scope: !429)
!1140 = !DILocation(line: 143, column: 11, scope: !429)
!1141 = !DILocation(line: 144, column: 10, scope: !429)
!1142 = !DILocation(line: 144, column: 3, scope: !429)
!1143 = !DILocalVariable(name: "err", arg: 1, scope: !437, file: !1, line: 160, type: !200)
!1144 = !DILocation(line: 160, column: 29, scope: !437)
!1145 = !DILocation(line: 161, column: 11, scope: !437)
!1146 = !DILocation(line: 161, column: 3, scope: !437)
!1147 = !DILocation(line: 162, column: 5, scope: !1148)
!1148 = distinct !DILexicalBlock(scope: !437, file: !1, line: 161, column: 16)
!1149 = !DILocation(line: 162, column: 5, scope: !1150)
!1150 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 1)
!1151 = !DILocation(line: 162, column: 5, scope: !1152)
!1152 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 2)
!1153 = !DILocation(line: 162, column: 5, scope: !1154)
!1154 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 3)
!1155 = !DILocation(line: 162, column: 5, scope: !1156)
!1156 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 4)
!1157 = !DILocation(line: 162, column: 5, scope: !1158)
!1158 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 5)
!1159 = !DILocation(line: 162, column: 5, scope: !1160)
!1160 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 6)
!1161 = !DILocation(line: 162, column: 5, scope: !1162)
!1162 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 7)
!1163 = !DILocation(line: 162, column: 5, scope: !1164)
!1164 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 8)
!1165 = !DILocation(line: 162, column: 5, scope: !1166)
!1166 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 9)
!1167 = !DILocation(line: 162, column: 5, scope: !1168)
!1168 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 10)
!1169 = !DILocation(line: 162, column: 5, scope: !1170)
!1170 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 11)
!1171 = !DILocation(line: 162, column: 5, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 12)
!1173 = !DILocation(line: 162, column: 5, scope: !1174)
!1174 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 13)
!1175 = !DILocation(line: 162, column: 5, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 14)
!1177 = !DILocation(line: 162, column: 5, scope: !1178)
!1178 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 15)
!1179 = !DILocation(line: 162, column: 5, scope: !1180)
!1180 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 16)
!1181 = !DILocation(line: 162, column: 5, scope: !1182)
!1182 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 17)
!1183 = !DILocation(line: 162, column: 5, scope: !1184)
!1184 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 18)
!1185 = !DILocation(line: 162, column: 5, scope: !1186)
!1186 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 19)
!1187 = !DILocation(line: 162, column: 5, scope: !1188)
!1188 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 20)
!1189 = !DILocation(line: 162, column: 5, scope: !1190)
!1190 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 21)
!1191 = !DILocation(line: 162, column: 5, scope: !1192)
!1192 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 22)
!1193 = !DILocation(line: 162, column: 5, scope: !1194)
!1194 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 23)
!1195 = !DILocation(line: 162, column: 5, scope: !1196)
!1196 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 24)
!1197 = !DILocation(line: 162, column: 5, scope: !1198)
!1198 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 25)
!1199 = !DILocation(line: 162, column: 5, scope: !1200)
!1200 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 26)
!1201 = !DILocation(line: 162, column: 5, scope: !1202)
!1202 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 27)
!1203 = !DILocation(line: 162, column: 5, scope: !1204)
!1204 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 28)
!1205 = !DILocation(line: 162, column: 5, scope: !1206)
!1206 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 29)
!1207 = !DILocation(line: 162, column: 5, scope: !1208)
!1208 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 30)
!1209 = !DILocation(line: 162, column: 5, scope: !1210)
!1210 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 31)
!1211 = !DILocation(line: 162, column: 5, scope: !1212)
!1212 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 32)
!1213 = !DILocation(line: 162, column: 5, scope: !1214)
!1214 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 33)
!1215 = !DILocation(line: 162, column: 5, scope: !1216)
!1216 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 34)
!1217 = !DILocation(line: 162, column: 5, scope: !1218)
!1218 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 35)
!1219 = !DILocation(line: 162, column: 5, scope: !1220)
!1220 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 36)
!1221 = !DILocation(line: 162, column: 5, scope: !1222)
!1222 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 37)
!1223 = !DILocation(line: 162, column: 5, scope: !1224)
!1224 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 38)
!1225 = !DILocation(line: 162, column: 5, scope: !1226)
!1226 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 39)
!1227 = !DILocation(line: 162, column: 5, scope: !1228)
!1228 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 40)
!1229 = !DILocation(line: 162, column: 5, scope: !1230)
!1230 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 41)
!1231 = !DILocation(line: 162, column: 5, scope: !1232)
!1232 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 42)
!1233 = !DILocation(line: 162, column: 5, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 43)
!1235 = !DILocation(line: 162, column: 5, scope: !1236)
!1236 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 44)
!1237 = !DILocation(line: 162, column: 5, scope: !1238)
!1238 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 45)
!1239 = !DILocation(line: 162, column: 5, scope: !1240)
!1240 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 46)
!1241 = !DILocation(line: 162, column: 5, scope: !1242)
!1242 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 47)
!1243 = !DILocation(line: 162, column: 5, scope: !1244)
!1244 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 48)
!1245 = !DILocation(line: 162, column: 5, scope: !1246)
!1246 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 49)
!1247 = !DILocation(line: 162, column: 5, scope: !1248)
!1248 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 50)
!1249 = !DILocation(line: 162, column: 5, scope: !1250)
!1250 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 51)
!1251 = !DILocation(line: 162, column: 5, scope: !1252)
!1252 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 52)
!1253 = !DILocation(line: 162, column: 5, scope: !1254)
!1254 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 53)
!1255 = !DILocation(line: 162, column: 5, scope: !1256)
!1256 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 54)
!1257 = !DILocation(line: 162, column: 5, scope: !1258)
!1258 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 55)
!1259 = !DILocation(line: 162, column: 5, scope: !1260)
!1260 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 56)
!1261 = !DILocation(line: 162, column: 5, scope: !1262)
!1262 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 57)
!1263 = !DILocation(line: 162, column: 5, scope: !1264)
!1264 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 58)
!1265 = !DILocation(line: 162, column: 5, scope: !1266)
!1266 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 59)
!1267 = !DILocation(line: 162, column: 5, scope: !1268)
!1268 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 60)
!1269 = !DILocation(line: 162, column: 5, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 61)
!1271 = !DILocation(line: 162, column: 5, scope: !1272)
!1272 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 62)
!1273 = !DILocation(line: 162, column: 5, scope: !1274)
!1274 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 63)
!1275 = !DILocation(line: 162, column: 5, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 64)
!1277 = !DILocation(line: 162, column: 5, scope: !1278)
!1278 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 65)
!1279 = !DILocation(line: 162, column: 5, scope: !1280)
!1280 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 66)
!1281 = !DILocation(line: 162, column: 5, scope: !1282)
!1282 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 67)
!1283 = !DILocation(line: 162, column: 5, scope: !1284)
!1284 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 68)
!1285 = !DILocation(line: 162, column: 5, scope: !1286)
!1286 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 69)
!1287 = !DILocation(line: 162, column: 5, scope: !1288)
!1288 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 70)
!1289 = !DILocation(line: 162, column: 5, scope: !1290)
!1290 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 71)
!1291 = !DILocation(line: 162, column: 5, scope: !1292)
!1292 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 72)
!1293 = !DILocation(line: 162, column: 5, scope: !1294)
!1294 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 73)
!1295 = !DILocation(line: 162, column: 5, scope: !1296)
!1296 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 74)
!1297 = !DILocation(line: 162, column: 5, scope: !1298)
!1298 = !DILexicalBlockFile(scope: !1148, file: !1, discriminator: 75)
!1299 = !DILocation(line: 164, column: 31, scope: !437)
!1300 = !DILocation(line: 164, column: 10, scope: !437)
!1301 = !DILocation(line: 164, column: 3, scope: !437)
!1302 = !DILocation(line: 165, column: 1, scope: !437)
!1303 = !DILocalVariable(name: "err", arg: 1, scope: !913, file: !1, line: 148, type: !200)
!1304 = !DILocation(line: 148, column: 45, scope: !913)
!1305 = !DILocalVariable(name: "buf", scope: !913, file: !1, line: 149, type: !1306)
!1306 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 256, align: 8, elements: !1307)
!1307 = !{!1308}
!1308 = !DISubrange(count: 32)
!1309 = !DILocation(line: 149, column: 8, scope: !913)
!1310 = !DILocalVariable(name: "copy", scope: !913, file: !1, line: 150, type: !383)
!1311 = !DILocation(line: 150, column: 9, scope: !913)
!1312 = !DILocation(line: 152, column: 12, scope: !913)
!1313 = !DILocation(line: 152, column: 57, scope: !913)
!1314 = !DILocation(line: 152, column: 3, scope: !913)
!1315 = !DILocation(line: 153, column: 21, scope: !913)
!1316 = !DILocation(line: 153, column: 10, scope: !913)
!1317 = !DILocation(line: 153, column: 8, scope: !913)
!1318 = !DILocation(line: 155, column: 10, scope: !913)
!1319 = !DILocation(line: 155, column: 15, scope: !913)
!1320 = !DILocation(line: 155, column: 25, scope: !1321)
!1321 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 1)
!1322 = !DILocation(line: 155, column: 10, scope: !1321)
!1323 = !DILocation(line: 155, column: 10, scope: !1324)
!1324 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 2)
!1325 = !DILocation(line: 155, column: 10, scope: !1326)
!1326 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 3)
!1327 = !DILocation(line: 155, column: 3, scope: !1326)
!1328 = !DILocalVariable(name: "err", arg: 1, scope: !440, file: !1, line: 170, type: !200)
!1329 = !DILocation(line: 170, column: 29, scope: !440)
!1330 = !DILocation(line: 171, column: 11, scope: !440)
!1331 = !DILocation(line: 171, column: 3, scope: !440)
!1332 = !DILocation(line: 172, column: 5, scope: !1333)
!1333 = distinct !DILexicalBlock(scope: !440, file: !1, line: 171, column: 16)
!1334 = !DILocation(line: 172, column: 5, scope: !1335)
!1335 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 1)
!1336 = !DILocation(line: 172, column: 5, scope: !1337)
!1337 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 2)
!1338 = !DILocation(line: 172, column: 5, scope: !1339)
!1339 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 3)
!1340 = !DILocation(line: 172, column: 5, scope: !1341)
!1341 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 4)
!1342 = !DILocation(line: 172, column: 5, scope: !1343)
!1343 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 5)
!1344 = !DILocation(line: 172, column: 5, scope: !1345)
!1345 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 6)
!1346 = !DILocation(line: 172, column: 5, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 7)
!1348 = !DILocation(line: 172, column: 5, scope: !1349)
!1349 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 8)
!1350 = !DILocation(line: 172, column: 5, scope: !1351)
!1351 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 9)
!1352 = !DILocation(line: 172, column: 5, scope: !1353)
!1353 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 10)
!1354 = !DILocation(line: 172, column: 5, scope: !1355)
!1355 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 11)
!1356 = !DILocation(line: 172, column: 5, scope: !1357)
!1357 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 12)
!1358 = !DILocation(line: 172, column: 5, scope: !1359)
!1359 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 13)
!1360 = !DILocation(line: 172, column: 5, scope: !1361)
!1361 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 14)
!1362 = !DILocation(line: 172, column: 5, scope: !1363)
!1363 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 15)
!1364 = !DILocation(line: 172, column: 5, scope: !1365)
!1365 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 16)
!1366 = !DILocation(line: 172, column: 5, scope: !1367)
!1367 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 17)
!1368 = !DILocation(line: 172, column: 5, scope: !1369)
!1369 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 18)
!1370 = !DILocation(line: 172, column: 5, scope: !1371)
!1371 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 19)
!1372 = !DILocation(line: 172, column: 5, scope: !1373)
!1373 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 20)
!1374 = !DILocation(line: 172, column: 5, scope: !1375)
!1375 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 21)
!1376 = !DILocation(line: 172, column: 5, scope: !1377)
!1377 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 22)
!1378 = !DILocation(line: 172, column: 5, scope: !1379)
!1379 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 23)
!1380 = !DILocation(line: 172, column: 5, scope: !1381)
!1381 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 24)
!1382 = !DILocation(line: 172, column: 5, scope: !1383)
!1383 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 25)
!1384 = !DILocation(line: 172, column: 5, scope: !1385)
!1385 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 26)
!1386 = !DILocation(line: 172, column: 5, scope: !1387)
!1387 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 27)
!1388 = !DILocation(line: 172, column: 5, scope: !1389)
!1389 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 28)
!1390 = !DILocation(line: 172, column: 5, scope: !1391)
!1391 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 29)
!1392 = !DILocation(line: 172, column: 5, scope: !1393)
!1393 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 30)
!1394 = !DILocation(line: 172, column: 5, scope: !1395)
!1395 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 31)
!1396 = !DILocation(line: 172, column: 5, scope: !1397)
!1397 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 32)
!1398 = !DILocation(line: 172, column: 5, scope: !1399)
!1399 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 33)
!1400 = !DILocation(line: 172, column: 5, scope: !1401)
!1401 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 34)
!1402 = !DILocation(line: 172, column: 5, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 35)
!1404 = !DILocation(line: 172, column: 5, scope: !1405)
!1405 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 36)
!1406 = !DILocation(line: 172, column: 5, scope: !1407)
!1407 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 37)
!1408 = !DILocation(line: 172, column: 5, scope: !1409)
!1409 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 38)
!1410 = !DILocation(line: 172, column: 5, scope: !1411)
!1411 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 39)
!1412 = !DILocation(line: 172, column: 5, scope: !1413)
!1413 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 40)
!1414 = !DILocation(line: 172, column: 5, scope: !1415)
!1415 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 41)
!1416 = !DILocation(line: 172, column: 5, scope: !1417)
!1417 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 42)
!1418 = !DILocation(line: 172, column: 5, scope: !1419)
!1419 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 43)
!1420 = !DILocation(line: 172, column: 5, scope: !1421)
!1421 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 44)
!1422 = !DILocation(line: 172, column: 5, scope: !1423)
!1423 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 45)
!1424 = !DILocation(line: 172, column: 5, scope: !1425)
!1425 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 46)
!1426 = !DILocation(line: 172, column: 5, scope: !1427)
!1427 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 47)
!1428 = !DILocation(line: 172, column: 5, scope: !1429)
!1429 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 48)
!1430 = !DILocation(line: 172, column: 5, scope: !1431)
!1431 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 49)
!1432 = !DILocation(line: 172, column: 5, scope: !1433)
!1433 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 50)
!1434 = !DILocation(line: 172, column: 5, scope: !1435)
!1435 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 51)
!1436 = !DILocation(line: 172, column: 5, scope: !1437)
!1437 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 52)
!1438 = !DILocation(line: 172, column: 5, scope: !1439)
!1439 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 53)
!1440 = !DILocation(line: 172, column: 5, scope: !1441)
!1441 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 54)
!1442 = !DILocation(line: 172, column: 5, scope: !1443)
!1443 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 55)
!1444 = !DILocation(line: 172, column: 5, scope: !1445)
!1445 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 56)
!1446 = !DILocation(line: 172, column: 5, scope: !1447)
!1447 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 57)
!1448 = !DILocation(line: 172, column: 5, scope: !1449)
!1449 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 58)
!1450 = !DILocation(line: 172, column: 5, scope: !1451)
!1451 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 59)
!1452 = !DILocation(line: 172, column: 5, scope: !1453)
!1453 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 60)
!1454 = !DILocation(line: 172, column: 5, scope: !1455)
!1455 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 61)
!1456 = !DILocation(line: 172, column: 5, scope: !1457)
!1457 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 62)
!1458 = !DILocation(line: 172, column: 5, scope: !1459)
!1459 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 63)
!1460 = !DILocation(line: 172, column: 5, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 64)
!1462 = !DILocation(line: 172, column: 5, scope: !1463)
!1463 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 65)
!1464 = !DILocation(line: 172, column: 5, scope: !1465)
!1465 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 66)
!1466 = !DILocation(line: 172, column: 5, scope: !1467)
!1467 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 67)
!1468 = !DILocation(line: 172, column: 5, scope: !1469)
!1469 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 68)
!1470 = !DILocation(line: 172, column: 5, scope: !1471)
!1471 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 69)
!1472 = !DILocation(line: 172, column: 5, scope: !1473)
!1473 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 70)
!1474 = !DILocation(line: 172, column: 5, scope: !1475)
!1475 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 71)
!1476 = !DILocation(line: 172, column: 5, scope: !1477)
!1477 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 72)
!1478 = !DILocation(line: 172, column: 5, scope: !1479)
!1479 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 73)
!1480 = !DILocation(line: 172, column: 5, scope: !1481)
!1481 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 74)
!1482 = !DILocation(line: 172, column: 5, scope: !1483)
!1483 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 75)
!1484 = !DILocation(line: 174, column: 31, scope: !440)
!1485 = !DILocation(line: 174, column: 10, scope: !440)
!1486 = !DILocation(line: 174, column: 3, scope: !440)
!1487 = !DILocation(line: 175, column: 1, scope: !440)
!1488 = !DILocalVariable(name: "ip", arg: 1, scope: !441, file: !1, line: 179, type: !390)
!1489 = !DILocation(line: 179, column: 29, scope: !441)
!1490 = !DILocalVariable(name: "port", arg: 2, scope: !441, file: !1, line: 179, type: !200)
!1491 = !DILocation(line: 179, column: 37, scope: !441)
!1492 = !DILocalVariable(name: "addr", arg: 3, scope: !441, file: !1, line: 179, type: !444)
!1493 = !DILocation(line: 179, column: 63, scope: !441)
!1494 = !DILocation(line: 180, column: 10, scope: !441)
!1495 = !DILocation(line: 180, column: 3, scope: !441)
!1496 = !DILocation(line: 181, column: 3, scope: !441)
!1497 = !DILocation(line: 181, column: 9, scope: !441)
!1498 = !DILocation(line: 181, column: 20, scope: !441)
!1499 = !DILocation(line: 182, column: 26, scope: !441)
!1500 = !DILocation(line: 182, column: 20, scope: !441)
!1501 = !DILocation(line: 182, column: 3, scope: !441)
!1502 = !DILocation(line: 182, column: 9, scope: !441)
!1503 = !DILocation(line: 182, column: 18, scope: !441)
!1504 = !DILocation(line: 183, column: 32, scope: !441)
!1505 = !DILocation(line: 183, column: 38, scope: !441)
!1506 = !DILocation(line: 183, column: 44, scope: !441)
!1507 = !DILocation(line: 183, column: 53, scope: !441)
!1508 = !DILocation(line: 183, column: 36, scope: !441)
!1509 = !DILocation(line: 183, column: 10, scope: !441)
!1510 = !DILocation(line: 183, column: 3, scope: !441)
!1511 = !DILocalVariable(name: "ip", arg: 1, scope: !466, file: !1, line: 187, type: !390)
!1512 = !DILocation(line: 187, column: 29, scope: !466)
!1513 = !DILocalVariable(name: "port", arg: 2, scope: !466, file: !1, line: 187, type: !200)
!1514 = !DILocation(line: 187, column: 37, scope: !466)
!1515 = !DILocalVariable(name: "addr", arg: 3, scope: !466, file: !1, line: 187, type: !469)
!1516 = !DILocation(line: 187, column: 64, scope: !466)
!1517 = !DILocalVariable(name: "address_part", scope: !466, file: !1, line: 188, type: !250)
!1518 = !DILocation(line: 188, column: 8, scope: !466)
!1519 = !DILocalVariable(name: "address_part_size", scope: !466, file: !1, line: 189, type: !384)
!1520 = !DILocation(line: 189, column: 10, scope: !466)
!1521 = !DILocalVariable(name: "zone_index", scope: !466, file: !1, line: 190, type: !390)
!1522 = !DILocation(line: 190, column: 15, scope: !466)
!1523 = !DILocation(line: 192, column: 10, scope: !466)
!1524 = !DILocation(line: 192, column: 3, scope: !466)
!1525 = !DILocation(line: 193, column: 3, scope: !466)
!1526 = !DILocation(line: 193, column: 9, scope: !466)
!1527 = !DILocation(line: 193, column: 21, scope: !466)
!1528 = !DILocation(line: 194, column: 27, scope: !466)
!1529 = !DILocation(line: 194, column: 21, scope: !466)
!1530 = !DILocation(line: 194, column: 3, scope: !466)
!1531 = !DILocation(line: 194, column: 9, scope: !466)
!1532 = !DILocation(line: 194, column: 19, scope: !466)
!1533 = !DILocation(line: 196, column: 23, scope: !466)
!1534 = !DILocation(line: 196, column: 16, scope: !466)
!1535 = !DILocation(line: 196, column: 14, scope: !466)
!1536 = !DILocation(line: 197, column: 7, scope: !1537)
!1537 = distinct !DILexicalBlock(scope: !466, file: !1, line: 197, column: 7)
!1538 = !DILocation(line: 197, column: 18, scope: !1537)
!1539 = !DILocation(line: 197, column: 7, scope: !466)
!1540 = !DILocation(line: 198, column: 25, scope: !1541)
!1541 = distinct !DILexicalBlock(scope: !1537, file: !1, line: 197, column: 27)
!1542 = !DILocation(line: 198, column: 38, scope: !1541)
!1543 = !DILocation(line: 198, column: 36, scope: !1541)
!1544 = !DILocation(line: 198, column: 23, scope: !1541)
!1545 = !DILocation(line: 199, column: 9, scope: !1546)
!1546 = distinct !DILexicalBlock(scope: !1541, file: !1, line: 199, column: 9)
!1547 = !DILocation(line: 199, column: 27, scope: !1546)
!1548 = !DILocation(line: 199, column: 9, scope: !1541)
!1549 = !DILocation(line: 200, column: 25, scope: !1546)
!1550 = !DILocation(line: 200, column: 7, scope: !1546)
!1551 = !DILocation(line: 202, column: 5, scope: !1541)
!1552 = !DILocation(line: 202, column: 26, scope: !1541)
!1553 = !DILocation(line: 202, column: 30, scope: !1541)
!1554 = !DILocation(line: 203, column: 18, scope: !1541)
!1555 = !DILocation(line: 203, column: 5, scope: !1541)
!1556 = !DILocation(line: 203, column: 37, scope: !1541)
!1557 = !DILocation(line: 204, column: 10, scope: !1541)
!1558 = !DILocation(line: 204, column: 8, scope: !1541)
!1559 = !DILocation(line: 206, column: 15, scope: !1541)
!1560 = !DILocation(line: 211, column: 42, scope: !1541)
!1561 = !DILocation(line: 211, column: 27, scope: !1541)
!1562 = !DILocation(line: 211, column: 5, scope: !1541)
!1563 = !DILocation(line: 211, column: 11, scope: !1541)
!1564 = !DILocation(line: 211, column: 25, scope: !1541)
!1565 = !DILocation(line: 213, column: 3, scope: !1541)
!1566 = !DILocation(line: 215, column: 33, scope: !466)
!1567 = !DILocation(line: 215, column: 38, scope: !466)
!1568 = !DILocation(line: 215, column: 44, scope: !466)
!1569 = !DILocation(line: 215, column: 37, scope: !466)
!1570 = !DILocation(line: 215, column: 10, scope: !466)
!1571 = !DILocation(line: 215, column: 3, scope: !466)
!1572 = !DILocalVariable(name: "src", arg: 1, scope: !491, file: !1, line: 219, type: !494)
!1573 = !DILocation(line: 219, column: 43, scope: !491)
!1574 = !DILocalVariable(name: "dst", arg: 2, scope: !491, file: !1, line: 219, type: !383)
!1575 = !DILocation(line: 219, column: 54, scope: !491)
!1576 = !DILocalVariable(name: "size", arg: 3, scope: !491, file: !1, line: 219, type: !384)
!1577 = !DILocation(line: 219, column: 66, scope: !491)
!1578 = !DILocation(line: 220, column: 33, scope: !491)
!1579 = !DILocation(line: 220, column: 38, scope: !491)
!1580 = !DILocation(line: 220, column: 32, scope: !491)
!1581 = !DILocation(line: 220, column: 48, scope: !491)
!1582 = !DILocation(line: 220, column: 53, scope: !491)
!1583 = !DILocation(line: 220, column: 10, scope: !491)
!1584 = !DILocation(line: 220, column: 3, scope: !491)
!1585 = !DILocalVariable(name: "src", arg: 1, scope: !496, file: !1, line: 224, type: !499)
!1586 = !DILocation(line: 224, column: 44, scope: !496)
!1587 = !DILocalVariable(name: "dst", arg: 2, scope: !496, file: !1, line: 224, type: !383)
!1588 = !DILocation(line: 224, column: 55, scope: !496)
!1589 = !DILocalVariable(name: "size", arg: 3, scope: !496, file: !1, line: 224, type: !384)
!1590 = !DILocation(line: 224, column: 67, scope: !496)
!1591 = !DILocation(line: 225, column: 34, scope: !496)
!1592 = !DILocation(line: 225, column: 39, scope: !496)
!1593 = !DILocation(line: 225, column: 33, scope: !496)
!1594 = !DILocation(line: 225, column: 50, scope: !496)
!1595 = !DILocation(line: 225, column: 55, scope: !496)
!1596 = !DILocation(line: 225, column: 10, scope: !496)
!1597 = !DILocation(line: 225, column: 3, scope: !496)
!1598 = !DILocalVariable(name: "handle", arg: 1, scope: !501, file: !1, line: 229, type: !504)
!1599 = !DILocation(line: 229, column: 27, scope: !501)
!1600 = !DILocalVariable(name: "addr", arg: 2, scope: !501, file: !1, line: 230, type: !608)
!1601 = !DILocation(line: 230, column: 40, scope: !501)
!1602 = !DILocalVariable(name: "flags", arg: 3, scope: !501, file: !1, line: 231, type: !193)
!1603 = !DILocation(line: 231, column: 30, scope: !501)
!1604 = !DILocalVariable(name: "addrlen", scope: !501, file: !1, line: 232, type: !193)
!1605 = !DILocation(line: 232, column: 16, scope: !501)
!1606 = !DILocation(line: 234, column: 7, scope: !1607)
!1607 = distinct !DILexicalBlock(scope: !501, file: !1, line: 234, column: 7)
!1608 = !DILocation(line: 234, column: 15, scope: !1607)
!1609 = !DILocation(line: 234, column: 20, scope: !1607)
!1610 = !DILocation(line: 234, column: 7, scope: !501)
!1611 = !DILocation(line: 235, column: 5, scope: !1607)
!1612 = !DILocation(line: 237, column: 7, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !501, file: !1, line: 237, column: 7)
!1614 = !DILocation(line: 237, column: 13, scope: !1613)
!1615 = !DILocation(line: 237, column: 23, scope: !1613)
!1616 = !DILocation(line: 237, column: 7, scope: !501)
!1617 = !DILocation(line: 238, column: 13, scope: !1613)
!1618 = !DILocation(line: 238, column: 5, scope: !1613)
!1619 = !DILocation(line: 239, column: 12, scope: !1620)
!1620 = distinct !DILexicalBlock(scope: !1613, file: !1, line: 239, column: 12)
!1621 = !DILocation(line: 239, column: 18, scope: !1620)
!1622 = !DILocation(line: 239, column: 28, scope: !1620)
!1623 = !DILocation(line: 239, column: 12, scope: !1613)
!1624 = !DILocation(line: 240, column: 13, scope: !1620)
!1625 = !DILocation(line: 240, column: 5, scope: !1620)
!1626 = !DILocation(line: 242, column: 5, scope: !1620)
!1627 = !DILocation(line: 244, column: 23, scope: !501)
!1628 = !DILocation(line: 244, column: 31, scope: !501)
!1629 = !DILocation(line: 244, column: 37, scope: !501)
!1630 = !DILocation(line: 244, column: 46, scope: !501)
!1631 = !DILocation(line: 244, column: 10, scope: !501)
!1632 = !DILocation(line: 244, column: 3, scope: !501)
!1633 = !DILocation(line: 245, column: 1, scope: !501)
!1634 = !DILocalVariable(name: "handle", arg: 1, scope: !618, file: !1, line: 248, type: !621)
!1635 = !DILocation(line: 248, column: 27, scope: !618)
!1636 = !DILocalVariable(name: "addr", arg: 2, scope: !618, file: !1, line: 249, type: !608)
!1637 = !DILocation(line: 249, column: 40, scope: !618)
!1638 = !DILocalVariable(name: "flags", arg: 3, scope: !618, file: !1, line: 250, type: !193)
!1639 = !DILocation(line: 250, column: 30, scope: !618)
!1640 = !DILocalVariable(name: "addrlen", scope: !618, file: !1, line: 251, type: !193)
!1641 = !DILocation(line: 251, column: 16, scope: !618)
!1642 = !DILocation(line: 253, column: 7, scope: !1643)
!1643 = distinct !DILexicalBlock(scope: !618, file: !1, line: 253, column: 7)
!1644 = !DILocation(line: 253, column: 15, scope: !1643)
!1645 = !DILocation(line: 253, column: 20, scope: !1643)
!1646 = !DILocation(line: 253, column: 7, scope: !618)
!1647 = !DILocation(line: 254, column: 5, scope: !1643)
!1648 = !DILocation(line: 256, column: 7, scope: !1649)
!1649 = distinct !DILexicalBlock(scope: !618, file: !1, line: 256, column: 7)
!1650 = !DILocation(line: 256, column: 13, scope: !1649)
!1651 = !DILocation(line: 256, column: 23, scope: !1649)
!1652 = !DILocation(line: 256, column: 7, scope: !618)
!1653 = !DILocation(line: 257, column: 13, scope: !1649)
!1654 = !DILocation(line: 257, column: 5, scope: !1649)
!1655 = !DILocation(line: 258, column: 12, scope: !1656)
!1656 = distinct !DILexicalBlock(scope: !1649, file: !1, line: 258, column: 12)
!1657 = !DILocation(line: 258, column: 18, scope: !1656)
!1658 = !DILocation(line: 258, column: 28, scope: !1656)
!1659 = !DILocation(line: 258, column: 12, scope: !1649)
!1660 = !DILocation(line: 259, column: 13, scope: !1656)
!1661 = !DILocation(line: 259, column: 5, scope: !1656)
!1662 = !DILocation(line: 261, column: 5, scope: !1656)
!1663 = !DILocation(line: 263, column: 23, scope: !618)
!1664 = !DILocation(line: 263, column: 31, scope: !618)
!1665 = !DILocation(line: 263, column: 37, scope: !618)
!1666 = !DILocation(line: 263, column: 46, scope: !618)
!1667 = !DILocation(line: 263, column: 10, scope: !618)
!1668 = !DILocation(line: 263, column: 3, scope: !618)
!1669 = !DILocation(line: 264, column: 1, scope: !618)
!1670 = !DILocalVariable(name: "req", arg: 1, scope: !648, file: !1, line: 267, type: !552)
!1671 = !DILocation(line: 267, column: 34, scope: !648)
!1672 = !DILocalVariable(name: "handle", arg: 2, scope: !648, file: !1, line: 268, type: !504)
!1673 = !DILocation(line: 268, column: 30, scope: !648)
!1674 = !DILocalVariable(name: "addr", arg: 3, scope: !648, file: !1, line: 269, type: !608)
!1675 = !DILocation(line: 269, column: 43, scope: !648)
!1676 = !DILocalVariable(name: "cb", arg: 4, scope: !648, file: !1, line: 270, type: !561)
!1677 = !DILocation(line: 270, column: 34, scope: !648)
!1678 = !DILocalVariable(name: "addrlen", scope: !648, file: !1, line: 271, type: !193)
!1679 = !DILocation(line: 271, column: 16, scope: !648)
!1680 = !DILocation(line: 273, column: 7, scope: !1681)
!1681 = distinct !DILexicalBlock(scope: !648, file: !1, line: 273, column: 7)
!1682 = !DILocation(line: 273, column: 15, scope: !1681)
!1683 = !DILocation(line: 273, column: 20, scope: !1681)
!1684 = !DILocation(line: 273, column: 7, scope: !648)
!1685 = !DILocation(line: 274, column: 5, scope: !1681)
!1686 = !DILocation(line: 276, column: 7, scope: !1687)
!1687 = distinct !DILexicalBlock(scope: !648, file: !1, line: 276, column: 7)
!1688 = !DILocation(line: 276, column: 13, scope: !1687)
!1689 = !DILocation(line: 276, column: 23, scope: !1687)
!1690 = !DILocation(line: 276, column: 7, scope: !648)
!1691 = !DILocation(line: 277, column: 13, scope: !1687)
!1692 = !DILocation(line: 277, column: 5, scope: !1687)
!1693 = !DILocation(line: 278, column: 12, scope: !1694)
!1694 = distinct !DILexicalBlock(scope: !1687, file: !1, line: 278, column: 12)
!1695 = !DILocation(line: 278, column: 18, scope: !1694)
!1696 = !DILocation(line: 278, column: 28, scope: !1694)
!1697 = !DILocation(line: 278, column: 12, scope: !1687)
!1698 = !DILocation(line: 279, column: 13, scope: !1694)
!1699 = !DILocation(line: 279, column: 5, scope: !1694)
!1700 = !DILocation(line: 281, column: 5, scope: !1694)
!1701 = !DILocation(line: 283, column: 26, scope: !648)
!1702 = !DILocation(line: 283, column: 31, scope: !648)
!1703 = !DILocation(line: 283, column: 39, scope: !648)
!1704 = !DILocation(line: 283, column: 45, scope: !648)
!1705 = !DILocation(line: 283, column: 54, scope: !648)
!1706 = !DILocation(line: 283, column: 10, scope: !648)
!1707 = !DILocation(line: 283, column: 3, scope: !648)
!1708 = !DILocation(line: 284, column: 1, scope: !648)
!1709 = !DILocalVariable(name: "req", arg: 1, scope: !651, file: !1, line: 287, type: !654)
!1710 = !DILocation(line: 287, column: 32, scope: !651)
!1711 = !DILocalVariable(name: "handle", arg: 2, scope: !651, file: !1, line: 288, type: !621)
!1712 = !DILocation(line: 288, column: 27, scope: !651)
!1713 = !DILocalVariable(name: "bufs", arg: 3, scope: !651, file: !1, line: 289, type: !597)
!1714 = !DILocation(line: 289, column: 32, scope: !651)
!1715 = !DILocalVariable(name: "nbufs", arg: 4, scope: !651, file: !1, line: 290, type: !193)
!1716 = !DILocation(line: 290, column: 30, scope: !651)
!1717 = !DILocalVariable(name: "addr", arg: 5, scope: !651, file: !1, line: 291, type: !608)
!1718 = !DILocation(line: 291, column: 40, scope: !651)
!1719 = !DILocalVariable(name: "send_cb", arg: 6, scope: !651, file: !1, line: 292, type: !664)
!1720 = !DILocation(line: 292, column: 32, scope: !651)
!1721 = !DILocalVariable(name: "addrlen", scope: !651, file: !1, line: 293, type: !193)
!1722 = !DILocation(line: 293, column: 16, scope: !651)
!1723 = !DILocation(line: 295, column: 7, scope: !1724)
!1724 = distinct !DILexicalBlock(scope: !651, file: !1, line: 295, column: 7)
!1725 = !DILocation(line: 295, column: 15, scope: !1724)
!1726 = !DILocation(line: 295, column: 20, scope: !1724)
!1727 = !DILocation(line: 295, column: 7, scope: !651)
!1728 = !DILocation(line: 296, column: 5, scope: !1724)
!1729 = !DILocation(line: 298, column: 7, scope: !1730)
!1730 = distinct !DILexicalBlock(scope: !651, file: !1, line: 298, column: 7)
!1731 = !DILocation(line: 298, column: 13, scope: !1730)
!1732 = !DILocation(line: 298, column: 23, scope: !1730)
!1733 = !DILocation(line: 298, column: 7, scope: !651)
!1734 = !DILocation(line: 299, column: 13, scope: !1730)
!1735 = !DILocation(line: 299, column: 5, scope: !1730)
!1736 = !DILocation(line: 300, column: 12, scope: !1737)
!1737 = distinct !DILexicalBlock(scope: !1730, file: !1, line: 300, column: 12)
!1738 = !DILocation(line: 300, column: 18, scope: !1737)
!1739 = !DILocation(line: 300, column: 28, scope: !1737)
!1740 = !DILocation(line: 300, column: 12, scope: !1730)
!1741 = !DILocation(line: 301, column: 13, scope: !1737)
!1742 = !DILocation(line: 301, column: 5, scope: !1737)
!1743 = !DILocation(line: 303, column: 5, scope: !1737)
!1744 = !DILocation(line: 305, column: 23, scope: !651)
!1745 = !DILocation(line: 305, column: 28, scope: !651)
!1746 = !DILocation(line: 305, column: 36, scope: !651)
!1747 = !DILocation(line: 305, column: 42, scope: !651)
!1748 = !DILocation(line: 305, column: 49, scope: !651)
!1749 = !DILocation(line: 305, column: 55, scope: !651)
!1750 = !DILocation(line: 305, column: 64, scope: !651)
!1751 = !DILocation(line: 305, column: 10, scope: !651)
!1752 = !DILocation(line: 305, column: 3, scope: !651)
!1753 = !DILocation(line: 306, column: 1, scope: !651)
!1754 = !DILocalVariable(name: "handle", arg: 1, scope: !684, file: !1, line: 309, type: !621)
!1755 = !DILocation(line: 309, column: 31, scope: !684)
!1756 = !DILocalVariable(name: "bufs", arg: 2, scope: !684, file: !1, line: 310, type: !597)
!1757 = !DILocation(line: 310, column: 36, scope: !684)
!1758 = !DILocalVariable(name: "nbufs", arg: 3, scope: !684, file: !1, line: 311, type: !193)
!1759 = !DILocation(line: 311, column: 34, scope: !684)
!1760 = !DILocalVariable(name: "addr", arg: 4, scope: !684, file: !1, line: 312, type: !608)
!1761 = !DILocation(line: 312, column: 44, scope: !684)
!1762 = !DILocalVariable(name: "addrlen", scope: !684, file: !1, line: 313, type: !193)
!1763 = !DILocation(line: 313, column: 16, scope: !684)
!1764 = !DILocation(line: 315, column: 7, scope: !1765)
!1765 = distinct !DILexicalBlock(scope: !684, file: !1, line: 315, column: 7)
!1766 = !DILocation(line: 315, column: 15, scope: !1765)
!1767 = !DILocation(line: 315, column: 20, scope: !1765)
!1768 = !DILocation(line: 315, column: 7, scope: !684)
!1769 = !DILocation(line: 316, column: 5, scope: !1765)
!1770 = !DILocation(line: 318, column: 7, scope: !1771)
!1771 = distinct !DILexicalBlock(scope: !684, file: !1, line: 318, column: 7)
!1772 = !DILocation(line: 318, column: 13, scope: !1771)
!1773 = !DILocation(line: 318, column: 23, scope: !1771)
!1774 = !DILocation(line: 318, column: 7, scope: !684)
!1775 = !DILocation(line: 319, column: 13, scope: !1771)
!1776 = !DILocation(line: 319, column: 5, scope: !1771)
!1777 = !DILocation(line: 320, column: 12, scope: !1778)
!1778 = distinct !DILexicalBlock(scope: !1771, file: !1, line: 320, column: 12)
!1779 = !DILocation(line: 320, column: 18, scope: !1778)
!1780 = !DILocation(line: 320, column: 28, scope: !1778)
!1781 = !DILocation(line: 320, column: 12, scope: !1771)
!1782 = !DILocation(line: 321, column: 13, scope: !1778)
!1783 = !DILocation(line: 321, column: 5, scope: !1778)
!1784 = !DILocation(line: 323, column: 5, scope: !1778)
!1785 = !DILocation(line: 325, column: 27, scope: !684)
!1786 = !DILocation(line: 325, column: 35, scope: !684)
!1787 = !DILocation(line: 325, column: 41, scope: !684)
!1788 = !DILocation(line: 325, column: 48, scope: !684)
!1789 = !DILocation(line: 325, column: 54, scope: !684)
!1790 = !DILocation(line: 325, column: 10, scope: !684)
!1791 = !DILocation(line: 325, column: 3, scope: !684)
!1792 = !DILocation(line: 326, column: 1, scope: !684)
!1793 = !DILocalVariable(name: "handle", arg: 1, scope: !687, file: !1, line: 329, type: !621)
!1794 = !DILocation(line: 329, column: 33, scope: !687)
!1795 = !DILocalVariable(name: "alloc_cb", arg: 2, scope: !687, file: !1, line: 330, type: !522)
!1796 = !DILocation(line: 330, column: 35, scope: !687)
!1797 = !DILocalVariable(name: "recv_cb", arg: 3, scope: !687, file: !1, line: 331, type: !641)
!1798 = !DILocation(line: 331, column: 38, scope: !687)
!1799 = !DILocation(line: 332, column: 7, scope: !1800)
!1800 = distinct !DILexicalBlock(scope: !687, file: !1, line: 332, column: 7)
!1801 = !DILocation(line: 332, column: 15, scope: !1800)
!1802 = !DILocation(line: 332, column: 20, scope: !1800)
!1803 = !DILocation(line: 332, column: 30, scope: !1800)
!1804 = !DILocation(line: 332, column: 33, scope: !1805)
!1805 = !DILexicalBlockFile(scope: !1800, file: !1, discriminator: 1)
!1806 = !DILocation(line: 332, column: 42, scope: !1805)
!1807 = !DILocation(line: 332, column: 50, scope: !1805)
!1808 = !DILocation(line: 332, column: 53, scope: !1809)
!1809 = !DILexicalBlockFile(scope: !1800, file: !1, discriminator: 2)
!1810 = !DILocation(line: 332, column: 61, scope: !1809)
!1811 = !DILocation(line: 332, column: 7, scope: !1809)
!1812 = !DILocation(line: 333, column: 5, scope: !1800)
!1813 = !DILocation(line: 335, column: 31, scope: !1800)
!1814 = !DILocation(line: 335, column: 39, scope: !1800)
!1815 = !DILocation(line: 335, column: 49, scope: !1800)
!1816 = !DILocation(line: 335, column: 12, scope: !1800)
!1817 = !DILocation(line: 335, column: 5, scope: !1800)
!1818 = !DILocation(line: 336, column: 1, scope: !687)
!1819 = !DILocalVariable(name: "handle", arg: 1, scope: !690, file: !1, line: 339, type: !621)
!1820 = !DILocation(line: 339, column: 32, scope: !690)
!1821 = !DILocation(line: 340, column: 7, scope: !1822)
!1822 = distinct !DILexicalBlock(scope: !690, file: !1, line: 340, column: 7)
!1823 = !DILocation(line: 340, column: 15, scope: !1822)
!1824 = !DILocation(line: 340, column: 20, scope: !1822)
!1825 = !DILocation(line: 340, column: 7, scope: !690)
!1826 = !DILocation(line: 341, column: 5, scope: !1822)
!1827 = !DILocation(line: 343, column: 30, scope: !1822)
!1828 = !DILocation(line: 343, column: 12, scope: !1822)
!1829 = !DILocation(line: 343, column: 5, scope: !1822)
!1830 = !DILocation(line: 344, column: 1, scope: !690)
!1831 = !DILocalVariable(name: "loop", arg: 1, scope: !693, file: !1, line: 347, type: !187)
!1832 = !DILocation(line: 347, column: 25, scope: !693)
!1833 = !DILocalVariable(name: "walk_cb", arg: 2, scope: !693, file: !1, line: 347, type: !696)
!1834 = !DILocation(line: 347, column: 42, scope: !693)
!1835 = !DILocalVariable(name: "arg", arg: 3, scope: !693, file: !1, line: 347, type: !171)
!1836 = !DILocation(line: 347, column: 57, scope: !693)
!1837 = !DILocalVariable(name: "queue", scope: !693, file: !1, line: 348, type: !174)
!1838 = !DILocation(line: 348, column: 9, scope: !693)
!1839 = !DILocalVariable(name: "q", scope: !693, file: !1, line: 349, type: !180)
!1840 = !DILocation(line: 349, column: 10, scope: !693)
!1841 = !DILocalVariable(name: "h", scope: !693, file: !1, line: 350, type: !181)
!1842 = !DILocation(line: 350, column: 16, scope: !693)
!1843 = !DILocation(line: 352, column: 3, scope: !693)
!1844 = !DILocation(line: 352, column: 3, scope: !1845)
!1845 = !DILexicalBlockFile(scope: !1846, file: !1, discriminator: 1)
!1846 = distinct !DILexicalBlock(scope: !1847, file: !1, line: 352, column: 3)
!1847 = distinct !DILexicalBlock(scope: !693, file: !1, line: 352, column: 3)
!1848 = !DILocation(line: 352, column: 3, scope: !1849)
!1849 = !DILexicalBlockFile(scope: !1846, file: !1, discriminator: 2)
!1850 = !DILocation(line: 352, column: 3, scope: !1851)
!1851 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 3)
!1852 = distinct !DILexicalBlock(scope: !1846, file: !1, line: 352, column: 3)
!1853 = !DILocation(line: 352, column: 3, scope: !1854)
!1854 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 4)
!1855 = !DILocalVariable(name: "q", scope: !1856, file: !1, line: 352, type: !180)
!1856 = distinct !DILexicalBlock(scope: !1846, file: !1, line: 352, column: 3)
!1857 = !DILocation(line: 352, column: 3, scope: !1856)
!1858 = !DILocation(line: 352, column: 3, scope: !1859)
!1859 = !DILexicalBlockFile(scope: !1856, file: !1, discriminator: 5)
!1860 = !DILocation(line: 352, column: 3, scope: !1861)
!1861 = !DILexicalBlockFile(scope: !1862, file: !1, discriminator: 6)
!1862 = distinct !DILexicalBlock(scope: !1856, file: !1, line: 352, column: 3)
!1863 = !DILocation(line: 352, column: 3, scope: !1864)
!1864 = !DILexicalBlockFile(scope: !1847, file: !1, discriminator: 7)
!1865 = !DILocation(line: 353, column: 3, scope: !693)
!1866 = !DILocation(line: 353, column: 11, scope: !1867)
!1867 = !DILexicalBlockFile(scope: !693, file: !1, discriminator: 1)
!1868 = !DILocation(line: 353, column: 10, scope: !1867)
!1869 = !DILocation(line: 353, column: 3, scope: !1867)
!1870 = !DILocation(line: 354, column: 9, scope: !1871)
!1871 = distinct !DILexicalBlock(scope: !693, file: !1, line: 353, column: 32)
!1872 = !DILocation(line: 354, column: 7, scope: !1871)
!1873 = !DILocation(line: 355, column: 9, scope: !1871)
!1874 = !DILocation(line: 355, column: 7, scope: !1871)
!1875 = !DILocation(line: 357, column: 5, scope: !1871)
!1876 = !DILocation(line: 357, column: 5, scope: !1877)
!1877 = !DILexicalBlockFile(scope: !1878, file: !1, discriminator: 1)
!1878 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 357, column: 5)
!1879 = !DILocation(line: 358, column: 5, scope: !1871)
!1880 = !DILocation(line: 358, column: 5, scope: !1881)
!1881 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 1)
!1882 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 358, column: 5)
!1883 = !DILocation(line: 360, column: 9, scope: !1884)
!1884 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 360, column: 9)
!1885 = !DILocation(line: 360, column: 12, scope: !1884)
!1886 = !DILocation(line: 360, column: 18, scope: !1884)
!1887 = !DILocation(line: 360, column: 9, scope: !1871)
!1888 = !DILocation(line: 360, column: 41, scope: !1889)
!1889 = !DILexicalBlockFile(scope: !1884, file: !1, discriminator: 1)
!1890 = !DILocation(line: 361, column: 5, scope: !1871)
!1891 = !DILocation(line: 361, column: 13, scope: !1871)
!1892 = !DILocation(line: 361, column: 16, scope: !1871)
!1893 = !DILocation(line: 353, column: 3, scope: !1894)
!1894 = !DILexicalBlockFile(scope: !693, file: !1, discriminator: 2)
!1895 = !DILocation(line: 363, column: 1, scope: !693)
!1896 = !DILocalVariable(name: "loop", arg: 1, scope: !700, file: !1, line: 398, type: !187)
!1897 = !DILocation(line: 398, column: 38, scope: !700)
!1898 = !DILocalVariable(name: "stream", arg: 2, scope: !700, file: !1, line: 398, type: !703)
!1899 = !DILocation(line: 398, column: 50, scope: !700)
!1900 = !DILocation(line: 399, column: 21, scope: !700)
!1901 = !DILocation(line: 399, column: 30, scope: !700)
!1902 = !DILocation(line: 399, column: 3, scope: !700)
!1903 = !DILocation(line: 400, column: 1, scope: !700)
!1904 = !DILocalVariable(name: "loop", arg: 1, scope: !914, file: !1, line: 366, type: !187)
!1905 = !DILocation(line: 366, column: 42, scope: !914)
!1906 = !DILocalVariable(name: "only_active", arg: 2, scope: !914, file: !1, line: 366, type: !200)
!1907 = !DILocation(line: 366, column: 52, scope: !914)
!1908 = !DILocalVariable(name: "stream", arg: 3, scope: !914, file: !1, line: 366, type: !703)
!1909 = !DILocation(line: 366, column: 71, scope: !914)
!1910 = !DILocalVariable(name: "type", scope: !914, file: !1, line: 367, type: !390)
!1911 = !DILocation(line: 367, column: 15, scope: !914)
!1912 = !DILocalVariable(name: "q", scope: !914, file: !1, line: 368, type: !180)
!1913 = !DILocation(line: 368, column: 10, scope: !914)
!1914 = !DILocalVariable(name: "h", scope: !914, file: !1, line: 369, type: !181)
!1915 = !DILocation(line: 369, column: 16, scope: !914)
!1916 = !DILocation(line: 371, column: 7, scope: !1917)
!1917 = distinct !DILexicalBlock(scope: !914, file: !1, line: 371, column: 7)
!1918 = !DILocation(line: 371, column: 12, scope: !1917)
!1919 = !DILocation(line: 371, column: 7, scope: !914)
!1920 = !DILocation(line: 372, column: 12, scope: !1917)
!1921 = !DILocation(line: 372, column: 10, scope: !1917)
!1922 = !DILocation(line: 372, column: 5, scope: !1917)
!1923 = !DILocation(line: 374, column: 3, scope: !1924)
!1924 = distinct !DILexicalBlock(scope: !914, file: !1, line: 374, column: 3)
!1925 = !DILocation(line: 374, column: 3, scope: !1926)
!1926 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 1)
!1927 = distinct !DILexicalBlock(scope: !1924, file: !1, line: 374, column: 3)
!1928 = !DILocation(line: 375, column: 9, scope: !1929)
!1929 = distinct !DILexicalBlock(scope: !1927, file: !1, line: 374, column: 41)
!1930 = !DILocation(line: 375, column: 7, scope: !1929)
!1931 = !DILocation(line: 377, column: 9, scope: !1932)
!1932 = distinct !DILexicalBlock(scope: !1929, file: !1, line: 377, column: 9)
!1933 = !DILocation(line: 377, column: 21, scope: !1932)
!1934 = !DILocation(line: 377, column: 25, scope: !1935)
!1935 = !DILexicalBlockFile(scope: !1932, file: !1, discriminator: 1)
!1936 = !DILocation(line: 377, column: 9, scope: !1935)
!1937 = !DILocation(line: 378, column: 7, scope: !1932)
!1938 = !DILocation(line: 380, column: 13, scope: !1929)
!1939 = !DILocation(line: 380, column: 16, scope: !1929)
!1940 = !DILocation(line: 380, column: 5, scope: !1929)
!1941 = !DILocation(line: 382, column: 7, scope: !1942)
!1942 = distinct !DILexicalBlock(scope: !1929, file: !1, line: 380, column: 22)
!1943 = !DILocation(line: 382, column: 7, scope: !1944)
!1944 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 1)
!1945 = !DILocation(line: 382, column: 7, scope: !1946)
!1946 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 2)
!1947 = !DILocation(line: 382, column: 7, scope: !1948)
!1948 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 3)
!1949 = !DILocation(line: 382, column: 7, scope: !1950)
!1950 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 4)
!1951 = !DILocation(line: 382, column: 7, scope: !1952)
!1952 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 5)
!1953 = !DILocation(line: 382, column: 7, scope: !1954)
!1954 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 6)
!1955 = !DILocation(line: 382, column: 7, scope: !1956)
!1956 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 7)
!1957 = !DILocation(line: 382, column: 7, scope: !1958)
!1958 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 8)
!1959 = !DILocation(line: 382, column: 7, scope: !1960)
!1960 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 9)
!1961 = !DILocation(line: 382, column: 7, scope: !1962)
!1962 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 10)
!1963 = !DILocation(line: 382, column: 7, scope: !1964)
!1964 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 11)
!1965 = !DILocation(line: 382, column: 7, scope: !1966)
!1966 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 12)
!1967 = !DILocation(line: 382, column: 7, scope: !1968)
!1968 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 13)
!1969 = !DILocation(line: 382, column: 7, scope: !1970)
!1970 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 14)
!1971 = !DILocation(line: 382, column: 7, scope: !1972)
!1972 = !DILexicalBlockFile(scope: !1942, file: !1, discriminator: 15)
!1973 = !DILocation(line: 384, column: 21, scope: !1942)
!1974 = !DILocation(line: 385, column: 5, scope: !1942)
!1975 = !DILocation(line: 387, column: 13, scope: !1929)
!1976 = !DILocation(line: 389, column: 20, scope: !1929)
!1977 = !DILocation(line: 389, column: 23, scope: !1929)
!1978 = !DILocation(line: 389, column: 29, scope: !1929)
!1979 = !DILocation(line: 389, column: 18, scope: !1929)
!1980 = !DILocation(line: 389, column: 13, scope: !1929)
!1981 = !DILocation(line: 390, column: 20, scope: !1929)
!1982 = !DILocation(line: 390, column: 23, scope: !1929)
!1983 = !DILocation(line: 390, column: 29, scope: !1929)
!1984 = !DILocation(line: 390, column: 18, scope: !1929)
!1985 = !DILocation(line: 390, column: 13, scope: !1929)
!1986 = !DILocation(line: 391, column: 20, scope: !1929)
!1987 = !DILocation(line: 391, column: 23, scope: !1929)
!1988 = !DILocation(line: 391, column: 29, scope: !1929)
!1989 = !DILocation(line: 391, column: 18, scope: !1929)
!1990 = !DILocation(line: 391, column: 13, scope: !1929)
!1991 = !DILocation(line: 392, column: 13, scope: !1929)
!1992 = !DILocation(line: 393, column: 20, scope: !1929)
!1993 = !DILocation(line: 393, column: 13, scope: !1929)
!1994 = !DILocation(line: 387, column: 5, scope: !1929)
!1995 = !DILocation(line: 394, column: 3, scope: !1929)
!1996 = !DILocation(line: 374, column: 3, scope: !1997)
!1997 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 2)
!1998 = !DILocation(line: 395, column: 1, scope: !914)
!1999 = !DILocalVariable(name: "loop", arg: 1, scope: !755, file: !1, line: 403, type: !187)
!2000 = !DILocation(line: 403, column: 41, scope: !755)
!2001 = !DILocalVariable(name: "stream", arg: 2, scope: !755, file: !1, line: 403, type: !703)
!2002 = !DILocation(line: 403, column: 53, scope: !755)
!2003 = !DILocation(line: 404, column: 21, scope: !755)
!2004 = !DILocation(line: 404, column: 30, scope: !755)
!2005 = !DILocation(line: 404, column: 3, scope: !755)
!2006 = !DILocation(line: 405, column: 1, scope: !755)
!2007 = !DILocalVariable(name: "handle", arg: 1, scope: !756, file: !1, line: 408, type: !181)
!2008 = !DILocation(line: 408, column: 26, scope: !756)
!2009 = !DILocation(line: 409, column: 3, scope: !756)
!2010 = !DILocation(line: 409, column: 3, scope: !2011)
!2011 = !DILexicalBlockFile(scope: !2012, file: !1, discriminator: 1)
!2012 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 409, column: 3)
!2013 = distinct !DILexicalBlock(scope: !756, file: !1, line: 409, column: 3)
!2014 = !DILocation(line: 409, column: 3, scope: !2015)
!2015 = !DILexicalBlockFile(scope: !2012, file: !1, discriminator: 2)
!2016 = !DILocation(line: 409, column: 3, scope: !2017)
!2017 = !DILexicalBlockFile(scope: !2013, file: !1, discriminator: 3)
!2018 = !DILocation(line: 409, column: 3, scope: !2019)
!2019 = !DILexicalBlockFile(scope: !2020, file: !1, discriminator: 4)
!2020 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 409, column: 3)
!2021 = !DILocation(line: 409, column: 3, scope: !2022)
!2022 = !DILexicalBlockFile(scope: !2023, file: !1, discriminator: 5)
!2023 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 409, column: 3)
!2024 = !DILocation(line: 409, column: 3, scope: !2025)
!2025 = !DILexicalBlockFile(scope: !2023, file: !1, discriminator: 6)
!2026 = !DILocation(line: 409, column: 3, scope: !2027)
!2027 = !DILexicalBlockFile(scope: !2028, file: !1, discriminator: 7)
!2028 = distinct !DILexicalBlock(scope: !2023, file: !1, line: 409, column: 3)
!2029 = !DILocation(line: 409, column: 3, scope: !2030)
!2030 = !DILexicalBlockFile(scope: !2028, file: !1, discriminator: 8)
!2031 = !DILocation(line: 409, column: 3, scope: !2032)
!2032 = !DILexicalBlockFile(scope: !2013, file: !1, discriminator: 9)
!2033 = !DILocation(line: 410, column: 1, scope: !756)
!2034 = !DILocalVariable(name: "handle", arg: 1, scope: !757, file: !1, line: 413, type: !181)
!2035 = !DILocation(line: 413, column: 28, scope: !757)
!2036 = !DILocation(line: 414, column: 3, scope: !757)
!2037 = !DILocation(line: 414, column: 3, scope: !2038)
!2038 = !DILexicalBlockFile(scope: !2039, file: !1, discriminator: 1)
!2039 = distinct !DILexicalBlock(scope: !2040, file: !1, line: 414, column: 3)
!2040 = distinct !DILexicalBlock(scope: !757, file: !1, line: 414, column: 3)
!2041 = !DILocation(line: 414, column: 3, scope: !2042)
!2042 = !DILexicalBlockFile(scope: !2039, file: !1, discriminator: 2)
!2043 = !DILocation(line: 414, column: 3, scope: !2044)
!2044 = !DILexicalBlockFile(scope: !2040, file: !1, discriminator: 3)
!2045 = !DILocation(line: 414, column: 3, scope: !2046)
!2046 = !DILexicalBlockFile(scope: !2047, file: !1, discriminator: 4)
!2047 = distinct !DILexicalBlock(scope: !2040, file: !1, line: 414, column: 3)
!2048 = !DILocation(line: 414, column: 3, scope: !2049)
!2049 = !DILexicalBlockFile(scope: !2050, file: !1, discriminator: 5)
!2050 = distinct !DILexicalBlock(scope: !2040, file: !1, line: 414, column: 3)
!2051 = !DILocation(line: 414, column: 3, scope: !2052)
!2052 = !DILexicalBlockFile(scope: !2050, file: !1, discriminator: 6)
!2053 = !DILocation(line: 414, column: 3, scope: !2054)
!2054 = !DILexicalBlockFile(scope: !2055, file: !1, discriminator: 7)
!2055 = distinct !DILexicalBlock(scope: !2050, file: !1, line: 414, column: 3)
!2056 = !DILocation(line: 414, column: 3, scope: !2057)
!2057 = !DILexicalBlockFile(scope: !2055, file: !1, discriminator: 8)
!2058 = !DILocation(line: 414, column: 3, scope: !2059)
!2059 = !DILexicalBlockFile(scope: !2040, file: !1, discriminator: 9)
!2060 = !DILocation(line: 415, column: 1, scope: !757)
!2061 = !DILocalVariable(name: "handle", arg: 1, scope: !758, file: !1, line: 418, type: !761)
!2062 = !DILocation(line: 418, column: 35, scope: !758)
!2063 = !DILocation(line: 419, column: 10, scope: !758)
!2064 = !DILocation(line: 419, column: 3, scope: !758)
!2065 = !DILocalVariable(name: "loop", arg: 1, scope: !763, file: !1, line: 423, type: !187)
!2066 = !DILocation(line: 423, column: 25, scope: !763)
!2067 = !DILocation(line: 424, column: 3, scope: !763)
!2068 = !DILocation(line: 424, column: 9, scope: !763)
!2069 = !DILocation(line: 424, column: 19, scope: !763)
!2070 = !DILocation(line: 425, column: 1, scope: !763)
!2071 = !DILocalVariable(name: "loop", arg: 1, scope: !766, file: !1, line: 428, type: !769)
!2072 = !DILocation(line: 428, column: 34, scope: !766)
!2073 = !DILocation(line: 429, column: 10, scope: !766)
!2074 = !DILocation(line: 429, column: 16, scope: !766)
!2075 = !DILocation(line: 429, column: 3, scope: !766)
!2076 = !DILocalVariable(name: "bufs", arg: 1, scope: !771, file: !1, line: 434, type: !597)
!2077 = !DILocation(line: 434, column: 38, scope: !771)
!2078 = !DILocalVariable(name: "nbufs", arg: 2, scope: !771, file: !1, line: 434, type: !193)
!2079 = !DILocation(line: 434, column: 59, scope: !771)
!2080 = !DILocalVariable(name: "i", scope: !771, file: !1, line: 435, type: !193)
!2081 = !DILocation(line: 435, column: 16, scope: !771)
!2082 = !DILocalVariable(name: "bytes", scope: !771, file: !1, line: 436, type: !384)
!2083 = !DILocation(line: 436, column: 10, scope: !771)
!2084 = !DILocation(line: 438, column: 9, scope: !771)
!2085 = !DILocation(line: 439, column: 10, scope: !2086)
!2086 = distinct !DILexicalBlock(scope: !771, file: !1, line: 439, column: 3)
!2087 = !DILocation(line: 439, column: 8, scope: !2086)
!2088 = !DILocation(line: 439, column: 15, scope: !2089)
!2089 = !DILexicalBlockFile(scope: !2090, file: !1, discriminator: 1)
!2090 = distinct !DILexicalBlock(scope: !2086, file: !1, line: 439, column: 3)
!2091 = !DILocation(line: 439, column: 19, scope: !2089)
!2092 = !DILocation(line: 439, column: 17, scope: !2089)
!2093 = !DILocation(line: 439, column: 3, scope: !2089)
!2094 = !DILocation(line: 440, column: 28, scope: !2090)
!2095 = !DILocation(line: 440, column: 23, scope: !2090)
!2096 = !DILocation(line: 440, column: 31, scope: !2090)
!2097 = !DILocation(line: 440, column: 11, scope: !2090)
!2098 = !DILocation(line: 440, column: 5, scope: !2090)
!2099 = !DILocation(line: 439, column: 27, scope: !2100)
!2100 = !DILexicalBlockFile(scope: !2090, file: !1, discriminator: 2)
!2101 = !DILocation(line: 439, column: 3, scope: !2100)
!2102 = !DILocation(line: 442, column: 10, scope: !771)
!2103 = !DILocation(line: 442, column: 3, scope: !771)
!2104 = !DILocalVariable(name: "handle", arg: 1, scope: !774, file: !1, line: 445, type: !181)
!2105 = !DILocation(line: 445, column: 38, scope: !774)
!2106 = !DILocalVariable(name: "value", arg: 2, scope: !774, file: !1, line: 445, type: !777)
!2107 = !DILocation(line: 445, column: 51, scope: !774)
!2108 = !DILocation(line: 446, column: 29, scope: !774)
!2109 = !DILocation(line: 446, column: 48, scope: !774)
!2110 = !DILocation(line: 446, column: 10, scope: !774)
!2111 = !DILocation(line: 446, column: 3, scope: !774)
!2112 = !DILocalVariable(name: "handle", arg: 1, scope: !778, file: !1, line: 449, type: !181)
!2113 = !DILocation(line: 449, column: 38, scope: !778)
!2114 = !DILocalVariable(name: "value", arg: 2, scope: !778, file: !1, line: 449, type: !777)
!2115 = !DILocation(line: 449, column: 51, scope: !778)
!2116 = !DILocation(line: 450, column: 29, scope: !778)
!2117 = !DILocation(line: 450, column: 48, scope: !778)
!2118 = !DILocation(line: 450, column: 10, scope: !778)
!2119 = !DILocation(line: 450, column: 3, scope: !778)
!2120 = !DILocalVariable(name: "handle", arg: 1, scope: !779, file: !1, line: 453, type: !782)
!2121 = !DILocation(line: 453, column: 40, scope: !779)
!2122 = !DILocalVariable(name: "buffer", arg: 2, scope: !779, file: !1, line: 453, type: !383)
!2123 = !DILocation(line: 453, column: 54, scope: !779)
!2124 = !DILocalVariable(name: "size", arg: 3, scope: !779, file: !1, line: 453, type: !806)
!2125 = !DILocation(line: 453, column: 70, scope: !779)
!2126 = !DILocalVariable(name: "required_len", scope: !779, file: !1, line: 454, type: !384)
!2127 = !DILocation(line: 454, column: 10, scope: !779)
!2128 = !DILocation(line: 456, column: 8, scope: !2129)
!2129 = distinct !DILexicalBlock(scope: !779, file: !1, line: 456, column: 7)
!2130 = !DILocation(line: 456, column: 7, scope: !779)
!2131 = !DILocation(line: 457, column: 6, scope: !2132)
!2132 = distinct !DILexicalBlock(scope: !2129, file: !1, line: 456, column: 31)
!2133 = !DILocation(line: 457, column: 11, scope: !2132)
!2134 = !DILocation(line: 458, column: 5, scope: !2132)
!2135 = !DILocation(line: 461, column: 25, scope: !779)
!2136 = !DILocation(line: 461, column: 33, scope: !779)
!2137 = !DILocation(line: 461, column: 18, scope: !779)
!2138 = !DILocation(line: 461, column: 16, scope: !779)
!2139 = !DILocation(line: 462, column: 7, scope: !2140)
!2140 = distinct !DILexicalBlock(scope: !779, file: !1, line: 462, column: 7)
!2141 = !DILocation(line: 462, column: 24, scope: !2140)
!2142 = !DILocation(line: 462, column: 23, scope: !2140)
!2143 = !DILocation(line: 462, column: 20, scope: !2140)
!2144 = !DILocation(line: 462, column: 7, scope: !779)
!2145 = !DILocation(line: 463, column: 13, scope: !2146)
!2146 = distinct !DILexicalBlock(scope: !2140, file: !1, line: 462, column: 30)
!2147 = !DILocation(line: 463, column: 26, scope: !2146)
!2148 = !DILocation(line: 463, column: 6, scope: !2146)
!2149 = !DILocation(line: 463, column: 11, scope: !2146)
!2150 = !DILocation(line: 464, column: 5, scope: !2146)
!2151 = !DILocation(line: 467, column: 10, scope: !779)
!2152 = !DILocation(line: 467, column: 18, scope: !779)
!2153 = !DILocation(line: 467, column: 26, scope: !779)
!2154 = !DILocation(line: 467, column: 32, scope: !779)
!2155 = !DILocation(line: 467, column: 3, scope: !779)
!2156 = !DILocation(line: 468, column: 11, scope: !779)
!2157 = !DILocation(line: 468, column: 4, scope: !779)
!2158 = !DILocation(line: 468, column: 9, scope: !779)
!2159 = !DILocation(line: 469, column: 10, scope: !779)
!2160 = !DILocation(line: 469, column: 3, scope: !779)
!2161 = !DILocation(line: 469, column: 24, scope: !779)
!2162 = !DILocation(line: 471, column: 3, scope: !779)
!2163 = !DILocation(line: 472, column: 1, scope: !779)
!2164 = !DILocalVariable(name: "req", arg: 1, scope: !807, file: !1, line: 496, type: !810)
!2165 = !DILocation(line: 496, column: 38, scope: !807)
!2166 = !DILocalVariable(name: "dents", scope: !807, file: !1, line: 497, type: !2167)
!2167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2168, size: 64, align: 64)
!2168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2169, size: 64, align: 64)
!2169 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__dirent_t", file: !207, line: 141, baseType: !2170)
!2170 = !DICompositeType(tag: DW_TAG_structure_type, name: "dirent", file: !2171, line: 22, size: 2240, align: 64, elements: !2172)
!2171 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/dirent.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2172 = !{!2173, !2175, !2176, !2177, !2178}
!2173 = !DIDerivedType(tag: DW_TAG_member, name: "d_ino", scope: !2170, file: !2171, line: 28, baseType: !2174, size: 64, align: 64)
!2174 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino64_t", file: !596, line: 128, baseType: !198)
!2175 = !DIDerivedType(tag: DW_TAG_member, name: "d_off", scope: !2170, file: !2171, line: 29, baseType: !744, size: 64, align: 64, offset: 64)
!2176 = !DIDerivedType(tag: DW_TAG_member, name: "d_reclen", scope: !2170, file: !2171, line: 31, baseType: !451, size: 16, align: 16, offset: 128)
!2177 = !DIDerivedType(tag: DW_TAG_member, name: "d_type", scope: !2170, file: !2171, line: 32, baseType: !463, size: 8, align: 8, offset: 144)
!2178 = !DIDerivedType(tag: DW_TAG_member, name: "d_name", scope: !2170, file: !2171, line: 33, baseType: !2179, size: 2048, align: 8, offset: 152)
!2179 = !DICompositeType(tag: DW_TAG_array_type, baseType: !251, size: 2048, align: 8, elements: !2180)
!2180 = !{!2181}
!2181 = !DISubrange(count: 256)
!2182 = !DILocation(line: 497, column: 18, scope: !807)
!2183 = !DILocalVariable(name: "nbufs", scope: !807, file: !1, line: 499, type: !920)
!2184 = !DILocation(line: 499, column: 17, scope: !807)
!2185 = !DILocation(line: 499, column: 39, scope: !807)
!2186 = !DILocation(line: 499, column: 25, scope: !807)
!2187 = !DILocation(line: 501, column: 11, scope: !807)
!2188 = !DILocation(line: 501, column: 16, scope: !807)
!2189 = !DILocation(line: 501, column: 9, scope: !807)
!2190 = !DILocation(line: 502, column: 8, scope: !2191)
!2191 = distinct !DILexicalBlock(scope: !807, file: !1, line: 502, column: 7)
!2192 = !DILocation(line: 502, column: 7, scope: !2191)
!2193 = !DILocation(line: 502, column: 14, scope: !2191)
!2194 = !DILocation(line: 502, column: 18, scope: !2191)
!2195 = !DILocation(line: 502, column: 22, scope: !2196)
!2196 = !DILexicalBlockFile(scope: !2191, file: !1, discriminator: 1)
!2197 = !DILocation(line: 502, column: 21, scope: !2196)
!2198 = !DILocation(line: 502, column: 46, scope: !2196)
!2199 = !DILocation(line: 502, column: 51, scope: !2196)
!2200 = !DILocation(line: 502, column: 31, scope: !2196)
!2201 = !DILocation(line: 502, column: 28, scope: !2196)
!2202 = !DILocation(line: 502, column: 7, scope: !2196)
!2203 = !DILocation(line: 503, column: 7, scope: !2191)
!2204 = !DILocation(line: 503, column: 13, scope: !2191)
!2205 = !DILocation(line: 503, column: 5, scope: !2191)
!2206 = !DILocation(line: 504, column: 3, scope: !807)
!2207 = !DILocation(line: 504, column: 11, scope: !2208)
!2208 = !DILexicalBlockFile(scope: !2209, file: !1, discriminator: 1)
!2209 = distinct !DILexicalBlock(scope: !2210, file: !1, line: 504, column: 3)
!2210 = distinct !DILexicalBlock(scope: !807, file: !1, line: 504, column: 3)
!2211 = !DILocation(line: 504, column: 10, scope: !2208)
!2212 = !DILocation(line: 504, column: 34, scope: !2208)
!2213 = !DILocation(line: 504, column: 39, scope: !2208)
!2214 = !DILocation(line: 504, column: 19, scope: !2208)
!2215 = !DILocation(line: 504, column: 17, scope: !2208)
!2216 = !DILocation(line: 504, column: 3, scope: !2208)
!2217 = !DILocation(line: 505, column: 32, scope: !2209)
!2218 = !DILocation(line: 505, column: 31, scope: !2209)
!2219 = !DILocation(line: 505, column: 25, scope: !2209)
!2220 = !DILocation(line: 505, column: 5, scope: !2209)
!2221 = !DILocation(line: 504, column: 49, scope: !2222)
!2222 = !DILexicalBlockFile(scope: !2209, file: !1, discriminator: 2)
!2223 = !DILocation(line: 504, column: 55, scope: !2222)
!2224 = !DILocation(line: 504, column: 3, scope: !2222)
!2225 = !DILocation(line: 507, column: 23, scope: !807)
!2226 = !DILocation(line: 507, column: 28, scope: !807)
!2227 = !DILocation(line: 507, column: 3, scope: !807)
!2228 = !DILocation(line: 508, column: 3, scope: !807)
!2229 = !DILocation(line: 508, column: 8, scope: !807)
!2230 = !DILocation(line: 508, column: 12, scope: !807)
!2231 = !DILocation(line: 509, column: 1, scope: !807)
!2232 = !DILocalVariable(name: "req", arg: 1, scope: !917, file: !1, line: 478, type: !810)
!2233 = !DILocation(line: 478, column: 45, scope: !917)
!2234 = !DILocation(line: 482, column: 11, scope: !917)
!2235 = !DILocation(line: 482, column: 16, scope: !917)
!2236 = !DILocation(line: 482, column: 3, scope: !917)
!2237 = !DILocalVariable(name: "req", arg: 1, scope: !891, file: !1, line: 512, type: !810)
!2238 = !DILocation(line: 512, column: 33, scope: !891)
!2239 = !DILocalVariable(name: "ent", arg: 2, scope: !891, file: !1, line: 512, type: !894)
!2240 = !DILocation(line: 512, column: 51, scope: !891)
!2241 = !DILocalVariable(name: "dents", scope: !891, file: !1, line: 513, type: !2167)
!2242 = !DILocation(line: 513, column: 18, scope: !891)
!2243 = !DILocalVariable(name: "dent", scope: !891, file: !1, line: 514, type: !2168)
!2244 = !DILocation(line: 514, column: 17, scope: !891)
!2245 = !DILocalVariable(name: "nbufs", scope: !891, file: !1, line: 515, type: !920)
!2246 = !DILocation(line: 515, column: 17, scope: !891)
!2247 = !DILocation(line: 518, column: 7, scope: !2248)
!2248 = distinct !DILexicalBlock(scope: !891, file: !1, line: 518, column: 7)
!2249 = !DILocation(line: 518, column: 12, scope: !2248)
!2250 = !DILocation(line: 518, column: 19, scope: !2248)
!2251 = !DILocation(line: 518, column: 7, scope: !891)
!2252 = !DILocation(line: 519, column: 12, scope: !2248)
!2253 = !DILocation(line: 519, column: 17, scope: !2248)
!2254 = !DILocation(line: 519, column: 5, scope: !2248)
!2255 = !DILocation(line: 522, column: 8, scope: !2256)
!2256 = distinct !DILexicalBlock(scope: !891, file: !1, line: 522, column: 7)
!2257 = !DILocation(line: 522, column: 13, scope: !2256)
!2258 = !DILocation(line: 522, column: 7, scope: !891)
!2259 = !DILocation(line: 523, column: 5, scope: !2256)
!2260 = !DILocation(line: 525, column: 25, scope: !891)
!2261 = !DILocation(line: 525, column: 11, scope: !891)
!2262 = !DILocation(line: 525, column: 9, scope: !891)
!2263 = !DILocation(line: 526, column: 3, scope: !891)
!2264 = !DILocation(line: 526, column: 3, scope: !2265)
!2265 = !DILexicalBlockFile(scope: !891, file: !1, discriminator: 1)
!2266 = !DILocation(line: 526, column: 3, scope: !2267)
!2267 = !DILexicalBlockFile(scope: !891, file: !1, discriminator: 2)
!2268 = !DILocation(line: 526, column: 3, scope: !2269)
!2269 = !DILexicalBlockFile(scope: !891, file: !1, discriminator: 3)
!2270 = !DILocation(line: 528, column: 11, scope: !891)
!2271 = !DILocation(line: 528, column: 16, scope: !891)
!2272 = !DILocation(line: 528, column: 9, scope: !891)
!2273 = !DILocation(line: 531, column: 8, scope: !2274)
!2274 = distinct !DILexicalBlock(scope: !891, file: !1, line: 531, column: 7)
!2275 = !DILocation(line: 531, column: 7, scope: !2274)
!2276 = !DILocation(line: 531, column: 14, scope: !2274)
!2277 = !DILocation(line: 531, column: 7, scope: !891)
!2278 = !DILocation(line: 532, column: 32, scope: !2274)
!2279 = !DILocation(line: 532, column: 31, scope: !2274)
!2280 = !DILocation(line: 532, column: 38, scope: !2274)
!2281 = !DILocation(line: 532, column: 25, scope: !2274)
!2282 = !DILocation(line: 532, column: 5, scope: !2274)
!2283 = !DILocation(line: 535, column: 8, scope: !2284)
!2284 = distinct !DILexicalBlock(scope: !891, file: !1, line: 535, column: 7)
!2285 = !DILocation(line: 535, column: 7, scope: !2284)
!2286 = !DILocation(line: 535, column: 32, scope: !2284)
!2287 = !DILocation(line: 535, column: 37, scope: !2284)
!2288 = !DILocation(line: 535, column: 17, scope: !2284)
!2289 = !DILocation(line: 535, column: 14, scope: !2284)
!2290 = !DILocation(line: 535, column: 7, scope: !891)
!2291 = !DILocation(line: 536, column: 25, scope: !2292)
!2292 = distinct !DILexicalBlock(scope: !2284, file: !1, line: 535, column: 45)
!2293 = !DILocation(line: 536, column: 5, scope: !2292)
!2294 = !DILocation(line: 537, column: 5, scope: !2292)
!2295 = !DILocation(line: 537, column: 10, scope: !2292)
!2296 = !DILocation(line: 537, column: 14, scope: !2292)
!2297 = !DILocation(line: 538, column: 5, scope: !2292)
!2298 = !DILocation(line: 541, column: 18, scope: !891)
!2299 = !DILocation(line: 541, column: 24, scope: !891)
!2300 = !DILocation(line: 541, column: 10, scope: !891)
!2301 = !DILocation(line: 541, column: 8, scope: !891)
!2302 = !DILocation(line: 543, column: 15, scope: !891)
!2303 = !DILocation(line: 543, column: 21, scope: !891)
!2304 = !DILocation(line: 543, column: 3, scope: !891)
!2305 = !DILocation(line: 543, column: 8, scope: !891)
!2306 = !DILocation(line: 543, column: 13, scope: !891)
!2307 = !DILocation(line: 545, column: 11, scope: !891)
!2308 = !DILocation(line: 545, column: 17, scope: !891)
!2309 = !DILocation(line: 545, column: 3, scope: !891)
!2310 = !DILocation(line: 547, column: 7, scope: !2311)
!2311 = distinct !DILexicalBlock(scope: !891, file: !1, line: 545, column: 25)
!2312 = !DILocation(line: 547, column: 12, scope: !2311)
!2313 = !DILocation(line: 547, column: 17, scope: !2311)
!2314 = !DILocation(line: 548, column: 7, scope: !2311)
!2315 = !DILocation(line: 550, column: 7, scope: !2311)
!2316 = !DILocation(line: 550, column: 12, scope: !2311)
!2317 = !DILocation(line: 550, column: 17, scope: !2311)
!2318 = !DILocation(line: 551, column: 7, scope: !2311)
!2319 = !DILocation(line: 553, column: 7, scope: !2311)
!2320 = !DILocation(line: 553, column: 12, scope: !2311)
!2321 = !DILocation(line: 553, column: 17, scope: !2311)
!2322 = !DILocation(line: 554, column: 7, scope: !2311)
!2323 = !DILocation(line: 556, column: 7, scope: !2311)
!2324 = !DILocation(line: 556, column: 12, scope: !2311)
!2325 = !DILocation(line: 556, column: 17, scope: !2311)
!2326 = !DILocation(line: 557, column: 7, scope: !2311)
!2327 = !DILocation(line: 559, column: 7, scope: !2311)
!2328 = !DILocation(line: 559, column: 12, scope: !2311)
!2329 = !DILocation(line: 559, column: 17, scope: !2311)
!2330 = !DILocation(line: 560, column: 7, scope: !2311)
!2331 = !DILocation(line: 562, column: 7, scope: !2311)
!2332 = !DILocation(line: 562, column: 12, scope: !2311)
!2333 = !DILocation(line: 562, column: 17, scope: !2311)
!2334 = !DILocation(line: 563, column: 7, scope: !2311)
!2335 = !DILocation(line: 565, column: 7, scope: !2311)
!2336 = !DILocation(line: 565, column: 12, scope: !2311)
!2337 = !DILocation(line: 565, column: 17, scope: !2311)
!2338 = !DILocation(line: 566, column: 7, scope: !2311)
!2339 = !DILocation(line: 568, column: 7, scope: !2311)
!2340 = !DILocation(line: 568, column: 12, scope: !2311)
!2341 = !DILocation(line: 568, column: 17, scope: !2311)
!2342 = !DILocation(line: 569, column: 3, scope: !2311)
!2343 = !DILocation(line: 574, column: 3, scope: !891)
!2344 = !DILocation(line: 575, column: 1, scope: !891)
!2345 = !DILocalVariable(name: "loop", arg: 1, scope: !901, file: !1, line: 578, type: !187)
!2346 = !DILocation(line: 578, column: 34, scope: !901)
!2347 = !DILocalVariable(name: "option", arg: 2, scope: !901, file: !1, line: 578, type: !904)
!2348 = !DILocation(line: 578, column: 55, scope: !901)
!2349 = !DILocalVariable(name: "ap", scope: !901, file: !1, line: 579, type: !2350)
!2350 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !594, line: 79, baseType: !2351)
!2351 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !2352, line: 50, baseType: !2353)
!2352 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2353 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 579, baseType: !2354)
!2354 = !DICompositeType(tag: DW_TAG_array_type, baseType: !2355, size: 192, align: 64, elements: !738)
!2355 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 579, size: 192, align: 64, elements: !2356)
!2356 = !{!2357, !2358, !2359, !2360}
!2357 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !2355, file: !1, line: 579, baseType: !193, size: 32, align: 32)
!2358 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !2355, file: !1, line: 579, baseType: !193, size: 32, align: 32, offset: 32)
!2359 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !2355, file: !1, line: 579, baseType: !171, size: 64, align: 64, offset: 64)
!2360 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !2355, file: !1, line: 579, baseType: !171, size: 64, align: 64, offset: 128)
!2361 = !DILocation(line: 579, column: 11, scope: !901)
!2362 = !DILocalVariable(name: "err", scope: !901, file: !1, line: 580, type: !200)
!2363 = !DILocation(line: 580, column: 7, scope: !901)
!2364 = !DILocation(line: 582, column: 3, scope: !901)
!2365 = !DILocation(line: 584, column: 28, scope: !901)
!2366 = !DILocation(line: 584, column: 34, scope: !901)
!2367 = !DILocation(line: 584, column: 42, scope: !901)
!2368 = !DILocation(line: 584, column: 9, scope: !901)
!2369 = !DILocation(line: 584, column: 7, scope: !901)
!2370 = !DILocation(line: 585, column: 3, scope: !901)
!2371 = !DILocation(line: 587, column: 10, scope: !901)
!2372 = !DILocation(line: 587, column: 3, scope: !901)
!2373 = !DILocation(line: 596, column: 7, scope: !2374)
!2374 = distinct !DILexicalBlock(scope: !905, file: !1, line: 596, column: 7)
!2375 = !DILocation(line: 596, column: 24, scope: !2374)
!2376 = !DILocation(line: 596, column: 7, scope: !905)
!2377 = !DILocation(line: 597, column: 12, scope: !2374)
!2378 = !DILocation(line: 597, column: 5, scope: !2374)
!2379 = !DILocation(line: 599, column: 7, scope: !2380)
!2380 = distinct !DILexicalBlock(scope: !905, file: !1, line: 599, column: 7)
!2381 = !DILocation(line: 599, column: 7, scope: !905)
!2382 = !DILocation(line: 600, column: 5, scope: !2380)
!2383 = !DILocation(line: 602, column: 20, scope: !905)
!2384 = !DILocation(line: 603, column: 10, scope: !905)
!2385 = !DILocation(line: 603, column: 3, scope: !905)
!2386 = !DILocation(line: 604, column: 1, scope: !905)
!2387 = !DILocalVariable(name: "loop", scope: !908, file: !1, line: 608, type: !187)
!2388 = !DILocation(line: 608, column: 14, scope: !908)
!2389 = !DILocation(line: 610, column: 10, scope: !908)
!2390 = !DILocation(line: 610, column: 8, scope: !908)
!2391 = !DILocation(line: 611, column: 7, scope: !2392)
!2392 = distinct !DILexicalBlock(scope: !908, file: !1, line: 611, column: 7)
!2393 = !DILocation(line: 611, column: 12, scope: !2392)
!2394 = !DILocation(line: 611, column: 7, scope: !908)
!2395 = !DILocation(line: 612, column: 5, scope: !2392)
!2396 = !DILocation(line: 614, column: 20, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !908, file: !1, line: 614, column: 7)
!2398 = !DILocation(line: 614, column: 7, scope: !2397)
!2399 = !DILocation(line: 614, column: 7, scope: !908)
!2400 = !DILocation(line: 615, column: 14, scope: !2401)
!2401 = distinct !DILexicalBlock(scope: !2397, file: !1, line: 614, column: 27)
!2402 = !DILocation(line: 615, column: 5, scope: !2401)
!2403 = !DILocation(line: 616, column: 5, scope: !2401)
!2404 = !DILocation(line: 619, column: 10, scope: !908)
!2405 = !DILocation(line: 619, column: 3, scope: !908)
!2406 = !DILocation(line: 620, column: 1, scope: !908)
!2407 = !DILocalVariable(name: "loop", arg: 1, scope: !909, file: !1, line: 623, type: !187)
!2408 = !DILocation(line: 623, column: 30, scope: !909)
!2409 = !DILocalVariable(name: "q", scope: !909, file: !1, line: 624, type: !180)
!2410 = !DILocation(line: 624, column: 10, scope: !909)
!2411 = !DILocalVariable(name: "h", scope: !909, file: !1, line: 625, type: !181)
!2412 = !DILocation(line: 625, column: 16, scope: !909)
!2413 = !DILocalVariable(name: "saved_data", scope: !909, file: !1, line: 627, type: !171)
!2414 = !DILocation(line: 627, column: 9, scope: !909)
!2415 = !DILocation(line: 630, column: 8, scope: !2416)
!2416 = distinct !DILexicalBlock(scope: !909, file: !1, line: 630, column: 7)
!2417 = !DILocation(line: 630, column: 7, scope: !909)
!2418 = !DILocation(line: 631, column: 5, scope: !2416)
!2419 = !DILocation(line: 633, column: 3, scope: !2420)
!2420 = distinct !DILexicalBlock(scope: !909, file: !1, line: 633, column: 3)
!2421 = !DILocation(line: 633, column: 3, scope: !2422)
!2422 = !DILexicalBlockFile(scope: !2423, file: !1, discriminator: 1)
!2423 = distinct !DILexicalBlock(scope: !2420, file: !1, line: 633, column: 3)
!2424 = !DILocation(line: 634, column: 9, scope: !2425)
!2425 = distinct !DILexicalBlock(scope: !2423, file: !1, line: 633, column: 41)
!2426 = !DILocation(line: 634, column: 7, scope: !2425)
!2427 = !DILocation(line: 635, column: 11, scope: !2428)
!2428 = distinct !DILexicalBlock(scope: !2425, file: !1, line: 635, column: 9)
!2429 = !DILocation(line: 635, column: 14, scope: !2428)
!2430 = !DILocation(line: 635, column: 20, scope: !2428)
!2431 = !DILocation(line: 635, column: 9, scope: !2425)
!2432 = !DILocation(line: 636, column: 7, scope: !2428)
!2433 = !DILocation(line: 637, column: 3, scope: !2425)
!2434 = !DILocation(line: 633, column: 3, scope: !2435)
!2435 = !DILexicalBlockFile(scope: !2423, file: !1, discriminator: 2)
!2436 = !DILocation(line: 639, column: 18, scope: !909)
!2437 = !DILocation(line: 639, column: 3, scope: !909)
!2438 = !DILocation(line: 642, column: 16, scope: !909)
!2439 = !DILocation(line: 642, column: 22, scope: !909)
!2440 = !DILocation(line: 642, column: 14, scope: !909)
!2441 = !DILocation(line: 643, column: 10, scope: !909)
!2442 = !DILocation(line: 643, column: 3, scope: !909)
!2443 = !DILocation(line: 644, column: 16, scope: !909)
!2444 = !DILocation(line: 644, column: 3, scope: !909)
!2445 = !DILocation(line: 644, column: 9, scope: !909)
!2446 = !DILocation(line: 644, column: 14, scope: !909)
!2447 = !DILocation(line: 646, column: 7, scope: !2448)
!2448 = distinct !DILexicalBlock(scope: !909, file: !1, line: 646, column: 7)
!2449 = !DILocation(line: 646, column: 15, scope: !2448)
!2450 = !DILocation(line: 646, column: 12, scope: !2448)
!2451 = !DILocation(line: 646, column: 7, scope: !909)
!2452 = !DILocation(line: 647, column: 22, scope: !2448)
!2453 = !DILocation(line: 647, column: 5, scope: !2448)
!2454 = !DILocation(line: 649, column: 3, scope: !909)
!2455 = !DILocation(line: 650, column: 1, scope: !909)
!2456 = !DILocalVariable(name: "loop", arg: 1, scope: !912, file: !1, line: 653, type: !187)
!2457 = !DILocation(line: 653, column: 32, scope: !912)
!2458 = !DILocalVariable(name: "default_loop", scope: !912, file: !1, line: 654, type: !187)
!2459 = !DILocation(line: 654, column: 14, scope: !912)
!2460 = !DILocalVariable(name: "err", scope: !912, file: !1, line: 655, type: !200)
!2461 = !DILocation(line: 655, column: 7, scope: !912)
!2462 = !DILocation(line: 657, column: 18, scope: !912)
!2463 = !DILocation(line: 657, column: 16, scope: !912)
!2464 = !DILocation(line: 659, column: 23, scope: !912)
!2465 = !DILocation(line: 659, column: 9, scope: !912)
!2466 = !DILocation(line: 659, column: 7, scope: !912)
!2467 = !DILocation(line: 660, column: 10, scope: !912)
!2468 = !DILocation(line: 661, column: 3, scope: !912)
!2469 = !DILocation(line: 661, column: 3, scope: !2470)
!2470 = !DILexicalBlockFile(scope: !912, file: !1, discriminator: 1)
!2471 = !DILocation(line: 661, column: 3, scope: !2472)
!2472 = !DILexicalBlockFile(scope: !912, file: !1, discriminator: 2)
!2473 = !DILocation(line: 661, column: 3, scope: !2474)
!2474 = !DILexicalBlockFile(scope: !912, file: !1, discriminator: 3)
!2475 = !DILocation(line: 662, column: 7, scope: !2476)
!2476 = distinct !DILexicalBlock(scope: !912, file: !1, line: 662, column: 7)
!2477 = !DILocation(line: 662, column: 15, scope: !2476)
!2478 = !DILocation(line: 662, column: 12, scope: !2476)
!2479 = !DILocation(line: 662, column: 7, scope: !912)
!2480 = !DILocation(line: 663, column: 14, scope: !2476)
!2481 = !DILocation(line: 663, column: 5, scope: !2476)
!2482 = !DILocation(line: 664, column: 1, scope: !912)
