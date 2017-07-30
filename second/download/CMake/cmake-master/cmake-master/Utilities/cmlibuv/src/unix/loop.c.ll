; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/loop.c'
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
%struct.heap = type { %struct.heap_node*, i32 }
%struct.heap_node = type { %struct.heap_node*, %struct.heap_node*, %struct.heap_node* }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [34 x i8] c"thread pool work queue not empty!\00", align 1
@.str.1 = private unnamed_addr constant [123 x i8] c"((const QUEUE *) (&loop->wq) == (const QUEUE *) (*(QUEUE **) &((*(&loop->wq))[0]))) && \22thread pool work queue not empty!\22\00", align 1
@.str.2 = private unnamed_addr constant [68 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/loop.c\00", align 1
@__PRETTY_FUNCTION__.uv__loop_close = private unnamed_addr constant [33 x i8] c"void uv__loop_close(uv_loop_t *)\00", align 1
@.str.3 = private unnamed_addr constant [114 x i8] c"!(((const QUEUE *) (&(loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(loop)->active_reqs))[0]))) == 0)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_loop_init(%struct.uv_loop_s* %loop) #0 !dbg !148 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %saved_data = alloca i8*, align 8
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !375, metadata !376), !dbg !377
  call void @llvm.dbg.declare(metadata i8** %saved_data, metadata !378, metadata !376), !dbg !379
  call void @llvm.dbg.declare(metadata i32* %err, metadata !380, metadata !376), !dbg !381
  call void @uv__signal_global_once_init(), !dbg !382
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !383
  %data = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 0, !dbg !384
  %1 = load i8*, i8** %data, align 8, !dbg !384
  store i8* %1, i8** %saved_data, align 8, !dbg !385
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !386
  %3 = bitcast %struct.uv_loop_s* %2 to i8*, !dbg !387
  call void @llvm.memset.p0i8.i64(i8* %3, i8 0, i64 848, i32 8, i1 false), !dbg !387
  %4 = load i8*, i8** %saved_data, align 8, !dbg !388
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !389
  %data1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 0, !dbg !390
  store i8* %4, i8** %data1, align 8, !dbg !391
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !392
  %timer_heap = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 25, !dbg !393
  %7 = bitcast %struct.anon.1* %timer_heap to %struct.heap*, !dbg !394
  call void @heap_init(%struct.heap* %7), !dbg !395
  br label %do.body, !dbg !396

do.body:                                          ; preds = %entry
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !397
  %wq = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 12, !dbg !397
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !397
  %wq2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 12, !dbg !397
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq2, i64 0, i64 0, !dbg !397
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !397
  store [2 x i8*]* %wq, [2 x i8*]** %10, align 8, !dbg !397
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !397
  %wq3 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 12, !dbg !397
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !397
  %wq4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 12, !dbg !397
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq4, i64 0, i64 1, !dbg !397
  %13 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !397
  store [2 x i8*]* %wq3, [2 x i8*]** %13, align 8, !dbg !397
  br label %do.end, !dbg !397

do.end:                                           ; preds = %do.body
  br label %do.body6, !dbg !400

do.body6:                                         ; preds = %do.end
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !401
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 3, !dbg !401
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !401
  %active_reqs7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %15, i32 0, i32 3, !dbg !401
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs7, i64 0, i64 0, !dbg !401
  %16 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !401
  store [2 x i8*]* %active_reqs, [2 x i8*]** %16, align 8, !dbg !401
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !401
  %active_reqs9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !401
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !401
  %active_reqs10 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 3, !dbg !401
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs10, i64 0, i64 1, !dbg !401
  %19 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !401
  store [2 x i8*]* %active_reqs9, [2 x i8*]** %19, align 8, !dbg !401
  br label %do.end12, !dbg !401

do.end12:                                         ; preds = %do.body6
  br label %do.body13, !dbg !404

do.body13:                                        ; preds = %do.end12
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !405
  %idle_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 20, !dbg !405
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !405
  %idle_handles14 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 20, !dbg !405
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles14, i64 0, i64 0, !dbg !405
  %22 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !405
  store [2 x i8*]* %idle_handles, [2 x i8*]** %22, align 8, !dbg !405
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !405
  %idle_handles16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 20, !dbg !405
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !405
  %idle_handles17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 20, !dbg !405
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles17, i64 0, i64 1, !dbg !405
  %25 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !405
  store [2 x i8*]* %idle_handles16, [2 x i8*]** %25, align 8, !dbg !405
  br label %do.end19, !dbg !405

do.end19:                                         ; preds = %do.body13
  br label %do.body20, !dbg !408

do.body20:                                        ; preds = %do.end19
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !409
  %async_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 21, !dbg !409
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !409
  %async_handles21 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 21, !dbg !409
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles21, i64 0, i64 0, !dbg !409
  %28 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !409
  store [2 x i8*]* %async_handles, [2 x i8*]** %28, align 8, !dbg !409
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !409
  %async_handles23 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %29, i32 0, i32 21, !dbg !409
  %30 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !409
  %async_handles24 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %30, i32 0, i32 21, !dbg !409
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles24, i64 0, i64 1, !dbg !409
  %31 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !409
  store [2 x i8*]* %async_handles23, [2 x i8*]** %31, align 8, !dbg !409
  br label %do.end26, !dbg !409

do.end26:                                         ; preds = %do.body20
  br label %do.body27, !dbg !412

do.body27:                                        ; preds = %do.end26
  %32 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !413
  %check_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %32, i32 0, i32 19, !dbg !413
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !413
  %check_handles28 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 19, !dbg !413
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles28, i64 0, i64 0, !dbg !413
  %34 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !413
  store [2 x i8*]* %check_handles, [2 x i8*]** %34, align 8, !dbg !413
  %35 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !413
  %check_handles30 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %35, i32 0, i32 19, !dbg !413
  %36 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !413
  %check_handles31 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %36, i32 0, i32 19, !dbg !413
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles31, i64 0, i64 1, !dbg !413
  %37 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !413
  store [2 x i8*]* %check_handles30, [2 x i8*]** %37, align 8, !dbg !413
  br label %do.end33, !dbg !413

do.end33:                                         ; preds = %do.body27
  br label %do.body34, !dbg !416

do.body34:                                        ; preds = %do.end33
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !417
  %prepare_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 18, !dbg !417
  %39 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !417
  %prepare_handles35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %39, i32 0, i32 18, !dbg !417
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles35, i64 0, i64 0, !dbg !417
  %40 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !417
  store [2 x i8*]* %prepare_handles, [2 x i8*]** %40, align 8, !dbg !417
  %41 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !417
  %prepare_handles37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %41, i32 0, i32 18, !dbg !417
  %42 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !417
  %prepare_handles38 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %42, i32 0, i32 18, !dbg !417
  %arrayidx39 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles38, i64 0, i64 1, !dbg !417
  %43 = bitcast i8** %arrayidx39 to [2 x i8*]**, !dbg !417
  store [2 x i8*]* %prepare_handles37, [2 x i8*]** %43, align 8, !dbg !417
  br label %do.end40, !dbg !417

do.end40:                                         ; preds = %do.body34
  br label %do.body41, !dbg !420

do.body41:                                        ; preds = %do.end40
  %44 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !421
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %44, i32 0, i32 2, !dbg !421
  %45 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !421
  %handle_queue42 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %45, i32 0, i32 2, !dbg !421
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue42, i64 0, i64 0, !dbg !421
  %46 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !421
  store [2 x i8*]* %handle_queue, [2 x i8*]** %46, align 8, !dbg !421
  %47 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !421
  %handle_queue44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %47, i32 0, i32 2, !dbg !421
  %48 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !421
  %handle_queue45 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %48, i32 0, i32 2, !dbg !421
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue45, i64 0, i64 1, !dbg !421
  %49 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !421
  store [2 x i8*]* %handle_queue44, [2 x i8*]** %49, align 8, !dbg !421
  br label %do.end47, !dbg !421

do.end47:                                         ; preds = %do.body41
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !424
  %nfds = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %50, i32 0, i32 11, !dbg !425
  store i32 0, i32* %nfds, align 4, !dbg !426
  %51 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !427
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %51, i32 0, i32 9, !dbg !428
  store %struct.uv__io_s** null, %struct.uv__io_s*** %watchers, align 8, !dbg !429
  %52 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !430
  %nwatchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %52, i32 0, i32 10, !dbg !431
  store i32 0, i32* %nwatchers, align 8, !dbg !432
  br label %do.body48, !dbg !433

do.body48:                                        ; preds = %do.end47
  %53 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !434
  %pending_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %53, i32 0, i32 7, !dbg !434
  %54 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !434
  %pending_queue49 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %54, i32 0, i32 7, !dbg !434
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue49, i64 0, i64 0, !dbg !434
  %55 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !434
  store [2 x i8*]* %pending_queue, [2 x i8*]** %55, align 8, !dbg !434
  %56 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !434
  %pending_queue51 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %56, i32 0, i32 7, !dbg !434
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !434
  %pending_queue52 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %57, i32 0, i32 7, !dbg !434
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending_queue52, i64 0, i64 1, !dbg !434
  %58 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !434
  store [2 x i8*]* %pending_queue51, [2 x i8*]** %58, align 8, !dbg !434
  br label %do.end54, !dbg !434

do.end54:                                         ; preds = %do.body48
  br label %do.body55, !dbg !437

do.body55:                                        ; preds = %do.end54
  %59 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !438
  %watcher_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %59, i32 0, i32 8, !dbg !438
  %60 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !438
  %watcher_queue56 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %60, i32 0, i32 8, !dbg !438
  %arrayidx57 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue56, i64 0, i64 0, !dbg !438
  %61 = bitcast i8** %arrayidx57 to [2 x i8*]**, !dbg !438
  store [2 x i8*]* %watcher_queue, [2 x i8*]** %61, align 8, !dbg !438
  %62 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !438
  %watcher_queue58 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %62, i32 0, i32 8, !dbg !438
  %63 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !438
  %watcher_queue59 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %63, i32 0, i32 8, !dbg !438
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue59, i64 0, i64 1, !dbg !438
  %64 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !438
  store [2 x i8*]* %watcher_queue58, [2 x i8*]** %64, align 8, !dbg !438
  br label %do.end61, !dbg !438

do.end61:                                         ; preds = %do.body55
  %65 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !441
  %closing_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %65, i32 0, i32 16, !dbg !442
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %closing_handles, align 8, !dbg !443
  %66 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !444
  call void @uv__update_time(%struct.uv_loop_s* %66), !dbg !445
  %67 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !446
  %async_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %67, i32 0, i32 23, !dbg !447
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher, i32 0, i32 5, !dbg !448
  store i32 -1, i32* %fd, align 8, !dbg !449
  %68 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !450
  %async_wfd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %68, i32 0, i32 24, !dbg !451
  store i32 -1, i32* %async_wfd, align 8, !dbg !452
  %69 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !453
  %signal_pipefd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %69, i32 0, i32 28, !dbg !454
  %arrayidx62 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd, i64 0, i64 0, !dbg !453
  store i32 -1, i32* %arrayidx62, align 8, !dbg !455
  %70 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !456
  %signal_pipefd63 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %70, i32 0, i32 28, !dbg !457
  %arrayidx64 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipefd63, i64 0, i64 1, !dbg !456
  store i32 -1, i32* %arrayidx64, align 4, !dbg !458
  %71 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !459
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %71, i32 0, i32 6, !dbg !460
  store i32 -1, i32* %backend_fd, align 8, !dbg !461
  %72 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !462
  %emfile_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %72, i32 0, i32 31, !dbg !463
  store i32 -1, i32* %emfile_fd, align 8, !dbg !464
  %73 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !465
  %timer_counter = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %73, i32 0, i32 26, !dbg !466
  store i64 0, i64* %timer_counter, align 8, !dbg !467
  %74 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !468
  %stop_flag = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %74, i32 0, i32 4, !dbg !469
  store i32 0, i32* %stop_flag, align 8, !dbg !470
  %75 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !471
  %call = call i32 @uv__platform_loop_init(%struct.uv_loop_s* %75), !dbg !472
  store i32 %call, i32* %err, align 4, !dbg !473
  %76 = load i32, i32* %err, align 4, !dbg !474
  %tobool = icmp ne i32 %76, 0, !dbg !474
  br i1 %tobool, label %if.then, label %if.end, !dbg !476

if.then:                                          ; preds = %do.end61
  %77 = load i32, i32* %err, align 4, !dbg !477
  store i32 %77, i32* %retval, align 4, !dbg !478
  br label %return, !dbg !478

if.end:                                           ; preds = %do.end61
  %78 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !479
  %79 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !480
  %child_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %79, i32 0, i32 30, !dbg !481
  %call65 = call i32 @uv_signal_init(%struct.uv_loop_s* %78, %struct.uv_signal_s* %child_watcher), !dbg !482
  store i32 %call65, i32* %err, align 4, !dbg !483
  %80 = load i32, i32* %err, align 4, !dbg !484
  %tobool66 = icmp ne i32 %80, 0, !dbg !484
  br i1 %tobool66, label %if.then67, label %if.end68, !dbg !486

if.then67:                                        ; preds = %if.end
  br label %fail_signal_init, !dbg !487

if.end68:                                         ; preds = %if.end
  br label %do.body69, !dbg !488

do.body69:                                        ; preds = %if.end68
  %81 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !489
  %child_watcher70 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %81, i32 0, i32 30, !dbg !489
  %flags = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %child_watcher70, i32 0, i32 7, !dbg !489
  %82 = load i32, i32* %flags, align 8, !dbg !489
  %and = and i32 %82, 8192, !dbg !489
  %cmp = icmp eq i32 %and, 0, !dbg !489
  br i1 %cmp, label %if.then71, label %if.end72, !dbg !489

if.then71:                                        ; preds = %do.body69
  br label %do.end92, !dbg !493

if.end72:                                         ; preds = %do.body69
  %83 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !495
  %child_watcher73 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %83, i32 0, i32 30, !dbg !495
  %flags74 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %child_watcher73, i32 0, i32 7, !dbg !495
  %84 = load i32, i32* %flags74, align 8, !dbg !495
  %and75 = and i32 %84, -8193, !dbg !495
  store i32 %and75, i32* %flags74, align 8, !dbg !495
  %85 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !495
  %child_watcher76 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %85, i32 0, i32 30, !dbg !495
  %flags77 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %child_watcher76, i32 0, i32 7, !dbg !495
  %86 = load i32, i32* %flags77, align 8, !dbg !495
  %and78 = and i32 %86, 0, !dbg !495
  %cmp79 = icmp ne i32 %and78, 0, !dbg !495
  br i1 %cmp79, label %if.then80, label %if.end81, !dbg !495

if.then80:                                        ; preds = %if.end72
  br label %do.end92, !dbg !497

if.end81:                                         ; preds = %if.end72
  %87 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !500
  %child_watcher82 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %87, i32 0, i32 30, !dbg !500
  %flags83 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %child_watcher82, i32 0, i32 7, !dbg !500
  %88 = load i32, i32* %flags83, align 8, !dbg !500
  %and84 = and i32 %88, 16384, !dbg !500
  %cmp85 = icmp ne i32 %and84, 0, !dbg !500
  br i1 %cmp85, label %if.then86, label %if.end91, !dbg !500

if.then86:                                        ; preds = %if.end81
  br label %do.body87, !dbg !503

do.body87:                                        ; preds = %if.then86
  %89 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !505
  %child_watcher88 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %89, i32 0, i32 30, !dbg !505
  %loop89 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %child_watcher88, i32 0, i32 1, !dbg !505
  %90 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop89, align 8, !dbg !505
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %90, i32 0, i32 1, !dbg !505
  %91 = load i32, i32* %active_handles, align 8, !dbg !505
  %dec = add i32 %91, -1, !dbg !505
  store i32 %dec, i32* %active_handles, align 8, !dbg !505
  br label %do.end90, !dbg !505

do.end90:                                         ; preds = %do.body87
  br label %if.end91, !dbg !508

if.end91:                                         ; preds = %do.end90, %if.end81
  br label %do.end92, !dbg !510

do.end92:                                         ; preds = %if.end91, %if.then80, %if.then71
  %92 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !512
  %child_watcher93 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %92, i32 0, i32 30, !dbg !513
  %flags94 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %child_watcher93, i32 0, i32 7, !dbg !514
  %93 = load i32, i32* %flags94, align 8, !dbg !515
  %or = or i32 %93, 32768, !dbg !515
  store i32 %or, i32* %flags94, align 8, !dbg !515
  br label %do.body95, !dbg !516

do.body95:                                        ; preds = %do.end92
  %94 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !517
  %process_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %94, i32 0, i32 17, !dbg !517
  %95 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !517
  %process_handles96 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %95, i32 0, i32 17, !dbg !517
  %arrayidx97 = getelementptr inbounds [2 x i8*], [2 x i8*]* %process_handles96, i64 0, i64 0, !dbg !517
  %96 = bitcast i8** %arrayidx97 to [2 x i8*]**, !dbg !517
  store [2 x i8*]* %process_handles, [2 x i8*]** %96, align 8, !dbg !517
  %97 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !517
  %process_handles98 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %97, i32 0, i32 17, !dbg !517
  %98 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !517
  %process_handles99 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %98, i32 0, i32 17, !dbg !517
  %arrayidx100 = getelementptr inbounds [2 x i8*], [2 x i8*]* %process_handles99, i64 0, i64 1, !dbg !517
  %99 = bitcast i8** %arrayidx100 to [2 x i8*]**, !dbg !517
  store [2 x i8*]* %process_handles98, [2 x i8*]** %99, align 8, !dbg !517
  br label %do.end101, !dbg !517

do.end101:                                        ; preds = %do.body95
  %100 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !520
  %cloexec_lock = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %100, i32 0, i32 15, !dbg !521
  %call102 = call i32 @uv_rwlock_init(%union.pthread_rwlock_t* %cloexec_lock), !dbg !522
  store i32 %call102, i32* %err, align 4, !dbg !523
  %101 = load i32, i32* %err, align 4, !dbg !524
  %tobool103 = icmp ne i32 %101, 0, !dbg !524
  br i1 %tobool103, label %if.then104, label %if.end105, !dbg !526

if.then104:                                       ; preds = %do.end101
  br label %fail_rwlock_init, !dbg !527

if.end105:                                        ; preds = %do.end101
  %102 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !528
  %wq_mutex = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %102, i32 0, i32 13, !dbg !529
  %call106 = call i32 @uv_mutex_init(%union.pthread_mutex_t* %wq_mutex), !dbg !530
  store i32 %call106, i32* %err, align 4, !dbg !531
  %103 = load i32, i32* %err, align 4, !dbg !532
  %tobool107 = icmp ne i32 %103, 0, !dbg !532
  br i1 %tobool107, label %if.then108, label %if.end109, !dbg !534

if.then108:                                       ; preds = %if.end105
  br label %fail_mutex_init, !dbg !535

if.end109:                                        ; preds = %if.end105
  %104 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !536
  %105 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !537
  %wq_async = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %105, i32 0, i32 14, !dbg !538
  %call110 = call i32 @uv_async_init(%struct.uv_loop_s* %104, %struct.uv_async_s* %wq_async, void (%struct.uv_async_s*)* @uv__work_done), !dbg !539
  store i32 %call110, i32* %err, align 4, !dbg !540
  %106 = load i32, i32* %err, align 4, !dbg !541
  %tobool111 = icmp ne i32 %106, 0, !dbg !541
  br i1 %tobool111, label %if.then112, label %if.end113, !dbg !543

if.then112:                                       ; preds = %if.end109
  br label %fail_async_init, !dbg !544

if.end113:                                        ; preds = %if.end109
  br label %do.body114, !dbg !545

do.body114:                                       ; preds = %if.end113
  %107 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !546
  %wq_async115 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %107, i32 0, i32 14, !dbg !546
  %flags116 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %wq_async115, i32 0, i32 7, !dbg !546
  %108 = load i32, i32* %flags116, align 8, !dbg !546
  %and117 = and i32 %108, 8192, !dbg !546
  %cmp118 = icmp eq i32 %and117, 0, !dbg !546
  br i1 %cmp118, label %if.then119, label %if.end120, !dbg !546

if.then119:                                       ; preds = %do.body114
  br label %do.end142, !dbg !550

if.end120:                                        ; preds = %do.body114
  %109 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !552
  %wq_async121 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %109, i32 0, i32 14, !dbg !552
  %flags122 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %wq_async121, i32 0, i32 7, !dbg !552
  %110 = load i32, i32* %flags122, align 8, !dbg !552
  %and123 = and i32 %110, -8193, !dbg !552
  store i32 %and123, i32* %flags122, align 8, !dbg !552
  %111 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !552
  %wq_async124 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %111, i32 0, i32 14, !dbg !552
  %flags125 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %wq_async124, i32 0, i32 7, !dbg !552
  %112 = load i32, i32* %flags125, align 8, !dbg !552
  %and126 = and i32 %112, 0, !dbg !552
  %cmp127 = icmp ne i32 %and126, 0, !dbg !552
  br i1 %cmp127, label %if.then128, label %if.end129, !dbg !552

if.then128:                                       ; preds = %if.end120
  br label %do.end142, !dbg !554

if.end129:                                        ; preds = %if.end120
  %113 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !557
  %wq_async130 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %113, i32 0, i32 14, !dbg !557
  %flags131 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %wq_async130, i32 0, i32 7, !dbg !557
  %114 = load i32, i32* %flags131, align 8, !dbg !557
  %and132 = and i32 %114, 16384, !dbg !557
  %cmp133 = icmp ne i32 %and132, 0, !dbg !557
  br i1 %cmp133, label %if.then134, label %if.end141, !dbg !557

if.then134:                                       ; preds = %if.end129
  br label %do.body135, !dbg !560

do.body135:                                       ; preds = %if.then134
  %115 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !562
  %wq_async136 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %115, i32 0, i32 14, !dbg !562
  %loop137 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %wq_async136, i32 0, i32 1, !dbg !562
  %116 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop137, align 8, !dbg !562
  %active_handles138 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %116, i32 0, i32 1, !dbg !562
  %117 = load i32, i32* %active_handles138, align 8, !dbg !562
  %dec139 = add i32 %117, -1, !dbg !562
  store i32 %dec139, i32* %active_handles138, align 8, !dbg !562
  br label %do.end140, !dbg !562

do.end140:                                        ; preds = %do.body135
  br label %if.end141, !dbg !565

if.end141:                                        ; preds = %do.end140, %if.end129
  br label %do.end142, !dbg !567

do.end142:                                        ; preds = %if.end141, %if.then128, %if.then119
  %118 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !569
  %wq_async143 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %118, i32 0, i32 14, !dbg !570
  %flags144 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %wq_async143, i32 0, i32 7, !dbg !571
  %119 = load i32, i32* %flags144, align 8, !dbg !572
  %or145 = or i32 %119, 32768, !dbg !572
  store i32 %or145, i32* %flags144, align 8, !dbg !572
  store i32 0, i32* %retval, align 4, !dbg !573
  br label %return, !dbg !573

fail_async_init:                                  ; preds = %if.then112
  %120 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !574
  %wq_mutex146 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %120, i32 0, i32 13, !dbg !575
  call void @uv_mutex_destroy(%union.pthread_mutex_t* %wq_mutex146), !dbg !576
  br label %fail_mutex_init, !dbg !576

fail_mutex_init:                                  ; preds = %fail_async_init, %if.then108
  %121 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !577
  %cloexec_lock147 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %121, i32 0, i32 15, !dbg !578
  call void @uv_rwlock_destroy(%union.pthread_rwlock_t* %cloexec_lock147), !dbg !579
  br label %fail_rwlock_init, !dbg !579

fail_rwlock_init:                                 ; preds = %fail_mutex_init, %if.then104
  %122 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !580
  call void @uv__signal_loop_cleanup(%struct.uv_loop_s* %122), !dbg !581
  br label %fail_signal_init, !dbg !581

fail_signal_init:                                 ; preds = %fail_rwlock_init, %if.then67
  %123 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !582
  call void @uv__platform_loop_delete(%struct.uv_loop_s* %123), !dbg !583
  %124 = load i32, i32* %err, align 4, !dbg !584
  store i32 %124, i32* %retval, align 4, !dbg !585
  br label %return, !dbg !585

return:                                           ; preds = %fail_signal_init, %do.end142, %if.then
  %125 = load i32, i32* %retval, align 4, !dbg !586
  ret i32 %125, !dbg !586
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @uv__signal_global_once_init() #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define internal void @heap_init(%struct.heap* %heap) #0 !dbg !368 {
entry:
  %heap.addr = alloca %struct.heap*, align 8
  store %struct.heap* %heap, %struct.heap** %heap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap** %heap.addr, metadata !587, metadata !376), !dbg !588
  %0 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !589
  %min = getelementptr inbounds %struct.heap, %struct.heap* %0, i32 0, i32 0, !dbg !590
  store %struct.heap_node* null, %struct.heap_node** %min, align 8, !dbg !591
  %1 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !592
  %nelts = getelementptr inbounds %struct.heap, %struct.heap* %1, i32 0, i32 1, !dbg !593
  store i32 0, i32* %nelts, align 8, !dbg !594
  ret void, !dbg !595
}

; Function Attrs: nounwind uwtable
define internal void @uv__update_time(%struct.uv_loop_s* %loop) #0 !dbg !371 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !596, metadata !376), !dbg !597
  %call = call i64 @uv__hrtime(i32 1), !dbg !598
  %div = udiv i64 %call, 1000000, !dbg !599
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !600
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 27, !dbg !601
  store i64 %div, i64* %time, align 8, !dbg !602
  ret void, !dbg !603
}

declare i32 @uv__platform_loop_init(%struct.uv_loop_s*) #2

declare i32 @uv_signal_init(%struct.uv_loop_s*, %struct.uv_signal_s*) #2

declare i32 @uv_rwlock_init(%union.pthread_rwlock_t*) #2

declare i32 @uv_mutex_init(%union.pthread_mutex_t*) #2

declare i32 @uv_async_init(%struct.uv_loop_s*, %struct.uv_async_s*, void (%struct.uv_async_s*)*) #2

declare void @uv__work_done(%struct.uv_async_s*) #2

declare void @uv_mutex_destroy(%union.pthread_mutex_t*) #2

declare void @uv_rwlock_destroy(%union.pthread_rwlock_t*) #2

declare void @uv__signal_loop_cleanup(%struct.uv_loop_s*) #2

declare void @uv__platform_loop_delete(%struct.uv_loop_s*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_loop_fork(%struct.uv_loop_s* %loop) #0 !dbg !353 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %err = alloca i32, align 4
  %i = alloca i32, align 4
  %w = alloca %struct.uv__io_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !604, metadata !376), !dbg !605
  call void @llvm.dbg.declare(metadata i32* %err, metadata !606, metadata !376), !dbg !607
  call void @llvm.dbg.declare(metadata i32* %i, metadata !608, metadata !376), !dbg !609
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w, metadata !610, metadata !376), !dbg !611
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !612
  %call = call i32 @uv__io_fork(%struct.uv_loop_s* %0), !dbg !613
  store i32 %call, i32* %err, align 4, !dbg !614
  %1 = load i32, i32* %err, align 4, !dbg !615
  %tobool = icmp ne i32 %1, 0, !dbg !615
  br i1 %tobool, label %if.then, label %if.end, !dbg !617

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !618
  store i32 %2, i32* %retval, align 4, !dbg !619
  br label %return, !dbg !619

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !620
  %call1 = call i32 @uv__async_fork(%struct.uv_loop_s* %3), !dbg !621
  store i32 %call1, i32* %err, align 4, !dbg !622
  %4 = load i32, i32* %err, align 4, !dbg !623
  %tobool2 = icmp ne i32 %4, 0, !dbg !623
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !625

if.then3:                                         ; preds = %if.end
  %5 = load i32, i32* %err, align 4, !dbg !626
  store i32 %5, i32* %retval, align 4, !dbg !627
  br label %return, !dbg !627

if.end4:                                          ; preds = %if.end
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !628
  %call5 = call i32 @uv__signal_loop_fork(%struct.uv_loop_s* %6), !dbg !629
  store i32 %call5, i32* %err, align 4, !dbg !630
  %7 = load i32, i32* %err, align 4, !dbg !631
  %tobool6 = icmp ne i32 %7, 0, !dbg !631
  br i1 %tobool6, label %if.then7, label %if.end8, !dbg !633

if.then7:                                         ; preds = %if.end4
  %8 = load i32, i32* %err, align 4, !dbg !634
  store i32 %8, i32* %retval, align 4, !dbg !635
  br label %return, !dbg !635

if.end8:                                          ; preds = %if.end4
  store i32 0, i32* %i, align 4, !dbg !636
  br label %for.cond, !dbg !638

for.cond:                                         ; preds = %for.inc, %if.end8
  %9 = load i32, i32* %i, align 4, !dbg !639
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !642
  %nwatchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 10, !dbg !643
  %11 = load i32, i32* %nwatchers, align 8, !dbg !643
  %cmp = icmp ult i32 %9, %11, !dbg !644
  br i1 %cmp, label %for.body, label %for.end, !dbg !645

for.body:                                         ; preds = %for.cond
  %12 = load i32, i32* %i, align 4, !dbg !646
  %idxprom = zext i32 %12 to i64, !dbg !648
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !648
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 9, !dbg !649
  %14 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !649
  %arrayidx = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %14, i64 %idxprom, !dbg !648
  %15 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx, align 8, !dbg !648
  store %struct.uv__io_s* %15, %struct.uv__io_s** %w, align 8, !dbg !650
  %16 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !651
  %cmp9 = icmp eq %struct.uv__io_s* %16, null, !dbg !653
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !654

if.then10:                                        ; preds = %for.body
  br label %for.inc, !dbg !655

if.end11:                                         ; preds = %for.body
  %17 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !656
  %pevents = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %17, i32 0, i32 3, !dbg !658
  %18 = load i32, i32* %pevents, align 8, !dbg !658
  %cmp12 = icmp ne i32 %18, 0, !dbg !659
  br i1 %cmp12, label %land.lhs.true, label %if.end31, !dbg !660

land.lhs.true:                                    ; preds = %if.end11
  %19 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !661
  %watcher_queue = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %19, i32 0, i32 2, !dbg !661
  %20 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !661
  %watcher_queue13 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %20, i32 0, i32 2, !dbg !661
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue13, i64 0, i64 0, !dbg !661
  %21 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !661
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !661
  %cmp15 = icmp eq [2 x i8*]* %watcher_queue, %22, !dbg !661
  br i1 %cmp15, label %if.then16, label %if.end31, !dbg !663

if.then16:                                        ; preds = %land.lhs.true
  %23 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !664
  %events = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %23, i32 0, i32 4, !dbg !666
  store i32 0, i32* %events, align 4, !dbg !667
  br label %do.body, !dbg !668

do.body:                                          ; preds = %if.then16
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !669
  %watcher_queue17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 8, !dbg !669
  %25 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !669
  %watcher_queue18 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %25, i32 0, i32 2, !dbg !669
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue18, i64 0, i64 0, !dbg !669
  %26 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !669
  store [2 x i8*]* %watcher_queue17, [2 x i8*]** %26, align 8, !dbg !669
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !669
  %watcher_queue20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 8, !dbg !669
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue20, i64 0, i64 1, !dbg !669
  %28 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !669
  %29 = load [2 x i8*]*, [2 x i8*]** %28, align 8, !dbg !669
  %30 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !669
  %watcher_queue22 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %30, i32 0, i32 2, !dbg !669
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue22, i64 0, i64 1, !dbg !669
  %31 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !669
  store [2 x i8*]* %29, [2 x i8*]** %31, align 8, !dbg !669
  %32 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !669
  %watcher_queue24 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %32, i32 0, i32 2, !dbg !669
  %33 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !669
  %watcher_queue25 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %33, i32 0, i32 2, !dbg !669
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue25, i64 0, i64 1, !dbg !669
  %34 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !669
  %35 = load [2 x i8*]*, [2 x i8*]** %34, align 8, !dbg !669
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %35, i64 0, i64 0, !dbg !669
  %36 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !669
  store [2 x i8*]* %watcher_queue24, [2 x i8*]** %36, align 8, !dbg !669
  %37 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !669
  %watcher_queue28 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %37, i32 0, i32 2, !dbg !669
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !669
  %watcher_queue29 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 8, !dbg !669
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue29, i64 0, i64 1, !dbg !669
  %39 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !669
  store [2 x i8*]* %watcher_queue28, [2 x i8*]** %39, align 8, !dbg !669
  br label %do.end, !dbg !669

do.end:                                           ; preds = %do.body
  br label %if.end31, !dbg !672

if.end31:                                         ; preds = %do.end, %land.lhs.true, %if.end11
  br label %for.inc, !dbg !673

for.inc:                                          ; preds = %if.end31, %if.then10
  %40 = load i32, i32* %i, align 4, !dbg !674
  %inc = add i32 %40, 1, !dbg !674
  store i32 %inc, i32* %i, align 4, !dbg !674
  br label %for.cond, !dbg !676

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !677
  br label %return, !dbg !677

return:                                           ; preds = %for.end, %if.then7, %if.then3, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !678
  ret i32 %41, !dbg !678
}

declare i32 @uv__io_fork(%struct.uv_loop_s*) #2

declare i32 @uv__async_fork(%struct.uv_loop_s*) #2

declare i32 @uv__signal_loop_fork(%struct.uv_loop_s*) #2

; Function Attrs: nounwind uwtable
define void @uv__loop_close(%struct.uv_loop_s* %loop) #0 !dbg !354 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !679, metadata !376), !dbg !680
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !681
  call void @uv__signal_loop_cleanup(%struct.uv_loop_s* %0), !dbg !682
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !683
  call void @uv__platform_loop_delete(%struct.uv_loop_s* %1), !dbg !684
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !685
  call void @uv__async_stop(%struct.uv_loop_s* %2), !dbg !686
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !687
  %emfile_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 31, !dbg !689
  %4 = load i32, i32* %emfile_fd, align 8, !dbg !689
  %cmp = icmp ne i32 %4, -1, !dbg !690
  br i1 %cmp, label %if.then, label %if.end, !dbg !691

if.then:                                          ; preds = %entry
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !692
  %emfile_fd1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 31, !dbg !694
  %6 = load i32, i32* %emfile_fd1, align 8, !dbg !694
  %call = call i32 @uv__close(i32 %6), !dbg !695
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !696
  %emfile_fd2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 31, !dbg !697
  store i32 -1, i32* %emfile_fd2, align 8, !dbg !698
  br label %if.end, !dbg !699

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !700
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 6, !dbg !702
  %9 = load i32, i32* %backend_fd, align 8, !dbg !702
  %cmp3 = icmp ne i32 %9, -1, !dbg !703
  br i1 %cmp3, label %if.then4, label %if.end8, !dbg !704

if.then4:                                         ; preds = %if.end
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !705
  %backend_fd5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 6, !dbg !707
  %11 = load i32, i32* %backend_fd5, align 8, !dbg !707
  %call6 = call i32 @uv__close(i32 %11), !dbg !708
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !709
  %backend_fd7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 6, !dbg !710
  store i32 -1, i32* %backend_fd7, align 8, !dbg !711
  br label %if.end8, !dbg !712

if.end8:                                          ; preds = %if.then4, %if.end
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !713
  %wq_mutex = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 13, !dbg !714
  call void @uv_mutex_lock(%union.pthread_mutex_t* %wq_mutex), !dbg !715
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !716
  %wq = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 12, !dbg !716
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !716
  %wq9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %15, i32 0, i32 12, !dbg !716
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq9, i64 0, i64 0, !dbg !716
  %16 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !716
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !716
  %cmp10 = icmp eq [2 x i8*]* %wq, %17, !dbg !716
  br i1 %cmp10, label %land.lhs.true, label %cond.false, !dbg !716

land.lhs.true:                                    ; preds = %if.end8
  br i1 true, label %cond.true, label %cond.false, !dbg !717

cond.true:                                        ; preds = %land.lhs.true
  br label %cond.end, !dbg !719

cond.false:                                       ; preds = %land.lhs.true, %if.end8
  call void @__assert_fail(i8* getelementptr inbounds ([123 x i8], [123 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.2, i32 0, i32 0), i32 161, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__loop_close, i32 0, i32 0)) #5, !dbg !721
  unreachable, !dbg !721
                                                  ; No predecessors!
  br label %cond.end, !dbg !723

cond.end:                                         ; preds = %18, %cond.true
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !725
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %19, i32 0, i32 3, !dbg !725
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !725
  %active_reqs11 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 3, !dbg !725
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs11, i64 0, i64 0, !dbg !725
  %21 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !725
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !725
  %cmp13 = icmp eq [2 x i8*]* %active_reqs, %22, !dbg !725
  %conv = zext i1 %cmp13 to i32, !dbg !725
  %cmp14 = icmp eq i32 %conv, 0, !dbg !725
  br i1 %cmp14, label %cond.false17, label %cond.true16, !dbg !725

cond.true16:                                      ; preds = %cond.end
  br label %cond.end18, !dbg !726

cond.false17:                                     ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([114 x i8], [114 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([68 x i8], [68 x i8]* @.str.2, i32 0, i32 0), i32 162, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.uv__loop_close, i32 0, i32 0)) #5, !dbg !727
  unreachable, !dbg !727
                                                  ; No predecessors!
  br label %cond.end18, !dbg !728

cond.end18:                                       ; preds = %23, %cond.true16
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !729
  %wq_mutex19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 13, !dbg !730
  call void @uv_mutex_unlock(%union.pthread_mutex_t* %wq_mutex19), !dbg !731
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !732
  %wq_mutex20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %25, i32 0, i32 13, !dbg !733
  call void @uv_mutex_destroy(%union.pthread_mutex_t* %wq_mutex20), !dbg !734
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !735
  %cloexec_lock = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 15, !dbg !736
  call void @uv_rwlock_destroy(%union.pthread_rwlock_t* %cloexec_lock), !dbg !737
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !738
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 9, !dbg !739
  %28 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !739
  %29 = bitcast %struct.uv__io_s** %28 to i8*, !dbg !738
  call void @uv__free(i8* %29), !dbg !740
  %30 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !741
  %watchers21 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %30, i32 0, i32 9, !dbg !742
  store %struct.uv__io_s** null, %struct.uv__io_s*** %watchers21, align 8, !dbg !743
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !744
  %nwatchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %31, i32 0, i32 10, !dbg !745
  store i32 0, i32* %nwatchers, align 8, !dbg !746
  ret void, !dbg !747
}

declare void @uv__async_stop(%struct.uv_loop_s*) #2

declare i32 @uv__close(i32) #2

declare void @uv_mutex_lock(%union.pthread_mutex_t*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

declare void @uv_mutex_unlock(%union.pthread_mutex_t*) #2

declare void @uv__free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @uv__loop_configure(%struct.uv_loop_s* %loop, i32 %option, %struct.__va_list_tag* %ap) #0 !dbg !357 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %option.addr = alloca i32, align 4
  %ap.addr = alloca %struct.__va_list_tag*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !748, metadata !376), !dbg !749
  store i32 %option, i32* %option.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %option.addr, metadata !750, metadata !376), !dbg !751
  store %struct.__va_list_tag* %ap, %struct.__va_list_tag** %ap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap.addr, metadata !752, metadata !376), !dbg !753
  %0 = load i32, i32* %option.addr, align 4, !dbg !754
  %cmp = icmp ne i32 %0, 0, !dbg !756
  br i1 %cmp, label %if.then, label %if.end, !dbg !757

if.then:                                          ; preds = %entry
  store i32 -38, i32* %retval, align 4, !dbg !758
  br label %return, !dbg !758

if.end:                                           ; preds = %entry
  %1 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap.addr, align 8, !dbg !759
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %1, i32 0, i32 0, !dbg !759
  %gp_offset = load i32, i32* %gp_offset_p, align 8, !dbg !759
  %fits_in_gp = icmp ule i32 %gp_offset, 40, !dbg !759
  br i1 %fits_in_gp, label %vaarg.in_reg, label %vaarg.in_mem, !dbg !759

vaarg.in_reg:                                     ; preds = %if.end
  %2 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %1, i32 0, i32 3, !dbg !761
  %reg_save_area = load i8*, i8** %2, align 8, !dbg !761
  %3 = getelementptr i8, i8* %reg_save_area, i32 %gp_offset, !dbg !761
  %4 = bitcast i8* %3 to i32*, !dbg !761
  %5 = add i32 %gp_offset, 8, !dbg !761
  store i32 %5, i32* %gp_offset_p, align 8, !dbg !761
  br label %vaarg.end, !dbg !761

vaarg.in_mem:                                     ; preds = %if.end
  %overflow_arg_area_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %1, i32 0, i32 2, !dbg !763
  %overflow_arg_area = load i8*, i8** %overflow_arg_area_p, align 8, !dbg !763
  %6 = bitcast i8* %overflow_arg_area to i32*, !dbg !763
  %overflow_arg_area.next = getelementptr i8, i8* %overflow_arg_area, i32 8, !dbg !763
  store i8* %overflow_arg_area.next, i8** %overflow_arg_area_p, align 8, !dbg !763
  br label %vaarg.end, !dbg !763

vaarg.end:                                        ; preds = %vaarg.in_mem, %vaarg.in_reg
  %vaarg.addr = phi i32* [ %4, %vaarg.in_reg ], [ %6, %vaarg.in_mem ], !dbg !765
  %7 = load i32, i32* %vaarg.addr, align 4, !dbg !765
  %cmp1 = icmp ne i32 %7, 27, !dbg !767
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !765

if.then2:                                         ; preds = %vaarg.end
  store i32 -22, i32* %retval, align 4, !dbg !768
  br label %return, !dbg !768

if.end3:                                          ; preds = %vaarg.end
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !769
  %flags = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 5, !dbg !770
  %9 = load i64, i64* %flags, align 8, !dbg !771
  %or = or i64 %9, 1, !dbg !771
  store i64 %or, i64* %flags, align 8, !dbg !771
  store i32 0, i32* %retval, align 4, !dbg !772
  br label %return, !dbg !772

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !773
  ret i32 %10, !dbg !773
}

declare i64 @uv__hrtime(i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!372, !373}
!llvm.ident = !{!374}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !123, subprograms: !147)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/loop.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !33, !36, !115, !119}
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
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 239, size: 32, align: 32, elements: !34)
!34 = !{!35}
!35 = !DIEnumerator(name: "UV_LOOP_BLOCK_SIGNAL", value: 0)
!36 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !37)
!37 = !{!38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114}
!38 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!39 = !DIEnumerator(name: "UV_EACCES", value: -13)
!40 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!41 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!42 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!43 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!44 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!45 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!46 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!47 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!48 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!49 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!50 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!51 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!52 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!53 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!54 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!55 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!56 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!57 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!58 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!59 = !DIEnumerator(name: "UV_EBADF", value: -9)
!60 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!61 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!62 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!63 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!64 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!65 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!66 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!67 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!68 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!69 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!70 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!71 = !DIEnumerator(name: "UV_EINTR", value: -4)
!72 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!73 = !DIEnumerator(name: "UV_EIO", value: -5)
!74 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!75 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!76 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!77 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!78 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!79 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!80 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!81 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!82 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!83 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!84 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!85 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!86 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!87 = !DIEnumerator(name: "UV_ENONET", value: -64)
!88 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!89 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!90 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!91 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!92 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!93 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!94 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!95 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!96 = !DIEnumerator(name: "UV_EPERM", value: -1)
!97 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!98 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!99 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!100 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!101 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!102 = !DIEnumerator(name: "UV_EROFS", value: -30)
!103 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!104 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!105 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!106 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!107 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!108 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!109 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!110 = !DIEnumerator(name: "UV_EOF", value: -4095)
!111 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!112 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!113 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!114 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!115 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !116, line: 144, size: 32, align: 32, elements: !117)
!116 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!117 = !{!118}
!118 = !DIEnumerator(name: "UV_LOOP_BLOCK_SIGPROF", value: 1)
!119 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !116, line: 148, size: 32, align: 32, elements: !120)
!120 = !{!121, !122}
!121 = !DIEnumerator(name: "UV_CLOCK_PRECISE", value: 0)
!122 = !DIEnumerator(name: "UV_CLOCK_FAST", value: 1)
!123 = !{!124, !137, !142, !145}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DICompositeType(tag: DW_TAG_structure_type, name: "heap", file: !126, line: 40, size: 128, align: 64, elements: !127)
!126 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/heap-inl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!127 = !{!128, !135}
!128 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !125, file: !126, line: 41, baseType: !129, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "heap_node", file: !126, line: 27, size: 192, align: 64, elements: !131)
!131 = !{!132, !133, !134}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "left", scope: !130, file: !126, line: 28, baseType: !129, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "right", scope: !130, file: !126, line: 29, baseType: !129, size: 64, align: 64, offset: 64)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "parent", scope: !130, file: !126, line: 30, baseType: !129, size: 64, align: 64, offset: 128)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !125, file: !126, line: 42, baseType: !136, size: 32, align: 32, offset: 64)
!136 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !140, line: 21, baseType: !141)
!140 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!141 = !DICompositeType(tag: DW_TAG_array_type, baseType: !142, size: 128, align: 64, elements: !143)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!143 = !{!144}
!144 = !DISubrange(count: 2)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !139)
!147 = !{!148, !353, !354, !357, !368, !371}
!148 = distinct !DISubprogram(name: "uv_loop_init", scope: !1, file: !1, line: 30, type: !149, isLocal: false, isDefinition: true, scopeLine: 30, flags: DIFlagPrototyped, isOptimized: false, variables: !352)
!149 = !DISubroutineType(types: !150)
!150 = !{!151, !152}
!151 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !154)
!154 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !155)
!155 = !{!156, !157, !158, !159, !160, !161, !163, !164, !165, !166, !185, !186, !187, !188, !219, !267, !291, !292, !293, !294, !295, !296, !297, !301, !302, !303, !308, !311, !312, !314, !315, !348, !349, !350, !351}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !154, file: !4, line: 1475, baseType: !142, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !154, file: !4, line: 1477, baseType: !136, size: 32, align: 32, offset: 64)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !154, file: !4, line: 1478, baseType: !141, size: 128, align: 64, offset: 128)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !154, file: !4, line: 1479, baseType: !141, size: 128, align: 64, offset: 256)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !154, file: !4, line: 1481, baseType: !136, size: 32, align: 32, offset: 384)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !154, file: !4, line: 1482, baseType: !162, size: 64, align: 64, offset: 448)
!162 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !154, file: !4, line: 1482, baseType: !151, size: 32, align: 32, offset: 512)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 576)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 704)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !154, file: !4, line: 1482, baseType: !167, size: 64, align: 64, offset: 832)
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !170, line: 87, baseType: !171)
!170 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!171 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !170, line: 89, size: 448, align: 64, elements: !172)
!172 = !{!173, !180, !181, !182, !183, !184}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !171, file: !170, line: 90, baseType: !174, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !170, line: 84, baseType: !175)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{null, !178, !179, !136}
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !171, file: !170, line: 91, baseType: !141, size: 128, align: 64, offset: 64)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !171, file: !170, line: 92, baseType: !141, size: 128, align: 64, offset: 192)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !171, file: !170, line: 93, baseType: !136, size: 32, align: 32, offset: 320)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !171, file: !170, line: 94, baseType: !136, size: 32, align: 32, offset: 352)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !171, file: !170, line: 95, baseType: !151, size: 32, align: 32, offset: 384)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !154, file: !4, line: 1482, baseType: !136, size: 32, align: 32, offset: 896)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !154, file: !4, line: 1482, baseType: !136, size: 32, align: 32, offset: 928)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 960)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !154, file: !4, line: 1482, baseType: !189, size: 320, align: 64, offset: 1088)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !170, line: 129, baseType: !190)
!190 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !191, line: 127, baseType: !192)
!191 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!192 = !DICompositeType(tag: DW_TAG_union_type, file: !191, line: 90, size: 320, align: 64, elements: !193)
!193 = !{!194, !212, !217}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !192, file: !191, line: 124, baseType: !195, size: 320, align: 64)
!195 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !191, line: 92, size: 320, align: 64, elements: !196)
!196 = !{!197, !198, !199, !200, !201, !202, !204, !205}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !195, file: !191, line: 94, baseType: !151, size: 32, align: 32)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !195, file: !191, line: 95, baseType: !136, size: 32, align: 32, offset: 32)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !195, file: !191, line: 96, baseType: !151, size: 32, align: 32, offset: 64)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !195, file: !191, line: 98, baseType: !136, size: 32, align: 32, offset: 96)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !195, file: !191, line: 102, baseType: !151, size: 32, align: 32, offset: 128)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !195, file: !191, line: 104, baseType: !203, size: 16, align: 16, offset: 160)
!203 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !195, file: !191, line: 105, baseType: !203, size: 16, align: 16, offset: 176)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !195, file: !191, line: 106, baseType: !206, size: 128, align: 64, offset: 192)
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !191, line: 79, baseType: !207)
!207 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !191, line: 75, size: 128, align: 64, elements: !208)
!208 = !{!209, !211}
!209 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !207, file: !191, line: 77, baseType: !210, size: 64, align: 64)
!210 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !207, size: 64, align: 64)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !207, file: !191, line: 78, baseType: !210, size: 64, align: 64, offset: 64)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !192, file: !191, line: 125, baseType: !213, size: 320, align: 8)
!213 = !DICompositeType(tag: DW_TAG_array_type, baseType: !214, size: 320, align: 8, elements: !215)
!214 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!215 = !{!216}
!216 = !DISubrange(count: 40)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !192, file: !191, line: 126, baseType: !218, size: 64, align: 64)
!218 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !154, file: !4, line: 1482, baseType: !220, size: 1024, align: 64, offset: 1408)
!220 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !221)
!221 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !222)
!222 = !{!223, !224, !225, !227, !251, !252, !257, !258, !259, !265, !266}
!223 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !221, file: !4, line: 768, baseType: !142, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !221, file: !4, line: 768, baseType: !152, size: 64, align: 64, offset: 64)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !221, file: !4, line: 768, baseType: !226, size: 32, align: 32, offset: 128)
!226 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !221, file: !4, line: 768, baseType: !228, size: 64, align: 64, offset: 192)
!228 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !229)
!229 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !230, size: 64, align: 64)
!230 = !DISubroutineType(types: !231)
!231 = !{null, !232}
!232 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !233, size: 64, align: 64)
!233 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !234)
!234 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !235)
!235 = !{!236, !237, !238, !239, !240, !241, !249, !250}
!236 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !234, file: !4, line: 426, baseType: !142, size: 64, align: 64)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !234, file: !4, line: 426, baseType: !152, size: 64, align: 64, offset: 64)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !234, file: !4, line: 426, baseType: !226, size: 32, align: 32, offset: 128)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !234, file: !4, line: 426, baseType: !228, size: 64, align: 64, offset: 192)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !234, file: !4, line: 426, baseType: !141, size: 128, align: 64, offset: 256)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !234, file: !4, line: 426, baseType: !242, size: 256, align: 64, offset: 384)
!242 = !DICompositeType(tag: DW_TAG_union_type, scope: !234, file: !4, line: 426, size: 256, align: 64, elements: !243)
!243 = !{!244, !245}
!244 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !242, file: !4, line: 426, baseType: !151, size: 32, align: 32)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !242, file: !4, line: 426, baseType: !246, size: 256, align: 64)
!246 = !DICompositeType(tag: DW_TAG_array_type, baseType: !142, size: 256, align: 64, elements: !247)
!247 = !{!248}
!248 = !DISubrange(count: 4)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !234, file: !4, line: 426, baseType: !232, size: 64, align: 64, offset: 640)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !234, file: !4, line: 426, baseType: !136, size: 32, align: 32, offset: 704)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !221, file: !4, line: 768, baseType: !141, size: 128, align: 64, offset: 256)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !221, file: !4, line: 768, baseType: !253, size: 256, align: 64, offset: 384)
!253 = !DICompositeType(tag: DW_TAG_union_type, scope: !221, file: !4, line: 768, size: 256, align: 64, elements: !254)
!254 = !{!255, !256}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !253, file: !4, line: 768, baseType: !151, size: 32, align: 32)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !253, file: !4, line: 768, baseType: !246, size: 256, align: 64)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !221, file: !4, line: 768, baseType: !232, size: 64, align: 64, offset: 640)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !221, file: !4, line: 768, baseType: !136, size: 32, align: 32, offset: 704)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !221, file: !4, line: 769, baseType: !260, size: 64, align: 64, offset: 768)
!260 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !261)
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !262, size: 64, align: 64)
!262 = !DISubroutineType(types: !263)
!263 = !{null, !264}
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !220, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !221, file: !4, line: 769, baseType: !141, size: 128, align: 64, offset: 832)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !221, file: !4, line: 769, baseType: !151, size: 32, align: 32, offset: 960)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !154, file: !4, line: 1482, baseType: !268, size: 448, align: 64, offset: 2432)
!268 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !170, line: 130, baseType: !269)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !191, line: 213, baseType: !270)
!270 = !DICompositeType(tag: DW_TAG_union_type, file: !191, line: 173, size: 448, align: 64, elements: !271)
!271 = !{!272, !286, !290}
!272 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !270, file: !191, line: 192, baseType: !273, size: 448, align: 64)
!273 = !DICompositeType(tag: DW_TAG_structure_type, scope: !270, file: !191, line: 176, size: 448, align: 64, elements: !274)
!274 = !{!275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285}
!275 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !273, file: !191, line: 178, baseType: !151, size: 32, align: 32)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !273, file: !191, line: 179, baseType: !136, size: 32, align: 32, offset: 32)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !273, file: !191, line: 180, baseType: !136, size: 32, align: 32, offset: 64)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !273, file: !191, line: 181, baseType: !136, size: 32, align: 32, offset: 96)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !273, file: !191, line: 182, baseType: !136, size: 32, align: 32, offset: 128)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !273, file: !191, line: 183, baseType: !136, size: 32, align: 32, offset: 160)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !273, file: !191, line: 184, baseType: !151, size: 32, align: 32, offset: 192)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !273, file: !191, line: 185, baseType: !151, size: 32, align: 32, offset: 224)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !273, file: !191, line: 186, baseType: !162, size: 64, align: 64, offset: 256)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !273, file: !191, line: 187, baseType: !162, size: 64, align: 64, offset: 320)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !273, file: !191, line: 190, baseType: !136, size: 32, align: 32, offset: 384)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !270, file: !191, line: 211, baseType: !287, size: 448, align: 8)
!287 = !DICompositeType(tag: DW_TAG_array_type, baseType: !214, size: 448, align: 8, elements: !288)
!288 = !{!289}
!289 = !DISubrange(count: 56)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !270, file: !191, line: 212, baseType: !218, size: 64, align: 64)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !154, file: !4, line: 1482, baseType: !232, size: 64, align: 64, offset: 2880)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 2944)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 3072)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 3200)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 3328)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !154, file: !4, line: 1482, baseType: !141, size: 128, align: 64, offset: 3456)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !154, file: !4, line: 1482, baseType: !298, size: 64, align: 64, offset: 3584)
!298 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !299, size: 64, align: 64)
!299 = !DISubroutineType(types: !300)
!300 = !{null}
!301 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !154, file: !4, line: 1482, baseType: !169, size: 448, align: 64, offset: 3648)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !154, file: !4, line: 1482, baseType: !151, size: 32, align: 32, offset: 4096)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !154, file: !4, line: 1482, baseType: !304, size: 128, align: 64, offset: 4160)
!304 = !DICompositeType(tag: DW_TAG_structure_type, scope: !154, file: !4, line: 1482, size: 128, align: 64, elements: !305)
!305 = !{!306, !307}
!306 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !304, file: !4, line: 1482, baseType: !142, size: 64, align: 64)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !304, file: !4, line: 1482, baseType: !136, size: 32, align: 32, offset: 64)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !154, file: !4, line: 1482, baseType: !309, size: 64, align: 64, offset: 4288)
!309 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !310, line: 55, baseType: !162)
!310 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!311 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !154, file: !4, line: 1482, baseType: !309, size: 64, align: 64, offset: 4352)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !154, file: !4, line: 1482, baseType: !313, size: 64, align: 32, offset: 4416)
!313 = !DICompositeType(tag: DW_TAG_array_type, baseType: !151, size: 64, align: 32, elements: !143)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !154, file: !4, line: 1482, baseType: !169, size: 448, align: 64, offset: 4480)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !154, file: !4, line: 1482, baseType: !316, size: 1216, align: 64, offset: 4928)
!316 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !317)
!317 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !318)
!318 = !{!319, !320, !321, !322, !323, !324, !329, !330, !331, !337, !338, !346, !347}
!319 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !317, file: !4, line: 1326, baseType: !142, size: 64, align: 64)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !317, file: !4, line: 1326, baseType: !152, size: 64, align: 64, offset: 64)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !317, file: !4, line: 1326, baseType: !226, size: 32, align: 32, offset: 128)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !317, file: !4, line: 1326, baseType: !228, size: 64, align: 64, offset: 192)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !317, file: !4, line: 1326, baseType: !141, size: 128, align: 64, offset: 256)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !317, file: !4, line: 1326, baseType: !325, size: 256, align: 64, offset: 384)
!325 = !DICompositeType(tag: DW_TAG_union_type, scope: !317, file: !4, line: 1326, size: 256, align: 64, elements: !326)
!326 = !{!327, !328}
!327 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !325, file: !4, line: 1326, baseType: !151, size: 32, align: 32)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !325, file: !4, line: 1326, baseType: !246, size: 256, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !317, file: !4, line: 1326, baseType: !232, size: 64, align: 64, offset: 640)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !317, file: !4, line: 1326, baseType: !136, size: 32, align: 32, offset: 704)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !317, file: !4, line: 1327, baseType: !332, size: 64, align: 64, offset: 768)
!332 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !333)
!333 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !334, size: 64, align: 64)
!334 = !DISubroutineType(types: !335)
!335 = !{null, !336, !151}
!336 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !316, size: 64, align: 64)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !317, file: !4, line: 1328, baseType: !151, size: 32, align: 32, offset: 832)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !317, file: !4, line: 1329, baseType: !339, size: 256, align: 64, offset: 896)
!339 = !DICompositeType(tag: DW_TAG_structure_type, scope: !317, file: !4, line: 1329, size: 256, align: 64, elements: !340)
!340 = !{!341, !343, !344, !345}
!341 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !339, file: !4, line: 1329, baseType: !342, size: 64, align: 64)
!342 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !317, size: 64, align: 64)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !339, file: !4, line: 1329, baseType: !342, size: 64, align: 64, offset: 64)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !339, file: !4, line: 1329, baseType: !342, size: 64, align: 64, offset: 128)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !339, file: !4, line: 1329, baseType: !151, size: 32, align: 32, offset: 192)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !317, file: !4, line: 1329, baseType: !136, size: 32, align: 32, offset: 1152)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !317, file: !4, line: 1329, baseType: !136, size: 32, align: 32, offset: 1184)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !154, file: !4, line: 1482, baseType: !151, size: 32, align: 32, offset: 6144)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !154, file: !4, line: 1482, baseType: !169, size: 448, align: 64, offset: 6208)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !154, file: !4, line: 1482, baseType: !142, size: 64, align: 64, offset: 6656)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !154, file: !4, line: 1482, baseType: !151, size: 32, align: 32, offset: 6720)
!352 = !{}
!353 = distinct !DISubprogram(name: "uv_loop_fork", scope: !1, file: !1, line: 112, type: !149, isLocal: false, isDefinition: true, scopeLine: 112, flags: DIFlagPrototyped, isOptimized: false, variables: !352)
!354 = distinct !DISubprogram(name: "uv__loop_close", scope: !1, file: !1, line: 145, type: !355, isLocal: false, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !352)
!355 = !DISubroutineType(types: !356)
!356 = !{null, !152}
!357 = distinct !DISubprogram(name: "uv__loop_configure", scope: !1, file: !1, line: 184, type: !358, isLocal: false, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !352)
!358 = !DISubroutineType(types: !359)
!359 = !{!151, !152, !360, !361}
!360 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_option", file: !4, line: 241, baseType: !33)
!361 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !362, size: 64, align: 64)
!362 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 181, size: 192, align: 64, elements: !363)
!363 = !{!364, !365, !366, !367}
!364 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !362, file: !1, line: 181, baseType: !136, size: 32, align: 32)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !362, file: !1, line: 181, baseType: !136, size: 32, align: 32, offset: 32)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !362, file: !1, line: 181, baseType: !142, size: 64, align: 64, offset: 64)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !362, file: !1, line: 181, baseType: !142, size: 64, align: 64, offset: 128)
!368 = distinct !DISubprogram(name: "heap_init", scope: !126, file: !126, line: 62, type: !369, isLocal: true, isDefinition: true, scopeLine: 62, flags: DIFlagPrototyped, isOptimized: false, variables: !352)
!369 = !DISubroutineType(types: !370)
!370 = !{null, !124}
!371 = distinct !DISubprogram(name: "uv__update_time", scope: !116, file: !116, line: 306, type: !355, isLocal: true, isDefinition: true, scopeLine: 306, flags: DIFlagPrototyped, isOptimized: false, variables: !352)
!372 = !{i32 2, !"Dwarf Version", i32 4}
!373 = !{i32 2, !"Debug Info Version", i32 3}
!374 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!375 = !DILocalVariable(name: "loop", arg: 1, scope: !148, file: !1, line: 30, type: !152)
!376 = !DIExpression()
!377 = !DILocation(line: 30, column: 29, scope: !148)
!378 = !DILocalVariable(name: "saved_data", scope: !148, file: !1, line: 31, type: !142)
!379 = !DILocation(line: 31, column: 9, scope: !148)
!380 = !DILocalVariable(name: "err", scope: !148, file: !1, line: 32, type: !151)
!381 = !DILocation(line: 32, column: 7, scope: !148)
!382 = !DILocation(line: 34, column: 3, scope: !148)
!383 = !DILocation(line: 36, column: 16, scope: !148)
!384 = !DILocation(line: 36, column: 22, scope: !148)
!385 = !DILocation(line: 36, column: 14, scope: !148)
!386 = !DILocation(line: 37, column: 10, scope: !148)
!387 = !DILocation(line: 37, column: 3, scope: !148)
!388 = !DILocation(line: 38, column: 16, scope: !148)
!389 = !DILocation(line: 38, column: 3, scope: !148)
!390 = !DILocation(line: 38, column: 9, scope: !148)
!391 = !DILocation(line: 38, column: 14, scope: !148)
!392 = !DILocation(line: 40, column: 29, scope: !148)
!393 = !DILocation(line: 40, column: 35, scope: !148)
!394 = !DILocation(line: 40, column: 13, scope: !148)
!395 = !DILocation(line: 40, column: 3, scope: !148)
!396 = !DILocation(line: 41, column: 3, scope: !148)
!397 = !DILocation(line: 41, column: 3, scope: !398)
!398 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 1)
!399 = distinct !DILexicalBlock(scope: !148, file: !1, line: 41, column: 3)
!400 = !DILocation(line: 42, column: 3, scope: !148)
!401 = !DILocation(line: 42, column: 3, scope: !402)
!402 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 1)
!403 = distinct !DILexicalBlock(scope: !148, file: !1, line: 42, column: 3)
!404 = !DILocation(line: 43, column: 3, scope: !148)
!405 = !DILocation(line: 43, column: 3, scope: !406)
!406 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 1)
!407 = distinct !DILexicalBlock(scope: !148, file: !1, line: 43, column: 3)
!408 = !DILocation(line: 44, column: 3, scope: !148)
!409 = !DILocation(line: 44, column: 3, scope: !410)
!410 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 1)
!411 = distinct !DILexicalBlock(scope: !148, file: !1, line: 44, column: 3)
!412 = !DILocation(line: 45, column: 3, scope: !148)
!413 = !DILocation(line: 45, column: 3, scope: !414)
!414 = !DILexicalBlockFile(scope: !415, file: !1, discriminator: 1)
!415 = distinct !DILexicalBlock(scope: !148, file: !1, line: 45, column: 3)
!416 = !DILocation(line: 46, column: 3, scope: !148)
!417 = !DILocation(line: 46, column: 3, scope: !418)
!418 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 1)
!419 = distinct !DILexicalBlock(scope: !148, file: !1, line: 46, column: 3)
!420 = !DILocation(line: 47, column: 3, scope: !148)
!421 = !DILocation(line: 47, column: 3, scope: !422)
!422 = !DILexicalBlockFile(scope: !423, file: !1, discriminator: 1)
!423 = distinct !DILexicalBlock(scope: !148, file: !1, line: 47, column: 3)
!424 = !DILocation(line: 49, column: 3, scope: !148)
!425 = !DILocation(line: 49, column: 9, scope: !148)
!426 = !DILocation(line: 49, column: 14, scope: !148)
!427 = !DILocation(line: 50, column: 3, scope: !148)
!428 = !DILocation(line: 50, column: 9, scope: !148)
!429 = !DILocation(line: 50, column: 18, scope: !148)
!430 = !DILocation(line: 51, column: 3, scope: !148)
!431 = !DILocation(line: 51, column: 9, scope: !148)
!432 = !DILocation(line: 51, column: 19, scope: !148)
!433 = !DILocation(line: 52, column: 3, scope: !148)
!434 = !DILocation(line: 52, column: 3, scope: !435)
!435 = !DILexicalBlockFile(scope: !436, file: !1, discriminator: 1)
!436 = distinct !DILexicalBlock(scope: !148, file: !1, line: 52, column: 3)
!437 = !DILocation(line: 53, column: 3, scope: !148)
!438 = !DILocation(line: 53, column: 3, scope: !439)
!439 = !DILexicalBlockFile(scope: !440, file: !1, discriminator: 1)
!440 = distinct !DILexicalBlock(scope: !148, file: !1, line: 53, column: 3)
!441 = !DILocation(line: 55, column: 3, scope: !148)
!442 = !DILocation(line: 55, column: 9, scope: !148)
!443 = !DILocation(line: 55, column: 25, scope: !148)
!444 = !DILocation(line: 56, column: 19, scope: !148)
!445 = !DILocation(line: 56, column: 3, scope: !148)
!446 = !DILocation(line: 57, column: 3, scope: !148)
!447 = !DILocation(line: 57, column: 9, scope: !148)
!448 = !DILocation(line: 57, column: 26, scope: !148)
!449 = !DILocation(line: 57, column: 29, scope: !148)
!450 = !DILocation(line: 58, column: 3, scope: !148)
!451 = !DILocation(line: 58, column: 9, scope: !148)
!452 = !DILocation(line: 58, column: 19, scope: !148)
!453 = !DILocation(line: 59, column: 3, scope: !148)
!454 = !DILocation(line: 59, column: 9, scope: !148)
!455 = !DILocation(line: 59, column: 26, scope: !148)
!456 = !DILocation(line: 60, column: 3, scope: !148)
!457 = !DILocation(line: 60, column: 9, scope: !148)
!458 = !DILocation(line: 60, column: 26, scope: !148)
!459 = !DILocation(line: 61, column: 3, scope: !148)
!460 = !DILocation(line: 61, column: 9, scope: !148)
!461 = !DILocation(line: 61, column: 20, scope: !148)
!462 = !DILocation(line: 62, column: 3, scope: !148)
!463 = !DILocation(line: 62, column: 9, scope: !148)
!464 = !DILocation(line: 62, column: 19, scope: !148)
!465 = !DILocation(line: 64, column: 3, scope: !148)
!466 = !DILocation(line: 64, column: 9, scope: !148)
!467 = !DILocation(line: 64, column: 23, scope: !148)
!468 = !DILocation(line: 65, column: 3, scope: !148)
!469 = !DILocation(line: 65, column: 9, scope: !148)
!470 = !DILocation(line: 65, column: 19, scope: !148)
!471 = !DILocation(line: 67, column: 32, scope: !148)
!472 = !DILocation(line: 67, column: 9, scope: !148)
!473 = !DILocation(line: 67, column: 7, scope: !148)
!474 = !DILocation(line: 68, column: 7, scope: !475)
!475 = distinct !DILexicalBlock(scope: !148, file: !1, line: 68, column: 7)
!476 = !DILocation(line: 68, column: 7, scope: !148)
!477 = !DILocation(line: 69, column: 12, scope: !475)
!478 = !DILocation(line: 69, column: 5, scope: !475)
!479 = !DILocation(line: 71, column: 24, scope: !148)
!480 = !DILocation(line: 71, column: 31, scope: !148)
!481 = !DILocation(line: 71, column: 37, scope: !148)
!482 = !DILocation(line: 71, column: 9, scope: !148)
!483 = !DILocation(line: 71, column: 7, scope: !148)
!484 = !DILocation(line: 72, column: 7, scope: !485)
!485 = distinct !DILexicalBlock(scope: !148, file: !1, line: 72, column: 7)
!486 = !DILocation(line: 72, column: 7, scope: !148)
!487 = !DILocation(line: 73, column: 5, scope: !485)
!488 = !DILocation(line: 75, column: 3, scope: !148)
!489 = !DILocation(line: 75, column: 3, scope: !490)
!490 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 1)
!491 = distinct !DILexicalBlock(scope: !492, file: !1, line: 75, column: 3)
!492 = distinct !DILexicalBlock(scope: !148, file: !1, line: 75, column: 3)
!493 = !DILocation(line: 75, column: 3, scope: !494)
!494 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 2)
!495 = !DILocation(line: 75, column: 3, scope: !496)
!496 = !DILexicalBlockFile(scope: !492, file: !1, discriminator: 3)
!497 = !DILocation(line: 75, column: 3, scope: !498)
!498 = !DILexicalBlockFile(scope: !499, file: !1, discriminator: 4)
!499 = distinct !DILexicalBlock(scope: !492, file: !1, line: 75, column: 3)
!500 = !DILocation(line: 75, column: 3, scope: !501)
!501 = !DILexicalBlockFile(scope: !502, file: !1, discriminator: 5)
!502 = distinct !DILexicalBlock(scope: !492, file: !1, line: 75, column: 3)
!503 = !DILocation(line: 75, column: 3, scope: !504)
!504 = !DILexicalBlockFile(scope: !502, file: !1, discriminator: 6)
!505 = !DILocation(line: 75, column: 3, scope: !506)
!506 = !DILexicalBlockFile(scope: !507, file: !1, discriminator: 7)
!507 = distinct !DILexicalBlock(scope: !502, file: !1, line: 75, column: 3)
!508 = !DILocation(line: 75, column: 3, scope: !509)
!509 = !DILexicalBlockFile(scope: !507, file: !1, discriminator: 8)
!510 = !DILocation(line: 75, column: 3, scope: !511)
!511 = !DILexicalBlockFile(scope: !492, file: !1, discriminator: 9)
!512 = !DILocation(line: 76, column: 3, scope: !148)
!513 = !DILocation(line: 76, column: 9, scope: !148)
!514 = !DILocation(line: 76, column: 23, scope: !148)
!515 = !DILocation(line: 76, column: 29, scope: !148)
!516 = !DILocation(line: 77, column: 3, scope: !148)
!517 = !DILocation(line: 77, column: 3, scope: !518)
!518 = !DILexicalBlockFile(scope: !519, file: !1, discriminator: 1)
!519 = distinct !DILexicalBlock(scope: !148, file: !1, line: 77, column: 3)
!520 = !DILocation(line: 79, column: 25, scope: !148)
!521 = !DILocation(line: 79, column: 31, scope: !148)
!522 = !DILocation(line: 79, column: 9, scope: !148)
!523 = !DILocation(line: 79, column: 7, scope: !148)
!524 = !DILocation(line: 80, column: 7, scope: !525)
!525 = distinct !DILexicalBlock(scope: !148, file: !1, line: 80, column: 7)
!526 = !DILocation(line: 80, column: 7, scope: !148)
!527 = !DILocation(line: 81, column: 5, scope: !525)
!528 = !DILocation(line: 83, column: 24, scope: !148)
!529 = !DILocation(line: 83, column: 30, scope: !148)
!530 = !DILocation(line: 83, column: 9, scope: !148)
!531 = !DILocation(line: 83, column: 7, scope: !148)
!532 = !DILocation(line: 84, column: 7, scope: !533)
!533 = distinct !DILexicalBlock(scope: !148, file: !1, line: 84, column: 7)
!534 = !DILocation(line: 84, column: 7, scope: !148)
!535 = !DILocation(line: 85, column: 5, scope: !533)
!536 = !DILocation(line: 87, column: 23, scope: !148)
!537 = !DILocation(line: 87, column: 30, scope: !148)
!538 = !DILocation(line: 87, column: 36, scope: !148)
!539 = !DILocation(line: 87, column: 9, scope: !148)
!540 = !DILocation(line: 87, column: 7, scope: !148)
!541 = !DILocation(line: 88, column: 7, scope: !542)
!542 = distinct !DILexicalBlock(scope: !148, file: !1, line: 88, column: 7)
!543 = !DILocation(line: 88, column: 7, scope: !148)
!544 = !DILocation(line: 89, column: 5, scope: !542)
!545 = !DILocation(line: 91, column: 3, scope: !148)
!546 = !DILocation(line: 91, column: 3, scope: !547)
!547 = !DILexicalBlockFile(scope: !548, file: !1, discriminator: 1)
!548 = distinct !DILexicalBlock(scope: !549, file: !1, line: 91, column: 3)
!549 = distinct !DILexicalBlock(scope: !148, file: !1, line: 91, column: 3)
!550 = !DILocation(line: 91, column: 3, scope: !551)
!551 = !DILexicalBlockFile(scope: !548, file: !1, discriminator: 2)
!552 = !DILocation(line: 91, column: 3, scope: !553)
!553 = !DILexicalBlockFile(scope: !549, file: !1, discriminator: 3)
!554 = !DILocation(line: 91, column: 3, scope: !555)
!555 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 4)
!556 = distinct !DILexicalBlock(scope: !549, file: !1, line: 91, column: 3)
!557 = !DILocation(line: 91, column: 3, scope: !558)
!558 = !DILexicalBlockFile(scope: !559, file: !1, discriminator: 5)
!559 = distinct !DILexicalBlock(scope: !549, file: !1, line: 91, column: 3)
!560 = !DILocation(line: 91, column: 3, scope: !561)
!561 = !DILexicalBlockFile(scope: !559, file: !1, discriminator: 6)
!562 = !DILocation(line: 91, column: 3, scope: !563)
!563 = !DILexicalBlockFile(scope: !564, file: !1, discriminator: 7)
!564 = distinct !DILexicalBlock(scope: !559, file: !1, line: 91, column: 3)
!565 = !DILocation(line: 91, column: 3, scope: !566)
!566 = !DILexicalBlockFile(scope: !564, file: !1, discriminator: 8)
!567 = !DILocation(line: 91, column: 3, scope: !568)
!568 = !DILexicalBlockFile(scope: !549, file: !1, discriminator: 9)
!569 = !DILocation(line: 92, column: 3, scope: !148)
!570 = !DILocation(line: 92, column: 9, scope: !148)
!571 = !DILocation(line: 92, column: 18, scope: !148)
!572 = !DILocation(line: 92, column: 24, scope: !148)
!573 = !DILocation(line: 94, column: 3, scope: !148)
!574 = !DILocation(line: 97, column: 21, scope: !148)
!575 = !DILocation(line: 97, column: 27, scope: !148)
!576 = !DILocation(line: 97, column: 3, scope: !148)
!577 = !DILocation(line: 100, column: 22, scope: !148)
!578 = !DILocation(line: 100, column: 28, scope: !148)
!579 = !DILocation(line: 100, column: 3, scope: !148)
!580 = !DILocation(line: 103, column: 27, scope: !148)
!581 = !DILocation(line: 103, column: 3, scope: !148)
!582 = !DILocation(line: 106, column: 28, scope: !148)
!583 = !DILocation(line: 106, column: 3, scope: !148)
!584 = !DILocation(line: 108, column: 10, scope: !148)
!585 = !DILocation(line: 108, column: 3, scope: !148)
!586 = !DILocation(line: 109, column: 1, scope: !148)
!587 = !DILocalVariable(name: "heap", arg: 1, scope: !368, file: !126, line: 62, type: !124)
!588 = !DILocation(line: 62, column: 1, scope: !368)
!589 = !DILocation(line: 63, column: 3, scope: !368)
!590 = !DILocation(line: 63, column: 9, scope: !368)
!591 = !DILocation(line: 63, column: 13, scope: !368)
!592 = !DILocation(line: 64, column: 3, scope: !368)
!593 = !DILocation(line: 64, column: 9, scope: !368)
!594 = !DILocation(line: 64, column: 15, scope: !368)
!595 = !DILocation(line: 65, column: 1, scope: !368)
!596 = !DILocalVariable(name: "loop", arg: 1, scope: !371, file: !116, line: 306, type: !152)
!597 = !DILocation(line: 306, column: 1, scope: !371)
!598 = !DILocation(line: 309, column: 16, scope: !371)
!599 = !DILocation(line: 309, column: 42, scope: !371)
!600 = !DILocation(line: 309, column: 3, scope: !371)
!601 = !DILocation(line: 309, column: 9, scope: !371)
!602 = !DILocation(line: 309, column: 14, scope: !371)
!603 = !DILocation(line: 310, column: 1, scope: !371)
!604 = !DILocalVariable(name: "loop", arg: 1, scope: !353, file: !1, line: 112, type: !152)
!605 = !DILocation(line: 112, column: 29, scope: !353)
!606 = !DILocalVariable(name: "err", scope: !353, file: !1, line: 113, type: !151)
!607 = !DILocation(line: 113, column: 7, scope: !353)
!608 = !DILocalVariable(name: "i", scope: !353, file: !1, line: 114, type: !136)
!609 = !DILocation(line: 114, column: 16, scope: !353)
!610 = !DILocalVariable(name: "w", scope: !353, file: !1, line: 115, type: !168)
!611 = !DILocation(line: 115, column: 13, scope: !353)
!612 = !DILocation(line: 117, column: 21, scope: !353)
!613 = !DILocation(line: 117, column: 9, scope: !353)
!614 = !DILocation(line: 117, column: 7, scope: !353)
!615 = !DILocation(line: 118, column: 7, scope: !616)
!616 = distinct !DILexicalBlock(scope: !353, file: !1, line: 118, column: 7)
!617 = !DILocation(line: 118, column: 7, scope: !353)
!618 = !DILocation(line: 119, column: 12, scope: !616)
!619 = !DILocation(line: 119, column: 5, scope: !616)
!620 = !DILocation(line: 121, column: 24, scope: !353)
!621 = !DILocation(line: 121, column: 9, scope: !353)
!622 = !DILocation(line: 121, column: 7, scope: !353)
!623 = !DILocation(line: 122, column: 7, scope: !624)
!624 = distinct !DILexicalBlock(scope: !353, file: !1, line: 122, column: 7)
!625 = !DILocation(line: 122, column: 7, scope: !353)
!626 = !DILocation(line: 123, column: 12, scope: !624)
!627 = !DILocation(line: 123, column: 5, scope: !624)
!628 = !DILocation(line: 125, column: 30, scope: !353)
!629 = !DILocation(line: 125, column: 9, scope: !353)
!630 = !DILocation(line: 125, column: 7, scope: !353)
!631 = !DILocation(line: 126, column: 7, scope: !632)
!632 = distinct !DILexicalBlock(scope: !353, file: !1, line: 126, column: 7)
!633 = !DILocation(line: 126, column: 7, scope: !353)
!634 = !DILocation(line: 127, column: 12, scope: !632)
!635 = !DILocation(line: 127, column: 5, scope: !632)
!636 = !DILocation(line: 130, column: 10, scope: !637)
!637 = distinct !DILexicalBlock(scope: !353, file: !1, line: 130, column: 3)
!638 = !DILocation(line: 130, column: 8, scope: !637)
!639 = !DILocation(line: 130, column: 15, scope: !640)
!640 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 1)
!641 = distinct !DILexicalBlock(scope: !637, file: !1, line: 130, column: 3)
!642 = !DILocation(line: 130, column: 19, scope: !640)
!643 = !DILocation(line: 130, column: 25, scope: !640)
!644 = !DILocation(line: 130, column: 17, scope: !640)
!645 = !DILocation(line: 130, column: 3, scope: !640)
!646 = !DILocation(line: 131, column: 24, scope: !647)
!647 = distinct !DILexicalBlock(scope: !641, file: !1, line: 130, column: 41)
!648 = !DILocation(line: 131, column: 9, scope: !647)
!649 = !DILocation(line: 131, column: 15, scope: !647)
!650 = !DILocation(line: 131, column: 7, scope: !647)
!651 = !DILocation(line: 132, column: 9, scope: !652)
!652 = distinct !DILexicalBlock(scope: !647, file: !1, line: 132, column: 9)
!653 = !DILocation(line: 132, column: 11, scope: !652)
!654 = !DILocation(line: 132, column: 9, scope: !647)
!655 = !DILocation(line: 133, column: 7, scope: !652)
!656 = !DILocation(line: 135, column: 9, scope: !657)
!657 = distinct !DILexicalBlock(scope: !647, file: !1, line: 135, column: 9)
!658 = !DILocation(line: 135, column: 12, scope: !657)
!659 = !DILocation(line: 135, column: 20, scope: !657)
!660 = !DILocation(line: 135, column: 25, scope: !657)
!661 = !DILocation(line: 135, column: 28, scope: !662)
!662 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 1)
!663 = !DILocation(line: 135, column: 9, scope: !662)
!664 = !DILocation(line: 136, column: 7, scope: !665)
!665 = distinct !DILexicalBlock(scope: !657, file: !1, line: 135, column: 60)
!666 = !DILocation(line: 136, column: 10, scope: !665)
!667 = !DILocation(line: 136, column: 17, scope: !665)
!668 = !DILocation(line: 137, column: 7, scope: !665)
!669 = !DILocation(line: 137, column: 7, scope: !670)
!670 = !DILexicalBlockFile(scope: !671, file: !1, discriminator: 1)
!671 = distinct !DILexicalBlock(scope: !665, file: !1, line: 137, column: 7)
!672 = !DILocation(line: 138, column: 5, scope: !665)
!673 = !DILocation(line: 139, column: 3, scope: !647)
!674 = !DILocation(line: 130, column: 37, scope: !675)
!675 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 2)
!676 = !DILocation(line: 130, column: 3, scope: !675)
!677 = !DILocation(line: 141, column: 3, scope: !353)
!678 = !DILocation(line: 142, column: 1, scope: !353)
!679 = !DILocalVariable(name: "loop", arg: 1, scope: !354, file: !1, line: 145, type: !152)
!680 = !DILocation(line: 145, column: 32, scope: !354)
!681 = !DILocation(line: 146, column: 27, scope: !354)
!682 = !DILocation(line: 146, column: 3, scope: !354)
!683 = !DILocation(line: 147, column: 28, scope: !354)
!684 = !DILocation(line: 147, column: 3, scope: !354)
!685 = !DILocation(line: 148, column: 18, scope: !354)
!686 = !DILocation(line: 148, column: 3, scope: !354)
!687 = !DILocation(line: 150, column: 7, scope: !688)
!688 = distinct !DILexicalBlock(scope: !354, file: !1, line: 150, column: 7)
!689 = !DILocation(line: 150, column: 13, scope: !688)
!690 = !DILocation(line: 150, column: 23, scope: !688)
!691 = !DILocation(line: 150, column: 7, scope: !354)
!692 = !DILocation(line: 151, column: 15, scope: !693)
!693 = distinct !DILexicalBlock(scope: !688, file: !1, line: 150, column: 30)
!694 = !DILocation(line: 151, column: 21, scope: !693)
!695 = !DILocation(line: 151, column: 5, scope: !693)
!696 = !DILocation(line: 152, column: 5, scope: !693)
!697 = !DILocation(line: 152, column: 11, scope: !693)
!698 = !DILocation(line: 152, column: 21, scope: !693)
!699 = !DILocation(line: 153, column: 3, scope: !693)
!700 = !DILocation(line: 155, column: 7, scope: !701)
!701 = distinct !DILexicalBlock(scope: !354, file: !1, line: 155, column: 7)
!702 = !DILocation(line: 155, column: 13, scope: !701)
!703 = !DILocation(line: 155, column: 24, scope: !701)
!704 = !DILocation(line: 155, column: 7, scope: !354)
!705 = !DILocation(line: 156, column: 15, scope: !706)
!706 = distinct !DILexicalBlock(scope: !701, file: !1, line: 155, column: 31)
!707 = !DILocation(line: 156, column: 21, scope: !706)
!708 = !DILocation(line: 156, column: 5, scope: !706)
!709 = !DILocation(line: 157, column: 5, scope: !706)
!710 = !DILocation(line: 157, column: 11, scope: !706)
!711 = !DILocation(line: 157, column: 22, scope: !706)
!712 = !DILocation(line: 158, column: 3, scope: !706)
!713 = !DILocation(line: 160, column: 18, scope: !354)
!714 = !DILocation(line: 160, column: 24, scope: !354)
!715 = !DILocation(line: 160, column: 3, scope: !354)
!716 = !DILocation(line: 161, column: 3, scope: !354)
!717 = !DILocation(line: 161, column: 3, scope: !718)
!718 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 1)
!719 = !DILocation(line: 161, column: 3, scope: !720)
!720 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 2)
!721 = !DILocation(line: 161, column: 3, scope: !722)
!722 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 3)
!723 = !DILocation(line: 161, column: 3, scope: !724)
!724 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 4)
!725 = !DILocation(line: 162, column: 3, scope: !354)
!726 = !DILocation(line: 162, column: 3, scope: !718)
!727 = !DILocation(line: 162, column: 3, scope: !720)
!728 = !DILocation(line: 162, column: 3, scope: !722)
!729 = !DILocation(line: 163, column: 20, scope: !354)
!730 = !DILocation(line: 163, column: 26, scope: !354)
!731 = !DILocation(line: 163, column: 3, scope: !354)
!732 = !DILocation(line: 164, column: 21, scope: !354)
!733 = !DILocation(line: 164, column: 27, scope: !354)
!734 = !DILocation(line: 164, column: 3, scope: !354)
!735 = !DILocation(line: 170, column: 22, scope: !354)
!736 = !DILocation(line: 170, column: 28, scope: !354)
!737 = !DILocation(line: 170, column: 3, scope: !354)
!738 = !DILocation(line: 178, column: 12, scope: !354)
!739 = !DILocation(line: 178, column: 18, scope: !354)
!740 = !DILocation(line: 178, column: 3, scope: !354)
!741 = !DILocation(line: 179, column: 3, scope: !354)
!742 = !DILocation(line: 179, column: 9, scope: !354)
!743 = !DILocation(line: 179, column: 18, scope: !354)
!744 = !DILocation(line: 180, column: 3, scope: !354)
!745 = !DILocation(line: 180, column: 9, scope: !354)
!746 = !DILocation(line: 180, column: 19, scope: !354)
!747 = !DILocation(line: 181, column: 1, scope: !354)
!748 = !DILocalVariable(name: "loop", arg: 1, scope: !357, file: !1, line: 184, type: !152)
!749 = !DILocation(line: 184, column: 35, scope: !357)
!750 = !DILocalVariable(name: "option", arg: 2, scope: !357, file: !1, line: 184, type: !360)
!751 = !DILocation(line: 184, column: 56, scope: !357)
!752 = !DILocalVariable(name: "ap", arg: 3, scope: !357, file: !1, line: 184, type: !361)
!753 = !DILocation(line: 184, column: 72, scope: !357)
!754 = !DILocation(line: 185, column: 7, scope: !755)
!755 = distinct !DILexicalBlock(scope: !357, file: !1, line: 185, column: 7)
!756 = !DILocation(line: 185, column: 14, scope: !755)
!757 = !DILocation(line: 185, column: 7, scope: !357)
!758 = !DILocation(line: 186, column: 5, scope: !755)
!759 = !DILocation(line: 188, column: 7, scope: !760)
!760 = distinct !DILexicalBlock(scope: !357, file: !1, line: 188, column: 7)
!761 = !DILocation(line: 188, column: 7, scope: !762)
!762 = !DILexicalBlockFile(scope: !760, file: !1, discriminator: 1)
!763 = !DILocation(line: 188, column: 7, scope: !764)
!764 = !DILexicalBlockFile(scope: !760, file: !1, discriminator: 2)
!765 = !DILocation(line: 188, column: 7, scope: !766)
!766 = !DILexicalBlockFile(scope: !760, file: !1, discriminator: 3)
!767 = !DILocation(line: 188, column: 23, scope: !766)
!768 = !DILocation(line: 189, column: 5, scope: !760)
!769 = !DILocation(line: 191, column: 3, scope: !357)
!770 = !DILocation(line: 191, column: 9, scope: !357)
!771 = !DILocation(line: 191, column: 15, scope: !357)
!772 = !DILocation(line: 192, column: 3, scope: !357)
!773 = !DILocation(line: 193, column: 1, scope: !357)
