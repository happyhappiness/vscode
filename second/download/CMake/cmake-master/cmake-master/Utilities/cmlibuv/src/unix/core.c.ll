; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/core.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.3, %struct.uv_handle_s*, i32 }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.0, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.anon.0 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.1, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.2, i32, i32 }
%union.anon.1 = type { [4 x i8*] }
%struct.anon.2 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%union.anon.3 = type { [4 x i8*] }
%struct.uv_pipe_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8*, i32, i8* }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, {}*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%struct.uv_tcp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.6, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.6 = type { [4 x i8*] }
%struct.uv_udp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.7, %struct.uv_handle_s*, i32, i64, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, %struct.uv__io_s, [2 x i8*], [2 x i8*] }
%union.anon.7 = type { [4 x i8*] }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv_prepare_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.8, %struct.uv_handle_s*, i32, {}*, [2 x i8*] }
%union.anon.8 = type { [4 x i8*] }
%struct.uv_check_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.9, %struct.uv_handle_s*, i32, {}*, [2 x i8*] }
%union.anon.9 = type { [4 x i8*] }
%struct.uv_idle_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.10, %struct.uv_handle_s*, i32, {}*, [2 x i8*] }
%union.anon.10 = type { [4 x i8*] }
%struct.uv_timer_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.11, %struct.uv_handle_s*, i32, {}*, [3 x i8*], i64, i64, i64 }
%union.anon.11 = type { [4 x i8*] }
%struct.uv_process_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.12, %struct.uv_handle_s*, i32, void (%struct.uv_process_s*, i64, i32)*, i32, [2 x i8*], i32 }
%union.anon.12 = type { [4 x i8*] }
%struct.uv_fs_event_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.13, %struct.uv_handle_s*, i32, i8*, void (%struct.uv_fs_event_s*, i8*, i32, i32)*, [2 x i8*], i32 }
%union.anon.13 = type { [4 x i8*] }
%struct.uv_poll_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.14, %struct.uv_handle_s*, i32, void (%struct.uv_poll_s*, i32, i32)*, %struct.uv__io_s }
%union.anon.14 = type { [4 x i8*] }
%struct.uv_fs_poll_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.15, %struct.uv_handle_s*, i32, i8* }
%union.anon.15 = type { [4 x i8*] }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%union.__SOCKADDR_ARG = type { %struct.sockaddr* }
%struct.msghdr = type { i8*, i32, %struct.iovec*, i64, i8*, i64, i32 }
%struct.iovec = type { i8*, i64 }
%struct.cmsghdr = type { i64, i32, i32, [0 x i8] }
%struct.uv_rusage_t = type { %struct.uv_timeval_t, %struct.uv_timeval_t, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64 }
%struct.uv_timeval_t = type { i64, i64 }
%struct.rusage = type { %struct.timeval, %struct.timeval, %union.anon.17, %union.anon.18, %union.anon.19, %union.anon.20, %union.anon.21, %union.anon.22, %union.anon.23, %union.anon.24, %union.anon.25, %union.anon.26, %union.anon.27, %union.anon.28, %union.anon.29, %union.anon.30 }
%struct.timeval = type { i64, i64 }
%union.anon.17 = type { i64 }
%union.anon.18 = type { i64 }
%union.anon.19 = type { i64 }
%union.anon.20 = type { i64 }
%union.anon.21 = type { i64 }
%union.anon.22 = type { i64 }
%union.anon.23 = type { i64 }
%union.anon.24 = type { i64 }
%union.anon.25 = type { i64 }
%union.anon.26 = type { i64 }
%union.anon.27 = type { i64 }
%union.anon.28 = type { i64 }
%union.anon.29 = type { i64 }
%union.anon.30 = type { i64 }
%struct.uv_passwd_s = type { i8*, i64, i64, i8*, i8* }
%struct.passwd = type { i8*, i8*, i32, i32, i8*, i8*, i8* }

@.str = private unnamed_addr constant [53 x i8] c"!(((handle)->flags & (UV_CLOSING | UV_CLOSED)) != 0)\00", align 1
@.str.1 = private unnamed_addr constant [68 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/core.c\00", align 1
@__PRETTY_FUNCTION__.uv_close = private unnamed_addr constant [42 x i8] c"void uv_close(uv_handle_t *, uv_close_cb)\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.3 = private unnamed_addr constant [27 x i8] c"handle->flags & UV_CLOSING\00", align 1
@__PRETTY_FUNCTION__.uv__make_close_pending = private unnamed_addr constant [43 x i8] c"void uv__make_close_pending(uv_handle_t *)\00", align 1
@.str.4 = private unnamed_addr constant [29 x i8] c"!(handle->flags & UV_CLOSED)\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.6 = private unnamed_addr constant [12 x i8] c"sockfd >= 0\00", align 1
@__PRETTY_FUNCTION__.uv__accept = private unnamed_addr constant [20 x i8] c"int uv__accept(int)\00", align 1
@uv__accept.no_accept4 = internal global i32 0, align 4
@.str.7 = private unnamed_addr constant [8 x i8] c"fd > -1\00", align 1
@__PRETTY_FUNCTION__.uv__close_nocheckstdio = private unnamed_addr constant [32 x i8] c"int uv__close_nocheckstdio(int)\00", align 1
@.str.8 = private unnamed_addr constant [7 x i8] c"fd > 2\00", align 1
@__PRETTY_FUNCTION__.uv__close = private unnamed_addr constant [19 x i8] c"int uv__close(int)\00", align 1
@uv__recvmsg.no_msg_cmsg_cloexec = internal global i32 0, align 4
@.str.9 = private unnamed_addr constant [17 x i8] c"cb != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv__io_init = private unnamed_addr constant [45 x i8] c"void uv__io_init(uv__io_t *, uv__io_cb, int)\00", align 1
@.str.10 = private unnamed_addr constant [9 x i8] c"fd >= -1\00", align 1
@.str.11 = private unnamed_addr constant [42 x i8] c"0 == (events & ~(0x001 | 0x004 | 0x2000))\00", align 1
@__PRETTY_FUNCTION__.uv__io_start = private unnamed_addr constant [57 x i8] c"void uv__io_start(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@.str.12 = private unnamed_addr constant [12 x i8] c"0 != events\00", align 1
@.str.13 = private unnamed_addr constant [11 x i8] c"w->fd >= 0\00", align 1
@.str.14 = private unnamed_addr constant [19 x i8] c"w->fd < 2147483647\00", align 1
@__PRETTY_FUNCTION__.uv__io_stop = private unnamed_addr constant [56 x i8] c"void uv__io_stop(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@.str.15 = private unnamed_addr constant [27 x i8] c"loop->watchers[w->fd] == w\00", align 1
@.str.16 = private unnamed_addr constant [15 x i8] c"loop->nfds > 0\00", align 1
@__PRETTY_FUNCTION__.uv__io_active = private unnamed_addr constant [50 x i8] c"int uv__io_active(const uv__io_t *, unsigned int)\00", align 1
@uv__open_cloexec.no_cloexec = internal global i32 0, align 4
@uv__dup2_cloexec.no_dup3 = internal global i32 0, align 4
@.str.17 = private unnamed_addr constant [5 x i8] c"HOME\00", align 1
@.str.18 = private unnamed_addr constant [7 x i8] c"TMPDIR\00", align 1
@.str.19 = private unnamed_addr constant [4 x i8] c"TMP\00", align 1
@.str.20 = private unnamed_addr constant [5 x i8] c"TEMP\00", align 1
@.str.21 = private unnamed_addr constant [8 x i8] c"TEMPDIR\00", align 1
@.str.22 = private unnamed_addr constant [5 x i8] c"/tmp\00", align 1
@__PRETTY_FUNCTION__.uv__finish_close = private unnamed_addr constant [37 x i8] c"void uv__finish_close(uv_handle_t *)\00", align 1

; Function Attrs: nounwind uwtable
define i64 @uv_hrtime() #0 !dbg !909 {
entry:
  %call = call i64 @uv__hrtime(i32 0), !dbg !1142
  ret i64 %call, !dbg !1143
}

declare i64 @uv__hrtime(i32) #1

; Function Attrs: nounwind uwtable
define void @uv_close(%struct.uv_handle_s* %handle, void (%struct.uv_handle_s*)* %close_cb) #0 !dbg !913 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  %close_cb.addr = alloca void (%struct.uv_handle_s*)*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !1144, metadata !1145), !dbg !1146
  store void (%struct.uv_handle_s*)* %close_cb, void (%struct.uv_handle_s*)** %close_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_handle_s*)** %close_cb.addr, metadata !1147, metadata !1145), !dbg !1148
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1149
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !1149
  %1 = load i32, i32* %flags, align 8, !dbg !1149
  %and = and i32 %1, 3, !dbg !1149
  %cmp = icmp ne i32 %and, 0, !dbg !1149
  br i1 %cmp, label %cond.false, label %cond.true, !dbg !1149

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1150

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 101, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @__PRETTY_FUNCTION__.uv_close, i32 0, i32 0)) #8, !dbg !1152
  unreachable, !dbg !1152
                                                  ; No predecessors!
  br label %cond.end, !dbg !1154

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1156
  %flags1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %3, i32 0, i32 7, !dbg !1157
  %4 = load i32, i32* %flags1, align 8, !dbg !1158
  %or = or i32 %4, 1, !dbg !1158
  store i32 %or, i32* %flags1, align 8, !dbg !1158
  %5 = load void (%struct.uv_handle_s*)*, void (%struct.uv_handle_s*)** %close_cb.addr, align 8, !dbg !1159
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1160
  %close_cb2 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 3, !dbg !1161
  store void (%struct.uv_handle_s*)* %5, void (%struct.uv_handle_s*)** %close_cb2, align 8, !dbg !1162
  %7 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1163
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %7, i32 0, i32 2, !dbg !1164
  %8 = load i32, i32* %type, align 8, !dbg !1164
  switch i32 %8, label %sw.default [
    i32 7, label %sw.bb
    i32 14, label %sw.bb3
    i32 12, label %sw.bb4
    i32 15, label %sw.bb5
    i32 9, label %sw.bb6
    i32 2, label %sw.bb7
    i32 6, label %sw.bb8
    i32 1, label %sw.bb9
    i32 13, label %sw.bb10
    i32 10, label %sw.bb11
    i32 3, label %sw.bb12
    i32 8, label %sw.bb13
    i32 4, label %sw.bb14
    i32 16, label %sw.bb15
  ], !dbg !1165

sw.bb:                                            ; preds = %cond.end
  %9 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1166
  %10 = bitcast %struct.uv_handle_s* %9 to %struct.uv_pipe_s*, !dbg !1168
  call void @uv__pipe_close(%struct.uv_pipe_s* %10), !dbg !1169
  br label %sw.epilog, !dbg !1170

sw.bb3:                                           ; preds = %cond.end
  %11 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1171
  %12 = bitcast %struct.uv_handle_s* %11 to %struct.uv_stream_s*, !dbg !1172
  call void @uv__stream_close(%struct.uv_stream_s* %12), !dbg !1173
  br label %sw.epilog, !dbg !1174

sw.bb4:                                           ; preds = %cond.end
  %13 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1175
  %14 = bitcast %struct.uv_handle_s* %13 to %struct.uv_tcp_s*, !dbg !1176
  call void @uv__tcp_close(%struct.uv_tcp_s* %14), !dbg !1177
  br label %sw.epilog, !dbg !1178

sw.bb5:                                           ; preds = %cond.end
  %15 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1179
  %16 = bitcast %struct.uv_handle_s* %15 to %struct.uv_udp_s*, !dbg !1180
  call void @uv__udp_close(%struct.uv_udp_s* %16), !dbg !1181
  br label %sw.epilog, !dbg !1182

sw.bb6:                                           ; preds = %cond.end
  %17 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1183
  %18 = bitcast %struct.uv_handle_s* %17 to %struct.uv_prepare_s*, !dbg !1184
  call void @uv__prepare_close(%struct.uv_prepare_s* %18), !dbg !1185
  br label %sw.epilog, !dbg !1186

sw.bb7:                                           ; preds = %cond.end
  %19 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1187
  %20 = bitcast %struct.uv_handle_s* %19 to %struct.uv_check_s*, !dbg !1188
  call void @uv__check_close(%struct.uv_check_s* %20), !dbg !1189
  br label %sw.epilog, !dbg !1190

sw.bb8:                                           ; preds = %cond.end
  %21 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1191
  %22 = bitcast %struct.uv_handle_s* %21 to %struct.uv_idle_s*, !dbg !1192
  call void @uv__idle_close(%struct.uv_idle_s* %22), !dbg !1193
  br label %sw.epilog, !dbg !1194

sw.bb9:                                           ; preds = %cond.end
  %23 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1195
  %24 = bitcast %struct.uv_handle_s* %23 to %struct.uv_async_s*, !dbg !1196
  call void @uv__async_close(%struct.uv_async_s* %24), !dbg !1197
  br label %sw.epilog, !dbg !1198

sw.bb10:                                          ; preds = %cond.end
  %25 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1199
  %26 = bitcast %struct.uv_handle_s* %25 to %struct.uv_timer_s*, !dbg !1200
  call void @uv__timer_close(%struct.uv_timer_s* %26), !dbg !1201
  br label %sw.epilog, !dbg !1202

sw.bb11:                                          ; preds = %cond.end
  %27 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1203
  %28 = bitcast %struct.uv_handle_s* %27 to %struct.uv_process_s*, !dbg !1204
  call void @uv__process_close(%struct.uv_process_s* %28), !dbg !1205
  br label %sw.epilog, !dbg !1206

sw.bb12:                                          ; preds = %cond.end
  %29 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1207
  %30 = bitcast %struct.uv_handle_s* %29 to %struct.uv_fs_event_s*, !dbg !1208
  call void @uv__fs_event_close(%struct.uv_fs_event_s* %30), !dbg !1209
  br label %sw.epilog, !dbg !1210

sw.bb13:                                          ; preds = %cond.end
  %31 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1211
  %32 = bitcast %struct.uv_handle_s* %31 to %struct.uv_poll_s*, !dbg !1212
  call void @uv__poll_close(%struct.uv_poll_s* %32), !dbg !1213
  br label %sw.epilog, !dbg !1214

sw.bb14:                                          ; preds = %cond.end
  %33 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1215
  %34 = bitcast %struct.uv_handle_s* %33 to %struct.uv_fs_poll_s*, !dbg !1216
  call void @uv__fs_poll_close(%struct.uv_fs_poll_s* %34), !dbg !1217
  br label %sw.epilog, !dbg !1218

sw.bb15:                                          ; preds = %cond.end
  %35 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1219
  %36 = bitcast %struct.uv_handle_s* %35 to %struct.uv_signal_s*, !dbg !1220
  call void @uv__signal_close(%struct.uv_signal_s* %36), !dbg !1221
  br label %return, !dbg !1222

sw.default:                                       ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 166, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @__PRETTY_FUNCTION__.uv_close, i32 0, i32 0)) #8, !dbg !1223
  unreachable, !dbg !1223

sw.epilog:                                        ; preds = %sw.bb14, %sw.bb13, %sw.bb12, %sw.bb11, %sw.bb10, %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb
  %37 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1224
  call void @uv__make_close_pending(%struct.uv_handle_s* %37), !dbg !1225
  br label %return, !dbg !1226

return:                                           ; preds = %sw.epilog, %sw.bb15
  ret void, !dbg !1227
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

declare void @uv__pipe_close(%struct.uv_pipe_s*) #1

declare void @uv__stream_close(%struct.uv_stream_s*) #1

declare void @uv__tcp_close(%struct.uv_tcp_s*) #1

declare void @uv__udp_close(%struct.uv_udp_s*) #1

declare void @uv__prepare_close(%struct.uv_prepare_s*) #1

declare void @uv__check_close(%struct.uv_check_s*) #1

declare void @uv__idle_close(%struct.uv_idle_s*) #1

declare void @uv__async_close(%struct.uv_async_s*) #1

declare void @uv__timer_close(%struct.uv_timer_s*) #1

declare void @uv__process_close(%struct.uv_process_s*) #1

declare void @uv__fs_event_close(%struct.uv_fs_event_s*) #1

declare void @uv__poll_close(%struct.uv_poll_s*) #1

declare void @uv__fs_poll_close(%struct.uv_fs_poll_s*) #1

declare void @uv__signal_close(%struct.uv_signal_s*) #1

; Function Attrs: nounwind uwtable
define void @uv__make_close_pending(%struct.uv_handle_s* %handle) #0 !dbg !919 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !1228, metadata !1145), !dbg !1229
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1230
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !1230
  %1 = load i32, i32* %flags, align 8, !dbg !1230
  %and = and i32 %1, 1, !dbg !1230
  %tobool = icmp ne i32 %and, 0, !dbg !1230
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !1230

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1231

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 201, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.uv__make_close_pending, i32 0, i32 0)) #8, !dbg !1233
  unreachable, !dbg !1233
                                                  ; No predecessors!
  br label %cond.end, !dbg !1235

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1237
  %flags1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %3, i32 0, i32 7, !dbg !1237
  %4 = load i32, i32* %flags1, align 8, !dbg !1237
  %and2 = and i32 %4, 2, !dbg !1237
  %tobool3 = icmp ne i32 %and2, 0, !dbg !1237
  br i1 %tobool3, label %cond.false5, label %cond.true4, !dbg !1237

cond.true4:                                       ; preds = %cond.end
  br label %cond.end6, !dbg !1238

cond.false5:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 202, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.uv__make_close_pending, i32 0, i32 0)) #8, !dbg !1239
  unreachable, !dbg !1239
                                                  ; No predecessors!
  br label %cond.end6, !dbg !1240

cond.end6:                                        ; preds = %5, %cond.true4
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1241
  %loop = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 1, !dbg !1242
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1242
  %closing_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 16, !dbg !1243
  %8 = load %struct.uv_handle_s*, %struct.uv_handle_s** %closing_handles, align 8, !dbg !1243
  %9 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1244
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 6, !dbg !1245
  store %struct.uv_handle_s* %8, %struct.uv_handle_s** %next_closing, align 8, !dbg !1246
  %10 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1247
  %11 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1248
  %loop7 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %11, i32 0, i32 1, !dbg !1249
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop7, align 8, !dbg !1249
  %closing_handles8 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 16, !dbg !1250
  store %struct.uv_handle_s* %10, %struct.uv_handle_s** %closing_handles8, align 8, !dbg !1251
  ret void, !dbg !1252
}

; Function Attrs: nounwind uwtable
define i32 @uv__socket_sockopt(%struct.uv_handle_s* %handle, i32 %optname, i32* %value) #0 !dbg !916 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  %optname.addr = alloca i32, align 4
  %value.addr = alloca i32*, align 8
  %r = alloca i32, align 4
  %fd = alloca i32, align 4
  %len = alloca i32, align 4
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !1253, metadata !1145), !dbg !1254
  store i32 %optname, i32* %optname.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %optname.addr, metadata !1255, metadata !1145), !dbg !1256
  store i32* %value, i32** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %value.addr, metadata !1257, metadata !1145), !dbg !1258
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1259, metadata !1145), !dbg !1260
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1261, metadata !1145), !dbg !1262
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1263, metadata !1145), !dbg !1264
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1265
  %cmp = icmp eq %struct.uv_handle_s* %0, null, !dbg !1267
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1268

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32*, i32** %value.addr, align 8, !dbg !1269
  %cmp1 = icmp eq i32* %1, null, !dbg !1271
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1272

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1273
  br label %return, !dbg !1273

if.end:                                           ; preds = %lor.lhs.false
  %2 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1274
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 2, !dbg !1276
  %3 = load i32, i32* %type, align 8, !dbg !1276
  %cmp2 = icmp eq i32 %3, 12, !dbg !1277
  br i1 %cmp2, label %if.then6, label %lor.lhs.false3, !dbg !1278

lor.lhs.false3:                                   ; preds = %if.end
  %4 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1279
  %type4 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !1281
  %5 = load i32, i32* %type4, align 8, !dbg !1281
  %cmp5 = icmp eq i32 %5, 7, !dbg !1282
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !1283

if.then6:                                         ; preds = %lor.lhs.false3, %if.end
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1284
  %7 = bitcast %struct.uv_handle_s* %6 to %struct.uv_stream_s*, !dbg !1284
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 13, !dbg !1284
  %fd7 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1284
  %8 = load i32, i32* %fd7, align 8, !dbg !1284
  store i32 %8, i32* %fd, align 4, !dbg !1285
  br label %if.end15, !dbg !1286

if.else:                                          ; preds = %lor.lhs.false3
  %9 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1287
  %type8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 2, !dbg !1289
  %10 = load i32, i32* %type8, align 8, !dbg !1289
  %cmp9 = icmp eq i32 %10, 15, !dbg !1290
  br i1 %cmp9, label %if.then10, label %if.else13, !dbg !1291

if.then10:                                        ; preds = %if.else
  %11 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1292
  %12 = bitcast %struct.uv_handle_s* %11 to %struct.uv_udp_s*, !dbg !1293
  %io_watcher11 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %12, i32 0, i32 12, !dbg !1293
  %fd12 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher11, i32 0, i32 5, !dbg !1294
  %13 = load i32, i32* %fd12, align 8, !dbg !1294
  store i32 %13, i32* %fd, align 4, !dbg !1295
  br label %if.end14, !dbg !1296

if.else13:                                        ; preds = %if.else
  store i32 -95, i32* %retval, align 4, !dbg !1297
  br label %return, !dbg !1297

if.end14:                                         ; preds = %if.then10
  br label %if.end15

if.end15:                                         ; preds = %if.end14, %if.then6
  store i32 4, i32* %len, align 4, !dbg !1298
  %14 = load i32*, i32** %value.addr, align 8, !dbg !1299
  %15 = load i32, i32* %14, align 4, !dbg !1301
  %cmp16 = icmp eq i32 %15, 0, !dbg !1302
  br i1 %cmp16, label %if.then17, label %if.else18, !dbg !1303

if.then17:                                        ; preds = %if.end15
  %16 = load i32, i32* %fd, align 4, !dbg !1304
  %17 = load i32, i32* %optname.addr, align 4, !dbg !1305
  %18 = load i32*, i32** %value.addr, align 8, !dbg !1306
  %19 = bitcast i32* %18 to i8*, !dbg !1306
  %call = call i32 @getsockopt(i32 %16, i32 1, i32 %17, i8* %19, i32* %len) #9, !dbg !1307
  store i32 %call, i32* %r, align 4, !dbg !1308
  br label %if.end20, !dbg !1309

if.else18:                                        ; preds = %if.end15
  %20 = load i32, i32* %fd, align 4, !dbg !1310
  %21 = load i32, i32* %optname.addr, align 4, !dbg !1311
  %22 = load i32*, i32** %value.addr, align 8, !dbg !1312
  %23 = bitcast i32* %22 to i8*, !dbg !1313
  %24 = load i32, i32* %len, align 4, !dbg !1314
  %call19 = call i32 @setsockopt(i32 %20, i32 1, i32 %21, i8* %23, i32 %24) #9, !dbg !1315
  store i32 %call19, i32* %r, align 4, !dbg !1316
  br label %if.end20

if.end20:                                         ; preds = %if.else18, %if.then17
  %25 = load i32, i32* %r, align 4, !dbg !1317
  %cmp21 = icmp slt i32 %25, 0, !dbg !1319
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !1320

if.then22:                                        ; preds = %if.end20
  %call23 = call i32* @__errno_location() #2, !dbg !1321
  %26 = load i32, i32* %call23, align 4, !dbg !1321
  %sub = sub nsw i32 0, %26, !dbg !1322
  store i32 %sub, i32* %retval, align 4, !dbg !1323
  br label %return, !dbg !1323

if.end24:                                         ; preds = %if.end20
  store i32 0, i32* %retval, align 4, !dbg !1324
  br label %return, !dbg !1324

return:                                           ; preds = %if.end24, %if.then22, %if.else13, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !1325
  ret i32 %27, !dbg !1325
}

; Function Attrs: nounwind
declare i32 @getsockopt(i32, i32, i32, i8*, i32*) #4

; Function Attrs: nounwind
declare i32 @setsockopt(i32, i32, i32, i8*, i32) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind uwtable
define i32 @uv__getiovmax() #0 !dbg !920 {
entry:
  ret i32 1024, !dbg !1326
}

; Function Attrs: nounwind uwtable
define i32 @uv_is_closing(%struct.uv_handle_s* %handle) #0 !dbg !923 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !1327, metadata !1145), !dbg !1328
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1329
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !1329
  %1 = load i32, i32* %flags, align 8, !dbg !1329
  %and = and i32 %1, 3, !dbg !1329
  %cmp = icmp ne i32 %and, 0, !dbg !1329
  %conv = zext i1 %cmp to i32, !dbg !1329
  ret i32 %conv, !dbg !1330
}

; Function Attrs: nounwind uwtable
define i32 @uv_backend_fd(%struct.uv_loop_s* %loop) #0 !dbg !928 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1331, metadata !1145), !dbg !1332
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1333
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 6, !dbg !1334
  %1 = load i32, i32* %backend_fd, align 8, !dbg !1334
  ret i32 %1, !dbg !1335
}

; Function Attrs: nounwind uwtable
define i32 @uv_backend_timeout(%struct.uv_loop_s* %loop) #0 !dbg !933 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1336, metadata !1145), !dbg !1337
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1338
  %stop_flag = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 4, !dbg !1340
  %1 = load i32, i32* %stop_flag, align 8, !dbg !1340
  %cmp = icmp ne i32 %1, 0, !dbg !1341
  br i1 %cmp, label %if.then, label %if.end, !dbg !1342

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1343
  br label %return, !dbg !1343

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1344
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 1, !dbg !1344
  %3 = load i32, i32* %active_handles, align 8, !dbg !1344
  %cmp1 = icmp ugt i32 %3, 0, !dbg !1344
  br i1 %cmp1, label %if.end7, label %land.lhs.true, !dbg !1346

land.lhs.true:                                    ; preds = %if.end
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1347
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 3, !dbg !1347
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1347
  %active_reqs2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 3, !dbg !1347
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs2, i64 0, i64 0, !dbg !1347
  %6 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1347
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !1347
  %cmp3 = icmp eq [2 x i8*]* %active_reqs, %7, !dbg !1347
  %conv = zext i1 %cmp3 to i32, !dbg !1347
  %cmp4 = icmp eq i32 %conv, 0, !dbg !1347
  br i1 %cmp4, label %if.end7, label %if.then6, !dbg !1349

if.then6:                                         ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !1350
  br label %return, !dbg !1350

if.end7:                                          ; preds = %land.lhs.true, %if.end
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1351
  %idle_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 20, !dbg !1351
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1351
  %idle_handles8 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 20, !dbg !1351
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles8, i64 0, i64 0, !dbg !1351
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1351
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !1351
  %cmp10 = icmp eq [2 x i8*]* %idle_handles, %11, !dbg !1351
  br i1 %cmp10, label %if.end13, label %if.then12, !dbg !1353

if.then12:                                        ; preds = %if.end7
  store i32 0, i32* %retval, align 4, !dbg !1354
  br label %return, !dbg !1354

if.end13:                                         ; preds = %if.end7
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1355
  %pending_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 7, !dbg !1355
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1355
  %pending_queue14 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 7, !dbg !1355
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue14, i64 0, i64 0, !dbg !1355
  %14 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !1355
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !1355
  %cmp16 = icmp eq [2 x i8*]* %pending_queue, %15, !dbg !1355
  br i1 %cmp16, label %if.end19, label %if.then18, !dbg !1357

if.then18:                                        ; preds = %if.end13
  store i32 0, i32* %retval, align 4, !dbg !1358
  br label %return, !dbg !1358

if.end19:                                         ; preds = %if.end13
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1359
  %closing_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 16, !dbg !1361
  %17 = load %struct.uv_handle_s*, %struct.uv_handle_s** %closing_handles, align 8, !dbg !1361
  %tobool = icmp ne %struct.uv_handle_s* %17, null, !dbg !1359
  br i1 %tobool, label %if.then20, label %if.end21, !dbg !1362

if.then20:                                        ; preds = %if.end19
  store i32 0, i32* %retval, align 4, !dbg !1363
  br label %return, !dbg !1363

if.end21:                                         ; preds = %if.end19
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1364
  %call = call i32 @uv__next_timeout(%struct.uv_loop_s* %18), !dbg !1365
  store i32 %call, i32* %retval, align 4, !dbg !1366
  br label %return, !dbg !1366

return:                                           ; preds = %if.end21, %if.then20, %if.then18, %if.then12, %if.then6, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !1367
  ret i32 %19, !dbg !1367
}

declare i32 @uv__next_timeout(%struct.uv_loop_s*) #1

; Function Attrs: nounwind uwtable
define i32 @uv_loop_alive(%struct.uv_loop_s* %loop) #0 !dbg !934 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1368, metadata !1145), !dbg !1369
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1370
  %call = call i32 @uv__loop_alive(%struct.uv_loop_s* %0), !dbg !1371
  ret i32 %call, !dbg !1372
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__loop_alive(%struct.uv_loop_s* %loop) #0 !dbg !1121 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1373, metadata !1145), !dbg !1374
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1375
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 1, !dbg !1375
  %1 = load i32, i32* %active_handles, align 8, !dbg !1375
  %cmp = icmp ugt i32 %1, 0, !dbg !1375
  br i1 %cmp, label %lor.end, label %lor.lhs.false, !dbg !1376

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1377
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 3, !dbg !1377
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1377
  %active_reqs1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1377
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs1, i64 0, i64 0, !dbg !1377
  %4 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1377
  %5 = load [2 x i8*]*, [2 x i8*]** %4, align 8, !dbg !1377
  %cmp2 = icmp eq [2 x i8*]* %active_reqs, %5, !dbg !1377
  %conv = zext i1 %cmp2 to i32, !dbg !1377
  %cmp3 = icmp eq i32 %conv, 0, !dbg !1377
  br i1 %cmp3, label %lor.end, label %lor.rhs, !dbg !1378

lor.rhs:                                          ; preds = %lor.lhs.false
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1379
  %closing_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 16, !dbg !1380
  %7 = load %struct.uv_handle_s*, %struct.uv_handle_s** %closing_handles, align 8, !dbg !1380
  %cmp5 = icmp ne %struct.uv_handle_s* %7, null, !dbg !1381
  br label %lor.end, !dbg !1382

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false, %entry
  %8 = phi i1 [ true, %lor.lhs.false ], [ true, %entry ], [ %cmp5, %lor.rhs ]
  %lor.ext = zext i1 %8 to i32, !dbg !1384
  ret i32 %lor.ext, !dbg !1386
}

; Function Attrs: nounwind uwtable
define i32 @uv_run(%struct.uv_loop_s* %loop, i32 %mode) #0 !dbg !935 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %mode.addr = alloca i32, align 4
  %timeout = alloca i32, align 4
  %r = alloca i32, align 4
  %ran_pending = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1387, metadata !1145), !dbg !1388
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !1389, metadata !1145), !dbg !1390
  call void @llvm.dbg.declare(metadata i32* %timeout, metadata !1391, metadata !1145), !dbg !1392
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1393, metadata !1145), !dbg !1394
  call void @llvm.dbg.declare(metadata i32* %ran_pending, metadata !1395, metadata !1145), !dbg !1396
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1397
  %call = call i32 @uv__loop_alive(%struct.uv_loop_s* %0), !dbg !1398
  store i32 %call, i32* %r, align 4, !dbg !1399
  %1 = load i32, i32* %r, align 4, !dbg !1400
  %tobool = icmp ne i32 %1, 0, !dbg !1400
  br i1 %tobool, label %if.end, label %if.then, !dbg !1402

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1403
  call void @uv__update_time(%struct.uv_loop_s* %2), !dbg !1404
  br label %if.end, !dbg !1404

if.end:                                           ; preds = %if.then, %entry
  br label %while.cond, !dbg !1405

while.cond:                                       ; preds = %if.end17, %if.end
  %3 = load i32, i32* %r, align 4, !dbg !1406
  %cmp = icmp ne i32 %3, 0, !dbg !1408
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1409

land.rhs:                                         ; preds = %while.cond
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1410
  %stop_flag = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 4, !dbg !1412
  %5 = load i32, i32* %stop_flag, align 8, !dbg !1412
  %cmp1 = icmp eq i32 %5, 0, !dbg !1413
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %6 = phi i1 [ false, %while.cond ], [ %cmp1, %land.rhs ]
  br i1 %6, label %while.body, label %while.end, !dbg !1414

while.body:                                       ; preds = %land.end
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1416
  call void @uv__update_time(%struct.uv_loop_s* %7), !dbg !1418
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1419
  call void @uv__run_timers(%struct.uv_loop_s* %8), !dbg !1420
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1421
  %call2 = call i32 @uv__run_pending(%struct.uv_loop_s* %9), !dbg !1422
  store i32 %call2, i32* %ran_pending, align 4, !dbg !1423
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1424
  call void @uv__run_idle(%struct.uv_loop_s* %10), !dbg !1425
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1426
  call void @uv__run_prepare(%struct.uv_loop_s* %11), !dbg !1427
  store i32 0, i32* %timeout, align 4, !dbg !1428
  %12 = load i32, i32* %mode.addr, align 4, !dbg !1429
  %cmp3 = icmp eq i32 %12, 1, !dbg !1431
  br i1 %cmp3, label %land.lhs.true, label %lor.lhs.false, !dbg !1432

land.lhs.true:                                    ; preds = %while.body
  %13 = load i32, i32* %ran_pending, align 4, !dbg !1433
  %tobool4 = icmp ne i32 %13, 0, !dbg !1433
  br i1 %tobool4, label %lor.lhs.false, label %if.then6, !dbg !1435

lor.lhs.false:                                    ; preds = %land.lhs.true, %while.body
  %14 = load i32, i32* %mode.addr, align 4, !dbg !1436
  %cmp5 = icmp eq i32 %14, 0, !dbg !1438
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !1439

if.then6:                                         ; preds = %lor.lhs.false, %land.lhs.true
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1440
  %call7 = call i32 @uv_backend_timeout(%struct.uv_loop_s* %15), !dbg !1441
  store i32 %call7, i32* %timeout, align 4, !dbg !1442
  br label %if.end8, !dbg !1443

if.end8:                                          ; preds = %if.then6, %lor.lhs.false
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1444
  %17 = load i32, i32* %timeout, align 4, !dbg !1445
  call void @uv__io_poll(%struct.uv_loop_s* %16, i32 %17), !dbg !1446
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1447
  call void @uv__run_check(%struct.uv_loop_s* %18), !dbg !1448
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1449
  call void @uv__run_closing_handles(%struct.uv_loop_s* %19), !dbg !1450
  %20 = load i32, i32* %mode.addr, align 4, !dbg !1451
  %cmp9 = icmp eq i32 %20, 1, !dbg !1453
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !1454

if.then10:                                        ; preds = %if.end8
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1455
  call void @uv__update_time(%struct.uv_loop_s* %21), !dbg !1457
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1458
  call void @uv__run_timers(%struct.uv_loop_s* %22), !dbg !1459
  br label %if.end11, !dbg !1460

if.end11:                                         ; preds = %if.then10, %if.end8
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1461
  %call12 = call i32 @uv__loop_alive(%struct.uv_loop_s* %23), !dbg !1462
  store i32 %call12, i32* %r, align 4, !dbg !1463
  %24 = load i32, i32* %mode.addr, align 4, !dbg !1464
  %cmp13 = icmp eq i32 %24, 1, !dbg !1466
  br i1 %cmp13, label %if.then16, label %lor.lhs.false14, !dbg !1467

lor.lhs.false14:                                  ; preds = %if.end11
  %25 = load i32, i32* %mode.addr, align 4, !dbg !1468
  %cmp15 = icmp eq i32 %25, 2, !dbg !1470
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !1471

if.then16:                                        ; preds = %lor.lhs.false14, %if.end11
  br label %while.end, !dbg !1472

if.end17:                                         ; preds = %lor.lhs.false14
  br label %while.cond, !dbg !1473

while.end:                                        ; preds = %if.then16, %land.end
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1475
  %stop_flag18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 4, !dbg !1477
  %27 = load i32, i32* %stop_flag18, align 8, !dbg !1477
  %cmp19 = icmp ne i32 %27, 0, !dbg !1478
  br i1 %cmp19, label %if.then20, label %if.end22, !dbg !1479

if.then20:                                        ; preds = %while.end
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1480
  %stop_flag21 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 4, !dbg !1481
  store i32 0, i32* %stop_flag21, align 8, !dbg !1482
  br label %if.end22, !dbg !1480

if.end22:                                         ; preds = %if.then20, %while.end
  %29 = load i32, i32* %r, align 4, !dbg !1483
  ret i32 %29, !dbg !1484
}

; Function Attrs: nounwind uwtable
define internal void @uv__update_time(%struct.uv_loop_s* %loop) #0 !dbg !1122 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1485, metadata !1145), !dbg !1486
  %call = call i64 @uv__hrtime(i32 1), !dbg !1487
  %div = udiv i64 %call, 1000000, !dbg !1488
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1489
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 27, !dbg !1490
  store i64 %div, i64* %time, align 8, !dbg !1491
  ret void, !dbg !1492
}

declare void @uv__run_timers(%struct.uv_loop_s*) #1

; Function Attrs: nounwind uwtable
define internal i32 @uv__run_pending(%struct.uv_loop_s* %loop) #0 !dbg !1125 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  %pq = alloca [2 x i8*], align 16
  %w = alloca %struct.uv__io_s*, align 8
  %q10 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1493, metadata !1145), !dbg !1494
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1495, metadata !1145), !dbg !1496
  call void @llvm.dbg.declare(metadata [2 x i8*]* %pq, metadata !1497, metadata !1145), !dbg !1498
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w, metadata !1499, metadata !1145), !dbg !1500
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1501
  %pending_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 7, !dbg !1501
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1501
  %pending_queue1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 7, !dbg !1501
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue1, i64 0, i64 0, !dbg !1501
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1501
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !1501
  %cmp = icmp eq [2 x i8*]* %pending_queue, %3, !dbg !1501
  br i1 %cmp, label %if.then, label %if.end, !dbg !1503

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1504
  br label %return, !dbg !1504

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !1505

do.body:                                          ; preds = %if.end
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1506
  %pending_queue2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 7, !dbg !1506
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1506
  %pending_queue3 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 7, !dbg !1506
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue3, i64 0, i64 0, !dbg !1506
  %6 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !1506
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !1506
  %cmp5 = icmp eq [2 x i8*]* %pending_queue2, %7, !dbg !1506
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !1506

if.then6:                                         ; preds = %do.body
  br label %do.body7, !dbg !1510

do.body7:                                         ; preds = %if.then6
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 0, !dbg !1512
  %8 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !1512
  store [2 x i8*]* %pq, [2 x i8*]** %8, align 16, !dbg !1512
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 1, !dbg !1512
  %9 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1512
  store [2 x i8*]* %pq, [2 x i8*]** %9, align 8, !dbg !1512
  br label %do.end, !dbg !1512

do.end:                                           ; preds = %do.body7
  br label %if.end29, !dbg !1515

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q10, metadata !1517, metadata !1145), !dbg !1519
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1520
  %pending_queue11 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 7, !dbg !1520
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue11, i64 0, i64 0, !dbg !1520
  %11 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1520
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !1520
  store [2 x i8*]* %12, [2 x i8*]** %q10, align 8, !dbg !1520
  br label %do.body13, !dbg !1520

do.body13:                                        ; preds = %if.else
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1522
  %pending_queue14 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 7, !dbg !1522
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue14, i64 0, i64 1, !dbg !1522
  %14 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !1522
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !1522
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 1, !dbg !1522
  %16 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1522
  store [2 x i8*]* %15, [2 x i8*]** %16, align 8, !dbg !1522
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 1, !dbg !1522
  %17 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !1522
  %18 = load [2 x i8*]*, [2 x i8*]** %17, align 8, !dbg !1522
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 0, !dbg !1522
  %19 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1522
  store [2 x i8*]* %pq, [2 x i8*]** %19, align 8, !dbg !1522
  %20 = load [2 x i8*]*, [2 x i8*]** %q10, align 8, !dbg !1522
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 0, !dbg !1522
  %21 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !1522
  store [2 x i8*]* %20, [2 x i8*]** %21, align 16, !dbg !1522
  %22 = load [2 x i8*]*, [2 x i8*]** %q10, align 8, !dbg !1522
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !1522
  %23 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !1522
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !1522
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1522
  %pending_queue21 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %25, i32 0, i32 7, !dbg !1522
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue21, i64 0, i64 1, !dbg !1522
  %26 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !1522
  store [2 x i8*]* %24, [2 x i8*]** %26, align 8, !dbg !1522
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1522
  %pending_queue23 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 7, !dbg !1522
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1522
  %pending_queue24 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 7, !dbg !1522
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue24, i64 0, i64 1, !dbg !1522
  %29 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !1522
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !1522
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %30, i64 0, i64 0, !dbg !1522
  %31 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !1522
  store [2 x i8*]* %pending_queue23, [2 x i8*]** %31, align 8, !dbg !1522
  %32 = load [2 x i8*]*, [2 x i8*]** %q10, align 8, !dbg !1522
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %32, i64 0, i64 1, !dbg !1522
  %33 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !1522
  store [2 x i8*]* %pq, [2 x i8*]** %33, align 8, !dbg !1522
  br label %do.end28, !dbg !1522

do.end28:                                         ; preds = %do.body13
  br label %if.end29

if.end29:                                         ; preds = %do.end28, %do.end
  br label %do.end30, !dbg !1525

do.end30:                                         ; preds = %if.end29
  br label %while.cond, !dbg !1527

while.cond:                                       ; preds = %do.end45, %do.end30
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 0, !dbg !1528
  %34 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !1528
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 16, !dbg !1528
  %cmp32 = icmp eq [2 x i8*]* %pq, %35, !dbg !1528
  %lnot = xor i1 %cmp32, true, !dbg !1530
  br i1 %lnot, label %while.body, label %while.end, !dbg !1531

while.body:                                       ; preds = %while.cond
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pq, i64 0, i64 0, !dbg !1532
  %36 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !1532
  %37 = load [2 x i8*]*, [2 x i8*]** %36, align 16, !dbg !1532
  store [2 x i8*]* %37, [2 x i8*]** %q, align 8, !dbg !1534
  br label %do.body34, !dbg !1535

do.body34:                                        ; preds = %while.body
  %38 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1536
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %38, i64 0, i64 0, !dbg !1536
  %39 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !1536
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1536
  %41 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1536
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %41, i64 0, i64 1, !dbg !1536
  %42 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !1536
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !1536
  %arrayidx37 = getelementptr inbounds [2 x i8*], [2 x i8*]* %43, i64 0, i64 0, !dbg !1536
  %44 = bitcast i8** %arrayidx37 to [2 x i8*]**, !dbg !1536
  store [2 x i8*]* %40, [2 x i8*]** %44, align 8, !dbg !1536
  %45 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1536
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %45, i64 0, i64 1, !dbg !1536
  %46 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1536
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1536
  %48 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1536
  %arrayidx39 = getelementptr inbounds [2 x i8*], [2 x i8*]* %48, i64 0, i64 0, !dbg !1536
  %49 = bitcast i8** %arrayidx39 to [2 x i8*]**, !dbg !1536
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !1536
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 1, !dbg !1536
  %51 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !1536
  store [2 x i8*]* %47, [2 x i8*]** %51, align 8, !dbg !1536
  br label %do.end41, !dbg !1536

do.end41:                                         ; preds = %do.body34
  br label %do.body42, !dbg !1539

do.body42:                                        ; preds = %do.end41
  %52 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1540
  %53 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1540
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %53, i64 0, i64 0, !dbg !1540
  %54 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !1540
  store [2 x i8*]* %52, [2 x i8*]** %54, align 8, !dbg !1540
  %55 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1540
  %56 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1540
  %arrayidx44 = getelementptr inbounds [2 x i8*], [2 x i8*]* %56, i64 0, i64 1, !dbg !1540
  %57 = bitcast i8** %arrayidx44 to [2 x i8*]**, !dbg !1540
  store [2 x i8*]* %55, [2 x i8*]** %57, align 8, !dbg !1540
  br label %do.end45, !dbg !1540

do.end45:                                         ; preds = %do.body42
  %58 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1543
  %59 = bitcast [2 x i8*]* %58 to i8*, !dbg !1543
  %add.ptr = getelementptr inbounds i8, i8* %59, i64 -8, !dbg !1543
  %60 = bitcast i8* %add.ptr to %struct.uv__io_s*, !dbg !1543
  store %struct.uv__io_s* %60, %struct.uv__io_s** %w, align 8, !dbg !1544
  %61 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1545
  %cb = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %61, i32 0, i32 0, !dbg !1546
  %62 = load void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb, align 8, !dbg !1546
  %63 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1547
  %64 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1548
  call void %62(%struct.uv_loop_s* %63, %struct.uv__io_s* %64, i32 4), !dbg !1545
  br label %while.cond, !dbg !1549

while.end:                                        ; preds = %while.cond
  store i32 1, i32* %retval, align 4, !dbg !1551
  br label %return, !dbg !1551

return:                                           ; preds = %while.end, %if.then
  %65 = load i32, i32* %retval, align 4, !dbg !1552
  ret i32 %65, !dbg !1552
}

declare void @uv__run_idle(%struct.uv_loop_s*) #1

declare void @uv__run_prepare(%struct.uv_loop_s*) #1

declare void @uv__io_poll(%struct.uv_loop_s*, i32) #1

declare void @uv__run_check(%struct.uv_loop_s*) #1

; Function Attrs: nounwind uwtable
define internal void @uv__run_closing_handles(%struct.uv_loop_s* %loop) #0 !dbg !1123 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %p = alloca %struct.uv_handle_s*, align 8
  %q = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1553, metadata !1145), !dbg !1554
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %p, metadata !1555, metadata !1145), !dbg !1556
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %q, metadata !1557, metadata !1145), !dbg !1558
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1559
  %closing_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 16, !dbg !1560
  %1 = load %struct.uv_handle_s*, %struct.uv_handle_s** %closing_handles, align 8, !dbg !1560
  store %struct.uv_handle_s* %1, %struct.uv_handle_s** %p, align 8, !dbg !1561
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1562
  %closing_handles1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 16, !dbg !1563
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %closing_handles1, align 8, !dbg !1564
  br label %while.cond, !dbg !1565

while.cond:                                       ; preds = %while.body, %entry
  %3 = load %struct.uv_handle_s*, %struct.uv_handle_s** %p, align 8, !dbg !1566
  %tobool = icmp ne %struct.uv_handle_s* %3, null, !dbg !1568
  br i1 %tobool, label %while.body, label %while.end, !dbg !1568

while.body:                                       ; preds = %while.cond
  %4 = load %struct.uv_handle_s*, %struct.uv_handle_s** %p, align 8, !dbg !1569
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 6, !dbg !1571
  %5 = load %struct.uv_handle_s*, %struct.uv_handle_s** %next_closing, align 8, !dbg !1571
  store %struct.uv_handle_s* %5, %struct.uv_handle_s** %q, align 8, !dbg !1572
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %p, align 8, !dbg !1573
  call void @uv__finish_close(%struct.uv_handle_s* %6), !dbg !1574
  %7 = load %struct.uv_handle_s*, %struct.uv_handle_s** %q, align 8, !dbg !1575
  store %struct.uv_handle_s* %7, %struct.uv_handle_s** %p, align 8, !dbg !1576
  br label %while.cond, !dbg !1577

while.end:                                        ; preds = %while.cond
  ret void, !dbg !1579
}

; Function Attrs: nounwind uwtable
define void @uv_update_time(%struct.uv_loop_s* %loop) #0 !dbg !939 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1580, metadata !1145), !dbg !1581
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1582
  call void @uv__update_time(%struct.uv_loop_s* %0), !dbg !1583
  ret void, !dbg !1584
}

; Function Attrs: nounwind uwtable
define i32 @uv_is_active(%struct.uv_handle_s* %handle) #0 !dbg !942 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !1585, metadata !1145), !dbg !1586
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1587
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !1587
  %1 = load i32, i32* %flags, align 8, !dbg !1587
  %and = and i32 %1, 16384, !dbg !1587
  %cmp = icmp ne i32 %and, 0, !dbg !1587
  %conv = zext i1 %cmp to i32, !dbg !1587
  ret i32 %conv, !dbg !1588
}

; Function Attrs: nounwind uwtable
define i32 @uv__socket(i32 %domain, i32 %type, i32 %protocol) #0 !dbg !943 {
entry:
  %retval = alloca i32, align 4
  %domain.addr = alloca i32, align 4
  %type.addr = alloca i32, align 4
  %protocol.addr = alloca i32, align 4
  %sockfd = alloca i32, align 4
  %err = alloca i32, align 4
  store i32 %domain, i32* %domain.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %domain.addr, metadata !1589, metadata !1145), !dbg !1590
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1591, metadata !1145), !dbg !1592
  store i32 %protocol, i32* %protocol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %protocol.addr, metadata !1593, metadata !1145), !dbg !1594
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !1595, metadata !1145), !dbg !1596
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1597, metadata !1145), !dbg !1598
  %0 = load i32, i32* %domain.addr, align 4, !dbg !1599
  %1 = load i32, i32* %type.addr, align 4, !dbg !1600
  %or = or i32 %1, 2048, !dbg !1601
  %or1 = or i32 %or, 524288, !dbg !1602
  %2 = load i32, i32* %protocol.addr, align 4, !dbg !1603
  %call = call i32 @socket(i32 %0, i32 %or1, i32 %2) #9, !dbg !1604
  store i32 %call, i32* %sockfd, align 4, !dbg !1605
  %3 = load i32, i32* %sockfd, align 4, !dbg !1606
  %cmp = icmp ne i32 %3, -1, !dbg !1608
  br i1 %cmp, label %if.then, label %if.end, !dbg !1609

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %sockfd, align 4, !dbg !1610
  store i32 %4, i32* %retval, align 4, !dbg !1611
  br label %return, !dbg !1611

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #2, !dbg !1612
  %5 = load i32, i32* %call2, align 4, !dbg !1612
  %cmp3 = icmp ne i32 %5, 22, !dbg !1614
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !1615

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #2, !dbg !1616
  %6 = load i32, i32* %call5, align 4, !dbg !1616
  %sub = sub nsw i32 0, %6, !dbg !1617
  store i32 %sub, i32* %retval, align 4, !dbg !1618
  br label %return, !dbg !1618

if.end6:                                          ; preds = %if.end
  %7 = load i32, i32* %domain.addr, align 4, !dbg !1619
  %8 = load i32, i32* %type.addr, align 4, !dbg !1620
  %9 = load i32, i32* %protocol.addr, align 4, !dbg !1621
  %call7 = call i32 @socket(i32 %7, i32 %8, i32 %9) #9, !dbg !1622
  store i32 %call7, i32* %sockfd, align 4, !dbg !1623
  %10 = load i32, i32* %sockfd, align 4, !dbg !1624
  %cmp8 = icmp eq i32 %10, -1, !dbg !1626
  br i1 %cmp8, label %if.then9, label %if.end12, !dbg !1627

if.then9:                                         ; preds = %if.end6
  %call10 = call i32* @__errno_location() #2, !dbg !1628
  %11 = load i32, i32* %call10, align 4, !dbg !1628
  %sub11 = sub nsw i32 0, %11, !dbg !1629
  store i32 %sub11, i32* %retval, align 4, !dbg !1630
  br label %return, !dbg !1630

if.end12:                                         ; preds = %if.end6
  %12 = load i32, i32* %sockfd, align 4, !dbg !1631
  %call13 = call i32 @uv__nonblock_ioctl(i32 %12, i32 1), !dbg !1632
  store i32 %call13, i32* %err, align 4, !dbg !1633
  %13 = load i32, i32* %err, align 4, !dbg !1634
  %cmp14 = icmp eq i32 %13, 0, !dbg !1636
  br i1 %cmp14, label %if.then15, label %if.end17, !dbg !1637

if.then15:                                        ; preds = %if.end12
  %14 = load i32, i32* %sockfd, align 4, !dbg !1638
  %call16 = call i32 @uv__cloexec_ioctl(i32 %14, i32 1), !dbg !1639
  store i32 %call16, i32* %err, align 4, !dbg !1640
  br label %if.end17, !dbg !1641

if.end17:                                         ; preds = %if.then15, %if.end12
  %15 = load i32, i32* %err, align 4, !dbg !1642
  %tobool = icmp ne i32 %15, 0, !dbg !1642
  br i1 %tobool, label %if.then18, label %if.end20, !dbg !1644

if.then18:                                        ; preds = %if.end17
  %16 = load i32, i32* %sockfd, align 4, !dbg !1645
  %call19 = call i32 @uv__close(i32 %16), !dbg !1647
  %17 = load i32, i32* %err, align 4, !dbg !1648
  store i32 %17, i32* %retval, align 4, !dbg !1649
  br label %return, !dbg !1649

if.end20:                                         ; preds = %if.end17
  %18 = load i32, i32* %sockfd, align 4, !dbg !1650
  store i32 %18, i32* %retval, align 4, !dbg !1651
  br label %return, !dbg !1651

return:                                           ; preds = %if.end20, %if.then18, %if.then9, %if.then4, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !1652
  ret i32 %19, !dbg !1652
}

; Function Attrs: nounwind
declare i32 @socket(i32, i32, i32) #4

; Function Attrs: nounwind uwtable
define i32 @uv__nonblock_ioctl(i32 %fd, i32 %set) #0 !dbg !1006 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %set.addr = alloca i32, align 4
  %r = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1653, metadata !1145), !dbg !1654
  store i32 %set, i32* %set.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %set.addr, metadata !1655, metadata !1145), !dbg !1656
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1657, metadata !1145), !dbg !1658
  br label %do.body, !dbg !1659

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1660
  %call = call i32 (i32, i64, ...) @ioctl(i32 %0, i64 21537, i32* %set.addr) #9, !dbg !1661
  store i32 %call, i32* %r, align 4, !dbg !1662
  br label %do.cond, !dbg !1663

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !1664
  %cmp = icmp eq i32 %1, -1, !dbg !1665
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1666

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #2, !dbg !1667
  %2 = load i32, i32* %call1, align 4, !dbg !1667
  %cmp2 = icmp eq i32 %2, 4, !dbg !1669
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !1670

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !1671
  %tobool = icmp ne i32 %4, 0, !dbg !1671
  br i1 %tobool, label %if.then, label %if.end, !dbg !1673

if.then:                                          ; preds = %do.end
  %call3 = call i32* @__errno_location() #2, !dbg !1674
  %5 = load i32, i32* %call3, align 4, !dbg !1674
  %sub = sub nsw i32 0, %5, !dbg !1675
  store i32 %sub, i32* %retval, align 4, !dbg !1676
  br label %return, !dbg !1676

if.end:                                           ; preds = %do.end
  store i32 0, i32* %retval, align 4, !dbg !1677
  br label %return, !dbg !1677

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !1678
  ret i32 %6, !dbg !1678
}

; Function Attrs: nounwind uwtable
define i32 @uv__cloexec_ioctl(i32 %fd, i32 %set) #0 !dbg !1009 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %set.addr = alloca i32, align 4
  %r = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1679, metadata !1145), !dbg !1680
  store i32 %set, i32* %set.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %set.addr, metadata !1681, metadata !1145), !dbg !1682
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1683, metadata !1145), !dbg !1684
  br label %do.body, !dbg !1685

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1686
  %1 = load i32, i32* %set.addr, align 4, !dbg !1687
  %tobool = icmp ne i32 %1, 0, !dbg !1687
  %cond = select i1 %tobool, i32 21585, i32 21584, !dbg !1687
  %conv = sext i32 %cond to i64, !dbg !1687
  %call = call i32 (i32, i64, ...) @ioctl(i32 %0, i64 %conv) #9, !dbg !1688
  store i32 %call, i32* %r, align 4, !dbg !1689
  br label %do.cond, !dbg !1690

do.cond:                                          ; preds = %do.body
  %2 = load i32, i32* %r, align 4, !dbg !1691
  %cmp = icmp eq i32 %2, -1, !dbg !1692
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1693

land.rhs:                                         ; preds = %do.cond
  %call2 = call i32* @__errno_location() #2, !dbg !1694
  %3 = load i32, i32* %call2, align 4, !dbg !1694
  %cmp3 = icmp eq i32 %3, 4, !dbg !1696
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %4 = phi i1 [ false, %do.cond ], [ %cmp3, %land.rhs ]
  br i1 %4, label %do.body, label %do.end, !dbg !1697

do.end:                                           ; preds = %land.end
  %5 = load i32, i32* %r, align 4, !dbg !1698
  %tobool5 = icmp ne i32 %5, 0, !dbg !1698
  br i1 %tobool5, label %if.then, label %if.end, !dbg !1700

if.then:                                          ; preds = %do.end
  %call6 = call i32* @__errno_location() #2, !dbg !1701
  %6 = load i32, i32* %call6, align 4, !dbg !1701
  %sub = sub nsw i32 0, %6, !dbg !1702
  store i32 %sub, i32* %retval, align 4, !dbg !1703
  br label %return, !dbg !1703

if.end:                                           ; preds = %do.end
  store i32 0, i32* %retval, align 4, !dbg !1704
  br label %return, !dbg !1704

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1705
  ret i32 %7, !dbg !1705
}

; Function Attrs: nounwind uwtable
define i32 @uv__close(i32 %fd) #0 !dbg !1005 {
entry:
  %fd.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1706, metadata !1145), !dbg !1707
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1708
  %cmp = icmp sgt i32 %0, 2, !dbg !1708
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1708

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1709

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 519, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @__PRETTY_FUNCTION__.uv__close, i32 0, i32 0)) #8, !dbg !1711
  unreachable, !dbg !1711
                                                  ; No predecessors!
  br label %cond.end, !dbg !1713

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %fd.addr, align 4, !dbg !1715
  %call = call i32 @uv__close_nocheckstdio(i32 %2), !dbg !1716
  ret i32 %call, !dbg !1717
}

; Function Attrs: nounwind uwtable
define %struct._IO_FILE* @uv__open_file(i8* %path) #0 !dbg !946 {
entry:
  %retval = alloca %struct._IO_FILE*, align 8
  %path.addr = alloca i8*, align 8
  %fd = alloca i32, align 4
  %fp = alloca %struct._IO_FILE*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1718, metadata !1145), !dbg !1719
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1720, metadata !1145), !dbg !1721
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fp, metadata !1722, metadata !1145), !dbg !1723
  %0 = load i8*, i8** %path.addr, align 8, !dbg !1724
  %call = call i32 @uv__open_cloexec(i8* %0, i32 0), !dbg !1725
  store i32 %call, i32* %fd, align 4, !dbg !1726
  %1 = load i32, i32* %fd, align 4, !dbg !1727
  %cmp = icmp slt i32 %1, 0, !dbg !1729
  br i1 %cmp, label %if.then, label %if.end, !dbg !1730

if.then:                                          ; preds = %entry
  store %struct._IO_FILE* null, %struct._IO_FILE** %retval, align 8, !dbg !1731
  br label %return, !dbg !1731

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %fd, align 4, !dbg !1732
  %call1 = call %struct._IO_FILE* @fdopen(i32 %2, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0)) #9, !dbg !1733
  store %struct._IO_FILE* %call1, %struct._IO_FILE** %fp, align 8, !dbg !1734
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !1735
  %cmp2 = icmp eq %struct._IO_FILE* %3, null, !dbg !1737
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !1738

if.then3:                                         ; preds = %if.end
  %4 = load i32, i32* %fd, align 4, !dbg !1739
  %call4 = call i32 @uv__close(i32 %4), !dbg !1740
  br label %if.end5, !dbg !1740

if.end5:                                          ; preds = %if.then3, %if.end
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !1741
  store %struct._IO_FILE* %5, %struct._IO_FILE** %retval, align 8, !dbg !1742
  br label %return, !dbg !1742

return:                                           ; preds = %if.end5, %if.then
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** %retval, align 8, !dbg !1743
  ret %struct._IO_FILE* %6, !dbg !1743
}

; Function Attrs: nounwind uwtable
define i32 @uv__open_cloexec(i8* %path, i32 %flags) #0 !dbg !1091 {
entry:
  %retval = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %fd = alloca i32, align 4
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1744, metadata !1145), !dbg !1745
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1746, metadata !1145), !dbg !1747
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1748, metadata !1145), !dbg !1749
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1750, metadata !1145), !dbg !1751
  %0 = load i32, i32* @uv__open_cloexec.no_cloexec, align 4, !dbg !1752
  %tobool = icmp ne i32 %0, 0, !dbg !1752
  br i1 %tobool, label %if.end7, label %if.then, !dbg !1754

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %path.addr, align 8, !dbg !1755
  %2 = load i32, i32* %flags.addr, align 4, !dbg !1757
  %or = or i32 %2, 524288, !dbg !1758
  %call = call i32 (i8*, i32, ...) @open64(i8* %1, i32 %or), !dbg !1759
  store i32 %call, i32* %fd, align 4, !dbg !1760
  %3 = load i32, i32* %fd, align 4, !dbg !1761
  %cmp = icmp ne i32 %3, -1, !dbg !1763
  br i1 %cmp, label %if.then1, label %if.end, !dbg !1764

if.then1:                                         ; preds = %if.then
  %4 = load i32, i32* %fd, align 4, !dbg !1765
  store i32 %4, i32* %retval, align 4, !dbg !1766
  br label %return, !dbg !1766

if.end:                                           ; preds = %if.then
  %call2 = call i32* @__errno_location() #2, !dbg !1767
  %5 = load i32, i32* %call2, align 4, !dbg !1767
  %cmp3 = icmp ne i32 %5, 22, !dbg !1769
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !1770

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #2, !dbg !1771
  %6 = load i32, i32* %call5, align 4, !dbg !1771
  %sub = sub nsw i32 0, %6, !dbg !1772
  store i32 %sub, i32* %retval, align 4, !dbg !1773
  br label %return, !dbg !1773

if.end6:                                          ; preds = %if.end
  store i32 1, i32* @uv__open_cloexec.no_cloexec, align 4, !dbg !1774
  br label %if.end7, !dbg !1775

if.end7:                                          ; preds = %if.end6, %entry
  %7 = load i8*, i8** %path.addr, align 8, !dbg !1776
  %8 = load i32, i32* %flags.addr, align 4, !dbg !1777
  %call8 = call i32 (i8*, i32, ...) @open64(i8* %7, i32 %8), !dbg !1778
  store i32 %call8, i32* %fd, align 4, !dbg !1779
  %9 = load i32, i32* %fd, align 4, !dbg !1780
  %cmp9 = icmp eq i32 %9, -1, !dbg !1782
  br i1 %cmp9, label %if.then10, label %if.end13, !dbg !1783

if.then10:                                        ; preds = %if.end7
  %call11 = call i32* @__errno_location() #2, !dbg !1784
  %10 = load i32, i32* %call11, align 4, !dbg !1784
  %sub12 = sub nsw i32 0, %10, !dbg !1785
  store i32 %sub12, i32* %retval, align 4, !dbg !1786
  br label %return, !dbg !1786

if.end13:                                         ; preds = %if.end7
  %11 = load i32, i32* %fd, align 4, !dbg !1787
  %call14 = call i32 @uv__cloexec_ioctl(i32 %11, i32 1), !dbg !1788
  store i32 %call14, i32* %err, align 4, !dbg !1789
  %12 = load i32, i32* %err, align 4, !dbg !1790
  %tobool15 = icmp ne i32 %12, 0, !dbg !1790
  br i1 %tobool15, label %if.then16, label %if.end18, !dbg !1792

if.then16:                                        ; preds = %if.end13
  %13 = load i32, i32* %fd, align 4, !dbg !1793
  %call17 = call i32 @uv__close(i32 %13), !dbg !1795
  %14 = load i32, i32* %err, align 4, !dbg !1796
  store i32 %14, i32* %retval, align 4, !dbg !1797
  br label %return, !dbg !1797

if.end18:                                         ; preds = %if.end13
  %15 = load i32, i32* %fd, align 4, !dbg !1798
  store i32 %15, i32* %retval, align 4, !dbg !1799
  br label %return, !dbg !1799

return:                                           ; preds = %if.end18, %if.then16, %if.then10, %if.then4, %if.then1
  %16 = load i32, i32* %retval, align 4, !dbg !1800
  ret i32 %16, !dbg !1800
}

; Function Attrs: nounwind
declare %struct._IO_FILE* @fdopen(i32, i8*) #4

; Function Attrs: nounwind uwtable
define i32 @uv__accept(i32 %sockfd) #0 !dbg !1001 {
entry:
  %retval = alloca i32, align 4
  %sockfd.addr = alloca i32, align 4
  %peerfd = alloca i32, align 4
  %err = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !1801, metadata !1145), !dbg !1802
  call void @llvm.dbg.declare(metadata i32* %peerfd, metadata !1803, metadata !1145), !dbg !1804
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1805, metadata !1145), !dbg !1806
  %0 = load i32, i32* %sockfd.addr, align 4, !dbg !1807
  %cmp = icmp sge i32 %0, 0, !dbg !1807
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1807

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1808

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 452, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @__PRETTY_FUNCTION__.uv__accept, i32 0, i32 0)) #8, !dbg !1810
  unreachable, !dbg !1810
                                                  ; No predecessors!
  br label %cond.end, !dbg !1812

cond.end:                                         ; preds = %1, %cond.true
  br label %while.body, !dbg !1814

while.body:                                       ; preds = %cond.end, %if.then6, %if.then18
  %2 = load i32, i32* @uv__accept.no_accept4, align 4, !dbg !1815
  %tobool = icmp ne i32 %2, 0, !dbg !1815
  br i1 %tobool, label %if.then, label %if.end, !dbg !1818

if.then:                                          ; preds = %while.body
  br label %skip, !dbg !1819

if.end:                                           ; preds = %while.body
  %3 = load i32, i32* %sockfd.addr, align 4, !dbg !1820
  %call = call i32 @uv__accept4(i32 %3, %struct.sockaddr* null, i32* null, i32 526336), !dbg !1821
  store i32 %call, i32* %peerfd, align 4, !dbg !1822
  %4 = load i32, i32* %peerfd, align 4, !dbg !1823
  %cmp1 = icmp ne i32 %4, -1, !dbg !1825
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1826

if.then2:                                         ; preds = %if.end
  %5 = load i32, i32* %peerfd, align 4, !dbg !1827
  store i32 %5, i32* %retval, align 4, !dbg !1828
  br label %return, !dbg !1828

if.end3:                                          ; preds = %if.end
  %call4 = call i32* @__errno_location() #2, !dbg !1829
  %6 = load i32, i32* %call4, align 4, !dbg !1829
  %cmp5 = icmp eq i32 %6, 4, !dbg !1831
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1832

if.then6:                                         ; preds = %if.end3
  br label %while.body, !dbg !1833

if.end7:                                          ; preds = %if.end3
  %call8 = call i32* @__errno_location() #2, !dbg !1834
  %7 = load i32, i32* %call8, align 4, !dbg !1834
  %cmp9 = icmp ne i32 %7, 38, !dbg !1836
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !1837

if.then10:                                        ; preds = %if.end7
  %call11 = call i32* @__errno_location() #2, !dbg !1838
  %8 = load i32, i32* %call11, align 4, !dbg !1838
  %sub = sub nsw i32 0, %8, !dbg !1839
  store i32 %sub, i32* %retval, align 4, !dbg !1840
  br label %return, !dbg !1840

if.end12:                                         ; preds = %if.end7
  store i32 1, i32* @uv__accept.no_accept4, align 4, !dbg !1841
  br label %skip, !dbg !1842

skip:                                             ; preds = %if.end12, %if.then
  %9 = load i32, i32* %sockfd.addr, align 4, !dbg !1843
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !1844
  store %struct.sockaddr* null, %struct.sockaddr** %__sockaddr__, align 8, !dbg !1844
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !1845
  %10 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !1845
  %call13 = call i32 @accept(i32 %9, %struct.sockaddr* %10, i32* null), !dbg !1845
  store i32 %call13, i32* %peerfd, align 4, !dbg !1846
  %11 = load i32, i32* %peerfd, align 4, !dbg !1847
  %cmp14 = icmp eq i32 %11, -1, !dbg !1849
  br i1 %cmp14, label %if.then15, label %if.end22, !dbg !1850

if.then15:                                        ; preds = %skip
  %call16 = call i32* @__errno_location() #2, !dbg !1851
  %12 = load i32, i32* %call16, align 4, !dbg !1851
  %cmp17 = icmp eq i32 %12, 4, !dbg !1854
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !1855

if.then18:                                        ; preds = %if.then15
  br label %while.body, !dbg !1856

if.end19:                                         ; preds = %if.then15
  %call20 = call i32* @__errno_location() #2, !dbg !1857
  %13 = load i32, i32* %call20, align 4, !dbg !1857
  %sub21 = sub nsw i32 0, %13, !dbg !1858
  store i32 %sub21, i32* %retval, align 4, !dbg !1859
  br label %return, !dbg !1859

if.end22:                                         ; preds = %skip
  %14 = load i32, i32* %peerfd, align 4, !dbg !1860
  %call23 = call i32 @uv__cloexec_ioctl(i32 %14, i32 1), !dbg !1861
  store i32 %call23, i32* %err, align 4, !dbg !1862
  %15 = load i32, i32* %err, align 4, !dbg !1863
  %cmp24 = icmp eq i32 %15, 0, !dbg !1865
  br i1 %cmp24, label %if.then25, label %if.end27, !dbg !1866

if.then25:                                        ; preds = %if.end22
  %16 = load i32, i32* %peerfd, align 4, !dbg !1867
  %call26 = call i32 @uv__nonblock_ioctl(i32 %16, i32 1), !dbg !1868
  store i32 %call26, i32* %err, align 4, !dbg !1869
  br label %if.end27, !dbg !1870

if.end27:                                         ; preds = %if.then25, %if.end22
  %17 = load i32, i32* %err, align 4, !dbg !1871
  %tobool28 = icmp ne i32 %17, 0, !dbg !1871
  br i1 %tobool28, label %if.then29, label %if.end31, !dbg !1873

if.then29:                                        ; preds = %if.end27
  %18 = load i32, i32* %peerfd, align 4, !dbg !1874
  %call30 = call i32 @uv__close(i32 %18), !dbg !1876
  %19 = load i32, i32* %err, align 4, !dbg !1877
  store i32 %19, i32* %retval, align 4, !dbg !1878
  br label %return, !dbg !1878

if.end31:                                         ; preds = %if.end27
  %20 = load i32, i32* %peerfd, align 4, !dbg !1879
  store i32 %20, i32* %retval, align 4, !dbg !1880
  br label %return, !dbg !1880

return:                                           ; preds = %if.end31, %if.then29, %if.end19, %if.then10, %if.then2
  %21 = load i32, i32* %retval, align 4, !dbg !1881
  ret i32 %21, !dbg !1881
}

declare i32 @uv__accept4(i32, %struct.sockaddr*, i32*, i32) #1

declare i32 @accept(i32, %struct.sockaddr*, i32*) #1

; Function Attrs: nounwind uwtable
define i32 @uv__close_nocheckstdio(i32 %fd) #0 !dbg !1004 {
entry:
  %fd.addr = alloca i32, align 4
  %saved_errno = alloca i32, align 4
  %rc = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1882, metadata !1145), !dbg !1883
  call void @llvm.dbg.declare(metadata i32* %saved_errno, metadata !1884, metadata !1145), !dbg !1885
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !1886, metadata !1145), !dbg !1887
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1888
  %cmp = icmp sgt i32 %0, -1, !dbg !1888
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1888

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1889

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 503, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.uv__close_nocheckstdio, i32 0, i32 0)) #8, !dbg !1891
  unreachable, !dbg !1891
                                                  ; No predecessors!
  br label %cond.end, !dbg !1893

cond.end:                                         ; preds = %1, %cond.true
  %call = call i32* @__errno_location() #2, !dbg !1895
  %2 = load i32, i32* %call, align 4, !dbg !1895
  store i32 %2, i32* %saved_errno, align 4, !dbg !1896
  %3 = load i32, i32* %fd.addr, align 4, !dbg !1897
  %call1 = call i32 @close(i32 %3), !dbg !1898
  store i32 %call1, i32* %rc, align 4, !dbg !1899
  %4 = load i32, i32* %rc, align 4, !dbg !1900
  %cmp2 = icmp eq i32 %4, -1, !dbg !1902
  br i1 %cmp2, label %if.then, label %if.end8, !dbg !1903

if.then:                                          ; preds = %cond.end
  %call3 = call i32* @__errno_location() #2, !dbg !1904
  %5 = load i32, i32* %call3, align 4, !dbg !1904
  %sub = sub nsw i32 0, %5, !dbg !1906
  store i32 %sub, i32* %rc, align 4, !dbg !1907
  %6 = load i32, i32* %rc, align 4, !dbg !1908
  %cmp4 = icmp eq i32 %6, -4, !dbg !1910
  br i1 %cmp4, label %if.then6, label %lor.lhs.false, !dbg !1911

lor.lhs.false:                                    ; preds = %if.then
  %7 = load i32, i32* %rc, align 4, !dbg !1912
  %cmp5 = icmp eq i32 %7, -115, !dbg !1914
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !1915

if.then6:                                         ; preds = %lor.lhs.false, %if.then
  store i32 0, i32* %rc, align 4, !dbg !1916
  br label %if.end, !dbg !1917

if.end:                                           ; preds = %if.then6, %lor.lhs.false
  %8 = load i32, i32* %saved_errno, align 4, !dbg !1918
  %call7 = call i32* @__errno_location() #2, !dbg !1919
  store i32 %8, i32* %call7, align 4, !dbg !1920
  br label %if.end8, !dbg !1921

if.end8:                                          ; preds = %if.end, %cond.end
  %9 = load i32, i32* %rc, align 4, !dbg !1922
  ret i32 %9, !dbg !1923
}

declare i32 @close(i32) #1

; Function Attrs: nounwind
declare i32 @ioctl(i32, i64, ...) #4

; Function Attrs: nounwind uwtable
define i32 @uv__nonblock_fcntl(i32 %fd, i32 %set) #0 !dbg !1010 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %set.addr = alloca i32, align 4
  %flags = alloca i32, align 4
  %r = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1924, metadata !1145), !dbg !1925
  store i32 %set, i32* %set.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %set.addr, metadata !1926, metadata !1145), !dbg !1927
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !1928, metadata !1145), !dbg !1929
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1930, metadata !1145), !dbg !1931
  br label %do.body, !dbg !1932

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1933
  %call = call i32 (i32, i32, ...) @fcntl(i32 %0, i32 3), !dbg !1934
  store i32 %call, i32* %r, align 4, !dbg !1935
  br label %do.cond, !dbg !1936

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !1937
  %cmp = icmp eq i32 %1, -1, !dbg !1938
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1939

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #2, !dbg !1940
  %2 = load i32, i32* %call1, align 4, !dbg !1940
  %cmp2 = icmp eq i32 %2, 4, !dbg !1942
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !1943

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !1944
  %cmp3 = icmp eq i32 %4, -1, !dbg !1946
  br i1 %cmp3, label %if.then, label %if.end, !dbg !1947

if.then:                                          ; preds = %do.end
  %call4 = call i32* @__errno_location() #2, !dbg !1948
  %5 = load i32, i32* %call4, align 4, !dbg !1948
  %sub = sub nsw i32 0, %5, !dbg !1949
  store i32 %sub, i32* %retval, align 4, !dbg !1950
  br label %return, !dbg !1950

if.end:                                           ; preds = %do.end
  %6 = load i32, i32* %r, align 4, !dbg !1951
  %and = and i32 %6, 2048, !dbg !1953
  %tobool = icmp ne i32 %and, 0, !dbg !1954
  %lnot = xor i1 %tobool, true, !dbg !1954
  %lnot5 = xor i1 %lnot, true, !dbg !1955
  %lnot.ext = zext i1 %lnot5 to i32, !dbg !1955
  %7 = load i32, i32* %set.addr, align 4, !dbg !1956
  %tobool6 = icmp ne i32 %7, 0, !dbg !1957
  %lnot7 = xor i1 %tobool6, true, !dbg !1957
  %lnot9 = xor i1 %lnot7, true, !dbg !1958
  %lnot.ext10 = zext i1 %lnot9 to i32, !dbg !1958
  %cmp11 = icmp eq i32 %lnot.ext, %lnot.ext10, !dbg !1959
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1960

if.then12:                                        ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1961
  br label %return, !dbg !1961

if.end13:                                         ; preds = %if.end
  %8 = load i32, i32* %set.addr, align 4, !dbg !1962
  %tobool14 = icmp ne i32 %8, 0, !dbg !1962
  br i1 %tobool14, label %if.then15, label %if.else, !dbg !1964

if.then15:                                        ; preds = %if.end13
  %9 = load i32, i32* %r, align 4, !dbg !1965
  %or = or i32 %9, 2048, !dbg !1966
  store i32 %or, i32* %flags, align 4, !dbg !1967
  br label %if.end17, !dbg !1968

if.else:                                          ; preds = %if.end13
  %10 = load i32, i32* %r, align 4, !dbg !1969
  %and16 = and i32 %10, -2049, !dbg !1970
  store i32 %and16, i32* %flags, align 4, !dbg !1971
  br label %if.end17

if.end17:                                         ; preds = %if.else, %if.then15
  br label %do.body18, !dbg !1972

do.body18:                                        ; preds = %land.end25, %if.end17
  %11 = load i32, i32* %fd.addr, align 4, !dbg !1973
  %12 = load i32, i32* %flags, align 4, !dbg !1974
  %call19 = call i32 (i32, i32, ...) @fcntl(i32 %11, i32 4, i32 %12), !dbg !1975
  store i32 %call19, i32* %r, align 4, !dbg !1976
  br label %do.cond20, !dbg !1977

do.cond20:                                        ; preds = %do.body18
  %13 = load i32, i32* %r, align 4, !dbg !1978
  %cmp21 = icmp eq i32 %13, -1, !dbg !1979
  br i1 %cmp21, label %land.rhs22, label %land.end25, !dbg !1980

land.rhs22:                                       ; preds = %do.cond20
  %call23 = call i32* @__errno_location() #2, !dbg !1981
  %14 = load i32, i32* %call23, align 4, !dbg !1981
  %cmp24 = icmp eq i32 %14, 4, !dbg !1982
  br label %land.end25

land.end25:                                       ; preds = %land.rhs22, %do.cond20
  %15 = phi i1 [ false, %do.cond20 ], [ %cmp24, %land.rhs22 ]
  br i1 %15, label %do.body18, label %do.end26, !dbg !1983

do.end26:                                         ; preds = %land.end25
  %16 = load i32, i32* %r, align 4, !dbg !1984
  %tobool27 = icmp ne i32 %16, 0, !dbg !1984
  br i1 %tobool27, label %if.then28, label %if.end31, !dbg !1986

if.then28:                                        ; preds = %do.end26
  %call29 = call i32* @__errno_location() #2, !dbg !1987
  %17 = load i32, i32* %call29, align 4, !dbg !1987
  %sub30 = sub nsw i32 0, %17, !dbg !1988
  store i32 %sub30, i32* %retval, align 4, !dbg !1989
  br label %return, !dbg !1989

if.end31:                                         ; preds = %do.end26
  store i32 0, i32* %retval, align 4, !dbg !1990
  br label %return, !dbg !1990

return:                                           ; preds = %if.end31, %if.then28, %if.then12, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !1991
  ret i32 %18, !dbg !1991
}

declare i32 @fcntl(i32, i32, ...) #1

; Function Attrs: nounwind uwtable
define i32 @uv__cloexec_fcntl(i32 %fd, i32 %set) #0 !dbg !1011 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %set.addr = alloca i32, align 4
  %flags = alloca i32, align 4
  %r = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1992, metadata !1145), !dbg !1993
  store i32 %set, i32* %set.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %set.addr, metadata !1994, metadata !1145), !dbg !1995
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !1996, metadata !1145), !dbg !1997
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1998, metadata !1145), !dbg !1999
  br label %do.body, !dbg !2000

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* %fd.addr, align 4, !dbg !2001
  %call = call i32 (i32, i32, ...) @fcntl(i32 %0, i32 1), !dbg !2002
  store i32 %call, i32* %r, align 4, !dbg !2003
  br label %do.cond, !dbg !2004

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !2005
  %cmp = icmp eq i32 %1, -1, !dbg !2006
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2007

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #2, !dbg !2008
  %2 = load i32, i32* %call1, align 4, !dbg !2008
  %cmp2 = icmp eq i32 %2, 4, !dbg !2010
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !2011

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !2012
  %cmp3 = icmp eq i32 %4, -1, !dbg !2014
  br i1 %cmp3, label %if.then, label %if.end, !dbg !2015

if.then:                                          ; preds = %do.end
  %call4 = call i32* @__errno_location() #2, !dbg !2016
  %5 = load i32, i32* %call4, align 4, !dbg !2016
  %sub = sub nsw i32 0, %5, !dbg !2017
  store i32 %sub, i32* %retval, align 4, !dbg !2018
  br label %return, !dbg !2018

if.end:                                           ; preds = %do.end
  %6 = load i32, i32* %r, align 4, !dbg !2019
  %and = and i32 %6, 1, !dbg !2021
  %tobool = icmp ne i32 %and, 0, !dbg !2022
  %lnot = xor i1 %tobool, true, !dbg !2022
  %lnot5 = xor i1 %lnot, true, !dbg !2023
  %lnot.ext = zext i1 %lnot5 to i32, !dbg !2023
  %7 = load i32, i32* %set.addr, align 4, !dbg !2024
  %tobool6 = icmp ne i32 %7, 0, !dbg !2025
  %lnot7 = xor i1 %tobool6, true, !dbg !2025
  %lnot9 = xor i1 %lnot7, true, !dbg !2026
  %lnot.ext10 = zext i1 %lnot9 to i32, !dbg !2026
  %cmp11 = icmp eq i32 %lnot.ext, %lnot.ext10, !dbg !2027
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !2028

if.then12:                                        ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !2029
  br label %return, !dbg !2029

if.end13:                                         ; preds = %if.end
  %8 = load i32, i32* %set.addr, align 4, !dbg !2030
  %tobool14 = icmp ne i32 %8, 0, !dbg !2030
  br i1 %tobool14, label %if.then15, label %if.else, !dbg !2032

if.then15:                                        ; preds = %if.end13
  %9 = load i32, i32* %r, align 4, !dbg !2033
  %or = or i32 %9, 1, !dbg !2034
  store i32 %or, i32* %flags, align 4, !dbg !2035
  br label %if.end17, !dbg !2036

if.else:                                          ; preds = %if.end13
  %10 = load i32, i32* %r, align 4, !dbg !2037
  %and16 = and i32 %10, -2, !dbg !2038
  store i32 %and16, i32* %flags, align 4, !dbg !2039
  br label %if.end17

if.end17:                                         ; preds = %if.else, %if.then15
  br label %do.body18, !dbg !2040

do.body18:                                        ; preds = %land.end25, %if.end17
  %11 = load i32, i32* %fd.addr, align 4, !dbg !2041
  %12 = load i32, i32* %flags, align 4, !dbg !2042
  %call19 = call i32 (i32, i32, ...) @fcntl(i32 %11, i32 2, i32 %12), !dbg !2043
  store i32 %call19, i32* %r, align 4, !dbg !2044
  br label %do.cond20, !dbg !2045

do.cond20:                                        ; preds = %do.body18
  %13 = load i32, i32* %r, align 4, !dbg !2046
  %cmp21 = icmp eq i32 %13, -1, !dbg !2047
  br i1 %cmp21, label %land.rhs22, label %land.end25, !dbg !2048

land.rhs22:                                       ; preds = %do.cond20
  %call23 = call i32* @__errno_location() #2, !dbg !2049
  %14 = load i32, i32* %call23, align 4, !dbg !2049
  %cmp24 = icmp eq i32 %14, 4, !dbg !2050
  br label %land.end25

land.end25:                                       ; preds = %land.rhs22, %do.cond20
  %15 = phi i1 [ false, %do.cond20 ], [ %cmp24, %land.rhs22 ]
  br i1 %15, label %do.body18, label %do.end26, !dbg !2051

do.end26:                                         ; preds = %land.end25
  %16 = load i32, i32* %r, align 4, !dbg !2052
  %tobool27 = icmp ne i32 %16, 0, !dbg !2052
  br i1 %tobool27, label %if.then28, label %if.end31, !dbg !2054

if.then28:                                        ; preds = %do.end26
  %call29 = call i32* @__errno_location() #2, !dbg !2055
  %17 = load i32, i32* %call29, align 4, !dbg !2055
  %sub30 = sub nsw i32 0, %17, !dbg !2056
  store i32 %sub30, i32* %retval, align 4, !dbg !2057
  br label %return, !dbg !2057

if.end31:                                         ; preds = %do.end26
  store i32 0, i32* %retval, align 4, !dbg !2058
  br label %return, !dbg !2058

return:                                           ; preds = %if.end31, %if.then28, %if.then12, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !2059
  ret i32 %18, !dbg !2059
}

; Function Attrs: nounwind uwtable
define i32 @uv__dup(i32 %fd) #0 !dbg !1012 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2060, metadata !1145), !dbg !2061
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2062, metadata !1145), !dbg !2063
  %0 = load i32, i32* %fd.addr, align 4, !dbg !2064
  %call = call i32 @dup(i32 %0) #9, !dbg !2065
  store i32 %call, i32* %fd.addr, align 4, !dbg !2066
  %1 = load i32, i32* %fd.addr, align 4, !dbg !2067
  %cmp = icmp eq i32 %1, -1, !dbg !2069
  br i1 %cmp, label %if.then, label %if.end, !dbg !2070

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #2, !dbg !2071
  %2 = load i32, i32* %call1, align 4, !dbg !2071
  %sub = sub nsw i32 0, %2, !dbg !2072
  store i32 %sub, i32* %retval, align 4, !dbg !2073
  br label %return, !dbg !2073

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %fd.addr, align 4, !dbg !2074
  %call2 = call i32 @uv__cloexec_ioctl(i32 %3, i32 1), !dbg !2075
  store i32 %call2, i32* %err, align 4, !dbg !2076
  %4 = load i32, i32* %err, align 4, !dbg !2077
  %tobool = icmp ne i32 %4, 0, !dbg !2077
  br i1 %tobool, label %if.then3, label %if.end5, !dbg !2079

if.then3:                                         ; preds = %if.end
  %5 = load i32, i32* %fd.addr, align 4, !dbg !2080
  %call4 = call i32 @uv__close(i32 %5), !dbg !2082
  %6 = load i32, i32* %err, align 4, !dbg !2083
  store i32 %6, i32* %retval, align 4, !dbg !2084
  br label %return, !dbg !2084

if.end5:                                          ; preds = %if.end
  %7 = load i32, i32* %fd.addr, align 4, !dbg !2085
  store i32 %7, i32* %retval, align 4, !dbg !2086
  br label %return, !dbg !2086

return:                                           ; preds = %if.end5, %if.then3, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2087
  ret i32 %8, !dbg !2087
}

; Function Attrs: nounwind
declare i32 @dup(i32) #4

; Function Attrs: nounwind uwtable
define i64 @uv__recvmsg(i32 %fd, %struct.msghdr* %msg, i32 %flags) #0 !dbg !1013 {
entry:
  %retval = alloca i64, align 8
  %fd.addr = alloca i32, align 4
  %msg.addr = alloca %struct.msghdr*, align 8
  %flags.addr = alloca i32, align 4
  %cmsg = alloca %struct.cmsghdr*, align 8
  %rc = alloca i64, align 8
  %pfd = alloca i32*, align 8
  %end = alloca i32*, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2088, metadata !1145), !dbg !2089
  store %struct.msghdr* %msg, %struct.msghdr** %msg.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.msghdr** %msg.addr, metadata !2090, metadata !1145), !dbg !2091
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !2092, metadata !1145), !dbg !2093
  call void @llvm.dbg.declare(metadata %struct.cmsghdr** %cmsg, metadata !2094, metadata !1145), !dbg !2095
  call void @llvm.dbg.declare(metadata i64* %rc, metadata !2096, metadata !1145), !dbg !2097
  call void @llvm.dbg.declare(metadata i32** %pfd, metadata !2098, metadata !1145), !dbg !2099
  call void @llvm.dbg.declare(metadata i32** %end, metadata !2100, metadata !1145), !dbg !2101
  %0 = load i32, i32* @uv__recvmsg.no_msg_cmsg_cloexec, align 4, !dbg !2102
  %cmp = icmp eq i32 %0, 0, !dbg !2104
  br i1 %cmp, label %if.then, label %if.else, !dbg !2105

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %fd.addr, align 4, !dbg !2106
  %2 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2108
  %3 = load i32, i32* %flags.addr, align 4, !dbg !2109
  %or = or i32 %3, 1073741824, !dbg !2110
  %call = call i64 @recvmsg(i32 %1, %struct.msghdr* %2, i32 %or), !dbg !2111
  store i64 %call, i64* %rc, align 8, !dbg !2112
  %4 = load i64, i64* %rc, align 8, !dbg !2113
  %cmp1 = icmp ne i64 %4, -1, !dbg !2115
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !2116

if.then2:                                         ; preds = %if.then
  %5 = load i64, i64* %rc, align 8, !dbg !2117
  store i64 %5, i64* %retval, align 8, !dbg !2118
  br label %return, !dbg !2118

if.end:                                           ; preds = %if.then
  %call3 = call i32* @__errno_location() #2, !dbg !2119
  %6 = load i32, i32* %call3, align 4, !dbg !2119
  %cmp4 = icmp ne i32 %6, 22, !dbg !2121
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !2122

if.then5:                                         ; preds = %if.end
  %call6 = call i32* @__errno_location() #2, !dbg !2123
  %7 = load i32, i32* %call6, align 4, !dbg !2123
  %sub = sub nsw i32 0, %7, !dbg !2124
  %conv = sext i32 %sub to i64, !dbg !2124
  store i64 %conv, i64* %retval, align 8, !dbg !2125
  br label %return, !dbg !2125

if.end7:                                          ; preds = %if.end
  %8 = load i32, i32* %fd.addr, align 4, !dbg !2126
  %9 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2127
  %10 = load i32, i32* %flags.addr, align 4, !dbg !2128
  %call8 = call i64 @recvmsg(i32 %8, %struct.msghdr* %9, i32 %10), !dbg !2129
  store i64 %call8, i64* %rc, align 8, !dbg !2130
  %11 = load i64, i64* %rc, align 8, !dbg !2131
  %cmp9 = icmp eq i64 %11, -1, !dbg !2133
  br i1 %cmp9, label %if.then11, label %if.end15, !dbg !2134

if.then11:                                        ; preds = %if.end7
  %call12 = call i32* @__errno_location() #2, !dbg !2135
  %12 = load i32, i32* %call12, align 4, !dbg !2135
  %sub13 = sub nsw i32 0, %12, !dbg !2136
  %conv14 = sext i32 %sub13 to i64, !dbg !2136
  store i64 %conv14, i64* %retval, align 8, !dbg !2137
  br label %return, !dbg !2137

if.end15:                                         ; preds = %if.end7
  store i32 1, i32* @uv__recvmsg.no_msg_cmsg_cloexec, align 4, !dbg !2138
  br label %if.end17, !dbg !2139

if.else:                                          ; preds = %entry
  %13 = load i32, i32* %fd.addr, align 4, !dbg !2140
  %14 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2142
  %15 = load i32, i32* %flags.addr, align 4, !dbg !2143
  %call16 = call i64 @recvmsg(i32 %13, %struct.msghdr* %14, i32 %15), !dbg !2144
  store i64 %call16, i64* %rc, align 8, !dbg !2145
  br label %if.end17

if.end17:                                         ; preds = %if.else, %if.end15
  %16 = load i64, i64* %rc, align 8, !dbg !2146
  %cmp18 = icmp eq i64 %16, -1, !dbg !2148
  br i1 %cmp18, label %if.then20, label %if.end24, !dbg !2149

if.then20:                                        ; preds = %if.end17
  %call21 = call i32* @__errno_location() #2, !dbg !2150
  %17 = load i32, i32* %call21, align 4, !dbg !2150
  %sub22 = sub nsw i32 0, %17, !dbg !2151
  %conv23 = sext i32 %sub22 to i64, !dbg !2151
  store i64 %conv23, i64* %retval, align 8, !dbg !2152
  br label %return, !dbg !2152

if.end24:                                         ; preds = %if.end17
  %18 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2153
  %msg_controllen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %18, i32 0, i32 5, !dbg !2155
  %19 = load i64, i64* %msg_controllen, align 8, !dbg !2155
  %cmp25 = icmp eq i64 %19, 0, !dbg !2156
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !2157

if.then27:                                        ; preds = %if.end24
  %20 = load i64, i64* %rc, align 8, !dbg !2158
  store i64 %20, i64* %retval, align 8, !dbg !2159
  br label %return, !dbg !2159

if.end28:                                         ; preds = %if.end24
  %21 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2160
  %msg_controllen29 = getelementptr inbounds %struct.msghdr, %struct.msghdr* %21, i32 0, i32 5, !dbg !2160
  %22 = load i64, i64* %msg_controllen29, align 8, !dbg !2160
  %cmp30 = icmp uge i64 %22, 16, !dbg !2160
  br i1 %cmp30, label %cond.true, label %cond.false, !dbg !2160

cond.true:                                        ; preds = %if.end28
  %23 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2162
  %msg_control = getelementptr inbounds %struct.msghdr, %struct.msghdr* %23, i32 0, i32 4, !dbg !2162
  %24 = load i8*, i8** %msg_control, align 8, !dbg !2162
  %25 = bitcast i8* %24 to %struct.cmsghdr*, !dbg !2162
  br label %cond.end, !dbg !2162

cond.false:                                       ; preds = %if.end28
  br label %cond.end, !dbg !2164

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %struct.cmsghdr* [ %25, %cond.true ], [ null, %cond.false ], !dbg !2166
  store %struct.cmsghdr* %cond, %struct.cmsghdr** %cmsg, align 8, !dbg !2168
  br label %for.cond, !dbg !2169

for.cond:                                         ; preds = %for.inc44, %cond.end
  %26 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !2170
  %cmp32 = icmp ne %struct.cmsghdr* %26, null, !dbg !2173
  br i1 %cmp32, label %for.body, label %for.end46, !dbg !2174

for.body:                                         ; preds = %for.cond
  %27 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !2175
  %cmsg_type = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %27, i32 0, i32 2, !dbg !2177
  %28 = load i32, i32* %cmsg_type, align 4, !dbg !2177
  %cmp34 = icmp eq i32 %28, 1, !dbg !2178
  br i1 %cmp34, label %if.then36, label %if.end43, !dbg !2179

if.then36:                                        ; preds = %for.body
  %29 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !2180
  %__cmsg_data = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %29, i32 0, i32 3, !dbg !2180
  %arraydecay = getelementptr inbounds [0 x i8], [0 x i8]* %__cmsg_data, i32 0, i32 0, !dbg !2180
  %30 = bitcast i8* %arraydecay to i32*, !dbg !2182
  store i32* %30, i32** %pfd, align 8, !dbg !2183
  %31 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !2184
  %32 = bitcast %struct.cmsghdr* %31 to i8*, !dbg !2185
  %33 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !2186
  %cmsg_len = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %33, i32 0, i32 0, !dbg !2187
  %34 = load i64, i64* %cmsg_len, align 8, !dbg !2187
  %add.ptr = getelementptr inbounds i8, i8* %32, i64 %34, !dbg !2188
  %35 = bitcast i8* %add.ptr to i32*, !dbg !2189
  store i32* %35, i32** %end, align 8, !dbg !2190
  br label %for.cond37, !dbg !2191

for.cond37:                                       ; preds = %for.inc, %if.then36
  %36 = load i32*, i32** %pfd, align 8, !dbg !2192
  %37 = load i32*, i32** %end, align 8, !dbg !2194
  %cmp38 = icmp ult i32* %36, %37, !dbg !2195
  br i1 %cmp38, label %for.body40, label %for.end, !dbg !2196

for.body40:                                       ; preds = %for.cond37
  %38 = load i32*, i32** %pfd, align 8, !dbg !2198
  %39 = load i32, i32* %38, align 4, !dbg !2199
  %call41 = call i32 @uv__cloexec_ioctl(i32 %39, i32 1), !dbg !2200
  br label %for.inc, !dbg !2200

for.inc:                                          ; preds = %for.body40
  %40 = load i32*, i32** %pfd, align 8, !dbg !2201
  %add.ptr42 = getelementptr inbounds i32, i32* %40, i64 1, !dbg !2201
  store i32* %add.ptr42, i32** %pfd, align 8, !dbg !2201
  br label %for.cond37, !dbg !2202

for.end:                                          ; preds = %for.cond37
  br label %if.end43, !dbg !2204

if.end43:                                         ; preds = %for.end, %for.body
  br label %for.inc44, !dbg !2205

for.inc44:                                        ; preds = %if.end43
  %41 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !2207
  %42 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !2207
  %call45 = call %struct.cmsghdr* @__cmsg_nxthdr(%struct.msghdr* %41, %struct.cmsghdr* %42) #9, !dbg !2207
  store %struct.cmsghdr* %call45, %struct.cmsghdr** %cmsg, align 8, !dbg !2209
  br label %for.cond, !dbg !2210

for.end46:                                        ; preds = %for.cond
  %43 = load i64, i64* %rc, align 8, !dbg !2211
  store i64 %43, i64* %retval, align 8, !dbg !2212
  br label %return, !dbg !2212

return:                                           ; preds = %for.end46, %if.then27, %if.then20, %if.then11, %if.then5, %if.then2
  %44 = load i64, i64* %retval, align 8, !dbg !2213
  ret i64 %44, !dbg !2213
}

declare i64 @recvmsg(i32, %struct.msghdr*, i32) #1

; Function Attrs: nounwind
declare %struct.cmsghdr* @__cmsg_nxthdr(%struct.msghdr*, %struct.cmsghdr*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_cwd(i8* %buffer, i64* %size) #0 !dbg !1034 {
entry:
  %retval = alloca i32, align 4
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !2214, metadata !1145), !dbg !2215
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !2216, metadata !1145), !dbg !2217
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !2218
  %cmp = icmp eq i8* %0, null, !dbg !2220
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2221

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64*, i64** %size.addr, align 8, !dbg !2222
  %cmp1 = icmp eq i64* %1, null, !dbg !2224
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2225

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !2226
  br label %return, !dbg !2226

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i8*, i8** %buffer.addr, align 8, !dbg !2227
  %3 = load i64*, i64** %size.addr, align 8, !dbg !2229
  %4 = load i64, i64* %3, align 8, !dbg !2230
  %call = call i8* @getcwd(i8* %2, i64 %4) #9, !dbg !2231
  %cmp2 = icmp eq i8* %call, null, !dbg !2232
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !2233

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__errno_location() #2, !dbg !2234
  %5 = load i32, i32* %call4, align 4, !dbg !2234
  %sub = sub nsw i32 0, %5, !dbg !2235
  store i32 %sub, i32* %retval, align 4, !dbg !2236
  br label %return, !dbg !2236

if.end5:                                          ; preds = %if.end
  %6 = load i8*, i8** %buffer.addr, align 8, !dbg !2237
  %call6 = call i64 @strlen(i8* %6) #10, !dbg !2238
  %7 = load i64*, i64** %size.addr, align 8, !dbg !2239
  store i64 %call6, i64* %7, align 8, !dbg !2240
  %8 = load i64*, i64** %size.addr, align 8, !dbg !2241
  %9 = load i64, i64* %8, align 8, !dbg !2243
  %cmp7 = icmp ugt i64 %9, 1, !dbg !2244
  br i1 %cmp7, label %land.lhs.true, label %if.end14, !dbg !2245

land.lhs.true:                                    ; preds = %if.end5
  %10 = load i64*, i64** %size.addr, align 8, !dbg !2246
  %11 = load i64, i64* %10, align 8, !dbg !2248
  %sub8 = sub i64 %11, 1, !dbg !2249
  %12 = load i8*, i8** %buffer.addr, align 8, !dbg !2250
  %arrayidx = getelementptr inbounds i8, i8* %12, i64 %sub8, !dbg !2250
  %13 = load i8, i8* %arrayidx, align 1, !dbg !2250
  %conv = sext i8 %13 to i32, !dbg !2250
  %cmp9 = icmp eq i32 %conv, 47, !dbg !2251
  br i1 %cmp9, label %if.then11, label %if.end14, !dbg !2252

if.then11:                                        ; preds = %land.lhs.true
  %14 = load i64*, i64** %size.addr, align 8, !dbg !2253
  %15 = load i64, i64* %14, align 8, !dbg !2255
  %sub12 = sub i64 %15, 1, !dbg !2256
  %16 = load i8*, i8** %buffer.addr, align 8, !dbg !2257
  %arrayidx13 = getelementptr inbounds i8, i8* %16, i64 %sub12, !dbg !2257
  store i8 0, i8* %arrayidx13, align 1, !dbg !2258
  %17 = load i64*, i64** %size.addr, align 8, !dbg !2259
  %18 = load i64, i64* %17, align 8, !dbg !2260
  %dec = add i64 %18, -1, !dbg !2260
  store i64 %dec, i64* %17, align 8, !dbg !2260
  br label %if.end14, !dbg !2261

if.end14:                                         ; preds = %if.then11, %land.lhs.true, %if.end5
  store i32 0, i32* %retval, align 4, !dbg !2262
  br label %return, !dbg !2262

return:                                           ; preds = %if.end14, %if.then3, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !2263
  ret i32 %19, !dbg !2263
}

; Function Attrs: nounwind
declare i8* @getcwd(i8*, i64) #4

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #6

; Function Attrs: nounwind uwtable
define i32 @uv_chdir(i8* %dir) #0 !dbg !1038 {
entry:
  %retval = alloca i32, align 4
  %dir.addr = alloca i8*, align 8
  store i8* %dir, i8** %dir.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dir.addr, metadata !2264, metadata !1145), !dbg !2265
  %0 = load i8*, i8** %dir.addr, align 8, !dbg !2266
  %call = call i32 @chdir(i8* %0) #9, !dbg !2268
  %tobool = icmp ne i32 %call, 0, !dbg !2268
  br i1 %tobool, label %if.then, label %if.end, !dbg !2269

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #2, !dbg !2270
  %1 = load i32, i32* %call1, align 4, !dbg !2270
  %sub = sub nsw i32 0, %1, !dbg !2271
  store i32 %sub, i32* %retval, align 4, !dbg !2272
  br label %return, !dbg !2272

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2273
  br label %return, !dbg !2273

return:                                           ; preds = %if.end, %if.then
  %2 = load i32, i32* %retval, align 4, !dbg !2274
  ret i32 %2, !dbg !2274
}

; Function Attrs: nounwind
declare i32 @chdir(i8*) #4

; Function Attrs: nounwind uwtable
define void @uv_disable_stdio_inheritance() #0 !dbg !1041 {
entry:
  %fd = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !2275, metadata !1145), !dbg !2276
  store i32 0, i32* %fd, align 4, !dbg !2277
  br label %for.cond, !dbg !2279

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %fd, align 4, !dbg !2280
  %call = call i32 @uv__cloexec_ioctl(i32 %0, i32 1), !dbg !2283
  %tobool = icmp ne i32 %call, 0, !dbg !2283
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !2284

land.lhs.true:                                    ; preds = %for.cond
  %1 = load i32, i32* %fd, align 4, !dbg !2285
  %cmp = icmp sgt i32 %1, 15, !dbg !2287
  br i1 %cmp, label %if.then, label %if.end, !dbg !2288

if.then:                                          ; preds = %land.lhs.true
  br label %for.end, !dbg !2289

if.end:                                           ; preds = %land.lhs.true, %for.cond
  br label %for.inc, !dbg !2290

for.inc:                                          ; preds = %if.end
  %2 = load i32, i32* %fd, align 4, !dbg !2292
  %inc = add nsw i32 %2, 1, !dbg !2292
  store i32 %inc, i32* %fd, align 4, !dbg !2292
  br label %for.cond, !dbg !2294

for.end:                                          ; preds = %if.then
  ret void, !dbg !2295
}

; Function Attrs: nounwind uwtable
define i32 @uv_fileno(%struct.uv_handle_s* %handle, i32* %fd) #0 !dbg !1042 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  %fd.addr = alloca i32*, align 8
  %fd_out = alloca i32, align 4
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !2296, metadata !1145), !dbg !2297
  store i32* %fd, i32** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fd.addr, metadata !2298, metadata !1145), !dbg !2299
  call void @llvm.dbg.declare(metadata i32* %fd_out, metadata !2300, metadata !1145), !dbg !2301
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2302
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 2, !dbg !2303
  %1 = load i32, i32* %type, align 8, !dbg !2303
  switch i32 %1, label %sw.default [
    i32 12, label %sw.bb
    i32 7, label %sw.bb
    i32 14, label %sw.bb
    i32 15, label %sw.bb2
    i32 8, label %sw.bb5
  ], !dbg !2304

sw.bb:                                            ; preds = %entry, %entry, %entry
  %2 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2305
  %3 = bitcast %struct.uv_handle_s* %2 to %struct.uv_stream_s*, !dbg !2305
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %3, i32 0, i32 13, !dbg !2305
  %fd1 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2305
  %4 = load i32, i32* %fd1, align 8, !dbg !2305
  store i32 %4, i32* %fd_out, align 4, !dbg !2307
  br label %sw.epilog, !dbg !2308

sw.bb2:                                           ; preds = %entry
  %5 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2309
  %6 = bitcast %struct.uv_handle_s* %5 to %struct.uv_udp_s*, !dbg !2310
  %io_watcher3 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %6, i32 0, i32 12, !dbg !2310
  %fd4 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher3, i32 0, i32 5, !dbg !2311
  %7 = load i32, i32* %fd4, align 8, !dbg !2311
  store i32 %7, i32* %fd_out, align 4, !dbg !2312
  br label %sw.epilog, !dbg !2313

sw.bb5:                                           ; preds = %entry
  %8 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2314
  %9 = bitcast %struct.uv_handle_s* %8 to %struct.uv_poll_s*, !dbg !2315
  %io_watcher6 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %9, i32 0, i32 9, !dbg !2315
  %fd7 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher6, i32 0, i32 5, !dbg !2316
  %10 = load i32, i32* %fd7, align 8, !dbg !2316
  store i32 %10, i32* %fd_out, align 4, !dbg !2317
  br label %sw.epilog, !dbg !2318

sw.default:                                       ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !2319
  br label %return, !dbg !2319

sw.epilog:                                        ; preds = %sw.bb5, %sw.bb2, %sw.bb
  %11 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !2320
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %11, i32 0, i32 7, !dbg !2320
  %12 = load i32, i32* %flags, align 8, !dbg !2320
  %and = and i32 %12, 3, !dbg !2320
  %cmp = icmp ne i32 %and, 0, !dbg !2320
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2322

lor.lhs.false:                                    ; preds = %sw.epilog
  %13 = load i32, i32* %fd_out, align 4, !dbg !2323
  %cmp8 = icmp eq i32 %13, -1, !dbg !2325
  br i1 %cmp8, label %if.then, label %if.end, !dbg !2326

if.then:                                          ; preds = %lor.lhs.false, %sw.epilog
  store i32 -9, i32* %retval, align 4, !dbg !2327
  br label %return, !dbg !2327

if.end:                                           ; preds = %lor.lhs.false
  %14 = load i32, i32* %fd_out, align 4, !dbg !2328
  %15 = load i32*, i32** %fd.addr, align 8, !dbg !2329
  store i32 %14, i32* %15, align 4, !dbg !2330
  store i32 0, i32* %retval, align 4, !dbg !2331
  br label %return, !dbg !2331

return:                                           ; preds = %if.end, %if.then, %sw.default
  %16 = load i32, i32* %retval, align 4, !dbg !2332
  ret i32 %16, !dbg !2332
}

; Function Attrs: nounwind uwtable
define void @uv__io_init(%struct.uv__io_s* %w, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* %cb, i32 %fd) #0 !dbg !1047 {
entry:
  %w.addr = alloca %struct.uv__io_s*, align 8
  %cb.addr = alloca void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, align 8
  %fd.addr = alloca i32, align 4
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !2333, metadata !1145), !dbg !2334
  store void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* %cb, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb.addr, metadata !2335, metadata !1145), !dbg !2336
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2337, metadata !1145), !dbg !2338
  %0 = load void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb.addr, align 8, !dbg !2339
  %cmp = icmp ne void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* %0, null, !dbg !2339
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2339

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2340

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 812, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @__PRETTY_FUNCTION__.uv__io_init, i32 0, i32 0)) #8, !dbg !2342
  unreachable, !dbg !2342
                                                  ; No predecessors!
  br label %cond.end, !dbg !2344

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %fd.addr, align 4, !dbg !2346
  %cmp1 = icmp sge i32 %2, -1, !dbg !2346
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !2346

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !2347

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 813, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @__PRETTY_FUNCTION__.uv__io_init, i32 0, i32 0)) #8, !dbg !2348
  unreachable, !dbg !2348
                                                  ; No predecessors!
  br label %cond.end4, !dbg !2349

cond.end4:                                        ; preds = %3, %cond.true2
  br label %do.body, !dbg !2350

do.body:                                          ; preds = %cond.end4
  %4 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2351
  %pending_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %4, i32 0, i32 1, !dbg !2351
  %5 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2351
  %pending_queue5 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %5, i32 0, i32 1, !dbg !2351
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue5, i64 0, i64 0, !dbg !2351
  %6 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2351
  store [2 x i8*]* %pending_queue, [2 x i8*]** %6, align 8, !dbg !2351
  %7 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2351
  %pending_queue6 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %7, i32 0, i32 1, !dbg !2351
  %8 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2351
  %pending_queue7 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %8, i32 0, i32 1, !dbg !2351
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue7, i64 0, i64 1, !dbg !2351
  %9 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !2351
  store [2 x i8*]* %pending_queue6, [2 x i8*]** %9, align 8, !dbg !2351
  br label %do.end, !dbg !2351

do.end:                                           ; preds = %do.body
  br label %do.body9, !dbg !2354

do.body9:                                         ; preds = %do.end
  %10 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2355
  %watcher_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %10, i32 0, i32 2, !dbg !2355
  %11 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2355
  %watcher_queue10 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %11, i32 0, i32 2, !dbg !2355
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue10, i64 0, i64 0, !dbg !2355
  %12 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !2355
  store [2 x i8*]* %watcher_queue, [2 x i8*]** %12, align 8, !dbg !2355
  %13 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2355
  %watcher_queue12 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %13, i32 0, i32 2, !dbg !2355
  %14 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2355
  %watcher_queue13 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %14, i32 0, i32 2, !dbg !2355
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue13, i64 0, i64 1, !dbg !2355
  %15 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !2355
  store [2 x i8*]* %watcher_queue12, [2 x i8*]** %15, align 8, !dbg !2355
  br label %do.end15, !dbg !2355

do.end15:                                         ; preds = %do.body9
  %16 = load void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb.addr, align 8, !dbg !2358
  %17 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2359
  %cb16 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %17, i32 0, i32 0, !dbg !2360
  store void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* %16, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb16, align 8, !dbg !2361
  %18 = load i32, i32* %fd.addr, align 4, !dbg !2362
  %19 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2363
  %fd17 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %19, i32 0, i32 5, !dbg !2364
  store i32 %18, i32* %fd17, align 8, !dbg !2365
  %20 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2366
  %events = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %20, i32 0, i32 4, !dbg !2367
  store i32 0, i32* %events, align 4, !dbg !2368
  %21 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2369
  %pevents = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %21, i32 0, i32 3, !dbg !2370
  store i32 0, i32* %pevents, align 8, !dbg !2371
  ret void, !dbg !2372
}

; Function Attrs: nounwind uwtable
define void @uv__io_start(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !1050 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2373, metadata !1145), !dbg !2374
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !2375, metadata !1145), !dbg !2376
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !2377, metadata !1145), !dbg !2378
  %0 = load i32, i32* %events.addr, align 4, !dbg !2379
  %and = and i32 %0, -8198, !dbg !2379
  %cmp = icmp eq i32 0, %and, !dbg !2379
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2379

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2380

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 829, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv__io_start, i32 0, i32 0)) #8, !dbg !2382
  unreachable, !dbg !2382
                                                  ; No predecessors!
  br label %cond.end, !dbg !2384

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %events.addr, align 4, !dbg !2386
  %cmp1 = icmp ne i32 0, %2, !dbg !2386
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !2386

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !2387

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 830, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv__io_start, i32 0, i32 0)) #8, !dbg !2388
  unreachable, !dbg !2388
                                                  ; No predecessors!
  br label %cond.end4, !dbg !2389

cond.end4:                                        ; preds = %3, %cond.true2
  %4 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2390
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %4, i32 0, i32 5, !dbg !2390
  %5 = load i32, i32* %fd, align 8, !dbg !2390
  %cmp5 = icmp sge i32 %5, 0, !dbg !2390
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !2390

cond.true6:                                       ; preds = %cond.end4
  br label %cond.end8, !dbg !2391

cond.false7:                                      ; preds = %cond.end4
  call void @__assert_fail(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 831, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv__io_start, i32 0, i32 0)) #8, !dbg !2392
  unreachable, !dbg !2392
                                                  ; No predecessors!
  br label %cond.end8, !dbg !2393

cond.end8:                                        ; preds = %6, %cond.true6
  %7 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2394
  %fd9 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %7, i32 0, i32 5, !dbg !2394
  %8 = load i32, i32* %fd9, align 8, !dbg !2394
  %cmp10 = icmp slt i32 %8, 2147483647, !dbg !2394
  br i1 %cmp10, label %cond.true11, label %cond.false12, !dbg !2394

cond.true11:                                      ; preds = %cond.end8
  br label %cond.end13, !dbg !2395

cond.false12:                                     ; preds = %cond.end8
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 832, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv__io_start, i32 0, i32 0)) #8, !dbg !2396
  unreachable, !dbg !2396
                                                  ; No predecessors!
  br label %cond.end13, !dbg !2397

cond.end13:                                       ; preds = %9, %cond.true11
  %10 = load i32, i32* %events.addr, align 4, !dbg !2398
  %11 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2399
  %pevents = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %11, i32 0, i32 3, !dbg !2400
  %12 = load i32, i32* %pevents, align 8, !dbg !2401
  %or = or i32 %12, %10, !dbg !2401
  store i32 %or, i32* %pevents, align 8, !dbg !2401
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2402
  %14 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2403
  %fd14 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %14, i32 0, i32 5, !dbg !2404
  %15 = load i32, i32* %fd14, align 8, !dbg !2404
  %add = add nsw i32 %15, 1, !dbg !2405
  call void @maybe_resize(%struct.uv_loop_s* %13, i32 %add), !dbg !2406
  %16 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2407
  %events15 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %16, i32 0, i32 4, !dbg !2409
  %17 = load i32, i32* %events15, align 4, !dbg !2409
  %18 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2410
  %pevents16 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %18, i32 0, i32 3, !dbg !2411
  %19 = load i32, i32* %pevents16, align 8, !dbg !2411
  %cmp17 = icmp eq i32 %17, %19, !dbg !2412
  br i1 %cmp17, label %if.then, label %if.end, !dbg !2413

if.then:                                          ; preds = %cond.end13
  br label %if.end44, !dbg !2414

if.end:                                           ; preds = %cond.end13
  %20 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2415
  %watcher_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %20, i32 0, i32 2, !dbg !2415
  %21 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2415
  %watcher_queue18 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %21, i32 0, i32 2, !dbg !2415
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue18, i64 0, i64 0, !dbg !2415
  %22 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2415
  %23 = load [2 x i8*]*, [2 x i8*]** %22, align 8, !dbg !2415
  %cmp19 = icmp eq [2 x i8*]* %watcher_queue, %23, !dbg !2415
  br i1 %cmp19, label %if.then20, label %if.end35, !dbg !2417

if.then20:                                        ; preds = %if.end
  br label %do.body, !dbg !2418

do.body:                                          ; preds = %if.then20
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2419
  %watcher_queue21 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 8, !dbg !2419
  %25 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2419
  %watcher_queue22 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %25, i32 0, i32 2, !dbg !2419
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue22, i64 0, i64 0, !dbg !2419
  %26 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !2419
  store [2 x i8*]* %watcher_queue21, [2 x i8*]** %26, align 8, !dbg !2419
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2419
  %watcher_queue24 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 8, !dbg !2419
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue24, i64 0, i64 1, !dbg !2419
  %28 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !2419
  %29 = load [2 x i8*]*, [2 x i8*]** %28, align 8, !dbg !2419
  %30 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2419
  %watcher_queue26 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %30, i32 0, i32 2, !dbg !2419
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue26, i64 0, i64 1, !dbg !2419
  %31 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !2419
  store [2 x i8*]* %29, [2 x i8*]** %31, align 8, !dbg !2419
  %32 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2419
  %watcher_queue28 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %32, i32 0, i32 2, !dbg !2419
  %33 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2419
  %watcher_queue29 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %33, i32 0, i32 2, !dbg !2419
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue29, i64 0, i64 1, !dbg !2419
  %34 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !2419
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !2419
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %35, i64 0, i64 0, !dbg !2419
  %36 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !2419
  store [2 x i8*]* %watcher_queue28, [2 x i8*]** %36, align 8, !dbg !2419
  %37 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2419
  %watcher_queue32 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %37, i32 0, i32 2, !dbg !2419
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2419
  %watcher_queue33 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 8, !dbg !2419
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue33, i64 0, i64 1, !dbg !2419
  %39 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !2419
  store [2 x i8*]* %watcher_queue32, [2 x i8*]** %39, align 8, !dbg !2419
  br label %do.end, !dbg !2419

do.end:                                           ; preds = %do.body
  br label %if.end35, !dbg !2422

if.end35:                                         ; preds = %do.end, %if.end
  %40 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2424
  %fd36 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %40, i32 0, i32 5, !dbg !2426
  %41 = load i32, i32* %fd36, align 8, !dbg !2426
  %idxprom = sext i32 %41 to i64, !dbg !2427
  %42 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2427
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %42, i32 0, i32 9, !dbg !2428
  %43 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2428
  %arrayidx37 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %43, i64 %idxprom, !dbg !2427
  %44 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx37, align 8, !dbg !2427
  %cmp38 = icmp eq %struct.uv__io_s* %44, null, !dbg !2429
  br i1 %cmp38, label %if.then39, label %if.end44, !dbg !2430

if.then39:                                        ; preds = %if.end35
  %45 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2431
  %46 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2433
  %fd40 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %46, i32 0, i32 5, !dbg !2434
  %47 = load i32, i32* %fd40, align 8, !dbg !2434
  %idxprom41 = sext i32 %47 to i64, !dbg !2435
  %48 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2435
  %watchers42 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %48, i32 0, i32 9, !dbg !2436
  %49 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers42, align 8, !dbg !2436
  %arrayidx43 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %49, i64 %idxprom41, !dbg !2435
  store %struct.uv__io_s* %45, %struct.uv__io_s** %arrayidx43, align 8, !dbg !2437
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2438
  %nfds = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %50, i32 0, i32 11, !dbg !2439
  %51 = load i32, i32* %nfds, align 4, !dbg !2440
  %inc = add i32 %51, 1, !dbg !2440
  store i32 %inc, i32* %nfds, align 4, !dbg !2440
  br label %if.end44, !dbg !2441

if.end44:                                         ; preds = %if.then, %if.then39, %if.end35
  ret void, !dbg !2442
}

; Function Attrs: nounwind uwtable
define internal void @maybe_resize(%struct.uv_loop_s* %loop, i32 %len) #0 !dbg !1128 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %len.addr = alloca i32, align 4
  %watchers = alloca %struct.uv__io_s**, align 8
  %fake_watcher_list = alloca i8*, align 8
  %fake_watcher_count = alloca i8*, align 8
  %nwatchers = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2443, metadata !1145), !dbg !2444
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !2445, metadata !1145), !dbg !2446
  call void @llvm.dbg.declare(metadata %struct.uv__io_s*** %watchers, metadata !2447, metadata !1145), !dbg !2448
  call void @llvm.dbg.declare(metadata i8** %fake_watcher_list, metadata !2449, metadata !1145), !dbg !2450
  call void @llvm.dbg.declare(metadata i8** %fake_watcher_count, metadata !2451, metadata !1145), !dbg !2452
  call void @llvm.dbg.declare(metadata i32* %nwatchers, metadata !2453, metadata !1145), !dbg !2454
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2455, metadata !1145), !dbg !2456
  %0 = load i32, i32* %len.addr, align 4, !dbg !2457
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2459
  %nwatchers1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 10, !dbg !2460
  %2 = load i32, i32* %nwatchers1, align 8, !dbg !2460
  %cmp = icmp ule i32 %0, %2, !dbg !2461
  br i1 %cmp, label %if.then, label %if.end, !dbg !2462

if.then:                                          ; preds = %entry
  br label %return, !dbg !2463

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2464
  %watchers2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 9, !dbg !2466
  %4 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers2, align 8, !dbg !2466
  %cmp3 = icmp ne %struct.uv__io_s** %4, null, !dbg !2467
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !2468

if.then4:                                         ; preds = %if.end
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2469
  %nwatchers5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 10, !dbg !2471
  %6 = load i32, i32* %nwatchers5, align 8, !dbg !2471
  %idxprom = zext i32 %6 to i64, !dbg !2472
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2472
  %watchers6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 9, !dbg !2473
  %8 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers6, align 8, !dbg !2473
  %arrayidx = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %8, i64 %idxprom, !dbg !2472
  %9 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx, align 8, !dbg !2472
  %10 = bitcast %struct.uv__io_s* %9 to i8*, !dbg !2472
  store i8* %10, i8** %fake_watcher_list, align 8, !dbg !2474
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2475
  %nwatchers7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 10, !dbg !2476
  %12 = load i32, i32* %nwatchers7, align 8, !dbg !2476
  %add = add i32 %12, 1, !dbg !2477
  %idxprom8 = zext i32 %add to i64, !dbg !2478
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2478
  %watchers9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 9, !dbg !2479
  %14 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers9, align 8, !dbg !2479
  %arrayidx10 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %14, i64 %idxprom8, !dbg !2478
  %15 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx10, align 8, !dbg !2478
  %16 = bitcast %struct.uv__io_s* %15 to i8*, !dbg !2478
  store i8* %16, i8** %fake_watcher_count, align 8, !dbg !2480
  br label %if.end11, !dbg !2481

if.else:                                          ; preds = %if.end
  store i8* null, i8** %fake_watcher_list, align 8, !dbg !2482
  store i8* null, i8** %fake_watcher_count, align 8, !dbg !2484
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then4
  %17 = load i32, i32* %len.addr, align 4, !dbg !2485
  %add12 = add i32 %17, 2, !dbg !2486
  %call = call i32 @next_power_of_two(i32 %add12), !dbg !2487
  %sub = sub i32 %call, 2, !dbg !2488
  store i32 %sub, i32* %nwatchers, align 4, !dbg !2489
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2490
  %watchers13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 9, !dbg !2491
  %19 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers13, align 8, !dbg !2491
  %20 = bitcast %struct.uv__io_s** %19 to i8*, !dbg !2490
  %21 = load i32, i32* %nwatchers, align 4, !dbg !2492
  %add14 = add i32 %21, 2, !dbg !2493
  %conv = zext i32 %add14 to i64, !dbg !2494
  %mul = mul i64 %conv, 8, !dbg !2495
  %call15 = call i8* @uv__realloc(i8* %20, i64 %mul), !dbg !2496
  %22 = bitcast i8* %call15 to %struct.uv__io_s**, !dbg !2496
  store %struct.uv__io_s** %22, %struct.uv__io_s*** %watchers, align 8, !dbg !2497
  %23 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2498
  %cmp16 = icmp eq %struct.uv__io_s** %23, null, !dbg !2500
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !2501

if.then18:                                        ; preds = %if.end11
  call void @abort() #8, !dbg !2502
  unreachable, !dbg !2502

if.end19:                                         ; preds = %if.end11
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2503
  %nwatchers20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 10, !dbg !2505
  %25 = load i32, i32* %nwatchers20, align 8, !dbg !2505
  store i32 %25, i32* %i, align 4, !dbg !2506
  br label %for.cond, !dbg !2507

for.cond:                                         ; preds = %for.inc, %if.end19
  %26 = load i32, i32* %i, align 4, !dbg !2508
  %27 = load i32, i32* %nwatchers, align 4, !dbg !2511
  %cmp21 = icmp ult i32 %26, %27, !dbg !2512
  br i1 %cmp21, label %for.body, label %for.end, !dbg !2513

for.body:                                         ; preds = %for.cond
  %28 = load i32, i32* %i, align 4, !dbg !2514
  %idxprom23 = zext i32 %28 to i64, !dbg !2515
  %29 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2515
  %arrayidx24 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %29, i64 %idxprom23, !dbg !2515
  store %struct.uv__io_s* null, %struct.uv__io_s** %arrayidx24, align 8, !dbg !2516
  br label %for.inc, !dbg !2515

for.inc:                                          ; preds = %for.body
  %30 = load i32, i32* %i, align 4, !dbg !2517
  %inc = add i32 %30, 1, !dbg !2517
  store i32 %inc, i32* %i, align 4, !dbg !2517
  br label %for.cond, !dbg !2519

for.end:                                          ; preds = %for.cond
  %31 = load i8*, i8** %fake_watcher_list, align 8, !dbg !2520
  %32 = bitcast i8* %31 to %struct.uv__io_s*, !dbg !2520
  %33 = load i32, i32* %nwatchers, align 4, !dbg !2521
  %idxprom25 = zext i32 %33 to i64, !dbg !2522
  %34 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2522
  %arrayidx26 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %34, i64 %idxprom25, !dbg !2522
  store %struct.uv__io_s* %32, %struct.uv__io_s** %arrayidx26, align 8, !dbg !2523
  %35 = load i8*, i8** %fake_watcher_count, align 8, !dbg !2524
  %36 = bitcast i8* %35 to %struct.uv__io_s*, !dbg !2524
  %37 = load i32, i32* %nwatchers, align 4, !dbg !2525
  %add27 = add i32 %37, 1, !dbg !2526
  %idxprom28 = zext i32 %add27 to i64, !dbg !2527
  %38 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2527
  %arrayidx29 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %38, i64 %idxprom28, !dbg !2527
  store %struct.uv__io_s* %36, %struct.uv__io_s** %arrayidx29, align 8, !dbg !2528
  %39 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2529
  %40 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2530
  %watchers30 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %40, i32 0, i32 9, !dbg !2531
  store %struct.uv__io_s** %39, %struct.uv__io_s*** %watchers30, align 8, !dbg !2532
  %41 = load i32, i32* %nwatchers, align 4, !dbg !2533
  %42 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2534
  %nwatchers31 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %42, i32 0, i32 10, !dbg !2535
  store i32 %41, i32* %nwatchers31, align 8, !dbg !2536
  br label %return, !dbg !2537

return:                                           ; preds = %for.end, %if.then
  ret void, !dbg !2538
}

; Function Attrs: nounwind uwtable
define void @uv__io_stop(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !1053 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2540, metadata !1145), !dbg !2541
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !2542, metadata !1145), !dbg !2543
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !2544, metadata !1145), !dbg !2545
  %0 = load i32, i32* %events.addr, align 4, !dbg !2546
  %and = and i32 %0, -8198, !dbg !2546
  %cmp = icmp eq i32 0, %and, !dbg !2546
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2546

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2547

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 857, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.uv__io_stop, i32 0, i32 0)) #8, !dbg !2549
  unreachable, !dbg !2549
                                                  ; No predecessors!
  br label %cond.end, !dbg !2551

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %events.addr, align 4, !dbg !2553
  %cmp1 = icmp ne i32 0, %2, !dbg !2553
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !2553

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !2554

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 858, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.uv__io_stop, i32 0, i32 0)) #8, !dbg !2555
  unreachable, !dbg !2555
                                                  ; No predecessors!
  br label %cond.end4, !dbg !2556

cond.end4:                                        ; preds = %3, %cond.true2
  %4 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2557
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %4, i32 0, i32 5, !dbg !2559
  %5 = load i32, i32* %fd, align 8, !dbg !2559
  %cmp5 = icmp eq i32 %5, -1, !dbg !2560
  br i1 %cmp5, label %if.then, label %if.end, !dbg !2561

if.then:                                          ; preds = %cond.end4
  br label %if.end80, !dbg !2562

if.end:                                           ; preds = %cond.end4
  %6 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2563
  %fd6 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %6, i32 0, i32 5, !dbg !2563
  %7 = load i32, i32* %fd6, align 8, !dbg !2563
  %cmp7 = icmp sge i32 %7, 0, !dbg !2563
  br i1 %cmp7, label %cond.true8, label %cond.false9, !dbg !2563

cond.true8:                                       ; preds = %if.end
  br label %cond.end10, !dbg !2564

cond.false9:                                      ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 863, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.uv__io_stop, i32 0, i32 0)) #8, !dbg !2565
  unreachable, !dbg !2565
                                                  ; No predecessors!
  br label %cond.end10, !dbg !2566

cond.end10:                                       ; preds = %8, %cond.true8
  %9 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2567
  %fd11 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %9, i32 0, i32 5, !dbg !2569
  %10 = load i32, i32* %fd11, align 8, !dbg !2569
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2570
  %nwatchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 10, !dbg !2571
  %12 = load i32, i32* %nwatchers, align 8, !dbg !2571
  %cmp12 = icmp uge i32 %10, %12, !dbg !2572
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !2573

if.then13:                                        ; preds = %cond.end10
  br label %if.end80, !dbg !2574

if.end14:                                         ; preds = %cond.end10
  %13 = load i32, i32* %events.addr, align 4, !dbg !2575
  %neg = xor i32 %13, -1, !dbg !2576
  %14 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2577
  %pevents = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %14, i32 0, i32 3, !dbg !2578
  %15 = load i32, i32* %pevents, align 8, !dbg !2579
  %and15 = and i32 %15, %neg, !dbg !2579
  store i32 %and15, i32* %pevents, align 8, !dbg !2579
  %16 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2580
  %pevents16 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %16, i32 0, i32 3, !dbg !2582
  %17 = load i32, i32* %pevents16, align 8, !dbg !2582
  %cmp17 = icmp eq i32 %17, 0, !dbg !2583
  br i1 %cmp17, label %if.then18, label %if.else, !dbg !2584

if.then18:                                        ; preds = %if.end14
  br label %do.body, !dbg !2585

do.body:                                          ; preds = %if.then18
  %18 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2587
  %watcher_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %18, i32 0, i32 2, !dbg !2587
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue, i64 0, i64 0, !dbg !2587
  %19 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2587
  %20 = load [2 x i8*]*, [2 x i8*]** %19, align 8, !dbg !2587
  %21 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2587
  %watcher_queue19 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %21, i32 0, i32 2, !dbg !2587
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue19, i64 0, i64 1, !dbg !2587
  %22 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !2587
  %23 = load [2 x i8*]*, [2 x i8*]** %22, align 8, !dbg !2587
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %23, i64 0, i64 0, !dbg !2587
  %24 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !2587
  store [2 x i8*]* %20, [2 x i8*]** %24, align 8, !dbg !2587
  %25 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2587
  %watcher_queue22 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %25, i32 0, i32 2, !dbg !2587
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue22, i64 0, i64 1, !dbg !2587
  %26 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !2587
  %27 = load [2 x i8*]*, [2 x i8*]** %26, align 8, !dbg !2587
  %28 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2587
  %watcher_queue24 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %28, i32 0, i32 2, !dbg !2587
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue24, i64 0, i64 0, !dbg !2587
  %29 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !2587
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !2587
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %30, i64 0, i64 1, !dbg !2587
  %31 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !2587
  store [2 x i8*]* %27, [2 x i8*]** %31, align 8, !dbg !2587
  br label %do.end, !dbg !2587

do.end:                                           ; preds = %do.body
  br label %do.body27, !dbg !2590

do.body27:                                        ; preds = %do.end
  %32 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2591
  %watcher_queue28 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %32, i32 0, i32 2, !dbg !2591
  %33 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2591
  %watcher_queue29 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %33, i32 0, i32 2, !dbg !2591
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue29, i64 0, i64 0, !dbg !2591
  %34 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !2591
  store [2 x i8*]* %watcher_queue28, [2 x i8*]** %34, align 8, !dbg !2591
  %35 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2591
  %watcher_queue31 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %35, i32 0, i32 2, !dbg !2591
  %36 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2591
  %watcher_queue32 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %36, i32 0, i32 2, !dbg !2591
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue32, i64 0, i64 1, !dbg !2591
  %37 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !2591
  store [2 x i8*]* %watcher_queue31, [2 x i8*]** %37, align 8, !dbg !2591
  br label %do.end34, !dbg !2591

do.end34:                                         ; preds = %do.body27
  %38 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2594
  %fd35 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %38, i32 0, i32 5, !dbg !2596
  %39 = load i32, i32* %fd35, align 8, !dbg !2596
  %idxprom = sext i32 %39 to i64, !dbg !2597
  %40 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2597
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %40, i32 0, i32 9, !dbg !2598
  %41 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !2598
  %arrayidx36 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %41, i64 %idxprom, !dbg !2597
  %42 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx36, align 8, !dbg !2597
  %cmp37 = icmp ne %struct.uv__io_s* %42, null, !dbg !2599
  br i1 %cmp37, label %if.then38, label %if.end57, !dbg !2600

if.then38:                                        ; preds = %do.end34
  %43 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2601
  %fd39 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %43, i32 0, i32 5, !dbg !2601
  %44 = load i32, i32* %fd39, align 8, !dbg !2601
  %idxprom40 = sext i32 %44 to i64, !dbg !2601
  %45 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2601
  %watchers41 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %45, i32 0, i32 9, !dbg !2601
  %46 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers41, align 8, !dbg !2601
  %arrayidx42 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %46, i64 %idxprom40, !dbg !2601
  %47 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx42, align 8, !dbg !2601
  %48 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2601
  %cmp43 = icmp eq %struct.uv__io_s* %47, %48, !dbg !2601
  br i1 %cmp43, label %cond.true44, label %cond.false45, !dbg !2601

cond.true44:                                      ; preds = %if.then38
  br label %cond.end46, !dbg !2603

cond.false45:                                     ; preds = %if.then38
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 876, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.uv__io_stop, i32 0, i32 0)) #8, !dbg !2605
  unreachable, !dbg !2605
                                                  ; No predecessors!
  br label %cond.end46, !dbg !2607

cond.end46:                                       ; preds = %49, %cond.true44
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2609
  %nfds = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %50, i32 0, i32 11, !dbg !2609
  %51 = load i32, i32* %nfds, align 4, !dbg !2609
  %cmp47 = icmp ugt i32 %51, 0, !dbg !2609
  br i1 %cmp47, label %cond.true48, label %cond.false49, !dbg !2609

cond.true48:                                      ; preds = %cond.end46
  br label %cond.end50, !dbg !2610

cond.false49:                                     ; preds = %cond.end46
  call void @__assert_fail(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 877, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.uv__io_stop, i32 0, i32 0)) #8, !dbg !2611
  unreachable, !dbg !2611
                                                  ; No predecessors!
  br label %cond.end50, !dbg !2612

cond.end50:                                       ; preds = %52, %cond.true48
  %53 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2613
  %fd51 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %53, i32 0, i32 5, !dbg !2614
  %54 = load i32, i32* %fd51, align 8, !dbg !2614
  %idxprom52 = sext i32 %54 to i64, !dbg !2615
  %55 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2615
  %watchers53 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %55, i32 0, i32 9, !dbg !2616
  %56 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers53, align 8, !dbg !2616
  %arrayidx54 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %56, i64 %idxprom52, !dbg !2615
  store %struct.uv__io_s* null, %struct.uv__io_s** %arrayidx54, align 8, !dbg !2617
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2618
  %nfds55 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %57, i32 0, i32 11, !dbg !2619
  %58 = load i32, i32* %nfds55, align 4, !dbg !2620
  %dec = add i32 %58, -1, !dbg !2620
  store i32 %dec, i32* %nfds55, align 4, !dbg !2620
  %59 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2621
  %events56 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %59, i32 0, i32 4, !dbg !2622
  store i32 0, i32* %events56, align 4, !dbg !2623
  br label %if.end57, !dbg !2624

if.end57:                                         ; preds = %cond.end50, %do.end34
  br label %if.end80, !dbg !2625

if.else:                                          ; preds = %if.end14
  %60 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2626
  %watcher_queue58 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %60, i32 0, i32 2, !dbg !2626
  %61 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2626
  %watcher_queue59 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %61, i32 0, i32 2, !dbg !2626
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue59, i64 0, i64 0, !dbg !2626
  %62 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !2626
  %63 = load [2 x i8*]*, [2 x i8*]** %62, align 8, !dbg !2626
  %cmp61 = icmp eq [2 x i8*]* %watcher_queue58, %63, !dbg !2626
  br i1 %cmp61, label %if.then62, label %if.end79, !dbg !2628

if.then62:                                        ; preds = %if.else
  br label %do.body63, !dbg !2629

do.body63:                                        ; preds = %if.then62
  %64 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2630
  %watcher_queue64 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %64, i32 0, i32 8, !dbg !2630
  %65 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2630
  %watcher_queue65 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %65, i32 0, i32 2, !dbg !2630
  %arrayidx66 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue65, i64 0, i64 0, !dbg !2630
  %66 = bitcast i8** %arrayidx66 to [2 x i8*]**, !dbg !2630
  store [2 x i8*]* %watcher_queue64, [2 x i8*]** %66, align 8, !dbg !2630
  %67 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2630
  %watcher_queue67 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %67, i32 0, i32 8, !dbg !2630
  %arrayidx68 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue67, i64 0, i64 1, !dbg !2630
  %68 = bitcast i8** %arrayidx68 to [2 x i8*]**, !dbg !2630
  %69 = load [2 x i8*]*, [2 x i8*]** %68, align 8, !dbg !2630
  %70 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2630
  %watcher_queue69 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %70, i32 0, i32 2, !dbg !2630
  %arrayidx70 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue69, i64 0, i64 1, !dbg !2630
  %71 = bitcast i8** %arrayidx70 to [2 x i8*]**, !dbg !2630
  store [2 x i8*]* %69, [2 x i8*]** %71, align 8, !dbg !2630
  %72 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2630
  %watcher_queue71 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %72, i32 0, i32 2, !dbg !2630
  %73 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2630
  %watcher_queue72 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %73, i32 0, i32 2, !dbg !2630
  %arrayidx73 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue72, i64 0, i64 1, !dbg !2630
  %74 = bitcast i8** %arrayidx73 to [2 x i8*]**, !dbg !2630
  %75 = load [2 x i8*]*, [2 x i8*]** %74, align 8, !dbg !2630
  %arrayidx74 = getelementptr inbounds [2 x i8*], [2 x i8*]* %75, i64 0, i64 0, !dbg !2630
  %76 = bitcast i8** %arrayidx74 to [2 x i8*]**, !dbg !2630
  store [2 x i8*]* %watcher_queue71, [2 x i8*]** %76, align 8, !dbg !2630
  %77 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2630
  %watcher_queue75 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %77, i32 0, i32 2, !dbg !2630
  %78 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2630
  %watcher_queue76 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %78, i32 0, i32 8, !dbg !2630
  %arrayidx77 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue76, i64 0, i64 1, !dbg !2630
  %79 = bitcast i8** %arrayidx77 to [2 x i8*]**, !dbg !2630
  store [2 x i8*]* %watcher_queue75, [2 x i8*]** %79, align 8, !dbg !2630
  br label %do.end78, !dbg !2630

do.end78:                                         ; preds = %do.body63
  br label %if.end79, !dbg !2633

if.end79:                                         ; preds = %do.end78, %if.else
  br label %if.end80

if.end80:                                         ; preds = %if.then, %if.then13, %if.end79, %if.end57
  ret void, !dbg !2635
}

; Function Attrs: nounwind uwtable
define void @uv__io_close(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w) #0 !dbg !1054 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2636, metadata !1145), !dbg !2637
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !2638, metadata !1145), !dbg !2639
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2640
  %1 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2641
  call void @uv__io_stop(%struct.uv_loop_s* %0, %struct.uv__io_s* %1, i32 8197), !dbg !2642
  br label %do.body, !dbg !2643

do.body:                                          ; preds = %entry
  %2 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2644
  %pending_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %2, i32 0, i32 1, !dbg !2644
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue, i64 0, i64 0, !dbg !2644
  %3 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2644
  %4 = load [2 x i8*]*, [2 x i8*]** %3, align 8, !dbg !2644
  %5 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2644
  %pending_queue1 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %5, i32 0, i32 1, !dbg !2644
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue1, i64 0, i64 1, !dbg !2644
  %6 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !2644
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !2644
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !2644
  %8 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !2644
  store [2 x i8*]* %4, [2 x i8*]** %8, align 8, !dbg !2644
  %9 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2644
  %pending_queue4 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %9, i32 0, i32 1, !dbg !2644
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue4, i64 0, i64 1, !dbg !2644
  %10 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !2644
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !2644
  %12 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2644
  %pending_queue6 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %12, i32 0, i32 1, !dbg !2644
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue6, i64 0, i64 0, !dbg !2644
  %13 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2644
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2644
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 1, !dbg !2644
  %15 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !2644
  store [2 x i8*]* %11, [2 x i8*]** %15, align 8, !dbg !2644
  br label %do.end, !dbg !2644

do.end:                                           ; preds = %do.body
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2647
  %17 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2648
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %17, i32 0, i32 5, !dbg !2649
  %18 = load i32, i32* %fd, align 8, !dbg !2649
  call void @uv__platform_invalidate_fd(%struct.uv_loop_s* %16, i32 %18), !dbg !2650
  ret void, !dbg !2651
}

declare void @uv__platform_invalidate_fd(%struct.uv_loop_s*, i32) #1

; Function Attrs: nounwind uwtable
define void @uv__io_feed(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w) #0 !dbg !1057 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2652, metadata !1145), !dbg !2653
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !2654, metadata !1145), !dbg !2655
  %0 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2656
  %pending_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %0, i32 0, i32 1, !dbg !2656
  %1 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2656
  %pending_queue1 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %1, i32 0, i32 1, !dbg !2656
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue1, i64 0, i64 0, !dbg !2656
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2656
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !2656
  %cmp = icmp eq [2 x i8*]* %pending_queue, %3, !dbg !2656
  br i1 %cmp, label %if.then, label %if.end, !dbg !2658

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !2659

do.body:                                          ; preds = %if.then
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2660
  %pending_queue2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 7, !dbg !2660
  %5 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2660
  %pending_queue3 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %5, i32 0, i32 1, !dbg !2660
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue3, i64 0, i64 0, !dbg !2660
  %6 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !2660
  store [2 x i8*]* %pending_queue2, [2 x i8*]** %6, align 8, !dbg !2660
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2660
  %pending_queue5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 7, !dbg !2660
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue5, i64 0, i64 1, !dbg !2660
  %8 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !2660
  %9 = load [2 x i8*]*, [2 x i8*]** %8, align 8, !dbg !2660
  %10 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2660
  %pending_queue7 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %10, i32 0, i32 1, !dbg !2660
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue7, i64 0, i64 1, !dbg !2660
  %11 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !2660
  store [2 x i8*]* %9, [2 x i8*]** %11, align 8, !dbg !2660
  %12 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2660
  %pending_queue9 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %12, i32 0, i32 1, !dbg !2660
  %13 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2660
  %pending_queue10 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %13, i32 0, i32 1, !dbg !2660
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue10, i64 0, i64 1, !dbg !2660
  %14 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !2660
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !2660
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !2660
  %16 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2660
  store [2 x i8*]* %pending_queue9, [2 x i8*]** %16, align 8, !dbg !2660
  %17 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2660
  %pending_queue13 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %17, i32 0, i32 1, !dbg !2660
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2660
  %pending_queue14 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 7, !dbg !2660
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue14, i64 0, i64 1, !dbg !2660
  %19 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !2660
  store [2 x i8*]* %pending_queue13, [2 x i8*]** %19, align 8, !dbg !2660
  br label %do.end, !dbg !2660

do.end:                                           ; preds = %do.body
  br label %if.end, !dbg !2663

if.end:                                           ; preds = %do.end, %entry
  ret void, !dbg !2665
}

; Function Attrs: nounwind uwtable
define i32 @uv__io_active(%struct.uv__io_s* %w, i32 %events) #0 !dbg !1058 {
entry:
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !2666, metadata !1145), !dbg !2667
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !2668, metadata !1145), !dbg !2669
  %0 = load i32, i32* %events.addr, align 4, !dbg !2670
  %and = and i32 %0, -8198, !dbg !2670
  %cmp = icmp eq i32 0, %and, !dbg !2670
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2670

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2671

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 904, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__io_active, i32 0, i32 0)) #8, !dbg !2673
  unreachable, !dbg !2673
                                                  ; No predecessors!
  br label %cond.end, !dbg !2675

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %events.addr, align 4, !dbg !2677
  %cmp1 = icmp ne i32 0, %2, !dbg !2677
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !2677

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !2678

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 905, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__io_active, i32 0, i32 0)) #8, !dbg !2679
  unreachable, !dbg !2679
                                                  ; No predecessors!
  br label %cond.end4, !dbg !2680

cond.end4:                                        ; preds = %3, %cond.true2
  %4 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !2681
  %pevents = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %4, i32 0, i32 3, !dbg !2682
  %5 = load i32, i32* %pevents, align 8, !dbg !2682
  %6 = load i32, i32* %events.addr, align 4, !dbg !2683
  %and5 = and i32 %5, %6, !dbg !2684
  %cmp6 = icmp ne i32 0, %and5, !dbg !2685
  %conv = zext i1 %cmp6 to i32, !dbg !2685
  ret i32 %conv, !dbg !2686
}

; Function Attrs: nounwind uwtable
define i32 @uv_getrusage(%struct.uv_rusage_t* %rusage) #0 !dbg !1063 {
entry:
  %retval = alloca i32, align 4
  %rusage.addr = alloca %struct.uv_rusage_t*, align 8
  %usage = alloca %struct.rusage, align 8
  store %struct.uv_rusage_t* %rusage, %struct.uv_rusage_t** %rusage.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_rusage_t** %rusage.addr, metadata !2687, metadata !1145), !dbg !2688
  call void @llvm.dbg.declare(metadata %struct.rusage* %usage, metadata !2689, metadata !1145), !dbg !2772
  %call = call i32 @getrusage(i32 0, %struct.rusage* %usage) #9, !dbg !2773
  %tobool = icmp ne i32 %call, 0, !dbg !2773
  br i1 %tobool, label %if.then, label %if.end, !dbg !2775

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #2, !dbg !2776
  %0 = load i32, i32* %call1, align 4, !dbg !2776
  %sub = sub nsw i32 0, %0, !dbg !2777
  store i32 %sub, i32* %retval, align 4, !dbg !2778
  br label %return, !dbg !2778

if.end:                                           ; preds = %entry
  %ru_utime = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 0, !dbg !2779
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %ru_utime, i32 0, i32 0, !dbg !2780
  %1 = load i64, i64* %tv_sec, align 8, !dbg !2780
  %2 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2781
  %ru_utime2 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %2, i32 0, i32 0, !dbg !2782
  %tv_sec3 = getelementptr inbounds %struct.uv_timeval_t, %struct.uv_timeval_t* %ru_utime2, i32 0, i32 0, !dbg !2783
  store i64 %1, i64* %tv_sec3, align 8, !dbg !2784
  %ru_utime4 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 0, !dbg !2785
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %ru_utime4, i32 0, i32 1, !dbg !2786
  %3 = load i64, i64* %tv_usec, align 8, !dbg !2786
  %4 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2787
  %ru_utime5 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %4, i32 0, i32 0, !dbg !2788
  %tv_usec6 = getelementptr inbounds %struct.uv_timeval_t, %struct.uv_timeval_t* %ru_utime5, i32 0, i32 1, !dbg !2789
  store i64 %3, i64* %tv_usec6, align 8, !dbg !2790
  %ru_stime = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 1, !dbg !2791
  %tv_sec7 = getelementptr inbounds %struct.timeval, %struct.timeval* %ru_stime, i32 0, i32 0, !dbg !2792
  %5 = load i64, i64* %tv_sec7, align 8, !dbg !2792
  %6 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2793
  %ru_stime8 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %6, i32 0, i32 1, !dbg !2794
  %tv_sec9 = getelementptr inbounds %struct.uv_timeval_t, %struct.uv_timeval_t* %ru_stime8, i32 0, i32 0, !dbg !2795
  store i64 %5, i64* %tv_sec9, align 8, !dbg !2796
  %ru_stime10 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 1, !dbg !2797
  %tv_usec11 = getelementptr inbounds %struct.timeval, %struct.timeval* %ru_stime10, i32 0, i32 1, !dbg !2798
  %7 = load i64, i64* %tv_usec11, align 8, !dbg !2798
  %8 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2799
  %ru_stime12 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %8, i32 0, i32 1, !dbg !2800
  %tv_usec13 = getelementptr inbounds %struct.uv_timeval_t, %struct.uv_timeval_t* %ru_stime12, i32 0, i32 1, !dbg !2801
  store i64 %7, i64* %tv_usec13, align 8, !dbg !2802
  %9 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 2, !dbg !2803
  %ru_maxrss = bitcast %union.anon.17* %9 to i64*, !dbg !2803
  %10 = load i64, i64* %ru_maxrss, align 8, !dbg !2803
  %11 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2804
  %ru_maxrss14 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %11, i32 0, i32 2, !dbg !2805
  store i64 %10, i64* %ru_maxrss14, align 8, !dbg !2806
  %12 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 3, !dbg !2807
  %ru_ixrss = bitcast %union.anon.18* %12 to i64*, !dbg !2807
  %13 = load i64, i64* %ru_ixrss, align 8, !dbg !2807
  %14 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2808
  %ru_ixrss15 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %14, i32 0, i32 3, !dbg !2809
  store i64 %13, i64* %ru_ixrss15, align 8, !dbg !2810
  %15 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 4, !dbg !2811
  %ru_idrss = bitcast %union.anon.19* %15 to i64*, !dbg !2811
  %16 = load i64, i64* %ru_idrss, align 8, !dbg !2811
  %17 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2812
  %ru_idrss16 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %17, i32 0, i32 4, !dbg !2813
  store i64 %16, i64* %ru_idrss16, align 8, !dbg !2814
  %18 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 5, !dbg !2815
  %ru_isrss = bitcast %union.anon.20* %18 to i64*, !dbg !2815
  %19 = load i64, i64* %ru_isrss, align 8, !dbg !2815
  %20 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2816
  %ru_isrss17 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %20, i32 0, i32 5, !dbg !2817
  store i64 %19, i64* %ru_isrss17, align 8, !dbg !2818
  %21 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 6, !dbg !2819
  %ru_minflt = bitcast %union.anon.21* %21 to i64*, !dbg !2819
  %22 = load i64, i64* %ru_minflt, align 8, !dbg !2819
  %23 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2820
  %ru_minflt18 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %23, i32 0, i32 6, !dbg !2821
  store i64 %22, i64* %ru_minflt18, align 8, !dbg !2822
  %24 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 7, !dbg !2823
  %ru_majflt = bitcast %union.anon.22* %24 to i64*, !dbg !2823
  %25 = load i64, i64* %ru_majflt, align 8, !dbg !2823
  %26 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2824
  %ru_majflt19 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %26, i32 0, i32 7, !dbg !2825
  store i64 %25, i64* %ru_majflt19, align 8, !dbg !2826
  %27 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 8, !dbg !2827
  %ru_nswap = bitcast %union.anon.23* %27 to i64*, !dbg !2827
  %28 = load i64, i64* %ru_nswap, align 8, !dbg !2827
  %29 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2828
  %ru_nswap20 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %29, i32 0, i32 8, !dbg !2829
  store i64 %28, i64* %ru_nswap20, align 8, !dbg !2830
  %30 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 9, !dbg !2831
  %ru_inblock = bitcast %union.anon.24* %30 to i64*, !dbg !2831
  %31 = load i64, i64* %ru_inblock, align 8, !dbg !2831
  %32 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2832
  %ru_inblock21 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %32, i32 0, i32 9, !dbg !2833
  store i64 %31, i64* %ru_inblock21, align 8, !dbg !2834
  %33 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 10, !dbg !2835
  %ru_oublock = bitcast %union.anon.25* %33 to i64*, !dbg !2835
  %34 = load i64, i64* %ru_oublock, align 8, !dbg !2835
  %35 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2836
  %ru_oublock22 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %35, i32 0, i32 10, !dbg !2837
  store i64 %34, i64* %ru_oublock22, align 8, !dbg !2838
  %36 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 11, !dbg !2839
  %ru_msgsnd = bitcast %union.anon.26* %36 to i64*, !dbg !2839
  %37 = load i64, i64* %ru_msgsnd, align 8, !dbg !2839
  %38 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2840
  %ru_msgsnd23 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %38, i32 0, i32 11, !dbg !2841
  store i64 %37, i64* %ru_msgsnd23, align 8, !dbg !2842
  %39 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 12, !dbg !2843
  %ru_msgrcv = bitcast %union.anon.27* %39 to i64*, !dbg !2843
  %40 = load i64, i64* %ru_msgrcv, align 8, !dbg !2843
  %41 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2844
  %ru_msgrcv24 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %41, i32 0, i32 12, !dbg !2845
  store i64 %40, i64* %ru_msgrcv24, align 8, !dbg !2846
  %42 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 13, !dbg !2847
  %ru_nsignals = bitcast %union.anon.28* %42 to i64*, !dbg !2847
  %43 = load i64, i64* %ru_nsignals, align 8, !dbg !2847
  %44 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2848
  %ru_nsignals25 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %44, i32 0, i32 13, !dbg !2849
  store i64 %43, i64* %ru_nsignals25, align 8, !dbg !2850
  %45 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 14, !dbg !2851
  %ru_nvcsw = bitcast %union.anon.29* %45 to i64*, !dbg !2851
  %46 = load i64, i64* %ru_nvcsw, align 8, !dbg !2851
  %47 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2852
  %ru_nvcsw26 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %47, i32 0, i32 14, !dbg !2853
  store i64 %46, i64* %ru_nvcsw26, align 8, !dbg !2854
  %48 = getelementptr inbounds %struct.rusage, %struct.rusage* %usage, i32 0, i32 15, !dbg !2855
  %ru_nivcsw = bitcast %union.anon.30* %48 to i64*, !dbg !2855
  %49 = load i64, i64* %ru_nivcsw, align 8, !dbg !2855
  %50 = load %struct.uv_rusage_t*, %struct.uv_rusage_t** %rusage.addr, align 8, !dbg !2856
  %ru_nivcsw27 = getelementptr inbounds %struct.uv_rusage_t, %struct.uv_rusage_t* %50, i32 0, i32 15, !dbg !2857
  store i64 %49, i64* %ru_nivcsw27, align 8, !dbg !2858
  store i32 0, i32* %retval, align 4, !dbg !2859
  br label %return, !dbg !2859

return:                                           ; preds = %if.end, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !2860
  ret i32 %51, !dbg !2860
}

; Function Attrs: nounwind
declare i32 @getrusage(i32, %struct.rusage*) #4

declare i32 @open64(i8*, i32, ...) #1

; Function Attrs: nounwind uwtable
define i32 @uv__dup2_cloexec(i32 %oldfd, i32 %newfd) #0 !dbg !1094 {
entry:
  %retval = alloca i32, align 4
  %oldfd.addr = alloca i32, align 4
  %newfd.addr = alloca i32, align 4
  %r = alloca i32, align 4
  %err = alloca i32, align 4
  store i32 %oldfd, i32* %oldfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %oldfd.addr, metadata !2861, metadata !1145), !dbg !2862
  store i32 %newfd, i32* %newfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %newfd.addr, metadata !2863, metadata !1145), !dbg !2864
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2865, metadata !1145), !dbg !2866
  %0 = load i32, i32* @uv__dup2_cloexec.no_dup3, align 4, !dbg !2867
  %tobool = icmp ne i32 %0, 0, !dbg !2867
  br i1 %tobool, label %if.end10, label %if.then, !dbg !2869

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !2870

do.body:                                          ; preds = %land.end, %if.then
  %1 = load i32, i32* %oldfd.addr, align 4, !dbg !2872
  %2 = load i32, i32* %newfd.addr, align 4, !dbg !2873
  %call = call i32 @uv__dup3(i32 %1, i32 %2, i32 524288), !dbg !2874
  store i32 %call, i32* %r, align 4, !dbg !2875
  br label %do.cond, !dbg !2876

do.cond:                                          ; preds = %do.body
  %3 = load i32, i32* %r, align 4, !dbg !2877
  %cmp = icmp eq i32 %3, -1, !dbg !2878
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2879

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #2, !dbg !2880
  %4 = load i32, i32* %call1, align 4, !dbg !2880
  %cmp2 = icmp eq i32 %4, 16, !dbg !2882
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %5 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %5, label %do.body, label %do.end, !dbg !2883

do.end:                                           ; preds = %land.end
  %6 = load i32, i32* %r, align 4, !dbg !2884
  %cmp3 = icmp ne i32 %6, -1, !dbg !2886
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2887

if.then4:                                         ; preds = %do.end
  %7 = load i32, i32* %r, align 4, !dbg !2888
  store i32 %7, i32* %retval, align 4, !dbg !2889
  br label %return, !dbg !2889

if.end:                                           ; preds = %do.end
  %call5 = call i32* @__errno_location() #2, !dbg !2890
  %8 = load i32, i32* %call5, align 4, !dbg !2890
  %cmp6 = icmp ne i32 %8, 38, !dbg !2892
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !2893

if.then7:                                         ; preds = %if.end
  %call8 = call i32* @__errno_location() #2, !dbg !2894
  %9 = load i32, i32* %call8, align 4, !dbg !2894
  %sub = sub nsw i32 0, %9, !dbg !2895
  store i32 %sub, i32* %retval, align 4, !dbg !2896
  br label %return, !dbg !2896

if.end9:                                          ; preds = %if.end
  store i32 1, i32* @uv__dup2_cloexec.no_dup3, align 4, !dbg !2897
  br label %if.end10, !dbg !2898

if.end10:                                         ; preds = %if.end9, %entry
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2899, metadata !1145), !dbg !2901
  br label %do.body11, !dbg !2902

do.body11:                                        ; preds = %land.end18, %if.end10
  %10 = load i32, i32* %oldfd.addr, align 4, !dbg !2903
  %11 = load i32, i32* %newfd.addr, align 4, !dbg !2904
  %call12 = call i32 @dup2(i32 %10, i32 %11) #9, !dbg !2905
  store i32 %call12, i32* %r, align 4, !dbg !2906
  br label %do.cond13, !dbg !2907

do.cond13:                                        ; preds = %do.body11
  %12 = load i32, i32* %r, align 4, !dbg !2908
  %cmp14 = icmp eq i32 %12, -1, !dbg !2909
  br i1 %cmp14, label %land.rhs15, label %land.end18, !dbg !2910

land.rhs15:                                       ; preds = %do.cond13
  %call16 = call i32* @__errno_location() #2, !dbg !2911
  %13 = load i32, i32* %call16, align 4, !dbg !2911
  %cmp17 = icmp eq i32 %13, 16, !dbg !2913
  br label %land.end18

land.end18:                                       ; preds = %land.rhs15, %do.cond13
  %14 = phi i1 [ false, %do.cond13 ], [ %cmp17, %land.rhs15 ]
  br i1 %14, label %do.body11, label %do.end19, !dbg !2914

do.end19:                                         ; preds = %land.end18
  %15 = load i32, i32* %r, align 4, !dbg !2915
  %cmp20 = icmp eq i32 %15, -1, !dbg !2917
  br i1 %cmp20, label %if.then21, label %if.end24, !dbg !2918

if.then21:                                        ; preds = %do.end19
  %call22 = call i32* @__errno_location() #2, !dbg !2919
  %16 = load i32, i32* %call22, align 4, !dbg !2919
  %sub23 = sub nsw i32 0, %16, !dbg !2920
  store i32 %sub23, i32* %retval, align 4, !dbg !2921
  br label %return, !dbg !2921

if.end24:                                         ; preds = %do.end19
  %17 = load i32, i32* %newfd.addr, align 4, !dbg !2922
  %call25 = call i32 @uv__cloexec_ioctl(i32 %17, i32 1), !dbg !2923
  store i32 %call25, i32* %err, align 4, !dbg !2924
  %18 = load i32, i32* %err, align 4, !dbg !2925
  %tobool26 = icmp ne i32 %18, 0, !dbg !2925
  br i1 %tobool26, label %if.then27, label %if.end29, !dbg !2927

if.then27:                                        ; preds = %if.end24
  %19 = load i32, i32* %newfd.addr, align 4, !dbg !2928
  %call28 = call i32 @uv__close(i32 %19), !dbg !2930
  %20 = load i32, i32* %err, align 4, !dbg !2931
  store i32 %20, i32* %retval, align 4, !dbg !2932
  br label %return, !dbg !2932

if.end29:                                         ; preds = %if.end24
  %21 = load i32, i32* %r, align 4, !dbg !2933
  store i32 %21, i32* %retval, align 4, !dbg !2934
  br label %return, !dbg !2934

return:                                           ; preds = %if.end29, %if.then27, %if.then21, %if.then7, %if.then4
  %22 = load i32, i32* %retval, align 4, !dbg !2935
  ret i32 %22, !dbg !2935
}

declare i32 @uv__dup3(i32, i32, i32) #1

; Function Attrs: nounwind
declare i32 @dup2(i32, i32) #4

; Function Attrs: nounwind uwtable
define i32 @uv_os_homedir(i8* %buffer, i64* %size) #0 !dbg !1095 {
entry:
  %retval = alloca i32, align 4
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %pwd = alloca %struct.uv_passwd_s, align 8
  %buf = alloca i8*, align 8
  %len = alloca i64, align 8
  %r = alloca i32, align 4
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !2936, metadata !1145), !dbg !2937
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !2938, metadata !1145), !dbg !2939
  call void @llvm.dbg.declare(metadata %struct.uv_passwd_s* %pwd, metadata !2940, metadata !1145), !dbg !2941
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !2942, metadata !1145), !dbg !2943
  call void @llvm.dbg.declare(metadata i64* %len, metadata !2944, metadata !1145), !dbg !2945
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2946, metadata !1145), !dbg !2947
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !2948
  %cmp = icmp eq i8* %0, null, !dbg !2950
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2951

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64*, i64** %size.addr, align 8, !dbg !2952
  %cmp1 = icmp eq i64* %1, null, !dbg !2954
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !2955

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64*, i64** %size.addr, align 8, !dbg !2956
  %3 = load i64, i64* %2, align 8, !dbg !2958
  %cmp3 = icmp eq i64 %3, 0, !dbg !2959
  br i1 %cmp3, label %if.then, label %if.end, !dbg !2960

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !2961
  br label %return, !dbg !2961

if.end:                                           ; preds = %lor.lhs.false2
  %call = call i8* @getenv(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0)) #9, !dbg !2962
  store i8* %call, i8** %buf, align 8, !dbg !2963
  %4 = load i8*, i8** %buf, align 8, !dbg !2964
  %cmp4 = icmp ne i8* %4, null, !dbg !2966
  br i1 %cmp4, label %if.then5, label %if.end11, !dbg !2967

if.then5:                                         ; preds = %if.end
  %5 = load i8*, i8** %buf, align 8, !dbg !2968
  %call6 = call i64 @strlen(i8* %5) #10, !dbg !2970
  store i64 %call6, i64* %len, align 8, !dbg !2971
  %6 = load i64, i64* %len, align 8, !dbg !2972
  %7 = load i64*, i64** %size.addr, align 8, !dbg !2974
  %8 = load i64, i64* %7, align 8, !dbg !2975
  %cmp7 = icmp uge i64 %6, %8, !dbg !2976
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !2977

if.then8:                                         ; preds = %if.then5
  %9 = load i64, i64* %len, align 8, !dbg !2978
  %add = add i64 %9, 1, !dbg !2980
  %10 = load i64*, i64** %size.addr, align 8, !dbg !2981
  store i64 %add, i64* %10, align 8, !dbg !2982
  store i32 -105, i32* %retval, align 4, !dbg !2983
  br label %return, !dbg !2983

if.end9:                                          ; preds = %if.then5
  %11 = load i8*, i8** %buffer.addr, align 8, !dbg !2984
  %12 = load i8*, i8** %buf, align 8, !dbg !2985
  %13 = load i64, i64* %len, align 8, !dbg !2986
  %add10 = add i64 %13, 1, !dbg !2987
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* %12, i64 %add10, i32 1, i1 false), !dbg !2988
  %14 = load i64, i64* %len, align 8, !dbg !2989
  %15 = load i64*, i64** %size.addr, align 8, !dbg !2990
  store i64 %14, i64* %15, align 8, !dbg !2991
  store i32 0, i32* %retval, align 4, !dbg !2992
  br label %return, !dbg !2992

if.end11:                                         ; preds = %if.end
  %call12 = call i32 @uv__getpwuid_r(%struct.uv_passwd_s* %pwd), !dbg !2993
  store i32 %call12, i32* %r, align 4, !dbg !2994
  %16 = load i32, i32* %r, align 4, !dbg !2995
  %cmp13 = icmp ne i32 %16, 0, !dbg !2997
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !2998

if.then14:                                        ; preds = %if.end11
  %17 = load i32, i32* %r, align 4, !dbg !2999
  store i32 %17, i32* %retval, align 4, !dbg !3001
  br label %return, !dbg !3001

if.end15:                                         ; preds = %if.end11
  %homedir = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %pwd, i32 0, i32 4, !dbg !3002
  %18 = load i8*, i8** %homedir, align 8, !dbg !3002
  %call16 = call i64 @strlen(i8* %18) #10, !dbg !3003
  store i64 %call16, i64* %len, align 8, !dbg !3004
  %19 = load i64, i64* %len, align 8, !dbg !3005
  %20 = load i64*, i64** %size.addr, align 8, !dbg !3007
  %21 = load i64, i64* %20, align 8, !dbg !3008
  %cmp17 = icmp uge i64 %19, %21, !dbg !3009
  br i1 %cmp17, label %if.then18, label %if.end20, !dbg !3010

if.then18:                                        ; preds = %if.end15
  %22 = load i64, i64* %len, align 8, !dbg !3011
  %add19 = add i64 %22, 1, !dbg !3013
  %23 = load i64*, i64** %size.addr, align 8, !dbg !3014
  store i64 %add19, i64* %23, align 8, !dbg !3015
  call void @uv_os_free_passwd(%struct.uv_passwd_s* %pwd), !dbg !3016
  store i32 -105, i32* %retval, align 4, !dbg !3017
  br label %return, !dbg !3017

if.end20:                                         ; preds = %if.end15
  %24 = load i8*, i8** %buffer.addr, align 8, !dbg !3018
  %homedir21 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %pwd, i32 0, i32 4, !dbg !3019
  %25 = load i8*, i8** %homedir21, align 8, !dbg !3019
  %26 = load i64, i64* %len, align 8, !dbg !3020
  %add22 = add i64 %26, 1, !dbg !3021
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %24, i8* %25, i64 %add22, i32 1, i1 false), !dbg !3022
  %27 = load i64, i64* %len, align 8, !dbg !3023
  %28 = load i64*, i64** %size.addr, align 8, !dbg !3024
  store i64 %27, i64* %28, align 8, !dbg !3025
  call void @uv_os_free_passwd(%struct.uv_passwd_s* %pwd), !dbg !3026
  store i32 0, i32* %retval, align 4, !dbg !3027
  br label %return, !dbg !3027

return:                                           ; preds = %if.end20, %if.then18, %if.then14, %if.end9, %if.then8, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !3028
  ret i32 %29, !dbg !3028
}

; Function Attrs: nounwind
declare i8* @getenv(i8*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #7

; Function Attrs: nounwind uwtable
define i32 @uv__getpwuid_r(%struct.uv_passwd_s* %pwd) #0 !dbg !1097 {
entry:
  %retval = alloca i32, align 4
  %pwd.addr = alloca %struct.uv_passwd_s*, align 8
  %pw = alloca %struct.passwd, align 8
  %result = alloca %struct.passwd*, align 8
  %buf = alloca i8*, align 8
  %uid = alloca i32, align 4
  %bufsize = alloca i64, align 8
  %name_size = alloca i64, align 8
  %homedir_size = alloca i64, align 8
  %shell_size = alloca i64, align 8
  %initsize = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.uv_passwd_s* %pwd, %struct.uv_passwd_s** %pwd.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_passwd_s** %pwd.addr, metadata !3029, metadata !1145), !dbg !3030
  call void @llvm.dbg.declare(metadata %struct.passwd* %pw, metadata !3031, metadata !1145), !dbg !3044
  call void @llvm.dbg.declare(metadata %struct.passwd** %result, metadata !3045, metadata !1145), !dbg !3047
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !3048, metadata !1145), !dbg !3049
  call void @llvm.dbg.declare(metadata i32* %uid, metadata !3050, metadata !1145), !dbg !3053
  call void @llvm.dbg.declare(metadata i64* %bufsize, metadata !3054, metadata !1145), !dbg !3055
  call void @llvm.dbg.declare(metadata i64* %name_size, metadata !3056, metadata !1145), !dbg !3057
  call void @llvm.dbg.declare(metadata i64* %homedir_size, metadata !3058, metadata !1145), !dbg !3059
  call void @llvm.dbg.declare(metadata i64* %shell_size, metadata !3060, metadata !1145), !dbg !3061
  call void @llvm.dbg.declare(metadata i64* %initsize, metadata !3062, metadata !1145), !dbg !3063
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3064, metadata !1145), !dbg !3065
  %0 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3066
  %cmp = icmp eq %struct.uv_passwd_s* %0, null, !dbg !3068
  br i1 %cmp, label %if.then, label %if.end, !dbg !3069

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !3070
  br label %return, !dbg !3070

if.end:                                           ; preds = %entry
  %call = call i64 @sysconf(i32 70) #9, !dbg !3071
  store i64 %call, i64* %initsize, align 8, !dbg !3072
  %1 = load i64, i64* %initsize, align 8, !dbg !3073
  %cmp1 = icmp sle i64 %1, 0, !dbg !3075
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !3076

if.then2:                                         ; preds = %if.end
  store i64 4096, i64* %bufsize, align 8, !dbg !3077
  br label %if.end3, !dbg !3078

if.else:                                          ; preds = %if.end
  %2 = load i64, i64* %initsize, align 8, !dbg !3079
  store i64 %2, i64* %bufsize, align 8, !dbg !3080
  br label %if.end3

if.end3:                                          ; preds = %if.else, %if.then2
  %call4 = call i32 @geteuid() #9, !dbg !3081
  store i32 %call4, i32* %uid, align 4, !dbg !3082
  store i8* null, i8** %buf, align 8, !dbg !3083
  br label %for.cond, !dbg !3084

for.cond:                                         ; preds = %if.end12, %if.end3
  %3 = load i8*, i8** %buf, align 8, !dbg !3085
  call void @uv__free(i8* %3), !dbg !3089
  %4 = load i64, i64* %bufsize, align 8, !dbg !3090
  %call5 = call i8* @uv__malloc(i64 %4), !dbg !3091
  store i8* %call5, i8** %buf, align 8, !dbg !3092
  %5 = load i8*, i8** %buf, align 8, !dbg !3093
  %cmp6 = icmp eq i8* %5, null, !dbg !3095
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !3096

if.then7:                                         ; preds = %for.cond
  store i32 -12, i32* %retval, align 4, !dbg !3097
  br label %return, !dbg !3097

if.end8:                                          ; preds = %for.cond
  %6 = load i32, i32* %uid, align 4, !dbg !3098
  %7 = load i8*, i8** %buf, align 8, !dbg !3099
  %8 = load i64, i64* %bufsize, align 8, !dbg !3100
  %call9 = call i32 @getpwuid_r(i32 %6, %struct.passwd* %pw, i8* %7, i64 %8, %struct.passwd** %result), !dbg !3101
  store i32 %call9, i32* %r, align 4, !dbg !3102
  %9 = load i32, i32* %r, align 4, !dbg !3103
  %cmp10 = icmp ne i32 %9, 34, !dbg !3105
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !3106

if.then11:                                        ; preds = %if.end8
  br label %for.end, !dbg !3107

if.end12:                                         ; preds = %if.end8
  %10 = load i64, i64* %bufsize, align 8, !dbg !3108
  %mul = mul i64 %10, 2, !dbg !3108
  store i64 %mul, i64* %bufsize, align 8, !dbg !3108
  br label %for.cond, !dbg !3109

for.end:                                          ; preds = %if.then11
  %11 = load i32, i32* %r, align 4, !dbg !3111
  %cmp13 = icmp ne i32 %11, 0, !dbg !3113
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !3114

if.then14:                                        ; preds = %for.end
  %12 = load i8*, i8** %buf, align 8, !dbg !3115
  call void @uv__free(i8* %12), !dbg !3117
  %13 = load i32, i32* %r, align 4, !dbg !3118
  %sub = sub nsw i32 0, %13, !dbg !3119
  store i32 %sub, i32* %retval, align 4, !dbg !3120
  br label %return, !dbg !3120

if.end15:                                         ; preds = %for.end
  %14 = load %struct.passwd*, %struct.passwd** %result, align 8, !dbg !3121
  %cmp16 = icmp eq %struct.passwd* %14, null, !dbg !3123
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !3124

if.then17:                                        ; preds = %if.end15
  %15 = load i8*, i8** %buf, align 8, !dbg !3125
  call void @uv__free(i8* %15), !dbg !3127
  store i32 -2, i32* %retval, align 4, !dbg !3128
  br label %return, !dbg !3128

if.end18:                                         ; preds = %if.end15
  %pw_name = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 0, !dbg !3129
  %16 = load i8*, i8** %pw_name, align 8, !dbg !3129
  %call19 = call i64 @strlen(i8* %16) #10, !dbg !3130
  %add = add i64 %call19, 1, !dbg !3131
  store i64 %add, i64* %name_size, align 8, !dbg !3132
  %pw_dir = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 5, !dbg !3133
  %17 = load i8*, i8** %pw_dir, align 8, !dbg !3133
  %call20 = call i64 @strlen(i8* %17) #10, !dbg !3134
  %add21 = add i64 %call20, 1, !dbg !3135
  store i64 %add21, i64* %homedir_size, align 8, !dbg !3136
  %pw_shell = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 6, !dbg !3137
  %18 = load i8*, i8** %pw_shell, align 8, !dbg !3137
  %call22 = call i64 @strlen(i8* %18) #10, !dbg !3138
  %add23 = add i64 %call22, 1, !dbg !3139
  store i64 %add23, i64* %shell_size, align 8, !dbg !3140
  %19 = load i64, i64* %name_size, align 8, !dbg !3141
  %20 = load i64, i64* %homedir_size, align 8, !dbg !3142
  %add24 = add i64 %19, %20, !dbg !3143
  %21 = load i64, i64* %shell_size, align 8, !dbg !3144
  %add25 = add i64 %add24, %21, !dbg !3145
  %call26 = call i8* @uv__malloc(i64 %add25), !dbg !3146
  %22 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3147
  %username = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %22, i32 0, i32 0, !dbg !3148
  store i8* %call26, i8** %username, align 8, !dbg !3149
  %23 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3150
  %username27 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %23, i32 0, i32 0, !dbg !3152
  %24 = load i8*, i8** %username27, align 8, !dbg !3152
  %cmp28 = icmp eq i8* %24, null, !dbg !3153
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !3154

if.then29:                                        ; preds = %if.end18
  %25 = load i8*, i8** %buf, align 8, !dbg !3155
  call void @uv__free(i8* %25), !dbg !3157
  store i32 -12, i32* %retval, align 4, !dbg !3158
  br label %return, !dbg !3158

if.end30:                                         ; preds = %if.end18
  %26 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3159
  %username31 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %26, i32 0, i32 0, !dbg !3160
  %27 = load i8*, i8** %username31, align 8, !dbg !3160
  %pw_name32 = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 0, !dbg !3161
  %28 = load i8*, i8** %pw_name32, align 8, !dbg !3161
  %29 = load i64, i64* %name_size, align 8, !dbg !3162
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %27, i8* %28, i64 %29, i32 1, i1 false), !dbg !3163
  %30 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3164
  %username33 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %30, i32 0, i32 0, !dbg !3165
  %31 = load i8*, i8** %username33, align 8, !dbg !3165
  %32 = load i64, i64* %name_size, align 8, !dbg !3166
  %add.ptr = getelementptr inbounds i8, i8* %31, i64 %32, !dbg !3167
  %33 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3168
  %homedir = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %33, i32 0, i32 4, !dbg !3169
  store i8* %add.ptr, i8** %homedir, align 8, !dbg !3170
  %34 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3171
  %homedir34 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %34, i32 0, i32 4, !dbg !3172
  %35 = load i8*, i8** %homedir34, align 8, !dbg !3172
  %pw_dir35 = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 5, !dbg !3173
  %36 = load i8*, i8** %pw_dir35, align 8, !dbg !3173
  %37 = load i64, i64* %homedir_size, align 8, !dbg !3174
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %35, i8* %36, i64 %37, i32 1, i1 false), !dbg !3175
  %38 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3176
  %homedir36 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %38, i32 0, i32 4, !dbg !3177
  %39 = load i8*, i8** %homedir36, align 8, !dbg !3177
  %40 = load i64, i64* %homedir_size, align 8, !dbg !3178
  %add.ptr37 = getelementptr inbounds i8, i8* %39, i64 %40, !dbg !3179
  %41 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3180
  %shell = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %41, i32 0, i32 3, !dbg !3181
  store i8* %add.ptr37, i8** %shell, align 8, !dbg !3182
  %42 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3183
  %shell38 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %42, i32 0, i32 3, !dbg !3184
  %43 = load i8*, i8** %shell38, align 8, !dbg !3184
  %pw_shell39 = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 6, !dbg !3185
  %44 = load i8*, i8** %pw_shell39, align 8, !dbg !3185
  %45 = load i64, i64* %shell_size, align 8, !dbg !3186
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %43, i8* %44, i64 %45, i32 1, i1 false), !dbg !3187
  %pw_uid = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 2, !dbg !3188
  %46 = load i32, i32* %pw_uid, align 8, !dbg !3188
  %conv = zext i32 %46 to i64, !dbg !3189
  %47 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3190
  %uid40 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %47, i32 0, i32 1, !dbg !3191
  store i64 %conv, i64* %uid40, align 8, !dbg !3192
  %pw_gid = getelementptr inbounds %struct.passwd, %struct.passwd* %pw, i32 0, i32 3, !dbg !3193
  %48 = load i32, i32* %pw_gid, align 4, !dbg !3193
  %conv41 = zext i32 %48 to i64, !dbg !3194
  %49 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3195
  %gid = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %49, i32 0, i32 2, !dbg !3196
  store i64 %conv41, i64* %gid, align 8, !dbg !3197
  %50 = load i8*, i8** %buf, align 8, !dbg !3198
  call void @uv__free(i8* %50), !dbg !3199
  store i32 0, i32* %retval, align 4, !dbg !3200
  br label %return, !dbg !3200

return:                                           ; preds = %if.end30, %if.then29, %if.then17, %if.then14, %if.then7, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !3201
  ret i32 %51, !dbg !3201
}

; Function Attrs: nounwind uwtable
define void @uv_os_free_passwd(%struct.uv_passwd_s* %pwd) #0 !dbg !1109 {
entry:
  %pwd.addr = alloca %struct.uv_passwd_s*, align 8
  store %struct.uv_passwd_s* %pwd, %struct.uv_passwd_s** %pwd.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_passwd_s** %pwd.addr, metadata !3202, metadata !1145), !dbg !3203
  %0 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3204
  %cmp = icmp eq %struct.uv_passwd_s* %0, null, !dbg !3206
  br i1 %cmp, label %if.then, label %if.end, !dbg !3207

if.then:                                          ; preds = %entry
  br label %return, !dbg !3208

if.end:                                           ; preds = %entry
  %1 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3209
  %username = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %1, i32 0, i32 0, !dbg !3210
  %2 = load i8*, i8** %username, align 8, !dbg !3210
  call void @uv__free(i8* %2), !dbg !3211
  %3 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3212
  %username1 = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %3, i32 0, i32 0, !dbg !3213
  store i8* null, i8** %username1, align 8, !dbg !3214
  %4 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3215
  %shell = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %4, i32 0, i32 3, !dbg !3216
  store i8* null, i8** %shell, align 8, !dbg !3217
  %5 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3218
  %homedir = getelementptr inbounds %struct.uv_passwd_s, %struct.uv_passwd_s* %5, i32 0, i32 4, !dbg !3219
  store i8* null, i8** %homedir, align 8, !dbg !3220
  br label %return, !dbg !3221

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !3222
}

; Function Attrs: nounwind uwtable
define i32 @uv_os_tmpdir(i8* %buffer, i64* %size) #0 !dbg !1096 {
entry:
  %retval = alloca i32, align 4
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %buf = alloca i8*, align 8
  %len = alloca i64, align 8
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !3224, metadata !1145), !dbg !3225
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !3226, metadata !1145), !dbg !3227
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !3228, metadata !1145), !dbg !3229
  call void @llvm.dbg.declare(metadata i64* %len, metadata !3230, metadata !1145), !dbg !3231
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !3232
  %cmp = icmp eq i8* %0, null, !dbg !3234
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3235

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64*, i64** %size.addr, align 8, !dbg !3236
  %cmp1 = icmp eq i64* %1, null, !dbg !3238
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !3239

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64*, i64** %size.addr, align 8, !dbg !3240
  %3 = load i64, i64* %2, align 8, !dbg !3242
  %cmp3 = icmp eq i64 %3, 0, !dbg !3243
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3244

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !3245
  br label %return, !dbg !3245

if.end:                                           ; preds = %lor.lhs.false2
  br label %do.body, !dbg !3246

do.body:                                          ; preds = %if.end
  %call = call i8* @getenv(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.18, i32 0, i32 0)) #9, !dbg !3247
  store i8* %call, i8** %buf, align 8, !dbg !3247
  %4 = load i8*, i8** %buf, align 8, !dbg !3247
  %cmp4 = icmp ne i8* %4, null, !dbg !3247
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !3247

if.then5:                                         ; preds = %do.body
  br label %return_buffer, !dbg !3250

if.end6:                                          ; preds = %do.body
  br label %do.end, !dbg !3253

do.end:                                           ; preds = %if.end6
  br label %do.body7, !dbg !3255

do.body7:                                         ; preds = %do.end
  %call8 = call i8* @getenv(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.19, i32 0, i32 0)) #9, !dbg !3256
  store i8* %call8, i8** %buf, align 8, !dbg !3256
  %5 = load i8*, i8** %buf, align 8, !dbg !3256
  %cmp9 = icmp ne i8* %5, null, !dbg !3256
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !3256

if.then10:                                        ; preds = %do.body7
  br label %return_buffer, !dbg !3259

if.end11:                                         ; preds = %do.body7
  br label %do.end12, !dbg !3262

do.end12:                                         ; preds = %if.end11
  br label %do.body13, !dbg !3264

do.body13:                                        ; preds = %do.end12
  %call14 = call i8* @getenv(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i32 0, i32 0)) #9, !dbg !3265
  store i8* %call14, i8** %buf, align 8, !dbg !3265
  %6 = load i8*, i8** %buf, align 8, !dbg !3265
  %cmp15 = icmp ne i8* %6, null, !dbg !3265
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !3265

if.then16:                                        ; preds = %do.body13
  br label %return_buffer, !dbg !3268

if.end17:                                         ; preds = %do.body13
  br label %do.end18, !dbg !3271

do.end18:                                         ; preds = %if.end17
  br label %do.body19, !dbg !3273

do.body19:                                        ; preds = %do.end18
  %call20 = call i8* @getenv(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.21, i32 0, i32 0)) #9, !dbg !3274
  store i8* %call20, i8** %buf, align 8, !dbg !3274
  %7 = load i8*, i8** %buf, align 8, !dbg !3274
  %cmp21 = icmp ne i8* %7, null, !dbg !3274
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !3274

if.then22:                                        ; preds = %do.body19
  br label %return_buffer, !dbg !3277

if.end23:                                         ; preds = %do.body19
  br label %do.end24, !dbg !3280

do.end24:                                         ; preds = %if.end23
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i32 0, i32 0), i8** %buf, align 8, !dbg !3282
  br label %return_buffer, !dbg !3283

return_buffer:                                    ; preds = %do.end24, %if.then22, %if.then16, %if.then10, %if.then5
  %8 = load i8*, i8** %buf, align 8, !dbg !3284
  %call25 = call i64 @strlen(i8* %8) #10, !dbg !3285
  store i64 %call25, i64* %len, align 8, !dbg !3286
  %9 = load i64, i64* %len, align 8, !dbg !3287
  %10 = load i64*, i64** %size.addr, align 8, !dbg !3289
  %11 = load i64, i64* %10, align 8, !dbg !3290
  %cmp26 = icmp uge i64 %9, %11, !dbg !3291
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !3292

if.then27:                                        ; preds = %return_buffer
  %12 = load i64, i64* %len, align 8, !dbg !3293
  %add = add i64 %12, 1, !dbg !3295
  %13 = load i64*, i64** %size.addr, align 8, !dbg !3296
  store i64 %add, i64* %13, align 8, !dbg !3297
  store i32 -105, i32* %retval, align 4, !dbg !3298
  br label %return, !dbg !3298

if.end28:                                         ; preds = %return_buffer
  %14 = load i64, i64* %len, align 8, !dbg !3299
  %cmp29 = icmp ugt i64 %14, 1, !dbg !3301
  br i1 %cmp29, label %land.lhs.true, label %if.end33, !dbg !3302

land.lhs.true:                                    ; preds = %if.end28
  %15 = load i64, i64* %len, align 8, !dbg !3303
  %sub = sub i64 %15, 1, !dbg !3305
  %16 = load i8*, i8** %buf, align 8, !dbg !3306
  %arrayidx = getelementptr inbounds i8, i8* %16, i64 %sub, !dbg !3306
  %17 = load i8, i8* %arrayidx, align 1, !dbg !3306
  %conv = sext i8 %17 to i32, !dbg !3306
  %cmp30 = icmp eq i32 %conv, 47, !dbg !3307
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !3308

if.then32:                                        ; preds = %land.lhs.true
  %18 = load i64, i64* %len, align 8, !dbg !3309
  %dec = add i64 %18, -1, !dbg !3309
  store i64 %dec, i64* %len, align 8, !dbg !3309
  br label %if.end33, !dbg !3311

if.end33:                                         ; preds = %if.then32, %land.lhs.true, %if.end28
  %19 = load i8*, i8** %buffer.addr, align 8, !dbg !3312
  %20 = load i8*, i8** %buf, align 8, !dbg !3313
  %21 = load i64, i64* %len, align 8, !dbg !3314
  %add34 = add i64 %21, 1, !dbg !3315
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* %20, i64 %add34, i32 1, i1 false), !dbg !3316
  %22 = load i64, i64* %len, align 8, !dbg !3317
  %23 = load i8*, i8** %buffer.addr, align 8, !dbg !3318
  %arrayidx35 = getelementptr inbounds i8, i8* %23, i64 %22, !dbg !3318
  store i8 0, i8* %arrayidx35, align 1, !dbg !3319
  %24 = load i64, i64* %len, align 8, !dbg !3320
  %25 = load i64*, i64** %size.addr, align 8, !dbg !3321
  store i64 %24, i64* %25, align 8, !dbg !3322
  store i32 0, i32* %retval, align 4, !dbg !3323
  br label %return, !dbg !3323

return:                                           ; preds = %if.end33, %if.then27, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !3324
  ret i32 %26, !dbg !3324
}

; Function Attrs: nounwind
declare i64 @sysconf(i32) #4

; Function Attrs: nounwind
declare i32 @geteuid() #4

declare void @uv__free(i8*) #1

declare i8* @uv__malloc(i64) #1

declare i32 @getpwuid_r(i32, %struct.passwd*, i8*, i64, %struct.passwd**) #1

; Function Attrs: nounwind uwtable
define i32 @uv_os_get_passwd(%struct.uv_passwd_s* %pwd) #0 !dbg !1112 {
entry:
  %pwd.addr = alloca %struct.uv_passwd_s*, align 8
  store %struct.uv_passwd_s* %pwd, %struct.uv_passwd_s** %pwd.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_passwd_s** %pwd.addr, metadata !3325, metadata !1145), !dbg !3326
  %0 = load %struct.uv_passwd_s*, %struct.uv_passwd_s** %pwd.addr, align 8, !dbg !3327
  %call = call i32 @uv__getpwuid_r(%struct.uv_passwd_s* %0), !dbg !3328
  ret i32 %call, !dbg !3329
}

; Function Attrs: nounwind uwtable
define i32 @uv_translate_sys_error(i32 %sys_errno) #0 !dbg !1113 {
entry:
  %sys_errno.addr = alloca i32, align 4
  store i32 %sys_errno, i32* %sys_errno.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sys_errno.addr, metadata !3330, metadata !1145), !dbg !3331
  %0 = load i32, i32* %sys_errno.addr, align 4, !dbg !3332
  %cmp = icmp sle i32 %0, 0, !dbg !3333
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3332

cond.true:                                        ; preds = %entry
  %1 = load i32, i32* %sys_errno.addr, align 4, !dbg !3334
  br label %cond.end, !dbg !3336

cond.false:                                       ; preds = %entry
  %2 = load i32, i32* %sys_errno.addr, align 4, !dbg !3337
  %sub = sub nsw i32 0, %2, !dbg !3339
  br label %cond.end, !dbg !3340

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %1, %cond.true ], [ %sub, %cond.false ], !dbg !3341
  ret i32 %cond, !dbg !3343
}

; Function Attrs: nounwind uwtable
define i32 @uv_os_getenv(i8* %name, i8* %buffer, i64* %size) #0 !dbg !1114 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %var = alloca i8*, align 8
  %len = alloca i64, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3344, metadata !1145), !dbg !3345
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !3346, metadata !1145), !dbg !3347
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !3348, metadata !1145), !dbg !3349
  call void @llvm.dbg.declare(metadata i8** %var, metadata !3350, metadata !1145), !dbg !3351
  call void @llvm.dbg.declare(metadata i64* %len, metadata !3352, metadata !1145), !dbg !3353
  %0 = load i8*, i8** %name.addr, align 8, !dbg !3354
  %cmp = icmp eq i8* %0, null, !dbg !3356
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3357

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %buffer.addr, align 8, !dbg !3358
  %cmp1 = icmp eq i8* %1, null, !dbg !3360
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !3361

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64*, i64** %size.addr, align 8, !dbg !3362
  %cmp3 = icmp eq i64* %2, null, !dbg !3364
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !3365

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i64*, i64** %size.addr, align 8, !dbg !3366
  %4 = load i64, i64* %3, align 8, !dbg !3368
  %cmp5 = icmp eq i64 %4, 0, !dbg !3369
  br i1 %cmp5, label %if.then, label %if.end, !dbg !3370

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !3371
  br label %return, !dbg !3371

if.end:                                           ; preds = %lor.lhs.false4
  %5 = load i8*, i8** %name.addr, align 8, !dbg !3372
  %call = call i8* @getenv(i8* %5) #9, !dbg !3373
  store i8* %call, i8** %var, align 8, !dbg !3374
  %6 = load i8*, i8** %var, align 8, !dbg !3375
  %cmp6 = icmp eq i8* %6, null, !dbg !3377
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !3378

if.then7:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !3379
  br label %return, !dbg !3379

if.end8:                                          ; preds = %if.end
  %7 = load i8*, i8** %var, align 8, !dbg !3380
  %call9 = call i64 @strlen(i8* %7) #10, !dbg !3381
  store i64 %call9, i64* %len, align 8, !dbg !3382
  %8 = load i64, i64* %len, align 8, !dbg !3383
  %9 = load i64*, i64** %size.addr, align 8, !dbg !3385
  %10 = load i64, i64* %9, align 8, !dbg !3386
  %cmp10 = icmp uge i64 %8, %10, !dbg !3387
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !3388

if.then11:                                        ; preds = %if.end8
  %11 = load i64, i64* %len, align 8, !dbg !3389
  %add = add i64 %11, 1, !dbg !3391
  %12 = load i64*, i64** %size.addr, align 8, !dbg !3392
  store i64 %add, i64* %12, align 8, !dbg !3393
  store i32 -105, i32* %retval, align 4, !dbg !3394
  br label %return, !dbg !3394

if.end12:                                         ; preds = %if.end8
  %13 = load i8*, i8** %buffer.addr, align 8, !dbg !3395
  %14 = load i8*, i8** %var, align 8, !dbg !3396
  %15 = load i64, i64* %len, align 8, !dbg !3397
  %add13 = add i64 %15, 1, !dbg !3398
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* %14, i64 %add13, i32 1, i1 false), !dbg !3399
  %16 = load i64, i64* %len, align 8, !dbg !3400
  %17 = load i64*, i64** %size.addr, align 8, !dbg !3401
  store i64 %16, i64* %17, align 8, !dbg !3402
  store i32 0, i32* %retval, align 4, !dbg !3403
  br label %return, !dbg !3403

return:                                           ; preds = %if.end12, %if.then11, %if.then7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !3404
  ret i32 %18, !dbg !3404
}

; Function Attrs: nounwind uwtable
define i32 @uv_os_setenv(i8* %name, i8* %value) #0 !dbg !1117 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3405, metadata !1145), !dbg !3406
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3407, metadata !1145), !dbg !3408
  %0 = load i8*, i8** %name.addr, align 8, !dbg !3409
  %cmp = icmp eq i8* %0, null, !dbg !3411
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3412

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %value.addr, align 8, !dbg !3413
  %cmp1 = icmp eq i8* %1, null, !dbg !3415
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3416

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !3417
  br label %return, !dbg !3417

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i8*, i8** %name.addr, align 8, !dbg !3418
  %3 = load i8*, i8** %value.addr, align 8, !dbg !3420
  %call = call i32 @setenv(i8* %2, i8* %3, i32 1) #9, !dbg !3421
  %cmp2 = icmp ne i32 %call, 0, !dbg !3422
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !3423

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__errno_location() #2, !dbg !3424
  %4 = load i32, i32* %call4, align 4, !dbg !3424
  %sub = sub nsw i32 0, %4, !dbg !3425
  store i32 %sub, i32* %retval, align 4, !dbg !3426
  br label %return, !dbg !3426

if.end5:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !3427
  br label %return, !dbg !3427

return:                                           ; preds = %if.end5, %if.then3, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !3428
  ret i32 %5, !dbg !3428
}

; Function Attrs: nounwind
declare i32 @setenv(i8*, i8*, i32) #4

; Function Attrs: nounwind uwtable
define i32 @uv_os_unsetenv(i8* %name) #0 !dbg !1120 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3429, metadata !1145), !dbg !3430
  %0 = load i8*, i8** %name.addr, align 8, !dbg !3431
  %call = call i32 @unsetenv(i8* %0) #9, !dbg !3433
  %cmp = icmp ne i32 %call, 0, !dbg !3434
  br i1 %cmp, label %if.then, label %if.end, !dbg !3435

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #2, !dbg !3436
  %1 = load i32, i32* %call1, align 4, !dbg !3436
  %sub = sub nsw i32 0, %1, !dbg !3437
  store i32 %sub, i32* %retval, align 4, !dbg !3438
  br label %return, !dbg !3438

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3439
  br label %return, !dbg !3439

return:                                           ; preds = %if.end, %if.then
  %2 = load i32, i32* %retval, align 4, !dbg !3440
  ret i32 %2, !dbg !3440
}

; Function Attrs: nounwind
declare i32 @unsetenv(i8*) #4

; Function Attrs: nounwind uwtable
define internal void @uv__finish_close(%struct.uv_handle_s* %handle) #0 !dbg !1124 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !3441, metadata !1145), !dbg !3442
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3443
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 7, !dbg !3443
  %1 = load i32, i32* %flags, align 8, !dbg !3443
  %and = and i32 %1, 1, !dbg !3443
  %tobool = icmp ne i32 %and, 0, !dbg !3443
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !3443

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !3444

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 234, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.uv__finish_close, i32 0, i32 0)) #8, !dbg !3446
  unreachable, !dbg !3446
                                                  ; No predecessors!
  br label %cond.end, !dbg !3448

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3450
  %flags1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %3, i32 0, i32 7, !dbg !3450
  %4 = load i32, i32* %flags1, align 8, !dbg !3450
  %and2 = and i32 %4, 2, !dbg !3450
  %tobool3 = icmp ne i32 %and2, 0, !dbg !3450
  br i1 %tobool3, label %cond.false5, label %cond.true4, !dbg !3450

cond.true4:                                       ; preds = %cond.end
  br label %cond.end6, !dbg !3451

cond.false5:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 235, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.uv__finish_close, i32 0, i32 0)) #8, !dbg !3452
  unreachable, !dbg !3452
                                                  ; No predecessors!
  br label %cond.end6, !dbg !3453

cond.end6:                                        ; preds = %5, %cond.true4
  %6 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3454
  %flags7 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !3455
  %7 = load i32, i32* %flags7, align 8, !dbg !3456
  %or = or i32 %7, 2, !dbg !3456
  store i32 %or, i32* %flags7, align 8, !dbg !3456
  %8 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3457
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %8, i32 0, i32 2, !dbg !3458
  %9 = load i32, i32* %type, align 8, !dbg !3458
  switch i32 %9, label %sw.default [
    i32 9, label %sw.bb
    i32 2, label %sw.bb
    i32 6, label %sw.bb
    i32 1, label %sw.bb
    i32 13, label %sw.bb
    i32 10, label %sw.bb
    i32 3, label %sw.bb
    i32 4, label %sw.bb
    i32 8, label %sw.bb
    i32 16, label %sw.bb
    i32 7, label %sw.bb8
    i32 12, label %sw.bb8
    i32 14, label %sw.bb8
    i32 15, label %sw.bb9
  ], !dbg !3459

sw.bb:                                            ; preds = %cond.end6, %cond.end6, %cond.end6, %cond.end6, %cond.end6, %cond.end6, %cond.end6, %cond.end6, %cond.end6, %cond.end6
  br label %sw.epilog, !dbg !3460

sw.bb8:                                           ; preds = %cond.end6, %cond.end6, %cond.end6
  %10 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3462
  %11 = bitcast %struct.uv_handle_s* %10 to %struct.uv_stream_s*, !dbg !3463
  call void @uv__stream_destroy(%struct.uv_stream_s* %11), !dbg !3464
  br label %sw.epilog, !dbg !3465

sw.bb9:                                           ; preds = %cond.end6
  %12 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3466
  %13 = bitcast %struct.uv_handle_s* %12 to %struct.uv_udp_s*, !dbg !3467
  call void @uv__udp_finish_close(%struct.uv_udp_s* %13), !dbg !3468
  br label %sw.epilog, !dbg !3469

sw.default:                                       ; preds = %cond.end6
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 262, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.uv__finish_close, i32 0, i32 0)) #8, !dbg !3470
  unreachable, !dbg !3470

sw.epilog:                                        ; preds = %sw.bb9, %sw.bb8, %sw.bb
  br label %do.body, !dbg !3471

do.body:                                          ; preds = %sw.epilog
  %14 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3472
  %flags10 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %14, i32 0, i32 7, !dbg !3472
  %15 = load i32, i32* %flags10, align 8, !dbg !3472
  %and11 = and i32 %15, 8192, !dbg !3472
  %cmp = icmp eq i32 %and11, 0, !dbg !3472
  br i1 %cmp, label %if.then, label %if.end, !dbg !3472

if.then:                                          ; preds = %do.body
  br label %do.end25, !dbg !3476

if.end:                                           ; preds = %do.body
  %16 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3478
  %flags12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %16, i32 0, i32 7, !dbg !3478
  %17 = load i32, i32* %flags12, align 8, !dbg !3478
  %and13 = and i32 %17, -8193, !dbg !3478
  store i32 %and13, i32* %flags12, align 8, !dbg !3478
  %18 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3478
  %flags14 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 7, !dbg !3478
  %19 = load i32, i32* %flags14, align 8, !dbg !3478
  %and15 = and i32 %19, 0, !dbg !3478
  %cmp16 = icmp ne i32 %and15, 0, !dbg !3478
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !3478

if.then17:                                        ; preds = %if.end
  br label %do.end25, !dbg !3480

if.end18:                                         ; preds = %if.end
  %20 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3483
  %flags19 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 7, !dbg !3483
  %21 = load i32, i32* %flags19, align 8, !dbg !3483
  %and20 = and i32 %21, 16384, !dbg !3483
  %cmp21 = icmp ne i32 %and20, 0, !dbg !3483
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !3483

if.then22:                                        ; preds = %if.end18
  br label %do.body23, !dbg !3486

do.body23:                                        ; preds = %if.then22
  %22 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3488
  %loop = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %22, i32 0, i32 1, !dbg !3488
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !3488
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 1, !dbg !3488
  %24 = load i32, i32* %active_handles, align 8, !dbg !3488
  %dec = add i32 %24, -1, !dbg !3488
  store i32 %dec, i32* %active_handles, align 8, !dbg !3488
  br label %do.end, !dbg !3488

do.end:                                           ; preds = %do.body23
  br label %if.end24, !dbg !3491

if.end24:                                         ; preds = %do.end, %if.end18
  br label %do.end25, !dbg !3493

do.end25:                                         ; preds = %if.end24, %if.then17, %if.then
  br label %do.body26, !dbg !3495

do.body26:                                        ; preds = %do.end25
  %25 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3496
  %handle_queue = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !3496
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue, i64 0, i64 0, !dbg !3496
  %26 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !3496
  %27 = load [2 x i8*]*, [2 x i8*]** %26, align 8, !dbg !3496
  %28 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3496
  %handle_queue27 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %28, i32 0, i32 4, !dbg !3496
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue27, i64 0, i64 1, !dbg !3496
  %29 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !3496
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !3496
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %30, i64 0, i64 0, !dbg !3496
  %31 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !3496
  store [2 x i8*]* %27, [2 x i8*]** %31, align 8, !dbg !3496
  %32 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3496
  %handle_queue30 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %32, i32 0, i32 4, !dbg !3496
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue30, i64 0, i64 1, !dbg !3496
  %33 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !3496
  %34 = load [2 x i8*]*, [2 x i8*]** %33, align 8, !dbg !3496
  %35 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3496
  %handle_queue32 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %35, i32 0, i32 4, !dbg !3496
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue32, i64 0, i64 0, !dbg !3496
  %36 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !3496
  %37 = load [2 x i8*]*, [2 x i8*]** %36, align 8, !dbg !3496
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 1, !dbg !3496
  %38 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !3496
  store [2 x i8*]* %34, [2 x i8*]** %38, align 8, !dbg !3496
  br label %do.end35, !dbg !3496

do.end35:                                         ; preds = %do.body26
  %39 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3499
  %close_cb = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %39, i32 0, i32 3, !dbg !3501
  %40 = load void (%struct.uv_handle_s*)*, void (%struct.uv_handle_s*)** %close_cb, align 8, !dbg !3501
  %tobool36 = icmp ne void (%struct.uv_handle_s*)* %40, null, !dbg !3499
  br i1 %tobool36, label %if.then37, label %if.end39, !dbg !3502

if.then37:                                        ; preds = %do.end35
  %41 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3503
  %close_cb38 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %41, i32 0, i32 3, !dbg !3505
  %42 = load void (%struct.uv_handle_s*)*, void (%struct.uv_handle_s*)** %close_cb38, align 8, !dbg !3505
  %43 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !3506
  call void %42(%struct.uv_handle_s* %43), !dbg !3503
  br label %if.end39, !dbg !3507

if.end39:                                         ; preds = %if.then37, %do.end35
  ret void, !dbg !3508
}

declare void @uv__stream_destroy(%struct.uv_stream_s*) #1

declare void @uv__udp_finish_close(%struct.uv_udp_s*) #1

; Function Attrs: nounwind uwtable
define internal i32 @next_power_of_two(i32 %val) #0 !dbg !1131 {
entry:
  %val.addr = alloca i32, align 4
  store i32 %val, i32* %val.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %val.addr, metadata !3509, metadata !1145), !dbg !3510
  %0 = load i32, i32* %val.addr, align 4, !dbg !3511
  %sub = sub i32 %0, 1, !dbg !3511
  store i32 %sub, i32* %val.addr, align 4, !dbg !3511
  %1 = load i32, i32* %val.addr, align 4, !dbg !3512
  %shr = lshr i32 %1, 1, !dbg !3513
  %2 = load i32, i32* %val.addr, align 4, !dbg !3514
  %or = or i32 %2, %shr, !dbg !3514
  store i32 %or, i32* %val.addr, align 4, !dbg !3514
  %3 = load i32, i32* %val.addr, align 4, !dbg !3515
  %shr1 = lshr i32 %3, 2, !dbg !3516
  %4 = load i32, i32* %val.addr, align 4, !dbg !3517
  %or2 = or i32 %4, %shr1, !dbg !3517
  store i32 %or2, i32* %val.addr, align 4, !dbg !3517
  %5 = load i32, i32* %val.addr, align 4, !dbg !3518
  %shr3 = lshr i32 %5, 4, !dbg !3519
  %6 = load i32, i32* %val.addr, align 4, !dbg !3520
  %or4 = or i32 %6, %shr3, !dbg !3520
  store i32 %or4, i32* %val.addr, align 4, !dbg !3520
  %7 = load i32, i32* %val.addr, align 4, !dbg !3521
  %shr5 = lshr i32 %7, 8, !dbg !3522
  %8 = load i32, i32* %val.addr, align 4, !dbg !3523
  %or6 = or i32 %8, %shr5, !dbg !3523
  store i32 %or6, i32* %val.addr, align 4, !dbg !3523
  %9 = load i32, i32* %val.addr, align 4, !dbg !3524
  %shr7 = lshr i32 %9, 16, !dbg !3525
  %10 = load i32, i32* %val.addr, align 4, !dbg !3526
  %or8 = or i32 %10, %shr7, !dbg !3526
  store i32 %or8, i32* %val.addr, align 4, !dbg !3526
  %11 = load i32, i32* %val.addr, align 4, !dbg !3527
  %add = add i32 %11, 1, !dbg !3527
  store i32 %add, i32* %val.addr, align 4, !dbg !3527
  %12 = load i32, i32* %val.addr, align 4, !dbg !3528
  ret i32 %12, !dbg !3529
}

declare i8* @uv__realloc(i8*, i64) #1

; Function Attrs: noreturn nounwind
declare void @abort() #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { argmemonly nounwind }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }
attributes #10 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1139, !1140}
!llvm.ident = !{!1141}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !315, subprograms: !908, globals: !1134)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/core.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !8, !30, !48, !61, !66, !74, !86, !91, !97}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 148, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7}
!6 = !DIEnumerator(name: "UV_CLOCK_PRECISE", value: 0)
!7 = !DIEnumerator(name: "UV_CLOCK_FAST", value: 1)
!8 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !9, line: 184, size: 32, align: 32, elements: !10)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!10 = !{!11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29}
!11 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!12 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!13 = !DIEnumerator(name: "UV_CHECK", value: 2)
!14 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!15 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!16 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!17 = !DIEnumerator(name: "UV_IDLE", value: 6)
!18 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!19 = !DIEnumerator(name: "UV_POLL", value: 8)
!20 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!21 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!22 = !DIEnumerator(name: "UV_STREAM", value: 11)
!23 = !DIEnumerator(name: "UV_TCP", value: 12)
!24 = !DIEnumerator(name: "UV_TIMER", value: 13)
!25 = !DIEnumerator(name: "UV_TTY", value: 14)
!26 = !DIEnumerator(name: "UV_UDP", value: 15)
!27 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!28 = !DIEnumerator(name: "UV_FILE", value: 17)
!29 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!30 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 124, size: 32, align: 32, elements: !31)
!31 = !{!32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47}
!32 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!33 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!34 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!35 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!36 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!37 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!38 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!39 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!40 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!41 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!42 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!43 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!44 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!45 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!46 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!47 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!48 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !9, line: 193, size: 32, align: 32, elements: !49)
!49 = !{!50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60}
!50 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!51 = !DIEnumerator(name: "UV_REQ", value: 1)
!52 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!53 = !DIEnumerator(name: "UV_WRITE", value: 3)
!54 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!55 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!56 = !DIEnumerator(name: "UV_FS", value: 6)
!57 = !DIEnumerator(name: "UV_WORK", value: 7)
!58 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!59 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!60 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!61 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !9, line: 243, size: 32, align: 32, elements: !62)
!62 = !{!63, !64, !65}
!63 = !DIEnumerator(name: "UV_RUN_DEFAULT", value: 0)
!64 = !DIEnumerator(name: "UV_RUN_ONCE", value: 1)
!65 = !DIEnumerator(name: "UV_RUN_NOWAIT", value: 2)
!66 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !67, line: 57, size: 32, align: 32, elements: !68)
!67 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!68 = !{!69, !70, !71, !72, !73}
!69 = !DIEnumerator(name: "UV__SIGNAL_ONE_SHOT", value: 524288)
!70 = !DIEnumerator(name: "UV__HANDLE_INTERNAL", value: 32768)
!71 = !DIEnumerator(name: "UV__HANDLE_ACTIVE", value: 16384)
!72 = !DIEnumerator(name: "UV__HANDLE_REF", value: 8192)
!73 = !DIEnumerator(name: "UV__HANDLE_CLOSING", value: 0)
!74 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !75, line: 24, size: 32, align: 32, elements: !76)
!75 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!76 = !{!77, !78, !79, !80, !81, !82, !83, !84, !85}
!77 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!78 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!79 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!80 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!81 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!82 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!83 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!84 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!85 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!86 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !87, line: 299, size: 32, align: 32, elements: !88)
!87 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!88 = !{!89, !90}
!89 = !DIEnumerator(name: "SCM_RIGHTS", value: 1)
!90 = !DIEnumerator(name: "SCM_CREDENTIALS", value: 2)
!91 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__rusage_who", file: !92, line: 158, size: 32, align: 32, elements: !93)
!92 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/resource.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!93 = !{!94, !95, !96}
!94 = !DIEnumerator(name: "RUSAGE_SELF", value: 0)
!95 = !DIEnumerator(name: "RUSAGE_CHILDREN", value: -1)
!96 = !DIEnumerator(name: "RUSAGE_THREAD", value: 1)
!97 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !98, line: 71, size: 32, align: 32, elements: !99)
!98 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/confname.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!99 = !{!100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191, !192, !193, !194, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249, !250, !251, !252, !253, !254, !255, !256, !257, !258, !259, !260, !261, !262, !263, !264, !265, !266, !267, !268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287, !288, !289, !290, !291, !292, !293, !294, !295, !296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !314}
!100 = !DIEnumerator(name: "_SC_ARG_MAX", value: 0)
!101 = !DIEnumerator(name: "_SC_CHILD_MAX", value: 1)
!102 = !DIEnumerator(name: "_SC_CLK_TCK", value: 2)
!103 = !DIEnumerator(name: "_SC_NGROUPS_MAX", value: 3)
!104 = !DIEnumerator(name: "_SC_OPEN_MAX", value: 4)
!105 = !DIEnumerator(name: "_SC_STREAM_MAX", value: 5)
!106 = !DIEnumerator(name: "_SC_TZNAME_MAX", value: 6)
!107 = !DIEnumerator(name: "_SC_JOB_CONTROL", value: 7)
!108 = !DIEnumerator(name: "_SC_SAVED_IDS", value: 8)
!109 = !DIEnumerator(name: "_SC_REALTIME_SIGNALS", value: 9)
!110 = !DIEnumerator(name: "_SC_PRIORITY_SCHEDULING", value: 10)
!111 = !DIEnumerator(name: "_SC_TIMERS", value: 11)
!112 = !DIEnumerator(name: "_SC_ASYNCHRONOUS_IO", value: 12)
!113 = !DIEnumerator(name: "_SC_PRIORITIZED_IO", value: 13)
!114 = !DIEnumerator(name: "_SC_SYNCHRONIZED_IO", value: 14)
!115 = !DIEnumerator(name: "_SC_FSYNC", value: 15)
!116 = !DIEnumerator(name: "_SC_MAPPED_FILES", value: 16)
!117 = !DIEnumerator(name: "_SC_MEMLOCK", value: 17)
!118 = !DIEnumerator(name: "_SC_MEMLOCK_RANGE", value: 18)
!119 = !DIEnumerator(name: "_SC_MEMORY_PROTECTION", value: 19)
!120 = !DIEnumerator(name: "_SC_MESSAGE_PASSING", value: 20)
!121 = !DIEnumerator(name: "_SC_SEMAPHORES", value: 21)
!122 = !DIEnumerator(name: "_SC_SHARED_MEMORY_OBJECTS", value: 22)
!123 = !DIEnumerator(name: "_SC_AIO_LISTIO_MAX", value: 23)
!124 = !DIEnumerator(name: "_SC_AIO_MAX", value: 24)
!125 = !DIEnumerator(name: "_SC_AIO_PRIO_DELTA_MAX", value: 25)
!126 = !DIEnumerator(name: "_SC_DELAYTIMER_MAX", value: 26)
!127 = !DIEnumerator(name: "_SC_MQ_OPEN_MAX", value: 27)
!128 = !DIEnumerator(name: "_SC_MQ_PRIO_MAX", value: 28)
!129 = !DIEnumerator(name: "_SC_VERSION", value: 29)
!130 = !DIEnumerator(name: "_SC_PAGESIZE", value: 30)
!131 = !DIEnumerator(name: "_SC_RTSIG_MAX", value: 31)
!132 = !DIEnumerator(name: "_SC_SEM_NSEMS_MAX", value: 32)
!133 = !DIEnumerator(name: "_SC_SEM_VALUE_MAX", value: 33)
!134 = !DIEnumerator(name: "_SC_SIGQUEUE_MAX", value: 34)
!135 = !DIEnumerator(name: "_SC_TIMER_MAX", value: 35)
!136 = !DIEnumerator(name: "_SC_BC_BASE_MAX", value: 36)
!137 = !DIEnumerator(name: "_SC_BC_DIM_MAX", value: 37)
!138 = !DIEnumerator(name: "_SC_BC_SCALE_MAX", value: 38)
!139 = !DIEnumerator(name: "_SC_BC_STRING_MAX", value: 39)
!140 = !DIEnumerator(name: "_SC_COLL_WEIGHTS_MAX", value: 40)
!141 = !DIEnumerator(name: "_SC_EQUIV_CLASS_MAX", value: 41)
!142 = !DIEnumerator(name: "_SC_EXPR_NEST_MAX", value: 42)
!143 = !DIEnumerator(name: "_SC_LINE_MAX", value: 43)
!144 = !DIEnumerator(name: "_SC_RE_DUP_MAX", value: 44)
!145 = !DIEnumerator(name: "_SC_CHARCLASS_NAME_MAX", value: 45)
!146 = !DIEnumerator(name: "_SC_2_VERSION", value: 46)
!147 = !DIEnumerator(name: "_SC_2_C_BIND", value: 47)
!148 = !DIEnumerator(name: "_SC_2_C_DEV", value: 48)
!149 = !DIEnumerator(name: "_SC_2_FORT_DEV", value: 49)
!150 = !DIEnumerator(name: "_SC_2_FORT_RUN", value: 50)
!151 = !DIEnumerator(name: "_SC_2_SW_DEV", value: 51)
!152 = !DIEnumerator(name: "_SC_2_LOCALEDEF", value: 52)
!153 = !DIEnumerator(name: "_SC_PII", value: 53)
!154 = !DIEnumerator(name: "_SC_PII_XTI", value: 54)
!155 = !DIEnumerator(name: "_SC_PII_SOCKET", value: 55)
!156 = !DIEnumerator(name: "_SC_PII_INTERNET", value: 56)
!157 = !DIEnumerator(name: "_SC_PII_OSI", value: 57)
!158 = !DIEnumerator(name: "_SC_POLL", value: 58)
!159 = !DIEnumerator(name: "_SC_SELECT", value: 59)
!160 = !DIEnumerator(name: "_SC_UIO_MAXIOV", value: 60)
!161 = !DIEnumerator(name: "_SC_IOV_MAX", value: 60)
!162 = !DIEnumerator(name: "_SC_PII_INTERNET_STREAM", value: 61)
!163 = !DIEnumerator(name: "_SC_PII_INTERNET_DGRAM", value: 62)
!164 = !DIEnumerator(name: "_SC_PII_OSI_COTS", value: 63)
!165 = !DIEnumerator(name: "_SC_PII_OSI_CLTS", value: 64)
!166 = !DIEnumerator(name: "_SC_PII_OSI_M", value: 65)
!167 = !DIEnumerator(name: "_SC_T_IOV_MAX", value: 66)
!168 = !DIEnumerator(name: "_SC_THREADS", value: 67)
!169 = !DIEnumerator(name: "_SC_THREAD_SAFE_FUNCTIONS", value: 68)
!170 = !DIEnumerator(name: "_SC_GETGR_R_SIZE_MAX", value: 69)
!171 = !DIEnumerator(name: "_SC_GETPW_R_SIZE_MAX", value: 70)
!172 = !DIEnumerator(name: "_SC_LOGIN_NAME_MAX", value: 71)
!173 = !DIEnumerator(name: "_SC_TTY_NAME_MAX", value: 72)
!174 = !DIEnumerator(name: "_SC_THREAD_DESTRUCTOR_ITERATIONS", value: 73)
!175 = !DIEnumerator(name: "_SC_THREAD_KEYS_MAX", value: 74)
!176 = !DIEnumerator(name: "_SC_THREAD_STACK_MIN", value: 75)
!177 = !DIEnumerator(name: "_SC_THREAD_THREADS_MAX", value: 76)
!178 = !DIEnumerator(name: "_SC_THREAD_ATTR_STACKADDR", value: 77)
!179 = !DIEnumerator(name: "_SC_THREAD_ATTR_STACKSIZE", value: 78)
!180 = !DIEnumerator(name: "_SC_THREAD_PRIORITY_SCHEDULING", value: 79)
!181 = !DIEnumerator(name: "_SC_THREAD_PRIO_INHERIT", value: 80)
!182 = !DIEnumerator(name: "_SC_THREAD_PRIO_PROTECT", value: 81)
!183 = !DIEnumerator(name: "_SC_THREAD_PROCESS_SHARED", value: 82)
!184 = !DIEnumerator(name: "_SC_NPROCESSORS_CONF", value: 83)
!185 = !DIEnumerator(name: "_SC_NPROCESSORS_ONLN", value: 84)
!186 = !DIEnumerator(name: "_SC_PHYS_PAGES", value: 85)
!187 = !DIEnumerator(name: "_SC_AVPHYS_PAGES", value: 86)
!188 = !DIEnumerator(name: "_SC_ATEXIT_MAX", value: 87)
!189 = !DIEnumerator(name: "_SC_PASS_MAX", value: 88)
!190 = !DIEnumerator(name: "_SC_XOPEN_VERSION", value: 89)
!191 = !DIEnumerator(name: "_SC_XOPEN_XCU_VERSION", value: 90)
!192 = !DIEnumerator(name: "_SC_XOPEN_UNIX", value: 91)
!193 = !DIEnumerator(name: "_SC_XOPEN_CRYPT", value: 92)
!194 = !DIEnumerator(name: "_SC_XOPEN_ENH_I18N", value: 93)
!195 = !DIEnumerator(name: "_SC_XOPEN_SHM", value: 94)
!196 = !DIEnumerator(name: "_SC_2_CHAR_TERM", value: 95)
!197 = !DIEnumerator(name: "_SC_2_C_VERSION", value: 96)
!198 = !DIEnumerator(name: "_SC_2_UPE", value: 97)
!199 = !DIEnumerator(name: "_SC_XOPEN_XPG2", value: 98)
!200 = !DIEnumerator(name: "_SC_XOPEN_XPG3", value: 99)
!201 = !DIEnumerator(name: "_SC_XOPEN_XPG4", value: 100)
!202 = !DIEnumerator(name: "_SC_CHAR_BIT", value: 101)
!203 = !DIEnumerator(name: "_SC_CHAR_MAX", value: 102)
!204 = !DIEnumerator(name: "_SC_CHAR_MIN", value: 103)
!205 = !DIEnumerator(name: "_SC_INT_MAX", value: 104)
!206 = !DIEnumerator(name: "_SC_INT_MIN", value: 105)
!207 = !DIEnumerator(name: "_SC_LONG_BIT", value: 106)
!208 = !DIEnumerator(name: "_SC_WORD_BIT", value: 107)
!209 = !DIEnumerator(name: "_SC_MB_LEN_MAX", value: 108)
!210 = !DIEnumerator(name: "_SC_NZERO", value: 109)
!211 = !DIEnumerator(name: "_SC_SSIZE_MAX", value: 110)
!212 = !DIEnumerator(name: "_SC_SCHAR_MAX", value: 111)
!213 = !DIEnumerator(name: "_SC_SCHAR_MIN", value: 112)
!214 = !DIEnumerator(name: "_SC_SHRT_MAX", value: 113)
!215 = !DIEnumerator(name: "_SC_SHRT_MIN", value: 114)
!216 = !DIEnumerator(name: "_SC_UCHAR_MAX", value: 115)
!217 = !DIEnumerator(name: "_SC_UINT_MAX", value: 116)
!218 = !DIEnumerator(name: "_SC_ULONG_MAX", value: 117)
!219 = !DIEnumerator(name: "_SC_USHRT_MAX", value: 118)
!220 = !DIEnumerator(name: "_SC_NL_ARGMAX", value: 119)
!221 = !DIEnumerator(name: "_SC_NL_LANGMAX", value: 120)
!222 = !DIEnumerator(name: "_SC_NL_MSGMAX", value: 121)
!223 = !DIEnumerator(name: "_SC_NL_NMAX", value: 122)
!224 = !DIEnumerator(name: "_SC_NL_SETMAX", value: 123)
!225 = !DIEnumerator(name: "_SC_NL_TEXTMAX", value: 124)
!226 = !DIEnumerator(name: "_SC_XBS5_ILP32_OFF32", value: 125)
!227 = !DIEnumerator(name: "_SC_XBS5_ILP32_OFFBIG", value: 126)
!228 = !DIEnumerator(name: "_SC_XBS5_LP64_OFF64", value: 127)
!229 = !DIEnumerator(name: "_SC_XBS5_LPBIG_OFFBIG", value: 128)
!230 = !DIEnumerator(name: "_SC_XOPEN_LEGACY", value: 129)
!231 = !DIEnumerator(name: "_SC_XOPEN_REALTIME", value: 130)
!232 = !DIEnumerator(name: "_SC_XOPEN_REALTIME_THREADS", value: 131)
!233 = !DIEnumerator(name: "_SC_ADVISORY_INFO", value: 132)
!234 = !DIEnumerator(name: "_SC_BARRIERS", value: 133)
!235 = !DIEnumerator(name: "_SC_BASE", value: 134)
!236 = !DIEnumerator(name: "_SC_C_LANG_SUPPORT", value: 135)
!237 = !DIEnumerator(name: "_SC_C_LANG_SUPPORT_R", value: 136)
!238 = !DIEnumerator(name: "_SC_CLOCK_SELECTION", value: 137)
!239 = !DIEnumerator(name: "_SC_CPUTIME", value: 138)
!240 = !DIEnumerator(name: "_SC_THREAD_CPUTIME", value: 139)
!241 = !DIEnumerator(name: "_SC_DEVICE_IO", value: 140)
!242 = !DIEnumerator(name: "_SC_DEVICE_SPECIFIC", value: 141)
!243 = !DIEnumerator(name: "_SC_DEVICE_SPECIFIC_R", value: 142)
!244 = !DIEnumerator(name: "_SC_FD_MGMT", value: 143)
!245 = !DIEnumerator(name: "_SC_FIFO", value: 144)
!246 = !DIEnumerator(name: "_SC_PIPE", value: 145)
!247 = !DIEnumerator(name: "_SC_FILE_ATTRIBUTES", value: 146)
!248 = !DIEnumerator(name: "_SC_FILE_LOCKING", value: 147)
!249 = !DIEnumerator(name: "_SC_FILE_SYSTEM", value: 148)
!250 = !DIEnumerator(name: "_SC_MONOTONIC_CLOCK", value: 149)
!251 = !DIEnumerator(name: "_SC_MULTI_PROCESS", value: 150)
!252 = !DIEnumerator(name: "_SC_SINGLE_PROCESS", value: 151)
!253 = !DIEnumerator(name: "_SC_NETWORKING", value: 152)
!254 = !DIEnumerator(name: "_SC_READER_WRITER_LOCKS", value: 153)
!255 = !DIEnumerator(name: "_SC_SPIN_LOCKS", value: 154)
!256 = !DIEnumerator(name: "_SC_REGEXP", value: 155)
!257 = !DIEnumerator(name: "_SC_REGEX_VERSION", value: 156)
!258 = !DIEnumerator(name: "_SC_SHELL", value: 157)
!259 = !DIEnumerator(name: "_SC_SIGNALS", value: 158)
!260 = !DIEnumerator(name: "_SC_SPAWN", value: 159)
!261 = !DIEnumerator(name: "_SC_SPORADIC_SERVER", value: 160)
!262 = !DIEnumerator(name: "_SC_THREAD_SPORADIC_SERVER", value: 161)
!263 = !DIEnumerator(name: "_SC_SYSTEM_DATABASE", value: 162)
!264 = !DIEnumerator(name: "_SC_SYSTEM_DATABASE_R", value: 163)
!265 = !DIEnumerator(name: "_SC_TIMEOUTS", value: 164)
!266 = !DIEnumerator(name: "_SC_TYPED_MEMORY_OBJECTS", value: 165)
!267 = !DIEnumerator(name: "_SC_USER_GROUPS", value: 166)
!268 = !DIEnumerator(name: "_SC_USER_GROUPS_R", value: 167)
!269 = !DIEnumerator(name: "_SC_2_PBS", value: 168)
!270 = !DIEnumerator(name: "_SC_2_PBS_ACCOUNTING", value: 169)
!271 = !DIEnumerator(name: "_SC_2_PBS_LOCATE", value: 170)
!272 = !DIEnumerator(name: "_SC_2_PBS_MESSAGE", value: 171)
!273 = !DIEnumerator(name: "_SC_2_PBS_TRACK", value: 172)
!274 = !DIEnumerator(name: "_SC_SYMLOOP_MAX", value: 173)
!275 = !DIEnumerator(name: "_SC_STREAMS", value: 174)
!276 = !DIEnumerator(name: "_SC_2_PBS_CHECKPOINT", value: 175)
!277 = !DIEnumerator(name: "_SC_V6_ILP32_OFF32", value: 176)
!278 = !DIEnumerator(name: "_SC_V6_ILP32_OFFBIG", value: 177)
!279 = !DIEnumerator(name: "_SC_V6_LP64_OFF64", value: 178)
!280 = !DIEnumerator(name: "_SC_V6_LPBIG_OFFBIG", value: 179)
!281 = !DIEnumerator(name: "_SC_HOST_NAME_MAX", value: 180)
!282 = !DIEnumerator(name: "_SC_TRACE", value: 181)
!283 = !DIEnumerator(name: "_SC_TRACE_EVENT_FILTER", value: 182)
!284 = !DIEnumerator(name: "_SC_TRACE_INHERIT", value: 183)
!285 = !DIEnumerator(name: "_SC_TRACE_LOG", value: 184)
!286 = !DIEnumerator(name: "_SC_LEVEL1_ICACHE_SIZE", value: 185)
!287 = !DIEnumerator(name: "_SC_LEVEL1_ICACHE_ASSOC", value: 186)
!288 = !DIEnumerator(name: "_SC_LEVEL1_ICACHE_LINESIZE", value: 187)
!289 = !DIEnumerator(name: "_SC_LEVEL1_DCACHE_SIZE", value: 188)
!290 = !DIEnumerator(name: "_SC_LEVEL1_DCACHE_ASSOC", value: 189)
!291 = !DIEnumerator(name: "_SC_LEVEL1_DCACHE_LINESIZE", value: 190)
!292 = !DIEnumerator(name: "_SC_LEVEL2_CACHE_SIZE", value: 191)
!293 = !DIEnumerator(name: "_SC_LEVEL2_CACHE_ASSOC", value: 192)
!294 = !DIEnumerator(name: "_SC_LEVEL2_CACHE_LINESIZE", value: 193)
!295 = !DIEnumerator(name: "_SC_LEVEL3_CACHE_SIZE", value: 194)
!296 = !DIEnumerator(name: "_SC_LEVEL3_CACHE_ASSOC", value: 195)
!297 = !DIEnumerator(name: "_SC_LEVEL3_CACHE_LINESIZE", value: 196)
!298 = !DIEnumerator(name: "_SC_LEVEL4_CACHE_SIZE", value: 197)
!299 = !DIEnumerator(name: "_SC_LEVEL4_CACHE_ASSOC", value: 198)
!300 = !DIEnumerator(name: "_SC_LEVEL4_CACHE_LINESIZE", value: 199)
!301 = !DIEnumerator(name: "_SC_IPV6", value: 235)
!302 = !DIEnumerator(name: "_SC_RAW_SOCKETS", value: 236)
!303 = !DIEnumerator(name: "_SC_V7_ILP32_OFF32", value: 237)
!304 = !DIEnumerator(name: "_SC_V7_ILP32_OFFBIG", value: 238)
!305 = !DIEnumerator(name: "_SC_V7_LP64_OFF64", value: 239)
!306 = !DIEnumerator(name: "_SC_V7_LPBIG_OFFBIG", value: 240)
!307 = !DIEnumerator(name: "_SC_SS_REPL_MAX", value: 241)
!308 = !DIEnumerator(name: "_SC_TRACE_EVENT_NAME_MAX", value: 242)
!309 = !DIEnumerator(name: "_SC_TRACE_NAME_MAX", value: 243)
!310 = !DIEnumerator(name: "_SC_TRACE_SYS_MAX", value: 244)
!311 = !DIEnumerator(name: "_SC_TRACE_USER_EVENT_MAX", value: 245)
!312 = !DIEnumerator(name: "_SC_XOPEN_STREAMS", value: 246)
!313 = !DIEnumerator(name: "_SC_THREAD_ROBUST_PRIO_INHERIT", value: 247)
!314 = !DIEnumerator(name: "_SC_THREAD_ROBUST_PRIO_PROTECT", value: 248)
!315 = !{!316, !558, !639, !667, !706, !728, !750, !440, !772, !800, !825, !849, !871, !512, !321, !888, !890, !894, !539, !896, !907, !551, !329, !344}
!316 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !317, size: 64, align: 64)
!317 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_pipe_t", file: !9, line: 209, baseType: !318)
!318 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_pipe_s", file: !9, line: 692, size: 2112, align: 64, elements: !319)
!319 = !{!320, !322, !528, !529, !530, !531, !536, !537, !538, !541, !553, !626, !627, !628, !629, !630, !631, !632, !633, !634, !635, !636}
!320 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !318, file: !9, line: 693, baseType: !321, size: 64, align: 64)
!321 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !318, file: !9, line: 693, baseType: !323, size: 64, align: 64, offset: 64)
!323 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !324, size: 64, align: 64)
!324 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !9, line: 204, baseType: !325)
!325 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !9, line: 1473, size: 6784, align: 64, elements: !326)
!326 = !{!327, !328, !330, !334, !335, !336, !338, !340, !341, !342, !361, !362, !363, !364, !395, !443, !467, !468, !469, !470, !471, !472, !473, !477, !478, !479, !484, !487, !488, !490, !491, !524, !525, !526, !527}
!327 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !325, file: !9, line: 1475, baseType: !321, size: 64, align: 64)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !325, file: !9, line: 1477, baseType: !329, size: 32, align: 32, offset: 64)
!329 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !325, file: !9, line: 1478, baseType: !331, size: 128, align: 64, offset: 128)
!331 = !DICompositeType(tag: DW_TAG_array_type, baseType: !321, size: 128, align: 64, elements: !332)
!332 = !{!333}
!333 = !DISubrange(count: 2)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !325, file: !9, line: 1479, baseType: !331, size: 128, align: 64, offset: 256)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !325, file: !9, line: 1481, baseType: !329, size: 32, align: 32, offset: 384)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !325, file: !9, line: 1482, baseType: !337, size: 64, align: 64, offset: 448)
!337 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !325, file: !9, line: 1482, baseType: !339, size: 32, align: 32, offset: 512)
!339 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 576)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 704)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !325, file: !9, line: 1482, baseType: !343, size: 64, align: 64, offset: 832)
!343 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !344, size: 64, align: 64)
!344 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !345, size: 64, align: 64)
!345 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !346, line: 87, baseType: !347)
!346 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!347 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !346, line: 89, size: 448, align: 64, elements: !348)
!348 = !{!349, !356, !357, !358, !359, !360}
!349 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !347, file: !346, line: 90, baseType: !350, size: 64, align: 64)
!350 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !346, line: 84, baseType: !351)
!351 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !352, size: 64, align: 64)
!352 = !DISubroutineType(types: !353)
!353 = !{null, !354, !355, !329}
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !325, size: 64, align: 64)
!355 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !347, size: 64, align: 64)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !347, file: !346, line: 91, baseType: !331, size: 128, align: 64, offset: 64)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !347, file: !346, line: 92, baseType: !331, size: 128, align: 64, offset: 192)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !347, file: !346, line: 93, baseType: !329, size: 32, align: 32, offset: 320)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !347, file: !346, line: 94, baseType: !329, size: 32, align: 32, offset: 352)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !347, file: !346, line: 95, baseType: !339, size: 32, align: 32, offset: 384)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !325, file: !9, line: 1482, baseType: !329, size: 32, align: 32, offset: 896)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !325, file: !9, line: 1482, baseType: !329, size: 32, align: 32, offset: 928)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 960)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !325, file: !9, line: 1482, baseType: !365, size: 320, align: 64, offset: 1088)
!365 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !346, line: 129, baseType: !366)
!366 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !367, line: 127, baseType: !368)
!367 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!368 = !DICompositeType(tag: DW_TAG_union_type, file: !367, line: 90, size: 320, align: 64, elements: !369)
!369 = !{!370, !388, !393}
!370 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !368, file: !367, line: 124, baseType: !371, size: 320, align: 64)
!371 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !367, line: 92, size: 320, align: 64, elements: !372)
!372 = !{!373, !374, !375, !376, !377, !378, !380, !381}
!373 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !371, file: !367, line: 94, baseType: !339, size: 32, align: 32)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !371, file: !367, line: 95, baseType: !329, size: 32, align: 32, offset: 32)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !371, file: !367, line: 96, baseType: !339, size: 32, align: 32, offset: 64)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !371, file: !367, line: 98, baseType: !329, size: 32, align: 32, offset: 96)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !371, file: !367, line: 102, baseType: !339, size: 32, align: 32, offset: 128)
!378 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !371, file: !367, line: 104, baseType: !379, size: 16, align: 16, offset: 160)
!379 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !371, file: !367, line: 105, baseType: !379, size: 16, align: 16, offset: 176)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !371, file: !367, line: 106, baseType: !382, size: 128, align: 64, offset: 192)
!382 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !367, line: 79, baseType: !383)
!383 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !367, line: 75, size: 128, align: 64, elements: !384)
!384 = !{!385, !387}
!385 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !383, file: !367, line: 77, baseType: !386, size: 64, align: 64)
!386 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !383, size: 64, align: 64)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !383, file: !367, line: 78, baseType: !386, size: 64, align: 64, offset: 64)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !368, file: !367, line: 125, baseType: !389, size: 320, align: 8)
!389 = !DICompositeType(tag: DW_TAG_array_type, baseType: !390, size: 320, align: 8, elements: !391)
!390 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!391 = !{!392}
!392 = !DISubrange(count: 40)
!393 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !368, file: !367, line: 126, baseType: !394, size: 64, align: 64)
!394 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !325, file: !9, line: 1482, baseType: !396, size: 1024, align: 64, offset: 1408)
!396 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !9, line: 216, baseType: !397)
!397 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !9, line: 767, size: 1024, align: 64, elements: !398)
!398 = !{!399, !400, !401, !403, !427, !428, !433, !434, !435, !441, !442}
!399 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !397, file: !9, line: 768, baseType: !321, size: 64, align: 64)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !397, file: !9, line: 768, baseType: !323, size: 64, align: 64, offset: 64)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !397, file: !9, line: 768, baseType: !402, size: 32, align: 32, offset: 128)
!402 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !9, line: 191, baseType: !8)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !397, file: !9, line: 768, baseType: !404, size: 64, align: 64, offset: 192)
!404 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !9, line: 306, baseType: !405)
!405 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !406, size: 64, align: 64)
!406 = !DISubroutineType(types: !407)
!407 = !{null, !408}
!408 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !409, size: 64, align: 64)
!409 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !9, line: 205, baseType: !410)
!410 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !9, line: 425, size: 768, align: 64, elements: !411)
!411 = !{!412, !413, !414, !415, !416, !417, !425, !426}
!412 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !410, file: !9, line: 426, baseType: !321, size: 64, align: 64)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !410, file: !9, line: 426, baseType: !323, size: 64, align: 64, offset: 64)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !410, file: !9, line: 426, baseType: !402, size: 32, align: 32, offset: 128)
!415 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !410, file: !9, line: 426, baseType: !404, size: 64, align: 64, offset: 192)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !410, file: !9, line: 426, baseType: !331, size: 128, align: 64, offset: 256)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !410, file: !9, line: 426, baseType: !418, size: 256, align: 64, offset: 384)
!418 = !DICompositeType(tag: DW_TAG_union_type, scope: !410, file: !9, line: 426, size: 256, align: 64, elements: !419)
!419 = !{!420, !421}
!420 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !418, file: !9, line: 426, baseType: !339, size: 32, align: 32)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !418, file: !9, line: 426, baseType: !422, size: 256, align: 64)
!422 = !DICompositeType(tag: DW_TAG_array_type, baseType: !321, size: 256, align: 64, elements: !423)
!423 = !{!424}
!424 = !DISubrange(count: 4)
!425 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !410, file: !9, line: 426, baseType: !408, size: 64, align: 64, offset: 640)
!426 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !410, file: !9, line: 426, baseType: !329, size: 32, align: 32, offset: 704)
!427 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !397, file: !9, line: 768, baseType: !331, size: 128, align: 64, offset: 256)
!428 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !397, file: !9, line: 768, baseType: !429, size: 256, align: 64, offset: 384)
!429 = !DICompositeType(tag: DW_TAG_union_type, scope: !397, file: !9, line: 768, size: 256, align: 64, elements: !430)
!430 = !{!431, !432}
!431 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !429, file: !9, line: 768, baseType: !339, size: 32, align: 32)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !429, file: !9, line: 768, baseType: !422, size: 256, align: 64)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !397, file: !9, line: 768, baseType: !408, size: 64, align: 64, offset: 640)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !397, file: !9, line: 768, baseType: !329, size: 32, align: 32, offset: 704)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !397, file: !9, line: 769, baseType: !436, size: 64, align: 64, offset: 768)
!436 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !9, line: 309, baseType: !437)
!437 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !438, size: 64, align: 64)
!438 = !DISubroutineType(types: !439)
!439 = !{null, !440}
!440 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !396, size: 64, align: 64)
!441 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !397, file: !9, line: 769, baseType: !331, size: 128, align: 64, offset: 832)
!442 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !397, file: !9, line: 769, baseType: !339, size: 32, align: 32, offset: 960)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !325, file: !9, line: 1482, baseType: !444, size: 448, align: 64, offset: 2432)
!444 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !346, line: 130, baseType: !445)
!445 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !367, line: 213, baseType: !446)
!446 = !DICompositeType(tag: DW_TAG_union_type, file: !367, line: 173, size: 448, align: 64, elements: !447)
!447 = !{!448, !462, !466}
!448 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !446, file: !367, line: 192, baseType: !449, size: 448, align: 64)
!449 = !DICompositeType(tag: DW_TAG_structure_type, scope: !446, file: !367, line: 176, size: 448, align: 64, elements: !450)
!450 = !{!451, !452, !453, !454, !455, !456, !457, !458, !459, !460, !461}
!451 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !449, file: !367, line: 178, baseType: !339, size: 32, align: 32)
!452 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !449, file: !367, line: 179, baseType: !329, size: 32, align: 32, offset: 32)
!453 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !449, file: !367, line: 180, baseType: !329, size: 32, align: 32, offset: 64)
!454 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !449, file: !367, line: 181, baseType: !329, size: 32, align: 32, offset: 96)
!455 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !449, file: !367, line: 182, baseType: !329, size: 32, align: 32, offset: 128)
!456 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !449, file: !367, line: 183, baseType: !329, size: 32, align: 32, offset: 160)
!457 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !449, file: !367, line: 184, baseType: !339, size: 32, align: 32, offset: 192)
!458 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !449, file: !367, line: 185, baseType: !339, size: 32, align: 32, offset: 224)
!459 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !449, file: !367, line: 186, baseType: !337, size: 64, align: 64, offset: 256)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !449, file: !367, line: 187, baseType: !337, size: 64, align: 64, offset: 320)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !449, file: !367, line: 190, baseType: !329, size: 32, align: 32, offset: 384)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !446, file: !367, line: 211, baseType: !463, size: 448, align: 8)
!463 = !DICompositeType(tag: DW_TAG_array_type, baseType: !390, size: 448, align: 8, elements: !464)
!464 = !{!465}
!465 = !DISubrange(count: 56)
!466 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !446, file: !367, line: 212, baseType: !394, size: 64, align: 64)
!467 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !325, file: !9, line: 1482, baseType: !408, size: 64, align: 64, offset: 2880)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 2944)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 3072)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 3200)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 3328)
!472 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !325, file: !9, line: 1482, baseType: !331, size: 128, align: 64, offset: 3456)
!473 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !325, file: !9, line: 1482, baseType: !474, size: 64, align: 64, offset: 3584)
!474 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !475, size: 64, align: 64)
!475 = !DISubroutineType(types: !476)
!476 = !{null}
!477 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !325, file: !9, line: 1482, baseType: !345, size: 448, align: 64, offset: 3648)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !325, file: !9, line: 1482, baseType: !339, size: 32, align: 32, offset: 4096)
!479 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !325, file: !9, line: 1482, baseType: !480, size: 128, align: 64, offset: 4160)
!480 = !DICompositeType(tag: DW_TAG_structure_type, scope: !325, file: !9, line: 1482, size: 128, align: 64, elements: !481)
!481 = !{!482, !483}
!482 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !480, file: !9, line: 1482, baseType: !321, size: 64, align: 64)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !480, file: !9, line: 1482, baseType: !329, size: 32, align: 32, offset: 64)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !325, file: !9, line: 1482, baseType: !485, size: 64, align: 64, offset: 4288)
!485 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !486, line: 55, baseType: !337)
!486 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!487 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !325, file: !9, line: 1482, baseType: !485, size: 64, align: 64, offset: 4352)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !325, file: !9, line: 1482, baseType: !489, size: 64, align: 32, offset: 4416)
!489 = !DICompositeType(tag: DW_TAG_array_type, baseType: !339, size: 64, align: 32, elements: !332)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !325, file: !9, line: 1482, baseType: !345, size: 448, align: 64, offset: 4480)
!491 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !325, file: !9, line: 1482, baseType: !492, size: 1216, align: 64, offset: 4928)
!492 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !9, line: 220, baseType: !493)
!493 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !9, line: 1325, size: 1216, align: 64, elements: !494)
!494 = !{!495, !496, !497, !498, !499, !500, !505, !506, !507, !513, !514, !522, !523}
!495 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !493, file: !9, line: 1326, baseType: !321, size: 64, align: 64)
!496 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !493, file: !9, line: 1326, baseType: !323, size: 64, align: 64, offset: 64)
!497 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !493, file: !9, line: 1326, baseType: !402, size: 32, align: 32, offset: 128)
!498 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !493, file: !9, line: 1326, baseType: !404, size: 64, align: 64, offset: 192)
!499 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !493, file: !9, line: 1326, baseType: !331, size: 128, align: 64, offset: 256)
!500 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !493, file: !9, line: 1326, baseType: !501, size: 256, align: 64, offset: 384)
!501 = !DICompositeType(tag: DW_TAG_union_type, scope: !493, file: !9, line: 1326, size: 256, align: 64, elements: !502)
!502 = !{!503, !504}
!503 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !501, file: !9, line: 1326, baseType: !339, size: 32, align: 32)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !501, file: !9, line: 1326, baseType: !422, size: 256, align: 64)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !493, file: !9, line: 1326, baseType: !408, size: 64, align: 64, offset: 640)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !493, file: !9, line: 1326, baseType: !329, size: 32, align: 32, offset: 704)
!507 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !493, file: !9, line: 1327, baseType: !508, size: 64, align: 64, offset: 768)
!508 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !9, line: 362, baseType: !509)
!509 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !510, size: 64, align: 64)
!510 = !DISubroutineType(types: !511)
!511 = !{null, !512, !339}
!512 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !492, size: 64, align: 64)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !493, file: !9, line: 1328, baseType: !339, size: 32, align: 32, offset: 832)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !493, file: !9, line: 1329, baseType: !515, size: 256, align: 64, offset: 896)
!515 = !DICompositeType(tag: DW_TAG_structure_type, scope: !493, file: !9, line: 1329, size: 256, align: 64, elements: !516)
!516 = !{!517, !519, !520, !521}
!517 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !515, file: !9, line: 1329, baseType: !518, size: 64, align: 64)
!518 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !493, size: 64, align: 64)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !515, file: !9, line: 1329, baseType: !518, size: 64, align: 64, offset: 64)
!520 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !515, file: !9, line: 1329, baseType: !518, size: 64, align: 64, offset: 128)
!521 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !515, file: !9, line: 1329, baseType: !339, size: 32, align: 32, offset: 192)
!522 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !493, file: !9, line: 1329, baseType: !329, size: 32, align: 32, offset: 1152)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !493, file: !9, line: 1329, baseType: !329, size: 32, align: 32, offset: 1184)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !325, file: !9, line: 1482, baseType: !339, size: 32, align: 32, offset: 6144)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !325, file: !9, line: 1482, baseType: !345, size: 448, align: 64, offset: 6208)
!526 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !325, file: !9, line: 1482, baseType: !321, size: 64, align: 64, offset: 6656)
!527 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !325, file: !9, line: 1482, baseType: !339, size: 32, align: 32, offset: 6720)
!528 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !318, file: !9, line: 693, baseType: !402, size: 32, align: 32, offset: 128)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !318, file: !9, line: 693, baseType: !404, size: 64, align: 64, offset: 192)
!530 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !318, file: !9, line: 693, baseType: !331, size: 128, align: 64, offset: 256)
!531 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !318, file: !9, line: 693, baseType: !532, size: 256, align: 64, offset: 384)
!532 = !DICompositeType(tag: DW_TAG_union_type, scope: !318, file: !9, line: 693, size: 256, align: 64, elements: !533)
!533 = !{!534, !535}
!534 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !532, file: !9, line: 693, baseType: !339, size: 32, align: 32)
!535 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !532, file: !9, line: 693, baseType: !422, size: 256, align: 64)
!536 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !318, file: !9, line: 693, baseType: !408, size: 64, align: 64, offset: 640)
!537 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !318, file: !9, line: 693, baseType: !329, size: 32, align: 32, offset: 704)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !318, file: !9, line: 694, baseType: !539, size: 64, align: 64, offset: 768)
!539 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !540, line: 62, baseType: !337)
!540 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!541 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !318, file: !9, line: 694, baseType: !542, size: 64, align: 64, offset: 832)
!542 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !9, line: 296, baseType: !543)
!543 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !544, size: 64, align: 64)
!544 = !DISubroutineType(types: !545)
!545 = !{null, !408, !539, !546}
!546 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !547, size: 64, align: 64)
!547 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !346, line: 119, baseType: !548)
!548 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !346, line: 116, size: 128, align: 64, elements: !549)
!549 = !{!550, !552}
!550 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !548, file: !346, line: 117, baseType: !551, size: 64, align: 64)
!551 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !390, size: 64, align: 64)
!552 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !548, file: !346, line: 118, baseType: !539, size: 64, align: 64, offset: 64)
!553 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !318, file: !9, line: 694, baseType: !554, size: 64, align: 64, offset: 896)
!554 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !9, line: 299, baseType: !555)
!555 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !556, size: 64, align: 64)
!556 = !DISubroutineType(types: !557)
!557 = !{null, !558, !620, !624}
!558 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !559, size: 64, align: 64)
!559 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !9, line: 206, baseType: !560)
!560 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !9, line: 465, size: 1984, align: 64, elements: !561)
!561 = !{!562, !563, !564, !565, !566, !567, !572, !573, !574, !575, !576, !577, !594, !609, !610, !611, !612, !617, !618, !619}
!562 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !560, file: !9, line: 466, baseType: !321, size: 64, align: 64)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !560, file: !9, line: 466, baseType: !323, size: 64, align: 64, offset: 64)
!564 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !560, file: !9, line: 466, baseType: !402, size: 32, align: 32, offset: 128)
!565 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !560, file: !9, line: 466, baseType: !404, size: 64, align: 64, offset: 192)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !560, file: !9, line: 466, baseType: !331, size: 128, align: 64, offset: 256)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !560, file: !9, line: 466, baseType: !568, size: 256, align: 64, offset: 384)
!568 = !DICompositeType(tag: DW_TAG_union_type, scope: !560, file: !9, line: 466, size: 256, align: 64, elements: !569)
!569 = !{!570, !571}
!570 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !568, file: !9, line: 466, baseType: !339, size: 32, align: 32)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !568, file: !9, line: 466, baseType: !422, size: 256, align: 64)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !560, file: !9, line: 466, baseType: !408, size: 64, align: 64, offset: 640)
!573 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !560, file: !9, line: 466, baseType: !329, size: 32, align: 32, offset: 704)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !560, file: !9, line: 467, baseType: !539, size: 64, align: 64, offset: 768)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !560, file: !9, line: 467, baseType: !542, size: 64, align: 64, offset: 832)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !560, file: !9, line: 467, baseType: !554, size: 64, align: 64, offset: 896)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !560, file: !9, line: 467, baseType: !578, size: 64, align: 64, offset: 960)
!578 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !579, size: 64, align: 64)
!579 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !9, line: 228, baseType: !580)
!580 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !9, line: 551, size: 768, align: 64, elements: !581)
!581 = !{!582, !583, !585, !586, !587, !592, !593}
!582 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !580, file: !9, line: 552, baseType: !321, size: 64, align: 64)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !580, file: !9, line: 552, baseType: !584, size: 32, align: 32, offset: 64)
!584 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !9, line: 200, baseType: !48)
!585 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !580, file: !9, line: 552, baseType: !331, size: 128, align: 64, offset: 128)
!586 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !580, file: !9, line: 552, baseType: !422, size: 256, align: 64, offset: 256)
!587 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !580, file: !9, line: 553, baseType: !588, size: 64, align: 64, offset: 512)
!588 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !9, line: 303, baseType: !589)
!589 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !590, size: 64, align: 64)
!590 = !DISubroutineType(types: !591)
!591 = !{null, !578, !339}
!592 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !580, file: !9, line: 554, baseType: !558, size: 64, align: 64, offset: 576)
!593 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !580, file: !9, line: 555, baseType: !331, size: 128, align: 64, offset: 640)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !560, file: !9, line: 467, baseType: !595, size: 64, align: 64, offset: 1024)
!595 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !596, size: 64, align: 64)
!596 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !9, line: 226, baseType: !597)
!597 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !9, line: 401, size: 640, align: 64, elements: !598)
!598 = !{!599, !600, !601, !602, !603, !604}
!599 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !597, file: !9, line: 402, baseType: !321, size: 64, align: 64)
!600 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !597, file: !9, line: 402, baseType: !584, size: 32, align: 32, offset: 64)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !597, file: !9, line: 402, baseType: !331, size: 128, align: 64, offset: 128)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !597, file: !9, line: 402, baseType: !422, size: 256, align: 64, offset: 256)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !597, file: !9, line: 403, baseType: !558, size: 64, align: 64, offset: 512)
!604 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !597, file: !9, line: 404, baseType: !605, size: 64, align: 64, offset: 576)
!605 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !9, line: 304, baseType: !606)
!606 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !607, size: 64, align: 64)
!607 = !DISubroutineType(types: !608)
!608 = !{null, !595, !339}
!609 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !560, file: !9, line: 467, baseType: !345, size: 448, align: 64, offset: 1088)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !560, file: !9, line: 467, baseType: !331, size: 128, align: 64, offset: 1536)
!611 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !560, file: !9, line: 467, baseType: !331, size: 128, align: 64, offset: 1664)
!612 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !560, file: !9, line: 467, baseType: !613, size: 64, align: 64, offset: 1792)
!613 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !9, line: 305, baseType: !614)
!614 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !615, size: 64, align: 64)
!615 = !DISubroutineType(types: !616)
!616 = !{null, !558, !339}
!617 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !560, file: !9, line: 467, baseType: !339, size: 32, align: 32, offset: 1856)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !560, file: !9, line: 467, baseType: !339, size: 32, align: 32, offset: 1888)
!619 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !560, file: !9, line: 467, baseType: !321, size: 64, align: 64, offset: 1920)
!620 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !621, line: 102, baseType: !622)
!621 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!622 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !623, line: 172, baseType: !394)
!623 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!624 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !625, size: 64, align: 64)
!625 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !547)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !318, file: !9, line: 694, baseType: !578, size: 64, align: 64, offset: 960)
!627 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !318, file: !9, line: 694, baseType: !595, size: 64, align: 64, offset: 1024)
!628 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !318, file: !9, line: 694, baseType: !345, size: 448, align: 64, offset: 1088)
!629 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !318, file: !9, line: 694, baseType: !331, size: 128, align: 64, offset: 1536)
!630 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !318, file: !9, line: 694, baseType: !331, size: 128, align: 64, offset: 1664)
!631 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !318, file: !9, line: 694, baseType: !613, size: 64, align: 64, offset: 1792)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !318, file: !9, line: 694, baseType: !339, size: 32, align: 32, offset: 1856)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !318, file: !9, line: 694, baseType: !339, size: 32, align: 32, offset: 1888)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !318, file: !9, line: 694, baseType: !321, size: 64, align: 64, offset: 1920)
!635 = !DIDerivedType(tag: DW_TAG_member, name: "ipc", scope: !318, file: !9, line: 695, baseType: !339, size: 32, align: 32, offset: 1984)
!636 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_fname", scope: !318, file: !9, line: 696, baseType: !637, size: 64, align: 64, offset: 2048)
!637 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !638, size: 64, align: 64)
!638 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !390)
!639 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !640, size: 64, align: 64)
!640 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_tcp_t", file: !9, line: 207, baseType: !641)
!641 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_tcp_s", file: !9, line: 516, size: 1984, align: 64, elements: !642)
!642 = !{!643, !644, !645, !646, !647, !648, !653, !654, !655, !656, !657, !658, !659, !660, !661, !662, !663, !664, !665, !666}
!643 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !641, file: !9, line: 517, baseType: !321, size: 64, align: 64)
!644 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !641, file: !9, line: 517, baseType: !323, size: 64, align: 64, offset: 64)
!645 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !641, file: !9, line: 517, baseType: !402, size: 32, align: 32, offset: 128)
!646 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !641, file: !9, line: 517, baseType: !404, size: 64, align: 64, offset: 192)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !641, file: !9, line: 517, baseType: !331, size: 128, align: 64, offset: 256)
!648 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !641, file: !9, line: 517, baseType: !649, size: 256, align: 64, offset: 384)
!649 = !DICompositeType(tag: DW_TAG_union_type, scope: !641, file: !9, line: 517, size: 256, align: 64, elements: !650)
!650 = !{!651, !652}
!651 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !649, file: !9, line: 517, baseType: !339, size: 32, align: 32)
!652 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !649, file: !9, line: 517, baseType: !422, size: 256, align: 64)
!653 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !641, file: !9, line: 517, baseType: !408, size: 64, align: 64, offset: 640)
!654 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !641, file: !9, line: 517, baseType: !329, size: 32, align: 32, offset: 704)
!655 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !641, file: !9, line: 518, baseType: !539, size: 64, align: 64, offset: 768)
!656 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !641, file: !9, line: 518, baseType: !542, size: 64, align: 64, offset: 832)
!657 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !641, file: !9, line: 518, baseType: !554, size: 64, align: 64, offset: 896)
!658 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !641, file: !9, line: 518, baseType: !578, size: 64, align: 64, offset: 960)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !641, file: !9, line: 518, baseType: !595, size: 64, align: 64, offset: 1024)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !641, file: !9, line: 518, baseType: !345, size: 448, align: 64, offset: 1088)
!661 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !641, file: !9, line: 518, baseType: !331, size: 128, align: 64, offset: 1536)
!662 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !641, file: !9, line: 518, baseType: !331, size: 128, align: 64, offset: 1664)
!663 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !641, file: !9, line: 518, baseType: !613, size: 64, align: 64, offset: 1792)
!664 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !641, file: !9, line: 518, baseType: !339, size: 32, align: 32, offset: 1856)
!665 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !641, file: !9, line: 518, baseType: !339, size: 32, align: 32, offset: 1888)
!666 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !641, file: !9, line: 518, baseType: !321, size: 64, align: 64, offset: 1920)
!667 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !668, size: 64, align: 64)
!668 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_t", file: !9, line: 208, baseType: !669)
!669 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_udp_s", file: !9, line: 590, size: 1728, align: 64, elements: !670)
!670 = !{!671, !672, !673, !674, !675, !676, !681, !682, !683, !684, !685, !686, !703, !704, !705}
!671 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !669, file: !9, line: 591, baseType: !321, size: 64, align: 64)
!672 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !669, file: !9, line: 591, baseType: !323, size: 64, align: 64, offset: 64)
!673 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !669, file: !9, line: 591, baseType: !402, size: 32, align: 32, offset: 128)
!674 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !669, file: !9, line: 591, baseType: !404, size: 64, align: 64, offset: 192)
!675 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !669, file: !9, line: 591, baseType: !331, size: 128, align: 64, offset: 256)
!676 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !669, file: !9, line: 591, baseType: !677, size: 256, align: 64, offset: 384)
!677 = !DICompositeType(tag: DW_TAG_union_type, scope: !669, file: !9, line: 591, size: 256, align: 64, elements: !678)
!678 = !{!679, !680}
!679 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !677, file: !9, line: 591, baseType: !339, size: 32, align: 32)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !677, file: !9, line: 591, baseType: !422, size: 256, align: 64)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !669, file: !9, line: 591, baseType: !408, size: 64, align: 64, offset: 640)
!682 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !669, file: !9, line: 591, baseType: !329, size: 32, align: 32, offset: 704)
!683 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_size", scope: !669, file: !9, line: 597, baseType: !539, size: 64, align: 64, offset: 768)
!684 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_count", scope: !669, file: !9, line: 601, baseType: !539, size: 64, align: 64, offset: 832)
!685 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !669, file: !9, line: 602, baseType: !542, size: 64, align: 64, offset: 896)
!686 = !DIDerivedType(tag: DW_TAG_member, name: "recv_cb", scope: !669, file: !9, line: 602, baseType: !687, size: 64, align: 64, offset: 960)
!687 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_recv_cb", file: !9, line: 583, baseType: !688)
!688 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !689, size: 64, align: 64)
!689 = !DISubroutineType(types: !690)
!690 = !{null, !667, !620, !624, !691, !329}
!691 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !692, size: 64, align: 64)
!692 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !693)
!693 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !87, line: 149, size: 128, align: 16, elements: !694)
!694 = !{!695, !699}
!695 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !693, file: !87, line: 151, baseType: !696, size: 16, align: 16)
!696 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !697, line: 28, baseType: !698)
!697 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!698 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!699 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !693, file: !87, line: 152, baseType: !700, size: 112, align: 8, offset: 16)
!700 = !DICompositeType(tag: DW_TAG_array_type, baseType: !390, size: 112, align: 8, elements: !701)
!701 = !{!702}
!702 = !DISubrange(count: 14)
!703 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !669, file: !9, line: 602, baseType: !345, size: 448, align: 64, offset: 1024)
!704 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !669, file: !9, line: 602, baseType: !331, size: 128, align: 64, offset: 1472)
!705 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !669, file: !9, line: 602, baseType: !331, size: 128, align: 64, offset: 1600)
!706 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !707, size: 64, align: 64)
!707 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_prepare_t", file: !9, line: 213, baseType: !708)
!708 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_prepare_s", file: !9, line: 737, size: 960, align: 64, elements: !709)
!709 = !{!710, !711, !712, !713, !714, !715, !720, !721, !722, !727}
!710 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !708, file: !9, line: 738, baseType: !321, size: 64, align: 64)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !708, file: !9, line: 738, baseType: !323, size: 64, align: 64, offset: 64)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !708, file: !9, line: 738, baseType: !402, size: 32, align: 32, offset: 128)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !708, file: !9, line: 738, baseType: !404, size: 64, align: 64, offset: 192)
!714 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !708, file: !9, line: 738, baseType: !331, size: 128, align: 64, offset: 256)
!715 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !708, file: !9, line: 738, baseType: !716, size: 256, align: 64, offset: 384)
!716 = !DICompositeType(tag: DW_TAG_union_type, scope: !708, file: !9, line: 738, size: 256, align: 64, elements: !717)
!717 = !{!718, !719}
!718 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !716, file: !9, line: 738, baseType: !339, size: 32, align: 32)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !716, file: !9, line: 738, baseType: !422, size: 256, align: 64)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !708, file: !9, line: 738, baseType: !408, size: 64, align: 64, offset: 640)
!721 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !708, file: !9, line: 738, baseType: !329, size: 32, align: 32, offset: 704)
!722 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_cb", scope: !708, file: !9, line: 739, baseType: !723, size: 64, align: 64, offset: 768)
!723 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_prepare_cb", file: !9, line: 310, baseType: !724)
!724 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !725, size: 64, align: 64)
!725 = !DISubroutineType(types: !726)
!726 = !{null, !706}
!727 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !708, file: !9, line: 739, baseType: !331, size: 128, align: 64, offset: 832)
!728 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !729, size: 64, align: 64)
!729 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_check_t", file: !9, line: 214, baseType: !730)
!730 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_check_s", file: !9, line: 747, size: 960, align: 64, elements: !731)
!731 = !{!732, !733, !734, !735, !736, !737, !742, !743, !744, !749}
!732 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !730, file: !9, line: 748, baseType: !321, size: 64, align: 64)
!733 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !730, file: !9, line: 748, baseType: !323, size: 64, align: 64, offset: 64)
!734 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !730, file: !9, line: 748, baseType: !402, size: 32, align: 32, offset: 128)
!735 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !730, file: !9, line: 748, baseType: !404, size: 64, align: 64, offset: 192)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !730, file: !9, line: 748, baseType: !331, size: 128, align: 64, offset: 256)
!737 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !730, file: !9, line: 748, baseType: !738, size: 256, align: 64, offset: 384)
!738 = !DICompositeType(tag: DW_TAG_union_type, scope: !730, file: !9, line: 748, size: 256, align: 64, elements: !739)
!739 = !{!740, !741}
!740 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !738, file: !9, line: 748, baseType: !339, size: 32, align: 32)
!741 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !738, file: !9, line: 748, baseType: !422, size: 256, align: 64)
!742 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !730, file: !9, line: 748, baseType: !408, size: 64, align: 64, offset: 640)
!743 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !730, file: !9, line: 748, baseType: !329, size: 32, align: 32, offset: 704)
!744 = !DIDerivedType(tag: DW_TAG_member, name: "check_cb", scope: !730, file: !9, line: 749, baseType: !745, size: 64, align: 64, offset: 768)
!745 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_check_cb", file: !9, line: 311, baseType: !746)
!746 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !747, size: 64, align: 64)
!747 = !DISubroutineType(types: !748)
!748 = !{null, !728}
!749 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !730, file: !9, line: 749, baseType: !331, size: 128, align: 64, offset: 832)
!750 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !751, size: 64, align: 64)
!751 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_idle_t", file: !9, line: 215, baseType: !752)
!752 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_idle_s", file: !9, line: 757, size: 960, align: 64, elements: !753)
!753 = !{!754, !755, !756, !757, !758, !759, !764, !765, !766, !771}
!754 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !752, file: !9, line: 758, baseType: !321, size: 64, align: 64)
!755 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !752, file: !9, line: 758, baseType: !323, size: 64, align: 64, offset: 64)
!756 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !752, file: !9, line: 758, baseType: !402, size: 32, align: 32, offset: 128)
!757 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !752, file: !9, line: 758, baseType: !404, size: 64, align: 64, offset: 192)
!758 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !752, file: !9, line: 758, baseType: !331, size: 128, align: 64, offset: 256)
!759 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !752, file: !9, line: 758, baseType: !760, size: 256, align: 64, offset: 384)
!760 = !DICompositeType(tag: DW_TAG_union_type, scope: !752, file: !9, line: 758, size: 256, align: 64, elements: !761)
!761 = !{!762, !763}
!762 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !760, file: !9, line: 758, baseType: !339, size: 32, align: 32)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !760, file: !9, line: 758, baseType: !422, size: 256, align: 64)
!764 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !752, file: !9, line: 758, baseType: !408, size: 64, align: 64, offset: 640)
!765 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !752, file: !9, line: 758, baseType: !329, size: 32, align: 32, offset: 704)
!766 = !DIDerivedType(tag: DW_TAG_member, name: "idle_cb", scope: !752, file: !9, line: 759, baseType: !767, size: 64, align: 64, offset: 768)
!767 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_idle_cb", file: !9, line: 312, baseType: !768)
!768 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !769, size: 64, align: 64)
!769 = !DISubroutineType(types: !770)
!770 = !{null, !750}
!771 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !752, file: !9, line: 759, baseType: !331, size: 128, align: 64, offset: 832)
!772 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !773, size: 64, align: 64)
!773 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timer_t", file: !9, line: 212, baseType: !774)
!774 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_timer_s", file: !9, line: 783, size: 1216, align: 64, elements: !775)
!775 = !{!776, !777, !778, !779, !780, !781, !786, !787, !788, !793, !797, !798, !799}
!776 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !774, file: !9, line: 784, baseType: !321, size: 64, align: 64)
!777 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !774, file: !9, line: 784, baseType: !323, size: 64, align: 64, offset: 64)
!778 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !774, file: !9, line: 784, baseType: !402, size: 32, align: 32, offset: 128)
!779 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !774, file: !9, line: 784, baseType: !404, size: 64, align: 64, offset: 192)
!780 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !774, file: !9, line: 784, baseType: !331, size: 128, align: 64, offset: 256)
!781 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !774, file: !9, line: 784, baseType: !782, size: 256, align: 64, offset: 384)
!782 = !DICompositeType(tag: DW_TAG_union_type, scope: !774, file: !9, line: 784, size: 256, align: 64, elements: !783)
!783 = !{!784, !785}
!784 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !782, file: !9, line: 784, baseType: !339, size: 32, align: 32)
!785 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !782, file: !9, line: 784, baseType: !422, size: 256, align: 64)
!786 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !774, file: !9, line: 784, baseType: !408, size: 64, align: 64, offset: 640)
!787 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !774, file: !9, line: 784, baseType: !329, size: 32, align: 32, offset: 704)
!788 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !774, file: !9, line: 785, baseType: !789, size: 64, align: 64, offset: 768)
!789 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timer_cb", file: !9, line: 308, baseType: !790)
!790 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !791, size: 64, align: 64)
!791 = !DISubroutineType(types: !792)
!792 = !{null, !772}
!793 = !DIDerivedType(tag: DW_TAG_member, name: "heap_node", scope: !774, file: !9, line: 785, baseType: !794, size: 192, align: 64, offset: 832)
!794 = !DICompositeType(tag: DW_TAG_array_type, baseType: !321, size: 192, align: 64, elements: !795)
!795 = !{!796}
!796 = !DISubrange(count: 3)
!797 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !774, file: !9, line: 785, baseType: !485, size: 64, align: 64, offset: 1024)
!798 = !DIDerivedType(tag: DW_TAG_member, name: "repeat", scope: !774, file: !9, line: 785, baseType: !485, size: 64, align: 64, offset: 1088)
!799 = !DIDerivedType(tag: DW_TAG_member, name: "start_id", scope: !774, file: !9, line: 785, baseType: !485, size: 64, align: 64, offset: 1152)
!800 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !801, size: 64, align: 64)
!801 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_process_t", file: !9, line: 217, baseType: !802)
!802 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_process_s", file: !9, line: 953, size: 1088, align: 64, elements: !803)
!803 = !{!804, !805, !806, !807, !808, !809, !814, !815, !816, !822, !823, !824}
!804 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !802, file: !9, line: 954, baseType: !321, size: 64, align: 64)
!805 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !802, file: !9, line: 954, baseType: !323, size: 64, align: 64, offset: 64)
!806 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !802, file: !9, line: 954, baseType: !402, size: 32, align: 32, offset: 128)
!807 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !802, file: !9, line: 954, baseType: !404, size: 64, align: 64, offset: 192)
!808 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !802, file: !9, line: 954, baseType: !331, size: 128, align: 64, offset: 256)
!809 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !802, file: !9, line: 954, baseType: !810, size: 256, align: 64, offset: 384)
!810 = !DICompositeType(tag: DW_TAG_union_type, scope: !802, file: !9, line: 954, size: 256, align: 64, elements: !811)
!811 = !{!812, !813}
!812 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !810, file: !9, line: 954, baseType: !339, size: 32, align: 32)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !810, file: !9, line: 954, baseType: !422, size: 256, align: 64)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !802, file: !9, line: 954, baseType: !408, size: 64, align: 64, offset: 640)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !802, file: !9, line: 954, baseType: !329, size: 32, align: 32, offset: 704)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "exit_cb", scope: !802, file: !9, line: 955, baseType: !817, size: 64, align: 64, offset: 768)
!817 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_exit_cb", file: !9, line: 313, baseType: !818)
!818 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !819, size: 64, align: 64)
!819 = !DISubroutineType(types: !820)
!820 = !{null, !800, !821, !339}
!821 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !486, line: 40, baseType: !394)
!822 = !DIDerivedType(tag: DW_TAG_member, name: "pid", scope: !802, file: !9, line: 956, baseType: !339, size: 32, align: 32, offset: 832)
!823 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !802, file: !9, line: 957, baseType: !331, size: 128, align: 64, offset: 896)
!824 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !802, file: !9, line: 957, baseType: !339, size: 32, align: 32, offset: 1024)
!825 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !826, size: 64, align: 64)
!826 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_event_t", file: !9, line: 218, baseType: !827)
!827 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_event_s", file: !9, line: 1297, size: 1088, align: 64, elements: !828)
!828 = !{!829, !830, !831, !832, !833, !834, !839, !840, !841, !842, !847, !848}
!829 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !827, file: !9, line: 1298, baseType: !321, size: 64, align: 64)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !827, file: !9, line: 1298, baseType: !323, size: 64, align: 64, offset: 64)
!831 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !827, file: !9, line: 1298, baseType: !402, size: 32, align: 32, offset: 128)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !827, file: !9, line: 1298, baseType: !404, size: 64, align: 64, offset: 192)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !827, file: !9, line: 1298, baseType: !331, size: 128, align: 64, offset: 256)
!834 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !827, file: !9, line: 1298, baseType: !835, size: 256, align: 64, offset: 384)
!835 = !DICompositeType(tag: DW_TAG_union_type, scope: !827, file: !9, line: 1298, size: 256, align: 64, elements: !836)
!836 = !{!837, !838}
!837 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !835, file: !9, line: 1298, baseType: !339, size: 32, align: 32)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !835, file: !9, line: 1298, baseType: !422, size: 256, align: 64)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !827, file: !9, line: 1298, baseType: !408, size: 64, align: 64, offset: 640)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !827, file: !9, line: 1298, baseType: !329, size: 32, align: 32, offset: 704)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !827, file: !9, line: 1300, baseType: !551, size: 64, align: 64, offset: 768)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !827, file: !9, line: 1301, baseType: !843, size: 64, align: 64, offset: 832)
!843 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_event_cb", file: !9, line: 352, baseType: !844)
!844 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !845, size: 64, align: 64)
!845 = !DISubroutineType(types: !846)
!846 = !{null, !825, !637, !339, !339}
!847 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !827, file: !9, line: 1301, baseType: !331, size: 128, align: 64, offset: 896)
!848 = !DIDerivedType(tag: DW_TAG_member, name: "wd", scope: !827, file: !9, line: 1301, baseType: !339, size: 32, align: 32, offset: 1024)
!849 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !850, size: 64, align: 64)
!850 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_poll_t", file: !9, line: 211, baseType: !851)
!851 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_poll_s", file: !9, line: 717, size: 1280, align: 64, elements: !852)
!852 = !{!853, !854, !855, !856, !857, !858, !863, !864, !865, !870}
!853 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !851, file: !9, line: 718, baseType: !321, size: 64, align: 64)
!854 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !851, file: !9, line: 718, baseType: !323, size: 64, align: 64, offset: 64)
!855 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !851, file: !9, line: 718, baseType: !402, size: 32, align: 32, offset: 128)
!856 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !851, file: !9, line: 718, baseType: !404, size: 64, align: 64, offset: 192)
!857 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !851, file: !9, line: 718, baseType: !331, size: 128, align: 64, offset: 256)
!858 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !851, file: !9, line: 718, baseType: !859, size: 256, align: 64, offset: 384)
!859 = !DICompositeType(tag: DW_TAG_union_type, scope: !851, file: !9, line: 718, size: 256, align: 64, elements: !860)
!860 = !{!861, !862}
!861 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !859, file: !9, line: 718, baseType: !339, size: 32, align: 32)
!862 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !859, file: !9, line: 718, baseType: !422, size: 256, align: 64)
!863 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !851, file: !9, line: 718, baseType: !408, size: 64, align: 64, offset: 640)
!864 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !851, file: !9, line: 718, baseType: !329, size: 32, align: 32, offset: 704)
!865 = !DIDerivedType(tag: DW_TAG_member, name: "poll_cb", scope: !851, file: !9, line: 719, baseType: !866, size: 64, align: 64, offset: 768)
!866 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_poll_cb", file: !9, line: 307, baseType: !867)
!867 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !868, size: 64, align: 64)
!868 = !DISubroutineType(types: !869)
!869 = !{null, !849, !339, !339}
!870 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !851, file: !9, line: 720, baseType: !345, size: 448, align: 64, offset: 832)
!871 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !872, size: 64, align: 64)
!872 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_poll_t", file: !9, line: 219, baseType: !873)
!873 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_poll_s", file: !9, line: 1308, size: 832, align: 64, elements: !874)
!874 = !{!875, !876, !877, !878, !879, !880, !885, !886, !887}
!875 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !873, file: !9, line: 1309, baseType: !321, size: 64, align: 64)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !873, file: !9, line: 1309, baseType: !323, size: 64, align: 64, offset: 64)
!877 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !873, file: !9, line: 1309, baseType: !402, size: 32, align: 32, offset: 128)
!878 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !873, file: !9, line: 1309, baseType: !404, size: 64, align: 64, offset: 192)
!879 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !873, file: !9, line: 1309, baseType: !331, size: 128, align: 64, offset: 256)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !873, file: !9, line: 1309, baseType: !881, size: 256, align: 64, offset: 384)
!881 = !DICompositeType(tag: DW_TAG_union_type, scope: !873, file: !9, line: 1309, size: 256, align: 64, elements: !882)
!882 = !{!883, !884}
!883 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !881, file: !9, line: 1309, baseType: !339, size: 32, align: 32)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !881, file: !9, line: 1309, baseType: !422, size: 256, align: 64)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !873, file: !9, line: 1309, baseType: !408, size: 64, align: 64, offset: 640)
!886 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !873, file: !9, line: 1309, baseType: !329, size: 32, align: 32, offset: 704)
!887 = !DIDerivedType(tag: DW_TAG_member, name: "poll_ctx", scope: !873, file: !9, line: 1311, baseType: !321, size: 64, align: 64, offset: 768)
!888 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !889, size: 64, align: 64)
!889 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!890 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !891, size: 64, align: 64)
!891 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !892)
!892 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !893, line: 21, baseType: !331)
!893 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!894 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !895, size: 64, align: 64)
!895 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !892, size: 64, align: 64)
!896 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !897, size: 64, align: 64)
!897 = !DICompositeType(tag: DW_TAG_structure_type, name: "cmsghdr", file: !87, line: 242, size: 128, align: 64, elements: !898)
!898 = !{!899, !900, !901, !902}
!899 = !DIDerivedType(tag: DW_TAG_member, name: "cmsg_len", scope: !897, file: !87, line: 244, baseType: !539, size: 64, align: 64)
!900 = !DIDerivedType(tag: DW_TAG_member, name: "cmsg_level", scope: !897, file: !87, line: 249, baseType: !339, size: 32, align: 32, offset: 64)
!901 = !DIDerivedType(tag: DW_TAG_member, name: "cmsg_type", scope: !897, file: !87, line: 250, baseType: !339, size: 32, align: 32, offset: 96)
!902 = !DIDerivedType(tag: DW_TAG_member, name: "__cmsg_data", scope: !897, file: !87, line: 252, baseType: !903, offset: 128)
!903 = !DICompositeType(tag: DW_TAG_array_type, baseType: !904, align: 8, elements: !905)
!904 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!905 = !{!906}
!906 = !DISubrange(count: -1)
!907 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !339, size: 64, align: 64)
!908 = !{!909, !913, !916, !919, !920, !923, !928, !933, !934, !935, !939, !942, !943, !946, !1001, !1004, !1005, !1006, !1009, !1010, !1011, !1012, !1013, !1034, !1038, !1041, !1042, !1047, !1050, !1053, !1054, !1057, !1058, !1063, !1091, !1094, !1095, !1096, !1097, !1109, !1112, !1113, !1114, !1117, !1120, !1121, !1122, !1123, !1124, !1125, !1128, !1131}
!909 = distinct !DISubprogram(name: "uv_hrtime", scope: !1, file: !1, line: 95, type: !910, isLocal: false, isDefinition: true, scopeLine: 95, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!910 = !DISubroutineType(types: !911)
!911 = !{!485}
!912 = !{}
!913 = distinct !DISubprogram(name: "uv_close", scope: !1, file: !1, line: 100, type: !914, isLocal: false, isDefinition: true, scopeLine: 100, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!914 = !DISubroutineType(types: !915)
!915 = !{null, !408, !404}
!916 = distinct !DISubprogram(name: "uv__socket_sockopt", scope: !1, file: !1, line: 172, type: !917, isLocal: false, isDefinition: true, scopeLine: 172, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!917 = !DISubroutineType(types: !918)
!918 = !{!339, !408, !339, !907}
!919 = distinct !DISubprogram(name: "uv__make_close_pending", scope: !1, file: !1, line: 200, type: !406, isLocal: false, isDefinition: true, scopeLine: 200, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!920 = distinct !DISubprogram(name: "uv__getiovmax", scope: !1, file: !1, line: 207, type: !921, isLocal: false, isDefinition: true, scopeLine: 207, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!921 = !DISubroutineType(types: !922)
!922 = !{!339}
!923 = distinct !DISubprogram(name: "uv_is_closing", scope: !1, file: !1, line: 290, type: !924, isLocal: false, isDefinition: true, scopeLine: 290, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!924 = !DISubroutineType(types: !925)
!925 = !{!339, !926}
!926 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !927, size: 64, align: 64)
!927 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !409)
!928 = distinct !DISubprogram(name: "uv_backend_fd", scope: !1, file: !1, line: 295, type: !929, isLocal: false, isDefinition: true, scopeLine: 295, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!929 = !DISubroutineType(types: !930)
!930 = !{!339, !931}
!931 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !932, size: 64, align: 64)
!932 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !324)
!933 = distinct !DISubprogram(name: "uv_backend_timeout", scope: !1, file: !1, line: 300, type: !929, isLocal: false, isDefinition: true, scopeLine: 300, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!934 = distinct !DISubprogram(name: "uv_loop_alive", scope: !1, file: !1, line: 327, type: !929, isLocal: false, isDefinition: true, scopeLine: 327, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!935 = distinct !DISubprogram(name: "uv_run", scope: !1, file: !1, line: 332, type: !936, isLocal: false, isDefinition: true, scopeLine: 332, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!936 = !DISubroutineType(types: !937)
!937 = !{!339, !323, !938}
!938 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_run_mode", file: !9, line: 247, baseType: !61)
!939 = distinct !DISubprogram(name: "uv_update_time", scope: !1, file: !1, line: 384, type: !940, isLocal: false, isDefinition: true, scopeLine: 384, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!940 = !DISubroutineType(types: !941)
!941 = !{null, !323}
!942 = distinct !DISubprogram(name: "uv_is_active", scope: !1, file: !1, line: 389, type: !924, isLocal: false, isDefinition: true, scopeLine: 389, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!943 = distinct !DISubprogram(name: "uv__socket", scope: !1, file: !1, line: 395, type: !944, isLocal: false, isDefinition: true, scopeLine: 395, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!944 = !DISubroutineType(types: !945)
!945 = !{!339, !339, !339, !339}
!946 = distinct !DISubprogram(name: "uv__open_file", scope: !1, file: !1, line: 432, type: !947, isLocal: false, isDefinition: true, scopeLine: 432, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!947 = !DISubroutineType(types: !948)
!948 = !{!949, !637}
!949 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !950, size: 64, align: 64)
!950 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !621, line: 48, baseType: !951)
!951 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !952, line: 245, size: 1728, align: 64, elements: !953)
!952 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!953 = !{!954, !955, !956, !957, !958, !959, !960, !961, !962, !963, !964, !965, !966, !974, !975, !976, !977, !979, !980, !982, !986, !989, !991, !992, !993, !994, !995, !996, !997}
!954 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !951, file: !952, line: 246, baseType: !339, size: 32, align: 32)
!955 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !951, file: !952, line: 251, baseType: !551, size: 64, align: 64, offset: 64)
!956 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !951, file: !952, line: 252, baseType: !551, size: 64, align: 64, offset: 128)
!957 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !951, file: !952, line: 253, baseType: !551, size: 64, align: 64, offset: 192)
!958 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !951, file: !952, line: 254, baseType: !551, size: 64, align: 64, offset: 256)
!959 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !951, file: !952, line: 255, baseType: !551, size: 64, align: 64, offset: 320)
!960 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !951, file: !952, line: 256, baseType: !551, size: 64, align: 64, offset: 384)
!961 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !951, file: !952, line: 257, baseType: !551, size: 64, align: 64, offset: 448)
!962 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !951, file: !952, line: 258, baseType: !551, size: 64, align: 64, offset: 512)
!963 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !951, file: !952, line: 260, baseType: !551, size: 64, align: 64, offset: 576)
!964 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !951, file: !952, line: 261, baseType: !551, size: 64, align: 64, offset: 640)
!965 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !951, file: !952, line: 262, baseType: !551, size: 64, align: 64, offset: 704)
!966 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !951, file: !952, line: 264, baseType: !967, size: 64, align: 64, offset: 768)
!967 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !968, size: 64, align: 64)
!968 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !952, line: 160, size: 192, align: 64, elements: !969)
!969 = !{!970, !971, !973}
!970 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !968, file: !952, line: 161, baseType: !967, size: 64, align: 64)
!971 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !968, file: !952, line: 162, baseType: !972, size: 64, align: 64, offset: 64)
!972 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !951, size: 64, align: 64)
!973 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !968, file: !952, line: 166, baseType: !339, size: 32, align: 32, offset: 128)
!974 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !951, file: !952, line: 266, baseType: !972, size: 64, align: 64, offset: 832)
!975 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !951, file: !952, line: 268, baseType: !339, size: 32, align: 32, offset: 896)
!976 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !951, file: !952, line: 272, baseType: !339, size: 32, align: 32, offset: 928)
!977 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !951, file: !952, line: 274, baseType: !978, size: 64, align: 64, offset: 960)
!978 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !623, line: 131, baseType: !394)
!979 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !951, file: !952, line: 278, baseType: !698, size: 16, align: 16, offset: 1024)
!980 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !951, file: !952, line: 279, baseType: !981, size: 8, align: 8, offset: 1040)
!981 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!982 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !951, file: !952, line: 280, baseType: !983, size: 8, align: 8, offset: 1048)
!983 = !DICompositeType(tag: DW_TAG_array_type, baseType: !390, size: 8, align: 8, elements: !984)
!984 = !{!985}
!985 = !DISubrange(count: 1)
!986 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !951, file: !952, line: 284, baseType: !987, size: 64, align: 64, offset: 1088)
!987 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !988, size: 64, align: 64)
!988 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !952, line: 154, baseType: null)
!989 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !951, file: !952, line: 293, baseType: !990, size: 64, align: 64, offset: 1152)
!990 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !623, line: 132, baseType: !394)
!991 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !951, file: !952, line: 302, baseType: !321, size: 64, align: 64, offset: 1216)
!992 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !951, file: !952, line: 303, baseType: !321, size: 64, align: 64, offset: 1280)
!993 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !951, file: !952, line: 304, baseType: !321, size: 64, align: 64, offset: 1344)
!994 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !951, file: !952, line: 305, baseType: !321, size: 64, align: 64, offset: 1408)
!995 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !951, file: !952, line: 306, baseType: !539, size: 64, align: 64, offset: 1472)
!996 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !951, file: !952, line: 308, baseType: !339, size: 32, align: 32, offset: 1536)
!997 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !951, file: !952, line: 310, baseType: !998, size: 160, align: 8, offset: 1568)
!998 = !DICompositeType(tag: DW_TAG_array_type, baseType: !390, size: 160, align: 8, elements: !999)
!999 = !{!1000}
!1000 = !DISubrange(count: 20)
!1001 = distinct !DISubprogram(name: "uv__accept", scope: !1, file: !1, line: 448, type: !1002, isLocal: false, isDefinition: true, scopeLine: 448, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1002 = !DISubroutineType(types: !1003)
!1003 = !{!339, !339}
!1004 = distinct !DISubprogram(name: "uv__close_nocheckstdio", scope: !1, file: !1, line: 499, type: !1002, isLocal: false, isDefinition: true, scopeLine: 499, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1005 = distinct !DISubprogram(name: "uv__close", scope: !1, file: !1, line: 518, type: !1002, isLocal: false, isDefinition: true, scopeLine: 518, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1006 = distinct !DISubprogram(name: "uv__nonblock_ioctl", scope: !1, file: !1, line: 527, type: !1007, isLocal: false, isDefinition: true, scopeLine: 527, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1007 = !DISubroutineType(types: !1008)
!1008 = !{!339, !339, !339}
!1009 = distinct !DISubprogram(name: "uv__cloexec_ioctl", scope: !1, file: !1, line: 541, type: !1007, isLocal: false, isDefinition: true, scopeLine: 541, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1010 = distinct !DISubprogram(name: "uv__nonblock_fcntl", scope: !1, file: !1, line: 555, type: !1007, isLocal: false, isDefinition: true, scopeLine: 555, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1011 = distinct !DISubprogram(name: "uv__cloexec_fcntl", scope: !1, file: !1, line: 586, type: !1007, isLocal: false, isDefinition: true, scopeLine: 586, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1012 = distinct !DISubprogram(name: "uv__dup", scope: !1, file: !1, line: 620, type: !1002, isLocal: false, isDefinition: true, scopeLine: 620, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1013 = distinct !DISubprogram(name: "uv__recvmsg", scope: !1, file: !1, line: 638, type: !1014, isLocal: false, isDefinition: true, scopeLine: 638, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1014 = !DISubroutineType(types: !1015)
!1015 = !{!620, !339, !1016, !339}
!1016 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1017, size: 64, align: 64)
!1017 = !DICompositeType(tag: DW_TAG_structure_type, name: "msghdr", file: !87, line: 224, size: 448, align: 64, elements: !1018)
!1018 = !{!1019, !1020, !1023, !1030, !1031, !1032, !1033}
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "msg_name", scope: !1017, file: !87, line: 226, baseType: !321, size: 64, align: 64)
!1020 = !DIDerivedType(tag: DW_TAG_member, name: "msg_namelen", scope: !1017, file: !87, line: 227, baseType: !1021, size: 32, align: 32, offset: 64)
!1021 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !87, line: 33, baseType: !1022)
!1022 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !623, line: 189, baseType: !329)
!1023 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iov", scope: !1017, file: !87, line: 229, baseType: !1024, size: 64, align: 64, offset: 128)
!1024 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1025, size: 64, align: 64)
!1025 = !DICompositeType(tag: DW_TAG_structure_type, name: "iovec", file: !1026, line: 43, size: 128, align: 64, elements: !1027)
!1026 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/uio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1027 = !{!1028, !1029}
!1028 = !DIDerivedType(tag: DW_TAG_member, name: "iov_base", scope: !1025, file: !1026, line: 45, baseType: !321, size: 64, align: 64)
!1029 = !DIDerivedType(tag: DW_TAG_member, name: "iov_len", scope: !1025, file: !1026, line: 46, baseType: !539, size: 64, align: 64, offset: 64)
!1030 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iovlen", scope: !1017, file: !87, line: 230, baseType: !539, size: 64, align: 64, offset: 192)
!1031 = !DIDerivedType(tag: DW_TAG_member, name: "msg_control", scope: !1017, file: !87, line: 232, baseType: !321, size: 64, align: 64, offset: 256)
!1032 = !DIDerivedType(tag: DW_TAG_member, name: "msg_controllen", scope: !1017, file: !87, line: 233, baseType: !539, size: 64, align: 64, offset: 320)
!1033 = !DIDerivedType(tag: DW_TAG_member, name: "msg_flags", scope: !1017, file: !87, line: 238, baseType: !339, size: 32, align: 32, offset: 384)
!1034 = distinct !DISubprogram(name: "uv_cwd", scope: !1, file: !1, line: 676, type: !1035, isLocal: false, isDefinition: true, scopeLine: 676, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1035 = !DISubroutineType(types: !1036)
!1036 = !{!339, !551, !1037}
!1037 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !539, size: 64, align: 64)
!1038 = distinct !DISubprogram(name: "uv_chdir", scope: !1, file: !1, line: 693, type: !1039, isLocal: false, isDefinition: true, scopeLine: 693, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1039 = !DISubroutineType(types: !1040)
!1040 = !{!339, !637}
!1041 = distinct !DISubprogram(name: "uv_disable_stdio_inheritance", scope: !1, file: !1, line: 701, type: !475, isLocal: false, isDefinition: true, scopeLine: 701, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1042 = distinct !DISubprogram(name: "uv_fileno", scope: !1, file: !1, line: 713, type: !1043, isLocal: false, isDefinition: true, scopeLine: 713, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1043 = !DISubroutineType(types: !1044)
!1044 = !{!339, !926, !1045}
!1045 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1046, size: 64, align: 64)
!1046 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_os_fd_t", file: !346, line: 123, baseType: !339)
!1047 = distinct !DISubprogram(name: "uv__io_init", scope: !1, file: !1, line: 811, type: !1048, isLocal: false, isDefinition: true, scopeLine: 811, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1048 = !DISubroutineType(types: !1049)
!1049 = !{null, !344, !350, !339}
!1050 = distinct !DISubprogram(name: "uv__io_start", scope: !1, file: !1, line: 828, type: !1051, isLocal: false, isDefinition: true, scopeLine: 828, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1051 = !DISubroutineType(types: !1052)
!1052 = !{null, !323, !344, !329}
!1053 = distinct !DISubprogram(name: "uv__io_stop", scope: !1, file: !1, line: 856, type: !1051, isLocal: false, isDefinition: true, scopeLine: 856, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1054 = distinct !DISubprogram(name: "uv__io_close", scope: !1, file: !1, line: 888, type: !1055, isLocal: false, isDefinition: true, scopeLine: 888, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1055 = !DISubroutineType(types: !1056)
!1056 = !{null, !323, !344}
!1057 = distinct !DISubprogram(name: "uv__io_feed", scope: !1, file: !1, line: 897, type: !1055, isLocal: false, isDefinition: true, scopeLine: 897, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1058 = distinct !DISubprogram(name: "uv__io_active", scope: !1, file: !1, line: 903, type: !1059, isLocal: false, isDefinition: true, scopeLine: 903, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1059 = !DISubroutineType(types: !1060)
!1060 = !{!339, !1061, !329}
!1061 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1062, size: 64, align: 64)
!1062 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !345)
!1063 = distinct !DISubprogram(name: "uv_getrusage", scope: !1, file: !1, line: 910, type: !1064, isLocal: false, isDefinition: true, scopeLine: 910, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1064 = !DISubroutineType(types: !1065)
!1065 = !{!339, !1066}
!1066 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1067, size: 64, align: 64)
!1067 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rusage_t", file: !9, line: 1064, baseType: !1068)
!1068 = !DICompositeType(tag: DW_TAG_structure_type, file: !9, line: 1047, size: 1152, align: 64, elements: !1069)
!1069 = !{!1070, !1076, !1077, !1078, !1079, !1080, !1081, !1082, !1083, !1084, !1085, !1086, !1087, !1088, !1089, !1090}
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "ru_utime", scope: !1068, file: !9, line: 1048, baseType: !1071, size: 128, align: 64)
!1071 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timeval_t", file: !9, line: 1045, baseType: !1072)
!1072 = !DICompositeType(tag: DW_TAG_structure_type, file: !9, line: 1042, size: 128, align: 64, elements: !1073)
!1073 = !{!1074, !1075}
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !1072, file: !9, line: 1043, baseType: !394, size: 64, align: 64)
!1075 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !1072, file: !9, line: 1044, baseType: !394, size: 64, align: 64, offset: 64)
!1076 = !DIDerivedType(tag: DW_TAG_member, name: "ru_stime", scope: !1068, file: !9, line: 1049, baseType: !1071, size: 128, align: 64, offset: 128)
!1077 = !DIDerivedType(tag: DW_TAG_member, name: "ru_maxrss", scope: !1068, file: !9, line: 1050, baseType: !485, size: 64, align: 64, offset: 256)
!1078 = !DIDerivedType(tag: DW_TAG_member, name: "ru_ixrss", scope: !1068, file: !9, line: 1051, baseType: !485, size: 64, align: 64, offset: 320)
!1079 = !DIDerivedType(tag: DW_TAG_member, name: "ru_idrss", scope: !1068, file: !9, line: 1052, baseType: !485, size: 64, align: 64, offset: 384)
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "ru_isrss", scope: !1068, file: !9, line: 1053, baseType: !485, size: 64, align: 64, offset: 448)
!1081 = !DIDerivedType(tag: DW_TAG_member, name: "ru_minflt", scope: !1068, file: !9, line: 1054, baseType: !485, size: 64, align: 64, offset: 512)
!1082 = !DIDerivedType(tag: DW_TAG_member, name: "ru_majflt", scope: !1068, file: !9, line: 1055, baseType: !485, size: 64, align: 64, offset: 576)
!1083 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nswap", scope: !1068, file: !9, line: 1056, baseType: !485, size: 64, align: 64, offset: 640)
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "ru_inblock", scope: !1068, file: !9, line: 1057, baseType: !485, size: 64, align: 64, offset: 704)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "ru_oublock", scope: !1068, file: !9, line: 1058, baseType: !485, size: 64, align: 64, offset: 768)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "ru_msgsnd", scope: !1068, file: !9, line: 1059, baseType: !485, size: 64, align: 64, offset: 832)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "ru_msgrcv", scope: !1068, file: !9, line: 1060, baseType: !485, size: 64, align: 64, offset: 896)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nsignals", scope: !1068, file: !9, line: 1061, baseType: !485, size: 64, align: 64, offset: 960)
!1089 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nvcsw", scope: !1068, file: !9, line: 1062, baseType: !485, size: 64, align: 64, offset: 1024)
!1090 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nivcsw", scope: !1068, file: !9, line: 1063, baseType: !485, size: 64, align: 64, offset: 1088)
!1091 = distinct !DISubprogram(name: "uv__open_cloexec", scope: !1, file: !1, line: 943, type: !1092, isLocal: false, isDefinition: true, scopeLine: 943, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1092 = !DISubroutineType(types: !1093)
!1093 = !{!339, !637, !339}
!1094 = distinct !DISubprogram(name: "uv__dup2_cloexec", scope: !1, file: !1, line: 977, type: !1007, isLocal: false, isDefinition: true, scopeLine: 977, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1095 = distinct !DISubprogram(name: "uv_os_homedir", scope: !1, file: !1, line: 1029, type: !1035, isLocal: false, isDefinition: true, scopeLine: 1029, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1096 = distinct !DISubprogram(name: "uv_os_tmpdir", scope: !1, file: !1, line: 1078, type: !1035, isLocal: false, isDefinition: true, scopeLine: 1078, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1097 = distinct !DISubprogram(name: "uv__getpwuid_r", scope: !1, file: !1, line: 1129, type: !1098, isLocal: false, isDefinition: true, scopeLine: 1129, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1098 = !DISubroutineType(types: !1099)
!1099 = !{!339, !1100}
!1100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1101, size: 64, align: 64)
!1101 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_passwd_t", file: !9, line: 237, baseType: !1102)
!1102 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_passwd_s", file: !9, line: 1012, size: 320, align: 64, elements: !1103)
!1103 = !{!1104, !1105, !1106, !1107, !1108}
!1104 = !DIDerivedType(tag: DW_TAG_member, name: "username", scope: !1102, file: !9, line: 1013, baseType: !551, size: 64, align: 64)
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1102, file: !9, line: 1014, baseType: !394, size: 64, align: 64, offset: 64)
!1106 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !1102, file: !9, line: 1015, baseType: !394, size: 64, align: 64, offset: 128)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "shell", scope: !1102, file: !9, line: 1016, baseType: !551, size: 64, align: 64, offset: 192)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "homedir", scope: !1102, file: !9, line: 1017, baseType: !551, size: 64, align: 64, offset: 256)
!1109 = distinct !DISubprogram(name: "uv_os_free_passwd", scope: !1, file: !1, line: 1218, type: !1110, isLocal: false, isDefinition: true, scopeLine: 1218, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1110 = !DISubroutineType(types: !1111)
!1111 = !{null, !1100}
!1112 = distinct !DISubprogram(name: "uv_os_get_passwd", scope: !1, file: !1, line: 1234, type: !1098, isLocal: false, isDefinition: true, scopeLine: 1234, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1113 = distinct !DISubprogram(name: "uv_translate_sys_error", scope: !1, file: !1, line: 1239, type: !1002, isLocal: false, isDefinition: true, scopeLine: 1239, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1114 = distinct !DISubprogram(name: "uv_os_getenv", scope: !1, file: !1, line: 1245, type: !1115, isLocal: false, isDefinition: true, scopeLine: 1245, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1115 = !DISubroutineType(types: !1116)
!1116 = !{!339, !637, !551, !1037}
!1117 = distinct !DISubprogram(name: "uv_os_setenv", scope: !1, file: !1, line: 1271, type: !1118, isLocal: false, isDefinition: true, scopeLine: 1271, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1118 = !DISubroutineType(types: !1119)
!1119 = !{!339, !637, !637}
!1120 = distinct !DISubprogram(name: "uv_os_unsetenv", scope: !1, file: !1, line: 1282, type: !1039, isLocal: false, isDefinition: true, scopeLine: 1282, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1121 = distinct !DISubprogram(name: "uv__loop_alive", scope: !1, file: !1, line: 320, type: !929, isLocal: true, isDefinition: true, scopeLine: 320, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1122 = distinct !DISubprogram(name: "uv__update_time", scope: !4, file: !4, line: 306, type: !940, isLocal: true, isDefinition: true, scopeLine: 306, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1123 = distinct !DISubprogram(name: "uv__run_closing_handles", scope: !1, file: !1, line: 275, type: !940, isLocal: true, isDefinition: true, scopeLine: 275, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1124 = distinct !DISubprogram(name: "uv__finish_close", scope: !1, file: !1, line: 227, type: !406, isLocal: true, isDefinition: true, scopeLine: 227, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1125 = distinct !DISubprogram(name: "uv__run_pending", scope: !1, file: !1, line: 743, type: !1126, isLocal: true, isDefinition: true, scopeLine: 743, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1126 = !DISubroutineType(types: !1127)
!1127 = !{!339, !323}
!1128 = distinct !DISubprogram(name: "maybe_resize", scope: !1, file: !1, line: 776, type: !1129, isLocal: true, isDefinition: true, scopeLine: 776, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1129 = !DISubroutineType(types: !1130)
!1130 = !{null, !323, !329}
!1131 = distinct !DISubprogram(name: "next_power_of_two", scope: !1, file: !1, line: 765, type: !1132, isLocal: true, isDefinition: true, scopeLine: 765, flags: DIFlagPrototyped, isOptimized: false, variables: !912)
!1132 = !DISubroutineType(types: !1133)
!1133 = !{!329, !329}
!1134 = !{!1135, !1136, !1137, !1138}
!1135 = !DIGlobalVariable(name: "no_accept4", scope: !1001, file: !1, line: 456, type: !339, isLocal: true, isDefinition: true, variable: i32* @uv__accept.no_accept4)
!1136 = !DIGlobalVariable(name: "no_msg_cmsg_cloexec", scope: !1013, file: !1, line: 644, type: !339, isLocal: true, isDefinition: true, variable: i32* @uv__recvmsg.no_msg_cmsg_cloexec)
!1137 = !DIGlobalVariable(name: "no_cloexec", scope: !1091, file: !1, line: 948, type: !339, isLocal: true, isDefinition: true, variable: i32* @uv__open_cloexec.no_cloexec)
!1138 = !DIGlobalVariable(name: "no_dup3", scope: !1094, file: !1, line: 992, type: !339, isLocal: true, isDefinition: true, variable: i32* @uv__dup2_cloexec.no_dup3)
!1139 = !{i32 2, !"Dwarf Version", i32 4}
!1140 = !{i32 2, !"Debug Info Version", i32 3}
!1141 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1142 = !DILocation(line: 96, column: 10, scope: !909)
!1143 = !DILocation(line: 96, column: 3, scope: !909)
!1144 = !DILocalVariable(name: "handle", arg: 1, scope: !913, file: !1, line: 100, type: !408)
!1145 = !DIExpression()
!1146 = !DILocation(line: 100, column: 28, scope: !913)
!1147 = !DILocalVariable(name: "close_cb", arg: 2, scope: !913, file: !1, line: 100, type: !404)
!1148 = !DILocation(line: 100, column: 48, scope: !913)
!1149 = !DILocation(line: 101, column: 3, scope: !913)
!1150 = !DILocation(line: 101, column: 3, scope: !1151)
!1151 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 1)
!1152 = !DILocation(line: 101, column: 3, scope: !1153)
!1153 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 2)
!1154 = !DILocation(line: 101, column: 3, scope: !1155)
!1155 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 3)
!1156 = !DILocation(line: 103, column: 3, scope: !913)
!1157 = !DILocation(line: 103, column: 11, scope: !913)
!1158 = !DILocation(line: 103, column: 17, scope: !913)
!1159 = !DILocation(line: 104, column: 22, scope: !913)
!1160 = !DILocation(line: 104, column: 3, scope: !913)
!1161 = !DILocation(line: 104, column: 11, scope: !913)
!1162 = !DILocation(line: 104, column: 20, scope: !913)
!1163 = !DILocation(line: 106, column: 11, scope: !913)
!1164 = !DILocation(line: 106, column: 19, scope: !913)
!1165 = !DILocation(line: 106, column: 3, scope: !913)
!1166 = !DILocation(line: 108, column: 32, scope: !1167)
!1167 = distinct !DILexicalBlock(scope: !913, file: !1, line: 106, column: 25)
!1168 = !DILocation(line: 108, column: 20, scope: !1167)
!1169 = !DILocation(line: 108, column: 5, scope: !1167)
!1170 = !DILocation(line: 109, column: 5, scope: !1167)
!1171 = !DILocation(line: 112, column: 36, scope: !1167)
!1172 = !DILocation(line: 112, column: 22, scope: !1167)
!1173 = !DILocation(line: 112, column: 5, scope: !1167)
!1174 = !DILocation(line: 113, column: 5, scope: !1167)
!1175 = !DILocation(line: 116, column: 30, scope: !1167)
!1176 = !DILocation(line: 116, column: 19, scope: !1167)
!1177 = !DILocation(line: 116, column: 5, scope: !1167)
!1178 = !DILocation(line: 117, column: 5, scope: !1167)
!1179 = !DILocation(line: 120, column: 30, scope: !1167)
!1180 = !DILocation(line: 120, column: 19, scope: !1167)
!1181 = !DILocation(line: 120, column: 5, scope: !1167)
!1182 = !DILocation(line: 121, column: 5, scope: !1167)
!1183 = !DILocation(line: 124, column: 38, scope: !1167)
!1184 = !DILocation(line: 124, column: 23, scope: !1167)
!1185 = !DILocation(line: 124, column: 5, scope: !1167)
!1186 = !DILocation(line: 125, column: 5, scope: !1167)
!1187 = !DILocation(line: 128, column: 34, scope: !1167)
!1188 = !DILocation(line: 128, column: 21, scope: !1167)
!1189 = !DILocation(line: 128, column: 5, scope: !1167)
!1190 = !DILocation(line: 129, column: 5, scope: !1167)
!1191 = !DILocation(line: 132, column: 32, scope: !1167)
!1192 = !DILocation(line: 132, column: 20, scope: !1167)
!1193 = !DILocation(line: 132, column: 5, scope: !1167)
!1194 = !DILocation(line: 133, column: 5, scope: !1167)
!1195 = !DILocation(line: 136, column: 34, scope: !1167)
!1196 = !DILocation(line: 136, column: 21, scope: !1167)
!1197 = !DILocation(line: 136, column: 5, scope: !1167)
!1198 = !DILocation(line: 137, column: 5, scope: !1167)
!1199 = !DILocation(line: 140, column: 34, scope: !1167)
!1200 = !DILocation(line: 140, column: 21, scope: !1167)
!1201 = !DILocation(line: 140, column: 5, scope: !1167)
!1202 = !DILocation(line: 141, column: 5, scope: !1167)
!1203 = !DILocation(line: 144, column: 38, scope: !1167)
!1204 = !DILocation(line: 144, column: 23, scope: !1167)
!1205 = !DILocation(line: 144, column: 5, scope: !1167)
!1206 = !DILocation(line: 145, column: 5, scope: !1167)
!1207 = !DILocation(line: 148, column: 40, scope: !1167)
!1208 = !DILocation(line: 148, column: 24, scope: !1167)
!1209 = !DILocation(line: 148, column: 5, scope: !1167)
!1210 = !DILocation(line: 149, column: 5, scope: !1167)
!1211 = !DILocation(line: 152, column: 32, scope: !1167)
!1212 = !DILocation(line: 152, column: 20, scope: !1167)
!1213 = !DILocation(line: 152, column: 5, scope: !1167)
!1214 = !DILocation(line: 153, column: 5, scope: !1167)
!1215 = !DILocation(line: 156, column: 38, scope: !1167)
!1216 = !DILocation(line: 156, column: 23, scope: !1167)
!1217 = !DILocation(line: 156, column: 5, scope: !1167)
!1218 = !DILocation(line: 157, column: 5, scope: !1167)
!1219 = !DILocation(line: 160, column: 37, scope: !1167)
!1220 = !DILocation(line: 160, column: 22, scope: !1167)
!1221 = !DILocation(line: 160, column: 5, scope: !1167)
!1222 = !DILocation(line: 163, column: 5, scope: !1167)
!1223 = !DILocation(line: 166, column: 5, scope: !1167)
!1224 = !DILocation(line: 169, column: 26, scope: !913)
!1225 = !DILocation(line: 169, column: 3, scope: !913)
!1226 = !DILocation(line: 170, column: 1, scope: !913)
!1227 = !DILocation(line: 170, column: 1, scope: !1151)
!1228 = !DILocalVariable(name: "handle", arg: 1, scope: !919, file: !1, line: 200, type: !408)
!1229 = !DILocation(line: 200, column: 42, scope: !919)
!1230 = !DILocation(line: 201, column: 3, scope: !919)
!1231 = !DILocation(line: 201, column: 3, scope: !1232)
!1232 = !DILexicalBlockFile(scope: !919, file: !1, discriminator: 1)
!1233 = !DILocation(line: 201, column: 3, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !919, file: !1, discriminator: 2)
!1235 = !DILocation(line: 201, column: 3, scope: !1236)
!1236 = !DILexicalBlockFile(scope: !919, file: !1, discriminator: 3)
!1237 = !DILocation(line: 202, column: 3, scope: !919)
!1238 = !DILocation(line: 202, column: 3, scope: !1232)
!1239 = !DILocation(line: 202, column: 3, scope: !1234)
!1240 = !DILocation(line: 202, column: 3, scope: !1236)
!1241 = !DILocation(line: 203, column: 26, scope: !919)
!1242 = !DILocation(line: 203, column: 34, scope: !919)
!1243 = !DILocation(line: 203, column: 40, scope: !919)
!1244 = !DILocation(line: 203, column: 3, scope: !919)
!1245 = !DILocation(line: 203, column: 11, scope: !919)
!1246 = !DILocation(line: 203, column: 24, scope: !919)
!1247 = !DILocation(line: 204, column: 35, scope: !919)
!1248 = !DILocation(line: 204, column: 3, scope: !919)
!1249 = !DILocation(line: 204, column: 11, scope: !919)
!1250 = !DILocation(line: 204, column: 17, scope: !919)
!1251 = !DILocation(line: 204, column: 33, scope: !919)
!1252 = !DILocation(line: 205, column: 1, scope: !919)
!1253 = !DILocalVariable(name: "handle", arg: 1, scope: !916, file: !1, line: 172, type: !408)
!1254 = !DILocation(line: 172, column: 37, scope: !916)
!1255 = !DILocalVariable(name: "optname", arg: 2, scope: !916, file: !1, line: 172, type: !339)
!1256 = !DILocation(line: 172, column: 49, scope: !916)
!1257 = !DILocalVariable(name: "value", arg: 3, scope: !916, file: !1, line: 172, type: !907)
!1258 = !DILocation(line: 172, column: 63, scope: !916)
!1259 = !DILocalVariable(name: "r", scope: !916, file: !1, line: 173, type: !339)
!1260 = !DILocation(line: 173, column: 7, scope: !916)
!1261 = !DILocalVariable(name: "fd", scope: !916, file: !1, line: 174, type: !339)
!1262 = !DILocation(line: 174, column: 7, scope: !916)
!1263 = !DILocalVariable(name: "len", scope: !916, file: !1, line: 175, type: !1021)
!1264 = !DILocation(line: 175, column: 13, scope: !916)
!1265 = !DILocation(line: 177, column: 7, scope: !1266)
!1266 = distinct !DILexicalBlock(scope: !916, file: !1, line: 177, column: 7)
!1267 = !DILocation(line: 177, column: 14, scope: !1266)
!1268 = !DILocation(line: 177, column: 22, scope: !1266)
!1269 = !DILocation(line: 177, column: 25, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 1)
!1271 = !DILocation(line: 177, column: 31, scope: !1270)
!1272 = !DILocation(line: 177, column: 7, scope: !1270)
!1273 = !DILocation(line: 178, column: 5, scope: !1266)
!1274 = !DILocation(line: 180, column: 7, scope: !1275)
!1275 = distinct !DILexicalBlock(scope: !916, file: !1, line: 180, column: 7)
!1276 = !DILocation(line: 180, column: 15, scope: !1275)
!1277 = !DILocation(line: 180, column: 20, scope: !1275)
!1278 = !DILocation(line: 180, column: 30, scope: !1275)
!1279 = !DILocation(line: 180, column: 33, scope: !1280)
!1280 = !DILexicalBlockFile(scope: !1275, file: !1, discriminator: 1)
!1281 = !DILocation(line: 180, column: 41, scope: !1280)
!1282 = !DILocation(line: 180, column: 46, scope: !1280)
!1283 = !DILocation(line: 180, column: 7, scope: !1280)
!1284 = !DILocation(line: 181, column: 10, scope: !1275)
!1285 = !DILocation(line: 181, column: 8, scope: !1275)
!1286 = !DILocation(line: 181, column: 5, scope: !1275)
!1287 = !DILocation(line: 182, column: 12, scope: !1288)
!1288 = distinct !DILexicalBlock(scope: !1275, file: !1, line: 182, column: 12)
!1289 = !DILocation(line: 182, column: 20, scope: !1288)
!1290 = !DILocation(line: 182, column: 25, scope: !1288)
!1291 = !DILocation(line: 182, column: 12, scope: !1275)
!1292 = !DILocation(line: 183, column: 24, scope: !1288)
!1293 = !DILocation(line: 183, column: 33, scope: !1288)
!1294 = !DILocation(line: 183, column: 44, scope: !1288)
!1295 = !DILocation(line: 183, column: 8, scope: !1288)
!1296 = !DILocation(line: 183, column: 5, scope: !1288)
!1297 = !DILocation(line: 185, column: 5, scope: !1288)
!1298 = !DILocation(line: 187, column: 7, scope: !916)
!1299 = !DILocation(line: 189, column: 8, scope: !1300)
!1300 = distinct !DILexicalBlock(scope: !916, file: !1, line: 189, column: 7)
!1301 = !DILocation(line: 189, column: 7, scope: !1300)
!1302 = !DILocation(line: 189, column: 14, scope: !1300)
!1303 = !DILocation(line: 189, column: 7, scope: !916)
!1304 = !DILocation(line: 190, column: 20, scope: !1300)
!1305 = !DILocation(line: 190, column: 36, scope: !1300)
!1306 = !DILocation(line: 190, column: 45, scope: !1300)
!1307 = !DILocation(line: 190, column: 9, scope: !1300)
!1308 = !DILocation(line: 190, column: 7, scope: !1300)
!1309 = !DILocation(line: 190, column: 5, scope: !1300)
!1310 = !DILocation(line: 192, column: 20, scope: !1300)
!1311 = !DILocation(line: 192, column: 36, scope: !1300)
!1312 = !DILocation(line: 192, column: 59, scope: !1300)
!1313 = !DILocation(line: 192, column: 45, scope: !1300)
!1314 = !DILocation(line: 192, column: 66, scope: !1300)
!1315 = !DILocation(line: 192, column: 9, scope: !1300)
!1316 = !DILocation(line: 192, column: 7, scope: !1300)
!1317 = !DILocation(line: 194, column: 7, scope: !1318)
!1318 = distinct !DILexicalBlock(scope: !916, file: !1, line: 194, column: 7)
!1319 = !DILocation(line: 194, column: 9, scope: !1318)
!1320 = !DILocation(line: 194, column: 7, scope: !916)
!1321 = !DILocation(line: 195, column: 13, scope: !1318)
!1322 = !DILocation(line: 195, column: 12, scope: !1318)
!1323 = !DILocation(line: 195, column: 5, scope: !1318)
!1324 = !DILocation(line: 197, column: 3, scope: !916)
!1325 = !DILocation(line: 198, column: 1, scope: !916)
!1326 = !DILocation(line: 209, column: 3, scope: !920)
!1327 = !DILocalVariable(name: "handle", arg: 1, scope: !923, file: !1, line: 290, type: !926)
!1328 = !DILocation(line: 290, column: 38, scope: !923)
!1329 = !DILocation(line: 291, column: 10, scope: !923)
!1330 = !DILocation(line: 291, column: 3, scope: !923)
!1331 = !DILocalVariable(name: "loop", arg: 1, scope: !928, file: !1, line: 295, type: !931)
!1332 = !DILocation(line: 295, column: 36, scope: !928)
!1333 = !DILocation(line: 296, column: 10, scope: !928)
!1334 = !DILocation(line: 296, column: 16, scope: !928)
!1335 = !DILocation(line: 296, column: 3, scope: !928)
!1336 = !DILocalVariable(name: "loop", arg: 1, scope: !933, file: !1, line: 300, type: !931)
!1337 = !DILocation(line: 300, column: 41, scope: !933)
!1338 = !DILocation(line: 301, column: 7, scope: !1339)
!1339 = distinct !DILexicalBlock(scope: !933, file: !1, line: 301, column: 7)
!1340 = !DILocation(line: 301, column: 13, scope: !1339)
!1341 = !DILocation(line: 301, column: 23, scope: !1339)
!1342 = !DILocation(line: 301, column: 7, scope: !933)
!1343 = !DILocation(line: 302, column: 5, scope: !1339)
!1344 = !DILocation(line: 304, column: 8, scope: !1345)
!1345 = distinct !DILexicalBlock(scope: !933, file: !1, line: 304, column: 7)
!1346 = !DILocation(line: 304, column: 37, scope: !1345)
!1347 = !DILocation(line: 304, column: 41, scope: !1348)
!1348 = !DILexicalBlockFile(scope: !1345, file: !1, discriminator: 1)
!1349 = !DILocation(line: 304, column: 7, scope: !1348)
!1350 = !DILocation(line: 305, column: 5, scope: !1345)
!1351 = !DILocation(line: 307, column: 8, scope: !1352)
!1352 = distinct !DILexicalBlock(scope: !933, file: !1, line: 307, column: 7)
!1353 = !DILocation(line: 307, column: 7, scope: !933)
!1354 = !DILocation(line: 308, column: 5, scope: !1352)
!1355 = !DILocation(line: 310, column: 8, scope: !1356)
!1356 = distinct !DILexicalBlock(scope: !933, file: !1, line: 310, column: 7)
!1357 = !DILocation(line: 310, column: 7, scope: !933)
!1358 = !DILocation(line: 311, column: 5, scope: !1356)
!1359 = !DILocation(line: 313, column: 7, scope: !1360)
!1360 = distinct !DILexicalBlock(scope: !933, file: !1, line: 313, column: 7)
!1361 = !DILocation(line: 313, column: 13, scope: !1360)
!1362 = !DILocation(line: 313, column: 7, scope: !933)
!1363 = !DILocation(line: 314, column: 5, scope: !1360)
!1364 = !DILocation(line: 316, column: 27, scope: !933)
!1365 = !DILocation(line: 316, column: 10, scope: !933)
!1366 = !DILocation(line: 316, column: 3, scope: !933)
!1367 = !DILocation(line: 317, column: 1, scope: !933)
!1368 = !DILocalVariable(name: "loop", arg: 1, scope: !934, file: !1, line: 327, type: !931)
!1369 = !DILocation(line: 327, column: 36, scope: !934)
!1370 = !DILocation(line: 328, column: 27, scope: !934)
!1371 = !DILocation(line: 328, column: 12, scope: !934)
!1372 = !DILocation(line: 328, column: 5, scope: !934)
!1373 = !DILocalVariable(name: "loop", arg: 1, scope: !1121, file: !1, line: 320, type: !931)
!1374 = !DILocation(line: 320, column: 44, scope: !1121)
!1375 = !DILocation(line: 321, column: 10, scope: !1121)
!1376 = !DILocation(line: 321, column: 39, scope: !1121)
!1377 = !DILocation(line: 322, column: 10, scope: !1121)
!1378 = !DILocation(line: 322, column: 36, scope: !1121)
!1379 = !DILocation(line: 323, column: 10, scope: !1121)
!1380 = !DILocation(line: 323, column: 16, scope: !1121)
!1381 = !DILocation(line: 323, column: 32, scope: !1121)
!1382 = !DILocation(line: 322, column: 36, scope: !1383)
!1383 = !DILexicalBlockFile(scope: !1121, file: !1, discriminator: 1)
!1384 = !DILocation(line: 322, column: 36, scope: !1385)
!1385 = !DILexicalBlockFile(scope: !1121, file: !1, discriminator: 2)
!1386 = !DILocation(line: 321, column: 3, scope: !1383)
!1387 = !DILocalVariable(name: "loop", arg: 1, scope: !935, file: !1, line: 332, type: !323)
!1388 = !DILocation(line: 332, column: 23, scope: !935)
!1389 = !DILocalVariable(name: "mode", arg: 2, scope: !935, file: !1, line: 332, type: !938)
!1390 = !DILocation(line: 332, column: 41, scope: !935)
!1391 = !DILocalVariable(name: "timeout", scope: !935, file: !1, line: 333, type: !339)
!1392 = !DILocation(line: 333, column: 7, scope: !935)
!1393 = !DILocalVariable(name: "r", scope: !935, file: !1, line: 334, type: !339)
!1394 = !DILocation(line: 334, column: 7, scope: !935)
!1395 = !DILocalVariable(name: "ran_pending", scope: !935, file: !1, line: 335, type: !339)
!1396 = !DILocation(line: 335, column: 7, scope: !935)
!1397 = !DILocation(line: 337, column: 22, scope: !935)
!1398 = !DILocation(line: 337, column: 7, scope: !935)
!1399 = !DILocation(line: 337, column: 5, scope: !935)
!1400 = !DILocation(line: 338, column: 8, scope: !1401)
!1401 = distinct !DILexicalBlock(scope: !935, file: !1, line: 338, column: 7)
!1402 = !DILocation(line: 338, column: 7, scope: !935)
!1403 = !DILocation(line: 339, column: 21, scope: !1401)
!1404 = !DILocation(line: 339, column: 5, scope: !1401)
!1405 = !DILocation(line: 341, column: 3, scope: !935)
!1406 = !DILocation(line: 341, column: 10, scope: !1407)
!1407 = !DILexicalBlockFile(scope: !935, file: !1, discriminator: 1)
!1408 = !DILocation(line: 341, column: 12, scope: !1407)
!1409 = !DILocation(line: 341, column: 17, scope: !1407)
!1410 = !DILocation(line: 341, column: 20, scope: !1411)
!1411 = !DILexicalBlockFile(scope: !935, file: !1, discriminator: 2)
!1412 = !DILocation(line: 341, column: 26, scope: !1411)
!1413 = !DILocation(line: 341, column: 36, scope: !1411)
!1414 = !DILocation(line: 341, column: 3, scope: !1415)
!1415 = !DILexicalBlockFile(scope: !935, file: !1, discriminator: 3)
!1416 = !DILocation(line: 342, column: 21, scope: !1417)
!1417 = distinct !DILexicalBlock(scope: !935, file: !1, line: 341, column: 42)
!1418 = !DILocation(line: 342, column: 5, scope: !1417)
!1419 = !DILocation(line: 343, column: 20, scope: !1417)
!1420 = !DILocation(line: 343, column: 5, scope: !1417)
!1421 = !DILocation(line: 344, column: 35, scope: !1417)
!1422 = !DILocation(line: 344, column: 19, scope: !1417)
!1423 = !DILocation(line: 344, column: 17, scope: !1417)
!1424 = !DILocation(line: 345, column: 18, scope: !1417)
!1425 = !DILocation(line: 345, column: 5, scope: !1417)
!1426 = !DILocation(line: 346, column: 21, scope: !1417)
!1427 = !DILocation(line: 346, column: 5, scope: !1417)
!1428 = !DILocation(line: 348, column: 13, scope: !1417)
!1429 = !DILocation(line: 349, column: 10, scope: !1430)
!1430 = distinct !DILexicalBlock(scope: !1417, file: !1, line: 349, column: 9)
!1431 = !DILocation(line: 349, column: 15, scope: !1430)
!1432 = !DILocation(line: 349, column: 30, scope: !1430)
!1433 = !DILocation(line: 349, column: 34, scope: !1434)
!1434 = !DILexicalBlockFile(scope: !1430, file: !1, discriminator: 1)
!1435 = !DILocation(line: 349, column: 47, scope: !1434)
!1436 = !DILocation(line: 349, column: 50, scope: !1437)
!1437 = !DILexicalBlockFile(scope: !1430, file: !1, discriminator: 2)
!1438 = !DILocation(line: 349, column: 55, scope: !1437)
!1439 = !DILocation(line: 349, column: 9, scope: !1437)
!1440 = !DILocation(line: 350, column: 36, scope: !1430)
!1441 = !DILocation(line: 350, column: 17, scope: !1430)
!1442 = !DILocation(line: 350, column: 15, scope: !1430)
!1443 = !DILocation(line: 350, column: 7, scope: !1430)
!1444 = !DILocation(line: 352, column: 17, scope: !1417)
!1445 = !DILocation(line: 352, column: 23, scope: !1417)
!1446 = !DILocation(line: 352, column: 5, scope: !1417)
!1447 = !DILocation(line: 353, column: 19, scope: !1417)
!1448 = !DILocation(line: 353, column: 5, scope: !1417)
!1449 = !DILocation(line: 354, column: 29, scope: !1417)
!1450 = !DILocation(line: 354, column: 5, scope: !1417)
!1451 = !DILocation(line: 356, column: 9, scope: !1452)
!1452 = distinct !DILexicalBlock(scope: !1417, file: !1, line: 356, column: 9)
!1453 = !DILocation(line: 356, column: 14, scope: !1452)
!1454 = !DILocation(line: 356, column: 9, scope: !1417)
!1455 = !DILocation(line: 365, column: 23, scope: !1456)
!1456 = distinct !DILexicalBlock(scope: !1452, file: !1, line: 356, column: 30)
!1457 = !DILocation(line: 365, column: 7, scope: !1456)
!1458 = !DILocation(line: 366, column: 22, scope: !1456)
!1459 = !DILocation(line: 366, column: 7, scope: !1456)
!1460 = !DILocation(line: 367, column: 5, scope: !1456)
!1461 = !DILocation(line: 369, column: 24, scope: !1417)
!1462 = !DILocation(line: 369, column: 9, scope: !1417)
!1463 = !DILocation(line: 369, column: 7, scope: !1417)
!1464 = !DILocation(line: 370, column: 9, scope: !1465)
!1465 = distinct !DILexicalBlock(scope: !1417, file: !1, line: 370, column: 9)
!1466 = !DILocation(line: 370, column: 14, scope: !1465)
!1467 = !DILocation(line: 370, column: 29, scope: !1465)
!1468 = !DILocation(line: 370, column: 32, scope: !1469)
!1469 = !DILexicalBlockFile(scope: !1465, file: !1, discriminator: 1)
!1470 = !DILocation(line: 370, column: 37, scope: !1469)
!1471 = !DILocation(line: 370, column: 9, scope: !1469)
!1472 = !DILocation(line: 371, column: 7, scope: !1465)
!1473 = !DILocation(line: 341, column: 3, scope: !1474)
!1474 = !DILexicalBlockFile(scope: !935, file: !1, discriminator: 4)
!1475 = !DILocation(line: 377, column: 7, scope: !1476)
!1476 = distinct !DILexicalBlock(scope: !935, file: !1, line: 377, column: 7)
!1477 = !DILocation(line: 377, column: 13, scope: !1476)
!1478 = !DILocation(line: 377, column: 23, scope: !1476)
!1479 = !DILocation(line: 377, column: 7, scope: !935)
!1480 = !DILocation(line: 378, column: 5, scope: !1476)
!1481 = !DILocation(line: 378, column: 11, scope: !1476)
!1482 = !DILocation(line: 378, column: 21, scope: !1476)
!1483 = !DILocation(line: 380, column: 10, scope: !935)
!1484 = !DILocation(line: 380, column: 3, scope: !935)
!1485 = !DILocalVariable(name: "loop", arg: 1, scope: !1122, file: !4, line: 306, type: !323)
!1486 = !DILocation(line: 306, column: 1, scope: !1122)
!1487 = !DILocation(line: 309, column: 16, scope: !1122)
!1488 = !DILocation(line: 309, column: 42, scope: !1122)
!1489 = !DILocation(line: 309, column: 3, scope: !1122)
!1490 = !DILocation(line: 309, column: 9, scope: !1122)
!1491 = !DILocation(line: 309, column: 14, scope: !1122)
!1492 = !DILocation(line: 310, column: 1, scope: !1122)
!1493 = !DILocalVariable(name: "loop", arg: 1, scope: !1125, file: !1, line: 743, type: !323)
!1494 = !DILocation(line: 743, column: 39, scope: !1125)
!1495 = !DILocalVariable(name: "q", scope: !1125, file: !1, line: 744, type: !895)
!1496 = !DILocation(line: 744, column: 10, scope: !1125)
!1497 = !DILocalVariable(name: "pq", scope: !1125, file: !1, line: 745, type: !892)
!1498 = !DILocation(line: 745, column: 9, scope: !1125)
!1499 = !DILocalVariable(name: "w", scope: !1125, file: !1, line: 746, type: !344)
!1500 = !DILocation(line: 746, column: 13, scope: !1125)
!1501 = !DILocation(line: 748, column: 7, scope: !1502)
!1502 = distinct !DILexicalBlock(scope: !1125, file: !1, line: 748, column: 7)
!1503 = !DILocation(line: 748, column: 7, scope: !1125)
!1504 = !DILocation(line: 749, column: 5, scope: !1502)
!1505 = !DILocation(line: 751, column: 3, scope: !1125)
!1506 = !DILocation(line: 751, column: 3, scope: !1507)
!1507 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 1)
!1508 = distinct !DILexicalBlock(scope: !1509, file: !1, line: 751, column: 3)
!1509 = distinct !DILexicalBlock(scope: !1125, file: !1, line: 751, column: 3)
!1510 = !DILocation(line: 751, column: 3, scope: !1511)
!1511 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 2)
!1512 = !DILocation(line: 751, column: 3, scope: !1513)
!1513 = !DILexicalBlockFile(scope: !1514, file: !1, discriminator: 3)
!1514 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 751, column: 3)
!1515 = !DILocation(line: 751, column: 3, scope: !1516)
!1516 = !DILexicalBlockFile(scope: !1514, file: !1, discriminator: 4)
!1517 = !DILocalVariable(name: "q", scope: !1518, file: !1, line: 751, type: !895)
!1518 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 751, column: 3)
!1519 = !DILocation(line: 751, column: 3, scope: !1518)
!1520 = !DILocation(line: 751, column: 3, scope: !1521)
!1521 = !DILexicalBlockFile(scope: !1518, file: !1, discriminator: 5)
!1522 = !DILocation(line: 751, column: 3, scope: !1523)
!1523 = !DILexicalBlockFile(scope: !1524, file: !1, discriminator: 6)
!1524 = distinct !DILexicalBlock(scope: !1518, file: !1, line: 751, column: 3)
!1525 = !DILocation(line: 751, column: 3, scope: !1526)
!1526 = !DILexicalBlockFile(scope: !1509, file: !1, discriminator: 7)
!1527 = !DILocation(line: 753, column: 3, scope: !1125)
!1528 = !DILocation(line: 753, column: 11, scope: !1529)
!1529 = !DILexicalBlockFile(scope: !1125, file: !1, discriminator: 1)
!1530 = !DILocation(line: 753, column: 10, scope: !1529)
!1531 = !DILocation(line: 753, column: 3, scope: !1529)
!1532 = !DILocation(line: 754, column: 9, scope: !1533)
!1533 = distinct !DILexicalBlock(scope: !1125, file: !1, line: 753, column: 29)
!1534 = !DILocation(line: 754, column: 7, scope: !1533)
!1535 = !DILocation(line: 755, column: 5, scope: !1533)
!1536 = !DILocation(line: 755, column: 5, scope: !1537)
!1537 = !DILexicalBlockFile(scope: !1538, file: !1, discriminator: 1)
!1538 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 755, column: 5)
!1539 = !DILocation(line: 756, column: 5, scope: !1533)
!1540 = !DILocation(line: 756, column: 5, scope: !1541)
!1541 = !DILexicalBlockFile(scope: !1542, file: !1, discriminator: 1)
!1542 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 756, column: 5)
!1543 = !DILocation(line: 757, column: 9, scope: !1533)
!1544 = !DILocation(line: 757, column: 7, scope: !1533)
!1545 = !DILocation(line: 758, column: 5, scope: !1533)
!1546 = !DILocation(line: 758, column: 8, scope: !1533)
!1547 = !DILocation(line: 758, column: 11, scope: !1533)
!1548 = !DILocation(line: 758, column: 17, scope: !1533)
!1549 = !DILocation(line: 753, column: 3, scope: !1550)
!1550 = !DILexicalBlockFile(scope: !1125, file: !1, discriminator: 2)
!1551 = !DILocation(line: 761, column: 3, scope: !1125)
!1552 = !DILocation(line: 762, column: 1, scope: !1125)
!1553 = !DILocalVariable(name: "loop", arg: 1, scope: !1123, file: !1, line: 275, type: !323)
!1554 = !DILocation(line: 275, column: 48, scope: !1123)
!1555 = !DILocalVariable(name: "p", scope: !1123, file: !1, line: 276, type: !408)
!1556 = !DILocation(line: 276, column: 16, scope: !1123)
!1557 = !DILocalVariable(name: "q", scope: !1123, file: !1, line: 277, type: !408)
!1558 = !DILocation(line: 277, column: 16, scope: !1123)
!1559 = !DILocation(line: 279, column: 7, scope: !1123)
!1560 = !DILocation(line: 279, column: 13, scope: !1123)
!1561 = !DILocation(line: 279, column: 5, scope: !1123)
!1562 = !DILocation(line: 280, column: 3, scope: !1123)
!1563 = !DILocation(line: 280, column: 9, scope: !1123)
!1564 = !DILocation(line: 280, column: 25, scope: !1123)
!1565 = !DILocation(line: 282, column: 3, scope: !1123)
!1566 = !DILocation(line: 282, column: 10, scope: !1567)
!1567 = !DILexicalBlockFile(scope: !1123, file: !1, discriminator: 1)
!1568 = !DILocation(line: 282, column: 3, scope: !1567)
!1569 = !DILocation(line: 283, column: 9, scope: !1570)
!1570 = distinct !DILexicalBlock(scope: !1123, file: !1, line: 282, column: 13)
!1571 = !DILocation(line: 283, column: 12, scope: !1570)
!1572 = !DILocation(line: 283, column: 7, scope: !1570)
!1573 = !DILocation(line: 284, column: 22, scope: !1570)
!1574 = !DILocation(line: 284, column: 5, scope: !1570)
!1575 = !DILocation(line: 285, column: 9, scope: !1570)
!1576 = !DILocation(line: 285, column: 7, scope: !1570)
!1577 = !DILocation(line: 282, column: 3, scope: !1578)
!1578 = !DILexicalBlockFile(scope: !1123, file: !1, discriminator: 2)
!1579 = !DILocation(line: 287, column: 1, scope: !1123)
!1580 = !DILocalVariable(name: "loop", arg: 1, scope: !939, file: !1, line: 384, type: !323)
!1581 = !DILocation(line: 384, column: 32, scope: !939)
!1582 = !DILocation(line: 385, column: 19, scope: !939)
!1583 = !DILocation(line: 385, column: 3, scope: !939)
!1584 = !DILocation(line: 386, column: 1, scope: !939)
!1585 = !DILocalVariable(name: "handle", arg: 1, scope: !942, file: !1, line: 389, type: !926)
!1586 = !DILocation(line: 389, column: 37, scope: !942)
!1587 = !DILocation(line: 390, column: 10, scope: !942)
!1588 = !DILocation(line: 390, column: 3, scope: !942)
!1589 = !DILocalVariable(name: "domain", arg: 1, scope: !943, file: !1, line: 395, type: !339)
!1590 = !DILocation(line: 395, column: 20, scope: !943)
!1591 = !DILocalVariable(name: "type", arg: 2, scope: !943, file: !1, line: 395, type: !339)
!1592 = !DILocation(line: 395, column: 32, scope: !943)
!1593 = !DILocalVariable(name: "protocol", arg: 3, scope: !943, file: !1, line: 395, type: !339)
!1594 = !DILocation(line: 395, column: 42, scope: !943)
!1595 = !DILocalVariable(name: "sockfd", scope: !943, file: !1, line: 396, type: !339)
!1596 = !DILocation(line: 396, column: 7, scope: !943)
!1597 = !DILocalVariable(name: "err", scope: !943, file: !1, line: 397, type: !339)
!1598 = !DILocation(line: 397, column: 7, scope: !943)
!1599 = !DILocation(line: 400, column: 19, scope: !943)
!1600 = !DILocation(line: 400, column: 27, scope: !943)
!1601 = !DILocation(line: 400, column: 32, scope: !943)
!1602 = !DILocation(line: 400, column: 48, scope: !943)
!1603 = !DILocation(line: 400, column: 64, scope: !943)
!1604 = !DILocation(line: 400, column: 12, scope: !943)
!1605 = !DILocation(line: 400, column: 10, scope: !943)
!1606 = !DILocation(line: 401, column: 7, scope: !1607)
!1607 = distinct !DILexicalBlock(scope: !943, file: !1, line: 401, column: 7)
!1608 = !DILocation(line: 401, column: 14, scope: !1607)
!1609 = !DILocation(line: 401, column: 7, scope: !943)
!1610 = !DILocation(line: 402, column: 12, scope: !1607)
!1611 = !DILocation(line: 402, column: 5, scope: !1607)
!1612 = !DILocation(line: 404, column: 7, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !943, file: !1, line: 404, column: 7)
!1614 = !DILocation(line: 404, column: 13, scope: !1613)
!1615 = !DILocation(line: 404, column: 7, scope: !943)
!1616 = !DILocation(line: 405, column: 13, scope: !1613)
!1617 = !DILocation(line: 405, column: 12, scope: !1613)
!1618 = !DILocation(line: 405, column: 5, scope: !1613)
!1619 = !DILocation(line: 408, column: 19, scope: !943)
!1620 = !DILocation(line: 408, column: 27, scope: !943)
!1621 = !DILocation(line: 408, column: 33, scope: !943)
!1622 = !DILocation(line: 408, column: 12, scope: !943)
!1623 = !DILocation(line: 408, column: 10, scope: !943)
!1624 = !DILocation(line: 409, column: 7, scope: !1625)
!1625 = distinct !DILexicalBlock(scope: !943, file: !1, line: 409, column: 7)
!1626 = !DILocation(line: 409, column: 14, scope: !1625)
!1627 = !DILocation(line: 409, column: 7, scope: !943)
!1628 = !DILocation(line: 410, column: 13, scope: !1625)
!1629 = !DILocation(line: 410, column: 12, scope: !1625)
!1630 = !DILocation(line: 410, column: 5, scope: !1625)
!1631 = !DILocation(line: 412, column: 22, scope: !943)
!1632 = !DILocation(line: 412, column: 9, scope: !943)
!1633 = !DILocation(line: 412, column: 7, scope: !943)
!1634 = !DILocation(line: 413, column: 7, scope: !1635)
!1635 = distinct !DILexicalBlock(scope: !943, file: !1, line: 413, column: 7)
!1636 = !DILocation(line: 413, column: 11, scope: !1635)
!1637 = !DILocation(line: 413, column: 7, scope: !943)
!1638 = !DILocation(line: 414, column: 23, scope: !1635)
!1639 = !DILocation(line: 414, column: 11, scope: !1635)
!1640 = !DILocation(line: 414, column: 9, scope: !1635)
!1641 = !DILocation(line: 414, column: 5, scope: !1635)
!1642 = !DILocation(line: 416, column: 7, scope: !1643)
!1643 = distinct !DILexicalBlock(scope: !943, file: !1, line: 416, column: 7)
!1644 = !DILocation(line: 416, column: 7, scope: !943)
!1645 = !DILocation(line: 417, column: 15, scope: !1646)
!1646 = distinct !DILexicalBlock(scope: !1643, file: !1, line: 416, column: 12)
!1647 = !DILocation(line: 417, column: 5, scope: !1646)
!1648 = !DILocation(line: 418, column: 12, scope: !1646)
!1649 = !DILocation(line: 418, column: 5, scope: !1646)
!1650 = !DILocation(line: 428, column: 10, scope: !943)
!1651 = !DILocation(line: 428, column: 3, scope: !943)
!1652 = !DILocation(line: 429, column: 1, scope: !943)
!1653 = !DILocalVariable(name: "fd", arg: 1, scope: !1006, file: !1, line: 527, type: !339)
!1654 = !DILocation(line: 527, column: 28, scope: !1006)
!1655 = !DILocalVariable(name: "set", arg: 2, scope: !1006, file: !1, line: 527, type: !339)
!1656 = !DILocation(line: 527, column: 36, scope: !1006)
!1657 = !DILocalVariable(name: "r", scope: !1006, file: !1, line: 528, type: !339)
!1658 = !DILocation(line: 528, column: 7, scope: !1006)
!1659 = !DILocation(line: 530, column: 3, scope: !1006)
!1660 = !DILocation(line: 531, column: 15, scope: !1006)
!1661 = !DILocation(line: 531, column: 9, scope: !1006)
!1662 = !DILocation(line: 531, column: 7, scope: !1006)
!1663 = !DILocation(line: 531, column: 5, scope: !1006)
!1664 = !DILocation(line: 532, column: 10, scope: !1006)
!1665 = !DILocation(line: 532, column: 12, scope: !1006)
!1666 = !DILocation(line: 532, column: 18, scope: !1006)
!1667 = !DILocation(line: 532, column: 21, scope: !1668)
!1668 = !DILexicalBlockFile(scope: !1006, file: !1, discriminator: 1)
!1669 = !DILocation(line: 532, column: 27, scope: !1668)
!1670 = !DILocation(line: 531, column: 5, scope: !1668)
!1671 = !DILocation(line: 534, column: 7, scope: !1672)
!1672 = distinct !DILexicalBlock(scope: !1006, file: !1, line: 534, column: 7)
!1673 = !DILocation(line: 534, column: 7, scope: !1006)
!1674 = !DILocation(line: 535, column: 13, scope: !1672)
!1675 = !DILocation(line: 535, column: 12, scope: !1672)
!1676 = !DILocation(line: 535, column: 5, scope: !1672)
!1677 = !DILocation(line: 537, column: 3, scope: !1006)
!1678 = !DILocation(line: 538, column: 1, scope: !1006)
!1679 = !DILocalVariable(name: "fd", arg: 1, scope: !1009, file: !1, line: 541, type: !339)
!1680 = !DILocation(line: 541, column: 27, scope: !1009)
!1681 = !DILocalVariable(name: "set", arg: 2, scope: !1009, file: !1, line: 541, type: !339)
!1682 = !DILocation(line: 541, column: 35, scope: !1009)
!1683 = !DILocalVariable(name: "r", scope: !1009, file: !1, line: 542, type: !339)
!1684 = !DILocation(line: 542, column: 7, scope: !1009)
!1685 = !DILocation(line: 544, column: 3, scope: !1009)
!1686 = !DILocation(line: 545, column: 15, scope: !1009)
!1687 = !DILocation(line: 545, column: 19, scope: !1009)
!1688 = !DILocation(line: 545, column: 9, scope: !1009)
!1689 = !DILocation(line: 545, column: 7, scope: !1009)
!1690 = !DILocation(line: 545, column: 5, scope: !1009)
!1691 = !DILocation(line: 546, column: 10, scope: !1009)
!1692 = !DILocation(line: 546, column: 12, scope: !1009)
!1693 = !DILocation(line: 546, column: 18, scope: !1009)
!1694 = !DILocation(line: 546, column: 21, scope: !1695)
!1695 = !DILexicalBlockFile(scope: !1009, file: !1, discriminator: 1)
!1696 = !DILocation(line: 546, column: 27, scope: !1695)
!1697 = !DILocation(line: 545, column: 5, scope: !1695)
!1698 = !DILocation(line: 548, column: 7, scope: !1699)
!1699 = distinct !DILexicalBlock(scope: !1009, file: !1, line: 548, column: 7)
!1700 = !DILocation(line: 548, column: 7, scope: !1009)
!1701 = !DILocation(line: 549, column: 13, scope: !1699)
!1702 = !DILocation(line: 549, column: 12, scope: !1699)
!1703 = !DILocation(line: 549, column: 5, scope: !1699)
!1704 = !DILocation(line: 551, column: 3, scope: !1009)
!1705 = !DILocation(line: 552, column: 1, scope: !1009)
!1706 = !DILocalVariable(name: "fd", arg: 1, scope: !1005, file: !1, line: 518, type: !339)
!1707 = !DILocation(line: 518, column: 19, scope: !1005)
!1708 = !DILocation(line: 519, column: 3, scope: !1005)
!1709 = !DILocation(line: 519, column: 3, scope: !1710)
!1710 = !DILexicalBlockFile(scope: !1005, file: !1, discriminator: 1)
!1711 = !DILocation(line: 519, column: 3, scope: !1712)
!1712 = !DILexicalBlockFile(scope: !1005, file: !1, discriminator: 2)
!1713 = !DILocation(line: 519, column: 3, scope: !1714)
!1714 = !DILexicalBlockFile(scope: !1005, file: !1, discriminator: 3)
!1715 = !DILocation(line: 523, column: 33, scope: !1005)
!1716 = !DILocation(line: 523, column: 10, scope: !1005)
!1717 = !DILocation(line: 523, column: 3, scope: !1005)
!1718 = !DILocalVariable(name: "path", arg: 1, scope: !946, file: !1, line: 432, type: !637)
!1719 = !DILocation(line: 432, column: 33, scope: !946)
!1720 = !DILocalVariable(name: "fd", scope: !946, file: !1, line: 433, type: !339)
!1721 = !DILocation(line: 433, column: 7, scope: !946)
!1722 = !DILocalVariable(name: "fp", scope: !946, file: !1, line: 434, type: !949)
!1723 = !DILocation(line: 434, column: 9, scope: !946)
!1724 = !DILocation(line: 436, column: 25, scope: !946)
!1725 = !DILocation(line: 436, column: 8, scope: !946)
!1726 = !DILocation(line: 436, column: 6, scope: !946)
!1727 = !DILocation(line: 437, column: 7, scope: !1728)
!1728 = distinct !DILexicalBlock(scope: !946, file: !1, line: 437, column: 7)
!1729 = !DILocation(line: 437, column: 10, scope: !1728)
!1730 = !DILocation(line: 437, column: 7, scope: !946)
!1731 = !DILocation(line: 438, column: 5, scope: !1728)
!1732 = !DILocation(line: 440, column: 16, scope: !946)
!1733 = !DILocation(line: 440, column: 9, scope: !946)
!1734 = !DILocation(line: 440, column: 7, scope: !946)
!1735 = !DILocation(line: 441, column: 8, scope: !1736)
!1736 = distinct !DILexicalBlock(scope: !946, file: !1, line: 441, column: 8)
!1737 = !DILocation(line: 441, column: 11, scope: !1736)
!1738 = !DILocation(line: 441, column: 8, scope: !946)
!1739 = !DILocation(line: 442, column: 16, scope: !1736)
!1740 = !DILocation(line: 442, column: 6, scope: !1736)
!1741 = !DILocation(line: 444, column: 11, scope: !946)
!1742 = !DILocation(line: 444, column: 4, scope: !946)
!1743 = !DILocation(line: 445, column: 1, scope: !946)
!1744 = !DILocalVariable(name: "path", arg: 1, scope: !1091, file: !1, line: 943, type: !637)
!1745 = !DILocation(line: 943, column: 34, scope: !1091)
!1746 = !DILocalVariable(name: "flags", arg: 2, scope: !1091, file: !1, line: 943, type: !339)
!1747 = !DILocation(line: 943, column: 44, scope: !1091)
!1748 = !DILocalVariable(name: "err", scope: !1091, file: !1, line: 944, type: !339)
!1749 = !DILocation(line: 944, column: 7, scope: !1091)
!1750 = !DILocalVariable(name: "fd", scope: !1091, file: !1, line: 945, type: !339)
!1751 = !DILocation(line: 945, column: 7, scope: !1091)
!1752 = !DILocation(line: 950, column: 8, scope: !1753)
!1753 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 950, column: 7)
!1754 = !DILocation(line: 950, column: 7, scope: !1091)
!1755 = !DILocation(line: 951, column: 15, scope: !1756)
!1756 = distinct !DILexicalBlock(scope: !1753, file: !1, line: 950, column: 20)
!1757 = !DILocation(line: 951, column: 21, scope: !1756)
!1758 = !DILocation(line: 951, column: 27, scope: !1756)
!1759 = !DILocation(line: 951, column: 10, scope: !1756)
!1760 = !DILocation(line: 951, column: 8, scope: !1756)
!1761 = !DILocation(line: 952, column: 9, scope: !1762)
!1762 = distinct !DILexicalBlock(scope: !1756, file: !1, line: 952, column: 9)
!1763 = !DILocation(line: 952, column: 12, scope: !1762)
!1764 = !DILocation(line: 952, column: 9, scope: !1756)
!1765 = !DILocation(line: 953, column: 14, scope: !1762)
!1766 = !DILocation(line: 953, column: 7, scope: !1762)
!1767 = !DILocation(line: 955, column: 9, scope: !1768)
!1768 = distinct !DILexicalBlock(scope: !1756, file: !1, line: 955, column: 9)
!1769 = !DILocation(line: 955, column: 15, scope: !1768)
!1770 = !DILocation(line: 955, column: 9, scope: !1756)
!1771 = !DILocation(line: 956, column: 15, scope: !1768)
!1772 = !DILocation(line: 956, column: 14, scope: !1768)
!1773 = !DILocation(line: 956, column: 7, scope: !1768)
!1774 = !DILocation(line: 959, column: 16, scope: !1756)
!1775 = !DILocation(line: 960, column: 3, scope: !1756)
!1776 = !DILocation(line: 963, column: 13, scope: !1091)
!1777 = !DILocation(line: 963, column: 19, scope: !1091)
!1778 = !DILocation(line: 963, column: 8, scope: !1091)
!1779 = !DILocation(line: 963, column: 6, scope: !1091)
!1780 = !DILocation(line: 964, column: 7, scope: !1781)
!1781 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 964, column: 7)
!1782 = !DILocation(line: 964, column: 10, scope: !1781)
!1783 = !DILocation(line: 964, column: 7, scope: !1091)
!1784 = !DILocation(line: 965, column: 13, scope: !1781)
!1785 = !DILocation(line: 965, column: 12, scope: !1781)
!1786 = !DILocation(line: 965, column: 5, scope: !1781)
!1787 = !DILocation(line: 967, column: 21, scope: !1091)
!1788 = !DILocation(line: 967, column: 9, scope: !1091)
!1789 = !DILocation(line: 967, column: 7, scope: !1091)
!1790 = !DILocation(line: 968, column: 7, scope: !1791)
!1791 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 968, column: 7)
!1792 = !DILocation(line: 968, column: 7, scope: !1091)
!1793 = !DILocation(line: 969, column: 15, scope: !1794)
!1794 = distinct !DILexicalBlock(scope: !1791, file: !1, line: 968, column: 12)
!1795 = !DILocation(line: 969, column: 5, scope: !1794)
!1796 = !DILocation(line: 970, column: 12, scope: !1794)
!1797 = !DILocation(line: 970, column: 5, scope: !1794)
!1798 = !DILocation(line: 973, column: 10, scope: !1091)
!1799 = !DILocation(line: 973, column: 3, scope: !1091)
!1800 = !DILocation(line: 974, column: 1, scope: !1091)
!1801 = !DILocalVariable(name: "sockfd", arg: 1, scope: !1001, file: !1, line: 448, type: !339)
!1802 = !DILocation(line: 448, column: 20, scope: !1001)
!1803 = !DILocalVariable(name: "peerfd", scope: !1001, file: !1, line: 449, type: !339)
!1804 = !DILocation(line: 449, column: 7, scope: !1001)
!1805 = !DILocalVariable(name: "err", scope: !1001, file: !1, line: 450, type: !339)
!1806 = !DILocation(line: 450, column: 7, scope: !1001)
!1807 = !DILocation(line: 452, column: 3, scope: !1001)
!1808 = !DILocation(line: 452, column: 3, scope: !1809)
!1809 = !DILexicalBlockFile(scope: !1001, file: !1, discriminator: 1)
!1810 = !DILocation(line: 452, column: 3, scope: !1811)
!1811 = !DILexicalBlockFile(scope: !1001, file: !1, discriminator: 2)
!1812 = !DILocation(line: 452, column: 3, scope: !1813)
!1813 = !DILexicalBlockFile(scope: !1001, file: !1, discriminator: 3)
!1814 = !DILocation(line: 454, column: 3, scope: !1001)
!1815 = !DILocation(line: 458, column: 9, scope: !1816)
!1816 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 458, column: 9)
!1817 = distinct !DILexicalBlock(scope: !1001, file: !1, line: 454, column: 13)
!1818 = !DILocation(line: 458, column: 9, scope: !1817)
!1819 = !DILocation(line: 459, column: 7, scope: !1816)
!1820 = !DILocation(line: 461, column: 26, scope: !1817)
!1821 = !DILocation(line: 461, column: 14, scope: !1817)
!1822 = !DILocation(line: 461, column: 12, scope: !1817)
!1823 = !DILocation(line: 465, column: 9, scope: !1824)
!1824 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 465, column: 9)
!1825 = !DILocation(line: 465, column: 16, scope: !1824)
!1826 = !DILocation(line: 465, column: 9, scope: !1817)
!1827 = !DILocation(line: 466, column: 14, scope: !1824)
!1828 = !DILocation(line: 466, column: 7, scope: !1824)
!1829 = !DILocation(line: 468, column: 9, scope: !1830)
!1830 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 468, column: 9)
!1831 = !DILocation(line: 468, column: 15, scope: !1830)
!1832 = !DILocation(line: 468, column: 9, scope: !1817)
!1833 = !DILocation(line: 469, column: 7, scope: !1830)
!1834 = !DILocation(line: 471, column: 9, scope: !1835)
!1835 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 471, column: 9)
!1836 = !DILocation(line: 471, column: 15, scope: !1835)
!1837 = !DILocation(line: 471, column: 9, scope: !1817)
!1838 = !DILocation(line: 472, column: 15, scope: !1835)
!1839 = !DILocation(line: 472, column: 14, scope: !1835)
!1840 = !DILocation(line: 472, column: 7, scope: !1835)
!1841 = !DILocation(line: 474, column: 16, scope: !1817)
!1842 = !DILocation(line: 474, column: 5, scope: !1817)
!1843 = !DILocation(line: 478, column: 21, scope: !1817)
!1844 = !DILocation(line: 478, column: 29, scope: !1817)
!1845 = !DILocation(line: 478, column: 14, scope: !1817)
!1846 = !DILocation(line: 478, column: 12, scope: !1817)
!1847 = !DILocation(line: 479, column: 9, scope: !1848)
!1848 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 479, column: 9)
!1849 = !DILocation(line: 479, column: 16, scope: !1848)
!1850 = !DILocation(line: 479, column: 9, scope: !1817)
!1851 = !DILocation(line: 480, column: 11, scope: !1852)
!1852 = distinct !DILexicalBlock(scope: !1853, file: !1, line: 480, column: 11)
!1853 = distinct !DILexicalBlock(scope: !1848, file: !1, line: 479, column: 23)
!1854 = !DILocation(line: 480, column: 17, scope: !1852)
!1855 = !DILocation(line: 480, column: 11, scope: !1853)
!1856 = !DILocation(line: 481, column: 9, scope: !1852)
!1857 = !DILocation(line: 482, column: 15, scope: !1853)
!1858 = !DILocation(line: 482, column: 14, scope: !1853)
!1859 = !DILocation(line: 482, column: 7, scope: !1853)
!1860 = !DILocation(line: 485, column: 23, scope: !1817)
!1861 = !DILocation(line: 485, column: 11, scope: !1817)
!1862 = !DILocation(line: 485, column: 9, scope: !1817)
!1863 = !DILocation(line: 486, column: 9, scope: !1864)
!1864 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 486, column: 9)
!1865 = !DILocation(line: 486, column: 13, scope: !1864)
!1866 = !DILocation(line: 486, column: 9, scope: !1817)
!1867 = !DILocation(line: 487, column: 26, scope: !1864)
!1868 = !DILocation(line: 487, column: 13, scope: !1864)
!1869 = !DILocation(line: 487, column: 11, scope: !1864)
!1870 = !DILocation(line: 487, column: 7, scope: !1864)
!1871 = !DILocation(line: 489, column: 9, scope: !1872)
!1872 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 489, column: 9)
!1873 = !DILocation(line: 489, column: 9, scope: !1817)
!1874 = !DILocation(line: 490, column: 17, scope: !1875)
!1875 = distinct !DILexicalBlock(scope: !1872, file: !1, line: 489, column: 14)
!1876 = !DILocation(line: 490, column: 7, scope: !1875)
!1877 = !DILocation(line: 491, column: 14, scope: !1875)
!1878 = !DILocation(line: 491, column: 7, scope: !1875)
!1879 = !DILocation(line: 494, column: 12, scope: !1817)
!1880 = !DILocation(line: 494, column: 5, scope: !1817)
!1881 = !DILocation(line: 496, column: 1, scope: !1001)
!1882 = !DILocalVariable(name: "fd", arg: 1, scope: !1004, file: !1, line: 499, type: !339)
!1883 = !DILocation(line: 499, column: 32, scope: !1004)
!1884 = !DILocalVariable(name: "saved_errno", scope: !1004, file: !1, line: 500, type: !339)
!1885 = !DILocation(line: 500, column: 7, scope: !1004)
!1886 = !DILocalVariable(name: "rc", scope: !1004, file: !1, line: 501, type: !339)
!1887 = !DILocation(line: 501, column: 7, scope: !1004)
!1888 = !DILocation(line: 503, column: 3, scope: !1004)
!1889 = !DILocation(line: 503, column: 3, scope: !1890)
!1890 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 1)
!1891 = !DILocation(line: 503, column: 3, scope: !1892)
!1892 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 2)
!1893 = !DILocation(line: 503, column: 3, scope: !1894)
!1894 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 3)
!1895 = !DILocation(line: 505, column: 17, scope: !1004)
!1896 = !DILocation(line: 505, column: 15, scope: !1004)
!1897 = !DILocation(line: 506, column: 14, scope: !1004)
!1898 = !DILocation(line: 506, column: 8, scope: !1004)
!1899 = !DILocation(line: 506, column: 6, scope: !1004)
!1900 = !DILocation(line: 507, column: 7, scope: !1901)
!1901 = distinct !DILexicalBlock(scope: !1004, file: !1, line: 507, column: 7)
!1902 = !DILocation(line: 507, column: 10, scope: !1901)
!1903 = !DILocation(line: 507, column: 7, scope: !1004)
!1904 = !DILocation(line: 508, column: 11, scope: !1905)
!1905 = distinct !DILexicalBlock(scope: !1901, file: !1, line: 507, column: 17)
!1906 = !DILocation(line: 508, column: 10, scope: !1905)
!1907 = !DILocation(line: 508, column: 8, scope: !1905)
!1908 = !DILocation(line: 509, column: 9, scope: !1909)
!1909 = distinct !DILexicalBlock(scope: !1905, file: !1, line: 509, column: 9)
!1910 = !DILocation(line: 509, column: 12, scope: !1909)
!1911 = !DILocation(line: 509, column: 22, scope: !1909)
!1912 = !DILocation(line: 509, column: 25, scope: !1913)
!1913 = !DILexicalBlockFile(scope: !1909, file: !1, discriminator: 1)
!1914 = !DILocation(line: 509, column: 28, scope: !1913)
!1915 = !DILocation(line: 509, column: 9, scope: !1913)
!1916 = !DILocation(line: 510, column: 10, scope: !1909)
!1917 = !DILocation(line: 510, column: 7, scope: !1909)
!1918 = !DILocation(line: 511, column: 13, scope: !1905)
!1919 = !DILocation(line: 511, column: 5, scope: !1905)
!1920 = !DILocation(line: 511, column: 11, scope: !1905)
!1921 = !DILocation(line: 512, column: 3, scope: !1905)
!1922 = !DILocation(line: 514, column: 10, scope: !1004)
!1923 = !DILocation(line: 514, column: 3, scope: !1004)
!1924 = !DILocalVariable(name: "fd", arg: 1, scope: !1010, file: !1, line: 555, type: !339)
!1925 = !DILocation(line: 555, column: 28, scope: !1010)
!1926 = !DILocalVariable(name: "set", arg: 2, scope: !1010, file: !1, line: 555, type: !339)
!1927 = !DILocation(line: 555, column: 36, scope: !1010)
!1928 = !DILocalVariable(name: "flags", scope: !1010, file: !1, line: 556, type: !339)
!1929 = !DILocation(line: 556, column: 7, scope: !1010)
!1930 = !DILocalVariable(name: "r", scope: !1010, file: !1, line: 557, type: !339)
!1931 = !DILocation(line: 557, column: 7, scope: !1010)
!1932 = !DILocation(line: 559, column: 3, scope: !1010)
!1933 = !DILocation(line: 560, column: 15, scope: !1010)
!1934 = !DILocation(line: 560, column: 9, scope: !1010)
!1935 = !DILocation(line: 560, column: 7, scope: !1010)
!1936 = !DILocation(line: 560, column: 5, scope: !1010)
!1937 = !DILocation(line: 561, column: 10, scope: !1010)
!1938 = !DILocation(line: 561, column: 12, scope: !1010)
!1939 = !DILocation(line: 561, column: 18, scope: !1010)
!1940 = !DILocation(line: 561, column: 21, scope: !1941)
!1941 = !DILexicalBlockFile(scope: !1010, file: !1, discriminator: 1)
!1942 = !DILocation(line: 561, column: 27, scope: !1941)
!1943 = !DILocation(line: 560, column: 5, scope: !1941)
!1944 = !DILocation(line: 563, column: 7, scope: !1945)
!1945 = distinct !DILexicalBlock(scope: !1010, file: !1, line: 563, column: 7)
!1946 = !DILocation(line: 563, column: 9, scope: !1945)
!1947 = !DILocation(line: 563, column: 7, scope: !1010)
!1948 = !DILocation(line: 564, column: 13, scope: !1945)
!1949 = !DILocation(line: 564, column: 12, scope: !1945)
!1950 = !DILocation(line: 564, column: 5, scope: !1945)
!1951 = !DILocation(line: 567, column: 10, scope: !1952)
!1952 = distinct !DILexicalBlock(scope: !1010, file: !1, line: 567, column: 7)
!1953 = !DILocation(line: 567, column: 12, scope: !1952)
!1954 = !DILocation(line: 567, column: 8, scope: !1952)
!1955 = !DILocation(line: 567, column: 7, scope: !1952)
!1956 = !DILocation(line: 567, column: 31, scope: !1952)
!1957 = !DILocation(line: 567, column: 30, scope: !1952)
!1958 = !DILocation(line: 567, column: 29, scope: !1952)
!1959 = !DILocation(line: 567, column: 26, scope: !1952)
!1960 = !DILocation(line: 567, column: 7, scope: !1010)
!1961 = !DILocation(line: 568, column: 5, scope: !1952)
!1962 = !DILocation(line: 570, column: 7, scope: !1963)
!1963 = distinct !DILexicalBlock(scope: !1010, file: !1, line: 570, column: 7)
!1964 = !DILocation(line: 570, column: 7, scope: !1010)
!1965 = !DILocation(line: 571, column: 13, scope: !1963)
!1966 = !DILocation(line: 571, column: 15, scope: !1963)
!1967 = !DILocation(line: 571, column: 11, scope: !1963)
!1968 = !DILocation(line: 571, column: 5, scope: !1963)
!1969 = !DILocation(line: 573, column: 13, scope: !1963)
!1970 = !DILocation(line: 573, column: 15, scope: !1963)
!1971 = !DILocation(line: 573, column: 11, scope: !1963)
!1972 = !DILocation(line: 575, column: 3, scope: !1010)
!1973 = !DILocation(line: 576, column: 15, scope: !1010)
!1974 = !DILocation(line: 576, column: 28, scope: !1010)
!1975 = !DILocation(line: 576, column: 9, scope: !1010)
!1976 = !DILocation(line: 576, column: 7, scope: !1010)
!1977 = !DILocation(line: 576, column: 5, scope: !1010)
!1978 = !DILocation(line: 577, column: 10, scope: !1010)
!1979 = !DILocation(line: 577, column: 12, scope: !1010)
!1980 = !DILocation(line: 577, column: 18, scope: !1010)
!1981 = !DILocation(line: 577, column: 21, scope: !1941)
!1982 = !DILocation(line: 577, column: 27, scope: !1941)
!1983 = !DILocation(line: 576, column: 5, scope: !1941)
!1984 = !DILocation(line: 579, column: 7, scope: !1985)
!1985 = distinct !DILexicalBlock(scope: !1010, file: !1, line: 579, column: 7)
!1986 = !DILocation(line: 579, column: 7, scope: !1010)
!1987 = !DILocation(line: 580, column: 13, scope: !1985)
!1988 = !DILocation(line: 580, column: 12, scope: !1985)
!1989 = !DILocation(line: 580, column: 5, scope: !1985)
!1990 = !DILocation(line: 582, column: 3, scope: !1010)
!1991 = !DILocation(line: 583, column: 1, scope: !1010)
!1992 = !DILocalVariable(name: "fd", arg: 1, scope: !1011, file: !1, line: 586, type: !339)
!1993 = !DILocation(line: 586, column: 27, scope: !1011)
!1994 = !DILocalVariable(name: "set", arg: 2, scope: !1011, file: !1, line: 586, type: !339)
!1995 = !DILocation(line: 586, column: 35, scope: !1011)
!1996 = !DILocalVariable(name: "flags", scope: !1011, file: !1, line: 587, type: !339)
!1997 = !DILocation(line: 587, column: 7, scope: !1011)
!1998 = !DILocalVariable(name: "r", scope: !1011, file: !1, line: 588, type: !339)
!1999 = !DILocation(line: 588, column: 7, scope: !1011)
!2000 = !DILocation(line: 590, column: 3, scope: !1011)
!2001 = !DILocation(line: 591, column: 15, scope: !1011)
!2002 = !DILocation(line: 591, column: 9, scope: !1011)
!2003 = !DILocation(line: 591, column: 7, scope: !1011)
!2004 = !DILocation(line: 591, column: 5, scope: !1011)
!2005 = !DILocation(line: 592, column: 10, scope: !1011)
!2006 = !DILocation(line: 592, column: 12, scope: !1011)
!2007 = !DILocation(line: 592, column: 18, scope: !1011)
!2008 = !DILocation(line: 592, column: 21, scope: !2009)
!2009 = !DILexicalBlockFile(scope: !1011, file: !1, discriminator: 1)
!2010 = !DILocation(line: 592, column: 27, scope: !2009)
!2011 = !DILocation(line: 591, column: 5, scope: !2009)
!2012 = !DILocation(line: 594, column: 7, scope: !2013)
!2013 = distinct !DILexicalBlock(scope: !1011, file: !1, line: 594, column: 7)
!2014 = !DILocation(line: 594, column: 9, scope: !2013)
!2015 = !DILocation(line: 594, column: 7, scope: !1011)
!2016 = !DILocation(line: 595, column: 13, scope: !2013)
!2017 = !DILocation(line: 595, column: 12, scope: !2013)
!2018 = !DILocation(line: 595, column: 5, scope: !2013)
!2019 = !DILocation(line: 598, column: 10, scope: !2020)
!2020 = distinct !DILexicalBlock(scope: !1011, file: !1, line: 598, column: 7)
!2021 = !DILocation(line: 598, column: 12, scope: !2020)
!2022 = !DILocation(line: 598, column: 8, scope: !2020)
!2023 = !DILocation(line: 598, column: 7, scope: !2020)
!2024 = !DILocation(line: 598, column: 31, scope: !2020)
!2025 = !DILocation(line: 598, column: 30, scope: !2020)
!2026 = !DILocation(line: 598, column: 29, scope: !2020)
!2027 = !DILocation(line: 598, column: 26, scope: !2020)
!2028 = !DILocation(line: 598, column: 7, scope: !1011)
!2029 = !DILocation(line: 599, column: 5, scope: !2020)
!2030 = !DILocation(line: 601, column: 7, scope: !2031)
!2031 = distinct !DILexicalBlock(scope: !1011, file: !1, line: 601, column: 7)
!2032 = !DILocation(line: 601, column: 7, scope: !1011)
!2033 = !DILocation(line: 602, column: 13, scope: !2031)
!2034 = !DILocation(line: 602, column: 15, scope: !2031)
!2035 = !DILocation(line: 602, column: 11, scope: !2031)
!2036 = !DILocation(line: 602, column: 5, scope: !2031)
!2037 = !DILocation(line: 604, column: 13, scope: !2031)
!2038 = !DILocation(line: 604, column: 15, scope: !2031)
!2039 = !DILocation(line: 604, column: 11, scope: !2031)
!2040 = !DILocation(line: 606, column: 3, scope: !1011)
!2041 = !DILocation(line: 607, column: 15, scope: !1011)
!2042 = !DILocation(line: 607, column: 28, scope: !1011)
!2043 = !DILocation(line: 607, column: 9, scope: !1011)
!2044 = !DILocation(line: 607, column: 7, scope: !1011)
!2045 = !DILocation(line: 607, column: 5, scope: !1011)
!2046 = !DILocation(line: 608, column: 10, scope: !1011)
!2047 = !DILocation(line: 608, column: 12, scope: !1011)
!2048 = !DILocation(line: 608, column: 18, scope: !1011)
!2049 = !DILocation(line: 608, column: 21, scope: !2009)
!2050 = !DILocation(line: 608, column: 27, scope: !2009)
!2051 = !DILocation(line: 607, column: 5, scope: !2009)
!2052 = !DILocation(line: 610, column: 7, scope: !2053)
!2053 = distinct !DILexicalBlock(scope: !1011, file: !1, line: 610, column: 7)
!2054 = !DILocation(line: 610, column: 7, scope: !1011)
!2055 = !DILocation(line: 611, column: 13, scope: !2053)
!2056 = !DILocation(line: 611, column: 12, scope: !2053)
!2057 = !DILocation(line: 611, column: 5, scope: !2053)
!2058 = !DILocation(line: 613, column: 3, scope: !1011)
!2059 = !DILocation(line: 614, column: 1, scope: !1011)
!2060 = !DILocalVariable(name: "fd", arg: 1, scope: !1012, file: !1, line: 620, type: !339)
!2061 = !DILocation(line: 620, column: 17, scope: !1012)
!2062 = !DILocalVariable(name: "err", scope: !1012, file: !1, line: 621, type: !339)
!2063 = !DILocation(line: 621, column: 7, scope: !1012)
!2064 = !DILocation(line: 623, column: 12, scope: !1012)
!2065 = !DILocation(line: 623, column: 8, scope: !1012)
!2066 = !DILocation(line: 623, column: 6, scope: !1012)
!2067 = !DILocation(line: 625, column: 7, scope: !2068)
!2068 = distinct !DILexicalBlock(scope: !1012, file: !1, line: 625, column: 7)
!2069 = !DILocation(line: 625, column: 10, scope: !2068)
!2070 = !DILocation(line: 625, column: 7, scope: !1012)
!2071 = !DILocation(line: 626, column: 13, scope: !2068)
!2072 = !DILocation(line: 626, column: 12, scope: !2068)
!2073 = !DILocation(line: 626, column: 5, scope: !2068)
!2074 = !DILocation(line: 628, column: 21, scope: !1012)
!2075 = !DILocation(line: 628, column: 9, scope: !1012)
!2076 = !DILocation(line: 628, column: 7, scope: !1012)
!2077 = !DILocation(line: 629, column: 7, scope: !2078)
!2078 = distinct !DILexicalBlock(scope: !1012, file: !1, line: 629, column: 7)
!2079 = !DILocation(line: 629, column: 7, scope: !1012)
!2080 = !DILocation(line: 630, column: 15, scope: !2081)
!2081 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 629, column: 12)
!2082 = !DILocation(line: 630, column: 5, scope: !2081)
!2083 = !DILocation(line: 631, column: 12, scope: !2081)
!2084 = !DILocation(line: 631, column: 5, scope: !2081)
!2085 = !DILocation(line: 634, column: 10, scope: !1012)
!2086 = !DILocation(line: 634, column: 3, scope: !1012)
!2087 = !DILocation(line: 635, column: 1, scope: !1012)
!2088 = !DILocalVariable(name: "fd", arg: 1, scope: !1013, file: !1, line: 638, type: !339)
!2089 = !DILocation(line: 638, column: 25, scope: !1013)
!2090 = !DILocalVariable(name: "msg", arg: 2, scope: !1013, file: !1, line: 638, type: !1016)
!2091 = !DILocation(line: 638, column: 44, scope: !1013)
!2092 = !DILocalVariable(name: "flags", arg: 3, scope: !1013, file: !1, line: 638, type: !339)
!2093 = !DILocation(line: 638, column: 53, scope: !1013)
!2094 = !DILocalVariable(name: "cmsg", scope: !1013, file: !1, line: 639, type: !896)
!2095 = !DILocation(line: 639, column: 19, scope: !1013)
!2096 = !DILocalVariable(name: "rc", scope: !1013, file: !1, line: 640, type: !620)
!2097 = !DILocation(line: 640, column: 11, scope: !1013)
!2098 = !DILocalVariable(name: "pfd", scope: !1013, file: !1, line: 641, type: !907)
!2099 = !DILocation(line: 641, column: 8, scope: !1013)
!2100 = !DILocalVariable(name: "end", scope: !1013, file: !1, line: 642, type: !907)
!2101 = !DILocation(line: 642, column: 8, scope: !1013)
!2102 = !DILocation(line: 645, column: 7, scope: !2103)
!2103 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 645, column: 7)
!2104 = !DILocation(line: 645, column: 27, scope: !2103)
!2105 = !DILocation(line: 645, column: 7, scope: !1013)
!2106 = !DILocation(line: 646, column: 18, scope: !2107)
!2107 = distinct !DILexicalBlock(scope: !2103, file: !1, line: 645, column: 33)
!2108 = !DILocation(line: 646, column: 22, scope: !2107)
!2109 = !DILocation(line: 646, column: 27, scope: !2107)
!2110 = !DILocation(line: 646, column: 33, scope: !2107)
!2111 = !DILocation(line: 646, column: 10, scope: !2107)
!2112 = !DILocation(line: 646, column: 8, scope: !2107)
!2113 = !DILocation(line: 647, column: 9, scope: !2114)
!2114 = distinct !DILexicalBlock(scope: !2107, file: !1, line: 647, column: 9)
!2115 = !DILocation(line: 647, column: 12, scope: !2114)
!2116 = !DILocation(line: 647, column: 9, scope: !2107)
!2117 = !DILocation(line: 648, column: 14, scope: !2114)
!2118 = !DILocation(line: 648, column: 7, scope: !2114)
!2119 = !DILocation(line: 649, column: 9, scope: !2120)
!2120 = distinct !DILexicalBlock(scope: !2107, file: !1, line: 649, column: 9)
!2121 = !DILocation(line: 649, column: 15, scope: !2120)
!2122 = !DILocation(line: 649, column: 9, scope: !2107)
!2123 = !DILocation(line: 650, column: 15, scope: !2120)
!2124 = !DILocation(line: 650, column: 14, scope: !2120)
!2125 = !DILocation(line: 650, column: 7, scope: !2120)
!2126 = !DILocation(line: 651, column: 18, scope: !2107)
!2127 = !DILocation(line: 651, column: 22, scope: !2107)
!2128 = !DILocation(line: 651, column: 27, scope: !2107)
!2129 = !DILocation(line: 651, column: 10, scope: !2107)
!2130 = !DILocation(line: 651, column: 8, scope: !2107)
!2131 = !DILocation(line: 652, column: 9, scope: !2132)
!2132 = distinct !DILexicalBlock(scope: !2107, file: !1, line: 652, column: 9)
!2133 = !DILocation(line: 652, column: 12, scope: !2132)
!2134 = !DILocation(line: 652, column: 9, scope: !2107)
!2135 = !DILocation(line: 653, column: 15, scope: !2132)
!2136 = !DILocation(line: 653, column: 14, scope: !2132)
!2137 = !DILocation(line: 653, column: 7, scope: !2132)
!2138 = !DILocation(line: 654, column: 25, scope: !2107)
!2139 = !DILocation(line: 655, column: 3, scope: !2107)
!2140 = !DILocation(line: 656, column: 18, scope: !2141)
!2141 = distinct !DILexicalBlock(scope: !2103, file: !1, line: 655, column: 10)
!2142 = !DILocation(line: 656, column: 22, scope: !2141)
!2143 = !DILocation(line: 656, column: 27, scope: !2141)
!2144 = !DILocation(line: 656, column: 10, scope: !2141)
!2145 = !DILocation(line: 656, column: 8, scope: !2141)
!2146 = !DILocation(line: 661, column: 7, scope: !2147)
!2147 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 661, column: 7)
!2148 = !DILocation(line: 661, column: 10, scope: !2147)
!2149 = !DILocation(line: 661, column: 7, scope: !1013)
!2150 = !DILocation(line: 662, column: 13, scope: !2147)
!2151 = !DILocation(line: 662, column: 12, scope: !2147)
!2152 = !DILocation(line: 662, column: 5, scope: !2147)
!2153 = !DILocation(line: 663, column: 7, scope: !2154)
!2154 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 663, column: 7)
!2155 = !DILocation(line: 663, column: 12, scope: !2154)
!2156 = !DILocation(line: 663, column: 27, scope: !2154)
!2157 = !DILocation(line: 663, column: 7, scope: !1013)
!2158 = !DILocation(line: 664, column: 12, scope: !2154)
!2159 = !DILocation(line: 664, column: 5, scope: !2154)
!2160 = !DILocation(line: 665, column: 15, scope: !2161)
!2161 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 665, column: 3)
!2162 = !DILocation(line: 665, column: 15, scope: !2163)
!2163 = !DILexicalBlockFile(scope: !2161, file: !1, discriminator: 1)
!2164 = !DILocation(line: 665, column: 15, scope: !2165)
!2165 = !DILexicalBlockFile(scope: !2161, file: !1, discriminator: 2)
!2166 = !DILocation(line: 665, column: 15, scope: !2167)
!2167 = !DILexicalBlockFile(scope: !2161, file: !1, discriminator: 3)
!2168 = !DILocation(line: 665, column: 13, scope: !2167)
!2169 = !DILocation(line: 665, column: 8, scope: !2167)
!2170 = !DILocation(line: 665, column: 35, scope: !2171)
!2171 = !DILexicalBlockFile(scope: !2172, file: !1, discriminator: 4)
!2172 = distinct !DILexicalBlock(scope: !2161, file: !1, line: 665, column: 3)
!2173 = !DILocation(line: 665, column: 40, scope: !2171)
!2174 = !DILocation(line: 665, column: 3, scope: !2171)
!2175 = !DILocation(line: 666, column: 9, scope: !2176)
!2176 = distinct !DILexicalBlock(scope: !2172, file: !1, line: 666, column: 9)
!2177 = !DILocation(line: 666, column: 15, scope: !2176)
!2178 = !DILocation(line: 666, column: 25, scope: !2176)
!2179 = !DILocation(line: 666, column: 9, scope: !2172)
!2180 = !DILocation(line: 667, column: 25, scope: !2181)
!2181 = distinct !DILexicalBlock(scope: !2176, file: !1, line: 667, column: 7)
!2182 = !DILocation(line: 667, column: 18, scope: !2181)
!2183 = !DILocation(line: 667, column: 16, scope: !2181)
!2184 = !DILocation(line: 668, column: 34, scope: !2181)
!2185 = !DILocation(line: 668, column: 26, scope: !2181)
!2186 = !DILocation(line: 668, column: 41, scope: !2181)
!2187 = !DILocation(line: 668, column: 47, scope: !2181)
!2188 = !DILocation(line: 668, column: 39, scope: !2181)
!2189 = !DILocation(line: 668, column: 18, scope: !2181)
!2190 = !DILocation(line: 668, column: 16, scope: !2181)
!2191 = !DILocation(line: 667, column: 12, scope: !2181)
!2192 = !DILocation(line: 669, column: 12, scope: !2193)
!2193 = distinct !DILexicalBlock(scope: !2181, file: !1, line: 667, column: 7)
!2194 = !DILocation(line: 669, column: 18, scope: !2193)
!2195 = !DILocation(line: 669, column: 16, scope: !2193)
!2196 = !DILocation(line: 667, column: 7, scope: !2197)
!2197 = !DILexicalBlockFile(scope: !2181, file: !1, discriminator: 1)
!2198 = !DILocation(line: 671, column: 22, scope: !2193)
!2199 = !DILocation(line: 671, column: 21, scope: !2193)
!2200 = !DILocation(line: 671, column: 9, scope: !2193)
!2201 = !DILocation(line: 670, column: 16, scope: !2193)
!2202 = !DILocation(line: 667, column: 7, scope: !2203)
!2203 = !DILexicalBlockFile(scope: !2193, file: !1, discriminator: 2)
!2204 = !DILocation(line: 671, column: 28, scope: !2197)
!2205 = !DILocation(line: 666, column: 28, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !2176, file: !1, discriminator: 1)
!2207 = !DILocation(line: 665, column: 56, scope: !2208)
!2208 = !DILexicalBlockFile(scope: !2172, file: !1, discriminator: 5)
!2209 = !DILocation(line: 665, column: 54, scope: !2208)
!2210 = !DILocation(line: 665, column: 3, scope: !2208)
!2211 = !DILocation(line: 672, column: 10, scope: !1013)
!2212 = !DILocation(line: 672, column: 3, scope: !1013)
!2213 = !DILocation(line: 673, column: 1, scope: !1013)
!2214 = !DILocalVariable(name: "buffer", arg: 1, scope: !1034, file: !1, line: 676, type: !551)
!2215 = !DILocation(line: 676, column: 18, scope: !1034)
!2216 = !DILocalVariable(name: "size", arg: 2, scope: !1034, file: !1, line: 676, type: !1037)
!2217 = !DILocation(line: 676, column: 34, scope: !1034)
!2218 = !DILocation(line: 677, column: 7, scope: !2219)
!2219 = distinct !DILexicalBlock(scope: !1034, file: !1, line: 677, column: 7)
!2220 = !DILocation(line: 677, column: 14, scope: !2219)
!2221 = !DILocation(line: 677, column: 22, scope: !2219)
!2222 = !DILocation(line: 677, column: 25, scope: !2223)
!2223 = !DILexicalBlockFile(scope: !2219, file: !1, discriminator: 1)
!2224 = !DILocation(line: 677, column: 30, scope: !2223)
!2225 = !DILocation(line: 677, column: 7, scope: !2223)
!2226 = !DILocation(line: 678, column: 5, scope: !2219)
!2227 = !DILocation(line: 680, column: 14, scope: !2228)
!2228 = distinct !DILexicalBlock(scope: !1034, file: !1, line: 680, column: 7)
!2229 = !DILocation(line: 680, column: 23, scope: !2228)
!2230 = !DILocation(line: 680, column: 22, scope: !2228)
!2231 = !DILocation(line: 680, column: 7, scope: !2228)
!2232 = !DILocation(line: 680, column: 29, scope: !2228)
!2233 = !DILocation(line: 680, column: 7, scope: !1034)
!2234 = !DILocation(line: 681, column: 13, scope: !2228)
!2235 = !DILocation(line: 681, column: 12, scope: !2228)
!2236 = !DILocation(line: 681, column: 5, scope: !2228)
!2237 = !DILocation(line: 683, column: 18, scope: !1034)
!2238 = !DILocation(line: 683, column: 11, scope: !1034)
!2239 = !DILocation(line: 683, column: 4, scope: !1034)
!2240 = !DILocation(line: 683, column: 9, scope: !1034)
!2241 = !DILocation(line: 684, column: 8, scope: !2242)
!2242 = distinct !DILexicalBlock(scope: !1034, file: !1, line: 684, column: 7)
!2243 = !DILocation(line: 684, column: 7, scope: !2242)
!2244 = !DILocation(line: 684, column: 13, scope: !2242)
!2245 = !DILocation(line: 684, column: 17, scope: !2242)
!2246 = !DILocation(line: 684, column: 28, scope: !2247)
!2247 = !DILexicalBlockFile(scope: !2242, file: !1, discriminator: 1)
!2248 = !DILocation(line: 684, column: 27, scope: !2247)
!2249 = !DILocation(line: 684, column: 33, scope: !2247)
!2250 = !DILocation(line: 684, column: 20, scope: !2247)
!2251 = !DILocation(line: 684, column: 38, scope: !2247)
!2252 = !DILocation(line: 684, column: 7, scope: !2247)
!2253 = !DILocation(line: 685, column: 13, scope: !2254)
!2254 = distinct !DILexicalBlock(scope: !2242, file: !1, line: 684, column: 46)
!2255 = !DILocation(line: 685, column: 12, scope: !2254)
!2256 = !DILocation(line: 685, column: 17, scope: !2254)
!2257 = !DILocation(line: 685, column: 5, scope: !2254)
!2258 = !DILocation(line: 685, column: 21, scope: !2254)
!2259 = !DILocation(line: 686, column: 7, scope: !2254)
!2260 = !DILocation(line: 686, column: 12, scope: !2254)
!2261 = !DILocation(line: 687, column: 3, scope: !2254)
!2262 = !DILocation(line: 689, column: 3, scope: !1034)
!2263 = !DILocation(line: 690, column: 1, scope: !1034)
!2264 = !DILocalVariable(name: "dir", arg: 1, scope: !1038, file: !1, line: 693, type: !637)
!2265 = !DILocation(line: 693, column: 26, scope: !1038)
!2266 = !DILocation(line: 694, column: 13, scope: !2267)
!2267 = distinct !DILexicalBlock(scope: !1038, file: !1, line: 694, column: 7)
!2268 = !DILocation(line: 694, column: 7, scope: !2267)
!2269 = !DILocation(line: 694, column: 7, scope: !1038)
!2270 = !DILocation(line: 695, column: 13, scope: !2267)
!2271 = !DILocation(line: 695, column: 12, scope: !2267)
!2272 = !DILocation(line: 695, column: 5, scope: !2267)
!2273 = !DILocation(line: 697, column: 3, scope: !1038)
!2274 = !DILocation(line: 698, column: 1, scope: !1038)
!2275 = !DILocalVariable(name: "fd", scope: !1041, file: !1, line: 702, type: !339)
!2276 = !DILocation(line: 702, column: 7, scope: !1041)
!2277 = !DILocation(line: 707, column: 11, scope: !2278)
!2278 = distinct !DILexicalBlock(scope: !1041, file: !1, line: 707, column: 3)
!2279 = !DILocation(line: 707, column: 8, scope: !2278)
!2280 = !DILocation(line: 708, column: 21, scope: !2281)
!2281 = distinct !DILexicalBlock(scope: !2282, file: !1, line: 708, column: 9)
!2282 = distinct !DILexicalBlock(scope: !2278, file: !1, line: 707, column: 3)
!2283 = !DILocation(line: 708, column: 9, scope: !2281)
!2284 = !DILocation(line: 708, column: 28, scope: !2281)
!2285 = !DILocation(line: 708, column: 31, scope: !2286)
!2286 = !DILexicalBlockFile(scope: !2281, file: !1, discriminator: 1)
!2287 = !DILocation(line: 708, column: 34, scope: !2286)
!2288 = !DILocation(line: 708, column: 9, scope: !2286)
!2289 = !DILocation(line: 709, column: 7, scope: !2281)
!2290 = !DILocation(line: 708, column: 36, scope: !2291)
!2291 = !DILexicalBlockFile(scope: !2281, file: !1, discriminator: 2)
!2292 = !DILocation(line: 707, column: 20, scope: !2293)
!2293 = !DILexicalBlockFile(scope: !2282, file: !1, discriminator: 1)
!2294 = !DILocation(line: 707, column: 3, scope: !2293)
!2295 = !DILocation(line: 710, column: 1, scope: !1041)
!2296 = !DILocalVariable(name: "handle", arg: 1, scope: !1042, file: !1, line: 713, type: !926)
!2297 = !DILocation(line: 713, column: 34, scope: !1042)
!2298 = !DILocalVariable(name: "fd", arg: 2, scope: !1042, file: !1, line: 713, type: !1045)
!2299 = !DILocation(line: 713, column: 54, scope: !1042)
!2300 = !DILocalVariable(name: "fd_out", scope: !1042, file: !1, line: 714, type: !339)
!2301 = !DILocation(line: 714, column: 7, scope: !1042)
!2302 = !DILocation(line: 716, column: 11, scope: !1042)
!2303 = !DILocation(line: 716, column: 19, scope: !1042)
!2304 = !DILocation(line: 716, column: 3, scope: !1042)
!2305 = !DILocation(line: 720, column: 14, scope: !2306)
!2306 = distinct !DILexicalBlock(scope: !1042, file: !1, line: 716, column: 25)
!2307 = !DILocation(line: 720, column: 12, scope: !2306)
!2308 = !DILocation(line: 721, column: 5, scope: !2306)
!2309 = !DILocation(line: 724, column: 28, scope: !2306)
!2310 = !DILocation(line: 724, column: 37, scope: !2306)
!2311 = !DILocation(line: 724, column: 48, scope: !2306)
!2312 = !DILocation(line: 724, column: 12, scope: !2306)
!2313 = !DILocation(line: 725, column: 5, scope: !2306)
!2314 = !DILocation(line: 728, column: 29, scope: !2306)
!2315 = !DILocation(line: 728, column: 38, scope: !2306)
!2316 = !DILocation(line: 728, column: 49, scope: !2306)
!2317 = !DILocation(line: 728, column: 12, scope: !2306)
!2318 = !DILocation(line: 729, column: 5, scope: !2306)
!2319 = !DILocation(line: 732, column: 5, scope: !2306)
!2320 = !DILocation(line: 735, column: 7, scope: !2321)
!2321 = distinct !DILexicalBlock(scope: !1042, file: !1, line: 735, column: 7)
!2322 = !DILocation(line: 735, column: 30, scope: !2321)
!2323 = !DILocation(line: 735, column: 33, scope: !2324)
!2324 = !DILexicalBlockFile(scope: !2321, file: !1, discriminator: 1)
!2325 = !DILocation(line: 735, column: 40, scope: !2324)
!2326 = !DILocation(line: 735, column: 7, scope: !2324)
!2327 = !DILocation(line: 736, column: 5, scope: !2321)
!2328 = !DILocation(line: 738, column: 9, scope: !1042)
!2329 = !DILocation(line: 738, column: 4, scope: !1042)
!2330 = !DILocation(line: 738, column: 7, scope: !1042)
!2331 = !DILocation(line: 739, column: 3, scope: !1042)
!2332 = !DILocation(line: 740, column: 1, scope: !1042)
!2333 = !DILocalVariable(name: "w", arg: 1, scope: !1047, file: !1, line: 811, type: !344)
!2334 = !DILocation(line: 811, column: 28, scope: !1047)
!2335 = !DILocalVariable(name: "cb", arg: 2, scope: !1047, file: !1, line: 811, type: !350)
!2336 = !DILocation(line: 811, column: 41, scope: !1047)
!2337 = !DILocalVariable(name: "fd", arg: 3, scope: !1047, file: !1, line: 811, type: !339)
!2338 = !DILocation(line: 811, column: 49, scope: !1047)
!2339 = !DILocation(line: 812, column: 3, scope: !1047)
!2340 = !DILocation(line: 812, column: 3, scope: !2341)
!2341 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 1)
!2342 = !DILocation(line: 812, column: 3, scope: !2343)
!2343 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 2)
!2344 = !DILocation(line: 812, column: 3, scope: !2345)
!2345 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 3)
!2346 = !DILocation(line: 813, column: 3, scope: !1047)
!2347 = !DILocation(line: 813, column: 3, scope: !2341)
!2348 = !DILocation(line: 813, column: 3, scope: !2343)
!2349 = !DILocation(line: 813, column: 3, scope: !2345)
!2350 = !DILocation(line: 814, column: 3, scope: !1047)
!2351 = !DILocation(line: 814, column: 3, scope: !2352)
!2352 = !DILexicalBlockFile(scope: !2353, file: !1, discriminator: 1)
!2353 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 814, column: 3)
!2354 = !DILocation(line: 815, column: 3, scope: !1047)
!2355 = !DILocation(line: 815, column: 3, scope: !2356)
!2356 = !DILexicalBlockFile(scope: !2357, file: !1, discriminator: 1)
!2357 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 815, column: 3)
!2358 = !DILocation(line: 816, column: 11, scope: !1047)
!2359 = !DILocation(line: 816, column: 3, scope: !1047)
!2360 = !DILocation(line: 816, column: 6, scope: !1047)
!2361 = !DILocation(line: 816, column: 9, scope: !1047)
!2362 = !DILocation(line: 817, column: 11, scope: !1047)
!2363 = !DILocation(line: 817, column: 3, scope: !1047)
!2364 = !DILocation(line: 817, column: 6, scope: !1047)
!2365 = !DILocation(line: 817, column: 9, scope: !1047)
!2366 = !DILocation(line: 818, column: 3, scope: !1047)
!2367 = !DILocation(line: 818, column: 6, scope: !1047)
!2368 = !DILocation(line: 818, column: 13, scope: !1047)
!2369 = !DILocation(line: 819, column: 3, scope: !1047)
!2370 = !DILocation(line: 819, column: 6, scope: !1047)
!2371 = !DILocation(line: 819, column: 14, scope: !1047)
!2372 = !DILocation(line: 825, column: 1, scope: !1047)
!2373 = !DILocalVariable(name: "loop", arg: 1, scope: !1050, file: !1, line: 828, type: !323)
!2374 = !DILocation(line: 828, column: 30, scope: !1050)
!2375 = !DILocalVariable(name: "w", arg: 2, scope: !1050, file: !1, line: 828, type: !344)
!2376 = !DILocation(line: 828, column: 46, scope: !1050)
!2377 = !DILocalVariable(name: "events", arg: 3, scope: !1050, file: !1, line: 828, type: !329)
!2378 = !DILocation(line: 828, column: 62, scope: !1050)
!2379 = !DILocation(line: 829, column: 3, scope: !1050)
!2380 = !DILocation(line: 829, column: 3, scope: !2381)
!2381 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 1)
!2382 = !DILocation(line: 829, column: 3, scope: !2383)
!2383 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 2)
!2384 = !DILocation(line: 829, column: 3, scope: !2385)
!2385 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 3)
!2386 = !DILocation(line: 830, column: 3, scope: !1050)
!2387 = !DILocation(line: 830, column: 3, scope: !2381)
!2388 = !DILocation(line: 830, column: 3, scope: !2383)
!2389 = !DILocation(line: 830, column: 3, scope: !2385)
!2390 = !DILocation(line: 831, column: 3, scope: !1050)
!2391 = !DILocation(line: 831, column: 3, scope: !2381)
!2392 = !DILocation(line: 831, column: 3, scope: !2383)
!2393 = !DILocation(line: 831, column: 3, scope: !2385)
!2394 = !DILocation(line: 832, column: 3, scope: !1050)
!2395 = !DILocation(line: 832, column: 3, scope: !2381)
!2396 = !DILocation(line: 832, column: 3, scope: !2383)
!2397 = !DILocation(line: 832, column: 3, scope: !2385)
!2398 = !DILocation(line: 834, column: 17, scope: !1050)
!2399 = !DILocation(line: 834, column: 3, scope: !1050)
!2400 = !DILocation(line: 834, column: 6, scope: !1050)
!2401 = !DILocation(line: 834, column: 14, scope: !1050)
!2402 = !DILocation(line: 835, column: 16, scope: !1050)
!2403 = !DILocation(line: 835, column: 22, scope: !1050)
!2404 = !DILocation(line: 835, column: 25, scope: !1050)
!2405 = !DILocation(line: 835, column: 28, scope: !1050)
!2406 = !DILocation(line: 835, column: 3, scope: !1050)
!2407 = !DILocation(line: 842, column: 7, scope: !2408)
!2408 = distinct !DILexicalBlock(scope: !1050, file: !1, line: 842, column: 7)
!2409 = !DILocation(line: 842, column: 10, scope: !2408)
!2410 = !DILocation(line: 842, column: 20, scope: !2408)
!2411 = !DILocation(line: 842, column: 23, scope: !2408)
!2412 = !DILocation(line: 842, column: 17, scope: !2408)
!2413 = !DILocation(line: 842, column: 7, scope: !1050)
!2414 = !DILocation(line: 843, column: 5, scope: !2408)
!2415 = !DILocation(line: 846, column: 7, scope: !2416)
!2416 = distinct !DILexicalBlock(scope: !1050, file: !1, line: 846, column: 7)
!2417 = !DILocation(line: 846, column: 7, scope: !1050)
!2418 = !DILocation(line: 847, column: 5, scope: !2416)
!2419 = !DILocation(line: 847, column: 5, scope: !2420)
!2420 = !DILexicalBlockFile(scope: !2421, file: !1, discriminator: 1)
!2421 = distinct !DILexicalBlock(scope: !2416, file: !1, line: 847, column: 5)
!2422 = !DILocation(line: 847, column: 5, scope: !2423)
!2423 = !DILexicalBlockFile(scope: !2421, file: !1, discriminator: 2)
!2424 = !DILocation(line: 849, column: 22, scope: !2425)
!2425 = distinct !DILexicalBlock(scope: !1050, file: !1, line: 849, column: 7)
!2426 = !DILocation(line: 849, column: 25, scope: !2425)
!2427 = !DILocation(line: 849, column: 7, scope: !2425)
!2428 = !DILocation(line: 849, column: 13, scope: !2425)
!2429 = !DILocation(line: 849, column: 29, scope: !2425)
!2430 = !DILocation(line: 849, column: 7, scope: !1050)
!2431 = !DILocation(line: 850, column: 29, scope: !2432)
!2432 = distinct !DILexicalBlock(scope: !2425, file: !1, line: 849, column: 38)
!2433 = !DILocation(line: 850, column: 20, scope: !2432)
!2434 = !DILocation(line: 850, column: 23, scope: !2432)
!2435 = !DILocation(line: 850, column: 5, scope: !2432)
!2436 = !DILocation(line: 850, column: 11, scope: !2432)
!2437 = !DILocation(line: 850, column: 27, scope: !2432)
!2438 = !DILocation(line: 851, column: 5, scope: !2432)
!2439 = !DILocation(line: 851, column: 11, scope: !2432)
!2440 = !DILocation(line: 851, column: 15, scope: !2432)
!2441 = !DILocation(line: 852, column: 3, scope: !2432)
!2442 = !DILocation(line: 853, column: 1, scope: !1050)
!2443 = !DILocalVariable(name: "loop", arg: 1, scope: !1128, file: !1, line: 776, type: !323)
!2444 = !DILocation(line: 776, column: 37, scope: !1128)
!2445 = !DILocalVariable(name: "len", arg: 2, scope: !1128, file: !1, line: 776, type: !329)
!2446 = !DILocation(line: 776, column: 56, scope: !1128)
!2447 = !DILocalVariable(name: "watchers", scope: !1128, file: !1, line: 777, type: !343)
!2448 = !DILocation(line: 777, column: 14, scope: !1128)
!2449 = !DILocalVariable(name: "fake_watcher_list", scope: !1128, file: !1, line: 778, type: !321)
!2450 = !DILocation(line: 778, column: 9, scope: !1128)
!2451 = !DILocalVariable(name: "fake_watcher_count", scope: !1128, file: !1, line: 779, type: !321)
!2452 = !DILocation(line: 779, column: 9, scope: !1128)
!2453 = !DILocalVariable(name: "nwatchers", scope: !1128, file: !1, line: 780, type: !329)
!2454 = !DILocation(line: 780, column: 16, scope: !1128)
!2455 = !DILocalVariable(name: "i", scope: !1128, file: !1, line: 781, type: !329)
!2456 = !DILocation(line: 781, column: 16, scope: !1128)
!2457 = !DILocation(line: 783, column: 7, scope: !2458)
!2458 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 783, column: 7)
!2459 = !DILocation(line: 783, column: 14, scope: !2458)
!2460 = !DILocation(line: 783, column: 20, scope: !2458)
!2461 = !DILocation(line: 783, column: 11, scope: !2458)
!2462 = !DILocation(line: 783, column: 7, scope: !1128)
!2463 = !DILocation(line: 784, column: 5, scope: !2458)
!2464 = !DILocation(line: 787, column: 7, scope: !2465)
!2465 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 787, column: 7)
!2466 = !DILocation(line: 787, column: 13, scope: !2465)
!2467 = !DILocation(line: 787, column: 22, scope: !2465)
!2468 = !DILocation(line: 787, column: 7, scope: !1128)
!2469 = !DILocation(line: 788, column: 40, scope: !2470)
!2470 = distinct !DILexicalBlock(scope: !2465, file: !1, line: 787, column: 31)
!2471 = !DILocation(line: 788, column: 46, scope: !2470)
!2472 = !DILocation(line: 788, column: 25, scope: !2470)
!2473 = !DILocation(line: 788, column: 31, scope: !2470)
!2474 = !DILocation(line: 788, column: 23, scope: !2470)
!2475 = !DILocation(line: 789, column: 41, scope: !2470)
!2476 = !DILocation(line: 789, column: 47, scope: !2470)
!2477 = !DILocation(line: 789, column: 57, scope: !2470)
!2478 = !DILocation(line: 789, column: 26, scope: !2470)
!2479 = !DILocation(line: 789, column: 32, scope: !2470)
!2480 = !DILocation(line: 789, column: 24, scope: !2470)
!2481 = !DILocation(line: 790, column: 3, scope: !2470)
!2482 = !DILocation(line: 791, column: 23, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !2465, file: !1, line: 790, column: 10)
!2484 = !DILocation(line: 792, column: 24, scope: !2483)
!2485 = !DILocation(line: 795, column: 33, scope: !1128)
!2486 = !DILocation(line: 795, column: 37, scope: !1128)
!2487 = !DILocation(line: 795, column: 15, scope: !1128)
!2488 = !DILocation(line: 795, column: 42, scope: !1128)
!2489 = !DILocation(line: 795, column: 13, scope: !1128)
!2490 = !DILocation(line: 796, column: 26, scope: !1128)
!2491 = !DILocation(line: 796, column: 32, scope: !1128)
!2492 = !DILocation(line: 797, column: 27, scope: !1128)
!2493 = !DILocation(line: 797, column: 37, scope: !1128)
!2494 = !DILocation(line: 797, column: 26, scope: !1128)
!2495 = !DILocation(line: 797, column: 42, scope: !1128)
!2496 = !DILocation(line: 796, column: 14, scope: !1128)
!2497 = !DILocation(line: 796, column: 12, scope: !1128)
!2498 = !DILocation(line: 799, column: 7, scope: !2499)
!2499 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 799, column: 7)
!2500 = !DILocation(line: 799, column: 16, scope: !2499)
!2501 = !DILocation(line: 799, column: 7, scope: !1128)
!2502 = !DILocation(line: 800, column: 5, scope: !2499)
!2503 = !DILocation(line: 801, column: 12, scope: !2504)
!2504 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 801, column: 3)
!2505 = !DILocation(line: 801, column: 18, scope: !2504)
!2506 = !DILocation(line: 801, column: 10, scope: !2504)
!2507 = !DILocation(line: 801, column: 8, scope: !2504)
!2508 = !DILocation(line: 801, column: 29, scope: !2509)
!2509 = !DILexicalBlockFile(scope: !2510, file: !1, discriminator: 1)
!2510 = distinct !DILexicalBlock(scope: !2504, file: !1, line: 801, column: 3)
!2511 = !DILocation(line: 801, column: 33, scope: !2509)
!2512 = !DILocation(line: 801, column: 31, scope: !2509)
!2513 = !DILocation(line: 801, column: 3, scope: !2509)
!2514 = !DILocation(line: 802, column: 14, scope: !2510)
!2515 = !DILocation(line: 802, column: 5, scope: !2510)
!2516 = !DILocation(line: 802, column: 17, scope: !2510)
!2517 = !DILocation(line: 801, column: 45, scope: !2518)
!2518 = !DILexicalBlockFile(scope: !2510, file: !1, discriminator: 2)
!2519 = !DILocation(line: 801, column: 3, scope: !2518)
!2520 = !DILocation(line: 803, column: 25, scope: !1128)
!2521 = !DILocation(line: 803, column: 12, scope: !1128)
!2522 = !DILocation(line: 803, column: 3, scope: !1128)
!2523 = !DILocation(line: 803, column: 23, scope: !1128)
!2524 = !DILocation(line: 804, column: 29, scope: !1128)
!2525 = !DILocation(line: 804, column: 12, scope: !1128)
!2526 = !DILocation(line: 804, column: 22, scope: !1128)
!2527 = !DILocation(line: 804, column: 3, scope: !1128)
!2528 = !DILocation(line: 804, column: 27, scope: !1128)
!2529 = !DILocation(line: 806, column: 20, scope: !1128)
!2530 = !DILocation(line: 806, column: 3, scope: !1128)
!2531 = !DILocation(line: 806, column: 9, scope: !1128)
!2532 = !DILocation(line: 806, column: 18, scope: !1128)
!2533 = !DILocation(line: 807, column: 21, scope: !1128)
!2534 = !DILocation(line: 807, column: 3, scope: !1128)
!2535 = !DILocation(line: 807, column: 9, scope: !1128)
!2536 = !DILocation(line: 807, column: 19, scope: !1128)
!2537 = !DILocation(line: 808, column: 1, scope: !1128)
!2538 = !DILocation(line: 808, column: 1, scope: !2539)
!2539 = !DILexicalBlockFile(scope: !1128, file: !1, discriminator: 1)
!2540 = !DILocalVariable(name: "loop", arg: 1, scope: !1053, file: !1, line: 856, type: !323)
!2541 = !DILocation(line: 856, column: 29, scope: !1053)
!2542 = !DILocalVariable(name: "w", arg: 2, scope: !1053, file: !1, line: 856, type: !344)
!2543 = !DILocation(line: 856, column: 45, scope: !1053)
!2544 = !DILocalVariable(name: "events", arg: 3, scope: !1053, file: !1, line: 856, type: !329)
!2545 = !DILocation(line: 856, column: 61, scope: !1053)
!2546 = !DILocation(line: 857, column: 3, scope: !1053)
!2547 = !DILocation(line: 857, column: 3, scope: !2548)
!2548 = !DILexicalBlockFile(scope: !1053, file: !1, discriminator: 1)
!2549 = !DILocation(line: 857, column: 3, scope: !2550)
!2550 = !DILexicalBlockFile(scope: !1053, file: !1, discriminator: 2)
!2551 = !DILocation(line: 857, column: 3, scope: !2552)
!2552 = !DILexicalBlockFile(scope: !1053, file: !1, discriminator: 3)
!2553 = !DILocation(line: 858, column: 3, scope: !1053)
!2554 = !DILocation(line: 858, column: 3, scope: !2548)
!2555 = !DILocation(line: 858, column: 3, scope: !2550)
!2556 = !DILocation(line: 858, column: 3, scope: !2552)
!2557 = !DILocation(line: 860, column: 7, scope: !2558)
!2558 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 860, column: 7)
!2559 = !DILocation(line: 860, column: 10, scope: !2558)
!2560 = !DILocation(line: 860, column: 13, scope: !2558)
!2561 = !DILocation(line: 860, column: 7, scope: !1053)
!2562 = !DILocation(line: 861, column: 5, scope: !2558)
!2563 = !DILocation(line: 863, column: 3, scope: !1053)
!2564 = !DILocation(line: 863, column: 3, scope: !2548)
!2565 = !DILocation(line: 863, column: 3, scope: !2550)
!2566 = !DILocation(line: 863, column: 3, scope: !2552)
!2567 = !DILocation(line: 866, column: 18, scope: !2568)
!2568 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 866, column: 7)
!2569 = !DILocation(line: 866, column: 21, scope: !2568)
!2570 = !DILocation(line: 866, column: 27, scope: !2568)
!2571 = !DILocation(line: 866, column: 33, scope: !2568)
!2572 = !DILocation(line: 866, column: 24, scope: !2568)
!2573 = !DILocation(line: 866, column: 7, scope: !1053)
!2574 = !DILocation(line: 867, column: 5, scope: !2568)
!2575 = !DILocation(line: 869, column: 18, scope: !1053)
!2576 = !DILocation(line: 869, column: 17, scope: !1053)
!2577 = !DILocation(line: 869, column: 3, scope: !1053)
!2578 = !DILocation(line: 869, column: 6, scope: !1053)
!2579 = !DILocation(line: 869, column: 14, scope: !1053)
!2580 = !DILocation(line: 871, column: 7, scope: !2581)
!2581 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 871, column: 7)
!2582 = !DILocation(line: 871, column: 10, scope: !2581)
!2583 = !DILocation(line: 871, column: 18, scope: !2581)
!2584 = !DILocation(line: 871, column: 7, scope: !1053)
!2585 = !DILocation(line: 872, column: 5, scope: !2586)
!2586 = distinct !DILexicalBlock(scope: !2581, file: !1, line: 871, column: 24)
!2587 = !DILocation(line: 872, column: 5, scope: !2588)
!2588 = !DILexicalBlockFile(scope: !2589, file: !1, discriminator: 1)
!2589 = distinct !DILexicalBlock(scope: !2586, file: !1, line: 872, column: 5)
!2590 = !DILocation(line: 873, column: 5, scope: !2586)
!2591 = !DILocation(line: 873, column: 5, scope: !2592)
!2592 = !DILexicalBlockFile(scope: !2593, file: !1, discriminator: 1)
!2593 = distinct !DILexicalBlock(scope: !2586, file: !1, line: 873, column: 5)
!2594 = !DILocation(line: 875, column: 24, scope: !2595)
!2595 = distinct !DILexicalBlock(scope: !2586, file: !1, line: 875, column: 9)
!2596 = !DILocation(line: 875, column: 27, scope: !2595)
!2597 = !DILocation(line: 875, column: 9, scope: !2595)
!2598 = !DILocation(line: 875, column: 15, scope: !2595)
!2599 = !DILocation(line: 875, column: 31, scope: !2595)
!2600 = !DILocation(line: 875, column: 9, scope: !2586)
!2601 = !DILocation(line: 876, column: 7, scope: !2602)
!2602 = distinct !DILexicalBlock(scope: !2595, file: !1, line: 875, column: 40)
!2603 = !DILocation(line: 876, column: 7, scope: !2604)
!2604 = !DILexicalBlockFile(scope: !2602, file: !1, discriminator: 1)
!2605 = !DILocation(line: 876, column: 7, scope: !2606)
!2606 = !DILexicalBlockFile(scope: !2602, file: !1, discriminator: 2)
!2607 = !DILocation(line: 876, column: 7, scope: !2608)
!2608 = !DILexicalBlockFile(scope: !2602, file: !1, discriminator: 3)
!2609 = !DILocation(line: 877, column: 7, scope: !2602)
!2610 = !DILocation(line: 877, column: 7, scope: !2604)
!2611 = !DILocation(line: 877, column: 7, scope: !2606)
!2612 = !DILocation(line: 877, column: 7, scope: !2608)
!2613 = !DILocation(line: 878, column: 22, scope: !2602)
!2614 = !DILocation(line: 878, column: 25, scope: !2602)
!2615 = !DILocation(line: 878, column: 7, scope: !2602)
!2616 = !DILocation(line: 878, column: 13, scope: !2602)
!2617 = !DILocation(line: 878, column: 29, scope: !2602)
!2618 = !DILocation(line: 879, column: 7, scope: !2602)
!2619 = !DILocation(line: 879, column: 13, scope: !2602)
!2620 = !DILocation(line: 879, column: 17, scope: !2602)
!2621 = !DILocation(line: 880, column: 7, scope: !2602)
!2622 = !DILocation(line: 880, column: 10, scope: !2602)
!2623 = !DILocation(line: 880, column: 17, scope: !2602)
!2624 = !DILocation(line: 881, column: 5, scope: !2602)
!2625 = !DILocation(line: 882, column: 3, scope: !2586)
!2626 = !DILocation(line: 883, column: 12, scope: !2627)
!2627 = distinct !DILexicalBlock(scope: !2581, file: !1, line: 883, column: 12)
!2628 = !DILocation(line: 883, column: 12, scope: !2581)
!2629 = !DILocation(line: 884, column: 5, scope: !2627)
!2630 = !DILocation(line: 884, column: 5, scope: !2631)
!2631 = !DILexicalBlockFile(scope: !2632, file: !1, discriminator: 1)
!2632 = distinct !DILexicalBlock(scope: !2627, file: !1, line: 884, column: 5)
!2633 = !DILocation(line: 884, column: 5, scope: !2634)
!2634 = !DILexicalBlockFile(scope: !2632, file: !1, discriminator: 2)
!2635 = !DILocation(line: 885, column: 1, scope: !1053)
!2636 = !DILocalVariable(name: "loop", arg: 1, scope: !1054, file: !1, line: 888, type: !323)
!2637 = !DILocation(line: 888, column: 30, scope: !1054)
!2638 = !DILocalVariable(name: "w", arg: 2, scope: !1054, file: !1, line: 888, type: !344)
!2639 = !DILocation(line: 888, column: 46, scope: !1054)
!2640 = !DILocation(line: 889, column: 15, scope: !1054)
!2641 = !DILocation(line: 889, column: 21, scope: !1054)
!2642 = !DILocation(line: 889, column: 3, scope: !1054)
!2643 = !DILocation(line: 890, column: 3, scope: !1054)
!2644 = !DILocation(line: 890, column: 3, scope: !2645)
!2645 = !DILexicalBlockFile(scope: !2646, file: !1, discriminator: 1)
!2646 = distinct !DILexicalBlock(scope: !1054, file: !1, line: 890, column: 3)
!2647 = !DILocation(line: 893, column: 30, scope: !1054)
!2648 = !DILocation(line: 893, column: 36, scope: !1054)
!2649 = !DILocation(line: 893, column: 39, scope: !1054)
!2650 = !DILocation(line: 893, column: 3, scope: !1054)
!2651 = !DILocation(line: 894, column: 1, scope: !1054)
!2652 = !DILocalVariable(name: "loop", arg: 1, scope: !1057, file: !1, line: 897, type: !323)
!2653 = !DILocation(line: 897, column: 29, scope: !1057)
!2654 = !DILocalVariable(name: "w", arg: 2, scope: !1057, file: !1, line: 897, type: !344)
!2655 = !DILocation(line: 897, column: 45, scope: !1057)
!2656 = !DILocation(line: 898, column: 7, scope: !2657)
!2657 = distinct !DILexicalBlock(scope: !1057, file: !1, line: 898, column: 7)
!2658 = !DILocation(line: 898, column: 7, scope: !1057)
!2659 = !DILocation(line: 899, column: 5, scope: !2657)
!2660 = !DILocation(line: 899, column: 5, scope: !2661)
!2661 = !DILexicalBlockFile(scope: !2662, file: !1, discriminator: 1)
!2662 = distinct !DILexicalBlock(scope: !2657, file: !1, line: 899, column: 5)
!2663 = !DILocation(line: 899, column: 5, scope: !2664)
!2664 = !DILexicalBlockFile(scope: !2662, file: !1, discriminator: 2)
!2665 = !DILocation(line: 900, column: 1, scope: !1057)
!2666 = !DILocalVariable(name: "w", arg: 1, scope: !1058, file: !1, line: 903, type: !1061)
!2667 = !DILocation(line: 903, column: 35, scope: !1058)
!2668 = !DILocalVariable(name: "events", arg: 2, scope: !1058, file: !1, line: 903, type: !329)
!2669 = !DILocation(line: 903, column: 51, scope: !1058)
!2670 = !DILocation(line: 904, column: 3, scope: !1058)
!2671 = !DILocation(line: 904, column: 3, scope: !2672)
!2672 = !DILexicalBlockFile(scope: !1058, file: !1, discriminator: 1)
!2673 = !DILocation(line: 904, column: 3, scope: !2674)
!2674 = !DILexicalBlockFile(scope: !1058, file: !1, discriminator: 2)
!2675 = !DILocation(line: 904, column: 3, scope: !2676)
!2676 = !DILexicalBlockFile(scope: !1058, file: !1, discriminator: 3)
!2677 = !DILocation(line: 905, column: 3, scope: !1058)
!2678 = !DILocation(line: 905, column: 3, scope: !2672)
!2679 = !DILocation(line: 905, column: 3, scope: !2674)
!2680 = !DILocation(line: 905, column: 3, scope: !2676)
!2681 = !DILocation(line: 906, column: 16, scope: !1058)
!2682 = !DILocation(line: 906, column: 19, scope: !1058)
!2683 = !DILocation(line: 906, column: 29, scope: !1058)
!2684 = !DILocation(line: 906, column: 27, scope: !1058)
!2685 = !DILocation(line: 906, column: 12, scope: !1058)
!2686 = !DILocation(line: 906, column: 3, scope: !1058)
!2687 = !DILocalVariable(name: "rusage", arg: 1, scope: !1063, file: !1, line: 910, type: !1066)
!2688 = !DILocation(line: 910, column: 31, scope: !1063)
!2689 = !DILocalVariable(name: "usage", scope: !1063, file: !1, line: 911, type: !2690)
!2690 = !DICompositeType(tag: DW_TAG_structure_type, name: "rusage", file: !92, line: 187, size: 1152, align: 64, elements: !2691)
!2691 = !{!2692, !2700, !2701, !2707, !2712, !2717, !2722, !2727, !2732, !2737, !2742, !2747, !2752, !2757, !2762, !2767}
!2692 = !DIDerivedType(tag: DW_TAG_member, name: "ru_utime", scope: !2690, file: !92, line: 190, baseType: !2693, size: 128, align: 64)
!2693 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !2694, line: 30, size: 128, align: 64, elements: !2695)
!2694 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2695 = !{!2696, !2698}
!2696 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !2693, file: !2694, line: 32, baseType: !2697, size: 64, align: 64)
!2697 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !623, line: 139, baseType: !394)
!2698 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !2693, file: !2694, line: 33, baseType: !2699, size: 64, align: 64, offset: 64)
!2699 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !623, line: 141, baseType: !394)
!2700 = !DIDerivedType(tag: DW_TAG_member, name: "ru_stime", scope: !2690, file: !92, line: 192, baseType: !2693, size: 128, align: 64, offset: 128)
!2701 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 194, baseType: !2702, size: 64, align: 64, offset: 256)
!2702 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 194, size: 64, align: 64, elements: !2703)
!2703 = !{!2704, !2705}
!2704 = !DIDerivedType(tag: DW_TAG_member, name: "ru_maxrss", scope: !2702, file: !92, line: 196, baseType: !394, size: 64, align: 64)
!2705 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_maxrss_word", scope: !2702, file: !92, line: 197, baseType: !2706, size: 64, align: 64)
!2706 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !623, line: 175, baseType: !394)
!2707 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 202, baseType: !2708, size: 64, align: 64, offset: 320)
!2708 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 202, size: 64, align: 64, elements: !2709)
!2709 = !{!2710, !2711}
!2710 = !DIDerivedType(tag: DW_TAG_member, name: "ru_ixrss", scope: !2708, file: !92, line: 204, baseType: !394, size: 64, align: 64)
!2711 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_ixrss_word", scope: !2708, file: !92, line: 205, baseType: !2706, size: 64, align: 64)
!2712 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 208, baseType: !2713, size: 64, align: 64, offset: 384)
!2713 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 208, size: 64, align: 64, elements: !2714)
!2714 = !{!2715, !2716}
!2715 = !DIDerivedType(tag: DW_TAG_member, name: "ru_idrss", scope: !2713, file: !92, line: 210, baseType: !394, size: 64, align: 64)
!2716 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_idrss_word", scope: !2713, file: !92, line: 211, baseType: !2706, size: 64, align: 64)
!2717 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 214, baseType: !2718, size: 64, align: 64, offset: 448)
!2718 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 214, size: 64, align: 64, elements: !2719)
!2719 = !{!2720, !2721}
!2720 = !DIDerivedType(tag: DW_TAG_member, name: "ru_isrss", scope: !2718, file: !92, line: 216, baseType: !394, size: 64, align: 64)
!2721 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_isrss_word", scope: !2718, file: !92, line: 217, baseType: !2706, size: 64, align: 64)
!2722 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 221, baseType: !2723, size: 64, align: 64, offset: 512)
!2723 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 221, size: 64, align: 64, elements: !2724)
!2724 = !{!2725, !2726}
!2725 = !DIDerivedType(tag: DW_TAG_member, name: "ru_minflt", scope: !2723, file: !92, line: 223, baseType: !394, size: 64, align: 64)
!2726 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_minflt_word", scope: !2723, file: !92, line: 224, baseType: !2706, size: 64, align: 64)
!2727 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 227, baseType: !2728, size: 64, align: 64, offset: 576)
!2728 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 227, size: 64, align: 64, elements: !2729)
!2729 = !{!2730, !2731}
!2730 = !DIDerivedType(tag: DW_TAG_member, name: "ru_majflt", scope: !2728, file: !92, line: 229, baseType: !394, size: 64, align: 64)
!2731 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_majflt_word", scope: !2728, file: !92, line: 230, baseType: !2706, size: 64, align: 64)
!2732 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 233, baseType: !2733, size: 64, align: 64, offset: 640)
!2733 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 233, size: 64, align: 64, elements: !2734)
!2734 = !{!2735, !2736}
!2735 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nswap", scope: !2733, file: !92, line: 235, baseType: !394, size: 64, align: 64)
!2736 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_nswap_word", scope: !2733, file: !92, line: 236, baseType: !2706, size: 64, align: 64)
!2737 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 240, baseType: !2738, size: 64, align: 64, offset: 704)
!2738 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 240, size: 64, align: 64, elements: !2739)
!2739 = !{!2740, !2741}
!2740 = !DIDerivedType(tag: DW_TAG_member, name: "ru_inblock", scope: !2738, file: !92, line: 242, baseType: !394, size: 64, align: 64)
!2741 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_inblock_word", scope: !2738, file: !92, line: 243, baseType: !2706, size: 64, align: 64)
!2742 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 246, baseType: !2743, size: 64, align: 64, offset: 768)
!2743 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 246, size: 64, align: 64, elements: !2744)
!2744 = !{!2745, !2746}
!2745 = !DIDerivedType(tag: DW_TAG_member, name: "ru_oublock", scope: !2743, file: !92, line: 248, baseType: !394, size: 64, align: 64)
!2746 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_oublock_word", scope: !2743, file: !92, line: 249, baseType: !2706, size: 64, align: 64)
!2747 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 252, baseType: !2748, size: 64, align: 64, offset: 832)
!2748 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 252, size: 64, align: 64, elements: !2749)
!2749 = !{!2750, !2751}
!2750 = !DIDerivedType(tag: DW_TAG_member, name: "ru_msgsnd", scope: !2748, file: !92, line: 254, baseType: !394, size: 64, align: 64)
!2751 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_msgsnd_word", scope: !2748, file: !92, line: 255, baseType: !2706, size: 64, align: 64)
!2752 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 258, baseType: !2753, size: 64, align: 64, offset: 896)
!2753 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 258, size: 64, align: 64, elements: !2754)
!2754 = !{!2755, !2756}
!2755 = !DIDerivedType(tag: DW_TAG_member, name: "ru_msgrcv", scope: !2753, file: !92, line: 260, baseType: !394, size: 64, align: 64)
!2756 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_msgrcv_word", scope: !2753, file: !92, line: 261, baseType: !2706, size: 64, align: 64)
!2757 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 264, baseType: !2758, size: 64, align: 64, offset: 960)
!2758 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 264, size: 64, align: 64, elements: !2759)
!2759 = !{!2760, !2761}
!2760 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nsignals", scope: !2758, file: !92, line: 266, baseType: !394, size: 64, align: 64)
!2761 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_nsignals_word", scope: !2758, file: !92, line: 267, baseType: !2706, size: 64, align: 64)
!2762 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 272, baseType: !2763, size: 64, align: 64, offset: 1024)
!2763 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 272, size: 64, align: 64, elements: !2764)
!2764 = !{!2765, !2766}
!2765 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nvcsw", scope: !2763, file: !92, line: 274, baseType: !394, size: 64, align: 64)
!2766 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_nvcsw_word", scope: !2763, file: !92, line: 275, baseType: !2706, size: 64, align: 64)
!2767 = !DIDerivedType(tag: DW_TAG_member, scope: !2690, file: !92, line: 279, baseType: !2768, size: 64, align: 64, offset: 1088)
!2768 = !DICompositeType(tag: DW_TAG_union_type, scope: !2690, file: !92, line: 279, size: 64, align: 64, elements: !2769)
!2769 = !{!2770, !2771}
!2770 = !DIDerivedType(tag: DW_TAG_member, name: "ru_nivcsw", scope: !2768, file: !92, line: 281, baseType: !394, size: 64, align: 64)
!2771 = !DIDerivedType(tag: DW_TAG_member, name: "__ru_nivcsw_word", scope: !2768, file: !92, line: 282, baseType: !2706, size: 64, align: 64)
!2772 = !DILocation(line: 911, column: 17, scope: !1063)
!2773 = !DILocation(line: 913, column: 7, scope: !2774)
!2774 = distinct !DILexicalBlock(scope: !1063, file: !1, line: 913, column: 7)
!2775 = !DILocation(line: 913, column: 7, scope: !1063)
!2776 = !DILocation(line: 914, column: 13, scope: !2774)
!2777 = !DILocation(line: 914, column: 12, scope: !2774)
!2778 = !DILocation(line: 914, column: 5, scope: !2774)
!2779 = !DILocation(line: 916, column: 35, scope: !1063)
!2780 = !DILocation(line: 916, column: 44, scope: !1063)
!2781 = !DILocation(line: 916, column: 3, scope: !1063)
!2782 = !DILocation(line: 916, column: 11, scope: !1063)
!2783 = !DILocation(line: 916, column: 20, scope: !1063)
!2784 = !DILocation(line: 916, column: 27, scope: !1063)
!2785 = !DILocation(line: 917, column: 36, scope: !1063)
!2786 = !DILocation(line: 917, column: 45, scope: !1063)
!2787 = !DILocation(line: 917, column: 3, scope: !1063)
!2788 = !DILocation(line: 917, column: 11, scope: !1063)
!2789 = !DILocation(line: 917, column: 20, scope: !1063)
!2790 = !DILocation(line: 917, column: 28, scope: !1063)
!2791 = !DILocation(line: 919, column: 35, scope: !1063)
!2792 = !DILocation(line: 919, column: 44, scope: !1063)
!2793 = !DILocation(line: 919, column: 3, scope: !1063)
!2794 = !DILocation(line: 919, column: 11, scope: !1063)
!2795 = !DILocation(line: 919, column: 20, scope: !1063)
!2796 = !DILocation(line: 919, column: 27, scope: !1063)
!2797 = !DILocation(line: 920, column: 36, scope: !1063)
!2798 = !DILocation(line: 920, column: 45, scope: !1063)
!2799 = !DILocation(line: 920, column: 3, scope: !1063)
!2800 = !DILocation(line: 920, column: 11, scope: !1063)
!2801 = !DILocation(line: 920, column: 20, scope: !1063)
!2802 = !DILocation(line: 920, column: 28, scope: !1063)
!2803 = !DILocation(line: 923, column: 29, scope: !1063)
!2804 = !DILocation(line: 923, column: 3, scope: !1063)
!2805 = !DILocation(line: 923, column: 11, scope: !1063)
!2806 = !DILocation(line: 923, column: 21, scope: !1063)
!2807 = !DILocation(line: 924, column: 28, scope: !1063)
!2808 = !DILocation(line: 924, column: 3, scope: !1063)
!2809 = !DILocation(line: 924, column: 11, scope: !1063)
!2810 = !DILocation(line: 924, column: 20, scope: !1063)
!2811 = !DILocation(line: 925, column: 28, scope: !1063)
!2812 = !DILocation(line: 925, column: 3, scope: !1063)
!2813 = !DILocation(line: 925, column: 11, scope: !1063)
!2814 = !DILocation(line: 925, column: 20, scope: !1063)
!2815 = !DILocation(line: 926, column: 28, scope: !1063)
!2816 = !DILocation(line: 926, column: 3, scope: !1063)
!2817 = !DILocation(line: 926, column: 11, scope: !1063)
!2818 = !DILocation(line: 926, column: 20, scope: !1063)
!2819 = !DILocation(line: 927, column: 29, scope: !1063)
!2820 = !DILocation(line: 927, column: 3, scope: !1063)
!2821 = !DILocation(line: 927, column: 11, scope: !1063)
!2822 = !DILocation(line: 927, column: 21, scope: !1063)
!2823 = !DILocation(line: 928, column: 29, scope: !1063)
!2824 = !DILocation(line: 928, column: 3, scope: !1063)
!2825 = !DILocation(line: 928, column: 11, scope: !1063)
!2826 = !DILocation(line: 928, column: 21, scope: !1063)
!2827 = !DILocation(line: 929, column: 28, scope: !1063)
!2828 = !DILocation(line: 929, column: 3, scope: !1063)
!2829 = !DILocation(line: 929, column: 11, scope: !1063)
!2830 = !DILocation(line: 929, column: 20, scope: !1063)
!2831 = !DILocation(line: 930, column: 30, scope: !1063)
!2832 = !DILocation(line: 930, column: 3, scope: !1063)
!2833 = !DILocation(line: 930, column: 11, scope: !1063)
!2834 = !DILocation(line: 930, column: 22, scope: !1063)
!2835 = !DILocation(line: 931, column: 30, scope: !1063)
!2836 = !DILocation(line: 931, column: 3, scope: !1063)
!2837 = !DILocation(line: 931, column: 11, scope: !1063)
!2838 = !DILocation(line: 931, column: 22, scope: !1063)
!2839 = !DILocation(line: 932, column: 29, scope: !1063)
!2840 = !DILocation(line: 932, column: 3, scope: !1063)
!2841 = !DILocation(line: 932, column: 11, scope: !1063)
!2842 = !DILocation(line: 932, column: 21, scope: !1063)
!2843 = !DILocation(line: 933, column: 29, scope: !1063)
!2844 = !DILocation(line: 933, column: 3, scope: !1063)
!2845 = !DILocation(line: 933, column: 11, scope: !1063)
!2846 = !DILocation(line: 933, column: 21, scope: !1063)
!2847 = !DILocation(line: 934, column: 31, scope: !1063)
!2848 = !DILocation(line: 934, column: 3, scope: !1063)
!2849 = !DILocation(line: 934, column: 11, scope: !1063)
!2850 = !DILocation(line: 934, column: 23, scope: !1063)
!2851 = !DILocation(line: 935, column: 28, scope: !1063)
!2852 = !DILocation(line: 935, column: 3, scope: !1063)
!2853 = !DILocation(line: 935, column: 11, scope: !1063)
!2854 = !DILocation(line: 935, column: 20, scope: !1063)
!2855 = !DILocation(line: 936, column: 29, scope: !1063)
!2856 = !DILocation(line: 936, column: 3, scope: !1063)
!2857 = !DILocation(line: 936, column: 11, scope: !1063)
!2858 = !DILocation(line: 936, column: 21, scope: !1063)
!2859 = !DILocation(line: 939, column: 3, scope: !1063)
!2860 = !DILocation(line: 940, column: 1, scope: !1063)
!2861 = !DILocalVariable(name: "oldfd", arg: 1, scope: !1094, file: !1, line: 977, type: !339)
!2862 = !DILocation(line: 977, column: 26, scope: !1094)
!2863 = !DILocalVariable(name: "newfd", arg: 2, scope: !1094, file: !1, line: 977, type: !339)
!2864 = !DILocation(line: 977, column: 37, scope: !1094)
!2865 = !DILocalVariable(name: "r", scope: !1094, file: !1, line: 978, type: !339)
!2866 = !DILocation(line: 978, column: 7, scope: !1094)
!2867 = !DILocation(line: 993, column: 8, scope: !2868)
!2868 = distinct !DILexicalBlock(scope: !1094, file: !1, line: 993, column: 7)
!2869 = !DILocation(line: 993, column: 7, scope: !1094)
!2870 = !DILocation(line: 994, column: 5, scope: !2871)
!2871 = distinct !DILexicalBlock(scope: !2868, file: !1, line: 993, column: 17)
!2872 = !DILocation(line: 995, column: 20, scope: !2871)
!2873 = !DILocation(line: 995, column: 27, scope: !2871)
!2874 = !DILocation(line: 995, column: 11, scope: !2871)
!2875 = !DILocation(line: 995, column: 9, scope: !2871)
!2876 = !DILocation(line: 995, column: 7, scope: !2871)
!2877 = !DILocation(line: 996, column: 12, scope: !2871)
!2878 = !DILocation(line: 996, column: 14, scope: !2871)
!2879 = !DILocation(line: 996, column: 20, scope: !2871)
!2880 = !DILocation(line: 996, column: 23, scope: !2881)
!2881 = !DILexicalBlockFile(scope: !2871, file: !1, discriminator: 1)
!2882 = !DILocation(line: 996, column: 29, scope: !2881)
!2883 = !DILocation(line: 995, column: 7, scope: !2881)
!2884 = !DILocation(line: 997, column: 9, scope: !2885)
!2885 = distinct !DILexicalBlock(scope: !2871, file: !1, line: 997, column: 9)
!2886 = !DILocation(line: 997, column: 11, scope: !2885)
!2887 = !DILocation(line: 997, column: 9, scope: !2871)
!2888 = !DILocation(line: 998, column: 14, scope: !2885)
!2889 = !DILocation(line: 998, column: 7, scope: !2885)
!2890 = !DILocation(line: 999, column: 9, scope: !2891)
!2891 = distinct !DILexicalBlock(scope: !2871, file: !1, line: 999, column: 9)
!2892 = !DILocation(line: 999, column: 15, scope: !2891)
!2893 = !DILocation(line: 999, column: 9, scope: !2871)
!2894 = !DILocation(line: 1000, column: 15, scope: !2891)
!2895 = !DILocation(line: 1000, column: 14, scope: !2891)
!2896 = !DILocation(line: 1000, column: 7, scope: !2891)
!2897 = !DILocation(line: 1002, column: 13, scope: !2871)
!2898 = !DILocation(line: 1003, column: 3, scope: !2871)
!2899 = !DILocalVariable(name: "err", scope: !2900, file: !1, line: 1006, type: !339)
!2900 = distinct !DILexicalBlock(scope: !1094, file: !1, line: 1005, column: 3)
!2901 = !DILocation(line: 1006, column: 9, scope: !2900)
!2902 = !DILocation(line: 1007, column: 5, scope: !2900)
!2903 = !DILocation(line: 1008, column: 16, scope: !2900)
!2904 = !DILocation(line: 1008, column: 23, scope: !2900)
!2905 = !DILocation(line: 1008, column: 11, scope: !2900)
!2906 = !DILocation(line: 1008, column: 9, scope: !2900)
!2907 = !DILocation(line: 1008, column: 7, scope: !2900)
!2908 = !DILocation(line: 1010, column: 12, scope: !2900)
!2909 = !DILocation(line: 1010, column: 14, scope: !2900)
!2910 = !DILocation(line: 1010, column: 20, scope: !2900)
!2911 = !DILocation(line: 1010, column: 23, scope: !2912)
!2912 = !DILexicalBlockFile(scope: !2900, file: !1, discriminator: 1)
!2913 = !DILocation(line: 1010, column: 29, scope: !2912)
!2914 = !DILocation(line: 1008, column: 7, scope: !2912)
!2915 = !DILocation(line: 1015, column: 9, scope: !2916)
!2916 = distinct !DILexicalBlock(scope: !2900, file: !1, line: 1015, column: 9)
!2917 = !DILocation(line: 1015, column: 11, scope: !2916)
!2918 = !DILocation(line: 1015, column: 9, scope: !2900)
!2919 = !DILocation(line: 1016, column: 15, scope: !2916)
!2920 = !DILocation(line: 1016, column: 14, scope: !2916)
!2921 = !DILocation(line: 1016, column: 7, scope: !2916)
!2922 = !DILocation(line: 1018, column: 23, scope: !2900)
!2923 = !DILocation(line: 1018, column: 11, scope: !2900)
!2924 = !DILocation(line: 1018, column: 9, scope: !2900)
!2925 = !DILocation(line: 1019, column: 9, scope: !2926)
!2926 = distinct !DILexicalBlock(scope: !2900, file: !1, line: 1019, column: 9)
!2927 = !DILocation(line: 1019, column: 9, scope: !2900)
!2928 = !DILocation(line: 1020, column: 17, scope: !2929)
!2929 = distinct !DILexicalBlock(scope: !2926, file: !1, line: 1019, column: 14)
!2930 = !DILocation(line: 1020, column: 7, scope: !2929)
!2931 = !DILocation(line: 1021, column: 14, scope: !2929)
!2932 = !DILocation(line: 1021, column: 7, scope: !2929)
!2933 = !DILocation(line: 1024, column: 12, scope: !2900)
!2934 = !DILocation(line: 1024, column: 5, scope: !2900)
!2935 = !DILocation(line: 1026, column: 1, scope: !1094)
!2936 = !DILocalVariable(name: "buffer", arg: 1, scope: !1095, file: !1, line: 1029, type: !551)
!2937 = !DILocation(line: 1029, column: 25, scope: !1095)
!2938 = !DILocalVariable(name: "size", arg: 2, scope: !1095, file: !1, line: 1029, type: !1037)
!2939 = !DILocation(line: 1029, column: 41, scope: !1095)
!2940 = !DILocalVariable(name: "pwd", scope: !1095, file: !1, line: 1030, type: !1101)
!2941 = !DILocation(line: 1030, column: 15, scope: !1095)
!2942 = !DILocalVariable(name: "buf", scope: !1095, file: !1, line: 1031, type: !551)
!2943 = !DILocation(line: 1031, column: 9, scope: !1095)
!2944 = !DILocalVariable(name: "len", scope: !1095, file: !1, line: 1032, type: !539)
!2945 = !DILocation(line: 1032, column: 10, scope: !1095)
!2946 = !DILocalVariable(name: "r", scope: !1095, file: !1, line: 1033, type: !339)
!2947 = !DILocation(line: 1033, column: 7, scope: !1095)
!2948 = !DILocation(line: 1035, column: 7, scope: !2949)
!2949 = distinct !DILexicalBlock(scope: !1095, file: !1, line: 1035, column: 7)
!2950 = !DILocation(line: 1035, column: 14, scope: !2949)
!2951 = !DILocation(line: 1035, column: 22, scope: !2949)
!2952 = !DILocation(line: 1035, column: 25, scope: !2953)
!2953 = !DILexicalBlockFile(scope: !2949, file: !1, discriminator: 1)
!2954 = !DILocation(line: 1035, column: 30, scope: !2953)
!2955 = !DILocation(line: 1035, column: 38, scope: !2953)
!2956 = !DILocation(line: 1035, column: 42, scope: !2957)
!2957 = !DILexicalBlockFile(scope: !2949, file: !1, discriminator: 2)
!2958 = !DILocation(line: 1035, column: 41, scope: !2957)
!2959 = !DILocation(line: 1035, column: 47, scope: !2957)
!2960 = !DILocation(line: 1035, column: 7, scope: !2957)
!2961 = !DILocation(line: 1036, column: 5, scope: !2949)
!2962 = !DILocation(line: 1039, column: 9, scope: !1095)
!2963 = !DILocation(line: 1039, column: 7, scope: !1095)
!2964 = !DILocation(line: 1041, column: 7, scope: !2965)
!2965 = distinct !DILexicalBlock(scope: !1095, file: !1, line: 1041, column: 7)
!2966 = !DILocation(line: 1041, column: 11, scope: !2965)
!2967 = !DILocation(line: 1041, column: 7, scope: !1095)
!2968 = !DILocation(line: 1042, column: 18, scope: !2969)
!2969 = distinct !DILexicalBlock(scope: !2965, file: !1, line: 1041, column: 20)
!2970 = !DILocation(line: 1042, column: 11, scope: !2969)
!2971 = !DILocation(line: 1042, column: 9, scope: !2969)
!2972 = !DILocation(line: 1044, column: 9, scope: !2973)
!2973 = distinct !DILexicalBlock(scope: !2969, file: !1, line: 1044, column: 9)
!2974 = !DILocation(line: 1044, column: 17, scope: !2973)
!2975 = !DILocation(line: 1044, column: 16, scope: !2973)
!2976 = !DILocation(line: 1044, column: 13, scope: !2973)
!2977 = !DILocation(line: 1044, column: 9, scope: !2969)
!2978 = !DILocation(line: 1045, column: 15, scope: !2979)
!2979 = distinct !DILexicalBlock(scope: !2973, file: !1, line: 1044, column: 23)
!2980 = !DILocation(line: 1045, column: 19, scope: !2979)
!2981 = !DILocation(line: 1045, column: 8, scope: !2979)
!2982 = !DILocation(line: 1045, column: 13, scope: !2979)
!2983 = !DILocation(line: 1046, column: 7, scope: !2979)
!2984 = !DILocation(line: 1049, column: 12, scope: !2969)
!2985 = !DILocation(line: 1049, column: 20, scope: !2969)
!2986 = !DILocation(line: 1049, column: 25, scope: !2969)
!2987 = !DILocation(line: 1049, column: 29, scope: !2969)
!2988 = !DILocation(line: 1049, column: 5, scope: !2969)
!2989 = !DILocation(line: 1050, column: 13, scope: !2969)
!2990 = !DILocation(line: 1050, column: 6, scope: !2969)
!2991 = !DILocation(line: 1050, column: 11, scope: !2969)
!2992 = !DILocation(line: 1052, column: 5, scope: !2969)
!2993 = !DILocation(line: 1056, column: 7, scope: !1095)
!2994 = !DILocation(line: 1056, column: 5, scope: !1095)
!2995 = !DILocation(line: 1058, column: 7, scope: !2996)
!2996 = distinct !DILexicalBlock(scope: !1095, file: !1, line: 1058, column: 7)
!2997 = !DILocation(line: 1058, column: 9, scope: !2996)
!2998 = !DILocation(line: 1058, column: 7, scope: !1095)
!2999 = !DILocation(line: 1059, column: 12, scope: !3000)
!3000 = distinct !DILexicalBlock(scope: !2996, file: !1, line: 1058, column: 15)
!3001 = !DILocation(line: 1059, column: 5, scope: !3000)
!3002 = !DILocation(line: 1062, column: 20, scope: !1095)
!3003 = !DILocation(line: 1062, column: 9, scope: !1095)
!3004 = !DILocation(line: 1062, column: 7, scope: !1095)
!3005 = !DILocation(line: 1064, column: 7, scope: !3006)
!3006 = distinct !DILexicalBlock(scope: !1095, file: !1, line: 1064, column: 7)
!3007 = !DILocation(line: 1064, column: 15, scope: !3006)
!3008 = !DILocation(line: 1064, column: 14, scope: !3006)
!3009 = !DILocation(line: 1064, column: 11, scope: !3006)
!3010 = !DILocation(line: 1064, column: 7, scope: !1095)
!3011 = !DILocation(line: 1065, column: 13, scope: !3012)
!3012 = distinct !DILexicalBlock(scope: !3006, file: !1, line: 1064, column: 21)
!3013 = !DILocation(line: 1065, column: 17, scope: !3012)
!3014 = !DILocation(line: 1065, column: 6, scope: !3012)
!3015 = !DILocation(line: 1065, column: 11, scope: !3012)
!3016 = !DILocation(line: 1066, column: 5, scope: !3012)
!3017 = !DILocation(line: 1067, column: 5, scope: !3012)
!3018 = !DILocation(line: 1070, column: 10, scope: !1095)
!3019 = !DILocation(line: 1070, column: 22, scope: !1095)
!3020 = !DILocation(line: 1070, column: 31, scope: !1095)
!3021 = !DILocation(line: 1070, column: 35, scope: !1095)
!3022 = !DILocation(line: 1070, column: 3, scope: !1095)
!3023 = !DILocation(line: 1071, column: 11, scope: !1095)
!3024 = !DILocation(line: 1071, column: 4, scope: !1095)
!3025 = !DILocation(line: 1071, column: 9, scope: !1095)
!3026 = !DILocation(line: 1072, column: 3, scope: !1095)
!3027 = !DILocation(line: 1074, column: 3, scope: !1095)
!3028 = !DILocation(line: 1075, column: 1, scope: !1095)
!3029 = !DILocalVariable(name: "pwd", arg: 1, scope: !1097, file: !1, line: 1129, type: !1100)
!3030 = !DILocation(line: 1129, column: 33, scope: !1097)
!3031 = !DILocalVariable(name: "pw", scope: !1097, file: !1, line: 1130, type: !3032)
!3032 = !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !3033, line: 49, size: 384, align: 64, elements: !3034)
!3033 = !DIFile(filename: "/usr/include/pwd.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!3034 = !{!3035, !3036, !3037, !3039, !3041, !3042, !3043}
!3035 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !3032, file: !3033, line: 51, baseType: !551, size: 64, align: 64)
!3036 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !3032, file: !3033, line: 52, baseType: !551, size: 64, align: 64, offset: 64)
!3037 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !3032, file: !3033, line: 53, baseType: !3038, size: 32, align: 32, offset: 128)
!3038 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !623, line: 125, baseType: !329)
!3039 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !3032, file: !3033, line: 54, baseType: !3040, size: 32, align: 32, offset: 160)
!3040 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !623, line: 126, baseType: !329)
!3041 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !3032, file: !3033, line: 55, baseType: !551, size: 64, align: 64, offset: 192)
!3042 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !3032, file: !3033, line: 56, baseType: !551, size: 64, align: 64, offset: 256)
!3043 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !3032, file: !3033, line: 57, baseType: !551, size: 64, align: 64, offset: 320)
!3044 = !DILocation(line: 1130, column: 17, scope: !1097)
!3045 = !DILocalVariable(name: "result", scope: !1097, file: !1, line: 1131, type: !3046)
!3046 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !3032, size: 64, align: 64)
!3047 = !DILocation(line: 1131, column: 18, scope: !1097)
!3048 = !DILocalVariable(name: "buf", scope: !1097, file: !1, line: 1132, type: !551)
!3049 = !DILocation(line: 1132, column: 9, scope: !1097)
!3050 = !DILocalVariable(name: "uid", scope: !1097, file: !1, line: 1133, type: !3051)
!3051 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !3052, line: 80, baseType: !3038)
!3052 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!3053 = !DILocation(line: 1133, column: 9, scope: !1097)
!3054 = !DILocalVariable(name: "bufsize", scope: !1097, file: !1, line: 1134, type: !539)
!3055 = !DILocation(line: 1134, column: 10, scope: !1097)
!3056 = !DILocalVariable(name: "name_size", scope: !1097, file: !1, line: 1135, type: !539)
!3057 = !DILocation(line: 1135, column: 10, scope: !1097)
!3058 = !DILocalVariable(name: "homedir_size", scope: !1097, file: !1, line: 1136, type: !539)
!3059 = !DILocation(line: 1136, column: 10, scope: !1097)
!3060 = !DILocalVariable(name: "shell_size", scope: !1097, file: !1, line: 1137, type: !539)
!3061 = !DILocation(line: 1137, column: 10, scope: !1097)
!3062 = !DILocalVariable(name: "initsize", scope: !1097, file: !1, line: 1138, type: !394)
!3063 = !DILocation(line: 1138, column: 8, scope: !1097)
!3064 = !DILocalVariable(name: "r", scope: !1097, file: !1, line: 1139, type: !339)
!3065 = !DILocation(line: 1139, column: 7, scope: !1097)
!3066 = !DILocation(line: 1148, column: 7, scope: !3067)
!3067 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 1148, column: 7)
!3068 = !DILocation(line: 1148, column: 11, scope: !3067)
!3069 = !DILocation(line: 1148, column: 7, scope: !1097)
!3070 = !DILocation(line: 1149, column: 5, scope: !3067)
!3071 = !DILocation(line: 1151, column: 14, scope: !1097)
!3072 = !DILocation(line: 1151, column: 12, scope: !1097)
!3073 = !DILocation(line: 1153, column: 7, scope: !3074)
!3074 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 1153, column: 7)
!3075 = !DILocation(line: 1153, column: 16, scope: !3074)
!3076 = !DILocation(line: 1153, column: 7, scope: !1097)
!3077 = !DILocation(line: 1154, column: 13, scope: !3074)
!3078 = !DILocation(line: 1154, column: 5, scope: !3074)
!3079 = !DILocation(line: 1156, column: 24, scope: !3074)
!3080 = !DILocation(line: 1156, column: 13, scope: !3074)
!3081 = !DILocation(line: 1158, column: 9, scope: !1097)
!3082 = !DILocation(line: 1158, column: 7, scope: !1097)
!3083 = !DILocation(line: 1159, column: 7, scope: !1097)
!3084 = !DILocation(line: 1161, column: 3, scope: !1097)
!3085 = !DILocation(line: 1162, column: 14, scope: !3086)
!3086 = distinct !DILexicalBlock(scope: !3087, file: !1, line: 1161, column: 12)
!3087 = distinct !DILexicalBlock(scope: !3088, file: !1, line: 1161, column: 3)
!3088 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 1161, column: 3)
!3089 = !DILocation(line: 1162, column: 5, scope: !3086)
!3090 = !DILocation(line: 1163, column: 22, scope: !3086)
!3091 = !DILocation(line: 1163, column: 11, scope: !3086)
!3092 = !DILocation(line: 1163, column: 9, scope: !3086)
!3093 = !DILocation(line: 1165, column: 9, scope: !3094)
!3094 = distinct !DILexicalBlock(scope: !3086, file: !1, line: 1165, column: 9)
!3095 = !DILocation(line: 1165, column: 13, scope: !3094)
!3096 = !DILocation(line: 1165, column: 9, scope: !3086)
!3097 = !DILocation(line: 1166, column: 7, scope: !3094)
!3098 = !DILocation(line: 1168, column: 20, scope: !3086)
!3099 = !DILocation(line: 1168, column: 30, scope: !3086)
!3100 = !DILocation(line: 1168, column: 35, scope: !3086)
!3101 = !DILocation(line: 1168, column: 9, scope: !3086)
!3102 = !DILocation(line: 1168, column: 7, scope: !3086)
!3103 = !DILocation(line: 1170, column: 9, scope: !3104)
!3104 = distinct !DILexicalBlock(scope: !3086, file: !1, line: 1170, column: 9)
!3105 = !DILocation(line: 1170, column: 11, scope: !3104)
!3106 = !DILocation(line: 1170, column: 9, scope: !3086)
!3107 = !DILocation(line: 1171, column: 7, scope: !3104)
!3108 = !DILocation(line: 1173, column: 13, scope: !3086)
!3109 = !DILocation(line: 1161, column: 3, scope: !3110)
!3110 = !DILexicalBlockFile(scope: !3087, file: !1, discriminator: 1)
!3111 = !DILocation(line: 1176, column: 7, scope: !3112)
!3112 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 1176, column: 7)
!3113 = !DILocation(line: 1176, column: 9, scope: !3112)
!3114 = !DILocation(line: 1176, column: 7, scope: !1097)
!3115 = !DILocation(line: 1177, column: 14, scope: !3116)
!3116 = distinct !DILexicalBlock(scope: !3112, file: !1, line: 1176, column: 15)
!3117 = !DILocation(line: 1177, column: 5, scope: !3116)
!3118 = !DILocation(line: 1178, column: 13, scope: !3116)
!3119 = !DILocation(line: 1178, column: 12, scope: !3116)
!3120 = !DILocation(line: 1178, column: 5, scope: !3116)
!3121 = !DILocation(line: 1181, column: 7, scope: !3122)
!3122 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 1181, column: 7)
!3123 = !DILocation(line: 1181, column: 14, scope: !3122)
!3124 = !DILocation(line: 1181, column: 7, scope: !1097)
!3125 = !DILocation(line: 1182, column: 14, scope: !3126)
!3126 = distinct !DILexicalBlock(scope: !3122, file: !1, line: 1181, column: 23)
!3127 = !DILocation(line: 1182, column: 5, scope: !3126)
!3128 = !DILocation(line: 1183, column: 5, scope: !3126)
!3129 = !DILocation(line: 1187, column: 25, scope: !1097)
!3130 = !DILocation(line: 1187, column: 15, scope: !1097)
!3131 = !DILocation(line: 1187, column: 34, scope: !1097)
!3132 = !DILocation(line: 1187, column: 13, scope: !1097)
!3133 = !DILocation(line: 1188, column: 28, scope: !1097)
!3134 = !DILocation(line: 1188, column: 18, scope: !1097)
!3135 = !DILocation(line: 1188, column: 36, scope: !1097)
!3136 = !DILocation(line: 1188, column: 16, scope: !1097)
!3137 = !DILocation(line: 1189, column: 26, scope: !1097)
!3138 = !DILocation(line: 1189, column: 16, scope: !1097)
!3139 = !DILocation(line: 1189, column: 36, scope: !1097)
!3140 = !DILocation(line: 1189, column: 14, scope: !1097)
!3141 = !DILocation(line: 1190, column: 30, scope: !1097)
!3142 = !DILocation(line: 1190, column: 42, scope: !1097)
!3143 = !DILocation(line: 1190, column: 40, scope: !1097)
!3144 = !DILocation(line: 1190, column: 57, scope: !1097)
!3145 = !DILocation(line: 1190, column: 55, scope: !1097)
!3146 = !DILocation(line: 1190, column: 19, scope: !1097)
!3147 = !DILocation(line: 1190, column: 3, scope: !1097)
!3148 = !DILocation(line: 1190, column: 8, scope: !1097)
!3149 = !DILocation(line: 1190, column: 17, scope: !1097)
!3150 = !DILocation(line: 1192, column: 7, scope: !3151)
!3151 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 1192, column: 7)
!3152 = !DILocation(line: 1192, column: 12, scope: !3151)
!3153 = !DILocation(line: 1192, column: 21, scope: !3151)
!3154 = !DILocation(line: 1192, column: 7, scope: !1097)
!3155 = !DILocation(line: 1193, column: 14, scope: !3156)
!3156 = distinct !DILexicalBlock(scope: !3151, file: !1, line: 1192, column: 30)
!3157 = !DILocation(line: 1193, column: 5, scope: !3156)
!3158 = !DILocation(line: 1194, column: 5, scope: !3156)
!3159 = !DILocation(line: 1198, column: 10, scope: !1097)
!3160 = !DILocation(line: 1198, column: 15, scope: !1097)
!3161 = !DILocation(line: 1198, column: 28, scope: !1097)
!3162 = !DILocation(line: 1198, column: 37, scope: !1097)
!3163 = !DILocation(line: 1198, column: 3, scope: !1097)
!3164 = !DILocation(line: 1201, column: 18, scope: !1097)
!3165 = !DILocation(line: 1201, column: 23, scope: !1097)
!3166 = !DILocation(line: 1201, column: 34, scope: !1097)
!3167 = !DILocation(line: 1201, column: 32, scope: !1097)
!3168 = !DILocation(line: 1201, column: 3, scope: !1097)
!3169 = !DILocation(line: 1201, column: 8, scope: !1097)
!3170 = !DILocation(line: 1201, column: 16, scope: !1097)
!3171 = !DILocation(line: 1202, column: 10, scope: !1097)
!3172 = !DILocation(line: 1202, column: 15, scope: !1097)
!3173 = !DILocation(line: 1202, column: 27, scope: !1097)
!3174 = !DILocation(line: 1202, column: 35, scope: !1097)
!3175 = !DILocation(line: 1202, column: 3, scope: !1097)
!3176 = !DILocation(line: 1205, column: 16, scope: !1097)
!3177 = !DILocation(line: 1205, column: 21, scope: !1097)
!3178 = !DILocation(line: 1205, column: 31, scope: !1097)
!3179 = !DILocation(line: 1205, column: 29, scope: !1097)
!3180 = !DILocation(line: 1205, column: 3, scope: !1097)
!3181 = !DILocation(line: 1205, column: 8, scope: !1097)
!3182 = !DILocation(line: 1205, column: 14, scope: !1097)
!3183 = !DILocation(line: 1206, column: 10, scope: !1097)
!3184 = !DILocation(line: 1206, column: 15, scope: !1097)
!3185 = !DILocation(line: 1206, column: 25, scope: !1097)
!3186 = !DILocation(line: 1206, column: 35, scope: !1097)
!3187 = !DILocation(line: 1206, column: 3, scope: !1097)
!3188 = !DILocation(line: 1209, column: 17, scope: !1097)
!3189 = !DILocation(line: 1209, column: 14, scope: !1097)
!3190 = !DILocation(line: 1209, column: 3, scope: !1097)
!3191 = !DILocation(line: 1209, column: 8, scope: !1097)
!3192 = !DILocation(line: 1209, column: 12, scope: !1097)
!3193 = !DILocation(line: 1210, column: 17, scope: !1097)
!3194 = !DILocation(line: 1210, column: 14, scope: !1097)
!3195 = !DILocation(line: 1210, column: 3, scope: !1097)
!3196 = !DILocation(line: 1210, column: 8, scope: !1097)
!3197 = !DILocation(line: 1210, column: 12, scope: !1097)
!3198 = !DILocation(line: 1212, column: 12, scope: !1097)
!3199 = !DILocation(line: 1212, column: 3, scope: !1097)
!3200 = !DILocation(line: 1214, column: 3, scope: !1097)
!3201 = !DILocation(line: 1215, column: 1, scope: !1097)
!3202 = !DILocalVariable(name: "pwd", arg: 1, scope: !1109, file: !1, line: 1218, type: !1100)
!3203 = !DILocation(line: 1218, column: 37, scope: !1109)
!3204 = !DILocation(line: 1219, column: 7, scope: !3205)
!3205 = distinct !DILexicalBlock(scope: !1109, file: !1, line: 1219, column: 7)
!3206 = !DILocation(line: 1219, column: 11, scope: !3205)
!3207 = !DILocation(line: 1219, column: 7, scope: !1109)
!3208 = !DILocation(line: 1220, column: 5, scope: !3205)
!3209 = !DILocation(line: 1227, column: 12, scope: !1109)
!3210 = !DILocation(line: 1227, column: 17, scope: !1109)
!3211 = !DILocation(line: 1227, column: 3, scope: !1109)
!3212 = !DILocation(line: 1228, column: 3, scope: !1109)
!3213 = !DILocation(line: 1228, column: 8, scope: !1109)
!3214 = !DILocation(line: 1228, column: 17, scope: !1109)
!3215 = !DILocation(line: 1229, column: 3, scope: !1109)
!3216 = !DILocation(line: 1229, column: 8, scope: !1109)
!3217 = !DILocation(line: 1229, column: 14, scope: !1109)
!3218 = !DILocation(line: 1230, column: 3, scope: !1109)
!3219 = !DILocation(line: 1230, column: 8, scope: !1109)
!3220 = !DILocation(line: 1230, column: 16, scope: !1109)
!3221 = !DILocation(line: 1231, column: 1, scope: !1109)
!3222 = !DILocation(line: 1231, column: 1, scope: !3223)
!3223 = !DILexicalBlockFile(scope: !1109, file: !1, discriminator: 1)
!3224 = !DILocalVariable(name: "buffer", arg: 1, scope: !1096, file: !1, line: 1078, type: !551)
!3225 = !DILocation(line: 1078, column: 24, scope: !1096)
!3226 = !DILocalVariable(name: "size", arg: 2, scope: !1096, file: !1, line: 1078, type: !1037)
!3227 = !DILocation(line: 1078, column: 40, scope: !1096)
!3228 = !DILocalVariable(name: "buf", scope: !1096, file: !1, line: 1079, type: !637)
!3229 = !DILocation(line: 1079, column: 15, scope: !1096)
!3230 = !DILocalVariable(name: "len", scope: !1096, file: !1, line: 1080, type: !539)
!3231 = !DILocation(line: 1080, column: 10, scope: !1096)
!3232 = !DILocation(line: 1082, column: 7, scope: !3233)
!3233 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1082, column: 7)
!3234 = !DILocation(line: 1082, column: 14, scope: !3233)
!3235 = !DILocation(line: 1082, column: 22, scope: !3233)
!3236 = !DILocation(line: 1082, column: 25, scope: !3237)
!3237 = !DILexicalBlockFile(scope: !3233, file: !1, discriminator: 1)
!3238 = !DILocation(line: 1082, column: 30, scope: !3237)
!3239 = !DILocation(line: 1082, column: 38, scope: !3237)
!3240 = !DILocation(line: 1082, column: 42, scope: !3241)
!3241 = !DILexicalBlockFile(scope: !3233, file: !1, discriminator: 2)
!3242 = !DILocation(line: 1082, column: 41, scope: !3241)
!3243 = !DILocation(line: 1082, column: 47, scope: !3241)
!3244 = !DILocation(line: 1082, column: 7, scope: !3241)
!3245 = !DILocation(line: 1083, column: 5, scope: !3233)
!3246 = !DILocation(line: 1094, column: 3, scope: !1096)
!3247 = !DILocation(line: 1094, column: 3, scope: !3248)
!3248 = !DILexicalBlockFile(scope: !3249, file: !1, discriminator: 1)
!3249 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1094, column: 3)
!3250 = !DILocation(line: 1094, column: 3, scope: !3251)
!3251 = !DILexicalBlockFile(scope: !3252, file: !1, discriminator: 2)
!3252 = distinct !DILexicalBlock(scope: !3249, file: !1, line: 1094, column: 3)
!3253 = !DILocation(line: 1094, column: 3, scope: !3254)
!3254 = !DILexicalBlockFile(scope: !3249, file: !1, discriminator: 3)
!3255 = !DILocation(line: 1095, column: 3, scope: !1096)
!3256 = !DILocation(line: 1095, column: 3, scope: !3257)
!3257 = !DILexicalBlockFile(scope: !3258, file: !1, discriminator: 1)
!3258 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1095, column: 3)
!3259 = !DILocation(line: 1095, column: 3, scope: !3260)
!3260 = !DILexicalBlockFile(scope: !3261, file: !1, discriminator: 2)
!3261 = distinct !DILexicalBlock(scope: !3258, file: !1, line: 1095, column: 3)
!3262 = !DILocation(line: 1095, column: 3, scope: !3263)
!3263 = !DILexicalBlockFile(scope: !3258, file: !1, discriminator: 3)
!3264 = !DILocation(line: 1096, column: 3, scope: !1096)
!3265 = !DILocation(line: 1096, column: 3, scope: !3266)
!3266 = !DILexicalBlockFile(scope: !3267, file: !1, discriminator: 1)
!3267 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1096, column: 3)
!3268 = !DILocation(line: 1096, column: 3, scope: !3269)
!3269 = !DILexicalBlockFile(scope: !3270, file: !1, discriminator: 2)
!3270 = distinct !DILexicalBlock(scope: !3267, file: !1, line: 1096, column: 3)
!3271 = !DILocation(line: 1096, column: 3, scope: !3272)
!3272 = !DILexicalBlockFile(scope: !3267, file: !1, discriminator: 3)
!3273 = !DILocation(line: 1097, column: 3, scope: !1096)
!3274 = !DILocation(line: 1097, column: 3, scope: !3275)
!3275 = !DILexicalBlockFile(scope: !3276, file: !1, discriminator: 1)
!3276 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1097, column: 3)
!3277 = !DILocation(line: 1097, column: 3, scope: !3278)
!3278 = !DILexicalBlockFile(scope: !3279, file: !1, discriminator: 2)
!3279 = distinct !DILexicalBlock(scope: !3276, file: !1, line: 1097, column: 3)
!3280 = !DILocation(line: 1097, column: 3, scope: !3281)
!3281 = !DILexicalBlockFile(scope: !3276, file: !1, discriminator: 3)
!3282 = !DILocation(line: 1105, column: 9, scope: !1096)
!3283 = !DILocation(line: 1105, column: 5, scope: !1096)
!3284 = !DILocation(line: 1109, column: 16, scope: !1096)
!3285 = !DILocation(line: 1109, column: 9, scope: !1096)
!3286 = !DILocation(line: 1109, column: 7, scope: !1096)
!3287 = !DILocation(line: 1111, column: 7, scope: !3288)
!3288 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1111, column: 7)
!3289 = !DILocation(line: 1111, column: 15, scope: !3288)
!3290 = !DILocation(line: 1111, column: 14, scope: !3288)
!3291 = !DILocation(line: 1111, column: 11, scope: !3288)
!3292 = !DILocation(line: 1111, column: 7, scope: !1096)
!3293 = !DILocation(line: 1112, column: 13, scope: !3294)
!3294 = distinct !DILexicalBlock(scope: !3288, file: !1, line: 1111, column: 21)
!3295 = !DILocation(line: 1112, column: 17, scope: !3294)
!3296 = !DILocation(line: 1112, column: 6, scope: !3294)
!3297 = !DILocation(line: 1112, column: 11, scope: !3294)
!3298 = !DILocation(line: 1113, column: 5, scope: !3294)
!3299 = !DILocation(line: 1117, column: 7, scope: !3300)
!3300 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1117, column: 7)
!3301 = !DILocation(line: 1117, column: 11, scope: !3300)
!3302 = !DILocation(line: 1117, column: 15, scope: !3300)
!3303 = !DILocation(line: 1117, column: 22, scope: !3304)
!3304 = !DILexicalBlockFile(scope: !3300, file: !1, discriminator: 1)
!3305 = !DILocation(line: 1117, column: 26, scope: !3304)
!3306 = !DILocation(line: 1117, column: 18, scope: !3304)
!3307 = !DILocation(line: 1117, column: 31, scope: !3304)
!3308 = !DILocation(line: 1117, column: 7, scope: !3304)
!3309 = !DILocation(line: 1118, column: 8, scope: !3310)
!3310 = distinct !DILexicalBlock(scope: !3300, file: !1, line: 1117, column: 39)
!3311 = !DILocation(line: 1119, column: 3, scope: !3310)
!3312 = !DILocation(line: 1121, column: 10, scope: !1096)
!3313 = !DILocation(line: 1121, column: 18, scope: !1096)
!3314 = !DILocation(line: 1121, column: 23, scope: !1096)
!3315 = !DILocation(line: 1121, column: 27, scope: !1096)
!3316 = !DILocation(line: 1121, column: 3, scope: !1096)
!3317 = !DILocation(line: 1122, column: 10, scope: !1096)
!3318 = !DILocation(line: 1122, column: 3, scope: !1096)
!3319 = !DILocation(line: 1122, column: 15, scope: !1096)
!3320 = !DILocation(line: 1123, column: 11, scope: !1096)
!3321 = !DILocation(line: 1123, column: 4, scope: !1096)
!3322 = !DILocation(line: 1123, column: 9, scope: !1096)
!3323 = !DILocation(line: 1125, column: 3, scope: !1096)
!3324 = !DILocation(line: 1126, column: 1, scope: !1096)
!3325 = !DILocalVariable(name: "pwd", arg: 1, scope: !1112, file: !1, line: 1234, type: !1100)
!3326 = !DILocation(line: 1234, column: 35, scope: !1112)
!3327 = !DILocation(line: 1235, column: 25, scope: !1112)
!3328 = !DILocation(line: 1235, column: 10, scope: !1112)
!3329 = !DILocation(line: 1235, column: 3, scope: !1112)
!3330 = !DILocalVariable(name: "sys_errno", arg: 1, scope: !1113, file: !1, line: 1239, type: !339)
!3331 = !DILocation(line: 1239, column: 32, scope: !1113)
!3332 = !DILocation(line: 1241, column: 10, scope: !1113)
!3333 = !DILocation(line: 1241, column: 20, scope: !1113)
!3334 = !DILocation(line: 1241, column: 27, scope: !3335)
!3335 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 1)
!3336 = !DILocation(line: 1241, column: 10, scope: !3335)
!3337 = !DILocation(line: 1241, column: 40, scope: !3338)
!3338 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 2)
!3339 = !DILocation(line: 1241, column: 39, scope: !3338)
!3340 = !DILocation(line: 1241, column: 10, scope: !3338)
!3341 = !DILocation(line: 1241, column: 10, scope: !3342)
!3342 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 3)
!3343 = !DILocation(line: 1241, column: 3, scope: !3342)
!3344 = !DILocalVariable(name: "name", arg: 1, scope: !1114, file: !1, line: 1245, type: !637)
!3345 = !DILocation(line: 1245, column: 30, scope: !1114)
!3346 = !DILocalVariable(name: "buffer", arg: 2, scope: !1114, file: !1, line: 1245, type: !551)
!3347 = !DILocation(line: 1245, column: 42, scope: !1114)
!3348 = !DILocalVariable(name: "size", arg: 3, scope: !1114, file: !1, line: 1245, type: !1037)
!3349 = !DILocation(line: 1245, column: 58, scope: !1114)
!3350 = !DILocalVariable(name: "var", scope: !1114, file: !1, line: 1246, type: !551)
!3351 = !DILocation(line: 1246, column: 9, scope: !1114)
!3352 = !DILocalVariable(name: "len", scope: !1114, file: !1, line: 1247, type: !539)
!3353 = !DILocation(line: 1247, column: 10, scope: !1114)
!3354 = !DILocation(line: 1249, column: 7, scope: !3355)
!3355 = distinct !DILexicalBlock(scope: !1114, file: !1, line: 1249, column: 7)
!3356 = !DILocation(line: 1249, column: 12, scope: !3355)
!3357 = !DILocation(line: 1249, column: 20, scope: !3355)
!3358 = !DILocation(line: 1249, column: 23, scope: !3359)
!3359 = !DILexicalBlockFile(scope: !3355, file: !1, discriminator: 1)
!3360 = !DILocation(line: 1249, column: 30, scope: !3359)
!3361 = !DILocation(line: 1249, column: 38, scope: !3359)
!3362 = !DILocation(line: 1249, column: 41, scope: !3363)
!3363 = !DILexicalBlockFile(scope: !3355, file: !1, discriminator: 2)
!3364 = !DILocation(line: 1249, column: 46, scope: !3363)
!3365 = !DILocation(line: 1249, column: 54, scope: !3363)
!3366 = !DILocation(line: 1249, column: 58, scope: !3367)
!3367 = !DILexicalBlockFile(scope: !3355, file: !1, discriminator: 3)
!3368 = !DILocation(line: 1249, column: 57, scope: !3367)
!3369 = !DILocation(line: 1249, column: 63, scope: !3367)
!3370 = !DILocation(line: 1249, column: 7, scope: !3367)
!3371 = !DILocation(line: 1250, column: 5, scope: !3355)
!3372 = !DILocation(line: 1252, column: 16, scope: !1114)
!3373 = !DILocation(line: 1252, column: 9, scope: !1114)
!3374 = !DILocation(line: 1252, column: 7, scope: !1114)
!3375 = !DILocation(line: 1254, column: 7, scope: !3376)
!3376 = distinct !DILexicalBlock(scope: !1114, file: !1, line: 1254, column: 7)
!3377 = !DILocation(line: 1254, column: 11, scope: !3376)
!3378 = !DILocation(line: 1254, column: 7, scope: !1114)
!3379 = !DILocation(line: 1255, column: 5, scope: !3376)
!3380 = !DILocation(line: 1257, column: 16, scope: !1114)
!3381 = !DILocation(line: 1257, column: 9, scope: !1114)
!3382 = !DILocation(line: 1257, column: 7, scope: !1114)
!3383 = !DILocation(line: 1259, column: 7, scope: !3384)
!3384 = distinct !DILexicalBlock(scope: !1114, file: !1, line: 1259, column: 7)
!3385 = !DILocation(line: 1259, column: 15, scope: !3384)
!3386 = !DILocation(line: 1259, column: 14, scope: !3384)
!3387 = !DILocation(line: 1259, column: 11, scope: !3384)
!3388 = !DILocation(line: 1259, column: 7, scope: !1114)
!3389 = !DILocation(line: 1260, column: 13, scope: !3390)
!3390 = distinct !DILexicalBlock(scope: !3384, file: !1, line: 1259, column: 21)
!3391 = !DILocation(line: 1260, column: 17, scope: !3390)
!3392 = !DILocation(line: 1260, column: 6, scope: !3390)
!3393 = !DILocation(line: 1260, column: 11, scope: !3390)
!3394 = !DILocation(line: 1261, column: 5, scope: !3390)
!3395 = !DILocation(line: 1264, column: 10, scope: !1114)
!3396 = !DILocation(line: 1264, column: 18, scope: !1114)
!3397 = !DILocation(line: 1264, column: 23, scope: !1114)
!3398 = !DILocation(line: 1264, column: 27, scope: !1114)
!3399 = !DILocation(line: 1264, column: 3, scope: !1114)
!3400 = !DILocation(line: 1265, column: 11, scope: !1114)
!3401 = !DILocation(line: 1265, column: 4, scope: !1114)
!3402 = !DILocation(line: 1265, column: 9, scope: !1114)
!3403 = !DILocation(line: 1267, column: 3, scope: !1114)
!3404 = !DILocation(line: 1268, column: 1, scope: !1114)
!3405 = !DILocalVariable(name: "name", arg: 1, scope: !1117, file: !1, line: 1271, type: !637)
!3406 = !DILocation(line: 1271, column: 30, scope: !1117)
!3407 = !DILocalVariable(name: "value", arg: 2, scope: !1117, file: !1, line: 1271, type: !637)
!3408 = !DILocation(line: 1271, column: 48, scope: !1117)
!3409 = !DILocation(line: 1272, column: 7, scope: !3410)
!3410 = distinct !DILexicalBlock(scope: !1117, file: !1, line: 1272, column: 7)
!3411 = !DILocation(line: 1272, column: 12, scope: !3410)
!3412 = !DILocation(line: 1272, column: 20, scope: !3410)
!3413 = !DILocation(line: 1272, column: 23, scope: !3414)
!3414 = !DILexicalBlockFile(scope: !3410, file: !1, discriminator: 1)
!3415 = !DILocation(line: 1272, column: 29, scope: !3414)
!3416 = !DILocation(line: 1272, column: 7, scope: !3414)
!3417 = !DILocation(line: 1273, column: 5, scope: !3410)
!3418 = !DILocation(line: 1275, column: 14, scope: !3419)
!3419 = distinct !DILexicalBlock(scope: !1117, file: !1, line: 1275, column: 7)
!3420 = !DILocation(line: 1275, column: 20, scope: !3419)
!3421 = !DILocation(line: 1275, column: 7, scope: !3419)
!3422 = !DILocation(line: 1275, column: 30, scope: !3419)
!3423 = !DILocation(line: 1275, column: 7, scope: !1117)
!3424 = !DILocation(line: 1276, column: 13, scope: !3419)
!3425 = !DILocation(line: 1276, column: 12, scope: !3419)
!3426 = !DILocation(line: 1276, column: 5, scope: !3419)
!3427 = !DILocation(line: 1278, column: 3, scope: !1117)
!3428 = !DILocation(line: 1279, column: 1, scope: !1117)
!3429 = !DILocalVariable(name: "name", arg: 1, scope: !1120, file: !1, line: 1282, type: !637)
!3430 = !DILocation(line: 1282, column: 32, scope: !1120)
!3431 = !DILocation(line: 1283, column: 16, scope: !3432)
!3432 = distinct !DILexicalBlock(scope: !1120, file: !1, line: 1283, column: 7)
!3433 = !DILocation(line: 1283, column: 7, scope: !3432)
!3434 = !DILocation(line: 1283, column: 22, scope: !3432)
!3435 = !DILocation(line: 1283, column: 7, scope: !1120)
!3436 = !DILocation(line: 1284, column: 13, scope: !3432)
!3437 = !DILocation(line: 1284, column: 12, scope: !3432)
!3438 = !DILocation(line: 1284, column: 5, scope: !3432)
!3439 = !DILocation(line: 1286, column: 3, scope: !1120)
!3440 = !DILocation(line: 1287, column: 1, scope: !1120)
!3441 = !DILocalVariable(name: "handle", arg: 1, scope: !1124, file: !1, line: 227, type: !408)
!3442 = !DILocation(line: 227, column: 43, scope: !1124)
!3443 = !DILocation(line: 234, column: 3, scope: !1124)
!3444 = !DILocation(line: 234, column: 3, scope: !3445)
!3445 = !DILexicalBlockFile(scope: !1124, file: !1, discriminator: 1)
!3446 = !DILocation(line: 234, column: 3, scope: !3447)
!3447 = !DILexicalBlockFile(scope: !1124, file: !1, discriminator: 2)
!3448 = !DILocation(line: 234, column: 3, scope: !3449)
!3449 = !DILexicalBlockFile(scope: !1124, file: !1, discriminator: 3)
!3450 = !DILocation(line: 235, column: 3, scope: !1124)
!3451 = !DILocation(line: 235, column: 3, scope: !3445)
!3452 = !DILocation(line: 235, column: 3, scope: !3447)
!3453 = !DILocation(line: 235, column: 3, scope: !3449)
!3454 = !DILocation(line: 236, column: 3, scope: !1124)
!3455 = !DILocation(line: 236, column: 11, scope: !1124)
!3456 = !DILocation(line: 236, column: 17, scope: !1124)
!3457 = !DILocation(line: 238, column: 11, scope: !1124)
!3458 = !DILocation(line: 238, column: 19, scope: !1124)
!3459 = !DILocation(line: 238, column: 3, scope: !1124)
!3460 = !DILocation(line: 249, column: 7, scope: !3461)
!3461 = distinct !DILexicalBlock(scope: !1124, file: !1, line: 238, column: 25)
!3462 = !DILocation(line: 254, column: 40, scope: !3461)
!3463 = !DILocation(line: 254, column: 26, scope: !3461)
!3464 = !DILocation(line: 254, column: 7, scope: !3461)
!3465 = !DILocation(line: 255, column: 7, scope: !3461)
!3466 = !DILocation(line: 258, column: 39, scope: !3461)
!3467 = !DILocation(line: 258, column: 28, scope: !3461)
!3468 = !DILocation(line: 258, column: 7, scope: !3461)
!3469 = !DILocation(line: 259, column: 7, scope: !3461)
!3470 = !DILocation(line: 262, column: 7, scope: !3461)
!3471 = !DILocation(line: 266, column: 3, scope: !1124)
!3472 = !DILocation(line: 266, column: 3, scope: !3473)
!3473 = !DILexicalBlockFile(scope: !3474, file: !1, discriminator: 1)
!3474 = distinct !DILexicalBlock(scope: !3475, file: !1, line: 266, column: 3)
!3475 = distinct !DILexicalBlock(scope: !1124, file: !1, line: 266, column: 3)
!3476 = !DILocation(line: 266, column: 3, scope: !3477)
!3477 = !DILexicalBlockFile(scope: !3474, file: !1, discriminator: 2)
!3478 = !DILocation(line: 266, column: 3, scope: !3479)
!3479 = !DILexicalBlockFile(scope: !3475, file: !1, discriminator: 3)
!3480 = !DILocation(line: 266, column: 3, scope: !3481)
!3481 = !DILexicalBlockFile(scope: !3482, file: !1, discriminator: 4)
!3482 = distinct !DILexicalBlock(scope: !3475, file: !1, line: 266, column: 3)
!3483 = !DILocation(line: 266, column: 3, scope: !3484)
!3484 = !DILexicalBlockFile(scope: !3485, file: !1, discriminator: 5)
!3485 = distinct !DILexicalBlock(scope: !3475, file: !1, line: 266, column: 3)
!3486 = !DILocation(line: 266, column: 3, scope: !3487)
!3487 = !DILexicalBlockFile(scope: !3485, file: !1, discriminator: 6)
!3488 = !DILocation(line: 266, column: 3, scope: !3489)
!3489 = !DILexicalBlockFile(scope: !3490, file: !1, discriminator: 7)
!3490 = distinct !DILexicalBlock(scope: !3485, file: !1, line: 266, column: 3)
!3491 = !DILocation(line: 266, column: 3, scope: !3492)
!3492 = !DILexicalBlockFile(scope: !3490, file: !1, discriminator: 8)
!3493 = !DILocation(line: 266, column: 3, scope: !3494)
!3494 = !DILexicalBlockFile(scope: !3475, file: !1, discriminator: 9)
!3495 = !DILocation(line: 267, column: 3, scope: !1124)
!3496 = !DILocation(line: 267, column: 3, scope: !3497)
!3497 = !DILexicalBlockFile(scope: !3498, file: !1, discriminator: 1)
!3498 = distinct !DILexicalBlock(scope: !1124, file: !1, line: 267, column: 3)
!3499 = !DILocation(line: 269, column: 7, scope: !3500)
!3500 = distinct !DILexicalBlock(scope: !1124, file: !1, line: 269, column: 7)
!3501 = !DILocation(line: 269, column: 15, scope: !3500)
!3502 = !DILocation(line: 269, column: 7, scope: !1124)
!3503 = !DILocation(line: 270, column: 5, scope: !3504)
!3504 = distinct !DILexicalBlock(scope: !3500, file: !1, line: 269, column: 25)
!3505 = !DILocation(line: 270, column: 13, scope: !3504)
!3506 = !DILocation(line: 270, column: 22, scope: !3504)
!3507 = !DILocation(line: 271, column: 3, scope: !3504)
!3508 = !DILocation(line: 272, column: 1, scope: !1124)
!3509 = !DILocalVariable(name: "val", arg: 1, scope: !1131, file: !1, line: 765, type: !329)
!3510 = !DILocation(line: 765, column: 52, scope: !1131)
!3511 = !DILocation(line: 766, column: 7, scope: !1131)
!3512 = !DILocation(line: 767, column: 10, scope: !1131)
!3513 = !DILocation(line: 767, column: 14, scope: !1131)
!3514 = !DILocation(line: 767, column: 7, scope: !1131)
!3515 = !DILocation(line: 768, column: 10, scope: !1131)
!3516 = !DILocation(line: 768, column: 14, scope: !1131)
!3517 = !DILocation(line: 768, column: 7, scope: !1131)
!3518 = !DILocation(line: 769, column: 10, scope: !1131)
!3519 = !DILocation(line: 769, column: 14, scope: !1131)
!3520 = !DILocation(line: 769, column: 7, scope: !1131)
!3521 = !DILocation(line: 770, column: 10, scope: !1131)
!3522 = !DILocation(line: 770, column: 14, scope: !1131)
!3523 = !DILocation(line: 770, column: 7, scope: !1131)
!3524 = !DILocation(line: 771, column: 10, scope: !1131)
!3525 = !DILocation(line: 771, column: 14, scope: !1131)
!3526 = !DILocation(line: 771, column: 7, scope: !1131)
!3527 = !DILocation(line: 772, column: 7, scope: !1131)
!3528 = !DILocation(line: 773, column: 10, scope: !1131)
!3529 = !DILocation(line: 773, column: 3, scope: !1131)
