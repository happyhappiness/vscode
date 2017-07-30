; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/async.c'
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

@.str = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.1 = private unnamed_addr constant [69 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/async.c\00", align 1
@__PRETTY_FUNCTION__.uv_async_init = private unnamed_addr constant [58 x i8] c"int uv_async_init(uv_loop_t *, uv_async_t *, uv_async_cb)\00", align 1
@__PRETTY_FUNCTION__.uv__async_close = private unnamed_addr constant [35 x i8] c"void uv__async_close(uv_async_t *)\00", align 1
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@uv__async_send.val = internal constant i64 1, align 8
@.str.3 = private unnamed_addr constant [17 x i8] c"/proc/self/fd/%d\00", align 1
@uv__async_eventfd.no_eventfd2 = internal global i32 0, align 4
@uv__async_eventfd.no_eventfd = internal global i32 0, align 4
@.str.4 = private unnamed_addr constant [29 x i8] c"w == &loop->async_io_watcher\00", align 1
@__PRETTY_FUNCTION__.uv__async_io = private unnamed_addr constant [57 x i8] c"void uv__async_io(uv_loop_t *, uv__io_t *, unsigned int)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_async_init(%struct.uv_loop_s* %loop, %struct.uv_async_s* %handle, void (%struct.uv_async_s*)* %async_cb) #0 !dbg !250 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_async_s*, align 8
  %async_cb.addr = alloca void (%struct.uv_async_s*)*, align 8
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !285, metadata !286), !dbg !287
  store %struct.uv_async_s* %handle, %struct.uv_async_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_async_s** %handle.addr, metadata !288, metadata !286), !dbg !289
  store void (%struct.uv_async_s*)* %async_cb, void (%struct.uv_async_s*)** %async_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_async_s*)** %async_cb.addr, metadata !290, metadata !286), !dbg !291
  call void @llvm.dbg.declare(metadata i32* %err, metadata !292, metadata !286), !dbg !293
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !294
  %call = call i32 @uv__async_start(%struct.uv_loop_s* %0), !dbg !295
  store i32 %call, i32* %err, align 4, !dbg !296
  %1 = load i32, i32* %err, align 4, !dbg !297
  %tobool = icmp ne i32 %1, 0, !dbg !297
  br i1 %tobool, label %if.then, label %if.end, !dbg !299

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !300
  store i32 %2, i32* %retval, align 4, !dbg !301
  br label %return, !dbg !301

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !302

do.body:                                          ; preds = %if.end
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !303
  %4 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !303
  %5 = bitcast %struct.uv_async_s* %4 to %struct.uv_handle_s*, !dbg !303
  %loop1 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %5, i32 0, i32 1, !dbg !303
  store %struct.uv_loop_s* %3, %struct.uv_loop_s** %loop1, align 8, !dbg !303
  %6 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !303
  %7 = bitcast %struct.uv_async_s* %6 to %struct.uv_handle_s*, !dbg !303
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %7, i32 0, i32 2, !dbg !303
  store i32 1, i32* %type, align 8, !dbg !303
  %8 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !303
  %9 = bitcast %struct.uv_async_s* %8 to %struct.uv_handle_s*, !dbg !303
  %flags = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 7, !dbg !303
  store i32 8192, i32* %flags, align 8, !dbg !303
  br label %do.body2, !dbg !303

do.body2:                                         ; preds = %do.body
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !306
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 2, !dbg !306
  %11 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !306
  %12 = bitcast %struct.uv_async_s* %11 to %struct.uv_handle_s*, !dbg !306
  %handle_queue3 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %12, i32 0, i32 4, !dbg !306
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue3, i64 0, i64 0, !dbg !306
  %13 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !306
  store [2 x i8*]* %handle_queue, [2 x i8*]** %13, align 8, !dbg !306
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !306
  %handle_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 2, !dbg !306
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue4, i64 0, i64 1, !dbg !306
  %15 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !306
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !306
  %17 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !306
  %18 = bitcast %struct.uv_async_s* %17 to %struct.uv_handle_s*, !dbg !306
  %handle_queue6 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %18, i32 0, i32 4, !dbg !306
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue6, i64 0, i64 1, !dbg !306
  %19 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !306
  store [2 x i8*]* %16, [2 x i8*]** %19, align 8, !dbg !306
  %20 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !306
  %21 = bitcast %struct.uv_async_s* %20 to %struct.uv_handle_s*, !dbg !306
  %handle_queue8 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %21, i32 0, i32 4, !dbg !306
  %22 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !306
  %23 = bitcast %struct.uv_async_s* %22 to %struct.uv_handle_s*, !dbg !306
  %handle_queue9 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %23, i32 0, i32 4, !dbg !306
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue9, i64 0, i64 1, !dbg !306
  %24 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !306
  %25 = load [2 x i8*]*, [2 x i8*]** %24, align 8, !dbg !306
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %25, i64 0, i64 0, !dbg !306
  %26 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !306
  store [2 x i8*]* %handle_queue8, [2 x i8*]** %26, align 8, !dbg !306
  %27 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !306
  %28 = bitcast %struct.uv_async_s* %27 to %struct.uv_handle_s*, !dbg !306
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %28, i32 0, i32 4, !dbg !306
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !306
  %handle_queue13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %29, i32 0, i32 2, !dbg !306
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !306
  %30 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !306
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %30, align 8, !dbg !306
  br label %do.end, !dbg !306

do.end:                                           ; preds = %do.body2
  %31 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !309
  %32 = bitcast %struct.uv_async_s* %31 to %struct.uv_handle_s*, !dbg !309
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %32, i32 0, i32 6, !dbg !309
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !309
  br label %do.end15, !dbg !309

do.end15:                                         ; preds = %do.end
  %33 = load void (%struct.uv_async_s*)*, void (%struct.uv_async_s*)** %async_cb.addr, align 8, !dbg !311
  %34 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !312
  %async_cb16 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %34, i32 0, i32 8, !dbg !313
  store void (%struct.uv_async_s*)* %33, void (%struct.uv_async_s*)** %async_cb16, align 8, !dbg !314
  %35 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !315
  %pending = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %35, i32 0, i32 10, !dbg !316
  store i32 0, i32* %pending, align 8, !dbg !317
  br label %do.body17, !dbg !318

do.body17:                                        ; preds = %do.end15
  %36 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !319
  %async_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %36, i32 0, i32 21, !dbg !319
  %37 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !319
  %queue = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %37, i32 0, i32 9, !dbg !319
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !319
  %38 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !319
  store [2 x i8*]* %async_handles, [2 x i8*]** %38, align 8, !dbg !319
  %39 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !319
  %async_handles19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %39, i32 0, i32 21, !dbg !319
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles19, i64 0, i64 1, !dbg !319
  %40 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !319
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 8, !dbg !319
  %42 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !319
  %queue21 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %42, i32 0, i32 9, !dbg !319
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue21, i64 0, i64 1, !dbg !319
  %43 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !319
  store [2 x i8*]* %41, [2 x i8*]** %43, align 8, !dbg !319
  %44 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !319
  %queue23 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %44, i32 0, i32 9, !dbg !319
  %45 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !319
  %queue24 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %45, i32 0, i32 9, !dbg !319
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue24, i64 0, i64 1, !dbg !319
  %46 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !319
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !319
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !319
  %48 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !319
  store [2 x i8*]* %queue23, [2 x i8*]** %48, align 8, !dbg !319
  %49 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !319
  %queue27 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %49, i32 0, i32 9, !dbg !319
  %50 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !319
  %async_handles28 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %50, i32 0, i32 21, !dbg !319
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles28, i64 0, i64 1, !dbg !319
  %51 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !319
  store [2 x i8*]* %queue27, [2 x i8*]** %51, align 8, !dbg !319
  br label %do.end30, !dbg !319

do.end30:                                         ; preds = %do.body17
  br label %do.body31, !dbg !322

do.body31:                                        ; preds = %do.end30
  %52 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !323
  %flags32 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %52, i32 0, i32 7, !dbg !323
  %53 = load i32, i32* %flags32, align 8, !dbg !323
  %and = and i32 %53, 0, !dbg !323
  %cmp = icmp eq i32 %and, 0, !dbg !323
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !323

cond.true:                                        ; preds = %do.body31
  br label %cond.end, !dbg !326

cond.false:                                       ; preds = %do.body31
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.1, i32 0, i32 0), i32 53, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv_async_init, i32 0, i32 0)) #6, !dbg !328
  unreachable, !dbg !328
                                                  ; No predecessors!
  br label %cond.end, !dbg !330

cond.end:                                         ; preds = %54, %cond.true
  %55 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !332
  %flags33 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %55, i32 0, i32 7, !dbg !332
  %56 = load i32, i32* %flags33, align 8, !dbg !332
  %and34 = and i32 %56, 16384, !dbg !332
  %cmp35 = icmp ne i32 %and34, 0, !dbg !332
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !332

if.then36:                                        ; preds = %cond.end
  br label %do.end47, !dbg !335

if.end37:                                         ; preds = %cond.end
  %57 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !337
  %flags38 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %57, i32 0, i32 7, !dbg !337
  %58 = load i32, i32* %flags38, align 8, !dbg !337
  %or = or i32 %58, 16384, !dbg !337
  store i32 %or, i32* %flags38, align 8, !dbg !337
  %59 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !337
  %flags39 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %59, i32 0, i32 7, !dbg !337
  %60 = load i32, i32* %flags39, align 8, !dbg !337
  %and40 = and i32 %60, 8192, !dbg !337
  %cmp41 = icmp ne i32 %and40, 0, !dbg !337
  br i1 %cmp41, label %if.then42, label %if.end46, !dbg !337

if.then42:                                        ; preds = %if.end37
  br label %do.body43, !dbg !339

do.body43:                                        ; preds = %if.then42
  %61 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !342
  %loop44 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %61, i32 0, i32 1, !dbg !342
  %62 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop44, align 8, !dbg !342
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %62, i32 0, i32 1, !dbg !342
  %63 = load i32, i32* %active_handles, align 8, !dbg !342
  %inc = add i32 %63, 1, !dbg !342
  store i32 %inc, i32* %active_handles, align 8, !dbg !342
  br label %do.end45, !dbg !342

do.end45:                                         ; preds = %do.body43
  br label %if.end46, !dbg !345

if.end46:                                         ; preds = %do.end45, %if.end37
  br label %do.end47, !dbg !347

do.end47:                                         ; preds = %if.end46, %if.then36
  store i32 0, i32* %retval, align 4, !dbg !349
  br label %return, !dbg !349

return:                                           ; preds = %do.end47, %if.then
  %64 = load i32, i32* %retval, align 4, !dbg !350
  ret i32 %64, !dbg !350
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @uv__async_start(%struct.uv_loop_s* %loop) #0 !dbg !270 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %pipefd = alloca [2 x i32], align 4
  %err = alloca i32, align 4
  %buf = alloca [32 x i8], align 16
  %fd9 = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !351, metadata !286), !dbg !352
  call void @llvm.dbg.declare(metadata [2 x i32]* %pipefd, metadata !353, metadata !286), !dbg !354
  call void @llvm.dbg.declare(metadata i32* %err, metadata !355, metadata !286), !dbg !356
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !357
  %async_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 23, !dbg !359
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher, i32 0, i32 5, !dbg !360
  %1 = load i32, i32* %fd, align 8, !dbg !360
  %cmp = icmp ne i32 %1, -1, !dbg !361
  br i1 %cmp, label %if.then, label %if.end, !dbg !362

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !363
  br label %return, !dbg !363

if.end:                                           ; preds = %entry
  %call = call i32 @uv__async_eventfd(), !dbg !364
  store i32 %call, i32* %err, align 4, !dbg !365
  %2 = load i32, i32* %err, align 4, !dbg !366
  %cmp1 = icmp sge i32 %2, 0, !dbg !368
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !369

if.then2:                                         ; preds = %if.end
  %3 = load i32, i32* %err, align 4, !dbg !370
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 0, !dbg !372
  store i32 %3, i32* %arrayidx, align 4, !dbg !373
  %arrayidx3 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 1, !dbg !374
  store i32 -1, i32* %arrayidx3, align 4, !dbg !375
  br label %if.end26, !dbg !376

if.else:                                          ; preds = %if.end
  %4 = load i32, i32* %err, align 4, !dbg !377
  %cmp4 = icmp eq i32 %4, -38, !dbg !379
  br i1 %cmp4, label %if.then5, label %if.end25, !dbg !380

if.then5:                                         ; preds = %if.else
  %arraydecay = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i32 0, i32 0, !dbg !381
  %call6 = call i32 @uv__make_pipe(i32* %arraydecay, i32 2048), !dbg !383
  store i32 %call6, i32* %err, align 4, !dbg !384
  %5 = load i32, i32* %err, align 4, !dbg !385
  %cmp7 = icmp eq i32 %5, 0, !dbg !387
  br i1 %cmp7, label %if.then8, label %if.end24, !dbg !388

if.then8:                                         ; preds = %if.then5
  call void @llvm.dbg.declare(metadata [32 x i8]* %buf, metadata !389, metadata !286), !dbg !394
  call void @llvm.dbg.declare(metadata i32* %fd9, metadata !395, metadata !286), !dbg !396
  %arraydecay10 = getelementptr inbounds [32 x i8], [32 x i8]* %buf, i32 0, i32 0, !dbg !397
  %arrayidx11 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 0, !dbg !398
  %6 = load i32, i32* %arrayidx11, align 4, !dbg !398
  %call12 = call i32 (i8*, i64, i8*, ...) @snprintf(i8* %arraydecay10, i64 32, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.3, i32 0, i32 0), i32 %6) #7, !dbg !399
  %arraydecay13 = getelementptr inbounds [32 x i8], [32 x i8]* %buf, i32 0, i32 0, !dbg !400
  %call14 = call i32 @uv__open_cloexec(i8* %arraydecay13, i32 2), !dbg !401
  store i32 %call14, i32* %fd9, align 4, !dbg !402
  %7 = load i32, i32* %fd9, align 4, !dbg !403
  %cmp15 = icmp sge i32 %7, 0, !dbg !405
  br i1 %cmp15, label %if.then16, label %if.end23, !dbg !406

if.then16:                                        ; preds = %if.then8
  %arrayidx17 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 0, !dbg !407
  %8 = load i32, i32* %arrayidx17, align 4, !dbg !407
  %call18 = call i32 @uv__close(i32 %8), !dbg !409
  %arrayidx19 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 1, !dbg !410
  %9 = load i32, i32* %arrayidx19, align 4, !dbg !410
  %call20 = call i32 @uv__close(i32 %9), !dbg !411
  %10 = load i32, i32* %fd9, align 4, !dbg !412
  %arrayidx21 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 0, !dbg !413
  store i32 %10, i32* %arrayidx21, align 4, !dbg !414
  %11 = load i32, i32* %fd9, align 4, !dbg !415
  %arrayidx22 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 1, !dbg !416
  store i32 %11, i32* %arrayidx22, align 4, !dbg !417
  br label %if.end23, !dbg !418

if.end23:                                         ; preds = %if.then16, %if.then8
  br label %if.end24, !dbg !419

if.end24:                                         ; preds = %if.end23, %if.then5
  br label %if.end25, !dbg !420

if.end25:                                         ; preds = %if.end24, %if.else
  br label %if.end26

if.end26:                                         ; preds = %if.end25, %if.then2
  %12 = load i32, i32* %err, align 4, !dbg !421
  %cmp27 = icmp slt i32 %12, 0, !dbg !423
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !424

if.then28:                                        ; preds = %if.end26
  %13 = load i32, i32* %err, align 4, !dbg !425
  store i32 %13, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

if.end29:                                         ; preds = %if.end26
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !427
  %async_io_watcher30 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 23, !dbg !428
  %arrayidx31 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 0, !dbg !429
  %15 = load i32, i32* %arrayidx31, align 4, !dbg !429
  call void @uv__io_init(%struct.uv__io_s* %async_io_watcher30, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__async_io, i32 %15), !dbg !430
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !431
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !432
  %async_io_watcher32 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 23, !dbg !433
  call void @uv__io_start(%struct.uv_loop_s* %16, %struct.uv__io_s* %async_io_watcher32, i32 1), !dbg !434
  %arrayidx33 = getelementptr inbounds [2 x i32], [2 x i32]* %pipefd, i64 0, i64 1, !dbg !435
  %18 = load i32, i32* %arrayidx33, align 4, !dbg !435
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !436
  %async_wfd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %19, i32 0, i32 24, !dbg !437
  store i32 %18, i32* %async_wfd, align 8, !dbg !438
  store i32 0, i32* %retval, align 4, !dbg !439
  br label %return, !dbg !439

return:                                           ; preds = %if.end29, %if.then28, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !440
  ret i32 %20, !dbg !440
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_async_send(%struct.uv_async_s* %handle) #0 !dbg !254 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_async_s*, align 8
  store %struct.uv_async_s* %handle, %struct.uv_async_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_async_s** %handle.addr, metadata !441, metadata !286), !dbg !442
  %0 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !443
  %pending = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %0, i32 0, i32 10, !dbg !443
  %1 = load volatile i32, i32* %pending, align 8, !dbg !443
  %cmp = icmp ne i32 %1, 0, !dbg !445
  br i1 %cmp, label %if.then, label %if.end, !dbg !446

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !447
  br label %return, !dbg !447

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !448
  %pending1 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %2, i32 0, i32 10, !dbg !450
  %call = call i32 @cmpxchgi(i32* %pending1, i32 0, i32 1), !dbg !451
  %cmp2 = icmp eq i32 %call, 0, !dbg !452
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !453

if.then3:                                         ; preds = %if.end
  %3 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !454
  %loop = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %3, i32 0, i32 1, !dbg !455
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !455
  call void @uv__async_send(%struct.uv_loop_s* %4), !dbg !456
  br label %if.end4, !dbg !456

if.end4:                                          ; preds = %if.then3, %if.end
  store i32 0, i32* %retval, align 4, !dbg !457
  br label %return, !dbg !457

return:                                           ; preds = %if.end4, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !458
  ret i32 %5, !dbg !458
}

; Function Attrs: nounwind uwtable
define internal i32 @cmpxchgi(i32* %ptr, i32 %oldval, i32 %newval) #0 !dbg !264 {
entry:
  %ptr.addr = alloca i32*, align 8
  %oldval.addr = alloca i32, align 4
  %newval.addr = alloca i32, align 4
  %out = alloca i32, align 4
  store i32* %ptr, i32** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ptr.addr, metadata !459, metadata !286), !dbg !460
  store i32 %oldval, i32* %oldval.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %oldval.addr, metadata !461, metadata !286), !dbg !460
  store i32 %newval, i32* %newval.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %newval.addr, metadata !462, metadata !286), !dbg !460
  call void @llvm.dbg.declare(metadata i32* %out, metadata !463, metadata !286), !dbg !464
  %0 = load i32*, i32** %ptr.addr, align 8, !dbg !465
  %1 = load i32, i32* %newval.addr, align 4, !dbg !466
  %2 = load i32, i32* %oldval.addr, align 4, !dbg !467
  %3 = call i32 asm sideeffect "lock; cmpxchg $2, $1;", "={ax},=*m,r,0,*m,~{memory},~{dirflag},~{fpsr},~{flags}"(i32* %0, i32 %1, i32 %2, i32* %0) #7, !dbg !468, !srcloc !469
  store i32 %3, i32* %out, align 4, !dbg !468
  %4 = load i32, i32* %out, align 4, !dbg !470
  ret i32 %4, !dbg !471
}

; Function Attrs: nounwind uwtable
define internal void @uv__async_send(%struct.uv_loop_s* %loop) #0 !dbg !269 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %buf = alloca i8*, align 8
  %len = alloca i64, align 8
  %fd = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !472, metadata !286), !dbg !473
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !474, metadata !286), !dbg !477
  call void @llvm.dbg.declare(metadata i64* %len, metadata !478, metadata !286), !dbg !483
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !484, metadata !286), !dbg !485
  call void @llvm.dbg.declare(metadata i32* %r, metadata !486, metadata !286), !dbg !487
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.2, i32 0, i32 0), i8** %buf, align 8, !dbg !488
  store i64 1, i64* %len, align 8, !dbg !489
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !490
  %async_wfd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 24, !dbg !491
  %1 = load i32, i32* %async_wfd, align 8, !dbg !491
  store i32 %1, i32* %fd, align 4, !dbg !492
  %2 = load i32, i32* %fd, align 4, !dbg !493
  %cmp = icmp eq i32 %2, -1, !dbg !495
  br i1 %cmp, label %if.then, label %if.end, !dbg !496

if.then:                                          ; preds = %entry
  store i8* bitcast (i64* @uv__async_send.val to i8*), i8** %buf, align 8, !dbg !497
  store i64 8, i64* %len, align 8, !dbg !499
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !500
  %async_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 23, !dbg !501
  %fd1 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher, i32 0, i32 5, !dbg !502
  %4 = load i32, i32* %fd1, align 8, !dbg !502
  store i32 %4, i32* %fd, align 4, !dbg !503
  br label %if.end, !dbg !504

if.end:                                           ; preds = %if.then, %entry
  br label %do.body, !dbg !505

do.body:                                          ; preds = %land.end, %if.end
  %5 = load i32, i32* %fd, align 4, !dbg !506
  %6 = load i8*, i8** %buf, align 8, !dbg !507
  %7 = load i64, i64* %len, align 8, !dbg !508
  %call = call i64 @write(i32 %5, i8* %6, i64 %7), !dbg !509
  %conv = trunc i64 %call to i32, !dbg !509
  store i32 %conv, i32* %r, align 4, !dbg !510
  br label %do.cond, !dbg !511

do.cond:                                          ; preds = %do.body
  %8 = load i32, i32* %r, align 4, !dbg !512
  %cmp2 = icmp eq i32 %8, -1, !dbg !513
  br i1 %cmp2, label %land.rhs, label %land.end, !dbg !514

land.rhs:                                         ; preds = %do.cond
  %call4 = call i32* @__errno_location() #1, !dbg !515
  %9 = load i32, i32* %call4, align 4, !dbg !515
  %cmp5 = icmp eq i32 %9, 4, !dbg !517
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %10 = phi i1 [ false, %do.cond ], [ %cmp5, %land.rhs ]
  br i1 %10, label %do.body, label %do.end, !dbg !518

do.end:                                           ; preds = %land.end
  %11 = load i32, i32* %r, align 4, !dbg !519
  %conv7 = sext i32 %11 to i64, !dbg !519
  %12 = load i64, i64* %len, align 8, !dbg !521
  %cmp8 = icmp eq i64 %conv7, %12, !dbg !522
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !523

if.then10:                                        ; preds = %do.end
  br label %return, !dbg !524

if.end11:                                         ; preds = %do.end
  %13 = load i32, i32* %r, align 4, !dbg !525
  %cmp12 = icmp eq i32 %13, -1, !dbg !527
  br i1 %cmp12, label %if.then14, label %if.end23, !dbg !528

if.then14:                                        ; preds = %if.end11
  %call15 = call i32* @__errno_location() #1, !dbg !529
  %14 = load i32, i32* %call15, align 4, !dbg !529
  %cmp16 = icmp eq i32 %14, 11, !dbg !531
  br i1 %cmp16, label %if.then21, label %lor.lhs.false, !dbg !532

lor.lhs.false:                                    ; preds = %if.then14
  %call18 = call i32* @__errno_location() #1, !dbg !533
  %15 = load i32, i32* %call18, align 4, !dbg !533
  %cmp19 = icmp eq i32 %15, 11, !dbg !535
  br i1 %cmp19, label %if.then21, label %if.end22, !dbg !536

if.then21:                                        ; preds = %lor.lhs.false, %if.then14
  br label %return, !dbg !537

if.end22:                                         ; preds = %lor.lhs.false
  br label %if.end23, !dbg !538

if.end23:                                         ; preds = %if.end22, %if.end11
  call void @abort() #6, !dbg !540
  unreachable, !dbg !540

return:                                           ; preds = %if.then21, %if.then10
  ret void, !dbg !541
}

; Function Attrs: nounwind uwtable
define void @uv__async_close(%struct.uv_async_s* %handle) #0 !dbg !257 {
entry:
  %handle.addr = alloca %struct.uv_async_s*, align 8
  store %struct.uv_async_s* %handle, %struct.uv_async_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_async_s** %handle.addr, metadata !542, metadata !286), !dbg !543
  br label %do.body, !dbg !544

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !545
  %queue = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %0, i32 0, i32 9, !dbg !545
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !545
  %1 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !545
  %2 = load [2 x i8*]*, [2 x i8*]** %1, align 8, !dbg !545
  %3 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !545
  %queue1 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %3, i32 0, i32 9, !dbg !545
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue1, i64 0, i64 1, !dbg !545
  %4 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !545
  %5 = load [2 x i8*]*, [2 x i8*]** %4, align 8, !dbg !545
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %5, i64 0, i64 0, !dbg !545
  %6 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !545
  store [2 x i8*]* %2, [2 x i8*]** %6, align 8, !dbg !545
  %7 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !545
  %queue4 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %7, i32 0, i32 9, !dbg !545
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue4, i64 0, i64 1, !dbg !545
  %8 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !545
  %9 = load [2 x i8*]*, [2 x i8*]** %8, align 8, !dbg !545
  %10 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !545
  %queue6 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %10, i32 0, i32 9, !dbg !545
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue6, i64 0, i64 0, !dbg !545
  %11 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !545
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !545
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %12, i64 0, i64 1, !dbg !545
  %13 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !545
  store [2 x i8*]* %9, [2 x i8*]** %13, align 8, !dbg !545
  br label %do.end, !dbg !545

do.end:                                           ; preds = %do.body
  br label %do.body9, !dbg !548

do.body9:                                         ; preds = %do.end
  %14 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !549
  %flags = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %14, i32 0, i32 7, !dbg !549
  %15 = load i32, i32* %flags, align 8, !dbg !549
  %and = and i32 %15, 0, !dbg !549
  %cmp = icmp eq i32 %and, 0, !dbg !549
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !549

cond.true:                                        ; preds = %do.body9
  br label %cond.end, !dbg !552

cond.false:                                       ; preds = %do.body9
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.1, i32 0, i32 0), i32 73, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__async_close, i32 0, i32 0)) #6, !dbg !554
  unreachable, !dbg !554
                                                  ; No predecessors!
  br label %cond.end, !dbg !556

cond.end:                                         ; preds = %16, %cond.true
  %17 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !558
  %flags10 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %17, i32 0, i32 7, !dbg !558
  %18 = load i32, i32* %flags10, align 8, !dbg !558
  %and11 = and i32 %18, 16384, !dbg !558
  %cmp12 = icmp eq i32 %and11, 0, !dbg !558
  br i1 %cmp12, label %if.then, label %if.end, !dbg !558

if.then:                                          ; preds = %cond.end
  br label %do.end22, !dbg !561

if.end:                                           ; preds = %cond.end
  %19 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !563
  %flags13 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %19, i32 0, i32 7, !dbg !563
  %20 = load i32, i32* %flags13, align 8, !dbg !563
  %and14 = and i32 %20, -16385, !dbg !563
  store i32 %and14, i32* %flags13, align 8, !dbg !563
  %21 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !563
  %flags15 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %21, i32 0, i32 7, !dbg !563
  %22 = load i32, i32* %flags15, align 8, !dbg !563
  %and16 = and i32 %22, 8192, !dbg !563
  %cmp17 = icmp ne i32 %and16, 0, !dbg !563
  br i1 %cmp17, label %if.then18, label %if.end21, !dbg !563

if.then18:                                        ; preds = %if.end
  br label %do.body19, !dbg !565

do.body19:                                        ; preds = %if.then18
  %23 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !568
  %loop = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %23, i32 0, i32 1, !dbg !568
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !568
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 1, !dbg !568
  %25 = load i32, i32* %active_handles, align 8, !dbg !568
  %dec = add i32 %25, -1, !dbg !568
  store i32 %dec, i32* %active_handles, align 8, !dbg !568
  br label %do.end20, !dbg !568

do.end20:                                         ; preds = %do.body19
  br label %if.end21, !dbg !571

if.end21:                                         ; preds = %do.end20, %if.end
  br label %do.end22, !dbg !573

do.end22:                                         ; preds = %if.end21, %if.then
  ret void, !dbg !575
}

; Function Attrs: nounwind uwtable
define i32 @uv__async_fork(%struct.uv_loop_s* %loop) #0 !dbg !258 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !576, metadata !286), !dbg !577
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !578
  %async_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 23, !dbg !580
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher, i32 0, i32 5, !dbg !581
  %1 = load i32, i32* %fd, align 8, !dbg !581
  %cmp = icmp eq i32 %1, -1, !dbg !582
  br i1 %cmp, label %if.then, label %if.end, !dbg !583

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !584
  br label %return, !dbg !584

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !585
  call void @uv__async_stop(%struct.uv_loop_s* %2), !dbg !586
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !587
  %call = call i32 @uv__async_start(%struct.uv_loop_s* %3), !dbg !588
  store i32 %call, i32* %retval, align 4, !dbg !589
  br label %return, !dbg !589

return:                                           ; preds = %if.end, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !590
  ret i32 %4, !dbg !590
}

; Function Attrs: nounwind uwtable
define void @uv__async_stop(%struct.uv_loop_s* %loop) #0 !dbg !261 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !591, metadata !286), !dbg !592
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !593
  %async_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 23, !dbg !595
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher, i32 0, i32 5, !dbg !596
  %1 = load i32, i32* %fd, align 8, !dbg !596
  %cmp = icmp eq i32 %1, -1, !dbg !597
  br i1 %cmp, label %if.then, label %if.end, !dbg !598

if.then:                                          ; preds = %entry
  br label %return, !dbg !599

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !600
  %async_wfd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 24, !dbg !602
  %3 = load i32, i32* %async_wfd, align 8, !dbg !602
  %cmp1 = icmp ne i32 %3, -1, !dbg !603
  br i1 %cmp1, label %if.then2, label %if.end11, !dbg !604

if.then2:                                         ; preds = %if.end
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !605
  %async_wfd3 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 24, !dbg !608
  %5 = load i32, i32* %async_wfd3, align 8, !dbg !608
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !609
  %async_io_watcher4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 23, !dbg !610
  %fd5 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher4, i32 0, i32 5, !dbg !611
  %7 = load i32, i32* %fd5, align 8, !dbg !611
  %cmp6 = icmp ne i32 %5, %7, !dbg !612
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !613

if.then7:                                         ; preds = %if.then2
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !614
  %async_wfd8 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 24, !dbg !615
  %9 = load i32, i32* %async_wfd8, align 8, !dbg !615
  %call = call i32 @uv__close(i32 %9), !dbg !616
  br label %if.end9, !dbg !616

if.end9:                                          ; preds = %if.then7, %if.then2
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !617
  %async_wfd10 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 24, !dbg !618
  store i32 -1, i32* %async_wfd10, align 8, !dbg !619
  br label %if.end11, !dbg !620

if.end11:                                         ; preds = %if.end9, %if.end
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !621
  %12 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !622
  %async_io_watcher12 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %12, i32 0, i32 23, !dbg !623
  call void @uv__io_stop(%struct.uv_loop_s* %11, %struct.uv__io_s* %async_io_watcher12, i32 1), !dbg !624
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !625
  %async_io_watcher13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 23, !dbg !626
  %fd14 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher13, i32 0, i32 5, !dbg !627
  %14 = load i32, i32* %fd14, align 8, !dbg !627
  %call15 = call i32 @uv__close(i32 %14), !dbg !628
  %15 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !629
  %async_io_watcher16 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %15, i32 0, i32 23, !dbg !630
  %fd17 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %async_io_watcher16, i32 0, i32 5, !dbg !631
  store i32 -1, i32* %fd17, align 8, !dbg !632
  br label %return, !dbg !633

return:                                           ; preds = %if.end11, %if.then
  ret void, !dbg !634
}

declare i32 @uv__close(i32) #3

declare void @uv__io_stop(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #3

declare i64 @write(i32, i8*, i64) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: noreturn nounwind
declare void @abort() #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__async_eventfd() #0 !dbg !271 {
entry:
  %retval = alloca i32, align 4
  %fd = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !636, metadata !286), !dbg !637
  %0 = load i32, i32* @uv__async_eventfd.no_eventfd2, align 4, !dbg !638
  %tobool = icmp ne i32 %0, 0, !dbg !638
  br i1 %tobool, label %if.then, label %if.end, !dbg !640

if.then:                                          ; preds = %entry
  br label %skip_eventfd2, !dbg !641

if.end:                                           ; preds = %entry
  %call = call i32 @uv__eventfd2(i32 0, i32 526336), !dbg !642
  store i32 %call, i32* %fd, align 4, !dbg !643
  %1 = load i32, i32* %fd, align 4, !dbg !644
  %cmp = icmp ne i32 %1, -1, !dbg !646
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !647

if.then1:                                         ; preds = %if.end
  %2 = load i32, i32* %fd, align 4, !dbg !648
  store i32 %2, i32* %retval, align 4, !dbg !649
  br label %return, !dbg !649

if.end2:                                          ; preds = %if.end
  %call3 = call i32* @__errno_location() #1, !dbg !650
  %3 = load i32, i32* %call3, align 4, !dbg !650
  %cmp4 = icmp ne i32 %3, 38, !dbg !652
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !653

if.then5:                                         ; preds = %if.end2
  %call6 = call i32* @__errno_location() #1, !dbg !654
  %4 = load i32, i32* %call6, align 4, !dbg !654
  %sub = sub nsw i32 0, %4, !dbg !655
  store i32 %sub, i32* %retval, align 4, !dbg !656
  br label %return, !dbg !656

if.end7:                                          ; preds = %if.end2
  store i32 1, i32* @uv__async_eventfd.no_eventfd2, align 4, !dbg !657
  br label %skip_eventfd2, !dbg !658

skip_eventfd2:                                    ; preds = %if.end7, %if.then
  %5 = load i32, i32* @uv__async_eventfd.no_eventfd, align 4, !dbg !659
  %tobool8 = icmp ne i32 %5, 0, !dbg !659
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !661

if.then9:                                         ; preds = %skip_eventfd2
  br label %skip_eventfd, !dbg !662

if.end10:                                         ; preds = %skip_eventfd2
  %call11 = call i32 @uv__eventfd(i32 0), !dbg !663
  store i32 %call11, i32* %fd, align 4, !dbg !664
  %6 = load i32, i32* %fd, align 4, !dbg !665
  %cmp12 = icmp ne i32 %6, -1, !dbg !667
  br i1 %cmp12, label %if.then13, label %if.end16, !dbg !668

if.then13:                                        ; preds = %if.end10
  %7 = load i32, i32* %fd, align 4, !dbg !669
  %call14 = call i32 @uv__cloexec_ioctl(i32 %7, i32 1), !dbg !671
  %8 = load i32, i32* %fd, align 4, !dbg !672
  %call15 = call i32 @uv__nonblock_ioctl(i32 %8, i32 1), !dbg !673
  %9 = load i32, i32* %fd, align 4, !dbg !674
  store i32 %9, i32* %retval, align 4, !dbg !675
  br label %return, !dbg !675

if.end16:                                         ; preds = %if.end10
  %call17 = call i32* @__errno_location() #1, !dbg !676
  %10 = load i32, i32* %call17, align 4, !dbg !676
  %cmp18 = icmp ne i32 %10, 38, !dbg !678
  br i1 %cmp18, label %if.then19, label %if.end22, !dbg !679

if.then19:                                        ; preds = %if.end16
  %call20 = call i32* @__errno_location() #1, !dbg !680
  %11 = load i32, i32* %call20, align 4, !dbg !680
  %sub21 = sub nsw i32 0, %11, !dbg !681
  store i32 %sub21, i32* %retval, align 4, !dbg !682
  br label %return, !dbg !682

if.end22:                                         ; preds = %if.end16
  store i32 1, i32* @uv__async_eventfd.no_eventfd, align 4, !dbg !683
  br label %skip_eventfd, !dbg !684

skip_eventfd:                                     ; preds = %if.end22, %if.then9
  store i32 -38, i32* %retval, align 4, !dbg !685
  br label %return, !dbg !685

return:                                           ; preds = %skip_eventfd, %if.then19, %if.then13, %if.then5, %if.then1
  %12 = load i32, i32* %retval, align 4, !dbg !686
  ret i32 %12, !dbg !686
}

declare i32 @uv__make_pipe(i32*, i32) #3

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i64, i8*, ...) #5

declare i32 @uv__open_cloexec(i8*, i32) #3

declare void @uv__io_init(%struct.uv__io_s*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, i32) #3

; Function Attrs: nounwind uwtable
define internal void @uv__async_io(%struct.uv_loop_s* %loop, %struct.uv__io_s* %w, i32 %events) #0 !dbg !274 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__io_s*, align 8
  %events.addr = alloca i32, align 4
  %buf = alloca [1024 x i8], align 16
  %r = alloca i64, align 8
  %queue = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %h = alloca %struct.uv_async_s*, align 8
  %q21 = alloca [2 x i8*]*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !687, metadata !286), !dbg !688
  store %struct.uv__io_s* %w, %struct.uv__io_s** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w.addr, metadata !689, metadata !286), !dbg !690
  store i32 %events, i32* %events.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %events.addr, metadata !691, metadata !286), !dbg !692
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buf, metadata !693, metadata !286), !dbg !697
  call void @llvm.dbg.declare(metadata i64* %r, metadata !698, metadata !286), !dbg !699
  call void @llvm.dbg.declare(metadata [2 x i8*]* %queue, metadata !700, metadata !286), !dbg !701
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !702, metadata !286), !dbg !703
  call void @llvm.dbg.declare(metadata %struct.uv_async_s** %h, metadata !704, metadata !286), !dbg !705
  %0 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !706
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !706
  %async_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 23, !dbg !706
  %cmp = icmp eq %struct.uv__io_s* %0, %async_io_watcher, !dbg !706
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !706

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !707

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.1, i32 0, i32 0), i32 84, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @__PRETTY_FUNCTION__.uv__async_io, i32 0, i32 0)) #6, !dbg !709
  unreachable, !dbg !709
                                                  ; No predecessors!
  br label %cond.end, !dbg !711

cond.end:                                         ; preds = %2, %cond.true
  br label %for.cond, !dbg !713

for.cond:                                         ; preds = %if.then13, %if.then, %cond.end
  %3 = load %struct.uv__io_s*, %struct.uv__io_s** %w.addr, align 8, !dbg !714
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %3, i32 0, i32 5, !dbg !718
  %4 = load i32, i32* %fd, align 8, !dbg !718
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !719
  %call = call i64 @read(i32 %4, i8* %arraydecay, i64 1024), !dbg !720
  store i64 %call, i64* %r, align 8, !dbg !721
  %5 = load i64, i64* %r, align 8, !dbg !722
  %cmp1 = icmp eq i64 %5, 1024, !dbg !724
  br i1 %cmp1, label %if.then, label %if.end, !dbg !725

if.then:                                          ; preds = %for.cond
  br label %for.cond, !dbg !726

if.end:                                           ; preds = %for.cond
  %6 = load i64, i64* %r, align 8, !dbg !727
  %cmp2 = icmp ne i64 %6, -1, !dbg !729
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !730

if.then3:                                         ; preds = %if.end
  br label %for.end, !dbg !731

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !732
  %7 = load i32, i32* %call5, align 4, !dbg !732
  %cmp6 = icmp eq i32 %7, 11, !dbg !734
  br i1 %cmp6, label %if.then9, label %lor.lhs.false, !dbg !735

lor.lhs.false:                                    ; preds = %if.end4
  %call7 = call i32* @__errno_location() #1, !dbg !736
  %8 = load i32, i32* %call7, align 4, !dbg !736
  %cmp8 = icmp eq i32 %8, 11, !dbg !738
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !739

if.then9:                                         ; preds = %lor.lhs.false, %if.end4
  br label %for.end, !dbg !740

if.end10:                                         ; preds = %lor.lhs.false
  %call11 = call i32* @__errno_location() #1, !dbg !741
  %9 = load i32, i32* %call11, align 4, !dbg !741
  %cmp12 = icmp eq i32 %9, 4, !dbg !743
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !744

if.then13:                                        ; preds = %if.end10
  br label %for.cond, !dbg !745

if.end14:                                         ; preds = %if.end10
  call void @abort() #6, !dbg !746
  unreachable, !dbg !746

for.end:                                          ; preds = %if.then9, %if.then3
  br label %do.body, !dbg !747

do.body:                                          ; preds = %for.end
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !748
  %async_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 21, !dbg !748
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !748
  %async_handles15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 21, !dbg !748
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles15, i64 0, i64 0, !dbg !748
  %12 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !748
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !748
  %cmp16 = icmp eq [2 x i8*]* %async_handles, %13, !dbg !748
  br i1 %cmp16, label %if.then17, label %if.else, !dbg !748

if.then17:                                        ; preds = %do.body
  br label %do.body18, !dbg !752

do.body18:                                        ; preds = %if.then17
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !754
  %14 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !754
  store [2 x i8*]* %queue, [2 x i8*]** %14, align 16, !dbg !754
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !754
  %15 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !754
  store [2 x i8*]* %queue, [2 x i8*]** %15, align 8, !dbg !754
  br label %do.end, !dbg !754

do.end:                                           ; preds = %do.body18
  br label %if.end40, !dbg !757

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q21, metadata !759, metadata !286), !dbg !761
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !762
  %async_handles22 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 21, !dbg !762
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles22, i64 0, i64 0, !dbg !762
  %17 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !762
  %18 = load [2 x i8*]*, [2 x i8*]** %17, align 8, !dbg !762
  store [2 x i8*]* %18, [2 x i8*]** %q21, align 8, !dbg !762
  br label %do.body24, !dbg !762

do.body24:                                        ; preds = %if.else
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !764
  %async_handles25 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %19, i32 0, i32 21, !dbg !764
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles25, i64 0, i64 1, !dbg !764
  %20 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !764
  %21 = load [2 x i8*]*, [2 x i8*]** %20, align 8, !dbg !764
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !764
  %22 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !764
  store [2 x i8*]* %21, [2 x i8*]** %22, align 8, !dbg !764
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 1, !dbg !764
  %23 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !764
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !764
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 0, !dbg !764
  %25 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !764
  store [2 x i8*]* %queue, [2 x i8*]** %25, align 8, !dbg !764
  %26 = load [2 x i8*]*, [2 x i8*]** %q21, align 8, !dbg !764
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !764
  %27 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !764
  store [2 x i8*]* %26, [2 x i8*]** %27, align 16, !dbg !764
  %28 = load [2 x i8*]*, [2 x i8*]** %q21, align 8, !dbg !764
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %28, i64 0, i64 1, !dbg !764
  %29 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !764
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !764
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !764
  %async_handles32 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %31, i32 0, i32 21, !dbg !764
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles32, i64 0, i64 1, !dbg !764
  %32 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !764
  store [2 x i8*]* %30, [2 x i8*]** %32, align 8, !dbg !764
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !764
  %async_handles34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 21, !dbg !764
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !764
  %async_handles35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 21, !dbg !764
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles35, i64 0, i64 1, !dbg !764
  %35 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !764
  %36 = load [2 x i8*]*, [2 x i8*]** %35, align 8, !dbg !764
  %arrayidx37 = getelementptr inbounds [2 x i8*], [2 x i8*]* %36, i64 0, i64 0, !dbg !764
  %37 = bitcast i8** %arrayidx37 to [2 x i8*]**, !dbg !764
  store [2 x i8*]* %async_handles34, [2 x i8*]** %37, align 8, !dbg !764
  %38 = load [2 x i8*]*, [2 x i8*]** %q21, align 8, !dbg !764
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %38, i64 0, i64 1, !dbg !764
  %39 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !764
  store [2 x i8*]* %queue, [2 x i8*]** %39, align 8, !dbg !764
  br label %do.end39, !dbg !764

do.end39:                                         ; preds = %do.body24
  br label %if.end40

if.end40:                                         ; preds = %do.end39, %do.end
  br label %do.end41, !dbg !767

do.end41:                                         ; preds = %if.end40
  br label %while.cond, !dbg !769

while.cond:                                       ; preds = %if.end70, %if.then69, %if.then66, %do.end41
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !770
  %40 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !770
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 16, !dbg !770
  %cmp43 = icmp eq [2 x i8*]* %queue, %41, !dbg !770
  %lnot = xor i1 %cmp43, true, !dbg !771
  br i1 %lnot, label %while.body, label %while.end, !dbg !772

while.body:                                       ; preds = %while.cond
  %arrayidx44 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !773
  %42 = bitcast i8** %arrayidx44 to [2 x i8*]**, !dbg !773
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 16, !dbg !773
  store [2 x i8*]* %43, [2 x i8*]** %q, align 8, !dbg !775
  %44 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !776
  %45 = bitcast [2 x i8*]* %44 to i8*, !dbg !776
  %add.ptr = getelementptr inbounds i8, i8* %45, i64 -104, !dbg !776
  %46 = bitcast i8* %add.ptr to %struct.uv_async_s*, !dbg !776
  store %struct.uv_async_s* %46, %struct.uv_async_s** %h, align 8, !dbg !777
  br label %do.body45, !dbg !778

do.body45:                                        ; preds = %while.body
  %47 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !779
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !779
  %48 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !779
  %49 = load [2 x i8*]*, [2 x i8*]** %48, align 8, !dbg !779
  %50 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !779
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 1, !dbg !779
  %51 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !779
  %52 = load [2 x i8*]*, [2 x i8*]** %51, align 8, !dbg !779
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %52, i64 0, i64 0, !dbg !779
  %53 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !779
  store [2 x i8*]* %49, [2 x i8*]** %53, align 8, !dbg !779
  %54 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !779
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !779
  %55 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !779
  %56 = load [2 x i8*]*, [2 x i8*]** %55, align 8, !dbg !779
  %57 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !779
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 0, !dbg !779
  %58 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !779
  %59 = load [2 x i8*]*, [2 x i8*]** %58, align 8, !dbg !779
  %arrayidx51 = getelementptr inbounds [2 x i8*], [2 x i8*]* %59, i64 0, i64 1, !dbg !779
  %60 = bitcast i8** %arrayidx51 to [2 x i8*]**, !dbg !779
  store [2 x i8*]* %56, [2 x i8*]** %60, align 8, !dbg !779
  br label %do.end52, !dbg !779

do.end52:                                         ; preds = %do.body45
  br label %do.body53, !dbg !782

do.body53:                                        ; preds = %do.end52
  %61 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !783
  %async_handles54 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %61, i32 0, i32 21, !dbg !783
  %62 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %62, i64 0, i64 0, !dbg !783
  %63 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !783
  store [2 x i8*]* %async_handles54, [2 x i8*]** %63, align 8, !dbg !783
  %64 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !783
  %async_handles56 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %64, i32 0, i32 21, !dbg !783
  %arrayidx57 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles56, i64 0, i64 1, !dbg !783
  %65 = bitcast i8** %arrayidx57 to [2 x i8*]**, !dbg !783
  %66 = load [2 x i8*]*, [2 x i8*]** %65, align 8, !dbg !783
  %67 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx58 = getelementptr inbounds [2 x i8*], [2 x i8*]* %67, i64 0, i64 1, !dbg !783
  %68 = bitcast i8** %arrayidx58 to [2 x i8*]**, !dbg !783
  store [2 x i8*]* %66, [2 x i8*]** %68, align 8, !dbg !783
  %69 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %70 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %arrayidx59 = getelementptr inbounds [2 x i8*], [2 x i8*]* %70, i64 0, i64 1, !dbg !783
  %71 = bitcast i8** %arrayidx59 to [2 x i8*]**, !dbg !783
  %72 = load [2 x i8*]*, [2 x i8*]** %71, align 8, !dbg !783
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %72, i64 0, i64 0, !dbg !783
  %73 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !783
  store [2 x i8*]* %69, [2 x i8*]** %73, align 8, !dbg !783
  %74 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !783
  %75 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !783
  %async_handles61 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %75, i32 0, i32 21, !dbg !783
  %arrayidx62 = getelementptr inbounds [2 x i8*], [2 x i8*]* %async_handles61, i64 0, i64 1, !dbg !783
  %76 = bitcast i8** %arrayidx62 to [2 x i8*]**, !dbg !783
  store [2 x i8*]* %74, [2 x i8*]** %76, align 8, !dbg !783
  br label %do.end63, !dbg !783

do.end63:                                         ; preds = %do.body53
  %77 = load %struct.uv_async_s*, %struct.uv_async_s** %h, align 8, !dbg !786
  %pending = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %77, i32 0, i32 10, !dbg !788
  %call64 = call i32 @cmpxchgi(i32* %pending, i32 1, i32 0), !dbg !789
  %cmp65 = icmp eq i32 %call64, 0, !dbg !790
  br i1 %cmp65, label %if.then66, label %if.end67, !dbg !791

if.then66:                                        ; preds = %do.end63
  br label %while.cond, !dbg !792

if.end67:                                         ; preds = %do.end63
  %78 = load %struct.uv_async_s*, %struct.uv_async_s** %h, align 8, !dbg !793
  %async_cb = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %78, i32 0, i32 8, !dbg !795
  %79 = load void (%struct.uv_async_s*)*, void (%struct.uv_async_s*)** %async_cb, align 8, !dbg !795
  %cmp68 = icmp eq void (%struct.uv_async_s*)* %79, null, !dbg !796
  br i1 %cmp68, label %if.then69, label %if.end70, !dbg !797

if.then69:                                        ; preds = %if.end67
  br label %while.cond, !dbg !798

if.end70:                                         ; preds = %if.end67
  %80 = load %struct.uv_async_s*, %struct.uv_async_s** %h, align 8, !dbg !799
  %async_cb71 = getelementptr inbounds %struct.uv_async_s, %struct.uv_async_s* %80, i32 0, i32 8, !dbg !800
  %81 = load void (%struct.uv_async_s*)*, void (%struct.uv_async_s*)** %async_cb71, align 8, !dbg !800
  %82 = load %struct.uv_async_s*, %struct.uv_async_s** %h, align 8, !dbg !801
  call void %81(%struct.uv_async_s* %82), !dbg !799
  br label %while.cond, !dbg !802

while.end:                                        ; preds = %while.cond
  ret void, !dbg !803
}

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #3

declare i32 @uv__eventfd2(i32, i32) #3

declare i32 @uv__eventfd(i32) #3

declare i32 @uv__cloexec_ioctl(i32, i32) #3

declare i32 @uv__nonblock_ioctl(i32, i32) #3

declare i64 @read(i32, i8*, i64) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!282, !283}
!llvm.ident = !{!284}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !33, subprograms: !249, globals: !277)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/async.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
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
!33 = !{!34, !240, !244, !246, !142, !248, !39}
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
!245 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !57)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !242)
!248 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!249 = !{!250, !254, !257, !258, !261, !264, !269, !270, !271, !274}
!250 = distinct !DISubprogram(name: "uv_async_init", scope: !1, file: !1, line: 41, type: !251, isLocal: false, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!251 = !DISubroutineType(types: !252)
!252 = !{!57, !41, !142, !138}
!253 = !{}
!254 = distinct !DISubprogram(name: "uv_async_send", scope: !1, file: !1, line: 59, type: !255, isLocal: false, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!255 = !DISubroutineType(types: !256)
!256 = !{!57, !142}
!257 = distinct !DISubprogram(name: "uv__async_close", scope: !1, file: !1, line: 71, type: !140, isLocal: false, isDefinition: true, scopeLine: 71, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!258 = distinct !DISubprogram(name: "uv__async_fork", scope: !1, file: !1, line: 203, type: !259, isLocal: false, isDefinition: true, scopeLine: 203, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!259 = !DISubroutineType(types: !260)
!260 = !{!57, !41}
!261 = distinct !DISubprogram(name: "uv__async_stop", scope: !1, file: !1, line: 213, type: !262, isLocal: false, isDefinition: true, scopeLine: 213, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!262 = !DISubroutineType(types: !263)
!263 = !{null, !41}
!264 = distinct !DISubprogram(name: "cmpxchgi", scope: !265, file: !265, line: 33, type: !266, isLocal: true, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!265 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/atomic-ops.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!266 = !DISubroutineType(types: !267)
!267 = !{!57, !268, !57, !57}
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!269 = distinct !DISubprogram(name: "uv__async_send", scope: !1, file: !1, line: 123, type: !262, isLocal: true, isDefinition: true, scopeLine: 123, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!270 = distinct !DISubprogram(name: "uv__async_start", scope: !1, file: !1, line: 157, type: !259, isLocal: true, isDefinition: true, scopeLine: 157, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!271 = distinct !DISubprogram(name: "uv__async_eventfd", scope: !1, file: !1, line: 229, type: !272, isLocal: true, isDefinition: true, scopeLine: 229, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!272 = !DISubroutineType(types: !273)
!273 = !{!57}
!274 = distinct !DISubprogram(name: "uv__async_io", scope: !1, file: !1, line: 77, type: !275, isLocal: true, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !253)
!275 = !DISubroutineType(types: !276)
!276 = !{null, !41, !62, !47}
!277 = !{!278, !280, !281}
!278 = !DIGlobalVariable(name: "val", scope: !269, file: !1, line: 135, type: !279, isLocal: true, isDefinition: true, variable: i64* @uv__async_send.val)
!279 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !187)
!280 = !DIGlobalVariable(name: "no_eventfd2", scope: !271, file: !1, line: 231, type: !57, isLocal: true, isDefinition: true, variable: i32* @uv__async_eventfd.no_eventfd2)
!281 = !DIGlobalVariable(name: "no_eventfd", scope: !271, file: !1, line: 232, type: !57, isLocal: true, isDefinition: true, variable: i32* @uv__async_eventfd.no_eventfd)
!282 = !{i32 2, !"Dwarf Version", i32 4}
!283 = !{i32 2, !"Debug Info Version", i32 3}
!284 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!285 = !DILocalVariable(name: "loop", arg: 1, scope: !250, file: !1, line: 41, type: !41)
!286 = !DIExpression()
!287 = !DILocation(line: 41, column: 30, scope: !250)
!288 = !DILocalVariable(name: "handle", arg: 2, scope: !250, file: !1, line: 41, type: !142)
!289 = !DILocation(line: 41, column: 48, scope: !250)
!290 = !DILocalVariable(name: "async_cb", arg: 3, scope: !250, file: !1, line: 41, type: !138)
!291 = !DILocation(line: 41, column: 68, scope: !250)
!292 = !DILocalVariable(name: "err", scope: !250, file: !1, line: 42, type: !57)
!293 = !DILocation(line: 42, column: 7, scope: !250)
!294 = !DILocation(line: 44, column: 25, scope: !250)
!295 = !DILocation(line: 44, column: 9, scope: !250)
!296 = !DILocation(line: 44, column: 7, scope: !250)
!297 = !DILocation(line: 45, column: 7, scope: !298)
!298 = distinct !DILexicalBlock(scope: !250, file: !1, line: 45, column: 7)
!299 = !DILocation(line: 45, column: 7, scope: !250)
!300 = !DILocation(line: 46, column: 12, scope: !298)
!301 = !DILocation(line: 46, column: 5, scope: !298)
!302 = !DILocation(line: 48, column: 3, scope: !250)
!303 = !DILocation(line: 48, column: 3, scope: !304)
!304 = !DILexicalBlockFile(scope: !305, file: !1, discriminator: 1)
!305 = distinct !DILexicalBlock(scope: !250, file: !1, line: 48, column: 3)
!306 = !DILocation(line: 48, column: 3, scope: !307)
!307 = !DILexicalBlockFile(scope: !308, file: !1, discriminator: 2)
!308 = distinct !DILexicalBlock(scope: !305, file: !1, line: 48, column: 3)
!309 = !DILocation(line: 48, column: 3, scope: !310)
!310 = !DILexicalBlockFile(scope: !305, file: !1, discriminator: 3)
!311 = !DILocation(line: 49, column: 22, scope: !250)
!312 = !DILocation(line: 49, column: 3, scope: !250)
!313 = !DILocation(line: 49, column: 11, scope: !250)
!314 = !DILocation(line: 49, column: 20, scope: !250)
!315 = !DILocation(line: 50, column: 3, scope: !250)
!316 = !DILocation(line: 50, column: 11, scope: !250)
!317 = !DILocation(line: 50, column: 19, scope: !250)
!318 = !DILocation(line: 52, column: 3, scope: !250)
!319 = !DILocation(line: 52, column: 3, scope: !320)
!320 = !DILexicalBlockFile(scope: !321, file: !1, discriminator: 1)
!321 = distinct !DILexicalBlock(scope: !250, file: !1, line: 52, column: 3)
!322 = !DILocation(line: 53, column: 3, scope: !250)
!323 = !DILocation(line: 53, column: 3, scope: !324)
!324 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 1)
!325 = distinct !DILexicalBlock(scope: !250, file: !1, line: 53, column: 3)
!326 = !DILocation(line: 53, column: 3, scope: !327)
!327 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 2)
!328 = !DILocation(line: 53, column: 3, scope: !329)
!329 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 3)
!330 = !DILocation(line: 53, column: 3, scope: !331)
!331 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 4)
!332 = !DILocation(line: 53, column: 3, scope: !333)
!333 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 5)
!334 = distinct !DILexicalBlock(scope: !325, file: !1, line: 53, column: 3)
!335 = !DILocation(line: 53, column: 3, scope: !336)
!336 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 6)
!337 = !DILocation(line: 53, column: 3, scope: !338)
!338 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 7)
!339 = !DILocation(line: 53, column: 3, scope: !340)
!340 = !DILexicalBlockFile(scope: !341, file: !1, discriminator: 8)
!341 = distinct !DILexicalBlock(scope: !325, file: !1, line: 53, column: 3)
!342 = !DILocation(line: 53, column: 3, scope: !343)
!343 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 9)
!344 = distinct !DILexicalBlock(scope: !341, file: !1, line: 53, column: 3)
!345 = !DILocation(line: 53, column: 3, scope: !346)
!346 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 10)
!347 = !DILocation(line: 53, column: 3, scope: !348)
!348 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 11)
!349 = !DILocation(line: 55, column: 3, scope: !250)
!350 = !DILocation(line: 56, column: 1, scope: !250)
!351 = !DILocalVariable(name: "loop", arg: 1, scope: !270, file: !1, line: 157, type: !41)
!352 = !DILocation(line: 157, column: 39, scope: !270)
!353 = !DILocalVariable(name: "pipefd", scope: !270, file: !1, line: 158, type: !191)
!354 = !DILocation(line: 158, column: 7, scope: !270)
!355 = !DILocalVariable(name: "err", scope: !270, file: !1, line: 159, type: !57)
!356 = !DILocation(line: 159, column: 7, scope: !270)
!357 = !DILocation(line: 161, column: 7, scope: !358)
!358 = distinct !DILexicalBlock(scope: !270, file: !1, line: 161, column: 7)
!359 = !DILocation(line: 161, column: 13, scope: !358)
!360 = !DILocation(line: 161, column: 30, scope: !358)
!361 = !DILocation(line: 161, column: 33, scope: !358)
!362 = !DILocation(line: 161, column: 7, scope: !270)
!363 = !DILocation(line: 162, column: 5, scope: !358)
!364 = !DILocation(line: 164, column: 9, scope: !270)
!365 = !DILocation(line: 164, column: 7, scope: !270)
!366 = !DILocation(line: 165, column: 7, scope: !367)
!367 = distinct !DILexicalBlock(scope: !270, file: !1, line: 165, column: 7)
!368 = !DILocation(line: 165, column: 11, scope: !367)
!369 = !DILocation(line: 165, column: 7, scope: !270)
!370 = !DILocation(line: 166, column: 17, scope: !371)
!371 = distinct !DILexicalBlock(scope: !367, file: !1, line: 165, column: 17)
!372 = !DILocation(line: 166, column: 5, scope: !371)
!373 = !DILocation(line: 166, column: 15, scope: !371)
!374 = !DILocation(line: 167, column: 5, scope: !371)
!375 = !DILocation(line: 167, column: 15, scope: !371)
!376 = !DILocation(line: 168, column: 3, scope: !371)
!377 = !DILocation(line: 169, column: 12, scope: !378)
!378 = distinct !DILexicalBlock(scope: !367, file: !1, line: 169, column: 12)
!379 = !DILocation(line: 169, column: 16, scope: !378)
!380 = !DILocation(line: 169, column: 12, scope: !367)
!381 = !DILocation(line: 170, column: 25, scope: !382)
!382 = distinct !DILexicalBlock(scope: !378, file: !1, line: 169, column: 28)
!383 = !DILocation(line: 170, column: 11, scope: !382)
!384 = !DILocation(line: 170, column: 9, scope: !382)
!385 = !DILocation(line: 176, column: 9, scope: !386)
!386 = distinct !DILexicalBlock(scope: !382, file: !1, line: 176, column: 9)
!387 = !DILocation(line: 176, column: 13, scope: !386)
!388 = !DILocation(line: 176, column: 9, scope: !382)
!389 = !DILocalVariable(name: "buf", scope: !390, file: !1, line: 177, type: !391)
!390 = distinct !DILexicalBlock(scope: !386, file: !1, line: 176, column: 19)
!391 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 256, align: 8, elements: !392)
!392 = !{!393}
!393 = !DISubrange(count: 32)
!394 = !DILocation(line: 177, column: 12, scope: !390)
!395 = !DILocalVariable(name: "fd", scope: !390, file: !1, line: 178, type: !57)
!396 = !DILocation(line: 178, column: 11, scope: !390)
!397 = !DILocation(line: 180, column: 16, scope: !390)
!398 = !DILocation(line: 180, column: 54, scope: !390)
!399 = !DILocation(line: 180, column: 7, scope: !390)
!400 = !DILocation(line: 181, column: 29, scope: !390)
!401 = !DILocation(line: 181, column: 12, scope: !390)
!402 = !DILocation(line: 181, column: 10, scope: !390)
!403 = !DILocation(line: 182, column: 11, scope: !404)
!404 = distinct !DILexicalBlock(scope: !390, file: !1, line: 182, column: 11)
!405 = !DILocation(line: 182, column: 14, scope: !404)
!406 = !DILocation(line: 182, column: 11, scope: !390)
!407 = !DILocation(line: 183, column: 19, scope: !408)
!408 = distinct !DILexicalBlock(scope: !404, file: !1, line: 182, column: 20)
!409 = !DILocation(line: 183, column: 9, scope: !408)
!410 = !DILocation(line: 184, column: 19, scope: !408)
!411 = !DILocation(line: 184, column: 9, scope: !408)
!412 = !DILocation(line: 185, column: 21, scope: !408)
!413 = !DILocation(line: 185, column: 9, scope: !408)
!414 = !DILocation(line: 185, column: 19, scope: !408)
!415 = !DILocation(line: 186, column: 21, scope: !408)
!416 = !DILocation(line: 186, column: 9, scope: !408)
!417 = !DILocation(line: 186, column: 19, scope: !408)
!418 = !DILocation(line: 187, column: 7, scope: !408)
!419 = !DILocation(line: 188, column: 5, scope: !390)
!420 = !DILocation(line: 190, column: 3, scope: !382)
!421 = !DILocation(line: 192, column: 7, scope: !422)
!422 = distinct !DILexicalBlock(scope: !270, file: !1, line: 192, column: 7)
!423 = !DILocation(line: 192, column: 11, scope: !422)
!424 = !DILocation(line: 192, column: 7, scope: !270)
!425 = !DILocation(line: 193, column: 12, scope: !422)
!426 = !DILocation(line: 193, column: 5, scope: !422)
!427 = !DILocation(line: 195, column: 16, scope: !270)
!428 = !DILocation(line: 195, column: 22, scope: !270)
!429 = !DILocation(line: 195, column: 54, scope: !270)
!430 = !DILocation(line: 195, column: 3, scope: !270)
!431 = !DILocation(line: 196, column: 16, scope: !270)
!432 = !DILocation(line: 196, column: 23, scope: !270)
!433 = !DILocation(line: 196, column: 29, scope: !270)
!434 = !DILocation(line: 196, column: 3, scope: !270)
!435 = !DILocation(line: 197, column: 21, scope: !270)
!436 = !DILocation(line: 197, column: 3, scope: !270)
!437 = !DILocation(line: 197, column: 9, scope: !270)
!438 = !DILocation(line: 197, column: 19, scope: !270)
!439 = !DILocation(line: 199, column: 3, scope: !270)
!440 = !DILocation(line: 200, column: 1, scope: !270)
!441 = !DILocalVariable(name: "handle", arg: 1, scope: !254, file: !1, line: 59, type: !142)
!442 = !DILocation(line: 59, column: 31, scope: !254)
!443 = !DILocation(line: 61, column: 7, scope: !444)
!444 = distinct !DILexicalBlock(scope: !254, file: !1, line: 61, column: 7)
!445 = !DILocation(line: 61, column: 41, scope: !444)
!446 = !DILocation(line: 61, column: 7, scope: !254)
!447 = !DILocation(line: 62, column: 5, scope: !444)
!448 = !DILocation(line: 64, column: 17, scope: !449)
!449 = distinct !DILexicalBlock(scope: !254, file: !1, line: 64, column: 7)
!450 = !DILocation(line: 64, column: 25, scope: !449)
!451 = !DILocation(line: 64, column: 7, scope: !449)
!452 = !DILocation(line: 64, column: 40, scope: !449)
!453 = !DILocation(line: 64, column: 7, scope: !254)
!454 = !DILocation(line: 65, column: 20, scope: !449)
!455 = !DILocation(line: 65, column: 28, scope: !449)
!456 = !DILocation(line: 65, column: 5, scope: !449)
!457 = !DILocation(line: 67, column: 3, scope: !254)
!458 = !DILocation(line: 68, column: 1, scope: !254)
!459 = !DILocalVariable(name: "ptr", arg: 1, scope: !264, file: !265, line: 33, type: !268)
!460 = !DILocation(line: 33, column: 1, scope: !264)
!461 = !DILocalVariable(name: "oldval", arg: 2, scope: !264, file: !265, line: 33, type: !57)
!462 = !DILocalVariable(name: "newval", arg: 3, scope: !264, file: !265, line: 33, type: !57)
!463 = !DILocalVariable(name: "out", scope: !264, file: !265, line: 35, type: !57)
!464 = !DILocation(line: 35, column: 7, scope: !264)
!465 = !DILocation(line: 37, column: 62, scope: !264)
!466 = !DILocation(line: 38, column: 32, scope: !264)
!467 = !DILocation(line: 38, column: 46, scope: !264)
!468 = !DILocation(line: 36, column: 3, scope: !264)
!469 = !{i32 1170134}
!470 = !DILocation(line: 40, column: 10, scope: !264)
!471 = !DILocation(line: 40, column: 3, scope: !264)
!472 = !DILocalVariable(name: "loop", arg: 1, scope: !269, file: !1, line: 123, type: !41)
!473 = !DILocation(line: 123, column: 39, scope: !269)
!474 = !DILocalVariable(name: "buf", scope: !269, file: !1, line: 124, type: !475)
!475 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !476, size: 64, align: 64)
!476 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!477 = !DILocation(line: 124, column: 15, scope: !269)
!478 = !DILocalVariable(name: "len", scope: !269, file: !1, line: 125, type: !479)
!479 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !480, line: 102, baseType: !481)
!480 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!481 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !482, line: 172, baseType: !112)
!482 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!483 = !DILocation(line: 125, column: 11, scope: !269)
!484 = !DILocalVariable(name: "fd", scope: !269, file: !1, line: 126, type: !57)
!485 = !DILocation(line: 126, column: 7, scope: !269)
!486 = !DILocalVariable(name: "r", scope: !269, file: !1, line: 127, type: !57)
!487 = !DILocation(line: 127, column: 7, scope: !269)
!488 = !DILocation(line: 129, column: 7, scope: !269)
!489 = !DILocation(line: 130, column: 7, scope: !269)
!490 = !DILocation(line: 131, column: 8, scope: !269)
!491 = !DILocation(line: 131, column: 14, scope: !269)
!492 = !DILocation(line: 131, column: 6, scope: !269)
!493 = !DILocation(line: 134, column: 7, scope: !494)
!494 = distinct !DILexicalBlock(scope: !269, file: !1, line: 134, column: 7)
!495 = !DILocation(line: 134, column: 10, scope: !494)
!496 = !DILocation(line: 134, column: 7, scope: !269)
!497 = !DILocation(line: 136, column: 9, scope: !498)
!498 = distinct !DILexicalBlock(scope: !494, file: !1, line: 134, column: 17)
!499 = !DILocation(line: 137, column: 9, scope: !498)
!500 = !DILocation(line: 138, column: 10, scope: !498)
!501 = !DILocation(line: 138, column: 16, scope: !498)
!502 = !DILocation(line: 138, column: 33, scope: !498)
!503 = !DILocation(line: 138, column: 8, scope: !498)
!504 = !DILocation(line: 139, column: 3, scope: !498)
!505 = !DILocation(line: 142, column: 3, scope: !269)
!506 = !DILocation(line: 143, column: 15, scope: !269)
!507 = !DILocation(line: 143, column: 19, scope: !269)
!508 = !DILocation(line: 143, column: 24, scope: !269)
!509 = !DILocation(line: 143, column: 9, scope: !269)
!510 = !DILocation(line: 143, column: 7, scope: !269)
!511 = !DILocation(line: 143, column: 5, scope: !269)
!512 = !DILocation(line: 144, column: 10, scope: !269)
!513 = !DILocation(line: 144, column: 12, scope: !269)
!514 = !DILocation(line: 144, column: 18, scope: !269)
!515 = !DILocation(line: 144, column: 21, scope: !516)
!516 = !DILexicalBlockFile(scope: !269, file: !1, discriminator: 1)
!517 = !DILocation(line: 144, column: 27, scope: !516)
!518 = !DILocation(line: 143, column: 5, scope: !516)
!519 = !DILocation(line: 146, column: 7, scope: !520)
!520 = distinct !DILexicalBlock(scope: !269, file: !1, line: 146, column: 7)
!521 = !DILocation(line: 146, column: 12, scope: !520)
!522 = !DILocation(line: 146, column: 9, scope: !520)
!523 = !DILocation(line: 146, column: 7, scope: !269)
!524 = !DILocation(line: 147, column: 5, scope: !520)
!525 = !DILocation(line: 149, column: 7, scope: !526)
!526 = distinct !DILexicalBlock(scope: !269, file: !1, line: 149, column: 7)
!527 = !DILocation(line: 149, column: 9, scope: !526)
!528 = !DILocation(line: 149, column: 7, scope: !269)
!529 = !DILocation(line: 150, column: 9, scope: !530)
!530 = distinct !DILexicalBlock(scope: !526, file: !1, line: 150, column: 9)
!531 = !DILocation(line: 150, column: 15, scope: !530)
!532 = !DILocation(line: 150, column: 25, scope: !530)
!533 = !DILocation(line: 150, column: 28, scope: !534)
!534 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 1)
!535 = !DILocation(line: 150, column: 34, scope: !534)
!536 = !DILocation(line: 150, column: 9, scope: !534)
!537 = !DILocation(line: 151, column: 7, scope: !530)
!538 = !DILocation(line: 150, column: 37, scope: !539)
!539 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 2)
!540 = !DILocation(line: 153, column: 3, scope: !269)
!541 = !DILocation(line: 154, column: 1, scope: !269)
!542 = !DILocalVariable(name: "handle", arg: 1, scope: !257, file: !1, line: 71, type: !142)
!543 = !DILocation(line: 71, column: 34, scope: !257)
!544 = !DILocation(line: 72, column: 3, scope: !257)
!545 = !DILocation(line: 72, column: 3, scope: !546)
!546 = !DILexicalBlockFile(scope: !547, file: !1, discriminator: 1)
!547 = distinct !DILexicalBlock(scope: !257, file: !1, line: 72, column: 3)
!548 = !DILocation(line: 73, column: 3, scope: !257)
!549 = !DILocation(line: 73, column: 3, scope: !550)
!550 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 1)
!551 = distinct !DILexicalBlock(scope: !257, file: !1, line: 73, column: 3)
!552 = !DILocation(line: 73, column: 3, scope: !553)
!553 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 2)
!554 = !DILocation(line: 73, column: 3, scope: !555)
!555 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 3)
!556 = !DILocation(line: 73, column: 3, scope: !557)
!557 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 4)
!558 = !DILocation(line: 73, column: 3, scope: !559)
!559 = !DILexicalBlockFile(scope: !560, file: !1, discriminator: 5)
!560 = distinct !DILexicalBlock(scope: !551, file: !1, line: 73, column: 3)
!561 = !DILocation(line: 73, column: 3, scope: !562)
!562 = !DILexicalBlockFile(scope: !560, file: !1, discriminator: 6)
!563 = !DILocation(line: 73, column: 3, scope: !564)
!564 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 7)
!565 = !DILocation(line: 73, column: 3, scope: !566)
!566 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 8)
!567 = distinct !DILexicalBlock(scope: !551, file: !1, line: 73, column: 3)
!568 = !DILocation(line: 73, column: 3, scope: !569)
!569 = !DILexicalBlockFile(scope: !570, file: !1, discriminator: 9)
!570 = distinct !DILexicalBlock(scope: !567, file: !1, line: 73, column: 3)
!571 = !DILocation(line: 73, column: 3, scope: !572)
!572 = !DILexicalBlockFile(scope: !570, file: !1, discriminator: 10)
!573 = !DILocation(line: 73, column: 3, scope: !574)
!574 = !DILexicalBlockFile(scope: !551, file: !1, discriminator: 11)
!575 = !DILocation(line: 74, column: 1, scope: !257)
!576 = !DILocalVariable(name: "loop", arg: 1, scope: !258, file: !1, line: 203, type: !41)
!577 = !DILocation(line: 203, column: 31, scope: !258)
!578 = !DILocation(line: 204, column: 7, scope: !579)
!579 = distinct !DILexicalBlock(scope: !258, file: !1, line: 204, column: 7)
!580 = !DILocation(line: 204, column: 13, scope: !579)
!581 = !DILocation(line: 204, column: 30, scope: !579)
!582 = !DILocation(line: 204, column: 33, scope: !579)
!583 = !DILocation(line: 204, column: 7, scope: !258)
!584 = !DILocation(line: 205, column: 5, scope: !579)
!585 = !DILocation(line: 207, column: 18, scope: !258)
!586 = !DILocation(line: 207, column: 3, scope: !258)
!587 = !DILocation(line: 209, column: 26, scope: !258)
!588 = !DILocation(line: 209, column: 10, scope: !258)
!589 = !DILocation(line: 209, column: 3, scope: !258)
!590 = !DILocation(line: 210, column: 1, scope: !258)
!591 = !DILocalVariable(name: "loop", arg: 1, scope: !261, file: !1, line: 213, type: !41)
!592 = !DILocation(line: 213, column: 32, scope: !261)
!593 = !DILocation(line: 214, column: 7, scope: !594)
!594 = distinct !DILexicalBlock(scope: !261, file: !1, line: 214, column: 7)
!595 = !DILocation(line: 214, column: 13, scope: !594)
!596 = !DILocation(line: 214, column: 30, scope: !594)
!597 = !DILocation(line: 214, column: 33, scope: !594)
!598 = !DILocation(line: 214, column: 7, scope: !261)
!599 = !DILocation(line: 215, column: 5, scope: !594)
!600 = !DILocation(line: 217, column: 7, scope: !601)
!601 = distinct !DILexicalBlock(scope: !261, file: !1, line: 217, column: 7)
!602 = !DILocation(line: 217, column: 13, scope: !601)
!603 = !DILocation(line: 217, column: 23, scope: !601)
!604 = !DILocation(line: 217, column: 7, scope: !261)
!605 = !DILocation(line: 218, column: 9, scope: !606)
!606 = distinct !DILexicalBlock(scope: !607, file: !1, line: 218, column: 9)
!607 = distinct !DILexicalBlock(scope: !601, file: !1, line: 217, column: 30)
!608 = !DILocation(line: 218, column: 15, scope: !606)
!609 = !DILocation(line: 218, column: 28, scope: !606)
!610 = !DILocation(line: 218, column: 34, scope: !606)
!611 = !DILocation(line: 218, column: 51, scope: !606)
!612 = !DILocation(line: 218, column: 25, scope: !606)
!613 = !DILocation(line: 218, column: 9, scope: !607)
!614 = !DILocation(line: 219, column: 17, scope: !606)
!615 = !DILocation(line: 219, column: 23, scope: !606)
!616 = !DILocation(line: 219, column: 7, scope: !606)
!617 = !DILocation(line: 220, column: 5, scope: !607)
!618 = !DILocation(line: 220, column: 11, scope: !607)
!619 = !DILocation(line: 220, column: 21, scope: !607)
!620 = !DILocation(line: 221, column: 3, scope: !607)
!621 = !DILocation(line: 223, column: 15, scope: !261)
!622 = !DILocation(line: 223, column: 22, scope: !261)
!623 = !DILocation(line: 223, column: 28, scope: !261)
!624 = !DILocation(line: 223, column: 3, scope: !261)
!625 = !DILocation(line: 224, column: 13, scope: !261)
!626 = !DILocation(line: 224, column: 19, scope: !261)
!627 = !DILocation(line: 224, column: 36, scope: !261)
!628 = !DILocation(line: 224, column: 3, scope: !261)
!629 = !DILocation(line: 225, column: 3, scope: !261)
!630 = !DILocation(line: 225, column: 9, scope: !261)
!631 = !DILocation(line: 225, column: 26, scope: !261)
!632 = !DILocation(line: 225, column: 29, scope: !261)
!633 = !DILocation(line: 226, column: 1, scope: !261)
!634 = !DILocation(line: 226, column: 1, scope: !635)
!635 = !DILexicalBlockFile(scope: !261, file: !1, discriminator: 1)
!636 = !DILocalVariable(name: "fd", scope: !271, file: !1, line: 233, type: !57)
!637 = !DILocation(line: 233, column: 7, scope: !271)
!638 = !DILocation(line: 235, column: 7, scope: !639)
!639 = distinct !DILexicalBlock(scope: !271, file: !1, line: 235, column: 7)
!640 = !DILocation(line: 235, column: 7, scope: !271)
!641 = !DILocation(line: 236, column: 5, scope: !639)
!642 = !DILocation(line: 238, column: 8, scope: !271)
!643 = !DILocation(line: 238, column: 6, scope: !271)
!644 = !DILocation(line: 239, column: 7, scope: !645)
!645 = distinct !DILexicalBlock(scope: !271, file: !1, line: 239, column: 7)
!646 = !DILocation(line: 239, column: 10, scope: !645)
!647 = !DILocation(line: 239, column: 7, scope: !271)
!648 = !DILocation(line: 240, column: 12, scope: !645)
!649 = !DILocation(line: 240, column: 5, scope: !645)
!650 = !DILocation(line: 242, column: 7, scope: !651)
!651 = distinct !DILexicalBlock(scope: !271, file: !1, line: 242, column: 7)
!652 = !DILocation(line: 242, column: 13, scope: !651)
!653 = !DILocation(line: 242, column: 7, scope: !271)
!654 = !DILocation(line: 243, column: 13, scope: !651)
!655 = !DILocation(line: 243, column: 12, scope: !651)
!656 = !DILocation(line: 243, column: 5, scope: !651)
!657 = !DILocation(line: 245, column: 15, scope: !271)
!658 = !DILocation(line: 245, column: 3, scope: !271)
!659 = !DILocation(line: 249, column: 7, scope: !660)
!660 = distinct !DILexicalBlock(scope: !271, file: !1, line: 249, column: 7)
!661 = !DILocation(line: 249, column: 7, scope: !271)
!662 = !DILocation(line: 250, column: 5, scope: !660)
!663 = !DILocation(line: 252, column: 8, scope: !271)
!664 = !DILocation(line: 252, column: 6, scope: !271)
!665 = !DILocation(line: 253, column: 7, scope: !666)
!666 = distinct !DILexicalBlock(scope: !271, file: !1, line: 253, column: 7)
!667 = !DILocation(line: 253, column: 10, scope: !666)
!668 = !DILocation(line: 253, column: 7, scope: !271)
!669 = !DILocation(line: 254, column: 17, scope: !670)
!670 = distinct !DILexicalBlock(scope: !666, file: !1, line: 253, column: 17)
!671 = !DILocation(line: 254, column: 5, scope: !670)
!672 = !DILocation(line: 255, column: 18, scope: !670)
!673 = !DILocation(line: 255, column: 5, scope: !670)
!674 = !DILocation(line: 256, column: 12, scope: !670)
!675 = !DILocation(line: 256, column: 5, scope: !670)
!676 = !DILocation(line: 259, column: 7, scope: !677)
!677 = distinct !DILexicalBlock(scope: !271, file: !1, line: 259, column: 7)
!678 = !DILocation(line: 259, column: 13, scope: !677)
!679 = !DILocation(line: 259, column: 7, scope: !271)
!680 = !DILocation(line: 260, column: 13, scope: !677)
!681 = !DILocation(line: 260, column: 12, scope: !677)
!682 = !DILocation(line: 260, column: 5, scope: !677)
!683 = !DILocation(line: 262, column: 14, scope: !271)
!684 = !DILocation(line: 262, column: 3, scope: !271)
!685 = !DILocation(line: 268, column: 3, scope: !271)
!686 = !DILocation(line: 269, column: 1, scope: !271)
!687 = !DILocalVariable(name: "loop", arg: 1, scope: !274, file: !1, line: 77, type: !41)
!688 = !DILocation(line: 77, column: 37, scope: !274)
!689 = !DILocalVariable(name: "w", arg: 2, scope: !274, file: !1, line: 77, type: !62)
!690 = !DILocation(line: 77, column: 53, scope: !274)
!691 = !DILocalVariable(name: "events", arg: 3, scope: !274, file: !1, line: 77, type: !47)
!692 = !DILocation(line: 77, column: 69, scope: !274)
!693 = !DILocalVariable(name: "buf", scope: !274, file: !1, line: 78, type: !694)
!694 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 8192, align: 8, elements: !695)
!695 = !{!696}
!696 = !DISubrange(count: 1024)
!697 = !DILocation(line: 78, column: 8, scope: !274)
!698 = !DILocalVariable(name: "r", scope: !274, file: !1, line: 79, type: !479)
!699 = !DILocation(line: 79, column: 11, scope: !274)
!700 = !DILocalVariable(name: "queue", scope: !274, file: !1, line: 80, type: !242)
!701 = !DILocation(line: 80, column: 9, scope: !274)
!702 = !DILocalVariable(name: "q", scope: !274, file: !1, line: 81, type: !241)
!703 = !DILocation(line: 81, column: 10, scope: !274)
!704 = !DILocalVariable(name: "h", scope: !274, file: !1, line: 82, type: !142)
!705 = !DILocation(line: 82, column: 15, scope: !274)
!706 = !DILocation(line: 84, column: 3, scope: !274)
!707 = !DILocation(line: 84, column: 3, scope: !708)
!708 = !DILexicalBlockFile(scope: !274, file: !1, discriminator: 1)
!709 = !DILocation(line: 84, column: 3, scope: !710)
!710 = !DILexicalBlockFile(scope: !274, file: !1, discriminator: 2)
!711 = !DILocation(line: 84, column: 3, scope: !712)
!712 = !DILexicalBlockFile(scope: !274, file: !1, discriminator: 3)
!713 = !DILocation(line: 86, column: 3, scope: !274)
!714 = !DILocation(line: 87, column: 14, scope: !715)
!715 = distinct !DILexicalBlock(scope: !716, file: !1, line: 86, column: 12)
!716 = distinct !DILexicalBlock(scope: !717, file: !1, line: 86, column: 3)
!717 = distinct !DILexicalBlock(scope: !274, file: !1, line: 86, column: 3)
!718 = !DILocation(line: 87, column: 17, scope: !715)
!719 = !DILocation(line: 87, column: 21, scope: !715)
!720 = !DILocation(line: 87, column: 9, scope: !715)
!721 = !DILocation(line: 87, column: 7, scope: !715)
!722 = !DILocation(line: 89, column: 9, scope: !723)
!723 = distinct !DILexicalBlock(scope: !715, file: !1, line: 89, column: 9)
!724 = !DILocation(line: 89, column: 11, scope: !723)
!725 = !DILocation(line: 89, column: 9, scope: !715)
!726 = !DILocation(line: 90, column: 7, scope: !723)
!727 = !DILocation(line: 92, column: 9, scope: !728)
!728 = distinct !DILexicalBlock(scope: !715, file: !1, line: 92, column: 9)
!729 = !DILocation(line: 92, column: 11, scope: !728)
!730 = !DILocation(line: 92, column: 9, scope: !715)
!731 = !DILocation(line: 93, column: 7, scope: !728)
!732 = !DILocation(line: 95, column: 9, scope: !733)
!733 = distinct !DILexicalBlock(scope: !715, file: !1, line: 95, column: 9)
!734 = !DILocation(line: 95, column: 15, scope: !733)
!735 = !DILocation(line: 95, column: 25, scope: !733)
!736 = !DILocation(line: 95, column: 28, scope: !737)
!737 = !DILexicalBlockFile(scope: !733, file: !1, discriminator: 1)
!738 = !DILocation(line: 95, column: 34, scope: !737)
!739 = !DILocation(line: 95, column: 9, scope: !737)
!740 = !DILocation(line: 96, column: 7, scope: !733)
!741 = !DILocation(line: 98, column: 9, scope: !742)
!742 = distinct !DILexicalBlock(scope: !715, file: !1, line: 98, column: 9)
!743 = !DILocation(line: 98, column: 15, scope: !742)
!744 = !DILocation(line: 98, column: 9, scope: !715)
!745 = !DILocation(line: 99, column: 7, scope: !742)
!746 = !DILocation(line: 101, column: 5, scope: !715)
!747 = !DILocation(line: 104, column: 3, scope: !274)
!748 = !DILocation(line: 104, column: 3, scope: !749)
!749 = !DILexicalBlockFile(scope: !750, file: !1, discriminator: 1)
!750 = distinct !DILexicalBlock(scope: !751, file: !1, line: 104, column: 3)
!751 = distinct !DILexicalBlock(scope: !274, file: !1, line: 104, column: 3)
!752 = !DILocation(line: 104, column: 3, scope: !753)
!753 = !DILexicalBlockFile(scope: !750, file: !1, discriminator: 2)
!754 = !DILocation(line: 104, column: 3, scope: !755)
!755 = !DILexicalBlockFile(scope: !756, file: !1, discriminator: 3)
!756 = distinct !DILexicalBlock(scope: !750, file: !1, line: 104, column: 3)
!757 = !DILocation(line: 104, column: 3, scope: !758)
!758 = !DILexicalBlockFile(scope: !756, file: !1, discriminator: 4)
!759 = !DILocalVariable(name: "q", scope: !760, file: !1, line: 104, type: !241)
!760 = distinct !DILexicalBlock(scope: !750, file: !1, line: 104, column: 3)
!761 = !DILocation(line: 104, column: 3, scope: !760)
!762 = !DILocation(line: 104, column: 3, scope: !763)
!763 = !DILexicalBlockFile(scope: !760, file: !1, discriminator: 5)
!764 = !DILocation(line: 104, column: 3, scope: !765)
!765 = !DILexicalBlockFile(scope: !766, file: !1, discriminator: 6)
!766 = distinct !DILexicalBlock(scope: !760, file: !1, line: 104, column: 3)
!767 = !DILocation(line: 104, column: 3, scope: !768)
!768 = !DILexicalBlockFile(scope: !751, file: !1, discriminator: 7)
!769 = !DILocation(line: 105, column: 3, scope: !274)
!770 = !DILocation(line: 105, column: 11, scope: !708)
!771 = !DILocation(line: 105, column: 10, scope: !708)
!772 = !DILocation(line: 105, column: 3, scope: !708)
!773 = !DILocation(line: 106, column: 9, scope: !774)
!774 = distinct !DILexicalBlock(scope: !274, file: !1, line: 105, column: 32)
!775 = !DILocation(line: 106, column: 7, scope: !774)
!776 = !DILocation(line: 107, column: 9, scope: !774)
!777 = !DILocation(line: 107, column: 7, scope: !774)
!778 = !DILocation(line: 109, column: 5, scope: !774)
!779 = !DILocation(line: 109, column: 5, scope: !780)
!780 = !DILexicalBlockFile(scope: !781, file: !1, discriminator: 1)
!781 = distinct !DILexicalBlock(scope: !774, file: !1, line: 109, column: 5)
!782 = !DILocation(line: 110, column: 5, scope: !774)
!783 = !DILocation(line: 110, column: 5, scope: !784)
!784 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 1)
!785 = distinct !DILexicalBlock(scope: !774, file: !1, line: 110, column: 5)
!786 = !DILocation(line: 112, column: 19, scope: !787)
!787 = distinct !DILexicalBlock(scope: !774, file: !1, line: 112, column: 9)
!788 = !DILocation(line: 112, column: 22, scope: !787)
!789 = !DILocation(line: 112, column: 9, scope: !787)
!790 = !DILocation(line: 112, column: 37, scope: !787)
!791 = !DILocation(line: 112, column: 9, scope: !774)
!792 = !DILocation(line: 113, column: 7, scope: !787)
!793 = !DILocation(line: 115, column: 9, scope: !794)
!794 = distinct !DILexicalBlock(scope: !774, file: !1, line: 115, column: 9)
!795 = !DILocation(line: 115, column: 12, scope: !794)
!796 = !DILocation(line: 115, column: 21, scope: !794)
!797 = !DILocation(line: 115, column: 9, scope: !774)
!798 = !DILocation(line: 116, column: 7, scope: !794)
!799 = !DILocation(line: 118, column: 5, scope: !774)
!800 = !DILocation(line: 118, column: 8, scope: !774)
!801 = !DILocation(line: 118, column: 17, scope: !774)
!802 = !DILocation(line: 105, column: 3, scope: !710)
!803 = !DILocation(line: 120, column: 1, scope: !274)
