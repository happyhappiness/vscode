; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/loop-watcher.c'
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
%struct.uv_prepare_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, void (%struct.uv_prepare_s*)*, [2 x i8*] }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_check_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, void (%struct.uv_check_s*)*, [2 x i8*] }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_idle_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.6, %struct.uv_handle_s*, i32, void (%struct.uv_idle_s*)*, [2 x i8*] }
%union.anon.6 = type { [4 x i8*] }

@.str = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.1 = private unnamed_addr constant [76 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/loop-watcher.c\00", align 1
@__PRETTY_FUNCTION__.uv_prepare_start = private unnamed_addr constant [52 x i8] c"int uv_prepare_start(uv_prepare_t *, uv_prepare_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_prepare_stop = private unnamed_addr constant [36 x i8] c"int uv_prepare_stop(uv_prepare_t *)\00", align 1
@__PRETTY_FUNCTION__.uv_check_start = private unnamed_addr constant [46 x i8] c"int uv_check_start(uv_check_t *, uv_check_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_check_stop = private unnamed_addr constant [32 x i8] c"int uv_check_stop(uv_check_t *)\00", align 1
@__PRETTY_FUNCTION__.uv_idle_start = private unnamed_addr constant [43 x i8] c"int uv_idle_start(uv_idle_t *, uv_idle_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_idle_stop = private unnamed_addr constant [30 x i8] c"int uv_idle_stop(uv_idle_t *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_prepare_init(%struct.uv_loop_s* %loop, %struct.uv_prepare_s* %handle) #0 !dbg !314 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_prepare_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !353, metadata !354), !dbg !355
  store %struct.uv_prepare_s* %handle, %struct.uv_prepare_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_prepare_s** %handle.addr, metadata !356, metadata !354), !dbg !355
  br label %do.body, !dbg !355

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !357
  %1 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !357
  %2 = bitcast %struct.uv_prepare_s* %1 to %struct.uv_handle_s*, !dbg !357
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !357
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !357
  %3 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !357
  %4 = bitcast %struct.uv_prepare_s* %3 to %struct.uv_handle_s*, !dbg !357
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !357
  store i32 9, i32* %type, align 8, !dbg !357
  %5 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !357
  %6 = bitcast %struct.uv_prepare_s* %5 to %struct.uv_handle_s*, !dbg !357
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !357
  store i32 8192, i32* %flags, align 8, !dbg !357
  br label %do.body2, !dbg !357

do.body2:                                         ; preds = %do.body
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !360
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 2, !dbg !360
  %8 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !360
  %9 = bitcast %struct.uv_prepare_s* %8 to %struct.uv_handle_s*, !dbg !360
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 4, !dbg !360
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !360
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !360
  store [2 x i8*]* %handle_queue, [2 x i8*]** %10, align 8, !dbg !360
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !360
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 2, !dbg !360
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !360
  %12 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !360
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !360
  %14 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !360
  %15 = bitcast %struct.uv_prepare_s* %14 to %struct.uv_handle_s*, !dbg !360
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 4, !dbg !360
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !360
  %16 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !360
  store [2 x i8*]* %13, [2 x i8*]** %16, align 8, !dbg !360
  %17 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !360
  %18 = bitcast %struct.uv_prepare_s* %17 to %struct.uv_handle_s*, !dbg !360
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !360
  %19 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !360
  %20 = bitcast %struct.uv_prepare_s* %19 to %struct.uv_handle_s*, !dbg !360
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 4, !dbg !360
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !360
  %21 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !360
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !360
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !360
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !360
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %23, align 8, !dbg !360
  %24 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !360
  %25 = bitcast %struct.uv_prepare_s* %24 to %struct.uv_handle_s*, !dbg !360
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !360
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !360
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 2, !dbg !360
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !360
  %27 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !360
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %27, align 8, !dbg !360
  br label %do.end, !dbg !360

do.end:                                           ; preds = %do.body2
  %28 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !363
  %29 = bitcast %struct.uv_prepare_s* %28 to %struct.uv_handle_s*, !dbg !363
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 6, !dbg !363
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !363
  br label %do.end15, !dbg !363

do.end15:                                         ; preds = %do.end
  %30 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !365
  %prepare_cb = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %30, i32 0, i32 8, !dbg !365
  store void (%struct.uv_prepare_s*)* null, void (%struct.uv_prepare_s*)** %prepare_cb, align 8, !dbg !365
  ret i32 0, !dbg !365
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @uv_prepare_start(%struct.uv_prepare_s* %handle, void (%struct.uv_prepare_s*)* %cb) #0 !dbg !318 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_prepare_s*, align 8
  %cb.addr = alloca void (%struct.uv_prepare_s*)*, align 8
  store %struct.uv_prepare_s* %handle, %struct.uv_prepare_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_prepare_s** %handle.addr, metadata !367, metadata !354), !dbg !368
  store void (%struct.uv_prepare_s*)* %cb, void (%struct.uv_prepare_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_prepare_s*)** %cb.addr, metadata !369, metadata !354), !dbg !368
  %0 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !370
  %flags = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %0, i32 0, i32 7, !dbg !370
  %1 = load i32, i32* %flags, align 8, !dbg !370
  %and = and i32 %1, 16384, !dbg !370
  %cmp = icmp ne i32 %and, 0, !dbg !370
  br i1 %cmp, label %if.then, label %if.end, !dbg !368

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !372
  br label %return, !dbg !372

if.end:                                           ; preds = %entry
  %2 = load void (%struct.uv_prepare_s*)*, void (%struct.uv_prepare_s*)** %cb.addr, align 8, !dbg !374
  %cmp1 = icmp eq void (%struct.uv_prepare_s*)* %2, null, !dbg !374
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !374

if.then2:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !377
  br label %return, !dbg !377

if.end3:                                          ; preds = %if.end
  br label %do.body, !dbg !379

do.body:                                          ; preds = %if.end3
  %3 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %loop = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %3, i32 0, i32 1, !dbg !381
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !381
  %prepare_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 18, !dbg !381
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles, i64 0, i64 0, !dbg !381
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !381
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !381
  %7 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %queue = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %7, i32 0, i32 9, !dbg !381
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !381
  %8 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !381
  store [2 x i8*]* %6, [2 x i8*]** %8, align 8, !dbg !381
  %9 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %loop5 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %9, i32 0, i32 1, !dbg !381
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop5, align 8, !dbg !381
  %prepare_handles6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 18, !dbg !381
  %11 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %queue7 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %11, i32 0, i32 9, !dbg !381
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue7, i64 0, i64 1, !dbg !381
  %12 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !381
  store [2 x i8*]* %prepare_handles6, [2 x i8*]** %12, align 8, !dbg !381
  %13 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %queue9 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %13, i32 0, i32 9, !dbg !381
  %14 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %queue10 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %14, i32 0, i32 9, !dbg !381
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue10, i64 0, i64 0, !dbg !381
  %15 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !381
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !381
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %16, i64 0, i64 1, !dbg !381
  %17 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !381
  store [2 x i8*]* %queue9, [2 x i8*]** %17, align 8, !dbg !381
  %18 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %queue13 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %18, i32 0, i32 9, !dbg !381
  %19 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !381
  %loop14 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %19, i32 0, i32 1, !dbg !381
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop14, align 8, !dbg !381
  %prepare_handles15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 18, !dbg !381
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles15, i64 0, i64 0, !dbg !381
  %21 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !381
  store [2 x i8*]* %queue13, [2 x i8*]** %21, align 8, !dbg !381
  br label %do.end, !dbg !381

do.end:                                           ; preds = %do.body
  %22 = load void (%struct.uv_prepare_s*)*, void (%struct.uv_prepare_s*)** %cb.addr, align 8, !dbg !384
  %23 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !384
  %prepare_cb = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %23, i32 0, i32 8, !dbg !384
  store void (%struct.uv_prepare_s*)* %22, void (%struct.uv_prepare_s*)** %prepare_cb, align 8, !dbg !384
  br label %do.body17, !dbg !384

do.body17:                                        ; preds = %do.end
  %24 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !386
  %flags18 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %24, i32 0, i32 7, !dbg !386
  %25 = load i32, i32* %flags18, align 8, !dbg !386
  %and19 = and i32 %25, 0, !dbg !386
  %cmp20 = icmp eq i32 %and19, 0, !dbg !386
  br i1 %cmp20, label %cond.true, label %cond.false, !dbg !386

cond.true:                                        ; preds = %do.body17
  br label %cond.end, !dbg !389

cond.false:                                       ; preds = %do.body17
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.1, i32 0, i32 0), i32 66, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @__PRETTY_FUNCTION__.uv_prepare_start, i32 0, i32 0)) #3, !dbg !391
  unreachable, !dbg !391
                                                  ; No predecessors!
  br label %cond.end, !dbg !393

cond.end:                                         ; preds = %26, %cond.true
  %27 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !395
  %flags21 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %27, i32 0, i32 7, !dbg !395
  %28 = load i32, i32* %flags21, align 8, !dbg !395
  %and22 = and i32 %28, 16384, !dbg !395
  %cmp23 = icmp ne i32 %and22, 0, !dbg !395
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !395

if.then24:                                        ; preds = %cond.end
  br label %do.end35, !dbg !398

if.end25:                                         ; preds = %cond.end
  %29 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !400
  %flags26 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %29, i32 0, i32 7, !dbg !400
  %30 = load i32, i32* %flags26, align 8, !dbg !400
  %or = or i32 %30, 16384, !dbg !400
  store i32 %or, i32* %flags26, align 8, !dbg !400
  %31 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !400
  %flags27 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %31, i32 0, i32 7, !dbg !400
  %32 = load i32, i32* %flags27, align 8, !dbg !400
  %and28 = and i32 %32, 8192, !dbg !400
  %cmp29 = icmp ne i32 %and28, 0, !dbg !400
  br i1 %cmp29, label %if.then30, label %if.end34, !dbg !400

if.then30:                                        ; preds = %if.end25
  br label %do.body31, !dbg !402

do.body31:                                        ; preds = %if.then30
  %33 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !405
  %loop32 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %33, i32 0, i32 1, !dbg !405
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop32, align 8, !dbg !405
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 1, !dbg !405
  %35 = load i32, i32* %active_handles, align 8, !dbg !405
  %inc = add i32 %35, 1, !dbg !405
  store i32 %inc, i32* %active_handles, align 8, !dbg !405
  br label %do.end33, !dbg !405

do.end33:                                         ; preds = %do.body31
  br label %if.end34, !dbg !408

if.end34:                                         ; preds = %do.end33, %if.end25
  br label %do.end35, !dbg !410

do.end35:                                         ; preds = %if.end34, %if.then24
  store i32 0, i32* %retval, align 4, !dbg !412
  br label %return, !dbg !412

return:                                           ; preds = %do.end35, %if.then2, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !414
  ret i32 %36, !dbg !414
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_prepare_stop(%struct.uv_prepare_s* %handle) #0 !dbg !321 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_prepare_s*, align 8
  store %struct.uv_prepare_s* %handle, %struct.uv_prepare_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_prepare_s** %handle.addr, metadata !416, metadata !354), !dbg !417
  %0 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !418
  %flags = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %0, i32 0, i32 7, !dbg !418
  %1 = load i32, i32* %flags, align 8, !dbg !418
  %and = and i32 %1, 16384, !dbg !418
  %cmp = icmp ne i32 %and, 0, !dbg !418
  br i1 %cmp, label %if.end, label %if.then, !dbg !417

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !420
  br label %return, !dbg !420

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !422

do.body:                                          ; preds = %if.end
  %2 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !424
  %queue = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %2, i32 0, i32 9, !dbg !424
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !424
  %3 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !424
  %4 = load [2 x i8*]*, [2 x i8*]** %3, align 8, !dbg !424
  %5 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !424
  %queue1 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %5, i32 0, i32 9, !dbg !424
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue1, i64 0, i64 1, !dbg !424
  %6 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !424
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !424
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !424
  %8 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !424
  store [2 x i8*]* %4, [2 x i8*]** %8, align 8, !dbg !424
  %9 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !424
  %queue4 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %9, i32 0, i32 9, !dbg !424
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue4, i64 0, i64 1, !dbg !424
  %10 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !424
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !424
  %12 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !424
  %queue6 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %12, i32 0, i32 9, !dbg !424
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue6, i64 0, i64 0, !dbg !424
  %13 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !424
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !424
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 1, !dbg !424
  %15 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !424
  store [2 x i8*]* %11, [2 x i8*]** %15, align 8, !dbg !424
  br label %do.end, !dbg !424

do.end:                                           ; preds = %do.body
  br label %do.body9, !dbg !427

do.body9:                                         ; preds = %do.end
  %16 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !429
  %flags10 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %16, i32 0, i32 7, !dbg !429
  %17 = load i32, i32* %flags10, align 8, !dbg !429
  %and11 = and i32 %17, 0, !dbg !429
  %cmp12 = icmp eq i32 %and11, 0, !dbg !429
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !429

cond.true:                                        ; preds = %do.body9
  br label %cond.end, !dbg !432

cond.false:                                       ; preds = %do.body9
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.1, i32 0, i32 0), i32 66, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @__PRETTY_FUNCTION__.uv_prepare_stop, i32 0, i32 0)) #3, !dbg !434
  unreachable, !dbg !434
                                                  ; No predecessors!
  br label %cond.end, !dbg !436

cond.end:                                         ; preds = %18, %cond.true
  %19 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !438
  %flags13 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %19, i32 0, i32 7, !dbg !438
  %20 = load i32, i32* %flags13, align 8, !dbg !438
  %and14 = and i32 %20, 16384, !dbg !438
  %cmp15 = icmp eq i32 %and14, 0, !dbg !438
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !438

if.then16:                                        ; preds = %cond.end
  br label %do.end27, !dbg !441

if.end17:                                         ; preds = %cond.end
  %21 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !443
  %flags18 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %21, i32 0, i32 7, !dbg !443
  %22 = load i32, i32* %flags18, align 8, !dbg !443
  %and19 = and i32 %22, -16385, !dbg !443
  store i32 %and19, i32* %flags18, align 8, !dbg !443
  %23 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !443
  %flags20 = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %23, i32 0, i32 7, !dbg !443
  %24 = load i32, i32* %flags20, align 8, !dbg !443
  %and21 = and i32 %24, 8192, !dbg !443
  %cmp22 = icmp ne i32 %and21, 0, !dbg !443
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !443

if.then23:                                        ; preds = %if.end17
  br label %do.body24, !dbg !445

do.body24:                                        ; preds = %if.then23
  %25 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !448
  %loop = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %25, i32 0, i32 1, !dbg !448
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !448
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 1, !dbg !448
  %27 = load i32, i32* %active_handles, align 8, !dbg !448
  %dec = add i32 %27, -1, !dbg !448
  store i32 %dec, i32* %active_handles, align 8, !dbg !448
  br label %do.end25, !dbg !448

do.end25:                                         ; preds = %do.body24
  br label %if.end26, !dbg !451

if.end26:                                         ; preds = %do.end25, %if.end17
  br label %do.end27, !dbg !453

do.end27:                                         ; preds = %if.end26, %if.then16
  store i32 0, i32* %retval, align 4, !dbg !455
  br label %return, !dbg !455

return:                                           ; preds = %do.end27, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !457
  ret i32 %28, !dbg !457
}

; Function Attrs: nounwind uwtable
define void @uv__run_prepare(%struct.uv_loop_s* %loop) #0 !dbg !324 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %h = alloca %struct.uv_prepare_s*, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %q5 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !459, metadata !354), !dbg !460
  call void @llvm.dbg.declare(metadata %struct.uv_prepare_s** %h, metadata !461, metadata !354), !dbg !460
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !462, metadata !354), !dbg !460
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !463, metadata !354), !dbg !460
  br label %do.body, !dbg !460

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !464
  %prepare_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 18, !dbg !464
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !464
  %prepare_handles1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 18, !dbg !464
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles1, i64 0, i64 0, !dbg !464
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !464
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !464
  %cmp = icmp eq [2 x i8*]* %prepare_handles, %3, !dbg !464
  br i1 %cmp, label %if.then, label %if.else, !dbg !464

if.then:                                          ; preds = %do.body
  br label %do.body2, !dbg !468

do.body2:                                         ; preds = %if.then
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !470
  %4 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !470
  store [2 x i8*]* %queue, [2 x i8*]** %4, align 16, !dbg !470
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !470
  %5 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !470
  store [2 x i8*]* %queue, [2 x i8*]** %5, align 8, !dbg !470
  br label %do.end, !dbg !470

do.end:                                           ; preds = %do.body2
  br label %if.end, !dbg !473

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q5, metadata !475, metadata !354), !dbg !477
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !478
  %prepare_handles6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 18, !dbg !478
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles6, i64 0, i64 0, !dbg !478
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !478
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !478
  store [2 x i8*]* %8, [2 x i8*]** %q5, align 8, !dbg !478
  br label %do.body8, !dbg !478

do.body8:                                         ; preds = %if.else
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !480
  %prepare_handles9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 18, !dbg !480
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles9, i64 0, i64 1, !dbg !480
  %10 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !480
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !480
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !480
  %12 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !480
  store [2 x i8*]* %11, [2 x i8*]** %12, align 8, !dbg !480
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !480
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !480
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !480
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !480
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !480
  store [2 x i8*]* %queue, [2 x i8*]** %15, align 8, !dbg !480
  %16 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !480
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !480
  %17 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !480
  store [2 x i8*]* %16, [2 x i8*]** %17, align 16, !dbg !480
  %18 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !480
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 1, !dbg !480
  %19 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !480
  %20 = load [2 x i8*]*, [2 x i8*]** %19, align 8, !dbg !480
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !480
  %prepare_handles16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 18, !dbg !480
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles16, i64 0, i64 1, !dbg !480
  %22 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !480
  store [2 x i8*]* %20, [2 x i8*]** %22, align 8, !dbg !480
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !480
  %prepare_handles18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 18, !dbg !480
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !480
  %prepare_handles19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 18, !dbg !480
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles19, i64 0, i64 1, !dbg !480
  %25 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !480
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !480
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %26, i64 0, i64 0, !dbg !480
  %27 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !480
  store [2 x i8*]* %prepare_handles18, [2 x i8*]** %27, align 8, !dbg !480
  %28 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !480
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %28, i64 0, i64 1, !dbg !480
  %29 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !480
  store [2 x i8*]* %queue, [2 x i8*]** %29, align 8, !dbg !480
  br label %do.end23, !dbg !480

do.end23:                                         ; preds = %do.body8
  br label %if.end

if.end:                                           ; preds = %do.end23, %do.end
  br label %do.end24, !dbg !483

do.end24:                                         ; preds = %if.end
  br label %while.cond, !dbg !485

while.cond:                                       ; preds = %do.end46, %do.end24
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !487
  %30 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !487
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 16, !dbg !487
  %cmp26 = icmp eq [2 x i8*]* %queue, %31, !dbg !487
  %lnot = xor i1 %cmp26, true, !dbg !487
  br i1 %lnot, label %while.body, label %while.end, !dbg !487

while.body:                                       ; preds = %while.cond
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !489
  %32 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !489
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 16, !dbg !489
  store [2 x i8*]* %33, [2 x i8*]** %q, align 8, !dbg !489
  %34 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !489
  %35 = bitcast [2 x i8*]* %34 to i8*, !dbg !489
  %add.ptr = getelementptr inbounds i8, i8* %35, i64 -104, !dbg !489
  %36 = bitcast i8* %add.ptr to %struct.uv_prepare_s*, !dbg !489
  store %struct.uv_prepare_s* %36, %struct.uv_prepare_s** %h, align 8, !dbg !489
  br label %do.body28, !dbg !489

do.body28:                                        ; preds = %while.body
  %37 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !492
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 0, !dbg !492
  %38 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !492
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !492
  %40 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !492
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 1, !dbg !492
  %41 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !492
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 8, !dbg !492
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 0, !dbg !492
  %43 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !492
  store [2 x i8*]* %39, [2 x i8*]** %43, align 8, !dbg !492
  %44 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !492
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %44, i64 0, i64 1, !dbg !492
  %45 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !492
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !492
  %47 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !492
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !492
  %48 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !492
  %49 = load [2 x i8*]*, [2 x i8*]** %48, align 8, !dbg !492
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %49, i64 0, i64 1, !dbg !492
  %50 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !492
  store [2 x i8*]* %46, [2 x i8*]** %50, align 8, !dbg !492
  br label %do.end35, !dbg !492

do.end35:                                         ; preds = %do.body28
  br label %do.body36, !dbg !495

do.body36:                                        ; preds = %do.end35
  %51 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !497
  %prepare_handles37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %51, i32 0, i32 18, !dbg !497
  %52 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !497
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %52, i64 0, i64 0, !dbg !497
  %53 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !497
  store [2 x i8*]* %prepare_handles37, [2 x i8*]** %53, align 8, !dbg !497
  %54 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !497
  %prepare_handles39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %54, i32 0, i32 18, !dbg !497
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles39, i64 0, i64 1, !dbg !497
  %55 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !497
  %56 = load [2 x i8*]*, [2 x i8*]** %55, align 8, !dbg !497
  %57 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !497
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !497
  %58 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !497
  store [2 x i8*]* %56, [2 x i8*]** %58, align 8, !dbg !497
  %59 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !497
  %60 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !497
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !497
  %61 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !497
  %62 = load [2 x i8*]*, [2 x i8*]** %61, align 8, !dbg !497
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !497
  %63 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !497
  store [2 x i8*]* %59, [2 x i8*]** %63, align 8, !dbg !497
  %64 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !497
  %65 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !497
  %prepare_handles44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %65, i32 0, i32 18, !dbg !497
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %prepare_handles44, i64 0, i64 1, !dbg !497
  %66 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !497
  store [2 x i8*]* %64, [2 x i8*]** %66, align 8, !dbg !497
  br label %do.end46, !dbg !497

do.end46:                                         ; preds = %do.body36
  %67 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %h, align 8, !dbg !500
  %prepare_cb = getelementptr inbounds %struct.uv_prepare_s, %struct.uv_prepare_s* %67, i32 0, i32 8, !dbg !500
  %68 = load void (%struct.uv_prepare_s*)*, void (%struct.uv_prepare_s*)** %prepare_cb, align 8, !dbg !500
  %69 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %h, align 8, !dbg !500
  call void %68(%struct.uv_prepare_s* %69), !dbg !500
  br label %while.cond, !dbg !500

while.end:                                        ; preds = %while.cond
  ret void, !dbg !502
}

; Function Attrs: nounwind uwtable
define void @uv__prepare_close(%struct.uv_prepare_s* %handle) #0 !dbg !327 {
entry:
  %handle.addr = alloca %struct.uv_prepare_s*, align 8
  store %struct.uv_prepare_s* %handle, %struct.uv_prepare_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_prepare_s** %handle.addr, metadata !504, metadata !354), !dbg !505
  %0 = load %struct.uv_prepare_s*, %struct.uv_prepare_s** %handle.addr, align 8, !dbg !505
  %call = call i32 @uv_prepare_stop(%struct.uv_prepare_s* %0), !dbg !505
  ret void, !dbg !505
}

; Function Attrs: nounwind uwtable
define i32 @uv_check_init(%struct.uv_loop_s* %loop, %struct.uv_check_s* %handle) #0 !dbg !328 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_check_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !506, metadata !354), !dbg !507
  store %struct.uv_check_s* %handle, %struct.uv_check_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_check_s** %handle.addr, metadata !508, metadata !354), !dbg !507
  br label %do.body, !dbg !507

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !509
  %1 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !509
  %2 = bitcast %struct.uv_check_s* %1 to %struct.uv_handle_s*, !dbg !509
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !509
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !509
  %3 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !509
  %4 = bitcast %struct.uv_check_s* %3 to %struct.uv_handle_s*, !dbg !509
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !509
  store i32 2, i32* %type, align 8, !dbg !509
  %5 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !509
  %6 = bitcast %struct.uv_check_s* %5 to %struct.uv_handle_s*, !dbg !509
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !509
  store i32 8192, i32* %flags, align 8, !dbg !509
  br label %do.body2, !dbg !509

do.body2:                                         ; preds = %do.body
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !512
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 2, !dbg !512
  %8 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !512
  %9 = bitcast %struct.uv_check_s* %8 to %struct.uv_handle_s*, !dbg !512
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 4, !dbg !512
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !512
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !512
  store [2 x i8*]* %handle_queue, [2 x i8*]** %10, align 8, !dbg !512
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !512
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 2, !dbg !512
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !512
  %12 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !512
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !512
  %14 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !512
  %15 = bitcast %struct.uv_check_s* %14 to %struct.uv_handle_s*, !dbg !512
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 4, !dbg !512
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !512
  %16 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !512
  store [2 x i8*]* %13, [2 x i8*]** %16, align 8, !dbg !512
  %17 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !512
  %18 = bitcast %struct.uv_check_s* %17 to %struct.uv_handle_s*, !dbg !512
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !512
  %19 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !512
  %20 = bitcast %struct.uv_check_s* %19 to %struct.uv_handle_s*, !dbg !512
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 4, !dbg !512
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !512
  %21 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !512
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !512
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !512
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !512
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %23, align 8, !dbg !512
  %24 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !512
  %25 = bitcast %struct.uv_check_s* %24 to %struct.uv_handle_s*, !dbg !512
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !512
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !512
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 2, !dbg !512
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !512
  %27 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !512
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %27, align 8, !dbg !512
  br label %do.end, !dbg !512

do.end:                                           ; preds = %do.body2
  %28 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !515
  %29 = bitcast %struct.uv_check_s* %28 to %struct.uv_handle_s*, !dbg !515
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 6, !dbg !515
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !515
  br label %do.end15, !dbg !515

do.end15:                                         ; preds = %do.end
  %30 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !517
  %check_cb = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %30, i32 0, i32 8, !dbg !517
  store void (%struct.uv_check_s*)* null, void (%struct.uv_check_s*)** %check_cb, align 8, !dbg !517
  ret i32 0, !dbg !517
}

; Function Attrs: nounwind uwtable
define i32 @uv_check_start(%struct.uv_check_s* %handle, void (%struct.uv_check_s*)* %cb) #0 !dbg !331 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_check_s*, align 8
  %cb.addr = alloca void (%struct.uv_check_s*)*, align 8
  store %struct.uv_check_s* %handle, %struct.uv_check_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_check_s** %handle.addr, metadata !519, metadata !354), !dbg !520
  store void (%struct.uv_check_s*)* %cb, void (%struct.uv_check_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_check_s*)** %cb.addr, metadata !521, metadata !354), !dbg !520
  %0 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !522
  %flags = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %0, i32 0, i32 7, !dbg !522
  %1 = load i32, i32* %flags, align 8, !dbg !522
  %and = and i32 %1, 16384, !dbg !522
  %cmp = icmp ne i32 %and, 0, !dbg !522
  br i1 %cmp, label %if.then, label %if.end, !dbg !520

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !524
  br label %return, !dbg !524

if.end:                                           ; preds = %entry
  %2 = load void (%struct.uv_check_s*)*, void (%struct.uv_check_s*)** %cb.addr, align 8, !dbg !526
  %cmp1 = icmp eq void (%struct.uv_check_s*)* %2, null, !dbg !526
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !526

if.then2:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !529
  br label %return, !dbg !529

if.end3:                                          ; preds = %if.end
  br label %do.body, !dbg !531

do.body:                                          ; preds = %if.end3
  %3 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %loop = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %3, i32 0, i32 1, !dbg !533
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !533
  %check_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 19, !dbg !533
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles, i64 0, i64 0, !dbg !533
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !533
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !533
  %7 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %queue = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %7, i32 0, i32 9, !dbg !533
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !533
  %8 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !533
  store [2 x i8*]* %6, [2 x i8*]** %8, align 8, !dbg !533
  %9 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %loop5 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %9, i32 0, i32 1, !dbg !533
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop5, align 8, !dbg !533
  %check_handles6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 19, !dbg !533
  %11 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %queue7 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %11, i32 0, i32 9, !dbg !533
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue7, i64 0, i64 1, !dbg !533
  %12 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !533
  store [2 x i8*]* %check_handles6, [2 x i8*]** %12, align 8, !dbg !533
  %13 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %queue9 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %13, i32 0, i32 9, !dbg !533
  %14 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %queue10 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %14, i32 0, i32 9, !dbg !533
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue10, i64 0, i64 0, !dbg !533
  %15 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !533
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !533
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %16, i64 0, i64 1, !dbg !533
  %17 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !533
  store [2 x i8*]* %queue9, [2 x i8*]** %17, align 8, !dbg !533
  %18 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %queue13 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %18, i32 0, i32 9, !dbg !533
  %19 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !533
  %loop14 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %19, i32 0, i32 1, !dbg !533
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop14, align 8, !dbg !533
  %check_handles15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 19, !dbg !533
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles15, i64 0, i64 0, !dbg !533
  %21 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !533
  store [2 x i8*]* %queue13, [2 x i8*]** %21, align 8, !dbg !533
  br label %do.end, !dbg !533

do.end:                                           ; preds = %do.body
  %22 = load void (%struct.uv_check_s*)*, void (%struct.uv_check_s*)** %cb.addr, align 8, !dbg !536
  %23 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !536
  %check_cb = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %23, i32 0, i32 8, !dbg !536
  store void (%struct.uv_check_s*)* %22, void (%struct.uv_check_s*)** %check_cb, align 8, !dbg !536
  br label %do.body17, !dbg !536

do.body17:                                        ; preds = %do.end
  %24 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !538
  %flags18 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %24, i32 0, i32 7, !dbg !538
  %25 = load i32, i32* %flags18, align 8, !dbg !538
  %and19 = and i32 %25, 0, !dbg !538
  %cmp20 = icmp eq i32 %and19, 0, !dbg !538
  br i1 %cmp20, label %cond.true, label %cond.false, !dbg !538

cond.true:                                        ; preds = %do.body17
  br label %cond.end, !dbg !541

cond.false:                                       ; preds = %do.body17
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.1, i32 0, i32 0), i32 67, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @__PRETTY_FUNCTION__.uv_check_start, i32 0, i32 0)) #3, !dbg !543
  unreachable, !dbg !543
                                                  ; No predecessors!
  br label %cond.end, !dbg !545

cond.end:                                         ; preds = %26, %cond.true
  %27 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !547
  %flags21 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %27, i32 0, i32 7, !dbg !547
  %28 = load i32, i32* %flags21, align 8, !dbg !547
  %and22 = and i32 %28, 16384, !dbg !547
  %cmp23 = icmp ne i32 %and22, 0, !dbg !547
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !547

if.then24:                                        ; preds = %cond.end
  br label %do.end35, !dbg !550

if.end25:                                         ; preds = %cond.end
  %29 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !552
  %flags26 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %29, i32 0, i32 7, !dbg !552
  %30 = load i32, i32* %flags26, align 8, !dbg !552
  %or = or i32 %30, 16384, !dbg !552
  store i32 %or, i32* %flags26, align 8, !dbg !552
  %31 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !552
  %flags27 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %31, i32 0, i32 7, !dbg !552
  %32 = load i32, i32* %flags27, align 8, !dbg !552
  %and28 = and i32 %32, 8192, !dbg !552
  %cmp29 = icmp ne i32 %and28, 0, !dbg !552
  br i1 %cmp29, label %if.then30, label %if.end34, !dbg !552

if.then30:                                        ; preds = %if.end25
  br label %do.body31, !dbg !554

do.body31:                                        ; preds = %if.then30
  %33 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !557
  %loop32 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %33, i32 0, i32 1, !dbg !557
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop32, align 8, !dbg !557
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 1, !dbg !557
  %35 = load i32, i32* %active_handles, align 8, !dbg !557
  %inc = add i32 %35, 1, !dbg !557
  store i32 %inc, i32* %active_handles, align 8, !dbg !557
  br label %do.end33, !dbg !557

do.end33:                                         ; preds = %do.body31
  br label %if.end34, !dbg !560

if.end34:                                         ; preds = %do.end33, %if.end25
  br label %do.end35, !dbg !562

do.end35:                                         ; preds = %if.end34, %if.then24
  store i32 0, i32* %retval, align 4, !dbg !564
  br label %return, !dbg !564

return:                                           ; preds = %do.end35, %if.then2, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !566
  ret i32 %36, !dbg !566
}

; Function Attrs: nounwind uwtable
define i32 @uv_check_stop(%struct.uv_check_s* %handle) #0 !dbg !334 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_check_s*, align 8
  store %struct.uv_check_s* %handle, %struct.uv_check_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_check_s** %handle.addr, metadata !568, metadata !354), !dbg !569
  %0 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !570
  %flags = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %0, i32 0, i32 7, !dbg !570
  %1 = load i32, i32* %flags, align 8, !dbg !570
  %and = and i32 %1, 16384, !dbg !570
  %cmp = icmp ne i32 %and, 0, !dbg !570
  br i1 %cmp, label %if.end, label %if.then, !dbg !569

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !572
  br label %return, !dbg !572

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !574

do.body:                                          ; preds = %if.end
  %2 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !576
  %queue = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %2, i32 0, i32 9, !dbg !576
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !576
  %3 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !576
  %4 = load [2 x i8*]*, [2 x i8*]** %3, align 8, !dbg !576
  %5 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !576
  %queue1 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %5, i32 0, i32 9, !dbg !576
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue1, i64 0, i64 1, !dbg !576
  %6 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !576
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !576
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !576
  %8 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !576
  store [2 x i8*]* %4, [2 x i8*]** %8, align 8, !dbg !576
  %9 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !576
  %queue4 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %9, i32 0, i32 9, !dbg !576
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue4, i64 0, i64 1, !dbg !576
  %10 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !576
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !576
  %12 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !576
  %queue6 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %12, i32 0, i32 9, !dbg !576
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue6, i64 0, i64 0, !dbg !576
  %13 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !576
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !576
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 1, !dbg !576
  %15 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !576
  store [2 x i8*]* %11, [2 x i8*]** %15, align 8, !dbg !576
  br label %do.end, !dbg !576

do.end:                                           ; preds = %do.body
  br label %do.body9, !dbg !579

do.body9:                                         ; preds = %do.end
  %16 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !581
  %flags10 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %16, i32 0, i32 7, !dbg !581
  %17 = load i32, i32* %flags10, align 8, !dbg !581
  %and11 = and i32 %17, 0, !dbg !581
  %cmp12 = icmp eq i32 %and11, 0, !dbg !581
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !581

cond.true:                                        ; preds = %do.body9
  br label %cond.end, !dbg !584

cond.false:                                       ; preds = %do.body9
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.1, i32 0, i32 0), i32 67, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.uv_check_stop, i32 0, i32 0)) #3, !dbg !586
  unreachable, !dbg !586
                                                  ; No predecessors!
  br label %cond.end, !dbg !588

cond.end:                                         ; preds = %18, %cond.true
  %19 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !590
  %flags13 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %19, i32 0, i32 7, !dbg !590
  %20 = load i32, i32* %flags13, align 8, !dbg !590
  %and14 = and i32 %20, 16384, !dbg !590
  %cmp15 = icmp eq i32 %and14, 0, !dbg !590
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !590

if.then16:                                        ; preds = %cond.end
  br label %do.end27, !dbg !593

if.end17:                                         ; preds = %cond.end
  %21 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !595
  %flags18 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %21, i32 0, i32 7, !dbg !595
  %22 = load i32, i32* %flags18, align 8, !dbg !595
  %and19 = and i32 %22, -16385, !dbg !595
  store i32 %and19, i32* %flags18, align 8, !dbg !595
  %23 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !595
  %flags20 = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %23, i32 0, i32 7, !dbg !595
  %24 = load i32, i32* %flags20, align 8, !dbg !595
  %and21 = and i32 %24, 8192, !dbg !595
  %cmp22 = icmp ne i32 %and21, 0, !dbg !595
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !595

if.then23:                                        ; preds = %if.end17
  br label %do.body24, !dbg !597

do.body24:                                        ; preds = %if.then23
  %25 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !600
  %loop = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %25, i32 0, i32 1, !dbg !600
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !600
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 1, !dbg !600
  %27 = load i32, i32* %active_handles, align 8, !dbg !600
  %dec = add i32 %27, -1, !dbg !600
  store i32 %dec, i32* %active_handles, align 8, !dbg !600
  br label %do.end25, !dbg !600

do.end25:                                         ; preds = %do.body24
  br label %if.end26, !dbg !603

if.end26:                                         ; preds = %do.end25, %if.end17
  br label %do.end27, !dbg !605

do.end27:                                         ; preds = %if.end26, %if.then16
  store i32 0, i32* %retval, align 4, !dbg !607
  br label %return, !dbg !607

return:                                           ; preds = %do.end27, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !609
  ret i32 %28, !dbg !609
}

; Function Attrs: nounwind uwtable
define void @uv__run_check(%struct.uv_loop_s* %loop) #0 !dbg !337 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %h = alloca %struct.uv_check_s*, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %q5 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !611, metadata !354), !dbg !612
  call void @llvm.dbg.declare(metadata %struct.uv_check_s** %h, metadata !613, metadata !354), !dbg !612
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !614, metadata !354), !dbg !612
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !615, metadata !354), !dbg !612
  br label %do.body, !dbg !612

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !616
  %check_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 19, !dbg !616
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !616
  %check_handles1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 19, !dbg !616
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles1, i64 0, i64 0, !dbg !616
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !616
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !616
  %cmp = icmp eq [2 x i8*]* %check_handles, %3, !dbg !616
  br i1 %cmp, label %if.then, label %if.else, !dbg !616

if.then:                                          ; preds = %do.body
  br label %do.body2, !dbg !620

do.body2:                                         ; preds = %if.then
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !622
  %4 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !622
  store [2 x i8*]* %queue, [2 x i8*]** %4, align 16, !dbg !622
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !622
  %5 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !622
  store [2 x i8*]* %queue, [2 x i8*]** %5, align 8, !dbg !622
  br label %do.end, !dbg !622

do.end:                                           ; preds = %do.body2
  br label %if.end, !dbg !625

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q5, metadata !627, metadata !354), !dbg !629
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !630
  %check_handles6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 19, !dbg !630
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles6, i64 0, i64 0, !dbg !630
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !630
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !630
  store [2 x i8*]* %8, [2 x i8*]** %q5, align 8, !dbg !630
  br label %do.body8, !dbg !630

do.body8:                                         ; preds = %if.else
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !632
  %check_handles9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 19, !dbg !632
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles9, i64 0, i64 1, !dbg !632
  %10 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !632
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !632
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !632
  %12 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !632
  store [2 x i8*]* %11, [2 x i8*]** %12, align 8, !dbg !632
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !632
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !632
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !632
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !632
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !632
  store [2 x i8*]* %queue, [2 x i8*]** %15, align 8, !dbg !632
  %16 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !632
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !632
  %17 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !632
  store [2 x i8*]* %16, [2 x i8*]** %17, align 16, !dbg !632
  %18 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !632
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 1, !dbg !632
  %19 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !632
  %20 = load [2 x i8*]*, [2 x i8*]** %19, align 8, !dbg !632
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !632
  %check_handles16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 19, !dbg !632
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles16, i64 0, i64 1, !dbg !632
  %22 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !632
  store [2 x i8*]* %20, [2 x i8*]** %22, align 8, !dbg !632
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !632
  %check_handles18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 19, !dbg !632
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !632
  %check_handles19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 19, !dbg !632
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles19, i64 0, i64 1, !dbg !632
  %25 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !632
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !632
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %26, i64 0, i64 0, !dbg !632
  %27 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !632
  store [2 x i8*]* %check_handles18, [2 x i8*]** %27, align 8, !dbg !632
  %28 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !632
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %28, i64 0, i64 1, !dbg !632
  %29 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !632
  store [2 x i8*]* %queue, [2 x i8*]** %29, align 8, !dbg !632
  br label %do.end23, !dbg !632

do.end23:                                         ; preds = %do.body8
  br label %if.end

if.end:                                           ; preds = %do.end23, %do.end
  br label %do.end24, !dbg !635

do.end24:                                         ; preds = %if.end
  br label %while.cond, !dbg !637

while.cond:                                       ; preds = %do.end46, %do.end24
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !639
  %30 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !639
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 16, !dbg !639
  %cmp26 = icmp eq [2 x i8*]* %queue, %31, !dbg !639
  %lnot = xor i1 %cmp26, true, !dbg !639
  br i1 %lnot, label %while.body, label %while.end, !dbg !639

while.body:                                       ; preds = %while.cond
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !641
  %32 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !641
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 16, !dbg !641
  store [2 x i8*]* %33, [2 x i8*]** %q, align 8, !dbg !641
  %34 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !641
  %35 = bitcast [2 x i8*]* %34 to i8*, !dbg !641
  %add.ptr = getelementptr inbounds i8, i8* %35, i64 -104, !dbg !641
  %36 = bitcast i8* %add.ptr to %struct.uv_check_s*, !dbg !641
  store %struct.uv_check_s* %36, %struct.uv_check_s** %h, align 8, !dbg !641
  br label %do.body28, !dbg !641

do.body28:                                        ; preds = %while.body
  %37 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !644
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 0, !dbg !644
  %38 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !644
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !644
  %40 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !644
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 1, !dbg !644
  %41 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !644
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 8, !dbg !644
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 0, !dbg !644
  %43 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !644
  store [2 x i8*]* %39, [2 x i8*]** %43, align 8, !dbg !644
  %44 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !644
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %44, i64 0, i64 1, !dbg !644
  %45 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !644
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !644
  %47 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !644
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !644
  %48 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !644
  %49 = load [2 x i8*]*, [2 x i8*]** %48, align 8, !dbg !644
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %49, i64 0, i64 1, !dbg !644
  %50 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !644
  store [2 x i8*]* %46, [2 x i8*]** %50, align 8, !dbg !644
  br label %do.end35, !dbg !644

do.end35:                                         ; preds = %do.body28
  br label %do.body36, !dbg !647

do.body36:                                        ; preds = %do.end35
  %51 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !649
  %check_handles37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %51, i32 0, i32 19, !dbg !649
  %52 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !649
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %52, i64 0, i64 0, !dbg !649
  %53 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !649
  store [2 x i8*]* %check_handles37, [2 x i8*]** %53, align 8, !dbg !649
  %54 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !649
  %check_handles39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %54, i32 0, i32 19, !dbg !649
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles39, i64 0, i64 1, !dbg !649
  %55 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !649
  %56 = load [2 x i8*]*, [2 x i8*]** %55, align 8, !dbg !649
  %57 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !649
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !649
  %58 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !649
  store [2 x i8*]* %56, [2 x i8*]** %58, align 8, !dbg !649
  %59 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !649
  %60 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !649
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !649
  %61 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !649
  %62 = load [2 x i8*]*, [2 x i8*]** %61, align 8, !dbg !649
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !649
  %63 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !649
  store [2 x i8*]* %59, [2 x i8*]** %63, align 8, !dbg !649
  %64 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !649
  %65 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !649
  %check_handles44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %65, i32 0, i32 19, !dbg !649
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %check_handles44, i64 0, i64 1, !dbg !649
  %66 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !649
  store [2 x i8*]* %64, [2 x i8*]** %66, align 8, !dbg !649
  br label %do.end46, !dbg !649

do.end46:                                         ; preds = %do.body36
  %67 = load %struct.uv_check_s*, %struct.uv_check_s** %h, align 8, !dbg !652
  %check_cb = getelementptr inbounds %struct.uv_check_s, %struct.uv_check_s* %67, i32 0, i32 8, !dbg !652
  %68 = load void (%struct.uv_check_s*)*, void (%struct.uv_check_s*)** %check_cb, align 8, !dbg !652
  %69 = load %struct.uv_check_s*, %struct.uv_check_s** %h, align 8, !dbg !652
  call void %68(%struct.uv_check_s* %69), !dbg !652
  br label %while.cond, !dbg !652

while.end:                                        ; preds = %while.cond
  ret void, !dbg !654
}

; Function Attrs: nounwind uwtable
define void @uv__check_close(%struct.uv_check_s* %handle) #0 !dbg !338 {
entry:
  %handle.addr = alloca %struct.uv_check_s*, align 8
  store %struct.uv_check_s* %handle, %struct.uv_check_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_check_s** %handle.addr, metadata !656, metadata !354), !dbg !657
  %0 = load %struct.uv_check_s*, %struct.uv_check_s** %handle.addr, align 8, !dbg !657
  %call = call i32 @uv_check_stop(%struct.uv_check_s* %0), !dbg !657
  ret void, !dbg !657
}

; Function Attrs: nounwind uwtable
define i32 @uv_idle_init(%struct.uv_loop_s* %loop, %struct.uv_idle_s* %handle) #0 !dbg !339 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_idle_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !658, metadata !354), !dbg !659
  store %struct.uv_idle_s* %handle, %struct.uv_idle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_idle_s** %handle.addr, metadata !660, metadata !354), !dbg !659
  br label %do.body, !dbg !659

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !661
  %1 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !661
  %2 = bitcast %struct.uv_idle_s* %1 to %struct.uv_handle_s*, !dbg !661
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !661
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !661
  %3 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !661
  %4 = bitcast %struct.uv_idle_s* %3 to %struct.uv_handle_s*, !dbg !661
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !661
  store i32 6, i32* %type, align 8, !dbg !661
  %5 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !661
  %6 = bitcast %struct.uv_idle_s* %5 to %struct.uv_handle_s*, !dbg !661
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !661
  store i32 8192, i32* %flags, align 8, !dbg !661
  br label %do.body2, !dbg !661

do.body2:                                         ; preds = %do.body
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !664
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 2, !dbg !664
  %8 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !664
  %9 = bitcast %struct.uv_idle_s* %8 to %struct.uv_handle_s*, !dbg !664
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 4, !dbg !664
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !664
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !664
  store [2 x i8*]* %handle_queue, [2 x i8*]** %10, align 8, !dbg !664
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !664
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 2, !dbg !664
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !664
  %12 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !664
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !664
  %14 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !664
  %15 = bitcast %struct.uv_idle_s* %14 to %struct.uv_handle_s*, !dbg !664
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 4, !dbg !664
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !664
  %16 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !664
  store [2 x i8*]* %13, [2 x i8*]** %16, align 8, !dbg !664
  %17 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !664
  %18 = bitcast %struct.uv_idle_s* %17 to %struct.uv_handle_s*, !dbg !664
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !664
  %19 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !664
  %20 = bitcast %struct.uv_idle_s* %19 to %struct.uv_handle_s*, !dbg !664
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 4, !dbg !664
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !664
  %21 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !664
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !664
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !664
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !664
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %23, align 8, !dbg !664
  %24 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !664
  %25 = bitcast %struct.uv_idle_s* %24 to %struct.uv_handle_s*, !dbg !664
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !664
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !664
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 2, !dbg !664
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !664
  %27 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !664
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %27, align 8, !dbg !664
  br label %do.end, !dbg !664

do.end:                                           ; preds = %do.body2
  %28 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !667
  %29 = bitcast %struct.uv_idle_s* %28 to %struct.uv_handle_s*, !dbg !667
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 6, !dbg !667
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !667
  br label %do.end15, !dbg !667

do.end15:                                         ; preds = %do.end
  %30 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !669
  %idle_cb = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %30, i32 0, i32 8, !dbg !669
  store void (%struct.uv_idle_s*)* null, void (%struct.uv_idle_s*)** %idle_cb, align 8, !dbg !669
  ret i32 0, !dbg !669
}

; Function Attrs: nounwind uwtable
define i32 @uv_idle_start(%struct.uv_idle_s* %handle, void (%struct.uv_idle_s*)* %cb) #0 !dbg !342 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_idle_s*, align 8
  %cb.addr = alloca void (%struct.uv_idle_s*)*, align 8
  store %struct.uv_idle_s* %handle, %struct.uv_idle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_idle_s** %handle.addr, metadata !671, metadata !354), !dbg !672
  store void (%struct.uv_idle_s*)* %cb, void (%struct.uv_idle_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_idle_s*)** %cb.addr, metadata !673, metadata !354), !dbg !672
  %0 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !674
  %flags = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %0, i32 0, i32 7, !dbg !674
  %1 = load i32, i32* %flags, align 8, !dbg !674
  %and = and i32 %1, 16384, !dbg !674
  %cmp = icmp ne i32 %and, 0, !dbg !674
  br i1 %cmp, label %if.then, label %if.end, !dbg !672

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !676
  br label %return, !dbg !676

if.end:                                           ; preds = %entry
  %2 = load void (%struct.uv_idle_s*)*, void (%struct.uv_idle_s*)** %cb.addr, align 8, !dbg !678
  %cmp1 = icmp eq void (%struct.uv_idle_s*)* %2, null, !dbg !678
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !678

if.then2:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !681
  br label %return, !dbg !681

if.end3:                                          ; preds = %if.end
  br label %do.body, !dbg !683

do.body:                                          ; preds = %if.end3
  %3 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %loop = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %3, i32 0, i32 1, !dbg !685
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !685
  %idle_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 20, !dbg !685
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles, i64 0, i64 0, !dbg !685
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !685
  %6 = load [2 x i8*]*, [2 x i8*]** %5, align 8, !dbg !685
  %7 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %queue = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %7, i32 0, i32 9, !dbg !685
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !685
  %8 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !685
  store [2 x i8*]* %6, [2 x i8*]** %8, align 8, !dbg !685
  %9 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %loop5 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %9, i32 0, i32 1, !dbg !685
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop5, align 8, !dbg !685
  %idle_handles6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 20, !dbg !685
  %11 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %queue7 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %11, i32 0, i32 9, !dbg !685
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue7, i64 0, i64 1, !dbg !685
  %12 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !685
  store [2 x i8*]* %idle_handles6, [2 x i8*]** %12, align 8, !dbg !685
  %13 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %queue9 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %13, i32 0, i32 9, !dbg !685
  %14 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %queue10 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %14, i32 0, i32 9, !dbg !685
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue10, i64 0, i64 0, !dbg !685
  %15 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !685
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !685
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %16, i64 0, i64 1, !dbg !685
  %17 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !685
  store [2 x i8*]* %queue9, [2 x i8*]** %17, align 8, !dbg !685
  %18 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %queue13 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %18, i32 0, i32 9, !dbg !685
  %19 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !685
  %loop14 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %19, i32 0, i32 1, !dbg !685
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop14, align 8, !dbg !685
  %idle_handles15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 20, !dbg !685
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles15, i64 0, i64 0, !dbg !685
  %21 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !685
  store [2 x i8*]* %queue13, [2 x i8*]** %21, align 8, !dbg !685
  br label %do.end, !dbg !685

do.end:                                           ; preds = %do.body
  %22 = load void (%struct.uv_idle_s*)*, void (%struct.uv_idle_s*)** %cb.addr, align 8, !dbg !688
  %23 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !688
  %idle_cb = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %23, i32 0, i32 8, !dbg !688
  store void (%struct.uv_idle_s*)* %22, void (%struct.uv_idle_s*)** %idle_cb, align 8, !dbg !688
  br label %do.body17, !dbg !688

do.body17:                                        ; preds = %do.end
  %24 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !690
  %flags18 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %24, i32 0, i32 7, !dbg !690
  %25 = load i32, i32* %flags18, align 8, !dbg !690
  %and19 = and i32 %25, 0, !dbg !690
  %cmp20 = icmp eq i32 %and19, 0, !dbg !690
  br i1 %cmp20, label %cond.true, label %cond.false, !dbg !690

cond.true:                                        ; preds = %do.body17
  br label %cond.end, !dbg !693

cond.false:                                       ; preds = %do.body17
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.1, i32 0, i32 0), i32 68, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.uv_idle_start, i32 0, i32 0)) #3, !dbg !695
  unreachable, !dbg !695
                                                  ; No predecessors!
  br label %cond.end, !dbg !697

cond.end:                                         ; preds = %26, %cond.true
  %27 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !699
  %flags21 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %27, i32 0, i32 7, !dbg !699
  %28 = load i32, i32* %flags21, align 8, !dbg !699
  %and22 = and i32 %28, 16384, !dbg !699
  %cmp23 = icmp ne i32 %and22, 0, !dbg !699
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !699

if.then24:                                        ; preds = %cond.end
  br label %do.end35, !dbg !702

if.end25:                                         ; preds = %cond.end
  %29 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !704
  %flags26 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %29, i32 0, i32 7, !dbg !704
  %30 = load i32, i32* %flags26, align 8, !dbg !704
  %or = or i32 %30, 16384, !dbg !704
  store i32 %or, i32* %flags26, align 8, !dbg !704
  %31 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !704
  %flags27 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %31, i32 0, i32 7, !dbg !704
  %32 = load i32, i32* %flags27, align 8, !dbg !704
  %and28 = and i32 %32, 8192, !dbg !704
  %cmp29 = icmp ne i32 %and28, 0, !dbg !704
  br i1 %cmp29, label %if.then30, label %if.end34, !dbg !704

if.then30:                                        ; preds = %if.end25
  br label %do.body31, !dbg !706

do.body31:                                        ; preds = %if.then30
  %33 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !709
  %loop32 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %33, i32 0, i32 1, !dbg !709
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop32, align 8, !dbg !709
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 1, !dbg !709
  %35 = load i32, i32* %active_handles, align 8, !dbg !709
  %inc = add i32 %35, 1, !dbg !709
  store i32 %inc, i32* %active_handles, align 8, !dbg !709
  br label %do.end33, !dbg !709

do.end33:                                         ; preds = %do.body31
  br label %if.end34, !dbg !712

if.end34:                                         ; preds = %do.end33, %if.end25
  br label %do.end35, !dbg !714

do.end35:                                         ; preds = %if.end34, %if.then24
  store i32 0, i32* %retval, align 4, !dbg !716
  br label %return, !dbg !716

return:                                           ; preds = %do.end35, %if.then2, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !718
  ret i32 %36, !dbg !718
}

; Function Attrs: nounwind uwtable
define i32 @uv_idle_stop(%struct.uv_idle_s* %handle) #0 !dbg !345 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_idle_s*, align 8
  store %struct.uv_idle_s* %handle, %struct.uv_idle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_idle_s** %handle.addr, metadata !720, metadata !354), !dbg !721
  %0 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !722
  %flags = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %0, i32 0, i32 7, !dbg !722
  %1 = load i32, i32* %flags, align 8, !dbg !722
  %and = and i32 %1, 16384, !dbg !722
  %cmp = icmp ne i32 %and, 0, !dbg !722
  br i1 %cmp, label %if.end, label %if.then, !dbg !721

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !724
  br label %return, !dbg !724

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !726

do.body:                                          ; preds = %if.end
  %2 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !728
  %queue = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %2, i32 0, i32 9, !dbg !728
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !728
  %3 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !728
  %4 = load [2 x i8*]*, [2 x i8*]** %3, align 8, !dbg !728
  %5 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !728
  %queue1 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %5, i32 0, i32 9, !dbg !728
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue1, i64 0, i64 1, !dbg !728
  %6 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !728
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !728
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !728
  %8 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !728
  store [2 x i8*]* %4, [2 x i8*]** %8, align 8, !dbg !728
  %9 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !728
  %queue4 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %9, i32 0, i32 9, !dbg !728
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue4, i64 0, i64 1, !dbg !728
  %10 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !728
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !728
  %12 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !728
  %queue6 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %12, i32 0, i32 9, !dbg !728
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue6, i64 0, i64 0, !dbg !728
  %13 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !728
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !728
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 1, !dbg !728
  %15 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !728
  store [2 x i8*]* %11, [2 x i8*]** %15, align 8, !dbg !728
  br label %do.end, !dbg !728

do.end:                                           ; preds = %do.body
  br label %do.body9, !dbg !731

do.body9:                                         ; preds = %do.end
  %16 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !733
  %flags10 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %16, i32 0, i32 7, !dbg !733
  %17 = load i32, i32* %flags10, align 8, !dbg !733
  %and11 = and i32 %17, 0, !dbg !733
  %cmp12 = icmp eq i32 %and11, 0, !dbg !733
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !733

cond.true:                                        ; preds = %do.body9
  br label %cond.end, !dbg !736

cond.false:                                       ; preds = %do.body9
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.1, i32 0, i32 0), i32 68, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @__PRETTY_FUNCTION__.uv_idle_stop, i32 0, i32 0)) #3, !dbg !738
  unreachable, !dbg !738
                                                  ; No predecessors!
  br label %cond.end, !dbg !740

cond.end:                                         ; preds = %18, %cond.true
  %19 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !742
  %flags13 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %19, i32 0, i32 7, !dbg !742
  %20 = load i32, i32* %flags13, align 8, !dbg !742
  %and14 = and i32 %20, 16384, !dbg !742
  %cmp15 = icmp eq i32 %and14, 0, !dbg !742
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !742

if.then16:                                        ; preds = %cond.end
  br label %do.end27, !dbg !745

if.end17:                                         ; preds = %cond.end
  %21 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !747
  %flags18 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %21, i32 0, i32 7, !dbg !747
  %22 = load i32, i32* %flags18, align 8, !dbg !747
  %and19 = and i32 %22, -16385, !dbg !747
  store i32 %and19, i32* %flags18, align 8, !dbg !747
  %23 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !747
  %flags20 = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %23, i32 0, i32 7, !dbg !747
  %24 = load i32, i32* %flags20, align 8, !dbg !747
  %and21 = and i32 %24, 8192, !dbg !747
  %cmp22 = icmp ne i32 %and21, 0, !dbg !747
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !747

if.then23:                                        ; preds = %if.end17
  br label %do.body24, !dbg !749

do.body24:                                        ; preds = %if.then23
  %25 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !752
  %loop = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %25, i32 0, i32 1, !dbg !752
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !752
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 1, !dbg !752
  %27 = load i32, i32* %active_handles, align 8, !dbg !752
  %dec = add i32 %27, -1, !dbg !752
  store i32 %dec, i32* %active_handles, align 8, !dbg !752
  br label %do.end25, !dbg !752

do.end25:                                         ; preds = %do.body24
  br label %if.end26, !dbg !755

if.end26:                                         ; preds = %do.end25, %if.end17
  br label %do.end27, !dbg !757

do.end27:                                         ; preds = %if.end26, %if.then16
  store i32 0, i32* %retval, align 4, !dbg !759
  br label %return, !dbg !759

return:                                           ; preds = %do.end27, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !761
  ret i32 %28, !dbg !761
}

; Function Attrs: nounwind uwtable
define void @uv__run_idle(%struct.uv_loop_s* %loop) #0 !dbg !348 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %h = alloca %struct.uv_idle_s*, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %q5 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !763, metadata !354), !dbg !764
  call void @llvm.dbg.declare(metadata %struct.uv_idle_s** %h, metadata !765, metadata !354), !dbg !764
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !766, metadata !354), !dbg !764
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !767, metadata !354), !dbg !764
  br label %do.body, !dbg !764

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !768
  %idle_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 20, !dbg !768
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !768
  %idle_handles1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 20, !dbg !768
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles1, i64 0, i64 0, !dbg !768
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !768
  %3 = load [2 x i8*]*, [2 x i8*]** %2, align 8, !dbg !768
  %cmp = icmp eq [2 x i8*]* %idle_handles, %3, !dbg !768
  br i1 %cmp, label %if.then, label %if.else, !dbg !768

if.then:                                          ; preds = %do.body
  br label %do.body2, !dbg !772

do.body2:                                         ; preds = %if.then
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !774
  %4 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !774
  store [2 x i8*]* %queue, [2 x i8*]** %4, align 16, !dbg !774
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !774
  %5 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !774
  store [2 x i8*]* %queue, [2 x i8*]** %5, align 8, !dbg !774
  br label %do.end, !dbg !774

do.end:                                           ; preds = %do.body2
  br label %if.end, !dbg !777

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q5, metadata !779, metadata !354), !dbg !781
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !782
  %idle_handles6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 20, !dbg !782
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles6, i64 0, i64 0, !dbg !782
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !782
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !782
  store [2 x i8*]* %8, [2 x i8*]** %q5, align 8, !dbg !782
  br label %do.body8, !dbg !782

do.body8:                                         ; preds = %if.else
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !784
  %idle_handles9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 20, !dbg !784
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles9, i64 0, i64 1, !dbg !784
  %10 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !784
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !784
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !784
  %12 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !784
  store [2 x i8*]* %11, [2 x i8*]** %12, align 8, !dbg !784
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !784
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !784
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !784
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !784
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !784
  store [2 x i8*]* %queue, [2 x i8*]** %15, align 8, !dbg !784
  %16 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !784
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !784
  %17 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !784
  store [2 x i8*]* %16, [2 x i8*]** %17, align 16, !dbg !784
  %18 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !784
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 1, !dbg !784
  %19 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !784
  %20 = load [2 x i8*]*, [2 x i8*]** %19, align 8, !dbg !784
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !784
  %idle_handles16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 20, !dbg !784
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles16, i64 0, i64 1, !dbg !784
  %22 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !784
  store [2 x i8*]* %20, [2 x i8*]** %22, align 8, !dbg !784
  %23 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !784
  %idle_handles18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %23, i32 0, i32 20, !dbg !784
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !784
  %idle_handles19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 20, !dbg !784
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles19, i64 0, i64 1, !dbg !784
  %25 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !784
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !784
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %26, i64 0, i64 0, !dbg !784
  %27 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !784
  store [2 x i8*]* %idle_handles18, [2 x i8*]** %27, align 8, !dbg !784
  %28 = load [2 x i8*]*, [2 x i8*]** %q5, align 8, !dbg !784
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %28, i64 0, i64 1, !dbg !784
  %29 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !784
  store [2 x i8*]* %queue, [2 x i8*]** %29, align 8, !dbg !784
  br label %do.end23, !dbg !784

do.end23:                                         ; preds = %do.body8
  br label %if.end

if.end:                                           ; preds = %do.end23, %do.end
  br label %do.end24, !dbg !787

do.end24:                                         ; preds = %if.end
  br label %while.cond, !dbg !789

while.cond:                                       ; preds = %do.end46, %do.end24
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !791
  %30 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !791
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 16, !dbg !791
  %cmp26 = icmp eq [2 x i8*]* %queue, %31, !dbg !791
  %lnot = xor i1 %cmp26, true, !dbg !791
  br i1 %lnot, label %while.body, label %while.end, !dbg !791

while.body:                                       ; preds = %while.cond
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !793
  %32 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !793
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 16, !dbg !793
  store [2 x i8*]* %33, [2 x i8*]** %q, align 8, !dbg !793
  %34 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !793
  %35 = bitcast [2 x i8*]* %34 to i8*, !dbg !793
  %add.ptr = getelementptr inbounds i8, i8* %35, i64 -104, !dbg !793
  %36 = bitcast i8* %add.ptr to %struct.uv_idle_s*, !dbg !793
  store %struct.uv_idle_s* %36, %struct.uv_idle_s** %h, align 8, !dbg !793
  br label %do.body28, !dbg !793

do.body28:                                        ; preds = %while.body
  %37 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !796
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %37, i64 0, i64 0, !dbg !796
  %38 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !796
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !796
  %40 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !796
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 1, !dbg !796
  %41 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !796
  %42 = load [2 x i8*]*, [2 x i8*]** %41, align 8, !dbg !796
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 0, !dbg !796
  %43 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !796
  store [2 x i8*]* %39, [2 x i8*]** %43, align 8, !dbg !796
  %44 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !796
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %44, i64 0, i64 1, !dbg !796
  %45 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !796
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !796
  %47 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !796
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !796
  %48 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !796
  %49 = load [2 x i8*]*, [2 x i8*]** %48, align 8, !dbg !796
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %49, i64 0, i64 1, !dbg !796
  %50 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !796
  store [2 x i8*]* %46, [2 x i8*]** %50, align 8, !dbg !796
  br label %do.end35, !dbg !796

do.end35:                                         ; preds = %do.body28
  br label %do.body36, !dbg !799

do.body36:                                        ; preds = %do.end35
  %51 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !801
  %idle_handles37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %51, i32 0, i32 20, !dbg !801
  %52 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !801
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %52, i64 0, i64 0, !dbg !801
  %53 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %idle_handles37, [2 x i8*]** %53, align 8, !dbg !801
  %54 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !801
  %idle_handles39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %54, i32 0, i32 20, !dbg !801
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles39, i64 0, i64 1, !dbg !801
  %55 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !801
  %56 = load [2 x i8*]*, [2 x i8*]** %55, align 8, !dbg !801
  %57 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !801
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !801
  %58 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %56, [2 x i8*]** %58, align 8, !dbg !801
  %59 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !801
  %60 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !801
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !801
  %61 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !801
  %62 = load [2 x i8*]*, [2 x i8*]** %61, align 8, !dbg !801
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !801
  %63 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %59, [2 x i8*]** %63, align 8, !dbg !801
  %64 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !801
  %65 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !801
  %idle_handles44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %65, i32 0, i32 20, !dbg !801
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %idle_handles44, i64 0, i64 1, !dbg !801
  %66 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !801
  store [2 x i8*]* %64, [2 x i8*]** %66, align 8, !dbg !801
  br label %do.end46, !dbg !801

do.end46:                                         ; preds = %do.body36
  %67 = load %struct.uv_idle_s*, %struct.uv_idle_s** %h, align 8, !dbg !804
  %idle_cb = getelementptr inbounds %struct.uv_idle_s, %struct.uv_idle_s* %67, i32 0, i32 8, !dbg !804
  %68 = load void (%struct.uv_idle_s*)*, void (%struct.uv_idle_s*)** %idle_cb, align 8, !dbg !804
  %69 = load %struct.uv_idle_s*, %struct.uv_idle_s** %h, align 8, !dbg !804
  call void %68(%struct.uv_idle_s* %69), !dbg !804
  br label %while.cond, !dbg !804

while.end:                                        ; preds = %while.cond
  ret void, !dbg !806
}

; Function Attrs: nounwind uwtable
define void @uv__idle_close(%struct.uv_idle_s* %handle) #0 !dbg !349 {
entry:
  %handle.addr = alloca %struct.uv_idle_s*, align 8
  store %struct.uv_idle_s* %handle, %struct.uv_idle_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_idle_s** %handle.addr, metadata !808, metadata !354), !dbg !809
  %0 = load %struct.uv_idle_s*, %struct.uv_idle_s** %handle.addr, align 8, !dbg !809
  %call = call i32 @uv_idle_stop(%struct.uv_idle_s* %0), !dbg !809
  ret void, !dbg !809
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!350, !351}
!llvm.ident = !{!352}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !33, subprograms: !313)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/loop-watcher.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25}
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
!33 = !{!34, !240, !39, !244, !246, !268, !269, !291}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !36)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !37)
!37 = !{!38, !40, !230, !231, !232, !233, !238, !239}
!38 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !36, file: !4, line: 426, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !36, file: !4, line: 426, baseType: !41, size: 64, align: 64, offset: 64)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !43)
!43 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !44)
!44 = !{!45, !46, !48, !52, !53, !54, !56, !58, !59, !60, !79, !80, !81, !82, !113, !145, !169, !170, !171, !172, !173, !174, !175, !179, !180, !181, !186, !189, !190, !192, !193, !226, !227, !228, !229}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !43, file: !4, line: 1475, baseType: !39, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !43, file: !4, line: 1477, baseType: !47, size: 32, align: 32, offset: 64)
!47 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !43, file: !4, line: 1478, baseType: !49, size: 128, align: 64, offset: 128)
!49 = !DICompositeType(tag: DW_TAG_array_type, baseType: !39, size: 128, align: 64, elements: !50)
!50 = !{!51}
!51 = !DISubrange(count: 2)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !43, file: !4, line: 1479, baseType: !49, size: 128, align: 64, offset: 256)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !43, file: !4, line: 1481, baseType: !47, size: 32, align: 32, offset: 384)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !43, file: !4, line: 1482, baseType: !55, size: 64, align: 64, offset: 448)
!55 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !43, file: !4, line: 1482, baseType: !57, size: 32, align: 32, offset: 512)
!57 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 576)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 704)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !43, file: !4, line: 1482, baseType: !61, size: 64, align: 64, offset: 832)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !64, line: 87, baseType: !65)
!64 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!65 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !64, line: 89, size: 448, align: 64, elements: !66)
!66 = !{!67, !74, !75, !76, !77, !78}
!67 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !65, file: !64, line: 90, baseType: !68, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !64, line: 84, baseType: !69)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{null, !72, !73, !47}
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !65, file: !64, line: 91, baseType: !49, size: 128, align: 64, offset: 64)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !65, file: !64, line: 92, baseType: !49, size: 128, align: 64, offset: 192)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !65, file: !64, line: 93, baseType: !47, size: 32, align: 32, offset: 320)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !65, file: !64, line: 94, baseType: !47, size: 32, align: 32, offset: 352)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !65, file: !64, line: 95, baseType: !57, size: 32, align: 32, offset: 384)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !43, file: !4, line: 1482, baseType: !47, size: 32, align: 32, offset: 896)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !43, file: !4, line: 1482, baseType: !47, size: 32, align: 32, offset: 928)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 960)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !43, file: !4, line: 1482, baseType: !83, size: 320, align: 64, offset: 1088)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !64, line: 129, baseType: !84)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !85, line: 127, baseType: !86)
!85 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!86 = !DICompositeType(tag: DW_TAG_union_type, file: !85, line: 90, size: 320, align: 64, elements: !87)
!87 = !{!88, !106, !111}
!88 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !86, file: !85, line: 124, baseType: !89, size: 320, align: 64)
!89 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !85, line: 92, size: 320, align: 64, elements: !90)
!90 = !{!91, !92, !93, !94, !95, !96, !98, !99}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !89, file: !85, line: 94, baseType: !57, size: 32, align: 32)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !89, file: !85, line: 95, baseType: !47, size: 32, align: 32, offset: 32)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !89, file: !85, line: 96, baseType: !57, size: 32, align: 32, offset: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !89, file: !85, line: 98, baseType: !47, size: 32, align: 32, offset: 96)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !89, file: !85, line: 102, baseType: !57, size: 32, align: 32, offset: 128)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !89, file: !85, line: 104, baseType: !97, size: 16, align: 16, offset: 160)
!97 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !89, file: !85, line: 105, baseType: !97, size: 16, align: 16, offset: 176)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !89, file: !85, line: 106, baseType: !100, size: 128, align: 64, offset: 192)
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !85, line: 79, baseType: !101)
!101 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !85, line: 75, size: 128, align: 64, elements: !102)
!102 = !{!103, !105}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !101, file: !85, line: 77, baseType: !104, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !101, file: !85, line: 78, baseType: !104, size: 64, align: 64, offset: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !86, file: !85, line: 125, baseType: !107, size: 320, align: 8)
!107 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 320, align: 8, elements: !109)
!108 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!109 = !{!110}
!110 = !DISubrange(count: 40)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !86, file: !85, line: 126, baseType: !112, size: 64, align: 64)
!112 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !43, file: !4, line: 1482, baseType: !114, size: 1024, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !115)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !116)
!116 = !{!117, !118, !119, !121, !126, !127, !135, !136, !137, !143, !144}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !115, file: !4, line: 768, baseType: !39, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !115, file: !4, line: 768, baseType: !41, size: 64, align: 64, offset: 64)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !115, file: !4, line: 768, baseType: !120, size: 32, align: 32, offset: 128)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !115, file: !4, line: 768, baseType: !122, size: 64, align: 64, offset: 192)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !123)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DISubroutineType(types: !125)
!125 = !{null, !34}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !115, file: !4, line: 768, baseType: !49, size: 128, align: 64, offset: 256)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !115, file: !4, line: 768, baseType: !128, size: 256, align: 64, offset: 384)
!128 = !DICompositeType(tag: DW_TAG_union_type, scope: !115, file: !4, line: 768, size: 256, align: 64, elements: !129)
!129 = !{!130, !131}
!130 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !128, file: !4, line: 768, baseType: !57, size: 32, align: 32)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !128, file: !4, line: 768, baseType: !132, size: 256, align: 64)
!132 = !DICompositeType(tag: DW_TAG_array_type, baseType: !39, size: 256, align: 64, elements: !133)
!133 = !{!134}
!134 = !DISubrange(count: 4)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !115, file: !4, line: 768, baseType: !34, size: 64, align: 64, offset: 640)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !115, file: !4, line: 768, baseType: !47, size: 32, align: 32, offset: 704)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !115, file: !4, line: 769, baseType: !138, size: 64, align: 64, offset: 768)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !139)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DISubroutineType(types: !141)
!141 = !{null, !142}
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !115, file: !4, line: 769, baseType: !49, size: 128, align: 64, offset: 832)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !115, file: !4, line: 769, baseType: !57, size: 32, align: 32, offset: 960)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !43, file: !4, line: 1482, baseType: !146, size: 448, align: 64, offset: 2432)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !64, line: 130, baseType: !147)
!147 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !85, line: 213, baseType: !148)
!148 = !DICompositeType(tag: DW_TAG_union_type, file: !85, line: 173, size: 448, align: 64, elements: !149)
!149 = !{!150, !164, !168}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !148, file: !85, line: 192, baseType: !151, size: 448, align: 64)
!151 = !DICompositeType(tag: DW_TAG_structure_type, scope: !148, file: !85, line: 176, size: 448, align: 64, elements: !152)
!152 = !{!153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163}
!153 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !151, file: !85, line: 178, baseType: !57, size: 32, align: 32)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !151, file: !85, line: 179, baseType: !47, size: 32, align: 32, offset: 32)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !151, file: !85, line: 180, baseType: !47, size: 32, align: 32, offset: 64)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !151, file: !85, line: 181, baseType: !47, size: 32, align: 32, offset: 96)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !151, file: !85, line: 182, baseType: !47, size: 32, align: 32, offset: 128)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !151, file: !85, line: 183, baseType: !47, size: 32, align: 32, offset: 160)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !151, file: !85, line: 184, baseType: !57, size: 32, align: 32, offset: 192)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !151, file: !85, line: 185, baseType: !57, size: 32, align: 32, offset: 224)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !151, file: !85, line: 186, baseType: !55, size: 64, align: 64, offset: 256)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !151, file: !85, line: 187, baseType: !55, size: 64, align: 64, offset: 320)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !151, file: !85, line: 190, baseType: !47, size: 32, align: 32, offset: 384)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !148, file: !85, line: 211, baseType: !165, size: 448, align: 8)
!165 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 448, align: 8, elements: !166)
!166 = !{!167}
!167 = !DISubrange(count: 56)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !148, file: !85, line: 212, baseType: !112, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !43, file: !4, line: 1482, baseType: !34, size: 64, align: 64, offset: 2880)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 2944)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 3072)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 3200)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 3328)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !43, file: !4, line: 1482, baseType: !49, size: 128, align: 64, offset: 3456)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !43, file: !4, line: 1482, baseType: !176, size: 64, align: 64, offset: 3584)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DISubroutineType(types: !178)
!178 = !{null}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !43, file: !4, line: 1482, baseType: !63, size: 448, align: 64, offset: 3648)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !43, file: !4, line: 1482, baseType: !57, size: 32, align: 32, offset: 4096)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !43, file: !4, line: 1482, baseType: !182, size: 128, align: 64, offset: 4160)
!182 = !DICompositeType(tag: DW_TAG_structure_type, scope: !43, file: !4, line: 1482, size: 128, align: 64, elements: !183)
!183 = !{!184, !185}
!184 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !182, file: !4, line: 1482, baseType: !39, size: 64, align: 64)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !182, file: !4, line: 1482, baseType: !47, size: 32, align: 32, offset: 64)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !43, file: !4, line: 1482, baseType: !187, size: 64, align: 64, offset: 4288)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !188, line: 55, baseType: !55)
!188 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!189 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !43, file: !4, line: 1482, baseType: !187, size: 64, align: 64, offset: 4352)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !43, file: !4, line: 1482, baseType: !191, size: 64, align: 32, offset: 4416)
!191 = !DICompositeType(tag: DW_TAG_array_type, baseType: !57, size: 64, align: 32, elements: !50)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !43, file: !4, line: 1482, baseType: !63, size: 448, align: 64, offset: 4480)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !43, file: !4, line: 1482, baseType: !194, size: 1216, align: 64, offset: 4928)
!194 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !195)
!195 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !196)
!196 = !{!197, !198, !199, !200, !201, !202, !207, !208, !209, !215, !216, !224, !225}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !195, file: !4, line: 1326, baseType: !39, size: 64, align: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !195, file: !4, line: 1326, baseType: !41, size: 64, align: 64, offset: 64)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !195, file: !4, line: 1326, baseType: !120, size: 32, align: 32, offset: 128)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !195, file: !4, line: 1326, baseType: !122, size: 64, align: 64, offset: 192)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !195, file: !4, line: 1326, baseType: !49, size: 128, align: 64, offset: 256)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !195, file: !4, line: 1326, baseType: !203, size: 256, align: 64, offset: 384)
!203 = !DICompositeType(tag: DW_TAG_union_type, scope: !195, file: !4, line: 1326, size: 256, align: 64, elements: !204)
!204 = !{!205, !206}
!205 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !203, file: !4, line: 1326, baseType: !57, size: 32, align: 32)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !203, file: !4, line: 1326, baseType: !132, size: 256, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !195, file: !4, line: 1326, baseType: !34, size: 64, align: 64, offset: 640)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !195, file: !4, line: 1326, baseType: !47, size: 32, align: 32, offset: 704)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !195, file: !4, line: 1327, baseType: !210, size: 64, align: 64, offset: 768)
!210 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !211)
!211 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !212, size: 64, align: 64)
!212 = !DISubroutineType(types: !213)
!213 = !{null, !214, !57}
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64, align: 64)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !195, file: !4, line: 1328, baseType: !57, size: 32, align: 32, offset: 832)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !195, file: !4, line: 1329, baseType: !217, size: 256, align: 64, offset: 896)
!217 = !DICompositeType(tag: DW_TAG_structure_type, scope: !195, file: !4, line: 1329, size: 256, align: 64, elements: !218)
!218 = !{!219, !221, !222, !223}
!219 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !217, file: !4, line: 1329, baseType: !220, size: 64, align: 64)
!220 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !217, file: !4, line: 1329, baseType: !220, size: 64, align: 64, offset: 64)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !217, file: !4, line: 1329, baseType: !220, size: 64, align: 64, offset: 128)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !217, file: !4, line: 1329, baseType: !57, size: 32, align: 32, offset: 192)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !195, file: !4, line: 1329, baseType: !47, size: 32, align: 32, offset: 1152)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !195, file: !4, line: 1329, baseType: !47, size: 32, align: 32, offset: 1184)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !43, file: !4, line: 1482, baseType: !57, size: 32, align: 32, offset: 6144)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !43, file: !4, line: 1482, baseType: !63, size: 448, align: 64, offset: 6208)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !43, file: !4, line: 1482, baseType: !39, size: 64, align: 64, offset: 6656)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !43, file: !4, line: 1482, baseType: !57, size: 32, align: 32, offset: 6720)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !36, file: !4, line: 426, baseType: !120, size: 32, align: 32, offset: 128)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !36, file: !4, line: 426, baseType: !122, size: 64, align: 64, offset: 192)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !36, file: !4, line: 426, baseType: !49, size: 128, align: 64, offset: 256)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !36, file: !4, line: 426, baseType: !234, size: 256, align: 64, offset: 384)
!234 = !DICompositeType(tag: DW_TAG_union_type, scope: !36, file: !4, line: 426, size: 256, align: 64, elements: !235)
!235 = !{!236, !237}
!236 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !234, file: !4, line: 426, baseType: !57, size: 32, align: 32)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !234, file: !4, line: 426, baseType: !132, size: 256, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !36, file: !4, line: 426, baseType: !34, size: 64, align: 64, offset: 640)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !36, file: !4, line: 426, baseType: !47, size: 32, align: 32, offset: 704)
!240 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !241, size: 64, align: 64)
!241 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !242, size: 64, align: 64)
!242 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !243, line: 21, baseType: !49)
!243 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!244 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !245, size: 64, align: 64)
!245 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !242)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_prepare_t", file: !4, line: 213, baseType: !248)
!248 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_prepare_s", file: !4, line: 737, size: 960, align: 64, elements: !249)
!249 = !{!250, !251, !252, !253, !254, !255, !260, !261, !262, !267}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !248, file: !4, line: 738, baseType: !39, size: 64, align: 64)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !248, file: !4, line: 738, baseType: !41, size: 64, align: 64, offset: 64)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !248, file: !4, line: 738, baseType: !120, size: 32, align: 32, offset: 128)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !248, file: !4, line: 738, baseType: !122, size: 64, align: 64, offset: 192)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !248, file: !4, line: 738, baseType: !49, size: 128, align: 64, offset: 256)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !248, file: !4, line: 738, baseType: !256, size: 256, align: 64, offset: 384)
!256 = !DICompositeType(tag: DW_TAG_union_type, scope: !248, file: !4, line: 738, size: 256, align: 64, elements: !257)
!257 = !{!258, !259}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !256, file: !4, line: 738, baseType: !57, size: 32, align: 32)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !256, file: !4, line: 738, baseType: !132, size: 256, align: 64)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !248, file: !4, line: 738, baseType: !34, size: 64, align: 64, offset: 640)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !248, file: !4, line: 738, baseType: !47, size: 32, align: 32, offset: 704)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_cb", scope: !248, file: !4, line: 739, baseType: !263, size: 64, align: 64, offset: 768)
!263 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_prepare_cb", file: !4, line: 310, baseType: !264)
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DISubroutineType(types: !266)
!266 = !{null, !246}
!267 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !248, file: !4, line: 739, baseType: !49, size: 128, align: 64, offset: 832)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !270, size: 64, align: 64)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_check_t", file: !4, line: 214, baseType: !271)
!271 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_check_s", file: !4, line: 747, size: 960, align: 64, elements: !272)
!272 = !{!273, !274, !275, !276, !277, !278, !283, !284, !285, !290}
!273 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !271, file: !4, line: 748, baseType: !39, size: 64, align: 64)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !271, file: !4, line: 748, baseType: !41, size: 64, align: 64, offset: 64)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !271, file: !4, line: 748, baseType: !120, size: 32, align: 32, offset: 128)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !271, file: !4, line: 748, baseType: !122, size: 64, align: 64, offset: 192)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !271, file: !4, line: 748, baseType: !49, size: 128, align: 64, offset: 256)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !271, file: !4, line: 748, baseType: !279, size: 256, align: 64, offset: 384)
!279 = !DICompositeType(tag: DW_TAG_union_type, scope: !271, file: !4, line: 748, size: 256, align: 64, elements: !280)
!280 = !{!281, !282}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !279, file: !4, line: 748, baseType: !57, size: 32, align: 32)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !279, file: !4, line: 748, baseType: !132, size: 256, align: 64)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !271, file: !4, line: 748, baseType: !34, size: 64, align: 64, offset: 640)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !271, file: !4, line: 748, baseType: !47, size: 32, align: 32, offset: 704)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "check_cb", scope: !271, file: !4, line: 749, baseType: !286, size: 64, align: 64, offset: 768)
!286 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_check_cb", file: !4, line: 311, baseType: !287)
!287 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !288, size: 64, align: 64)
!288 = !DISubroutineType(types: !289)
!289 = !{null, !269}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !271, file: !4, line: 749, baseType: !49, size: 128, align: 64, offset: 832)
!291 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !292, size: 64, align: 64)
!292 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_idle_t", file: !4, line: 215, baseType: !293)
!293 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_idle_s", file: !4, line: 757, size: 960, align: 64, elements: !294)
!294 = !{!295, !296, !297, !298, !299, !300, !305, !306, !307, !312}
!295 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !293, file: !4, line: 758, baseType: !39, size: 64, align: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !293, file: !4, line: 758, baseType: !41, size: 64, align: 64, offset: 64)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !293, file: !4, line: 758, baseType: !120, size: 32, align: 32, offset: 128)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !293, file: !4, line: 758, baseType: !122, size: 64, align: 64, offset: 192)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !293, file: !4, line: 758, baseType: !49, size: 128, align: 64, offset: 256)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !293, file: !4, line: 758, baseType: !301, size: 256, align: 64, offset: 384)
!301 = !DICompositeType(tag: DW_TAG_union_type, scope: !293, file: !4, line: 758, size: 256, align: 64, elements: !302)
!302 = !{!303, !304}
!303 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !301, file: !4, line: 758, baseType: !57, size: 32, align: 32)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !301, file: !4, line: 758, baseType: !132, size: 256, align: 64)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !293, file: !4, line: 758, baseType: !34, size: 64, align: 64, offset: 640)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !293, file: !4, line: 758, baseType: !47, size: 32, align: 32, offset: 704)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "idle_cb", scope: !293, file: !4, line: 759, baseType: !308, size: 64, align: 64, offset: 768)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_idle_cb", file: !4, line: 312, baseType: !309)
!309 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !310, size: 64, align: 64)
!310 = !DISubroutineType(types: !311)
!311 = !{null, !291}
!312 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !293, file: !4, line: 759, baseType: !49, size: 128, align: 64, offset: 832)
!313 = !{!314, !318, !321, !324, !327, !328, !331, !334, !337, !338, !339, !342, !345, !348, !349}
!314 = distinct !DISubprogram(name: "uv_prepare_init", scope: !1, file: !1, line: 66, type: !315, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!315 = !DISubroutineType(types: !316)
!316 = !{!57, !41, !246}
!317 = !{}
!318 = distinct !DISubprogram(name: "uv_prepare_start", scope: !1, file: !1, line: 66, type: !319, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!319 = !DISubroutineType(types: !320)
!320 = !{!57, !246, !263}
!321 = distinct !DISubprogram(name: "uv_prepare_stop", scope: !1, file: !1, line: 66, type: !322, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!322 = !DISubroutineType(types: !323)
!323 = !{!57, !246}
!324 = distinct !DISubprogram(name: "uv__run_prepare", scope: !1, file: !1, line: 66, type: !325, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!325 = !DISubroutineType(types: !326)
!326 = !{null, !41}
!327 = distinct !DISubprogram(name: "uv__prepare_close", scope: !1, file: !1, line: 66, type: !265, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!328 = distinct !DISubprogram(name: "uv_check_init", scope: !1, file: !1, line: 67, type: !329, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!329 = !DISubroutineType(types: !330)
!330 = !{!57, !41, !269}
!331 = distinct !DISubprogram(name: "uv_check_start", scope: !1, file: !1, line: 67, type: !332, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!332 = !DISubroutineType(types: !333)
!333 = !{!57, !269, !286}
!334 = distinct !DISubprogram(name: "uv_check_stop", scope: !1, file: !1, line: 67, type: !335, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!335 = !DISubroutineType(types: !336)
!336 = !{!57, !269}
!337 = distinct !DISubprogram(name: "uv__run_check", scope: !1, file: !1, line: 67, type: !325, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!338 = distinct !DISubprogram(name: "uv__check_close", scope: !1, file: !1, line: 67, type: !288, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!339 = distinct !DISubprogram(name: "uv_idle_init", scope: !1, file: !1, line: 68, type: !340, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!340 = !DISubroutineType(types: !341)
!341 = !{!57, !41, !291}
!342 = distinct !DISubprogram(name: "uv_idle_start", scope: !1, file: !1, line: 68, type: !343, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!343 = !DISubroutineType(types: !344)
!344 = !{!57, !291, !308}
!345 = distinct !DISubprogram(name: "uv_idle_stop", scope: !1, file: !1, line: 68, type: !346, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!346 = !DISubroutineType(types: !347)
!347 = !{!57, !291}
!348 = distinct !DISubprogram(name: "uv__run_idle", scope: !1, file: !1, line: 68, type: !325, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!349 = distinct !DISubprogram(name: "uv__idle_close", scope: !1, file: !1, line: 68, type: !310, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !317)
!350 = !{i32 2, !"Dwarf Version", i32 4}
!351 = !{i32 2, !"Debug Info Version", i32 3}
!352 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!353 = !DILocalVariable(name: "loop", arg: 1, scope: !314, file: !1, line: 66, type: !41)
!354 = !DIExpression()
!355 = !DILocation(line: 66, column: 1, scope: !314)
!356 = !DILocalVariable(name: "handle", arg: 2, scope: !314, file: !1, line: 66, type: !246)
!357 = !DILocation(line: 66, column: 1, scope: !358)
!358 = !DILexicalBlockFile(scope: !359, file: !1, discriminator: 1)
!359 = distinct !DILexicalBlock(scope: !314, file: !1, line: 66, column: 1)
!360 = !DILocation(line: 66, column: 1, scope: !361)
!361 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 2)
!362 = distinct !DILexicalBlock(scope: !359, file: !1, line: 66, column: 1)
!363 = !DILocation(line: 66, column: 1, scope: !364)
!364 = !DILexicalBlockFile(scope: !359, file: !1, discriminator: 3)
!365 = !DILocation(line: 66, column: 1, scope: !366)
!366 = !DILexicalBlockFile(scope: !314, file: !1, discriminator: 4)
!367 = !DILocalVariable(name: "handle", arg: 1, scope: !318, file: !1, line: 66, type: !246)
!368 = !DILocation(line: 66, column: 1, scope: !318)
!369 = !DILocalVariable(name: "cb", arg: 2, scope: !318, file: !1, line: 66, type: !263)
!370 = !DILocation(line: 66, column: 1, scope: !371)
!371 = distinct !DILexicalBlock(scope: !318, file: !1, line: 66, column: 1)
!372 = !DILocation(line: 66, column: 1, scope: !373)
!373 = !DILexicalBlockFile(scope: !371, file: !1, discriminator: 5)
!374 = !DILocation(line: 66, column: 1, scope: !375)
!375 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 6)
!376 = distinct !DILexicalBlock(scope: !318, file: !1, line: 66, column: 1)
!377 = !DILocation(line: 66, column: 1, scope: !378)
!378 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 7)
!379 = !DILocation(line: 66, column: 1, scope: !380)
!380 = !DILexicalBlockFile(scope: !318, file: !1, discriminator: 8)
!381 = !DILocation(line: 66, column: 1, scope: !382)
!382 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 9)
!383 = distinct !DILexicalBlock(scope: !318, file: !1, line: 66, column: 1)
!384 = !DILocation(line: 66, column: 1, scope: !385)
!385 = !DILexicalBlockFile(scope: !318, file: !1, discriminator: 10)
!386 = !DILocation(line: 66, column: 1, scope: !387)
!387 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 11)
!388 = distinct !DILexicalBlock(scope: !318, file: !1, line: 66, column: 1)
!389 = !DILocation(line: 66, column: 1, scope: !390)
!390 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 12)
!391 = !DILocation(line: 66, column: 1, scope: !392)
!392 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 13)
!393 = !DILocation(line: 66, column: 1, scope: !394)
!394 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 14)
!395 = !DILocation(line: 66, column: 1, scope: !396)
!396 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 15)
!397 = distinct !DILexicalBlock(scope: !388, file: !1, line: 66, column: 1)
!398 = !DILocation(line: 66, column: 1, scope: !399)
!399 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 16)
!400 = !DILocation(line: 66, column: 1, scope: !401)
!401 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 17)
!402 = !DILocation(line: 66, column: 1, scope: !403)
!403 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 18)
!404 = distinct !DILexicalBlock(scope: !388, file: !1, line: 66, column: 1)
!405 = !DILocation(line: 66, column: 1, scope: !406)
!406 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 19)
!407 = distinct !DILexicalBlock(scope: !404, file: !1, line: 66, column: 1)
!408 = !DILocation(line: 66, column: 1, scope: !409)
!409 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 20)
!410 = !DILocation(line: 66, column: 1, scope: !411)
!411 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 21)
!412 = !DILocation(line: 66, column: 1, scope: !413)
!413 = !DILexicalBlockFile(scope: !318, file: !1, discriminator: 22)
!414 = !DILocation(line: 66, column: 1, scope: !415)
!415 = !DILexicalBlockFile(scope: !318, file: !1, discriminator: 23)
!416 = !DILocalVariable(name: "handle", arg: 1, scope: !321, file: !1, line: 66, type: !246)
!417 = !DILocation(line: 66, column: 1, scope: !321)
!418 = !DILocation(line: 66, column: 1, scope: !419)
!419 = distinct !DILexicalBlock(scope: !321, file: !1, line: 66, column: 1)
!420 = !DILocation(line: 66, column: 1, scope: !421)
!421 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 24)
!422 = !DILocation(line: 66, column: 1, scope: !423)
!423 = !DILexicalBlockFile(scope: !321, file: !1, discriminator: 25)
!424 = !DILocation(line: 66, column: 1, scope: !425)
!425 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 26)
!426 = distinct !DILexicalBlock(scope: !321, file: !1, line: 66, column: 1)
!427 = !DILocation(line: 66, column: 1, scope: !428)
!428 = !DILexicalBlockFile(scope: !321, file: !1, discriminator: 27)
!429 = !DILocation(line: 66, column: 1, scope: !430)
!430 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 28)
!431 = distinct !DILexicalBlock(scope: !321, file: !1, line: 66, column: 1)
!432 = !DILocation(line: 66, column: 1, scope: !433)
!433 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 29)
!434 = !DILocation(line: 66, column: 1, scope: !435)
!435 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 30)
!436 = !DILocation(line: 66, column: 1, scope: !437)
!437 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 31)
!438 = !DILocation(line: 66, column: 1, scope: !439)
!439 = !DILexicalBlockFile(scope: !440, file: !1, discriminator: 32)
!440 = distinct !DILexicalBlock(scope: !431, file: !1, line: 66, column: 1)
!441 = !DILocation(line: 66, column: 1, scope: !442)
!442 = !DILexicalBlockFile(scope: !440, file: !1, discriminator: 33)
!443 = !DILocation(line: 66, column: 1, scope: !444)
!444 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 34)
!445 = !DILocation(line: 66, column: 1, scope: !446)
!446 = !DILexicalBlockFile(scope: !447, file: !1, discriminator: 35)
!447 = distinct !DILexicalBlock(scope: !431, file: !1, line: 66, column: 1)
!448 = !DILocation(line: 66, column: 1, scope: !449)
!449 = !DILexicalBlockFile(scope: !450, file: !1, discriminator: 36)
!450 = distinct !DILexicalBlock(scope: !447, file: !1, line: 66, column: 1)
!451 = !DILocation(line: 66, column: 1, scope: !452)
!452 = !DILexicalBlockFile(scope: !450, file: !1, discriminator: 37)
!453 = !DILocation(line: 66, column: 1, scope: !454)
!454 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 38)
!455 = !DILocation(line: 66, column: 1, scope: !456)
!456 = !DILexicalBlockFile(scope: !321, file: !1, discriminator: 39)
!457 = !DILocation(line: 66, column: 1, scope: !458)
!458 = !DILexicalBlockFile(scope: !321, file: !1, discriminator: 40)
!459 = !DILocalVariable(name: "loop", arg: 1, scope: !324, file: !1, line: 66, type: !41)
!460 = !DILocation(line: 66, column: 1, scope: !324)
!461 = !DILocalVariable(name: "h", scope: !324, file: !1, line: 66, type: !246)
!462 = !DILocalVariable(name: "queue", scope: !324, file: !1, line: 66, type: !242)
!463 = !DILocalVariable(name: "q", scope: !324, file: !1, line: 66, type: !241)
!464 = !DILocation(line: 66, column: 1, scope: !465)
!465 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 41)
!466 = distinct !DILexicalBlock(scope: !467, file: !1, line: 66, column: 1)
!467 = distinct !DILexicalBlock(scope: !324, file: !1, line: 66, column: 1)
!468 = !DILocation(line: 66, column: 1, scope: !469)
!469 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 42)
!470 = !DILocation(line: 66, column: 1, scope: !471)
!471 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 43)
!472 = distinct !DILexicalBlock(scope: !466, file: !1, line: 66, column: 1)
!473 = !DILocation(line: 66, column: 1, scope: !474)
!474 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 44)
!475 = !DILocalVariable(name: "q", scope: !476, file: !1, line: 66, type: !241)
!476 = distinct !DILexicalBlock(scope: !466, file: !1, line: 66, column: 1)
!477 = !DILocation(line: 66, column: 1, scope: !476)
!478 = !DILocation(line: 66, column: 1, scope: !479)
!479 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 45)
!480 = !DILocation(line: 66, column: 1, scope: !481)
!481 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 46)
!482 = distinct !DILexicalBlock(scope: !476, file: !1, line: 66, column: 1)
!483 = !DILocation(line: 66, column: 1, scope: !484)
!484 = !DILexicalBlockFile(scope: !467, file: !1, discriminator: 47)
!485 = !DILocation(line: 66, column: 1, scope: !486)
!486 = !DILexicalBlockFile(scope: !324, file: !1, discriminator: 48)
!487 = !DILocation(line: 66, column: 1, scope: !488)
!488 = !DILexicalBlockFile(scope: !324, file: !1, discriminator: 49)
!489 = !DILocation(line: 66, column: 1, scope: !490)
!490 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 50)
!491 = distinct !DILexicalBlock(scope: !324, file: !1, line: 66, column: 1)
!492 = !DILocation(line: 66, column: 1, scope: !493)
!493 = !DILexicalBlockFile(scope: !494, file: !1, discriminator: 51)
!494 = distinct !DILexicalBlock(scope: !491, file: !1, line: 66, column: 1)
!495 = !DILocation(line: 66, column: 1, scope: !496)
!496 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 52)
!497 = !DILocation(line: 66, column: 1, scope: !498)
!498 = !DILexicalBlockFile(scope: !499, file: !1, discriminator: 53)
!499 = distinct !DILexicalBlock(scope: !491, file: !1, line: 66, column: 1)
!500 = !DILocation(line: 66, column: 1, scope: !501)
!501 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 54)
!502 = !DILocation(line: 66, column: 1, scope: !503)
!503 = !DILexicalBlockFile(scope: !324, file: !1, discriminator: 55)
!504 = !DILocalVariable(name: "handle", arg: 1, scope: !327, file: !1, line: 66, type: !246)
!505 = !DILocation(line: 66, column: 1, scope: !327)
!506 = !DILocalVariable(name: "loop", arg: 1, scope: !328, file: !1, line: 67, type: !41)
!507 = !DILocation(line: 67, column: 1, scope: !328)
!508 = !DILocalVariable(name: "handle", arg: 2, scope: !328, file: !1, line: 67, type: !269)
!509 = !DILocation(line: 67, column: 1, scope: !510)
!510 = !DILexicalBlockFile(scope: !511, file: !1, discriminator: 1)
!511 = distinct !DILexicalBlock(scope: !328, file: !1, line: 67, column: 1)
!512 = !DILocation(line: 67, column: 1, scope: !513)
!513 = !DILexicalBlockFile(scope: !514, file: !1, discriminator: 2)
!514 = distinct !DILexicalBlock(scope: !511, file: !1, line: 67, column: 1)
!515 = !DILocation(line: 67, column: 1, scope: !516)
!516 = !DILexicalBlockFile(scope: !511, file: !1, discriminator: 3)
!517 = !DILocation(line: 67, column: 1, scope: !518)
!518 = !DILexicalBlockFile(scope: !328, file: !1, discriminator: 4)
!519 = !DILocalVariable(name: "handle", arg: 1, scope: !331, file: !1, line: 67, type: !269)
!520 = !DILocation(line: 67, column: 1, scope: !331)
!521 = !DILocalVariable(name: "cb", arg: 2, scope: !331, file: !1, line: 67, type: !286)
!522 = !DILocation(line: 67, column: 1, scope: !523)
!523 = distinct !DILexicalBlock(scope: !331, file: !1, line: 67, column: 1)
!524 = !DILocation(line: 67, column: 1, scope: !525)
!525 = !DILexicalBlockFile(scope: !523, file: !1, discriminator: 5)
!526 = !DILocation(line: 67, column: 1, scope: !527)
!527 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 6)
!528 = distinct !DILexicalBlock(scope: !331, file: !1, line: 67, column: 1)
!529 = !DILocation(line: 67, column: 1, scope: !530)
!530 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 7)
!531 = !DILocation(line: 67, column: 1, scope: !532)
!532 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 8)
!533 = !DILocation(line: 67, column: 1, scope: !534)
!534 = !DILexicalBlockFile(scope: !535, file: !1, discriminator: 9)
!535 = distinct !DILexicalBlock(scope: !331, file: !1, line: 67, column: 1)
!536 = !DILocation(line: 67, column: 1, scope: !537)
!537 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 10)
!538 = !DILocation(line: 67, column: 1, scope: !539)
!539 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 11)
!540 = distinct !DILexicalBlock(scope: !331, file: !1, line: 67, column: 1)
!541 = !DILocation(line: 67, column: 1, scope: !542)
!542 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 12)
!543 = !DILocation(line: 67, column: 1, scope: !544)
!544 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 13)
!545 = !DILocation(line: 67, column: 1, scope: !546)
!546 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 14)
!547 = !DILocation(line: 67, column: 1, scope: !548)
!548 = !DILexicalBlockFile(scope: !549, file: !1, discriminator: 15)
!549 = distinct !DILexicalBlock(scope: !540, file: !1, line: 67, column: 1)
!550 = !DILocation(line: 67, column: 1, scope: !551)
!551 = !DILexicalBlockFile(scope: !549, file: !1, discriminator: 16)
!552 = !DILocation(line: 67, column: 1, scope: !553)
!553 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 17)
!554 = !DILocation(line: 67, column: 1, scope: !555)
!555 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 18)
!556 = distinct !DILexicalBlock(scope: !540, file: !1, line: 67, column: 1)
!557 = !DILocation(line: 67, column: 1, scope: !558)
!558 = !DILexicalBlockFile(scope: !559, file: !1, discriminator: 19)
!559 = distinct !DILexicalBlock(scope: !556, file: !1, line: 67, column: 1)
!560 = !DILocation(line: 67, column: 1, scope: !561)
!561 = !DILexicalBlockFile(scope: !559, file: !1, discriminator: 20)
!562 = !DILocation(line: 67, column: 1, scope: !563)
!563 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 21)
!564 = !DILocation(line: 67, column: 1, scope: !565)
!565 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 22)
!566 = !DILocation(line: 67, column: 1, scope: !567)
!567 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 23)
!568 = !DILocalVariable(name: "handle", arg: 1, scope: !334, file: !1, line: 67, type: !269)
!569 = !DILocation(line: 67, column: 1, scope: !334)
!570 = !DILocation(line: 67, column: 1, scope: !571)
!571 = distinct !DILexicalBlock(scope: !334, file: !1, line: 67, column: 1)
!572 = !DILocation(line: 67, column: 1, scope: !573)
!573 = !DILexicalBlockFile(scope: !571, file: !1, discriminator: 24)
!574 = !DILocation(line: 67, column: 1, scope: !575)
!575 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 25)
!576 = !DILocation(line: 67, column: 1, scope: !577)
!577 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 26)
!578 = distinct !DILexicalBlock(scope: !334, file: !1, line: 67, column: 1)
!579 = !DILocation(line: 67, column: 1, scope: !580)
!580 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 27)
!581 = !DILocation(line: 67, column: 1, scope: !582)
!582 = !DILexicalBlockFile(scope: !583, file: !1, discriminator: 28)
!583 = distinct !DILexicalBlock(scope: !334, file: !1, line: 67, column: 1)
!584 = !DILocation(line: 67, column: 1, scope: !585)
!585 = !DILexicalBlockFile(scope: !583, file: !1, discriminator: 29)
!586 = !DILocation(line: 67, column: 1, scope: !587)
!587 = !DILexicalBlockFile(scope: !583, file: !1, discriminator: 30)
!588 = !DILocation(line: 67, column: 1, scope: !589)
!589 = !DILexicalBlockFile(scope: !583, file: !1, discriminator: 31)
!590 = !DILocation(line: 67, column: 1, scope: !591)
!591 = !DILexicalBlockFile(scope: !592, file: !1, discriminator: 32)
!592 = distinct !DILexicalBlock(scope: !583, file: !1, line: 67, column: 1)
!593 = !DILocation(line: 67, column: 1, scope: !594)
!594 = !DILexicalBlockFile(scope: !592, file: !1, discriminator: 33)
!595 = !DILocation(line: 67, column: 1, scope: !596)
!596 = !DILexicalBlockFile(scope: !583, file: !1, discriminator: 34)
!597 = !DILocation(line: 67, column: 1, scope: !598)
!598 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 35)
!599 = distinct !DILexicalBlock(scope: !583, file: !1, line: 67, column: 1)
!600 = !DILocation(line: 67, column: 1, scope: !601)
!601 = !DILexicalBlockFile(scope: !602, file: !1, discriminator: 36)
!602 = distinct !DILexicalBlock(scope: !599, file: !1, line: 67, column: 1)
!603 = !DILocation(line: 67, column: 1, scope: !604)
!604 = !DILexicalBlockFile(scope: !602, file: !1, discriminator: 37)
!605 = !DILocation(line: 67, column: 1, scope: !606)
!606 = !DILexicalBlockFile(scope: !583, file: !1, discriminator: 38)
!607 = !DILocation(line: 67, column: 1, scope: !608)
!608 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 39)
!609 = !DILocation(line: 67, column: 1, scope: !610)
!610 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 40)
!611 = !DILocalVariable(name: "loop", arg: 1, scope: !337, file: !1, line: 67, type: !41)
!612 = !DILocation(line: 67, column: 1, scope: !337)
!613 = !DILocalVariable(name: "h", scope: !337, file: !1, line: 67, type: !269)
!614 = !DILocalVariable(name: "queue", scope: !337, file: !1, line: 67, type: !242)
!615 = !DILocalVariable(name: "q", scope: !337, file: !1, line: 67, type: !241)
!616 = !DILocation(line: 67, column: 1, scope: !617)
!617 = !DILexicalBlockFile(scope: !618, file: !1, discriminator: 41)
!618 = distinct !DILexicalBlock(scope: !619, file: !1, line: 67, column: 1)
!619 = distinct !DILexicalBlock(scope: !337, file: !1, line: 67, column: 1)
!620 = !DILocation(line: 67, column: 1, scope: !621)
!621 = !DILexicalBlockFile(scope: !618, file: !1, discriminator: 42)
!622 = !DILocation(line: 67, column: 1, scope: !623)
!623 = !DILexicalBlockFile(scope: !624, file: !1, discriminator: 43)
!624 = distinct !DILexicalBlock(scope: !618, file: !1, line: 67, column: 1)
!625 = !DILocation(line: 67, column: 1, scope: !626)
!626 = !DILexicalBlockFile(scope: !624, file: !1, discriminator: 44)
!627 = !DILocalVariable(name: "q", scope: !628, file: !1, line: 67, type: !241)
!628 = distinct !DILexicalBlock(scope: !618, file: !1, line: 67, column: 1)
!629 = !DILocation(line: 67, column: 1, scope: !628)
!630 = !DILocation(line: 67, column: 1, scope: !631)
!631 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 45)
!632 = !DILocation(line: 67, column: 1, scope: !633)
!633 = !DILexicalBlockFile(scope: !634, file: !1, discriminator: 46)
!634 = distinct !DILexicalBlock(scope: !628, file: !1, line: 67, column: 1)
!635 = !DILocation(line: 67, column: 1, scope: !636)
!636 = !DILexicalBlockFile(scope: !619, file: !1, discriminator: 47)
!637 = !DILocation(line: 67, column: 1, scope: !638)
!638 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 48)
!639 = !DILocation(line: 67, column: 1, scope: !640)
!640 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 49)
!641 = !DILocation(line: 67, column: 1, scope: !642)
!642 = !DILexicalBlockFile(scope: !643, file: !1, discriminator: 50)
!643 = distinct !DILexicalBlock(scope: !337, file: !1, line: 67, column: 1)
!644 = !DILocation(line: 67, column: 1, scope: !645)
!645 = !DILexicalBlockFile(scope: !646, file: !1, discriminator: 51)
!646 = distinct !DILexicalBlock(scope: !643, file: !1, line: 67, column: 1)
!647 = !DILocation(line: 67, column: 1, scope: !648)
!648 = !DILexicalBlockFile(scope: !643, file: !1, discriminator: 52)
!649 = !DILocation(line: 67, column: 1, scope: !650)
!650 = !DILexicalBlockFile(scope: !651, file: !1, discriminator: 53)
!651 = distinct !DILexicalBlock(scope: !643, file: !1, line: 67, column: 1)
!652 = !DILocation(line: 67, column: 1, scope: !653)
!653 = !DILexicalBlockFile(scope: !643, file: !1, discriminator: 54)
!654 = !DILocation(line: 67, column: 1, scope: !655)
!655 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 55)
!656 = !DILocalVariable(name: "handle", arg: 1, scope: !338, file: !1, line: 67, type: !269)
!657 = !DILocation(line: 67, column: 1, scope: !338)
!658 = !DILocalVariable(name: "loop", arg: 1, scope: !339, file: !1, line: 68, type: !41)
!659 = !DILocation(line: 68, column: 1, scope: !339)
!660 = !DILocalVariable(name: "handle", arg: 2, scope: !339, file: !1, line: 68, type: !291)
!661 = !DILocation(line: 68, column: 1, scope: !662)
!662 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 1)
!663 = distinct !DILexicalBlock(scope: !339, file: !1, line: 68, column: 1)
!664 = !DILocation(line: 68, column: 1, scope: !665)
!665 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 2)
!666 = distinct !DILexicalBlock(scope: !663, file: !1, line: 68, column: 1)
!667 = !DILocation(line: 68, column: 1, scope: !668)
!668 = !DILexicalBlockFile(scope: !663, file: !1, discriminator: 3)
!669 = !DILocation(line: 68, column: 1, scope: !670)
!670 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 4)
!671 = !DILocalVariable(name: "handle", arg: 1, scope: !342, file: !1, line: 68, type: !291)
!672 = !DILocation(line: 68, column: 1, scope: !342)
!673 = !DILocalVariable(name: "cb", arg: 2, scope: !342, file: !1, line: 68, type: !308)
!674 = !DILocation(line: 68, column: 1, scope: !675)
!675 = distinct !DILexicalBlock(scope: !342, file: !1, line: 68, column: 1)
!676 = !DILocation(line: 68, column: 1, scope: !677)
!677 = !DILexicalBlockFile(scope: !675, file: !1, discriminator: 5)
!678 = !DILocation(line: 68, column: 1, scope: !679)
!679 = !DILexicalBlockFile(scope: !680, file: !1, discriminator: 6)
!680 = distinct !DILexicalBlock(scope: !342, file: !1, line: 68, column: 1)
!681 = !DILocation(line: 68, column: 1, scope: !682)
!682 = !DILexicalBlockFile(scope: !680, file: !1, discriminator: 7)
!683 = !DILocation(line: 68, column: 1, scope: !684)
!684 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 8)
!685 = !DILocation(line: 68, column: 1, scope: !686)
!686 = !DILexicalBlockFile(scope: !687, file: !1, discriminator: 9)
!687 = distinct !DILexicalBlock(scope: !342, file: !1, line: 68, column: 1)
!688 = !DILocation(line: 68, column: 1, scope: !689)
!689 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 10)
!690 = !DILocation(line: 68, column: 1, scope: !691)
!691 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 11)
!692 = distinct !DILexicalBlock(scope: !342, file: !1, line: 68, column: 1)
!693 = !DILocation(line: 68, column: 1, scope: !694)
!694 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 12)
!695 = !DILocation(line: 68, column: 1, scope: !696)
!696 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 13)
!697 = !DILocation(line: 68, column: 1, scope: !698)
!698 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 14)
!699 = !DILocation(line: 68, column: 1, scope: !700)
!700 = !DILexicalBlockFile(scope: !701, file: !1, discriminator: 15)
!701 = distinct !DILexicalBlock(scope: !692, file: !1, line: 68, column: 1)
!702 = !DILocation(line: 68, column: 1, scope: !703)
!703 = !DILexicalBlockFile(scope: !701, file: !1, discriminator: 16)
!704 = !DILocation(line: 68, column: 1, scope: !705)
!705 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 17)
!706 = !DILocation(line: 68, column: 1, scope: !707)
!707 = !DILexicalBlockFile(scope: !708, file: !1, discriminator: 18)
!708 = distinct !DILexicalBlock(scope: !692, file: !1, line: 68, column: 1)
!709 = !DILocation(line: 68, column: 1, scope: !710)
!710 = !DILexicalBlockFile(scope: !711, file: !1, discriminator: 19)
!711 = distinct !DILexicalBlock(scope: !708, file: !1, line: 68, column: 1)
!712 = !DILocation(line: 68, column: 1, scope: !713)
!713 = !DILexicalBlockFile(scope: !711, file: !1, discriminator: 20)
!714 = !DILocation(line: 68, column: 1, scope: !715)
!715 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 21)
!716 = !DILocation(line: 68, column: 1, scope: !717)
!717 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 22)
!718 = !DILocation(line: 68, column: 1, scope: !719)
!719 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 23)
!720 = !DILocalVariable(name: "handle", arg: 1, scope: !345, file: !1, line: 68, type: !291)
!721 = !DILocation(line: 68, column: 1, scope: !345)
!722 = !DILocation(line: 68, column: 1, scope: !723)
!723 = distinct !DILexicalBlock(scope: !345, file: !1, line: 68, column: 1)
!724 = !DILocation(line: 68, column: 1, scope: !725)
!725 = !DILexicalBlockFile(scope: !723, file: !1, discriminator: 24)
!726 = !DILocation(line: 68, column: 1, scope: !727)
!727 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 25)
!728 = !DILocation(line: 68, column: 1, scope: !729)
!729 = !DILexicalBlockFile(scope: !730, file: !1, discriminator: 26)
!730 = distinct !DILexicalBlock(scope: !345, file: !1, line: 68, column: 1)
!731 = !DILocation(line: 68, column: 1, scope: !732)
!732 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 27)
!733 = !DILocation(line: 68, column: 1, scope: !734)
!734 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 28)
!735 = distinct !DILexicalBlock(scope: !345, file: !1, line: 68, column: 1)
!736 = !DILocation(line: 68, column: 1, scope: !737)
!737 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 29)
!738 = !DILocation(line: 68, column: 1, scope: !739)
!739 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 30)
!740 = !DILocation(line: 68, column: 1, scope: !741)
!741 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 31)
!742 = !DILocation(line: 68, column: 1, scope: !743)
!743 = !DILexicalBlockFile(scope: !744, file: !1, discriminator: 32)
!744 = distinct !DILexicalBlock(scope: !735, file: !1, line: 68, column: 1)
!745 = !DILocation(line: 68, column: 1, scope: !746)
!746 = !DILexicalBlockFile(scope: !744, file: !1, discriminator: 33)
!747 = !DILocation(line: 68, column: 1, scope: !748)
!748 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 34)
!749 = !DILocation(line: 68, column: 1, scope: !750)
!750 = !DILexicalBlockFile(scope: !751, file: !1, discriminator: 35)
!751 = distinct !DILexicalBlock(scope: !735, file: !1, line: 68, column: 1)
!752 = !DILocation(line: 68, column: 1, scope: !753)
!753 = !DILexicalBlockFile(scope: !754, file: !1, discriminator: 36)
!754 = distinct !DILexicalBlock(scope: !751, file: !1, line: 68, column: 1)
!755 = !DILocation(line: 68, column: 1, scope: !756)
!756 = !DILexicalBlockFile(scope: !754, file: !1, discriminator: 37)
!757 = !DILocation(line: 68, column: 1, scope: !758)
!758 = !DILexicalBlockFile(scope: !735, file: !1, discriminator: 38)
!759 = !DILocation(line: 68, column: 1, scope: !760)
!760 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 39)
!761 = !DILocation(line: 68, column: 1, scope: !762)
!762 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 40)
!763 = !DILocalVariable(name: "loop", arg: 1, scope: !348, file: !1, line: 68, type: !41)
!764 = !DILocation(line: 68, column: 1, scope: !348)
!765 = !DILocalVariable(name: "h", scope: !348, file: !1, line: 68, type: !291)
!766 = !DILocalVariable(name: "queue", scope: !348, file: !1, line: 68, type: !242)
!767 = !DILocalVariable(name: "q", scope: !348, file: !1, line: 68, type: !241)
!768 = !DILocation(line: 68, column: 1, scope: !769)
!769 = !DILexicalBlockFile(scope: !770, file: !1, discriminator: 41)
!770 = distinct !DILexicalBlock(scope: !771, file: !1, line: 68, column: 1)
!771 = distinct !DILexicalBlock(scope: !348, file: !1, line: 68, column: 1)
!772 = !DILocation(line: 68, column: 1, scope: !773)
!773 = !DILexicalBlockFile(scope: !770, file: !1, discriminator: 42)
!774 = !DILocation(line: 68, column: 1, scope: !775)
!775 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 43)
!776 = distinct !DILexicalBlock(scope: !770, file: !1, line: 68, column: 1)
!777 = !DILocation(line: 68, column: 1, scope: !778)
!778 = !DILexicalBlockFile(scope: !776, file: !1, discriminator: 44)
!779 = !DILocalVariable(name: "q", scope: !780, file: !1, line: 68, type: !241)
!780 = distinct !DILexicalBlock(scope: !770, file: !1, line: 68, column: 1)
!781 = !DILocation(line: 68, column: 1, scope: !780)
!782 = !DILocation(line: 68, column: 1, scope: !783)
!783 = !DILexicalBlockFile(scope: !780, file: !1, discriminator: 45)
!784 = !DILocation(line: 68, column: 1, scope: !785)
!785 = !DILexicalBlockFile(scope: !786, file: !1, discriminator: 46)
!786 = distinct !DILexicalBlock(scope: !780, file: !1, line: 68, column: 1)
!787 = !DILocation(line: 68, column: 1, scope: !788)
!788 = !DILexicalBlockFile(scope: !771, file: !1, discriminator: 47)
!789 = !DILocation(line: 68, column: 1, scope: !790)
!790 = !DILexicalBlockFile(scope: !348, file: !1, discriminator: 48)
!791 = !DILocation(line: 68, column: 1, scope: !792)
!792 = !DILexicalBlockFile(scope: !348, file: !1, discriminator: 49)
!793 = !DILocation(line: 68, column: 1, scope: !794)
!794 = !DILexicalBlockFile(scope: !795, file: !1, discriminator: 50)
!795 = distinct !DILexicalBlock(scope: !348, file: !1, line: 68, column: 1)
!796 = !DILocation(line: 68, column: 1, scope: !797)
!797 = !DILexicalBlockFile(scope: !798, file: !1, discriminator: 51)
!798 = distinct !DILexicalBlock(scope: !795, file: !1, line: 68, column: 1)
!799 = !DILocation(line: 68, column: 1, scope: !800)
!800 = !DILexicalBlockFile(scope: !795, file: !1, discriminator: 52)
!801 = !DILocation(line: 68, column: 1, scope: !802)
!802 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 53)
!803 = distinct !DILexicalBlock(scope: !795, file: !1, line: 68, column: 1)
!804 = !DILocation(line: 68, column: 1, scope: !805)
!805 = !DILexicalBlockFile(scope: !795, file: !1, discriminator: 54)
!806 = !DILocation(line: 68, column: 1, scope: !807)
!807 = !DILexicalBlockFile(scope: !348, file: !1, discriminator: 55)
!808 = !DILocalVariable(name: "handle", arg: 1, scope: !349, file: !1, line: 68, type: !291)
!809 = !DILocation(line: 68, column: 1, scope: !349)
