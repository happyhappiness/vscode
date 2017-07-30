; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-inotify.c'
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
%struct.watcher_list = type { %struct.anon.4, [2 x i8*], i32, i8*, i32 }
%struct.anon.4 = type { %struct.watcher_list*, %struct.watcher_list*, %struct.watcher_list*, i32 }
%struct.uv_fs_event_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i8*, void (%struct.uv_fs_event_s*, i8*, i32, i32)*, [2 x i8*], i32 }
%union.anon.5 = type { [4 x i8*] }
%struct.watcher_root = type { %struct.watcher_list* }
%struct.uv__inotify_event = type { i32, i32, i32, i32 }

@.str = private unnamed_addr constant [23 x i8] c"tmp_path != ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [77 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-inotify.c\00", align 1
@__PRETTY_FUNCTION__.uv__inotify_fork = private unnamed_addr constant [42 x i8] c"int uv__inotify_fork(uv_loop_t *, void *)\00", align 1
@.str.2 = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@__PRETTY_FUNCTION__.uv_fs_event_start = private unnamed_addr constant [83 x i8] c"int uv_fs_event_start(uv_fs_event_t *, uv_fs_event_cb, const char *, unsigned int)\00", align 1
@.str.3 = private unnamed_addr constant [16 x i8] c"w != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_event_stop = private unnamed_addr constant [38 x i8] c"int uv_fs_event_stop(uv_fs_event_t *)\00", align 1
@.str.4 = private unnamed_addr constant [61 x i8] c"(*__errno_location ()) == 11 || (*__errno_location ()) == 11\00", align 1
@__PRETTY_FUNCTION__.uv__inotify_read = private unnamed_addr constant [61 x i8] c"void uv__inotify_read(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1
@.str.5 = private unnamed_addr constant [9 x i8] c"size > 0\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv__inotify_fork(%struct.uv_loop_s* %loop, i8* %old_watchers) #0 !dbg !307 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %old_watchers.addr = alloca i8*, align 8
  %err = alloca i32, align 4
  %tmp_watcher_list_iter = alloca %struct.watcher_list*, align 8
  %watcher_list = alloca %struct.watcher_list*, align 8
  %tmp_watcher_list = alloca %struct.watcher_list, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %handle = alloca %struct.uv_fs_event_s*, align 8
  %tmp_path = alloca i8*, align 8
  %q18 = alloca [2 x i8*]*, align 8
  %q92 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !367, metadata !368), !dbg !369
  store i8* %old_watchers, i8** %old_watchers.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %old_watchers.addr, metadata !370, metadata !368), !dbg !371
  call void @llvm.dbg.declare(metadata i32* %err, metadata !372, metadata !368), !dbg !373
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %tmp_watcher_list_iter, metadata !374, metadata !368), !dbg !375
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %watcher_list, metadata !376, metadata !368), !dbg !377
  call void @llvm.dbg.declare(metadata %struct.watcher_list* %tmp_watcher_list, metadata !378, metadata !368), !dbg !379
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !380, metadata !368), !dbg !381
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !382, metadata !368), !dbg !383
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %handle, metadata !384, metadata !368), !dbg !385
  call void @llvm.dbg.declare(metadata i8** %tmp_path, metadata !386, metadata !368), !dbg !387
  %0 = load i8*, i8** %old_watchers.addr, align 8, !dbg !388
  %cmp = icmp ne i8* %0, null, !dbg !390
  br i1 %cmp, label %if.then, label %if.end134, !dbg !391

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %old_watchers.addr, align 8, !dbg !392
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !394
  %inotify_watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 33, !dbg !395
  store i8* %1, i8** %inotify_watchers, align 8, !dbg !396
  br label %do.body, !dbg !397

do.body:                                          ; preds = %if.then
  %watchers = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !398
  %watchers1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !398
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers1, i64 0, i64 0, !dbg !398
  %3 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !398
  store [2 x i8*]* %watchers, [2 x i8*]** %3, align 8, !dbg !398
  %watchers2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !398
  %watchers3 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !398
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers3, i64 0, i64 1, !dbg !398
  %4 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !398
  store [2 x i8*]* %watchers2, [2 x i8*]** %4, align 8, !dbg !398
  br label %do.end, !dbg !398

do.end:                                           ; preds = %do.body
  %5 = bitcast i8** %old_watchers.addr to %struct.watcher_root*, !dbg !401
  %call = call %struct.watcher_list* @watcher_root_RB_MINMAX(%struct.watcher_root* %5, i32 -1), !dbg !401
  store %struct.watcher_list* %call, %struct.watcher_list** %watcher_list, align 8, !dbg !401
  br label %for.cond, !dbg !401

for.cond:                                         ; preds = %for.inc, %do.end
  %6 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !403
  %cmp5 = icmp ne %struct.watcher_list* %6, null, !dbg !403
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !403

land.rhs:                                         ; preds = %for.cond
  %7 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !406
  %call6 = call %struct.watcher_list* @watcher_root_RB_NEXT(%struct.watcher_list* %7), !dbg !406
  store %struct.watcher_list* %call6, %struct.watcher_list** %tmp_watcher_list_iter, align 8, !dbg !406
  %8 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !406
  %cmp7 = icmp ne %struct.watcher_list* %8, null, !dbg !406
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %9 = phi i1 [ false, %for.cond ], [ %cmp7, %land.rhs ]
  br i1 %9, label %for.body, label %for.end, !dbg !408

for.body:                                         ; preds = %land.end
  %10 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !410
  %iterating = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %10, i32 0, i32 2, !dbg !412
  store i32 1, i32* %iterating, align 8, !dbg !413
  br label %do.body8, !dbg !414

do.body8:                                         ; preds = %for.body
  %11 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !415
  %watchers9 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %11, i32 0, i32 1, !dbg !415
  %12 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !415
  %watchers10 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %12, i32 0, i32 1, !dbg !415
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers10, i64 0, i64 0, !dbg !415
  %13 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !415
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !415
  %cmp12 = icmp eq [2 x i8*]* %watchers9, %14, !dbg !415
  br i1 %cmp12, label %if.then13, label %if.else, !dbg !415

if.then13:                                        ; preds = %do.body8
  br label %do.body14, !dbg !419

do.body14:                                        ; preds = %if.then13
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !421
  %15 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !421
  store [2 x i8*]* %queue, [2 x i8*]** %15, align 16, !dbg !421
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !421
  %16 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !421
  store [2 x i8*]* %queue, [2 x i8*]** %16, align 8, !dbg !421
  br label %do.end17, !dbg !421

do.end17:                                         ; preds = %do.body14
  br label %if.end, !dbg !424

if.else:                                          ; preds = %do.body8
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q18, metadata !426, metadata !368), !dbg !428
  %17 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !429
  %watchers19 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %17, i32 0, i32 1, !dbg !429
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers19, i64 0, i64 0, !dbg !429
  %18 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !429
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !429
  store [2 x i8*]* %19, [2 x i8*]** %q18, align 8, !dbg !429
  br label %do.body21, !dbg !429

do.body21:                                        ; preds = %if.else
  %20 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !431
  %watchers22 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %20, i32 0, i32 1, !dbg !431
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers22, i64 0, i64 1, !dbg !431
  %21 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !431
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !431
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !431
  %23 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !431
  store [2 x i8*]* %22, [2 x i8*]** %23, align 8, !dbg !431
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !431
  %24 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !431
  %25 = load [2 x i8*]*, [2 x i8*]** %24, align 8, !dbg !431
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %25, i64 0, i64 0, !dbg !431
  %26 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !431
  store [2 x i8*]* %queue, [2 x i8*]** %26, align 8, !dbg !431
  %27 = load [2 x i8*]*, [2 x i8*]** %q18, align 8, !dbg !431
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !431
  %28 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !431
  store [2 x i8*]* %27, [2 x i8*]** %28, align 16, !dbg !431
  %29 = load [2 x i8*]*, [2 x i8*]** %q18, align 8, !dbg !431
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %29, i64 0, i64 1, !dbg !431
  %30 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !431
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 8, !dbg !431
  %32 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !431
  %watchers29 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %32, i32 0, i32 1, !dbg !431
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers29, i64 0, i64 1, !dbg !431
  %33 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !431
  store [2 x i8*]* %31, [2 x i8*]** %33, align 8, !dbg !431
  %34 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !431
  %watchers31 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %34, i32 0, i32 1, !dbg !431
  %35 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !431
  %watchers32 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %35, i32 0, i32 1, !dbg !431
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers32, i64 0, i64 1, !dbg !431
  %36 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !431
  %37 = load [2 x i8*]*, [2 x i8*]** %36, align 8, !dbg !431
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 0, !dbg !431
  %38 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !431
  store [2 x i8*]* %watchers31, [2 x i8*]** %38, align 8, !dbg !431
  %39 = load [2 x i8*]*, [2 x i8*]** %q18, align 8, !dbg !431
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %39, i64 0, i64 1, !dbg !431
  %40 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !431
  store [2 x i8*]* %queue, [2 x i8*]** %40, align 8, !dbg !431
  br label %do.end36, !dbg !431

do.end36:                                         ; preds = %do.body21
  br label %if.end

if.end:                                           ; preds = %do.end36, %do.end17
  br label %do.end37, !dbg !434

do.end37:                                         ; preds = %if.end
  br label %while.cond, !dbg !436

while.cond:                                       ; preds = %do.end78, %do.end37
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !437
  %41 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !437
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 16, !dbg !437
  %cmp39 = icmp eq [2 x i8*]* %queue, %42, !dbg !437
  %lnot = xor i1 %cmp39, true, !dbg !439
  br i1 %lnot, label %while.body, label %while.end, !dbg !440

while.body:                                       ; preds = %while.cond
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !441
  %43 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !441
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 16, !dbg !441
  store [2 x i8*]* %44, [2 x i8*]** %q, align 8, !dbg !443
  %45 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !444
  %46 = bitcast [2 x i8*]* %45 to i8*, !dbg !444
  %add.ptr = getelementptr inbounds i8, i8* %46, i64 -112, !dbg !444
  %47 = bitcast i8* %add.ptr to %struct.uv_fs_event_s*, !dbg !444
  store %struct.uv_fs_event_s* %47, %struct.uv_fs_event_s** %handle, align 8, !dbg !445
  %48 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !446
  %path = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %48, i32 0, i32 8, !dbg !447
  %49 = load i8*, i8** %path, align 8, !dbg !447
  %call41 = call i8* @uv__strdup(i8* %49), !dbg !448
  store i8* %call41, i8** %tmp_path, align 8, !dbg !449
  %50 = load i8*, i8** %tmp_path, align 8, !dbg !450
  %cmp42 = icmp ne i8* %50, null, !dbg !450
  br i1 %cmp42, label %cond.true, label %cond.false, !dbg !450

cond.true:                                        ; preds = %while.body
  br label %cond.end, !dbg !451

cond.false:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 148, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @__PRETTY_FUNCTION__.uv__inotify_fork, i32 0, i32 0)) #8, !dbg !453
  unreachable, !dbg !453
                                                  ; No predecessors!
  br label %cond.end, !dbg !455

cond.end:                                         ; preds = %51, %cond.true
  br label %do.body43, !dbg !457

do.body43:                                        ; preds = %cond.end
  %52 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !458
  %arrayidx44 = getelementptr inbounds [2 x i8*], [2 x i8*]* %52, i64 0, i64 0, !dbg !458
  %53 = bitcast i8** %arrayidx44 to [2 x i8*]**, !dbg !458
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !458
  %55 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !458
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %55, i64 0, i64 1, !dbg !458
  %56 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !458
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !458
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 0, !dbg !458
  %58 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !458
  store [2 x i8*]* %54, [2 x i8*]** %58, align 8, !dbg !458
  %59 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !458
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %59, i64 0, i64 1, !dbg !458
  %60 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !458
  %61 = load [2 x i8*]*, [2 x i8*]** %60, align 8, !dbg !458
  %62 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !458
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !458
  %63 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !458
  %64 = load [2 x i8*]*, [2 x i8*]** %63, align 8, !dbg !458
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %64, i64 0, i64 1, !dbg !458
  %65 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !458
  store [2 x i8*]* %61, [2 x i8*]** %65, align 8, !dbg !458
  br label %do.end50, !dbg !458

do.end50:                                         ; preds = %do.body43
  br label %do.body51, !dbg !461

do.body51:                                        ; preds = %do.end50
  %66 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !462
  %watchers52 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %66, i32 0, i32 1, !dbg !462
  %67 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !462
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %67, i64 0, i64 0, !dbg !462
  %68 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !462
  store [2 x i8*]* %watchers52, [2 x i8*]** %68, align 8, !dbg !462
  %69 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !462
  %watchers54 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %69, i32 0, i32 1, !dbg !462
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers54, i64 0, i64 1, !dbg !462
  %70 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !462
  %71 = load [2 x i8*]*, [2 x i8*]** %70, align 8, !dbg !462
  %72 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !462
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %72, i64 0, i64 1, !dbg !462
  %73 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !462
  store [2 x i8*]* %71, [2 x i8*]** %73, align 8, !dbg !462
  %74 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !462
  %75 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !462
  %arrayidx57 = getelementptr inbounds [2 x i8*], [2 x i8*]* %75, i64 0, i64 1, !dbg !462
  %76 = bitcast i8** %arrayidx57 to [2 x i8*]**, !dbg !462
  %77 = load [2 x i8*]*, [2 x i8*]** %76, align 8, !dbg !462
  %arrayidx58 = getelementptr inbounds [2 x i8*], [2 x i8*]* %77, i64 0, i64 0, !dbg !462
  %78 = bitcast i8** %arrayidx58 to [2 x i8*]**, !dbg !462
  store [2 x i8*]* %74, [2 x i8*]** %78, align 8, !dbg !462
  %79 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !462
  %80 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !462
  %watchers59 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %80, i32 0, i32 1, !dbg !462
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers59, i64 0, i64 1, !dbg !462
  %81 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !462
  store [2 x i8*]* %79, [2 x i8*]** %81, align 8, !dbg !462
  br label %do.end61, !dbg !462

do.end61:                                         ; preds = %do.body51
  %82 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !465
  %call62 = call i32 @uv_fs_event_stop(%struct.uv_fs_event_s* %82), !dbg !466
  br label %do.body63, !dbg !467

do.body63:                                        ; preds = %do.end61
  %watchers64 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !468
  %83 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !468
  %watchers65 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %83, i32 0, i32 10, !dbg !468
  %arrayidx66 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers65, i64 0, i64 0, !dbg !468
  %84 = bitcast i8** %arrayidx66 to [2 x i8*]**, !dbg !468
  store [2 x i8*]* %watchers64, [2 x i8*]** %84, align 8, !dbg !468
  %watchers67 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !468
  %arrayidx68 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers67, i64 0, i64 1, !dbg !468
  %85 = bitcast i8** %arrayidx68 to [2 x i8*]**, !dbg !468
  %86 = load [2 x i8*]*, [2 x i8*]** %85, align 8, !dbg !468
  %87 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !468
  %watchers69 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %87, i32 0, i32 10, !dbg !468
  %arrayidx70 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers69, i64 0, i64 1, !dbg !468
  %88 = bitcast i8** %arrayidx70 to [2 x i8*]**, !dbg !468
  store [2 x i8*]* %86, [2 x i8*]** %88, align 8, !dbg !468
  %89 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !468
  %watchers71 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %89, i32 0, i32 10, !dbg !468
  %90 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !468
  %watchers72 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %90, i32 0, i32 10, !dbg !468
  %arrayidx73 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers72, i64 0, i64 1, !dbg !468
  %91 = bitcast i8** %arrayidx73 to [2 x i8*]**, !dbg !468
  %92 = load [2 x i8*]*, [2 x i8*]** %91, align 8, !dbg !468
  %arrayidx74 = getelementptr inbounds [2 x i8*], [2 x i8*]* %92, i64 0, i64 0, !dbg !468
  %93 = bitcast i8** %arrayidx74 to [2 x i8*]**, !dbg !468
  store [2 x i8*]* %watchers71, [2 x i8*]** %93, align 8, !dbg !468
  %94 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !468
  %watchers75 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %94, i32 0, i32 10, !dbg !468
  %watchers76 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !468
  %arrayidx77 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers76, i64 0, i64 1, !dbg !468
  %95 = bitcast i8** %arrayidx77 to [2 x i8*]**, !dbg !468
  store [2 x i8*]* %watchers75, [2 x i8*]** %95, align 8, !dbg !468
  br label %do.end78, !dbg !468

do.end78:                                         ; preds = %do.body63
  %96 = load i8*, i8** %tmp_path, align 8, !dbg !471
  %97 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !472
  %path79 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %97, i32 0, i32 8, !dbg !473
  store i8* %96, i8** %path79, align 8, !dbg !474
  br label %while.cond, !dbg !475

while.end:                                        ; preds = %while.cond
  %98 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !477
  %iterating80 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %98, i32 0, i32 2, !dbg !478
  store i32 0, i32* %iterating80, align 8, !dbg !479
  %99 = load %struct.watcher_list*, %struct.watcher_list** %watcher_list, align 8, !dbg !480
  %100 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !481
  call void @maybe_free_watcher_list(%struct.watcher_list* %99, %struct.uv_loop_s* %100), !dbg !482
  br label %for.inc, !dbg !483

for.inc:                                          ; preds = %while.end
  %101 = load %struct.watcher_list*, %struct.watcher_list** %tmp_watcher_list_iter, align 8, !dbg !484
  store %struct.watcher_list* %101, %struct.watcher_list** %watcher_list, align 8, !dbg !484
  br label %for.cond, !dbg !484

for.end:                                          ; preds = %land.end
  br label %do.body81, !dbg !486

do.body81:                                        ; preds = %for.end
  %watchers82 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !487
  %watchers83 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !487
  %arrayidx84 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers83, i64 0, i64 0, !dbg !487
  %102 = bitcast i8** %arrayidx84 to [2 x i8*]**, !dbg !487
  %103 = load [2 x i8*]*, [2 x i8*]** %102, align 8, !dbg !487
  %cmp85 = icmp eq [2 x i8*]* %watchers82, %103, !dbg !487
  br i1 %cmp85, label %if.then86, label %if.else91, !dbg !487

if.then86:                                        ; preds = %do.body81
  br label %do.body87, !dbg !491

do.body87:                                        ; preds = %if.then86
  %arrayidx88 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !493
  %104 = bitcast i8** %arrayidx88 to [2 x i8*]**, !dbg !493
  store [2 x i8*]* %queue, [2 x i8*]** %104, align 16, !dbg !493
  %arrayidx89 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !493
  %105 = bitcast i8** %arrayidx89 to [2 x i8*]**, !dbg !493
  store [2 x i8*]* %queue, [2 x i8*]** %105, align 8, !dbg !493
  br label %do.end90, !dbg !493

do.end90:                                         ; preds = %do.body87
  br label %if.end111, !dbg !496

if.else91:                                        ; preds = %do.body81
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q92, metadata !498, metadata !368), !dbg !500
  %watchers93 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !501
  %arrayidx94 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers93, i64 0, i64 0, !dbg !501
  %106 = bitcast i8** %arrayidx94 to [2 x i8*]**, !dbg !501
  %107 = load [2 x i8*]*, [2 x i8*]** %106, align 8, !dbg !501
  store [2 x i8*]* %107, [2 x i8*]** %q92, align 8, !dbg !501
  br label %do.body95, !dbg !501

do.body95:                                        ; preds = %if.else91
  %watchers96 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !503
  %arrayidx97 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers96, i64 0, i64 1, !dbg !503
  %108 = bitcast i8** %arrayidx97 to [2 x i8*]**, !dbg !503
  %109 = load [2 x i8*]*, [2 x i8*]** %108, align 8, !dbg !503
  %arrayidx98 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !503
  %110 = bitcast i8** %arrayidx98 to [2 x i8*]**, !dbg !503
  store [2 x i8*]* %109, [2 x i8*]** %110, align 8, !dbg !503
  %arrayidx99 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !503
  %111 = bitcast i8** %arrayidx99 to [2 x i8*]**, !dbg !503
  %112 = load [2 x i8*]*, [2 x i8*]** %111, align 8, !dbg !503
  %arrayidx100 = getelementptr inbounds [2 x i8*], [2 x i8*]* %112, i64 0, i64 0, !dbg !503
  %113 = bitcast i8** %arrayidx100 to [2 x i8*]**, !dbg !503
  store [2 x i8*]* %queue, [2 x i8*]** %113, align 8, !dbg !503
  %114 = load [2 x i8*]*, [2 x i8*]** %q92, align 8, !dbg !503
  %arrayidx101 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !503
  %115 = bitcast i8** %arrayidx101 to [2 x i8*]**, !dbg !503
  store [2 x i8*]* %114, [2 x i8*]** %115, align 16, !dbg !503
  %116 = load [2 x i8*]*, [2 x i8*]** %q92, align 8, !dbg !503
  %arrayidx102 = getelementptr inbounds [2 x i8*], [2 x i8*]* %116, i64 0, i64 1, !dbg !503
  %117 = bitcast i8** %arrayidx102 to [2 x i8*]**, !dbg !503
  %118 = load [2 x i8*]*, [2 x i8*]** %117, align 8, !dbg !503
  %watchers103 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !503
  %arrayidx104 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers103, i64 0, i64 1, !dbg !503
  %119 = bitcast i8** %arrayidx104 to [2 x i8*]**, !dbg !503
  store [2 x i8*]* %118, [2 x i8*]** %119, align 8, !dbg !503
  %watchers105 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !503
  %watchers106 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %tmp_watcher_list, i32 0, i32 1, !dbg !503
  %arrayidx107 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers106, i64 0, i64 1, !dbg !503
  %120 = bitcast i8** %arrayidx107 to [2 x i8*]**, !dbg !503
  %121 = load [2 x i8*]*, [2 x i8*]** %120, align 8, !dbg !503
  %arrayidx108 = getelementptr inbounds [2 x i8*], [2 x i8*]* %121, i64 0, i64 0, !dbg !503
  %122 = bitcast i8** %arrayidx108 to [2 x i8*]**, !dbg !503
  store [2 x i8*]* %watchers105, [2 x i8*]** %122, align 8, !dbg !503
  %123 = load [2 x i8*]*, [2 x i8*]** %q92, align 8, !dbg !503
  %arrayidx109 = getelementptr inbounds [2 x i8*], [2 x i8*]* %123, i64 0, i64 1, !dbg !503
  %124 = bitcast i8** %arrayidx109 to [2 x i8*]**, !dbg !503
  store [2 x i8*]* %queue, [2 x i8*]** %124, align 8, !dbg !503
  br label %do.end110, !dbg !503

do.end110:                                        ; preds = %do.body95
  br label %if.end111

if.end111:                                        ; preds = %do.end110, %do.end90
  br label %do.end112, !dbg !506

do.end112:                                        ; preds = %if.end111
  br label %while.cond113, !dbg !508

while.cond113:                                    ; preds = %if.end132, %do.end112
  %arrayidx114 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !509
  %125 = bitcast i8** %arrayidx114 to [2 x i8*]**, !dbg !509
  %126 = load [2 x i8*]*, [2 x i8*]** %125, align 16, !dbg !509
  %cmp115 = icmp eq [2 x i8*]* %queue, %126, !dbg !509
  %lnot116 = xor i1 %cmp115, true, !dbg !511
  br i1 %lnot116, label %while.body117, label %while.end133, !dbg !512

while.body117:                                    ; preds = %while.cond113
  %arrayidx118 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !513
  %127 = bitcast i8** %arrayidx118 to [2 x i8*]**, !dbg !513
  %128 = load [2 x i8*]*, [2 x i8*]** %127, align 16, !dbg !513
  store [2 x i8*]* %128, [2 x i8*]** %q, align 8, !dbg !515
  br label %do.body119, !dbg !516

do.body119:                                       ; preds = %while.body117
  %129 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !517
  %arrayidx120 = getelementptr inbounds [2 x i8*], [2 x i8*]* %129, i64 0, i64 0, !dbg !517
  %130 = bitcast i8** %arrayidx120 to [2 x i8*]**, !dbg !517
  %131 = load [2 x i8*]*, [2 x i8*]** %130, align 8, !dbg !517
  %132 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !517
  %arrayidx121 = getelementptr inbounds [2 x i8*], [2 x i8*]* %132, i64 0, i64 1, !dbg !517
  %133 = bitcast i8** %arrayidx121 to [2 x i8*]**, !dbg !517
  %134 = load [2 x i8*]*, [2 x i8*]** %133, align 8, !dbg !517
  %arrayidx122 = getelementptr inbounds [2 x i8*], [2 x i8*]* %134, i64 0, i64 0, !dbg !517
  %135 = bitcast i8** %arrayidx122 to [2 x i8*]**, !dbg !517
  store [2 x i8*]* %131, [2 x i8*]** %135, align 8, !dbg !517
  %136 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !517
  %arrayidx123 = getelementptr inbounds [2 x i8*], [2 x i8*]* %136, i64 0, i64 1, !dbg !517
  %137 = bitcast i8** %arrayidx123 to [2 x i8*]**, !dbg !517
  %138 = load [2 x i8*]*, [2 x i8*]** %137, align 8, !dbg !517
  %139 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !517
  %arrayidx124 = getelementptr inbounds [2 x i8*], [2 x i8*]* %139, i64 0, i64 0, !dbg !517
  %140 = bitcast i8** %arrayidx124 to [2 x i8*]**, !dbg !517
  %141 = load [2 x i8*]*, [2 x i8*]** %140, align 8, !dbg !517
  %arrayidx125 = getelementptr inbounds [2 x i8*], [2 x i8*]* %141, i64 0, i64 1, !dbg !517
  %142 = bitcast i8** %arrayidx125 to [2 x i8*]**, !dbg !517
  store [2 x i8*]* %138, [2 x i8*]** %142, align 8, !dbg !517
  br label %do.end126, !dbg !517

do.end126:                                        ; preds = %do.body119
  %143 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !520
  %144 = bitcast [2 x i8*]* %143 to i8*, !dbg !520
  %add.ptr127 = getelementptr inbounds i8, i8* %144, i64 -112, !dbg !520
  %145 = bitcast i8* %add.ptr127 to %struct.uv_fs_event_s*, !dbg !520
  store %struct.uv_fs_event_s* %145, %struct.uv_fs_event_s** %handle, align 8, !dbg !521
  %146 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !522
  %path128 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %146, i32 0, i32 8, !dbg !523
  %147 = load i8*, i8** %path128, align 8, !dbg !523
  store i8* %147, i8** %tmp_path, align 8, !dbg !524
  %148 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !525
  %path129 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %148, i32 0, i32 8, !dbg !526
  store i8* null, i8** %path129, align 8, !dbg !527
  %149 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !528
  %150 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle, align 8, !dbg !529
  %cb = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %150, i32 0, i32 9, !dbg !530
  %151 = load void (%struct.uv_fs_event_s*, i8*, i32, i32)*, void (%struct.uv_fs_event_s*, i8*, i32, i32)** %cb, align 8, !dbg !530
  %152 = load i8*, i8** %tmp_path, align 8, !dbg !531
  %call130 = call i32 @uv_fs_event_start(%struct.uv_fs_event_s* %149, void (%struct.uv_fs_event_s*, i8*, i32, i32)* %151, i8* %152, i32 0), !dbg !532
  store i32 %call130, i32* %err, align 4, !dbg !533
  %153 = load i8*, i8** %tmp_path, align 8, !dbg !534
  call void @uv__free(i8* %153), !dbg !535
  %154 = load i32, i32* %err, align 4, !dbg !536
  %tobool = icmp ne i32 %154, 0, !dbg !536
  br i1 %tobool, label %if.then131, label %if.end132, !dbg !538

if.then131:                                       ; preds = %do.end126
  %155 = load i32, i32* %err, align 4, !dbg !539
  store i32 %155, i32* %retval, align 4, !dbg !540
  br label %return, !dbg !540

if.end132:                                        ; preds = %do.end126
  br label %while.cond113, !dbg !541

while.end133:                                     ; preds = %while.cond113
  br label %if.end134, !dbg !543

if.end134:                                        ; preds = %while.end133, %entry
  store i32 0, i32* %retval, align 4, !dbg !544
  br label %return, !dbg !544

return:                                           ; preds = %if.end134, %if.then131
  %156 = load i32, i32* %retval, align 4, !dbg !545
  ret i32 %156, !dbg !545
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal %struct.watcher_list* @watcher_root_RB_MINMAX(%struct.watcher_root* %head, i32 %val) #0 !dbg !323 {
entry:
  %head.addr = alloca %struct.watcher_root*, align 8
  %val.addr = alloca i32, align 4
  %tmp = alloca %struct.watcher_list*, align 8
  %parent = alloca %struct.watcher_list*, align 8
  store %struct.watcher_root* %head, %struct.watcher_root** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_root** %head.addr, metadata !546, metadata !368), !dbg !547
  store i32 %val, i32* %val.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %val.addr, metadata !548, metadata !368), !dbg !547
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %tmp, metadata !549, metadata !368), !dbg !547
  %0 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !547
  %rbh_root = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %0, i32 0, i32 0, !dbg !547
  %1 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root, align 8, !dbg !547
  store %struct.watcher_list* %1, %struct.watcher_list** %tmp, align 8, !dbg !547
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %parent, metadata !550, metadata !368), !dbg !547
  store %struct.watcher_list* null, %struct.watcher_list** %parent, align 8, !dbg !547
  br label %while.cond, !dbg !547

while.cond:                                       ; preds = %if.end, %entry
  %2 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !551
  %tobool = icmp ne %struct.watcher_list* %2, null, !dbg !551
  br i1 %tobool, label %while.body, label %while.end, !dbg !551

while.body:                                       ; preds = %while.cond
  %3 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !553
  store %struct.watcher_list* %3, %struct.watcher_list** %parent, align 8, !dbg !553
  %4 = load i32, i32* %val.addr, align 4, !dbg !553
  %cmp = icmp slt i32 %4, 0, !dbg !553
  br i1 %cmp, label %if.then, label %if.else, !dbg !553

if.then:                                          ; preds = %while.body
  %5 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !556
  %entry2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %5, i32 0, i32 0, !dbg !556
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry2, i32 0, i32 0, !dbg !556
  %6 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !556
  store %struct.watcher_list* %6, %struct.watcher_list** %tmp, align 8, !dbg !556
  br label %if.end, !dbg !556

if.else:                                          ; preds = %while.body
  %7 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !559
  %entry3 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %7, i32 0, i32 0, !dbg !559
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry3, i32 0, i32 1, !dbg !559
  %8 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !559
  store %struct.watcher_list* %8, %struct.watcher_list** %tmp, align 8, !dbg !559
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !dbg !561

while.end:                                        ; preds = %while.cond
  %9 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !563
  ret %struct.watcher_list* %9, !dbg !563
}

; Function Attrs: nounwind uwtable
define internal %struct.watcher_list* @watcher_root_RB_NEXT(%struct.watcher_list* %elm) #0 !dbg !326 {
entry:
  %elm.addr = alloca %struct.watcher_list*, align 8
  store %struct.watcher_list* %elm, %struct.watcher_list** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %elm.addr, metadata !565, metadata !368), !dbg !566
  %0 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !567
  %entry1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %0, i32 0, i32 0, !dbg !567
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry1, i32 0, i32 1, !dbg !567
  %1 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !567
  %tobool = icmp ne %struct.watcher_list* %1, null, !dbg !567
  br i1 %tobool, label %if.then, label %if.else, !dbg !566

if.then:                                          ; preds = %entry
  %2 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !569
  %entry2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %2, i32 0, i32 0, !dbg !569
  %rbe_right3 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry2, i32 0, i32 1, !dbg !569
  %3 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right3, align 8, !dbg !569
  store %struct.watcher_list* %3, %struct.watcher_list** %elm.addr, align 8, !dbg !569
  br label %while.cond, !dbg !569

while.cond:                                       ; preds = %while.body, %if.then
  %4 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !572
  %entry4 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %4, i32 0, i32 0, !dbg !572
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry4, i32 0, i32 0, !dbg !572
  %5 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !572
  %tobool5 = icmp ne %struct.watcher_list* %5, null, !dbg !572
  br i1 %tobool5, label %while.body, label %while.end, !dbg !572

while.body:                                       ; preds = %while.cond
  %6 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !574
  %entry6 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %6, i32 0, i32 0, !dbg !574
  %rbe_left7 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry6, i32 0, i32 0, !dbg !574
  %7 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left7, align 8, !dbg !574
  store %struct.watcher_list* %7, %struct.watcher_list** %elm.addr, align 8, !dbg !574
  br label %while.cond, !dbg !574

while.end:                                        ; preds = %while.cond
  br label %if.end33, !dbg !576

if.else:                                          ; preds = %entry
  %8 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !578
  %entry8 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %8, i32 0, i32 0, !dbg !578
  %rbe_parent = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry8, i32 0, i32 2, !dbg !578
  %9 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent, align 8, !dbg !578
  %tobool9 = icmp ne %struct.watcher_list* %9, null, !dbg !578
  br i1 %tobool9, label %land.lhs.true, label %if.else17, !dbg !578

land.lhs.true:                                    ; preds = %if.else
  %10 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !582
  %11 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !582
  %entry10 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %11, i32 0, i32 0, !dbg !582
  %rbe_parent11 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry10, i32 0, i32 2, !dbg !582
  %12 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent11, align 8, !dbg !582
  %entry12 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %12, i32 0, i32 0, !dbg !582
  %rbe_left13 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry12, i32 0, i32 0, !dbg !582
  %13 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left13, align 8, !dbg !582
  %cmp = icmp eq %struct.watcher_list* %10, %13, !dbg !582
  br i1 %cmp, label %if.then14, label %if.else17, !dbg !582

if.then14:                                        ; preds = %land.lhs.true
  %14 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !584
  %entry15 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %14, i32 0, i32 0, !dbg !584
  %rbe_parent16 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry15, i32 0, i32 2, !dbg !584
  %15 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent16, align 8, !dbg !584
  store %struct.watcher_list* %15, %struct.watcher_list** %elm.addr, align 8, !dbg !584
  br label %if.end, !dbg !584

if.else17:                                        ; preds = %land.lhs.true, %if.else
  br label %while.cond18, !dbg !586

while.cond18:                                     ; preds = %while.body27, %if.else17
  %16 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !589
  %entry19 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %16, i32 0, i32 0, !dbg !589
  %rbe_parent20 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry19, i32 0, i32 2, !dbg !589
  %17 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent20, align 8, !dbg !589
  %tobool21 = icmp ne %struct.watcher_list* %17, null, !dbg !589
  br i1 %tobool21, label %land.rhs, label %land.end, !dbg !589

land.rhs:                                         ; preds = %while.cond18
  %18 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !591
  %19 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !591
  %entry22 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %19, i32 0, i32 0, !dbg !591
  %rbe_parent23 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry22, i32 0, i32 2, !dbg !591
  %20 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent23, align 8, !dbg !591
  %entry24 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %20, i32 0, i32 0, !dbg !591
  %rbe_right25 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry24, i32 0, i32 1, !dbg !591
  %21 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right25, align 8, !dbg !591
  %cmp26 = icmp eq %struct.watcher_list* %18, %21, !dbg !591
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond18
  %22 = phi i1 [ false, %while.cond18 ], [ %cmp26, %land.rhs ]
  br i1 %22, label %while.body27, label %while.end30, !dbg !593

while.body27:                                     ; preds = %land.end
  %23 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !595
  %entry28 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %23, i32 0, i32 0, !dbg !595
  %rbe_parent29 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry28, i32 0, i32 2, !dbg !595
  %24 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent29, align 8, !dbg !595
  store %struct.watcher_list* %24, %struct.watcher_list** %elm.addr, align 8, !dbg !595
  br label %while.cond18, !dbg !595

while.end30:                                      ; preds = %land.end
  %25 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !597
  %entry31 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %25, i32 0, i32 0, !dbg !597
  %rbe_parent32 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry31, i32 0, i32 2, !dbg !597
  %26 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent32, align 8, !dbg !597
  store %struct.watcher_list* %26, %struct.watcher_list** %elm.addr, align 8, !dbg !597
  br label %if.end

if.end:                                           ; preds = %while.end30, %if.then14
  br label %if.end33

if.end33:                                         ; preds = %if.end, %while.end
  %27 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !599
  ret %struct.watcher_list* %27, !dbg !599
}

declare i8* @uv__strdup(i8*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind uwtable
define i32 @uv_fs_event_stop(%struct.uv_fs_event_s* %handle) #0 !dbg !317 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_fs_event_s*, align 8
  %w = alloca %struct.watcher_list*, align 8
  store %struct.uv_fs_event_s* %handle, %struct.uv_fs_event_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %handle.addr, metadata !601, metadata !368), !dbg !602
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %w, metadata !603, metadata !368), !dbg !604
  %0 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !605
  %flags = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %0, i32 0, i32 7, !dbg !605
  %1 = load i32, i32* %flags, align 8, !dbg !605
  %and = and i32 %1, 16384, !dbg !605
  %cmp = icmp ne i32 %and, 0, !dbg !605
  br i1 %cmp, label %if.end, label %if.then, !dbg !607

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !608
  br label %return, !dbg !608

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !609
  %loop = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %2, i32 0, i32 1, !dbg !610
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !610
  %4 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !611
  %wd = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %4, i32 0, i32 11, !dbg !612
  %5 = load i32, i32* %wd, align 8, !dbg !612
  %call = call %struct.watcher_list* @find_watcher(%struct.uv_loop_s* %3, i32 %5), !dbg !613
  store %struct.watcher_list* %call, %struct.watcher_list** %w, align 8, !dbg !614
  %6 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !615
  %cmp1 = icmp ne %struct.watcher_list* %6, null, !dbg !615
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !615

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !616

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 337, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.uv_fs_event_stop, i32 0, i32 0)) #8, !dbg !618
  unreachable, !dbg !618
                                                  ; No predecessors!
  br label %cond.end, !dbg !620

cond.end:                                         ; preds = %7, %cond.true
  %8 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !622
  %wd2 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %8, i32 0, i32 11, !dbg !623
  store i32 -1, i32* %wd2, align 8, !dbg !624
  %9 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !625
  %path = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %9, i32 0, i32 8, !dbg !626
  store i8* null, i8** %path, align 8, !dbg !627
  br label %do.body, !dbg !628

do.body:                                          ; preds = %cond.end
  %10 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !629
  %flags3 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %10, i32 0, i32 7, !dbg !629
  %11 = load i32, i32* %flags3, align 8, !dbg !629
  %and4 = and i32 %11, 0, !dbg !629
  %cmp5 = icmp eq i32 %and4, 0, !dbg !629
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !629

cond.true6:                                       ; preds = %do.body
  br label %cond.end8, !dbg !632

cond.false7:                                      ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 341, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.uv_fs_event_stop, i32 0, i32 0)) #8, !dbg !634
  unreachable, !dbg !634
                                                  ; No predecessors!
  br label %cond.end8, !dbg !636

cond.end8:                                        ; preds = %12, %cond.true6
  %13 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !638
  %flags9 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %13, i32 0, i32 7, !dbg !638
  %14 = load i32, i32* %flags9, align 8, !dbg !638
  %and10 = and i32 %14, 16384, !dbg !638
  %cmp11 = icmp eq i32 %and10, 0, !dbg !638
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !638

if.then12:                                        ; preds = %cond.end8
  br label %do.end23, !dbg !641

if.end13:                                         ; preds = %cond.end8
  %15 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !643
  %flags14 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %15, i32 0, i32 7, !dbg !643
  %16 = load i32, i32* %flags14, align 8, !dbg !643
  %and15 = and i32 %16, -16385, !dbg !643
  store i32 %and15, i32* %flags14, align 8, !dbg !643
  %17 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !643
  %flags16 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %17, i32 0, i32 7, !dbg !643
  %18 = load i32, i32* %flags16, align 8, !dbg !643
  %and17 = and i32 %18, 8192, !dbg !643
  %cmp18 = icmp ne i32 %and17, 0, !dbg !643
  br i1 %cmp18, label %if.then19, label %if.end22, !dbg !643

if.then19:                                        ; preds = %if.end13
  br label %do.body20, !dbg !645

do.body20:                                        ; preds = %if.then19
  %19 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !648
  %loop21 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %19, i32 0, i32 1, !dbg !648
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop21, align 8, !dbg !648
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 1, !dbg !648
  %21 = load i32, i32* %active_handles, align 8, !dbg !648
  %dec = add i32 %21, -1, !dbg !648
  store i32 %dec, i32* %active_handles, align 8, !dbg !648
  br label %do.end, !dbg !648

do.end:                                           ; preds = %do.body20
  br label %if.end22, !dbg !651

if.end22:                                         ; preds = %do.end, %if.end13
  br label %do.end23, !dbg !653

do.end23:                                         ; preds = %if.end22, %if.then12
  br label %do.body24, !dbg !655

do.body24:                                        ; preds = %do.end23
  %22 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !656
  %watchers = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %22, i32 0, i32 10, !dbg !656
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers, i64 0, i64 0, !dbg !656
  %23 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !656
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !656
  %25 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !656
  %watchers25 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %25, i32 0, i32 10, !dbg !656
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers25, i64 0, i64 1, !dbg !656
  %26 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !656
  %27 = load [2 x i8*]*, [2 x i8*]** %26, align 8, !dbg !656
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %27, i64 0, i64 0, !dbg !656
  %28 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !656
  store [2 x i8*]* %24, [2 x i8*]** %28, align 8, !dbg !656
  %29 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !656
  %watchers28 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %29, i32 0, i32 10, !dbg !656
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers28, i64 0, i64 1, !dbg !656
  %30 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !656
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 8, !dbg !656
  %32 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !656
  %watchers30 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %32, i32 0, i32 10, !dbg !656
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers30, i64 0, i64 0, !dbg !656
  %33 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !656
  %34 = load [2 x i8*]*, [2 x i8*]** %33, align 8, !dbg !656
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %34, i64 0, i64 1, !dbg !656
  %35 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !656
  store [2 x i8*]* %31, [2 x i8*]** %35, align 8, !dbg !656
  br label %do.end33, !dbg !656

do.end33:                                         ; preds = %do.body24
  %36 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !659
  %37 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !660
  %loop34 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %37, i32 0, i32 1, !dbg !661
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop34, align 8, !dbg !661
  call void @maybe_free_watcher_list(%struct.watcher_list* %36, %struct.uv_loop_s* %38), !dbg !662
  store i32 0, i32* %retval, align 4, !dbg !663
  br label %return, !dbg !663

return:                                           ; preds = %do.end33, %if.then
  %39 = load i32, i32* %retval, align 4, !dbg !664
  ret i32 %39, !dbg !664
}

; Function Attrs: nounwind uwtable
define internal void @maybe_free_watcher_list(%struct.watcher_list* %w, %struct.uv_loop_s* %loop) #0 !dbg !329 {
entry:
  %w.addr = alloca %struct.watcher_list*, align 8
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.watcher_list* %w, %struct.watcher_list** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %w.addr, metadata !665, metadata !368), !dbg !666
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !667, metadata !368), !dbg !668
  %0 = load %struct.watcher_list*, %struct.watcher_list** %w.addr, align 8, !dbg !669
  %iterating = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %0, i32 0, i32 2, !dbg !671
  %1 = load i32, i32* %iterating, align 8, !dbg !671
  %tobool = icmp ne i32 %1, 0, !dbg !669
  br i1 %tobool, label %if.end, label %land.lhs.true, !dbg !672

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.watcher_list*, %struct.watcher_list** %w.addr, align 8, !dbg !673
  %watchers = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %2, i32 0, i32 1, !dbg !673
  %3 = load %struct.watcher_list*, %struct.watcher_list** %w.addr, align 8, !dbg !673
  %watchers1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %3, i32 0, i32 1, !dbg !673
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers1, i64 0, i64 0, !dbg !673
  %4 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !673
  %5 = load [2 x i8*]*, [2 x i8*]** %4, align 8, !dbg !673
  %cmp = icmp eq [2 x i8*]* %watchers, %5, !dbg !673
  br i1 %cmp, label %if.then, label %if.end, !dbg !675

if.then:                                          ; preds = %land.lhs.true
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !676
  %inotify_watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 33, !dbg !676
  %7 = bitcast i8** %inotify_watchers to %struct.watcher_root*, !dbg !676
  %8 = load %struct.watcher_list*, %struct.watcher_list** %w.addr, align 8, !dbg !676
  %call = call %struct.watcher_list* @watcher_root_RB_REMOVE(%struct.watcher_root* %7, %struct.watcher_list* %8), !dbg !676
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !678
  %inotify_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 34, !dbg !679
  %10 = load i32, i32* %inotify_fd, align 8, !dbg !679
  %11 = load %struct.watcher_list*, %struct.watcher_list** %w.addr, align 8, !dbg !680
  %wd = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %11, i32 0, i32 4, !dbg !681
  %12 = load i32, i32* %wd, align 8, !dbg !681
  %call2 = call i32 @uv__inotify_rm_watch(i32 %10, i32 %12), !dbg !682
  %13 = load %struct.watcher_list*, %struct.watcher_list** %w.addr, align 8, !dbg !683
  %14 = bitcast %struct.watcher_list* %13 to i8*, !dbg !683
  call void @uv__free(i8* %14), !dbg !684
  br label %if.end, !dbg !685

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret void, !dbg !686
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_event_start(%struct.uv_fs_event_s* %handle, void (%struct.uv_fs_event_s*, i8*, i32, i32)* %cb, i8* %path, i32 %flags) #0 !dbg !314 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_fs_event_s*, align 8
  %cb.addr = alloca void (%struct.uv_fs_event_s*, i8*, i32, i32)*, align 8
  %path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %w = alloca %struct.watcher_list*, align 8
  %events = alloca i32, align 4
  %err = alloca i32, align 4
  %wd = alloca i32, align 4
  store %struct.uv_fs_event_s* %handle, %struct.uv_fs_event_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %handle.addr, metadata !687, metadata !368), !dbg !688
  store void (%struct.uv_fs_event_s*, i8*, i32, i32)* %cb, void (%struct.uv_fs_event_s*, i8*, i32, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_event_s*, i8*, i32, i32)** %cb.addr, metadata !689, metadata !368), !dbg !690
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !691, metadata !368), !dbg !692
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !693, metadata !368), !dbg !694
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %w, metadata !695, metadata !368), !dbg !696
  call void @llvm.dbg.declare(metadata i32* %events, metadata !697, metadata !368), !dbg !698
  call void @llvm.dbg.declare(metadata i32* %err, metadata !699, metadata !368), !dbg !700
  call void @llvm.dbg.declare(metadata i32* %wd, metadata !701, metadata !368), !dbg !702
  %0 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !703
  %flags1 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %0, i32 0, i32 7, !dbg !703
  %1 = load i32, i32* %flags1, align 8, !dbg !703
  %and = and i32 %1, 16384, !dbg !703
  %cmp = icmp ne i32 %and, 0, !dbg !703
  br i1 %cmp, label %if.then, label %if.end, !dbg !705

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !706
  br label %return, !dbg !706

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !707
  %loop = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %2, i32 0, i32 1, !dbg !708
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !708
  %call = call i32 @init_inotify(%struct.uv_loop_s* %3), !dbg !709
  store i32 %call, i32* %err, align 4, !dbg !710
  %4 = load i32, i32* %err, align 4, !dbg !711
  %tobool = icmp ne i32 %4, 0, !dbg !711
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !713

if.then2:                                         ; preds = %if.end
  %5 = load i32, i32* %err, align 4, !dbg !714
  store i32 %5, i32* %retval, align 4, !dbg !715
  br label %return, !dbg !715

if.end3:                                          ; preds = %if.end
  store i32 4038, i32* %events, align 4, !dbg !716
  %6 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !717
  %loop4 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %6, i32 0, i32 1, !dbg !718
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop4, align 8, !dbg !718
  %inotify_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 34, !dbg !719
  %8 = load i32, i32* %inotify_fd, align 8, !dbg !719
  %9 = load i8*, i8** %path.addr, align 8, !dbg !720
  %10 = load i32, i32* %events, align 4, !dbg !721
  %call5 = call i32 @uv__inotify_add_watch(i32 %8, i8* %9, i32 %10), !dbg !722
  store i32 %call5, i32* %wd, align 4, !dbg !723
  %11 = load i32, i32* %wd, align 4, !dbg !724
  %cmp6 = icmp eq i32 %11, -1, !dbg !726
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !727

if.then7:                                         ; preds = %if.end3
  %call8 = call i32* @__errno_location() #1, !dbg !728
  %12 = load i32, i32* %call8, align 4, !dbg !728
  %sub = sub nsw i32 0, %12, !dbg !729
  store i32 %sub, i32* %retval, align 4, !dbg !730
  br label %return, !dbg !730

if.end9:                                          ; preds = %if.end3
  %13 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !731
  %loop10 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %13, i32 0, i32 1, !dbg !732
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop10, align 8, !dbg !732
  %15 = load i32, i32* %wd, align 4, !dbg !733
  %call11 = call %struct.watcher_list* @find_watcher(%struct.uv_loop_s* %14, i32 %15), !dbg !734
  store %struct.watcher_list* %call11, %struct.watcher_list** %w, align 8, !dbg !735
  %16 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !736
  %tobool12 = icmp ne %struct.watcher_list* %16, null, !dbg !736
  br i1 %tobool12, label %if.then13, label %if.end14, !dbg !738

if.then13:                                        ; preds = %if.end9
  br label %no_insert, !dbg !739

if.end14:                                         ; preds = %if.end9
  %17 = load i8*, i8** %path.addr, align 8, !dbg !740
  %call15 = call i64 @strlen(i8* %17) #9, !dbg !741
  %add = add i64 72, %call15, !dbg !742
  %add16 = add i64 %add, 1, !dbg !743
  %call17 = call i8* @uv__malloc(i64 %add16), !dbg !744
  %18 = bitcast i8* %call17 to %struct.watcher_list*, !dbg !746
  store %struct.watcher_list* %18, %struct.watcher_list** %w, align 8, !dbg !747
  %19 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !748
  %cmp18 = icmp eq %struct.watcher_list* %19, null, !dbg !750
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !751

if.then19:                                        ; preds = %if.end14
  store i32 -12, i32* %retval, align 4, !dbg !752
  br label %return, !dbg !752

if.end20:                                         ; preds = %if.end14
  %20 = load i32, i32* %wd, align 4, !dbg !753
  %21 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !754
  %wd21 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %21, i32 0, i32 4, !dbg !755
  store i32 %20, i32* %wd21, align 8, !dbg !756
  %22 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !757
  %add.ptr = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %22, i64 1, !dbg !758
  %23 = bitcast %struct.watcher_list* %add.ptr to i8*, !dbg !759
  %24 = load i8*, i8** %path.addr, align 8, !dbg !760
  %call22 = call i8* @strcpy(i8* %23, i8* %24) #10, !dbg !761
  %25 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !762
  %path23 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %25, i32 0, i32 3, !dbg !763
  store i8* %call22, i8** %path23, align 8, !dbg !764
  br label %do.body, !dbg !765

do.body:                                          ; preds = %if.end20
  %26 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !766
  %watchers = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %26, i32 0, i32 1, !dbg !766
  %27 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !766
  %watchers24 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %27, i32 0, i32 1, !dbg !766
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers24, i64 0, i64 0, !dbg !766
  %28 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !766
  store [2 x i8*]* %watchers, [2 x i8*]** %28, align 8, !dbg !766
  %29 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !766
  %watchers25 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %29, i32 0, i32 1, !dbg !766
  %30 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !766
  %watchers26 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %30, i32 0, i32 1, !dbg !766
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers26, i64 0, i64 1, !dbg !766
  %31 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !766
  store [2 x i8*]* %watchers25, [2 x i8*]** %31, align 8, !dbg !766
  br label %do.end, !dbg !766

do.end:                                           ; preds = %do.body
  %32 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !769
  %iterating = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %32, i32 0, i32 2, !dbg !770
  store i32 0, i32* %iterating, align 8, !dbg !771
  %33 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !772
  %loop28 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %33, i32 0, i32 1, !dbg !772
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop28, align 8, !dbg !772
  %inotify_watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 33, !dbg !772
  %35 = bitcast i8** %inotify_watchers to %struct.watcher_root*, !dbg !772
  %36 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !772
  %call29 = call %struct.watcher_list* @watcher_root_RB_INSERT(%struct.watcher_root* %35, %struct.watcher_list* %36), !dbg !772
  br label %no_insert, !dbg !772

no_insert:                                        ; preds = %do.end, %if.then13
  br label %do.body30, !dbg !773

do.body30:                                        ; preds = %no_insert
  %37 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !774
  %flags31 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %37, i32 0, i32 7, !dbg !774
  %38 = load i32, i32* %flags31, align 8, !dbg !774
  %and32 = and i32 %38, 0, !dbg !774
  %cmp33 = icmp eq i32 %and32, 0, !dbg !774
  br i1 %cmp33, label %cond.true, label %cond.false, !dbg !774

cond.true:                                        ; preds = %do.body30
  br label %cond.end, !dbg !777

cond.false:                                       ; preds = %do.body30
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 320, i8* getelementptr inbounds ([83 x i8], [83 x i8]* @__PRETTY_FUNCTION__.uv_fs_event_start, i32 0, i32 0)) #8, !dbg !779
  unreachable, !dbg !779
                                                  ; No predecessors!
  br label %cond.end, !dbg !781

cond.end:                                         ; preds = %39, %cond.true
  %40 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !783
  %flags34 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %40, i32 0, i32 7, !dbg !783
  %41 = load i32, i32* %flags34, align 8, !dbg !783
  %and35 = and i32 %41, 16384, !dbg !783
  %cmp36 = icmp ne i32 %and35, 0, !dbg !783
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !783

if.then37:                                        ; preds = %cond.end
  br label %do.end48, !dbg !786

if.end38:                                         ; preds = %cond.end
  %42 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !788
  %flags39 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %42, i32 0, i32 7, !dbg !788
  %43 = load i32, i32* %flags39, align 8, !dbg !788
  %or = or i32 %43, 16384, !dbg !788
  store i32 %or, i32* %flags39, align 8, !dbg !788
  %44 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !788
  %flags40 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %44, i32 0, i32 7, !dbg !788
  %45 = load i32, i32* %flags40, align 8, !dbg !788
  %and41 = and i32 %45, 8192, !dbg !788
  %cmp42 = icmp ne i32 %and41, 0, !dbg !788
  br i1 %cmp42, label %if.then43, label %if.end47, !dbg !788

if.then43:                                        ; preds = %if.end38
  br label %do.body44, !dbg !790

do.body44:                                        ; preds = %if.then43
  %46 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !793
  %loop45 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %46, i32 0, i32 1, !dbg !793
  %47 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop45, align 8, !dbg !793
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %47, i32 0, i32 1, !dbg !793
  %48 = load i32, i32* %active_handles, align 8, !dbg !793
  %inc = add i32 %48, 1, !dbg !793
  store i32 %inc, i32* %active_handles, align 8, !dbg !793
  br label %do.end46, !dbg !793

do.end46:                                         ; preds = %do.body44
  br label %if.end47, !dbg !796

if.end47:                                         ; preds = %do.end46, %if.end38
  br label %do.end48, !dbg !798

do.end48:                                         ; preds = %if.end47, %if.then37
  br label %do.body49, !dbg !800

do.body49:                                        ; preds = %do.end48
  %49 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !801
  %watchers50 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %49, i32 0, i32 1, !dbg !801
  %50 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !801
  %watchers51 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %50, i32 0, i32 10, !dbg !801
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers51, i64 0, i64 0, !dbg !801
  %51 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %watchers50, [2 x i8*]** %51, align 8, !dbg !801
  %52 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !801
  %watchers53 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %52, i32 0, i32 1, !dbg !801
  %arrayidx54 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers53, i64 0, i64 1, !dbg !801
  %53 = bitcast i8** %arrayidx54 to [2 x i8*]**, !dbg !801
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !801
  %55 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !801
  %watchers55 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %55, i32 0, i32 10, !dbg !801
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers55, i64 0, i64 1, !dbg !801
  %56 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %54, [2 x i8*]** %56, align 8, !dbg !801
  %57 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !801
  %watchers57 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %57, i32 0, i32 10, !dbg !801
  %58 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !801
  %watchers58 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %58, i32 0, i32 10, !dbg !801
  %arrayidx59 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers58, i64 0, i64 1, !dbg !801
  %59 = bitcast i8** %arrayidx59 to [2 x i8*]**, !dbg !801
  %60 = load [2 x i8*]*, [2 x i8*]** %59, align 8, !dbg !801
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 0, !dbg !801
  %61 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %watchers57, [2 x i8*]** %61, align 8, !dbg !801
  %62 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !801
  %watchers61 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %62, i32 0, i32 10, !dbg !801
  %63 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !801
  %watchers62 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %63, i32 0, i32 1, !dbg !801
  %arrayidx63 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers62, i64 0, i64 1, !dbg !801
  %64 = bitcast i8** %arrayidx63 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %watchers61, [2 x i8*]** %64, align 8, !dbg !801
  br label %do.end64, !dbg !801

do.end64:                                         ; preds = %do.body49
  %65 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !804
  %path65 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %65, i32 0, i32 3, !dbg !805
  %66 = load i8*, i8** %path65, align 8, !dbg !805
  %67 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !806
  %path66 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %67, i32 0, i32 8, !dbg !807
  store i8* %66, i8** %path66, align 8, !dbg !808
  %68 = load void (%struct.uv_fs_event_s*, i8*, i32, i32)*, void (%struct.uv_fs_event_s*, i8*, i32, i32)** %cb.addr, align 8, !dbg !809
  %69 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !810
  %cb67 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %69, i32 0, i32 9, !dbg !811
  store void (%struct.uv_fs_event_s*, i8*, i32, i32)* %68, void (%struct.uv_fs_event_s*, i8*, i32, i32)** %cb67, align 8, !dbg !812
  %70 = load i32, i32* %wd, align 4, !dbg !813
  %71 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !814
  %wd68 = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %71, i32 0, i32 11, !dbg !815
  store i32 %70, i32* %wd68, align 8, !dbg !816
  store i32 0, i32* %retval, align 4, !dbg !817
  br label %return, !dbg !817

return:                                           ; preds = %do.end64, %if.then19, %if.then7, %if.then2, %if.then
  %72 = load i32, i32* %retval, align 4, !dbg !818
  ret i32 %72, !dbg !818
}

declare void @uv__free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_fs_event_init(%struct.uv_loop_s* %loop, %struct.uv_fs_event_s* %handle) #0 !dbg !311 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_fs_event_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !819, metadata !368), !dbg !820
  store %struct.uv_fs_event_s* %handle, %struct.uv_fs_event_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %handle.addr, metadata !821, metadata !368), !dbg !822
  br label %do.body, !dbg !823

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !824
  %1 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !824
  %2 = bitcast %struct.uv_fs_event_s* %1 to %struct.uv_handle_s*, !dbg !824
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !824
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !824
  %3 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !824
  %4 = bitcast %struct.uv_fs_event_s* %3 to %struct.uv_handle_s*, !dbg !824
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !824
  store i32 3, i32* %type, align 8, !dbg !824
  %5 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !824
  %6 = bitcast %struct.uv_fs_event_s* %5 to %struct.uv_handle_s*, !dbg !824
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !824
  store i32 8192, i32* %flags, align 8, !dbg !824
  br label %do.body2, !dbg !824

do.body2:                                         ; preds = %do.body
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !827
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 2, !dbg !827
  %8 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !827
  %9 = bitcast %struct.uv_fs_event_s* %8 to %struct.uv_handle_s*, !dbg !827
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 4, !dbg !827
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !827
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !827
  store [2 x i8*]* %handle_queue, [2 x i8*]** %10, align 8, !dbg !827
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !827
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 2, !dbg !827
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !827
  %12 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !827
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !827
  %14 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !827
  %15 = bitcast %struct.uv_fs_event_s* %14 to %struct.uv_handle_s*, !dbg !827
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 4, !dbg !827
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !827
  %16 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !827
  store [2 x i8*]* %13, [2 x i8*]** %16, align 8, !dbg !827
  %17 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !827
  %18 = bitcast %struct.uv_fs_event_s* %17 to %struct.uv_handle_s*, !dbg !827
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !827
  %19 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !827
  %20 = bitcast %struct.uv_fs_event_s* %19 to %struct.uv_handle_s*, !dbg !827
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 4, !dbg !827
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !827
  %21 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !827
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !827
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !827
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !827
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %23, align 8, !dbg !827
  %24 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !827
  %25 = bitcast %struct.uv_fs_event_s* %24 to %struct.uv_handle_s*, !dbg !827
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !827
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !827
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 2, !dbg !827
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !827
  %27 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !827
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %27, align 8, !dbg !827
  br label %do.end, !dbg !827

do.end:                                           ; preds = %do.body2
  %28 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !830
  %29 = bitcast %struct.uv_fs_event_s* %28 to %struct.uv_handle_s*, !dbg !830
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 6, !dbg !830
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !830
  br label %do.end15, !dbg !830

do.end15:                                         ; preds = %do.end
  ret i32 0, !dbg !832
}

; Function Attrs: nounwind uwtable
define internal i32 @init_inotify(%struct.uv_loop_s* %loop) #0 !dbg !338 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !833, metadata !368), !dbg !834
  call void @llvm.dbg.declare(metadata i32* %err, metadata !835, metadata !368), !dbg !836
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !837
  %inotify_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 34, !dbg !839
  %1 = load i32, i32* %inotify_fd, align 8, !dbg !839
  %cmp = icmp ne i32 %1, -1, !dbg !840
  br i1 %cmp, label %if.then, label %if.end, !dbg !841

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !842
  br label %return, !dbg !842

if.end:                                           ; preds = %entry
  %call = call i32 @new_inotify_fd(), !dbg !843
  store i32 %call, i32* %err, align 4, !dbg !844
  %2 = load i32, i32* %err, align 4, !dbg !845
  %cmp1 = icmp slt i32 %2, 0, !dbg !847
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !848

if.then2:                                         ; preds = %if.end
  %3 = load i32, i32* %err, align 4, !dbg !849
  store i32 %3, i32* %retval, align 4, !dbg !850
  br label %return, !dbg !850

if.end3:                                          ; preds = %if.end
  %4 = load i32, i32* %err, align 4, !dbg !851
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !852
  %inotify_fd4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 34, !dbg !853
  store i32 %4, i32* %inotify_fd4, align 8, !dbg !854
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !855
  %inotify_read_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 32, !dbg !856
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !857
  %inotify_fd5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 34, !dbg !858
  %8 = load i32, i32* %inotify_fd5, align 8, !dbg !858
  call void @uv__io_init(%struct.uv__io_s* %inotify_read_watcher, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__inotify_read, i32 %8), !dbg !859
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !860
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !861
  %inotify_read_watcher6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 32, !dbg !862
  call void @uv__io_start(%struct.uv_loop_s* %9, %struct.uv__io_s* %inotify_read_watcher6, i32 1), !dbg !863
  store i32 0, i32* %retval, align 4, !dbg !864
  br label %return, !dbg !864

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !865
  ret i32 %11, !dbg !865
}

declare i32 @uv__inotify_add_watch(i32, i8*, i32) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind uwtable
define internal %struct.watcher_list* @find_watcher(%struct.uv_loop_s* %loop, i32 %wd) #0 !dbg !351 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %wd.addr = alloca i32, align 4
  %w = alloca %struct.watcher_list, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !866, metadata !368), !dbg !867
  store i32 %wd, i32* %wd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %wd.addr, metadata !868, metadata !368), !dbg !869
  call void @llvm.dbg.declare(metadata %struct.watcher_list* %w, metadata !870, metadata !368), !dbg !871
  %0 = load i32, i32* %wd.addr, align 4, !dbg !872
  %wd1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %w, i32 0, i32 4, !dbg !873
  store i32 %0, i32* %wd1, align 8, !dbg !874
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !875
  %inotify_watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 33, !dbg !875
  %2 = bitcast i8** %inotify_watchers to %struct.watcher_root*, !dbg !875
  %call = call %struct.watcher_list* @watcher_root_RB_FIND(%struct.watcher_root* %2, %struct.watcher_list* %w), !dbg !875
  ret %struct.watcher_list* %call, !dbg !876
}

declare i8* @uv__malloc(i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #5

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #6

; Function Attrs: nounwind uwtable
define internal %struct.watcher_list* @watcher_root_RB_INSERT(%struct.watcher_root* %head, %struct.watcher_list* %elm) #0 !dbg !360 {
entry:
  %retval = alloca %struct.watcher_list*, align 8
  %head.addr = alloca %struct.watcher_root*, align 8
  %elm.addr = alloca %struct.watcher_list*, align 8
  %tmp = alloca %struct.watcher_list*, align 8
  %parent = alloca %struct.watcher_list*, align 8
  %comp = alloca i32, align 4
  store %struct.watcher_root* %head, %struct.watcher_root** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_root** %head.addr, metadata !877, metadata !368), !dbg !878
  store %struct.watcher_list* %elm, %struct.watcher_list** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %elm.addr, metadata !879, metadata !368), !dbg !878
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %tmp, metadata !880, metadata !368), !dbg !878
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %parent, metadata !881, metadata !368), !dbg !878
  store %struct.watcher_list* null, %struct.watcher_list** %parent, align 8, !dbg !878
  call void @llvm.dbg.declare(metadata i32* %comp, metadata !882, metadata !368), !dbg !878
  store i32 0, i32* %comp, align 4, !dbg !878
  %0 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !878
  %rbh_root = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %0, i32 0, i32 0, !dbg !878
  %1 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root, align 8, !dbg !878
  store %struct.watcher_list* %1, %struct.watcher_list** %tmp, align 8, !dbg !878
  br label %while.cond, !dbg !878

while.cond:                                       ; preds = %if.end8, %entry
  %2 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !883
  %tobool = icmp ne %struct.watcher_list* %2, null, !dbg !883
  br i1 %tobool, label %while.body, label %while.end, !dbg !883

while.body:                                       ; preds = %while.cond
  %3 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !885
  store %struct.watcher_list* %3, %struct.watcher_list** %parent, align 8, !dbg !885
  %4 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !885
  %5 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !885
  %call = call i32 @compare_watchers(%struct.watcher_list* %4, %struct.watcher_list* %5), !dbg !885
  store i32 %call, i32* %comp, align 4, !dbg !885
  %6 = load i32, i32* %comp, align 4, !dbg !885
  %cmp = icmp slt i32 %6, 0, !dbg !885
  br i1 %cmp, label %if.then, label %if.else, !dbg !885

if.then:                                          ; preds = %while.body
  %7 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !888
  %entry3 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %7, i32 0, i32 0, !dbg !888
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry3, i32 0, i32 0, !dbg !888
  %8 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !888
  store %struct.watcher_list* %8, %struct.watcher_list** %tmp, align 8, !dbg !888
  br label %if.end8, !dbg !888

if.else:                                          ; preds = %while.body
  %9 = load i32, i32* %comp, align 4, !dbg !891
  %cmp4 = icmp sgt i32 %9, 0, !dbg !891
  br i1 %cmp4, label %if.then5, label %if.else7, !dbg !891

if.then5:                                         ; preds = %if.else
  %10 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !894
  %entry6 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %10, i32 0, i32 0, !dbg !894
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry6, i32 0, i32 1, !dbg !894
  %11 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !894
  store %struct.watcher_list* %11, %struct.watcher_list** %tmp, align 8, !dbg !894
  br label %if.end, !dbg !894

if.else7:                                         ; preds = %if.else
  %12 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !896
  store %struct.watcher_list* %12, %struct.watcher_list** %retval, align 8, !dbg !896
  br label %return, !dbg !896

if.end:                                           ; preds = %if.then5
  br label %if.end8

if.end8:                                          ; preds = %if.end, %if.then
  br label %while.cond, !dbg !898

while.end:                                        ; preds = %while.cond
  br label %do.body, !dbg !900

do.body:                                          ; preds = %while.end
  %13 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !902
  %14 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !902
  %entry9 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %14, i32 0, i32 0, !dbg !902
  %rbe_parent = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry9, i32 0, i32 2, !dbg !902
  store %struct.watcher_list* %13, %struct.watcher_list** %rbe_parent, align 8, !dbg !902
  %15 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !902
  %entry10 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %15, i32 0, i32 0, !dbg !902
  %rbe_right11 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry10, i32 0, i32 1, !dbg !902
  store %struct.watcher_list* null, %struct.watcher_list** %rbe_right11, align 8, !dbg !902
  %16 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !902
  %entry12 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %16, i32 0, i32 0, !dbg !902
  %rbe_left13 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry12, i32 0, i32 0, !dbg !902
  store %struct.watcher_list* null, %struct.watcher_list** %rbe_left13, align 8, !dbg !902
  %17 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !902
  %entry14 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %17, i32 0, i32 0, !dbg !902
  %rbe_color = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry14, i32 0, i32 3, !dbg !902
  store i32 1, i32* %rbe_color, align 8, !dbg !902
  br label %do.end, !dbg !902

do.end:                                           ; preds = %do.body
  %18 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !905
  %cmp15 = icmp ne %struct.watcher_list* %18, null, !dbg !905
  br i1 %cmp15, label %if.then16, label %if.else27, !dbg !905

if.then16:                                        ; preds = %do.end
  %19 = load i32, i32* %comp, align 4, !dbg !908
  %cmp17 = icmp slt i32 %19, 0, !dbg !908
  br i1 %cmp17, label %if.then18, label %if.else21, !dbg !908

if.then18:                                        ; preds = %if.then16
  %20 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !912
  %21 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !912
  %entry19 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %21, i32 0, i32 0, !dbg !912
  %rbe_left20 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry19, i32 0, i32 0, !dbg !912
  store %struct.watcher_list* %20, %struct.watcher_list** %rbe_left20, align 8, !dbg !912
  br label %if.end24, !dbg !912

if.else21:                                        ; preds = %if.then16
  %22 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !914
  %23 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !914
  %entry22 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %23, i32 0, i32 0, !dbg !914
  %rbe_right23 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry22, i32 0, i32 1, !dbg !914
  store %struct.watcher_list* %22, %struct.watcher_list** %rbe_right23, align 8, !dbg !914
  br label %if.end24

if.end24:                                         ; preds = %if.else21, %if.then18
  br label %do.body25, !dbg !916

do.body25:                                        ; preds = %if.end24
  br label %do.end26, !dbg !918

do.end26:                                         ; preds = %do.body25
  br label %if.end29, !dbg !921

if.else27:                                        ; preds = %do.end
  %24 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !923
  %25 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !923
  %rbh_root28 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %25, i32 0, i32 0, !dbg !923
  store %struct.watcher_list* %24, %struct.watcher_list** %rbh_root28, align 8, !dbg !923
  br label %if.end29

if.end29:                                         ; preds = %if.else27, %do.end26
  %26 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !925
  %27 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !925
  call void @watcher_root_RB_INSERT_COLOR(%struct.watcher_root* %26, %struct.watcher_list* %27), !dbg !925
  store %struct.watcher_list* null, %struct.watcher_list** %retval, align 8, !dbg !925
  br label %return, !dbg !925

return:                                           ; preds = %if.end29, %if.else7
  %28 = load %struct.watcher_list*, %struct.watcher_list** %retval, align 8, !dbg !927
  ret %struct.watcher_list* %28, !dbg !927
}

; Function Attrs: nounwind uwtable
define void @uv__fs_event_close(%struct.uv_fs_event_s* %handle) #0 !dbg !320 {
entry:
  %handle.addr = alloca %struct.uv_fs_event_s*, align 8
  store %struct.uv_fs_event_s* %handle, %struct.uv_fs_event_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %handle.addr, metadata !929, metadata !368), !dbg !930
  %0 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %handle.addr, align 8, !dbg !931
  %call = call i32 @uv_fs_event_stop(%struct.uv_fs_event_s* %0), !dbg !932
  ret void, !dbg !933
}

; Function Attrs: nounwind uwtable
define internal %struct.watcher_list* @watcher_root_RB_REMOVE(%struct.watcher_root* %head, %struct.watcher_list* %elm) #0 !dbg !332 {
entry:
  %head.addr = alloca %struct.watcher_root*, align 8
  %elm.addr = alloca %struct.watcher_list*, align 8
  %child = alloca %struct.watcher_list*, align 8
  %parent = alloca %struct.watcher_list*, align 8
  %old = alloca %struct.watcher_list*, align 8
  %color = alloca i32, align 4
  %left = alloca %struct.watcher_list*, align 8
  store %struct.watcher_root* %head, %struct.watcher_root** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_root** %head.addr, metadata !934, metadata !368), !dbg !935
  store %struct.watcher_list* %elm, %struct.watcher_list** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %elm.addr, metadata !936, metadata !368), !dbg !935
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %child, metadata !937, metadata !368), !dbg !935
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %parent, metadata !938, metadata !368), !dbg !935
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %old, metadata !939, metadata !368), !dbg !935
  %0 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !935
  store %struct.watcher_list* %0, %struct.watcher_list** %old, align 8, !dbg !935
  call void @llvm.dbg.declare(metadata i32* %color, metadata !940, metadata !368), !dbg !935
  %1 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !941
  %entry1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %1, i32 0, i32 0, !dbg !941
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry1, i32 0, i32 0, !dbg !941
  %2 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !941
  %cmp = icmp eq %struct.watcher_list* %2, null, !dbg !941
  br i1 %cmp, label %if.then, label %if.else, !dbg !935

if.then:                                          ; preds = %entry
  %3 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !943
  %entry2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %3, i32 0, i32 0, !dbg !943
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry2, i32 0, i32 1, !dbg !943
  %4 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !943
  store %struct.watcher_list* %4, %struct.watcher_list** %child, align 8, !dbg !943
  br label %if.end92, !dbg !943

if.else:                                          ; preds = %entry
  %5 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !945
  %entry3 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %5, i32 0, i32 0, !dbg !945
  %rbe_right4 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry3, i32 0, i32 1, !dbg !945
  %6 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right4, align 8, !dbg !945
  %cmp5 = icmp eq %struct.watcher_list* %6, null, !dbg !945
  br i1 %cmp5, label %if.then6, label %if.else9, !dbg !945

if.then6:                                         ; preds = %if.else
  %7 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !948
  %entry7 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %7, i32 0, i32 0, !dbg !948
  %rbe_left8 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry7, i32 0, i32 0, !dbg !948
  %8 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left8, align 8, !dbg !948
  store %struct.watcher_list* %8, %struct.watcher_list** %child, align 8, !dbg !948
  br label %if.end91, !dbg !948

if.else9:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %left, metadata !950, metadata !368), !dbg !952
  %9 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !953
  %entry10 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %9, i32 0, i32 0, !dbg !953
  %rbe_right11 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry10, i32 0, i32 1, !dbg !953
  %10 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right11, align 8, !dbg !953
  store %struct.watcher_list* %10, %struct.watcher_list** %elm.addr, align 8, !dbg !953
  br label %while.cond, !dbg !953

while.cond:                                       ; preds = %while.body, %if.else9
  %11 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !955
  %entry12 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %11, i32 0, i32 0, !dbg !955
  %rbe_left13 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry12, i32 0, i32 0, !dbg !955
  %12 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left13, align 8, !dbg !955
  store %struct.watcher_list* %12, %struct.watcher_list** %left, align 8, !dbg !955
  %cmp14 = icmp ne %struct.watcher_list* %12, null, !dbg !955
  br i1 %cmp14, label %while.body, label %while.end, !dbg !955

while.body:                                       ; preds = %while.cond
  %13 = load %struct.watcher_list*, %struct.watcher_list** %left, align 8, !dbg !957
  store %struct.watcher_list* %13, %struct.watcher_list** %elm.addr, align 8, !dbg !957
  br label %while.cond, !dbg !957

while.end:                                        ; preds = %while.cond
  %14 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !959
  %entry15 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %14, i32 0, i32 0, !dbg !959
  %rbe_right16 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry15, i32 0, i32 1, !dbg !959
  %15 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right16, align 8, !dbg !959
  store %struct.watcher_list* %15, %struct.watcher_list** %child, align 8, !dbg !959
  %16 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !959
  %entry17 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %16, i32 0, i32 0, !dbg !959
  %rbe_parent = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry17, i32 0, i32 2, !dbg !959
  %17 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent, align 8, !dbg !959
  store %struct.watcher_list* %17, %struct.watcher_list** %parent, align 8, !dbg !959
  %18 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !959
  %entry18 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %18, i32 0, i32 0, !dbg !959
  %rbe_color = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry18, i32 0, i32 3, !dbg !959
  %19 = load i32, i32* %rbe_color, align 8, !dbg !959
  store i32 %19, i32* %color, align 4, !dbg !959
  %20 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !959
  %tobool = icmp ne %struct.watcher_list* %20, null, !dbg !959
  br i1 %tobool, label %if.then19, label %if.end, !dbg !959

if.then19:                                        ; preds = %while.end
  %21 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !961
  %22 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !961
  %entry20 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %22, i32 0, i32 0, !dbg !961
  %rbe_parent21 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry20, i32 0, i32 2, !dbg !961
  store %struct.watcher_list* %21, %struct.watcher_list** %rbe_parent21, align 8, !dbg !961
  br label %if.end, !dbg !961

if.end:                                           ; preds = %if.then19, %while.end
  %23 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !964
  %tobool22 = icmp ne %struct.watcher_list* %23, null, !dbg !964
  br i1 %tobool22, label %if.then23, label %if.else34, !dbg !964

if.then23:                                        ; preds = %if.end
  %24 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !967
  %entry24 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %24, i32 0, i32 0, !dbg !967
  %rbe_left25 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry24, i32 0, i32 0, !dbg !967
  %25 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left25, align 8, !dbg !967
  %26 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !967
  %cmp26 = icmp eq %struct.watcher_list* %25, %26, !dbg !967
  br i1 %cmp26, label %if.then27, label %if.else30, !dbg !967

if.then27:                                        ; preds = %if.then23
  %27 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !971
  %28 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !971
  %entry28 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %28, i32 0, i32 0, !dbg !971
  %rbe_left29 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry28, i32 0, i32 0, !dbg !971
  store %struct.watcher_list* %27, %struct.watcher_list** %rbe_left29, align 8, !dbg !971
  br label %if.end33, !dbg !971

if.else30:                                        ; preds = %if.then23
  %29 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !973
  %30 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !973
  %entry31 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %30, i32 0, i32 0, !dbg !973
  %rbe_right32 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry31, i32 0, i32 1, !dbg !973
  store %struct.watcher_list* %29, %struct.watcher_list** %rbe_right32, align 8, !dbg !973
  br label %if.end33

if.end33:                                         ; preds = %if.else30, %if.then27
  br label %do.body, !dbg !975

do.body:                                          ; preds = %if.end33
  br label %do.end, !dbg !977

do.end:                                           ; preds = %do.body
  br label %if.end35, !dbg !980

if.else34:                                        ; preds = %if.end
  %31 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !982
  %32 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !982
  %rbh_root = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %32, i32 0, i32 0, !dbg !982
  store %struct.watcher_list* %31, %struct.watcher_list** %rbh_root, align 8, !dbg !982
  br label %if.end35

if.end35:                                         ; preds = %if.else34, %do.end
  %33 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !984
  %entry36 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %33, i32 0, i32 0, !dbg !984
  %rbe_parent37 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry36, i32 0, i32 2, !dbg !984
  %34 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent37, align 8, !dbg !984
  %35 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !984
  %cmp38 = icmp eq %struct.watcher_list* %34, %35, !dbg !984
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !984

if.then39:                                        ; preds = %if.end35
  %36 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !987
  store %struct.watcher_list* %36, %struct.watcher_list** %parent, align 8, !dbg !987
  br label %if.end40, !dbg !987

if.end40:                                         ; preds = %if.then39, %if.end35
  %37 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !989
  %entry41 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %37, i32 0, i32 0, !dbg !989
  %38 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !989
  %entry42 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %38, i32 0, i32 0, !dbg !989
  %39 = bitcast %struct.anon.4* %entry41 to i8*, !dbg !989
  %40 = bitcast %struct.anon.4* %entry42 to i8*, !dbg !989
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %39, i8* %40, i64 32, i32 8, i1 false), !dbg !989
  %41 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !989
  %entry43 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %41, i32 0, i32 0, !dbg !989
  %rbe_parent44 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry43, i32 0, i32 2, !dbg !989
  %42 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent44, align 8, !dbg !989
  %tobool45 = icmp ne %struct.watcher_list* %42, null, !dbg !989
  br i1 %tobool45, label %if.then46, label %if.else65, !dbg !989

if.then46:                                        ; preds = %if.end40
  %43 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !991
  %entry47 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %43, i32 0, i32 0, !dbg !991
  %rbe_parent48 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry47, i32 0, i32 2, !dbg !991
  %44 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent48, align 8, !dbg !991
  %entry49 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %44, i32 0, i32 0, !dbg !991
  %rbe_left50 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry49, i32 0, i32 0, !dbg !991
  %45 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left50, align 8, !dbg !991
  %46 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !991
  %cmp51 = icmp eq %struct.watcher_list* %45, %46, !dbg !991
  br i1 %cmp51, label %if.then52, label %if.else57, !dbg !991

if.then52:                                        ; preds = %if.then46
  %47 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !996
  %48 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !996
  %entry53 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %48, i32 0, i32 0, !dbg !996
  %rbe_parent54 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry53, i32 0, i32 2, !dbg !996
  %49 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent54, align 8, !dbg !996
  %entry55 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %49, i32 0, i32 0, !dbg !996
  %rbe_left56 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry55, i32 0, i32 0, !dbg !996
  store %struct.watcher_list* %47, %struct.watcher_list** %rbe_left56, align 8, !dbg !996
  br label %if.end62, !dbg !996

if.else57:                                        ; preds = %if.then46
  %50 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !998
  %51 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !998
  %entry58 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %51, i32 0, i32 0, !dbg !998
  %rbe_parent59 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry58, i32 0, i32 2, !dbg !998
  %52 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent59, align 8, !dbg !998
  %entry60 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %52, i32 0, i32 0, !dbg !998
  %rbe_right61 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry60, i32 0, i32 1, !dbg !998
  store %struct.watcher_list* %50, %struct.watcher_list** %rbe_right61, align 8, !dbg !998
  br label %if.end62

if.end62:                                         ; preds = %if.else57, %if.then52
  br label %do.body63, !dbg !1000

do.body63:                                        ; preds = %if.end62
  br label %do.end64, !dbg !1002

do.end64:                                         ; preds = %do.body63
  br label %if.end67, !dbg !1005

if.else65:                                        ; preds = %if.end40
  %53 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1007
  %54 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1007
  %rbh_root66 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %54, i32 0, i32 0, !dbg !1007
  store %struct.watcher_list* %53, %struct.watcher_list** %rbh_root66, align 8, !dbg !1007
  br label %if.end67

if.end67:                                         ; preds = %if.else65, %do.end64
  %55 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1009
  %56 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !1009
  %entry68 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %56, i32 0, i32 0, !dbg !1009
  %rbe_left69 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry68, i32 0, i32 0, !dbg !1009
  %57 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left69, align 8, !dbg !1009
  %entry70 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %57, i32 0, i32 0, !dbg !1009
  %rbe_parent71 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry70, i32 0, i32 2, !dbg !1009
  store %struct.watcher_list* %55, %struct.watcher_list** %rbe_parent71, align 8, !dbg !1009
  %58 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !1009
  %entry72 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %58, i32 0, i32 0, !dbg !1009
  %rbe_right73 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry72, i32 0, i32 1, !dbg !1009
  %59 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right73, align 8, !dbg !1009
  %tobool74 = icmp ne %struct.watcher_list* %59, null, !dbg !1009
  br i1 %tobool74, label %if.then75, label %if.end80, !dbg !1009

if.then75:                                        ; preds = %if.end67
  %60 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1011
  %61 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !1011
  %entry76 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %61, i32 0, i32 0, !dbg !1011
  %rbe_right77 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry76, i32 0, i32 1, !dbg !1011
  %62 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right77, align 8, !dbg !1011
  %entry78 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %62, i32 0, i32 0, !dbg !1011
  %rbe_parent79 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry78, i32 0, i32 2, !dbg !1011
  store %struct.watcher_list* %60, %struct.watcher_list** %rbe_parent79, align 8, !dbg !1011
  br label %if.end80, !dbg !1011

if.end80:                                         ; preds = %if.then75, %if.end67
  %63 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1014
  %tobool81 = icmp ne %struct.watcher_list* %63, null, !dbg !1014
  br i1 %tobool81, label %if.then82, label %if.end90, !dbg !1014

if.then82:                                        ; preds = %if.end80
  %64 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1017
  store %struct.watcher_list* %64, %struct.watcher_list** %left, align 8, !dbg !1017
  br label %do.body83, !dbg !1017

do.body83:                                        ; preds = %do.cond, %if.then82
  br label %do.body84, !dbg !1020

do.body84:                                        ; preds = %do.body83
  br label %do.end85, !dbg !1023

do.end85:                                         ; preds = %do.body84
  br label %do.cond, !dbg !1026

do.cond:                                          ; preds = %do.end85
  %65 = load %struct.watcher_list*, %struct.watcher_list** %left, align 8, !dbg !1028
  %entry86 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %65, i32 0, i32 0, !dbg !1028
  %rbe_parent87 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry86, i32 0, i32 2, !dbg !1028
  %66 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent87, align 8, !dbg !1028
  store %struct.watcher_list* %66, %struct.watcher_list** %left, align 8, !dbg !1028
  %cmp88 = icmp ne %struct.watcher_list* %66, null, !dbg !1028
  br i1 %cmp88, label %do.body83, label %do.end89, !dbg !1028

do.end89:                                         ; preds = %do.cond
  br label %if.end90, !dbg !1030

if.end90:                                         ; preds = %do.end89, %if.end80
  br label %color120, !dbg !1032

if.end91:                                         ; preds = %if.then6
  br label %if.end92

if.end92:                                         ; preds = %if.end91, %if.then
  %67 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1034
  %entry93 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %67, i32 0, i32 0, !dbg !1034
  %rbe_parent94 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry93, i32 0, i32 2, !dbg !1034
  %68 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent94, align 8, !dbg !1034
  store %struct.watcher_list* %68, %struct.watcher_list** %parent, align 8, !dbg !1034
  %69 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1034
  %entry95 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %69, i32 0, i32 0, !dbg !1034
  %rbe_color96 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry95, i32 0, i32 3, !dbg !1034
  %70 = load i32, i32* %rbe_color96, align 8, !dbg !1034
  store i32 %70, i32* %color, align 4, !dbg !1034
  %71 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !1034
  %tobool97 = icmp ne %struct.watcher_list* %71, null, !dbg !1034
  br i1 %tobool97, label %if.then98, label %if.end101, !dbg !1034

if.then98:                                        ; preds = %if.end92
  %72 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1036
  %73 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !1036
  %entry99 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %73, i32 0, i32 0, !dbg !1036
  %rbe_parent100 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry99, i32 0, i32 2, !dbg !1036
  store %struct.watcher_list* %72, %struct.watcher_list** %rbe_parent100, align 8, !dbg !1036
  br label %if.end101, !dbg !1036

if.end101:                                        ; preds = %if.then98, %if.end92
  %74 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1039
  %tobool102 = icmp ne %struct.watcher_list* %74, null, !dbg !1039
  br i1 %tobool102, label %if.then103, label %if.else117, !dbg !1039

if.then103:                                       ; preds = %if.end101
  %75 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1042
  %entry104 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %75, i32 0, i32 0, !dbg !1042
  %rbe_left105 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry104, i32 0, i32 0, !dbg !1042
  %76 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left105, align 8, !dbg !1042
  %77 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1042
  %cmp106 = icmp eq %struct.watcher_list* %76, %77, !dbg !1042
  br i1 %cmp106, label %if.then107, label %if.else110, !dbg !1042

if.then107:                                       ; preds = %if.then103
  %78 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !1046
  %79 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1046
  %entry108 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %79, i32 0, i32 0, !dbg !1046
  %rbe_left109 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry108, i32 0, i32 0, !dbg !1046
  store %struct.watcher_list* %78, %struct.watcher_list** %rbe_left109, align 8, !dbg !1046
  br label %if.end113, !dbg !1046

if.else110:                                       ; preds = %if.then103
  %80 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !1048
  %81 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1048
  %entry111 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %81, i32 0, i32 0, !dbg !1048
  %rbe_right112 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry111, i32 0, i32 1, !dbg !1048
  store %struct.watcher_list* %80, %struct.watcher_list** %rbe_right112, align 8, !dbg !1048
  br label %if.end113

if.end113:                                        ; preds = %if.else110, %if.then107
  br label %do.body114, !dbg !1050

do.body114:                                       ; preds = %if.end113
  br label %do.end116, !dbg !1052

do.end116:                                        ; preds = %do.body114
  br label %if.end119, !dbg !1055

if.else117:                                       ; preds = %if.end101
  %82 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !1057
  %83 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1057
  %rbh_root118 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %83, i32 0, i32 0, !dbg !1057
  store %struct.watcher_list* %82, %struct.watcher_list** %rbh_root118, align 8, !dbg !1057
  br label %if.end119

if.end119:                                        ; preds = %if.else117, %do.end116
  br label %color120, !dbg !1059

color120:                                         ; preds = %if.end119, %if.end90
  %84 = load i32, i32* %color, align 4, !dbg !1061
  %cmp121 = icmp eq i32 %84, 0, !dbg !1061
  br i1 %cmp121, label %if.then122, label %if.end123, !dbg !1061

if.then122:                                       ; preds = %color120
  %85 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1064
  %86 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1064
  %87 = load %struct.watcher_list*, %struct.watcher_list** %child, align 8, !dbg !1064
  call void @watcher_root_RB_REMOVE_COLOR(%struct.watcher_root* %85, %struct.watcher_list* %86, %struct.watcher_list* %87), !dbg !1064
  br label %if.end123, !dbg !1064

if.end123:                                        ; preds = %if.then122, %color120
  %88 = load %struct.watcher_list*, %struct.watcher_list** %old, align 8, !dbg !1066
  ret %struct.watcher_list* %88, !dbg !1066
}

declare i32 @uv__inotify_rm_watch(i32, i32) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #7

; Function Attrs: nounwind uwtable
define internal void @watcher_root_RB_REMOVE_COLOR(%struct.watcher_root* %head, %struct.watcher_list* %parent, %struct.watcher_list* %elm) #0 !dbg !335 {
entry:
  %head.addr = alloca %struct.watcher_root*, align 8
  %parent.addr = alloca %struct.watcher_list*, align 8
  %elm.addr = alloca %struct.watcher_list*, align 8
  %tmp = alloca %struct.watcher_list*, align 8
  %oleft = alloca %struct.watcher_list*, align 8
  %oright = alloca %struct.watcher_list*, align 8
  store %struct.watcher_root* %head, %struct.watcher_root** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_root** %head.addr, metadata !1068, metadata !368), !dbg !1069
  store %struct.watcher_list* %parent, %struct.watcher_list** %parent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %parent.addr, metadata !1070, metadata !368), !dbg !1069
  store %struct.watcher_list* %elm, %struct.watcher_list** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %elm.addr, metadata !1071, metadata !368), !dbg !1069
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %tmp, metadata !1072, metadata !368), !dbg !1069
  br label %while.cond, !dbg !1069

while.cond:                                       ; preds = %if.end489, %entry
  %0 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1073
  %cmp = icmp eq %struct.watcher_list* %0, null, !dbg !1073
  br i1 %cmp, label %land.rhs, label %lor.lhs.false, !dbg !1073

lor.lhs.false:                                    ; preds = %while.cond
  %1 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1075
  %entry1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %1, i32 0, i32 0, !dbg !1075
  %rbe_color = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry1, i32 0, i32 3, !dbg !1075
  %2 = load i32, i32* %rbe_color, align 8, !dbg !1075
  %cmp2 = icmp eq i32 %2, 0, !dbg !1075
  br i1 %cmp2, label %land.rhs, label %land.end, !dbg !1075

land.rhs:                                         ; preds = %lor.lhs.false, %while.cond
  %3 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1077
  %4 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1077
  %rbh_root = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %4, i32 0, i32 0, !dbg !1077
  %5 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root, align 8, !dbg !1077
  %cmp3 = icmp ne %struct.watcher_list* %3, %5, !dbg !1077
  br label %land.end

land.end:                                         ; preds = %land.rhs, %lor.lhs.false
  %6 = phi i1 [ false, %lor.lhs.false ], [ %cmp3, %land.rhs ]
  br i1 %6, label %while.body, label %while.end, !dbg !1079

while.body:                                       ; preds = %land.end
  %7 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1081
  %entry4 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %7, i32 0, i32 0, !dbg !1081
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry4, i32 0, i32 0, !dbg !1081
  %8 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !1081
  %9 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1081
  %cmp5 = icmp eq %struct.watcher_list* %8, %9, !dbg !1081
  br i1 %cmp5, label %if.then, label %if.else243, !dbg !1081

if.then:                                          ; preds = %while.body
  %10 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1085
  %entry6 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %10, i32 0, i32 0, !dbg !1085
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry6, i32 0, i32 1, !dbg !1085
  %11 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !1085
  store %struct.watcher_list* %11, %struct.watcher_list** %tmp, align 8, !dbg !1085
  %12 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1085
  %entry7 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %12, i32 0, i32 0, !dbg !1085
  %rbe_color8 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry7, i32 0, i32 3, !dbg !1085
  %13 = load i32, i32* %rbe_color8, align 8, !dbg !1085
  %cmp9 = icmp eq i32 %13, 1, !dbg !1085
  br i1 %cmp9, label %if.then10, label %if.end68, !dbg !1085

if.then10:                                        ; preds = %if.then
  br label %do.body, !dbg !1088

do.body:                                          ; preds = %if.then10
  %14 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1092
  %entry11 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %14, i32 0, i32 0, !dbg !1092
  %rbe_color12 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry11, i32 0, i32 3, !dbg !1092
  store i32 0, i32* %rbe_color12, align 8, !dbg !1092
  %15 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1092
  %entry13 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %15, i32 0, i32 0, !dbg !1092
  %rbe_color14 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry13, i32 0, i32 3, !dbg !1092
  store i32 1, i32* %rbe_color14, align 8, !dbg !1092
  br label %do.end, !dbg !1092

do.end:                                           ; preds = %do.body
  br label %do.body15, !dbg !1095

do.body15:                                        ; preds = %do.end
  %16 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1097
  %entry16 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %16, i32 0, i32 0, !dbg !1097
  %rbe_right17 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry16, i32 0, i32 1, !dbg !1097
  %17 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right17, align 8, !dbg !1097
  store %struct.watcher_list* %17, %struct.watcher_list** %tmp, align 8, !dbg !1097
  %18 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1097
  %entry18 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %18, i32 0, i32 0, !dbg !1097
  %rbe_left19 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry18, i32 0, i32 0, !dbg !1097
  %19 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left19, align 8, !dbg !1097
  %20 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1097
  %entry20 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %20, i32 0, i32 0, !dbg !1097
  %rbe_right21 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry20, i32 0, i32 1, !dbg !1097
  store %struct.watcher_list* %19, %struct.watcher_list** %rbe_right21, align 8, !dbg !1097
  %cmp22 = icmp ne %struct.watcher_list* %19, null, !dbg !1097
  br i1 %cmp22, label %if.then23, label %if.end, !dbg !1097

if.then23:                                        ; preds = %do.body15
  %21 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1100
  %22 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1100
  %entry24 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %22, i32 0, i32 0, !dbg !1100
  %rbe_left25 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry24, i32 0, i32 0, !dbg !1100
  %23 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left25, align 8, !dbg !1100
  %entry26 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %23, i32 0, i32 0, !dbg !1100
  %rbe_parent = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry26, i32 0, i32 2, !dbg !1100
  store %struct.watcher_list* %21, %struct.watcher_list** %rbe_parent, align 8, !dbg !1100
  br label %if.end, !dbg !1100

if.end:                                           ; preds = %if.then23, %do.body15
  br label %do.body27, !dbg !1104

do.body27:                                        ; preds = %if.end
  br label %do.end28, !dbg !1106

do.end28:                                         ; preds = %do.body27
  %24 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1109
  %entry29 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %24, i32 0, i32 0, !dbg !1109
  %rbe_parent30 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry29, i32 0, i32 2, !dbg !1109
  %25 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent30, align 8, !dbg !1109
  %26 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1109
  %entry31 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %26, i32 0, i32 0, !dbg !1109
  %rbe_parent32 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry31, i32 0, i32 2, !dbg !1109
  store %struct.watcher_list* %25, %struct.watcher_list** %rbe_parent32, align 8, !dbg !1109
  %cmp33 = icmp ne %struct.watcher_list* %25, null, !dbg !1109
  br i1 %cmp33, label %if.then34, label %if.else50, !dbg !1109

if.then34:                                        ; preds = %do.end28
  %27 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1112
  %28 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1112
  %entry35 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %28, i32 0, i32 0, !dbg !1112
  %rbe_parent36 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry35, i32 0, i32 2, !dbg !1112
  %29 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent36, align 8, !dbg !1112
  %entry37 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %29, i32 0, i32 0, !dbg !1112
  %rbe_left38 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry37, i32 0, i32 0, !dbg !1112
  %30 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left38, align 8, !dbg !1112
  %cmp39 = icmp eq %struct.watcher_list* %27, %30, !dbg !1112
  br i1 %cmp39, label %if.then40, label %if.else, !dbg !1112

if.then40:                                        ; preds = %if.then34
  %31 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1116
  %32 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1116
  %entry41 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %32, i32 0, i32 0, !dbg !1116
  %rbe_parent42 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry41, i32 0, i32 2, !dbg !1116
  %33 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent42, align 8, !dbg !1116
  %entry43 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %33, i32 0, i32 0, !dbg !1116
  %rbe_left44 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry43, i32 0, i32 0, !dbg !1116
  store %struct.watcher_list* %31, %struct.watcher_list** %rbe_left44, align 8, !dbg !1116
  br label %if.end49, !dbg !1116

if.else:                                          ; preds = %if.then34
  %34 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1118
  %35 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1118
  %entry45 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %35, i32 0, i32 0, !dbg !1118
  %rbe_parent46 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry45, i32 0, i32 2, !dbg !1118
  %36 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent46, align 8, !dbg !1118
  %entry47 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %36, i32 0, i32 0, !dbg !1118
  %rbe_right48 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry47, i32 0, i32 1, !dbg !1118
  store %struct.watcher_list* %34, %struct.watcher_list** %rbe_right48, align 8, !dbg !1118
  br label %if.end49

if.end49:                                         ; preds = %if.else, %if.then40
  br label %if.end52, !dbg !1120

if.else50:                                        ; preds = %do.end28
  %37 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1122
  %38 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1122
  %rbh_root51 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %38, i32 0, i32 0, !dbg !1122
  store %struct.watcher_list* %37, %struct.watcher_list** %rbh_root51, align 8, !dbg !1122
  br label %if.end52

if.end52:                                         ; preds = %if.else50, %if.end49
  %39 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1124
  %40 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1124
  %entry53 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %40, i32 0, i32 0, !dbg !1124
  %rbe_left54 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry53, i32 0, i32 0, !dbg !1124
  store %struct.watcher_list* %39, %struct.watcher_list** %rbe_left54, align 8, !dbg !1124
  %41 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1124
  %42 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1124
  %entry55 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %42, i32 0, i32 0, !dbg !1124
  %rbe_parent56 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry55, i32 0, i32 2, !dbg !1124
  store %struct.watcher_list* %41, %struct.watcher_list** %rbe_parent56, align 8, !dbg !1124
  br label %do.body57, !dbg !1124

do.body57:                                        ; preds = %if.end52
  br label %do.end58, !dbg !1126

do.end58:                                         ; preds = %do.body57
  %43 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1129
  %entry59 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %43, i32 0, i32 0, !dbg !1129
  %rbe_parent60 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry59, i32 0, i32 2, !dbg !1129
  %44 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent60, align 8, !dbg !1129
  %tobool = icmp ne %struct.watcher_list* %44, null, !dbg !1129
  br i1 %tobool, label %if.then61, label %if.end64, !dbg !1129

if.then61:                                        ; preds = %do.end58
  br label %do.body62, !dbg !1132

do.body62:                                        ; preds = %if.then61
  br label %do.end63, !dbg !1134

do.end63:                                         ; preds = %do.body62
  br label %if.end64, !dbg !1137

if.end64:                                         ; preds = %do.end63, %do.end58
  br label %do.end65, !dbg !1139

do.end65:                                         ; preds = %if.end64
  %45 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1141
  %entry66 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %45, i32 0, i32 0, !dbg !1141
  %rbe_right67 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry66, i32 0, i32 1, !dbg !1141
  %46 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right67, align 8, !dbg !1141
  store %struct.watcher_list* %46, %struct.watcher_list** %tmp, align 8, !dbg !1141
  br label %if.end68, !dbg !1141

if.end68:                                         ; preds = %do.end65, %if.then
  %47 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1143
  %entry69 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %47, i32 0, i32 0, !dbg !1143
  %rbe_left70 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry69, i32 0, i32 0, !dbg !1143
  %48 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left70, align 8, !dbg !1143
  %cmp71 = icmp eq %struct.watcher_list* %48, null, !dbg !1143
  br i1 %cmp71, label %land.lhs.true, label %lor.lhs.false72, !dbg !1143

lor.lhs.false72:                                  ; preds = %if.end68
  %49 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1146
  %entry73 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %49, i32 0, i32 0, !dbg !1146
  %rbe_left74 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry73, i32 0, i32 0, !dbg !1146
  %50 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left74, align 8, !dbg !1146
  %entry75 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %50, i32 0, i32 0, !dbg !1146
  %rbe_color76 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry75, i32 0, i32 3, !dbg !1146
  %51 = load i32, i32* %rbe_color76, align 8, !dbg !1146
  %cmp77 = icmp eq i32 %51, 0, !dbg !1146
  br i1 %cmp77, label %land.lhs.true, label %if.else92, !dbg !1146

land.lhs.true:                                    ; preds = %lor.lhs.false72, %if.end68
  %52 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1148
  %entry78 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %52, i32 0, i32 0, !dbg !1148
  %rbe_right79 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry78, i32 0, i32 1, !dbg !1148
  %53 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right79, align 8, !dbg !1148
  %cmp80 = icmp eq %struct.watcher_list* %53, null, !dbg !1148
  br i1 %cmp80, label %if.then87, label %lor.lhs.false81, !dbg !1148

lor.lhs.false81:                                  ; preds = %land.lhs.true
  %54 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1150
  %entry82 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %54, i32 0, i32 0, !dbg !1150
  %rbe_right83 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry82, i32 0, i32 1, !dbg !1150
  %55 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right83, align 8, !dbg !1150
  %entry84 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %55, i32 0, i32 0, !dbg !1150
  %rbe_color85 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry84, i32 0, i32 3, !dbg !1150
  %56 = load i32, i32* %rbe_color85, align 8, !dbg !1150
  %cmp86 = icmp eq i32 %56, 0, !dbg !1150
  br i1 %cmp86, label %if.then87, label %if.else92, !dbg !1150

if.then87:                                        ; preds = %lor.lhs.false81, %land.lhs.true
  %57 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1152
  %entry88 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %57, i32 0, i32 0, !dbg !1152
  %rbe_color89 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry88, i32 0, i32 3, !dbg !1152
  store i32 1, i32* %rbe_color89, align 8, !dbg !1152
  %58 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1152
  store %struct.watcher_list* %58, %struct.watcher_list** %elm.addr, align 8, !dbg !1152
  %59 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1152
  %entry90 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %59, i32 0, i32 0, !dbg !1152
  %rbe_parent91 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry90, i32 0, i32 2, !dbg !1152
  %60 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent91, align 8, !dbg !1152
  store %struct.watcher_list* %60, %struct.watcher_list** %parent.addr, align 8, !dbg !1152
  br label %if.end242, !dbg !1152

if.else92:                                        ; preds = %lor.lhs.false81, %lor.lhs.false72
  %61 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1155
  %entry93 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %61, i32 0, i32 0, !dbg !1155
  %rbe_right94 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry93, i32 0, i32 1, !dbg !1155
  %62 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right94, align 8, !dbg !1155
  %cmp95 = icmp eq %struct.watcher_list* %62, null, !dbg !1155
  br i1 %cmp95, label %if.then102, label %lor.lhs.false96, !dbg !1155

lor.lhs.false96:                                  ; preds = %if.else92
  %63 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1159
  %entry97 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %63, i32 0, i32 0, !dbg !1159
  %rbe_right98 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry97, i32 0, i32 1, !dbg !1159
  %64 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right98, align 8, !dbg !1159
  %entry99 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %64, i32 0, i32 0, !dbg !1159
  %rbe_color100 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry99, i32 0, i32 3, !dbg !1159
  %65 = load i32, i32* %rbe_color100, align 8, !dbg !1159
  %cmp101 = icmp eq i32 %65, 0, !dbg !1159
  br i1 %cmp101, label %if.then102, label %if.end170, !dbg !1159

if.then102:                                       ; preds = %lor.lhs.false96, %if.else92
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %oleft, metadata !1161, metadata !368), !dbg !1163
  %66 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1164
  %entry104 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %66, i32 0, i32 0, !dbg !1164
  %rbe_left105 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry104, i32 0, i32 0, !dbg !1164
  %67 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left105, align 8, !dbg !1164
  store %struct.watcher_list* %67, %struct.watcher_list** %oleft, align 8, !dbg !1164
  %cmp106 = icmp ne %struct.watcher_list* %67, null, !dbg !1164
  br i1 %cmp106, label %if.then107, label %if.end110, !dbg !1164

if.then107:                                       ; preds = %if.then102
  %68 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1167
  %entry108 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %68, i32 0, i32 0, !dbg !1167
  %rbe_color109 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry108, i32 0, i32 3, !dbg !1167
  store i32 0, i32* %rbe_color109, align 8, !dbg !1167
  br label %if.end110, !dbg !1167

if.end110:                                        ; preds = %if.then107, %if.then102
  %69 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1169
  %entry111 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %69, i32 0, i32 0, !dbg !1169
  %rbe_color112 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry111, i32 0, i32 3, !dbg !1169
  store i32 1, i32* %rbe_color112, align 8, !dbg !1169
  br label %do.body113, !dbg !1169

do.body113:                                       ; preds = %if.end110
  %70 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1171
  %entry114 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %70, i32 0, i32 0, !dbg !1171
  %rbe_left115 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry114, i32 0, i32 0, !dbg !1171
  %71 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left115, align 8, !dbg !1171
  store %struct.watcher_list* %71, %struct.watcher_list** %oleft, align 8, !dbg !1171
  %72 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1171
  %entry116 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %72, i32 0, i32 0, !dbg !1171
  %rbe_right117 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry116, i32 0, i32 1, !dbg !1171
  %73 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right117, align 8, !dbg !1171
  %74 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1171
  %entry118 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %74, i32 0, i32 0, !dbg !1171
  %rbe_left119 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry118, i32 0, i32 0, !dbg !1171
  store %struct.watcher_list* %73, %struct.watcher_list** %rbe_left119, align 8, !dbg !1171
  %cmp120 = icmp ne %struct.watcher_list* %73, null, !dbg !1171
  br i1 %cmp120, label %if.then121, label %if.end126, !dbg !1171

if.then121:                                       ; preds = %do.body113
  %75 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1174
  %76 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1174
  %entry122 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %76, i32 0, i32 0, !dbg !1174
  %rbe_right123 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry122, i32 0, i32 1, !dbg !1174
  %77 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right123, align 8, !dbg !1174
  %entry124 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %77, i32 0, i32 0, !dbg !1174
  %rbe_parent125 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry124, i32 0, i32 2, !dbg !1174
  store %struct.watcher_list* %75, %struct.watcher_list** %rbe_parent125, align 8, !dbg !1174
  br label %if.end126, !dbg !1174

if.end126:                                        ; preds = %if.then121, %do.body113
  br label %do.body127, !dbg !1178

do.body127:                                       ; preds = %if.end126
  br label %do.end128, !dbg !1180

do.end128:                                        ; preds = %do.body127
  %78 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1183
  %entry129 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %78, i32 0, i32 0, !dbg !1183
  %rbe_parent130 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry129, i32 0, i32 2, !dbg !1183
  %79 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent130, align 8, !dbg !1183
  %80 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1183
  %entry131 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %80, i32 0, i32 0, !dbg !1183
  %rbe_parent132 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry131, i32 0, i32 2, !dbg !1183
  store %struct.watcher_list* %79, %struct.watcher_list** %rbe_parent132, align 8, !dbg !1183
  %cmp133 = icmp ne %struct.watcher_list* %79, null, !dbg !1183
  br i1 %cmp133, label %if.then134, label %if.else151, !dbg !1183

if.then134:                                       ; preds = %do.end128
  %81 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1186
  %82 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1186
  %entry135 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %82, i32 0, i32 0, !dbg !1186
  %rbe_parent136 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry135, i32 0, i32 2, !dbg !1186
  %83 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent136, align 8, !dbg !1186
  %entry137 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %83, i32 0, i32 0, !dbg !1186
  %rbe_left138 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry137, i32 0, i32 0, !dbg !1186
  %84 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left138, align 8, !dbg !1186
  %cmp139 = icmp eq %struct.watcher_list* %81, %84, !dbg !1186
  br i1 %cmp139, label %if.then140, label %if.else145, !dbg !1186

if.then140:                                       ; preds = %if.then134
  %85 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1190
  %86 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1190
  %entry141 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %86, i32 0, i32 0, !dbg !1190
  %rbe_parent142 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry141, i32 0, i32 2, !dbg !1190
  %87 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent142, align 8, !dbg !1190
  %entry143 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %87, i32 0, i32 0, !dbg !1190
  %rbe_left144 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry143, i32 0, i32 0, !dbg !1190
  store %struct.watcher_list* %85, %struct.watcher_list** %rbe_left144, align 8, !dbg !1190
  br label %if.end150, !dbg !1190

if.else145:                                       ; preds = %if.then134
  %88 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1192
  %89 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1192
  %entry146 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %89, i32 0, i32 0, !dbg !1192
  %rbe_parent147 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry146, i32 0, i32 2, !dbg !1192
  %90 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent147, align 8, !dbg !1192
  %entry148 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %90, i32 0, i32 0, !dbg !1192
  %rbe_right149 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry148, i32 0, i32 1, !dbg !1192
  store %struct.watcher_list* %88, %struct.watcher_list** %rbe_right149, align 8, !dbg !1192
  br label %if.end150

if.end150:                                        ; preds = %if.else145, %if.then140
  br label %if.end153, !dbg !1194

if.else151:                                       ; preds = %do.end128
  %91 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1196
  %92 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1196
  %rbh_root152 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %92, i32 0, i32 0, !dbg !1196
  store %struct.watcher_list* %91, %struct.watcher_list** %rbh_root152, align 8, !dbg !1196
  br label %if.end153

if.end153:                                        ; preds = %if.else151, %if.end150
  %93 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1198
  %94 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1198
  %entry154 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %94, i32 0, i32 0, !dbg !1198
  %rbe_right155 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry154, i32 0, i32 1, !dbg !1198
  store %struct.watcher_list* %93, %struct.watcher_list** %rbe_right155, align 8, !dbg !1198
  %95 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1198
  %96 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1198
  %entry156 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %96, i32 0, i32 0, !dbg !1198
  %rbe_parent157 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry156, i32 0, i32 2, !dbg !1198
  store %struct.watcher_list* %95, %struct.watcher_list** %rbe_parent157, align 8, !dbg !1198
  br label %do.body158, !dbg !1198

do.body158:                                       ; preds = %if.end153
  br label %do.end159, !dbg !1200

do.end159:                                        ; preds = %do.body158
  %97 = load %struct.watcher_list*, %struct.watcher_list** %oleft, align 8, !dbg !1203
  %entry160 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %97, i32 0, i32 0, !dbg !1203
  %rbe_parent161 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry160, i32 0, i32 2, !dbg !1203
  %98 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent161, align 8, !dbg !1203
  %tobool162 = icmp ne %struct.watcher_list* %98, null, !dbg !1203
  br i1 %tobool162, label %if.then163, label %if.end166, !dbg !1203

if.then163:                                       ; preds = %do.end159
  br label %do.body164, !dbg !1206

do.body164:                                       ; preds = %if.then163
  br label %do.end165, !dbg !1208

do.end165:                                        ; preds = %do.body164
  br label %if.end166, !dbg !1211

if.end166:                                        ; preds = %do.end165, %do.end159
  br label %do.end167, !dbg !1213

do.end167:                                        ; preds = %if.end166
  %99 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1215
  %entry168 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %99, i32 0, i32 0, !dbg !1215
  %rbe_right169 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry168, i32 0, i32 1, !dbg !1215
  %100 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right169, align 8, !dbg !1215
  store %struct.watcher_list* %100, %struct.watcher_list** %tmp, align 8, !dbg !1215
  br label %if.end170, !dbg !1215

if.end170:                                        ; preds = %do.end167, %lor.lhs.false96
  %101 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1217
  %entry171 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %101, i32 0, i32 0, !dbg !1217
  %rbe_color172 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry171, i32 0, i32 3, !dbg !1217
  %102 = load i32, i32* %rbe_color172, align 8, !dbg !1217
  %103 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1217
  %entry173 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %103, i32 0, i32 0, !dbg !1217
  %rbe_color174 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry173, i32 0, i32 3, !dbg !1217
  store i32 %102, i32* %rbe_color174, align 8, !dbg !1217
  %104 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1217
  %entry175 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %104, i32 0, i32 0, !dbg !1217
  %rbe_color176 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry175, i32 0, i32 3, !dbg !1217
  store i32 0, i32* %rbe_color176, align 8, !dbg !1217
  %105 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1217
  %entry177 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %105, i32 0, i32 0, !dbg !1217
  %rbe_right178 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry177, i32 0, i32 1, !dbg !1217
  %106 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right178, align 8, !dbg !1217
  %tobool179 = icmp ne %struct.watcher_list* %106, null, !dbg !1217
  br i1 %tobool179, label %if.then180, label %if.end185, !dbg !1217

if.then180:                                       ; preds = %if.end170
  %107 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1219
  %entry181 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %107, i32 0, i32 0, !dbg !1219
  %rbe_right182 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry181, i32 0, i32 1, !dbg !1219
  %108 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right182, align 8, !dbg !1219
  %entry183 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %108, i32 0, i32 0, !dbg !1219
  %rbe_color184 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry183, i32 0, i32 3, !dbg !1219
  store i32 0, i32* %rbe_color184, align 8, !dbg !1219
  br label %if.end185, !dbg !1219

if.end185:                                        ; preds = %if.then180, %if.end170
  br label %do.body186, !dbg !1222

do.body186:                                       ; preds = %if.end185
  %109 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1224
  %entry187 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %109, i32 0, i32 0, !dbg !1224
  %rbe_right188 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry187, i32 0, i32 1, !dbg !1224
  %110 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right188, align 8, !dbg !1224
  store %struct.watcher_list* %110, %struct.watcher_list** %tmp, align 8, !dbg !1224
  %111 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1224
  %entry189 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %111, i32 0, i32 0, !dbg !1224
  %rbe_left190 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry189, i32 0, i32 0, !dbg !1224
  %112 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left190, align 8, !dbg !1224
  %113 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1224
  %entry191 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %113, i32 0, i32 0, !dbg !1224
  %rbe_right192 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry191, i32 0, i32 1, !dbg !1224
  store %struct.watcher_list* %112, %struct.watcher_list** %rbe_right192, align 8, !dbg !1224
  %cmp193 = icmp ne %struct.watcher_list* %112, null, !dbg !1224
  br i1 %cmp193, label %if.then194, label %if.end199, !dbg !1224

if.then194:                                       ; preds = %do.body186
  %114 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1227
  %115 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1227
  %entry195 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %115, i32 0, i32 0, !dbg !1227
  %rbe_left196 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry195, i32 0, i32 0, !dbg !1227
  %116 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left196, align 8, !dbg !1227
  %entry197 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %116, i32 0, i32 0, !dbg !1227
  %rbe_parent198 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry197, i32 0, i32 2, !dbg !1227
  store %struct.watcher_list* %114, %struct.watcher_list** %rbe_parent198, align 8, !dbg !1227
  br label %if.end199, !dbg !1227

if.end199:                                        ; preds = %if.then194, %do.body186
  br label %do.body200, !dbg !1231

do.body200:                                       ; preds = %if.end199
  br label %do.end201, !dbg !1233

do.end201:                                        ; preds = %do.body200
  %117 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1236
  %entry202 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %117, i32 0, i32 0, !dbg !1236
  %rbe_parent203 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry202, i32 0, i32 2, !dbg !1236
  %118 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent203, align 8, !dbg !1236
  %119 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1236
  %entry204 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %119, i32 0, i32 0, !dbg !1236
  %rbe_parent205 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry204, i32 0, i32 2, !dbg !1236
  store %struct.watcher_list* %118, %struct.watcher_list** %rbe_parent205, align 8, !dbg !1236
  %cmp206 = icmp ne %struct.watcher_list* %118, null, !dbg !1236
  br i1 %cmp206, label %if.then207, label %if.else224, !dbg !1236

if.then207:                                       ; preds = %do.end201
  %120 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1239
  %121 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1239
  %entry208 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %121, i32 0, i32 0, !dbg !1239
  %rbe_parent209 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry208, i32 0, i32 2, !dbg !1239
  %122 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent209, align 8, !dbg !1239
  %entry210 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %122, i32 0, i32 0, !dbg !1239
  %rbe_left211 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry210, i32 0, i32 0, !dbg !1239
  %123 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left211, align 8, !dbg !1239
  %cmp212 = icmp eq %struct.watcher_list* %120, %123, !dbg !1239
  br i1 %cmp212, label %if.then213, label %if.else218, !dbg !1239

if.then213:                                       ; preds = %if.then207
  %124 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1243
  %125 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1243
  %entry214 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %125, i32 0, i32 0, !dbg !1243
  %rbe_parent215 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry214, i32 0, i32 2, !dbg !1243
  %126 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent215, align 8, !dbg !1243
  %entry216 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %126, i32 0, i32 0, !dbg !1243
  %rbe_left217 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry216, i32 0, i32 0, !dbg !1243
  store %struct.watcher_list* %124, %struct.watcher_list** %rbe_left217, align 8, !dbg !1243
  br label %if.end223, !dbg !1243

if.else218:                                       ; preds = %if.then207
  %127 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1245
  %128 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1245
  %entry219 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %128, i32 0, i32 0, !dbg !1245
  %rbe_parent220 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry219, i32 0, i32 2, !dbg !1245
  %129 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent220, align 8, !dbg !1245
  %entry221 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %129, i32 0, i32 0, !dbg !1245
  %rbe_right222 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry221, i32 0, i32 1, !dbg !1245
  store %struct.watcher_list* %127, %struct.watcher_list** %rbe_right222, align 8, !dbg !1245
  br label %if.end223

if.end223:                                        ; preds = %if.else218, %if.then213
  br label %if.end226, !dbg !1247

if.else224:                                       ; preds = %do.end201
  %130 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1249
  %131 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1249
  %rbh_root225 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %131, i32 0, i32 0, !dbg !1249
  store %struct.watcher_list* %130, %struct.watcher_list** %rbh_root225, align 8, !dbg !1249
  br label %if.end226

if.end226:                                        ; preds = %if.else224, %if.end223
  %132 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1251
  %133 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1251
  %entry227 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %133, i32 0, i32 0, !dbg !1251
  %rbe_left228 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry227, i32 0, i32 0, !dbg !1251
  store %struct.watcher_list* %132, %struct.watcher_list** %rbe_left228, align 8, !dbg !1251
  %134 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1251
  %135 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1251
  %entry229 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %135, i32 0, i32 0, !dbg !1251
  %rbe_parent230 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry229, i32 0, i32 2, !dbg !1251
  store %struct.watcher_list* %134, %struct.watcher_list** %rbe_parent230, align 8, !dbg !1251
  br label %do.body231, !dbg !1251

do.body231:                                       ; preds = %if.end226
  br label %do.end232, !dbg !1253

do.end232:                                        ; preds = %do.body231
  %136 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1256
  %entry233 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %136, i32 0, i32 0, !dbg !1256
  %rbe_parent234 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry233, i32 0, i32 2, !dbg !1256
  %137 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent234, align 8, !dbg !1256
  %tobool235 = icmp ne %struct.watcher_list* %137, null, !dbg !1256
  br i1 %tobool235, label %if.then236, label %if.end239, !dbg !1256

if.then236:                                       ; preds = %do.end232
  br label %do.body237, !dbg !1259

do.body237:                                       ; preds = %if.then236
  br label %do.end238, !dbg !1261

do.end238:                                        ; preds = %do.body237
  br label %if.end239, !dbg !1264

if.end239:                                        ; preds = %do.end238, %do.end232
  br label %do.end240, !dbg !1266

do.end240:                                        ; preds = %if.end239
  %138 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1268
  %rbh_root241 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %138, i32 0, i32 0, !dbg !1268
  %139 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root241, align 8, !dbg !1268
  store %struct.watcher_list* %139, %struct.watcher_list** %elm.addr, align 8, !dbg !1268
  br label %while.end, !dbg !1268

if.end242:                                        ; preds = %if.then87
  br label %if.end489, !dbg !1270

if.else243:                                       ; preds = %while.body
  %140 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1272
  %entry244 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %140, i32 0, i32 0, !dbg !1272
  %rbe_left245 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry244, i32 0, i32 0, !dbg !1272
  %141 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left245, align 8, !dbg !1272
  store %struct.watcher_list* %141, %struct.watcher_list** %tmp, align 8, !dbg !1272
  %142 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1272
  %entry246 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %142, i32 0, i32 0, !dbg !1272
  %rbe_color247 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry246, i32 0, i32 3, !dbg !1272
  %143 = load i32, i32* %rbe_color247, align 8, !dbg !1272
  %cmp248 = icmp eq i32 %143, 1, !dbg !1272
  br i1 %cmp248, label %if.then249, label %if.end313, !dbg !1272

if.then249:                                       ; preds = %if.else243
  br label %do.body250, !dbg !1275

do.body250:                                       ; preds = %if.then249
  %144 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1279
  %entry251 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %144, i32 0, i32 0, !dbg !1279
  %rbe_color252 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry251, i32 0, i32 3, !dbg !1279
  store i32 0, i32* %rbe_color252, align 8, !dbg !1279
  %145 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1279
  %entry253 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %145, i32 0, i32 0, !dbg !1279
  %rbe_color254 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry253, i32 0, i32 3, !dbg !1279
  store i32 1, i32* %rbe_color254, align 8, !dbg !1279
  br label %do.end255, !dbg !1279

do.end255:                                        ; preds = %do.body250
  br label %do.body256, !dbg !1282

do.body256:                                       ; preds = %do.end255
  %146 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1284
  %entry257 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %146, i32 0, i32 0, !dbg !1284
  %rbe_left258 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry257, i32 0, i32 0, !dbg !1284
  %147 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left258, align 8, !dbg !1284
  store %struct.watcher_list* %147, %struct.watcher_list** %tmp, align 8, !dbg !1284
  %148 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1284
  %entry259 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %148, i32 0, i32 0, !dbg !1284
  %rbe_right260 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry259, i32 0, i32 1, !dbg !1284
  %149 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right260, align 8, !dbg !1284
  %150 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1284
  %entry261 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %150, i32 0, i32 0, !dbg !1284
  %rbe_left262 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry261, i32 0, i32 0, !dbg !1284
  store %struct.watcher_list* %149, %struct.watcher_list** %rbe_left262, align 8, !dbg !1284
  %cmp263 = icmp ne %struct.watcher_list* %149, null, !dbg !1284
  br i1 %cmp263, label %if.then264, label %if.end269, !dbg !1284

if.then264:                                       ; preds = %do.body256
  %151 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1287
  %152 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1287
  %entry265 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %152, i32 0, i32 0, !dbg !1287
  %rbe_right266 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry265, i32 0, i32 1, !dbg !1287
  %153 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right266, align 8, !dbg !1287
  %entry267 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %153, i32 0, i32 0, !dbg !1287
  %rbe_parent268 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry267, i32 0, i32 2, !dbg !1287
  store %struct.watcher_list* %151, %struct.watcher_list** %rbe_parent268, align 8, !dbg !1287
  br label %if.end269, !dbg !1287

if.end269:                                        ; preds = %if.then264, %do.body256
  br label %do.body270, !dbg !1291

do.body270:                                       ; preds = %if.end269
  br label %do.end271, !dbg !1293

do.end271:                                        ; preds = %do.body270
  %154 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1296
  %entry272 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %154, i32 0, i32 0, !dbg !1296
  %rbe_parent273 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry272, i32 0, i32 2, !dbg !1296
  %155 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent273, align 8, !dbg !1296
  %156 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1296
  %entry274 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %156, i32 0, i32 0, !dbg !1296
  %rbe_parent275 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry274, i32 0, i32 2, !dbg !1296
  store %struct.watcher_list* %155, %struct.watcher_list** %rbe_parent275, align 8, !dbg !1296
  %cmp276 = icmp ne %struct.watcher_list* %155, null, !dbg !1296
  br i1 %cmp276, label %if.then277, label %if.else294, !dbg !1296

if.then277:                                       ; preds = %do.end271
  %157 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1299
  %158 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1299
  %entry278 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %158, i32 0, i32 0, !dbg !1299
  %rbe_parent279 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry278, i32 0, i32 2, !dbg !1299
  %159 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent279, align 8, !dbg !1299
  %entry280 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %159, i32 0, i32 0, !dbg !1299
  %rbe_left281 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry280, i32 0, i32 0, !dbg !1299
  %160 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left281, align 8, !dbg !1299
  %cmp282 = icmp eq %struct.watcher_list* %157, %160, !dbg !1299
  br i1 %cmp282, label %if.then283, label %if.else288, !dbg !1299

if.then283:                                       ; preds = %if.then277
  %161 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1303
  %162 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1303
  %entry284 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %162, i32 0, i32 0, !dbg !1303
  %rbe_parent285 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry284, i32 0, i32 2, !dbg !1303
  %163 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent285, align 8, !dbg !1303
  %entry286 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %163, i32 0, i32 0, !dbg !1303
  %rbe_left287 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry286, i32 0, i32 0, !dbg !1303
  store %struct.watcher_list* %161, %struct.watcher_list** %rbe_left287, align 8, !dbg !1303
  br label %if.end293, !dbg !1303

if.else288:                                       ; preds = %if.then277
  %164 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1305
  %165 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1305
  %entry289 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %165, i32 0, i32 0, !dbg !1305
  %rbe_parent290 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry289, i32 0, i32 2, !dbg !1305
  %166 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent290, align 8, !dbg !1305
  %entry291 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %166, i32 0, i32 0, !dbg !1305
  %rbe_right292 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry291, i32 0, i32 1, !dbg !1305
  store %struct.watcher_list* %164, %struct.watcher_list** %rbe_right292, align 8, !dbg !1305
  br label %if.end293

if.end293:                                        ; preds = %if.else288, %if.then283
  br label %if.end296, !dbg !1307

if.else294:                                       ; preds = %do.end271
  %167 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1309
  %168 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1309
  %rbh_root295 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %168, i32 0, i32 0, !dbg !1309
  store %struct.watcher_list* %167, %struct.watcher_list** %rbh_root295, align 8, !dbg !1309
  br label %if.end296

if.end296:                                        ; preds = %if.else294, %if.end293
  %169 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1311
  %170 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1311
  %entry297 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %170, i32 0, i32 0, !dbg !1311
  %rbe_right298 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry297, i32 0, i32 1, !dbg !1311
  store %struct.watcher_list* %169, %struct.watcher_list** %rbe_right298, align 8, !dbg !1311
  %171 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1311
  %172 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1311
  %entry299 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %172, i32 0, i32 0, !dbg !1311
  %rbe_parent300 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry299, i32 0, i32 2, !dbg !1311
  store %struct.watcher_list* %171, %struct.watcher_list** %rbe_parent300, align 8, !dbg !1311
  br label %do.body301, !dbg !1311

do.body301:                                       ; preds = %if.end296
  br label %do.end302, !dbg !1313

do.end302:                                        ; preds = %do.body301
  %173 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1316
  %entry303 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %173, i32 0, i32 0, !dbg !1316
  %rbe_parent304 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry303, i32 0, i32 2, !dbg !1316
  %174 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent304, align 8, !dbg !1316
  %tobool305 = icmp ne %struct.watcher_list* %174, null, !dbg !1316
  br i1 %tobool305, label %if.then306, label %if.end309, !dbg !1316

if.then306:                                       ; preds = %do.end302
  br label %do.body307, !dbg !1319

do.body307:                                       ; preds = %if.then306
  br label %do.end308, !dbg !1321

do.end308:                                        ; preds = %do.body307
  br label %if.end309, !dbg !1324

if.end309:                                        ; preds = %do.end308, %do.end302
  br label %do.end310, !dbg !1326

do.end310:                                        ; preds = %if.end309
  %175 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1328
  %entry311 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %175, i32 0, i32 0, !dbg !1328
  %rbe_left312 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry311, i32 0, i32 0, !dbg !1328
  %176 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left312, align 8, !dbg !1328
  store %struct.watcher_list* %176, %struct.watcher_list** %tmp, align 8, !dbg !1328
  br label %if.end313, !dbg !1328

if.end313:                                        ; preds = %do.end310, %if.else243
  %177 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1330
  %entry314 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %177, i32 0, i32 0, !dbg !1330
  %rbe_left315 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry314, i32 0, i32 0, !dbg !1330
  %178 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left315, align 8, !dbg !1330
  %cmp316 = icmp eq %struct.watcher_list* %178, null, !dbg !1330
  br i1 %cmp316, label %land.lhs.true323, label %lor.lhs.false317, !dbg !1330

lor.lhs.false317:                                 ; preds = %if.end313
  %179 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1333
  %entry318 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %179, i32 0, i32 0, !dbg !1333
  %rbe_left319 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry318, i32 0, i32 0, !dbg !1333
  %180 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left319, align 8, !dbg !1333
  %entry320 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %180, i32 0, i32 0, !dbg !1333
  %rbe_color321 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry320, i32 0, i32 3, !dbg !1333
  %181 = load i32, i32* %rbe_color321, align 8, !dbg !1333
  %cmp322 = icmp eq i32 %181, 0, !dbg !1333
  br i1 %cmp322, label %land.lhs.true323, label %if.else338, !dbg !1333

land.lhs.true323:                                 ; preds = %lor.lhs.false317, %if.end313
  %182 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1335
  %entry324 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %182, i32 0, i32 0, !dbg !1335
  %rbe_right325 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry324, i32 0, i32 1, !dbg !1335
  %183 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right325, align 8, !dbg !1335
  %cmp326 = icmp eq %struct.watcher_list* %183, null, !dbg !1335
  br i1 %cmp326, label %if.then333, label %lor.lhs.false327, !dbg !1335

lor.lhs.false327:                                 ; preds = %land.lhs.true323
  %184 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1337
  %entry328 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %184, i32 0, i32 0, !dbg !1337
  %rbe_right329 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry328, i32 0, i32 1, !dbg !1337
  %185 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right329, align 8, !dbg !1337
  %entry330 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %185, i32 0, i32 0, !dbg !1337
  %rbe_color331 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry330, i32 0, i32 3, !dbg !1337
  %186 = load i32, i32* %rbe_color331, align 8, !dbg !1337
  %cmp332 = icmp eq i32 %186, 0, !dbg !1337
  br i1 %cmp332, label %if.then333, label %if.else338, !dbg !1337

if.then333:                                       ; preds = %lor.lhs.false327, %land.lhs.true323
  %187 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1339
  %entry334 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %187, i32 0, i32 0, !dbg !1339
  %rbe_color335 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry334, i32 0, i32 3, !dbg !1339
  store i32 1, i32* %rbe_color335, align 8, !dbg !1339
  %188 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1339
  store %struct.watcher_list* %188, %struct.watcher_list** %elm.addr, align 8, !dbg !1339
  %189 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1339
  %entry336 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %189, i32 0, i32 0, !dbg !1339
  %rbe_parent337 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry336, i32 0, i32 2, !dbg !1339
  %190 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent337, align 8, !dbg !1339
  store %struct.watcher_list* %190, %struct.watcher_list** %parent.addr, align 8, !dbg !1339
  br label %if.end488, !dbg !1339

if.else338:                                       ; preds = %lor.lhs.false327, %lor.lhs.false317
  %191 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1342
  %entry339 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %191, i32 0, i32 0, !dbg !1342
  %rbe_left340 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry339, i32 0, i32 0, !dbg !1342
  %192 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left340, align 8, !dbg !1342
  %cmp341 = icmp eq %struct.watcher_list* %192, null, !dbg !1342
  br i1 %cmp341, label %if.then348, label %lor.lhs.false342, !dbg !1342

lor.lhs.false342:                                 ; preds = %if.else338
  %193 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1346
  %entry343 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %193, i32 0, i32 0, !dbg !1346
  %rbe_left344 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry343, i32 0, i32 0, !dbg !1346
  %194 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left344, align 8, !dbg !1346
  %entry345 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %194, i32 0, i32 0, !dbg !1346
  %rbe_color346 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry345, i32 0, i32 3, !dbg !1346
  %195 = load i32, i32* %rbe_color346, align 8, !dbg !1346
  %cmp347 = icmp eq i32 %195, 0, !dbg !1346
  br i1 %cmp347, label %if.then348, label %if.end416, !dbg !1346

if.then348:                                       ; preds = %lor.lhs.false342, %if.else338
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %oright, metadata !1348, metadata !368), !dbg !1350
  %196 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1351
  %entry350 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %196, i32 0, i32 0, !dbg !1351
  %rbe_right351 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry350, i32 0, i32 1, !dbg !1351
  %197 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right351, align 8, !dbg !1351
  store %struct.watcher_list* %197, %struct.watcher_list** %oright, align 8, !dbg !1351
  %cmp352 = icmp ne %struct.watcher_list* %197, null, !dbg !1351
  br i1 %cmp352, label %if.then353, label %if.end356, !dbg !1351

if.then353:                                       ; preds = %if.then348
  %198 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1354
  %entry354 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %198, i32 0, i32 0, !dbg !1354
  %rbe_color355 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry354, i32 0, i32 3, !dbg !1354
  store i32 0, i32* %rbe_color355, align 8, !dbg !1354
  br label %if.end356, !dbg !1354

if.end356:                                        ; preds = %if.then353, %if.then348
  %199 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1356
  %entry357 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %199, i32 0, i32 0, !dbg !1356
  %rbe_color358 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry357, i32 0, i32 3, !dbg !1356
  store i32 1, i32* %rbe_color358, align 8, !dbg !1356
  br label %do.body359, !dbg !1356

do.body359:                                       ; preds = %if.end356
  %200 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1358
  %entry360 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %200, i32 0, i32 0, !dbg !1358
  %rbe_right361 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry360, i32 0, i32 1, !dbg !1358
  %201 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right361, align 8, !dbg !1358
  store %struct.watcher_list* %201, %struct.watcher_list** %oright, align 8, !dbg !1358
  %202 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1358
  %entry362 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %202, i32 0, i32 0, !dbg !1358
  %rbe_left363 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry362, i32 0, i32 0, !dbg !1358
  %203 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left363, align 8, !dbg !1358
  %204 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1358
  %entry364 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %204, i32 0, i32 0, !dbg !1358
  %rbe_right365 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry364, i32 0, i32 1, !dbg !1358
  store %struct.watcher_list* %203, %struct.watcher_list** %rbe_right365, align 8, !dbg !1358
  %cmp366 = icmp ne %struct.watcher_list* %203, null, !dbg !1358
  br i1 %cmp366, label %if.then367, label %if.end372, !dbg !1358

if.then367:                                       ; preds = %do.body359
  %205 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1361
  %206 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1361
  %entry368 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %206, i32 0, i32 0, !dbg !1361
  %rbe_left369 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry368, i32 0, i32 0, !dbg !1361
  %207 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left369, align 8, !dbg !1361
  %entry370 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %207, i32 0, i32 0, !dbg !1361
  %rbe_parent371 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry370, i32 0, i32 2, !dbg !1361
  store %struct.watcher_list* %205, %struct.watcher_list** %rbe_parent371, align 8, !dbg !1361
  br label %if.end372, !dbg !1361

if.end372:                                        ; preds = %if.then367, %do.body359
  br label %do.body373, !dbg !1365

do.body373:                                       ; preds = %if.end372
  br label %do.end374, !dbg !1367

do.end374:                                        ; preds = %do.body373
  %208 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1370
  %entry375 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %208, i32 0, i32 0, !dbg !1370
  %rbe_parent376 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry375, i32 0, i32 2, !dbg !1370
  %209 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent376, align 8, !dbg !1370
  %210 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1370
  %entry377 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %210, i32 0, i32 0, !dbg !1370
  %rbe_parent378 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry377, i32 0, i32 2, !dbg !1370
  store %struct.watcher_list* %209, %struct.watcher_list** %rbe_parent378, align 8, !dbg !1370
  %cmp379 = icmp ne %struct.watcher_list* %209, null, !dbg !1370
  br i1 %cmp379, label %if.then380, label %if.else397, !dbg !1370

if.then380:                                       ; preds = %do.end374
  %211 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1373
  %212 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1373
  %entry381 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %212, i32 0, i32 0, !dbg !1373
  %rbe_parent382 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry381, i32 0, i32 2, !dbg !1373
  %213 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent382, align 8, !dbg !1373
  %entry383 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %213, i32 0, i32 0, !dbg !1373
  %rbe_left384 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry383, i32 0, i32 0, !dbg !1373
  %214 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left384, align 8, !dbg !1373
  %cmp385 = icmp eq %struct.watcher_list* %211, %214, !dbg !1373
  br i1 %cmp385, label %if.then386, label %if.else391, !dbg !1373

if.then386:                                       ; preds = %if.then380
  %215 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1377
  %216 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1377
  %entry387 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %216, i32 0, i32 0, !dbg !1377
  %rbe_parent388 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry387, i32 0, i32 2, !dbg !1377
  %217 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent388, align 8, !dbg !1377
  %entry389 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %217, i32 0, i32 0, !dbg !1377
  %rbe_left390 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry389, i32 0, i32 0, !dbg !1377
  store %struct.watcher_list* %215, %struct.watcher_list** %rbe_left390, align 8, !dbg !1377
  br label %if.end396, !dbg !1377

if.else391:                                       ; preds = %if.then380
  %218 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1379
  %219 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1379
  %entry392 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %219, i32 0, i32 0, !dbg !1379
  %rbe_parent393 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry392, i32 0, i32 2, !dbg !1379
  %220 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent393, align 8, !dbg !1379
  %entry394 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %220, i32 0, i32 0, !dbg !1379
  %rbe_right395 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry394, i32 0, i32 1, !dbg !1379
  store %struct.watcher_list* %218, %struct.watcher_list** %rbe_right395, align 8, !dbg !1379
  br label %if.end396

if.end396:                                        ; preds = %if.else391, %if.then386
  br label %if.end399, !dbg !1381

if.else397:                                       ; preds = %do.end374
  %221 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1383
  %222 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1383
  %rbh_root398 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %222, i32 0, i32 0, !dbg !1383
  store %struct.watcher_list* %221, %struct.watcher_list** %rbh_root398, align 8, !dbg !1383
  br label %if.end399

if.end399:                                        ; preds = %if.else397, %if.end396
  %223 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1385
  %224 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1385
  %entry400 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %224, i32 0, i32 0, !dbg !1385
  %rbe_left401 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry400, i32 0, i32 0, !dbg !1385
  store %struct.watcher_list* %223, %struct.watcher_list** %rbe_left401, align 8, !dbg !1385
  %225 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1385
  %226 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1385
  %entry402 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %226, i32 0, i32 0, !dbg !1385
  %rbe_parent403 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry402, i32 0, i32 2, !dbg !1385
  store %struct.watcher_list* %225, %struct.watcher_list** %rbe_parent403, align 8, !dbg !1385
  br label %do.body404, !dbg !1385

do.body404:                                       ; preds = %if.end399
  br label %do.end405, !dbg !1387

do.end405:                                        ; preds = %do.body404
  %227 = load %struct.watcher_list*, %struct.watcher_list** %oright, align 8, !dbg !1390
  %entry406 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %227, i32 0, i32 0, !dbg !1390
  %rbe_parent407 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry406, i32 0, i32 2, !dbg !1390
  %228 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent407, align 8, !dbg !1390
  %tobool408 = icmp ne %struct.watcher_list* %228, null, !dbg !1390
  br i1 %tobool408, label %if.then409, label %if.end412, !dbg !1390

if.then409:                                       ; preds = %do.end405
  br label %do.body410, !dbg !1393

do.body410:                                       ; preds = %if.then409
  br label %do.end411, !dbg !1395

do.end411:                                        ; preds = %do.body410
  br label %if.end412, !dbg !1398

if.end412:                                        ; preds = %do.end411, %do.end405
  br label %do.end413, !dbg !1400

do.end413:                                        ; preds = %if.end412
  %229 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1402
  %entry414 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %229, i32 0, i32 0, !dbg !1402
  %rbe_left415 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry414, i32 0, i32 0, !dbg !1402
  %230 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left415, align 8, !dbg !1402
  store %struct.watcher_list* %230, %struct.watcher_list** %tmp, align 8, !dbg !1402
  br label %if.end416, !dbg !1402

if.end416:                                        ; preds = %do.end413, %lor.lhs.false342
  %231 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1404
  %entry417 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %231, i32 0, i32 0, !dbg !1404
  %rbe_color418 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry417, i32 0, i32 3, !dbg !1404
  %232 = load i32, i32* %rbe_color418, align 8, !dbg !1404
  %233 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1404
  %entry419 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %233, i32 0, i32 0, !dbg !1404
  %rbe_color420 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry419, i32 0, i32 3, !dbg !1404
  store i32 %232, i32* %rbe_color420, align 8, !dbg !1404
  %234 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1404
  %entry421 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %234, i32 0, i32 0, !dbg !1404
  %rbe_color422 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry421, i32 0, i32 3, !dbg !1404
  store i32 0, i32* %rbe_color422, align 8, !dbg !1404
  %235 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1404
  %entry423 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %235, i32 0, i32 0, !dbg !1404
  %rbe_left424 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry423, i32 0, i32 0, !dbg !1404
  %236 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left424, align 8, !dbg !1404
  %tobool425 = icmp ne %struct.watcher_list* %236, null, !dbg !1404
  br i1 %tobool425, label %if.then426, label %if.end431, !dbg !1404

if.then426:                                       ; preds = %if.end416
  %237 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1406
  %entry427 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %237, i32 0, i32 0, !dbg !1406
  %rbe_left428 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry427, i32 0, i32 0, !dbg !1406
  %238 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left428, align 8, !dbg !1406
  %entry429 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %238, i32 0, i32 0, !dbg !1406
  %rbe_color430 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry429, i32 0, i32 3, !dbg !1406
  store i32 0, i32* %rbe_color430, align 8, !dbg !1406
  br label %if.end431, !dbg !1406

if.end431:                                        ; preds = %if.then426, %if.end416
  br label %do.body432, !dbg !1409

do.body432:                                       ; preds = %if.end431
  %239 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1411
  %entry433 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %239, i32 0, i32 0, !dbg !1411
  %rbe_left434 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry433, i32 0, i32 0, !dbg !1411
  %240 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left434, align 8, !dbg !1411
  store %struct.watcher_list* %240, %struct.watcher_list** %tmp, align 8, !dbg !1411
  %241 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1411
  %entry435 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %241, i32 0, i32 0, !dbg !1411
  %rbe_right436 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry435, i32 0, i32 1, !dbg !1411
  %242 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right436, align 8, !dbg !1411
  %243 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1411
  %entry437 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %243, i32 0, i32 0, !dbg !1411
  %rbe_left438 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry437, i32 0, i32 0, !dbg !1411
  store %struct.watcher_list* %242, %struct.watcher_list** %rbe_left438, align 8, !dbg !1411
  %cmp439 = icmp ne %struct.watcher_list* %242, null, !dbg !1411
  br i1 %cmp439, label %if.then440, label %if.end445, !dbg !1411

if.then440:                                       ; preds = %do.body432
  %244 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1414
  %245 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1414
  %entry441 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %245, i32 0, i32 0, !dbg !1414
  %rbe_right442 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry441, i32 0, i32 1, !dbg !1414
  %246 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right442, align 8, !dbg !1414
  %entry443 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %246, i32 0, i32 0, !dbg !1414
  %rbe_parent444 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry443, i32 0, i32 2, !dbg !1414
  store %struct.watcher_list* %244, %struct.watcher_list** %rbe_parent444, align 8, !dbg !1414
  br label %if.end445, !dbg !1414

if.end445:                                        ; preds = %if.then440, %do.body432
  br label %do.body446, !dbg !1418

do.body446:                                       ; preds = %if.end445
  br label %do.end447, !dbg !1420

do.end447:                                        ; preds = %do.body446
  %247 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1423
  %entry448 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %247, i32 0, i32 0, !dbg !1423
  %rbe_parent449 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry448, i32 0, i32 2, !dbg !1423
  %248 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent449, align 8, !dbg !1423
  %249 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1423
  %entry450 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %249, i32 0, i32 0, !dbg !1423
  %rbe_parent451 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry450, i32 0, i32 2, !dbg !1423
  store %struct.watcher_list* %248, %struct.watcher_list** %rbe_parent451, align 8, !dbg !1423
  %cmp452 = icmp ne %struct.watcher_list* %248, null, !dbg !1423
  br i1 %cmp452, label %if.then453, label %if.else470, !dbg !1423

if.then453:                                       ; preds = %do.end447
  %250 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1426
  %251 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1426
  %entry454 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %251, i32 0, i32 0, !dbg !1426
  %rbe_parent455 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry454, i32 0, i32 2, !dbg !1426
  %252 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent455, align 8, !dbg !1426
  %entry456 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %252, i32 0, i32 0, !dbg !1426
  %rbe_left457 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry456, i32 0, i32 0, !dbg !1426
  %253 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left457, align 8, !dbg !1426
  %cmp458 = icmp eq %struct.watcher_list* %250, %253, !dbg !1426
  br i1 %cmp458, label %if.then459, label %if.else464, !dbg !1426

if.then459:                                       ; preds = %if.then453
  %254 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1430
  %255 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1430
  %entry460 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %255, i32 0, i32 0, !dbg !1430
  %rbe_parent461 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry460, i32 0, i32 2, !dbg !1430
  %256 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent461, align 8, !dbg !1430
  %entry462 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %256, i32 0, i32 0, !dbg !1430
  %rbe_left463 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry462, i32 0, i32 0, !dbg !1430
  store %struct.watcher_list* %254, %struct.watcher_list** %rbe_left463, align 8, !dbg !1430
  br label %if.end469, !dbg !1430

if.else464:                                       ; preds = %if.then453
  %257 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1432
  %258 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1432
  %entry465 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %258, i32 0, i32 0, !dbg !1432
  %rbe_parent466 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry465, i32 0, i32 2, !dbg !1432
  %259 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent466, align 8, !dbg !1432
  %entry467 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %259, i32 0, i32 0, !dbg !1432
  %rbe_right468 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry467, i32 0, i32 1, !dbg !1432
  store %struct.watcher_list* %257, %struct.watcher_list** %rbe_right468, align 8, !dbg !1432
  br label %if.end469

if.end469:                                        ; preds = %if.else464, %if.then459
  br label %if.end472, !dbg !1434

if.else470:                                       ; preds = %do.end447
  %260 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1436
  %261 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1436
  %rbh_root471 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %261, i32 0, i32 0, !dbg !1436
  store %struct.watcher_list* %260, %struct.watcher_list** %rbh_root471, align 8, !dbg !1436
  br label %if.end472

if.end472:                                        ; preds = %if.else470, %if.end469
  %262 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1438
  %263 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1438
  %entry473 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %263, i32 0, i32 0, !dbg !1438
  %rbe_right474 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry473, i32 0, i32 1, !dbg !1438
  store %struct.watcher_list* %262, %struct.watcher_list** %rbe_right474, align 8, !dbg !1438
  %264 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1438
  %265 = load %struct.watcher_list*, %struct.watcher_list** %parent.addr, align 8, !dbg !1438
  %entry475 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %265, i32 0, i32 0, !dbg !1438
  %rbe_parent476 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry475, i32 0, i32 2, !dbg !1438
  store %struct.watcher_list* %264, %struct.watcher_list** %rbe_parent476, align 8, !dbg !1438
  br label %do.body477, !dbg !1438

do.body477:                                       ; preds = %if.end472
  br label %do.end478, !dbg !1440

do.end478:                                        ; preds = %do.body477
  %266 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1443
  %entry479 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %266, i32 0, i32 0, !dbg !1443
  %rbe_parent480 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry479, i32 0, i32 2, !dbg !1443
  %267 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent480, align 8, !dbg !1443
  %tobool481 = icmp ne %struct.watcher_list* %267, null, !dbg !1443
  br i1 %tobool481, label %if.then482, label %if.end485, !dbg !1443

if.then482:                                       ; preds = %do.end478
  br label %do.body483, !dbg !1446

do.body483:                                       ; preds = %if.then482
  br label %do.end484, !dbg !1448

do.end484:                                        ; preds = %do.body483
  br label %if.end485, !dbg !1451

if.end485:                                        ; preds = %do.end484, %do.end478
  br label %do.end486, !dbg !1453

do.end486:                                        ; preds = %if.end485
  %268 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1455
  %rbh_root487 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %268, i32 0, i32 0, !dbg !1455
  %269 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root487, align 8, !dbg !1455
  store %struct.watcher_list* %269, %struct.watcher_list** %elm.addr, align 8, !dbg !1455
  br label %while.end, !dbg !1455

if.end488:                                        ; preds = %if.then333
  br label %if.end489

if.end489:                                        ; preds = %if.end488, %if.end242
  br label %while.cond, !dbg !1457

while.end:                                        ; preds = %do.end486, %do.end240, %land.end
  %270 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1459
  %tobool490 = icmp ne %struct.watcher_list* %270, null, !dbg !1459
  br i1 %tobool490, label %if.then491, label %if.end494, !dbg !1459

if.then491:                                       ; preds = %while.end
  %271 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1462
  %entry492 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %271, i32 0, i32 0, !dbg !1462
  %rbe_color493 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry492, i32 0, i32 3, !dbg !1462
  store i32 0, i32* %rbe_color493, align 8, !dbg !1462
  br label %if.end494, !dbg !1462

if.end494:                                        ; preds = %if.then491, %while.end
  ret void, !dbg !1464
}

; Function Attrs: nounwind uwtable
define internal i32 @new_inotify_fd() #0 !dbg !341 {
entry:
  %retval = alloca i32, align 4
  %err = alloca i32, align 4
  %fd = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1466, metadata !368), !dbg !1467
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1468, metadata !368), !dbg !1469
  %call = call i32 @uv__inotify_init1(i32 526336), !dbg !1470
  store i32 %call, i32* %fd, align 4, !dbg !1471
  %0 = load i32, i32* %fd, align 4, !dbg !1472
  %cmp = icmp ne i32 %0, -1, !dbg !1474
  br i1 %cmp, label %if.then, label %if.end, !dbg !1475

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %fd, align 4, !dbg !1476
  store i32 %1, i32* %retval, align 4, !dbg !1477
  br label %return, !dbg !1477

if.end:                                           ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1478
  %2 = load i32, i32* %call1, align 4, !dbg !1478
  %cmp2 = icmp ne i32 %2, 38, !dbg !1480
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !1481

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__errno_location() #1, !dbg !1482
  %3 = load i32, i32* %call4, align 4, !dbg !1482
  %sub = sub nsw i32 0, %3, !dbg !1483
  store i32 %sub, i32* %retval, align 4, !dbg !1484
  br label %return, !dbg !1484

if.end5:                                          ; preds = %if.end
  %call6 = call i32 @uv__inotify_init(), !dbg !1485
  store i32 %call6, i32* %fd, align 4, !dbg !1486
  %4 = load i32, i32* %fd, align 4, !dbg !1487
  %cmp7 = icmp eq i32 %4, -1, !dbg !1489
  br i1 %cmp7, label %if.then8, label %if.end11, !dbg !1490

if.then8:                                         ; preds = %if.end5
  %call9 = call i32* @__errno_location() #1, !dbg !1491
  %5 = load i32, i32* %call9, align 4, !dbg !1491
  %sub10 = sub nsw i32 0, %5, !dbg !1492
  store i32 %sub10, i32* %retval, align 4, !dbg !1493
  br label %return, !dbg !1493

if.end11:                                         ; preds = %if.end5
  %6 = load i32, i32* %fd, align 4, !dbg !1494
  %call12 = call i32 @uv__cloexec_ioctl(i32 %6, i32 1), !dbg !1495
  store i32 %call12, i32* %err, align 4, !dbg !1496
  %7 = load i32, i32* %err, align 4, !dbg !1497
  %cmp13 = icmp eq i32 %7, 0, !dbg !1499
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !1500

if.then14:                                        ; preds = %if.end11
  %8 = load i32, i32* %fd, align 4, !dbg !1501
  %call15 = call i32 @uv__nonblock_ioctl(i32 %8, i32 1), !dbg !1502
  store i32 %call15, i32* %err, align 4, !dbg !1503
  br label %if.end16, !dbg !1504

if.end16:                                         ; preds = %if.then14, %if.end11
  %9 = load i32, i32* %err, align 4, !dbg !1505
  %tobool = icmp ne i32 %9, 0, !dbg !1505
  br i1 %tobool, label %if.then17, label %if.end19, !dbg !1507

if.then17:                                        ; preds = %if.end16
  %10 = load i32, i32* %fd, align 4, !dbg !1508
  %call18 = call i32 @uv__close(i32 %10), !dbg !1510
  %11 = load i32, i32* %err, align 4, !dbg !1511
  store i32 %11, i32* %retval, align 4, !dbg !1512
  br label %return, !dbg !1512

if.end19:                                         ; preds = %if.end16
  %12 = load i32, i32* %fd, align 4, !dbg !1513
  store i32 %12, i32* %retval, align 4, !dbg !1514
  br label %return, !dbg !1514

return:                                           ; preds = %if.end19, %if.then17, %if.then8, %if.then3, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !1515
  ret i32 %13, !dbg !1515
}

declare void @uv__io_init(%struct.uv__io_s*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__inotify_read(%struct.uv_loop_s* %loop, %struct.uv__io_s* %dummy, i32 %events) #0 !dbg !344 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %dummy.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  %e = alloca %struct.uv__inotify_event*, align 8
  %w = alloca %struct.watcher_list*, align 8
  %h = alloca %struct.uv_fs_event_s*, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %path = alloca i8*, align 8
  %size = alloca i64, align 8
  %p = alloca i8*, align 8
  %buf = alloca [4096 x i8], align 16
  %q43 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1516, metadata !368), !dbg !1517
  store %struct.uv__io_s* %dummy, %struct.uv__io_s** %dummy.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %dummy.addr, metadata !1518, metadata !368), !dbg !1519
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !1520, metadata !368), !dbg !1521
  call void @llvm.dbg.declare(metadata %struct.uv__inotify_event** %e, metadata !1522, metadata !368), !dbg !1523
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %w, metadata !1524, metadata !368), !dbg !1525
  call void @llvm.dbg.declare(metadata %struct.uv_fs_event_s** %h, metadata !1526, metadata !368), !dbg !1527
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !1528, metadata !368), !dbg !1529
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1530, metadata !368), !dbg !1531
  call void @llvm.dbg.declare(metadata i8** %path, metadata !1532, metadata !368), !dbg !1533
  call void @llvm.dbg.declare(metadata i64* %size, metadata !1534, metadata !368), !dbg !1539
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1540, metadata !368), !dbg !1541
  call void @llvm.dbg.declare(metadata [4096 x i8]* %buf, metadata !1542, metadata !368), !dbg !1546
  br label %while.body, !dbg !1547

while.body:                                       ; preds = %entry, %for.end
  br label %do.body, !dbg !1548

do.body:                                          ; preds = %land.end, %while.body
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1550
  %inotify_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 34, !dbg !1551
  %1 = load i32, i32* %inotify_fd, align 8, !dbg !1551
  %arraydecay = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i32 0, i32 0, !dbg !1552
  %call = call i64 @read(i32 %1, i8* %arraydecay, i64 4096), !dbg !1553
  store i64 %call, i64* %size, align 8, !dbg !1554
  br label %do.cond, !dbg !1555

do.cond:                                          ; preds = %do.body
  %2 = load i64, i64* %size, align 8, !dbg !1556
  %cmp = icmp eq i64 %2, -1, !dbg !1557
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1558

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #1, !dbg !1559
  %3 = load i32, i32* %call1, align 4, !dbg !1559
  %cmp2 = icmp eq i32 %3, 4, !dbg !1561
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %4 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %4, label %do.body, label %do.end, !dbg !1562

do.end:                                           ; preds = %land.end
  %5 = load i64, i64* %size, align 8, !dbg !1563
  %cmp3 = icmp eq i64 %5, -1, !dbg !1565
  br i1 %cmp3, label %if.then, label %if.end, !dbg !1566

if.then:                                          ; preds = %do.end
  %call4 = call i32* @__errno_location() #1, !dbg !1567
  %6 = load i32, i32* %call4, align 4, !dbg !1567
  %cmp5 = icmp eq i32 %6, 11, !dbg !1567
  br i1 %cmp5, label %cond.true, label %lor.lhs.false, !dbg !1567

lor.lhs.false:                                    ; preds = %if.then
  %call6 = call i32* @__errno_location() #1, !dbg !1569
  %7 = load i32, i32* %call6, align 4, !dbg !1569
  %cmp7 = icmp eq i32 %7, 11, !dbg !1569
  br i1 %cmp7, label %cond.true, label %cond.false, !dbg !1569

cond.true:                                        ; preds = %lor.lhs.false, %if.then
  br label %cond.end, !dbg !1571

cond.false:                                       ; preds = %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 214, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @__PRETTY_FUNCTION__.uv__inotify_read, i32 0, i32 0)) #8, !dbg !1573
  unreachable, !dbg !1573
                                                  ; No predecessors!
  br label %cond.end, !dbg !1575

cond.end:                                         ; preds = %8, %cond.true
  br label %while.end96, !dbg !1577

if.end:                                           ; preds = %do.end
  %9 = load i64, i64* %size, align 8, !dbg !1578
  %cmp8 = icmp sgt i64 %9, 0, !dbg !1578
  br i1 %cmp8, label %cond.true9, label %cond.false10, !dbg !1578

cond.true9:                                       ; preds = %if.end
  br label %cond.end11, !dbg !1579

cond.false10:                                     ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 218, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @__PRETTY_FUNCTION__.uv__inotify_read, i32 0, i32 0)) #8, !dbg !1580
  unreachable, !dbg !1580
                                                  ; No predecessors!
  br label %cond.end11, !dbg !1582

cond.end11:                                       ; preds = %10, %cond.true9
  %arraydecay12 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i32 0, i32 0, !dbg !1584
  store i8* %arraydecay12, i8** %p, align 8, !dbg !1586
  br label %for.cond, !dbg !1587

for.cond:                                         ; preds = %for.inc, %cond.end11
  %11 = load i8*, i8** %p, align 8, !dbg !1588
  %arraydecay13 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i32 0, i32 0, !dbg !1591
  %12 = load i64, i64* %size, align 8, !dbg !1592
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay13, i64 %12, !dbg !1593
  %cmp14 = icmp ult i8* %11, %add.ptr, !dbg !1594
  br i1 %cmp14, label %for.body, label %for.end, !dbg !1595

for.body:                                         ; preds = %for.cond
  %13 = load i8*, i8** %p, align 8, !dbg !1596
  %14 = bitcast i8* %13 to %struct.uv__inotify_event*, !dbg !1598
  store %struct.uv__inotify_event* %14, %struct.uv__inotify_event** %e, align 8, !dbg !1599
  store i32 0, i32* %events.addr, align 4, !dbg !1600
  %15 = load %struct.uv__inotify_event*, %struct.uv__inotify_event** %e, align 8, !dbg !1601
  %mask = getelementptr inbounds %struct.uv__inotify_event, %struct.uv__inotify_event* %15, i32 0, i32 1, !dbg !1603
  %16 = load i32, i32* %mask, align 4, !dbg !1603
  %and = and i32 %16, 6, !dbg !1604
  %tobool = icmp ne i32 %and, 0, !dbg !1604
  br i1 %tobool, label %if.then15, label %if.end16, !dbg !1605

if.then15:                                        ; preds = %for.body
  %17 = load i32, i32* %events.addr, align 4, !dbg !1606
  %or = or i32 %17, 2, !dbg !1606
  store i32 %or, i32* %events.addr, align 4, !dbg !1606
  br label %if.end16, !dbg !1607

if.end16:                                         ; preds = %if.then15, %for.body
  %18 = load %struct.uv__inotify_event*, %struct.uv__inotify_event** %e, align 8, !dbg !1608
  %mask17 = getelementptr inbounds %struct.uv__inotify_event, %struct.uv__inotify_event* %18, i32 0, i32 1, !dbg !1610
  %19 = load i32, i32* %mask17, align 4, !dbg !1610
  %and18 = and i32 %19, -7, !dbg !1611
  %tobool19 = icmp ne i32 %and18, 0, !dbg !1611
  br i1 %tobool19, label %if.then20, label %if.end22, !dbg !1612

if.then20:                                        ; preds = %if.end16
  %20 = load i32, i32* %events.addr, align 4, !dbg !1613
  %or21 = or i32 %20, 1, !dbg !1613
  store i32 %or21, i32* %events.addr, align 4, !dbg !1613
  br label %if.end22, !dbg !1614

if.end22:                                         ; preds = %if.then20, %if.end16
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1615
  %22 = load %struct.uv__inotify_event*, %struct.uv__inotify_event** %e, align 8, !dbg !1616
  %wd = getelementptr inbounds %struct.uv__inotify_event, %struct.uv__inotify_event* %22, i32 0, i32 0, !dbg !1617
  %23 = load i32, i32* %wd, align 4, !dbg !1617
  %call23 = call %struct.watcher_list* @find_watcher(%struct.uv_loop_s* %21, i32 %23), !dbg !1618
  store %struct.watcher_list* %call23, %struct.watcher_list** %w, align 8, !dbg !1619
  %24 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1620
  %cmp24 = icmp eq %struct.watcher_list* %24, null, !dbg !1622
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !1623

if.then25:                                        ; preds = %if.end22
  br label %for.inc, !dbg !1624

if.end26:                                         ; preds = %if.end22
  %25 = load %struct.uv__inotify_event*, %struct.uv__inotify_event** %e, align 8, !dbg !1625
  %len = getelementptr inbounds %struct.uv__inotify_event, %struct.uv__inotify_event* %25, i32 0, i32 3, !dbg !1626
  %26 = load i32, i32* %len, align 4, !dbg !1626
  %tobool27 = icmp ne i32 %26, 0, !dbg !1625
  br i1 %tobool27, label %cond.true28, label %cond.false30, !dbg !1625

cond.true28:                                      ; preds = %if.end26
  %27 = load %struct.uv__inotify_event*, %struct.uv__inotify_event** %e, align 8, !dbg !1627
  %add.ptr29 = getelementptr inbounds %struct.uv__inotify_event, %struct.uv__inotify_event* %27, i64 1, !dbg !1629
  %28 = bitcast %struct.uv__inotify_event* %add.ptr29 to i8*, !dbg !1630
  br label %cond.end33, !dbg !1631

cond.false30:                                     ; preds = %if.end26
  %29 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1632
  %path31 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %29, i32 0, i32 3, !dbg !1634
  %30 = load i8*, i8** %path31, align 8, !dbg !1634
  %call32 = call i8* @uv__basename_r(i8* %30), !dbg !1635
  br label %cond.end33, !dbg !1636

cond.end33:                                       ; preds = %cond.false30, %cond.true28
  %cond = phi i8* [ %28, %cond.true28 ], [ %call32, %cond.false30 ], !dbg !1637
  store i8* %cond, i8** %path, align 8, !dbg !1639
  %31 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1640
  %iterating = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %31, i32 0, i32 2, !dbg !1641
  store i32 1, i32* %iterating, align 8, !dbg !1642
  br label %do.body34, !dbg !1643

do.body34:                                        ; preds = %cond.end33
  %32 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1644
  %watchers = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %32, i32 0, i32 1, !dbg !1644
  %33 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1644
  %watchers35 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %33, i32 0, i32 1, !dbg !1644
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers35, i64 0, i64 0, !dbg !1644
  %34 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1644
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !1644
  %cmp36 = icmp eq [2 x i8*]* %watchers, %35, !dbg !1644
  br i1 %cmp36, label %if.then37, label %if.else, !dbg !1644

if.then37:                                        ; preds = %do.body34
  br label %do.body38, !dbg !1648

do.body38:                                        ; preds = %if.then37
  %arrayidx39 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1650
  %36 = bitcast i8** %arrayidx39 to [2 x i8*]**, !dbg !1650
  store [2 x i8*]* %queue, [2 x i8*]** %36, align 16, !dbg !1650
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !1650
  %37 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !1650
  store [2 x i8*]* %queue, [2 x i8*]** %37, align 8, !dbg !1650
  br label %do.end42, !dbg !1650

do.end42:                                         ; preds = %do.body38
  br label %if.end63, !dbg !1653

if.else:                                          ; preds = %do.body34
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q43, metadata !1655, metadata !368), !dbg !1657
  %38 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1658
  %watchers44 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %38, i32 0, i32 1, !dbg !1658
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers44, i64 0, i64 0, !dbg !1658
  %39 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1658
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1658
  store [2 x i8*]* %40, [2 x i8*]** %q43, align 8, !dbg !1658
  br label %do.body46, !dbg !1658

do.body46:                                        ; preds = %if.else
  %41 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1660
  %watchers47 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %41, i32 0, i32 1, !dbg !1660
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers47, i64 0, i64 1, !dbg !1660
  %42 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !1660
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !1660
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !1660
  %44 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !1660
  store [2 x i8*]* %43, [2 x i8*]** %44, align 8, !dbg !1660
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !1660
  %45 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1660
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !1660
  %arrayidx51 = getelementptr inbounds [2 x i8*], [2 x i8*]* %46, i64 0, i64 0, !dbg !1660
  %47 = bitcast i8** %arrayidx51 to [2 x i8*]**, !dbg !1660
  store [2 x i8*]* %queue, [2 x i8*]** %47, align 8, !dbg !1660
  %48 = load [2 x i8*]*, [2 x i8*]** %q43, align 8, !dbg !1660
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1660
  %49 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1660
  store [2 x i8*]* %48, [2 x i8*]** %49, align 16, !dbg !1660
  %50 = load [2 x i8*]*, [2 x i8*]** %q43, align 8, !dbg !1660
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 1, !dbg !1660
  %51 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1660
  %52 = load [2 x i8*]*, [2 x i8*]** %51, align 8, !dbg !1660
  %53 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1660
  %watchers54 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %53, i32 0, i32 1, !dbg !1660
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers54, i64 0, i64 1, !dbg !1660
  %54 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !1660
  store [2 x i8*]* %52, [2 x i8*]** %54, align 8, !dbg !1660
  %55 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1660
  %watchers56 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %55, i32 0, i32 1, !dbg !1660
  %56 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1660
  %watchers57 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %56, i32 0, i32 1, !dbg !1660
  %arrayidx58 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers57, i64 0, i64 1, !dbg !1660
  %57 = bitcast i8** %arrayidx58 to [2 x i8*]**, !dbg !1660
  %58 = load [2 x i8*]*, [2 x i8*]** %57, align 8, !dbg !1660
  %arrayidx59 = getelementptr inbounds [2 x i8*], [2 x i8*]* %58, i64 0, i64 0, !dbg !1660
  %59 = bitcast i8** %arrayidx59 to [2 x i8*]**, !dbg !1660
  store [2 x i8*]* %watchers56, [2 x i8*]** %59, align 8, !dbg !1660
  %60 = load [2 x i8*]*, [2 x i8*]** %q43, align 8, !dbg !1660
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !1660
  %61 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !1660
  store [2 x i8*]* %queue, [2 x i8*]** %61, align 8, !dbg !1660
  br label %do.end62, !dbg !1660

do.end62:                                         ; preds = %do.body46
  br label %if.end63

if.end63:                                         ; preds = %do.end62, %do.end42
  br label %do.end65, !dbg !1663

do.end65:                                         ; preds = %if.end63
  br label %while.cond66, !dbg !1665

while.cond66:                                     ; preds = %do.end92, %do.end65
  %arrayidx67 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1666
  %62 = bitcast i8** %arrayidx67 to [2 x i8*]**, !dbg !1666
  %63 = load [2 x i8*]*, [2 x i8*]** %62, align 16, !dbg !1666
  %cmp68 = icmp eq [2 x i8*]* %queue, %63, !dbg !1666
  %lnot = xor i1 %cmp68, true, !dbg !1667
  br i1 %lnot, label %while.body69, label %while.end, !dbg !1668

while.body69:                                     ; preds = %while.cond66
  %arrayidx70 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1669
  %64 = bitcast i8** %arrayidx70 to [2 x i8*]**, !dbg !1669
  %65 = load [2 x i8*]*, [2 x i8*]** %64, align 16, !dbg !1669
  store [2 x i8*]* %65, [2 x i8*]** %q, align 8, !dbg !1671
  %66 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1672
  %67 = bitcast [2 x i8*]* %66 to i8*, !dbg !1672
  %add.ptr71 = getelementptr inbounds i8, i8* %67, i64 -112, !dbg !1672
  %68 = bitcast i8* %add.ptr71 to %struct.uv_fs_event_s*, !dbg !1672
  store %struct.uv_fs_event_s* %68, %struct.uv_fs_event_s** %h, align 8, !dbg !1673
  br label %do.body72, !dbg !1674

do.body72:                                        ; preds = %while.body69
  %69 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1675
  %arrayidx73 = getelementptr inbounds [2 x i8*], [2 x i8*]* %69, i64 0, i64 0, !dbg !1675
  %70 = bitcast i8** %arrayidx73 to [2 x i8*]**, !dbg !1675
  %71 = load [2 x i8*]*, [2 x i8*]** %70, align 8, !dbg !1675
  %72 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1675
  %arrayidx74 = getelementptr inbounds [2 x i8*], [2 x i8*]* %72, i64 0, i64 1, !dbg !1675
  %73 = bitcast i8** %arrayidx74 to [2 x i8*]**, !dbg !1675
  %74 = load [2 x i8*]*, [2 x i8*]** %73, align 8, !dbg !1675
  %arrayidx75 = getelementptr inbounds [2 x i8*], [2 x i8*]* %74, i64 0, i64 0, !dbg !1675
  %75 = bitcast i8** %arrayidx75 to [2 x i8*]**, !dbg !1675
  store [2 x i8*]* %71, [2 x i8*]** %75, align 8, !dbg !1675
  %76 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1675
  %arrayidx76 = getelementptr inbounds [2 x i8*], [2 x i8*]* %76, i64 0, i64 1, !dbg !1675
  %77 = bitcast i8** %arrayidx76 to [2 x i8*]**, !dbg !1675
  %78 = load [2 x i8*]*, [2 x i8*]** %77, align 8, !dbg !1675
  %79 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1675
  %arrayidx77 = getelementptr inbounds [2 x i8*], [2 x i8*]* %79, i64 0, i64 0, !dbg !1675
  %80 = bitcast i8** %arrayidx77 to [2 x i8*]**, !dbg !1675
  %81 = load [2 x i8*]*, [2 x i8*]** %80, align 8, !dbg !1675
  %arrayidx78 = getelementptr inbounds [2 x i8*], [2 x i8*]* %81, i64 0, i64 1, !dbg !1675
  %82 = bitcast i8** %arrayidx78 to [2 x i8*]**, !dbg !1675
  store [2 x i8*]* %78, [2 x i8*]** %82, align 8, !dbg !1675
  br label %do.end80, !dbg !1675

do.end80:                                         ; preds = %do.body72
  br label %do.body81, !dbg !1678

do.body81:                                        ; preds = %do.end80
  %83 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1679
  %watchers82 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %83, i32 0, i32 1, !dbg !1679
  %84 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1679
  %arrayidx83 = getelementptr inbounds [2 x i8*], [2 x i8*]* %84, i64 0, i64 0, !dbg !1679
  %85 = bitcast i8** %arrayidx83 to [2 x i8*]**, !dbg !1679
  store [2 x i8*]* %watchers82, [2 x i8*]** %85, align 8, !dbg !1679
  %86 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1679
  %watchers84 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %86, i32 0, i32 1, !dbg !1679
  %arrayidx85 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers84, i64 0, i64 1, !dbg !1679
  %87 = bitcast i8** %arrayidx85 to [2 x i8*]**, !dbg !1679
  %88 = load [2 x i8*]*, [2 x i8*]** %87, align 8, !dbg !1679
  %89 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1679
  %arrayidx86 = getelementptr inbounds [2 x i8*], [2 x i8*]* %89, i64 0, i64 1, !dbg !1679
  %90 = bitcast i8** %arrayidx86 to [2 x i8*]**, !dbg !1679
  store [2 x i8*]* %88, [2 x i8*]** %90, align 8, !dbg !1679
  %91 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1679
  %92 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1679
  %arrayidx87 = getelementptr inbounds [2 x i8*], [2 x i8*]* %92, i64 0, i64 1, !dbg !1679
  %93 = bitcast i8** %arrayidx87 to [2 x i8*]**, !dbg !1679
  %94 = load [2 x i8*]*, [2 x i8*]** %93, align 8, !dbg !1679
  %arrayidx88 = getelementptr inbounds [2 x i8*], [2 x i8*]* %94, i64 0, i64 0, !dbg !1679
  %95 = bitcast i8** %arrayidx88 to [2 x i8*]**, !dbg !1679
  store [2 x i8*]* %91, [2 x i8*]** %95, align 8, !dbg !1679
  %96 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1679
  %97 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1679
  %watchers89 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %97, i32 0, i32 1, !dbg !1679
  %arrayidx90 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watchers89, i64 0, i64 1, !dbg !1679
  %98 = bitcast i8** %arrayidx90 to [2 x i8*]**, !dbg !1679
  store [2 x i8*]* %96, [2 x i8*]** %98, align 8, !dbg !1679
  br label %do.end92, !dbg !1679

do.end92:                                         ; preds = %do.body81
  %99 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %h, align 8, !dbg !1682
  %cb = getelementptr inbounds %struct.uv_fs_event_s, %struct.uv_fs_event_s* %99, i32 0, i32 9, !dbg !1683
  %100 = load void (%struct.uv_fs_event_s*, i8*, i32, i32)*, void (%struct.uv_fs_event_s*, i8*, i32, i32)** %cb, align 8, !dbg !1683
  %101 = load %struct.uv_fs_event_s*, %struct.uv_fs_event_s** %h, align 8, !dbg !1684
  %102 = load i8*, i8** %path, align 8, !dbg !1685
  %103 = load i32, i32* %events.addr, align 4, !dbg !1686
  call void %100(%struct.uv_fs_event_s* %101, i8* %102, i32 %103, i32 0), !dbg !1682
  br label %while.cond66, !dbg !1687

while.end:                                        ; preds = %while.cond66
  %104 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1688
  %iterating93 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %104, i32 0, i32 2, !dbg !1689
  store i32 0, i32* %iterating93, align 8, !dbg !1690
  %105 = load %struct.watcher_list*, %struct.watcher_list** %w, align 8, !dbg !1691
  %106 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1692
  call void @maybe_free_watcher_list(%struct.watcher_list* %105, %struct.uv_loop_s* %106), !dbg !1693
  br label %for.inc, !dbg !1694

for.inc:                                          ; preds = %while.end, %if.then25
  %107 = load %struct.uv__inotify_event*, %struct.uv__inotify_event** %e, align 8, !dbg !1695
  %len94 = getelementptr inbounds %struct.uv__inotify_event, %struct.uv__inotify_event* %107, i32 0, i32 3, !dbg !1697
  %108 = load i32, i32* %len94, align 4, !dbg !1697
  %conv = zext i32 %108 to i64, !dbg !1695
  %add = add i64 16, %conv, !dbg !1698
  %109 = load i8*, i8** %p, align 8, !dbg !1699
  %add.ptr95 = getelementptr inbounds i8, i8* %109, i64 %add, !dbg !1699
  store i8* %add.ptr95, i8** %p, align 8, !dbg !1699
  br label %for.cond, !dbg !1700

for.end:                                          ; preds = %for.cond
  br label %while.body, !dbg !1701

while.end96:                                      ; preds = %cond.end
  ret void, !dbg !1703
}

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

declare i32 @uv__inotify_init1(i32) #2

declare i32 @uv__inotify_init() #2

declare i32 @uv__cloexec_ioctl(i32, i32) #2

declare i32 @uv__nonblock_ioctl(i32, i32) #2

declare i32 @uv__close(i32) #2

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i8* @uv__basename_r(i8* %path) #0 !dbg !347 {
entry:
  %retval = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  %s = alloca i8*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1704, metadata !368), !dbg !1705
  call void @llvm.dbg.declare(metadata i8** %s, metadata !1706, metadata !368), !dbg !1707
  %0 = load i8*, i8** %path.addr, align 8, !dbg !1708
  %call = call i8* @strrchr(i8* %0, i32 47) #9, !dbg !1709
  store i8* %call, i8** %s, align 8, !dbg !1710
  %1 = load i8*, i8** %s, align 8, !dbg !1711
  %cmp = icmp eq i8* %1, null, !dbg !1713
  br i1 %cmp, label %if.then, label %if.end, !dbg !1714

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %path.addr, align 8, !dbg !1715
  store i8* %2, i8** %retval, align 8, !dbg !1716
  br label %return, !dbg !1716

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %s, align 8, !dbg !1717
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 1, !dbg !1718
  store i8* %add.ptr, i8** %retval, align 8, !dbg !1719
  br label %return, !dbg !1719

return:                                           ; preds = %if.end, %if.then
  %4 = load i8*, i8** %retval, align 8, !dbg !1720
  ret i8* %4, !dbg !1720
}

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #5

; Function Attrs: nounwind uwtable
define internal %struct.watcher_list* @watcher_root_RB_FIND(%struct.watcher_root* %head, %struct.watcher_list* %elm) #0 !dbg !354 {
entry:
  %retval = alloca %struct.watcher_list*, align 8
  %head.addr = alloca %struct.watcher_root*, align 8
  %elm.addr = alloca %struct.watcher_list*, align 8
  %tmp = alloca %struct.watcher_list*, align 8
  %comp = alloca i32, align 4
  store %struct.watcher_root* %head, %struct.watcher_root** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_root** %head.addr, metadata !1721, metadata !368), !dbg !1722
  store %struct.watcher_list* %elm, %struct.watcher_list** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %elm.addr, metadata !1723, metadata !368), !dbg !1722
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %tmp, metadata !1724, metadata !368), !dbg !1722
  %0 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1722
  %rbh_root = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %0, i32 0, i32 0, !dbg !1722
  %1 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root, align 8, !dbg !1722
  store %struct.watcher_list* %1, %struct.watcher_list** %tmp, align 8, !dbg !1722
  call void @llvm.dbg.declare(metadata i32* %comp, metadata !1725, metadata !368), !dbg !1722
  br label %while.cond, !dbg !1722

while.cond:                                       ; preds = %if.end7, %entry
  %2 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1726
  %tobool = icmp ne %struct.watcher_list* %2, null, !dbg !1726
  br i1 %tobool, label %while.body, label %while.end, !dbg !1726

while.body:                                       ; preds = %while.cond
  %3 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1728
  %4 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1728
  %call = call i32 @compare_watchers(%struct.watcher_list* %3, %struct.watcher_list* %4), !dbg !1728
  store i32 %call, i32* %comp, align 4, !dbg !1728
  %5 = load i32, i32* %comp, align 4, !dbg !1728
  %cmp = icmp slt i32 %5, 0, !dbg !1728
  br i1 %cmp, label %if.then, label %if.else, !dbg !1728

if.then:                                          ; preds = %while.body
  %6 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1731
  %entry2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %6, i32 0, i32 0, !dbg !1731
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry2, i32 0, i32 0, !dbg !1731
  %7 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !1731
  store %struct.watcher_list* %7, %struct.watcher_list** %tmp, align 8, !dbg !1731
  br label %if.end7, !dbg !1731

if.else:                                          ; preds = %while.body
  %8 = load i32, i32* %comp, align 4, !dbg !1734
  %cmp3 = icmp sgt i32 %8, 0, !dbg !1734
  br i1 %cmp3, label %if.then4, label %if.else6, !dbg !1734

if.then4:                                         ; preds = %if.else
  %9 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1737
  %entry5 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %9, i32 0, i32 0, !dbg !1737
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry5, i32 0, i32 1, !dbg !1737
  %10 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !1737
  store %struct.watcher_list* %10, %struct.watcher_list** %tmp, align 8, !dbg !1737
  br label %if.end, !dbg !1737

if.else6:                                         ; preds = %if.else
  %11 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1739
  store %struct.watcher_list* %11, %struct.watcher_list** %retval, align 8, !dbg !1739
  br label %return, !dbg !1739

if.end:                                           ; preds = %if.then4
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  br label %while.cond, !dbg !1741

while.end:                                        ; preds = %while.cond
  store %struct.watcher_list* null, %struct.watcher_list** %retval, align 8, !dbg !1743
  br label %return, !dbg !1743

return:                                           ; preds = %while.end, %if.else6
  %12 = load %struct.watcher_list*, %struct.watcher_list** %retval, align 8, !dbg !1745
  ret %struct.watcher_list* %12, !dbg !1745
}

; Function Attrs: nounwind uwtable
define internal i32 @compare_watchers(%struct.watcher_list* %a, %struct.watcher_list* %b) #0 !dbg !355 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.watcher_list*, align 8
  %b.addr = alloca %struct.watcher_list*, align 8
  store %struct.watcher_list* %a, %struct.watcher_list** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %a.addr, metadata !1747, metadata !368), !dbg !1748
  store %struct.watcher_list* %b, %struct.watcher_list** %b.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %b.addr, metadata !1749, metadata !368), !dbg !1750
  %0 = load %struct.watcher_list*, %struct.watcher_list** %a.addr, align 8, !dbg !1751
  %wd = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %0, i32 0, i32 4, !dbg !1753
  %1 = load i32, i32* %wd, align 8, !dbg !1753
  %2 = load %struct.watcher_list*, %struct.watcher_list** %b.addr, align 8, !dbg !1754
  %wd1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %2, i32 0, i32 4, !dbg !1755
  %3 = load i32, i32* %wd1, align 8, !dbg !1755
  %cmp = icmp slt i32 %1, %3, !dbg !1756
  br i1 %cmp, label %if.then, label %if.end, !dbg !1757

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !1758
  br label %return, !dbg !1758

if.end:                                           ; preds = %entry
  %4 = load %struct.watcher_list*, %struct.watcher_list** %a.addr, align 8, !dbg !1760
  %wd2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %4, i32 0, i32 4, !dbg !1762
  %5 = load i32, i32* %wd2, align 8, !dbg !1762
  %6 = load %struct.watcher_list*, %struct.watcher_list** %b.addr, align 8, !dbg !1763
  %wd3 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %6, i32 0, i32 4, !dbg !1764
  %7 = load i32, i32* %wd3, align 8, !dbg !1764
  %cmp4 = icmp sgt i32 %5, %7, !dbg !1765
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1766

if.then5:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !1767
  br label %return, !dbg !1767

if.end6:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1769
  br label %return, !dbg !1769

return:                                           ; preds = %if.end6, %if.then5, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1770
  ret i32 %8, !dbg !1770
}

; Function Attrs: nounwind uwtable
define internal void @watcher_root_RB_INSERT_COLOR(%struct.watcher_root* %head, %struct.watcher_list* %elm) #0 !dbg !361 {
entry:
  %head.addr = alloca %struct.watcher_root*, align 8
  %elm.addr = alloca %struct.watcher_list*, align 8
  %parent = alloca %struct.watcher_list*, align 8
  %gparent = alloca %struct.watcher_list*, align 8
  %tmp = alloca %struct.watcher_list*, align 8
  store %struct.watcher_root* %head, %struct.watcher_root** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_root** %head.addr, metadata !1771, metadata !368), !dbg !1772
  store %struct.watcher_list* %elm, %struct.watcher_list** %elm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %elm.addr, metadata !1773, metadata !368), !dbg !1772
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %parent, metadata !1774, metadata !368), !dbg !1772
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %gparent, metadata !1775, metadata !368), !dbg !1772
  call void @llvm.dbg.declare(metadata %struct.watcher_list** %tmp, metadata !1776, metadata !368), !dbg !1772
  br label %while.cond, !dbg !1772

while.cond:                                       ; preds = %if.end277, %do.end154, %do.end, %entry
  %0 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1777
  %entry1 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %0, i32 0, i32 0, !dbg !1777
  %rbe_parent = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry1, i32 0, i32 2, !dbg !1777
  %1 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent, align 8, !dbg !1777
  store %struct.watcher_list* %1, %struct.watcher_list** %parent, align 8, !dbg !1777
  %cmp = icmp ne %struct.watcher_list* %1, null, !dbg !1777
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1777

land.rhs:                                         ; preds = %while.cond
  %2 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1779
  %entry2 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %2, i32 0, i32 0, !dbg !1779
  %rbe_color = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry2, i32 0, i32 3, !dbg !1779
  %3 = load i32, i32* %rbe_color, align 8, !dbg !1779
  %cmp3 = icmp eq i32 %3, 1, !dbg !1779
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %4 = phi i1 [ false, %while.cond ], [ %cmp3, %land.rhs ]
  br i1 %4, label %while.body, label %while.end, !dbg !1781

while.body:                                       ; preds = %land.end
  %5 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1783
  %entry4 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %5, i32 0, i32 0, !dbg !1783
  %rbe_parent5 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry4, i32 0, i32 2, !dbg !1783
  %6 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent5, align 8, !dbg !1783
  store %struct.watcher_list* %6, %struct.watcher_list** %gparent, align 8, !dbg !1783
  %7 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1783
  %8 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1783
  %entry6 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %8, i32 0, i32 0, !dbg !1783
  %rbe_left = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry6, i32 0, i32 0, !dbg !1783
  %9 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left, align 8, !dbg !1783
  %cmp7 = icmp eq %struct.watcher_list* %7, %9, !dbg !1783
  br i1 %cmp7, label %if.then, label %if.else138, !dbg !1783

if.then:                                          ; preds = %while.body
  %10 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1786
  %entry8 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %10, i32 0, i32 0, !dbg !1786
  %rbe_right = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry8, i32 0, i32 1, !dbg !1786
  %11 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right, align 8, !dbg !1786
  store %struct.watcher_list* %11, %struct.watcher_list** %tmp, align 8, !dbg !1786
  %12 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1786
  %tobool = icmp ne %struct.watcher_list* %12, null, !dbg !1786
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !1786

land.lhs.true:                                    ; preds = %if.then
  %13 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1790
  %entry9 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %13, i32 0, i32 0, !dbg !1790
  %rbe_color10 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry9, i32 0, i32 3, !dbg !1790
  %14 = load i32, i32* %rbe_color10, align 8, !dbg !1790
  %cmp11 = icmp eq i32 %14, 1, !dbg !1790
  br i1 %cmp11, label %if.then12, label %if.end, !dbg !1790

if.then12:                                        ; preds = %land.lhs.true
  %15 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1793
  %entry13 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %15, i32 0, i32 0, !dbg !1793
  %rbe_color14 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry13, i32 0, i32 3, !dbg !1793
  store i32 0, i32* %rbe_color14, align 8, !dbg !1793
  br label %do.body, !dbg !1793

do.body:                                          ; preds = %if.then12
  %16 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1796
  %entry15 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %16, i32 0, i32 0, !dbg !1796
  %rbe_color16 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry15, i32 0, i32 3, !dbg !1796
  store i32 0, i32* %rbe_color16, align 8, !dbg !1796
  %17 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1796
  %entry17 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %17, i32 0, i32 0, !dbg !1796
  %rbe_color18 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry17, i32 0, i32 3, !dbg !1796
  store i32 1, i32* %rbe_color18, align 8, !dbg !1796
  br label %do.end, !dbg !1796

do.end:                                           ; preds = %do.body
  %18 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1799
  store %struct.watcher_list* %18, %struct.watcher_list** %elm.addr, align 8, !dbg !1799
  br label %while.cond, !dbg !1799

if.end:                                           ; preds = %land.lhs.true, %if.then
  %19 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1801
  %entry19 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %19, i32 0, i32 0, !dbg !1801
  %rbe_right20 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry19, i32 0, i32 1, !dbg !1801
  %20 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right20, align 8, !dbg !1801
  %21 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1801
  %cmp21 = icmp eq %struct.watcher_list* %20, %21, !dbg !1801
  br i1 %cmp21, label %if.then22, label %if.end76, !dbg !1801

if.then22:                                        ; preds = %if.end
  br label %do.body23, !dbg !1804

do.body23:                                        ; preds = %if.then22
  %22 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1807
  %entry24 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %22, i32 0, i32 0, !dbg !1807
  %rbe_right25 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry24, i32 0, i32 1, !dbg !1807
  %23 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right25, align 8, !dbg !1807
  store %struct.watcher_list* %23, %struct.watcher_list** %tmp, align 8, !dbg !1807
  %24 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1807
  %entry26 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %24, i32 0, i32 0, !dbg !1807
  %rbe_left27 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry26, i32 0, i32 0, !dbg !1807
  %25 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left27, align 8, !dbg !1807
  %26 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1807
  %entry28 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %26, i32 0, i32 0, !dbg !1807
  %rbe_right29 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry28, i32 0, i32 1, !dbg !1807
  store %struct.watcher_list* %25, %struct.watcher_list** %rbe_right29, align 8, !dbg !1807
  %cmp30 = icmp ne %struct.watcher_list* %25, null, !dbg !1807
  br i1 %cmp30, label %if.then31, label %if.end36, !dbg !1807

if.then31:                                        ; preds = %do.body23
  %27 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1810
  %28 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1810
  %entry32 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %28, i32 0, i32 0, !dbg !1810
  %rbe_left33 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry32, i32 0, i32 0, !dbg !1810
  %29 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left33, align 8, !dbg !1810
  %entry34 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %29, i32 0, i32 0, !dbg !1810
  %rbe_parent35 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry34, i32 0, i32 2, !dbg !1810
  store %struct.watcher_list* %27, %struct.watcher_list** %rbe_parent35, align 8, !dbg !1810
  br label %if.end36, !dbg !1810

if.end36:                                         ; preds = %if.then31, %do.body23
  br label %do.body37, !dbg !1814

do.body37:                                        ; preds = %if.end36
  br label %do.end38, !dbg !1816

do.end38:                                         ; preds = %do.body37
  %30 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1819
  %entry39 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %30, i32 0, i32 0, !dbg !1819
  %rbe_parent40 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry39, i32 0, i32 2, !dbg !1819
  %31 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent40, align 8, !dbg !1819
  %32 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1819
  %entry41 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %32, i32 0, i32 0, !dbg !1819
  %rbe_parent42 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry41, i32 0, i32 2, !dbg !1819
  store %struct.watcher_list* %31, %struct.watcher_list** %rbe_parent42, align 8, !dbg !1819
  %cmp43 = icmp ne %struct.watcher_list* %31, null, !dbg !1819
  br i1 %cmp43, label %if.then44, label %if.else60, !dbg !1819

if.then44:                                        ; preds = %do.end38
  %33 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1822
  %34 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1822
  %entry45 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %34, i32 0, i32 0, !dbg !1822
  %rbe_parent46 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry45, i32 0, i32 2, !dbg !1822
  %35 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent46, align 8, !dbg !1822
  %entry47 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %35, i32 0, i32 0, !dbg !1822
  %rbe_left48 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry47, i32 0, i32 0, !dbg !1822
  %36 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left48, align 8, !dbg !1822
  %cmp49 = icmp eq %struct.watcher_list* %33, %36, !dbg !1822
  br i1 %cmp49, label %if.then50, label %if.else, !dbg !1822

if.then50:                                        ; preds = %if.then44
  %37 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1826
  %38 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1826
  %entry51 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %38, i32 0, i32 0, !dbg !1826
  %rbe_parent52 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry51, i32 0, i32 2, !dbg !1826
  %39 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent52, align 8, !dbg !1826
  %entry53 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %39, i32 0, i32 0, !dbg !1826
  %rbe_left54 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry53, i32 0, i32 0, !dbg !1826
  store %struct.watcher_list* %37, %struct.watcher_list** %rbe_left54, align 8, !dbg !1826
  br label %if.end59, !dbg !1826

if.else:                                          ; preds = %if.then44
  %40 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1828
  %41 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1828
  %entry55 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %41, i32 0, i32 0, !dbg !1828
  %rbe_parent56 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry55, i32 0, i32 2, !dbg !1828
  %42 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent56, align 8, !dbg !1828
  %entry57 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %42, i32 0, i32 0, !dbg !1828
  %rbe_right58 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry57, i32 0, i32 1, !dbg !1828
  store %struct.watcher_list* %40, %struct.watcher_list** %rbe_right58, align 8, !dbg !1828
  br label %if.end59

if.end59:                                         ; preds = %if.else, %if.then50
  br label %if.end61, !dbg !1830

if.else60:                                        ; preds = %do.end38
  %43 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1832
  %44 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1832
  %rbh_root = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %44, i32 0, i32 0, !dbg !1832
  store %struct.watcher_list* %43, %struct.watcher_list** %rbh_root, align 8, !dbg !1832
  br label %if.end61

if.end61:                                         ; preds = %if.else60, %if.end59
  %45 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1834
  %46 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1834
  %entry62 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %46, i32 0, i32 0, !dbg !1834
  %rbe_left63 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry62, i32 0, i32 0, !dbg !1834
  store %struct.watcher_list* %45, %struct.watcher_list** %rbe_left63, align 8, !dbg !1834
  %47 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1834
  %48 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1834
  %entry64 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %48, i32 0, i32 0, !dbg !1834
  %rbe_parent65 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry64, i32 0, i32 2, !dbg !1834
  store %struct.watcher_list* %47, %struct.watcher_list** %rbe_parent65, align 8, !dbg !1834
  br label %do.body66, !dbg !1834

do.body66:                                        ; preds = %if.end61
  br label %do.end67, !dbg !1836

do.end67:                                         ; preds = %do.body66
  %49 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1839
  %entry68 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %49, i32 0, i32 0, !dbg !1839
  %rbe_parent69 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry68, i32 0, i32 2, !dbg !1839
  %50 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent69, align 8, !dbg !1839
  %tobool70 = icmp ne %struct.watcher_list* %50, null, !dbg !1839
  br i1 %tobool70, label %if.then71, label %if.end74, !dbg !1839

if.then71:                                        ; preds = %do.end67
  br label %do.body72, !dbg !1842

do.body72:                                        ; preds = %if.then71
  br label %do.end73, !dbg !1844

do.end73:                                         ; preds = %do.body72
  br label %if.end74, !dbg !1847

if.end74:                                         ; preds = %do.end73, %do.end67
  br label %do.end75, !dbg !1849

do.end75:                                         ; preds = %if.end74
  %51 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1851
  store %struct.watcher_list* %51, %struct.watcher_list** %tmp, align 8, !dbg !1851
  %52 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1851
  store %struct.watcher_list* %52, %struct.watcher_list** %parent, align 8, !dbg !1851
  %53 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1851
  store %struct.watcher_list* %53, %struct.watcher_list** %elm.addr, align 8, !dbg !1851
  br label %if.end76, !dbg !1851

if.end76:                                         ; preds = %do.end75, %if.end
  br label %do.body77, !dbg !1853

do.body77:                                        ; preds = %if.end76
  %54 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1855
  %entry78 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %54, i32 0, i32 0, !dbg !1855
  %rbe_color79 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry78, i32 0, i32 3, !dbg !1855
  store i32 0, i32* %rbe_color79, align 8, !dbg !1855
  %55 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1855
  %entry80 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %55, i32 0, i32 0, !dbg !1855
  %rbe_color81 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry80, i32 0, i32 3, !dbg !1855
  store i32 1, i32* %rbe_color81, align 8, !dbg !1855
  br label %do.end82, !dbg !1855

do.end82:                                         ; preds = %do.body77
  br label %do.body83, !dbg !1858

do.body83:                                        ; preds = %do.end82
  %56 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1860
  %entry84 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %56, i32 0, i32 0, !dbg !1860
  %rbe_left85 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry84, i32 0, i32 0, !dbg !1860
  %57 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left85, align 8, !dbg !1860
  store %struct.watcher_list* %57, %struct.watcher_list** %tmp, align 8, !dbg !1860
  %58 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1860
  %entry86 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %58, i32 0, i32 0, !dbg !1860
  %rbe_right87 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry86, i32 0, i32 1, !dbg !1860
  %59 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right87, align 8, !dbg !1860
  %60 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1860
  %entry88 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %60, i32 0, i32 0, !dbg !1860
  %rbe_left89 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry88, i32 0, i32 0, !dbg !1860
  store %struct.watcher_list* %59, %struct.watcher_list** %rbe_left89, align 8, !dbg !1860
  %cmp90 = icmp ne %struct.watcher_list* %59, null, !dbg !1860
  br i1 %cmp90, label %if.then91, label %if.end96, !dbg !1860

if.then91:                                        ; preds = %do.body83
  %61 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1863
  %62 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1863
  %entry92 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %62, i32 0, i32 0, !dbg !1863
  %rbe_right93 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry92, i32 0, i32 1, !dbg !1863
  %63 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right93, align 8, !dbg !1863
  %entry94 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %63, i32 0, i32 0, !dbg !1863
  %rbe_parent95 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry94, i32 0, i32 2, !dbg !1863
  store %struct.watcher_list* %61, %struct.watcher_list** %rbe_parent95, align 8, !dbg !1863
  br label %if.end96, !dbg !1863

if.end96:                                         ; preds = %if.then91, %do.body83
  br label %do.body97, !dbg !1867

do.body97:                                        ; preds = %if.end96
  br label %do.end98, !dbg !1869

do.end98:                                         ; preds = %do.body97
  %64 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1872
  %entry99 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %64, i32 0, i32 0, !dbg !1872
  %rbe_parent100 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry99, i32 0, i32 2, !dbg !1872
  %65 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent100, align 8, !dbg !1872
  %66 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1872
  %entry101 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %66, i32 0, i32 0, !dbg !1872
  %rbe_parent102 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry101, i32 0, i32 2, !dbg !1872
  store %struct.watcher_list* %65, %struct.watcher_list** %rbe_parent102, align 8, !dbg !1872
  %cmp103 = icmp ne %struct.watcher_list* %65, null, !dbg !1872
  br i1 %cmp103, label %if.then104, label %if.else121, !dbg !1872

if.then104:                                       ; preds = %do.end98
  %67 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1875
  %68 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1875
  %entry105 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %68, i32 0, i32 0, !dbg !1875
  %rbe_parent106 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry105, i32 0, i32 2, !dbg !1875
  %69 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent106, align 8, !dbg !1875
  %entry107 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %69, i32 0, i32 0, !dbg !1875
  %rbe_left108 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry107, i32 0, i32 0, !dbg !1875
  %70 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left108, align 8, !dbg !1875
  %cmp109 = icmp eq %struct.watcher_list* %67, %70, !dbg !1875
  br i1 %cmp109, label %if.then110, label %if.else115, !dbg !1875

if.then110:                                       ; preds = %if.then104
  %71 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1879
  %72 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1879
  %entry111 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %72, i32 0, i32 0, !dbg !1879
  %rbe_parent112 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry111, i32 0, i32 2, !dbg !1879
  %73 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent112, align 8, !dbg !1879
  %entry113 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %73, i32 0, i32 0, !dbg !1879
  %rbe_left114 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry113, i32 0, i32 0, !dbg !1879
  store %struct.watcher_list* %71, %struct.watcher_list** %rbe_left114, align 8, !dbg !1879
  br label %if.end120, !dbg !1879

if.else115:                                       ; preds = %if.then104
  %74 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1881
  %75 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1881
  %entry116 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %75, i32 0, i32 0, !dbg !1881
  %rbe_parent117 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry116, i32 0, i32 2, !dbg !1881
  %76 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent117, align 8, !dbg !1881
  %entry118 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %76, i32 0, i32 0, !dbg !1881
  %rbe_right119 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry118, i32 0, i32 1, !dbg !1881
  store %struct.watcher_list* %74, %struct.watcher_list** %rbe_right119, align 8, !dbg !1881
  br label %if.end120

if.end120:                                        ; preds = %if.else115, %if.then110
  br label %if.end123, !dbg !1883

if.else121:                                       ; preds = %do.end98
  %77 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1885
  %78 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1885
  %rbh_root122 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %78, i32 0, i32 0, !dbg !1885
  store %struct.watcher_list* %77, %struct.watcher_list** %rbh_root122, align 8, !dbg !1885
  br label %if.end123

if.end123:                                        ; preds = %if.else121, %if.end120
  %79 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1887
  %80 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1887
  %entry124 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %80, i32 0, i32 0, !dbg !1887
  %rbe_right125 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry124, i32 0, i32 1, !dbg !1887
  store %struct.watcher_list* %79, %struct.watcher_list** %rbe_right125, align 8, !dbg !1887
  %81 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1887
  %82 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1887
  %entry126 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %82, i32 0, i32 0, !dbg !1887
  %rbe_parent127 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry126, i32 0, i32 2, !dbg !1887
  store %struct.watcher_list* %81, %struct.watcher_list** %rbe_parent127, align 8, !dbg !1887
  br label %do.body128, !dbg !1887

do.body128:                                       ; preds = %if.end123
  br label %do.end129, !dbg !1889

do.end129:                                        ; preds = %do.body128
  %83 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1892
  %entry130 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %83, i32 0, i32 0, !dbg !1892
  %rbe_parent131 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry130, i32 0, i32 2, !dbg !1892
  %84 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent131, align 8, !dbg !1892
  %tobool132 = icmp ne %struct.watcher_list* %84, null, !dbg !1892
  br i1 %tobool132, label %if.then133, label %if.end136, !dbg !1892

if.then133:                                       ; preds = %do.end129
  br label %do.body134, !dbg !1895

do.body134:                                       ; preds = %if.then133
  br label %do.end135, !dbg !1897

do.end135:                                        ; preds = %do.body134
  br label %if.end136, !dbg !1900

if.end136:                                        ; preds = %do.end135, %do.end129
  br label %do.end137, !dbg !1902

do.end137:                                        ; preds = %if.end136
  br label %if.end277, !dbg !1904

if.else138:                                       ; preds = %while.body
  %85 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1906
  %entry139 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %85, i32 0, i32 0, !dbg !1906
  %rbe_left140 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry139, i32 0, i32 0, !dbg !1906
  %86 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left140, align 8, !dbg !1906
  store %struct.watcher_list* %86, %struct.watcher_list** %tmp, align 8, !dbg !1906
  %87 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1906
  %tobool141 = icmp ne %struct.watcher_list* %87, null, !dbg !1906
  br i1 %tobool141, label %land.lhs.true142, label %if.end155, !dbg !1906

land.lhs.true142:                                 ; preds = %if.else138
  %88 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1909
  %entry143 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %88, i32 0, i32 0, !dbg !1909
  %rbe_color144 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry143, i32 0, i32 3, !dbg !1909
  %89 = load i32, i32* %rbe_color144, align 8, !dbg !1909
  %cmp145 = icmp eq i32 %89, 1, !dbg !1909
  br i1 %cmp145, label %if.then146, label %if.end155, !dbg !1909

if.then146:                                       ; preds = %land.lhs.true142
  %90 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1912
  %entry147 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %90, i32 0, i32 0, !dbg !1912
  %rbe_color148 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry147, i32 0, i32 3, !dbg !1912
  store i32 0, i32* %rbe_color148, align 8, !dbg !1912
  br label %do.body149, !dbg !1912

do.body149:                                       ; preds = %if.then146
  %91 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1915
  %entry150 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %91, i32 0, i32 0, !dbg !1915
  %rbe_color151 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry150, i32 0, i32 3, !dbg !1915
  store i32 0, i32* %rbe_color151, align 8, !dbg !1915
  %92 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1915
  %entry152 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %92, i32 0, i32 0, !dbg !1915
  %rbe_color153 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry152, i32 0, i32 3, !dbg !1915
  store i32 1, i32* %rbe_color153, align 8, !dbg !1915
  br label %do.end154, !dbg !1915

do.end154:                                        ; preds = %do.body149
  %93 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1918
  store %struct.watcher_list* %93, %struct.watcher_list** %elm.addr, align 8, !dbg !1918
  br label %while.cond, !dbg !1918

if.end155:                                        ; preds = %land.lhs.true142, %if.else138
  %94 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1920
  %entry156 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %94, i32 0, i32 0, !dbg !1920
  %rbe_left157 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry156, i32 0, i32 0, !dbg !1920
  %95 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left157, align 8, !dbg !1920
  %96 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1920
  %cmp158 = icmp eq %struct.watcher_list* %95, %96, !dbg !1920
  br i1 %cmp158, label %if.then159, label %if.end215, !dbg !1920

if.then159:                                       ; preds = %if.end155
  br label %do.body160, !dbg !1923

do.body160:                                       ; preds = %if.then159
  %97 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1926
  %entry161 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %97, i32 0, i32 0, !dbg !1926
  %rbe_left162 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry161, i32 0, i32 0, !dbg !1926
  %98 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left162, align 8, !dbg !1926
  store %struct.watcher_list* %98, %struct.watcher_list** %tmp, align 8, !dbg !1926
  %99 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1926
  %entry163 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %99, i32 0, i32 0, !dbg !1926
  %rbe_right164 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry163, i32 0, i32 1, !dbg !1926
  %100 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right164, align 8, !dbg !1926
  %101 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1926
  %entry165 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %101, i32 0, i32 0, !dbg !1926
  %rbe_left166 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry165, i32 0, i32 0, !dbg !1926
  store %struct.watcher_list* %100, %struct.watcher_list** %rbe_left166, align 8, !dbg !1926
  %cmp167 = icmp ne %struct.watcher_list* %100, null, !dbg !1926
  br i1 %cmp167, label %if.then168, label %if.end173, !dbg !1926

if.then168:                                       ; preds = %do.body160
  %102 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1929
  %103 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1929
  %entry169 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %103, i32 0, i32 0, !dbg !1929
  %rbe_right170 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry169, i32 0, i32 1, !dbg !1929
  %104 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right170, align 8, !dbg !1929
  %entry171 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %104, i32 0, i32 0, !dbg !1929
  %rbe_parent172 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry171, i32 0, i32 2, !dbg !1929
  store %struct.watcher_list* %102, %struct.watcher_list** %rbe_parent172, align 8, !dbg !1929
  br label %if.end173, !dbg !1929

if.end173:                                        ; preds = %if.then168, %do.body160
  br label %do.body174, !dbg !1933

do.body174:                                       ; preds = %if.end173
  br label %do.end175, !dbg !1935

do.end175:                                        ; preds = %do.body174
  %105 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1938
  %entry176 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %105, i32 0, i32 0, !dbg !1938
  %rbe_parent177 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry176, i32 0, i32 2, !dbg !1938
  %106 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent177, align 8, !dbg !1938
  %107 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1938
  %entry178 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %107, i32 0, i32 0, !dbg !1938
  %rbe_parent179 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry178, i32 0, i32 2, !dbg !1938
  store %struct.watcher_list* %106, %struct.watcher_list** %rbe_parent179, align 8, !dbg !1938
  %cmp180 = icmp ne %struct.watcher_list* %106, null, !dbg !1938
  br i1 %cmp180, label %if.then181, label %if.else198, !dbg !1938

if.then181:                                       ; preds = %do.end175
  %108 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1941
  %109 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1941
  %entry182 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %109, i32 0, i32 0, !dbg !1941
  %rbe_parent183 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry182, i32 0, i32 2, !dbg !1941
  %110 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent183, align 8, !dbg !1941
  %entry184 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %110, i32 0, i32 0, !dbg !1941
  %rbe_left185 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry184, i32 0, i32 0, !dbg !1941
  %111 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left185, align 8, !dbg !1941
  %cmp186 = icmp eq %struct.watcher_list* %108, %111, !dbg !1941
  br i1 %cmp186, label %if.then187, label %if.else192, !dbg !1941

if.then187:                                       ; preds = %if.then181
  %112 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1945
  %113 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1945
  %entry188 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %113, i32 0, i32 0, !dbg !1945
  %rbe_parent189 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry188, i32 0, i32 2, !dbg !1945
  %114 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent189, align 8, !dbg !1945
  %entry190 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %114, i32 0, i32 0, !dbg !1945
  %rbe_left191 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry190, i32 0, i32 0, !dbg !1945
  store %struct.watcher_list* %112, %struct.watcher_list** %rbe_left191, align 8, !dbg !1945
  br label %if.end197, !dbg !1945

if.else192:                                       ; preds = %if.then181
  %115 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1947
  %116 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1947
  %entry193 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %116, i32 0, i32 0, !dbg !1947
  %rbe_parent194 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry193, i32 0, i32 2, !dbg !1947
  %117 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent194, align 8, !dbg !1947
  %entry195 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %117, i32 0, i32 0, !dbg !1947
  %rbe_right196 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry195, i32 0, i32 1, !dbg !1947
  store %struct.watcher_list* %115, %struct.watcher_list** %rbe_right196, align 8, !dbg !1947
  br label %if.end197

if.end197:                                        ; preds = %if.else192, %if.then187
  br label %if.end200, !dbg !1949

if.else198:                                       ; preds = %do.end175
  %118 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1951
  %119 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !1951
  %rbh_root199 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %119, i32 0, i32 0, !dbg !1951
  store %struct.watcher_list* %118, %struct.watcher_list** %rbh_root199, align 8, !dbg !1951
  br label %if.end200

if.end200:                                        ; preds = %if.else198, %if.end197
  %120 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1953
  %121 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1953
  %entry201 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %121, i32 0, i32 0, !dbg !1953
  %rbe_right202 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry201, i32 0, i32 1, !dbg !1953
  store %struct.watcher_list* %120, %struct.watcher_list** %rbe_right202, align 8, !dbg !1953
  %122 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1953
  %123 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1953
  %entry203 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %123, i32 0, i32 0, !dbg !1953
  %rbe_parent204 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry203, i32 0, i32 2, !dbg !1953
  store %struct.watcher_list* %122, %struct.watcher_list** %rbe_parent204, align 8, !dbg !1953
  br label %do.body205, !dbg !1953

do.body205:                                       ; preds = %if.end200
  br label %do.end206, !dbg !1955

do.end206:                                        ; preds = %do.body205
  %124 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1958
  %entry207 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %124, i32 0, i32 0, !dbg !1958
  %rbe_parent208 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry207, i32 0, i32 2, !dbg !1958
  %125 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent208, align 8, !dbg !1958
  %tobool209 = icmp ne %struct.watcher_list* %125, null, !dbg !1958
  br i1 %tobool209, label %if.then210, label %if.end213, !dbg !1958

if.then210:                                       ; preds = %do.end206
  br label %do.body211, !dbg !1961

do.body211:                                       ; preds = %if.then210
  br label %do.end212, !dbg !1963

do.end212:                                        ; preds = %do.body211
  br label %if.end213, !dbg !1966

if.end213:                                        ; preds = %do.end212, %do.end206
  br label %do.end214, !dbg !1968

do.end214:                                        ; preds = %if.end213
  %126 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1970
  store %struct.watcher_list* %126, %struct.watcher_list** %tmp, align 8, !dbg !1970
  %127 = load %struct.watcher_list*, %struct.watcher_list** %elm.addr, align 8, !dbg !1970
  store %struct.watcher_list* %127, %struct.watcher_list** %parent, align 8, !dbg !1970
  %128 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1970
  store %struct.watcher_list* %128, %struct.watcher_list** %elm.addr, align 8, !dbg !1970
  br label %if.end215, !dbg !1970

if.end215:                                        ; preds = %do.end214, %if.end155
  br label %do.body216, !dbg !1972

do.body216:                                       ; preds = %if.end215
  %129 = load %struct.watcher_list*, %struct.watcher_list** %parent, align 8, !dbg !1974
  %entry217 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %129, i32 0, i32 0, !dbg !1974
  %rbe_color218 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry217, i32 0, i32 3, !dbg !1974
  store i32 0, i32* %rbe_color218, align 8, !dbg !1974
  %130 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1974
  %entry219 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %130, i32 0, i32 0, !dbg !1974
  %rbe_color220 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry219, i32 0, i32 3, !dbg !1974
  store i32 1, i32* %rbe_color220, align 8, !dbg !1974
  br label %do.end221, !dbg !1974

do.end221:                                        ; preds = %do.body216
  br label %do.body222, !dbg !1977

do.body222:                                       ; preds = %do.end221
  %131 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1979
  %entry223 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %131, i32 0, i32 0, !dbg !1979
  %rbe_right224 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry223, i32 0, i32 1, !dbg !1979
  %132 = load %struct.watcher_list*, %struct.watcher_list** %rbe_right224, align 8, !dbg !1979
  store %struct.watcher_list* %132, %struct.watcher_list** %tmp, align 8, !dbg !1979
  %133 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1979
  %entry225 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %133, i32 0, i32 0, !dbg !1979
  %rbe_left226 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry225, i32 0, i32 0, !dbg !1979
  %134 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left226, align 8, !dbg !1979
  %135 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1979
  %entry227 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %135, i32 0, i32 0, !dbg !1979
  %rbe_right228 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry227, i32 0, i32 1, !dbg !1979
  store %struct.watcher_list* %134, %struct.watcher_list** %rbe_right228, align 8, !dbg !1979
  %cmp229 = icmp ne %struct.watcher_list* %134, null, !dbg !1979
  br i1 %cmp229, label %if.then230, label %if.end235, !dbg !1979

if.then230:                                       ; preds = %do.body222
  %136 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1982
  %137 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1982
  %entry231 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %137, i32 0, i32 0, !dbg !1982
  %rbe_left232 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry231, i32 0, i32 0, !dbg !1982
  %138 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left232, align 8, !dbg !1982
  %entry233 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %138, i32 0, i32 0, !dbg !1982
  %rbe_parent234 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry233, i32 0, i32 2, !dbg !1982
  store %struct.watcher_list* %136, %struct.watcher_list** %rbe_parent234, align 8, !dbg !1982
  br label %if.end235, !dbg !1982

if.end235:                                        ; preds = %if.then230, %do.body222
  br label %do.body236, !dbg !1986

do.body236:                                       ; preds = %if.end235
  br label %do.end237, !dbg !1988

do.end237:                                        ; preds = %do.body236
  %139 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1991
  %entry238 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %139, i32 0, i32 0, !dbg !1991
  %rbe_parent239 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry238, i32 0, i32 2, !dbg !1991
  %140 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent239, align 8, !dbg !1991
  %141 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1991
  %entry240 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %141, i32 0, i32 0, !dbg !1991
  %rbe_parent241 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry240, i32 0, i32 2, !dbg !1991
  store %struct.watcher_list* %140, %struct.watcher_list** %rbe_parent241, align 8, !dbg !1991
  %cmp242 = icmp ne %struct.watcher_list* %140, null, !dbg !1991
  br i1 %cmp242, label %if.then243, label %if.else260, !dbg !1991

if.then243:                                       ; preds = %do.end237
  %142 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1994
  %143 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1994
  %entry244 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %143, i32 0, i32 0, !dbg !1994
  %rbe_parent245 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry244, i32 0, i32 2, !dbg !1994
  %144 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent245, align 8, !dbg !1994
  %entry246 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %144, i32 0, i32 0, !dbg !1994
  %rbe_left247 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry246, i32 0, i32 0, !dbg !1994
  %145 = load %struct.watcher_list*, %struct.watcher_list** %rbe_left247, align 8, !dbg !1994
  %cmp248 = icmp eq %struct.watcher_list* %142, %145, !dbg !1994
  br i1 %cmp248, label %if.then249, label %if.else254, !dbg !1994

if.then249:                                       ; preds = %if.then243
  %146 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !1998
  %147 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !1998
  %entry250 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %147, i32 0, i32 0, !dbg !1998
  %rbe_parent251 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry250, i32 0, i32 2, !dbg !1998
  %148 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent251, align 8, !dbg !1998
  %entry252 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %148, i32 0, i32 0, !dbg !1998
  %rbe_left253 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry252, i32 0, i32 0, !dbg !1998
  store %struct.watcher_list* %146, %struct.watcher_list** %rbe_left253, align 8, !dbg !1998
  br label %if.end259, !dbg !1998

if.else254:                                       ; preds = %if.then243
  %149 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !2000
  %150 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !2000
  %entry255 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %150, i32 0, i32 0, !dbg !2000
  %rbe_parent256 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry255, i32 0, i32 2, !dbg !2000
  %151 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent256, align 8, !dbg !2000
  %entry257 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %151, i32 0, i32 0, !dbg !2000
  %rbe_right258 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry257, i32 0, i32 1, !dbg !2000
  store %struct.watcher_list* %149, %struct.watcher_list** %rbe_right258, align 8, !dbg !2000
  br label %if.end259

if.end259:                                        ; preds = %if.else254, %if.then249
  br label %if.end262, !dbg !2002

if.else260:                                       ; preds = %do.end237
  %152 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !2004
  %153 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !2004
  %rbh_root261 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %153, i32 0, i32 0, !dbg !2004
  store %struct.watcher_list* %152, %struct.watcher_list** %rbh_root261, align 8, !dbg !2004
  br label %if.end262

if.end262:                                        ; preds = %if.else260, %if.end259
  %154 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !2006
  %155 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !2006
  %entry263 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %155, i32 0, i32 0, !dbg !2006
  %rbe_left264 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry263, i32 0, i32 0, !dbg !2006
  store %struct.watcher_list* %154, %struct.watcher_list** %rbe_left264, align 8, !dbg !2006
  %156 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !2006
  %157 = load %struct.watcher_list*, %struct.watcher_list** %gparent, align 8, !dbg !2006
  %entry265 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %157, i32 0, i32 0, !dbg !2006
  %rbe_parent266 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry265, i32 0, i32 2, !dbg !2006
  store %struct.watcher_list* %156, %struct.watcher_list** %rbe_parent266, align 8, !dbg !2006
  br label %do.body267, !dbg !2006

do.body267:                                       ; preds = %if.end262
  br label %do.end268, !dbg !2008

do.end268:                                        ; preds = %do.body267
  %158 = load %struct.watcher_list*, %struct.watcher_list** %tmp, align 8, !dbg !2011
  %entry269 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %158, i32 0, i32 0, !dbg !2011
  %rbe_parent270 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry269, i32 0, i32 2, !dbg !2011
  %159 = load %struct.watcher_list*, %struct.watcher_list** %rbe_parent270, align 8, !dbg !2011
  %tobool271 = icmp ne %struct.watcher_list* %159, null, !dbg !2011
  br i1 %tobool271, label %if.then272, label %if.end275, !dbg !2011

if.then272:                                       ; preds = %do.end268
  br label %do.body273, !dbg !2014

do.body273:                                       ; preds = %if.then272
  br label %do.end274, !dbg !2016

do.end274:                                        ; preds = %do.body273
  br label %if.end275, !dbg !2019

if.end275:                                        ; preds = %do.end274, %do.end268
  br label %do.end276, !dbg !2021

do.end276:                                        ; preds = %if.end275
  br label %if.end277

if.end277:                                        ; preds = %do.end276, %do.end137
  br label %while.cond, !dbg !2023

while.end:                                        ; preds = %land.end
  %160 = load %struct.watcher_root*, %struct.watcher_root** %head.addr, align 8, !dbg !2025
  %rbh_root278 = getelementptr inbounds %struct.watcher_root, %struct.watcher_root* %160, i32 0, i32 0, !dbg !2025
  %161 = load %struct.watcher_list*, %struct.watcher_list** %rbh_root278, align 8, !dbg !2025
  %entry279 = getelementptr inbounds %struct.watcher_list, %struct.watcher_list* %161, i32 0, i32 0, !dbg !2025
  %rbe_color280 = getelementptr inbounds %struct.anon.4, %struct.anon.4* %entry279, i32 0, i32 3, !dbg !2025
  store i32 0, i32* %rbe_color280, align 8, !dbg !2025
  ret void, !dbg !2025
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { argmemonly nounwind }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind readonly }
attributes #10 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!364, !365}
!llvm.ident = !{!366}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !37, subprograms: !306)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-inotify.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
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
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "uv_fs_event", file: !4, line: 1291, size: 32, align: 32, elements: !34)
!34 = !{!35, !36}
!35 = !DIEnumerator(name: "UV_RENAME", value: 1)
!36 = !DIEnumerator(name: "UV_CHANGE", value: 2)
!37 = !{!38, !39, !46, !67, !69, !64, !155, !295, !291}
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !42, line: 21, baseType: !43)
!42 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!43 = !DICompositeType(tag: DW_TAG_array_type, baseType: !38, size: 128, align: 64, elements: !44)
!44 = !{!45}
!45 = !DISubrange(count: 2)
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!47 = !DICompositeType(tag: DW_TAG_structure_type, name: "watcher_root", file: !1, line: 43, size: 64, align: 64, elements: !48)
!48 = !{!49}
!49 = !DIDerivedType(tag: DW_TAG_member, name: "rbh_root", scope: !47, file: !1, line: 44, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DICompositeType(tag: DW_TAG_structure_type, name: "watcher_list", file: !1, line: 35, size: 576, align: 64, elements: !52)
!52 = !{!53, !61, !62, !63, !66}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !51, file: !1, line: 36, baseType: !54, size: 256, align: 64)
!54 = !DICompositeType(tag: DW_TAG_structure_type, scope: !51, file: !1, line: 36, size: 256, align: 64, elements: !55)
!55 = !{!56, !57, !58, !59}
!56 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !54, file: !1, line: 36, baseType: !50, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !54, file: !1, line: 36, baseType: !50, size: 64, align: 64, offset: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !54, file: !1, line: 36, baseType: !50, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !54, file: !1, line: 36, baseType: !60, size: 32, align: 32, offset: 192)
!60 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !51, file: !1, line: 37, baseType: !41, size: 128, align: 64, offset: 256)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "iterating", scope: !51, file: !1, line: 38, baseType: !60, size: 32, align: 32, offset: 384)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !51, file: !1, line: 39, baseType: !64, size: 64, align: 64, offset: 448)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!65 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "wd", scope: !51, file: !1, line: 40, baseType: !60, size: 32, align: 32, offset: 512)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !41)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_event_t", file: !4, line: 218, baseType: !71)
!71 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_event_s", file: !4, line: 1297, size: 1088, align: 64, elements: !72)
!72 = !{!73, !74, !275, !276, !277, !278, !283, !284, !285, !286, !293, !294}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !71, file: !4, line: 1298, baseType: !38, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !71, file: !4, line: 1298, baseType: !75, size: 64, align: 64, offset: 64)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !77)
!77 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !78)
!78 = !{!79, !80, !82, !83, !84, !85, !87, !88, !89, !90, !109, !110, !111, !112, !142, !190, !214, !215, !216, !217, !218, !219, !220, !224, !225, !226, !231, !234, !235, !237, !238, !271, !272, !273, !274}
!79 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !77, file: !4, line: 1475, baseType: !38, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !77, file: !4, line: 1477, baseType: !81, size: 32, align: 32, offset: 64)
!81 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !77, file: !4, line: 1478, baseType: !43, size: 128, align: 64, offset: 128)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !77, file: !4, line: 1479, baseType: !43, size: 128, align: 64, offset: 256)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !77, file: !4, line: 1481, baseType: !81, size: 32, align: 32, offset: 384)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !77, file: !4, line: 1482, baseType: !86, size: 64, align: 64, offset: 448)
!86 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !77, file: !4, line: 1482, baseType: !60, size: 32, align: 32, offset: 512)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 576)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 704)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !77, file: !4, line: 1482, baseType: !91, size: 64, align: 64, offset: 832)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !94, line: 87, baseType: !95)
!94 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!95 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !94, line: 89, size: 448, align: 64, elements: !96)
!96 = !{!97, !104, !105, !106, !107, !108}
!97 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !95, file: !94, line: 90, baseType: !98, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !94, line: 84, baseType: !99)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DISubroutineType(types: !101)
!101 = !{null, !102, !103, !81}
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !95, file: !94, line: 91, baseType: !43, size: 128, align: 64, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !95, file: !94, line: 92, baseType: !43, size: 128, align: 64, offset: 192)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !95, file: !94, line: 93, baseType: !81, size: 32, align: 32, offset: 320)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !95, file: !94, line: 94, baseType: !81, size: 32, align: 32, offset: 352)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !95, file: !94, line: 95, baseType: !60, size: 32, align: 32, offset: 384)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !77, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 896)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !77, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 928)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 960)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !77, file: !4, line: 1482, baseType: !113, size: 320, align: 64, offset: 1088)
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !94, line: 129, baseType: !114)
!114 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !115, line: 127, baseType: !116)
!115 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!116 = !DICompositeType(tag: DW_TAG_union_type, file: !115, line: 90, size: 320, align: 64, elements: !117)
!117 = !{!118, !136, !140}
!118 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !116, file: !115, line: 124, baseType: !119, size: 320, align: 64)
!119 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !115, line: 92, size: 320, align: 64, elements: !120)
!120 = !{!121, !122, !123, !124, !125, !126, !128, !129}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !119, file: !115, line: 94, baseType: !60, size: 32, align: 32)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !119, file: !115, line: 95, baseType: !81, size: 32, align: 32, offset: 32)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !119, file: !115, line: 96, baseType: !60, size: 32, align: 32, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !119, file: !115, line: 98, baseType: !81, size: 32, align: 32, offset: 96)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !119, file: !115, line: 102, baseType: !60, size: 32, align: 32, offset: 128)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !119, file: !115, line: 104, baseType: !127, size: 16, align: 16, offset: 160)
!127 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !119, file: !115, line: 105, baseType: !127, size: 16, align: 16, offset: 176)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !119, file: !115, line: 106, baseType: !130, size: 128, align: 64, offset: 192)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !115, line: 79, baseType: !131)
!131 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !115, line: 75, size: 128, align: 64, elements: !132)
!132 = !{!133, !135}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !131, file: !115, line: 77, baseType: !134, size: 64, align: 64)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !131, size: 64, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !131, file: !115, line: 78, baseType: !134, size: 64, align: 64, offset: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !116, file: !115, line: 125, baseType: !137, size: 320, align: 8)
!137 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 320, align: 8, elements: !138)
!138 = !{!139}
!139 = !DISubrange(count: 40)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !116, file: !115, line: 126, baseType: !141, size: 64, align: 64)
!141 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !77, file: !4, line: 1482, baseType: !143, size: 1024, align: 64, offset: 1408)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !144)
!144 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !145)
!145 = !{!146, !147, !148, !150, !174, !175, !180, !181, !182, !188, !189}
!146 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !144, file: !4, line: 768, baseType: !38, size: 64, align: 64)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !144, file: !4, line: 768, baseType: !75, size: 64, align: 64, offset: 64)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !144, file: !4, line: 768, baseType: !149, size: 32, align: 32, offset: 128)
!149 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !144, file: !4, line: 768, baseType: !151, size: 64, align: 64, offset: 192)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !152)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{null, !155}
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !156, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !157)
!157 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !158)
!158 = !{!159, !160, !161, !162, !163, !164, !172, !173}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !157, file: !4, line: 426, baseType: !38, size: 64, align: 64)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !157, file: !4, line: 426, baseType: !75, size: 64, align: 64, offset: 64)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !157, file: !4, line: 426, baseType: !149, size: 32, align: 32, offset: 128)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !157, file: !4, line: 426, baseType: !151, size: 64, align: 64, offset: 192)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !157, file: !4, line: 426, baseType: !43, size: 128, align: 64, offset: 256)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !157, file: !4, line: 426, baseType: !165, size: 256, align: 64, offset: 384)
!165 = !DICompositeType(tag: DW_TAG_union_type, scope: !157, file: !4, line: 426, size: 256, align: 64, elements: !166)
!166 = !{!167, !168}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !165, file: !4, line: 426, baseType: !60, size: 32, align: 32)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !165, file: !4, line: 426, baseType: !169, size: 256, align: 64)
!169 = !DICompositeType(tag: DW_TAG_array_type, baseType: !38, size: 256, align: 64, elements: !170)
!170 = !{!171}
!171 = !DISubrange(count: 4)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !157, file: !4, line: 426, baseType: !155, size: 64, align: 64, offset: 640)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !157, file: !4, line: 426, baseType: !81, size: 32, align: 32, offset: 704)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !144, file: !4, line: 768, baseType: !43, size: 128, align: 64, offset: 256)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !144, file: !4, line: 768, baseType: !176, size: 256, align: 64, offset: 384)
!176 = !DICompositeType(tag: DW_TAG_union_type, scope: !144, file: !4, line: 768, size: 256, align: 64, elements: !177)
!177 = !{!178, !179}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !176, file: !4, line: 768, baseType: !60, size: 32, align: 32)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !176, file: !4, line: 768, baseType: !169, size: 256, align: 64)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !144, file: !4, line: 768, baseType: !155, size: 64, align: 64, offset: 640)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !144, file: !4, line: 768, baseType: !81, size: 32, align: 32, offset: 704)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !144, file: !4, line: 769, baseType: !183, size: 64, align: 64, offset: 768)
!183 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !184)
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !185, size: 64, align: 64)
!185 = !DISubroutineType(types: !186)
!186 = !{null, !187}
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !144, file: !4, line: 769, baseType: !43, size: 128, align: 64, offset: 832)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !144, file: !4, line: 769, baseType: !60, size: 32, align: 32, offset: 960)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !77, file: !4, line: 1482, baseType: !191, size: 448, align: 64, offset: 2432)
!191 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !94, line: 130, baseType: !192)
!192 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !115, line: 213, baseType: !193)
!193 = !DICompositeType(tag: DW_TAG_union_type, file: !115, line: 173, size: 448, align: 64, elements: !194)
!194 = !{!195, !209, !213}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !193, file: !115, line: 192, baseType: !196, size: 448, align: 64)
!196 = !DICompositeType(tag: DW_TAG_structure_type, scope: !193, file: !115, line: 176, size: 448, align: 64, elements: !197)
!197 = !{!198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !196, file: !115, line: 178, baseType: !60, size: 32, align: 32)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !196, file: !115, line: 179, baseType: !81, size: 32, align: 32, offset: 32)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !196, file: !115, line: 180, baseType: !81, size: 32, align: 32, offset: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !196, file: !115, line: 181, baseType: !81, size: 32, align: 32, offset: 96)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !196, file: !115, line: 182, baseType: !81, size: 32, align: 32, offset: 128)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !196, file: !115, line: 183, baseType: !81, size: 32, align: 32, offset: 160)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !196, file: !115, line: 184, baseType: !60, size: 32, align: 32, offset: 192)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !196, file: !115, line: 185, baseType: !60, size: 32, align: 32, offset: 224)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !196, file: !115, line: 186, baseType: !86, size: 64, align: 64, offset: 256)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !196, file: !115, line: 187, baseType: !86, size: 64, align: 64, offset: 320)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !196, file: !115, line: 190, baseType: !81, size: 32, align: 32, offset: 384)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !193, file: !115, line: 211, baseType: !210, size: 448, align: 8)
!210 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 448, align: 8, elements: !211)
!211 = !{!212}
!212 = !DISubrange(count: 56)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !193, file: !115, line: 212, baseType: !141, size: 64, align: 64)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !77, file: !4, line: 1482, baseType: !155, size: 64, align: 64, offset: 2880)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 2944)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 3072)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 3200)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 3328)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !77, file: !4, line: 1482, baseType: !43, size: 128, align: 64, offset: 3456)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !77, file: !4, line: 1482, baseType: !221, size: 64, align: 64, offset: 3584)
!221 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !222, size: 64, align: 64)
!222 = !DISubroutineType(types: !223)
!223 = !{null}
!224 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !77, file: !4, line: 1482, baseType: !93, size: 448, align: 64, offset: 3648)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !77, file: !4, line: 1482, baseType: !60, size: 32, align: 32, offset: 4096)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !77, file: !4, line: 1482, baseType: !227, size: 128, align: 64, offset: 4160)
!227 = !DICompositeType(tag: DW_TAG_structure_type, scope: !77, file: !4, line: 1482, size: 128, align: 64, elements: !228)
!228 = !{!229, !230}
!229 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !227, file: !4, line: 1482, baseType: !38, size: 64, align: 64)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !227, file: !4, line: 1482, baseType: !81, size: 32, align: 32, offset: 64)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !77, file: !4, line: 1482, baseType: !232, size: 64, align: 64, offset: 4288)
!232 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !233, line: 55, baseType: !86)
!233 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!234 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !77, file: !4, line: 1482, baseType: !232, size: 64, align: 64, offset: 4352)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !77, file: !4, line: 1482, baseType: !236, size: 64, align: 32, offset: 4416)
!236 = !DICompositeType(tag: DW_TAG_array_type, baseType: !60, size: 64, align: 32, elements: !44)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !77, file: !4, line: 1482, baseType: !93, size: 448, align: 64, offset: 4480)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !77, file: !4, line: 1482, baseType: !239, size: 1216, align: 64, offset: 4928)
!239 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !240)
!240 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !241)
!241 = !{!242, !243, !244, !245, !246, !247, !252, !253, !254, !260, !261, !269, !270}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !240, file: !4, line: 1326, baseType: !38, size: 64, align: 64)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !240, file: !4, line: 1326, baseType: !75, size: 64, align: 64, offset: 64)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !240, file: !4, line: 1326, baseType: !149, size: 32, align: 32, offset: 128)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !240, file: !4, line: 1326, baseType: !151, size: 64, align: 64, offset: 192)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !240, file: !4, line: 1326, baseType: !43, size: 128, align: 64, offset: 256)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !240, file: !4, line: 1326, baseType: !248, size: 256, align: 64, offset: 384)
!248 = !DICompositeType(tag: DW_TAG_union_type, scope: !240, file: !4, line: 1326, size: 256, align: 64, elements: !249)
!249 = !{!250, !251}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !248, file: !4, line: 1326, baseType: !60, size: 32, align: 32)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !248, file: !4, line: 1326, baseType: !169, size: 256, align: 64)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !240, file: !4, line: 1326, baseType: !155, size: 64, align: 64, offset: 640)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !240, file: !4, line: 1326, baseType: !81, size: 32, align: 32, offset: 704)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !240, file: !4, line: 1327, baseType: !255, size: 64, align: 64, offset: 768)
!255 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !256)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DISubroutineType(types: !258)
!258 = !{null, !259, !60}
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !240, file: !4, line: 1328, baseType: !60, size: 32, align: 32, offset: 832)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !240, file: !4, line: 1329, baseType: !262, size: 256, align: 64, offset: 896)
!262 = !DICompositeType(tag: DW_TAG_structure_type, scope: !240, file: !4, line: 1329, size: 256, align: 64, elements: !263)
!263 = !{!264, !266, !267, !268}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !262, file: !4, line: 1329, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !240, size: 64, align: 64)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !262, file: !4, line: 1329, baseType: !265, size: 64, align: 64, offset: 64)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !262, file: !4, line: 1329, baseType: !265, size: 64, align: 64, offset: 128)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !262, file: !4, line: 1329, baseType: !60, size: 32, align: 32, offset: 192)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !240, file: !4, line: 1329, baseType: !81, size: 32, align: 32, offset: 1152)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !240, file: !4, line: 1329, baseType: !81, size: 32, align: 32, offset: 1184)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !77, file: !4, line: 1482, baseType: !60, size: 32, align: 32, offset: 6144)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !77, file: !4, line: 1482, baseType: !93, size: 448, align: 64, offset: 6208)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !77, file: !4, line: 1482, baseType: !38, size: 64, align: 64, offset: 6656)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !77, file: !4, line: 1482, baseType: !60, size: 32, align: 32, offset: 6720)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !71, file: !4, line: 1298, baseType: !149, size: 32, align: 32, offset: 128)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !71, file: !4, line: 1298, baseType: !151, size: 64, align: 64, offset: 192)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !71, file: !4, line: 1298, baseType: !43, size: 128, align: 64, offset: 256)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !71, file: !4, line: 1298, baseType: !279, size: 256, align: 64, offset: 384)
!279 = !DICompositeType(tag: DW_TAG_union_type, scope: !71, file: !4, line: 1298, size: 256, align: 64, elements: !280)
!280 = !{!281, !282}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !279, file: !4, line: 1298, baseType: !60, size: 32, align: 32)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !279, file: !4, line: 1298, baseType: !169, size: 256, align: 64)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !71, file: !4, line: 1298, baseType: !155, size: 64, align: 64, offset: 640)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !71, file: !4, line: 1298, baseType: !81, size: 32, align: 32, offset: 704)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !71, file: !4, line: 1300, baseType: !64, size: 64, align: 64, offset: 768)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !71, file: !4, line: 1301, baseType: !287, size: 64, align: 64, offset: 832)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_event_cb", file: !4, line: 352, baseType: !288)
!288 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !289, size: 64, align: 64)
!289 = !DISubroutineType(types: !290)
!290 = !{null, !69, !291, !60, !60}
!291 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !292, size: 64, align: 64)
!292 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !65)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !71, file: !4, line: 1301, baseType: !43, size: 128, align: 64, offset: 896)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "wd", scope: !71, file: !4, line: 1301, baseType: !60, size: 32, align: 32, offset: 1024)
!295 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !296, size: 64, align: 64)
!296 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !297)
!297 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__inotify_event", file: !298, line: 101, size: 128, align: 32, elements: !299)
!298 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-syscalls.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!299 = !{!300, !302, !304, !305}
!300 = !DIDerivedType(tag: DW_TAG_member, name: "wd", scope: !297, file: !298, line: 102, baseType: !301, size: 32, align: 32)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "int32_t", file: !233, line: 38, baseType: !60)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "mask", scope: !297, file: !298, line: 103, baseType: !303, size: 32, align: 32, offset: 32)
!303 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !233, line: 51, baseType: !81)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "cookie", scope: !297, file: !298, line: 104, baseType: !303, size: 32, align: 32, offset: 64)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !297, file: !298, line: 105, baseType: !303, size: 32, align: 32, offset: 96)
!306 = !{!307, !311, !314, !317, !320, !323, !326, !329, !332, !335, !338, !341, !344, !347, !351, !354, !355, !360, !361}
!307 = distinct !DISubprogram(name: "uv__inotify_fork", scope: !1, file: !1, line: 113, type: !308, isLocal: false, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!308 = !DISubroutineType(types: !309)
!309 = !{!60, !75, !38}
!310 = !{}
!311 = distinct !DISubprogram(name: "uv_fs_event_init", scope: !1, file: !1, line: 270, type: !312, isLocal: false, isDefinition: true, scopeLine: 270, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!312 = !DISubroutineType(types: !313)
!313 = !{!60, !75, !69}
!314 = distinct !DISubprogram(name: "uv_fs_event_start", scope: !1, file: !1, line: 276, type: !315, isLocal: false, isDefinition: true, scopeLine: 279, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!315 = !DISubroutineType(types: !316)
!316 = !{!60, !69, !287, !291, !81}
!317 = distinct !DISubprogram(name: "uv_fs_event_stop", scope: !1, file: !1, line: 330, type: !318, isLocal: false, isDefinition: true, scopeLine: 330, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!318 = !DISubroutineType(types: !319)
!319 = !{!60, !69}
!320 = distinct !DISubprogram(name: "uv__fs_event_close", scope: !1, file: !1, line: 350, type: !321, isLocal: false, isDefinition: true, scopeLine: 350, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!321 = !DISubroutineType(types: !322)
!322 = !{null, !69}
!323 = distinct !DISubprogram(name: "watcher_root_RB_MINMAX", scope: !1, file: !1, line: 57, type: !324, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!324 = !DISubroutineType(types: !325)
!325 = !{!50, !46, !60}
!326 = distinct !DISubprogram(name: "watcher_root_RB_NEXT", scope: !1, file: !1, line: 57, type: !327, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!327 = !DISubroutineType(types: !328)
!328 = !{!50, !50}
!329 = distinct !DISubprogram(name: "maybe_free_watcher_list", scope: !1, file: !1, line: 184, type: !330, isLocal: true, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!330 = !DISubroutineType(types: !331)
!331 = !{null, !50, !75}
!332 = distinct !DISubprogram(name: "watcher_root_RB_REMOVE", scope: !1, file: !1, line: 57, type: !333, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!333 = !DISubroutineType(types: !334)
!334 = !{!50, !46, !50}
!335 = distinct !DISubprogram(name: "watcher_root_RB_REMOVE_COLOR", scope: !1, file: !1, line: 57, type: !336, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!336 = !DISubroutineType(types: !337)
!337 = !{null, !46, !50, !50}
!338 = distinct !DISubprogram(name: "init_inotify", scope: !1, file: !1, line: 95, type: !339, isLocal: true, isDefinition: true, scopeLine: 95, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!339 = !DISubroutineType(types: !340)
!340 = !{!60, !75}
!341 = distinct !DISubprogram(name: "new_inotify_fd", scope: !1, file: !1, line: 67, type: !342, isLocal: true, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!342 = !DISubroutineType(types: !343)
!343 = !{!60}
!344 = distinct !DISubprogram(name: "uv__inotify_read", scope: !1, file: !1, line: 194, type: !345, isLocal: true, isDefinition: true, scopeLine: 196, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!345 = !DISubroutineType(types: !346)
!346 = !{null, !75, !92, !81}
!347 = distinct !DISubprogram(name: "uv__basename_r", scope: !348, file: !348, line: 312, type: !349, isLocal: true, isDefinition: true, scopeLine: 312, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!348 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!349 = !DISubroutineType(types: !350)
!350 = !{!64, !291}
!351 = distinct !DISubprogram(name: "find_watcher", scope: !1, file: !1, line: 178, type: !352, isLocal: true, isDefinition: true, scopeLine: 178, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!352 = !DISubroutineType(types: !353)
!353 = !{!50, !75, !60}
!354 = distinct !DISubprogram(name: "watcher_root_RB_FIND", scope: !1, file: !1, line: 57, type: !333, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!355 = distinct !DISubprogram(name: "compare_watchers", scope: !1, file: !1, line: 49, type: !356, isLocal: true, isDefinition: true, scopeLine: 50, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!356 = !DISubroutineType(types: !357)
!357 = !{!60, !358, !358}
!358 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !359, size: 64, align: 64)
!359 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !51)
!360 = distinct !DISubprogram(name: "watcher_root_RB_INSERT", scope: !1, file: !1, line: 57, type: !333, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!361 = distinct !DISubprogram(name: "watcher_root_RB_INSERT_COLOR", scope: !1, file: !1, line: 57, type: !362, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !310)
!362 = !DISubroutineType(types: !363)
!363 = !{null, !46, !50}
!364 = !{i32 2, !"Dwarf Version", i32 4}
!365 = !{i32 2, !"Debug Info Version", i32 3}
!366 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!367 = !DILocalVariable(name: "loop", arg: 1, scope: !307, file: !1, line: 113, type: !75)
!368 = !DIExpression()
!369 = !DILocation(line: 113, column: 33, scope: !307)
!370 = !DILocalVariable(name: "old_watchers", arg: 2, scope: !307, file: !1, line: 113, type: !38)
!371 = !DILocation(line: 113, column: 45, scope: !307)
!372 = !DILocalVariable(name: "err", scope: !307, file: !1, line: 115, type: !60)
!373 = !DILocation(line: 115, column: 7, scope: !307)
!374 = !DILocalVariable(name: "tmp_watcher_list_iter", scope: !307, file: !1, line: 116, type: !50)
!375 = !DILocation(line: 116, column: 24, scope: !307)
!376 = !DILocalVariable(name: "watcher_list", scope: !307, file: !1, line: 117, type: !50)
!377 = !DILocation(line: 117, column: 24, scope: !307)
!378 = !DILocalVariable(name: "tmp_watcher_list", scope: !307, file: !1, line: 118, type: !51)
!379 = !DILocation(line: 118, column: 23, scope: !307)
!380 = !DILocalVariable(name: "queue", scope: !307, file: !1, line: 119, type: !41)
!381 = !DILocation(line: 119, column: 9, scope: !307)
!382 = !DILocalVariable(name: "q", scope: !307, file: !1, line: 120, type: !40)
!383 = !DILocation(line: 120, column: 10, scope: !307)
!384 = !DILocalVariable(name: "handle", scope: !307, file: !1, line: 121, type: !69)
!385 = !DILocation(line: 121, column: 18, scope: !307)
!386 = !DILocalVariable(name: "tmp_path", scope: !307, file: !1, line: 122, type: !64)
!387 = !DILocation(line: 122, column: 9, scope: !307)
!388 = !DILocation(line: 124, column: 7, scope: !389)
!389 = distinct !DILexicalBlock(scope: !307, file: !1, line: 124, column: 7)
!390 = !DILocation(line: 124, column: 20, scope: !389)
!391 = !DILocation(line: 124, column: 7, scope: !307)
!392 = !DILocation(line: 128, column: 30, scope: !393)
!393 = distinct !DILexicalBlock(scope: !389, file: !1, line: 124, column: 29)
!394 = !DILocation(line: 128, column: 5, scope: !393)
!395 = !DILocation(line: 128, column: 11, scope: !393)
!396 = !DILocation(line: 128, column: 28, scope: !393)
!397 = !DILocation(line: 130, column: 5, scope: !393)
!398 = !DILocation(line: 130, column: 5, scope: !399)
!399 = !DILexicalBlockFile(scope: !400, file: !1, discriminator: 1)
!400 = distinct !DILexicalBlock(scope: !393, file: !1, line: 130, column: 5)
!401 = !DILocation(line: 136, column: 5, scope: !402)
!402 = distinct !DILexicalBlock(scope: !393, file: !1, line: 136, column: 5)
!403 = !DILocation(line: 136, column: 5, scope: !404)
!404 = !DILexicalBlockFile(scope: !405, file: !1, discriminator: 1)
!405 = distinct !DILexicalBlock(scope: !402, file: !1, line: 136, column: 5)
!406 = !DILocation(line: 136, column: 5, scope: !407)
!407 = !DILexicalBlockFile(scope: !405, file: !1, discriminator: 2)
!408 = !DILocation(line: 136, column: 5, scope: !409)
!409 = !DILexicalBlockFile(scope: !402, file: !1, discriminator: 3)
!410 = !DILocation(line: 138, column: 7, scope: !411)
!411 = distinct !DILexicalBlock(scope: !405, file: !1, line: 137, column: 65)
!412 = !DILocation(line: 138, column: 21, scope: !411)
!413 = !DILocation(line: 138, column: 31, scope: !411)
!414 = !DILocation(line: 139, column: 7, scope: !411)
!415 = !DILocation(line: 139, column: 7, scope: !416)
!416 = !DILexicalBlockFile(scope: !417, file: !1, discriminator: 1)
!417 = distinct !DILexicalBlock(scope: !418, file: !1, line: 139, column: 7)
!418 = distinct !DILexicalBlock(scope: !411, file: !1, line: 139, column: 7)
!419 = !DILocation(line: 139, column: 7, scope: !420)
!420 = !DILexicalBlockFile(scope: !417, file: !1, discriminator: 2)
!421 = !DILocation(line: 139, column: 7, scope: !422)
!422 = !DILexicalBlockFile(scope: !423, file: !1, discriminator: 3)
!423 = distinct !DILexicalBlock(scope: !417, file: !1, line: 139, column: 7)
!424 = !DILocation(line: 139, column: 7, scope: !425)
!425 = !DILexicalBlockFile(scope: !423, file: !1, discriminator: 4)
!426 = !DILocalVariable(name: "q", scope: !427, file: !1, line: 139, type: !40)
!427 = distinct !DILexicalBlock(scope: !417, file: !1, line: 139, column: 7)
!428 = !DILocation(line: 139, column: 7, scope: !427)
!429 = !DILocation(line: 139, column: 7, scope: !430)
!430 = !DILexicalBlockFile(scope: !427, file: !1, discriminator: 5)
!431 = !DILocation(line: 139, column: 7, scope: !432)
!432 = !DILexicalBlockFile(scope: !433, file: !1, discriminator: 6)
!433 = distinct !DILexicalBlock(scope: !427, file: !1, line: 139, column: 7)
!434 = !DILocation(line: 139, column: 7, scope: !435)
!435 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 7)
!436 = !DILocation(line: 140, column: 7, scope: !411)
!437 = !DILocation(line: 140, column: 15, scope: !438)
!438 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 1)
!439 = !DILocation(line: 140, column: 14, scope: !438)
!440 = !DILocation(line: 140, column: 7, scope: !438)
!441 = !DILocation(line: 141, column: 13, scope: !442)
!442 = distinct !DILexicalBlock(scope: !411, file: !1, line: 140, column: 36)
!443 = !DILocation(line: 141, column: 11, scope: !442)
!444 = !DILocation(line: 142, column: 18, scope: !442)
!445 = !DILocation(line: 142, column: 16, scope: !442)
!446 = !DILocation(line: 147, column: 31, scope: !442)
!447 = !DILocation(line: 147, column: 39, scope: !442)
!448 = !DILocation(line: 147, column: 20, scope: !442)
!449 = !DILocation(line: 147, column: 18, scope: !442)
!450 = !DILocation(line: 148, column: 9, scope: !442)
!451 = !DILocation(line: 148, column: 9, scope: !452)
!452 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 1)
!453 = !DILocation(line: 148, column: 9, scope: !454)
!454 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 2)
!455 = !DILocation(line: 148, column: 9, scope: !456)
!456 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 3)
!457 = !DILocation(line: 149, column: 9, scope: !442)
!458 = !DILocation(line: 149, column: 9, scope: !459)
!459 = !DILexicalBlockFile(scope: !460, file: !1, discriminator: 1)
!460 = distinct !DILexicalBlock(scope: !442, file: !1, line: 149, column: 9)
!461 = !DILocation(line: 150, column: 9, scope: !442)
!462 = !DILocation(line: 150, column: 9, scope: !463)
!463 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 1)
!464 = distinct !DILexicalBlock(scope: !442, file: !1, line: 150, column: 9)
!465 = !DILocation(line: 151, column: 26, scope: !442)
!466 = !DILocation(line: 151, column: 9, scope: !442)
!467 = !DILocation(line: 153, column: 9, scope: !442)
!468 = !DILocation(line: 153, column: 9, scope: !469)
!469 = !DILexicalBlockFile(scope: !470, file: !1, discriminator: 1)
!470 = distinct !DILexicalBlock(scope: !442, file: !1, line: 153, column: 9)
!471 = !DILocation(line: 154, column: 24, scope: !442)
!472 = !DILocation(line: 154, column: 9, scope: !442)
!473 = !DILocation(line: 154, column: 17, scope: !442)
!474 = !DILocation(line: 154, column: 22, scope: !442)
!475 = !DILocation(line: 140, column: 7, scope: !476)
!476 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 2)
!477 = !DILocation(line: 156, column: 7, scope: !411)
!478 = !DILocation(line: 156, column: 21, scope: !411)
!479 = !DILocation(line: 156, column: 31, scope: !411)
!480 = !DILocation(line: 157, column: 31, scope: !411)
!481 = !DILocation(line: 157, column: 45, scope: !411)
!482 = !DILocation(line: 157, column: 7, scope: !411)
!483 = !DILocation(line: 158, column: 5, scope: !411)
!484 = !DILocation(line: 136, column: 5, scope: !485)
!485 = !DILexicalBlockFile(scope: !405, file: !1, discriminator: 4)
!486 = !DILocation(line: 160, column: 5, scope: !393)
!487 = !DILocation(line: 160, column: 5, scope: !488)
!488 = !DILexicalBlockFile(scope: !489, file: !1, discriminator: 1)
!489 = distinct !DILexicalBlock(scope: !490, file: !1, line: 160, column: 5)
!490 = distinct !DILexicalBlock(scope: !393, file: !1, line: 160, column: 5)
!491 = !DILocation(line: 160, column: 5, scope: !492)
!492 = !DILexicalBlockFile(scope: !489, file: !1, discriminator: 2)
!493 = !DILocation(line: 160, column: 5, scope: !494)
!494 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 3)
!495 = distinct !DILexicalBlock(scope: !489, file: !1, line: 160, column: 5)
!496 = !DILocation(line: 160, column: 5, scope: !497)
!497 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 4)
!498 = !DILocalVariable(name: "q", scope: !499, file: !1, line: 160, type: !40)
!499 = distinct !DILexicalBlock(scope: !489, file: !1, line: 160, column: 5)
!500 = !DILocation(line: 160, column: 5, scope: !499)
!501 = !DILocation(line: 160, column: 5, scope: !502)
!502 = !DILexicalBlockFile(scope: !499, file: !1, discriminator: 5)
!503 = !DILocation(line: 160, column: 5, scope: !504)
!504 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 6)
!505 = distinct !DILexicalBlock(scope: !499, file: !1, line: 160, column: 5)
!506 = !DILocation(line: 160, column: 5, scope: !507)
!507 = !DILexicalBlockFile(scope: !490, file: !1, discriminator: 7)
!508 = !DILocation(line: 161, column: 5, scope: !393)
!509 = !DILocation(line: 161, column: 13, scope: !510)
!510 = !DILexicalBlockFile(scope: !393, file: !1, discriminator: 1)
!511 = !DILocation(line: 161, column: 12, scope: !510)
!512 = !DILocation(line: 161, column: 5, scope: !510)
!513 = !DILocation(line: 162, column: 13, scope: !514)
!514 = distinct !DILexicalBlock(scope: !393, file: !1, line: 161, column: 34)
!515 = !DILocation(line: 162, column: 11, scope: !514)
!516 = !DILocation(line: 163, column: 9, scope: !514)
!517 = !DILocation(line: 163, column: 9, scope: !518)
!518 = !DILexicalBlockFile(scope: !519, file: !1, discriminator: 1)
!519 = distinct !DILexicalBlock(scope: !514, file: !1, line: 163, column: 9)
!520 = !DILocation(line: 164, column: 18, scope: !514)
!521 = !DILocation(line: 164, column: 16, scope: !514)
!522 = !DILocation(line: 165, column: 20, scope: !514)
!523 = !DILocation(line: 165, column: 28, scope: !514)
!524 = !DILocation(line: 165, column: 18, scope: !514)
!525 = !DILocation(line: 166, column: 9, scope: !514)
!526 = !DILocation(line: 166, column: 17, scope: !514)
!527 = !DILocation(line: 166, column: 22, scope: !514)
!528 = !DILocation(line: 167, column: 33, scope: !514)
!529 = !DILocation(line: 167, column: 41, scope: !514)
!530 = !DILocation(line: 167, column: 49, scope: !514)
!531 = !DILocation(line: 167, column: 53, scope: !514)
!532 = !DILocation(line: 167, column: 15, scope: !514)
!533 = !DILocation(line: 167, column: 13, scope: !514)
!534 = !DILocation(line: 168, column: 18, scope: !514)
!535 = !DILocation(line: 168, column: 9, scope: !514)
!536 = !DILocation(line: 169, column: 13, scope: !537)
!537 = distinct !DILexicalBlock(scope: !514, file: !1, line: 169, column: 13)
!538 = !DILocation(line: 169, column: 13, scope: !514)
!539 = !DILocation(line: 170, column: 18, scope: !537)
!540 = !DILocation(line: 170, column: 11, scope: !537)
!541 = !DILocation(line: 161, column: 5, scope: !542)
!542 = !DILexicalBlockFile(scope: !393, file: !1, discriminator: 2)
!543 = !DILocation(line: 172, column: 3, scope: !393)
!544 = !DILocation(line: 174, column: 3, scope: !307)
!545 = !DILocation(line: 175, column: 1, scope: !307)
!546 = !DILocalVariable(name: "head", arg: 1, scope: !323, file: !1, line: 57, type: !46)
!547 = !DILocation(line: 57, column: 1, scope: !323)
!548 = !DILocalVariable(name: "val", arg: 2, scope: !323, file: !1, line: 57, type: !60)
!549 = !DILocalVariable(name: "tmp", scope: !323, file: !1, line: 57, type: !50)
!550 = !DILocalVariable(name: "parent", scope: !323, file: !1, line: 57, type: !50)
!551 = !DILocation(line: 57, column: 1, scope: !552)
!552 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 1)
!553 = !DILocation(line: 57, column: 1, scope: !554)
!554 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 2)
!555 = distinct !DILexicalBlock(scope: !323, file: !1, line: 57, column: 1)
!556 = !DILocation(line: 57, column: 1, scope: !557)
!557 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 3)
!558 = distinct !DILexicalBlock(scope: !555, file: !1, line: 57, column: 1)
!559 = !DILocation(line: 57, column: 1, scope: !560)
!560 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 4)
!561 = !DILocation(line: 57, column: 1, scope: !562)
!562 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 5)
!563 = !DILocation(line: 57, column: 1, scope: !564)
!564 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 6)
!565 = !DILocalVariable(name: "elm", arg: 1, scope: !326, file: !1, line: 57, type: !50)
!566 = !DILocation(line: 57, column: 1, scope: !326)
!567 = !DILocation(line: 57, column: 1, scope: !568)
!568 = distinct !DILexicalBlock(scope: !326, file: !1, line: 57, column: 1)
!569 = !DILocation(line: 57, column: 1, scope: !570)
!570 = !DILexicalBlockFile(scope: !571, file: !1, discriminator: 7)
!571 = distinct !DILexicalBlock(scope: !568, file: !1, line: 57, column: 1)
!572 = !DILocation(line: 57, column: 1, scope: !573)
!573 = !DILexicalBlockFile(scope: !571, file: !1, discriminator: 8)
!574 = !DILocation(line: 57, column: 1, scope: !575)
!575 = !DILexicalBlockFile(scope: !571, file: !1, discriminator: 9)
!576 = !DILocation(line: 57, column: 1, scope: !577)
!577 = !DILexicalBlockFile(scope: !571, file: !1, discriminator: 10)
!578 = !DILocation(line: 57, column: 1, scope: !579)
!579 = !DILexicalBlockFile(scope: !580, file: !1, discriminator: 11)
!580 = distinct !DILexicalBlock(scope: !581, file: !1, line: 57, column: 1)
!581 = distinct !DILexicalBlock(scope: !568, file: !1, line: 57, column: 1)
!582 = !DILocation(line: 57, column: 1, scope: !583)
!583 = !DILexicalBlockFile(scope: !580, file: !1, discriminator: 12)
!584 = !DILocation(line: 57, column: 1, scope: !585)
!585 = !DILexicalBlockFile(scope: !580, file: !1, discriminator: 13)
!586 = !DILocation(line: 57, column: 1, scope: !587)
!587 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 14)
!588 = distinct !DILexicalBlock(scope: !580, file: !1, line: 57, column: 1)
!589 = !DILocation(line: 57, column: 1, scope: !590)
!590 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 15)
!591 = !DILocation(line: 57, column: 1, scope: !592)
!592 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 16)
!593 = !DILocation(line: 57, column: 1, scope: !594)
!594 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 17)
!595 = !DILocation(line: 57, column: 1, scope: !596)
!596 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 18)
!597 = !DILocation(line: 57, column: 1, scope: !598)
!598 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 19)
!599 = !DILocation(line: 57, column: 1, scope: !600)
!600 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 20)
!601 = !DILocalVariable(name: "handle", arg: 1, scope: !317, file: !1, line: 330, type: !69)
!602 = !DILocation(line: 330, column: 37, scope: !317)
!603 = !DILocalVariable(name: "w", scope: !317, file: !1, line: 331, type: !50)
!604 = !DILocation(line: 331, column: 24, scope: !317)
!605 = !DILocation(line: 333, column: 8, scope: !606)
!606 = distinct !DILexicalBlock(scope: !317, file: !1, line: 333, column: 7)
!607 = !DILocation(line: 333, column: 7, scope: !317)
!608 = !DILocation(line: 334, column: 5, scope: !606)
!609 = !DILocation(line: 336, column: 20, scope: !317)
!610 = !DILocation(line: 336, column: 28, scope: !317)
!611 = !DILocation(line: 336, column: 34, scope: !317)
!612 = !DILocation(line: 336, column: 42, scope: !317)
!613 = !DILocation(line: 336, column: 7, scope: !317)
!614 = !DILocation(line: 336, column: 5, scope: !317)
!615 = !DILocation(line: 337, column: 3, scope: !317)
!616 = !DILocation(line: 337, column: 3, scope: !617)
!617 = !DILexicalBlockFile(scope: !317, file: !1, discriminator: 1)
!618 = !DILocation(line: 337, column: 3, scope: !619)
!619 = !DILexicalBlockFile(scope: !317, file: !1, discriminator: 2)
!620 = !DILocation(line: 337, column: 3, scope: !621)
!621 = !DILexicalBlockFile(scope: !317, file: !1, discriminator: 3)
!622 = !DILocation(line: 339, column: 3, scope: !317)
!623 = !DILocation(line: 339, column: 11, scope: !317)
!624 = !DILocation(line: 339, column: 14, scope: !317)
!625 = !DILocation(line: 340, column: 3, scope: !317)
!626 = !DILocation(line: 340, column: 11, scope: !317)
!627 = !DILocation(line: 340, column: 16, scope: !317)
!628 = !DILocation(line: 341, column: 3, scope: !317)
!629 = !DILocation(line: 341, column: 3, scope: !630)
!630 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 1)
!631 = distinct !DILexicalBlock(scope: !317, file: !1, line: 341, column: 3)
!632 = !DILocation(line: 341, column: 3, scope: !633)
!633 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 2)
!634 = !DILocation(line: 341, column: 3, scope: !635)
!635 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 3)
!636 = !DILocation(line: 341, column: 3, scope: !637)
!637 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 4)
!638 = !DILocation(line: 341, column: 3, scope: !639)
!639 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 5)
!640 = distinct !DILexicalBlock(scope: !631, file: !1, line: 341, column: 3)
!641 = !DILocation(line: 341, column: 3, scope: !642)
!642 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 6)
!643 = !DILocation(line: 341, column: 3, scope: !644)
!644 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 7)
!645 = !DILocation(line: 341, column: 3, scope: !646)
!646 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 8)
!647 = distinct !DILexicalBlock(scope: !631, file: !1, line: 341, column: 3)
!648 = !DILocation(line: 341, column: 3, scope: !649)
!649 = !DILexicalBlockFile(scope: !650, file: !1, discriminator: 9)
!650 = distinct !DILexicalBlock(scope: !647, file: !1, line: 341, column: 3)
!651 = !DILocation(line: 341, column: 3, scope: !652)
!652 = !DILexicalBlockFile(scope: !650, file: !1, discriminator: 10)
!653 = !DILocation(line: 341, column: 3, scope: !654)
!654 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 11)
!655 = !DILocation(line: 342, column: 3, scope: !317)
!656 = !DILocation(line: 342, column: 3, scope: !657)
!657 = !DILexicalBlockFile(scope: !658, file: !1, discriminator: 1)
!658 = distinct !DILexicalBlock(scope: !317, file: !1, line: 342, column: 3)
!659 = !DILocation(line: 344, column: 27, scope: !317)
!660 = !DILocation(line: 344, column: 30, scope: !317)
!661 = !DILocation(line: 344, column: 38, scope: !317)
!662 = !DILocation(line: 344, column: 3, scope: !317)
!663 = !DILocation(line: 346, column: 3, scope: !317)
!664 = !DILocation(line: 347, column: 1, scope: !317)
!665 = !DILocalVariable(name: "w", arg: 1, scope: !329, file: !1, line: 184, type: !50)
!666 = !DILocation(line: 184, column: 58, scope: !329)
!667 = !DILocalVariable(name: "loop", arg: 2, scope: !329, file: !1, line: 184, type: !75)
!668 = !DILocation(line: 184, column: 72, scope: !329)
!669 = !DILocation(line: 186, column: 9, scope: !670)
!670 = distinct !DILexicalBlock(scope: !329, file: !1, line: 186, column: 7)
!671 = !DILocation(line: 186, column: 12, scope: !670)
!672 = !DILocation(line: 186, column: 23, scope: !670)
!673 = !DILocation(line: 186, column: 26, scope: !674)
!674 = !DILexicalBlockFile(scope: !670, file: !1, discriminator: 1)
!675 = !DILocation(line: 186, column: 7, scope: !674)
!676 = !DILocation(line: 188, column: 5, scope: !677)
!677 = distinct !DILexicalBlock(scope: !670, file: !1, line: 186, column: 53)
!678 = !DILocation(line: 189, column: 26, scope: !677)
!679 = !DILocation(line: 189, column: 32, scope: !677)
!680 = !DILocation(line: 189, column: 44, scope: !677)
!681 = !DILocation(line: 189, column: 47, scope: !677)
!682 = !DILocation(line: 189, column: 5, scope: !677)
!683 = !DILocation(line: 190, column: 14, scope: !677)
!684 = !DILocation(line: 190, column: 5, scope: !677)
!685 = !DILocation(line: 191, column: 3, scope: !677)
!686 = !DILocation(line: 192, column: 1, scope: !329)
!687 = !DILocalVariable(name: "handle", arg: 1, scope: !314, file: !1, line: 276, type: !69)
!688 = !DILocation(line: 276, column: 38, scope: !314)
!689 = !DILocalVariable(name: "cb", arg: 2, scope: !314, file: !1, line: 277, type: !287)
!690 = !DILocation(line: 277, column: 38, scope: !314)
!691 = !DILocalVariable(name: "path", arg: 3, scope: !314, file: !1, line: 278, type: !291)
!692 = !DILocation(line: 278, column: 35, scope: !314)
!693 = !DILocalVariable(name: "flags", arg: 4, scope: !314, file: !1, line: 279, type: !81)
!694 = !DILocation(line: 279, column: 36, scope: !314)
!695 = !DILocalVariable(name: "w", scope: !314, file: !1, line: 280, type: !50)
!696 = !DILocation(line: 280, column: 24, scope: !314)
!697 = !DILocalVariable(name: "events", scope: !314, file: !1, line: 281, type: !60)
!698 = !DILocation(line: 281, column: 7, scope: !314)
!699 = !DILocalVariable(name: "err", scope: !314, file: !1, line: 282, type: !60)
!700 = !DILocation(line: 282, column: 7, scope: !314)
!701 = !DILocalVariable(name: "wd", scope: !314, file: !1, line: 283, type: !60)
!702 = !DILocation(line: 283, column: 7, scope: !314)
!703 = !DILocation(line: 285, column: 7, scope: !704)
!704 = distinct !DILexicalBlock(scope: !314, file: !1, line: 285, column: 7)
!705 = !DILocation(line: 285, column: 7, scope: !314)
!706 = !DILocation(line: 286, column: 5, scope: !704)
!707 = !DILocation(line: 288, column: 22, scope: !314)
!708 = !DILocation(line: 288, column: 30, scope: !314)
!709 = !DILocation(line: 288, column: 9, scope: !314)
!710 = !DILocation(line: 288, column: 7, scope: !314)
!711 = !DILocation(line: 289, column: 7, scope: !712)
!712 = distinct !DILexicalBlock(scope: !314, file: !1, line: 289, column: 7)
!713 = !DILocation(line: 289, column: 7, scope: !314)
!714 = !DILocation(line: 290, column: 12, scope: !712)
!715 = !DILocation(line: 290, column: 5, scope: !712)
!716 = !DILocation(line: 292, column: 10, scope: !314)
!717 = !DILocation(line: 301, column: 30, scope: !314)
!718 = !DILocation(line: 301, column: 38, scope: !314)
!719 = !DILocation(line: 301, column: 44, scope: !314)
!720 = !DILocation(line: 301, column: 56, scope: !314)
!721 = !DILocation(line: 301, column: 62, scope: !314)
!722 = !DILocation(line: 301, column: 8, scope: !314)
!723 = !DILocation(line: 301, column: 6, scope: !314)
!724 = !DILocation(line: 302, column: 7, scope: !725)
!725 = distinct !DILexicalBlock(scope: !314, file: !1, line: 302, column: 7)
!726 = !DILocation(line: 302, column: 10, scope: !725)
!727 = !DILocation(line: 302, column: 7, scope: !314)
!728 = !DILocation(line: 303, column: 13, scope: !725)
!729 = !DILocation(line: 303, column: 12, scope: !725)
!730 = !DILocation(line: 303, column: 5, scope: !725)
!731 = !DILocation(line: 305, column: 20, scope: !314)
!732 = !DILocation(line: 305, column: 28, scope: !314)
!733 = !DILocation(line: 305, column: 34, scope: !314)
!734 = !DILocation(line: 305, column: 7, scope: !314)
!735 = !DILocation(line: 305, column: 5, scope: !314)
!736 = !DILocation(line: 306, column: 7, scope: !737)
!737 = distinct !DILexicalBlock(scope: !314, file: !1, line: 306, column: 7)
!738 = !DILocation(line: 306, column: 7, scope: !314)
!739 = !DILocation(line: 307, column: 5, scope: !737)
!740 = !DILocation(line: 309, column: 38, scope: !314)
!741 = !DILocation(line: 309, column: 31, scope: !314)
!742 = !DILocation(line: 309, column: 29, scope: !314)
!743 = !DILocation(line: 309, column: 44, scope: !314)
!744 = !DILocation(line: 309, column: 7, scope: !745)
!745 = !DILexicalBlockFile(scope: !314, file: !1, discriminator: 1)
!746 = !DILocation(line: 309, column: 7, scope: !314)
!747 = !DILocation(line: 309, column: 5, scope: !314)
!748 = !DILocation(line: 310, column: 7, scope: !749)
!749 = distinct !DILexicalBlock(scope: !314, file: !1, line: 310, column: 7)
!750 = !DILocation(line: 310, column: 9, scope: !749)
!751 = !DILocation(line: 310, column: 7, scope: !314)
!752 = !DILocation(line: 311, column: 5, scope: !749)
!753 = !DILocation(line: 313, column: 11, scope: !314)
!754 = !DILocation(line: 313, column: 3, scope: !314)
!755 = !DILocation(line: 313, column: 6, scope: !314)
!756 = !DILocation(line: 313, column: 9, scope: !314)
!757 = !DILocation(line: 314, column: 28, scope: !314)
!758 = !DILocation(line: 314, column: 30, scope: !314)
!759 = !DILocation(line: 314, column: 20, scope: !314)
!760 = !DILocation(line: 314, column: 36, scope: !314)
!761 = !DILocation(line: 314, column: 13, scope: !314)
!762 = !DILocation(line: 314, column: 3, scope: !314)
!763 = !DILocation(line: 314, column: 6, scope: !314)
!764 = !DILocation(line: 314, column: 11, scope: !314)
!765 = !DILocation(line: 315, column: 3, scope: !314)
!766 = !DILocation(line: 315, column: 3, scope: !767)
!767 = !DILexicalBlockFile(scope: !768, file: !1, discriminator: 1)
!768 = distinct !DILexicalBlock(scope: !314, file: !1, line: 315, column: 3)
!769 = !DILocation(line: 316, column: 3, scope: !314)
!770 = !DILocation(line: 316, column: 6, scope: !314)
!771 = !DILocation(line: 316, column: 16, scope: !314)
!772 = !DILocation(line: 317, column: 3, scope: !314)
!773 = !DILocation(line: 320, column: 3, scope: !314)
!774 = !DILocation(line: 320, column: 3, scope: !775)
!775 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 1)
!776 = distinct !DILexicalBlock(scope: !314, file: !1, line: 320, column: 3)
!777 = !DILocation(line: 320, column: 3, scope: !778)
!778 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 2)
!779 = !DILocation(line: 320, column: 3, scope: !780)
!780 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 3)
!781 = !DILocation(line: 320, column: 3, scope: !782)
!782 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 4)
!783 = !DILocation(line: 320, column: 3, scope: !784)
!784 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 5)
!785 = distinct !DILexicalBlock(scope: !776, file: !1, line: 320, column: 3)
!786 = !DILocation(line: 320, column: 3, scope: !787)
!787 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 6)
!788 = !DILocation(line: 320, column: 3, scope: !789)
!789 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 7)
!790 = !DILocation(line: 320, column: 3, scope: !791)
!791 = !DILexicalBlockFile(scope: !792, file: !1, discriminator: 8)
!792 = distinct !DILexicalBlock(scope: !776, file: !1, line: 320, column: 3)
!793 = !DILocation(line: 320, column: 3, scope: !794)
!794 = !DILexicalBlockFile(scope: !795, file: !1, discriminator: 9)
!795 = distinct !DILexicalBlock(scope: !792, file: !1, line: 320, column: 3)
!796 = !DILocation(line: 320, column: 3, scope: !797)
!797 = !DILexicalBlockFile(scope: !795, file: !1, discriminator: 10)
!798 = !DILocation(line: 320, column: 3, scope: !799)
!799 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 11)
!800 = !DILocation(line: 321, column: 3, scope: !314)
!801 = !DILocation(line: 321, column: 3, scope: !802)
!802 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 1)
!803 = distinct !DILexicalBlock(scope: !314, file: !1, line: 321, column: 3)
!804 = !DILocation(line: 322, column: 18, scope: !314)
!805 = !DILocation(line: 322, column: 21, scope: !314)
!806 = !DILocation(line: 322, column: 3, scope: !314)
!807 = !DILocation(line: 322, column: 11, scope: !314)
!808 = !DILocation(line: 322, column: 16, scope: !314)
!809 = !DILocation(line: 323, column: 16, scope: !314)
!810 = !DILocation(line: 323, column: 3, scope: !314)
!811 = !DILocation(line: 323, column: 11, scope: !314)
!812 = !DILocation(line: 323, column: 14, scope: !314)
!813 = !DILocation(line: 324, column: 16, scope: !314)
!814 = !DILocation(line: 324, column: 3, scope: !314)
!815 = !DILocation(line: 324, column: 11, scope: !314)
!816 = !DILocation(line: 324, column: 14, scope: !314)
!817 = !DILocation(line: 326, column: 3, scope: !314)
!818 = !DILocation(line: 327, column: 1, scope: !314)
!819 = !DILocalVariable(name: "loop", arg: 1, scope: !311, file: !1, line: 270, type: !75)
!820 = !DILocation(line: 270, column: 33, scope: !311)
!821 = !DILocalVariable(name: "handle", arg: 2, scope: !311, file: !1, line: 270, type: !69)
!822 = !DILocation(line: 270, column: 54, scope: !311)
!823 = !DILocation(line: 271, column: 3, scope: !311)
!824 = !DILocation(line: 271, column: 3, scope: !825)
!825 = !DILexicalBlockFile(scope: !826, file: !1, discriminator: 1)
!826 = distinct !DILexicalBlock(scope: !311, file: !1, line: 271, column: 3)
!827 = !DILocation(line: 271, column: 3, scope: !828)
!828 = !DILexicalBlockFile(scope: !829, file: !1, discriminator: 2)
!829 = distinct !DILexicalBlock(scope: !826, file: !1, line: 271, column: 3)
!830 = !DILocation(line: 271, column: 3, scope: !831)
!831 = !DILexicalBlockFile(scope: !826, file: !1, discriminator: 3)
!832 = !DILocation(line: 272, column: 3, scope: !311)
!833 = !DILocalVariable(name: "loop", arg: 1, scope: !338, file: !1, line: 95, type: !75)
!834 = !DILocation(line: 95, column: 36, scope: !338)
!835 = !DILocalVariable(name: "err", scope: !338, file: !1, line: 96, type: !60)
!836 = !DILocation(line: 96, column: 7, scope: !338)
!837 = !DILocation(line: 98, column: 7, scope: !838)
!838 = distinct !DILexicalBlock(scope: !338, file: !1, line: 98, column: 7)
!839 = !DILocation(line: 98, column: 13, scope: !838)
!840 = !DILocation(line: 98, column: 24, scope: !838)
!841 = !DILocation(line: 98, column: 7, scope: !338)
!842 = !DILocation(line: 99, column: 5, scope: !838)
!843 = !DILocation(line: 101, column: 9, scope: !338)
!844 = !DILocation(line: 101, column: 7, scope: !338)
!845 = !DILocation(line: 102, column: 7, scope: !846)
!846 = distinct !DILexicalBlock(scope: !338, file: !1, line: 102, column: 7)
!847 = !DILocation(line: 102, column: 11, scope: !846)
!848 = !DILocation(line: 102, column: 7, scope: !338)
!849 = !DILocation(line: 103, column: 12, scope: !846)
!850 = !DILocation(line: 103, column: 5, scope: !846)
!851 = !DILocation(line: 105, column: 22, scope: !338)
!852 = !DILocation(line: 105, column: 3, scope: !338)
!853 = !DILocation(line: 105, column: 9, scope: !338)
!854 = !DILocation(line: 105, column: 20, scope: !338)
!855 = !DILocation(line: 106, column: 16, scope: !338)
!856 = !DILocation(line: 106, column: 22, scope: !338)
!857 = !DILocation(line: 106, column: 62, scope: !338)
!858 = !DILocation(line: 106, column: 68, scope: !338)
!859 = !DILocation(line: 106, column: 3, scope: !338)
!860 = !DILocation(line: 107, column: 16, scope: !338)
!861 = !DILocation(line: 107, column: 23, scope: !338)
!862 = !DILocation(line: 107, column: 29, scope: !338)
!863 = !DILocation(line: 107, column: 3, scope: !338)
!864 = !DILocation(line: 109, column: 3, scope: !338)
!865 = !DILocation(line: 110, column: 1, scope: !338)
!866 = !DILocalVariable(name: "loop", arg: 1, scope: !351, file: !1, line: 178, type: !75)
!867 = !DILocation(line: 178, column: 53, scope: !351)
!868 = !DILocalVariable(name: "wd", arg: 2, scope: !351, file: !1, line: 178, type: !60)
!869 = !DILocation(line: 178, column: 63, scope: !351)
!870 = !DILocalVariable(name: "w", scope: !351, file: !1, line: 179, type: !51)
!871 = !DILocation(line: 179, column: 23, scope: !351)
!872 = !DILocation(line: 180, column: 10, scope: !351)
!873 = !DILocation(line: 180, column: 5, scope: !351)
!874 = !DILocation(line: 180, column: 8, scope: !351)
!875 = !DILocation(line: 181, column: 10, scope: !351)
!876 = !DILocation(line: 181, column: 3, scope: !351)
!877 = !DILocalVariable(name: "head", arg: 1, scope: !360, file: !1, line: 57, type: !46)
!878 = !DILocation(line: 57, column: 1, scope: !360)
!879 = !DILocalVariable(name: "elm", arg: 2, scope: !360, file: !1, line: 57, type: !50)
!880 = !DILocalVariable(name: "tmp", scope: !360, file: !1, line: 57, type: !50)
!881 = !DILocalVariable(name: "parent", scope: !360, file: !1, line: 57, type: !50)
!882 = !DILocalVariable(name: "comp", scope: !360, file: !1, line: 57, type: !60)
!883 = !DILocation(line: 57, column: 1, scope: !884)
!884 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 21)
!885 = !DILocation(line: 57, column: 1, scope: !886)
!886 = !DILexicalBlockFile(scope: !887, file: !1, discriminator: 22)
!887 = distinct !DILexicalBlock(scope: !360, file: !1, line: 57, column: 1)
!888 = !DILocation(line: 57, column: 1, scope: !889)
!889 = !DILexicalBlockFile(scope: !890, file: !1, discriminator: 23)
!890 = distinct !DILexicalBlock(scope: !887, file: !1, line: 57, column: 1)
!891 = !DILocation(line: 57, column: 1, scope: !892)
!892 = !DILexicalBlockFile(scope: !893, file: !1, discriminator: 24)
!893 = distinct !DILexicalBlock(scope: !890, file: !1, line: 57, column: 1)
!894 = !DILocation(line: 57, column: 1, scope: !895)
!895 = !DILexicalBlockFile(scope: !893, file: !1, discriminator: 25)
!896 = !DILocation(line: 57, column: 1, scope: !897)
!897 = !DILexicalBlockFile(scope: !893, file: !1, discriminator: 26)
!898 = !DILocation(line: 57, column: 1, scope: !899)
!899 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 27)
!900 = !DILocation(line: 57, column: 1, scope: !901)
!901 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 28)
!902 = !DILocation(line: 57, column: 1, scope: !903)
!903 = !DILexicalBlockFile(scope: !904, file: !1, discriminator: 29)
!904 = distinct !DILexicalBlock(scope: !360, file: !1, line: 57, column: 1)
!905 = !DILocation(line: 57, column: 1, scope: !906)
!906 = !DILexicalBlockFile(scope: !907, file: !1, discriminator: 30)
!907 = distinct !DILexicalBlock(scope: !360, file: !1, line: 57, column: 1)
!908 = !DILocation(line: 57, column: 1, scope: !909)
!909 = !DILexicalBlockFile(scope: !910, file: !1, discriminator: 31)
!910 = distinct !DILexicalBlock(scope: !911, file: !1, line: 57, column: 1)
!911 = distinct !DILexicalBlock(scope: !907, file: !1, line: 57, column: 1)
!912 = !DILocation(line: 57, column: 1, scope: !913)
!913 = !DILexicalBlockFile(scope: !910, file: !1, discriminator: 32)
!914 = !DILocation(line: 57, column: 1, scope: !915)
!915 = !DILexicalBlockFile(scope: !910, file: !1, discriminator: 33)
!916 = !DILocation(line: 57, column: 1, scope: !917)
!917 = !DILexicalBlockFile(scope: !911, file: !1, discriminator: 34)
!918 = !DILocation(line: 57, column: 1, scope: !919)
!919 = !DILexicalBlockFile(scope: !920, file: !1, discriminator: 35)
!920 = distinct !DILexicalBlock(scope: !911, file: !1, line: 57, column: 1)
!921 = !DILocation(line: 57, column: 1, scope: !922)
!922 = !DILexicalBlockFile(scope: !911, file: !1, discriminator: 36)
!923 = !DILocation(line: 57, column: 1, scope: !924)
!924 = !DILexicalBlockFile(scope: !907, file: !1, discriminator: 37)
!925 = !DILocation(line: 57, column: 1, scope: !926)
!926 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 38)
!927 = !DILocation(line: 57, column: 1, scope: !928)
!928 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 39)
!929 = !DILocalVariable(name: "handle", arg: 1, scope: !320, file: !1, line: 350, type: !69)
!930 = !DILocation(line: 350, column: 40, scope: !320)
!931 = !DILocation(line: 351, column: 20, scope: !320)
!932 = !DILocation(line: 351, column: 3, scope: !320)
!933 = !DILocation(line: 352, column: 1, scope: !320)
!934 = !DILocalVariable(name: "head", arg: 1, scope: !332, file: !1, line: 57, type: !46)
!935 = !DILocation(line: 57, column: 1, scope: !332)
!936 = !DILocalVariable(name: "elm", arg: 2, scope: !332, file: !1, line: 57, type: !50)
!937 = !DILocalVariable(name: "child", scope: !332, file: !1, line: 57, type: !50)
!938 = !DILocalVariable(name: "parent", scope: !332, file: !1, line: 57, type: !50)
!939 = !DILocalVariable(name: "old", scope: !332, file: !1, line: 57, type: !50)
!940 = !DILocalVariable(name: "color", scope: !332, file: !1, line: 57, type: !60)
!941 = !DILocation(line: 57, column: 1, scope: !942)
!942 = distinct !DILexicalBlock(scope: !332, file: !1, line: 57, column: 1)
!943 = !DILocation(line: 57, column: 1, scope: !944)
!944 = !DILexicalBlockFile(scope: !942, file: !1, discriminator: 40)
!945 = !DILocation(line: 57, column: 1, scope: !946)
!946 = !DILexicalBlockFile(scope: !947, file: !1, discriminator: 41)
!947 = distinct !DILexicalBlock(scope: !942, file: !1, line: 57, column: 1)
!948 = !DILocation(line: 57, column: 1, scope: !949)
!949 = !DILexicalBlockFile(scope: !947, file: !1, discriminator: 42)
!950 = !DILocalVariable(name: "left", scope: !951, file: !1, line: 57, type: !50)
!951 = distinct !DILexicalBlock(scope: !947, file: !1, line: 57, column: 1)
!952 = !DILocation(line: 57, column: 1, scope: !951)
!953 = !DILocation(line: 57, column: 1, scope: !954)
!954 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 43)
!955 = !DILocation(line: 57, column: 1, scope: !956)
!956 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 44)
!957 = !DILocation(line: 57, column: 1, scope: !958)
!958 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 45)
!959 = !DILocation(line: 57, column: 1, scope: !960)
!960 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 46)
!961 = !DILocation(line: 57, column: 1, scope: !962)
!962 = !DILexicalBlockFile(scope: !963, file: !1, discriminator: 47)
!963 = distinct !DILexicalBlock(scope: !951, file: !1, line: 57, column: 1)
!964 = !DILocation(line: 57, column: 1, scope: !965)
!965 = !DILexicalBlockFile(scope: !966, file: !1, discriminator: 48)
!966 = distinct !DILexicalBlock(scope: !951, file: !1, line: 57, column: 1)
!967 = !DILocation(line: 57, column: 1, scope: !968)
!968 = !DILexicalBlockFile(scope: !969, file: !1, discriminator: 49)
!969 = distinct !DILexicalBlock(scope: !970, file: !1, line: 57, column: 1)
!970 = distinct !DILexicalBlock(scope: !966, file: !1, line: 57, column: 1)
!971 = !DILocation(line: 57, column: 1, scope: !972)
!972 = !DILexicalBlockFile(scope: !969, file: !1, discriminator: 50)
!973 = !DILocation(line: 57, column: 1, scope: !974)
!974 = !DILexicalBlockFile(scope: !969, file: !1, discriminator: 51)
!975 = !DILocation(line: 57, column: 1, scope: !976)
!976 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 52)
!977 = !DILocation(line: 57, column: 1, scope: !978)
!978 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 53)
!979 = distinct !DILexicalBlock(scope: !970, file: !1, line: 57, column: 1)
!980 = !DILocation(line: 57, column: 1, scope: !981)
!981 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 54)
!982 = !DILocation(line: 57, column: 1, scope: !983)
!983 = !DILexicalBlockFile(scope: !966, file: !1, discriminator: 55)
!984 = !DILocation(line: 57, column: 1, scope: !985)
!985 = !DILexicalBlockFile(scope: !986, file: !1, discriminator: 56)
!986 = distinct !DILexicalBlock(scope: !951, file: !1, line: 57, column: 1)
!987 = !DILocation(line: 57, column: 1, scope: !988)
!988 = !DILexicalBlockFile(scope: !986, file: !1, discriminator: 57)
!989 = !DILocation(line: 57, column: 1, scope: !990)
!990 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 58)
!991 = !DILocation(line: 57, column: 1, scope: !992)
!992 = !DILexicalBlockFile(scope: !993, file: !1, discriminator: 59)
!993 = distinct !DILexicalBlock(scope: !994, file: !1, line: 57, column: 1)
!994 = distinct !DILexicalBlock(scope: !995, file: !1, line: 57, column: 1)
!995 = distinct !DILexicalBlock(scope: !951, file: !1, line: 57, column: 1)
!996 = !DILocation(line: 57, column: 1, scope: !997)
!997 = !DILexicalBlockFile(scope: !993, file: !1, discriminator: 60)
!998 = !DILocation(line: 57, column: 1, scope: !999)
!999 = !DILexicalBlockFile(scope: !993, file: !1, discriminator: 61)
!1000 = !DILocation(line: 57, column: 1, scope: !1001)
!1001 = !DILexicalBlockFile(scope: !994, file: !1, discriminator: 62)
!1002 = !DILocation(line: 57, column: 1, scope: !1003)
!1003 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 63)
!1004 = distinct !DILexicalBlock(scope: !994, file: !1, line: 57, column: 1)
!1005 = !DILocation(line: 57, column: 1, scope: !1006)
!1006 = !DILexicalBlockFile(scope: !994, file: !1, discriminator: 64)
!1007 = !DILocation(line: 57, column: 1, scope: !1008)
!1008 = !DILexicalBlockFile(scope: !995, file: !1, discriminator: 65)
!1009 = !DILocation(line: 57, column: 1, scope: !1010)
!1010 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 66)
!1011 = !DILocation(line: 57, column: 1, scope: !1012)
!1012 = !DILexicalBlockFile(scope: !1013, file: !1, discriminator: 67)
!1013 = distinct !DILexicalBlock(scope: !951, file: !1, line: 57, column: 1)
!1014 = !DILocation(line: 57, column: 1, scope: !1015)
!1015 = !DILexicalBlockFile(scope: !1016, file: !1, discriminator: 68)
!1016 = distinct !DILexicalBlock(scope: !951, file: !1, line: 57, column: 1)
!1017 = !DILocation(line: 57, column: 1, scope: !1018)
!1018 = !DILexicalBlockFile(scope: !1019, file: !1, discriminator: 69)
!1019 = distinct !DILexicalBlock(scope: !1016, file: !1, line: 57, column: 1)
!1020 = !DILocation(line: 57, column: 1, scope: !1021)
!1021 = !DILexicalBlockFile(scope: !1022, file: !1, discriminator: 70)
!1022 = distinct !DILexicalBlock(scope: !1019, file: !1, line: 57, column: 1)
!1023 = !DILocation(line: 57, column: 1, scope: !1024)
!1024 = !DILexicalBlockFile(scope: !1025, file: !1, discriminator: 71)
!1025 = distinct !DILexicalBlock(scope: !1022, file: !1, line: 57, column: 1)
!1026 = !DILocation(line: 57, column: 1, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1022, file: !1, discriminator: 72)
!1028 = !DILocation(line: 57, column: 1, scope: !1029)
!1029 = !DILexicalBlockFile(scope: !1019, file: !1, discriminator: 73)
!1030 = !DILocation(line: 57, column: 1, scope: !1031)
!1031 = !DILexicalBlockFile(scope: !1019, file: !1, discriminator: 74)
!1032 = !DILocation(line: 57, column: 1, scope: !1033)
!1033 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 75)
!1034 = !DILocation(line: 57, column: 1, scope: !1035)
!1035 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 76)
!1036 = !DILocation(line: 57, column: 1, scope: !1037)
!1037 = !DILexicalBlockFile(scope: !1038, file: !1, discriminator: 77)
!1038 = distinct !DILexicalBlock(scope: !332, file: !1, line: 57, column: 1)
!1039 = !DILocation(line: 57, column: 1, scope: !1040)
!1040 = !DILexicalBlockFile(scope: !1041, file: !1, discriminator: 78)
!1041 = distinct !DILexicalBlock(scope: !332, file: !1, line: 57, column: 1)
!1042 = !DILocation(line: 57, column: 1, scope: !1043)
!1043 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 79)
!1044 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 57, column: 1)
!1045 = distinct !DILexicalBlock(scope: !1041, file: !1, line: 57, column: 1)
!1046 = !DILocation(line: 57, column: 1, scope: !1047)
!1047 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 80)
!1048 = !DILocation(line: 57, column: 1, scope: !1049)
!1049 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 81)
!1050 = !DILocation(line: 57, column: 1, scope: !1051)
!1051 = !DILexicalBlockFile(scope: !1045, file: !1, discriminator: 82)
!1052 = !DILocation(line: 57, column: 1, scope: !1053)
!1053 = !DILexicalBlockFile(scope: !1054, file: !1, discriminator: 83)
!1054 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 57, column: 1)
!1055 = !DILocation(line: 57, column: 1, scope: !1056)
!1056 = !DILexicalBlockFile(scope: !1045, file: !1, discriminator: 84)
!1057 = !DILocation(line: 57, column: 1, scope: !1058)
!1058 = !DILexicalBlockFile(scope: !1041, file: !1, discriminator: 85)
!1059 = !DILocation(line: 57, column: 1, scope: !1060)
!1060 = !DILexicalBlockFile(scope: !1041, file: !1, discriminator: 86)
!1061 = !DILocation(line: 57, column: 1, scope: !1062)
!1062 = !DILexicalBlockFile(scope: !1063, file: !1, discriminator: 87)
!1063 = distinct !DILexicalBlock(scope: !332, file: !1, line: 57, column: 1)
!1064 = !DILocation(line: 57, column: 1, scope: !1065)
!1065 = !DILexicalBlockFile(scope: !1063, file: !1, discriminator: 88)
!1066 = !DILocation(line: 57, column: 1, scope: !1067)
!1067 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 89)
!1068 = !DILocalVariable(name: "head", arg: 1, scope: !335, file: !1, line: 57, type: !46)
!1069 = !DILocation(line: 57, column: 1, scope: !335)
!1070 = !DILocalVariable(name: "parent", arg: 2, scope: !335, file: !1, line: 57, type: !50)
!1071 = !DILocalVariable(name: "elm", arg: 3, scope: !335, file: !1, line: 57, type: !50)
!1072 = !DILocalVariable(name: "tmp", scope: !335, file: !1, line: 57, type: !50)
!1073 = !DILocation(line: 57, column: 1, scope: !1074)
!1074 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 90)
!1075 = !DILocation(line: 57, column: 1, scope: !1076)
!1076 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 91)
!1077 = !DILocation(line: 57, column: 1, scope: !1078)
!1078 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 92)
!1079 = !DILocation(line: 57, column: 1, scope: !1080)
!1080 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 93)
!1081 = !DILocation(line: 57, column: 1, scope: !1082)
!1082 = !DILexicalBlockFile(scope: !1083, file: !1, discriminator: 94)
!1083 = distinct !DILexicalBlock(scope: !1084, file: !1, line: 57, column: 1)
!1084 = distinct !DILexicalBlock(scope: !335, file: !1, line: 57, column: 1)
!1085 = !DILocation(line: 57, column: 1, scope: !1086)
!1086 = !DILexicalBlockFile(scope: !1087, file: !1, discriminator: 95)
!1087 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 57, column: 1)
!1088 = !DILocation(line: 57, column: 1, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1090, file: !1, discriminator: 96)
!1090 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 57, column: 1)
!1091 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 57, column: 1)
!1092 = !DILocation(line: 57, column: 1, scope: !1093)
!1093 = !DILexicalBlockFile(scope: !1094, file: !1, discriminator: 97)
!1094 = distinct !DILexicalBlock(scope: !1090, file: !1, line: 57, column: 1)
!1095 = !DILocation(line: 57, column: 1, scope: !1096)
!1096 = !DILexicalBlockFile(scope: !1090, file: !1, discriminator: 98)
!1097 = !DILocation(line: 57, column: 1, scope: !1098)
!1098 = !DILexicalBlockFile(scope: !1099, file: !1, discriminator: 99)
!1099 = distinct !DILexicalBlock(scope: !1090, file: !1, line: 57, column: 1)
!1100 = !DILocation(line: 57, column: 1, scope: !1101)
!1101 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 100)
!1102 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 57, column: 1)
!1103 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 57, column: 1)
!1104 = !DILocation(line: 57, column: 1, scope: !1105)
!1105 = !DILexicalBlockFile(scope: !1099, file: !1, discriminator: 101)
!1106 = !DILocation(line: 57, column: 1, scope: !1107)
!1107 = !DILexicalBlockFile(scope: !1108, file: !1, discriminator: 102)
!1108 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 57, column: 1)
!1109 = !DILocation(line: 57, column: 1, scope: !1110)
!1110 = !DILexicalBlockFile(scope: !1111, file: !1, discriminator: 103)
!1111 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 57, column: 1)
!1112 = !DILocation(line: 57, column: 1, scope: !1113)
!1113 = !DILexicalBlockFile(scope: !1114, file: !1, discriminator: 104)
!1114 = distinct !DILexicalBlock(scope: !1115, file: !1, line: 57, column: 1)
!1115 = distinct !DILexicalBlock(scope: !1111, file: !1, line: 57, column: 1)
!1116 = !DILocation(line: 57, column: 1, scope: !1117)
!1117 = !DILexicalBlockFile(scope: !1114, file: !1, discriminator: 105)
!1118 = !DILocation(line: 57, column: 1, scope: !1119)
!1119 = !DILexicalBlockFile(scope: !1114, file: !1, discriminator: 106)
!1120 = !DILocation(line: 57, column: 1, scope: !1121)
!1121 = !DILexicalBlockFile(scope: !1115, file: !1, discriminator: 107)
!1122 = !DILocation(line: 57, column: 1, scope: !1123)
!1123 = !DILexicalBlockFile(scope: !1111, file: !1, discriminator: 108)
!1124 = !DILocation(line: 57, column: 1, scope: !1125)
!1125 = !DILexicalBlockFile(scope: !1099, file: !1, discriminator: 109)
!1126 = !DILocation(line: 57, column: 1, scope: !1127)
!1127 = !DILexicalBlockFile(scope: !1128, file: !1, discriminator: 110)
!1128 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 57, column: 1)
!1129 = !DILocation(line: 57, column: 1, scope: !1130)
!1130 = !DILexicalBlockFile(scope: !1131, file: !1, discriminator: 111)
!1131 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 57, column: 1)
!1132 = !DILocation(line: 57, column: 1, scope: !1133)
!1133 = !DILexicalBlockFile(scope: !1131, file: !1, discriminator: 112)
!1134 = !DILocation(line: 57, column: 1, scope: !1135)
!1135 = !DILexicalBlockFile(scope: !1136, file: !1, discriminator: 113)
!1136 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 57, column: 1)
!1137 = !DILocation(line: 57, column: 1, scope: !1138)
!1138 = !DILexicalBlockFile(scope: !1136, file: !1, discriminator: 114)
!1139 = !DILocation(line: 57, column: 1, scope: !1140)
!1140 = !DILexicalBlockFile(scope: !1099, file: !1, discriminator: 115)
!1141 = !DILocation(line: 57, column: 1, scope: !1142)
!1142 = !DILexicalBlockFile(scope: !1090, file: !1, discriminator: 116)
!1143 = !DILocation(line: 57, column: 1, scope: !1144)
!1144 = !DILexicalBlockFile(scope: !1145, file: !1, discriminator: 117)
!1145 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 57, column: 1)
!1146 = !DILocation(line: 57, column: 1, scope: !1147)
!1147 = !DILexicalBlockFile(scope: !1145, file: !1, discriminator: 118)
!1148 = !DILocation(line: 57, column: 1, scope: !1149)
!1149 = !DILexicalBlockFile(scope: !1145, file: !1, discriminator: 119)
!1150 = !DILocation(line: 57, column: 1, scope: !1151)
!1151 = !DILexicalBlockFile(scope: !1145, file: !1, discriminator: 120)
!1152 = !DILocation(line: 57, column: 1, scope: !1153)
!1153 = !DILexicalBlockFile(scope: !1154, file: !1, discriminator: 121)
!1154 = distinct !DILexicalBlock(scope: !1145, file: !1, line: 57, column: 1)
!1155 = !DILocation(line: 57, column: 1, scope: !1156)
!1156 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 122)
!1157 = distinct !DILexicalBlock(scope: !1158, file: !1, line: 57, column: 1)
!1158 = distinct !DILexicalBlock(scope: !1145, file: !1, line: 57, column: 1)
!1159 = !DILocation(line: 57, column: 1, scope: !1160)
!1160 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 123)
!1161 = !DILocalVariable(name: "oleft", scope: !1162, file: !1, line: 57, type: !50)
!1162 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 57, column: 1)
!1163 = !DILocation(line: 57, column: 1, scope: !1162)
!1164 = !DILocation(line: 57, column: 1, scope: !1165)
!1165 = !DILexicalBlockFile(scope: !1166, file: !1, discriminator: 124)
!1166 = distinct !DILexicalBlock(scope: !1162, file: !1, line: 57, column: 1)
!1167 = !DILocation(line: 57, column: 1, scope: !1168)
!1168 = !DILexicalBlockFile(scope: !1166, file: !1, discriminator: 125)
!1169 = !DILocation(line: 57, column: 1, scope: !1170)
!1170 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 126)
!1171 = !DILocation(line: 57, column: 1, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 127)
!1173 = distinct !DILexicalBlock(scope: !1162, file: !1, line: 57, column: 1)
!1174 = !DILocation(line: 57, column: 1, scope: !1175)
!1175 = !DILexicalBlockFile(scope: !1176, file: !1, discriminator: 128)
!1176 = distinct !DILexicalBlock(scope: !1177, file: !1, line: 57, column: 1)
!1177 = distinct !DILexicalBlock(scope: !1173, file: !1, line: 57, column: 1)
!1178 = !DILocation(line: 57, column: 1, scope: !1179)
!1179 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 129)
!1180 = !DILocation(line: 57, column: 1, scope: !1181)
!1181 = !DILexicalBlockFile(scope: !1182, file: !1, discriminator: 130)
!1182 = distinct !DILexicalBlock(scope: !1173, file: !1, line: 57, column: 1)
!1183 = !DILocation(line: 57, column: 1, scope: !1184)
!1184 = !DILexicalBlockFile(scope: !1185, file: !1, discriminator: 131)
!1185 = distinct !DILexicalBlock(scope: !1173, file: !1, line: 57, column: 1)
!1186 = !DILocation(line: 57, column: 1, scope: !1187)
!1187 = !DILexicalBlockFile(scope: !1188, file: !1, discriminator: 132)
!1188 = distinct !DILexicalBlock(scope: !1189, file: !1, line: 57, column: 1)
!1189 = distinct !DILexicalBlock(scope: !1185, file: !1, line: 57, column: 1)
!1190 = !DILocation(line: 57, column: 1, scope: !1191)
!1191 = !DILexicalBlockFile(scope: !1188, file: !1, discriminator: 133)
!1192 = !DILocation(line: 57, column: 1, scope: !1193)
!1193 = !DILexicalBlockFile(scope: !1188, file: !1, discriminator: 134)
!1194 = !DILocation(line: 57, column: 1, scope: !1195)
!1195 = !DILexicalBlockFile(scope: !1189, file: !1, discriminator: 135)
!1196 = !DILocation(line: 57, column: 1, scope: !1197)
!1197 = !DILexicalBlockFile(scope: !1185, file: !1, discriminator: 136)
!1198 = !DILocation(line: 57, column: 1, scope: !1199)
!1199 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 137)
!1200 = !DILocation(line: 57, column: 1, scope: !1201)
!1201 = !DILexicalBlockFile(scope: !1202, file: !1, discriminator: 138)
!1202 = distinct !DILexicalBlock(scope: !1173, file: !1, line: 57, column: 1)
!1203 = !DILocation(line: 57, column: 1, scope: !1204)
!1204 = !DILexicalBlockFile(scope: !1205, file: !1, discriminator: 139)
!1205 = distinct !DILexicalBlock(scope: !1173, file: !1, line: 57, column: 1)
!1206 = !DILocation(line: 57, column: 1, scope: !1207)
!1207 = !DILexicalBlockFile(scope: !1205, file: !1, discriminator: 140)
!1208 = !DILocation(line: 57, column: 1, scope: !1209)
!1209 = !DILexicalBlockFile(scope: !1210, file: !1, discriminator: 141)
!1210 = distinct !DILexicalBlock(scope: !1205, file: !1, line: 57, column: 1)
!1211 = !DILocation(line: 57, column: 1, scope: !1212)
!1212 = !DILexicalBlockFile(scope: !1210, file: !1, discriminator: 142)
!1213 = !DILocation(line: 57, column: 1, scope: !1214)
!1214 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 143)
!1215 = !DILocation(line: 57, column: 1, scope: !1216)
!1216 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 144)
!1217 = !DILocation(line: 57, column: 1, scope: !1218)
!1218 = !DILexicalBlockFile(scope: !1158, file: !1, discriminator: 145)
!1219 = !DILocation(line: 57, column: 1, scope: !1220)
!1220 = !DILexicalBlockFile(scope: !1221, file: !1, discriminator: 146)
!1221 = distinct !DILexicalBlock(scope: !1158, file: !1, line: 57, column: 1)
!1222 = !DILocation(line: 57, column: 1, scope: !1223)
!1223 = !DILexicalBlockFile(scope: !1158, file: !1, discriminator: 147)
!1224 = !DILocation(line: 57, column: 1, scope: !1225)
!1225 = !DILexicalBlockFile(scope: !1226, file: !1, discriminator: 148)
!1226 = distinct !DILexicalBlock(scope: !1158, file: !1, line: 57, column: 1)
!1227 = !DILocation(line: 57, column: 1, scope: !1228)
!1228 = !DILexicalBlockFile(scope: !1229, file: !1, discriminator: 149)
!1229 = distinct !DILexicalBlock(scope: !1230, file: !1, line: 57, column: 1)
!1230 = distinct !DILexicalBlock(scope: !1226, file: !1, line: 57, column: 1)
!1231 = !DILocation(line: 57, column: 1, scope: !1232)
!1232 = !DILexicalBlockFile(scope: !1226, file: !1, discriminator: 150)
!1233 = !DILocation(line: 57, column: 1, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !1235, file: !1, discriminator: 151)
!1235 = distinct !DILexicalBlock(scope: !1226, file: !1, line: 57, column: 1)
!1236 = !DILocation(line: 57, column: 1, scope: !1237)
!1237 = !DILexicalBlockFile(scope: !1238, file: !1, discriminator: 152)
!1238 = distinct !DILexicalBlock(scope: !1226, file: !1, line: 57, column: 1)
!1239 = !DILocation(line: 57, column: 1, scope: !1240)
!1240 = !DILexicalBlockFile(scope: !1241, file: !1, discriminator: 153)
!1241 = distinct !DILexicalBlock(scope: !1242, file: !1, line: 57, column: 1)
!1242 = distinct !DILexicalBlock(scope: !1238, file: !1, line: 57, column: 1)
!1243 = !DILocation(line: 57, column: 1, scope: !1244)
!1244 = !DILexicalBlockFile(scope: !1241, file: !1, discriminator: 154)
!1245 = !DILocation(line: 57, column: 1, scope: !1246)
!1246 = !DILexicalBlockFile(scope: !1241, file: !1, discriminator: 155)
!1247 = !DILocation(line: 57, column: 1, scope: !1248)
!1248 = !DILexicalBlockFile(scope: !1242, file: !1, discriminator: 156)
!1249 = !DILocation(line: 57, column: 1, scope: !1250)
!1250 = !DILexicalBlockFile(scope: !1238, file: !1, discriminator: 157)
!1251 = !DILocation(line: 57, column: 1, scope: !1252)
!1252 = !DILexicalBlockFile(scope: !1226, file: !1, discriminator: 158)
!1253 = !DILocation(line: 57, column: 1, scope: !1254)
!1254 = !DILexicalBlockFile(scope: !1255, file: !1, discriminator: 159)
!1255 = distinct !DILexicalBlock(scope: !1226, file: !1, line: 57, column: 1)
!1256 = !DILocation(line: 57, column: 1, scope: !1257)
!1257 = !DILexicalBlockFile(scope: !1258, file: !1, discriminator: 160)
!1258 = distinct !DILexicalBlock(scope: !1226, file: !1, line: 57, column: 1)
!1259 = !DILocation(line: 57, column: 1, scope: !1260)
!1260 = !DILexicalBlockFile(scope: !1258, file: !1, discriminator: 161)
!1261 = !DILocation(line: 57, column: 1, scope: !1262)
!1262 = !DILexicalBlockFile(scope: !1263, file: !1, discriminator: 162)
!1263 = distinct !DILexicalBlock(scope: !1258, file: !1, line: 57, column: 1)
!1264 = !DILocation(line: 57, column: 1, scope: !1265)
!1265 = !DILexicalBlockFile(scope: !1263, file: !1, discriminator: 163)
!1266 = !DILocation(line: 57, column: 1, scope: !1267)
!1267 = !DILexicalBlockFile(scope: !1226, file: !1, discriminator: 164)
!1268 = !DILocation(line: 57, column: 1, scope: !1269)
!1269 = !DILexicalBlockFile(scope: !1158, file: !1, discriminator: 165)
!1270 = !DILocation(line: 57, column: 1, scope: !1271)
!1271 = !DILexicalBlockFile(scope: !1087, file: !1, discriminator: 166)
!1272 = !DILocation(line: 57, column: 1, scope: !1273)
!1273 = !DILexicalBlockFile(scope: !1274, file: !1, discriminator: 167)
!1274 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 57, column: 1)
!1275 = !DILocation(line: 57, column: 1, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 168)
!1277 = distinct !DILexicalBlock(scope: !1278, file: !1, line: 57, column: 1)
!1278 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 57, column: 1)
!1279 = !DILocation(line: 57, column: 1, scope: !1280)
!1280 = !DILexicalBlockFile(scope: !1281, file: !1, discriminator: 169)
!1281 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 57, column: 1)
!1282 = !DILocation(line: 57, column: 1, scope: !1283)
!1283 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 170)
!1284 = !DILocation(line: 57, column: 1, scope: !1285)
!1285 = !DILexicalBlockFile(scope: !1286, file: !1, discriminator: 171)
!1286 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 57, column: 1)
!1287 = !DILocation(line: 57, column: 1, scope: !1288)
!1288 = !DILexicalBlockFile(scope: !1289, file: !1, discriminator: 172)
!1289 = distinct !DILexicalBlock(scope: !1290, file: !1, line: 57, column: 1)
!1290 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 57, column: 1)
!1291 = !DILocation(line: 57, column: 1, scope: !1292)
!1292 = !DILexicalBlockFile(scope: !1286, file: !1, discriminator: 173)
!1293 = !DILocation(line: 57, column: 1, scope: !1294)
!1294 = !DILexicalBlockFile(scope: !1295, file: !1, discriminator: 174)
!1295 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 57, column: 1)
!1296 = !DILocation(line: 57, column: 1, scope: !1297)
!1297 = !DILexicalBlockFile(scope: !1298, file: !1, discriminator: 175)
!1298 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 57, column: 1)
!1299 = !DILocation(line: 57, column: 1, scope: !1300)
!1300 = !DILexicalBlockFile(scope: !1301, file: !1, discriminator: 176)
!1301 = distinct !DILexicalBlock(scope: !1302, file: !1, line: 57, column: 1)
!1302 = distinct !DILexicalBlock(scope: !1298, file: !1, line: 57, column: 1)
!1303 = !DILocation(line: 57, column: 1, scope: !1304)
!1304 = !DILexicalBlockFile(scope: !1301, file: !1, discriminator: 177)
!1305 = !DILocation(line: 57, column: 1, scope: !1306)
!1306 = !DILexicalBlockFile(scope: !1301, file: !1, discriminator: 178)
!1307 = !DILocation(line: 57, column: 1, scope: !1308)
!1308 = !DILexicalBlockFile(scope: !1302, file: !1, discriminator: 179)
!1309 = !DILocation(line: 57, column: 1, scope: !1310)
!1310 = !DILexicalBlockFile(scope: !1298, file: !1, discriminator: 180)
!1311 = !DILocation(line: 57, column: 1, scope: !1312)
!1312 = !DILexicalBlockFile(scope: !1286, file: !1, discriminator: 181)
!1313 = !DILocation(line: 57, column: 1, scope: !1314)
!1314 = !DILexicalBlockFile(scope: !1315, file: !1, discriminator: 182)
!1315 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 57, column: 1)
!1316 = !DILocation(line: 57, column: 1, scope: !1317)
!1317 = !DILexicalBlockFile(scope: !1318, file: !1, discriminator: 183)
!1318 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 57, column: 1)
!1319 = !DILocation(line: 57, column: 1, scope: !1320)
!1320 = !DILexicalBlockFile(scope: !1318, file: !1, discriminator: 184)
!1321 = !DILocation(line: 57, column: 1, scope: !1322)
!1322 = !DILexicalBlockFile(scope: !1323, file: !1, discriminator: 185)
!1323 = distinct !DILexicalBlock(scope: !1318, file: !1, line: 57, column: 1)
!1324 = !DILocation(line: 57, column: 1, scope: !1325)
!1325 = !DILexicalBlockFile(scope: !1323, file: !1, discriminator: 186)
!1326 = !DILocation(line: 57, column: 1, scope: !1327)
!1327 = !DILexicalBlockFile(scope: !1286, file: !1, discriminator: 187)
!1328 = !DILocation(line: 57, column: 1, scope: !1329)
!1329 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 188)
!1330 = !DILocation(line: 57, column: 1, scope: !1331)
!1331 = !DILexicalBlockFile(scope: !1332, file: !1, discriminator: 189)
!1332 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 57, column: 1)
!1333 = !DILocation(line: 57, column: 1, scope: !1334)
!1334 = !DILexicalBlockFile(scope: !1332, file: !1, discriminator: 190)
!1335 = !DILocation(line: 57, column: 1, scope: !1336)
!1336 = !DILexicalBlockFile(scope: !1332, file: !1, discriminator: 191)
!1337 = !DILocation(line: 57, column: 1, scope: !1338)
!1338 = !DILexicalBlockFile(scope: !1332, file: !1, discriminator: 192)
!1339 = !DILocation(line: 57, column: 1, scope: !1340)
!1340 = !DILexicalBlockFile(scope: !1341, file: !1, discriminator: 193)
!1341 = distinct !DILexicalBlock(scope: !1332, file: !1, line: 57, column: 1)
!1342 = !DILocation(line: 57, column: 1, scope: !1343)
!1343 = !DILexicalBlockFile(scope: !1344, file: !1, discriminator: 194)
!1344 = distinct !DILexicalBlock(scope: !1345, file: !1, line: 57, column: 1)
!1345 = distinct !DILexicalBlock(scope: !1332, file: !1, line: 57, column: 1)
!1346 = !DILocation(line: 57, column: 1, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !1344, file: !1, discriminator: 195)
!1348 = !DILocalVariable(name: "oright", scope: !1349, file: !1, line: 57, type: !50)
!1349 = distinct !DILexicalBlock(scope: !1344, file: !1, line: 57, column: 1)
!1350 = !DILocation(line: 57, column: 1, scope: !1349)
!1351 = !DILocation(line: 57, column: 1, scope: !1352)
!1352 = !DILexicalBlockFile(scope: !1353, file: !1, discriminator: 196)
!1353 = distinct !DILexicalBlock(scope: !1349, file: !1, line: 57, column: 1)
!1354 = !DILocation(line: 57, column: 1, scope: !1355)
!1355 = !DILexicalBlockFile(scope: !1353, file: !1, discriminator: 197)
!1356 = !DILocation(line: 57, column: 1, scope: !1357)
!1357 = !DILexicalBlockFile(scope: !1349, file: !1, discriminator: 198)
!1358 = !DILocation(line: 57, column: 1, scope: !1359)
!1359 = !DILexicalBlockFile(scope: !1360, file: !1, discriminator: 199)
!1360 = distinct !DILexicalBlock(scope: !1349, file: !1, line: 57, column: 1)
!1361 = !DILocation(line: 57, column: 1, scope: !1362)
!1362 = !DILexicalBlockFile(scope: !1363, file: !1, discriminator: 200)
!1363 = distinct !DILexicalBlock(scope: !1364, file: !1, line: 57, column: 1)
!1364 = distinct !DILexicalBlock(scope: !1360, file: !1, line: 57, column: 1)
!1365 = !DILocation(line: 57, column: 1, scope: !1366)
!1366 = !DILexicalBlockFile(scope: !1360, file: !1, discriminator: 201)
!1367 = !DILocation(line: 57, column: 1, scope: !1368)
!1368 = !DILexicalBlockFile(scope: !1369, file: !1, discriminator: 202)
!1369 = distinct !DILexicalBlock(scope: !1360, file: !1, line: 57, column: 1)
!1370 = !DILocation(line: 57, column: 1, scope: !1371)
!1371 = !DILexicalBlockFile(scope: !1372, file: !1, discriminator: 203)
!1372 = distinct !DILexicalBlock(scope: !1360, file: !1, line: 57, column: 1)
!1373 = !DILocation(line: 57, column: 1, scope: !1374)
!1374 = !DILexicalBlockFile(scope: !1375, file: !1, discriminator: 204)
!1375 = distinct !DILexicalBlock(scope: !1376, file: !1, line: 57, column: 1)
!1376 = distinct !DILexicalBlock(scope: !1372, file: !1, line: 57, column: 1)
!1377 = !DILocation(line: 57, column: 1, scope: !1378)
!1378 = !DILexicalBlockFile(scope: !1375, file: !1, discriminator: 205)
!1379 = !DILocation(line: 57, column: 1, scope: !1380)
!1380 = !DILexicalBlockFile(scope: !1375, file: !1, discriminator: 206)
!1381 = !DILocation(line: 57, column: 1, scope: !1382)
!1382 = !DILexicalBlockFile(scope: !1376, file: !1, discriminator: 207)
!1383 = !DILocation(line: 57, column: 1, scope: !1384)
!1384 = !DILexicalBlockFile(scope: !1372, file: !1, discriminator: 208)
!1385 = !DILocation(line: 57, column: 1, scope: !1386)
!1386 = !DILexicalBlockFile(scope: !1360, file: !1, discriminator: 209)
!1387 = !DILocation(line: 57, column: 1, scope: !1388)
!1388 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 210)
!1389 = distinct !DILexicalBlock(scope: !1360, file: !1, line: 57, column: 1)
!1390 = !DILocation(line: 57, column: 1, scope: !1391)
!1391 = !DILexicalBlockFile(scope: !1392, file: !1, discriminator: 211)
!1392 = distinct !DILexicalBlock(scope: !1360, file: !1, line: 57, column: 1)
!1393 = !DILocation(line: 57, column: 1, scope: !1394)
!1394 = !DILexicalBlockFile(scope: !1392, file: !1, discriminator: 212)
!1395 = !DILocation(line: 57, column: 1, scope: !1396)
!1396 = !DILexicalBlockFile(scope: !1397, file: !1, discriminator: 213)
!1397 = distinct !DILexicalBlock(scope: !1392, file: !1, line: 57, column: 1)
!1398 = !DILocation(line: 57, column: 1, scope: !1399)
!1399 = !DILexicalBlockFile(scope: !1397, file: !1, discriminator: 214)
!1400 = !DILocation(line: 57, column: 1, scope: !1401)
!1401 = !DILexicalBlockFile(scope: !1360, file: !1, discriminator: 215)
!1402 = !DILocation(line: 57, column: 1, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1349, file: !1, discriminator: 216)
!1404 = !DILocation(line: 57, column: 1, scope: !1405)
!1405 = !DILexicalBlockFile(scope: !1345, file: !1, discriminator: 217)
!1406 = !DILocation(line: 57, column: 1, scope: !1407)
!1407 = !DILexicalBlockFile(scope: !1408, file: !1, discriminator: 218)
!1408 = distinct !DILexicalBlock(scope: !1345, file: !1, line: 57, column: 1)
!1409 = !DILocation(line: 57, column: 1, scope: !1410)
!1410 = !DILexicalBlockFile(scope: !1345, file: !1, discriminator: 219)
!1411 = !DILocation(line: 57, column: 1, scope: !1412)
!1412 = !DILexicalBlockFile(scope: !1413, file: !1, discriminator: 220)
!1413 = distinct !DILexicalBlock(scope: !1345, file: !1, line: 57, column: 1)
!1414 = !DILocation(line: 57, column: 1, scope: !1415)
!1415 = !DILexicalBlockFile(scope: !1416, file: !1, discriminator: 221)
!1416 = distinct !DILexicalBlock(scope: !1417, file: !1, line: 57, column: 1)
!1417 = distinct !DILexicalBlock(scope: !1413, file: !1, line: 57, column: 1)
!1418 = !DILocation(line: 57, column: 1, scope: !1419)
!1419 = !DILexicalBlockFile(scope: !1413, file: !1, discriminator: 222)
!1420 = !DILocation(line: 57, column: 1, scope: !1421)
!1421 = !DILexicalBlockFile(scope: !1422, file: !1, discriminator: 223)
!1422 = distinct !DILexicalBlock(scope: !1413, file: !1, line: 57, column: 1)
!1423 = !DILocation(line: 57, column: 1, scope: !1424)
!1424 = !DILexicalBlockFile(scope: !1425, file: !1, discriminator: 224)
!1425 = distinct !DILexicalBlock(scope: !1413, file: !1, line: 57, column: 1)
!1426 = !DILocation(line: 57, column: 1, scope: !1427)
!1427 = !DILexicalBlockFile(scope: !1428, file: !1, discriminator: 225)
!1428 = distinct !DILexicalBlock(scope: !1429, file: !1, line: 57, column: 1)
!1429 = distinct !DILexicalBlock(scope: !1425, file: !1, line: 57, column: 1)
!1430 = !DILocation(line: 57, column: 1, scope: !1431)
!1431 = !DILexicalBlockFile(scope: !1428, file: !1, discriminator: 226)
!1432 = !DILocation(line: 57, column: 1, scope: !1433)
!1433 = !DILexicalBlockFile(scope: !1428, file: !1, discriminator: 227)
!1434 = !DILocation(line: 57, column: 1, scope: !1435)
!1435 = !DILexicalBlockFile(scope: !1429, file: !1, discriminator: 228)
!1436 = !DILocation(line: 57, column: 1, scope: !1437)
!1437 = !DILexicalBlockFile(scope: !1425, file: !1, discriminator: 229)
!1438 = !DILocation(line: 57, column: 1, scope: !1439)
!1439 = !DILexicalBlockFile(scope: !1413, file: !1, discriminator: 230)
!1440 = !DILocation(line: 57, column: 1, scope: !1441)
!1441 = !DILexicalBlockFile(scope: !1442, file: !1, discriminator: 231)
!1442 = distinct !DILexicalBlock(scope: !1413, file: !1, line: 57, column: 1)
!1443 = !DILocation(line: 57, column: 1, scope: !1444)
!1444 = !DILexicalBlockFile(scope: !1445, file: !1, discriminator: 232)
!1445 = distinct !DILexicalBlock(scope: !1413, file: !1, line: 57, column: 1)
!1446 = !DILocation(line: 57, column: 1, scope: !1447)
!1447 = !DILexicalBlockFile(scope: !1445, file: !1, discriminator: 233)
!1448 = !DILocation(line: 57, column: 1, scope: !1449)
!1449 = !DILexicalBlockFile(scope: !1450, file: !1, discriminator: 234)
!1450 = distinct !DILexicalBlock(scope: !1445, file: !1, line: 57, column: 1)
!1451 = !DILocation(line: 57, column: 1, scope: !1452)
!1452 = !DILexicalBlockFile(scope: !1450, file: !1, discriminator: 235)
!1453 = !DILocation(line: 57, column: 1, scope: !1454)
!1454 = !DILexicalBlockFile(scope: !1413, file: !1, discriminator: 236)
!1455 = !DILocation(line: 57, column: 1, scope: !1456)
!1456 = !DILexicalBlockFile(scope: !1345, file: !1, discriminator: 237)
!1457 = !DILocation(line: 57, column: 1, scope: !1458)
!1458 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 238)
!1459 = !DILocation(line: 57, column: 1, scope: !1460)
!1460 = !DILexicalBlockFile(scope: !1461, file: !1, discriminator: 239)
!1461 = distinct !DILexicalBlock(scope: !335, file: !1, line: 57, column: 1)
!1462 = !DILocation(line: 57, column: 1, scope: !1463)
!1463 = !DILexicalBlockFile(scope: !1461, file: !1, discriminator: 240)
!1464 = !DILocation(line: 57, column: 1, scope: !1465)
!1465 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 241)
!1466 = !DILocalVariable(name: "err", scope: !341, file: !1, line: 68, type: !60)
!1467 = !DILocation(line: 68, column: 7, scope: !341)
!1468 = !DILocalVariable(name: "fd", scope: !341, file: !1, line: 69, type: !60)
!1469 = !DILocation(line: 69, column: 7, scope: !341)
!1470 = !DILocation(line: 71, column: 8, scope: !341)
!1471 = !DILocation(line: 71, column: 6, scope: !341)
!1472 = !DILocation(line: 72, column: 7, scope: !1473)
!1473 = distinct !DILexicalBlock(scope: !341, file: !1, line: 72, column: 7)
!1474 = !DILocation(line: 72, column: 10, scope: !1473)
!1475 = !DILocation(line: 72, column: 7, scope: !341)
!1476 = !DILocation(line: 73, column: 12, scope: !1473)
!1477 = !DILocation(line: 73, column: 5, scope: !1473)
!1478 = !DILocation(line: 75, column: 7, scope: !1479)
!1479 = distinct !DILexicalBlock(scope: !341, file: !1, line: 75, column: 7)
!1480 = !DILocation(line: 75, column: 13, scope: !1479)
!1481 = !DILocation(line: 75, column: 7, scope: !341)
!1482 = !DILocation(line: 76, column: 13, scope: !1479)
!1483 = !DILocation(line: 76, column: 12, scope: !1479)
!1484 = !DILocation(line: 76, column: 5, scope: !1479)
!1485 = !DILocation(line: 78, column: 8, scope: !341)
!1486 = !DILocation(line: 78, column: 6, scope: !341)
!1487 = !DILocation(line: 79, column: 7, scope: !1488)
!1488 = distinct !DILexicalBlock(scope: !341, file: !1, line: 79, column: 7)
!1489 = !DILocation(line: 79, column: 10, scope: !1488)
!1490 = !DILocation(line: 79, column: 7, scope: !341)
!1491 = !DILocation(line: 80, column: 13, scope: !1488)
!1492 = !DILocation(line: 80, column: 12, scope: !1488)
!1493 = !DILocation(line: 80, column: 5, scope: !1488)
!1494 = !DILocation(line: 82, column: 21, scope: !341)
!1495 = !DILocation(line: 82, column: 9, scope: !341)
!1496 = !DILocation(line: 82, column: 7, scope: !341)
!1497 = !DILocation(line: 83, column: 7, scope: !1498)
!1498 = distinct !DILexicalBlock(scope: !341, file: !1, line: 83, column: 7)
!1499 = !DILocation(line: 83, column: 11, scope: !1498)
!1500 = !DILocation(line: 83, column: 7, scope: !341)
!1501 = !DILocation(line: 84, column: 24, scope: !1498)
!1502 = !DILocation(line: 84, column: 11, scope: !1498)
!1503 = !DILocation(line: 84, column: 9, scope: !1498)
!1504 = !DILocation(line: 84, column: 5, scope: !1498)
!1505 = !DILocation(line: 86, column: 7, scope: !1506)
!1506 = distinct !DILexicalBlock(scope: !341, file: !1, line: 86, column: 7)
!1507 = !DILocation(line: 86, column: 7, scope: !341)
!1508 = !DILocation(line: 87, column: 15, scope: !1509)
!1509 = distinct !DILexicalBlock(scope: !1506, file: !1, line: 86, column: 12)
!1510 = !DILocation(line: 87, column: 5, scope: !1509)
!1511 = !DILocation(line: 88, column: 12, scope: !1509)
!1512 = !DILocation(line: 88, column: 5, scope: !1509)
!1513 = !DILocation(line: 91, column: 10, scope: !341)
!1514 = !DILocation(line: 91, column: 3, scope: !341)
!1515 = !DILocation(line: 92, column: 1, scope: !341)
!1516 = !DILocalVariable(name: "loop", arg: 1, scope: !344, file: !1, line: 194, type: !75)
!1517 = !DILocation(line: 194, column: 41, scope: !344)
!1518 = !DILocalVariable(name: "dummy", arg: 2, scope: !344, file: !1, line: 195, type: !92)
!1519 = !DILocation(line: 195, column: 40, scope: !344)
!1520 = !DILocalVariable(name: "events", arg: 3, scope: !344, file: !1, line: 196, type: !81)
!1521 = !DILocation(line: 196, column: 43, scope: !344)
!1522 = !DILocalVariable(name: "e", scope: !344, file: !1, line: 197, type: !295)
!1523 = !DILocation(line: 197, column: 35, scope: !344)
!1524 = !DILocalVariable(name: "w", scope: !344, file: !1, line: 198, type: !50)
!1525 = !DILocation(line: 198, column: 24, scope: !344)
!1526 = !DILocalVariable(name: "h", scope: !344, file: !1, line: 199, type: !69)
!1527 = !DILocation(line: 199, column: 18, scope: !344)
!1528 = !DILocalVariable(name: "queue", scope: !344, file: !1, line: 200, type: !41)
!1529 = !DILocation(line: 200, column: 9, scope: !344)
!1530 = !DILocalVariable(name: "q", scope: !344, file: !1, line: 201, type: !40)
!1531 = !DILocation(line: 201, column: 10, scope: !344)
!1532 = !DILocalVariable(name: "path", scope: !344, file: !1, line: 202, type: !291)
!1533 = !DILocation(line: 202, column: 15, scope: !344)
!1534 = !DILocalVariable(name: "size", scope: !344, file: !1, line: 203, type: !1535)
!1535 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !1536, line: 102, baseType: !1537)
!1536 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1537 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !1538, line: 172, baseType: !141)
!1538 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1539 = !DILocation(line: 203, column: 11, scope: !344)
!1540 = !DILocalVariable(name: "p", scope: !344, file: !1, line: 204, type: !291)
!1541 = !DILocation(line: 204, column: 15, scope: !344)
!1542 = !DILocalVariable(name: "buf", scope: !344, file: !1, line: 206, type: !1543)
!1543 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 32768, align: 8, elements: !1544)
!1544 = !{!1545}
!1545 = !DISubrange(count: 4096)
!1546 = !DILocation(line: 206, column: 8, scope: !344)
!1547 = !DILocation(line: 208, column: 3, scope: !344)
!1548 = !DILocation(line: 209, column: 5, scope: !1549)
!1549 = distinct !DILexicalBlock(scope: !344, file: !1, line: 208, column: 13)
!1550 = !DILocation(line: 210, column: 19, scope: !1549)
!1551 = !DILocation(line: 210, column: 25, scope: !1549)
!1552 = !DILocation(line: 210, column: 37, scope: !1549)
!1553 = !DILocation(line: 210, column: 14, scope: !1549)
!1554 = !DILocation(line: 210, column: 12, scope: !1549)
!1555 = !DILocation(line: 210, column: 7, scope: !1549)
!1556 = !DILocation(line: 211, column: 12, scope: !1549)
!1557 = !DILocation(line: 211, column: 17, scope: !1549)
!1558 = !DILocation(line: 211, column: 23, scope: !1549)
!1559 = !DILocation(line: 211, column: 26, scope: !1560)
!1560 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 1)
!1561 = !DILocation(line: 211, column: 32, scope: !1560)
!1562 = !DILocation(line: 210, column: 7, scope: !1560)
!1563 = !DILocation(line: 213, column: 9, scope: !1564)
!1564 = distinct !DILexicalBlock(scope: !1549, file: !1, line: 213, column: 9)
!1565 = !DILocation(line: 213, column: 14, scope: !1564)
!1566 = !DILocation(line: 213, column: 9, scope: !1549)
!1567 = !DILocation(line: 214, column: 7, scope: !1568)
!1568 = distinct !DILexicalBlock(scope: !1564, file: !1, line: 213, column: 21)
!1569 = !DILocation(line: 214, column: 7, scope: !1570)
!1570 = !DILexicalBlockFile(scope: !1568, file: !1, discriminator: 1)
!1571 = !DILocation(line: 214, column: 7, scope: !1572)
!1572 = !DILexicalBlockFile(scope: !1568, file: !1, discriminator: 2)
!1573 = !DILocation(line: 214, column: 7, scope: !1574)
!1574 = !DILexicalBlockFile(scope: !1568, file: !1, discriminator: 3)
!1575 = !DILocation(line: 214, column: 7, scope: !1576)
!1576 = !DILexicalBlockFile(scope: !1568, file: !1, discriminator: 4)
!1577 = !DILocation(line: 215, column: 7, scope: !1568)
!1578 = !DILocation(line: 218, column: 5, scope: !1549)
!1579 = !DILocation(line: 218, column: 5, scope: !1560)
!1580 = !DILocation(line: 218, column: 5, scope: !1581)
!1581 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 2)
!1582 = !DILocation(line: 218, column: 5, scope: !1583)
!1583 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 3)
!1584 = !DILocation(line: 221, column: 14, scope: !1585)
!1585 = distinct !DILexicalBlock(scope: !1549, file: !1, line: 221, column: 5)
!1586 = !DILocation(line: 221, column: 12, scope: !1585)
!1587 = !DILocation(line: 221, column: 10, scope: !1585)
!1588 = !DILocation(line: 221, column: 19, scope: !1589)
!1589 = !DILexicalBlockFile(scope: !1590, file: !1, discriminator: 1)
!1590 = distinct !DILexicalBlock(scope: !1585, file: !1, line: 221, column: 5)
!1591 = !DILocation(line: 221, column: 23, scope: !1589)
!1592 = !DILocation(line: 221, column: 29, scope: !1589)
!1593 = !DILocation(line: 221, column: 27, scope: !1589)
!1594 = !DILocation(line: 221, column: 21, scope: !1589)
!1595 = !DILocation(line: 221, column: 5, scope: !1589)
!1596 = !DILocation(line: 222, column: 44, scope: !1597)
!1597 = distinct !DILexicalBlock(scope: !1590, file: !1, line: 221, column: 61)
!1598 = !DILocation(line: 222, column: 11, scope: !1597)
!1599 = !DILocation(line: 222, column: 9, scope: !1597)
!1600 = !DILocation(line: 224, column: 14, scope: !1597)
!1601 = !DILocation(line: 225, column: 11, scope: !1602)
!1602 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 225, column: 11)
!1603 = !DILocation(line: 225, column: 14, scope: !1602)
!1604 = !DILocation(line: 225, column: 19, scope: !1602)
!1605 = !DILocation(line: 225, column: 11, scope: !1597)
!1606 = !DILocation(line: 226, column: 16, scope: !1602)
!1607 = !DILocation(line: 226, column: 9, scope: !1602)
!1608 = !DILocation(line: 227, column: 11, scope: !1609)
!1609 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 227, column: 11)
!1610 = !DILocation(line: 227, column: 14, scope: !1609)
!1611 = !DILocation(line: 227, column: 19, scope: !1609)
!1612 = !DILocation(line: 227, column: 11, scope: !1597)
!1613 = !DILocation(line: 228, column: 16, scope: !1609)
!1614 = !DILocation(line: 228, column: 9, scope: !1609)
!1615 = !DILocation(line: 230, column: 24, scope: !1597)
!1616 = !DILocation(line: 230, column: 30, scope: !1597)
!1617 = !DILocation(line: 230, column: 33, scope: !1597)
!1618 = !DILocation(line: 230, column: 11, scope: !1597)
!1619 = !DILocation(line: 230, column: 9, scope: !1597)
!1620 = !DILocation(line: 231, column: 11, scope: !1621)
!1621 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 231, column: 11)
!1622 = !DILocation(line: 231, column: 13, scope: !1621)
!1623 = !DILocation(line: 231, column: 11, scope: !1597)
!1624 = !DILocation(line: 232, column: 9, scope: !1621)
!1625 = !DILocation(line: 238, column: 14, scope: !1597)
!1626 = !DILocation(line: 238, column: 17, scope: !1597)
!1627 = !DILocation(line: 238, column: 38, scope: !1628)
!1628 = !DILexicalBlockFile(scope: !1597, file: !1, discriminator: 1)
!1629 = !DILocation(line: 238, column: 40, scope: !1628)
!1630 = !DILocation(line: 238, column: 23, scope: !1628)
!1631 = !DILocation(line: 238, column: 14, scope: !1628)
!1632 = !DILocation(line: 238, column: 62, scope: !1633)
!1633 = !DILexicalBlockFile(scope: !1597, file: !1, discriminator: 2)
!1634 = !DILocation(line: 238, column: 65, scope: !1633)
!1635 = !DILocation(line: 238, column: 47, scope: !1633)
!1636 = !DILocation(line: 238, column: 14, scope: !1633)
!1637 = !DILocation(line: 238, column: 14, scope: !1638)
!1638 = !DILexicalBlockFile(scope: !1597, file: !1, discriminator: 3)
!1639 = !DILocation(line: 238, column: 12, scope: !1638)
!1640 = !DILocation(line: 251, column: 7, scope: !1597)
!1641 = !DILocation(line: 251, column: 10, scope: !1597)
!1642 = !DILocation(line: 251, column: 20, scope: !1597)
!1643 = !DILocation(line: 252, column: 7, scope: !1597)
!1644 = !DILocation(line: 252, column: 7, scope: !1645)
!1645 = !DILexicalBlockFile(scope: !1646, file: !1, discriminator: 1)
!1646 = distinct !DILexicalBlock(scope: !1647, file: !1, line: 252, column: 7)
!1647 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 252, column: 7)
!1648 = !DILocation(line: 252, column: 7, scope: !1649)
!1649 = !DILexicalBlockFile(scope: !1646, file: !1, discriminator: 2)
!1650 = !DILocation(line: 252, column: 7, scope: !1651)
!1651 = !DILexicalBlockFile(scope: !1652, file: !1, discriminator: 3)
!1652 = distinct !DILexicalBlock(scope: !1646, file: !1, line: 252, column: 7)
!1653 = !DILocation(line: 252, column: 7, scope: !1654)
!1654 = !DILexicalBlockFile(scope: !1652, file: !1, discriminator: 4)
!1655 = !DILocalVariable(name: "q", scope: !1656, file: !1, line: 252, type: !40)
!1656 = distinct !DILexicalBlock(scope: !1646, file: !1, line: 252, column: 7)
!1657 = !DILocation(line: 252, column: 7, scope: !1656)
!1658 = !DILocation(line: 252, column: 7, scope: !1659)
!1659 = !DILexicalBlockFile(scope: !1656, file: !1, discriminator: 5)
!1660 = !DILocation(line: 252, column: 7, scope: !1661)
!1661 = !DILexicalBlockFile(scope: !1662, file: !1, discriminator: 6)
!1662 = distinct !DILexicalBlock(scope: !1656, file: !1, line: 252, column: 7)
!1663 = !DILocation(line: 252, column: 7, scope: !1664)
!1664 = !DILexicalBlockFile(scope: !1647, file: !1, discriminator: 7)
!1665 = !DILocation(line: 253, column: 7, scope: !1597)
!1666 = !DILocation(line: 253, column: 15, scope: !1628)
!1667 = !DILocation(line: 253, column: 14, scope: !1628)
!1668 = !DILocation(line: 253, column: 7, scope: !1628)
!1669 = !DILocation(line: 254, column: 13, scope: !1670)
!1670 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 253, column: 36)
!1671 = !DILocation(line: 254, column: 11, scope: !1670)
!1672 = !DILocation(line: 255, column: 13, scope: !1670)
!1673 = !DILocation(line: 255, column: 11, scope: !1670)
!1674 = !DILocation(line: 257, column: 9, scope: !1670)
!1675 = !DILocation(line: 257, column: 9, scope: !1676)
!1676 = !DILexicalBlockFile(scope: !1677, file: !1, discriminator: 1)
!1677 = distinct !DILexicalBlock(scope: !1670, file: !1, line: 257, column: 9)
!1678 = !DILocation(line: 258, column: 9, scope: !1670)
!1679 = !DILocation(line: 258, column: 9, scope: !1680)
!1680 = !DILexicalBlockFile(scope: !1681, file: !1, discriminator: 1)
!1681 = distinct !DILexicalBlock(scope: !1670, file: !1, line: 258, column: 9)
!1682 = !DILocation(line: 260, column: 9, scope: !1670)
!1683 = !DILocation(line: 260, column: 12, scope: !1670)
!1684 = !DILocation(line: 260, column: 15, scope: !1670)
!1685 = !DILocation(line: 260, column: 18, scope: !1670)
!1686 = !DILocation(line: 260, column: 24, scope: !1670)
!1687 = !DILocation(line: 253, column: 7, scope: !1633)
!1688 = !DILocation(line: 263, column: 7, scope: !1597)
!1689 = !DILocation(line: 263, column: 10, scope: !1597)
!1690 = !DILocation(line: 263, column: 20, scope: !1597)
!1691 = !DILocation(line: 264, column: 31, scope: !1597)
!1692 = !DILocation(line: 264, column: 34, scope: !1597)
!1693 = !DILocation(line: 264, column: 7, scope: !1597)
!1694 = !DILocation(line: 265, column: 5, scope: !1597)
!1695 = !DILocation(line: 221, column: 53, scope: !1696)
!1696 = !DILexicalBlockFile(scope: !1590, file: !1, discriminator: 2)
!1697 = !DILocation(line: 221, column: 56, scope: !1696)
!1698 = !DILocation(line: 221, column: 51, scope: !1696)
!1699 = !DILocation(line: 221, column: 37, scope: !1696)
!1700 = !DILocation(line: 221, column: 5, scope: !1696)
!1701 = !DILocation(line: 208, column: 3, scope: !1702)
!1702 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 1)
!1703 = !DILocation(line: 267, column: 1, scope: !344)
!1704 = !DILocalVariable(name: "path", arg: 1, scope: !347, file: !348, line: 312, type: !291)
!1705 = !DILocation(line: 312, column: 1, scope: !347)
!1706 = !DILocalVariable(name: "s", scope: !347, file: !348, line: 313, type: !64)
!1707 = !DILocation(line: 313, column: 9, scope: !347)
!1708 = !DILocation(line: 315, column: 15, scope: !347)
!1709 = !DILocation(line: 315, column: 7, scope: !347)
!1710 = !DILocation(line: 315, column: 5, scope: !347)
!1711 = !DILocation(line: 316, column: 7, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !347, file: !348, line: 316, column: 7)
!1713 = !DILocation(line: 316, column: 9, scope: !1712)
!1714 = !DILocation(line: 316, column: 7, scope: !347)
!1715 = !DILocation(line: 317, column: 20, scope: !1712)
!1716 = !DILocation(line: 317, column: 5, scope: !1712)
!1717 = !DILocation(line: 319, column: 10, scope: !347)
!1718 = !DILocation(line: 319, column: 12, scope: !347)
!1719 = !DILocation(line: 319, column: 3, scope: !347)
!1720 = !DILocation(line: 320, column: 1, scope: !347)
!1721 = !DILocalVariable(name: "head", arg: 1, scope: !354, file: !1, line: 57, type: !46)
!1722 = !DILocation(line: 57, column: 1, scope: !354)
!1723 = !DILocalVariable(name: "elm", arg: 2, scope: !354, file: !1, line: 57, type: !50)
!1724 = !DILocalVariable(name: "tmp", scope: !354, file: !1, line: 57, type: !50)
!1725 = !DILocalVariable(name: "comp", scope: !354, file: !1, line: 57, type: !60)
!1726 = !DILocation(line: 57, column: 1, scope: !1727)
!1727 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 242)
!1728 = !DILocation(line: 57, column: 1, scope: !1729)
!1729 = !DILexicalBlockFile(scope: !1730, file: !1, discriminator: 243)
!1730 = distinct !DILexicalBlock(scope: !354, file: !1, line: 57, column: 1)
!1731 = !DILocation(line: 57, column: 1, scope: !1732)
!1732 = !DILexicalBlockFile(scope: !1733, file: !1, discriminator: 244)
!1733 = distinct !DILexicalBlock(scope: !1730, file: !1, line: 57, column: 1)
!1734 = !DILocation(line: 57, column: 1, scope: !1735)
!1735 = !DILexicalBlockFile(scope: !1736, file: !1, discriminator: 245)
!1736 = distinct !DILexicalBlock(scope: !1733, file: !1, line: 57, column: 1)
!1737 = !DILocation(line: 57, column: 1, scope: !1738)
!1738 = !DILexicalBlockFile(scope: !1736, file: !1, discriminator: 246)
!1739 = !DILocation(line: 57, column: 1, scope: !1740)
!1740 = !DILexicalBlockFile(scope: !1736, file: !1, discriminator: 247)
!1741 = !DILocation(line: 57, column: 1, scope: !1742)
!1742 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 248)
!1743 = !DILocation(line: 57, column: 1, scope: !1744)
!1744 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 249)
!1745 = !DILocation(line: 57, column: 1, scope: !1746)
!1746 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 250)
!1747 = !DILocalVariable(name: "a", arg: 1, scope: !355, file: !1, line: 49, type: !358)
!1748 = !DILocation(line: 49, column: 56, scope: !355)
!1749 = !DILocalVariable(name: "b", arg: 2, scope: !355, file: !1, line: 50, type: !358)
!1750 = !DILocation(line: 50, column: 56, scope: !355)
!1751 = !DILocation(line: 51, column: 7, scope: !1752)
!1752 = distinct !DILexicalBlock(scope: !355, file: !1, line: 51, column: 7)
!1753 = !DILocation(line: 51, column: 10, scope: !1752)
!1754 = !DILocation(line: 51, column: 15, scope: !1752)
!1755 = !DILocation(line: 51, column: 18, scope: !1752)
!1756 = !DILocation(line: 51, column: 13, scope: !1752)
!1757 = !DILocation(line: 51, column: 7, scope: !355)
!1758 = !DILocation(line: 51, column: 22, scope: !1759)
!1759 = !DILexicalBlockFile(scope: !1752, file: !1, discriminator: 1)
!1760 = !DILocation(line: 52, column: 7, scope: !1761)
!1761 = distinct !DILexicalBlock(scope: !355, file: !1, line: 52, column: 7)
!1762 = !DILocation(line: 52, column: 10, scope: !1761)
!1763 = !DILocation(line: 52, column: 15, scope: !1761)
!1764 = !DILocation(line: 52, column: 18, scope: !1761)
!1765 = !DILocation(line: 52, column: 13, scope: !1761)
!1766 = !DILocation(line: 52, column: 7, scope: !355)
!1767 = !DILocation(line: 52, column: 22, scope: !1768)
!1768 = !DILexicalBlockFile(scope: !1761, file: !1, discriminator: 1)
!1769 = !DILocation(line: 53, column: 3, scope: !355)
!1770 = !DILocation(line: 54, column: 1, scope: !355)
!1771 = !DILocalVariable(name: "head", arg: 1, scope: !361, file: !1, line: 57, type: !46)
!1772 = !DILocation(line: 57, column: 1, scope: !361)
!1773 = !DILocalVariable(name: "elm", arg: 2, scope: !361, file: !1, line: 57, type: !50)
!1774 = !DILocalVariable(name: "parent", scope: !361, file: !1, line: 57, type: !50)
!1775 = !DILocalVariable(name: "gparent", scope: !361, file: !1, line: 57, type: !50)
!1776 = !DILocalVariable(name: "tmp", scope: !361, file: !1, line: 57, type: !50)
!1777 = !DILocation(line: 57, column: 1, scope: !1778)
!1778 = !DILexicalBlockFile(scope: !361, file: !1, discriminator: 251)
!1779 = !DILocation(line: 57, column: 1, scope: !1780)
!1780 = !DILexicalBlockFile(scope: !361, file: !1, discriminator: 252)
!1781 = !DILocation(line: 57, column: 1, scope: !1782)
!1782 = !DILexicalBlockFile(scope: !361, file: !1, discriminator: 253)
!1783 = !DILocation(line: 57, column: 1, scope: !1784)
!1784 = !DILexicalBlockFile(scope: !1785, file: !1, discriminator: 254)
!1785 = distinct !DILexicalBlock(scope: !361, file: !1, line: 57, column: 1)
!1786 = !DILocation(line: 57, column: 1, scope: !1787)
!1787 = !DILexicalBlockFile(scope: !1788, file: !1, discriminator: 255)
!1788 = distinct !DILexicalBlock(scope: !1789, file: !1, line: 57, column: 1)
!1789 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 57, column: 1)
!1790 = !DILocation(line: 57, column: 1, scope: !1791)
!1791 = !DILexicalBlockFile(scope: !1792, file: !1, discriminator: 256)
!1792 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 57, column: 1)
!1793 = !DILocation(line: 57, column: 1, scope: !1794)
!1794 = !DILexicalBlockFile(scope: !1795, file: !1, discriminator: 257)
!1795 = distinct !DILexicalBlock(scope: !1792, file: !1, line: 57, column: 1)
!1796 = !DILocation(line: 57, column: 1, scope: !1797)
!1797 = !DILexicalBlockFile(scope: !1798, file: !1, discriminator: 258)
!1798 = distinct !DILexicalBlock(scope: !1795, file: !1, line: 57, column: 1)
!1799 = !DILocation(line: 57, column: 1, scope: !1800)
!1800 = !DILexicalBlockFile(scope: !1795, file: !1, discriminator: 259)
!1801 = !DILocation(line: 57, column: 1, scope: !1802)
!1802 = !DILexicalBlockFile(scope: !1803, file: !1, discriminator: 260)
!1803 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 57, column: 1)
!1804 = !DILocation(line: 57, column: 1, scope: !1805)
!1805 = !DILexicalBlockFile(scope: !1806, file: !1, discriminator: 261)
!1806 = distinct !DILexicalBlock(scope: !1803, file: !1, line: 57, column: 1)
!1807 = !DILocation(line: 57, column: 1, scope: !1808)
!1808 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 262)
!1809 = distinct !DILexicalBlock(scope: !1806, file: !1, line: 57, column: 1)
!1810 = !DILocation(line: 57, column: 1, scope: !1811)
!1811 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 263)
!1812 = distinct !DILexicalBlock(scope: !1813, file: !1, line: 57, column: 1)
!1813 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 57, column: 1)
!1814 = !DILocation(line: 57, column: 1, scope: !1815)
!1815 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 264)
!1816 = !DILocation(line: 57, column: 1, scope: !1817)
!1817 = !DILexicalBlockFile(scope: !1818, file: !1, discriminator: 265)
!1818 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 57, column: 1)
!1819 = !DILocation(line: 57, column: 1, scope: !1820)
!1820 = !DILexicalBlockFile(scope: !1821, file: !1, discriminator: 266)
!1821 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 57, column: 1)
!1822 = !DILocation(line: 57, column: 1, scope: !1823)
!1823 = !DILexicalBlockFile(scope: !1824, file: !1, discriminator: 267)
!1824 = distinct !DILexicalBlock(scope: !1825, file: !1, line: 57, column: 1)
!1825 = distinct !DILexicalBlock(scope: !1821, file: !1, line: 57, column: 1)
!1826 = !DILocation(line: 57, column: 1, scope: !1827)
!1827 = !DILexicalBlockFile(scope: !1824, file: !1, discriminator: 268)
!1828 = !DILocation(line: 57, column: 1, scope: !1829)
!1829 = !DILexicalBlockFile(scope: !1824, file: !1, discriminator: 269)
!1830 = !DILocation(line: 57, column: 1, scope: !1831)
!1831 = !DILexicalBlockFile(scope: !1825, file: !1, discriminator: 270)
!1832 = !DILocation(line: 57, column: 1, scope: !1833)
!1833 = !DILexicalBlockFile(scope: !1821, file: !1, discriminator: 271)
!1834 = !DILocation(line: 57, column: 1, scope: !1835)
!1835 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 272)
!1836 = !DILocation(line: 57, column: 1, scope: !1837)
!1837 = !DILexicalBlockFile(scope: !1838, file: !1, discriminator: 273)
!1838 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 57, column: 1)
!1839 = !DILocation(line: 57, column: 1, scope: !1840)
!1840 = !DILexicalBlockFile(scope: !1841, file: !1, discriminator: 274)
!1841 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 57, column: 1)
!1842 = !DILocation(line: 57, column: 1, scope: !1843)
!1843 = !DILexicalBlockFile(scope: !1841, file: !1, discriminator: 275)
!1844 = !DILocation(line: 57, column: 1, scope: !1845)
!1845 = !DILexicalBlockFile(scope: !1846, file: !1, discriminator: 276)
!1846 = distinct !DILexicalBlock(scope: !1841, file: !1, line: 57, column: 1)
!1847 = !DILocation(line: 57, column: 1, scope: !1848)
!1848 = !DILexicalBlockFile(scope: !1846, file: !1, discriminator: 277)
!1849 = !DILocation(line: 57, column: 1, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 278)
!1851 = !DILocation(line: 57, column: 1, scope: !1852)
!1852 = !DILexicalBlockFile(scope: !1806, file: !1, discriminator: 279)
!1853 = !DILocation(line: 57, column: 1, scope: !1854)
!1854 = !DILexicalBlockFile(scope: !1788, file: !1, discriminator: 280)
!1855 = !DILocation(line: 57, column: 1, scope: !1856)
!1856 = !DILexicalBlockFile(scope: !1857, file: !1, discriminator: 281)
!1857 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 57, column: 1)
!1858 = !DILocation(line: 57, column: 1, scope: !1859)
!1859 = !DILexicalBlockFile(scope: !1788, file: !1, discriminator: 282)
!1860 = !DILocation(line: 57, column: 1, scope: !1861)
!1861 = !DILexicalBlockFile(scope: !1862, file: !1, discriminator: 283)
!1862 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 57, column: 1)
!1863 = !DILocation(line: 57, column: 1, scope: !1864)
!1864 = !DILexicalBlockFile(scope: !1865, file: !1, discriminator: 284)
!1865 = distinct !DILexicalBlock(scope: !1866, file: !1, line: 57, column: 1)
!1866 = distinct !DILexicalBlock(scope: !1862, file: !1, line: 57, column: 1)
!1867 = !DILocation(line: 57, column: 1, scope: !1868)
!1868 = !DILexicalBlockFile(scope: !1862, file: !1, discriminator: 285)
!1869 = !DILocation(line: 57, column: 1, scope: !1870)
!1870 = !DILexicalBlockFile(scope: !1871, file: !1, discriminator: 286)
!1871 = distinct !DILexicalBlock(scope: !1862, file: !1, line: 57, column: 1)
!1872 = !DILocation(line: 57, column: 1, scope: !1873)
!1873 = !DILexicalBlockFile(scope: !1874, file: !1, discriminator: 287)
!1874 = distinct !DILexicalBlock(scope: !1862, file: !1, line: 57, column: 1)
!1875 = !DILocation(line: 57, column: 1, scope: !1876)
!1876 = !DILexicalBlockFile(scope: !1877, file: !1, discriminator: 288)
!1877 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 57, column: 1)
!1878 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 57, column: 1)
!1879 = !DILocation(line: 57, column: 1, scope: !1880)
!1880 = !DILexicalBlockFile(scope: !1877, file: !1, discriminator: 289)
!1881 = !DILocation(line: 57, column: 1, scope: !1882)
!1882 = !DILexicalBlockFile(scope: !1877, file: !1, discriminator: 290)
!1883 = !DILocation(line: 57, column: 1, scope: !1884)
!1884 = !DILexicalBlockFile(scope: !1878, file: !1, discriminator: 291)
!1885 = !DILocation(line: 57, column: 1, scope: !1886)
!1886 = !DILexicalBlockFile(scope: !1874, file: !1, discriminator: 292)
!1887 = !DILocation(line: 57, column: 1, scope: !1888)
!1888 = !DILexicalBlockFile(scope: !1862, file: !1, discriminator: 293)
!1889 = !DILocation(line: 57, column: 1, scope: !1890)
!1890 = !DILexicalBlockFile(scope: !1891, file: !1, discriminator: 294)
!1891 = distinct !DILexicalBlock(scope: !1862, file: !1, line: 57, column: 1)
!1892 = !DILocation(line: 57, column: 1, scope: !1893)
!1893 = !DILexicalBlockFile(scope: !1894, file: !1, discriminator: 295)
!1894 = distinct !DILexicalBlock(scope: !1862, file: !1, line: 57, column: 1)
!1895 = !DILocation(line: 57, column: 1, scope: !1896)
!1896 = !DILexicalBlockFile(scope: !1894, file: !1, discriminator: 296)
!1897 = !DILocation(line: 57, column: 1, scope: !1898)
!1898 = !DILexicalBlockFile(scope: !1899, file: !1, discriminator: 297)
!1899 = distinct !DILexicalBlock(scope: !1894, file: !1, line: 57, column: 1)
!1900 = !DILocation(line: 57, column: 1, scope: !1901)
!1901 = !DILexicalBlockFile(scope: !1899, file: !1, discriminator: 298)
!1902 = !DILocation(line: 57, column: 1, scope: !1903)
!1903 = !DILexicalBlockFile(scope: !1862, file: !1, discriminator: 299)
!1904 = !DILocation(line: 57, column: 1, scope: !1905)
!1905 = !DILexicalBlockFile(scope: !1788, file: !1, discriminator: 300)
!1906 = !DILocation(line: 57, column: 1, scope: !1907)
!1907 = !DILexicalBlockFile(scope: !1908, file: !1, discriminator: 301)
!1908 = distinct !DILexicalBlock(scope: !1789, file: !1, line: 57, column: 1)
!1909 = !DILocation(line: 57, column: 1, scope: !1910)
!1910 = !DILexicalBlockFile(scope: !1911, file: !1, discriminator: 302)
!1911 = distinct !DILexicalBlock(scope: !1908, file: !1, line: 57, column: 1)
!1912 = !DILocation(line: 57, column: 1, scope: !1913)
!1913 = !DILexicalBlockFile(scope: !1914, file: !1, discriminator: 303)
!1914 = distinct !DILexicalBlock(scope: !1911, file: !1, line: 57, column: 1)
!1915 = !DILocation(line: 57, column: 1, scope: !1916)
!1916 = !DILexicalBlockFile(scope: !1917, file: !1, discriminator: 304)
!1917 = distinct !DILexicalBlock(scope: !1914, file: !1, line: 57, column: 1)
!1918 = !DILocation(line: 57, column: 1, scope: !1919)
!1919 = !DILexicalBlockFile(scope: !1914, file: !1, discriminator: 305)
!1920 = !DILocation(line: 57, column: 1, scope: !1921)
!1921 = !DILexicalBlockFile(scope: !1922, file: !1, discriminator: 306)
!1922 = distinct !DILexicalBlock(scope: !1908, file: !1, line: 57, column: 1)
!1923 = !DILocation(line: 57, column: 1, scope: !1924)
!1924 = !DILexicalBlockFile(scope: !1925, file: !1, discriminator: 307)
!1925 = distinct !DILexicalBlock(scope: !1922, file: !1, line: 57, column: 1)
!1926 = !DILocation(line: 57, column: 1, scope: !1927)
!1927 = !DILexicalBlockFile(scope: !1928, file: !1, discriminator: 308)
!1928 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 57, column: 1)
!1929 = !DILocation(line: 57, column: 1, scope: !1930)
!1930 = !DILexicalBlockFile(scope: !1931, file: !1, discriminator: 309)
!1931 = distinct !DILexicalBlock(scope: !1932, file: !1, line: 57, column: 1)
!1932 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 57, column: 1)
!1933 = !DILocation(line: 57, column: 1, scope: !1934)
!1934 = !DILexicalBlockFile(scope: !1928, file: !1, discriminator: 310)
!1935 = !DILocation(line: 57, column: 1, scope: !1936)
!1936 = !DILexicalBlockFile(scope: !1937, file: !1, discriminator: 311)
!1937 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 57, column: 1)
!1938 = !DILocation(line: 57, column: 1, scope: !1939)
!1939 = !DILexicalBlockFile(scope: !1940, file: !1, discriminator: 312)
!1940 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 57, column: 1)
!1941 = !DILocation(line: 57, column: 1, scope: !1942)
!1942 = !DILexicalBlockFile(scope: !1943, file: !1, discriminator: 313)
!1943 = distinct !DILexicalBlock(scope: !1944, file: !1, line: 57, column: 1)
!1944 = distinct !DILexicalBlock(scope: !1940, file: !1, line: 57, column: 1)
!1945 = !DILocation(line: 57, column: 1, scope: !1946)
!1946 = !DILexicalBlockFile(scope: !1943, file: !1, discriminator: 314)
!1947 = !DILocation(line: 57, column: 1, scope: !1948)
!1948 = !DILexicalBlockFile(scope: !1943, file: !1, discriminator: 315)
!1949 = !DILocation(line: 57, column: 1, scope: !1950)
!1950 = !DILexicalBlockFile(scope: !1944, file: !1, discriminator: 316)
!1951 = !DILocation(line: 57, column: 1, scope: !1952)
!1952 = !DILexicalBlockFile(scope: !1940, file: !1, discriminator: 317)
!1953 = !DILocation(line: 57, column: 1, scope: !1954)
!1954 = !DILexicalBlockFile(scope: !1928, file: !1, discriminator: 318)
!1955 = !DILocation(line: 57, column: 1, scope: !1956)
!1956 = !DILexicalBlockFile(scope: !1957, file: !1, discriminator: 319)
!1957 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 57, column: 1)
!1958 = !DILocation(line: 57, column: 1, scope: !1959)
!1959 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 320)
!1960 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 57, column: 1)
!1961 = !DILocation(line: 57, column: 1, scope: !1962)
!1962 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 321)
!1963 = !DILocation(line: 57, column: 1, scope: !1964)
!1964 = !DILexicalBlockFile(scope: !1965, file: !1, discriminator: 322)
!1965 = distinct !DILexicalBlock(scope: !1960, file: !1, line: 57, column: 1)
!1966 = !DILocation(line: 57, column: 1, scope: !1967)
!1967 = !DILexicalBlockFile(scope: !1965, file: !1, discriminator: 323)
!1968 = !DILocation(line: 57, column: 1, scope: !1969)
!1969 = !DILexicalBlockFile(scope: !1928, file: !1, discriminator: 324)
!1970 = !DILocation(line: 57, column: 1, scope: !1971)
!1971 = !DILexicalBlockFile(scope: !1925, file: !1, discriminator: 325)
!1972 = !DILocation(line: 57, column: 1, scope: !1973)
!1973 = !DILexicalBlockFile(scope: !1908, file: !1, discriminator: 326)
!1974 = !DILocation(line: 57, column: 1, scope: !1975)
!1975 = !DILexicalBlockFile(scope: !1976, file: !1, discriminator: 327)
!1976 = distinct !DILexicalBlock(scope: !1908, file: !1, line: 57, column: 1)
!1977 = !DILocation(line: 57, column: 1, scope: !1978)
!1978 = !DILexicalBlockFile(scope: !1908, file: !1, discriminator: 328)
!1979 = !DILocation(line: 57, column: 1, scope: !1980)
!1980 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 329)
!1981 = distinct !DILexicalBlock(scope: !1908, file: !1, line: 57, column: 1)
!1982 = !DILocation(line: 57, column: 1, scope: !1983)
!1983 = !DILexicalBlockFile(scope: !1984, file: !1, discriminator: 330)
!1984 = distinct !DILexicalBlock(scope: !1985, file: !1, line: 57, column: 1)
!1985 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 57, column: 1)
!1986 = !DILocation(line: 57, column: 1, scope: !1987)
!1987 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 331)
!1988 = !DILocation(line: 57, column: 1, scope: !1989)
!1989 = !DILexicalBlockFile(scope: !1990, file: !1, discriminator: 332)
!1990 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 57, column: 1)
!1991 = !DILocation(line: 57, column: 1, scope: !1992)
!1992 = !DILexicalBlockFile(scope: !1993, file: !1, discriminator: 333)
!1993 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 57, column: 1)
!1994 = !DILocation(line: 57, column: 1, scope: !1995)
!1995 = !DILexicalBlockFile(scope: !1996, file: !1, discriminator: 334)
!1996 = distinct !DILexicalBlock(scope: !1997, file: !1, line: 57, column: 1)
!1997 = distinct !DILexicalBlock(scope: !1993, file: !1, line: 57, column: 1)
!1998 = !DILocation(line: 57, column: 1, scope: !1999)
!1999 = !DILexicalBlockFile(scope: !1996, file: !1, discriminator: 335)
!2000 = !DILocation(line: 57, column: 1, scope: !2001)
!2001 = !DILexicalBlockFile(scope: !1996, file: !1, discriminator: 336)
!2002 = !DILocation(line: 57, column: 1, scope: !2003)
!2003 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 337)
!2004 = !DILocation(line: 57, column: 1, scope: !2005)
!2005 = !DILexicalBlockFile(scope: !1993, file: !1, discriminator: 338)
!2006 = !DILocation(line: 57, column: 1, scope: !2007)
!2007 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 339)
!2008 = !DILocation(line: 57, column: 1, scope: !2009)
!2009 = !DILexicalBlockFile(scope: !2010, file: !1, discriminator: 340)
!2010 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 57, column: 1)
!2011 = !DILocation(line: 57, column: 1, scope: !2012)
!2012 = !DILexicalBlockFile(scope: !2013, file: !1, discriminator: 341)
!2013 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 57, column: 1)
!2014 = !DILocation(line: 57, column: 1, scope: !2015)
!2015 = !DILexicalBlockFile(scope: !2013, file: !1, discriminator: 342)
!2016 = !DILocation(line: 57, column: 1, scope: !2017)
!2017 = !DILexicalBlockFile(scope: !2018, file: !1, discriminator: 343)
!2018 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 57, column: 1)
!2019 = !DILocation(line: 57, column: 1, scope: !2020)
!2020 = !DILexicalBlockFile(scope: !2018, file: !1, discriminator: 344)
!2021 = !DILocation(line: 57, column: 1, scope: !2022)
!2022 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 345)
!2023 = !DILocation(line: 57, column: 1, scope: !2024)
!2024 = !DILexicalBlockFile(scope: !361, file: !1, discriminator: 346)
!2025 = !DILocation(line: 57, column: 1, scope: !2026)
!2026 = !DILexicalBlockFile(scope: !361, file: !1, discriminator: 347)
