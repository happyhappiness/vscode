; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/stream.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timespec = type { i64, i64 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.1, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.0 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32 }
%union.anon = type { [4 x i8*] }
%struct.anon.1 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.2, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.3, i32, i32 }
%union.anon.2 = type { [4 x i8*] }
%struct.anon.3 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%struct.uv_write_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_write_s*, i32)*, %struct.uv_stream_s*, %struct.uv_stream_s*, [2 x i8*], i32, %struct.uv_buf_t*, i32, i32, [4 x %struct.uv_buf_t] }
%struct.uv__stream_queued_fds_s = type { i32, i32, [1 x i32] }
%struct.uv_udp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i64, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_udp_s*, i64, %struct.uv_buf_t*, %struct.sockaddr*, i32)*, %struct.uv__io_s, [2 x i8*], [2 x i8*] }
%union.anon.5 = type { [4 x i8*] }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv_tcp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.6, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.6 = type { [4 x i8*] }
%struct.uv_pipe_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.7, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8*, i32, i8* }
%union.anon.7 = type { [4 x i8*] }
%struct.sockaddr_storage = type { i16, i64, [112 x i8] }
%union.__SOCKADDR_ARG = type { %struct.sockaddr* }
%struct.iovec = type { i8*, i64 }
%struct.msghdr = type { i8*, i32, %struct.iovec*, i64, i8*, i64, i32 }
%struct.cmsghdr = type { i64, i32, i32, [0 x i8] }
%union.anon.9 = type { %struct.cmsghdr, [48 x i8] }

@.str = private unnamed_addr constant [10 x i8] c"/dev/null\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.2 = private unnamed_addr constant [8 x i8] c"fd >= 0\00", align 1
@.str.3 = private unnamed_addr constant [70 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/stream.c\00", align 1
@__PRETTY_FUNCTION__.uv__stream_open = private unnamed_addr constant [45 x i8] c"int uv__stream_open(uv_stream_t *, int, int)\00", align 1
@.str.4 = private unnamed_addr constant [51 x i8] c"!uv__io_active(&stream->io_watcher, 0x001 | 0x004)\00", align 1
@__PRETTY_FUNCTION__.uv__stream_destroy = private unnamed_addr constant [39 x i8] c"void uv__stream_destroy(uv_stream_t *)\00", align 1
@.str.5 = private unnamed_addr constant [26 x i8] c"stream->flags & UV_CLOSED\00", align 1
@.str.6 = private unnamed_addr constant [129 x i8] c"(((const QUEUE *) (&(stream->loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(stream->loop)->active_reqs))[0]))) == 0)\00", align 1
@.str.7 = private unnamed_addr constant [30 x i8] c"stream->write_queue_size == 0\00", align 1
@.str.8 = private unnamed_addr constant [16 x i8] c"events == 0x001\00", align 1
@__PRETTY_FUNCTION__.uv__server_io = private unnamed_addr constant [58 x i8] c"void uv__server_io(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@.str.9 = private unnamed_addr constant [26 x i8] c"stream->accepted_fd == -1\00", align 1
@.str.10 = private unnamed_addr constant [30 x i8] c"!(stream->flags & UV_CLOSING)\00", align 1
@uv__server_io.timeout = private unnamed_addr constant %struct.timespec { i64 0, i64 1 }, align 8
@.str.11 = private unnamed_addr constant [29 x i8] c"server->loop == client->loop\00", align 1
@__PRETTY_FUNCTION__.uv_accept = private unnamed_addr constant [44 x i8] c"int uv_accept(uv_stream_t *, uv_stream_t *)\00", align 1
@.str.12 = private unnamed_addr constant [23 x i8] c"queued_fds->offset > 0\00", align 1
@.str.13 = private unnamed_addr constant [44 x i8] c"((stream)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@__PRETTY_FUNCTION__.uv_listen = private unnamed_addr constant [52 x i8] c"int uv_listen(uv_stream_t *, int, uv_connection_cb)\00", align 1
@.str.14 = private unnamed_addr constant [55 x i8] c"uv_shutdown (unix) only supports uv_handle_t right now\00", align 1
@.str.15 = private unnamed_addr constant [118 x i8] c"(stream->type == UV_TCP || stream->type == UV_NAMED_PIPE) && \22uv_shutdown (unix) only supports uv_handle_t right now\22\00", align 1
@__PRETTY_FUNCTION__.uv_shutdown = private unnamed_addr constant [64 x i8] c"int uv_shutdown(uv_shutdown_t *, uv_stream_t *, uv_shutdown_cb)\00", align 1
@.str.16 = private unnamed_addr constant [31 x i8] c"((stream)->io_watcher.fd) >= 0\00", align 1
@.str.17 = private unnamed_addr constant [10 x i8] c"nbufs > 0\00", align 1
@__PRETTY_FUNCTION__.uv_write2 = private unnamed_addr constant [103 x i8] c"int uv_write2(uv_write_t *, uv_stream_t *, const uv_buf_t *, unsigned int, uv_stream_t *, uv_write_cb)\00", align 1
@.str.18 = private unnamed_addr constant [60 x i8] c"uv_write (unix) does not yet support other types of streams\00", align 1
@.str.19 = private unnamed_addr constant [149 x i8] c"(stream->type == UV_TCP || stream->type == UV_NAMED_PIPE || stream->type == UV_TTY) && \22uv_write (unix) does not yet support other types of streams\22\00", align 1
@.str.20 = private unnamed_addr constant [38 x i8] c"!(stream->flags & UV_STREAM_BLOCKING)\00", align 1
@__PRETTY_FUNCTION__.uv_try_write = private unnamed_addr constant [64 x i8] c"int uv_try_write(uv_stream_t *, const uv_buf_t *, unsigned int)\00", align 1
@.str.21 = private unnamed_addr constant [82 x i8] c"stream->type == UV_TCP || stream->type == UV_NAMED_PIPE || stream->type == UV_TTY\00", align 1
@__PRETTY_FUNCTION__.uv_read_start = private unnamed_addr constant [58 x i8] c"int uv_read_start(uv_stream_t *, uv_alloc_cb, uv_read_cb)\00", align 1
@.str.22 = private unnamed_addr constant [9 x i8] c"alloc_cb\00", align 1
@__PRETTY_FUNCTION__.uv_read_stop = private unnamed_addr constant [32 x i8] c"int uv_read_stop(uv_stream_t *)\00", align 1
@.str.23 = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@__PRETTY_FUNCTION__.uv__stream_close = private unnamed_addr constant [37 x i8] c"void uv__stream_close(uv_stream_t *)\00", align 1
@.str.24 = private unnamed_addr constant [51 x i8] c"!uv__io_active(&handle->io_watcher, 0x001 | 0x004)\00", align 1
@__PRETTY_FUNCTION__.uv__write_callbacks = private unnamed_addr constant [40 x i8] c"void uv__write_callbacks(uv_stream_t *)\00", align 1
@.str.25 = private unnamed_addr constant [126 x i8] c"((const QUEUE *) (&stream->write_completed_queue) == (const QUEUE *) (*(QUEUE **) &((*(&stream->write_completed_queue))[0])))\00", align 1
@__PRETTY_FUNCTION__.uv__stream_io = private unnamed_addr constant [58 x i8] c"void uv__stream_io(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@.str.26 = private unnamed_addr constant [56 x i8] c"stream->type == UV_TCP || stream->type == UV_NAMED_PIPE\00", align 1
@__PRETTY_FUNCTION__.uv__stream_connect = private unnamed_addr constant [39 x i8] c"void uv__stream_connect(uv_stream_t *)\00", align 1
@.str.27 = private unnamed_addr constant [4 x i8] c"req\00", align 1
@.str.28 = private unnamed_addr constant [31 x i8] c"stream->alloc_cb != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv__read = private unnamed_addr constant [29 x i8] c"void uv__read(uv_stream_t *)\00", align 1
@.str.29 = private unnamed_addr constant [23 x i8] c"buf.base != ((void*)0)\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.30 = private unnamed_addr constant [44 x i8] c"ignoring non-SCM_RIGHTS ancillary data: %d\0A\00", align 1
@.str.31 = private unnamed_addr constant [127 x i8] c"start + ((((sizeof (struct cmsghdr)) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1)) + (count * sizeof(*pi))) == end\00", align 1
@__PRETTY_FUNCTION__.uv__stream_recv_cmsg = private unnamed_addr constant [57 x i8] c"int uv__stream_recv_cmsg(uv_stream_t *, struct msghdr *)\00", align 1
@__PRETTY_FUNCTION__.uv__stream_eof = private unnamed_addr constant [53 x i8] c"void uv__stream_eof(uv_stream_t *, const uv_buf_t *)\00", align 1
@.str.32 = private unnamed_addr constant [106 x i8] c"((const QUEUE *) (&stream->write_queue) == (const QUEUE *) (*(QUEUE **) &((*(&stream->write_queue))[0])))\00", align 1
@__PRETTY_FUNCTION__.uv__drain = private unnamed_addr constant [30 x i8] c"void uv__drain(uv_stream_t *)\00", align 1
@.str.33 = private unnamed_addr constant [21 x i8] c"stream->shutdown_req\00", align 1
@__PRETTY_FUNCTION__.uv__write = private unnamed_addr constant [30 x i8] c"void uv__write(uv_stream_t *)\00", align 1
@.str.34 = private unnamed_addr constant [22 x i8] c"req->handle == stream\00", align 1
@.str.35 = private unnamed_addr constant [16 x i8] c"fd_to_send >= 0\00", align 1
@.str.36 = private unnamed_addr constant [30 x i8] c"req->write_index < req->nbufs\00", align 1
@.str.37 = private unnamed_addr constant [17 x i8] c"(size_t)n >= len\00", align 1
@.str.38 = private unnamed_addr constant [32 x i8] c"stream->write_queue_size >= len\00", align 1
@.str.39 = private unnamed_addr constant [7 x i8] c"n == 0\00", align 1
@.str.40 = private unnamed_addr constant [18 x i8] c"n == 0 || n == -1\00", align 1
@.str.41 = private unnamed_addr constant [24 x i8] c"req->bufs != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv__write_req_size = private unnamed_addr constant [40 x i8] c"size_t uv__write_req_size(uv_write_t *)\00", align 1
@.str.42 = private unnamed_addr constant [38 x i8] c"req->handle->write_queue_size >= size\00", align 1

; Function Attrs: nounwind uwtable
define void @uv__stream_init(%struct.uv_loop_s* %loop, %struct.uv_stream_s* %stream, i32 %type) #0 !dbg !605 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %type.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !698, metadata !699), !dbg !700
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !701, metadata !699), !dbg !702
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !703, metadata !699), !dbg !704
  call void @llvm.dbg.declare(metadata i32* %err, metadata !705, metadata !699), !dbg !706
  br label %do.body, !dbg !707

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !708
  %1 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !708
  %2 = bitcast %struct.uv_stream_s* %1 to %struct.uv_handle_s*, !dbg !708
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !708
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !708
  %3 = load i32, i32* %type.addr, align 4, !dbg !708
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !708
  %5 = bitcast %struct.uv_stream_s* %4 to %struct.uv_handle_s*, !dbg !708
  %type2 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %5, i32 0, i32 2, !dbg !708
  store i32 %3, i32* %type2, align 8, !dbg !708
  %6 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !708
  %7 = bitcast %struct.uv_stream_s* %6 to %struct.uv_handle_s*, !dbg !708
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %7, i32 0, i32 7, !dbg !708
  store i32 8192, i32* %flags, align 8, !dbg !708
  br label %do.body3, !dbg !708

do.body3:                                         ; preds = %do.body
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !711
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 2, !dbg !711
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !711
  %10 = bitcast %struct.uv_stream_s* %9 to %struct.uv_handle_s*, !dbg !711
  %handle_queue4 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %10, i32 0, i32 4, !dbg !711
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 0, !dbg !711
  %11 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !711
  store [2 x i8*]* %handle_queue, [2 x i8*]** %11, align 8, !dbg !711
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !711
  %handle_queue5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 2, !dbg !711
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue5, i64 0, i64 1, !dbg !711
  %13 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !711
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !711
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !711
  %16 = bitcast %struct.uv_stream_s* %15 to %struct.uv_handle_s*, !dbg !711
  %handle_queue7 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %16, i32 0, i32 4, !dbg !711
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue7, i64 0, i64 1, !dbg !711
  %17 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !711
  store [2 x i8*]* %14, [2 x i8*]** %17, align 8, !dbg !711
  %18 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !711
  %19 = bitcast %struct.uv_stream_s* %18 to %struct.uv_handle_s*, !dbg !711
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %19, i32 0, i32 4, !dbg !711
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !711
  %21 = bitcast %struct.uv_stream_s* %20 to %struct.uv_handle_s*, !dbg !711
  %handle_queue10 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %21, i32 0, i32 4, !dbg !711
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue10, i64 0, i64 1, !dbg !711
  %22 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !711
  %23 = load [2 x i8*]*, [2 x i8*]** %22, align 8, !dbg !711
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %23, i64 0, i64 0, !dbg !711
  %24 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !711
  store [2 x i8*]* %handle_queue9, [2 x i8*]** %24, align 8, !dbg !711
  %25 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !711
  %26 = bitcast %struct.uv_stream_s* %25 to %struct.uv_handle_s*, !dbg !711
  %handle_queue13 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %26, i32 0, i32 4, !dbg !711
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !711
  %handle_queue14 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 2, !dbg !711
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue14, i64 0, i64 1, !dbg !711
  %28 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !711
  store [2 x i8*]* %handle_queue13, [2 x i8*]** %28, align 8, !dbg !711
  br label %do.end, !dbg !711

do.end:                                           ; preds = %do.body3
  %29 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !714
  %30 = bitcast %struct.uv_stream_s* %29 to %struct.uv_handle_s*, !dbg !714
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %30, i32 0, i32 6, !dbg !714
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !714
  br label %do.end16, !dbg !714

do.end16:                                         ; preds = %do.end
  %31 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !716
  %read_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %31, i32 0, i32 10, !dbg !717
  store void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb, align 8, !dbg !718
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !719
  %alloc_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %32, i32 0, i32 9, !dbg !720
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !721
  %33 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !722
  %close_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %33, i32 0, i32 3, !dbg !723
  store void (%struct.uv_handle_s*)* null, void (%struct.uv_handle_s*)** %close_cb, align 8, !dbg !724
  %34 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !725
  %connection_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %34, i32 0, i32 16, !dbg !726
  store void (%struct.uv_stream_s*, i32)* null, void (%struct.uv_stream_s*, i32)** %connection_cb, align 8, !dbg !727
  %35 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !728
  %connect_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %35, i32 0, i32 11, !dbg !729
  store %struct.uv_connect_s* null, %struct.uv_connect_s** %connect_req, align 8, !dbg !730
  %36 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !731
  %shutdown_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %36, i32 0, i32 12, !dbg !732
  store %struct.uv_shutdown_s* null, %struct.uv_shutdown_s** %shutdown_req, align 8, !dbg !733
  %37 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !734
  %accepted_fd = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %37, i32 0, i32 18, !dbg !735
  store i32 -1, i32* %accepted_fd, align 4, !dbg !736
  %38 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !737
  %queued_fds = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %38, i32 0, i32 19, !dbg !738
  store i8* null, i8** %queued_fds, align 8, !dbg !739
  %39 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !740
  %delayed_error = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %39, i32 0, i32 17, !dbg !741
  store i32 0, i32* %delayed_error, align 8, !dbg !742
  br label %do.body17, !dbg !743

do.body17:                                        ; preds = %do.end16
  %40 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !744
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %40, i32 0, i32 14, !dbg !744
  %41 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !744
  %write_queue18 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %41, i32 0, i32 14, !dbg !744
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue18, i64 0, i64 0, !dbg !744
  %42 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !744
  store [2 x i8*]* %write_queue, [2 x i8*]** %42, align 8, !dbg !744
  %43 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !744
  %write_queue20 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %43, i32 0, i32 14, !dbg !744
  %44 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !744
  %write_queue21 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %44, i32 0, i32 14, !dbg !744
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue21, i64 0, i64 1, !dbg !744
  %45 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !744
  store [2 x i8*]* %write_queue20, [2 x i8*]** %45, align 8, !dbg !744
  br label %do.end23, !dbg !744

do.end23:                                         ; preds = %do.body17
  br label %do.body24, !dbg !747

do.body24:                                        ; preds = %do.end23
  %46 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !748
  %write_completed_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %46, i32 0, i32 15, !dbg !748
  %47 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !748
  %write_completed_queue25 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %47, i32 0, i32 15, !dbg !748
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue25, i64 0, i64 0, !dbg !748
  %48 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !748
  store [2 x i8*]* %write_completed_queue, [2 x i8*]** %48, align 8, !dbg !748
  %49 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !748
  %write_completed_queue27 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %49, i32 0, i32 15, !dbg !748
  %50 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !748
  %write_completed_queue28 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %50, i32 0, i32 15, !dbg !748
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue28, i64 0, i64 1, !dbg !748
  %51 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !748
  store [2 x i8*]* %write_completed_queue27, [2 x i8*]** %51, align 8, !dbg !748
  br label %do.end30, !dbg !748

do.end30:                                         ; preds = %do.body24
  %52 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !751
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %52, i32 0, i32 8, !dbg !752
  store i64 0, i64* %write_queue_size, align 8, !dbg !753
  %53 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !754
  %emfile_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %53, i32 0, i32 31, !dbg !756
  %54 = load i32, i32* %emfile_fd, align 8, !dbg !756
  %cmp = icmp eq i32 %54, -1, !dbg !757
  br i1 %cmp, label %if.then, label %if.end38, !dbg !758

if.then:                                          ; preds = %do.end30
  %call = call i32 @uv__open_cloexec(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i32 0), !dbg !759
  store i32 %call, i32* %err, align 4, !dbg !761
  %55 = load i32, i32* %err, align 4, !dbg !762
  %cmp31 = icmp slt i32 %55, 0, !dbg !764
  br i1 %cmp31, label %if.then32, label %if.end, !dbg !765

if.then32:                                        ; preds = %if.then
  %call33 = call i32 @uv__open_cloexec(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0), i32 0), !dbg !766
  store i32 %call33, i32* %err, align 4, !dbg !767
  br label %if.end, !dbg !768

if.end:                                           ; preds = %if.then32, %if.then
  %56 = load i32, i32* %err, align 4, !dbg !769
  %cmp34 = icmp sge i32 %56, 0, !dbg !771
  br i1 %cmp34, label %if.then35, label %if.end37, !dbg !772

if.then35:                                        ; preds = %if.end
  %57 = load i32, i32* %err, align 4, !dbg !773
  %58 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !774
  %emfile_fd36 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %58, i32 0, i32 31, !dbg !775
  store i32 %57, i32* %emfile_fd36, align 8, !dbg !776
  br label %if.end37, !dbg !774

if.end37:                                         ; preds = %if.then35, %if.end
  br label %if.end38, !dbg !777

if.end38:                                         ; preds = %if.end37, %do.end30
  %59 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !778
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %59, i32 0, i32 13, !dbg !779
  call void @uv__io_init(%struct.uv__io_s* %io_watcher, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__stream_io, i32 -1), !dbg !780
  ret void, !dbg !781
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @uv__open_cloexec(i8*, i32) #2

declare void @uv__io_init(%struct.uv__io_s*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__stream_io(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !662 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  %stream = alloca %struct.uv_stream_s*, align 8
  %buf = alloca %struct.uv_buf_t, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !782, metadata !699), !dbg !783
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !784, metadata !699), !dbg !785
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !786, metadata !699), !dbg !787
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream, metadata !788, metadata !699), !dbg !789
  %0 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !790
  %1 = bitcast %struct.uv__io_s* %0 to i8*, !dbg !790
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -136, !dbg !790
  %2 = bitcast i8* %add.ptr to %struct.uv_stream_s*, !dbg !790
  store %struct.uv_stream_s* %2, %struct.uv_stream_s** %stream, align 8, !dbg !791
  %3 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !792
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %3, i32 0, i32 2, !dbg !792
  %4 = load i32, i32* %type, align 8, !dbg !792
  %cmp = icmp eq i32 %4, 12, !dbg !792
  br i1 %cmp, label %cond.true, label %lor.lhs.false, !dbg !792

lor.lhs.false:                                    ; preds = %entry
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !793
  %type1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 2, !dbg !793
  %6 = load i32, i32* %type1, align 8, !dbg !793
  %cmp2 = icmp eq i32 %6, 7, !dbg !793
  br i1 %cmp2, label %cond.true, label %lor.lhs.false3, !dbg !793

lor.lhs.false3:                                   ; preds = %lor.lhs.false
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !795
  %type4 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 2, !dbg !795
  %8 = load i32, i32* %type4, align 8, !dbg !795
  %cmp5 = icmp eq i32 %8, 14, !dbg !795
  br i1 %cmp5, label %cond.true, label %cond.false, !dbg !795

cond.true:                                        ; preds = %lor.lhs.false3, %lor.lhs.false, %entry
  br label %cond.end, !dbg !797

cond.false:                                       ; preds = %lor.lhs.false3
  call void @__assert_fail(i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1280, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__stream_io, i32 0, i32 0)) #7, !dbg !799
  unreachable, !dbg !799
                                                  ; No predecessors!
  br label %cond.end, !dbg !801

cond.end:                                         ; preds = %9, %cond.true
  %10 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !803
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %10, i32 0, i32 7, !dbg !803
  %11 = load i32, i32* %flags, align 8, !dbg !803
  %and = and i32 %11, 1, !dbg !803
  %tobool = icmp ne i32 %and, 0, !dbg !803
  br i1 %tobool, label %cond.false7, label %cond.true6, !dbg !803

cond.true6:                                       ; preds = %cond.end
  br label %cond.end8, !dbg !804

cond.false7:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1281, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__stream_io, i32 0, i32 0)) #7, !dbg !805
  unreachable, !dbg !805
                                                  ; No predecessors!
  br label %cond.end8, !dbg !806

cond.end8:                                        ; preds = %12, %cond.true6
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !807
  %connect_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 11, !dbg !809
  %14 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req, align 8, !dbg !809
  %tobool9 = icmp ne %struct.uv_connect_s* %14, null, !dbg !807
  br i1 %tobool9, label %if.then, label %if.end, !dbg !810

if.then:                                          ; preds = %cond.end8
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !811
  call void @uv__stream_connect(%struct.uv_stream_s* %15), !dbg !813
  br label %if.end50, !dbg !814

if.end:                                           ; preds = %cond.end8
  %16 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !815
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %16, i32 0, i32 13, !dbg !815
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !815
  %17 = load i32, i32* %fd, align 8, !dbg !815
  %cmp10 = icmp sge i32 %17, 0, !dbg !815
  br i1 %cmp10, label %cond.true11, label %cond.false12, !dbg !815

cond.true11:                                      ; preds = %if.end
  br label %cond.end13, !dbg !816

cond.false12:                                     ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1288, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__stream_io, i32 0, i32 0)) #7, !dbg !817
  unreachable, !dbg !817
                                                  ; No predecessors!
  br label %cond.end13, !dbg !818

cond.end13:                                       ; preds = %18, %cond.true11
  %19 = load i32, i32* %events.addr, align 4, !dbg !819
  %and14 = and i32 %19, 25, !dbg !821
  %tobool15 = icmp ne i32 %and14, 0, !dbg !821
  br i1 %tobool15, label %if.then16, label %if.end17, !dbg !822

if.then16:                                        ; preds = %cond.end13
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !823
  call void @uv__read(%struct.uv_stream_s* %20), !dbg !824
  br label %if.end17, !dbg !824

if.end17:                                         ; preds = %if.then16, %cond.end13
  %21 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !825
  %io_watcher18 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %21, i32 0, i32 13, !dbg !825
  %fd19 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher18, i32 0, i32 5, !dbg !825
  %22 = load i32, i32* %fd19, align 8, !dbg !825
  %cmp20 = icmp eq i32 %22, -1, !dbg !827
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !828

if.then21:                                        ; preds = %if.end17
  br label %if.end50, !dbg !829

if.end22:                                         ; preds = %if.end17
  %23 = load i32, i32* %events.addr, align 4, !dbg !830
  %and23 = and i32 %23, 16, !dbg !832
  %tobool24 = icmp ne i32 %and23, 0, !dbg !832
  br i1 %tobool24, label %land.lhs.true, label %if.end37, !dbg !833

land.lhs.true:                                    ; preds = %if.end22
  %24 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !834
  %flags25 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %24, i32 0, i32 7, !dbg !835
  %25 = load i32, i32* %flags25, align 8, !dbg !835
  %and26 = and i32 %25, 4, !dbg !836
  %tobool27 = icmp ne i32 %and26, 0, !dbg !836
  br i1 %tobool27, label %land.lhs.true28, label %if.end37, !dbg !837

land.lhs.true28:                                  ; preds = %land.lhs.true
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !838
  %flags29 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %26, i32 0, i32 7, !dbg !839
  %27 = load i32, i32* %flags29, align 8, !dbg !839
  %and30 = and i32 %27, 256, !dbg !840
  %tobool31 = icmp ne i32 %and30, 0, !dbg !840
  br i1 %tobool31, label %land.lhs.true32, label %if.end37, !dbg !841

land.lhs.true32:                                  ; preds = %land.lhs.true28
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !842
  %flags33 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 7, !dbg !843
  %29 = load i32, i32* %flags33, align 8, !dbg !843
  %and34 = and i32 %29, 512, !dbg !844
  %tobool35 = icmp ne i32 %and34, 0, !dbg !844
  br i1 %tobool35, label %if.end37, label %if.then36, !dbg !845

if.then36:                                        ; preds = %land.lhs.true32
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t* %buf, metadata !846, metadata !699), !dbg !848
  %30 = bitcast %struct.uv_buf_t* %buf to i8*, !dbg !848
  call void @llvm.memset.p0i8.i64(i8* %30, i8 0, i64 16, i32 8, i1 false), !dbg !848
  %31 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !849
  call void @uv__stream_eof(%struct.uv_stream_s* %31, %struct.uv_buf_t* %buf), !dbg !850
  br label %if.end37, !dbg !851

if.end37:                                         ; preds = %if.then36, %land.lhs.true32, %land.lhs.true28, %land.lhs.true, %if.end22
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !852
  %io_watcher38 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %32, i32 0, i32 13, !dbg !852
  %fd39 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher38, i32 0, i32 5, !dbg !852
  %33 = load i32, i32* %fd39, align 8, !dbg !852
  %cmp40 = icmp eq i32 %33, -1, !dbg !854
  br i1 %cmp40, label %if.then41, label %if.end42, !dbg !855

if.then41:                                        ; preds = %if.end37
  br label %if.end50, !dbg !856

if.end42:                                         ; preds = %if.end37
  %34 = load i32, i32* %events.addr, align 4, !dbg !857
  %and43 = and i32 %34, 28, !dbg !859
  %tobool44 = icmp ne i32 %and43, 0, !dbg !859
  br i1 %tobool44, label %if.then45, label %if.end50, !dbg !860

if.then45:                                        ; preds = %if.end42
  %35 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !861
  call void @uv__write(%struct.uv_stream_s* %35), !dbg !863
  %36 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !864
  call void @uv__write_callbacks(%struct.uv_stream_s* %36), !dbg !865
  %37 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !866
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %37, i32 0, i32 14, !dbg !866
  %38 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !866
  %write_queue46 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %38, i32 0, i32 14, !dbg !866
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue46, i64 0, i64 0, !dbg !866
  %39 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !866
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !866
  %cmp47 = icmp eq [2 x i8*]* %write_queue, %40, !dbg !866
  br i1 %cmp47, label %if.then48, label %if.end49, !dbg !868

if.then48:                                        ; preds = %if.then45
  %41 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !869
  call void @uv__drain(%struct.uv_stream_s* %41), !dbg !870
  br label %if.end49, !dbg !870

if.end49:                                         ; preds = %if.then48, %if.then45
  br label %if.end50, !dbg !871

if.end50:                                         ; preds = %if.then, %if.then21, %if.then41, %if.end49, %if.end42
  ret void, !dbg !872
}

; Function Attrs: nounwind uwtable
define i32 @uv__stream_open(%struct.uv_stream_s* %stream, i32 %fd, i32 %flags) #0 !dbg !609 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %fd.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !873, metadata !699), !dbg !874
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !875, metadata !699), !dbg !876
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !877, metadata !699), !dbg !878
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !879
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 13, !dbg !881
  %fd1 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !882
  %1 = load i32, i32* %fd1, align 8, !dbg !882
  %cmp = icmp eq i32 %1, -1, !dbg !883
  br i1 %cmp, label %if.end, label %lor.lhs.false, !dbg !884

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !885
  %io_watcher2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 13, !dbg !887
  %fd3 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher2, i32 0, i32 5, !dbg !888
  %3 = load i32, i32* %fd3, align 8, !dbg !888
  %4 = load i32, i32* %fd.addr, align 4, !dbg !889
  %cmp4 = icmp eq i32 %3, %4, !dbg !890
  br i1 %cmp4, label %if.end, label %if.then, !dbg !891

if.then:                                          ; preds = %lor.lhs.false
  store i32 -16, i32* %retval, align 4, !dbg !892
  br label %return, !dbg !892

if.end:                                           ; preds = %lor.lhs.false, %entry
  %5 = load i32, i32* %fd.addr, align 4, !dbg !893
  %cmp5 = icmp sge i32 %5, 0, !dbg !893
  br i1 %cmp5, label %cond.true, label %cond.false, !dbg !893

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !894

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 400, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @__PRETTY_FUNCTION__.uv__stream_open, i32 0, i32 0)) #7, !dbg !896
  unreachable, !dbg !896
                                                  ; No predecessors!
  br label %cond.end, !dbg !898

cond.end:                                         ; preds = %6, %cond.true
  %7 = load i32, i32* %flags.addr, align 4, !dbg !900
  %8 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !901
  %flags6 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %8, i32 0, i32 7, !dbg !902
  %9 = load i32, i32* %flags6, align 8, !dbg !903
  %or = or i32 %9, %7, !dbg !903
  store i32 %or, i32* %flags6, align 8, !dbg !903
  %10 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !904
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %10, i32 0, i32 2, !dbg !906
  %11 = load i32, i32* %type, align 8, !dbg !906
  %cmp7 = icmp eq i32 %11, 12, !dbg !907
  br i1 %cmp7, label %if.then8, label %if.end24, !dbg !908

if.then8:                                         ; preds = %cond.end
  %12 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !909
  %flags9 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %12, i32 0, i32 7, !dbg !912
  %13 = load i32, i32* %flags9, align 8, !dbg !912
  %and = and i32 %13, 1024, !dbg !913
  %tobool = icmp ne i32 %and, 0, !dbg !913
  br i1 %tobool, label %land.lhs.true, label %if.end13, !dbg !914

land.lhs.true:                                    ; preds = %if.then8
  %14 = load i32, i32* %fd.addr, align 4, !dbg !915
  %call = call i32 @uv__tcp_nodelay(i32 %14, i32 1), !dbg !917
  %tobool10 = icmp ne i32 %call, 0, !dbg !917
  br i1 %tobool10, label %if.then11, label %if.end13, !dbg !918

if.then11:                                        ; preds = %land.lhs.true
  %call12 = call i32* @__errno_location() #1, !dbg !919
  %15 = load i32, i32* %call12, align 4, !dbg !919
  %sub = sub nsw i32 0, %15, !dbg !920
  store i32 %sub, i32* %retval, align 4, !dbg !921
  br label %return, !dbg !921

if.end13:                                         ; preds = %land.lhs.true, %if.then8
  %16 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !922
  %flags14 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %16, i32 0, i32 7, !dbg !924
  %17 = load i32, i32* %flags14, align 8, !dbg !924
  %and15 = and i32 %17, 2048, !dbg !925
  %tobool16 = icmp ne i32 %and15, 0, !dbg !925
  br i1 %tobool16, label %land.lhs.true17, label %if.end23, !dbg !926

land.lhs.true17:                                  ; preds = %if.end13
  %18 = load i32, i32* %fd.addr, align 4, !dbg !927
  %call18 = call i32 @uv__tcp_keepalive(i32 %18, i32 1, i32 60), !dbg !929
  %tobool19 = icmp ne i32 %call18, 0, !dbg !929
  br i1 %tobool19, label %if.then20, label %if.end23, !dbg !930

if.then20:                                        ; preds = %land.lhs.true17
  %call21 = call i32* @__errno_location() #1, !dbg !931
  %19 = load i32, i32* %call21, align 4, !dbg !931
  %sub22 = sub nsw i32 0, %19, !dbg !932
  store i32 %sub22, i32* %retval, align 4, !dbg !933
  br label %return, !dbg !933

if.end23:                                         ; preds = %land.lhs.true17, %if.end13
  br label %if.end24, !dbg !934

if.end24:                                         ; preds = %if.end23, %cond.end
  %20 = load i32, i32* %fd.addr, align 4, !dbg !935
  %21 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !936
  %io_watcher25 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %21, i32 0, i32 13, !dbg !937
  %fd26 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher25, i32 0, i32 5, !dbg !938
  store i32 %20, i32* %fd26, align 8, !dbg !939
  store i32 0, i32* %retval, align 4, !dbg !940
  br label %return, !dbg !940

return:                                           ; preds = %if.end24, %if.then20, %if.then11, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !941
  ret i32 %22, !dbg !941
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

declare i32 @uv__tcp_nodelay(i32, i32) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

declare i32 @uv__tcp_keepalive(i32, i32, i32) #2

; Function Attrs: nounwind uwtable
define void @uv__stream_flush_write_queue(%struct.uv_stream_s* %stream, i32 %error) #0 !dbg !612 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %error.addr = alloca i32, align 4
  %req = alloca %struct.uv_write_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !942, metadata !699), !dbg !943
  store i32 %error, i32* %error.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %error.addr, metadata !944, metadata !699), !dbg !945
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req, metadata !946, metadata !699), !dbg !947
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !948, metadata !699), !dbg !949
  br label %while.cond, !dbg !950

while.cond:                                       ; preds = %do.end24, %entry
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !951
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 14, !dbg !951
  %1 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !951
  %write_queue1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %1, i32 0, i32 14, !dbg !951
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue1, i64 0, i64 0, !dbg !951
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !951
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !951
  %cmp = icmp eq [2 x i8*]* %write_queue, %3, !dbg !951
  %lnot = xor i1 %cmp, true, !dbg !953
  br i1 %lnot, label %while.body, label %while.end, !dbg !954

while.body:                                       ; preds = %while.cond
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !955
  %write_queue2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 14, !dbg !955
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue2, i64 0, i64 0, !dbg !955
  %5 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !955
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !955
  store [2 x i8*]* %6, [2 x i8*]** %q, align 8, !dbg !957
  br label %do.body, !dbg !958

do.body:                                          ; preds = %while.body
  %7 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !959
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !959
  %8 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !959
  %9 = load [2 x i8*]*, [2 x i8*]** %8, align 8, !dbg !959
  %10 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !959
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %10, i64 0, i64 1, !dbg !959
  %11 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !959
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !959
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %12, i64 0, i64 0, !dbg !959
  %13 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !959
  store [2 x i8*]* %9, [2 x i8*]** %13, align 8, !dbg !959
  %14 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !959
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 1, !dbg !959
  %15 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !959
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !959
  %17 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !959
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %17, i64 0, i64 0, !dbg !959
  %18 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !959
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !959
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %19, i64 0, i64 1, !dbg !959
  %20 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !959
  store [2 x i8*]* %16, [2 x i8*]** %20, align 8, !dbg !959
  br label %do.end, !dbg !959

do.end:                                           ; preds = %do.body
  %21 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !962
  %22 = bitcast [2 x i8*]* %21 to i8*, !dbg !962
  %add.ptr = getelementptr inbounds i8, i8* %22, i64 -88, !dbg !962
  %23 = bitcast i8* %add.ptr to %struct.uv_write_s*, !dbg !962
  store %struct.uv_write_s* %23, %struct.uv_write_s** %req, align 8, !dbg !963
  %24 = load i32, i32* %error.addr, align 4, !dbg !964
  %25 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !965
  %error10 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %25, i32 0, i32 11, !dbg !966
  store i32 %24, i32* %error10, align 4, !dbg !967
  br label %do.body11, !dbg !968

do.body11:                                        ; preds = %do.end
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !969
  %write_completed_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %26, i32 0, i32 15, !dbg !969
  %27 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !969
  %queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %27, i32 0, i32 7, !dbg !969
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !969
  %28 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !969
  store [2 x i8*]* %write_completed_queue, [2 x i8*]** %28, align 8, !dbg !969
  %29 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !969
  %write_completed_queue13 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %29, i32 0, i32 15, !dbg !969
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue13, i64 0, i64 1, !dbg !969
  %30 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !969
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 8, !dbg !969
  %32 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !969
  %queue15 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %32, i32 0, i32 7, !dbg !969
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue15, i64 0, i64 1, !dbg !969
  %33 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !969
  store [2 x i8*]* %31, [2 x i8*]** %33, align 8, !dbg !969
  %34 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !969
  %queue17 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %34, i32 0, i32 7, !dbg !969
  %35 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !969
  %queue18 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %35, i32 0, i32 7, !dbg !969
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue18, i64 0, i64 1, !dbg !969
  %36 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !969
  %37 = load [2 x i8*]*, [2 x i8*]** %36, align 8, !dbg !969
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 0, !dbg !969
  %38 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !969
  store [2 x i8*]* %queue17, [2 x i8*]** %38, align 8, !dbg !969
  %39 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !969
  %queue21 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %39, i32 0, i32 7, !dbg !969
  %40 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !969
  %write_completed_queue22 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %40, i32 0, i32 15, !dbg !969
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue22, i64 0, i64 1, !dbg !969
  %41 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !969
  store [2 x i8*]* %queue21, [2 x i8*]** %41, align 8, !dbg !969
  br label %do.end24, !dbg !969

do.end24:                                         ; preds = %do.body11
  br label %while.cond, !dbg !972

while.end:                                        ; preds = %while.cond
  ret void, !dbg !974
}

; Function Attrs: nounwind uwtable
define void @uv__stream_destroy(%struct.uv_stream_s* %stream) #0 !dbg !613 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !975, metadata !699), !dbg !976
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !977
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 13, !dbg !977
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher, i32 5), !dbg !977
  %tobool = icmp ne i32 %call, 0, !dbg !977
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !977

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !978

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 443, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_destroy, i32 0, i32 0)) #7, !dbg !980
  unreachable, !dbg !980
                                                  ; No predecessors!
  br label %cond.end, !dbg !982

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !984
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 7, !dbg !984
  %3 = load i32, i32* %flags, align 8, !dbg !984
  %and = and i32 %3, 2, !dbg !984
  %tobool1 = icmp ne i32 %and, 0, !dbg !984
  br i1 %tobool1, label %cond.true2, label %cond.false3, !dbg !984

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !985

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 444, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_destroy, i32 0, i32 0)) #7, !dbg !986
  unreachable, !dbg !986
                                                  ; No predecessors!
  br label %cond.end4, !dbg !987

cond.end4:                                        ; preds = %4, %cond.true2
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !988
  %connect_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 11, !dbg !990
  %6 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req, align 8, !dbg !990
  %tobool5 = icmp ne %struct.uv_connect_s* %6, null, !dbg !988
  br i1 %tobool5, label %if.then, label %if.end, !dbg !991

if.then:                                          ; preds = %cond.end4
  br label %do.body, !dbg !992

do.body:                                          ; preds = %if.then
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !994
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 1, !dbg !994
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !994
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 3, !dbg !994
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !994
  %loop6 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 1, !dbg !994
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop6, align 8, !dbg !994
  %active_reqs7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 3, !dbg !994
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs7, i64 0, i64 0, !dbg !994
  %11 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !994
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !994
  %cmp = icmp eq [2 x i8*]* %active_reqs, %12, !dbg !994
  %conv = zext i1 %cmp to i32, !dbg !994
  %cmp8 = icmp eq i32 %conv, 0, !dbg !994
  br i1 %cmp8, label %cond.true10, label %cond.false11, !dbg !994

cond.true10:                                      ; preds = %do.body
  br label %cond.end12, !dbg !997

cond.false11:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 447, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_destroy, i32 0, i32 0)) #7, !dbg !999
  unreachable, !dbg !999
                                                  ; No predecessors!
  br label %cond.end12, !dbg !1001

cond.end12:                                       ; preds = %13, %cond.true10
  br label %do.body13, !dbg !1003

do.body13:                                        ; preds = %cond.end12
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1005
  %connect_req14 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %14, i32 0, i32 11, !dbg !1005
  %15 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req14, align 8, !dbg !1005
  %active_queue = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %15, i32 0, i32 2, !dbg !1005
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1005
  %16 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !1005
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !1005
  %18 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1005
  %connect_req16 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %18, i32 0, i32 11, !dbg !1005
  %19 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req16, align 8, !dbg !1005
  %active_queue17 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %19, i32 0, i32 2, !dbg !1005
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue17, i64 0, i64 1, !dbg !1005
  %20 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1005
  %21 = load [2 x i8*]*, [2 x i8*]** %20, align 8, !dbg !1005
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %21, i64 0, i64 0, !dbg !1005
  %22 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !1005
  store [2 x i8*]* %17, [2 x i8*]** %22, align 8, !dbg !1005
  %23 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1005
  %connect_req20 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %23, i32 0, i32 11, !dbg !1005
  %24 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req20, align 8, !dbg !1005
  %active_queue21 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %24, i32 0, i32 2, !dbg !1005
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue21, i64 0, i64 1, !dbg !1005
  %25 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !1005
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !1005
  %27 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1005
  %connect_req23 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %27, i32 0, i32 11, !dbg !1005
  %28 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req23, align 8, !dbg !1005
  %active_queue24 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %28, i32 0, i32 2, !dbg !1005
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue24, i64 0, i64 0, !dbg !1005
  %29 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !1005
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !1005
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %30, i64 0, i64 1, !dbg !1005
  %31 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !1005
  store [2 x i8*]* %26, [2 x i8*]** %31, align 8, !dbg !1005
  br label %do.end, !dbg !1005

do.end:                                           ; preds = %do.body13
  br label %do.end27, !dbg !1008

do.end27:                                         ; preds = %do.end
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1010
  %connect_req28 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %32, i32 0, i32 11, !dbg !1011
  %33 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req28, align 8, !dbg !1011
  %cb = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %33, i32 0, i32 4, !dbg !1012
  %34 = load void (%struct.uv_connect_s*, i32)*, void (%struct.uv_connect_s*, i32)** %cb, align 8, !dbg !1012
  %35 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1013
  %connect_req29 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %35, i32 0, i32 11, !dbg !1014
  %36 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req29, align 8, !dbg !1014
  call void %34(%struct.uv_connect_s* %36, i32 -125), !dbg !1010
  %37 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1015
  %connect_req30 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %37, i32 0, i32 11, !dbg !1016
  store %struct.uv_connect_s* null, %struct.uv_connect_s** %connect_req30, align 8, !dbg !1017
  br label %if.end, !dbg !1018

if.end:                                           ; preds = %do.end27, %cond.end4
  %38 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1019
  call void @uv__stream_flush_write_queue(%struct.uv_stream_s* %38, i32 -125), !dbg !1020
  %39 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1021
  call void @uv__write_callbacks(%struct.uv_stream_s* %39), !dbg !1022
  %40 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1023
  %shutdown_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %40, i32 0, i32 12, !dbg !1025
  %41 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req, align 8, !dbg !1025
  %tobool31 = icmp ne %struct.uv_shutdown_s* %41, null, !dbg !1023
  br i1 %tobool31, label %if.then32, label %if.end67, !dbg !1026

if.then32:                                        ; preds = %if.end
  br label %do.body33, !dbg !1027

do.body33:                                        ; preds = %if.then32
  %42 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1029
  %loop34 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %42, i32 0, i32 1, !dbg !1029
  %43 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop34, align 8, !dbg !1029
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %43, i32 0, i32 3, !dbg !1029
  %44 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1029
  %loop36 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %44, i32 0, i32 1, !dbg !1029
  %45 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop36, align 8, !dbg !1029
  %active_reqs37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %45, i32 0, i32 3, !dbg !1029
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs37, i64 0, i64 0, !dbg !1029
  %46 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1029
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1029
  %cmp39 = icmp eq [2 x i8*]* %active_reqs35, %47, !dbg !1029
  %conv40 = zext i1 %cmp39 to i32, !dbg !1029
  %cmp41 = icmp eq i32 %conv40, 0, !dbg !1029
  br i1 %cmp41, label %cond.true43, label %cond.false44, !dbg !1029

cond.true43:                                      ; preds = %do.body33
  br label %cond.end45, !dbg !1032

cond.false44:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 461, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_destroy, i32 0, i32 0)) #7, !dbg !1034
  unreachable, !dbg !1034
                                                  ; No predecessors!
  br label %cond.end45, !dbg !1036

cond.end45:                                       ; preds = %48, %cond.true43
  br label %do.body46, !dbg !1038

do.body46:                                        ; preds = %cond.end45
  %49 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1040
  %shutdown_req47 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %49, i32 0, i32 12, !dbg !1040
  %50 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req47, align 8, !dbg !1040
  %active_queue48 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %50, i32 0, i32 2, !dbg !1040
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue48, i64 0, i64 0, !dbg !1040
  %51 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !1040
  %52 = load [2 x i8*]*, [2 x i8*]** %51, align 8, !dbg !1040
  %53 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1040
  %shutdown_req50 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %53, i32 0, i32 12, !dbg !1040
  %54 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req50, align 8, !dbg !1040
  %active_queue51 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %54, i32 0, i32 2, !dbg !1040
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 1, !dbg !1040
  %55 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1040
  %56 = load [2 x i8*]*, [2 x i8*]** %55, align 8, !dbg !1040
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %56, i64 0, i64 0, !dbg !1040
  %57 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1040
  store [2 x i8*]* %52, [2 x i8*]** %57, align 8, !dbg !1040
  %58 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1040
  %shutdown_req54 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %58, i32 0, i32 12, !dbg !1040
  %59 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req54, align 8, !dbg !1040
  %active_queue55 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %59, i32 0, i32 2, !dbg !1040
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue55, i64 0, i64 1, !dbg !1040
  %60 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !1040
  %61 = load [2 x i8*]*, [2 x i8*]** %60, align 8, !dbg !1040
  %62 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1040
  %shutdown_req57 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %62, i32 0, i32 12, !dbg !1040
  %63 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req57, align 8, !dbg !1040
  %active_queue58 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %63, i32 0, i32 2, !dbg !1040
  %arrayidx59 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue58, i64 0, i64 0, !dbg !1040
  %64 = bitcast i8** %arrayidx59 to [2 x i8*]**, !dbg !1040
  %65 = load [2 x i8*]*, [2 x i8*]** %64, align 8, !dbg !1040
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %65, i64 0, i64 1, !dbg !1040
  %66 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !1040
  store [2 x i8*]* %61, [2 x i8*]** %66, align 8, !dbg !1040
  br label %do.end61, !dbg !1040

do.end61:                                         ; preds = %do.body46
  br label %do.end62, !dbg !1043

do.end62:                                         ; preds = %do.end61
  %67 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1045
  %shutdown_req63 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %67, i32 0, i32 12, !dbg !1046
  %68 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req63, align 8, !dbg !1046
  %cb64 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %68, i32 0, i32 5, !dbg !1047
  %69 = load void (%struct.uv_shutdown_s*, i32)*, void (%struct.uv_shutdown_s*, i32)** %cb64, align 8, !dbg !1047
  %70 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1048
  %shutdown_req65 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %70, i32 0, i32 12, !dbg !1049
  %71 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req65, align 8, !dbg !1049
  call void %69(%struct.uv_shutdown_s* %71, i32 -125), !dbg !1045
  %72 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1050
  %shutdown_req66 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %72, i32 0, i32 12, !dbg !1051
  store %struct.uv_shutdown_s* null, %struct.uv_shutdown_s** %shutdown_req66, align 8, !dbg !1052
  br label %if.end67, !dbg !1053

if.end67:                                         ; preds = %do.end62, %if.end
  %73 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1054
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %73, i32 0, i32 8, !dbg !1054
  %74 = load i64, i64* %write_queue_size, align 8, !dbg !1054
  %cmp68 = icmp eq i64 %74, 0, !dbg !1054
  br i1 %cmp68, label %cond.true70, label %cond.false71, !dbg !1054

cond.true70:                                      ; preds = %if.end67
  br label %cond.end72, !dbg !1055

cond.false71:                                     ; preds = %if.end67
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 466, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_destroy, i32 0, i32 0)) #7, !dbg !1056
  unreachable, !dbg !1056
                                                  ; No predecessors!
  br label %cond.end72, !dbg !1057

cond.end72:                                       ; preds = %75, %cond.true70
  ret void, !dbg !1058
}

declare i32 @uv__io_active(%struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__write_callbacks(%struct.uv_stream_s* %stream) #0 !dbg !660 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %req = alloca %struct.uv_write_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !1059, metadata !699), !dbg !1060
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req, metadata !1061, metadata !699), !dbg !1062
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1063, metadata !699), !dbg !1064
  br label %while.cond, !dbg !1065

while.cond:                                       ; preds = %if.end40, %entry
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1066
  %write_completed_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 15, !dbg !1066
  %1 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1066
  %write_completed_queue1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %1, i32 0, i32 15, !dbg !1066
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue1, i64 0, i64 0, !dbg !1066
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1066
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !1066
  %cmp = icmp eq [2 x i8*]* %write_completed_queue, %3, !dbg !1066
  %lnot = xor i1 %cmp, true, !dbg !1068
  br i1 %lnot, label %while.body, label %while.end, !dbg !1069

while.body:                                       ; preds = %while.cond
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1070
  %write_completed_queue2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 15, !dbg !1070
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue2, i64 0, i64 0, !dbg !1070
  %5 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !1070
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !1070
  store [2 x i8*]* %6, [2 x i8*]** %q, align 8, !dbg !1072
  %7 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1073
  %8 = bitcast [2 x i8*]* %7 to i8*, !dbg !1073
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 -88, !dbg !1073
  %9 = bitcast i8* %add.ptr to %struct.uv_write_s*, !dbg !1073
  store %struct.uv_write_s* %9, %struct.uv_write_s** %req, align 8, !dbg !1074
  br label %do.body, !dbg !1075

do.body:                                          ; preds = %while.body
  %10 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1076
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %10, i64 0, i64 0, !dbg !1076
  %11 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !1076
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !1076
  %13 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1076
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %13, i64 0, i64 1, !dbg !1076
  %14 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !1076
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !1076
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !1076
  %16 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !1076
  store [2 x i8*]* %12, [2 x i8*]** %16, align 8, !dbg !1076
  %17 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1076
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %17, i64 0, i64 1, !dbg !1076
  %18 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1076
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !1076
  %20 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1076
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %20, i64 0, i64 0, !dbg !1076
  %21 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !1076
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !1076
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !1076
  %23 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1076
  store [2 x i8*]* %19, [2 x i8*]** %23, align 8, !dbg !1076
  br label %do.end, !dbg !1076

do.end:                                           ; preds = %do.body
  br label %do.body10, !dbg !1079

do.body10:                                        ; preds = %do.end
  %24 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1080
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %24, i32 0, i32 1, !dbg !1080
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1080
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %25, i32 0, i32 3, !dbg !1080
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1080
  %loop11 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %26, i32 0, i32 1, !dbg !1080
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop11, align 8, !dbg !1080
  %active_reqs12 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 3, !dbg !1080
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs12, i64 0, i64 0, !dbg !1080
  %28 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1080
  %29 = load [2 x i8*]*, [2 x i8*]** %28, align 8, !dbg !1080
  %cmp14 = icmp eq [2 x i8*]* %active_reqs, %29, !dbg !1080
  %conv = zext i1 %cmp14 to i32, !dbg !1080
  %cmp15 = icmp eq i32 %conv, 0, !dbg !1080
  br i1 %cmp15, label %cond.true, label %cond.false, !dbg !1080

cond.true:                                        ; preds = %do.body10
  br label %cond.end, !dbg !1083

cond.false:                                       ; preds = %do.body10
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 938, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.uv__write_callbacks, i32 0, i32 0)) #7, !dbg !1085
  unreachable, !dbg !1085
                                                  ; No predecessors!
  br label %cond.end, !dbg !1087

cond.end:                                         ; preds = %30, %cond.true
  br label %do.body17, !dbg !1089

do.body17:                                        ; preds = %cond.end
  %31 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1091
  %active_queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %31, i32 0, i32 2, !dbg !1091
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1091
  %32 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1091
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 8, !dbg !1091
  %34 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1091
  %active_queue19 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %34, i32 0, i32 2, !dbg !1091
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue19, i64 0, i64 1, !dbg !1091
  %35 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !1091
  %36 = load [2 x i8*]*, [2 x i8*]** %35, align 8, !dbg !1091
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %36, i64 0, i64 0, !dbg !1091
  %37 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !1091
  store [2 x i8*]* %33, [2 x i8*]** %37, align 8, !dbg !1091
  %38 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1091
  %active_queue22 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %38, i32 0, i32 2, !dbg !1091
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue22, i64 0, i64 1, !dbg !1091
  %39 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !1091
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1091
  %41 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1091
  %active_queue24 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %41, i32 0, i32 2, !dbg !1091
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue24, i64 0, i64 0, !dbg !1091
  %42 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !1091
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !1091
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %43, i64 0, i64 1, !dbg !1091
  %44 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !1091
  store [2 x i8*]* %40, [2 x i8*]** %44, align 8, !dbg !1091
  br label %do.end27, !dbg !1091

do.end27:                                         ; preds = %do.body17
  br label %do.end28, !dbg !1094

do.end28:                                         ; preds = %do.end27
  %45 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1096
  %bufs = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %45, i32 0, i32 9, !dbg !1098
  %46 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !1098
  %cmp29 = icmp ne %struct.uv_buf_t* %46, null, !dbg !1099
  br i1 %cmp29, label %if.then, label %if.end37, !dbg !1100

if.then:                                          ; preds = %do.end28
  %47 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1101
  %call = call i64 @uv__write_req_size(%struct.uv_write_s* %47), !dbg !1103
  %48 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1104
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %48, i32 0, i32 8, !dbg !1105
  %49 = load i64, i64* %write_queue_size, align 8, !dbg !1106
  %sub = sub i64 %49, %call, !dbg !1106
  store i64 %sub, i64* %write_queue_size, align 8, !dbg !1106
  %50 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1107
  %bufs31 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %50, i32 0, i32 9, !dbg !1109
  %51 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs31, align 8, !dbg !1109
  %52 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1110
  %bufsml = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %52, i32 0, i32 12, !dbg !1111
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !1110
  %cmp32 = icmp ne %struct.uv_buf_t* %51, %arraydecay, !dbg !1112
  br i1 %cmp32, label %if.then34, label %if.end, !dbg !1113

if.then34:                                        ; preds = %if.then
  %53 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1114
  %bufs35 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %53, i32 0, i32 9, !dbg !1115
  %54 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs35, align 8, !dbg !1115
  %55 = bitcast %struct.uv_buf_t* %54 to i8*, !dbg !1114
  call void @uv__free(i8* %55), !dbg !1116
  br label %if.end, !dbg !1116

if.end:                                           ; preds = %if.then34, %if.then
  %56 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1117
  %bufs36 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %56, i32 0, i32 9, !dbg !1118
  store %struct.uv_buf_t* null, %struct.uv_buf_t** %bufs36, align 8, !dbg !1119
  br label %if.end37, !dbg !1120

if.end37:                                         ; preds = %if.end, %do.end28
  %57 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1121
  %cb = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %57, i32 0, i32 4, !dbg !1123
  %58 = load void (%struct.uv_write_s*, i32)*, void (%struct.uv_write_s*, i32)** %cb, align 8, !dbg !1123
  %tobool = icmp ne void (%struct.uv_write_s*, i32)* %58, null, !dbg !1121
  br i1 %tobool, label %if.then38, label %if.end40, !dbg !1124

if.then38:                                        ; preds = %if.end37
  %59 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1125
  %cb39 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %59, i32 0, i32 4, !dbg !1126
  %60 = load void (%struct.uv_write_s*, i32)*, void (%struct.uv_write_s*, i32)** %cb39, align 8, !dbg !1126
  %61 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1127
  %62 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1128
  %error = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %62, i32 0, i32 11, !dbg !1129
  %63 = load i32, i32* %error, align 4, !dbg !1129
  call void %60(%struct.uv_write_s* %61, i32 %63), !dbg !1125
  br label %if.end40, !dbg !1125

if.end40:                                         ; preds = %if.then38, %if.end37
  br label %while.cond, !dbg !1130

while.end:                                        ; preds = %while.cond
  %64 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1132
  %write_completed_queue41 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %64, i32 0, i32 15, !dbg !1132
  %65 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1132
  %write_completed_queue42 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %65, i32 0, i32 15, !dbg !1132
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue42, i64 0, i64 0, !dbg !1132
  %66 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !1132
  %67 = load [2 x i8*]*, [2 x i8*]** %66, align 8, !dbg !1132
  %cmp44 = icmp eq [2 x i8*]* %write_completed_queue41, %67, !dbg !1132
  br i1 %cmp44, label %cond.true46, label %cond.false47, !dbg !1132

cond.true46:                                      ; preds = %while.end
  br label %cond.end48, !dbg !1133

cond.false47:                                     ; preds = %while.end
  call void @__assert_fail(i8* getelementptr inbounds ([126 x i8], [126 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 952, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.uv__write_callbacks, i32 0, i32 0)) #7, !dbg !1134
  unreachable, !dbg !1134
                                                  ; No predecessors!
  br label %cond.end48, !dbg !1135

cond.end48:                                       ; preds = %68, %cond.true46
  ret void, !dbg !1137
}

; Function Attrs: nounwind uwtable
define void @uv__server_io(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !616 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  %stream = alloca %struct.uv_stream_s*, align 8
  %err = alloca i32, align 4
  %timeout = alloca %struct.timespec, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1138, metadata !699), !dbg !1139
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !1140, metadata !699), !dbg !1141
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !1142, metadata !699), !dbg !1143
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream, metadata !1144, metadata !699), !dbg !1145
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1146, metadata !699), !dbg !1147
  %0 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !1148
  %1 = bitcast %struct.uv__io_s* %0 to i8*, !dbg !1148
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -136, !dbg !1148
  %2 = bitcast i8* %add.ptr to %struct.uv_stream_s*, !dbg !1148
  store %struct.uv_stream_s* %2, %struct.uv_stream_s** %stream, align 8, !dbg !1149
  %3 = load i32, i32* %events.addr, align 4, !dbg !1150
  %cmp = icmp eq i32 %3, 1, !dbg !1150
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1150

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1151

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 517, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__server_io, i32 0, i32 0)) #7, !dbg !1153
  unreachable, !dbg !1153
                                                  ; No predecessors!
  br label %cond.end, !dbg !1155

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1157
  %accepted_fd = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 18, !dbg !1157
  %6 = load i32, i32* %accepted_fd, align 4, !dbg !1157
  %cmp1 = icmp eq i32 %6, -1, !dbg !1157
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !1157

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !1158

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 518, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__server_io, i32 0, i32 0)) #7, !dbg !1159
  unreachable, !dbg !1159
                                                  ; No predecessors!
  br label %cond.end4, !dbg !1160

cond.end4:                                        ; preds = %7, %cond.true2
  %8 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1161
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %8, i32 0, i32 7, !dbg !1161
  %9 = load i32, i32* %flags, align 8, !dbg !1161
  %and = and i32 %9, 1, !dbg !1161
  %tobool = icmp ne i32 %and, 0, !dbg !1161
  br i1 %tobool, label %cond.false6, label %cond.true5, !dbg !1161

cond.true5:                                       ; preds = %cond.end4
  br label %cond.end7, !dbg !1162

cond.false6:                                      ; preds = %cond.end4
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 519, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__server_io, i32 0, i32 0)) #7, !dbg !1163
  unreachable, !dbg !1163
                                                  ; No predecessors!
  br label %cond.end7, !dbg !1164

cond.end7:                                        ; preds = %10, %cond.true5
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1165
  %loop8 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 1, !dbg !1166
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop8, align 8, !dbg !1166
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1167
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 13, !dbg !1168
  call void @uv__io_start(%struct.uv_loop_s* %12, %struct.uv__io_s* %io_watcher, i32 1), !dbg !1169
  br label %while.cond, !dbg !1170

while.cond:                                       ; preds = %if.end52, %if.end37, %if.then23, %cond.end7
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1171
  %io_watcher9 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %14, i32 0, i32 13, !dbg !1171
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher9, i32 0, i32 5, !dbg !1171
  %15 = load i32, i32* %fd, align 8, !dbg !1171
  %cmp10 = icmp ne i32 %15, -1, !dbg !1172
  br i1 %cmp10, label %while.body, label %while.end, !dbg !1173

while.body:                                       ; preds = %while.cond
  %16 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1174
  %accepted_fd11 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %16, i32 0, i32 18, !dbg !1174
  %17 = load i32, i32* %accepted_fd11, align 4, !dbg !1174
  %cmp12 = icmp eq i32 %17, -1, !dbg !1174
  br i1 %cmp12, label %cond.true13, label %cond.false14, !dbg !1174

cond.true13:                                      ; preds = %while.body
  br label %cond.end15, !dbg !1176

cond.false14:                                     ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 527, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__server_io, i32 0, i32 0)) #7, !dbg !1178
  unreachable, !dbg !1178
                                                  ; No predecessors!
  br label %cond.end15, !dbg !1180

cond.end15:                                       ; preds = %18, %cond.true13
  %19 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1182
  %io_watcher16 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %19, i32 0, i32 13, !dbg !1182
  %fd17 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher16, i32 0, i32 5, !dbg !1182
  %20 = load i32, i32* %fd17, align 8, !dbg !1182
  %call = call i32 @uv__accept(i32 %20), !dbg !1183
  store i32 %call, i32* %err, align 4, !dbg !1184
  %21 = load i32, i32* %err, align 4, !dbg !1185
  %cmp18 = icmp slt i32 %21, 0, !dbg !1187
  br i1 %cmp18, label %if.then, label %if.end38, !dbg !1188

if.then:                                          ; preds = %cond.end15
  %22 = load i32, i32* %err, align 4, !dbg !1189
  %cmp19 = icmp eq i32 %22, -11, !dbg !1192
  br i1 %cmp19, label %if.then21, label %lor.lhs.false, !dbg !1193

lor.lhs.false:                                    ; preds = %if.then
  %23 = load i32, i32* %err, align 4, !dbg !1194
  %cmp20 = icmp eq i32 %23, -11, !dbg !1196
  br i1 %cmp20, label %if.then21, label %if.end, !dbg !1197

if.then21:                                        ; preds = %lor.lhs.false, %if.then
  br label %while.end, !dbg !1198

if.end:                                           ; preds = %lor.lhs.false
  %24 = load i32, i32* %err, align 4, !dbg !1199
  %cmp22 = icmp eq i32 %24, -103, !dbg !1201
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !1202

if.then23:                                        ; preds = %if.end
  br label %while.cond, !dbg !1203

if.end24:                                         ; preds = %if.end
  %25 = load i32, i32* %err, align 4, !dbg !1204
  %cmp25 = icmp eq i32 %25, -24, !dbg !1206
  br i1 %cmp25, label %if.then28, label %lor.lhs.false26, !dbg !1207

lor.lhs.false26:                                  ; preds = %if.end24
  %26 = load i32, i32* %err, align 4, !dbg !1208
  %cmp27 = icmp eq i32 %26, -23, !dbg !1210
  br i1 %cmp27, label %if.then28, label %if.end37, !dbg !1211

if.then28:                                        ; preds = %lor.lhs.false26, %if.end24
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1212
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1214
  %io_watcher29 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 13, !dbg !1214
  %fd30 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher29, i32 0, i32 5, !dbg !1214
  %29 = load i32, i32* %fd30, align 8, !dbg !1214
  %call31 = call i32 @uv__emfile_trick(%struct.uv_loop_s* %27, i32 %29), !dbg !1215
  store i32 %call31, i32* %err, align 4, !dbg !1216
  %30 = load i32, i32* %err, align 4, !dbg !1217
  %cmp32 = icmp eq i32 %30, -11, !dbg !1219
  br i1 %cmp32, label %if.then35, label %lor.lhs.false33, !dbg !1220

lor.lhs.false33:                                  ; preds = %if.then28
  %31 = load i32, i32* %err, align 4, !dbg !1221
  %cmp34 = icmp eq i32 %31, -11, !dbg !1223
  br i1 %cmp34, label %if.then35, label %if.end36, !dbg !1224

if.then35:                                        ; preds = %lor.lhs.false33, %if.then28
  br label %while.end, !dbg !1225

if.end36:                                         ; preds = %lor.lhs.false33
  br label %if.end37, !dbg !1226

if.end37:                                         ; preds = %if.end36, %lor.lhs.false26
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1227
  %connection_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %32, i32 0, i32 16, !dbg !1228
  %33 = load void (%struct.uv_stream_s*, i32)*, void (%struct.uv_stream_s*, i32)** %connection_cb, align 8, !dbg !1228
  %34 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1229
  %35 = load i32, i32* %err, align 4, !dbg !1230
  call void %33(%struct.uv_stream_s* %34, i32 %35), !dbg !1227
  br label %while.cond, !dbg !1231

if.end38:                                         ; preds = %cond.end15
  %36 = load i32, i32* %err, align 4, !dbg !1232
  %37 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1233
  %accepted_fd39 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %37, i32 0, i32 18, !dbg !1234
  store i32 %36, i32* %accepted_fd39, align 4, !dbg !1235
  %38 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1236
  %connection_cb40 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %38, i32 0, i32 16, !dbg !1237
  %39 = load void (%struct.uv_stream_s*, i32)*, void (%struct.uv_stream_s*, i32)** %connection_cb40, align 8, !dbg !1237
  %40 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1238
  call void %39(%struct.uv_stream_s* %40, i32 0), !dbg !1236
  %41 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1239
  %accepted_fd41 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %41, i32 0, i32 18, !dbg !1241
  %42 = load i32, i32* %accepted_fd41, align 4, !dbg !1241
  %cmp42 = icmp ne i32 %42, -1, !dbg !1242
  br i1 %cmp42, label %if.then43, label %if.end45, !dbg !1243

if.then43:                                        ; preds = %if.end38
  %43 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1244
  %44 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1246
  %io_watcher44 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %44, i32 0, i32 13, !dbg !1247
  call void @uv__io_stop(%struct.uv_loop_s* %43, %struct.uv__io_s* %io_watcher44, i32 1), !dbg !1248
  br label %while.end, !dbg !1249

if.end45:                                         ; preds = %if.end38
  %45 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1250
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %45, i32 0, i32 2, !dbg !1252
  %46 = load i32, i32* %type, align 8, !dbg !1252
  %cmp46 = icmp eq i32 %46, 12, !dbg !1253
  br i1 %cmp46, label %land.lhs.true, label %if.end52, !dbg !1254

land.lhs.true:                                    ; preds = %if.end45
  %47 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1255
  %flags47 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %47, i32 0, i32 7, !dbg !1257
  %48 = load i32, i32* %flags47, align 8, !dbg !1257
  %and48 = and i32 %48, 4096, !dbg !1258
  %tobool49 = icmp ne i32 %and48, 0, !dbg !1258
  br i1 %tobool49, label %if.then50, label %if.end52, !dbg !1259

if.then50:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.timespec* %timeout, metadata !1260, metadata !699), !dbg !1269
  %49 = bitcast %struct.timespec* %timeout to i8*, !dbg !1269
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %49, i8* bitcast (%struct.timespec* @uv__server_io.timeout to i8*), i64 16, i32 8, i1 false), !dbg !1269
  %call51 = call i32 @nanosleep(%struct.timespec* %timeout, %struct.timespec* null), !dbg !1270
  br label %if.end52, !dbg !1271

if.end52:                                         ; preds = %if.then50, %land.lhs.true, %if.end45
  br label %while.cond, !dbg !1272

while.end:                                        ; preds = %if.then21, %if.then43, %if.then35, %while.cond
  ret void, !dbg !1273
}

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

declare i32 @uv__accept(i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__emfile_trick(%struct.uv_loop_s* %loop, i32 %accept_fd) #0 !dbg !657 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %accept_fd.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %emfile_fd = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1274, metadata !699), !dbg !1275
  store i32 %accept_fd, i32* %accept_fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %accept_fd.addr, metadata !1276, metadata !699), !dbg !1277
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1278, metadata !699), !dbg !1279
  call void @llvm.dbg.declare(metadata i32* %emfile_fd, metadata !1280, metadata !699), !dbg !1281
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1282
  %emfile_fd1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 31, !dbg !1284
  %1 = load i32, i32* %emfile_fd1, align 8, !dbg !1284
  %cmp = icmp eq i32 %1, -1, !dbg !1285
  br i1 %cmp, label %if.then, label %if.end, !dbg !1286

if.then:                                          ; preds = %entry
  store i32 -24, i32* %retval, align 4, !dbg !1287
  br label %return, !dbg !1287

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1288
  %emfile_fd2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 31, !dbg !1289
  %3 = load i32, i32* %emfile_fd2, align 8, !dbg !1289
  %call = call i32 @uv__close(i32 %3), !dbg !1290
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1291
  %emfile_fd3 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 31, !dbg !1292
  store i32 -1, i32* %emfile_fd3, align 8, !dbg !1293
  br label %do.body, !dbg !1294

do.body:                                          ; preds = %lor.end, %if.end
  %5 = load i32, i32* %accept_fd.addr, align 4, !dbg !1295
  %call4 = call i32 @uv__accept(i32 %5), !dbg !1297
  store i32 %call4, i32* %err, align 4, !dbg !1298
  %6 = load i32, i32* %err, align 4, !dbg !1299
  %cmp5 = icmp sge i32 %6, 0, !dbg !1301
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !1302

if.then6:                                         ; preds = %do.body
  %7 = load i32, i32* %err, align 4, !dbg !1303
  %call7 = call i32 @uv__close(i32 %7), !dbg !1304
  br label %if.end8, !dbg !1304

if.end8:                                          ; preds = %if.then6, %do.body
  br label %do.cond, !dbg !1305

do.cond:                                          ; preds = %if.end8
  %8 = load i32, i32* %err, align 4, !dbg !1306
  %cmp9 = icmp sge i32 %8, 0, !dbg !1308
  br i1 %cmp9, label %lor.end, label %lor.rhs, !dbg !1309

lor.rhs:                                          ; preds = %do.cond
  %9 = load i32, i32* %err, align 4, !dbg !1310
  %cmp10 = icmp eq i32 %9, -4, !dbg !1312
  br label %lor.end, !dbg !1313

lor.end:                                          ; preds = %lor.rhs, %do.cond
  %10 = phi i1 [ true, %do.cond ], [ %cmp10, %lor.rhs ]
  br i1 %10, label %do.body, label %do.end, !dbg !1314

do.end:                                           ; preds = %lor.end
  %call11 = call i32 @uv__open_cloexec(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0), i32 0), !dbg !1316
  store i32 %call11, i32* %emfile_fd, align 4, !dbg !1317
  %11 = load i32, i32* %emfile_fd, align 4, !dbg !1318
  %cmp12 = icmp sge i32 %11, 0, !dbg !1320
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !1321

if.then13:                                        ; preds = %do.end
  %12 = load i32, i32* %emfile_fd, align 4, !dbg !1322
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1323
  %emfile_fd14 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 31, !dbg !1324
  store i32 %12, i32* %emfile_fd14, align 8, !dbg !1325
  br label %if.end15, !dbg !1323

if.end15:                                         ; preds = %if.then13, %do.end
  %14 = load i32, i32* %err, align 4, !dbg !1326
  store i32 %14, i32* %retval, align 4, !dbg !1327
  br label %return, !dbg !1327

return:                                           ; preds = %if.end15, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !1328
  ret i32 %15, !dbg !1328
}

declare void @uv__io_stop(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare i32 @nanosleep(%struct.timespec*, %struct.timespec*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_accept(%struct.uv_stream_s* %server, %struct.uv_stream_s* %client) #0 !dbg !619 {
entry:
  %retval = alloca i32, align 4
  %server.addr = alloca %struct.uv_stream_s*, align 8
  %client.addr = alloca %struct.uv_stream_s*, align 8
  %err = alloca i32, align 4
  %queued_fds18 = alloca %struct.uv__stream_queued_fds_s*, align 8
  store %struct.uv_stream_s* %server, %struct.uv_stream_s** %server.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %server.addr, metadata !1329, metadata !699), !dbg !1330
  store %struct.uv_stream_s* %client, %struct.uv_stream_s** %client.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %client.addr, metadata !1331, metadata !699), !dbg !1332
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1333, metadata !699), !dbg !1334
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1335
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 1, !dbg !1335
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1335
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %client.addr, align 8, !dbg !1335
  %loop1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 1, !dbg !1335
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !1335
  %cmp = icmp eq %struct.uv_loop_s* %1, %3, !dbg !1335
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1335

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1336

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 577, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @__PRETTY_FUNCTION__.uv_accept, i32 0, i32 0)) #7, !dbg !1338
  unreachable, !dbg !1338
                                                  ; No predecessors!
  br label %cond.end, !dbg !1340

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1342
  %accepted_fd = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 18, !dbg !1344
  %6 = load i32, i32* %accepted_fd, align 4, !dbg !1344
  %cmp2 = icmp eq i32 %6, -1, !dbg !1345
  br i1 %cmp2, label %if.then, label %if.end, !dbg !1346

if.then:                                          ; preds = %cond.end
  store i32 -11, i32* %retval, align 4, !dbg !1347
  br label %return, !dbg !1347

if.end:                                           ; preds = %cond.end
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %client.addr, align 8, !dbg !1348
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 2, !dbg !1349
  %8 = load i32, i32* %type, align 8, !dbg !1349
  switch i32 %8, label %sw.default [
    i32 7, label %sw.bb
    i32 12, label %sw.bb
    i32 15, label %sw.bb8
  ], !dbg !1350

sw.bb:                                            ; preds = %if.end, %if.end
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %client.addr, align 8, !dbg !1351
  %10 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1353
  %accepted_fd3 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %10, i32 0, i32 18, !dbg !1354
  %11 = load i32, i32* %accepted_fd3, align 4, !dbg !1354
  %call = call i32 @uv__stream_open(%struct.uv_stream_s* %9, i32 %11, i32 96), !dbg !1355
  store i32 %call, i32* %err, align 4, !dbg !1356
  %12 = load i32, i32* %err, align 4, !dbg !1357
  %tobool = icmp ne i32 %12, 0, !dbg !1357
  br i1 %tobool, label %if.then4, label %if.end7, !dbg !1359

if.then4:                                         ; preds = %sw.bb
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1360
  %accepted_fd5 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 18, !dbg !1362
  %14 = load i32, i32* %accepted_fd5, align 4, !dbg !1362
  %call6 = call i32 @uv__close(i32 %14), !dbg !1363
  br label %done, !dbg !1364

if.end7:                                          ; preds = %sw.bb
  br label %sw.epilog, !dbg !1365

sw.bb8:                                           ; preds = %if.end
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %client.addr, align 8, !dbg !1366
  %16 = bitcast %struct.uv_stream_s* %15 to %struct.uv_udp_s*, !dbg !1367
  %17 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1368
  %accepted_fd9 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %17, i32 0, i32 18, !dbg !1369
  %18 = load i32, i32* %accepted_fd9, align 4, !dbg !1369
  %call10 = call i32 @uv_udp_open(%struct.uv_udp_s* %16, i32 %18), !dbg !1370
  store i32 %call10, i32* %err, align 4, !dbg !1371
  %19 = load i32, i32* %err, align 4, !dbg !1372
  %tobool11 = icmp ne i32 %19, 0, !dbg !1372
  br i1 %tobool11, label %if.then12, label %if.end15, !dbg !1374

if.then12:                                        ; preds = %sw.bb8
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1375
  %accepted_fd13 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %20, i32 0, i32 18, !dbg !1377
  %21 = load i32, i32* %accepted_fd13, align 4, !dbg !1377
  %call14 = call i32 @uv__close(i32 %21), !dbg !1378
  br label %done, !dbg !1379

if.end15:                                         ; preds = %sw.bb8
  br label %sw.epilog, !dbg !1380

sw.default:                                       ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !1381
  br label %return, !dbg !1381

sw.epilog:                                        ; preds = %if.end15, %if.end7
  %22 = load %struct.uv_stream_s*, %struct.uv_stream_s** %client.addr, align 8, !dbg !1382
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %22, i32 0, i32 7, !dbg !1383
  %23 = load i32, i32* %flags, align 8, !dbg !1384
  %or = or i32 %23, 262144, !dbg !1384
  store i32 %or, i32* %flags, align 8, !dbg !1384
  br label %done, !dbg !1382

done:                                             ; preds = %sw.epilog, %if.then12, %if.then4
  %24 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1385
  %queued_fds = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %24, i32 0, i32 19, !dbg !1387
  %25 = load i8*, i8** %queued_fds, align 8, !dbg !1387
  %cmp16 = icmp ne i8* %25, null, !dbg !1388
  br i1 %cmp16, label %if.then17, label %if.else34, !dbg !1389

if.then17:                                        ; preds = %done
  call void @llvm.dbg.declare(metadata %struct.uv__stream_queued_fds_s** %queued_fds18, metadata !1390, metadata !699), !dbg !1402
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1403
  %queued_fds19 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %26, i32 0, i32 19, !dbg !1404
  %27 = load i8*, i8** %queued_fds19, align 8, !dbg !1404
  %28 = bitcast i8* %27 to %struct.uv__stream_queued_fds_s*, !dbg !1403
  store %struct.uv__stream_queued_fds_s* %28, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1405
  %29 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1406
  %fds = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %29, i32 0, i32 2, !dbg !1407
  %arrayidx = getelementptr inbounds [1 x i32], [1 x i32]* %fds, i64 0, i64 0, !dbg !1406
  %30 = load i32, i32* %arrayidx, align 4, !dbg !1406
  %31 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1408
  %accepted_fd20 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %31, i32 0, i32 18, !dbg !1409
  store i32 %30, i32* %accepted_fd20, align 4, !dbg !1410
  %32 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1411
  %offset = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %32, i32 0, i32 1, !dbg !1411
  %33 = load i32, i32* %offset, align 4, !dbg !1411
  %cmp21 = icmp ugt i32 %33, 0, !dbg !1411
  br i1 %cmp21, label %cond.true22, label %cond.false23, !dbg !1411

cond.true22:                                      ; preds = %if.then17
  br label %cond.end24, !dbg !1412

cond.false23:                                     ; preds = %if.then17
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 620, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @__PRETTY_FUNCTION__.uv_accept, i32 0, i32 0)) #7, !dbg !1414
  unreachable, !dbg !1414
                                                  ; No predecessors!
  br label %cond.end24, !dbg !1416

cond.end24:                                       ; preds = %34, %cond.true22
  %35 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1418
  %offset25 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %35, i32 0, i32 1, !dbg !1420
  %36 = load i32, i32* %offset25, align 4, !dbg !1421
  %dec = add i32 %36, -1, !dbg !1421
  store i32 %dec, i32* %offset25, align 4, !dbg !1421
  %cmp26 = icmp eq i32 %dec, 0, !dbg !1422
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1423

if.then27:                                        ; preds = %cond.end24
  %37 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1424
  %38 = bitcast %struct.uv__stream_queued_fds_s* %37 to i8*, !dbg !1424
  call void @uv__free(i8* %38), !dbg !1426
  %39 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1427
  %queued_fds28 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %39, i32 0, i32 19, !dbg !1428
  store i8* null, i8** %queued_fds28, align 8, !dbg !1429
  br label %if.end33, !dbg !1430

if.else:                                          ; preds = %cond.end24
  %40 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1431
  %fds29 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %40, i32 0, i32 2, !dbg !1433
  %arraydecay = getelementptr inbounds [1 x i32], [1 x i32]* %fds29, i32 0, i32 0, !dbg !1434
  %41 = bitcast i32* %arraydecay to i8*, !dbg !1434
  %42 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1435
  %fds30 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %42, i32 0, i32 2, !dbg !1436
  %arraydecay31 = getelementptr inbounds [1 x i32], [1 x i32]* %fds30, i32 0, i32 0, !dbg !1435
  %add.ptr = getelementptr inbounds i32, i32* %arraydecay31, i64 1, !dbg !1437
  %43 = bitcast i32* %add.ptr to i8*, !dbg !1434
  %44 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds18, align 8, !dbg !1438
  %offset32 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %44, i32 0, i32 1, !dbg !1439
  %45 = load i32, i32* %offset32, align 4, !dbg !1439
  %conv = zext i32 %45 to i64, !dbg !1438
  %mul = mul i64 %conv, 4, !dbg !1440
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %41, i8* %43, i64 %mul, i32 4, i1 false), !dbg !1434
  br label %if.end33

if.end33:                                         ; preds = %if.else, %if.then27
  br label %if.end41, !dbg !1441

if.else34:                                        ; preds = %done
  %46 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1442
  %accepted_fd35 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %46, i32 0, i32 18, !dbg !1444
  store i32 -1, i32* %accepted_fd35, align 4, !dbg !1445
  %47 = load i32, i32* %err, align 4, !dbg !1446
  %cmp36 = icmp eq i32 %47, 0, !dbg !1448
  br i1 %cmp36, label %if.then38, label %if.end40, !dbg !1449

if.then38:                                        ; preds = %if.else34
  %48 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1450
  %loop39 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %48, i32 0, i32 1, !dbg !1451
  %49 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop39, align 8, !dbg !1451
  %50 = load %struct.uv_stream_s*, %struct.uv_stream_s** %server.addr, align 8, !dbg !1452
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %50, i32 0, i32 13, !dbg !1453
  call void @uv__io_start(%struct.uv_loop_s* %49, %struct.uv__io_s* %io_watcher, i32 1), !dbg !1454
  br label %if.end40, !dbg !1454

if.end40:                                         ; preds = %if.then38, %if.else34
  br label %if.end41

if.end41:                                         ; preds = %if.end40, %if.end33
  %51 = load i32, i32* %err, align 4, !dbg !1455
  store i32 %51, i32* %retval, align 4, !dbg !1456
  br label %return, !dbg !1456

return:                                           ; preds = %if.end41, %sw.default, %if.then
  %52 = load i32, i32* %retval, align 4, !dbg !1457
  ret i32 %52, !dbg !1457
}

declare i32 @uv__close(i32) #2

declare i32 @uv_udp_open(%struct.uv_udp_s*, i32) #2

declare void @uv__free(i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define i32 @uv_listen(%struct.uv_stream_s* %stream, i32 %backlog, void (%struct.uv_stream_s*, i32)* %cb) #0 !dbg !622 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %backlog.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_stream_s*, i32)*, align 8
  %err = alloca i32, align 4
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !1458, metadata !699), !dbg !1459
  store i32 %backlog, i32* %backlog.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %backlog.addr, metadata !1460, metadata !699), !dbg !1461
  store void (%struct.uv_stream_s*, i32)* %cb, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_stream_s*, i32)** %cb.addr, metadata !1462, metadata !699), !dbg !1463
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1464, metadata !699), !dbg !1465
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1466
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 2, !dbg !1467
  %1 = load i32, i32* %type, align 8, !dbg !1467
  switch i32 %1, label %sw.default [
    i32 12, label %sw.bb
    i32 7, label %sw.bb1
  ], !dbg !1468

sw.bb:                                            ; preds = %entry
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1469
  %3 = bitcast %struct.uv_stream_s* %2 to %struct.uv_tcp_s*, !dbg !1471
  %4 = load i32, i32* %backlog.addr, align 4, !dbg !1472
  %5 = load void (%struct.uv_stream_s*, i32)*, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8, !dbg !1473
  %call = call i32 @uv_tcp_listen(%struct.uv_tcp_s* %3, i32 %4, void (%struct.uv_stream_s*, i32)* %5), !dbg !1474
  store i32 %call, i32* %err, align 4, !dbg !1475
  br label %sw.epilog, !dbg !1476

sw.bb1:                                           ; preds = %entry
  %6 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1477
  %7 = bitcast %struct.uv_stream_s* %6 to %struct.uv_pipe_s*, !dbg !1478
  %8 = load i32, i32* %backlog.addr, align 4, !dbg !1479
  %9 = load void (%struct.uv_stream_s*, i32)*, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8, !dbg !1480
  %call2 = call i32 @uv_pipe_listen(%struct.uv_pipe_s* %7, i32 %8, void (%struct.uv_stream_s*, i32)* %9), !dbg !1481
  store i32 %call2, i32* %err, align 4, !dbg !1482
  br label %sw.epilog, !dbg !1483

sw.default:                                       ; preds = %entry
  store i32 -22, i32* %err, align 4, !dbg !1484
  br label %sw.epilog, !dbg !1485

sw.epilog:                                        ; preds = %sw.default, %sw.bb1, %sw.bb
  %10 = load i32, i32* %err, align 4, !dbg !1486
  %cmp = icmp eq i32 %10, 0, !dbg !1488
  br i1 %cmp, label %if.then, label %if.end16, !dbg !1489

if.then:                                          ; preds = %sw.epilog
  br label %do.body, !dbg !1490

do.body:                                          ; preds = %if.then
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1491
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 7, !dbg !1491
  %12 = load i32, i32* %flags, align 8, !dbg !1491
  %and = and i32 %12, 0, !dbg !1491
  %cmp3 = icmp eq i32 %and, 0, !dbg !1491
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !1491

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !1494

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 656, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @__PRETTY_FUNCTION__.uv_listen, i32 0, i32 0)) #7, !dbg !1496
  unreachable, !dbg !1496
                                                  ; No predecessors!
  br label %cond.end, !dbg !1498

cond.end:                                         ; preds = %13, %cond.true
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1500
  %flags4 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %14, i32 0, i32 7, !dbg !1500
  %15 = load i32, i32* %flags4, align 8, !dbg !1500
  %and5 = and i32 %15, 16384, !dbg !1500
  %cmp6 = icmp ne i32 %and5, 0, !dbg !1500
  br i1 %cmp6, label %if.then7, label %if.end, !dbg !1500

if.then7:                                         ; preds = %cond.end
  br label %do.end15, !dbg !1503

if.end:                                           ; preds = %cond.end
  %16 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1505
  %flags8 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %16, i32 0, i32 7, !dbg !1505
  %17 = load i32, i32* %flags8, align 8, !dbg !1505
  %or = or i32 %17, 16384, !dbg !1505
  store i32 %or, i32* %flags8, align 8, !dbg !1505
  %18 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1505
  %flags9 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %18, i32 0, i32 7, !dbg !1505
  %19 = load i32, i32* %flags9, align 8, !dbg !1505
  %and10 = and i32 %19, 8192, !dbg !1505
  %cmp11 = icmp ne i32 %and10, 0, !dbg !1505
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !1505

if.then12:                                        ; preds = %if.end
  br label %do.body13, !dbg !1507

do.body13:                                        ; preds = %if.then12
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1510
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %20, i32 0, i32 1, !dbg !1510
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1510
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 1, !dbg !1510
  %22 = load i32, i32* %active_handles, align 8, !dbg !1510
  %inc = add i32 %22, 1, !dbg !1510
  store i32 %inc, i32* %active_handles, align 8, !dbg !1510
  br label %do.end, !dbg !1510

do.end:                                           ; preds = %do.body13
  br label %if.end14, !dbg !1513

if.end14:                                         ; preds = %do.end, %if.end
  br label %do.end15, !dbg !1515

do.end15:                                         ; preds = %if.end14, %if.then7
  br label %if.end16, !dbg !1517

if.end16:                                         ; preds = %do.end15, %sw.epilog
  %23 = load i32, i32* %err, align 4, !dbg !1519
  ret i32 %23, !dbg !1520
}

declare i32 @uv_tcp_listen(%struct.uv_tcp_s*, i32, void (%struct.uv_stream_s*, i32)*) #2

declare i32 @uv_pipe_listen(%struct.uv_pipe_s*, i32, void (%struct.uv_stream_s*, i32)*) #2

; Function Attrs: nounwind uwtable
define i32 @uv__handle_type(i32 %fd) #0 !dbg !625 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %ss = alloca %struct.sockaddr_storage, align 8
  %sslen = alloca i32, align 4
  %len = alloca i32, align 4
  %type = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1521, metadata !699), !dbg !1522
  call void @llvm.dbg.declare(metadata %struct.sockaddr_storage* %ss, metadata !1523, metadata !699), !dbg !1532
  call void @llvm.dbg.declare(metadata i32* %sslen, metadata !1533, metadata !699), !dbg !1534
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1535, metadata !699), !dbg !1536
  call void @llvm.dbg.declare(metadata i32* %type, metadata !1537, metadata !699), !dbg !1538
  %0 = bitcast %struct.sockaddr_storage* %ss to i8*, !dbg !1539
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 128, i32 8, i1 false), !dbg !1539
  store i32 128, i32* %sslen, align 4, !dbg !1540
  %1 = load i32, i32* %fd.addr, align 4, !dbg !1541
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !1543
  %2 = bitcast %struct.sockaddr_storage* %ss to %struct.sockaddr*, !dbg !1543
  store %struct.sockaddr* %2, %struct.sockaddr** %__sockaddr__, align 8, !dbg !1543
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !1544
  %3 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !1544
  %call = call i32 @getsockname(i32 %1, %struct.sockaddr* %3, i32* %sslen) #8, !dbg !1544
  %tobool = icmp ne i32 %call, 0, !dbg !1544
  br i1 %tobool, label %if.then, label %if.end, !dbg !1545

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1546
  br label %return, !dbg !1546

if.end:                                           ; preds = %entry
  store i32 4, i32* %len, align 4, !dbg !1547
  %4 = load i32, i32* %fd.addr, align 4, !dbg !1548
  %5 = bitcast i32* %type to i8*, !dbg !1550
  %call1 = call i32 @getsockopt(i32 %4, i32 1, i32 3, i8* %5, i32* %len) #8, !dbg !1551
  %tobool2 = icmp ne i32 %call1, 0, !dbg !1551
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !1552

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1553
  br label %return, !dbg !1553

if.end4:                                          ; preds = %if.end
  %6 = load i32, i32* %type, align 4, !dbg !1554
  %cmp = icmp eq i32 %6, 1, !dbg !1556
  br i1 %cmp, label %if.then5, label %if.end7, !dbg !1557

if.then5:                                         ; preds = %if.end4
  %ss_family = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %ss, i32 0, i32 0, !dbg !1558
  %7 = load i16, i16* %ss_family, align 8, !dbg !1558
  %conv = zext i16 %7 to i32, !dbg !1560
  switch i32 %conv, label %sw.epilog [
    i32 1, label %sw.bb
    i32 2, label %sw.bb6
    i32 10, label %sw.bb6
  ], !dbg !1561

sw.bb:                                            ; preds = %if.then5
  store i32 7, i32* %retval, align 4, !dbg !1562
  br label %return, !dbg !1562

sw.bb6:                                           ; preds = %if.then5, %if.then5
  store i32 12, i32* %retval, align 4, !dbg !1564
  br label %return, !dbg !1564

sw.epilog:                                        ; preds = %if.then5
  br label %if.end7, !dbg !1565

if.end7:                                          ; preds = %sw.epilog, %if.end4
  %8 = load i32, i32* %type, align 4, !dbg !1566
  %cmp8 = icmp eq i32 %8, 2, !dbg !1568
  br i1 %cmp8, label %land.lhs.true, label %if.end19, !dbg !1569

land.lhs.true:                                    ; preds = %if.end7
  %ss_family10 = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %ss, i32 0, i32 0, !dbg !1570
  %9 = load i16, i16* %ss_family10, align 8, !dbg !1570
  %conv11 = zext i16 %9 to i32, !dbg !1571
  %cmp12 = icmp eq i32 %conv11, 2, !dbg !1572
  br i1 %cmp12, label %if.then18, label %lor.lhs.false, !dbg !1573

lor.lhs.false:                                    ; preds = %land.lhs.true
  %ss_family14 = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %ss, i32 0, i32 0, !dbg !1574
  %10 = load i16, i16* %ss_family14, align 8, !dbg !1574
  %conv15 = zext i16 %10 to i32, !dbg !1576
  %cmp16 = icmp eq i32 %conv15, 10, !dbg !1577
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !1578

if.then18:                                        ; preds = %lor.lhs.false, %land.lhs.true
  store i32 15, i32* %retval, align 4, !dbg !1580
  br label %return, !dbg !1580

if.end19:                                         ; preds = %lor.lhs.false, %if.end7
  store i32 0, i32* %retval, align 4, !dbg !1581
  br label %return, !dbg !1581

return:                                           ; preds = %if.end19, %if.then18, %sw.bb6, %sw.bb, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !1582
  ret i32 %11, !dbg !1582
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #6

; Function Attrs: nounwind
declare i32 @getsockopt(i32, i32, i32, i8*, i32*) #6

; Function Attrs: nounwind uwtable
define i32 @uv_shutdown(%struct.uv_shutdown_s* %req, %struct.uv_stream_s* %stream, void (%struct.uv_shutdown_s*, i32)* %cb) #0 !dbg !628 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_shutdown_s*, align 8
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %cb.addr = alloca void (%struct.uv_shutdown_s*, i32)*, align 8
  store %struct.uv_shutdown_s* %req, %struct.uv_shutdown_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_shutdown_s** %req.addr, metadata !1583, metadata !699), !dbg !1584
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !1585, metadata !699), !dbg !1586
  store void (%struct.uv_shutdown_s*, i32)* %cb, void (%struct.uv_shutdown_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_shutdown_s*, i32)** %cb.addr, metadata !1587, metadata !699), !dbg !1588
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1589
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 2, !dbg !1589
  %1 = load i32, i32* %type, align 8, !dbg !1589
  %cmp = icmp eq i32 %1, 12, !dbg !1589
  br i1 %cmp, label %land.lhs.true, label %lor.lhs.false, !dbg !1589

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1590
  %type1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 2, !dbg !1590
  %3 = load i32, i32* %type1, align 8, !dbg !1590
  %cmp2 = icmp eq i32 %3, 7, !dbg !1590
  br i1 %cmp2, label %land.lhs.true, label %cond.false, !dbg !1590

land.lhs.true:                                    ; preds = %lor.lhs.false, %entry
  br i1 true, label %cond.true, label %cond.false, !dbg !1592

cond.true:                                        ; preds = %land.lhs.true
  br label %cond.end, !dbg !1594

cond.false:                                       ; preds = %land.lhs.true, %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([118 x i8], [118 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1248, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_shutdown, i32 0, i32 0)) #7, !dbg !1596
  unreachable, !dbg !1596
                                                  ; No predecessors!
  br label %cond.end, !dbg !1598

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1600
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 7, !dbg !1602
  %6 = load i32, i32* %flags, align 8, !dbg !1602
  %and = and i32 %6, 64, !dbg !1603
  %tobool = icmp ne i32 %and, 0, !dbg !1603
  br i1 %tobool, label %lor.lhs.false3, label %if.then, !dbg !1604

lor.lhs.false3:                                   ; preds = %cond.end
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1605
  %flags4 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 7, !dbg !1606
  %8 = load i32, i32* %flags4, align 8, !dbg !1606
  %and5 = and i32 %8, 16, !dbg !1607
  %tobool6 = icmp ne i32 %and5, 0, !dbg !1607
  br i1 %tobool6, label %if.then, label %lor.lhs.false7, !dbg !1608

lor.lhs.false7:                                   ; preds = %lor.lhs.false3
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1609
  %flags8 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 7, !dbg !1610
  %10 = load i32, i32* %flags8, align 8, !dbg !1610
  %and9 = and i32 %10, 8, !dbg !1611
  %tobool10 = icmp ne i32 %and9, 0, !dbg !1611
  br i1 %tobool10, label %if.then, label %lor.lhs.false11, !dbg !1612

lor.lhs.false11:                                  ; preds = %lor.lhs.false7
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1613
  %flags12 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 7, !dbg !1613
  %12 = load i32, i32* %flags12, align 8, !dbg !1613
  %and13 = and i32 %12, 3, !dbg !1613
  %cmp14 = icmp ne i32 %and13, 0, !dbg !1613
  br i1 %cmp14, label %if.then, label %if.end, !dbg !1614

if.then:                                          ; preds = %lor.lhs.false11, %lor.lhs.false7, %lor.lhs.false3, %cond.end
  store i32 -107, i32* %retval, align 4, !dbg !1615
  br label %return, !dbg !1615

if.end:                                           ; preds = %lor.lhs.false11
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1617
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 13, !dbg !1617
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1617
  %14 = load i32, i32* %fd, align 8, !dbg !1617
  %cmp15 = icmp sge i32 %14, 0, !dbg !1617
  br i1 %cmp15, label %cond.true16, label %cond.false17, !dbg !1617

cond.true16:                                      ; preds = %if.end
  br label %cond.end18, !dbg !1618

cond.false17:                                     ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1257, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_shutdown, i32 0, i32 0)) #7, !dbg !1619
  unreachable, !dbg !1619
                                                  ; No predecessors!
  br label %cond.end18, !dbg !1620

cond.end18:                                       ; preds = %15, %cond.true16
  br label %do.body, !dbg !1621

do.body:                                          ; preds = %cond.end18
  br label %do.body19, !dbg !1622

do.body19:                                        ; preds = %do.body
  %16 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1625
  %type20 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %16, i32 0, i32 1, !dbg !1625
  store i32 4, i32* %type20, align 8, !dbg !1625
  br label %do.end, !dbg !1625

do.end:                                           ; preds = %do.body19
  br label %do.body21, !dbg !1628

do.body21:                                        ; preds = %do.end
  br label %do.body22, !dbg !1630

do.body22:                                        ; preds = %do.body21
  %17 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1633
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %17, i32 0, i32 1, !dbg !1633
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1633
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 3, !dbg !1633
  %19 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1633
  %active_queue = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %19, i32 0, i32 2, !dbg !1633
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1633
  %20 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1633
  store [2 x i8*]* %active_reqs, [2 x i8*]** %20, align 8, !dbg !1633
  %21 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1633
  %loop23 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %21, i32 0, i32 1, !dbg !1633
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop23, align 8, !dbg !1633
  %active_reqs24 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %22, i32 0, i32 3, !dbg !1633
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs24, i64 0, i64 1, !dbg !1633
  %23 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !1633
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !1633
  %25 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1633
  %active_queue26 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %25, i32 0, i32 2, !dbg !1633
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue26, i64 0, i64 1, !dbg !1633
  %26 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !1633
  store [2 x i8*]* %24, [2 x i8*]** %26, align 8, !dbg !1633
  %27 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1633
  %active_queue28 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %27, i32 0, i32 2, !dbg !1633
  %28 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1633
  %active_queue29 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %28, i32 0, i32 2, !dbg !1633
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue29, i64 0, i64 1, !dbg !1633
  %29 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !1633
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !1633
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %30, i64 0, i64 0, !dbg !1633
  %31 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !1633
  store [2 x i8*]* %active_queue28, [2 x i8*]** %31, align 8, !dbg !1633
  %32 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1633
  %active_queue32 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %32, i32 0, i32 2, !dbg !1633
  %33 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1633
  %loop33 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %33, i32 0, i32 1, !dbg !1633
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop33, align 8, !dbg !1633
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 3, !dbg !1633
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs34, i64 0, i64 1, !dbg !1633
  %35 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !1633
  store [2 x i8*]* %active_queue32, [2 x i8*]** %35, align 8, !dbg !1633
  br label %do.end36, !dbg !1633

do.end36:                                         ; preds = %do.body22
  br label %do.end37, !dbg !1636

do.end37:                                         ; preds = %do.end36
  br label %do.end38, !dbg !1638

do.end38:                                         ; preds = %do.end37
  %36 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1640
  %37 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1641
  %handle = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %37, i32 0, i32 4, !dbg !1642
  store %struct.uv_stream_s* %36, %struct.uv_stream_s** %handle, align 8, !dbg !1643
  %38 = load void (%struct.uv_shutdown_s*, i32)*, void (%struct.uv_shutdown_s*, i32)** %cb.addr, align 8, !dbg !1644
  %39 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1645
  %cb39 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %39, i32 0, i32 5, !dbg !1646
  store void (%struct.uv_shutdown_s*, i32)* %38, void (%struct.uv_shutdown_s*, i32)** %cb39, align 8, !dbg !1647
  %40 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req.addr, align 8, !dbg !1648
  %41 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1649
  %shutdown_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %41, i32 0, i32 12, !dbg !1650
  store %struct.uv_shutdown_s* %40, %struct.uv_shutdown_s** %shutdown_req, align 8, !dbg !1651
  %42 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1652
  %flags40 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %42, i32 0, i32 7, !dbg !1653
  %43 = load i32, i32* %flags40, align 8, !dbg !1654
  %or = or i32 %43, 8, !dbg !1654
  store i32 %or, i32* %flags40, align 8, !dbg !1654
  %44 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1655
  %loop41 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %44, i32 0, i32 1, !dbg !1656
  %45 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop41, align 8, !dbg !1656
  %46 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1657
  %io_watcher42 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %46, i32 0, i32 13, !dbg !1658
  call void @uv__io_start(%struct.uv_loop_s* %45, %struct.uv__io_s* %io_watcher42, i32 4), !dbg !1659
  %47 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1660
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %47), !dbg !1661
  store i32 0, i32* %retval, align 4, !dbg !1662
  br label %return, !dbg !1662

return:                                           ; preds = %do.end38, %if.then
  %48 = load i32, i32* %retval, align 4, !dbg !1663
  ret i32 %48, !dbg !1663
}

; Function Attrs: nounwind uwtable
define internal void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %stream) #0 !dbg !661 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !1664, metadata !699), !dbg !1665
  ret void, !dbg !1666
}

; Function Attrs: nounwind uwtable
define i32 @uv_write2(%struct.uv_write_s* %req, %struct.uv_stream_s* %stream, %struct.uv_buf_t* %bufs, i32 %nbufs, %struct.uv_stream_s* %send_handle, void (%struct.uv_write_s*, i32)* %cb) #0 !dbg !631 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_write_s*, align 8
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %send_handle.addr = alloca %struct.uv_stream_s*, align 8
  %cb.addr = alloca void (%struct.uv_write_s*, i32)*, align 8
  %empty_queue = alloca i32, align 4
  store %struct.uv_write_s* %req, %struct.uv_write_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req.addr, metadata !1667, metadata !699), !dbg !1668
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !1669, metadata !699), !dbg !1670
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !1671, metadata !699), !dbg !1672
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !1673, metadata !699), !dbg !1674
  store %struct.uv_stream_s* %send_handle, %struct.uv_stream_s** %send_handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %send_handle.addr, metadata !1675, metadata !699), !dbg !1676
  store void (%struct.uv_write_s*, i32)* %cb, void (%struct.uv_write_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_write_s*, i32)** %cb.addr, metadata !1677, metadata !699), !dbg !1678
  call void @llvm.dbg.declare(metadata i32* %empty_queue, metadata !1679, metadata !699), !dbg !1680
  %0 = load i32, i32* %nbufs.addr, align 4, !dbg !1681
  %cmp = icmp ugt i32 %0, 0, !dbg !1681
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1681

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1682

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1387, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @__PRETTY_FUNCTION__.uv_write2, i32 0, i32 0)) #7, !dbg !1684
  unreachable, !dbg !1684
                                                  ; No predecessors!
  br label %cond.end, !dbg !1686

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1688
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 2, !dbg !1688
  %3 = load i32, i32* %type, align 8, !dbg !1688
  %cmp1 = icmp eq i32 %3, 12, !dbg !1688
  br i1 %cmp1, label %land.lhs.true, label %lor.lhs.false, !dbg !1688

lor.lhs.false:                                    ; preds = %cond.end
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1689
  %type2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 2, !dbg !1689
  %5 = load i32, i32* %type2, align 8, !dbg !1689
  %cmp3 = icmp eq i32 %5, 7, !dbg !1689
  br i1 %cmp3, label %land.lhs.true, label %lor.lhs.false4, !dbg !1689

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %6 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1690
  %type5 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %6, i32 0, i32 2, !dbg !1690
  %7 = load i32, i32* %type5, align 8, !dbg !1690
  %cmp6 = icmp eq i32 %7, 14, !dbg !1690
  br i1 %cmp6, label %land.lhs.true, label %cond.false8, !dbg !1690

land.lhs.true:                                    ; preds = %lor.lhs.false4, %lor.lhs.false, %cond.end
  br i1 true, label %cond.true7, label %cond.false8, !dbg !1691

cond.true7:                                       ; preds = %land.lhs.true
  br label %cond.end9, !dbg !1692

cond.false8:                                      ; preds = %land.lhs.true, %lor.lhs.false4
  call void @__assert_fail(i8* getelementptr inbounds ([149 x i8], [149 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1391, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @__PRETTY_FUNCTION__.uv_write2, i32 0, i32 0)) #7, !dbg !1694
  unreachable, !dbg !1694
                                                  ; No predecessors!
  br label %cond.end9, !dbg !1696

cond.end9:                                        ; preds = %8, %cond.true7
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1698
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 13, !dbg !1698
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1698
  %10 = load i32, i32* %fd, align 8, !dbg !1698
  %cmp10 = icmp slt i32 %10, 0, !dbg !1700
  br i1 %cmp10, label %if.then, label %if.end, !dbg !1701

if.then:                                          ; preds = %cond.end9
  store i32 -9, i32* %retval, align 4, !dbg !1702
  br label %return, !dbg !1702

if.end:                                           ; preds = %cond.end9
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %send_handle.addr, align 8, !dbg !1703
  %tobool = icmp ne %struct.uv_stream_s* %11, null, !dbg !1703
  br i1 %tobool, label %if.then11, label %if.end21, !dbg !1705

if.then11:                                        ; preds = %if.end
  %12 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1706
  %type12 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %12, i32 0, i32 2, !dbg !1709
  %13 = load i32, i32* %type12, align 8, !dbg !1709
  %cmp13 = icmp ne i32 %13, 7, !dbg !1710
  br i1 %cmp13, label %if.then16, label %lor.lhs.false14, !dbg !1711

lor.lhs.false14:                                  ; preds = %if.then11
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1712
  %15 = bitcast %struct.uv_stream_s* %14 to %struct.uv_pipe_s*, !dbg !1714
  %ipc = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %15, i32 0, i32 20, !dbg !1714
  %16 = load i32, i32* %ipc, align 8, !dbg !1714
  %tobool15 = icmp ne i32 %16, 0, !dbg !1715
  br i1 %tobool15, label %if.end17, label %if.then16, !dbg !1716

if.then16:                                        ; preds = %lor.lhs.false14, %if.then11
  store i32 -22, i32* %retval, align 4, !dbg !1717
  br label %return, !dbg !1717

if.end17:                                         ; preds = %lor.lhs.false14
  %17 = load %struct.uv_stream_s*, %struct.uv_stream_s** %send_handle.addr, align 8, !dbg !1718
  %18 = bitcast %struct.uv_stream_s* %17 to %struct.uv_handle_s*, !dbg !1720
  %call = call i32 @uv__handle_fd(%struct.uv_handle_s* %18), !dbg !1721
  %cmp18 = icmp slt i32 %call, 0, !dbg !1722
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !1723

if.then19:                                        ; preds = %if.end17
  store i32 -9, i32* %retval, align 4, !dbg !1724
  br label %return, !dbg !1724

if.end20:                                         ; preds = %if.end17
  br label %if.end21, !dbg !1725

if.end21:                                         ; preds = %if.end20, %if.end
  %19 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1726
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %19, i32 0, i32 8, !dbg !1727
  %20 = load i64, i64* %write_queue_size, align 8, !dbg !1727
  %cmp22 = icmp eq i64 %20, 0, !dbg !1728
  %conv = zext i1 %cmp22 to i32, !dbg !1728
  store i32 %conv, i32* %empty_queue, align 4, !dbg !1729
  br label %do.body, !dbg !1730

do.body:                                          ; preds = %if.end21
  br label %do.body23, !dbg !1731

do.body23:                                        ; preds = %do.body
  %21 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1734
  %type24 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %21, i32 0, i32 1, !dbg !1734
  store i32 3, i32* %type24, align 8, !dbg !1734
  br label %do.end, !dbg !1734

do.end:                                           ; preds = %do.body23
  br label %do.body25, !dbg !1737

do.body25:                                        ; preds = %do.end
  br label %do.body26, !dbg !1739

do.body26:                                        ; preds = %do.body25
  %22 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1742
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %22, i32 0, i32 1, !dbg !1742
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1742
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 3, !dbg !1742
  %24 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1742
  %active_queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %24, i32 0, i32 2, !dbg !1742
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1742
  %25 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1742
  store [2 x i8*]* %active_reqs, [2 x i8*]** %25, align 8, !dbg !1742
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1742
  %loop27 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %26, i32 0, i32 1, !dbg !1742
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop27, align 8, !dbg !1742
  %active_reqs28 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 3, !dbg !1742
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs28, i64 0, i64 1, !dbg !1742
  %28 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !1742
  %29 = load [2 x i8*]*, [2 x i8*]** %28, align 8, !dbg !1742
  %30 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1742
  %active_queue30 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %30, i32 0, i32 2, !dbg !1742
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue30, i64 0, i64 1, !dbg !1742
  %31 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !1742
  store [2 x i8*]* %29, [2 x i8*]** %31, align 8, !dbg !1742
  %32 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1742
  %active_queue32 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %32, i32 0, i32 2, !dbg !1742
  %33 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1742
  %active_queue33 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %33, i32 0, i32 2, !dbg !1742
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue33, i64 0, i64 1, !dbg !1742
  %34 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !1742
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !1742
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %35, i64 0, i64 0, !dbg !1742
  %36 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !1742
  store [2 x i8*]* %active_queue32, [2 x i8*]** %36, align 8, !dbg !1742
  %37 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1742
  %active_queue36 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %37, i32 0, i32 2, !dbg !1742
  %38 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1742
  %loop37 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %38, i32 0, i32 1, !dbg !1742
  %39 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop37, align 8, !dbg !1742
  %active_reqs38 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %39, i32 0, i32 3, !dbg !1742
  %arrayidx39 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs38, i64 0, i64 1, !dbg !1742
  %40 = bitcast i8** %arrayidx39 to [2 x i8*]**, !dbg !1742
  store [2 x i8*]* %active_queue36, [2 x i8*]** %40, align 8, !dbg !1742
  br label %do.end40, !dbg !1742

do.end40:                                         ; preds = %do.body26
  br label %do.end41, !dbg !1745

do.end41:                                         ; preds = %do.end40
  br label %do.end42, !dbg !1747

do.end42:                                         ; preds = %do.end41
  %41 = load void (%struct.uv_write_s*, i32)*, void (%struct.uv_write_s*, i32)** %cb.addr, align 8, !dbg !1749
  %42 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1750
  %cb43 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %42, i32 0, i32 4, !dbg !1751
  store void (%struct.uv_write_s*, i32)* %41, void (%struct.uv_write_s*, i32)** %cb43, align 8, !dbg !1752
  %43 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1753
  %44 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1754
  %handle = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %44, i32 0, i32 6, !dbg !1755
  store %struct.uv_stream_s* %43, %struct.uv_stream_s** %handle, align 8, !dbg !1756
  %45 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1757
  %error = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %45, i32 0, i32 11, !dbg !1758
  store i32 0, i32* %error, align 4, !dbg !1759
  %46 = load %struct.uv_stream_s*, %struct.uv_stream_s** %send_handle.addr, align 8, !dbg !1760
  %47 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1761
  %send_handle44 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %47, i32 0, i32 5, !dbg !1762
  store %struct.uv_stream_s* %46, %struct.uv_stream_s** %send_handle44, align 8, !dbg !1763
  br label %do.body45, !dbg !1764

do.body45:                                        ; preds = %do.end42
  %48 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1765
  %queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %48, i32 0, i32 7, !dbg !1765
  %49 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1765
  %queue46 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %49, i32 0, i32 7, !dbg !1765
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue46, i64 0, i64 0, !dbg !1765
  %50 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1765
  store [2 x i8*]* %queue, [2 x i8*]** %50, align 8, !dbg !1765
  %51 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1765
  %queue48 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %51, i32 0, i32 7, !dbg !1765
  %52 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1765
  %queue49 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %52, i32 0, i32 7, !dbg !1765
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue49, i64 0, i64 1, !dbg !1765
  %53 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1765
  store [2 x i8*]* %queue48, [2 x i8*]** %53, align 8, !dbg !1765
  br label %do.end51, !dbg !1765

do.end51:                                         ; preds = %do.body45
  %54 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1768
  %bufsml = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %54, i32 0, i32 12, !dbg !1769
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !1768
  %55 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1770
  %bufs52 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %55, i32 0, i32 9, !dbg !1771
  store %struct.uv_buf_t* %arraydecay, %struct.uv_buf_t** %bufs52, align 8, !dbg !1772
  %56 = load i32, i32* %nbufs.addr, align 4, !dbg !1773
  %conv53 = zext i32 %56 to i64, !dbg !1773
  %cmp54 = icmp ugt i64 %conv53, 4, !dbg !1775
  br i1 %cmp54, label %if.then56, label %if.end60, !dbg !1776

if.then56:                                        ; preds = %do.end51
  %57 = load i32, i32* %nbufs.addr, align 4, !dbg !1777
  %conv57 = zext i32 %57 to i64, !dbg !1777
  %mul = mul i64 %conv57, 16, !dbg !1778
  %call58 = call i8* @uv__malloc(i64 %mul), !dbg !1779
  %58 = bitcast i8* %call58 to %struct.uv_buf_t*, !dbg !1779
  %59 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1780
  %bufs59 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %59, i32 0, i32 9, !dbg !1781
  store %struct.uv_buf_t* %58, %struct.uv_buf_t** %bufs59, align 8, !dbg !1782
  br label %if.end60, !dbg !1780

if.end60:                                         ; preds = %if.then56, %do.end51
  %60 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1783
  %bufs61 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %60, i32 0, i32 9, !dbg !1785
  %61 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs61, align 8, !dbg !1785
  %cmp62 = icmp eq %struct.uv_buf_t* %61, null, !dbg !1786
  br i1 %cmp62, label %if.then64, label %if.end65, !dbg !1787

if.then64:                                        ; preds = %if.end60
  store i32 -12, i32* %retval, align 4, !dbg !1788
  br label %return, !dbg !1788

if.end65:                                         ; preds = %if.end60
  %62 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1789
  %bufs66 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %62, i32 0, i32 9, !dbg !1790
  %63 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs66, align 8, !dbg !1790
  %64 = bitcast %struct.uv_buf_t* %63 to i8*, !dbg !1791
  %65 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1792
  %66 = bitcast %struct.uv_buf_t* %65 to i8*, !dbg !1791
  %67 = load i32, i32* %nbufs.addr, align 4, !dbg !1793
  %conv67 = zext i32 %67 to i64, !dbg !1793
  %mul68 = mul i64 %conv67, 16, !dbg !1794
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %66, i64 %mul68, i32 8, i1 false), !dbg !1791
  %68 = load i32, i32* %nbufs.addr, align 4, !dbg !1795
  %69 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1796
  %nbufs69 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %69, i32 0, i32 10, !dbg !1797
  store i32 %68, i32* %nbufs69, align 8, !dbg !1798
  %70 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1799
  %write_index = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %70, i32 0, i32 8, !dbg !1800
  store i32 0, i32* %write_index, align 8, !dbg !1801
  %71 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1802
  %72 = load i32, i32* %nbufs.addr, align 4, !dbg !1803
  %call70 = call i64 @uv__count_bufs(%struct.uv_buf_t* %71, i32 %72), !dbg !1804
  %73 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1805
  %write_queue_size71 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %73, i32 0, i32 8, !dbg !1806
  %74 = load i64, i64* %write_queue_size71, align 8, !dbg !1807
  %add = add i64 %74, %call70, !dbg !1807
  store i64 %add, i64* %write_queue_size71, align 8, !dbg !1807
  br label %do.body72, !dbg !1808

do.body72:                                        ; preds = %if.end65
  %75 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1809
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %75, i32 0, i32 14, !dbg !1809
  %76 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1809
  %queue73 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %76, i32 0, i32 7, !dbg !1809
  %arrayidx74 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue73, i64 0, i64 0, !dbg !1809
  %77 = bitcast i8** %arrayidx74 to [2 x i8*]**, !dbg !1809
  store [2 x i8*]* %write_queue, [2 x i8*]** %77, align 8, !dbg !1809
  %78 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1809
  %write_queue75 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %78, i32 0, i32 14, !dbg !1809
  %arrayidx76 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue75, i64 0, i64 1, !dbg !1809
  %79 = bitcast i8** %arrayidx76 to [2 x i8*]**, !dbg !1809
  %80 = load [2 x i8*]*, [2 x i8*]** %79, align 8, !dbg !1809
  %81 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1809
  %queue77 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %81, i32 0, i32 7, !dbg !1809
  %arrayidx78 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue77, i64 0, i64 1, !dbg !1809
  %82 = bitcast i8** %arrayidx78 to [2 x i8*]**, !dbg !1809
  store [2 x i8*]* %80, [2 x i8*]** %82, align 8, !dbg !1809
  %83 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1809
  %queue79 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %83, i32 0, i32 7, !dbg !1809
  %84 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1809
  %queue80 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %84, i32 0, i32 7, !dbg !1809
  %arrayidx81 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue80, i64 0, i64 1, !dbg !1809
  %85 = bitcast i8** %arrayidx81 to [2 x i8*]**, !dbg !1809
  %86 = load [2 x i8*]*, [2 x i8*]** %85, align 8, !dbg !1809
  %arrayidx82 = getelementptr inbounds [2 x i8*], [2 x i8*]* %86, i64 0, i64 0, !dbg !1809
  %87 = bitcast i8** %arrayidx82 to [2 x i8*]**, !dbg !1809
  store [2 x i8*]* %queue79, [2 x i8*]** %87, align 8, !dbg !1809
  %88 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !1809
  %queue83 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %88, i32 0, i32 7, !dbg !1809
  %89 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1809
  %write_queue84 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %89, i32 0, i32 14, !dbg !1809
  %arrayidx85 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue84, i64 0, i64 1, !dbg !1809
  %90 = bitcast i8** %arrayidx85 to [2 x i8*]**, !dbg !1809
  store [2 x i8*]* %queue83, [2 x i8*]** %90, align 8, !dbg !1809
  br label %do.end86, !dbg !1809

do.end86:                                         ; preds = %do.body72
  %91 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1812
  %connect_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %91, i32 0, i32 11, !dbg !1814
  %92 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req, align 8, !dbg !1814
  %tobool87 = icmp ne %struct.uv_connect_s* %92, null, !dbg !1812
  br i1 %tobool87, label %if.then88, label %if.else, !dbg !1815

if.then88:                                        ; preds = %do.end86
  br label %if.end99, !dbg !1816

if.else:                                          ; preds = %do.end86
  %93 = load i32, i32* %empty_queue, align 4, !dbg !1818
  %tobool89 = icmp ne i32 %93, 0, !dbg !1818
  br i1 %tobool89, label %if.then90, label %if.else91, !dbg !1820

if.then90:                                        ; preds = %if.else
  %94 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1821
  call void @uv__write(%struct.uv_stream_s* %94), !dbg !1823
  br label %if.end98, !dbg !1824

if.else91:                                        ; preds = %if.else
  %95 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1825
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %95, i32 0, i32 7, !dbg !1825
  %96 = load i32, i32* %flags, align 8, !dbg !1825
  %and = and i32 %96, 128, !dbg !1825
  %tobool92 = icmp ne i32 %and, 0, !dbg !1825
  br i1 %tobool92, label %cond.false94, label %cond.true93, !dbg !1825

cond.true93:                                      ; preds = %if.else91
  br label %cond.end95, !dbg !1827

cond.false94:                                     ; preds = %if.else91
  call void @__assert_fail(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1457, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @__PRETTY_FUNCTION__.uv_write2, i32 0, i32 0)) #7, !dbg !1829
  unreachable, !dbg !1829
                                                  ; No predecessors!
  br label %cond.end95, !dbg !1831

cond.end95:                                       ; preds = %97, %cond.true93
  %98 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1833
  %loop96 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %98, i32 0, i32 1, !dbg !1834
  %99 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop96, align 8, !dbg !1834
  %100 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1835
  %io_watcher97 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %100, i32 0, i32 13, !dbg !1836
  call void @uv__io_start(%struct.uv_loop_s* %99, %struct.uv__io_s* %io_watcher97, i32 4), !dbg !1837
  %101 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1838
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %101), !dbg !1839
  br label %if.end98

if.end98:                                         ; preds = %cond.end95, %if.then90
  br label %if.end99

if.end99:                                         ; preds = %if.end98, %if.then88
  store i32 0, i32* %retval, align 4, !dbg !1840
  br label %return, !dbg !1840

return:                                           ; preds = %if.end99, %if.then64, %if.then19, %if.then16, %if.then
  %102 = load i32, i32* %retval, align 4, !dbg !1841
  ret i32 %102, !dbg !1841
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__handle_fd(%struct.uv_handle_s* %handle) #0 !dbg !685 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !1842, metadata !699), !dbg !1843
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1844
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %0, i32 0, i32 2, !dbg !1845
  %1 = load i32, i32* %type, align 8, !dbg !1845
  switch i32 %1, label %sw.default [
    i32 7, label %sw.bb
    i32 12, label %sw.bb
    i32 15, label %sw.bb1
  ], !dbg !1846

sw.bb:                                            ; preds = %entry, %entry
  %2 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1847
  %3 = bitcast %struct.uv_handle_s* %2 to %struct.uv_stream_s*, !dbg !1849
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %3, i32 0, i32 13, !dbg !1849
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1850
  %4 = load i32, i32* %fd, align 8, !dbg !1850
  store i32 %4, i32* %retval, align 4, !dbg !1851
  br label %return, !dbg !1851

sw.bb1:                                           ; preds = %entry
  %5 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !1852
  %6 = bitcast %struct.uv_handle_s* %5 to %struct.uv_udp_s*, !dbg !1853
  %io_watcher2 = getelementptr inbounds %struct.uv_udp_s, %struct.uv_udp_s* %6, i32 0, i32 12, !dbg !1853
  %fd3 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher2, i32 0, i32 5, !dbg !1854
  %7 = load i32, i32* %fd3, align 8, !dbg !1854
  store i32 %7, i32* %retval, align 4, !dbg !1855
  br label %return, !dbg !1855

sw.default:                                       ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !1856
  br label %return, !dbg !1856

return:                                           ; preds = %sw.default, %sw.bb1, %sw.bb
  %8 = load i32, i32* %retval, align 4, !dbg !1857
  ret i32 %8, !dbg !1857
}

declare i8* @uv__malloc(i64) #2

declare i64 @uv__count_bufs(%struct.uv_buf_t*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__write(%struct.uv_stream_s* %stream) #0 !dbg !688 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %iov = alloca %struct.iovec*, align 8
  %q = alloca [2 x i8*]*, align 8
  %req = alloca %struct.uv_write_s*, align 8
  %iovmax = alloca i32, align 4
  %iovcnt = alloca i32, align 4
  %n = alloca i64, align 8
  %msg = alloca %struct.msghdr, align 8
  %cmsg = alloca %struct.cmsghdr*, align 8
  %fd_to_send = alloca i32, align 4
  %scratch = alloca %union.anon.9, align 8
  %pv = alloca i8*, align 8
  %pi = alloca i32*, align 8
  %buf = alloca %struct.uv_buf_t*, align 8
  %len = alloca i64, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !1858, metadata !699), !dbg !1859
  call void @llvm.dbg.declare(metadata %struct.iovec** %iov, metadata !1860, metadata !699), !dbg !1861
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1862, metadata !699), !dbg !1863
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req, metadata !1864, metadata !699), !dbg !1865
  call void @llvm.dbg.declare(metadata i32* %iovmax, metadata !1866, metadata !699), !dbg !1867
  call void @llvm.dbg.declare(metadata i32* %iovcnt, metadata !1868, metadata !699), !dbg !1869
  call void @llvm.dbg.declare(metadata i64* %n, metadata !1870, metadata !699), !dbg !1871
  br label %start, !dbg !1872

start:                                            ; preds = %if.then136, %if.then108, %entry
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1873
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 13, !dbg !1873
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1873
  %1 = load i32, i32* %fd, align 8, !dbg !1873
  %cmp = icmp sge i32 %1, 0, !dbg !1873
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1873

cond.true:                                        ; preds = %start
  br label %cond.end, !dbg !1874

cond.false:                                       ; preds = %start
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 756, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !1876
  unreachable, !dbg !1876
                                                  ; No predecessors!
  br label %cond.end, !dbg !1878

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1880
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %3, i32 0, i32 14, !dbg !1880
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1880
  %write_queue1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 14, !dbg !1880
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue1, i64 0, i64 0, !dbg !1880
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1880
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !1880
  %cmp2 = icmp eq [2 x i8*]* %write_queue, %6, !dbg !1880
  br i1 %cmp2, label %if.then, label %if.end, !dbg !1882

if.then:                                          ; preds = %cond.end
  br label %return, !dbg !1883

if.end:                                           ; preds = %cond.end
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1884
  %write_queue3 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 14, !dbg !1884
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue3, i64 0, i64 0, !dbg !1884
  %8 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !1884
  %9 = load [2 x i8*]*, [2 x i8*]** %8, align 8, !dbg !1884
  store [2 x i8*]* %9, [2 x i8*]** %q, align 8, !dbg !1885
  %10 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1886
  %11 = bitcast [2 x i8*]* %10 to i8*, !dbg !1886
  %add.ptr = getelementptr inbounds i8, i8* %11, i64 -88, !dbg !1886
  %12 = bitcast i8* %add.ptr to %struct.uv_write_s*, !dbg !1886
  store %struct.uv_write_s* %12, %struct.uv_write_s** %req, align 8, !dbg !1887
  %13 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1888
  %handle = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %13, i32 0, i32 6, !dbg !1888
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle, align 8, !dbg !1888
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1888
  %cmp5 = icmp eq %struct.uv_stream_s* %14, %15, !dbg !1888
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !1888

cond.true6:                                       ; preds = %if.end
  br label %cond.end8, !dbg !1889

cond.false7:                                      ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.34, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 763, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !1890
  unreachable, !dbg !1890
                                                  ; No predecessors!
  br label %cond.end8, !dbg !1891

cond.end8:                                        ; preds = %16, %cond.true6
  %17 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1892
  %write_index = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %17, i32 0, i32 8, !dbg !1893
  %18 = load i32, i32* %write_index, align 8, !dbg !1893
  %idxprom = zext i32 %18 to i64, !dbg !1894
  %19 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1894
  %bufs = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %19, i32 0, i32 9, !dbg !1895
  %20 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !1895
  %arrayidx9 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %20, i64 %idxprom, !dbg !1894
  %21 = bitcast %struct.uv_buf_t* %arrayidx9 to %struct.iovec*, !dbg !1896
  store %struct.iovec* %21, %struct.iovec** %iov, align 8, !dbg !1897
  %22 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1898
  %nbufs = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %22, i32 0, i32 10, !dbg !1899
  %23 = load i32, i32* %nbufs, align 8, !dbg !1899
  %24 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1900
  %write_index10 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %24, i32 0, i32 8, !dbg !1901
  %25 = load i32, i32* %write_index10, align 8, !dbg !1901
  %sub = sub i32 %23, %25, !dbg !1902
  store i32 %sub, i32* %iovcnt, align 4, !dbg !1903
  %call = call i32 @uv__getiovmax(), !dbg !1904
  store i32 %call, i32* %iovmax, align 4, !dbg !1905
  %26 = load i32, i32* %iovcnt, align 4, !dbg !1906
  %27 = load i32, i32* %iovmax, align 4, !dbg !1908
  %cmp11 = icmp sgt i32 %26, %27, !dbg !1909
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1910

if.then12:                                        ; preds = %cond.end8
  %28 = load i32, i32* %iovmax, align 4, !dbg !1911
  store i32 %28, i32* %iovcnt, align 4, !dbg !1912
  br label %if.end13, !dbg !1913

if.end13:                                         ; preds = %if.then12, %cond.end8
  %29 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1914
  %send_handle = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %29, i32 0, i32 5, !dbg !1916
  %30 = load %struct.uv_stream_s*, %struct.uv_stream_s** %send_handle, align 8, !dbg !1916
  %tobool = icmp ne %struct.uv_stream_s* %30, null, !dbg !1914
  br i1 %tobool, label %if.then14, label %if.else, !dbg !1917

if.then14:                                        ; preds = %if.end13
  call void @llvm.dbg.declare(metadata %struct.msghdr* %msg, metadata !1918, metadata !699), !dbg !1920
  call void @llvm.dbg.declare(metadata %struct.cmsghdr** %cmsg, metadata !1921, metadata !699), !dbg !1922
  call void @llvm.dbg.declare(metadata i32* %fd_to_send, metadata !1923, metadata !699), !dbg !1924
  %31 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !1925
  %send_handle15 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %31, i32 0, i32 5, !dbg !1926
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %send_handle15, align 8, !dbg !1926
  %33 = bitcast %struct.uv_stream_s* %32 to %struct.uv_handle_s*, !dbg !1927
  %call16 = call i32 @uv__handle_fd(%struct.uv_handle_s* %33), !dbg !1928
  store i32 %call16, i32* %fd_to_send, align 4, !dbg !1924
  call void @llvm.dbg.declare(metadata %union.anon.9* %scratch, metadata !1929, metadata !699), !dbg !1937
  %34 = bitcast %union.anon.9* %scratch to i8*, !dbg !1938
  call void @llvm.memset.p0i8.i64(i8* %34, i8 0, i64 64, i32 8, i1 false), !dbg !1938
  %35 = load i32, i32* %fd_to_send, align 4, !dbg !1939
  %cmp17 = icmp sge i32 %35, 0, !dbg !1939
  br i1 %cmp17, label %cond.true18, label %cond.false19, !dbg !1939

cond.true18:                                      ; preds = %if.then14
  br label %cond.end20, !dbg !1940

cond.false19:                                     ; preds = %if.then14
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.35, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 795, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !1942
  unreachable, !dbg !1942
                                                  ; No predecessors!
  br label %cond.end20, !dbg !1944

cond.end20:                                       ; preds = %36, %cond.true18
  %msg_name = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 0, !dbg !1946
  store i8* null, i8** %msg_name, align 8, !dbg !1947
  %msg_namelen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 1, !dbg !1948
  store i32 0, i32* %msg_namelen, align 8, !dbg !1949
  %37 = load %struct.iovec*, %struct.iovec** %iov, align 8, !dbg !1950
  %msg_iov = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 2, !dbg !1951
  store %struct.iovec* %37, %struct.iovec** %msg_iov, align 8, !dbg !1952
  %38 = load i32, i32* %iovcnt, align 4, !dbg !1953
  %conv = sext i32 %38 to i64, !dbg !1953
  %msg_iovlen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 3, !dbg !1954
  store i64 %conv, i64* %msg_iovlen, align 8, !dbg !1955
  %msg_flags = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 6, !dbg !1956
  store i32 0, i32* %msg_flags, align 8, !dbg !1957
  %alias = bitcast %union.anon.9* %scratch to %struct.cmsghdr*, !dbg !1958
  %39 = bitcast %struct.cmsghdr* %alias to i8*, !dbg !1959
  %msg_control = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 4, !dbg !1960
  store i8* %39, i8** %msg_control, align 8, !dbg !1961
  %msg_controllen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 5, !dbg !1962
  store i64 24, i64* %msg_controllen, align 8, !dbg !1963
  %msg_controllen21 = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 5, !dbg !1964
  %40 = load i64, i64* %msg_controllen21, align 8, !dbg !1964
  %cmp22 = icmp uge i64 %40, 16, !dbg !1964
  br i1 %cmp22, label %cond.true24, label %cond.false26, !dbg !1964

cond.true24:                                      ; preds = %cond.end20
  %msg_control25 = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 4, !dbg !1965
  %41 = load i8*, i8** %msg_control25, align 8, !dbg !1965
  %42 = bitcast i8* %41 to %struct.cmsghdr*, !dbg !1965
  br label %cond.end27, !dbg !1965

cond.false26:                                     ; preds = %cond.end20
  br label %cond.end27, !dbg !1966

cond.end27:                                       ; preds = %cond.false26, %cond.true24
  %cond = phi %struct.cmsghdr* [ %42, %cond.true24 ], [ null, %cond.false26 ], !dbg !1967
  store %struct.cmsghdr* %cond, %struct.cmsghdr** %cmsg, align 8, !dbg !1968
  %43 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !1969
  %cmsg_level = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %43, i32 0, i32 1, !dbg !1970
  store i32 1, i32* %cmsg_level, align 8, !dbg !1971
  %44 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !1972
  %cmsg_type = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %44, i32 0, i32 2, !dbg !1973
  store i32 1, i32* %cmsg_type, align 4, !dbg !1974
  %45 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !1975
  %cmsg_len = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %45, i32 0, i32 0, !dbg !1976
  store i64 20, i64* %cmsg_len, align 8, !dbg !1977
  call void @llvm.dbg.declare(metadata i8** %pv, metadata !1978, metadata !699), !dbg !1980
  %46 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !1981
  %__cmsg_data = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %46, i32 0, i32 3, !dbg !1981
  %arraydecay = getelementptr inbounds [0 x i8], [0 x i8]* %__cmsg_data, i32 0, i32 0, !dbg !1981
  store i8* %arraydecay, i8** %pv, align 8, !dbg !1980
  call void @llvm.dbg.declare(metadata i32** %pi, metadata !1982, metadata !699), !dbg !1984
  %47 = load i8*, i8** %pv, align 8, !dbg !1985
  %48 = bitcast i8* %47 to i32*, !dbg !1985
  store i32* %48, i32** %pi, align 8, !dbg !1984
  %49 = load i32, i32* %fd_to_send, align 4, !dbg !1986
  %50 = load i32*, i32** %pi, align 8, !dbg !1987
  store i32 %49, i32* %50, align 4, !dbg !1988
  br label %do.body, !dbg !1989

do.body:                                          ; preds = %land.end, %cond.end27
  %51 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !1990
  %io_watcher28 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %51, i32 0, i32 13, !dbg !1990
  %fd29 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher28, i32 0, i32 5, !dbg !1990
  %52 = load i32, i32* %fd29, align 8, !dbg !1990
  %call30 = call i64 @sendmsg(i32 %52, %struct.msghdr* %msg, i32 0), !dbg !1992
  store i64 %call30, i64* %n, align 8, !dbg !1993
  br label %do.cond, !dbg !1994

do.cond:                                          ; preds = %do.body
  %53 = load i64, i64* %n, align 8, !dbg !1995
  %cmp31 = icmp eq i64 %53, -1, !dbg !1996
  br i1 %cmp31, label %land.rhs, label %land.end, !dbg !1997

land.rhs:                                         ; preds = %do.cond
  %call33 = call i32* @__errno_location() #1, !dbg !1998
  %54 = load i32, i32* %call33, align 4, !dbg !1998
  %cmp34 = icmp eq i32 %54, 4, !dbg !1999
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %55 = phi i1 [ false, %do.cond ], [ %cmp34, %land.rhs ]
  br i1 %55, label %do.body, label %do.end, !dbg !2000

do.end:                                           ; preds = %land.end
  br label %if.end59, !dbg !2002

if.else:                                          ; preds = %if.end13
  br label %do.body36, !dbg !2003

do.body36:                                        ; preds = %land.end57, %if.else
  %56 = load i32, i32* %iovcnt, align 4, !dbg !2005
  %cmp37 = icmp eq i32 %56, 1, !dbg !2008
  br i1 %cmp37, label %if.then39, label %if.else45, !dbg !2009

if.then39:                                        ; preds = %do.body36
  %57 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2010
  %io_watcher40 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %57, i32 0, i32 13, !dbg !2010
  %fd41 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher40, i32 0, i32 5, !dbg !2010
  %58 = load i32, i32* %fd41, align 8, !dbg !2010
  %59 = load %struct.iovec*, %struct.iovec** %iov, align 8, !dbg !2012
  %arrayidx42 = getelementptr inbounds %struct.iovec, %struct.iovec* %59, i64 0, !dbg !2012
  %iov_base = getelementptr inbounds %struct.iovec, %struct.iovec* %arrayidx42, i32 0, i32 0, !dbg !2013
  %60 = load i8*, i8** %iov_base, align 8, !dbg !2013
  %61 = load %struct.iovec*, %struct.iovec** %iov, align 8, !dbg !2014
  %arrayidx43 = getelementptr inbounds %struct.iovec, %struct.iovec* %61, i64 0, !dbg !2014
  %iov_len = getelementptr inbounds %struct.iovec, %struct.iovec* %arrayidx43, i32 0, i32 1, !dbg !2015
  %62 = load i64, i64* %iov_len, align 8, !dbg !2015
  %call44 = call i64 @write(i32 %58, i8* %60, i64 %62), !dbg !2016
  store i64 %call44, i64* %n, align 8, !dbg !2017
  br label %if.end49, !dbg !2018

if.else45:                                        ; preds = %do.body36
  %63 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2019
  %io_watcher46 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %63, i32 0, i32 13, !dbg !2019
  %fd47 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher46, i32 0, i32 5, !dbg !2019
  %64 = load i32, i32* %fd47, align 8, !dbg !2019
  %65 = load %struct.iovec*, %struct.iovec** %iov, align 8, !dbg !2021
  %66 = load i32, i32* %iovcnt, align 4, !dbg !2022
  %call48 = call i64 @writev(i32 %64, %struct.iovec* %65, i32 %66), !dbg !2023
  store i64 %call48, i64* %n, align 8, !dbg !2024
  br label %if.end49

if.end49:                                         ; preds = %if.else45, %if.then39
  br label %do.cond50, !dbg !2025

do.cond50:                                        ; preds = %if.end49
  %67 = load i64, i64* %n, align 8, !dbg !2026
  %cmp51 = icmp eq i64 %67, -1, !dbg !2027
  br i1 %cmp51, label %land.rhs53, label %land.end57, !dbg !2028

land.rhs53:                                       ; preds = %do.cond50
  %call54 = call i32* @__errno_location() #1, !dbg !2029
  %68 = load i32, i32* %call54, align 4, !dbg !2029
  %cmp55 = icmp eq i32 %68, 4, !dbg !2031
  br label %land.end57

land.end57:                                       ; preds = %land.rhs53, %do.cond50
  %69 = phi i1 [ false, %do.cond50 ], [ %cmp55, %land.rhs53 ]
  br i1 %69, label %do.body36, label %do.end58, !dbg !2032

do.end58:                                         ; preds = %land.end57
  br label %if.end59

if.end59:                                         ; preds = %do.end58, %do.end
  %70 = load i64, i64* %n, align 8, !dbg !2034
  %cmp60 = icmp slt i64 %70, 0, !dbg !2036
  br i1 %cmp60, label %if.then62, label %if.else111, !dbg !2037

if.then62:                                        ; preds = %if.end59
  %call63 = call i32* @__errno_location() #1, !dbg !2038
  %71 = load i32, i32* %call63, align 4, !dbg !2038
  %cmp64 = icmp ne i32 %71, 11, !dbg !2041
  br i1 %cmp64, label %land.lhs.true, label %if.else104, !dbg !2042

land.lhs.true:                                    ; preds = %if.then62
  %call66 = call i32* @__errno_location() #1, !dbg !2043
  %72 = load i32, i32* %call66, align 4, !dbg !2043
  %cmp67 = icmp ne i32 %72, 11, !dbg !2045
  br i1 %cmp67, label %if.then69, label %if.else104, !dbg !2046

if.then69:                                        ; preds = %land.lhs.true
  %call70 = call i32* @__errno_location() #1, !dbg !2047
  %73 = load i32, i32* %call70, align 4, !dbg !2047
  %sub71 = sub nsw i32 0, %73, !dbg !2049
  %74 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2050
  %error = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %74, i32 0, i32 11, !dbg !2051
  store i32 %sub71, i32* %error, align 4, !dbg !2052
  %75 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2053
  call void @uv__write_req_finish(%struct.uv_write_s* %75), !dbg !2054
  %76 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2055
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %76, i32 0, i32 1, !dbg !2056
  %77 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2056
  %78 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2057
  %io_watcher72 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %78, i32 0, i32 13, !dbg !2058
  call void @uv__io_stop(%struct.uv_loop_s* %77, %struct.uv__io_s* %io_watcher72, i32 4), !dbg !2059
  %79 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2060
  %io_watcher73 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %79, i32 0, i32 13, !dbg !2062
  %call74 = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher73, i32 1), !dbg !2063
  %tobool75 = icmp ne i32 %call74, 0, !dbg !2063
  br i1 %tobool75, label %if.end103, label %if.then76, !dbg !2064

if.then76:                                        ; preds = %if.then69
  br label %do.body77, !dbg !2065

do.body77:                                        ; preds = %if.then76
  %80 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2066
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %80, i32 0, i32 7, !dbg !2066
  %81 = load i32, i32* %flags, align 8, !dbg !2066
  %and = and i32 %81, 0, !dbg !2066
  %cmp78 = icmp eq i32 %and, 0, !dbg !2066
  br i1 %cmp78, label %cond.true80, label %cond.false81, !dbg !2066

cond.true80:                                      ; preds = %do.body77
  br label %cond.end82, !dbg !2069

cond.false81:                                     ; preds = %do.body77
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 860, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2071
  unreachable, !dbg !2071
                                                  ; No predecessors!
  br label %cond.end82, !dbg !2073

cond.end82:                                       ; preds = %82, %cond.true80
  %83 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2075
  %flags83 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %83, i32 0, i32 7, !dbg !2075
  %84 = load i32, i32* %flags83, align 8, !dbg !2075
  %and84 = and i32 %84, 16384, !dbg !2075
  %cmp85 = icmp eq i32 %and84, 0, !dbg !2075
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !2075

if.then87:                                        ; preds = %cond.end82
  br label %do.end102, !dbg !2078

if.end88:                                         ; preds = %cond.end82
  %85 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2080
  %flags89 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %85, i32 0, i32 7, !dbg !2080
  %86 = load i32, i32* %flags89, align 8, !dbg !2080
  %and90 = and i32 %86, -16385, !dbg !2080
  store i32 %and90, i32* %flags89, align 8, !dbg !2080
  %87 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2080
  %flags91 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %87, i32 0, i32 7, !dbg !2080
  %88 = load i32, i32* %flags91, align 8, !dbg !2080
  %and92 = and i32 %88, 8192, !dbg !2080
  %cmp93 = icmp ne i32 %and92, 0, !dbg !2080
  br i1 %cmp93, label %if.then95, label %if.end100, !dbg !2080

if.then95:                                        ; preds = %if.end88
  br label %do.body96, !dbg !2082

do.body96:                                        ; preds = %if.then95
  %89 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2085
  %loop97 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %89, i32 0, i32 1, !dbg !2085
  %90 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop97, align 8, !dbg !2085
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %90, i32 0, i32 1, !dbg !2085
  %91 = load i32, i32* %active_handles, align 8, !dbg !2085
  %dec = add i32 %91, -1, !dbg !2085
  store i32 %dec, i32* %active_handles, align 8, !dbg !2085
  br label %do.end99, !dbg !2085

do.end99:                                         ; preds = %do.body96
  br label %if.end100, !dbg !2088

if.end100:                                        ; preds = %do.end99, %if.end88
  br label %do.end102, !dbg !2090

do.end102:                                        ; preds = %if.end100, %if.then87
  br label %if.end103, !dbg !2092

if.end103:                                        ; preds = %do.end102, %if.then69
  %92 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2094
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %92), !dbg !2095
  br label %return, !dbg !2096

if.else104:                                       ; preds = %land.lhs.true, %if.then62
  %93 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2097
  %flags105 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %93, i32 0, i32 7, !dbg !2099
  %94 = load i32, i32* %flags105, align 8, !dbg !2099
  %and106 = and i32 %94, 128, !dbg !2100
  %tobool107 = icmp ne i32 %and106, 0, !dbg !2100
  br i1 %tobool107, label %if.then108, label %if.end109, !dbg !2101

if.then108:                                       ; preds = %if.else104
  br label %start, !dbg !2102

if.end109:                                        ; preds = %if.else104
  br label %if.end110

if.end110:                                        ; preds = %if.end109
  br label %if.end166, !dbg !2104

if.else111:                                       ; preds = %if.end59
  br label %while.cond, !dbg !2105

while.cond:                                       ; preds = %if.end165, %if.else111
  %95 = load i64, i64* %n, align 8, !dbg !2107
  %cmp112 = icmp sge i64 %95, 0, !dbg !2109
  br i1 %cmp112, label %while.body, label %while.end, !dbg !2110

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %buf, metadata !2111, metadata !699), !dbg !2113
  %96 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2114
  %write_index114 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %96, i32 0, i32 8, !dbg !2115
  %97 = load i32, i32* %write_index114, align 8, !dbg !2115
  %idxprom115 = zext i32 %97 to i64, !dbg !2116
  %98 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2116
  %bufs116 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %98, i32 0, i32 9, !dbg !2117
  %99 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs116, align 8, !dbg !2117
  %arrayidx117 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %99, i64 %idxprom115, !dbg !2116
  store %struct.uv_buf_t* %arrayidx117, %struct.uv_buf_t** %buf, align 8, !dbg !2113
  call void @llvm.dbg.declare(metadata i64* %len, metadata !2118, metadata !699), !dbg !2119
  %100 = load %struct.uv_buf_t*, %struct.uv_buf_t** %buf, align 8, !dbg !2120
  %len118 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %100, i32 0, i32 1, !dbg !2121
  %101 = load i64, i64* %len118, align 8, !dbg !2121
  store i64 %101, i64* %len, align 8, !dbg !2119
  %102 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2122
  %write_index119 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %102, i32 0, i32 8, !dbg !2122
  %103 = load i32, i32* %write_index119, align 8, !dbg !2122
  %104 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2122
  %nbufs120 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %104, i32 0, i32 10, !dbg !2122
  %105 = load i32, i32* %nbufs120, align 8, !dbg !2122
  %cmp121 = icmp ult i32 %103, %105, !dbg !2122
  br i1 %cmp121, label %cond.true123, label %cond.false124, !dbg !2122

cond.true123:                                     ; preds = %while.body
  br label %cond.end125, !dbg !2123

cond.false124:                                    ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 874, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2125
  unreachable, !dbg !2125
                                                  ; No predecessors!
  br label %cond.end125, !dbg !2127

cond.end125:                                      ; preds = %106, %cond.true123
  %107 = load i64, i64* %n, align 8, !dbg !2129
  %108 = load i64, i64* %len, align 8, !dbg !2131
  %cmp126 = icmp ult i64 %107, %108, !dbg !2132
  br i1 %cmp126, label %if.then128, label %if.else138, !dbg !2133

if.then128:                                       ; preds = %cond.end125
  %109 = load i64, i64* %n, align 8, !dbg !2134
  %110 = load %struct.uv_buf_t*, %struct.uv_buf_t** %buf, align 8, !dbg !2136
  %base = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %110, i32 0, i32 0, !dbg !2137
  %111 = load i8*, i8** %base, align 8, !dbg !2138
  %add.ptr129 = getelementptr inbounds i8, i8* %111, i64 %109, !dbg !2138
  store i8* %add.ptr129, i8** %base, align 8, !dbg !2138
  %112 = load i64, i64* %n, align 8, !dbg !2139
  %113 = load %struct.uv_buf_t*, %struct.uv_buf_t** %buf, align 8, !dbg !2140
  %len130 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %113, i32 0, i32 1, !dbg !2141
  %114 = load i64, i64* %len130, align 8, !dbg !2142
  %sub131 = sub i64 %114, %112, !dbg !2142
  store i64 %sub131, i64* %len130, align 8, !dbg !2142
  %115 = load i64, i64* %n, align 8, !dbg !2143
  %116 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2144
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %116, i32 0, i32 8, !dbg !2145
  %117 = load i64, i64* %write_queue_size, align 8, !dbg !2146
  %sub132 = sub i64 %117, %115, !dbg !2146
  store i64 %sub132, i64* %write_queue_size, align 8, !dbg !2146
  store i64 0, i64* %n, align 8, !dbg !2147
  %118 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2148
  %flags133 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %118, i32 0, i32 7, !dbg !2150
  %119 = load i32, i32* %flags133, align 8, !dbg !2150
  %and134 = and i32 %119, 128, !dbg !2151
  %tobool135 = icmp ne i32 %and134, 0, !dbg !2151
  br i1 %tobool135, label %if.then136, label %if.else137, !dbg !2152

if.then136:                                       ; preds = %if.then128
  br label %start, !dbg !2153

if.else137:                                       ; preds = %if.then128
  br label %while.end, !dbg !2155

if.else138:                                       ; preds = %cond.end125
  %120 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2157
  %write_index139 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %120, i32 0, i32 8, !dbg !2159
  %121 = load i32, i32* %write_index139, align 8, !dbg !2160
  %inc = add i32 %121, 1, !dbg !2160
  store i32 %inc, i32* %write_index139, align 8, !dbg !2160
  %122 = load i64, i64* %n, align 8, !dbg !2161
  %123 = load i64, i64* %len, align 8, !dbg !2161
  %cmp140 = icmp uge i64 %122, %123, !dbg !2161
  br i1 %cmp140, label %cond.true142, label %cond.false143, !dbg !2161

cond.true142:                                     ; preds = %if.else138
  br label %cond.end144, !dbg !2162

cond.false143:                                    ; preds = %if.else138
  call void @__assert_fail(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.37, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 898, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2164
  unreachable, !dbg !2164
                                                  ; No predecessors!
  br label %cond.end144, !dbg !2166

cond.end144:                                      ; preds = %124, %cond.true142
  %125 = load i64, i64* %len, align 8, !dbg !2168
  %126 = load i64, i64* %n, align 8, !dbg !2169
  %sub145 = sub i64 %126, %125, !dbg !2169
  store i64 %sub145, i64* %n, align 8, !dbg !2169
  %127 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2170
  %write_queue_size146 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %127, i32 0, i32 8, !dbg !2170
  %128 = load i64, i64* %write_queue_size146, align 8, !dbg !2170
  %129 = load i64, i64* %len, align 8, !dbg !2170
  %cmp147 = icmp uge i64 %128, %129, !dbg !2170
  br i1 %cmp147, label %cond.true149, label %cond.false150, !dbg !2170

cond.true149:                                     ; preds = %cond.end144
  br label %cond.end151, !dbg !2171

cond.false150:                                    ; preds = %cond.end144
  call void @__assert_fail(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 901, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2172
  unreachable, !dbg !2172
                                                  ; No predecessors!
  br label %cond.end151, !dbg !2173

cond.end151:                                      ; preds = %130, %cond.true149
  %131 = load i64, i64* %len, align 8, !dbg !2174
  %132 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2175
  %write_queue_size152 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %132, i32 0, i32 8, !dbg !2176
  %133 = load i64, i64* %write_queue_size152, align 8, !dbg !2177
  %sub153 = sub i64 %133, %131, !dbg !2177
  store i64 %sub153, i64* %write_queue_size152, align 8, !dbg !2177
  %134 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2178
  %write_index154 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %134, i32 0, i32 8, !dbg !2180
  %135 = load i32, i32* %write_index154, align 8, !dbg !2180
  %136 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2181
  %nbufs155 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %136, i32 0, i32 10, !dbg !2182
  %137 = load i32, i32* %nbufs155, align 8, !dbg !2182
  %cmp156 = icmp eq i32 %135, %137, !dbg !2183
  br i1 %cmp156, label %if.then158, label %if.end164, !dbg !2184

if.then158:                                       ; preds = %cond.end151
  %138 = load i64, i64* %n, align 8, !dbg !2185
  %cmp159 = icmp eq i64 %138, 0, !dbg !2185
  br i1 %cmp159, label %cond.true161, label %cond.false162, !dbg !2185

cond.true161:                                     ; preds = %if.then158
  br label %cond.end163, !dbg !2187

cond.false162:                                    ; preds = %if.then158
  call void @__assert_fail(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.39, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 906, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2189
  unreachable, !dbg !2189
                                                  ; No predecessors!
  br label %cond.end163, !dbg !2191

cond.end163:                                      ; preds = %139, %cond.true161
  %140 = load %struct.uv_write_s*, %struct.uv_write_s** %req, align 8, !dbg !2193
  call void @uv__write_req_finish(%struct.uv_write_s* %140), !dbg !2194
  br label %return, !dbg !2195

if.end164:                                        ; preds = %cond.end151
  br label %if.end165

if.end165:                                        ; preds = %if.end164
  br label %while.cond, !dbg !2196

while.end:                                        ; preds = %if.else137, %while.cond
  br label %if.end166

if.end166:                                        ; preds = %while.end, %if.end110
  %141 = load i64, i64* %n, align 8, !dbg !2198
  %cmp167 = icmp eq i64 %141, 0, !dbg !2198
  br i1 %cmp167, label %cond.true171, label %lor.lhs.false, !dbg !2198

lor.lhs.false:                                    ; preds = %if.end166
  %142 = load i64, i64* %n, align 8, !dbg !2199
  %cmp169 = icmp eq i64 %142, -1, !dbg !2199
  br i1 %cmp169, label %cond.true171, label %cond.false172, !dbg !2199

cond.true171:                                     ; preds = %lor.lhs.false, %if.end166
  br label %cond.end173, !dbg !2200

cond.false172:                                    ; preds = %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.40, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 916, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2201
  unreachable, !dbg !2201
                                                  ; No predecessors!
  br label %cond.end173, !dbg !2202

cond.end173:                                      ; preds = %143, %cond.true171
  %144 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2204
  %flags174 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %144, i32 0, i32 7, !dbg !2204
  %145 = load i32, i32* %flags174, align 8, !dbg !2204
  %and175 = and i32 %145, 128, !dbg !2204
  %tobool176 = icmp ne i32 %and175, 0, !dbg !2204
  br i1 %tobool176, label %cond.false178, label %cond.true177, !dbg !2204

cond.true177:                                     ; preds = %cond.end173
  br label %cond.end179, !dbg !2205

cond.false178:                                    ; preds = %cond.end173
  call void @__assert_fail(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 919, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__write, i32 0, i32 0)) #7, !dbg !2206
  unreachable, !dbg !2206
                                                  ; No predecessors!
  br label %cond.end179, !dbg !2207

cond.end179:                                      ; preds = %146, %cond.true177
  %147 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2208
  %loop180 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %147, i32 0, i32 1, !dbg !2209
  %148 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop180, align 8, !dbg !2209
  %149 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2210
  %io_watcher181 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %149, i32 0, i32 13, !dbg !2211
  call void @uv__io_start(%struct.uv_loop_s* %148, %struct.uv__io_s* %io_watcher181, i32 4), !dbg !2212
  %150 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2213
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %150), !dbg !2214
  br label %return, !dbg !2215

return:                                           ; preds = %cond.end179, %cond.end163, %if.end103, %if.then
  ret void, !dbg !2216
}

; Function Attrs: nounwind uwtable
define i32 @uv_write(%struct.uv_write_s* %req, %struct.uv_stream_s* %handle, %struct.uv_buf_t* %bufs, i32 %nbufs, void (%struct.uv_write_s*, i32)* %cb) #0 !dbg !634 {
entry:
  %req.addr = alloca %struct.uv_write_s*, align 8
  %handle.addr = alloca %struct.uv_stream_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_write_s*, i32)*, align 8
  store %struct.uv_write_s* %req, %struct.uv_write_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req.addr, metadata !2217, metadata !699), !dbg !2218
  store %struct.uv_stream_s* %handle, %struct.uv_stream_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %handle.addr, metadata !2219, metadata !699), !dbg !2220
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !2221, metadata !699), !dbg !2222
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !2223, metadata !699), !dbg !2224
  store void (%struct.uv_write_s*, i32)* %cb, void (%struct.uv_write_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_write_s*, i32)** %cb.addr, metadata !2225, metadata !699), !dbg !2226
  %0 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2227
  %1 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2228
  %2 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !2229
  %3 = load i32, i32* %nbufs.addr, align 4, !dbg !2230
  %4 = load void (%struct.uv_write_s*, i32)*, void (%struct.uv_write_s*, i32)** %cb.addr, align 8, !dbg !2231
  %call = call i32 @uv_write2(%struct.uv_write_s* %0, %struct.uv_stream_s* %1, %struct.uv_buf_t* %2, i32 %3, %struct.uv_stream_s* null, void (%struct.uv_write_s*, i32)* %4), !dbg !2232
  ret i32 %call, !dbg !2233
}

; Function Attrs: nounwind uwtable
define void @uv_try_write_cb(%struct.uv_write_s* %req, i32 %status) #0 !dbg !637 {
entry:
  %req.addr = alloca %struct.uv_write_s*, align 8
  %status.addr = alloca i32, align 4
  store %struct.uv_write_s* %req, %struct.uv_write_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req.addr, metadata !2234, metadata !699), !dbg !2235
  store i32 %status, i32* %status.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %status.addr, metadata !2236, metadata !699), !dbg !2237
  call void @abort() #7, !dbg !2238
  unreachable, !dbg !2238

return:                                           ; No predecessors!
  ret void, !dbg !2239
}

; Function Attrs: noreturn nounwind
declare void @abort() #3

; Function Attrs: nounwind uwtable
define i32 @uv_try_write(%struct.uv_stream_s* %stream, %struct.uv_buf_t* %bufs, i32 %nbufs) #0 !dbg !638 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %r = alloca i32, align 4
  %has_pollout = alloca i32, align 4
  %written = alloca i64, align 8
  %req_size = alloca i64, align 8
  %req = alloca %struct.uv_write_s, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2240, metadata !699), !dbg !2241
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !2242, metadata !699), !dbg !2243
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !2244, metadata !699), !dbg !2245
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2246, metadata !699), !dbg !2247
  call void @llvm.dbg.declare(metadata i32* %has_pollout, metadata !2248, metadata !699), !dbg !2249
  call void @llvm.dbg.declare(metadata i64* %written, metadata !2250, metadata !699), !dbg !2251
  call void @llvm.dbg.declare(metadata i64* %req_size, metadata !2252, metadata !699), !dbg !2253
  call void @llvm.dbg.declare(metadata %struct.uv_write_s* %req, metadata !2254, metadata !699), !dbg !2255
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2256
  %connect_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 11, !dbg !2258
  %1 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req, align 8, !dbg !2258
  %cmp = icmp ne %struct.uv_connect_s* %1, null, !dbg !2259
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2260

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2261
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 8, !dbg !2263
  %3 = load i64, i64* %write_queue_size, align 8, !dbg !2263
  %cmp1 = icmp ne i64 %3, 0, !dbg !2264
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2265

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -11, i32* %retval, align 4, !dbg !2266
  br label %return, !dbg !2266

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2267
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 13, !dbg !2268
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher, i32 4), !dbg !2269
  store i32 %call, i32* %has_pollout, align 4, !dbg !2270
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2271
  %6 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !2272
  %7 = load i32, i32* %nbufs.addr, align 4, !dbg !2273
  %call2 = call i32 @uv_write(%struct.uv_write_s* %req, %struct.uv_stream_s* %5, %struct.uv_buf_t* %6, i32 %7, void (%struct.uv_write_s*, i32)* @uv_try_write_cb), !dbg !2274
  store i32 %call2, i32* %r, align 4, !dbg !2275
  %8 = load i32, i32* %r, align 4, !dbg !2276
  %cmp3 = icmp ne i32 %8, 0, !dbg !2278
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2279

if.then4:                                         ; preds = %if.end
  %9 = load i32, i32* %r, align 4, !dbg !2280
  store i32 %9, i32* %retval, align 4, !dbg !2281
  br label %return, !dbg !2281

if.end5:                                          ; preds = %if.end
  %10 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !2282
  %11 = load i32, i32* %nbufs.addr, align 4, !dbg !2283
  %call6 = call i64 @uv__count_bufs(%struct.uv_buf_t* %10, i32 %11), !dbg !2284
  store i64 %call6, i64* %written, align 8, !dbg !2285
  %bufs7 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 9, !dbg !2286
  %12 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs7, align 8, !dbg !2286
  %cmp8 = icmp ne %struct.uv_buf_t* %12, null, !dbg !2288
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !2289

if.then9:                                         ; preds = %if.end5
  %call10 = call i64 @uv__write_req_size(%struct.uv_write_s* %req), !dbg !2290
  store i64 %call10, i64* %req_size, align 8, !dbg !2291
  br label %if.end11, !dbg !2292

if.else:                                          ; preds = %if.end5
  store i64 0, i64* %req_size, align 8, !dbg !2293
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then9
  %13 = load i64, i64* %req_size, align 8, !dbg !2294
  %14 = load i64, i64* %written, align 8, !dbg !2295
  %sub = sub i64 %14, %13, !dbg !2295
  store i64 %sub, i64* %written, align 8, !dbg !2295
  %15 = load i64, i64* %req_size, align 8, !dbg !2296
  %16 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2297
  %write_queue_size12 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %16, i32 0, i32 8, !dbg !2298
  %17 = load i64, i64* %write_queue_size12, align 8, !dbg !2299
  %sub13 = sub i64 %17, %15, !dbg !2299
  store i64 %sub13, i64* %write_queue_size12, align 8, !dbg !2299
  br label %do.body, !dbg !2300

do.body:                                          ; preds = %if.end11
  %queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 7, !dbg !2301
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !2301
  %18 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2301
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !2301
  %queue14 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 7, !dbg !2301
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue14, i64 0, i64 1, !dbg !2301
  %20 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !2301
  %21 = load [2 x i8*]*, [2 x i8*]** %20, align 8, !dbg !2301
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %21, i64 0, i64 0, !dbg !2301
  %22 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2301
  store [2 x i8*]* %19, [2 x i8*]** %22, align 8, !dbg !2301
  %queue17 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 7, !dbg !2301
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue17, i64 0, i64 1, !dbg !2301
  %23 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !2301
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !2301
  %queue19 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 7, !dbg !2301
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue19, i64 0, i64 0, !dbg !2301
  %25 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !2301
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !2301
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %26, i64 0, i64 1, !dbg !2301
  %27 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !2301
  store [2 x i8*]* %24, [2 x i8*]** %27, align 8, !dbg !2301
  br label %do.end, !dbg !2301

do.end:                                           ; preds = %do.body
  br label %do.body22, !dbg !2304

do.body22:                                        ; preds = %do.end
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2305
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 1, !dbg !2305
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2305
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %29, i32 0, i32 3, !dbg !2305
  %30 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2305
  %loop23 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %30, i32 0, i32 1, !dbg !2305
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop23, align 8, !dbg !2305
  %active_reqs24 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %31, i32 0, i32 3, !dbg !2305
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs24, i64 0, i64 0, !dbg !2305
  %32 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !2305
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 8, !dbg !2305
  %cmp26 = icmp eq [2 x i8*]* %active_reqs, %33, !dbg !2305
  %conv = zext i1 %cmp26 to i32, !dbg !2305
  %cmp27 = icmp eq i32 %conv, 0, !dbg !2305
  br i1 %cmp27, label %cond.true, label %cond.false, !dbg !2305

cond.true:                                        ; preds = %do.body22
  br label %cond.end, !dbg !2308

cond.false:                                       ; preds = %do.body22
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1514, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_try_write, i32 0, i32 0)) #7, !dbg !2310
  unreachable, !dbg !2310
                                                  ; No predecessors!
  br label %cond.end, !dbg !2312

cond.end:                                         ; preds = %34, %cond.true
  br label %do.body29, !dbg !2314

do.body29:                                        ; preds = %cond.end
  %active_queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 2, !dbg !2316
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2316
  %35 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !2316
  %36 = load [2 x i8*]*, [2 x i8*]** %35, align 8, !dbg !2316
  %active_queue31 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 2, !dbg !2316
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue31, i64 0, i64 1, !dbg !2316
  %37 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !2316
  %38 = load [2 x i8*]*, [2 x i8*]** %37, align 8, !dbg !2316
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %38, i64 0, i64 0, !dbg !2316
  %39 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !2316
  store [2 x i8*]* %36, [2 x i8*]** %39, align 8, !dbg !2316
  %active_queue34 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 2, !dbg !2316
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue34, i64 0, i64 1, !dbg !2316
  %40 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !2316
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 8, !dbg !2316
  %active_queue36 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 2, !dbg !2316
  %arrayidx37 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue36, i64 0, i64 0, !dbg !2316
  %42 = bitcast i8** %arrayidx37 to [2 x i8*]**, !dbg !2316
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !2316
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %43, i64 0, i64 1, !dbg !2316
  %44 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !2316
  store [2 x i8*]* %41, [2 x i8*]** %44, align 8, !dbg !2316
  br label %do.end39, !dbg !2316

do.end39:                                         ; preds = %do.body29
  br label %do.end40, !dbg !2319

do.end40:                                         ; preds = %do.end39
  %bufs41 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 9, !dbg !2321
  %45 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs41, align 8, !dbg !2321
  %bufsml = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 12, !dbg !2323
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !2324
  %cmp42 = icmp ne %struct.uv_buf_t* %45, %arraydecay, !dbg !2325
  br i1 %cmp42, label %if.then44, label %if.end46, !dbg !2326

if.then44:                                        ; preds = %do.end40
  %bufs45 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 9, !dbg !2327
  %46 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs45, align 8, !dbg !2327
  %47 = bitcast %struct.uv_buf_t* %46 to i8*, !dbg !2328
  call void @uv__free(i8* %47), !dbg !2329
  br label %if.end46, !dbg !2329

if.end46:                                         ; preds = %if.then44, %do.end40
  %bufs47 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %req, i32 0, i32 9, !dbg !2330
  store %struct.uv_buf_t* null, %struct.uv_buf_t** %bufs47, align 8, !dbg !2331
  %48 = load i32, i32* %has_pollout, align 4, !dbg !2332
  %tobool = icmp ne i32 %48, 0, !dbg !2332
  br i1 %tobool, label %if.end51, label %if.then48, !dbg !2334

if.then48:                                        ; preds = %if.end46
  %49 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2335
  %loop49 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %49, i32 0, i32 1, !dbg !2337
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop49, align 8, !dbg !2337
  %51 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2338
  %io_watcher50 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %51, i32 0, i32 13, !dbg !2339
  call void @uv__io_stop(%struct.uv_loop_s* %50, %struct.uv__io_s* %io_watcher50, i32 4), !dbg !2340
  %52 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2341
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %52), !dbg !2342
  br label %if.end51, !dbg !2343

if.end51:                                         ; preds = %if.then48, %if.end46
  %53 = load i64, i64* %written, align 8, !dbg !2344
  %cmp52 = icmp eq i64 %53, 0, !dbg !2346
  br i1 %cmp52, label %land.lhs.true, label %if.else57, !dbg !2347

land.lhs.true:                                    ; preds = %if.end51
  %54 = load i64, i64* %req_size, align 8, !dbg !2348
  %cmp54 = icmp ne i64 %54, 0, !dbg !2350
  br i1 %cmp54, label %if.then56, label %if.else57, !dbg !2351

if.then56:                                        ; preds = %land.lhs.true
  store i32 -11, i32* %retval, align 4, !dbg !2352
  br label %return, !dbg !2352

if.else57:                                        ; preds = %land.lhs.true, %if.end51
  %55 = load i64, i64* %written, align 8, !dbg !2353
  %conv58 = trunc i64 %55 to i32, !dbg !2353
  store i32 %conv58, i32* %retval, align 4, !dbg !2354
  br label %return, !dbg !2354

return:                                           ; preds = %if.else57, %if.then56, %if.then4, %if.then
  %56 = load i32, i32* %retval, align 4, !dbg !2355
  ret i32 %56, !dbg !2355
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__write_req_size(%struct.uv_write_s* %req) #0 !dbg !692 {
entry:
  %req.addr = alloca %struct.uv_write_s*, align 8
  %size = alloca i64, align 8
  store %struct.uv_write_s* %req, %struct.uv_write_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req.addr, metadata !2356, metadata !699), !dbg !2357
  call void @llvm.dbg.declare(metadata i64* %size, metadata !2358, metadata !699), !dbg !2359
  %0 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2360
  %bufs = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %0, i32 0, i32 9, !dbg !2360
  %1 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !2360
  %cmp = icmp ne %struct.uv_buf_t* %1, null, !dbg !2360
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2360

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2361

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.41, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 697, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.uv__write_req_size, i32 0, i32 0)) #7, !dbg !2363
  unreachable, !dbg !2363
                                                  ; No predecessors!
  br label %cond.end, !dbg !2365

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2367
  %bufs1 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %3, i32 0, i32 9, !dbg !2368
  %4 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs1, align 8, !dbg !2368
  %5 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2369
  %write_index = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %5, i32 0, i32 8, !dbg !2370
  %6 = load i32, i32* %write_index, align 8, !dbg !2370
  %idx.ext = zext i32 %6 to i64, !dbg !2371
  %add.ptr = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %4, i64 %idx.ext, !dbg !2371
  %7 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2372
  %nbufs = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %7, i32 0, i32 10, !dbg !2373
  %8 = load i32, i32* %nbufs, align 8, !dbg !2373
  %9 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2374
  %write_index2 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %9, i32 0, i32 8, !dbg !2375
  %10 = load i32, i32* %write_index2, align 8, !dbg !2375
  %sub = sub i32 %8, %10, !dbg !2376
  %call = call i64 @uv__count_bufs(%struct.uv_buf_t* %add.ptr, i32 %sub), !dbg !2377
  store i64 %call, i64* %size, align 8, !dbg !2378
  %11 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !2379
  %handle = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %11, i32 0, i32 6, !dbg !2379
  %12 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle, align 8, !dbg !2379
  %write_queue_size = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %12, i32 0, i32 8, !dbg !2379
  %13 = load i64, i64* %write_queue_size, align 8, !dbg !2379
  %14 = load i64, i64* %size, align 8, !dbg !2379
  %cmp3 = icmp uge i64 %13, %14, !dbg !2379
  br i1 %cmp3, label %cond.true4, label %cond.false5, !dbg !2379

cond.true4:                                       ; preds = %cond.end
  br label %cond.end6, !dbg !2380

cond.false5:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.42, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 700, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.uv__write_req_size, i32 0, i32 0)) #7, !dbg !2381
  unreachable, !dbg !2381
                                                  ; No predecessors!
  br label %cond.end6, !dbg !2382

cond.end6:                                        ; preds = %15, %cond.true4
  %16 = load i64, i64* %size, align 8, !dbg !2383
  ret i64 %16, !dbg !2384
}

; Function Attrs: nounwind uwtable
define i32 @uv_read_start(%struct.uv_stream_s* %stream, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %alloc_cb, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)* %read_cb) #0 !dbg !641 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %alloc_cb.addr = alloca void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, align 8
  %read_cb.addr = alloca void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2385, metadata !699), !dbg !2386
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %alloc_cb, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, metadata !2387, metadata !699), !dbg !2388
  store void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)* %read_cb, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb.addr, metadata !2389, metadata !699), !dbg !2390
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2391
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 2, !dbg !2391
  %1 = load i32, i32* %type, align 8, !dbg !2391
  %cmp = icmp eq i32 %1, 12, !dbg !2391
  br i1 %cmp, label %cond.true, label %lor.lhs.false, !dbg !2391

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2392
  %type1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 2, !dbg !2392
  %3 = load i32, i32* %type1, align 8, !dbg !2392
  %cmp2 = icmp eq i32 %3, 7, !dbg !2392
  br i1 %cmp2, label %cond.true, label %lor.lhs.false3, !dbg !2392

lor.lhs.false3:                                   ; preds = %lor.lhs.false
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2394
  %type4 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 2, !dbg !2394
  %5 = load i32, i32* %type4, align 8, !dbg !2394
  %cmp5 = icmp eq i32 %5, 14, !dbg !2394
  br i1 %cmp5, label %cond.true, label %cond.false, !dbg !2394

cond.true:                                        ; preds = %lor.lhs.false3, %lor.lhs.false, %entry
  br label %cond.end, !dbg !2396

cond.false:                                       ; preds = %lor.lhs.false3
  call void @__assert_fail(i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1536, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv_read_start, i32 0, i32 0)) #7, !dbg !2398
  unreachable, !dbg !2398
                                                  ; No predecessors!
  br label %cond.end, !dbg !2400

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2402
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 7, !dbg !2404
  %8 = load i32, i32* %flags, align 8, !dbg !2404
  %and = and i32 %8, 1, !dbg !2405
  %tobool = icmp ne i32 %and, 0, !dbg !2405
  br i1 %tobool, label %if.then, label %if.end, !dbg !2406

if.then:                                          ; preds = %cond.end
  store i32 -22, i32* %retval, align 4, !dbg !2407
  br label %return, !dbg !2407

if.end:                                           ; preds = %cond.end
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2408
  %flags6 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 7, !dbg !2409
  %10 = load i32, i32* %flags6, align 8, !dbg !2410
  %or = or i32 %10, 4, !dbg !2410
  store i32 %or, i32* %flags6, align 8, !dbg !2410
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2411
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 13, !dbg !2411
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2411
  %12 = load i32, i32* %fd, align 8, !dbg !2411
  %cmp7 = icmp sge i32 %12, 0, !dbg !2411
  br i1 %cmp7, label %cond.true8, label %cond.false9, !dbg !2411

cond.true8:                                       ; preds = %if.end
  br label %cond.end10, !dbg !2412

cond.false9:                                      ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1550, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv_read_start, i32 0, i32 0)) #7, !dbg !2413
  unreachable, !dbg !2413
                                                  ; No predecessors!
  br label %cond.end10, !dbg !2414

cond.end10:                                       ; preds = %13, %cond.true8
  %14 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8, !dbg !2415
  %tobool11 = icmp ne void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %14, null, !dbg !2415
  br i1 %tobool11, label %cond.true12, label %cond.false13, !dbg !2415

cond.true12:                                      ; preds = %cond.end10
  br label %cond.end14, !dbg !2416

cond.false13:                                     ; preds = %cond.end10
  call void @__assert_fail(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.22, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1551, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv_read_start, i32 0, i32 0)) #7, !dbg !2417
  unreachable, !dbg !2417
                                                  ; No predecessors!
  br label %cond.end14, !dbg !2418

cond.end14:                                       ; preds = %15, %cond.true12
  %16 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb.addr, align 8, !dbg !2419
  %17 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2420
  %read_cb15 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %17, i32 0, i32 10, !dbg !2421
  store void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)* %16, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb15, align 8, !dbg !2422
  %18 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb.addr, align 8, !dbg !2423
  %19 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2424
  %alloc_cb16 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %19, i32 0, i32 9, !dbg !2425
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %18, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb16, align 8, !dbg !2426
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2427
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %20, i32 0, i32 1, !dbg !2428
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2428
  %22 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2429
  %io_watcher17 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %22, i32 0, i32 13, !dbg !2430
  call void @uv__io_start(%struct.uv_loop_s* %21, %struct.uv__io_s* %io_watcher17, i32 1), !dbg !2431
  br label %do.body, !dbg !2432

do.body:                                          ; preds = %cond.end14
  %23 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2433
  %flags18 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %23, i32 0, i32 7, !dbg !2433
  %24 = load i32, i32* %flags18, align 8, !dbg !2433
  %and19 = and i32 %24, 0, !dbg !2433
  %cmp20 = icmp eq i32 %and19, 0, !dbg !2433
  br i1 %cmp20, label %cond.true21, label %cond.false22, !dbg !2433

cond.true21:                                      ; preds = %do.body
  br label %cond.end23, !dbg !2436

cond.false22:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1557, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv_read_start, i32 0, i32 0)) #7, !dbg !2438
  unreachable, !dbg !2438
                                                  ; No predecessors!
  br label %cond.end23, !dbg !2440

cond.end23:                                       ; preds = %25, %cond.true21
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2442
  %flags24 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %26, i32 0, i32 7, !dbg !2442
  %27 = load i32, i32* %flags24, align 8, !dbg !2442
  %and25 = and i32 %27, 16384, !dbg !2442
  %cmp26 = icmp ne i32 %and25, 0, !dbg !2442
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !2442

if.then27:                                        ; preds = %cond.end23
  br label %do.end38, !dbg !2445

if.end28:                                         ; preds = %cond.end23
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2447
  %flags29 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 7, !dbg !2447
  %29 = load i32, i32* %flags29, align 8, !dbg !2447
  %or30 = or i32 %29, 16384, !dbg !2447
  store i32 %or30, i32* %flags29, align 8, !dbg !2447
  %30 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2447
  %flags31 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %30, i32 0, i32 7, !dbg !2447
  %31 = load i32, i32* %flags31, align 8, !dbg !2447
  %and32 = and i32 %31, 8192, !dbg !2447
  %cmp33 = icmp ne i32 %and32, 0, !dbg !2447
  br i1 %cmp33, label %if.then34, label %if.end37, !dbg !2447

if.then34:                                        ; preds = %if.end28
  br label %do.body35, !dbg !2449

do.body35:                                        ; preds = %if.then34
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2452
  %loop36 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %32, i32 0, i32 1, !dbg !2452
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop36, align 8, !dbg !2452
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 1, !dbg !2452
  %34 = load i32, i32* %active_handles, align 8, !dbg !2452
  %inc = add i32 %34, 1, !dbg !2452
  store i32 %inc, i32* %active_handles, align 8, !dbg !2452
  br label %do.end, !dbg !2452

do.end:                                           ; preds = %do.body35
  br label %if.end37, !dbg !2455

if.end37:                                         ; preds = %do.end, %if.end28
  br label %do.end38, !dbg !2457

do.end38:                                         ; preds = %if.end37, %if.then27
  %35 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2459
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %35), !dbg !2460
  store i32 0, i32* %retval, align 4, !dbg !2461
  br label %return, !dbg !2461

return:                                           ; preds = %do.end38, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !2462
  ret i32 %36, !dbg !2462
}

; Function Attrs: nounwind uwtable
define i32 @uv_read_stop(%struct.uv_stream_s* %stream) #0 !dbg !644 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2463, metadata !699), !dbg !2464
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2465
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 7, !dbg !2467
  %1 = load i32, i32* %flags, align 8, !dbg !2467
  %and = and i32 %1, 4, !dbg !2468
  %tobool = icmp ne i32 %and, 0, !dbg !2468
  br i1 %tobool, label %if.end, label %if.then, !dbg !2469

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2470
  br label %return, !dbg !2470

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2471
  %flags1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 7, !dbg !2472
  %3 = load i32, i32* %flags1, align 8, !dbg !2473
  %and2 = and i32 %3, -5, !dbg !2473
  store i32 %and2, i32* %flags1, align 8, !dbg !2473
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2474
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 1, !dbg !2475
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2475
  %6 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2476
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %6, i32 0, i32 13, !dbg !2477
  call void @uv__io_stop(%struct.uv_loop_s* %5, %struct.uv__io_s* %io_watcher, i32 1), !dbg !2478
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2479
  %io_watcher3 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 13, !dbg !2481
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher3, i32 4), !dbg !2482
  %tobool4 = icmp ne i32 %call, 0, !dbg !2482
  br i1 %tobool4, label %if.end23, label %if.then5, !dbg !2483

if.then5:                                         ; preds = %if.end
  br label %do.body, !dbg !2484

do.body:                                          ; preds = %if.then5
  %8 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2485
  %flags6 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %8, i32 0, i32 7, !dbg !2485
  %9 = load i32, i32* %flags6, align 8, !dbg !2485
  %and7 = and i32 %9, 0, !dbg !2485
  %cmp = icmp eq i32 %and7, 0, !dbg !2485
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2485

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !2488

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1571, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.uv_read_stop, i32 0, i32 0)) #7, !dbg !2490
  unreachable, !dbg !2490
                                                  ; No predecessors!
  br label %cond.end, !dbg !2492

cond.end:                                         ; preds = %10, %cond.true
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2494
  %flags8 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 7, !dbg !2494
  %12 = load i32, i32* %flags8, align 8, !dbg !2494
  %and9 = and i32 %12, 16384, !dbg !2494
  %cmp10 = icmp eq i32 %and9, 0, !dbg !2494
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !2494

if.then11:                                        ; preds = %cond.end
  br label %do.end22, !dbg !2497

if.end12:                                         ; preds = %cond.end
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2499
  %flags13 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 7, !dbg !2499
  %14 = load i32, i32* %flags13, align 8, !dbg !2499
  %and14 = and i32 %14, -16385, !dbg !2499
  store i32 %and14, i32* %flags13, align 8, !dbg !2499
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2499
  %flags15 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %15, i32 0, i32 7, !dbg !2499
  %16 = load i32, i32* %flags15, align 8, !dbg !2499
  %and16 = and i32 %16, 8192, !dbg !2499
  %cmp17 = icmp ne i32 %and16, 0, !dbg !2499
  br i1 %cmp17, label %if.then18, label %if.end21, !dbg !2499

if.then18:                                        ; preds = %if.end12
  br label %do.body19, !dbg !2501

do.body19:                                        ; preds = %if.then18
  %17 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2504
  %loop20 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %17, i32 0, i32 1, !dbg !2504
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop20, align 8, !dbg !2504
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 1, !dbg !2504
  %19 = load i32, i32* %active_handles, align 8, !dbg !2504
  %dec = add i32 %19, -1, !dbg !2504
  store i32 %dec, i32* %active_handles, align 8, !dbg !2504
  br label %do.end, !dbg !2504

do.end:                                           ; preds = %do.body19
  br label %if.end21, !dbg !2507

if.end21:                                         ; preds = %do.end, %if.end12
  br label %do.end22, !dbg !2509

do.end22:                                         ; preds = %if.end21, %if.then11
  br label %if.end23, !dbg !2511

if.end23:                                         ; preds = %do.end22, %if.end
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2513
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %20), !dbg !2514
  %21 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2515
  %read_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %21, i32 0, i32 10, !dbg !2516
  store void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb, align 8, !dbg !2517
  %22 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2518
  %alloc_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %22, i32 0, i32 9, !dbg !2519
  store void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* null, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !2520
  store i32 0, i32* %retval, align 4, !dbg !2521
  br label %return, !dbg !2521

return:                                           ; preds = %if.end23, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !2522
  ret i32 %23, !dbg !2522
}

; Function Attrs: nounwind uwtable
define i32 @uv_is_readable(%struct.uv_stream_s* %stream) #0 !dbg !647 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2523, metadata !699), !dbg !2524
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2525
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 7, !dbg !2526
  %1 = load i32, i32* %flags, align 8, !dbg !2526
  %and = and i32 %1, 32, !dbg !2527
  %tobool = icmp ne i32 %and, 0, !dbg !2528
  %lnot = xor i1 %tobool, true, !dbg !2528
  %lnot1 = xor i1 %lnot, true, !dbg !2529
  %lnot.ext = zext i1 %lnot1 to i32, !dbg !2529
  ret i32 %lnot.ext, !dbg !2530
}

; Function Attrs: nounwind uwtable
define i32 @uv_is_writable(%struct.uv_stream_s* %stream) #0 !dbg !652 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2531, metadata !699), !dbg !2532
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2533
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 7, !dbg !2534
  %1 = load i32, i32* %flags, align 8, !dbg !2534
  %and = and i32 %1, 64, !dbg !2535
  %tobool = icmp ne i32 %and, 0, !dbg !2536
  %lnot = xor i1 %tobool, true, !dbg !2536
  %lnot1 = xor i1 %lnot, true, !dbg !2537
  %lnot.ext = zext i1 %lnot1 to i32, !dbg !2537
  ret i32 %lnot.ext, !dbg !2538
}

; Function Attrs: nounwind uwtable
define void @uv__stream_close(%struct.uv_stream_s* %handle) #0 !dbg !653 {
entry:
  %handle.addr = alloca %struct.uv_stream_s*, align 8
  %i = alloca i32, align 4
  %queued_fds = alloca %struct.uv__stream_queued_fds_s*, align 8
  store %struct.uv_stream_s* %handle, %struct.uv_stream_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %handle.addr, metadata !2539, metadata !699), !dbg !2540
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2541, metadata !699), !dbg !2542
  call void @llvm.dbg.declare(metadata %struct.uv__stream_queued_fds_s** %queued_fds, metadata !2543, metadata !699), !dbg !2544
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2545
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 1, !dbg !2546
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2546
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2547
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 13, !dbg !2548
  call void @uv__io_close(%struct.uv_loop_s* %1, %struct.uv__io_s* %io_watcher), !dbg !2549
  %3 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2550
  %call = call i32 @uv_read_stop(%struct.uv_stream_s* %3), !dbg !2551
  br label %do.body, !dbg !2552

do.body:                                          ; preds = %entry
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2553
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 7, !dbg !2553
  %5 = load i32, i32* %flags, align 8, !dbg !2553
  %and = and i32 %5, 0, !dbg !2553
  %cmp = icmp eq i32 %and, 0, !dbg !2553
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2553

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !2556

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.23, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1634, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.uv__stream_close, i32 0, i32 0)) #7, !dbg !2558
  unreachable, !dbg !2558
                                                  ; No predecessors!
  br label %cond.end, !dbg !2560

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2562
  %flags1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 7, !dbg !2562
  %8 = load i32, i32* %flags1, align 8, !dbg !2562
  %and2 = and i32 %8, 16384, !dbg !2562
  %cmp3 = icmp eq i32 %and2, 0, !dbg !2562
  br i1 %cmp3, label %if.then, label %if.end, !dbg !2562

if.then:                                          ; preds = %cond.end
  br label %do.end13, !dbg !2565

if.end:                                           ; preds = %cond.end
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2567
  %flags4 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 7, !dbg !2567
  %10 = load i32, i32* %flags4, align 8, !dbg !2567
  %and5 = and i32 %10, -16385, !dbg !2567
  store i32 %and5, i32* %flags4, align 8, !dbg !2567
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2567
  %flags6 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 7, !dbg !2567
  %12 = load i32, i32* %flags6, align 8, !dbg !2567
  %and7 = and i32 %12, 8192, !dbg !2567
  %cmp8 = icmp ne i32 %and7, 0, !dbg !2567
  br i1 %cmp8, label %if.then9, label %if.end12, !dbg !2567

if.then9:                                         ; preds = %if.end
  br label %do.body10, !dbg !2569

do.body10:                                        ; preds = %if.then9
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2572
  %loop11 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 1, !dbg !2572
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop11, align 8, !dbg !2572
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 1, !dbg !2572
  %15 = load i32, i32* %active_handles, align 8, !dbg !2572
  %dec = add i32 %15, -1, !dbg !2572
  store i32 %dec, i32* %active_handles, align 8, !dbg !2572
  br label %do.end, !dbg !2572

do.end:                                           ; preds = %do.body10
  br label %if.end12, !dbg !2575

if.end12:                                         ; preds = %do.end, %if.end
  br label %do.end13, !dbg !2577

do.end13:                                         ; preds = %if.end12, %if.then
  %16 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2579
  %io_watcher14 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %16, i32 0, i32 13, !dbg !2581
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher14, i32 0, i32 5, !dbg !2582
  %17 = load i32, i32* %fd, align 8, !dbg !2582
  %cmp15 = icmp ne i32 %17, -1, !dbg !2583
  br i1 %cmp15, label %if.then16, label %if.end27, !dbg !2584

if.then16:                                        ; preds = %do.end13
  %18 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2585
  %io_watcher17 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %18, i32 0, i32 13, !dbg !2588
  %fd18 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher17, i32 0, i32 5, !dbg !2589
  %19 = load i32, i32* %fd18, align 8, !dbg !2589
  %cmp19 = icmp sgt i32 %19, 2, !dbg !2590
  br i1 %cmp19, label %if.then20, label %if.end24, !dbg !2591

if.then20:                                        ; preds = %if.then16
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2592
  %io_watcher21 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %20, i32 0, i32 13, !dbg !2593
  %fd22 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher21, i32 0, i32 5, !dbg !2594
  %21 = load i32, i32* %fd22, align 8, !dbg !2594
  %call23 = call i32 @uv__close(i32 %21), !dbg !2595
  br label %if.end24, !dbg !2595

if.end24:                                         ; preds = %if.then20, %if.then16
  %22 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2596
  %io_watcher25 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %22, i32 0, i32 13, !dbg !2597
  %fd26 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher25, i32 0, i32 5, !dbg !2598
  store i32 -1, i32* %fd26, align 8, !dbg !2599
  br label %if.end27, !dbg !2600

if.end27:                                         ; preds = %if.end24, %do.end13
  %23 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2601
  %accepted_fd = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %23, i32 0, i32 18, !dbg !2603
  %24 = load i32, i32* %accepted_fd, align 4, !dbg !2603
  %cmp28 = icmp ne i32 %24, -1, !dbg !2604
  br i1 %cmp28, label %if.then29, label %if.end33, !dbg !2605

if.then29:                                        ; preds = %if.end27
  %25 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2606
  %accepted_fd30 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %25, i32 0, i32 18, !dbg !2608
  %26 = load i32, i32* %accepted_fd30, align 4, !dbg !2608
  %call31 = call i32 @uv__close(i32 %26), !dbg !2609
  %27 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2610
  %accepted_fd32 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %27, i32 0, i32 18, !dbg !2611
  store i32 -1, i32* %accepted_fd32, align 4, !dbg !2612
  br label %if.end33, !dbg !2613

if.end33:                                         ; preds = %if.then29, %if.end27
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2614
  %queued_fds34 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 19, !dbg !2616
  %29 = load i8*, i8** %queued_fds34, align 8, !dbg !2616
  %cmp35 = icmp ne i8* %29, null, !dbg !2617
  br i1 %cmp35, label %if.then36, label %if.end42, !dbg !2618

if.then36:                                        ; preds = %if.end33
  %30 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2619
  %queued_fds37 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %30, i32 0, i32 19, !dbg !2621
  %31 = load i8*, i8** %queued_fds37, align 8, !dbg !2621
  %32 = bitcast i8* %31 to %struct.uv__stream_queued_fds_s*, !dbg !2619
  store %struct.uv__stream_queued_fds_s* %32, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !2622
  store i32 0, i32* %i, align 4, !dbg !2623
  br label %for.cond, !dbg !2625

for.cond:                                         ; preds = %for.inc, %if.then36
  %33 = load i32, i32* %i, align 4, !dbg !2626
  %34 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !2629
  %offset = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %34, i32 0, i32 1, !dbg !2630
  %35 = load i32, i32* %offset, align 4, !dbg !2630
  %cmp38 = icmp ult i32 %33, %35, !dbg !2631
  br i1 %cmp38, label %for.body, label %for.end, !dbg !2632

for.body:                                         ; preds = %for.cond
  %36 = load i32, i32* %i, align 4, !dbg !2633
  %idxprom = zext i32 %36 to i64, !dbg !2634
  %37 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !2634
  %fds = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %37, i32 0, i32 2, !dbg !2635
  %arrayidx = getelementptr inbounds [1 x i32], [1 x i32]* %fds, i64 0, i64 %idxprom, !dbg !2634
  %38 = load i32, i32* %arrayidx, align 4, !dbg !2634
  %call39 = call i32 @uv__close(i32 %38), !dbg !2636
  br label %for.inc, !dbg !2636

for.inc:                                          ; preds = %for.body
  %39 = load i32, i32* %i, align 4, !dbg !2637
  %inc = add i32 %39, 1, !dbg !2637
  store i32 %inc, i32* %i, align 4, !dbg !2637
  br label %for.cond, !dbg !2639

for.end:                                          ; preds = %for.cond
  %40 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2640
  %queued_fds40 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %40, i32 0, i32 19, !dbg !2641
  %41 = load i8*, i8** %queued_fds40, align 8, !dbg !2641
  call void @uv__free(i8* %41), !dbg !2642
  %42 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2643
  %queued_fds41 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %42, i32 0, i32 19, !dbg !2644
  store i8* null, i8** %queued_fds41, align 8, !dbg !2645
  br label %if.end42, !dbg !2646

if.end42:                                         ; preds = %for.end, %if.end33
  %43 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2647
  %io_watcher43 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %43, i32 0, i32 13, !dbg !2647
  %call44 = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher43, i32 5), !dbg !2647
  %tobool = icmp ne i32 %call44, 0, !dbg !2647
  br i1 %tobool, label %cond.false46, label %cond.true45, !dbg !2647

cond.true45:                                      ; preds = %if.end42
  br label %cond.end47, !dbg !2648

cond.false46:                                     ; preds = %if.end42
  call void @__assert_fail(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1657, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @__PRETTY_FUNCTION__.uv__stream_close, i32 0, i32 0)) #7, !dbg !2650
  unreachable, !dbg !2650
                                                  ; No predecessors!
  br label %cond.end47, !dbg !2652

cond.end47:                                       ; preds = %44, %cond.true45
  ret void, !dbg !2654
}

declare void @uv__io_close(%struct.uv_loop_s*, %struct.uv__io_s*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_stream_set_blocking(%struct.uv_stream_s* %handle, i32 %blocking) #0 !dbg !654 {
entry:
  %handle.addr = alloca %struct.uv_stream_s*, align 8
  %blocking.addr = alloca i32, align 4
  store %struct.uv_stream_s* %handle, %struct.uv_stream_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %handle.addr, metadata !2655, metadata !699), !dbg !2656
  store i32 %blocking, i32* %blocking.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %blocking.addr, metadata !2657, metadata !699), !dbg !2658
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle.addr, align 8, !dbg !2659
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 13, !dbg !2659
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2659
  %1 = load i32, i32* %fd, align 8, !dbg !2659
  %2 = load i32, i32* %blocking.addr, align 4, !dbg !2660
  %tobool = icmp ne i32 %2, 0, !dbg !2661
  %lnot = xor i1 %tobool, true, !dbg !2661
  %lnot.ext = zext i1 %lnot to i32, !dbg !2661
  %call = call i32 @uv__nonblock_ioctl(i32 %1, i32 %lnot.ext), !dbg !2662
  ret i32 %call, !dbg !2663
}

declare i32 @uv__nonblock_ioctl(i32, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__stream_connect(%struct.uv_stream_s* %stream) #0 !dbg !663 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %error = alloca i32, align 4
  %req = alloca %struct.uv_connect_s*, align 8
  %errorsize = alloca i32, align 4
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2664, metadata !699), !dbg !2665
  call void @llvm.dbg.declare(metadata i32* %error, metadata !2666, metadata !699), !dbg !2667
  call void @llvm.dbg.declare(metadata %struct.uv_connect_s** %req, metadata !2668, metadata !699), !dbg !2669
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2670
  %connect_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 11, !dbg !2671
  %1 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req, align 8, !dbg !2671
  store %struct.uv_connect_s* %1, %struct.uv_connect_s** %req, align 8, !dbg !2669
  call void @llvm.dbg.declare(metadata i32* %errorsize, metadata !2672, metadata !699), !dbg !2673
  store i32 4, i32* %errorsize, align 4, !dbg !2673
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2674
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 2, !dbg !2674
  %3 = load i32, i32* %type, align 8, !dbg !2674
  %cmp = icmp eq i32 %3, 12, !dbg !2674
  br i1 %cmp, label %cond.true, label %lor.lhs.false, !dbg !2674

lor.lhs.false:                                    ; preds = %entry
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2675
  %type1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 2, !dbg !2675
  %5 = load i32, i32* %type1, align 8, !dbg !2675
  %cmp2 = icmp eq i32 %5, 7, !dbg !2675
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !2675

cond.true:                                        ; preds = %lor.lhs.false, %entry
  br label %cond.end, !dbg !2677

cond.false:                                       ; preds = %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.26, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1335, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_connect, i32 0, i32 0)) #7, !dbg !2679
  unreachable, !dbg !2679
                                                  ; No predecessors!
  br label %cond.end, !dbg !2681

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2683
  %tobool = icmp ne %struct.uv_connect_s* %7, null, !dbg !2683
  br i1 %tobool, label %cond.true3, label %cond.false4, !dbg !2683

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !2684

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.27, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1336, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_connect, i32 0, i32 0)) #7, !dbg !2685
  unreachable, !dbg !2685
                                                  ; No predecessors!
  br label %cond.end5, !dbg !2686

cond.end5:                                        ; preds = %8, %cond.true3
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2687
  %delayed_error = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 17, !dbg !2689
  %10 = load i32, i32* %delayed_error, align 8, !dbg !2689
  %tobool6 = icmp ne i32 %10, 0, !dbg !2687
  br i1 %tobool6, label %if.then, label %if.else, !dbg !2690

if.then:                                          ; preds = %cond.end5
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2691
  %delayed_error7 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 17, !dbg !2693
  %12 = load i32, i32* %delayed_error7, align 8, !dbg !2693
  store i32 %12, i32* %error, align 4, !dbg !2694
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2695
  %delayed_error8 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 17, !dbg !2696
  store i32 0, i32* %delayed_error8, align 8, !dbg !2697
  br label %if.end, !dbg !2698

if.else:                                          ; preds = %cond.end5
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2699
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %14, i32 0, i32 13, !dbg !2699
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2699
  %15 = load i32, i32* %fd, align 8, !dbg !2699
  %cmp9 = icmp sge i32 %15, 0, !dbg !2699
  br i1 %cmp9, label %cond.true10, label %cond.false11, !dbg !2699

cond.true10:                                      ; preds = %if.else
  br label %cond.end12, !dbg !2701

cond.false11:                                     ; preds = %if.else
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1347, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_connect, i32 0, i32 0)) #7, !dbg !2703
  unreachable, !dbg !2703
                                                  ; No predecessors!
  br label %cond.end12, !dbg !2705

cond.end12:                                       ; preds = %16, %cond.true10
  %17 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2707
  %io_watcher13 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %17, i32 0, i32 13, !dbg !2707
  %fd14 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher13, i32 0, i32 5, !dbg !2707
  %18 = load i32, i32* %fd14, align 8, !dbg !2707
  %19 = bitcast i32* %error to i8*, !dbg !2708
  %call = call i32 @getsockopt(i32 %18, i32 1, i32 4, i8* %19, i32* %errorsize) #8, !dbg !2709
  %20 = load i32, i32* %error, align 4, !dbg !2710
  %sub = sub nsw i32 0, %20, !dbg !2711
  store i32 %sub, i32* %error, align 4, !dbg !2712
  br label %if.end

if.end:                                           ; preds = %cond.end12, %if.then
  %21 = load i32, i32* %error, align 4, !dbg !2713
  %cmp15 = icmp eq i32 %21, -115, !dbg !2715
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !2716

if.then16:                                        ; preds = %if.end
  br label %if.end62, !dbg !2717

if.end17:                                         ; preds = %if.end
  %22 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2718
  %connect_req18 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %22, i32 0, i32 11, !dbg !2719
  store %struct.uv_connect_s* null, %struct.uv_connect_s** %connect_req18, align 8, !dbg !2720
  br label %do.body, !dbg !2721

do.body:                                          ; preds = %if.end17
  %23 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2722
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %23, i32 0, i32 1, !dbg !2722
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2722
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 3, !dbg !2722
  %25 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2722
  %loop19 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %25, i32 0, i32 1, !dbg !2722
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop19, align 8, !dbg !2722
  %active_reqs20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 3, !dbg !2722
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs20, i64 0, i64 0, !dbg !2722
  %27 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2722
  %28 = load [2 x i8*]*, [2 x i8*]** %27, align 8, !dbg !2722
  %cmp21 = icmp eq [2 x i8*]* %active_reqs, %28, !dbg !2722
  %conv = zext i1 %cmp21 to i32, !dbg !2722
  %cmp22 = icmp eq i32 %conv, 0, !dbg !2722
  br i1 %cmp22, label %cond.true24, label %cond.false25, !dbg !2722

cond.true24:                                      ; preds = %do.body
  br label %cond.end26, !dbg !2725

cond.false25:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1360, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__stream_connect, i32 0, i32 0)) #7, !dbg !2727
  unreachable, !dbg !2727
                                                  ; No predecessors!
  br label %cond.end26, !dbg !2729

cond.end26:                                       ; preds = %29, %cond.true24
  br label %do.body27, !dbg !2731

do.body27:                                        ; preds = %cond.end26
  %30 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2733
  %active_queue = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %30, i32 0, i32 2, !dbg !2733
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2733
  %31 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !2733
  %32 = load [2 x i8*]*, [2 x i8*]** %31, align 8, !dbg !2733
  %33 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2733
  %active_queue29 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %33, i32 0, i32 2, !dbg !2733
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue29, i64 0, i64 1, !dbg !2733
  %34 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !2733
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !2733
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %35, i64 0, i64 0, !dbg !2733
  %36 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !2733
  store [2 x i8*]* %32, [2 x i8*]** %36, align 8, !dbg !2733
  %37 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2733
  %active_queue32 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %37, i32 0, i32 2, !dbg !2733
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue32, i64 0, i64 1, !dbg !2733
  %38 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !2733
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !2733
  %40 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2733
  %active_queue34 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %40, i32 0, i32 2, !dbg !2733
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue34, i64 0, i64 0, !dbg !2733
  %41 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !2733
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 8, !dbg !2733
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 1, !dbg !2733
  %43 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2733
  store [2 x i8*]* %39, [2 x i8*]** %43, align 8, !dbg !2733
  br label %do.end, !dbg !2733

do.end:                                           ; preds = %do.body27
  br label %do.end37, !dbg !2736

do.end37:                                         ; preds = %do.end
  %44 = load i32, i32* %error, align 4, !dbg !2738
  %cmp38 = icmp slt i32 %44, 0, !dbg !2740
  br i1 %cmp38, label %if.then45, label %lor.lhs.false40, !dbg !2741

lor.lhs.false40:                                  ; preds = %do.end37
  %45 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2742
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %45, i32 0, i32 14, !dbg !2742
  %46 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2742
  %write_queue41 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %46, i32 0, i32 14, !dbg !2742
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue41, i64 0, i64 0, !dbg !2742
  %47 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !2742
  %48 = load [2 x i8*]*, [2 x i8*]** %47, align 8, !dbg !2742
  %cmp43 = icmp eq [2 x i8*]* %write_queue, %48, !dbg !2742
  br i1 %cmp43, label %if.then45, label %if.end48, !dbg !2744

if.then45:                                        ; preds = %lor.lhs.false40, %do.end37
  %49 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2745
  %loop46 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %49, i32 0, i32 1, !dbg !2747
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop46, align 8, !dbg !2747
  %51 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2748
  %io_watcher47 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %51, i32 0, i32 13, !dbg !2749
  call void @uv__io_stop(%struct.uv_loop_s* %50, %struct.uv__io_s* %io_watcher47, i32 4), !dbg !2750
  br label %if.end48, !dbg !2751

if.end48:                                         ; preds = %if.then45, %lor.lhs.false40
  %52 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2752
  %cb = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %52, i32 0, i32 4, !dbg !2754
  %53 = load void (%struct.uv_connect_s*, i32)*, void (%struct.uv_connect_s*, i32)** %cb, align 8, !dbg !2754
  %tobool49 = icmp ne void (%struct.uv_connect_s*, i32)* %53, null, !dbg !2752
  br i1 %tobool49, label %if.then50, label %if.end52, !dbg !2755

if.then50:                                        ; preds = %if.end48
  %54 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2756
  %cb51 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %54, i32 0, i32 4, !dbg !2757
  %55 = load void (%struct.uv_connect_s*, i32)*, void (%struct.uv_connect_s*, i32)** %cb51, align 8, !dbg !2757
  %56 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req, align 8, !dbg !2758
  %57 = load i32, i32* %error, align 4, !dbg !2759
  call void %55(%struct.uv_connect_s* %56, i32 %57), !dbg !2756
  br label %if.end52, !dbg !2756

if.end52:                                         ; preds = %if.then50, %if.end48
  %58 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2760
  %io_watcher53 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %58, i32 0, i32 13, !dbg !2760
  %fd54 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher53, i32 0, i32 5, !dbg !2760
  %59 = load i32, i32* %fd54, align 8, !dbg !2760
  %cmp55 = icmp eq i32 %59, -1, !dbg !2762
  br i1 %cmp55, label %if.then57, label %if.end58, !dbg !2763

if.then57:                                        ; preds = %if.end52
  br label %if.end62, !dbg !2764

if.end58:                                         ; preds = %if.end52
  %60 = load i32, i32* %error, align 4, !dbg !2765
  %cmp59 = icmp slt i32 %60, 0, !dbg !2767
  br i1 %cmp59, label %if.then61, label %if.end62, !dbg !2768

if.then61:                                        ; preds = %if.end58
  %61 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2769
  call void @uv__stream_flush_write_queue(%struct.uv_stream_s* %61, i32 -125), !dbg !2771
  %62 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2772
  call void @uv__write_callbacks(%struct.uv_stream_s* %62), !dbg !2773
  br label %if.end62, !dbg !2774

if.end62:                                         ; preds = %if.then16, %if.then57, %if.then61, %if.end58
  ret void, !dbg !2775
}

; Function Attrs: nounwind uwtable
define internal void @uv__read(%struct.uv_stream_s* %stream) #0 !dbg !664 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %buf = alloca %struct.uv_buf_t, align 8
  %nread = alloca i64, align 8
  %msg = alloca %struct.msghdr, align 8
  %cmsg_space = alloca [272 x i8], align 16
  %count = alloca i32, align 4
  %err = alloca i32, align 4
  %is_ipc = alloca i32, align 4
  %coerce = alloca %struct.uv_buf_t, align 8
  %buflen = alloca i64, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !2776, metadata !699), !dbg !2777
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t* %buf, metadata !2778, metadata !699), !dbg !2779
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2780, metadata !699), !dbg !2781
  call void @llvm.dbg.declare(metadata %struct.msghdr* %msg, metadata !2782, metadata !699), !dbg !2783
  call void @llvm.dbg.declare(metadata [272 x i8]* %cmsg_space, metadata !2784, metadata !699), !dbg !2788
  call void @llvm.dbg.declare(metadata i32* %count, metadata !2789, metadata !699), !dbg !2790
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2791, metadata !699), !dbg !2792
  call void @llvm.dbg.declare(metadata i32* %is_ipc, metadata !2793, metadata !699), !dbg !2794
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2795
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 7, !dbg !2796
  %1 = load i32, i32* %flags, align 8, !dbg !2797
  %and = and i32 %1, -257, !dbg !2797
  store i32 %and, i32* %flags, align 8, !dbg !2797
  store i32 32, i32* %count, align 4, !dbg !2798
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2799
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 2, !dbg !2800
  %3 = load i32, i32* %type, align 8, !dbg !2800
  %cmp = icmp eq i32 %3, 7, !dbg !2801
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2802

land.rhs:                                         ; preds = %entry
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2803
  %5 = bitcast %struct.uv_stream_s* %4 to %struct.uv_pipe_s*, !dbg !2805
  %ipc = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %5, i32 0, i32 20, !dbg !2805
  %6 = load i32, i32* %ipc, align 8, !dbg !2805
  %tobool = icmp ne i32 %6, 0, !dbg !2806
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %7 = phi i1 [ false, %entry ], [ %tobool, %land.rhs ]
  %land.ext = zext i1 %7 to i32, !dbg !2807
  store i32 %land.ext, i32* %is_ipc, align 4, !dbg !2809
  br label %while.cond, !dbg !2810

while.cond:                                       ; preds = %if.end134, %land.end
  %8 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2811
  %read_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %8, i32 0, i32 10, !dbg !2812
  %9 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb, align 8, !dbg !2812
  %tobool1 = icmp ne void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)* %9, null, !dbg !2811
  br i1 %tobool1, label %land.lhs.true, label %land.end7, !dbg !2813

land.lhs.true:                                    ; preds = %while.cond
  %10 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2814
  %flags2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %10, i32 0, i32 7, !dbg !2815
  %11 = load i32, i32* %flags2, align 8, !dbg !2815
  %and3 = and i32 %11, 4, !dbg !2816
  %tobool4 = icmp ne i32 %and3, 0, !dbg !2816
  br i1 %tobool4, label %land.rhs5, label %land.end7, !dbg !2817

land.rhs5:                                        ; preds = %land.lhs.true
  %12 = load i32, i32* %count, align 4, !dbg !2818
  %dec = add nsw i32 %12, -1, !dbg !2818
  store i32 %dec, i32* %count, align 4, !dbg !2818
  %cmp6 = icmp sgt i32 %12, 0, !dbg !2819
  br label %land.end7

land.end7:                                        ; preds = %land.rhs5, %land.lhs.true, %while.cond
  %13 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond ], [ %cmp6, %land.rhs5 ]
  br i1 %13, label %while.body, label %while.end, !dbg !2820

while.body:                                       ; preds = %land.end7
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2821
  %alloc_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %14, i32 0, i32 9, !dbg !2821
  %15 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb, align 8, !dbg !2821
  %cmp9 = icmp ne void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)* %15, null, !dbg !2821
  br i1 %cmp9, label %cond.true, label %cond.false, !dbg !2821

cond.true:                                        ; preds = %while.body
  br label %cond.end, !dbg !2823

cond.false:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.28, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1132, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.uv__read, i32 0, i32 0)) #7, !dbg !2825
  unreachable, !dbg !2825
                                                  ; No predecessors!
  br label %cond.end, !dbg !2827

cond.end:                                         ; preds = %16, %cond.true
  %call = call { i8*, i64 } @uv_buf_init(i8* null, i32 0), !dbg !2829
  %17 = bitcast %struct.uv_buf_t* %coerce to { i8*, i64 }*, !dbg !2829
  %18 = getelementptr inbounds { i8*, i64 }, { i8*, i64 }* %17, i32 0, i32 0, !dbg !2829
  %19 = extractvalue { i8*, i64 } %call, 0, !dbg !2829
  store i8* %19, i8** %18, align 8, !dbg !2829
  %20 = getelementptr inbounds { i8*, i64 }, { i8*, i64 }* %17, i32 0, i32 1, !dbg !2829
  %21 = extractvalue { i8*, i64 } %call, 1, !dbg !2829
  store i64 %21, i64* %20, align 8, !dbg !2829
  %22 = bitcast %struct.uv_buf_t* %buf to i8*, !dbg !2829
  %23 = bitcast %struct.uv_buf_t* %coerce to i8*, !dbg !2829
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %22, i8* %23, i64 16, i32 8, i1 false), !dbg !2830
  %24 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2831
  %alloc_cb10 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %24, i32 0, i32 9, !dbg !2832
  %25 = load void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)** %alloc_cb10, align 8, !dbg !2832
  %26 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2833
  %27 = bitcast %struct.uv_stream_s* %26 to %struct.uv_handle_s*, !dbg !2834
  call void %25(%struct.uv_handle_s* %27, i64 65536, %struct.uv_buf_t* %buf), !dbg !2831
  %base = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 0, !dbg !2835
  %28 = load i8*, i8** %base, align 8, !dbg !2835
  %cmp11 = icmp eq i8* %28, null, !dbg !2837
  br i1 %cmp11, label %if.then, label %lor.lhs.false, !dbg !2838

lor.lhs.false:                                    ; preds = %cond.end
  %len = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 1, !dbg !2839
  %29 = load i64, i64* %len, align 8, !dbg !2839
  %cmp12 = icmp eq i64 %29, 0, !dbg !2841
  br i1 %cmp12, label %if.then, label %if.end, !dbg !2842

if.then:                                          ; preds = %lor.lhs.false, %cond.end
  %30 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2843
  %read_cb13 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %30, i32 0, i32 10, !dbg !2845
  %31 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb13, align 8, !dbg !2845
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2846
  call void %31(%struct.uv_stream_s* %32, i64 -105, %struct.uv_buf_t* %buf), !dbg !2843
  br label %while.end, !dbg !2847

if.end:                                           ; preds = %lor.lhs.false
  %base14 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 0, !dbg !2848
  %33 = load i8*, i8** %base14, align 8, !dbg !2848
  %cmp15 = icmp ne i8* %33, null, !dbg !2848
  br i1 %cmp15, label %cond.true16, label %cond.false17, !dbg !2848

cond.true16:                                      ; preds = %if.end
  br label %cond.end18, !dbg !2849

cond.false17:                                     ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1142, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.uv__read, i32 0, i32 0)) #7, !dbg !2850
  unreachable, !dbg !2850
                                                  ; No predecessors!
  br label %cond.end18, !dbg !2851

cond.end18:                                       ; preds = %34, %cond.true16
  %35 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2852
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %35, i32 0, i32 13, !dbg !2852
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !2852
  %36 = load i32, i32* %fd, align 8, !dbg !2852
  %cmp19 = icmp sge i32 %36, 0, !dbg !2852
  br i1 %cmp19, label %cond.true20, label %cond.false21, !dbg !2852

cond.true20:                                      ; preds = %cond.end18
  br label %cond.end22, !dbg !2853

cond.false21:                                     ; preds = %cond.end18
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1143, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.uv__read, i32 0, i32 0)) #7, !dbg !2854
  unreachable, !dbg !2854
                                                  ; No predecessors!
  br label %cond.end22, !dbg !2855

cond.end22:                                       ; preds = %37, %cond.true20
  %38 = load i32, i32* %is_ipc, align 4, !dbg !2856
  %tobool23 = icmp ne i32 %38, 0, !dbg !2856
  br i1 %tobool23, label %if.else, label %if.then24, !dbg !2858

if.then24:                                        ; preds = %cond.end22
  br label %do.body, !dbg !2859

do.body:                                          ; preds = %land.end34, %if.then24
  %39 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2861
  %io_watcher25 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %39, i32 0, i32 13, !dbg !2861
  %fd26 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher25, i32 0, i32 5, !dbg !2861
  %40 = load i32, i32* %fd26, align 8, !dbg !2861
  %base27 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 0, !dbg !2863
  %41 = load i8*, i8** %base27, align 8, !dbg !2863
  %len28 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 1, !dbg !2864
  %42 = load i64, i64* %len28, align 8, !dbg !2864
  %call29 = call i64 @read(i32 %40, i8* %41, i64 %42), !dbg !2865
  store i64 %call29, i64* %nread, align 8, !dbg !2866
  br label %do.cond, !dbg !2867

do.cond:                                          ; preds = %do.body
  %43 = load i64, i64* %nread, align 8, !dbg !2868
  %cmp30 = icmp slt i64 %43, 0, !dbg !2869
  br i1 %cmp30, label %land.rhs31, label %land.end34, !dbg !2870

land.rhs31:                                       ; preds = %do.cond
  %call32 = call i32* @__errno_location() #1, !dbg !2871
  %44 = load i32, i32* %call32, align 4, !dbg !2871
  %cmp33 = icmp eq i32 %44, 4, !dbg !2873
  br label %land.end34

land.end34:                                       ; preds = %land.rhs31, %do.cond
  %45 = phi i1 [ false, %do.cond ], [ %cmp33, %land.rhs31 ]
  br i1 %45, label %do.body, label %do.end, !dbg !2874

do.end:                                           ; preds = %land.end34
  br label %if.end48, !dbg !2876

if.else:                                          ; preds = %cond.end22
  %msg_flags = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 6, !dbg !2877
  store i32 0, i32* %msg_flags, align 8, !dbg !2879
  %46 = bitcast %struct.uv_buf_t* %buf to %struct.iovec*, !dbg !2880
  %msg_iov = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 2, !dbg !2881
  store %struct.iovec* %46, %struct.iovec** %msg_iov, align 8, !dbg !2882
  %msg_iovlen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 3, !dbg !2883
  store i64 1, i64* %msg_iovlen, align 8, !dbg !2884
  %msg_name = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 0, !dbg !2885
  store i8* null, i8** %msg_name, align 8, !dbg !2886
  %msg_namelen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 1, !dbg !2887
  store i32 0, i32* %msg_namelen, align 8, !dbg !2888
  %msg_controllen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 5, !dbg !2889
  store i64 272, i64* %msg_controllen, align 8, !dbg !2890
  %arraydecay = getelementptr inbounds [272 x i8], [272 x i8]* %cmsg_space, i32 0, i32 0, !dbg !2891
  %msg_control = getelementptr inbounds %struct.msghdr, %struct.msghdr* %msg, i32 0, i32 4, !dbg !2892
  store i8* %arraydecay, i8** %msg_control, align 8, !dbg !2893
  br label %do.body36, !dbg !2894

do.body36:                                        ; preds = %land.end45, %if.else
  %47 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2895
  %io_watcher37 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %47, i32 0, i32 13, !dbg !2895
  %fd38 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher37, i32 0, i32 5, !dbg !2895
  %48 = load i32, i32* %fd38, align 8, !dbg !2895
  %call39 = call i64 @uv__recvmsg(i32 %48, %struct.msghdr* %msg, i32 0), !dbg !2897
  store i64 %call39, i64* %nread, align 8, !dbg !2898
  br label %do.cond40, !dbg !2899

do.cond40:                                        ; preds = %do.body36
  %49 = load i64, i64* %nread, align 8, !dbg !2900
  %cmp41 = icmp slt i64 %49, 0, !dbg !2901
  br i1 %cmp41, label %land.rhs42, label %land.end45, !dbg !2902

land.rhs42:                                       ; preds = %do.cond40
  %call43 = call i32* @__errno_location() #1, !dbg !2903
  %50 = load i32, i32* %call43, align 4, !dbg !2903
  %cmp44 = icmp eq i32 %50, 4, !dbg !2905
  br label %land.end45

land.end45:                                       ; preds = %land.rhs42, %do.cond40
  %51 = phi i1 [ false, %do.cond40 ], [ %cmp44, %land.rhs42 ]
  br i1 %51, label %do.body36, label %do.end47, !dbg !2906

do.end47:                                         ; preds = %land.end45
  br label %if.end48

if.end48:                                         ; preds = %do.end47, %do.end
  %52 = load i64, i64* %nread, align 8, !dbg !2908
  %cmp49 = icmp slt i64 %52, 0, !dbg !2910
  br i1 %cmp49, label %if.then50, label %if.else111, !dbg !2911

if.then50:                                        ; preds = %if.end48
  %call51 = call i32* @__errno_location() #1, !dbg !2912
  %53 = load i32, i32* %call51, align 4, !dbg !2912
  %cmp52 = icmp eq i32 %53, 11, !dbg !2915
  br i1 %cmp52, label %if.then56, label %lor.lhs.false53, !dbg !2916

lor.lhs.false53:                                  ; preds = %if.then50
  %call54 = call i32* @__errno_location() #1, !dbg !2917
  %54 = load i32, i32* %call54, align 4, !dbg !2917
  %cmp55 = icmp eq i32 %54, 11, !dbg !2919
  br i1 %cmp55, label %if.then56, label %if.else64, !dbg !2920

if.then56:                                        ; preds = %lor.lhs.false53, %if.then50
  %55 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2921
  %flags57 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %55, i32 0, i32 7, !dbg !2924
  %56 = load i32, i32* %flags57, align 8, !dbg !2924
  %and58 = and i32 %56, 4, !dbg !2925
  %tobool59 = icmp ne i32 %and58, 0, !dbg !2925
  br i1 %tobool59, label %if.then60, label %if.end62, !dbg !2926

if.then60:                                        ; preds = %if.then56
  %57 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2927
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %57, i32 0, i32 1, !dbg !2929
  %58 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !2929
  %59 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2930
  %io_watcher61 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %59, i32 0, i32 13, !dbg !2931
  call void @uv__io_start(%struct.uv_loop_s* %58, %struct.uv__io_s* %io_watcher61, i32 1), !dbg !2932
  %60 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2933
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %60), !dbg !2934
  br label %if.end62, !dbg !2935

if.end62:                                         ; preds = %if.then60, %if.then56
  %61 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2936
  %read_cb63 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %61, i32 0, i32 10, !dbg !2937
  %62 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb63, align 8, !dbg !2937
  %63 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2938
  call void %62(%struct.uv_stream_s* %63, i64 0, %struct.uv_buf_t* %buf), !dbg !2936
  br label %if.end110, !dbg !2939

if.else64:                                        ; preds = %lor.lhs.false53
  %64 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2940
  %read_cb65 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %64, i32 0, i32 10, !dbg !2942
  %65 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb65, align 8, !dbg !2942
  %66 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2943
  %call66 = call i32* @__errno_location() #1, !dbg !2944
  %67 = load i32, i32* %call66, align 4, !dbg !2944
  %sub = sub nsw i32 0, %67, !dbg !2945
  %conv = sext i32 %sub to i64, !dbg !2945
  call void %65(%struct.uv_stream_s* %66, i64 %conv, %struct.uv_buf_t* %buf), !dbg !2946
  %68 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2948
  %flags67 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %68, i32 0, i32 7, !dbg !2950
  %69 = load i32, i32* %flags67, align 8, !dbg !2950
  %and68 = and i32 %69, 4, !dbg !2951
  %tobool69 = icmp ne i32 %and68, 0, !dbg !2951
  br i1 %tobool69, label %if.then70, label %if.end109, !dbg !2952

if.then70:                                        ; preds = %if.else64
  %70 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2953
  %flags71 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %70, i32 0, i32 7, !dbg !2955
  %71 = load i32, i32* %flags71, align 8, !dbg !2956
  %and72 = and i32 %71, -5, !dbg !2956
  store i32 %and72, i32* %flags71, align 8, !dbg !2956
  %72 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2957
  %loop73 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %72, i32 0, i32 1, !dbg !2958
  %73 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop73, align 8, !dbg !2958
  %74 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2959
  %io_watcher74 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %74, i32 0, i32 13, !dbg !2960
  call void @uv__io_stop(%struct.uv_loop_s* %73, %struct.uv__io_s* %io_watcher74, i32 1), !dbg !2961
  %75 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2962
  %io_watcher75 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %75, i32 0, i32 13, !dbg !2964
  %call76 = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher75, i32 4), !dbg !2965
  %tobool77 = icmp ne i32 %call76, 0, !dbg !2965
  br i1 %tobool77, label %if.end108, label %if.then78, !dbg !2966

if.then78:                                        ; preds = %if.then70
  br label %do.body79, !dbg !2967

do.body79:                                        ; preds = %if.then78
  %76 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2968
  %flags80 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %76, i32 0, i32 7, !dbg !2968
  %77 = load i32, i32* %flags80, align 8, !dbg !2968
  %and81 = and i32 %77, 0, !dbg !2968
  %cmp82 = icmp eq i32 %and81, 0, !dbg !2968
  br i1 %cmp82, label %cond.true84, label %cond.false85, !dbg !2968

cond.true84:                                      ; preds = %do.body79
  br label %cond.end86, !dbg !2971

cond.false85:                                     ; preds = %do.body79
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1183, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.uv__read, i32 0, i32 0)) #7, !dbg !2973
  unreachable, !dbg !2973
                                                  ; No predecessors!
  br label %cond.end86, !dbg !2975

cond.end86:                                       ; preds = %78, %cond.true84
  %79 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2977
  %flags87 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %79, i32 0, i32 7, !dbg !2977
  %80 = load i32, i32* %flags87, align 8, !dbg !2977
  %and88 = and i32 %80, 16384, !dbg !2977
  %cmp89 = icmp eq i32 %and88, 0, !dbg !2977
  br i1 %cmp89, label %if.then91, label %if.end92, !dbg !2977

if.then91:                                        ; preds = %cond.end86
  br label %do.end107, !dbg !2980

if.end92:                                         ; preds = %cond.end86
  %81 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2982
  %flags93 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %81, i32 0, i32 7, !dbg !2982
  %82 = load i32, i32* %flags93, align 8, !dbg !2982
  %and94 = and i32 %82, -16385, !dbg !2982
  store i32 %and94, i32* %flags93, align 8, !dbg !2982
  %83 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2982
  %flags95 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %83, i32 0, i32 7, !dbg !2982
  %84 = load i32, i32* %flags95, align 8, !dbg !2982
  %and96 = and i32 %84, 8192, !dbg !2982
  %cmp97 = icmp ne i32 %and96, 0, !dbg !2982
  br i1 %cmp97, label %if.then99, label %if.end105, !dbg !2982

if.then99:                                        ; preds = %if.end92
  br label %do.body100, !dbg !2984

do.body100:                                       ; preds = %if.then99
  %85 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2987
  %loop101 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %85, i32 0, i32 1, !dbg !2987
  %86 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop101, align 8, !dbg !2987
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %86, i32 0, i32 1, !dbg !2987
  %87 = load i32, i32* %active_handles, align 8, !dbg !2987
  %dec102 = add i32 %87, -1, !dbg !2987
  store i32 %dec102, i32* %active_handles, align 8, !dbg !2987
  br label %do.end104, !dbg !2987

do.end104:                                        ; preds = %do.body100
  br label %if.end105, !dbg !2990

if.end105:                                        ; preds = %do.end104, %if.end92
  br label %do.end107, !dbg !2992

do.end107:                                        ; preds = %if.end105, %if.then91
  br label %if.end108, !dbg !2994

if.end108:                                        ; preds = %do.end107, %if.then70
  %88 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !2996
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %88), !dbg !2997
  br label %if.end109, !dbg !2998

if.end109:                                        ; preds = %if.end108, %if.else64
  br label %if.end110

if.end110:                                        ; preds = %if.end109, %if.end62
  br label %while.end, !dbg !2999

if.else111:                                       ; preds = %if.end48
  %89 = load i64, i64* %nread, align 8, !dbg !3000
  %cmp112 = icmp eq i64 %89, 0, !dbg !3002
  br i1 %cmp112, label %if.then114, label %if.else115, !dbg !3003

if.then114:                                       ; preds = %if.else111
  %90 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3004
  call void @uv__stream_eof(%struct.uv_stream_s* %90, %struct.uv_buf_t* %buf), !dbg !3006
  br label %while.end, !dbg !3007

if.else115:                                       ; preds = %if.else111
  call void @llvm.dbg.declare(metadata i64* %buflen, metadata !3008, metadata !699), !dbg !3010
  %len116 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %buf, i32 0, i32 1, !dbg !3011
  %91 = load i64, i64* %len116, align 8, !dbg !3011
  store i64 %91, i64* %buflen, align 8, !dbg !3010
  %92 = load i32, i32* %is_ipc, align 4, !dbg !3012
  %tobool117 = icmp ne i32 %92, 0, !dbg !3012
  br i1 %tobool117, label %if.then118, label %if.end126, !dbg !3014

if.then118:                                       ; preds = %if.else115
  %93 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3015
  %call119 = call i32 @uv__stream_recv_cmsg(%struct.uv_stream_s* %93, %struct.msghdr* %msg), !dbg !3017
  store i32 %call119, i32* %err, align 4, !dbg !3018
  %94 = load i32, i32* %err, align 4, !dbg !3019
  %cmp120 = icmp ne i32 %94, 0, !dbg !3021
  br i1 %cmp120, label %if.then122, label %if.end125, !dbg !3022

if.then122:                                       ; preds = %if.then118
  %95 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3023
  %read_cb123 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %95, i32 0, i32 10, !dbg !3025
  %96 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb123, align 8, !dbg !3025
  %97 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3026
  %98 = load i32, i32* %err, align 4, !dbg !3027
  %conv124 = sext i32 %98 to i64, !dbg !3027
  call void %96(%struct.uv_stream_s* %97, i64 %conv124, %struct.uv_buf_t* %buf), !dbg !3023
  br label %while.end, !dbg !3028

if.end125:                                        ; preds = %if.then118
  br label %if.end126, !dbg !3029

if.end126:                                        ; preds = %if.end125, %if.else115
  %99 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3030
  %read_cb127 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %99, i32 0, i32 10, !dbg !3031
  %100 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb127, align 8, !dbg !3031
  %101 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3032
  %102 = load i64, i64* %nread, align 8, !dbg !3033
  call void %100(%struct.uv_stream_s* %101, i64 %102, %struct.uv_buf_t* %buf), !dbg !3030
  %103 = load i64, i64* %nread, align 8, !dbg !3034
  %104 = load i64, i64* %buflen, align 8, !dbg !3036
  %cmp128 = icmp slt i64 %103, %104, !dbg !3037
  br i1 %cmp128, label %if.then130, label %if.end132, !dbg !3038

if.then130:                                       ; preds = %if.end126
  %105 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3039
  %flags131 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %105, i32 0, i32 7, !dbg !3041
  %106 = load i32, i32* %flags131, align 8, !dbg !3042
  %or = or i32 %106, 256, !dbg !3042
  store i32 %or, i32* %flags131, align 8, !dbg !3042
  br label %while.end, !dbg !3043

if.end132:                                        ; preds = %if.end126
  br label %if.end133

if.end133:                                        ; preds = %if.end132
  br label %if.end134

if.end134:                                        ; preds = %if.end133
  br label %while.cond, !dbg !3044

while.end:                                        ; preds = %if.then, %if.end110, %if.then114, %if.then122, %if.then130, %land.end7
  ret void, !dbg !3046
}

; Function Attrs: nounwind uwtable
define internal void @uv__stream_eof(%struct.uv_stream_s* %stream, %struct.uv_buf_t* %buf) #0 !dbg !681 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %buf.addr = alloca %struct.uv_buf_t*, align 8
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !3047, metadata !699), !dbg !3048
  store %struct.uv_buf_t* %buf, %struct.uv_buf_t** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %buf.addr, metadata !3049, metadata !699), !dbg !3050
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3051
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 7, !dbg !3052
  %1 = load i32, i32* %flags, align 8, !dbg !3053
  %or = or i32 %1, 512, !dbg !3053
  store i32 %or, i32* %flags, align 8, !dbg !3053
  %2 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3054
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %2, i32 0, i32 1, !dbg !3055
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !3055
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3056
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %4, i32 0, i32 13, !dbg !3057
  call void @uv__io_stop(%struct.uv_loop_s* %3, %struct.uv__io_s* %io_watcher, i32 1), !dbg !3058
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3059
  %io_watcher1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 13, !dbg !3061
  %call = call i32 @uv__io_active(%struct.uv__io_s* %io_watcher1, i32 4), !dbg !3062
  %tobool = icmp ne i32 %call, 0, !dbg !3062
  br i1 %tobool, label %if.end17, label %if.then, !dbg !3063

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !3064

do.body:                                          ; preds = %if.then
  %6 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3065
  %flags2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %6, i32 0, i32 7, !dbg !3065
  %7 = load i32, i32* %flags2, align 8, !dbg !3065
  %and = and i32 %7, 0, !dbg !3065
  %cmp = icmp eq i32 %and, 0, !dbg !3065
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3065

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !3068

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1003, i8* getelementptr inbounds ([53 x i8], [53 x i8]* @__PRETTY_FUNCTION__.uv__stream_eof, i32 0, i32 0)) #7, !dbg !3070
  unreachable, !dbg !3070
                                                  ; No predecessors!
  br label %cond.end, !dbg !3072

cond.end:                                         ; preds = %8, %cond.true
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3074
  %flags3 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 7, !dbg !3074
  %10 = load i32, i32* %flags3, align 8, !dbg !3074
  %and4 = and i32 %10, 16384, !dbg !3074
  %cmp5 = icmp eq i32 %and4, 0, !dbg !3074
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !3074

if.then6:                                         ; preds = %cond.end
  br label %do.end16, !dbg !3077

if.end:                                           ; preds = %cond.end
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3079
  %flags7 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 7, !dbg !3079
  %12 = load i32, i32* %flags7, align 8, !dbg !3079
  %and8 = and i32 %12, -16385, !dbg !3079
  store i32 %and8, i32* %flags7, align 8, !dbg !3079
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3079
  %flags9 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 7, !dbg !3079
  %14 = load i32, i32* %flags9, align 8, !dbg !3079
  %and10 = and i32 %14, 8192, !dbg !3079
  %cmp11 = icmp ne i32 %and10, 0, !dbg !3079
  br i1 %cmp11, label %if.then12, label %if.end15, !dbg !3079

if.then12:                                        ; preds = %if.end
  br label %do.body13, !dbg !3081

do.body13:                                        ; preds = %if.then12
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3084
  %loop14 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %15, i32 0, i32 1, !dbg !3084
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop14, align 8, !dbg !3084
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 1, !dbg !3084
  %17 = load i32, i32* %active_handles, align 8, !dbg !3084
  %dec = add i32 %17, -1, !dbg !3084
  store i32 %dec, i32* %active_handles, align 8, !dbg !3084
  br label %do.end, !dbg !3084

do.end:                                           ; preds = %do.body13
  br label %if.end15, !dbg !3087

if.end15:                                         ; preds = %do.end, %if.end
  br label %do.end16, !dbg !3089

do.end16:                                         ; preds = %if.end15, %if.then6
  br label %if.end17, !dbg !3091

if.end17:                                         ; preds = %do.end16, %entry
  %18 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3093
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %18), !dbg !3094
  %19 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3095
  %read_cb = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %19, i32 0, i32 10, !dbg !3096
  %20 = load void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)** %read_cb, align 8, !dbg !3096
  %21 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3097
  %22 = load %struct.uv_buf_t*, %struct.uv_buf_t** %buf.addr, align 8, !dbg !3098
  call void %20(%struct.uv_stream_s* %21, i64 -4095, %struct.uv_buf_t* %22), !dbg !3095
  %23 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3099
  %flags18 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %23, i32 0, i32 7, !dbg !3100
  %24 = load i32, i32* %flags18, align 8, !dbg !3101
  %and19 = and i32 %24, -5, !dbg !3101
  store i32 %and19, i32* %flags18, align 8, !dbg !3101
  ret void, !dbg !3102
}

; Function Attrs: nounwind uwtable
define internal void @uv__drain(%struct.uv_stream_s* %stream) #0 !dbg !684 {
entry:
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %req = alloca %struct.uv_shutdown_s*, align 8
  %err = alloca i32, align 4
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !3103, metadata !699), !dbg !3104
  call void @llvm.dbg.declare(metadata %struct.uv_shutdown_s** %req, metadata !3105, metadata !699), !dbg !3106
  call void @llvm.dbg.declare(metadata i32* %err, metadata !3107, metadata !699), !dbg !3108
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3109
  %write_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 14, !dbg !3109
  %1 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3109
  %write_queue1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %1, i32 0, i32 14, !dbg !3109
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_queue1, i64 0, i64 0, !dbg !3109
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !3109
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !3109
  %cmp = icmp eq [2 x i8*]* %write_queue, %3, !dbg !3109
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3109

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !3110

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([106 x i8], [106 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 666, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__drain, i32 0, i32 0)) #7, !dbg !3112
  unreachable, !dbg !3112
                                                  ; No predecessors!
  br label %cond.end, !dbg !3114

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3116
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %5, i32 0, i32 1, !dbg !3117
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !3117
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3118
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 13, !dbg !3119
  call void @uv__io_stop(%struct.uv_loop_s* %6, %struct.uv__io_s* %io_watcher, i32 4), !dbg !3120
  %8 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3121
  call void @uv__stream_osx_interrupt_select(%struct.uv_stream_s* %8), !dbg !3122
  %9 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3123
  %flags = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %9, i32 0, i32 7, !dbg !3125
  %10 = load i32, i32* %flags, align 8, !dbg !3125
  %and = and i32 %10, 8, !dbg !3126
  %tobool = icmp ne i32 %and, 0, !dbg !3126
  br i1 %tobool, label %land.lhs.true, label %if.end52, !dbg !3127

land.lhs.true:                                    ; preds = %cond.end
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3128
  %flags2 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 7, !dbg !3129
  %12 = load i32, i32* %flags2, align 8, !dbg !3129
  %and3 = and i32 %12, 1, !dbg !3130
  %tobool4 = icmp ne i32 %and3, 0, !dbg !3130
  br i1 %tobool4, label %if.end52, label %land.lhs.true5, !dbg !3131

land.lhs.true5:                                   ; preds = %land.lhs.true
  %13 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3132
  %flags6 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %13, i32 0, i32 7, !dbg !3133
  %14 = load i32, i32* %flags6, align 8, !dbg !3133
  %and7 = and i32 %14, 16, !dbg !3134
  %tobool8 = icmp ne i32 %and7, 0, !dbg !3134
  br i1 %tobool8, label %if.end52, label %if.then, !dbg !3135

if.then:                                          ; preds = %land.lhs.true5
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3136
  %shutdown_req = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %15, i32 0, i32 12, !dbg !3136
  %16 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req, align 8, !dbg !3136
  %tobool9 = icmp ne %struct.uv_shutdown_s* %16, null, !dbg !3136
  br i1 %tobool9, label %cond.true10, label %cond.false11, !dbg !3136

cond.true10:                                      ; preds = %if.then
  br label %cond.end12, !dbg !3138

cond.false11:                                     ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.33, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 674, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__drain, i32 0, i32 0)) #7, !dbg !3140
  unreachable, !dbg !3140
                                                  ; No predecessors!
  br label %cond.end12, !dbg !3142

cond.end12:                                       ; preds = %17, %cond.true10
  %18 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3144
  %shutdown_req13 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %18, i32 0, i32 12, !dbg !3145
  %19 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %shutdown_req13, align 8, !dbg !3145
  store %struct.uv_shutdown_s* %19, %struct.uv_shutdown_s** %req, align 8, !dbg !3146
  %20 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3147
  %shutdown_req14 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %20, i32 0, i32 12, !dbg !3148
  store %struct.uv_shutdown_s* null, %struct.uv_shutdown_s** %shutdown_req14, align 8, !dbg !3149
  %21 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3150
  %flags15 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %21, i32 0, i32 7, !dbg !3151
  %22 = load i32, i32* %flags15, align 8, !dbg !3152
  %and16 = and i32 %22, -9, !dbg !3152
  store i32 %and16, i32* %flags15, align 8, !dbg !3152
  br label %do.body, !dbg !3153

do.body:                                          ; preds = %cond.end12
  %23 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3154
  %loop17 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %23, i32 0, i32 1, !dbg !3154
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop17, align 8, !dbg !3154
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 3, !dbg !3154
  %25 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3154
  %loop18 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %25, i32 0, i32 1, !dbg !3154
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop18, align 8, !dbg !3154
  %active_reqs19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 3, !dbg !3154
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs19, i64 0, i64 0, !dbg !3154
  %27 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !3154
  %28 = load [2 x i8*]*, [2 x i8*]** %27, align 8, !dbg !3154
  %cmp21 = icmp eq [2 x i8*]* %active_reqs, %28, !dbg !3154
  %conv = zext i1 %cmp21 to i32, !dbg !3154
  %cmp22 = icmp eq i32 %conv, 0, !dbg !3154
  br i1 %cmp22, label %cond.true24, label %cond.false25, !dbg !3154

cond.true24:                                      ; preds = %do.body
  br label %cond.end26, !dbg !3157

cond.false25:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 679, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv__drain, i32 0, i32 0)) #7, !dbg !3159
  unreachable, !dbg !3159
                                                  ; No predecessors!
  br label %cond.end26, !dbg !3161

cond.end26:                                       ; preds = %29, %cond.true24
  br label %do.body27, !dbg !3163

do.body27:                                        ; preds = %cond.end26
  %30 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3165
  %active_queue = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %30, i32 0, i32 2, !dbg !3165
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !3165
  %31 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !3165
  %32 = load [2 x i8*]*, [2 x i8*]** %31, align 8, !dbg !3165
  %33 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3165
  %active_queue29 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %33, i32 0, i32 2, !dbg !3165
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue29, i64 0, i64 1, !dbg !3165
  %34 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !3165
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !3165
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %35, i64 0, i64 0, !dbg !3165
  %36 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !3165
  store [2 x i8*]* %32, [2 x i8*]** %36, align 8, !dbg !3165
  %37 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3165
  %active_queue32 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %37, i32 0, i32 2, !dbg !3165
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue32, i64 0, i64 1, !dbg !3165
  %38 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !3165
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !3165
  %40 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3165
  %active_queue34 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %40, i32 0, i32 2, !dbg !3165
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue34, i64 0, i64 0, !dbg !3165
  %41 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !3165
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 8, !dbg !3165
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 1, !dbg !3165
  %43 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !3165
  store [2 x i8*]* %39, [2 x i8*]** %43, align 8, !dbg !3165
  br label %do.end, !dbg !3165

do.end:                                           ; preds = %do.body27
  br label %do.end37, !dbg !3168

do.end37:                                         ; preds = %do.end
  store i32 0, i32* %err, align 4, !dbg !3170
  %44 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3171
  %io_watcher38 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %44, i32 0, i32 13, !dbg !3171
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher38, i32 0, i32 5, !dbg !3171
  %45 = load i32, i32* %fd, align 8, !dbg !3171
  %call = call i32 @shutdown(i32 %45, i32 1) #8, !dbg !3173
  %tobool39 = icmp ne i32 %call, 0, !dbg !3173
  br i1 %tobool39, label %if.then40, label %if.end, !dbg !3174

if.then40:                                        ; preds = %do.end37
  %call41 = call i32* @__errno_location() #1, !dbg !3175
  %46 = load i32, i32* %call41, align 4, !dbg !3175
  %sub = sub nsw i32 0, %46, !dbg !3176
  store i32 %sub, i32* %err, align 4, !dbg !3177
  br label %if.end, !dbg !3178

if.end:                                           ; preds = %if.then40, %do.end37
  %47 = load i32, i32* %err, align 4, !dbg !3179
  %cmp42 = icmp eq i32 %47, 0, !dbg !3181
  br i1 %cmp42, label %if.then44, label %if.end46, !dbg !3182

if.then44:                                        ; preds = %if.end
  %48 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3183
  %flags45 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %48, i32 0, i32 7, !dbg !3184
  %49 = load i32, i32* %flags45, align 8, !dbg !3185
  %or = or i32 %49, 16, !dbg !3185
  store i32 %or, i32* %flags45, align 8, !dbg !3185
  br label %if.end46, !dbg !3183

if.end46:                                         ; preds = %if.then44, %if.end
  %50 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3186
  %cb = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %50, i32 0, i32 5, !dbg !3188
  %51 = load void (%struct.uv_shutdown_s*, i32)*, void (%struct.uv_shutdown_s*, i32)** %cb, align 8, !dbg !3188
  %cmp47 = icmp ne void (%struct.uv_shutdown_s*, i32)* %51, null, !dbg !3189
  br i1 %cmp47, label %if.then49, label %if.end51, !dbg !3190

if.then49:                                        ; preds = %if.end46
  %52 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3191
  %cb50 = getelementptr inbounds %struct.uv_shutdown_s, %struct.uv_shutdown_s* %52, i32 0, i32 5, !dbg !3192
  %53 = load void (%struct.uv_shutdown_s*, i32)*, void (%struct.uv_shutdown_s*, i32)** %cb50, align 8, !dbg !3192
  %54 = load %struct.uv_shutdown_s*, %struct.uv_shutdown_s** %req, align 8, !dbg !3193
  %55 = load i32, i32* %err, align 4, !dbg !3194
  call void %53(%struct.uv_shutdown_s* %54, i32 %55), !dbg !3191
  br label %if.end51, !dbg !3191

if.end51:                                         ; preds = %if.then49, %if.end46
  br label %if.end52, !dbg !3195

if.end52:                                         ; preds = %if.end51, %land.lhs.true5, %land.lhs.true, %cond.end
  ret void, !dbg !3196
}

declare { i8*, i64 } @uv_buf_init(i8*, i32) #2

declare i64 @read(i32, i8*, i64) #2

declare i64 @uv__recvmsg(i32, %struct.msghdr*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__stream_recv_cmsg(%struct.uv_stream_s* %stream, %struct.msghdr* %msg) #0 !dbg !665 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %msg.addr = alloca %struct.msghdr*, align 8
  %cmsg = alloca %struct.cmsghdr*, align 8
  %start = alloca i8*, align 8
  %end = alloca i8*, align 8
  %err = alloca i32, align 4
  %pv = alloca i8*, align 8
  %pi = alloca i32*, align 8
  %i = alloca i32, align 4
  %count = alloca i32, align 4
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !3197, metadata !699), !dbg !3198
  store %struct.msghdr* %msg, %struct.msghdr** %msg.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.msghdr** %msg.addr, metadata !3199, metadata !699), !dbg !3200
  call void @llvm.dbg.declare(metadata %struct.cmsghdr** %cmsg, metadata !3201, metadata !699), !dbg !3202
  %0 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !3203
  %msg_controllen = getelementptr inbounds %struct.msghdr, %struct.msghdr* %0, i32 0, i32 5, !dbg !3203
  %1 = load i64, i64* %msg_controllen, align 8, !dbg !3203
  %cmp = icmp uge i64 %1, 16, !dbg !3203
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3203

cond.true:                                        ; preds = %entry
  %2 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !3205
  %msg_control = getelementptr inbounds %struct.msghdr, %struct.msghdr* %2, i32 0, i32 4, !dbg !3205
  %3 = load i8*, i8** %msg_control, align 8, !dbg !3205
  %4 = bitcast i8* %3 to %struct.cmsghdr*, !dbg !3205
  br label %cond.end, !dbg !3205

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !3207

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %struct.cmsghdr* [ %4, %cond.true ], [ null, %cond.false ], !dbg !3209
  store %struct.cmsghdr* %cond, %struct.cmsghdr** %cmsg, align 8, !dbg !3211
  br label %for.cond, !dbg !3212

for.cond:                                         ; preds = %for.inc43, %cond.end
  %5 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3213
  %cmp1 = icmp ne %struct.cmsghdr* %5, null, !dbg !3216
  br i1 %cmp1, label %for.body, label %for.end45, !dbg !3217

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i8** %start, metadata !3218, metadata !699), !dbg !3220
  call void @llvm.dbg.declare(metadata i8** %end, metadata !3221, metadata !699), !dbg !3222
  call void @llvm.dbg.declare(metadata i32* %err, metadata !3223, metadata !699), !dbg !3224
  call void @llvm.dbg.declare(metadata i8** %pv, metadata !3225, metadata !699), !dbg !3226
  call void @llvm.dbg.declare(metadata i32** %pi, metadata !3227, metadata !699), !dbg !3228
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3229, metadata !699), !dbg !3230
  call void @llvm.dbg.declare(metadata i32* %count, metadata !3231, metadata !699), !dbg !3232
  %6 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3233
  %cmsg_type = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %6, i32 0, i32 2, !dbg !3235
  %7 = load i32, i32* %cmsg_type, align 4, !dbg !3235
  %cmp2 = icmp ne i32 %7, 1, !dbg !3236
  br i1 %cmp2, label %if.then, label %if.end, !dbg !3237

if.then:                                          ; preds = %for.body
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3238
  %9 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3240
  %cmsg_type3 = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %9, i32 0, i32 2, !dbg !3241
  %10 = load i32, i32* %cmsg_type3, align 4, !dbg !3241
  %call = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %8, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.30, i32 0, i32 0), i32 %10), !dbg !3242
  br label %for.inc43, !dbg !3243

if.end:                                           ; preds = %for.body
  %11 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3244
  %__cmsg_data = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %11, i32 0, i32 3, !dbg !3244
  %arraydecay = getelementptr inbounds [0 x i8], [0 x i8]* %__cmsg_data, i32 0, i32 0, !dbg !3244
  store i8* %arraydecay, i8** %pv, align 8, !dbg !3245
  %12 = load i8*, i8** %pv, align 8, !dbg !3246
  %13 = bitcast i8* %12 to i32*, !dbg !3246
  store i32* %13, i32** %pi, align 8, !dbg !3247
  %14 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3248
  %15 = bitcast %struct.cmsghdr* %14 to i8*, !dbg !3249
  store i8* %15, i8** %start, align 8, !dbg !3250
  %16 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3251
  %17 = bitcast %struct.cmsghdr* %16 to i8*, !dbg !3252
  %18 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3253
  %cmsg_len = getelementptr inbounds %struct.cmsghdr, %struct.cmsghdr* %18, i32 0, i32 0, !dbg !3254
  %19 = load i64, i64* %cmsg_len, align 8, !dbg !3254
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %19, !dbg !3255
  store i8* %add.ptr, i8** %end, align 8, !dbg !3256
  store i32 0, i32* %count, align 4, !dbg !3257
  br label %while.cond, !dbg !3258

while.cond:                                       ; preds = %while.body, %if.end
  %20 = load i8*, i8** %start, align 8, !dbg !3259
  %21 = load i32, i32* %count, align 4, !dbg !3261
  %conv = zext i32 %21 to i64, !dbg !3261
  %mul = mul i64 %conv, 4, !dbg !3261
  %add = add i64 16, %mul, !dbg !3261
  %add.ptr4 = getelementptr inbounds i8, i8* %20, i64 %add, !dbg !3262
  %22 = load i8*, i8** %end, align 8, !dbg !3263
  %cmp5 = icmp ult i8* %add.ptr4, %22, !dbg !3264
  br i1 %cmp5, label %while.body, label %while.end, !dbg !3265

while.body:                                       ; preds = %while.cond
  %23 = load i32, i32* %count, align 4, !dbg !3266
  %inc = add i32 %23, 1, !dbg !3266
  store i32 %inc, i32* %count, align 4, !dbg !3266
  br label %while.cond, !dbg !3267

while.end:                                        ; preds = %while.cond
  %24 = load i8*, i8** %start, align 8, !dbg !3269
  %25 = load i32, i32* %count, align 4, !dbg !3269
  %conv7 = zext i32 %25 to i64, !dbg !3269
  %mul8 = mul i64 %conv7, 4, !dbg !3269
  %add9 = add i64 16, %mul8, !dbg !3269
  %add.ptr10 = getelementptr inbounds i8, i8* %24, i64 %add9, !dbg !3269
  %26 = load i8*, i8** %end, align 8, !dbg !3269
  %cmp11 = icmp eq i8* %add.ptr10, %26, !dbg !3269
  br i1 %cmp11, label %cond.true13, label %cond.false14, !dbg !3269

cond.true13:                                      ; preds = %while.end
  br label %cond.end15, !dbg !3270

cond.false14:                                     ; preds = %while.end
  call void @__assert_fail(i8* getelementptr inbounds ([127 x i8], [127 x i8]* @.str.31, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.3, i32 0, i32 0), i32 1081, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv__stream_recv_cmsg, i32 0, i32 0)) #7, !dbg !3271
  unreachable, !dbg !3271
                                                  ; No predecessors!
  br label %cond.end15, !dbg !3272

cond.end15:                                       ; preds = %27, %cond.true13
  store i32 0, i32* %i, align 4, !dbg !3274
  br label %for.cond16, !dbg !3276

for.cond16:                                       ; preds = %for.inc40, %cond.end15
  %28 = load i32, i32* %i, align 4, !dbg !3277
  %29 = load i32, i32* %count, align 4, !dbg !3280
  %cmp17 = icmp ult i32 %28, %29, !dbg !3281
  br i1 %cmp17, label %for.body19, label %for.end42, !dbg !3282

for.body19:                                       ; preds = %for.cond16
  %30 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3283
  %accepted_fd = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %30, i32 0, i32 18, !dbg !3286
  %31 = load i32, i32* %accepted_fd, align 4, !dbg !3286
  %cmp20 = icmp ne i32 %31, -1, !dbg !3287
  br i1 %cmp20, label %if.then22, label %if.else, !dbg !3288

if.then22:                                        ; preds = %for.body19
  %32 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3289
  %33 = load i32, i32* %i, align 4, !dbg !3291
  %idxprom = zext i32 %33 to i64, !dbg !3292
  %34 = load i32*, i32** %pi, align 8, !dbg !3292
  %arrayidx = getelementptr inbounds i32, i32* %34, i64 %idxprom, !dbg !3292
  %35 = load i32, i32* %arrayidx, align 4, !dbg !3292
  %call23 = call i32 @uv__stream_queue_fd(%struct.uv_stream_s* %32, i32 %35), !dbg !3293
  store i32 %call23, i32* %err, align 4, !dbg !3294
  %36 = load i32, i32* %err, align 4, !dbg !3295
  %cmp24 = icmp ne i32 %36, 0, !dbg !3297
  br i1 %cmp24, label %if.then26, label %if.end35, !dbg !3298

if.then26:                                        ; preds = %if.then22
  br label %for.cond27, !dbg !3299

for.cond27:                                       ; preds = %for.inc, %if.then26
  %37 = load i32, i32* %i, align 4, !dbg !3301
  %38 = load i32, i32* %count, align 4, !dbg !3305
  %cmp28 = icmp ult i32 %37, %38, !dbg !3306
  br i1 %cmp28, label %for.body30, label %for.end, !dbg !3307

for.body30:                                       ; preds = %for.cond27
  %39 = load i32, i32* %i, align 4, !dbg !3308
  %idxprom31 = zext i32 %39 to i64, !dbg !3309
  %40 = load i32*, i32** %pi, align 8, !dbg !3309
  %arrayidx32 = getelementptr inbounds i32, i32* %40, i64 %idxprom31, !dbg !3309
  %41 = load i32, i32* %arrayidx32, align 4, !dbg !3309
  %call33 = call i32 @uv__close(i32 %41), !dbg !3310
  br label %for.inc, !dbg !3310

for.inc:                                          ; preds = %for.body30
  %42 = load i32, i32* %i, align 4, !dbg !3311
  %inc34 = add i32 %42, 1, !dbg !3311
  store i32 %inc34, i32* %i, align 4, !dbg !3311
  br label %for.cond27, !dbg !3313

for.end:                                          ; preds = %for.cond27
  %43 = load i32, i32* %err, align 4, !dbg !3314
  store i32 %43, i32* %retval, align 4, !dbg !3315
  br label %return, !dbg !3315

if.end35:                                         ; preds = %if.then22
  br label %if.end39, !dbg !3316

if.else:                                          ; preds = %for.body19
  %44 = load i32, i32* %i, align 4, !dbg !3317
  %idxprom36 = zext i32 %44 to i64, !dbg !3319
  %45 = load i32*, i32** %pi, align 8, !dbg !3319
  %arrayidx37 = getelementptr inbounds i32, i32* %45, i64 %idxprom36, !dbg !3319
  %46 = load i32, i32* %arrayidx37, align 4, !dbg !3319
  %47 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3320
  %accepted_fd38 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %47, i32 0, i32 18, !dbg !3321
  store i32 %46, i32* %accepted_fd38, align 4, !dbg !3322
  br label %if.end39

if.end39:                                         ; preds = %if.else, %if.end35
  br label %for.inc40, !dbg !3323

for.inc40:                                        ; preds = %if.end39
  %48 = load i32, i32* %i, align 4, !dbg !3324
  %inc41 = add i32 %48, 1, !dbg !3324
  store i32 %inc41, i32* %i, align 4, !dbg !3324
  br label %for.cond16, !dbg !3326

for.end42:                                        ; preds = %for.cond16
  br label %for.inc43, !dbg !3327

for.inc43:                                        ; preds = %for.end42, %if.then
  %49 = load %struct.msghdr*, %struct.msghdr** %msg.addr, align 8, !dbg !3328
  %50 = load %struct.cmsghdr*, %struct.cmsghdr** %cmsg, align 8, !dbg !3328
  %call44 = call %struct.cmsghdr* @__cmsg_nxthdr(%struct.msghdr* %49, %struct.cmsghdr* %50) #8, !dbg !3328
  store %struct.cmsghdr* %call44, %struct.cmsghdr** %cmsg, align 8, !dbg !3330
  br label %for.cond, !dbg !3331

for.end45:                                        ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !3332
  br label %return, !dbg !3332

return:                                           ; preds = %for.end45, %for.end
  %51 = load i32, i32* %retval, align 4, !dbg !3333
  ret i32 %51, !dbg !3333
}

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__stream_queue_fd(%struct.uv_stream_s* %stream, i32 %fd) #0 !dbg !680 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct.uv_stream_s*, align 8
  %fd.addr = alloca i32, align 4
  %queued_fds = alloca %struct.uv__stream_queued_fds_s*, align 8
  %queue_size = alloca i32, align 4
  store %struct.uv_stream_s* %stream, %struct.uv_stream_s** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream.addr, metadata !3334, metadata !699), !dbg !3335
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !3336, metadata !699), !dbg !3337
  call void @llvm.dbg.declare(metadata %struct.uv__stream_queued_fds_s** %queued_fds, metadata !3338, metadata !699), !dbg !3339
  call void @llvm.dbg.declare(metadata i32* %queue_size, metadata !3340, metadata !699), !dbg !3341
  %0 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3342
  %queued_fds1 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %0, i32 0, i32 19, !dbg !3343
  %1 = load i8*, i8** %queued_fds1, align 8, !dbg !3343
  %2 = bitcast i8* %1 to %struct.uv__stream_queued_fds_s*, !dbg !3342
  store %struct.uv__stream_queued_fds_s* %2, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3344
  %3 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3345
  %cmp = icmp eq %struct.uv__stream_queued_fds_s* %3, null, !dbg !3347
  br i1 %cmp, label %if.then, label %if.else, !dbg !3348

if.then:                                          ; preds = %entry
  store i32 8, i32* %queue_size, align 4, !dbg !3349
  %4 = load i32, i32* %queue_size, align 4, !dbg !3351
  %sub = sub i32 %4, 1, !dbg !3352
  %conv = zext i32 %sub to i64, !dbg !3353
  %mul = mul i64 %conv, 4, !dbg !3354
  %add = add i64 %mul, 12, !dbg !3355
  %call = call i8* @uv__malloc(i64 %add), !dbg !3356
  %5 = bitcast i8* %call to %struct.uv__stream_queued_fds_s*, !dbg !3356
  store %struct.uv__stream_queued_fds_s* %5, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3357
  %6 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3358
  %cmp2 = icmp eq %struct.uv__stream_queued_fds_s* %6, null, !dbg !3360
  br i1 %cmp2, label %if.then4, label %if.end, !dbg !3361

if.then4:                                         ; preds = %if.then
  store i32 -12, i32* %retval, align 4, !dbg !3362
  br label %return, !dbg !3362

if.end:                                           ; preds = %if.then
  %7 = load i32, i32* %queue_size, align 4, !dbg !3363
  %8 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3364
  %size = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %8, i32 0, i32 0, !dbg !3365
  store i32 %7, i32* %size, align 4, !dbg !3366
  %9 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3367
  %offset = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %9, i32 0, i32 1, !dbg !3368
  store i32 0, i32* %offset, align 4, !dbg !3369
  %10 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3370
  %11 = bitcast %struct.uv__stream_queued_fds_s* %10 to i8*, !dbg !3370
  %12 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3371
  %queued_fds5 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %12, i32 0, i32 19, !dbg !3372
  store i8* %11, i8** %queued_fds5, align 8, !dbg !3373
  br label %if.end25, !dbg !3374

if.else:                                          ; preds = %entry
  %13 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3375
  %size6 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %13, i32 0, i32 0, !dbg !3378
  %14 = load i32, i32* %size6, align 4, !dbg !3378
  %15 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3379
  %offset7 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %15, i32 0, i32 1, !dbg !3380
  %16 = load i32, i32* %offset7, align 4, !dbg !3380
  %cmp8 = icmp eq i32 %14, %16, !dbg !3381
  br i1 %cmp8, label %if.then10, label %if.end24, !dbg !3375

if.then10:                                        ; preds = %if.else
  %17 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3382
  %size11 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %17, i32 0, i32 0, !dbg !3384
  %18 = load i32, i32* %size11, align 4, !dbg !3384
  %add12 = add i32 %18, 8, !dbg !3385
  store i32 %add12, i32* %queue_size, align 4, !dbg !3386
  %19 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3387
  %20 = bitcast %struct.uv__stream_queued_fds_s* %19 to i8*, !dbg !3387
  %21 = load i32, i32* %queue_size, align 4, !dbg !3388
  %sub13 = sub i32 %21, 1, !dbg !3389
  %conv14 = zext i32 %sub13 to i64, !dbg !3390
  %mul15 = mul i64 %conv14, 4, !dbg !3391
  %add16 = add i64 %mul15, 12, !dbg !3392
  %call17 = call i8* @uv__realloc(i8* %20, i64 %add16), !dbg !3393
  %22 = bitcast i8* %call17 to %struct.uv__stream_queued_fds_s*, !dbg !3393
  store %struct.uv__stream_queued_fds_s* %22, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3394
  %23 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3395
  %cmp18 = icmp eq %struct.uv__stream_queued_fds_s* %23, null, !dbg !3397
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !3398

if.then20:                                        ; preds = %if.then10
  store i32 -12, i32* %retval, align 4, !dbg !3399
  br label %return, !dbg !3399

if.end21:                                         ; preds = %if.then10
  %24 = load i32, i32* %queue_size, align 4, !dbg !3400
  %25 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3401
  %size22 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %25, i32 0, i32 0, !dbg !3402
  store i32 %24, i32* %size22, align 4, !dbg !3403
  %26 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3404
  %27 = bitcast %struct.uv__stream_queued_fds_s* %26 to i8*, !dbg !3404
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream.addr, align 8, !dbg !3405
  %queued_fds23 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 19, !dbg !3406
  store i8* %27, i8** %queued_fds23, align 8, !dbg !3407
  br label %if.end24, !dbg !3408

if.end24:                                         ; preds = %if.end21, %if.else
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %if.end
  %29 = load i32, i32* %fd.addr, align 4, !dbg !3409
  %30 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3410
  %offset26 = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %30, i32 0, i32 1, !dbg !3411
  %31 = load i32, i32* %offset26, align 4, !dbg !3412
  %inc = add i32 %31, 1, !dbg !3412
  store i32 %inc, i32* %offset26, align 4, !dbg !3412
  %idxprom = zext i32 %31 to i64, !dbg !3413
  %32 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !3413
  %fds = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %32, i32 0, i32 2, !dbg !3414
  %arrayidx = getelementptr inbounds [1 x i32], [1 x i32]* %fds, i64 0, i64 %idxprom, !dbg !3413
  store i32 %29, i32* %arrayidx, align 4, !dbg !3415
  store i32 0, i32* %retval, align 4, !dbg !3416
  br label %return, !dbg !3416

return:                                           ; preds = %if.end25, %if.then20, %if.then4
  %33 = load i32, i32* %retval, align 4, !dbg !3417
  ret i32 %33, !dbg !3417
}

; Function Attrs: nounwind
declare %struct.cmsghdr* @__cmsg_nxthdr(%struct.msghdr*, %struct.cmsghdr*) #6

declare i8* @uv__realloc(i8*, i64) #2

; Function Attrs: nounwind
declare i32 @shutdown(i32, i32) #6

declare i32 @uv__getiovmax() #2

declare i64 @sendmsg(i32, %struct.msghdr*, i32) #2

declare i64 @write(i32, i8*, i64) #2

declare i64 @writev(i32, %struct.iovec*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__write_req_finish(%struct.uv_write_s* %req) #0 !dbg !689 {
entry:
  %req.addr = alloca %struct.uv_write_s*, align 8
  %stream = alloca %struct.uv_stream_s*, align 8
  store %struct.uv_write_s* %req, %struct.uv_write_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_write_s** %req.addr, metadata !3418, metadata !699), !dbg !3419
  call void @llvm.dbg.declare(metadata %struct.uv_stream_s** %stream, metadata !3420, metadata !699), !dbg !3421
  %0 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3422
  %handle = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %0, i32 0, i32 6, !dbg !3423
  %1 = load %struct.uv_stream_s*, %struct.uv_stream_s** %handle, align 8, !dbg !3423
  store %struct.uv_stream_s* %1, %struct.uv_stream_s** %stream, align 8, !dbg !3421
  br label %do.body, !dbg !3424

do.body:                                          ; preds = %entry
  %2 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3425
  %queue = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %2, i32 0, i32 7, !dbg !3425
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !3425
  %3 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !3425
  %4 = load [2 x i8*]*, [2 x i8*]** %3, align 8, !dbg !3425
  %5 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3425
  %queue1 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %5, i32 0, i32 7, !dbg !3425
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue1, i64 0, i64 1, !dbg !3425
  %6 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !3425
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !3425
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !3425
  %8 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !3425
  store [2 x i8*]* %4, [2 x i8*]** %8, align 8, !dbg !3425
  %9 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3425
  %queue4 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %9, i32 0, i32 7, !dbg !3425
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue4, i64 0, i64 1, !dbg !3425
  %10 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !3425
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !3425
  %12 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3425
  %queue6 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %12, i32 0, i32 7, !dbg !3425
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue6, i64 0, i64 0, !dbg !3425
  %13 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !3425
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !3425
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 1, !dbg !3425
  %15 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !3425
  store [2 x i8*]* %11, [2 x i8*]** %15, align 8, !dbg !3425
  br label %do.end, !dbg !3425

do.end:                                           ; preds = %do.body
  %16 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3428
  %error = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %16, i32 0, i32 11, !dbg !3430
  %17 = load i32, i32* %error, align 4, !dbg !3430
  %cmp = icmp eq i32 %17, 0, !dbg !3431
  br i1 %cmp, label %if.then, label %if.end13, !dbg !3432

if.then:                                          ; preds = %do.end
  %18 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3433
  %bufs = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %18, i32 0, i32 9, !dbg !3436
  %19 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !3436
  %20 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3437
  %bufsml = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %20, i32 0, i32 12, !dbg !3438
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !3437
  %cmp9 = icmp ne %struct.uv_buf_t* %19, %arraydecay, !dbg !3439
  br i1 %cmp9, label %if.then10, label %if.end, !dbg !3440

if.then10:                                        ; preds = %if.then
  %21 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3441
  %bufs11 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %21, i32 0, i32 9, !dbg !3442
  %22 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs11, align 8, !dbg !3442
  %23 = bitcast %struct.uv_buf_t* %22 to i8*, !dbg !3441
  call void @uv__free(i8* %23), !dbg !3443
  br label %if.end, !dbg !3443

if.end:                                           ; preds = %if.then10, %if.then
  %24 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3444
  %bufs12 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %24, i32 0, i32 9, !dbg !3445
  store %struct.uv_buf_t* null, %struct.uv_buf_t** %bufs12, align 8, !dbg !3446
  br label %if.end13, !dbg !3447

if.end13:                                         ; preds = %if.end, %do.end
  br label %do.body14, !dbg !3448

do.body14:                                        ; preds = %if.end13
  %25 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !3449
  %write_completed_queue = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %25, i32 0, i32 15, !dbg !3449
  %26 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3449
  %queue15 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %26, i32 0, i32 7, !dbg !3449
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue15, i64 0, i64 0, !dbg !3449
  %27 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !3449
  store [2 x i8*]* %write_completed_queue, [2 x i8*]** %27, align 8, !dbg !3449
  %28 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !3449
  %write_completed_queue17 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %28, i32 0, i32 15, !dbg !3449
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue17, i64 0, i64 1, !dbg !3449
  %29 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !3449
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !3449
  %31 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3449
  %queue19 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %31, i32 0, i32 7, !dbg !3449
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue19, i64 0, i64 1, !dbg !3449
  %32 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !3449
  store [2 x i8*]* %30, [2 x i8*]** %32, align 8, !dbg !3449
  %33 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3449
  %queue21 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %33, i32 0, i32 7, !dbg !3449
  %34 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3449
  %queue22 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %34, i32 0, i32 7, !dbg !3449
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue22, i64 0, i64 1, !dbg !3449
  %35 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !3449
  %36 = load [2 x i8*]*, [2 x i8*]** %35, align 8, !dbg !3449
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %36, i64 0, i64 0, !dbg !3449
  %37 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !3449
  store [2 x i8*]* %queue21, [2 x i8*]** %37, align 8, !dbg !3449
  %38 = load %struct.uv_write_s*, %struct.uv_write_s** %req.addr, align 8, !dbg !3449
  %queue25 = getelementptr inbounds %struct.uv_write_s, %struct.uv_write_s* %38, i32 0, i32 7, !dbg !3449
  %39 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !3449
  %write_completed_queue26 = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %39, i32 0, i32 15, !dbg !3449
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %write_completed_queue26, i64 0, i64 1, !dbg !3449
  %40 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !3449
  store [2 x i8*]* %queue25, [2 x i8*]** %40, align 8, !dbg !3449
  br label %do.end28, !dbg !3449

do.end28:                                         ; preds = %do.body14
  %41 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !3452
  %loop = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %41, i32 0, i32 1, !dbg !3453
  %42 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !3453
  %43 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !3454
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %43, i32 0, i32 13, !dbg !3455
  call void @uv__io_feed(%struct.uv_loop_s* %42, %struct.uv__io_s* %io_watcher), !dbg !3456
  ret void, !dbg !3457
}

declare void @uv__io_feed(%struct.uv_loop_s*, %struct.uv__io_s*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!695, !696}
!llvm.ident = !{!697}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !167, subprograms: !604)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/stream.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !38, !46, !65, !77, !156, !161}
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
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 193, size: 32, align: 32, elements: !26)
!26 = !{!27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37}
!27 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!28 = !DIEnumerator(name: "UV_REQ", value: 1)
!29 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!30 = !DIEnumerator(name: "UV_WRITE", value: 3)
!31 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!32 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!33 = !DIEnumerator(name: "UV_FS", value: 6)
!34 = !DIEnumerator(name: "UV_WORK", value: 7)
!35 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!36 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!37 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !39, line: 57, size: 32, align: 32, elements: !40)
!39 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!40 = !{!41, !42, !43, !44, !45}
!41 = !DIEnumerator(name: "UV__SIGNAL_ONE_SHOT", value: 524288)
!42 = !DIEnumerator(name: "UV__HANDLE_INTERNAL", value: 32768)
!43 = !DIEnumerator(name: "UV__HANDLE_ACTIVE", value: 16384)
!44 = !DIEnumerator(name: "UV__HANDLE_REF", value: 8192)
!45 = !DIEnumerator(name: "UV__HANDLE_CLOSING", value: 0)
!46 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !47, line: 124, size: 32, align: 32, elements: !48)
!47 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!48 = !{!49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64}
!49 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!50 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!51 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!52 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!53 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!54 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!55 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!56 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!57 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!58 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!59 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!60 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!61 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!62 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!63 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!64 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!65 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !66, line: 24, size: 32, align: 32, elements: !67)
!66 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!67 = !{!68, !69, !70, !71, !72, !73, !74, !75, !76}
!68 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!69 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!70 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!71 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!72 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!73 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!74 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!75 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!76 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!77 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !78)
!78 = !{!79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155}
!79 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!80 = !DIEnumerator(name: "UV_EACCES", value: -13)
!81 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!82 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!83 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!84 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!85 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!86 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!87 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!88 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!89 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!90 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!91 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!92 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!93 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!94 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!95 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!96 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!97 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!98 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!99 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!100 = !DIEnumerator(name: "UV_EBADF", value: -9)
!101 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!102 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!103 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!104 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!105 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!106 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!107 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!108 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!109 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!110 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!111 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!112 = !DIEnumerator(name: "UV_EINTR", value: -4)
!113 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!114 = !DIEnumerator(name: "UV_EIO", value: -5)
!115 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!116 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!117 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!118 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!119 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!120 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!121 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!122 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!123 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!124 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!125 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!126 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!127 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!128 = !DIEnumerator(name: "UV_ENONET", value: -64)
!129 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!130 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!131 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!132 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!133 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!134 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!135 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!136 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!137 = !DIEnumerator(name: "UV_EPERM", value: -1)
!138 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!139 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!140 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!141 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!142 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!143 = !DIEnumerator(name: "UV_EROFS", value: -30)
!144 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!145 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!146 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!147 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!148 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!149 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!150 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!151 = !DIEnumerator(name: "UV_EOF", value: -4095)
!152 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!153 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!154 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!155 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!156 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !157, line: 299, size: 32, align: 32, elements: !158)
!157 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!158 = !{!159, !160}
!159 = !DIEnumerator(name: "SCM_RIGHTS", value: 1)
!160 = !DIEnumerator(name: "SCM_CREDENTIALS", value: 2)
!161 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !162, line: 52, size: 32, align: 32, elements: !163)
!162 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!163 = !{!164, !165, !166}
!164 = !DIEnumerator(name: "SHUT_RD", value: 0)
!165 = !DIEnumerator(name: "SHUT_WR", value: 1)
!166 = !DIEnumerator(name: "SHUT_RDWR", value: 2)
!167 = !{!168, !374, !173, !378, !380, !424, !395, !487, !526, !554, !586, !587, !412, !593}
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !170)
!170 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !171)
!171 = !{!172, !174, !364, !365, !366, !367, !372, !373}
!172 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !170, file: !4, line: 426, baseType: !173, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !170, file: !4, line: 426, baseType: !175, size: 64, align: 64, offset: 64)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !177)
!177 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !178)
!178 = !{!179, !180, !182, !186, !187, !188, !190, !192, !193, !194, !213, !214, !215, !216, !247, !279, !303, !304, !305, !306, !307, !308, !309, !313, !314, !315, !320, !323, !324, !326, !327, !360, !361, !362, !363}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !177, file: !4, line: 1475, baseType: !173, size: 64, align: 64)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !177, file: !4, line: 1477, baseType: !181, size: 32, align: 32, offset: 64)
!181 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !177, file: !4, line: 1478, baseType: !183, size: 128, align: 64, offset: 128)
!183 = !DICompositeType(tag: DW_TAG_array_type, baseType: !173, size: 128, align: 64, elements: !184)
!184 = !{!185}
!185 = !DISubrange(count: 2)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !177, file: !4, line: 1479, baseType: !183, size: 128, align: 64, offset: 256)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !177, file: !4, line: 1481, baseType: !181, size: 32, align: 32, offset: 384)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !177, file: !4, line: 1482, baseType: !189, size: 64, align: 64, offset: 448)
!189 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !177, file: !4, line: 1482, baseType: !191, size: 32, align: 32, offset: 512)
!191 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 576)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 704)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !177, file: !4, line: 1482, baseType: !195, size: 64, align: 64, offset: 832)
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !197, size: 64, align: 64)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !198, line: 87, baseType: !199)
!198 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!199 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !198, line: 89, size: 448, align: 64, elements: !200)
!200 = !{!201, !208, !209, !210, !211, !212}
!201 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !199, file: !198, line: 90, baseType: !202, size: 64, align: 64)
!202 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !198, line: 84, baseType: !203)
!203 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !204, size: 64, align: 64)
!204 = !DISubroutineType(types: !205)
!205 = !{null, !206, !207, !181}
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !199, size: 64, align: 64)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !199, file: !198, line: 91, baseType: !183, size: 128, align: 64, offset: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !199, file: !198, line: 92, baseType: !183, size: 128, align: 64, offset: 192)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !199, file: !198, line: 93, baseType: !181, size: 32, align: 32, offset: 320)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !199, file: !198, line: 94, baseType: !181, size: 32, align: 32, offset: 352)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !199, file: !198, line: 95, baseType: !191, size: 32, align: 32, offset: 384)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !177, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 896)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !177, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 928)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 960)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !177, file: !4, line: 1482, baseType: !217, size: 320, align: 64, offset: 1088)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !198, line: 129, baseType: !218)
!218 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !219, line: 127, baseType: !220)
!219 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!220 = !DICompositeType(tag: DW_TAG_union_type, file: !219, line: 90, size: 320, align: 64, elements: !221)
!221 = !{!222, !240, !245}
!222 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !220, file: !219, line: 124, baseType: !223, size: 320, align: 64)
!223 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !219, line: 92, size: 320, align: 64, elements: !224)
!224 = !{!225, !226, !227, !228, !229, !230, !232, !233}
!225 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !223, file: !219, line: 94, baseType: !191, size: 32, align: 32)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !223, file: !219, line: 95, baseType: !181, size: 32, align: 32, offset: 32)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !223, file: !219, line: 96, baseType: !191, size: 32, align: 32, offset: 64)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !223, file: !219, line: 98, baseType: !181, size: 32, align: 32, offset: 96)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !223, file: !219, line: 102, baseType: !191, size: 32, align: 32, offset: 128)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !223, file: !219, line: 104, baseType: !231, size: 16, align: 16, offset: 160)
!231 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !223, file: !219, line: 105, baseType: !231, size: 16, align: 16, offset: 176)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !223, file: !219, line: 106, baseType: !234, size: 128, align: 64, offset: 192)
!234 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !219, line: 79, baseType: !235)
!235 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !219, line: 75, size: 128, align: 64, elements: !236)
!236 = !{!237, !239}
!237 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !235, file: !219, line: 77, baseType: !238, size: 64, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !235, file: !219, line: 78, baseType: !238, size: 64, align: 64, offset: 64)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !220, file: !219, line: 125, baseType: !241, size: 320, align: 8)
!241 = !DICompositeType(tag: DW_TAG_array_type, baseType: !242, size: 320, align: 8, elements: !243)
!242 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!243 = !{!244}
!244 = !DISubrange(count: 40)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !220, file: !219, line: 126, baseType: !246, size: 64, align: 64)
!246 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !177, file: !4, line: 1482, baseType: !248, size: 1024, align: 64, offset: 1408)
!248 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !249)
!249 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !250)
!250 = !{!251, !252, !253, !255, !260, !261, !269, !270, !271, !277, !278}
!251 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !249, file: !4, line: 768, baseType: !173, size: 64, align: 64)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !249, file: !4, line: 768, baseType: !175, size: 64, align: 64, offset: 64)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !249, file: !4, line: 768, baseType: !254, size: 32, align: 32, offset: 128)
!254 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !249, file: !4, line: 768, baseType: !256, size: 64, align: 64, offset: 192)
!256 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !257)
!257 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !258, size: 64, align: 64)
!258 = !DISubroutineType(types: !259)
!259 = !{null, !168}
!260 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !249, file: !4, line: 768, baseType: !183, size: 128, align: 64, offset: 256)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !249, file: !4, line: 768, baseType: !262, size: 256, align: 64, offset: 384)
!262 = !DICompositeType(tag: DW_TAG_union_type, scope: !249, file: !4, line: 768, size: 256, align: 64, elements: !263)
!263 = !{!264, !265}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !262, file: !4, line: 768, baseType: !191, size: 32, align: 32)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !262, file: !4, line: 768, baseType: !266, size: 256, align: 64)
!266 = !DICompositeType(tag: DW_TAG_array_type, baseType: !173, size: 256, align: 64, elements: !267)
!267 = !{!268}
!268 = !DISubrange(count: 4)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !249, file: !4, line: 768, baseType: !168, size: 64, align: 64, offset: 640)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !249, file: !4, line: 768, baseType: !181, size: 32, align: 32, offset: 704)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !249, file: !4, line: 769, baseType: !272, size: 64, align: 64, offset: 768)
!272 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !273)
!273 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !274, size: 64, align: 64)
!274 = !DISubroutineType(types: !275)
!275 = !{null, !276}
!276 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !249, file: !4, line: 769, baseType: !183, size: 128, align: 64, offset: 832)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !249, file: !4, line: 769, baseType: !191, size: 32, align: 32, offset: 960)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !177, file: !4, line: 1482, baseType: !280, size: 448, align: 64, offset: 2432)
!280 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !198, line: 130, baseType: !281)
!281 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !219, line: 213, baseType: !282)
!282 = !DICompositeType(tag: DW_TAG_union_type, file: !219, line: 173, size: 448, align: 64, elements: !283)
!283 = !{!284, !298, !302}
!284 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !282, file: !219, line: 192, baseType: !285, size: 448, align: 64)
!285 = !DICompositeType(tag: DW_TAG_structure_type, scope: !282, file: !219, line: 176, size: 448, align: 64, elements: !286)
!286 = !{!287, !288, !289, !290, !291, !292, !293, !294, !295, !296, !297}
!287 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !285, file: !219, line: 178, baseType: !191, size: 32, align: 32)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !285, file: !219, line: 179, baseType: !181, size: 32, align: 32, offset: 32)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !285, file: !219, line: 180, baseType: !181, size: 32, align: 32, offset: 64)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !285, file: !219, line: 181, baseType: !181, size: 32, align: 32, offset: 96)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !285, file: !219, line: 182, baseType: !181, size: 32, align: 32, offset: 128)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !285, file: !219, line: 183, baseType: !181, size: 32, align: 32, offset: 160)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !285, file: !219, line: 184, baseType: !191, size: 32, align: 32, offset: 192)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !285, file: !219, line: 185, baseType: !191, size: 32, align: 32, offset: 224)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !285, file: !219, line: 186, baseType: !189, size: 64, align: 64, offset: 256)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !285, file: !219, line: 187, baseType: !189, size: 64, align: 64, offset: 320)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !285, file: !219, line: 190, baseType: !181, size: 32, align: 32, offset: 384)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !282, file: !219, line: 211, baseType: !299, size: 448, align: 8)
!299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !242, size: 448, align: 8, elements: !300)
!300 = !{!301}
!301 = !DISubrange(count: 56)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !282, file: !219, line: 212, baseType: !246, size: 64, align: 64)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !177, file: !4, line: 1482, baseType: !168, size: 64, align: 64, offset: 2880)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 2944)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 3072)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 3200)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 3328)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !177, file: !4, line: 1482, baseType: !183, size: 128, align: 64, offset: 3456)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !177, file: !4, line: 1482, baseType: !310, size: 64, align: 64, offset: 3584)
!310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !311, size: 64, align: 64)
!311 = !DISubroutineType(types: !312)
!312 = !{null}
!313 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !177, file: !4, line: 1482, baseType: !197, size: 448, align: 64, offset: 3648)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !177, file: !4, line: 1482, baseType: !191, size: 32, align: 32, offset: 4096)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !177, file: !4, line: 1482, baseType: !316, size: 128, align: 64, offset: 4160)
!316 = !DICompositeType(tag: DW_TAG_structure_type, scope: !177, file: !4, line: 1482, size: 128, align: 64, elements: !317)
!317 = !{!318, !319}
!318 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !316, file: !4, line: 1482, baseType: !173, size: 64, align: 64)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !316, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 64)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !177, file: !4, line: 1482, baseType: !321, size: 64, align: 64, offset: 4288)
!321 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !322, line: 55, baseType: !189)
!322 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!323 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !177, file: !4, line: 1482, baseType: !321, size: 64, align: 64, offset: 4352)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !177, file: !4, line: 1482, baseType: !325, size: 64, align: 32, offset: 4416)
!325 = !DICompositeType(tag: DW_TAG_array_type, baseType: !191, size: 64, align: 32, elements: !184)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !177, file: !4, line: 1482, baseType: !197, size: 448, align: 64, offset: 4480)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !177, file: !4, line: 1482, baseType: !328, size: 1216, align: 64, offset: 4928)
!328 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !329)
!329 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !330)
!330 = !{!331, !332, !333, !334, !335, !336, !341, !342, !343, !349, !350, !358, !359}
!331 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !329, file: !4, line: 1326, baseType: !173, size: 64, align: 64)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !329, file: !4, line: 1326, baseType: !175, size: 64, align: 64, offset: 64)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !329, file: !4, line: 1326, baseType: !254, size: 32, align: 32, offset: 128)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !329, file: !4, line: 1326, baseType: !256, size: 64, align: 64, offset: 192)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !329, file: !4, line: 1326, baseType: !183, size: 128, align: 64, offset: 256)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !329, file: !4, line: 1326, baseType: !337, size: 256, align: 64, offset: 384)
!337 = !DICompositeType(tag: DW_TAG_union_type, scope: !329, file: !4, line: 1326, size: 256, align: 64, elements: !338)
!338 = !{!339, !340}
!339 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !337, file: !4, line: 1326, baseType: !191, size: 32, align: 32)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !337, file: !4, line: 1326, baseType: !266, size: 256, align: 64)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !329, file: !4, line: 1326, baseType: !168, size: 64, align: 64, offset: 640)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !329, file: !4, line: 1326, baseType: !181, size: 32, align: 32, offset: 704)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !329, file: !4, line: 1327, baseType: !344, size: 64, align: 64, offset: 768)
!344 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !345)
!345 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !346, size: 64, align: 64)
!346 = !DISubroutineType(types: !347)
!347 = !{null, !348, !191}
!348 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !328, size: 64, align: 64)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !329, file: !4, line: 1328, baseType: !191, size: 32, align: 32, offset: 832)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !329, file: !4, line: 1329, baseType: !351, size: 256, align: 64, offset: 896)
!351 = !DICompositeType(tag: DW_TAG_structure_type, scope: !329, file: !4, line: 1329, size: 256, align: 64, elements: !352)
!352 = !{!353, !355, !356, !357}
!353 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !351, file: !4, line: 1329, baseType: !354, size: 64, align: 64)
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !329, size: 64, align: 64)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !351, file: !4, line: 1329, baseType: !354, size: 64, align: 64, offset: 64)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !351, file: !4, line: 1329, baseType: !354, size: 64, align: 64, offset: 128)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !351, file: !4, line: 1329, baseType: !191, size: 32, align: 32, offset: 192)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !329, file: !4, line: 1329, baseType: !181, size: 32, align: 32, offset: 1152)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !329, file: !4, line: 1329, baseType: !181, size: 32, align: 32, offset: 1184)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !177, file: !4, line: 1482, baseType: !191, size: 32, align: 32, offset: 6144)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !177, file: !4, line: 1482, baseType: !197, size: 448, align: 64, offset: 6208)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !177, file: !4, line: 1482, baseType: !173, size: 64, align: 64, offset: 6656)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !177, file: !4, line: 1482, baseType: !191, size: 32, align: 32, offset: 6720)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !170, file: !4, line: 426, baseType: !254, size: 32, align: 32, offset: 128)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !170, file: !4, line: 426, baseType: !256, size: 64, align: 64, offset: 192)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !170, file: !4, line: 426, baseType: !183, size: 128, align: 64, offset: 256)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !170, file: !4, line: 426, baseType: !368, size: 256, align: 64, offset: 384)
!368 = !DICompositeType(tag: DW_TAG_union_type, scope: !170, file: !4, line: 426, size: 256, align: 64, elements: !369)
!369 = !{!370, !371}
!370 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !368, file: !4, line: 426, baseType: !191, size: 32, align: 32)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !368, file: !4, line: 426, baseType: !266, size: 256, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !170, file: !4, line: 426, baseType: !168, size: 64, align: 64, offset: 640)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !170, file: !4, line: 426, baseType: !181, size: 32, align: 32, offset: 704)
!374 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !375, size: 64, align: 64)
!375 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !376, size: 64, align: 64)
!376 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !377, line: 21, baseType: !183)
!377 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!378 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !379, size: 64, align: 64)
!379 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !376)
!380 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !381, size: 64, align: 64)
!381 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_write_t", file: !4, line: 227, baseType: !382)
!382 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_write_s", file: !4, line: 494, size: 1536, align: 64, elements: !383)
!383 = !{!384, !385, !387, !388, !389, !394, !479, !480, !481, !482, !483, !484, !485}
!384 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !382, file: !4, line: 495, baseType: !173, size: 64, align: 64)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !382, file: !4, line: 495, baseType: !386, size: 32, align: 32, offset: 64)
!386 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !25)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !382, file: !4, line: 495, baseType: !183, size: 128, align: 64, offset: 128)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !382, file: !4, line: 495, baseType: !266, size: 256, align: 64, offset: 256)
!389 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !382, file: !4, line: 496, baseType: !390, size: 64, align: 64, offset: 512)
!390 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_write_cb", file: !4, line: 302, baseType: !391)
!391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !392, size: 64, align: 64)
!392 = !DISubroutineType(types: !393)
!393 = !{null, !380, !191}
!394 = !DIDerivedType(tag: DW_TAG_member, name: "send_handle", scope: !382, file: !4, line: 497, baseType: !395, size: 64, align: 64, offset: 576)
!395 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !396, size: 64, align: 64)
!396 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !4, line: 206, baseType: !397)
!397 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !4, line: 465, size: 1984, align: 64, elements: !398)
!398 = !{!399, !400, !401, !402, !403, !404, !409, !410, !411, !414, !426, !437, !453, !468, !469, !470, !471, !476, !477, !478}
!399 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !397, file: !4, line: 466, baseType: !173, size: 64, align: 64)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !397, file: !4, line: 466, baseType: !175, size: 64, align: 64, offset: 64)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !397, file: !4, line: 466, baseType: !254, size: 32, align: 32, offset: 128)
!402 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !397, file: !4, line: 466, baseType: !256, size: 64, align: 64, offset: 192)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !397, file: !4, line: 466, baseType: !183, size: 128, align: 64, offset: 256)
!404 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !397, file: !4, line: 466, baseType: !405, size: 256, align: 64, offset: 384)
!405 = !DICompositeType(tag: DW_TAG_union_type, scope: !397, file: !4, line: 466, size: 256, align: 64, elements: !406)
!406 = !{!407, !408}
!407 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !405, file: !4, line: 466, baseType: !191, size: 32, align: 32)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !405, file: !4, line: 466, baseType: !266, size: 256, align: 64)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !397, file: !4, line: 466, baseType: !168, size: 64, align: 64, offset: 640)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !397, file: !4, line: 466, baseType: !181, size: 32, align: 32, offset: 704)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !397, file: !4, line: 467, baseType: !412, size: 64, align: 64, offset: 768)
!412 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !413, line: 62, baseType: !189)
!413 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!414 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !397, file: !4, line: 467, baseType: !415, size: 64, align: 64, offset: 832)
!415 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !4, line: 296, baseType: !416)
!416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !417, size: 64, align: 64)
!417 = !DISubroutineType(types: !418)
!418 = !{null, !168, !412, !419}
!419 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !420, size: 64, align: 64)
!420 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !198, line: 119, baseType: !421)
!421 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !198, line: 116, size: 128, align: 64, elements: !422)
!422 = !{!423, !425}
!423 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !421, file: !198, line: 117, baseType: !424, size: 64, align: 64)
!424 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !242, size: 64, align: 64)
!425 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !421, file: !198, line: 118, baseType: !412, size: 64, align: 64, offset: 64)
!426 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !397, file: !4, line: 467, baseType: !427, size: 64, align: 64, offset: 896)
!427 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !4, line: 299, baseType: !428)
!428 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !429, size: 64, align: 64)
!429 = !DISubroutineType(types: !430)
!430 = !{null, !395, !431, !435}
!431 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !432, line: 102, baseType: !433)
!432 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!433 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !434, line: 172, baseType: !246)
!434 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!435 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !436, size: 64, align: 64)
!436 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !420)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !397, file: !4, line: 467, baseType: !438, size: 64, align: 64, offset: 960)
!438 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !439, size: 64, align: 64)
!439 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !4, line: 228, baseType: !440)
!440 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !4, line: 551, size: 768, align: 64, elements: !441)
!441 = !{!442, !443, !444, !445, !446, !451, !452}
!442 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !440, file: !4, line: 552, baseType: !173, size: 64, align: 64)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !440, file: !4, line: 552, baseType: !386, size: 32, align: 32, offset: 64)
!444 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !440, file: !4, line: 552, baseType: !183, size: 128, align: 64, offset: 128)
!445 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !440, file: !4, line: 552, baseType: !266, size: 256, align: 64, offset: 256)
!446 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !440, file: !4, line: 553, baseType: !447, size: 64, align: 64, offset: 512)
!447 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !4, line: 303, baseType: !448)
!448 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !449, size: 64, align: 64)
!449 = !DISubroutineType(types: !450)
!450 = !{null, !438, !191}
!451 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !440, file: !4, line: 554, baseType: !395, size: 64, align: 64, offset: 576)
!452 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !440, file: !4, line: 555, baseType: !183, size: 128, align: 64, offset: 640)
!453 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !397, file: !4, line: 467, baseType: !454, size: 64, align: 64, offset: 1024)
!454 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !455, size: 64, align: 64)
!455 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !4, line: 226, baseType: !456)
!456 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !4, line: 401, size: 640, align: 64, elements: !457)
!457 = !{!458, !459, !460, !461, !462, !463}
!458 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !456, file: !4, line: 402, baseType: !173, size: 64, align: 64)
!459 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !456, file: !4, line: 402, baseType: !386, size: 32, align: 32, offset: 64)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !456, file: !4, line: 402, baseType: !183, size: 128, align: 64, offset: 128)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !456, file: !4, line: 402, baseType: !266, size: 256, align: 64, offset: 256)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !456, file: !4, line: 403, baseType: !395, size: 64, align: 64, offset: 512)
!463 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !456, file: !4, line: 404, baseType: !464, size: 64, align: 64, offset: 576)
!464 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !4, line: 304, baseType: !465)
!465 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !466, size: 64, align: 64)
!466 = !DISubroutineType(types: !467)
!467 = !{null, !454, !191}
!468 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !397, file: !4, line: 467, baseType: !197, size: 448, align: 64, offset: 1088)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !397, file: !4, line: 467, baseType: !183, size: 128, align: 64, offset: 1536)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !397, file: !4, line: 467, baseType: !183, size: 128, align: 64, offset: 1664)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !397, file: !4, line: 467, baseType: !472, size: 64, align: 64, offset: 1792)
!472 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !4, line: 305, baseType: !473)
!473 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !474, size: 64, align: 64)
!474 = !DISubroutineType(types: !475)
!475 = !{null, !395, !191}
!476 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !397, file: !4, line: 467, baseType: !191, size: 32, align: 32, offset: 1856)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !397, file: !4, line: 467, baseType: !191, size: 32, align: 32, offset: 1888)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !397, file: !4, line: 467, baseType: !173, size: 64, align: 64, offset: 1920)
!479 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !382, file: !4, line: 498, baseType: !395, size: 64, align: 64, offset: 640)
!480 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !382, file: !4, line: 499, baseType: !183, size: 128, align: 64, offset: 704)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "write_index", scope: !382, file: !4, line: 499, baseType: !181, size: 32, align: 32, offset: 832)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !382, file: !4, line: 499, baseType: !419, size: 64, align: 64, offset: 896)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !382, file: !4, line: 499, baseType: !181, size: 32, align: 32, offset: 960)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !382, file: !4, line: 499, baseType: !191, size: 32, align: 32, offset: 992)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !382, file: !4, line: 499, baseType: !486, size: 512, align: 64, offset: 1024)
!486 = !DICompositeType(tag: DW_TAG_array_type, baseType: !420, size: 512, align: 64, elements: !267)
!487 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !488, size: 64, align: 64)
!488 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_t", file: !4, line: 208, baseType: !489)
!489 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_udp_s", file: !4, line: 590, size: 1728, align: 64, elements: !490)
!490 = !{!491, !492, !493, !494, !495, !496, !501, !502, !503, !504, !505, !506, !523, !524, !525}
!491 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !489, file: !4, line: 591, baseType: !173, size: 64, align: 64)
!492 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !489, file: !4, line: 591, baseType: !175, size: 64, align: 64, offset: 64)
!493 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !489, file: !4, line: 591, baseType: !254, size: 32, align: 32, offset: 128)
!494 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !489, file: !4, line: 591, baseType: !256, size: 64, align: 64, offset: 192)
!495 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !489, file: !4, line: 591, baseType: !183, size: 128, align: 64, offset: 256)
!496 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !489, file: !4, line: 591, baseType: !497, size: 256, align: 64, offset: 384)
!497 = !DICompositeType(tag: DW_TAG_union_type, scope: !489, file: !4, line: 591, size: 256, align: 64, elements: !498)
!498 = !{!499, !500}
!499 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !497, file: !4, line: 591, baseType: !191, size: 32, align: 32)
!500 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !497, file: !4, line: 591, baseType: !266, size: 256, align: 64)
!501 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !489, file: !4, line: 591, baseType: !168, size: 64, align: 64, offset: 640)
!502 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !489, file: !4, line: 591, baseType: !181, size: 32, align: 32, offset: 704)
!503 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_size", scope: !489, file: !4, line: 597, baseType: !412, size: 64, align: 64, offset: 768)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "send_queue_count", scope: !489, file: !4, line: 601, baseType: !412, size: 64, align: 64, offset: 832)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !489, file: !4, line: 602, baseType: !415, size: 64, align: 64, offset: 896)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "recv_cb", scope: !489, file: !4, line: 602, baseType: !507, size: 64, align: 64, offset: 960)
!507 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_udp_recv_cb", file: !4, line: 583, baseType: !508)
!508 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !509, size: 64, align: 64)
!509 = !DISubroutineType(types: !510)
!510 = !{null, !487, !431, !435, !511, !181}
!511 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !512, size: 64, align: 64)
!512 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !513)
!513 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !157, line: 149, size: 128, align: 16, elements: !514)
!514 = !{!515, !519}
!515 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !513, file: !157, line: 151, baseType: !516, size: 16, align: 16)
!516 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !517, line: 28, baseType: !518)
!517 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!518 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !513, file: !157, line: 152, baseType: !520, size: 112, align: 8, offset: 16)
!520 = !DICompositeType(tag: DW_TAG_array_type, baseType: !242, size: 112, align: 8, elements: !521)
!521 = !{!522}
!522 = !DISubrange(count: 14)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !489, file: !4, line: 602, baseType: !197, size: 448, align: 64, offset: 1024)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !489, file: !4, line: 602, baseType: !183, size: 128, align: 64, offset: 1472)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !489, file: !4, line: 602, baseType: !183, size: 128, align: 64, offset: 1600)
!526 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !527, size: 64, align: 64)
!527 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_tcp_t", file: !4, line: 207, baseType: !528)
!528 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_tcp_s", file: !4, line: 516, size: 1984, align: 64, elements: !529)
!529 = !{!530, !531, !532, !533, !534, !535, !540, !541, !542, !543, !544, !545, !546, !547, !548, !549, !550, !551, !552, !553}
!530 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !528, file: !4, line: 517, baseType: !173, size: 64, align: 64)
!531 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !528, file: !4, line: 517, baseType: !175, size: 64, align: 64, offset: 64)
!532 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !528, file: !4, line: 517, baseType: !254, size: 32, align: 32, offset: 128)
!533 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !528, file: !4, line: 517, baseType: !256, size: 64, align: 64, offset: 192)
!534 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !528, file: !4, line: 517, baseType: !183, size: 128, align: 64, offset: 256)
!535 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !528, file: !4, line: 517, baseType: !536, size: 256, align: 64, offset: 384)
!536 = !DICompositeType(tag: DW_TAG_union_type, scope: !528, file: !4, line: 517, size: 256, align: 64, elements: !537)
!537 = !{!538, !539}
!538 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !536, file: !4, line: 517, baseType: !191, size: 32, align: 32)
!539 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !536, file: !4, line: 517, baseType: !266, size: 256, align: 64)
!540 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !528, file: !4, line: 517, baseType: !168, size: 64, align: 64, offset: 640)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !528, file: !4, line: 517, baseType: !181, size: 32, align: 32, offset: 704)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !528, file: !4, line: 518, baseType: !412, size: 64, align: 64, offset: 768)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !528, file: !4, line: 518, baseType: !415, size: 64, align: 64, offset: 832)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !528, file: !4, line: 518, baseType: !427, size: 64, align: 64, offset: 896)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !528, file: !4, line: 518, baseType: !438, size: 64, align: 64, offset: 960)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !528, file: !4, line: 518, baseType: !454, size: 64, align: 64, offset: 1024)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !528, file: !4, line: 518, baseType: !197, size: 448, align: 64, offset: 1088)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !528, file: !4, line: 518, baseType: !183, size: 128, align: 64, offset: 1536)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !528, file: !4, line: 518, baseType: !183, size: 128, align: 64, offset: 1664)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !528, file: !4, line: 518, baseType: !472, size: 64, align: 64, offset: 1792)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !528, file: !4, line: 518, baseType: !191, size: 32, align: 32, offset: 1856)
!552 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !528, file: !4, line: 518, baseType: !191, size: 32, align: 32, offset: 1888)
!553 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !528, file: !4, line: 518, baseType: !173, size: 64, align: 64, offset: 1920)
!554 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !555, size: 64, align: 64)
!555 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_pipe_t", file: !4, line: 209, baseType: !556)
!556 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_pipe_s", file: !4, line: 692, size: 2112, align: 64, elements: !557)
!557 = !{!558, !559, !560, !561, !562, !563, !568, !569, !570, !571, !572, !573, !574, !575, !576, !577, !578, !579, !580, !581, !582, !583}
!558 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !556, file: !4, line: 693, baseType: !173, size: 64, align: 64)
!559 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !556, file: !4, line: 693, baseType: !175, size: 64, align: 64, offset: 64)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !556, file: !4, line: 693, baseType: !254, size: 32, align: 32, offset: 128)
!561 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !556, file: !4, line: 693, baseType: !256, size: 64, align: 64, offset: 192)
!562 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !556, file: !4, line: 693, baseType: !183, size: 128, align: 64, offset: 256)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !556, file: !4, line: 693, baseType: !564, size: 256, align: 64, offset: 384)
!564 = !DICompositeType(tag: DW_TAG_union_type, scope: !556, file: !4, line: 693, size: 256, align: 64, elements: !565)
!565 = !{!566, !567}
!566 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !564, file: !4, line: 693, baseType: !191, size: 32, align: 32)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !564, file: !4, line: 693, baseType: !266, size: 256, align: 64)
!568 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !556, file: !4, line: 693, baseType: !168, size: 64, align: 64, offset: 640)
!569 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !556, file: !4, line: 693, baseType: !181, size: 32, align: 32, offset: 704)
!570 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !556, file: !4, line: 694, baseType: !412, size: 64, align: 64, offset: 768)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !556, file: !4, line: 694, baseType: !415, size: 64, align: 64, offset: 832)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !556, file: !4, line: 694, baseType: !427, size: 64, align: 64, offset: 896)
!573 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !556, file: !4, line: 694, baseType: !438, size: 64, align: 64, offset: 960)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !556, file: !4, line: 694, baseType: !454, size: 64, align: 64, offset: 1024)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !556, file: !4, line: 694, baseType: !197, size: 448, align: 64, offset: 1088)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !556, file: !4, line: 694, baseType: !183, size: 128, align: 64, offset: 1536)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !556, file: !4, line: 694, baseType: !183, size: 128, align: 64, offset: 1664)
!578 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !556, file: !4, line: 694, baseType: !472, size: 64, align: 64, offset: 1792)
!579 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !556, file: !4, line: 694, baseType: !191, size: 32, align: 32, offset: 1856)
!580 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !556, file: !4, line: 694, baseType: !191, size: 32, align: 32, offset: 1888)
!581 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !556, file: !4, line: 694, baseType: !173, size: 64, align: 64, offset: 1920)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "ipc", scope: !556, file: !4, line: 695, baseType: !191, size: 32, align: 32, offset: 1984)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_fname", scope: !556, file: !4, line: 696, baseType: !584, size: 64, align: 64, offset: 2048)
!584 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !585, size: 64, align: 64)
!585 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !242)
!586 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !513, size: 64, align: 64)
!587 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !588, size: 64, align: 64)
!588 = !DICompositeType(tag: DW_TAG_structure_type, name: "iovec", file: !589, line: 43, size: 128, align: 64, elements: !590)
!589 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/uio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!590 = !{!591, !592}
!591 = !DIDerivedType(tag: DW_TAG_member, name: "iov_base", scope: !588, file: !589, line: 45, baseType: !173, size: 64, align: 64)
!592 = !DIDerivedType(tag: DW_TAG_member, name: "iov_len", scope: !588, file: !589, line: 46, baseType: !412, size: 64, align: 64, offset: 64)
!593 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !594, size: 64, align: 64)
!594 = !DICompositeType(tag: DW_TAG_structure_type, name: "cmsghdr", file: !157, line: 242, size: 128, align: 64, elements: !595)
!595 = !{!596, !597, !598, !599}
!596 = !DIDerivedType(tag: DW_TAG_member, name: "cmsg_len", scope: !594, file: !157, line: 244, baseType: !412, size: 64, align: 64)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "cmsg_level", scope: !594, file: !157, line: 249, baseType: !191, size: 32, align: 32, offset: 64)
!598 = !DIDerivedType(tag: DW_TAG_member, name: "cmsg_type", scope: !594, file: !157, line: 250, baseType: !191, size: 32, align: 32, offset: 96)
!599 = !DIDerivedType(tag: DW_TAG_member, name: "__cmsg_data", scope: !594, file: !157, line: 252, baseType: !600, offset: 128)
!600 = !DICompositeType(tag: DW_TAG_array_type, baseType: !601, align: 8, elements: !602)
!601 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!602 = !{!603}
!603 = !DISubrange(count: -1)
!604 = !{!605, !609, !612, !613, !616, !619, !622, !625, !628, !631, !634, !637, !638, !641, !644, !647, !652, !653, !654, !657, !660, !661, !662, !663, !664, !665, !680, !681, !684, !685, !688, !689, !692}
!605 = distinct !DISubprogram(name: "uv__stream_init", scope: !1, file: !1, line: 71, type: !606, isLocal: false, isDefinition: true, scopeLine: 73, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!606 = !DISubroutineType(types: !607)
!607 = !{null, !175, !395, !254}
!608 = !{}
!609 = distinct !DISubprogram(name: "uv__stream_open", scope: !1, file: !1, line: 392, type: !610, isLocal: false, isDefinition: true, scopeLine: 392, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!610 = !DISubroutineType(types: !611)
!611 = !{!191, !395, !191, !191}
!612 = distinct !DISubprogram(name: "uv__stream_flush_write_queue", scope: !1, file: !1, line: 427, type: !474, isLocal: false, isDefinition: true, scopeLine: 427, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!613 = distinct !DISubprogram(name: "uv__stream_destroy", scope: !1, file: !1, line: 442, type: !614, isLocal: false, isDefinition: true, scopeLine: 442, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!614 = !DISubroutineType(types: !615)
!615 = !{null, !395}
!616 = distinct !DISubprogram(name: "uv__server_io", scope: !1, file: !1, line: 512, type: !617, isLocal: false, isDefinition: true, scopeLine: 512, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!617 = !DISubroutineType(types: !618)
!618 = !{null, !175, !196, !181}
!619 = distinct !DISubprogram(name: "uv_accept", scope: !1, file: !1, line: 574, type: !620, isLocal: false, isDefinition: true, scopeLine: 574, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!620 = !DISubroutineType(types: !621)
!621 = !{!191, !395, !395}
!622 = distinct !DISubprogram(name: "uv_listen", scope: !1, file: !1, line: 639, type: !623, isLocal: false, isDefinition: true, scopeLine: 639, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!623 = !DISubroutineType(types: !624)
!624 = !{!191, !395, !191, !472}
!625 = distinct !DISubprogram(name: "uv__handle_type", scope: !1, file: !1, line: 956, type: !626, isLocal: false, isDefinition: true, scopeLine: 956, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!626 = !DISubroutineType(types: !627)
!627 = !{!254, !191}
!628 = distinct !DISubprogram(name: "uv_shutdown", scope: !1, file: !1, line: 1246, type: !629, isLocal: false, isDefinition: true, scopeLine: 1246, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!629 = !DISubroutineType(types: !630)
!630 = !{!191, !454, !395, !464}
!631 = distinct !DISubprogram(name: "uv_write2", scope: !1, file: !1, line: 1379, type: !632, isLocal: false, isDefinition: true, scopeLine: 1384, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!632 = !DISubroutineType(types: !633)
!633 = !{!191, !380, !395, !435, !181, !395, !390}
!634 = distinct !DISubprogram(name: "uv_write", scope: !1, file: !1, line: 1469, type: !635, isLocal: false, isDefinition: true, scopeLine: 1473, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!635 = !DISubroutineType(types: !636)
!636 = !{!191, !380, !395, !435, !181, !390}
!637 = distinct !DISubprogram(name: "uv_try_write_cb", scope: !1, file: !1, line: 1478, type: !392, isLocal: false, isDefinition: true, scopeLine: 1478, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!638 = distinct !DISubprogram(name: "uv_try_write", scope: !1, file: !1, line: 1484, type: !639, isLocal: false, isDefinition: true, scopeLine: 1486, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!639 = !DISubroutineType(types: !640)
!640 = !{!191, !395, !435, !181}
!641 = distinct !DISubprogram(name: "uv_read_start", scope: !1, file: !1, line: 1532, type: !642, isLocal: false, isDefinition: true, scopeLine: 1534, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!642 = !DISubroutineType(types: !643)
!643 = !{!191, !395, !415, !427}
!644 = distinct !DISubprogram(name: "uv_read_stop", scope: !1, file: !1, line: 1564, type: !645, isLocal: false, isDefinition: true, scopeLine: 1564, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!645 = !DISubroutineType(types: !646)
!646 = !{!191, !395}
!647 = distinct !DISubprogram(name: "uv_is_readable", scope: !1, file: !1, line: 1580, type: !648, isLocal: false, isDefinition: true, scopeLine: 1580, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!648 = !DISubroutineType(types: !649)
!649 = !{!191, !650}
!650 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !651, size: 64, align: 64)
!651 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !396)
!652 = distinct !DISubprogram(name: "uv_is_writable", scope: !1, file: !1, line: 1585, type: !648, isLocal: false, isDefinition: true, scopeLine: 1585, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!653 = distinct !DISubprogram(name: "uv__stream_close", scope: !1, file: !1, line: 1607, type: !614, isLocal: false, isDefinition: true, scopeLine: 1607, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!654 = distinct !DISubprogram(name: "uv_stream_set_blocking", scope: !1, file: !1, line: 1661, type: !655, isLocal: false, isDefinition: true, scopeLine: 1661, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!655 = !DISubroutineType(types: !656)
!656 = !{!191, !395, !191}
!657 = distinct !DISubprogram(name: "uv__emfile_trick", scope: !1, file: !1, line: 481, type: !658, isLocal: true, isDefinition: true, scopeLine: 481, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!658 = !DISubroutineType(types: !659)
!659 = !{!191, !175, !191}
!660 = distinct !DISubprogram(name: "uv__write_callbacks", scope: !1, file: !1, line: 929, type: !614, isLocal: true, isDefinition: true, scopeLine: 929, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!661 = distinct !DISubprogram(name: "uv__stream_osx_interrupt_select", scope: !1, file: !1, line: 109, type: !614, isLocal: true, isDefinition: true, scopeLine: 109, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!662 = distinct !DISubprogram(name: "uv__stream_io", scope: !1, file: !1, line: 1273, type: !617, isLocal: true, isDefinition: true, scopeLine: 1273, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!663 = distinct !DISubprogram(name: "uv__stream_connect", scope: !1, file: !1, line: 1330, type: !614, isLocal: true, isDefinition: true, scopeLine: 1330, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!664 = distinct !DISubprogram(name: "uv__read", scope: !1, file: !1, line: 1108, type: !614, isLocal: true, isDefinition: true, scopeLine: 1108, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!665 = distinct !DISubprogram(name: "uv__stream_recv_cmsg", scope: !1, file: !1, line: 1053, type: !666, isLocal: true, isDefinition: true, scopeLine: 1053, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!666 = !DISubroutineType(types: !667)
!667 = !{!191, !395, !668}
!668 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !669, size: 64, align: 64)
!669 = !DICompositeType(tag: DW_TAG_structure_type, name: "msghdr", file: !157, line: 224, size: 448, align: 64, elements: !670)
!670 = !{!671, !672, !675, !676, !677, !678, !679}
!671 = !DIDerivedType(tag: DW_TAG_member, name: "msg_name", scope: !669, file: !157, line: 226, baseType: !173, size: 64, align: 64)
!672 = !DIDerivedType(tag: DW_TAG_member, name: "msg_namelen", scope: !669, file: !157, line: 227, baseType: !673, size: 32, align: 32, offset: 64)
!673 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !157, line: 33, baseType: !674)
!674 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !434, line: 189, baseType: !181)
!675 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iov", scope: !669, file: !157, line: 229, baseType: !587, size: 64, align: 64, offset: 128)
!676 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iovlen", scope: !669, file: !157, line: 230, baseType: !412, size: 64, align: 64, offset: 192)
!677 = !DIDerivedType(tag: DW_TAG_member, name: "msg_control", scope: !669, file: !157, line: 232, baseType: !173, size: 64, align: 64, offset: 256)
!678 = !DIDerivedType(tag: DW_TAG_member, name: "msg_controllen", scope: !669, file: !157, line: 233, baseType: !412, size: 64, align: 64, offset: 320)
!679 = !DIDerivedType(tag: DW_TAG_member, name: "msg_flags", scope: !669, file: !157, line: 238, baseType: !191, size: 32, align: 32, offset: 384)
!680 = distinct !DISubprogram(name: "uv__stream_queue_fd", scope: !1, file: !1, line: 1010, type: !655, isLocal: true, isDefinition: true, scopeLine: 1010, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!681 = distinct !DISubprogram(name: "uv__stream_eof", scope: !1, file: !1, line: 999, type: !682, isLocal: true, isDefinition: true, scopeLine: 999, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!682 = !DISubroutineType(types: !683)
!683 = !{null, !395, !435}
!684 = distinct !DISubprogram(name: "uv__drain", scope: !1, file: !1, line: 662, type: !614, isLocal: true, isDefinition: true, scopeLine: 662, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!685 = distinct !DISubprogram(name: "uv__handle_fd", scope: !1, file: !1, line: 732, type: !686, isLocal: true, isDefinition: true, scopeLine: 732, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!686 = !DISubroutineType(types: !687)
!687 = !{!191, !168}
!688 = distinct !DISubprogram(name: "uv__write", scope: !1, file: !1, line: 746, type: !614, isLocal: true, isDefinition: true, scopeLine: 746, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!689 = distinct !DISubprogram(name: "uv__write_req_finish", scope: !1, file: !1, line: 706, type: !690, isLocal: true, isDefinition: true, scopeLine: 706, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!690 = !DISubroutineType(types: !691)
!691 = !{null, !380}
!692 = distinct !DISubprogram(name: "uv__write_req_size", scope: !1, file: !1, line: 694, type: !693, isLocal: true, isDefinition: true, scopeLine: 694, flags: DIFlagPrototyped, isOptimized: false, variables: !608)
!693 = !DISubroutineType(types: !694)
!694 = !{!412, !380}
!695 = !{i32 2, !"Dwarf Version", i32 4}
!696 = !{i32 2, !"Debug Info Version", i32 3}
!697 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!698 = !DILocalVariable(name: "loop", arg: 1, scope: !605, file: !1, line: 71, type: !175)
!699 = !DIExpression()
!700 = !DILocation(line: 71, column: 33, scope: !605)
!701 = !DILocalVariable(name: "stream", arg: 2, scope: !605, file: !1, line: 72, type: !395)
!702 = !DILocation(line: 72, column: 35, scope: !605)
!703 = !DILocalVariable(name: "type", arg: 3, scope: !605, file: !1, line: 73, type: !254)
!704 = !DILocation(line: 73, column: 37, scope: !605)
!705 = !DILocalVariable(name: "err", scope: !605, file: !1, line: 74, type: !191)
!706 = !DILocation(line: 74, column: 7, scope: !605)
!707 = !DILocation(line: 76, column: 3, scope: !605)
!708 = !DILocation(line: 76, column: 3, scope: !709)
!709 = !DILexicalBlockFile(scope: !710, file: !1, discriminator: 1)
!710 = distinct !DILexicalBlock(scope: !605, file: !1, line: 76, column: 3)
!711 = !DILocation(line: 76, column: 3, scope: !712)
!712 = !DILexicalBlockFile(scope: !713, file: !1, discriminator: 2)
!713 = distinct !DILexicalBlock(scope: !710, file: !1, line: 76, column: 3)
!714 = !DILocation(line: 76, column: 3, scope: !715)
!715 = !DILexicalBlockFile(scope: !710, file: !1, discriminator: 3)
!716 = !DILocation(line: 77, column: 3, scope: !605)
!717 = !DILocation(line: 77, column: 11, scope: !605)
!718 = !DILocation(line: 77, column: 19, scope: !605)
!719 = !DILocation(line: 78, column: 3, scope: !605)
!720 = !DILocation(line: 78, column: 11, scope: !605)
!721 = !DILocation(line: 78, column: 20, scope: !605)
!722 = !DILocation(line: 79, column: 3, scope: !605)
!723 = !DILocation(line: 79, column: 11, scope: !605)
!724 = !DILocation(line: 79, column: 20, scope: !605)
!725 = !DILocation(line: 80, column: 3, scope: !605)
!726 = !DILocation(line: 80, column: 11, scope: !605)
!727 = !DILocation(line: 80, column: 25, scope: !605)
!728 = !DILocation(line: 81, column: 3, scope: !605)
!729 = !DILocation(line: 81, column: 11, scope: !605)
!730 = !DILocation(line: 81, column: 23, scope: !605)
!731 = !DILocation(line: 82, column: 3, scope: !605)
!732 = !DILocation(line: 82, column: 11, scope: !605)
!733 = !DILocation(line: 82, column: 24, scope: !605)
!734 = !DILocation(line: 83, column: 3, scope: !605)
!735 = !DILocation(line: 83, column: 11, scope: !605)
!736 = !DILocation(line: 83, column: 23, scope: !605)
!737 = !DILocation(line: 84, column: 3, scope: !605)
!738 = !DILocation(line: 84, column: 11, scope: !605)
!739 = !DILocation(line: 84, column: 22, scope: !605)
!740 = !DILocation(line: 85, column: 3, scope: !605)
!741 = !DILocation(line: 85, column: 11, scope: !605)
!742 = !DILocation(line: 85, column: 25, scope: !605)
!743 = !DILocation(line: 86, column: 3, scope: !605)
!744 = !DILocation(line: 86, column: 3, scope: !745)
!745 = !DILexicalBlockFile(scope: !746, file: !1, discriminator: 1)
!746 = distinct !DILexicalBlock(scope: !605, file: !1, line: 86, column: 3)
!747 = !DILocation(line: 87, column: 3, scope: !605)
!748 = !DILocation(line: 87, column: 3, scope: !749)
!749 = !DILexicalBlockFile(scope: !750, file: !1, discriminator: 1)
!750 = distinct !DILexicalBlock(scope: !605, file: !1, line: 87, column: 3)
!751 = !DILocation(line: 88, column: 3, scope: !605)
!752 = !DILocation(line: 88, column: 11, scope: !605)
!753 = !DILocation(line: 88, column: 28, scope: !605)
!754 = !DILocation(line: 90, column: 7, scope: !755)
!755 = distinct !DILexicalBlock(scope: !605, file: !1, line: 90, column: 7)
!756 = !DILocation(line: 90, column: 13, scope: !755)
!757 = !DILocation(line: 90, column: 23, scope: !755)
!758 = !DILocation(line: 90, column: 7, scope: !605)
!759 = !DILocation(line: 91, column: 11, scope: !760)
!760 = distinct !DILexicalBlock(scope: !755, file: !1, line: 90, column: 30)
!761 = !DILocation(line: 91, column: 9, scope: !760)
!762 = !DILocation(line: 92, column: 9, scope: !763)
!763 = distinct !DILexicalBlock(scope: !760, file: !1, line: 92, column: 9)
!764 = !DILocation(line: 92, column: 13, scope: !763)
!765 = !DILocation(line: 92, column: 9, scope: !760)
!766 = !DILocation(line: 96, column: 15, scope: !763)
!767 = !DILocation(line: 96, column: 13, scope: !763)
!768 = !DILocation(line: 96, column: 9, scope: !763)
!769 = !DILocation(line: 97, column: 9, scope: !770)
!770 = distinct !DILexicalBlock(scope: !760, file: !1, line: 97, column: 9)
!771 = !DILocation(line: 97, column: 13, scope: !770)
!772 = !DILocation(line: 97, column: 9, scope: !760)
!773 = !DILocation(line: 98, column: 25, scope: !770)
!774 = !DILocation(line: 98, column: 7, scope: !770)
!775 = !DILocation(line: 98, column: 13, scope: !770)
!776 = !DILocation(line: 98, column: 23, scope: !770)
!777 = !DILocation(line: 99, column: 3, scope: !760)
!778 = !DILocation(line: 105, column: 16, scope: !605)
!779 = !DILocation(line: 105, column: 24, scope: !605)
!780 = !DILocation(line: 105, column: 3, scope: !605)
!781 = !DILocation(line: 106, column: 1, scope: !605)
!782 = !DILocalVariable(name: "loop", arg: 1, scope: !662, file: !1, line: 1273, type: !175)
!783 = !DILocation(line: 1273, column: 38, scope: !662)
!784 = !DILocalVariable(name: "w", arg: 2, scope: !662, file: !1, line: 1273, type: !196)
!785 = !DILocation(line: 1273, column: 54, scope: !662)
!786 = !DILocalVariable(name: "events", arg: 3, scope: !662, file: !1, line: 1273, type: !181)
!787 = !DILocation(line: 1273, column: 70, scope: !662)
!788 = !DILocalVariable(name: "stream", scope: !662, file: !1, line: 1274, type: !395)
!789 = !DILocation(line: 1274, column: 16, scope: !662)
!790 = !DILocation(line: 1276, column: 12, scope: !662)
!791 = !DILocation(line: 1276, column: 10, scope: !662)
!792 = !DILocation(line: 1278, column: 3, scope: !662)
!793 = !DILocation(line: 1278, column: 3, scope: !794)
!794 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 1)
!795 = !DILocation(line: 1278, column: 3, scope: !796)
!796 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 2)
!797 = !DILocation(line: 1278, column: 3, scope: !798)
!798 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 3)
!799 = !DILocation(line: 1278, column: 3, scope: !800)
!800 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 4)
!801 = !DILocation(line: 1278, column: 3, scope: !802)
!802 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 5)
!803 = !DILocation(line: 1281, column: 3, scope: !662)
!804 = !DILocation(line: 1281, column: 3, scope: !794)
!805 = !DILocation(line: 1281, column: 3, scope: !796)
!806 = !DILocation(line: 1281, column: 3, scope: !798)
!807 = !DILocation(line: 1283, column: 7, scope: !808)
!808 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1283, column: 7)
!809 = !DILocation(line: 1283, column: 15, scope: !808)
!810 = !DILocation(line: 1283, column: 7, scope: !662)
!811 = !DILocation(line: 1284, column: 24, scope: !812)
!812 = distinct !DILexicalBlock(scope: !808, file: !1, line: 1283, column: 28)
!813 = !DILocation(line: 1284, column: 5, scope: !812)
!814 = !DILocation(line: 1285, column: 5, scope: !812)
!815 = !DILocation(line: 1288, column: 3, scope: !662)
!816 = !DILocation(line: 1288, column: 3, scope: !794)
!817 = !DILocation(line: 1288, column: 3, scope: !796)
!818 = !DILocation(line: 1288, column: 3, scope: !798)
!819 = !DILocation(line: 1291, column: 7, scope: !820)
!820 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1291, column: 7)
!821 = !DILocation(line: 1291, column: 14, scope: !820)
!822 = !DILocation(line: 1291, column: 7, scope: !662)
!823 = !DILocation(line: 1292, column: 14, scope: !820)
!824 = !DILocation(line: 1292, column: 5, scope: !820)
!825 = !DILocation(line: 1294, column: 7, scope: !826)
!826 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1294, column: 7)
!827 = !DILocation(line: 1294, column: 29, scope: !826)
!828 = !DILocation(line: 1294, column: 7, scope: !662)
!829 = !DILocation(line: 1295, column: 5, scope: !826)
!830 = !DILocation(line: 1303, column: 8, scope: !831)
!831 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1303, column: 7)
!832 = !DILocation(line: 1303, column: 15, scope: !831)
!833 = !DILocation(line: 1303, column: 26, scope: !831)
!834 = !DILocation(line: 1304, column: 8, scope: !831)
!835 = !DILocation(line: 1304, column: 16, scope: !831)
!836 = !DILocation(line: 1304, column: 22, scope: !831)
!837 = !DILocation(line: 1304, column: 43, scope: !831)
!838 = !DILocation(line: 1305, column: 8, scope: !831)
!839 = !DILocation(line: 1305, column: 16, scope: !831)
!840 = !DILocation(line: 1305, column: 22, scope: !831)
!841 = !DILocation(line: 1305, column: 48, scope: !831)
!842 = !DILocation(line: 1306, column: 9, scope: !831)
!843 = !DILocation(line: 1306, column: 17, scope: !831)
!844 = !DILocation(line: 1306, column: 23, scope: !831)
!845 = !DILocation(line: 1303, column: 7, scope: !794)
!846 = !DILocalVariable(name: "buf", scope: !847, file: !1, line: 1307, type: !420)
!847 = distinct !DILexicalBlock(scope: !831, file: !1, line: 1306, column: 46)
!848 = !DILocation(line: 1307, column: 14, scope: !847)
!849 = !DILocation(line: 1308, column: 20, scope: !847)
!850 = !DILocation(line: 1308, column: 5, scope: !847)
!851 = !DILocation(line: 1309, column: 3, scope: !847)
!852 = !DILocation(line: 1311, column: 7, scope: !853)
!853 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1311, column: 7)
!854 = !DILocation(line: 1311, column: 29, scope: !853)
!855 = !DILocation(line: 1311, column: 7, scope: !662)
!856 = !DILocation(line: 1312, column: 5, scope: !853)
!857 = !DILocation(line: 1314, column: 7, scope: !858)
!858 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1314, column: 7)
!859 = !DILocation(line: 1314, column: 14, scope: !858)
!860 = !DILocation(line: 1314, column: 7, scope: !662)
!861 = !DILocation(line: 1315, column: 15, scope: !862)
!862 = distinct !DILexicalBlock(scope: !858, file: !1, line: 1314, column: 47)
!863 = !DILocation(line: 1315, column: 5, scope: !862)
!864 = !DILocation(line: 1316, column: 25, scope: !862)
!865 = !DILocation(line: 1316, column: 5, scope: !862)
!866 = !DILocation(line: 1319, column: 9, scope: !867)
!867 = distinct !DILexicalBlock(scope: !862, file: !1, line: 1319, column: 9)
!868 = !DILocation(line: 1319, column: 9, scope: !862)
!869 = !DILocation(line: 1320, column: 17, scope: !867)
!870 = !DILocation(line: 1320, column: 7, scope: !867)
!871 = !DILocation(line: 1321, column: 3, scope: !862)
!872 = !DILocation(line: 1322, column: 1, scope: !662)
!873 = !DILocalVariable(name: "stream", arg: 1, scope: !609, file: !1, line: 392, type: !395)
!874 = !DILocation(line: 392, column: 34, scope: !609)
!875 = !DILocalVariable(name: "fd", arg: 2, scope: !609, file: !1, line: 392, type: !191)
!876 = !DILocation(line: 392, column: 46, scope: !609)
!877 = !DILocalVariable(name: "flags", arg: 3, scope: !609, file: !1, line: 392, type: !191)
!878 = !DILocation(line: 392, column: 54, scope: !609)
!879 = !DILocation(line: 397, column: 9, scope: !880)
!880 = distinct !DILexicalBlock(scope: !609, file: !1, line: 397, column: 7)
!881 = !DILocation(line: 397, column: 17, scope: !880)
!882 = !DILocation(line: 397, column: 28, scope: !880)
!883 = !DILocation(line: 397, column: 31, scope: !880)
!884 = !DILocation(line: 397, column: 37, scope: !880)
!885 = !DILocation(line: 397, column: 40, scope: !886)
!886 = !DILexicalBlockFile(scope: !880, file: !1, discriminator: 1)
!887 = !DILocation(line: 397, column: 48, scope: !886)
!888 = !DILocation(line: 397, column: 59, scope: !886)
!889 = !DILocation(line: 397, column: 65, scope: !886)
!890 = !DILocation(line: 397, column: 62, scope: !886)
!891 = !DILocation(line: 397, column: 7, scope: !886)
!892 = !DILocation(line: 398, column: 5, scope: !880)
!893 = !DILocation(line: 400, column: 3, scope: !609)
!894 = !DILocation(line: 400, column: 3, scope: !895)
!895 = !DILexicalBlockFile(scope: !609, file: !1, discriminator: 1)
!896 = !DILocation(line: 400, column: 3, scope: !897)
!897 = !DILexicalBlockFile(scope: !609, file: !1, discriminator: 2)
!898 = !DILocation(line: 400, column: 3, scope: !899)
!899 = !DILexicalBlockFile(scope: !609, file: !1, discriminator: 3)
!900 = !DILocation(line: 401, column: 20, scope: !609)
!901 = !DILocation(line: 401, column: 3, scope: !609)
!902 = !DILocation(line: 401, column: 11, scope: !609)
!903 = !DILocation(line: 401, column: 17, scope: !609)
!904 = !DILocation(line: 403, column: 7, scope: !905)
!905 = distinct !DILexicalBlock(scope: !609, file: !1, line: 403, column: 7)
!906 = !DILocation(line: 403, column: 15, scope: !905)
!907 = !DILocation(line: 403, column: 20, scope: !905)
!908 = !DILocation(line: 403, column: 7, scope: !609)
!909 = !DILocation(line: 404, column: 10, scope: !910)
!910 = distinct !DILexicalBlock(scope: !911, file: !1, line: 404, column: 9)
!911 = distinct !DILexicalBlock(scope: !905, file: !1, line: 403, column: 31)
!912 = !DILocation(line: 404, column: 18, scope: !910)
!913 = !DILocation(line: 404, column: 24, scope: !910)
!914 = !DILocation(line: 404, column: 42, scope: !910)
!915 = !DILocation(line: 404, column: 61, scope: !916)
!916 = !DILexicalBlockFile(scope: !910, file: !1, discriminator: 1)
!917 = !DILocation(line: 404, column: 45, scope: !916)
!918 = !DILocation(line: 404, column: 9, scope: !916)
!919 = !DILocation(line: 405, column: 15, scope: !910)
!920 = !DILocation(line: 405, column: 14, scope: !910)
!921 = !DILocation(line: 405, column: 7, scope: !910)
!922 = !DILocation(line: 408, column: 10, scope: !923)
!923 = distinct !DILexicalBlock(scope: !911, file: !1, line: 408, column: 9)
!924 = !DILocation(line: 408, column: 18, scope: !923)
!925 = !DILocation(line: 408, column: 24, scope: !923)
!926 = !DILocation(line: 408, column: 44, scope: !923)
!927 = !DILocation(line: 408, column: 65, scope: !928)
!928 = !DILexicalBlockFile(scope: !923, file: !1, discriminator: 1)
!929 = !DILocation(line: 408, column: 47, scope: !928)
!930 = !DILocation(line: 408, column: 9, scope: !928)
!931 = !DILocation(line: 409, column: 15, scope: !923)
!932 = !DILocation(line: 409, column: 14, scope: !923)
!933 = !DILocation(line: 409, column: 7, scope: !923)
!934 = !DILocation(line: 410, column: 3, scope: !911)
!935 = !DILocation(line: 421, column: 27, scope: !609)
!936 = !DILocation(line: 421, column: 3, scope: !609)
!937 = !DILocation(line: 421, column: 11, scope: !609)
!938 = !DILocation(line: 421, column: 22, scope: !609)
!939 = !DILocation(line: 421, column: 25, scope: !609)
!940 = !DILocation(line: 423, column: 3, scope: !609)
!941 = !DILocation(line: 424, column: 1, scope: !609)
!942 = !DILocalVariable(name: "stream", arg: 1, scope: !612, file: !1, line: 427, type: !395)
!943 = !DILocation(line: 427, column: 48, scope: !612)
!944 = !DILocalVariable(name: "error", arg: 2, scope: !612, file: !1, line: 427, type: !191)
!945 = !DILocation(line: 427, column: 60, scope: !612)
!946 = !DILocalVariable(name: "req", scope: !612, file: !1, line: 428, type: !380)
!947 = !DILocation(line: 428, column: 15, scope: !612)
!948 = !DILocalVariable(name: "q", scope: !612, file: !1, line: 429, type: !375)
!949 = !DILocation(line: 429, column: 10, scope: !612)
!950 = !DILocation(line: 430, column: 3, scope: !612)
!951 = !DILocation(line: 430, column: 11, scope: !952)
!952 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 1)
!953 = !DILocation(line: 430, column: 10, scope: !952)
!954 = !DILocation(line: 430, column: 3, scope: !952)
!955 = !DILocation(line: 431, column: 9, scope: !956)
!956 = distinct !DILexicalBlock(scope: !612, file: !1, line: 430, column: 46)
!957 = !DILocation(line: 431, column: 7, scope: !956)
!958 = !DILocation(line: 432, column: 5, scope: !956)
!959 = !DILocation(line: 432, column: 5, scope: !960)
!960 = !DILexicalBlockFile(scope: !961, file: !1, discriminator: 1)
!961 = distinct !DILexicalBlock(scope: !956, file: !1, line: 432, column: 5)
!962 = !DILocation(line: 434, column: 11, scope: !956)
!963 = !DILocation(line: 434, column: 9, scope: !956)
!964 = !DILocation(line: 435, column: 18, scope: !956)
!965 = !DILocation(line: 435, column: 5, scope: !956)
!966 = !DILocation(line: 435, column: 10, scope: !956)
!967 = !DILocation(line: 435, column: 16, scope: !956)
!968 = !DILocation(line: 437, column: 5, scope: !956)
!969 = !DILocation(line: 437, column: 5, scope: !970)
!970 = !DILexicalBlockFile(scope: !971, file: !1, discriminator: 1)
!971 = distinct !DILexicalBlock(scope: !956, file: !1, line: 437, column: 5)
!972 = !DILocation(line: 430, column: 3, scope: !973)
!973 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 2)
!974 = !DILocation(line: 439, column: 1, scope: !612)
!975 = !DILocalVariable(name: "stream", arg: 1, scope: !613, file: !1, line: 442, type: !395)
!976 = !DILocation(line: 442, column: 38, scope: !613)
!977 = !DILocation(line: 443, column: 3, scope: !613)
!978 = !DILocation(line: 443, column: 3, scope: !979)
!979 = !DILexicalBlockFile(scope: !613, file: !1, discriminator: 1)
!980 = !DILocation(line: 443, column: 3, scope: !981)
!981 = !DILexicalBlockFile(scope: !613, file: !1, discriminator: 2)
!982 = !DILocation(line: 443, column: 3, scope: !983)
!983 = !DILexicalBlockFile(scope: !613, file: !1, discriminator: 3)
!984 = !DILocation(line: 444, column: 3, scope: !613)
!985 = !DILocation(line: 444, column: 3, scope: !979)
!986 = !DILocation(line: 444, column: 3, scope: !981)
!987 = !DILocation(line: 444, column: 3, scope: !983)
!988 = !DILocation(line: 446, column: 7, scope: !989)
!989 = distinct !DILexicalBlock(scope: !613, file: !1, line: 446, column: 7)
!990 = !DILocation(line: 446, column: 15, scope: !989)
!991 = !DILocation(line: 446, column: 7, scope: !613)
!992 = !DILocation(line: 447, column: 5, scope: !993)
!993 = distinct !DILexicalBlock(scope: !989, file: !1, line: 446, column: 28)
!994 = !DILocation(line: 447, column: 5, scope: !995)
!995 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 1)
!996 = distinct !DILexicalBlock(scope: !993, file: !1, line: 447, column: 5)
!997 = !DILocation(line: 447, column: 5, scope: !998)
!998 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 2)
!999 = !DILocation(line: 447, column: 5, scope: !1000)
!1000 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 3)
!1001 = !DILocation(line: 447, column: 5, scope: !1002)
!1002 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 4)
!1003 = !DILocation(line: 447, column: 5, scope: !1004)
!1004 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 5)
!1005 = !DILocation(line: 447, column: 5, scope: !1006)
!1006 = !DILexicalBlockFile(scope: !1007, file: !1, discriminator: 6)
!1007 = distinct !DILexicalBlock(scope: !996, file: !1, line: 447, column: 5)
!1008 = !DILocation(line: 447, column: 5, scope: !1009)
!1009 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 7)
!1010 = !DILocation(line: 448, column: 5, scope: !993)
!1011 = !DILocation(line: 448, column: 13, scope: !993)
!1012 = !DILocation(line: 448, column: 26, scope: !993)
!1013 = !DILocation(line: 448, column: 29, scope: !993)
!1014 = !DILocation(line: 448, column: 37, scope: !993)
!1015 = !DILocation(line: 449, column: 5, scope: !993)
!1016 = !DILocation(line: 449, column: 13, scope: !993)
!1017 = !DILocation(line: 449, column: 25, scope: !993)
!1018 = !DILocation(line: 450, column: 3, scope: !993)
!1019 = !DILocation(line: 452, column: 32, scope: !613)
!1020 = !DILocation(line: 452, column: 3, scope: !613)
!1021 = !DILocation(line: 453, column: 23, scope: !613)
!1022 = !DILocation(line: 453, column: 3, scope: !613)
!1023 = !DILocation(line: 455, column: 7, scope: !1024)
!1024 = distinct !DILexicalBlock(scope: !613, file: !1, line: 455, column: 7)
!1025 = !DILocation(line: 455, column: 15, scope: !1024)
!1026 = !DILocation(line: 455, column: 7, scope: !613)
!1027 = !DILocation(line: 461, column: 5, scope: !1028)
!1028 = distinct !DILexicalBlock(scope: !1024, file: !1, line: 455, column: 29)
!1029 = !DILocation(line: 461, column: 5, scope: !1030)
!1030 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 1)
!1031 = distinct !DILexicalBlock(scope: !1028, file: !1, line: 461, column: 5)
!1032 = !DILocation(line: 461, column: 5, scope: !1033)
!1033 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 2)
!1034 = !DILocation(line: 461, column: 5, scope: !1035)
!1035 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 3)
!1036 = !DILocation(line: 461, column: 5, scope: !1037)
!1037 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 4)
!1038 = !DILocation(line: 461, column: 5, scope: !1039)
!1039 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 5)
!1040 = !DILocation(line: 461, column: 5, scope: !1041)
!1041 = !DILexicalBlockFile(scope: !1042, file: !1, discriminator: 6)
!1042 = distinct !DILexicalBlock(scope: !1031, file: !1, line: 461, column: 5)
!1043 = !DILocation(line: 461, column: 5, scope: !1044)
!1044 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 7)
!1045 = !DILocation(line: 462, column: 5, scope: !1028)
!1046 = !DILocation(line: 462, column: 13, scope: !1028)
!1047 = !DILocation(line: 462, column: 27, scope: !1028)
!1048 = !DILocation(line: 462, column: 30, scope: !1028)
!1049 = !DILocation(line: 462, column: 38, scope: !1028)
!1050 = !DILocation(line: 463, column: 5, scope: !1028)
!1051 = !DILocation(line: 463, column: 13, scope: !1028)
!1052 = !DILocation(line: 463, column: 26, scope: !1028)
!1053 = !DILocation(line: 464, column: 3, scope: !1028)
!1054 = !DILocation(line: 466, column: 3, scope: !613)
!1055 = !DILocation(line: 466, column: 3, scope: !979)
!1056 = !DILocation(line: 466, column: 3, scope: !981)
!1057 = !DILocation(line: 466, column: 3, scope: !983)
!1058 = !DILocation(line: 467, column: 1, scope: !613)
!1059 = !DILocalVariable(name: "stream", arg: 1, scope: !660, file: !1, line: 929, type: !395)
!1060 = !DILocation(line: 929, column: 46, scope: !660)
!1061 = !DILocalVariable(name: "req", scope: !660, file: !1, line: 930, type: !380)
!1062 = !DILocation(line: 930, column: 15, scope: !660)
!1063 = !DILocalVariable(name: "q", scope: !660, file: !1, line: 931, type: !375)
!1064 = !DILocation(line: 931, column: 10, scope: !660)
!1065 = !DILocation(line: 933, column: 3, scope: !660)
!1066 = !DILocation(line: 933, column: 11, scope: !1067)
!1067 = !DILexicalBlockFile(scope: !660, file: !1, discriminator: 1)
!1068 = !DILocation(line: 933, column: 10, scope: !1067)
!1069 = !DILocation(line: 933, column: 3, scope: !1067)
!1070 = !DILocation(line: 935, column: 9, scope: !1071)
!1071 = distinct !DILexicalBlock(scope: !660, file: !1, line: 933, column: 56)
!1072 = !DILocation(line: 935, column: 7, scope: !1071)
!1073 = !DILocation(line: 936, column: 11, scope: !1071)
!1074 = !DILocation(line: 936, column: 9, scope: !1071)
!1075 = !DILocation(line: 937, column: 5, scope: !1071)
!1076 = !DILocation(line: 937, column: 5, scope: !1077)
!1077 = !DILexicalBlockFile(scope: !1078, file: !1, discriminator: 1)
!1078 = distinct !DILexicalBlock(scope: !1071, file: !1, line: 937, column: 5)
!1079 = !DILocation(line: 938, column: 5, scope: !1071)
!1080 = !DILocation(line: 938, column: 5, scope: !1081)
!1081 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 1)
!1082 = distinct !DILexicalBlock(scope: !1071, file: !1, line: 938, column: 5)
!1083 = !DILocation(line: 938, column: 5, scope: !1084)
!1084 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 2)
!1085 = !DILocation(line: 938, column: 5, scope: !1086)
!1086 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 3)
!1087 = !DILocation(line: 938, column: 5, scope: !1088)
!1088 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 4)
!1089 = !DILocation(line: 938, column: 5, scope: !1090)
!1090 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 5)
!1091 = !DILocation(line: 938, column: 5, scope: !1092)
!1092 = !DILexicalBlockFile(scope: !1093, file: !1, discriminator: 6)
!1093 = distinct !DILexicalBlock(scope: !1082, file: !1, line: 938, column: 5)
!1094 = !DILocation(line: 938, column: 5, scope: !1095)
!1095 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 7)
!1096 = !DILocation(line: 940, column: 9, scope: !1097)
!1097 = distinct !DILexicalBlock(scope: !1071, file: !1, line: 940, column: 9)
!1098 = !DILocation(line: 940, column: 14, scope: !1097)
!1099 = !DILocation(line: 940, column: 19, scope: !1097)
!1100 = !DILocation(line: 940, column: 9, scope: !1071)
!1101 = !DILocation(line: 941, column: 54, scope: !1102)
!1102 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 940, column: 28)
!1103 = !DILocation(line: 941, column: 35, scope: !1102)
!1104 = !DILocation(line: 941, column: 7, scope: !1102)
!1105 = !DILocation(line: 941, column: 15, scope: !1102)
!1106 = !DILocation(line: 941, column: 32, scope: !1102)
!1107 = !DILocation(line: 942, column: 11, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 942, column: 11)
!1109 = !DILocation(line: 942, column: 16, scope: !1108)
!1110 = !DILocation(line: 942, column: 24, scope: !1108)
!1111 = !DILocation(line: 942, column: 29, scope: !1108)
!1112 = !DILocation(line: 942, column: 21, scope: !1108)
!1113 = !DILocation(line: 942, column: 11, scope: !1102)
!1114 = !DILocation(line: 943, column: 18, scope: !1108)
!1115 = !DILocation(line: 943, column: 23, scope: !1108)
!1116 = !DILocation(line: 943, column: 9, scope: !1108)
!1117 = !DILocation(line: 944, column: 7, scope: !1102)
!1118 = !DILocation(line: 944, column: 12, scope: !1102)
!1119 = !DILocation(line: 944, column: 17, scope: !1102)
!1120 = !DILocation(line: 945, column: 5, scope: !1102)
!1121 = !DILocation(line: 948, column: 9, scope: !1122)
!1122 = distinct !DILexicalBlock(scope: !1071, file: !1, line: 948, column: 9)
!1123 = !DILocation(line: 948, column: 14, scope: !1122)
!1124 = !DILocation(line: 948, column: 9, scope: !1071)
!1125 = !DILocation(line: 949, column: 7, scope: !1122)
!1126 = !DILocation(line: 949, column: 12, scope: !1122)
!1127 = !DILocation(line: 949, column: 15, scope: !1122)
!1128 = !DILocation(line: 949, column: 20, scope: !1122)
!1129 = !DILocation(line: 949, column: 25, scope: !1122)
!1130 = !DILocation(line: 933, column: 3, scope: !1131)
!1131 = !DILexicalBlockFile(scope: !660, file: !1, discriminator: 2)
!1132 = !DILocation(line: 952, column: 3, scope: !660)
!1133 = !DILocation(line: 952, column: 3, scope: !1067)
!1134 = !DILocation(line: 952, column: 3, scope: !1131)
!1135 = !DILocation(line: 952, column: 3, scope: !1136)
!1136 = !DILexicalBlockFile(scope: !660, file: !1, discriminator: 3)
!1137 = !DILocation(line: 953, column: 1, scope: !660)
!1138 = !DILocalVariable(name: "loop", arg: 1, scope: !616, file: !1, line: 512, type: !175)
!1139 = !DILocation(line: 512, column: 31, scope: !616)
!1140 = !DILocalVariable(name: "w", arg: 2, scope: !616, file: !1, line: 512, type: !196)
!1141 = !DILocation(line: 512, column: 47, scope: !616)
!1142 = !DILocalVariable(name: "events", arg: 3, scope: !616, file: !1, line: 512, type: !181)
!1143 = !DILocation(line: 512, column: 63, scope: !616)
!1144 = !DILocalVariable(name: "stream", scope: !616, file: !1, line: 513, type: !395)
!1145 = !DILocation(line: 513, column: 16, scope: !616)
!1146 = !DILocalVariable(name: "err", scope: !616, file: !1, line: 514, type: !191)
!1147 = !DILocation(line: 514, column: 7, scope: !616)
!1148 = !DILocation(line: 516, column: 12, scope: !616)
!1149 = !DILocation(line: 516, column: 10, scope: !616)
!1150 = !DILocation(line: 517, column: 3, scope: !616)
!1151 = !DILocation(line: 517, column: 3, scope: !1152)
!1152 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 1)
!1153 = !DILocation(line: 517, column: 3, scope: !1154)
!1154 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 2)
!1155 = !DILocation(line: 517, column: 3, scope: !1156)
!1156 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 3)
!1157 = !DILocation(line: 518, column: 3, scope: !616)
!1158 = !DILocation(line: 518, column: 3, scope: !1152)
!1159 = !DILocation(line: 518, column: 3, scope: !1154)
!1160 = !DILocation(line: 518, column: 3, scope: !1156)
!1161 = !DILocation(line: 519, column: 3, scope: !616)
!1162 = !DILocation(line: 519, column: 3, scope: !1152)
!1163 = !DILocation(line: 519, column: 3, scope: !1154)
!1164 = !DILocation(line: 519, column: 3, scope: !1156)
!1165 = !DILocation(line: 521, column: 16, scope: !616)
!1166 = !DILocation(line: 521, column: 24, scope: !616)
!1167 = !DILocation(line: 521, column: 31, scope: !616)
!1168 = !DILocation(line: 521, column: 39, scope: !616)
!1169 = !DILocation(line: 521, column: 3, scope: !616)
!1170 = !DILocation(line: 526, column: 3, scope: !616)
!1171 = !DILocation(line: 526, column: 10, scope: !1152)
!1172 = !DILocation(line: 526, column: 32, scope: !1152)
!1173 = !DILocation(line: 526, column: 3, scope: !1152)
!1174 = !DILocation(line: 527, column: 5, scope: !1175)
!1175 = distinct !DILexicalBlock(scope: !616, file: !1, line: 526, column: 39)
!1176 = !DILocation(line: 527, column: 5, scope: !1177)
!1177 = !DILexicalBlockFile(scope: !1175, file: !1, discriminator: 1)
!1178 = !DILocation(line: 527, column: 5, scope: !1179)
!1179 = !DILexicalBlockFile(scope: !1175, file: !1, discriminator: 2)
!1180 = !DILocation(line: 527, column: 5, scope: !1181)
!1181 = !DILexicalBlockFile(scope: !1175, file: !1, discriminator: 3)
!1182 = !DILocation(line: 534, column: 22, scope: !1175)
!1183 = !DILocation(line: 534, column: 11, scope: !1175)
!1184 = !DILocation(line: 534, column: 9, scope: !1175)
!1185 = !DILocation(line: 535, column: 9, scope: !1186)
!1186 = distinct !DILexicalBlock(scope: !1175, file: !1, line: 535, column: 9)
!1187 = !DILocation(line: 535, column: 13, scope: !1186)
!1188 = !DILocation(line: 535, column: 9, scope: !1175)
!1189 = !DILocation(line: 536, column: 11, scope: !1190)
!1190 = distinct !DILexicalBlock(scope: !1191, file: !1, line: 536, column: 11)
!1191 = distinct !DILexicalBlock(scope: !1186, file: !1, line: 535, column: 18)
!1192 = !DILocation(line: 536, column: 15, scope: !1190)
!1193 = !DILocation(line: 536, column: 26, scope: !1190)
!1194 = !DILocation(line: 536, column: 29, scope: !1195)
!1195 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 1)
!1196 = !DILocation(line: 536, column: 33, scope: !1195)
!1197 = !DILocation(line: 536, column: 11, scope: !1195)
!1198 = !DILocation(line: 537, column: 9, scope: !1190)
!1199 = !DILocation(line: 539, column: 11, scope: !1200)
!1200 = distinct !DILexicalBlock(scope: !1191, file: !1, line: 539, column: 11)
!1201 = !DILocation(line: 539, column: 15, scope: !1200)
!1202 = !DILocation(line: 539, column: 11, scope: !1191)
!1203 = !DILocation(line: 540, column: 9, scope: !1200)
!1204 = !DILocation(line: 542, column: 11, scope: !1205)
!1205 = distinct !DILexicalBlock(scope: !1191, file: !1, line: 542, column: 11)
!1206 = !DILocation(line: 542, column: 15, scope: !1205)
!1207 = !DILocation(line: 542, column: 26, scope: !1205)
!1208 = !DILocation(line: 542, column: 29, scope: !1209)
!1209 = !DILexicalBlockFile(scope: !1205, file: !1, discriminator: 1)
!1210 = !DILocation(line: 542, column: 33, scope: !1209)
!1211 = !DILocation(line: 542, column: 11, scope: !1209)
!1212 = !DILocation(line: 543, column: 32, scope: !1213)
!1213 = distinct !DILexicalBlock(scope: !1205, file: !1, line: 542, column: 45)
!1214 = !DILocation(line: 543, column: 38, scope: !1213)
!1215 = !DILocation(line: 543, column: 15, scope: !1213)
!1216 = !DILocation(line: 543, column: 13, scope: !1213)
!1217 = !DILocation(line: 544, column: 13, scope: !1218)
!1218 = distinct !DILexicalBlock(scope: !1213, file: !1, line: 544, column: 13)
!1219 = !DILocation(line: 544, column: 17, scope: !1218)
!1220 = !DILocation(line: 544, column: 28, scope: !1218)
!1221 = !DILocation(line: 544, column: 31, scope: !1222)
!1222 = !DILexicalBlockFile(scope: !1218, file: !1, discriminator: 1)
!1223 = !DILocation(line: 544, column: 35, scope: !1222)
!1224 = !DILocation(line: 544, column: 13, scope: !1222)
!1225 = !DILocation(line: 545, column: 11, scope: !1218)
!1226 = !DILocation(line: 546, column: 7, scope: !1213)
!1227 = !DILocation(line: 548, column: 7, scope: !1191)
!1228 = !DILocation(line: 548, column: 15, scope: !1191)
!1229 = !DILocation(line: 548, column: 29, scope: !1191)
!1230 = !DILocation(line: 548, column: 37, scope: !1191)
!1231 = !DILocation(line: 549, column: 7, scope: !1191)
!1232 = !DILocation(line: 553, column: 27, scope: !1175)
!1233 = !DILocation(line: 553, column: 5, scope: !1175)
!1234 = !DILocation(line: 553, column: 13, scope: !1175)
!1235 = !DILocation(line: 553, column: 25, scope: !1175)
!1236 = !DILocation(line: 554, column: 5, scope: !1175)
!1237 = !DILocation(line: 554, column: 13, scope: !1175)
!1238 = !DILocation(line: 554, column: 27, scope: !1175)
!1239 = !DILocation(line: 556, column: 9, scope: !1240)
!1240 = distinct !DILexicalBlock(scope: !1175, file: !1, line: 556, column: 9)
!1241 = !DILocation(line: 556, column: 17, scope: !1240)
!1242 = !DILocation(line: 556, column: 29, scope: !1240)
!1243 = !DILocation(line: 556, column: 9, scope: !1175)
!1244 = !DILocation(line: 558, column: 19, scope: !1245)
!1245 = distinct !DILexicalBlock(scope: !1240, file: !1, line: 556, column: 36)
!1246 = !DILocation(line: 558, column: 26, scope: !1245)
!1247 = !DILocation(line: 558, column: 34, scope: !1245)
!1248 = !DILocation(line: 558, column: 7, scope: !1245)
!1249 = !DILocation(line: 559, column: 7, scope: !1245)
!1250 = !DILocation(line: 562, column: 9, scope: !1251)
!1251 = distinct !DILexicalBlock(scope: !1175, file: !1, line: 562, column: 9)
!1252 = !DILocation(line: 562, column: 17, scope: !1251)
!1253 = !DILocation(line: 562, column: 22, scope: !1251)
!1254 = !DILocation(line: 562, column: 32, scope: !1251)
!1255 = !DILocation(line: 562, column: 36, scope: !1256)
!1256 = !DILexicalBlockFile(scope: !1251, file: !1, discriminator: 1)
!1257 = !DILocation(line: 562, column: 44, scope: !1256)
!1258 = !DILocation(line: 562, column: 50, scope: !1256)
!1259 = !DILocation(line: 562, column: 9, scope: !1256)
!1260 = !DILocalVariable(name: "timeout", scope: !1261, file: !1, line: 564, type: !1262)
!1261 = distinct !DILexicalBlock(scope: !1251, file: !1, line: 562, column: 75)
!1262 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !1263, line: 120, size: 128, align: 64, elements: !1264)
!1263 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1264 = !{!1265, !1267}
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !1262, file: !1263, line: 122, baseType: !1266, size: 64, align: 64)
!1266 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !434, line: 139, baseType: !246)
!1267 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !1262, file: !1263, line: 123, baseType: !1268, size: 64, align: 64, offset: 64)
!1268 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !434, line: 175, baseType: !246)
!1269 = !DILocation(line: 564, column: 23, scope: !1261)
!1270 = !DILocation(line: 565, column: 7, scope: !1261)
!1271 = !DILocation(line: 566, column: 5, scope: !1261)
!1272 = !DILocation(line: 526, column: 3, scope: !1154)
!1273 = !DILocation(line: 568, column: 1, scope: !616)
!1274 = !DILocalVariable(name: "loop", arg: 1, scope: !657, file: !1, line: 481, type: !175)
!1275 = !DILocation(line: 481, column: 40, scope: !657)
!1276 = !DILocalVariable(name: "accept_fd", arg: 2, scope: !657, file: !1, line: 481, type: !191)
!1277 = !DILocation(line: 481, column: 50, scope: !657)
!1278 = !DILocalVariable(name: "err", scope: !657, file: !1, line: 482, type: !191)
!1279 = !DILocation(line: 482, column: 7, scope: !657)
!1280 = !DILocalVariable(name: "emfile_fd", scope: !657, file: !1, line: 483, type: !191)
!1281 = !DILocation(line: 483, column: 7, scope: !657)
!1282 = !DILocation(line: 485, column: 7, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !657, file: !1, line: 485, column: 7)
!1284 = !DILocation(line: 485, column: 13, scope: !1283)
!1285 = !DILocation(line: 485, column: 23, scope: !1283)
!1286 = !DILocation(line: 485, column: 7, scope: !657)
!1287 = !DILocation(line: 486, column: 5, scope: !1283)
!1288 = !DILocation(line: 488, column: 13, scope: !657)
!1289 = !DILocation(line: 488, column: 19, scope: !657)
!1290 = !DILocation(line: 488, column: 3, scope: !657)
!1291 = !DILocation(line: 489, column: 3, scope: !657)
!1292 = !DILocation(line: 489, column: 9, scope: !657)
!1293 = !DILocation(line: 489, column: 19, scope: !657)
!1294 = !DILocation(line: 491, column: 3, scope: !657)
!1295 = !DILocation(line: 492, column: 22, scope: !1296)
!1296 = distinct !DILexicalBlock(scope: !657, file: !1, line: 491, column: 6)
!1297 = !DILocation(line: 492, column: 11, scope: !1296)
!1298 = !DILocation(line: 492, column: 9, scope: !1296)
!1299 = !DILocation(line: 493, column: 9, scope: !1300)
!1300 = distinct !DILexicalBlock(scope: !1296, file: !1, line: 493, column: 9)
!1301 = !DILocation(line: 493, column: 13, scope: !1300)
!1302 = !DILocation(line: 493, column: 9, scope: !1296)
!1303 = !DILocation(line: 494, column: 17, scope: !1300)
!1304 = !DILocation(line: 494, column: 7, scope: !1300)
!1305 = !DILocation(line: 495, column: 3, scope: !1296)
!1306 = !DILocation(line: 495, column: 12, scope: !1307)
!1307 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 1)
!1308 = !DILocation(line: 495, column: 16, scope: !1307)
!1309 = !DILocation(line: 495, column: 21, scope: !1307)
!1310 = !DILocation(line: 495, column: 24, scope: !1311)
!1311 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 2)
!1312 = !DILocation(line: 495, column: 28, scope: !1311)
!1313 = !DILocation(line: 495, column: 21, scope: !1311)
!1314 = !DILocation(line: 495, column: 3, scope: !1315)
!1315 = !DILexicalBlockFile(scope: !1296, file: !1, discriminator: 3)
!1316 = !DILocation(line: 497, column: 15, scope: !657)
!1317 = !DILocation(line: 497, column: 13, scope: !657)
!1318 = !DILocation(line: 498, column: 7, scope: !1319)
!1319 = distinct !DILexicalBlock(scope: !657, file: !1, line: 498, column: 7)
!1320 = !DILocation(line: 498, column: 17, scope: !1319)
!1321 = !DILocation(line: 498, column: 7, scope: !657)
!1322 = !DILocation(line: 499, column: 23, scope: !1319)
!1323 = !DILocation(line: 499, column: 5, scope: !1319)
!1324 = !DILocation(line: 499, column: 11, scope: !1319)
!1325 = !DILocation(line: 499, column: 21, scope: !1319)
!1326 = !DILocation(line: 501, column: 10, scope: !657)
!1327 = !DILocation(line: 501, column: 3, scope: !657)
!1328 = !DILocation(line: 502, column: 1, scope: !657)
!1329 = !DILocalVariable(name: "server", arg: 1, scope: !619, file: !1, line: 574, type: !395)
!1330 = !DILocation(line: 574, column: 28, scope: !619)
!1331 = !DILocalVariable(name: "client", arg: 2, scope: !619, file: !1, line: 574, type: !395)
!1332 = !DILocation(line: 574, column: 49, scope: !619)
!1333 = !DILocalVariable(name: "err", scope: !619, file: !1, line: 575, type: !191)
!1334 = !DILocation(line: 575, column: 7, scope: !619)
!1335 = !DILocation(line: 577, column: 3, scope: !619)
!1336 = !DILocation(line: 577, column: 3, scope: !1337)
!1337 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 1)
!1338 = !DILocation(line: 577, column: 3, scope: !1339)
!1339 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 2)
!1340 = !DILocation(line: 577, column: 3, scope: !1341)
!1341 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 3)
!1342 = !DILocation(line: 579, column: 7, scope: !1343)
!1343 = distinct !DILexicalBlock(scope: !619, file: !1, line: 579, column: 7)
!1344 = !DILocation(line: 579, column: 15, scope: !1343)
!1345 = !DILocation(line: 579, column: 27, scope: !1343)
!1346 = !DILocation(line: 579, column: 7, scope: !619)
!1347 = !DILocation(line: 580, column: 5, scope: !1343)
!1348 = !DILocation(line: 582, column: 11, scope: !619)
!1349 = !DILocation(line: 582, column: 19, scope: !619)
!1350 = !DILocation(line: 582, column: 3, scope: !619)
!1351 = !DILocation(line: 585, column: 29, scope: !1352)
!1352 = distinct !DILexicalBlock(scope: !619, file: !1, line: 582, column: 25)
!1353 = !DILocation(line: 586, column: 29, scope: !1352)
!1354 = !DILocation(line: 586, column: 37, scope: !1352)
!1355 = !DILocation(line: 585, column: 13, scope: !1352)
!1356 = !DILocation(line: 585, column: 11, scope: !1352)
!1357 = !DILocation(line: 588, column: 11, scope: !1358)
!1358 = distinct !DILexicalBlock(scope: !1352, file: !1, line: 588, column: 11)
!1359 = !DILocation(line: 588, column: 11, scope: !1352)
!1360 = !DILocation(line: 590, column: 19, scope: !1361)
!1361 = distinct !DILexicalBlock(scope: !1358, file: !1, line: 588, column: 16)
!1362 = !DILocation(line: 590, column: 27, scope: !1361)
!1363 = !DILocation(line: 590, column: 9, scope: !1361)
!1364 = !DILocation(line: 591, column: 9, scope: !1361)
!1365 = !DILocation(line: 593, column: 7, scope: !1352)
!1366 = !DILocation(line: 596, column: 37, scope: !1352)
!1367 = !DILocation(line: 596, column: 25, scope: !1352)
!1368 = !DILocation(line: 596, column: 45, scope: !1352)
!1369 = !DILocation(line: 596, column: 53, scope: !1352)
!1370 = !DILocation(line: 596, column: 13, scope: !1352)
!1371 = !DILocation(line: 596, column: 11, scope: !1352)
!1372 = !DILocation(line: 597, column: 11, scope: !1373)
!1373 = distinct !DILexicalBlock(scope: !1352, file: !1, line: 597, column: 11)
!1374 = !DILocation(line: 597, column: 11, scope: !1352)
!1375 = !DILocation(line: 598, column: 19, scope: !1376)
!1376 = distinct !DILexicalBlock(scope: !1373, file: !1, line: 597, column: 16)
!1377 = !DILocation(line: 598, column: 27, scope: !1376)
!1378 = !DILocation(line: 598, column: 9, scope: !1376)
!1379 = !DILocation(line: 599, column: 9, scope: !1376)
!1380 = !DILocation(line: 601, column: 7, scope: !1352)
!1381 = !DILocation(line: 604, column: 7, scope: !1352)
!1382 = !DILocation(line: 607, column: 3, scope: !619)
!1383 = !DILocation(line: 607, column: 11, scope: !619)
!1384 = !DILocation(line: 607, column: 17, scope: !619)
!1385 = !DILocation(line: 611, column: 7, scope: !1386)
!1386 = distinct !DILexicalBlock(scope: !619, file: !1, line: 611, column: 7)
!1387 = !DILocation(line: 611, column: 15, scope: !1386)
!1388 = !DILocation(line: 611, column: 26, scope: !1386)
!1389 = !DILocation(line: 611, column: 7, scope: !619)
!1390 = !DILocalVariable(name: "queued_fds", scope: !1391, file: !1, line: 612, type: !1392)
!1391 = distinct !DILexicalBlock(scope: !1386, file: !1, line: 611, column: 35)
!1392 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1393, size: 64, align: 64)
!1393 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__stream_queued_fds_t", file: !47, line: 121, baseType: !1394)
!1394 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__stream_queued_fds_s", file: !47, line: 153, size: 96, align: 32, elements: !1395)
!1395 = !{!1396, !1397, !1398}
!1396 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !1394, file: !47, line: 154, baseType: !181, size: 32, align: 32)
!1397 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !1394, file: !47, line: 155, baseType: !181, size: 32, align: 32, offset: 32)
!1398 = !DIDerivedType(tag: DW_TAG_member, name: "fds", scope: !1394, file: !47, line: 156, baseType: !1399, size: 32, align: 32, offset: 64)
!1399 = !DICompositeType(tag: DW_TAG_array_type, baseType: !191, size: 32, align: 32, elements: !1400)
!1400 = !{!1401}
!1401 = !DISubrange(count: 1)
!1402 = !DILocation(line: 612, column: 30, scope: !1391)
!1403 = !DILocation(line: 614, column: 18, scope: !1391)
!1404 = !DILocation(line: 614, column: 26, scope: !1391)
!1405 = !DILocation(line: 614, column: 16, scope: !1391)
!1406 = !DILocation(line: 617, column: 27, scope: !1391)
!1407 = !DILocation(line: 617, column: 39, scope: !1391)
!1408 = !DILocation(line: 617, column: 5, scope: !1391)
!1409 = !DILocation(line: 617, column: 13, scope: !1391)
!1410 = !DILocation(line: 617, column: 25, scope: !1391)
!1411 = !DILocation(line: 620, column: 5, scope: !1391)
!1412 = !DILocation(line: 620, column: 5, scope: !1413)
!1413 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 1)
!1414 = !DILocation(line: 620, column: 5, scope: !1415)
!1415 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 2)
!1416 = !DILocation(line: 620, column: 5, scope: !1417)
!1417 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 3)
!1418 = !DILocation(line: 621, column: 11, scope: !1419)
!1419 = distinct !DILexicalBlock(scope: !1391, file: !1, line: 621, column: 9)
!1420 = !DILocation(line: 621, column: 23, scope: !1419)
!1421 = !DILocation(line: 621, column: 9, scope: !1419)
!1422 = !DILocation(line: 621, column: 30, scope: !1419)
!1423 = !DILocation(line: 621, column: 9, scope: !1391)
!1424 = !DILocation(line: 622, column: 16, scope: !1425)
!1425 = distinct !DILexicalBlock(scope: !1419, file: !1, line: 621, column: 36)
!1426 = !DILocation(line: 622, column: 7, scope: !1425)
!1427 = !DILocation(line: 623, column: 7, scope: !1425)
!1428 = !DILocation(line: 623, column: 15, scope: !1425)
!1429 = !DILocation(line: 623, column: 26, scope: !1425)
!1430 = !DILocation(line: 624, column: 5, scope: !1425)
!1431 = !DILocation(line: 626, column: 15, scope: !1432)
!1432 = distinct !DILexicalBlock(scope: !1419, file: !1, line: 624, column: 12)
!1433 = !DILocation(line: 626, column: 27, scope: !1432)
!1434 = !DILocation(line: 626, column: 7, scope: !1432)
!1435 = !DILocation(line: 627, column: 15, scope: !1432)
!1436 = !DILocation(line: 627, column: 27, scope: !1432)
!1437 = !DILocation(line: 627, column: 31, scope: !1432)
!1438 = !DILocation(line: 628, column: 15, scope: !1432)
!1439 = !DILocation(line: 628, column: 27, scope: !1432)
!1440 = !DILocation(line: 628, column: 34, scope: !1432)
!1441 = !DILocation(line: 630, column: 3, scope: !1391)
!1442 = !DILocation(line: 631, column: 5, scope: !1443)
!1443 = distinct !DILexicalBlock(scope: !1386, file: !1, line: 630, column: 10)
!1444 = !DILocation(line: 631, column: 13, scope: !1443)
!1445 = !DILocation(line: 631, column: 25, scope: !1443)
!1446 = !DILocation(line: 632, column: 9, scope: !1447)
!1447 = distinct !DILexicalBlock(scope: !1443, file: !1, line: 632, column: 9)
!1448 = !DILocation(line: 632, column: 13, scope: !1447)
!1449 = !DILocation(line: 632, column: 9, scope: !1443)
!1450 = !DILocation(line: 633, column: 20, scope: !1447)
!1451 = !DILocation(line: 633, column: 28, scope: !1447)
!1452 = !DILocation(line: 633, column: 35, scope: !1447)
!1453 = !DILocation(line: 633, column: 43, scope: !1447)
!1454 = !DILocation(line: 633, column: 7, scope: !1447)
!1455 = !DILocation(line: 635, column: 10, scope: !619)
!1456 = !DILocation(line: 635, column: 3, scope: !619)
!1457 = !DILocation(line: 636, column: 1, scope: !619)
!1458 = !DILocalVariable(name: "stream", arg: 1, scope: !622, file: !1, line: 639, type: !395)
!1459 = !DILocation(line: 639, column: 28, scope: !622)
!1460 = !DILocalVariable(name: "backlog", arg: 2, scope: !622, file: !1, line: 639, type: !191)
!1461 = !DILocation(line: 639, column: 40, scope: !622)
!1462 = !DILocalVariable(name: "cb", arg: 3, scope: !622, file: !1, line: 639, type: !472)
!1463 = !DILocation(line: 639, column: 66, scope: !622)
!1464 = !DILocalVariable(name: "err", scope: !622, file: !1, line: 640, type: !191)
!1465 = !DILocation(line: 640, column: 7, scope: !622)
!1466 = !DILocation(line: 642, column: 11, scope: !622)
!1467 = !DILocation(line: 642, column: 19, scope: !622)
!1468 = !DILocation(line: 642, column: 3, scope: !622)
!1469 = !DILocation(line: 644, column: 36, scope: !1470)
!1470 = distinct !DILexicalBlock(scope: !622, file: !1, line: 642, column: 25)
!1471 = !DILocation(line: 644, column: 25, scope: !1470)
!1472 = !DILocation(line: 644, column: 44, scope: !1470)
!1473 = !DILocation(line: 644, column: 53, scope: !1470)
!1474 = !DILocation(line: 644, column: 11, scope: !1470)
!1475 = !DILocation(line: 644, column: 9, scope: !1470)
!1476 = !DILocation(line: 645, column: 5, scope: !1470)
!1477 = !DILocation(line: 648, column: 38, scope: !1470)
!1478 = !DILocation(line: 648, column: 26, scope: !1470)
!1479 = !DILocation(line: 648, column: 46, scope: !1470)
!1480 = !DILocation(line: 648, column: 55, scope: !1470)
!1481 = !DILocation(line: 648, column: 11, scope: !1470)
!1482 = !DILocation(line: 648, column: 9, scope: !1470)
!1483 = !DILocation(line: 649, column: 5, scope: !1470)
!1484 = !DILocation(line: 652, column: 9, scope: !1470)
!1485 = !DILocation(line: 653, column: 3, scope: !1470)
!1486 = !DILocation(line: 655, column: 7, scope: !1487)
!1487 = distinct !DILexicalBlock(scope: !622, file: !1, line: 655, column: 7)
!1488 = !DILocation(line: 655, column: 11, scope: !1487)
!1489 = !DILocation(line: 655, column: 7, scope: !622)
!1490 = !DILocation(line: 656, column: 5, scope: !1487)
!1491 = !DILocation(line: 656, column: 5, scope: !1492)
!1492 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 1)
!1493 = distinct !DILexicalBlock(scope: !1487, file: !1, line: 656, column: 5)
!1494 = !DILocation(line: 656, column: 5, scope: !1495)
!1495 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 2)
!1496 = !DILocation(line: 656, column: 5, scope: !1497)
!1497 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 3)
!1498 = !DILocation(line: 656, column: 5, scope: !1499)
!1499 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 4)
!1500 = !DILocation(line: 656, column: 5, scope: !1501)
!1501 = !DILexicalBlockFile(scope: !1502, file: !1, discriminator: 5)
!1502 = distinct !DILexicalBlock(scope: !1493, file: !1, line: 656, column: 5)
!1503 = !DILocation(line: 656, column: 5, scope: !1504)
!1504 = !DILexicalBlockFile(scope: !1502, file: !1, discriminator: 6)
!1505 = !DILocation(line: 656, column: 5, scope: !1506)
!1506 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 7)
!1507 = !DILocation(line: 656, column: 5, scope: !1508)
!1508 = !DILexicalBlockFile(scope: !1509, file: !1, discriminator: 8)
!1509 = distinct !DILexicalBlock(scope: !1493, file: !1, line: 656, column: 5)
!1510 = !DILocation(line: 656, column: 5, scope: !1511)
!1511 = !DILexicalBlockFile(scope: !1512, file: !1, discriminator: 9)
!1512 = distinct !DILexicalBlock(scope: !1509, file: !1, line: 656, column: 5)
!1513 = !DILocation(line: 656, column: 5, scope: !1514)
!1514 = !DILexicalBlockFile(scope: !1512, file: !1, discriminator: 10)
!1515 = !DILocation(line: 656, column: 5, scope: !1516)
!1516 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 11)
!1517 = !DILocation(line: 656, column: 5, scope: !1518)
!1518 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 12)
!1519 = !DILocation(line: 658, column: 10, scope: !622)
!1520 = !DILocation(line: 658, column: 3, scope: !622)
!1521 = !DILocalVariable(name: "fd", arg: 1, scope: !625, file: !1, line: 956, type: !191)
!1522 = !DILocation(line: 956, column: 36, scope: !625)
!1523 = !DILocalVariable(name: "ss", scope: !625, file: !1, line: 957, type: !1524)
!1524 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !157, line: 162, size: 1024, align: 64, elements: !1525)
!1525 = !{!1526, !1527, !1528}
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !1524, file: !157, line: 164, baseType: !516, size: 16, align: 16)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !1524, file: !157, line: 165, baseType: !189, size: 64, align: 64, offset: 64)
!1528 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_padding", scope: !1524, file: !157, line: 166, baseType: !1529, size: 896, align: 8, offset: 128)
!1529 = !DICompositeType(tag: DW_TAG_array_type, baseType: !242, size: 896, align: 8, elements: !1530)
!1530 = !{!1531}
!1531 = !DISubrange(count: 112)
!1532 = !DILocation(line: 957, column: 27, scope: !625)
!1533 = !DILocalVariable(name: "sslen", scope: !625, file: !1, line: 958, type: !673)
!1534 = !DILocation(line: 958, column: 13, scope: !625)
!1535 = !DILocalVariable(name: "len", scope: !625, file: !1, line: 959, type: !673)
!1536 = !DILocation(line: 959, column: 13, scope: !625)
!1537 = !DILocalVariable(name: "type", scope: !625, file: !1, line: 960, type: !191)
!1538 = !DILocation(line: 960, column: 7, scope: !625)
!1539 = !DILocation(line: 962, column: 3, scope: !625)
!1540 = !DILocation(line: 963, column: 9, scope: !625)
!1541 = !DILocation(line: 965, column: 19, scope: !1542)
!1542 = distinct !DILexicalBlock(scope: !625, file: !1, line: 965, column: 7)
!1543 = !DILocation(line: 965, column: 23, scope: !1542)
!1544 = !DILocation(line: 965, column: 7, scope: !1542)
!1545 = !DILocation(line: 965, column: 7, scope: !625)
!1546 = !DILocation(line: 966, column: 5, scope: !1542)
!1547 = !DILocation(line: 968, column: 7, scope: !625)
!1548 = !DILocation(line: 970, column: 18, scope: !1549)
!1549 = distinct !DILexicalBlock(scope: !625, file: !1, line: 970, column: 7)
!1550 = !DILocation(line: 970, column: 43, scope: !1549)
!1551 = !DILocation(line: 970, column: 7, scope: !1549)
!1552 = !DILocation(line: 970, column: 7, scope: !625)
!1553 = !DILocation(line: 971, column: 5, scope: !1549)
!1554 = !DILocation(line: 973, column: 7, scope: !1555)
!1555 = distinct !DILexicalBlock(scope: !625, file: !1, line: 973, column: 7)
!1556 = !DILocation(line: 973, column: 12, scope: !1555)
!1557 = !DILocation(line: 973, column: 7, scope: !625)
!1558 = !DILocation(line: 982, column: 16, scope: !1559)
!1559 = distinct !DILexicalBlock(scope: !1555, file: !1, line: 973, column: 28)
!1560 = !DILocation(line: 982, column: 13, scope: !1559)
!1561 = !DILocation(line: 982, column: 5, scope: !1559)
!1562 = !DILocation(line: 984, column: 9, scope: !1563)
!1563 = distinct !DILexicalBlock(scope: !1559, file: !1, line: 982, column: 27)
!1564 = !DILocation(line: 987, column: 9, scope: !1563)
!1565 = !DILocation(line: 989, column: 3, scope: !1559)
!1566 = !DILocation(line: 991, column: 7, scope: !1567)
!1567 = distinct !DILexicalBlock(scope: !625, file: !1, line: 991, column: 7)
!1568 = !DILocation(line: 991, column: 12, scope: !1567)
!1569 = !DILocation(line: 991, column: 26, scope: !1567)
!1570 = !DILocation(line: 992, column: 11, scope: !1567)
!1571 = !DILocation(line: 992, column: 8, scope: !1567)
!1572 = !DILocation(line: 992, column: 21, scope: !1567)
!1573 = !DILocation(line: 992, column: 32, scope: !1567)
!1574 = !DILocation(line: 992, column: 38, scope: !1575)
!1575 = !DILexicalBlockFile(scope: !1567, file: !1, discriminator: 1)
!1576 = !DILocation(line: 992, column: 35, scope: !1575)
!1577 = !DILocation(line: 992, column: 48, scope: !1575)
!1578 = !DILocation(line: 991, column: 7, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !625, file: !1, discriminator: 1)
!1580 = !DILocation(line: 993, column: 5, scope: !1567)
!1581 = !DILocation(line: 995, column: 3, scope: !625)
!1582 = !DILocation(line: 996, column: 1, scope: !625)
!1583 = !DILocalVariable(name: "req", arg: 1, scope: !628, file: !1, line: 1246, type: !454)
!1584 = !DILocation(line: 1246, column: 32, scope: !628)
!1585 = !DILocalVariable(name: "stream", arg: 2, scope: !628, file: !1, line: 1246, type: !395)
!1586 = !DILocation(line: 1246, column: 50, scope: !628)
!1587 = !DILocalVariable(name: "cb", arg: 3, scope: !628, file: !1, line: 1246, type: !464)
!1588 = !DILocation(line: 1246, column: 73, scope: !628)
!1589 = !DILocation(line: 1247, column: 3, scope: !628)
!1590 = !DILocation(line: 1247, column: 3, scope: !1591)
!1591 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 1)
!1592 = !DILocation(line: 1247, column: 3, scope: !1593)
!1593 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 2)
!1594 = !DILocation(line: 1247, column: 3, scope: !1595)
!1595 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 3)
!1596 = !DILocation(line: 1247, column: 3, scope: !1597)
!1597 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 4)
!1598 = !DILocation(line: 1247, column: 3, scope: !1599)
!1599 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 5)
!1600 = !DILocation(line: 1250, column: 9, scope: !1601)
!1601 = distinct !DILexicalBlock(scope: !628, file: !1, line: 1250, column: 7)
!1602 = !DILocation(line: 1250, column: 17, scope: !1601)
!1603 = !DILocation(line: 1250, column: 23, scope: !1601)
!1604 = !DILocation(line: 1250, column: 45, scope: !1601)
!1605 = !DILocation(line: 1251, column: 7, scope: !1601)
!1606 = !DILocation(line: 1251, column: 15, scope: !1601)
!1607 = !DILocation(line: 1251, column: 21, scope: !1601)
!1608 = !DILocation(line: 1251, column: 38, scope: !1601)
!1609 = !DILocation(line: 1252, column: 7, scope: !1601)
!1610 = !DILocation(line: 1252, column: 15, scope: !1601)
!1611 = !DILocation(line: 1252, column: 21, scope: !1601)
!1612 = !DILocation(line: 1252, column: 42, scope: !1601)
!1613 = !DILocation(line: 1253, column: 7, scope: !1601)
!1614 = !DILocation(line: 1250, column: 7, scope: !1591)
!1615 = !DILocation(line: 1254, column: 5, scope: !1616)
!1616 = distinct !DILexicalBlock(scope: !1601, file: !1, line: 1253, column: 31)
!1617 = !DILocation(line: 1257, column: 3, scope: !628)
!1618 = !DILocation(line: 1257, column: 3, scope: !1591)
!1619 = !DILocation(line: 1257, column: 3, scope: !1593)
!1620 = !DILocation(line: 1257, column: 3, scope: !1595)
!1621 = !DILocation(line: 1260, column: 3, scope: !628)
!1622 = !DILocation(line: 1260, column: 3, scope: !1623)
!1623 = !DILexicalBlockFile(scope: !1624, file: !1, discriminator: 1)
!1624 = distinct !DILexicalBlock(scope: !628, file: !1, line: 1260, column: 3)
!1625 = !DILocation(line: 1260, column: 3, scope: !1626)
!1626 = !DILexicalBlockFile(scope: !1627, file: !1, discriminator: 2)
!1627 = distinct !DILexicalBlock(scope: !1624, file: !1, line: 1260, column: 3)
!1628 = !DILocation(line: 1260, column: 3, scope: !1629)
!1629 = !DILexicalBlockFile(scope: !1624, file: !1, discriminator: 3)
!1630 = !DILocation(line: 1260, column: 3, scope: !1631)
!1631 = !DILexicalBlockFile(scope: !1632, file: !1, discriminator: 4)
!1632 = distinct !DILexicalBlock(scope: !1624, file: !1, line: 1260, column: 3)
!1633 = !DILocation(line: 1260, column: 3, scope: !1634)
!1634 = !DILexicalBlockFile(scope: !1635, file: !1, discriminator: 5)
!1635 = distinct !DILexicalBlock(scope: !1632, file: !1, line: 1260, column: 3)
!1636 = !DILocation(line: 1260, column: 3, scope: !1637)
!1637 = !DILexicalBlockFile(scope: !1632, file: !1, discriminator: 6)
!1638 = !DILocation(line: 1260, column: 3, scope: !1639)
!1639 = !DILexicalBlockFile(scope: !1624, file: !1, discriminator: 7)
!1640 = !DILocation(line: 1261, column: 17, scope: !628)
!1641 = !DILocation(line: 1261, column: 3, scope: !628)
!1642 = !DILocation(line: 1261, column: 8, scope: !628)
!1643 = !DILocation(line: 1261, column: 15, scope: !628)
!1644 = !DILocation(line: 1262, column: 13, scope: !628)
!1645 = !DILocation(line: 1262, column: 3, scope: !628)
!1646 = !DILocation(line: 1262, column: 8, scope: !628)
!1647 = !DILocation(line: 1262, column: 11, scope: !628)
!1648 = !DILocation(line: 1263, column: 26, scope: !628)
!1649 = !DILocation(line: 1263, column: 3, scope: !628)
!1650 = !DILocation(line: 1263, column: 11, scope: !628)
!1651 = !DILocation(line: 1263, column: 24, scope: !628)
!1652 = !DILocation(line: 1264, column: 3, scope: !628)
!1653 = !DILocation(line: 1264, column: 11, scope: !628)
!1654 = !DILocation(line: 1264, column: 17, scope: !628)
!1655 = !DILocation(line: 1266, column: 16, scope: !628)
!1656 = !DILocation(line: 1266, column: 24, scope: !628)
!1657 = !DILocation(line: 1266, column: 31, scope: !628)
!1658 = !DILocation(line: 1266, column: 39, scope: !628)
!1659 = !DILocation(line: 1266, column: 3, scope: !628)
!1660 = !DILocation(line: 1267, column: 35, scope: !628)
!1661 = !DILocation(line: 1267, column: 3, scope: !628)
!1662 = !DILocation(line: 1269, column: 3, scope: !628)
!1663 = !DILocation(line: 1270, column: 1, scope: !628)
!1664 = !DILocalVariable(name: "stream", arg: 1, scope: !661, file: !1, line: 109, type: !395)
!1665 = !DILocation(line: 109, column: 58, scope: !661)
!1666 = !DILocation(line: 131, column: 1, scope: !661)
!1667 = !DILocalVariable(name: "req", arg: 1, scope: !631, file: !1, line: 1379, type: !380)
!1668 = !DILocation(line: 1379, column: 27, scope: !631)
!1669 = !DILocalVariable(name: "stream", arg: 2, scope: !631, file: !1, line: 1380, type: !395)
!1670 = !DILocation(line: 1380, column: 28, scope: !631)
!1671 = !DILocalVariable(name: "bufs", arg: 3, scope: !631, file: !1, line: 1381, type: !435)
!1672 = !DILocation(line: 1381, column: 30, scope: !631)
!1673 = !DILocalVariable(name: "nbufs", arg: 4, scope: !631, file: !1, line: 1382, type: !181)
!1674 = !DILocation(line: 1382, column: 28, scope: !631)
!1675 = !DILocalVariable(name: "send_handle", arg: 5, scope: !631, file: !1, line: 1383, type: !395)
!1676 = !DILocation(line: 1383, column: 28, scope: !631)
!1677 = !DILocalVariable(name: "cb", arg: 6, scope: !631, file: !1, line: 1384, type: !390)
!1678 = !DILocation(line: 1384, column: 27, scope: !631)
!1679 = !DILocalVariable(name: "empty_queue", scope: !631, file: !1, line: 1385, type: !191)
!1680 = !DILocation(line: 1385, column: 7, scope: !631)
!1681 = !DILocation(line: 1387, column: 3, scope: !631)
!1682 = !DILocation(line: 1387, column: 3, scope: !1683)
!1683 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 1)
!1684 = !DILocation(line: 1387, column: 3, scope: !1685)
!1685 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 2)
!1686 = !DILocation(line: 1387, column: 3, scope: !1687)
!1687 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 3)
!1688 = !DILocation(line: 1388, column: 3, scope: !631)
!1689 = !DILocation(line: 1388, column: 3, scope: !1683)
!1690 = !DILocation(line: 1388, column: 3, scope: !1685)
!1691 = !DILocation(line: 1388, column: 3, scope: !1687)
!1692 = !DILocation(line: 1388, column: 3, scope: !1693)
!1693 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 4)
!1694 = !DILocation(line: 1388, column: 3, scope: !1695)
!1695 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 5)
!1696 = !DILocation(line: 1388, column: 3, scope: !1697)
!1697 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 6)
!1698 = !DILocation(line: 1393, column: 7, scope: !1699)
!1699 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1393, column: 7)
!1700 = !DILocation(line: 1393, column: 29, scope: !1699)
!1701 = !DILocation(line: 1393, column: 7, scope: !631)
!1702 = !DILocation(line: 1394, column: 5, scope: !1699)
!1703 = !DILocation(line: 1396, column: 7, scope: !1704)
!1704 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1396, column: 7)
!1705 = !DILocation(line: 1396, column: 7, scope: !631)
!1706 = !DILocation(line: 1397, column: 9, scope: !1707)
!1707 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 1397, column: 9)
!1708 = distinct !DILexicalBlock(scope: !1704, file: !1, line: 1396, column: 20)
!1709 = !DILocation(line: 1397, column: 17, scope: !1707)
!1710 = !DILocation(line: 1397, column: 22, scope: !1707)
!1711 = !DILocation(line: 1397, column: 39, scope: !1707)
!1712 = !DILocation(line: 1397, column: 56, scope: !1713)
!1713 = !DILexicalBlockFile(scope: !1707, file: !1, discriminator: 1)
!1714 = !DILocation(line: 1397, column: 65, scope: !1713)
!1715 = !DILocation(line: 1397, column: 43, scope: !1713)
!1716 = !DILocation(line: 1397, column: 9, scope: !1713)
!1717 = !DILocation(line: 1398, column: 7, scope: !1707)
!1718 = !DILocation(line: 1406, column: 38, scope: !1719)
!1719 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 1406, column: 9)
!1720 = !DILocation(line: 1406, column: 23, scope: !1719)
!1721 = !DILocation(line: 1406, column: 9, scope: !1719)
!1722 = !DILocation(line: 1406, column: 51, scope: !1719)
!1723 = !DILocation(line: 1406, column: 9, scope: !1708)
!1724 = !DILocation(line: 1407, column: 7, scope: !1719)
!1725 = !DILocation(line: 1408, column: 3, scope: !1708)
!1726 = !DILocation(line: 1416, column: 18, scope: !631)
!1727 = !DILocation(line: 1416, column: 26, scope: !631)
!1728 = !DILocation(line: 1416, column: 43, scope: !631)
!1729 = !DILocation(line: 1416, column: 15, scope: !631)
!1730 = !DILocation(line: 1419, column: 3, scope: !631)
!1731 = !DILocation(line: 1419, column: 3, scope: !1732)
!1732 = !DILexicalBlockFile(scope: !1733, file: !1, discriminator: 1)
!1733 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1419, column: 3)
!1734 = !DILocation(line: 1419, column: 3, scope: !1735)
!1735 = !DILexicalBlockFile(scope: !1736, file: !1, discriminator: 2)
!1736 = distinct !DILexicalBlock(scope: !1733, file: !1, line: 1419, column: 3)
!1737 = !DILocation(line: 1419, column: 3, scope: !1738)
!1738 = !DILexicalBlockFile(scope: !1733, file: !1, discriminator: 3)
!1739 = !DILocation(line: 1419, column: 3, scope: !1740)
!1740 = !DILexicalBlockFile(scope: !1741, file: !1, discriminator: 4)
!1741 = distinct !DILexicalBlock(scope: !1733, file: !1, line: 1419, column: 3)
!1742 = !DILocation(line: 1419, column: 3, scope: !1743)
!1743 = !DILexicalBlockFile(scope: !1744, file: !1, discriminator: 5)
!1744 = distinct !DILexicalBlock(scope: !1741, file: !1, line: 1419, column: 3)
!1745 = !DILocation(line: 1419, column: 3, scope: !1746)
!1746 = !DILexicalBlockFile(scope: !1741, file: !1, discriminator: 6)
!1747 = !DILocation(line: 1419, column: 3, scope: !1748)
!1748 = !DILexicalBlockFile(scope: !1733, file: !1, discriminator: 7)
!1749 = !DILocation(line: 1420, column: 13, scope: !631)
!1750 = !DILocation(line: 1420, column: 3, scope: !631)
!1751 = !DILocation(line: 1420, column: 8, scope: !631)
!1752 = !DILocation(line: 1420, column: 11, scope: !631)
!1753 = !DILocation(line: 1421, column: 17, scope: !631)
!1754 = !DILocation(line: 1421, column: 3, scope: !631)
!1755 = !DILocation(line: 1421, column: 8, scope: !631)
!1756 = !DILocation(line: 1421, column: 15, scope: !631)
!1757 = !DILocation(line: 1422, column: 3, scope: !631)
!1758 = !DILocation(line: 1422, column: 8, scope: !631)
!1759 = !DILocation(line: 1422, column: 14, scope: !631)
!1760 = !DILocation(line: 1423, column: 22, scope: !631)
!1761 = !DILocation(line: 1423, column: 3, scope: !631)
!1762 = !DILocation(line: 1423, column: 8, scope: !631)
!1763 = !DILocation(line: 1423, column: 20, scope: !631)
!1764 = !DILocation(line: 1424, column: 3, scope: !631)
!1765 = !DILocation(line: 1424, column: 3, scope: !1766)
!1766 = !DILexicalBlockFile(scope: !1767, file: !1, discriminator: 1)
!1767 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1424, column: 3)
!1768 = !DILocation(line: 1426, column: 15, scope: !631)
!1769 = !DILocation(line: 1426, column: 20, scope: !631)
!1770 = !DILocation(line: 1426, column: 3, scope: !631)
!1771 = !DILocation(line: 1426, column: 8, scope: !631)
!1772 = !DILocation(line: 1426, column: 13, scope: !631)
!1773 = !DILocation(line: 1427, column: 7, scope: !1774)
!1774 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1427, column: 7)
!1775 = !DILocation(line: 1427, column: 13, scope: !1774)
!1776 = !DILocation(line: 1427, column: 7, scope: !631)
!1777 = !DILocation(line: 1428, column: 28, scope: !1774)
!1778 = !DILocation(line: 1428, column: 34, scope: !1774)
!1779 = !DILocation(line: 1428, column: 17, scope: !1774)
!1780 = !DILocation(line: 1428, column: 5, scope: !1774)
!1781 = !DILocation(line: 1428, column: 10, scope: !1774)
!1782 = !DILocation(line: 1428, column: 15, scope: !1774)
!1783 = !DILocation(line: 1430, column: 7, scope: !1784)
!1784 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1430, column: 7)
!1785 = !DILocation(line: 1430, column: 12, scope: !1784)
!1786 = !DILocation(line: 1430, column: 17, scope: !1784)
!1787 = !DILocation(line: 1430, column: 7, scope: !631)
!1788 = !DILocation(line: 1431, column: 5, scope: !1784)
!1789 = !DILocation(line: 1433, column: 10, scope: !631)
!1790 = !DILocation(line: 1433, column: 15, scope: !631)
!1791 = !DILocation(line: 1433, column: 3, scope: !631)
!1792 = !DILocation(line: 1433, column: 21, scope: !631)
!1793 = !DILocation(line: 1433, column: 27, scope: !631)
!1794 = !DILocation(line: 1433, column: 33, scope: !631)
!1795 = !DILocation(line: 1434, column: 16, scope: !631)
!1796 = !DILocation(line: 1434, column: 3, scope: !631)
!1797 = !DILocation(line: 1434, column: 8, scope: !631)
!1798 = !DILocation(line: 1434, column: 14, scope: !631)
!1799 = !DILocation(line: 1435, column: 3, scope: !631)
!1800 = !DILocation(line: 1435, column: 8, scope: !631)
!1801 = !DILocation(line: 1435, column: 20, scope: !631)
!1802 = !DILocation(line: 1436, column: 46, scope: !631)
!1803 = !DILocation(line: 1436, column: 52, scope: !631)
!1804 = !DILocation(line: 1436, column: 31, scope: !631)
!1805 = !DILocation(line: 1436, column: 3, scope: !631)
!1806 = !DILocation(line: 1436, column: 11, scope: !631)
!1807 = !DILocation(line: 1436, column: 28, scope: !631)
!1808 = !DILocation(line: 1439, column: 3, scope: !631)
!1809 = !DILocation(line: 1439, column: 3, scope: !1810)
!1810 = !DILexicalBlockFile(scope: !1811, file: !1, discriminator: 1)
!1811 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1439, column: 3)
!1812 = !DILocation(line: 1445, column: 7, scope: !1813)
!1813 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1445, column: 7)
!1814 = !DILocation(line: 1445, column: 15, scope: !1813)
!1815 = !DILocation(line: 1445, column: 7, scope: !631)
!1816 = !DILocation(line: 1447, column: 3, scope: !1817)
!1817 = distinct !DILexicalBlock(scope: !1813, file: !1, line: 1445, column: 28)
!1818 = !DILocation(line: 1448, column: 12, scope: !1819)
!1819 = distinct !DILexicalBlock(scope: !1813, file: !1, line: 1448, column: 12)
!1820 = !DILocation(line: 1448, column: 12, scope: !1813)
!1821 = !DILocation(line: 1449, column: 15, scope: !1822)
!1822 = distinct !DILexicalBlock(scope: !1819, file: !1, line: 1448, column: 25)
!1823 = !DILocation(line: 1449, column: 5, scope: !1822)
!1824 = !DILocation(line: 1450, column: 3, scope: !1822)
!1825 = !DILocation(line: 1457, column: 5, scope: !1826)
!1826 = distinct !DILexicalBlock(scope: !1819, file: !1, line: 1451, column: 8)
!1827 = !DILocation(line: 1457, column: 5, scope: !1828)
!1828 = !DILexicalBlockFile(scope: !1826, file: !1, discriminator: 1)
!1829 = !DILocation(line: 1457, column: 5, scope: !1830)
!1830 = !DILexicalBlockFile(scope: !1826, file: !1, discriminator: 2)
!1831 = !DILocation(line: 1457, column: 5, scope: !1832)
!1832 = !DILexicalBlockFile(scope: !1826, file: !1, discriminator: 3)
!1833 = !DILocation(line: 1458, column: 18, scope: !1826)
!1834 = !DILocation(line: 1458, column: 26, scope: !1826)
!1835 = !DILocation(line: 1458, column: 33, scope: !1826)
!1836 = !DILocation(line: 1458, column: 41, scope: !1826)
!1837 = !DILocation(line: 1458, column: 5, scope: !1826)
!1838 = !DILocation(line: 1459, column: 37, scope: !1826)
!1839 = !DILocation(line: 1459, column: 5, scope: !1826)
!1840 = !DILocation(line: 1462, column: 3, scope: !631)
!1841 = !DILocation(line: 1463, column: 1, scope: !631)
!1842 = !DILocalVariable(name: "handle", arg: 1, scope: !685, file: !1, line: 732, type: !168)
!1843 = !DILocation(line: 732, column: 39, scope: !685)
!1844 = !DILocation(line: 733, column: 11, scope: !685)
!1845 = !DILocation(line: 733, column: 19, scope: !685)
!1846 = !DILocation(line: 733, column: 3, scope: !685)
!1847 = !DILocation(line: 736, column: 30, scope: !1848)
!1848 = distinct !DILexicalBlock(scope: !685, file: !1, line: 733, column: 25)
!1849 = !DILocation(line: 736, column: 39, scope: !1848)
!1850 = !DILocation(line: 736, column: 50, scope: !1848)
!1851 = !DILocation(line: 736, column: 7, scope: !1848)
!1852 = !DILocation(line: 739, column: 27, scope: !1848)
!1853 = !DILocation(line: 739, column: 36, scope: !1848)
!1854 = !DILocation(line: 739, column: 47, scope: !1848)
!1855 = !DILocation(line: 739, column: 7, scope: !1848)
!1856 = !DILocation(line: 742, column: 7, scope: !1848)
!1857 = !DILocation(line: 744, column: 1, scope: !685)
!1858 = !DILocalVariable(name: "stream", arg: 1, scope: !688, file: !1, line: 746, type: !395)
!1859 = !DILocation(line: 746, column: 36, scope: !688)
!1860 = !DILocalVariable(name: "iov", scope: !688, file: !1, line: 747, type: !587)
!1861 = !DILocation(line: 747, column: 17, scope: !688)
!1862 = !DILocalVariable(name: "q", scope: !688, file: !1, line: 748, type: !375)
!1863 = !DILocation(line: 748, column: 10, scope: !688)
!1864 = !DILocalVariable(name: "req", scope: !688, file: !1, line: 749, type: !380)
!1865 = !DILocation(line: 749, column: 15, scope: !688)
!1866 = !DILocalVariable(name: "iovmax", scope: !688, file: !1, line: 750, type: !191)
!1867 = !DILocation(line: 750, column: 7, scope: !688)
!1868 = !DILocalVariable(name: "iovcnt", scope: !688, file: !1, line: 751, type: !191)
!1869 = !DILocation(line: 751, column: 7, scope: !688)
!1870 = !DILocalVariable(name: "n", scope: !688, file: !1, line: 752, type: !431)
!1871 = !DILocation(line: 752, column: 11, scope: !688)
!1872 = !DILocation(line: 752, column: 3, scope: !688)
!1873 = !DILocation(line: 756, column: 3, scope: !688)
!1874 = !DILocation(line: 756, column: 3, scope: !1875)
!1875 = !DILexicalBlockFile(scope: !688, file: !1, discriminator: 1)
!1876 = !DILocation(line: 756, column: 3, scope: !1877)
!1877 = !DILexicalBlockFile(scope: !688, file: !1, discriminator: 2)
!1878 = !DILocation(line: 756, column: 3, scope: !1879)
!1879 = !DILexicalBlockFile(scope: !688, file: !1, discriminator: 3)
!1880 = !DILocation(line: 758, column: 7, scope: !1881)
!1881 = distinct !DILexicalBlock(scope: !688, file: !1, line: 758, column: 7)
!1882 = !DILocation(line: 758, column: 7, scope: !688)
!1883 = !DILocation(line: 759, column: 5, scope: !1881)
!1884 = !DILocation(line: 761, column: 7, scope: !688)
!1885 = !DILocation(line: 761, column: 5, scope: !688)
!1886 = !DILocation(line: 762, column: 9, scope: !688)
!1887 = !DILocation(line: 762, column: 7, scope: !688)
!1888 = !DILocation(line: 763, column: 3, scope: !688)
!1889 = !DILocation(line: 763, column: 3, scope: !1875)
!1890 = !DILocation(line: 763, column: 3, scope: !1877)
!1891 = !DILocation(line: 763, column: 3, scope: !1879)
!1892 = !DILocation(line: 770, column: 37, scope: !688)
!1893 = !DILocation(line: 770, column: 42, scope: !688)
!1894 = !DILocation(line: 770, column: 27, scope: !688)
!1895 = !DILocation(line: 770, column: 32, scope: !688)
!1896 = !DILocation(line: 770, column: 9, scope: !688)
!1897 = !DILocation(line: 770, column: 7, scope: !688)
!1898 = !DILocation(line: 771, column: 12, scope: !688)
!1899 = !DILocation(line: 771, column: 17, scope: !688)
!1900 = !DILocation(line: 771, column: 25, scope: !688)
!1901 = !DILocation(line: 771, column: 30, scope: !688)
!1902 = !DILocation(line: 771, column: 23, scope: !688)
!1903 = !DILocation(line: 771, column: 10, scope: !688)
!1904 = !DILocation(line: 773, column: 12, scope: !688)
!1905 = !DILocation(line: 773, column: 10, scope: !688)
!1906 = !DILocation(line: 776, column: 7, scope: !1907)
!1907 = distinct !DILexicalBlock(scope: !688, file: !1, line: 776, column: 7)
!1908 = !DILocation(line: 776, column: 16, scope: !1907)
!1909 = !DILocation(line: 776, column: 14, scope: !1907)
!1910 = !DILocation(line: 776, column: 7, scope: !688)
!1911 = !DILocation(line: 777, column: 14, scope: !1907)
!1912 = !DILocation(line: 777, column: 12, scope: !1907)
!1913 = !DILocation(line: 777, column: 5, scope: !1907)
!1914 = !DILocation(line: 784, column: 7, scope: !1915)
!1915 = distinct !DILexicalBlock(scope: !688, file: !1, line: 784, column: 7)
!1916 = !DILocation(line: 784, column: 12, scope: !1915)
!1917 = !DILocation(line: 784, column: 7, scope: !688)
!1918 = !DILocalVariable(name: "msg", scope: !1919, file: !1, line: 785, type: !669)
!1919 = distinct !DILexicalBlock(scope: !1915, file: !1, line: 784, column: 25)
!1920 = !DILocation(line: 785, column: 19, scope: !1919)
!1921 = !DILocalVariable(name: "cmsg", scope: !1919, file: !1, line: 786, type: !593)
!1922 = !DILocation(line: 786, column: 21, scope: !1919)
!1923 = !DILocalVariable(name: "fd_to_send", scope: !1919, file: !1, line: 787, type: !191)
!1924 = !DILocation(line: 787, column: 9, scope: !1919)
!1925 = !DILocation(line: 787, column: 51, scope: !1919)
!1926 = !DILocation(line: 787, column: 56, scope: !1919)
!1927 = !DILocation(line: 787, column: 36, scope: !1919)
!1928 = !DILocation(line: 787, column: 22, scope: !1919)
!1929 = !DILocalVariable(name: "scratch", scope: !1919, file: !1, line: 791, type: !1930)
!1930 = !DICompositeType(tag: DW_TAG_union_type, scope: !688, file: !1, line: 788, size: 512, align: 64, elements: !1931)
!1931 = !{!1932, !1936}
!1932 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1930, file: !1, line: 789, baseType: !1933, size: 512, align: 8)
!1933 = !DICompositeType(tag: DW_TAG_array_type, baseType: !242, size: 512, align: 8, elements: !1934)
!1934 = !{!1935}
!1935 = !DISubrange(count: 64)
!1936 = !DIDerivedType(tag: DW_TAG_member, name: "alias", scope: !1930, file: !1, line: 790, baseType: !594, size: 128, align: 64)
!1937 = !DILocation(line: 791, column: 7, scope: !1919)
!1938 = !DILocation(line: 793, column: 5, scope: !1919)
!1939 = !DILocation(line: 795, column: 5, scope: !1919)
!1940 = !DILocation(line: 795, column: 5, scope: !1941)
!1941 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 1)
!1942 = !DILocation(line: 795, column: 5, scope: !1943)
!1943 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 2)
!1944 = !DILocation(line: 795, column: 5, scope: !1945)
!1945 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 3)
!1946 = !DILocation(line: 797, column: 9, scope: !1919)
!1947 = !DILocation(line: 797, column: 18, scope: !1919)
!1948 = !DILocation(line: 798, column: 9, scope: !1919)
!1949 = !DILocation(line: 798, column: 21, scope: !1919)
!1950 = !DILocation(line: 799, column: 19, scope: !1919)
!1951 = !DILocation(line: 799, column: 9, scope: !1919)
!1952 = !DILocation(line: 799, column: 17, scope: !1919)
!1953 = !DILocation(line: 800, column: 22, scope: !1919)
!1954 = !DILocation(line: 800, column: 9, scope: !1919)
!1955 = !DILocation(line: 800, column: 20, scope: !1919)
!1956 = !DILocation(line: 801, column: 9, scope: !1919)
!1957 = !DILocation(line: 801, column: 19, scope: !1919)
!1958 = !DILocation(line: 803, column: 32, scope: !1919)
!1959 = !DILocation(line: 803, column: 23, scope: !1919)
!1960 = !DILocation(line: 803, column: 9, scope: !1919)
!1961 = !DILocation(line: 803, column: 21, scope: !1919)
!1962 = !DILocation(line: 804, column: 9, scope: !1919)
!1963 = !DILocation(line: 804, column: 24, scope: !1919)
!1964 = !DILocation(line: 806, column: 12, scope: !1919)
!1965 = !DILocation(line: 806, column: 12, scope: !1941)
!1966 = !DILocation(line: 806, column: 12, scope: !1943)
!1967 = !DILocation(line: 806, column: 12, scope: !1945)
!1968 = !DILocation(line: 806, column: 10, scope: !1945)
!1969 = !DILocation(line: 807, column: 5, scope: !1919)
!1970 = !DILocation(line: 807, column: 11, scope: !1919)
!1971 = !DILocation(line: 807, column: 22, scope: !1919)
!1972 = !DILocation(line: 808, column: 5, scope: !1919)
!1973 = !DILocation(line: 808, column: 11, scope: !1919)
!1974 = !DILocation(line: 808, column: 21, scope: !1919)
!1975 = !DILocation(line: 809, column: 5, scope: !1919)
!1976 = !DILocation(line: 809, column: 11, scope: !1919)
!1977 = !DILocation(line: 809, column: 20, scope: !1919)
!1978 = !DILocalVariable(name: "pv", scope: !1979, file: !1, line: 813, type: !173)
!1979 = distinct !DILexicalBlock(scope: !1919, file: !1, line: 812, column: 5)
!1980 = !DILocation(line: 813, column: 13, scope: !1979)
!1981 = !DILocation(line: 813, column: 18, scope: !1979)
!1982 = !DILocalVariable(name: "pi", scope: !1979, file: !1, line: 814, type: !1983)
!1983 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!1984 = !DILocation(line: 814, column: 12, scope: !1979)
!1985 = !DILocation(line: 814, column: 17, scope: !1979)
!1986 = !DILocation(line: 815, column: 13, scope: !1979)
!1987 = !DILocation(line: 815, column: 8, scope: !1979)
!1988 = !DILocation(line: 815, column: 11, scope: !1979)
!1989 = !DILocation(line: 818, column: 5, scope: !1919)
!1990 = !DILocation(line: 819, column: 19, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !1919, file: !1, line: 818, column: 8)
!1992 = !DILocation(line: 819, column: 11, scope: !1991)
!1993 = !DILocation(line: 819, column: 9, scope: !1991)
!1994 = !DILocation(line: 820, column: 5, scope: !1991)
!1995 = !DILocation(line: 830, column: 12, scope: !1919)
!1996 = !DILocation(line: 830, column: 14, scope: !1919)
!1997 = !DILocation(line: 830, column: 20, scope: !1919)
!1998 = !DILocation(line: 830, column: 23, scope: !1941)
!1999 = !DILocation(line: 830, column: 29, scope: !1941)
!2000 = !DILocation(line: 820, column: 5, scope: !2001)
!2001 = !DILexicalBlockFile(scope: !1991, file: !1, discriminator: 1)
!2002 = !DILocation(line: 832, column: 3, scope: !1919)
!2003 = !DILocation(line: 833, column: 5, scope: !2004)
!2004 = distinct !DILexicalBlock(scope: !1915, file: !1, line: 832, column: 10)
!2005 = !DILocation(line: 834, column: 11, scope: !2006)
!2006 = distinct !DILexicalBlock(scope: !2007, file: !1, line: 834, column: 11)
!2007 = distinct !DILexicalBlock(scope: !2004, file: !1, line: 833, column: 8)
!2008 = !DILocation(line: 834, column: 18, scope: !2006)
!2009 = !DILocation(line: 834, column: 11, scope: !2007)
!2010 = !DILocation(line: 835, column: 19, scope: !2011)
!2011 = distinct !DILexicalBlock(scope: !2006, file: !1, line: 834, column: 24)
!2012 = !DILocation(line: 835, column: 42, scope: !2011)
!2013 = !DILocation(line: 835, column: 49, scope: !2011)
!2014 = !DILocation(line: 835, column: 59, scope: !2011)
!2015 = !DILocation(line: 835, column: 66, scope: !2011)
!2016 = !DILocation(line: 835, column: 13, scope: !2011)
!2017 = !DILocation(line: 835, column: 11, scope: !2011)
!2018 = !DILocation(line: 836, column: 7, scope: !2011)
!2019 = !DILocation(line: 837, column: 20, scope: !2020)
!2020 = distinct !DILexicalBlock(scope: !2006, file: !1, line: 836, column: 14)
!2021 = !DILocation(line: 837, column: 43, scope: !2020)
!2022 = !DILocation(line: 837, column: 48, scope: !2020)
!2023 = !DILocation(line: 837, column: 13, scope: !2020)
!2024 = !DILocation(line: 837, column: 11, scope: !2020)
!2025 = !DILocation(line: 839, column: 5, scope: !2007)
!2026 = !DILocation(line: 849, column: 12, scope: !2004)
!2027 = !DILocation(line: 849, column: 14, scope: !2004)
!2028 = !DILocation(line: 849, column: 20, scope: !2004)
!2029 = !DILocation(line: 849, column: 23, scope: !2030)
!2030 = !DILexicalBlockFile(scope: !2004, file: !1, discriminator: 1)
!2031 = !DILocation(line: 849, column: 29, scope: !2030)
!2032 = !DILocation(line: 839, column: 5, scope: !2033)
!2033 = !DILexicalBlockFile(scope: !2007, file: !1, discriminator: 1)
!2034 = !DILocation(line: 853, column: 7, scope: !2035)
!2035 = distinct !DILexicalBlock(scope: !688, file: !1, line: 853, column: 7)
!2036 = !DILocation(line: 853, column: 9, scope: !2035)
!2037 = !DILocation(line: 853, column: 7, scope: !688)
!2038 = !DILocation(line: 854, column: 9, scope: !2039)
!2039 = distinct !DILexicalBlock(scope: !2040, file: !1, line: 854, column: 9)
!2040 = distinct !DILexicalBlock(scope: !2035, file: !1, line: 853, column: 14)
!2041 = !DILocation(line: 854, column: 15, scope: !2039)
!2042 = !DILocation(line: 854, column: 25, scope: !2039)
!2043 = !DILocation(line: 854, column: 28, scope: !2044)
!2044 = !DILexicalBlockFile(scope: !2039, file: !1, discriminator: 1)
!2045 = !DILocation(line: 854, column: 34, scope: !2044)
!2046 = !DILocation(line: 854, column: 9, scope: !2044)
!2047 = !DILocation(line: 856, column: 21, scope: !2048)
!2048 = distinct !DILexicalBlock(scope: !2039, file: !1, line: 854, column: 50)
!2049 = !DILocation(line: 856, column: 20, scope: !2048)
!2050 = !DILocation(line: 856, column: 7, scope: !2048)
!2051 = !DILocation(line: 856, column: 12, scope: !2048)
!2052 = !DILocation(line: 856, column: 18, scope: !2048)
!2053 = !DILocation(line: 857, column: 28, scope: !2048)
!2054 = !DILocation(line: 857, column: 7, scope: !2048)
!2055 = !DILocation(line: 858, column: 19, scope: !2048)
!2056 = !DILocation(line: 858, column: 27, scope: !2048)
!2057 = !DILocation(line: 858, column: 34, scope: !2048)
!2058 = !DILocation(line: 858, column: 42, scope: !2048)
!2059 = !DILocation(line: 858, column: 7, scope: !2048)
!2060 = !DILocation(line: 859, column: 27, scope: !2061)
!2061 = distinct !DILexicalBlock(scope: !2048, file: !1, line: 859, column: 11)
!2062 = !DILocation(line: 859, column: 35, scope: !2061)
!2063 = !DILocation(line: 859, column: 12, scope: !2061)
!2064 = !DILocation(line: 859, column: 11, scope: !2048)
!2065 = !DILocation(line: 860, column: 9, scope: !2061)
!2066 = !DILocation(line: 860, column: 9, scope: !2067)
!2067 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 1)
!2068 = distinct !DILexicalBlock(scope: !2061, file: !1, line: 860, column: 9)
!2069 = !DILocation(line: 860, column: 9, scope: !2070)
!2070 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 2)
!2071 = !DILocation(line: 860, column: 9, scope: !2072)
!2072 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 3)
!2073 = !DILocation(line: 860, column: 9, scope: !2074)
!2074 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 4)
!2075 = !DILocation(line: 860, column: 9, scope: !2076)
!2076 = !DILexicalBlockFile(scope: !2077, file: !1, discriminator: 5)
!2077 = distinct !DILexicalBlock(scope: !2068, file: !1, line: 860, column: 9)
!2078 = !DILocation(line: 860, column: 9, scope: !2079)
!2079 = !DILexicalBlockFile(scope: !2077, file: !1, discriminator: 6)
!2080 = !DILocation(line: 860, column: 9, scope: !2081)
!2081 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 7)
!2082 = !DILocation(line: 860, column: 9, scope: !2083)
!2083 = !DILexicalBlockFile(scope: !2084, file: !1, discriminator: 8)
!2084 = distinct !DILexicalBlock(scope: !2068, file: !1, line: 860, column: 9)
!2085 = !DILocation(line: 860, column: 9, scope: !2086)
!2086 = !DILexicalBlockFile(scope: !2087, file: !1, discriminator: 9)
!2087 = distinct !DILexicalBlock(scope: !2084, file: !1, line: 860, column: 9)
!2088 = !DILocation(line: 860, column: 9, scope: !2089)
!2089 = !DILexicalBlockFile(scope: !2087, file: !1, discriminator: 10)
!2090 = !DILocation(line: 860, column: 9, scope: !2091)
!2091 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 11)
!2092 = !DILocation(line: 860, column: 9, scope: !2093)
!2093 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 12)
!2094 = !DILocation(line: 861, column: 39, scope: !2048)
!2095 = !DILocation(line: 861, column: 7, scope: !2048)
!2096 = !DILocation(line: 862, column: 7, scope: !2048)
!2097 = !DILocation(line: 863, column: 16, scope: !2098)
!2098 = distinct !DILexicalBlock(scope: !2039, file: !1, line: 863, column: 16)
!2099 = !DILocation(line: 863, column: 24, scope: !2098)
!2100 = !DILocation(line: 863, column: 30, scope: !2098)
!2101 = !DILocation(line: 863, column: 16, scope: !2039)
!2102 = !DILocation(line: 865, column: 7, scope: !2103)
!2103 = distinct !DILexicalBlock(scope: !2098, file: !1, line: 863, column: 52)
!2104 = !DILocation(line: 867, column: 3, scope: !2040)
!2105 = !DILocation(line: 870, column: 5, scope: !2106)
!2106 = distinct !DILexicalBlock(scope: !2035, file: !1, line: 867, column: 10)
!2107 = !DILocation(line: 870, column: 12, scope: !2108)
!2108 = !DILexicalBlockFile(scope: !2106, file: !1, discriminator: 1)
!2109 = !DILocation(line: 870, column: 14, scope: !2108)
!2110 = !DILocation(line: 870, column: 5, scope: !2108)
!2111 = !DILocalVariable(name: "buf", scope: !2112, file: !1, line: 871, type: !419)
!2112 = distinct !DILexicalBlock(scope: !2106, file: !1, line: 870, column: 20)
!2113 = !DILocation(line: 871, column: 17, scope: !2112)
!2114 = !DILocation(line: 871, column: 35, scope: !2112)
!2115 = !DILocation(line: 871, column: 40, scope: !2112)
!2116 = !DILocation(line: 871, column: 25, scope: !2112)
!2117 = !DILocation(line: 871, column: 30, scope: !2112)
!2118 = !DILocalVariable(name: "len", scope: !2112, file: !1, line: 872, type: !412)
!2119 = !DILocation(line: 872, column: 14, scope: !2112)
!2120 = !DILocation(line: 872, column: 20, scope: !2112)
!2121 = !DILocation(line: 872, column: 25, scope: !2112)
!2122 = !DILocation(line: 874, column: 7, scope: !2112)
!2123 = !DILocation(line: 874, column: 7, scope: !2124)
!2124 = !DILexicalBlockFile(scope: !2112, file: !1, discriminator: 1)
!2125 = !DILocation(line: 874, column: 7, scope: !2126)
!2126 = !DILexicalBlockFile(scope: !2112, file: !1, discriminator: 2)
!2127 = !DILocation(line: 874, column: 7, scope: !2128)
!2128 = !DILexicalBlockFile(scope: !2112, file: !1, discriminator: 3)
!2129 = !DILocation(line: 876, column: 19, scope: !2130)
!2130 = distinct !DILexicalBlock(scope: !2112, file: !1, line: 876, column: 11)
!2131 = !DILocation(line: 876, column: 23, scope: !2130)
!2132 = !DILocation(line: 876, column: 21, scope: !2130)
!2133 = !DILocation(line: 876, column: 11, scope: !2112)
!2134 = !DILocation(line: 877, column: 22, scope: !2135)
!2135 = distinct !DILexicalBlock(scope: !2130, file: !1, line: 876, column: 28)
!2136 = !DILocation(line: 877, column: 9, scope: !2135)
!2137 = !DILocation(line: 877, column: 14, scope: !2135)
!2138 = !DILocation(line: 877, column: 19, scope: !2135)
!2139 = !DILocation(line: 878, column: 21, scope: !2135)
!2140 = !DILocation(line: 878, column: 9, scope: !2135)
!2141 = !DILocation(line: 878, column: 14, scope: !2135)
!2142 = !DILocation(line: 878, column: 18, scope: !2135)
!2143 = !DILocation(line: 879, column: 37, scope: !2135)
!2144 = !DILocation(line: 879, column: 9, scope: !2135)
!2145 = !DILocation(line: 879, column: 17, scope: !2135)
!2146 = !DILocation(line: 879, column: 34, scope: !2135)
!2147 = !DILocation(line: 880, column: 11, scope: !2135)
!2148 = !DILocation(line: 883, column: 13, scope: !2149)
!2149 = distinct !DILexicalBlock(scope: !2135, file: !1, line: 883, column: 13)
!2150 = !DILocation(line: 883, column: 21, scope: !2149)
!2151 = !DILocation(line: 883, column: 27, scope: !2149)
!2152 = !DILocation(line: 883, column: 13, scope: !2135)
!2153 = !DILocation(line: 888, column: 11, scope: !2154)
!2154 = distinct !DILexicalBlock(scope: !2149, file: !1, line: 883, column: 49)
!2155 = !DILocation(line: 891, column: 11, scope: !2156)
!2156 = distinct !DILexicalBlock(scope: !2149, file: !1, line: 889, column: 16)
!2157 = !DILocation(line: 896, column: 9, scope: !2158)
!2158 = distinct !DILexicalBlock(scope: !2130, file: !1, line: 894, column: 14)
!2159 = !DILocation(line: 896, column: 14, scope: !2158)
!2160 = !DILocation(line: 896, column: 25, scope: !2158)
!2161 = !DILocation(line: 898, column: 9, scope: !2158)
!2162 = !DILocation(line: 898, column: 9, scope: !2163)
!2163 = !DILexicalBlockFile(scope: !2158, file: !1, discriminator: 1)
!2164 = !DILocation(line: 898, column: 9, scope: !2165)
!2165 = !DILexicalBlockFile(scope: !2158, file: !1, discriminator: 2)
!2166 = !DILocation(line: 898, column: 9, scope: !2167)
!2167 = !DILexicalBlockFile(scope: !2158, file: !1, discriminator: 3)
!2168 = !DILocation(line: 899, column: 14, scope: !2158)
!2169 = !DILocation(line: 899, column: 11, scope: !2158)
!2170 = !DILocation(line: 901, column: 9, scope: !2158)
!2171 = !DILocation(line: 901, column: 9, scope: !2163)
!2172 = !DILocation(line: 901, column: 9, scope: !2165)
!2173 = !DILocation(line: 901, column: 9, scope: !2167)
!2174 = !DILocation(line: 902, column: 37, scope: !2158)
!2175 = !DILocation(line: 902, column: 9, scope: !2158)
!2176 = !DILocation(line: 902, column: 17, scope: !2158)
!2177 = !DILocation(line: 902, column: 34, scope: !2158)
!2178 = !DILocation(line: 904, column: 13, scope: !2179)
!2179 = distinct !DILexicalBlock(scope: !2158, file: !1, line: 904, column: 13)
!2180 = !DILocation(line: 904, column: 18, scope: !2179)
!2181 = !DILocation(line: 904, column: 33, scope: !2179)
!2182 = !DILocation(line: 904, column: 38, scope: !2179)
!2183 = !DILocation(line: 904, column: 30, scope: !2179)
!2184 = !DILocation(line: 904, column: 13, scope: !2158)
!2185 = !DILocation(line: 906, column: 11, scope: !2186)
!2186 = distinct !DILexicalBlock(scope: !2179, file: !1, line: 904, column: 45)
!2187 = !DILocation(line: 906, column: 11, scope: !2188)
!2188 = !DILexicalBlockFile(scope: !2186, file: !1, discriminator: 1)
!2189 = !DILocation(line: 906, column: 11, scope: !2190)
!2190 = !DILexicalBlockFile(scope: !2186, file: !1, discriminator: 2)
!2191 = !DILocation(line: 906, column: 11, scope: !2192)
!2192 = !DILexicalBlockFile(scope: !2186, file: !1, discriminator: 3)
!2193 = !DILocation(line: 907, column: 32, scope: !2186)
!2194 = !DILocation(line: 907, column: 11, scope: !2186)
!2195 = !DILocation(line: 909, column: 11, scope: !2186)
!2196 = !DILocation(line: 870, column: 5, scope: !2197)
!2197 = !DILexicalBlockFile(scope: !2106, file: !1, discriminator: 2)
!2198 = !DILocation(line: 916, column: 3, scope: !688)
!2199 = !DILocation(line: 916, column: 3, scope: !1875)
!2200 = !DILocation(line: 916, column: 3, scope: !1877)
!2201 = !DILocation(line: 916, column: 3, scope: !1879)
!2202 = !DILocation(line: 916, column: 3, scope: !2203)
!2203 = !DILexicalBlockFile(scope: !688, file: !1, discriminator: 4)
!2204 = !DILocation(line: 919, column: 3, scope: !688)
!2205 = !DILocation(line: 919, column: 3, scope: !1875)
!2206 = !DILocation(line: 919, column: 3, scope: !1877)
!2207 = !DILocation(line: 919, column: 3, scope: !1879)
!2208 = !DILocation(line: 922, column: 16, scope: !688)
!2209 = !DILocation(line: 922, column: 24, scope: !688)
!2210 = !DILocation(line: 922, column: 31, scope: !688)
!2211 = !DILocation(line: 922, column: 39, scope: !688)
!2212 = !DILocation(line: 922, column: 3, scope: !688)
!2213 = !DILocation(line: 925, column: 35, scope: !688)
!2214 = !DILocation(line: 925, column: 3, scope: !688)
!2215 = !DILocation(line: 926, column: 1, scope: !688)
!2216 = !DILocation(line: 926, column: 1, scope: !1875)
!2217 = !DILocalVariable(name: "req", arg: 1, scope: !634, file: !1, line: 1469, type: !380)
!2218 = !DILocation(line: 1469, column: 26, scope: !634)
!2219 = !DILocalVariable(name: "handle", arg: 2, scope: !634, file: !1, line: 1470, type: !395)
!2220 = !DILocation(line: 1470, column: 27, scope: !634)
!2221 = !DILocalVariable(name: "bufs", arg: 3, scope: !634, file: !1, line: 1471, type: !435)
!2222 = !DILocation(line: 1471, column: 29, scope: !634)
!2223 = !DILocalVariable(name: "nbufs", arg: 4, scope: !634, file: !1, line: 1472, type: !181)
!2224 = !DILocation(line: 1472, column: 27, scope: !634)
!2225 = !DILocalVariable(name: "cb", arg: 5, scope: !634, file: !1, line: 1473, type: !390)
!2226 = !DILocation(line: 1473, column: 26, scope: !634)
!2227 = !DILocation(line: 1474, column: 20, scope: !634)
!2228 = !DILocation(line: 1474, column: 25, scope: !634)
!2229 = !DILocation(line: 1474, column: 33, scope: !634)
!2230 = !DILocation(line: 1474, column: 39, scope: !634)
!2231 = !DILocation(line: 1474, column: 52, scope: !634)
!2232 = !DILocation(line: 1474, column: 10, scope: !634)
!2233 = !DILocation(line: 1474, column: 3, scope: !634)
!2234 = !DILocalVariable(name: "req", arg: 1, scope: !637, file: !1, line: 1478, type: !380)
!2235 = !DILocation(line: 1478, column: 34, scope: !637)
!2236 = !DILocalVariable(name: "status", arg: 2, scope: !637, file: !1, line: 1478, type: !191)
!2237 = !DILocation(line: 1478, column: 43, scope: !637)
!2238 = !DILocation(line: 1480, column: 3, scope: !637)
!2239 = !DILocation(line: 1481, column: 1, scope: !637)
!2240 = !DILocalVariable(name: "stream", arg: 1, scope: !638, file: !1, line: 1484, type: !395)
!2241 = !DILocation(line: 1484, column: 31, scope: !638)
!2242 = !DILocalVariable(name: "bufs", arg: 2, scope: !638, file: !1, line: 1485, type: !435)
!2243 = !DILocation(line: 1485, column: 33, scope: !638)
!2244 = !DILocalVariable(name: "nbufs", arg: 3, scope: !638, file: !1, line: 1486, type: !181)
!2245 = !DILocation(line: 1486, column: 31, scope: !638)
!2246 = !DILocalVariable(name: "r", scope: !638, file: !1, line: 1487, type: !191)
!2247 = !DILocation(line: 1487, column: 7, scope: !638)
!2248 = !DILocalVariable(name: "has_pollout", scope: !638, file: !1, line: 1488, type: !191)
!2249 = !DILocation(line: 1488, column: 7, scope: !638)
!2250 = !DILocalVariable(name: "written", scope: !638, file: !1, line: 1489, type: !412)
!2251 = !DILocation(line: 1489, column: 10, scope: !638)
!2252 = !DILocalVariable(name: "req_size", scope: !638, file: !1, line: 1490, type: !412)
!2253 = !DILocation(line: 1490, column: 10, scope: !638)
!2254 = !DILocalVariable(name: "req", scope: !638, file: !1, line: 1491, type: !381)
!2255 = !DILocation(line: 1491, column: 14, scope: !638)
!2256 = !DILocation(line: 1494, column: 7, scope: !2257)
!2257 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1494, column: 7)
!2258 = !DILocation(line: 1494, column: 15, scope: !2257)
!2259 = !DILocation(line: 1494, column: 27, scope: !2257)
!2260 = !DILocation(line: 1494, column: 35, scope: !2257)
!2261 = !DILocation(line: 1494, column: 38, scope: !2262)
!2262 = !DILexicalBlockFile(scope: !2257, file: !1, discriminator: 1)
!2263 = !DILocation(line: 1494, column: 46, scope: !2262)
!2264 = !DILocation(line: 1494, column: 63, scope: !2262)
!2265 = !DILocation(line: 1494, column: 7, scope: !2262)
!2266 = !DILocation(line: 1495, column: 5, scope: !2257)
!2267 = !DILocation(line: 1497, column: 32, scope: !638)
!2268 = !DILocation(line: 1497, column: 40, scope: !638)
!2269 = !DILocation(line: 1497, column: 17, scope: !638)
!2270 = !DILocation(line: 1497, column: 15, scope: !638)
!2271 = !DILocation(line: 1499, column: 22, scope: !638)
!2272 = !DILocation(line: 1499, column: 30, scope: !638)
!2273 = !DILocation(line: 1499, column: 36, scope: !638)
!2274 = !DILocation(line: 1499, column: 7, scope: !638)
!2275 = !DILocation(line: 1499, column: 5, scope: !638)
!2276 = !DILocation(line: 1500, column: 7, scope: !2277)
!2277 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1500, column: 7)
!2278 = !DILocation(line: 1500, column: 9, scope: !2277)
!2279 = !DILocation(line: 1500, column: 7, scope: !638)
!2280 = !DILocation(line: 1501, column: 12, scope: !2277)
!2281 = !DILocation(line: 1501, column: 5, scope: !2277)
!2282 = !DILocation(line: 1504, column: 28, scope: !638)
!2283 = !DILocation(line: 1504, column: 34, scope: !638)
!2284 = !DILocation(line: 1504, column: 13, scope: !638)
!2285 = !DILocation(line: 1504, column: 11, scope: !638)
!2286 = !DILocation(line: 1505, column: 11, scope: !2287)
!2287 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1505, column: 7)
!2288 = !DILocation(line: 1505, column: 16, scope: !2287)
!2289 = !DILocation(line: 1505, column: 7, scope: !638)
!2290 = !DILocation(line: 1506, column: 16, scope: !2287)
!2291 = !DILocation(line: 1506, column: 14, scope: !2287)
!2292 = !DILocation(line: 1506, column: 5, scope: !2287)
!2293 = !DILocation(line: 1508, column: 14, scope: !2287)
!2294 = !DILocation(line: 1509, column: 14, scope: !638)
!2295 = !DILocation(line: 1509, column: 11, scope: !638)
!2296 = !DILocation(line: 1510, column: 31, scope: !638)
!2297 = !DILocation(line: 1510, column: 3, scope: !638)
!2298 = !DILocation(line: 1510, column: 11, scope: !638)
!2299 = !DILocation(line: 1510, column: 28, scope: !638)
!2300 = !DILocation(line: 1513, column: 3, scope: !638)
!2301 = !DILocation(line: 1513, column: 3, scope: !2302)
!2302 = !DILexicalBlockFile(scope: !2303, file: !1, discriminator: 1)
!2303 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1513, column: 3)
!2304 = !DILocation(line: 1514, column: 3, scope: !638)
!2305 = !DILocation(line: 1514, column: 3, scope: !2306)
!2306 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 1)
!2307 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1514, column: 3)
!2308 = !DILocation(line: 1514, column: 3, scope: !2309)
!2309 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 2)
!2310 = !DILocation(line: 1514, column: 3, scope: !2311)
!2311 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 3)
!2312 = !DILocation(line: 1514, column: 3, scope: !2313)
!2313 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 4)
!2314 = !DILocation(line: 1514, column: 3, scope: !2315)
!2315 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 5)
!2316 = !DILocation(line: 1514, column: 3, scope: !2317)
!2317 = !DILexicalBlockFile(scope: !2318, file: !1, discriminator: 6)
!2318 = distinct !DILexicalBlock(scope: !2307, file: !1, line: 1514, column: 3)
!2319 = !DILocation(line: 1514, column: 3, scope: !2320)
!2320 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 7)
!2321 = !DILocation(line: 1515, column: 11, scope: !2322)
!2322 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1515, column: 7)
!2323 = !DILocation(line: 1515, column: 23, scope: !2322)
!2324 = !DILocation(line: 1515, column: 19, scope: !2322)
!2325 = !DILocation(line: 1515, column: 16, scope: !2322)
!2326 = !DILocation(line: 1515, column: 7, scope: !638)
!2327 = !DILocation(line: 1516, column: 18, scope: !2322)
!2328 = !DILocation(line: 1516, column: 14, scope: !2322)
!2329 = !DILocation(line: 1516, column: 5, scope: !2322)
!2330 = !DILocation(line: 1517, column: 7, scope: !638)
!2331 = !DILocation(line: 1517, column: 12, scope: !638)
!2332 = !DILocation(line: 1520, column: 8, scope: !2333)
!2333 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1520, column: 7)
!2334 = !DILocation(line: 1520, column: 7, scope: !638)
!2335 = !DILocation(line: 1521, column: 17, scope: !2336)
!2336 = distinct !DILexicalBlock(scope: !2333, file: !1, line: 1520, column: 21)
!2337 = !DILocation(line: 1521, column: 25, scope: !2336)
!2338 = !DILocation(line: 1521, column: 32, scope: !2336)
!2339 = !DILocation(line: 1521, column: 40, scope: !2336)
!2340 = !DILocation(line: 1521, column: 5, scope: !2336)
!2341 = !DILocation(line: 1522, column: 37, scope: !2336)
!2342 = !DILocation(line: 1522, column: 5, scope: !2336)
!2343 = !DILocation(line: 1523, column: 3, scope: !2336)
!2344 = !DILocation(line: 1525, column: 7, scope: !2345)
!2345 = distinct !DILexicalBlock(scope: !638, file: !1, line: 1525, column: 7)
!2346 = !DILocation(line: 1525, column: 15, scope: !2345)
!2347 = !DILocation(line: 1525, column: 20, scope: !2345)
!2348 = !DILocation(line: 1525, column: 23, scope: !2349)
!2349 = !DILexicalBlockFile(scope: !2345, file: !1, discriminator: 1)
!2350 = !DILocation(line: 1525, column: 32, scope: !2349)
!2351 = !DILocation(line: 1525, column: 7, scope: !2349)
!2352 = !DILocation(line: 1526, column: 5, scope: !2345)
!2353 = !DILocation(line: 1528, column: 12, scope: !2345)
!2354 = !DILocation(line: 1528, column: 5, scope: !2345)
!2355 = !DILocation(line: 1529, column: 1, scope: !638)
!2356 = !DILocalVariable(name: "req", arg: 1, scope: !692, file: !1, line: 694, type: !380)
!2357 = !DILocation(line: 694, column: 46, scope: !692)
!2358 = !DILocalVariable(name: "size", scope: !692, file: !1, line: 695, type: !412)
!2359 = !DILocation(line: 695, column: 10, scope: !692)
!2360 = !DILocation(line: 697, column: 3, scope: !692)
!2361 = !DILocation(line: 697, column: 3, scope: !2362)
!2362 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 1)
!2363 = !DILocation(line: 697, column: 3, scope: !2364)
!2364 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 2)
!2365 = !DILocation(line: 697, column: 3, scope: !2366)
!2366 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 3)
!2367 = !DILocation(line: 698, column: 25, scope: !692)
!2368 = !DILocation(line: 698, column: 30, scope: !692)
!2369 = !DILocation(line: 698, column: 37, scope: !692)
!2370 = !DILocation(line: 698, column: 42, scope: !692)
!2371 = !DILocation(line: 698, column: 35, scope: !692)
!2372 = !DILocation(line: 699, column: 25, scope: !692)
!2373 = !DILocation(line: 699, column: 30, scope: !692)
!2374 = !DILocation(line: 699, column: 38, scope: !692)
!2375 = !DILocation(line: 699, column: 43, scope: !692)
!2376 = !DILocation(line: 699, column: 36, scope: !692)
!2377 = !DILocation(line: 698, column: 10, scope: !692)
!2378 = !DILocation(line: 698, column: 8, scope: !692)
!2379 = !DILocation(line: 700, column: 3, scope: !692)
!2380 = !DILocation(line: 700, column: 3, scope: !2362)
!2381 = !DILocation(line: 700, column: 3, scope: !2364)
!2382 = !DILocation(line: 700, column: 3, scope: !2366)
!2383 = !DILocation(line: 702, column: 10, scope: !692)
!2384 = !DILocation(line: 702, column: 3, scope: !692)
!2385 = !DILocalVariable(name: "stream", arg: 1, scope: !641, file: !1, line: 1532, type: !395)
!2386 = !DILocation(line: 1532, column: 32, scope: !641)
!2387 = !DILocalVariable(name: "alloc_cb", arg: 2, scope: !641, file: !1, line: 1533, type: !415)
!2388 = !DILocation(line: 1533, column: 31, scope: !641)
!2389 = !DILocalVariable(name: "read_cb", arg: 3, scope: !641, file: !1, line: 1534, type: !427)
!2390 = !DILocation(line: 1534, column: 30, scope: !641)
!2391 = !DILocation(line: 1535, column: 3, scope: !641)
!2392 = !DILocation(line: 1535, column: 3, scope: !2393)
!2393 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 1)
!2394 = !DILocation(line: 1535, column: 3, scope: !2395)
!2395 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 2)
!2396 = !DILocation(line: 1535, column: 3, scope: !2397)
!2397 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 3)
!2398 = !DILocation(line: 1535, column: 3, scope: !2399)
!2399 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 4)
!2400 = !DILocation(line: 1535, column: 3, scope: !2401)
!2401 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 5)
!2402 = !DILocation(line: 1538, column: 7, scope: !2403)
!2403 = distinct !DILexicalBlock(scope: !641, file: !1, line: 1538, column: 7)
!2404 = !DILocation(line: 1538, column: 15, scope: !2403)
!2405 = !DILocation(line: 1538, column: 21, scope: !2403)
!2406 = !DILocation(line: 1538, column: 7, scope: !641)
!2407 = !DILocation(line: 1539, column: 5, scope: !2403)
!2408 = !DILocation(line: 1544, column: 3, scope: !641)
!2409 = !DILocation(line: 1544, column: 11, scope: !641)
!2410 = !DILocation(line: 1544, column: 17, scope: !641)
!2411 = !DILocation(line: 1550, column: 3, scope: !641)
!2412 = !DILocation(line: 1550, column: 3, scope: !2393)
!2413 = !DILocation(line: 1550, column: 3, scope: !2395)
!2414 = !DILocation(line: 1550, column: 3, scope: !2397)
!2415 = !DILocation(line: 1551, column: 3, scope: !641)
!2416 = !DILocation(line: 1551, column: 3, scope: !2393)
!2417 = !DILocation(line: 1551, column: 3, scope: !2395)
!2418 = !DILocation(line: 1551, column: 3, scope: !2397)
!2419 = !DILocation(line: 1553, column: 21, scope: !641)
!2420 = !DILocation(line: 1553, column: 3, scope: !641)
!2421 = !DILocation(line: 1553, column: 11, scope: !641)
!2422 = !DILocation(line: 1553, column: 19, scope: !641)
!2423 = !DILocation(line: 1554, column: 22, scope: !641)
!2424 = !DILocation(line: 1554, column: 3, scope: !641)
!2425 = !DILocation(line: 1554, column: 11, scope: !641)
!2426 = !DILocation(line: 1554, column: 20, scope: !641)
!2427 = !DILocation(line: 1556, column: 16, scope: !641)
!2428 = !DILocation(line: 1556, column: 24, scope: !641)
!2429 = !DILocation(line: 1556, column: 31, scope: !641)
!2430 = !DILocation(line: 1556, column: 39, scope: !641)
!2431 = !DILocation(line: 1556, column: 3, scope: !641)
!2432 = !DILocation(line: 1557, column: 3, scope: !641)
!2433 = !DILocation(line: 1557, column: 3, scope: !2434)
!2434 = !DILexicalBlockFile(scope: !2435, file: !1, discriminator: 1)
!2435 = distinct !DILexicalBlock(scope: !641, file: !1, line: 1557, column: 3)
!2436 = !DILocation(line: 1557, column: 3, scope: !2437)
!2437 = !DILexicalBlockFile(scope: !2435, file: !1, discriminator: 2)
!2438 = !DILocation(line: 1557, column: 3, scope: !2439)
!2439 = !DILexicalBlockFile(scope: !2435, file: !1, discriminator: 3)
!2440 = !DILocation(line: 1557, column: 3, scope: !2441)
!2441 = !DILexicalBlockFile(scope: !2435, file: !1, discriminator: 4)
!2442 = !DILocation(line: 1557, column: 3, scope: !2443)
!2443 = !DILexicalBlockFile(scope: !2444, file: !1, discriminator: 5)
!2444 = distinct !DILexicalBlock(scope: !2435, file: !1, line: 1557, column: 3)
!2445 = !DILocation(line: 1557, column: 3, scope: !2446)
!2446 = !DILexicalBlockFile(scope: !2444, file: !1, discriminator: 6)
!2447 = !DILocation(line: 1557, column: 3, scope: !2448)
!2448 = !DILexicalBlockFile(scope: !2435, file: !1, discriminator: 7)
!2449 = !DILocation(line: 1557, column: 3, scope: !2450)
!2450 = !DILexicalBlockFile(scope: !2451, file: !1, discriminator: 8)
!2451 = distinct !DILexicalBlock(scope: !2435, file: !1, line: 1557, column: 3)
!2452 = !DILocation(line: 1557, column: 3, scope: !2453)
!2453 = !DILexicalBlockFile(scope: !2454, file: !1, discriminator: 9)
!2454 = distinct !DILexicalBlock(scope: !2451, file: !1, line: 1557, column: 3)
!2455 = !DILocation(line: 1557, column: 3, scope: !2456)
!2456 = !DILexicalBlockFile(scope: !2454, file: !1, discriminator: 10)
!2457 = !DILocation(line: 1557, column: 3, scope: !2458)
!2458 = !DILexicalBlockFile(scope: !2435, file: !1, discriminator: 11)
!2459 = !DILocation(line: 1558, column: 35, scope: !641)
!2460 = !DILocation(line: 1558, column: 3, scope: !641)
!2461 = !DILocation(line: 1560, column: 3, scope: !641)
!2462 = !DILocation(line: 1561, column: 1, scope: !641)
!2463 = !DILocalVariable(name: "stream", arg: 1, scope: !644, file: !1, line: 1564, type: !395)
!2464 = !DILocation(line: 1564, column: 31, scope: !644)
!2465 = !DILocation(line: 1565, column: 9, scope: !2466)
!2466 = distinct !DILexicalBlock(scope: !644, file: !1, line: 1565, column: 7)
!2467 = !DILocation(line: 1565, column: 17, scope: !2466)
!2468 = !DILocation(line: 1565, column: 23, scope: !2466)
!2469 = !DILocation(line: 1565, column: 7, scope: !644)
!2470 = !DILocation(line: 1566, column: 5, scope: !2466)
!2471 = !DILocation(line: 1568, column: 3, scope: !644)
!2472 = !DILocation(line: 1568, column: 11, scope: !644)
!2473 = !DILocation(line: 1568, column: 17, scope: !644)
!2474 = !DILocation(line: 1569, column: 15, scope: !644)
!2475 = !DILocation(line: 1569, column: 23, scope: !644)
!2476 = !DILocation(line: 1569, column: 30, scope: !644)
!2477 = !DILocation(line: 1569, column: 38, scope: !644)
!2478 = !DILocation(line: 1569, column: 3, scope: !644)
!2479 = !DILocation(line: 1570, column: 23, scope: !2480)
!2480 = distinct !DILexicalBlock(scope: !644, file: !1, line: 1570, column: 7)
!2481 = !DILocation(line: 1570, column: 31, scope: !2480)
!2482 = !DILocation(line: 1570, column: 8, scope: !2480)
!2483 = !DILocation(line: 1570, column: 7, scope: !644)
!2484 = !DILocation(line: 1571, column: 5, scope: !2480)
!2485 = !DILocation(line: 1571, column: 5, scope: !2486)
!2486 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 1)
!2487 = distinct !DILexicalBlock(scope: !2480, file: !1, line: 1571, column: 5)
!2488 = !DILocation(line: 1571, column: 5, scope: !2489)
!2489 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 2)
!2490 = !DILocation(line: 1571, column: 5, scope: !2491)
!2491 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 3)
!2492 = !DILocation(line: 1571, column: 5, scope: !2493)
!2493 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 4)
!2494 = !DILocation(line: 1571, column: 5, scope: !2495)
!2495 = !DILexicalBlockFile(scope: !2496, file: !1, discriminator: 5)
!2496 = distinct !DILexicalBlock(scope: !2487, file: !1, line: 1571, column: 5)
!2497 = !DILocation(line: 1571, column: 5, scope: !2498)
!2498 = !DILexicalBlockFile(scope: !2496, file: !1, discriminator: 6)
!2499 = !DILocation(line: 1571, column: 5, scope: !2500)
!2500 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 7)
!2501 = !DILocation(line: 1571, column: 5, scope: !2502)
!2502 = !DILexicalBlockFile(scope: !2503, file: !1, discriminator: 8)
!2503 = distinct !DILexicalBlock(scope: !2487, file: !1, line: 1571, column: 5)
!2504 = !DILocation(line: 1571, column: 5, scope: !2505)
!2505 = !DILexicalBlockFile(scope: !2506, file: !1, discriminator: 9)
!2506 = distinct !DILexicalBlock(scope: !2503, file: !1, line: 1571, column: 5)
!2507 = !DILocation(line: 1571, column: 5, scope: !2508)
!2508 = !DILexicalBlockFile(scope: !2506, file: !1, discriminator: 10)
!2509 = !DILocation(line: 1571, column: 5, scope: !2510)
!2510 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 11)
!2511 = !DILocation(line: 1571, column: 5, scope: !2512)
!2512 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 12)
!2513 = !DILocation(line: 1572, column: 35, scope: !644)
!2514 = !DILocation(line: 1572, column: 3, scope: !644)
!2515 = !DILocation(line: 1574, column: 3, scope: !644)
!2516 = !DILocation(line: 1574, column: 11, scope: !644)
!2517 = !DILocation(line: 1574, column: 19, scope: !644)
!2518 = !DILocation(line: 1575, column: 3, scope: !644)
!2519 = !DILocation(line: 1575, column: 11, scope: !644)
!2520 = !DILocation(line: 1575, column: 20, scope: !644)
!2521 = !DILocation(line: 1576, column: 3, scope: !644)
!2522 = !DILocation(line: 1577, column: 1, scope: !644)
!2523 = !DILocalVariable(name: "stream", arg: 1, scope: !647, file: !1, line: 1580, type: !650)
!2524 = !DILocation(line: 1580, column: 39, scope: !647)
!2525 = !DILocation(line: 1581, column: 13, scope: !647)
!2526 = !DILocation(line: 1581, column: 21, scope: !647)
!2527 = !DILocation(line: 1581, column: 27, scope: !647)
!2528 = !DILocation(line: 1581, column: 11, scope: !647)
!2529 = !DILocation(line: 1581, column: 10, scope: !647)
!2530 = !DILocation(line: 1581, column: 3, scope: !647)
!2531 = !DILocalVariable(name: "stream", arg: 1, scope: !652, file: !1, line: 1585, type: !650)
!2532 = !DILocation(line: 1585, column: 39, scope: !652)
!2533 = !DILocation(line: 1586, column: 13, scope: !652)
!2534 = !DILocation(line: 1586, column: 21, scope: !652)
!2535 = !DILocation(line: 1586, column: 27, scope: !652)
!2536 = !DILocation(line: 1586, column: 11, scope: !652)
!2537 = !DILocation(line: 1586, column: 10, scope: !652)
!2538 = !DILocation(line: 1586, column: 3, scope: !652)
!2539 = !DILocalVariable(name: "handle", arg: 1, scope: !653, file: !1, line: 1607, type: !395)
!2540 = !DILocation(line: 1607, column: 36, scope: !653)
!2541 = !DILocalVariable(name: "i", scope: !653, file: !1, line: 1608, type: !181)
!2542 = !DILocation(line: 1608, column: 16, scope: !653)
!2543 = !DILocalVariable(name: "queued_fds", scope: !653, file: !1, line: 1609, type: !1392)
!2544 = !DILocation(line: 1609, column: 28, scope: !653)
!2545 = !DILocation(line: 1632, column: 16, scope: !653)
!2546 = !DILocation(line: 1632, column: 24, scope: !653)
!2547 = !DILocation(line: 1632, column: 31, scope: !653)
!2548 = !DILocation(line: 1632, column: 39, scope: !653)
!2549 = !DILocation(line: 1632, column: 3, scope: !653)
!2550 = !DILocation(line: 1633, column: 16, scope: !653)
!2551 = !DILocation(line: 1633, column: 3, scope: !653)
!2552 = !DILocation(line: 1634, column: 3, scope: !653)
!2553 = !DILocation(line: 1634, column: 3, scope: !2554)
!2554 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 1)
!2555 = distinct !DILexicalBlock(scope: !653, file: !1, line: 1634, column: 3)
!2556 = !DILocation(line: 1634, column: 3, scope: !2557)
!2557 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 2)
!2558 = !DILocation(line: 1634, column: 3, scope: !2559)
!2559 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 3)
!2560 = !DILocation(line: 1634, column: 3, scope: !2561)
!2561 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 4)
!2562 = !DILocation(line: 1634, column: 3, scope: !2563)
!2563 = !DILexicalBlockFile(scope: !2564, file: !1, discriminator: 5)
!2564 = distinct !DILexicalBlock(scope: !2555, file: !1, line: 1634, column: 3)
!2565 = !DILocation(line: 1634, column: 3, scope: !2566)
!2566 = !DILexicalBlockFile(scope: !2564, file: !1, discriminator: 6)
!2567 = !DILocation(line: 1634, column: 3, scope: !2568)
!2568 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 7)
!2569 = !DILocation(line: 1634, column: 3, scope: !2570)
!2570 = !DILexicalBlockFile(scope: !2571, file: !1, discriminator: 8)
!2571 = distinct !DILexicalBlock(scope: !2555, file: !1, line: 1634, column: 3)
!2572 = !DILocation(line: 1634, column: 3, scope: !2573)
!2573 = !DILexicalBlockFile(scope: !2574, file: !1, discriminator: 9)
!2574 = distinct !DILexicalBlock(scope: !2571, file: !1, line: 1634, column: 3)
!2575 = !DILocation(line: 1634, column: 3, scope: !2576)
!2576 = !DILexicalBlockFile(scope: !2574, file: !1, discriminator: 10)
!2577 = !DILocation(line: 1634, column: 3, scope: !2578)
!2578 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 11)
!2579 = !DILocation(line: 1636, column: 7, scope: !2580)
!2580 = distinct !DILexicalBlock(scope: !653, file: !1, line: 1636, column: 7)
!2581 = !DILocation(line: 1636, column: 15, scope: !2580)
!2582 = !DILocation(line: 1636, column: 26, scope: !2580)
!2583 = !DILocation(line: 1636, column: 29, scope: !2580)
!2584 = !DILocation(line: 1636, column: 7, scope: !653)
!2585 = !DILocation(line: 1638, column: 9, scope: !2586)
!2586 = distinct !DILexicalBlock(scope: !2587, file: !1, line: 1638, column: 9)
!2587 = distinct !DILexicalBlock(scope: !2580, file: !1, line: 1636, column: 36)
!2588 = !DILocation(line: 1638, column: 17, scope: !2586)
!2589 = !DILocation(line: 1638, column: 28, scope: !2586)
!2590 = !DILocation(line: 1638, column: 31, scope: !2586)
!2591 = !DILocation(line: 1638, column: 9, scope: !2587)
!2592 = !DILocation(line: 1639, column: 17, scope: !2586)
!2593 = !DILocation(line: 1639, column: 25, scope: !2586)
!2594 = !DILocation(line: 1639, column: 36, scope: !2586)
!2595 = !DILocation(line: 1639, column: 7, scope: !2586)
!2596 = !DILocation(line: 1640, column: 5, scope: !2587)
!2597 = !DILocation(line: 1640, column: 13, scope: !2587)
!2598 = !DILocation(line: 1640, column: 24, scope: !2587)
!2599 = !DILocation(line: 1640, column: 27, scope: !2587)
!2600 = !DILocation(line: 1641, column: 3, scope: !2587)
!2601 = !DILocation(line: 1643, column: 7, scope: !2602)
!2602 = distinct !DILexicalBlock(scope: !653, file: !1, line: 1643, column: 7)
!2603 = !DILocation(line: 1643, column: 15, scope: !2602)
!2604 = !DILocation(line: 1643, column: 27, scope: !2602)
!2605 = !DILocation(line: 1643, column: 7, scope: !653)
!2606 = !DILocation(line: 1644, column: 15, scope: !2607)
!2607 = distinct !DILexicalBlock(scope: !2602, file: !1, line: 1643, column: 34)
!2608 = !DILocation(line: 1644, column: 23, scope: !2607)
!2609 = !DILocation(line: 1644, column: 5, scope: !2607)
!2610 = !DILocation(line: 1645, column: 5, scope: !2607)
!2611 = !DILocation(line: 1645, column: 13, scope: !2607)
!2612 = !DILocation(line: 1645, column: 25, scope: !2607)
!2613 = !DILocation(line: 1646, column: 3, scope: !2607)
!2614 = !DILocation(line: 1649, column: 7, scope: !2615)
!2615 = distinct !DILexicalBlock(scope: !653, file: !1, line: 1649, column: 7)
!2616 = !DILocation(line: 1649, column: 15, scope: !2615)
!2617 = !DILocation(line: 1649, column: 26, scope: !2615)
!2618 = !DILocation(line: 1649, column: 7, scope: !653)
!2619 = !DILocation(line: 1650, column: 18, scope: !2620)
!2620 = distinct !DILexicalBlock(scope: !2615, file: !1, line: 1649, column: 35)
!2621 = !DILocation(line: 1650, column: 26, scope: !2620)
!2622 = !DILocation(line: 1650, column: 16, scope: !2620)
!2623 = !DILocation(line: 1651, column: 12, scope: !2624)
!2624 = distinct !DILexicalBlock(scope: !2620, file: !1, line: 1651, column: 5)
!2625 = !DILocation(line: 1651, column: 10, scope: !2624)
!2626 = !DILocation(line: 1651, column: 17, scope: !2627)
!2627 = !DILexicalBlockFile(scope: !2628, file: !1, discriminator: 1)
!2628 = distinct !DILexicalBlock(scope: !2624, file: !1, line: 1651, column: 5)
!2629 = !DILocation(line: 1651, column: 21, scope: !2627)
!2630 = !DILocation(line: 1651, column: 33, scope: !2627)
!2631 = !DILocation(line: 1651, column: 19, scope: !2627)
!2632 = !DILocation(line: 1651, column: 5, scope: !2627)
!2633 = !DILocation(line: 1652, column: 33, scope: !2628)
!2634 = !DILocation(line: 1652, column: 17, scope: !2628)
!2635 = !DILocation(line: 1652, column: 29, scope: !2628)
!2636 = !DILocation(line: 1652, column: 7, scope: !2628)
!2637 = !DILocation(line: 1651, column: 42, scope: !2638)
!2638 = !DILexicalBlockFile(scope: !2628, file: !1, discriminator: 2)
!2639 = !DILocation(line: 1651, column: 5, scope: !2638)
!2640 = !DILocation(line: 1653, column: 14, scope: !2620)
!2641 = !DILocation(line: 1653, column: 22, scope: !2620)
!2642 = !DILocation(line: 1653, column: 5, scope: !2620)
!2643 = !DILocation(line: 1654, column: 5, scope: !2620)
!2644 = !DILocation(line: 1654, column: 13, scope: !2620)
!2645 = !DILocation(line: 1654, column: 24, scope: !2620)
!2646 = !DILocation(line: 1655, column: 3, scope: !2620)
!2647 = !DILocation(line: 1657, column: 3, scope: !653)
!2648 = !DILocation(line: 1657, column: 3, scope: !2649)
!2649 = !DILexicalBlockFile(scope: !653, file: !1, discriminator: 1)
!2650 = !DILocation(line: 1657, column: 3, scope: !2651)
!2651 = !DILexicalBlockFile(scope: !653, file: !1, discriminator: 2)
!2652 = !DILocation(line: 1657, column: 3, scope: !2653)
!2653 = !DILexicalBlockFile(scope: !653, file: !1, discriminator: 3)
!2654 = !DILocation(line: 1658, column: 1, scope: !653)
!2655 = !DILocalVariable(name: "handle", arg: 1, scope: !654, file: !1, line: 1661, type: !395)
!2656 = !DILocation(line: 1661, column: 41, scope: !654)
!2657 = !DILocalVariable(name: "blocking", arg: 2, scope: !654, file: !1, line: 1661, type: !191)
!2658 = !DILocation(line: 1661, column: 53, scope: !654)
!2659 = !DILocation(line: 1665, column: 23, scope: !654)
!2660 = !DILocation(line: 1665, column: 47, scope: !654)
!2661 = !DILocation(line: 1665, column: 46, scope: !654)
!2662 = !DILocation(line: 1665, column: 10, scope: !654)
!2663 = !DILocation(line: 1665, column: 3, scope: !654)
!2664 = !DILocalVariable(name: "stream", arg: 1, scope: !663, file: !1, line: 1330, type: !395)
!2665 = !DILocation(line: 1330, column: 45, scope: !663)
!2666 = !DILocalVariable(name: "error", scope: !663, file: !1, line: 1331, type: !191)
!2667 = !DILocation(line: 1331, column: 7, scope: !663)
!2668 = !DILocalVariable(name: "req", scope: !663, file: !1, line: 1332, type: !438)
!2669 = !DILocation(line: 1332, column: 17, scope: !663)
!2670 = !DILocation(line: 1332, column: 23, scope: !663)
!2671 = !DILocation(line: 1332, column: 31, scope: !663)
!2672 = !DILocalVariable(name: "errorsize", scope: !663, file: !1, line: 1333, type: !673)
!2673 = !DILocation(line: 1333, column: 13, scope: !663)
!2674 = !DILocation(line: 1335, column: 3, scope: !663)
!2675 = !DILocation(line: 1335, column: 3, scope: !2676)
!2676 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 1)
!2677 = !DILocation(line: 1335, column: 3, scope: !2678)
!2678 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 2)
!2679 = !DILocation(line: 1335, column: 3, scope: !2680)
!2680 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 3)
!2681 = !DILocation(line: 1335, column: 3, scope: !2682)
!2682 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 4)
!2683 = !DILocation(line: 1336, column: 3, scope: !663)
!2684 = !DILocation(line: 1336, column: 3, scope: !2676)
!2685 = !DILocation(line: 1336, column: 3, scope: !2678)
!2686 = !DILocation(line: 1336, column: 3, scope: !2680)
!2687 = !DILocation(line: 1338, column: 7, scope: !2688)
!2688 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1338, column: 7)
!2689 = !DILocation(line: 1338, column: 15, scope: !2688)
!2690 = !DILocation(line: 1338, column: 7, scope: !663)
!2691 = !DILocation(line: 1343, column: 13, scope: !2692)
!2692 = distinct !DILexicalBlock(scope: !2688, file: !1, line: 1338, column: 30)
!2693 = !DILocation(line: 1343, column: 21, scope: !2692)
!2694 = !DILocation(line: 1343, column: 11, scope: !2692)
!2695 = !DILocation(line: 1344, column: 5, scope: !2692)
!2696 = !DILocation(line: 1344, column: 13, scope: !2692)
!2697 = !DILocation(line: 1344, column: 27, scope: !2692)
!2698 = !DILocation(line: 1345, column: 3, scope: !2692)
!2699 = !DILocation(line: 1347, column: 5, scope: !2700)
!2700 = distinct !DILexicalBlock(scope: !2688, file: !1, line: 1345, column: 10)
!2701 = !DILocation(line: 1347, column: 5, scope: !2702)
!2702 = !DILexicalBlockFile(scope: !2700, file: !1, discriminator: 1)
!2703 = !DILocation(line: 1347, column: 5, scope: !2704)
!2704 = !DILexicalBlockFile(scope: !2700, file: !1, discriminator: 2)
!2705 = !DILocation(line: 1347, column: 5, scope: !2706)
!2706 = !DILexicalBlockFile(scope: !2700, file: !1, discriminator: 3)
!2707 = !DILocation(line: 1348, column: 16, scope: !2700)
!2708 = !DILocation(line: 1351, column: 16, scope: !2700)
!2709 = !DILocation(line: 1348, column: 5, scope: !2700)
!2710 = !DILocation(line: 1353, column: 14, scope: !2700)
!2711 = !DILocation(line: 1353, column: 13, scope: !2700)
!2712 = !DILocation(line: 1353, column: 11, scope: !2700)
!2713 = !DILocation(line: 1356, column: 7, scope: !2714)
!2714 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1356, column: 7)
!2715 = !DILocation(line: 1356, column: 13, scope: !2714)
!2716 = !DILocation(line: 1356, column: 7, scope: !663)
!2717 = !DILocation(line: 1357, column: 5, scope: !2714)
!2718 = !DILocation(line: 1359, column: 3, scope: !663)
!2719 = !DILocation(line: 1359, column: 11, scope: !663)
!2720 = !DILocation(line: 1359, column: 23, scope: !663)
!2721 = !DILocation(line: 1360, column: 3, scope: !663)
!2722 = !DILocation(line: 1360, column: 3, scope: !2723)
!2723 = !DILexicalBlockFile(scope: !2724, file: !1, discriminator: 1)
!2724 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1360, column: 3)
!2725 = !DILocation(line: 1360, column: 3, scope: !2726)
!2726 = !DILexicalBlockFile(scope: !2724, file: !1, discriminator: 2)
!2727 = !DILocation(line: 1360, column: 3, scope: !2728)
!2728 = !DILexicalBlockFile(scope: !2724, file: !1, discriminator: 3)
!2729 = !DILocation(line: 1360, column: 3, scope: !2730)
!2730 = !DILexicalBlockFile(scope: !2724, file: !1, discriminator: 4)
!2731 = !DILocation(line: 1360, column: 3, scope: !2732)
!2732 = !DILexicalBlockFile(scope: !2724, file: !1, discriminator: 5)
!2733 = !DILocation(line: 1360, column: 3, scope: !2734)
!2734 = !DILexicalBlockFile(scope: !2735, file: !1, discriminator: 6)
!2735 = distinct !DILexicalBlock(scope: !2724, file: !1, line: 1360, column: 3)
!2736 = !DILocation(line: 1360, column: 3, scope: !2737)
!2737 = !DILexicalBlockFile(scope: !2724, file: !1, discriminator: 7)
!2738 = !DILocation(line: 1362, column: 7, scope: !2739)
!2739 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1362, column: 7)
!2740 = !DILocation(line: 1362, column: 13, scope: !2739)
!2741 = !DILocation(line: 1362, column: 17, scope: !2739)
!2742 = !DILocation(line: 1362, column: 20, scope: !2743)
!2743 = !DILexicalBlockFile(scope: !2739, file: !1, discriminator: 1)
!2744 = !DILocation(line: 1362, column: 7, scope: !2743)
!2745 = !DILocation(line: 1363, column: 17, scope: !2746)
!2746 = distinct !DILexicalBlock(scope: !2739, file: !1, line: 1362, column: 55)
!2747 = !DILocation(line: 1363, column: 25, scope: !2746)
!2748 = !DILocation(line: 1363, column: 32, scope: !2746)
!2749 = !DILocation(line: 1363, column: 40, scope: !2746)
!2750 = !DILocation(line: 1363, column: 5, scope: !2746)
!2751 = !DILocation(line: 1364, column: 3, scope: !2746)
!2752 = !DILocation(line: 1366, column: 7, scope: !2753)
!2753 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1366, column: 7)
!2754 = !DILocation(line: 1366, column: 12, scope: !2753)
!2755 = !DILocation(line: 1366, column: 7, scope: !663)
!2756 = !DILocation(line: 1367, column: 5, scope: !2753)
!2757 = !DILocation(line: 1367, column: 10, scope: !2753)
!2758 = !DILocation(line: 1367, column: 13, scope: !2753)
!2759 = !DILocation(line: 1367, column: 18, scope: !2753)
!2760 = !DILocation(line: 1369, column: 7, scope: !2761)
!2761 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1369, column: 7)
!2762 = !DILocation(line: 1369, column: 29, scope: !2761)
!2763 = !DILocation(line: 1369, column: 7, scope: !663)
!2764 = !DILocation(line: 1370, column: 5, scope: !2761)
!2765 = !DILocation(line: 1372, column: 7, scope: !2766)
!2766 = distinct !DILexicalBlock(scope: !663, file: !1, line: 1372, column: 7)
!2767 = !DILocation(line: 1372, column: 13, scope: !2766)
!2768 = !DILocation(line: 1372, column: 7, scope: !663)
!2769 = !DILocation(line: 1373, column: 34, scope: !2770)
!2770 = distinct !DILexicalBlock(scope: !2766, file: !1, line: 1372, column: 18)
!2771 = !DILocation(line: 1373, column: 5, scope: !2770)
!2772 = !DILocation(line: 1374, column: 25, scope: !2770)
!2773 = !DILocation(line: 1374, column: 5, scope: !2770)
!2774 = !DILocation(line: 1375, column: 3, scope: !2770)
!2775 = !DILocation(line: 1376, column: 1, scope: !663)
!2776 = !DILocalVariable(name: "stream", arg: 1, scope: !664, file: !1, line: 1108, type: !395)
!2777 = !DILocation(line: 1108, column: 35, scope: !664)
!2778 = !DILocalVariable(name: "buf", scope: !664, file: !1, line: 1109, type: !420)
!2779 = !DILocation(line: 1109, column: 12, scope: !664)
!2780 = !DILocalVariable(name: "nread", scope: !664, file: !1, line: 1110, type: !431)
!2781 = !DILocation(line: 1110, column: 11, scope: !664)
!2782 = !DILocalVariable(name: "msg", scope: !664, file: !1, line: 1111, type: !669)
!2783 = !DILocation(line: 1111, column: 17, scope: !664)
!2784 = !DILocalVariable(name: "cmsg_space", scope: !664, file: !1, line: 1112, type: !2785)
!2785 = !DICompositeType(tag: DW_TAG_array_type, baseType: !242, size: 2176, align: 8, elements: !2786)
!2786 = !{!2787}
!2787 = !DISubrange(count: 272)
!2788 = !DILocation(line: 1112, column: 8, scope: !664)
!2789 = !DILocalVariable(name: "count", scope: !664, file: !1, line: 1113, type: !191)
!2790 = !DILocation(line: 1113, column: 7, scope: !664)
!2791 = !DILocalVariable(name: "err", scope: !664, file: !1, line: 1114, type: !191)
!2792 = !DILocation(line: 1114, column: 7, scope: !664)
!2793 = !DILocalVariable(name: "is_ipc", scope: !664, file: !1, line: 1115, type: !191)
!2794 = !DILocation(line: 1115, column: 7, scope: !664)
!2795 = !DILocation(line: 1117, column: 3, scope: !664)
!2796 = !DILocation(line: 1117, column: 11, scope: !664)
!2797 = !DILocation(line: 1117, column: 17, scope: !664)
!2798 = !DILocation(line: 1122, column: 9, scope: !664)
!2799 = !DILocation(line: 1124, column: 12, scope: !664)
!2800 = !DILocation(line: 1124, column: 20, scope: !664)
!2801 = !DILocation(line: 1124, column: 25, scope: !664)
!2802 = !DILocation(line: 1124, column: 42, scope: !664)
!2803 = !DILocation(line: 1124, column: 59, scope: !2804)
!2804 = !DILexicalBlockFile(scope: !664, file: !1, discriminator: 1)
!2805 = !DILocation(line: 1124, column: 68, scope: !2804)
!2806 = !DILocation(line: 1124, column: 42, scope: !2804)
!2807 = !DILocation(line: 1124, column: 42, scope: !2808)
!2808 = !DILexicalBlockFile(scope: !664, file: !1, discriminator: 2)
!2809 = !DILocation(line: 1124, column: 10, scope: !2808)
!2810 = !DILocation(line: 1129, column: 3, scope: !664)
!2811 = !DILocation(line: 1129, column: 10, scope: !2804)
!2812 = !DILocation(line: 1129, column: 18, scope: !2804)
!2813 = !DILocation(line: 1130, column: 7, scope: !664)
!2814 = !DILocation(line: 1130, column: 11, scope: !2804)
!2815 = !DILocation(line: 1130, column: 19, scope: !2804)
!2816 = !DILocation(line: 1130, column: 25, scope: !2804)
!2817 = !DILocation(line: 1131, column: 7, scope: !664)
!2818 = !DILocation(line: 1131, column: 16, scope: !2804)
!2819 = !DILocation(line: 1131, column: 19, scope: !2804)
!2820 = !DILocation(line: 1129, column: 3, scope: !2808)
!2821 = !DILocation(line: 1132, column: 5, scope: !2822)
!2822 = distinct !DILexicalBlock(scope: !664, file: !1, line: 1131, column: 25)
!2823 = !DILocation(line: 1132, column: 5, scope: !2824)
!2824 = !DILexicalBlockFile(scope: !2822, file: !1, discriminator: 1)
!2825 = !DILocation(line: 1132, column: 5, scope: !2826)
!2826 = !DILexicalBlockFile(scope: !2822, file: !1, discriminator: 2)
!2827 = !DILocation(line: 1132, column: 5, scope: !2828)
!2828 = !DILexicalBlockFile(scope: !2822, file: !1, discriminator: 3)
!2829 = !DILocation(line: 1134, column: 11, scope: !2822)
!2830 = !DILocation(line: 1134, column: 11, scope: !2824)
!2831 = !DILocation(line: 1135, column: 5, scope: !2822)
!2832 = !DILocation(line: 1135, column: 13, scope: !2822)
!2833 = !DILocation(line: 1135, column: 36, scope: !2822)
!2834 = !DILocation(line: 1135, column: 22, scope: !2822)
!2835 = !DILocation(line: 1136, column: 13, scope: !2836)
!2836 = distinct !DILexicalBlock(scope: !2822, file: !1, line: 1136, column: 9)
!2837 = !DILocation(line: 1136, column: 18, scope: !2836)
!2838 = !DILocation(line: 1136, column: 26, scope: !2836)
!2839 = !DILocation(line: 1136, column: 33, scope: !2840)
!2840 = !DILexicalBlockFile(scope: !2836, file: !1, discriminator: 1)
!2841 = !DILocation(line: 1136, column: 37, scope: !2840)
!2842 = !DILocation(line: 1136, column: 9, scope: !2840)
!2843 = !DILocation(line: 1138, column: 7, scope: !2844)
!2844 = distinct !DILexicalBlock(scope: !2836, file: !1, line: 1136, column: 43)
!2845 = !DILocation(line: 1138, column: 15, scope: !2844)
!2846 = !DILocation(line: 1138, column: 23, scope: !2844)
!2847 = !DILocation(line: 1139, column: 7, scope: !2844)
!2848 = !DILocation(line: 1142, column: 5, scope: !2822)
!2849 = !DILocation(line: 1142, column: 5, scope: !2824)
!2850 = !DILocation(line: 1142, column: 5, scope: !2826)
!2851 = !DILocation(line: 1142, column: 5, scope: !2828)
!2852 = !DILocation(line: 1143, column: 5, scope: !2822)
!2853 = !DILocation(line: 1143, column: 5, scope: !2824)
!2854 = !DILocation(line: 1143, column: 5, scope: !2826)
!2855 = !DILocation(line: 1143, column: 5, scope: !2828)
!2856 = !DILocation(line: 1145, column: 10, scope: !2857)
!2857 = distinct !DILexicalBlock(scope: !2822, file: !1, line: 1145, column: 9)
!2858 = !DILocation(line: 1145, column: 9, scope: !2822)
!2859 = !DILocation(line: 1146, column: 7, scope: !2860)
!2860 = distinct !DILexicalBlock(scope: !2857, file: !1, line: 1145, column: 18)
!2861 = !DILocation(line: 1147, column: 22, scope: !2862)
!2862 = distinct !DILexicalBlock(scope: !2860, file: !1, line: 1146, column: 10)
!2863 = !DILocation(line: 1147, column: 49, scope: !2862)
!2864 = !DILocation(line: 1147, column: 59, scope: !2862)
!2865 = !DILocation(line: 1147, column: 17, scope: !2862)
!2866 = !DILocation(line: 1147, column: 15, scope: !2862)
!2867 = !DILocation(line: 1148, column: 7, scope: !2862)
!2868 = !DILocation(line: 1149, column: 14, scope: !2860)
!2869 = !DILocation(line: 1149, column: 20, scope: !2860)
!2870 = !DILocation(line: 1149, column: 24, scope: !2860)
!2871 = !DILocation(line: 1149, column: 27, scope: !2872)
!2872 = !DILexicalBlockFile(scope: !2860, file: !1, discriminator: 1)
!2873 = !DILocation(line: 1149, column: 33, scope: !2872)
!2874 = !DILocation(line: 1148, column: 7, scope: !2875)
!2875 = !DILexicalBlockFile(scope: !2862, file: !1, discriminator: 1)
!2876 = !DILocation(line: 1150, column: 5, scope: !2860)
!2877 = !DILocation(line: 1152, column: 11, scope: !2878)
!2878 = distinct !DILexicalBlock(scope: !2857, file: !1, line: 1150, column: 12)
!2879 = !DILocation(line: 1152, column: 21, scope: !2878)
!2880 = !DILocation(line: 1153, column: 21, scope: !2878)
!2881 = !DILocation(line: 1153, column: 11, scope: !2878)
!2882 = !DILocation(line: 1153, column: 19, scope: !2878)
!2883 = !DILocation(line: 1154, column: 11, scope: !2878)
!2884 = !DILocation(line: 1154, column: 22, scope: !2878)
!2885 = !DILocation(line: 1155, column: 11, scope: !2878)
!2886 = !DILocation(line: 1155, column: 20, scope: !2878)
!2887 = !DILocation(line: 1156, column: 11, scope: !2878)
!2888 = !DILocation(line: 1156, column: 23, scope: !2878)
!2889 = !DILocation(line: 1158, column: 11, scope: !2878)
!2890 = !DILocation(line: 1158, column: 26, scope: !2878)
!2891 = !DILocation(line: 1159, column: 25, scope: !2878)
!2892 = !DILocation(line: 1159, column: 11, scope: !2878)
!2893 = !DILocation(line: 1159, column: 23, scope: !2878)
!2894 = !DILocation(line: 1161, column: 7, scope: !2878)
!2895 = !DILocation(line: 1162, column: 29, scope: !2896)
!2896 = distinct !DILexicalBlock(scope: !2878, file: !1, line: 1161, column: 10)
!2897 = !DILocation(line: 1162, column: 17, scope: !2896)
!2898 = !DILocation(line: 1162, column: 15, scope: !2896)
!2899 = !DILocation(line: 1163, column: 7, scope: !2896)
!2900 = !DILocation(line: 1164, column: 14, scope: !2878)
!2901 = !DILocation(line: 1164, column: 20, scope: !2878)
!2902 = !DILocation(line: 1164, column: 24, scope: !2878)
!2903 = !DILocation(line: 1164, column: 27, scope: !2904)
!2904 = !DILexicalBlockFile(scope: !2878, file: !1, discriminator: 1)
!2905 = !DILocation(line: 1164, column: 33, scope: !2904)
!2906 = !DILocation(line: 1163, column: 7, scope: !2907)
!2907 = !DILexicalBlockFile(scope: !2896, file: !1, discriminator: 1)
!2908 = !DILocation(line: 1167, column: 9, scope: !2909)
!2909 = distinct !DILexicalBlock(scope: !2822, file: !1, line: 1167, column: 9)
!2910 = !DILocation(line: 1167, column: 15, scope: !2909)
!2911 = !DILocation(line: 1167, column: 9, scope: !2822)
!2912 = !DILocation(line: 1169, column: 11, scope: !2913)
!2913 = distinct !DILexicalBlock(scope: !2914, file: !1, line: 1169, column: 11)
!2914 = distinct !DILexicalBlock(scope: !2909, file: !1, line: 1167, column: 20)
!2915 = !DILocation(line: 1169, column: 17, scope: !2913)
!2916 = !DILocation(line: 1169, column: 27, scope: !2913)
!2917 = !DILocation(line: 1169, column: 30, scope: !2918)
!2918 = !DILexicalBlockFile(scope: !2913, file: !1, discriminator: 1)
!2919 = !DILocation(line: 1169, column: 36, scope: !2918)
!2920 = !DILocation(line: 1169, column: 11, scope: !2918)
!2921 = !DILocation(line: 1171, column: 13, scope: !2922)
!2922 = distinct !DILexicalBlock(scope: !2923, file: !1, line: 1171, column: 13)
!2923 = distinct !DILexicalBlock(scope: !2913, file: !1, line: 1169, column: 52)
!2924 = !DILocation(line: 1171, column: 21, scope: !2922)
!2925 = !DILocation(line: 1171, column: 27, scope: !2922)
!2926 = !DILocation(line: 1171, column: 13, scope: !2923)
!2927 = !DILocation(line: 1172, column: 24, scope: !2928)
!2928 = distinct !DILexicalBlock(scope: !2922, file: !1, line: 1171, column: 48)
!2929 = !DILocation(line: 1172, column: 32, scope: !2928)
!2930 = !DILocation(line: 1172, column: 39, scope: !2928)
!2931 = !DILocation(line: 1172, column: 47, scope: !2928)
!2932 = !DILocation(line: 1172, column: 11, scope: !2928)
!2933 = !DILocation(line: 1173, column: 43, scope: !2928)
!2934 = !DILocation(line: 1173, column: 11, scope: !2928)
!2935 = !DILocation(line: 1174, column: 9, scope: !2928)
!2936 = !DILocation(line: 1175, column: 9, scope: !2923)
!2937 = !DILocation(line: 1175, column: 17, scope: !2923)
!2938 = !DILocation(line: 1175, column: 25, scope: !2923)
!2939 = !DILocation(line: 1176, column: 7, scope: !2923)
!2940 = !DILocation(line: 1178, column: 9, scope: !2941)
!2941 = distinct !DILexicalBlock(scope: !2913, file: !1, line: 1176, column: 14)
!2942 = !DILocation(line: 1178, column: 17, scope: !2941)
!2943 = !DILocation(line: 1178, column: 25, scope: !2941)
!2944 = !DILocation(line: 1178, column: 34, scope: !2941)
!2945 = !DILocation(line: 1178, column: 33, scope: !2941)
!2946 = !DILocation(line: 1178, column: 9, scope: !2947)
!2947 = !DILexicalBlockFile(scope: !2941, file: !1, discriminator: 1)
!2948 = !DILocation(line: 1179, column: 13, scope: !2949)
!2949 = distinct !DILexicalBlock(scope: !2941, file: !1, line: 1179, column: 13)
!2950 = !DILocation(line: 1179, column: 21, scope: !2949)
!2951 = !DILocation(line: 1179, column: 27, scope: !2949)
!2952 = !DILocation(line: 1179, column: 13, scope: !2941)
!2953 = !DILocation(line: 1180, column: 11, scope: !2954)
!2954 = distinct !DILexicalBlock(scope: !2949, file: !1, line: 1179, column: 48)
!2955 = !DILocation(line: 1180, column: 19, scope: !2954)
!2956 = !DILocation(line: 1180, column: 25, scope: !2954)
!2957 = !DILocation(line: 1181, column: 23, scope: !2954)
!2958 = !DILocation(line: 1181, column: 31, scope: !2954)
!2959 = !DILocation(line: 1181, column: 38, scope: !2954)
!2960 = !DILocation(line: 1181, column: 46, scope: !2954)
!2961 = !DILocation(line: 1181, column: 11, scope: !2954)
!2962 = !DILocation(line: 1182, column: 31, scope: !2963)
!2963 = distinct !DILexicalBlock(scope: !2954, file: !1, line: 1182, column: 15)
!2964 = !DILocation(line: 1182, column: 39, scope: !2963)
!2965 = !DILocation(line: 1182, column: 16, scope: !2963)
!2966 = !DILocation(line: 1182, column: 15, scope: !2954)
!2967 = !DILocation(line: 1183, column: 13, scope: !2963)
!2968 = !DILocation(line: 1183, column: 13, scope: !2969)
!2969 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 1)
!2970 = distinct !DILexicalBlock(scope: !2963, file: !1, line: 1183, column: 13)
!2971 = !DILocation(line: 1183, column: 13, scope: !2972)
!2972 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 2)
!2973 = !DILocation(line: 1183, column: 13, scope: !2974)
!2974 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 3)
!2975 = !DILocation(line: 1183, column: 13, scope: !2976)
!2976 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 4)
!2977 = !DILocation(line: 1183, column: 13, scope: !2978)
!2978 = !DILexicalBlockFile(scope: !2979, file: !1, discriminator: 5)
!2979 = distinct !DILexicalBlock(scope: !2970, file: !1, line: 1183, column: 13)
!2980 = !DILocation(line: 1183, column: 13, scope: !2981)
!2981 = !DILexicalBlockFile(scope: !2979, file: !1, discriminator: 6)
!2982 = !DILocation(line: 1183, column: 13, scope: !2983)
!2983 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 7)
!2984 = !DILocation(line: 1183, column: 13, scope: !2985)
!2985 = !DILexicalBlockFile(scope: !2986, file: !1, discriminator: 8)
!2986 = distinct !DILexicalBlock(scope: !2970, file: !1, line: 1183, column: 13)
!2987 = !DILocation(line: 1183, column: 13, scope: !2988)
!2988 = !DILexicalBlockFile(scope: !2989, file: !1, discriminator: 9)
!2989 = distinct !DILexicalBlock(scope: !2986, file: !1, line: 1183, column: 13)
!2990 = !DILocation(line: 1183, column: 13, scope: !2991)
!2991 = !DILexicalBlockFile(scope: !2989, file: !1, discriminator: 10)
!2992 = !DILocation(line: 1183, column: 13, scope: !2993)
!2993 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 11)
!2994 = !DILocation(line: 1183, column: 13, scope: !2995)
!2995 = !DILexicalBlockFile(scope: !2970, file: !1, discriminator: 12)
!2996 = !DILocation(line: 1184, column: 43, scope: !2954)
!2997 = !DILocation(line: 1184, column: 11, scope: !2954)
!2998 = !DILocation(line: 1185, column: 9, scope: !2954)
!2999 = !DILocation(line: 1187, column: 7, scope: !2914)
!3000 = !DILocation(line: 1188, column: 16, scope: !3001)
!3001 = distinct !DILexicalBlock(scope: !2909, file: !1, line: 1188, column: 16)
!3002 = !DILocation(line: 1188, column: 22, scope: !3001)
!3003 = !DILocation(line: 1188, column: 16, scope: !2909)
!3004 = !DILocation(line: 1189, column: 22, scope: !3005)
!3005 = distinct !DILexicalBlock(scope: !3001, file: !1, line: 1188, column: 28)
!3006 = !DILocation(line: 1189, column: 7, scope: !3005)
!3007 = !DILocation(line: 1190, column: 7, scope: !3005)
!3008 = !DILocalVariable(name: "buflen", scope: !3009, file: !1, line: 1193, type: !431)
!3009 = distinct !DILexicalBlock(scope: !3001, file: !1, line: 1191, column: 12)
!3010 = !DILocation(line: 1193, column: 15, scope: !3009)
!3011 = !DILocation(line: 1193, column: 28, scope: !3009)
!3012 = !DILocation(line: 1195, column: 11, scope: !3013)
!3013 = distinct !DILexicalBlock(scope: !3009, file: !1, line: 1195, column: 11)
!3014 = !DILocation(line: 1195, column: 11, scope: !3009)
!3015 = !DILocation(line: 1196, column: 36, scope: !3016)
!3016 = distinct !DILexicalBlock(scope: !3013, file: !1, line: 1195, column: 19)
!3017 = !DILocation(line: 1196, column: 15, scope: !3016)
!3018 = !DILocation(line: 1196, column: 13, scope: !3016)
!3019 = !DILocation(line: 1197, column: 13, scope: !3020)
!3020 = distinct !DILexicalBlock(scope: !3016, file: !1, line: 1197, column: 13)
!3021 = !DILocation(line: 1197, column: 17, scope: !3020)
!3022 = !DILocation(line: 1197, column: 13, scope: !3016)
!3023 = !DILocation(line: 1198, column: 11, scope: !3024)
!3024 = distinct !DILexicalBlock(scope: !3020, file: !1, line: 1197, column: 23)
!3025 = !DILocation(line: 1198, column: 19, scope: !3024)
!3026 = !DILocation(line: 1198, column: 27, scope: !3024)
!3027 = !DILocation(line: 1198, column: 35, scope: !3024)
!3028 = !DILocation(line: 1199, column: 11, scope: !3024)
!3029 = !DILocation(line: 1201, column: 7, scope: !3016)
!3030 = !DILocation(line: 1226, column: 7, scope: !3009)
!3031 = !DILocation(line: 1226, column: 15, scope: !3009)
!3032 = !DILocation(line: 1226, column: 23, scope: !3009)
!3033 = !DILocation(line: 1226, column: 31, scope: !3009)
!3034 = !DILocation(line: 1229, column: 11, scope: !3035)
!3035 = distinct !DILexicalBlock(scope: !3009, file: !1, line: 1229, column: 11)
!3036 = !DILocation(line: 1229, column: 19, scope: !3035)
!3037 = !DILocation(line: 1229, column: 17, scope: !3035)
!3038 = !DILocation(line: 1229, column: 11, scope: !3009)
!3039 = !DILocation(line: 1230, column: 9, scope: !3040)
!3040 = distinct !DILexicalBlock(scope: !3035, file: !1, line: 1229, column: 27)
!3041 = !DILocation(line: 1230, column: 17, scope: !3040)
!3042 = !DILocation(line: 1230, column: 23, scope: !3040)
!3043 = !DILocation(line: 1231, column: 9, scope: !3040)
!3044 = !DILocation(line: 1129, column: 3, scope: !3045)
!3045 = !DILexicalBlockFile(scope: !664, file: !1, discriminator: 3)
!3046 = !DILocation(line: 1235, column: 1, scope: !664)
!3047 = !DILocalVariable(name: "stream", arg: 1, scope: !681, file: !1, line: 999, type: !395)
!3048 = !DILocation(line: 999, column: 41, scope: !681)
!3049 = !DILocalVariable(name: "buf", arg: 2, scope: !681, file: !1, line: 999, type: !435)
!3050 = !DILocation(line: 999, column: 65, scope: !681)
!3051 = !DILocation(line: 1000, column: 3, scope: !681)
!3052 = !DILocation(line: 1000, column: 11, scope: !681)
!3053 = !DILocation(line: 1000, column: 17, scope: !681)
!3054 = !DILocation(line: 1001, column: 15, scope: !681)
!3055 = !DILocation(line: 1001, column: 23, scope: !681)
!3056 = !DILocation(line: 1001, column: 30, scope: !681)
!3057 = !DILocation(line: 1001, column: 38, scope: !681)
!3058 = !DILocation(line: 1001, column: 3, scope: !681)
!3059 = !DILocation(line: 1002, column: 23, scope: !3060)
!3060 = distinct !DILexicalBlock(scope: !681, file: !1, line: 1002, column: 7)
!3061 = !DILocation(line: 1002, column: 31, scope: !3060)
!3062 = !DILocation(line: 1002, column: 8, scope: !3060)
!3063 = !DILocation(line: 1002, column: 7, scope: !681)
!3064 = !DILocation(line: 1003, column: 5, scope: !3060)
!3065 = !DILocation(line: 1003, column: 5, scope: !3066)
!3066 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 1)
!3067 = distinct !DILexicalBlock(scope: !3060, file: !1, line: 1003, column: 5)
!3068 = !DILocation(line: 1003, column: 5, scope: !3069)
!3069 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 2)
!3070 = !DILocation(line: 1003, column: 5, scope: !3071)
!3071 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 3)
!3072 = !DILocation(line: 1003, column: 5, scope: !3073)
!3073 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 4)
!3074 = !DILocation(line: 1003, column: 5, scope: !3075)
!3075 = !DILexicalBlockFile(scope: !3076, file: !1, discriminator: 5)
!3076 = distinct !DILexicalBlock(scope: !3067, file: !1, line: 1003, column: 5)
!3077 = !DILocation(line: 1003, column: 5, scope: !3078)
!3078 = !DILexicalBlockFile(scope: !3076, file: !1, discriminator: 6)
!3079 = !DILocation(line: 1003, column: 5, scope: !3080)
!3080 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 7)
!3081 = !DILocation(line: 1003, column: 5, scope: !3082)
!3082 = !DILexicalBlockFile(scope: !3083, file: !1, discriminator: 8)
!3083 = distinct !DILexicalBlock(scope: !3067, file: !1, line: 1003, column: 5)
!3084 = !DILocation(line: 1003, column: 5, scope: !3085)
!3085 = !DILexicalBlockFile(scope: !3086, file: !1, discriminator: 9)
!3086 = distinct !DILexicalBlock(scope: !3083, file: !1, line: 1003, column: 5)
!3087 = !DILocation(line: 1003, column: 5, scope: !3088)
!3088 = !DILexicalBlockFile(scope: !3086, file: !1, discriminator: 10)
!3089 = !DILocation(line: 1003, column: 5, scope: !3090)
!3090 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 11)
!3091 = !DILocation(line: 1003, column: 5, scope: !3092)
!3092 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 12)
!3093 = !DILocation(line: 1004, column: 35, scope: !681)
!3094 = !DILocation(line: 1004, column: 3, scope: !681)
!3095 = !DILocation(line: 1005, column: 3, scope: !681)
!3096 = !DILocation(line: 1005, column: 11, scope: !681)
!3097 = !DILocation(line: 1005, column: 19, scope: !681)
!3098 = !DILocation(line: 1005, column: 35, scope: !681)
!3099 = !DILocation(line: 1006, column: 3, scope: !681)
!3100 = !DILocation(line: 1006, column: 11, scope: !681)
!3101 = !DILocation(line: 1006, column: 17, scope: !681)
!3102 = !DILocation(line: 1007, column: 1, scope: !681)
!3103 = !DILocalVariable(name: "stream", arg: 1, scope: !684, file: !1, line: 662, type: !395)
!3104 = !DILocation(line: 662, column: 36, scope: !684)
!3105 = !DILocalVariable(name: "req", scope: !684, file: !1, line: 663, type: !454)
!3106 = !DILocation(line: 663, column: 18, scope: !684)
!3107 = !DILocalVariable(name: "err", scope: !684, file: !1, line: 664, type: !191)
!3108 = !DILocation(line: 664, column: 7, scope: !684)
!3109 = !DILocation(line: 666, column: 3, scope: !684)
!3110 = !DILocation(line: 666, column: 3, scope: !3111)
!3111 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 1)
!3112 = !DILocation(line: 666, column: 3, scope: !3113)
!3113 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 2)
!3114 = !DILocation(line: 666, column: 3, scope: !3115)
!3115 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 3)
!3116 = !DILocation(line: 667, column: 15, scope: !684)
!3117 = !DILocation(line: 667, column: 23, scope: !684)
!3118 = !DILocation(line: 667, column: 30, scope: !684)
!3119 = !DILocation(line: 667, column: 38, scope: !684)
!3120 = !DILocation(line: 667, column: 3, scope: !684)
!3121 = !DILocation(line: 668, column: 35, scope: !684)
!3122 = !DILocation(line: 668, column: 3, scope: !684)
!3123 = !DILocation(line: 671, column: 8, scope: !3124)
!3124 = distinct !DILexicalBlock(scope: !684, file: !1, line: 671, column: 7)
!3125 = !DILocation(line: 671, column: 16, scope: !3124)
!3126 = !DILocation(line: 671, column: 22, scope: !3124)
!3127 = !DILocation(line: 671, column: 44, scope: !3124)
!3128 = !DILocation(line: 672, column: 9, scope: !3124)
!3129 = !DILocation(line: 672, column: 17, scope: !3124)
!3130 = !DILocation(line: 672, column: 23, scope: !3124)
!3131 = !DILocation(line: 672, column: 37, scope: !3124)
!3132 = !DILocation(line: 673, column: 9, scope: !3124)
!3133 = !DILocation(line: 673, column: 17, scope: !3124)
!3134 = !DILocation(line: 673, column: 23, scope: !3124)
!3135 = !DILocation(line: 671, column: 7, scope: !3111)
!3136 = !DILocation(line: 674, column: 5, scope: !3137)
!3137 = distinct !DILexicalBlock(scope: !3124, file: !1, line: 673, column: 42)
!3138 = !DILocation(line: 674, column: 5, scope: !3139)
!3139 = !DILexicalBlockFile(scope: !3137, file: !1, discriminator: 1)
!3140 = !DILocation(line: 674, column: 5, scope: !3141)
!3141 = !DILexicalBlockFile(scope: !3137, file: !1, discriminator: 2)
!3142 = !DILocation(line: 674, column: 5, scope: !3143)
!3143 = !DILexicalBlockFile(scope: !3137, file: !1, discriminator: 3)
!3144 = !DILocation(line: 676, column: 11, scope: !3137)
!3145 = !DILocation(line: 676, column: 19, scope: !3137)
!3146 = !DILocation(line: 676, column: 9, scope: !3137)
!3147 = !DILocation(line: 677, column: 5, scope: !3137)
!3148 = !DILocation(line: 677, column: 13, scope: !3137)
!3149 = !DILocation(line: 677, column: 26, scope: !3137)
!3150 = !DILocation(line: 678, column: 5, scope: !3137)
!3151 = !DILocation(line: 678, column: 13, scope: !3137)
!3152 = !DILocation(line: 678, column: 19, scope: !3137)
!3153 = !DILocation(line: 679, column: 5, scope: !3137)
!3154 = !DILocation(line: 679, column: 5, scope: !3155)
!3155 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 1)
!3156 = distinct !DILexicalBlock(scope: !3137, file: !1, line: 679, column: 5)
!3157 = !DILocation(line: 679, column: 5, scope: !3158)
!3158 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 2)
!3159 = !DILocation(line: 679, column: 5, scope: !3160)
!3160 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 3)
!3161 = !DILocation(line: 679, column: 5, scope: !3162)
!3162 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 4)
!3163 = !DILocation(line: 679, column: 5, scope: !3164)
!3164 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 5)
!3165 = !DILocation(line: 679, column: 5, scope: !3166)
!3166 = !DILexicalBlockFile(scope: !3167, file: !1, discriminator: 6)
!3167 = distinct !DILexicalBlock(scope: !3156, file: !1, line: 679, column: 5)
!3168 = !DILocation(line: 679, column: 5, scope: !3169)
!3169 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 7)
!3170 = !DILocation(line: 681, column: 9, scope: !3137)
!3171 = !DILocation(line: 682, column: 18, scope: !3172)
!3172 = distinct !DILexicalBlock(scope: !3137, file: !1, line: 682, column: 9)
!3173 = !DILocation(line: 682, column: 9, scope: !3172)
!3174 = !DILocation(line: 682, column: 9, scope: !3137)
!3175 = !DILocation(line: 683, column: 14, scope: !3172)
!3176 = !DILocation(line: 683, column: 13, scope: !3172)
!3177 = !DILocation(line: 683, column: 11, scope: !3172)
!3178 = !DILocation(line: 683, column: 7, scope: !3172)
!3179 = !DILocation(line: 685, column: 9, scope: !3180)
!3180 = distinct !DILexicalBlock(scope: !3137, file: !1, line: 685, column: 9)
!3181 = !DILocation(line: 685, column: 13, scope: !3180)
!3182 = !DILocation(line: 685, column: 9, scope: !3137)
!3183 = !DILocation(line: 686, column: 7, scope: !3180)
!3184 = !DILocation(line: 686, column: 15, scope: !3180)
!3185 = !DILocation(line: 686, column: 21, scope: !3180)
!3186 = !DILocation(line: 688, column: 9, scope: !3187)
!3187 = distinct !DILexicalBlock(scope: !3137, file: !1, line: 688, column: 9)
!3188 = !DILocation(line: 688, column: 14, scope: !3187)
!3189 = !DILocation(line: 688, column: 17, scope: !3187)
!3190 = !DILocation(line: 688, column: 9, scope: !3137)
!3191 = !DILocation(line: 689, column: 7, scope: !3187)
!3192 = !DILocation(line: 689, column: 12, scope: !3187)
!3193 = !DILocation(line: 689, column: 15, scope: !3187)
!3194 = !DILocation(line: 689, column: 20, scope: !3187)
!3195 = !DILocation(line: 690, column: 3, scope: !3137)
!3196 = !DILocation(line: 691, column: 1, scope: !684)
!3197 = !DILocalVariable(name: "stream", arg: 1, scope: !665, file: !1, line: 1053, type: !395)
!3198 = !DILocation(line: 1053, column: 46, scope: !665)
!3199 = !DILocalVariable(name: "msg", arg: 2, scope: !665, file: !1, line: 1053, type: !668)
!3200 = !DILocation(line: 1053, column: 69, scope: !665)
!3201 = !DILocalVariable(name: "cmsg", scope: !665, file: !1, line: 1054, type: !593)
!3202 = !DILocation(line: 1054, column: 19, scope: !665)
!3203 = !DILocation(line: 1056, column: 15, scope: !3204)
!3204 = distinct !DILexicalBlock(scope: !665, file: !1, line: 1056, column: 3)
!3205 = !DILocation(line: 1056, column: 15, scope: !3206)
!3206 = !DILexicalBlockFile(scope: !3204, file: !1, discriminator: 1)
!3207 = !DILocation(line: 1056, column: 15, scope: !3208)
!3208 = !DILexicalBlockFile(scope: !3204, file: !1, discriminator: 2)
!3209 = !DILocation(line: 1056, column: 15, scope: !3210)
!3210 = !DILexicalBlockFile(scope: !3204, file: !1, discriminator: 3)
!3211 = !DILocation(line: 1056, column: 13, scope: !3210)
!3212 = !DILocation(line: 1056, column: 8, scope: !3210)
!3213 = !DILocation(line: 1056, column: 35, scope: !3214)
!3214 = !DILexicalBlockFile(scope: !3215, file: !1, discriminator: 4)
!3215 = distinct !DILexicalBlock(scope: !3204, file: !1, line: 1056, column: 3)
!3216 = !DILocation(line: 1056, column: 40, scope: !3214)
!3217 = !DILocation(line: 1056, column: 3, scope: !3214)
!3218 = !DILocalVariable(name: "start", scope: !3219, file: !1, line: 1057, type: !424)
!3219 = distinct !DILexicalBlock(scope: !3215, file: !1, line: 1056, column: 80)
!3220 = !DILocation(line: 1057, column: 11, scope: !3219)
!3221 = !DILocalVariable(name: "end", scope: !3219, file: !1, line: 1058, type: !424)
!3222 = !DILocation(line: 1058, column: 11, scope: !3219)
!3223 = !DILocalVariable(name: "err", scope: !3219, file: !1, line: 1059, type: !191)
!3224 = !DILocation(line: 1059, column: 9, scope: !3219)
!3225 = !DILocalVariable(name: "pv", scope: !3219, file: !1, line: 1060, type: !173)
!3226 = !DILocation(line: 1060, column: 11, scope: !3219)
!3227 = !DILocalVariable(name: "pi", scope: !3219, file: !1, line: 1061, type: !1983)
!3228 = !DILocation(line: 1061, column: 10, scope: !3219)
!3229 = !DILocalVariable(name: "i", scope: !3219, file: !1, line: 1062, type: !181)
!3230 = !DILocation(line: 1062, column: 18, scope: !3219)
!3231 = !DILocalVariable(name: "count", scope: !3219, file: !1, line: 1063, type: !181)
!3232 = !DILocation(line: 1063, column: 18, scope: !3219)
!3233 = !DILocation(line: 1065, column: 9, scope: !3234)
!3234 = distinct !DILexicalBlock(scope: !3219, file: !1, line: 1065, column: 9)
!3235 = !DILocation(line: 1065, column: 15, scope: !3234)
!3236 = !DILocation(line: 1065, column: 25, scope: !3234)
!3237 = !DILocation(line: 1065, column: 9, scope: !3219)
!3238 = !DILocation(line: 1066, column: 15, scope: !3239)
!3239 = distinct !DILexicalBlock(scope: !3234, file: !1, line: 1065, column: 40)
!3240 = !DILocation(line: 1067, column: 11, scope: !3239)
!3241 = !DILocation(line: 1067, column: 17, scope: !3239)
!3242 = !DILocation(line: 1066, column: 7, scope: !3239)
!3243 = !DILocation(line: 1068, column: 7, scope: !3239)
!3244 = !DILocation(line: 1072, column: 10, scope: !3219)
!3245 = !DILocation(line: 1072, column: 8, scope: !3219)
!3246 = !DILocation(line: 1073, column: 10, scope: !3219)
!3247 = !DILocation(line: 1073, column: 8, scope: !3219)
!3248 = !DILocation(line: 1076, column: 21, scope: !3219)
!3249 = !DILocation(line: 1076, column: 13, scope: !3219)
!3250 = !DILocation(line: 1076, column: 11, scope: !3219)
!3251 = !DILocation(line: 1077, column: 19, scope: !3219)
!3252 = !DILocation(line: 1077, column: 11, scope: !3219)
!3253 = !DILocation(line: 1077, column: 26, scope: !3219)
!3254 = !DILocation(line: 1077, column: 32, scope: !3219)
!3255 = !DILocation(line: 1077, column: 24, scope: !3219)
!3256 = !DILocation(line: 1077, column: 9, scope: !3219)
!3257 = !DILocation(line: 1078, column: 11, scope: !3219)
!3258 = !DILocation(line: 1079, column: 5, scope: !3219)
!3259 = !DILocation(line: 1079, column: 12, scope: !3260)
!3260 = !DILexicalBlockFile(scope: !3219, file: !1, discriminator: 1)
!3261 = !DILocation(line: 1079, column: 20, scope: !3260)
!3262 = !DILocation(line: 1079, column: 18, scope: !3260)
!3263 = !DILocation(line: 1079, column: 52, scope: !3260)
!3264 = !DILocation(line: 1079, column: 50, scope: !3260)
!3265 = !DILocation(line: 1079, column: 5, scope: !3260)
!3266 = !DILocation(line: 1080, column: 12, scope: !3219)
!3267 = !DILocation(line: 1079, column: 5, scope: !3268)
!3268 = !DILexicalBlockFile(scope: !3219, file: !1, discriminator: 2)
!3269 = !DILocation(line: 1081, column: 5, scope: !3219)
!3270 = !DILocation(line: 1081, column: 5, scope: !3260)
!3271 = !DILocation(line: 1081, column: 5, scope: !3268)
!3272 = !DILocation(line: 1081, column: 5, scope: !3273)
!3273 = !DILexicalBlockFile(scope: !3219, file: !1, discriminator: 3)
!3274 = !DILocation(line: 1083, column: 12, scope: !3275)
!3275 = distinct !DILexicalBlock(scope: !3219, file: !1, line: 1083, column: 5)
!3276 = !DILocation(line: 1083, column: 10, scope: !3275)
!3277 = !DILocation(line: 1083, column: 17, scope: !3278)
!3278 = !DILexicalBlockFile(scope: !3279, file: !1, discriminator: 1)
!3279 = distinct !DILexicalBlock(scope: !3275, file: !1, line: 1083, column: 5)
!3280 = !DILocation(line: 1083, column: 21, scope: !3278)
!3281 = !DILocation(line: 1083, column: 19, scope: !3278)
!3282 = !DILocation(line: 1083, column: 5, scope: !3278)
!3283 = !DILocation(line: 1085, column: 11, scope: !3284)
!3284 = distinct !DILexicalBlock(scope: !3285, file: !1, line: 1085, column: 11)
!3285 = distinct !DILexicalBlock(scope: !3279, file: !1, line: 1083, column: 33)
!3286 = !DILocation(line: 1085, column: 19, scope: !3284)
!3287 = !DILocation(line: 1085, column: 31, scope: !3284)
!3288 = !DILocation(line: 1085, column: 11, scope: !3285)
!3289 = !DILocation(line: 1086, column: 35, scope: !3290)
!3290 = distinct !DILexicalBlock(scope: !3284, file: !1, line: 1085, column: 38)
!3291 = !DILocation(line: 1086, column: 46, scope: !3290)
!3292 = !DILocation(line: 1086, column: 43, scope: !3290)
!3293 = !DILocation(line: 1086, column: 15, scope: !3290)
!3294 = !DILocation(line: 1086, column: 13, scope: !3290)
!3295 = !DILocation(line: 1087, column: 13, scope: !3296)
!3296 = distinct !DILexicalBlock(scope: !3290, file: !1, line: 1087, column: 13)
!3297 = !DILocation(line: 1087, column: 17, scope: !3296)
!3298 = !DILocation(line: 1087, column: 13, scope: !3290)
!3299 = !DILocation(line: 1089, column: 11, scope: !3300)
!3300 = distinct !DILexicalBlock(scope: !3296, file: !1, line: 1087, column: 23)
!3301 = !DILocation(line: 1089, column: 18, scope: !3302)
!3302 = !DILexicalBlockFile(scope: !3303, file: !1, discriminator: 1)
!3303 = distinct !DILexicalBlock(scope: !3304, file: !1, line: 1089, column: 11)
!3304 = distinct !DILexicalBlock(scope: !3300, file: !1, line: 1089, column: 11)
!3305 = !DILocation(line: 1089, column: 22, scope: !3302)
!3306 = !DILocation(line: 1089, column: 20, scope: !3302)
!3307 = !DILocation(line: 1089, column: 11, scope: !3302)
!3308 = !DILocation(line: 1090, column: 26, scope: !3303)
!3309 = !DILocation(line: 1090, column: 23, scope: !3303)
!3310 = !DILocation(line: 1090, column: 13, scope: !3303)
!3311 = !DILocation(line: 1089, column: 30, scope: !3312)
!3312 = !DILexicalBlockFile(scope: !3303, file: !1, discriminator: 2)
!3313 = !DILocation(line: 1089, column: 11, scope: !3312)
!3314 = !DILocation(line: 1091, column: 18, scope: !3300)
!3315 = !DILocation(line: 1091, column: 11, scope: !3300)
!3316 = !DILocation(line: 1093, column: 7, scope: !3290)
!3317 = !DILocation(line: 1094, column: 34, scope: !3318)
!3318 = distinct !DILexicalBlock(scope: !3284, file: !1, line: 1093, column: 14)
!3319 = !DILocation(line: 1094, column: 31, scope: !3318)
!3320 = !DILocation(line: 1094, column: 9, scope: !3318)
!3321 = !DILocation(line: 1094, column: 17, scope: !3318)
!3322 = !DILocation(line: 1094, column: 29, scope: !3318)
!3323 = !DILocation(line: 1096, column: 5, scope: !3285)
!3324 = !DILocation(line: 1083, column: 29, scope: !3325)
!3325 = !DILexicalBlockFile(scope: !3279, file: !1, discriminator: 2)
!3326 = !DILocation(line: 1083, column: 5, scope: !3325)
!3327 = !DILocation(line: 1097, column: 3, scope: !3219)
!3328 = !DILocation(line: 1056, column: 56, scope: !3329)
!3329 = !DILexicalBlockFile(scope: !3215, file: !1, discriminator: 5)
!3330 = !DILocation(line: 1056, column: 54, scope: !3329)
!3331 = !DILocation(line: 1056, column: 3, scope: !3329)
!3332 = !DILocation(line: 1099, column: 3, scope: !665)
!3333 = !DILocation(line: 1100, column: 1, scope: !665)
!3334 = !DILocalVariable(name: "stream", arg: 1, scope: !680, file: !1, line: 1010, type: !395)
!3335 = !DILocation(line: 1010, column: 45, scope: !680)
!3336 = !DILocalVariable(name: "fd", arg: 2, scope: !680, file: !1, line: 1010, type: !191)
!3337 = !DILocation(line: 1010, column: 57, scope: !680)
!3338 = !DILocalVariable(name: "queued_fds", scope: !680, file: !1, line: 1011, type: !1392)
!3339 = !DILocation(line: 1011, column: 28, scope: !680)
!3340 = !DILocalVariable(name: "queue_size", scope: !680, file: !1, line: 1012, type: !181)
!3341 = !DILocation(line: 1012, column: 16, scope: !680)
!3342 = !DILocation(line: 1014, column: 16, scope: !680)
!3343 = !DILocation(line: 1014, column: 24, scope: !680)
!3344 = !DILocation(line: 1014, column: 14, scope: !680)
!3345 = !DILocation(line: 1015, column: 7, scope: !3346)
!3346 = distinct !DILexicalBlock(scope: !680, file: !1, line: 1015, column: 7)
!3347 = !DILocation(line: 1015, column: 18, scope: !3346)
!3348 = !DILocation(line: 1015, column: 7, scope: !680)
!3349 = !DILocation(line: 1016, column: 16, scope: !3350)
!3350 = distinct !DILexicalBlock(scope: !3346, file: !1, line: 1015, column: 27)
!3351 = !DILocation(line: 1017, column: 30, scope: !3350)
!3352 = !DILocation(line: 1017, column: 41, scope: !3350)
!3353 = !DILocation(line: 1017, column: 29, scope: !3350)
!3354 = !DILocation(line: 1017, column: 46, scope: !3350)
!3355 = !DILocation(line: 1017, column: 73, scope: !3350)
!3356 = !DILocation(line: 1017, column: 18, scope: !3350)
!3357 = !DILocation(line: 1017, column: 16, scope: !3350)
!3358 = !DILocation(line: 1019, column: 9, scope: !3359)
!3359 = distinct !DILexicalBlock(scope: !3350, file: !1, line: 1019, column: 9)
!3360 = !DILocation(line: 1019, column: 20, scope: !3359)
!3361 = !DILocation(line: 1019, column: 9, scope: !3350)
!3362 = !DILocation(line: 1020, column: 7, scope: !3359)
!3363 = !DILocation(line: 1021, column: 24, scope: !3350)
!3364 = !DILocation(line: 1021, column: 5, scope: !3350)
!3365 = !DILocation(line: 1021, column: 17, scope: !3350)
!3366 = !DILocation(line: 1021, column: 22, scope: !3350)
!3367 = !DILocation(line: 1022, column: 5, scope: !3350)
!3368 = !DILocation(line: 1022, column: 17, scope: !3350)
!3369 = !DILocation(line: 1022, column: 24, scope: !3350)
!3370 = !DILocation(line: 1023, column: 26, scope: !3350)
!3371 = !DILocation(line: 1023, column: 5, scope: !3350)
!3372 = !DILocation(line: 1023, column: 13, scope: !3350)
!3373 = !DILocation(line: 1023, column: 24, scope: !3350)
!3374 = !DILocation(line: 1026, column: 3, scope: !3350)
!3375 = !DILocation(line: 1026, column: 14, scope: !3376)
!3376 = !DILexicalBlockFile(scope: !3377, file: !1, discriminator: 1)
!3377 = distinct !DILexicalBlock(scope: !3346, file: !1, line: 1026, column: 14)
!3378 = !DILocation(line: 1026, column: 26, scope: !3376)
!3379 = !DILocation(line: 1026, column: 34, scope: !3376)
!3380 = !DILocation(line: 1026, column: 46, scope: !3376)
!3381 = !DILocation(line: 1026, column: 31, scope: !3376)
!3382 = !DILocation(line: 1027, column: 18, scope: !3383)
!3383 = distinct !DILexicalBlock(scope: !3377, file: !1, line: 1026, column: 54)
!3384 = !DILocation(line: 1027, column: 30, scope: !3383)
!3385 = !DILocation(line: 1027, column: 35, scope: !3383)
!3386 = !DILocation(line: 1027, column: 16, scope: !3383)
!3387 = !DILocation(line: 1028, column: 30, scope: !3383)
!3388 = !DILocation(line: 1029, column: 31, scope: !3383)
!3389 = !DILocation(line: 1029, column: 42, scope: !3383)
!3390 = !DILocation(line: 1029, column: 30, scope: !3383)
!3391 = !DILocation(line: 1029, column: 47, scope: !3383)
!3392 = !DILocation(line: 1029, column: 74, scope: !3383)
!3393 = !DILocation(line: 1028, column: 18, scope: !3383)
!3394 = !DILocation(line: 1028, column: 16, scope: !3383)
!3395 = !DILocation(line: 1036, column: 9, scope: !3396)
!3396 = distinct !DILexicalBlock(scope: !3383, file: !1, line: 1036, column: 9)
!3397 = !DILocation(line: 1036, column: 20, scope: !3396)
!3398 = !DILocation(line: 1036, column: 9, scope: !3383)
!3399 = !DILocation(line: 1037, column: 7, scope: !3396)
!3400 = !DILocation(line: 1038, column: 24, scope: !3383)
!3401 = !DILocation(line: 1038, column: 5, scope: !3383)
!3402 = !DILocation(line: 1038, column: 17, scope: !3383)
!3403 = !DILocation(line: 1038, column: 22, scope: !3383)
!3404 = !DILocation(line: 1039, column: 26, scope: !3383)
!3405 = !DILocation(line: 1039, column: 5, scope: !3383)
!3406 = !DILocation(line: 1039, column: 13, scope: !3383)
!3407 = !DILocation(line: 1039, column: 24, scope: !3383)
!3408 = !DILocation(line: 1040, column: 3, scope: !3383)
!3409 = !DILocation(line: 1043, column: 43, scope: !680)
!3410 = !DILocation(line: 1043, column: 19, scope: !680)
!3411 = !DILocation(line: 1043, column: 31, scope: !680)
!3412 = !DILocation(line: 1043, column: 37, scope: !680)
!3413 = !DILocation(line: 1043, column: 3, scope: !680)
!3414 = !DILocation(line: 1043, column: 15, scope: !680)
!3415 = !DILocation(line: 1043, column: 41, scope: !680)
!3416 = !DILocation(line: 1045, column: 3, scope: !680)
!3417 = !DILocation(line: 1046, column: 1, scope: !680)
!3418 = !DILocalVariable(name: "req", arg: 1, scope: !689, file: !1, line: 706, type: !380)
!3419 = !DILocation(line: 706, column: 46, scope: !689)
!3420 = !DILocalVariable(name: "stream", scope: !689, file: !1, line: 707, type: !395)
!3421 = !DILocation(line: 707, column: 16, scope: !689)
!3422 = !DILocation(line: 707, column: 25, scope: !689)
!3423 = !DILocation(line: 707, column: 30, scope: !689)
!3424 = !DILocation(line: 710, column: 3, scope: !689)
!3425 = !DILocation(line: 710, column: 3, scope: !3426)
!3426 = !DILexicalBlockFile(scope: !3427, file: !1, discriminator: 1)
!3427 = distinct !DILexicalBlock(scope: !689, file: !1, line: 710, column: 3)
!3428 = !DILocation(line: 718, column: 7, scope: !3429)
!3429 = distinct !DILexicalBlock(scope: !689, file: !1, line: 718, column: 7)
!3430 = !DILocation(line: 718, column: 12, scope: !3429)
!3431 = !DILocation(line: 718, column: 18, scope: !3429)
!3432 = !DILocation(line: 718, column: 7, scope: !689)
!3433 = !DILocation(line: 719, column: 9, scope: !3434)
!3434 = distinct !DILexicalBlock(scope: !3435, file: !1, line: 719, column: 9)
!3435 = distinct !DILexicalBlock(scope: !3429, file: !1, line: 718, column: 24)
!3436 = !DILocation(line: 719, column: 14, scope: !3434)
!3437 = !DILocation(line: 719, column: 22, scope: !3434)
!3438 = !DILocation(line: 719, column: 27, scope: !3434)
!3439 = !DILocation(line: 719, column: 19, scope: !3434)
!3440 = !DILocation(line: 719, column: 9, scope: !3435)
!3441 = !DILocation(line: 720, column: 16, scope: !3434)
!3442 = !DILocation(line: 720, column: 21, scope: !3434)
!3443 = !DILocation(line: 720, column: 7, scope: !3434)
!3444 = !DILocation(line: 721, column: 5, scope: !3435)
!3445 = !DILocation(line: 721, column: 10, scope: !3435)
!3446 = !DILocation(line: 721, column: 15, scope: !3435)
!3447 = !DILocation(line: 722, column: 3, scope: !3435)
!3448 = !DILocation(line: 727, column: 3, scope: !689)
!3449 = !DILocation(line: 727, column: 3, scope: !3450)
!3450 = !DILexicalBlockFile(scope: !3451, file: !1, discriminator: 1)
!3451 = distinct !DILexicalBlock(scope: !689, file: !1, line: 727, column: 3)
!3452 = !DILocation(line: 728, column: 15, scope: !689)
!3453 = !DILocation(line: 728, column: 23, scope: !689)
!3454 = !DILocation(line: 728, column: 30, scope: !689)
!3455 = !DILocation(line: 728, column: 38, scope: !689)
!3456 = !DILocation(line: 728, column: 3, scope: !689)
!3457 = !DILocation(line: 729, column: 1, scope: !689)
