; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/signal.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.uv__signal_tree_s = type { %struct.uv_signal_s* }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.2, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.3, i32, i32 }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.1, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.0 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.anon.1 = type { i8*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%union.anon.2 = type { [4 x i8*] }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32 }
%union.anon = type { [4 x i8*] }
%struct.anon.3 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.__sigset_t = type { [16 x i64] }
%struct.uv__signal_msg_t = type { %struct.uv_signal_s*, i32 }
%struct.sigaction = type { %union.anon.4, %struct.__sigset_t, i32, void ()* }
%union.anon.4 = type { void (i32)* }

@uv__signal_global_init_guard = internal global i32 0, align 4
@.str = private unnamed_addr constant [53 x i8] c"!(((handle)->flags & (UV_CLOSING | UV_CLOSED)) != 0)\00", align 1
@.str.1 = private unnamed_addr constant [70 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/signal.c\00", align 1
@__PRETTY_FUNCTION__.uv_signal_stop = private unnamed_addr constant [34 x i8] c"int uv_signal_stop(uv_signal_t *)\00", align 1
@uv__signal_lock_pipefd = internal global [2 x i32] zeroinitializer, align 4
@.str.2 = private unnamed_addr constant [30 x i8] c"!(handle->flags & UV_CLOSING)\00", align 1
@__PRETTY_FUNCTION__.uv__signal_event = private unnamed_addr constant [61 x i8] c"void uv__signal_event(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@__PRETTY_FUNCTION__.uv__signal_start = private unnamed_addr constant [60 x i8] c"int uv__signal_start(uv_signal_t *, uv_signal_cb, int, int)\00", align 1
@uv__signal_tree = internal global %struct.uv__signal_tree_s zeroinitializer, align 8
@.str.3 = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.4 = private unnamed_addr constant [95 x i8] c"r == sizeof msg || (r == -1 && ((*__errno_location ()) == 11 || (*__errno_location ()) == 11))\00", align 1
@__PRETTY_FUNCTION__.uv__signal_handler = private unnamed_addr constant [29 x i8] c"void uv__signal_handler(int)\00", align 1
@.str.5 = private unnamed_addr constant [25 x i8] c"removed_handle == handle\00", align 1
@__PRETTY_FUNCTION__.uv__signal_stop = private unnamed_addr constant [36 x i8] c"void uv__signal_stop(uv_signal_t *)\00", align 1
@.str.6 = private unnamed_addr constant [9 x i8] c"ret == 0\00", align 1

; Function Attrs: nounwind uwtable
define void @uv__signal_global_once_init() #0 !dbg !276 {
entry:
  call void @uv_once(i32* @uv__signal_global_init_guard, void ()* @uv__signal_global_init), !dbg !364
  ret void, !dbg !365
}

declare void @uv_once(i32*, void ()*) #1

; Function Attrs: nounwind uwtable
define internal void @uv__signal_global_init() #0 !dbg !297 {
entry:
  %0 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 0), align 4, !dbg !366
  %tobool = icmp ne i32 %0, 0, !dbg !366
  br i1 %tobool, label %if.end3, label %if.then, !dbg !368

if.then:                                          ; preds = %entry
  %call = call i32 @pthread_atfork(void ()* null, void ()* null, void ()* @uv__signal_global_reinit) #7, !dbg !369
  %tobool1 = icmp ne i32 %call, 0, !dbg !369
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !371

if.then2:                                         ; preds = %if.then
  call void @abort() #8, !dbg !372
  unreachable, !dbg !372

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !373

if.end3:                                          ; preds = %if.end, %entry
  %call4 = call i32 @uv__make_pipe(i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i32 0, i32 0), i32 0), !dbg !375
  %tobool5 = icmp ne i32 %call4, 0, !dbg !375
  br i1 %tobool5, label %if.then6, label %if.end7, !dbg !377

if.then6:                                         ; preds = %if.end3
  call void @abort() #8, !dbg !378
  unreachable, !dbg !378

if.end7:                                          ; preds = %if.end3
  %call8 = call i32 @uv__signal_unlock(), !dbg !379
  %tobool9 = icmp ne i32 %call8, 0, !dbg !379
  br i1 %tobool9, label %if.then10, label %if.end11, !dbg !381

if.then10:                                        ; preds = %if.end7
  call void @abort() #8, !dbg !382
  unreachable, !dbg !382

if.end11:                                         ; preds = %if.end7
  ret void, !dbg !383
}

; Function Attrs: nounwind uwtable
define i32 @uv__signal_loop_fork(%struct.uv_loop_s* %loop) #0 !dbg !278 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !384, metadata !385), !dbg !386
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !387
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !388
  %signal_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 29, !dbg !389
  call void @uv__io_stop(%struct.uv_loop_s* %0, %struct.uv__io_s* %signal_io_watcher, i32 1), !dbg !390
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !391
  %signal_pipefd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 28, !dbg !392
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd, i64 0, i64 0, !dbg !391
  %3 = load i32, i32* %arrayidx, align 8, !dbg !391
  %call = call i32 @uv__close(i32 %3), !dbg !393
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !394
  %signal_pipefd1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 28, !dbg !395
  %arrayidx2 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd1, i64 0, i64 1, !dbg !394
  %5 = load i32, i32* %arrayidx2, align 4, !dbg !394
  %call3 = call i32 @uv__close(i32 %5), !dbg !396
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !397
  %signal_pipefd4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 28, !dbg !398
  %arrayidx5 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd4, i64 0, i64 0, !dbg !397
  store i32 -1, i32* %arrayidx5, align 8, !dbg !399
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !400
  %signal_pipefd6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 28, !dbg !401
  %arrayidx7 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd6, i64 0, i64 1, !dbg !400
  store i32 -1, i32* %arrayidx7, align 4, !dbg !402
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !403
  %call8 = call i32 @uv__signal_loop_once_init(%struct.uv_loop_s* %8), !dbg !404
  ret i32 %call8, !dbg !405
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

declare void @uv__io_stop(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #1

declare i32 @uv__close(i32) #1

; Function Attrs: nounwind uwtable
define internal i32 @uv__signal_loop_once_init(%struct.uv_loop_s* %loop) #0 !dbg !302 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !406, metadata !385), !dbg !407
  call void @llvm.dbg.declare(metadata i32* %err, metadata !408, metadata !385), !dbg !409
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !410
  %signal_pipefd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 28, !dbg !412
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd, i64 0, i64 0, !dbg !410
  %1 = load i32, i32* %arrayidx, align 8, !dbg !410
  %cmp = icmp ne i32 %1, -1, !dbg !413
  br i1 %cmp, label %if.then, label %if.end, !dbg !414

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !415
  br label %return, !dbg !415

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !416
  %signal_pipefd1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 28, !dbg !417
  %arraydecay = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd1, i32 0, i32 0, !dbg !416
  %call = call i32 @uv__make_pipe(i32* %arraydecay, i32 2048), !dbg !418
  store i32 %call, i32* %err, align 4, !dbg !419
  %3 = load i32, i32* %err, align 4, !dbg !420
  %tobool = icmp ne i32 %3, 0, !dbg !420
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !422

if.then2:                                         ; preds = %if.end
  %4 = load i32, i32* %err, align 4, !dbg !423
  store i32 %4, i32* %retval, align 4, !dbg !424
  br label %return, !dbg !424

if.end3:                                          ; preds = %if.end
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !425
  %signal_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 29, !dbg !426
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !427
  %signal_pipefd4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 28, !dbg !428
  %arrayidx5 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd4, i64 0, i64 0, !dbg !427
  %7 = load i32, i32* %arrayidx5, align 8, !dbg !427
  call void @uv__io_init(%struct.uv__io_s* %signal_io_watcher, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__signal_event, i32 %7), !dbg !429
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !430
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !431
  %signal_io_watcher6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 29, !dbg !432
  call void @uv__io_start(%struct.uv_loop_s* %8, %struct.uv__io_s* %signal_io_watcher6, i32 1), !dbg !433
  store i32 0, i32* %retval, align 4, !dbg !434
  br label %return, !dbg !434

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !435
  ret i32 %10, !dbg !435
}

; Function Attrs: nounwind uwtable
define void @uv__signal_loop_cleanup(%struct.uv_loop_s* %loop) #0 !dbg !281 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  %handle = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !436, metadata !385), !dbg !437
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !438, metadata !385), !dbg !439
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !440
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 2, !dbg !440
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue, i64 0, i64 0, !dbg !440
  %1 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !440
  %2 = load [2 x i8*]*, [2 x i8*]** %1, align 8, !dbg !440
  store [2 x i8*]* %2, [2 x i8*]** %q, align 8, !dbg !440
  br label %for.cond, !dbg !440

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !442
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !442
  %handle_queue1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 2, !dbg !442
  %cmp = icmp ne [2 x i8*]* %3, %handle_queue1, !dbg !442
  br i1 %cmp, label %for.body, label %for.end, !dbg !442

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle, metadata !445, metadata !385), !dbg !447
  %5 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !448
  %6 = bitcast [2 x i8*]* %5 to i8*, !dbg !448
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 -32, !dbg !448
  %7 = bitcast i8* %add.ptr to %struct.uv_handle_s*, !dbg !448
  store %struct.uv_handle_s* %7, %struct.uv_handle_s** %handle, align 8, !dbg !447
  %8 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle, align 8, !dbg !449
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %8, i32 0, i32 2, !dbg !451
  %9 = load i32, i32* %type, align 8, !dbg !451
  %cmp2 = icmp eq i32 %9, 16, !dbg !452
  br i1 %cmp2, label %if.then, label %if.end, !dbg !453

if.then:                                          ; preds = %for.body
  %10 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle, align 8, !dbg !454
  %11 = bitcast %struct.uv_handle_s* %10 to %struct.uv_signal_s*, !dbg !455
  call void @uv__signal_stop(%struct.uv_signal_s* %11), !dbg !456
  br label %if.end, !dbg !456

if.end:                                           ; preds = %if.then, %for.body
  br label %for.inc, !dbg !457

for.inc:                                          ; preds = %if.end
  %12 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !458
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %12, i64 0, i64 0, !dbg !458
  %13 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !458
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !458
  store [2 x i8*]* %14, [2 x i8*]** %q, align 8, !dbg !458
  br label %for.cond, !dbg !458

for.end:                                          ; preds = %for.cond
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !460
  %signal_pipefd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %15, i32 0, i32 28, !dbg !462
  %arrayidx4 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd, i64 0, i64 0, !dbg !460
  %16 = load i32, i32* %arrayidx4, align 8, !dbg !460
  %cmp5 = icmp ne i32 %16, -1, !dbg !463
  br i1 %cmp5, label %if.then6, label %if.end11, !dbg !464

if.then6:                                         ; preds = %for.end
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !465
  %signal_pipefd7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 28, !dbg !467
  %arrayidx8 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd7, i64 0, i64 0, !dbg !465
  %18 = load i32, i32* %arrayidx8, align 8, !dbg !465
  %call = call i32 @uv__close(i32 %18), !dbg !468
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !469
  %signal_pipefd9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %19, i32 0, i32 28, !dbg !470
  %arrayidx10 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd9, i64 0, i64 0, !dbg !469
  store i32 -1, i32* %arrayidx10, align 8, !dbg !471
  br label %if.end11, !dbg !472

if.end11:                                         ; preds = %if.then6, %for.end
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !473
  %signal_pipefd12 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 28, !dbg !475
  %arrayidx13 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd12, i64 0, i64 1, !dbg !473
  %21 = load i32, i32* %arrayidx13, align 4, !dbg !473
  %cmp14 = icmp ne i32 %21, -1, !dbg !476
  br i1 %cmp14, label %if.then15, label %if.end21, !dbg !477

if.then15:                                        ; preds = %if.end11
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !478
  %signal_pipefd16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %22, i32 0, i32 28, !dbg !480
  %arrayidx17 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd16, i64 0, i64 1, !dbg !478
  %23 = load i32, i32* %arrayidx17, align 4, !dbg !478
  %call18 = call i32 @uv__close(i32 %23), !dbg !481
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !482
  %signal_pipefd19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 28, !dbg !483
  %arrayidx20 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd19, i64 0, i64 1, !dbg !482
  store i32 -1, i32* %arrayidx20, align 4, !dbg !484
  br label %if.end21, !dbg !485

if.end21:                                         ; preds = %if.then15, %if.end11
  ret void, !dbg !486
}

; Function Attrs: nounwind uwtable
define internal void @uv__signal_stop(%struct.uv_signal_s* %handle) #0 !dbg !349 {
entry:
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  %removed_handle = alloca %struct.uv_signal_s*, align 8
  %saved_sigmask = alloca %struct.__sigset_t, align 8
  %first_handle = alloca %struct.uv_signal_s*, align 8
  %rem_oneshot = alloca i32, align 4
  %first_oneshot = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !487, metadata !385), !dbg !488
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %removed_handle, metadata !489, metadata !385), !dbg !490
  call void @llvm.dbg.declare(metadata %struct.__sigset_t* %saved_sigmask, metadata !491, metadata !385), !dbg !492
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %first_handle, metadata !493, metadata !385), !dbg !494
  call void @llvm.dbg.declare(metadata i32* %rem_oneshot, metadata !495, metadata !385), !dbg !496
  call void @llvm.dbg.declare(metadata i32* %first_oneshot, metadata !497, metadata !385), !dbg !498
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !499, metadata !385), !dbg !500
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !501
  %signum = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %0, i32 0, i32 9, !dbg !503
  %1 = load i32, i32* %signum, align 8, !dbg !503
  %cmp = icmp eq i32 %1, 0, !dbg !504
  br i1 %cmp, label %if.then, label %if.end, !dbg !505

if.then:                                          ; preds = %entry
  br label %do.end39, !dbg !506

if.end:                                           ; preds = %entry
  call void @uv__signal_block_and_lock(%struct.__sigset_t* %saved_sigmask), !dbg !507
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !508
  %call = call %struct.uv_signal_s* @uv__signal_tree_s_RB_REMOVE(%struct.uv__signal_tree_s* @uv__signal_tree, %struct.uv_signal_s* %2), !dbg !508
  store %struct.uv_signal_s* %call, %struct.uv_signal_s** %removed_handle, align 8, !dbg !509
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %removed_handle, align 8, !dbg !510
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !510
  %cmp1 = icmp eq %struct.uv_signal_s* %3, %4, !dbg !510
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !510

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !511

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 537, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv__signal_stop, i32 0, i32 0)) #8, !dbg !513
  unreachable, !dbg !513
                                                  ; No predecessors!
  br label %cond.end, !dbg !515

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %removed_handle, align 8, !dbg !517
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !518
  %signum2 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %7, i32 0, i32 9, !dbg !519
  %8 = load i32, i32* %signum2, align 8, !dbg !519
  %call3 = call %struct.uv_signal_s* @uv__signal_first_handle(i32 %8), !dbg !520
  store %struct.uv_signal_s* %call3, %struct.uv_signal_s** %first_handle, align 8, !dbg !521
  %9 = load %struct.uv_signal_s*, %struct.uv_signal_s** %first_handle, align 8, !dbg !522
  %cmp4 = icmp eq %struct.uv_signal_s* %9, null, !dbg !524
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !525

if.then5:                                         ; preds = %cond.end
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !526
  %signum6 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %10, i32 0, i32 9, !dbg !528
  %11 = load i32, i32* %signum6, align 8, !dbg !528
  call void @uv__signal_unregister_handler(i32 %11), !dbg !529
  br label %if.end18, !dbg !530

if.else:                                          ; preds = %cond.end
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !531
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %12, i32 0, i32 7, !dbg !533
  %13 = load i32, i32* %flags, align 8, !dbg !533
  %and = and i32 %13, 524288, !dbg !534
  store i32 %and, i32* %rem_oneshot, align 4, !dbg !535
  %14 = load %struct.uv_signal_s*, %struct.uv_signal_s** %first_handle, align 8, !dbg !536
  %flags7 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %14, i32 0, i32 7, !dbg !537
  %15 = load i32, i32* %flags7, align 8, !dbg !537
  %and8 = and i32 %15, 524288, !dbg !538
  store i32 %and8, i32* %first_oneshot, align 4, !dbg !539
  %16 = load i32, i32* %first_oneshot, align 4, !dbg !540
  %tobool = icmp ne i32 %16, 0, !dbg !540
  br i1 %tobool, label %land.lhs.true, label %if.end17, !dbg !542

land.lhs.true:                                    ; preds = %if.else
  %17 = load i32, i32* %rem_oneshot, align 4, !dbg !543
  %tobool9 = icmp ne i32 %17, 0, !dbg !543
  br i1 %tobool9, label %if.end17, label %if.then10, !dbg !545

if.then10:                                        ; preds = %land.lhs.true
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !546
  %signum11 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %18, i32 0, i32 9, !dbg !548
  %19 = load i32, i32* %signum11, align 8, !dbg !548
  %call12 = call i32 @uv__signal_register_handler(i32 %19, i32 1), !dbg !549
  store i32 %call12, i32* %ret, align 4, !dbg !550
  %20 = load i32, i32* %ret, align 4, !dbg !551
  %cmp13 = icmp eq i32 %20, 0, !dbg !551
  br i1 %cmp13, label %cond.true14, label %cond.false15, !dbg !551

cond.true14:                                      ; preds = %if.then10
  br label %cond.end16, !dbg !552

cond.false15:                                     ; preds = %if.then10
  call void @__assert_fail(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 551, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv__signal_stop, i32 0, i32 0)) #8, !dbg !554
  unreachable, !dbg !554
                                                  ; No predecessors!
  br label %cond.end16, !dbg !556

cond.end16:                                       ; preds = %21, %cond.true14
  br label %if.end17, !dbg !558

if.end17:                                         ; preds = %cond.end16, %land.lhs.true, %if.else
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.then5
  call void @uv__signal_unlock_and_unblock(%struct.__sigset_t* %saved_sigmask), !dbg !559
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !560
  %signum19 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 9, !dbg !561
  store i32 0, i32* %signum19, align 8, !dbg !562
  br label %do.body, !dbg !563

do.body:                                          ; preds = %if.end18
  %23 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !564
  %flags20 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %23, i32 0, i32 7, !dbg !564
  %24 = load i32, i32* %flags20, align 8, !dbg !564
  %and21 = and i32 %24, 0, !dbg !564
  %cmp22 = icmp eq i32 %and21, 0, !dbg !564
  br i1 %cmp22, label %cond.true23, label %cond.false24, !dbg !564

cond.true23:                                      ; preds = %do.body
  br label %cond.end25, !dbg !567

cond.false24:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 558, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv__signal_stop, i32 0, i32 0)) #8, !dbg !569
  unreachable, !dbg !569
                                                  ; No predecessors!
  br label %cond.end25, !dbg !571

cond.end25:                                       ; preds = %25, %cond.true23
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !573
  %flags26 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %26, i32 0, i32 7, !dbg !573
  %27 = load i32, i32* %flags26, align 8, !dbg !573
  %and27 = and i32 %27, 16384, !dbg !573
  %cmp28 = icmp eq i32 %and27, 0, !dbg !573
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !573

if.then29:                                        ; preds = %cond.end25
  br label %do.end39, !dbg !576

if.end30:                                         ; preds = %cond.end25
  %28 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !578
  %flags31 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %28, i32 0, i32 7, !dbg !578
  %29 = load i32, i32* %flags31, align 8, !dbg !578
  %and32 = and i32 %29, -16385, !dbg !578
  store i32 %and32, i32* %flags31, align 8, !dbg !578
  %30 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !578
  %flags33 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %30, i32 0, i32 7, !dbg !578
  %31 = load i32, i32* %flags33, align 8, !dbg !578
  %and34 = and i32 %31, 8192, !dbg !578
  %cmp35 = icmp ne i32 %and34, 0, !dbg !578
  br i1 %cmp35, label %if.then36, label %if.end38, !dbg !578

if.then36:                                        ; preds = %if.end30
  br label %do.body37, !dbg !580

do.body37:                                        ; preds = %if.then36
  %32 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !583
  %loop = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %32, i32 0, i32 1, !dbg !583
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !583
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 1, !dbg !583
  %34 = load i32, i32* %active_handles, align 8, !dbg !583
  %dec = add i32 %34, -1, !dbg !583
  store i32 %dec, i32* %active_handles, align 8, !dbg !583
  br label %do.end, !dbg !583

do.end:                                           ; preds = %do.body37
  br label %if.end38, !dbg !586

if.end38:                                         ; preds = %do.end, %if.end30
  br label %do.end39, !dbg !588

do.end39:                                         ; preds = %if.then, %if.end38, %if.then29
  ret void, !dbg !590
}

; Function Attrs: nounwind uwtable
define i32 @uv_signal_init(%struct.uv_loop_s* %loop, %struct.uv_signal_s* %handle) #0 !dbg !284 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !591, metadata !385), !dbg !592
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !593, metadata !385), !dbg !594
  call void @llvm.dbg.declare(metadata i32* %err, metadata !595, metadata !385), !dbg !596
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !597
  %call = call i32 @uv__signal_loop_once_init(%struct.uv_loop_s* %0), !dbg !598
  store i32 %call, i32* %err, align 4, !dbg !599
  %1 = load i32, i32* %err, align 4, !dbg !600
  %tobool = icmp ne i32 %1, 0, !dbg !600
  br i1 %tobool, label %if.then, label %if.end, !dbg !602

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !603
  store i32 %2, i32* %retval, align 4, !dbg !604
  br label %return, !dbg !604

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !605

do.body:                                          ; preds = %if.end
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !606
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !606
  %5 = bitcast %struct.uv_signal_s* %4 to %struct.uv_handle_s*, !dbg !606
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %5, i32 0, i32 1, !dbg !606
  store %struct.uv_loop_s* %3, %struct.uv_loop_s** %loop1, align 8, !dbg !606
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !606
  %7 = bitcast %struct.uv_signal_s* %6 to %struct.uv_handle_s*, !dbg !606
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %7, i32 0, i32 2, !dbg !606
  store i32 16, i32* %type, align 8, !dbg !606
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !606
  %9 = bitcast %struct.uv_signal_s* %8 to %struct.uv_handle_s*, !dbg !606
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 7, !dbg !606
  store i32 8192, i32* %flags, align 8, !dbg !606
  br label %do.body2, !dbg !606

do.body2:                                         ; preds = %do.body
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !609
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 2, !dbg !609
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !609
  %12 = bitcast %struct.uv_signal_s* %11 to %struct.uv_handle_s*, !dbg !609
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %12, i32 0, i32 4, !dbg !609
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !609
  %13 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !609
  store [2 x i8*]* %handle_queue, [2 x i8*]** %13, align 8, !dbg !609
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !609
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 2, !dbg !609
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !609
  %15 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !609
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !609
  %17 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !609
  %18 = bitcast %struct.uv_signal_s* %17 to %struct.uv_handle_s*, !dbg !609
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !609
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !609
  %19 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !609
  store [2 x i8*]* %16, [2 x i8*]** %19, align 8, !dbg !609
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !609
  %21 = bitcast %struct.uv_signal_s* %20 to %struct.uv_handle_s*, !dbg !609
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %21, i32 0, i32 4, !dbg !609
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !609
  %23 = bitcast %struct.uv_signal_s* %22 to %struct.uv_handle_s*, !dbg !609
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %23, i32 0, i32 4, !dbg !609
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !609
  %24 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !609
  %25 = load [2 x i8*]*, [2 x i8*]** %24, align 8, !dbg !609
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %25, i64 0, i64 0, !dbg !609
  %26 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !609
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %26, align 8, !dbg !609
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !609
  %28 = bitcast %struct.uv_signal_s* %27 to %struct.uv_handle_s*, !dbg !609
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %28, i32 0, i32 4, !dbg !609
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !609
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %29, i32 0, i32 2, !dbg !609
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !609
  %30 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !609
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %30, align 8, !dbg !609
  br label %do.end, !dbg !609

do.end:                                           ; preds = %do.body2
  %31 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !612
  %32 = bitcast %struct.uv_signal_s* %31 to %struct.uv_handle_s*, !dbg !612
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %32, i32 0, i32 6, !dbg !612
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !612
  br label %do.end15, !dbg !612

do.end15:                                         ; preds = %do.end
  %33 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !614
  %signum = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %33, i32 0, i32 9, !dbg !615
  store i32 0, i32* %signum, align 8, !dbg !616
  %34 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !617
  %caught_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %34, i32 0, i32 11, !dbg !618
  store i32 0, i32* %caught_signals, align 8, !dbg !619
  %35 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !620
  %dispatched_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %35, i32 0, i32 12, !dbg !621
  store i32 0, i32* %dispatched_signals, align 4, !dbg !622
  store i32 0, i32* %retval, align 4, !dbg !623
  br label %return, !dbg !623

return:                                           ; preds = %do.end15, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !624
  ret i32 %36, !dbg !624
}

; Function Attrs: nounwind uwtable
define void @uv__signal_close(%struct.uv_signal_s* %handle) #0 !dbg !287 {
entry:
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !625, metadata !385), !dbg !626
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !627
  call void @uv__signal_stop(%struct.uv_signal_s* %0), !dbg !628
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !629
  %caught_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %1, i32 0, i32 11, !dbg !631
  %2 = load i32, i32* %caught_signals, align 8, !dbg !631
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !632
  %dispatched_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %3, i32 0, i32 12, !dbg !633
  %4 = load i32, i32* %dispatched_signals, align 4, !dbg !633
  %cmp = icmp eq i32 %2, %4, !dbg !634
  br i1 %cmp, label %if.then, label %if.end, !dbg !635

if.then:                                          ; preds = %entry
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !636
  %6 = bitcast %struct.uv_signal_s* %5 to %struct.uv_handle_s*, !dbg !638
  call void @uv__make_close_pending(%struct.uv_handle_s* %6), !dbg !639
  br label %if.end, !dbg !640

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !641
}

declare void @uv__make_close_pending(%struct.uv_handle_s*) #1

; Function Attrs: nounwind uwtable
define i32 @uv_signal_start(%struct.uv_signal_s* %handle, void (%struct.uv_signal_s*, i32)* %signal_cb, i32 %signum) #0 !dbg !290 {
entry:
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  %signal_cb.addr = alloca void (%struct.uv_signal_s*, i32)*, align 8
  %signum.addr = alloca i32, align 4
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !642, metadata !385), !dbg !643
  store void (%struct.uv_signal_s*, i32)* %signal_cb, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_signal_s*, i32)** %signal_cb.addr, metadata !644, metadata !385), !dbg !645
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !646, metadata !385), !dbg !647
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !648
  %1 = load void (%struct.uv_signal_s*, i32)*, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8, !dbg !649
  %2 = load i32, i32* %signum.addr, align 4, !dbg !650
  %call = call i32 @uv__signal_start(%struct.uv_signal_s* %0, void (%struct.uv_signal_s*, i32)* %1, i32 %2, i32 0), !dbg !651
  ret i32 %call, !dbg !652
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__signal_start(%struct.uv_signal_s* %handle, void (%struct.uv_signal_s*, i32)* %signal_cb, i32 %signum, i32 %oneshot) #0 !dbg !306 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  %signal_cb.addr = alloca void (%struct.uv_signal_s*, i32)*, align 8
  %signum.addr = alloca i32, align 4
  %oneshot.addr = alloca i32, align 4
  %saved_sigmask = alloca %struct.__sigset_t, align 8
  %err = alloca i32, align 4
  %first_handle = alloca %struct.uv_signal_s*, align 8
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !653, metadata !385), !dbg !654
  store void (%struct.uv_signal_s*, i32)* %signal_cb, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_signal_s*, i32)** %signal_cb.addr, metadata !655, metadata !385), !dbg !656
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !657, metadata !385), !dbg !658
  store i32 %oneshot, i32* %oneshot.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %oneshot.addr, metadata !659, metadata !385), !dbg !660
  call void @llvm.dbg.declare(metadata %struct.__sigset_t* %saved_sigmask, metadata !661, metadata !385), !dbg !662
  call void @llvm.dbg.declare(metadata i32* %err, metadata !663, metadata !385), !dbg !664
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %first_handle, metadata !665, metadata !385), !dbg !666
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !667
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %0, i32 0, i32 7, !dbg !667
  %1 = load i32, i32* %flags, align 8, !dbg !667
  %and = and i32 %1, 3, !dbg !667
  %cmp = icmp ne i32 %and, 0, !dbg !667
  br i1 %cmp, label %cond.false, label %cond.true, !dbg !667

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !668

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 353, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @__PRETTY_FUNCTION__.uv__signal_start, i32 0, i32 0)) #8, !dbg !670
  unreachable, !dbg !670
                                                  ; No predecessors!
  br label %cond.end, !dbg !672

cond.end:                                         ; preds = %2, %cond.true
  %3 = load i32, i32* %signum.addr, align 4, !dbg !674
  %cmp1 = icmp eq i32 %3, 0, !dbg !676
  br i1 %cmp1, label %if.then, label %if.end, !dbg !677

if.then:                                          ; preds = %cond.end
  store i32 -22, i32* %retval, align 4, !dbg !678
  br label %return, !dbg !678

if.end:                                           ; preds = %cond.end
  %4 = load i32, i32* %signum.addr, align 4, !dbg !679
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !681
  %signum2 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %5, i32 0, i32 9, !dbg !682
  %6 = load i32, i32* %signum2, align 8, !dbg !682
  %cmp3 = icmp eq i32 %4, %6, !dbg !683
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !684

if.then4:                                         ; preds = %if.end
  %7 = load void (%struct.uv_signal_s*, i32)*, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8, !dbg !685
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !687
  %signal_cb5 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %8, i32 0, i32 8, !dbg !688
  store void (%struct.uv_signal_s*, i32)* %7, void (%struct.uv_signal_s*, i32)** %signal_cb5, align 8, !dbg !689
  store i32 0, i32* %retval, align 4, !dbg !690
  br label %return, !dbg !690

if.end6:                                          ; preds = %if.end
  %9 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !691
  %signum7 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %9, i32 0, i32 9, !dbg !693
  %10 = load i32, i32* %signum7, align 8, !dbg !693
  %cmp8 = icmp ne i32 %10, 0, !dbg !694
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !695

if.then9:                                         ; preds = %if.end6
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !696
  call void @uv__signal_stop(%struct.uv_signal_s* %11), !dbg !698
  br label %if.end10, !dbg !699

if.end10:                                         ; preds = %if.then9, %if.end6
  call void @uv__signal_block_and_lock(%struct.__sigset_t* %saved_sigmask), !dbg !700
  %12 = load i32, i32* %signum.addr, align 4, !dbg !701
  %call = call %struct.uv_signal_s* @uv__signal_first_handle(i32 %12), !dbg !702
  store %struct.uv_signal_s* %call, %struct.uv_signal_s** %first_handle, align 8, !dbg !703
  %13 = load %struct.uv_signal_s*, %struct.uv_signal_s** %first_handle, align 8, !dbg !704
  %cmp11 = icmp eq %struct.uv_signal_s* %13, null, !dbg !706
  br i1 %cmp11, label %if.then15, label %lor.lhs.false, !dbg !707

lor.lhs.false:                                    ; preds = %if.end10
  %14 = load i32, i32* %oneshot.addr, align 4, !dbg !708
  %tobool = icmp ne i32 %14, 0, !dbg !708
  br i1 %tobool, label %if.end20, label %land.lhs.true, !dbg !709

land.lhs.true:                                    ; preds = %lor.lhs.false
  %15 = load %struct.uv_signal_s*, %struct.uv_signal_s** %first_handle, align 8, !dbg !710
  %flags12 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %15, i32 0, i32 7, !dbg !712
  %16 = load i32, i32* %flags12, align 8, !dbg !712
  %and13 = and i32 %16, 524288, !dbg !713
  %tobool14 = icmp ne i32 %and13, 0, !dbg !713
  br i1 %tobool14, label %if.then15, label %if.end20, !dbg !714

if.then15:                                        ; preds = %land.lhs.true, %if.end10
  %17 = load i32, i32* %signum.addr, align 4, !dbg !715
  %18 = load i32, i32* %oneshot.addr, align 4, !dbg !717
  %call16 = call i32 @uv__signal_register_handler(i32 %17, i32 %18), !dbg !718
  store i32 %call16, i32* %err, align 4, !dbg !719
  %19 = load i32, i32* %err, align 4, !dbg !720
  %tobool17 = icmp ne i32 %19, 0, !dbg !720
  br i1 %tobool17, label %if.then18, label %if.end19, !dbg !722

if.then18:                                        ; preds = %if.then15
  call void @uv__signal_unlock_and_unblock(%struct.__sigset_t* %saved_sigmask), !dbg !723
  %20 = load i32, i32* %err, align 4, !dbg !725
  store i32 %20, i32* %retval, align 4, !dbg !726
  br label %return, !dbg !726

if.end19:                                         ; preds = %if.then15
  br label %if.end20, !dbg !727

if.end20:                                         ; preds = %if.end19, %land.lhs.true, %lor.lhs.false
  %21 = load i32, i32* %signum.addr, align 4, !dbg !728
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !729
  %signum21 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 9, !dbg !730
  store i32 %21, i32* %signum21, align 8, !dbg !731
  %23 = load i32, i32* %oneshot.addr, align 4, !dbg !732
  %tobool22 = icmp ne i32 %23, 0, !dbg !732
  br i1 %tobool22, label %if.then23, label %if.end25, !dbg !734

if.then23:                                        ; preds = %if.end20
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !735
  %flags24 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %24, i32 0, i32 7, !dbg !736
  %25 = load i32, i32* %flags24, align 8, !dbg !737
  %or = or i32 %25, 524288, !dbg !737
  store i32 %or, i32* %flags24, align 8, !dbg !737
  br label %if.end25, !dbg !735

if.end25:                                         ; preds = %if.then23, %if.end20
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !738
  %call26 = call %struct.uv_signal_s* @uv__signal_tree_s_RB_INSERT(%struct.uv__signal_tree_s* @uv__signal_tree, %struct.uv_signal_s* %26), !dbg !738
  call void @uv__signal_unlock_and_unblock(%struct.__sigset_t* %saved_sigmask), !dbg !739
  %27 = load void (%struct.uv_signal_s*, i32)*, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8, !dbg !740
  %28 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !741
  %signal_cb27 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %28, i32 0, i32 8, !dbg !742
  store void (%struct.uv_signal_s*, i32)* %27, void (%struct.uv_signal_s*, i32)** %signal_cb27, align 8, !dbg !743
  br label %do.body, !dbg !744

do.body:                                          ; preds = %if.end25
  %29 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !745
  %flags28 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %29, i32 0, i32 7, !dbg !745
  %30 = load i32, i32* %flags28, align 8, !dbg !745
  %and29 = and i32 %30, 0, !dbg !745
  %cmp30 = icmp eq i32 %and29, 0, !dbg !745
  br i1 %cmp30, label %cond.true31, label %cond.false32, !dbg !745

cond.true31:                                      ; preds = %do.body
  br label %cond.end33, !dbg !748

cond.false32:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 403, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @__PRETTY_FUNCTION__.uv__signal_start, i32 0, i32 0)) #8, !dbg !750
  unreachable, !dbg !750
                                                  ; No predecessors!
  br label %cond.end33, !dbg !752

cond.end33:                                       ; preds = %31, %cond.true31
  %32 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !754
  %flags34 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %32, i32 0, i32 7, !dbg !754
  %33 = load i32, i32* %flags34, align 8, !dbg !754
  %and35 = and i32 %33, 16384, !dbg !754
  %cmp36 = icmp ne i32 %and35, 0, !dbg !754
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !754

if.then37:                                        ; preds = %cond.end33
  br label %do.end47, !dbg !757

if.end38:                                         ; preds = %cond.end33
  %34 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !759
  %flags39 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %34, i32 0, i32 7, !dbg !759
  %35 = load i32, i32* %flags39, align 8, !dbg !759
  %or40 = or i32 %35, 16384, !dbg !759
  store i32 %or40, i32* %flags39, align 8, !dbg !759
  %36 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !759
  %flags41 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %36, i32 0, i32 7, !dbg !759
  %37 = load i32, i32* %flags41, align 8, !dbg !759
  %and42 = and i32 %37, 8192, !dbg !759
  %cmp43 = icmp ne i32 %and42, 0, !dbg !759
  br i1 %cmp43, label %if.then44, label %if.end46, !dbg !759

if.then44:                                        ; preds = %if.end38
  br label %do.body45, !dbg !761

do.body45:                                        ; preds = %if.then44
  %38 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !764
  %loop = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %38, i32 0, i32 1, !dbg !764
  %39 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !764
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %39, i32 0, i32 1, !dbg !764
  %40 = load i32, i32* %active_handles, align 8, !dbg !764
  %inc = add i32 %40, 1, !dbg !764
  store i32 %inc, i32* %active_handles, align 8, !dbg !764
  br label %do.end, !dbg !764

do.end:                                           ; preds = %do.body45
  br label %if.end46, !dbg !767

if.end46:                                         ; preds = %do.end, %if.end38
  br label %do.end47, !dbg !769

do.end47:                                         ; preds = %if.end46, %if.then37
  store i32 0, i32* %retval, align 4, !dbg !771
  br label %return, !dbg !771

return:                                           ; preds = %do.end47, %if.then18, %if.then4, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !772
  ret i32 %41, !dbg !772
}

; Function Attrs: nounwind uwtable
define i32 @uv_signal_start_oneshot(%struct.uv_signal_s* %handle, void (%struct.uv_signal_s*, i32)* %signal_cb, i32 %signum) #0 !dbg !293 {
entry:
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  %signal_cb.addr = alloca void (%struct.uv_signal_s*, i32)*, align 8
  %signum.addr = alloca i32, align 4
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !773, metadata !385), !dbg !774
  store void (%struct.uv_signal_s*, i32)* %signal_cb, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_signal_s*, i32)** %signal_cb.addr, metadata !775, metadata !385), !dbg !776
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !777, metadata !385), !dbg !778
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !779
  %1 = load void (%struct.uv_signal_s*, i32)*, void (%struct.uv_signal_s*, i32)** %signal_cb.addr, align 8, !dbg !780
  %2 = load i32, i32* %signum.addr, align 4, !dbg !781
  %call = call i32 @uv__signal_start(%struct.uv_signal_s* %0, void (%struct.uv_signal_s*, i32)* %1, i32 %2, i32 1), !dbg !782
  ret i32 %call, !dbg !783
}

; Function Attrs: nounwind uwtable
define i32 @uv_signal_stop(%struct.uv_signal_s* %handle) #0 !dbg !294 {
entry:
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !784, metadata !385), !dbg !785
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !786
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %0, i32 0, i32 7, !dbg !786
  %1 = load i32, i32* %flags, align 8, !dbg !786
  %and = and i32 %1, 3, !dbg !786
  %cmp = icmp ne i32 %and, 0, !dbg !786
  br i1 %cmp, label %cond.false, label %cond.true, !dbg !786

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !787

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 516, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @__PRETTY_FUNCTION__.uv_signal_stop, i32 0, i32 0)) #8, !dbg !789
  unreachable, !dbg !789
                                                  ; No predecessors!
  br label %cond.end, !dbg !791

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !793
  call void @uv__signal_stop(%struct.uv_signal_s* %3), !dbg !794
  ret i32 0, !dbg !795
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind
declare i32 @pthread_atfork(void ()*, void ()*, void ()*) #4

; Function Attrs: nounwind uwtable
define internal void @uv__signal_global_reinit() #0 !dbg !298 {
entry:
  %0 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 0), align 4, !dbg !796
  %call = call i32 @uv__close(i32 %0), !dbg !797
  store i32 -1, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 0), align 4, !dbg !798
  %1 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 1), align 4, !dbg !799
  %call1 = call i32 @uv__close(i32 %1), !dbg !800
  store i32 -1, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 1), align 4, !dbg !801
  call void @uv__signal_global_init(), !dbg !802
  ret void, !dbg !803
}

; Function Attrs: noreturn nounwind
declare void @abort() #3

declare i32 @uv__make_pipe(i32*, i32) #1

; Function Attrs: nounwind uwtable
define internal i32 @uv__signal_unlock() #0 !dbg !299 {
entry:
  %r = alloca i32, align 4
  %data = alloca i8, align 1
  call void @llvm.dbg.declare(metadata i32* %r, metadata !804, metadata !385), !dbg !805
  call void @llvm.dbg.declare(metadata i8* %data, metadata !806, metadata !385), !dbg !807
  store i8 42, i8* %data, align 1, !dbg !807
  br label %do.body, !dbg !808

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 1), align 4, !dbg !809
  %call = call i64 @write(i32 %0, i8* %data, i64 1), !dbg !811
  %conv = trunc i64 %call to i32, !dbg !811
  store i32 %conv, i32* %r, align 4, !dbg !812
  br label %do.cond, !dbg !813

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !814
  %cmp = icmp slt i32 %1, 0, !dbg !816
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !817

land.rhs:                                         ; preds = %do.cond
  %call2 = call i32* @__errno_location() #2, !dbg !818
  %2 = load i32, i32* %call2, align 4, !dbg !818
  %cmp3 = icmp eq i32 %2, 4, !dbg !820
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp3, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !821

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !823
  %cmp5 = icmp slt i32 %4, 0, !dbg !824
  %cond = select i1 %cmp5, i32 -1, i32 0, !dbg !825
  ret i32 %cond, !dbg !826
}

declare i64 @write(i32, i8*, i64) #1

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare void @uv__io_init(%struct.uv__io_s*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, i32) #1

; Function Attrs: nounwind uwtable
define internal void @uv__signal_event(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !303 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  %msg = alloca %struct.uv__signal_msg_t*, align 8
  %handle = alloca %struct.uv_signal_s*, align 8
  %buf = alloca [512 x i8], align 16
  %bytes = alloca i64, align 8
  %end = alloca i64, align 8
  %i = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !827, metadata !385), !dbg !828
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !829, metadata !385), !dbg !830
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !831, metadata !385), !dbg !832
  call void @llvm.dbg.declare(metadata %struct.uv__signal_msg_t** %msg, metadata !833, metadata !385), !dbg !834
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle, metadata !835, metadata !385), !dbg !836
  call void @llvm.dbg.declare(metadata [512 x i8]* %buf, metadata !837, metadata !385), !dbg !841
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !842, metadata !385), !dbg !845
  call void @llvm.dbg.declare(metadata i64* %end, metadata !846, metadata !385), !dbg !847
  call void @llvm.dbg.declare(metadata i64* %i, metadata !848, metadata !385), !dbg !849
  call void @llvm.dbg.declare(metadata i32* %r, metadata !850, metadata !385), !dbg !851
  store i64 0, i64* %bytes, align 8, !dbg !852
  store i64 0, i64* %end, align 8, !dbg !853
  br label %do.body, !dbg !854

do.body:                                          ; preds = %do.cond, %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !855
  %signal_pipefd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 28, !dbg !857
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd, i64 0, i64 0, !dbg !855
  %1 = load i32, i32* %arrayidx, align 8, !dbg !855
  %arraydecay = getelementptr inbounds [512 x i8], [512 x i8]* %buf, i32 0, i32 0, !dbg !858
  %2 = load i64, i64* %bytes, align 8, !dbg !859
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 %2, !dbg !860
  %3 = load i64, i64* %bytes, align 8, !dbg !861
  %sub = sub i64 512, %3, !dbg !862
  %call = call i64 @read(i32 %1, i8* %add.ptr, i64 %sub), !dbg !863
  %conv = trunc i64 %call to i32, !dbg !863
  store i32 %conv, i32* %r, align 4, !dbg !864
  %4 = load i32, i32* %r, align 4, !dbg !865
  %cmp = icmp eq i32 %4, -1, !dbg !867
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !868

land.lhs.true:                                    ; preds = %do.body
  %call2 = call i32* @__errno_location() #2, !dbg !869
  %5 = load i32, i32* %call2, align 4, !dbg !869
  %cmp3 = icmp eq i32 %5, 4, !dbg !871
  br i1 %cmp3, label %if.then, label %if.end, !dbg !872

if.then:                                          ; preds = %land.lhs.true
  br label %do.cond, !dbg !873

if.end:                                           ; preds = %land.lhs.true, %do.body
  %6 = load i32, i32* %r, align 4, !dbg !874
  %cmp5 = icmp eq i32 %6, -1, !dbg !876
  br i1 %cmp5, label %land.lhs.true7, label %if.end19, !dbg !877

land.lhs.true7:                                   ; preds = %if.end
  %call8 = call i32* @__errno_location() #2, !dbg !878
  %7 = load i32, i32* %call8, align 4, !dbg !878
  %cmp9 = icmp eq i32 %7, 11, !dbg !880
  br i1 %cmp9, label %if.then14, label %lor.lhs.false, !dbg !881

lor.lhs.false:                                    ; preds = %land.lhs.true7
  %call11 = call i32* @__errno_location() #2, !dbg !882
  %8 = load i32, i32* %call11, align 4, !dbg !882
  %cmp12 = icmp eq i32 %8, 11, !dbg !884
  br i1 %cmp12, label %if.then14, label %if.end19, !dbg !885

if.then14:                                        ; preds = %lor.lhs.false, %land.lhs.true7
  %9 = load i64, i64* %bytes, align 8, !dbg !886
  %cmp15 = icmp ugt i64 %9, 0, !dbg !889
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !890

if.then17:                                        ; preds = %if.then14
  br label %do.cond, !dbg !891

if.end18:                                         ; preds = %if.then14
  br label %do.end, !dbg !892

if.end19:                                         ; preds = %lor.lhs.false, %if.end
  %10 = load i32, i32* %r, align 4, !dbg !893
  %cmp20 = icmp eq i32 %10, -1, !dbg !895
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !896

if.then22:                                        ; preds = %if.end19
  call void @abort() #8, !dbg !897
  unreachable, !dbg !897

if.end23:                                         ; preds = %if.end19
  %11 = load i32, i32* %r, align 4, !dbg !898
  %conv24 = sext i32 %11 to i64, !dbg !898
  %12 = load i64, i64* %bytes, align 8, !dbg !899
  %add = add i64 %12, %conv24, !dbg !899
  store i64 %add, i64* %bytes, align 8, !dbg !899
  %13 = load i64, i64* %bytes, align 8, !dbg !900
  %div = udiv i64 %13, 16, !dbg !901
  %mul = mul i64 %div, 16, !dbg !902
  store i64 %mul, i64* %end, align 8, !dbg !903
  store i64 0, i64* %i, align 8, !dbg !904
  br label %for.cond, !dbg !906

for.cond:                                         ; preds = %for.inc, %if.end23
  %14 = load i64, i64* %i, align 8, !dbg !907
  %15 = load i64, i64* %end, align 8, !dbg !910
  %cmp25 = icmp ult i64 %14, %15, !dbg !911
  br i1 %cmp25, label %for.body, label %for.end, !dbg !912

for.body:                                         ; preds = %for.cond
  %arraydecay27 = getelementptr inbounds [512 x i8], [512 x i8]* %buf, i32 0, i32 0, !dbg !913
  %16 = load i64, i64* %i, align 8, !dbg !915
  %add.ptr28 = getelementptr inbounds i8, i8* %arraydecay27, i64 %16, !dbg !916
  %17 = bitcast i8* %add.ptr28 to %struct.uv__signal_msg_t*, !dbg !917
  store %struct.uv__signal_msg_t* %17, %struct.uv__signal_msg_t** %msg, align 8, !dbg !918
  %18 = load %struct.uv__signal_msg_t*, %struct.uv__signal_msg_t** %msg, align 8, !dbg !919
  %handle29 = getelementptr inbounds %struct.uv__signal_msg_t, %struct.uv__signal_msg_t* %18, i32 0, i32 0, !dbg !920
  %19 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle29, align 8, !dbg !920
  store %struct.uv_signal_s* %19, %struct.uv_signal_s** %handle, align 8, !dbg !921
  %20 = load %struct.uv__signal_msg_t*, %struct.uv__signal_msg_t** %msg, align 8, !dbg !922
  %signum = getelementptr inbounds %struct.uv__signal_msg_t, %struct.uv__signal_msg_t* %20, i32 0, i32 1, !dbg !924
  %21 = load i32, i32* %signum, align 8, !dbg !924
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !925
  %signum30 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 9, !dbg !926
  %23 = load i32, i32* %signum30, align 8, !dbg !926
  %cmp31 = icmp eq i32 %21, %23, !dbg !927
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !928

if.then33:                                        ; preds = %for.body
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !929
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %24, i32 0, i32 7, !dbg !929
  %25 = load i32, i32* %flags, align 8, !dbg !929
  %and = and i32 %25, 1, !dbg !929
  %tobool = icmp ne i32 %and, 0, !dbg !929
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !929

cond.true:                                        ; preds = %if.then33
  br label %cond.end, !dbg !931

cond.false:                                       ; preds = %if.then33
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 453, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @__PRETTY_FUNCTION__.uv__signal_event, i32 0, i32 0)) #8, !dbg !933
  unreachable, !dbg !933
                                                  ; No predecessors!
  br label %cond.end, !dbg !935

cond.end:                                         ; preds = %26, %cond.true
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !937
  %signal_cb = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %27, i32 0, i32 8, !dbg !938
  %28 = load void (%struct.uv_signal_s*, i32)*, void (%struct.uv_signal_s*, i32)** %signal_cb, align 8, !dbg !938
  %29 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !939
  %30 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !940
  %signum34 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %30, i32 0, i32 9, !dbg !941
  %31 = load i32, i32* %signum34, align 8, !dbg !941
  call void %28(%struct.uv_signal_s* %29, i32 %31), !dbg !937
  br label %if.end35, !dbg !942

if.end35:                                         ; preds = %cond.end, %for.body
  %32 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !943
  %dispatched_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %32, i32 0, i32 12, !dbg !944
  %33 = load i32, i32* %dispatched_signals, align 4, !dbg !945
  %inc = add i32 %33, 1, !dbg !945
  store i32 %inc, i32* %dispatched_signals, align 4, !dbg !945
  %34 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !946
  %flags36 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %34, i32 0, i32 7, !dbg !948
  %35 = load i32, i32* %flags36, align 8, !dbg !948
  %and37 = and i32 %35, 524288, !dbg !949
  %tobool38 = icmp ne i32 %and37, 0, !dbg !949
  br i1 %tobool38, label %if.then39, label %if.end40, !dbg !950

if.then39:                                        ; preds = %if.end35
  %36 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !951
  call void @uv__signal_stop(%struct.uv_signal_s* %36), !dbg !952
  br label %if.end40, !dbg !952

if.end40:                                         ; preds = %if.then39, %if.end35
  %37 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !953
  %flags41 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %37, i32 0, i32 7, !dbg !955
  %38 = load i32, i32* %flags41, align 8, !dbg !955
  %and42 = and i32 %38, 1, !dbg !956
  %tobool43 = icmp ne i32 %and42, 0, !dbg !956
  br i1 %tobool43, label %land.lhs.true44, label %if.end49, !dbg !957

land.lhs.true44:                                  ; preds = %if.end40
  %39 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !958
  %caught_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %39, i32 0, i32 11, !dbg !959
  %40 = load i32, i32* %caught_signals, align 8, !dbg !959
  %41 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !960
  %dispatched_signals45 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %41, i32 0, i32 12, !dbg !961
  %42 = load i32, i32* %dispatched_signals45, align 4, !dbg !961
  %cmp46 = icmp eq i32 %40, %42, !dbg !962
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !963

if.then48:                                        ; preds = %land.lhs.true44
  %43 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !965
  %44 = bitcast %struct.uv_signal_s* %43 to %struct.uv_handle_s*, !dbg !967
  call void @uv__make_close_pending(%struct.uv_handle_s* %44), !dbg !968
  br label %if.end49, !dbg !969

if.end49:                                         ; preds = %if.then48, %land.lhs.true44, %if.end40
  br label %for.inc, !dbg !970

for.inc:                                          ; preds = %if.end49
  %45 = load i64, i64* %i, align 8, !dbg !971
  %add50 = add i64 %45, 16, !dbg !971
  store i64 %add50, i64* %i, align 8, !dbg !971
  br label %for.cond, !dbg !973

for.end:                                          ; preds = %for.cond
  %46 = load i64, i64* %end, align 8, !dbg !974
  %47 = load i64, i64* %bytes, align 8, !dbg !975
  %sub51 = sub i64 %47, %46, !dbg !975
  store i64 %sub51, i64* %bytes, align 8, !dbg !975
  %48 = load i64, i64* %bytes, align 8, !dbg !976
  %tobool52 = icmp ne i64 %48, 0, !dbg !976
  br i1 %tobool52, label %if.then53, label %if.end57, !dbg !978

if.then53:                                        ; preds = %for.end
  %arraydecay54 = getelementptr inbounds [512 x i8], [512 x i8]* %buf, i32 0, i32 0, !dbg !979
  %arraydecay55 = getelementptr inbounds [512 x i8], [512 x i8]* %buf, i32 0, i32 0, !dbg !981
  %49 = load i64, i64* %end, align 8, !dbg !982
  %add.ptr56 = getelementptr inbounds i8, i8* %arraydecay55, i64 %49, !dbg !983
  %50 = load i64, i64* %bytes, align 8, !dbg !984
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %arraydecay54, i8* %add.ptr56, i64 %50, i32 1, i1 false), !dbg !979
  br label %do.cond, !dbg !985

if.end57:                                         ; preds = %for.end
  br label %do.cond, !dbg !986

do.cond:                                          ; preds = %if.end57, %if.then53, %if.then17, %if.then
  %51 = load i64, i64* %end, align 8, !dbg !987
  %cmp58 = icmp eq i64 %51, 512, !dbg !989
  br i1 %cmp58, label %do.body, label %do.end, !dbg !990

do.end:                                           ; preds = %if.end18, %do.cond
  ret void, !dbg !991
}

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #1

declare i64 @read(i32, i8*, i64) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal void @uv__signal_block_and_lock(%struct.__sigset_t* %saved_sigmask) #0 !dbg !309 {
entry:
  %saved_sigmask.addr = alloca %struct.__sigset_t*, align 8
  %new_mask = alloca %struct.__sigset_t, align 8
  store %struct.__sigset_t* %saved_sigmask, %struct.__sigset_t** %saved_sigmask.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__sigset_t** %saved_sigmask.addr, metadata !992, metadata !385), !dbg !993
  call void @llvm.dbg.declare(metadata %struct.__sigset_t* %new_mask, metadata !994, metadata !385), !dbg !995
  %call = call i32 @sigfillset(%struct.__sigset_t* %new_mask) #7, !dbg !996
  %tobool = icmp ne i32 %call, 0, !dbg !996
  br i1 %tobool, label %if.then, label %if.end, !dbg !998

if.then:                                          ; preds = %entry
  call void @abort() #8, !dbg !999
  unreachable, !dbg !999

if.end:                                           ; preds = %entry
  %0 = load %struct.__sigset_t*, %struct.__sigset_t** %saved_sigmask.addr, align 8, !dbg !1000
  %call1 = call i32 @pthread_sigmask(i32 2, %struct.__sigset_t* %new_mask, %struct.__sigset_t* %0) #7, !dbg !1002
  %tobool2 = icmp ne i32 %call1, 0, !dbg !1002
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !1003

if.then3:                                         ; preds = %if.end
  call void @abort() #8, !dbg !1004
  unreachable, !dbg !1004

if.end4:                                          ; preds = %if.end
  %call5 = call i32 @uv__signal_lock(), !dbg !1005
  %tobool6 = icmp ne i32 %call5, 0, !dbg !1005
  br i1 %tobool6, label %if.then7, label %if.end8, !dbg !1007

if.then7:                                         ; preds = %if.end4
  call void @abort() #8, !dbg !1008
  unreachable, !dbg !1008

if.end8:                                          ; preds = %if.end4
  ret void, !dbg !1009
}

; Function Attrs: nounwind uwtable
define internal %struct.uv_signal_s* @uv__signal_first_handle(i32 %signum) #0 !dbg !324 {
entry:
  %retval = alloca %struct.uv_signal_s*, align 8
  %signum.addr = alloca i32, align 4
  %lookup = alloca %struct.uv_signal_s, align 8
  %handle = alloca %struct.uv_signal_s*, align 8
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1010, metadata !385), !dbg !1011
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s* %lookup, metadata !1012, metadata !385), !dbg !1013
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle, metadata !1014, metadata !385), !dbg !1015
  %0 = load i32, i32* %signum.addr, align 4, !dbg !1016
  %signum1 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %lookup, i32 0, i32 9, !dbg !1017
  store i32 %0, i32* %signum1, align 8, !dbg !1018
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %lookup, i32 0, i32 7, !dbg !1019
  store i32 0, i32* %flags, align 8, !dbg !1020
  %loop = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %lookup, i32 0, i32 1, !dbg !1021
  store %struct.uv_loop_s* null, %struct.uv_loop_s** %loop, align 8, !dbg !1022
  %call = call %struct.uv_signal_s* @uv__signal_tree_s_RB_NFIND(%struct.uv__signal_tree_s* @uv__signal_tree, %struct.uv_signal_s* %lookup), !dbg !1023
  store %struct.uv_signal_s* %call, %struct.uv_signal_s** %handle, align 8, !dbg !1024
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1025
  %cmp = icmp ne %struct.uv_signal_s* %1, null, !dbg !1027
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !1028

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1029
  %signum2 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %2, i32 0, i32 9, !dbg !1031
  %3 = load i32, i32* %signum2, align 8, !dbg !1031
  %4 = load i32, i32* %signum.addr, align 4, !dbg !1032
  %cmp3 = icmp eq i32 %3, %4, !dbg !1033
  br i1 %cmp3, label %if.then, label %if.end, !dbg !1034

if.then:                                          ; preds = %land.lhs.true
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1035
  store %struct.uv_signal_s* %5, %struct.uv_signal_s** %retval, align 8, !dbg !1036
  br label %return, !dbg !1036

if.end:                                           ; preds = %land.lhs.true, %entry
  store %struct.uv_signal_s* null, %struct.uv_signal_s** %retval, align 8, !dbg !1037
  br label %return, !dbg !1037

return:                                           ; preds = %if.end, %if.then
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %retval, align 8, !dbg !1038
  ret %struct.uv_signal_s* %6, !dbg !1038
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__signal_register_handler(i32 %signum, i32 %oneshot) #0 !dbg !337 {
entry:
  %retval = alloca i32, align 4
  %signum.addr = alloca i32, align 4
  %oneshot.addr = alloca i32, align 4
  %sa = alloca %struct.sigaction, align 8
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1039, metadata !385), !dbg !1040
  store i32 %oneshot, i32* %oneshot.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %oneshot.addr, metadata !1041, metadata !385), !dbg !1042
  call void @llvm.dbg.declare(metadata %struct.sigaction* %sa, metadata !1043, metadata !385), !dbg !1124
  %0 = bitcast %struct.sigaction* %sa to i8*, !dbg !1125
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 152, i32 8, i1 false), !dbg !1125
  %sa_mask = getelementptr inbounds %struct.sigaction, %struct.sigaction* %sa, i32 0, i32 1, !dbg !1126
  %call = call i32 @sigfillset(%struct.__sigset_t* %sa_mask) #7, !dbg !1128
  %tobool = icmp ne i32 %call, 0, !dbg !1128
  br i1 %tobool, label %if.then, label %if.end, !dbg !1129

if.then:                                          ; preds = %entry
  call void @abort() #8, !dbg !1130
  unreachable, !dbg !1130

if.end:                                           ; preds = %entry
  %__sigaction_handler = getelementptr inbounds %struct.sigaction, %struct.sigaction* %sa, i32 0, i32 0, !dbg !1131
  %sa_handler = bitcast %union.anon.4* %__sigaction_handler to void (i32)**, !dbg !1131
  store void (i32)* @uv__signal_handler, void (i32)** %sa_handler, align 8, !dbg !1132
  %1 = load i32, i32* %oneshot.addr, align 4, !dbg !1133
  %tobool1 = icmp ne i32 %1, 0, !dbg !1133
  %cond = select i1 %tobool1, i32 -2147483648, i32 0, !dbg !1133
  %sa_flags = getelementptr inbounds %struct.sigaction, %struct.sigaction* %sa, i32 0, i32 2, !dbg !1134
  store i32 %cond, i32* %sa_flags, align 8, !dbg !1135
  %2 = load i32, i32* %signum.addr, align 4, !dbg !1136
  %call2 = call i32 @sigaction(i32 %2, %struct.sigaction* %sa, %struct.sigaction* null) #7, !dbg !1138
  %tobool3 = icmp ne i32 %call2, 0, !dbg !1138
  br i1 %tobool3, label %if.then4, label %if.end6, !dbg !1139

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #2, !dbg !1140
  %3 = load i32, i32* %call5, align 4, !dbg !1140
  %sub = sub nsw i32 0, %3, !dbg !1141
  store i32 %sub, i32* %retval, align 4, !dbg !1142
  br label %return, !dbg !1142

if.end6:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1143
  br label %return, !dbg !1143

return:                                           ; preds = %if.end6, %if.then4
  %4 = load i32, i32* %retval, align 4, !dbg !1144
  ret i32 %4, !dbg !1144
}

; Function Attrs: nounwind uwtable
define internal void @uv__signal_unlock_and_unblock(%struct.__sigset_t* %saved_sigmask) #0 !dbg !344 {
entry:
  %saved_sigmask.addr = alloca %struct.__sigset_t*, align 8
  store %struct.__sigset_t* %saved_sigmask, %struct.__sigset_t** %saved_sigmask.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__sigset_t** %saved_sigmask.addr, metadata !1145, metadata !385), !dbg !1146
  %call = call i32 @uv__signal_unlock(), !dbg !1147
  %tobool = icmp ne i32 %call, 0, !dbg !1147
  br i1 %tobool, label %if.then, label %if.end, !dbg !1149

if.then:                                          ; preds = %entry
  call void @abort() #8, !dbg !1150
  unreachable, !dbg !1150

if.end:                                           ; preds = %entry
  %0 = load %struct.__sigset_t*, %struct.__sigset_t** %saved_sigmask.addr, align 8, !dbg !1151
  %call1 = call i32 @pthread_sigmask(i32 2, %struct.__sigset_t* %0, %struct.__sigset_t* null) #7, !dbg !1153
  %tobool2 = icmp ne i32 %call1, 0, !dbg !1153
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !1154

if.then3:                                         ; preds = %if.end
  call void @abort() #8, !dbg !1155
  unreachable, !dbg !1155

if.end4:                                          ; preds = %if.end
  ret void, !dbg !1156
}

; Function Attrs: nounwind uwtable
define internal %struct.uv_signal_s* @uv__signal_tree_s_RB_INSERT(%struct.uv__signal_tree_s* %head, %struct.uv_signal_s* %elm) #0 !dbg !345 {
entry:
  %retval = alloca %struct.uv_signal_s*, align 8
  %head.addr = alloca %struct.uv__signal_tree_s*, align 8
  %elm.addr = alloca %struct.uv_signal_s*, align 8
  %tmp = alloca %struct.uv_signal_s*, align 8
  %parent = alloca %struct.uv_signal_s*, align 8
  %comp = alloca i32, align 4
  store %struct.uv__signal_tree_s* %head, %struct.uv__signal_tree_s** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__signal_tree_s** %head.addr, metadata !1157, metadata !385), !dbg !1158
  store %struct.uv_signal_s* %elm, %struct.uv_signal_s** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %elm.addr, metadata !1159, metadata !385), !dbg !1158
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %tmp, metadata !1160, metadata !385), !dbg !1158
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %parent, metadata !1161, metadata !385), !dbg !1158
  store %struct.uv_signal_s* null, %struct.uv_signal_s** %parent, align 8, !dbg !1158
  call void @llvm.dbg.declare(metadata i32* %comp, metadata !1162, metadata !385), !dbg !1158
  store i32 0, i32* %comp, align 4, !dbg !1158
  %0 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1158
  %rbh_root = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %0, i32 0, i32 0, !dbg !1158
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbh_root, align 8, !dbg !1158
  store %struct.uv_signal_s* %1, %struct.uv_signal_s** %tmp, align 8, !dbg !1158
  br label %while.cond, !dbg !1158

while.cond:                                       ; preds = %if.end7, %entry
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1163
  %tobool = icmp ne %struct.uv_signal_s* %2, null, !dbg !1163
  br i1 %tobool, label %while.body, label %while.end, !dbg !1163

while.body:                                       ; preds = %while.cond
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1165
  store %struct.uv_signal_s* %3, %struct.uv_signal_s** %parent, align 8, !dbg !1165
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1165
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1165
  %call = call i32 @uv__signal_compare(%struct.uv_signal_s* %4, %struct.uv_signal_s* %5), !dbg !1165
  store i32 %call, i32* %comp, align 4, !dbg !1165
  %6 = load i32, i32* %comp, align 4, !dbg !1165
  %cmp = icmp slt i32 %6, 0, !dbg !1165
  br i1 %cmp, label %if.then, label %if.else, !dbg !1165

if.then:                                          ; preds = %while.body
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1168
  %tree_entry = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %7, i32 0, i32 10, !dbg !1168
  %rbe_left = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry, i32 0, i32 0, !dbg !1168
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left, align 8, !dbg !1168
  store %struct.uv_signal_s* %8, %struct.uv_signal_s** %tmp, align 8, !dbg !1168
  br label %if.end7, !dbg !1168

if.else:                                          ; preds = %while.body
  %9 = load i32, i32* %comp, align 4, !dbg !1171
  %cmp3 = icmp sgt i32 %9, 0, !dbg !1171
  br i1 %cmp3, label %if.then4, label %if.else6, !dbg !1171

if.then4:                                         ; preds = %if.else
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1174
  %tree_entry5 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %10, i32 0, i32 10, !dbg !1174
  %rbe_right = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry5, i32 0, i32 1, !dbg !1174
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right, align 8, !dbg !1174
  store %struct.uv_signal_s* %11, %struct.uv_signal_s** %tmp, align 8, !dbg !1174
  br label %if.end, !dbg !1174

if.else6:                                         ; preds = %if.else
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1176
  store %struct.uv_signal_s* %12, %struct.uv_signal_s** %retval, align 8, !dbg !1176
  br label %return, !dbg !1176

if.end:                                           ; preds = %if.then4
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  br label %while.cond, !dbg !1178

while.end:                                        ; preds = %while.cond
  br label %do.body, !dbg !1180

do.body:                                          ; preds = %while.end
  %13 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1182
  %14 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1182
  %tree_entry8 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %14, i32 0, i32 10, !dbg !1182
  %rbe_parent = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry8, i32 0, i32 2, !dbg !1182
  store %struct.uv_signal_s* %13, %struct.uv_signal_s** %rbe_parent, align 8, !dbg !1182
  %15 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1182
  %tree_entry9 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %15, i32 0, i32 10, !dbg !1182
  %rbe_right10 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry9, i32 0, i32 1, !dbg !1182
  store %struct.uv_signal_s* null, %struct.uv_signal_s** %rbe_right10, align 8, !dbg !1182
  %16 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1182
  %tree_entry11 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %16, i32 0, i32 10, !dbg !1182
  %rbe_left12 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry11, i32 0, i32 0, !dbg !1182
  store %struct.uv_signal_s* null, %struct.uv_signal_s** %rbe_left12, align 8, !dbg !1182
  %17 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1182
  %tree_entry13 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %17, i32 0, i32 10, !dbg !1182
  %rbe_color = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry13, i32 0, i32 3, !dbg !1182
  store i32 1, i32* %rbe_color, align 8, !dbg !1182
  br label %do.end, !dbg !1182

do.end:                                           ; preds = %do.body
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1185
  %cmp14 = icmp ne %struct.uv_signal_s* %18, null, !dbg !1185
  br i1 %cmp14, label %if.then15, label %if.else26, !dbg !1185

if.then15:                                        ; preds = %do.end
  %19 = load i32, i32* %comp, align 4, !dbg !1188
  %cmp16 = icmp slt i32 %19, 0, !dbg !1188
  br i1 %cmp16, label %if.then17, label %if.else20, !dbg !1188

if.then17:                                        ; preds = %if.then15
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1192
  %21 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1192
  %tree_entry18 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %21, i32 0, i32 10, !dbg !1192
  %rbe_left19 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry18, i32 0, i32 0, !dbg !1192
  store %struct.uv_signal_s* %20, %struct.uv_signal_s** %rbe_left19, align 8, !dbg !1192
  br label %if.end23, !dbg !1192

if.else20:                                        ; preds = %if.then15
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1194
  %23 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1194
  %tree_entry21 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %23, i32 0, i32 10, !dbg !1194
  %rbe_right22 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry21, i32 0, i32 1, !dbg !1194
  store %struct.uv_signal_s* %22, %struct.uv_signal_s** %rbe_right22, align 8, !dbg !1194
  br label %if.end23

if.end23:                                         ; preds = %if.else20, %if.then17
  br label %do.body24, !dbg !1196

do.body24:                                        ; preds = %if.end23
  br label %do.end25, !dbg !1198

do.end25:                                         ; preds = %do.body24
  br label %if.end28, !dbg !1201

if.else26:                                        ; preds = %do.end
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1203
  %25 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1203
  %rbh_root27 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %25, i32 0, i32 0, !dbg !1203
  store %struct.uv_signal_s* %24, %struct.uv_signal_s** %rbh_root27, align 8, !dbg !1203
  br label %if.end28

if.end28:                                         ; preds = %if.else26, %do.end25
  %26 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1205
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1205
  call void @uv__signal_tree_s_RB_INSERT_COLOR(%struct.uv__signal_tree_s* %26, %struct.uv_signal_s* %27), !dbg !1205
  store %struct.uv_signal_s* null, %struct.uv_signal_s** %retval, align 8, !dbg !1205
  br label %return, !dbg !1205

return:                                           ; preds = %if.end28, %if.else6
  %28 = load %struct.uv_signal_s*, %struct.uv_signal_s** %retval, align 8, !dbg !1207
  ret %struct.uv_signal_s* %28, !dbg !1207
}

; Function Attrs: nounwind
declare i32 @sigfillset(%struct.__sigset_t*) #4

; Function Attrs: nounwind
declare i32 @pthread_sigmask(i32, %struct.__sigset_t*, %struct.__sigset_t*) #4

; Function Attrs: nounwind uwtable
define internal i32 @uv__signal_lock() #0 !dbg !323 {
entry:
  %r = alloca i32, align 4
  %data = alloca i8, align 1
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1209, metadata !385), !dbg !1210
  call void @llvm.dbg.declare(metadata i8* %data, metadata !1211, metadata !385), !dbg !1212
  br label %do.body, !dbg !1213

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @uv__signal_lock_pipefd, i64 0, i64 0), align 4, !dbg !1214
  %call = call i64 @read(i32 %0, i8* %data, i64 1), !dbg !1216
  %conv = trunc i64 %call to i32, !dbg !1216
  store i32 %conv, i32* %r, align 4, !dbg !1217
  br label %do.cond, !dbg !1218

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !1219
  %cmp = icmp slt i32 %1, 0, !dbg !1221
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1222

land.rhs:                                         ; preds = %do.cond
  %call2 = call i32* @__errno_location() #2, !dbg !1223
  %2 = load i32, i32* %call2, align 4, !dbg !1223
  %cmp3 = icmp eq i32 %2, 4, !dbg !1225
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp3, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !1226

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !1228
  %cmp5 = icmp slt i32 %4, 0, !dbg !1229
  %cond = select i1 %cmp5, i32 -1, i32 0, !dbg !1230
  ret i32 %cond, !dbg !1231
}

; Function Attrs: nounwind uwtable
define internal %struct.uv_signal_s* @uv__signal_tree_s_RB_NFIND(%struct.uv__signal_tree_s* %head, %struct.uv_signal_s* %elm) #0 !dbg !327 {
entry:
  %retval = alloca %struct.uv_signal_s*, align 8
  %head.addr = alloca %struct.uv__signal_tree_s*, align 8
  %elm.addr = alloca %struct.uv_signal_s*, align 8
  %tmp = alloca %struct.uv_signal_s*, align 8
  %res = alloca %struct.uv_signal_s*, align 8
  %comp = alloca i32, align 4
  store %struct.uv__signal_tree_s* %head, %struct.uv__signal_tree_s** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__signal_tree_s** %head.addr, metadata !1232, metadata !385), !dbg !1233
  store %struct.uv_signal_s* %elm, %struct.uv_signal_s** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %elm.addr, metadata !1234, metadata !385), !dbg !1233
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %tmp, metadata !1235, metadata !385), !dbg !1233
  %0 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1233
  %rbh_root = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %0, i32 0, i32 0, !dbg !1233
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbh_root, align 8, !dbg !1233
  store %struct.uv_signal_s* %1, %struct.uv_signal_s** %tmp, align 8, !dbg !1233
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %res, metadata !1236, metadata !385), !dbg !1233
  store %struct.uv_signal_s* null, %struct.uv_signal_s** %res, align 8, !dbg !1233
  call void @llvm.dbg.declare(metadata i32* %comp, metadata !1237, metadata !385), !dbg !1233
  br label %while.cond, !dbg !1233

while.cond:                                       ; preds = %if.end7, %entry
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1238
  %tobool = icmp ne %struct.uv_signal_s* %2, null, !dbg !1238
  br i1 %tobool, label %while.body, label %while.end, !dbg !1238

while.body:                                       ; preds = %while.cond
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1240
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1240
  %call = call i32 @uv__signal_compare(%struct.uv_signal_s* %3, %struct.uv_signal_s* %4), !dbg !1240
  store i32 %call, i32* %comp, align 4, !dbg !1240
  %5 = load i32, i32* %comp, align 4, !dbg !1240
  %cmp = icmp slt i32 %5, 0, !dbg !1240
  br i1 %cmp, label %if.then, label %if.else, !dbg !1240

if.then:                                          ; preds = %while.body
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1243
  store %struct.uv_signal_s* %6, %struct.uv_signal_s** %res, align 8, !dbg !1243
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1243
  %tree_entry = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %7, i32 0, i32 10, !dbg !1243
  %rbe_left = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry, i32 0, i32 0, !dbg !1243
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left, align 8, !dbg !1243
  store %struct.uv_signal_s* %8, %struct.uv_signal_s** %tmp, align 8, !dbg !1243
  br label %if.end7, !dbg !1243

if.else:                                          ; preds = %while.body
  %9 = load i32, i32* %comp, align 4, !dbg !1247
  %cmp3 = icmp sgt i32 %9, 0, !dbg !1247
  br i1 %cmp3, label %if.then4, label %if.else6, !dbg !1247

if.then4:                                         ; preds = %if.else
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1250
  %tree_entry5 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %10, i32 0, i32 10, !dbg !1250
  %rbe_right = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry5, i32 0, i32 1, !dbg !1250
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right, align 8, !dbg !1250
  store %struct.uv_signal_s* %11, %struct.uv_signal_s** %tmp, align 8, !dbg !1250
  br label %if.end, !dbg !1250

if.else6:                                         ; preds = %if.else
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1252
  store %struct.uv_signal_s* %12, %struct.uv_signal_s** %retval, align 8, !dbg !1252
  br label %return, !dbg !1252

if.end:                                           ; preds = %if.then4
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  br label %while.cond, !dbg !1254

while.end:                                        ; preds = %while.cond
  %13 = load %struct.uv_signal_s*, %struct.uv_signal_s** %res, align 8, !dbg !1256
  store %struct.uv_signal_s* %13, %struct.uv_signal_s** %retval, align 8, !dbg !1256
  br label %return, !dbg !1256

return:                                           ; preds = %while.end, %if.else6
  %14 = load %struct.uv_signal_s*, %struct.uv_signal_s** %retval, align 8, !dbg !1258
  ret %struct.uv_signal_s* %14, !dbg !1258
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__signal_compare(%struct.uv_signal_s* %w1, %struct.uv_signal_s* %w2) #0 !dbg !334 {
entry:
  %retval = alloca i32, align 4
  %w1.addr = alloca %struct.uv_signal_s*, align 8
  %w2.addr = alloca %struct.uv_signal_s*, align 8
  %f1 = alloca i32, align 4
  %f2 = alloca i32, align 4
  store %struct.uv_signal_s* %w1, %struct.uv_signal_s** %w1.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %w1.addr, metadata !1260, metadata !385), !dbg !1261
  store %struct.uv_signal_s* %w2, %struct.uv_signal_s** %w2.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %w2.addr, metadata !1262, metadata !385), !dbg !1263
  call void @llvm.dbg.declare(metadata i32* %f1, metadata !1264, metadata !385), !dbg !1265
  call void @llvm.dbg.declare(metadata i32* %f2, metadata !1266, metadata !385), !dbg !1267
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1268
  %signum = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %0, i32 0, i32 9, !dbg !1270
  %1 = load i32, i32* %signum, align 8, !dbg !1270
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1271
  %signum1 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %2, i32 0, i32 9, !dbg !1272
  %3 = load i32, i32* %signum1, align 8, !dbg !1272
  %cmp = icmp slt i32 %1, %3, !dbg !1273
  br i1 %cmp, label %if.then, label %if.end, !dbg !1274

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !1275
  br label %return, !dbg !1275

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1277
  %signum2 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %4, i32 0, i32 9, !dbg !1279
  %5 = load i32, i32* %signum2, align 8, !dbg !1279
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1280
  %signum3 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %6, i32 0, i32 9, !dbg !1281
  %7 = load i32, i32* %signum3, align 8, !dbg !1281
  %cmp4 = icmp sgt i32 %5, %7, !dbg !1282
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1283

if.then5:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !1284
  br label %return, !dbg !1284

if.end6:                                          ; preds = %if.end
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1286
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %8, i32 0, i32 7, !dbg !1287
  %9 = load i32, i32* %flags, align 8, !dbg !1287
  %and = and i32 %9, 524288, !dbg !1288
  store i32 %and, i32* %f1, align 4, !dbg !1289
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1290
  %flags7 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %10, i32 0, i32 7, !dbg !1291
  %11 = load i32, i32* %flags7, align 8, !dbg !1291
  %and8 = and i32 %11, 524288, !dbg !1292
  store i32 %and8, i32* %f2, align 4, !dbg !1293
  %12 = load i32, i32* %f1, align 4, !dbg !1294
  %13 = load i32, i32* %f2, align 4, !dbg !1296
  %cmp9 = icmp slt i32 %12, %13, !dbg !1297
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !1298

if.then10:                                        ; preds = %if.end6
  store i32 -1, i32* %retval, align 4, !dbg !1299
  br label %return, !dbg !1299

if.end11:                                         ; preds = %if.end6
  %14 = load i32, i32* %f1, align 4, !dbg !1301
  %15 = load i32, i32* %f2, align 4, !dbg !1303
  %cmp12 = icmp sgt i32 %14, %15, !dbg !1304
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !1305

if.then13:                                        ; preds = %if.end11
  store i32 1, i32* %retval, align 4, !dbg !1306
  br label %return, !dbg !1306

if.end14:                                         ; preds = %if.end11
  %16 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1308
  %loop = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %16, i32 0, i32 1, !dbg !1310
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1310
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1311
  %loop15 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %18, i32 0, i32 1, !dbg !1312
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop15, align 8, !dbg !1312
  %cmp16 = icmp ult %struct.uv_loop_s* %17, %19, !dbg !1313
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !1314

if.then17:                                        ; preds = %if.end14
  store i32 -1, i32* %retval, align 4, !dbg !1315
  br label %return, !dbg !1315

if.end18:                                         ; preds = %if.end14
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1317
  %loop19 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %20, i32 0, i32 1, !dbg !1319
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop19, align 8, !dbg !1319
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1320
  %loop20 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 1, !dbg !1321
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop20, align 8, !dbg !1321
  %cmp21 = icmp ugt %struct.uv_loop_s* %21, %23, !dbg !1322
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !1323

if.then22:                                        ; preds = %if.end18
  store i32 1, i32* %retval, align 4, !dbg !1324
  br label %return, !dbg !1324

if.end23:                                         ; preds = %if.end18
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1326
  %25 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1328
  %cmp24 = icmp ult %struct.uv_signal_s* %24, %25, !dbg !1329
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !1330

if.then25:                                        ; preds = %if.end23
  store i32 -1, i32* %retval, align 4, !dbg !1331
  br label %return, !dbg !1331

if.end26:                                         ; preds = %if.end23
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w1.addr, align 8, !dbg !1333
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %w2.addr, align 8, !dbg !1335
  %cmp27 = icmp ugt %struct.uv_signal_s* %26, %27, !dbg !1336
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !1337

if.then28:                                        ; preds = %if.end26
  store i32 1, i32* %retval, align 4, !dbg !1338
  br label %return, !dbg !1338

if.end29:                                         ; preds = %if.end26
  store i32 0, i32* %retval, align 4, !dbg !1340
  br label %return, !dbg !1340

return:                                           ; preds = %if.end29, %if.then28, %if.then25, %if.then22, %if.then17, %if.then13, %if.then10, %if.then5, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !1341
  ret i32 %28, !dbg !1341
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal void @uv__signal_handler(i32 %signum) #0 !dbg !340 {
entry:
  %signum.addr = alloca i32, align 4
  %msg = alloca %struct.uv__signal_msg_t, align 8
  %handle = alloca %struct.uv_signal_s*, align 8
  %saved_errno = alloca i32, align 4
  %r = alloca i32, align 4
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1342, metadata !385), !dbg !1343
  call void @llvm.dbg.declare(metadata %struct.uv__signal_msg_t* %msg, metadata !1344, metadata !385), !dbg !1345
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle, metadata !1346, metadata !385), !dbg !1347
  call void @llvm.dbg.declare(metadata i32* %saved_errno, metadata !1348, metadata !385), !dbg !1349
  %call = call i32* @__errno_location() #2, !dbg !1350
  %0 = load i32, i32* %call, align 4, !dbg !1350
  store i32 %0, i32* %saved_errno, align 4, !dbg !1351
  %1 = bitcast %struct.uv__signal_msg_t* %msg to i8*, !dbg !1352
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 16, i32 8, i1 false), !dbg !1352
  %call1 = call i32 @uv__signal_lock(), !dbg !1353
  %tobool = icmp ne i32 %call1, 0, !dbg !1353
  br i1 %tobool, label %if.then, label %if.end, !dbg !1355

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %saved_errno, align 4, !dbg !1356
  %call2 = call i32* @__errno_location() #2, !dbg !1358
  store i32 %2, i32* %call2, align 4, !dbg !1359
  br label %return, !dbg !1360

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %signum.addr, align 4, !dbg !1361
  %call3 = call %struct.uv_signal_s* @uv__signal_first_handle(i32 %3), !dbg !1363
  store %struct.uv_signal_s* %call3, %struct.uv_signal_s** %handle, align 8, !dbg !1364
  br label %for.cond, !dbg !1365

for.cond:                                         ; preds = %for.inc, %if.end
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1366
  %cmp = icmp ne %struct.uv_signal_s* %4, null, !dbg !1368
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1369

land.rhs:                                         ; preds = %for.cond
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1370
  %signum4 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %5, i32 0, i32 9, !dbg !1372
  %6 = load i32, i32* %signum4, align 8, !dbg !1372
  %7 = load i32, i32* %signum.addr, align 4, !dbg !1373
  %cmp5 = icmp eq i32 %6, %7, !dbg !1374
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %8 = phi i1 [ false, %for.cond ], [ %cmp5, %land.rhs ]
  br i1 %8, label %for.body, label %for.end, !dbg !1375

for.body:                                         ; preds = %land.end
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1377, metadata !385), !dbg !1379
  %9 = load i32, i32* %signum.addr, align 4, !dbg !1380
  %signum6 = getelementptr inbounds %struct.uv__signal_msg_t, %struct.uv__signal_msg_t* %msg, i32 0, i32 1, !dbg !1381
  store i32 %9, i32* %signum6, align 8, !dbg !1382
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1383
  %handle7 = getelementptr inbounds %struct.uv__signal_msg_t, %struct.uv__signal_msg_t* %msg, i32 0, i32 0, !dbg !1384
  store %struct.uv_signal_s* %10, %struct.uv_signal_s** %handle7, align 8, !dbg !1385
  br label %do.body, !dbg !1386

do.body:                                          ; preds = %land.end15, %for.body
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1387
  %loop = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %11, i32 0, i32 1, !dbg !1389
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1389
  %signal_pipefd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 28, !dbg !1390
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd, i64 0, i64 1, !dbg !1387
  %13 = load i32, i32* %arrayidx, align 4, !dbg !1387
  %14 = bitcast %struct.uv__signal_msg_t* %msg to i8*, !dbg !1391
  %call8 = call i64 @write(i32 %13, i8* %14, i64 16), !dbg !1392
  %conv = trunc i64 %call8 to i32, !dbg !1392
  store i32 %conv, i32* %r, align 4, !dbg !1393
  br label %do.cond, !dbg !1394

do.cond:                                          ; preds = %do.body
  %15 = load i32, i32* %r, align 4, !dbg !1395
  %cmp9 = icmp eq i32 %15, -1, !dbg !1397
  br i1 %cmp9, label %land.rhs11, label %land.end15, !dbg !1398

land.rhs11:                                       ; preds = %do.cond
  %call12 = call i32* @__errno_location() #2, !dbg !1399
  %16 = load i32, i32* %call12, align 4, !dbg !1399
  %cmp13 = icmp eq i32 %16, 4, !dbg !1401
  br label %land.end15

land.end15:                                       ; preds = %land.rhs11, %do.cond
  %17 = phi i1 [ false, %do.cond ], [ %cmp13, %land.rhs11 ]
  br i1 %17, label %do.body, label %do.end, !dbg !1402

do.end:                                           ; preds = %land.end15
  %18 = load i32, i32* %r, align 4, !dbg !1404
  %conv16 = sext i32 %18 to i64, !dbg !1404
  %cmp17 = icmp eq i64 %conv16, 16, !dbg !1404
  br i1 %cmp17, label %cond.true, label %lor.lhs.false, !dbg !1404

lor.lhs.false:                                    ; preds = %do.end
  %19 = load i32, i32* %r, align 4, !dbg !1405
  %cmp19 = icmp eq i32 %19, -1, !dbg !1405
  br i1 %cmp19, label %land.lhs.true, label %cond.false, !dbg !1405

land.lhs.true:                                    ; preds = %lor.lhs.false
  %call21 = call i32* @__errno_location() #2, !dbg !1406
  %20 = load i32, i32* %call21, align 4, !dbg !1406
  %cmp22 = icmp eq i32 %20, 11, !dbg !1406
  br i1 %cmp22, label %cond.true, label %lor.lhs.false24, !dbg !1406

lor.lhs.false24:                                  ; preds = %land.lhs.true
  %call25 = call i32* @__errno_location() #2, !dbg !1407
  %21 = load i32, i32* %call25, align 4, !dbg !1407
  %cmp26 = icmp eq i32 %21, 11, !dbg !1407
  br i1 %cmp26, label %cond.true, label %cond.false, !dbg !1407

cond.true:                                        ; preds = %lor.lhs.false24, %land.lhs.true, %do.end
  br label %cond.end, !dbg !1409

cond.false:                                       ; preds = %lor.lhs.false24, %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([95 x i8], [95 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0), i32 199, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.uv__signal_handler, i32 0, i32 0)) #8, !dbg !1411
  unreachable, !dbg !1411
                                                  ; No predecessors!
  br label %cond.end, !dbg !1413

cond.end:                                         ; preds = %22, %cond.true
  %23 = load i32, i32* %r, align 4, !dbg !1415
  %cmp28 = icmp ne i32 %23, -1, !dbg !1417
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !1418

if.then30:                                        ; preds = %cond.end
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1419
  %caught_signals = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %24, i32 0, i32 11, !dbg !1420
  %25 = load i32, i32* %caught_signals, align 8, !dbg !1421
  %inc = add i32 %25, 1, !dbg !1421
  store i32 %inc, i32* %caught_signals, align 8, !dbg !1421
  br label %if.end31, !dbg !1419

if.end31:                                         ; preds = %if.then30, %cond.end
  br label %for.inc, !dbg !1422

for.inc:                                          ; preds = %if.end31
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle, align 8, !dbg !1423
  %call32 = call %struct.uv_signal_s* @uv__signal_tree_s_RB_NEXT(%struct.uv_signal_s* %26), !dbg !1423
  store %struct.uv_signal_s* %call32, %struct.uv_signal_s** %handle, align 8, !dbg !1424
  br label %for.cond, !dbg !1425

for.end:                                          ; preds = %land.end
  %call33 = call i32 @uv__signal_unlock(), !dbg !1427
  %27 = load i32, i32* %saved_errno, align 4, !dbg !1428
  %call34 = call i32* @__errno_location() #2, !dbg !1429
  store i32 %27, i32* %call34, align 4, !dbg !1430
  br label %return, !dbg !1431

return:                                           ; preds = %for.end, %if.then
  ret void, !dbg !1432
}

; Function Attrs: nounwind
declare i32 @sigaction(i32, %struct.sigaction*, %struct.sigaction*) #4

; Function Attrs: nounwind uwtable
define internal %struct.uv_signal_s* @uv__signal_tree_s_RB_NEXT(%struct.uv_signal_s* %elm) #0 !dbg !341 {
entry:
  %elm.addr = alloca %struct.uv_signal_s*, align 8
  store %struct.uv_signal_s* %elm, %struct.uv_signal_s** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %elm.addr, metadata !1434, metadata !385), !dbg !1435
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1436
  %tree_entry = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %0, i32 0, i32 10, !dbg !1436
  %rbe_right = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry, i32 0, i32 1, !dbg !1436
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right, align 8, !dbg !1436
  %tobool = icmp ne %struct.uv_signal_s* %1, null, !dbg !1436
  br i1 %tobool, label %if.then, label %if.else, !dbg !1435

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1438
  %tree_entry1 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %2, i32 0, i32 10, !dbg !1438
  %rbe_right2 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry1, i32 0, i32 1, !dbg !1438
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right2, align 8, !dbg !1438
  store %struct.uv_signal_s* %3, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1438
  br label %while.cond, !dbg !1438

while.cond:                                       ; preds = %while.body, %if.then
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1441
  %tree_entry3 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %4, i32 0, i32 10, !dbg !1441
  %rbe_left = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry3, i32 0, i32 0, !dbg !1441
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left, align 8, !dbg !1441
  %tobool4 = icmp ne %struct.uv_signal_s* %5, null, !dbg !1441
  br i1 %tobool4, label %while.body, label %while.end, !dbg !1441

while.body:                                       ; preds = %while.cond
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1443
  %tree_entry5 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %6, i32 0, i32 10, !dbg !1443
  %rbe_left6 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry5, i32 0, i32 0, !dbg !1443
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left6, align 8, !dbg !1443
  store %struct.uv_signal_s* %7, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1443
  br label %while.cond, !dbg !1443

while.end:                                        ; preds = %while.cond
  br label %if.end32, !dbg !1445

if.else:                                          ; preds = %entry
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1447
  %tree_entry7 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %8, i32 0, i32 10, !dbg !1447
  %rbe_parent = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry7, i32 0, i32 2, !dbg !1447
  %9 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent, align 8, !dbg !1447
  %tobool8 = icmp ne %struct.uv_signal_s* %9, null, !dbg !1447
  br i1 %tobool8, label %land.lhs.true, label %if.else16, !dbg !1447

land.lhs.true:                                    ; preds = %if.else
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1451
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1451
  %tree_entry9 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %11, i32 0, i32 10, !dbg !1451
  %rbe_parent10 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry9, i32 0, i32 2, !dbg !1451
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent10, align 8, !dbg !1451
  %tree_entry11 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %12, i32 0, i32 10, !dbg !1451
  %rbe_left12 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry11, i32 0, i32 0, !dbg !1451
  %13 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left12, align 8, !dbg !1451
  %cmp = icmp eq %struct.uv_signal_s* %10, %13, !dbg !1451
  br i1 %cmp, label %if.then13, label %if.else16, !dbg !1451

if.then13:                                        ; preds = %land.lhs.true
  %14 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1453
  %tree_entry14 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %14, i32 0, i32 10, !dbg !1453
  %rbe_parent15 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry14, i32 0, i32 2, !dbg !1453
  %15 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent15, align 8, !dbg !1453
  store %struct.uv_signal_s* %15, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1453
  br label %if.end, !dbg !1453

if.else16:                                        ; preds = %land.lhs.true, %if.else
  br label %while.cond17, !dbg !1455

while.cond17:                                     ; preds = %while.body26, %if.else16
  %16 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1458
  %tree_entry18 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %16, i32 0, i32 10, !dbg !1458
  %rbe_parent19 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry18, i32 0, i32 2, !dbg !1458
  %17 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent19, align 8, !dbg !1458
  %tobool20 = icmp ne %struct.uv_signal_s* %17, null, !dbg !1458
  br i1 %tobool20, label %land.rhs, label %land.end, !dbg !1458

land.rhs:                                         ; preds = %while.cond17
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1460
  %19 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1460
  %tree_entry21 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %19, i32 0, i32 10, !dbg !1460
  %rbe_parent22 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry21, i32 0, i32 2, !dbg !1460
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent22, align 8, !dbg !1460
  %tree_entry23 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %20, i32 0, i32 10, !dbg !1460
  %rbe_right24 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry23, i32 0, i32 1, !dbg !1460
  %21 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right24, align 8, !dbg !1460
  %cmp25 = icmp eq %struct.uv_signal_s* %18, %21, !dbg !1460
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond17
  %22 = phi i1 [ false, %while.cond17 ], [ %cmp25, %land.rhs ]
  br i1 %22, label %while.body26, label %while.end29, !dbg !1462

while.body26:                                     ; preds = %land.end
  %23 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1464
  %tree_entry27 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %23, i32 0, i32 10, !dbg !1464
  %rbe_parent28 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry27, i32 0, i32 2, !dbg !1464
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent28, align 8, !dbg !1464
  store %struct.uv_signal_s* %24, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1464
  br label %while.cond17, !dbg !1464

while.end29:                                      ; preds = %land.end
  %25 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1466
  %tree_entry30 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %25, i32 0, i32 10, !dbg !1466
  %rbe_parent31 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry30, i32 0, i32 2, !dbg !1466
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent31, align 8, !dbg !1466
  store %struct.uv_signal_s* %26, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1466
  br label %if.end

if.end:                                           ; preds = %while.end29, %if.then13
  br label %if.end32

if.end32:                                         ; preds = %if.end, %while.end
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1468
  ret %struct.uv_signal_s* %27, !dbg !1468
}

; Function Attrs: nounwind uwtable
define internal void @uv__signal_tree_s_RB_INSERT_COLOR(%struct.uv__signal_tree_s* %head, %struct.uv_signal_s* %elm) #0 !dbg !346 {
entry:
  %head.addr = alloca %struct.uv__signal_tree_s*, align 8
  %elm.addr = alloca %struct.uv_signal_s*, align 8
  %parent = alloca %struct.uv_signal_s*, align 8
  %gparent = alloca %struct.uv_signal_s*, align 8
  %tmp = alloca %struct.uv_signal_s*, align 8
  store %struct.uv__signal_tree_s* %head, %struct.uv__signal_tree_s** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__signal_tree_s** %head.addr, metadata !1470, metadata !385), !dbg !1471
  store %struct.uv_signal_s* %elm, %struct.uv_signal_s** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %elm.addr, metadata !1472, metadata !385), !dbg !1471
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %parent, metadata !1473, metadata !385), !dbg !1471
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %gparent, metadata !1474, metadata !385), !dbg !1471
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %tmp, metadata !1475, metadata !385), !dbg !1471
  br label %while.cond, !dbg !1471

while.cond:                                       ; preds = %if.end276, %do.end153, %do.end, %entry
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1476
  %tree_entry = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %0, i32 0, i32 10, !dbg !1476
  %rbe_parent = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry, i32 0, i32 2, !dbg !1476
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent, align 8, !dbg !1476
  store %struct.uv_signal_s* %1, %struct.uv_signal_s** %parent, align 8, !dbg !1476
  %cmp = icmp ne %struct.uv_signal_s* %1, null, !dbg !1476
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1476

land.rhs:                                         ; preds = %while.cond
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1478
  %tree_entry1 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %2, i32 0, i32 10, !dbg !1478
  %rbe_color = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry1, i32 0, i32 3, !dbg !1478
  %3 = load i32, i32* %rbe_color, align 8, !dbg !1478
  %cmp2 = icmp eq i32 %3, 1, !dbg !1478
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %4 = phi i1 [ false, %while.cond ], [ %cmp2, %land.rhs ]
  br i1 %4, label %while.body, label %while.end, !dbg !1480

while.body:                                       ; preds = %land.end
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1482
  %tree_entry3 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %5, i32 0, i32 10, !dbg !1482
  %rbe_parent4 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry3, i32 0, i32 2, !dbg !1482
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent4, align 8, !dbg !1482
  store %struct.uv_signal_s* %6, %struct.uv_signal_s** %gparent, align 8, !dbg !1482
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1482
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1482
  %tree_entry5 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %8, i32 0, i32 10, !dbg !1482
  %rbe_left = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry5, i32 0, i32 0, !dbg !1482
  %9 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left, align 8, !dbg !1482
  %cmp6 = icmp eq %struct.uv_signal_s* %7, %9, !dbg !1482
  br i1 %cmp6, label %if.then, label %if.else137, !dbg !1482

if.then:                                          ; preds = %while.body
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1485
  %tree_entry7 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %10, i32 0, i32 10, !dbg !1485
  %rbe_right = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry7, i32 0, i32 1, !dbg !1485
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right, align 8, !dbg !1485
  store %struct.uv_signal_s* %11, %struct.uv_signal_s** %tmp, align 8, !dbg !1485
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1485
  %tobool = icmp ne %struct.uv_signal_s* %12, null, !dbg !1485
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !1485

land.lhs.true:                                    ; preds = %if.then
  %13 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1489
  %tree_entry8 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %13, i32 0, i32 10, !dbg !1489
  %rbe_color9 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry8, i32 0, i32 3, !dbg !1489
  %14 = load i32, i32* %rbe_color9, align 8, !dbg !1489
  %cmp10 = icmp eq i32 %14, 1, !dbg !1489
  br i1 %cmp10, label %if.then11, label %if.end, !dbg !1489

if.then11:                                        ; preds = %land.lhs.true
  %15 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1492
  %tree_entry12 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %15, i32 0, i32 10, !dbg !1492
  %rbe_color13 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry12, i32 0, i32 3, !dbg !1492
  store i32 0, i32* %rbe_color13, align 8, !dbg !1492
  br label %do.body, !dbg !1492

do.body:                                          ; preds = %if.then11
  %16 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1495
  %tree_entry14 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %16, i32 0, i32 10, !dbg !1495
  %rbe_color15 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry14, i32 0, i32 3, !dbg !1495
  store i32 0, i32* %rbe_color15, align 8, !dbg !1495
  %17 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1495
  %tree_entry16 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %17, i32 0, i32 10, !dbg !1495
  %rbe_color17 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry16, i32 0, i32 3, !dbg !1495
  store i32 1, i32* %rbe_color17, align 8, !dbg !1495
  br label %do.end, !dbg !1495

do.end:                                           ; preds = %do.body
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1498
  store %struct.uv_signal_s* %18, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1498
  br label %while.cond, !dbg !1498

if.end:                                           ; preds = %land.lhs.true, %if.then
  %19 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1500
  %tree_entry18 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %19, i32 0, i32 10, !dbg !1500
  %rbe_right19 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry18, i32 0, i32 1, !dbg !1500
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right19, align 8, !dbg !1500
  %21 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1500
  %cmp20 = icmp eq %struct.uv_signal_s* %20, %21, !dbg !1500
  br i1 %cmp20, label %if.then21, label %if.end75, !dbg !1500

if.then21:                                        ; preds = %if.end
  br label %do.body22, !dbg !1503

do.body22:                                        ; preds = %if.then21
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1506
  %tree_entry23 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 10, !dbg !1506
  %rbe_right24 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry23, i32 0, i32 1, !dbg !1506
  %23 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right24, align 8, !dbg !1506
  store %struct.uv_signal_s* %23, %struct.uv_signal_s** %tmp, align 8, !dbg !1506
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1506
  %tree_entry25 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %24, i32 0, i32 10, !dbg !1506
  %rbe_left26 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry25, i32 0, i32 0, !dbg !1506
  %25 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left26, align 8, !dbg !1506
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1506
  %tree_entry27 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %26, i32 0, i32 10, !dbg !1506
  %rbe_right28 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry27, i32 0, i32 1, !dbg !1506
  store %struct.uv_signal_s* %25, %struct.uv_signal_s** %rbe_right28, align 8, !dbg !1506
  %cmp29 = icmp ne %struct.uv_signal_s* %25, null, !dbg !1506
  br i1 %cmp29, label %if.then30, label %if.end35, !dbg !1506

if.then30:                                        ; preds = %do.body22
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1509
  %28 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1509
  %tree_entry31 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %28, i32 0, i32 10, !dbg !1509
  %rbe_left32 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry31, i32 0, i32 0, !dbg !1509
  %29 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left32, align 8, !dbg !1509
  %tree_entry33 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %29, i32 0, i32 10, !dbg !1509
  %rbe_parent34 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry33, i32 0, i32 2, !dbg !1509
  store %struct.uv_signal_s* %27, %struct.uv_signal_s** %rbe_parent34, align 8, !dbg !1509
  br label %if.end35, !dbg !1509

if.end35:                                         ; preds = %if.then30, %do.body22
  br label %do.body36, !dbg !1513

do.body36:                                        ; preds = %if.end35
  br label %do.end37, !dbg !1515

do.end37:                                         ; preds = %do.body36
  %30 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1518
  %tree_entry38 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %30, i32 0, i32 10, !dbg !1518
  %rbe_parent39 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry38, i32 0, i32 2, !dbg !1518
  %31 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent39, align 8, !dbg !1518
  %32 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1518
  %tree_entry40 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %32, i32 0, i32 10, !dbg !1518
  %rbe_parent41 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry40, i32 0, i32 2, !dbg !1518
  store %struct.uv_signal_s* %31, %struct.uv_signal_s** %rbe_parent41, align 8, !dbg !1518
  %cmp42 = icmp ne %struct.uv_signal_s* %31, null, !dbg !1518
  br i1 %cmp42, label %if.then43, label %if.else59, !dbg !1518

if.then43:                                        ; preds = %do.end37
  %33 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1521
  %34 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1521
  %tree_entry44 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %34, i32 0, i32 10, !dbg !1521
  %rbe_parent45 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry44, i32 0, i32 2, !dbg !1521
  %35 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent45, align 8, !dbg !1521
  %tree_entry46 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %35, i32 0, i32 10, !dbg !1521
  %rbe_left47 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry46, i32 0, i32 0, !dbg !1521
  %36 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left47, align 8, !dbg !1521
  %cmp48 = icmp eq %struct.uv_signal_s* %33, %36, !dbg !1521
  br i1 %cmp48, label %if.then49, label %if.else, !dbg !1521

if.then49:                                        ; preds = %if.then43
  %37 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1525
  %38 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1525
  %tree_entry50 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %38, i32 0, i32 10, !dbg !1525
  %rbe_parent51 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry50, i32 0, i32 2, !dbg !1525
  %39 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent51, align 8, !dbg !1525
  %tree_entry52 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %39, i32 0, i32 10, !dbg !1525
  %rbe_left53 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry52, i32 0, i32 0, !dbg !1525
  store %struct.uv_signal_s* %37, %struct.uv_signal_s** %rbe_left53, align 8, !dbg !1525
  br label %if.end58, !dbg !1525

if.else:                                          ; preds = %if.then43
  %40 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1527
  %41 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1527
  %tree_entry54 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %41, i32 0, i32 10, !dbg !1527
  %rbe_parent55 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry54, i32 0, i32 2, !dbg !1527
  %42 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent55, align 8, !dbg !1527
  %tree_entry56 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %42, i32 0, i32 10, !dbg !1527
  %rbe_right57 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry56, i32 0, i32 1, !dbg !1527
  store %struct.uv_signal_s* %40, %struct.uv_signal_s** %rbe_right57, align 8, !dbg !1527
  br label %if.end58

if.end58:                                         ; preds = %if.else, %if.then49
  br label %if.end60, !dbg !1529

if.else59:                                        ; preds = %do.end37
  %43 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1531
  %44 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1531
  %rbh_root = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %44, i32 0, i32 0, !dbg !1531
  store %struct.uv_signal_s* %43, %struct.uv_signal_s** %rbh_root, align 8, !dbg !1531
  br label %if.end60

if.end60:                                         ; preds = %if.else59, %if.end58
  %45 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1533
  %46 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1533
  %tree_entry61 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %46, i32 0, i32 10, !dbg !1533
  %rbe_left62 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry61, i32 0, i32 0, !dbg !1533
  store %struct.uv_signal_s* %45, %struct.uv_signal_s** %rbe_left62, align 8, !dbg !1533
  %47 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1533
  %48 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1533
  %tree_entry63 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %48, i32 0, i32 10, !dbg !1533
  %rbe_parent64 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry63, i32 0, i32 2, !dbg !1533
  store %struct.uv_signal_s* %47, %struct.uv_signal_s** %rbe_parent64, align 8, !dbg !1533
  br label %do.body65, !dbg !1533

do.body65:                                        ; preds = %if.end60
  br label %do.end66, !dbg !1535

do.end66:                                         ; preds = %do.body65
  %49 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1538
  %tree_entry67 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %49, i32 0, i32 10, !dbg !1538
  %rbe_parent68 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry67, i32 0, i32 2, !dbg !1538
  %50 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent68, align 8, !dbg !1538
  %tobool69 = icmp ne %struct.uv_signal_s* %50, null, !dbg !1538
  br i1 %tobool69, label %if.then70, label %if.end73, !dbg !1538

if.then70:                                        ; preds = %do.end66
  br label %do.body71, !dbg !1541

do.body71:                                        ; preds = %if.then70
  br label %do.end72, !dbg !1543

do.end72:                                         ; preds = %do.body71
  br label %if.end73, !dbg !1546

if.end73:                                         ; preds = %do.end72, %do.end66
  br label %do.end74, !dbg !1548

do.end74:                                         ; preds = %if.end73
  %51 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1550
  store %struct.uv_signal_s* %51, %struct.uv_signal_s** %tmp, align 8, !dbg !1550
  %52 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1550
  store %struct.uv_signal_s* %52, %struct.uv_signal_s** %parent, align 8, !dbg !1550
  %53 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1550
  store %struct.uv_signal_s* %53, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1550
  br label %if.end75, !dbg !1550

if.end75:                                         ; preds = %do.end74, %if.end
  br label %do.body76, !dbg !1552

do.body76:                                        ; preds = %if.end75
  %54 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1554
  %tree_entry77 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %54, i32 0, i32 10, !dbg !1554
  %rbe_color78 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry77, i32 0, i32 3, !dbg !1554
  store i32 0, i32* %rbe_color78, align 8, !dbg !1554
  %55 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1554
  %tree_entry79 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %55, i32 0, i32 10, !dbg !1554
  %rbe_color80 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry79, i32 0, i32 3, !dbg !1554
  store i32 1, i32* %rbe_color80, align 8, !dbg !1554
  br label %do.end81, !dbg !1554

do.end81:                                         ; preds = %do.body76
  br label %do.body82, !dbg !1557

do.body82:                                        ; preds = %do.end81
  %56 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1559
  %tree_entry83 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %56, i32 0, i32 10, !dbg !1559
  %rbe_left84 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry83, i32 0, i32 0, !dbg !1559
  %57 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left84, align 8, !dbg !1559
  store %struct.uv_signal_s* %57, %struct.uv_signal_s** %tmp, align 8, !dbg !1559
  %58 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1559
  %tree_entry85 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %58, i32 0, i32 10, !dbg !1559
  %rbe_right86 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry85, i32 0, i32 1, !dbg !1559
  %59 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right86, align 8, !dbg !1559
  %60 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1559
  %tree_entry87 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %60, i32 0, i32 10, !dbg !1559
  %rbe_left88 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry87, i32 0, i32 0, !dbg !1559
  store %struct.uv_signal_s* %59, %struct.uv_signal_s** %rbe_left88, align 8, !dbg !1559
  %cmp89 = icmp ne %struct.uv_signal_s* %59, null, !dbg !1559
  br i1 %cmp89, label %if.then90, label %if.end95, !dbg !1559

if.then90:                                        ; preds = %do.body82
  %61 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1562
  %62 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1562
  %tree_entry91 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %62, i32 0, i32 10, !dbg !1562
  %rbe_right92 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry91, i32 0, i32 1, !dbg !1562
  %63 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right92, align 8, !dbg !1562
  %tree_entry93 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %63, i32 0, i32 10, !dbg !1562
  %rbe_parent94 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry93, i32 0, i32 2, !dbg !1562
  store %struct.uv_signal_s* %61, %struct.uv_signal_s** %rbe_parent94, align 8, !dbg !1562
  br label %if.end95, !dbg !1562

if.end95:                                         ; preds = %if.then90, %do.body82
  br label %do.body96, !dbg !1566

do.body96:                                        ; preds = %if.end95
  br label %do.end97, !dbg !1568

do.end97:                                         ; preds = %do.body96
  %64 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1571
  %tree_entry98 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %64, i32 0, i32 10, !dbg !1571
  %rbe_parent99 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry98, i32 0, i32 2, !dbg !1571
  %65 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent99, align 8, !dbg !1571
  %66 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1571
  %tree_entry100 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %66, i32 0, i32 10, !dbg !1571
  %rbe_parent101 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry100, i32 0, i32 2, !dbg !1571
  store %struct.uv_signal_s* %65, %struct.uv_signal_s** %rbe_parent101, align 8, !dbg !1571
  %cmp102 = icmp ne %struct.uv_signal_s* %65, null, !dbg !1571
  br i1 %cmp102, label %if.then103, label %if.else120, !dbg !1571

if.then103:                                       ; preds = %do.end97
  %67 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1574
  %68 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1574
  %tree_entry104 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %68, i32 0, i32 10, !dbg !1574
  %rbe_parent105 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry104, i32 0, i32 2, !dbg !1574
  %69 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent105, align 8, !dbg !1574
  %tree_entry106 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %69, i32 0, i32 10, !dbg !1574
  %rbe_left107 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry106, i32 0, i32 0, !dbg !1574
  %70 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left107, align 8, !dbg !1574
  %cmp108 = icmp eq %struct.uv_signal_s* %67, %70, !dbg !1574
  br i1 %cmp108, label %if.then109, label %if.else114, !dbg !1574

if.then109:                                       ; preds = %if.then103
  %71 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1578
  %72 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1578
  %tree_entry110 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %72, i32 0, i32 10, !dbg !1578
  %rbe_parent111 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry110, i32 0, i32 2, !dbg !1578
  %73 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent111, align 8, !dbg !1578
  %tree_entry112 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %73, i32 0, i32 10, !dbg !1578
  %rbe_left113 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry112, i32 0, i32 0, !dbg !1578
  store %struct.uv_signal_s* %71, %struct.uv_signal_s** %rbe_left113, align 8, !dbg !1578
  br label %if.end119, !dbg !1578

if.else114:                                       ; preds = %if.then103
  %74 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1580
  %75 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1580
  %tree_entry115 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %75, i32 0, i32 10, !dbg !1580
  %rbe_parent116 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry115, i32 0, i32 2, !dbg !1580
  %76 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent116, align 8, !dbg !1580
  %tree_entry117 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %76, i32 0, i32 10, !dbg !1580
  %rbe_right118 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry117, i32 0, i32 1, !dbg !1580
  store %struct.uv_signal_s* %74, %struct.uv_signal_s** %rbe_right118, align 8, !dbg !1580
  br label %if.end119

if.end119:                                        ; preds = %if.else114, %if.then109
  br label %if.end122, !dbg !1582

if.else120:                                       ; preds = %do.end97
  %77 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1584
  %78 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1584
  %rbh_root121 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %78, i32 0, i32 0, !dbg !1584
  store %struct.uv_signal_s* %77, %struct.uv_signal_s** %rbh_root121, align 8, !dbg !1584
  br label %if.end122

if.end122:                                        ; preds = %if.else120, %if.end119
  %79 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1586
  %80 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1586
  %tree_entry123 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %80, i32 0, i32 10, !dbg !1586
  %rbe_right124 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry123, i32 0, i32 1, !dbg !1586
  store %struct.uv_signal_s* %79, %struct.uv_signal_s** %rbe_right124, align 8, !dbg !1586
  %81 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1586
  %82 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1586
  %tree_entry125 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %82, i32 0, i32 10, !dbg !1586
  %rbe_parent126 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry125, i32 0, i32 2, !dbg !1586
  store %struct.uv_signal_s* %81, %struct.uv_signal_s** %rbe_parent126, align 8, !dbg !1586
  br label %do.body127, !dbg !1586

do.body127:                                       ; preds = %if.end122
  br label %do.end128, !dbg !1588

do.end128:                                        ; preds = %do.body127
  %83 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1591
  %tree_entry129 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %83, i32 0, i32 10, !dbg !1591
  %rbe_parent130 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry129, i32 0, i32 2, !dbg !1591
  %84 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent130, align 8, !dbg !1591
  %tobool131 = icmp ne %struct.uv_signal_s* %84, null, !dbg !1591
  br i1 %tobool131, label %if.then132, label %if.end135, !dbg !1591

if.then132:                                       ; preds = %do.end128
  br label %do.body133, !dbg !1594

do.body133:                                       ; preds = %if.then132
  br label %do.end134, !dbg !1596

do.end134:                                        ; preds = %do.body133
  br label %if.end135, !dbg !1599

if.end135:                                        ; preds = %do.end134, %do.end128
  br label %do.end136, !dbg !1601

do.end136:                                        ; preds = %if.end135
  br label %if.end276, !dbg !1603

if.else137:                                       ; preds = %while.body
  %85 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1605
  %tree_entry138 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %85, i32 0, i32 10, !dbg !1605
  %rbe_left139 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry138, i32 0, i32 0, !dbg !1605
  %86 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left139, align 8, !dbg !1605
  store %struct.uv_signal_s* %86, %struct.uv_signal_s** %tmp, align 8, !dbg !1605
  %87 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1605
  %tobool140 = icmp ne %struct.uv_signal_s* %87, null, !dbg !1605
  br i1 %tobool140, label %land.lhs.true141, label %if.end154, !dbg !1605

land.lhs.true141:                                 ; preds = %if.else137
  %88 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1608
  %tree_entry142 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %88, i32 0, i32 10, !dbg !1608
  %rbe_color143 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry142, i32 0, i32 3, !dbg !1608
  %89 = load i32, i32* %rbe_color143, align 8, !dbg !1608
  %cmp144 = icmp eq i32 %89, 1, !dbg !1608
  br i1 %cmp144, label %if.then145, label %if.end154, !dbg !1608

if.then145:                                       ; preds = %land.lhs.true141
  %90 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1611
  %tree_entry146 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %90, i32 0, i32 10, !dbg !1611
  %rbe_color147 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry146, i32 0, i32 3, !dbg !1611
  store i32 0, i32* %rbe_color147, align 8, !dbg !1611
  br label %do.body148, !dbg !1611

do.body148:                                       ; preds = %if.then145
  %91 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1614
  %tree_entry149 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %91, i32 0, i32 10, !dbg !1614
  %rbe_color150 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry149, i32 0, i32 3, !dbg !1614
  store i32 0, i32* %rbe_color150, align 8, !dbg !1614
  %92 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1614
  %tree_entry151 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %92, i32 0, i32 10, !dbg !1614
  %rbe_color152 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry151, i32 0, i32 3, !dbg !1614
  store i32 1, i32* %rbe_color152, align 8, !dbg !1614
  br label %do.end153, !dbg !1614

do.end153:                                        ; preds = %do.body148
  %93 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1617
  store %struct.uv_signal_s* %93, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1617
  br label %while.cond, !dbg !1617

if.end154:                                        ; preds = %land.lhs.true141, %if.else137
  %94 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1619
  %tree_entry155 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %94, i32 0, i32 10, !dbg !1619
  %rbe_left156 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry155, i32 0, i32 0, !dbg !1619
  %95 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left156, align 8, !dbg !1619
  %96 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1619
  %cmp157 = icmp eq %struct.uv_signal_s* %95, %96, !dbg !1619
  br i1 %cmp157, label %if.then158, label %if.end214, !dbg !1619

if.then158:                                       ; preds = %if.end154
  br label %do.body159, !dbg !1622

do.body159:                                       ; preds = %if.then158
  %97 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1625
  %tree_entry160 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %97, i32 0, i32 10, !dbg !1625
  %rbe_left161 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry160, i32 0, i32 0, !dbg !1625
  %98 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left161, align 8, !dbg !1625
  store %struct.uv_signal_s* %98, %struct.uv_signal_s** %tmp, align 8, !dbg !1625
  %99 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1625
  %tree_entry162 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %99, i32 0, i32 10, !dbg !1625
  %rbe_right163 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry162, i32 0, i32 1, !dbg !1625
  %100 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right163, align 8, !dbg !1625
  %101 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1625
  %tree_entry164 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %101, i32 0, i32 10, !dbg !1625
  %rbe_left165 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry164, i32 0, i32 0, !dbg !1625
  store %struct.uv_signal_s* %100, %struct.uv_signal_s** %rbe_left165, align 8, !dbg !1625
  %cmp166 = icmp ne %struct.uv_signal_s* %100, null, !dbg !1625
  br i1 %cmp166, label %if.then167, label %if.end172, !dbg !1625

if.then167:                                       ; preds = %do.body159
  %102 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1628
  %103 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1628
  %tree_entry168 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %103, i32 0, i32 10, !dbg !1628
  %rbe_right169 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry168, i32 0, i32 1, !dbg !1628
  %104 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right169, align 8, !dbg !1628
  %tree_entry170 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %104, i32 0, i32 10, !dbg !1628
  %rbe_parent171 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry170, i32 0, i32 2, !dbg !1628
  store %struct.uv_signal_s* %102, %struct.uv_signal_s** %rbe_parent171, align 8, !dbg !1628
  br label %if.end172, !dbg !1628

if.end172:                                        ; preds = %if.then167, %do.body159
  br label %do.body173, !dbg !1632

do.body173:                                       ; preds = %if.end172
  br label %do.end174, !dbg !1634

do.end174:                                        ; preds = %do.body173
  %105 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1637
  %tree_entry175 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %105, i32 0, i32 10, !dbg !1637
  %rbe_parent176 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry175, i32 0, i32 2, !dbg !1637
  %106 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent176, align 8, !dbg !1637
  %107 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1637
  %tree_entry177 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %107, i32 0, i32 10, !dbg !1637
  %rbe_parent178 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry177, i32 0, i32 2, !dbg !1637
  store %struct.uv_signal_s* %106, %struct.uv_signal_s** %rbe_parent178, align 8, !dbg !1637
  %cmp179 = icmp ne %struct.uv_signal_s* %106, null, !dbg !1637
  br i1 %cmp179, label %if.then180, label %if.else197, !dbg !1637

if.then180:                                       ; preds = %do.end174
  %108 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1640
  %109 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1640
  %tree_entry181 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %109, i32 0, i32 10, !dbg !1640
  %rbe_parent182 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry181, i32 0, i32 2, !dbg !1640
  %110 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent182, align 8, !dbg !1640
  %tree_entry183 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %110, i32 0, i32 10, !dbg !1640
  %rbe_left184 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry183, i32 0, i32 0, !dbg !1640
  %111 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left184, align 8, !dbg !1640
  %cmp185 = icmp eq %struct.uv_signal_s* %108, %111, !dbg !1640
  br i1 %cmp185, label %if.then186, label %if.else191, !dbg !1640

if.then186:                                       ; preds = %if.then180
  %112 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1644
  %113 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1644
  %tree_entry187 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %113, i32 0, i32 10, !dbg !1644
  %rbe_parent188 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry187, i32 0, i32 2, !dbg !1644
  %114 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent188, align 8, !dbg !1644
  %tree_entry189 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %114, i32 0, i32 10, !dbg !1644
  %rbe_left190 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry189, i32 0, i32 0, !dbg !1644
  store %struct.uv_signal_s* %112, %struct.uv_signal_s** %rbe_left190, align 8, !dbg !1644
  br label %if.end196, !dbg !1644

if.else191:                                       ; preds = %if.then180
  %115 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1646
  %116 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1646
  %tree_entry192 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %116, i32 0, i32 10, !dbg !1646
  %rbe_parent193 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry192, i32 0, i32 2, !dbg !1646
  %117 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent193, align 8, !dbg !1646
  %tree_entry194 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %117, i32 0, i32 10, !dbg !1646
  %rbe_right195 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry194, i32 0, i32 1, !dbg !1646
  store %struct.uv_signal_s* %115, %struct.uv_signal_s** %rbe_right195, align 8, !dbg !1646
  br label %if.end196

if.end196:                                        ; preds = %if.else191, %if.then186
  br label %if.end199, !dbg !1648

if.else197:                                       ; preds = %do.end174
  %118 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1650
  %119 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1650
  %rbh_root198 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %119, i32 0, i32 0, !dbg !1650
  store %struct.uv_signal_s* %118, %struct.uv_signal_s** %rbh_root198, align 8, !dbg !1650
  br label %if.end199

if.end199:                                        ; preds = %if.else197, %if.end196
  %120 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1652
  %121 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1652
  %tree_entry200 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %121, i32 0, i32 10, !dbg !1652
  %rbe_right201 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry200, i32 0, i32 1, !dbg !1652
  store %struct.uv_signal_s* %120, %struct.uv_signal_s** %rbe_right201, align 8, !dbg !1652
  %122 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1652
  %123 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1652
  %tree_entry202 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %123, i32 0, i32 10, !dbg !1652
  %rbe_parent203 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry202, i32 0, i32 2, !dbg !1652
  store %struct.uv_signal_s* %122, %struct.uv_signal_s** %rbe_parent203, align 8, !dbg !1652
  br label %do.body204, !dbg !1652

do.body204:                                       ; preds = %if.end199
  br label %do.end205, !dbg !1654

do.end205:                                        ; preds = %do.body204
  %124 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1657
  %tree_entry206 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %124, i32 0, i32 10, !dbg !1657
  %rbe_parent207 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry206, i32 0, i32 2, !dbg !1657
  %125 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent207, align 8, !dbg !1657
  %tobool208 = icmp ne %struct.uv_signal_s* %125, null, !dbg !1657
  br i1 %tobool208, label %if.then209, label %if.end212, !dbg !1657

if.then209:                                       ; preds = %do.end205
  br label %do.body210, !dbg !1660

do.body210:                                       ; preds = %if.then209
  br label %do.end211, !dbg !1662

do.end211:                                        ; preds = %do.body210
  br label %if.end212, !dbg !1665

if.end212:                                        ; preds = %do.end211, %do.end205
  br label %do.end213, !dbg !1667

do.end213:                                        ; preds = %if.end212
  %126 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1669
  store %struct.uv_signal_s* %126, %struct.uv_signal_s** %tmp, align 8, !dbg !1669
  %127 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1669
  store %struct.uv_signal_s* %127, %struct.uv_signal_s** %parent, align 8, !dbg !1669
  %128 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1669
  store %struct.uv_signal_s* %128, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1669
  br label %if.end214, !dbg !1669

if.end214:                                        ; preds = %do.end213, %if.end154
  br label %do.body215, !dbg !1671

do.body215:                                       ; preds = %if.end214
  %129 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1673
  %tree_entry216 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %129, i32 0, i32 10, !dbg !1673
  %rbe_color217 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry216, i32 0, i32 3, !dbg !1673
  store i32 0, i32* %rbe_color217, align 8, !dbg !1673
  %130 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1673
  %tree_entry218 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %130, i32 0, i32 10, !dbg !1673
  %rbe_color219 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry218, i32 0, i32 3, !dbg !1673
  store i32 1, i32* %rbe_color219, align 8, !dbg !1673
  br label %do.end220, !dbg !1673

do.end220:                                        ; preds = %do.body215
  br label %do.body221, !dbg !1676

do.body221:                                       ; preds = %do.end220
  %131 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1678
  %tree_entry222 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %131, i32 0, i32 10, !dbg !1678
  %rbe_right223 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry222, i32 0, i32 1, !dbg !1678
  %132 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right223, align 8, !dbg !1678
  store %struct.uv_signal_s* %132, %struct.uv_signal_s** %tmp, align 8, !dbg !1678
  %133 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1678
  %tree_entry224 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %133, i32 0, i32 10, !dbg !1678
  %rbe_left225 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry224, i32 0, i32 0, !dbg !1678
  %134 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left225, align 8, !dbg !1678
  %135 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1678
  %tree_entry226 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %135, i32 0, i32 10, !dbg !1678
  %rbe_right227 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry226, i32 0, i32 1, !dbg !1678
  store %struct.uv_signal_s* %134, %struct.uv_signal_s** %rbe_right227, align 8, !dbg !1678
  %cmp228 = icmp ne %struct.uv_signal_s* %134, null, !dbg !1678
  br i1 %cmp228, label %if.then229, label %if.end234, !dbg !1678

if.then229:                                       ; preds = %do.body221
  %136 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1681
  %137 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1681
  %tree_entry230 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %137, i32 0, i32 10, !dbg !1681
  %rbe_left231 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry230, i32 0, i32 0, !dbg !1681
  %138 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left231, align 8, !dbg !1681
  %tree_entry232 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %138, i32 0, i32 10, !dbg !1681
  %rbe_parent233 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry232, i32 0, i32 2, !dbg !1681
  store %struct.uv_signal_s* %136, %struct.uv_signal_s** %rbe_parent233, align 8, !dbg !1681
  br label %if.end234, !dbg !1681

if.end234:                                        ; preds = %if.then229, %do.body221
  br label %do.body235, !dbg !1685

do.body235:                                       ; preds = %if.end234
  br label %do.end236, !dbg !1687

do.end236:                                        ; preds = %do.body235
  %139 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1690
  %tree_entry237 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %139, i32 0, i32 10, !dbg !1690
  %rbe_parent238 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry237, i32 0, i32 2, !dbg !1690
  %140 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent238, align 8, !dbg !1690
  %141 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1690
  %tree_entry239 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %141, i32 0, i32 10, !dbg !1690
  %rbe_parent240 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry239, i32 0, i32 2, !dbg !1690
  store %struct.uv_signal_s* %140, %struct.uv_signal_s** %rbe_parent240, align 8, !dbg !1690
  %cmp241 = icmp ne %struct.uv_signal_s* %140, null, !dbg !1690
  br i1 %cmp241, label %if.then242, label %if.else259, !dbg !1690

if.then242:                                       ; preds = %do.end236
  %142 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1693
  %143 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1693
  %tree_entry243 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %143, i32 0, i32 10, !dbg !1693
  %rbe_parent244 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry243, i32 0, i32 2, !dbg !1693
  %144 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent244, align 8, !dbg !1693
  %tree_entry245 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %144, i32 0, i32 10, !dbg !1693
  %rbe_left246 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry245, i32 0, i32 0, !dbg !1693
  %145 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left246, align 8, !dbg !1693
  %cmp247 = icmp eq %struct.uv_signal_s* %142, %145, !dbg !1693
  br i1 %cmp247, label %if.then248, label %if.else253, !dbg !1693

if.then248:                                       ; preds = %if.then242
  %146 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1697
  %147 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1697
  %tree_entry249 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %147, i32 0, i32 10, !dbg !1697
  %rbe_parent250 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry249, i32 0, i32 2, !dbg !1697
  %148 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent250, align 8, !dbg !1697
  %tree_entry251 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %148, i32 0, i32 10, !dbg !1697
  %rbe_left252 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry251, i32 0, i32 0, !dbg !1697
  store %struct.uv_signal_s* %146, %struct.uv_signal_s** %rbe_left252, align 8, !dbg !1697
  br label %if.end258, !dbg !1697

if.else253:                                       ; preds = %if.then242
  %149 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1699
  %150 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1699
  %tree_entry254 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %150, i32 0, i32 10, !dbg !1699
  %rbe_parent255 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry254, i32 0, i32 2, !dbg !1699
  %151 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent255, align 8, !dbg !1699
  %tree_entry256 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %151, i32 0, i32 10, !dbg !1699
  %rbe_right257 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry256, i32 0, i32 1, !dbg !1699
  store %struct.uv_signal_s* %149, %struct.uv_signal_s** %rbe_right257, align 8, !dbg !1699
  br label %if.end258

if.end258:                                        ; preds = %if.else253, %if.then248
  br label %if.end261, !dbg !1701

if.else259:                                       ; preds = %do.end236
  %152 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1703
  %153 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1703
  %rbh_root260 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %153, i32 0, i32 0, !dbg !1703
  store %struct.uv_signal_s* %152, %struct.uv_signal_s** %rbh_root260, align 8, !dbg !1703
  br label %if.end261

if.end261:                                        ; preds = %if.else259, %if.end258
  %154 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1705
  %155 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1705
  %tree_entry262 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %155, i32 0, i32 10, !dbg !1705
  %rbe_left263 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry262, i32 0, i32 0, !dbg !1705
  store %struct.uv_signal_s* %154, %struct.uv_signal_s** %rbe_left263, align 8, !dbg !1705
  %156 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1705
  %157 = load %struct.uv_signal_s*, %struct.uv_signal_s** %gparent, align 8, !dbg !1705
  %tree_entry264 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %157, i32 0, i32 10, !dbg !1705
  %rbe_parent265 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry264, i32 0, i32 2, !dbg !1705
  store %struct.uv_signal_s* %156, %struct.uv_signal_s** %rbe_parent265, align 8, !dbg !1705
  br label %do.body266, !dbg !1705

do.body266:                                       ; preds = %if.end261
  br label %do.end267, !dbg !1707

do.end267:                                        ; preds = %do.body266
  %158 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1710
  %tree_entry268 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %158, i32 0, i32 10, !dbg !1710
  %rbe_parent269 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry268, i32 0, i32 2, !dbg !1710
  %159 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent269, align 8, !dbg !1710
  %tobool270 = icmp ne %struct.uv_signal_s* %159, null, !dbg !1710
  br i1 %tobool270, label %if.then271, label %if.end274, !dbg !1710

if.then271:                                       ; preds = %do.end267
  br label %do.body272, !dbg !1713

do.body272:                                       ; preds = %if.then271
  br label %do.end273, !dbg !1715

do.end273:                                        ; preds = %do.body272
  br label %if.end274, !dbg !1718

if.end274:                                        ; preds = %do.end273, %do.end267
  br label %do.end275, !dbg !1720

do.end275:                                        ; preds = %if.end274
  br label %if.end276

if.end276:                                        ; preds = %do.end275, %do.end136
  br label %while.cond, !dbg !1722

while.end:                                        ; preds = %land.end
  %160 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1724
  %rbh_root277 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %160, i32 0, i32 0, !dbg !1724
  %161 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbh_root277, align 8, !dbg !1724
  %tree_entry278 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %161, i32 0, i32 10, !dbg !1724
  %rbe_color279 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry278, i32 0, i32 3, !dbg !1724
  store i32 0, i32* %rbe_color279, align 8, !dbg !1724
  ret void, !dbg !1724
}

; Function Attrs: nounwind uwtable
define internal %struct.uv_signal_s* @uv__signal_tree_s_RB_REMOVE(%struct.uv__signal_tree_s* %head, %struct.uv_signal_s* %elm) #0 !dbg !350 {
entry:
  %head.addr = alloca %struct.uv__signal_tree_s*, align 8
  %elm.addr = alloca %struct.uv_signal_s*, align 8
  %child = alloca %struct.uv_signal_s*, align 8
  %parent = alloca %struct.uv_signal_s*, align 8
  %old = alloca %struct.uv_signal_s*, align 8
  %color = alloca i32, align 4
  %left = alloca %struct.uv_signal_s*, align 8
  store %struct.uv__signal_tree_s* %head, %struct.uv__signal_tree_s** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__signal_tree_s** %head.addr, metadata !1726, metadata !385), !dbg !1727
  store %struct.uv_signal_s* %elm, %struct.uv_signal_s** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %elm.addr, metadata !1728, metadata !385), !dbg !1727
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %child, metadata !1729, metadata !385), !dbg !1727
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %parent, metadata !1730, metadata !385), !dbg !1727
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %old, metadata !1731, metadata !385), !dbg !1727
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1727
  store %struct.uv_signal_s* %0, %struct.uv_signal_s** %old, align 8, !dbg !1727
  call void @llvm.dbg.declare(metadata i32* %color, metadata !1732, metadata !385), !dbg !1727
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1733
  %tree_entry = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %1, i32 0, i32 10, !dbg !1733
  %rbe_left = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry, i32 0, i32 0, !dbg !1733
  %2 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left, align 8, !dbg !1733
  %cmp = icmp eq %struct.uv_signal_s* %2, null, !dbg !1733
  br i1 %cmp, label %if.then, label %if.else, !dbg !1727

if.then:                                          ; preds = %entry
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1735
  %tree_entry1 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %3, i32 0, i32 10, !dbg !1735
  %rbe_right = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry1, i32 0, i32 1, !dbg !1735
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right, align 8, !dbg !1735
  store %struct.uv_signal_s* %4, %struct.uv_signal_s** %child, align 8, !dbg !1735
  br label %if.end91, !dbg !1735

if.else:                                          ; preds = %entry
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1737
  %tree_entry2 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %5, i32 0, i32 10, !dbg !1737
  %rbe_right3 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry2, i32 0, i32 1, !dbg !1737
  %6 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right3, align 8, !dbg !1737
  %cmp4 = icmp eq %struct.uv_signal_s* %6, null, !dbg !1737
  br i1 %cmp4, label %if.then5, label %if.else8, !dbg !1737

if.then5:                                         ; preds = %if.else
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1740
  %tree_entry6 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %7, i32 0, i32 10, !dbg !1740
  %rbe_left7 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry6, i32 0, i32 0, !dbg !1740
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left7, align 8, !dbg !1740
  store %struct.uv_signal_s* %8, %struct.uv_signal_s** %child, align 8, !dbg !1740
  br label %if.end90, !dbg !1740

if.else8:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %left, metadata !1742, metadata !385), !dbg !1744
  %9 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1745
  %tree_entry9 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %9, i32 0, i32 10, !dbg !1745
  %rbe_right10 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry9, i32 0, i32 1, !dbg !1745
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right10, align 8, !dbg !1745
  store %struct.uv_signal_s* %10, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1745
  br label %while.cond, !dbg !1745

while.cond:                                       ; preds = %while.body, %if.else8
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1747
  %tree_entry11 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %11, i32 0, i32 10, !dbg !1747
  %rbe_left12 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry11, i32 0, i32 0, !dbg !1747
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left12, align 8, !dbg !1747
  store %struct.uv_signal_s* %12, %struct.uv_signal_s** %left, align 8, !dbg !1747
  %cmp13 = icmp ne %struct.uv_signal_s* %12, null, !dbg !1747
  br i1 %cmp13, label %while.body, label %while.end, !dbg !1747

while.body:                                       ; preds = %while.cond
  %13 = load %struct.uv_signal_s*, %struct.uv_signal_s** %left, align 8, !dbg !1749
  store %struct.uv_signal_s* %13, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1749
  br label %while.cond, !dbg !1749

while.end:                                        ; preds = %while.cond
  %14 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1751
  %tree_entry14 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %14, i32 0, i32 10, !dbg !1751
  %rbe_right15 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry14, i32 0, i32 1, !dbg !1751
  %15 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right15, align 8, !dbg !1751
  store %struct.uv_signal_s* %15, %struct.uv_signal_s** %child, align 8, !dbg !1751
  %16 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1751
  %tree_entry16 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %16, i32 0, i32 10, !dbg !1751
  %rbe_parent = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry16, i32 0, i32 2, !dbg !1751
  %17 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent, align 8, !dbg !1751
  store %struct.uv_signal_s* %17, %struct.uv_signal_s** %parent, align 8, !dbg !1751
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1751
  %tree_entry17 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %18, i32 0, i32 10, !dbg !1751
  %rbe_color = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry17, i32 0, i32 3, !dbg !1751
  %19 = load i32, i32* %rbe_color, align 8, !dbg !1751
  store i32 %19, i32* %color, align 4, !dbg !1751
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1751
  %tobool = icmp ne %struct.uv_signal_s* %20, null, !dbg !1751
  br i1 %tobool, label %if.then18, label %if.end, !dbg !1751

if.then18:                                        ; preds = %while.end
  %21 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1753
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1753
  %tree_entry19 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 10, !dbg !1753
  %rbe_parent20 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry19, i32 0, i32 2, !dbg !1753
  store %struct.uv_signal_s* %21, %struct.uv_signal_s** %rbe_parent20, align 8, !dbg !1753
  br label %if.end, !dbg !1753

if.end:                                           ; preds = %if.then18, %while.end
  %23 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1756
  %tobool21 = icmp ne %struct.uv_signal_s* %23, null, !dbg !1756
  br i1 %tobool21, label %if.then22, label %if.else33, !dbg !1756

if.then22:                                        ; preds = %if.end
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1759
  %tree_entry23 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %24, i32 0, i32 10, !dbg !1759
  %rbe_left24 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry23, i32 0, i32 0, !dbg !1759
  %25 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left24, align 8, !dbg !1759
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1759
  %cmp25 = icmp eq %struct.uv_signal_s* %25, %26, !dbg !1759
  br i1 %cmp25, label %if.then26, label %if.else29, !dbg !1759

if.then26:                                        ; preds = %if.then22
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1763
  %28 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1763
  %tree_entry27 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %28, i32 0, i32 10, !dbg !1763
  %rbe_left28 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry27, i32 0, i32 0, !dbg !1763
  store %struct.uv_signal_s* %27, %struct.uv_signal_s** %rbe_left28, align 8, !dbg !1763
  br label %if.end32, !dbg !1763

if.else29:                                        ; preds = %if.then22
  %29 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1765
  %30 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1765
  %tree_entry30 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %30, i32 0, i32 10, !dbg !1765
  %rbe_right31 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry30, i32 0, i32 1, !dbg !1765
  store %struct.uv_signal_s* %29, %struct.uv_signal_s** %rbe_right31, align 8, !dbg !1765
  br label %if.end32

if.end32:                                         ; preds = %if.else29, %if.then26
  br label %do.body, !dbg !1767

do.body:                                          ; preds = %if.end32
  br label %do.end, !dbg !1769

do.end:                                           ; preds = %do.body
  br label %if.end34, !dbg !1772

if.else33:                                        ; preds = %if.end
  %31 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1774
  %32 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1774
  %rbh_root = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %32, i32 0, i32 0, !dbg !1774
  store %struct.uv_signal_s* %31, %struct.uv_signal_s** %rbh_root, align 8, !dbg !1774
  br label %if.end34

if.end34:                                         ; preds = %if.else33, %do.end
  %33 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1776
  %tree_entry35 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %33, i32 0, i32 10, !dbg !1776
  %rbe_parent36 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry35, i32 0, i32 2, !dbg !1776
  %34 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent36, align 8, !dbg !1776
  %35 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1776
  %cmp37 = icmp eq %struct.uv_signal_s* %34, %35, !dbg !1776
  br i1 %cmp37, label %if.then38, label %if.end39, !dbg !1776

if.then38:                                        ; preds = %if.end34
  %36 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1779
  store %struct.uv_signal_s* %36, %struct.uv_signal_s** %parent, align 8, !dbg !1779
  br label %if.end39, !dbg !1779

if.end39:                                         ; preds = %if.then38, %if.end34
  %37 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1781
  %tree_entry40 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %37, i32 0, i32 10, !dbg !1781
  %38 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1781
  %tree_entry41 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %38, i32 0, i32 10, !dbg !1781
  %39 = bitcast %struct.anon.3* %tree_entry40 to i8*, !dbg !1781
  %40 = bitcast %struct.anon.3* %tree_entry41 to i8*, !dbg !1781
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %39, i8* %40, i64 32, i32 8, i1 false), !dbg !1781
  %41 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1781
  %tree_entry42 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %41, i32 0, i32 10, !dbg !1781
  %rbe_parent43 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry42, i32 0, i32 2, !dbg !1781
  %42 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent43, align 8, !dbg !1781
  %tobool44 = icmp ne %struct.uv_signal_s* %42, null, !dbg !1781
  br i1 %tobool44, label %if.then45, label %if.else64, !dbg !1781

if.then45:                                        ; preds = %if.end39
  %43 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1783
  %tree_entry46 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %43, i32 0, i32 10, !dbg !1783
  %rbe_parent47 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry46, i32 0, i32 2, !dbg !1783
  %44 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent47, align 8, !dbg !1783
  %tree_entry48 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %44, i32 0, i32 10, !dbg !1783
  %rbe_left49 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry48, i32 0, i32 0, !dbg !1783
  %45 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left49, align 8, !dbg !1783
  %46 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1783
  %cmp50 = icmp eq %struct.uv_signal_s* %45, %46, !dbg !1783
  br i1 %cmp50, label %if.then51, label %if.else56, !dbg !1783

if.then51:                                        ; preds = %if.then45
  %47 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1788
  %48 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1788
  %tree_entry52 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %48, i32 0, i32 10, !dbg !1788
  %rbe_parent53 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry52, i32 0, i32 2, !dbg !1788
  %49 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent53, align 8, !dbg !1788
  %tree_entry54 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %49, i32 0, i32 10, !dbg !1788
  %rbe_left55 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry54, i32 0, i32 0, !dbg !1788
  store %struct.uv_signal_s* %47, %struct.uv_signal_s** %rbe_left55, align 8, !dbg !1788
  br label %if.end61, !dbg !1788

if.else56:                                        ; preds = %if.then45
  %50 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1790
  %51 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1790
  %tree_entry57 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %51, i32 0, i32 10, !dbg !1790
  %rbe_parent58 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry57, i32 0, i32 2, !dbg !1790
  %52 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent58, align 8, !dbg !1790
  %tree_entry59 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %52, i32 0, i32 10, !dbg !1790
  %rbe_right60 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry59, i32 0, i32 1, !dbg !1790
  store %struct.uv_signal_s* %50, %struct.uv_signal_s** %rbe_right60, align 8, !dbg !1790
  br label %if.end61

if.end61:                                         ; preds = %if.else56, %if.then51
  br label %do.body62, !dbg !1792

do.body62:                                        ; preds = %if.end61
  br label %do.end63, !dbg !1794

do.end63:                                         ; preds = %do.body62
  br label %if.end66, !dbg !1797

if.else64:                                        ; preds = %if.end39
  %53 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1799
  %54 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1799
  %rbh_root65 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %54, i32 0, i32 0, !dbg !1799
  store %struct.uv_signal_s* %53, %struct.uv_signal_s** %rbh_root65, align 8, !dbg !1799
  br label %if.end66

if.end66:                                         ; preds = %if.else64, %do.end63
  %55 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1801
  %56 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1801
  %tree_entry67 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %56, i32 0, i32 10, !dbg !1801
  %rbe_left68 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry67, i32 0, i32 0, !dbg !1801
  %57 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left68, align 8, !dbg !1801
  %tree_entry69 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %57, i32 0, i32 10, !dbg !1801
  %rbe_parent70 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry69, i32 0, i32 2, !dbg !1801
  store %struct.uv_signal_s* %55, %struct.uv_signal_s** %rbe_parent70, align 8, !dbg !1801
  %58 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1801
  %tree_entry71 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %58, i32 0, i32 10, !dbg !1801
  %rbe_right72 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry71, i32 0, i32 1, !dbg !1801
  %59 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right72, align 8, !dbg !1801
  %tobool73 = icmp ne %struct.uv_signal_s* %59, null, !dbg !1801
  br i1 %tobool73, label %if.then74, label %if.end79, !dbg !1801

if.then74:                                        ; preds = %if.end66
  %60 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1803
  %61 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1803
  %tree_entry75 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %61, i32 0, i32 10, !dbg !1803
  %rbe_right76 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry75, i32 0, i32 1, !dbg !1803
  %62 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right76, align 8, !dbg !1803
  %tree_entry77 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %62, i32 0, i32 10, !dbg !1803
  %rbe_parent78 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry77, i32 0, i32 2, !dbg !1803
  store %struct.uv_signal_s* %60, %struct.uv_signal_s** %rbe_parent78, align 8, !dbg !1803
  br label %if.end79, !dbg !1803

if.end79:                                         ; preds = %if.then74, %if.end66
  %63 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1806
  %tobool80 = icmp ne %struct.uv_signal_s* %63, null, !dbg !1806
  br i1 %tobool80, label %if.then81, label %if.end89, !dbg !1806

if.then81:                                        ; preds = %if.end79
  %64 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1809
  store %struct.uv_signal_s* %64, %struct.uv_signal_s** %left, align 8, !dbg !1809
  br label %do.body82, !dbg !1809

do.body82:                                        ; preds = %do.cond, %if.then81
  br label %do.body83, !dbg !1812

do.body83:                                        ; preds = %do.body82
  br label %do.end84, !dbg !1815

do.end84:                                         ; preds = %do.body83
  br label %do.cond, !dbg !1818

do.cond:                                          ; preds = %do.end84
  %65 = load %struct.uv_signal_s*, %struct.uv_signal_s** %left, align 8, !dbg !1820
  %tree_entry85 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %65, i32 0, i32 10, !dbg !1820
  %rbe_parent86 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry85, i32 0, i32 2, !dbg !1820
  %66 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent86, align 8, !dbg !1820
  store %struct.uv_signal_s* %66, %struct.uv_signal_s** %left, align 8, !dbg !1820
  %cmp87 = icmp ne %struct.uv_signal_s* %66, null, !dbg !1820
  br i1 %cmp87, label %do.body82, label %do.end88, !dbg !1820

do.end88:                                         ; preds = %do.cond
  br label %if.end89, !dbg !1822

if.end89:                                         ; preds = %do.end88, %if.end79
  br label %color119, !dbg !1824

if.end90:                                         ; preds = %if.then5
  br label %if.end91

if.end91:                                         ; preds = %if.end90, %if.then
  %67 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1826
  %tree_entry92 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %67, i32 0, i32 10, !dbg !1826
  %rbe_parent93 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry92, i32 0, i32 2, !dbg !1826
  %68 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent93, align 8, !dbg !1826
  store %struct.uv_signal_s* %68, %struct.uv_signal_s** %parent, align 8, !dbg !1826
  %69 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1826
  %tree_entry94 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %69, i32 0, i32 10, !dbg !1826
  %rbe_color95 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry94, i32 0, i32 3, !dbg !1826
  %70 = load i32, i32* %rbe_color95, align 8, !dbg !1826
  store i32 %70, i32* %color, align 4, !dbg !1826
  %71 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1826
  %tobool96 = icmp ne %struct.uv_signal_s* %71, null, !dbg !1826
  br i1 %tobool96, label %if.then97, label %if.end100, !dbg !1826

if.then97:                                        ; preds = %if.end91
  %72 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1828
  %73 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1828
  %tree_entry98 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %73, i32 0, i32 10, !dbg !1828
  %rbe_parent99 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry98, i32 0, i32 2, !dbg !1828
  store %struct.uv_signal_s* %72, %struct.uv_signal_s** %rbe_parent99, align 8, !dbg !1828
  br label %if.end100, !dbg !1828

if.end100:                                        ; preds = %if.then97, %if.end91
  %74 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1831
  %tobool101 = icmp ne %struct.uv_signal_s* %74, null, !dbg !1831
  br i1 %tobool101, label %if.then102, label %if.else116, !dbg !1831

if.then102:                                       ; preds = %if.end100
  %75 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1834
  %tree_entry103 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %75, i32 0, i32 10, !dbg !1834
  %rbe_left104 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry103, i32 0, i32 0, !dbg !1834
  %76 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left104, align 8, !dbg !1834
  %77 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1834
  %cmp105 = icmp eq %struct.uv_signal_s* %76, %77, !dbg !1834
  br i1 %cmp105, label %if.then106, label %if.else109, !dbg !1834

if.then106:                                       ; preds = %if.then102
  %78 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1838
  %79 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1838
  %tree_entry107 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %79, i32 0, i32 10, !dbg !1838
  %rbe_left108 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry107, i32 0, i32 0, !dbg !1838
  store %struct.uv_signal_s* %78, %struct.uv_signal_s** %rbe_left108, align 8, !dbg !1838
  br label %if.end112, !dbg !1838

if.else109:                                       ; preds = %if.then102
  %80 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1840
  %81 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1840
  %tree_entry110 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %81, i32 0, i32 10, !dbg !1840
  %rbe_right111 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry110, i32 0, i32 1, !dbg !1840
  store %struct.uv_signal_s* %80, %struct.uv_signal_s** %rbe_right111, align 8, !dbg !1840
  br label %if.end112

if.end112:                                        ; preds = %if.else109, %if.then106
  br label %do.body113, !dbg !1842

do.body113:                                       ; preds = %if.end112
  br label %do.end115, !dbg !1844

do.end115:                                        ; preds = %do.body113
  br label %if.end118, !dbg !1847

if.else116:                                       ; preds = %if.end100
  %82 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1849
  %83 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1849
  %rbh_root117 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %83, i32 0, i32 0, !dbg !1849
  store %struct.uv_signal_s* %82, %struct.uv_signal_s** %rbh_root117, align 8, !dbg !1849
  br label %if.end118

if.end118:                                        ; preds = %if.else116, %do.end115
  br label %color119, !dbg !1851

color119:                                         ; preds = %if.end118, %if.end89
  %84 = load i32, i32* %color, align 4, !dbg !1853
  %cmp120 = icmp eq i32 %84, 0, !dbg !1853
  br i1 %cmp120, label %if.then121, label %if.end122, !dbg !1853

if.then121:                                       ; preds = %color119
  %85 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1856
  %86 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent, align 8, !dbg !1856
  %87 = load %struct.uv_signal_s*, %struct.uv_signal_s** %child, align 8, !dbg !1856
  call void @uv__signal_tree_s_RB_REMOVE_COLOR(%struct.uv__signal_tree_s* %85, %struct.uv_signal_s* %86, %struct.uv_signal_s* %87), !dbg !1856
  br label %if.end122, !dbg !1856

if.end122:                                        ; preds = %if.then121, %color119
  %88 = load %struct.uv_signal_s*, %struct.uv_signal_s** %old, align 8, !dbg !1858
  ret %struct.uv_signal_s* %88, !dbg !1858
}

; Function Attrs: nounwind uwtable
define internal void @uv__signal_unregister_handler(i32 %signum) #0 !dbg !354 {
entry:
  %signum.addr = alloca i32, align 4
  %sa = alloca %struct.sigaction, align 8
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1860, metadata !385), !dbg !1861
  call void @llvm.dbg.declare(metadata %struct.sigaction* %sa, metadata !1862, metadata !385), !dbg !1863
  %0 = bitcast %struct.sigaction* %sa to i8*, !dbg !1864
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 152, i32 8, i1 false), !dbg !1864
  %__sigaction_handler = getelementptr inbounds %struct.sigaction, %struct.sigaction* %sa, i32 0, i32 0, !dbg !1865
  %sa_handler = bitcast %union.anon.4* %__sigaction_handler to void (i32)**, !dbg !1865
  store void (i32)* null, void (i32)** %sa_handler, align 8, !dbg !1866
  %1 = load i32, i32* %signum.addr, align 4, !dbg !1867
  %call = call i32 @sigaction(i32 %1, %struct.sigaction* %sa, %struct.sigaction* null) #7, !dbg !1869
  %tobool = icmp ne i32 %call, 0, !dbg !1869
  br i1 %tobool, label %if.then, label %if.end, !dbg !1870

if.then:                                          ; preds = %entry
  call void @abort() #8, !dbg !1871
  unreachable, !dbg !1871

if.end:                                           ; preds = %entry
  ret void, !dbg !1872
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal void @uv__signal_tree_s_RB_REMOVE_COLOR(%struct.uv__signal_tree_s* %head, %struct.uv_signal_s* %parent, %struct.uv_signal_s* %elm) #0 !dbg !351 {
entry:
  %head.addr = alloca %struct.uv__signal_tree_s*, align 8
  %parent.addr = alloca %struct.uv_signal_s*, align 8
  %elm.addr = alloca %struct.uv_signal_s*, align 8
  %tmp = alloca %struct.uv_signal_s*, align 8
  %oleft = alloca %struct.uv_signal_s*, align 8
  %oright = alloca %struct.uv_signal_s*, align 8
  store %struct.uv__signal_tree_s* %head, %struct.uv__signal_tree_s** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__signal_tree_s** %head.addr, metadata !1873, metadata !385), !dbg !1874
  store %struct.uv_signal_s* %parent, %struct.uv_signal_s** %parent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %parent.addr, metadata !1875, metadata !385), !dbg !1874
  store %struct.uv_signal_s* %elm, %struct.uv_signal_s** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %elm.addr, metadata !1876, metadata !385), !dbg !1874
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %tmp, metadata !1877, metadata !385), !dbg !1874
  br label %while.cond, !dbg !1874

while.cond:                                       ; preds = %if.end488, %entry
  %0 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1878
  %cmp = icmp eq %struct.uv_signal_s* %0, null, !dbg !1878
  br i1 %cmp, label %land.rhs, label %lor.lhs.false, !dbg !1878

lor.lhs.false:                                    ; preds = %while.cond
  %1 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1880
  %tree_entry = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %1, i32 0, i32 10, !dbg !1880
  %rbe_color = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry, i32 0, i32 3, !dbg !1880
  %2 = load i32, i32* %rbe_color, align 8, !dbg !1880
  %cmp1 = icmp eq i32 %2, 0, !dbg !1880
  br i1 %cmp1, label %land.rhs, label %land.end, !dbg !1880

land.rhs:                                         ; preds = %lor.lhs.false, %while.cond
  %3 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1882
  %4 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1882
  %rbh_root = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %4, i32 0, i32 0, !dbg !1882
  %5 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbh_root, align 8, !dbg !1882
  %cmp2 = icmp ne %struct.uv_signal_s* %3, %5, !dbg !1882
  br label %land.end

land.end:                                         ; preds = %land.rhs, %lor.lhs.false
  %6 = phi i1 [ false, %lor.lhs.false ], [ %cmp2, %land.rhs ]
  br i1 %6, label %while.body, label %while.end, !dbg !1884

while.body:                                       ; preds = %land.end
  %7 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1886
  %tree_entry3 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %7, i32 0, i32 10, !dbg !1886
  %rbe_left = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry3, i32 0, i32 0, !dbg !1886
  %8 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left, align 8, !dbg !1886
  %9 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1886
  %cmp4 = icmp eq %struct.uv_signal_s* %8, %9, !dbg !1886
  br i1 %cmp4, label %if.then, label %if.else242, !dbg !1886

if.then:                                          ; preds = %while.body
  %10 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1890
  %tree_entry5 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %10, i32 0, i32 10, !dbg !1890
  %rbe_right = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry5, i32 0, i32 1, !dbg !1890
  %11 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right, align 8, !dbg !1890
  store %struct.uv_signal_s* %11, %struct.uv_signal_s** %tmp, align 8, !dbg !1890
  %12 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1890
  %tree_entry6 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %12, i32 0, i32 10, !dbg !1890
  %rbe_color7 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry6, i32 0, i32 3, !dbg !1890
  %13 = load i32, i32* %rbe_color7, align 8, !dbg !1890
  %cmp8 = icmp eq i32 %13, 1, !dbg !1890
  br i1 %cmp8, label %if.then9, label %if.end67, !dbg !1890

if.then9:                                         ; preds = %if.then
  br label %do.body, !dbg !1893

do.body:                                          ; preds = %if.then9
  %14 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1897
  %tree_entry10 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %14, i32 0, i32 10, !dbg !1897
  %rbe_color11 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry10, i32 0, i32 3, !dbg !1897
  store i32 0, i32* %rbe_color11, align 8, !dbg !1897
  %15 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1897
  %tree_entry12 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %15, i32 0, i32 10, !dbg !1897
  %rbe_color13 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry12, i32 0, i32 3, !dbg !1897
  store i32 1, i32* %rbe_color13, align 8, !dbg !1897
  br label %do.end, !dbg !1897

do.end:                                           ; preds = %do.body
  br label %do.body14, !dbg !1900

do.body14:                                        ; preds = %do.end
  %16 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1902
  %tree_entry15 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %16, i32 0, i32 10, !dbg !1902
  %rbe_right16 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry15, i32 0, i32 1, !dbg !1902
  %17 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right16, align 8, !dbg !1902
  store %struct.uv_signal_s* %17, %struct.uv_signal_s** %tmp, align 8, !dbg !1902
  %18 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1902
  %tree_entry17 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %18, i32 0, i32 10, !dbg !1902
  %rbe_left18 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry17, i32 0, i32 0, !dbg !1902
  %19 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left18, align 8, !dbg !1902
  %20 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1902
  %tree_entry19 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %20, i32 0, i32 10, !dbg !1902
  %rbe_right20 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry19, i32 0, i32 1, !dbg !1902
  store %struct.uv_signal_s* %19, %struct.uv_signal_s** %rbe_right20, align 8, !dbg !1902
  %cmp21 = icmp ne %struct.uv_signal_s* %19, null, !dbg !1902
  br i1 %cmp21, label %if.then22, label %if.end, !dbg !1902

if.then22:                                        ; preds = %do.body14
  %21 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1905
  %22 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1905
  %tree_entry23 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %22, i32 0, i32 10, !dbg !1905
  %rbe_left24 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry23, i32 0, i32 0, !dbg !1905
  %23 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left24, align 8, !dbg !1905
  %tree_entry25 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %23, i32 0, i32 10, !dbg !1905
  %rbe_parent = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry25, i32 0, i32 2, !dbg !1905
  store %struct.uv_signal_s* %21, %struct.uv_signal_s** %rbe_parent, align 8, !dbg !1905
  br label %if.end, !dbg !1905

if.end:                                           ; preds = %if.then22, %do.body14
  br label %do.body26, !dbg !1909

do.body26:                                        ; preds = %if.end
  br label %do.end27, !dbg !1911

do.end27:                                         ; preds = %do.body26
  %24 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1914
  %tree_entry28 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %24, i32 0, i32 10, !dbg !1914
  %rbe_parent29 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry28, i32 0, i32 2, !dbg !1914
  %25 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent29, align 8, !dbg !1914
  %26 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1914
  %tree_entry30 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %26, i32 0, i32 10, !dbg !1914
  %rbe_parent31 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry30, i32 0, i32 2, !dbg !1914
  store %struct.uv_signal_s* %25, %struct.uv_signal_s** %rbe_parent31, align 8, !dbg !1914
  %cmp32 = icmp ne %struct.uv_signal_s* %25, null, !dbg !1914
  br i1 %cmp32, label %if.then33, label %if.else49, !dbg !1914

if.then33:                                        ; preds = %do.end27
  %27 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1917
  %28 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1917
  %tree_entry34 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %28, i32 0, i32 10, !dbg !1917
  %rbe_parent35 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry34, i32 0, i32 2, !dbg !1917
  %29 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent35, align 8, !dbg !1917
  %tree_entry36 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %29, i32 0, i32 10, !dbg !1917
  %rbe_left37 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry36, i32 0, i32 0, !dbg !1917
  %30 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left37, align 8, !dbg !1917
  %cmp38 = icmp eq %struct.uv_signal_s* %27, %30, !dbg !1917
  br i1 %cmp38, label %if.then39, label %if.else, !dbg !1917

if.then39:                                        ; preds = %if.then33
  %31 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1921
  %32 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1921
  %tree_entry40 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %32, i32 0, i32 10, !dbg !1921
  %rbe_parent41 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry40, i32 0, i32 2, !dbg !1921
  %33 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent41, align 8, !dbg !1921
  %tree_entry42 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %33, i32 0, i32 10, !dbg !1921
  %rbe_left43 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry42, i32 0, i32 0, !dbg !1921
  store %struct.uv_signal_s* %31, %struct.uv_signal_s** %rbe_left43, align 8, !dbg !1921
  br label %if.end48, !dbg !1921

if.else:                                          ; preds = %if.then33
  %34 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1923
  %35 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1923
  %tree_entry44 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %35, i32 0, i32 10, !dbg !1923
  %rbe_parent45 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry44, i32 0, i32 2, !dbg !1923
  %36 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent45, align 8, !dbg !1923
  %tree_entry46 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %36, i32 0, i32 10, !dbg !1923
  %rbe_right47 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry46, i32 0, i32 1, !dbg !1923
  store %struct.uv_signal_s* %34, %struct.uv_signal_s** %rbe_right47, align 8, !dbg !1923
  br label %if.end48

if.end48:                                         ; preds = %if.else, %if.then39
  br label %if.end51, !dbg !1925

if.else49:                                        ; preds = %do.end27
  %37 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1927
  %38 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !1927
  %rbh_root50 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %38, i32 0, i32 0, !dbg !1927
  store %struct.uv_signal_s* %37, %struct.uv_signal_s** %rbh_root50, align 8, !dbg !1927
  br label %if.end51

if.end51:                                         ; preds = %if.else49, %if.end48
  %39 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1929
  %40 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1929
  %tree_entry52 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %40, i32 0, i32 10, !dbg !1929
  %rbe_left53 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry52, i32 0, i32 0, !dbg !1929
  store %struct.uv_signal_s* %39, %struct.uv_signal_s** %rbe_left53, align 8, !dbg !1929
  %41 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1929
  %42 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1929
  %tree_entry54 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %42, i32 0, i32 10, !dbg !1929
  %rbe_parent55 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry54, i32 0, i32 2, !dbg !1929
  store %struct.uv_signal_s* %41, %struct.uv_signal_s** %rbe_parent55, align 8, !dbg !1929
  br label %do.body56, !dbg !1929

do.body56:                                        ; preds = %if.end51
  br label %do.end57, !dbg !1931

do.end57:                                         ; preds = %do.body56
  %43 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1934
  %tree_entry58 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %43, i32 0, i32 10, !dbg !1934
  %rbe_parent59 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry58, i32 0, i32 2, !dbg !1934
  %44 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent59, align 8, !dbg !1934
  %tobool = icmp ne %struct.uv_signal_s* %44, null, !dbg !1934
  br i1 %tobool, label %if.then60, label %if.end63, !dbg !1934

if.then60:                                        ; preds = %do.end57
  br label %do.body61, !dbg !1937

do.body61:                                        ; preds = %if.then60
  br label %do.end62, !dbg !1939

do.end62:                                         ; preds = %do.body61
  br label %if.end63, !dbg !1942

if.end63:                                         ; preds = %do.end62, %do.end57
  br label %do.end64, !dbg !1944

do.end64:                                         ; preds = %if.end63
  %45 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1946
  %tree_entry65 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %45, i32 0, i32 10, !dbg !1946
  %rbe_right66 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry65, i32 0, i32 1, !dbg !1946
  %46 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right66, align 8, !dbg !1946
  store %struct.uv_signal_s* %46, %struct.uv_signal_s** %tmp, align 8, !dbg !1946
  br label %if.end67, !dbg !1946

if.end67:                                         ; preds = %do.end64, %if.then
  %47 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1948
  %tree_entry68 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %47, i32 0, i32 10, !dbg !1948
  %rbe_left69 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry68, i32 0, i32 0, !dbg !1948
  %48 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left69, align 8, !dbg !1948
  %cmp70 = icmp eq %struct.uv_signal_s* %48, null, !dbg !1948
  br i1 %cmp70, label %land.lhs.true, label %lor.lhs.false71, !dbg !1948

lor.lhs.false71:                                  ; preds = %if.end67
  %49 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1951
  %tree_entry72 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %49, i32 0, i32 10, !dbg !1951
  %rbe_left73 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry72, i32 0, i32 0, !dbg !1951
  %50 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left73, align 8, !dbg !1951
  %tree_entry74 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %50, i32 0, i32 10, !dbg !1951
  %rbe_color75 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry74, i32 0, i32 3, !dbg !1951
  %51 = load i32, i32* %rbe_color75, align 8, !dbg !1951
  %cmp76 = icmp eq i32 %51, 0, !dbg !1951
  br i1 %cmp76, label %land.lhs.true, label %if.else91, !dbg !1951

land.lhs.true:                                    ; preds = %lor.lhs.false71, %if.end67
  %52 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1953
  %tree_entry77 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %52, i32 0, i32 10, !dbg !1953
  %rbe_right78 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry77, i32 0, i32 1, !dbg !1953
  %53 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right78, align 8, !dbg !1953
  %cmp79 = icmp eq %struct.uv_signal_s* %53, null, !dbg !1953
  br i1 %cmp79, label %if.then86, label %lor.lhs.false80, !dbg !1953

lor.lhs.false80:                                  ; preds = %land.lhs.true
  %54 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1955
  %tree_entry81 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %54, i32 0, i32 10, !dbg !1955
  %rbe_right82 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry81, i32 0, i32 1, !dbg !1955
  %55 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right82, align 8, !dbg !1955
  %tree_entry83 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %55, i32 0, i32 10, !dbg !1955
  %rbe_color84 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry83, i32 0, i32 3, !dbg !1955
  %56 = load i32, i32* %rbe_color84, align 8, !dbg !1955
  %cmp85 = icmp eq i32 %56, 0, !dbg !1955
  br i1 %cmp85, label %if.then86, label %if.else91, !dbg !1955

if.then86:                                        ; preds = %lor.lhs.false80, %land.lhs.true
  %57 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1957
  %tree_entry87 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %57, i32 0, i32 10, !dbg !1957
  %rbe_color88 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry87, i32 0, i32 3, !dbg !1957
  store i32 1, i32* %rbe_color88, align 8, !dbg !1957
  %58 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1957
  store %struct.uv_signal_s* %58, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1957
  %59 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !1957
  %tree_entry89 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %59, i32 0, i32 10, !dbg !1957
  %rbe_parent90 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry89, i32 0, i32 2, !dbg !1957
  %60 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent90, align 8, !dbg !1957
  store %struct.uv_signal_s* %60, %struct.uv_signal_s** %parent.addr, align 8, !dbg !1957
  br label %if.end241, !dbg !1957

if.else91:                                        ; preds = %lor.lhs.false80, %lor.lhs.false71
  %61 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1960
  %tree_entry92 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %61, i32 0, i32 10, !dbg !1960
  %rbe_right93 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry92, i32 0, i32 1, !dbg !1960
  %62 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right93, align 8, !dbg !1960
  %cmp94 = icmp eq %struct.uv_signal_s* %62, null, !dbg !1960
  br i1 %cmp94, label %if.then101, label %lor.lhs.false95, !dbg !1960

lor.lhs.false95:                                  ; preds = %if.else91
  %63 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1964
  %tree_entry96 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %63, i32 0, i32 10, !dbg !1964
  %rbe_right97 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry96, i32 0, i32 1, !dbg !1964
  %64 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right97, align 8, !dbg !1964
  %tree_entry98 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %64, i32 0, i32 10, !dbg !1964
  %rbe_color99 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry98, i32 0, i32 3, !dbg !1964
  %65 = load i32, i32* %rbe_color99, align 8, !dbg !1964
  %cmp100 = icmp eq i32 %65, 0, !dbg !1964
  br i1 %cmp100, label %if.then101, label %if.end169, !dbg !1964

if.then101:                                       ; preds = %lor.lhs.false95, %if.else91
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %oleft, metadata !1966, metadata !385), !dbg !1968
  %66 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1969
  %tree_entry103 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %66, i32 0, i32 10, !dbg !1969
  %rbe_left104 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry103, i32 0, i32 0, !dbg !1969
  %67 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left104, align 8, !dbg !1969
  store %struct.uv_signal_s* %67, %struct.uv_signal_s** %oleft, align 8, !dbg !1969
  %cmp105 = icmp ne %struct.uv_signal_s* %67, null, !dbg !1969
  br i1 %cmp105, label %if.then106, label %if.end109, !dbg !1969

if.then106:                                       ; preds = %if.then101
  %68 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !1972
  %tree_entry107 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %68, i32 0, i32 10, !dbg !1972
  %rbe_color108 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry107, i32 0, i32 3, !dbg !1972
  store i32 0, i32* %rbe_color108, align 8, !dbg !1972
  br label %if.end109, !dbg !1972

if.end109:                                        ; preds = %if.then106, %if.then101
  %69 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1974
  %tree_entry110 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %69, i32 0, i32 10, !dbg !1974
  %rbe_color111 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry110, i32 0, i32 3, !dbg !1974
  store i32 1, i32* %rbe_color111, align 8, !dbg !1974
  br label %do.body112, !dbg !1974

do.body112:                                       ; preds = %if.end109
  %70 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1976
  %tree_entry113 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %70, i32 0, i32 10, !dbg !1976
  %rbe_left114 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry113, i32 0, i32 0, !dbg !1976
  %71 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left114, align 8, !dbg !1976
  store %struct.uv_signal_s* %71, %struct.uv_signal_s** %oleft, align 8, !dbg !1976
  %72 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !1976
  %tree_entry115 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %72, i32 0, i32 10, !dbg !1976
  %rbe_right116 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry115, i32 0, i32 1, !dbg !1976
  %73 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right116, align 8, !dbg !1976
  %74 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1976
  %tree_entry117 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %74, i32 0, i32 10, !dbg !1976
  %rbe_left118 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry117, i32 0, i32 0, !dbg !1976
  store %struct.uv_signal_s* %73, %struct.uv_signal_s** %rbe_left118, align 8, !dbg !1976
  %cmp119 = icmp ne %struct.uv_signal_s* %73, null, !dbg !1976
  br i1 %cmp119, label %if.then120, label %if.end125, !dbg !1976

if.then120:                                       ; preds = %do.body112
  %75 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1979
  %76 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !1979
  %tree_entry121 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %76, i32 0, i32 10, !dbg !1979
  %rbe_right122 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry121, i32 0, i32 1, !dbg !1979
  %77 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right122, align 8, !dbg !1979
  %tree_entry123 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %77, i32 0, i32 10, !dbg !1979
  %rbe_parent124 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry123, i32 0, i32 2, !dbg !1979
  store %struct.uv_signal_s* %75, %struct.uv_signal_s** %rbe_parent124, align 8, !dbg !1979
  br label %if.end125, !dbg !1979

if.end125:                                        ; preds = %if.then120, %do.body112
  br label %do.body126, !dbg !1983

do.body126:                                       ; preds = %if.end125
  br label %do.end127, !dbg !1985

do.end127:                                        ; preds = %do.body126
  %78 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1988
  %tree_entry128 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %78, i32 0, i32 10, !dbg !1988
  %rbe_parent129 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry128, i32 0, i32 2, !dbg !1988
  %79 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent129, align 8, !dbg !1988
  %80 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !1988
  %tree_entry130 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %80, i32 0, i32 10, !dbg !1988
  %rbe_parent131 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry130, i32 0, i32 2, !dbg !1988
  store %struct.uv_signal_s* %79, %struct.uv_signal_s** %rbe_parent131, align 8, !dbg !1988
  %cmp132 = icmp ne %struct.uv_signal_s* %79, null, !dbg !1988
  br i1 %cmp132, label %if.then133, label %if.else150, !dbg !1988

if.then133:                                       ; preds = %do.end127
  %81 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1991
  %82 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1991
  %tree_entry134 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %82, i32 0, i32 10, !dbg !1991
  %rbe_parent135 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry134, i32 0, i32 2, !dbg !1991
  %83 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent135, align 8, !dbg !1991
  %tree_entry136 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %83, i32 0, i32 10, !dbg !1991
  %rbe_left137 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry136, i32 0, i32 0, !dbg !1991
  %84 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left137, align 8, !dbg !1991
  %cmp138 = icmp eq %struct.uv_signal_s* %81, %84, !dbg !1991
  br i1 %cmp138, label %if.then139, label %if.else144, !dbg !1991

if.then139:                                       ; preds = %if.then133
  %85 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !1995
  %86 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1995
  %tree_entry140 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %86, i32 0, i32 10, !dbg !1995
  %rbe_parent141 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry140, i32 0, i32 2, !dbg !1995
  %87 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent141, align 8, !dbg !1995
  %tree_entry142 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %87, i32 0, i32 10, !dbg !1995
  %rbe_left143 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry142, i32 0, i32 0, !dbg !1995
  store %struct.uv_signal_s* %85, %struct.uv_signal_s** %rbe_left143, align 8, !dbg !1995
  br label %if.end149, !dbg !1995

if.else144:                                       ; preds = %if.then133
  %88 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !1997
  %89 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !1997
  %tree_entry145 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %89, i32 0, i32 10, !dbg !1997
  %rbe_parent146 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry145, i32 0, i32 2, !dbg !1997
  %90 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent146, align 8, !dbg !1997
  %tree_entry147 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %90, i32 0, i32 10, !dbg !1997
  %rbe_right148 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry147, i32 0, i32 1, !dbg !1997
  store %struct.uv_signal_s* %88, %struct.uv_signal_s** %rbe_right148, align 8, !dbg !1997
  br label %if.end149

if.end149:                                        ; preds = %if.else144, %if.then139
  br label %if.end152, !dbg !1999

if.else150:                                       ; preds = %do.end127
  %91 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !2001
  %92 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2001
  %rbh_root151 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %92, i32 0, i32 0, !dbg !2001
  store %struct.uv_signal_s* %91, %struct.uv_signal_s** %rbh_root151, align 8, !dbg !2001
  br label %if.end152

if.end152:                                        ; preds = %if.else150, %if.end149
  %93 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2003
  %94 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !2003
  %tree_entry153 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %94, i32 0, i32 10, !dbg !2003
  %rbe_right154 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry153, i32 0, i32 1, !dbg !2003
  store %struct.uv_signal_s* %93, %struct.uv_signal_s** %rbe_right154, align 8, !dbg !2003
  %95 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !2003
  %96 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2003
  %tree_entry155 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %96, i32 0, i32 10, !dbg !2003
  %rbe_parent156 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry155, i32 0, i32 2, !dbg !2003
  store %struct.uv_signal_s* %95, %struct.uv_signal_s** %rbe_parent156, align 8, !dbg !2003
  br label %do.body157, !dbg !2003

do.body157:                                       ; preds = %if.end152
  br label %do.end158, !dbg !2005

do.end158:                                        ; preds = %do.body157
  %97 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oleft, align 8, !dbg !2008
  %tree_entry159 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %97, i32 0, i32 10, !dbg !2008
  %rbe_parent160 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry159, i32 0, i32 2, !dbg !2008
  %98 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent160, align 8, !dbg !2008
  %tobool161 = icmp ne %struct.uv_signal_s* %98, null, !dbg !2008
  br i1 %tobool161, label %if.then162, label %if.end165, !dbg !2008

if.then162:                                       ; preds = %do.end158
  br label %do.body163, !dbg !2011

do.body163:                                       ; preds = %if.then162
  br label %do.end164, !dbg !2013

do.end164:                                        ; preds = %do.body163
  br label %if.end165, !dbg !2016

if.end165:                                        ; preds = %do.end164, %do.end158
  br label %do.end166, !dbg !2018

do.end166:                                        ; preds = %if.end165
  %99 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2020
  %tree_entry167 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %99, i32 0, i32 10, !dbg !2020
  %rbe_right168 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry167, i32 0, i32 1, !dbg !2020
  %100 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right168, align 8, !dbg !2020
  store %struct.uv_signal_s* %100, %struct.uv_signal_s** %tmp, align 8, !dbg !2020
  br label %if.end169, !dbg !2020

if.end169:                                        ; preds = %do.end166, %lor.lhs.false95
  %101 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2022
  %tree_entry170 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %101, i32 0, i32 10, !dbg !2022
  %rbe_color171 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry170, i32 0, i32 3, !dbg !2022
  %102 = load i32, i32* %rbe_color171, align 8, !dbg !2022
  %103 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2022
  %tree_entry172 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %103, i32 0, i32 10, !dbg !2022
  %rbe_color173 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry172, i32 0, i32 3, !dbg !2022
  store i32 %102, i32* %rbe_color173, align 8, !dbg !2022
  %104 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2022
  %tree_entry174 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %104, i32 0, i32 10, !dbg !2022
  %rbe_color175 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry174, i32 0, i32 3, !dbg !2022
  store i32 0, i32* %rbe_color175, align 8, !dbg !2022
  %105 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2022
  %tree_entry176 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %105, i32 0, i32 10, !dbg !2022
  %rbe_right177 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry176, i32 0, i32 1, !dbg !2022
  %106 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right177, align 8, !dbg !2022
  %tobool178 = icmp ne %struct.uv_signal_s* %106, null, !dbg !2022
  br i1 %tobool178, label %if.then179, label %if.end184, !dbg !2022

if.then179:                                       ; preds = %if.end169
  %107 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2024
  %tree_entry180 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %107, i32 0, i32 10, !dbg !2024
  %rbe_right181 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry180, i32 0, i32 1, !dbg !2024
  %108 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right181, align 8, !dbg !2024
  %tree_entry182 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %108, i32 0, i32 10, !dbg !2024
  %rbe_color183 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry182, i32 0, i32 3, !dbg !2024
  store i32 0, i32* %rbe_color183, align 8, !dbg !2024
  br label %if.end184, !dbg !2024

if.end184:                                        ; preds = %if.then179, %if.end169
  br label %do.body185, !dbg !2027

do.body185:                                       ; preds = %if.end184
  %109 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2029
  %tree_entry186 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %109, i32 0, i32 10, !dbg !2029
  %rbe_right187 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry186, i32 0, i32 1, !dbg !2029
  %110 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right187, align 8, !dbg !2029
  store %struct.uv_signal_s* %110, %struct.uv_signal_s** %tmp, align 8, !dbg !2029
  %111 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2029
  %tree_entry188 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %111, i32 0, i32 10, !dbg !2029
  %rbe_left189 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry188, i32 0, i32 0, !dbg !2029
  %112 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left189, align 8, !dbg !2029
  %113 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2029
  %tree_entry190 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %113, i32 0, i32 10, !dbg !2029
  %rbe_right191 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry190, i32 0, i32 1, !dbg !2029
  store %struct.uv_signal_s* %112, %struct.uv_signal_s** %rbe_right191, align 8, !dbg !2029
  %cmp192 = icmp ne %struct.uv_signal_s* %112, null, !dbg !2029
  br i1 %cmp192, label %if.then193, label %if.end198, !dbg !2029

if.then193:                                       ; preds = %do.body185
  %114 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2032
  %115 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2032
  %tree_entry194 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %115, i32 0, i32 10, !dbg !2032
  %rbe_left195 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry194, i32 0, i32 0, !dbg !2032
  %116 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left195, align 8, !dbg !2032
  %tree_entry196 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %116, i32 0, i32 10, !dbg !2032
  %rbe_parent197 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry196, i32 0, i32 2, !dbg !2032
  store %struct.uv_signal_s* %114, %struct.uv_signal_s** %rbe_parent197, align 8, !dbg !2032
  br label %if.end198, !dbg !2032

if.end198:                                        ; preds = %if.then193, %do.body185
  br label %do.body199, !dbg !2036

do.body199:                                       ; preds = %if.end198
  br label %do.end200, !dbg !2038

do.end200:                                        ; preds = %do.body199
  %117 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2041
  %tree_entry201 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %117, i32 0, i32 10, !dbg !2041
  %rbe_parent202 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry201, i32 0, i32 2, !dbg !2041
  %118 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent202, align 8, !dbg !2041
  %119 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2041
  %tree_entry203 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %119, i32 0, i32 10, !dbg !2041
  %rbe_parent204 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry203, i32 0, i32 2, !dbg !2041
  store %struct.uv_signal_s* %118, %struct.uv_signal_s** %rbe_parent204, align 8, !dbg !2041
  %cmp205 = icmp ne %struct.uv_signal_s* %118, null, !dbg !2041
  br i1 %cmp205, label %if.then206, label %if.else223, !dbg !2041

if.then206:                                       ; preds = %do.end200
  %120 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2044
  %121 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2044
  %tree_entry207 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %121, i32 0, i32 10, !dbg !2044
  %rbe_parent208 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry207, i32 0, i32 2, !dbg !2044
  %122 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent208, align 8, !dbg !2044
  %tree_entry209 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %122, i32 0, i32 10, !dbg !2044
  %rbe_left210 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry209, i32 0, i32 0, !dbg !2044
  %123 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left210, align 8, !dbg !2044
  %cmp211 = icmp eq %struct.uv_signal_s* %120, %123, !dbg !2044
  br i1 %cmp211, label %if.then212, label %if.else217, !dbg !2044

if.then212:                                       ; preds = %if.then206
  %124 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2048
  %125 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2048
  %tree_entry213 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %125, i32 0, i32 10, !dbg !2048
  %rbe_parent214 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry213, i32 0, i32 2, !dbg !2048
  %126 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent214, align 8, !dbg !2048
  %tree_entry215 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %126, i32 0, i32 10, !dbg !2048
  %rbe_left216 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry215, i32 0, i32 0, !dbg !2048
  store %struct.uv_signal_s* %124, %struct.uv_signal_s** %rbe_left216, align 8, !dbg !2048
  br label %if.end222, !dbg !2048

if.else217:                                       ; preds = %if.then206
  %127 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2050
  %128 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2050
  %tree_entry218 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %128, i32 0, i32 10, !dbg !2050
  %rbe_parent219 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry218, i32 0, i32 2, !dbg !2050
  %129 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent219, align 8, !dbg !2050
  %tree_entry220 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %129, i32 0, i32 10, !dbg !2050
  %rbe_right221 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry220, i32 0, i32 1, !dbg !2050
  store %struct.uv_signal_s* %127, %struct.uv_signal_s** %rbe_right221, align 8, !dbg !2050
  br label %if.end222

if.end222:                                        ; preds = %if.else217, %if.then212
  br label %if.end225, !dbg !2052

if.else223:                                       ; preds = %do.end200
  %130 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2054
  %131 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2054
  %rbh_root224 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %131, i32 0, i32 0, !dbg !2054
  store %struct.uv_signal_s* %130, %struct.uv_signal_s** %rbh_root224, align 8, !dbg !2054
  br label %if.end225

if.end225:                                        ; preds = %if.else223, %if.end222
  %132 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2056
  %133 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2056
  %tree_entry226 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %133, i32 0, i32 10, !dbg !2056
  %rbe_left227 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry226, i32 0, i32 0, !dbg !2056
  store %struct.uv_signal_s* %132, %struct.uv_signal_s** %rbe_left227, align 8, !dbg !2056
  %134 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2056
  %135 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2056
  %tree_entry228 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %135, i32 0, i32 10, !dbg !2056
  %rbe_parent229 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry228, i32 0, i32 2, !dbg !2056
  store %struct.uv_signal_s* %134, %struct.uv_signal_s** %rbe_parent229, align 8, !dbg !2056
  br label %do.body230, !dbg !2056

do.body230:                                       ; preds = %if.end225
  br label %do.end231, !dbg !2058

do.end231:                                        ; preds = %do.body230
  %136 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2061
  %tree_entry232 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %136, i32 0, i32 10, !dbg !2061
  %rbe_parent233 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry232, i32 0, i32 2, !dbg !2061
  %137 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent233, align 8, !dbg !2061
  %tobool234 = icmp ne %struct.uv_signal_s* %137, null, !dbg !2061
  br i1 %tobool234, label %if.then235, label %if.end238, !dbg !2061

if.then235:                                       ; preds = %do.end231
  br label %do.body236, !dbg !2064

do.body236:                                       ; preds = %if.then235
  br label %do.end237, !dbg !2066

do.end237:                                        ; preds = %do.body236
  br label %if.end238, !dbg !2069

if.end238:                                        ; preds = %do.end237, %do.end231
  br label %do.end239, !dbg !2071

do.end239:                                        ; preds = %if.end238
  %138 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2073
  %rbh_root240 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %138, i32 0, i32 0, !dbg !2073
  %139 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbh_root240, align 8, !dbg !2073
  store %struct.uv_signal_s* %139, %struct.uv_signal_s** %elm.addr, align 8, !dbg !2073
  br label %while.end, !dbg !2073

if.end241:                                        ; preds = %if.then86
  br label %if.end488, !dbg !2075

if.else242:                                       ; preds = %while.body
  %140 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2077
  %tree_entry243 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %140, i32 0, i32 10, !dbg !2077
  %rbe_left244 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry243, i32 0, i32 0, !dbg !2077
  %141 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left244, align 8, !dbg !2077
  store %struct.uv_signal_s* %141, %struct.uv_signal_s** %tmp, align 8, !dbg !2077
  %142 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2077
  %tree_entry245 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %142, i32 0, i32 10, !dbg !2077
  %rbe_color246 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry245, i32 0, i32 3, !dbg !2077
  %143 = load i32, i32* %rbe_color246, align 8, !dbg !2077
  %cmp247 = icmp eq i32 %143, 1, !dbg !2077
  br i1 %cmp247, label %if.then248, label %if.end312, !dbg !2077

if.then248:                                       ; preds = %if.else242
  br label %do.body249, !dbg !2080

do.body249:                                       ; preds = %if.then248
  %144 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2084
  %tree_entry250 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %144, i32 0, i32 10, !dbg !2084
  %rbe_color251 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry250, i32 0, i32 3, !dbg !2084
  store i32 0, i32* %rbe_color251, align 8, !dbg !2084
  %145 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2084
  %tree_entry252 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %145, i32 0, i32 10, !dbg !2084
  %rbe_color253 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry252, i32 0, i32 3, !dbg !2084
  store i32 1, i32* %rbe_color253, align 8, !dbg !2084
  br label %do.end254, !dbg !2084

do.end254:                                        ; preds = %do.body249
  br label %do.body255, !dbg !2087

do.body255:                                       ; preds = %do.end254
  %146 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2089
  %tree_entry256 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %146, i32 0, i32 10, !dbg !2089
  %rbe_left257 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry256, i32 0, i32 0, !dbg !2089
  %147 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left257, align 8, !dbg !2089
  store %struct.uv_signal_s* %147, %struct.uv_signal_s** %tmp, align 8, !dbg !2089
  %148 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2089
  %tree_entry258 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %148, i32 0, i32 10, !dbg !2089
  %rbe_right259 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry258, i32 0, i32 1, !dbg !2089
  %149 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right259, align 8, !dbg !2089
  %150 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2089
  %tree_entry260 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %150, i32 0, i32 10, !dbg !2089
  %rbe_left261 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry260, i32 0, i32 0, !dbg !2089
  store %struct.uv_signal_s* %149, %struct.uv_signal_s** %rbe_left261, align 8, !dbg !2089
  %cmp262 = icmp ne %struct.uv_signal_s* %149, null, !dbg !2089
  br i1 %cmp262, label %if.then263, label %if.end268, !dbg !2089

if.then263:                                       ; preds = %do.body255
  %151 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2092
  %152 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2092
  %tree_entry264 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %152, i32 0, i32 10, !dbg !2092
  %rbe_right265 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry264, i32 0, i32 1, !dbg !2092
  %153 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right265, align 8, !dbg !2092
  %tree_entry266 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %153, i32 0, i32 10, !dbg !2092
  %rbe_parent267 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry266, i32 0, i32 2, !dbg !2092
  store %struct.uv_signal_s* %151, %struct.uv_signal_s** %rbe_parent267, align 8, !dbg !2092
  br label %if.end268, !dbg !2092

if.end268:                                        ; preds = %if.then263, %do.body255
  br label %do.body269, !dbg !2096

do.body269:                                       ; preds = %if.end268
  br label %do.end270, !dbg !2098

do.end270:                                        ; preds = %do.body269
  %154 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2101
  %tree_entry271 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %154, i32 0, i32 10, !dbg !2101
  %rbe_parent272 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry271, i32 0, i32 2, !dbg !2101
  %155 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent272, align 8, !dbg !2101
  %156 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2101
  %tree_entry273 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %156, i32 0, i32 10, !dbg !2101
  %rbe_parent274 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry273, i32 0, i32 2, !dbg !2101
  store %struct.uv_signal_s* %155, %struct.uv_signal_s** %rbe_parent274, align 8, !dbg !2101
  %cmp275 = icmp ne %struct.uv_signal_s* %155, null, !dbg !2101
  br i1 %cmp275, label %if.then276, label %if.else293, !dbg !2101

if.then276:                                       ; preds = %do.end270
  %157 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2104
  %158 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2104
  %tree_entry277 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %158, i32 0, i32 10, !dbg !2104
  %rbe_parent278 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry277, i32 0, i32 2, !dbg !2104
  %159 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent278, align 8, !dbg !2104
  %tree_entry279 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %159, i32 0, i32 10, !dbg !2104
  %rbe_left280 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry279, i32 0, i32 0, !dbg !2104
  %160 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left280, align 8, !dbg !2104
  %cmp281 = icmp eq %struct.uv_signal_s* %157, %160, !dbg !2104
  br i1 %cmp281, label %if.then282, label %if.else287, !dbg !2104

if.then282:                                       ; preds = %if.then276
  %161 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2108
  %162 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2108
  %tree_entry283 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %162, i32 0, i32 10, !dbg !2108
  %rbe_parent284 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry283, i32 0, i32 2, !dbg !2108
  %163 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent284, align 8, !dbg !2108
  %tree_entry285 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %163, i32 0, i32 10, !dbg !2108
  %rbe_left286 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry285, i32 0, i32 0, !dbg !2108
  store %struct.uv_signal_s* %161, %struct.uv_signal_s** %rbe_left286, align 8, !dbg !2108
  br label %if.end292, !dbg !2108

if.else287:                                       ; preds = %if.then276
  %164 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2110
  %165 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2110
  %tree_entry288 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %165, i32 0, i32 10, !dbg !2110
  %rbe_parent289 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry288, i32 0, i32 2, !dbg !2110
  %166 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent289, align 8, !dbg !2110
  %tree_entry290 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %166, i32 0, i32 10, !dbg !2110
  %rbe_right291 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry290, i32 0, i32 1, !dbg !2110
  store %struct.uv_signal_s* %164, %struct.uv_signal_s** %rbe_right291, align 8, !dbg !2110
  br label %if.end292

if.end292:                                        ; preds = %if.else287, %if.then282
  br label %if.end295, !dbg !2112

if.else293:                                       ; preds = %do.end270
  %167 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2114
  %168 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2114
  %rbh_root294 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %168, i32 0, i32 0, !dbg !2114
  store %struct.uv_signal_s* %167, %struct.uv_signal_s** %rbh_root294, align 8, !dbg !2114
  br label %if.end295

if.end295:                                        ; preds = %if.else293, %if.end292
  %169 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2116
  %170 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2116
  %tree_entry296 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %170, i32 0, i32 10, !dbg !2116
  %rbe_right297 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry296, i32 0, i32 1, !dbg !2116
  store %struct.uv_signal_s* %169, %struct.uv_signal_s** %rbe_right297, align 8, !dbg !2116
  %171 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2116
  %172 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2116
  %tree_entry298 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %172, i32 0, i32 10, !dbg !2116
  %rbe_parent299 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry298, i32 0, i32 2, !dbg !2116
  store %struct.uv_signal_s* %171, %struct.uv_signal_s** %rbe_parent299, align 8, !dbg !2116
  br label %do.body300, !dbg !2116

do.body300:                                       ; preds = %if.end295
  br label %do.end301, !dbg !2118

do.end301:                                        ; preds = %do.body300
  %173 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2121
  %tree_entry302 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %173, i32 0, i32 10, !dbg !2121
  %rbe_parent303 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry302, i32 0, i32 2, !dbg !2121
  %174 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent303, align 8, !dbg !2121
  %tobool304 = icmp ne %struct.uv_signal_s* %174, null, !dbg !2121
  br i1 %tobool304, label %if.then305, label %if.end308, !dbg !2121

if.then305:                                       ; preds = %do.end301
  br label %do.body306, !dbg !2124

do.body306:                                       ; preds = %if.then305
  br label %do.end307, !dbg !2126

do.end307:                                        ; preds = %do.body306
  br label %if.end308, !dbg !2129

if.end308:                                        ; preds = %do.end307, %do.end301
  br label %do.end309, !dbg !2131

do.end309:                                        ; preds = %if.end308
  %175 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2133
  %tree_entry310 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %175, i32 0, i32 10, !dbg !2133
  %rbe_left311 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry310, i32 0, i32 0, !dbg !2133
  %176 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left311, align 8, !dbg !2133
  store %struct.uv_signal_s* %176, %struct.uv_signal_s** %tmp, align 8, !dbg !2133
  br label %if.end312, !dbg !2133

if.end312:                                        ; preds = %do.end309, %if.else242
  %177 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2135
  %tree_entry313 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %177, i32 0, i32 10, !dbg !2135
  %rbe_left314 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry313, i32 0, i32 0, !dbg !2135
  %178 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left314, align 8, !dbg !2135
  %cmp315 = icmp eq %struct.uv_signal_s* %178, null, !dbg !2135
  br i1 %cmp315, label %land.lhs.true322, label %lor.lhs.false316, !dbg !2135

lor.lhs.false316:                                 ; preds = %if.end312
  %179 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2138
  %tree_entry317 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %179, i32 0, i32 10, !dbg !2138
  %rbe_left318 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry317, i32 0, i32 0, !dbg !2138
  %180 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left318, align 8, !dbg !2138
  %tree_entry319 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %180, i32 0, i32 10, !dbg !2138
  %rbe_color320 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry319, i32 0, i32 3, !dbg !2138
  %181 = load i32, i32* %rbe_color320, align 8, !dbg !2138
  %cmp321 = icmp eq i32 %181, 0, !dbg !2138
  br i1 %cmp321, label %land.lhs.true322, label %if.else337, !dbg !2138

land.lhs.true322:                                 ; preds = %lor.lhs.false316, %if.end312
  %182 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2140
  %tree_entry323 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %182, i32 0, i32 10, !dbg !2140
  %rbe_right324 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry323, i32 0, i32 1, !dbg !2140
  %183 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right324, align 8, !dbg !2140
  %cmp325 = icmp eq %struct.uv_signal_s* %183, null, !dbg !2140
  br i1 %cmp325, label %if.then332, label %lor.lhs.false326, !dbg !2140

lor.lhs.false326:                                 ; preds = %land.lhs.true322
  %184 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2142
  %tree_entry327 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %184, i32 0, i32 10, !dbg !2142
  %rbe_right328 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry327, i32 0, i32 1, !dbg !2142
  %185 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right328, align 8, !dbg !2142
  %tree_entry329 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %185, i32 0, i32 10, !dbg !2142
  %rbe_color330 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry329, i32 0, i32 3, !dbg !2142
  %186 = load i32, i32* %rbe_color330, align 8, !dbg !2142
  %cmp331 = icmp eq i32 %186, 0, !dbg !2142
  br i1 %cmp331, label %if.then332, label %if.else337, !dbg !2142

if.then332:                                       ; preds = %lor.lhs.false326, %land.lhs.true322
  %187 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2144
  %tree_entry333 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %187, i32 0, i32 10, !dbg !2144
  %rbe_color334 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry333, i32 0, i32 3, !dbg !2144
  store i32 1, i32* %rbe_color334, align 8, !dbg !2144
  %188 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2144
  store %struct.uv_signal_s* %188, %struct.uv_signal_s** %elm.addr, align 8, !dbg !2144
  %189 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !2144
  %tree_entry335 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %189, i32 0, i32 10, !dbg !2144
  %rbe_parent336 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry335, i32 0, i32 2, !dbg !2144
  %190 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent336, align 8, !dbg !2144
  store %struct.uv_signal_s* %190, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2144
  br label %if.end487, !dbg !2144

if.else337:                                       ; preds = %lor.lhs.false326, %lor.lhs.false316
  %191 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2147
  %tree_entry338 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %191, i32 0, i32 10, !dbg !2147
  %rbe_left339 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry338, i32 0, i32 0, !dbg !2147
  %192 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left339, align 8, !dbg !2147
  %cmp340 = icmp eq %struct.uv_signal_s* %192, null, !dbg !2147
  br i1 %cmp340, label %if.then347, label %lor.lhs.false341, !dbg !2147

lor.lhs.false341:                                 ; preds = %if.else337
  %193 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2151
  %tree_entry342 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %193, i32 0, i32 10, !dbg !2151
  %rbe_left343 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry342, i32 0, i32 0, !dbg !2151
  %194 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left343, align 8, !dbg !2151
  %tree_entry344 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %194, i32 0, i32 10, !dbg !2151
  %rbe_color345 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry344, i32 0, i32 3, !dbg !2151
  %195 = load i32, i32* %rbe_color345, align 8, !dbg !2151
  %cmp346 = icmp eq i32 %195, 0, !dbg !2151
  br i1 %cmp346, label %if.then347, label %if.end415, !dbg !2151

if.then347:                                       ; preds = %lor.lhs.false341, %if.else337
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %oright, metadata !2153, metadata !385), !dbg !2155
  %196 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2156
  %tree_entry349 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %196, i32 0, i32 10, !dbg !2156
  %rbe_right350 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry349, i32 0, i32 1, !dbg !2156
  %197 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right350, align 8, !dbg !2156
  store %struct.uv_signal_s* %197, %struct.uv_signal_s** %oright, align 8, !dbg !2156
  %cmp351 = icmp ne %struct.uv_signal_s* %197, null, !dbg !2156
  br i1 %cmp351, label %if.then352, label %if.end355, !dbg !2156

if.then352:                                       ; preds = %if.then347
  %198 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2159
  %tree_entry353 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %198, i32 0, i32 10, !dbg !2159
  %rbe_color354 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry353, i32 0, i32 3, !dbg !2159
  store i32 0, i32* %rbe_color354, align 8, !dbg !2159
  br label %if.end355, !dbg !2159

if.end355:                                        ; preds = %if.then352, %if.then347
  %199 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2161
  %tree_entry356 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %199, i32 0, i32 10, !dbg !2161
  %rbe_color357 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry356, i32 0, i32 3, !dbg !2161
  store i32 1, i32* %rbe_color357, align 8, !dbg !2161
  br label %do.body358, !dbg !2161

do.body358:                                       ; preds = %if.end355
  %200 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2163
  %tree_entry359 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %200, i32 0, i32 10, !dbg !2163
  %rbe_right360 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry359, i32 0, i32 1, !dbg !2163
  %201 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right360, align 8, !dbg !2163
  store %struct.uv_signal_s* %201, %struct.uv_signal_s** %oright, align 8, !dbg !2163
  %202 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2163
  %tree_entry361 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %202, i32 0, i32 10, !dbg !2163
  %rbe_left362 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry361, i32 0, i32 0, !dbg !2163
  %203 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left362, align 8, !dbg !2163
  %204 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2163
  %tree_entry363 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %204, i32 0, i32 10, !dbg !2163
  %rbe_right364 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry363, i32 0, i32 1, !dbg !2163
  store %struct.uv_signal_s* %203, %struct.uv_signal_s** %rbe_right364, align 8, !dbg !2163
  %cmp365 = icmp ne %struct.uv_signal_s* %203, null, !dbg !2163
  br i1 %cmp365, label %if.then366, label %if.end371, !dbg !2163

if.then366:                                       ; preds = %do.body358
  %205 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2166
  %206 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2166
  %tree_entry367 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %206, i32 0, i32 10, !dbg !2166
  %rbe_left368 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry367, i32 0, i32 0, !dbg !2166
  %207 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left368, align 8, !dbg !2166
  %tree_entry369 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %207, i32 0, i32 10, !dbg !2166
  %rbe_parent370 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry369, i32 0, i32 2, !dbg !2166
  store %struct.uv_signal_s* %205, %struct.uv_signal_s** %rbe_parent370, align 8, !dbg !2166
  br label %if.end371, !dbg !2166

if.end371:                                        ; preds = %if.then366, %do.body358
  br label %do.body372, !dbg !2170

do.body372:                                       ; preds = %if.end371
  br label %do.end373, !dbg !2172

do.end373:                                        ; preds = %do.body372
  %208 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2175
  %tree_entry374 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %208, i32 0, i32 10, !dbg !2175
  %rbe_parent375 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry374, i32 0, i32 2, !dbg !2175
  %209 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent375, align 8, !dbg !2175
  %210 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2175
  %tree_entry376 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %210, i32 0, i32 10, !dbg !2175
  %rbe_parent377 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry376, i32 0, i32 2, !dbg !2175
  store %struct.uv_signal_s* %209, %struct.uv_signal_s** %rbe_parent377, align 8, !dbg !2175
  %cmp378 = icmp ne %struct.uv_signal_s* %209, null, !dbg !2175
  br i1 %cmp378, label %if.then379, label %if.else396, !dbg !2175

if.then379:                                       ; preds = %do.end373
  %211 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2178
  %212 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2178
  %tree_entry380 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %212, i32 0, i32 10, !dbg !2178
  %rbe_parent381 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry380, i32 0, i32 2, !dbg !2178
  %213 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent381, align 8, !dbg !2178
  %tree_entry382 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %213, i32 0, i32 10, !dbg !2178
  %rbe_left383 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry382, i32 0, i32 0, !dbg !2178
  %214 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left383, align 8, !dbg !2178
  %cmp384 = icmp eq %struct.uv_signal_s* %211, %214, !dbg !2178
  br i1 %cmp384, label %if.then385, label %if.else390, !dbg !2178

if.then385:                                       ; preds = %if.then379
  %215 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2182
  %216 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2182
  %tree_entry386 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %216, i32 0, i32 10, !dbg !2182
  %rbe_parent387 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry386, i32 0, i32 2, !dbg !2182
  %217 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent387, align 8, !dbg !2182
  %tree_entry388 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %217, i32 0, i32 10, !dbg !2182
  %rbe_left389 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry388, i32 0, i32 0, !dbg !2182
  store %struct.uv_signal_s* %215, %struct.uv_signal_s** %rbe_left389, align 8, !dbg !2182
  br label %if.end395, !dbg !2182

if.else390:                                       ; preds = %if.then379
  %218 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2184
  %219 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2184
  %tree_entry391 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %219, i32 0, i32 10, !dbg !2184
  %rbe_parent392 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry391, i32 0, i32 2, !dbg !2184
  %220 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent392, align 8, !dbg !2184
  %tree_entry393 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %220, i32 0, i32 10, !dbg !2184
  %rbe_right394 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry393, i32 0, i32 1, !dbg !2184
  store %struct.uv_signal_s* %218, %struct.uv_signal_s** %rbe_right394, align 8, !dbg !2184
  br label %if.end395

if.end395:                                        ; preds = %if.else390, %if.then385
  br label %if.end398, !dbg !2186

if.else396:                                       ; preds = %do.end373
  %221 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2188
  %222 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2188
  %rbh_root397 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %222, i32 0, i32 0, !dbg !2188
  store %struct.uv_signal_s* %221, %struct.uv_signal_s** %rbh_root397, align 8, !dbg !2188
  br label %if.end398

if.end398:                                        ; preds = %if.else396, %if.end395
  %223 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2190
  %224 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2190
  %tree_entry399 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %224, i32 0, i32 10, !dbg !2190
  %rbe_left400 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry399, i32 0, i32 0, !dbg !2190
  store %struct.uv_signal_s* %223, %struct.uv_signal_s** %rbe_left400, align 8, !dbg !2190
  %225 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2190
  %226 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2190
  %tree_entry401 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %226, i32 0, i32 10, !dbg !2190
  %rbe_parent402 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry401, i32 0, i32 2, !dbg !2190
  store %struct.uv_signal_s* %225, %struct.uv_signal_s** %rbe_parent402, align 8, !dbg !2190
  br label %do.body403, !dbg !2190

do.body403:                                       ; preds = %if.end398
  br label %do.end404, !dbg !2192

do.end404:                                        ; preds = %do.body403
  %227 = load %struct.uv_signal_s*, %struct.uv_signal_s** %oright, align 8, !dbg !2195
  %tree_entry405 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %227, i32 0, i32 10, !dbg !2195
  %rbe_parent406 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry405, i32 0, i32 2, !dbg !2195
  %228 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent406, align 8, !dbg !2195
  %tobool407 = icmp ne %struct.uv_signal_s* %228, null, !dbg !2195
  br i1 %tobool407, label %if.then408, label %if.end411, !dbg !2195

if.then408:                                       ; preds = %do.end404
  br label %do.body409, !dbg !2198

do.body409:                                       ; preds = %if.then408
  br label %do.end410, !dbg !2200

do.end410:                                        ; preds = %do.body409
  br label %if.end411, !dbg !2203

if.end411:                                        ; preds = %do.end410, %do.end404
  br label %do.end412, !dbg !2205

do.end412:                                        ; preds = %if.end411
  %229 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2207
  %tree_entry413 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %229, i32 0, i32 10, !dbg !2207
  %rbe_left414 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry413, i32 0, i32 0, !dbg !2207
  %230 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left414, align 8, !dbg !2207
  store %struct.uv_signal_s* %230, %struct.uv_signal_s** %tmp, align 8, !dbg !2207
  br label %if.end415, !dbg !2207

if.end415:                                        ; preds = %do.end412, %lor.lhs.false341
  %231 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2209
  %tree_entry416 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %231, i32 0, i32 10, !dbg !2209
  %rbe_color417 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry416, i32 0, i32 3, !dbg !2209
  %232 = load i32, i32* %rbe_color417, align 8, !dbg !2209
  %233 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2209
  %tree_entry418 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %233, i32 0, i32 10, !dbg !2209
  %rbe_color419 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry418, i32 0, i32 3, !dbg !2209
  store i32 %232, i32* %rbe_color419, align 8, !dbg !2209
  %234 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2209
  %tree_entry420 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %234, i32 0, i32 10, !dbg !2209
  %rbe_color421 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry420, i32 0, i32 3, !dbg !2209
  store i32 0, i32* %rbe_color421, align 8, !dbg !2209
  %235 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2209
  %tree_entry422 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %235, i32 0, i32 10, !dbg !2209
  %rbe_left423 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry422, i32 0, i32 0, !dbg !2209
  %236 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left423, align 8, !dbg !2209
  %tobool424 = icmp ne %struct.uv_signal_s* %236, null, !dbg !2209
  br i1 %tobool424, label %if.then425, label %if.end430, !dbg !2209

if.then425:                                       ; preds = %if.end415
  %237 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2211
  %tree_entry426 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %237, i32 0, i32 10, !dbg !2211
  %rbe_left427 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry426, i32 0, i32 0, !dbg !2211
  %238 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left427, align 8, !dbg !2211
  %tree_entry428 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %238, i32 0, i32 10, !dbg !2211
  %rbe_color429 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry428, i32 0, i32 3, !dbg !2211
  store i32 0, i32* %rbe_color429, align 8, !dbg !2211
  br label %if.end430, !dbg !2211

if.end430:                                        ; preds = %if.then425, %if.end415
  br label %do.body431, !dbg !2214

do.body431:                                       ; preds = %if.end430
  %239 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2216
  %tree_entry432 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %239, i32 0, i32 10, !dbg !2216
  %rbe_left433 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry432, i32 0, i32 0, !dbg !2216
  %240 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left433, align 8, !dbg !2216
  store %struct.uv_signal_s* %240, %struct.uv_signal_s** %tmp, align 8, !dbg !2216
  %241 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2216
  %tree_entry434 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %241, i32 0, i32 10, !dbg !2216
  %rbe_right435 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry434, i32 0, i32 1, !dbg !2216
  %242 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right435, align 8, !dbg !2216
  %243 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2216
  %tree_entry436 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %243, i32 0, i32 10, !dbg !2216
  %rbe_left437 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry436, i32 0, i32 0, !dbg !2216
  store %struct.uv_signal_s* %242, %struct.uv_signal_s** %rbe_left437, align 8, !dbg !2216
  %cmp438 = icmp ne %struct.uv_signal_s* %242, null, !dbg !2216
  br i1 %cmp438, label %if.then439, label %if.end444, !dbg !2216

if.then439:                                       ; preds = %do.body431
  %244 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2219
  %245 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2219
  %tree_entry440 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %245, i32 0, i32 10, !dbg !2219
  %rbe_right441 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry440, i32 0, i32 1, !dbg !2219
  %246 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_right441, align 8, !dbg !2219
  %tree_entry442 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %246, i32 0, i32 10, !dbg !2219
  %rbe_parent443 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry442, i32 0, i32 2, !dbg !2219
  store %struct.uv_signal_s* %244, %struct.uv_signal_s** %rbe_parent443, align 8, !dbg !2219
  br label %if.end444, !dbg !2219

if.end444:                                        ; preds = %if.then439, %do.body431
  br label %do.body445, !dbg !2223

do.body445:                                       ; preds = %if.end444
  br label %do.end446, !dbg !2225

do.end446:                                        ; preds = %do.body445
  %247 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2228
  %tree_entry447 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %247, i32 0, i32 10, !dbg !2228
  %rbe_parent448 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry447, i32 0, i32 2, !dbg !2228
  %248 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent448, align 8, !dbg !2228
  %249 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2228
  %tree_entry449 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %249, i32 0, i32 10, !dbg !2228
  %rbe_parent450 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry449, i32 0, i32 2, !dbg !2228
  store %struct.uv_signal_s* %248, %struct.uv_signal_s** %rbe_parent450, align 8, !dbg !2228
  %cmp451 = icmp ne %struct.uv_signal_s* %248, null, !dbg !2228
  br i1 %cmp451, label %if.then452, label %if.else469, !dbg !2228

if.then452:                                       ; preds = %do.end446
  %250 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2231
  %251 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2231
  %tree_entry453 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %251, i32 0, i32 10, !dbg !2231
  %rbe_parent454 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry453, i32 0, i32 2, !dbg !2231
  %252 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent454, align 8, !dbg !2231
  %tree_entry455 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %252, i32 0, i32 10, !dbg !2231
  %rbe_left456 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry455, i32 0, i32 0, !dbg !2231
  %253 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_left456, align 8, !dbg !2231
  %cmp457 = icmp eq %struct.uv_signal_s* %250, %253, !dbg !2231
  br i1 %cmp457, label %if.then458, label %if.else463, !dbg !2231

if.then458:                                       ; preds = %if.then452
  %254 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2235
  %255 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2235
  %tree_entry459 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %255, i32 0, i32 10, !dbg !2235
  %rbe_parent460 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry459, i32 0, i32 2, !dbg !2235
  %256 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent460, align 8, !dbg !2235
  %tree_entry461 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %256, i32 0, i32 10, !dbg !2235
  %rbe_left462 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry461, i32 0, i32 0, !dbg !2235
  store %struct.uv_signal_s* %254, %struct.uv_signal_s** %rbe_left462, align 8, !dbg !2235
  br label %if.end468, !dbg !2235

if.else463:                                       ; preds = %if.then452
  %257 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2237
  %258 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2237
  %tree_entry464 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %258, i32 0, i32 10, !dbg !2237
  %rbe_parent465 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry464, i32 0, i32 2, !dbg !2237
  %259 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent465, align 8, !dbg !2237
  %tree_entry466 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %259, i32 0, i32 10, !dbg !2237
  %rbe_right467 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry466, i32 0, i32 1, !dbg !2237
  store %struct.uv_signal_s* %257, %struct.uv_signal_s** %rbe_right467, align 8, !dbg !2237
  br label %if.end468

if.end468:                                        ; preds = %if.else463, %if.then458
  br label %if.end471, !dbg !2239

if.else469:                                       ; preds = %do.end446
  %260 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2241
  %261 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2241
  %rbh_root470 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %261, i32 0, i32 0, !dbg !2241
  store %struct.uv_signal_s* %260, %struct.uv_signal_s** %rbh_root470, align 8, !dbg !2241
  br label %if.end471

if.end471:                                        ; preds = %if.else469, %if.end468
  %262 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2243
  %263 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2243
  %tree_entry472 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %263, i32 0, i32 10, !dbg !2243
  %rbe_right473 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry472, i32 0, i32 1, !dbg !2243
  store %struct.uv_signal_s* %262, %struct.uv_signal_s** %rbe_right473, align 8, !dbg !2243
  %264 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2243
  %265 = load %struct.uv_signal_s*, %struct.uv_signal_s** %parent.addr, align 8, !dbg !2243
  %tree_entry474 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %265, i32 0, i32 10, !dbg !2243
  %rbe_parent475 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry474, i32 0, i32 2, !dbg !2243
  store %struct.uv_signal_s* %264, %struct.uv_signal_s** %rbe_parent475, align 8, !dbg !2243
  br label %do.body476, !dbg !2243

do.body476:                                       ; preds = %if.end471
  br label %do.end477, !dbg !2245

do.end477:                                        ; preds = %do.body476
  %266 = load %struct.uv_signal_s*, %struct.uv_signal_s** %tmp, align 8, !dbg !2248
  %tree_entry478 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %266, i32 0, i32 10, !dbg !2248
  %rbe_parent479 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry478, i32 0, i32 2, !dbg !2248
  %267 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbe_parent479, align 8, !dbg !2248
  %tobool480 = icmp ne %struct.uv_signal_s* %267, null, !dbg !2248
  br i1 %tobool480, label %if.then481, label %if.end484, !dbg !2248

if.then481:                                       ; preds = %do.end477
  br label %do.body482, !dbg !2251

do.body482:                                       ; preds = %if.then481
  br label %do.end483, !dbg !2253

do.end483:                                        ; preds = %do.body482
  br label %if.end484, !dbg !2256

if.end484:                                        ; preds = %do.end483, %do.end477
  br label %do.end485, !dbg !2258

do.end485:                                        ; preds = %if.end484
  %268 = load %struct.uv__signal_tree_s*, %struct.uv__signal_tree_s** %head.addr, align 8, !dbg !2260
  %rbh_root486 = getelementptr inbounds %struct.uv__signal_tree_s, %struct.uv__signal_tree_s* %268, i32 0, i32 0, !dbg !2260
  %269 = load %struct.uv_signal_s*, %struct.uv_signal_s** %rbh_root486, align 8, !dbg !2260
  store %struct.uv_signal_s* %269, %struct.uv_signal_s** %elm.addr, align 8, !dbg !2260
  br label %while.end, !dbg !2260

if.end487:                                        ; preds = %if.then332
  br label %if.end488

if.end488:                                        ; preds = %if.end487, %if.end241
  br label %while.cond, !dbg !2262

while.end:                                        ; preds = %do.end485, %do.end239, %land.end
  %270 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !2264
  %tobool489 = icmp ne %struct.uv_signal_s* %270, null, !dbg !2264
  br i1 %tobool489, label %if.then490, label %if.end493, !dbg !2264

if.then490:                                       ; preds = %while.end
  %271 = load %struct.uv_signal_s*, %struct.uv_signal_s** %elm.addr, align 8, !dbg !2267
  %tree_entry491 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %271, i32 0, i32 10, !dbg !2267
  %rbe_color492 = getelementptr inbounds %struct.anon.3, %struct.anon.3* %tree_entry491, i32 0, i32 3, !dbg !2267
  store i32 0, i32* %rbe_color492, align 8, !dbg !2267
  br label %if.end493, !dbg !2267

if.end493:                                        ; preds = %if.then490, %while.end
  ret void, !dbg !2269
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!361, !362}
!llvm.ident = !{!363}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !52, subprograms: !275, globals: !355)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/signal.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !33}
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
!52 = !{!53, !61, !263, !237, !264, !58, !270}
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !56, line: 21, baseType: !57)
!56 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!57 = !DICompositeType(tag: DW_TAG_array_type, baseType: !58, size: 128, align: 64, elements: !59)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!59 = !{!60}
!60 = !DISubrange(count: 2)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !63)
!63 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !64)
!64 = !{!65, !66, !253, !254, !255, !256, !261, !262}
!65 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !63, file: !4, line: 426, baseType: !58, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !63, file: !4, line: 426, baseType: !67, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !69)
!69 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !70)
!70 = !{!71, !72, !74, !75, !76, !77, !79, !81, !82, !83, !102, !103, !104, !105, !136, !168, !192, !193, !194, !195, !196, !197, !198, !202, !203, !204, !209, !212, !213, !215, !216, !249, !250, !251, !252}
!71 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !69, file: !4, line: 1475, baseType: !58, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !69, file: !4, line: 1477, baseType: !73, size: 32, align: 32, offset: 64)
!73 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !69, file: !4, line: 1478, baseType: !57, size: 128, align: 64, offset: 128)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !69, file: !4, line: 1479, baseType: !57, size: 128, align: 64, offset: 256)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !69, file: !4, line: 1481, baseType: !73, size: 32, align: 32, offset: 384)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !69, file: !4, line: 1482, baseType: !78, size: 64, align: 64, offset: 448)
!78 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !69, file: !4, line: 1482, baseType: !80, size: 32, align: 32, offset: 512)
!80 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 576)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 704)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !69, file: !4, line: 1482, baseType: !84, size: 64, align: 64, offset: 832)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !87, line: 87, baseType: !88)
!87 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!88 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !87, line: 89, size: 448, align: 64, elements: !89)
!89 = !{!90, !97, !98, !99, !100, !101}
!90 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !88, file: !87, line: 90, baseType: !91, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !87, line: 84, baseType: !92)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DISubroutineType(types: !94)
!94 = !{null, !95, !96, !73}
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !88, file: !87, line: 91, baseType: !57, size: 128, align: 64, offset: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !88, file: !87, line: 92, baseType: !57, size: 128, align: 64, offset: 192)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !88, file: !87, line: 93, baseType: !73, size: 32, align: 32, offset: 320)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !88, file: !87, line: 94, baseType: !73, size: 32, align: 32, offset: 352)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !88, file: !87, line: 95, baseType: !80, size: 32, align: 32, offset: 384)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !69, file: !4, line: 1482, baseType: !73, size: 32, align: 32, offset: 896)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !69, file: !4, line: 1482, baseType: !73, size: 32, align: 32, offset: 928)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 960)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !69, file: !4, line: 1482, baseType: !106, size: 320, align: 64, offset: 1088)
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !87, line: 129, baseType: !107)
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !108, line: 127, baseType: !109)
!108 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!109 = !DICompositeType(tag: DW_TAG_union_type, file: !108, line: 90, size: 320, align: 64, elements: !110)
!110 = !{!111, !129, !134}
!111 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !109, file: !108, line: 124, baseType: !112, size: 320, align: 64)
!112 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !108, line: 92, size: 320, align: 64, elements: !113)
!113 = !{!114, !115, !116, !117, !118, !119, !121, !122}
!114 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !112, file: !108, line: 94, baseType: !80, size: 32, align: 32)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !112, file: !108, line: 95, baseType: !73, size: 32, align: 32, offset: 32)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !112, file: !108, line: 96, baseType: !80, size: 32, align: 32, offset: 64)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !112, file: !108, line: 98, baseType: !73, size: 32, align: 32, offset: 96)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !112, file: !108, line: 102, baseType: !80, size: 32, align: 32, offset: 128)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !112, file: !108, line: 104, baseType: !120, size: 16, align: 16, offset: 160)
!120 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !112, file: !108, line: 105, baseType: !120, size: 16, align: 16, offset: 176)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !112, file: !108, line: 106, baseType: !123, size: 128, align: 64, offset: 192)
!123 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !108, line: 79, baseType: !124)
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !108, line: 75, size: 128, align: 64, elements: !125)
!125 = !{!126, !128}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !124, file: !108, line: 77, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !124, file: !108, line: 78, baseType: !127, size: 64, align: 64, offset: 64)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !109, file: !108, line: 125, baseType: !130, size: 320, align: 8)
!130 = !DICompositeType(tag: DW_TAG_array_type, baseType: !131, size: 320, align: 8, elements: !132)
!131 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!132 = !{!133}
!133 = !DISubrange(count: 40)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !109, file: !108, line: 126, baseType: !135, size: 64, align: 64)
!135 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !69, file: !4, line: 1482, baseType: !137, size: 1024, align: 64, offset: 1408)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !138)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !139)
!139 = !{!140, !141, !142, !144, !149, !150, !158, !159, !160, !166, !167}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !138, file: !4, line: 768, baseType: !58, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !138, file: !4, line: 768, baseType: !67, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !138, file: !4, line: 768, baseType: !143, size: 32, align: 32, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !138, file: !4, line: 768, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !146)
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!147 = !DISubroutineType(types: !148)
!148 = !{null, !61}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !138, file: !4, line: 768, baseType: !57, size: 128, align: 64, offset: 256)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !138, file: !4, line: 768, baseType: !151, size: 256, align: 64, offset: 384)
!151 = !DICompositeType(tag: DW_TAG_union_type, scope: !138, file: !4, line: 768, size: 256, align: 64, elements: !152)
!152 = !{!153, !154}
!153 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !151, file: !4, line: 768, baseType: !80, size: 32, align: 32)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !151, file: !4, line: 768, baseType: !155, size: 256, align: 64)
!155 = !DICompositeType(tag: DW_TAG_array_type, baseType: !58, size: 256, align: 64, elements: !156)
!156 = !{!157}
!157 = !DISubrange(count: 4)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !138, file: !4, line: 768, baseType: !61, size: 64, align: 64, offset: 640)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !138, file: !4, line: 768, baseType: !73, size: 32, align: 32, offset: 704)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !138, file: !4, line: 769, baseType: !161, size: 64, align: 64, offset: 768)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !162)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DISubroutineType(types: !164)
!164 = !{null, !165}
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !138, file: !4, line: 769, baseType: !57, size: 128, align: 64, offset: 832)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !138, file: !4, line: 769, baseType: !80, size: 32, align: 32, offset: 960)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !69, file: !4, line: 1482, baseType: !169, size: 448, align: 64, offset: 2432)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !87, line: 130, baseType: !170)
!170 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !108, line: 213, baseType: !171)
!171 = !DICompositeType(tag: DW_TAG_union_type, file: !108, line: 173, size: 448, align: 64, elements: !172)
!172 = !{!173, !187, !191}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !171, file: !108, line: 192, baseType: !174, size: 448, align: 64)
!174 = !DICompositeType(tag: DW_TAG_structure_type, scope: !171, file: !108, line: 176, size: 448, align: 64, elements: !175)
!175 = !{!176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !174, file: !108, line: 178, baseType: !80, size: 32, align: 32)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !174, file: !108, line: 179, baseType: !73, size: 32, align: 32, offset: 32)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !174, file: !108, line: 180, baseType: !73, size: 32, align: 32, offset: 64)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !174, file: !108, line: 181, baseType: !73, size: 32, align: 32, offset: 96)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !174, file: !108, line: 182, baseType: !73, size: 32, align: 32, offset: 128)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !174, file: !108, line: 183, baseType: !73, size: 32, align: 32, offset: 160)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !174, file: !108, line: 184, baseType: !80, size: 32, align: 32, offset: 192)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !174, file: !108, line: 185, baseType: !80, size: 32, align: 32, offset: 224)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !174, file: !108, line: 186, baseType: !78, size: 64, align: 64, offset: 256)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !174, file: !108, line: 187, baseType: !78, size: 64, align: 64, offset: 320)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !174, file: !108, line: 190, baseType: !73, size: 32, align: 32, offset: 384)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !171, file: !108, line: 211, baseType: !188, size: 448, align: 8)
!188 = !DICompositeType(tag: DW_TAG_array_type, baseType: !131, size: 448, align: 8, elements: !189)
!189 = !{!190}
!190 = !DISubrange(count: 56)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !171, file: !108, line: 212, baseType: !135, size: 64, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !69, file: !4, line: 1482, baseType: !61, size: 64, align: 64, offset: 2880)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 2944)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 3072)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 3200)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 3328)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !69, file: !4, line: 1482, baseType: !57, size: 128, align: 64, offset: 3456)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !69, file: !4, line: 1482, baseType: !199, size: 64, align: 64, offset: 3584)
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!200 = !DISubroutineType(types: !201)
!201 = !{null}
!202 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !69, file: !4, line: 1482, baseType: !86, size: 448, align: 64, offset: 3648)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !69, file: !4, line: 1482, baseType: !80, size: 32, align: 32, offset: 4096)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !69, file: !4, line: 1482, baseType: !205, size: 128, align: 64, offset: 4160)
!205 = !DICompositeType(tag: DW_TAG_structure_type, scope: !69, file: !4, line: 1482, size: 128, align: 64, elements: !206)
!206 = !{!207, !208}
!207 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !205, file: !4, line: 1482, baseType: !58, size: 64, align: 64)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !205, file: !4, line: 1482, baseType: !73, size: 32, align: 32, offset: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !69, file: !4, line: 1482, baseType: !210, size: 64, align: 64, offset: 4288)
!210 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !211, line: 55, baseType: !78)
!211 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!212 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !69, file: !4, line: 1482, baseType: !210, size: 64, align: 64, offset: 4352)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !69, file: !4, line: 1482, baseType: !214, size: 64, align: 32, offset: 4416)
!214 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 64, align: 32, elements: !59)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !69, file: !4, line: 1482, baseType: !86, size: 448, align: 64, offset: 4480)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !69, file: !4, line: 1482, baseType: !217, size: 1216, align: 64, offset: 4928)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !218)
!218 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !219)
!219 = !{!220, !221, !222, !223, !224, !225, !230, !231, !232, !238, !239, !247, !248}
!220 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !218, file: !4, line: 1326, baseType: !58, size: 64, align: 64)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !218, file: !4, line: 1326, baseType: !67, size: 64, align: 64, offset: 64)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !218, file: !4, line: 1326, baseType: !143, size: 32, align: 32, offset: 128)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !218, file: !4, line: 1326, baseType: !145, size: 64, align: 64, offset: 192)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !218, file: !4, line: 1326, baseType: !57, size: 128, align: 64, offset: 256)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !218, file: !4, line: 1326, baseType: !226, size: 256, align: 64, offset: 384)
!226 = !DICompositeType(tag: DW_TAG_union_type, scope: !218, file: !4, line: 1326, size: 256, align: 64, elements: !227)
!227 = !{!228, !229}
!228 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !226, file: !4, line: 1326, baseType: !80, size: 32, align: 32)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !226, file: !4, line: 1326, baseType: !155, size: 256, align: 64)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !218, file: !4, line: 1326, baseType: !61, size: 64, align: 64, offset: 640)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !218, file: !4, line: 1326, baseType: !73, size: 32, align: 32, offset: 704)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !218, file: !4, line: 1327, baseType: !233, size: 64, align: 64, offset: 768)
!233 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !234)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!235 = !DISubroutineType(types: !236)
!236 = !{null, !237, !80}
!237 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !217, size: 64, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !218, file: !4, line: 1328, baseType: !80, size: 32, align: 32, offset: 832)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !218, file: !4, line: 1329, baseType: !240, size: 256, align: 64, offset: 896)
!240 = !DICompositeType(tag: DW_TAG_structure_type, scope: !218, file: !4, line: 1329, size: 256, align: 64, elements: !241)
!241 = !{!242, !244, !245, !246}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !240, file: !4, line: 1329, baseType: !243, size: 64, align: 64)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !240, file: !4, line: 1329, baseType: !243, size: 64, align: 64, offset: 64)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !240, file: !4, line: 1329, baseType: !243, size: 64, align: 64, offset: 128)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !240, file: !4, line: 1329, baseType: !80, size: 32, align: 32, offset: 192)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !218, file: !4, line: 1329, baseType: !73, size: 32, align: 32, offset: 1152)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !218, file: !4, line: 1329, baseType: !73, size: 32, align: 32, offset: 1184)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !69, file: !4, line: 1482, baseType: !80, size: 32, align: 32, offset: 6144)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !69, file: !4, line: 1482, baseType: !86, size: 448, align: 64, offset: 6208)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !69, file: !4, line: 1482, baseType: !58, size: 64, align: 64, offset: 6656)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !69, file: !4, line: 1482, baseType: !80, size: 32, align: 32, offset: 6720)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !63, file: !4, line: 426, baseType: !143, size: 32, align: 32, offset: 128)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !63, file: !4, line: 426, baseType: !145, size: 64, align: 64, offset: 192)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !63, file: !4, line: 426, baseType: !57, size: 128, align: 64, offset: 256)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !63, file: !4, line: 426, baseType: !257, size: 256, align: 64, offset: 384)
!257 = !DICompositeType(tag: DW_TAG_union_type, scope: !63, file: !4, line: 426, size: 256, align: 64, elements: !258)
!258 = !{!259, !260}
!259 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !257, file: !4, line: 426, baseType: !80, size: 32, align: 32)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !257, file: !4, line: 426, baseType: !155, size: 256, align: 64)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !63, file: !4, line: 426, baseType: !61, size: 64, align: 64, offset: 640)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !63, file: !4, line: 426, baseType: !73, size: 32, align: 32, offset: 704)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !131, size: 64, align: 64)
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__signal_msg_t", file: !1, line: 35, baseType: !266)
!266 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 32, size: 128, align: 64, elements: !267)
!267 = !{!268, !269}
!268 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !266, file: !1, line: 33, baseType: !237, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !266, file: !1, line: 34, baseType: !80, size: 32, align: 32, offset: 64)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sighandler_t", file: !271, line: 85, baseType: !272)
!271 = !DIFile(filename: "/usr/include/signal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!272 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !273, size: 64, align: 64)
!273 = !DISubroutineType(types: !274)
!274 = !{null, !80}
!275 = !{!276, !278, !281, !284, !287, !290, !293, !294, !297, !298, !299, !302, !303, !306, !309, !323, !324, !327, !334, !337, !340, !341, !344, !345, !346, !349, !350, !351, !354}
!276 = distinct !DISubprogram(name: "uv__signal_global_once_init", scope: !1, file: !1, line: 98, type: !200, isLocal: false, isDefinition: true, scopeLine: 98, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!277 = !{}
!278 = distinct !DISubprogram(name: "uv__signal_loop_fork", scope: !1, file: !1, line: 265, type: !279, isLocal: false, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!279 = !DISubroutineType(types: !280)
!280 = !{!80, !67}
!281 = distinct !DISubprogram(name: "uv__signal_loop_cleanup", scope: !1, file: !1, line: 275, type: !282, isLocal: false, isDefinition: true, scopeLine: 275, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!282 = !DISubroutineType(types: !283)
!283 = !{null, !67}
!284 = distinct !DISubprogram(name: "uv_signal_init", scope: !1, file: !1, line: 303, type: !285, isLocal: false, isDefinition: true, scopeLine: 303, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!285 = !DISubroutineType(types: !286)
!286 = !{!80, !67, !237}
!287 = distinct !DISubprogram(name: "uv__signal_close", scope: !1, file: !1, line: 319, type: !288, isLocal: false, isDefinition: true, scopeLine: 319, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!288 = !DISubroutineType(types: !289)
!289 = !{null, !237}
!290 = distinct !DISubprogram(name: "uv_signal_start", scope: !1, file: !1, line: 333, type: !291, isLocal: false, isDefinition: true, scopeLine: 333, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!291 = !DISubroutineType(types: !292)
!292 = !{!80, !237, !233, !80}
!293 = distinct !DISubprogram(name: "uv_signal_start_oneshot", scope: !1, file: !1, line: 338, type: !291, isLocal: false, isDefinition: true, scopeLine: 340, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!294 = distinct !DISubprogram(name: "uv_signal_stop", scope: !1, file: !1, line: 515, type: !295, isLocal: false, isDefinition: true, scopeLine: 515, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!295 = !DISubroutineType(types: !296)
!296 = !{!80, !237}
!297 = distinct !DISubprogram(name: "uv__signal_global_init", scope: !1, file: !1, line: 63, type: !200, isLocal: true, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!298 = distinct !DISubprogram(name: "uv__signal_global_reinit", scope: !1, file: !1, line: 82, type: !200, isLocal: true, isDefinition: true, scopeLine: 82, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!299 = distinct !DISubprogram(name: "uv__signal_unlock", scope: !1, file: !1, line: 116, type: !300, isLocal: true, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!300 = !DISubroutineType(types: !301)
!301 = !{!80}
!302 = distinct !DISubprogram(name: "uv__signal_loop_once_init", scope: !1, file: !1, line: 245, type: !279, isLocal: true, isDefinition: true, scopeLine: 245, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!303 = distinct !DISubprogram(name: "uv__signal_event", scope: !1, file: !1, line: 409, type: !304, isLocal: true, isDefinition: true, scopeLine: 411, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!304 = !DISubroutineType(types: !305)
!305 = !{null, !67, !85, !73}
!306 = distinct !DISubprogram(name: "uv__signal_start", scope: !1, file: !1, line: 345, type: !307, isLocal: true, isDefinition: true, scopeLine: 348, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!307 = !DISubroutineType(types: !308)
!308 = !{!80, !237, !233, !80, !80}
!309 = distinct !DISubprogram(name: "uv__signal_block_and_lock", scope: !1, file: !1, line: 128, type: !310, isLocal: true, isDefinition: true, scopeLine: 128, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!310 = !DISubroutineType(types: !311)
!311 = !{null, !312}
!312 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !313, size: 64, align: 64)
!313 = !DIDerivedType(tag: DW_TAG_typedef, name: "sigset_t", file: !314, line: 37, baseType: !315)
!314 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/select.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sigset_t", file: !316, line: 30, baseType: !317)
!316 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sigset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!317 = !DICompositeType(tag: DW_TAG_structure_type, file: !316, line: 27, size: 1024, align: 64, elements: !318)
!318 = !{!319}
!319 = !DIDerivedType(tag: DW_TAG_member, name: "__val", scope: !317, file: !316, line: 29, baseType: !320, size: 1024, align: 64)
!320 = !DICompositeType(tag: DW_TAG_array_type, baseType: !78, size: 1024, align: 64, elements: !321)
!321 = !{!322}
!322 = !DISubrange(count: 16)
!323 = distinct !DISubprogram(name: "uv__signal_lock", scope: !1, file: !1, line: 104, type: !300, isLocal: true, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!324 = distinct !DISubprogram(name: "uv__signal_first_handle", scope: !1, file: !1, line: 151, type: !325, isLocal: true, isDefinition: true, scopeLine: 151, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!325 = !DISubroutineType(types: !326)
!326 = !{!237, !80}
!327 = distinct !DISubprogram(name: "uv__signal_tree_s_RB_NFIND", scope: !1, file: !1, line: 57, type: !328, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!328 = !DISubroutineType(types: !329)
!329 = !{!243, !330, !243}
!330 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !331, size: 64, align: 64)
!331 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__signal_tree_s", file: !1, line: 37, size: 64, align: 64, elements: !332)
!332 = !{!333}
!333 = !DIDerivedType(tag: DW_TAG_member, name: "rbh_root", scope: !331, file: !1, line: 37, baseType: !243, size: 64, align: 64)
!334 = distinct !DISubprogram(name: "uv__signal_compare", scope: !1, file: !1, line: 485, type: !335, isLocal: true, isDefinition: true, scopeLine: 485, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!335 = !DISubroutineType(types: !336)
!336 = !{!80, !237, !237}
!337 = distinct !DISubprogram(name: "uv__signal_register_handler", scope: !1, file: !1, line: 210, type: !338, isLocal: true, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!338 = !DISubroutineType(types: !339)
!339 = !{!80, !80, !80}
!340 = distinct !DISubprogram(name: "uv__signal_handler", scope: !1, file: !1, line: 169, type: !273, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!341 = distinct !DISubprogram(name: "uv__signal_tree_s_RB_NEXT", scope: !1, file: !1, line: 57, type: !342, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!342 = !DISubroutineType(types: !343)
!343 = !{!243, !243}
!344 = distinct !DISubprogram(name: "uv__signal_unlock_and_unblock", scope: !1, file: !1, line: 142, type: !310, isLocal: true, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!345 = distinct !DISubprogram(name: "uv__signal_tree_s_RB_INSERT", scope: !1, file: !1, line: 57, type: !328, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!346 = distinct !DISubprogram(name: "uv__signal_tree_s_RB_INSERT_COLOR", scope: !1, file: !1, line: 57, type: !347, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!347 = !DISubroutineType(types: !348)
!348 = !{null, !330, !243}
!349 = distinct !DISubprogram(name: "uv__signal_stop", scope: !1, file: !1, line: 522, type: !288, isLocal: true, isDefinition: true, scopeLine: 522, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!350 = distinct !DISubprogram(name: "uv__signal_tree_s_RB_REMOVE", scope: !1, file: !1, line: 57, type: !328, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!351 = distinct !DISubprogram(name: "uv__signal_tree_s_RB_REMOVE_COLOR", scope: !1, file: !1, line: 57, type: !352, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!352 = !DISubroutineType(types: !353)
!353 = !{null, !330, !243, !243}
!354 = distinct !DISubprogram(name: "uv__signal_unregister_handler", scope: !1, file: !1, line: 229, type: !273, isLocal: true, isDefinition: true, scopeLine: 229, flags: DIFlagPrototyped, isOptimized: false, variables: !277)
!355 = !{!356, !359, !360}
!356 = !DIGlobalVariable(name: "uv__signal_global_init_guard", scope: !0, file: !1, line: 51, type: !357, isLocal: true, isDefinition: true, variable: i32* @uv__signal_global_init_guard)
!357 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_once_t", file: !87, line: 127, baseType: !358)
!358 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_once_t", file: !108, line: 167, baseType: !80)
!359 = !DIGlobalVariable(name: "uv__signal_lock_pipefd", scope: !0, file: !1, line: 54, type: !214, isLocal: true, isDefinition: true, variable: [2 x i32]* @uv__signal_lock_pipefd)
!360 = !DIGlobalVariable(name: "uv__signal_tree", scope: !0, file: !1, line: 52, type: !331, isLocal: true, isDefinition: true, variable: %struct.uv__signal_tree_s* @uv__signal_tree)
!361 = !{i32 2, !"Dwarf Version", i32 4}
!362 = !{i32 2, !"Debug Info Version", i32 3}
!363 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!364 = !DILocation(line: 99, column: 3, scope: !276)
!365 = !DILocation(line: 100, column: 1, scope: !276)
!366 = !DILocation(line: 64, column: 8, scope: !367)
!367 = distinct !DILexicalBlock(scope: !297, file: !1, line: 64, column: 7)
!368 = !DILocation(line: 64, column: 7, scope: !297)
!369 = !DILocation(line: 71, column: 9, scope: !370)
!370 = distinct !DILexicalBlock(scope: !367, file: !1, line: 71, column: 9)
!371 = !DILocation(line: 71, column: 9, scope: !367)
!372 = !DILocation(line: 72, column: 7, scope: !370)
!373 = !DILocation(line: 71, column: 61, scope: !374)
!374 = !DILexicalBlockFile(scope: !370, file: !1, discriminator: 1)
!375 = !DILocation(line: 74, column: 7, scope: !376)
!376 = distinct !DILexicalBlock(scope: !297, file: !1, line: 74, column: 7)
!377 = !DILocation(line: 74, column: 7, scope: !297)
!378 = !DILocation(line: 75, column: 5, scope: !376)
!379 = !DILocation(line: 77, column: 7, scope: !380)
!380 = distinct !DILexicalBlock(scope: !297, file: !1, line: 77, column: 7)
!381 = !DILocation(line: 77, column: 7, scope: !297)
!382 = !DILocation(line: 78, column: 5, scope: !380)
!383 = !DILocation(line: 79, column: 1, scope: !297)
!384 = !DILocalVariable(name: "loop", arg: 1, scope: !278, file: !1, line: 265, type: !67)
!385 = !DIExpression()
!386 = !DILocation(line: 265, column: 37, scope: !278)
!387 = !DILocation(line: 266, column: 15, scope: !278)
!388 = !DILocation(line: 266, column: 22, scope: !278)
!389 = !DILocation(line: 266, column: 28, scope: !278)
!390 = !DILocation(line: 266, column: 3, scope: !278)
!391 = !DILocation(line: 267, column: 13, scope: !278)
!392 = !DILocation(line: 267, column: 19, scope: !278)
!393 = !DILocation(line: 267, column: 3, scope: !278)
!394 = !DILocation(line: 268, column: 13, scope: !278)
!395 = !DILocation(line: 268, column: 19, scope: !278)
!396 = !DILocation(line: 268, column: 3, scope: !278)
!397 = !DILocation(line: 269, column: 3, scope: !278)
!398 = !DILocation(line: 269, column: 9, scope: !278)
!399 = !DILocation(line: 269, column: 26, scope: !278)
!400 = !DILocation(line: 270, column: 3, scope: !278)
!401 = !DILocation(line: 270, column: 9, scope: !278)
!402 = !DILocation(line: 270, column: 26, scope: !278)
!403 = !DILocation(line: 271, column: 36, scope: !278)
!404 = !DILocation(line: 271, column: 10, scope: !278)
!405 = !DILocation(line: 271, column: 3, scope: !278)
!406 = !DILocalVariable(name: "loop", arg: 1, scope: !302, file: !1, line: 245, type: !67)
!407 = !DILocation(line: 245, column: 49, scope: !302)
!408 = !DILocalVariable(name: "err", scope: !302, file: !1, line: 246, type: !80)
!409 = !DILocation(line: 246, column: 7, scope: !302)
!410 = !DILocation(line: 249, column: 7, scope: !411)
!411 = distinct !DILexicalBlock(scope: !302, file: !1, line: 249, column: 7)
!412 = !DILocation(line: 249, column: 13, scope: !411)
!413 = !DILocation(line: 249, column: 30, scope: !411)
!414 = !DILocation(line: 249, column: 7, scope: !302)
!415 = !DILocation(line: 250, column: 5, scope: !411)
!416 = !DILocation(line: 252, column: 23, scope: !302)
!417 = !DILocation(line: 252, column: 29, scope: !302)
!418 = !DILocation(line: 252, column: 9, scope: !302)
!419 = !DILocation(line: 252, column: 7, scope: !302)
!420 = !DILocation(line: 253, column: 7, scope: !421)
!421 = distinct !DILexicalBlock(scope: !302, file: !1, line: 253, column: 7)
!422 = !DILocation(line: 253, column: 7, scope: !302)
!423 = !DILocation(line: 254, column: 12, scope: !421)
!424 = !DILocation(line: 254, column: 5, scope: !421)
!425 = !DILocation(line: 256, column: 16, scope: !302)
!426 = !DILocation(line: 256, column: 22, scope: !302)
!427 = !DILocation(line: 258, column: 15, scope: !302)
!428 = !DILocation(line: 258, column: 21, scope: !302)
!429 = !DILocation(line: 256, column: 3, scope: !302)
!430 = !DILocation(line: 259, column: 16, scope: !302)
!431 = !DILocation(line: 259, column: 23, scope: !302)
!432 = !DILocation(line: 259, column: 29, scope: !302)
!433 = !DILocation(line: 259, column: 3, scope: !302)
!434 = !DILocation(line: 261, column: 3, scope: !302)
!435 = !DILocation(line: 262, column: 1, scope: !302)
!436 = !DILocalVariable(name: "loop", arg: 1, scope: !281, file: !1, line: 275, type: !67)
!437 = !DILocation(line: 275, column: 41, scope: !281)
!438 = !DILocalVariable(name: "q", scope: !281, file: !1, line: 276, type: !54)
!439 = !DILocation(line: 276, column: 10, scope: !281)
!440 = !DILocation(line: 284, column: 3, scope: !441)
!441 = distinct !DILexicalBlock(scope: !281, file: !1, line: 284, column: 3)
!442 = !DILocation(line: 284, column: 3, scope: !443)
!443 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 1)
!444 = distinct !DILexicalBlock(scope: !441, file: !1, line: 284, column: 3)
!445 = !DILocalVariable(name: "handle", scope: !446, file: !1, line: 285, type: !61)
!446 = distinct !DILexicalBlock(scope: !444, file: !1, line: 284, column: 41)
!447 = !DILocation(line: 285, column: 18, scope: !446)
!448 = !DILocation(line: 285, column: 27, scope: !446)
!449 = !DILocation(line: 287, column: 9, scope: !450)
!450 = distinct !DILexicalBlock(scope: !446, file: !1, line: 287, column: 9)
!451 = !DILocation(line: 287, column: 17, scope: !450)
!452 = !DILocation(line: 287, column: 22, scope: !450)
!453 = !DILocation(line: 287, column: 9, scope: !446)
!454 = !DILocation(line: 288, column: 38, scope: !450)
!455 = !DILocation(line: 288, column: 23, scope: !450)
!456 = !DILocation(line: 288, column: 7, scope: !450)
!457 = !DILocation(line: 289, column: 3, scope: !446)
!458 = !DILocation(line: 284, column: 3, scope: !459)
!459 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 2)
!460 = !DILocation(line: 291, column: 7, scope: !461)
!461 = distinct !DILexicalBlock(scope: !281, file: !1, line: 291, column: 7)
!462 = !DILocation(line: 291, column: 13, scope: !461)
!463 = !DILocation(line: 291, column: 30, scope: !461)
!464 = !DILocation(line: 291, column: 7, scope: !281)
!465 = !DILocation(line: 292, column: 15, scope: !466)
!466 = distinct !DILexicalBlock(scope: !461, file: !1, line: 291, column: 37)
!467 = !DILocation(line: 292, column: 21, scope: !466)
!468 = !DILocation(line: 292, column: 5, scope: !466)
!469 = !DILocation(line: 293, column: 5, scope: !466)
!470 = !DILocation(line: 293, column: 11, scope: !466)
!471 = !DILocation(line: 293, column: 28, scope: !466)
!472 = !DILocation(line: 294, column: 3, scope: !466)
!473 = !DILocation(line: 296, column: 7, scope: !474)
!474 = distinct !DILexicalBlock(scope: !281, file: !1, line: 296, column: 7)
!475 = !DILocation(line: 296, column: 13, scope: !474)
!476 = !DILocation(line: 296, column: 30, scope: !474)
!477 = !DILocation(line: 296, column: 7, scope: !281)
!478 = !DILocation(line: 297, column: 15, scope: !479)
!479 = distinct !DILexicalBlock(scope: !474, file: !1, line: 296, column: 37)
!480 = !DILocation(line: 297, column: 21, scope: !479)
!481 = !DILocation(line: 297, column: 5, scope: !479)
!482 = !DILocation(line: 298, column: 5, scope: !479)
!483 = !DILocation(line: 298, column: 11, scope: !479)
!484 = !DILocation(line: 298, column: 28, scope: !479)
!485 = !DILocation(line: 299, column: 3, scope: !479)
!486 = !DILocation(line: 300, column: 1, scope: !281)
!487 = !DILocalVariable(name: "handle", arg: 1, scope: !349, file: !1, line: 522, type: !237)
!488 = !DILocation(line: 522, column: 42, scope: !349)
!489 = !DILocalVariable(name: "removed_handle", scope: !349, file: !1, line: 523, type: !237)
!490 = !DILocation(line: 523, column: 16, scope: !349)
!491 = !DILocalVariable(name: "saved_sigmask", scope: !349, file: !1, line: 524, type: !313)
!492 = !DILocation(line: 524, column: 12, scope: !349)
!493 = !DILocalVariable(name: "first_handle", scope: !349, file: !1, line: 525, type: !237)
!494 = !DILocation(line: 525, column: 16, scope: !349)
!495 = !DILocalVariable(name: "rem_oneshot", scope: !349, file: !1, line: 526, type: !80)
!496 = !DILocation(line: 526, column: 7, scope: !349)
!497 = !DILocalVariable(name: "first_oneshot", scope: !349, file: !1, line: 527, type: !80)
!498 = !DILocation(line: 527, column: 7, scope: !349)
!499 = !DILocalVariable(name: "ret", scope: !349, file: !1, line: 528, type: !80)
!500 = !DILocation(line: 528, column: 7, scope: !349)
!501 = !DILocation(line: 531, column: 7, scope: !502)
!502 = distinct !DILexicalBlock(scope: !349, file: !1, line: 531, column: 7)
!503 = !DILocation(line: 531, column: 15, scope: !502)
!504 = !DILocation(line: 531, column: 22, scope: !502)
!505 = !DILocation(line: 531, column: 7, scope: !349)
!506 = !DILocation(line: 532, column: 5, scope: !502)
!507 = !DILocation(line: 534, column: 3, scope: !349)
!508 = !DILocation(line: 536, column: 20, scope: !349)
!509 = !DILocation(line: 536, column: 18, scope: !349)
!510 = !DILocation(line: 537, column: 3, scope: !349)
!511 = !DILocation(line: 537, column: 3, scope: !512)
!512 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 1)
!513 = !DILocation(line: 537, column: 3, scope: !514)
!514 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 2)
!515 = !DILocation(line: 537, column: 3, scope: !516)
!516 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 3)
!517 = !DILocation(line: 538, column: 10, scope: !349)
!518 = !DILocation(line: 543, column: 42, scope: !349)
!519 = !DILocation(line: 543, column: 50, scope: !349)
!520 = !DILocation(line: 543, column: 18, scope: !349)
!521 = !DILocation(line: 543, column: 16, scope: !349)
!522 = !DILocation(line: 544, column: 7, scope: !523)
!523 = distinct !DILexicalBlock(scope: !349, file: !1, line: 544, column: 7)
!524 = !DILocation(line: 544, column: 20, scope: !523)
!525 = !DILocation(line: 544, column: 7, scope: !349)
!526 = !DILocation(line: 545, column: 35, scope: !527)
!527 = distinct !DILexicalBlock(scope: !523, file: !1, line: 544, column: 29)
!528 = !DILocation(line: 545, column: 43, scope: !527)
!529 = !DILocation(line: 545, column: 5, scope: !527)
!530 = !DILocation(line: 546, column: 3, scope: !527)
!531 = !DILocation(line: 547, column: 19, scope: !532)
!532 = distinct !DILexicalBlock(scope: !523, file: !1, line: 546, column: 10)
!533 = !DILocation(line: 547, column: 27, scope: !532)
!534 = !DILocation(line: 547, column: 33, scope: !532)
!535 = !DILocation(line: 547, column: 17, scope: !532)
!536 = !DILocation(line: 548, column: 21, scope: !532)
!537 = !DILocation(line: 548, column: 35, scope: !532)
!538 = !DILocation(line: 548, column: 41, scope: !532)
!539 = !DILocation(line: 548, column: 19, scope: !532)
!540 = !DILocation(line: 549, column: 9, scope: !541)
!541 = distinct !DILexicalBlock(scope: !532, file: !1, line: 549, column: 9)
!542 = !DILocation(line: 549, column: 23, scope: !541)
!543 = !DILocation(line: 549, column: 27, scope: !544)
!544 = !DILexicalBlockFile(scope: !541, file: !1, discriminator: 1)
!545 = !DILocation(line: 549, column: 9, scope: !544)
!546 = !DILocation(line: 550, column: 41, scope: !547)
!547 = distinct !DILexicalBlock(scope: !541, file: !1, line: 549, column: 40)
!548 = !DILocation(line: 550, column: 49, scope: !547)
!549 = !DILocation(line: 550, column: 13, scope: !547)
!550 = !DILocation(line: 550, column: 11, scope: !547)
!551 = !DILocation(line: 551, column: 7, scope: !547)
!552 = !DILocation(line: 551, column: 7, scope: !553)
!553 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 1)
!554 = !DILocation(line: 551, column: 7, scope: !555)
!555 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 2)
!556 = !DILocation(line: 551, column: 7, scope: !557)
!557 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 3)
!558 = !DILocation(line: 552, column: 5, scope: !547)
!559 = !DILocation(line: 555, column: 3, scope: !349)
!560 = !DILocation(line: 557, column: 3, scope: !349)
!561 = !DILocation(line: 557, column: 11, scope: !349)
!562 = !DILocation(line: 557, column: 18, scope: !349)
!563 = !DILocation(line: 558, column: 3, scope: !349)
!564 = !DILocation(line: 558, column: 3, scope: !565)
!565 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 1)
!566 = distinct !DILexicalBlock(scope: !349, file: !1, line: 558, column: 3)
!567 = !DILocation(line: 558, column: 3, scope: !568)
!568 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 2)
!569 = !DILocation(line: 558, column: 3, scope: !570)
!570 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 3)
!571 = !DILocation(line: 558, column: 3, scope: !572)
!572 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 4)
!573 = !DILocation(line: 558, column: 3, scope: !574)
!574 = !DILexicalBlockFile(scope: !575, file: !1, discriminator: 5)
!575 = distinct !DILexicalBlock(scope: !566, file: !1, line: 558, column: 3)
!576 = !DILocation(line: 558, column: 3, scope: !577)
!577 = !DILexicalBlockFile(scope: !575, file: !1, discriminator: 6)
!578 = !DILocation(line: 558, column: 3, scope: !579)
!579 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 7)
!580 = !DILocation(line: 558, column: 3, scope: !581)
!581 = !DILexicalBlockFile(scope: !582, file: !1, discriminator: 8)
!582 = distinct !DILexicalBlock(scope: !566, file: !1, line: 558, column: 3)
!583 = !DILocation(line: 558, column: 3, scope: !584)
!584 = !DILexicalBlockFile(scope: !585, file: !1, discriminator: 9)
!585 = distinct !DILexicalBlock(scope: !582, file: !1, line: 558, column: 3)
!586 = !DILocation(line: 558, column: 3, scope: !587)
!587 = !DILexicalBlockFile(scope: !585, file: !1, discriminator: 10)
!588 = !DILocation(line: 558, column: 3, scope: !589)
!589 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 11)
!590 = !DILocation(line: 559, column: 1, scope: !349)
!591 = !DILocalVariable(name: "loop", arg: 1, scope: !284, file: !1, line: 303, type: !67)
!592 = !DILocation(line: 303, column: 31, scope: !284)
!593 = !DILocalVariable(name: "handle", arg: 2, scope: !284, file: !1, line: 303, type: !237)
!594 = !DILocation(line: 303, column: 50, scope: !284)
!595 = !DILocalVariable(name: "err", scope: !284, file: !1, line: 304, type: !80)
!596 = !DILocation(line: 304, column: 7, scope: !284)
!597 = !DILocation(line: 306, column: 35, scope: !284)
!598 = !DILocation(line: 306, column: 9, scope: !284)
!599 = !DILocation(line: 306, column: 7, scope: !284)
!600 = !DILocation(line: 307, column: 7, scope: !601)
!601 = distinct !DILexicalBlock(scope: !284, file: !1, line: 307, column: 7)
!602 = !DILocation(line: 307, column: 7, scope: !284)
!603 = !DILocation(line: 308, column: 12, scope: !601)
!604 = !DILocation(line: 308, column: 5, scope: !601)
!605 = !DILocation(line: 310, column: 3, scope: !284)
!606 = !DILocation(line: 310, column: 3, scope: !607)
!607 = !DILexicalBlockFile(scope: !608, file: !1, discriminator: 1)
!608 = distinct !DILexicalBlock(scope: !284, file: !1, line: 310, column: 3)
!609 = !DILocation(line: 310, column: 3, scope: !610)
!610 = !DILexicalBlockFile(scope: !611, file: !1, discriminator: 2)
!611 = distinct !DILexicalBlock(scope: !608, file: !1, line: 310, column: 3)
!612 = !DILocation(line: 310, column: 3, scope: !613)
!613 = !DILexicalBlockFile(scope: !608, file: !1, discriminator: 3)
!614 = !DILocation(line: 311, column: 3, scope: !284)
!615 = !DILocation(line: 311, column: 11, scope: !284)
!616 = !DILocation(line: 311, column: 18, scope: !284)
!617 = !DILocation(line: 312, column: 3, scope: !284)
!618 = !DILocation(line: 312, column: 11, scope: !284)
!619 = !DILocation(line: 312, column: 26, scope: !284)
!620 = !DILocation(line: 313, column: 3, scope: !284)
!621 = !DILocation(line: 313, column: 11, scope: !284)
!622 = !DILocation(line: 313, column: 30, scope: !284)
!623 = !DILocation(line: 315, column: 3, scope: !284)
!624 = !DILocation(line: 316, column: 1, scope: !284)
!625 = !DILocalVariable(name: "handle", arg: 1, scope: !287, file: !1, line: 319, type: !237)
!626 = !DILocation(line: 319, column: 36, scope: !287)
!627 = !DILocation(line: 321, column: 19, scope: !287)
!628 = !DILocation(line: 321, column: 3, scope: !287)
!629 = !DILocation(line: 327, column: 7, scope: !630)
!630 = distinct !DILexicalBlock(scope: !287, file: !1, line: 327, column: 7)
!631 = !DILocation(line: 327, column: 15, scope: !630)
!632 = !DILocation(line: 327, column: 33, scope: !630)
!633 = !DILocation(line: 327, column: 41, scope: !630)
!634 = !DILocation(line: 327, column: 30, scope: !630)
!635 = !DILocation(line: 327, column: 7, scope: !287)
!636 = !DILocation(line: 328, column: 43, scope: !637)
!637 = distinct !DILexicalBlock(scope: !630, file: !1, line: 327, column: 61)
!638 = !DILocation(line: 328, column: 28, scope: !637)
!639 = !DILocation(line: 328, column: 5, scope: !637)
!640 = !DILocation(line: 329, column: 3, scope: !637)
!641 = !DILocation(line: 330, column: 1, scope: !287)
!642 = !DILocalVariable(name: "handle", arg: 1, scope: !290, file: !1, line: 333, type: !237)
!643 = !DILocation(line: 333, column: 34, scope: !290)
!644 = !DILocalVariable(name: "signal_cb", arg: 2, scope: !290, file: !1, line: 333, type: !233)
!645 = !DILocation(line: 333, column: 55, scope: !290)
!646 = !DILocalVariable(name: "signum", arg: 3, scope: !290, file: !1, line: 333, type: !80)
!647 = !DILocation(line: 333, column: 70, scope: !290)
!648 = !DILocation(line: 334, column: 27, scope: !290)
!649 = !DILocation(line: 334, column: 35, scope: !290)
!650 = !DILocation(line: 334, column: 46, scope: !290)
!651 = !DILocation(line: 334, column: 10, scope: !290)
!652 = !DILocation(line: 334, column: 3, scope: !290)
!653 = !DILocalVariable(name: "handle", arg: 1, scope: !306, file: !1, line: 345, type: !237)
!654 = !DILocation(line: 345, column: 42, scope: !306)
!655 = !DILocalVariable(name: "signal_cb", arg: 2, scope: !306, file: !1, line: 346, type: !233)
!656 = !DILocation(line: 346, column: 42, scope: !306)
!657 = !DILocalVariable(name: "signum", arg: 3, scope: !306, file: !1, line: 347, type: !80)
!658 = !DILocation(line: 347, column: 33, scope: !306)
!659 = !DILocalVariable(name: "oneshot", arg: 4, scope: !306, file: !1, line: 348, type: !80)
!660 = !DILocation(line: 348, column: 33, scope: !306)
!661 = !DILocalVariable(name: "saved_sigmask", scope: !306, file: !1, line: 349, type: !313)
!662 = !DILocation(line: 349, column: 12, scope: !306)
!663 = !DILocalVariable(name: "err", scope: !306, file: !1, line: 350, type: !80)
!664 = !DILocation(line: 350, column: 7, scope: !306)
!665 = !DILocalVariable(name: "first_handle", scope: !306, file: !1, line: 351, type: !237)
!666 = !DILocation(line: 351, column: 16, scope: !306)
!667 = !DILocation(line: 353, column: 3, scope: !306)
!668 = !DILocation(line: 353, column: 3, scope: !669)
!669 = !DILexicalBlockFile(scope: !306, file: !1, discriminator: 1)
!670 = !DILocation(line: 353, column: 3, scope: !671)
!671 = !DILexicalBlockFile(scope: !306, file: !1, discriminator: 2)
!672 = !DILocation(line: 353, column: 3, scope: !673)
!673 = !DILexicalBlockFile(scope: !306, file: !1, discriminator: 3)
!674 = !DILocation(line: 359, column: 7, scope: !675)
!675 = distinct !DILexicalBlock(scope: !306, file: !1, line: 359, column: 7)
!676 = !DILocation(line: 359, column: 14, scope: !675)
!677 = !DILocation(line: 359, column: 7, scope: !306)
!678 = !DILocation(line: 360, column: 5, scope: !675)
!679 = !DILocation(line: 367, column: 7, scope: !680)
!680 = distinct !DILexicalBlock(scope: !306, file: !1, line: 367, column: 7)
!681 = !DILocation(line: 367, column: 17, scope: !680)
!682 = !DILocation(line: 367, column: 25, scope: !680)
!683 = !DILocation(line: 367, column: 14, scope: !680)
!684 = !DILocation(line: 367, column: 7, scope: !306)
!685 = !DILocation(line: 368, column: 25, scope: !686)
!686 = distinct !DILexicalBlock(scope: !680, file: !1, line: 367, column: 33)
!687 = !DILocation(line: 368, column: 5, scope: !686)
!688 = !DILocation(line: 368, column: 13, scope: !686)
!689 = !DILocation(line: 368, column: 23, scope: !686)
!690 = !DILocation(line: 369, column: 5, scope: !686)
!691 = !DILocation(line: 373, column: 7, scope: !692)
!692 = distinct !DILexicalBlock(scope: !306, file: !1, line: 373, column: 7)
!693 = !DILocation(line: 373, column: 15, scope: !692)
!694 = !DILocation(line: 373, column: 22, scope: !692)
!695 = !DILocation(line: 373, column: 7, scope: !306)
!696 = !DILocation(line: 374, column: 21, scope: !697)
!697 = distinct !DILexicalBlock(scope: !692, file: !1, line: 373, column: 28)
!698 = !DILocation(line: 374, column: 5, scope: !697)
!699 = !DILocation(line: 375, column: 3, scope: !697)
!700 = !DILocation(line: 377, column: 3, scope: !306)
!701 = !DILocation(line: 383, column: 42, scope: !306)
!702 = !DILocation(line: 383, column: 18, scope: !306)
!703 = !DILocation(line: 383, column: 16, scope: !306)
!704 = !DILocation(line: 384, column: 7, scope: !705)
!705 = distinct !DILexicalBlock(scope: !306, file: !1, line: 384, column: 7)
!706 = !DILocation(line: 384, column: 20, scope: !705)
!707 = !DILocation(line: 384, column: 28, scope: !705)
!708 = !DILocation(line: 385, column: 9, scope: !705)
!709 = !DILocation(line: 385, column: 17, scope: !705)
!710 = !DILocation(line: 385, column: 21, scope: !711)
!711 = !DILexicalBlockFile(scope: !705, file: !1, discriminator: 1)
!712 = !DILocation(line: 385, column: 35, scope: !711)
!713 = !DILocation(line: 385, column: 41, scope: !711)
!714 = !DILocation(line: 384, column: 7, scope: !669)
!715 = !DILocation(line: 386, column: 39, scope: !716)
!716 = distinct !DILexicalBlock(scope: !705, file: !1, line: 385, column: 66)
!717 = !DILocation(line: 386, column: 47, scope: !716)
!718 = !DILocation(line: 386, column: 11, scope: !716)
!719 = !DILocation(line: 386, column: 9, scope: !716)
!720 = !DILocation(line: 387, column: 9, scope: !721)
!721 = distinct !DILexicalBlock(scope: !716, file: !1, line: 387, column: 9)
!722 = !DILocation(line: 387, column: 9, scope: !716)
!723 = !DILocation(line: 389, column: 7, scope: !724)
!724 = distinct !DILexicalBlock(scope: !721, file: !1, line: 387, column: 14)
!725 = !DILocation(line: 390, column: 14, scope: !724)
!726 = !DILocation(line: 390, column: 7, scope: !724)
!727 = !DILocation(line: 392, column: 3, scope: !716)
!728 = !DILocation(line: 394, column: 20, scope: !306)
!729 = !DILocation(line: 394, column: 3, scope: !306)
!730 = !DILocation(line: 394, column: 11, scope: !306)
!731 = !DILocation(line: 394, column: 18, scope: !306)
!732 = !DILocation(line: 395, column: 7, scope: !733)
!733 = distinct !DILexicalBlock(scope: !306, file: !1, line: 395, column: 7)
!734 = !DILocation(line: 395, column: 7, scope: !306)
!735 = !DILocation(line: 396, column: 5, scope: !733)
!736 = !DILocation(line: 396, column: 13, scope: !733)
!737 = !DILocation(line: 396, column: 19, scope: !733)
!738 = !DILocation(line: 398, column: 3, scope: !306)
!739 = !DILocation(line: 400, column: 3, scope: !306)
!740 = !DILocation(line: 402, column: 23, scope: !306)
!741 = !DILocation(line: 402, column: 3, scope: !306)
!742 = !DILocation(line: 402, column: 11, scope: !306)
!743 = !DILocation(line: 402, column: 21, scope: !306)
!744 = !DILocation(line: 403, column: 3, scope: !306)
!745 = !DILocation(line: 403, column: 3, scope: !746)
!746 = !DILexicalBlockFile(scope: !747, file: !1, discriminator: 1)
!747 = distinct !DILexicalBlock(scope: !306, file: !1, line: 403, column: 3)
!748 = !DILocation(line: 403, column: 3, scope: !749)
!749 = !DILexicalBlockFile(scope: !747, file: !1, discriminator: 2)
!750 = !DILocation(line: 403, column: 3, scope: !751)
!751 = !DILexicalBlockFile(scope: !747, file: !1, discriminator: 3)
!752 = !DILocation(line: 403, column: 3, scope: !753)
!753 = !DILexicalBlockFile(scope: !747, file: !1, discriminator: 4)
!754 = !DILocation(line: 403, column: 3, scope: !755)
!755 = !DILexicalBlockFile(scope: !756, file: !1, discriminator: 5)
!756 = distinct !DILexicalBlock(scope: !747, file: !1, line: 403, column: 3)
!757 = !DILocation(line: 403, column: 3, scope: !758)
!758 = !DILexicalBlockFile(scope: !756, file: !1, discriminator: 6)
!759 = !DILocation(line: 403, column: 3, scope: !760)
!760 = !DILexicalBlockFile(scope: !747, file: !1, discriminator: 7)
!761 = !DILocation(line: 403, column: 3, scope: !762)
!762 = !DILexicalBlockFile(scope: !763, file: !1, discriminator: 8)
!763 = distinct !DILexicalBlock(scope: !747, file: !1, line: 403, column: 3)
!764 = !DILocation(line: 403, column: 3, scope: !765)
!765 = !DILexicalBlockFile(scope: !766, file: !1, discriminator: 9)
!766 = distinct !DILexicalBlock(scope: !763, file: !1, line: 403, column: 3)
!767 = !DILocation(line: 403, column: 3, scope: !768)
!768 = !DILexicalBlockFile(scope: !766, file: !1, discriminator: 10)
!769 = !DILocation(line: 403, column: 3, scope: !770)
!770 = !DILexicalBlockFile(scope: !747, file: !1, discriminator: 11)
!771 = !DILocation(line: 405, column: 3, scope: !306)
!772 = !DILocation(line: 406, column: 1, scope: !306)
!773 = !DILocalVariable(name: "handle", arg: 1, scope: !293, file: !1, line: 338, type: !237)
!774 = !DILocation(line: 338, column: 42, scope: !293)
!775 = !DILocalVariable(name: "signal_cb", arg: 2, scope: !293, file: !1, line: 339, type: !233)
!776 = !DILocation(line: 339, column: 42, scope: !293)
!777 = !DILocalVariable(name: "signum", arg: 3, scope: !293, file: !1, line: 340, type: !80)
!778 = !DILocation(line: 340, column: 33, scope: !293)
!779 = !DILocation(line: 341, column: 27, scope: !293)
!780 = !DILocation(line: 341, column: 35, scope: !293)
!781 = !DILocation(line: 341, column: 46, scope: !293)
!782 = !DILocation(line: 341, column: 10, scope: !293)
!783 = !DILocation(line: 341, column: 3, scope: !293)
!784 = !DILocalVariable(name: "handle", arg: 1, scope: !294, file: !1, line: 515, type: !237)
!785 = !DILocation(line: 515, column: 33, scope: !294)
!786 = !DILocation(line: 516, column: 3, scope: !294)
!787 = !DILocation(line: 516, column: 3, scope: !788)
!788 = !DILexicalBlockFile(scope: !294, file: !1, discriminator: 1)
!789 = !DILocation(line: 516, column: 3, scope: !790)
!790 = !DILexicalBlockFile(scope: !294, file: !1, discriminator: 2)
!791 = !DILocation(line: 516, column: 3, scope: !792)
!792 = !DILexicalBlockFile(scope: !294, file: !1, discriminator: 3)
!793 = !DILocation(line: 517, column: 19, scope: !294)
!794 = !DILocation(line: 517, column: 3, scope: !294)
!795 = !DILocation(line: 518, column: 3, scope: !294)
!796 = !DILocation(line: 90, column: 13, scope: !298)
!797 = !DILocation(line: 90, column: 3, scope: !298)
!798 = !DILocation(line: 91, column: 29, scope: !298)
!799 = !DILocation(line: 92, column: 13, scope: !298)
!800 = !DILocation(line: 92, column: 3, scope: !298)
!801 = !DILocation(line: 93, column: 29, scope: !298)
!802 = !DILocation(line: 94, column: 3, scope: !298)
!803 = !DILocation(line: 95, column: 1, scope: !298)
!804 = !DILocalVariable(name: "r", scope: !299, file: !1, line: 117, type: !80)
!805 = !DILocation(line: 117, column: 7, scope: !299)
!806 = !DILocalVariable(name: "data", scope: !299, file: !1, line: 118, type: !131)
!807 = !DILocation(line: 118, column: 8, scope: !299)
!808 = !DILocation(line: 120, column: 3, scope: !299)
!809 = !DILocation(line: 121, column: 15, scope: !810)
!810 = distinct !DILexicalBlock(scope: !299, file: !1, line: 120, column: 6)
!811 = !DILocation(line: 121, column: 9, scope: !810)
!812 = !DILocation(line: 121, column: 7, scope: !810)
!813 = !DILocation(line: 122, column: 3, scope: !810)
!814 = !DILocation(line: 122, column: 12, scope: !815)
!815 = !DILexicalBlockFile(scope: !299, file: !1, discriminator: 1)
!816 = !DILocation(line: 122, column: 14, scope: !815)
!817 = !DILocation(line: 122, column: 18, scope: !815)
!818 = !DILocation(line: 122, column: 21, scope: !819)
!819 = !DILexicalBlockFile(scope: !299, file: !1, discriminator: 2)
!820 = !DILocation(line: 122, column: 27, scope: !819)
!821 = !DILocation(line: 122, column: 3, scope: !822)
!822 = !DILexicalBlockFile(scope: !810, file: !1, discriminator: 3)
!823 = !DILocation(line: 124, column: 11, scope: !299)
!824 = !DILocation(line: 124, column: 13, scope: !299)
!825 = !DILocation(line: 124, column: 10, scope: !299)
!826 = !DILocation(line: 124, column: 3, scope: !299)
!827 = !DILocalVariable(name: "loop", arg: 1, scope: !303, file: !1, line: 409, type: !67)
!828 = !DILocation(line: 409, column: 41, scope: !303)
!829 = !DILocalVariable(name: "w", arg: 2, scope: !303, file: !1, line: 410, type: !85)
!830 = !DILocation(line: 410, column: 40, scope: !303)
!831 = !DILocalVariable(name: "events", arg: 3, scope: !303, file: !1, line: 411, type: !73)
!832 = !DILocation(line: 411, column: 43, scope: !303)
!833 = !DILocalVariable(name: "msg", scope: !303, file: !1, line: 412, type: !264)
!834 = !DILocation(line: 412, column: 21, scope: !303)
!835 = !DILocalVariable(name: "handle", scope: !303, file: !1, line: 413, type: !237)
!836 = !DILocation(line: 413, column: 16, scope: !303)
!837 = !DILocalVariable(name: "buf", scope: !303, file: !1, line: 414, type: !838)
!838 = !DICompositeType(tag: DW_TAG_array_type, baseType: !131, size: 4096, align: 8, elements: !839)
!839 = !{!840}
!840 = !DISubrange(count: 512)
!841 = !DILocation(line: 414, column: 8, scope: !303)
!842 = !DILocalVariable(name: "bytes", scope: !303, file: !1, line: 415, type: !843)
!843 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !844, line: 62, baseType: !78)
!844 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!845 = !DILocation(line: 415, column: 10, scope: !303)
!846 = !DILocalVariable(name: "end", scope: !303, file: !1, line: 415, type: !843)
!847 = !DILocation(line: 415, column: 17, scope: !303)
!848 = !DILocalVariable(name: "i", scope: !303, file: !1, line: 415, type: !843)
!849 = !DILocation(line: 415, column: 22, scope: !303)
!850 = !DILocalVariable(name: "r", scope: !303, file: !1, line: 416, type: !80)
!851 = !DILocation(line: 416, column: 7, scope: !303)
!852 = !DILocation(line: 418, column: 9, scope: !303)
!853 = !DILocation(line: 419, column: 7, scope: !303)
!854 = !DILocation(line: 421, column: 3, scope: !303)
!855 = !DILocation(line: 422, column: 14, scope: !856)
!856 = distinct !DILexicalBlock(scope: !303, file: !1, line: 421, column: 6)
!857 = !DILocation(line: 422, column: 20, scope: !856)
!858 = !DILocation(line: 422, column: 38, scope: !856)
!859 = !DILocation(line: 422, column: 44, scope: !856)
!860 = !DILocation(line: 422, column: 42, scope: !856)
!861 = !DILocation(line: 422, column: 65, scope: !856)
!862 = !DILocation(line: 422, column: 63, scope: !856)
!863 = !DILocation(line: 422, column: 9, scope: !856)
!864 = !DILocation(line: 422, column: 7, scope: !856)
!865 = !DILocation(line: 424, column: 9, scope: !866)
!866 = distinct !DILexicalBlock(scope: !856, file: !1, line: 424, column: 9)
!867 = !DILocation(line: 424, column: 11, scope: !866)
!868 = !DILocation(line: 424, column: 17, scope: !866)
!869 = !DILocation(line: 424, column: 20, scope: !870)
!870 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 1)
!871 = !DILocation(line: 424, column: 26, scope: !870)
!872 = !DILocation(line: 424, column: 9, scope: !870)
!873 = !DILocation(line: 425, column: 7, scope: !866)
!874 = !DILocation(line: 427, column: 9, scope: !875)
!875 = distinct !DILexicalBlock(scope: !856, file: !1, line: 427, column: 9)
!876 = !DILocation(line: 427, column: 11, scope: !875)
!877 = !DILocation(line: 427, column: 17, scope: !875)
!878 = !DILocation(line: 427, column: 21, scope: !879)
!879 = !DILexicalBlockFile(scope: !875, file: !1, discriminator: 1)
!880 = !DILocation(line: 427, column: 27, scope: !879)
!881 = !DILocation(line: 427, column: 37, scope: !879)
!882 = !DILocation(line: 427, column: 40, scope: !883)
!883 = !DILexicalBlockFile(scope: !875, file: !1, discriminator: 2)
!884 = !DILocation(line: 427, column: 46, scope: !883)
!885 = !DILocation(line: 427, column: 9, scope: !883)
!886 = !DILocation(line: 432, column: 11, scope: !887)
!887 = distinct !DILexicalBlock(scope: !888, file: !1, line: 432, column: 11)
!888 = distinct !DILexicalBlock(scope: !875, file: !1, line: 427, column: 63)
!889 = !DILocation(line: 432, column: 17, scope: !887)
!890 = !DILocation(line: 432, column: 11, scope: !888)
!891 = !DILocation(line: 433, column: 9, scope: !887)
!892 = !DILocation(line: 436, column: 7, scope: !888)
!893 = !DILocation(line: 440, column: 9, scope: !894)
!894 = distinct !DILexicalBlock(scope: !856, file: !1, line: 440, column: 9)
!895 = !DILocation(line: 440, column: 11, scope: !894)
!896 = !DILocation(line: 440, column: 9, scope: !856)
!897 = !DILocation(line: 441, column: 7, scope: !894)
!898 = !DILocation(line: 443, column: 14, scope: !856)
!899 = !DILocation(line: 443, column: 11, scope: !856)
!900 = !DILocation(line: 446, column: 12, scope: !856)
!901 = !DILocation(line: 446, column: 18, scope: !856)
!902 = !DILocation(line: 446, column: 46, scope: !856)
!903 = !DILocation(line: 446, column: 9, scope: !856)
!904 = !DILocation(line: 448, column: 12, scope: !905)
!905 = distinct !DILexicalBlock(scope: !856, file: !1, line: 448, column: 5)
!906 = !DILocation(line: 448, column: 10, scope: !905)
!907 = !DILocation(line: 448, column: 17, scope: !908)
!908 = !DILexicalBlockFile(scope: !909, file: !1, discriminator: 1)
!909 = distinct !DILexicalBlock(scope: !905, file: !1, line: 448, column: 5)
!910 = !DILocation(line: 448, column: 21, scope: !908)
!911 = !DILocation(line: 448, column: 19, scope: !908)
!912 = !DILocation(line: 448, column: 5, scope: !908)
!913 = !DILocation(line: 449, column: 34, scope: !914)
!914 = distinct !DILexicalBlock(scope: !909, file: !1, line: 448, column: 57)
!915 = !DILocation(line: 449, column: 40, scope: !914)
!916 = !DILocation(line: 449, column: 38, scope: !914)
!917 = !DILocation(line: 449, column: 13, scope: !914)
!918 = !DILocation(line: 449, column: 11, scope: !914)
!919 = !DILocation(line: 450, column: 16, scope: !914)
!920 = !DILocation(line: 450, column: 21, scope: !914)
!921 = !DILocation(line: 450, column: 14, scope: !914)
!922 = !DILocation(line: 452, column: 11, scope: !923)
!923 = distinct !DILexicalBlock(scope: !914, file: !1, line: 452, column: 11)
!924 = !DILocation(line: 452, column: 16, scope: !923)
!925 = !DILocation(line: 452, column: 26, scope: !923)
!926 = !DILocation(line: 452, column: 34, scope: !923)
!927 = !DILocation(line: 452, column: 23, scope: !923)
!928 = !DILocation(line: 452, column: 11, scope: !914)
!929 = !DILocation(line: 453, column: 9, scope: !930)
!930 = distinct !DILexicalBlock(scope: !923, file: !1, line: 452, column: 42)
!931 = !DILocation(line: 453, column: 9, scope: !932)
!932 = !DILexicalBlockFile(scope: !930, file: !1, discriminator: 1)
!933 = !DILocation(line: 453, column: 9, scope: !934)
!934 = !DILexicalBlockFile(scope: !930, file: !1, discriminator: 2)
!935 = !DILocation(line: 453, column: 9, scope: !936)
!936 = !DILexicalBlockFile(scope: !930, file: !1, discriminator: 3)
!937 = !DILocation(line: 454, column: 9, scope: !930)
!938 = !DILocation(line: 454, column: 17, scope: !930)
!939 = !DILocation(line: 454, column: 27, scope: !930)
!940 = !DILocation(line: 454, column: 35, scope: !930)
!941 = !DILocation(line: 454, column: 43, scope: !930)
!942 = !DILocation(line: 455, column: 7, scope: !930)
!943 = !DILocation(line: 457, column: 7, scope: !914)
!944 = !DILocation(line: 457, column: 15, scope: !914)
!945 = !DILocation(line: 457, column: 33, scope: !914)
!946 = !DILocation(line: 459, column: 11, scope: !947)
!947 = distinct !DILexicalBlock(scope: !914, file: !1, line: 459, column: 11)
!948 = !DILocation(line: 459, column: 19, scope: !947)
!949 = !DILocation(line: 459, column: 25, scope: !947)
!950 = !DILocation(line: 459, column: 11, scope: !914)
!951 = !DILocation(line: 460, column: 25, scope: !947)
!952 = !DILocation(line: 460, column: 9, scope: !947)
!953 = !DILocation(line: 466, column: 12, scope: !954)
!954 = distinct !DILexicalBlock(scope: !914, file: !1, line: 466, column: 11)
!955 = !DILocation(line: 466, column: 20, scope: !954)
!956 = !DILocation(line: 466, column: 26, scope: !954)
!957 = !DILocation(line: 466, column: 40, scope: !954)
!958 = !DILocation(line: 467, column: 12, scope: !954)
!959 = !DILocation(line: 467, column: 20, scope: !954)
!960 = !DILocation(line: 467, column: 38, scope: !954)
!961 = !DILocation(line: 467, column: 46, scope: !954)
!962 = !DILocation(line: 467, column: 35, scope: !954)
!963 = !DILocation(line: 466, column: 11, scope: !964)
!964 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 1)
!965 = !DILocation(line: 468, column: 47, scope: !966)
!966 = distinct !DILexicalBlock(scope: !954, file: !1, line: 467, column: 67)
!967 = !DILocation(line: 468, column: 32, scope: !966)
!968 = !DILocation(line: 468, column: 9, scope: !966)
!969 = !DILocation(line: 469, column: 7, scope: !966)
!970 = !DILocation(line: 470, column: 5, scope: !914)
!971 = !DILocation(line: 448, column: 28, scope: !972)
!972 = !DILexicalBlockFile(scope: !909, file: !1, discriminator: 2)
!973 = !DILocation(line: 448, column: 5, scope: !972)
!974 = !DILocation(line: 472, column: 14, scope: !856)
!975 = !DILocation(line: 472, column: 11, scope: !856)
!976 = !DILocation(line: 477, column: 9, scope: !977)
!977 = distinct !DILexicalBlock(scope: !856, file: !1, line: 477, column: 9)
!978 = !DILocation(line: 477, column: 9, scope: !856)
!979 = !DILocation(line: 478, column: 7, scope: !980)
!980 = distinct !DILexicalBlock(scope: !977, file: !1, line: 477, column: 16)
!981 = !DILocation(line: 478, column: 20, scope: !980)
!982 = !DILocation(line: 478, column: 26, scope: !980)
!983 = !DILocation(line: 478, column: 24, scope: !980)
!984 = !DILocation(line: 478, column: 31, scope: !980)
!985 = !DILocation(line: 479, column: 7, scope: !980)
!986 = !DILocation(line: 481, column: 3, scope: !856)
!987 = !DILocation(line: 481, column: 12, scope: !988)
!988 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 1)
!989 = !DILocation(line: 481, column: 16, scope: !988)
!990 = !DILocation(line: 481, column: 3, scope: !988)
!991 = !DILocation(line: 482, column: 1, scope: !303)
!992 = !DILocalVariable(name: "saved_sigmask", arg: 1, scope: !309, file: !1, line: 128, type: !312)
!993 = !DILocation(line: 128, column: 49, scope: !309)
!994 = !DILocalVariable(name: "new_mask", scope: !309, file: !1, line: 129, type: !313)
!995 = !DILocation(line: 129, column: 12, scope: !309)
!996 = !DILocation(line: 131, column: 7, scope: !997)
!997 = distinct !DILexicalBlock(scope: !309, file: !1, line: 131, column: 7)
!998 = !DILocation(line: 131, column: 7, scope: !309)
!999 = !DILocation(line: 132, column: 5, scope: !997)
!1000 = !DILocation(line: 134, column: 47, scope: !1001)
!1001 = distinct !DILexicalBlock(scope: !309, file: !1, line: 134, column: 7)
!1002 = !DILocation(line: 134, column: 7, scope: !1001)
!1003 = !DILocation(line: 134, column: 7, scope: !309)
!1004 = !DILocation(line: 135, column: 5, scope: !1001)
!1005 = !DILocation(line: 137, column: 7, scope: !1006)
!1006 = distinct !DILexicalBlock(scope: !309, file: !1, line: 137, column: 7)
!1007 = !DILocation(line: 137, column: 7, scope: !309)
!1008 = !DILocation(line: 138, column: 5, scope: !1006)
!1009 = !DILocation(line: 139, column: 1, scope: !309)
!1010 = !DILocalVariable(name: "signum", arg: 1, scope: !324, file: !1, line: 151, type: !80)
!1011 = !DILocation(line: 151, column: 49, scope: !324)
!1012 = !DILocalVariable(name: "lookup", scope: !324, file: !1, line: 153, type: !217)
!1013 = !DILocation(line: 153, column: 15, scope: !324)
!1014 = !DILocalVariable(name: "handle", scope: !324, file: !1, line: 154, type: !237)
!1015 = !DILocation(line: 154, column: 16, scope: !324)
!1016 = !DILocation(line: 156, column: 19, scope: !324)
!1017 = !DILocation(line: 156, column: 10, scope: !324)
!1018 = !DILocation(line: 156, column: 17, scope: !324)
!1019 = !DILocation(line: 157, column: 10, scope: !324)
!1020 = !DILocation(line: 157, column: 16, scope: !324)
!1021 = !DILocation(line: 158, column: 10, scope: !324)
!1022 = !DILocation(line: 158, column: 15, scope: !324)
!1023 = !DILocation(line: 160, column: 12, scope: !324)
!1024 = !DILocation(line: 160, column: 10, scope: !324)
!1025 = !DILocation(line: 162, column: 7, scope: !1026)
!1026 = distinct !DILexicalBlock(scope: !324, file: !1, line: 162, column: 7)
!1027 = !DILocation(line: 162, column: 14, scope: !1026)
!1028 = !DILocation(line: 162, column: 22, scope: !1026)
!1029 = !DILocation(line: 162, column: 25, scope: !1030)
!1030 = !DILexicalBlockFile(scope: !1026, file: !1, discriminator: 1)
!1031 = !DILocation(line: 162, column: 33, scope: !1030)
!1032 = !DILocation(line: 162, column: 43, scope: !1030)
!1033 = !DILocation(line: 162, column: 40, scope: !1030)
!1034 = !DILocation(line: 162, column: 7, scope: !1030)
!1035 = !DILocation(line: 163, column: 12, scope: !1026)
!1036 = !DILocation(line: 163, column: 5, scope: !1026)
!1037 = !DILocation(line: 165, column: 3, scope: !324)
!1038 = !DILocation(line: 166, column: 1, scope: !324)
!1039 = !DILocalVariable(name: "signum", arg: 1, scope: !337, file: !1, line: 210, type: !80)
!1040 = !DILocation(line: 210, column: 44, scope: !337)
!1041 = !DILocalVariable(name: "oneshot", arg: 2, scope: !337, file: !1, line: 210, type: !80)
!1042 = !DILocation(line: 210, column: 56, scope: !337)
!1043 = !DILocalVariable(name: "sa", scope: !337, file: !1, line: 212, type: !1044)
!1044 = !DICompositeType(tag: DW_TAG_structure_type, name: "sigaction", file: !1045, line: 24, size: 1216, align: 64, elements: !1046)
!1045 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sigaction.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1046 = !{!1047, !1121, !1122, !1123}
!1047 = !DIDerivedType(tag: DW_TAG_member, name: "__sigaction_handler", scope: !1044, file: !1045, line: 35, baseType: !1048, size: 64, align: 64)
!1048 = !DICompositeType(tag: DW_TAG_union_type, scope: !1044, file: !1045, line: 28, size: 64, align: 64, elements: !1049)
!1049 = !{!1050, !1051}
!1050 = !DIDerivedType(tag: DW_TAG_member, name: "sa_handler", scope: !1048, file: !1045, line: 31, baseType: !270, size: 64, align: 64)
!1051 = !DIDerivedType(tag: DW_TAG_member, name: "sa_sigaction", scope: !1048, file: !1045, line: 33, baseType: !1052, size: 64, align: 64)
!1052 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1053, size: 64, align: 64)
!1053 = !DISubroutineType(types: !1054)
!1054 = !{null, !80, !1055, !58}
!1055 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1056, size: 64, align: 64)
!1056 = !DIDerivedType(tag: DW_TAG_typedef, name: "siginfo_t", file: !1057, line: 128, baseType: !1058)
!1057 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/siginfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1058 = !DICompositeType(tag: DW_TAG_structure_type, file: !1057, line: 62, size: 1024, align: 64, elements: !1059)
!1059 = !{!1060, !1061, !1062, !1063}
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "si_signo", scope: !1058, file: !1057, line: 64, baseType: !80, size: 32, align: 32)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "si_errno", scope: !1058, file: !1057, line: 65, baseType: !80, size: 32, align: 32, offset: 32)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "si_code", scope: !1058, file: !1057, line: 67, baseType: !80, size: 32, align: 32, offset: 64)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "_sifields", scope: !1058, file: !1057, line: 127, baseType: !1064, size: 896, align: 64, offset: 128)
!1064 = !DICompositeType(tag: DW_TAG_union_type, scope: !1058, file: !1057, line: 69, size: 896, align: 64, elements: !1065)
!1065 = !{!1066, !1070, !1078, !1089, !1095, !1105, !1110, !1115}
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "_pad", scope: !1064, file: !1057, line: 71, baseType: !1067, size: 896, align: 32)
!1067 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 896, align: 32, elements: !1068)
!1068 = !{!1069}
!1069 = !DISubrange(count: 28)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "_kill", scope: !1064, file: !1057, line: 78, baseType: !1071, size: 64, align: 32)
!1071 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 74, size: 64, align: 32, elements: !1072)
!1072 = !{!1073, !1076}
!1073 = !DIDerivedType(tag: DW_TAG_member, name: "si_pid", scope: !1071, file: !1057, line: 76, baseType: !1074, size: 32, align: 32)
!1074 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !1075, line: 133, baseType: !80)
!1075 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1076 = !DIDerivedType(tag: DW_TAG_member, name: "si_uid", scope: !1071, file: !1057, line: 77, baseType: !1077, size: 32, align: 32, offset: 32)
!1077 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !1075, line: 125, baseType: !73)
!1078 = !DIDerivedType(tag: DW_TAG_member, name: "_timer", scope: !1064, file: !1057, line: 86, baseType: !1079, size: 128, align: 64)
!1079 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 81, size: 128, align: 64, elements: !1080)
!1080 = !{!1081, !1082, !1083}
!1081 = !DIDerivedType(tag: DW_TAG_member, name: "si_tid", scope: !1079, file: !1057, line: 83, baseType: !80, size: 32, align: 32)
!1082 = !DIDerivedType(tag: DW_TAG_member, name: "si_overrun", scope: !1079, file: !1057, line: 84, baseType: !80, size: 32, align: 32, offset: 32)
!1083 = !DIDerivedType(tag: DW_TAG_member, name: "si_sigval", scope: !1079, file: !1057, line: 85, baseType: !1084, size: 64, align: 64, offset: 64)
!1084 = !DIDerivedType(tag: DW_TAG_typedef, name: "sigval_t", file: !1057, line: 36, baseType: !1085)
!1085 = !DICompositeType(tag: DW_TAG_union_type, name: "sigval", file: !1057, line: 32, size: 64, align: 64, elements: !1086)
!1086 = !{!1087, !1088}
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "sival_int", scope: !1085, file: !1057, line: 34, baseType: !80, size: 32, align: 32)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "sival_ptr", scope: !1085, file: !1057, line: 35, baseType: !58, size: 64, align: 64)
!1089 = !DIDerivedType(tag: DW_TAG_member, name: "_rt", scope: !1064, file: !1057, line: 94, baseType: !1090, size: 128, align: 64)
!1090 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 89, size: 128, align: 64, elements: !1091)
!1091 = !{!1092, !1093, !1094}
!1092 = !DIDerivedType(tag: DW_TAG_member, name: "si_pid", scope: !1090, file: !1057, line: 91, baseType: !1074, size: 32, align: 32)
!1093 = !DIDerivedType(tag: DW_TAG_member, name: "si_uid", scope: !1090, file: !1057, line: 92, baseType: !1077, size: 32, align: 32, offset: 32)
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "si_sigval", scope: !1090, file: !1057, line: 93, baseType: !1084, size: 64, align: 64, offset: 64)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "_sigchld", scope: !1064, file: !1057, line: 104, baseType: !1096, size: 256, align: 64)
!1096 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 97, size: 256, align: 64, elements: !1097)
!1097 = !{!1098, !1099, !1100, !1101, !1104}
!1098 = !DIDerivedType(tag: DW_TAG_member, name: "si_pid", scope: !1096, file: !1057, line: 99, baseType: !1074, size: 32, align: 32)
!1099 = !DIDerivedType(tag: DW_TAG_member, name: "si_uid", scope: !1096, file: !1057, line: 100, baseType: !1077, size: 32, align: 32, offset: 32)
!1100 = !DIDerivedType(tag: DW_TAG_member, name: "si_status", scope: !1096, file: !1057, line: 101, baseType: !80, size: 32, align: 32, offset: 64)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "si_utime", scope: !1096, file: !1057, line: 102, baseType: !1102, size: 64, align: 64, offset: 128)
!1102 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sigchld_clock_t", file: !1057, line: 58, baseType: !1103)
!1103 = !DIDerivedType(tag: DW_TAG_typedef, name: "__clock_t", file: !1075, line: 135, baseType: !135)
!1104 = !DIDerivedType(tag: DW_TAG_member, name: "si_stime", scope: !1096, file: !1057, line: 103, baseType: !1102, size: 64, align: 64, offset: 192)
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "_sigfault", scope: !1064, file: !1057, line: 111, baseType: !1106, size: 128, align: 64)
!1106 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 107, size: 128, align: 64, elements: !1107)
!1107 = !{!1108, !1109}
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "si_addr", scope: !1106, file: !1057, line: 109, baseType: !58, size: 64, align: 64)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "si_addr_lsb", scope: !1106, file: !1057, line: 110, baseType: !120, size: 16, align: 16, offset: 64)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "_sigpoll", scope: !1064, file: !1057, line: 118, baseType: !1111, size: 128, align: 64)
!1111 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 114, size: 128, align: 64, elements: !1112)
!1112 = !{!1113, !1114}
!1113 = !DIDerivedType(tag: DW_TAG_member, name: "si_band", scope: !1111, file: !1057, line: 116, baseType: !135, size: 64, align: 64)
!1114 = !DIDerivedType(tag: DW_TAG_member, name: "si_fd", scope: !1111, file: !1057, line: 117, baseType: !80, size: 32, align: 32, offset: 64)
!1115 = !DIDerivedType(tag: DW_TAG_member, name: "_sigsys", scope: !1064, file: !1057, line: 126, baseType: !1116, size: 128, align: 64)
!1116 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1064, file: !1057, line: 121, size: 128, align: 64, elements: !1117)
!1117 = !{!1118, !1119, !1120}
!1118 = !DIDerivedType(tag: DW_TAG_member, name: "_call_addr", scope: !1116, file: !1057, line: 123, baseType: !58, size: 64, align: 64)
!1119 = !DIDerivedType(tag: DW_TAG_member, name: "_syscall", scope: !1116, file: !1057, line: 124, baseType: !80, size: 32, align: 32, offset: 64)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "_arch", scope: !1116, file: !1057, line: 125, baseType: !73, size: 32, align: 32, offset: 96)
!1121 = !DIDerivedType(tag: DW_TAG_member, name: "sa_mask", scope: !1044, file: !1045, line: 43, baseType: !315, size: 1024, align: 64, offset: 64)
!1122 = !DIDerivedType(tag: DW_TAG_member, name: "sa_flags", scope: !1044, file: !1045, line: 46, baseType: !80, size: 32, align: 32, offset: 1088)
!1123 = !DIDerivedType(tag: DW_TAG_member, name: "sa_restorer", scope: !1044, file: !1045, line: 49, baseType: !199, size: 64, align: 64, offset: 1152)
!1124 = !DILocation(line: 212, column: 20, scope: !337)
!1125 = !DILocation(line: 215, column: 3, scope: !337)
!1126 = !DILocation(line: 216, column: 22, scope: !1127)
!1127 = distinct !DILexicalBlock(scope: !337, file: !1, line: 216, column: 7)
!1128 = !DILocation(line: 216, column: 7, scope: !1127)
!1129 = !DILocation(line: 216, column: 7, scope: !337)
!1130 = !DILocation(line: 217, column: 5, scope: !1127)
!1131 = !DILocation(line: 218, column: 6, scope: !337)
!1132 = !DILocation(line: 218, column: 17, scope: !337)
!1133 = !DILocation(line: 219, column: 17, scope: !337)
!1134 = !DILocation(line: 219, column: 6, scope: !337)
!1135 = !DILocation(line: 219, column: 15, scope: !337)
!1136 = !DILocation(line: 222, column: 17, scope: !1137)
!1137 = distinct !DILexicalBlock(scope: !337, file: !1, line: 222, column: 7)
!1138 = !DILocation(line: 222, column: 7, scope: !1137)
!1139 = !DILocation(line: 222, column: 7, scope: !337)
!1140 = !DILocation(line: 223, column: 13, scope: !1137)
!1141 = !DILocation(line: 223, column: 12, scope: !1137)
!1142 = !DILocation(line: 223, column: 5, scope: !1137)
!1143 = !DILocation(line: 225, column: 3, scope: !337)
!1144 = !DILocation(line: 226, column: 1, scope: !337)
!1145 = !DILocalVariable(name: "saved_sigmask", arg: 1, scope: !344, file: !1, line: 142, type: !312)
!1146 = !DILocation(line: 142, column: 53, scope: !344)
!1147 = !DILocation(line: 143, column: 7, scope: !1148)
!1148 = distinct !DILexicalBlock(scope: !344, file: !1, line: 143, column: 7)
!1149 = !DILocation(line: 143, column: 7, scope: !344)
!1150 = !DILocation(line: 144, column: 5, scope: !1148)
!1151 = !DILocation(line: 146, column: 36, scope: !1152)
!1152 = distinct !DILexicalBlock(scope: !344, file: !1, line: 146, column: 7)
!1153 = !DILocation(line: 146, column: 7, scope: !1152)
!1154 = !DILocation(line: 146, column: 7, scope: !344)
!1155 = !DILocation(line: 147, column: 5, scope: !1152)
!1156 = !DILocation(line: 148, column: 1, scope: !344)
!1157 = !DILocalVariable(name: "head", arg: 1, scope: !345, file: !1, line: 57, type: !330)
!1158 = !DILocation(line: 57, column: 1, scope: !345)
!1159 = !DILocalVariable(name: "elm", arg: 2, scope: !345, file: !1, line: 57, type: !243)
!1160 = !DILocalVariable(name: "tmp", scope: !345, file: !1, line: 57, type: !243)
!1161 = !DILocalVariable(name: "parent", scope: !345, file: !1, line: 57, type: !243)
!1162 = !DILocalVariable(name: "comp", scope: !345, file: !1, line: 57, type: !80)
!1163 = !DILocation(line: 57, column: 1, scope: !1164)
!1164 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 1)
!1165 = !DILocation(line: 57, column: 1, scope: !1166)
!1166 = !DILexicalBlockFile(scope: !1167, file: !1, discriminator: 2)
!1167 = distinct !DILexicalBlock(scope: !345, file: !1, line: 57, column: 1)
!1168 = !DILocation(line: 57, column: 1, scope: !1169)
!1169 = !DILexicalBlockFile(scope: !1170, file: !1, discriminator: 3)
!1170 = distinct !DILexicalBlock(scope: !1167, file: !1, line: 57, column: 1)
!1171 = !DILocation(line: 57, column: 1, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 4)
!1173 = distinct !DILexicalBlock(scope: !1170, file: !1, line: 57, column: 1)
!1174 = !DILocation(line: 57, column: 1, scope: !1175)
!1175 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 5)
!1176 = !DILocation(line: 57, column: 1, scope: !1177)
!1177 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 6)
!1178 = !DILocation(line: 57, column: 1, scope: !1179)
!1179 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 7)
!1180 = !DILocation(line: 57, column: 1, scope: !1181)
!1181 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 8)
!1182 = !DILocation(line: 57, column: 1, scope: !1183)
!1183 = !DILexicalBlockFile(scope: !1184, file: !1, discriminator: 9)
!1184 = distinct !DILexicalBlock(scope: !345, file: !1, line: 57, column: 1)
!1185 = !DILocation(line: 57, column: 1, scope: !1186)
!1186 = !DILexicalBlockFile(scope: !1187, file: !1, discriminator: 10)
!1187 = distinct !DILexicalBlock(scope: !345, file: !1, line: 57, column: 1)
!1188 = !DILocation(line: 57, column: 1, scope: !1189)
!1189 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 11)
!1190 = distinct !DILexicalBlock(scope: !1191, file: !1, line: 57, column: 1)
!1191 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 57, column: 1)
!1192 = !DILocation(line: 57, column: 1, scope: !1193)
!1193 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 12)
!1194 = !DILocation(line: 57, column: 1, scope: !1195)
!1195 = !DILexicalBlockFile(scope: !1190, file: !1, discriminator: 13)
!1196 = !DILocation(line: 57, column: 1, scope: !1197)
!1197 = !DILexicalBlockFile(scope: !1191, file: !1, discriminator: 14)
!1198 = !DILocation(line: 57, column: 1, scope: !1199)
!1199 = !DILexicalBlockFile(scope: !1200, file: !1, discriminator: 15)
!1200 = distinct !DILexicalBlock(scope: !1191, file: !1, line: 57, column: 1)
!1201 = !DILocation(line: 57, column: 1, scope: !1202)
!1202 = !DILexicalBlockFile(scope: !1191, file: !1, discriminator: 16)
!1203 = !DILocation(line: 57, column: 1, scope: !1204)
!1204 = !DILexicalBlockFile(scope: !1187, file: !1, discriminator: 17)
!1205 = !DILocation(line: 57, column: 1, scope: !1206)
!1206 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 18)
!1207 = !DILocation(line: 57, column: 1, scope: !1208)
!1208 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 19)
!1209 = !DILocalVariable(name: "r", scope: !323, file: !1, line: 105, type: !80)
!1210 = !DILocation(line: 105, column: 7, scope: !323)
!1211 = !DILocalVariable(name: "data", scope: !323, file: !1, line: 106, type: !131)
!1212 = !DILocation(line: 106, column: 8, scope: !323)
!1213 = !DILocation(line: 108, column: 3, scope: !323)
!1214 = !DILocation(line: 109, column: 14, scope: !1215)
!1215 = distinct !DILexicalBlock(scope: !323, file: !1, line: 108, column: 6)
!1216 = !DILocation(line: 109, column: 9, scope: !1215)
!1217 = !DILocation(line: 109, column: 7, scope: !1215)
!1218 = !DILocation(line: 110, column: 3, scope: !1215)
!1219 = !DILocation(line: 110, column: 12, scope: !1220)
!1220 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 1)
!1221 = !DILocation(line: 110, column: 14, scope: !1220)
!1222 = !DILocation(line: 110, column: 18, scope: !1220)
!1223 = !DILocation(line: 110, column: 21, scope: !1224)
!1224 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 2)
!1225 = !DILocation(line: 110, column: 27, scope: !1224)
!1226 = !DILocation(line: 110, column: 3, scope: !1227)
!1227 = !DILexicalBlockFile(scope: !1215, file: !1, discriminator: 3)
!1228 = !DILocation(line: 112, column: 11, scope: !323)
!1229 = !DILocation(line: 112, column: 13, scope: !323)
!1230 = !DILocation(line: 112, column: 10, scope: !323)
!1231 = !DILocation(line: 112, column: 3, scope: !323)
!1232 = !DILocalVariable(name: "head", arg: 1, scope: !327, file: !1, line: 57, type: !330)
!1233 = !DILocation(line: 57, column: 1, scope: !327)
!1234 = !DILocalVariable(name: "elm", arg: 2, scope: !327, file: !1, line: 57, type: !243)
!1235 = !DILocalVariable(name: "tmp", scope: !327, file: !1, line: 57, type: !243)
!1236 = !DILocalVariable(name: "res", scope: !327, file: !1, line: 57, type: !243)
!1237 = !DILocalVariable(name: "comp", scope: !327, file: !1, line: 57, type: !80)
!1238 = !DILocation(line: 57, column: 1, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !327, file: !1, discriminator: 20)
!1240 = !DILocation(line: 57, column: 1, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1242, file: !1, discriminator: 21)
!1242 = distinct !DILexicalBlock(scope: !327, file: !1, line: 57, column: 1)
!1243 = !DILocation(line: 57, column: 1, scope: !1244)
!1244 = !DILexicalBlockFile(scope: !1245, file: !1, discriminator: 22)
!1245 = distinct !DILexicalBlock(scope: !1246, file: !1, line: 57, column: 1)
!1246 = distinct !DILexicalBlock(scope: !1242, file: !1, line: 57, column: 1)
!1247 = !DILocation(line: 57, column: 1, scope: !1248)
!1248 = !DILexicalBlockFile(scope: !1249, file: !1, discriminator: 23)
!1249 = distinct !DILexicalBlock(scope: !1246, file: !1, line: 57, column: 1)
!1250 = !DILocation(line: 57, column: 1, scope: !1251)
!1251 = !DILexicalBlockFile(scope: !1249, file: !1, discriminator: 24)
!1252 = !DILocation(line: 57, column: 1, scope: !1253)
!1253 = !DILexicalBlockFile(scope: !1249, file: !1, discriminator: 25)
!1254 = !DILocation(line: 57, column: 1, scope: !1255)
!1255 = !DILexicalBlockFile(scope: !327, file: !1, discriminator: 26)
!1256 = !DILocation(line: 57, column: 1, scope: !1257)
!1257 = !DILexicalBlockFile(scope: !327, file: !1, discriminator: 27)
!1258 = !DILocation(line: 57, column: 1, scope: !1259)
!1259 = !DILexicalBlockFile(scope: !327, file: !1, discriminator: 28)
!1260 = !DILocalVariable(name: "w1", arg: 1, scope: !334, file: !1, line: 485, type: !237)
!1261 = !DILocation(line: 485, column: 44, scope: !334)
!1262 = !DILocalVariable(name: "w2", arg: 2, scope: !334, file: !1, line: 485, type: !237)
!1263 = !DILocation(line: 485, column: 61, scope: !334)
!1264 = !DILocalVariable(name: "f1", scope: !334, file: !1, line: 486, type: !80)
!1265 = !DILocation(line: 486, column: 7, scope: !334)
!1266 = !DILocalVariable(name: "f2", scope: !334, file: !1, line: 487, type: !80)
!1267 = !DILocation(line: 487, column: 7, scope: !334)
!1268 = !DILocation(line: 491, column: 7, scope: !1269)
!1269 = distinct !DILexicalBlock(scope: !334, file: !1, line: 491, column: 7)
!1270 = !DILocation(line: 491, column: 11, scope: !1269)
!1271 = !DILocation(line: 491, column: 20, scope: !1269)
!1272 = !DILocation(line: 491, column: 24, scope: !1269)
!1273 = !DILocation(line: 491, column: 18, scope: !1269)
!1274 = !DILocation(line: 491, column: 7, scope: !334)
!1275 = !DILocation(line: 491, column: 32, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !1269, file: !1, discriminator: 1)
!1277 = !DILocation(line: 492, column: 7, scope: !1278)
!1278 = distinct !DILexicalBlock(scope: !334, file: !1, line: 492, column: 7)
!1279 = !DILocation(line: 492, column: 11, scope: !1278)
!1280 = !DILocation(line: 492, column: 20, scope: !1278)
!1281 = !DILocation(line: 492, column: 24, scope: !1278)
!1282 = !DILocation(line: 492, column: 18, scope: !1278)
!1283 = !DILocation(line: 492, column: 7, scope: !334)
!1284 = !DILocation(line: 492, column: 32, scope: !1285)
!1285 = !DILexicalBlockFile(scope: !1278, file: !1, discriminator: 1)
!1286 = !DILocation(line: 497, column: 8, scope: !334)
!1287 = !DILocation(line: 497, column: 12, scope: !334)
!1288 = !DILocation(line: 497, column: 18, scope: !334)
!1289 = !DILocation(line: 497, column: 6, scope: !334)
!1290 = !DILocation(line: 498, column: 8, scope: !334)
!1291 = !DILocation(line: 498, column: 12, scope: !334)
!1292 = !DILocation(line: 498, column: 18, scope: !334)
!1293 = !DILocation(line: 498, column: 6, scope: !334)
!1294 = !DILocation(line: 499, column: 7, scope: !1295)
!1295 = distinct !DILexicalBlock(scope: !334, file: !1, line: 499, column: 7)
!1296 = !DILocation(line: 499, column: 12, scope: !1295)
!1297 = !DILocation(line: 499, column: 10, scope: !1295)
!1298 = !DILocation(line: 499, column: 7, scope: !334)
!1299 = !DILocation(line: 499, column: 16, scope: !1300)
!1300 = !DILexicalBlockFile(scope: !1295, file: !1, discriminator: 1)
!1301 = !DILocation(line: 500, column: 7, scope: !1302)
!1302 = distinct !DILexicalBlock(scope: !334, file: !1, line: 500, column: 7)
!1303 = !DILocation(line: 500, column: 12, scope: !1302)
!1304 = !DILocation(line: 500, column: 10, scope: !1302)
!1305 = !DILocation(line: 500, column: 7, scope: !334)
!1306 = !DILocation(line: 500, column: 16, scope: !1307)
!1307 = !DILexicalBlockFile(scope: !1302, file: !1, discriminator: 1)
!1308 = !DILocation(line: 505, column: 7, scope: !1309)
!1309 = distinct !DILexicalBlock(scope: !334, file: !1, line: 505, column: 7)
!1310 = !DILocation(line: 505, column: 11, scope: !1309)
!1311 = !DILocation(line: 505, column: 18, scope: !1309)
!1312 = !DILocation(line: 505, column: 22, scope: !1309)
!1313 = !DILocation(line: 505, column: 16, scope: !1309)
!1314 = !DILocation(line: 505, column: 7, scope: !334)
!1315 = !DILocation(line: 505, column: 28, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !1309, file: !1, discriminator: 1)
!1317 = !DILocation(line: 506, column: 7, scope: !1318)
!1318 = distinct !DILexicalBlock(scope: !334, file: !1, line: 506, column: 7)
!1319 = !DILocation(line: 506, column: 11, scope: !1318)
!1320 = !DILocation(line: 506, column: 18, scope: !1318)
!1321 = !DILocation(line: 506, column: 22, scope: !1318)
!1322 = !DILocation(line: 506, column: 16, scope: !1318)
!1323 = !DILocation(line: 506, column: 7, scope: !334)
!1324 = !DILocation(line: 506, column: 28, scope: !1325)
!1325 = !DILexicalBlockFile(scope: !1318, file: !1, discriminator: 1)
!1326 = !DILocation(line: 508, column: 7, scope: !1327)
!1327 = distinct !DILexicalBlock(scope: !334, file: !1, line: 508, column: 7)
!1328 = !DILocation(line: 508, column: 12, scope: !1327)
!1329 = !DILocation(line: 508, column: 10, scope: !1327)
!1330 = !DILocation(line: 508, column: 7, scope: !334)
!1331 = !DILocation(line: 508, column: 16, scope: !1332)
!1332 = !DILexicalBlockFile(scope: !1327, file: !1, discriminator: 1)
!1333 = !DILocation(line: 509, column: 7, scope: !1334)
!1334 = distinct !DILexicalBlock(scope: !334, file: !1, line: 509, column: 7)
!1335 = !DILocation(line: 509, column: 12, scope: !1334)
!1336 = !DILocation(line: 509, column: 10, scope: !1334)
!1337 = !DILocation(line: 509, column: 7, scope: !334)
!1338 = !DILocation(line: 509, column: 16, scope: !1339)
!1339 = !DILexicalBlockFile(scope: !1334, file: !1, discriminator: 1)
!1340 = !DILocation(line: 511, column: 3, scope: !334)
!1341 = !DILocation(line: 512, column: 1, scope: !334)
!1342 = !DILocalVariable(name: "signum", arg: 1, scope: !340, file: !1, line: 169, type: !80)
!1343 = !DILocation(line: 169, column: 36, scope: !340)
!1344 = !DILocalVariable(name: "msg", scope: !340, file: !1, line: 170, type: !265)
!1345 = !DILocation(line: 170, column: 20, scope: !340)
!1346 = !DILocalVariable(name: "handle", scope: !340, file: !1, line: 171, type: !237)
!1347 = !DILocation(line: 171, column: 16, scope: !340)
!1348 = !DILocalVariable(name: "saved_errno", scope: !340, file: !1, line: 172, type: !80)
!1349 = !DILocation(line: 172, column: 7, scope: !340)
!1350 = !DILocation(line: 174, column: 17, scope: !340)
!1351 = !DILocation(line: 174, column: 15, scope: !340)
!1352 = !DILocation(line: 175, column: 3, scope: !340)
!1353 = !DILocation(line: 177, column: 7, scope: !1354)
!1354 = distinct !DILexicalBlock(scope: !340, file: !1, line: 177, column: 7)
!1355 = !DILocation(line: 177, column: 7, scope: !340)
!1356 = !DILocation(line: 178, column: 13, scope: !1357)
!1357 = distinct !DILexicalBlock(scope: !1354, file: !1, line: 177, column: 26)
!1358 = !DILocation(line: 178, column: 5, scope: !1357)
!1359 = !DILocation(line: 178, column: 11, scope: !1357)
!1360 = !DILocation(line: 179, column: 5, scope: !1357)
!1361 = !DILocation(line: 182, column: 41, scope: !1362)
!1362 = distinct !DILexicalBlock(scope: !340, file: !1, line: 182, column: 3)
!1363 = !DILocation(line: 182, column: 17, scope: !1362)
!1364 = !DILocation(line: 182, column: 15, scope: !1362)
!1365 = !DILocation(line: 182, column: 8, scope: !1362)
!1366 = !DILocation(line: 183, column: 8, scope: !1367)
!1367 = distinct !DILexicalBlock(scope: !1362, file: !1, line: 182, column: 3)
!1368 = !DILocation(line: 183, column: 15, scope: !1367)
!1369 = !DILocation(line: 183, column: 23, scope: !1367)
!1370 = !DILocation(line: 183, column: 26, scope: !1371)
!1371 = !DILexicalBlockFile(scope: !1367, file: !1, discriminator: 1)
!1372 = !DILocation(line: 183, column: 34, scope: !1371)
!1373 = !DILocation(line: 183, column: 44, scope: !1371)
!1374 = !DILocation(line: 183, column: 41, scope: !1371)
!1375 = !DILocation(line: 182, column: 3, scope: !1376)
!1376 = !DILexicalBlockFile(scope: !1362, file: !1, discriminator: 1)
!1377 = !DILocalVariable(name: "r", scope: !1378, file: !1, line: 185, type: !80)
!1378 = distinct !DILexicalBlock(scope: !1367, file: !1, line: 184, column: 71)
!1379 = !DILocation(line: 185, column: 9, scope: !1378)
!1380 = !DILocation(line: 187, column: 18, scope: !1378)
!1381 = !DILocation(line: 187, column: 9, scope: !1378)
!1382 = !DILocation(line: 187, column: 16, scope: !1378)
!1383 = !DILocation(line: 188, column: 18, scope: !1378)
!1384 = !DILocation(line: 188, column: 9, scope: !1378)
!1385 = !DILocation(line: 188, column: 16, scope: !1378)
!1386 = !DILocation(line: 194, column: 5, scope: !1378)
!1387 = !DILocation(line: 195, column: 17, scope: !1388)
!1388 = distinct !DILexicalBlock(scope: !1378, file: !1, line: 194, column: 8)
!1389 = !DILocation(line: 195, column: 25, scope: !1388)
!1390 = !DILocation(line: 195, column: 31, scope: !1388)
!1391 = !DILocation(line: 195, column: 49, scope: !1388)
!1392 = !DILocation(line: 195, column: 11, scope: !1388)
!1393 = !DILocation(line: 195, column: 9, scope: !1388)
!1394 = !DILocation(line: 196, column: 5, scope: !1388)
!1395 = !DILocation(line: 196, column: 14, scope: !1396)
!1396 = !DILexicalBlockFile(scope: !1378, file: !1, discriminator: 1)
!1397 = !DILocation(line: 196, column: 16, scope: !1396)
!1398 = !DILocation(line: 196, column: 22, scope: !1396)
!1399 = !DILocation(line: 196, column: 25, scope: !1400)
!1400 = !DILexicalBlockFile(scope: !1378, file: !1, discriminator: 2)
!1401 = !DILocation(line: 196, column: 31, scope: !1400)
!1402 = !DILocation(line: 196, column: 5, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1388, file: !1, discriminator: 3)
!1404 = !DILocation(line: 198, column: 5, scope: !1378)
!1405 = !DILocation(line: 198, column: 5, scope: !1396)
!1406 = !DILocation(line: 198, column: 5, scope: !1400)
!1407 = !DILocation(line: 198, column: 5, scope: !1408)
!1408 = !DILexicalBlockFile(scope: !1378, file: !1, discriminator: 3)
!1409 = !DILocation(line: 198, column: 5, scope: !1410)
!1410 = !DILexicalBlockFile(scope: !1378, file: !1, discriminator: 4)
!1411 = !DILocation(line: 198, column: 5, scope: !1412)
!1412 = !DILexicalBlockFile(scope: !1378, file: !1, discriminator: 5)
!1413 = !DILocation(line: 198, column: 5, scope: !1414)
!1414 = !DILexicalBlockFile(scope: !1378, file: !1, discriminator: 6)
!1415 = !DILocation(line: 201, column: 9, scope: !1416)
!1416 = distinct !DILexicalBlock(scope: !1378, file: !1, line: 201, column: 9)
!1417 = !DILocation(line: 201, column: 11, scope: !1416)
!1418 = !DILocation(line: 201, column: 9, scope: !1378)
!1419 = !DILocation(line: 202, column: 7, scope: !1416)
!1420 = !DILocation(line: 202, column: 15, scope: !1416)
!1421 = !DILocation(line: 202, column: 29, scope: !1416)
!1422 = !DILocation(line: 203, column: 3, scope: !1378)
!1423 = !DILocation(line: 184, column: 17, scope: !1367)
!1424 = !DILocation(line: 184, column: 15, scope: !1367)
!1425 = !DILocation(line: 182, column: 3, scope: !1426)
!1426 = !DILexicalBlockFile(scope: !1367, file: !1, discriminator: 2)
!1427 = !DILocation(line: 205, column: 3, scope: !340)
!1428 = !DILocation(line: 206, column: 11, scope: !340)
!1429 = !DILocation(line: 206, column: 3, scope: !340)
!1430 = !DILocation(line: 206, column: 9, scope: !340)
!1431 = !DILocation(line: 207, column: 1, scope: !340)
!1432 = !DILocation(line: 207, column: 1, scope: !1433)
!1433 = !DILexicalBlockFile(scope: !340, file: !1, discriminator: 1)
!1434 = !DILocalVariable(name: "elm", arg: 1, scope: !341, file: !1, line: 57, type: !243)
!1435 = !DILocation(line: 57, column: 1, scope: !341)
!1436 = !DILocation(line: 57, column: 1, scope: !1437)
!1437 = distinct !DILexicalBlock(scope: !341, file: !1, line: 57, column: 1)
!1438 = !DILocation(line: 57, column: 1, scope: !1439)
!1439 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 29)
!1440 = distinct !DILexicalBlock(scope: !1437, file: !1, line: 57, column: 1)
!1441 = !DILocation(line: 57, column: 1, scope: !1442)
!1442 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 30)
!1443 = !DILocation(line: 57, column: 1, scope: !1444)
!1444 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 31)
!1445 = !DILocation(line: 57, column: 1, scope: !1446)
!1446 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 32)
!1447 = !DILocation(line: 57, column: 1, scope: !1448)
!1448 = !DILexicalBlockFile(scope: !1449, file: !1, discriminator: 33)
!1449 = distinct !DILexicalBlock(scope: !1450, file: !1, line: 57, column: 1)
!1450 = distinct !DILexicalBlock(scope: !1437, file: !1, line: 57, column: 1)
!1451 = !DILocation(line: 57, column: 1, scope: !1452)
!1452 = !DILexicalBlockFile(scope: !1449, file: !1, discriminator: 34)
!1453 = !DILocation(line: 57, column: 1, scope: !1454)
!1454 = !DILexicalBlockFile(scope: !1449, file: !1, discriminator: 35)
!1455 = !DILocation(line: 57, column: 1, scope: !1456)
!1456 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 36)
!1457 = distinct !DILexicalBlock(scope: !1449, file: !1, line: 57, column: 1)
!1458 = !DILocation(line: 57, column: 1, scope: !1459)
!1459 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 37)
!1460 = !DILocation(line: 57, column: 1, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 38)
!1462 = !DILocation(line: 57, column: 1, scope: !1463)
!1463 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 39)
!1464 = !DILocation(line: 57, column: 1, scope: !1465)
!1465 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 40)
!1466 = !DILocation(line: 57, column: 1, scope: !1467)
!1467 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 41)
!1468 = !DILocation(line: 57, column: 1, scope: !1469)
!1469 = !DILexicalBlockFile(scope: !341, file: !1, discriminator: 42)
!1470 = !DILocalVariable(name: "head", arg: 1, scope: !346, file: !1, line: 57, type: !330)
!1471 = !DILocation(line: 57, column: 1, scope: !346)
!1472 = !DILocalVariable(name: "elm", arg: 2, scope: !346, file: !1, line: 57, type: !243)
!1473 = !DILocalVariable(name: "parent", scope: !346, file: !1, line: 57, type: !243)
!1474 = !DILocalVariable(name: "gparent", scope: !346, file: !1, line: 57, type: !243)
!1475 = !DILocalVariable(name: "tmp", scope: !346, file: !1, line: 57, type: !243)
!1476 = !DILocation(line: 57, column: 1, scope: !1477)
!1477 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 43)
!1478 = !DILocation(line: 57, column: 1, scope: !1479)
!1479 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 44)
!1480 = !DILocation(line: 57, column: 1, scope: !1481)
!1481 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 45)
!1482 = !DILocation(line: 57, column: 1, scope: !1483)
!1483 = !DILexicalBlockFile(scope: !1484, file: !1, discriminator: 46)
!1484 = distinct !DILexicalBlock(scope: !346, file: !1, line: 57, column: 1)
!1485 = !DILocation(line: 57, column: 1, scope: !1486)
!1486 = !DILexicalBlockFile(scope: !1487, file: !1, discriminator: 47)
!1487 = distinct !DILexicalBlock(scope: !1488, file: !1, line: 57, column: 1)
!1488 = distinct !DILexicalBlock(scope: !1484, file: !1, line: 57, column: 1)
!1489 = !DILocation(line: 57, column: 1, scope: !1490)
!1490 = !DILexicalBlockFile(scope: !1491, file: !1, discriminator: 48)
!1491 = distinct !DILexicalBlock(scope: !1487, file: !1, line: 57, column: 1)
!1492 = !DILocation(line: 57, column: 1, scope: !1493)
!1493 = !DILexicalBlockFile(scope: !1494, file: !1, discriminator: 49)
!1494 = distinct !DILexicalBlock(scope: !1491, file: !1, line: 57, column: 1)
!1495 = !DILocation(line: 57, column: 1, scope: !1496)
!1496 = !DILexicalBlockFile(scope: !1497, file: !1, discriminator: 50)
!1497 = distinct !DILexicalBlock(scope: !1494, file: !1, line: 57, column: 1)
!1498 = !DILocation(line: 57, column: 1, scope: !1499)
!1499 = !DILexicalBlockFile(scope: !1494, file: !1, discriminator: 51)
!1500 = !DILocation(line: 57, column: 1, scope: !1501)
!1501 = !DILexicalBlockFile(scope: !1502, file: !1, discriminator: 52)
!1502 = distinct !DILexicalBlock(scope: !1487, file: !1, line: 57, column: 1)
!1503 = !DILocation(line: 57, column: 1, scope: !1504)
!1504 = !DILexicalBlockFile(scope: !1505, file: !1, discriminator: 53)
!1505 = distinct !DILexicalBlock(scope: !1502, file: !1, line: 57, column: 1)
!1506 = !DILocation(line: 57, column: 1, scope: !1507)
!1507 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 54)
!1508 = distinct !DILexicalBlock(scope: !1505, file: !1, line: 57, column: 1)
!1509 = !DILocation(line: 57, column: 1, scope: !1510)
!1510 = !DILexicalBlockFile(scope: !1511, file: !1, discriminator: 55)
!1511 = distinct !DILexicalBlock(scope: !1512, file: !1, line: 57, column: 1)
!1512 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 57, column: 1)
!1513 = !DILocation(line: 57, column: 1, scope: !1514)
!1514 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 56)
!1515 = !DILocation(line: 57, column: 1, scope: !1516)
!1516 = !DILexicalBlockFile(scope: !1517, file: !1, discriminator: 57)
!1517 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 57, column: 1)
!1518 = !DILocation(line: 57, column: 1, scope: !1519)
!1519 = !DILexicalBlockFile(scope: !1520, file: !1, discriminator: 58)
!1520 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 57, column: 1)
!1521 = !DILocation(line: 57, column: 1, scope: !1522)
!1522 = !DILexicalBlockFile(scope: !1523, file: !1, discriminator: 59)
!1523 = distinct !DILexicalBlock(scope: !1524, file: !1, line: 57, column: 1)
!1524 = distinct !DILexicalBlock(scope: !1520, file: !1, line: 57, column: 1)
!1525 = !DILocation(line: 57, column: 1, scope: !1526)
!1526 = !DILexicalBlockFile(scope: !1523, file: !1, discriminator: 60)
!1527 = !DILocation(line: 57, column: 1, scope: !1528)
!1528 = !DILexicalBlockFile(scope: !1523, file: !1, discriminator: 61)
!1529 = !DILocation(line: 57, column: 1, scope: !1530)
!1530 = !DILexicalBlockFile(scope: !1524, file: !1, discriminator: 62)
!1531 = !DILocation(line: 57, column: 1, scope: !1532)
!1532 = !DILexicalBlockFile(scope: !1520, file: !1, discriminator: 63)
!1533 = !DILocation(line: 57, column: 1, scope: !1534)
!1534 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 64)
!1535 = !DILocation(line: 57, column: 1, scope: !1536)
!1536 = !DILexicalBlockFile(scope: !1537, file: !1, discriminator: 65)
!1537 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 57, column: 1)
!1538 = !DILocation(line: 57, column: 1, scope: !1539)
!1539 = !DILexicalBlockFile(scope: !1540, file: !1, discriminator: 66)
!1540 = distinct !DILexicalBlock(scope: !1508, file: !1, line: 57, column: 1)
!1541 = !DILocation(line: 57, column: 1, scope: !1542)
!1542 = !DILexicalBlockFile(scope: !1540, file: !1, discriminator: 67)
!1543 = !DILocation(line: 57, column: 1, scope: !1544)
!1544 = !DILexicalBlockFile(scope: !1545, file: !1, discriminator: 68)
!1545 = distinct !DILexicalBlock(scope: !1540, file: !1, line: 57, column: 1)
!1546 = !DILocation(line: 57, column: 1, scope: !1547)
!1547 = !DILexicalBlockFile(scope: !1545, file: !1, discriminator: 69)
!1548 = !DILocation(line: 57, column: 1, scope: !1549)
!1549 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 70)
!1550 = !DILocation(line: 57, column: 1, scope: !1551)
!1551 = !DILexicalBlockFile(scope: !1505, file: !1, discriminator: 71)
!1552 = !DILocation(line: 57, column: 1, scope: !1553)
!1553 = !DILexicalBlockFile(scope: !1487, file: !1, discriminator: 72)
!1554 = !DILocation(line: 57, column: 1, scope: !1555)
!1555 = !DILexicalBlockFile(scope: !1556, file: !1, discriminator: 73)
!1556 = distinct !DILexicalBlock(scope: !1487, file: !1, line: 57, column: 1)
!1557 = !DILocation(line: 57, column: 1, scope: !1558)
!1558 = !DILexicalBlockFile(scope: !1487, file: !1, discriminator: 74)
!1559 = !DILocation(line: 57, column: 1, scope: !1560)
!1560 = !DILexicalBlockFile(scope: !1561, file: !1, discriminator: 75)
!1561 = distinct !DILexicalBlock(scope: !1487, file: !1, line: 57, column: 1)
!1562 = !DILocation(line: 57, column: 1, scope: !1563)
!1563 = !DILexicalBlockFile(scope: !1564, file: !1, discriminator: 76)
!1564 = distinct !DILexicalBlock(scope: !1565, file: !1, line: 57, column: 1)
!1565 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 57, column: 1)
!1566 = !DILocation(line: 57, column: 1, scope: !1567)
!1567 = !DILexicalBlockFile(scope: !1561, file: !1, discriminator: 77)
!1568 = !DILocation(line: 57, column: 1, scope: !1569)
!1569 = !DILexicalBlockFile(scope: !1570, file: !1, discriminator: 78)
!1570 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 57, column: 1)
!1571 = !DILocation(line: 57, column: 1, scope: !1572)
!1572 = !DILexicalBlockFile(scope: !1573, file: !1, discriminator: 79)
!1573 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 57, column: 1)
!1574 = !DILocation(line: 57, column: 1, scope: !1575)
!1575 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 80)
!1576 = distinct !DILexicalBlock(scope: !1577, file: !1, line: 57, column: 1)
!1577 = distinct !DILexicalBlock(scope: !1573, file: !1, line: 57, column: 1)
!1578 = !DILocation(line: 57, column: 1, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 81)
!1580 = !DILocation(line: 57, column: 1, scope: !1581)
!1581 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 82)
!1582 = !DILocation(line: 57, column: 1, scope: !1583)
!1583 = !DILexicalBlockFile(scope: !1577, file: !1, discriminator: 83)
!1584 = !DILocation(line: 57, column: 1, scope: !1585)
!1585 = !DILexicalBlockFile(scope: !1573, file: !1, discriminator: 84)
!1586 = !DILocation(line: 57, column: 1, scope: !1587)
!1587 = !DILexicalBlockFile(scope: !1561, file: !1, discriminator: 85)
!1588 = !DILocation(line: 57, column: 1, scope: !1589)
!1589 = !DILexicalBlockFile(scope: !1590, file: !1, discriminator: 86)
!1590 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 57, column: 1)
!1591 = !DILocation(line: 57, column: 1, scope: !1592)
!1592 = !DILexicalBlockFile(scope: !1593, file: !1, discriminator: 87)
!1593 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 57, column: 1)
!1594 = !DILocation(line: 57, column: 1, scope: !1595)
!1595 = !DILexicalBlockFile(scope: !1593, file: !1, discriminator: 88)
!1596 = !DILocation(line: 57, column: 1, scope: !1597)
!1597 = !DILexicalBlockFile(scope: !1598, file: !1, discriminator: 89)
!1598 = distinct !DILexicalBlock(scope: !1593, file: !1, line: 57, column: 1)
!1599 = !DILocation(line: 57, column: 1, scope: !1600)
!1600 = !DILexicalBlockFile(scope: !1598, file: !1, discriminator: 90)
!1601 = !DILocation(line: 57, column: 1, scope: !1602)
!1602 = !DILexicalBlockFile(scope: !1561, file: !1, discriminator: 91)
!1603 = !DILocation(line: 57, column: 1, scope: !1604)
!1604 = !DILexicalBlockFile(scope: !1487, file: !1, discriminator: 92)
!1605 = !DILocation(line: 57, column: 1, scope: !1606)
!1606 = !DILexicalBlockFile(scope: !1607, file: !1, discriminator: 93)
!1607 = distinct !DILexicalBlock(scope: !1488, file: !1, line: 57, column: 1)
!1608 = !DILocation(line: 57, column: 1, scope: !1609)
!1609 = !DILexicalBlockFile(scope: !1610, file: !1, discriminator: 94)
!1610 = distinct !DILexicalBlock(scope: !1607, file: !1, line: 57, column: 1)
!1611 = !DILocation(line: 57, column: 1, scope: !1612)
!1612 = !DILexicalBlockFile(scope: !1613, file: !1, discriminator: 95)
!1613 = distinct !DILexicalBlock(scope: !1610, file: !1, line: 57, column: 1)
!1614 = !DILocation(line: 57, column: 1, scope: !1615)
!1615 = !DILexicalBlockFile(scope: !1616, file: !1, discriminator: 96)
!1616 = distinct !DILexicalBlock(scope: !1613, file: !1, line: 57, column: 1)
!1617 = !DILocation(line: 57, column: 1, scope: !1618)
!1618 = !DILexicalBlockFile(scope: !1613, file: !1, discriminator: 97)
!1619 = !DILocation(line: 57, column: 1, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 98)
!1621 = distinct !DILexicalBlock(scope: !1607, file: !1, line: 57, column: 1)
!1622 = !DILocation(line: 57, column: 1, scope: !1623)
!1623 = !DILexicalBlockFile(scope: !1624, file: !1, discriminator: 99)
!1624 = distinct !DILexicalBlock(scope: !1621, file: !1, line: 57, column: 1)
!1625 = !DILocation(line: 57, column: 1, scope: !1626)
!1626 = !DILexicalBlockFile(scope: !1627, file: !1, discriminator: 100)
!1627 = distinct !DILexicalBlock(scope: !1624, file: !1, line: 57, column: 1)
!1628 = !DILocation(line: 57, column: 1, scope: !1629)
!1629 = !DILexicalBlockFile(scope: !1630, file: !1, discriminator: 101)
!1630 = distinct !DILexicalBlock(scope: !1631, file: !1, line: 57, column: 1)
!1631 = distinct !DILexicalBlock(scope: !1627, file: !1, line: 57, column: 1)
!1632 = !DILocation(line: 57, column: 1, scope: !1633)
!1633 = !DILexicalBlockFile(scope: !1627, file: !1, discriminator: 102)
!1634 = !DILocation(line: 57, column: 1, scope: !1635)
!1635 = !DILexicalBlockFile(scope: !1636, file: !1, discriminator: 103)
!1636 = distinct !DILexicalBlock(scope: !1627, file: !1, line: 57, column: 1)
!1637 = !DILocation(line: 57, column: 1, scope: !1638)
!1638 = !DILexicalBlockFile(scope: !1639, file: !1, discriminator: 104)
!1639 = distinct !DILexicalBlock(scope: !1627, file: !1, line: 57, column: 1)
!1640 = !DILocation(line: 57, column: 1, scope: !1641)
!1641 = !DILexicalBlockFile(scope: !1642, file: !1, discriminator: 105)
!1642 = distinct !DILexicalBlock(scope: !1643, file: !1, line: 57, column: 1)
!1643 = distinct !DILexicalBlock(scope: !1639, file: !1, line: 57, column: 1)
!1644 = !DILocation(line: 57, column: 1, scope: !1645)
!1645 = !DILexicalBlockFile(scope: !1642, file: !1, discriminator: 106)
!1646 = !DILocation(line: 57, column: 1, scope: !1647)
!1647 = !DILexicalBlockFile(scope: !1642, file: !1, discriminator: 107)
!1648 = !DILocation(line: 57, column: 1, scope: !1649)
!1649 = !DILexicalBlockFile(scope: !1643, file: !1, discriminator: 108)
!1650 = !DILocation(line: 57, column: 1, scope: !1651)
!1651 = !DILexicalBlockFile(scope: !1639, file: !1, discriminator: 109)
!1652 = !DILocation(line: 57, column: 1, scope: !1653)
!1653 = !DILexicalBlockFile(scope: !1627, file: !1, discriminator: 110)
!1654 = !DILocation(line: 57, column: 1, scope: !1655)
!1655 = !DILexicalBlockFile(scope: !1656, file: !1, discriminator: 111)
!1656 = distinct !DILexicalBlock(scope: !1627, file: !1, line: 57, column: 1)
!1657 = !DILocation(line: 57, column: 1, scope: !1658)
!1658 = !DILexicalBlockFile(scope: !1659, file: !1, discriminator: 112)
!1659 = distinct !DILexicalBlock(scope: !1627, file: !1, line: 57, column: 1)
!1660 = !DILocation(line: 57, column: 1, scope: !1661)
!1661 = !DILexicalBlockFile(scope: !1659, file: !1, discriminator: 113)
!1662 = !DILocation(line: 57, column: 1, scope: !1663)
!1663 = !DILexicalBlockFile(scope: !1664, file: !1, discriminator: 114)
!1664 = distinct !DILexicalBlock(scope: !1659, file: !1, line: 57, column: 1)
!1665 = !DILocation(line: 57, column: 1, scope: !1666)
!1666 = !DILexicalBlockFile(scope: !1664, file: !1, discriminator: 115)
!1667 = !DILocation(line: 57, column: 1, scope: !1668)
!1668 = !DILexicalBlockFile(scope: !1627, file: !1, discriminator: 116)
!1669 = !DILocation(line: 57, column: 1, scope: !1670)
!1670 = !DILexicalBlockFile(scope: !1624, file: !1, discriminator: 117)
!1671 = !DILocation(line: 57, column: 1, scope: !1672)
!1672 = !DILexicalBlockFile(scope: !1607, file: !1, discriminator: 118)
!1673 = !DILocation(line: 57, column: 1, scope: !1674)
!1674 = !DILexicalBlockFile(scope: !1675, file: !1, discriminator: 119)
!1675 = distinct !DILexicalBlock(scope: !1607, file: !1, line: 57, column: 1)
!1676 = !DILocation(line: 57, column: 1, scope: !1677)
!1677 = !DILexicalBlockFile(scope: !1607, file: !1, discriminator: 120)
!1678 = !DILocation(line: 57, column: 1, scope: !1679)
!1679 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 121)
!1680 = distinct !DILexicalBlock(scope: !1607, file: !1, line: 57, column: 1)
!1681 = !DILocation(line: 57, column: 1, scope: !1682)
!1682 = !DILexicalBlockFile(scope: !1683, file: !1, discriminator: 122)
!1683 = distinct !DILexicalBlock(scope: !1684, file: !1, line: 57, column: 1)
!1684 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 57, column: 1)
!1685 = !DILocation(line: 57, column: 1, scope: !1686)
!1686 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 123)
!1687 = !DILocation(line: 57, column: 1, scope: !1688)
!1688 = !DILexicalBlockFile(scope: !1689, file: !1, discriminator: 124)
!1689 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 57, column: 1)
!1690 = !DILocation(line: 57, column: 1, scope: !1691)
!1691 = !DILexicalBlockFile(scope: !1692, file: !1, discriminator: 125)
!1692 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 57, column: 1)
!1693 = !DILocation(line: 57, column: 1, scope: !1694)
!1694 = !DILexicalBlockFile(scope: !1695, file: !1, discriminator: 126)
!1695 = distinct !DILexicalBlock(scope: !1696, file: !1, line: 57, column: 1)
!1696 = distinct !DILexicalBlock(scope: !1692, file: !1, line: 57, column: 1)
!1697 = !DILocation(line: 57, column: 1, scope: !1698)
!1698 = !DILexicalBlockFile(scope: !1695, file: !1, discriminator: 127)
!1699 = !DILocation(line: 57, column: 1, scope: !1700)
!1700 = !DILexicalBlockFile(scope: !1695, file: !1, discriminator: 128)
!1701 = !DILocation(line: 57, column: 1, scope: !1702)
!1702 = !DILexicalBlockFile(scope: !1696, file: !1, discriminator: 129)
!1703 = !DILocation(line: 57, column: 1, scope: !1704)
!1704 = !DILexicalBlockFile(scope: !1692, file: !1, discriminator: 130)
!1705 = !DILocation(line: 57, column: 1, scope: !1706)
!1706 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 131)
!1707 = !DILocation(line: 57, column: 1, scope: !1708)
!1708 = !DILexicalBlockFile(scope: !1709, file: !1, discriminator: 132)
!1709 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 57, column: 1)
!1710 = !DILocation(line: 57, column: 1, scope: !1711)
!1711 = !DILexicalBlockFile(scope: !1712, file: !1, discriminator: 133)
!1712 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 57, column: 1)
!1713 = !DILocation(line: 57, column: 1, scope: !1714)
!1714 = !DILexicalBlockFile(scope: !1712, file: !1, discriminator: 134)
!1715 = !DILocation(line: 57, column: 1, scope: !1716)
!1716 = !DILexicalBlockFile(scope: !1717, file: !1, discriminator: 135)
!1717 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 57, column: 1)
!1718 = !DILocation(line: 57, column: 1, scope: !1719)
!1719 = !DILexicalBlockFile(scope: !1717, file: !1, discriminator: 136)
!1720 = !DILocation(line: 57, column: 1, scope: !1721)
!1721 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 137)
!1722 = !DILocation(line: 57, column: 1, scope: !1723)
!1723 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 138)
!1724 = !DILocation(line: 57, column: 1, scope: !1725)
!1725 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 139)
!1726 = !DILocalVariable(name: "head", arg: 1, scope: !350, file: !1, line: 57, type: !330)
!1727 = !DILocation(line: 57, column: 1, scope: !350)
!1728 = !DILocalVariable(name: "elm", arg: 2, scope: !350, file: !1, line: 57, type: !243)
!1729 = !DILocalVariable(name: "child", scope: !350, file: !1, line: 57, type: !243)
!1730 = !DILocalVariable(name: "parent", scope: !350, file: !1, line: 57, type: !243)
!1731 = !DILocalVariable(name: "old", scope: !350, file: !1, line: 57, type: !243)
!1732 = !DILocalVariable(name: "color", scope: !350, file: !1, line: 57, type: !80)
!1733 = !DILocation(line: 57, column: 1, scope: !1734)
!1734 = distinct !DILexicalBlock(scope: !350, file: !1, line: 57, column: 1)
!1735 = !DILocation(line: 57, column: 1, scope: !1736)
!1736 = !DILexicalBlockFile(scope: !1734, file: !1, discriminator: 140)
!1737 = !DILocation(line: 57, column: 1, scope: !1738)
!1738 = !DILexicalBlockFile(scope: !1739, file: !1, discriminator: 141)
!1739 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 57, column: 1)
!1740 = !DILocation(line: 57, column: 1, scope: !1741)
!1741 = !DILexicalBlockFile(scope: !1739, file: !1, discriminator: 142)
!1742 = !DILocalVariable(name: "left", scope: !1743, file: !1, line: 57, type: !243)
!1743 = distinct !DILexicalBlock(scope: !1739, file: !1, line: 57, column: 1)
!1744 = !DILocation(line: 57, column: 1, scope: !1743)
!1745 = !DILocation(line: 57, column: 1, scope: !1746)
!1746 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 143)
!1747 = !DILocation(line: 57, column: 1, scope: !1748)
!1748 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 144)
!1749 = !DILocation(line: 57, column: 1, scope: !1750)
!1750 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 145)
!1751 = !DILocation(line: 57, column: 1, scope: !1752)
!1752 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 146)
!1753 = !DILocation(line: 57, column: 1, scope: !1754)
!1754 = !DILexicalBlockFile(scope: !1755, file: !1, discriminator: 147)
!1755 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 57, column: 1)
!1756 = !DILocation(line: 57, column: 1, scope: !1757)
!1757 = !DILexicalBlockFile(scope: !1758, file: !1, discriminator: 148)
!1758 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 57, column: 1)
!1759 = !DILocation(line: 57, column: 1, scope: !1760)
!1760 = !DILexicalBlockFile(scope: !1761, file: !1, discriminator: 149)
!1761 = distinct !DILexicalBlock(scope: !1762, file: !1, line: 57, column: 1)
!1762 = distinct !DILexicalBlock(scope: !1758, file: !1, line: 57, column: 1)
!1763 = !DILocation(line: 57, column: 1, scope: !1764)
!1764 = !DILexicalBlockFile(scope: !1761, file: !1, discriminator: 150)
!1765 = !DILocation(line: 57, column: 1, scope: !1766)
!1766 = !DILexicalBlockFile(scope: !1761, file: !1, discriminator: 151)
!1767 = !DILocation(line: 57, column: 1, scope: !1768)
!1768 = !DILexicalBlockFile(scope: !1762, file: !1, discriminator: 152)
!1769 = !DILocation(line: 57, column: 1, scope: !1770)
!1770 = !DILexicalBlockFile(scope: !1771, file: !1, discriminator: 153)
!1771 = distinct !DILexicalBlock(scope: !1762, file: !1, line: 57, column: 1)
!1772 = !DILocation(line: 57, column: 1, scope: !1773)
!1773 = !DILexicalBlockFile(scope: !1762, file: !1, discriminator: 154)
!1774 = !DILocation(line: 57, column: 1, scope: !1775)
!1775 = !DILexicalBlockFile(scope: !1758, file: !1, discriminator: 155)
!1776 = !DILocation(line: 57, column: 1, scope: !1777)
!1777 = !DILexicalBlockFile(scope: !1778, file: !1, discriminator: 156)
!1778 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 57, column: 1)
!1779 = !DILocation(line: 57, column: 1, scope: !1780)
!1780 = !DILexicalBlockFile(scope: !1778, file: !1, discriminator: 157)
!1781 = !DILocation(line: 57, column: 1, scope: !1782)
!1782 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 158)
!1783 = !DILocation(line: 57, column: 1, scope: !1784)
!1784 = !DILexicalBlockFile(scope: !1785, file: !1, discriminator: 159)
!1785 = distinct !DILexicalBlock(scope: !1786, file: !1, line: 57, column: 1)
!1786 = distinct !DILexicalBlock(scope: !1787, file: !1, line: 57, column: 1)
!1787 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 57, column: 1)
!1788 = !DILocation(line: 57, column: 1, scope: !1789)
!1789 = !DILexicalBlockFile(scope: !1785, file: !1, discriminator: 160)
!1790 = !DILocation(line: 57, column: 1, scope: !1791)
!1791 = !DILexicalBlockFile(scope: !1785, file: !1, discriminator: 161)
!1792 = !DILocation(line: 57, column: 1, scope: !1793)
!1793 = !DILexicalBlockFile(scope: !1786, file: !1, discriminator: 162)
!1794 = !DILocation(line: 57, column: 1, scope: !1795)
!1795 = !DILexicalBlockFile(scope: !1796, file: !1, discriminator: 163)
!1796 = distinct !DILexicalBlock(scope: !1786, file: !1, line: 57, column: 1)
!1797 = !DILocation(line: 57, column: 1, scope: !1798)
!1798 = !DILexicalBlockFile(scope: !1786, file: !1, discriminator: 164)
!1799 = !DILocation(line: 57, column: 1, scope: !1800)
!1800 = !DILexicalBlockFile(scope: !1787, file: !1, discriminator: 165)
!1801 = !DILocation(line: 57, column: 1, scope: !1802)
!1802 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 166)
!1803 = !DILocation(line: 57, column: 1, scope: !1804)
!1804 = !DILexicalBlockFile(scope: !1805, file: !1, discriminator: 167)
!1805 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 57, column: 1)
!1806 = !DILocation(line: 57, column: 1, scope: !1807)
!1807 = !DILexicalBlockFile(scope: !1808, file: !1, discriminator: 168)
!1808 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 57, column: 1)
!1809 = !DILocation(line: 57, column: 1, scope: !1810)
!1810 = !DILexicalBlockFile(scope: !1811, file: !1, discriminator: 169)
!1811 = distinct !DILexicalBlock(scope: !1808, file: !1, line: 57, column: 1)
!1812 = !DILocation(line: 57, column: 1, scope: !1813)
!1813 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 170)
!1814 = distinct !DILexicalBlock(scope: !1811, file: !1, line: 57, column: 1)
!1815 = !DILocation(line: 57, column: 1, scope: !1816)
!1816 = !DILexicalBlockFile(scope: !1817, file: !1, discriminator: 171)
!1817 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 57, column: 1)
!1818 = !DILocation(line: 57, column: 1, scope: !1819)
!1819 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 172)
!1820 = !DILocation(line: 57, column: 1, scope: !1821)
!1821 = !DILexicalBlockFile(scope: !1811, file: !1, discriminator: 173)
!1822 = !DILocation(line: 57, column: 1, scope: !1823)
!1823 = !DILexicalBlockFile(scope: !1811, file: !1, discriminator: 174)
!1824 = !DILocation(line: 57, column: 1, scope: !1825)
!1825 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 175)
!1826 = !DILocation(line: 57, column: 1, scope: !1827)
!1827 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 176)
!1828 = !DILocation(line: 57, column: 1, scope: !1829)
!1829 = !DILexicalBlockFile(scope: !1830, file: !1, discriminator: 177)
!1830 = distinct !DILexicalBlock(scope: !350, file: !1, line: 57, column: 1)
!1831 = !DILocation(line: 57, column: 1, scope: !1832)
!1832 = !DILexicalBlockFile(scope: !1833, file: !1, discriminator: 178)
!1833 = distinct !DILexicalBlock(scope: !350, file: !1, line: 57, column: 1)
!1834 = !DILocation(line: 57, column: 1, scope: !1835)
!1835 = !DILexicalBlockFile(scope: !1836, file: !1, discriminator: 179)
!1836 = distinct !DILexicalBlock(scope: !1837, file: !1, line: 57, column: 1)
!1837 = distinct !DILexicalBlock(scope: !1833, file: !1, line: 57, column: 1)
!1838 = !DILocation(line: 57, column: 1, scope: !1839)
!1839 = !DILexicalBlockFile(scope: !1836, file: !1, discriminator: 180)
!1840 = !DILocation(line: 57, column: 1, scope: !1841)
!1841 = !DILexicalBlockFile(scope: !1836, file: !1, discriminator: 181)
!1842 = !DILocation(line: 57, column: 1, scope: !1843)
!1843 = !DILexicalBlockFile(scope: !1837, file: !1, discriminator: 182)
!1844 = !DILocation(line: 57, column: 1, scope: !1845)
!1845 = !DILexicalBlockFile(scope: !1846, file: !1, discriminator: 183)
!1846 = distinct !DILexicalBlock(scope: !1837, file: !1, line: 57, column: 1)
!1847 = !DILocation(line: 57, column: 1, scope: !1848)
!1848 = !DILexicalBlockFile(scope: !1837, file: !1, discriminator: 184)
!1849 = !DILocation(line: 57, column: 1, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !1833, file: !1, discriminator: 185)
!1851 = !DILocation(line: 57, column: 1, scope: !1852)
!1852 = !DILexicalBlockFile(scope: !1833, file: !1, discriminator: 186)
!1853 = !DILocation(line: 57, column: 1, scope: !1854)
!1854 = !DILexicalBlockFile(scope: !1855, file: !1, discriminator: 187)
!1855 = distinct !DILexicalBlock(scope: !350, file: !1, line: 57, column: 1)
!1856 = !DILocation(line: 57, column: 1, scope: !1857)
!1857 = !DILexicalBlockFile(scope: !1855, file: !1, discriminator: 188)
!1858 = !DILocation(line: 57, column: 1, scope: !1859)
!1859 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 189)
!1860 = !DILocalVariable(name: "signum", arg: 1, scope: !354, file: !1, line: 229, type: !80)
!1861 = !DILocation(line: 229, column: 47, scope: !354)
!1862 = !DILocalVariable(name: "sa", scope: !354, file: !1, line: 231, type: !1044)
!1863 = !DILocation(line: 231, column: 20, scope: !354)
!1864 = !DILocation(line: 233, column: 3, scope: !354)
!1865 = !DILocation(line: 234, column: 6, scope: !354)
!1866 = !DILocation(line: 234, column: 17, scope: !354)
!1867 = !DILocation(line: 240, column: 17, scope: !1868)
!1868 = distinct !DILexicalBlock(scope: !354, file: !1, line: 240, column: 7)
!1869 = !DILocation(line: 240, column: 7, scope: !1868)
!1870 = !DILocation(line: 240, column: 7, scope: !354)
!1871 = !DILocation(line: 241, column: 5, scope: !1868)
!1872 = !DILocation(line: 242, column: 1, scope: !354)
!1873 = !DILocalVariable(name: "head", arg: 1, scope: !351, file: !1, line: 57, type: !330)
!1874 = !DILocation(line: 57, column: 1, scope: !351)
!1875 = !DILocalVariable(name: "parent", arg: 2, scope: !351, file: !1, line: 57, type: !243)
!1876 = !DILocalVariable(name: "elm", arg: 3, scope: !351, file: !1, line: 57, type: !243)
!1877 = !DILocalVariable(name: "tmp", scope: !351, file: !1, line: 57, type: !243)
!1878 = !DILocation(line: 57, column: 1, scope: !1879)
!1879 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 190)
!1880 = !DILocation(line: 57, column: 1, scope: !1881)
!1881 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 191)
!1882 = !DILocation(line: 57, column: 1, scope: !1883)
!1883 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 192)
!1884 = !DILocation(line: 57, column: 1, scope: !1885)
!1885 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 193)
!1886 = !DILocation(line: 57, column: 1, scope: !1887)
!1887 = !DILexicalBlockFile(scope: !1888, file: !1, discriminator: 194)
!1888 = distinct !DILexicalBlock(scope: !1889, file: !1, line: 57, column: 1)
!1889 = distinct !DILexicalBlock(scope: !351, file: !1, line: 57, column: 1)
!1890 = !DILocation(line: 57, column: 1, scope: !1891)
!1891 = !DILexicalBlockFile(scope: !1892, file: !1, discriminator: 195)
!1892 = distinct !DILexicalBlock(scope: !1888, file: !1, line: 57, column: 1)
!1893 = !DILocation(line: 57, column: 1, scope: !1894)
!1894 = !DILexicalBlockFile(scope: !1895, file: !1, discriminator: 196)
!1895 = distinct !DILexicalBlock(scope: !1896, file: !1, line: 57, column: 1)
!1896 = distinct !DILexicalBlock(scope: !1892, file: !1, line: 57, column: 1)
!1897 = !DILocation(line: 57, column: 1, scope: !1898)
!1898 = !DILexicalBlockFile(scope: !1899, file: !1, discriminator: 197)
!1899 = distinct !DILexicalBlock(scope: !1895, file: !1, line: 57, column: 1)
!1900 = !DILocation(line: 57, column: 1, scope: !1901)
!1901 = !DILexicalBlockFile(scope: !1895, file: !1, discriminator: 198)
!1902 = !DILocation(line: 57, column: 1, scope: !1903)
!1903 = !DILexicalBlockFile(scope: !1904, file: !1, discriminator: 199)
!1904 = distinct !DILexicalBlock(scope: !1895, file: !1, line: 57, column: 1)
!1905 = !DILocation(line: 57, column: 1, scope: !1906)
!1906 = !DILexicalBlockFile(scope: !1907, file: !1, discriminator: 200)
!1907 = distinct !DILexicalBlock(scope: !1908, file: !1, line: 57, column: 1)
!1908 = distinct !DILexicalBlock(scope: !1904, file: !1, line: 57, column: 1)
!1909 = !DILocation(line: 57, column: 1, scope: !1910)
!1910 = !DILexicalBlockFile(scope: !1904, file: !1, discriminator: 201)
!1911 = !DILocation(line: 57, column: 1, scope: !1912)
!1912 = !DILexicalBlockFile(scope: !1913, file: !1, discriminator: 202)
!1913 = distinct !DILexicalBlock(scope: !1904, file: !1, line: 57, column: 1)
!1914 = !DILocation(line: 57, column: 1, scope: !1915)
!1915 = !DILexicalBlockFile(scope: !1916, file: !1, discriminator: 203)
!1916 = distinct !DILexicalBlock(scope: !1904, file: !1, line: 57, column: 1)
!1917 = !DILocation(line: 57, column: 1, scope: !1918)
!1918 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 204)
!1919 = distinct !DILexicalBlock(scope: !1920, file: !1, line: 57, column: 1)
!1920 = distinct !DILexicalBlock(scope: !1916, file: !1, line: 57, column: 1)
!1921 = !DILocation(line: 57, column: 1, scope: !1922)
!1922 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 205)
!1923 = !DILocation(line: 57, column: 1, scope: !1924)
!1924 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 206)
!1925 = !DILocation(line: 57, column: 1, scope: !1926)
!1926 = !DILexicalBlockFile(scope: !1920, file: !1, discriminator: 207)
!1927 = !DILocation(line: 57, column: 1, scope: !1928)
!1928 = !DILexicalBlockFile(scope: !1916, file: !1, discriminator: 208)
!1929 = !DILocation(line: 57, column: 1, scope: !1930)
!1930 = !DILexicalBlockFile(scope: !1904, file: !1, discriminator: 209)
!1931 = !DILocation(line: 57, column: 1, scope: !1932)
!1932 = !DILexicalBlockFile(scope: !1933, file: !1, discriminator: 210)
!1933 = distinct !DILexicalBlock(scope: !1904, file: !1, line: 57, column: 1)
!1934 = !DILocation(line: 57, column: 1, scope: !1935)
!1935 = !DILexicalBlockFile(scope: !1936, file: !1, discriminator: 211)
!1936 = distinct !DILexicalBlock(scope: !1904, file: !1, line: 57, column: 1)
!1937 = !DILocation(line: 57, column: 1, scope: !1938)
!1938 = !DILexicalBlockFile(scope: !1936, file: !1, discriminator: 212)
!1939 = !DILocation(line: 57, column: 1, scope: !1940)
!1940 = !DILexicalBlockFile(scope: !1941, file: !1, discriminator: 213)
!1941 = distinct !DILexicalBlock(scope: !1936, file: !1, line: 57, column: 1)
!1942 = !DILocation(line: 57, column: 1, scope: !1943)
!1943 = !DILexicalBlockFile(scope: !1941, file: !1, discriminator: 214)
!1944 = !DILocation(line: 57, column: 1, scope: !1945)
!1945 = !DILexicalBlockFile(scope: !1904, file: !1, discriminator: 215)
!1946 = !DILocation(line: 57, column: 1, scope: !1947)
!1947 = !DILexicalBlockFile(scope: !1895, file: !1, discriminator: 216)
!1948 = !DILocation(line: 57, column: 1, scope: !1949)
!1949 = !DILexicalBlockFile(scope: !1950, file: !1, discriminator: 217)
!1950 = distinct !DILexicalBlock(scope: !1892, file: !1, line: 57, column: 1)
!1951 = !DILocation(line: 57, column: 1, scope: !1952)
!1952 = !DILexicalBlockFile(scope: !1950, file: !1, discriminator: 218)
!1953 = !DILocation(line: 57, column: 1, scope: !1954)
!1954 = !DILexicalBlockFile(scope: !1950, file: !1, discriminator: 219)
!1955 = !DILocation(line: 57, column: 1, scope: !1956)
!1956 = !DILexicalBlockFile(scope: !1950, file: !1, discriminator: 220)
!1957 = !DILocation(line: 57, column: 1, scope: !1958)
!1958 = !DILexicalBlockFile(scope: !1959, file: !1, discriminator: 221)
!1959 = distinct !DILexicalBlock(scope: !1950, file: !1, line: 57, column: 1)
!1960 = !DILocation(line: 57, column: 1, scope: !1961)
!1961 = !DILexicalBlockFile(scope: !1962, file: !1, discriminator: 222)
!1962 = distinct !DILexicalBlock(scope: !1963, file: !1, line: 57, column: 1)
!1963 = distinct !DILexicalBlock(scope: !1950, file: !1, line: 57, column: 1)
!1964 = !DILocation(line: 57, column: 1, scope: !1965)
!1965 = !DILexicalBlockFile(scope: !1962, file: !1, discriminator: 223)
!1966 = !DILocalVariable(name: "oleft", scope: !1967, file: !1, line: 57, type: !243)
!1967 = distinct !DILexicalBlock(scope: !1962, file: !1, line: 57, column: 1)
!1968 = !DILocation(line: 57, column: 1, scope: !1967)
!1969 = !DILocation(line: 57, column: 1, scope: !1970)
!1970 = !DILexicalBlockFile(scope: !1971, file: !1, discriminator: 224)
!1971 = distinct !DILexicalBlock(scope: !1967, file: !1, line: 57, column: 1)
!1972 = !DILocation(line: 57, column: 1, scope: !1973)
!1973 = !DILexicalBlockFile(scope: !1971, file: !1, discriminator: 225)
!1974 = !DILocation(line: 57, column: 1, scope: !1975)
!1975 = !DILexicalBlockFile(scope: !1967, file: !1, discriminator: 226)
!1976 = !DILocation(line: 57, column: 1, scope: !1977)
!1977 = !DILexicalBlockFile(scope: !1978, file: !1, discriminator: 227)
!1978 = distinct !DILexicalBlock(scope: !1967, file: !1, line: 57, column: 1)
!1979 = !DILocation(line: 57, column: 1, scope: !1980)
!1980 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 228)
!1981 = distinct !DILexicalBlock(scope: !1982, file: !1, line: 57, column: 1)
!1982 = distinct !DILexicalBlock(scope: !1978, file: !1, line: 57, column: 1)
!1983 = !DILocation(line: 57, column: 1, scope: !1984)
!1984 = !DILexicalBlockFile(scope: !1978, file: !1, discriminator: 229)
!1985 = !DILocation(line: 57, column: 1, scope: !1986)
!1986 = !DILexicalBlockFile(scope: !1987, file: !1, discriminator: 230)
!1987 = distinct !DILexicalBlock(scope: !1978, file: !1, line: 57, column: 1)
!1988 = !DILocation(line: 57, column: 1, scope: !1989)
!1989 = !DILexicalBlockFile(scope: !1990, file: !1, discriminator: 231)
!1990 = distinct !DILexicalBlock(scope: !1978, file: !1, line: 57, column: 1)
!1991 = !DILocation(line: 57, column: 1, scope: !1992)
!1992 = !DILexicalBlockFile(scope: !1993, file: !1, discriminator: 232)
!1993 = distinct !DILexicalBlock(scope: !1994, file: !1, line: 57, column: 1)
!1994 = distinct !DILexicalBlock(scope: !1990, file: !1, line: 57, column: 1)
!1995 = !DILocation(line: 57, column: 1, scope: !1996)
!1996 = !DILexicalBlockFile(scope: !1993, file: !1, discriminator: 233)
!1997 = !DILocation(line: 57, column: 1, scope: !1998)
!1998 = !DILexicalBlockFile(scope: !1993, file: !1, discriminator: 234)
!1999 = !DILocation(line: 57, column: 1, scope: !2000)
!2000 = !DILexicalBlockFile(scope: !1994, file: !1, discriminator: 235)
!2001 = !DILocation(line: 57, column: 1, scope: !2002)
!2002 = !DILexicalBlockFile(scope: !1990, file: !1, discriminator: 236)
!2003 = !DILocation(line: 57, column: 1, scope: !2004)
!2004 = !DILexicalBlockFile(scope: !1978, file: !1, discriminator: 237)
!2005 = !DILocation(line: 57, column: 1, scope: !2006)
!2006 = !DILexicalBlockFile(scope: !2007, file: !1, discriminator: 238)
!2007 = distinct !DILexicalBlock(scope: !1978, file: !1, line: 57, column: 1)
!2008 = !DILocation(line: 57, column: 1, scope: !2009)
!2009 = !DILexicalBlockFile(scope: !2010, file: !1, discriminator: 239)
!2010 = distinct !DILexicalBlock(scope: !1978, file: !1, line: 57, column: 1)
!2011 = !DILocation(line: 57, column: 1, scope: !2012)
!2012 = !DILexicalBlockFile(scope: !2010, file: !1, discriminator: 240)
!2013 = !DILocation(line: 57, column: 1, scope: !2014)
!2014 = !DILexicalBlockFile(scope: !2015, file: !1, discriminator: 241)
!2015 = distinct !DILexicalBlock(scope: !2010, file: !1, line: 57, column: 1)
!2016 = !DILocation(line: 57, column: 1, scope: !2017)
!2017 = !DILexicalBlockFile(scope: !2015, file: !1, discriminator: 242)
!2018 = !DILocation(line: 57, column: 1, scope: !2019)
!2019 = !DILexicalBlockFile(scope: !1978, file: !1, discriminator: 243)
!2020 = !DILocation(line: 57, column: 1, scope: !2021)
!2021 = !DILexicalBlockFile(scope: !1967, file: !1, discriminator: 244)
!2022 = !DILocation(line: 57, column: 1, scope: !2023)
!2023 = !DILexicalBlockFile(scope: !1963, file: !1, discriminator: 245)
!2024 = !DILocation(line: 57, column: 1, scope: !2025)
!2025 = !DILexicalBlockFile(scope: !2026, file: !1, discriminator: 246)
!2026 = distinct !DILexicalBlock(scope: !1963, file: !1, line: 57, column: 1)
!2027 = !DILocation(line: 57, column: 1, scope: !2028)
!2028 = !DILexicalBlockFile(scope: !1963, file: !1, discriminator: 247)
!2029 = !DILocation(line: 57, column: 1, scope: !2030)
!2030 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 248)
!2031 = distinct !DILexicalBlock(scope: !1963, file: !1, line: 57, column: 1)
!2032 = !DILocation(line: 57, column: 1, scope: !2033)
!2033 = !DILexicalBlockFile(scope: !2034, file: !1, discriminator: 249)
!2034 = distinct !DILexicalBlock(scope: !2035, file: !1, line: 57, column: 1)
!2035 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 57, column: 1)
!2036 = !DILocation(line: 57, column: 1, scope: !2037)
!2037 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 250)
!2038 = !DILocation(line: 57, column: 1, scope: !2039)
!2039 = !DILexicalBlockFile(scope: !2040, file: !1, discriminator: 251)
!2040 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 57, column: 1)
!2041 = !DILocation(line: 57, column: 1, scope: !2042)
!2042 = !DILexicalBlockFile(scope: !2043, file: !1, discriminator: 252)
!2043 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 57, column: 1)
!2044 = !DILocation(line: 57, column: 1, scope: !2045)
!2045 = !DILexicalBlockFile(scope: !2046, file: !1, discriminator: 253)
!2046 = distinct !DILexicalBlock(scope: !2047, file: !1, line: 57, column: 1)
!2047 = distinct !DILexicalBlock(scope: !2043, file: !1, line: 57, column: 1)
!2048 = !DILocation(line: 57, column: 1, scope: !2049)
!2049 = !DILexicalBlockFile(scope: !2046, file: !1, discriminator: 254)
!2050 = !DILocation(line: 57, column: 1, scope: !2051)
!2051 = !DILexicalBlockFile(scope: !2046, file: !1, discriminator: 255)
!2052 = !DILocation(line: 57, column: 1, scope: !2053)
!2053 = !DILexicalBlockFile(scope: !2047, file: !1, discriminator: 256)
!2054 = !DILocation(line: 57, column: 1, scope: !2055)
!2055 = !DILexicalBlockFile(scope: !2043, file: !1, discriminator: 257)
!2056 = !DILocation(line: 57, column: 1, scope: !2057)
!2057 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 258)
!2058 = !DILocation(line: 57, column: 1, scope: !2059)
!2059 = !DILexicalBlockFile(scope: !2060, file: !1, discriminator: 259)
!2060 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 57, column: 1)
!2061 = !DILocation(line: 57, column: 1, scope: !2062)
!2062 = !DILexicalBlockFile(scope: !2063, file: !1, discriminator: 260)
!2063 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 57, column: 1)
!2064 = !DILocation(line: 57, column: 1, scope: !2065)
!2065 = !DILexicalBlockFile(scope: !2063, file: !1, discriminator: 261)
!2066 = !DILocation(line: 57, column: 1, scope: !2067)
!2067 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 262)
!2068 = distinct !DILexicalBlock(scope: !2063, file: !1, line: 57, column: 1)
!2069 = !DILocation(line: 57, column: 1, scope: !2070)
!2070 = !DILexicalBlockFile(scope: !2068, file: !1, discriminator: 263)
!2071 = !DILocation(line: 57, column: 1, scope: !2072)
!2072 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 264)
!2073 = !DILocation(line: 57, column: 1, scope: !2074)
!2074 = !DILexicalBlockFile(scope: !1963, file: !1, discriminator: 265)
!2075 = !DILocation(line: 57, column: 1, scope: !2076)
!2076 = !DILexicalBlockFile(scope: !1892, file: !1, discriminator: 266)
!2077 = !DILocation(line: 57, column: 1, scope: !2078)
!2078 = !DILexicalBlockFile(scope: !2079, file: !1, discriminator: 267)
!2079 = distinct !DILexicalBlock(scope: !1888, file: !1, line: 57, column: 1)
!2080 = !DILocation(line: 57, column: 1, scope: !2081)
!2081 = !DILexicalBlockFile(scope: !2082, file: !1, discriminator: 268)
!2082 = distinct !DILexicalBlock(scope: !2083, file: !1, line: 57, column: 1)
!2083 = distinct !DILexicalBlock(scope: !2079, file: !1, line: 57, column: 1)
!2084 = !DILocation(line: 57, column: 1, scope: !2085)
!2085 = !DILexicalBlockFile(scope: !2086, file: !1, discriminator: 269)
!2086 = distinct !DILexicalBlock(scope: !2082, file: !1, line: 57, column: 1)
!2087 = !DILocation(line: 57, column: 1, scope: !2088)
!2088 = !DILexicalBlockFile(scope: !2082, file: !1, discriminator: 270)
!2089 = !DILocation(line: 57, column: 1, scope: !2090)
!2090 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 271)
!2091 = distinct !DILexicalBlock(scope: !2082, file: !1, line: 57, column: 1)
!2092 = !DILocation(line: 57, column: 1, scope: !2093)
!2093 = !DILexicalBlockFile(scope: !2094, file: !1, discriminator: 272)
!2094 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 57, column: 1)
!2095 = distinct !DILexicalBlock(scope: !2091, file: !1, line: 57, column: 1)
!2096 = !DILocation(line: 57, column: 1, scope: !2097)
!2097 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 273)
!2098 = !DILocation(line: 57, column: 1, scope: !2099)
!2099 = !DILexicalBlockFile(scope: !2100, file: !1, discriminator: 274)
!2100 = distinct !DILexicalBlock(scope: !2091, file: !1, line: 57, column: 1)
!2101 = !DILocation(line: 57, column: 1, scope: !2102)
!2102 = !DILexicalBlockFile(scope: !2103, file: !1, discriminator: 275)
!2103 = distinct !DILexicalBlock(scope: !2091, file: !1, line: 57, column: 1)
!2104 = !DILocation(line: 57, column: 1, scope: !2105)
!2105 = !DILexicalBlockFile(scope: !2106, file: !1, discriminator: 276)
!2106 = distinct !DILexicalBlock(scope: !2107, file: !1, line: 57, column: 1)
!2107 = distinct !DILexicalBlock(scope: !2103, file: !1, line: 57, column: 1)
!2108 = !DILocation(line: 57, column: 1, scope: !2109)
!2109 = !DILexicalBlockFile(scope: !2106, file: !1, discriminator: 277)
!2110 = !DILocation(line: 57, column: 1, scope: !2111)
!2111 = !DILexicalBlockFile(scope: !2106, file: !1, discriminator: 278)
!2112 = !DILocation(line: 57, column: 1, scope: !2113)
!2113 = !DILexicalBlockFile(scope: !2107, file: !1, discriminator: 279)
!2114 = !DILocation(line: 57, column: 1, scope: !2115)
!2115 = !DILexicalBlockFile(scope: !2103, file: !1, discriminator: 280)
!2116 = !DILocation(line: 57, column: 1, scope: !2117)
!2117 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 281)
!2118 = !DILocation(line: 57, column: 1, scope: !2119)
!2119 = !DILexicalBlockFile(scope: !2120, file: !1, discriminator: 282)
!2120 = distinct !DILexicalBlock(scope: !2091, file: !1, line: 57, column: 1)
!2121 = !DILocation(line: 57, column: 1, scope: !2122)
!2122 = !DILexicalBlockFile(scope: !2123, file: !1, discriminator: 283)
!2123 = distinct !DILexicalBlock(scope: !2091, file: !1, line: 57, column: 1)
!2124 = !DILocation(line: 57, column: 1, scope: !2125)
!2125 = !DILexicalBlockFile(scope: !2123, file: !1, discriminator: 284)
!2126 = !DILocation(line: 57, column: 1, scope: !2127)
!2127 = !DILexicalBlockFile(scope: !2128, file: !1, discriminator: 285)
!2128 = distinct !DILexicalBlock(scope: !2123, file: !1, line: 57, column: 1)
!2129 = !DILocation(line: 57, column: 1, scope: !2130)
!2130 = !DILexicalBlockFile(scope: !2128, file: !1, discriminator: 286)
!2131 = !DILocation(line: 57, column: 1, scope: !2132)
!2132 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 287)
!2133 = !DILocation(line: 57, column: 1, scope: !2134)
!2134 = !DILexicalBlockFile(scope: !2082, file: !1, discriminator: 288)
!2135 = !DILocation(line: 57, column: 1, scope: !2136)
!2136 = !DILexicalBlockFile(scope: !2137, file: !1, discriminator: 289)
!2137 = distinct !DILexicalBlock(scope: !2079, file: !1, line: 57, column: 1)
!2138 = !DILocation(line: 57, column: 1, scope: !2139)
!2139 = !DILexicalBlockFile(scope: !2137, file: !1, discriminator: 290)
!2140 = !DILocation(line: 57, column: 1, scope: !2141)
!2141 = !DILexicalBlockFile(scope: !2137, file: !1, discriminator: 291)
!2142 = !DILocation(line: 57, column: 1, scope: !2143)
!2143 = !DILexicalBlockFile(scope: !2137, file: !1, discriminator: 292)
!2144 = !DILocation(line: 57, column: 1, scope: !2145)
!2145 = !DILexicalBlockFile(scope: !2146, file: !1, discriminator: 293)
!2146 = distinct !DILexicalBlock(scope: !2137, file: !1, line: 57, column: 1)
!2147 = !DILocation(line: 57, column: 1, scope: !2148)
!2148 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 294)
!2149 = distinct !DILexicalBlock(scope: !2150, file: !1, line: 57, column: 1)
!2150 = distinct !DILexicalBlock(scope: !2137, file: !1, line: 57, column: 1)
!2151 = !DILocation(line: 57, column: 1, scope: !2152)
!2152 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 295)
!2153 = !DILocalVariable(name: "oright", scope: !2154, file: !1, line: 57, type: !243)
!2154 = distinct !DILexicalBlock(scope: !2149, file: !1, line: 57, column: 1)
!2155 = !DILocation(line: 57, column: 1, scope: !2154)
!2156 = !DILocation(line: 57, column: 1, scope: !2157)
!2157 = !DILexicalBlockFile(scope: !2158, file: !1, discriminator: 296)
!2158 = distinct !DILexicalBlock(scope: !2154, file: !1, line: 57, column: 1)
!2159 = !DILocation(line: 57, column: 1, scope: !2160)
!2160 = !DILexicalBlockFile(scope: !2158, file: !1, discriminator: 297)
!2161 = !DILocation(line: 57, column: 1, scope: !2162)
!2162 = !DILexicalBlockFile(scope: !2154, file: !1, discriminator: 298)
!2163 = !DILocation(line: 57, column: 1, scope: !2164)
!2164 = !DILexicalBlockFile(scope: !2165, file: !1, discriminator: 299)
!2165 = distinct !DILexicalBlock(scope: !2154, file: !1, line: 57, column: 1)
!2166 = !DILocation(line: 57, column: 1, scope: !2167)
!2167 = !DILexicalBlockFile(scope: !2168, file: !1, discriminator: 300)
!2168 = distinct !DILexicalBlock(scope: !2169, file: !1, line: 57, column: 1)
!2169 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 57, column: 1)
!2170 = !DILocation(line: 57, column: 1, scope: !2171)
!2171 = !DILexicalBlockFile(scope: !2165, file: !1, discriminator: 301)
!2172 = !DILocation(line: 57, column: 1, scope: !2173)
!2173 = !DILexicalBlockFile(scope: !2174, file: !1, discriminator: 302)
!2174 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 57, column: 1)
!2175 = !DILocation(line: 57, column: 1, scope: !2176)
!2176 = !DILexicalBlockFile(scope: !2177, file: !1, discriminator: 303)
!2177 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 57, column: 1)
!2178 = !DILocation(line: 57, column: 1, scope: !2179)
!2179 = !DILexicalBlockFile(scope: !2180, file: !1, discriminator: 304)
!2180 = distinct !DILexicalBlock(scope: !2181, file: !1, line: 57, column: 1)
!2181 = distinct !DILexicalBlock(scope: !2177, file: !1, line: 57, column: 1)
!2182 = !DILocation(line: 57, column: 1, scope: !2183)
!2183 = !DILexicalBlockFile(scope: !2180, file: !1, discriminator: 305)
!2184 = !DILocation(line: 57, column: 1, scope: !2185)
!2185 = !DILexicalBlockFile(scope: !2180, file: !1, discriminator: 306)
!2186 = !DILocation(line: 57, column: 1, scope: !2187)
!2187 = !DILexicalBlockFile(scope: !2181, file: !1, discriminator: 307)
!2188 = !DILocation(line: 57, column: 1, scope: !2189)
!2189 = !DILexicalBlockFile(scope: !2177, file: !1, discriminator: 308)
!2190 = !DILocation(line: 57, column: 1, scope: !2191)
!2191 = !DILexicalBlockFile(scope: !2165, file: !1, discriminator: 309)
!2192 = !DILocation(line: 57, column: 1, scope: !2193)
!2193 = !DILexicalBlockFile(scope: !2194, file: !1, discriminator: 310)
!2194 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 57, column: 1)
!2195 = !DILocation(line: 57, column: 1, scope: !2196)
!2196 = !DILexicalBlockFile(scope: !2197, file: !1, discriminator: 311)
!2197 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 57, column: 1)
!2198 = !DILocation(line: 57, column: 1, scope: !2199)
!2199 = !DILexicalBlockFile(scope: !2197, file: !1, discriminator: 312)
!2200 = !DILocation(line: 57, column: 1, scope: !2201)
!2201 = !DILexicalBlockFile(scope: !2202, file: !1, discriminator: 313)
!2202 = distinct !DILexicalBlock(scope: !2197, file: !1, line: 57, column: 1)
!2203 = !DILocation(line: 57, column: 1, scope: !2204)
!2204 = !DILexicalBlockFile(scope: !2202, file: !1, discriminator: 314)
!2205 = !DILocation(line: 57, column: 1, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !2165, file: !1, discriminator: 315)
!2207 = !DILocation(line: 57, column: 1, scope: !2208)
!2208 = !DILexicalBlockFile(scope: !2154, file: !1, discriminator: 316)
!2209 = !DILocation(line: 57, column: 1, scope: !2210)
!2210 = !DILexicalBlockFile(scope: !2150, file: !1, discriminator: 317)
!2211 = !DILocation(line: 57, column: 1, scope: !2212)
!2212 = !DILexicalBlockFile(scope: !2213, file: !1, discriminator: 318)
!2213 = distinct !DILexicalBlock(scope: !2150, file: !1, line: 57, column: 1)
!2214 = !DILocation(line: 57, column: 1, scope: !2215)
!2215 = !DILexicalBlockFile(scope: !2150, file: !1, discriminator: 319)
!2216 = !DILocation(line: 57, column: 1, scope: !2217)
!2217 = !DILexicalBlockFile(scope: !2218, file: !1, discriminator: 320)
!2218 = distinct !DILexicalBlock(scope: !2150, file: !1, line: 57, column: 1)
!2219 = !DILocation(line: 57, column: 1, scope: !2220)
!2220 = !DILexicalBlockFile(scope: !2221, file: !1, discriminator: 321)
!2221 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 57, column: 1)
!2222 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 57, column: 1)
!2223 = !DILocation(line: 57, column: 1, scope: !2224)
!2224 = !DILexicalBlockFile(scope: !2218, file: !1, discriminator: 322)
!2225 = !DILocation(line: 57, column: 1, scope: !2226)
!2226 = !DILexicalBlockFile(scope: !2227, file: !1, discriminator: 323)
!2227 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 57, column: 1)
!2228 = !DILocation(line: 57, column: 1, scope: !2229)
!2229 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 324)
!2230 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 57, column: 1)
!2231 = !DILocation(line: 57, column: 1, scope: !2232)
!2232 = !DILexicalBlockFile(scope: !2233, file: !1, discriminator: 325)
!2233 = distinct !DILexicalBlock(scope: !2234, file: !1, line: 57, column: 1)
!2234 = distinct !DILexicalBlock(scope: !2230, file: !1, line: 57, column: 1)
!2235 = !DILocation(line: 57, column: 1, scope: !2236)
!2236 = !DILexicalBlockFile(scope: !2233, file: !1, discriminator: 326)
!2237 = !DILocation(line: 57, column: 1, scope: !2238)
!2238 = !DILexicalBlockFile(scope: !2233, file: !1, discriminator: 327)
!2239 = !DILocation(line: 57, column: 1, scope: !2240)
!2240 = !DILexicalBlockFile(scope: !2234, file: !1, discriminator: 328)
!2241 = !DILocation(line: 57, column: 1, scope: !2242)
!2242 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 329)
!2243 = !DILocation(line: 57, column: 1, scope: !2244)
!2244 = !DILexicalBlockFile(scope: !2218, file: !1, discriminator: 330)
!2245 = !DILocation(line: 57, column: 1, scope: !2246)
!2246 = !DILexicalBlockFile(scope: !2247, file: !1, discriminator: 331)
!2247 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 57, column: 1)
!2248 = !DILocation(line: 57, column: 1, scope: !2249)
!2249 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 332)
!2250 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 57, column: 1)
!2251 = !DILocation(line: 57, column: 1, scope: !2252)
!2252 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 333)
!2253 = !DILocation(line: 57, column: 1, scope: !2254)
!2254 = !DILexicalBlockFile(scope: !2255, file: !1, discriminator: 334)
!2255 = distinct !DILexicalBlock(scope: !2250, file: !1, line: 57, column: 1)
!2256 = !DILocation(line: 57, column: 1, scope: !2257)
!2257 = !DILexicalBlockFile(scope: !2255, file: !1, discriminator: 335)
!2258 = !DILocation(line: 57, column: 1, scope: !2259)
!2259 = !DILexicalBlockFile(scope: !2218, file: !1, discriminator: 336)
!2260 = !DILocation(line: 57, column: 1, scope: !2261)
!2261 = !DILexicalBlockFile(scope: !2150, file: !1, discriminator: 337)
!2262 = !DILocation(line: 57, column: 1, scope: !2263)
!2263 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 338)
!2264 = !DILocation(line: 57, column: 1, scope: !2265)
!2265 = !DILexicalBlockFile(scope: !2266, file: !1, discriminator: 339)
!2266 = distinct !DILexicalBlock(scope: !351, file: !1, line: 57, column: 1)
!2267 = !DILocation(line: 57, column: 1, scope: !2268)
!2268 = !DILexicalBlockFile(scope: !2266, file: !1, discriminator: 340)
!2269 = !DILocation(line: 57, column: 1, scope: !2270)
!2270 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 341)
