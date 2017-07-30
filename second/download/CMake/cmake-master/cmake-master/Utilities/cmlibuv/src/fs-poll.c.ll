; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/fs-poll.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.uv_stat_t = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t }
%struct.uv_timespec_t = type { i64, i64 }
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
%struct.uv_fs_poll_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i8* }
%union.anon.4 = type { [4 x i8*] }
%struct.poll_ctx = type { %struct.uv_fs_poll_s*, i32, i32, i64, %struct.uv_loop_s*, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)*, %struct.uv_timer_s, %struct.uv_fs_s, %struct.uv_stat_t, [1 x i8] }
%struct.uv_timer_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, void (%struct.uv_timer_s*)*, [3 x i8*], i64, i64, i64 }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_fs_s = type { i8*, i32, [2 x i8*], [4 x i8*], i32, %struct.uv_loop_s*, void (%struct.uv_fs_s*)*, i64, i8*, i8*, %struct.uv_stat_t, i8*, i32, i32, i32, i32, %struct.uv_buf_t*, i64, i32, i32, double, double, %struct.uv__work, [4 x %struct.uv_buf_t] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv__work = type { void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*, %struct.uv_loop_s*, [2 x i8*] }

@.str = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.1 = private unnamed_addr constant [66 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/fs-poll.c\00", align 1
@__PRETTY_FUNCTION__.uv_fs_poll_start = private unnamed_addr constant [80 x i8] c"int uv_fs_poll_start(uv_fs_poll_t *, uv_fs_poll_cb, const char *, unsigned int)\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"ctx != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_poll_stop = private unnamed_addr constant [36 x i8] c"int uv_fs_poll_stop(uv_fs_poll_t *)\00", align 1
@.str.3 = private unnamed_addr constant [33 x i8] c"ctx->parent_handle != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_poll_getpath = private unnamed_addr constant [57 x i8] c"int uv_fs_poll_getpath(uv_fs_poll_t *, char *, size_t *)\00", align 1
@zero_statbuf = internal global %struct.uv_stat_t zeroinitializer, align 8
@__PRETTY_FUNCTION__.timer_cb = private unnamed_addr constant [28 x i8] c"void timer_cb(uv_timer_t *)\00", align 1
@.str.4 = private unnamed_addr constant [36 x i8] c"ctx->parent_handle->poll_ctx == ctx\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_fs_poll_init(%struct.uv_loop_s* %loop, %struct.uv_fs_poll_s* %handle) #0 !dbg !537 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_fs_poll_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !565, metadata !566), !dbg !567
  store %struct.uv_fs_poll_s* %handle, %struct.uv_fs_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_poll_s** %handle.addr, metadata !568, metadata !566), !dbg !569
  br label %do.body, !dbg !570

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !571
  %1 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !571
  %2 = bitcast %struct.uv_fs_poll_s* %1 to %struct.uv_handle_s*, !dbg !571
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !571
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !571
  %3 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !571
  %4 = bitcast %struct.uv_fs_poll_s* %3 to %struct.uv_handle_s*, !dbg !571
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !571
  store i32 4, i32* %type, align 8, !dbg !571
  %5 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !571
  %6 = bitcast %struct.uv_fs_poll_s* %5 to %struct.uv_handle_s*, !dbg !571
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !571
  store i32 8192, i32* %flags, align 8, !dbg !571
  br label %do.body2, !dbg !571

do.body2:                                         ; preds = %do.body
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !574
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 2, !dbg !574
  %8 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !574
  %9 = bitcast %struct.uv_fs_poll_s* %8 to %struct.uv_handle_s*, !dbg !574
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 4, !dbg !574
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !574
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !574
  store [2 x i8*]* %handle_queue, [2 x i8*]** %10, align 8, !dbg !574
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !574
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 2, !dbg !574
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !574
  %12 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !574
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !574
  %14 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !574
  %15 = bitcast %struct.uv_fs_poll_s* %14 to %struct.uv_handle_s*, !dbg !574
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 4, !dbg !574
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !574
  %16 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !574
  store [2 x i8*]* %13, [2 x i8*]** %16, align 8, !dbg !574
  %17 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !574
  %18 = bitcast %struct.uv_fs_poll_s* %17 to %struct.uv_handle_s*, !dbg !574
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !574
  %19 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !574
  %20 = bitcast %struct.uv_fs_poll_s* %19 to %struct.uv_handle_s*, !dbg !574
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 4, !dbg !574
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !574
  %21 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !574
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !574
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !574
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !574
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %23, align 8, !dbg !574
  %24 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !574
  %25 = bitcast %struct.uv_fs_poll_s* %24 to %struct.uv_handle_s*, !dbg !574
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !574
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !574
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 2, !dbg !574
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !574
  %27 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !574
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %27, align 8, !dbg !574
  br label %do.end, !dbg !574

do.end:                                           ; preds = %do.body2
  %28 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !577
  %29 = bitcast %struct.uv_fs_poll_s* %28 to %struct.uv_handle_s*, !dbg !577
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 6, !dbg !577
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !577
  br label %do.end15, !dbg !577

do.end15:                                         ; preds = %do.end
  ret i32 0, !dbg !579
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @uv_fs_poll_start(%struct.uv_fs_poll_s* %handle, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)* %cb, i8* %path, i32 %interval) #0 !dbg !541 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_fs_poll_s*, align 8
  %cb.addr = alloca void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)*, align 8
  %path.addr = alloca i8*, align 8
  %interval.addr = alloca i32, align 4
  %ctx = alloca %struct.poll_ctx*, align 8
  %loop = alloca %struct.uv_loop_s*, align 8
  %len = alloca i64, align 8
  %err = alloca i32, align 4
  store %struct.uv_fs_poll_s* %handle, %struct.uv_fs_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_poll_s** %handle.addr, metadata !580, metadata !566), !dbg !581
  store void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)* %cb, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)** %cb.addr, metadata !582, metadata !566), !dbg !583
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !584, metadata !566), !dbg !585
  store i32 %interval, i32* %interval.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %interval.addr, metadata !586, metadata !566), !dbg !587
  call void @llvm.dbg.declare(metadata %struct.poll_ctx** %ctx, metadata !588, metadata !566), !dbg !589
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop, metadata !590, metadata !566), !dbg !591
  call void @llvm.dbg.declare(metadata i64* %len, metadata !592, metadata !566), !dbg !593
  call void @llvm.dbg.declare(metadata i32* %err, metadata !594, metadata !566), !dbg !595
  %0 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !596
  %flags = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %0, i32 0, i32 7, !dbg !596
  %1 = load i32, i32* %flags, align 8, !dbg !596
  %and = and i32 %1, 16384, !dbg !596
  %cmp = icmp ne i32 %and, 0, !dbg !596
  br i1 %cmp, label %if.then, label %if.end, !dbg !598

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !599
  br label %return, !dbg !599

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !600
  %loop1 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %2, i32 0, i32 1, !dbg !601
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !601
  store %struct.uv_loop_s* %3, %struct.uv_loop_s** %loop, align 8, !dbg !602
  %4 = load i8*, i8** %path.addr, align 8, !dbg !603
  %call = call i64 @strlen(i8* %4) #6, !dbg !604
  store i64 %call, i64* %len, align 8, !dbg !605
  %5 = load i64, i64* %len, align 8, !dbg !606
  %add = add i64 800, %5, !dbg !607
  %call2 = call i8* @uv__calloc(i64 1, i64 %add), !dbg !608
  %6 = bitcast i8* %call2 to %struct.poll_ctx*, !dbg !608
  store %struct.poll_ctx* %6, %struct.poll_ctx** %ctx, align 8, !dbg !609
  %7 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !610
  %cmp3 = icmp eq %struct.poll_ctx* %7, null, !dbg !612
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !613

if.then4:                                         ; preds = %if.end
  store i32 -12, i32* %retval, align 4, !dbg !614
  br label %return, !dbg !614

if.end5:                                          ; preds = %if.end
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !615
  %9 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !616
  %loop6 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %9, i32 0, i32 4, !dbg !617
  store %struct.uv_loop_s* %8, %struct.uv_loop_s** %loop6, align 8, !dbg !618
  %10 = load void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)*, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)** %cb.addr, align 8, !dbg !619
  %11 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !620
  %poll_cb = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %11, i32 0, i32 5, !dbg !621
  store void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)* %10, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)** %poll_cb, align 8, !dbg !622
  %12 = load i32, i32* %interval.addr, align 4, !dbg !623
  %tobool = icmp ne i32 %12, 0, !dbg !623
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !623

cond.true:                                        ; preds = %if.end5
  %13 = load i32, i32* %interval.addr, align 4, !dbg !624
  br label %cond.end, !dbg !626

cond.false:                                       ; preds = %if.end5
  br label %cond.end, !dbg !627

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %13, %cond.true ], [ 1, %cond.false ], !dbg !629
  %14 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !631
  %interval7 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %14, i32 0, i32 2, !dbg !632
  store i32 %cond, i32* %interval7, align 4, !dbg !633
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !634
  %call8 = call i64 @uv_now(%struct.uv_loop_s* %15), !dbg !635
  %16 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !636
  %start_time = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %16, i32 0, i32 3, !dbg !637
  store i64 %call8, i64* %start_time, align 8, !dbg !638
  %17 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !639
  %18 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !640
  %parent_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %18, i32 0, i32 0, !dbg !641
  store %struct.uv_fs_poll_s* %17, %struct.uv_fs_poll_s** %parent_handle, align 8, !dbg !642
  %19 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !643
  %path9 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %19, i32 0, i32 9, !dbg !644
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %path9, i32 0, i32 0, !dbg !645
  %20 = load i8*, i8** %path.addr, align 8, !dbg !646
  %21 = load i64, i64* %len, align 8, !dbg !647
  %add10 = add i64 %21, 1, !dbg !648
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %20, i64 %add10, i32 1, i1 false), !dbg !645
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !649
  %23 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !650
  %timer_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %23, i32 0, i32 6, !dbg !651
  %call11 = call i32 @uv_timer_init(%struct.uv_loop_s* %22, %struct.uv_timer_s* %timer_handle), !dbg !652
  store i32 %call11, i32* %err, align 4, !dbg !653
  %24 = load i32, i32* %err, align 4, !dbg !654
  %cmp12 = icmp slt i32 %24, 0, !dbg !656
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !657

if.then13:                                        ; preds = %cond.end
  br label %error, !dbg !658

if.end14:                                         ; preds = %cond.end
  %25 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !659
  %timer_handle15 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %25, i32 0, i32 6, !dbg !660
  %flags16 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle15, i32 0, i32 7, !dbg !661
  %26 = load i32, i32* %flags16, align 8, !dbg !662
  %or = or i32 %26, 32768, !dbg !662
  store i32 %or, i32* %flags16, align 8, !dbg !662
  br label %do.body, !dbg !663

do.body:                                          ; preds = %if.end14
  %27 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !664
  %timer_handle17 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %27, i32 0, i32 6, !dbg !664
  %flags18 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle17, i32 0, i32 7, !dbg !664
  %28 = load i32, i32* %flags18, align 8, !dbg !664
  %and19 = and i32 %28, 8192, !dbg !664
  %cmp20 = icmp eq i32 %and19, 0, !dbg !664
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !664

if.then21:                                        ; preds = %do.body
  br label %do.end41, !dbg !668

if.end22:                                         ; preds = %do.body
  %29 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !670
  %timer_handle23 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %29, i32 0, i32 6, !dbg !670
  %flags24 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle23, i32 0, i32 7, !dbg !670
  %30 = load i32, i32* %flags24, align 8, !dbg !670
  %and25 = and i32 %30, -8193, !dbg !670
  store i32 %and25, i32* %flags24, align 8, !dbg !670
  %31 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !670
  %timer_handle26 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %31, i32 0, i32 6, !dbg !670
  %flags27 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle26, i32 0, i32 7, !dbg !670
  %32 = load i32, i32* %flags27, align 8, !dbg !670
  %and28 = and i32 %32, 0, !dbg !670
  %cmp29 = icmp ne i32 %and28, 0, !dbg !670
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !670

if.then30:                                        ; preds = %if.end22
  br label %do.end41, !dbg !672

if.end31:                                         ; preds = %if.end22
  %33 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !675
  %timer_handle32 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %33, i32 0, i32 6, !dbg !675
  %flags33 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle32, i32 0, i32 7, !dbg !675
  %34 = load i32, i32* %flags33, align 8, !dbg !675
  %and34 = and i32 %34, 16384, !dbg !675
  %cmp35 = icmp ne i32 %and34, 0, !dbg !675
  br i1 %cmp35, label %if.then36, label %if.end40, !dbg !675

if.then36:                                        ; preds = %if.end31
  br label %do.body37, !dbg !678

do.body37:                                        ; preds = %if.then36
  %35 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !680
  %timer_handle38 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %35, i32 0, i32 6, !dbg !680
  %loop39 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle38, i32 0, i32 1, !dbg !680
  %36 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop39, align 8, !dbg !680
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %36, i32 0, i32 1, !dbg !680
  %37 = load i32, i32* %active_handles, align 8, !dbg !680
  %dec = add i32 %37, -1, !dbg !680
  store i32 %dec, i32* %active_handles, align 8, !dbg !680
  br label %do.end, !dbg !680

do.end:                                           ; preds = %do.body37
  br label %if.end40, !dbg !683

if.end40:                                         ; preds = %do.end, %if.end31
  br label %do.end41, !dbg !685

do.end41:                                         ; preds = %if.end40, %if.then30, %if.then21
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !687
  %39 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !688
  %fs_req = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %39, i32 0, i32 7, !dbg !689
  %40 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !690
  %path42 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %40, i32 0, i32 9, !dbg !691
  %arraydecay43 = getelementptr inbounds [1 x i8], [1 x i8]* %path42, i32 0, i32 0, !dbg !690
  %call44 = call i32 @uv_fs_stat(%struct.uv_loop_s* %38, %struct.uv_fs_s* %fs_req, i8* %arraydecay43, void (%struct.uv_fs_s*)* @poll_cb), !dbg !692
  store i32 %call44, i32* %err, align 4, !dbg !693
  %41 = load i32, i32* %err, align 4, !dbg !694
  %cmp45 = icmp slt i32 %41, 0, !dbg !696
  br i1 %cmp45, label %if.then46, label %if.end47, !dbg !697

if.then46:                                        ; preds = %do.end41
  br label %error, !dbg !698

if.end47:                                         ; preds = %do.end41
  %42 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !699
  %43 = bitcast %struct.poll_ctx* %42 to i8*, !dbg !699
  %44 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !700
  %poll_ctx = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %44, i32 0, i32 8, !dbg !701
  store i8* %43, i8** %poll_ctx, align 8, !dbg !702
  br label %do.body48, !dbg !703

do.body48:                                        ; preds = %if.end47
  %45 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !704
  %flags49 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %45, i32 0, i32 7, !dbg !704
  %46 = load i32, i32* %flags49, align 8, !dbg !704
  %and50 = and i32 %46, 0, !dbg !704
  %cmp51 = icmp eq i32 %and50, 0, !dbg !704
  br i1 %cmp51, label %cond.true52, label %cond.false53, !dbg !704

cond.true52:                                      ; preds = %do.body48
  br label %cond.end54, !dbg !707

cond.false53:                                     ; preds = %do.body48
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 94, i8* getelementptr inbounds ([80 x i8], [80 x i8]* @__PRETTY_FUNCTION__.uv_fs_poll_start, i32 0, i32 0)) #7, !dbg !709
  unreachable, !dbg !709
                                                  ; No predecessors!
  br label %cond.end54, !dbg !711

cond.end54:                                       ; preds = %47, %cond.true52
  %48 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !713
  %flags55 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %48, i32 0, i32 7, !dbg !713
  %49 = load i32, i32* %flags55, align 8, !dbg !713
  %and56 = and i32 %49, 16384, !dbg !713
  %cmp57 = icmp ne i32 %and56, 0, !dbg !713
  br i1 %cmp57, label %if.then58, label %if.end59, !dbg !713

if.then58:                                        ; preds = %cond.end54
  br label %do.end71, !dbg !716

if.end59:                                         ; preds = %cond.end54
  %50 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !718
  %flags60 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %50, i32 0, i32 7, !dbg !718
  %51 = load i32, i32* %flags60, align 8, !dbg !718
  %or61 = or i32 %51, 16384, !dbg !718
  store i32 %or61, i32* %flags60, align 8, !dbg !718
  %52 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !718
  %flags62 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %52, i32 0, i32 7, !dbg !718
  %53 = load i32, i32* %flags62, align 8, !dbg !718
  %and63 = and i32 %53, 8192, !dbg !718
  %cmp64 = icmp ne i32 %and63, 0, !dbg !718
  br i1 %cmp64, label %if.then65, label %if.end70, !dbg !718

if.then65:                                        ; preds = %if.end59
  br label %do.body66, !dbg !720

do.body66:                                        ; preds = %if.then65
  %54 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !723
  %loop67 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %54, i32 0, i32 1, !dbg !723
  %55 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop67, align 8, !dbg !723
  %active_handles68 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %55, i32 0, i32 1, !dbg !723
  %56 = load i32, i32* %active_handles68, align 8, !dbg !723
  %inc = add i32 %56, 1, !dbg !723
  store i32 %inc, i32* %active_handles68, align 8, !dbg !723
  br label %do.end69, !dbg !723

do.end69:                                         ; preds = %do.body66
  br label %if.end70, !dbg !726

if.end70:                                         ; preds = %do.end69, %if.end59
  br label %do.end71, !dbg !728

do.end71:                                         ; preds = %if.end70, %if.then58
  store i32 0, i32* %retval, align 4, !dbg !730
  br label %return, !dbg !730

error:                                            ; preds = %if.then46, %if.then13
  %57 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !731
  %58 = bitcast %struct.poll_ctx* %57 to i8*, !dbg !731
  call void @uv__free(i8* %58), !dbg !732
  %59 = load i32, i32* %err, align 4, !dbg !733
  store i32 %59, i32* %retval, align 4, !dbg !734
  br label %return, !dbg !734

return:                                           ; preds = %error, %do.end71, %if.then4, %if.then
  %60 = load i32, i32* %retval, align 4, !dbg !735
  ret i32 %60, !dbg !735
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

declare i8* @uv__calloc(i64, i64) #3

declare i64 @uv_now(%struct.uv_loop_s*) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @uv_timer_init(%struct.uv_loop_s*, %struct.uv_timer_s*) #3

declare i32 @uv_fs_stat(%struct.uv_loop_s*, %struct.uv_fs_s*, i8*, void (%struct.uv_fs_s*)*) #3

; Function Attrs: nounwind uwtable
define internal void @poll_cb(%struct.uv_fs_s* %req) #0 !dbg !554 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %statbuf = alloca %struct.uv_stat_t*, align 8
  %ctx = alloca %struct.poll_ctx*, align 8
  %interval = alloca i64, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !736, metadata !566), !dbg !737
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %statbuf, metadata !738, metadata !566), !dbg !740
  call void @llvm.dbg.declare(metadata %struct.poll_ctx** %ctx, metadata !741, metadata !566), !dbg !742
  call void @llvm.dbg.declare(metadata i64* %interval, metadata !743, metadata !566), !dbg !744
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !745
  %1 = bitcast %struct.uv_fs_s* %0 to i8*, !dbg !745
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -192, !dbg !745
  %2 = bitcast i8* %add.ptr to %struct.poll_ctx*, !dbg !745
  store %struct.poll_ctx* %2, %struct.poll_ctx** %ctx, align 8, !dbg !746
  %3 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !747
  %parent_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %3, i32 0, i32 0, !dbg !749
  %4 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle, align 8, !dbg !749
  %cmp = icmp eq %struct.uv_fs_poll_s* %4, null, !dbg !750
  br i1 %cmp, label %if.then, label %if.end, !dbg !751

if.then:                                          ; preds = %entry
  %5 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !752
  %timer_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %5, i32 0, i32 6, !dbg !754
  %6 = bitcast %struct.uv_timer_s* %timer_handle to %struct.uv_handle_s*, !dbg !755
  call void @uv_close(%struct.uv_handle_s* %6, void (%struct.uv_handle_s*)* @timer_close_cb), !dbg !756
  %7 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !757
  call void @uv_fs_req_cleanup(%struct.uv_fs_s* %7), !dbg !758
  br label %if.end47, !dbg !759

if.end:                                           ; preds = %entry
  %8 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !760
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %8, i32 0, i32 7, !dbg !762
  %9 = load i64, i64* %result, align 8, !dbg !762
  %cmp1 = icmp ne i64 %9, 0, !dbg !763
  br i1 %cmp1, label %if.then2, label %if.end15, !dbg !764

if.then2:                                         ; preds = %if.end
  %10 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !765
  %busy_polling = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %10, i32 0, i32 1, !dbg !768
  %11 = load i32, i32* %busy_polling, align 8, !dbg !768
  %conv = sext i32 %11 to i64, !dbg !765
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !769
  %result3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 7, !dbg !770
  %13 = load i64, i64* %result3, align 8, !dbg !770
  %cmp4 = icmp ne i64 %conv, %13, !dbg !771
  br i1 %cmp4, label %if.then6, label %if.end14, !dbg !772

if.then6:                                         ; preds = %if.then2
  %14 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !773
  %poll_cb = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %14, i32 0, i32 5, !dbg !775
  %15 = load void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)*, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)** %poll_cb, align 8, !dbg !775
  %16 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !776
  %parent_handle7 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %16, i32 0, i32 0, !dbg !777
  %17 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle7, align 8, !dbg !777
  %18 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !778
  %result8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %18, i32 0, i32 7, !dbg !779
  %19 = load i64, i64* %result8, align 8, !dbg !779
  %conv9 = trunc i64 %19 to i32, !dbg !778
  %20 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !780
  %statbuf10 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %20, i32 0, i32 8, !dbg !781
  call void %15(%struct.uv_fs_poll_s* %17, i32 %conv9, %struct.uv_stat_t* %statbuf10, %struct.uv_stat_t* @zero_statbuf), !dbg !773
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !782
  %result11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 7, !dbg !783
  %22 = load i64, i64* %result11, align 8, !dbg !783
  %conv12 = trunc i64 %22 to i32, !dbg !782
  %23 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !784
  %busy_polling13 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %23, i32 0, i32 1, !dbg !785
  store i32 %conv12, i32* %busy_polling13, align 8, !dbg !786
  br label %if.end14, !dbg !787

if.end14:                                         ; preds = %if.then6, %if.then2
  br label %out, !dbg !788

if.end15:                                         ; preds = %if.end
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !789
  %statbuf16 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 10, !dbg !790
  store %struct.uv_stat_t* %statbuf16, %struct.uv_stat_t** %statbuf, align 8, !dbg !791
  %25 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !792
  %busy_polling17 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %25, i32 0, i32 1, !dbg !794
  %26 = load i32, i32* %busy_polling17, align 8, !dbg !794
  %cmp18 = icmp ne i32 %26, 0, !dbg !795
  br i1 %cmp18, label %if.then20, label %if.end30, !dbg !796

if.then20:                                        ; preds = %if.end15
  %27 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !797
  %busy_polling21 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %27, i32 0, i32 1, !dbg !799
  %28 = load i32, i32* %busy_polling21, align 8, !dbg !799
  %cmp22 = icmp slt i32 %28, 0, !dbg !800
  br i1 %cmp22, label %if.then25, label %lor.lhs.false, !dbg !801

lor.lhs.false:                                    ; preds = %if.then20
  %29 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !802
  %statbuf24 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %29, i32 0, i32 8, !dbg !804
  %30 = load %struct.uv_stat_t*, %struct.uv_stat_t** %statbuf, align 8, !dbg !805
  %call = call i32 @statbuf_eq(%struct.uv_stat_t* %statbuf24, %struct.uv_stat_t* %30), !dbg !806
  %tobool = icmp ne i32 %call, 0, !dbg !806
  br i1 %tobool, label %if.end29, label %if.then25, !dbg !807

if.then25:                                        ; preds = %lor.lhs.false, %if.then20
  %31 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !808
  %poll_cb26 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %31, i32 0, i32 5, !dbg !809
  %32 = load void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)*, void (%struct.uv_fs_poll_s*, i32, %struct.uv_stat_t*, %struct.uv_stat_t*)** %poll_cb26, align 8, !dbg !809
  %33 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !810
  %parent_handle27 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %33, i32 0, i32 0, !dbg !811
  %34 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle27, align 8, !dbg !811
  %35 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !812
  %statbuf28 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %35, i32 0, i32 8, !dbg !813
  %36 = load %struct.uv_stat_t*, %struct.uv_stat_t** %statbuf, align 8, !dbg !814
  call void %32(%struct.uv_fs_poll_s* %34, i32 0, %struct.uv_stat_t* %statbuf28, %struct.uv_stat_t* %36), !dbg !808
  br label %if.end29, !dbg !808

if.end29:                                         ; preds = %if.then25, %lor.lhs.false
  br label %if.end30, !dbg !815

if.end30:                                         ; preds = %if.end29, %if.end15
  %37 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !817
  %statbuf31 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %37, i32 0, i32 8, !dbg !818
  %38 = load %struct.uv_stat_t*, %struct.uv_stat_t** %statbuf, align 8, !dbg !819
  %39 = bitcast %struct.uv_stat_t* %statbuf31 to i8*, !dbg !820
  %40 = bitcast %struct.uv_stat_t* %38 to i8*, !dbg !820
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %39, i8* %40, i64 160, i32 8, i1 false), !dbg !820
  %41 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !821
  %busy_polling32 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %41, i32 0, i32 1, !dbg !822
  store i32 1, i32* %busy_polling32, align 8, !dbg !823
  br label %out, !dbg !821

out:                                              ; preds = %if.end30, %if.end14
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !824
  call void @uv_fs_req_cleanup(%struct.uv_fs_s* %42), !dbg !825
  %43 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !826
  %parent_handle33 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %43, i32 0, i32 0, !dbg !828
  %44 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle33, align 8, !dbg !828
  %cmp34 = icmp eq %struct.uv_fs_poll_s* %44, null, !dbg !829
  br i1 %cmp34, label %if.then36, label %if.end38, !dbg !830

if.then36:                                        ; preds = %out
  %45 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !831
  %timer_handle37 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %45, i32 0, i32 6, !dbg !833
  %46 = bitcast %struct.uv_timer_s* %timer_handle37 to %struct.uv_handle_s*, !dbg !834
  call void @uv_close(%struct.uv_handle_s* %46, void (%struct.uv_handle_s*)* @timer_close_cb), !dbg !835
  br label %if.end47, !dbg !836

if.end38:                                         ; preds = %out
  %47 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !837
  %interval39 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %47, i32 0, i32 2, !dbg !838
  %48 = load i32, i32* %interval39, align 4, !dbg !838
  %conv40 = zext i32 %48 to i64, !dbg !837
  store i64 %conv40, i64* %interval, align 8, !dbg !839
  %49 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !840
  %loop = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %49, i32 0, i32 4, !dbg !841
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !841
  %call41 = call i64 @uv_now(%struct.uv_loop_s* %50), !dbg !842
  %51 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !843
  %start_time = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %51, i32 0, i32 3, !dbg !844
  %52 = load i64, i64* %start_time, align 8, !dbg !844
  %sub = sub i64 %call41, %52, !dbg !845
  %53 = load i64, i64* %interval, align 8, !dbg !846
  %rem = urem i64 %sub, %53, !dbg !847
  %54 = load i64, i64* %interval, align 8, !dbg !848
  %sub42 = sub i64 %54, %rem, !dbg !848
  store i64 %sub42, i64* %interval, align 8, !dbg !848
  %55 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !849
  %timer_handle43 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %55, i32 0, i32 6, !dbg !851
  %56 = load i64, i64* %interval, align 8, !dbg !852
  %call44 = call i32 @uv_timer_start(%struct.uv_timer_s* %timer_handle43, void (%struct.uv_timer_s*)* @timer_cb, i64 %56, i64 0), !dbg !853
  %tobool45 = icmp ne i32 %call44, 0, !dbg !853
  br i1 %tobool45, label %if.then46, label %if.end47, !dbg !854

if.then46:                                        ; preds = %if.end38
  call void @abort() #7, !dbg !855
  unreachable, !dbg !855

if.end47:                                         ; preds = %if.then, %if.then36, %if.end38
  ret void, !dbg !856
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

declare void @uv__free(i8*) #3

; Function Attrs: nounwind uwtable
define i32 @uv_fs_poll_stop(%struct.uv_fs_poll_s* %handle) #0 !dbg !544 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_fs_poll_s*, align 8
  %ctx = alloca %struct.poll_ctx*, align 8
  store %struct.uv_fs_poll_s* %handle, %struct.uv_fs_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_poll_s** %handle.addr, metadata !857, metadata !566), !dbg !858
  call void @llvm.dbg.declare(metadata %struct.poll_ctx** %ctx, metadata !859, metadata !566), !dbg !860
  %0 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !861
  %flags = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %0, i32 0, i32 7, !dbg !861
  %1 = load i32, i32* %flags, align 8, !dbg !861
  %and = and i32 %1, 16384, !dbg !861
  %cmp = icmp ne i32 %and, 0, !dbg !861
  br i1 %cmp, label %if.end, label %if.then, !dbg !863

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !864
  br label %return, !dbg !864

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !865
  %poll_ctx = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %2, i32 0, i32 8, !dbg !866
  %3 = load i8*, i8** %poll_ctx, align 8, !dbg !866
  %4 = bitcast i8* %3 to %struct.poll_ctx*, !dbg !865
  store %struct.poll_ctx* %4, %struct.poll_ctx** %ctx, align 8, !dbg !867
  %5 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !868
  %cmp1 = icmp ne %struct.poll_ctx* %5, null, !dbg !868
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !868

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !869

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 111, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv_fs_poll_stop, i32 0, i32 0)) #7, !dbg !871
  unreachable, !dbg !871
                                                  ; No predecessors!
  br label %cond.end, !dbg !873

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !875
  %parent_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %7, i32 0, i32 0, !dbg !875
  %8 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle, align 8, !dbg !875
  %cmp2 = icmp ne %struct.uv_fs_poll_s* %8, null, !dbg !875
  br i1 %cmp2, label %cond.true3, label %cond.false4, !dbg !875

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !876

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 112, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv_fs_poll_stop, i32 0, i32 0)) #7, !dbg !877
  unreachable, !dbg !877
                                                  ; No predecessors!
  br label %cond.end5, !dbg !878

cond.end5:                                        ; preds = %9, %cond.true3
  %10 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !879
  %parent_handle6 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %10, i32 0, i32 0, !dbg !880
  store %struct.uv_fs_poll_s* null, %struct.uv_fs_poll_s** %parent_handle6, align 8, !dbg !881
  %11 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !882
  %poll_ctx7 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %11, i32 0, i32 8, !dbg !883
  store i8* null, i8** %poll_ctx7, align 8, !dbg !884
  %12 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !885
  %timer_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %12, i32 0, i32 6, !dbg !885
  %flags8 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %timer_handle, i32 0, i32 7, !dbg !885
  %13 = load i32, i32* %flags8, align 8, !dbg !885
  %and9 = and i32 %13, 16384, !dbg !885
  %cmp10 = icmp ne i32 %and9, 0, !dbg !885
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !887

if.then11:                                        ; preds = %cond.end5
  %14 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !888
  %timer_handle12 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %14, i32 0, i32 6, !dbg !889
  %15 = bitcast %struct.uv_timer_s* %timer_handle12 to %struct.uv_handle_s*, !dbg !890
  call void @uv_close(%struct.uv_handle_s* %15, void (%struct.uv_handle_s*)* @timer_close_cb), !dbg !891
  br label %if.end13, !dbg !891

if.end13:                                         ; preds = %if.then11, %cond.end5
  br label %do.body, !dbg !892

do.body:                                          ; preds = %if.end13
  %16 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !893
  %flags14 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %16, i32 0, i32 7, !dbg !893
  %17 = load i32, i32* %flags14, align 8, !dbg !893
  %and15 = and i32 %17, 0, !dbg !893
  %cmp16 = icmp eq i32 %and15, 0, !dbg !893
  br i1 %cmp16, label %cond.true17, label %cond.false18, !dbg !893

cond.true17:                                      ; preds = %do.body
  br label %cond.end19, !dbg !896

cond.false18:                                     ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 122, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv_fs_poll_stop, i32 0, i32 0)) #7, !dbg !898
  unreachable, !dbg !898
                                                  ; No predecessors!
  br label %cond.end19, !dbg !900

cond.end19:                                       ; preds = %18, %cond.true17
  %19 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !902
  %flags20 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %19, i32 0, i32 7, !dbg !902
  %20 = load i32, i32* %flags20, align 8, !dbg !902
  %and21 = and i32 %20, 16384, !dbg !902
  %cmp22 = icmp eq i32 %and21, 0, !dbg !902
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !902

if.then23:                                        ; preds = %cond.end19
  br label %do.end33, !dbg !905

if.end24:                                         ; preds = %cond.end19
  %21 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !907
  %flags25 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %21, i32 0, i32 7, !dbg !907
  %22 = load i32, i32* %flags25, align 8, !dbg !907
  %and26 = and i32 %22, -16385, !dbg !907
  store i32 %and26, i32* %flags25, align 8, !dbg !907
  %23 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !907
  %flags27 = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %23, i32 0, i32 7, !dbg !907
  %24 = load i32, i32* %flags27, align 8, !dbg !907
  %and28 = and i32 %24, 8192, !dbg !907
  %cmp29 = icmp ne i32 %and28, 0, !dbg !907
  br i1 %cmp29, label %if.then30, label %if.end32, !dbg !907

if.then30:                                        ; preds = %if.end24
  br label %do.body31, !dbg !909

do.body31:                                        ; preds = %if.then30
  %25 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !912
  %loop = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %25, i32 0, i32 1, !dbg !912
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !912
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 1, !dbg !912
  %27 = load i32, i32* %active_handles, align 8, !dbg !912
  %dec = add i32 %27, -1, !dbg !912
  store i32 %dec, i32* %active_handles, align 8, !dbg !912
  br label %do.end, !dbg !912

do.end:                                           ; preds = %do.body31
  br label %if.end32, !dbg !915

if.end32:                                         ; preds = %do.end, %if.end24
  br label %do.end33, !dbg !917

do.end33:                                         ; preds = %if.end32, %if.then23
  store i32 0, i32* %retval, align 4, !dbg !919
  br label %return, !dbg !919

return:                                           ; preds = %do.end33, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !920
  ret i32 %28, !dbg !920
}

declare void @uv_close(%struct.uv_handle_s*, void (%struct.uv_handle_s*)*) #3

; Function Attrs: nounwind uwtable
define internal void @timer_close_cb(%struct.uv_handle_s* %handle) #0 !dbg !559 {
entry:
  %handle.addr = alloca %struct.uv_handle_s*, align 8
  store %struct.uv_handle_s* %handle, %struct.uv_handle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_handle_s** %handle.addr, metadata !921, metadata !566), !dbg !922
  %0 = load %struct.uv_handle_s*, %struct.uv_handle_s** %handle.addr, align 8, !dbg !923
  %1 = bitcast %struct.uv_handle_s* %0 to i8*, !dbg !923
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -40, !dbg !923
  %2 = bitcast i8* %add.ptr to %struct.poll_ctx*, !dbg !923
  %3 = bitcast %struct.poll_ctx* %2 to i8*, !dbg !923
  call void @uv__free(i8* %3), !dbg !924
  ret void, !dbg !925
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_poll_getpath(%struct.uv_fs_poll_s* %handle, i8* %buffer, i64* %size) #0 !dbg !547 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_fs_poll_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %ctx = alloca %struct.poll_ctx*, align 8
  %required_len = alloca i64, align 8
  store %struct.uv_fs_poll_s* %handle, %struct.uv_fs_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_poll_s** %handle.addr, metadata !926, metadata !566), !dbg !927
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !928, metadata !566), !dbg !929
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !930, metadata !566), !dbg !931
  call void @llvm.dbg.declare(metadata %struct.poll_ctx** %ctx, metadata !932, metadata !566), !dbg !933
  call void @llvm.dbg.declare(metadata i64* %required_len, metadata !934, metadata !566), !dbg !935
  %0 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !936
  %flags = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %0, i32 0, i32 7, !dbg !936
  %1 = load i32, i32* %flags, align 8, !dbg !936
  %and = and i32 %1, 16384, !dbg !936
  %cmp = icmp ne i32 %and, 0, !dbg !936
  br i1 %cmp, label %if.end, label %if.then, !dbg !938

if.then:                                          ; preds = %entry
  %2 = load i64*, i64** %size.addr, align 8, !dbg !939
  store i64 0, i64* %2, align 8, !dbg !941
  store i32 -22, i32* %retval, align 4, !dbg !942
  br label %return, !dbg !942

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !943
  %poll_ctx = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %3, i32 0, i32 8, !dbg !944
  %4 = load i8*, i8** %poll_ctx, align 8, !dbg !944
  %5 = bitcast i8* %4 to %struct.poll_ctx*, !dbg !943
  store %struct.poll_ctx* %5, %struct.poll_ctx** %ctx, align 8, !dbg !945
  %6 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !946
  %cmp1 = icmp ne %struct.poll_ctx* %6, null, !dbg !946
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !946

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !947

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 138, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv_fs_poll_getpath, i32 0, i32 0)) #7, !dbg !949
  unreachable, !dbg !949
                                                  ; No predecessors!
  br label %cond.end, !dbg !951

cond.end:                                         ; preds = %7, %cond.true
  %8 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !953
  %path = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %8, i32 0, i32 9, !dbg !954
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %path, i32 0, i32 0, !dbg !953
  %call = call i64 @strlen(i8* %arraydecay) #6, !dbg !955
  store i64 %call, i64* %required_len, align 8, !dbg !956
  %9 = load i64, i64* %required_len, align 8, !dbg !957
  %10 = load i64*, i64** %size.addr, align 8, !dbg !959
  %11 = load i64, i64* %10, align 8, !dbg !960
  %cmp2 = icmp uge i64 %9, %11, !dbg !961
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !962

if.then3:                                         ; preds = %cond.end
  %12 = load i64, i64* %required_len, align 8, !dbg !963
  %add = add i64 %12, 1, !dbg !965
  %13 = load i64*, i64** %size.addr, align 8, !dbg !966
  store i64 %add, i64* %13, align 8, !dbg !967
  store i32 -105, i32* %retval, align 4, !dbg !968
  br label %return, !dbg !968

if.end4:                                          ; preds = %cond.end
  %14 = load i8*, i8** %buffer.addr, align 8, !dbg !969
  %15 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !970
  %path5 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %15, i32 0, i32 9, !dbg !971
  %arraydecay6 = getelementptr inbounds [1 x i8], [1 x i8]* %path5, i32 0, i32 0, !dbg !972
  %16 = load i64, i64* %required_len, align 8, !dbg !973
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* %arraydecay6, i64 %16, i32 1, i1 false), !dbg !972
  %17 = load i64, i64* %required_len, align 8, !dbg !974
  %18 = load i64*, i64** %size.addr, align 8, !dbg !975
  store i64 %17, i64* %18, align 8, !dbg !976
  %19 = load i64, i64* %required_len, align 8, !dbg !977
  %20 = load i8*, i8** %buffer.addr, align 8, !dbg !978
  %arrayidx = getelementptr inbounds i8, i8* %20, i64 %19, !dbg !978
  store i8 0, i8* %arrayidx, align 1, !dbg !979
  store i32 0, i32* %retval, align 4, !dbg !980
  br label %return, !dbg !980

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !981
  ret i32 %21, !dbg !981
}

; Function Attrs: nounwind uwtable
define void @uv__fs_poll_close(%struct.uv_fs_poll_s* %handle) #0 !dbg !551 {
entry:
  %handle.addr = alloca %struct.uv_fs_poll_s*, align 8
  store %struct.uv_fs_poll_s* %handle, %struct.uv_fs_poll_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_poll_s** %handle.addr, metadata !982, metadata !566), !dbg !983
  %0 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %handle.addr, align 8, !dbg !984
  %call = call i32 @uv_fs_poll_stop(%struct.uv_fs_poll_s* %0), !dbg !985
  ret void, !dbg !986
}

declare void @uv_fs_req_cleanup(%struct.uv_fs_s*) #3

; Function Attrs: nounwind uwtable
define internal i32 @statbuf_eq(%struct.uv_stat_t* %a, %struct.uv_stat_t* %b) #0 !dbg !555 {
entry:
  %a.addr = alloca %struct.uv_stat_t*, align 8
  %b.addr = alloca %struct.uv_stat_t*, align 8
  store %struct.uv_stat_t* %a, %struct.uv_stat_t** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %a.addr, metadata !987, metadata !566), !dbg !988
  store %struct.uv_stat_t* %b, %struct.uv_stat_t** %b.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %b.addr, metadata !989, metadata !566), !dbg !990
  %0 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !991
  %st_ctim = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %0, i32 0, i32 14, !dbg !992
  %tv_nsec = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_ctim, i32 0, i32 1, !dbg !993
  %1 = load i64, i64* %tv_nsec, align 8, !dbg !993
  %2 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !994
  %st_ctim1 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %2, i32 0, i32 14, !dbg !995
  %tv_nsec2 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_ctim1, i32 0, i32 1, !dbg !996
  %3 = load i64, i64* %tv_nsec2, align 8, !dbg !996
  %cmp = icmp eq i64 %1, %3, !dbg !997
  br i1 %cmp, label %land.lhs.true, label %land.end, !dbg !998

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !999
  %st_mtim = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %4, i32 0, i32 13, !dbg !1001
  %tv_nsec3 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_mtim, i32 0, i32 1, !dbg !1002
  %5 = load i64, i64* %tv_nsec3, align 8, !dbg !1002
  %6 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1003
  %st_mtim4 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %6, i32 0, i32 13, !dbg !1004
  %tv_nsec5 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_mtim4, i32 0, i32 1, !dbg !1005
  %7 = load i64, i64* %tv_nsec5, align 8, !dbg !1005
  %cmp6 = icmp eq i64 %5, %7, !dbg !1006
  br i1 %cmp6, label %land.lhs.true7, label %land.end, !dbg !1007

land.lhs.true7:                                   ; preds = %land.lhs.true
  %8 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1008
  %st_birthtim = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %8, i32 0, i32 15, !dbg !1009
  %tv_nsec8 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_birthtim, i32 0, i32 1, !dbg !1010
  %9 = load i64, i64* %tv_nsec8, align 8, !dbg !1010
  %10 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1011
  %st_birthtim9 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %10, i32 0, i32 15, !dbg !1012
  %tv_nsec10 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_birthtim9, i32 0, i32 1, !dbg !1013
  %11 = load i64, i64* %tv_nsec10, align 8, !dbg !1013
  %cmp11 = icmp eq i64 %9, %11, !dbg !1014
  br i1 %cmp11, label %land.lhs.true12, label %land.end, !dbg !1015

land.lhs.true12:                                  ; preds = %land.lhs.true7
  %12 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1016
  %st_ctim13 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %12, i32 0, i32 14, !dbg !1017
  %tv_sec = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_ctim13, i32 0, i32 0, !dbg !1018
  %13 = load i64, i64* %tv_sec, align 8, !dbg !1018
  %14 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1019
  %st_ctim14 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %14, i32 0, i32 14, !dbg !1020
  %tv_sec15 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_ctim14, i32 0, i32 0, !dbg !1021
  %15 = load i64, i64* %tv_sec15, align 8, !dbg !1021
  %cmp16 = icmp eq i64 %13, %15, !dbg !1022
  br i1 %cmp16, label %land.lhs.true17, label %land.end, !dbg !1023

land.lhs.true17:                                  ; preds = %land.lhs.true12
  %16 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1024
  %st_mtim18 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %16, i32 0, i32 13, !dbg !1025
  %tv_sec19 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_mtim18, i32 0, i32 0, !dbg !1026
  %17 = load i64, i64* %tv_sec19, align 8, !dbg !1026
  %18 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1027
  %st_mtim20 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %18, i32 0, i32 13, !dbg !1028
  %tv_sec21 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_mtim20, i32 0, i32 0, !dbg !1029
  %19 = load i64, i64* %tv_sec21, align 8, !dbg !1029
  %cmp22 = icmp eq i64 %17, %19, !dbg !1030
  br i1 %cmp22, label %land.lhs.true23, label %land.end, !dbg !1031

land.lhs.true23:                                  ; preds = %land.lhs.true17
  %20 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1032
  %st_birthtim24 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %20, i32 0, i32 15, !dbg !1033
  %tv_sec25 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_birthtim24, i32 0, i32 0, !dbg !1034
  %21 = load i64, i64* %tv_sec25, align 8, !dbg !1034
  %22 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1035
  %st_birthtim26 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %22, i32 0, i32 15, !dbg !1036
  %tv_sec27 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_birthtim26, i32 0, i32 0, !dbg !1037
  %23 = load i64, i64* %tv_sec27, align 8, !dbg !1037
  %cmp28 = icmp eq i64 %21, %23, !dbg !1038
  br i1 %cmp28, label %land.lhs.true29, label %land.end, !dbg !1039

land.lhs.true29:                                  ; preds = %land.lhs.true23
  %24 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1040
  %st_size = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %24, i32 0, i32 7, !dbg !1041
  %25 = load i64, i64* %st_size, align 8, !dbg !1041
  %26 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1042
  %st_size30 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %26, i32 0, i32 7, !dbg !1043
  %27 = load i64, i64* %st_size30, align 8, !dbg !1043
  %cmp31 = icmp eq i64 %25, %27, !dbg !1044
  br i1 %cmp31, label %land.lhs.true32, label %land.end, !dbg !1045

land.lhs.true32:                                  ; preds = %land.lhs.true29
  %28 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1046
  %st_mode = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %28, i32 0, i32 1, !dbg !1047
  %29 = load i64, i64* %st_mode, align 8, !dbg !1047
  %30 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1048
  %st_mode33 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %30, i32 0, i32 1, !dbg !1049
  %31 = load i64, i64* %st_mode33, align 8, !dbg !1049
  %cmp34 = icmp eq i64 %29, %31, !dbg !1050
  br i1 %cmp34, label %land.lhs.true35, label %land.end, !dbg !1051

land.lhs.true35:                                  ; preds = %land.lhs.true32
  %32 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1052
  %st_uid = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %32, i32 0, i32 3, !dbg !1053
  %33 = load i64, i64* %st_uid, align 8, !dbg !1053
  %34 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1054
  %st_uid36 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %34, i32 0, i32 3, !dbg !1055
  %35 = load i64, i64* %st_uid36, align 8, !dbg !1055
  %cmp37 = icmp eq i64 %33, %35, !dbg !1056
  br i1 %cmp37, label %land.lhs.true38, label %land.end, !dbg !1057

land.lhs.true38:                                  ; preds = %land.lhs.true35
  %36 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1058
  %st_gid = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %36, i32 0, i32 4, !dbg !1059
  %37 = load i64, i64* %st_gid, align 8, !dbg !1059
  %38 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1060
  %st_gid39 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %38, i32 0, i32 4, !dbg !1061
  %39 = load i64, i64* %st_gid39, align 8, !dbg !1061
  %cmp40 = icmp eq i64 %37, %39, !dbg !1062
  br i1 %cmp40, label %land.lhs.true41, label %land.end, !dbg !1063

land.lhs.true41:                                  ; preds = %land.lhs.true38
  %40 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1064
  %st_ino = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %40, i32 0, i32 6, !dbg !1065
  %41 = load i64, i64* %st_ino, align 8, !dbg !1065
  %42 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1066
  %st_ino42 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %42, i32 0, i32 6, !dbg !1067
  %43 = load i64, i64* %st_ino42, align 8, !dbg !1067
  %cmp43 = icmp eq i64 %41, %43, !dbg !1068
  br i1 %cmp43, label %land.lhs.true44, label %land.end, !dbg !1069

land.lhs.true44:                                  ; preds = %land.lhs.true41
  %44 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1070
  %st_dev = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %44, i32 0, i32 0, !dbg !1071
  %45 = load i64, i64* %st_dev, align 8, !dbg !1071
  %46 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1072
  %st_dev45 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %46, i32 0, i32 0, !dbg !1073
  %47 = load i64, i64* %st_dev45, align 8, !dbg !1073
  %cmp46 = icmp eq i64 %45, %47, !dbg !1074
  br i1 %cmp46, label %land.lhs.true47, label %land.end, !dbg !1075

land.lhs.true47:                                  ; preds = %land.lhs.true44
  %48 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1076
  %st_flags = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %48, i32 0, i32 10, !dbg !1077
  %49 = load i64, i64* %st_flags, align 8, !dbg !1077
  %50 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1078
  %st_flags48 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %50, i32 0, i32 10, !dbg !1079
  %51 = load i64, i64* %st_flags48, align 8, !dbg !1079
  %cmp49 = icmp eq i64 %49, %51, !dbg !1080
  br i1 %cmp49, label %land.rhs, label %land.end, !dbg !1081

land.rhs:                                         ; preds = %land.lhs.true47
  %52 = load %struct.uv_stat_t*, %struct.uv_stat_t** %a.addr, align 8, !dbg !1082
  %st_gen = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %52, i32 0, i32 11, !dbg !1083
  %53 = load i64, i64* %st_gen, align 8, !dbg !1083
  %54 = load %struct.uv_stat_t*, %struct.uv_stat_t** %b.addr, align 8, !dbg !1084
  %st_gen50 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %54, i32 0, i32 11, !dbg !1085
  %55 = load i64, i64* %st_gen50, align 8, !dbg !1085
  %cmp51 = icmp eq i64 %53, %55, !dbg !1086
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true47, %land.lhs.true44, %land.lhs.true41, %land.lhs.true38, %land.lhs.true35, %land.lhs.true32, %land.lhs.true29, %land.lhs.true23, %land.lhs.true17, %land.lhs.true12, %land.lhs.true7, %land.lhs.true, %entry
  %56 = phi i1 [ false, %land.lhs.true47 ], [ false, %land.lhs.true44 ], [ false, %land.lhs.true41 ], [ false, %land.lhs.true38 ], [ false, %land.lhs.true35 ], [ false, %land.lhs.true32 ], [ false, %land.lhs.true29 ], [ false, %land.lhs.true23 ], [ false, %land.lhs.true17 ], [ false, %land.lhs.true12 ], [ false, %land.lhs.true7 ], [ false, %land.lhs.true ], [ false, %entry ], [ %cmp51, %land.rhs ]
  %land.ext = zext i1 %56 to i32, !dbg !1087
  ret i32 %land.ext, !dbg !1089
}

declare i32 @uv_timer_start(%struct.uv_timer_s*, void (%struct.uv_timer_s*)*, i64, i64) #3

; Function Attrs: nounwind uwtable
define internal void @timer_cb(%struct.uv_timer_s* %timer) #0 !dbg !558 {
entry:
  %timer.addr = alloca %struct.uv_timer_s*, align 8
  %ctx = alloca %struct.poll_ctx*, align 8
  store %struct.uv_timer_s* %timer, %struct.uv_timer_s** %timer.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %timer.addr, metadata !1090, metadata !566), !dbg !1091
  call void @llvm.dbg.declare(metadata %struct.poll_ctx** %ctx, metadata !1092, metadata !566), !dbg !1093
  %0 = load %struct.uv_timer_s*, %struct.uv_timer_s** %timer.addr, align 8, !dbg !1094
  %1 = bitcast %struct.uv_timer_s* %0 to i8*, !dbg !1094
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -40, !dbg !1094
  %2 = bitcast i8* %add.ptr to %struct.poll_ctx*, !dbg !1094
  store %struct.poll_ctx* %2, %struct.poll_ctx** %ctx, align 8, !dbg !1095
  %3 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1096
  %parent_handle = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %3, i32 0, i32 0, !dbg !1096
  %4 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle, align 8, !dbg !1096
  %cmp = icmp ne %struct.uv_fs_poll_s* %4, null, !dbg !1096
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1096

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1097

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 163, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.timer_cb, i32 0, i32 0)) #7, !dbg !1099
  unreachable, !dbg !1099
                                                  ; No predecessors!
  br label %cond.end, !dbg !1101

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1103
  %parent_handle1 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %6, i32 0, i32 0, !dbg !1103
  %7 = load %struct.uv_fs_poll_s*, %struct.uv_fs_poll_s** %parent_handle1, align 8, !dbg !1103
  %poll_ctx = getelementptr inbounds %struct.uv_fs_poll_s, %struct.uv_fs_poll_s* %7, i32 0, i32 8, !dbg !1103
  %8 = load i8*, i8** %poll_ctx, align 8, !dbg !1103
  %9 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1103
  %10 = bitcast %struct.poll_ctx* %9 to i8*, !dbg !1103
  %cmp2 = icmp eq i8* %8, %10, !dbg !1103
  br i1 %cmp2, label %cond.true3, label %cond.false4, !dbg !1103

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !1104

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 164, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.timer_cb, i32 0, i32 0)) #7, !dbg !1105
  unreachable, !dbg !1105
                                                  ; No predecessors!
  br label %cond.end5, !dbg !1106

cond.end5:                                        ; preds = %11, %cond.true3
  %12 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1107
  %loop = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %12, i32 0, i32 4, !dbg !1108
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1108
  %call = call i64 @uv_now(%struct.uv_loop_s* %13), !dbg !1109
  %14 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1110
  %start_time = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %14, i32 0, i32 3, !dbg !1111
  store i64 %call, i64* %start_time, align 8, !dbg !1112
  %15 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1113
  %loop6 = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %15, i32 0, i32 4, !dbg !1115
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop6, align 8, !dbg !1115
  %17 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1116
  %fs_req = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %17, i32 0, i32 7, !dbg !1117
  %18 = load %struct.poll_ctx*, %struct.poll_ctx** %ctx, align 8, !dbg !1118
  %path = getelementptr inbounds %struct.poll_ctx, %struct.poll_ctx* %18, i32 0, i32 9, !dbg !1119
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %path, i32 0, i32 0, !dbg !1118
  %call7 = call i32 @uv_fs_stat(%struct.uv_loop_s* %16, %struct.uv_fs_s* %fs_req, i8* %arraydecay, void (%struct.uv_fs_s*)* @poll_cb), !dbg !1120
  %tobool = icmp ne i32 %call7, 0, !dbg !1120
  br i1 %tobool, label %if.then, label %if.end, !dbg !1121

if.then:                                          ; preds = %cond.end5
  call void @abort() #7, !dbg !1122
  unreachable, !dbg !1122

if.end:                                           ; preds = %cond.end5
  ret void, !dbg !1123
}

; Function Attrs: noreturn nounwind
declare void @abort() #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!562, !563}
!llvm.ident = !{!564}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !157, subprograms: !536, globals: !560)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/fs-poll.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !33, !46, !78}
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
!46 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1086, size: 32, align: 32, elements: !47)
!47 = !{!48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77}
!48 = !DIEnumerator(name: "UV_FS_UNKNOWN", value: -1)
!49 = !DIEnumerator(name: "UV_FS_CUSTOM", value: 0)
!50 = !DIEnumerator(name: "UV_FS_OPEN", value: 1)
!51 = !DIEnumerator(name: "UV_FS_CLOSE", value: 2)
!52 = !DIEnumerator(name: "UV_FS_READ", value: 3)
!53 = !DIEnumerator(name: "UV_FS_WRITE", value: 4)
!54 = !DIEnumerator(name: "UV_FS_SENDFILE", value: 5)
!55 = !DIEnumerator(name: "UV_FS_STAT", value: 6)
!56 = !DIEnumerator(name: "UV_FS_LSTAT", value: 7)
!57 = !DIEnumerator(name: "UV_FS_FSTAT", value: 8)
!58 = !DIEnumerator(name: "UV_FS_FTRUNCATE", value: 9)
!59 = !DIEnumerator(name: "UV_FS_UTIME", value: 10)
!60 = !DIEnumerator(name: "UV_FS_FUTIME", value: 11)
!61 = !DIEnumerator(name: "UV_FS_ACCESS", value: 12)
!62 = !DIEnumerator(name: "UV_FS_CHMOD", value: 13)
!63 = !DIEnumerator(name: "UV_FS_FCHMOD", value: 14)
!64 = !DIEnumerator(name: "UV_FS_FSYNC", value: 15)
!65 = !DIEnumerator(name: "UV_FS_FDATASYNC", value: 16)
!66 = !DIEnumerator(name: "UV_FS_UNLINK", value: 17)
!67 = !DIEnumerator(name: "UV_FS_RMDIR", value: 18)
!68 = !DIEnumerator(name: "UV_FS_MKDIR", value: 19)
!69 = !DIEnumerator(name: "UV_FS_MKDTEMP", value: 20)
!70 = !DIEnumerator(name: "UV_FS_RENAME", value: 21)
!71 = !DIEnumerator(name: "UV_FS_SCANDIR", value: 22)
!72 = !DIEnumerator(name: "UV_FS_LINK", value: 23)
!73 = !DIEnumerator(name: "UV_FS_SYMLINK", value: 24)
!74 = !DIEnumerator(name: "UV_FS_READLINK", value: 25)
!75 = !DIEnumerator(name: "UV_FS_CHOWN", value: 26)
!76 = !DIEnumerator(name: "UV_FS_FCHOWN", value: 27)
!77 = !DIEnumerator(name: "UV_FS_REALPATH", value: 28)
!78 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !79)
!79 = !{!80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156}
!80 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!81 = !DIEnumerator(name: "UV_EACCES", value: -13)
!82 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!83 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!84 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!85 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!86 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!87 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!88 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!89 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!90 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!91 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!92 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!93 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!94 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!95 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!96 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!97 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!98 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!99 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!100 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!101 = !DIEnumerator(name: "UV_EBADF", value: -9)
!102 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!103 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!104 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!105 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!106 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!107 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!108 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!109 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!110 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!111 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!112 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!113 = !DIEnumerator(name: "UV_EINTR", value: -4)
!114 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!115 = !DIEnumerator(name: "UV_EIO", value: -5)
!116 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!117 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!118 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!119 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!120 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!121 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!122 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!123 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!124 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!125 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!126 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!127 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!128 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!129 = !DIEnumerator(name: "UV_ENONET", value: -64)
!130 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!131 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!132 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!133 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!134 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!135 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!136 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!137 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!138 = !DIEnumerator(name: "UV_EPERM", value: -1)
!139 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!140 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!141 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!142 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!143 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!144 = !DIEnumerator(name: "UV_EROFS", value: -30)
!145 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!146 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!147 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!148 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!149 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!150 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!151 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!152 = !DIEnumerator(name: "UV_EOF", value: -4095)
!153 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!154 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!155 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!156 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!157 = !{!158, !364, !163, !368, !496}
!158 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !160)
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !161)
!161 = !{!162, !164, !354, !355, !356, !357, !362, !363}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !160, file: !4, line: 426, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !160, file: !4, line: 426, baseType: !165, size: 64, align: 64, offset: 64)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !167)
!167 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !168)
!168 = !{!169, !170, !172, !176, !177, !178, !180, !182, !183, !184, !203, !204, !205, !206, !237, !269, !293, !294, !295, !296, !297, !298, !299, !303, !304, !305, !310, !313, !314, !316, !317, !350, !351, !352, !353}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !167, file: !4, line: 1475, baseType: !163, size: 64, align: 64)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !167, file: !4, line: 1477, baseType: !171, size: 32, align: 32, offset: 64)
!171 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !167, file: !4, line: 1478, baseType: !173, size: 128, align: 64, offset: 128)
!173 = !DICompositeType(tag: DW_TAG_array_type, baseType: !163, size: 128, align: 64, elements: !174)
!174 = !{!175}
!175 = !DISubrange(count: 2)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !167, file: !4, line: 1479, baseType: !173, size: 128, align: 64, offset: 256)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !167, file: !4, line: 1481, baseType: !171, size: 32, align: 32, offset: 384)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !167, file: !4, line: 1482, baseType: !179, size: 64, align: 64, offset: 448)
!179 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !167, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 512)
!181 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 576)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 704)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !167, file: !4, line: 1482, baseType: !185, size: 64, align: 64, offset: 832)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !188, line: 87, baseType: !189)
!188 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!189 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !188, line: 89, size: 448, align: 64, elements: !190)
!190 = !{!191, !198, !199, !200, !201, !202}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !189, file: !188, line: 90, baseType: !192, size: 64, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !188, line: 84, baseType: !193)
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64, align: 64)
!194 = !DISubroutineType(types: !195)
!195 = !{null, !196, !197, !171}
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!197 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !189, file: !188, line: 91, baseType: !173, size: 128, align: 64, offset: 64)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !189, file: !188, line: 92, baseType: !173, size: 128, align: 64, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !189, file: !188, line: 93, baseType: !171, size: 32, align: 32, offset: 320)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !189, file: !188, line: 94, baseType: !171, size: 32, align: 32, offset: 352)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !189, file: !188, line: 95, baseType: !181, size: 32, align: 32, offset: 384)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !167, file: !4, line: 1482, baseType: !171, size: 32, align: 32, offset: 896)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !167, file: !4, line: 1482, baseType: !171, size: 32, align: 32, offset: 928)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 960)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !167, file: !4, line: 1482, baseType: !207, size: 320, align: 64, offset: 1088)
!207 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !188, line: 129, baseType: !208)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !209, line: 127, baseType: !210)
!209 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!210 = !DICompositeType(tag: DW_TAG_union_type, file: !209, line: 90, size: 320, align: 64, elements: !211)
!211 = !{!212, !230, !235}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !210, file: !209, line: 124, baseType: !213, size: 320, align: 64)
!213 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !209, line: 92, size: 320, align: 64, elements: !214)
!214 = !{!215, !216, !217, !218, !219, !220, !222, !223}
!215 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !213, file: !209, line: 94, baseType: !181, size: 32, align: 32)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !213, file: !209, line: 95, baseType: !171, size: 32, align: 32, offset: 32)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !213, file: !209, line: 96, baseType: !181, size: 32, align: 32, offset: 64)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !213, file: !209, line: 98, baseType: !171, size: 32, align: 32, offset: 96)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !213, file: !209, line: 102, baseType: !181, size: 32, align: 32, offset: 128)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !213, file: !209, line: 104, baseType: !221, size: 16, align: 16, offset: 160)
!221 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !213, file: !209, line: 105, baseType: !221, size: 16, align: 16, offset: 176)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !213, file: !209, line: 106, baseType: !224, size: 128, align: 64, offset: 192)
!224 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !209, line: 79, baseType: !225)
!225 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !209, line: 75, size: 128, align: 64, elements: !226)
!226 = !{!227, !229}
!227 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !225, file: !209, line: 77, baseType: !228, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !225, size: 64, align: 64)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !225, file: !209, line: 78, baseType: !228, size: 64, align: 64, offset: 64)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !210, file: !209, line: 125, baseType: !231, size: 320, align: 8)
!231 = !DICompositeType(tag: DW_TAG_array_type, baseType: !232, size: 320, align: 8, elements: !233)
!232 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!233 = !{!234}
!234 = !DISubrange(count: 40)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !210, file: !209, line: 126, baseType: !236, size: 64, align: 64)
!236 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !167, file: !4, line: 1482, baseType: !238, size: 1024, align: 64, offset: 1408)
!238 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !239)
!239 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !240)
!240 = !{!241, !242, !243, !245, !250, !251, !259, !260, !261, !267, !268}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !239, file: !4, line: 768, baseType: !163, size: 64, align: 64)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !239, file: !4, line: 768, baseType: !165, size: 64, align: 64, offset: 64)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !239, file: !4, line: 768, baseType: !244, size: 32, align: 32, offset: 128)
!244 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !239, file: !4, line: 768, baseType: !246, size: 64, align: 64, offset: 192)
!246 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !247)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!248 = !DISubroutineType(types: !249)
!249 = !{null, !158}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !239, file: !4, line: 768, baseType: !173, size: 128, align: 64, offset: 256)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !239, file: !4, line: 768, baseType: !252, size: 256, align: 64, offset: 384)
!252 = !DICompositeType(tag: DW_TAG_union_type, scope: !239, file: !4, line: 768, size: 256, align: 64, elements: !253)
!253 = !{!254, !255}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !252, file: !4, line: 768, baseType: !181, size: 32, align: 32)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !252, file: !4, line: 768, baseType: !256, size: 256, align: 64)
!256 = !DICompositeType(tag: DW_TAG_array_type, baseType: !163, size: 256, align: 64, elements: !257)
!257 = !{!258}
!258 = !DISubrange(count: 4)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !239, file: !4, line: 768, baseType: !158, size: 64, align: 64, offset: 640)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !239, file: !4, line: 768, baseType: !171, size: 32, align: 32, offset: 704)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !239, file: !4, line: 769, baseType: !262, size: 64, align: 64, offset: 768)
!262 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !263)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DISubroutineType(types: !265)
!265 = !{null, !266}
!266 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !238, size: 64, align: 64)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !239, file: !4, line: 769, baseType: !173, size: 128, align: 64, offset: 832)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !239, file: !4, line: 769, baseType: !181, size: 32, align: 32, offset: 960)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !167, file: !4, line: 1482, baseType: !270, size: 448, align: 64, offset: 2432)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !188, line: 130, baseType: !271)
!271 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !209, line: 213, baseType: !272)
!272 = !DICompositeType(tag: DW_TAG_union_type, file: !209, line: 173, size: 448, align: 64, elements: !273)
!273 = !{!274, !288, !292}
!274 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !272, file: !209, line: 192, baseType: !275, size: 448, align: 64)
!275 = !DICompositeType(tag: DW_TAG_structure_type, scope: !272, file: !209, line: 176, size: 448, align: 64, elements: !276)
!276 = !{!277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287}
!277 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !275, file: !209, line: 178, baseType: !181, size: 32, align: 32)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !275, file: !209, line: 179, baseType: !171, size: 32, align: 32, offset: 32)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !275, file: !209, line: 180, baseType: !171, size: 32, align: 32, offset: 64)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !275, file: !209, line: 181, baseType: !171, size: 32, align: 32, offset: 96)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !275, file: !209, line: 182, baseType: !171, size: 32, align: 32, offset: 128)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !275, file: !209, line: 183, baseType: !171, size: 32, align: 32, offset: 160)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !275, file: !209, line: 184, baseType: !181, size: 32, align: 32, offset: 192)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !275, file: !209, line: 185, baseType: !181, size: 32, align: 32, offset: 224)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !275, file: !209, line: 186, baseType: !179, size: 64, align: 64, offset: 256)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !275, file: !209, line: 187, baseType: !179, size: 64, align: 64, offset: 320)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !275, file: !209, line: 190, baseType: !171, size: 32, align: 32, offset: 384)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !272, file: !209, line: 211, baseType: !289, size: 448, align: 8)
!289 = !DICompositeType(tag: DW_TAG_array_type, baseType: !232, size: 448, align: 8, elements: !290)
!290 = !{!291}
!291 = !DISubrange(count: 56)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !272, file: !209, line: 212, baseType: !236, size: 64, align: 64)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !167, file: !4, line: 1482, baseType: !158, size: 64, align: 64, offset: 2880)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 2944)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 3072)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 3200)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 3328)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !167, file: !4, line: 1482, baseType: !173, size: 128, align: 64, offset: 3456)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !167, file: !4, line: 1482, baseType: !300, size: 64, align: 64, offset: 3584)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!301 = !DISubroutineType(types: !302)
!302 = !{null}
!303 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !167, file: !4, line: 1482, baseType: !187, size: 448, align: 64, offset: 3648)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !167, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 4096)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !167, file: !4, line: 1482, baseType: !306, size: 128, align: 64, offset: 4160)
!306 = !DICompositeType(tag: DW_TAG_structure_type, scope: !167, file: !4, line: 1482, size: 128, align: 64, elements: !307)
!307 = !{!308, !309}
!308 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !306, file: !4, line: 1482, baseType: !163, size: 64, align: 64)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !306, file: !4, line: 1482, baseType: !171, size: 32, align: 32, offset: 64)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !167, file: !4, line: 1482, baseType: !311, size: 64, align: 64, offset: 4288)
!311 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !312, line: 55, baseType: !179)
!312 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!313 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !167, file: !4, line: 1482, baseType: !311, size: 64, align: 64, offset: 4352)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !167, file: !4, line: 1482, baseType: !315, size: 64, align: 32, offset: 4416)
!315 = !DICompositeType(tag: DW_TAG_array_type, baseType: !181, size: 64, align: 32, elements: !174)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !167, file: !4, line: 1482, baseType: !187, size: 448, align: 64, offset: 4480)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !167, file: !4, line: 1482, baseType: !318, size: 1216, align: 64, offset: 4928)
!318 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !319)
!319 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !320)
!320 = !{!321, !322, !323, !324, !325, !326, !331, !332, !333, !339, !340, !348, !349}
!321 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !319, file: !4, line: 1326, baseType: !163, size: 64, align: 64)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !319, file: !4, line: 1326, baseType: !165, size: 64, align: 64, offset: 64)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !319, file: !4, line: 1326, baseType: !244, size: 32, align: 32, offset: 128)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !319, file: !4, line: 1326, baseType: !246, size: 64, align: 64, offset: 192)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !319, file: !4, line: 1326, baseType: !173, size: 128, align: 64, offset: 256)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !319, file: !4, line: 1326, baseType: !327, size: 256, align: 64, offset: 384)
!327 = !DICompositeType(tag: DW_TAG_union_type, scope: !319, file: !4, line: 1326, size: 256, align: 64, elements: !328)
!328 = !{!329, !330}
!329 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !327, file: !4, line: 1326, baseType: !181, size: 32, align: 32)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !327, file: !4, line: 1326, baseType: !256, size: 256, align: 64)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !319, file: !4, line: 1326, baseType: !158, size: 64, align: 64, offset: 640)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !319, file: !4, line: 1326, baseType: !171, size: 32, align: 32, offset: 704)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !319, file: !4, line: 1327, baseType: !334, size: 64, align: 64, offset: 768)
!334 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !335)
!335 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !336, size: 64, align: 64)
!336 = !DISubroutineType(types: !337)
!337 = !{null, !338, !181}
!338 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !318, size: 64, align: 64)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !319, file: !4, line: 1328, baseType: !181, size: 32, align: 32, offset: 832)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !319, file: !4, line: 1329, baseType: !341, size: 256, align: 64, offset: 896)
!341 = !DICompositeType(tag: DW_TAG_structure_type, scope: !319, file: !4, line: 1329, size: 256, align: 64, elements: !342)
!342 = !{!343, !345, !346, !347}
!343 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !341, file: !4, line: 1329, baseType: !344, size: 64, align: 64)
!344 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !319, size: 64, align: 64)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !341, file: !4, line: 1329, baseType: !344, size: 64, align: 64, offset: 64)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !341, file: !4, line: 1329, baseType: !344, size: 64, align: 64, offset: 128)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !341, file: !4, line: 1329, baseType: !181, size: 32, align: 32, offset: 192)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !319, file: !4, line: 1329, baseType: !171, size: 32, align: 32, offset: 1152)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !319, file: !4, line: 1329, baseType: !171, size: 32, align: 32, offset: 1184)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !167, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 6144)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !167, file: !4, line: 1482, baseType: !187, size: 448, align: 64, offset: 6208)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !167, file: !4, line: 1482, baseType: !163, size: 64, align: 64, offset: 6656)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !167, file: !4, line: 1482, baseType: !181, size: 32, align: 32, offset: 6720)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !160, file: !4, line: 426, baseType: !244, size: 32, align: 32, offset: 128)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !160, file: !4, line: 426, baseType: !246, size: 64, align: 64, offset: 192)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !160, file: !4, line: 426, baseType: !173, size: 128, align: 64, offset: 256)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !160, file: !4, line: 426, baseType: !358, size: 256, align: 64, offset: 384)
!358 = !DICompositeType(tag: DW_TAG_union_type, scope: !160, file: !4, line: 426, size: 256, align: 64, elements: !359)
!359 = !{!360, !361}
!360 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !358, file: !4, line: 426, baseType: !181, size: 32, align: 32)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !358, file: !4, line: 426, baseType: !256, size: 256, align: 64)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !160, file: !4, line: 426, baseType: !158, size: 64, align: 64, offset: 640)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !160, file: !4, line: 426, baseType: !171, size: 32, align: 32, offset: 704)
!364 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !365, size: 64, align: 64)
!365 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !366, size: 64, align: 64)
!366 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !367, line: 21, baseType: !173)
!367 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!368 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !369, size: 64, align: 64)
!369 = !DICompositeType(tag: DW_TAG_structure_type, name: "poll_ctx", file: !1, line: 29, size: 6400, align: 64, elements: !370)
!370 = !{!371, !389, !390, !391, !392, !393, !424, !453, !531, !532}
!371 = !DIDerivedType(tag: DW_TAG_member, name: "parent_handle", scope: !369, file: !1, line: 30, baseType: !372, size: 64, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !373, size: 64, align: 64)
!373 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_poll_t", file: !4, line: 219, baseType: !374)
!374 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_poll_s", file: !4, line: 1308, size: 832, align: 64, elements: !375)
!375 = !{!376, !377, !378, !379, !380, !381, !386, !387, !388}
!376 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !374, file: !4, line: 1309, baseType: !163, size: 64, align: 64)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !374, file: !4, line: 1309, baseType: !165, size: 64, align: 64, offset: 64)
!378 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !374, file: !4, line: 1309, baseType: !244, size: 32, align: 32, offset: 128)
!379 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !374, file: !4, line: 1309, baseType: !246, size: 64, align: 64, offset: 192)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !374, file: !4, line: 1309, baseType: !173, size: 128, align: 64, offset: 256)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !374, file: !4, line: 1309, baseType: !382, size: 256, align: 64, offset: 384)
!382 = !DICompositeType(tag: DW_TAG_union_type, scope: !374, file: !4, line: 1309, size: 256, align: 64, elements: !383)
!383 = !{!384, !385}
!384 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !382, file: !4, line: 1309, baseType: !181, size: 32, align: 32)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !382, file: !4, line: 1309, baseType: !256, size: 256, align: 64)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !374, file: !4, line: 1309, baseType: !158, size: 64, align: 64, offset: 640)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !374, file: !4, line: 1309, baseType: !171, size: 32, align: 32, offset: 704)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "poll_ctx", scope: !374, file: !4, line: 1311, baseType: !163, size: 64, align: 64, offset: 768)
!389 = !DIDerivedType(tag: DW_TAG_member, name: "busy_polling", scope: !369, file: !1, line: 31, baseType: !181, size: 32, align: 32, offset: 64)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "interval", scope: !369, file: !1, line: 32, baseType: !171, size: 32, align: 32, offset: 96)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "start_time", scope: !369, file: !1, line: 33, baseType: !311, size: 64, align: 64, offset: 128)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !369, file: !1, line: 34, baseType: !165, size: 64, align: 64, offset: 192)
!393 = !DIDerivedType(tag: DW_TAG_member, name: "poll_cb", scope: !369, file: !1, line: 35, baseType: !394, size: 64, align: 64, offset: 256)
!394 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_poll_cb", file: !4, line: 357, baseType: !395)
!395 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !396, size: 64, align: 64)
!396 = !DISubroutineType(types: !397)
!397 = !{null, !372, !181, !398, !398}
!398 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !399, size: 64, align: 64)
!399 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !400)
!400 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stat_t", file: !4, line: 349, baseType: !401)
!401 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 332, size: 1280, align: 64, elements: !402)
!402 = !{!403, !404, !405, !406, !407, !408, !409, !410, !411, !412, !413, !414, !415, !421, !422, !423}
!403 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !401, file: !4, line: 333, baseType: !311, size: 64, align: 64)
!404 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !401, file: !4, line: 334, baseType: !311, size: 64, align: 64, offset: 64)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !401, file: !4, line: 335, baseType: !311, size: 64, align: 64, offset: 128)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !401, file: !4, line: 336, baseType: !311, size: 64, align: 64, offset: 192)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !401, file: !4, line: 337, baseType: !311, size: 64, align: 64, offset: 256)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !401, file: !4, line: 338, baseType: !311, size: 64, align: 64, offset: 320)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !401, file: !4, line: 339, baseType: !311, size: 64, align: 64, offset: 384)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !401, file: !4, line: 340, baseType: !311, size: 64, align: 64, offset: 448)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !401, file: !4, line: 341, baseType: !311, size: 64, align: 64, offset: 512)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !401, file: !4, line: 342, baseType: !311, size: 64, align: 64, offset: 576)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "st_flags", scope: !401, file: !4, line: 343, baseType: !311, size: 64, align: 64, offset: 640)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "st_gen", scope: !401, file: !4, line: 344, baseType: !311, size: 64, align: 64, offset: 704)
!415 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !401, file: !4, line: 345, baseType: !416, size: 128, align: 64, offset: 768)
!416 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timespec_t", file: !4, line: 329, baseType: !417)
!417 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 326, size: 128, align: 64, elements: !418)
!418 = !{!419, !420}
!419 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !417, file: !4, line: 327, baseType: !236, size: 64, align: 64)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !417, file: !4, line: 328, baseType: !236, size: 64, align: 64, offset: 64)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !401, file: !4, line: 346, baseType: !416, size: 128, align: 64, offset: 896)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !401, file: !4, line: 347, baseType: !416, size: 128, align: 64, offset: 1024)
!423 = !DIDerivedType(tag: DW_TAG_member, name: "st_birthtim", scope: !401, file: !4, line: 348, baseType: !416, size: 128, align: 64, offset: 1152)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "timer_handle", scope: !369, file: !1, line: 36, baseType: !425, size: 1216, align: 64, offset: 320)
!425 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timer_t", file: !4, line: 212, baseType: !426)
!426 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_timer_s", file: !4, line: 783, size: 1216, align: 64, elements: !427)
!427 = !{!428, !429, !430, !431, !432, !433, !438, !439, !440, !446, !450, !451, !452}
!428 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !426, file: !4, line: 784, baseType: !163, size: 64, align: 64)
!429 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !426, file: !4, line: 784, baseType: !165, size: 64, align: 64, offset: 64)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !426, file: !4, line: 784, baseType: !244, size: 32, align: 32, offset: 128)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !426, file: !4, line: 784, baseType: !246, size: 64, align: 64, offset: 192)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !426, file: !4, line: 784, baseType: !173, size: 128, align: 64, offset: 256)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !426, file: !4, line: 784, baseType: !434, size: 256, align: 64, offset: 384)
!434 = !DICompositeType(tag: DW_TAG_union_type, scope: !426, file: !4, line: 784, size: 256, align: 64, elements: !435)
!435 = !{!436, !437}
!436 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !434, file: !4, line: 784, baseType: !181, size: 32, align: 32)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !434, file: !4, line: 784, baseType: !256, size: 256, align: 64)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !426, file: !4, line: 784, baseType: !158, size: 64, align: 64, offset: 640)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !426, file: !4, line: 784, baseType: !171, size: 32, align: 32, offset: 704)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !426, file: !4, line: 785, baseType: !441, size: 64, align: 64, offset: 768)
!441 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timer_cb", file: !4, line: 308, baseType: !442)
!442 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !443, size: 64, align: 64)
!443 = !DISubroutineType(types: !444)
!444 = !{null, !445}
!445 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !425, size: 64, align: 64)
!446 = !DIDerivedType(tag: DW_TAG_member, name: "heap_node", scope: !426, file: !4, line: 785, baseType: !447, size: 192, align: 64, offset: 832)
!447 = !DICompositeType(tag: DW_TAG_array_type, baseType: !163, size: 192, align: 64, elements: !448)
!448 = !{!449}
!449 = !DISubrange(count: 3)
!450 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !426, file: !4, line: 785, baseType: !311, size: 64, align: 64, offset: 1024)
!451 = !DIDerivedType(tag: DW_TAG_member, name: "repeat", scope: !426, file: !4, line: 785, baseType: !311, size: 64, align: 64, offset: 1088)
!452 = !DIDerivedType(tag: DW_TAG_member, name: "start_id", scope: !426, file: !4, line: 785, baseType: !311, size: 64, align: 64, offset: 1152)
!453 = !DIDerivedType(tag: DW_TAG_member, name: "fs_req", scope: !369, file: !1, line: 37, baseType: !454, size: 3520, align: 64, offset: 1536)
!454 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_t", file: !4, line: 230, baseType: !455)
!455 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_s", file: !4, line: 1120, size: 3520, align: 64, elements: !456)
!456 = !{!457, !458, !460, !461, !462, !464, !465, !471, !476, !477, !480, !481, !482, !484, !485, !489, !490, !500, !503, !507, !511, !513, !514, !529}
!457 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !455, file: !4, line: 1121, baseType: !163, size: 64, align: 64)
!458 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !455, file: !4, line: 1121, baseType: !459, size: 32, align: 32, offset: 64)
!459 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !33)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !455, file: !4, line: 1121, baseType: !173, size: 128, align: 64, offset: 128)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !455, file: !4, line: 1121, baseType: !256, size: 256, align: 64, offset: 256)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "fs_type", scope: !455, file: !4, line: 1122, baseType: !463, size: 32, align: 32, offset: 512)
!463 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_type", file: !4, line: 1117, baseType: !46)
!464 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !455, file: !4, line: 1123, baseType: !165, size: 64, align: 64, offset: 576)
!465 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !455, file: !4, line: 1124, baseType: !466, size: 64, align: 64, offset: 640)
!466 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_cb", file: !4, line: 315, baseType: !467)
!467 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !468, size: 64, align: 64)
!468 = !DISubroutineType(types: !469)
!469 = !{null, !470}
!470 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !454, size: 64, align: 64)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !455, file: !4, line: 1125, baseType: !472, size: 64, align: 64, offset: 704)
!472 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !473, line: 102, baseType: !474)
!473 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!474 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !475, line: 172, baseType: !236)
!475 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!476 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !455, file: !4, line: 1126, baseType: !163, size: 64, align: 64, offset: 768)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !455, file: !4, line: 1127, baseType: !478, size: 64, align: 64, offset: 832)
!478 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !479, size: 64, align: 64)
!479 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !232)
!480 = !DIDerivedType(tag: DW_TAG_member, name: "statbuf", scope: !455, file: !4, line: 1128, baseType: !400, size: 1280, align: 64, offset: 896)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "new_path", scope: !455, file: !4, line: 1129, baseType: !478, size: 64, align: 64, offset: 2176)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !455, file: !4, line: 1129, baseType: !483, size: 32, align: 32, offset: 2240)
!483 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_file", file: !188, line: 121, baseType: !181)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !455, file: !4, line: 1129, baseType: !181, size: 32, align: 32, offset: 2272)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !455, file: !4, line: 1129, baseType: !486, size: 32, align: 32, offset: 2304)
!486 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !487, line: 70, baseType: !488)
!487 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!488 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !475, line: 129, baseType: !171)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !455, file: !4, line: 1129, baseType: !171, size: 32, align: 32, offset: 2336)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !455, file: !4, line: 1129, baseType: !491, size: 64, align: 64, offset: 2368)
!491 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !492, size: 64, align: 64)
!492 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !188, line: 119, baseType: !493)
!493 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !188, line: 116, size: 128, align: 64, elements: !494)
!494 = !{!495, !497}
!495 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !493, file: !188, line: 117, baseType: !496, size: 64, align: 64)
!496 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !232, size: 64, align: 64)
!497 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !493, file: !188, line: 118, baseType: !498, size: 64, align: 64, offset: 64)
!498 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !499, line: 62, baseType: !179)
!499 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!500 = !DIDerivedType(tag: DW_TAG_member, name: "off", scope: !455, file: !4, line: 1129, baseType: !501, size: 64, align: 64, offset: 2432)
!501 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !473, line: 92, baseType: !502)
!502 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !475, line: 132, baseType: !236)
!503 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !455, file: !4, line: 1129, baseType: !504, size: 32, align: 32, offset: 2496)
!504 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_uid_t", file: !188, line: 139, baseType: !505)
!505 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !487, line: 80, baseType: !506)
!506 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !475, line: 125, baseType: !171)
!507 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !455, file: !4, line: 1129, baseType: !508, size: 32, align: 32, offset: 2528)
!508 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_gid_t", file: !188, line: 138, baseType: !509)
!509 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !487, line: 65, baseType: !510)
!510 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !475, line: 126, baseType: !171)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !455, file: !4, line: 1129, baseType: !512, size: 64, align: 64, offset: 2560)
!512 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !455, file: !4, line: 1129, baseType: !512, size: 64, align: 64, offset: 2624)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !455, file: !4, line: 1129, baseType: !515, size: 320, align: 64, offset: 2688)
!515 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__work", file: !516, line: 30, size: 320, align: 64, elements: !517)
!516 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-threadpool.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!517 = !{!518, !523, !527, !528}
!518 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !515, file: !516, line: 31, baseType: !519, size: 64, align: 64)
!519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !520, size: 64, align: 64)
!520 = !DISubroutineType(types: !521)
!521 = !{null, !522}
!522 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !515, size: 64, align: 64)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !515, file: !516, line: 32, baseType: !524, size: 64, align: 64, offset: 64)
!524 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !525, size: 64, align: 64)
!525 = !DISubroutineType(types: !526)
!526 = !{null, !522, !181}
!527 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !515, file: !516, line: 33, baseType: !196, size: 64, align: 64, offset: 128)
!528 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !515, file: !516, line: 34, baseType: !173, size: 128, align: 64, offset: 192)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !455, file: !4, line: 1129, baseType: !530, size: 512, align: 64, offset: 3008)
!530 = !DICompositeType(tag: DW_TAG_array_type, baseType: !492, size: 512, align: 64, elements: !257)
!531 = !DIDerivedType(tag: DW_TAG_member, name: "statbuf", scope: !369, file: !1, line: 38, baseType: !400, size: 1280, align: 64, offset: 5056)
!532 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !369, file: !1, line: 39, baseType: !533, size: 8, align: 8, offset: 6336)
!533 = !DICompositeType(tag: DW_TAG_array_type, baseType: !232, size: 8, align: 8, elements: !534)
!534 = !{!535}
!535 = !DISubrange(count: 1)
!536 = !{!537, !541, !544, !547, !551, !554, !555, !558, !559}
!537 = distinct !DISubprogram(name: "uv_fs_poll_init", scope: !1, file: !1, line: 50, type: !538, isLocal: false, isDefinition: true, scopeLine: 50, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!538 = !DISubroutineType(types: !539)
!539 = !{!181, !165, !372}
!540 = !{}
!541 = distinct !DISubprogram(name: "uv_fs_poll_start", scope: !1, file: !1, line: 56, type: !542, isLocal: false, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!542 = !DISubroutineType(types: !543)
!543 = !{!181, !372, !394, !478, !171}
!544 = distinct !DISubprogram(name: "uv_fs_poll_stop", scope: !1, file: !1, line: 104, type: !545, isLocal: false, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!545 = !DISubroutineType(types: !546)
!546 = !{!181, !372}
!547 = distinct !DISubprogram(name: "uv_fs_poll_getpath", scope: !1, file: !1, line: 128, type: !548, isLocal: false, isDefinition: true, scopeLine: 128, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!548 = !DISubroutineType(types: !549)
!549 = !{!181, !372, !496, !550}
!550 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !498, size: 64, align: 64)
!551 = distinct !DISubprogram(name: "uv__fs_poll_close", scope: !1, file: !1, line: 154, type: !552, isLocal: false, isDefinition: true, scopeLine: 154, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!552 = !DISubroutineType(types: !553)
!553 = !{null, !372}
!554 = distinct !DISubprogram(name: "poll_cb", scope: !1, file: !1, line: 172, type: !468, isLocal: true, isDefinition: true, scopeLine: 172, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!555 = distinct !DISubprogram(name: "statbuf_eq", scope: !1, file: !1, line: 227, type: !556, isLocal: true, isDefinition: true, scopeLine: 227, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!556 = !DISubroutineType(types: !557)
!557 = !{!181, !398, !398}
!558 = distinct !DISubprogram(name: "timer_cb", scope: !1, file: !1, line: 159, type: !443, isLocal: true, isDefinition: true, scopeLine: 159, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!559 = distinct !DISubprogram(name: "timer_close_cb", scope: !1, file: !1, line: 222, type: !248, isLocal: true, isDefinition: true, scopeLine: 222, flags: DIFlagPrototyped, isOptimized: false, variables: !540)
!560 = !{!561}
!561 = !DIGlobalVariable(name: "zero_statbuf", scope: !0, file: !1, line: 47, type: !400, isLocal: true, isDefinition: true, variable: %struct.uv_stat_t* @zero_statbuf)
!562 = !{i32 2, !"Dwarf Version", i32 4}
!563 = !{i32 2, !"Debug Info Version", i32 3}
!564 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!565 = !DILocalVariable(name: "loop", arg: 1, scope: !537, file: !1, line: 50, type: !165)
!566 = !DIExpression()
!567 = !DILocation(line: 50, column: 32, scope: !537)
!568 = !DILocalVariable(name: "handle", arg: 2, scope: !537, file: !1, line: 50, type: !372)
!569 = !DILocation(line: 50, column: 52, scope: !537)
!570 = !DILocation(line: 51, column: 3, scope: !537)
!571 = !DILocation(line: 51, column: 3, scope: !572)
!572 = !DILexicalBlockFile(scope: !573, file: !1, discriminator: 1)
!573 = distinct !DILexicalBlock(scope: !537, file: !1, line: 51, column: 3)
!574 = !DILocation(line: 51, column: 3, scope: !575)
!575 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 2)
!576 = distinct !DILexicalBlock(scope: !573, file: !1, line: 51, column: 3)
!577 = !DILocation(line: 51, column: 3, scope: !578)
!578 = !DILexicalBlockFile(scope: !573, file: !1, discriminator: 3)
!579 = !DILocation(line: 52, column: 3, scope: !537)
!580 = !DILocalVariable(name: "handle", arg: 1, scope: !541, file: !1, line: 56, type: !372)
!581 = !DILocation(line: 56, column: 36, scope: !541)
!582 = !DILocalVariable(name: "cb", arg: 2, scope: !541, file: !1, line: 57, type: !394)
!583 = !DILocation(line: 57, column: 36, scope: !541)
!584 = !DILocalVariable(name: "path", arg: 3, scope: !541, file: !1, line: 58, type: !478)
!585 = !DILocation(line: 58, column: 34, scope: !541)
!586 = !DILocalVariable(name: "interval", arg: 4, scope: !541, file: !1, line: 59, type: !171)
!587 = !DILocation(line: 59, column: 35, scope: !541)
!588 = !DILocalVariable(name: "ctx", scope: !541, file: !1, line: 60, type: !368)
!589 = !DILocation(line: 60, column: 20, scope: !541)
!590 = !DILocalVariable(name: "loop", scope: !541, file: !1, line: 61, type: !165)
!591 = !DILocation(line: 61, column: 14, scope: !541)
!592 = !DILocalVariable(name: "len", scope: !541, file: !1, line: 62, type: !498)
!593 = !DILocation(line: 62, column: 10, scope: !541)
!594 = !DILocalVariable(name: "err", scope: !541, file: !1, line: 63, type: !181)
!595 = !DILocation(line: 63, column: 7, scope: !541)
!596 = !DILocation(line: 65, column: 7, scope: !597)
!597 = distinct !DILexicalBlock(scope: !541, file: !1, line: 65, column: 7)
!598 = !DILocation(line: 65, column: 7, scope: !541)
!599 = !DILocation(line: 66, column: 5, scope: !597)
!600 = !DILocation(line: 68, column: 10, scope: !541)
!601 = !DILocation(line: 68, column: 18, scope: !541)
!602 = !DILocation(line: 68, column: 8, scope: !541)
!603 = !DILocation(line: 69, column: 16, scope: !541)
!604 = !DILocation(line: 69, column: 9, scope: !541)
!605 = !DILocation(line: 69, column: 7, scope: !541)
!606 = !DILocation(line: 70, column: 38, scope: !541)
!607 = !DILocation(line: 70, column: 36, scope: !541)
!608 = !DILocation(line: 70, column: 9, scope: !541)
!609 = !DILocation(line: 70, column: 7, scope: !541)
!610 = !DILocation(line: 72, column: 7, scope: !611)
!611 = distinct !DILexicalBlock(scope: !541, file: !1, line: 72, column: 7)
!612 = !DILocation(line: 72, column: 11, scope: !611)
!613 = !DILocation(line: 72, column: 7, scope: !541)
!614 = !DILocation(line: 73, column: 5, scope: !611)
!615 = !DILocation(line: 75, column: 15, scope: !541)
!616 = !DILocation(line: 75, column: 3, scope: !541)
!617 = !DILocation(line: 75, column: 8, scope: !541)
!618 = !DILocation(line: 75, column: 13, scope: !541)
!619 = !DILocation(line: 76, column: 18, scope: !541)
!620 = !DILocation(line: 76, column: 3, scope: !541)
!621 = !DILocation(line: 76, column: 8, scope: !541)
!622 = !DILocation(line: 76, column: 16, scope: !541)
!623 = !DILocation(line: 77, column: 19, scope: !541)
!624 = !DILocation(line: 77, column: 30, scope: !625)
!625 = !DILexicalBlockFile(scope: !541, file: !1, discriminator: 1)
!626 = !DILocation(line: 77, column: 19, scope: !625)
!627 = !DILocation(line: 77, column: 19, scope: !628)
!628 = !DILexicalBlockFile(scope: !541, file: !1, discriminator: 2)
!629 = !DILocation(line: 77, column: 19, scope: !630)
!630 = !DILexicalBlockFile(scope: !541, file: !1, discriminator: 3)
!631 = !DILocation(line: 77, column: 3, scope: !630)
!632 = !DILocation(line: 77, column: 8, scope: !630)
!633 = !DILocation(line: 77, column: 17, scope: !630)
!634 = !DILocation(line: 78, column: 28, scope: !541)
!635 = !DILocation(line: 78, column: 21, scope: !541)
!636 = !DILocation(line: 78, column: 3, scope: !541)
!637 = !DILocation(line: 78, column: 8, scope: !541)
!638 = !DILocation(line: 78, column: 19, scope: !541)
!639 = !DILocation(line: 79, column: 24, scope: !541)
!640 = !DILocation(line: 79, column: 3, scope: !541)
!641 = !DILocation(line: 79, column: 8, scope: !541)
!642 = !DILocation(line: 79, column: 22, scope: !541)
!643 = !DILocation(line: 80, column: 10, scope: !541)
!644 = !DILocation(line: 80, column: 15, scope: !541)
!645 = !DILocation(line: 80, column: 3, scope: !541)
!646 = !DILocation(line: 80, column: 21, scope: !541)
!647 = !DILocation(line: 80, column: 27, scope: !541)
!648 = !DILocation(line: 80, column: 31, scope: !541)
!649 = !DILocation(line: 82, column: 23, scope: !541)
!650 = !DILocation(line: 82, column: 30, scope: !541)
!651 = !DILocation(line: 82, column: 35, scope: !541)
!652 = !DILocation(line: 82, column: 9, scope: !541)
!653 = !DILocation(line: 82, column: 7, scope: !541)
!654 = !DILocation(line: 83, column: 7, scope: !655)
!655 = distinct !DILexicalBlock(scope: !541, file: !1, line: 83, column: 7)
!656 = !DILocation(line: 83, column: 11, scope: !655)
!657 = !DILocation(line: 83, column: 7, scope: !541)
!658 = !DILocation(line: 84, column: 5, scope: !655)
!659 = !DILocation(line: 86, column: 3, scope: !541)
!660 = !DILocation(line: 86, column: 8, scope: !541)
!661 = !DILocation(line: 86, column: 21, scope: !541)
!662 = !DILocation(line: 86, column: 27, scope: !541)
!663 = !DILocation(line: 87, column: 3, scope: !541)
!664 = !DILocation(line: 87, column: 3, scope: !665)
!665 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 1)
!666 = distinct !DILexicalBlock(scope: !667, file: !1, line: 87, column: 3)
!667 = distinct !DILexicalBlock(scope: !541, file: !1, line: 87, column: 3)
!668 = !DILocation(line: 87, column: 3, scope: !669)
!669 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 2)
!670 = !DILocation(line: 87, column: 3, scope: !671)
!671 = !DILexicalBlockFile(scope: !667, file: !1, discriminator: 3)
!672 = !DILocation(line: 87, column: 3, scope: !673)
!673 = !DILexicalBlockFile(scope: !674, file: !1, discriminator: 4)
!674 = distinct !DILexicalBlock(scope: !667, file: !1, line: 87, column: 3)
!675 = !DILocation(line: 87, column: 3, scope: !676)
!676 = !DILexicalBlockFile(scope: !677, file: !1, discriminator: 5)
!677 = distinct !DILexicalBlock(scope: !667, file: !1, line: 87, column: 3)
!678 = !DILocation(line: 87, column: 3, scope: !679)
!679 = !DILexicalBlockFile(scope: !677, file: !1, discriminator: 6)
!680 = !DILocation(line: 87, column: 3, scope: !681)
!681 = !DILexicalBlockFile(scope: !682, file: !1, discriminator: 7)
!682 = distinct !DILexicalBlock(scope: !677, file: !1, line: 87, column: 3)
!683 = !DILocation(line: 87, column: 3, scope: !684)
!684 = !DILexicalBlockFile(scope: !682, file: !1, discriminator: 8)
!685 = !DILocation(line: 87, column: 3, scope: !686)
!686 = !DILexicalBlockFile(scope: !667, file: !1, discriminator: 9)
!687 = !DILocation(line: 89, column: 20, scope: !541)
!688 = !DILocation(line: 89, column: 27, scope: !541)
!689 = !DILocation(line: 89, column: 32, scope: !541)
!690 = !DILocation(line: 89, column: 40, scope: !541)
!691 = !DILocation(line: 89, column: 45, scope: !541)
!692 = !DILocation(line: 89, column: 9, scope: !541)
!693 = !DILocation(line: 89, column: 7, scope: !541)
!694 = !DILocation(line: 90, column: 7, scope: !695)
!695 = distinct !DILexicalBlock(scope: !541, file: !1, line: 90, column: 7)
!696 = !DILocation(line: 90, column: 11, scope: !695)
!697 = !DILocation(line: 90, column: 7, scope: !541)
!698 = !DILocation(line: 91, column: 5, scope: !695)
!699 = !DILocation(line: 93, column: 22, scope: !541)
!700 = !DILocation(line: 93, column: 3, scope: !541)
!701 = !DILocation(line: 93, column: 11, scope: !541)
!702 = !DILocation(line: 93, column: 20, scope: !541)
!703 = !DILocation(line: 94, column: 3, scope: !541)
!704 = !DILocation(line: 94, column: 3, scope: !705)
!705 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 1)
!706 = distinct !DILexicalBlock(scope: !541, file: !1, line: 94, column: 3)
!707 = !DILocation(line: 94, column: 3, scope: !708)
!708 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 2)
!709 = !DILocation(line: 94, column: 3, scope: !710)
!710 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 3)
!711 = !DILocation(line: 94, column: 3, scope: !712)
!712 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 4)
!713 = !DILocation(line: 94, column: 3, scope: !714)
!714 = !DILexicalBlockFile(scope: !715, file: !1, discriminator: 5)
!715 = distinct !DILexicalBlock(scope: !706, file: !1, line: 94, column: 3)
!716 = !DILocation(line: 94, column: 3, scope: !717)
!717 = !DILexicalBlockFile(scope: !715, file: !1, discriminator: 6)
!718 = !DILocation(line: 94, column: 3, scope: !719)
!719 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 7)
!720 = !DILocation(line: 94, column: 3, scope: !721)
!721 = !DILexicalBlockFile(scope: !722, file: !1, discriminator: 8)
!722 = distinct !DILexicalBlock(scope: !706, file: !1, line: 94, column: 3)
!723 = !DILocation(line: 94, column: 3, scope: !724)
!724 = !DILexicalBlockFile(scope: !725, file: !1, discriminator: 9)
!725 = distinct !DILexicalBlock(scope: !722, file: !1, line: 94, column: 3)
!726 = !DILocation(line: 94, column: 3, scope: !727)
!727 = !DILexicalBlockFile(scope: !725, file: !1, discriminator: 10)
!728 = !DILocation(line: 94, column: 3, scope: !729)
!729 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 11)
!730 = !DILocation(line: 96, column: 3, scope: !541)
!731 = !DILocation(line: 99, column: 12, scope: !541)
!732 = !DILocation(line: 99, column: 3, scope: !541)
!733 = !DILocation(line: 100, column: 10, scope: !541)
!734 = !DILocation(line: 100, column: 3, scope: !541)
!735 = !DILocation(line: 101, column: 1, scope: !541)
!736 = !DILocalVariable(name: "req", arg: 1, scope: !554, file: !1, line: 172, type: !470)
!737 = !DILocation(line: 172, column: 30, scope: !554)
!738 = !DILocalVariable(name: "statbuf", scope: !554, file: !1, line: 173, type: !739)
!739 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !400, size: 64, align: 64)
!740 = !DILocation(line: 173, column: 14, scope: !554)
!741 = !DILocalVariable(name: "ctx", scope: !554, file: !1, line: 174, type: !368)
!742 = !DILocation(line: 174, column: 20, scope: !554)
!743 = !DILocalVariable(name: "interval", scope: !554, file: !1, line: 175, type: !311)
!744 = !DILocation(line: 175, column: 12, scope: !554)
!745 = !DILocation(line: 177, column: 9, scope: !554)
!746 = !DILocation(line: 177, column: 7, scope: !554)
!747 = !DILocation(line: 179, column: 7, scope: !748)
!748 = distinct !DILexicalBlock(scope: !554, file: !1, line: 179, column: 7)
!749 = !DILocation(line: 179, column: 12, scope: !748)
!750 = !DILocation(line: 179, column: 26, scope: !748)
!751 = !DILocation(line: 179, column: 7, scope: !554)
!752 = !DILocation(line: 180, column: 29, scope: !753)
!753 = distinct !DILexicalBlock(scope: !748, file: !1, line: 179, column: 35)
!754 = !DILocation(line: 180, column: 34, scope: !753)
!755 = !DILocation(line: 180, column: 14, scope: !753)
!756 = !DILocation(line: 180, column: 5, scope: !753)
!757 = !DILocation(line: 181, column: 23, scope: !753)
!758 = !DILocation(line: 181, column: 5, scope: !753)
!759 = !DILocation(line: 182, column: 5, scope: !753)
!760 = !DILocation(line: 185, column: 7, scope: !761)
!761 = distinct !DILexicalBlock(scope: !554, file: !1, line: 185, column: 7)
!762 = !DILocation(line: 185, column: 12, scope: !761)
!763 = !DILocation(line: 185, column: 19, scope: !761)
!764 = !DILocation(line: 185, column: 7, scope: !554)
!765 = !DILocation(line: 186, column: 9, scope: !766)
!766 = distinct !DILexicalBlock(scope: !767, file: !1, line: 186, column: 9)
!767 = distinct !DILexicalBlock(scope: !761, file: !1, line: 185, column: 25)
!768 = !DILocation(line: 186, column: 14, scope: !766)
!769 = !DILocation(line: 186, column: 30, scope: !766)
!770 = !DILocation(line: 186, column: 35, scope: !766)
!771 = !DILocation(line: 186, column: 27, scope: !766)
!772 = !DILocation(line: 186, column: 9, scope: !767)
!773 = !DILocation(line: 187, column: 7, scope: !774)
!774 = distinct !DILexicalBlock(scope: !766, file: !1, line: 186, column: 43)
!775 = !DILocation(line: 187, column: 12, scope: !774)
!776 = !DILocation(line: 187, column: 20, scope: !774)
!777 = !DILocation(line: 187, column: 25, scope: !774)
!778 = !DILocation(line: 188, column: 20, scope: !774)
!779 = !DILocation(line: 188, column: 25, scope: !774)
!780 = !DILocation(line: 189, column: 21, scope: !774)
!781 = !DILocation(line: 189, column: 26, scope: !774)
!782 = !DILocation(line: 191, column: 27, scope: !774)
!783 = !DILocation(line: 191, column: 32, scope: !774)
!784 = !DILocation(line: 191, column: 7, scope: !774)
!785 = !DILocation(line: 191, column: 12, scope: !774)
!786 = !DILocation(line: 191, column: 25, scope: !774)
!787 = !DILocation(line: 192, column: 5, scope: !774)
!788 = !DILocation(line: 193, column: 5, scope: !767)
!789 = !DILocation(line: 196, column: 14, scope: !554)
!790 = !DILocation(line: 196, column: 19, scope: !554)
!791 = !DILocation(line: 196, column: 11, scope: !554)
!792 = !DILocation(line: 198, column: 7, scope: !793)
!793 = distinct !DILexicalBlock(scope: !554, file: !1, line: 198, column: 7)
!794 = !DILocation(line: 198, column: 12, scope: !793)
!795 = !DILocation(line: 198, column: 25, scope: !793)
!796 = !DILocation(line: 198, column: 7, scope: !554)
!797 = !DILocation(line: 199, column: 9, scope: !798)
!798 = distinct !DILexicalBlock(scope: !793, file: !1, line: 199, column: 9)
!799 = !DILocation(line: 199, column: 14, scope: !798)
!800 = !DILocation(line: 199, column: 27, scope: !798)
!801 = !DILocation(line: 199, column: 31, scope: !798)
!802 = !DILocation(line: 199, column: 47, scope: !803)
!803 = !DILexicalBlockFile(scope: !798, file: !1, discriminator: 1)
!804 = !DILocation(line: 199, column: 52, scope: !803)
!805 = !DILocation(line: 199, column: 61, scope: !803)
!806 = !DILocation(line: 199, column: 35, scope: !803)
!807 = !DILocation(line: 199, column: 9, scope: !803)
!808 = !DILocation(line: 200, column: 7, scope: !798)
!809 = !DILocation(line: 200, column: 12, scope: !798)
!810 = !DILocation(line: 200, column: 20, scope: !798)
!811 = !DILocation(line: 200, column: 25, scope: !798)
!812 = !DILocation(line: 200, column: 44, scope: !798)
!813 = !DILocation(line: 200, column: 49, scope: !798)
!814 = !DILocation(line: 200, column: 58, scope: !798)
!815 = !DILocation(line: 199, column: 68, scope: !816)
!816 = !DILexicalBlockFile(scope: !798, file: !1, discriminator: 2)
!817 = !DILocation(line: 202, column: 3, scope: !554)
!818 = !DILocation(line: 202, column: 8, scope: !554)
!819 = !DILocation(line: 202, column: 19, scope: !554)
!820 = !DILocation(line: 202, column: 18, scope: !554)
!821 = !DILocation(line: 203, column: 3, scope: !554)
!822 = !DILocation(line: 203, column: 8, scope: !554)
!823 = !DILocation(line: 203, column: 21, scope: !554)
!824 = !DILocation(line: 206, column: 21, scope: !554)
!825 = !DILocation(line: 206, column: 3, scope: !554)
!826 = !DILocation(line: 208, column: 7, scope: !827)
!827 = distinct !DILexicalBlock(scope: !554, file: !1, line: 208, column: 7)
!828 = !DILocation(line: 208, column: 12, scope: !827)
!829 = !DILocation(line: 208, column: 26, scope: !827)
!830 = !DILocation(line: 208, column: 7, scope: !554)
!831 = !DILocation(line: 209, column: 29, scope: !832)
!832 = distinct !DILexicalBlock(scope: !827, file: !1, line: 208, column: 35)
!833 = !DILocation(line: 209, column: 34, scope: !832)
!834 = !DILocation(line: 209, column: 14, scope: !832)
!835 = !DILocation(line: 209, column: 5, scope: !832)
!836 = !DILocation(line: 210, column: 5, scope: !832)
!837 = !DILocation(line: 214, column: 14, scope: !554)
!838 = !DILocation(line: 214, column: 19, scope: !554)
!839 = !DILocation(line: 214, column: 12, scope: !554)
!840 = !DILocation(line: 215, column: 23, scope: !554)
!841 = !DILocation(line: 215, column: 28, scope: !554)
!842 = !DILocation(line: 215, column: 16, scope: !554)
!843 = !DILocation(line: 215, column: 36, scope: !554)
!844 = !DILocation(line: 215, column: 41, scope: !554)
!845 = !DILocation(line: 215, column: 34, scope: !554)
!846 = !DILocation(line: 215, column: 55, scope: !554)
!847 = !DILocation(line: 215, column: 53, scope: !554)
!848 = !DILocation(line: 215, column: 12, scope: !554)
!849 = !DILocation(line: 217, column: 23, scope: !850)
!850 = distinct !DILexicalBlock(scope: !554, file: !1, line: 217, column: 7)
!851 = !DILocation(line: 217, column: 28, scope: !850)
!852 = !DILocation(line: 217, column: 52, scope: !850)
!853 = !DILocation(line: 217, column: 7, scope: !850)
!854 = !DILocation(line: 217, column: 7, scope: !554)
!855 = !DILocation(line: 218, column: 5, scope: !850)
!856 = !DILocation(line: 219, column: 1, scope: !554)
!857 = !DILocalVariable(name: "handle", arg: 1, scope: !544, file: !1, line: 104, type: !372)
!858 = !DILocation(line: 104, column: 35, scope: !544)
!859 = !DILocalVariable(name: "ctx", scope: !544, file: !1, line: 105, type: !368)
!860 = !DILocation(line: 105, column: 20, scope: !544)
!861 = !DILocation(line: 107, column: 8, scope: !862)
!862 = distinct !DILexicalBlock(scope: !544, file: !1, line: 107, column: 7)
!863 = !DILocation(line: 107, column: 7, scope: !544)
!864 = !DILocation(line: 108, column: 5, scope: !862)
!865 = !DILocation(line: 110, column: 9, scope: !544)
!866 = !DILocation(line: 110, column: 17, scope: !544)
!867 = !DILocation(line: 110, column: 7, scope: !544)
!868 = !DILocation(line: 111, column: 3, scope: !544)
!869 = !DILocation(line: 111, column: 3, scope: !870)
!870 = !DILexicalBlockFile(scope: !544, file: !1, discriminator: 1)
!871 = !DILocation(line: 111, column: 3, scope: !872)
!872 = !DILexicalBlockFile(scope: !544, file: !1, discriminator: 2)
!873 = !DILocation(line: 111, column: 3, scope: !874)
!874 = !DILexicalBlockFile(scope: !544, file: !1, discriminator: 3)
!875 = !DILocation(line: 112, column: 3, scope: !544)
!876 = !DILocation(line: 112, column: 3, scope: !870)
!877 = !DILocation(line: 112, column: 3, scope: !872)
!878 = !DILocation(line: 112, column: 3, scope: !874)
!879 = !DILocation(line: 113, column: 3, scope: !544)
!880 = !DILocation(line: 113, column: 8, scope: !544)
!881 = !DILocation(line: 113, column: 22, scope: !544)
!882 = !DILocation(line: 114, column: 3, scope: !544)
!883 = !DILocation(line: 114, column: 11, scope: !544)
!884 = !DILocation(line: 114, column: 20, scope: !544)
!885 = !DILocation(line: 119, column: 7, scope: !886)
!886 = distinct !DILexicalBlock(scope: !544, file: !1, line: 119, column: 7)
!887 = !DILocation(line: 119, column: 7, scope: !544)
!888 = !DILocation(line: 120, column: 29, scope: !886)
!889 = !DILocation(line: 120, column: 34, scope: !886)
!890 = !DILocation(line: 120, column: 14, scope: !886)
!891 = !DILocation(line: 120, column: 5, scope: !886)
!892 = !DILocation(line: 122, column: 3, scope: !544)
!893 = !DILocation(line: 122, column: 3, scope: !894)
!894 = !DILexicalBlockFile(scope: !895, file: !1, discriminator: 1)
!895 = distinct !DILexicalBlock(scope: !544, file: !1, line: 122, column: 3)
!896 = !DILocation(line: 122, column: 3, scope: !897)
!897 = !DILexicalBlockFile(scope: !895, file: !1, discriminator: 2)
!898 = !DILocation(line: 122, column: 3, scope: !899)
!899 = !DILexicalBlockFile(scope: !895, file: !1, discriminator: 3)
!900 = !DILocation(line: 122, column: 3, scope: !901)
!901 = !DILexicalBlockFile(scope: !895, file: !1, discriminator: 4)
!902 = !DILocation(line: 122, column: 3, scope: !903)
!903 = !DILexicalBlockFile(scope: !904, file: !1, discriminator: 5)
!904 = distinct !DILexicalBlock(scope: !895, file: !1, line: 122, column: 3)
!905 = !DILocation(line: 122, column: 3, scope: !906)
!906 = !DILexicalBlockFile(scope: !904, file: !1, discriminator: 6)
!907 = !DILocation(line: 122, column: 3, scope: !908)
!908 = !DILexicalBlockFile(scope: !895, file: !1, discriminator: 7)
!909 = !DILocation(line: 122, column: 3, scope: !910)
!910 = !DILexicalBlockFile(scope: !911, file: !1, discriminator: 8)
!911 = distinct !DILexicalBlock(scope: !895, file: !1, line: 122, column: 3)
!912 = !DILocation(line: 122, column: 3, scope: !913)
!913 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 9)
!914 = distinct !DILexicalBlock(scope: !911, file: !1, line: 122, column: 3)
!915 = !DILocation(line: 122, column: 3, scope: !916)
!916 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 10)
!917 = !DILocation(line: 122, column: 3, scope: !918)
!918 = !DILexicalBlockFile(scope: !895, file: !1, discriminator: 11)
!919 = !DILocation(line: 124, column: 3, scope: !544)
!920 = !DILocation(line: 125, column: 1, scope: !544)
!921 = !DILocalVariable(name: "handle", arg: 1, scope: !559, file: !1, line: 222, type: !158)
!922 = !DILocation(line: 222, column: 41, scope: !559)
!923 = !DILocation(line: 223, column: 12, scope: !559)
!924 = !DILocation(line: 223, column: 3, scope: !559)
!925 = !DILocation(line: 224, column: 1, scope: !559)
!926 = !DILocalVariable(name: "handle", arg: 1, scope: !547, file: !1, line: 128, type: !372)
!927 = !DILocation(line: 128, column: 38, scope: !547)
!928 = !DILocalVariable(name: "buffer", arg: 2, scope: !547, file: !1, line: 128, type: !496)
!929 = !DILocation(line: 128, column: 52, scope: !547)
!930 = !DILocalVariable(name: "size", arg: 3, scope: !547, file: !1, line: 128, type: !550)
!931 = !DILocation(line: 128, column: 68, scope: !547)
!932 = !DILocalVariable(name: "ctx", scope: !547, file: !1, line: 129, type: !368)
!933 = !DILocation(line: 129, column: 20, scope: !547)
!934 = !DILocalVariable(name: "required_len", scope: !547, file: !1, line: 130, type: !498)
!935 = !DILocation(line: 130, column: 10, scope: !547)
!936 = !DILocation(line: 132, column: 8, scope: !937)
!937 = distinct !DILexicalBlock(scope: !547, file: !1, line: 132, column: 7)
!938 = !DILocation(line: 132, column: 7, scope: !547)
!939 = !DILocation(line: 133, column: 6, scope: !940)
!940 = distinct !DILexicalBlock(scope: !937, file: !1, line: 132, column: 31)
!941 = !DILocation(line: 133, column: 11, scope: !940)
!942 = !DILocation(line: 134, column: 5, scope: !940)
!943 = !DILocation(line: 137, column: 9, scope: !547)
!944 = !DILocation(line: 137, column: 17, scope: !547)
!945 = !DILocation(line: 137, column: 7, scope: !547)
!946 = !DILocation(line: 138, column: 3, scope: !547)
!947 = !DILocation(line: 138, column: 3, scope: !948)
!948 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 1)
!949 = !DILocation(line: 138, column: 3, scope: !950)
!950 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 2)
!951 = !DILocation(line: 138, column: 3, scope: !952)
!952 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 3)
!953 = !DILocation(line: 140, column: 25, scope: !547)
!954 = !DILocation(line: 140, column: 30, scope: !547)
!955 = !DILocation(line: 140, column: 18, scope: !547)
!956 = !DILocation(line: 140, column: 16, scope: !547)
!957 = !DILocation(line: 141, column: 7, scope: !958)
!958 = distinct !DILexicalBlock(scope: !547, file: !1, line: 141, column: 7)
!959 = !DILocation(line: 141, column: 24, scope: !958)
!960 = !DILocation(line: 141, column: 23, scope: !958)
!961 = !DILocation(line: 141, column: 20, scope: !958)
!962 = !DILocation(line: 141, column: 7, scope: !547)
!963 = !DILocation(line: 142, column: 13, scope: !964)
!964 = distinct !DILexicalBlock(scope: !958, file: !1, line: 141, column: 30)
!965 = !DILocation(line: 142, column: 26, scope: !964)
!966 = !DILocation(line: 142, column: 6, scope: !964)
!967 = !DILocation(line: 142, column: 11, scope: !964)
!968 = !DILocation(line: 143, column: 5, scope: !964)
!969 = !DILocation(line: 146, column: 10, scope: !547)
!970 = !DILocation(line: 146, column: 18, scope: !547)
!971 = !DILocation(line: 146, column: 23, scope: !547)
!972 = !DILocation(line: 146, column: 3, scope: !547)
!973 = !DILocation(line: 146, column: 29, scope: !547)
!974 = !DILocation(line: 147, column: 11, scope: !547)
!975 = !DILocation(line: 147, column: 4, scope: !547)
!976 = !DILocation(line: 147, column: 9, scope: !547)
!977 = !DILocation(line: 148, column: 10, scope: !547)
!978 = !DILocation(line: 148, column: 3, scope: !547)
!979 = !DILocation(line: 148, column: 24, scope: !547)
!980 = !DILocation(line: 150, column: 3, scope: !547)
!981 = !DILocation(line: 151, column: 1, scope: !547)
!982 = !DILocalVariable(name: "handle", arg: 1, scope: !551, file: !1, line: 154, type: !372)
!983 = !DILocation(line: 154, column: 38, scope: !551)
!984 = !DILocation(line: 155, column: 19, scope: !551)
!985 = !DILocation(line: 155, column: 3, scope: !551)
!986 = !DILocation(line: 156, column: 1, scope: !551)
!987 = !DILocalVariable(name: "a", arg: 1, scope: !555, file: !1, line: 227, type: !398)
!988 = !DILocation(line: 227, column: 40, scope: !555)
!989 = !DILocalVariable(name: "b", arg: 2, scope: !555, file: !1, line: 227, type: !398)
!990 = !DILocation(line: 227, column: 60, scope: !555)
!991 = !DILocation(line: 228, column: 10, scope: !555)
!992 = !DILocation(line: 228, column: 13, scope: !555)
!993 = !DILocation(line: 228, column: 21, scope: !555)
!994 = !DILocation(line: 228, column: 32, scope: !555)
!995 = !DILocation(line: 228, column: 35, scope: !555)
!996 = !DILocation(line: 228, column: 43, scope: !555)
!997 = !DILocation(line: 228, column: 29, scope: !555)
!998 = !DILocation(line: 229, column: 7, scope: !555)
!999 = !DILocation(line: 229, column: 10, scope: !1000)
!1000 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 1)
!1001 = !DILocation(line: 229, column: 13, scope: !1000)
!1002 = !DILocation(line: 229, column: 21, scope: !1000)
!1003 = !DILocation(line: 229, column: 32, scope: !1000)
!1004 = !DILocation(line: 229, column: 35, scope: !1000)
!1005 = !DILocation(line: 229, column: 43, scope: !1000)
!1006 = !DILocation(line: 229, column: 29, scope: !1000)
!1007 = !DILocation(line: 230, column: 7, scope: !555)
!1008 = !DILocation(line: 230, column: 10, scope: !1000)
!1009 = !DILocation(line: 230, column: 13, scope: !1000)
!1010 = !DILocation(line: 230, column: 25, scope: !1000)
!1011 = !DILocation(line: 230, column: 36, scope: !1000)
!1012 = !DILocation(line: 230, column: 39, scope: !1000)
!1013 = !DILocation(line: 230, column: 51, scope: !1000)
!1014 = !DILocation(line: 230, column: 33, scope: !1000)
!1015 = !DILocation(line: 231, column: 7, scope: !555)
!1016 = !DILocation(line: 231, column: 10, scope: !1000)
!1017 = !DILocation(line: 231, column: 13, scope: !1000)
!1018 = !DILocation(line: 231, column: 21, scope: !1000)
!1019 = !DILocation(line: 231, column: 31, scope: !1000)
!1020 = !DILocation(line: 231, column: 34, scope: !1000)
!1021 = !DILocation(line: 231, column: 42, scope: !1000)
!1022 = !DILocation(line: 231, column: 28, scope: !1000)
!1023 = !DILocation(line: 232, column: 7, scope: !555)
!1024 = !DILocation(line: 232, column: 10, scope: !1000)
!1025 = !DILocation(line: 232, column: 13, scope: !1000)
!1026 = !DILocation(line: 232, column: 21, scope: !1000)
!1027 = !DILocation(line: 232, column: 31, scope: !1000)
!1028 = !DILocation(line: 232, column: 34, scope: !1000)
!1029 = !DILocation(line: 232, column: 42, scope: !1000)
!1030 = !DILocation(line: 232, column: 28, scope: !1000)
!1031 = !DILocation(line: 233, column: 7, scope: !555)
!1032 = !DILocation(line: 233, column: 10, scope: !1000)
!1033 = !DILocation(line: 233, column: 13, scope: !1000)
!1034 = !DILocation(line: 233, column: 25, scope: !1000)
!1035 = !DILocation(line: 233, column: 35, scope: !1000)
!1036 = !DILocation(line: 233, column: 38, scope: !1000)
!1037 = !DILocation(line: 233, column: 50, scope: !1000)
!1038 = !DILocation(line: 233, column: 32, scope: !1000)
!1039 = !DILocation(line: 234, column: 7, scope: !555)
!1040 = !DILocation(line: 234, column: 10, scope: !1000)
!1041 = !DILocation(line: 234, column: 13, scope: !1000)
!1042 = !DILocation(line: 234, column: 24, scope: !1000)
!1043 = !DILocation(line: 234, column: 27, scope: !1000)
!1044 = !DILocation(line: 234, column: 21, scope: !1000)
!1045 = !DILocation(line: 235, column: 7, scope: !555)
!1046 = !DILocation(line: 235, column: 10, scope: !1000)
!1047 = !DILocation(line: 235, column: 13, scope: !1000)
!1048 = !DILocation(line: 235, column: 24, scope: !1000)
!1049 = !DILocation(line: 235, column: 27, scope: !1000)
!1050 = !DILocation(line: 235, column: 21, scope: !1000)
!1051 = !DILocation(line: 236, column: 7, scope: !555)
!1052 = !DILocation(line: 236, column: 10, scope: !1000)
!1053 = !DILocation(line: 236, column: 13, scope: !1000)
!1054 = !DILocation(line: 236, column: 23, scope: !1000)
!1055 = !DILocation(line: 236, column: 26, scope: !1000)
!1056 = !DILocation(line: 236, column: 20, scope: !1000)
!1057 = !DILocation(line: 237, column: 7, scope: !555)
!1058 = !DILocation(line: 237, column: 10, scope: !1000)
!1059 = !DILocation(line: 237, column: 13, scope: !1000)
!1060 = !DILocation(line: 237, column: 23, scope: !1000)
!1061 = !DILocation(line: 237, column: 26, scope: !1000)
!1062 = !DILocation(line: 237, column: 20, scope: !1000)
!1063 = !DILocation(line: 238, column: 7, scope: !555)
!1064 = !DILocation(line: 238, column: 10, scope: !1000)
!1065 = !DILocation(line: 238, column: 13, scope: !1000)
!1066 = !DILocation(line: 238, column: 23, scope: !1000)
!1067 = !DILocation(line: 238, column: 26, scope: !1000)
!1068 = !DILocation(line: 238, column: 20, scope: !1000)
!1069 = !DILocation(line: 239, column: 7, scope: !555)
!1070 = !DILocation(line: 239, column: 10, scope: !1000)
!1071 = !DILocation(line: 239, column: 13, scope: !1000)
!1072 = !DILocation(line: 239, column: 23, scope: !1000)
!1073 = !DILocation(line: 239, column: 26, scope: !1000)
!1074 = !DILocation(line: 239, column: 20, scope: !1000)
!1075 = !DILocation(line: 240, column: 7, scope: !555)
!1076 = !DILocation(line: 240, column: 10, scope: !1000)
!1077 = !DILocation(line: 240, column: 13, scope: !1000)
!1078 = !DILocation(line: 240, column: 25, scope: !1000)
!1079 = !DILocation(line: 240, column: 28, scope: !1000)
!1080 = !DILocation(line: 240, column: 22, scope: !1000)
!1081 = !DILocation(line: 241, column: 7, scope: !555)
!1082 = !DILocation(line: 241, column: 10, scope: !1000)
!1083 = !DILocation(line: 241, column: 13, scope: !1000)
!1084 = !DILocation(line: 241, column: 23, scope: !1000)
!1085 = !DILocation(line: 241, column: 26, scope: !1000)
!1086 = !DILocation(line: 241, column: 20, scope: !1000)
!1087 = !DILocation(line: 241, column: 7, scope: !1088)
!1088 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 2)
!1089 = !DILocation(line: 228, column: 3, scope: !1000)
!1090 = !DILocalVariable(name: "timer", arg: 1, scope: !558, file: !1, line: 159, type: !445)
!1091 = !DILocation(line: 159, column: 34, scope: !558)
!1092 = !DILocalVariable(name: "ctx", scope: !558, file: !1, line: 160, type: !368)
!1093 = !DILocation(line: 160, column: 20, scope: !558)
!1094 = !DILocation(line: 162, column: 9, scope: !558)
!1095 = !DILocation(line: 162, column: 7, scope: !558)
!1096 = !DILocation(line: 163, column: 3, scope: !558)
!1097 = !DILocation(line: 163, column: 3, scope: !1098)
!1098 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 1)
!1099 = !DILocation(line: 163, column: 3, scope: !1100)
!1100 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 2)
!1101 = !DILocation(line: 163, column: 3, scope: !1102)
!1102 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 3)
!1103 = !DILocation(line: 164, column: 3, scope: !558)
!1104 = !DILocation(line: 164, column: 3, scope: !1098)
!1105 = !DILocation(line: 164, column: 3, scope: !1100)
!1106 = !DILocation(line: 164, column: 3, scope: !1102)
!1107 = !DILocation(line: 165, column: 28, scope: !558)
!1108 = !DILocation(line: 165, column: 33, scope: !558)
!1109 = !DILocation(line: 165, column: 21, scope: !558)
!1110 = !DILocation(line: 165, column: 3, scope: !558)
!1111 = !DILocation(line: 165, column: 8, scope: !558)
!1112 = !DILocation(line: 165, column: 19, scope: !558)
!1113 = !DILocation(line: 167, column: 18, scope: !1114)
!1114 = distinct !DILexicalBlock(scope: !558, file: !1, line: 167, column: 7)
!1115 = !DILocation(line: 167, column: 23, scope: !1114)
!1116 = !DILocation(line: 167, column: 30, scope: !1114)
!1117 = !DILocation(line: 167, column: 35, scope: !1114)
!1118 = !DILocation(line: 167, column: 43, scope: !1114)
!1119 = !DILocation(line: 167, column: 48, scope: !1114)
!1120 = !DILocation(line: 167, column: 7, scope: !1114)
!1121 = !DILocation(line: 167, column: 7, scope: !558)
!1122 = !DILocation(line: 168, column: 5, scope: !1114)
!1123 = !DILocation(line: 169, column: 1, scope: !558)
