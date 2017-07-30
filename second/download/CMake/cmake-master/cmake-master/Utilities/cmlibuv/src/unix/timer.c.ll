; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/timer.c'
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
%struct.uv_timer_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, void (%struct.uv_timer_s*)*, [3 x i8*], i64, i64, i64 }
%union.anon.4 = type { [4 x i8*] }
%struct.heap = type { %struct.heap_node*, i32 }
%struct.heap_node = type { %struct.heap_node*, %struct.heap_node*, %struct.heap_node* }

@.str = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.1 = private unnamed_addr constant [69 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/timer.c\00", align 1
@__PRETTY_FUNCTION__.uv_timer_start = private unnamed_addr constant [66 x i8] c"int uv_timer_start(uv_timer_t *, uv_timer_cb, uint64_t, uint64_t)\00", align 1
@__PRETTY_FUNCTION__.uv_timer_stop = private unnamed_addr constant [32 x i8] c"int uv_timer_stop(uv_timer_t *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_timer_init(%struct.uv_loop_s* %loop, %struct.uv_timer_s* %handle) #0 !dbg !288 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !336, metadata !337), !dbg !338
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !339, metadata !337), !dbg !340
  br label %do.body, !dbg !341

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !342
  %1 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !342
  %2 = bitcast %struct.uv_timer_s* %1 to %struct.uv_handle_s*, !dbg !342
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %2, i32 0, i32 1, !dbg !342
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !342
  %3 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !342
  %4 = bitcast %struct.uv_timer_s* %3 to %struct.uv_handle_s*, !dbg !342
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %4, i32 0, i32 2, !dbg !342
  store i32 13, i32* %type, align 8, !dbg !342
  %5 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !342
  %6 = bitcast %struct.uv_timer_s* %5 to %struct.uv_handle_s*, !dbg !342
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %6, i32 0, i32 7, !dbg !342
  store i32 8192, i32* %flags, align 8, !dbg !342
  br label %do.body2, !dbg !342

do.body2:                                         ; preds = %do.body
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !345
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 2, !dbg !345
  %8 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !345
  %9 = bitcast %struct.uv_timer_s* %8 to %struct.uv_handle_s*, !dbg !345
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 4, !dbg !345
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !345
  %10 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !345
  store [2 x i8*]* %handle_queue, [2 x i8*]** %10, align 8, !dbg !345
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !345
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 2, !dbg !345
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !345
  %12 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !345
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !345
  %14 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !345
  %15 = bitcast %struct.uv_timer_s* %14 to %struct.uv_handle_s*, !dbg !345
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %15, i32 0, i32 4, !dbg !345
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !345
  %16 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !345
  store [2 x i8*]* %13, [2 x i8*]** %16, align 8, !dbg !345
  %17 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !345
  %18 = bitcast %struct.uv_timer_s* %17 to %struct.uv_handle_s*, !dbg !345
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !345
  %19 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !345
  %20 = bitcast %struct.uv_timer_s* %19 to %struct.uv_handle_s*, !dbg !345
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %20, i32 0, i32 4, !dbg !345
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !345
  %21 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !345
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !345
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 0, !dbg !345
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !345
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %23, align 8, !dbg !345
  %24 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !345
  %25 = bitcast %struct.uv_timer_s* %24 to %struct.uv_handle_s*, !dbg !345
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !345
  %26 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !345
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %26, i32 0, i32 2, !dbg !345
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !345
  %27 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !345
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %27, align 8, !dbg !345
  br label %do.end, !dbg !345

do.end:                                           ; preds = %do.body2
  %28 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !348
  %29 = bitcast %struct.uv_timer_s* %28 to %struct.uv_handle_s*, !dbg !348
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %29, i32 0, i32 6, !dbg !348
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !348
  br label %do.end15, !dbg !348

do.end15:                                         ; preds = %do.end
  %30 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !350
  %timer_cb = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %30, i32 0, i32 8, !dbg !351
  store void (%struct.uv_timer_s*)* null, void (%struct.uv_timer_s*)** %timer_cb, align 8, !dbg !352
  %31 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !353
  %repeat = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %31, i32 0, i32 11, !dbg !354
  store i64 0, i64* %repeat, align 8, !dbg !355
  ret i32 0, !dbg !356
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @uv_timer_start(%struct.uv_timer_s* %handle, void (%struct.uv_timer_s*)* %cb, i64 %timeout, i64 %repeat) #0 !dbg !292 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  %cb.addr = alloca void (%struct.uv_timer_s*)*, align 8
  %timeout.addr = alloca i64, align 8
  %repeat.addr = alloca i64, align 8
  %clamped_timeout = alloca i64, align 8
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !357, metadata !337), !dbg !358
  store void (%struct.uv_timer_s*)* %cb, void (%struct.uv_timer_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_timer_s*)** %cb.addr, metadata !359, metadata !337), !dbg !360
  store i64 %timeout, i64* %timeout.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %timeout.addr, metadata !361, metadata !337), !dbg !362
  store i64 %repeat, i64* %repeat.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %repeat.addr, metadata !363, metadata !337), !dbg !364
  call void @llvm.dbg.declare(metadata i64* %clamped_timeout, metadata !365, metadata !337), !dbg !366
  %0 = load void (%struct.uv_timer_s*)*, void (%struct.uv_timer_s*)** %cb.addr, align 8, !dbg !367
  %cmp = icmp eq void (%struct.uv_timer_s*)* %0, null, !dbg !369
  br i1 %cmp, label %if.then, label %if.end, !dbg !370

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !371
  br label %return, !dbg !371

if.end:                                           ; preds = %entry
  %1 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !372
  %flags = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %1, i32 0, i32 7, !dbg !372
  %2 = load i32, i32* %flags, align 8, !dbg !372
  %and = and i32 %2, 16384, !dbg !372
  %cmp1 = icmp ne i32 %and, 0, !dbg !372
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !374

if.then2:                                         ; preds = %if.end
  %3 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !375
  %call = call i32 @uv_timer_stop(%struct.uv_timer_s* %3), !dbg !376
  br label %if.end3, !dbg !376

if.end3:                                          ; preds = %if.then2, %if.end
  %4 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !377
  %loop = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %4, i32 0, i32 1, !dbg !378
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !378
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 27, !dbg !379
  %6 = load i64, i64* %time, align 8, !dbg !379
  %7 = load i64, i64* %timeout.addr, align 8, !dbg !380
  %add = add i64 %6, %7, !dbg !381
  store i64 %add, i64* %clamped_timeout, align 8, !dbg !382
  %8 = load i64, i64* %clamped_timeout, align 8, !dbg !383
  %9 = load i64, i64* %timeout.addr, align 8, !dbg !385
  %cmp4 = icmp ult i64 %8, %9, !dbg !386
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !387

if.then5:                                         ; preds = %if.end3
  store i64 -1, i64* %clamped_timeout, align 8, !dbg !388
  br label %if.end6, !dbg !389

if.end6:                                          ; preds = %if.then5, %if.end3
  %10 = load void (%struct.uv_timer_s*)*, void (%struct.uv_timer_s*)** %cb.addr, align 8, !dbg !390
  %11 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !391
  %timer_cb = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %11, i32 0, i32 8, !dbg !392
  store void (%struct.uv_timer_s*)* %10, void (%struct.uv_timer_s*)** %timer_cb, align 8, !dbg !393
  %12 = load i64, i64* %clamped_timeout, align 8, !dbg !394
  %13 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !395
  %timeout7 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %13, i32 0, i32 10, !dbg !396
  store i64 %12, i64* %timeout7, align 8, !dbg !397
  %14 = load i64, i64* %repeat.addr, align 8, !dbg !398
  %15 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !399
  %repeat8 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %15, i32 0, i32 11, !dbg !400
  store i64 %14, i64* %repeat8, align 8, !dbg !401
  %16 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !402
  %loop9 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %16, i32 0, i32 1, !dbg !403
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop9, align 8, !dbg !403
  %timer_counter = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 26, !dbg !404
  %18 = load i64, i64* %timer_counter, align 8, !dbg !405
  %inc = add i64 %18, 1, !dbg !405
  store i64 %inc, i64* %timer_counter, align 8, !dbg !405
  %19 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !406
  %start_id = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %19, i32 0, i32 12, !dbg !407
  store i64 %18, i64* %start_id, align 8, !dbg !408
  %20 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !409
  %loop10 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %20, i32 0, i32 1, !dbg !410
  %21 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop10, align 8, !dbg !410
  %timer_heap = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %21, i32 0, i32 25, !dbg !411
  %22 = bitcast %struct.anon.1* %timer_heap to %struct.heap*, !dbg !412
  %23 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !413
  %heap_node = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %23, i32 0, i32 9, !dbg !414
  %24 = bitcast [3 x i8*]* %heap_node to %struct.heap_node*, !dbg !415
  call void @heap_insert(%struct.heap* %22, %struct.heap_node* %24, i32 (%struct.heap_node*, %struct.heap_node*)* @timer_less_than), !dbg !416
  br label %do.body, !dbg !417

do.body:                                          ; preds = %if.end6
  %25 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !418
  %flags11 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %25, i32 0, i32 7, !dbg !418
  %26 = load i32, i32* %flags11, align 8, !dbg !418
  %and12 = and i32 %26, 0, !dbg !418
  %cmp13 = icmp eq i32 %and12, 0, !dbg !418
  br i1 %cmp13, label %cond.true, label %cond.false, !dbg !418

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !421

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.1, i32 0, i32 0), i32 87, i8* getelementptr inbounds ([66 x i8], [66 x i8]* @__PRETTY_FUNCTION__.uv_timer_start, i32 0, i32 0)) #4, !dbg !423
  unreachable, !dbg !423
                                                  ; No predecessors!
  br label %cond.end, !dbg !425

cond.end:                                         ; preds = %27, %cond.true
  %28 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !427
  %flags14 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %28, i32 0, i32 7, !dbg !427
  %29 = load i32, i32* %flags14, align 8, !dbg !427
  %and15 = and i32 %29, 16384, !dbg !427
  %cmp16 = icmp ne i32 %and15, 0, !dbg !427
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !427

if.then17:                                        ; preds = %cond.end
  br label %do.end28, !dbg !430

if.end18:                                         ; preds = %cond.end
  %30 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !432
  %flags19 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %30, i32 0, i32 7, !dbg !432
  %31 = load i32, i32* %flags19, align 8, !dbg !432
  %or = or i32 %31, 16384, !dbg !432
  store i32 %or, i32* %flags19, align 8, !dbg !432
  %32 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !432
  %flags20 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %32, i32 0, i32 7, !dbg !432
  %33 = load i32, i32* %flags20, align 8, !dbg !432
  %and21 = and i32 %33, 8192, !dbg !432
  %cmp22 = icmp ne i32 %and21, 0, !dbg !432
  br i1 %cmp22, label %if.then23, label %if.end27, !dbg !432

if.then23:                                        ; preds = %if.end18
  br label %do.body24, !dbg !434

do.body24:                                        ; preds = %if.then23
  %34 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !437
  %loop25 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %34, i32 0, i32 1, !dbg !437
  %35 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop25, align 8, !dbg !437
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %35, i32 0, i32 1, !dbg !437
  %36 = load i32, i32* %active_handles, align 8, !dbg !437
  %inc26 = add i32 %36, 1, !dbg !437
  store i32 %inc26, i32* %active_handles, align 8, !dbg !437
  br label %do.end, !dbg !437

do.end:                                           ; preds = %do.body24
  br label %if.end27, !dbg !440

if.end27:                                         ; preds = %do.end, %if.end18
  br label %do.end28, !dbg !442

do.end28:                                         ; preds = %if.end27, %if.then17
  store i32 0, i32* %retval, align 4, !dbg !444
  br label %return, !dbg !444

return:                                           ; preds = %do.end28, %if.then
  %37 = load i32, i32* %retval, align 4, !dbg !445
  ret i32 %37, !dbg !445
}

; Function Attrs: nounwind uwtable
define i32 @uv_timer_stop(%struct.uv_timer_s* %handle) #0 !dbg !295 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !446, metadata !337), !dbg !447
  %0 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !448
  %flags = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %0, i32 0, i32 7, !dbg !448
  %1 = load i32, i32* %flags, align 8, !dbg !448
  %and = and i32 %1, 16384, !dbg !448
  %cmp = icmp ne i32 %and, 0, !dbg !448
  br i1 %cmp, label %if.end, label %if.then, !dbg !450

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !451
  br label %return, !dbg !451

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !452
  %loop = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %2, i32 0, i32 1, !dbg !453
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !453
  %timer_heap = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 25, !dbg !454
  %4 = bitcast %struct.anon.1* %timer_heap to %struct.heap*, !dbg !455
  %5 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !456
  %heap_node = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %5, i32 0, i32 9, !dbg !457
  %6 = bitcast [3 x i8*]* %heap_node to %struct.heap_node*, !dbg !458
  call void @heap_remove(%struct.heap* %4, %struct.heap_node* %6, i32 (%struct.heap_node*, %struct.heap_node*)* @timer_less_than), !dbg !459
  br label %do.body, !dbg !460

do.body:                                          ; preds = %if.end
  %7 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !461
  %flags1 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %7, i32 0, i32 7, !dbg !461
  %8 = load i32, i32* %flags1, align 8, !dbg !461
  %and2 = and i32 %8, 0, !dbg !461
  %cmp3 = icmp eq i32 %and2, 0, !dbg !461
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !461

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !464

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.1, i32 0, i32 0), i32 100, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.uv_timer_stop, i32 0, i32 0)) #4, !dbg !466
  unreachable, !dbg !466
                                                  ; No predecessors!
  br label %cond.end, !dbg !468

cond.end:                                         ; preds = %9, %cond.true
  %10 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !470
  %flags4 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %10, i32 0, i32 7, !dbg !470
  %11 = load i32, i32* %flags4, align 8, !dbg !470
  %and5 = and i32 %11, 16384, !dbg !470
  %cmp6 = icmp eq i32 %and5, 0, !dbg !470
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !470

if.then7:                                         ; preds = %cond.end
  br label %do.end18, !dbg !473

if.end8:                                          ; preds = %cond.end
  %12 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !475
  %flags9 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %12, i32 0, i32 7, !dbg !475
  %13 = load i32, i32* %flags9, align 8, !dbg !475
  %and10 = and i32 %13, -16385, !dbg !475
  store i32 %and10, i32* %flags9, align 8, !dbg !475
  %14 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !475
  %flags11 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %14, i32 0, i32 7, !dbg !475
  %15 = load i32, i32* %flags11, align 8, !dbg !475
  %and12 = and i32 %15, 8192, !dbg !475
  %cmp13 = icmp ne i32 %and12, 0, !dbg !475
  br i1 %cmp13, label %if.then14, label %if.end17, !dbg !475

if.then14:                                        ; preds = %if.end8
  br label %do.body15, !dbg !477

do.body15:                                        ; preds = %if.then14
  %16 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !480
  %loop16 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %16, i32 0, i32 1, !dbg !480
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop16, align 8, !dbg !480
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 1, !dbg !480
  %18 = load i32, i32* %active_handles, align 8, !dbg !480
  %dec = add i32 %18, -1, !dbg !480
  store i32 %dec, i32* %active_handles, align 8, !dbg !480
  br label %do.end, !dbg !480

do.end:                                           ; preds = %do.body15
  br label %if.end17, !dbg !483

if.end17:                                         ; preds = %do.end, %if.end8
  br label %do.end18, !dbg !485

do.end18:                                         ; preds = %if.end17, %if.then7
  store i32 0, i32* %retval, align 4, !dbg !487
  br label %return, !dbg !487

return:                                           ; preds = %do.end18, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !488
  ret i32 %19, !dbg !488
}

; Function Attrs: nounwind uwtable
define internal void @heap_insert(%struct.heap* %heap, %struct.heap_node* %newnode, i32 (%struct.heap_node*, %struct.heap_node*)* %less_than) #0 !dbg !316 {
entry:
  %heap.addr = alloca %struct.heap*, align 8
  %newnode.addr = alloca %struct.heap_node*, align 8
  %less_than.addr = alloca i32 (%struct.heap_node*, %struct.heap_node*)*, align 8
  %parent = alloca %struct.heap_node**, align 8
  %child = alloca %struct.heap_node**, align 8
  %path = alloca i32, align 4
  %n = alloca i32, align 4
  %k = alloca i32, align 4
  store %struct.heap* %heap, %struct.heap** %heap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap** %heap.addr, metadata !489, metadata !337), !dbg !490
  store %struct.heap_node* %newnode, %struct.heap_node** %newnode.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap_node** %newnode.addr, metadata !491, metadata !337), !dbg !490
  store i32 (%struct.heap_node*, %struct.heap_node*)* %less_than, i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, metadata !492, metadata !337), !dbg !490
  call void @llvm.dbg.declare(metadata %struct.heap_node*** %parent, metadata !493, metadata !337), !dbg !495
  call void @llvm.dbg.declare(metadata %struct.heap_node*** %child, metadata !496, metadata !337), !dbg !497
  call void @llvm.dbg.declare(metadata i32* %path, metadata !498, metadata !337), !dbg !499
  call void @llvm.dbg.declare(metadata i32* %n, metadata !500, metadata !337), !dbg !501
  call void @llvm.dbg.declare(metadata i32* %k, metadata !502, metadata !337), !dbg !503
  %0 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !504
  %left = getelementptr inbounds %struct.heap_node, %struct.heap_node* %0, i32 0, i32 0, !dbg !505
  store %struct.heap_node* null, %struct.heap_node** %left, align 8, !dbg !506
  %1 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !507
  %right = getelementptr inbounds %struct.heap_node, %struct.heap_node* %1, i32 0, i32 1, !dbg !508
  store %struct.heap_node* null, %struct.heap_node** %right, align 8, !dbg !509
  %2 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !510
  %parent1 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %2, i32 0, i32 2, !dbg !511
  store %struct.heap_node* null, %struct.heap_node** %parent1, align 8, !dbg !512
  store i32 0, i32* %path, align 4, !dbg !513
  store i32 0, i32* %k, align 4, !dbg !514
  %3 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !516
  %nelts = getelementptr inbounds %struct.heap, %struct.heap* %3, i32 0, i32 1, !dbg !517
  %4 = load i32, i32* %nelts, align 8, !dbg !517
  %add = add i32 1, %4, !dbg !518
  store i32 %add, i32* %n, align 4, !dbg !519
  br label %for.cond, !dbg !520

for.cond:                                         ; preds = %for.inc, %entry
  %5 = load i32, i32* %n, align 4, !dbg !521
  %cmp = icmp uge i32 %5, 2, !dbg !524
  br i1 %cmp, label %for.body, label %for.end, !dbg !525

for.body:                                         ; preds = %for.cond
  %6 = load i32, i32* %path, align 4, !dbg !526
  %shl = shl i32 %6, 1, !dbg !527
  %7 = load i32, i32* %n, align 4, !dbg !528
  %and = and i32 %7, 1, !dbg !529
  %or = or i32 %shl, %and, !dbg !530
  store i32 %or, i32* %path, align 4, !dbg !531
  br label %for.inc, !dbg !532

for.inc:                                          ; preds = %for.body
  %8 = load i32, i32* %k, align 4, !dbg !533
  %add2 = add i32 %8, 1, !dbg !533
  store i32 %add2, i32* %k, align 4, !dbg !533
  %9 = load i32, i32* %n, align 4, !dbg !535
  %div = udiv i32 %9, 2, !dbg !535
  store i32 %div, i32* %n, align 4, !dbg !535
  br label %for.cond, !dbg !536

for.end:                                          ; preds = %for.cond
  %10 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !537
  %min = getelementptr inbounds %struct.heap, %struct.heap* %10, i32 0, i32 0, !dbg !538
  store %struct.heap_node** %min, %struct.heap_node*** %child, align 8, !dbg !539
  store %struct.heap_node** %min, %struct.heap_node*** %parent, align 8, !dbg !540
  br label %while.cond, !dbg !541

while.cond:                                       ; preds = %if.end, %for.end
  %11 = load i32, i32* %k, align 4, !dbg !542
  %cmp3 = icmp ugt i32 %11, 0, !dbg !544
  br i1 %cmp3, label %while.body, label %while.end, !dbg !545

while.body:                                       ; preds = %while.cond
  %12 = load %struct.heap_node**, %struct.heap_node*** %child, align 8, !dbg !546
  store %struct.heap_node** %12, %struct.heap_node*** %parent, align 8, !dbg !548
  %13 = load i32, i32* %path, align 4, !dbg !549
  %and4 = and i32 %13, 1, !dbg !551
  %tobool = icmp ne i32 %and4, 0, !dbg !551
  br i1 %tobool, label %if.then, label %if.else, !dbg !552

if.then:                                          ; preds = %while.body
  %14 = load %struct.heap_node**, %struct.heap_node*** %child, align 8, !dbg !553
  %15 = load %struct.heap_node*, %struct.heap_node** %14, align 8, !dbg !554
  %right5 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %15, i32 0, i32 1, !dbg !555
  store %struct.heap_node** %right5, %struct.heap_node*** %child, align 8, !dbg !556
  br label %if.end, !dbg !557

if.else:                                          ; preds = %while.body
  %16 = load %struct.heap_node**, %struct.heap_node*** %child, align 8, !dbg !558
  %17 = load %struct.heap_node*, %struct.heap_node** %16, align 8, !dbg !559
  %left6 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %17, i32 0, i32 0, !dbg !560
  store %struct.heap_node** %left6, %struct.heap_node*** %child, align 8, !dbg !561
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %18 = load i32, i32* %path, align 4, !dbg !562
  %shr = lshr i32 %18, 1, !dbg !562
  store i32 %shr, i32* %path, align 4, !dbg !562
  %19 = load i32, i32* %k, align 4, !dbg !563
  %sub = sub i32 %19, 1, !dbg !563
  store i32 %sub, i32* %k, align 4, !dbg !563
  br label %while.cond, !dbg !564

while.end:                                        ; preds = %while.cond
  %20 = load %struct.heap_node**, %struct.heap_node*** %parent, align 8, !dbg !566
  %21 = load %struct.heap_node*, %struct.heap_node** %20, align 8, !dbg !567
  %22 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !568
  %parent7 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %22, i32 0, i32 2, !dbg !569
  store %struct.heap_node* %21, %struct.heap_node** %parent7, align 8, !dbg !570
  %23 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !571
  %24 = load %struct.heap_node**, %struct.heap_node*** %child, align 8, !dbg !572
  store %struct.heap_node* %23, %struct.heap_node** %24, align 8, !dbg !573
  %25 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !574
  %nelts8 = getelementptr inbounds %struct.heap, %struct.heap* %25, i32 0, i32 1, !dbg !575
  %26 = load i32, i32* %nelts8, align 8, !dbg !576
  %add9 = add i32 %26, 1, !dbg !576
  store i32 %add9, i32* %nelts8, align 8, !dbg !576
  br label %while.cond10, !dbg !577

while.cond10:                                     ; preds = %while.body15, %while.end
  %27 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !578
  %parent11 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %27, i32 0, i32 2, !dbg !579
  %28 = load %struct.heap_node*, %struct.heap_node** %parent11, align 8, !dbg !579
  %cmp12 = icmp ne %struct.heap_node* %28, null, !dbg !580
  br i1 %cmp12, label %land.rhs, label %land.end, !dbg !581

land.rhs:                                         ; preds = %while.cond10
  %29 = load i32 (%struct.heap_node*, %struct.heap_node*)*, i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, align 8, !dbg !582
  %30 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !583
  %31 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !584
  %parent13 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %31, i32 0, i32 2, !dbg !585
  %32 = load %struct.heap_node*, %struct.heap_node** %parent13, align 8, !dbg !585
  %call = call i32 %29(%struct.heap_node* %30, %struct.heap_node* %32), !dbg !582
  %tobool14 = icmp ne i32 %call, 0, !dbg !586
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond10
  %33 = phi i1 [ false, %while.cond10 ], [ %tobool14, %land.rhs ]
  br i1 %33, label %while.body15, label %while.end17, !dbg !587

while.body15:                                     ; preds = %land.end
  %34 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !589
  %35 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !590
  %parent16 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %35, i32 0, i32 2, !dbg !591
  %36 = load %struct.heap_node*, %struct.heap_node** %parent16, align 8, !dbg !591
  %37 = load %struct.heap_node*, %struct.heap_node** %newnode.addr, align 8, !dbg !592
  call void @heap_node_swap(%struct.heap* %34, %struct.heap_node* %36, %struct.heap_node* %37), !dbg !593
  br label %while.cond10, !dbg !594

while.end17:                                      ; preds = %land.end
  ret void, !dbg !596
}

; Function Attrs: nounwind uwtable
define internal i32 @timer_less_than(%struct.heap_node* %ha, %struct.heap_node* %hb) #0 !dbg !328 {
entry:
  %retval = alloca i32, align 4
  %ha.addr = alloca %struct.heap_node*, align 8
  %hb.addr = alloca %struct.heap_node*, align 8
  %a = alloca %struct.uv_timer_s*, align 8
  %b = alloca %struct.uv_timer_s*, align 8
  store %struct.heap_node* %ha, %struct.heap_node** %ha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap_node** %ha.addr, metadata !597, metadata !337), !dbg !598
  store %struct.heap_node* %hb, %struct.heap_node** %hb.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap_node** %hb.addr, metadata !599, metadata !337), !dbg !600
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %a, metadata !601, metadata !337), !dbg !602
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %b, metadata !603, metadata !337), !dbg !604
  %0 = load %struct.heap_node*, %struct.heap_node** %ha.addr, align 8, !dbg !605
  %1 = bitcast %struct.heap_node* %0 to i8*, !dbg !605
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -104, !dbg !605
  %2 = bitcast i8* %add.ptr to %struct.uv_timer_s*, !dbg !605
  store %struct.uv_timer_s* %2, %struct.uv_timer_s** %a, align 8, !dbg !606
  %3 = load %struct.heap_node*, %struct.heap_node** %hb.addr, align 8, !dbg !607
  %4 = bitcast %struct.heap_node* %3 to i8*, !dbg !607
  %add.ptr1 = getelementptr inbounds i8, i8* %4, i64 -104, !dbg !607
  %5 = bitcast i8* %add.ptr1 to %struct.uv_timer_s*, !dbg !607
  store %struct.uv_timer_s* %5, %struct.uv_timer_s** %b, align 8, !dbg !608
  %6 = load %struct.uv_timer_s*, %struct.uv_timer_s** %a, align 8, !dbg !609
  %timeout = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %6, i32 0, i32 10, !dbg !611
  %7 = load i64, i64* %timeout, align 8, !dbg !611
  %8 = load %struct.uv_timer_s*, %struct.uv_timer_s** %b, align 8, !dbg !612
  %timeout2 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %8, i32 0, i32 10, !dbg !613
  %9 = load i64, i64* %timeout2, align 8, !dbg !613
  %cmp = icmp ult i64 %7, %9, !dbg !614
  br i1 %cmp, label %if.then, label %if.end, !dbg !615

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !616
  br label %return, !dbg !616

if.end:                                           ; preds = %entry
  %10 = load %struct.uv_timer_s*, %struct.uv_timer_s** %b, align 8, !dbg !617
  %timeout3 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %10, i32 0, i32 10, !dbg !619
  %11 = load i64, i64* %timeout3, align 8, !dbg !619
  %12 = load %struct.uv_timer_s*, %struct.uv_timer_s** %a, align 8, !dbg !620
  %timeout4 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %12, i32 0, i32 10, !dbg !621
  %13 = load i64, i64* %timeout4, align 8, !dbg !621
  %cmp5 = icmp ult i64 %11, %13, !dbg !622
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !623

if.then6:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !624
  br label %return, !dbg !624

if.end7:                                          ; preds = %if.end
  %14 = load %struct.uv_timer_s*, %struct.uv_timer_s** %a, align 8, !dbg !625
  %start_id = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %14, i32 0, i32 12, !dbg !627
  %15 = load i64, i64* %start_id, align 8, !dbg !627
  %16 = load %struct.uv_timer_s*, %struct.uv_timer_s** %b, align 8, !dbg !628
  %start_id8 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %16, i32 0, i32 12, !dbg !629
  %17 = load i64, i64* %start_id8, align 8, !dbg !629
  %cmp9 = icmp ult i64 %15, %17, !dbg !630
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !631

if.then10:                                        ; preds = %if.end7
  store i32 1, i32* %retval, align 4, !dbg !632
  br label %return, !dbg !632

if.end11:                                         ; preds = %if.end7
  %18 = load %struct.uv_timer_s*, %struct.uv_timer_s** %b, align 8, !dbg !633
  %start_id12 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %18, i32 0, i32 12, !dbg !635
  %19 = load i64, i64* %start_id12, align 8, !dbg !635
  %20 = load %struct.uv_timer_s*, %struct.uv_timer_s** %a, align 8, !dbg !636
  %start_id13 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %20, i32 0, i32 12, !dbg !637
  %21 = load i64, i64* %start_id13, align 8, !dbg !637
  %cmp14 = icmp ult i64 %19, %21, !dbg !638
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !639

if.then15:                                        ; preds = %if.end11
  store i32 0, i32* %retval, align 4, !dbg !640
  br label %return, !dbg !640

if.end16:                                         ; preds = %if.end11
  store i32 0, i32* %retval, align 4, !dbg !641
  br label %return, !dbg !641

return:                                           ; preds = %if.end16, %if.then15, %if.then10, %if.then6, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !642
  ret i32 %22, !dbg !642
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

; Function Attrs: nounwind uwtable
define internal void @heap_remove(%struct.heap* %heap, %struct.heap_node* %node, i32 (%struct.heap_node*, %struct.heap_node*)* %less_than) #0 !dbg !329 {
entry:
  %heap.addr = alloca %struct.heap*, align 8
  %node.addr = alloca %struct.heap_node*, align 8
  %less_than.addr = alloca i32 (%struct.heap_node*, %struct.heap_node*)*, align 8
  %smallest = alloca %struct.heap_node*, align 8
  %max = alloca %struct.heap_node**, align 8
  %child = alloca %struct.heap_node*, align 8
  %path = alloca i32, align 4
  %k = alloca i32, align 4
  %n = alloca i32, align 4
  store %struct.heap* %heap, %struct.heap** %heap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap** %heap.addr, metadata !643, metadata !337), !dbg !644
  store %struct.heap_node* %node, %struct.heap_node** %node.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap_node** %node.addr, metadata !645, metadata !337), !dbg !644
  store i32 (%struct.heap_node*, %struct.heap_node*)* %less_than, i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, metadata !646, metadata !337), !dbg !644
  call void @llvm.dbg.declare(metadata %struct.heap_node** %smallest, metadata !647, metadata !337), !dbg !648
  call void @llvm.dbg.declare(metadata %struct.heap_node*** %max, metadata !649, metadata !337), !dbg !650
  call void @llvm.dbg.declare(metadata %struct.heap_node** %child, metadata !651, metadata !337), !dbg !652
  call void @llvm.dbg.declare(metadata i32* %path, metadata !653, metadata !337), !dbg !654
  call void @llvm.dbg.declare(metadata i32* %k, metadata !655, metadata !337), !dbg !656
  call void @llvm.dbg.declare(metadata i32* %n, metadata !657, metadata !337), !dbg !658
  %0 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !659
  %nelts = getelementptr inbounds %struct.heap, %struct.heap* %0, i32 0, i32 1, !dbg !661
  %1 = load i32, i32* %nelts, align 8, !dbg !661
  %cmp = icmp eq i32 %1, 0, !dbg !662
  br i1 %cmp, label %if.then, label %if.end, !dbg !663

if.then:                                          ; preds = %entry
  br label %while.end79, !dbg !664

if.end:                                           ; preds = %entry
  store i32 0, i32* %path, align 4, !dbg !665
  store i32 0, i32* %k, align 4, !dbg !666
  %2 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !668
  %nelts1 = getelementptr inbounds %struct.heap, %struct.heap* %2, i32 0, i32 1, !dbg !669
  %3 = load i32, i32* %nelts1, align 8, !dbg !669
  store i32 %3, i32* %n, align 4, !dbg !670
  br label %for.cond, !dbg !671

for.cond:                                         ; preds = %for.inc, %if.end
  %4 = load i32, i32* %n, align 4, !dbg !672
  %cmp2 = icmp uge i32 %4, 2, !dbg !675
  br i1 %cmp2, label %for.body, label %for.end, !dbg !676

for.body:                                         ; preds = %for.cond
  %5 = load i32, i32* %path, align 4, !dbg !677
  %shl = shl i32 %5, 1, !dbg !678
  %6 = load i32, i32* %n, align 4, !dbg !679
  %and = and i32 %6, 1, !dbg !680
  %or = or i32 %shl, %and, !dbg !681
  store i32 %or, i32* %path, align 4, !dbg !682
  br label %for.inc, !dbg !683

for.inc:                                          ; preds = %for.body
  %7 = load i32, i32* %k, align 4, !dbg !684
  %add = add i32 %7, 1, !dbg !684
  store i32 %add, i32* %k, align 4, !dbg !684
  %8 = load i32, i32* %n, align 4, !dbg !686
  %div = udiv i32 %8, 2, !dbg !686
  store i32 %div, i32* %n, align 4, !dbg !686
  br label %for.cond, !dbg !687

for.end:                                          ; preds = %for.cond
  %9 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !688
  %min = getelementptr inbounds %struct.heap, %struct.heap* %9, i32 0, i32 0, !dbg !689
  store %struct.heap_node** %min, %struct.heap_node*** %max, align 8, !dbg !690
  br label %while.cond, !dbg !691

while.cond:                                       ; preds = %if.end6, %for.end
  %10 = load i32, i32* %k, align 4, !dbg !692
  %cmp3 = icmp ugt i32 %10, 0, !dbg !694
  br i1 %cmp3, label %while.body, label %while.end, !dbg !695

while.body:                                       ; preds = %while.cond
  %11 = load i32, i32* %path, align 4, !dbg !696
  %and4 = and i32 %11, 1, !dbg !699
  %tobool = icmp ne i32 %and4, 0, !dbg !699
  br i1 %tobool, label %if.then5, label %if.else, !dbg !700

if.then5:                                         ; preds = %while.body
  %12 = load %struct.heap_node**, %struct.heap_node*** %max, align 8, !dbg !701
  %13 = load %struct.heap_node*, %struct.heap_node** %12, align 8, !dbg !702
  %right = getelementptr inbounds %struct.heap_node, %struct.heap_node* %13, i32 0, i32 1, !dbg !703
  store %struct.heap_node** %right, %struct.heap_node*** %max, align 8, !dbg !704
  br label %if.end6, !dbg !705

if.else:                                          ; preds = %while.body
  %14 = load %struct.heap_node**, %struct.heap_node*** %max, align 8, !dbg !706
  %15 = load %struct.heap_node*, %struct.heap_node** %14, align 8, !dbg !707
  %left = getelementptr inbounds %struct.heap_node, %struct.heap_node* %15, i32 0, i32 0, !dbg !708
  store %struct.heap_node** %left, %struct.heap_node*** %max, align 8, !dbg !709
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then5
  %16 = load i32, i32* %path, align 4, !dbg !710
  %shr = lshr i32 %16, 1, !dbg !710
  store i32 %shr, i32* %path, align 4, !dbg !710
  %17 = load i32, i32* %k, align 4, !dbg !711
  %sub = sub i32 %17, 1, !dbg !711
  store i32 %sub, i32* %k, align 4, !dbg !711
  br label %while.cond, !dbg !712

while.end:                                        ; preds = %while.cond
  %18 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !714
  %nelts7 = getelementptr inbounds %struct.heap, %struct.heap* %18, i32 0, i32 1, !dbg !715
  %19 = load i32, i32* %nelts7, align 8, !dbg !716
  %sub8 = sub i32 %19, 1, !dbg !716
  store i32 %sub8, i32* %nelts7, align 8, !dbg !716
  %20 = load %struct.heap_node**, %struct.heap_node*** %max, align 8, !dbg !717
  %21 = load %struct.heap_node*, %struct.heap_node** %20, align 8, !dbg !718
  store %struct.heap_node* %21, %struct.heap_node** %child, align 8, !dbg !719
  %22 = load %struct.heap_node**, %struct.heap_node*** %max, align 8, !dbg !720
  store %struct.heap_node* null, %struct.heap_node** %22, align 8, !dbg !721
  %23 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !722
  %24 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !724
  %cmp9 = icmp eq %struct.heap_node* %23, %24, !dbg !725
  br i1 %cmp9, label %if.then10, label %if.end16, !dbg !726

if.then10:                                        ; preds = %while.end
  %25 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !727
  %26 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !730
  %min11 = getelementptr inbounds %struct.heap, %struct.heap* %26, i32 0, i32 0, !dbg !731
  %27 = load %struct.heap_node*, %struct.heap_node** %min11, align 8, !dbg !731
  %cmp12 = icmp eq %struct.heap_node* %25, %27, !dbg !732
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !733

if.then13:                                        ; preds = %if.then10
  %28 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !734
  %min14 = getelementptr inbounds %struct.heap, %struct.heap* %28, i32 0, i32 0, !dbg !736
  store %struct.heap_node* null, %struct.heap_node** %min14, align 8, !dbg !737
  br label %if.end15, !dbg !738

if.end15:                                         ; preds = %if.then13, %if.then10
  br label %while.end79, !dbg !739

if.end16:                                         ; preds = %while.end
  %29 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !740
  %left17 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %29, i32 0, i32 0, !dbg !741
  %30 = load %struct.heap_node*, %struct.heap_node** %left17, align 8, !dbg !741
  %31 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !742
  %left18 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %31, i32 0, i32 0, !dbg !743
  store %struct.heap_node* %30, %struct.heap_node** %left18, align 8, !dbg !744
  %32 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !745
  %right19 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %32, i32 0, i32 1, !dbg !746
  %33 = load %struct.heap_node*, %struct.heap_node** %right19, align 8, !dbg !746
  %34 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !747
  %right20 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %34, i32 0, i32 1, !dbg !748
  store %struct.heap_node* %33, %struct.heap_node** %right20, align 8, !dbg !749
  %35 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !750
  %parent = getelementptr inbounds %struct.heap_node, %struct.heap_node* %35, i32 0, i32 2, !dbg !751
  %36 = load %struct.heap_node*, %struct.heap_node** %parent, align 8, !dbg !751
  %37 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !752
  %parent21 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %37, i32 0, i32 2, !dbg !753
  store %struct.heap_node* %36, %struct.heap_node** %parent21, align 8, !dbg !754
  %38 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !755
  %left22 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %38, i32 0, i32 0, !dbg !757
  %39 = load %struct.heap_node*, %struct.heap_node** %left22, align 8, !dbg !757
  %cmp23 = icmp ne %struct.heap_node* %39, null, !dbg !758
  br i1 %cmp23, label %if.then24, label %if.end27, !dbg !759

if.then24:                                        ; preds = %if.end16
  %40 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !760
  %41 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !762
  %left25 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %41, i32 0, i32 0, !dbg !763
  %42 = load %struct.heap_node*, %struct.heap_node** %left25, align 8, !dbg !763
  %parent26 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %42, i32 0, i32 2, !dbg !764
  store %struct.heap_node* %40, %struct.heap_node** %parent26, align 8, !dbg !765
  br label %if.end27, !dbg !766

if.end27:                                         ; preds = %if.then24, %if.end16
  %43 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !767
  %right28 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %43, i32 0, i32 1, !dbg !769
  %44 = load %struct.heap_node*, %struct.heap_node** %right28, align 8, !dbg !769
  %cmp29 = icmp ne %struct.heap_node* %44, null, !dbg !770
  br i1 %cmp29, label %if.then30, label %if.end33, !dbg !771

if.then30:                                        ; preds = %if.end27
  %45 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !772
  %46 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !774
  %right31 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %46, i32 0, i32 1, !dbg !775
  %47 = load %struct.heap_node*, %struct.heap_node** %right31, align 8, !dbg !775
  %parent32 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %47, i32 0, i32 2, !dbg !776
  store %struct.heap_node* %45, %struct.heap_node** %parent32, align 8, !dbg !777
  br label %if.end33, !dbg !778

if.end33:                                         ; preds = %if.then30, %if.end27
  %48 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !779
  %parent34 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %48, i32 0, i32 2, !dbg !781
  %49 = load %struct.heap_node*, %struct.heap_node** %parent34, align 8, !dbg !781
  %cmp35 = icmp eq %struct.heap_node* %49, null, !dbg !782
  br i1 %cmp35, label %if.then36, label %if.else38, !dbg !783

if.then36:                                        ; preds = %if.end33
  %50 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !784
  %51 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !786
  %min37 = getelementptr inbounds %struct.heap, %struct.heap* %51, i32 0, i32 0, !dbg !787
  store %struct.heap_node* %50, %struct.heap_node** %min37, align 8, !dbg !788
  br label %if.end49, !dbg !789

if.else38:                                        ; preds = %if.end33
  %52 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !790
  %parent39 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %52, i32 0, i32 2, !dbg !793
  %53 = load %struct.heap_node*, %struct.heap_node** %parent39, align 8, !dbg !793
  %left40 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %53, i32 0, i32 0, !dbg !794
  %54 = load %struct.heap_node*, %struct.heap_node** %left40, align 8, !dbg !794
  %55 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !795
  %cmp41 = icmp eq %struct.heap_node* %54, %55, !dbg !796
  br i1 %cmp41, label %if.then42, label %if.else45, !dbg !790

if.then42:                                        ; preds = %if.else38
  %56 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !797
  %57 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !799
  %parent43 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %57, i32 0, i32 2, !dbg !800
  %58 = load %struct.heap_node*, %struct.heap_node** %parent43, align 8, !dbg !800
  %left44 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %58, i32 0, i32 0, !dbg !801
  store %struct.heap_node* %56, %struct.heap_node** %left44, align 8, !dbg !802
  br label %if.end48, !dbg !803

if.else45:                                        ; preds = %if.else38
  %59 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !804
  %60 = load %struct.heap_node*, %struct.heap_node** %node.addr, align 8, !dbg !806
  %parent46 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %60, i32 0, i32 2, !dbg !807
  %61 = load %struct.heap_node*, %struct.heap_node** %parent46, align 8, !dbg !807
  %right47 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %61, i32 0, i32 1, !dbg !808
  store %struct.heap_node* %59, %struct.heap_node** %right47, align 8, !dbg !809
  br label %if.end48

if.end48:                                         ; preds = %if.else45, %if.then42
  br label %if.end49

if.end49:                                         ; preds = %if.end48, %if.then36
  br label %for.cond50, !dbg !810

for.cond50:                                       ; preds = %if.end69, %if.end49
  %62 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !811
  store %struct.heap_node* %62, %struct.heap_node** %smallest, align 8, !dbg !815
  %63 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !816
  %left51 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %63, i32 0, i32 0, !dbg !818
  %64 = load %struct.heap_node*, %struct.heap_node** %left51, align 8, !dbg !818
  %cmp52 = icmp ne %struct.heap_node* %64, null, !dbg !819
  br i1 %cmp52, label %land.lhs.true, label %if.end57, !dbg !820

land.lhs.true:                                    ; preds = %for.cond50
  %65 = load i32 (%struct.heap_node*, %struct.heap_node*)*, i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, align 8, !dbg !821
  %66 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !823
  %left53 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %66, i32 0, i32 0, !dbg !824
  %67 = load %struct.heap_node*, %struct.heap_node** %left53, align 8, !dbg !824
  %68 = load %struct.heap_node*, %struct.heap_node** %smallest, align 8, !dbg !825
  %call = call i32 %65(%struct.heap_node* %67, %struct.heap_node* %68), !dbg !821
  %tobool54 = icmp ne i32 %call, 0, !dbg !821
  br i1 %tobool54, label %if.then55, label %if.end57, !dbg !826

if.then55:                                        ; preds = %land.lhs.true
  %69 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !827
  %left56 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %69, i32 0, i32 0, !dbg !828
  %70 = load %struct.heap_node*, %struct.heap_node** %left56, align 8, !dbg !828
  store %struct.heap_node* %70, %struct.heap_node** %smallest, align 8, !dbg !829
  br label %if.end57, !dbg !830

if.end57:                                         ; preds = %if.then55, %land.lhs.true, %for.cond50
  %71 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !831
  %right58 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %71, i32 0, i32 1, !dbg !833
  %72 = load %struct.heap_node*, %struct.heap_node** %right58, align 8, !dbg !833
  %cmp59 = icmp ne %struct.heap_node* %72, null, !dbg !834
  br i1 %cmp59, label %land.lhs.true60, label %if.end66, !dbg !835

land.lhs.true60:                                  ; preds = %if.end57
  %73 = load i32 (%struct.heap_node*, %struct.heap_node*)*, i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, align 8, !dbg !836
  %74 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !838
  %right61 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %74, i32 0, i32 1, !dbg !839
  %75 = load %struct.heap_node*, %struct.heap_node** %right61, align 8, !dbg !839
  %76 = load %struct.heap_node*, %struct.heap_node** %smallest, align 8, !dbg !840
  %call62 = call i32 %73(%struct.heap_node* %75, %struct.heap_node* %76), !dbg !836
  %tobool63 = icmp ne i32 %call62, 0, !dbg !836
  br i1 %tobool63, label %if.then64, label %if.end66, !dbg !841

if.then64:                                        ; preds = %land.lhs.true60
  %77 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !842
  %right65 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %77, i32 0, i32 1, !dbg !843
  %78 = load %struct.heap_node*, %struct.heap_node** %right65, align 8, !dbg !843
  store %struct.heap_node* %78, %struct.heap_node** %smallest, align 8, !dbg !844
  br label %if.end66, !dbg !845

if.end66:                                         ; preds = %if.then64, %land.lhs.true60, %if.end57
  %79 = load %struct.heap_node*, %struct.heap_node** %smallest, align 8, !dbg !846
  %80 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !848
  %cmp67 = icmp eq %struct.heap_node* %79, %80, !dbg !849
  br i1 %cmp67, label %if.then68, label %if.end69, !dbg !850

if.then68:                                        ; preds = %if.end66
  br label %for.end70, !dbg !851

if.end69:                                         ; preds = %if.end66
  %81 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !852
  %82 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !853
  %83 = load %struct.heap_node*, %struct.heap_node** %smallest, align 8, !dbg !854
  call void @heap_node_swap(%struct.heap* %81, %struct.heap_node* %82, %struct.heap_node* %83), !dbg !855
  br label %for.cond50, !dbg !856

for.end70:                                        ; preds = %if.then68
  br label %while.cond71, !dbg !858

while.cond71:                                     ; preds = %while.body77, %for.end70
  %84 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !859
  %parent72 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %84, i32 0, i32 2, !dbg !860
  %85 = load %struct.heap_node*, %struct.heap_node** %parent72, align 8, !dbg !860
  %cmp73 = icmp ne %struct.heap_node* %85, null, !dbg !861
  br i1 %cmp73, label %land.rhs, label %land.end, !dbg !862

land.rhs:                                         ; preds = %while.cond71
  %86 = load i32 (%struct.heap_node*, %struct.heap_node*)*, i32 (%struct.heap_node*, %struct.heap_node*)** %less_than.addr, align 8, !dbg !863
  %87 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !864
  %88 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !865
  %parent74 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %88, i32 0, i32 2, !dbg !866
  %89 = load %struct.heap_node*, %struct.heap_node** %parent74, align 8, !dbg !866
  %call75 = call i32 %86(%struct.heap_node* %87, %struct.heap_node* %89), !dbg !863
  %tobool76 = icmp ne i32 %call75, 0, !dbg !867
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond71
  %90 = phi i1 [ false, %while.cond71 ], [ %tobool76, %land.rhs ]
  br i1 %90, label %while.body77, label %while.end79, !dbg !868

while.body77:                                     ; preds = %land.end
  %91 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !870
  %92 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !871
  %parent78 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %92, i32 0, i32 2, !dbg !872
  %93 = load %struct.heap_node*, %struct.heap_node** %parent78, align 8, !dbg !872
  %94 = load %struct.heap_node*, %struct.heap_node** %child, align 8, !dbg !873
  call void @heap_node_swap(%struct.heap* %91, %struct.heap_node* %93, %struct.heap_node* %94), !dbg !874
  br label %while.cond71, !dbg !875

while.end79:                                      ; preds = %if.then, %if.end15, %land.end
  ret void, !dbg !877
}

; Function Attrs: nounwind uwtable
define i32 @uv_timer_again(%struct.uv_timer_s* %handle) #0 !dbg !298 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !878, metadata !337), !dbg !879
  %0 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !880
  %timer_cb = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %0, i32 0, i32 8, !dbg !882
  %1 = load void (%struct.uv_timer_s*)*, void (%struct.uv_timer_s*)** %timer_cb, align 8, !dbg !882
  %cmp = icmp eq void (%struct.uv_timer_s*)* %1, null, !dbg !883
  br i1 %cmp, label %if.then, label %if.end, !dbg !884

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !885
  br label %return, !dbg !885

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !886
  %repeat = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %2, i32 0, i32 11, !dbg !888
  %3 = load i64, i64* %repeat, align 8, !dbg !888
  %tobool = icmp ne i64 %3, 0, !dbg !886
  br i1 %tobool, label %if.then1, label %if.end6, !dbg !889

if.then1:                                         ; preds = %if.end
  %4 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !890
  %call = call i32 @uv_timer_stop(%struct.uv_timer_s* %4), !dbg !892
  %5 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !893
  %6 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !894
  %timer_cb2 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %6, i32 0, i32 8, !dbg !895
  %7 = load void (%struct.uv_timer_s*)*, void (%struct.uv_timer_s*)** %timer_cb2, align 8, !dbg !895
  %8 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !896
  %repeat3 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %8, i32 0, i32 11, !dbg !897
  %9 = load i64, i64* %repeat3, align 8, !dbg !897
  %10 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !898
  %repeat4 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %10, i32 0, i32 11, !dbg !899
  %11 = load i64, i64* %repeat4, align 8, !dbg !899
  %call5 = call i32 @uv_timer_start(%struct.uv_timer_s* %5, void (%struct.uv_timer_s*)* %7, i64 %9, i64 %11), !dbg !900
  br label %if.end6, !dbg !901

if.end6:                                          ; preds = %if.then1, %if.end
  store i32 0, i32* %retval, align 4, !dbg !902
  br label %return, !dbg !902

return:                                           ; preds = %if.end6, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !903
  ret i32 %12, !dbg !903
}

; Function Attrs: nounwind uwtable
define void @uv_timer_set_repeat(%struct.uv_timer_s* %handle, i64 %repeat) #0 !dbg !299 {
entry:
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  %repeat.addr = alloca i64, align 8
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !904, metadata !337), !dbg !905
  store i64 %repeat, i64* %repeat.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %repeat.addr, metadata !906, metadata !337), !dbg !907
  %0 = load i64, i64* %repeat.addr, align 8, !dbg !908
  %1 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !909
  %repeat1 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %1, i32 0, i32 11, !dbg !910
  store i64 %0, i64* %repeat1, align 8, !dbg !911
  ret void, !dbg !912
}

; Function Attrs: nounwind uwtable
define i64 @uv_timer_get_repeat(%struct.uv_timer_s* %handle) #0 !dbg !302 {
entry:
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !913, metadata !337), !dbg !914
  %0 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !915
  %repeat = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %0, i32 0, i32 11, !dbg !916
  %1 = load i64, i64* %repeat, align 8, !dbg !916
  ret i64 %1, !dbg !917
}

; Function Attrs: nounwind uwtable
define i32 @uv__next_timeout(%struct.uv_loop_s* %loop) #0 !dbg !307 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %heap_node = alloca %struct.heap_node*, align 8
  %handle = alloca %struct.uv_timer_s*, align 8
  %diff = alloca i64, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !918, metadata !337), !dbg !919
  call void @llvm.dbg.declare(metadata %struct.heap_node** %heap_node, metadata !920, metadata !337), !dbg !921
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle, metadata !922, metadata !337), !dbg !923
  call void @llvm.dbg.declare(metadata i64* %diff, metadata !924, metadata !337), !dbg !925
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !926
  %timer_heap = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 25, !dbg !927
  %1 = bitcast %struct.anon.1* %timer_heap to %struct.heap*, !dbg !928
  %call = call %struct.heap_node* @heap_min(%struct.heap* %1), !dbg !929
  store %struct.heap_node* %call, %struct.heap_node** %heap_node, align 8, !dbg !930
  %2 = load %struct.heap_node*, %struct.heap_node** %heap_node, align 8, !dbg !931
  %cmp = icmp eq %struct.heap_node* %2, null, !dbg !933
  br i1 %cmp, label %if.then, label %if.end, !dbg !934

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !935
  br label %return, !dbg !935

if.end:                                           ; preds = %entry
  %3 = load %struct.heap_node*, %struct.heap_node** %heap_node, align 8, !dbg !936
  %4 = bitcast %struct.heap_node* %3 to i8*, !dbg !936
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 -104, !dbg !936
  %5 = bitcast i8* %add.ptr to %struct.uv_timer_s*, !dbg !936
  store %struct.uv_timer_s* %5, %struct.uv_timer_s** %handle, align 8, !dbg !937
  %6 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !938
  %timeout = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %6, i32 0, i32 10, !dbg !940
  %7 = load i64, i64* %timeout, align 8, !dbg !940
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !941
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 27, !dbg !942
  %9 = load i64, i64* %time, align 8, !dbg !942
  %cmp1 = icmp ule i64 %7, %9, !dbg !943
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !944

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !945
  br label %return, !dbg !945

if.end3:                                          ; preds = %if.end
  %10 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !946
  %timeout4 = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %10, i32 0, i32 10, !dbg !947
  %11 = load i64, i64* %timeout4, align 8, !dbg !947
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !948
  %time5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 27, !dbg !949
  %13 = load i64, i64* %time5, align 8, !dbg !949
  %sub = sub i64 %11, %13, !dbg !950
  store i64 %sub, i64* %diff, align 8, !dbg !951
  %14 = load i64, i64* %diff, align 8, !dbg !952
  %cmp6 = icmp ugt i64 %14, 2147483647, !dbg !954
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !955

if.then7:                                         ; preds = %if.end3
  store i64 2147483647, i64* %diff, align 8, !dbg !956
  br label %if.end8, !dbg !957

if.end8:                                          ; preds = %if.then7, %if.end3
  %15 = load i64, i64* %diff, align 8, !dbg !958
  %conv = trunc i64 %15 to i32, !dbg !958
  store i32 %conv, i32* %retval, align 4, !dbg !959
  br label %return, !dbg !959

return:                                           ; preds = %if.end8, %if.then2, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !960
  ret i32 %16, !dbg !960
}

; Function Attrs: nounwind uwtable
define internal %struct.heap_node* @heap_min(%struct.heap* %heap) #0 !dbg !330 {
entry:
  %heap.addr = alloca %struct.heap*, align 8
  store %struct.heap* %heap, %struct.heap** %heap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap** %heap.addr, metadata !961, metadata !337), !dbg !962
  %0 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !963
  %min = getelementptr inbounds %struct.heap, %struct.heap* %0, i32 0, i32 0, !dbg !964
  %1 = load %struct.heap_node*, %struct.heap_node** %min, align 8, !dbg !964
  ret %struct.heap_node* %1, !dbg !965
}

; Function Attrs: nounwind uwtable
define void @uv__run_timers(%struct.uv_loop_s* %loop) #0 !dbg !312 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %heap_node = alloca %struct.heap_node*, align 8
  %handle = alloca %struct.uv_timer_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !966, metadata !337), !dbg !967
  call void @llvm.dbg.declare(metadata %struct.heap_node** %heap_node, metadata !968, metadata !337), !dbg !969
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle, metadata !970, metadata !337), !dbg !971
  br label %for.cond, !dbg !972

for.cond:                                         ; preds = %if.end3, %entry
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !973
  %timer_heap = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 25, !dbg !977
  %1 = bitcast %struct.anon.1* %timer_heap to %struct.heap*, !dbg !978
  %call = call %struct.heap_node* @heap_min(%struct.heap* %1), !dbg !979
  store %struct.heap_node* %call, %struct.heap_node** %heap_node, align 8, !dbg !980
  %2 = load %struct.heap_node*, %struct.heap_node** %heap_node, align 8, !dbg !981
  %cmp = icmp eq %struct.heap_node* %2, null, !dbg !983
  br i1 %cmp, label %if.then, label %if.end, !dbg !984

if.then:                                          ; preds = %for.cond
  br label %for.end, !dbg !985

if.end:                                           ; preds = %for.cond
  %3 = load %struct.heap_node*, %struct.heap_node** %heap_node, align 8, !dbg !986
  %4 = bitcast %struct.heap_node* %3 to i8*, !dbg !986
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 -104, !dbg !986
  %5 = bitcast i8* %add.ptr to %struct.uv_timer_s*, !dbg !986
  store %struct.uv_timer_s* %5, %struct.uv_timer_s** %handle, align 8, !dbg !987
  %6 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !988
  %timeout = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %6, i32 0, i32 10, !dbg !990
  %7 = load i64, i64* %timeout, align 8, !dbg !990
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !991
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 27, !dbg !992
  %9 = load i64, i64* %time, align 8, !dbg !992
  %cmp1 = icmp ugt i64 %7, %9, !dbg !993
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !994

if.then2:                                         ; preds = %if.end
  br label %for.end, !dbg !995

if.end3:                                          ; preds = %if.end
  %10 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !996
  %call4 = call i32 @uv_timer_stop(%struct.uv_timer_s* %10), !dbg !997
  %11 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !998
  %call5 = call i32 @uv_timer_again(%struct.uv_timer_s* %11), !dbg !999
  %12 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !1000
  %timer_cb = getelementptr inbounds %struct.uv_timer_s, %struct.uv_timer_s* %12, i32 0, i32 8, !dbg !1001
  %13 = load void (%struct.uv_timer_s*)*, void (%struct.uv_timer_s*)** %timer_cb, align 8, !dbg !1001
  %14 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle, align 8, !dbg !1002
  call void %13(%struct.uv_timer_s* %14), !dbg !1000
  br label %for.cond, !dbg !1003

for.end:                                          ; preds = %if.then2, %if.then
  ret void, !dbg !1005
}

; Function Attrs: nounwind uwtable
define void @uv__timer_close(%struct.uv_timer_s* %handle) #0 !dbg !315 {
entry:
  %handle.addr = alloca %struct.uv_timer_s*, align 8
  store %struct.uv_timer_s* %handle, %struct.uv_timer_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_timer_s** %handle.addr, metadata !1006, metadata !337), !dbg !1007
  %0 = load %struct.uv_timer_s*, %struct.uv_timer_s** %handle.addr, align 8, !dbg !1008
  %call = call i32 @uv_timer_stop(%struct.uv_timer_s* %0), !dbg !1009
  ret void, !dbg !1010
}

; Function Attrs: nounwind uwtable
define internal void @heap_node_swap(%struct.heap* %heap, %struct.heap_node* %parent, %struct.heap_node* %child) #0 !dbg !325 {
entry:
  %heap.addr = alloca %struct.heap*, align 8
  %parent.addr = alloca %struct.heap_node*, align 8
  %child.addr = alloca %struct.heap_node*, align 8
  %sibling = alloca %struct.heap_node*, align 8
  %t = alloca %struct.heap_node, align 8
  store %struct.heap* %heap, %struct.heap** %heap.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap** %heap.addr, metadata !1011, metadata !337), !dbg !1012
  store %struct.heap_node* %parent, %struct.heap_node** %parent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap_node** %parent.addr, metadata !1013, metadata !337), !dbg !1014
  store %struct.heap_node* %child, %struct.heap_node** %child.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.heap_node** %child.addr, metadata !1015, metadata !337), !dbg !1016
  call void @llvm.dbg.declare(metadata %struct.heap_node** %sibling, metadata !1017, metadata !337), !dbg !1018
  call void @llvm.dbg.declare(metadata %struct.heap_node* %t, metadata !1019, metadata !337), !dbg !1020
  %0 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1021
  %1 = bitcast %struct.heap_node* %t to i8*, !dbg !1022
  %2 = bitcast %struct.heap_node* %0 to i8*, !dbg !1022
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %1, i8* %2, i64 24, i32 8, i1 false), !dbg !1022
  %3 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1023
  %4 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1024
  %5 = bitcast %struct.heap_node* %3 to i8*, !dbg !1025
  %6 = bitcast %struct.heap_node* %4 to i8*, !dbg !1025
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 24, i32 8, i1 false), !dbg !1025
  %7 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1026
  %8 = bitcast %struct.heap_node* %7 to i8*, !dbg !1027
  %9 = bitcast %struct.heap_node* %t to i8*, !dbg !1027
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* %9, i64 24, i32 8, i1 false), !dbg !1027
  %10 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1028
  %11 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1029
  %parent1 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %11, i32 0, i32 2, !dbg !1030
  store %struct.heap_node* %10, %struct.heap_node** %parent1, align 8, !dbg !1031
  %12 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1032
  %left = getelementptr inbounds %struct.heap_node, %struct.heap_node* %12, i32 0, i32 0, !dbg !1034
  %13 = load %struct.heap_node*, %struct.heap_node** %left, align 8, !dbg !1034
  %14 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1035
  %cmp = icmp eq %struct.heap_node* %13, %14, !dbg !1036
  br i1 %cmp, label %if.then, label %if.else, !dbg !1037

if.then:                                          ; preds = %entry
  %15 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1038
  %16 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1040
  %left2 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %16, i32 0, i32 0, !dbg !1041
  store %struct.heap_node* %15, %struct.heap_node** %left2, align 8, !dbg !1042
  %17 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1043
  %right = getelementptr inbounds %struct.heap_node, %struct.heap_node* %17, i32 0, i32 1, !dbg !1044
  %18 = load %struct.heap_node*, %struct.heap_node** %right, align 8, !dbg !1044
  store %struct.heap_node* %18, %struct.heap_node** %sibling, align 8, !dbg !1045
  br label %if.end, !dbg !1046

if.else:                                          ; preds = %entry
  %19 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1047
  %20 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1049
  %right3 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %20, i32 0, i32 1, !dbg !1050
  store %struct.heap_node* %19, %struct.heap_node** %right3, align 8, !dbg !1051
  %21 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1052
  %left4 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %21, i32 0, i32 0, !dbg !1053
  %22 = load %struct.heap_node*, %struct.heap_node** %left4, align 8, !dbg !1053
  store %struct.heap_node* %22, %struct.heap_node** %sibling, align 8, !dbg !1054
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %23 = load %struct.heap_node*, %struct.heap_node** %sibling, align 8, !dbg !1055
  %cmp5 = icmp ne %struct.heap_node* %23, null, !dbg !1057
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !1058

if.then6:                                         ; preds = %if.end
  %24 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1059
  %25 = load %struct.heap_node*, %struct.heap_node** %sibling, align 8, !dbg !1060
  %parent7 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %25, i32 0, i32 2, !dbg !1061
  store %struct.heap_node* %24, %struct.heap_node** %parent7, align 8, !dbg !1062
  br label %if.end8, !dbg !1060

if.end8:                                          ; preds = %if.then6, %if.end
  %26 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1063
  %left9 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %26, i32 0, i32 0, !dbg !1065
  %27 = load %struct.heap_node*, %struct.heap_node** %left9, align 8, !dbg !1065
  %cmp10 = icmp ne %struct.heap_node* %27, null, !dbg !1066
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !1067

if.then11:                                        ; preds = %if.end8
  %28 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1068
  %29 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1069
  %left12 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %29, i32 0, i32 0, !dbg !1070
  %30 = load %struct.heap_node*, %struct.heap_node** %left12, align 8, !dbg !1070
  %parent13 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %30, i32 0, i32 2, !dbg !1071
  store %struct.heap_node* %28, %struct.heap_node** %parent13, align 8, !dbg !1072
  br label %if.end14, !dbg !1069

if.end14:                                         ; preds = %if.then11, %if.end8
  %31 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1073
  %right15 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %31, i32 0, i32 1, !dbg !1075
  %32 = load %struct.heap_node*, %struct.heap_node** %right15, align 8, !dbg !1075
  %cmp16 = icmp ne %struct.heap_node* %32, null, !dbg !1076
  br i1 %cmp16, label %if.then17, label %if.end20, !dbg !1077

if.then17:                                        ; preds = %if.end14
  %33 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1078
  %34 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1079
  %right18 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %34, i32 0, i32 1, !dbg !1080
  %35 = load %struct.heap_node*, %struct.heap_node** %right18, align 8, !dbg !1080
  %parent19 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %35, i32 0, i32 2, !dbg !1081
  store %struct.heap_node* %33, %struct.heap_node** %parent19, align 8, !dbg !1082
  br label %if.end20, !dbg !1079

if.end20:                                         ; preds = %if.then17, %if.end14
  %36 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1083
  %parent21 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %36, i32 0, i32 2, !dbg !1085
  %37 = load %struct.heap_node*, %struct.heap_node** %parent21, align 8, !dbg !1085
  %cmp22 = icmp eq %struct.heap_node* %37, null, !dbg !1086
  br i1 %cmp22, label %if.then23, label %if.else24, !dbg !1087

if.then23:                                        ; preds = %if.end20
  %38 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1088
  %39 = load %struct.heap*, %struct.heap** %heap.addr, align 8, !dbg !1089
  %min = getelementptr inbounds %struct.heap, %struct.heap* %39, i32 0, i32 0, !dbg !1090
  store %struct.heap_node* %38, %struct.heap_node** %min, align 8, !dbg !1091
  br label %if.end35, !dbg !1089

if.else24:                                        ; preds = %if.end20
  %40 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1092
  %parent25 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %40, i32 0, i32 2, !dbg !1094
  %41 = load %struct.heap_node*, %struct.heap_node** %parent25, align 8, !dbg !1094
  %left26 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %41, i32 0, i32 0, !dbg !1095
  %42 = load %struct.heap_node*, %struct.heap_node** %left26, align 8, !dbg !1095
  %43 = load %struct.heap_node*, %struct.heap_node** %parent.addr, align 8, !dbg !1096
  %cmp27 = icmp eq %struct.heap_node* %42, %43, !dbg !1097
  br i1 %cmp27, label %if.then28, label %if.else31, !dbg !1098

if.then28:                                        ; preds = %if.else24
  %44 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1099
  %45 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1100
  %parent29 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %45, i32 0, i32 2, !dbg !1101
  %46 = load %struct.heap_node*, %struct.heap_node** %parent29, align 8, !dbg !1101
  %left30 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %46, i32 0, i32 0, !dbg !1102
  store %struct.heap_node* %44, %struct.heap_node** %left30, align 8, !dbg !1103
  br label %if.end34, !dbg !1100

if.else31:                                        ; preds = %if.else24
  %47 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1104
  %48 = load %struct.heap_node*, %struct.heap_node** %child.addr, align 8, !dbg !1105
  %parent32 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %48, i32 0, i32 2, !dbg !1106
  %49 = load %struct.heap_node*, %struct.heap_node** %parent32, align 8, !dbg !1106
  %right33 = getelementptr inbounds %struct.heap_node, %struct.heap_node* %49, i32 0, i32 1, !dbg !1107
  store %struct.heap_node* %47, %struct.heap_node** %right33, align 8, !dbg !1108
  br label %if.end34

if.end34:                                         ; preds = %if.else31, %if.then28
  br label %if.end35

if.end35:                                         ; preds = %if.end34, %if.then23
  ret void, !dbg !1109
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!333, !334}
!llvm.ident = !{!335}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !33, subprograms: !287)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/timer.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
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
!33 = !{!34, !240, !39, !187, !244, !249, !256, !258, !286}
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
!245 = !DICompositeType(tag: DW_TAG_structure_type, name: "heap", file: !246, line: 40, size: 128, align: 64, elements: !247)
!246 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/heap-inl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!247 = !{!248, !255}
!248 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !245, file: !246, line: 41, baseType: !249, size: 64, align: 64)
!249 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !250, size: 64, align: 64)
!250 = !DICompositeType(tag: DW_TAG_structure_type, name: "heap_node", file: !246, line: 27, size: 192, align: 64, elements: !251)
!251 = !{!252, !253, !254}
!252 = !DIDerivedType(tag: DW_TAG_member, name: "left", scope: !250, file: !246, line: 28, baseType: !249, size: 64, align: 64)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "right", scope: !250, file: !246, line: 29, baseType: !249, size: 64, align: 64, offset: 64)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "parent", scope: !250, file: !246, line: 30, baseType: !249, size: 64, align: 64, offset: 128)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !245, file: !246, line: 42, baseType: !47, size: 32, align: 32, offset: 64)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !245)
!258 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !259, size: 64, align: 64)
!259 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timer_t", file: !4, line: 212, baseType: !260)
!260 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_timer_s", file: !4, line: 783, size: 1216, align: 64, elements: !261)
!261 = !{!262, !263, !264, !265, !266, !267, !272, !273, !274, !279, !283, !284, !285}
!262 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !260, file: !4, line: 784, baseType: !39, size: 64, align: 64)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !260, file: !4, line: 784, baseType: !41, size: 64, align: 64, offset: 64)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !260, file: !4, line: 784, baseType: !120, size: 32, align: 32, offset: 128)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !260, file: !4, line: 784, baseType: !122, size: 64, align: 64, offset: 192)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !260, file: !4, line: 784, baseType: !49, size: 128, align: 64, offset: 256)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !260, file: !4, line: 784, baseType: !268, size: 256, align: 64, offset: 384)
!268 = !DICompositeType(tag: DW_TAG_union_type, scope: !260, file: !4, line: 784, size: 256, align: 64, elements: !269)
!269 = !{!270, !271}
!270 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !268, file: !4, line: 784, baseType: !57, size: 32, align: 32)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !268, file: !4, line: 784, baseType: !132, size: 256, align: 64)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !260, file: !4, line: 784, baseType: !34, size: 64, align: 64, offset: 640)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !260, file: !4, line: 784, baseType: !47, size: 32, align: 32, offset: 704)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !260, file: !4, line: 785, baseType: !275, size: 64, align: 64, offset: 768)
!275 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timer_cb", file: !4, line: 308, baseType: !276)
!276 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!277 = !DISubroutineType(types: !278)
!278 = !{null, !258}
!279 = !DIDerivedType(tag: DW_TAG_member, name: "heap_node", scope: !260, file: !4, line: 785, baseType: !280, size: 192, align: 64, offset: 832)
!280 = !DICompositeType(tag: DW_TAG_array_type, baseType: !39, size: 192, align: 64, elements: !281)
!281 = !{!282}
!282 = !DISubrange(count: 3)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !260, file: !4, line: 785, baseType: !187, size: 64, align: 64, offset: 1024)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "repeat", scope: !260, file: !4, line: 785, baseType: !187, size: 64, align: 64, offset: 1088)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "start_id", scope: !260, file: !4, line: 785, baseType: !187, size: 64, align: 64, offset: 1152)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!287 = !{!288, !292, !295, !298, !299, !302, !307, !312, !315, !316, !325, !328, !329, !330}
!288 = distinct !DISubprogram(name: "uv_timer_init", scope: !1, file: !1, line: 54, type: !289, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!289 = !DISubroutineType(types: !290)
!290 = !{!57, !41, !258}
!291 = !{}
!292 = distinct !DISubprogram(name: "uv_timer_start", scope: !1, file: !1, line: 62, type: !293, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!293 = !DISubroutineType(types: !294)
!294 = !{!57, !258, !275, !187, !187}
!295 = distinct !DISubprogram(name: "uv_timer_stop", scope: !1, file: !1, line: 93, type: !296, isLocal: false, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!296 = !DISubroutineType(types: !297)
!297 = !{!57, !258}
!298 = distinct !DISubprogram(name: "uv_timer_again", scope: !1, file: !1, line: 106, type: !296, isLocal: false, isDefinition: true, scopeLine: 106, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!299 = distinct !DISubprogram(name: "uv_timer_set_repeat", scope: !1, file: !1, line: 119, type: !300, isLocal: false, isDefinition: true, scopeLine: 119, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!300 = !DISubroutineType(types: !301)
!301 = !{null, !258, !187}
!302 = distinct !DISubprogram(name: "uv_timer_get_repeat", scope: !1, file: !1, line: 124, type: !303, isLocal: false, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!303 = !DISubroutineType(types: !304)
!304 = !{!187, !305}
!305 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !259)
!307 = distinct !DISubprogram(name: "uv__next_timeout", scope: !1, file: !1, line: 129, type: !308, isLocal: false, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!308 = !DISubroutineType(types: !309)
!309 = !{!57, !310}
!310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !311, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!312 = distinct !DISubprogram(name: "uv__run_timers", scope: !1, file: !1, line: 150, type: !313, isLocal: false, isDefinition: true, scopeLine: 150, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!313 = !DISubroutineType(types: !314)
!314 = !{null, !41}
!315 = distinct !DISubprogram(name: "uv__timer_close", scope: !1, file: !1, line: 170, type: !277, isLocal: false, isDefinition: true, scopeLine: 170, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!316 = distinct !DISubprogram(name: "heap_insert", scope: !246, file: !246, line: 106, type: !317, isLocal: true, isDefinition: true, scopeLine: 108, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!317 = !DISubroutineType(types: !318)
!318 = !{null, !244, !249, !319}
!319 = !DIDerivedType(tag: DW_TAG_typedef, name: "heap_compare_fn", file: !246, line: 46, baseType: !320)
!320 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !321, size: 64, align: 64)
!321 = !DISubroutineType(types: !322)
!322 = !{!57, !323, !323}
!323 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !324, size: 64, align: 64)
!324 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !250)
!325 = distinct !DISubprogram(name: "heap_node_swap", scope: !246, file: !246, line: 72, type: !326, isLocal: true, isDefinition: true, scopeLine: 74, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!326 = !DISubroutineType(types: !327)
!327 = !{null, !244, !249, !249}
!328 = distinct !DISubprogram(name: "timer_less_than", scope: !1, file: !1, line: 29, type: !321, isLocal: true, isDefinition: true, scopeLine: 30, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!329 = distinct !DISubprogram(name: "heap_remove", scope: !246, file: !246, line: 150, type: !317, isLocal: true, isDefinition: true, scopeLine: 152, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!330 = distinct !DISubprogram(name: "heap_min", scope: !246, file: !246, line: 67, type: !331, isLocal: true, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !291)
!331 = !DISubroutineType(types: !332)
!332 = !{!249, !256}
!333 = !{i32 2, !"Dwarf Version", i32 4}
!334 = !{i32 2, !"Debug Info Version", i32 3}
!335 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!336 = !DILocalVariable(name: "loop", arg: 1, scope: !288, file: !1, line: 54, type: !41)
!337 = !DIExpression()
!338 = !DILocation(line: 54, column: 30, scope: !288)
!339 = !DILocalVariable(name: "handle", arg: 2, scope: !288, file: !1, line: 54, type: !258)
!340 = !DILocation(line: 54, column: 48, scope: !288)
!341 = !DILocation(line: 55, column: 3, scope: !288)
!342 = !DILocation(line: 55, column: 3, scope: !343)
!343 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 1)
!344 = distinct !DILexicalBlock(scope: !288, file: !1, line: 55, column: 3)
!345 = !DILocation(line: 55, column: 3, scope: !346)
!346 = !DILexicalBlockFile(scope: !347, file: !1, discriminator: 2)
!347 = distinct !DILexicalBlock(scope: !344, file: !1, line: 55, column: 3)
!348 = !DILocation(line: 55, column: 3, scope: !349)
!349 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 3)
!350 = !DILocation(line: 56, column: 3, scope: !288)
!351 = !DILocation(line: 56, column: 11, scope: !288)
!352 = !DILocation(line: 56, column: 20, scope: !288)
!353 = !DILocation(line: 57, column: 3, scope: !288)
!354 = !DILocation(line: 57, column: 11, scope: !288)
!355 = !DILocation(line: 57, column: 18, scope: !288)
!356 = !DILocation(line: 58, column: 3, scope: !288)
!357 = !DILocalVariable(name: "handle", arg: 1, scope: !292, file: !1, line: 62, type: !258)
!358 = !DILocation(line: 62, column: 32, scope: !292)
!359 = !DILocalVariable(name: "cb", arg: 2, scope: !292, file: !1, line: 63, type: !275)
!360 = !DILocation(line: 63, column: 32, scope: !292)
!361 = !DILocalVariable(name: "timeout", arg: 3, scope: !292, file: !1, line: 64, type: !187)
!362 = !DILocation(line: 64, column: 29, scope: !292)
!363 = !DILocalVariable(name: "repeat", arg: 4, scope: !292, file: !1, line: 65, type: !187)
!364 = !DILocation(line: 65, column: 29, scope: !292)
!365 = !DILocalVariable(name: "clamped_timeout", scope: !292, file: !1, line: 66, type: !187)
!366 = !DILocation(line: 66, column: 12, scope: !292)
!367 = !DILocation(line: 68, column: 7, scope: !368)
!368 = distinct !DILexicalBlock(scope: !292, file: !1, line: 68, column: 7)
!369 = !DILocation(line: 68, column: 10, scope: !368)
!370 = !DILocation(line: 68, column: 7, scope: !292)
!371 = !DILocation(line: 69, column: 5, scope: !368)
!372 = !DILocation(line: 71, column: 7, scope: !373)
!373 = distinct !DILexicalBlock(scope: !292, file: !1, line: 71, column: 7)
!374 = !DILocation(line: 71, column: 7, scope: !292)
!375 = !DILocation(line: 72, column: 19, scope: !373)
!376 = !DILocation(line: 72, column: 5, scope: !373)
!377 = !DILocation(line: 74, column: 21, scope: !292)
!378 = !DILocation(line: 74, column: 29, scope: !292)
!379 = !DILocation(line: 74, column: 35, scope: !292)
!380 = !DILocation(line: 74, column: 42, scope: !292)
!381 = !DILocation(line: 74, column: 40, scope: !292)
!382 = !DILocation(line: 74, column: 19, scope: !292)
!383 = !DILocation(line: 75, column: 7, scope: !384)
!384 = distinct !DILexicalBlock(scope: !292, file: !1, line: 75, column: 7)
!385 = !DILocation(line: 75, column: 25, scope: !384)
!386 = !DILocation(line: 75, column: 23, scope: !384)
!387 = !DILocation(line: 75, column: 7, scope: !292)
!388 = !DILocation(line: 76, column: 21, scope: !384)
!389 = !DILocation(line: 76, column: 5, scope: !384)
!390 = !DILocation(line: 78, column: 22, scope: !292)
!391 = !DILocation(line: 78, column: 3, scope: !292)
!392 = !DILocation(line: 78, column: 11, scope: !292)
!393 = !DILocation(line: 78, column: 20, scope: !292)
!394 = !DILocation(line: 79, column: 21, scope: !292)
!395 = !DILocation(line: 79, column: 3, scope: !292)
!396 = !DILocation(line: 79, column: 11, scope: !292)
!397 = !DILocation(line: 79, column: 19, scope: !292)
!398 = !DILocation(line: 80, column: 20, scope: !292)
!399 = !DILocation(line: 80, column: 3, scope: !292)
!400 = !DILocation(line: 80, column: 11, scope: !292)
!401 = !DILocation(line: 80, column: 18, scope: !292)
!402 = !DILocation(line: 82, column: 22, scope: !292)
!403 = !DILocation(line: 82, column: 30, scope: !292)
!404 = !DILocation(line: 82, column: 36, scope: !292)
!405 = !DILocation(line: 82, column: 49, scope: !292)
!406 = !DILocation(line: 82, column: 3, scope: !292)
!407 = !DILocation(line: 82, column: 11, scope: !292)
!408 = !DILocation(line: 82, column: 20, scope: !292)
!409 = !DILocation(line: 84, column: 31, scope: !292)
!410 = !DILocation(line: 84, column: 39, scope: !292)
!411 = !DILocation(line: 84, column: 45, scope: !292)
!412 = !DILocation(line: 84, column: 15, scope: !292)
!413 = !DILocation(line: 85, column: 36, scope: !292)
!414 = !DILocation(line: 85, column: 44, scope: !292)
!415 = !DILocation(line: 85, column: 15, scope: !292)
!416 = !DILocation(line: 84, column: 3, scope: !292)
!417 = !DILocation(line: 87, column: 3, scope: !292)
!418 = !DILocation(line: 87, column: 3, scope: !419)
!419 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 1)
!420 = distinct !DILexicalBlock(scope: !292, file: !1, line: 87, column: 3)
!421 = !DILocation(line: 87, column: 3, scope: !422)
!422 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 2)
!423 = !DILocation(line: 87, column: 3, scope: !424)
!424 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 3)
!425 = !DILocation(line: 87, column: 3, scope: !426)
!426 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 4)
!427 = !DILocation(line: 87, column: 3, scope: !428)
!428 = !DILexicalBlockFile(scope: !429, file: !1, discriminator: 5)
!429 = distinct !DILexicalBlock(scope: !420, file: !1, line: 87, column: 3)
!430 = !DILocation(line: 87, column: 3, scope: !431)
!431 = !DILexicalBlockFile(scope: !429, file: !1, discriminator: 6)
!432 = !DILocation(line: 87, column: 3, scope: !433)
!433 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 7)
!434 = !DILocation(line: 87, column: 3, scope: !435)
!435 = !DILexicalBlockFile(scope: !436, file: !1, discriminator: 8)
!436 = distinct !DILexicalBlock(scope: !420, file: !1, line: 87, column: 3)
!437 = !DILocation(line: 87, column: 3, scope: !438)
!438 = !DILexicalBlockFile(scope: !439, file: !1, discriminator: 9)
!439 = distinct !DILexicalBlock(scope: !436, file: !1, line: 87, column: 3)
!440 = !DILocation(line: 87, column: 3, scope: !441)
!441 = !DILexicalBlockFile(scope: !439, file: !1, discriminator: 10)
!442 = !DILocation(line: 87, column: 3, scope: !443)
!443 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 11)
!444 = !DILocation(line: 89, column: 3, scope: !292)
!445 = !DILocation(line: 90, column: 1, scope: !292)
!446 = !DILocalVariable(name: "handle", arg: 1, scope: !295, file: !1, line: 93, type: !258)
!447 = !DILocation(line: 93, column: 31, scope: !295)
!448 = !DILocation(line: 94, column: 8, scope: !449)
!449 = distinct !DILexicalBlock(scope: !295, file: !1, line: 94, column: 7)
!450 = !DILocation(line: 94, column: 7, scope: !295)
!451 = !DILocation(line: 95, column: 5, scope: !449)
!452 = !DILocation(line: 97, column: 31, scope: !295)
!453 = !DILocation(line: 97, column: 39, scope: !295)
!454 = !DILocation(line: 97, column: 45, scope: !295)
!455 = !DILocation(line: 97, column: 15, scope: !295)
!456 = !DILocation(line: 98, column: 36, scope: !295)
!457 = !DILocation(line: 98, column: 44, scope: !295)
!458 = !DILocation(line: 98, column: 15, scope: !295)
!459 = !DILocation(line: 97, column: 3, scope: !295)
!460 = !DILocation(line: 100, column: 3, scope: !295)
!461 = !DILocation(line: 100, column: 3, scope: !462)
!462 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 1)
!463 = distinct !DILexicalBlock(scope: !295, file: !1, line: 100, column: 3)
!464 = !DILocation(line: 100, column: 3, scope: !465)
!465 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 2)
!466 = !DILocation(line: 100, column: 3, scope: !467)
!467 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 3)
!468 = !DILocation(line: 100, column: 3, scope: !469)
!469 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 4)
!470 = !DILocation(line: 100, column: 3, scope: !471)
!471 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 5)
!472 = distinct !DILexicalBlock(scope: !463, file: !1, line: 100, column: 3)
!473 = !DILocation(line: 100, column: 3, scope: !474)
!474 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 6)
!475 = !DILocation(line: 100, column: 3, scope: !476)
!476 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 7)
!477 = !DILocation(line: 100, column: 3, scope: !478)
!478 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 8)
!479 = distinct !DILexicalBlock(scope: !463, file: !1, line: 100, column: 3)
!480 = !DILocation(line: 100, column: 3, scope: !481)
!481 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 9)
!482 = distinct !DILexicalBlock(scope: !479, file: !1, line: 100, column: 3)
!483 = !DILocation(line: 100, column: 3, scope: !484)
!484 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 10)
!485 = !DILocation(line: 100, column: 3, scope: !486)
!486 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 11)
!487 = !DILocation(line: 102, column: 3, scope: !295)
!488 = !DILocation(line: 103, column: 1, scope: !295)
!489 = !DILocalVariable(name: "heap", arg: 1, scope: !316, file: !246, line: 106, type: !244)
!490 = !DILocation(line: 106, column: 1, scope: !316)
!491 = !DILocalVariable(name: "newnode", arg: 2, scope: !316, file: !246, line: 106, type: !249)
!492 = !DILocalVariable(name: "less_than", arg: 3, scope: !316, file: !246, line: 106, type: !319)
!493 = !DILocalVariable(name: "parent", scope: !316, file: !246, line: 109, type: !494)
!494 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !249, size: 64, align: 64)
!495 = !DILocation(line: 109, column: 22, scope: !316)
!496 = !DILocalVariable(name: "child", scope: !316, file: !246, line: 110, type: !494)
!497 = !DILocation(line: 110, column: 22, scope: !316)
!498 = !DILocalVariable(name: "path", scope: !316, file: !246, line: 111, type: !47)
!499 = !DILocation(line: 111, column: 16, scope: !316)
!500 = !DILocalVariable(name: "n", scope: !316, file: !246, line: 112, type: !47)
!501 = !DILocation(line: 112, column: 16, scope: !316)
!502 = !DILocalVariable(name: "k", scope: !316, file: !246, line: 113, type: !47)
!503 = !DILocation(line: 113, column: 16, scope: !316)
!504 = !DILocation(line: 115, column: 3, scope: !316)
!505 = !DILocation(line: 115, column: 12, scope: !316)
!506 = !DILocation(line: 115, column: 17, scope: !316)
!507 = !DILocation(line: 116, column: 3, scope: !316)
!508 = !DILocation(line: 116, column: 12, scope: !316)
!509 = !DILocation(line: 116, column: 18, scope: !316)
!510 = !DILocation(line: 117, column: 3, scope: !316)
!511 = !DILocation(line: 117, column: 12, scope: !316)
!512 = !DILocation(line: 117, column: 19, scope: !316)
!513 = !DILocation(line: 122, column: 8, scope: !316)
!514 = !DILocation(line: 123, column: 10, scope: !515)
!515 = distinct !DILexicalBlock(scope: !316, file: !246, line: 123, column: 3)
!516 = !DILocation(line: 123, column: 23, scope: !515)
!517 = !DILocation(line: 123, column: 29, scope: !515)
!518 = !DILocation(line: 123, column: 21, scope: !515)
!519 = !DILocation(line: 123, column: 17, scope: !515)
!520 = !DILocation(line: 123, column: 8, scope: !515)
!521 = !DILocation(line: 123, column: 36, scope: !522)
!522 = !DILexicalBlockFile(scope: !523, file: !246, discriminator: 1)
!523 = distinct !DILexicalBlock(scope: !515, file: !246, line: 123, column: 3)
!524 = !DILocation(line: 123, column: 38, scope: !522)
!525 = !DILocation(line: 123, column: 3, scope: !522)
!526 = !DILocation(line: 124, column: 13, scope: !523)
!527 = !DILocation(line: 124, column: 18, scope: !523)
!528 = !DILocation(line: 124, column: 27, scope: !523)
!529 = !DILocation(line: 124, column: 29, scope: !523)
!530 = !DILocation(line: 124, column: 24, scope: !523)
!531 = !DILocation(line: 124, column: 10, scope: !523)
!532 = !DILocation(line: 124, column: 5, scope: !523)
!533 = !DILocation(line: 123, column: 46, scope: !534)
!534 = !DILexicalBlockFile(scope: !523, file: !246, discriminator: 2)
!535 = !DILocation(line: 123, column: 54, scope: !534)
!536 = !DILocation(line: 123, column: 3, scope: !534)
!537 = !DILocation(line: 127, column: 21, scope: !316)
!538 = !DILocation(line: 127, column: 27, scope: !316)
!539 = !DILocation(line: 127, column: 18, scope: !316)
!540 = !DILocation(line: 127, column: 10, scope: !316)
!541 = !DILocation(line: 128, column: 3, scope: !316)
!542 = !DILocation(line: 128, column: 10, scope: !543)
!543 = !DILexicalBlockFile(scope: !316, file: !246, discriminator: 1)
!544 = !DILocation(line: 128, column: 12, scope: !543)
!545 = !DILocation(line: 128, column: 3, scope: !543)
!546 = !DILocation(line: 129, column: 14, scope: !547)
!547 = distinct !DILexicalBlock(scope: !316, file: !246, line: 128, column: 17)
!548 = !DILocation(line: 129, column: 12, scope: !547)
!549 = !DILocation(line: 130, column: 9, scope: !550)
!550 = distinct !DILexicalBlock(scope: !547, file: !246, line: 130, column: 9)
!551 = !DILocation(line: 130, column: 14, scope: !550)
!552 = !DILocation(line: 130, column: 9, scope: !547)
!553 = !DILocation(line: 131, column: 18, scope: !550)
!554 = !DILocation(line: 131, column: 17, scope: !550)
!555 = !DILocation(line: 131, column: 26, scope: !550)
!556 = !DILocation(line: 131, column: 13, scope: !550)
!557 = !DILocation(line: 131, column: 7, scope: !550)
!558 = !DILocation(line: 133, column: 18, scope: !550)
!559 = !DILocation(line: 133, column: 17, scope: !550)
!560 = !DILocation(line: 133, column: 26, scope: !550)
!561 = !DILocation(line: 133, column: 13, scope: !550)
!562 = !DILocation(line: 134, column: 10, scope: !547)
!563 = !DILocation(line: 135, column: 7, scope: !547)
!564 = !DILocation(line: 128, column: 3, scope: !565)
!565 = !DILexicalBlockFile(scope: !316, file: !246, discriminator: 2)
!566 = !DILocation(line: 139, column: 22, scope: !316)
!567 = !DILocation(line: 139, column: 21, scope: !316)
!568 = !DILocation(line: 139, column: 3, scope: !316)
!569 = !DILocation(line: 139, column: 12, scope: !316)
!570 = !DILocation(line: 139, column: 19, scope: !316)
!571 = !DILocation(line: 140, column: 12, scope: !316)
!572 = !DILocation(line: 140, column: 4, scope: !316)
!573 = !DILocation(line: 140, column: 10, scope: !316)
!574 = !DILocation(line: 141, column: 3, scope: !316)
!575 = !DILocation(line: 141, column: 9, scope: !316)
!576 = !DILocation(line: 141, column: 15, scope: !316)
!577 = !DILocation(line: 146, column: 3, scope: !316)
!578 = !DILocation(line: 146, column: 10, scope: !543)
!579 = !DILocation(line: 146, column: 19, scope: !543)
!580 = !DILocation(line: 146, column: 26, scope: !543)
!581 = !DILocation(line: 146, column: 34, scope: !543)
!582 = !DILocation(line: 146, column: 37, scope: !565)
!583 = !DILocation(line: 146, column: 47, scope: !565)
!584 = !DILocation(line: 146, column: 56, scope: !565)
!585 = !DILocation(line: 146, column: 65, scope: !565)
!586 = !DILocation(line: 146, column: 34, scope: !565)
!587 = !DILocation(line: 146, column: 3, scope: !588)
!588 = !DILexicalBlockFile(scope: !316, file: !246, discriminator: 3)
!589 = !DILocation(line: 147, column: 20, scope: !316)
!590 = !DILocation(line: 147, column: 26, scope: !316)
!591 = !DILocation(line: 147, column: 35, scope: !316)
!592 = !DILocation(line: 147, column: 43, scope: !316)
!593 = !DILocation(line: 147, column: 5, scope: !316)
!594 = !DILocation(line: 146, column: 3, scope: !595)
!595 = !DILexicalBlockFile(scope: !316, file: !246, discriminator: 4)
!596 = !DILocation(line: 148, column: 1, scope: !316)
!597 = !DILocalVariable(name: "ha", arg: 1, scope: !328, file: !1, line: 29, type: !323)
!598 = !DILocation(line: 29, column: 52, scope: !328)
!599 = !DILocalVariable(name: "hb", arg: 2, scope: !328, file: !1, line: 30, type: !323)
!600 = !DILocation(line: 30, column: 52, scope: !328)
!601 = !DILocalVariable(name: "a", scope: !328, file: !1, line: 31, type: !305)
!602 = !DILocation(line: 31, column: 21, scope: !328)
!603 = !DILocalVariable(name: "b", scope: !328, file: !1, line: 32, type: !305)
!604 = !DILocation(line: 32, column: 21, scope: !328)
!605 = !DILocation(line: 34, column: 7, scope: !328)
!606 = !DILocation(line: 34, column: 5, scope: !328)
!607 = !DILocation(line: 35, column: 7, scope: !328)
!608 = !DILocation(line: 35, column: 5, scope: !328)
!609 = !DILocation(line: 37, column: 7, scope: !610)
!610 = distinct !DILexicalBlock(scope: !328, file: !1, line: 37, column: 7)
!611 = !DILocation(line: 37, column: 10, scope: !610)
!612 = !DILocation(line: 37, column: 20, scope: !610)
!613 = !DILocation(line: 37, column: 23, scope: !610)
!614 = !DILocation(line: 37, column: 18, scope: !610)
!615 = !DILocation(line: 37, column: 7, scope: !328)
!616 = !DILocation(line: 38, column: 5, scope: !610)
!617 = !DILocation(line: 39, column: 7, scope: !618)
!618 = distinct !DILexicalBlock(scope: !328, file: !1, line: 39, column: 7)
!619 = !DILocation(line: 39, column: 10, scope: !618)
!620 = !DILocation(line: 39, column: 20, scope: !618)
!621 = !DILocation(line: 39, column: 23, scope: !618)
!622 = !DILocation(line: 39, column: 18, scope: !618)
!623 = !DILocation(line: 39, column: 7, scope: !328)
!624 = !DILocation(line: 40, column: 5, scope: !618)
!625 = !DILocation(line: 45, column: 7, scope: !626)
!626 = distinct !DILexicalBlock(scope: !328, file: !1, line: 45, column: 7)
!627 = !DILocation(line: 45, column: 10, scope: !626)
!628 = !DILocation(line: 45, column: 21, scope: !626)
!629 = !DILocation(line: 45, column: 24, scope: !626)
!630 = !DILocation(line: 45, column: 19, scope: !626)
!631 = !DILocation(line: 45, column: 7, scope: !328)
!632 = !DILocation(line: 46, column: 5, scope: !626)
!633 = !DILocation(line: 47, column: 7, scope: !634)
!634 = distinct !DILexicalBlock(scope: !328, file: !1, line: 47, column: 7)
!635 = !DILocation(line: 47, column: 10, scope: !634)
!636 = !DILocation(line: 47, column: 21, scope: !634)
!637 = !DILocation(line: 47, column: 24, scope: !634)
!638 = !DILocation(line: 47, column: 19, scope: !634)
!639 = !DILocation(line: 47, column: 7, scope: !328)
!640 = !DILocation(line: 48, column: 5, scope: !634)
!641 = !DILocation(line: 50, column: 3, scope: !328)
!642 = !DILocation(line: 51, column: 1, scope: !328)
!643 = !DILocalVariable(name: "heap", arg: 1, scope: !329, file: !246, line: 150, type: !244)
!644 = !DILocation(line: 150, column: 1, scope: !329)
!645 = !DILocalVariable(name: "node", arg: 2, scope: !329, file: !246, line: 150, type: !249)
!646 = !DILocalVariable(name: "less_than", arg: 3, scope: !329, file: !246, line: 150, type: !319)
!647 = !DILocalVariable(name: "smallest", scope: !329, file: !246, line: 153, type: !249)
!648 = !DILocation(line: 153, column: 21, scope: !329)
!649 = !DILocalVariable(name: "max", scope: !329, file: !246, line: 154, type: !494)
!650 = !DILocation(line: 154, column: 22, scope: !329)
!651 = !DILocalVariable(name: "child", scope: !329, file: !246, line: 155, type: !249)
!652 = !DILocation(line: 155, column: 21, scope: !329)
!653 = !DILocalVariable(name: "path", scope: !329, file: !246, line: 156, type: !47)
!654 = !DILocation(line: 156, column: 16, scope: !329)
!655 = !DILocalVariable(name: "k", scope: !329, file: !246, line: 157, type: !47)
!656 = !DILocation(line: 157, column: 16, scope: !329)
!657 = !DILocalVariable(name: "n", scope: !329, file: !246, line: 158, type: !47)
!658 = !DILocation(line: 158, column: 16, scope: !329)
!659 = !DILocation(line: 160, column: 7, scope: !660)
!660 = distinct !DILexicalBlock(scope: !329, file: !246, line: 160, column: 7)
!661 = !DILocation(line: 160, column: 13, scope: !660)
!662 = !DILocation(line: 160, column: 19, scope: !660)
!663 = !DILocation(line: 160, column: 7, scope: !329)
!664 = !DILocation(line: 161, column: 5, scope: !660)
!665 = !DILocation(line: 166, column: 8, scope: !329)
!666 = !DILocation(line: 167, column: 10, scope: !667)
!667 = distinct !DILexicalBlock(scope: !329, file: !246, line: 167, column: 3)
!668 = !DILocation(line: 167, column: 19, scope: !667)
!669 = !DILocation(line: 167, column: 25, scope: !667)
!670 = !DILocation(line: 167, column: 17, scope: !667)
!671 = !DILocation(line: 167, column: 8, scope: !667)
!672 = !DILocation(line: 167, column: 32, scope: !673)
!673 = !DILexicalBlockFile(scope: !674, file: !246, discriminator: 1)
!674 = distinct !DILexicalBlock(scope: !667, file: !246, line: 167, column: 3)
!675 = !DILocation(line: 167, column: 34, scope: !673)
!676 = !DILocation(line: 167, column: 3, scope: !673)
!677 = !DILocation(line: 168, column: 13, scope: !674)
!678 = !DILocation(line: 168, column: 18, scope: !674)
!679 = !DILocation(line: 168, column: 27, scope: !674)
!680 = !DILocation(line: 168, column: 29, scope: !674)
!681 = !DILocation(line: 168, column: 24, scope: !674)
!682 = !DILocation(line: 168, column: 10, scope: !674)
!683 = !DILocation(line: 168, column: 5, scope: !674)
!684 = !DILocation(line: 167, column: 42, scope: !685)
!685 = !DILexicalBlockFile(scope: !674, file: !246, discriminator: 2)
!686 = !DILocation(line: 167, column: 50, scope: !685)
!687 = !DILocation(line: 167, column: 3, scope: !685)
!688 = !DILocation(line: 171, column: 10, scope: !329)
!689 = !DILocation(line: 171, column: 16, scope: !329)
!690 = !DILocation(line: 171, column: 7, scope: !329)
!691 = !DILocation(line: 172, column: 3, scope: !329)
!692 = !DILocation(line: 172, column: 10, scope: !693)
!693 = !DILexicalBlockFile(scope: !329, file: !246, discriminator: 1)
!694 = !DILocation(line: 172, column: 12, scope: !693)
!695 = !DILocation(line: 172, column: 3, scope: !693)
!696 = !DILocation(line: 173, column: 9, scope: !697)
!697 = distinct !DILexicalBlock(scope: !698, file: !246, line: 173, column: 9)
!698 = distinct !DILexicalBlock(scope: !329, file: !246, line: 172, column: 17)
!699 = !DILocation(line: 173, column: 14, scope: !697)
!700 = !DILocation(line: 173, column: 9, scope: !698)
!701 = !DILocation(line: 174, column: 16, scope: !697)
!702 = !DILocation(line: 174, column: 15, scope: !697)
!703 = !DILocation(line: 174, column: 22, scope: !697)
!704 = !DILocation(line: 174, column: 11, scope: !697)
!705 = !DILocation(line: 174, column: 7, scope: !697)
!706 = !DILocation(line: 176, column: 16, scope: !697)
!707 = !DILocation(line: 176, column: 15, scope: !697)
!708 = !DILocation(line: 176, column: 22, scope: !697)
!709 = !DILocation(line: 176, column: 11, scope: !697)
!710 = !DILocation(line: 177, column: 10, scope: !698)
!711 = !DILocation(line: 178, column: 7, scope: !698)
!712 = !DILocation(line: 172, column: 3, scope: !713)
!713 = !DILexicalBlockFile(scope: !329, file: !246, discriminator: 2)
!714 = !DILocation(line: 181, column: 3, scope: !329)
!715 = !DILocation(line: 181, column: 9, scope: !329)
!716 = !DILocation(line: 181, column: 15, scope: !329)
!717 = !DILocation(line: 184, column: 12, scope: !329)
!718 = !DILocation(line: 184, column: 11, scope: !329)
!719 = !DILocation(line: 184, column: 9, scope: !329)
!720 = !DILocation(line: 185, column: 4, scope: !329)
!721 = !DILocation(line: 185, column: 8, scope: !329)
!722 = !DILocation(line: 187, column: 7, scope: !723)
!723 = distinct !DILexicalBlock(scope: !329, file: !246, line: 187, column: 7)
!724 = !DILocation(line: 187, column: 16, scope: !723)
!725 = !DILocation(line: 187, column: 13, scope: !723)
!726 = !DILocation(line: 187, column: 7, scope: !329)
!727 = !DILocation(line: 189, column: 9, scope: !728)
!728 = distinct !DILexicalBlock(scope: !729, file: !246, line: 189, column: 9)
!729 = distinct !DILexicalBlock(scope: !723, file: !246, line: 187, column: 22)
!730 = !DILocation(line: 189, column: 18, scope: !728)
!731 = !DILocation(line: 189, column: 24, scope: !728)
!732 = !DILocation(line: 189, column: 15, scope: !728)
!733 = !DILocation(line: 189, column: 9, scope: !729)
!734 = !DILocation(line: 190, column: 7, scope: !735)
!735 = distinct !DILexicalBlock(scope: !728, file: !246, line: 189, column: 29)
!736 = !DILocation(line: 190, column: 13, scope: !735)
!737 = !DILocation(line: 190, column: 17, scope: !735)
!738 = !DILocation(line: 191, column: 5, scope: !735)
!739 = !DILocation(line: 192, column: 5, scope: !729)
!740 = !DILocation(line: 196, column: 17, scope: !329)
!741 = !DILocation(line: 196, column: 23, scope: !329)
!742 = !DILocation(line: 196, column: 3, scope: !329)
!743 = !DILocation(line: 196, column: 10, scope: !329)
!744 = !DILocation(line: 196, column: 15, scope: !329)
!745 = !DILocation(line: 197, column: 18, scope: !329)
!746 = !DILocation(line: 197, column: 24, scope: !329)
!747 = !DILocation(line: 197, column: 3, scope: !329)
!748 = !DILocation(line: 197, column: 10, scope: !329)
!749 = !DILocation(line: 197, column: 16, scope: !329)
!750 = !DILocation(line: 198, column: 19, scope: !329)
!751 = !DILocation(line: 198, column: 25, scope: !329)
!752 = !DILocation(line: 198, column: 3, scope: !329)
!753 = !DILocation(line: 198, column: 10, scope: !329)
!754 = !DILocation(line: 198, column: 17, scope: !329)
!755 = !DILocation(line: 200, column: 7, scope: !756)
!756 = distinct !DILexicalBlock(scope: !329, file: !246, line: 200, column: 7)
!757 = !DILocation(line: 200, column: 14, scope: !756)
!758 = !DILocation(line: 200, column: 19, scope: !756)
!759 = !DILocation(line: 200, column: 7, scope: !329)
!760 = !DILocation(line: 201, column: 27, scope: !761)
!761 = distinct !DILexicalBlock(scope: !756, file: !246, line: 200, column: 28)
!762 = !DILocation(line: 201, column: 5, scope: !761)
!763 = !DILocation(line: 201, column: 12, scope: !761)
!764 = !DILocation(line: 201, column: 18, scope: !761)
!765 = !DILocation(line: 201, column: 25, scope: !761)
!766 = !DILocation(line: 202, column: 3, scope: !761)
!767 = !DILocation(line: 204, column: 7, scope: !768)
!768 = distinct !DILexicalBlock(scope: !329, file: !246, line: 204, column: 7)
!769 = !DILocation(line: 204, column: 14, scope: !768)
!770 = !DILocation(line: 204, column: 20, scope: !768)
!771 = !DILocation(line: 204, column: 7, scope: !329)
!772 = !DILocation(line: 205, column: 28, scope: !773)
!773 = distinct !DILexicalBlock(scope: !768, file: !246, line: 204, column: 29)
!774 = !DILocation(line: 205, column: 5, scope: !773)
!775 = !DILocation(line: 205, column: 12, scope: !773)
!776 = !DILocation(line: 205, column: 19, scope: !773)
!777 = !DILocation(line: 205, column: 26, scope: !773)
!778 = !DILocation(line: 206, column: 3, scope: !773)
!779 = !DILocation(line: 208, column: 7, scope: !780)
!780 = distinct !DILexicalBlock(scope: !329, file: !246, line: 208, column: 7)
!781 = !DILocation(line: 208, column: 13, scope: !780)
!782 = !DILocation(line: 208, column: 20, scope: !780)
!783 = !DILocation(line: 208, column: 7, scope: !329)
!784 = !DILocation(line: 209, column: 17, scope: !785)
!785 = distinct !DILexicalBlock(scope: !780, file: !246, line: 208, column: 29)
!786 = !DILocation(line: 209, column: 5, scope: !785)
!787 = !DILocation(line: 209, column: 11, scope: !785)
!788 = !DILocation(line: 209, column: 15, scope: !785)
!789 = !DILocation(line: 210, column: 3, scope: !785)
!790 = !DILocation(line: 210, column: 14, scope: !791)
!791 = !DILexicalBlockFile(scope: !792, file: !246, discriminator: 1)
!792 = distinct !DILexicalBlock(scope: !780, file: !246, line: 210, column: 14)
!793 = !DILocation(line: 210, column: 20, scope: !791)
!794 = !DILocation(line: 210, column: 28, scope: !791)
!795 = !DILocation(line: 210, column: 36, scope: !791)
!796 = !DILocation(line: 210, column: 33, scope: !791)
!797 = !DILocation(line: 211, column: 26, scope: !798)
!798 = distinct !DILexicalBlock(scope: !792, file: !246, line: 210, column: 42)
!799 = !DILocation(line: 211, column: 5, scope: !798)
!800 = !DILocation(line: 211, column: 11, scope: !798)
!801 = !DILocation(line: 211, column: 19, scope: !798)
!802 = !DILocation(line: 211, column: 24, scope: !798)
!803 = !DILocation(line: 212, column: 3, scope: !798)
!804 = !DILocation(line: 213, column: 27, scope: !805)
!805 = distinct !DILexicalBlock(scope: !792, file: !246, line: 212, column: 10)
!806 = !DILocation(line: 213, column: 5, scope: !805)
!807 = !DILocation(line: 213, column: 11, scope: !805)
!808 = !DILocation(line: 213, column: 19, scope: !805)
!809 = !DILocation(line: 213, column: 25, scope: !805)
!810 = !DILocation(line: 220, column: 3, scope: !329)
!811 = !DILocation(line: 221, column: 16, scope: !812)
!812 = distinct !DILexicalBlock(scope: !813, file: !246, line: 220, column: 12)
!813 = distinct !DILexicalBlock(scope: !814, file: !246, line: 220, column: 3)
!814 = distinct !DILexicalBlock(scope: !329, file: !246, line: 220, column: 3)
!815 = !DILocation(line: 221, column: 14, scope: !812)
!816 = !DILocation(line: 222, column: 9, scope: !817)
!817 = distinct !DILexicalBlock(scope: !812, file: !246, line: 222, column: 9)
!818 = !DILocation(line: 222, column: 16, scope: !817)
!819 = !DILocation(line: 222, column: 21, scope: !817)
!820 = !DILocation(line: 222, column: 29, scope: !817)
!821 = !DILocation(line: 222, column: 32, scope: !822)
!822 = !DILexicalBlockFile(scope: !817, file: !246, discriminator: 1)
!823 = !DILocation(line: 222, column: 42, scope: !822)
!824 = !DILocation(line: 222, column: 49, scope: !822)
!825 = !DILocation(line: 222, column: 55, scope: !822)
!826 = !DILocation(line: 222, column: 9, scope: !822)
!827 = !DILocation(line: 223, column: 18, scope: !817)
!828 = !DILocation(line: 223, column: 25, scope: !817)
!829 = !DILocation(line: 223, column: 16, scope: !817)
!830 = !DILocation(line: 223, column: 7, scope: !817)
!831 = !DILocation(line: 224, column: 9, scope: !832)
!832 = distinct !DILexicalBlock(scope: !812, file: !246, line: 224, column: 9)
!833 = !DILocation(line: 224, column: 16, scope: !832)
!834 = !DILocation(line: 224, column: 22, scope: !832)
!835 = !DILocation(line: 224, column: 30, scope: !832)
!836 = !DILocation(line: 224, column: 33, scope: !837)
!837 = !DILexicalBlockFile(scope: !832, file: !246, discriminator: 1)
!838 = !DILocation(line: 224, column: 43, scope: !837)
!839 = !DILocation(line: 224, column: 50, scope: !837)
!840 = !DILocation(line: 224, column: 57, scope: !837)
!841 = !DILocation(line: 224, column: 9, scope: !837)
!842 = !DILocation(line: 225, column: 18, scope: !832)
!843 = !DILocation(line: 225, column: 25, scope: !832)
!844 = !DILocation(line: 225, column: 16, scope: !832)
!845 = !DILocation(line: 225, column: 7, scope: !832)
!846 = !DILocation(line: 226, column: 9, scope: !847)
!847 = distinct !DILexicalBlock(scope: !812, file: !246, line: 226, column: 9)
!848 = !DILocation(line: 226, column: 21, scope: !847)
!849 = !DILocation(line: 226, column: 18, scope: !847)
!850 = !DILocation(line: 226, column: 9, scope: !812)
!851 = !DILocation(line: 227, column: 7, scope: !847)
!852 = !DILocation(line: 228, column: 20, scope: !812)
!853 = !DILocation(line: 228, column: 26, scope: !812)
!854 = !DILocation(line: 228, column: 33, scope: !812)
!855 = !DILocation(line: 228, column: 5, scope: !812)
!856 = !DILocation(line: 220, column: 3, scope: !857)
!857 = !DILexicalBlockFile(scope: !813, file: !246, discriminator: 1)
!858 = !DILocation(line: 235, column: 3, scope: !329)
!859 = !DILocation(line: 235, column: 10, scope: !693)
!860 = !DILocation(line: 235, column: 17, scope: !693)
!861 = !DILocation(line: 235, column: 24, scope: !693)
!862 = !DILocation(line: 235, column: 32, scope: !693)
!863 = !DILocation(line: 235, column: 35, scope: !713)
!864 = !DILocation(line: 235, column: 45, scope: !713)
!865 = !DILocation(line: 235, column: 52, scope: !713)
!866 = !DILocation(line: 235, column: 59, scope: !713)
!867 = !DILocation(line: 235, column: 32, scope: !713)
!868 = !DILocation(line: 235, column: 3, scope: !869)
!869 = !DILexicalBlockFile(scope: !329, file: !246, discriminator: 3)
!870 = !DILocation(line: 236, column: 20, scope: !329)
!871 = !DILocation(line: 236, column: 26, scope: !329)
!872 = !DILocation(line: 236, column: 33, scope: !329)
!873 = !DILocation(line: 236, column: 41, scope: !329)
!874 = !DILocation(line: 236, column: 5, scope: !329)
!875 = !DILocation(line: 235, column: 3, scope: !876)
!876 = !DILexicalBlockFile(scope: !329, file: !246, discriminator: 4)
!877 = !DILocation(line: 237, column: 1, scope: !329)
!878 = !DILocalVariable(name: "handle", arg: 1, scope: !298, file: !1, line: 106, type: !258)
!879 = !DILocation(line: 106, column: 32, scope: !298)
!880 = !DILocation(line: 107, column: 7, scope: !881)
!881 = distinct !DILexicalBlock(scope: !298, file: !1, line: 107, column: 7)
!882 = !DILocation(line: 107, column: 15, scope: !881)
!883 = !DILocation(line: 107, column: 24, scope: !881)
!884 = !DILocation(line: 107, column: 7, scope: !298)
!885 = !DILocation(line: 108, column: 5, scope: !881)
!886 = !DILocation(line: 110, column: 7, scope: !887)
!887 = distinct !DILexicalBlock(scope: !298, file: !1, line: 110, column: 7)
!888 = !DILocation(line: 110, column: 15, scope: !887)
!889 = !DILocation(line: 110, column: 7, scope: !298)
!890 = !DILocation(line: 111, column: 19, scope: !891)
!891 = distinct !DILexicalBlock(scope: !887, file: !1, line: 110, column: 23)
!892 = !DILocation(line: 111, column: 5, scope: !891)
!893 = !DILocation(line: 112, column: 20, scope: !891)
!894 = !DILocation(line: 112, column: 28, scope: !891)
!895 = !DILocation(line: 112, column: 36, scope: !891)
!896 = !DILocation(line: 112, column: 46, scope: !891)
!897 = !DILocation(line: 112, column: 54, scope: !891)
!898 = !DILocation(line: 112, column: 62, scope: !891)
!899 = !DILocation(line: 112, column: 70, scope: !891)
!900 = !DILocation(line: 112, column: 5, scope: !891)
!901 = !DILocation(line: 113, column: 3, scope: !891)
!902 = !DILocation(line: 115, column: 3, scope: !298)
!903 = !DILocation(line: 116, column: 1, scope: !298)
!904 = !DILocalVariable(name: "handle", arg: 1, scope: !299, file: !1, line: 119, type: !258)
!905 = !DILocation(line: 119, column: 38, scope: !299)
!906 = !DILocalVariable(name: "repeat", arg: 2, scope: !299, file: !1, line: 119, type: !187)
!907 = !DILocation(line: 119, column: 55, scope: !299)
!908 = !DILocation(line: 120, column: 20, scope: !299)
!909 = !DILocation(line: 120, column: 3, scope: !299)
!910 = !DILocation(line: 120, column: 11, scope: !299)
!911 = !DILocation(line: 120, column: 18, scope: !299)
!912 = !DILocation(line: 121, column: 1, scope: !299)
!913 = !DILocalVariable(name: "handle", arg: 1, scope: !302, file: !1, line: 124, type: !305)
!914 = !DILocation(line: 124, column: 48, scope: !302)
!915 = !DILocation(line: 125, column: 10, scope: !302)
!916 = !DILocation(line: 125, column: 18, scope: !302)
!917 = !DILocation(line: 125, column: 3, scope: !302)
!918 = !DILocalVariable(name: "loop", arg: 1, scope: !307, file: !1, line: 129, type: !310)
!919 = !DILocation(line: 129, column: 39, scope: !307)
!920 = !DILocalVariable(name: "heap_node", scope: !307, file: !1, line: 130, type: !323)
!921 = !DILocation(line: 130, column: 27, scope: !307)
!922 = !DILocalVariable(name: "handle", scope: !307, file: !1, line: 131, type: !305)
!923 = !DILocation(line: 131, column: 21, scope: !307)
!924 = !DILocalVariable(name: "diff", scope: !307, file: !1, line: 132, type: !187)
!925 = !DILocation(line: 132, column: 12, scope: !307)
!926 = !DILocation(line: 134, column: 46, scope: !307)
!927 = !DILocation(line: 134, column: 52, scope: !307)
!928 = !DILocation(line: 134, column: 24, scope: !307)
!929 = !DILocation(line: 134, column: 15, scope: !307)
!930 = !DILocation(line: 134, column: 13, scope: !307)
!931 = !DILocation(line: 135, column: 7, scope: !932)
!932 = distinct !DILexicalBlock(scope: !307, file: !1, line: 135, column: 7)
!933 = !DILocation(line: 135, column: 17, scope: !932)
!934 = !DILocation(line: 135, column: 7, scope: !307)
!935 = !DILocation(line: 136, column: 5, scope: !932)
!936 = !DILocation(line: 138, column: 12, scope: !307)
!937 = !DILocation(line: 138, column: 10, scope: !307)
!938 = !DILocation(line: 139, column: 7, scope: !939)
!939 = distinct !DILexicalBlock(scope: !307, file: !1, line: 139, column: 7)
!940 = !DILocation(line: 139, column: 15, scope: !939)
!941 = !DILocation(line: 139, column: 26, scope: !939)
!942 = !DILocation(line: 139, column: 32, scope: !939)
!943 = !DILocation(line: 139, column: 23, scope: !939)
!944 = !DILocation(line: 139, column: 7, scope: !307)
!945 = !DILocation(line: 140, column: 5, scope: !939)
!946 = !DILocation(line: 142, column: 10, scope: !307)
!947 = !DILocation(line: 142, column: 18, scope: !307)
!948 = !DILocation(line: 142, column: 28, scope: !307)
!949 = !DILocation(line: 142, column: 34, scope: !307)
!950 = !DILocation(line: 142, column: 26, scope: !307)
!951 = !DILocation(line: 142, column: 8, scope: !307)
!952 = !DILocation(line: 143, column: 7, scope: !953)
!953 = distinct !DILexicalBlock(scope: !307, file: !1, line: 143, column: 7)
!954 = !DILocation(line: 143, column: 12, scope: !953)
!955 = !DILocation(line: 143, column: 7, scope: !307)
!956 = !DILocation(line: 144, column: 10, scope: !953)
!957 = !DILocation(line: 144, column: 5, scope: !953)
!958 = !DILocation(line: 146, column: 10, scope: !307)
!959 = !DILocation(line: 146, column: 3, scope: !307)
!960 = !DILocation(line: 147, column: 1, scope: !307)
!961 = !DILocalVariable(name: "heap", arg: 1, scope: !330, file: !246, line: 67, type: !256)
!962 = !DILocation(line: 67, column: 1, scope: !330)
!963 = !DILocation(line: 68, column: 10, scope: !330)
!964 = !DILocation(line: 68, column: 16, scope: !330)
!965 = !DILocation(line: 68, column: 3, scope: !330)
!966 = !DILocalVariable(name: "loop", arg: 1, scope: !312, file: !1, line: 150, type: !41)
!967 = !DILocation(line: 150, column: 32, scope: !312)
!968 = !DILocalVariable(name: "heap_node", scope: !312, file: !1, line: 151, type: !249)
!969 = !DILocation(line: 151, column: 21, scope: !312)
!970 = !DILocalVariable(name: "handle", scope: !312, file: !1, line: 152, type: !258)
!971 = !DILocation(line: 152, column: 15, scope: !312)
!972 = !DILocation(line: 154, column: 3, scope: !312)
!973 = !DILocation(line: 155, column: 42, scope: !974)
!974 = distinct !DILexicalBlock(scope: !975, file: !1, line: 154, column: 12)
!975 = distinct !DILexicalBlock(scope: !976, file: !1, line: 154, column: 3)
!976 = distinct !DILexicalBlock(scope: !312, file: !1, line: 154, column: 3)
!977 = !DILocation(line: 155, column: 48, scope: !974)
!978 = !DILocation(line: 155, column: 26, scope: !974)
!979 = !DILocation(line: 155, column: 17, scope: !974)
!980 = !DILocation(line: 155, column: 15, scope: !974)
!981 = !DILocation(line: 156, column: 9, scope: !982)
!982 = distinct !DILexicalBlock(scope: !974, file: !1, line: 156, column: 9)
!983 = !DILocation(line: 156, column: 19, scope: !982)
!984 = !DILocation(line: 156, column: 9, scope: !974)
!985 = !DILocation(line: 157, column: 7, scope: !982)
!986 = !DILocation(line: 159, column: 14, scope: !974)
!987 = !DILocation(line: 159, column: 12, scope: !974)
!988 = !DILocation(line: 160, column: 9, scope: !989)
!989 = distinct !DILexicalBlock(scope: !974, file: !1, line: 160, column: 9)
!990 = !DILocation(line: 160, column: 17, scope: !989)
!991 = !DILocation(line: 160, column: 27, scope: !989)
!992 = !DILocation(line: 160, column: 33, scope: !989)
!993 = !DILocation(line: 160, column: 25, scope: !989)
!994 = !DILocation(line: 160, column: 9, scope: !974)
!995 = !DILocation(line: 161, column: 7, scope: !989)
!996 = !DILocation(line: 163, column: 19, scope: !974)
!997 = !DILocation(line: 163, column: 5, scope: !974)
!998 = !DILocation(line: 164, column: 20, scope: !974)
!999 = !DILocation(line: 164, column: 5, scope: !974)
!1000 = !DILocation(line: 165, column: 5, scope: !974)
!1001 = !DILocation(line: 165, column: 13, scope: !974)
!1002 = !DILocation(line: 165, column: 22, scope: !974)
!1003 = !DILocation(line: 154, column: 3, scope: !1004)
!1004 = !DILexicalBlockFile(scope: !975, file: !1, discriminator: 1)
!1005 = !DILocation(line: 167, column: 1, scope: !312)
!1006 = !DILocalVariable(name: "handle", arg: 1, scope: !315, file: !1, line: 170, type: !258)
!1007 = !DILocation(line: 170, column: 34, scope: !315)
!1008 = !DILocation(line: 171, column: 17, scope: !315)
!1009 = !DILocation(line: 171, column: 3, scope: !315)
!1010 = !DILocation(line: 172, column: 1, scope: !315)
!1011 = !DILocalVariable(name: "heap", arg: 1, scope: !325, file: !246, line: 72, type: !244)
!1012 = !DILocation(line: 72, column: 41, scope: !325)
!1013 = !DILocalVariable(name: "parent", arg: 2, scope: !325, file: !246, line: 73, type: !249)
!1014 = !DILocation(line: 73, column: 46, scope: !325)
!1015 = !DILocalVariable(name: "child", arg: 3, scope: !325, file: !246, line: 74, type: !249)
!1016 = !DILocation(line: 74, column: 46, scope: !325)
!1017 = !DILocalVariable(name: "sibling", scope: !325, file: !246, line: 75, type: !249)
!1018 = !DILocation(line: 75, column: 21, scope: !325)
!1019 = !DILocalVariable(name: "t", scope: !325, file: !246, line: 76, type: !250)
!1020 = !DILocation(line: 76, column: 20, scope: !325)
!1021 = !DILocation(line: 78, column: 8, scope: !325)
!1022 = !DILocation(line: 78, column: 7, scope: !325)
!1023 = !DILocation(line: 79, column: 4, scope: !325)
!1024 = !DILocation(line: 79, column: 14, scope: !325)
!1025 = !DILocation(line: 79, column: 13, scope: !325)
!1026 = !DILocation(line: 80, column: 4, scope: !325)
!1027 = !DILocation(line: 80, column: 12, scope: !325)
!1028 = !DILocation(line: 82, column: 20, scope: !325)
!1029 = !DILocation(line: 82, column: 3, scope: !325)
!1030 = !DILocation(line: 82, column: 11, scope: !325)
!1031 = !DILocation(line: 82, column: 18, scope: !325)
!1032 = !DILocation(line: 83, column: 7, scope: !1033)
!1033 = distinct !DILexicalBlock(scope: !325, file: !246, line: 83, column: 7)
!1034 = !DILocation(line: 83, column: 14, scope: !1033)
!1035 = !DILocation(line: 83, column: 22, scope: !1033)
!1036 = !DILocation(line: 83, column: 19, scope: !1033)
!1037 = !DILocation(line: 83, column: 7, scope: !325)
!1038 = !DILocation(line: 84, column: 19, scope: !1039)
!1039 = distinct !DILexicalBlock(scope: !1033, file: !246, line: 83, column: 29)
!1040 = !DILocation(line: 84, column: 5, scope: !1039)
!1041 = !DILocation(line: 84, column: 12, scope: !1039)
!1042 = !DILocation(line: 84, column: 17, scope: !1039)
!1043 = !DILocation(line: 85, column: 15, scope: !1039)
!1044 = !DILocation(line: 85, column: 22, scope: !1039)
!1045 = !DILocation(line: 85, column: 13, scope: !1039)
!1046 = !DILocation(line: 86, column: 3, scope: !1039)
!1047 = !DILocation(line: 87, column: 20, scope: !1048)
!1048 = distinct !DILexicalBlock(scope: !1033, file: !246, line: 86, column: 10)
!1049 = !DILocation(line: 87, column: 5, scope: !1048)
!1050 = !DILocation(line: 87, column: 12, scope: !1048)
!1051 = !DILocation(line: 87, column: 18, scope: !1048)
!1052 = !DILocation(line: 88, column: 15, scope: !1048)
!1053 = !DILocation(line: 88, column: 22, scope: !1048)
!1054 = !DILocation(line: 88, column: 13, scope: !1048)
!1055 = !DILocation(line: 90, column: 7, scope: !1056)
!1056 = distinct !DILexicalBlock(scope: !325, file: !246, line: 90, column: 7)
!1057 = !DILocation(line: 90, column: 15, scope: !1056)
!1058 = !DILocation(line: 90, column: 7, scope: !325)
!1059 = !DILocation(line: 91, column: 23, scope: !1056)
!1060 = !DILocation(line: 91, column: 5, scope: !1056)
!1061 = !DILocation(line: 91, column: 14, scope: !1056)
!1062 = !DILocation(line: 91, column: 21, scope: !1056)
!1063 = !DILocation(line: 93, column: 7, scope: !1064)
!1064 = distinct !DILexicalBlock(scope: !325, file: !246, line: 93, column: 7)
!1065 = !DILocation(line: 93, column: 15, scope: !1064)
!1066 = !DILocation(line: 93, column: 20, scope: !1064)
!1067 = !DILocation(line: 93, column: 7, scope: !325)
!1068 = !DILocation(line: 94, column: 28, scope: !1064)
!1069 = !DILocation(line: 94, column: 5, scope: !1064)
!1070 = !DILocation(line: 94, column: 13, scope: !1064)
!1071 = !DILocation(line: 94, column: 19, scope: !1064)
!1072 = !DILocation(line: 94, column: 26, scope: !1064)
!1073 = !DILocation(line: 95, column: 7, scope: !1074)
!1074 = distinct !DILexicalBlock(scope: !325, file: !246, line: 95, column: 7)
!1075 = !DILocation(line: 95, column: 15, scope: !1074)
!1076 = !DILocation(line: 95, column: 21, scope: !1074)
!1077 = !DILocation(line: 95, column: 7, scope: !325)
!1078 = !DILocation(line: 96, column: 29, scope: !1074)
!1079 = !DILocation(line: 96, column: 5, scope: !1074)
!1080 = !DILocation(line: 96, column: 13, scope: !1074)
!1081 = !DILocation(line: 96, column: 20, scope: !1074)
!1082 = !DILocation(line: 96, column: 27, scope: !1074)
!1083 = !DILocation(line: 98, column: 7, scope: !1084)
!1084 = distinct !DILexicalBlock(scope: !325, file: !246, line: 98, column: 7)
!1085 = !DILocation(line: 98, column: 14, scope: !1084)
!1086 = !DILocation(line: 98, column: 21, scope: !1084)
!1087 = !DILocation(line: 98, column: 7, scope: !325)
!1088 = !DILocation(line: 99, column: 17, scope: !1084)
!1089 = !DILocation(line: 99, column: 5, scope: !1084)
!1090 = !DILocation(line: 99, column: 11, scope: !1084)
!1091 = !DILocation(line: 99, column: 15, scope: !1084)
!1092 = !DILocation(line: 100, column: 12, scope: !1093)
!1093 = distinct !DILexicalBlock(scope: !1084, file: !246, line: 100, column: 12)
!1094 = !DILocation(line: 100, column: 19, scope: !1093)
!1095 = !DILocation(line: 100, column: 27, scope: !1093)
!1096 = !DILocation(line: 100, column: 35, scope: !1093)
!1097 = !DILocation(line: 100, column: 32, scope: !1093)
!1098 = !DILocation(line: 100, column: 12, scope: !1084)
!1099 = !DILocation(line: 101, column: 27, scope: !1093)
!1100 = !DILocation(line: 101, column: 5, scope: !1093)
!1101 = !DILocation(line: 101, column: 12, scope: !1093)
!1102 = !DILocation(line: 101, column: 20, scope: !1093)
!1103 = !DILocation(line: 101, column: 25, scope: !1093)
!1104 = !DILocation(line: 103, column: 28, scope: !1093)
!1105 = !DILocation(line: 103, column: 5, scope: !1093)
!1106 = !DILocation(line: 103, column: 12, scope: !1093)
!1107 = !DILocation(line: 103, column: 20, scope: !1093)
!1108 = !DILocation(line: 103, column: 26, scope: !1093)
!1109 = !DILocation(line: 104, column: 1, scope: !325)
