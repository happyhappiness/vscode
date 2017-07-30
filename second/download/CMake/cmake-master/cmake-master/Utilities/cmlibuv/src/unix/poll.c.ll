; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/poll.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

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
%struct.uv_poll_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, void (%struct.uv_poll_s*, i32, i32)*, %struct.uv__io_s }
%union.anon.4 = type { [4 x i8*] }

@.str = private unnamed_addr constant [53 x i8] c"!(((handle)->flags & (UV_CLOSING | UV_CLOSED)) != 0)\00", align 1
@.str.1 = private unnamed_addr constant [68 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/poll.c\00", align 1
@__PRETTY_FUNCTION__.uv_poll_stop = private unnamed_addr constant [30 x i8] c"int uv_poll_stop(uv_poll_t *)\00", align 1
@.str.2 = private unnamed_addr constant [62 x i8] c"(pevents & ~(UV_READABLE | UV_WRITABLE | UV_DISCONNECT)) == 0\00", align 1
@__PRETTY_FUNCTION__.uv_poll_start = private unnamed_addr constant [48 x i8] c"int uv_poll_start(uv_poll_t *, int, uv_poll_cb)\00", align 1
@.str.3 = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@__PRETTY_FUNCTION__.uv__poll_io = private unnamed_addr constant [56 x i8] c"void uv__poll_io(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@__PRETTY_FUNCTION__.uv__poll_stop = private unnamed_addr constant [32 x i8] c"void uv__poll_stop(uv_poll_t *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_poll_init(%struct.uv_loop_s* %loop, %struct.uv_poll_s* %handle, i32 %fd) #0 !dbg !292 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_poll_s*, align 8
  %fd.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !316, metadata !317), !dbg !318
  store %struct.uv_poll_s* %handle, %struct.uv_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle.addr, metadata !319, metadata !317), !dbg !320
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !321, metadata !317), !dbg !322
  call void @llvm.dbg.declare(metadata i32* %err, metadata !323, metadata !317), !dbg !324
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !325
  %1 = load i32, i32* %fd.addr, align 4, !dbg !326
  %call = call i32 @uv__io_check_fd(%struct.uv_loop_s* %0, i32 %1), !dbg !327
  store i32 %call, i32* %err, align 4, !dbg !328
  %2 = load i32, i32* %err, align 4, !dbg !329
  %tobool = icmp ne i32 %2, 0, !dbg !329
  br i1 %tobool, label %if.then, label %if.end, !dbg !331

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %err, align 4, !dbg !332
  store i32 %3, i32* %retval, align 4, !dbg !333
  br label %return, !dbg !333

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %fd.addr, align 4, !dbg !334
  %call1 = call i32 @uv__nonblock_ioctl(i32 %4, i32 1), !dbg !335
  store i32 %call1, i32* %err, align 4, !dbg !336
  %5 = load i32, i32* %err, align 4, !dbg !337
  %cmp = icmp eq i32 %5, -25, !dbg !339
  br i1 %cmp, label %if.then2, label %if.end4, !dbg !340

if.then2:                                         ; preds = %if.end
  %6 = load i32, i32* %fd.addr, align 4, !dbg !341
  %call3 = call i32 @uv__nonblock_fcntl(i32 %6, i32 1), !dbg !343
  store i32 %call3, i32* %err, align 4, !dbg !344
  br label %if.end4, !dbg !345

if.end4:                                          ; preds = %if.then2, %if.end
  %7 = load i32, i32* %err, align 4, !dbg !346
  %tobool5 = icmp ne i32 %7, 0, !dbg !346
  br i1 %tobool5, label %if.then6, label %if.end7, !dbg !348

if.then6:                                         ; preds = %if.end4
  %8 = load i32, i32* %err, align 4, !dbg !349
  store i32 %8, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

if.end7:                                          ; preds = %if.end4
  br label %do.body, !dbg !351

do.body:                                          ; preds = %if.end7
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !352
  %10 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !352
  %11 = bitcast %struct.uv_poll_s* %10 to %struct.uv_handle_s*, !dbg !352
  %loop8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %11, i32 0, i32 1, !dbg !352
  store %struct.uv_loop_s* %9, %struct.uv_loop_s** %loop8, align 8, !dbg !352
  %12 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !352
  %13 = bitcast %struct.uv_poll_s* %12 to %struct.uv_handle_s*, !dbg !352
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %13, i32 0, i32 2, !dbg !352
  store i32 8, i32* %type, align 8, !dbg !352
  %14 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !352
  %15 = bitcast %struct.uv_poll_s* %14 to %struct.uv_handle_s*, !dbg !352
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 7, !dbg !352
  store i32 8192, i32* %flags, align 8, !dbg !352
  br label %do.body9, !dbg !352

do.body9:                                         ; preds = %do.body
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !355
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 2, !dbg !355
  %17 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !355
  %18 = bitcast %struct.uv_poll_s* %17 to %struct.uv_handle_s*, !dbg !355
  %handle_queue10 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !355
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue10, i64 0, i64 0, !dbg !355
  %19 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !355
  store [2 x i8*]* %handle_queue, [2 x i8*]** %19, align 8, !dbg !355
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !355
  %handle_queue11 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 2, !dbg !355
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue11, i64 0, i64 1, !dbg !355
  %21 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !355
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !355
  %23 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !355
  %24 = bitcast %struct.uv_poll_s* %23 to %struct.uv_handle_s*, !dbg !355
  %handle_queue13 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %24, i32 0, i32 4, !dbg !355
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !355
  %25 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !355
  store [2 x i8*]* %22, [2 x i8*]** %25, align 8, !dbg !355
  %26 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !355
  %27 = bitcast %struct.uv_poll_s* %26 to %struct.uv_handle_s*, !dbg !355
  %handle_queue15 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %27, i32 0, i32 4, !dbg !355
  %28 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !355
  %29 = bitcast %struct.uv_poll_s* %28 to %struct.uv_handle_s*, !dbg !355
  %handle_queue16 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 4, !dbg !355
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue16, i64 0, i64 1, !dbg !355
  %30 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !355
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 8, !dbg !355
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %31, i64 0, i64 0, !dbg !355
  %32 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !355
  store [2 x i8*]* %handle_queue15, [2 x i8*]** %32, align 8, !dbg !355
  %33 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !355
  %34 = bitcast %struct.uv_poll_s* %33 to %struct.uv_handle_s*, !dbg !355
  %handle_queue19 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %34, i32 0, i32 4, !dbg !355
  %35 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !355
  %handle_queue20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %35, i32 0, i32 2, !dbg !355
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue20, i64 0, i64 1, !dbg !355
  %36 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !355
  store [2 x i8*]* %handle_queue19, [2 x i8*]** %36, align 8, !dbg !355
  br label %do.end, !dbg !355

do.end:                                           ; preds = %do.body9
  %37 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !358
  %38 = bitcast %struct.uv_poll_s* %37 to %struct.uv_handle_s*, !dbg !358
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %38, i32 0, i32 6, !dbg !358
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !358
  br label %do.end22, !dbg !358

do.end22:                                         ; preds = %do.end
  %39 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !360
  %io_watcher = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %39, i32 0, i32 9, !dbg !361
  %40 = load i32, i32* %fd.addr, align 4, !dbg !362
  call void @uv__io_init(%struct.uv__io_s* %io_watcher, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__poll_io, i32 %40), !dbg !363
  %41 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !364
  %poll_cb = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %41, i32 0, i32 8, !dbg !365
  store void (%struct.uv_poll_s*, i32, i32)* null, void (%struct.uv_poll_s*, i32, i32)** %poll_cb, align 8, !dbg !366
  store i32 0, i32* %retval, align 4, !dbg !367
  br label %return, !dbg !367

return:                                           ; preds = %do.end22, %if.then6, %if.then
  %42 = load i32, i32* %retval, align 4, !dbg !368
  ret i32 %42, !dbg !368
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @uv__io_check_fd(%struct.uv_loop_s*, i32) #2

declare i32 @uv__nonblock_ioctl(i32, i32) #2

declare i32 @uv__nonblock_fcntl(i32, i32) #2

declare void @uv__io_init(%struct.uv__io_s*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__poll_io(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !309 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  %handle = alloca %struct.uv_poll_s*, align 8
  %pevents = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !369, metadata !317), !dbg !370
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !371, metadata !317), !dbg !372
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !373, metadata !317), !dbg !374
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle, metadata !375, metadata !317), !dbg !376
  call void @llvm.dbg.declare(metadata i32* %pevents, metadata !377, metadata !317), !dbg !378
  %0 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !379
  %1 = bitcast %struct.uv__io_s* %0 to i8*, !dbg !379
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -104, !dbg !379
  %2 = bitcast i8* %add.ptr to %struct.uv_poll_s*, !dbg !379
  store %struct.uv_poll_s* %2, %struct.uv_poll_s** %handle, align 8, !dbg !380
  %3 = load i32, i32* %events.addr, align 4, !dbg !381
  %and = and i32 %3, 8, !dbg !383
  %tobool = icmp ne i32 %and, 0, !dbg !383
  br i1 %tobool, label %if.then, label %if.end16, !dbg !384

if.then:                                          ; preds = %entry
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !385
  %5 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !387
  call void @uv__io_stop(%struct.uv_loop_s* %4, %struct.uv__io_s* %5, i32 8197), !dbg !388
  br label %do.body, !dbg !389

do.body:                                          ; preds = %if.then
  %6 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !390
  %flags = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %6, i32 0, i32 7, !dbg !390
  %7 = load i32, i32* %flags, align 8, !dbg !390
  %and1 = and i32 %7, 0, !dbg !390
  %cmp = icmp eq i32 %and1, 0, !dbg !390
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !390

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !393

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 38, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.uv__poll_io, i32 0, i32 0)) #4, !dbg !395
  unreachable, !dbg !395
                                                  ; No predecessors!
  br label %cond.end, !dbg !397

cond.end:                                         ; preds = %8, %cond.true
  %9 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !399
  %flags2 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %9, i32 0, i32 7, !dbg !399
  %10 = load i32, i32* %flags2, align 8, !dbg !399
  %and3 = and i32 %10, 16384, !dbg !399
  %cmp4 = icmp eq i32 %and3, 0, !dbg !399
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !399

if.then5:                                         ; preds = %cond.end
  br label %do.end15, !dbg !402

if.end:                                           ; preds = %cond.end
  %11 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !404
  %flags6 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %11, i32 0, i32 7, !dbg !404
  %12 = load i32, i32* %flags6, align 8, !dbg !404
  %and7 = and i32 %12, -16385, !dbg !404
  store i32 %and7, i32* %flags6, align 8, !dbg !404
  %13 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !404
  %flags8 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %13, i32 0, i32 7, !dbg !404
  %14 = load i32, i32* %flags8, align 8, !dbg !404
  %and9 = and i32 %14, 8192, !dbg !404
  %cmp10 = icmp ne i32 %and9, 0, !dbg !404
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !404

if.then11:                                        ; preds = %if.end
  br label %do.body12, !dbg !406

do.body12:                                        ; preds = %if.then11
  %15 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !409
  %loop13 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %15, i32 0, i32 1, !dbg !409
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop13, align 8, !dbg !409
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 1, !dbg !409
  %17 = load i32, i32* %active_handles, align 8, !dbg !409
  %dec = add i32 %17, -1, !dbg !409
  store i32 %dec, i32* %active_handles, align 8, !dbg !409
  br label %do.end, !dbg !409

do.end:                                           ; preds = %do.body12
  br label %if.end14, !dbg !412

if.end14:                                         ; preds = %do.end, %if.end
  br label %do.end15, !dbg !414

do.end15:                                         ; preds = %if.end14, %if.then5
  %18 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !416
  %poll_cb = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %18, i32 0, i32 8, !dbg !417
  %19 = load void (%struct.uv_poll_s*, i32, i32)*, void (%struct.uv_poll_s*, i32, i32)** %poll_cb, align 8, !dbg !417
  %20 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !418
  call void %19(%struct.uv_poll_s* %20, i32 -9, i32 0), !dbg !416
  br label %return, !dbg !419

if.end16:                                         ; preds = %entry
  store i32 0, i32* %pevents, align 4, !dbg !420
  %21 = load i32, i32* %events.addr, align 4, !dbg !421
  %and17 = and i32 %21, 1, !dbg !423
  %tobool18 = icmp ne i32 %and17, 0, !dbg !423
  br i1 %tobool18, label %if.then19, label %if.end20, !dbg !424

if.then19:                                        ; preds = %if.end16
  %22 = load i32, i32* %pevents, align 4, !dbg !425
  %or = or i32 %22, 1, !dbg !425
  store i32 %or, i32* %pevents, align 4, !dbg !425
  br label %if.end20, !dbg !426

if.end20:                                         ; preds = %if.then19, %if.end16
  %23 = load i32, i32* %events.addr, align 4, !dbg !427
  %and21 = and i32 %23, 4, !dbg !429
  %tobool22 = icmp ne i32 %and21, 0, !dbg !429
  br i1 %tobool22, label %if.then23, label %if.end25, !dbg !430

if.then23:                                        ; preds = %if.end20
  %24 = load i32, i32* %pevents, align 4, !dbg !431
  %or24 = or i32 %24, 2, !dbg !431
  store i32 %or24, i32* %pevents, align 4, !dbg !431
  br label %if.end25, !dbg !432

if.end25:                                         ; preds = %if.then23, %if.end20
  %25 = load i32, i32* %events.addr, align 4, !dbg !433
  %and26 = and i32 %25, 8192, !dbg !435
  %tobool27 = icmp ne i32 %and26, 0, !dbg !435
  br i1 %tobool27, label %if.then28, label %if.end30, !dbg !436

if.then28:                                        ; preds = %if.end25
  %26 = load i32, i32* %pevents, align 4, !dbg !437
  %or29 = or i32 %26, 4, !dbg !437
  store i32 %or29, i32* %pevents, align 4, !dbg !437
  br label %if.end30, !dbg !438

if.end30:                                         ; preds = %if.then28, %if.end25
  %27 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !439
  %poll_cb31 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %27, i32 0, i32 8, !dbg !440
  %28 = load void (%struct.uv_poll_s*, i32, i32)*, void (%struct.uv_poll_s*, i32, i32)** %poll_cb31, align 8, !dbg !440
  %29 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle, align 8, !dbg !441
  %30 = load i32, i32* %pevents, align 4, !dbg !442
  call void %28(%struct.uv_poll_s* %29, i32 0, i32 %30), !dbg !439
  br label %return, !dbg !443

return:                                           ; preds = %if.end30, %do.end15
  ret void, !dbg !444
}

; Function Attrs: nounwind uwtable
define i32 @uv_poll_init_socket(%struct.uv_loop_s* %loop, %struct.uv_poll_s* %handle, i32 %socket) #0 !dbg !296 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_poll_s*, align 8
  %socket.addr = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !446, metadata !317), !dbg !447
  store %struct.uv_poll_s* %handle, %struct.uv_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle.addr, metadata !448, metadata !317), !dbg !449
  store i32 %socket, i32* %socket.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %socket.addr, metadata !450, metadata !317), !dbg !451
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !452
  %1 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !453
  %2 = load i32, i32* %socket.addr, align 4, !dbg !454
  %call = call i32 @uv_poll_init(%struct.uv_loop_s* %0, %struct.uv_poll_s* %1, i32 %2), !dbg !455
  ret i32 %call, !dbg !456
}

; Function Attrs: nounwind uwtable
define i32 @uv_poll_stop(%struct.uv_poll_s* %handle) #0 !dbg !300 {
entry:
  %handle.addr = alloca %struct.uv_poll_s*, align 8
  store %struct.uv_poll_s* %handle, %struct.uv_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle.addr, metadata !457, metadata !317), !dbg !458
  %0 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !459
  %flags = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %0, i32 0, i32 7, !dbg !459
  %1 = load i32, i32* %flags, align 8, !dbg !459
  %and = and i32 %1, 3, !dbg !459
  %cmp = icmp ne i32 %and, 0, !dbg !459
  br i1 %cmp, label %cond.false, label %cond.true, !dbg !459

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !460

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 95, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv_poll_stop, i32 0, i32 0)) #4, !dbg !462
  unreachable, !dbg !462
                                                  ; No predecessors!
  br label %cond.end, !dbg !464

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !466
  call void @uv__poll_stop(%struct.uv_poll_s* %3), !dbg !467
  ret i32 0, !dbg !468
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind uwtable
define internal void @uv__poll_stop(%struct.uv_poll_s* %handle) #0 !dbg !312 {
entry:
  %handle.addr = alloca %struct.uv_poll_s*, align 8
  store %struct.uv_poll_s* %handle, %struct.uv_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle.addr, metadata !469, metadata !317), !dbg !470
  %0 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !471
  %loop = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %0, i32 0, i32 1, !dbg !472
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !472
  %2 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !473
  %io_watcher = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %2, i32 0, i32 9, !dbg !474
  call void @uv__io_stop(%struct.uv_loop_s* %1, %struct.uv__io_s* %io_watcher, i32 8197), !dbg !475
  br label %do.body, !dbg !476

do.body:                                          ; preds = %entry
  %3 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !477
  %flags = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %3, i32 0, i32 7, !dbg !477
  %4 = load i32, i32* %flags, align 8, !dbg !477
  %and = and i32 %4, 0, !dbg !477
  %cmp = icmp eq i32 %and, 0, !dbg !477
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !477

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !480

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 90, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.uv__poll_stop, i32 0, i32 0)) #4, !dbg !482
  unreachable, !dbg !482
                                                  ; No predecessors!
  br label %cond.end, !dbg !484

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !486
  %flags1 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %6, i32 0, i32 7, !dbg !486
  %7 = load i32, i32* %flags1, align 8, !dbg !486
  %and2 = and i32 %7, 16384, !dbg !486
  %cmp3 = icmp eq i32 %and2, 0, !dbg !486
  br i1 %cmp3, label %if.then, label %if.end, !dbg !486

if.then:                                          ; preds = %cond.end
  br label %do.end13, !dbg !489

if.end:                                           ; preds = %cond.end
  %8 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !491
  %flags4 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %8, i32 0, i32 7, !dbg !491
  %9 = load i32, i32* %flags4, align 8, !dbg !491
  %and5 = and i32 %9, -16385, !dbg !491
  store i32 %and5, i32* %flags4, align 8, !dbg !491
  %10 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !491
  %flags6 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %10, i32 0, i32 7, !dbg !491
  %11 = load i32, i32* %flags6, align 8, !dbg !491
  %and7 = and i32 %11, 8192, !dbg !491
  %cmp8 = icmp ne i32 %and7, 0, !dbg !491
  br i1 %cmp8, label %if.then9, label %if.end12, !dbg !491

if.then9:                                         ; preds = %if.end
  br label %do.body10, !dbg !493

do.body10:                                        ; preds = %if.then9
  %12 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !496
  %loop11 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %12, i32 0, i32 1, !dbg !496
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop11, align 8, !dbg !496
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 1, !dbg !496
  %14 = load i32, i32* %active_handles, align 8, !dbg !496
  %dec = add i32 %14, -1, !dbg !496
  store i32 %dec, i32* %active_handles, align 8, !dbg !496
  br label %do.end, !dbg !496

do.end:                                           ; preds = %do.body10
  br label %if.end12, !dbg !499

if.end12:                                         ; preds = %do.end, %if.end
  br label %do.end13, !dbg !501

do.end13:                                         ; preds = %if.end12, %if.then
  ret void, !dbg !503
}

; Function Attrs: nounwind uwtable
define i32 @uv_poll_start(%struct.uv_poll_s* %handle, i32 %pevents, void (%struct.uv_poll_s*, i32, i32)* %poll_cb) #0 !dbg !303 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_poll_s*, align 8
  %pevents.addr = alloca i32, align 4
  %poll_cb.addr = alloca void (%struct.uv_poll_s*, i32, i32)*, align 8
  %events = alloca i32, align 4
  store %struct.uv_poll_s* %handle, %struct.uv_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle.addr, metadata !504, metadata !317), !dbg !505
  store i32 %pevents, i32* %pevents.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pevents.addr, metadata !506, metadata !317), !dbg !507
  store void (%struct.uv_poll_s*, i32, i32)* %poll_cb, void (%struct.uv_poll_s*, i32, i32)** %poll_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_poll_s*, i32, i32)** %poll_cb.addr, metadata !508, metadata !317), !dbg !509
  call void @llvm.dbg.declare(metadata i32* %events, metadata !510, metadata !317), !dbg !511
  %0 = load i32, i32* %pevents.addr, align 4, !dbg !512
  %and = and i32 %0, -8, !dbg !512
  %cmp = icmp eq i32 %and, 0, !dbg !512
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !512

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !513

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 104, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @__PRETTY_FUNCTION__.uv_poll_start, i32 0, i32 0)) #4, !dbg !515
  unreachable, !dbg !515
                                                  ; No predecessors!
  br label %cond.end, !dbg !517

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !519
  %flags = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %2, i32 0, i32 7, !dbg !519
  %3 = load i32, i32* %flags, align 8, !dbg !519
  %and1 = and i32 %3, 3, !dbg !519
  %cmp2 = icmp ne i32 %and1, 0, !dbg !519
  br i1 %cmp2, label %cond.false4, label %cond.true3, !dbg !519

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !520

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 105, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @__PRETTY_FUNCTION__.uv_poll_start, i32 0, i32 0)) #4, !dbg !521
  unreachable, !dbg !521
                                                  ; No predecessors!
  br label %cond.end5, !dbg !522

cond.end5:                                        ; preds = %4, %cond.true3
  %5 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !523
  call void @uv__poll_stop(%struct.uv_poll_s* %5), !dbg !524
  %6 = load i32, i32* %pevents.addr, align 4, !dbg !525
  %cmp6 = icmp eq i32 %6, 0, !dbg !527
  br i1 %cmp6, label %if.then, label %if.end, !dbg !528

if.then:                                          ; preds = %cond.end5
  store i32 0, i32* %retval, align 4, !dbg !529
  br label %return, !dbg !529

if.end:                                           ; preds = %cond.end5
  store i32 0, i32* %events, align 4, !dbg !530
  %7 = load i32, i32* %pevents.addr, align 4, !dbg !531
  %and7 = and i32 %7, 1, !dbg !533
  %tobool = icmp ne i32 %and7, 0, !dbg !533
  br i1 %tobool, label %if.then8, label %if.end9, !dbg !534

if.then8:                                         ; preds = %if.end
  %8 = load i32, i32* %events, align 4, !dbg !535
  %or = or i32 %8, 1, !dbg !535
  store i32 %or, i32* %events, align 4, !dbg !535
  br label %if.end9, !dbg !536

if.end9:                                          ; preds = %if.then8, %if.end
  %9 = load i32, i32* %pevents.addr, align 4, !dbg !537
  %and10 = and i32 %9, 2, !dbg !539
  %tobool11 = icmp ne i32 %and10, 0, !dbg !539
  br i1 %tobool11, label %if.then12, label %if.end14, !dbg !540

if.then12:                                        ; preds = %if.end9
  %10 = load i32, i32* %events, align 4, !dbg !541
  %or13 = or i32 %10, 4, !dbg !541
  store i32 %or13, i32* %events, align 4, !dbg !541
  br label %if.end14, !dbg !542

if.end14:                                         ; preds = %if.then12, %if.end9
  %11 = load i32, i32* %pevents.addr, align 4, !dbg !543
  %and15 = and i32 %11, 4, !dbg !545
  %tobool16 = icmp ne i32 %and15, 0, !dbg !545
  br i1 %tobool16, label %if.then17, label %if.end19, !dbg !546

if.then17:                                        ; preds = %if.end14
  %12 = load i32, i32* %events, align 4, !dbg !547
  %or18 = or i32 %12, 8192, !dbg !547
  store i32 %or18, i32* %events, align 4, !dbg !547
  br label %if.end19, !dbg !548

if.end19:                                         ; preds = %if.then17, %if.end14
  %13 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !549
  %loop = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %13, i32 0, i32 1, !dbg !550
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !550
  %15 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !551
  %io_watcher = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %15, i32 0, i32 9, !dbg !552
  %16 = load i32, i32* %events, align 4, !dbg !553
  call void @uv__io_start(%struct.uv_loop_s* %14, %struct.uv__io_s* %io_watcher, i32 %16), !dbg !554
  br label %do.body, !dbg !555

do.body:                                          ; preds = %if.end19
  %17 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !556
  %flags20 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %17, i32 0, i32 7, !dbg !556
  %18 = load i32, i32* %flags20, align 8, !dbg !556
  %and21 = and i32 %18, 0, !dbg !556
  %cmp22 = icmp eq i32 %and21, 0, !dbg !556
  br i1 %cmp22, label %cond.true23, label %cond.false24, !dbg !556

cond.true23:                                      ; preds = %do.body
  br label %cond.end25, !dbg !559

cond.false24:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.1, i32 0, i32 0), i32 121, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @__PRETTY_FUNCTION__.uv_poll_start, i32 0, i32 0)) #4, !dbg !561
  unreachable, !dbg !561
                                                  ; No predecessors!
  br label %cond.end25, !dbg !563

cond.end25:                                       ; preds = %19, %cond.true23
  %20 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !565
  %flags26 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %20, i32 0, i32 7, !dbg !565
  %21 = load i32, i32* %flags26, align 8, !dbg !565
  %and27 = and i32 %21, 16384, !dbg !565
  %cmp28 = icmp ne i32 %and27, 0, !dbg !565
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !565

if.then29:                                        ; preds = %cond.end25
  br label %do.end40, !dbg !568

if.end30:                                         ; preds = %cond.end25
  %22 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !570
  %flags31 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %22, i32 0, i32 7, !dbg !570
  %23 = load i32, i32* %flags31, align 8, !dbg !570
  %or32 = or i32 %23, 16384, !dbg !570
  store i32 %or32, i32* %flags31, align 8, !dbg !570
  %24 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !570
  %flags33 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %24, i32 0, i32 7, !dbg !570
  %25 = load i32, i32* %flags33, align 8, !dbg !570
  %and34 = and i32 %25, 8192, !dbg !570
  %cmp35 = icmp ne i32 %and34, 0, !dbg !570
  br i1 %cmp35, label %if.then36, label %if.end39, !dbg !570

if.then36:                                        ; preds = %if.end30
  br label %do.body37, !dbg !572

do.body37:                                        ; preds = %if.then36
  %26 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !575
  %loop38 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %26, i32 0, i32 1, !dbg !575
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop38, align 8, !dbg !575
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 1, !dbg !575
  %28 = load i32, i32* %active_handles, align 8, !dbg !575
  %inc = add i32 %28, 1, !dbg !575
  store i32 %inc, i32* %active_handles, align 8, !dbg !575
  br label %do.end, !dbg !575

do.end:                                           ; preds = %do.body37
  br label %if.end39, !dbg !578

if.end39:                                         ; preds = %do.end, %if.end30
  br label %do.end40, !dbg !580

do.end40:                                         ; preds = %if.end39, %if.then29
  %29 = load void (%struct.uv_poll_s*, i32, i32)*, void (%struct.uv_poll_s*, i32, i32)** %poll_cb.addr, align 8, !dbg !582
  %30 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !583
  %poll_cb41 = getelementptr inbounds %struct.uv_poll_s, %struct.uv_poll_s* %30, i32 0, i32 8, !dbg !584
  store void (%struct.uv_poll_s*, i32, i32)* %29, void (%struct.uv_poll_s*, i32, i32)** %poll_cb41, align 8, !dbg !585
  store i32 0, i32* %retval, align 4, !dbg !586
  br label %return, !dbg !586

return:                                           ; preds = %do.end40, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !587
  ret i32 %31, !dbg !587
}

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define void @uv__poll_close(%struct.uv_poll_s* %handle) #0 !dbg !306 {
entry:
  %handle.addr = alloca %struct.uv_poll_s*, align 8
  store %struct.uv_poll_s* %handle, %struct.uv_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_poll_s** %handle.addr, metadata !588, metadata !317), !dbg !589
  %0 = load %struct.uv_poll_s*, %struct.uv_poll_s** %handle.addr, align 8, !dbg !590
  call void @uv__poll_stop(%struct.uv_poll_s* %0), !dbg !591
  ret void, !dbg !592
}

declare void @uv__io_stop(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!313, !314}
!llvm.ident = !{!315}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !57, subprograms: !291)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/poll.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !33, !52}
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
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !34, line: 124, size: 32, align: 32, elements: !35)
!34 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!35 = !{!36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51}
!36 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!37 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!38 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!39 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!40 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!41 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!42 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!43 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!44 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!45 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!46 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!47 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!48 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!49 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!50 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!51 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!52 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "uv_poll_event", file: !4, line: 723, size: 32, align: 32, elements: !53)
!53 = !{!54, !55, !56}
!54 = !DIEnumerator(name: "UV_READABLE", value: 1)
!55 = !DIEnumerator(name: "UV_WRITABLE", value: 2)
!56 = !DIEnumerator(name: "UV_DISCONNECT", value: 4)
!57 = !{!58, !264, !268, !290}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !60)
!60 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !61)
!61 = !{!62, !64, !254, !255, !256, !257, !262, !263}
!62 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !60, file: !4, line: 426, baseType: !63, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !60, file: !4, line: 426, baseType: !65, size: 64, align: 64, offset: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !67)
!67 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !68)
!68 = !{!69, !70, !72, !76, !77, !78, !80, !82, !83, !84, !103, !104, !105, !106, !137, !169, !193, !194, !195, !196, !197, !198, !199, !203, !204, !205, !210, !213, !214, !216, !217, !250, !251, !252, !253}
!69 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !67, file: !4, line: 1475, baseType: !63, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !67, file: !4, line: 1477, baseType: !71, size: 32, align: 32, offset: 64)
!71 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !67, file: !4, line: 1478, baseType: !73, size: 128, align: 64, offset: 128)
!73 = !DICompositeType(tag: DW_TAG_array_type, baseType: !63, size: 128, align: 64, elements: !74)
!74 = !{!75}
!75 = !DISubrange(count: 2)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !67, file: !4, line: 1479, baseType: !73, size: 128, align: 64, offset: 256)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !67, file: !4, line: 1481, baseType: !71, size: 32, align: 32, offset: 384)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !67, file: !4, line: 1482, baseType: !79, size: 64, align: 64, offset: 448)
!79 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !67, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 512)
!81 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 576)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 704)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !67, file: !4, line: 1482, baseType: !85, size: 64, align: 64, offset: 832)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !88, line: 87, baseType: !89)
!88 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!89 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !88, line: 89, size: 448, align: 64, elements: !90)
!90 = !{!91, !98, !99, !100, !101, !102}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !89, file: !88, line: 90, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !88, line: 84, baseType: !93)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DISubroutineType(types: !95)
!95 = !{null, !96, !97, !71}
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !89, file: !88, line: 91, baseType: !73, size: 128, align: 64, offset: 64)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !89, file: !88, line: 92, baseType: !73, size: 128, align: 64, offset: 192)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !89, file: !88, line: 93, baseType: !71, size: 32, align: 32, offset: 320)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !89, file: !88, line: 94, baseType: !71, size: 32, align: 32, offset: 352)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !89, file: !88, line: 95, baseType: !81, size: 32, align: 32, offset: 384)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !67, file: !4, line: 1482, baseType: !71, size: 32, align: 32, offset: 896)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !67, file: !4, line: 1482, baseType: !71, size: 32, align: 32, offset: 928)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !67, file: !4, line: 1482, baseType: !107, size: 320, align: 64, offset: 1088)
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !88, line: 129, baseType: !108)
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !109, line: 127, baseType: !110)
!109 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!110 = !DICompositeType(tag: DW_TAG_union_type, file: !109, line: 90, size: 320, align: 64, elements: !111)
!111 = !{!112, !130, !135}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !110, file: !109, line: 124, baseType: !113, size: 320, align: 64)
!113 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !109, line: 92, size: 320, align: 64, elements: !114)
!114 = !{!115, !116, !117, !118, !119, !120, !122, !123}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !113, file: !109, line: 94, baseType: !81, size: 32, align: 32)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !113, file: !109, line: 95, baseType: !71, size: 32, align: 32, offset: 32)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !113, file: !109, line: 96, baseType: !81, size: 32, align: 32, offset: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !113, file: !109, line: 98, baseType: !71, size: 32, align: 32, offset: 96)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !113, file: !109, line: 102, baseType: !81, size: 32, align: 32, offset: 128)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !113, file: !109, line: 104, baseType: !121, size: 16, align: 16, offset: 160)
!121 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !113, file: !109, line: 105, baseType: !121, size: 16, align: 16, offset: 176)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !113, file: !109, line: 106, baseType: !124, size: 128, align: 64, offset: 192)
!124 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !109, line: 79, baseType: !125)
!125 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !109, line: 75, size: 128, align: 64, elements: !126)
!126 = !{!127, !129}
!127 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !125, file: !109, line: 77, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !125, file: !109, line: 78, baseType: !128, size: 64, align: 64, offset: 64)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !110, file: !109, line: 125, baseType: !131, size: 320, align: 8)
!131 = !DICompositeType(tag: DW_TAG_array_type, baseType: !132, size: 320, align: 8, elements: !133)
!132 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!133 = !{!134}
!134 = !DISubrange(count: 40)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !110, file: !109, line: 126, baseType: !136, size: 64, align: 64)
!136 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !67, file: !4, line: 1482, baseType: !138, size: 1024, align: 64, offset: 1408)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !139)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !140)
!140 = !{!141, !142, !143, !145, !150, !151, !159, !160, !161, !167, !168}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !139, file: !4, line: 768, baseType: !63, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !139, file: !4, line: 768, baseType: !65, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !139, file: !4, line: 768, baseType: !144, size: 32, align: 32, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !139, file: !4, line: 768, baseType: !146, size: 64, align: 64, offset: 192)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !147)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DISubroutineType(types: !149)
!149 = !{null, !58}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !139, file: !4, line: 768, baseType: !73, size: 128, align: 64, offset: 256)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !139, file: !4, line: 768, baseType: !152, size: 256, align: 64, offset: 384)
!152 = !DICompositeType(tag: DW_TAG_union_type, scope: !139, file: !4, line: 768, size: 256, align: 64, elements: !153)
!153 = !{!154, !155}
!154 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !152, file: !4, line: 768, baseType: !81, size: 32, align: 32)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !152, file: !4, line: 768, baseType: !156, size: 256, align: 64)
!156 = !DICompositeType(tag: DW_TAG_array_type, baseType: !63, size: 256, align: 64, elements: !157)
!157 = !{!158}
!158 = !DISubrange(count: 4)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !139, file: !4, line: 768, baseType: !58, size: 64, align: 64, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !139, file: !4, line: 768, baseType: !71, size: 32, align: 32, offset: 704)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !139, file: !4, line: 769, baseType: !162, size: 64, align: 64, offset: 768)
!162 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !163)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DISubroutineType(types: !165)
!165 = !{null, !166}
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !139, file: !4, line: 769, baseType: !73, size: 128, align: 64, offset: 832)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !139, file: !4, line: 769, baseType: !81, size: 32, align: 32, offset: 960)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !67, file: !4, line: 1482, baseType: !170, size: 448, align: 64, offset: 2432)
!170 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !88, line: 130, baseType: !171)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !109, line: 213, baseType: !172)
!172 = !DICompositeType(tag: DW_TAG_union_type, file: !109, line: 173, size: 448, align: 64, elements: !173)
!173 = !{!174, !188, !192}
!174 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !172, file: !109, line: 192, baseType: !175, size: 448, align: 64)
!175 = !DICompositeType(tag: DW_TAG_structure_type, scope: !172, file: !109, line: 176, size: 448, align: 64, elements: !176)
!176 = !{!177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187}
!177 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !175, file: !109, line: 178, baseType: !81, size: 32, align: 32)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !175, file: !109, line: 179, baseType: !71, size: 32, align: 32, offset: 32)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !175, file: !109, line: 180, baseType: !71, size: 32, align: 32, offset: 64)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !175, file: !109, line: 181, baseType: !71, size: 32, align: 32, offset: 96)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !175, file: !109, line: 182, baseType: !71, size: 32, align: 32, offset: 128)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !175, file: !109, line: 183, baseType: !71, size: 32, align: 32, offset: 160)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !175, file: !109, line: 184, baseType: !81, size: 32, align: 32, offset: 192)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !175, file: !109, line: 185, baseType: !81, size: 32, align: 32, offset: 224)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !175, file: !109, line: 186, baseType: !79, size: 64, align: 64, offset: 256)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !175, file: !109, line: 187, baseType: !79, size: 64, align: 64, offset: 320)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !175, file: !109, line: 190, baseType: !71, size: 32, align: 32, offset: 384)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !172, file: !109, line: 211, baseType: !189, size: 448, align: 8)
!189 = !DICompositeType(tag: DW_TAG_array_type, baseType: !132, size: 448, align: 8, elements: !190)
!190 = !{!191}
!191 = !DISubrange(count: 56)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !172, file: !109, line: 212, baseType: !136, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !67, file: !4, line: 1482, baseType: !58, size: 64, align: 64, offset: 2880)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 2944)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 3072)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 3200)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 3328)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !67, file: !4, line: 1482, baseType: !73, size: 128, align: 64, offset: 3456)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !67, file: !4, line: 1482, baseType: !200, size: 64, align: 64, offset: 3584)
!200 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !201, size: 64, align: 64)
!201 = !DISubroutineType(types: !202)
!202 = !{null}
!203 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !67, file: !4, line: 1482, baseType: !87, size: 448, align: 64, offset: 3648)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !67, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 4096)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !67, file: !4, line: 1482, baseType: !206, size: 128, align: 64, offset: 4160)
!206 = !DICompositeType(tag: DW_TAG_structure_type, scope: !67, file: !4, line: 1482, size: 128, align: 64, elements: !207)
!207 = !{!208, !209}
!208 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !206, file: !4, line: 1482, baseType: !63, size: 64, align: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !206, file: !4, line: 1482, baseType: !71, size: 32, align: 32, offset: 64)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !67, file: !4, line: 1482, baseType: !211, size: 64, align: 64, offset: 4288)
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !212, line: 55, baseType: !79)
!212 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!213 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !67, file: !4, line: 1482, baseType: !211, size: 64, align: 64, offset: 4352)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !67, file: !4, line: 1482, baseType: !215, size: 64, align: 32, offset: 4416)
!215 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 64, align: 32, elements: !74)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !67, file: !4, line: 1482, baseType: !87, size: 448, align: 64, offset: 4480)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !67, file: !4, line: 1482, baseType: !218, size: 1216, align: 64, offset: 4928)
!218 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !219)
!219 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !220)
!220 = !{!221, !222, !223, !224, !225, !226, !231, !232, !233, !239, !240, !248, !249}
!221 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !219, file: !4, line: 1326, baseType: !63, size: 64, align: 64)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !219, file: !4, line: 1326, baseType: !65, size: 64, align: 64, offset: 64)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !219, file: !4, line: 1326, baseType: !144, size: 32, align: 32, offset: 128)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !219, file: !4, line: 1326, baseType: !146, size: 64, align: 64, offset: 192)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !219, file: !4, line: 1326, baseType: !73, size: 128, align: 64, offset: 256)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !219, file: !4, line: 1326, baseType: !227, size: 256, align: 64, offset: 384)
!227 = !DICompositeType(tag: DW_TAG_union_type, scope: !219, file: !4, line: 1326, size: 256, align: 64, elements: !228)
!228 = !{!229, !230}
!229 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !227, file: !4, line: 1326, baseType: !81, size: 32, align: 32)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !227, file: !4, line: 1326, baseType: !156, size: 256, align: 64)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !219, file: !4, line: 1326, baseType: !58, size: 64, align: 64, offset: 640)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !219, file: !4, line: 1326, baseType: !71, size: 32, align: 32, offset: 704)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !219, file: !4, line: 1327, baseType: !234, size: 64, align: 64, offset: 768)
!234 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !235)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DISubroutineType(types: !237)
!237 = !{null, !238, !81}
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !219, file: !4, line: 1328, baseType: !81, size: 32, align: 32, offset: 832)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !219, file: !4, line: 1329, baseType: !241, size: 256, align: 64, offset: 896)
!241 = !DICompositeType(tag: DW_TAG_structure_type, scope: !219, file: !4, line: 1329, size: 256, align: 64, elements: !242)
!242 = !{!243, !245, !246, !247}
!243 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !241, file: !4, line: 1329, baseType: !244, size: 64, align: 64)
!244 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !241, file: !4, line: 1329, baseType: !244, size: 64, align: 64, offset: 64)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !241, file: !4, line: 1329, baseType: !244, size: 64, align: 64, offset: 128)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !241, file: !4, line: 1329, baseType: !81, size: 32, align: 32, offset: 192)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !219, file: !4, line: 1329, baseType: !71, size: 32, align: 32, offset: 1152)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !219, file: !4, line: 1329, baseType: !71, size: 32, align: 32, offset: 1184)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !67, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 6144)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !67, file: !4, line: 1482, baseType: !87, size: 448, align: 64, offset: 6208)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !67, file: !4, line: 1482, baseType: !63, size: 64, align: 64, offset: 6656)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !67, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 6720)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !60, file: !4, line: 426, baseType: !144, size: 32, align: 32, offset: 128)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !60, file: !4, line: 426, baseType: !146, size: 64, align: 64, offset: 192)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !60, file: !4, line: 426, baseType: !73, size: 128, align: 64, offset: 256)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !60, file: !4, line: 426, baseType: !258, size: 256, align: 64, offset: 384)
!258 = !DICompositeType(tag: DW_TAG_union_type, scope: !60, file: !4, line: 426, size: 256, align: 64, elements: !259)
!259 = !{!260, !261}
!260 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !258, file: !4, line: 426, baseType: !81, size: 32, align: 32)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !258, file: !4, line: 426, baseType: !156, size: 256, align: 64)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !60, file: !4, line: 426, baseType: !58, size: 64, align: 64, offset: 640)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !60, file: !4, line: 426, baseType: !71, size: 32, align: 32, offset: 704)
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !266, size: 64, align: 64)
!266 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !267, line: 21, baseType: !73)
!267 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_poll_t", file: !4, line: 211, baseType: !270)
!270 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_poll_s", file: !4, line: 717, size: 1280, align: 64, elements: !271)
!271 = !{!272, !273, !274, !275, !276, !277, !282, !283, !284, !289}
!272 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !270, file: !4, line: 718, baseType: !63, size: 64, align: 64)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !270, file: !4, line: 718, baseType: !65, size: 64, align: 64, offset: 64)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !270, file: !4, line: 718, baseType: !144, size: 32, align: 32, offset: 128)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !270, file: !4, line: 718, baseType: !146, size: 64, align: 64, offset: 192)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !270, file: !4, line: 718, baseType: !73, size: 128, align: 64, offset: 256)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !270, file: !4, line: 718, baseType: !278, size: 256, align: 64, offset: 384)
!278 = !DICompositeType(tag: DW_TAG_union_type, scope: !270, file: !4, line: 718, size: 256, align: 64, elements: !279)
!279 = !{!280, !281}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !278, file: !4, line: 718, baseType: !81, size: 32, align: 32)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !278, file: !4, line: 718, baseType: !156, size: 256, align: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !270, file: !4, line: 718, baseType: !58, size: 64, align: 64, offset: 640)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !270, file: !4, line: 718, baseType: !71, size: 32, align: 32, offset: 704)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "poll_cb", scope: !270, file: !4, line: 719, baseType: !285, size: 64, align: 64, offset: 768)
!285 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_poll_cb", file: !4, line: 307, baseType: !286)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!287 = !DISubroutineType(types: !288)
!288 = !{null, !268, !81, !81}
!289 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !270, file: !4, line: 720, baseType: !87, size: 448, align: 64, offset: 832)
!290 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!291 = !{!292, !296, !300, !303, !306, !309, !312}
!292 = distinct !DISubprogram(name: "uv_poll_init", scope: !1, file: !1, line: 55, type: !293, isLocal: false, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!293 = !DISubroutineType(types: !294)
!294 = !{!81, !65, !268, !81}
!295 = !{}
!296 = distinct !DISubprogram(name: "uv_poll_init_socket", scope: !1, file: !1, line: 80, type: !297, isLocal: false, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!297 = !DISubroutineType(types: !298)
!298 = !{!81, !65, !268, !299}
!299 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_os_sock_t", file: !88, line: 122, baseType: !81)
!300 = distinct !DISubprogram(name: "uv_poll_stop", scope: !1, file: !1, line: 94, type: !301, isLocal: false, isDefinition: true, scopeLine: 94, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!301 = !DISubroutineType(types: !302)
!302 = !{!81, !268}
!303 = distinct !DISubprogram(name: "uv_poll_start", scope: !1, file: !1, line: 101, type: !304, isLocal: false, isDefinition: true, scopeLine: 101, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!304 = !DISubroutineType(types: !305)
!305 = !{!81, !268, !81, !285}
!306 = distinct !DISubprogram(name: "uv__poll_close", scope: !1, file: !1, line: 128, type: !307, isLocal: false, isDefinition: true, scopeLine: 128, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!307 = !DISubroutineType(types: !308)
!308 = !{null, !268}
!309 = distinct !DISubprogram(name: "uv__poll_io", scope: !1, file: !1, line: 30, type: !310, isLocal: true, isDefinition: true, scopeLine: 30, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!310 = !DISubroutineType(types: !311)
!311 = !{null, !65, !86, !71}
!312 = distinct !DISubprogram(name: "uv__poll_stop", scope: !1, file: !1, line: 86, type: !307, isLocal: true, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !295)
!313 = !{i32 2, !"Dwarf Version", i32 4}
!314 = !{i32 2, !"Debug Info Version", i32 3}
!315 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!316 = !DILocalVariable(name: "loop", arg: 1, scope: !292, file: !1, line: 55, type: !65)
!317 = !DIExpression()
!318 = !DILocation(line: 55, column: 29, scope: !292)
!319 = !DILocalVariable(name: "handle", arg: 2, scope: !292, file: !1, line: 55, type: !268)
!320 = !DILocation(line: 55, column: 46, scope: !292)
!321 = !DILocalVariable(name: "fd", arg: 3, scope: !292, file: !1, line: 55, type: !81)
!322 = !DILocation(line: 55, column: 58, scope: !292)
!323 = !DILocalVariable(name: "err", scope: !292, file: !1, line: 56, type: !81)
!324 = !DILocation(line: 56, column: 7, scope: !292)
!325 = !DILocation(line: 58, column: 25, scope: !292)
!326 = !DILocation(line: 58, column: 31, scope: !292)
!327 = !DILocation(line: 58, column: 9, scope: !292)
!328 = !DILocation(line: 58, column: 7, scope: !292)
!329 = !DILocation(line: 59, column: 7, scope: !330)
!330 = distinct !DILexicalBlock(scope: !292, file: !1, line: 59, column: 7)
!331 = !DILocation(line: 59, column: 7, scope: !292)
!332 = !DILocation(line: 60, column: 12, scope: !330)
!333 = !DILocation(line: 60, column: 5, scope: !330)
!334 = !DILocation(line: 65, column: 22, scope: !292)
!335 = !DILocation(line: 65, column: 9, scope: !292)
!336 = !DILocation(line: 65, column: 7, scope: !292)
!337 = !DILocation(line: 66, column: 7, scope: !338)
!338 = distinct !DILexicalBlock(scope: !292, file: !1, line: 66, column: 7)
!339 = !DILocation(line: 66, column: 11, scope: !338)
!340 = !DILocation(line: 66, column: 7, scope: !292)
!341 = !DILocation(line: 68, column: 32, scope: !342)
!342 = distinct !DILexicalBlock(scope: !338, file: !1, line: 67, column: 9)
!343 = !DILocation(line: 68, column: 13, scope: !342)
!344 = !DILocation(line: 68, column: 11, scope: !342)
!345 = !DILocation(line: 67, column: 25, scope: !342)
!346 = !DILocation(line: 70, column: 7, scope: !347)
!347 = distinct !DILexicalBlock(scope: !292, file: !1, line: 70, column: 7)
!348 = !DILocation(line: 70, column: 7, scope: !292)
!349 = !DILocation(line: 71, column: 12, scope: !347)
!350 = !DILocation(line: 71, column: 5, scope: !347)
!351 = !DILocation(line: 73, column: 3, scope: !292)
!352 = !DILocation(line: 73, column: 3, scope: !353)
!353 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 1)
!354 = distinct !DILexicalBlock(scope: !292, file: !1, line: 73, column: 3)
!355 = !DILocation(line: 73, column: 3, scope: !356)
!356 = !DILexicalBlockFile(scope: !357, file: !1, discriminator: 2)
!357 = distinct !DILexicalBlock(scope: !354, file: !1, line: 73, column: 3)
!358 = !DILocation(line: 73, column: 3, scope: !359)
!359 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 3)
!360 = !DILocation(line: 74, column: 16, scope: !292)
!361 = !DILocation(line: 74, column: 24, scope: !292)
!362 = !DILocation(line: 74, column: 49, scope: !292)
!363 = !DILocation(line: 74, column: 3, scope: !292)
!364 = !DILocation(line: 75, column: 3, scope: !292)
!365 = !DILocation(line: 75, column: 11, scope: !292)
!366 = !DILocation(line: 75, column: 19, scope: !292)
!367 = !DILocation(line: 76, column: 3, scope: !292)
!368 = !DILocation(line: 77, column: 1, scope: !292)
!369 = !DILocalVariable(name: "loop", arg: 1, scope: !309, file: !1, line: 30, type: !65)
!370 = !DILocation(line: 30, column: 36, scope: !309)
!371 = !DILocalVariable(name: "w", arg: 2, scope: !309, file: !1, line: 30, type: !86)
!372 = !DILocation(line: 30, column: 52, scope: !309)
!373 = !DILocalVariable(name: "events", arg: 3, scope: !309, file: !1, line: 30, type: !71)
!374 = !DILocation(line: 30, column: 68, scope: !309)
!375 = !DILocalVariable(name: "handle", scope: !309, file: !1, line: 31, type: !268)
!376 = !DILocation(line: 31, column: 14, scope: !309)
!377 = !DILocalVariable(name: "pevents", scope: !309, file: !1, line: 32, type: !81)
!378 = !DILocation(line: 32, column: 7, scope: !309)
!379 = !DILocation(line: 34, column: 12, scope: !309)
!380 = !DILocation(line: 34, column: 10, scope: !309)
!381 = !DILocation(line: 36, column: 7, scope: !382)
!382 = distinct !DILexicalBlock(scope: !309, file: !1, line: 36, column: 7)
!383 = !DILocation(line: 36, column: 14, scope: !382)
!384 = !DILocation(line: 36, column: 7, scope: !309)
!385 = !DILocation(line: 37, column: 17, scope: !386)
!386 = distinct !DILexicalBlock(scope: !382, file: !1, line: 36, column: 25)
!387 = !DILocation(line: 37, column: 23, scope: !386)
!388 = !DILocation(line: 37, column: 5, scope: !386)
!389 = !DILocation(line: 38, column: 5, scope: !386)
!390 = !DILocation(line: 38, column: 5, scope: !391)
!391 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 1)
!392 = distinct !DILexicalBlock(scope: !386, file: !1, line: 38, column: 5)
!393 = !DILocation(line: 38, column: 5, scope: !394)
!394 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 2)
!395 = !DILocation(line: 38, column: 5, scope: !396)
!396 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 3)
!397 = !DILocation(line: 38, column: 5, scope: !398)
!398 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 4)
!399 = !DILocation(line: 38, column: 5, scope: !400)
!400 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 5)
!401 = distinct !DILexicalBlock(scope: !392, file: !1, line: 38, column: 5)
!402 = !DILocation(line: 38, column: 5, scope: !403)
!403 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 6)
!404 = !DILocation(line: 38, column: 5, scope: !405)
!405 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 7)
!406 = !DILocation(line: 38, column: 5, scope: !407)
!407 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 8)
!408 = distinct !DILexicalBlock(scope: !392, file: !1, line: 38, column: 5)
!409 = !DILocation(line: 38, column: 5, scope: !410)
!410 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 9)
!411 = distinct !DILexicalBlock(scope: !408, file: !1, line: 38, column: 5)
!412 = !DILocation(line: 38, column: 5, scope: !413)
!413 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 10)
!414 = !DILocation(line: 38, column: 5, scope: !415)
!415 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 11)
!416 = !DILocation(line: 39, column: 5, scope: !386)
!417 = !DILocation(line: 39, column: 13, scope: !386)
!418 = !DILocation(line: 39, column: 21, scope: !386)
!419 = !DILocation(line: 40, column: 5, scope: !386)
!420 = !DILocation(line: 43, column: 11, scope: !309)
!421 = !DILocation(line: 44, column: 7, scope: !422)
!422 = distinct !DILexicalBlock(scope: !309, file: !1, line: 44, column: 7)
!423 = !DILocation(line: 44, column: 14, scope: !422)
!424 = !DILocation(line: 44, column: 7, scope: !309)
!425 = !DILocation(line: 45, column: 13, scope: !422)
!426 = !DILocation(line: 45, column: 5, scope: !422)
!427 = !DILocation(line: 46, column: 7, scope: !428)
!428 = distinct !DILexicalBlock(scope: !309, file: !1, line: 46, column: 7)
!429 = !DILocation(line: 46, column: 14, scope: !428)
!430 = !DILocation(line: 46, column: 7, scope: !309)
!431 = !DILocation(line: 47, column: 13, scope: !428)
!432 = !DILocation(line: 47, column: 5, scope: !428)
!433 = !DILocation(line: 48, column: 7, scope: !434)
!434 = distinct !DILexicalBlock(scope: !309, file: !1, line: 48, column: 7)
!435 = !DILocation(line: 48, column: 14, scope: !434)
!436 = !DILocation(line: 48, column: 7, scope: !309)
!437 = !DILocation(line: 49, column: 13, scope: !434)
!438 = !DILocation(line: 49, column: 5, scope: !434)
!439 = !DILocation(line: 51, column: 3, scope: !309)
!440 = !DILocation(line: 51, column: 11, scope: !309)
!441 = !DILocation(line: 51, column: 19, scope: !309)
!442 = !DILocation(line: 51, column: 30, scope: !309)
!443 = !DILocation(line: 52, column: 1, scope: !309)
!444 = !DILocation(line: 52, column: 1, scope: !445)
!445 = !DILexicalBlockFile(scope: !309, file: !1, discriminator: 1)
!446 = !DILocalVariable(name: "loop", arg: 1, scope: !296, file: !1, line: 80, type: !65)
!447 = !DILocation(line: 80, column: 36, scope: !296)
!448 = !DILocalVariable(name: "handle", arg: 2, scope: !296, file: !1, line: 80, type: !268)
!449 = !DILocation(line: 80, column: 53, scope: !296)
!450 = !DILocalVariable(name: "socket", arg: 3, scope: !296, file: !1, line: 81, type: !299)
!451 = !DILocation(line: 81, column: 18, scope: !296)
!452 = !DILocation(line: 82, column: 23, scope: !296)
!453 = !DILocation(line: 82, column: 29, scope: !296)
!454 = !DILocation(line: 82, column: 37, scope: !296)
!455 = !DILocation(line: 82, column: 10, scope: !296)
!456 = !DILocation(line: 82, column: 3, scope: !296)
!457 = !DILocalVariable(name: "handle", arg: 1, scope: !300, file: !1, line: 94, type: !268)
!458 = !DILocation(line: 94, column: 29, scope: !300)
!459 = !DILocation(line: 95, column: 3, scope: !300)
!460 = !DILocation(line: 95, column: 3, scope: !461)
!461 = !DILexicalBlockFile(scope: !300, file: !1, discriminator: 1)
!462 = !DILocation(line: 95, column: 3, scope: !463)
!463 = !DILexicalBlockFile(scope: !300, file: !1, discriminator: 2)
!464 = !DILocation(line: 95, column: 3, scope: !465)
!465 = !DILexicalBlockFile(scope: !300, file: !1, discriminator: 3)
!466 = !DILocation(line: 96, column: 17, scope: !300)
!467 = !DILocation(line: 96, column: 3, scope: !300)
!468 = !DILocation(line: 97, column: 3, scope: !300)
!469 = !DILocalVariable(name: "handle", arg: 1, scope: !312, file: !1, line: 86, type: !268)
!470 = !DILocation(line: 86, column: 38, scope: !312)
!471 = !DILocation(line: 87, column: 15, scope: !312)
!472 = !DILocation(line: 87, column: 23, scope: !312)
!473 = !DILocation(line: 88, column: 16, scope: !312)
!474 = !DILocation(line: 88, column: 24, scope: !312)
!475 = !DILocation(line: 87, column: 3, scope: !312)
!476 = !DILocation(line: 90, column: 3, scope: !312)
!477 = !DILocation(line: 90, column: 3, scope: !478)
!478 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 1)
!479 = distinct !DILexicalBlock(scope: !312, file: !1, line: 90, column: 3)
!480 = !DILocation(line: 90, column: 3, scope: !481)
!481 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 2)
!482 = !DILocation(line: 90, column: 3, scope: !483)
!483 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 3)
!484 = !DILocation(line: 90, column: 3, scope: !485)
!485 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 4)
!486 = !DILocation(line: 90, column: 3, scope: !487)
!487 = !DILexicalBlockFile(scope: !488, file: !1, discriminator: 5)
!488 = distinct !DILexicalBlock(scope: !479, file: !1, line: 90, column: 3)
!489 = !DILocation(line: 90, column: 3, scope: !490)
!490 = !DILexicalBlockFile(scope: !488, file: !1, discriminator: 6)
!491 = !DILocation(line: 90, column: 3, scope: !492)
!492 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 7)
!493 = !DILocation(line: 90, column: 3, scope: !494)
!494 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 8)
!495 = distinct !DILexicalBlock(scope: !479, file: !1, line: 90, column: 3)
!496 = !DILocation(line: 90, column: 3, scope: !497)
!497 = !DILexicalBlockFile(scope: !498, file: !1, discriminator: 9)
!498 = distinct !DILexicalBlock(scope: !495, file: !1, line: 90, column: 3)
!499 = !DILocation(line: 90, column: 3, scope: !500)
!500 = !DILexicalBlockFile(scope: !498, file: !1, discriminator: 10)
!501 = !DILocation(line: 90, column: 3, scope: !502)
!502 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 11)
!503 = !DILocation(line: 91, column: 1, scope: !312)
!504 = !DILocalVariable(name: "handle", arg: 1, scope: !303, file: !1, line: 101, type: !268)
!505 = !DILocation(line: 101, column: 30, scope: !303)
!506 = !DILocalVariable(name: "pevents", arg: 2, scope: !303, file: !1, line: 101, type: !81)
!507 = !DILocation(line: 101, column: 42, scope: !303)
!508 = !DILocalVariable(name: "poll_cb", arg: 3, scope: !303, file: !1, line: 101, type: !285)
!509 = !DILocation(line: 101, column: 62, scope: !303)
!510 = !DILocalVariable(name: "events", scope: !303, file: !1, line: 102, type: !81)
!511 = !DILocation(line: 102, column: 7, scope: !303)
!512 = !DILocation(line: 104, column: 3, scope: !303)
!513 = !DILocation(line: 104, column: 3, scope: !514)
!514 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 1)
!515 = !DILocation(line: 104, column: 3, scope: !516)
!516 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 2)
!517 = !DILocation(line: 104, column: 3, scope: !518)
!518 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 3)
!519 = !DILocation(line: 105, column: 3, scope: !303)
!520 = !DILocation(line: 105, column: 3, scope: !514)
!521 = !DILocation(line: 105, column: 3, scope: !516)
!522 = !DILocation(line: 105, column: 3, scope: !518)
!523 = !DILocation(line: 107, column: 17, scope: !303)
!524 = !DILocation(line: 107, column: 3, scope: !303)
!525 = !DILocation(line: 109, column: 7, scope: !526)
!526 = distinct !DILexicalBlock(scope: !303, file: !1, line: 109, column: 7)
!527 = !DILocation(line: 109, column: 15, scope: !526)
!528 = !DILocation(line: 109, column: 7, scope: !303)
!529 = !DILocation(line: 110, column: 5, scope: !526)
!530 = !DILocation(line: 112, column: 10, scope: !303)
!531 = !DILocation(line: 113, column: 7, scope: !532)
!532 = distinct !DILexicalBlock(scope: !303, file: !1, line: 113, column: 7)
!533 = !DILocation(line: 113, column: 15, scope: !532)
!534 = !DILocation(line: 113, column: 7, scope: !303)
!535 = !DILocation(line: 114, column: 12, scope: !532)
!536 = !DILocation(line: 114, column: 5, scope: !532)
!537 = !DILocation(line: 115, column: 7, scope: !538)
!538 = distinct !DILexicalBlock(scope: !303, file: !1, line: 115, column: 7)
!539 = !DILocation(line: 115, column: 15, scope: !538)
!540 = !DILocation(line: 115, column: 7, scope: !303)
!541 = !DILocation(line: 116, column: 12, scope: !538)
!542 = !DILocation(line: 116, column: 5, scope: !538)
!543 = !DILocation(line: 117, column: 7, scope: !544)
!544 = distinct !DILexicalBlock(scope: !303, file: !1, line: 117, column: 7)
!545 = !DILocation(line: 117, column: 15, scope: !544)
!546 = !DILocation(line: 117, column: 7, scope: !303)
!547 = !DILocation(line: 118, column: 12, scope: !544)
!548 = !DILocation(line: 118, column: 5, scope: !544)
!549 = !DILocation(line: 120, column: 16, scope: !303)
!550 = !DILocation(line: 120, column: 24, scope: !303)
!551 = !DILocation(line: 120, column: 31, scope: !303)
!552 = !DILocation(line: 120, column: 39, scope: !303)
!553 = !DILocation(line: 120, column: 51, scope: !303)
!554 = !DILocation(line: 120, column: 3, scope: !303)
!555 = !DILocation(line: 121, column: 3, scope: !303)
!556 = !DILocation(line: 121, column: 3, scope: !557)
!557 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 1)
!558 = distinct !DILexicalBlock(scope: !303, file: !1, line: 121, column: 3)
!559 = !DILocation(line: 121, column: 3, scope: !560)
!560 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 2)
!561 = !DILocation(line: 121, column: 3, scope: !562)
!562 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 3)
!563 = !DILocation(line: 121, column: 3, scope: !564)
!564 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 4)
!565 = !DILocation(line: 121, column: 3, scope: !566)
!566 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 5)
!567 = distinct !DILexicalBlock(scope: !558, file: !1, line: 121, column: 3)
!568 = !DILocation(line: 121, column: 3, scope: !569)
!569 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 6)
!570 = !DILocation(line: 121, column: 3, scope: !571)
!571 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 7)
!572 = !DILocation(line: 121, column: 3, scope: !573)
!573 = !DILexicalBlockFile(scope: !574, file: !1, discriminator: 8)
!574 = distinct !DILexicalBlock(scope: !558, file: !1, line: 121, column: 3)
!575 = !DILocation(line: 121, column: 3, scope: !576)
!576 = !DILexicalBlockFile(scope: !577, file: !1, discriminator: 9)
!577 = distinct !DILexicalBlock(scope: !574, file: !1, line: 121, column: 3)
!578 = !DILocation(line: 121, column: 3, scope: !579)
!579 = !DILexicalBlockFile(scope: !577, file: !1, discriminator: 10)
!580 = !DILocation(line: 121, column: 3, scope: !581)
!581 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 11)
!582 = !DILocation(line: 122, column: 21, scope: !303)
!583 = !DILocation(line: 122, column: 3, scope: !303)
!584 = !DILocation(line: 122, column: 11, scope: !303)
!585 = !DILocation(line: 122, column: 19, scope: !303)
!586 = !DILocation(line: 124, column: 3, scope: !303)
!587 = !DILocation(line: 125, column: 1, scope: !303)
!588 = !DILocalVariable(name: "handle", arg: 1, scope: !306, file: !1, line: 128, type: !268)
!589 = !DILocation(line: 128, column: 32, scope: !306)
!590 = !DILocation(line: 129, column: 17, scope: !306)
!591 = !DILocation(line: 129, column: 3, scope: !306)
!592 = !DILocation(line: 130, column: 1, scope: !306)
