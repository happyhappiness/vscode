; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/udp.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.in6_addr = type { %union.anon.5 }
%union.anon.5 = type { [4 x i32] }
%struct.uv_udp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i64, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, %struct.uv__io_s, [2 x i8*], [2 x i8*] }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.1, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.0 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.anon.1 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.2, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.3, i32, i32 }
%union.anon.2 = type { [4 x i8*] }
%struct.anon.3 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32 }
%union.anon = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%struct.uv_udp_send_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_udp_s*, void (%struct.uv_udp_send_s*, i32)*, [2 x i8*], %struct.sockaddr_storage, i32, %struct.uv_buf_t*, i64, void (%struct.uv_udp_send_s*, i32)*, [4 x %struct.uv_buf_t] }
%struct.sockaddr_storage = type { i16, i64, [112 x i8] }
%union.__CONST_SOCKADDR_ARG = type { %struct.sockaddr* }
%union.anon.6 = type { %struct.sockaddr_in6 }
%struct.sockaddr_in6 = type { i16, i16, i32, %struct.in6_addr, i32 }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.msghdr = type { i8*, i32, %struct.iovec*, i64, i8*, i64, i32 }
%struct.iovec = type { i8*, i64 }
%struct.ip_mreq = type { %struct.in_addr, %struct.in_addr }
%struct.ipv6_mreq = type { %struct.in6_addr, i32 }
%union.__SOCKADDR_ARG = type { %struct.sockaddr* }

@.str = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.1 = private unnamed_addr constant [67 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/udp.c\00", align 1
@__PRETTY_FUNCTION__.uv__udp_close = private unnamed_addr constant [31 x i8] c"void uv__udp_close(uv_udp_t *)\00", align 1
@.str.2 = private unnamed_addr constant [51 x i8] c"!uv__io_active(&handle->io_watcher, 0x001 | 0x004)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_finish_close = private unnamed_addr constant [38 x i8] c"void uv__udp_finish_close(uv_udp_t *)\00", align 1
@.str.3 = private unnamed_addr constant [28 x i8] c"handle->io_watcher.fd == -1\00", align 1
@.str.4 = private unnamed_addr constant [29 x i8] c"handle->send_queue_size == 0\00", align 1
@.str.5 = private unnamed_addr constant [30 x i8] c"handle->send_queue_count == 0\00", align 1
@.str.6 = private unnamed_addr constant [10 x i8] c"nbufs > 0\00", align 1
@__PRETTY_FUNCTION__.uv__udp_send = private unnamed_addr constant [133 x i8] c"int uv__udp_send(uv_udp_send_t *, uv_udp_t *, const uv_buf_t *, unsigned int, const struct sockaddr *, unsigned int, uv_udp_send_cb)\00", align 1
@.str.7 = private unnamed_addr constant [29 x i8] c"addrlen <= sizeof(req->addr)\00", align 1
@.str.8 = private unnamed_addr constant [129 x i8] c"(((const QUEUE *) (&(handle->loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(handle->loop)->active_reqs))[0]))) == 0)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_try_send = private unnamed_addr constant [104 x i8] c"int uv__udp_try_send(uv_udp_t *, const uv_buf_t *, unsigned int, const struct sockaddr *, unsigned int)\00", align 1
@.str.9 = private unnamed_addr constant [33 x i8] c"0 && \22unexpected address family\22\00", align 1
@__PRETTY_FUNCTION__.uv_udp_set_multicast_interface = private unnamed_addr constant [61 x i8] c"int uv_udp_set_multicast_interface(uv_udp_t *, const char *)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_recv_start = private unnamed_addr constant [64 x i8] c"int uv__udp_recv_start(uv_udp_t *, uv_alloc_cb, uv_udp_recv_cb)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_recv_stop = private unnamed_addr constant [34 x i8] c"int uv__udp_recv_stop(uv_udp_t *)\00", align 1
@.str.10 = private unnamed_addr constant [37 x i8] c"!(handle->flags & UV_UDP_PROCESSING)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_run_completed = private unnamed_addr constant [39 x i8] c"void uv__udp_run_completed(uv_udp_t *)\00", align 1
@in6addr_any = external constant %struct.in6_addr, align 4
@.str.11 = private unnamed_addr constant [34 x i8] c"0 && \22unsupported address family\22\00", align 1
@__PRETTY_FUNCTION__.uv__udp_maybe_deferred_bind = private unnamed_addr constant [63 x i8] c"int uv__udp_maybe_deferred_bind(uv_udp_t *, int, unsigned int)\00", align 1
@.str.12 = private unnamed_addr constant [16 x i8] c"q != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_sendmsg = private unnamed_addr constant [33 x i8] c"void uv__udp_sendmsg(uv_udp_t *)\00", align 1
@.str.13 = private unnamed_addr constant [18 x i8] c"req != ((void*)0)\00", align 1
@.str.14 = private unnamed_addr constant [23 x i8] c"handle->type == UV_UDP\00", align 1
@__PRETTY_FUNCTION__.uv__udp_io = private unnamed_addr constant [55 x i8] c"void uv__udp_io(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@.str.15 = private unnamed_addr constant [30 x i8] c"handle->recv_cb != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv__udp_recvmsg = private unnamed_addr constant [33 x i8] c"void uv__udp_recvmsg(uv_udp_t *)\00", align 1
@.str.16 = private unnamed_addr constant [31 x i8] c"handle->alloc_cb != ((void*)0)\00", align 1
@.str.17 = private unnamed_addr constant [23 x i8] c"buf.base != ((void*)0)\00", align 1

; Function Attrs: nounwind uwtable
define void @uv__udp_close(%struct.uv_udp_s* %handle) #0 !dbg !568 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !652, metadata !653), !dbg !654
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !655
  %loop = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 1, !dbg !656
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !656
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !657
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %2, i32 0, i32 12, !dbg !658
  call void @uv__io_close(%struct.uv_loop_s* %1, %struct.uv__io_s* %io_watcher), !dbg !659
  br label %do.body, !dbg !660

do.body:                                          ; preds = %entry
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !661
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %3, i32 0, i32 7, !dbg !661
  %4 = load i32, i32* %flags, align 8, !dbg !661
  %and = and i32 %4, 0, !dbg !661
  %cmp = icmp eq i32 %and, 0, !dbg !661
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !661

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !664

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 54, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.uv__udp_close, i32 0, i32 0)) #7, !dbg !666
  unreachable, !dbg !666
                                                  ; No predecessors!
  br label %cond.end, !dbg !668

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !670
  %flags1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %6, i32 0, i32 7, !dbg !670
  %7 = load i32, i32* %flags1, align 8, !dbg !670
  %and2 = and i32 %7, 16384, !dbg !670
  %cmp3 = icmp eq i32 %and2, 0, !dbg !670
  br i1 %cmp3, label %if.then, label %if.end, !dbg !670

if.then:                                          ; preds = %cond.end
  br label %do.end13, !dbg !673

if.end:                                           ; preds = %cond.end
  %8 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !675
  %flags4 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %8, i32 0, i32 7, !dbg !675
  %9 = load i32, i32* %flags4, align 8, !dbg !675
  %and5 = and i32 %9, -16385, !dbg !675
  store i32 %and5, i32* %flags4, align 8, !dbg !675
  %10 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !675
  %flags6 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %10, i32 0, i32 7, !dbg !675
  %11 = load i32, i32* %flags6, align 8, !dbg !675
  %and7 = and i32 %11, 8192, !dbg !675
  %cmp8 = icmp ne i32 %and7, 0, !dbg !675
  br i1 %cmp8, label %if.then9, label %if.end12, !dbg !675

if.then9:                                         ; preds = %if.end
  br label %do.body10, !dbg !677

do.body10:                                        ; preds = %if.then9
  %12 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !680
  %loop11 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %12, i32 0, i32 1, !dbg !680
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop11, align 8, !dbg !680
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 1, !dbg !680
  %14 = load i32, i32* %active_handles, align 8, !dbg !680
  %dec = add i32 %14, -1, !dbg !680
  store i32 %dec, i32* %active_handles, align 8, !dbg !680
  br label %do.end, !dbg !680

do.end:                                           ; preds = %do.body10
  br label %if.end12, !dbg !683

if.end12:                                         ; preds = %do.end, %if.end
  br label %do.end13, !dbg !685

do.end13:                                         ; preds = %if.end12, %if.then
  %15 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !687
  %io_watcher14 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %15, i32 0, i32 12, !dbg !689
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher14, i32 0, i32 5, !dbg !690
  %16 = load i32, i32* %fd, align 8, !dbg !690
  %cmp15 = icmp ne i32 %16, -1, !dbg !691
  br i1 %cmp15, label %if.then16, label %if.end21, !dbg !692

if.then16:                                        ; preds = %do.end13
  %17 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !693
  %io_watcher17 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %17, i32 0, i32 12, !dbg !695
  %fd18 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher17, i32 0, i32 5, !dbg !696
  %18 = load i32, i32* %fd18, align 8, !dbg !696
  %call = call i32 @uv__close(i32 %18), !dbg !697
  %19 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !698
  %io_watcher19 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %19, i32 0, i32 12, !dbg !699
  %fd20 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher19, i32 0, i32 5, !dbg !700
  store i32 -1, i32* %fd20, align 8, !dbg !701
  br label %if.end21, !dbg !702

if.end21:                                         ; preds = %if.then16, %do.end13
  ret void, !dbg !703
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @uv__io_close(%struct.uv_loop_s*, %struct.uv__io_s*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

declare i32 @uv__close(i32) #2

; Function Attrs: nounwind uwtable
define void @uv__udp_finish_close(%struct.uv_udp_s* %handle) #0 !dbg !572 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %req = alloca %struct.uv_udp_send_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !704, metadata !653), !dbg !705
  call void @llvm.dbg.declare(metadata %struct.uv_udp_send_s** %req, metadata !706, metadata !653), !dbg !707
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !708, metadata !653), !dbg !709
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !710
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 12, !dbg !710
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher, i32 5), !dbg !710
  %tobool = icmp ne i32 %call, 0, !dbg !710
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !710

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !711

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 67, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.uv__udp_finish_close, i32 0, i32 0)) #7, !dbg !713
  unreachable, !dbg !713
                                                  ; No predecessors!
  br label %cond.end, !dbg !715

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !717
  %io_watcher1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %2, i32 0, i32 12, !dbg !717
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher1, i32 0, i32 5, !dbg !717
  %3 = load i32, i32* %fd, align 8, !dbg !717
  %cmp = icmp eq i32 %3, -1, !dbg !717
  br i1 %cmp, label %cond.true2, label %cond.false3, !dbg !717

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !718

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 68, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.uv__udp_finish_close, i32 0, i32 0)) #7, !dbg !719
  unreachable, !dbg !719
                                                  ; No predecessors!
  br label %cond.end4, !dbg !720

cond.end4:                                        ; preds = %4, %cond.true2
  br label %while.cond, !dbg !721

while.cond:                                       ; preds = %do.end28, %cond.end4
  %5 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !722
  %write_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %5, i32 0, i32 13, !dbg !722
  %6 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !722
  %write_queue5 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %6, i32 0, i32 13, !dbg !722
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue5, i64 0, i64 0, !dbg !722
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !722
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !722
  %cmp6 = icmp eq [2 x i8*]* %write_queue, %8, !dbg !722
  %lnot = xor i1 %cmp6, true, !dbg !723
  br i1 %lnot, label %while.body, label %while.end, !dbg !724

while.body:                                       ; preds = %while.cond
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !725
  %write_queue7 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %9, i32 0, i32 13, !dbg !725
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue7, i64 0, i64 0, !dbg !725
  %10 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !725
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !725
  store [2 x i8*]* %11, [2 x i8*]** %q, align 8, !dbg !727
  br label %do.body, !dbg !728

do.body:                                          ; preds = %while.body
  %12 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !729
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %12, i64 0, i64 0, !dbg !729
  %13 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !729
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !729
  %15 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !729
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 1, !dbg !729
  %16 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !729
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !729
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %17, i64 0, i64 0, !dbg !729
  %18 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !729
  store [2 x i8*]* %14, [2 x i8*]** %18, align 8, !dbg !729
  %19 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !729
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %19, i64 0, i64 1, !dbg !729
  %20 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !729
  %21 = load [2 x i8*]*, [2 x i8*]** %20, align 8, !dbg !729
  %22 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !729
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !729
  %23 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !729
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !729
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 1, !dbg !729
  %25 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !729
  store [2 x i8*]* %21, [2 x i8*]** %25, align 8, !dbg !729
  br label %do.end, !dbg !729

do.end:                                           ; preds = %do.body
  %26 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !732
  %27 = bitcast [2 x i8*]* %26 to i8*, !dbg !732
  %add.ptr = getelementptr inbounds i8, i8* %27, i64 -80, !dbg !732
  %28 = bitcast i8* %add.ptr to %struct.uv_udp_send_s*, !dbg !732
  store %struct.uv_udp_send_s* %28, %struct.uv_udp_send_s** %req, align 8, !dbg !733
  %29 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !734
  %status = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %29, i32 0, i32 10, !dbg !735
  store i64 -125, i64* %status, align 8, !dbg !736
  br label %do.body15, !dbg !737

do.body15:                                        ; preds = %do.end
  %30 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !738
  %write_completed_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %30, i32 0, i32 14, !dbg !738
  %31 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !738
  %queue = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %31, i32 0, i32 6, !dbg !738
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !738
  %32 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !738
  store [2 x i8*]* %write_completed_queue, [2 x i8*]** %32, align 8, !dbg !738
  %33 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !738
  %write_completed_queue17 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %33, i32 0, i32 14, !dbg !738
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue17, i64 0, i64 1, !dbg !738
  %34 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !738
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !738
  %36 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !738
  %queue19 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %36, i32 0, i32 6, !dbg !738
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue19, i64 0, i64 1, !dbg !738
  %37 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !738
  store [2 x i8*]* %35, [2 x i8*]** %37, align 8, !dbg !738
  %38 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !738
  %queue21 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %38, i32 0, i32 6, !dbg !738
  %39 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !738
  %queue22 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %39, i32 0, i32 6, !dbg !738
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue22, i64 0, i64 1, !dbg !738
  %40 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !738
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 8, !dbg !738
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %41, i64 0, i64 0, !dbg !738
  %42 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !738
  store [2 x i8*]* %queue21, [2 x i8*]** %42, align 8, !dbg !738
  %43 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !738
  %queue25 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %43, i32 0, i32 6, !dbg !738
  %44 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !738
  %write_completed_queue26 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %44, i32 0, i32 14, !dbg !738
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue26, i64 0, i64 1, !dbg !738
  %45 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !738
  store [2 x i8*]* %queue25, [2 x i8*]** %45, align 8, !dbg !738
  br label %do.end28, !dbg !738

do.end28:                                         ; preds = %do.body15
  br label %while.cond, !dbg !741

while.end:                                        ; preds = %while.cond
  %46 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !742
  call void @uv__udp_run_completed(%struct.uv_udp_s* %46), !dbg !743
  %47 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !744
  %send_queue_size = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %47, i32 0, i32 8, !dbg !744
  %48 = load i64, i64* %send_queue_size, align 8, !dbg !744
  %cmp29 = icmp eq i64 %48, 0, !dbg !744
  br i1 %cmp29, label %cond.true30, label %cond.false31, !dbg !744

cond.true30:                                      ; preds = %while.end
  br label %cond.end32, !dbg !745

cond.false31:                                     ; preds = %while.end
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 81, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.uv__udp_finish_close, i32 0, i32 0)) #7, !dbg !746
  unreachable, !dbg !746
                                                  ; No predecessors!
  br label %cond.end32, !dbg !747

cond.end32:                                       ; preds = %49, %cond.true30
  %50 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !748
  %send_queue_count = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %50, i32 0, i32 9, !dbg !748
  %51 = load i64, i64* %send_queue_count, align 8, !dbg !748
  %cmp33 = icmp eq i64 %51, 0, !dbg !748
  br i1 %cmp33, label %cond.true34, label %cond.false35, !dbg !748

cond.true34:                                      ; preds = %cond.end32
  br label %cond.end36, !dbg !749

cond.false35:                                     ; preds = %cond.end32
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 82, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.uv__udp_finish_close, i32 0, i32 0)) #7, !dbg !750
  unreachable, !dbg !750
                                                  ; No predecessors!
  br label %cond.end36, !dbg !751

cond.end36:                                       ; preds = %52, %cond.true34
  %53 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !752
  %recv_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %53, i32 0, i32 11, !dbg !753
  store void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* null, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb, align 8, !dbg !754
  %54 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !755
  %alloc_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %54, i32 0, i32 10, !dbg !756
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !757
  ret void, !dbg !758
}

declare i32 @uv__io_active(%struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__udp_run_completed(%struct.uv_udp_s* %handle) #0 !dbg !619 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %req = alloca %struct.uv_udp_send_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !759, metadata !653), !dbg !760
  call void @llvm.dbg.declare(metadata %struct.uv_udp_send_s** %req, metadata !761, metadata !653), !dbg !762
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !763, metadata !653), !dbg !764
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !765
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 7, !dbg !765
  %1 = load i32, i32* %flags, align 8, !dbg !765
  %and = and i32 %1, 131072, !dbg !765
  %tobool = icmp ne i32 %and, 0, !dbg !765
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !765

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !766

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 95, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__udp_run_completed, i32 0, i32 0)) #7, !dbg !768
  unreachable, !dbg !768
                                                  ; No predecessors!
  br label %cond.end, !dbg !770

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !772
  %flags1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %3, i32 0, i32 7, !dbg !773
  %4 = load i32, i32* %flags1, align 8, !dbg !774
  %or = or i32 %4, 131072, !dbg !774
  store i32 %or, i32* %flags1, align 8, !dbg !774
  br label %while.cond, !dbg !775

while.cond:                                       ; preds = %if.end49, %if.then40, %cond.end
  %5 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !776
  %write_completed_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %5, i32 0, i32 14, !dbg !776
  %6 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !776
  %write_completed_queue2 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %6, i32 0, i32 14, !dbg !776
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue2, i64 0, i64 0, !dbg !776
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !776
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !776
  %cmp = icmp eq [2 x i8*]* %write_completed_queue, %8, !dbg !776
  %lnot = xor i1 %cmp, true, !dbg !777
  br i1 %lnot, label %while.body, label %while.end, !dbg !778

while.body:                                       ; preds = %while.cond
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !779
  %write_completed_queue3 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %9, i32 0, i32 14, !dbg !779
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue3, i64 0, i64 0, !dbg !779
  %10 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !779
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !779
  store [2 x i8*]* %11, [2 x i8*]** %q, align 8, !dbg !781
  br label %do.body, !dbg !782

do.body:                                          ; preds = %while.body
  %12 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %12, i64 0, i64 0, !dbg !783
  %13 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !783
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !783
  %15 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 1, !dbg !783
  %16 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !783
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !783
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %17, i64 0, i64 0, !dbg !783
  %18 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !783
  store [2 x i8*]* %14, [2 x i8*]** %18, align 8, !dbg !783
  %19 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %19, i64 0, i64 1, !dbg !783
  %20 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !783
  %21 = load [2 x i8*]*, [2 x i8*]** %20, align 8, !dbg !783
  %22 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !783
  %23 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !783
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !783
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 1, !dbg !783
  %25 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !783
  store [2 x i8*]* %21, [2 x i8*]** %25, align 8, !dbg !783
  br label %do.end, !dbg !783

do.end:                                           ; preds = %do.body
  %26 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !786
  %27 = bitcast [2 x i8*]* %26 to i8*, !dbg !786
  %add.ptr = getelementptr inbounds i8, i8* %27, i64 -80, !dbg !786
  %28 = bitcast i8* %add.ptr to %struct.uv_udp_send_s*, !dbg !786
  store %struct.uv_udp_send_s* %28, %struct.uv_udp_send_s** %req, align 8, !dbg !787
  br label %do.body11, !dbg !788

do.body11:                                        ; preds = %do.end
  %29 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !789
  %loop = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %29, i32 0, i32 1, !dbg !789
  %30 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !789
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %30, i32 0, i32 3, !dbg !789
  %31 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !789
  %loop12 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %31, i32 0, i32 1, !dbg !789
  %32 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop12, align 8, !dbg !789
  %active_reqs13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %32, i32 0, i32 3, !dbg !789
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs13, i64 0, i64 0, !dbg !789
  %33 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !789
  %34 = load [2 x i8*]*, [2 x i8*]** %33, align 8, !dbg !789
  %cmp15 = icmp eq [2 x i8*]* %active_reqs, %34, !dbg !789
  %conv = zext i1 %cmp15 to i32, !dbg !789
  %cmp16 = icmp eq i32 %conv, 0, !dbg !789
  br i1 %cmp16, label %cond.true18, label %cond.false19, !dbg !789

cond.true18:                                      ; preds = %do.body11
  br label %cond.end20, !dbg !792

cond.false19:                                     ; preds = %do.body11
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 103, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__udp_run_completed, i32 0, i32 0)) #7, !dbg !794
  unreachable, !dbg !794
                                                  ; No predecessors!
  br label %cond.end20, !dbg !796

cond.end20:                                       ; preds = %35, %cond.true18
  br label %do.body21, !dbg !798

do.body21:                                        ; preds = %cond.end20
  %36 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !800
  %active_queue = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %36, i32 0, i32 2, !dbg !800
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !800
  %37 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !800
  %38 = load [2 x i8*]*, [2 x i8*]** %37, align 8, !dbg !800
  %39 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !800
  %active_queue23 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %39, i32 0, i32 2, !dbg !800
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue23, i64 0, i64 1, !dbg !800
  %40 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !800
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 8, !dbg !800
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %41, i64 0, i64 0, !dbg !800
  %42 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !800
  store [2 x i8*]* %38, [2 x i8*]** %42, align 8, !dbg !800
  %43 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !800
  %active_queue26 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %43, i32 0, i32 2, !dbg !800
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue26, i64 0, i64 1, !dbg !800
  %44 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !800
  %45 = load [2 x i8*]*, [2 x i8*]** %44, align 8, !dbg !800
  %46 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !800
  %active_queue28 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %46, i32 0, i32 2, !dbg !800
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue28, i64 0, i64 0, !dbg !800
  %47 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !800
  %48 = load [2 x i8*]*, [2 x i8*]** %47, align 8, !dbg !800
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %48, i64 0, i64 1, !dbg !800
  %49 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !800
  store [2 x i8*]* %45, [2 x i8*]** %49, align 8, !dbg !800
  br label %do.end31, !dbg !800

do.end31:                                         ; preds = %do.body21
  br label %do.end32, !dbg !803

do.end32:                                         ; preds = %do.end31
  %50 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !805
  %bufs = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %50, i32 0, i32 9, !dbg !806
  %51 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !806
  %52 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !807
  %nbufs = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %52, i32 0, i32 8, !dbg !808
  %53 = load i32, i32* %nbufs, align 8, !dbg !808
  %call = call i64 @uv__count_bufs(%struct.uv_buf_t* %51, i32 %53), !dbg !809
  %54 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !810
  %send_queue_size = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %54, i32 0, i32 8, !dbg !811
  %55 = load i64, i64* %send_queue_size, align 8, !dbg !812
  %sub = sub i64 %55, %call, !dbg !812
  store i64 %sub, i64* %send_queue_size, align 8, !dbg !812
  %56 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !813
  %send_queue_count = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %56, i32 0, i32 9, !dbg !814
  %57 = load i64, i64* %send_queue_count, align 8, !dbg !815
  %dec = add i64 %57, -1, !dbg !815
  store i64 %dec, i64* %send_queue_count, align 8, !dbg !815
  %58 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !816
  %bufs33 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %58, i32 0, i32 9, !dbg !818
  %59 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs33, align 8, !dbg !818
  %60 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !819
  %bufsml = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %60, i32 0, i32 12, !dbg !820
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !819
  %cmp34 = icmp ne %struct.uv_buf_t* %59, %arraydecay, !dbg !821
  br i1 %cmp34, label %if.then, label %if.end, !dbg !822

if.then:                                          ; preds = %do.end32
  %61 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !823
  %bufs36 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %61, i32 0, i32 9, !dbg !824
  %62 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs36, align 8, !dbg !824
  %63 = bitcast %struct.uv_buf_t* %62 to i8*, !dbg !823
  call void @uv__free(i8* %63), !dbg !825
  br label %if.end, !dbg !825

if.end:                                           ; preds = %if.then, %do.end32
  %64 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !826
  %bufs37 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %64, i32 0, i32 9, !dbg !827
  store %struct.uv_buf_t* null, %struct.uv_buf_t** %bufs37, align 8, !dbg !828
  %65 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !829
  %send_cb = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %65, i32 0, i32 11, !dbg !831
  %66 = load void (%struct.uv_udp_send_s*, i32)*, void (%struct.uv_udp_send_s*, i32)** %send_cb, align 8, !dbg !831
  %cmp38 = icmp eq void (%struct.uv_udp_send_s*, i32)* %66, null, !dbg !832
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !833

if.then40:                                        ; preds = %if.end
  br label %while.cond, !dbg !834

if.end41:                                         ; preds = %if.end
  %67 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !835
  %status = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %67, i32 0, i32 10, !dbg !837
  %68 = load i64, i64* %status, align 8, !dbg !837
  %cmp42 = icmp sge i64 %68, 0, !dbg !838
  br i1 %cmp42, label %if.then44, label %if.else, !dbg !839

if.then44:                                        ; preds = %if.end41
  %69 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !840
  %send_cb45 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %69, i32 0, i32 11, !dbg !841
  %70 = load void (%struct.uv_udp_send_s*, i32)*, void (%struct.uv_udp_send_s*, i32)** %send_cb45, align 8, !dbg !841
  %71 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !842
  call void %70(%struct.uv_udp_send_s* %71, i32 0), !dbg !840
  br label %if.end49, !dbg !840

if.else:                                          ; preds = %if.end41
  %72 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !843
  %send_cb46 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %72, i32 0, i32 11, !dbg !844
  %73 = load void (%struct.uv_udp_send_s*, i32)*, void (%struct.uv_udp_send_s*, i32)** %send_cb46, align 8, !dbg !844
  %74 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !845
  %75 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !846
  %status47 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %75, i32 0, i32 10, !dbg !847
  %76 = load i64, i64* %status47, align 8, !dbg !847
  %conv48 = trunc i64 %76 to i32, !dbg !846
  call void %73(%struct.uv_udp_send_s* %74, i32 %conv48), !dbg !843
  br label %if.end49

if.end49:                                         ; preds = %if.else, %if.then44
  br label %while.cond, !dbg !848

while.end:                                        ; preds = %while.cond
  %77 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !849
  %write_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %77, i32 0, i32 13, !dbg !849
  %78 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !849
  %write_queue50 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %78, i32 0, i32 13, !dbg !849
  %arrayidx51 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue50, i64 0, i64 0, !dbg !849
  %79 = bitcast i8** %arrayidx51 to [2 x i8*]**, !dbg !849
  %80 = load [2 x i8*]*, [2 x i8*]** %79, align 8, !dbg !849
  %cmp52 = icmp eq [2 x i8*]* %write_queue, %80, !dbg !849
  br i1 %cmp52, label %if.then54, label %if.end88, !dbg !851

if.then54:                                        ; preds = %while.end
  %81 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !852
  %loop55 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %81, i32 0, i32 1, !dbg !854
  %82 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop55, align 8, !dbg !854
  %83 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !855
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %83, i32 0, i32 12, !dbg !856
  call void @uv__io_stop(%struct.uv_loop_s* %82, %struct.uv__io_s* %io_watcher, i32 4), !dbg !857
  %84 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !858
  %io_watcher56 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %84, i32 0, i32 12, !dbg !860
  %call57 = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher56, i32 1), !dbg !861
  %tobool58 = icmp ne i32 %call57, 0, !dbg !861
  br i1 %tobool58, label %if.end87, label %if.then59, !dbg !862

if.then59:                                        ; preds = %if.then54
  br label %do.body60, !dbg !863

do.body60:                                        ; preds = %if.then59
  %85 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !864
  %flags61 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %85, i32 0, i32 7, !dbg !864
  %86 = load i32, i32* %flags61, align 8, !dbg !864
  %and62 = and i32 %86, 0, !dbg !864
  %cmp63 = icmp eq i32 %and62, 0, !dbg !864
  br i1 %cmp63, label %cond.true65, label %cond.false66, !dbg !864

cond.true65:                                      ; preds = %do.body60
  br label %cond.end67, !dbg !867

cond.false66:                                     ; preds = %do.body60
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 128, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__udp_run_completed, i32 0, i32 0)) #7, !dbg !869
  unreachable, !dbg !869
                                                  ; No predecessors!
  br label %cond.end67, !dbg !871

cond.end67:                                       ; preds = %87, %cond.true65
  %88 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !873
  %flags68 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %88, i32 0, i32 7, !dbg !873
  %89 = load i32, i32* %flags68, align 8, !dbg !873
  %and69 = and i32 %89, 16384, !dbg !873
  %cmp70 = icmp eq i32 %and69, 0, !dbg !873
  br i1 %cmp70, label %if.then72, label %if.end73, !dbg !873

if.then72:                                        ; preds = %cond.end67
  br label %do.end86, !dbg !876

if.end73:                                         ; preds = %cond.end67
  %90 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !878
  %flags74 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %90, i32 0, i32 7, !dbg !878
  %91 = load i32, i32* %flags74, align 8, !dbg !878
  %and75 = and i32 %91, -16385, !dbg !878
  store i32 %and75, i32* %flags74, align 8, !dbg !878
  %92 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !878
  %flags76 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %92, i32 0, i32 7, !dbg !878
  %93 = load i32, i32* %flags76, align 8, !dbg !878
  %and77 = and i32 %93, 8192, !dbg !878
  %cmp78 = icmp ne i32 %and77, 0, !dbg !878
  br i1 %cmp78, label %if.then80, label %if.end85, !dbg !878

if.then80:                                        ; preds = %if.end73
  br label %do.body81, !dbg !880

do.body81:                                        ; preds = %if.then80
  %94 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !883
  %loop82 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %94, i32 0, i32 1, !dbg !883
  %95 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop82, align 8, !dbg !883
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %95, i32 0, i32 1, !dbg !883
  %96 = load i32, i32* %active_handles, align 8, !dbg !883
  %dec83 = add i32 %96, -1, !dbg !883
  store i32 %dec83, i32* %active_handles, align 8, !dbg !883
  br label %do.end84, !dbg !883

do.end84:                                         ; preds = %do.body81
  br label %if.end85, !dbg !886

if.end85:                                         ; preds = %do.end84, %if.end73
  br label %do.end86, !dbg !888

do.end86:                                         ; preds = %if.end85, %if.then72
  br label %if.end87, !dbg !890

if.end87:                                         ; preds = %do.end86, %if.then54
  br label %if.end88, !dbg !892

if.end88:                                         ; preds = %if.end87, %while.end
  %97 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !893
  %flags89 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %97, i32 0, i32 7, !dbg !894
  %98 = load i32, i32* %flags89, align 8, !dbg !895
  %and90 = and i32 %98, -131073, !dbg !895
  store i32 %and90, i32* %flags89, align 8, !dbg !895
  ret void, !dbg !896
}

; Function Attrs: nounwind uwtable
define i32 @uv__udp_bind(%struct.uv_udp_s* %handle, %struct.sockaddr* %addr, i32 %addrlen, i32 %flags) #0 !dbg !573 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %yes = alloca i32, align 4
  %fd = alloca i32, align 4
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !897, metadata !653), !dbg !898
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !899, metadata !653), !dbg !900
  store i32 %addrlen, i32* %addrlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %addrlen.addr, metadata !901, metadata !653), !dbg !902
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !903, metadata !653), !dbg !904
  call void @llvm.dbg.declare(metadata i32* %err, metadata !905, metadata !653), !dbg !906
  call void @llvm.dbg.declare(metadata i32* %yes, metadata !907, metadata !653), !dbg !908
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !909, metadata !653), !dbg !910
  %0 = load i32, i32* %flags.addr, align 4, !dbg !911
  %and = and i32 %0, -6, !dbg !913
  %tobool = icmp ne i32 %and, 0, !dbg !913
  br i1 %tobool, label %if.then, label %if.end, !dbg !914

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !915
  br label %return, !dbg !915

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %flags.addr, align 4, !dbg !916
  %and1 = and i32 %1, 1, !dbg !918
  %tobool2 = icmp ne i32 %and1, 0, !dbg !918
  br i1 %tobool2, label %land.lhs.true, label %if.end5, !dbg !919

land.lhs.true:                                    ; preds = %if.end
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !920
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !922
  %3 = load i16, i16* %sa_family, align 2, !dbg !922
  %conv = zext i16 %3 to i32, !dbg !920
  %cmp = icmp ne i32 %conv, 10, !dbg !923
  br i1 %cmp, label %if.then4, label %if.end5, !dbg !924

if.then4:                                         ; preds = %land.lhs.true
  store i32 -22, i32* %retval, align 4, !dbg !925
  br label %return, !dbg !925

if.end5:                                          ; preds = %land.lhs.true, %if.end
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !926
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %4, i32 0, i32 12, !dbg !927
  %fd6 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !928
  %5 = load i32, i32* %fd6, align 8, !dbg !928
  store i32 %5, i32* %fd, align 4, !dbg !929
  %6 = load i32, i32* %fd, align 4, !dbg !930
  %cmp7 = icmp eq i32 %6, -1, !dbg !932
  br i1 %cmp7, label %if.then9, label %if.end18, !dbg !933

if.then9:                                         ; preds = %if.end5
  %7 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !934
  %sa_family10 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %7, i32 0, i32 0, !dbg !936
  %8 = load i16, i16* %sa_family10, align 2, !dbg !936
  %conv11 = zext i16 %8 to i32, !dbg !934
  %call = call i32 @uv__socket(i32 %conv11, i32 2, i32 0), !dbg !937
  store i32 %call, i32* %err, align 4, !dbg !938
  %9 = load i32, i32* %err, align 4, !dbg !939
  %cmp12 = icmp slt i32 %9, 0, !dbg !941
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !942

if.then14:                                        ; preds = %if.then9
  %10 = load i32, i32* %err, align 4, !dbg !943
  store i32 %10, i32* %retval, align 4, !dbg !944
  br label %return, !dbg !944

if.end15:                                         ; preds = %if.then9
  %11 = load i32, i32* %err, align 4, !dbg !945
  store i32 %11, i32* %fd, align 4, !dbg !946
  %12 = load i32, i32* %fd, align 4, !dbg !947
  %13 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !948
  %io_watcher16 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %13, i32 0, i32 12, !dbg !949
  %fd17 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher16, i32 0, i32 5, !dbg !950
  store i32 %12, i32* %fd17, align 8, !dbg !951
  br label %if.end18, !dbg !952

if.end18:                                         ; preds = %if.end15, %if.end5
  %14 = load i32, i32* %flags.addr, align 4, !dbg !953
  %and19 = and i32 %14, 4, !dbg !955
  %tobool20 = icmp ne i32 %and19, 0, !dbg !955
  br i1 %tobool20, label %if.then21, label %if.end26, !dbg !956

if.then21:                                        ; preds = %if.end18
  %15 = load i32, i32* %fd, align 4, !dbg !957
  %call22 = call i32 @uv__set_reuse(i32 %15), !dbg !959
  store i32 %call22, i32* %err, align 4, !dbg !960
  %16 = load i32, i32* %err, align 4, !dbg !961
  %tobool23 = icmp ne i32 %16, 0, !dbg !961
  br i1 %tobool23, label %if.then24, label %if.end25, !dbg !963

if.then24:                                        ; preds = %if.then21
  %17 = load i32, i32* %err, align 4, !dbg !964
  store i32 %17, i32* %retval, align 4, !dbg !965
  br label %return, !dbg !965

if.end25:                                         ; preds = %if.then21
  br label %if.end26, !dbg !966

if.end26:                                         ; preds = %if.end25, %if.end18
  %18 = load i32, i32* %flags.addr, align 4, !dbg !967
  %and27 = and i32 %18, 1, !dbg !969
  %tobool28 = icmp ne i32 %and27, 0, !dbg !969
  br i1 %tobool28, label %if.then29, label %if.end36, !dbg !970

if.then29:                                        ; preds = %if.end26
  store i32 1, i32* %yes, align 4, !dbg !971
  %19 = load i32, i32* %fd, align 4, !dbg !973
  %20 = bitcast i32* %yes to i8*, !dbg !975
  %call30 = call i32 @setsockopt(i32 %19, i32 41, i32 26, i8* %20, i32 4) #8, !dbg !976
  %cmp31 = icmp eq i32 %call30, -1, !dbg !977
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !978

if.then33:                                        ; preds = %if.then29
  %call34 = call i32* @__errno_location() #1, !dbg !979
  %21 = load i32, i32* %call34, align 4, !dbg !979
  %sub = sub nsw i32 0, %21, !dbg !981
  store i32 %sub, i32* %err, align 4, !dbg !982
  %22 = load i32, i32* %err, align 4, !dbg !983
  store i32 %22, i32* %retval, align 4, !dbg !984
  br label %return, !dbg !984

if.end35:                                         ; preds = %if.then29
  br label %if.end36, !dbg !985

if.end36:                                         ; preds = %if.end35, %if.end26
  %23 = load i32, i32* %fd, align 4, !dbg !986
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !988
  %24 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !988
  store %struct.sockaddr* %24, %struct.sockaddr** %__sockaddr__, align 8, !dbg !988
  %25 = load i32, i32* %addrlen.addr, align 4, !dbg !989
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !990
  %26 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !990
  %call37 = call i32 @bind(i32 %23, %struct.sockaddr* %26, i32 %25) #8, !dbg !990
  %tobool38 = icmp ne i32 %call37, 0, !dbg !990
  br i1 %tobool38, label %if.then39, label %if.end47, !dbg !991

if.then39:                                        ; preds = %if.end36
  %call40 = call i32* @__errno_location() #1, !dbg !992
  %27 = load i32, i32* %call40, align 4, !dbg !992
  %sub41 = sub nsw i32 0, %27, !dbg !994
  store i32 %sub41, i32* %err, align 4, !dbg !995
  %call42 = call i32* @__errno_location() #1, !dbg !996
  %28 = load i32, i32* %call42, align 4, !dbg !996
  %cmp43 = icmp eq i32 %28, 97, !dbg !998
  br i1 %cmp43, label %if.then45, label %if.end46, !dbg !999

if.then45:                                        ; preds = %if.then39
  store i32 -22, i32* %err, align 4, !dbg !1000
  br label %if.end46, !dbg !1001

if.end46:                                         ; preds = %if.then45, %if.then39
  %29 = load i32, i32* %err, align 4, !dbg !1002
  store i32 %29, i32* %retval, align 4, !dbg !1003
  br label %return, !dbg !1003

if.end47:                                         ; preds = %if.end36
  %30 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1004
  %sa_family48 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %30, i32 0, i32 0, !dbg !1006
  %31 = load i16, i16* %sa_family48, align 2, !dbg !1006
  %conv49 = zext i16 %31 to i32, !dbg !1004
  %cmp50 = icmp eq i32 %conv49, 10, !dbg !1007
  br i1 %cmp50, label %if.then52, label %if.end54, !dbg !1008

if.then52:                                        ; preds = %if.end47
  %32 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1009
  %flags53 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %32, i32 0, i32 7, !dbg !1010
  %33 = load i32, i32* %flags53, align 8, !dbg !1011
  %or = or i32 %33, 65536, !dbg !1011
  store i32 %or, i32* %flags53, align 8, !dbg !1011
  br label %if.end54, !dbg !1009

if.end54:                                         ; preds = %if.then52, %if.end47
  %34 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1012
  %flags55 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %34, i32 0, i32 7, !dbg !1013
  %35 = load i32, i32* %flags55, align 8, !dbg !1014
  %or56 = or i32 %35, 262144, !dbg !1014
  store i32 %or56, i32* %flags55, align 8, !dbg !1014
  store i32 0, i32* %retval, align 4, !dbg !1015
  br label %return, !dbg !1015

return:                                           ; preds = %if.end54, %if.end46, %if.then33, %if.then24, %if.then14, %if.then4, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !1016
  ret i32 %36, !dbg !1016
}

declare i32 @uv__socket(i32, i32, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__set_reuse(i32 %fd) #0 !dbg !620 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %yes = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1017, metadata !653), !dbg !1018
  call void @llvm.dbg.declare(metadata i32* %yes, metadata !1019, metadata !653), !dbg !1020
  store i32 1, i32* %yes, align 4, !dbg !1021
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1022
  %1 = bitcast i32* %yes to i8*, !dbg !1024
  %call = call i32 @setsockopt(i32 %0, i32 1, i32 2, i8* %1, i32 4) #8, !dbg !1025
  %tobool = icmp ne i32 %call, 0, !dbg !1025
  br i1 %tobool, label %if.then, label %if.end, !dbg !1026

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1027
  %2 = load i32, i32* %call1, align 4, !dbg !1027
  %sub = sub nsw i32 0, %2, !dbg !1028
  store i32 %sub, i32* %retval, align 4, !dbg !1029
  br label %return, !dbg !1029

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1030
  br label %return, !dbg !1030

return:                                           ; preds = %if.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !1031
  ret i32 %3, !dbg !1031
}

; Function Attrs: nounwind
declare i32 @setsockopt(i32, i32, i32, i8*, i32) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind
declare i32 @bind(i32, %struct.sockaddr*, i32) #4

; Function Attrs: nounwind uwtable
define i32 @uv__udp_send(%struct.uv_udp_send_s* %req, %struct.uv_udp_s* %handle, %struct.uv_buf_t* %bufs, i32 %nbufs, %struct.sockaddr* %addr, i32 %addrlen, void (%struct.uv_udp_send_s*, i32)* %send_cb) #0 !dbg !576 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_udp_send_s*, align 8
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen.addr = alloca i32, align 4
  %send_cb.addr = alloca void (%struct.uv_udp_send_s*, i32)*, align 8
  %err = alloca i32, align 4
  %empty_queue = alloca i32, align 4
  store %struct.uv_udp_send_s* %req, %struct.uv_udp_send_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_send_s** %req.addr, metadata !1032, metadata !653), !dbg !1033
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1034, metadata !653), !dbg !1035
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !1036, metadata !653), !dbg !1037
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !1038, metadata !653), !dbg !1039
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1040, metadata !653), !dbg !1041
  store i32 %addrlen, i32* %addrlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %addrlen.addr, metadata !1042, metadata !653), !dbg !1043
  store void (%struct.uv_udp_send_s*, i32)* %send_cb, void (%struct.uv_udp_send_s*, i32)** %send_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_udp_send_s*, i32)** %send_cb.addr, metadata !1044, metadata !653), !dbg !1045
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1046, metadata !653), !dbg !1047
  call void @llvm.dbg.declare(metadata i32* %empty_queue, metadata !1048, metadata !653), !dbg !1049
  %0 = load i32, i32* %nbufs.addr, align 4, !dbg !1050
  %cmp = icmp ugt i32 %0, 0, !dbg !1050
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1050

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1051

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 394, i8* getelementptr inbounds ([133 x i8], [133 x i8]* @__PRETTY_FUNCTION__.uv__udp_send, i32 0, i32 0)) #7, !dbg !1053
  unreachable, !dbg !1053
                                                  ; No predecessors!
  br label %cond.end, !dbg !1055

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1057
  %3 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1058
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %3, i32 0, i32 0, !dbg !1059
  %4 = load i16, i16* %sa_family, align 2, !dbg !1059
  %conv = zext i16 %4 to i32, !dbg !1058
  %call = call i32 @uv__udp_maybe_deferred_bind(%struct.uv_udp_s* %2, i32 %conv, i32 0), !dbg !1060
  store i32 %call, i32* %err, align 4, !dbg !1061
  %5 = load i32, i32* %err, align 4, !dbg !1062
  %tobool = icmp ne i32 %5, 0, !dbg !1062
  br i1 %tobool, label %if.then, label %if.end, !dbg !1064

if.then:                                          ; preds = %cond.end
  %6 = load i32, i32* %err, align 4, !dbg !1065
  store i32 %6, i32* %retval, align 4, !dbg !1066
  br label %return, !dbg !1066

if.end:                                           ; preds = %cond.end
  %7 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1067
  %send_queue_count = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %7, i32 0, i32 9, !dbg !1068
  %8 = load i64, i64* %send_queue_count, align 8, !dbg !1068
  %cmp1 = icmp eq i64 %8, 0, !dbg !1069
  %conv2 = zext i1 %cmp1 to i32, !dbg !1069
  store i32 %conv2, i32* %empty_queue, align 4, !dbg !1070
  br label %do.body, !dbg !1071

do.body:                                          ; preds = %if.end
  br label %do.body3, !dbg !1072

do.body3:                                         ; preds = %do.body
  %9 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1075
  %type = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %9, i32 0, i32 1, !dbg !1075
  store i32 5, i32* %type, align 8, !dbg !1075
  br label %do.end, !dbg !1075

do.end:                                           ; preds = %do.body3
  br label %do.body4, !dbg !1078

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1080

do.body5:                                         ; preds = %do.body4
  %10 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1083
  %loop = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %10, i32 0, i32 1, !dbg !1083
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1083
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 3, !dbg !1083
  %12 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1083
  %active_queue = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %12, i32 0, i32 2, !dbg !1083
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1083
  %13 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1083
  store [2 x i8*]* %active_reqs, [2 x i8*]** %13, align 8, !dbg !1083
  %14 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1083
  %loop6 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %14, i32 0, i32 1, !dbg !1083
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop6, align 8, !dbg !1083
  %active_reqs7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %15, i32 0, i32 3, !dbg !1083
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs7, i64 0, i64 1, !dbg !1083
  %16 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !1083
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !1083
  %18 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1083
  %active_queue9 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %18, i32 0, i32 2, !dbg !1083
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue9, i64 0, i64 1, !dbg !1083
  %19 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !1083
  store [2 x i8*]* %17, [2 x i8*]** %19, align 8, !dbg !1083
  %20 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1083
  %active_queue11 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %20, i32 0, i32 2, !dbg !1083
  %21 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1083
  %active_queue12 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %21, i32 0, i32 2, !dbg !1083
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue12, i64 0, i64 1, !dbg !1083
  %22 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1083
  %23 = load [2 x i8*]*, [2 x i8*]** %22, align 8, !dbg !1083
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %23, i64 0, i64 0, !dbg !1083
  %24 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !1083
  store [2 x i8*]* %active_queue11, [2 x i8*]** %24, align 8, !dbg !1083
  %25 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1083
  %active_queue15 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %25, i32 0, i32 2, !dbg !1083
  %26 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1083
  %loop16 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %26, i32 0, i32 1, !dbg !1083
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop16, align 8, !dbg !1083
  %active_reqs17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 3, !dbg !1083
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs17, i64 0, i64 1, !dbg !1083
  %28 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1083
  store [2 x i8*]* %active_queue15, [2 x i8*]** %28, align 8, !dbg !1083
  br label %do.end19, !dbg !1083

do.end19:                                         ; preds = %do.body5
  br label %do.end20, !dbg !1086

do.end20:                                         ; preds = %do.end19
  br label %do.end21, !dbg !1088

do.end21:                                         ; preds = %do.end20
  %29 = load i32, i32* %addrlen.addr, align 4, !dbg !1090
  %conv22 = zext i32 %29 to i64, !dbg !1090
  %cmp23 = icmp ule i64 %conv22, 128, !dbg !1090
  br i1 %cmp23, label %cond.true25, label %cond.false26, !dbg !1090

cond.true25:                                      ; preds = %do.end21
  br label %cond.end27, !dbg !1091

cond.false26:                                     ; preds = %do.end21
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 407, i8* getelementptr inbounds ([133 x i8], [133 x i8]* @__PRETTY_FUNCTION__.uv__udp_send, i32 0, i32 0)) #7, !dbg !1092
  unreachable, !dbg !1092
                                                  ; No predecessors!
  br label %cond.end27, !dbg !1093

cond.end27:                                       ; preds = %30, %cond.true25
  %31 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1094
  %addr28 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %31, i32 0, i32 7, !dbg !1095
  %32 = bitcast %struct.sockaddr_storage* %addr28 to i8*, !dbg !1096
  %33 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1097
  %34 = bitcast %struct.sockaddr* %33 to i8*, !dbg !1096
  %35 = load i32, i32* %addrlen.addr, align 4, !dbg !1098
  %conv29 = zext i32 %35 to i64, !dbg !1098
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %32, i8* %34, i64 %conv29, i32 2, i1 false), !dbg !1096
  %36 = load void (%struct.uv_udp_send_s*, i32)*, void (%struct.uv_udp_send_s*, i32)** %send_cb.addr, align 8, !dbg !1099
  %37 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1100
  %send_cb30 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %37, i32 0, i32 11, !dbg !1101
  store void (%struct.uv_udp_send_s*, i32)* %36, void (%struct.uv_udp_send_s*, i32)** %send_cb30, align 8, !dbg !1102
  %38 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1103
  %39 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1104
  %handle31 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %39, i32 0, i32 4, !dbg !1105
  store %struct.uv_udp_s* %38, %struct.uv_udp_s** %handle31, align 8, !dbg !1106
  %40 = load i32, i32* %nbufs.addr, align 4, !dbg !1107
  %41 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1108
  %nbufs32 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %41, i32 0, i32 8, !dbg !1109
  store i32 %40, i32* %nbufs32, align 8, !dbg !1110
  %42 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1111
  %bufsml = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %42, i32 0, i32 12, !dbg !1112
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !1111
  %43 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1113
  %bufs33 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %43, i32 0, i32 9, !dbg !1114
  store %struct.uv_buf_t* %arraydecay, %struct.uv_buf_t** %bufs33, align 8, !dbg !1115
  %44 = load i32, i32* %nbufs.addr, align 4, !dbg !1116
  %conv34 = zext i32 %44 to i64, !dbg !1116
  %cmp35 = icmp ugt i64 %conv34, 4, !dbg !1118
  br i1 %cmp35, label %if.then37, label %if.end41, !dbg !1119

if.then37:                                        ; preds = %cond.end27
  %45 = load i32, i32* %nbufs.addr, align 4, !dbg !1120
  %conv38 = zext i32 %45 to i64, !dbg !1120
  %mul = mul i64 %conv38, 16, !dbg !1121
  %call39 = call i8* @uv__malloc(i64 %mul), !dbg !1122
  %46 = bitcast i8* %call39 to %struct.uv_buf_t*, !dbg !1122
  %47 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1123
  %bufs40 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %47, i32 0, i32 9, !dbg !1124
  store %struct.uv_buf_t* %46, %struct.uv_buf_t** %bufs40, align 8, !dbg !1125
  br label %if.end41, !dbg !1123

if.end41:                                         ; preds = %if.then37, %cond.end27
  %48 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1126
  %bufs42 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %48, i32 0, i32 9, !dbg !1128
  %49 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs42, align 8, !dbg !1128
  %cmp43 = icmp eq %struct.uv_buf_t* %49, null, !dbg !1129
  br i1 %cmp43, label %if.then45, label %if.end72, !dbg !1130

if.then45:                                        ; preds = %if.end41
  br label %do.body46, !dbg !1131

do.body46:                                        ; preds = %if.then45
  %50 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1133
  %loop47 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %50, i32 0, i32 1, !dbg !1133
  %51 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop47, align 8, !dbg !1133
  %active_reqs48 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %51, i32 0, i32 3, !dbg !1133
  %52 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1133
  %loop49 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %52, i32 0, i32 1, !dbg !1133
  %53 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop49, align 8, !dbg !1133
  %active_reqs50 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %53, i32 0, i32 3, !dbg !1133
  %arrayidx51 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs50, i64 0, i64 0, !dbg !1133
  %54 = bitcast i8** %arrayidx51 to [2 x i8*]**, !dbg !1133
  %55 = load [2 x i8*]*, [2 x i8*]** %54, align 8, !dbg !1133
  %cmp52 = icmp eq [2 x i8*]* %active_reqs48, %55, !dbg !1133
  %conv53 = zext i1 %cmp52 to i32, !dbg !1133
  %cmp54 = icmp eq i32 %conv53, 0, !dbg !1133
  br i1 %cmp54, label %cond.true56, label %cond.false57, !dbg !1133

cond.true56:                                      ; preds = %do.body46
  br label %cond.end58, !dbg !1136

cond.false57:                                     ; preds = %do.body46
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 418, i8* getelementptr inbounds ([133 x i8], [133 x i8]* @__PRETTY_FUNCTION__.uv__udp_send, i32 0, i32 0)) #7, !dbg !1138
  unreachable, !dbg !1138
                                                  ; No predecessors!
  br label %cond.end58, !dbg !1140

cond.end58:                                       ; preds = %56, %cond.true56
  br label %do.body59, !dbg !1142

do.body59:                                        ; preds = %cond.end58
  %57 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1144
  %active_queue60 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %57, i32 0, i32 2, !dbg !1144
  %arrayidx61 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue60, i64 0, i64 0, !dbg !1144
  %58 = bitcast i8** %arrayidx61 to [2 x i8*]**, !dbg !1144
  %59 = load [2 x i8*]*, [2 x i8*]** %58, align 8, !dbg !1144
  %60 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1144
  %active_queue62 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %60, i32 0, i32 2, !dbg !1144
  %arrayidx63 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue62, i64 0, i64 1, !dbg !1144
  %61 = bitcast i8** %arrayidx63 to [2 x i8*]**, !dbg !1144
  %62 = load [2 x i8*]*, [2 x i8*]** %61, align 8, !dbg !1144
  %arrayidx64 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !1144
  %63 = bitcast i8** %arrayidx64 to [2 x i8*]**, !dbg !1144
  store [2 x i8*]* %59, [2 x i8*]** %63, align 8, !dbg !1144
  %64 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1144
  %active_queue65 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %64, i32 0, i32 2, !dbg !1144
  %arrayidx66 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue65, i64 0, i64 1, !dbg !1144
  %65 = bitcast i8** %arrayidx66 to [2 x i8*]**, !dbg !1144
  %66 = load [2 x i8*]*, [2 x i8*]** %65, align 8, !dbg !1144
  %67 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1144
  %active_queue67 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %67, i32 0, i32 2, !dbg !1144
  %arrayidx68 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue67, i64 0, i64 0, !dbg !1144
  %68 = bitcast i8** %arrayidx68 to [2 x i8*]**, !dbg !1144
  %69 = load [2 x i8*]*, [2 x i8*]** %68, align 8, !dbg !1144
  %arrayidx69 = getelementptr inbounds [2 x i8*], [2 x i8*]* %69, i64 0, i64 1, !dbg !1144
  %70 = bitcast i8** %arrayidx69 to [2 x i8*]**, !dbg !1144
  store [2 x i8*]* %66, [2 x i8*]** %70, align 8, !dbg !1144
  br label %do.end70, !dbg !1144

do.end70:                                         ; preds = %do.body59
  br label %do.end71, !dbg !1147

do.end71:                                         ; preds = %do.end70
  store i32 -12, i32* %retval, align 4, !dbg !1149
  br label %return, !dbg !1149

if.end72:                                         ; preds = %if.end41
  %71 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1150
  %bufs73 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %71, i32 0, i32 9, !dbg !1151
  %72 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs73, align 8, !dbg !1151
  %73 = bitcast %struct.uv_buf_t* %72 to i8*, !dbg !1152
  %74 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1153
  %75 = bitcast %struct.uv_buf_t* %74 to i8*, !dbg !1152
  %76 = load i32, i32* %nbufs.addr, align 4, !dbg !1154
  %conv74 = zext i32 %76 to i64, !dbg !1154
  %mul75 = mul i64 %conv74, 16, !dbg !1155
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %73, i8* %75, i64 %mul75, i32 8, i1 false), !dbg !1152
  %77 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1156
  %bufs76 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %77, i32 0, i32 9, !dbg !1157
  %78 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs76, align 8, !dbg !1157
  %79 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1158
  %nbufs77 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %79, i32 0, i32 8, !dbg !1159
  %80 = load i32, i32* %nbufs77, align 8, !dbg !1159
  %call78 = call i64 @uv__count_bufs(%struct.uv_buf_t* %78, i32 %80), !dbg !1160
  %81 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1161
  %send_queue_size = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %81, i32 0, i32 8, !dbg !1162
  %82 = load i64, i64* %send_queue_size, align 8, !dbg !1163
  %add = add i64 %82, %call78, !dbg !1163
  store i64 %add, i64* %send_queue_size, align 8, !dbg !1163
  %83 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1164
  %send_queue_count79 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %83, i32 0, i32 9, !dbg !1165
  %84 = load i64, i64* %send_queue_count79, align 8, !dbg !1166
  %inc = add i64 %84, 1, !dbg !1166
  store i64 %inc, i64* %send_queue_count79, align 8, !dbg !1166
  br label %do.body80, !dbg !1167

do.body80:                                        ; preds = %if.end72
  %85 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1168
  %write_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %85, i32 0, i32 13, !dbg !1168
  %86 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1168
  %queue = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %86, i32 0, i32 6, !dbg !1168
  %arrayidx81 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1168
  %87 = bitcast i8** %arrayidx81 to [2 x i8*]**, !dbg !1168
  store [2 x i8*]* %write_queue, [2 x i8*]** %87, align 8, !dbg !1168
  %88 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1168
  %write_queue82 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %88, i32 0, i32 13, !dbg !1168
  %arrayidx83 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue82, i64 0, i64 1, !dbg !1168
  %89 = bitcast i8** %arrayidx83 to [2 x i8*]**, !dbg !1168
  %90 = load [2 x i8*]*, [2 x i8*]** %89, align 8, !dbg !1168
  %91 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1168
  %queue84 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %91, i32 0, i32 6, !dbg !1168
  %arrayidx85 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue84, i64 0, i64 1, !dbg !1168
  %92 = bitcast i8** %arrayidx85 to [2 x i8*]**, !dbg !1168
  store [2 x i8*]* %90, [2 x i8*]** %92, align 8, !dbg !1168
  %93 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1168
  %queue86 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %93, i32 0, i32 6, !dbg !1168
  %94 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1168
  %queue87 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %94, i32 0, i32 6, !dbg !1168
  %arrayidx88 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue87, i64 0, i64 1, !dbg !1168
  %95 = bitcast i8** %arrayidx88 to [2 x i8*]**, !dbg !1168
  %96 = load [2 x i8*]*, [2 x i8*]** %95, align 8, !dbg !1168
  %arrayidx89 = getelementptr inbounds [2 x i8*], [2 x i8*]* %96, i64 0, i64 0, !dbg !1168
  %97 = bitcast i8** %arrayidx89 to [2 x i8*]**, !dbg !1168
  store [2 x i8*]* %queue86, [2 x i8*]** %97, align 8, !dbg !1168
  %98 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req.addr, align 8, !dbg !1168
  %queue90 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %98, i32 0, i32 6, !dbg !1168
  %99 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1168
  %write_queue91 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %99, i32 0, i32 13, !dbg !1168
  %arrayidx92 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue91, i64 0, i64 1, !dbg !1168
  %100 = bitcast i8** %arrayidx92 to [2 x i8*]**, !dbg !1168
  store [2 x i8*]* %queue90, [2 x i8*]** %100, align 8, !dbg !1168
  br label %do.end93, !dbg !1168

do.end93:                                         ; preds = %do.body80
  br label %do.body94, !dbg !1171

do.body94:                                        ; preds = %do.end93
  %101 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1172
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %101, i32 0, i32 7, !dbg !1172
  %102 = load i32, i32* %flags, align 8, !dbg !1172
  %and = and i32 %102, 0, !dbg !1172
  %cmp95 = icmp eq i32 %and, 0, !dbg !1172
  br i1 %cmp95, label %cond.true97, label %cond.false98, !dbg !1172

cond.true97:                                      ; preds = %do.body94
  br label %cond.end99, !dbg !1175

cond.false98:                                     ; preds = %do.body94
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 426, i8* getelementptr inbounds ([133 x i8], [133 x i8]* @__PRETTY_FUNCTION__.uv__udp_send, i32 0, i32 0)) #7, !dbg !1177
  unreachable, !dbg !1177
                                                  ; No predecessors!
  br label %cond.end99, !dbg !1179

cond.end99:                                       ; preds = %103, %cond.true97
  %104 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1181
  %flags100 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %104, i32 0, i32 7, !dbg !1181
  %105 = load i32, i32* %flags100, align 8, !dbg !1181
  %and101 = and i32 %105, 16384, !dbg !1181
  %cmp102 = icmp ne i32 %and101, 0, !dbg !1181
  br i1 %cmp102, label %if.then104, label %if.end105, !dbg !1181

if.then104:                                       ; preds = %cond.end99
  br label %do.end117, !dbg !1184

if.end105:                                        ; preds = %cond.end99
  %106 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1186
  %flags106 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %106, i32 0, i32 7, !dbg !1186
  %107 = load i32, i32* %flags106, align 8, !dbg !1186
  %or = or i32 %107, 16384, !dbg !1186
  store i32 %or, i32* %flags106, align 8, !dbg !1186
  %108 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1186
  %flags107 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %108, i32 0, i32 7, !dbg !1186
  %109 = load i32, i32* %flags107, align 8, !dbg !1186
  %and108 = and i32 %109, 8192, !dbg !1186
  %cmp109 = icmp ne i32 %and108, 0, !dbg !1186
  br i1 %cmp109, label %if.then111, label %if.end116, !dbg !1186

if.then111:                                       ; preds = %if.end105
  br label %do.body112, !dbg !1188

do.body112:                                       ; preds = %if.then111
  %110 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1191
  %loop113 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %110, i32 0, i32 1, !dbg !1191
  %111 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop113, align 8, !dbg !1191
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %111, i32 0, i32 1, !dbg !1191
  %112 = load i32, i32* %active_handles, align 8, !dbg !1191
  %inc114 = add i32 %112, 1, !dbg !1191
  store i32 %inc114, i32* %active_handles, align 8, !dbg !1191
  br label %do.end115, !dbg !1191

do.end115:                                        ; preds = %do.body112
  br label %if.end116, !dbg !1194

if.end116:                                        ; preds = %do.end115, %if.end105
  br label %do.end117, !dbg !1196

do.end117:                                        ; preds = %if.end116, %if.then104
  %113 = load i32, i32* %empty_queue, align 4, !dbg !1198
  %tobool118 = icmp ne i32 %113, 0, !dbg !1198
  br i1 %tobool118, label %land.lhs.true, label %if.else, !dbg !1200

land.lhs.true:                                    ; preds = %do.end117
  %114 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1201
  %flags119 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %114, i32 0, i32 7, !dbg !1203
  %115 = load i32, i32* %flags119, align 8, !dbg !1203
  %and120 = and i32 %115, 131072, !dbg !1204
  %tobool121 = icmp ne i32 %and120, 0, !dbg !1204
  br i1 %tobool121, label %if.else, label %if.then122, !dbg !1205

if.then122:                                       ; preds = %land.lhs.true
  %116 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1206
  call void @uv__udp_sendmsg(%struct.uv_udp_s* %116), !dbg !1208
  %117 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1209
  %write_queue123 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %117, i32 0, i32 13, !dbg !1209
  %118 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1209
  %write_queue124 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %118, i32 0, i32 13, !dbg !1209
  %arrayidx125 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue124, i64 0, i64 0, !dbg !1209
  %119 = bitcast i8** %arrayidx125 to [2 x i8*]**, !dbg !1209
  %120 = load [2 x i8*]*, [2 x i8*]** %119, align 8, !dbg !1209
  %cmp126 = icmp eq [2 x i8*]* %write_queue123, %120, !dbg !1209
  br i1 %cmp126, label %if.end130, label %if.then128, !dbg !1211

if.then128:                                       ; preds = %if.then122
  %121 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1212
  %loop129 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %121, i32 0, i32 1, !dbg !1213
  %122 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop129, align 8, !dbg !1213
  %123 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1214
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %123, i32 0, i32 12, !dbg !1215
  call void @uv__io_start(%struct.uv_loop_s* %122, %struct.uv__io_s* %io_watcher, i32 4), !dbg !1216
  br label %if.end130, !dbg !1216

if.end130:                                        ; preds = %if.then128, %if.then122
  br label %if.end133, !dbg !1217

if.else:                                          ; preds = %land.lhs.true, %do.end117
  %124 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1218
  %loop131 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %124, i32 0, i32 1, !dbg !1220
  %125 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop131, align 8, !dbg !1220
  %126 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1221
  %io_watcher132 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %126, i32 0, i32 12, !dbg !1222
  call void @uv__io_start(%struct.uv_loop_s* %125, %struct.uv__io_s* %io_watcher132, i32 4), !dbg !1223
  br label %if.end133

if.end133:                                        ; preds = %if.else, %if.end130
  store i32 0, i32* %retval, align 4, !dbg !1224
  br label %return, !dbg !1224

return:                                           ; preds = %if.end133, %do.end71, %if.then
  %127 = load i32, i32* %retval, align 4, !dbg !1225
  ret i32 %127, !dbg !1225
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__udp_maybe_deferred_bind(%struct.uv_udp_s* %handle, i32 %domain, i32 %flags) #0 !dbg !623 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %domain.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %taddr = alloca %union.anon.6, align 4
  %addrlen = alloca i32, align 4
  %addr = alloca %struct.sockaddr_in*, align 8
  %addr2 = alloca %struct.sockaddr_in6*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1226, metadata !653), !dbg !1227
  store i32 %domain, i32* %domain.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %domain.addr, metadata !1228, metadata !653), !dbg !1229
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1230, metadata !653), !dbg !1231
  call void @llvm.dbg.declare(metadata %union.anon.6* %taddr, metadata !1232, metadata !653), !dbg !1238
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !1239, metadata !653), !dbg !1240
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1241
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 12, !dbg !1243
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1244
  %1 = load i32, i32* %fd, align 8, !dbg !1244
  %cmp = icmp ne i32 %1, -1, !dbg !1245
  br i1 %cmp, label %if.then, label %if.end, !dbg !1246

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1247
  br label %return, !dbg !1247

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %domain.addr, align 4, !dbg !1248
  switch i32 %2, label %sw.default [
    i32 2, label %sw.bb
    i32 10, label %sw.bb1
  ], !dbg !1249

sw.bb:                                            ; preds = %if.end
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %addr, metadata !1250, metadata !653), !dbg !1253
  %in = bitcast %union.anon.6* %taddr to %struct.sockaddr_in*, !dbg !1254
  store %struct.sockaddr_in* %in, %struct.sockaddr_in** %addr, align 8, !dbg !1253
  %3 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr, align 8, !dbg !1255
  %4 = bitcast %struct.sockaddr_in* %3 to i8*, !dbg !1256
  call void @llvm.memset.p0i8.i64(i8* %4, i8 0, i64 16, i32 4, i1 false), !dbg !1256
  %5 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr, align 8, !dbg !1257
  %sin_family = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %5, i32 0, i32 0, !dbg !1258
  store i16 2, i16* %sin_family, align 4, !dbg !1259
  %6 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr, align 8, !dbg !1260
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %6, i32 0, i32 2, !dbg !1261
  %s_addr = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr, i32 0, i32 0, !dbg !1262
  store i32 0, i32* %s_addr, align 4, !dbg !1263
  store i32 16, i32* %addrlen, align 4, !dbg !1264
  br label %sw.epilog, !dbg !1265

sw.bb1:                                           ; preds = %if.end
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6** %addr2, metadata !1266, metadata !653), !dbg !1268
  %in6 = bitcast %union.anon.6* %taddr to %struct.sockaddr_in6*, !dbg !1269
  store %struct.sockaddr_in6* %in6, %struct.sockaddr_in6** %addr2, align 8, !dbg !1268
  %7 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr2, align 8, !dbg !1270
  %8 = bitcast %struct.sockaddr_in6* %7 to i8*, !dbg !1271
  call void @llvm.memset.p0i8.i64(i8* %8, i8 0, i64 28, i32 4, i1 false), !dbg !1271
  %9 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr2, align 8, !dbg !1272
  %sin6_family = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %9, i32 0, i32 0, !dbg !1273
  store i16 10, i16* %sin6_family, align 4, !dbg !1274
  %10 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr2, align 8, !dbg !1275
  %sin6_addr = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %10, i32 0, i32 3, !dbg !1276
  %11 = bitcast %struct.in6_addr* %sin6_addr to i8*, !dbg !1277
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* bitcast (%struct.in6_addr* @in6addr_any to i8*), i64 16, i32 4, i1 false), !dbg !1277
  store i32 28, i32* %addrlen, align 4, !dbg !1278
  br label %sw.epilog, !dbg !1279

sw.default:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 376, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @__PRETTY_FUNCTION__.uv__udp_maybe_deferred_bind, i32 0, i32 0)) #7, !dbg !1280
  unreachable, !dbg !1280

sw.epilog:                                        ; preds = %sw.bb1, %sw.bb
  %12 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1281
  %addr3 = bitcast %union.anon.6* %taddr to %struct.sockaddr*, !dbg !1282
  %13 = load i32, i32* %addrlen, align 4, !dbg !1283
  %14 = load i32, i32* %flags.addr, align 4, !dbg !1284
  %call = call i32 @uv__udp_bind(%struct.uv_udp_s* %12, %struct.sockaddr* %addr3, i32 %13, i32 %14), !dbg !1285
  store i32 %call, i32* %retval, align 4, !dbg !1286
  br label %return, !dbg !1286

return:                                           ; preds = %sw.epilog, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !1287
  ret i32 %15, !dbg !1287
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

declare i8* @uv__malloc(i64) #2

declare i64 @uv__count_bufs(%struct.uv_buf_t*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__udp_sendmsg(%struct.uv_udp_s* %handle) #0 !dbg !626 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %req = alloca %struct.uv_udp_send_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  %h = alloca %struct.msghdr, align 8
  %size = alloca i64, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1288, metadata !653), !dbg !1289
  call void @llvm.dbg.declare(metadata %struct.uv_udp_send_s** %req, metadata !1290, metadata !653), !dbg !1291
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1292, metadata !653), !dbg !1293
  call void @llvm.dbg.declare(metadata %struct.msghdr* %h, metadata !1294, metadata !653), !dbg !1304
  call void @llvm.dbg.declare(metadata i64* %size, metadata !1305, metadata !653), !dbg !1306
  br label %while.cond, !dbg !1307

while.cond:                                       ; preds = %do.end62, %entry
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1308
  %write_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 13, !dbg !1308
  %1 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1308
  %write_queue1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %1, i32 0, i32 13, !dbg !1308
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue1, i64 0, i64 0, !dbg !1308
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1308
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !1308
  %cmp = icmp eq [2 x i8*]* %write_queue, %3, !dbg !1308
  %lnot = xor i1 %cmp, true, !dbg !1310
  br i1 %lnot, label %while.body, label %while.end, !dbg !1311

while.body:                                       ; preds = %while.cond
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1312
  %write_queue2 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %4, i32 0, i32 13, !dbg !1312
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue2, i64 0, i64 0, !dbg !1312
  %5 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !1312
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !1312
  store [2 x i8*]* %6, [2 x i8*]** %q, align 8, !dbg !1314
  %7 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1315
  %cmp4 = icmp ne [2 x i8*]* %7, null, !dbg !1315
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !1315

cond.true:                                        ; preds = %while.body
  br label %cond.end, !dbg !1316

cond.false:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 224, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__udp_sendmsg, i32 0, i32 0)) #7, !dbg !1318
  unreachable, !dbg !1318
                                                  ; No predecessors!
  br label %cond.end, !dbg !1320

cond.end:                                         ; preds = %8, %cond.true
  %9 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1322
  %10 = bitcast [2 x i8*]* %9 to i8*, !dbg !1322
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 -80, !dbg !1322
  %11 = bitcast i8* %add.ptr to %struct.uv_udp_send_s*, !dbg !1322
  store %struct.uv_udp_send_s* %11, %struct.uv_udp_send_s** %req, align 8, !dbg !1323
  %12 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1324
  %cmp5 = icmp ne %struct.uv_udp_send_s* %12, null, !dbg !1324
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !1324

cond.true6:                                       ; preds = %cond.end
  br label %cond.end8, !dbg !1325

cond.false7:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 227, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__udp_sendmsg, i32 0, i32 0)) #7, !dbg !1326
  unreachable, !dbg !1326
                                                  ; No predecessors!
  br label %cond.end8, !dbg !1327

cond.end8:                                        ; preds = %13, %cond.true6
  %14 = bitcast %struct.msghdr* %h to i8*, !dbg !1328
  call void @llvm.memset.p0i8.i64(i8* %14, i8 0, i64 56, i32 8, i1 false), !dbg !1328
  %15 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1329
  %addr = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %15, i32 0, i32 7, !dbg !1330
  %16 = bitcast %struct.sockaddr_storage* %addr to i8*, !dbg !1331
  %msg_name = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 0, !dbg !1332
  store i8* %16, i8** %msg_name, align 8, !dbg !1333
  %17 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1334
  %addr9 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %17, i32 0, i32 7, !dbg !1335
  %ss_family = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %addr9, i32 0, i32 0, !dbg !1336
  %18 = load i16, i16* %ss_family, align 8, !dbg !1336
  %conv = zext i16 %18 to i32, !dbg !1334
  %cmp10 = icmp eq i32 %conv, 10, !dbg !1337
  %cond = select i1 %cmp10, i64 28, i64 16, !dbg !1334
  %conv12 = trunc i64 %cond to i32, !dbg !1338
  %msg_namelen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 1, !dbg !1339
  store i32 %conv12, i32* %msg_namelen, align 8, !dbg !1340
  %19 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1341
  %bufs = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %19, i32 0, i32 9, !dbg !1342
  %20 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !1342
  %21 = bitcast %struct.uv_buf_t* %20 to %struct.iovec*, !dbg !1343
  %msg_iov = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 2, !dbg !1344
  store %struct.iovec* %21, %struct.iovec** %msg_iov, align 8, !dbg !1345
  %22 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1346
  %nbufs = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %22, i32 0, i32 8, !dbg !1347
  %23 = load i32, i32* %nbufs, align 8, !dbg !1347
  %conv13 = zext i32 %23 to i64, !dbg !1346
  %msg_iovlen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 3, !dbg !1348
  store i64 %conv13, i64* %msg_iovlen, align 8, !dbg !1349
  br label %do.body, !dbg !1350

do.body:                                          ; preds = %land.end, %cond.end8
  %24 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1351
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %24, i32 0, i32 12, !dbg !1353
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1354
  %25 = load i32, i32* %fd, align 8, !dbg !1354
  %call = call i64 @sendmsg(i32 %25, %struct.msghdr* %h, i32 0), !dbg !1355
  store i64 %call, i64* %size, align 8, !dbg !1356
  br label %do.cond, !dbg !1357

do.cond:                                          ; preds = %do.body
  %26 = load i64, i64* %size, align 8, !dbg !1358
  %cmp14 = icmp eq i64 %26, -1, !dbg !1359
  br i1 %cmp14, label %land.rhs, label %land.end, !dbg !1360

land.rhs:                                         ; preds = %do.cond
  %call16 = call i32* @__errno_location() #1, !dbg !1361
  %27 = load i32, i32* %call16, align 4, !dbg !1361
  %cmp17 = icmp eq i32 %27, 4, !dbg !1362
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %28 = phi i1 [ false, %do.cond ], [ %cmp17, %land.rhs ]
  br i1 %28, label %do.body, label %do.end, !dbg !1363

do.end:                                           ; preds = %land.end
  %29 = load i64, i64* %size, align 8, !dbg !1365
  %cmp19 = icmp eq i64 %29, -1, !dbg !1367
  br i1 %cmp19, label %land.lhs.true, label %if.end, !dbg !1368

land.lhs.true:                                    ; preds = %do.end
  %call21 = call i32* @__errno_location() #1, !dbg !1369
  %30 = load i32, i32* %call21, align 4, !dbg !1369
  %cmp22 = icmp eq i32 %30, 11, !dbg !1371
  br i1 %cmp22, label %if.then, label %lor.lhs.false, !dbg !1372

lor.lhs.false:                                    ; preds = %land.lhs.true
  %call24 = call i32* @__errno_location() #1, !dbg !1373
  %31 = load i32, i32* %call24, align 4, !dbg !1373
  %cmp25 = icmp eq i32 %31, 11, !dbg !1375
  br i1 %cmp25, label %if.then, label %if.end, !dbg !1376

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  br label %while.end, !dbg !1377

if.end:                                           ; preds = %lor.lhs.false, %do.end
  %32 = load i64, i64* %size, align 8, !dbg !1378
  %cmp27 = icmp eq i64 %32, -1, !dbg !1379
  br i1 %cmp27, label %cond.true29, label %cond.false32, !dbg !1378

cond.true29:                                      ; preds = %if.end
  %call30 = call i32* @__errno_location() #1, !dbg !1380
  %33 = load i32, i32* %call30, align 4, !dbg !1380
  %sub = sub nsw i32 0, %33, !dbg !1381
  %conv31 = sext i32 %sub to i64, !dbg !1381
  br label %cond.end33, !dbg !1382

cond.false32:                                     ; preds = %if.end
  %34 = load i64, i64* %size, align 8, !dbg !1383
  br label %cond.end33, !dbg !1384

cond.end33:                                       ; preds = %cond.false32, %cond.true29
  %cond34 = phi i64 [ %conv31, %cond.true29 ], [ %34, %cond.false32 ], !dbg !1385
  %35 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1386
  %status = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %35, i32 0, i32 10, !dbg !1387
  store i64 %cond34, i64* %status, align 8, !dbg !1388
  br label %do.body35, !dbg !1389

do.body35:                                        ; preds = %cond.end33
  %36 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1390
  %queue = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %36, i32 0, i32 6, !dbg !1390
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1390
  %37 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !1390
  %38 = load [2 x i8*]*, [2 x i8*]** %37, align 8, !dbg !1390
  %39 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1390
  %queue37 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %39, i32 0, i32 6, !dbg !1390
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue37, i64 0, i64 1, !dbg !1390
  %40 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1390
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 8, !dbg !1390
  %arrayidx39 = getelementptr inbounds [2 x i8*], [2 x i8*]* %41, i64 0, i64 0, !dbg !1390
  %42 = bitcast i8** %arrayidx39 to [2 x i8*]**, !dbg !1390
  store [2 x i8*]* %38, [2 x i8*]** %42, align 8, !dbg !1390
  %43 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1390
  %queue40 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %43, i32 0, i32 6, !dbg !1390
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue40, i64 0, i64 1, !dbg !1390
  %44 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !1390
  %45 = load [2 x i8*]*, [2 x i8*]** %44, align 8, !dbg !1390
  %46 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1390
  %queue42 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %46, i32 0, i32 6, !dbg !1390
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue42, i64 0, i64 0, !dbg !1390
  %47 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !1390
  %48 = load [2 x i8*]*, [2 x i8*]** %47, align 8, !dbg !1390
  %arrayidx44 = getelementptr inbounds [2 x i8*], [2 x i8*]* %48, i64 0, i64 1, !dbg !1390
  %49 = bitcast i8** %arrayidx44 to [2 x i8*]**, !dbg !1390
  store [2 x i8*]* %45, [2 x i8*]** %49, align 8, !dbg !1390
  br label %do.end46, !dbg !1390

do.end46:                                         ; preds = %do.body35
  br label %do.body47, !dbg !1393

do.body47:                                        ; preds = %do.end46
  %50 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1394
  %write_completed_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %50, i32 0, i32 14, !dbg !1394
  %51 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1394
  %queue48 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %51, i32 0, i32 6, !dbg !1394
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue48, i64 0, i64 0, !dbg !1394
  %52 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %write_completed_queue, [2 x i8*]** %52, align 8, !dbg !1394
  %53 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1394
  %write_completed_queue50 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %53, i32 0, i32 14, !dbg !1394
  %arrayidx51 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue50, i64 0, i64 1, !dbg !1394
  %54 = bitcast i8** %arrayidx51 to [2 x i8*]**, !dbg !1394
  %55 = load [2 x i8*]*, [2 x i8*]** %54, align 8, !dbg !1394
  %56 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1394
  %queue52 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %56, i32 0, i32 6, !dbg !1394
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue52, i64 0, i64 1, !dbg !1394
  %57 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %55, [2 x i8*]** %57, align 8, !dbg !1394
  %58 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1394
  %queue54 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %58, i32 0, i32 6, !dbg !1394
  %59 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1394
  %queue55 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %59, i32 0, i32 6, !dbg !1394
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue55, i64 0, i64 1, !dbg !1394
  %60 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !1394
  %61 = load [2 x i8*]*, [2 x i8*]** %60, align 8, !dbg !1394
  %arrayidx57 = getelementptr inbounds [2 x i8*], [2 x i8*]* %61, i64 0, i64 0, !dbg !1394
  %62 = bitcast i8** %arrayidx57 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %queue54, [2 x i8*]** %62, align 8, !dbg !1394
  %63 = load %struct.uv_udp_send_s*, %struct.uv_udp_send_s** %req, align 8, !dbg !1394
  %queue58 = getelementptr inbounds %struct.uv_udp_send_s, %struct.uv_udp_send_s* %63, i32 0, i32 6, !dbg !1394
  %64 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1394
  %write_completed_queue59 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %64, i32 0, i32 14, !dbg !1394
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue59, i64 0, i64 1, !dbg !1394
  %65 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %queue58, [2 x i8*]** %65, align 8, !dbg !1394
  br label %do.end62, !dbg !1394

do.end62:                                         ; preds = %do.body47
  %66 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1397
  %loop = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %66, i32 0, i32 1, !dbg !1398
  %67 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1398
  %68 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1399
  %io_watcher63 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %68, i32 0, i32 12, !dbg !1400
  call void @uv__io_feed(%struct.uv_loop_s* %67, %struct.uv__io_s* %io_watcher63), !dbg !1401
  br label %while.cond, !dbg !1402

while.end:                                        ; preds = %if.then, %while.cond
  ret void, !dbg !1404
}

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv__udp_try_send(%struct.uv_udp_s* %handle, %struct.uv_buf_t* %bufs, i32 %nbufs, %struct.sockaddr* %addr, i32 %addrlen) #0 !dbg !579 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %h = alloca %struct.msghdr, align 8
  %size = alloca i64, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1405, metadata !653), !dbg !1406
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !1407, metadata !653), !dbg !1408
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !1409, metadata !653), !dbg !1410
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !1411, metadata !653), !dbg !1412
  store i32 %addrlen, i32* %addrlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %addrlen.addr, metadata !1413, metadata !653), !dbg !1414
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1415, metadata !653), !dbg !1416
  call void @llvm.dbg.declare(metadata %struct.msghdr* %h, metadata !1417, metadata !653), !dbg !1418
  call void @llvm.dbg.declare(metadata i64* %size, metadata !1419, metadata !653), !dbg !1420
  %0 = load i32, i32* %nbufs.addr, align 4, !dbg !1421
  %cmp = icmp ugt i32 %0, 0, !dbg !1421
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1421

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1422

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 454, i8* getelementptr inbounds ([104 x i8], [104 x i8]* @__PRETTY_FUNCTION__.uv__udp_try_send, i32 0, i32 0)) #7, !dbg !1424
  unreachable, !dbg !1424
                                                  ; No predecessors!
  br label %cond.end, !dbg !1426

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1428
  %send_queue_count = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %2, i32 0, i32 9, !dbg !1430
  %3 = load i64, i64* %send_queue_count, align 8, !dbg !1430
  %cmp1 = icmp ne i64 %3, 0, !dbg !1431
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1432

if.then:                                          ; preds = %cond.end
  store i32 -11, i32* %retval, align 4, !dbg !1433
  br label %return, !dbg !1433

if.end:                                           ; preds = %cond.end
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1434
  %5 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1435
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %5, i32 0, i32 0, !dbg !1436
  %6 = load i16, i16* %sa_family, align 2, !dbg !1436
  %conv = zext i16 %6 to i32, !dbg !1435
  %call = call i32 @uv__udp_maybe_deferred_bind(%struct.uv_udp_s* %4, i32 %conv, i32 0), !dbg !1437
  store i32 %call, i32* %err, align 4, !dbg !1438
  %7 = load i32, i32* %err, align 4, !dbg !1439
  %tobool = icmp ne i32 %7, 0, !dbg !1439
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !1441

if.then2:                                         ; preds = %if.end
  %8 = load i32, i32* %err, align 4, !dbg !1442
  store i32 %8, i32* %retval, align 4, !dbg !1443
  br label %return, !dbg !1443

if.end3:                                          ; preds = %if.end
  %9 = bitcast %struct.msghdr* %h to i8*, !dbg !1444
  call void @llvm.memset.p0i8.i64(i8* %9, i8 0, i64 56, i32 8, i1 false), !dbg !1444
  %10 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !1445
  %11 = bitcast %struct.sockaddr* %10 to i8*, !dbg !1446
  %msg_name = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 0, !dbg !1447
  store i8* %11, i8** %msg_name, align 8, !dbg !1448
  %12 = load i32, i32* %addrlen.addr, align 4, !dbg !1449
  %msg_namelen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 1, !dbg !1450
  store i32 %12, i32* %msg_namelen, align 8, !dbg !1451
  %13 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1452
  %14 = bitcast %struct.uv_buf_t* %13 to %struct.iovec*, !dbg !1453
  %msg_iov = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 2, !dbg !1454
  store %struct.iovec* %14, %struct.iovec** %msg_iov, align 8, !dbg !1455
  %15 = load i32, i32* %nbufs.addr, align 4, !dbg !1456
  %conv4 = zext i32 %15 to i64, !dbg !1456
  %msg_iovlen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 3, !dbg !1457
  store i64 %conv4, i64* %msg_iovlen, align 8, !dbg !1458
  br label %do.body, !dbg !1459

do.body:                                          ; preds = %land.end, %if.end3
  %16 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1460
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %16, i32 0, i32 12, !dbg !1462
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1463
  %17 = load i32, i32* %fd, align 8, !dbg !1463
  %call5 = call i64 @sendmsg(i32 %17, %struct.msghdr* %h, i32 0), !dbg !1464
  store i64 %call5, i64* %size, align 8, !dbg !1465
  br label %do.cond, !dbg !1466

do.cond:                                          ; preds = %do.body
  %18 = load i64, i64* %size, align 8, !dbg !1467
  %cmp6 = icmp eq i64 %18, -1, !dbg !1468
  br i1 %cmp6, label %land.rhs, label %land.end, !dbg !1469

land.rhs:                                         ; preds = %do.cond
  %call8 = call i32* @__errno_location() #1, !dbg !1470
  %19 = load i32, i32* %call8, align 4, !dbg !1470
  %cmp9 = icmp eq i32 %19, 4, !dbg !1471
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %20 = phi i1 [ false, %do.cond ], [ %cmp9, %land.rhs ]
  br i1 %20, label %do.body, label %do.end, !dbg !1472

do.end:                                           ; preds = %land.end
  %21 = load i64, i64* %size, align 8, !dbg !1474
  %cmp11 = icmp eq i64 %21, -1, !dbg !1476
  br i1 %cmp11, label %if.then13, label %if.end22, !dbg !1477

if.then13:                                        ; preds = %do.end
  %call14 = call i32* @__errno_location() #1, !dbg !1478
  %22 = load i32, i32* %call14, align 4, !dbg !1478
  %cmp15 = icmp eq i32 %22, 11, !dbg !1481
  br i1 %cmp15, label %if.then20, label %lor.lhs.false, !dbg !1482

lor.lhs.false:                                    ; preds = %if.then13
  %call17 = call i32* @__errno_location() #1, !dbg !1483
  %23 = load i32, i32* %call17, align 4, !dbg !1483
  %cmp18 = icmp eq i32 %23, 11, !dbg !1485
  br i1 %cmp18, label %if.then20, label %if.else, !dbg !1486

if.then20:                                        ; preds = %lor.lhs.false, %if.then13
  store i32 -11, i32* %retval, align 4, !dbg !1487
  br label %return, !dbg !1487

if.else:                                          ; preds = %lor.lhs.false
  %call21 = call i32* @__errno_location() #1, !dbg !1488
  %24 = load i32, i32* %call21, align 4, !dbg !1488
  %sub = sub nsw i32 0, %24, !dbg !1489
  store i32 %sub, i32* %retval, align 4, !dbg !1490
  br label %return, !dbg !1490

if.end22:                                         ; preds = %do.end
  %25 = load i64, i64* %size, align 8, !dbg !1491
  %conv23 = trunc i64 %25 to i32, !dbg !1491
  store i32 %conv23, i32* %retval, align 4, !dbg !1492
  br label %return, !dbg !1492

return:                                           ; preds = %if.end22, %if.else, %if.then20, %if.then2, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !1493
  ret i32 %26, !dbg !1493
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

declare i64 @sendmsg(i32, %struct.msghdr*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv_udp_init_ex(%struct.uv_loop_s* %loop, %struct.uv_udp_s* %handle, i32 %flags) #0 !dbg !582 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %flags.addr = alloca i32, align 4
  %domain = alloca i32, align 4
  %err = alloca i32, align 4
  %fd = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1494, metadata !653), !dbg !1495
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1496, metadata !653), !dbg !1497
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1498, metadata !653), !dbg !1499
  call void @llvm.dbg.declare(metadata i32* %domain, metadata !1500, metadata !653), !dbg !1501
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1502, metadata !653), !dbg !1503
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1504, metadata !653), !dbg !1505
  %0 = load i32, i32* %flags.addr, align 4, !dbg !1506
  %and = and i32 %0, 255, !dbg !1507
  store i32 %and, i32* %domain, align 4, !dbg !1508
  %1 = load i32, i32* %domain, align 4, !dbg !1509
  %cmp = icmp ne i32 %1, 2, !dbg !1511
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !1512

land.lhs.true:                                    ; preds = %entry
  %2 = load i32, i32* %domain, align 4, !dbg !1513
  %cmp1 = icmp ne i32 %2, 10, !dbg !1515
  br i1 %cmp1, label %land.lhs.true2, label %if.end, !dbg !1516

land.lhs.true2:                                   ; preds = %land.lhs.true
  %3 = load i32, i32* %domain, align 4, !dbg !1517
  %cmp3 = icmp ne i32 %3, 0, !dbg !1519
  br i1 %cmp3, label %if.then, label %if.end, !dbg !1520

if.then:                                          ; preds = %land.lhs.true2
  store i32 -22, i32* %retval, align 4, !dbg !1521
  br label %return, !dbg !1521

if.end:                                           ; preds = %land.lhs.true2, %land.lhs.true, %entry
  %4 = load i32, i32* %flags.addr, align 4, !dbg !1522
  %and4 = and i32 %4, -256, !dbg !1524
  %tobool = icmp ne i32 %and4, 0, !dbg !1524
  br i1 %tobool, label %if.then5, label %if.end6, !dbg !1525

if.then5:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !1526
  br label %return, !dbg !1526

if.end6:                                          ; preds = %if.end
  %5 = load i32, i32* %domain, align 4, !dbg !1527
  %cmp7 = icmp ne i32 %5, 0, !dbg !1529
  br i1 %cmp7, label %if.then8, label %if.else, !dbg !1530

if.then8:                                         ; preds = %if.end6
  %6 = load i32, i32* %domain, align 4, !dbg !1531
  %call = call i32 @uv__socket(i32 %6, i32 2, i32 0), !dbg !1533
  store i32 %call, i32* %err, align 4, !dbg !1534
  %7 = load i32, i32* %err, align 4, !dbg !1535
  %cmp9 = icmp slt i32 %7, 0, !dbg !1537
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !1538

if.then10:                                        ; preds = %if.then8
  %8 = load i32, i32* %err, align 4, !dbg !1539
  store i32 %8, i32* %retval, align 4, !dbg !1540
  br label %return, !dbg !1540

if.end11:                                         ; preds = %if.then8
  %9 = load i32, i32* %err, align 4, !dbg !1541
  store i32 %9, i32* %fd, align 4, !dbg !1542
  br label %if.end12, !dbg !1543

if.else:                                          ; preds = %if.end6
  store i32 -1, i32* %fd, align 4, !dbg !1544
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.end11
  br label %do.body, !dbg !1546

do.body:                                          ; preds = %if.end12
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1547
  %11 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1547
  %12 = bitcast %struct.uv_udp_s* %11 to %struct.uv_handle_s*, !dbg !1547
  %loop13 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %12, i32 0, i32 1, !dbg !1547
  store %struct.uv_loop_s* %10, %struct.uv_loop_s** %loop13, align 8, !dbg !1547
  %13 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1547
  %14 = bitcast %struct.uv_udp_s* %13 to %struct.uv_handle_s*, !dbg !1547
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %14, i32 0, i32 2, !dbg !1547
  store i32 15, i32* %type, align 8, !dbg !1547
  %15 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1547
  %16 = bitcast %struct.uv_udp_s* %15 to %struct.uv_handle_s*, !dbg !1547
  %flags14 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %16, i32 0, i32 7, !dbg !1547
  store i32 8192, i32* %flags14, align 8, !dbg !1547
  br label %do.body15, !dbg !1547

do.body15:                                        ; preds = %do.body
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1550
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 2, !dbg !1550
  %18 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1550
  %19 = bitcast %struct.uv_udp_s* %18 to %struct.uv_handle_s*, !dbg !1550
  %handle_queue16 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %19, i32 0, i32 4, !dbg !1550
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue16, i64 0, i64 0, !dbg !1550
  %20 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1550
  store [2 x i8*]* %handle_queue, [2 x i8*]** %20, align 8, !dbg !1550
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1550
  %handle_queue17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 2, !dbg !1550
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue17, i64 0, i64 1, !dbg !1550
  %22 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1550
  %23 = load [2 x i8*]*, [2 x i8*]** %22, align 8, !dbg !1550
  %24 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1550
  %25 = bitcast %struct.uv_udp_s* %24 to %struct.uv_handle_s*, !dbg !1550
  %handle_queue19 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !1550
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue19, i64 0, i64 1, !dbg !1550
  %26 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !1550
  store [2 x i8*]* %23, [2 x i8*]** %26, align 8, !dbg !1550
  %27 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1550
  %28 = bitcast %struct.uv_udp_s* %27 to %struct.uv_handle_s*, !dbg !1550
  %handle_queue21 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %28, i32 0, i32 4, !dbg !1550
  %29 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1550
  %30 = bitcast %struct.uv_udp_s* %29 to %struct.uv_handle_s*, !dbg !1550
  %handle_queue22 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %30, i32 0, i32 4, !dbg !1550
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue22, i64 0, i64 1, !dbg !1550
  %31 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !1550
  %32 = load [2 x i8*]*, [2 x i8*]** %31, align 8, !dbg !1550
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %32, i64 0, i64 0, !dbg !1550
  %33 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !1550
  store [2 x i8*]* %handle_queue21, [2 x i8*]** %33, align 8, !dbg !1550
  %34 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1550
  %35 = bitcast %struct.uv_udp_s* %34 to %struct.uv_handle_s*, !dbg !1550
  %handle_queue25 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %35, i32 0, i32 4, !dbg !1550
  %36 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1550
  %handle_queue26 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %36, i32 0, i32 2, !dbg !1550
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue26, i64 0, i64 1, !dbg !1550
  %37 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !1550
  store [2 x i8*]* %handle_queue25, [2 x i8*]** %37, align 8, !dbg !1550
  br label %do.end, !dbg !1550

do.end:                                           ; preds = %do.body15
  %38 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1553
  %39 = bitcast %struct.uv_udp_s* %38 to %struct.uv_handle_s*, !dbg !1553
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %39, i32 0, i32 6, !dbg !1553
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !1553
  br label %do.end28, !dbg !1553

do.end28:                                         ; preds = %do.end
  %40 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1555
  %alloc_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %40, i32 0, i32 10, !dbg !1556
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !1557
  %41 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1558
  %recv_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %41, i32 0, i32 11, !dbg !1559
  store void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* null, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb, align 8, !dbg !1560
  %42 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1561
  %send_queue_size = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %42, i32 0, i32 8, !dbg !1562
  store i64 0, i64* %send_queue_size, align 8, !dbg !1563
  %43 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1564
  %send_queue_count = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %43, i32 0, i32 9, !dbg !1565
  store i64 0, i64* %send_queue_count, align 8, !dbg !1566
  %44 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1567
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %44, i32 0, i32 12, !dbg !1568
  %45 = load i32, i32* %fd, align 4, !dbg !1569
  call void @uv__io_init(%struct.uv__io_s* %io_watcher, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__udp_io, i32 %45), !dbg !1570
  br label %do.body29, !dbg !1571

do.body29:                                        ; preds = %do.end28
  %46 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1572
  %write_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %46, i32 0, i32 13, !dbg !1572
  %47 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1572
  %write_queue30 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %47, i32 0, i32 13, !dbg !1572
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue30, i64 0, i64 0, !dbg !1572
  %48 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !1572
  store [2 x i8*]* %write_queue, [2 x i8*]** %48, align 8, !dbg !1572
  %49 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1572
  %write_queue32 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %49, i32 0, i32 13, !dbg !1572
  %50 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1572
  %write_queue33 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %50, i32 0, i32 13, !dbg !1572
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue33, i64 0, i64 1, !dbg !1572
  %51 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !1572
  store [2 x i8*]* %write_queue32, [2 x i8*]** %51, align 8, !dbg !1572
  br label %do.end35, !dbg !1572

do.end35:                                         ; preds = %do.body29
  br label %do.body36, !dbg !1575

do.body36:                                        ; preds = %do.end35
  %52 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1576
  %write_completed_queue = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %52, i32 0, i32 14, !dbg !1576
  %53 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1576
  %write_completed_queue37 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %53, i32 0, i32 14, !dbg !1576
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue37, i64 0, i64 0, !dbg !1576
  %54 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1576
  store [2 x i8*]* %write_completed_queue, [2 x i8*]** %54, align 8, !dbg !1576
  %55 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1576
  %write_completed_queue39 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %55, i32 0, i32 14, !dbg !1576
  %56 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1576
  %write_completed_queue40 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %56, i32 0, i32 14, !dbg !1576
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue40, i64 0, i64 1, !dbg !1576
  %57 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !1576
  store [2 x i8*]* %write_completed_queue39, [2 x i8*]** %57, align 8, !dbg !1576
  br label %do.end42, !dbg !1576

do.end42:                                         ; preds = %do.body36
  store i32 0, i32* %retval, align 4, !dbg !1579
  br label %return, !dbg !1579

return:                                           ; preds = %do.end42, %if.then10, %if.then5, %if.then
  %58 = load i32, i32* %retval, align 4, !dbg !1580
  ret i32 %58, !dbg !1580
}

declare void @uv__io_init(%struct.uv__io_s*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__udp_io(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %revents) #0 !dbg !627 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %revents.addr = alloca i32, align 4
  %handle = alloca %struct.uv_udp_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1581, metadata !653), !dbg !1582
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !1583, metadata !653), !dbg !1584
  store i32 %revents, i32* %revents.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %revents.addr, metadata !1585, metadata !653), !dbg !1586
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle, metadata !1587, metadata !653), !dbg !1588
  %0 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !1589
  %1 = bitcast %struct.uv__io_s* %0 to i8*, !dbg !1589
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -128, !dbg !1589
  %2 = bitcast i8* %add.ptr to %struct.uv_udp_s*, !dbg !1589
  store %struct.uv_udp_s* %2, %struct.uv_udp_s** %handle, align 8, !dbg !1590
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle, align 8, !dbg !1591
  %type = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %3, i32 0, i32 2, !dbg !1591
  %4 = load i32, i32* %type, align 8, !dbg !1591
  %cmp = icmp eq i32 %4, 15, !dbg !1591
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1591

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1592

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 139, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @__PRETTY_FUNCTION__.uv__udp_io, i32 0, i32 0)) #7, !dbg !1594
  unreachable, !dbg !1594
                                                  ; No predecessors!
  br label %cond.end, !dbg !1596

cond.end:                                         ; preds = %5, %cond.true
  %6 = load i32, i32* %revents.addr, align 4, !dbg !1598
  %and = and i32 %6, 1, !dbg !1600
  %tobool = icmp ne i32 %and, 0, !dbg !1600
  br i1 %tobool, label %if.then, label %if.end, !dbg !1601

if.then:                                          ; preds = %cond.end
  %7 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle, align 8, !dbg !1602
  call void @uv__udp_recvmsg(%struct.uv_udp_s* %7), !dbg !1603
  br label %if.end, !dbg !1603

if.end:                                           ; preds = %if.then, %cond.end
  %8 = load i32, i32* %revents.addr, align 4, !dbg !1604
  %and1 = and i32 %8, 4, !dbg !1606
  %tobool2 = icmp ne i32 %and1, 0, !dbg !1606
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !1607

if.then3:                                         ; preds = %if.end
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle, align 8, !dbg !1608
  call void @uv__udp_sendmsg(%struct.uv_udp_s* %9), !dbg !1610
  %10 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle, align 8, !dbg !1611
  call void @uv__udp_run_completed(%struct.uv_udp_s* %10), !dbg !1612
  br label %if.end4, !dbg !1613

if.end4:                                          ; preds = %if.then3, %if.end
  ret void, !dbg !1614
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_init(%struct.uv_loop_s* %loop, %struct.uv_udp_s* %handle) #0 !dbg !585 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1615, metadata !653), !dbg !1616
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1617, metadata !653), !dbg !1618
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1619
  %1 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1620
  %call = call i32 @uv_udp_init_ex(%struct.uv_loop_s* %0, %struct.uv_udp_s* %1, i32 0), !dbg !1621
  ret i32 %call, !dbg !1622
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_open(%struct.uv_udp_s* %handle, i32 %sock) #0 !dbg !588 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %sock.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1623, metadata !653), !dbg !1624
  store i32 %sock, i32* %sock.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sock.addr, metadata !1625, metadata !653), !dbg !1626
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1627, metadata !653), !dbg !1628
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1629
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 12, !dbg !1631
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1632
  %1 = load i32, i32* %fd, align 8, !dbg !1632
  %cmp = icmp ne i32 %1, -1, !dbg !1633
  br i1 %cmp, label %if.then, label %if.end, !dbg !1634

if.then:                                          ; preds = %entry
  store i32 -16, i32* %retval, align 4, !dbg !1635
  br label %return, !dbg !1635

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %sock.addr, align 4, !dbg !1636
  %call = call i32 @uv__nonblock_ioctl(i32 %2, i32 1), !dbg !1637
  store i32 %call, i32* %err, align 4, !dbg !1638
  %3 = load i32, i32* %err, align 4, !dbg !1639
  %tobool = icmp ne i32 %3, 0, !dbg !1639
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !1641

if.then1:                                         ; preds = %if.end
  %4 = load i32, i32* %err, align 4, !dbg !1642
  store i32 %4, i32* %retval, align 4, !dbg !1643
  br label %return, !dbg !1643

if.end2:                                          ; preds = %if.end
  %5 = load i32, i32* %sock.addr, align 4, !dbg !1644
  %call3 = call i32 @uv__set_reuse(i32 %5), !dbg !1645
  store i32 %call3, i32* %err, align 4, !dbg !1646
  %6 = load i32, i32* %err, align 4, !dbg !1647
  %tobool4 = icmp ne i32 %6, 0, !dbg !1647
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !1649

if.then5:                                         ; preds = %if.end2
  %7 = load i32, i32* %err, align 4, !dbg !1650
  store i32 %7, i32* %retval, align 4, !dbg !1651
  br label %return, !dbg !1651

if.end6:                                          ; preds = %if.end2
  %8 = load i32, i32* %sock.addr, align 4, !dbg !1652
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1653
  %io_watcher7 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %9, i32 0, i32 12, !dbg !1654
  %fd8 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher7, i32 0, i32 5, !dbg !1655
  store i32 %8, i32* %fd8, align 8, !dbg !1656
  store i32 0, i32* %retval, align 4, !dbg !1657
  br label %return, !dbg !1657

return:                                           ; preds = %if.end6, %if.then5, %if.then1, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !1658
  ret i32 %10, !dbg !1658
}

declare i32 @uv__nonblock_ioctl(i32, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv_udp_set_membership(%struct.uv_udp_s* %handle, i8* %multicast_addr, i8* %interface_addr, i32 %membership) #0 !dbg !592 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %multicast_addr.addr = alloca i8*, align 8
  %interface_addr.addr = alloca i8*, align 8
  %membership.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %addr4 = alloca %struct.sockaddr_in, align 4
  %addr6 = alloca %struct.sockaddr_in6, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1659, metadata !653), !dbg !1660
  store i8* %multicast_addr, i8** %multicast_addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %multicast_addr.addr, metadata !1661, metadata !653), !dbg !1662
  store i8* %interface_addr, i8** %interface_addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %interface_addr.addr, metadata !1663, metadata !653), !dbg !1664
  store i32 %membership, i32* %membership.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %membership.addr, metadata !1665, metadata !653), !dbg !1666
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1667, metadata !653), !dbg !1668
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in* %addr4, metadata !1669, metadata !653), !dbg !1670
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6* %addr6, metadata !1671, metadata !653), !dbg !1672
  %0 = load i8*, i8** %multicast_addr.addr, align 8, !dbg !1673
  %call = call i32 @uv_ip4_addr(i8* %0, i32 0, %struct.sockaddr_in* %addr4), !dbg !1675
  %cmp = icmp eq i32 %call, 0, !dbg !1676
  br i1 %cmp, label %if.then, label %if.else, !dbg !1677

if.then:                                          ; preds = %entry
  %1 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1678
  %call1 = call i32 @uv__udp_maybe_deferred_bind(%struct.uv_udp_s* %1, i32 2, i32 4), !dbg !1680
  store i32 %call1, i32* %err, align 4, !dbg !1681
  %2 = load i32, i32* %err, align 4, !dbg !1682
  %tobool = icmp ne i32 %2, 0, !dbg !1682
  br i1 %tobool, label %if.then2, label %if.end, !dbg !1684

if.then2:                                         ; preds = %if.then
  %3 = load i32, i32* %err, align 4, !dbg !1685
  store i32 %3, i32* %retval, align 4, !dbg !1686
  br label %return, !dbg !1686

if.end:                                           ; preds = %if.then
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1687
  %5 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1688
  %6 = load i32, i32* %membership.addr, align 4, !dbg !1689
  %call3 = call i32 @uv__udp_set_membership4(%struct.uv_udp_s* %4, %struct.sockaddr_in* %addr4, i8* %5, i32 %6), !dbg !1690
  store i32 %call3, i32* %retval, align 4, !dbg !1691
  br label %return, !dbg !1691

if.else:                                          ; preds = %entry
  %7 = load i8*, i8** %multicast_addr.addr, align 8, !dbg !1692
  %call4 = call i32 @uv_ip6_addr(i8* %7, i32 0, %struct.sockaddr_in6* %addr6), !dbg !1694
  %cmp5 = icmp eq i32 %call4, 0, !dbg !1695
  br i1 %cmp5, label %if.then6, label %if.else12, !dbg !1696

if.then6:                                         ; preds = %if.else
  %8 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1697
  %call7 = call i32 @uv__udp_maybe_deferred_bind(%struct.uv_udp_s* %8, i32 10, i32 4), !dbg !1699
  store i32 %call7, i32* %err, align 4, !dbg !1700
  %9 = load i32, i32* %err, align 4, !dbg !1701
  %tobool8 = icmp ne i32 %9, 0, !dbg !1701
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !1703

if.then9:                                         ; preds = %if.then6
  %10 = load i32, i32* %err, align 4, !dbg !1704
  store i32 %10, i32* %retval, align 4, !dbg !1705
  br label %return, !dbg !1705

if.end10:                                         ; preds = %if.then6
  %11 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1706
  %12 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1707
  %13 = load i32, i32* %membership.addr, align 4, !dbg !1708
  %call11 = call i32 @uv__udp_set_membership6(%struct.uv_udp_s* %11, %struct.sockaddr_in6* %addr6, i8* %12, i32 %13), !dbg !1709
  store i32 %call11, i32* %retval, align 4, !dbg !1710
  br label %return, !dbg !1710

if.else12:                                        ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !1711
  br label %return, !dbg !1711

return:                                           ; preds = %if.else12, %if.end10, %if.then9, %if.end, %if.then2
  %14 = load i32, i32* %retval, align 4, !dbg !1713
  ret i32 %14, !dbg !1713
}

declare i32 @uv_ip4_addr(i8*, i32, %struct.sockaddr_in*) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__udp_set_membership4(%struct.uv_udp_s* %handle, %struct.sockaddr_in* %multicast_addr, i8* %interface_addr, i32 %membership) #0 !dbg !631 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %multicast_addr.addr = alloca %struct.sockaddr_in*, align 8
  %interface_addr.addr = alloca i8*, align 8
  %membership.addr = alloca i32, align 4
  %mreq = alloca %struct.ip_mreq, align 4
  %optname = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1714, metadata !653), !dbg !1715
  store %struct.sockaddr_in* %multicast_addr, %struct.sockaddr_in** %multicast_addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %multicast_addr.addr, metadata !1716, metadata !653), !dbg !1717
  store i8* %interface_addr, i8** %interface_addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %interface_addr.addr, metadata !1718, metadata !653), !dbg !1719
  store i32 %membership, i32* %membership.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %membership.addr, metadata !1720, metadata !653), !dbg !1721
  call void @llvm.dbg.declare(metadata %struct.ip_mreq* %mreq, metadata !1722, metadata !653), !dbg !1727
  call void @llvm.dbg.declare(metadata i32* %optname, metadata !1728, metadata !653), !dbg !1729
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1730, metadata !653), !dbg !1731
  %0 = bitcast %struct.ip_mreq* %mreq to i8*, !dbg !1732
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 8, i32 4, i1 false), !dbg !1732
  %1 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1733
  %tobool = icmp ne i8* %1, null, !dbg !1733
  br i1 %tobool, label %if.then, label %if.else, !dbg !1735

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1736
  %imr_interface = getelementptr inbounds %struct.ip_mreq, %struct.ip_mreq* %mreq, i32 0, i32 1, !dbg !1738
  %s_addr = getelementptr inbounds %struct.in_addr, %struct.in_addr* %imr_interface, i32 0, i32 0, !dbg !1739
  %3 = bitcast i32* %s_addr to i8*, !dbg !1740
  %call = call i32 @uv_inet_pton(i32 2, i8* %2, i8* %3), !dbg !1741
  store i32 %call, i32* %err, align 4, !dbg !1742
  %4 = load i32, i32* %err, align 4, !dbg !1743
  %tobool1 = icmp ne i32 %4, 0, !dbg !1743
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !1745

if.then2:                                         ; preds = %if.then
  %5 = load i32, i32* %err, align 4, !dbg !1746
  store i32 %5, i32* %retval, align 4, !dbg !1747
  br label %return, !dbg !1747

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !1748

if.else:                                          ; preds = %entry
  %call3 = call i32 @htonl(i32 0) #1, !dbg !1749
  %imr_interface4 = getelementptr inbounds %struct.ip_mreq, %struct.ip_mreq* %mreq, i32 0, i32 1, !dbg !1751
  %s_addr5 = getelementptr inbounds %struct.in_addr, %struct.in_addr* %imr_interface4, i32 0, i32 0, !dbg !1752
  store i32 %call3, i32* %s_addr5, align 4, !dbg !1753
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.end
  %6 = load %struct.sockaddr_in*, %struct.sockaddr_in** %multicast_addr.addr, align 8, !dbg !1754
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %6, i32 0, i32 2, !dbg !1755
  %s_addr7 = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr, i32 0, i32 0, !dbg !1756
  %7 = load i32, i32* %s_addr7, align 4, !dbg !1756
  %imr_multiaddr = getelementptr inbounds %struct.ip_mreq, %struct.ip_mreq* %mreq, i32 0, i32 0, !dbg !1757
  %s_addr8 = getelementptr inbounds %struct.in_addr, %struct.in_addr* %imr_multiaddr, i32 0, i32 0, !dbg !1758
  store i32 %7, i32* %s_addr8, align 4, !dbg !1759
  %8 = load i32, i32* %membership.addr, align 4, !dbg !1760
  switch i32 %8, label %sw.default [
    i32 1, label %sw.bb
    i32 0, label %sw.bb9
  ], !dbg !1761

sw.bb:                                            ; preds = %if.end6
  store i32 35, i32* %optname, align 4, !dbg !1762
  br label %sw.epilog, !dbg !1764

sw.bb9:                                           ; preds = %if.end6
  store i32 36, i32* %optname, align 4, !dbg !1765
  br label %sw.epilog, !dbg !1766

sw.default:                                       ; preds = %if.end6
  store i32 -22, i32* %retval, align 4, !dbg !1767
  br label %return, !dbg !1767

sw.epilog:                                        ; preds = %sw.bb9, %sw.bb
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1768
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %9, i32 0, i32 12, !dbg !1770
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1771
  %10 = load i32, i32* %fd, align 8, !dbg !1771
  %11 = load i32, i32* %optname, align 4, !dbg !1772
  %12 = bitcast %struct.ip_mreq* %mreq to i8*, !dbg !1773
  %call10 = call i32 @setsockopt(i32 %10, i32 0, i32 %11, i8* %12, i32 8) #8, !dbg !1774
  %tobool11 = icmp ne i32 %call10, 0, !dbg !1774
  br i1 %tobool11, label %if.then12, label %if.end14, !dbg !1775

if.then12:                                        ; preds = %sw.epilog
  %call13 = call i32* @__errno_location() #1, !dbg !1776
  %13 = load i32, i32* %call13, align 4, !dbg !1776
  %sub = sub nsw i32 0, %13, !dbg !1778
  store i32 %sub, i32* %retval, align 4, !dbg !1779
  br label %return, !dbg !1779

if.end14:                                         ; preds = %sw.epilog
  store i32 0, i32* %retval, align 4, !dbg !1780
  br label %return, !dbg !1780

return:                                           ; preds = %if.end14, %if.then12, %sw.default, %if.then2
  %14 = load i32, i32* %retval, align 4, !dbg !1781
  ret i32 %14, !dbg !1781
}

declare i32 @uv_ip6_addr(i8*, i32, %struct.sockaddr_in6*) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__udp_set_membership6(%struct.uv_udp_s* %handle, %struct.sockaddr_in6* %multicast_addr, i8* %interface_addr, i32 %membership) #0 !dbg !636 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %multicast_addr.addr = alloca %struct.sockaddr_in6*, align 8
  %interface_addr.addr = alloca i8*, align 8
  %membership.addr = alloca i32, align 4
  %optname = alloca i32, align 4
  %mreq = alloca %struct.ipv6_mreq, align 4
  %addr6 = alloca %struct.sockaddr_in6, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1782, metadata !653), !dbg !1783
  store %struct.sockaddr_in6* %multicast_addr, %struct.sockaddr_in6** %multicast_addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6** %multicast_addr.addr, metadata !1784, metadata !653), !dbg !1785
  store i8* %interface_addr, i8** %interface_addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %interface_addr.addr, metadata !1786, metadata !653), !dbg !1787
  store i32 %membership, i32* %membership.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %membership.addr, metadata !1788, metadata !653), !dbg !1789
  call void @llvm.dbg.declare(metadata i32* %optname, metadata !1790, metadata !653), !dbg !1791
  call void @llvm.dbg.declare(metadata %struct.ipv6_mreq* %mreq, metadata !1792, metadata !653), !dbg !1797
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6* %addr6, metadata !1798, metadata !653), !dbg !1799
  %0 = bitcast %struct.ipv6_mreq* %mreq to i8*, !dbg !1800
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 20, i32 4, i1 false), !dbg !1800
  %1 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1801
  %tobool = icmp ne i8* %1, null, !dbg !1801
  br i1 %tobool, label %if.then, label %if.else, !dbg !1803

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1804
  %call = call i32 @uv_ip6_addr(i8* %2, i32 0, %struct.sockaddr_in6* %addr6), !dbg !1807
  %tobool1 = icmp ne i32 %call, 0, !dbg !1807
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !1808

if.then2:                                         ; preds = %if.then
  store i32 -22, i32* %retval, align 4, !dbg !1809
  br label %return, !dbg !1809

if.end:                                           ; preds = %if.then
  %sin6_scope_id = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %addr6, i32 0, i32 4, !dbg !1810
  %3 = load i32, i32* %sin6_scope_id, align 4, !dbg !1810
  %ipv6mr_interface = getelementptr inbounds %struct.ipv6_mreq, %struct.ipv6_mreq* %mreq, i32 0, i32 1, !dbg !1811
  store i32 %3, i32* %ipv6mr_interface, align 4, !dbg !1812
  br label %if.end4, !dbg !1813

if.else:                                          ; preds = %entry
  %ipv6mr_interface3 = getelementptr inbounds %struct.ipv6_mreq, %struct.ipv6_mreq* %mreq, i32 0, i32 1, !dbg !1814
  store i32 0, i32* %ipv6mr_interface3, align 4, !dbg !1816
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.end
  %ipv6mr_multiaddr = getelementptr inbounds %struct.ipv6_mreq, %struct.ipv6_mreq* %mreq, i32 0, i32 0, !dbg !1817
  %4 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %multicast_addr.addr, align 8, !dbg !1818
  %sin6_addr = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %4, i32 0, i32 3, !dbg !1819
  %5 = bitcast %struct.in6_addr* %ipv6mr_multiaddr to i8*, !dbg !1819
  %6 = bitcast %struct.in6_addr* %sin6_addr to i8*, !dbg !1819
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 16, i32 4, i1 false), !dbg !1819
  %7 = load i32, i32* %membership.addr, align 4, !dbg !1820
  switch i32 %7, label %sw.default [
    i32 1, label %sw.bb
    i32 0, label %sw.bb5
  ], !dbg !1821

sw.bb:                                            ; preds = %if.end4
  store i32 20, i32* %optname, align 4, !dbg !1822
  br label %sw.epilog, !dbg !1824

sw.bb5:                                           ; preds = %if.end4
  store i32 21, i32* %optname, align 4, !dbg !1825
  br label %sw.epilog, !dbg !1826

sw.default:                                       ; preds = %if.end4
  store i32 -22, i32* %retval, align 4, !dbg !1827
  br label %return, !dbg !1827

sw.epilog:                                        ; preds = %sw.bb5, %sw.bb
  %8 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1828
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %8, i32 0, i32 12, !dbg !1830
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1831
  %9 = load i32, i32* %fd, align 8, !dbg !1831
  %10 = load i32, i32* %optname, align 4, !dbg !1832
  %11 = bitcast %struct.ipv6_mreq* %mreq to i8*, !dbg !1833
  %call6 = call i32 @setsockopt(i32 %9, i32 41, i32 %10, i8* %11, i32 20) #8, !dbg !1834
  %tobool7 = icmp ne i32 %call6, 0, !dbg !1834
  br i1 %tobool7, label %if.then8, label %if.end10, !dbg !1835

if.then8:                                         ; preds = %sw.epilog
  %call9 = call i32* @__errno_location() #1, !dbg !1836
  %12 = load i32, i32* %call9, align 4, !dbg !1836
  %sub = sub nsw i32 0, %12, !dbg !1838
  store i32 %sub, i32* %retval, align 4, !dbg !1839
  br label %return, !dbg !1839

if.end10:                                         ; preds = %sw.epilog
  store i32 0, i32* %retval, align 4, !dbg !1840
  br label %return, !dbg !1840

return:                                           ; preds = %if.end10, %if.then8, %sw.default, %if.then2
  %13 = load i32, i32* %retval, align 4, !dbg !1841
  ret i32 %13, !dbg !1841
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_set_broadcast(%struct.uv_udp_s* %handle, i32 %on) #0 !dbg !598 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %on.addr = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1842, metadata !653), !dbg !1843
  store i32 %on, i32* %on.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %on.addr, metadata !1844, metadata !653), !dbg !1845
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1846
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 12, !dbg !1848
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1849
  %1 = load i32, i32* %fd, align 8, !dbg !1849
  %2 = bitcast i32* %on.addr to i8*, !dbg !1850
  %call = call i32 @setsockopt(i32 %1, i32 1, i32 6, i8* %2, i32 4) #8, !dbg !1851
  %tobool = icmp ne i32 %call, 0, !dbg !1851
  br i1 %tobool, label %if.then, label %if.end, !dbg !1852

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1853
  %3 = load i32, i32* %call1, align 4, !dbg !1853
  %sub = sub nsw i32 0, %3, !dbg !1855
  store i32 %sub, i32* %retval, align 4, !dbg !1856
  br label %return, !dbg !1856

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1857
  br label %return, !dbg !1857

return:                                           ; preds = %if.end, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !1858
  ret i32 %4, !dbg !1858
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_set_ttl(%struct.uv_udp_s* %handle, i32 %ttl) #0 !dbg !601 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %ttl.addr = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1859, metadata !653), !dbg !1860
  store i32 %ttl, i32* %ttl.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ttl.addr, metadata !1861, metadata !653), !dbg !1862
  %0 = load i32, i32* %ttl.addr, align 4, !dbg !1863
  %cmp = icmp slt i32 %0, 1, !dbg !1865
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1866

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32, i32* %ttl.addr, align 4, !dbg !1867
  %cmp1 = icmp sgt i32 %1, 255, !dbg !1869
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1870

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1871
  br label %return, !dbg !1871

if.end:                                           ; preds = %lor.lhs.false
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1872
  %3 = load i32, i32* %ttl.addr, align 4, !dbg !1873
  %call = call i32 @uv__setsockopt_maybe_char(%struct.uv_udp_s* %2, i32 2, i32 16, i32 %3), !dbg !1874
  store i32 %call, i32* %retval, align 4, !dbg !1875
  br label %return, !dbg !1875

return:                                           ; preds = %if.end, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !1876
  ret i32 %4, !dbg !1876
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__setsockopt_maybe_char(%struct.uv_udp_s* %handle, i32 %option4, i32 %option6, i32 %val) #0 !dbg !641 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %option4.addr = alloca i32, align 4
  %option6.addr = alloca i32, align 4
  %val.addr = alloca i32, align 4
  %arg = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1877, metadata !653), !dbg !1878
  store i32 %option4, i32* %option4.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option4.addr, metadata !1879, metadata !653), !dbg !1880
  store i32 %option6, i32* %option6.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option6.addr, metadata !1881, metadata !653), !dbg !1882
  store i32 %val, i32* %val.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %val.addr, metadata !1883, metadata !653), !dbg !1884
  call void @llvm.dbg.declare(metadata i32* %arg, metadata !1885, metadata !653), !dbg !1886
  %0 = load i32, i32* %val.addr, align 4, !dbg !1887
  store i32 %0, i32* %arg, align 4, !dbg !1886
  %1 = load i32, i32* %val.addr, align 4, !dbg !1888
  %cmp = icmp slt i32 %1, 0, !dbg !1890
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1891

lor.lhs.false:                                    ; preds = %entry
  %2 = load i32, i32* %val.addr, align 4, !dbg !1892
  %cmp1 = icmp sgt i32 %2, 255, !dbg !1894
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1895

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1896
  br label %return, !dbg !1896

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1897
  %4 = load i32, i32* %option4.addr, align 4, !dbg !1898
  %5 = load i32, i32* %option6.addr, align 4, !dbg !1899
  %6 = bitcast i32* %arg to i8*, !dbg !1900
  %call = call i32 @uv__setsockopt(%struct.uv_udp_s* %3, i32 %4, i32 %5, i8* %6, i64 4), !dbg !1901
  store i32 %call, i32* %retval, align 4, !dbg !1902
  br label %return, !dbg !1902

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1903
  ret i32 %7, !dbg !1903
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_set_multicast_ttl(%struct.uv_udp_s* %handle, i32 %ttl) #0 !dbg !602 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %ttl.addr = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1904, metadata !653), !dbg !1905
  store i32 %ttl, i32* %ttl.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ttl.addr, metadata !1906, metadata !653), !dbg !1907
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1908
  %1 = load i32, i32* %ttl.addr, align 4, !dbg !1909
  %call = call i32 @uv__setsockopt_maybe_char(%struct.uv_udp_s* %0, i32 33, i32 18, i32 %1), !dbg !1910
  ret i32 %call, !dbg !1911
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_set_multicast_loop(%struct.uv_udp_s* %handle, i32 %on) #0 !dbg !603 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %on.addr = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1912, metadata !653), !dbg !1913
  store i32 %on, i32* %on.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %on.addr, metadata !1914, metadata !653), !dbg !1915
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1916
  %1 = load i32, i32* %on.addr, align 4, !dbg !1917
  %call = call i32 @uv__setsockopt_maybe_char(%struct.uv_udp_s* %0, i32 34, i32 19, i32 %1), !dbg !1918
  ret i32 %call, !dbg !1919
}

; Function Attrs: nounwind uwtable
define i32 @uv_udp_set_multicast_interface(%struct.uv_udp_s* %handle, i8* %interface_addr) #0 !dbg !604 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %interface_addr.addr = alloca i8*, align 8
  %addr_st = alloca %struct.sockaddr_storage, align 8
  %addr4 = alloca %struct.sockaddr_in*, align 8
  %addr6 = alloca %struct.sockaddr_in6*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !1920, metadata !653), !dbg !1921
  store i8* %interface_addr, i8** %interface_addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %interface_addr.addr, metadata !1922, metadata !653), !dbg !1923
  call void @llvm.dbg.declare(metadata %struct.sockaddr_storage* %addr_st, metadata !1924, metadata !653), !dbg !1925
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %addr4, metadata !1926, metadata !653), !dbg !1927
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in6** %addr6, metadata !1928, metadata !653), !dbg !1929
  %0 = bitcast %struct.sockaddr_storage* %addr_st to %struct.sockaddr_in*, !dbg !1930
  store %struct.sockaddr_in* %0, %struct.sockaddr_in** %addr4, align 8, !dbg !1931
  %1 = bitcast %struct.sockaddr_storage* %addr_st to %struct.sockaddr_in6*, !dbg !1932
  store %struct.sockaddr_in6* %1, %struct.sockaddr_in6** %addr6, align 8, !dbg !1933
  %2 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1934
  %tobool = icmp ne i8* %2, null, !dbg !1934
  br i1 %tobool, label %if.else4, label %if.then, !dbg !1936

if.then:                                          ; preds = %entry
  %3 = bitcast %struct.sockaddr_storage* %addr_st to i8*, !dbg !1937
  call void @llvm.memset.p0i8.i64(i8* %3, i8 0, i64 128, i32 8, i1 false), !dbg !1937
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1939
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %4, i32 0, i32 7, !dbg !1941
  %5 = load i32, i32* %flags, align 8, !dbg !1941
  %and = and i32 %5, 65536, !dbg !1942
  %tobool1 = icmp ne i32 %and, 0, !dbg !1942
  br i1 %tobool1, label %if.then2, label %if.else, !dbg !1943

if.then2:                                         ; preds = %if.then
  %ss_family = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %addr_st, i32 0, i32 0, !dbg !1944
  store i16 10, i16* %ss_family, align 8, !dbg !1946
  %6 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr6, align 8, !dbg !1947
  %sin6_scope_id = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %6, i32 0, i32 4, !dbg !1948
  store i32 0, i32* %sin6_scope_id, align 4, !dbg !1949
  br label %if.end, !dbg !1950

if.else:                                          ; preds = %if.then
  %ss_family3 = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %addr_st, i32 0, i32 0, !dbg !1951
  store i16 2, i16* %ss_family3, align 8, !dbg !1953
  %call = call i32 @htonl(i32 0) #1, !dbg !1954
  %7 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr4, align 8, !dbg !1955
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %7, i32 0, i32 2, !dbg !1956
  %s_addr = getelementptr inbounds %struct.in_addr, %struct.in_addr* %sin_addr, i32 0, i32 0, !dbg !1957
  store i32 %call, i32* %s_addr, align 4, !dbg !1958
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  br label %if.end14, !dbg !1959

if.else4:                                         ; preds = %entry
  %8 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1960
  %9 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr4, align 8, !dbg !1963
  %call5 = call i32 @uv_ip4_addr(i8* %8, i32 0, %struct.sockaddr_in* %9), !dbg !1964
  %cmp = icmp eq i32 %call5, 0, !dbg !1965
  br i1 %cmp, label %if.then6, label %if.else7, !dbg !1964

if.then6:                                         ; preds = %if.else4
  br label %if.end13, !dbg !1966

if.else7:                                         ; preds = %if.else4
  %10 = load i8*, i8** %interface_addr.addr, align 8, !dbg !1968
  %11 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr6, align 8, !dbg !1971
  %call8 = call i32 @uv_ip6_addr(i8* %10, i32 0, %struct.sockaddr_in6* %11), !dbg !1972
  %cmp9 = icmp eq i32 %call8, 0, !dbg !1973
  br i1 %cmp9, label %if.then10, label %if.else11, !dbg !1972

if.then10:                                        ; preds = %if.else7
  br label %if.end12, !dbg !1974

if.else11:                                        ; preds = %if.else7
  store i32 -22, i32* %retval, align 4, !dbg !1976
  br label %return, !dbg !1976

if.end12:                                         ; preds = %if.then10
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.then6
  br label %if.end14

if.end14:                                         ; preds = %if.end13, %if.end
  %ss_family15 = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %addr_st, i32 0, i32 0, !dbg !1978
  %12 = load i16, i16* %ss_family15, align 8, !dbg !1978
  %conv = zext i16 %12 to i32, !dbg !1980
  %cmp16 = icmp eq i32 %conv, 2, !dbg !1981
  br i1 %cmp16, label %if.then18, label %if.else26, !dbg !1982

if.then18:                                        ; preds = %if.end14
  %13 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !1983
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %13, i32 0, i32 12, !dbg !1986
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1987
  %14 = load i32, i32* %fd, align 8, !dbg !1987
  %15 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr4, align 8, !dbg !1988
  %sin_addr19 = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %15, i32 0, i32 2, !dbg !1989
  %16 = bitcast %struct.in_addr* %sin_addr19 to i8*, !dbg !1990
  %call20 = call i32 @setsockopt(i32 %14, i32 0, i32 32, i8* %16, i32 4) #8, !dbg !1991
  %cmp21 = icmp eq i32 %call20, -1, !dbg !1992
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !1993

if.then23:                                        ; preds = %if.then18
  %call24 = call i32* @__errno_location() #1, !dbg !1994
  %17 = load i32, i32* %call24, align 4, !dbg !1994
  %sub = sub nsw i32 0, %17, !dbg !1996
  store i32 %sub, i32* %retval, align 4, !dbg !1997
  br label %return, !dbg !1997

if.end25:                                         ; preds = %if.then18
  br label %if.end44, !dbg !1998

if.else26:                                        ; preds = %if.end14
  %ss_family27 = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %addr_st, i32 0, i32 0, !dbg !1999
  %18 = load i16, i16* %ss_family27, align 8, !dbg !1999
  %conv28 = zext i16 %18 to i32, !dbg !2002
  %cmp29 = icmp eq i32 %conv28, 10, !dbg !2003
  br i1 %cmp29, label %if.then31, label %if.else42, !dbg !2002

if.then31:                                        ; preds = %if.else26
  %19 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2004
  %io_watcher32 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %19, i32 0, i32 12, !dbg !2007
  %fd33 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher32, i32 0, i32 5, !dbg !2008
  %20 = load i32, i32* %fd33, align 8, !dbg !2008
  %21 = load %struct.sockaddr_in6*, %struct.sockaddr_in6** %addr6, align 8, !dbg !2009
  %sin6_scope_id34 = getelementptr inbounds %struct.sockaddr_in6, %struct.sockaddr_in6* %21, i32 0, i32 4, !dbg !2010
  %22 = bitcast i32* %sin6_scope_id34 to i8*, !dbg !2011
  %call35 = call i32 @setsockopt(i32 %20, i32 41, i32 17, i8* %22, i32 4) #8, !dbg !2012
  %cmp36 = icmp eq i32 %call35, -1, !dbg !2013
  br i1 %cmp36, label %if.then38, label %if.end41, !dbg !2014

if.then38:                                        ; preds = %if.then31
  %call39 = call i32* @__errno_location() #1, !dbg !2015
  %23 = load i32, i32* %call39, align 4, !dbg !2015
  %sub40 = sub nsw i32 0, %23, !dbg !2017
  store i32 %sub40, i32* %retval, align 4, !dbg !2018
  br label %return, !dbg !2018

if.end41:                                         ; preds = %if.then31
  br label %if.end43, !dbg !2019

if.else42:                                        ; preds = %if.else26
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 838, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @__PRETTY_FUNCTION__.uv_udp_set_multicast_interface, i32 0, i32 0)) #7, !dbg !2020
  unreachable, !dbg !2020

if.end43:                                         ; preds = %if.end41
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.end25
  store i32 0, i32* %retval, align 4, !dbg !2022
  br label %return, !dbg !2022

return:                                           ; preds = %if.end44, %if.then38, %if.then23, %if.else11
  %24 = load i32, i32* %retval, align 4, !dbg !2023
  ret i32 %24, !dbg !2023
}

; Function Attrs: nounwind readnone
declare i32 @htonl(i32) #5

; Function Attrs: nounwind uwtable
define i32 @uv_udp_getsockname(%struct.uv_udp_s* %handle, %struct.sockaddr* %name, i32* %namelen) #0 !dbg !607 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %name.addr = alloca %struct.sockaddr*, align 8
  %namelen.addr = alloca i32*, align 8
  %socklen = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !2024, metadata !653), !dbg !2025
  store %struct.sockaddr* %name, %struct.sockaddr** %name.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %name.addr, metadata !2026, metadata !653), !dbg !2027
  store i32* %namelen, i32** %namelen.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %namelen.addr, metadata !2028, metadata !653), !dbg !2029
  call void @llvm.dbg.declare(metadata i32* %socklen, metadata !2030, metadata !653), !dbg !2031
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2032
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 12, !dbg !2034
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2035
  %1 = load i32, i32* %fd, align 8, !dbg !2035
  %cmp = icmp eq i32 %1, -1, !dbg !2036
  br i1 %cmp, label %if.then, label %if.end, !dbg !2037

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !2038
  br label %return, !dbg !2038

if.end:                                           ; preds = %entry
  %2 = load i32*, i32** %namelen.addr, align 8, !dbg !2039
  %3 = load i32, i32* %2, align 4, !dbg !2040
  store i32 %3, i32* %socklen, align 4, !dbg !2041
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2042
  %io_watcher1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %4, i32 0, i32 12, !dbg !2044
  %fd2 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher1, i32 0, i32 5, !dbg !2045
  %5 = load i32, i32* %fd2, align 8, !dbg !2045
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !2046
  %6 = load %struct.sockaddr*, %struct.sockaddr** %name.addr, align 8, !dbg !2046
  store %struct.sockaddr* %6, %struct.sockaddr** %__sockaddr__, align 8, !dbg !2046
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !2047
  %7 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !2047
  %call = call i32 @getsockname(i32 %5, %struct.sockaddr* %7, i32* %socklen) #8, !dbg !2047
  %tobool = icmp ne i32 %call, 0, !dbg !2047
  br i1 %tobool, label %if.then3, label %if.end5, !dbg !2048

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__errno_location() #1, !dbg !2049
  %8 = load i32, i32* %call4, align 4, !dbg !2049
  %sub = sub nsw i32 0, %8, !dbg !2050
  store i32 %sub, i32* %retval, align 4, !dbg !2051
  br label %return, !dbg !2051

if.end5:                                          ; preds = %if.end
  %9 = load i32, i32* %socklen, align 4, !dbg !2052
  %10 = load i32*, i32** %namelen.addr, align 8, !dbg !2053
  store i32 %9, i32* %10, align 4, !dbg !2054
  store i32 0, i32* %retval, align 4, !dbg !2055
  br label %return, !dbg !2055

return:                                           ; preds = %if.end5, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !2056
  ret i32 %11, !dbg !2056
}

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind uwtable
define i32 @uv__udp_recv_start(%struct.uv_udp_s* %handle, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %alloc_cb, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %recv_cb) #0 !dbg !613 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %alloc_cb.addr = alloca void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, align 8
  %recv_cb.addr = alloca void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, align 8
  %err = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !2057, metadata !653), !dbg !2058
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %alloc_cb, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, metadata !2059, metadata !653), !dbg !2060
  store void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %recv_cb, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, metadata !2061, metadata !653), !dbg !2062
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2063, metadata !653), !dbg !2064
  %0 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8, !dbg !2065
  %cmp = icmp eq void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %0, null, !dbg !2067
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2068

lor.lhs.false:                                    ; preds = %entry
  %1 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, align 8, !dbg !2069
  %cmp1 = icmp eq void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %1, null, !dbg !2071
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2072

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !2073
  br label %return, !dbg !2073

if.end:                                           ; preds = %lor.lhs.false
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2074
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %2, i32 0, i32 12, !dbg !2076
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher, i32 1), !dbg !2077
  %tobool = icmp ne i32 %call, 0, !dbg !2077
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !2078

if.then2:                                         ; preds = %if.end
  store i32 -114, i32* %retval, align 4, !dbg !2079
  br label %return, !dbg !2079

if.end3:                                          ; preds = %if.end
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2080
  %call4 = call i32 @uv__udp_maybe_deferred_bind(%struct.uv_udp_s* %3, i32 2, i32 0), !dbg !2081
  store i32 %call4, i32* %err, align 4, !dbg !2082
  %4 = load i32, i32* %err, align 4, !dbg !2083
  %tobool5 = icmp ne i32 %4, 0, !dbg !2083
  br i1 %tobool5, label %if.then6, label %if.end7, !dbg !2085

if.then6:                                         ; preds = %if.end3
  %5 = load i32, i32* %err, align 4, !dbg !2086
  store i32 %5, i32* %retval, align 4, !dbg !2087
  br label %return, !dbg !2087

if.end7:                                          ; preds = %if.end3
  %6 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8, !dbg !2088
  %7 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2089
  %alloc_cb8 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %7, i32 0, i32 10, !dbg !2090
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %6, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb8, align 8, !dbg !2091
  %8 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb.addr, align 8, !dbg !2092
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2093
  %recv_cb9 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %9, i32 0, i32 11, !dbg !2094
  store void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %8, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb9, align 8, !dbg !2095
  %10 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2096
  %loop = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %10, i32 0, i32 1, !dbg !2097
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2097
  %12 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2098
  %io_watcher10 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %12, i32 0, i32 12, !dbg !2099
  call void @uv__io_start(%struct.uv_loop_s* %11, %struct.uv__io_s* %io_watcher10, i32 1), !dbg !2100
  br label %do.body, !dbg !2101

do.body:                                          ; preds = %if.end7
  %13 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2102
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %13, i32 0, i32 7, !dbg !2102
  %14 = load i32, i32* %flags, align 8, !dbg !2102
  %and = and i32 %14, 0, !dbg !2102
  %cmp11 = icmp eq i32 %and, 0, !dbg !2102
  br i1 %cmp11, label %cond.true, label %cond.false, !dbg !2102

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !2105

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 884, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv__udp_recv_start, i32 0, i32 0)) #7, !dbg !2107
  unreachable, !dbg !2107
                                                  ; No predecessors!
  br label %cond.end, !dbg !2109

cond.end:                                         ; preds = %15, %cond.true
  %16 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2111
  %flags12 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %16, i32 0, i32 7, !dbg !2111
  %17 = load i32, i32* %flags12, align 8, !dbg !2111
  %and13 = and i32 %17, 16384, !dbg !2111
  %cmp14 = icmp ne i32 %and13, 0, !dbg !2111
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !2111

if.then15:                                        ; preds = %cond.end
  br label %do.end25, !dbg !2114

if.end16:                                         ; preds = %cond.end
  %18 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2116
  %flags17 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %18, i32 0, i32 7, !dbg !2116
  %19 = load i32, i32* %flags17, align 8, !dbg !2116
  %or = or i32 %19, 16384, !dbg !2116
  store i32 %or, i32* %flags17, align 8, !dbg !2116
  %20 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2116
  %flags18 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %20, i32 0, i32 7, !dbg !2116
  %21 = load i32, i32* %flags18, align 8, !dbg !2116
  %and19 = and i32 %21, 8192, !dbg !2116
  %cmp20 = icmp ne i32 %and19, 0, !dbg !2116
  br i1 %cmp20, label %if.then21, label %if.end24, !dbg !2116

if.then21:                                        ; preds = %if.end16
  br label %do.body22, !dbg !2118

do.body22:                                        ; preds = %if.then21
  %22 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2121
  %loop23 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %22, i32 0, i32 1, !dbg !2121
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop23, align 8, !dbg !2121
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 1, !dbg !2121
  %24 = load i32, i32* %active_handles, align 8, !dbg !2121
  %inc = add i32 %24, 1, !dbg !2121
  store i32 %inc, i32* %active_handles, align 8, !dbg !2121
  br label %do.end, !dbg !2121

do.end:                                           ; preds = %do.body22
  br label %if.end24, !dbg !2124

if.end24:                                         ; preds = %do.end, %if.end16
  br label %do.end25, !dbg !2126

do.end25:                                         ; preds = %if.end24, %if.then15
  store i32 0, i32* %retval, align 4, !dbg !2128
  br label %return, !dbg !2128

return:                                           ; preds = %do.end25, %if.then6, %if.then2, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !2129
  ret i32 %25, !dbg !2129
}

; Function Attrs: nounwind uwtable
define i32 @uv__udp_recv_stop(%struct.uv_udp_s* %handle) #0 !dbg !616 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !2130, metadata !653), !dbg !2131
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2132
  %loop = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 1, !dbg !2133
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2133
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2134
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %2, i32 0, i32 12, !dbg !2135
  call void @uv__io_stop(%struct.uv_loop_s* %1, %struct.uv__io_s* %io_watcher, i32 1), !dbg !2136
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2137
  %io_watcher1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %3, i32 0, i32 12, !dbg !2139
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher1, i32 4), !dbg !2140
  %tobool = icmp ne i32 %call, 0, !dbg !2140
  br i1 %tobool, label %if.end16, label %if.then, !dbg !2141

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !2142

do.body:                                          ; preds = %if.then
  %4 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2143
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %4, i32 0, i32 7, !dbg !2143
  %5 = load i32, i32* %flags, align 8, !dbg !2143
  %and = and i32 %5, 0, !dbg !2143
  %cmp = icmp eq i32 %and, 0, !dbg !2143
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2143

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !2146

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 894, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @__PRETTY_FUNCTION__.uv__udp_recv_stop, i32 0, i32 0)) #7, !dbg !2148
  unreachable, !dbg !2148
                                                  ; No predecessors!
  br label %cond.end, !dbg !2150

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2152
  %flags2 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %7, i32 0, i32 7, !dbg !2152
  %8 = load i32, i32* %flags2, align 8, !dbg !2152
  %and3 = and i32 %8, 16384, !dbg !2152
  %cmp4 = icmp eq i32 %and3, 0, !dbg !2152
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !2152

if.then5:                                         ; preds = %cond.end
  br label %do.end15, !dbg !2155

if.end:                                           ; preds = %cond.end
  %9 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2157
  %flags6 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %9, i32 0, i32 7, !dbg !2157
  %10 = load i32, i32* %flags6, align 8, !dbg !2157
  %and7 = and i32 %10, -16385, !dbg !2157
  store i32 %and7, i32* %flags6, align 8, !dbg !2157
  %11 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2157
  %flags8 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %11, i32 0, i32 7, !dbg !2157
  %12 = load i32, i32* %flags8, align 8, !dbg !2157
  %and9 = and i32 %12, 8192, !dbg !2157
  %cmp10 = icmp ne i32 %and9, 0, !dbg !2157
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !2157

if.then11:                                        ; preds = %if.end
  br label %do.body12, !dbg !2159

do.body12:                                        ; preds = %if.then11
  %13 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2162
  %loop13 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %13, i32 0, i32 1, !dbg !2162
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop13, align 8, !dbg !2162
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 1, !dbg !2162
  %15 = load i32, i32* %active_handles, align 8, !dbg !2162
  %dec = add i32 %15, -1, !dbg !2162
  store i32 %dec, i32* %active_handles, align 8, !dbg !2162
  br label %do.end, !dbg !2162

do.end:                                           ; preds = %do.body12
  br label %if.end14, !dbg !2165

if.end14:                                         ; preds = %do.end, %if.end
  br label %do.end15, !dbg !2167

do.end15:                                         ; preds = %if.end14, %if.then5
  br label %if.end16, !dbg !2169

if.end16:                                         ; preds = %do.end15, %entry
  %16 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2171
  %alloc_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %16, i32 0, i32 10, !dbg !2172
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !2173
  %17 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2174
  %recv_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %17, i32 0, i32 11, !dbg !2175
  store void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* null, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb, align 8, !dbg !2176
  ret i32 0, !dbg !2177
}

declare void @uv__io_stop(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

declare void @uv__free(i8*) #2

declare void @uv__io_feed(%struct.uv_loop_s*, %struct.uv__io_s*) #2

; Function Attrs: nounwind uwtable
define internal void @uv__udp_recvmsg(%struct.uv_udp_s* %handle) #0 !dbg !630 {
entry:
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %peer = alloca %struct.sockaddr_storage, align 8
  %h = alloca %struct.msghdr, align 8
  %nread = alloca i64, align 8
  %buf = alloca %struct.uv_buf_t, align 8
  %flags = alloca i32, align 4
  %count = alloca i32, align 4
  %coerce = alloca %struct.uv_buf_t, align 8
  %addr = alloca %struct.sockaddr*, align 8
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !2178, metadata !653), !dbg !2179
  call void @llvm.dbg.declare(metadata %struct.sockaddr_storage* %peer, metadata !2180, metadata !653), !dbg !2181
  call void @llvm.dbg.declare(metadata %struct.msghdr* %h, metadata !2182, metadata !653), !dbg !2183
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2184, metadata !653), !dbg !2185
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t* %buf, metadata !2186, metadata !653), !dbg !2187
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !2188, metadata !653), !dbg !2189
  call void @llvm.dbg.declare(metadata i32* %count, metadata !2190, metadata !653), !dbg !2191
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2192
  %recv_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 11, !dbg !2192
  %1 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb, align 8, !dbg !2192
  %cmp = icmp ne void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %1, null, !dbg !2192
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2192

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2193

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 159, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__udp_recvmsg, i32 0, i32 0)) #7, !dbg !2195
  unreachable, !dbg !2195
                                                  ; No predecessors!
  br label %cond.end, !dbg !2197

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2199
  %alloc_cb = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %3, i32 0, i32 10, !dbg !2199
  %4 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !2199
  %cmp1 = icmp ne void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %4, null, !dbg !2199
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !2199

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !2200

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 160, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__udp_recvmsg, i32 0, i32 0)) #7, !dbg !2201
  unreachable, !dbg !2201
                                                  ; No predecessors!
  br label %cond.end4, !dbg !2202

cond.end4:                                        ; preds = %5, %cond.true2
  store i32 32, i32* %count, align 4, !dbg !2203
  %6 = bitcast %struct.msghdr* %h to i8*, !dbg !2204
  call void @llvm.memset.p0i8.i64(i8* %6, i8 0, i64 56, i32 8, i1 false), !dbg !2204
  %7 = bitcast %struct.sockaddr_storage* %peer to i8*, !dbg !2205
  %msg_name = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 0, !dbg !2206
  store i8* %7, i8** %msg_name, align 8, !dbg !2207
  br label %do.body, !dbg !2208

do.body:                                          ; preds = %land.end56, %cond.end4
  %call = call { i8*, i64 } @uv_buf_init(i8* null, i32 0), !dbg !2209
  %8 = bitcast %struct.uv_buf_t* %coerce to { i8*, i64 }*, !dbg !2209
  %9 = getelementptr inbounds { i8*, i64 }, { i8*, i64 }* %8, i32 0, i32 0, !dbg !2209
  %10 = extractvalue { i8*, i64 } %call, 0, !dbg !2209
  store i8* %10, i8** %9, align 8, !dbg !2209
  %11 = getelementptr inbounds { i8*, i64 }, { i8*, i64 }* %8, i32 0, i32 1, !dbg !2209
  %12 = extractvalue { i8*, i64 } %call, 1, !dbg !2209
  store i64 %12, i64* %11, align 8, !dbg !2209
  %13 = bitcast %struct.uv_buf_t* %buf to i8*, !dbg !2209
  %14 = bitcast %struct.uv_buf_t* %coerce to i8*, !dbg !2209
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* %14, i64 16, i32 8, i1 false), !dbg !2211
  %15 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2213
  %alloc_cb5 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %15, i32 0, i32 10, !dbg !2214
  %16 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb5, align 8, !dbg !2214
  %17 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2215
  %18 = bitcast %struct.uv_udp_s* %17 to %struct.uv_handle_s*, !dbg !2216
  call void %16(%struct.uv_handle_s* %18, i64 65536, %struct.uv_buf_t* %buf), !dbg !2213
  %base = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 0, !dbg !2217
  %19 = load i8*, i8** %base, align 8, !dbg !2217
  %cmp6 = icmp eq i8* %19, null, !dbg !2219
  br i1 %cmp6, label %if.then, label %lor.lhs.false, !dbg !2220

lor.lhs.false:                                    ; preds = %do.body
  %len = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 1, !dbg !2221
  %20 = load i64, i64* %len, align 8, !dbg !2221
  %cmp7 = icmp eq i64 %20, 0, !dbg !2223
  br i1 %cmp7, label %if.then, label %if.end, !dbg !2224

if.then:                                          ; preds = %lor.lhs.false, %do.body
  %21 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2225
  %recv_cb8 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %21, i32 0, i32 11, !dbg !2227
  %22 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb8, align 8, !dbg !2227
  %23 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2228
  call void %22(%struct.uv_udp_s* %23, i64 -105, %struct.uv_buf_t* %buf, %struct.sockaddr* null, i32 0), !dbg !2225
  br label %do.end57, !dbg !2229

if.end:                                           ; preds = %lor.lhs.false
  %base9 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 0, !dbg !2230
  %24 = load i8*, i8** %base9, align 8, !dbg !2230
  %cmp10 = icmp ne i8* %24, null, !dbg !2230
  br i1 %cmp10, label %cond.true11, label %cond.false12, !dbg !2230

cond.true11:                                      ; preds = %if.end
  br label %cond.end13, !dbg !2231

cond.false12:                                     ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 177, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__udp_recvmsg, i32 0, i32 0)) #7, !dbg !2232
  unreachable, !dbg !2232
                                                  ; No predecessors!
  br label %cond.end13, !dbg !2234

cond.end13:                                       ; preds = %25, %cond.true11
  %msg_namelen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 1, !dbg !2236
  store i32 128, i32* %msg_namelen, align 8, !dbg !2237
  %26 = bitcast %struct.uv_buf_t* %buf to i8*, !dbg !2238
  %27 = bitcast i8* %26 to %struct.iovec*, !dbg !2238
  %msg_iov = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 2, !dbg !2239
  store %struct.iovec* %27, %struct.iovec** %msg_iov, align 8, !dbg !2240
  %msg_iovlen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 3, !dbg !2241
  store i64 1, i64* %msg_iovlen, align 8, !dbg !2242
  br label %do.body14, !dbg !2243

do.body14:                                        ; preds = %land.end, %cond.end13
  %28 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2244
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %28, i32 0, i32 12, !dbg !2246
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2247
  %29 = load i32, i32* %fd, align 8, !dbg !2247
  %call15 = call i64 @recvmsg(i32 %29, %struct.msghdr* %h, i32 0), !dbg !2248
  store i64 %call15, i64* %nread, align 8, !dbg !2249
  br label %do.cond, !dbg !2250

do.cond:                                          ; preds = %do.body14
  %30 = load i64, i64* %nread, align 8, !dbg !2251
  %cmp16 = icmp eq i64 %30, -1, !dbg !2252
  br i1 %cmp16, label %land.rhs, label %land.end, !dbg !2253

land.rhs:                                         ; preds = %do.cond
  %call17 = call i32* @__errno_location() #1, !dbg !2254
  %31 = load i32, i32* %call17, align 4, !dbg !2254
  %cmp18 = icmp eq i32 %31, 4, !dbg !2255
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %32 = phi i1 [ false, %do.cond ], [ %cmp18, %land.rhs ]
  br i1 %32, label %do.body14, label %do.end, !dbg !2256

do.end:                                           ; preds = %land.end
  %33 = load i64, i64* %nread, align 8, !dbg !2258
  %cmp19 = icmp eq i64 %33, -1, !dbg !2260
  br i1 %cmp19, label %if.then20, label %if.else31, !dbg !2261

if.then20:                                        ; preds = %do.end
  %call21 = call i32* @__errno_location() #1, !dbg !2262
  %34 = load i32, i32* %call21, align 4, !dbg !2262
  %cmp22 = icmp eq i32 %34, 11, !dbg !2265
  br i1 %cmp22, label %if.then26, label %lor.lhs.false23, !dbg !2266

lor.lhs.false23:                                  ; preds = %if.then20
  %call24 = call i32* @__errno_location() #1, !dbg !2267
  %35 = load i32, i32* %call24, align 4, !dbg !2267
  %cmp25 = icmp eq i32 %35, 11, !dbg !2269
  br i1 %cmp25, label %if.then26, label %if.else, !dbg !2270

if.then26:                                        ; preds = %lor.lhs.false23, %if.then20
  %36 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2271
  %recv_cb27 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %36, i32 0, i32 11, !dbg !2272
  %37 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb27, align 8, !dbg !2272
  %38 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2273
  call void %37(%struct.uv_udp_s* %38, i64 0, %struct.uv_buf_t* %buf, %struct.sockaddr* null, i32 0), !dbg !2271
  br label %if.end30, !dbg !2271

if.else:                                          ; preds = %lor.lhs.false23
  %39 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2274
  %recv_cb28 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %39, i32 0, i32 11, !dbg !2275
  %40 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb28, align 8, !dbg !2275
  %41 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2276
  %call29 = call i32* @__errno_location() #1, !dbg !2277
  %42 = load i32, i32* %call29, align 4, !dbg !2277
  %sub = sub nsw i32 0, %42, !dbg !2278
  %conv = sext i32 %sub to i64, !dbg !2278
  call void %40(%struct.uv_udp_s* %41, i64 %conv, %struct.uv_buf_t* %buf, %struct.sockaddr* null, i32 0), !dbg !2279
  br label %if.end30

if.end30:                                         ; preds = %if.else, %if.then26
  br label %if.end41, !dbg !2280

if.else31:                                        ; preds = %do.end
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr, metadata !2281, metadata !653), !dbg !2283
  %msg_namelen32 = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 1, !dbg !2284
  %43 = load i32, i32* %msg_namelen32, align 8, !dbg !2284
  %cmp33 = icmp eq i32 %43, 0, !dbg !2286
  br i1 %cmp33, label %if.then35, label %if.else36, !dbg !2287

if.then35:                                        ; preds = %if.else31
  store %struct.sockaddr* null, %struct.sockaddr** %addr, align 8, !dbg !2288
  br label %if.end37, !dbg !2289

if.else36:                                        ; preds = %if.else31
  %44 = bitcast %struct.sockaddr_storage* %peer to %struct.sockaddr*, !dbg !2290
  store %struct.sockaddr* %44, %struct.sockaddr** %addr, align 8, !dbg !2291
  br label %if.end37

if.end37:                                         ; preds = %if.else36, %if.then35
  store i32 0, i32* %flags, align 4, !dbg !2292
  %msg_flags = getelementptr inbounds %struct.msghdr, %struct.msghdr* %h, i32 0, i32 6, !dbg !2293
  %45 = load i32, i32* %msg_flags, align 8, !dbg !2293
  %and = and i32 %45, 32, !dbg !2295
  %tobool = icmp ne i32 %and, 0, !dbg !2295
  br i1 %tobool, label %if.then38, label %if.end39, !dbg !2296

if.then38:                                        ; preds = %if.end37
  %46 = load i32, i32* %flags, align 4, !dbg !2297
  %or = or i32 %46, 2, !dbg !2297
  store i32 %or, i32* %flags, align 4, !dbg !2297
  br label %if.end39, !dbg !2298

if.end39:                                         ; preds = %if.then38, %if.end37
  %47 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2299
  %recv_cb40 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %47, i32 0, i32 11, !dbg !2300
  %48 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb40, align 8, !dbg !2300
  %49 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2301
  %50 = load i64, i64* %nread, align 8, !dbg !2302
  %51 = load %struct.sockaddr*, %struct.sockaddr** %addr, align 8, !dbg !2303
  %52 = load i32, i32* %flags, align 4, !dbg !2304
  call void %48(%struct.uv_udp_s* %49, i64 %50, %struct.uv_buf_t* %buf, %struct.sockaddr* %51, i32 %52), !dbg !2299
  br label %if.end41

if.end41:                                         ; preds = %if.end39, %if.end30
  br label %do.cond42, !dbg !2305

do.cond42:                                        ; preds = %if.end41
  %53 = load i64, i64* %nread, align 8, !dbg !2306
  %cmp43 = icmp ne i64 %53, -1, !dbg !2307
  br i1 %cmp43, label %land.lhs.true, label %land.end56, !dbg !2308

land.lhs.true:                                    ; preds = %do.cond42
  %54 = load i32, i32* %count, align 4, !dbg !2309
  %dec = add nsw i32 %54, -1, !dbg !2309
  store i32 %dec, i32* %count, align 4, !dbg !2309
  %cmp45 = icmp sgt i32 %54, 0, !dbg !2310
  br i1 %cmp45, label %land.lhs.true47, label %land.end56, !dbg !2311

land.lhs.true47:                                  ; preds = %land.lhs.true
  %55 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2312
  %io_watcher48 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %55, i32 0, i32 12, !dbg !2313
  %fd49 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher48, i32 0, i32 5, !dbg !2314
  %56 = load i32, i32* %fd49, align 8, !dbg !2314
  %cmp50 = icmp ne i32 %56, -1, !dbg !2315
  br i1 %cmp50, label %land.rhs52, label %land.end56, !dbg !2316

land.rhs52:                                       ; preds = %land.lhs.true47
  %57 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2317
  %recv_cb53 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %57, i32 0, i32 11, !dbg !2318
  %58 = load void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)** %recv_cb53, align 8, !dbg !2318
  %cmp54 = icmp ne void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)* %58, null, !dbg !2319
  br label %land.end56

land.end56:                                       ; preds = %land.rhs52, %land.lhs.true47, %land.lhs.true, %do.cond42
  %59 = phi i1 [ false, %land.lhs.true47 ], [ false, %land.lhs.true ], [ false, %do.cond42 ], [ %cmp54, %land.rhs52 ]
  br i1 %59, label %do.body, label %do.end57, !dbg !2320

do.end57:                                         ; preds = %if.then, %land.end56
  ret void, !dbg !2321
}

declare { i8*, i64 } @uv_buf_init(i8*, i32) #2

declare i64 @recvmsg(i32, %struct.msghdr*, i32) #2

declare i32 @uv_inet_pton(i32, i8*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__setsockopt(%struct.uv_udp_s* %handle, i32 %option4, i32 %option6, i8* %val, i64 %size) #0 !dbg !644 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_udp_s*, align 8
  %option4.addr = alloca i32, align 4
  %option6.addr = alloca i32, align 4
  %val.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.uv_udp_s* %handle, %struct.uv_udp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_udp_s** %handle.addr, metadata !2322, metadata !653), !dbg !2323
  store i32 %option4, i32* %option4.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option4.addr, metadata !2324, metadata !653), !dbg !2325
  store i32 %option6, i32* %option6.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option6.addr, metadata !2326, metadata !653), !dbg !2327
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !2328, metadata !653), !dbg !2329
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2330, metadata !653), !dbg !2331
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2332, metadata !653), !dbg !2333
  %0 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2334
  %flags = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %0, i32 0, i32 7, !dbg !2336
  %1 = load i32, i32* %flags, align 8, !dbg !2336
  %and = and i32 %1, 65536, !dbg !2337
  %tobool = icmp ne i32 %and, 0, !dbg !2337
  br i1 %tobool, label %if.then, label %if.else, !dbg !2338

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2339
  %io_watcher = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %2, i32 0, i32 12, !dbg !2340
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2341
  %3 = load i32, i32* %fd, align 8, !dbg !2341
  %4 = load i32, i32* %option6.addr, align 4, !dbg !2342
  %5 = load i8*, i8** %val.addr, align 8, !dbg !2343
  %6 = load i64, i64* %size.addr, align 8, !dbg !2344
  %conv = trunc i64 %6 to i32, !dbg !2344
  %call = call i32 @setsockopt(i32 %3, i32 41, i32 %4, i8* %5, i32 %conv) #8, !dbg !2345
  store i32 %call, i32* %r, align 4, !dbg !2346
  br label %if.end, !dbg !2347

if.else:                                          ; preds = %entry
  %7 = load %struct.uv_udp_s*, %struct.uv_udp_s** %handle.addr, align 8, !dbg !2348
  %io_watcher1 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %7, i32 0, i32 12, !dbg !2349
  %fd2 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher1, i32 0, i32 5, !dbg !2350
  %8 = load i32, i32* %fd2, align 8, !dbg !2350
  %9 = load i32, i32* %option4.addr, align 4, !dbg !2351
  %10 = load i8*, i8** %val.addr, align 8, !dbg !2352
  %11 = load i64, i64* %size.addr, align 8, !dbg !2353
  %conv3 = trunc i64 %11 to i32, !dbg !2353
  %call4 = call i32 @setsockopt(i32 %8, i32 0, i32 %9, i8* %10, i32 %conv3) #8, !dbg !2354
  store i32 %call4, i32* %r, align 4, !dbg !2355
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %12 = load i32, i32* %r, align 4, !dbg !2356
  %tobool5 = icmp ne i32 %12, 0, !dbg !2356
  br i1 %tobool5, label %if.then6, label %if.end8, !dbg !2358

if.then6:                                         ; preds = %if.end
  %call7 = call i32* @__errno_location() #1, !dbg !2359
  %13 = load i32, i32* %call7, align 4, !dbg !2359
  %sub = sub nsw i32 0, %13, !dbg !2360
  store i32 %sub, i32* %retval, align 4, !dbg !2361
  br label %return, !dbg !2361

if.end8:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !2362
  br label %return, !dbg !2362

return:                                           ; preds = %if.end8, %if.then6
  %14 = load i32, i32* %retval, align 4, !dbg !2363
  ret i32 %14, !dbg !2363
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!649, !650}
!llvm.ident = !{!651}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !216, subprograms: !567)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/udp.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !33, !46, !51, !63, !91, !110, !114, !193}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 184, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24}
!6 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!7 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!8 = !DIEnumerator(name: "UV_CHECK", value: 2)
!9 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!10 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!11 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!12 = !DIEnumerator(name: "UV_IDLE", value: 6)
!13 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!14 = !DIEnumerator(name: "UV_POLL", value: 8)
!15 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!16 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!17 = !DIEnumerator(name: "UV_STREAM", value: 11)
!18 = !DIEnumerator(name: "UV_TCP", value: 12)
!19 = !DIEnumerator(name: "UV_TIMER", value: 13)
!20 = !DIEnumerator(name: "UV_TTY", value: 14)
!21 = !DIEnumerator(name: "UV_UDP", value: 15)
!22 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!23 = !DIEnumerator(name: "UV_FILE", value: 17)
!24 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !26, line: 57, size: 32, align: 32, elements: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!27 = !{!28, !29, !30, !31, !32}
!28 = !DIEnumerator(name: "UV__SIGNAL_ONE_SHOT", value: 524288)
!29 = !DIEnumerator(name: "UV__HANDLE_INTERNAL", value: 32768)
!30 = !DIEnumerator(name: "UV__HANDLE_ACTIVE", value: 16384)
!31 = !DIEnumerator(name: "UV__HANDLE_REF", value: 8192)
!32 = !DIEnumerator(name: "UV__HANDLE_CLOSING", value: 0)
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 193, size: 32, align: 32, elements: !34)
!34 = !{!35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45}
!35 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!36 = !DIEnumerator(name: "UV_REQ", value: 1)
!37 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!38 = !DIEnumerator(name: "UV_WRITE", value: 3)
!39 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!40 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!41 = !DIEnumerator(name: "UV_FS", value: 6)
!42 = !DIEnumerator(name: "UV_WORK", value: 7)
!43 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!44 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!45 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!46 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "uv_udp_flags", file: !4, line: 563, size: 32, align: 32, elements: !47)
!47 = !{!48, !49, !50}
!48 = !DIEnumerator(name: "UV_UDP_IPV6ONLY", value: 1)
!49 = !DIEnumerator(name: "UV_UDP_PARTIAL", value: 2)
!50 = !DIEnumerator(name: "UV_UDP_REUSEADDR", value: 4)
!51 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !52, line: 24, size: 32, align: 32, elements: !53)
!52 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!53 = !{!54, !55, !56, !57, !58, !59, !60, !61, !62}
!54 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!55 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!56 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!57 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!58 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!59 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!60 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!61 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!62 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!63 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !64, line: 40, size: 32, align: 32, elements: !65)
!64 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!65 = !{!66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90}
!66 = !DIEnumerator(name: "IPPROTO_IP", value: 0)
!67 = !DIEnumerator(name: "IPPROTO_ICMP", value: 1)
!68 = !DIEnumerator(name: "IPPROTO_IGMP", value: 2)
!69 = !DIEnumerator(name: "IPPROTO_IPIP", value: 4)
!70 = !DIEnumerator(name: "IPPROTO_TCP", value: 6)
!71 = !DIEnumerator(name: "IPPROTO_EGP", value: 8)
!72 = !DIEnumerator(name: "IPPROTO_PUP", value: 12)
!73 = !DIEnumerator(name: "IPPROTO_UDP", value: 17)
!74 = !DIEnumerator(name: "IPPROTO_IDP", value: 22)
!75 = !DIEnumerator(name: "IPPROTO_TP", value: 29)
!76 = !DIEnumerator(name: "IPPROTO_DCCP", value: 33)
!77 = !DIEnumerator(name: "IPPROTO_IPV6", value: 41)
!78 = !DIEnumerator(name: "IPPROTO_RSVP", value: 46)
!79 = !DIEnumerator(name: "IPPROTO_GRE", value: 47)
!80 = !DIEnumerator(name: "IPPROTO_ESP", value: 50)
!81 = !DIEnumerator(name: "IPPROTO_AH", value: 51)
!82 = !DIEnumerator(name: "IPPROTO_MTP", value: 92)
!83 = !DIEnumerator(name: "IPPROTO_BEETPH", value: 94)
!84 = !DIEnumerator(name: "IPPROTO_ENCAP", value: 98)
!85 = !DIEnumerator(name: "IPPROTO_PIM", value: 103)
!86 = !DIEnumerator(name: "IPPROTO_COMP", value: 108)
!87 = !DIEnumerator(name: "IPPROTO_SCTP", value: 132)
!88 = !DIEnumerator(name: "IPPROTO_UDPLITE", value: 136)
!89 = !DIEnumerator(name: "IPPROTO_RAW", value: 255)
!90 = !DIEnumerator(name: "IPPROTO_MAX", value: 256)
!91 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !92, line: 124, size: 32, align: 32, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!93 = !{!94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109}
!94 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!95 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!96 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!97 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!98 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!99 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!100 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!101 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!102 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!103 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!104 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!105 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!106 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!107 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!108 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!109 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!110 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 365, size: 32, align: 32, elements: !111)
!111 = !{!112, !113}
!112 = !DIEnumerator(name: "UV_LEAVE_GROUP", value: 0)
!113 = !DIEnumerator(name: "UV_JOIN_GROUP", value: 1)
!114 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !115)
!115 = !{!116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191, !192}
!116 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!117 = !DIEnumerator(name: "UV_EACCES", value: -13)
!118 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!119 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!120 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!121 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!122 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!123 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!124 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!125 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!126 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!127 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!128 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!129 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!130 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!131 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!132 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!133 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!134 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!135 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!136 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!137 = !DIEnumerator(name: "UV_EBADF", value: -9)
!138 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!139 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!140 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!141 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!142 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!143 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!144 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!145 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!146 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!147 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!148 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!149 = !DIEnumerator(name: "UV_EINTR", value: -4)
!150 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!151 = !DIEnumerator(name: "UV_EIO", value: -5)
!152 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!153 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!154 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!155 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!156 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!157 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!158 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!159 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!160 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!161 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!162 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!163 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!164 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!165 = !DIEnumerator(name: "UV_ENONET", value: -64)
!166 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!167 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!168 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!169 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!170 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!171 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!172 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!173 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!174 = !DIEnumerator(name: "UV_EPERM", value: -1)
!175 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!176 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!177 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!178 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!179 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!180 = !DIEnumerator(name: "UV_EROFS", value: -30)
!181 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!182 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!183 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!184 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!185 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!186 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!187 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!188 = !DIEnumerator(name: "UV_EOF", value: -4095)
!189 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!190 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!191 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!192 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!193 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !194, line: 171, size: 32, align: 32, elements: !195)
!194 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!195 = !{!196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215}
!196 = !DIEnumerator(name: "MSG_OOB", value: 1)
!197 = !DIEnumerator(name: "MSG_PEEK", value: 2)
!198 = !DIEnumerator(name: "MSG_DONTROUTE", value: 4)
!199 = !DIEnumerator(name: "MSG_TRYHARD", value: 4)
!200 = !DIEnumerator(name: "MSG_CTRUNC", value: 8)
!201 = !DIEnumerator(name: "MSG_PROXY", value: 16)
!202 = !DIEnumerator(name: "MSG_TRUNC", value: 32)
!203 = !DIEnumerator(name: "MSG_DONTWAIT", value: 64)
!204 = !DIEnumerator(name: "MSG_EOR", value: 128)
!205 = !DIEnumerator(name: "MSG_WAITALL", value: 256)
!206 = !DIEnumerator(name: "MSG_FIN", value: 512)
!207 = !DIEnumerator(name: "MSG_SYN", value: 1024)
!208 = !DIEnumerator(name: "MSG_CONFIRM", value: 2048)
!209 = !DIEnumerator(name: "MSG_RST", value: 4096)
!210 = !DIEnumerator(name: "MSG_ERRQUEUE", value: 8192)
!211 = !DIEnumerator(name: "MSG_NOSIGNAL", value: 16384)
!212 = !DIEnumerator(name: "MSG_MORE", value: 32768)
!213 = !DIEnumerator(name: "MSG_WAITFORONE", value: 65536)
!214 = !DIEnumerator(name: "MSG_FASTOPEN", value: 536870912)
!215 = !DIEnumerator(name: "MSG_CMSG_CLOEXEC", value: 1073741824)
!216 = !{!217, !225, !227, !469, !222, !518, !519, !328, !525, !543, !536, !565, !259, !240, !482}
!217 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!218 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !219)
!219 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !220, line: 21, baseType: !221)
!220 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!221 = !DICompositeType(tag: DW_TAG_array_type, baseType: !222, size: 128, align: 64, elements: !223)
!222 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!223 = !{!224}
!224 = !DISubrange(count: 2)
!225 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !226, size: 64, align: 64)
!226 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!227 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !228, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_send_t", file: !4, line: 229, baseType: !229)
!229 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_udp_send_s", file: !4, line: 606, size: 2560, align: 64, elements: !230)
!230 = !{!231, !232, !234, !235, !239, !497, !502, !503, !512, !513, !514, !515, !516}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !229, file: !4, line: 607, baseType: !222, size: 64, align: 64)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !229, file: !4, line: 607, baseType: !233, size: 32, align: 32, offset: 64)
!233 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !33)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !229, file: !4, line: 607, baseType: !221, size: 128, align: 64, offset: 128)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !229, file: !4, line: 607, baseType: !236, size: 256, align: 64, offset: 256)
!236 = !DICompositeType(tag: DW_TAG_array_type, baseType: !222, size: 256, align: 64, elements: !237)
!237 = !{!238}
!238 = !DISubrange(count: 4)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !229, file: !4, line: 608, baseType: !240, size: 64, align: 64, offset: 512)
!240 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !241, size: 64, align: 64)
!241 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_t", file: !4, line: 208, baseType: !242)
!242 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_udp_s", file: !4, line: 590, size: 1728, align: 64, elements: !243)
!243 = !{!244, !245, !445, !446, !447, !448, !453, !454, !455, !458, !459, !471, !494, !495, !496}
!244 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !242, file: !4, line: 591, baseType: !222, size: 64, align: 64)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !242, file: !4, line: 591, baseType: !246, size: 64, align: 64, offset: 64)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !248)
!248 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !249)
!249 = !{!250, !251, !253, !254, !255, !256, !258, !260, !261, !262, !281, !282, !283, !284, !315, !360, !384, !385, !386, !387, !388, !389, !390, !394, !395, !396, !401, !404, !405, !407, !408, !441, !442, !443, !444}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !248, file: !4, line: 1475, baseType: !222, size: 64, align: 64)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !248, file: !4, line: 1477, baseType: !252, size: 32, align: 32, offset: 64)
!252 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !248, file: !4, line: 1478, baseType: !221, size: 128, align: 64, offset: 128)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !248, file: !4, line: 1479, baseType: !221, size: 128, align: 64, offset: 256)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !248, file: !4, line: 1481, baseType: !252, size: 32, align: 32, offset: 384)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !248, file: !4, line: 1482, baseType: !257, size: 64, align: 64, offset: 448)
!257 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !248, file: !4, line: 1482, baseType: !259, size: 32, align: 32, offset: 512)
!259 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 576)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 704)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !248, file: !4, line: 1482, baseType: !263, size: 64, align: 64, offset: 832)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !266, line: 87, baseType: !267)
!266 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!267 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !266, line: 89, size: 448, align: 64, elements: !268)
!268 = !{!269, !276, !277, !278, !279, !280}
!269 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !267, file: !266, line: 90, baseType: !270, size: 64, align: 64)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !266, line: 84, baseType: !271)
!271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !272, size: 64, align: 64)
!272 = !DISubroutineType(types: !273)
!273 = !{null, !274, !275, !252}
!274 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!275 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !267, size: 64, align: 64)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !267, file: !266, line: 91, baseType: !221, size: 128, align: 64, offset: 64)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !267, file: !266, line: 92, baseType: !221, size: 128, align: 64, offset: 192)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !267, file: !266, line: 93, baseType: !252, size: 32, align: 32, offset: 320)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !267, file: !266, line: 94, baseType: !252, size: 32, align: 32, offset: 352)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !267, file: !266, line: 95, baseType: !259, size: 32, align: 32, offset: 384)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !248, file: !4, line: 1482, baseType: !252, size: 32, align: 32, offset: 896)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !248, file: !4, line: 1482, baseType: !252, size: 32, align: 32, offset: 928)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 960)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !248, file: !4, line: 1482, baseType: !285, size: 320, align: 64, offset: 1088)
!285 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !266, line: 129, baseType: !286)
!286 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !287, line: 127, baseType: !288)
!287 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!288 = !DICompositeType(tag: DW_TAG_union_type, file: !287, line: 90, size: 320, align: 64, elements: !289)
!289 = !{!290, !308, !313}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !288, file: !287, line: 124, baseType: !291, size: 320, align: 64)
!291 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !287, line: 92, size: 320, align: 64, elements: !292)
!292 = !{!293, !294, !295, !296, !297, !298, !300, !301}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !291, file: !287, line: 94, baseType: !259, size: 32, align: 32)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !291, file: !287, line: 95, baseType: !252, size: 32, align: 32, offset: 32)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !291, file: !287, line: 96, baseType: !259, size: 32, align: 32, offset: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !291, file: !287, line: 98, baseType: !252, size: 32, align: 32, offset: 96)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !291, file: !287, line: 102, baseType: !259, size: 32, align: 32, offset: 128)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !291, file: !287, line: 104, baseType: !299, size: 16, align: 16, offset: 160)
!299 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !291, file: !287, line: 105, baseType: !299, size: 16, align: 16, offset: 176)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !291, file: !287, line: 106, baseType: !302, size: 128, align: 64, offset: 192)
!302 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !287, line: 79, baseType: !303)
!303 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !287, line: 75, size: 128, align: 64, elements: !304)
!304 = !{!305, !307}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !303, file: !287, line: 77, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !303, file: !287, line: 78, baseType: !306, size: 64, align: 64, offset: 64)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !288, file: !287, line: 125, baseType: !309, size: 320, align: 8)
!309 = !DICompositeType(tag: DW_TAG_array_type, baseType: !310, size: 320, align: 8, elements: !311)
!310 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!311 = !{!312}
!312 = !DISubrange(count: 40)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !288, file: !287, line: 126, baseType: !314, size: 64, align: 64)
!314 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !248, file: !4, line: 1482, baseType: !316, size: 1024, align: 64, offset: 1408)
!316 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !317)
!317 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !318)
!318 = !{!319, !320, !321, !323, !344, !345, !350, !351, !352, !358, !359}
!319 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !317, file: !4, line: 768, baseType: !222, size: 64, align: 64)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !317, file: !4, line: 768, baseType: !246, size: 64, align: 64, offset: 64)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !317, file: !4, line: 768, baseType: !322, size: 32, align: 32, offset: 128)
!322 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !317, file: !4, line: 768, baseType: !324, size: 64, align: 64, offset: 192)
!324 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !325)
!325 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !326, size: 64, align: 64)
!326 = !DISubroutineType(types: !327)
!327 = !{null, !328}
!328 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !329, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !330)
!330 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !331)
!331 = !{!332, !333, !334, !335, !336, !337, !342, !343}
!332 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !330, file: !4, line: 426, baseType: !222, size: 64, align: 64)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !330, file: !4, line: 426, baseType: !246, size: 64, align: 64, offset: 64)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !330, file: !4, line: 426, baseType: !322, size: 32, align: 32, offset: 128)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !330, file: !4, line: 426, baseType: !324, size: 64, align: 64, offset: 192)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !330, file: !4, line: 426, baseType: !221, size: 128, align: 64, offset: 256)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !330, file: !4, line: 426, baseType: !338, size: 256, align: 64, offset: 384)
!338 = !DICompositeType(tag: DW_TAG_union_type, scope: !330, file: !4, line: 426, size: 256, align: 64, elements: !339)
!339 = !{!340, !341}
!340 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !338, file: !4, line: 426, baseType: !259, size: 32, align: 32)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !338, file: !4, line: 426, baseType: !236, size: 256, align: 64)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !330, file: !4, line: 426, baseType: !328, size: 64, align: 64, offset: 640)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !330, file: !4, line: 426, baseType: !252, size: 32, align: 32, offset: 704)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !317, file: !4, line: 768, baseType: !221, size: 128, align: 64, offset: 256)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !317, file: !4, line: 768, baseType: !346, size: 256, align: 64, offset: 384)
!346 = !DICompositeType(tag: DW_TAG_union_type, scope: !317, file: !4, line: 768, size: 256, align: 64, elements: !347)
!347 = !{!348, !349}
!348 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !346, file: !4, line: 768, baseType: !259, size: 32, align: 32)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !346, file: !4, line: 768, baseType: !236, size: 256, align: 64)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !317, file: !4, line: 768, baseType: !328, size: 64, align: 64, offset: 640)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !317, file: !4, line: 768, baseType: !252, size: 32, align: 32, offset: 704)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !317, file: !4, line: 769, baseType: !353, size: 64, align: 64, offset: 768)
!353 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !354)
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !355, size: 64, align: 64)
!355 = !DISubroutineType(types: !356)
!356 = !{null, !357}
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !316, size: 64, align: 64)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !317, file: !4, line: 769, baseType: !221, size: 128, align: 64, offset: 832)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !317, file: !4, line: 769, baseType: !259, size: 32, align: 32, offset: 960)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !248, file: !4, line: 1482, baseType: !361, size: 448, align: 64, offset: 2432)
!361 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !266, line: 130, baseType: !362)
!362 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !287, line: 213, baseType: !363)
!363 = !DICompositeType(tag: DW_TAG_union_type, file: !287, line: 173, size: 448, align: 64, elements: !364)
!364 = !{!365, !379, !383}
!365 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !363, file: !287, line: 192, baseType: !366, size: 448, align: 64)
!366 = !DICompositeType(tag: DW_TAG_structure_type, scope: !363, file: !287, line: 176, size: 448, align: 64, elements: !367)
!367 = !{!368, !369, !370, !371, !372, !373, !374, !375, !376, !377, !378}
!368 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !366, file: !287, line: 178, baseType: !259, size: 32, align: 32)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !366, file: !287, line: 179, baseType: !252, size: 32, align: 32, offset: 32)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !366, file: !287, line: 180, baseType: !252, size: 32, align: 32, offset: 64)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !366, file: !287, line: 181, baseType: !252, size: 32, align: 32, offset: 96)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !366, file: !287, line: 182, baseType: !252, size: 32, align: 32, offset: 128)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !366, file: !287, line: 183, baseType: !252, size: 32, align: 32, offset: 160)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !366, file: !287, line: 184, baseType: !259, size: 32, align: 32, offset: 192)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !366, file: !287, line: 185, baseType: !259, size: 32, align: 32, offset: 224)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !366, file: !287, line: 186, baseType: !257, size: 64, align: 64, offset: 256)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !366, file: !287, line: 187, baseType: !257, size: 64, align: 64, offset: 320)
!378 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !366, file: !287, line: 190, baseType: !252, size: 32, align: 32, offset: 384)
!379 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !363, file: !287, line: 211, baseType: !380, size: 448, align: 8)
!380 = !DICompositeType(tag: DW_TAG_array_type, baseType: !310, size: 448, align: 8, elements: !381)
!381 = !{!382}
!382 = !DISubrange(count: 56)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !363, file: !287, line: 212, baseType: !314, size: 64, align: 64)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !248, file: !4, line: 1482, baseType: !328, size: 64, align: 64, offset: 2880)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 2944)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 3072)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 3200)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 3328)
!389 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !248, file: !4, line: 1482, baseType: !221, size: 128, align: 64, offset: 3456)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !248, file: !4, line: 1482, baseType: !391, size: 64, align: 64, offset: 3584)
!391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !392, size: 64, align: 64)
!392 = !DISubroutineType(types: !393)
!393 = !{null}
!394 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !248, file: !4, line: 1482, baseType: !265, size: 448, align: 64, offset: 3648)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !248, file: !4, line: 1482, baseType: !259, size: 32, align: 32, offset: 4096)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !248, file: !4, line: 1482, baseType: !397, size: 128, align: 64, offset: 4160)
!397 = !DICompositeType(tag: DW_TAG_structure_type, scope: !248, file: !4, line: 1482, size: 128, align: 64, elements: !398)
!398 = !{!399, !400}
!399 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !397, file: !4, line: 1482, baseType: !222, size: 64, align: 64)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !397, file: !4, line: 1482, baseType: !252, size: 32, align: 32, offset: 64)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !248, file: !4, line: 1482, baseType: !402, size: 64, align: 64, offset: 4288)
!402 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !403, line: 55, baseType: !257)
!403 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!404 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !248, file: !4, line: 1482, baseType: !402, size: 64, align: 64, offset: 4352)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !248, file: !4, line: 1482, baseType: !406, size: 64, align: 32, offset: 4416)
!406 = !DICompositeType(tag: DW_TAG_array_type, baseType: !259, size: 64, align: 32, elements: !223)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !248, file: !4, line: 1482, baseType: !265, size: 448, align: 64, offset: 4480)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !248, file: !4, line: 1482, baseType: !409, size: 1216, align: 64, offset: 4928)
!409 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !410)
!410 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !411)
!411 = !{!412, !413, !414, !415, !416, !417, !422, !423, !424, !430, !431, !439, !440}
!412 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !410, file: !4, line: 1326, baseType: !222, size: 64, align: 64)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !410, file: !4, line: 1326, baseType: !246, size: 64, align: 64, offset: 64)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !410, file: !4, line: 1326, baseType: !322, size: 32, align: 32, offset: 128)
!415 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !410, file: !4, line: 1326, baseType: !324, size: 64, align: 64, offset: 192)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !410, file: !4, line: 1326, baseType: !221, size: 128, align: 64, offset: 256)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !410, file: !4, line: 1326, baseType: !418, size: 256, align: 64, offset: 384)
!418 = !DICompositeType(tag: DW_TAG_union_type, scope: !410, file: !4, line: 1326, size: 256, align: 64, elements: !419)
!419 = !{!420, !421}
!420 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !418, file: !4, line: 1326, baseType: !259, size: 32, align: 32)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !418, file: !4, line: 1326, baseType: !236, size: 256, align: 64)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !410, file: !4, line: 1326, baseType: !328, size: 64, align: 64, offset: 640)
!423 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !410, file: !4, line: 1326, baseType: !252, size: 32, align: 32, offset: 704)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !410, file: !4, line: 1327, baseType: !425, size: 64, align: 64, offset: 768)
!425 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !426)
!426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !427, size: 64, align: 64)
!427 = !DISubroutineType(types: !428)
!428 = !{null, !429, !259}
!429 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !409, size: 64, align: 64)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !410, file: !4, line: 1328, baseType: !259, size: 32, align: 32, offset: 832)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !410, file: !4, line: 1329, baseType: !432, size: 256, align: 64, offset: 896)
!432 = !DICompositeType(tag: DW_TAG_structure_type, scope: !410, file: !4, line: 1329, size: 256, align: 64, elements: !433)
!433 = !{!434, !436, !437, !438}
!434 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !432, file: !4, line: 1329, baseType: !435, size: 64, align: 64)
!435 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !410, size: 64, align: 64)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !432, file: !4, line: 1329, baseType: !435, size: 64, align: 64, offset: 64)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !432, file: !4, line: 1329, baseType: !435, size: 64, align: 64, offset: 128)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !432, file: !4, line: 1329, baseType: !259, size: 32, align: 32, offset: 192)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !410, file: !4, line: 1329, baseType: !252, size: 32, align: 32, offset: 1152)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !410, file: !4, line: 1329, baseType: !252, size: 32, align: 32, offset: 1184)
!441 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !248, file: !4, line: 1482, baseType: !259, size: 32, align: 32, offset: 6144)
!442 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !248, file: !4, line: 1482, baseType: !265, size: 448, align: 64, offset: 6208)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !248, file: !4, line: 1482, baseType: !222, size: 64, align: 64, offset: 6656)
!444 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !248, file: !4, line: 1482, baseType: !259, size: 32, align: 32, offset: 6720)
!445 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !242, file: !4, line: 591, baseType: !322, size: 32, align: 32, offset: 128)
!446 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !242, file: !4, line: 591, baseType: !324, size: 64, align: 64, offset: 192)
!447 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !242, file: !4, line: 591, baseType: !221, size: 128, align: 64, offset: 256)
!448 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !242, file: !4, line: 591, baseType: !449, size: 256, align: 64, offset: 384)
!449 = !DICompositeType(tag: DW_TAG_union_type, scope: !242, file: !4, line: 591, size: 256, align: 64, elements: !450)
!450 = !{!451, !452}
!451 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !449, file: !4, line: 591, baseType: !259, size: 32, align: 32)
!452 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !449, file: !4, line: 591, baseType: !236, size: 256, align: 64)
!453 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !242, file: !4, line: 591, baseType: !328, size: 64, align: 64, offset: 640)
!454 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !242, file: !4, line: 591, baseType: !252, size: 32, align: 32, offset: 704)
!455 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_size", scope: !242, file: !4, line: 597, baseType: !456, size: 64, align: 64, offset: 768)
!456 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !457, line: 62, baseType: !257)
!457 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!458 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_count", scope: !242, file: !4, line: 601, baseType: !456, size: 64, align: 64, offset: 832)
!459 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !242, file: !4, line: 602, baseType: !460, size: 64, align: 64, offset: 896)
!460 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !4, line: 296, baseType: !461)
!461 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !462, size: 64, align: 64)
!462 = !DISubroutineType(types: !463)
!463 = !{null, !328, !456, !464}
!464 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !465, size: 64, align: 64)
!465 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !266, line: 119, baseType: !466)
!466 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !266, line: 116, size: 128, align: 64, elements: !467)
!467 = !{!468, !470}
!468 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !466, file: !266, line: 117, baseType: !469, size: 64, align: 64)
!469 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !310, size: 64, align: 64)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !466, file: !266, line: 118, baseType: !456, size: 64, align: 64, offset: 64)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "recv_cb", scope: !242, file: !4, line: 602, baseType: !472, size: 64, align: 64, offset: 960)
!472 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_recv_cb", file: !4, line: 583, baseType: !473)
!473 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !474, size: 64, align: 64)
!474 = !DISubroutineType(types: !475)
!475 = !{null, !240, !476, !480, !482, !252}
!476 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !477, line: 102, baseType: !478)
!477 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!478 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !479, line: 172, baseType: !314)
!479 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!480 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !481, size: 64, align: 64)
!481 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !465)
!482 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !483, size: 64, align: 64)
!483 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !484)
!484 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !194, line: 149, size: 128, align: 16, elements: !485)
!485 = !{!486, !490}
!486 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !484, file: !194, line: 151, baseType: !487, size: 16, align: 16)
!487 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !488, line: 28, baseType: !489)
!488 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!489 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !484, file: !194, line: 152, baseType: !491, size: 112, align: 8, offset: 16)
!491 = !DICompositeType(tag: DW_TAG_array_type, baseType: !310, size: 112, align: 8, elements: !492)
!492 = !{!493}
!493 = !DISubrange(count: 14)
!494 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !242, file: !4, line: 602, baseType: !265, size: 448, align: 64, offset: 1024)
!495 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !242, file: !4, line: 602, baseType: !221, size: 128, align: 64, offset: 1472)
!496 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !242, file: !4, line: 602, baseType: !221, size: 128, align: 64, offset: 1600)
!497 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !229, file: !4, line: 609, baseType: !498, size: 64, align: 64, offset: 576)
!498 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_send_cb", file: !4, line: 582, baseType: !499)
!499 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !500, size: 64, align: 64)
!500 = !DISubroutineType(types: !501)
!501 = !{null, !227, !259}
!502 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !229, file: !4, line: 610, baseType: !221, size: 128, align: 64, offset: 640)
!503 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !229, file: !4, line: 610, baseType: !504, size: 1024, align: 64, offset: 768)
!504 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !194, line: 162, size: 1024, align: 64, elements: !505)
!505 = !{!506, !507, !508}
!506 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !504, file: !194, line: 164, baseType: !487, size: 16, align: 16)
!507 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !504, file: !194, line: 165, baseType: !257, size: 64, align: 64, offset: 64)
!508 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_padding", scope: !504, file: !194, line: 166, baseType: !509, size: 896, align: 8, offset: 128)
!509 = !DICompositeType(tag: DW_TAG_array_type, baseType: !310, size: 896, align: 8, elements: !510)
!510 = !{!511}
!511 = !DISubrange(count: 112)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !229, file: !4, line: 610, baseType: !252, size: 32, align: 32, offset: 1792)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !229, file: !4, line: 610, baseType: !464, size: 64, align: 64, offset: 1856)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !229, file: !4, line: 610, baseType: !476, size: 64, align: 64, offset: 1920)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "send_cb", scope: !229, file: !4, line: 610, baseType: !498, size: 64, align: 64, offset: 1984)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !229, file: !4, line: 610, baseType: !517, size: 512, align: 64, offset: 2048)
!517 = !DICompositeType(tag: DW_TAG_array_type, baseType: !465, size: 512, align: 64, elements: !237)
!518 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !484, size: 64, align: 64)
!519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !520, size: 64, align: 64)
!520 = !DICompositeType(tag: DW_TAG_structure_type, name: "iovec", file: !521, line: 43, size: 128, align: 64, elements: !522)
!521 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/uio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!522 = !{!523, !524}
!523 = !DIDerivedType(tag: DW_TAG_member, name: "iov_base", scope: !520, file: !521, line: 45, baseType: !222, size: 64, align: 64)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "iov_len", scope: !520, file: !521, line: 46, baseType: !456, size: 64, align: 64, offset: 64)
!525 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !526, size: 64, align: 64)
!526 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !64, line: 237, size: 128, align: 32, elements: !527)
!527 = !{!528, !529, !532, !538}
!528 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !526, file: !64, line: 239, baseType: !487, size: 16, align: 16)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !526, file: !64, line: 240, baseType: !530, size: 16, align: 16, offset: 16)
!530 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !64, line: 117, baseType: !531)
!531 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !403, line: 49, baseType: !489)
!532 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !526, file: !64, line: 241, baseType: !533, size: 32, align: 32, offset: 32)
!533 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !64, line: 31, size: 32, align: 32, elements: !534)
!534 = !{!535}
!535 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !533, file: !64, line: 33, baseType: !536, size: 32, align: 32)
!536 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !64, line: 30, baseType: !537)
!537 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !403, line: 51, baseType: !252)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !526, file: !64, line: 244, baseType: !539, size: 64, align: 8, offset: 64)
!539 = !DICompositeType(tag: DW_TAG_array_type, baseType: !540, size: 64, align: 8, elements: !541)
!540 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!541 = !{!542}
!542 = !DISubrange(count: 8)
!543 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !544, size: 64, align: 64)
!544 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in6", file: !64, line: 252, size: 224, align: 32, elements: !545)
!545 = !{!546, !547, !548, !549, !564}
!546 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_family", scope: !544, file: !64, line: 254, baseType: !487, size: 16, align: 16)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_port", scope: !544, file: !64, line: 255, baseType: !530, size: 16, align: 16, offset: 16)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_flowinfo", scope: !544, file: !64, line: 256, baseType: !537, size: 32, align: 32, offset: 32)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_addr", scope: !544, file: !64, line: 257, baseType: !550, size: 128, align: 32, offset: 64)
!550 = !DICompositeType(tag: DW_TAG_structure_type, name: "in6_addr", file: !64, line: 209, size: 128, align: 32, elements: !551)
!551 = !{!552}
!552 = !DIDerivedType(tag: DW_TAG_member, name: "__in6_u", scope: !550, file: !64, line: 218, baseType: !553, size: 128, align: 32)
!553 = !DICompositeType(tag: DW_TAG_union_type, scope: !550, file: !64, line: 211, size: 128, align: 32, elements: !554)
!554 = !{!555, !560, !562}
!555 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr8", scope: !553, file: !64, line: 213, baseType: !556, size: 128, align: 8)
!556 = !DICompositeType(tag: DW_TAG_array_type, baseType: !557, size: 128, align: 8, elements: !558)
!557 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !403, line: 48, baseType: !540)
!558 = !{!559}
!559 = !DISubrange(count: 16)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr16", scope: !553, file: !64, line: 215, baseType: !561, size: 128, align: 16)
!561 = !DICompositeType(tag: DW_TAG_array_type, baseType: !531, size: 128, align: 16, elements: !541)
!562 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr32", scope: !553, file: !64, line: 216, baseType: !563, size: 128, align: 32)
!563 = !DICompositeType(tag: DW_TAG_array_type, baseType: !537, size: 128, align: 32, elements: !237)
!564 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_scope_id", scope: !544, file: !64, line: 258, baseType: !537, size: 32, align: 32, offset: 192)
!565 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !194, line: 33, baseType: !566)
!566 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !479, line: 189, baseType: !252)
!567 = !{!568, !572, !573, !576, !579, !582, !585, !588, !592, !598, !601, !602, !603, !604, !607, !613, !616, !619, !620, !623, !626, !627, !630, !631, !636, !641, !644}
!568 = distinct !DISubprogram(name: "uv__udp_close", scope: !1, file: !1, line: 52, type: !569, isLocal: false, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!569 = !DISubroutineType(types: !570)
!570 = !{null, !240}
!571 = !{}
!572 = distinct !DISubprogram(name: "uv__udp_finish_close", scope: !1, file: !1, line: 63, type: !569, isLocal: false, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!573 = distinct !DISubprogram(name: "uv__udp_bind", scope: !1, file: !1, line: 282, type: !574, isLocal: false, isDefinition: true, scopeLine: 285, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!574 = !DISubroutineType(types: !575)
!575 = !{!259, !240, !482, !252, !252}
!576 = distinct !DISubprogram(name: "uv__udp_send", scope: !1, file: !1, line: 384, type: !577, isLocal: false, isDefinition: true, scopeLine: 390, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!577 = !DISubroutineType(types: !578)
!578 = !{!259, !227, !240, !480, !252, !482, !252, !498}
!579 = distinct !DISubprogram(name: "uv__udp_try_send", scope: !1, file: !1, line: 445, type: !580, isLocal: false, isDefinition: true, scopeLine: 449, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!580 = !DISubroutineType(types: !581)
!581 = !{!259, !240, !480, !252, !482, !252}
!582 = distinct !DISubprogram(name: "uv_udp_init_ex", scope: !1, file: !1, line: 579, type: !583, isLocal: false, isDefinition: true, scopeLine: 579, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!583 = !DISubroutineType(types: !584)
!584 = !{!259, !246, !240, !252}
!585 = distinct !DISubprogram(name: "uv_udp_init", scope: !1, file: !1, line: 613, type: !586, isLocal: false, isDefinition: true, scopeLine: 613, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!586 = !DISubroutineType(types: !587)
!587 = !{!259, !246, !240}
!588 = distinct !DISubprogram(name: "uv_udp_open", scope: !1, file: !1, line: 618, type: !589, isLocal: false, isDefinition: true, scopeLine: 618, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!589 = !DISubroutineType(types: !590)
!590 = !{!259, !240, !591}
!591 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_os_sock_t", file: !266, line: 122, baseType: !259)
!592 = distinct !DISubprogram(name: "uv_udp_set_membership", scope: !1, file: !1, line: 638, type: !593, isLocal: false, isDefinition: true, scopeLine: 641, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!593 = !DISubroutineType(types: !594)
!594 = !{!259, !240, !595, !595, !597}
!595 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !596, size: 64, align: 64)
!596 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !310)
!597 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_membership", file: !4, line: 368, baseType: !110)
!598 = distinct !DISubprogram(name: "uv_udp_set_broadcast", scope: !1, file: !1, line: 705, type: !599, isLocal: false, isDefinition: true, scopeLine: 705, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!599 = !DISubroutineType(types: !600)
!600 = !{!259, !240, !259}
!601 = distinct !DISubprogram(name: "uv_udp_set_ttl", scope: !1, file: !1, line: 718, type: !599, isLocal: false, isDefinition: true, scopeLine: 718, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!602 = distinct !DISubprogram(name: "uv_udp_set_multicast_ttl", scope: !1, file: !1, line: 751, type: !599, isLocal: false, isDefinition: true, scopeLine: 751, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!603 = distinct !DISubprogram(name: "uv_udp_set_multicast_loop", scope: !1, file: !1, line: 774, type: !599, isLocal: false, isDefinition: true, scopeLine: 774, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!604 = distinct !DISubprogram(name: "uv_udp_set_multicast_interface", scope: !1, file: !1, line: 796, type: !605, isLocal: false, isDefinition: true, scopeLine: 796, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!605 = !DISubroutineType(types: !606)
!606 = !{!259, !240, !595}
!607 = distinct !DISubprogram(name: "uv_udp_getsockname", scope: !1, file: !1, line: 846, type: !608, isLocal: false, isDefinition: true, scopeLine: 848, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!608 = !DISubroutineType(types: !609)
!609 = !{!259, !610, !518, !612}
!610 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !611, size: 64, align: 64)
!611 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !241)
!612 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !259, size: 64, align: 64)
!613 = distinct !DISubprogram(name: "uv__udp_recv_start", scope: !1, file: !1, line: 865, type: !614, isLocal: false, isDefinition: true, scopeLine: 867, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!614 = !DISubroutineType(types: !615)
!615 = !{!259, !240, !460, !472}
!616 = distinct !DISubprogram(name: "uv__udp_recv_stop", scope: !1, file: !1, line: 890, type: !617, isLocal: false, isDefinition: true, scopeLine: 890, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!617 = !DISubroutineType(types: !618)
!618 = !{!259, !240}
!619 = distinct !DISubprogram(name: "uv__udp_run_completed", scope: !1, file: !1, line: 91, type: !569, isLocal: true, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!620 = distinct !DISubprogram(name: "uv__set_reuse", scope: !1, file: !1, line: 265, type: !621, isLocal: true, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!621 = !DISubroutineType(types: !622)
!622 = !{!259, !259}
!623 = distinct !DISubprogram(name: "uv__udp_maybe_deferred_bind", scope: !1, file: !1, line: 343, type: !624, isLocal: true, isDefinition: true, scopeLine: 345, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!624 = !DISubroutineType(types: !625)
!625 = !{!259, !240, !259, !252}
!626 = distinct !DISubprogram(name: "uv__udp_sendmsg", scope: !1, file: !1, line: 216, type: !569, isLocal: true, isDefinition: true, scopeLine: 216, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!627 = distinct !DISubprogram(name: "uv__udp_io", scope: !1, file: !1, line: 135, type: !628, isLocal: true, isDefinition: true, scopeLine: 135, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!628 = !DISubroutineType(types: !629)
!629 = !{null, !246, !264, !252}
!630 = distinct !DISubprogram(name: "uv__udp_recvmsg", scope: !1, file: !1, line: 151, type: !569, isLocal: true, isDefinition: true, scopeLine: 151, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!631 = distinct !DISubprogram(name: "uv__udp_set_membership4", scope: !1, file: !1, line: 485, type: !632, isLocal: true, isDefinition: true, scopeLine: 488, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!632 = !DISubroutineType(types: !633)
!633 = !{!259, !240, !634, !595, !597}
!634 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !635, size: 64, align: 64)
!635 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !526)
!636 = distinct !DISubprogram(name: "uv__udp_set_membership6", scope: !1, file: !1, line: 532, type: !637, isLocal: true, isDefinition: true, scopeLine: 535, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!637 = !DISubroutineType(types: !638)
!638 = !{!259, !240, !639, !595, !597}
!639 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !640, size: 64, align: 64)
!640 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !544)
!641 = distinct !DISubprogram(name: "uv__setsockopt_maybe_char", scope: !1, file: !1, line: 686, type: !642, isLocal: true, isDefinition: true, scopeLine: 689, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!642 = !DISubroutineType(types: !643)
!643 = !{!259, !240, !259, !259, !259}
!644 = distinct !DISubprogram(name: "uv__setsockopt", scope: !1, file: !1, line: 661, type: !645, isLocal: true, isDefinition: true, scopeLine: 665, flags: DIFlagPrototyped, isOptimized: false, variables: !571)
!645 = !DISubroutineType(types: !646)
!646 = !{!259, !240, !259, !259, !647, !456}
!647 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !648, size: 64, align: 64)
!648 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!649 = !{i32 2, !"Dwarf Version", i32 4}
!650 = !{i32 2, !"Debug Info Version", i32 3}
!651 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!652 = !DILocalVariable(name: "handle", arg: 1, scope: !568, file: !1, line: 52, type: !240)
!653 = !DIExpression()
!654 = !DILocation(line: 52, column: 30, scope: !568)
!655 = !DILocation(line: 53, column: 16, scope: !568)
!656 = !DILocation(line: 53, column: 24, scope: !568)
!657 = !DILocation(line: 53, column: 31, scope: !568)
!658 = !DILocation(line: 53, column: 39, scope: !568)
!659 = !DILocation(line: 53, column: 3, scope: !568)
!660 = !DILocation(line: 54, column: 3, scope: !568)
!661 = !DILocation(line: 54, column: 3, scope: !662)
!662 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 1)
!663 = distinct !DILexicalBlock(scope: !568, file: !1, line: 54, column: 3)
!664 = !DILocation(line: 54, column: 3, scope: !665)
!665 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 2)
!666 = !DILocation(line: 54, column: 3, scope: !667)
!667 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 3)
!668 = !DILocation(line: 54, column: 3, scope: !669)
!669 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 4)
!670 = !DILocation(line: 54, column: 3, scope: !671)
!671 = !DILexicalBlockFile(scope: !672, file: !1, discriminator: 5)
!672 = distinct !DILexicalBlock(scope: !663, file: !1, line: 54, column: 3)
!673 = !DILocation(line: 54, column: 3, scope: !674)
!674 = !DILexicalBlockFile(scope: !672, file: !1, discriminator: 6)
!675 = !DILocation(line: 54, column: 3, scope: !676)
!676 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 7)
!677 = !DILocation(line: 54, column: 3, scope: !678)
!678 = !DILexicalBlockFile(scope: !679, file: !1, discriminator: 8)
!679 = distinct !DILexicalBlock(scope: !663, file: !1, line: 54, column: 3)
!680 = !DILocation(line: 54, column: 3, scope: !681)
!681 = !DILexicalBlockFile(scope: !682, file: !1, discriminator: 9)
!682 = distinct !DILexicalBlock(scope: !679, file: !1, line: 54, column: 3)
!683 = !DILocation(line: 54, column: 3, scope: !684)
!684 = !DILexicalBlockFile(scope: !682, file: !1, discriminator: 10)
!685 = !DILocation(line: 54, column: 3, scope: !686)
!686 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 11)
!687 = !DILocation(line: 56, column: 7, scope: !688)
!688 = distinct !DILexicalBlock(scope: !568, file: !1, line: 56, column: 7)
!689 = !DILocation(line: 56, column: 15, scope: !688)
!690 = !DILocation(line: 56, column: 26, scope: !688)
!691 = !DILocation(line: 56, column: 29, scope: !688)
!692 = !DILocation(line: 56, column: 7, scope: !568)
!693 = !DILocation(line: 57, column: 15, scope: !694)
!694 = distinct !DILexicalBlock(scope: !688, file: !1, line: 56, column: 36)
!695 = !DILocation(line: 57, column: 23, scope: !694)
!696 = !DILocation(line: 57, column: 34, scope: !694)
!697 = !DILocation(line: 57, column: 5, scope: !694)
!698 = !DILocation(line: 58, column: 5, scope: !694)
!699 = !DILocation(line: 58, column: 13, scope: !694)
!700 = !DILocation(line: 58, column: 24, scope: !694)
!701 = !DILocation(line: 58, column: 27, scope: !694)
!702 = !DILocation(line: 59, column: 3, scope: !694)
!703 = !DILocation(line: 60, column: 1, scope: !568)
!704 = !DILocalVariable(name: "handle", arg: 1, scope: !572, file: !1, line: 63, type: !240)
!705 = !DILocation(line: 63, column: 37, scope: !572)
!706 = !DILocalVariable(name: "req", scope: !572, file: !1, line: 64, type: !227)
!707 = !DILocation(line: 64, column: 18, scope: !572)
!708 = !DILocalVariable(name: "q", scope: !572, file: !1, line: 65, type: !226)
!709 = !DILocation(line: 65, column: 10, scope: !572)
!710 = !DILocation(line: 67, column: 3, scope: !572)
!711 = !DILocation(line: 67, column: 3, scope: !712)
!712 = !DILexicalBlockFile(scope: !572, file: !1, discriminator: 1)
!713 = !DILocation(line: 67, column: 3, scope: !714)
!714 = !DILexicalBlockFile(scope: !572, file: !1, discriminator: 2)
!715 = !DILocation(line: 67, column: 3, scope: !716)
!716 = !DILexicalBlockFile(scope: !572, file: !1, discriminator: 3)
!717 = !DILocation(line: 68, column: 3, scope: !572)
!718 = !DILocation(line: 68, column: 3, scope: !712)
!719 = !DILocation(line: 68, column: 3, scope: !714)
!720 = !DILocation(line: 68, column: 3, scope: !716)
!721 = !DILocation(line: 70, column: 3, scope: !572)
!722 = !DILocation(line: 70, column: 11, scope: !712)
!723 = !DILocation(line: 70, column: 10, scope: !712)
!724 = !DILocation(line: 70, column: 3, scope: !712)
!725 = !DILocation(line: 71, column: 9, scope: !726)
!726 = distinct !DILexicalBlock(scope: !572, file: !1, line: 70, column: 46)
!727 = !DILocation(line: 71, column: 7, scope: !726)
!728 = !DILocation(line: 72, column: 5, scope: !726)
!729 = !DILocation(line: 72, column: 5, scope: !730)
!730 = !DILexicalBlockFile(scope: !731, file: !1, discriminator: 1)
!731 = distinct !DILexicalBlock(scope: !726, file: !1, line: 72, column: 5)
!732 = !DILocation(line: 74, column: 11, scope: !726)
!733 = !DILocation(line: 74, column: 9, scope: !726)
!734 = !DILocation(line: 75, column: 5, scope: !726)
!735 = !DILocation(line: 75, column: 10, scope: !726)
!736 = !DILocation(line: 75, column: 17, scope: !726)
!737 = !DILocation(line: 76, column: 5, scope: !726)
!738 = !DILocation(line: 76, column: 5, scope: !739)
!739 = !DILexicalBlockFile(scope: !740, file: !1, discriminator: 1)
!740 = distinct !DILexicalBlock(scope: !726, file: !1, line: 76, column: 5)
!741 = !DILocation(line: 70, column: 3, scope: !714)
!742 = !DILocation(line: 79, column: 25, scope: !572)
!743 = !DILocation(line: 79, column: 3, scope: !572)
!744 = !DILocation(line: 81, column: 3, scope: !572)
!745 = !DILocation(line: 81, column: 3, scope: !712)
!746 = !DILocation(line: 81, column: 3, scope: !714)
!747 = !DILocation(line: 81, column: 3, scope: !716)
!748 = !DILocation(line: 82, column: 3, scope: !572)
!749 = !DILocation(line: 82, column: 3, scope: !712)
!750 = !DILocation(line: 82, column: 3, scope: !714)
!751 = !DILocation(line: 82, column: 3, scope: !716)
!752 = !DILocation(line: 85, column: 3, scope: !572)
!753 = !DILocation(line: 85, column: 11, scope: !572)
!754 = !DILocation(line: 85, column: 19, scope: !572)
!755 = !DILocation(line: 86, column: 3, scope: !572)
!756 = !DILocation(line: 86, column: 11, scope: !572)
!757 = !DILocation(line: 86, column: 20, scope: !572)
!758 = !DILocation(line: 88, column: 1, scope: !572)
!759 = !DILocalVariable(name: "handle", arg: 1, scope: !619, file: !1, line: 91, type: !240)
!760 = !DILocation(line: 91, column: 45, scope: !619)
!761 = !DILocalVariable(name: "req", scope: !619, file: !1, line: 92, type: !227)
!762 = !DILocation(line: 92, column: 18, scope: !619)
!763 = !DILocalVariable(name: "q", scope: !619, file: !1, line: 93, type: !226)
!764 = !DILocation(line: 93, column: 10, scope: !619)
!765 = !DILocation(line: 95, column: 3, scope: !619)
!766 = !DILocation(line: 95, column: 3, scope: !767)
!767 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 1)
!768 = !DILocation(line: 95, column: 3, scope: !769)
!769 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 2)
!770 = !DILocation(line: 95, column: 3, scope: !771)
!771 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 3)
!772 = !DILocation(line: 96, column: 3, scope: !619)
!773 = !DILocation(line: 96, column: 11, scope: !619)
!774 = !DILocation(line: 96, column: 17, scope: !619)
!775 = !DILocation(line: 98, column: 3, scope: !619)
!776 = !DILocation(line: 98, column: 11, scope: !767)
!777 = !DILocation(line: 98, column: 10, scope: !767)
!778 = !DILocation(line: 98, column: 3, scope: !767)
!779 = !DILocation(line: 99, column: 9, scope: !780)
!780 = distinct !DILexicalBlock(scope: !619, file: !1, line: 98, column: 56)
!781 = !DILocation(line: 99, column: 7, scope: !780)
!782 = !DILocation(line: 100, column: 5, scope: !780)
!783 = !DILocation(line: 100, column: 5, scope: !784)
!784 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 1)
!785 = distinct !DILexicalBlock(scope: !780, file: !1, line: 100, column: 5)
!786 = !DILocation(line: 102, column: 11, scope: !780)
!787 = !DILocation(line: 102, column: 9, scope: !780)
!788 = !DILocation(line: 103, column: 5, scope: !780)
!789 = !DILocation(line: 103, column: 5, scope: !790)
!790 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 1)
!791 = distinct !DILexicalBlock(scope: !780, file: !1, line: 103, column: 5)
!792 = !DILocation(line: 103, column: 5, scope: !793)
!793 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 2)
!794 = !DILocation(line: 103, column: 5, scope: !795)
!795 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 3)
!796 = !DILocation(line: 103, column: 5, scope: !797)
!797 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 4)
!798 = !DILocation(line: 103, column: 5, scope: !799)
!799 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 5)
!800 = !DILocation(line: 103, column: 5, scope: !801)
!801 = !DILexicalBlockFile(scope: !802, file: !1, discriminator: 6)
!802 = distinct !DILexicalBlock(scope: !791, file: !1, line: 103, column: 5)
!803 = !DILocation(line: 103, column: 5, scope: !804)
!804 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 7)
!805 = !DILocation(line: 105, column: 47, scope: !780)
!806 = !DILocation(line: 105, column: 52, scope: !780)
!807 = !DILocation(line: 105, column: 58, scope: !780)
!808 = !DILocation(line: 105, column: 63, scope: !780)
!809 = !DILocation(line: 105, column: 32, scope: !780)
!810 = !DILocation(line: 105, column: 5, scope: !780)
!811 = !DILocation(line: 105, column: 13, scope: !780)
!812 = !DILocation(line: 105, column: 29, scope: !780)
!813 = !DILocation(line: 106, column: 5, scope: !780)
!814 = !DILocation(line: 106, column: 13, scope: !780)
!815 = !DILocation(line: 106, column: 29, scope: !780)
!816 = !DILocation(line: 108, column: 9, scope: !817)
!817 = distinct !DILexicalBlock(scope: !780, file: !1, line: 108, column: 9)
!818 = !DILocation(line: 108, column: 14, scope: !817)
!819 = !DILocation(line: 108, column: 22, scope: !817)
!820 = !DILocation(line: 108, column: 27, scope: !817)
!821 = !DILocation(line: 108, column: 19, scope: !817)
!822 = !DILocation(line: 108, column: 9, scope: !780)
!823 = !DILocation(line: 109, column: 16, scope: !817)
!824 = !DILocation(line: 109, column: 21, scope: !817)
!825 = !DILocation(line: 109, column: 7, scope: !817)
!826 = !DILocation(line: 110, column: 5, scope: !780)
!827 = !DILocation(line: 110, column: 10, scope: !780)
!828 = !DILocation(line: 110, column: 15, scope: !780)
!829 = !DILocation(line: 112, column: 9, scope: !830)
!830 = distinct !DILexicalBlock(scope: !780, file: !1, line: 112, column: 9)
!831 = !DILocation(line: 112, column: 14, scope: !830)
!832 = !DILocation(line: 112, column: 22, scope: !830)
!833 = !DILocation(line: 112, column: 9, scope: !780)
!834 = !DILocation(line: 113, column: 7, scope: !830)
!835 = !DILocation(line: 118, column: 9, scope: !836)
!836 = distinct !DILexicalBlock(scope: !780, file: !1, line: 118, column: 9)
!837 = !DILocation(line: 118, column: 14, scope: !836)
!838 = !DILocation(line: 118, column: 21, scope: !836)
!839 = !DILocation(line: 118, column: 9, scope: !780)
!840 = !DILocation(line: 119, column: 7, scope: !836)
!841 = !DILocation(line: 119, column: 12, scope: !836)
!842 = !DILocation(line: 119, column: 20, scope: !836)
!843 = !DILocation(line: 121, column: 7, scope: !836)
!844 = !DILocation(line: 121, column: 12, scope: !836)
!845 = !DILocation(line: 121, column: 20, scope: !836)
!846 = !DILocation(line: 121, column: 25, scope: !836)
!847 = !DILocation(line: 121, column: 30, scope: !836)
!848 = !DILocation(line: 98, column: 3, scope: !769)
!849 = !DILocation(line: 124, column: 7, scope: !850)
!850 = distinct !DILexicalBlock(scope: !619, file: !1, line: 124, column: 7)
!851 = !DILocation(line: 124, column: 7, scope: !619)
!852 = !DILocation(line: 126, column: 17, scope: !853)
!853 = distinct !DILexicalBlock(scope: !850, file: !1, line: 124, column: 42)
!854 = !DILocation(line: 126, column: 25, scope: !853)
!855 = !DILocation(line: 126, column: 32, scope: !853)
!856 = !DILocation(line: 126, column: 40, scope: !853)
!857 = !DILocation(line: 126, column: 5, scope: !853)
!858 = !DILocation(line: 127, column: 25, scope: !859)
!859 = distinct !DILexicalBlock(scope: !853, file: !1, line: 127, column: 9)
!860 = !DILocation(line: 127, column: 33, scope: !859)
!861 = !DILocation(line: 127, column: 10, scope: !859)
!862 = !DILocation(line: 127, column: 9, scope: !853)
!863 = !DILocation(line: 128, column: 7, scope: !859)
!864 = !DILocation(line: 128, column: 7, scope: !865)
!865 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 1)
!866 = distinct !DILexicalBlock(scope: !859, file: !1, line: 128, column: 7)
!867 = !DILocation(line: 128, column: 7, scope: !868)
!868 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 2)
!869 = !DILocation(line: 128, column: 7, scope: !870)
!870 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 3)
!871 = !DILocation(line: 128, column: 7, scope: !872)
!872 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 4)
!873 = !DILocation(line: 128, column: 7, scope: !874)
!874 = !DILexicalBlockFile(scope: !875, file: !1, discriminator: 5)
!875 = distinct !DILexicalBlock(scope: !866, file: !1, line: 128, column: 7)
!876 = !DILocation(line: 128, column: 7, scope: !877)
!877 = !DILexicalBlockFile(scope: !875, file: !1, discriminator: 6)
!878 = !DILocation(line: 128, column: 7, scope: !879)
!879 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 7)
!880 = !DILocation(line: 128, column: 7, scope: !881)
!881 = !DILexicalBlockFile(scope: !882, file: !1, discriminator: 8)
!882 = distinct !DILexicalBlock(scope: !866, file: !1, line: 128, column: 7)
!883 = !DILocation(line: 128, column: 7, scope: !884)
!884 = !DILexicalBlockFile(scope: !885, file: !1, discriminator: 9)
!885 = distinct !DILexicalBlock(scope: !882, file: !1, line: 128, column: 7)
!886 = !DILocation(line: 128, column: 7, scope: !887)
!887 = !DILexicalBlockFile(scope: !885, file: !1, discriminator: 10)
!888 = !DILocation(line: 128, column: 7, scope: !889)
!889 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 11)
!890 = !DILocation(line: 128, column: 7, scope: !891)
!891 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 12)
!892 = !DILocation(line: 129, column: 3, scope: !853)
!893 = !DILocation(line: 131, column: 3, scope: !619)
!894 = !DILocation(line: 131, column: 11, scope: !619)
!895 = !DILocation(line: 131, column: 17, scope: !619)
!896 = !DILocation(line: 132, column: 1, scope: !619)
!897 = !DILocalVariable(name: "handle", arg: 1, scope: !573, file: !1, line: 282, type: !240)
!898 = !DILocation(line: 282, column: 28, scope: !573)
!899 = !DILocalVariable(name: "addr", arg: 2, scope: !573, file: !1, line: 283, type: !482)
!900 = !DILocation(line: 283, column: 41, scope: !573)
!901 = !DILocalVariable(name: "addrlen", arg: 3, scope: !573, file: !1, line: 284, type: !252)
!902 = !DILocation(line: 284, column: 31, scope: !573)
!903 = !DILocalVariable(name: "flags", arg: 4, scope: !573, file: !1, line: 285, type: !252)
!904 = !DILocation(line: 285, column: 31, scope: !573)
!905 = !DILocalVariable(name: "err", scope: !573, file: !1, line: 286, type: !259)
!906 = !DILocation(line: 286, column: 7, scope: !573)
!907 = !DILocalVariable(name: "yes", scope: !573, file: !1, line: 287, type: !259)
!908 = !DILocation(line: 287, column: 7, scope: !573)
!909 = !DILocalVariable(name: "fd", scope: !573, file: !1, line: 288, type: !259)
!910 = !DILocation(line: 288, column: 7, scope: !573)
!911 = !DILocation(line: 291, column: 7, scope: !912)
!912 = distinct !DILexicalBlock(scope: !573, file: !1, line: 291, column: 7)
!913 = !DILocation(line: 291, column: 13, scope: !912)
!914 = !DILocation(line: 291, column: 7, scope: !573)
!915 = !DILocation(line: 292, column: 5, scope: !912)
!916 = !DILocation(line: 295, column: 8, scope: !917)
!917 = distinct !DILexicalBlock(scope: !573, file: !1, line: 295, column: 7)
!918 = !DILocation(line: 295, column: 14, scope: !917)
!919 = !DILocation(line: 295, column: 33, scope: !917)
!920 = !DILocation(line: 295, column: 36, scope: !921)
!921 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 1)
!922 = !DILocation(line: 295, column: 42, scope: !921)
!923 = !DILocation(line: 295, column: 52, scope: !921)
!924 = !DILocation(line: 295, column: 7, scope: !921)
!925 = !DILocation(line: 296, column: 5, scope: !917)
!926 = !DILocation(line: 298, column: 8, scope: !573)
!927 = !DILocation(line: 298, column: 16, scope: !573)
!928 = !DILocation(line: 298, column: 27, scope: !573)
!929 = !DILocation(line: 298, column: 6, scope: !573)
!930 = !DILocation(line: 299, column: 7, scope: !931)
!931 = distinct !DILexicalBlock(scope: !573, file: !1, line: 299, column: 7)
!932 = !DILocation(line: 299, column: 10, scope: !931)
!933 = !DILocation(line: 299, column: 7, scope: !573)
!934 = !DILocation(line: 300, column: 22, scope: !935)
!935 = distinct !DILexicalBlock(scope: !931, file: !1, line: 299, column: 17)
!936 = !DILocation(line: 300, column: 28, scope: !935)
!937 = !DILocation(line: 300, column: 11, scope: !935)
!938 = !DILocation(line: 300, column: 9, scope: !935)
!939 = !DILocation(line: 301, column: 9, scope: !940)
!940 = distinct !DILexicalBlock(scope: !935, file: !1, line: 301, column: 9)
!941 = !DILocation(line: 301, column: 13, scope: !940)
!942 = !DILocation(line: 301, column: 9, scope: !935)
!943 = !DILocation(line: 302, column: 14, scope: !940)
!944 = !DILocation(line: 302, column: 7, scope: !940)
!945 = !DILocation(line: 303, column: 10, scope: !935)
!946 = !DILocation(line: 303, column: 8, scope: !935)
!947 = !DILocation(line: 304, column: 29, scope: !935)
!948 = !DILocation(line: 304, column: 5, scope: !935)
!949 = !DILocation(line: 304, column: 13, scope: !935)
!950 = !DILocation(line: 304, column: 24, scope: !935)
!951 = !DILocation(line: 304, column: 27, scope: !935)
!952 = !DILocation(line: 305, column: 3, scope: !935)
!953 = !DILocation(line: 307, column: 7, scope: !954)
!954 = distinct !DILexicalBlock(scope: !573, file: !1, line: 307, column: 7)
!955 = !DILocation(line: 307, column: 13, scope: !954)
!956 = !DILocation(line: 307, column: 7, scope: !573)
!957 = !DILocation(line: 308, column: 25, scope: !958)
!958 = distinct !DILexicalBlock(scope: !954, file: !1, line: 307, column: 33)
!959 = !DILocation(line: 308, column: 11, scope: !958)
!960 = !DILocation(line: 308, column: 9, scope: !958)
!961 = !DILocation(line: 309, column: 9, scope: !962)
!962 = distinct !DILexicalBlock(scope: !958, file: !1, line: 309, column: 9)
!963 = !DILocation(line: 309, column: 9, scope: !958)
!964 = !DILocation(line: 310, column: 14, scope: !962)
!965 = !DILocation(line: 310, column: 7, scope: !962)
!966 = !DILocation(line: 311, column: 3, scope: !958)
!967 = !DILocation(line: 313, column: 7, scope: !968)
!968 = distinct !DILexicalBlock(scope: !573, file: !1, line: 313, column: 7)
!969 = !DILocation(line: 313, column: 13, scope: !968)
!970 = !DILocation(line: 313, column: 7, scope: !573)
!971 = !DILocation(line: 315, column: 9, scope: !972)
!972 = distinct !DILexicalBlock(scope: !968, file: !1, line: 313, column: 32)
!973 = !DILocation(line: 316, column: 20, scope: !974)
!974 = distinct !DILexicalBlock(scope: !972, file: !1, line: 316, column: 9)
!975 = !DILocation(line: 316, column: 51, scope: !974)
!976 = !DILocation(line: 316, column: 9, scope: !974)
!977 = !DILocation(line: 316, column: 69, scope: !974)
!978 = !DILocation(line: 316, column: 9, scope: !972)
!979 = !DILocation(line: 317, column: 14, scope: !980)
!980 = distinct !DILexicalBlock(scope: !974, file: !1, line: 316, column: 76)
!981 = !DILocation(line: 317, column: 13, scope: !980)
!982 = !DILocation(line: 317, column: 11, scope: !980)
!983 = !DILocation(line: 318, column: 14, scope: !980)
!984 = !DILocation(line: 318, column: 7, scope: !980)
!985 = !DILocation(line: 324, column: 3, scope: !972)
!986 = !DILocation(line: 326, column: 12, scope: !987)
!987 = distinct !DILexicalBlock(scope: !573, file: !1, line: 326, column: 7)
!988 = !DILocation(line: 326, column: 16, scope: !987)
!989 = !DILocation(line: 326, column: 22, scope: !987)
!990 = !DILocation(line: 326, column: 7, scope: !987)
!991 = !DILocation(line: 326, column: 7, scope: !573)
!992 = !DILocation(line: 327, column: 12, scope: !993)
!993 = distinct !DILexicalBlock(scope: !987, file: !1, line: 326, column: 32)
!994 = !DILocation(line: 327, column: 11, scope: !993)
!995 = !DILocation(line: 327, column: 9, scope: !993)
!996 = !DILocation(line: 328, column: 9, scope: !997)
!997 = distinct !DILexicalBlock(scope: !993, file: !1, line: 328, column: 9)
!998 = !DILocation(line: 328, column: 15, scope: !997)
!999 = !DILocation(line: 328, column: 9, scope: !993)
!1000 = !DILocation(line: 331, column: 11, scope: !997)
!1001 = !DILocation(line: 331, column: 7, scope: !997)
!1002 = !DILocation(line: 332, column: 12, scope: !993)
!1003 = !DILocation(line: 332, column: 5, scope: !993)
!1004 = !DILocation(line: 335, column: 7, scope: !1005)
!1005 = distinct !DILexicalBlock(scope: !573, file: !1, line: 335, column: 7)
!1006 = !DILocation(line: 335, column: 13, scope: !1005)
!1007 = !DILocation(line: 335, column: 23, scope: !1005)
!1008 = !DILocation(line: 335, column: 7, scope: !573)
!1009 = !DILocation(line: 336, column: 5, scope: !1005)
!1010 = !DILocation(line: 336, column: 13, scope: !1005)
!1011 = !DILocation(line: 336, column: 19, scope: !1005)
!1012 = !DILocation(line: 338, column: 3, scope: !573)
!1013 = !DILocation(line: 338, column: 11, scope: !573)
!1014 = !DILocation(line: 338, column: 17, scope: !573)
!1015 = !DILocation(line: 339, column: 3, scope: !573)
!1016 = !DILocation(line: 340, column: 1, scope: !573)
!1017 = !DILocalVariable(name: "fd", arg: 1, scope: !620, file: !1, line: 265, type: !259)
!1018 = !DILocation(line: 265, column: 30, scope: !620)
!1019 = !DILocalVariable(name: "yes", scope: !620, file: !1, line: 266, type: !259)
!1020 = !DILocation(line: 266, column: 7, scope: !620)
!1021 = !DILocation(line: 273, column: 7, scope: !620)
!1022 = !DILocation(line: 274, column: 18, scope: !1023)
!1023 = distinct !DILexicalBlock(scope: !620, file: !1, line: 274, column: 7)
!1024 = !DILocation(line: 274, column: 48, scope: !1023)
!1025 = !DILocation(line: 274, column: 7, scope: !1023)
!1026 = !DILocation(line: 274, column: 7, scope: !620)
!1027 = !DILocation(line: 275, column: 13, scope: !1023)
!1028 = !DILocation(line: 275, column: 12, scope: !1023)
!1029 = !DILocation(line: 275, column: 5, scope: !1023)
!1030 = !DILocation(line: 278, column: 3, scope: !620)
!1031 = !DILocation(line: 279, column: 1, scope: !620)
!1032 = !DILocalVariable(name: "req", arg: 1, scope: !576, file: !1, line: 384, type: !227)
!1033 = !DILocation(line: 384, column: 33, scope: !576)
!1034 = !DILocalVariable(name: "handle", arg: 2, scope: !576, file: !1, line: 385, type: !240)
!1035 = !DILocation(line: 385, column: 28, scope: !576)
!1036 = !DILocalVariable(name: "bufs", arg: 3, scope: !576, file: !1, line: 386, type: !480)
!1037 = !DILocation(line: 386, column: 33, scope: !576)
!1038 = !DILocalVariable(name: "nbufs", arg: 4, scope: !576, file: !1, line: 387, type: !252)
!1039 = !DILocation(line: 387, column: 31, scope: !576)
!1040 = !DILocalVariable(name: "addr", arg: 5, scope: !576, file: !1, line: 388, type: !482)
!1041 = !DILocation(line: 388, column: 41, scope: !576)
!1042 = !DILocalVariable(name: "addrlen", arg: 6, scope: !576, file: !1, line: 389, type: !252)
!1043 = !DILocation(line: 389, column: 31, scope: !576)
!1044 = !DILocalVariable(name: "send_cb", arg: 7, scope: !576, file: !1, line: 390, type: !498)
!1045 = !DILocation(line: 390, column: 33, scope: !576)
!1046 = !DILocalVariable(name: "err", scope: !576, file: !1, line: 391, type: !259)
!1047 = !DILocation(line: 391, column: 7, scope: !576)
!1048 = !DILocalVariable(name: "empty_queue", scope: !576, file: !1, line: 392, type: !259)
!1049 = !DILocation(line: 392, column: 7, scope: !576)
!1050 = !DILocation(line: 394, column: 3, scope: !576)
!1051 = !DILocation(line: 394, column: 3, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 1)
!1053 = !DILocation(line: 394, column: 3, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 2)
!1055 = !DILocation(line: 394, column: 3, scope: !1056)
!1056 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 3)
!1057 = !DILocation(line: 396, column: 37, scope: !576)
!1058 = !DILocation(line: 396, column: 45, scope: !576)
!1059 = !DILocation(line: 396, column: 51, scope: !576)
!1060 = !DILocation(line: 396, column: 9, scope: !576)
!1061 = !DILocation(line: 396, column: 7, scope: !576)
!1062 = !DILocation(line: 397, column: 7, scope: !1063)
!1063 = distinct !DILexicalBlock(scope: !576, file: !1, line: 397, column: 7)
!1064 = !DILocation(line: 397, column: 7, scope: !576)
!1065 = !DILocation(line: 398, column: 12, scope: !1063)
!1066 = !DILocation(line: 398, column: 5, scope: !1063)
!1067 = !DILocation(line: 404, column: 18, scope: !576)
!1068 = !DILocation(line: 404, column: 26, scope: !576)
!1069 = !DILocation(line: 404, column: 43, scope: !576)
!1070 = !DILocation(line: 404, column: 15, scope: !576)
!1071 = !DILocation(line: 406, column: 3, scope: !576)
!1072 = !DILocation(line: 406, column: 3, scope: !1073)
!1073 = !DILexicalBlockFile(scope: !1074, file: !1, discriminator: 1)
!1074 = distinct !DILexicalBlock(scope: !576, file: !1, line: 406, column: 3)
!1075 = !DILocation(line: 406, column: 3, scope: !1076)
!1076 = !DILexicalBlockFile(scope: !1077, file: !1, discriminator: 2)
!1077 = distinct !DILexicalBlock(scope: !1074, file: !1, line: 406, column: 3)
!1078 = !DILocation(line: 406, column: 3, scope: !1079)
!1079 = !DILexicalBlockFile(scope: !1074, file: !1, discriminator: 3)
!1080 = !DILocation(line: 406, column: 3, scope: !1081)
!1081 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 4)
!1082 = distinct !DILexicalBlock(scope: !1074, file: !1, line: 406, column: 3)
!1083 = !DILocation(line: 406, column: 3, scope: !1084)
!1084 = !DILexicalBlockFile(scope: !1085, file: !1, discriminator: 5)
!1085 = distinct !DILexicalBlock(scope: !1082, file: !1, line: 406, column: 3)
!1086 = !DILocation(line: 406, column: 3, scope: !1087)
!1087 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 6)
!1088 = !DILocation(line: 406, column: 3, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1074, file: !1, discriminator: 7)
!1090 = !DILocation(line: 407, column: 3, scope: !576)
!1091 = !DILocation(line: 407, column: 3, scope: !1052)
!1092 = !DILocation(line: 407, column: 3, scope: !1054)
!1093 = !DILocation(line: 407, column: 3, scope: !1056)
!1094 = !DILocation(line: 408, column: 11, scope: !576)
!1095 = !DILocation(line: 408, column: 16, scope: !576)
!1096 = !DILocation(line: 408, column: 3, scope: !576)
!1097 = !DILocation(line: 408, column: 22, scope: !576)
!1098 = !DILocation(line: 408, column: 28, scope: !576)
!1099 = !DILocation(line: 409, column: 18, scope: !576)
!1100 = !DILocation(line: 409, column: 3, scope: !576)
!1101 = !DILocation(line: 409, column: 8, scope: !576)
!1102 = !DILocation(line: 409, column: 16, scope: !576)
!1103 = !DILocation(line: 410, column: 17, scope: !576)
!1104 = !DILocation(line: 410, column: 3, scope: !576)
!1105 = !DILocation(line: 410, column: 8, scope: !576)
!1106 = !DILocation(line: 410, column: 15, scope: !576)
!1107 = !DILocation(line: 411, column: 16, scope: !576)
!1108 = !DILocation(line: 411, column: 3, scope: !576)
!1109 = !DILocation(line: 411, column: 8, scope: !576)
!1110 = !DILocation(line: 411, column: 14, scope: !576)
!1111 = !DILocation(line: 413, column: 15, scope: !576)
!1112 = !DILocation(line: 413, column: 20, scope: !576)
!1113 = !DILocation(line: 413, column: 3, scope: !576)
!1114 = !DILocation(line: 413, column: 8, scope: !576)
!1115 = !DILocation(line: 413, column: 13, scope: !576)
!1116 = !DILocation(line: 414, column: 7, scope: !1117)
!1117 = distinct !DILexicalBlock(scope: !576, file: !1, line: 414, column: 7)
!1118 = !DILocation(line: 414, column: 13, scope: !1117)
!1119 = !DILocation(line: 414, column: 7, scope: !576)
!1120 = !DILocation(line: 415, column: 28, scope: !1117)
!1121 = !DILocation(line: 415, column: 34, scope: !1117)
!1122 = !DILocation(line: 415, column: 17, scope: !1117)
!1123 = !DILocation(line: 415, column: 5, scope: !1117)
!1124 = !DILocation(line: 415, column: 10, scope: !1117)
!1125 = !DILocation(line: 415, column: 15, scope: !1117)
!1126 = !DILocation(line: 417, column: 7, scope: !1127)
!1127 = distinct !DILexicalBlock(scope: !576, file: !1, line: 417, column: 7)
!1128 = !DILocation(line: 417, column: 12, scope: !1127)
!1129 = !DILocation(line: 417, column: 17, scope: !1127)
!1130 = !DILocation(line: 417, column: 7, scope: !576)
!1131 = !DILocation(line: 418, column: 5, scope: !1132)
!1132 = distinct !DILexicalBlock(scope: !1127, file: !1, line: 417, column: 26)
!1133 = !DILocation(line: 418, column: 5, scope: !1134)
!1134 = !DILexicalBlockFile(scope: !1135, file: !1, discriminator: 1)
!1135 = distinct !DILexicalBlock(scope: !1132, file: !1, line: 418, column: 5)
!1136 = !DILocation(line: 418, column: 5, scope: !1137)
!1137 = !DILexicalBlockFile(scope: !1135, file: !1, discriminator: 2)
!1138 = !DILocation(line: 418, column: 5, scope: !1139)
!1139 = !DILexicalBlockFile(scope: !1135, file: !1, discriminator: 3)
!1140 = !DILocation(line: 418, column: 5, scope: !1141)
!1141 = !DILexicalBlockFile(scope: !1135, file: !1, discriminator: 4)
!1142 = !DILocation(line: 418, column: 5, scope: !1143)
!1143 = !DILexicalBlockFile(scope: !1135, file: !1, discriminator: 5)
!1144 = !DILocation(line: 418, column: 5, scope: !1145)
!1145 = !DILexicalBlockFile(scope: !1146, file: !1, discriminator: 6)
!1146 = distinct !DILexicalBlock(scope: !1135, file: !1, line: 418, column: 5)
!1147 = !DILocation(line: 418, column: 5, scope: !1148)
!1148 = !DILexicalBlockFile(scope: !1135, file: !1, discriminator: 7)
!1149 = !DILocation(line: 419, column: 5, scope: !1132)
!1150 = !DILocation(line: 422, column: 10, scope: !576)
!1151 = !DILocation(line: 422, column: 15, scope: !576)
!1152 = !DILocation(line: 422, column: 3, scope: !576)
!1153 = !DILocation(line: 422, column: 21, scope: !576)
!1154 = !DILocation(line: 422, column: 27, scope: !576)
!1155 = !DILocation(line: 422, column: 33, scope: !576)
!1156 = !DILocation(line: 423, column: 45, scope: !576)
!1157 = !DILocation(line: 423, column: 50, scope: !576)
!1158 = !DILocation(line: 423, column: 56, scope: !576)
!1159 = !DILocation(line: 423, column: 61, scope: !576)
!1160 = !DILocation(line: 423, column: 30, scope: !576)
!1161 = !DILocation(line: 423, column: 3, scope: !576)
!1162 = !DILocation(line: 423, column: 11, scope: !576)
!1163 = !DILocation(line: 423, column: 27, scope: !576)
!1164 = !DILocation(line: 424, column: 3, scope: !576)
!1165 = !DILocation(line: 424, column: 11, scope: !576)
!1166 = !DILocation(line: 424, column: 27, scope: !576)
!1167 = !DILocation(line: 425, column: 3, scope: !576)
!1168 = !DILocation(line: 425, column: 3, scope: !1169)
!1169 = !DILexicalBlockFile(scope: !1170, file: !1, discriminator: 1)
!1170 = distinct !DILexicalBlock(scope: !576, file: !1, line: 425, column: 3)
!1171 = !DILocation(line: 426, column: 3, scope: !576)
!1172 = !DILocation(line: 426, column: 3, scope: !1173)
!1173 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 1)
!1174 = distinct !DILexicalBlock(scope: !576, file: !1, line: 426, column: 3)
!1175 = !DILocation(line: 426, column: 3, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 2)
!1177 = !DILocation(line: 426, column: 3, scope: !1178)
!1178 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 3)
!1179 = !DILocation(line: 426, column: 3, scope: !1180)
!1180 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 4)
!1181 = !DILocation(line: 426, column: 3, scope: !1182)
!1182 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 5)
!1183 = distinct !DILexicalBlock(scope: !1174, file: !1, line: 426, column: 3)
!1184 = !DILocation(line: 426, column: 3, scope: !1185)
!1185 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 6)
!1186 = !DILocation(line: 426, column: 3, scope: !1187)
!1187 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 7)
!1188 = !DILocation(line: 426, column: 3, scope: !1189)
!1189 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 8)
!1190 = distinct !DILexicalBlock(scope: !1174, file: !1, line: 426, column: 3)
!1191 = !DILocation(line: 426, column: 3, scope: !1192)
!1192 = !DILexicalBlockFile(scope: !1193, file: !1, discriminator: 9)
!1193 = distinct !DILexicalBlock(scope: !1190, file: !1, line: 426, column: 3)
!1194 = !DILocation(line: 426, column: 3, scope: !1195)
!1195 = !DILexicalBlockFile(scope: !1193, file: !1, discriminator: 10)
!1196 = !DILocation(line: 426, column: 3, scope: !1197)
!1197 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 11)
!1198 = !DILocation(line: 428, column: 7, scope: !1199)
!1199 = distinct !DILexicalBlock(scope: !576, file: !1, line: 428, column: 7)
!1200 = !DILocation(line: 428, column: 19, scope: !1199)
!1201 = !DILocation(line: 428, column: 24, scope: !1202)
!1202 = !DILexicalBlockFile(scope: !1199, file: !1, discriminator: 1)
!1203 = !DILocation(line: 428, column: 32, scope: !1202)
!1204 = !DILocation(line: 428, column: 38, scope: !1202)
!1205 = !DILocation(line: 428, column: 7, scope: !1202)
!1206 = !DILocation(line: 429, column: 21, scope: !1207)
!1207 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 428, column: 60)
!1208 = !DILocation(line: 429, column: 5, scope: !1207)
!1209 = !DILocation(line: 435, column: 10, scope: !1210)
!1210 = distinct !DILexicalBlock(scope: !1207, file: !1, line: 435, column: 9)
!1211 = !DILocation(line: 435, column: 9, scope: !1207)
!1212 = !DILocation(line: 436, column: 20, scope: !1210)
!1213 = !DILocation(line: 436, column: 28, scope: !1210)
!1214 = !DILocation(line: 436, column: 35, scope: !1210)
!1215 = !DILocation(line: 436, column: 43, scope: !1210)
!1216 = !DILocation(line: 436, column: 7, scope: !1210)
!1217 = !DILocation(line: 437, column: 3, scope: !1207)
!1218 = !DILocation(line: 438, column: 18, scope: !1219)
!1219 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 437, column: 10)
!1220 = !DILocation(line: 438, column: 26, scope: !1219)
!1221 = !DILocation(line: 438, column: 33, scope: !1219)
!1222 = !DILocation(line: 438, column: 41, scope: !1219)
!1223 = !DILocation(line: 438, column: 5, scope: !1219)
!1224 = !DILocation(line: 441, column: 3, scope: !576)
!1225 = !DILocation(line: 442, column: 1, scope: !576)
!1226 = !DILocalVariable(name: "handle", arg: 1, scope: !623, file: !1, line: 343, type: !240)
!1227 = !DILocation(line: 343, column: 50, scope: !623)
!1228 = !DILocalVariable(name: "domain", arg: 2, scope: !623, file: !1, line: 344, type: !259)
!1229 = !DILocation(line: 344, column: 44, scope: !623)
!1230 = !DILocalVariable(name: "flags", arg: 3, scope: !623, file: !1, line: 345, type: !252)
!1231 = !DILocation(line: 345, column: 53, scope: !623)
!1232 = !DILocalVariable(name: "taddr", scope: !623, file: !1, line: 350, type: !1233)
!1233 = !DICompositeType(tag: DW_TAG_union_type, scope: !623, file: !1, line: 346, size: 224, align: 32, elements: !1234)
!1234 = !{!1235, !1236, !1237}
!1235 = !DIDerivedType(tag: DW_TAG_member, name: "in6", scope: !1233, file: !1, line: 347, baseType: !544, size: 224, align: 32)
!1236 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1233, file: !1, line: 348, baseType: !526, size: 128, align: 32)
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !1233, file: !1, line: 349, baseType: !484, size: 128, align: 16)
!1238 = !DILocation(line: 350, column: 5, scope: !623)
!1239 = !DILocalVariable(name: "addrlen", scope: !623, file: !1, line: 351, type: !565)
!1240 = !DILocation(line: 351, column: 13, scope: !623)
!1241 = !DILocation(line: 353, column: 7, scope: !1242)
!1242 = distinct !DILexicalBlock(scope: !623, file: !1, line: 353, column: 7)
!1243 = !DILocation(line: 353, column: 15, scope: !1242)
!1244 = !DILocation(line: 353, column: 26, scope: !1242)
!1245 = !DILocation(line: 353, column: 29, scope: !1242)
!1246 = !DILocation(line: 353, column: 7, scope: !623)
!1247 = !DILocation(line: 354, column: 5, scope: !1242)
!1248 = !DILocation(line: 356, column: 11, scope: !623)
!1249 = !DILocation(line: 356, column: 3, scope: !623)
!1250 = !DILocalVariable(name: "addr", scope: !1251, file: !1, line: 359, type: !525)
!1251 = distinct !DILexicalBlock(scope: !1252, file: !1, line: 358, column: 3)
!1252 = distinct !DILexicalBlock(scope: !623, file: !1, line: 356, column: 19)
!1253 = !DILocation(line: 359, column: 25, scope: !1251)
!1254 = !DILocation(line: 359, column: 39, scope: !1251)
!1255 = !DILocation(line: 360, column: 12, scope: !1251)
!1256 = !DILocation(line: 360, column: 5, scope: !1251)
!1257 = !DILocation(line: 361, column: 5, scope: !1251)
!1258 = !DILocation(line: 361, column: 11, scope: !1251)
!1259 = !DILocation(line: 361, column: 22, scope: !1251)
!1260 = !DILocation(line: 362, column: 5, scope: !1251)
!1261 = !DILocation(line: 362, column: 11, scope: !1251)
!1262 = !DILocation(line: 362, column: 20, scope: !1251)
!1263 = !DILocation(line: 362, column: 27, scope: !1251)
!1264 = !DILocation(line: 363, column: 13, scope: !1251)
!1265 = !DILocation(line: 364, column: 5, scope: !1251)
!1266 = !DILocalVariable(name: "addr", scope: !1267, file: !1, line: 368, type: !543)
!1267 = distinct !DILexicalBlock(scope: !1252, file: !1, line: 367, column: 3)
!1268 = !DILocation(line: 368, column: 26, scope: !1267)
!1269 = !DILocation(line: 368, column: 40, scope: !1267)
!1270 = !DILocation(line: 369, column: 12, scope: !1267)
!1271 = !DILocation(line: 369, column: 5, scope: !1267)
!1272 = !DILocation(line: 370, column: 5, scope: !1267)
!1273 = !DILocation(line: 370, column: 11, scope: !1267)
!1274 = !DILocation(line: 370, column: 23, scope: !1267)
!1275 = !DILocation(line: 371, column: 5, scope: !1267)
!1276 = !DILocation(line: 371, column: 11, scope: !1267)
!1277 = !DILocation(line: 371, column: 23, scope: !1267)
!1278 = !DILocation(line: 372, column: 13, scope: !1267)
!1279 = !DILocation(line: 373, column: 5, scope: !1267)
!1280 = !DILocation(line: 376, column: 5, scope: !1252)
!1281 = !DILocation(line: 380, column: 23, scope: !623)
!1282 = !DILocation(line: 380, column: 38, scope: !623)
!1283 = !DILocation(line: 380, column: 44, scope: !623)
!1284 = !DILocation(line: 380, column: 53, scope: !623)
!1285 = !DILocation(line: 380, column: 10, scope: !623)
!1286 = !DILocation(line: 380, column: 3, scope: !623)
!1287 = !DILocation(line: 381, column: 1, scope: !623)
!1288 = !DILocalVariable(name: "handle", arg: 1, scope: !626, file: !1, line: 216, type: !240)
!1289 = !DILocation(line: 216, column: 39, scope: !626)
!1290 = !DILocalVariable(name: "req", scope: !626, file: !1, line: 217, type: !227)
!1291 = !DILocation(line: 217, column: 18, scope: !626)
!1292 = !DILocalVariable(name: "q", scope: !626, file: !1, line: 218, type: !226)
!1293 = !DILocation(line: 218, column: 10, scope: !626)
!1294 = !DILocalVariable(name: "h", scope: !626, file: !1, line: 219, type: !1295)
!1295 = !DICompositeType(tag: DW_TAG_structure_type, name: "msghdr", file: !194, line: 224, size: 448, align: 64, elements: !1296)
!1296 = !{!1297, !1298, !1299, !1300, !1301, !1302, !1303}
!1297 = !DIDerivedType(tag: DW_TAG_member, name: "msg_name", scope: !1295, file: !194, line: 226, baseType: !222, size: 64, align: 64)
!1298 = !DIDerivedType(tag: DW_TAG_member, name: "msg_namelen", scope: !1295, file: !194, line: 227, baseType: !565, size: 32, align: 32, offset: 64)
!1299 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iov", scope: !1295, file: !194, line: 229, baseType: !519, size: 64, align: 64, offset: 128)
!1300 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iovlen", scope: !1295, file: !194, line: 230, baseType: !456, size: 64, align: 64, offset: 192)
!1301 = !DIDerivedType(tag: DW_TAG_member, name: "msg_control", scope: !1295, file: !194, line: 232, baseType: !222, size: 64, align: 64, offset: 256)
!1302 = !DIDerivedType(tag: DW_TAG_member, name: "msg_controllen", scope: !1295, file: !194, line: 233, baseType: !456, size: 64, align: 64, offset: 320)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "msg_flags", scope: !1295, file: !194, line: 238, baseType: !259, size: 32, align: 32, offset: 384)
!1304 = !DILocation(line: 219, column: 17, scope: !626)
!1305 = !DILocalVariable(name: "size", scope: !626, file: !1, line: 220, type: !476)
!1306 = !DILocation(line: 220, column: 11, scope: !626)
!1307 = !DILocation(line: 222, column: 3, scope: !626)
!1308 = !DILocation(line: 222, column: 11, scope: !1309)
!1309 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 1)
!1310 = !DILocation(line: 222, column: 10, scope: !1309)
!1311 = !DILocation(line: 222, column: 3, scope: !1309)
!1312 = !DILocation(line: 223, column: 9, scope: !1313)
!1313 = distinct !DILexicalBlock(scope: !626, file: !1, line: 222, column: 46)
!1314 = !DILocation(line: 223, column: 7, scope: !1313)
!1315 = !DILocation(line: 224, column: 5, scope: !1313)
!1316 = !DILocation(line: 224, column: 5, scope: !1317)
!1317 = !DILexicalBlockFile(scope: !1313, file: !1, discriminator: 1)
!1318 = !DILocation(line: 224, column: 5, scope: !1319)
!1319 = !DILexicalBlockFile(scope: !1313, file: !1, discriminator: 2)
!1320 = !DILocation(line: 224, column: 5, scope: !1321)
!1321 = !DILexicalBlockFile(scope: !1313, file: !1, discriminator: 3)
!1322 = !DILocation(line: 226, column: 11, scope: !1313)
!1323 = !DILocation(line: 226, column: 9, scope: !1313)
!1324 = !DILocation(line: 227, column: 5, scope: !1313)
!1325 = !DILocation(line: 227, column: 5, scope: !1317)
!1326 = !DILocation(line: 227, column: 5, scope: !1319)
!1327 = !DILocation(line: 227, column: 5, scope: !1321)
!1328 = !DILocation(line: 229, column: 5, scope: !1313)
!1329 = !DILocation(line: 230, column: 19, scope: !1313)
!1330 = !DILocation(line: 230, column: 24, scope: !1313)
!1331 = !DILocation(line: 230, column: 18, scope: !1313)
!1332 = !DILocation(line: 230, column: 7, scope: !1313)
!1333 = !DILocation(line: 230, column: 16, scope: !1313)
!1334 = !DILocation(line: 231, column: 22, scope: !1313)
!1335 = !DILocation(line: 231, column: 27, scope: !1313)
!1336 = !DILocation(line: 231, column: 32, scope: !1313)
!1337 = !DILocation(line: 231, column: 42, scope: !1313)
!1338 = !DILocation(line: 231, column: 21, scope: !1313)
!1339 = !DILocation(line: 231, column: 7, scope: !1313)
!1340 = !DILocation(line: 231, column: 19, scope: !1313)
!1341 = !DILocation(line: 233, column: 33, scope: !1313)
!1342 = !DILocation(line: 233, column: 38, scope: !1313)
!1343 = !DILocation(line: 233, column: 17, scope: !1313)
!1344 = !DILocation(line: 233, column: 7, scope: !1313)
!1345 = !DILocation(line: 233, column: 15, scope: !1313)
!1346 = !DILocation(line: 234, column: 20, scope: !1313)
!1347 = !DILocation(line: 234, column: 25, scope: !1313)
!1348 = !DILocation(line: 234, column: 7, scope: !1313)
!1349 = !DILocation(line: 234, column: 18, scope: !1313)
!1350 = !DILocation(line: 236, column: 5, scope: !1313)
!1351 = !DILocation(line: 237, column: 22, scope: !1352)
!1352 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 236, column: 8)
!1353 = !DILocation(line: 237, column: 30, scope: !1352)
!1354 = !DILocation(line: 237, column: 41, scope: !1352)
!1355 = !DILocation(line: 237, column: 14, scope: !1352)
!1356 = !DILocation(line: 237, column: 12, scope: !1352)
!1357 = !DILocation(line: 238, column: 5, scope: !1352)
!1358 = !DILocation(line: 238, column: 14, scope: !1317)
!1359 = !DILocation(line: 238, column: 19, scope: !1317)
!1360 = !DILocation(line: 238, column: 25, scope: !1317)
!1361 = !DILocation(line: 238, column: 28, scope: !1319)
!1362 = !DILocation(line: 238, column: 34, scope: !1319)
!1363 = !DILocation(line: 238, column: 5, scope: !1364)
!1364 = !DILexicalBlockFile(scope: !1352, file: !1, discriminator: 3)
!1365 = !DILocation(line: 240, column: 9, scope: !1366)
!1366 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 240, column: 9)
!1367 = !DILocation(line: 240, column: 14, scope: !1366)
!1368 = !DILocation(line: 240, column: 20, scope: !1366)
!1369 = !DILocation(line: 240, column: 24, scope: !1370)
!1370 = !DILexicalBlockFile(scope: !1366, file: !1, discriminator: 1)
!1371 = !DILocation(line: 240, column: 30, scope: !1370)
!1372 = !DILocation(line: 240, column: 40, scope: !1370)
!1373 = !DILocation(line: 240, column: 43, scope: !1374)
!1374 = !DILexicalBlockFile(scope: !1366, file: !1, discriminator: 2)
!1375 = !DILocation(line: 240, column: 49, scope: !1374)
!1376 = !DILocation(line: 240, column: 9, scope: !1374)
!1377 = !DILocation(line: 241, column: 7, scope: !1366)
!1378 = !DILocation(line: 243, column: 20, scope: !1313)
!1379 = !DILocation(line: 243, column: 25, scope: !1313)
!1380 = !DILocation(line: 243, column: 34, scope: !1317)
!1381 = !DILocation(line: 243, column: 33, scope: !1317)
!1382 = !DILocation(line: 243, column: 20, scope: !1317)
!1383 = !DILocation(line: 243, column: 42, scope: !1319)
!1384 = !DILocation(line: 243, column: 20, scope: !1319)
!1385 = !DILocation(line: 243, column: 20, scope: !1321)
!1386 = !DILocation(line: 243, column: 5, scope: !1321)
!1387 = !DILocation(line: 243, column: 10, scope: !1321)
!1388 = !DILocation(line: 243, column: 17, scope: !1321)
!1389 = !DILocation(line: 250, column: 5, scope: !1313)
!1390 = !DILocation(line: 250, column: 5, scope: !1391)
!1391 = !DILexicalBlockFile(scope: !1392, file: !1, discriminator: 1)
!1392 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 250, column: 5)
!1393 = !DILocation(line: 251, column: 5, scope: !1313)
!1394 = !DILocation(line: 251, column: 5, scope: !1395)
!1395 = !DILexicalBlockFile(scope: !1396, file: !1, discriminator: 1)
!1396 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 251, column: 5)
!1397 = !DILocation(line: 252, column: 17, scope: !1313)
!1398 = !DILocation(line: 252, column: 25, scope: !1313)
!1399 = !DILocation(line: 252, column: 32, scope: !1313)
!1400 = !DILocation(line: 252, column: 40, scope: !1313)
!1401 = !DILocation(line: 252, column: 5, scope: !1313)
!1402 = !DILocation(line: 222, column: 3, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 2)
!1404 = !DILocation(line: 254, column: 1, scope: !626)
!1405 = !DILocalVariable(name: "handle", arg: 1, scope: !579, file: !1, line: 445, type: !240)
!1406 = !DILocation(line: 445, column: 32, scope: !579)
!1407 = !DILocalVariable(name: "bufs", arg: 2, scope: !579, file: !1, line: 446, type: !480)
!1408 = !DILocation(line: 446, column: 37, scope: !579)
!1409 = !DILocalVariable(name: "nbufs", arg: 3, scope: !579, file: !1, line: 447, type: !252)
!1410 = !DILocation(line: 447, column: 35, scope: !579)
!1411 = !DILocalVariable(name: "addr", arg: 4, scope: !579, file: !1, line: 448, type: !482)
!1412 = !DILocation(line: 448, column: 45, scope: !579)
!1413 = !DILocalVariable(name: "addrlen", arg: 5, scope: !579, file: !1, line: 449, type: !252)
!1414 = !DILocation(line: 449, column: 35, scope: !579)
!1415 = !DILocalVariable(name: "err", scope: !579, file: !1, line: 450, type: !259)
!1416 = !DILocation(line: 450, column: 7, scope: !579)
!1417 = !DILocalVariable(name: "h", scope: !579, file: !1, line: 451, type: !1295)
!1418 = !DILocation(line: 451, column: 17, scope: !579)
!1419 = !DILocalVariable(name: "size", scope: !579, file: !1, line: 452, type: !476)
!1420 = !DILocation(line: 452, column: 11, scope: !579)
!1421 = !DILocation(line: 454, column: 3, scope: !579)
!1422 = !DILocation(line: 454, column: 3, scope: !1423)
!1423 = !DILexicalBlockFile(scope: !579, file: !1, discriminator: 1)
!1424 = !DILocation(line: 454, column: 3, scope: !1425)
!1425 = !DILexicalBlockFile(scope: !579, file: !1, discriminator: 2)
!1426 = !DILocation(line: 454, column: 3, scope: !1427)
!1427 = !DILexicalBlockFile(scope: !579, file: !1, discriminator: 3)
!1428 = !DILocation(line: 457, column: 7, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !579, file: !1, line: 457, column: 7)
!1430 = !DILocation(line: 457, column: 15, scope: !1429)
!1431 = !DILocation(line: 457, column: 32, scope: !1429)
!1432 = !DILocation(line: 457, column: 7, scope: !579)
!1433 = !DILocation(line: 458, column: 5, scope: !1429)
!1434 = !DILocation(line: 460, column: 37, scope: !579)
!1435 = !DILocation(line: 460, column: 45, scope: !579)
!1436 = !DILocation(line: 460, column: 51, scope: !579)
!1437 = !DILocation(line: 460, column: 9, scope: !579)
!1438 = !DILocation(line: 460, column: 7, scope: !579)
!1439 = !DILocation(line: 461, column: 7, scope: !1440)
!1440 = distinct !DILexicalBlock(scope: !579, file: !1, line: 461, column: 7)
!1441 = !DILocation(line: 461, column: 7, scope: !579)
!1442 = !DILocation(line: 462, column: 12, scope: !1440)
!1443 = !DILocation(line: 462, column: 5, scope: !1440)
!1444 = !DILocation(line: 464, column: 3, scope: !579)
!1445 = !DILocation(line: 465, column: 35, scope: !579)
!1446 = !DILocation(line: 465, column: 16, scope: !579)
!1447 = !DILocation(line: 465, column: 5, scope: !579)
!1448 = !DILocation(line: 465, column: 14, scope: !579)
!1449 = !DILocation(line: 466, column: 19, scope: !579)
!1450 = !DILocation(line: 466, column: 5, scope: !579)
!1451 = !DILocation(line: 466, column: 17, scope: !579)
!1452 = !DILocation(line: 467, column: 31, scope: !579)
!1453 = !DILocation(line: 467, column: 15, scope: !579)
!1454 = !DILocation(line: 467, column: 5, scope: !579)
!1455 = !DILocation(line: 467, column: 13, scope: !579)
!1456 = !DILocation(line: 468, column: 18, scope: !579)
!1457 = !DILocation(line: 468, column: 5, scope: !579)
!1458 = !DILocation(line: 468, column: 16, scope: !579)
!1459 = !DILocation(line: 470, column: 3, scope: !579)
!1460 = !DILocation(line: 471, column: 20, scope: !1461)
!1461 = distinct !DILexicalBlock(scope: !579, file: !1, line: 470, column: 6)
!1462 = !DILocation(line: 471, column: 28, scope: !1461)
!1463 = !DILocation(line: 471, column: 39, scope: !1461)
!1464 = !DILocation(line: 471, column: 12, scope: !1461)
!1465 = !DILocation(line: 471, column: 10, scope: !1461)
!1466 = !DILocation(line: 472, column: 3, scope: !1461)
!1467 = !DILocation(line: 472, column: 12, scope: !1423)
!1468 = !DILocation(line: 472, column: 17, scope: !1423)
!1469 = !DILocation(line: 472, column: 23, scope: !1423)
!1470 = !DILocation(line: 472, column: 26, scope: !1425)
!1471 = !DILocation(line: 472, column: 32, scope: !1425)
!1472 = !DILocation(line: 472, column: 3, scope: !1473)
!1473 = !DILexicalBlockFile(scope: !1461, file: !1, discriminator: 3)
!1474 = !DILocation(line: 474, column: 7, scope: !1475)
!1475 = distinct !DILexicalBlock(scope: !579, file: !1, line: 474, column: 7)
!1476 = !DILocation(line: 474, column: 12, scope: !1475)
!1477 = !DILocation(line: 474, column: 7, scope: !579)
!1478 = !DILocation(line: 475, column: 9, scope: !1479)
!1479 = distinct !DILexicalBlock(scope: !1480, file: !1, line: 475, column: 9)
!1480 = distinct !DILexicalBlock(scope: !1475, file: !1, line: 474, column: 19)
!1481 = !DILocation(line: 475, column: 15, scope: !1479)
!1482 = !DILocation(line: 475, column: 25, scope: !1479)
!1483 = !DILocation(line: 475, column: 28, scope: !1484)
!1484 = !DILexicalBlockFile(scope: !1479, file: !1, discriminator: 1)
!1485 = !DILocation(line: 475, column: 34, scope: !1484)
!1486 = !DILocation(line: 475, column: 9, scope: !1484)
!1487 = !DILocation(line: 476, column: 7, scope: !1479)
!1488 = !DILocation(line: 478, column: 15, scope: !1479)
!1489 = !DILocation(line: 478, column: 14, scope: !1479)
!1490 = !DILocation(line: 478, column: 7, scope: !1479)
!1491 = !DILocation(line: 481, column: 10, scope: !579)
!1492 = !DILocation(line: 481, column: 3, scope: !579)
!1493 = !DILocation(line: 482, column: 1, scope: !579)
!1494 = !DILocalVariable(name: "loop", arg: 1, scope: !582, file: !1, line: 579, type: !246)
!1495 = !DILocation(line: 579, column: 31, scope: !582)
!1496 = !DILocalVariable(name: "handle", arg: 2, scope: !582, file: !1, line: 579, type: !240)
!1497 = !DILocation(line: 579, column: 47, scope: !582)
!1498 = !DILocalVariable(name: "flags", arg: 3, scope: !582, file: !1, line: 579, type: !252)
!1499 = !DILocation(line: 579, column: 68, scope: !582)
!1500 = !DILocalVariable(name: "domain", scope: !582, file: !1, line: 580, type: !259)
!1501 = !DILocation(line: 580, column: 7, scope: !582)
!1502 = !DILocalVariable(name: "err", scope: !582, file: !1, line: 581, type: !259)
!1503 = !DILocation(line: 581, column: 7, scope: !582)
!1504 = !DILocalVariable(name: "fd", scope: !582, file: !1, line: 582, type: !259)
!1505 = !DILocation(line: 582, column: 7, scope: !582)
!1506 = !DILocation(line: 585, column: 12, scope: !582)
!1507 = !DILocation(line: 585, column: 18, scope: !582)
!1508 = !DILocation(line: 585, column: 10, scope: !582)
!1509 = !DILocation(line: 586, column: 7, scope: !1510)
!1510 = distinct !DILexicalBlock(scope: !582, file: !1, line: 586, column: 7)
!1511 = !DILocation(line: 586, column: 14, scope: !1510)
!1512 = !DILocation(line: 586, column: 25, scope: !1510)
!1513 = !DILocation(line: 586, column: 28, scope: !1514)
!1514 = !DILexicalBlockFile(scope: !1510, file: !1, discriminator: 1)
!1515 = !DILocation(line: 586, column: 35, scope: !1514)
!1516 = !DILocation(line: 586, column: 47, scope: !1514)
!1517 = !DILocation(line: 586, column: 50, scope: !1518)
!1518 = !DILexicalBlockFile(scope: !1510, file: !1, discriminator: 2)
!1519 = !DILocation(line: 586, column: 57, scope: !1518)
!1520 = !DILocation(line: 586, column: 7, scope: !1518)
!1521 = !DILocation(line: 587, column: 5, scope: !1510)
!1522 = !DILocation(line: 589, column: 7, scope: !1523)
!1523 = distinct !DILexicalBlock(scope: !582, file: !1, line: 589, column: 7)
!1524 = !DILocation(line: 589, column: 13, scope: !1523)
!1525 = !DILocation(line: 589, column: 7, scope: !582)
!1526 = !DILocation(line: 590, column: 5, scope: !1523)
!1527 = !DILocation(line: 592, column: 7, scope: !1528)
!1528 = distinct !DILexicalBlock(scope: !582, file: !1, line: 592, column: 7)
!1529 = !DILocation(line: 592, column: 14, scope: !1528)
!1530 = !DILocation(line: 592, column: 7, scope: !582)
!1531 = !DILocation(line: 593, column: 22, scope: !1532)
!1532 = distinct !DILexicalBlock(scope: !1528, file: !1, line: 592, column: 28)
!1533 = !DILocation(line: 593, column: 11, scope: !1532)
!1534 = !DILocation(line: 593, column: 9, scope: !1532)
!1535 = !DILocation(line: 594, column: 9, scope: !1536)
!1536 = distinct !DILexicalBlock(scope: !1532, file: !1, line: 594, column: 9)
!1537 = !DILocation(line: 594, column: 13, scope: !1536)
!1538 = !DILocation(line: 594, column: 9, scope: !1532)
!1539 = !DILocation(line: 595, column: 14, scope: !1536)
!1540 = !DILocation(line: 595, column: 7, scope: !1536)
!1541 = !DILocation(line: 596, column: 10, scope: !1532)
!1542 = !DILocation(line: 596, column: 8, scope: !1532)
!1543 = !DILocation(line: 597, column: 3, scope: !1532)
!1544 = !DILocation(line: 598, column: 8, scope: !1545)
!1545 = distinct !DILexicalBlock(scope: !1528, file: !1, line: 597, column: 10)
!1546 = !DILocation(line: 601, column: 3, scope: !582)
!1547 = !DILocation(line: 601, column: 3, scope: !1548)
!1548 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 1)
!1549 = distinct !DILexicalBlock(scope: !582, file: !1, line: 601, column: 3)
!1550 = !DILocation(line: 601, column: 3, scope: !1551)
!1551 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 2)
!1552 = distinct !DILexicalBlock(scope: !1549, file: !1, line: 601, column: 3)
!1553 = !DILocation(line: 601, column: 3, scope: !1554)
!1554 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 3)
!1555 = !DILocation(line: 602, column: 3, scope: !582)
!1556 = !DILocation(line: 602, column: 11, scope: !582)
!1557 = !DILocation(line: 602, column: 20, scope: !582)
!1558 = !DILocation(line: 603, column: 3, scope: !582)
!1559 = !DILocation(line: 603, column: 11, scope: !582)
!1560 = !DILocation(line: 603, column: 19, scope: !582)
!1561 = !DILocation(line: 604, column: 3, scope: !582)
!1562 = !DILocation(line: 604, column: 11, scope: !582)
!1563 = !DILocation(line: 604, column: 27, scope: !582)
!1564 = !DILocation(line: 605, column: 3, scope: !582)
!1565 = !DILocation(line: 605, column: 11, scope: !582)
!1566 = !DILocation(line: 605, column: 28, scope: !582)
!1567 = !DILocation(line: 606, column: 16, scope: !582)
!1568 = !DILocation(line: 606, column: 24, scope: !582)
!1569 = !DILocation(line: 606, column: 48, scope: !582)
!1570 = !DILocation(line: 606, column: 3, scope: !582)
!1571 = !DILocation(line: 607, column: 3, scope: !582)
!1572 = !DILocation(line: 607, column: 3, scope: !1573)
!1573 = !DILexicalBlockFile(scope: !1574, file: !1, discriminator: 1)
!1574 = distinct !DILexicalBlock(scope: !582, file: !1, line: 607, column: 3)
!1575 = !DILocation(line: 608, column: 3, scope: !582)
!1576 = !DILocation(line: 608, column: 3, scope: !1577)
!1577 = !DILexicalBlockFile(scope: !1578, file: !1, discriminator: 1)
!1578 = distinct !DILexicalBlock(scope: !582, file: !1, line: 608, column: 3)
!1579 = !DILocation(line: 609, column: 3, scope: !582)
!1580 = !DILocation(line: 610, column: 1, scope: !582)
!1581 = !DILocalVariable(name: "loop", arg: 1, scope: !627, file: !1, line: 135, type: !246)
!1582 = !DILocation(line: 135, column: 35, scope: !627)
!1583 = !DILocalVariable(name: "w", arg: 2, scope: !627, file: !1, line: 135, type: !264)
!1584 = !DILocation(line: 135, column: 51, scope: !627)
!1585 = !DILocalVariable(name: "revents", arg: 3, scope: !627, file: !1, line: 135, type: !252)
!1586 = !DILocation(line: 135, column: 67, scope: !627)
!1587 = !DILocalVariable(name: "handle", scope: !627, file: !1, line: 136, type: !240)
!1588 = !DILocation(line: 136, column: 13, scope: !627)
!1589 = !DILocation(line: 138, column: 12, scope: !627)
!1590 = !DILocation(line: 138, column: 10, scope: !627)
!1591 = !DILocation(line: 139, column: 3, scope: !627)
!1592 = !DILocation(line: 139, column: 3, scope: !1593)
!1593 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 1)
!1594 = !DILocation(line: 139, column: 3, scope: !1595)
!1595 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 2)
!1596 = !DILocation(line: 139, column: 3, scope: !1597)
!1597 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 3)
!1598 = !DILocation(line: 141, column: 7, scope: !1599)
!1599 = distinct !DILexicalBlock(scope: !627, file: !1, line: 141, column: 7)
!1600 = !DILocation(line: 141, column: 15, scope: !1599)
!1601 = !DILocation(line: 141, column: 7, scope: !627)
!1602 = !DILocation(line: 142, column: 21, scope: !1599)
!1603 = !DILocation(line: 142, column: 5, scope: !1599)
!1604 = !DILocation(line: 144, column: 7, scope: !1605)
!1605 = distinct !DILexicalBlock(scope: !627, file: !1, line: 144, column: 7)
!1606 = !DILocation(line: 144, column: 15, scope: !1605)
!1607 = !DILocation(line: 144, column: 7, scope: !627)
!1608 = !DILocation(line: 145, column: 21, scope: !1609)
!1609 = distinct !DILexicalBlock(scope: !1605, file: !1, line: 144, column: 26)
!1610 = !DILocation(line: 145, column: 5, scope: !1609)
!1611 = !DILocation(line: 146, column: 27, scope: !1609)
!1612 = !DILocation(line: 146, column: 5, scope: !1609)
!1613 = !DILocation(line: 147, column: 3, scope: !1609)
!1614 = !DILocation(line: 148, column: 1, scope: !627)
!1615 = !DILocalVariable(name: "loop", arg: 1, scope: !585, file: !1, line: 613, type: !246)
!1616 = !DILocation(line: 613, column: 28, scope: !585)
!1617 = !DILocalVariable(name: "handle", arg: 2, scope: !585, file: !1, line: 613, type: !240)
!1618 = !DILocation(line: 613, column: 44, scope: !585)
!1619 = !DILocation(line: 614, column: 25, scope: !585)
!1620 = !DILocation(line: 614, column: 31, scope: !585)
!1621 = !DILocation(line: 614, column: 10, scope: !585)
!1622 = !DILocation(line: 614, column: 3, scope: !585)
!1623 = !DILocalVariable(name: "handle", arg: 1, scope: !588, file: !1, line: 618, type: !240)
!1624 = !DILocation(line: 618, column: 27, scope: !588)
!1625 = !DILocalVariable(name: "sock", arg: 2, scope: !588, file: !1, line: 618, type: !591)
!1626 = !DILocation(line: 618, column: 48, scope: !588)
!1627 = !DILocalVariable(name: "err", scope: !588, file: !1, line: 619, type: !259)
!1628 = !DILocation(line: 619, column: 7, scope: !588)
!1629 = !DILocation(line: 622, column: 7, scope: !1630)
!1630 = distinct !DILexicalBlock(scope: !588, file: !1, line: 622, column: 7)
!1631 = !DILocation(line: 622, column: 15, scope: !1630)
!1632 = !DILocation(line: 622, column: 26, scope: !1630)
!1633 = !DILocation(line: 622, column: 29, scope: !1630)
!1634 = !DILocation(line: 622, column: 7, scope: !588)
!1635 = !DILocation(line: 623, column: 5, scope: !1630)
!1636 = !DILocation(line: 625, column: 22, scope: !588)
!1637 = !DILocation(line: 625, column: 9, scope: !588)
!1638 = !DILocation(line: 625, column: 7, scope: !588)
!1639 = !DILocation(line: 626, column: 7, scope: !1640)
!1640 = distinct !DILexicalBlock(scope: !588, file: !1, line: 626, column: 7)
!1641 = !DILocation(line: 626, column: 7, scope: !588)
!1642 = !DILocation(line: 627, column: 12, scope: !1640)
!1643 = !DILocation(line: 627, column: 5, scope: !1640)
!1644 = !DILocation(line: 629, column: 23, scope: !588)
!1645 = !DILocation(line: 629, column: 9, scope: !588)
!1646 = !DILocation(line: 629, column: 7, scope: !588)
!1647 = !DILocation(line: 630, column: 7, scope: !1648)
!1648 = distinct !DILexicalBlock(scope: !588, file: !1, line: 630, column: 7)
!1649 = !DILocation(line: 630, column: 7, scope: !588)
!1650 = !DILocation(line: 631, column: 12, scope: !1648)
!1651 = !DILocation(line: 631, column: 5, scope: !1648)
!1652 = !DILocation(line: 633, column: 27, scope: !588)
!1653 = !DILocation(line: 633, column: 3, scope: !588)
!1654 = !DILocation(line: 633, column: 11, scope: !588)
!1655 = !DILocation(line: 633, column: 22, scope: !588)
!1656 = !DILocation(line: 633, column: 25, scope: !588)
!1657 = !DILocation(line: 634, column: 3, scope: !588)
!1658 = !DILocation(line: 635, column: 1, scope: !588)
!1659 = !DILocalVariable(name: "handle", arg: 1, scope: !592, file: !1, line: 638, type: !240)
!1660 = !DILocation(line: 638, column: 37, scope: !592)
!1661 = !DILocalVariable(name: "multicast_addr", arg: 2, scope: !592, file: !1, line: 639, type: !595)
!1662 = !DILocation(line: 639, column: 39, scope: !592)
!1663 = !DILocalVariable(name: "interface_addr", arg: 3, scope: !592, file: !1, line: 640, type: !595)
!1664 = !DILocation(line: 640, column: 39, scope: !592)
!1665 = !DILocalVariable(name: "membership", arg: 4, scope: !592, file: !1, line: 641, type: !597)
!1666 = !DILocation(line: 641, column: 41, scope: !592)
!1667 = !DILocalVariable(name: "err", scope: !592, file: !1, line: 642, type: !259)
!1668 = !DILocation(line: 642, column: 7, scope: !592)
!1669 = !DILocalVariable(name: "addr4", scope: !592, file: !1, line: 643, type: !526)
!1670 = !DILocation(line: 643, column: 22, scope: !592)
!1671 = !DILocalVariable(name: "addr6", scope: !592, file: !1, line: 644, type: !544)
!1672 = !DILocation(line: 644, column: 23, scope: !592)
!1673 = !DILocation(line: 646, column: 19, scope: !1674)
!1674 = distinct !DILexicalBlock(scope: !592, file: !1, line: 646, column: 7)
!1675 = !DILocation(line: 646, column: 7, scope: !1674)
!1676 = !DILocation(line: 646, column: 46, scope: !1674)
!1677 = !DILocation(line: 646, column: 7, scope: !592)
!1678 = !DILocation(line: 647, column: 39, scope: !1679)
!1679 = distinct !DILexicalBlock(scope: !1674, file: !1, line: 646, column: 52)
!1680 = !DILocation(line: 647, column: 11, scope: !1679)
!1681 = !DILocation(line: 647, column: 9, scope: !1679)
!1682 = !DILocation(line: 648, column: 9, scope: !1683)
!1683 = distinct !DILexicalBlock(scope: !1679, file: !1, line: 648, column: 9)
!1684 = !DILocation(line: 648, column: 9, scope: !1679)
!1685 = !DILocation(line: 649, column: 14, scope: !1683)
!1686 = !DILocation(line: 649, column: 7, scope: !1683)
!1687 = !DILocation(line: 650, column: 36, scope: !1679)
!1688 = !DILocation(line: 650, column: 52, scope: !1679)
!1689 = !DILocation(line: 650, column: 68, scope: !1679)
!1690 = !DILocation(line: 650, column: 12, scope: !1679)
!1691 = !DILocation(line: 650, column: 5, scope: !1679)
!1692 = !DILocation(line: 651, column: 26, scope: !1693)
!1693 = distinct !DILexicalBlock(scope: !1674, file: !1, line: 651, column: 14)
!1694 = !DILocation(line: 651, column: 14, scope: !1693)
!1695 = !DILocation(line: 651, column: 53, scope: !1693)
!1696 = !DILocation(line: 651, column: 14, scope: !1674)
!1697 = !DILocation(line: 652, column: 39, scope: !1698)
!1698 = distinct !DILexicalBlock(scope: !1693, file: !1, line: 651, column: 59)
!1699 = !DILocation(line: 652, column: 11, scope: !1698)
!1700 = !DILocation(line: 652, column: 9, scope: !1698)
!1701 = !DILocation(line: 653, column: 9, scope: !1702)
!1702 = distinct !DILexicalBlock(scope: !1698, file: !1, line: 653, column: 9)
!1703 = !DILocation(line: 653, column: 9, scope: !1698)
!1704 = !DILocation(line: 654, column: 14, scope: !1702)
!1705 = !DILocation(line: 654, column: 7, scope: !1702)
!1706 = !DILocation(line: 655, column: 36, scope: !1698)
!1707 = !DILocation(line: 655, column: 52, scope: !1698)
!1708 = !DILocation(line: 655, column: 68, scope: !1698)
!1709 = !DILocation(line: 655, column: 12, scope: !1698)
!1710 = !DILocation(line: 655, column: 5, scope: !1698)
!1711 = !DILocation(line: 657, column: 5, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !1693, file: !1, line: 656, column: 10)
!1713 = !DILocation(line: 659, column: 1, scope: !592)
!1714 = !DILocalVariable(name: "handle", arg: 1, scope: !631, file: !1, line: 485, type: !240)
!1715 = !DILocation(line: 485, column: 46, scope: !631)
!1716 = !DILocalVariable(name: "multicast_addr", arg: 2, scope: !631, file: !1, line: 486, type: !634)
!1717 = !DILocation(line: 486, column: 62, scope: !631)
!1718 = !DILocalVariable(name: "interface_addr", arg: 3, scope: !631, file: !1, line: 487, type: !595)
!1719 = !DILocation(line: 487, column: 48, scope: !631)
!1720 = !DILocalVariable(name: "membership", arg: 4, scope: !631, file: !1, line: 488, type: !597)
!1721 = !DILocation(line: 488, column: 50, scope: !631)
!1722 = !DILocalVariable(name: "mreq", scope: !631, file: !1, line: 489, type: !1723)
!1723 = !DICompositeType(tag: DW_TAG_structure_type, name: "ip_mreq", file: !64, line: 264, size: 64, align: 32, elements: !1724)
!1724 = !{!1725, !1726}
!1725 = !DIDerivedType(tag: DW_TAG_member, name: "imr_multiaddr", scope: !1723, file: !64, line: 267, baseType: !533, size: 32, align: 32)
!1726 = !DIDerivedType(tag: DW_TAG_member, name: "imr_interface", scope: !1723, file: !64, line: 270, baseType: !533, size: 32, align: 32, offset: 32)
!1727 = !DILocation(line: 489, column: 18, scope: !631)
!1728 = !DILocalVariable(name: "optname", scope: !631, file: !1, line: 490, type: !259)
!1729 = !DILocation(line: 490, column: 7, scope: !631)
!1730 = !DILocalVariable(name: "err", scope: !631, file: !1, line: 491, type: !259)
!1731 = !DILocation(line: 491, column: 7, scope: !631)
!1732 = !DILocation(line: 493, column: 3, scope: !631)
!1733 = !DILocation(line: 495, column: 7, scope: !1734)
!1734 = distinct !DILexicalBlock(scope: !631, file: !1, line: 495, column: 7)
!1735 = !DILocation(line: 495, column: 7, scope: !631)
!1736 = !DILocation(line: 496, column: 33, scope: !1737)
!1737 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 495, column: 23)
!1738 = !DILocation(line: 496, column: 55, scope: !1737)
!1739 = !DILocation(line: 496, column: 69, scope: !1737)
!1740 = !DILocation(line: 496, column: 49, scope: !1737)
!1741 = !DILocation(line: 496, column: 11, scope: !1737)
!1742 = !DILocation(line: 496, column: 9, scope: !1737)
!1743 = !DILocation(line: 497, column: 9, scope: !1744)
!1744 = distinct !DILexicalBlock(scope: !1737, file: !1, line: 497, column: 9)
!1745 = !DILocation(line: 497, column: 9, scope: !1737)
!1746 = !DILocation(line: 498, column: 14, scope: !1744)
!1747 = !DILocation(line: 498, column: 7, scope: !1744)
!1748 = !DILocation(line: 499, column: 3, scope: !1737)
!1749 = !DILocation(line: 500, column: 33, scope: !1750)
!1750 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 499, column: 10)
!1751 = !DILocation(line: 500, column: 10, scope: !1750)
!1752 = !DILocation(line: 500, column: 24, scope: !1750)
!1753 = !DILocation(line: 500, column: 31, scope: !1750)
!1754 = !DILocation(line: 503, column: 31, scope: !631)
!1755 = !DILocation(line: 503, column: 47, scope: !631)
!1756 = !DILocation(line: 503, column: 56, scope: !631)
!1757 = !DILocation(line: 503, column: 8, scope: !631)
!1758 = !DILocation(line: 503, column: 22, scope: !631)
!1759 = !DILocation(line: 503, column: 29, scope: !631)
!1760 = !DILocation(line: 505, column: 11, scope: !631)
!1761 = !DILocation(line: 505, column: 3, scope: !631)
!1762 = !DILocation(line: 507, column: 13, scope: !1763)
!1763 = distinct !DILexicalBlock(scope: !631, file: !1, line: 505, column: 23)
!1764 = !DILocation(line: 508, column: 5, scope: !1763)
!1765 = !DILocation(line: 510, column: 13, scope: !1763)
!1766 = !DILocation(line: 511, column: 5, scope: !1763)
!1767 = !DILocation(line: 513, column: 5, scope: !1763)
!1768 = !DILocation(line: 516, column: 18, scope: !1769)
!1769 = distinct !DILexicalBlock(scope: !631, file: !1, line: 516, column: 7)
!1770 = !DILocation(line: 516, column: 26, scope: !1769)
!1771 = !DILocation(line: 516, column: 37, scope: !1769)
!1772 = !DILocation(line: 518, column: 18, scope: !1769)
!1773 = !DILocation(line: 519, column: 18, scope: !1769)
!1774 = !DILocation(line: 516, column: 7, scope: !1769)
!1775 = !DILocation(line: 516, column: 7, scope: !631)
!1776 = !DILocation(line: 525, column: 13, scope: !1777)
!1777 = distinct !DILexicalBlock(scope: !1769, file: !1, line: 520, column: 33)
!1778 = !DILocation(line: 525, column: 12, scope: !1777)
!1779 = !DILocation(line: 525, column: 5, scope: !1777)
!1780 = !DILocation(line: 528, column: 3, scope: !631)
!1781 = !DILocation(line: 529, column: 1, scope: !631)
!1782 = !DILocalVariable(name: "handle", arg: 1, scope: !636, file: !1, line: 532, type: !240)
!1783 = !DILocation(line: 532, column: 46, scope: !636)
!1784 = !DILocalVariable(name: "multicast_addr", arg: 2, scope: !636, file: !1, line: 533, type: !639)
!1785 = !DILocation(line: 533, column: 63, scope: !636)
!1786 = !DILocalVariable(name: "interface_addr", arg: 3, scope: !636, file: !1, line: 534, type: !595)
!1787 = !DILocation(line: 534, column: 48, scope: !636)
!1788 = !DILocalVariable(name: "membership", arg: 4, scope: !636, file: !1, line: 535, type: !597)
!1789 = !DILocation(line: 535, column: 50, scope: !636)
!1790 = !DILocalVariable(name: "optname", scope: !636, file: !1, line: 536, type: !259)
!1791 = !DILocation(line: 536, column: 7, scope: !636)
!1792 = !DILocalVariable(name: "mreq", scope: !636, file: !1, line: 537, type: !1793)
!1793 = !DICompositeType(tag: DW_TAG_structure_type, name: "ipv6_mreq", file: !64, line: 288, size: 160, align: 32, elements: !1794)
!1794 = !{!1795, !1796}
!1795 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6mr_multiaddr", scope: !1793, file: !64, line: 291, baseType: !550, size: 128, align: 32)
!1796 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6mr_interface", scope: !1793, file: !64, line: 294, baseType: !252, size: 32, align: 32, offset: 128)
!1797 = !DILocation(line: 537, column: 20, scope: !636)
!1798 = !DILocalVariable(name: "addr6", scope: !636, file: !1, line: 538, type: !544)
!1799 = !DILocation(line: 538, column: 23, scope: !636)
!1800 = !DILocation(line: 540, column: 3, scope: !636)
!1801 = !DILocation(line: 542, column: 7, scope: !1802)
!1802 = distinct !DILexicalBlock(scope: !636, file: !1, line: 542, column: 7)
!1803 = !DILocation(line: 542, column: 7, scope: !636)
!1804 = !DILocation(line: 543, column: 21, scope: !1805)
!1805 = distinct !DILexicalBlock(scope: !1806, file: !1, line: 543, column: 9)
!1806 = distinct !DILexicalBlock(scope: !1802, file: !1, line: 542, column: 23)
!1807 = !DILocation(line: 543, column: 9, scope: !1805)
!1808 = !DILocation(line: 543, column: 9, scope: !1806)
!1809 = !DILocation(line: 544, column: 7, scope: !1805)
!1810 = !DILocation(line: 545, column: 35, scope: !1806)
!1811 = !DILocation(line: 545, column: 10, scope: !1806)
!1812 = !DILocation(line: 545, column: 27, scope: !1806)
!1813 = !DILocation(line: 546, column: 3, scope: !1806)
!1814 = !DILocation(line: 547, column: 10, scope: !1815)
!1815 = distinct !DILexicalBlock(scope: !1802, file: !1, line: 546, column: 10)
!1816 = !DILocation(line: 547, column: 27, scope: !1815)
!1817 = !DILocation(line: 550, column: 8, scope: !636)
!1818 = !DILocation(line: 550, column: 27, scope: !636)
!1819 = !DILocation(line: 550, column: 43, scope: !636)
!1820 = !DILocation(line: 552, column: 11, scope: !636)
!1821 = !DILocation(line: 552, column: 3, scope: !636)
!1822 = !DILocation(line: 554, column: 13, scope: !1823)
!1823 = distinct !DILexicalBlock(scope: !636, file: !1, line: 552, column: 23)
!1824 = !DILocation(line: 555, column: 5, scope: !1823)
!1825 = !DILocation(line: 557, column: 13, scope: !1823)
!1826 = !DILocation(line: 558, column: 5, scope: !1823)
!1827 = !DILocation(line: 560, column: 5, scope: !1823)
!1828 = !DILocation(line: 563, column: 18, scope: !1829)
!1829 = distinct !DILexicalBlock(scope: !636, file: !1, line: 563, column: 7)
!1830 = !DILocation(line: 563, column: 26, scope: !1829)
!1831 = !DILocation(line: 563, column: 37, scope: !1829)
!1832 = !DILocation(line: 565, column: 18, scope: !1829)
!1833 = !DILocation(line: 566, column: 18, scope: !1829)
!1834 = !DILocation(line: 563, column: 7, scope: !1829)
!1835 = !DILocation(line: 563, column: 7, scope: !636)
!1836 = !DILocation(line: 572, column: 13, scope: !1837)
!1837 = distinct !DILexicalBlock(scope: !1829, file: !1, line: 567, column: 33)
!1838 = !DILocation(line: 572, column: 12, scope: !1837)
!1839 = !DILocation(line: 572, column: 5, scope: !1837)
!1840 = !DILocation(line: 575, column: 3, scope: !636)
!1841 = !DILocation(line: 576, column: 1, scope: !636)
!1842 = !DILocalVariable(name: "handle", arg: 1, scope: !598, file: !1, line: 705, type: !240)
!1843 = !DILocation(line: 705, column: 36, scope: !598)
!1844 = !DILocalVariable(name: "on", arg: 2, scope: !598, file: !1, line: 705, type: !259)
!1845 = !DILocation(line: 705, column: 48, scope: !598)
!1846 = !DILocation(line: 706, column: 18, scope: !1847)
!1847 = distinct !DILexicalBlock(scope: !598, file: !1, line: 706, column: 7)
!1848 = !DILocation(line: 706, column: 26, scope: !1847)
!1849 = !DILocation(line: 706, column: 37, scope: !1847)
!1850 = !DILocation(line: 709, column: 18, scope: !1847)
!1851 = !DILocation(line: 706, column: 7, scope: !1847)
!1852 = !DILocation(line: 706, column: 7, scope: !598)
!1853 = !DILocation(line: 711, column: 13, scope: !1854)
!1854 = distinct !DILexicalBlock(scope: !1847, file: !1, line: 710, column: 31)
!1855 = !DILocation(line: 711, column: 12, scope: !1854)
!1856 = !DILocation(line: 711, column: 5, scope: !1854)
!1857 = !DILocation(line: 714, column: 3, scope: !598)
!1858 = !DILocation(line: 715, column: 1, scope: !598)
!1859 = !DILocalVariable(name: "handle", arg: 1, scope: !601, file: !1, line: 718, type: !240)
!1860 = !DILocation(line: 718, column: 30, scope: !601)
!1861 = !DILocalVariable(name: "ttl", arg: 2, scope: !601, file: !1, line: 718, type: !259)
!1862 = !DILocation(line: 718, column: 42, scope: !601)
!1863 = !DILocation(line: 719, column: 7, scope: !1864)
!1864 = distinct !DILexicalBlock(scope: !601, file: !1, line: 719, column: 7)
!1865 = !DILocation(line: 719, column: 11, scope: !1864)
!1866 = !DILocation(line: 719, column: 15, scope: !1864)
!1867 = !DILocation(line: 719, column: 18, scope: !1868)
!1868 = !DILexicalBlockFile(scope: !1864, file: !1, discriminator: 1)
!1869 = !DILocation(line: 719, column: 22, scope: !1868)
!1870 = !DILocation(line: 719, column: 7, scope: !1868)
!1871 = !DILocation(line: 720, column: 5, scope: !1864)
!1872 = !DILocation(line: 744, column: 36, scope: !601)
!1873 = !DILocation(line: 747, column: 36, scope: !601)
!1874 = !DILocation(line: 744, column: 10, scope: !601)
!1875 = !DILocation(line: 744, column: 3, scope: !601)
!1876 = !DILocation(line: 748, column: 1, scope: !601)
!1877 = !DILocalVariable(name: "handle", arg: 1, scope: !641, file: !1, line: 686, type: !240)
!1878 = !DILocation(line: 686, column: 48, scope: !641)
!1879 = !DILocalVariable(name: "option4", arg: 2, scope: !641, file: !1, line: 687, type: !259)
!1880 = !DILocation(line: 687, column: 42, scope: !641)
!1881 = !DILocalVariable(name: "option6", arg: 3, scope: !641, file: !1, line: 688, type: !259)
!1882 = !DILocation(line: 688, column: 42, scope: !641)
!1883 = !DILocalVariable(name: "val", arg: 4, scope: !641, file: !1, line: 689, type: !259)
!1884 = !DILocation(line: 689, column: 42, scope: !641)
!1885 = !DILocalVariable(name: "arg", scope: !641, file: !1, line: 695, type: !259)
!1886 = !DILocation(line: 695, column: 7, scope: !641)
!1887 = !DILocation(line: 695, column: 13, scope: !641)
!1888 = !DILocation(line: 698, column: 7, scope: !1889)
!1889 = distinct !DILexicalBlock(scope: !641, file: !1, line: 698, column: 7)
!1890 = !DILocation(line: 698, column: 11, scope: !1889)
!1891 = !DILocation(line: 698, column: 15, scope: !1889)
!1892 = !DILocation(line: 698, column: 18, scope: !1893)
!1893 = !DILexicalBlockFile(scope: !1889, file: !1, discriminator: 1)
!1894 = !DILocation(line: 698, column: 22, scope: !1893)
!1895 = !DILocation(line: 698, column: 7, scope: !1893)
!1896 = !DILocation(line: 699, column: 5, scope: !1889)
!1897 = !DILocation(line: 701, column: 25, scope: !641)
!1898 = !DILocation(line: 701, column: 33, scope: !641)
!1899 = !DILocation(line: 701, column: 42, scope: !641)
!1900 = !DILocation(line: 701, column: 51, scope: !641)
!1901 = !DILocation(line: 701, column: 10, scope: !641)
!1902 = !DILocation(line: 701, column: 3, scope: !641)
!1903 = !DILocation(line: 702, column: 1, scope: !641)
!1904 = !DILocalVariable(name: "handle", arg: 1, scope: !602, file: !1, line: 751, type: !240)
!1905 = !DILocation(line: 751, column: 40, scope: !602)
!1906 = !DILocalVariable(name: "ttl", arg: 2, scope: !602, file: !1, line: 751, type: !259)
!1907 = !DILocation(line: 751, column: 52, scope: !602)
!1908 = !DILocation(line: 767, column: 36, scope: !602)
!1909 = !DILocation(line: 770, column: 36, scope: !602)
!1910 = !DILocation(line: 767, column: 10, scope: !602)
!1911 = !DILocation(line: 767, column: 3, scope: !602)
!1912 = !DILocalVariable(name: "handle", arg: 1, scope: !603, file: !1, line: 774, type: !240)
!1913 = !DILocation(line: 774, column: 41, scope: !603)
!1914 = !DILocalVariable(name: "on", arg: 2, scope: !603, file: !1, line: 774, type: !259)
!1915 = !DILocation(line: 774, column: 53, scope: !603)
!1916 = !DILocation(line: 790, column: 36, scope: !603)
!1917 = !DILocation(line: 793, column: 36, scope: !603)
!1918 = !DILocation(line: 790, column: 10, scope: !603)
!1919 = !DILocation(line: 790, column: 3, scope: !603)
!1920 = !DILocalVariable(name: "handle", arg: 1, scope: !604, file: !1, line: 796, type: !240)
!1921 = !DILocation(line: 796, column: 46, scope: !604)
!1922 = !DILocalVariable(name: "interface_addr", arg: 2, scope: !604, file: !1, line: 796, type: !595)
!1923 = !DILocation(line: 796, column: 66, scope: !604)
!1924 = !DILocalVariable(name: "addr_st", scope: !604, file: !1, line: 797, type: !504)
!1925 = !DILocation(line: 797, column: 27, scope: !604)
!1926 = !DILocalVariable(name: "addr4", scope: !604, file: !1, line: 798, type: !525)
!1927 = !DILocation(line: 798, column: 23, scope: !604)
!1928 = !DILocalVariable(name: "addr6", scope: !604, file: !1, line: 799, type: !543)
!1929 = !DILocation(line: 799, column: 24, scope: !604)
!1930 = !DILocation(line: 801, column: 11, scope: !604)
!1931 = !DILocation(line: 801, column: 9, scope: !604)
!1932 = !DILocation(line: 802, column: 11, scope: !604)
!1933 = !DILocation(line: 802, column: 9, scope: !604)
!1934 = !DILocation(line: 804, column: 8, scope: !1935)
!1935 = distinct !DILexicalBlock(scope: !604, file: !1, line: 804, column: 7)
!1936 = !DILocation(line: 804, column: 7, scope: !604)
!1937 = !DILocation(line: 805, column: 5, scope: !1938)
!1938 = distinct !DILexicalBlock(scope: !1935, file: !1, line: 804, column: 24)
!1939 = !DILocation(line: 806, column: 9, scope: !1940)
!1940 = distinct !DILexicalBlock(scope: !1938, file: !1, line: 806, column: 9)
!1941 = !DILocation(line: 806, column: 17, scope: !1940)
!1942 = !DILocation(line: 806, column: 23, scope: !1940)
!1943 = !DILocation(line: 806, column: 9, scope: !1938)
!1944 = !DILocation(line: 807, column: 15, scope: !1945)
!1945 = distinct !DILexicalBlock(scope: !1940, file: !1, line: 806, column: 41)
!1946 = !DILocation(line: 807, column: 25, scope: !1945)
!1947 = !DILocation(line: 808, column: 7, scope: !1945)
!1948 = !DILocation(line: 808, column: 14, scope: !1945)
!1949 = !DILocation(line: 808, column: 28, scope: !1945)
!1950 = !DILocation(line: 809, column: 5, scope: !1945)
!1951 = !DILocation(line: 810, column: 15, scope: !1952)
!1952 = distinct !DILexicalBlock(scope: !1940, file: !1, line: 809, column: 12)
!1953 = !DILocation(line: 810, column: 25, scope: !1952)
!1954 = !DILocation(line: 811, column: 32, scope: !1952)
!1955 = !DILocation(line: 811, column: 7, scope: !1952)
!1956 = !DILocation(line: 811, column: 14, scope: !1952)
!1957 = !DILocation(line: 811, column: 23, scope: !1952)
!1958 = !DILocation(line: 811, column: 30, scope: !1952)
!1959 = !DILocation(line: 813, column: 3, scope: !1938)
!1960 = !DILocation(line: 813, column: 26, scope: !1961)
!1961 = !DILexicalBlockFile(scope: !1962, file: !1, discriminator: 1)
!1962 = distinct !DILexicalBlock(scope: !1935, file: !1, line: 813, column: 14)
!1963 = !DILocation(line: 813, column: 45, scope: !1961)
!1964 = !DILocation(line: 813, column: 14, scope: !1961)
!1965 = !DILocation(line: 813, column: 52, scope: !1961)
!1966 = !DILocation(line: 815, column: 3, scope: !1967)
!1967 = distinct !DILexicalBlock(scope: !1962, file: !1, line: 813, column: 58)
!1968 = !DILocation(line: 815, column: 26, scope: !1969)
!1969 = !DILexicalBlockFile(scope: !1970, file: !1, discriminator: 1)
!1970 = distinct !DILexicalBlock(scope: !1962, file: !1, line: 815, column: 14)
!1971 = !DILocation(line: 815, column: 45, scope: !1969)
!1972 = !DILocation(line: 815, column: 14, scope: !1969)
!1973 = !DILocation(line: 815, column: 52, scope: !1969)
!1974 = !DILocation(line: 817, column: 3, scope: !1975)
!1975 = distinct !DILexicalBlock(scope: !1970, file: !1, line: 815, column: 58)
!1976 = !DILocation(line: 818, column: 5, scope: !1977)
!1977 = distinct !DILexicalBlock(scope: !1970, file: !1, line: 817, column: 10)
!1978 = !DILocation(line: 821, column: 15, scope: !1979)
!1979 = distinct !DILexicalBlock(scope: !604, file: !1, line: 821, column: 7)
!1980 = !DILocation(line: 821, column: 7, scope: !1979)
!1981 = !DILocation(line: 821, column: 25, scope: !1979)
!1982 = !DILocation(line: 821, column: 7, scope: !604)
!1983 = !DILocation(line: 822, column: 20, scope: !1984)
!1984 = distinct !DILexicalBlock(scope: !1985, file: !1, line: 822, column: 9)
!1985 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 821, column: 37)
!1986 = !DILocation(line: 822, column: 28, scope: !1984)
!1987 = !DILocation(line: 822, column: 39, scope: !1984)
!1988 = !DILocation(line: 825, column: 29, scope: !1984)
!1989 = !DILocation(line: 825, column: 36, scope: !1984)
!1990 = !DILocation(line: 825, column: 20, scope: !1984)
!1991 = !DILocation(line: 822, column: 9, scope: !1984)
!1992 = !DILocation(line: 826, column: 45, scope: !1984)
!1993 = !DILocation(line: 822, column: 9, scope: !1985)
!1994 = !DILocation(line: 827, column: 15, scope: !1995)
!1995 = distinct !DILexicalBlock(scope: !1984, file: !1, line: 826, column: 52)
!1996 = !DILocation(line: 827, column: 14, scope: !1995)
!1997 = !DILocation(line: 827, column: 7, scope: !1995)
!1998 = !DILocation(line: 829, column: 3, scope: !1985)
!1999 = !DILocation(line: 829, column: 22, scope: !2000)
!2000 = !DILexicalBlockFile(scope: !2001, file: !1, discriminator: 1)
!2001 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 829, column: 14)
!2002 = !DILocation(line: 829, column: 14, scope: !2000)
!2003 = !DILocation(line: 829, column: 32, scope: !2000)
!2004 = !DILocation(line: 830, column: 20, scope: !2005)
!2005 = distinct !DILexicalBlock(scope: !2006, file: !1, line: 830, column: 9)
!2006 = distinct !DILexicalBlock(scope: !2001, file: !1, line: 829, column: 45)
!2007 = !DILocation(line: 830, column: 28, scope: !2005)
!2008 = !DILocation(line: 830, column: 39, scope: !2005)
!2009 = !DILocation(line: 833, column: 21, scope: !2005)
!2010 = !DILocation(line: 833, column: 28, scope: !2005)
!2011 = !DILocation(line: 833, column: 20, scope: !2005)
!2012 = !DILocation(line: 830, column: 9, scope: !2005)
!2013 = !DILocation(line: 834, column: 50, scope: !2005)
!2014 = !DILocation(line: 830, column: 9, scope: !2006)
!2015 = !DILocation(line: 835, column: 15, scope: !2016)
!2016 = distinct !DILexicalBlock(scope: !2005, file: !1, line: 834, column: 57)
!2017 = !DILocation(line: 835, column: 14, scope: !2016)
!2018 = !DILocation(line: 835, column: 7, scope: !2016)
!2019 = !DILocation(line: 837, column: 3, scope: !2006)
!2020 = !DILocation(line: 838, column: 5, scope: !2021)
!2021 = distinct !DILexicalBlock(scope: !2001, file: !1, line: 837, column: 10)
!2022 = !DILocation(line: 842, column: 3, scope: !604)
!2023 = !DILocation(line: 843, column: 1, scope: !604)
!2024 = !DILocalVariable(name: "handle", arg: 1, scope: !607, file: !1, line: 846, type: !610)
!2025 = !DILocation(line: 846, column: 40, scope: !607)
!2026 = !DILocalVariable(name: "name", arg: 2, scope: !607, file: !1, line: 847, type: !518)
!2027 = !DILocation(line: 847, column: 41, scope: !607)
!2028 = !DILocalVariable(name: "namelen", arg: 3, scope: !607, file: !1, line: 848, type: !612)
!2029 = !DILocation(line: 848, column: 29, scope: !607)
!2030 = !DILocalVariable(name: "socklen", scope: !607, file: !1, line: 849, type: !565)
!2031 = !DILocation(line: 849, column: 13, scope: !607)
!2032 = !DILocation(line: 851, column: 7, scope: !2033)
!2033 = distinct !DILexicalBlock(scope: !607, file: !1, line: 851, column: 7)
!2034 = !DILocation(line: 851, column: 15, scope: !2033)
!2035 = !DILocation(line: 851, column: 26, scope: !2033)
!2036 = !DILocation(line: 851, column: 29, scope: !2033)
!2037 = !DILocation(line: 851, column: 7, scope: !607)
!2038 = !DILocation(line: 852, column: 5, scope: !2033)
!2039 = !DILocation(line: 855, column: 26, scope: !607)
!2040 = !DILocation(line: 855, column: 25, scope: !607)
!2041 = !DILocation(line: 855, column: 11, scope: !607)
!2042 = !DILocation(line: 857, column: 19, scope: !2043)
!2043 = distinct !DILexicalBlock(scope: !607, file: !1, line: 857, column: 7)
!2044 = !DILocation(line: 857, column: 27, scope: !2043)
!2045 = !DILocation(line: 857, column: 38, scope: !2043)
!2046 = !DILocation(line: 857, column: 42, scope: !2043)
!2047 = !DILocation(line: 857, column: 7, scope: !2043)
!2048 = !DILocation(line: 857, column: 7, scope: !607)
!2049 = !DILocation(line: 858, column: 13, scope: !2043)
!2050 = !DILocation(line: 858, column: 12, scope: !2043)
!2051 = !DILocation(line: 858, column: 5, scope: !2043)
!2052 = !DILocation(line: 860, column: 20, scope: !607)
!2053 = !DILocation(line: 860, column: 4, scope: !607)
!2054 = !DILocation(line: 860, column: 12, scope: !607)
!2055 = !DILocation(line: 861, column: 3, scope: !607)
!2056 = !DILocation(line: 862, column: 1, scope: !607)
!2057 = !DILocalVariable(name: "handle", arg: 1, scope: !613, file: !1, line: 865, type: !240)
!2058 = !DILocation(line: 865, column: 34, scope: !613)
!2059 = !DILocalVariable(name: "alloc_cb", arg: 2, scope: !613, file: !1, line: 866, type: !460)
!2060 = !DILocation(line: 866, column: 36, scope: !613)
!2061 = !DILocalVariable(name: "recv_cb", arg: 3, scope: !613, file: !1, line: 867, type: !472)
!2062 = !DILocation(line: 867, column: 39, scope: !613)
!2063 = !DILocalVariable(name: "err", scope: !613, file: !1, line: 868, type: !259)
!2064 = !DILocation(line: 868, column: 7, scope: !613)
!2065 = !DILocation(line: 870, column: 7, scope: !2066)
!2066 = distinct !DILexicalBlock(scope: !613, file: !1, line: 870, column: 7)
!2067 = !DILocation(line: 870, column: 16, scope: !2066)
!2068 = !DILocation(line: 870, column: 24, scope: !2066)
!2069 = !DILocation(line: 870, column: 27, scope: !2070)
!2070 = !DILexicalBlockFile(scope: !2066, file: !1, discriminator: 1)
!2071 = !DILocation(line: 870, column: 35, scope: !2070)
!2072 = !DILocation(line: 870, column: 7, scope: !2070)
!2073 = !DILocation(line: 871, column: 5, scope: !2066)
!2074 = !DILocation(line: 873, column: 22, scope: !2075)
!2075 = distinct !DILexicalBlock(scope: !613, file: !1, line: 873, column: 7)
!2076 = !DILocation(line: 873, column: 30, scope: !2075)
!2077 = !DILocation(line: 873, column: 7, scope: !2075)
!2078 = !DILocation(line: 873, column: 7, scope: !613)
!2079 = !DILocation(line: 874, column: 5, scope: !2075)
!2080 = !DILocation(line: 876, column: 37, scope: !613)
!2081 = !DILocation(line: 876, column: 9, scope: !613)
!2082 = !DILocation(line: 876, column: 7, scope: !613)
!2083 = !DILocation(line: 877, column: 7, scope: !2084)
!2084 = distinct !DILexicalBlock(scope: !613, file: !1, line: 877, column: 7)
!2085 = !DILocation(line: 877, column: 7, scope: !613)
!2086 = !DILocation(line: 878, column: 12, scope: !2084)
!2087 = !DILocation(line: 878, column: 5, scope: !2084)
!2088 = !DILocation(line: 880, column: 22, scope: !613)
!2089 = !DILocation(line: 880, column: 3, scope: !613)
!2090 = !DILocation(line: 880, column: 11, scope: !613)
!2091 = !DILocation(line: 880, column: 20, scope: !613)
!2092 = !DILocation(line: 881, column: 21, scope: !613)
!2093 = !DILocation(line: 881, column: 3, scope: !613)
!2094 = !DILocation(line: 881, column: 11, scope: !613)
!2095 = !DILocation(line: 881, column: 19, scope: !613)
!2096 = !DILocation(line: 883, column: 16, scope: !613)
!2097 = !DILocation(line: 883, column: 24, scope: !613)
!2098 = !DILocation(line: 883, column: 31, scope: !613)
!2099 = !DILocation(line: 883, column: 39, scope: !613)
!2100 = !DILocation(line: 883, column: 3, scope: !613)
!2101 = !DILocation(line: 884, column: 3, scope: !613)
!2102 = !DILocation(line: 884, column: 3, scope: !2103)
!2103 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 1)
!2104 = distinct !DILexicalBlock(scope: !613, file: !1, line: 884, column: 3)
!2105 = !DILocation(line: 884, column: 3, scope: !2106)
!2106 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 2)
!2107 = !DILocation(line: 884, column: 3, scope: !2108)
!2108 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 3)
!2109 = !DILocation(line: 884, column: 3, scope: !2110)
!2110 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 4)
!2111 = !DILocation(line: 884, column: 3, scope: !2112)
!2112 = !DILexicalBlockFile(scope: !2113, file: !1, discriminator: 5)
!2113 = distinct !DILexicalBlock(scope: !2104, file: !1, line: 884, column: 3)
!2114 = !DILocation(line: 884, column: 3, scope: !2115)
!2115 = !DILexicalBlockFile(scope: !2113, file: !1, discriminator: 6)
!2116 = !DILocation(line: 884, column: 3, scope: !2117)
!2117 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 7)
!2118 = !DILocation(line: 884, column: 3, scope: !2119)
!2119 = !DILexicalBlockFile(scope: !2120, file: !1, discriminator: 8)
!2120 = distinct !DILexicalBlock(scope: !2104, file: !1, line: 884, column: 3)
!2121 = !DILocation(line: 884, column: 3, scope: !2122)
!2122 = !DILexicalBlockFile(scope: !2123, file: !1, discriminator: 9)
!2123 = distinct !DILexicalBlock(scope: !2120, file: !1, line: 884, column: 3)
!2124 = !DILocation(line: 884, column: 3, scope: !2125)
!2125 = !DILexicalBlockFile(scope: !2123, file: !1, discriminator: 10)
!2126 = !DILocation(line: 884, column: 3, scope: !2127)
!2127 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 11)
!2128 = !DILocation(line: 886, column: 3, scope: !613)
!2129 = !DILocation(line: 887, column: 1, scope: !613)
!2130 = !DILocalVariable(name: "handle", arg: 1, scope: !616, file: !1, line: 890, type: !240)
!2131 = !DILocation(line: 890, column: 33, scope: !616)
!2132 = !DILocation(line: 891, column: 15, scope: !616)
!2133 = !DILocation(line: 891, column: 23, scope: !616)
!2134 = !DILocation(line: 891, column: 30, scope: !616)
!2135 = !DILocation(line: 891, column: 38, scope: !616)
!2136 = !DILocation(line: 891, column: 3, scope: !616)
!2137 = !DILocation(line: 893, column: 23, scope: !2138)
!2138 = distinct !DILexicalBlock(scope: !616, file: !1, line: 893, column: 7)
!2139 = !DILocation(line: 893, column: 31, scope: !2138)
!2140 = !DILocation(line: 893, column: 8, scope: !2138)
!2141 = !DILocation(line: 893, column: 7, scope: !616)
!2142 = !DILocation(line: 894, column: 5, scope: !2138)
!2143 = !DILocation(line: 894, column: 5, scope: !2144)
!2144 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 1)
!2145 = distinct !DILexicalBlock(scope: !2138, file: !1, line: 894, column: 5)
!2146 = !DILocation(line: 894, column: 5, scope: !2147)
!2147 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 2)
!2148 = !DILocation(line: 894, column: 5, scope: !2149)
!2149 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 3)
!2150 = !DILocation(line: 894, column: 5, scope: !2151)
!2151 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 4)
!2152 = !DILocation(line: 894, column: 5, scope: !2153)
!2153 = !DILexicalBlockFile(scope: !2154, file: !1, discriminator: 5)
!2154 = distinct !DILexicalBlock(scope: !2145, file: !1, line: 894, column: 5)
!2155 = !DILocation(line: 894, column: 5, scope: !2156)
!2156 = !DILexicalBlockFile(scope: !2154, file: !1, discriminator: 6)
!2157 = !DILocation(line: 894, column: 5, scope: !2158)
!2158 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 7)
!2159 = !DILocation(line: 894, column: 5, scope: !2160)
!2160 = !DILexicalBlockFile(scope: !2161, file: !1, discriminator: 8)
!2161 = distinct !DILexicalBlock(scope: !2145, file: !1, line: 894, column: 5)
!2162 = !DILocation(line: 894, column: 5, scope: !2163)
!2163 = !DILexicalBlockFile(scope: !2164, file: !1, discriminator: 9)
!2164 = distinct !DILexicalBlock(scope: !2161, file: !1, line: 894, column: 5)
!2165 = !DILocation(line: 894, column: 5, scope: !2166)
!2166 = !DILexicalBlockFile(scope: !2164, file: !1, discriminator: 10)
!2167 = !DILocation(line: 894, column: 5, scope: !2168)
!2168 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 11)
!2169 = !DILocation(line: 894, column: 5, scope: !2170)
!2170 = !DILexicalBlockFile(scope: !2145, file: !1, discriminator: 12)
!2171 = !DILocation(line: 896, column: 3, scope: !616)
!2172 = !DILocation(line: 896, column: 11, scope: !616)
!2173 = !DILocation(line: 896, column: 20, scope: !616)
!2174 = !DILocation(line: 897, column: 3, scope: !616)
!2175 = !DILocation(line: 897, column: 11, scope: !616)
!2176 = !DILocation(line: 897, column: 19, scope: !616)
!2177 = !DILocation(line: 899, column: 3, scope: !616)
!2178 = !DILocalVariable(name: "handle", arg: 1, scope: !630, file: !1, line: 151, type: !240)
!2179 = !DILocation(line: 151, column: 39, scope: !630)
!2180 = !DILocalVariable(name: "peer", scope: !630, file: !1, line: 152, type: !504)
!2181 = !DILocation(line: 152, column: 27, scope: !630)
!2182 = !DILocalVariable(name: "h", scope: !630, file: !1, line: 153, type: !1295)
!2183 = !DILocation(line: 153, column: 17, scope: !630)
!2184 = !DILocalVariable(name: "nread", scope: !630, file: !1, line: 154, type: !476)
!2185 = !DILocation(line: 154, column: 11, scope: !630)
!2186 = !DILocalVariable(name: "buf", scope: !630, file: !1, line: 155, type: !465)
!2187 = !DILocation(line: 155, column: 12, scope: !630)
!2188 = !DILocalVariable(name: "flags", scope: !630, file: !1, line: 156, type: !259)
!2189 = !DILocation(line: 156, column: 7, scope: !630)
!2190 = !DILocalVariable(name: "count", scope: !630, file: !1, line: 157, type: !259)
!2191 = !DILocation(line: 157, column: 7, scope: !630)
!2192 = !DILocation(line: 159, column: 3, scope: !630)
!2193 = !DILocation(line: 159, column: 3, scope: !2194)
!2194 = !DILexicalBlockFile(scope: !630, file: !1, discriminator: 1)
!2195 = !DILocation(line: 159, column: 3, scope: !2196)
!2196 = !DILexicalBlockFile(scope: !630, file: !1, discriminator: 2)
!2197 = !DILocation(line: 159, column: 3, scope: !2198)
!2198 = !DILexicalBlockFile(scope: !630, file: !1, discriminator: 3)
!2199 = !DILocation(line: 160, column: 3, scope: !630)
!2200 = !DILocation(line: 160, column: 3, scope: !2194)
!2201 = !DILocation(line: 160, column: 3, scope: !2196)
!2202 = !DILocation(line: 160, column: 3, scope: !2198)
!2203 = !DILocation(line: 165, column: 9, scope: !630)
!2204 = !DILocation(line: 167, column: 3, scope: !630)
!2205 = !DILocation(line: 168, column: 16, scope: !630)
!2206 = !DILocation(line: 168, column: 5, scope: !630)
!2207 = !DILocation(line: 168, column: 14, scope: !630)
!2208 = !DILocation(line: 170, column: 3, scope: !630)
!2209 = !DILocation(line: 171, column: 11, scope: !2210)
!2210 = distinct !DILexicalBlock(scope: !630, file: !1, line: 170, column: 6)
!2211 = !DILocation(line: 171, column: 11, scope: !2212)
!2212 = !DILexicalBlockFile(scope: !2210, file: !1, discriminator: 1)
!2213 = !DILocation(line: 172, column: 5, scope: !2210)
!2214 = !DILocation(line: 172, column: 13, scope: !2210)
!2215 = !DILocation(line: 172, column: 37, scope: !2210)
!2216 = !DILocation(line: 172, column: 22, scope: !2210)
!2217 = !DILocation(line: 173, column: 13, scope: !2218)
!2218 = distinct !DILexicalBlock(scope: !2210, file: !1, line: 173, column: 9)
!2219 = !DILocation(line: 173, column: 18, scope: !2218)
!2220 = !DILocation(line: 173, column: 26, scope: !2218)
!2221 = !DILocation(line: 173, column: 33, scope: !2222)
!2222 = !DILexicalBlockFile(scope: !2218, file: !1, discriminator: 1)
!2223 = !DILocation(line: 173, column: 37, scope: !2222)
!2224 = !DILocation(line: 173, column: 9, scope: !2222)
!2225 = !DILocation(line: 174, column: 7, scope: !2226)
!2226 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 173, column: 43)
!2227 = !DILocation(line: 174, column: 15, scope: !2226)
!2228 = !DILocation(line: 174, column: 23, scope: !2226)
!2229 = !DILocation(line: 175, column: 7, scope: !2226)
!2230 = !DILocation(line: 177, column: 5, scope: !2210)
!2231 = !DILocation(line: 177, column: 5, scope: !2212)
!2232 = !DILocation(line: 177, column: 5, scope: !2233)
!2233 = !DILexicalBlockFile(scope: !2210, file: !1, discriminator: 2)
!2234 = !DILocation(line: 177, column: 5, scope: !2235)
!2235 = !DILexicalBlockFile(scope: !2210, file: !1, discriminator: 3)
!2236 = !DILocation(line: 179, column: 7, scope: !2210)
!2237 = !DILocation(line: 179, column: 19, scope: !2210)
!2238 = !DILocation(line: 180, column: 17, scope: !2210)
!2239 = !DILocation(line: 180, column: 7, scope: !2210)
!2240 = !DILocation(line: 180, column: 15, scope: !2210)
!2241 = !DILocation(line: 181, column: 7, scope: !2210)
!2242 = !DILocation(line: 181, column: 18, scope: !2210)
!2243 = !DILocation(line: 183, column: 5, scope: !2210)
!2244 = !DILocation(line: 184, column: 23, scope: !2245)
!2245 = distinct !DILexicalBlock(scope: !2210, file: !1, line: 183, column: 8)
!2246 = !DILocation(line: 184, column: 31, scope: !2245)
!2247 = !DILocation(line: 184, column: 42, scope: !2245)
!2248 = !DILocation(line: 184, column: 15, scope: !2245)
!2249 = !DILocation(line: 184, column: 13, scope: !2245)
!2250 = !DILocation(line: 185, column: 5, scope: !2245)
!2251 = !DILocation(line: 186, column: 12, scope: !2210)
!2252 = !DILocation(line: 186, column: 18, scope: !2210)
!2253 = !DILocation(line: 186, column: 24, scope: !2210)
!2254 = !DILocation(line: 186, column: 27, scope: !2212)
!2255 = !DILocation(line: 186, column: 33, scope: !2212)
!2256 = !DILocation(line: 185, column: 5, scope: !2257)
!2257 = !DILexicalBlockFile(scope: !2245, file: !1, discriminator: 1)
!2258 = !DILocation(line: 188, column: 9, scope: !2259)
!2259 = distinct !DILexicalBlock(scope: !2210, file: !1, line: 188, column: 9)
!2260 = !DILocation(line: 188, column: 15, scope: !2259)
!2261 = !DILocation(line: 188, column: 9, scope: !2210)
!2262 = !DILocation(line: 189, column: 11, scope: !2263)
!2263 = distinct !DILexicalBlock(scope: !2264, file: !1, line: 189, column: 11)
!2264 = distinct !DILexicalBlock(scope: !2259, file: !1, line: 188, column: 22)
!2265 = !DILocation(line: 189, column: 17, scope: !2263)
!2266 = !DILocation(line: 189, column: 27, scope: !2263)
!2267 = !DILocation(line: 189, column: 30, scope: !2268)
!2268 = !DILexicalBlockFile(scope: !2263, file: !1, discriminator: 1)
!2269 = !DILocation(line: 189, column: 36, scope: !2268)
!2270 = !DILocation(line: 189, column: 11, scope: !2268)
!2271 = !DILocation(line: 190, column: 9, scope: !2263)
!2272 = !DILocation(line: 190, column: 17, scope: !2263)
!2273 = !DILocation(line: 190, column: 25, scope: !2263)
!2274 = !DILocation(line: 192, column: 9, scope: !2263)
!2275 = !DILocation(line: 192, column: 17, scope: !2263)
!2276 = !DILocation(line: 192, column: 25, scope: !2263)
!2277 = !DILocation(line: 192, column: 34, scope: !2263)
!2278 = !DILocation(line: 192, column: 33, scope: !2263)
!2279 = !DILocation(line: 192, column: 9, scope: !2268)
!2280 = !DILocation(line: 193, column: 5, scope: !2264)
!2281 = !DILocalVariable(name: "addr", scope: !2282, file: !1, line: 195, type: !482)
!2282 = distinct !DILexicalBlock(scope: !2259, file: !1, line: 194, column: 10)
!2283 = !DILocation(line: 195, column: 30, scope: !2282)
!2284 = !DILocation(line: 196, column: 13, scope: !2285)
!2285 = distinct !DILexicalBlock(scope: !2282, file: !1, line: 196, column: 11)
!2286 = !DILocation(line: 196, column: 25, scope: !2285)
!2287 = !DILocation(line: 196, column: 11, scope: !2282)
!2288 = !DILocation(line: 197, column: 14, scope: !2285)
!2289 = !DILocation(line: 197, column: 9, scope: !2285)
!2290 = !DILocation(line: 199, column: 16, scope: !2285)
!2291 = !DILocation(line: 199, column: 14, scope: !2285)
!2292 = !DILocation(line: 201, column: 13, scope: !2282)
!2293 = !DILocation(line: 202, column: 13, scope: !2294)
!2294 = distinct !DILexicalBlock(scope: !2282, file: !1, line: 202, column: 11)
!2295 = !DILocation(line: 202, column: 23, scope: !2294)
!2296 = !DILocation(line: 202, column: 11, scope: !2282)
!2297 = !DILocation(line: 203, column: 15, scope: !2294)
!2298 = !DILocation(line: 203, column: 9, scope: !2294)
!2299 = !DILocation(line: 205, column: 7, scope: !2282)
!2300 = !DILocation(line: 205, column: 15, scope: !2282)
!2301 = !DILocation(line: 205, column: 23, scope: !2282)
!2302 = !DILocation(line: 205, column: 31, scope: !2282)
!2303 = !DILocation(line: 205, column: 44, scope: !2282)
!2304 = !DILocation(line: 205, column: 50, scope: !2282)
!2305 = !DILocation(line: 207, column: 3, scope: !2210)
!2306 = !DILocation(line: 209, column: 10, scope: !630)
!2307 = !DILocation(line: 209, column: 16, scope: !630)
!2308 = !DILocation(line: 210, column: 7, scope: !630)
!2309 = !DILocation(line: 210, column: 15, scope: !2194)
!2310 = !DILocation(line: 210, column: 18, scope: !2194)
!2311 = !DILocation(line: 211, column: 7, scope: !630)
!2312 = !DILocation(line: 211, column: 10, scope: !2194)
!2313 = !DILocation(line: 211, column: 18, scope: !2194)
!2314 = !DILocation(line: 211, column: 29, scope: !2194)
!2315 = !DILocation(line: 211, column: 32, scope: !2194)
!2316 = !DILocation(line: 212, column: 7, scope: !630)
!2317 = !DILocation(line: 212, column: 10, scope: !2194)
!2318 = !DILocation(line: 212, column: 18, scope: !2194)
!2319 = !DILocation(line: 212, column: 26, scope: !2194)
!2320 = !DILocation(line: 207, column: 3, scope: !2212)
!2321 = !DILocation(line: 213, column: 1, scope: !630)
!2322 = !DILocalVariable(name: "handle", arg: 1, scope: !644, file: !1, line: 661, type: !240)
!2323 = !DILocation(line: 661, column: 37, scope: !644)
!2324 = !DILocalVariable(name: "option4", arg: 2, scope: !644, file: !1, line: 662, type: !259)
!2325 = !DILocation(line: 662, column: 30, scope: !644)
!2326 = !DILocalVariable(name: "option6", arg: 3, scope: !644, file: !1, line: 663, type: !259)
!2327 = !DILocation(line: 663, column: 30, scope: !644)
!2328 = !DILocalVariable(name: "val", arg: 4, scope: !644, file: !1, line: 664, type: !647)
!2329 = !DILocation(line: 664, column: 38, scope: !644)
!2330 = !DILocalVariable(name: "size", arg: 5, scope: !644, file: !1, line: 665, type: !456)
!2331 = !DILocation(line: 665, column: 33, scope: !644)
!2332 = !DILocalVariable(name: "r", scope: !644, file: !1, line: 666, type: !259)
!2333 = !DILocation(line: 666, column: 7, scope: !644)
!2334 = !DILocation(line: 668, column: 7, scope: !2335)
!2335 = distinct !DILexicalBlock(scope: !644, file: !1, line: 668, column: 7)
!2336 = !DILocation(line: 668, column: 15, scope: !2335)
!2337 = !DILocation(line: 668, column: 21, scope: !2335)
!2338 = !DILocation(line: 668, column: 7, scope: !644)
!2339 = !DILocation(line: 669, column: 20, scope: !2335)
!2340 = !DILocation(line: 669, column: 28, scope: !2335)
!2341 = !DILocation(line: 669, column: 39, scope: !2335)
!2342 = !DILocation(line: 671, column: 20, scope: !2335)
!2343 = !DILocation(line: 672, column: 20, scope: !2335)
!2344 = !DILocation(line: 673, column: 20, scope: !2335)
!2345 = !DILocation(line: 669, column: 9, scope: !2335)
!2346 = !DILocation(line: 669, column: 7, scope: !2335)
!2347 = !DILocation(line: 669, column: 5, scope: !2335)
!2348 = !DILocation(line: 675, column: 20, scope: !2335)
!2349 = !DILocation(line: 675, column: 28, scope: !2335)
!2350 = !DILocation(line: 675, column: 39, scope: !2335)
!2351 = !DILocation(line: 677, column: 20, scope: !2335)
!2352 = !DILocation(line: 678, column: 20, scope: !2335)
!2353 = !DILocation(line: 679, column: 20, scope: !2335)
!2354 = !DILocation(line: 675, column: 9, scope: !2335)
!2355 = !DILocation(line: 675, column: 7, scope: !2335)
!2356 = !DILocation(line: 680, column: 7, scope: !2357)
!2357 = distinct !DILexicalBlock(scope: !644, file: !1, line: 680, column: 7)
!2358 = !DILocation(line: 680, column: 7, scope: !644)
!2359 = !DILocation(line: 681, column: 13, scope: !2357)
!2360 = !DILocation(line: 681, column: 12, scope: !2357)
!2361 = !DILocation(line: 681, column: 5, scope: !2357)
!2362 = !DILocation(line: 683, column: 3, scope: !644)
!2363 = !DILocation(line: 684, column: 1, scope: !644)
